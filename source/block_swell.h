#ifndef VERTRIX_BLOCK_SWELL_H
#define VERTRIX_BLOCK_SWELL_H
#include "block_update.h"
typedef struct
{
    VertrixTimer timer;
    uint8_t mode, mode_target;
    int16_t mode_step;
    int16_t effect, effect_target, effect_step;
    uint8_t amount, field_93;
    uint32_t handler;
} VertrixBlockSwell;
/* Original 0x44e590 -> 0x44e600 -> 0x44e670 -> 0x44c860,
 * plus 0x44f040 -> 0x44f0b0 -> 0x44c860. */
int vertrix_block_swell_update(VertrixAnimation *animation, const uint32_t *frames, size_t storage,
                               uint32_t elapsed, uint32_t *descriptor, VertrixBlockSwell *swell);
#endif
