#include "player_indicator.h"
#include <stddef.h>

int vertrix_player_countdown_update(VertrixPlayerCountdown *countdown, uint32_t player_value,
                                    uint32_t *player_flag, uint32_t elapsed)
{
    if (!countdown || !player_flag ||
        (countdown->handler != 0x450750 && countdown->handler != 0x4507e0 &&
         countdown->handler != 0x450830))
    {
        return 0;
    }
    VertrixPlayerCountdown next = *countdown;
    if (next.handler == 0x450750)
    {
        next.value = 0;
        next.target = *player_flag == 1 ? 0 : player_value;
        vertrix_timer_advance(&next.secondary, elapsed);
        if (vertrix_timer_due(&next.secondary))
        {
            next.secondary.counter = 0;
            if ((next.state ^ UINT32_C(0x80000000)) > (next.target ^ UINT32_C(0x80000000)))
            {
                next.state--;
            }
        }
        if (*player_flag == 1 && next.state == next.target)
        {
            *player_flag = 0;
            next.primary.counter = 0;
            next.handler = 0x4507e0;
        }
    }
    else
    {
        vertrix_timer_advance(&next.primary, elapsed);
        if (vertrix_timer_due(&next.primary))
        {
            next.primary.counter = 0;
            if (next.handler == 0x4507e0)
            {
                next.value = 1;
                next.state = 12;
                next.target = 12;
                next.handler = 0x450830;
            }
            else
            {
                next.handler = 0x450750;
            }
        }
    }
    *countdown = next;
    return 1;
}

int vertrix_player_indicator_update(VertrixPlayerIndicator *indicator, uint32_t player_state,
                                    uint32_t elapsed, int *notify)
{
    if (!indicator || !notify ||
        (indicator->handler != 0x44fe80 && indicator->handler != 0x44fed0 &&
         indicator->handler != 0x44ff30 && indicator->handler != 0x44ff60))
    {
        return 0;
    }
    VertrixPlayerIndicator next = *indicator;
    int request = 0;
    switch (next.handler)
    {
        case 0x44fe80:
            next.value = 0;
            next.state = player_state;
            if (player_state == 3)
            {
                next.primary.counter = 0;
                next.handler = 0x44fed0;
            }
            break;
        case 0x44fed0:
            vertrix_timer_advance(&next.primary, elapsed);
            if (vertrix_timer_due(&next.primary))
            {
                next.primary.counter = 0;
                next.secondary.counter = 0;
                next.value = 1;
                next.state = 0;
                request = 1;
                next.handler = 0x44ff30;
            }
            break;
        case 0x44ff30:
            vertrix_timer_advance(&next.secondary, elapsed);
            if (vertrix_timer_due(&next.secondary))
            {
                next.secondary.counter = 0;
                next.handler = 0x44ff60;
            }
            break;
        case 0x44ff60:
            if (player_state != 3)
            {
                next.handler = 0x44fe80;
            }
            break;
    }
    *indicator = next;
    *notify = request;
    return 1;
}
