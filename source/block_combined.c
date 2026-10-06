#include "block_combined.h"
#include <limits.h>

static int32_t combined_signed(uint32_t value)
{
    return value <= INT32_MAX ? (int32_t)value : -(int32_t)(UINT32_MAX - value) - 1;
}

static uint32_t combined_transition(int32_t current, int32_t target, int16_t step, uint32_t cycles)
{
    uint32_t distance = cycles * (uint32_t)(int32_t)step;
    int32_t result = current;
    if (current > target)
    {
        result = combined_signed((uint32_t)current - distance);
        if (result < target)
        {
            result = target;
        }
    }
    else if (current < target)
    {
        result = combined_signed((uint32_t)current + distance);
        if (result > target)
        {
            result = target;
        }
    }
    return (uint32_t)result;
}

int vertrix_block_combined_update(VertrixAnimation *animation, const uint32_t *frames,
                                  size_t frame_storage, uint32_t elapsed, uint32_t *descriptor,
                                  VertrixBlockCombined *combined)
{
    if (!animation || !descriptor || !combined ||
        (combined->handler != 0x44cab0 && combined->handler != 0x44cb50 &&
         combined->handler != 0x44f7e0 && combined->handler != 0x44f880))
    {
        return 0;
    }
    VertrixAnimation next_animation = *animation;
    VertrixBlockCombined next = *combined;
    uint32_t selected = *descriptor;
    if (!vertrix_block_update(&next_animation, frames, frame_storage, elapsed, &selected))
    {
        return 0;
    }
    next.field_93 = 1;
    next.field_95 = 3;
    vertrix_timer_advance(&next.timer, elapsed);
    if (vertrix_timer_due(&next.timer))
    {
        uint32_t cycles = vertrix_timer_cycles(&next.timer);
        vertrix_timer_consume(&next.timer);
        int hide = next.handler == 0x44f7e0;
        int reveal = next.handler == 0x44f880;
        next.amount_target = (next.handler == 0x44cab0 || reveal) ? 100 : 0;
        next.amount_step = reveal ? 4 : 8;
        next.amount =
            (uint8_t)combined_transition(next.amount, next.amount_target, next.amount_step, cycles);
        next.effect_target = hide ? -100 : (next.handler == 0x44cab0 ? 0 : 100);
        next.effect_step = reveal ? 4 : (next.handler == 0x44cab0 ? 16 : 8);
        uint32_t word = (uint16_t)combined_transition(next.effect, next.effect_target,
                                                      next.effect_step, cycles);
        next.effect = (int16_t)(word < 32768 ? (int32_t)word : (int32_t)word - 65536);
        if (next.amount == next.amount_target && next.effect == next.effect_target)
        {
            next.handler = reveal ? 0x44f920 : 0x44c860;
            if (reveal)
            {
                next.field_95 = 1;
            }
        }
    }
    *animation = next_animation;
    *combined = next;
    *descriptor = selected;
    return 1;
}
