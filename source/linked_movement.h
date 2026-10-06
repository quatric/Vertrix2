#ifndef VERTRIX_LINKED_MOVEMENT_H
#define VERTRIX_LINKED_MOVEMENT_H
#include "timer.h"
#include <stddef.h>
typedef struct
{
    uint32_t threshold, source, active, refresh, handler;
    int16_t origin_y, y, target_y, step_y, refresh_index;
    VertrixTimer primary, secondary;
} VertrixLinkedMovement;
/* Original450860/4508c0/450920/450960/4509a0/4509d0. Caller resolves first
 * matching linked object; supplies58/64 and global startingY533d78.
 * Shared refresh words represent5bb714. Invalid inputs preserve outputs. */
int vertrix_linked_movement_update(VertrixLinkedMovement *movement, int linked_present,
                                   uint32_t linked_value, uint32_t linked_state, int16_t start_y,
                                   uint32_t elapsed, uint32_t *refresh_words, size_t refresh_count);
#endif
