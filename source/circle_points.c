#include "circle_points.h"

#include "actor_storage.h"

enum
{
    DWORD_WIDTH = 4,
    WORD_WIDTH = 2,
    SURFACE_WIDTH = 4,
    SURFACE_HEIGHT = 8,
    STATE_BASE = 0x558a60,
    STATE_X = 0x558a64,
    STATE_Y = 0x558a66,
    STATE_D = 0x558a68,
    STATE_TEST_Y = 0x558a6c,
    STATE_TEST_D = 0x558a6e,
    STATE_CENTRE_X = 0x558a70,
    STATE_CENTRE_Y = 0x558a74,
    PLOT = 0x479df0,
    WORD_MASK = 0xffff
};

typedef struct Circle
{
    const VertrixFactoryServices *services;
    int ok;
} Circle;

static uint32_t state_read(Circle *c, uint32_t address, unsigned width)
{
    void *storage;
    size_t size;
    uint32_t value = 0;
    if (!c->services->resolve(VERTRIX_CIRCLE_STATE, &storage, &size, c->services->context) ||
        !vertrix_actor_storage_read(storage, size, address - STATE_BASE, width, &value))
    {
        c->ok = 0;
    }
    return value;
}

static void state_write(Circle *c, uint32_t address, unsigned width, uint32_t value)
{
    void *storage;
    size_t size;
    if (!c->services->resolve(VERTRIX_CIRCLE_STATE, &storage, &size, c->services->context) ||
        !vertrix_actor_storage_write(storage, size, address - STATE_BASE, width, value))
    {
        c->ok = 0;
    }
}

static int32_t signed_word(Circle *c, uint32_t address)
{
    return (int16_t)state_read(c, address, WORD_WIDTH);
}

int vertrix_circle_points(const VertrixCalls *calls, const VertrixFactoryServices *services,
                          uint32_t surface, uint32_t argument, uint32_t radius)
{
    Circle circle = {services, 1};
    Circle *c = &circle;
    void *storage;
    size_t size;
    uint32_t width, height;
    if (!services->resolve(surface, &storage, &size, services->context) ||
        !vertrix_actor_storage_read(storage, size, SURFACE_WIDTH, DWORD_WIDTH, &width) ||
        !vertrix_actor_storage_read(storage, size, SURFACE_HEIGHT, DWORD_WIDTH, &height))
    {
        return 0;
    }
    state_write(c, STATE_CENTRE_X, DWORD_WIDTH, width >> 1);
    state_write(c, STATE_Y, WORD_WIDTH, radius & WORD_MASK);
    state_write(c, STATE_CENTRE_Y, DWORD_WIDTH, height >> 1);
    state_write(c, STATE_X, WORD_WIDTH, 0);
    state_write(c, STATE_D, WORD_WIDTH, (2u - 2u * radius) & WORD_MASK);
    while (c->ok)
    {
        int32_t x = signed_word(c, STATE_X), y = signed_word(c, STATE_Y);
        int32_t d = signed_word(c, STATE_D);
        uint32_t centre_x = state_read(c, STATE_CENTRE_X, DWORD_WIDTH);
        uint32_t centre_y = state_read(c, STATE_CENTRE_Y, DWORD_WIDTH);
        vertrix_call(calls, PLOT, surface, argument, (uint32_t)x + centre_x, centre_y - (uint32_t)y,
                     0);
        vertrix_call(calls, PLOT, surface, argument, centre_x - (uint32_t)x, centre_y - (uint32_t)y,
                     0);
        vertrix_call(calls, PLOT, surface, argument, centre_x - (uint32_t)x, (uint32_t)y + centre_y,
                     0);
        vertrix_call(calls, PLOT, surface, argument, (uint32_t)x + centre_x, (uint32_t)y + centre_y,
                     0);
        if (y <= 0)
        {
            return c->ok;
        }
        enum
        {
            HORIZONTAL,
            DIAGONAL,
            VERTICAL
        } move;
        if (d < 0)
        {
            state_write(c, STATE_TEST_Y, WORD_WIDTH, (uint32_t)(2 * y + 2 * d - 1) & WORD_MASK);
            move = signed_word(c, STATE_TEST_Y) <= 0 ? HORIZONTAL : DIAGONAL;
        }
        else if (d == 0)
        {
            move = DIAGONAL;
        }
        else
        {
            state_write(c, STATE_TEST_D, WORD_WIDTH, (uint32_t)(2 * d - 2 * x - 1) & WORD_MASK);
            move = signed_word(c, STATE_TEST_D) <= 0 ? DIAGONAL : VERTICAL;
        }
        if (move == VERTICAL)
        {
            y--;
            state_write(c, STATE_Y, WORD_WIDTH, (uint32_t)y & WORD_MASK);
            d = d - 2 * y + 1;
        }
        else if (move == DIAGONAL)
        {
            x++;
            y--;
            state_write(c, STATE_X, WORD_WIDTH, (uint32_t)x & WORD_MASK);
            state_write(c, STATE_Y, WORD_WIDTH, (uint32_t)y & WORD_MASK);
            d = 2 * x + d - 2 * y + 2;
        }
        else
        {
            x++;
            state_write(c, STATE_X, WORD_WIDTH, (uint32_t)x & WORD_MASK);
            d = 2 * x + d + 1;
        }
        state_write(c, STATE_D, WORD_WIDTH, (uint32_t)d & WORD_MASK);
    }
    return 0;
}
