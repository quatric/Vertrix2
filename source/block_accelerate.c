#include "block_accelerate.h"
#include "word_transition.h"
#include <limits.h>

static int32_t accelerate_signed(uint32_t value)
{
    return value <= INT32_MAX ? (int32_t)value : -(int32_t)(UINT32_MAX - value) - 1;
}

int vertrix_block_accelerate_update(VertrixAnimation *animation, const uint32_t *frames,
                                    size_t storage, uint32_t elapsed, uint32_t *descriptor,
                                    VertrixBlockAccelerate *accelerate)
{
    if (!animation || !descriptor || !accelerate || accelerate->handler != 0x44e6e0)
    {
        return 0;
    }
    VertrixAnimation next_animation = *animation;
    VertrixBlockAccelerate next = *accelerate;
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
        int32_t speed = accelerate_signed(next_animation.timer.period) / 12;
        if (speed > 1)
        {
            speed = accelerate_signed((uint32_t)speed - cycles);
            if (speed < 1)
            {
                speed = 1;
            }
            next_animation.timer.period = (uint32_t)speed * 12u;
        }
        else
        {
            speed = 1;
        }
        next.target = 50;
        next.step = 2;
        if (!vertrix_word_transition(&next.effect, next.target, next.step, cycles) && speed == 1)
        {
            next.handler = 0x44c860;
        }
    }
    *animation = next_animation;
    *accelerate = next;
    *descriptor = selected;
    return 1;
}
