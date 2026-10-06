#ifndef VERTRIX_BLOCK_ACCELERATE_H
#define VERTRIX_BLOCK_ACCELERATE_H
#include "block_update.h"
typedef struct
{
    VertrixTimer timer;
    int16_t effect, target, step;
    uint32_t handler;
} VertrixBlockAccelerate;
/* Original 0x44e6e0 changes animation period after advancing its frame.
 * A period whose signed quotient by 12 is <=1 remains unchanged. */
int vertrix_block_accelerate_update(VertrixAnimation *animation, const uint32_t *frames,
                                    size_t storage, uint32_t elapsed, uint32_t *descriptor,
                                    VertrixBlockAccelerate *accelerate);
#endif
