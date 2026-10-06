#include "block_scale.h"
#include "dword_transition.h"

int vertrix_block_scale_update(VertrixAnimation *animation, const uint32_t *frames,
                               size_t frame_storage, uint32_t elapsed, uint32_t *descriptor,
                               VertrixBlockScale *scale)
{
    if (!animation || !descriptor || !scale ||
        (scale->handler != 0x44ce80 && scale->handler != 0x44cfd0 && scale->handler != 0x44d330 &&
         scale->handler != 0x44d3a0 && scale->handler != 0x44d5f0 && scale->handler != 0x44d660))
    {
        return 0;
    }
    VertrixAnimation next_animation = *animation;
    VertrixBlockScale next = *scale;
    uint32_t selected = *descriptor;
    if (!vertrix_block_update(&next_animation, frames, frame_storage, elapsed, &selected))
    {
        return 0;
    }
    if (next.handler == 0x44ce80 || next.handler == 0x44cfd0)
    {
        next.field_95 = 1;
    }
    vertrix_timer_advance(&next.timer, elapsed);
    if (vertrix_timer_due(&next.timer))
    {
        uint32_t cycles = vertrix_timer_cycles(&next.timer);
        vertrix_timer_consume(&next.timer);
        if (next.handler == 0x44d330 || next.handler == 0x44d3a0)
        {
            next.target = 100;
            next.step = next.handler == 0x44d330 ? 10 : 20;
        }
        else if (next.handler == 0x44d5f0 || next.handler == 0x44d660)
        {
            next.target = next.handler == 0x44d5f0 ? -100 : 0;
            next.step = 20;
        }
        vertrix_dword_transition(&next.current, next.target, next.step, cycles);
        if (next.current == next.target)
        {
            if (next.handler == 0x44ce80)
            {
                next.amount = 100;
                next.handler = 0x44cf00;
                next.effect = 0;
                next.effect_target = 50;
                next.effect_step = 10;
            }
            else if (next.handler == 0x44cfd0)
            {
                next.handler = 0x44d030;
            }
            else if (next.handler == 0x44d330)
            {
                next.current = 0;
                next.handler = 0x44d3a0;
            }
            else if (next.handler == 0x44d3a0)
            {
                next.handler = 0x44d410;
            }
            else
            {
                next.handler = next.handler == 0x44d5f0 ? 0x44d660 : 0x44d6d0;
            }
        }
    }
    *animation = next_animation;
    *scale = next;
    *descriptor = selected;
    return 1;
}
