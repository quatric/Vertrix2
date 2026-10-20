#ifndef V3_THREADS_H
#define V3_THREADS_H

/* Host threads and waits behind the Windows threads, events, mutexes and critical sections the
 * game uses (threads_posix.c on the build machine, threads_wii.c on the Wii). */

#include <stdint.h>

/* One lock around host bookkeeping (heap, handles); recursive. */
void v3_lock(void);
void v3_unlock(void);

typedef struct V3Event V3Event;
V3Event *v3_event_create(int manual_reset, int initial);
void v3_event_set(V3Event *event);
void v3_event_reset(V3Event *event);
/* Wait for one (all = 0) or all of `count` events; returns the index of a signalled one, or -1
 * on timeout. timeout_ms 0xffffffff waits forever. Auto-reset events are reset by the wait. */
int v3_event_wait(V3Event **events, unsigned count, int all, uint32_t timeout_ms);

typedef struct V3Mutex V3Mutex;
V3Mutex *v3_mutex_create(void);
void v3_mutex_lock(V3Mutex *mutex);
int v3_mutex_try_lock(V3Mutex *mutex);
void v3_mutex_unlock(V3Mutex *mutex);

/* Start a host thread running `entry(argument)`; nonzero on success. */
int v3_thread_start(void (*entry)(void *), void *argument, int priority);
/* The calling host thread's own pointer (set by the thread itself). */
void v3_thread_set_self(void *self);
void *v3_thread_self(void);
void v3_yield(void);

#endif
