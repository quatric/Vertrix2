#ifndef VERTRIX_BLOCK_COLLAPSE_H
#define VERTRIX_BLOCK_COLLAPSE_H
#include "block_update.h"
typedef struct
{
    VertrixTimer timer;
    uint8_t mode, mode_target;
    int16_t mode_step;
    int16_t effect, effect_target, effect_step;
    uint8_t field_93, field_94, field_95;
    uint32_t handler;
} VertrixBlockCollapse;
/* Original 0x44e380/0x44e410. Mode completion overrides the phase handoff. */
int vertrix_block_collapse_update(VertrixAnimation *animation, const uint32_t *frames,
                                  size_t storage, uint32_t elapsed, uint32_t *descriptor,
                                  VertrixBlockCollapse *collapse);
#endif
