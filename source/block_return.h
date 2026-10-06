#ifndef VERTRIX_BLOCK_RETURN_H
#define VERTRIX_BLOCK_RETURN_H
#include "block_motion.h"

/* Original 0x44cf00/0x44cf70: signed effect transition, followed by
 * return to zero and the normal handler. motion.y represents effect +0x48.
 * Invalid inputs preserve all outputs. */
int vertrix_block_return_update(VertrixAnimation *animation, const uint32_t *frames,
                                size_t frame_storage, uint32_t elapsed, uint32_t *descriptor,
                                VertrixBlockMotion *motion, uint8_t *field_95);
#endif
