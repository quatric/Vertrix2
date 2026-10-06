#include "block_staged.h"
#include <limits.h>

static int32_t staged_signed(uint32_t value)
{
    return value <= INT32_MAX ? (int32_t)value : -(int32_t)(UINT32_MAX - value) - 1;
}

static uint32_t staged_transition(int32_t current, int32_t target, int16_t step, uint32_t cycles)
{
    uint32_t distance = cycles * (uint32_t)(int32_t)step;
    int32_t result = current;
    if (current > target)
    {
        result = staged_signed((uint32_t)current - distance);
        if (result < target)
        {
            result = target;
        }
    }
    else if (current < target)
    {
        result = staged_signed((uint32_t)current + distance);
        if (result > target)
        {
            result = target;
        }
    }
    return (uint32_t)result;
}

int vertrix_block_staged_update(VertrixAnimation *animation, const uint32_t *frames,
                                size_t frame_storage, uint32_t elapsed, uint32_t *descriptor,
                                VertrixBlockStaged *combined)
{
    if (!animation || !descriptor || !combined || combined->handler != 0x44dbb0)
    {
        return 0;
    }
    VertrixAnimation next_animation = *animation;
    VertrixBlockStaged next = *combined;
    uint32_t selected = *descriptor;
    if (!vertrix_block_update(&next_animation, frames, frame_storage, elapsed, &selected))
    {
        return 0;
    }
    next.field_95 = 4;
    vertrix_timer_advance(&next.timer, elapsed);
    if (vertrix_timer_due(&next.timer))
    {
        uint32_t cycles = vertrix_timer_cycles(&next.timer);
        vertrix_timer_consume(&next.timer);
        next.mode_target = 16;
        next.mode_step = 1;
        next.mode = (uint8_t)staged_transition(next.mode, next.mode_target, next.mode_step, cycles);
        next.amount_target = 0;
        next.amount_step = 4;
        next.amount =
            (uint8_t)staged_transition(next.amount, next.amount_target, next.amount_step, cycles);
        next.effect_target = 50;
        next.effect_step = 5;
        uint32_t word =
            (uint16_t)staged_transition(next.effect, next.effect_target, next.effect_step, cycles);
        next.effect = (int16_t)(word < 32768 ? (int32_t)word : (int32_t)word - 65536);
        if (next.effect >= 15)
        {
            next.stage = 1;
        }
        if (next.effect >= 30)
        {
            next.stage = 2;
        }
        if (next.effect == 50)
        {
            next.stage = 3;
        }
        if (next.amount == next.amount_target)
        {
            next.handler = 0x44dc80;
        }
    }
    *animation = next_animation;
    *combined = next;
    *descriptor = selected;
    return 1;
}
