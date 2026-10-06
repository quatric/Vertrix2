#ifndef VERTRIX_BLOCK_COMBINED_H
#define VERTRIX_BLOCK_COMBINED_H
#include "block_update.h"

typedef struct
{
    VertrixTimer timer;
    int16_t effect, effect_target, effect_step;
    uint8_t amount, amount_target;
    int16_t amount_step;
    uint8_t field_93, field_95;
    uint32_t handler;
} VertrixBlockCombined;
/* Complete original 0x44cab0/0x44cb50/0x44f7e0/0x44f880. Both transitions
 * must arrive before the next handler. Invalid input preserves all outputs.
 * Resolved descriptor order required. */
int vertrix_block_combined_update(VertrixAnimation *animation, const uint32_t *frames,
                                  size_t frame_storage, uint32_t elapsed, uint32_t *descriptor,
                                  VertrixBlockCombined *combined);
#endif
