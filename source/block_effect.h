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
/* Original variants 0x44f120, 0x44f180, 0x44f1e0, 0x44f240, 0x44f2b0, 0x44f320,
 * 0x44f4a0, 0x44f500, 0x44f560, 0x44f5d0, 0x44f630, 0x44f690: all preserve the
 * existing effect step. */
int vertrix_block_effect_update(VertrixAnimation *animation, const uint32_t *frames, size_t storage,
                                uint32_t elapsed, uint32_t *descriptor, VertrixBlockEffect *effect);
#endif
