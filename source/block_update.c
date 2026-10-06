#include "block_update.h"

int vertrix_block_update(VertrixAnimation *animation, const uint32_t *frames, size_t frame_storage,
                         uint32_t elapsed, uint32_t *descriptor)
{
    return vertrix_block_animation_update(0x44c860, animation, frames, frame_storage, elapsed,
                                          descriptor);
}

int vertrix_block_animation_update(uint32_t handler, VertrixAnimation *animation,
                                   const uint32_t *frames, size_t frame_storage, uint32_t elapsed,
                                   uint32_t *descriptor)
{
    if (handler != 0x44c860 && handler != 0x450710 && handler != 0x450730)
    {
        return 0;
    }
    if (!animation || !frames || !descriptor || frame_storage < animation->frame_count)
    {
        return 0;
    }
    VertrixAnimation next = *animation;
    VertrixAnimationMode mode =
        handler == 0x450730 ? VERTRIX_ANIMATION_REVERSE_LOOP : VERTRIX_ANIMATION_FORWARD_LOOP;
    if (vertrix_animation_tick(&next, elapsed, mode) < 0)
    {
        return 0;
    }
    uint32_t selected = frames[next.frame];
    *animation = next;
    *descriptor = selected;
    return 1;
}
