/* Vertrix 3 recompiled, on the build machine: runs the game with no window, writing presented
 * frames as PPM files and the log to stderr.
 *
 * usage: v3_host IMAGE GAME_DIRECTORY OUT_DIR [seconds] [frame_every] [-options] */
#include "runtime.h"

#include <pthread.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

static const char *out_dir;
static unsigned frame_every = 30;
static unsigned frames;
static double seconds = 20;
static uint64_t started;

uint64_t v3_microseconds(void)
{
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    const uint64_t now = (uint64_t)ts.tv_sec * 1000000u + (uint64_t)ts.tv_nsec / 1000u;
    if (!started)
    {
        started = now;
    }
    return now - started + 1000000u;
}

void v3_sleep_ms(uint32_t ms)
{
    usleep(ms * 1000u);
}

void v3_log(const char *format, ...)
{
    va_list args;
    va_start(args, format);
    fprintf(stderr, "[%7.3f] ", (double)(v3_microseconds() - 1000000u) / 1e6);
    vfprintf(stderr, format, args);
    fputc('\n', stderr);
    va_end(args);
}

_Noreturn void v3_fatal(const char *format, ...)
{
    va_list args;
    va_start(args, format);
    fprintf(stderr, "FATAL: ");
    vfprintf(stderr, format, args);
    fputc('\n', stderr);
    va_end(args);
    exit(2);
}

static void present(const V3Frame *frame)
{
    ++frames;
    if (frame_every == 0 || frames % frame_every != 0)
    {
        return;
    }
    char path[512];
    snprintf(path, sizeof path, "%s/frame%05u.ppm", out_dir, frames);
    FILE *f = fopen(path, "wb");
    if (!f)
    {
        return;
    }
    fprintf(f, "P6\n%u %u\n255\n", frame->width, frame->height);
    for (uint32_t i = 0; i < frame->width * frame->height; ++i)
    {
        const uint32_t p = frame->pixels[i];
        const uint8_t rgb[3] = {(uint8_t)(p >> 16), (uint8_t)(p >> 8), (uint8_t)p};
        fwrite(rgb, 1, 3, f);
    }
    fclose(f);
}

/* V3_SCRIPT: timed input, `;`-separated steps of `SECONDS key SCAN DOWN`, `SECONDS move DX DY`
 * or `SECONDS button N DOWN`, e.g. "3 move 260 172; 3.5 button 0 1; 3.6 button 0 0". */
static const char *script;

static void run_script(double now)
{
    while (script && *script)
    {
        double at;
        char kind[16];
        int a = 0, b = 0, used = 0;
        if (sscanf(script, " %lf %15s %d %d%n", &at, kind, &a, &b, &used) < 4 || at > now)
        {
            return;
        }
        if (!strcmp(kind, "key"))
        {
            v3_input_key((unsigned)a, b);
        }
        else if (!strcmp(kind, "move"))
        {
            v3_input_mouse_move(a, b);
        }
        else if (!strcmp(kind, "button"))
        {
            v3_input_mouse_button((unsigned)a, b);
        }
        v3_log("script: %s %d %d", kind, a, b);
        script += used;
        while (*script == ' ' || *script == ';')
        {
            ++script;
        }
        /* One step per poll: the game adds up a poll's mouse motion before clamping. */
        return;
    }
}

static int poll_input(void)
{
    const double now = (double)(v3_microseconds() - 1000000u) / 1e6;
    run_script(now);
    return now > seconds;
}

static uint64_t wave_bytes, wave_rate_bytes;
static uint64_t wave_start;

static void wave_open(uint32_t rate, uint32_t channels, uint32_t bits)
{
    wave_rate_bytes = (uint64_t)rate * channels * bits / 8u;
    wave_start = v3_microseconds();
}

static void wave_write(const uint8_t *samples, uint32_t bytes)
{
    (void)samples;
    wave_bytes += bytes;
}

static uint64_t wave_played(void)
{
    const uint64_t elapsed = (v3_microseconds() - wave_start) * wave_rate_bytes / 1000000u;
    return elapsed < wave_bytes ? elapsed : wave_bytes;
}

typedef struct
{
    uint8_t *image;
    long size;
    const char *options;
    V3Platform platform;
} Run;

static void *game(void *p)
{
    Run *r = p;
    const int code = v3_run(r->image, (uint32_t)r->size, r->options, &r->platform);
    v3_log("game exited with %d after %u frames", code, frames);
    exit(code);
}

/* A fault inside the guest space: say where, and what the game was doing. */
static void on_fault(int signal, siginfo_t *info, void *context)
{
    (void)context;
    const uintptr_t at = (uintptr_t)info->si_addr;
    const uintptr_t base = (uintptr_t)v3_memory;
    if (at >= base && at - base < ((uintptr_t)1 << 32))
    {
        v3_log("signal %d: guest address %08x", signal, (unsigned)(at - base));
    }
    else
    {
        v3_log("signal %d: host address %p", signal, info->si_addr);
    }
    v3_history_dump(64);
    _exit(128 + signal);
}

int main(int argc, char **argv)
{
    struct sigaction action = {0};
    action.sa_sigaction = on_fault;
    action.sa_flags = SA_SIGINFO | SA_ONSTACK;
    sigaction(SIGSEGV, &action, NULL);
    sigaction(SIGBUS, &action, NULL);
    if (argc < 4)
    {
        fprintf(stderr, "usage: v3_host IMAGE GAME_DIRECTORY OUT_DIR [seconds] [frame_every] "
                        "[-options]\n");
        return 2;
    }
    static Run run;
    FILE *f = fopen(argv[1], "rb");
    if (!f)
    {
        perror(argv[1]);
        return 1;
    }
    fseek(f, 0, SEEK_END);
    run.size = ftell(f);
    fseek(f, 0, SEEK_SET);
    run.image = malloc((size_t)run.size);
    if (fread(run.image, 1, (size_t)run.size, f) != (size_t)run.size)
    {
        return 1;
    }
    fclose(f);
    out_dir = argv[3];
    if (argc > 4)
    {
        seconds = atof(argv[4]);
    }
    if (argc > 5)
    {
        frame_every = (unsigned)atoi(argv[5]);
    }
    run.options = argc > 6 ? "-options" : NULL;
    script = getenv("V3_SCRIPT");
    if (getenv("V3_TRACE"))
    {
        v3_trace_calls = 1;
    }
    if (getenv("V3_WATCH"))
    {
        extern uint32_t v3_watch;
        v3_watch = (uint32_t)strtoul(getenv("V3_WATCH"), NULL, 16);
    }
    if (getenv("V3_TRACE_D3D"))
    {
        extern int v3_trace_d3d;
        v3_trace_d3d = 1;
    }
    run.platform.directory = argv[2];
    run.platform.present = present;
    run.platform.poll = poll_input;
    run.platform.wave_open = wave_open;
    run.platform.wave_write = wave_write;
    run.platform.wave_played = wave_played;
    pthread_t t;
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setstacksize(&attr, 256u << 20);
    pthread_create(&t, &attr, game, &run);
    pthread_join(t, NULL);
    return 0;
}
