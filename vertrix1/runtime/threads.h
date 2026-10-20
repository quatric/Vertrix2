#ifndef V3_THREADS_H
#define V3_THREADS_H

/* The DOS machine runs on one host thread: hardware interrupts arrive at safe points of the
 * recompiled code, never concurrently, so vertrix3/runtime/memory.c's heap lock is a no-op. */

static inline void v3_lock(void)
{
}

static inline void v3_unlock(void)
{
}

#endif
