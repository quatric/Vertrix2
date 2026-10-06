#include "block_visibility.h"
#include "byte_transition.h"

int vertrix_block_visibility_update(VertrixAnimation *animation, const uint32_t *frames,
                                    size_t storage, uint32_t elapsed, uint32_t *descriptor,
                                    VertrixBlockVisibility *visibility)
{
    if (!animation || !descriptor || !visibility ||
        (visibility->handler != 0x44e4a0 && visibility->handler != 0x44e510 &&
         visibility->handler != 0x44ef60 && visibility->handler != 0x44efd0))
    {
        return 0;
    }
    VertrixAnimation next_animation = *animation;
    VertrixBlockVisibility next = *visibility;
    uint32_t selected = *descriptor;
    if (!vertrix_block_update(&next_animation, frames, storage, elapsed, &selected))
    {
        return 0;
    }
    int hide = next.handler == 0x44e510 || next.handler == 0x44ef60;
    int clear_completion = next.handler == 0x44e4a0;
    next.field_93 = 1;
    if (next.handler == 0x44e510)
    {
        next.field_94 = 0;
        next.field_95 = 0;
    }
    vertrix_timer_advance(&next.timer, elapsed);
    if (vertrix_timer_due(&next.timer))
    {
        uint32_t cycles = vertrix_timer_cycles(&next.timer);
        vertrix_timer_consume(&next.timer);
        next.target = hide ? 0 : 100;
        next.step = clear_completion ? 2 : 8;
        if (!vertrix_byte_transition(&next.amount, next.target, next.step, cycles))
        {
            next.handler = 0x44c860;
            if (clear_completion)
            {
                next.field_93 = 0;
            }
        }
    }
    *animation = next_animation;
    *visibility = next;
    *descriptor = selected;
    return 1;
}
