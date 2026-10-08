#include "particle_spawn.h"
#include "actor_fields.h"
#include "object_access.h"

enum
{
    FIELD_X = 0xe,
    FIELD_Y = 0x16,
    FIELD_VELOCITY_X = 0x8,
    FIELD_VELOCITY_Y = 0xa,
    FIELD_LIFE = 0x60,
    FIELD_TIMER = 0x5c,
    FIELD_START = 0x58,
    FIELD_BANK = 0xb0,
    FIELD_FRAME = 0xb8,
    FIELD_CC = 0xcc,
    FIELD_SCENE_MODE = 0x94c,
    FIELD_SPARKLE = 0x95,
    FIELD_WORD_28 = 0x28,
    FIELD_144 = 0x144,
    SPREAD_RESOURCE = 0x544c10,
    SPREAD_FRAME = 0xf,
    SPREAD_SCALE = 0x96,
    SCENE_FAST_PERIOD = 0xc,
    SCENE_SLOW_PERIOD = 5,
    SPREAD_START = 0xc8,
    DRIFT_RESOURCE = 0x544c64,
    DRIFT_HANDLER = 0x4574a0,
    DRIFT_PERIOD = 5,
    DRIFT_LIFE_FIELD = 0x70,
    DRIFT_BASE_FIELD = 0x64,
    DRIFT_BASE = 0x64,
    DRIFT_LIFE_RANGE = 0xc8,
    FLAG_93 = 0x93,
    POWER_4E = 0x4e,
    KIND_44 = 0x44,
    SPARKLE_ROW_OFFSET = 0x136,
    SPARKLE_TABLE_COUNT = 5
};

/* Tables at 0x4fb93c and 0x4fb950. */
static const uint32_t sparkle_x[SPARKLE_TABLE_COUNT] = {58, 375, 513, 227, 333};
static const uint32_t sparkle_y[SPARKLE_TABLE_COUNT] = {192, 182, 208, 25, 27};

static int field_write(const VertrixSpawnServices *services, uint32_t handle, size_t offset,
                       unsigned width, uint32_t value)
{
    return vertrix_object_write(handle, services->resolve, services->context, offset, width, value);
}

/* Original 0x4ac8d0 (resource attach, clearing +0xcc and the frame), 0x4ac710 (frame) and 0x4ac8a0
 * (image binding), which the particle routines call in sequence. */
static int attach_and_bind(const VertrixSpawnServices *services, uint32_t child, uint32_t resource,
                           uint32_t frame)
{
    void *storage;
    size_t size;
    if (!field_write(services, child, FIELD_CC, 4, 0) ||
        !field_write(services, child, FIELD_FRAME, 4, 0) ||
        !field_write(services, child, FIELD_BANK, 4, resource) ||
        !field_write(services, child, FIELD_FRAME, 4, frame))
    {
        return 0;
    }
    return services->resolve(child, &storage, &size, services->context) &&
           vertrix_actor_lookup_image(storage, size, services->lookup, services->context);
}

static int set_period(const VertrixSpawnServices *services, uint32_t child, uint32_t period,
                      int steps)
{
    void *storage;
    size_t size;
    if (!services->resolve(child, &storage, &size, services->context))
    {
        return 0;
    }
    return steps ? vertrix_actor_set_period_steps(storage, size, period)
                 : vertrix_actor_set_period(storage, size, period);
}

static void fill_scratch(VertrixSpawnScratch *scratch, uint16_t width, uint16_t height)
{
    scratch->width = width;
    scratch->height = height;
    scratch->half_width = (uint16_t)(width / 2);
    scratch->half_height = (uint16_t)(height / 2);
}

/* Velocity word: (draw - half) * 150, wrapping at 16 bits. */
static uint32_t velocity(const VertrixSpawnServices *services, uint16_t range, uint16_t half)
{
    uint16_t value = services->draw(range, services->context);
    return (uint16_t)((uint16_t)(value - half) * SPREAD_SCALE);
}

static int place_and_move(const VertrixSpawnServices *services, uint32_t child,
                          const VertrixSpawnScratch *scratch)
{
    return field_write(services, child, FIELD_X, 2, 0) &&
           field_write(services, child, FIELD_Y, 2, 0) &&
           field_write(services, child, FIELD_VELOCITY_X, 2,
                       velocity(services, scratch->width, scratch->half_width)) &&
           field_write(services, child, FIELD_VELOCITY_Y, 2,
                       velocity(services, scratch->height, scratch->half_height));
}

int vertrix_spawn_spread(uint32_t scene, uint32_t child, uint16_t width, uint16_t height,
                         VertrixSpawnScratch *scratch, const VertrixSpawnServices *services)
{
    uint32_t mode;
    uint32_t life;
    fill_scratch(scratch, width, height);
    if (!attach_and_bind(services, child, SPREAD_RESOURCE, SPREAD_FRAME) ||
        !vertrix_object_read(scene, services->resolve, services->context, FIELD_SCENE_MODE, 4,
                             &mode) ||
        !set_period(services, child, mode == 1 ? SCENE_FAST_PERIOD : SCENE_SLOW_PERIOD, 0) ||
        !place_and_move(services, child, scratch) ||
        !vertrix_object_read(scene, services->resolve, services->context, FIELD_SCENE_MODE, 4,
                             &mode) ||
        !field_write(services, child, FIELD_START, 4, SPREAD_START) ||
        !field_write(services, child, FIELD_TIMER, 4, 0))
    {
        return 0;
    }
    life = services->draw(2, services->context);
    if (mode == 1 && !field_write(services, child, FIELD_WORD_28, 2, 1))
    {
        return 0;
    }
    return field_write(services, child, FIELD_LIFE, 4, life + 1);
}

int vertrix_spawn_burst(uint32_t child, uint16_t width, uint16_t height,
                        VertrixSpawnScratch *scratch, const VertrixSpawnServices *services)
{
    uint32_t life;
    fill_scratch(scratch, width, height);
    if (!attach_and_bind(services, child, SPREAD_RESOURCE, SPREAD_FRAME) ||
        !set_period(services, child, 1, 1) || !place_and_move(services, child, scratch) ||
        !field_write(services, child, FIELD_START, 4, SPREAD_START) ||
        !field_write(services, child, FIELD_TIMER, 4, 0))
    {
        return 0;
    }
    life = services->draw(3, services->context);
    return field_write(services, child, FIELD_144, 4, 0) &&
           field_write(services, child, FIELD_LIFE, 4, life + 1);
}

int vertrix_spawn_drift(uint32_t child, uint16_t width, uint16_t height,
                        VertrixSpawnScratch *scratch, const VertrixSpawnServices *services)
{
    void *storage;
    size_t size;
    uint16_t x;
    uint16_t y;
    uint32_t life;
    scratch->width = width;
    scratch->height = height;
    if (!attach_and_bind(services, child, DRIFT_RESOURCE, 0) ||
        !set_period(services, child, DRIFT_PERIOD, 1) ||
        !field_write(services, child, FIELD_VELOCITY_X, 2, width) ||
        !field_write(services, child, FIELD_VELOCITY_Y, 2, height))
    {
        return 0;
    }
    x = services->draw(width, services->context);
    if (!field_write(services, child, FIELD_X, 2, x))
    {
        return 0;
    }
    y = services->draw(height, services->context);
    if (!field_write(services, child, FIELD_Y, 2, y) ||
        !services->resolve(child, &storage, &size, services->context) ||
        !vertrix_actor_set_handler(storage, size, DRIFT_HANDLER) ||
        !field_write(services, child, FIELD_START, 4, 0) ||
        !field_write(services, child, FIELD_LIFE, 4, 1) ||
        !field_write(services, child, DRIFT_LIFE_FIELD, 4, DRIFT_LIFE_RANGE) ||
        !field_write(services, child, DRIFT_BASE_FIELD, 4, DRIFT_BASE))
    {
        return 0;
    }
    life = services->draw(DRIFT_LIFE_RANGE, services->context);
    return field_write(services, child, FLAG_93, 1, 1) &&
           field_write(services, child, POWER_4E, 1, 0) &&
           field_write(services, child, KIND_44, 1, 0) &&
           field_write(services, child, FIELD_TIMER, 4, DRIFT_BASE + life);
}

int vertrix_spawn_place(uint32_t child, const VertrixSpawnServices *services)
{
    uint32_t mode;
    uint32_t width;
    uint32_t height;
    if (!vertrix_object_read(child, services->resolve, services->context, FIELD_FRAME, 4, &mode) ||
        !field_write(services, child, FIELD_SPARKLE, 1, (mode == 1) + 4))
    {
        return 0;
    }
    if (!vertrix_object_read(child, services->resolve, services->context, FIELD_FRAME, 4, &mode))
    {
        return 0;
    }
    if (mode == 2)
    {
        uint16_t row;
        if (!vertrix_object_read(child, services->resolve, services->context, FIELD_VELOCITY_X, 2,
                                 &width) ||
            !field_write(services, child, FIELD_X, 2,
                         services->draw((uint16_t)width, services->context)) ||
            !vertrix_object_read(child, services->resolve, services->context, FIELD_VELOCITY_Y, 2,
                                 &height))
        {
            return 0;
        }
        row = services->draw((uint16_t)(height - SPARKLE_ROW_OFFSET), services->context);
        return field_write(services, child, FIELD_Y, 2, row + SPARKLE_ROW_OFFSET);
    }
    {
        uint16_t index = services->draw(SPARKLE_TABLE_COUNT, services->context);
        return field_write(services, child, FIELD_X, 2, sparkle_x[index]) &&
               field_write(services, child, FIELD_Y, 2, sparkle_y[index]);
    }
}

int vertrix_spawn_spread_full(uint32_t scene, uint32_t child, VertrixMemoryRead read,
                              VertrixMemoryWrite write, void *context, const VertrixCalls *calls,
                              uint32_t *result)
{
    if (!read || !write || !calls || !calls->call || !result)
    {
        return 0;
    }
    uint32_t width, height, half, range, value, mode;
    if (!read(0x5b9c8e, 2, &width, context) || !write(0x540fd4, 2, width, context) ||
        !read(0x5b9c90, 2, &height, context) || !read(0x5b9c8e, 2, &width, context) ||
        !write(0x540fd6, 2, height, context) || !read(0x5b9c90, 2, &height, context) ||
        !write(0x540fd8, 2, width / 2, context) || !write(0x540fda, 2, height / 2, context) ||
        !write(child + 0xcc, 4, 0, context) || !write(child + 0xb8, 4, 0, context) ||
        !write(child + 0xb0, 4, SPREAD_RESOURCE, context) || !write(child + 0xb8, 4, 15, context))
    {
        return 0;
    }
    vertrix_call(calls, 0x4ac8a0, child, 15, scene, child, 0);
    if (!read(scene + 0x94c, 4, &mode, context) ||
        !write(child + 0xc0, 4, mode == 1 ? 12 : 5, context) ||
        !write(child + 0xe, 2, 0, context) || !read(0x540fd4, 2, &range, context) ||
        !write(child + 0x16, 2, 0, context))
    {
        return 0;
    }
    value = vertrix_call(calls, 0x4826c0, 0x598d30, range, scene, child, 0);
    if (!read(0x540fd8, 2, &half, context) || !read(0x540fd6, 2, &range, context) ||
        !write(child + 8, 2, (uint16_t)(value - half) * 150u, context))
    {
        return 0;
    }
    value = vertrix_call(calls, 0x4826c0, 0x598d30, range, scene, child, 0);
    if (!read(0x540fda, 2, &half, context) ||
        !write(child + 0xa, 2, (uint16_t)(value - half) * 150u, context) ||
        !read(scene + 0x94c, 4, &mode, context) || !write(child + 0x58, 4, 200, context) ||
        !write(child + 0x5c, 4, 0, context))
    {
        return 0;
    }
    value = (vertrix_call(calls, 0x4826c0, 0x598d30, 2, scene, child, 0) & 0xffff) + 1;
    if ((mode == 1 && !write(child + 0x28, 2, 1, context)) ||
        !write(child + 0x60, 4, value, context))
    {
        return 0;
    }
    *result = value;
    return 1;
}

int vertrix_spawn_place_full(uint32_t child, uint32_t ebx, VertrixMemoryRead read,
                             VertrixMemoryWrite write, void *context, const VertrixCalls *calls,
                             uint32_t *result)
{
    if (!read || !write || !calls || !calls->call || !result)
    {
        return 0;
    }
    uint32_t x[5], y[5], first_mode, mode, range, value;
    for (unsigned i = 0; i < 5; ++i)
    {
        if (!read(0x4fb93c + 4 * i, 4, &x[i], context))
        {
            return 0;
        }
    }
    for (unsigned i = 0; i < 5; ++i)
    {
        if (!read(0x4fb950 + 4 * i, 4, &y[i], context))
        {
            return 0;
        }
    }
    if (!read(child + 0xb8, 4, &first_mode, context) || !read(child + 0xb8, 4, &mode, context) ||
        !write(child + 0x95, 1, first_mode == 1 ? 5 : 4, context))
    {
        return 0;
    }
    if (mode != 2)
    {
        value = vertrix_call(calls, 0x4826c0, 0x598d30, 5, ebx, child, 0);
        unsigned index = value & 0xffff;
        if (index >= 5 || !write(child + 0xe, 2, x[index], context) ||
            !write(child + 0x16, 2, y[index], context))
        {
            return 0;
        }
        value = (value & 0xffff0000u) | (y[index] & 0xffff);
    }
    else
    {
        if (!read(child + 8, 2, &range, context))
        {
            return 0;
        }
        value = vertrix_call(calls, 0x4826c0, 0x598d30, range, ebx, child, 0);
        if (!write(child + 0xe, 2, value, context) || !read(child + 0xa, 2, &range, context))
        {
            return 0;
        }
        value = vertrix_call(calls, 0x4826c0, 0x598d30, (range - 0x136) & 0xffff, ebx, child, 0) +
                0x136;
        if (!write(child + 0x16, 2, value, context))
        {
            return 0;
        }
    }
    *result = value;
    return 1;
}
