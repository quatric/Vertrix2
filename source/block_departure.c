#include "block_departure.h"
#include <limits.h>

static int32_t departure_signed(uint32_t bits)
{
    return bits <= INT32_MAX ? (int32_t)bits : -(int32_t)(UINT32_MAX - bits) - 1;
}

static int16_t departure_word(uint32_t bits)
{
    uint32_t word = (uint16_t)bits;
    return (int16_t)(word < 32768 ? (int32_t)word : (int32_t)word - 65536);
}

static uint32_t departure_transition(int32_t current, int32_t target, int16_t step, uint32_t cycles)
{
    uint32_t distance = cycles * (uint32_t)(int32_t)step;
    int32_t value = current;
    if (current > target)
    {
        value = departure_signed((uint32_t)current - distance);
        if (value < target)
        {
            value = target;
        }
    }
    else if (current < target)
    {
        value = departure_signed((uint32_t)current + distance);
        if (value > target)
        {
            value = target;
        }
    }
    return (uint32_t)value;
}

int vertrix_block_departure_update(VertrixAnimation *animation, const uint32_t *frames,
                                   size_t storage, uint32_t elapsed, uint32_t *descriptor,
                                   VertrixBlockDeparture *departure)
{
    if (!animation || !descriptor || !departure || departure->handler != 0x44dcf0)
    {
        return 0;
    }
    VertrixAnimation next_animation = *animation;
    VertrixBlockDeparture next = *departure;
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
        next.age += cycles;
        if (departure_signed(next.age) > next.threshold)
        {
            next.age = 0;
            next.step_y = departure_word((uint32_t)(int32_t)next.step_y + 1u);
            next.effect_target = -200;
            next.effect_step = 30;
            next.effect = departure_word(departure_transition(next.effect, -200, 30, cycles));
            next.mode_target = 0;
            next.mode_step = 1;
            next.mode = (uint8_t)departure_transition(next.mode, 0, 1, cycles);
            if (!next.mode)
            {
                next.handler = 0x44c860;
            }
            next.x =
                departure_word((uint32_t)(int32_t)next.x + cycles * (uint32_t)(int32_t)next.step_x);
            next.y =
                departure_word((uint32_t)(int32_t)next.y + cycles * (uint32_t)(int32_t)next.step_y);
            if (next.x > next.right || (int32_t)next.x + 23 < next.left || next.y > next.bottom ||
                (int32_t)next.y + 23 < next.top)
            {
                next.handler = 0x44c860;
            }
        }
    }
    *animation = next_animation;
    *departure = next;
    *descriptor = selected;
    return 1;
}
