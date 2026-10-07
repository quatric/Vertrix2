#ifndef VERTRIX_BLOCK_BYTE_PULSE_H
#define VERTRIX_BLOCK_BYTE_PULSE_H

#include "block_fade.h"

/* Original variants 0x44cbf0, 0x44cc60, 0x44d410, 0x44d760: first two handlers pulse between zero
 * and 100 with step five. Handler 0x44d410 targets 100 with step eight, then selects normal
 * 0x44c860. Handler 0x44d760 uses the same target/step, then selects 0x44d7d0. */
int vertrix_block_byte_pulse_update(VertrixAnimation *animation, const uint32_t *frames,
                                    size_t frame_storage, uint32_t elapsed, uint32_t *descriptor,
                                    VertrixBlockFade *pulse);

#endif
