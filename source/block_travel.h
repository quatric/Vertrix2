#ifndef VERTRIX_BLOCK_TRAVEL_H
#define VERTRIX_BLOCK_TRAVEL_H
#include "block_update.h"
typedef struct
{
    VertrixTimer timer;
    int16_t origin_x, origin_y;
    int16_t x, target_x, step_x, y, target_y, step_y;
    int32_t current, target, step;
    uint32_t handler;
} VertrixBlockTravel;
/* Original 0x44ebe0 -> 0x44ec40 -> 0x44c860. */
int vertrix_block_travel_update(VertrixAnimation *animation, const uint32_t *frames, size_t storage,
                                uint32_t elapsed, uint32_t *descriptor, VertrixBlockTravel *travel);
#endif
