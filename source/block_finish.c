#include "block_finish.h"
#include <limits.h>

static uint8_t finish_byte(uint8_t current, uint8_t target, uint32_t distance)
{
    if (current == target)
    {
        return current;
    }
    uint32_t bits = current > target ? (uint32_t)current - distance : (uint32_t)current + distance;
    int32_t value = bits <= INT32_MAX ? (int32_t)bits : -(int32_t)(UINT32_MAX - bits) - 1;
    if ((current > target && value < target) || (current < target && value > target))
    {
        value = target;
    }
    return (uint8_t)value;
}

int vertrix_block_finish_update(VertrixAnimation *animation, const uint32_t *frames,
                                size_t frame_storage, uint32_t elapsed, uint32_t *descriptor,
                                VertrixBlockFinish *finish)
{
    if (!animation || !descriptor || !finish ||
        (finish->handler != 0x44d560 && finish->handler != 0x44d6d0))
    {
        return 0;
    }
    VertrixAnimation next_animation = *animation;
    VertrixBlockFinish next = *finish;
    uint32_t selected = *descriptor;
    if (!vertrix_block_update(&next_animation, frames, frame_storage, elapsed, &selected))
    {
        return 0;
    }
    next.field_93 = next.handler == 0x44d6d0 ? 1 : 0;
    if (next.handler == 0x44d6d0)
    {
        next.amount = 80;
    }
    vertrix_timer_advance(&next.timer, elapsed);
    if (vertrix_timer_due(&next.timer))
    {
        uint32_t cycles = vertrix_timer_cycles(&next.timer);
        vertrix_timer_consume(&next.timer);
        next.amount_target = next.handler == 0x44d6d0 ? 80 : 0;
        next.amount_step = 8;
        next.amount = finish_byte(next.amount, next.amount_target, cycles * 8u);
        next.mode_target = next.handler == 0x44d6d0 ? 16 : 0;
        next.mode_step = 1;
        next.mode = finish_byte(next.mode, next.mode_target, cycles);
        if (next.amount == next.amount_target && next.mode == next.mode_target)
        {
            next.handler = next.handler == 0x44d6d0 ? 0x44d760 : 0x44c860;
        }
    }
    *animation = next_animation;
    *finish = next;
    *descriptor = selected;
    return 1;
}
