#ifndef VERTRIX_TIMER_H
#define VERTRIX_TIMER_H

#include <stdint.h>

typedef struct
{
    uint32_t counter;
    uint32_t period;
} VertrixTimer;

typedef struct
{
    uint32_t previous;
    uint32_t current;
    uint32_t elapsed;
} VertrixFrameClock;

/* Input is the original unsigned millisecond clock sample. */
void vertrix_frame_sample(VertrixFrameClock *clock, uint32_t now);

void vertrix_timer_advance(VertrixTimer *timer, uint32_t elapsed);
int vertrix_timer_due(const VertrixTimer *timer);
uint32_t vertrix_timer_cycles(const VertrixTimer *timer);
uint32_t vertrix_timer_scaled(const VertrixTimer *timer, uint32_t scale);
void vertrix_timer_consume(VertrixTimer *timer);

#endif
