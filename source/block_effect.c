#include "block_effect.h"
#include "word_transition.h"

int vertrix_block_effect_update(VertrixAnimation *animation, const uint32_t *frames, size_t storage,
                                uint32_t elapsed, uint32_t *descriptor, VertrixBlockEffect *effect)
{
    if (!animation || !descriptor || !effect ||
        (effect->handler != 0x44f120 && effect->handler != 0x44f180 &&
         effect->handler != 0x44f1e0 && effect->handler != 0x44f240 &&
         effect->handler != 0x44f2b0 && effect->handler != 0x44f320 &&
         effect->handler != 0x44f4a0 && effect->handler != 0x44f500 &&
         effect->handler != 0x44f560 && effect->handler != 0x44f5d0 &&
         effect->handler != 0x44f630 && effect->handler != 0x44f690))
    {
        return 0;
    }
    VertrixAnimation next_animation = *animation;
    VertrixBlockEffect next = *effect;
    uint32_t selected = *descriptor;
    if (!vertrix_block_update(&next_animation, frames, storage, elapsed, &selected))
    {
        return 0;
    }
    if (next.handler == 0x44f240 || next.handler == 0x44f2b0)
    {
        next.field_94 = 0;
    }
    vertrix_timer_advance(&next.timer, elapsed);
    if (vertrix_timer_due(&next.timer))
    {
        uint32_t cycles = vertrix_timer_cycles(&next.timer);
        vertrix_timer_consume(&next.timer);
        if (next.handler == 0x44f120 || next.handler == 0x44f4a0 || next.handler == 0x44f5d0)
        {
            next.target = 100;
        }
        else if (next.handler == 0x44f180 || next.handler == 0x44f500 || next.handler == 0x44f630)
        {
            next.target = -100;
        }
        else if (next.handler == 0x44f1e0 || next.handler == 0x44f320 || next.handler == 0x44f560 ||
                 next.handler == 0x44f690)
        {
            next.target = 0;
        }
        if (!vertrix_word_transition(&next.current, next.target, next.step, cycles))
        {
            switch (next.handler)
            {
                case 0x44f120:
                    next.handler = 0x44f180;
                    break;
                case 0x44f180:
                    next.handler = 0x44f120;
                    break;
                case 0x44f1e0:
                    next.handler = 0x44c860;
                    break;
                case 0x44f4a0:
                    next.handler = 0x44f500;
                    break;
                case 0x44f500:
                    next.handler = 0x44f4a0;
                    break;
                case 0x44f5d0:
                    next.handler = 0x44f630;
                    break;
                case 0x44f630:
                    next.handler = 0x44f5d0;
                    break;
                case 0x44f560:
                case 0x44f690:
                case 0x44f320:
                    next.stage = 13;
                    next.handler = 0x44c860;
                    break;
                case 0x44f240:
                    next.target = 0;
                    next.handler = 0x44f2b0;
                    break;
                case 0x44f2b0:
                    next.target = -100;
                    next.handler = 0x44f240;
                    break;
            }
        }
    }
    *animation = next_animation;
    *effect = next;
    *descriptor = selected;
    return 1;
}
