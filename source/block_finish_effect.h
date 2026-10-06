#ifndef VERTRIX_BLOCK_FINISH_EFFECT_H
#define VERTRIX_BLOCK_FINISH_EFFECT_H
#include "block_combined.h"
typedef struct
{
    VertrixBlockCombined transition;
    uint8_t state;
} VertrixBlockFinishEffect;
/* Original450330/4503b0/450450 and non-animating4504e0/450550/4505c0/450630/4506a0;
 * state is object byte15d. The latter handlers bind the existing frame. */
int vertrix_block_finish_effect_update(VertrixAnimation *animation, const uint32_t *frames,
                                       size_t storage, uint32_t elapsed, uint32_t *descriptor,
                                       VertrixBlockFinishEffect *effect);
#endif
