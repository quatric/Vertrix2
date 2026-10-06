#include "block_finish_effect.h"
#include "byte_transition.h"
#include "word_transition.h"

int vertrix_block_finish_effect_update(VertrixAnimation *animation, const uint32_t *frames,
                                       size_t storage, uint32_t elapsed, uint32_t *descriptor,
                                       VertrixBlockFinishEffect *effect)
{
    if (!animation || !descriptor || !effect ||
        (effect->transition.handler != 0x450330 && effect->transition.handler != 0x4503b0 &&
         effect->transition.handler != 0x450450 && effect->transition.handler != 0x4504e0 &&
         effect->transition.handler != 0x450550 && effect->transition.handler != 0x4505c0 &&
         effect->transition.handler != 0x450630 && effect->transition.handler != 0x4506a0))
    {
        return 0;
    }
    VertrixBlockFinishEffect next = *effect;
    VertrixBlockCombined *transition = &next.transition;
    VertrixAnimation next_animation = *animation;
    uint32_t selected = *descriptor;
    if (transition->handler == 0x4504e0 || transition->handler == 0x450550 ||
        transition->handler == 0x4505c0 || transition->handler == 0x450630 ||
        transition->handler == 0x4506a0)
    {
        if (!frames || !animation->frame_count || storage < animation->frame_count ||
            animation->frame >= animation->frame_count)
        {
            return 0;
        }
        selected = frames[animation->frame];
        vertrix_timer_advance(&transition->timer, elapsed);
        if (vertrix_timer_due(&transition->timer))
        {
            uint32_t cycles = vertrix_timer_cycles(&transition->timer);
            vertrix_timer_consume(&transition->timer);
            int alternate = transition->handler == 0x450630 || transition->handler == 0x4506a0;
            int first = transition->handler == 0x4504e0 || transition->handler == 0x450630;
            int middle = transition->handler == 0x450550;
            transition->effect_target = first ? 100 : (alternate ? 0 : (middle ? -100 : -200));
            transition->effect_step = first ? 3 : (alternate || middle ? 4 : 10);
            if (!vertrix_word_transition(&transition->effect, transition->effect_target,
                                         transition->effect_step, cycles))
            {
                transition->handler =
                    first ? (alternate ? 0x4506a0 : 0x450550) : (middle ? 0x4505c0 : 0);
                if (first)
                {
                    transition->field_95 = 4;
                    transition->amount = 50;
                }
                else if (!middle)
                {
                    next.state = 2;
                }
            }
        }
        *descriptor = selected;
        *effect = next;
        return 1;
    }
    if (!vertrix_block_update(&next_animation, frames, storage, elapsed, &selected))
    {
        return 0;
    }
    int reveal = transition->handler == 0x450330;
    int paired = transition->handler == 0x4503b0;
    if (reveal || paired)
    {
        transition->field_93 = paired;
        transition->field_95 = 3;
        if (reveal)
        {
            transition->amount = 50;
        }
    }
    vertrix_timer_advance(&transition->timer, elapsed);
    if (vertrix_timer_due(&transition->timer))
    {
        uint32_t cycles = vertrix_timer_cycles(&transition->timer);
        vertrix_timer_consume(&transition->timer);
        int moving = 0;
        if (!reveal)
        {
            transition->amount_target = 0;
            transition->amount_step = paired ? 4 : 2;
            moving = vertrix_byte_transition(&transition->amount, transition->amount_target,
                                             transition->amount_step, cycles);
        }
        transition->effect_target = reveal ? 200 : 0;
        transition->effect_step = reveal || paired ? 8 : 1;
        moving |= vertrix_word_transition(&transition->effect, transition->effect_target,
                                          transition->effect_step, cycles);
        if (!moving)
        {
            transition->handler = reveal ? 0x4503b0 : 0;
            if (paired)
            {
                next.state = 2;
            }
            else
            {
                transition->field_93 = 1;
                transition->amount = reveal ? 100 : 0;
            }
        }
    }
    *animation = next_animation;
    *descriptor = selected;
    *effect = next;
    return 1;
}
