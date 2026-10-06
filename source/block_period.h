#ifndef VERTRIX_BLOCK_PERIOD_H
#define VERTRIX_BLOCK_PERIOD_H
#include "block_update.h"
typedef struct
{
    VertrixTimer timer;
    int32_t target;
    uint32_t handler;
} VertrixBlockPeriod;
/* Original 0x44e890. Targets at or below the current quotient complete
 * without rewriting the animation period. */
int vertrix_block_period_update(VertrixAnimation *animation, const uint32_t *frames, size_t storage,
                                uint32_t elapsed, uint32_t *descriptor, VertrixBlockPeriod *period);
#endif
