#include "block_byte_pulse.h"
#include <limits.h>

static int32_t pulse_signed(uint32_t value)
{
    return value <= INT32_MAX ? (int32_t)value : -(int32_t)(UINT32_MAX - value) - 1;
}

int vertrix_block_byte_pulse_update(VertrixAnimation *animation, const uint32_t *frames,
                                    size_t frame_storage, uint32_t elapsed, uint32_t *descriptor,
                                    VertrixBlockFade *pulse)
{
    if (!animation || !descriptor || !pulse ||
        (pulse->handler != 0x44cbf0 && pulse->handler != 0x44cc60 && pulse->handler != 0x44d410 &&
         pulse->handler != 0x44d760))
    {
        return 0;
    }
    VertrixAnimation next_animation = *animation;
    VertrixBlockFade next = *pulse;
    uint32_t selected = *descriptor;
    if (!vertrix_block_update(&next_animation, frames, frame_storage, elapsed, &selected))
    {
        return 0;
    }
    next.field_93 = 1;
    vertrix_timer_advance(&next.timer, elapsed);
    if (vertrix_timer_due(&next.timer))
    {
        uint32_t cycles = vertrix_timer_cycles(&next.timer);
        vertrix_timer_consume(&next.timer);
        next.target = next.handler == 0x44cc60 ? 0 : 100;
        next.step = (next.handler == 0x44d410 || next.handler == 0x44d760) ? 8 : 5;
        int32_t position = next.current;
        uint32_t distance = cycles * (uint32_t)next.step;
        if (position > next.target)
        {
            position = pulse_signed((uint32_t)position - distance);
            if (position < next.target)
            {
                position = next.target;
            }
        }
        else if (position < next.target)
        {
            position = pulse_signed((uint32_t)position + distance);
            if (position > next.target)
            {
                position = next.target;
            }
        }
        next.current = (uint8_t)position;
        if (next.current == next.target)
        {
            next.handler =
                next.handler == 0x44d760
                    ? 0x44d7d0
                    : (next.handler == 0x44d410 ? 0x44c860
                                                : (next.handler == 0x44cbf0 ? 0x44cc60 : 0x44cbf0));
        }
    }
    *animation = next_animation;
    *pulse = next;
    *descriptor = selected;
    return 1;
}
