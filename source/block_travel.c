#include "block_travel.h"
#include "dword_transition.h"
#include "word_transition.h"

int vertrix_block_travel_update(VertrixAnimation *animation, const uint32_t *frames, size_t storage,
                                uint32_t elapsed, uint32_t *descriptor, VertrixBlockTravel *travel)
{
    if (!animation || !descriptor || !travel ||
        (travel->handler != 0x44ebe0 && travel->handler != 0x44ec40))
    {
        return 0;
    }
    VertrixAnimation next_animation = *animation;
    VertrixBlockTravel next = *travel;
    uint32_t selected = *descriptor;
    if (!vertrix_block_update(&next_animation, frames, storage, elapsed, &selected))
    {
        return 0;
    }
    vertrix_timer_advance(&next.timer, elapsed);
    if (vertrix_timer_due(&next.timer))
    {
        uint32_t cycles = vertrix_timer_cycles(&next.timer);
        vertrix_timer_consume(&next.timer);
        if (next.handler == 0x44ebe0)
        {
            if (!vertrix_dword_transition(&next.current, next.target, next.step, cycles))
            {
                next.handler = 0x44ec40;
            }
        }
        else
        {
            next.x = next.origin_x;
            next.y = next.origin_y;
            int moving_x = vertrix_word_transition(&next.x, next.target_x, next.step_x, cycles);
            int moving_y = vertrix_word_transition(&next.y, next.target_y, next.step_y, cycles);
            next.origin_x = next.x;
            next.origin_y = next.y;
            if (!moving_x && !moving_y)
            {
                next.handler = 0x44c860;
            }
        }
    }
    *animation = next_animation;
    *travel = next;
    *descriptor = selected;
    return 1;
}
