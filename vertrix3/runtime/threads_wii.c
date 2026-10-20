/* threads.h on the Wii: libogc's LWP threads, mutexes and condition variables. As on the build
 * machine, all events share one mutex and condition, so a wait for several is one predicate. */
#include "threads.h"
#include "runtime.h"

#include <gccore.h>
#include <malloc.h>
#include <ogc/cond.h>
#include <ogc/lwp_watchdog.h>
#include <ogc/mutex.h>
#include <stdlib.h>

static mutex_t big_lock = LWP_MUTEX_NULL;
static mutex_t event_lock = LWP_MUTEX_NULL;
static cond_t event_changed = LWP_COND_NULL;

/* The first call comes from the main thread before any other thread exists. */
static void init_once(void)
{
    if (big_lock == LWP_MUTEX_NULL)
    {
        LWP_MutexInit(&big_lock, true);
        LWP_MutexInit(&event_lock, false);
        LWP_CondInit(&event_changed);
    }
}

void v3_lock(void)
{
    init_once();
    LWP_MutexLock(big_lock);
}

void v3_unlock(void)
{
    LWP_MutexUnlock(big_lock);
}

struct V3Event
{
    int manual;
    int signalled;
};

V3Event *v3_event_create(int manual_reset, int initial)
{
    init_once();
    V3Event *e = calloc(1, sizeof *e);
    e->manual = manual_reset;
    e->signalled = initial;
    return e;
}

void v3_event_set(V3Event *e)
{
    LWP_MutexLock(event_lock);
    e->signalled = 1;
    LWP_CondBroadcast(event_changed);
    LWP_MutexUnlock(event_lock);
}

void v3_event_reset(V3Event *e)
{
    LWP_MutexLock(event_lock);
    e->signalled = 0;
    LWP_MutexUnlock(event_lock);
}

static int ready(V3Event **events, unsigned count, int all)
{
    if (all)
    {
        for (unsigned i = 0; i < count; ++i)
        {
            if (!events[i]->signalled)
            {
                return -1;
            }
        }
        for (unsigned i = 0; i < count; ++i)
        {
            if (!events[i]->manual)
            {
                events[i]->signalled = 0;
            }
        }
        return 0;
    }
    for (unsigned i = 0; i < count; ++i)
    {
        if (events[i]->signalled)
        {
            if (!events[i]->manual)
            {
                events[i]->signalled = 0;
            }
            return (int)i;
        }
    }
    return -1;
}

int v3_event_wait(V3Event **events, unsigned count, int all, uint32_t timeout_ms)
{
    const uint64_t until = v3_microseconds() + (uint64_t)timeout_ms * 1000u;
    LWP_MutexLock(event_lock);
    int got;
    while ((got = ready(events, count, all)) < 0)
    {
        if (timeout_ms == 0)
        {
            break;
        }
        if (timeout_ms == 0xffffffffu)
        {
            LWP_CondWait(event_changed, event_lock);
            continue;
        }
        const uint64_t now = v3_microseconds();
        if (now >= until)
        {
            break;
        }
        const uint64_t left = until - now;
        struct timespec span = {(time_t)(left / 1000000u), (long)(left % 1000000u) * 1000};
        LWP_CondTimedWait(event_changed, event_lock, &span);
    }
    LWP_MutexUnlock(event_lock);
    return got;
}

struct V3Mutex
{
    mutex_t mutex;
};

V3Mutex *v3_mutex_create(void)
{
    V3Mutex *m = calloc(1, sizeof *m);
    LWP_MutexInit(&m->mutex, true);
    return m;
}

void v3_mutex_lock(V3Mutex *m)
{
    LWP_MutexLock(m->mutex);
}

int v3_mutex_try_lock(V3Mutex *m)
{
    return LWP_MutexTryLock(m->mutex) == 0;
}

void v3_mutex_unlock(V3Mutex *m)
{
    LWP_MutexUnlock(m->mutex);
}

/* Each thread's own pointer, found by its LWP handle. */
enum
{
    THREADS = 64,
    HOST_STACK = 512 * 1024
};

static struct
{
    lwp_t thread;
    void *self;
} selves[THREADS];

typedef struct
{
    void (*entry)(void *);
    void *argument;
} Start;

static void *start(void *p)
{
    Start s = *(Start *)p;
    free(p);
    s.entry(s.argument);
    return NULL;
}

int v3_thread_start(void (*entry)(void *), void *argument, int priority)
{
    Start *s = malloc(sizeof *s);
    s->entry = entry;
    s->argument = argument;
    /* The game's threads (input, sound) run a little above its main loop, as their waits are
     * short; Windows' THREAD_PRIORITY_* maps around LWP's 64. */
    int lwp_priority = 64 + priority * 4;
    if (lwp_priority < 1)
    {
        lwp_priority = 1;
    }
    if (lwp_priority > 120)
    {
        lwp_priority = 120;
    }
    lwp_t thread;
    void *stack = memalign(32, HOST_STACK);
    return LWP_CreateThread(&thread, start, s, stack, HOST_STACK, (u8)lwp_priority) == 0;
}

void v3_thread_set_self(void *p)
{
    const lwp_t me = LWP_GetSelf();
    v3_lock();
    for (unsigned i = 0; i < THREADS; ++i)
    {
        if (selves[i].thread == me || !selves[i].self)
        {
            selves[i].thread = me;
            selves[i].self = p;
            break;
        }
    }
    v3_unlock();
}

void *v3_thread_self(void)
{
    const lwp_t me = LWP_GetSelf();
    for (unsigned i = 0; i < THREADS; ++i)
    {
        if (selves[i].self && selves[i].thread == me)
        {
            return selves[i].self;
        }
    }
    return NULL;
}

void v3_yield(void)
{
    LWP_YieldThread();
}
