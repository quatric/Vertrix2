#ifndef VERTRIX_BLOCK_MOTION_H
#define VERTRIX_BLOCK_MOTION_H
#include "block_update.h"

typedef struct
{
    VertrixTimer timer;
    int16_t y;
    int16_t target;
    int16_t step;
    uint32_t handler;
} VertrixBlockMotion;
/* Complete original moving block handler 0x44c880, including 0x4acab0.
 * Animate, advance primary timer, consume due cycles, move/clamp toward target,
 * return to normal handler 0x44c860 on arrival, and bind the selected descriptor.
 * Resolved frame order is required. Invalid animation/storage preserves output. */
int vertrix_block_motion_update(VertrixAnimation *animation, const uint32_t *frames,
                                size_t frame_storage, uint32_t elapsed, uint32_t *descriptor,
                                VertrixBlockMotion *motion);
#endif
