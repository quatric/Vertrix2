#include "threads.h"
#include "runtime.h"

#include <errno.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>

#ifdef __WIIU__
#include <coreinit/thread.h>
#endif

/* A host thread's stack: 8 MB, less on the consoles (the Wii's threads have 512 KB). */
#ifndef V3_HOST_THREAD_STACK
#define V3_HOST_THREAD_STACK (8u << 20)
#endif

static pthread_mutex_t big_lock;
static pthread_once_t big_once = PTHREAD_ONCE_INIT;

static void big_init(void)
{
    pthread_mutexattr_t attr;
    pthread_mutexattr_init(&attr);
    pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
    pthread_mutex_init(&big_lock, &attr);
}

void v3_lock(void)
{
    pthread_once(&big_once, big_init);
    pthread_mutex_lock(&big_lock);
}

void v3_unlock(void)
{
    pthread_mutex_unlock(&big_lock);
}

/* All events share one mutex and condition: a wait for several is then one predicate. */
static pthread_mutex_t event_lock = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t event_changed = PTHREAD_COND_INITIALIZER;

struct V3Event
{
    int manual;
    int signalled;
};

V3Event *v3_event_create(int manual_reset, int initial)
{
    V3Event *e = calloc(1, sizeof *e);
    e->manual = manual_reset;
    e->signalled = initial;
    return e;
}

void v3_event_set(V3Event *e)
{
    pthread_mutex_lock(&event_lock);
    e->signalled = 1;
    pthread_cond_broadcast(&event_changed);
    pthread_mutex_unlock(&event_lock);
}

void v3_event_reset(V3Event *e)
{
    pthread_mutex_lock(&event_lock);
    e->signalled = 0;
    pthread_mutex_unlock(&event_lock);
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
    struct timespec until;
    struct timeval now;
    gettimeofday(&now, NULL);
    uint64_t ns = (uint64_t)now.tv_usec * 1000u + (uint64_t)timeout_ms * 1000000u;
    until.tv_sec = now.tv_sec + (time_t)(ns / 1000000000u);
    until.tv_nsec = (long)(ns % 1000000000u);
    pthread_mutex_lock(&event_lock);
    int got;
    while ((got = ready(events, count, all)) < 0)
    {
        if (timeout_ms == 0)
        {
            break;
        }
        if (timeout_ms == 0xffffffffu)
        {
            pthread_cond_wait(&event_changed, &event_lock);
        }
#ifdef __WIIU__
        /* wut's timed wait leaves an alarm that can fire after the wait returned (it crashed
         * Cemu in OSFastCond_Signal): the events are polled every millisecond instead. */
        else
        {
            pthread_mutex_unlock(&event_lock);
            usleep(1000);
            pthread_mutex_lock(&event_lock);
            gettimeofday(&now, NULL);
            if (now.tv_sec > until.tv_sec ||
                (now.tv_sec == until.tv_sec && now.tv_usec * 1000L >= until.tv_nsec))
            {
                got = ready(events, count, all);
                break;
            }
        }
#else
        else if (pthread_cond_timedwait(&event_changed, &event_lock, &until) == ETIMEDOUT)
        {
            got = ready(events, count, all);
            break;
        }
#endif
    }
    pthread_mutex_unlock(&event_lock);
    return got;
}

struct V3Mutex
{
    pthread_mutex_t mutex;
};

V3Mutex *v3_mutex_create(void)
{
    V3Mutex *m = calloc(1, sizeof *m);
    pthread_mutexattr_t attr;
    pthread_mutexattr_init(&attr);
    pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
    pthread_mutex_init(&m->mutex, &attr);
    return m;
}

void v3_mutex_lock(V3Mutex *m)
{
    pthread_mutex_lock(&m->mutex);
}

int v3_mutex_try_lock(V3Mutex *m)
{
    return pthread_mutex_trylock(&m->mutex) == 0;
}

void v3_mutex_unlock(V3Mutex *m)
{
    pthread_mutex_unlock(&m->mutex);
}

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
    (void)priority;
    pthread_t t;
    Start *s = malloc(sizeof *s);
    s->entry = entry;
    s->argument = argument;
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setstacksize(&attr, V3_HOST_THREAD_STACK);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    const int ok = pthread_create(&t, &attr, start, s) == 0;
    pthread_attr_destroy(&attr);
    return ok;
}

#ifdef __WIIU__
/* An RPX has no thread-local storage (elf2rpl refuses its relocations), and newlib's pthread
 * keys did not keep the value under wut: coreinit's first application slot instead. */
void v3_thread_set_self(void *p)
{
    OSSetThreadSpecific(OS_THREAD_SPECIFIC_0, p);
}

void *v3_thread_self(void)
{
    return OSGetThreadSpecific(OS_THREAD_SPECIFIC_0);
}
#else
static __thread void *self;

void v3_thread_set_self(void *p)
{
    self = p;
}

void *v3_thread_self(void)
{
    return self;
}
#endif

void v3_yield(void)
{
    sched_yield();
}
