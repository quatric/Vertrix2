#ifndef VERTRIX_BLOCK_MODE_PULSE_H
#define VERTRIX_BLOCK_MODE_PULSE_H
#include "block_update.h"
typedef struct
{
    VertrixTimer timer;
    uint8_t current, target;
    int16_t step;
    uint32_t age;
    uint8_t field_95;
    uint32_t handler;
} VertrixBlockModePulse;
/* Original 0x44d8b0/0x44d940: alternate mode zero/16, stop at signed age >=30.
 * Invalid state preserves all outputs. */
int vertrix_block_mode_pulse_update(VertrixAnimation *animation, const uint32_t *frames,
                                    size_t storage, uint32_t elapsed, uint32_t *descriptor,
                                    VertrixBlockModePulse *pulse);
#endif
