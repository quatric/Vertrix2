#include "block_period.h"
#include <limits.h>

static int32_t period_signed(uint32_t value)
{
    return value <= INT32_MAX ? (int32_t)value : -(int32_t)(UINT32_MAX - value) - 1;
}

int vertrix_block_period_update(VertrixAnimation *animation, const uint32_t *frames, size_t storage,
                                uint32_t elapsed, uint32_t *descriptor, VertrixBlockPeriod *period)
{
    if (!animation || !descriptor || !period || period->handler != 0x44e890)
    {
        return 0;
    }
    VertrixAnimation next_animation = *animation;
    VertrixBlockPeriod next = *period;
    uint32_t selected = *descriptor;
    if (!vertrix_block_update(&next_animation, frames, storage, elapsed, &selected))
    {
        return 0;
    }
    vertrix_timer_advance(&next.timer, elapsed);
    if (vertrix_timer_due(&next.timer))
    {
        uint32_t cycles = vertrix_timer_cycles(&next.timer);
        vertrix_timer_consume(&next.timer);
        int32_t speed = period_signed(next_animation.timer.period) / 12;
        if (speed < next.target)
        {
            speed = period_signed((uint32_t)speed + cycles);
            if (speed > next.target)
            {
                speed = next.target;
            }
            next_animation.timer.period = (uint32_t)speed * 12u;
        }
        else
        {
            speed = next.target;
        }
        if (speed == next.target)
        {
            next.handler = 0x44c860;
        }
    }
    *animation = next_animation;
    *period = next;
    *descriptor = selected;
    return 1;
}
