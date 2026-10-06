#ifndef VERTRIX_BLOCK_SLIDE_H
#define VERTRIX_BLOCK_SLIDE_H
#include "block_update.h"
typedef struct
{
    VertrixTimer timer;
    int16_t x, target_x, step_x;
    int16_t effect, effect_target, effect_step;
    uint8_t amount, amount_target;
    int16_t amount_step;
    uint8_t field_95;
    uint32_t handler;
} VertrixBlockSlide;
/* Original 0x44e250 and 0x44e2d0, including narrowed signed distance
 * and unsigned division in the second phase. */
int vertrix_block_slide_update(VertrixAnimation *animation, const uint32_t *frames, size_t storage,
                               uint32_t elapsed, uint32_t *descriptor, VertrixBlockSlide *slide);
#endif
