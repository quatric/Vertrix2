#ifndef VERTRIX_BLOCK_UPDATE_H
#define VERTRIX_BLOCK_UPDATE_H
#include "animation.h"
#include <stddef.h>

/* Original normal block handler 0x44c860: forward-loop animation followed by
 * descriptor binding through 0x4ac8a0. Frames are resolved resource descriptors
 * in original frame order, including any source-resource indirection. Valid
 * storage must cover animation.frame_count. Rejects before mutation on error. */
int vertrix_block_update(VertrixAnimation *animation, const uint32_t *frames, size_t frame_storage,
                         uint32_t elapsed, uint32_t *descriptor);
/* Animation-only dispatch:44c860/450710 forward loop,450730 reverse loop. */
int vertrix_block_animation_update(uint32_t handler, VertrixAnimation *animation,
                                   const uint32_t *frames, size_t frame_storage, uint32_t elapsed,
                                   uint32_t *descriptor);
#endif
