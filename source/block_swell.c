#include "block_swell.h"
#include "byte_transition.h"
#include "word_transition.h"

int vertrix_block_swell_update(VertrixAnimation *animation, const uint32_t *frames, size_t storage,
                               uint32_t elapsed, uint32_t *descriptor, VertrixBlockSwell *swell)
{
    if (!animation || !descriptor || !swell ||
        (swell->handler != 0x44e590 && swell->handler != 0x44e600 && swell->handler != 0x44e670 &&
         swell->handler != 0x44f040 && swell->handler != 0x44f0b0 && swell->handler != 0x44f700 &&
         swell->handler != 0x44f770 && swell->handler != 0x44f920))
    {
        return 0;
    }
    VertrixAnimation next_animation = *animation;
    VertrixBlockSwell next = *swell;
    uint32_t selected = *descriptor;
    if (!vertrix_block_update(&next_animation, frames, storage, elapsed, &selected))
    {
        return 0;
    }
    if (next.handler == 0x44e590)
    {
        next.field_93 = 0;
        next.amount = 100;
    }
    vertrix_timer_advance(&next.timer, elapsed);
    if (vertrix_timer_due(&next.timer))
    {
        uint32_t cycles = vertrix_timer_cycles(&next.timer);
        vertrix_timer_consume(&next.timer);
        if (next.handler == 0x44e590)
        {
            next.mode_target = 16;
            next.mode_step = 1;
            if (!vertrix_byte_transition(&next.mode, next.mode_target, next.mode_step, cycles))
            {
                next.handler = 0x44e600;
            }
        }
        else
        {
            int alternate = next.handler == 0x44f040 || next.handler == 0x44f0b0;
            int middle = next.handler == 0x44e600 || next.handler == 0x44f040;
            int high = next.handler == 0x44f700;
            next.effect_target = high ? 100 : (middle ? 50 : 0);
            next.effect_step = next.handler == 0x44f920
                                   ? 20
                                   : (alternate ? (middle ? 10 : 20) : (middle ? 5 : 10));
            if (!vertrix_word_transition(&next.effect, next.effect_target, next.effect_step,
                                         cycles))
            {
                next.handler =
                    high ? 0x44f770 : (middle ? (alternate ? 0x44f0b0 : 0x44e670) : 0x44c860);
            }
        }
    }
    *animation = next_animation;
    *swell = next;
    *descriptor = selected;
    return 1;
}
