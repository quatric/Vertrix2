#ifndef VERTRIX_BLOCK_TRIPLE_H
#define VERTRIX_BLOCK_TRIPLE_H
#include "block_update.h"
typedef struct
{
    VertrixTimer timer;
    uint8_t mode, mode_target;
    int16_t mode_step;
    int16_t effect, effect_target, effect_step;
    uint8_t amount, amount_target;
    int16_t amount_step;
    uint8_t field_95;
    uint32_t handler;
} VertrixBlockTriple;
/* Complete original 0x44d9d0; only amount completion selects normal handler. */
int vertrix_block_triple_update(VertrixAnimation *animation, const uint32_t *frames, size_t storage,
                                uint32_t elapsed, uint32_t *descriptor, VertrixBlockTriple *triple);
#endif
