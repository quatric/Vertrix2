#ifndef VERTRIX_BLOCK_CHAIN_H
#define VERTRIX_BLOCK_CHAIN_H
#include "block_combined.h"

/* Complete original 0x44d1e0 -> 0x44d250 -> 0x44d2c0 effect sequence,
 * plus 0x44d480 -> 0x44d4f0 signed phases handing off to 0x44d560.
 * Also 0x44d7d0 -> 0x44d840, targeting 50 then zero before normal updates.
 * Handler 0x44dc80 returns the signed effect to zero with step twenty.
 * Uses the shared combined state without changing field 0x95.
 * Invalid input preserves outputs. Descriptors must already be resolved. */
int vertrix_block_chain_update(VertrixAnimation *animation, const uint32_t *frames,
                               size_t frame_storage, uint32_t elapsed, uint32_t *descriptor,
                               VertrixBlockCombined *chain);
#endif
