#ifndef VERTRIX_BLOCK_FINISH_EFFECT_H
#define VERTRIX_BLOCK_FINISH_EFFECT_H
#include "block_combined.h"
typedef struct
{
    VertrixBlockCombined transition;
    uint8_t state;
} VertrixBlockFinishEffect;
/* Original variants 0x450330, 0x4503b0, 0x450450, 0x4504e0, 0x450550, 0x4505c0,
 * 0x450630, 0x4506a0: the latter five handlers are non-animating;
 * state is object byte15d. The latter handlers bind the existing frame. */
int vertrix_block_finish_effect_update(VertrixAnimation *animation, const uint32_t *frames,
                                       size_t storage, uint32_t elapsed, uint32_t *descriptor,
                                       VertrixBlockFinishEffect *effect);
#endif
