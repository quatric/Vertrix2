#ifndef VERTRIX_BLOCK_SCALE_H
#define VERTRIX_BLOCK_SCALE_H
#include "block_update.h"

typedef struct
{
    VertrixTimer timer;
    int32_t current, target, step;
    int16_t effect, effect_target, effect_step;
    uint8_t amount, field_95;
    uint32_t handler;
} VertrixBlockScale;

/* Original 0x44ce80/0x44cfd0/0x44d330/0x44d3a0/0x44d5f0/0x44d660,
 * using transition 0x4ad6e0.
 * Caller supplies resolved animation descriptors. Invalid input preserves outputs. */
int vertrix_block_scale_update(VertrixAnimation *animation, const uint32_t *frames,
                               size_t frame_storage, uint32_t elapsed, uint32_t *descriptor,
                               VertrixBlockScale *scale);
#endif
