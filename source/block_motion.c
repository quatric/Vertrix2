#include "block_motion.h"
#include "word_transition.h"

int vertrix_block_motion_update(VertrixAnimation *animation, const uint32_t *frames,
                                size_t frame_storage, uint32_t elapsed, uint32_t *descriptor,
                                VertrixBlockMotion *motion)
{
    if (!animation || !descriptor || !motion)
    {
        return 0;
    }
    VertrixAnimation next_animation = *animation;
    VertrixBlockMotion next = *motion;
    uint32_t selected = *descriptor;
    if (!vertrix_block_update(&next_animation, frames, frame_storage, elapsed, &selected))
    {
        return 0;
    }
    vertrix_timer_advance(&next.timer, elapsed);
    if (vertrix_timer_due(&next.timer))
    {
        uint32_t cycles = vertrix_timer_cycles(&next.timer);
        vertrix_timer_consume(&next.timer);
        vertrix_word_transition(&next.y, next.target, next.step, cycles);
        if (next.y == next.target)
        {
            next.handler = 0x44c860;
        }
    }
    *animation = next_animation;
    *motion = next;
    *descriptor = selected;
    return 1;
}
