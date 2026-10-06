#include "block_collapse.h"
#include "byte_transition.h"
#include "word_transition.h"

int vertrix_block_collapse_update(VertrixAnimation *animation, const uint32_t *frames,
                                  size_t storage, uint32_t elapsed, uint32_t *descriptor,
                                  VertrixBlockCollapse *collapse)
{
    if (!animation || !descriptor || !collapse ||
        (collapse->handler != 0x44e380 && collapse->handler != 0x44e410))
    {
        return 0;
    }
    VertrixAnimation next_animation = *animation;
    VertrixBlockCollapse next = *collapse;
    uint32_t selected = *descriptor;
    if (!vertrix_block_update(&next_animation, frames, storage, elapsed, &selected))
    {
        return 0;
    }
    int second = next.handler == 0x44e410;
    if (second)
    {
        next.field_93 = 1;
        next.field_94 = 0;
        next.field_95 = 0;
    }
    vertrix_timer_advance(&next.timer, elapsed);
    if (vertrix_timer_due(&next.timer))
    {
        uint32_t cycles = vertrix_timer_cycles(&next.timer);
        vertrix_timer_consume(&next.timer);
        next.effect_target = second ? -200 : 50;
        next.effect_step = second ? 10 : 20;
        int changing_effect =
            vertrix_word_transition(&next.effect, next.effect_target, next.effect_step, cycles);
        if (!second && !changing_effect)
        {
            next.handler = 0x44e410;
        }
        next.mode_target = 0;
        next.mode_step = 1;
        if (!vertrix_byte_transition(&next.mode, next.mode_target, next.mode_step, cycles))
        {
            next.handler = 0x44c860;
        }
    }
    *animation = next_animation;
    *collapse = next;
    *descriptor = selected;
    return 1;
}
