#ifndef VERTRIX_BLOCK_HALF_PULSE_H
#define VERTRIX_BLOCK_HALF_PULSE_H
#include "block_mode_pulse.h"
typedef struct
{
    VertrixBlockModePulse mode;
    uint8_t amount, amount_target;
    int16_t amount_step;
} VertrixBlockHalfPulse;
/* Original 0x44da70/0x44db10: amount targets 50 while mode alternates.
 * Signed age >=30 overrides phase switching; invalid input preserves outputs. */
int vertrix_block_half_pulse_update(VertrixAnimation *animation, const uint32_t *frames,
                                    size_t storage, uint32_t elapsed, uint32_t *descriptor,
                                    VertrixBlockHalfPulse *pulse);
#endif
