#include "block_half_pulse.h"
#include <limits.h>

static int32_t half_signed(uint32_t bits)
{
    return bits <= INT32_MAX ? (int32_t)bits : -(int32_t)(UINT32_MAX - bits) - 1;
}

int vertrix_block_half_pulse_update(VertrixAnimation *animation, const uint32_t *frames,
                                    size_t storage, uint32_t elapsed, uint32_t *descriptor,
                                    VertrixBlockHalfPulse *pulse)
{
    if (!pulse || (pulse->mode.handler != 0x44da70 && pulse->mode.handler != 0x44db10))
    {
        return 0;
    }
    VertrixBlockHalfPulse next = *pulse;
    VertrixTimer timer = next.mode.timer;
    vertrix_timer_advance(&timer, elapsed);
    if (vertrix_timer_due(&timer))
    {
        uint32_t distance = vertrix_timer_cycles(&timer) * 10u;
        next.amount_target = 50;
        next.amount_step = 10;
        int32_t value = next.amount;
        if (next.amount > 50)
        {
            value = half_signed((uint32_t)next.amount - distance);
            if (value < 50)
            {
                value = 50;
            }
        }
        else if (next.amount < 50)
        {
            value = half_signed((uint32_t)next.amount + distance);
            if (value > 50)
            {
                value = 50;
            }
        }
        next.amount = (uint8_t)value;
    }
    next.mode.handler = next.mode.handler == 0x44da70 ? 0x44d940 : 0x44d8b0;
    if (!vertrix_block_mode_pulse_update(animation, frames, storage, elapsed, descriptor,
                                         &next.mode))
    {
        return 0;
    }
    if (next.mode.handler != 0x44c860)
    {
        next.mode.handler = next.mode.handler == 0x44d940 ? 0x44da70 : 0x44db10;
    }
    *pulse = next;
    return 1;
}
