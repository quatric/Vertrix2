#include "linked_movement.h"
#include "word_transition.h"

int vertrix_linked_movement_update(VertrixLinkedMovement *movement, int linked_present,
                                   uint32_t linked_value, uint32_t linked_state, int16_t start_y,
                                   uint32_t elapsed, uint32_t *refresh_words, size_t refresh_count)
{
    if (!movement || (movement->handler != 0x450860 && movement->handler != 0x4508c0 &&
                      movement->handler != 0x450920 && movement->handler != 0x450960 &&
                      movement->handler != 0x4509a0 && movement->handler != 0x4509d0))
    {
        return 0;
    }
    VertrixLinkedMovement next = *movement;
    int refresh = 0;
    switch (next.handler)
    {
        case 0x450860:
            if (linked_present &&
                (linked_state ^ UINT32_C(0x80000000)) < (next.threshold ^ UINT32_C(0x80000000)))
            {
                next.y = start_y;
                next.target_y = next.origin_y;
                next.step_y = 1;
                next.source = 1;
                next.primary.counter = 0;
                next.handler = 0x4508c0;
            }
            break;
        case 0x4508c0:
            vertrix_timer_advance(&next.primary, elapsed);
            if (vertrix_timer_due(&next.primary))
            {
                uint32_t cycles = vertrix_timer_cycles(&next.primary);
                vertrix_timer_consume(&next.primary);
                if (!vertrix_word_transition(&next.y, next.target_y, next.step_y, cycles))
                {
                    next.primary.counter = 0;
                    next.active = 1;
                    refresh = 1;
                    next.handler = 0x450920;
                }
            }
            break;
        case 0x450920:
            if (linked_present && linked_value == 1)
            {
                next.secondary.counter = 0;
                next.handler = 0x450960;
            }
            break;
        case 0x450960:
            vertrix_timer_advance(&next.secondary, elapsed);
            if (vertrix_timer_due(&next.secondary))
            {
                next.source = 0;
                refresh = 1;
                next.handler = 0x4509a0;
                next.secondary.counter = 0;
            }
            break;
        case 0x4509a0:
            vertrix_timer_advance(&next.secondary, elapsed);
            if (vertrix_timer_due(&next.secondary))
            {
                next.primary.counter = 0;
                next.handler = 0x4509d0;
            }
            break;
        case 0x4509d0:
            if (linked_present && linked_value == 0)
            {
                next.active = 0;
                next.handler = 0x450860;
            }
            break;
    }
    if (refresh)
    {
        if (next.refresh_index == -1)
        {
            next.refresh = 1;
        }
        else
        {
            if (next.refresh_index < 0 || !refresh_words ||
                (size_t)next.refresh_index >= refresh_count)
            {
                return 0;
            }
            refresh_words[next.refresh_index] = 1;
        }
    }
    *movement = next;
    return 1;
}
