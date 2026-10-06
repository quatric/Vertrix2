#ifndef VERTRIX_BLOCK_VISIBILITY_H
#define VERTRIX_BLOCK_VISIBILITY_H
#include "block_update.h"
typedef struct
{
    VertrixTimer timer;
    uint8_t amount, target;
    int16_t step;
    uint8_t field_93, field_94, field_95;
    uint32_t handler;
} VertrixBlockVisibility;
/* Original 0x44e4a0/0x44e510/0x44ef60/0x44efd0.
 * Only 0x44e4a0 clears field_93 on completion; only 0x44e510 clears fields_94/95. */
int vertrix_block_visibility_update(VertrixAnimation *animation, const uint32_t *frames,
                                    size_t storage, uint32_t elapsed, uint32_t *descriptor,
                                    VertrixBlockVisibility *visibility);
#endif
