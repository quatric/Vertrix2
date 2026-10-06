#include "block_cycle.h"
#include "dword_transition.h"
#include <limits.h>

static int32_t cycle_signed(uint32_t value)
{
    return value <= INT32_MAX ? (int32_t)value : -(int32_t)(UINT32_MAX - value) - 1;
}

int vertrix_block_cycle_update(VertrixAnimation *animation, const uint32_t *frames, size_t storage,
                               uint32_t elapsed, uint32_t *descriptor, VertrixBlockCycle *cycle,
                               VertrixCycleTrace *trace)
{
    if (!animation || !descriptor || !cycle || !trace ||
        (cycle->handler != 0x44f390 && cycle->handler != 0x44f3e0 && cycle->handler != 0x44f430))
    {
        return 0;
    }
    VertrixAnimation next_animation = *animation;
    VertrixBlockCycle next = *cycle;
    VertrixCycleTrace next_trace = *trace;
    uint32_t selected = *descriptor;
    if (!vertrix_block_update(&next_animation, frames, storage, elapsed, &selected))
    {
        return 0;
    }
    if (next.handler != 0x44f430)
    {
        next.field_94 = 0;
    }
    vertrix_timer_advance(&next.timer, elapsed);
    if (vertrix_timer_due(&next.timer))
    {
        uint32_t cycles = vertrix_timer_cycles(&next.timer);
        vertrix_timer_consume(&next.timer);
        if (next.handler == 0x44f430)
        {
            next.target = 0;
            if (!vertrix_dword_transition(&next.current, next.target, next.step, cycles))
            {
                next.current = 0;
                next.field_8c = 0;
                next.handler = 0x44c860;
            }
        }
        else
        {
            int reverse = next.handler == 0x44f3e0;
            next_trace.iterations = 0;
            next_trace.unwrapped = 1;
            for (uint32_t i = 0; i < cycles; ++i)
            {
                uint32_t bits = reverse ? (uint32_t)next.current - (uint32_t)next.step
                                        : (uint32_t)next.current + (uint32_t)next.step;
                next.current = cycle_signed(bits);
                if ((!reverse && next.current >= 255) || (reverse && next.current < 0))
                {
                    bits = reverse ? bits + 255u : bits - 255u;
                    next.current = cycle_signed(bits) % 255;
                    next_trace.unwrapped = 0;
                }
                ++next_trace.iterations;
            }
        }
    }
    *animation = next_animation;
    *cycle = next;
    *trace = next_trace;
    *descriptor = selected;
    return 1;
}
