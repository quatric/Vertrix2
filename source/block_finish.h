#ifndef VERTRIX_BLOCK_FINISH_H
#define VERTRIX_BLOCK_FINISH_H
#include "block_update.h"

typedef struct
{
    VertrixTimer timer;
    uint8_t amount, amount_target;
    int16_t amount_step;
    uint8_t mode, mode_target;
    int16_t mode_step;
    uint8_t field_93;
    uint32_t handler;
} VertrixBlockFinish;

/* Complete original 0x44d560 and 0x44d6d0: paired byte/mode transitions.
 * 0x44d560 selects normal after both reach zero. 0x44d6d0 sets amount 80
 * each update and selects 0x44d760 when mode reaches 16.
 * Invalid input preserves outputs. */
int vertrix_block_finish_update(VertrixAnimation *animation, const uint32_t *frames,
                                size_t frame_storage, uint32_t elapsed, uint32_t *descriptor,
                                VertrixBlockFinish *finish);
#endif
