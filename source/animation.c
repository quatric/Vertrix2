#include "animation.h"

int vertrix_animation_tick(VertrixAnimation *animation, uint32_t elapsed, VertrixAnimationMode mode)
{
    if (!animation->frame_count || animation->frame >= animation->frame_count ||
        mode < VERTRIX_ANIMATION_FORWARD_LOOP || mode > VERTRIX_ANIMATION_REVERSE_LOOP)
    {
        return -1;
    }
    vertrix_timer_advance(&animation->timer, elapsed);
    if (!vertrix_timer_due(&animation->timer))
    {
        return 1;
    }
    uint32_t steps = vertrix_timer_cycles(&animation->timer);
    vertrix_timer_consume(&animation->timer);
    if (mode == VERTRIX_ANIMATION_FORWARD_LOOP)
    {
        animation->frame = ((uint64_t)animation->frame + steps) % animation->frame_count;
    }
    else if (mode == VERTRIX_ANIMATION_REVERSE_LOOP)
    {
        uint32_t backwards = steps % animation->frame_count;
        animation->frame = ((uint64_t)animation->frame + animation->frame_count - backwards) %
                           animation->frame_count;
    }
    else
    {
        uint32_t distance = mode == VERTRIX_ANIMATION_FORWARD_ONCE
                                ? animation->frame_count - 1 - animation->frame
                                : animation->frame;
        if (steps > distance)
        {
            animation->frame =
                mode == VERTRIX_ANIMATION_FORWARD_ONCE ? animation->frame_count - 1 : 0;
            return 0;
        }
        if (mode == VERTRIX_ANIMATION_FORWARD_ONCE)
        {
            animation->frame += steps;
        }
        else
        {
            animation->frame -= steps;
        }
    }
    return 1;
}
