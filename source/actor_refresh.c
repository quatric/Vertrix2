#include "actor_refresh.h"

enum
{
    WORD_WIDTH = 2,
    WORD_MASK = 0xffff,
    HIGH_MASK = 0xffff0000u,
    HALF_SHIFT = 16,
    REFRESH_PREPARE = 0x4ac600,
    REFRESH_STATE = 0x4ac620,
    REFRESH_ACTIVE = 1,
    REFRESH_MODE = 0x4ac640,
    REFRESH_APPLY = 0x4ac6b0,
    REFRESH_BUSY = 0x4ad060,
    REFRESH_DRAW = 0x4826c0,
    REFRESH_DRAW_TABLE = 0x598d30,
    REFRESH_DRAW_DIVISOR = 5,
    REFRESH_STEP = 0x4ac860,
    REFRESH_ANGLE = 0x4ad1c0,
    REFRESH_CHANGED = 0x4adfe0,
    REFRESH_DRAW_WORD = 0x30,
    REFRESH_Y = 0x16,
    REFRESH_OFFSET = 0xa,
    REFRESH_X = 0xe,
    REFRESH_ANGLE_FIELD = 0x2e,
    REFRESH_LOCAL_RESULT = 0x1c,
    REFRESH_LOCAL_COPY = 0x20,
    REFRESH_STATE_FIELD = 0x58,
    REFRESH_FRAME_SHIFT = 4
};

static int read_field(const VertrixFactoryServices *services, uint32_t object, uint32_t offset,
                      unsigned width, uint32_t *value)
{
    void *storage;
    size_t size;
    return services->resolve(object, &storage, &size, services->context) &&
           vertrix_actor_storage_read(storage, size, offset, width, value);
}

static int write_field(const VertrixFactoryServices *services, uint32_t object, uint32_t offset,
                       unsigned width, uint32_t value)
{
    void *storage;
    size_t size;
    return services->resolve(object, &storage, &size, services->context) &&
           vertrix_actor_storage_write(storage, size, offset, width, value);
}

uint32_t vertrix_actor_refresh(const VertrixCalls *calls, const VertrixFactoryServices *services,
                               uint32_t frame, uint32_t object, uint32_t edx, uint32_t ebx,
                               uint32_t ecx)
{
    uint32_t result, mode, last, draw, y, angle, x, offset, delta, sum, stack[1];
    vertrix_call(calls, REFRESH_PREPARE, object, edx, ebx, ecx, 0);
    result = vertrix_call(calls, REFRESH_STATE, object, edx, ebx, ecx, 0);
    if (result != REFRESH_ACTIVE)
    {
        return result;
    }
    mode = vertrix_call(calls, REFRESH_MODE, object, edx, ebx, ecx, 0);
    vertrix_call(calls, REFRESH_APPLY, object, mode, ebx, ecx, 0);
    last = vertrix_call(calls, REFRESH_BUSY, object, mode, ebx, ecx, 0);
    if (last == 0)
    {
        draw = vertrix_call(calls, REFRESH_DRAW, REFRESH_DRAW_TABLE, REFRESH_DRAW_DIVISOR, ebx, ecx,
                            0);
        if (!write_field(services, object, REFRESH_DRAW_WORD, WORD_WIDTH, draw))
        {
            return 0;
        }
        draw = vertrix_call(calls, REFRESH_DRAW, REFRESH_DRAW_TABLE, REFRESH_DRAW_DIVISOR, ebx, ecx,
                            0);
        last = vertrix_call(calls, REFRESH_STEP, object, (draw & WORD_MASK) + REFRESH_DRAW_DIVISOR,
                            ebx, ecx, 0);
    }
    if (!read_field(services, object, REFRESH_Y, WORD_WIDTH, &y) ||
        !read_field(services, object, REFRESH_ANGLE_FIELD, 4, &angle) ||
        !read_field(services, object, REFRESH_X, WORD_WIDTH, &x))
    {
        return 0;
    }
    angle = (uint32_t)((int32_t)angle >> HALF_SHIFT);
    stack[0] = frame - REFRESH_LOCAL_RESULT;
    result = vertrix_calln(calls, REFRESH_ANGLE, object, angle, angle, frame - REFRESH_LOCAL_COPY,
                           stack, 1, &delta);
    if (!read_field(services, object, REFRESH_OFFSET, WORD_WIDTH, &offset))
    {
        return 0;
    }
    sum = ((angle & HIGH_MASK) | offset) + delta;
    if (!write_field(services, object, REFRESH_Y, WORD_WIDTH, sum))
    {
        return 0;
    }
    if ((sum & WORD_MASK) == y)
    {
        uint32_t current;
        if (!read_field(services, object, REFRESH_X, WORD_WIDTH, &current))
        {
            return 0;
        }
        if (x == current)
        {
            return result;
        }
    }
    return vertrix_call(calls, REFRESH_CHANGED, object, sum, delta, (last & HIGH_MASK) | y, 0);
}

uint32_t vertrix_actor_refresh_if_active(const VertrixCalls *calls,
                                         const VertrixFactoryServices *services, uint32_t frame,
                                         uint32_t object, uint32_t edx, uint32_t ebx, uint32_t ecx)
{
    uint32_t state;
    if (!read_field(services, object, REFRESH_STATE_FIELD, 4, &state))
    {
        return 0;
    }
    if (state != REFRESH_ACTIVE)
    {
        return object;
    }
    return vertrix_actor_refresh(calls, services, frame - REFRESH_FRAME_SHIFT, object, edx, ebx,
                                 ecx);
}
