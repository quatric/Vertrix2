#include "block_spin.h"
#include "byte_transition.h"
#include "render_geometry.h"
#include "word_transition.h"
#include <limits.h>

static int16_t spin_word(uint32_t value)
{
    uint32_t word = (uint16_t)value;
    return (int16_t)(word < 32768 ? (int32_t)word : (int32_t)word - 65536);
}

int vertrix_block_spin_update(VertrixAnimation *animation, const uint32_t *frames, size_t storage,
                              uint32_t elapsed, uint32_t *descriptor, VertrixBlockSpin *spin,
                              VertrixRotationTrace *trace, const VertrixBlockOrbitContext *context)
{
    if (!animation || !descriptor || !spin || !trace || !context ||
        (spin->handler != 0x44ece0 && spin->handler != 0x44ee20))
    {
        return 0;
    }
    VertrixAnimation next_animation = *animation;
    VertrixBlockSpin next = *spin;
    VertrixRotationTrace next_trace = *trace;
    uint32_t selected = *descriptor;
    if (!vertrix_block_update(&next_animation, frames, storage, elapsed, &selected))
    {
        return 0;
    }
    next.field_93 = 1;
    int reveal = next.handler == 0x44ee20;
    uint32_t rotation_cycles = 0, fade_cycles = 0;
    vertrix_timer_advance(&next.rotation_timer, elapsed);
    if (vertrix_timer_due(&next.rotation_timer))
    {
        rotation_cycles = vertrix_timer_cycles(&next.rotation_timer);
        vertrix_timer_consume(&next.rotation_timer);
    }
    vertrix_timer_advance(&next.timer, elapsed);
    if (vertrix_timer_due(&next.timer))
    {
        fade_cycles = vertrix_timer_cycles(&next.timer);
        vertrix_timer_consume(&next.timer);
    }
    int rotating = vertrix_word_transition(&next.radius, next.rotation_target, next.rotation_change,
                                           rotation_cycles);
    vertrix_rotation_advance(&next.angle, next.rotation_step, rotation_cycles, &next_trace);
    next.amount_target = reveal ? 100 : 0;
    next.amount_step = 8;
    int fading =
        vertrix_byte_transition(&next.amount, next.amount_target, next.amount_step, fade_cycles);
    if (!rotating && !fading)
    {
        next.handler = 0x44c860;
        if (reveal)
        {
            next.field_93 = 0;
        }
    }
    uint32_t bits = 16u - (((uint32_t)(int32_t)next.radius << 4) / 100u);
    int32_t scale = bits <= INT32_MAX ? (int32_t)bits : -(int32_t)(UINT32_MAX - bits) - 1;
    next.mode = (uint8_t)(scale >= 16 ? 16 : scale);
    VertrixResourceDimensions dimensions = {context->width, context->height};
    int32_t width, height, offset_x, offset_y;
    if (!vertrix_resource_measure_state(&dimensions, dimensions, next.mode,
                                        context->screen_override, context->screen_unscaled,
                                        context->screen_mode, &width, &height) ||
        !vertrix_rotation_coordinates(context->tables, next.angle, next.radius, next.radius,
                                      &offset_x, &offset_y))
    {
        return 0;
    }
    next.x =
        spin_word((uint32_t)(int32_t)next.center_x + (uint32_t)offset_x - ((uint32_t)width >> 1));
    next.y =
        spin_word((uint32_t)(int32_t)next.center_y - (uint32_t)offset_y - ((uint32_t)height >> 1));
    *animation = next_animation;
    *spin = next;
    *trace = next_trace;
    *descriptor = selected;
    return 1;
}
