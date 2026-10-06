#ifndef VERTRIX_BLOCK_EFFECT_H
#define VERTRIX_BLOCK_EFFECT_H
#include "block_update.h"
typedef struct
{
    VertrixTimer timer;
    int16_t current, target, step;
    uint8_t field_94;
    uint32_t handler;
    uint8_t stage;
} VertrixBlockEffect;
/* Original 0x44f120/180/1e0/240/2b0/320; plus 0x44f4a0/500/560/5d0/630/690; all preserve the
 * existing effect step. */
int vertrix_block_effect_update(VertrixAnimation *animation, const uint32_t *frames, size_t storage,
                                uint32_t elapsed, uint32_t *descriptor, VertrixBlockEffect *effect);
#endif
