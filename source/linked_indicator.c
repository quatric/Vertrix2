#include "linked_indicator.h"
#include "byte_transition.h"
#include <stddef.h>

int vertrix_linked_indicator_update(VertrixLinkedIndicator *indicator, int linked_present,
                                    uint32_t linked_value, uint32_t linked_state, uint32_t elapsed)
{
    if (!indicator || (indicator->handler != 0x44ff90 && indicator->handler != 0x44fff0 &&
                       indicator->handler != 0x450040 && indicator->handler != 0x4500b0 &&
                       indicator->handler != 0x450100))
    {
        return 0;
    }
    VertrixLinkedIndicator next = *indicator;
    int below = (linked_state ^ UINT32_C(0x80000000)) < (next.threshold ^ UINT32_C(0x80000000));
    switch (next.handler)
    {
        case 0x44ff90:
            if (linked_present && !below)
            {
                next.stage = 13;
                next.timer.counter = 0;
                next.amount = 0;
                next.target = 100;
                next.step = 3;
                next.source = 1;
                next.handler = 0x44fff0;
            }
            break;
        case 0x450040:
            if (linked_present && (linked_value == 1 || below))
            {
                next.timer.counter = 0;
                next.target = 0;
                next.step = linked_value == 1 ? 1 : 3;
                next.handler = 0x4500b0;
            }
            break;
        case 0x450100:
            if (linked_present && linked_value == 0)
            {
                next.handler = 0x44ff90;
            }
            break;
        default:
            vertrix_timer_advance(&next.timer, elapsed);
            if (vertrix_timer_due(&next.timer))
            {
                uint32_t cycles = vertrix_timer_cycles(&next.timer);
                vertrix_timer_consume(&next.timer);
                if (!vertrix_byte_transition(&next.amount, next.target, next.step, cycles))
                {
                    if (next.handler == 0x44fff0)
                    {
                        next.handler = 0x450040;
                    }
                    else
                    {
                        next.source = 0;
                        next.handler = 0x450100;
                    }
                }
            }
            break;
    }
    *indicator = next;
    return 1;
}
