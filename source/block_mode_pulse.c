#include "block_mode_pulse.h"
#include <limits.h>

static int32_t mode_signed(uint32_t bits)
{
    return bits <= INT32_MAX ? (int32_t)bits : -(int32_t)(UINT32_MAX - bits) - 1;
}

int vertrix_block_mode_pulse_update(VertrixAnimation *animation, const uint32_t *frames,
                                    size_t storage, uint32_t elapsed, uint32_t *descriptor,
                                    VertrixBlockModePulse *pulse)
{
    if (!animation || !descriptor || !pulse ||
        (pulse->handler != 0x44d8b0 && pulse->handler != 0x44d940))
    {
        return 0;
    }
    VertrixAnimation next_animation = *animation;
    VertrixBlockModePulse next = *pulse;
    uint32_t selected = *descriptor;
    if (!vertrix_block_update(&next_animation, frames, storage, elapsed, &selected))
    {
        return 0;
    }
    next.field_95 = 3;
    vertrix_timer_advance(&next.timer, elapsed);
    if (vertrix_timer_due(&next.timer))
    {
        uint32_t cycles = vertrix_timer_cycles(&next.timer);
        vertrix_timer_consume(&next.timer);
        next.target = next.handler == 0x44d8b0 ? 0 : 16;
        next.step = 1;
        next.age += cycles;
        int32_t value = next.current;
        if (next.current > next.target)
        {
            value = mode_signed((uint32_t)next.current - cycles);
            if (value < next.target)
            {
                value = next.target;
            }
        }
        else if (next.current < next.target)
        {
            value = mode_signed((uint32_t)next.current + cycles);
            if (value > next.target)
            {
                value = next.target;
            }
        }
        next.current = (uint8_t)value;
        if (next.current == next.target)
        {
            next.handler = next.handler == 0x44d8b0 ? 0x44d940 : 0x44d8b0;
        }
        if (mode_signed(next.age) >= 30)
        {
            next.handler = 0x44c860;
        }
    }
    *animation = next_animation;
    *pulse = next;
    *descriptor = selected;
    return 1;
}
