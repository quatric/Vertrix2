#ifndef VERTRIX_LINKED_ALTERNATING_H
#define VERTRIX_LINKED_ALTERNATING_H
#include "block_resource.h"
typedef struct
{
    uint32_t threshold, source, phase, handler, descriptor;
    int16_t origin_y, y, target_y, step_y, effect, effect_target, effect_step;
    int32_t delay, delay_target, delay_step;
    VertrixTimer primary, secondary;
    VertrixAnimation animation;
    const VertrixFrameResource *resource;
} VertrixLinkedAlternating;
/* Original450a10/450aa0/450b30/450b90/450bf0/450c70. Resources correspond
 * to546618 and546634; startingY is533d78. Borrowed resources stay live.
 * Caller resolves first matching linked object. Failed updates preserve state. */
int vertrix_linked_alternating_update(VertrixLinkedAlternating *display, int linked_present,
                                      uint32_t linked_value, uint32_t linked_state, int16_t start_y,
                                      uint32_t elapsed, const VertrixFrameResource *resource_one,
                                      const VertrixFrameResource *resource_other, size_t budget);
#endif
