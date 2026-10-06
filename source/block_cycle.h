#ifndef VERTRIX_BLOCK_CYCLE_H
#define VERTRIX_BLOCK_CYCLE_H
#include "block_update.h"
typedef struct
{
    VertrixTimer timer;
    int32_t current, step;
    uint8_t field_94;
    uint32_t handler;
    int32_t target;
    uint8_t field_8c;
} VertrixBlockCycle;
typedef struct
{
    uint32_t iterations, unwrapped;
} VertrixCycleTrace;
/* Original 0x44f390/0x44f3e0 through 0x4accc0/0x4acd30, plus 0x44f430 through 0x4acc70.
 * Supply the distinct shared trace for the selected direction. */
int vertrix_block_cycle_update(VertrixAnimation *animation, const uint32_t *frames, size_t storage,
                               uint32_t elapsed, uint32_t *descriptor, VertrixBlockCycle *cycle,
                               VertrixCycleTrace *trace);
#endif
