#include "block_fade.h"
#include "byte_transition.h"

int vertrix_block_fade_update(VertrixAnimation *animation, const uint32_t *frames,
                              size_t frame_storage, uint32_t elapsed, uint32_t *descriptor,
                              VertrixBlockFade *fade)
{
    if (!animation || !descriptor || !fade)
    {
        return 0;
    }
    VertrixAnimation next_animation = *animation;
    VertrixBlockFade next = *fade;
    uint32_t selected = *descriptor;
    if (!vertrix_block_update(&next_animation, frames, frame_storage, elapsed, &selected))
    {
        return 0;
    }
    next.field_93 = 1;
    vertrix_timer_advance(&next.timer, elapsed);
    if (vertrix_timer_due(&next.timer))
    {
        uint32_t cycles = vertrix_timer_cycles(&next.timer);
        vertrix_timer_consume(&next.timer);
        next.target = 0;
        next.step = 8;
        vertrix_byte_transition(&next.current, next.target, next.step, cycles);
        if (!next.current)
        {
            next.handler = 0x44c940;
        }
    }
    *animation = next_animation;
    *fade = next;
    *descriptor = selected;
    return 1;
}
