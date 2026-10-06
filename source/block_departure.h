#ifndef VERTRIX_BLOCK_DEPARTURE_H
#define VERTRIX_BLOCK_DEPARTURE_H
#include "block_update.h"
typedef struct
{
    VertrixTimer timer;
    uint32_t age;
    int32_t threshold;
    int16_t x, y, step_x, step_y;
    uint8_t mode, mode_target;
    int16_t mode_step;
    int16_t effect, effect_target, effect_step;
    uint8_t field_95;
    uint32_t handler;
    int16_t left, right, top, bottom;
} VertrixBlockDeparture;
/* Complete original 0x44dcf0. Strict signed age threshold gates transitions
 * and movement; source clipping uses the original 24-pixel block bounds.
 * Invalid input preserves outputs. */
int vertrix_block_departure_update(VertrixAnimation *animation, const uint32_t *frames,
                                   size_t storage, uint32_t elapsed, uint32_t *descriptor,
                                   VertrixBlockDeparture *departure);
#endif
