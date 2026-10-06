#ifndef VERTRIX_BLOCK_STAGED_H
#define VERTRIX_BLOCK_STAGED_H
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
    uint8_t stage;
} VertrixBlockStaged;
/* Complete original 0x44dbb0. Stage tracks signed effect thresholds;
 * amount completion alone hands off to 0x44dc80. Invalid inputs preserve outputs. */
int vertrix_block_staged_update(VertrixAnimation *animation, const uint32_t *frames, size_t storage,
                                uint32_t elapsed, uint32_t *descriptor, VertrixBlockStaged *staged);
#endif
