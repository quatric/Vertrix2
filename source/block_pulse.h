#ifndef VERTRIX_BLOCK_PULSE_H
#define VERTRIX_BLOCK_PULSE_H
#include "block_motion.h"

typedef struct
{
    VertrixTimer timer;
    int16_t effect, target, step;
    uint32_t handler;
} VertrixBlockPulse;
/* Original 0x44c9d0/0x44ca40: due ticks target +200/-200 with step 4,
 * switching to the other handler on arrival. Same signed-word transition
 * arithmetic as 0x4ad530. Handler must identify one of these two phases.
 * Resolved descriptors required; invalid input preserves outputs. */
int vertrix_block_pulse_update(VertrixAnimation *animation, const uint32_t *frames,
                               size_t frame_storage, uint32_t elapsed, uint32_t *descriptor,
                               VertrixBlockPulse *pulse);
#endif
