#include "block_return.h"

int vertrix_block_return_update(VertrixAnimation *animation, const uint32_t *frames,
                                size_t frame_storage, uint32_t elapsed, uint32_t *descriptor,
                                VertrixBlockMotion *motion, uint8_t *field_95)
{
    if (!motion || !field_95 || (motion->handler != 0x44cf00 && motion->handler != 0x44cf70))
    {
        return 0;
    }
    VertrixBlockMotion next = *motion;
    if (!vertrix_block_motion_update(animation, frames, frame_storage, elapsed, descriptor, &next))
    {
        return 0;
    }
    if (next.handler == 0x44c860 && motion->handler == 0x44cf00)
    {
        next.handler = 0x44cf70;
        next.target = 0;
        next.step = 10;
    }
    *motion = next;
    *field_95 = 1;
    return 1;
}
