#ifndef VERTRIX_BLOCK_SPIN_H
#define VERTRIX_BLOCK_SPIN_H
#include "block_orbit.h"
typedef struct
{
    VertrixTimer timer, rotation_timer;
    int16_t x, y, angle, rotation_step, radius;
    int16_t center_x, center_y, rotation_target, rotation_change;
    uint8_t mode, amount, amount_target;
    int16_t amount_step;
    uint8_t field_93;
    uint32_t handler;
} VertrixBlockSpin;
/* Original 0x44ece0/0x44ee20. Both transitions execute even when their timer supplies zero cycles.
 * The reveal variant clears field_93 only when both transitions complete. */
int vertrix_block_spin_update(VertrixAnimation *animation, const uint32_t *frames, size_t storage,
                              uint32_t elapsed, uint32_t *descriptor, VertrixBlockSpin *spin,
                              VertrixRotationTrace *trace, const VertrixBlockOrbitContext *context);
#endif
