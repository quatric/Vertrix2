#include "process.h"
#include "win32.h"

#include <stdlib.h>
#include <string.h>

/* The multimedia timer functions and one wave output device. Written buffers go to the
 * platform at once; a host thread marks each header done once the platform has played past its
 * end, then signals the game the way waveOutOpen asked (an event or a callback function). */

static void timeGetTime(Cpu *c)
{
    STDCALL_RETURN(0, (uint32_t)(v3_microseconds() / 1000u));
}

static void timeBeginPeriod(Cpu *c)
{
    STDCALL_RETURN(1, 0);
}

static void timeEndPeriod(Cpu *c)
{
    STDCALL_RETURN(1, 0);
}

static void timeGetDevCaps(Cpu *c)
{
    v3_w32(ARG(0), 1);
    v3_w32(ARG(0) + 4, 1000000);
    STDCALL_RETURN(2, 0);
}

enum
{
    QUEUE = 64,
    WHDR_DONE = 1,
    WHDR_PREPARED = 2,
    WHDR_INQUEUE = 0x10,
    WOM_OPEN = 0x3bb,
    WOM_CLOSE = 0x3bc,
    WOM_DONE = 0x3bd
};

static struct
{
    int open;
    uint32_t handle;
    uint32_t flags, callback, instance;
    uint32_t rate, channels, bits;
    uint32_t headers[QUEUE];
    uint64_t ends[QUEUE];
    unsigned head, count;
    uint64_t written;
    int pump_started;
    V3Thread *pump;
} wave;

static void notify(Cpu *c, uint32_t message, uint32_t header)
{
    const uint32_t type = wave.flags & 0x70000u;
    if (type == 0x50000u) /* CALLBACK_EVENT */
    {
        const uint32_t h = wave.callback;
        V3EventObject *e = v3_handle_get(h, V3_HANDLE_EVENT);
        if (e)
        {
            v3_event_set(e->event);
        }
    }
    else if (type == 0x30000u && c) /* CALLBACK_FUNCTION */
    {
        const uint32_t arguments[5] = {wave.handle, message, wave.instance, header, 0};
        v3_call_guest(c, wave.callback, 5, arguments, 0);
    }
}

static void pump(void *p)
{
    V3Thread *t = p;
    v3_thread_set_self(t);
    for (;;)
    {
        v3_sleep_ms(4);
        if (!wave.open)
        {
            continue;
        }
        const uint64_t played = v3_platform->wave_played ? v3_platform->wave_played() : wave.written;
        for (;;)
        {
            uint32_t header = 0;
            v3_lock();
            if (wave.count && wave.ends[wave.head] <= played)
            {
                header = wave.headers[wave.head];
                wave.head = (wave.head + 1) % QUEUE;
                --wave.count;
                v3_w32(header + 16, (v3_r32(header + 16) | WHDR_DONE) & ~WHDR_INQUEUE);
            }
            v3_unlock();
            if (!header)
            {
                break;
            }
            notify(&t->cpu, WOM_DONE, header);
        }
    }
}

static void waveOutGetNumDevs(Cpu *c)
{
    STDCALL_RETURN(0, 1);
}

static void waveOutGetDevCapsA(Cpu *c)
{
    const uint32_t caps = ARG(1);
    memset(MEM(caps), 0, ARG(2) < 52 ? ARG(2) : 52);
    v3_w16(caps, 1);
    v3_w16(caps + 2, 1);
    v3_w32(caps + 4, 0x100);
    v3_write_string(caps + 8, "Wii audio", 32);
    v3_w32(caps + 40, 0xfff);
    v3_w16(caps + 44, 2);
    v3_w32(caps + 48, 0x2c); /* volume, left/right volume, sample accurate */
    STDCALL_RETURN(3, 0);
}

static void waveOutOpen(Cpu *c)
{
    const uint32_t format = ARG(2);
    const uint32_t flags = ARG(5);
    const uint32_t tag = v3_r16(format);
    const uint32_t channels = v3_r16(format + 2);
    const uint32_t rate = v3_r32(format + 4);
    const uint32_t bits = v3_r16(format + 14);
    v3_log("waveOutOpen(format %u, %u Hz, %u channels, %u bits, flags %x)", tag, rate, channels,
           bits, flags);
    if (tag != 1 || (bits != 8 && bits != 16) || channels < 1 || channels > 2)
    {
        STDCALL_RETURN(6, 32); /* WAVERR_BADFORMAT */
    }
    if (flags & 1) /* WAVE_FORMAT_QUERY */
    {
        STDCALL_RETURN(6, 0);
    }
    wave.flags = flags;
    wave.callback = ARG(3);
    wave.instance = ARG(4);
    wave.rate = rate;
    wave.channels = channels;
    wave.bits = bits;
    wave.head = wave.count = 0;
    wave.written = 0;
    wave.handle = v3_handle_new(V3_HANDLE_WAVE, &wave);
    if (ARG(0))
    {
        v3_w32(ARG(0), wave.handle);
    }
    if (v3_platform->wave_open)
    {
        v3_platform->wave_open(rate, channels, bits);
    }
    wave.open = 1;
    if (!wave.pump_started)
    {
        wave.pump_started = 1;
        wave.pump = v3_thread_create(0, 0, 0x40000);
        v3_thread_start(pump, wave.pump, 1);
    }
    notify(c, WOM_OPEN, 0);
    STDCALL_RETURN(6, 0);
}

static void waveOutPrepareHeader(Cpu *c)
{
    const uint32_t header = ARG(1);
    v3_w32(header + 16, (v3_r32(header + 16) | WHDR_PREPARED) & ~WHDR_DONE);
    STDCALL_RETURN(3, 0);
}

static void waveOutUnprepareHeader(Cpu *c)
{
    const uint32_t header = ARG(1);
    if (v3_r32(header + 16) & WHDR_INQUEUE)
    {
        STDCALL_RETURN(3, 33); /* WAVERR_STILLPLAYING */
    }
    v3_w32(header + 16, v3_r32(header + 16) & ~WHDR_PREPARED);
    STDCALL_RETURN(3, 0);
}

static void waveOutWrite(Cpu *c)
{
    const uint32_t header = ARG(1);
    const uint32_t data = v3_r32(header);
    const uint32_t length = v3_r32(header + 4);
    v3_lock();
    if (wave.count == QUEUE)
    {
        v3_unlock();
        STDCALL_RETURN(3, 1);
    }
    v3_w32(header + 16, (v3_r32(header + 16) | WHDR_INQUEUE) & ~WHDR_DONE);
    wave.written += length;
    const unsigned slot = (wave.head + wave.count) % QUEUE;
    wave.headers[slot] = header;
    wave.ends[slot] = wave.written;
    ++wave.count;
    v3_unlock();
    if (v3_platform->wave_write && v3_contiguous(data, length))
    {
        v3_platform->wave_write(MEM(data), length);
    }
    STDCALL_RETURN(3, 0);
}

static void waveOutReset(Cpu *c)
{
    for (;;)
    {
        uint32_t header = 0;
        v3_lock();
        if (wave.count)
        {
            header = wave.headers[wave.head];
            wave.head = (wave.head + 1) % QUEUE;
            --wave.count;
            v3_w32(header + 16, (v3_r32(header + 16) | WHDR_DONE) & ~WHDR_INQUEUE);
        }
        v3_unlock();
        if (!header)
        {
            break;
        }
        notify(c, WOM_DONE, header);
    }
    STDCALL_RETURN(1, 0);
}

static void waveOutClose(Cpu *c)
{
    wave.open = 0;
    notify(c, WOM_CLOSE, 0);
    STDCALL_RETURN(1, 0);
}

/* --- multimedia timers ----------------------------------------------------------------------
 * Each timer runs on its own host thread with its own guest CPU, as a Windows timer callback runs
 * on the system's timer thread: due times follow a fixed schedule from the start, so a late tick
 * does not move the ones after it. */

enum
{
    TIMERS = 8,
    TIME_PERIODIC = 0x1,
    TIME_CALLBACK_EVENT_SET = 0x10,
    TIME_CALLBACK_EVENT_PULSE = 0x20
};

typedef struct
{
    volatile int active;
    uint32_t id, delay, callback, user, flags;
    V3Thread *thread;
} Timer;

static Timer timers[TIMERS];

static void timer_run(void *p)
{
    Timer *t = p;
    v3_thread_set_self(t->thread);
    const uint32_t id = t->id;
    uint64_t due = v3_microseconds();
    while (t->active && t->id == id)
    {
        due += (uint64_t)(t->delay ? t->delay : 1u) * 1000u;
        const uint64_t now = v3_microseconds();
        if (due > now)
        {
            v3_sleep_ms((uint32_t)((due - now + 999u) / 1000u));
        }
        if (!t->active || t->id != id)
        {
            break;
        }
        if (t->flags & (TIME_CALLBACK_EVENT_SET | TIME_CALLBACK_EVENT_PULSE))
        {
            V3EventObject *e = v3_handle_get(t->callback, V3_HANDLE_EVENT);
            if (e)
            {
                v3_event_set(e->event);
            }
        }
        else
        {
            const uint32_t arguments[5] = {id, 0, t->user, 0, 0};
            v3_call_guest(&t->thread->cpu, t->callback, 5, arguments, 0);
        }
        if (!(t->flags & TIME_PERIODIC))
        {
            t->active = 0;
        }
    }
}

/* timeSetEvent(delay, resolution, callback, user, flags) */
static void timeSetEvent(Cpu *c)
{
    static uint32_t next_id;
    for (unsigned i = 0; i < TIMERS; ++i)
    {
        Timer *t = &timers[i];
        if (t->active)
        {
            continue;
        }
        t->id = ++next_id;
        t->delay = ARG(0);
        t->callback = ARG(2);
        t->user = ARG(3);
        t->flags = ARG(4);
        t->active = 1;
        t->thread = v3_thread_create(0, 0, 0x40000);
        v3_log("timeSetEvent(%u ms, callback %08x, flags %x) -> %u", t->delay, t->callback,
               t->flags, t->id);
        if (!t->thread || !v3_thread_start(timer_run, t, 1))
        {
            t->active = 0;
            STDCALL_RETURN(5, 0);
        }
        STDCALL_RETURN(5, t->id);
    }
    STDCALL_RETURN(5, 0);
}

static void timeKillEvent(Cpu *c)
{
    for (unsigned i = 0; i < TIMERS; ++i)
    {
        if (timers[i].active && timers[i].id == ARG(0))
        {
            timers[i].active = 0;
            STDCALL_RETURN(1, 0);
        }
    }
    STDCALL_RETURN(1, 97); /* MMSYSERR_INVALPARAM */
}

const V3Export v3_winmm[] = {{"timeGetTime", timeGetTime},
                             {"timeBeginPeriod", timeBeginPeriod},
                             {"timeEndPeriod", timeEndPeriod},
                             {"timeGetDevCaps", timeGetDevCaps},
                             {"timeSetEvent", timeSetEvent},
                             {"timeKillEvent", timeKillEvent},
                             {"waveOutGetNumDevs", waveOutGetNumDevs},
                             {"waveOutGetDevCapsA", waveOutGetDevCapsA},
                             {"waveOutOpen", waveOutOpen},
                             {"waveOutPrepareHeader", waveOutPrepareHeader},
                             {"waveOutUnprepareHeader", waveOutUnprepareHeader},
                             {"waveOutWrite", waveOutWrite},
                             {"waveOutReset", waveOutReset},
                             {"waveOutClose", waveOutClose},
                             {NULL, NULL}};
