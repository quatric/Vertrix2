#include "linked_burst.h"
#include "dword_transition.h"
#include "word_transition.h"
#include <stddef.h>

static void burst_start(VertrixLinkedBurst *burst, VertrixRandom *random)
{
    burst->effect = -40;
    burst->target = 0;
    burst->step = (int16_t)(vertrix_random_modulo(random, 3) + 2);
    burst->handler = 0x4501a0;
}

int vertrix_linked_burst_update(VertrixLinkedBurst *burst, int linked_present,
                                uint32_t linked_value, uint32_t elapsed, VertrixRandom *random)
{
    if (!burst || !random ||
        (burst->handler != 0x450130 && burst->handler != 0x4501a0 && burst->handler != 0x450200 &&
         burst->handler != 0x450270 && burst->handler != 0x450300))
    {
        return 0;
    }
    VertrixLinkedBurst next = *burst;
    if (next.handler == 0x450130)
    {
        if (linked_present && linked_value == 1)
        {
            next.repetitions = 3;
            next.source = 1;
            burst_start(&next, random);
            next.timer.counter = 0;
        }
    }
    else if (next.handler == 0x450300)
    {
        if (linked_present && linked_value == 0)
        {
            next.handler = 0x450130;
        }
    }
    else
    {
        vertrix_timer_advance(&next.timer, elapsed);
        if (vertrix_timer_due(&next.timer))
        {
            uint32_t cycles = vertrix_timer_cycles(&next.timer);
            vertrix_timer_consume(&next.timer);
            if (next.handler == 0x450200)
            {
                if (!vertrix_dword_transition(&next.delay, next.delay_target, next.delay_step,
                                              cycles))
                {
                    next.target = -100;
                    int32_t scaled = (int32_t)next.step * 5 / 2;
                    uint16_t word = (uint16_t)scaled;
                    next.step = (int16_t)(word < 32768 ? (int32_t)word : (int32_t)word - 65536);
                    next.effect = 0;
                    next.handler = 0x450270;
                }
            }
            else if (!vertrix_word_transition(&next.effect, next.target, next.step, cycles))
            {
                if (next.handler == 0x4501a0)
                {
                    next.delay = 0;
                    next.delay_target = 1;
                    next.delay_step = 1;
                    next.handler = 0x450200;
                }
                else
                {
                    next.repetitions--;
                    if (!next.repetitions)
                    {
                        next.source = 0;
                        next.handler = 0x450300;
                    }
                    else
                    {
                        burst_start(&next, random);
                    }
                }
            }
        }
    }
    *burst = next;
    return 1;
}
