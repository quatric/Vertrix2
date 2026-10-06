#include "block_slide.h"
#include "byte_transition.h"
#include "word_transition.h"

static int16_t slide_word(uint32_t value)
{
    uint32_t word = (uint16_t)value;
    return (int16_t)(word < 32768 ? (int32_t)word : (int32_t)word - 65536);
}

int vertrix_block_slide_update(VertrixAnimation *animation, const uint32_t *frames, size_t storage,
                               uint32_t elapsed, uint32_t *descriptor, VertrixBlockSlide *slide)
{
    if (!animation || !descriptor || !slide ||
        (slide->handler != 0x44e250 && slide->handler != 0x44e2d0))
    {
        return 0;
    }
    VertrixAnimation next_animation = *animation;
    VertrixBlockSlide next = *slide;
    uint32_t selected = *descriptor;
    if (!vertrix_block_update(&next_animation, frames, storage, elapsed, &selected))
    {
        return 0;
    }
    if (next.handler == 0x44e250)
    {
        next.field_95 = 2;
    }
    vertrix_timer_advance(&next.timer, elapsed);
    if (vertrix_timer_due(&next.timer))
    {
        uint32_t cycles = vertrix_timer_cycles(&next.timer);
        vertrix_timer_consume(&next.timer);
        if (next.handler == 0x44e250)
        {
            int amount =
                vertrix_byte_transition(&next.amount, next.amount_target, next.amount_step, cycles);
            int effect =
                vertrix_word_transition(&next.effect, next.effect_target, next.effect_step, cycles);
            if (!amount && !effect)
            {
                next.handler = 0x44e2d0;
            }
        }
        else
        {
            int32_t difference = (int32_t)next.target_x - next.x;
            uint32_t absolute = (uint32_t)(difference < 0 ? -difference : difference);
            uint32_t distance = (uint32_t)(int32_t)slide_word(absolute);
            next.effect = slide_word((distance * 100u) / 60u);
            next.step_x = slide_word((distance * 4u) / 60u + 1u);
            if (!vertrix_word_transition(&next.x, next.target_x, next.step_x, cycles))
            {
                next.handler = 0x44c860;
            }
        }
    }
    *animation = next_animation;
    *slide = next;
    *descriptor = selected;
    return 1;
}
