#include "actor_fields.h"

enum
{
    ACTOR_COUNTER = 0xbc,
    ACTOR_PERIOD = 0xc0,
    ACTOR_HANDLER = 0x154,
    ACTOR_FRAME_INDEX = 0xb8,
    ACTOR_CC = 0xcc,
    ACTOR_D0 = 0xd0,
    PERIOD_STEP = 12,
    ACTOR_DONE = 0xdc,
    ACTOR_TOTAL = 0xe0,
    ACTOR_EC = 0xec,
    ACTOR_F0 = 0xf0,
    ACTOR_B4 = 0xb4,
    ACTOR_114 = 0x114,
    ACTOR_118 = 0x118,
    ACTOR_11C = 0x11c,
    ACTOR_WORDS_2A = 0x2a,
    ACTOR_WORDS_3A = 0x3a,
    ACTOR_X = 0xe,
    ACTOR_Y = 0x16,
    ACTOR_WIDTH = 0xf4,
    ACTOR_HEIGHT = 0xf8
};

int vertrix_actor_clear_counter(void *actor, size_t size)
{
    return vertrix_actor_storage_write(actor, size, ACTOR_COUNTER, 4, 0);
}

int vertrix_actor_set_period_steps(void *actor, size_t size, uint32_t steps)
{
    return vertrix_actor_storage_write(actor, size, ACTOR_PERIOD, 4, steps * PERIOD_STEP);
}

int vertrix_actor_set_period(void *actor, size_t size, uint32_t period)
{
    return vertrix_actor_storage_write(actor, size, ACTOR_PERIOD, 4, period);
}

int vertrix_actor_set_handler(void *actor, size_t size, uint32_t handler)
{
    return vertrix_actor_storage_write(actor, size, ACTOR_HANDLER, 4, handler);
}

int vertrix_actor_clear_cc(void *actor, size_t size)
{
    return vertrix_actor_storage_write(actor, size, ACTOR_CC, 4, 0);
}

int vertrix_actor_set_d0(void *actor, size_t size, uint32_t value)
{
    return vertrix_actor_storage_write(actor, size, ACTOR_D0, 4, value);
}

int vertrix_actor_set_frame_index(void *actor, size_t size, uint32_t index)
{
    return vertrix_actor_storage_write(actor, size, ACTOR_FRAME_INDEX, 4, index);
}

int vertrix_actor_set_d0_steps(void *actor, size_t size, uint32_t steps)
{
    return vertrix_actor_storage_write(actor, size, ACTOR_D0, 4, steps * PERIOD_STEP);
}

int vertrix_actor_get_handler(const void *actor, size_t size, uint32_t *handler)
{
    return vertrix_actor_storage_read(actor, size, ACTOR_HANDLER, 4, handler);
}

static int update(void *actor, size_t size, size_t offset, uint32_t (*step)(uint32_t))
{
    uint32_t value;
    return vertrix_actor_storage_read(actor, size, offset, 4, &value) &&
           vertrix_actor_storage_write(actor, size, offset, 4, step(value));
}

static uint32_t increment(uint32_t value)
{
    return value + 1;
}

static uint32_t decrement(uint32_t value)
{
    return value - 1;
}

static int reached(const void *actor, size_t size, size_t left, size_t right, uint32_t *flag)
{
    uint32_t a, b;
    if (!vertrix_actor_storage_read(actor, size, left, 4, &a) ||
        !vertrix_actor_storage_read(actor, size, right, 4, &b))
    {
        return 0;
    }
    *flag = a >= b;
    return 1;
}

static int quotient(const void *actor, size_t size, size_t dividend, size_t divisor,
                    uint32_t *result)
{
    uint32_t a, b;
    if (!vertrix_actor_storage_read(actor, size, dividend, 4, &a) ||
        !vertrix_actor_storage_read(actor, size, divisor, 4, &b))
    {
        return 0;
    }
    *result = a / (b ? b : 1);
    return 1;
}

static int copy_to_handler(void *actor, size_t size, size_t source)
{
    uint32_t value;
    return vertrix_actor_storage_read(actor, size, source, 4, &value) &&
           vertrix_actor_storage_write(actor, size, ACTOR_HANDLER, 4, value);
}

static int set_three_words(void *actor, size_t size, size_t offset, uint16_t a, uint16_t b,
                           uint16_t c)
{
    uint32_t probe;
    return vertrix_actor_storage_read(actor, size, offset + 4, 2, &probe) &&
           vertrix_actor_storage_write(actor, size, offset, 2, a) &&
           vertrix_actor_storage_write(actor, size, offset + 2, 2, b) &&
           vertrix_actor_storage_write(actor, size, offset + 4, 2, c);
}

int vertrix_actor_add_cc(void *actor, size_t size, uint32_t delta)
{
    uint32_t value;
    return vertrix_actor_storage_read(actor, size, ACTOR_CC, 4, &value) &&
           vertrix_actor_storage_write(actor, size, ACTOR_CC, 4, value + delta);
}

int vertrix_actor_cc_reached(const void *actor, size_t size, uint32_t *flag)
{
    return reached(actor, size, ACTOR_CC, ACTOR_D0, flag);
}

int vertrix_actor_counter_reached(const void *actor, size_t size, uint32_t *flag)
{
    return reached(actor, size, ACTOR_COUNTER, ACTOR_PERIOD, flag);
}

int vertrix_actor_counter_quotient(const void *actor, size_t size, uint32_t *result)
{
    return quotient(actor, size, ACTOR_COUNTER, ACTOR_PERIOD, result);
}

int vertrix_actor_progress_quotient(const void *actor, size_t size, uint32_t *result)
{
    return quotient(actor, size, ACTOR_DONE, ACTOR_TOTAL, result);
}

int vertrix_actor_reset_frame_counter(void *actor, size_t size)
{
    return vertrix_actor_storage_write(actor, size, ACTOR_FRAME_INDEX, 4, 0);
}

int vertrix_actor_next_frame_counter(void *actor, size_t size)
{
    return update(actor, size, ACTOR_FRAME_INDEX, increment);
}

int vertrix_actor_previous_frame_counter(void *actor, size_t size)
{
    return update(actor, size, ACTOR_FRAME_INDEX, decrement);
}

int vertrix_actor_frame_counter_is_zero(const void *actor, size_t size, uint32_t *zero)
{
    uint32_t value;
    if (!vertrix_actor_storage_read(actor, size, ACTOR_FRAME_INDEX, 4, &value))
    {
        return 0;
    }
    *zero = value == 0;
    return 1;
}

int vertrix_actor_set_e0_steps(void *actor, size_t size, uint32_t steps)
{
    return vertrix_actor_storage_write(actor, size, ACTOR_TOTAL, 4, steps * PERIOD_STEP);
}

int vertrix_actor_set_e0(void *actor, size_t size, uint32_t value)
{
    return vertrix_actor_storage_write(actor, size, ACTOR_TOTAL, 4, value);
}

int vertrix_actor_set_ec(void *actor, size_t size, uint32_t value)
{
    return vertrix_actor_storage_write(actor, size, ACTOR_EC, 4, value);
}

int vertrix_actor_set_f0(void *actor, size_t size, uint32_t value)
{
    return vertrix_actor_storage_write(actor, size, ACTOR_F0, 4, value);
}

int vertrix_actor_set_b4(void *actor, size_t size, uint32_t value)
{
    return vertrix_actor_storage_write(actor, size, ACTOR_B4, 4, value);
}

int vertrix_actor_get_b4(const void *actor, size_t size, uint32_t *value)
{
    return vertrix_actor_storage_read(actor, size, ACTOR_B4, 4, value);
}

int vertrix_actor_handler_from_ec(void *actor, size_t size)
{
    return copy_to_handler(actor, size, ACTOR_EC);
}

int vertrix_actor_handler_from_f0(void *actor, size_t size)
{
    return copy_to_handler(actor, size, ACTOR_F0);
}

int vertrix_actor_set_114(void *actor, size_t size, uint32_t first, uint32_t second)
{
    uint32_t probe;
    return vertrix_actor_storage_read(actor, size, ACTOR_118, 4, &probe) &&
           vertrix_actor_storage_write(actor, size, ACTOR_114, 4, first) &&
           vertrix_actor_storage_write(actor, size, ACTOR_118, 4, second);
}

int vertrix_actor_set_11c(void *actor, size_t size, uint32_t value)
{
    return vertrix_actor_storage_write(actor, size, ACTOR_11C, 4, value);
}

int vertrix_actor_set_words_2a(void *actor, size_t size, uint16_t a, uint16_t b, uint16_t c)
{
    return set_three_words(actor, size, ACTOR_WORDS_2A, a, b, c);
}

int vertrix_actor_set_words_3a(void *actor, size_t size, uint16_t a, uint16_t b, uint16_t c)
{
    return set_three_words(actor, size, ACTOR_WORDS_3A, a, b, c);
}

int vertrix_actor_set_box(void *actor, size_t size, uint16_t x, uint16_t y, uint16_t width,
                          uint16_t height)
{
    uint32_t probe;
    return vertrix_actor_storage_read(actor, size, ACTOR_HEIGHT, 4, &probe) &&
           vertrix_actor_storage_write(actor, size, ACTOR_X, 2, x) &&
           vertrix_actor_storage_write(actor, size, ACTOR_Y, 2, y) &&
           vertrix_actor_storage_write(actor, size, ACTOR_WIDTH, 4, width) &&
           vertrix_actor_storage_write(actor, size, ACTOR_HEIGHT, 4, height);
}

static int wrap(void *actor, size_t size, size_t dividend, size_t divisor, uint32_t *consumed)
{
    uint32_t a, b, product;
    if (!vertrix_actor_storage_read(actor, size, dividend, 4, &a) ||
        !vertrix_actor_storage_read(actor, size, divisor, 4, &b))
    {
        return 0;
    }
    b = b ? b : 1;
    product = (a / b) * b;
    if (!vertrix_actor_storage_write(actor, size, dividend, 4, product >= a ? 0 : a - product))
    {
        return 0;
    }
    if (consumed)
    {
        *consumed = product;
    }
    return 1;
}

int vertrix_actor_counter_wrap(void *actor, size_t size)
{
    return wrap(actor, size, ACTOR_COUNTER, ACTOR_PERIOD, NULL);
}

int vertrix_actor_progress_wrap(void *actor, size_t size)
{
    return wrap(actor, size, ACTOR_DONE, ACTOR_TOTAL, NULL);
}

uint32_t vertrix_actor_counter_consume(void *actor, size_t size)
{
    uint32_t consumed = 0;
    wrap(actor, size, ACTOR_COUNTER, ACTOR_PERIOD, &consumed);
    return consumed;
}

uint32_t vertrix_actor_progress_consume(void *actor, size_t size)
{
    uint32_t consumed = 0;
    wrap(actor, size, ACTOR_DONE, ACTOR_TOTAL, &consumed);
    return consumed;
}
