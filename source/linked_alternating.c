#include "linked_alternating.h"
#include "dword_transition.h"
#include "word_transition.h"

static int display_attach(VertrixLinkedAlternating *display, const VertrixFrameResource *resource,
                          size_t budget)
{
    return vertrix_block_resource_attach(&display->animation, &display->resource, resource) &&
           vertrix_block_resource_bind(&display->animation, display->resource, budget,
                                       &display->descriptor);
}

int vertrix_linked_alternating_update(VertrixLinkedAlternating *display, int linked_present,
                                      uint32_t linked_value, uint32_t linked_state, int16_t start_y,
                                      uint32_t elapsed, const VertrixFrameResource *resource_one,
                                      const VertrixFrameResource *resource_other, size_t budget)
{
    if (!display || (display->handler != 0x450a10 && display->handler != 0x450aa0 &&
                     display->handler != 0x450b30 && display->handler != 0x450b90 &&
                     display->handler != 0x450bf0 && display->handler != 0x450c70))
    {
        return 0;
    }
    VertrixLinkedAlternating next = *display;
    if (next.handler == 0x450a10)
    {
        if (linked_present && next.phase == 1 && linked_value == 1)
        {
            if (!display_attach(&next, resource_one, budget))
            {
                return 0;
            }
            next.secondary.counter = 0;
            next.handler = 0x450b30;
        }
        else if (linked_present && next.phase != 1 &&
                 (linked_state ^ UINT32_C(0x80000000)) < (next.threshold ^ UINT32_C(0x80000000)))
        {
            next.primary.counter = 0;
            next.y = start_y;
            next.target_y = next.origin_y;
            next.step_y = 1;
            next.handler = 0x450aa0;
        }
    }
    else if (next.handler == 0x450b30)
    {
        vertrix_timer_advance(&next.secondary, elapsed);
        if (vertrix_timer_due(&next.secondary))
        {
            next.secondary.counter = 0;
            next.source = 1;
            next.effect = -40;
            next.effect_target = 5;
            next.effect_step = 1;
            next.primary.counter = 0;
            next.handler = 0x450b90;
        }
    }
    else
    {
        vertrix_timer_advance(&next.primary, elapsed);
        if (vertrix_timer_due(&next.primary))
        {
            uint32_t cycles = vertrix_timer_cycles(&next.primary);
            vertrix_timer_consume(&next.primary);
            if (next.handler == 0x450aa0)
            {
                if (!vertrix_word_transition(&next.y, next.target_y, next.step_y, cycles))
                {
                    if (!display_attach(&next, resource_other, budget))
                    {
                        return 0;
                    }
                    next.source = 1;
                    next.effect = -40;
                    next.effect_target = 5;
                    next.effect_step = 4;
                    next.primary.counter = 0;
                    next.handler = 0x450b90;
                }
            }
            else if (next.handler == 0x450bf0)
            {
                if (!vertrix_dword_transition(&next.delay, next.delay_target, next.delay_step,
                                              cycles))
                {
                    next.effect = 5;
                    next.effect_target = -60;
                    next.effect_step = next.phase == 1 ? 2 : 1;
                    next.handler = 0x450c70;
                }
            }
            else if (!vertrix_word_transition(&next.effect, next.effect_target, next.effect_step,
                                              cycles))
            {
                if (next.handler == 0x450b90)
                {
                    next.delay = 0;
                    next.delay_target = 1;
                    next.delay_step = 1;
                    next.handler = 0x450bf0;
                }
                else
                {
                    next.source = 0;
                    next.phase = 1 - next.phase;
                    next.handler = 0x450a10;
                }
            }
        }
    }
    *display = next;
    return 1;
}
