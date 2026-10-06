#include "block_orbit.h"
#include "byte_transition.h"
#include "dword_transition.h"
#include "render_geometry.h"
#include "word_transition.h"
#include <limits.h>

static int32_t orbit_signed(uint32_t bits)
{
    return bits <= INT32_MAX ? (int32_t)bits : -(int32_t)(UINT32_MAX - bits) - 1;
}

static int16_t orbit_word(uint32_t bits)
{
    uint32_t word = (uint16_t)bits;
    return (int16_t)(word < 32768 ? (int32_t)word : (int32_t)word - 65536);
}

static int orbit_second(VertrixBlockOrbit *next, VertrixRotationTrace *trace,
                        const VertrixBlockOrbitContext *context, uint32_t cycles)
{
    if (!vertrix_word_transition(&next->effect, next->effect_target, next->effect_step, cycles) &&
        next->effect_target == 100)
    {
        next->stage = 2;
    }
    next->y = next->origin_y;
    int moving_y = vertrix_word_transition(&next->y, next->target_y, next->step_y, cycles);
    next->origin_y = next->y;
    vertrix_rotation_advance(&next->angle, next->rotation_step, cycles, trace);
    int32_t radius = orbit_signed(next->parameter_64);
    vertrix_dword_transition(&radius, next->radius_target, orbit_signed(next->parameter_6c),
                             cycles);
    next->parameter_64 = (uint32_t)radius;
    int32_t offset_x, offset_y, width, height;
    if (!vertrix_rotation_coordinates(context->tables, next->angle, radius, radius, &offset_x,
                                      &offset_y))
    {
        return 0;
    }
    uint32_t scaled = ((uint32_t)offset_y * 5u) / 48u;
    next->mode = (uint8_t)(11u + scaled);
    if (next->mode >= 16)
    {
        next->mode = 16;
    }
    VertrixResourceDimensions dimensions = {context->width, context->height};
    if (!vertrix_resource_measure_state(&dimensions, dimensions, next->mode,
                                        context->screen_override, context->screen_unscaled,
                                        context->screen_mode, &width, &height))
    {
        return 0;
    }
    next->x =
        orbit_word((uint32_t)(int32_t)next->origin_x + (uint32_t)offset_x - ((uint32_t)width >> 1));
    next->y = orbit_word((uint32_t)(int32_t)next->origin_y - ((uint32_t)height >> 1));
    int changing = vertrix_dword_transition(&next->current, next->target, next->step, cycles);
    if (!moving_y || !changing)
    {
        next->handler = 0x44c860;
    }
    return 1;
}

static int orbit_centered(VertrixBlockOrbit *next, const VertrixBlockOrbitContext *context,
                          uint32_t cycles)
{
    int moving_x = 1, moving_y = 1;
    if (next->handler == 0x44e920 || next->handler == 0x44eaf0)
    {
        int finish = next->handler == 0x44eaf0;
        if (!vertrix_byte_transition(&next->mode, next->mode_target, next->mode_step, cycles))
        {
            next->handler = finish ? 0x44c860 : 0x44e9f0;
            if (finish)
            {
                next->field_93 = 0;
                next->amount = 50;
                next->field_95 = 1;
            }
        }
        next->effect = (int16_t)(4 * ((int32_t)next->mode - 16));
    }
    else
    {
        next->x = next->origin_x;
        next->y = next->origin_y;
        moving_x = vertrix_word_transition(&next->x, next->target_x, next->step_x, cycles);
        moving_y = vertrix_word_transition(&next->y, next->target_y, next->step_y, cycles);
        next->origin_x = next->x;
        next->origin_y = next->y;
    }
    VertrixResourceDimensions dimensions = {context->width, context->height};
    int32_t width, height;
    if (!vertrix_resource_measure_state(&dimensions, dimensions, next->mode,
                                        context->screen_override, context->screen_unscaled,
                                        context->screen_mode, &width, &height))
    {
        return 0;
    }
    next->x = orbit_word((uint32_t)(int32_t)next->origin_x + ((24u - (uint32_t)width) >> 1));
    next->y = orbit_word((uint32_t)(int32_t)next->origin_y + ((24u - (uint32_t)height) >> 1));
    if (!moving_x && !moving_y)
    {
        next->handler = 0x44c860;
        next->mode_target = 16;
        next->mode_step = 1;
    }
    return 1;
}

int vertrix_block_orbit_update(VertrixAnimation *animation, const uint32_t *frames, size_t storage,
                               uint32_t elapsed, uint32_t *descriptor, VertrixBlockOrbit *orbit,
                               VertrixRotationTrace *trace, const VertrixBlockOrbitContext *context)
{
    if (!animation || !descriptor || !orbit || !trace || !context ||
        (orbit->handler != 0x44de20 && orbit->handler != 0x44dfb0 && orbit->handler != 0x44e920 &&
         orbit->handler != 0x44e9f0 && orbit->handler != 0x44eaf0))
    {
        return 0;
    }
    VertrixAnimation next_animation = *animation;
    VertrixBlockOrbit next = *orbit;
    VertrixRotationTrace next_trace = *trace;
    uint32_t selected = *descriptor;
    if (!vertrix_block_update(&next_animation, frames, storage, elapsed, &selected))
    {
        return 0;
    }
    if (next.handler == 0x44de20 || next.handler == 0x44dfb0)
    {
        next.field_95 = 3;
    }
    if (next.handler == 0x44dfb0)
    {
        next.field_94 = 0;
    }
    vertrix_timer_advance(&next.timer, elapsed);
    if (vertrix_timer_due(&next.timer))
    {
        uint32_t cycles = vertrix_timer_cycles(&next.timer);
        vertrix_timer_consume(&next.timer);
        if (next.handler == 0x44e920 || next.handler == 0x44e9f0 || next.handler == 0x44eaf0)
        {
            if (!orbit_centered(&next, context, cycles))
            {
                return 0;
            }
        }
        else if (next.handler == 0x44dfb0)
        {
            if (!orbit_second(&next, &next_trace, context, cycles))
            {
                return 0;
            }
        }
        else
        {
            vertrix_rotation_advance(&next.angle, next.rotation_step, cycles, &next_trace);
            int32_t offset_x, offset_y, width, height;
            if (!vertrix_rotation_coordinates(context->tables, next.angle, 48, 5, &offset_x,
                                              &offset_y))
            {
                return 0;
            }
            uint8_t proposed = (uint8_t)(11u + (uint32_t)offset_y);
            if (proposed > 16)
            {
                proposed = 16;
            }
            VertrixResourceDimensions dimensions = {context->width, context->height};
            if (!vertrix_resource_measure_state(&dimensions, dimensions, next.mode,
                                                context->screen_override, context->screen_unscaled,
                                                context->screen_mode, &width, &height))
            {
                return 0;
            }
            next.target_x = orbit_word((uint32_t)(int32_t)next.origin_x + (uint32_t)offset_x -
                                       ((uint32_t)width >> 1));
            next.target_y = orbit_word((uint32_t)(int32_t)next.origin_y - ((uint32_t)height >> 1));
            next.mode_target = proposed;
            int moving_x = vertrix_word_transition(&next.x, next.target_x, next.step_x, cycles);
            int moving_y = vertrix_word_transition(&next.y, next.target_y, next.step_y, cycles);
            int changing_mode =
                vertrix_byte_transition(&next.mode, next.mode_target, next.mode_step, cycles);
            if (!moving_x && !moving_y && !changing_mode)
            {
                next.handler = 0x44dfb0;
                next.parameter_64 = 48;
                next.parameter_6c = 5;
                next.target_y = 0;
                next.step_x = 6;
                next.step_y = 6;
                next.rotation_step = 15;
                next.effect_target = 100;
                next.effect_step = 5;
            }
            if (!vertrix_dword_transition(&next.current, next.target, next.step, cycles))
            {
                next.handler = 0x44c860;
            }
        }
    }
    *animation = next_animation;
    *orbit = next;
    *trace = next_trace;
    *descriptor = selected;
    return 1;
}
