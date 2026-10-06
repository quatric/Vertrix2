#include "number_transition.h"
#include "word_transition.h"

int vertrix_number_transition_update(VertrixNumberTransition *transition,
                                     VertrixNumberPlayer *linked_number,
                                     const uint32_t *player_values, size_t player_count,
                                     uint32_t elapsed)
{
    return vertrix_number_transition_configured(transition, linked_number, player_values,
                                                player_count, elapsed, 0, 0);
}

int vertrix_number_transition_configured(VertrixNumberTransition *transition,
                                         VertrixNumberPlayer *linked_number,
                                         const uint32_t *player_values, size_t player_count,
                                         uint32_t elapsed, uint32_t config_mode,
                                         uint32_t config_value)
{
    if (!transition || (transition->handler != 0x44fad0 && transition->handler != 0x44fb40 &&
                        transition->handler != 0x44fbb0 && transition->handler != 0x44fc60 &&
                        transition->handler != 0x44fcf0 && transition->handler != 0x44fd60 &&
                        transition->handler != 0x44fdb0 && transition->handler != 0x44fe30))
    {
        return 0;
    }
    if ((transition->handler == 0x44fad0 || transition->handler == 0x44fc60 ||
         transition->handler == 0x44fdb0) &&
        (!linked_number || !player_values || linked_number->id >= player_count))
    {
        return 0;
    }
    VertrixNumberTransition next = *transition;
    if (next.handler == 0x44fad0 || next.handler == 0x44fc60)
    {
        next.source = 0;
        if (linked_number->value != player_values[linked_number->id])
        {
            next.effect = -100;
            next.source = 1;
            next.timer.counter = 0;
            next.handler =
                next.handler == 0x44fad0
                    ? 0x44fb40
                    : (config_mode == 1 && config_value == player_values[linked_number->id]
                           ? 0x44fe30
                           : 0x44fcf0);
        }
    }
    else
    {
        vertrix_timer_advance(&next.timer, elapsed);
        if (vertrix_timer_due(&next.timer))
        {
            uint32_t cycles = vertrix_timer_cycles(&next.timer);
            vertrix_timer_consume(&next.timer);
            int rising =
                next.handler == 0x44fb40 || next.handler == 0x44fcf0 || next.handler == 0x44fdb0;
            next.target = rising ? 50 : -100;
            next.step = next.handler == 0x44fdb0 || next.handler == 0x44fe30 ? 4 : 2;
            if (!vertrix_word_transition(&next.effect, next.target, next.step, cycles))
            {
                if (rising)
                {
                    if (!linked_number)
                    {
                        return 0;
                    }
                    if (next.handler != 0x44fdb0 ||
                        linked_number->value != player_values[linked_number->id])
                    {
                        linked_number->handler = next.handler == 0x44fb40 ? 0x44faa0 : 0x44fc30;
                    }
                    next.handler = next.handler == 0x44fb40   ? 0x44fbb0
                                   : next.handler == 0x44fcf0 ? 0x44fd60
                                                              : 0x44fe30;
                }
                else
                {
                    next.handler = next.handler == 0x44fbb0   ? 0x44fad0
                                   : next.handler == 0x44fd60 ? 0x44fc60
                                                              : 0x44fdb0;
                }
            }
        }
    }
    *transition = next;
    return 1;
}
