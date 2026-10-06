#include "block_mode_amount.h"
#include "byte_transition.h"

int vertrix_block_mode_amount_update(VertrixAnimation *animation, const uint32_t *frames,
                                     size_t storage, uint32_t elapsed, uint32_t *descriptor,
                                     VertrixBlockModeAmount *state)
{
    if (!animation || !descriptor || !state ||
        (state->handler != 0x44e790 && state->handler != 0x44e800 && state->handler != 0x44f990 &&
         state->handler != 0x44fa00))
    {
        return 0;
    }
    VertrixAnimation next_animation = *animation;
    VertrixBlockModeAmount next = *state;
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
        int both = next.handler == 0x44e800;
        int amount = 0;
        if (both)
        {
            next.amount_target = 100;
            next.amount_step = 6;
            amount =
                vertrix_byte_transition(&next.amount, next.amount_target, next.amount_step, cycles);
        }
        next.mode_target = (both || next.handler == 0x44f990) ? 16 : 0;
        next.mode_step = 1;
        int mode = vertrix_byte_transition(&next.mode, next.mode_target, next.mode_step, cycles);
        if (!amount && !mode)
        {
            next.handler = both ? 0x44e890
                                : (next.handler == 0x44f990
                                       ? 0x44fa00
                                       : (next.handler == 0x44fa00 ? 0x44f990 : 0x44c860));
        }
    }
    *animation = next_animation;
    *state = next;
    *descriptor = selected;
    return 1;
}
