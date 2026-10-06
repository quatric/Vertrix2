#ifndef VERTRIX_BLOCK_FADE_H
#define VERTRIX_BLOCK_FADE_H
#include "block_update.h"

typedef struct
{
    VertrixTimer timer;
    uint8_t current, target;
    int16_t step;
    uint8_t field_93;
    uint32_t handler;
} VertrixBlockFade;
/* Original 0x44c960 with byte transition 0x4ad580. Preserve wrapping 32-bit
 * arithmetic and signed comparisons before storing the low byte. Resolved
 * frame order required. Invalid input preserves every output. */
int vertrix_block_fade_update(VertrixAnimation *animation, const uint32_t *frames,
                              size_t frame_storage, uint32_t elapsed, uint32_t *descriptor,
                              VertrixBlockFade *fade);
#endif
