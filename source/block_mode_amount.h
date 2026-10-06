#ifndef VERTRIX_BLOCK_MODE_AMOUNT_H
#define VERTRIX_BLOCK_MODE_AMOUNT_H
#include "block_update.h"
typedef struct
{
    VertrixTimer timer;
    uint8_t mode, mode_target;
    int16_t mode_step;
    uint8_t amount, amount_target;
    int16_t amount_step;
    uint32_t handler;
} VertrixBlockModeAmount;
/* Original 0x44e790/0x44e800 plus 0x44f990/0x44fa00.
 * 0x44e800 waits for both transitions; the final pair alternates mode16/0. */
int vertrix_block_mode_amount_update(VertrixAnimation *animation, const uint32_t *frames,
                                     size_t storage, uint32_t elapsed, uint32_t *descriptor,
                                     VertrixBlockModeAmount *state);
#endif
