#include "timer.h"

/* Original 0x004b7d10. Equal/backward/wrapped clock samples yield zero;
 * advance the baseline even in that case. Long intervals cap at 65535. */
void vertrix_frame_sample(VertrixFrameClock *clock, uint32_t now)
{
    uint32_t elapsed = now > clock->previous ? now - clock->previous : 0;
    clock->current = now;
    clock->previous = now;
    clock->elapsed = elapsed >= 65535 ? 65535 : elapsed;
}

/* Original timer families 0x004ac500..0x004ac5f3 and
 * 0x004ac600..0x004ac6f3. Elapsed input is original global +0x5bd834. */
void vertrix_timer_advance(VertrixTimer *timer, uint32_t elapsed)
{
    timer->counter += elapsed;
}

int vertrix_timer_due(const VertrixTimer *timer)
{
    return timer->counter >= timer->period;
}

uint32_t vertrix_timer_cycles(const VertrixTimer *timer)
{
    return timer->counter / (timer->period ? timer->period : 1);
}

/* The multiplication wraps before division, as in the original imul/div. */
uint32_t vertrix_timer_scaled(const VertrixTimer *timer, uint32_t scale)
{
    uint32_t product = timer->counter * scale;
    return product / (timer->period ? timer->period : 1);
}

void vertrix_timer_consume(VertrixTimer *timer)
{
    timer->counter %= timer->period ? timer->period : 1;
}
