#include "float_exp.h"

#include "actor_storage.h"

enum
{
    DWORD_WIDTH = 4,
    BYTE_WIDTH = 1,
    ABSOLUTE = 0x4dae62,
    COMPARE = 0x4eb57c,
    MULTIPLY = 0x4db507,
    ADD = 0x4db350,
    SUBTRACT = 0x4db34a,
    DIVIDE = 0x4eb652,
    SCALE = 0x4e5271,
    SPLIT = 0x4dae1e,
    TO_INTEGER = 0x4eb892,
    CLASSIFY = 0x4dad19,
    RAISE = 0x4dad2e,
    HARDWARE = 0x4e51c8,
    SMALL_LOW = 0xf368cb40u,
    SMALL_HIGH = 0x3cc003c9u,
    LARGE_LOW = 0xfefa39efu,
    LARGE_HIGH = 0x40862e42u,
    LOG2E_LOW = 0x652b8301u,
    LOG2E_HIGH = 0x3ff71547u,
    ONE_HIGH = 0x3ff00000u,
    OVERFLOW_CODE = 0x8104,
    POLY_A_LOW = 0x4f237e45u,
    POLY_A_HIGH = 0x4034d053u,
    POLY_B_LOW = 0x1ac13af9u,
    POLY_B_HIGH = 0x3fad92deu,
    POLY_C_LOW = 0xa35ca6dcu,
    POLY_C_HIGH = 0x401cdaa0u,
    LOCAL_VALUE = 0x3c,
    LOCAL_INTEGER = 0x34,
    SIXTEEN = 4,
    SHIFT = 32
};

typedef struct Exp
{
    const VertrixCalls *calls;
    const VertrixFactoryServices *services;
    uint32_t frame;
    int ok;
} Exp;

static uint32_t get(Exp *e, uint32_t handle, size_t offset)
{
    void *storage;
    size_t size;
    uint32_t value = 0;
    if (!e->services->resolve(handle, &storage, &size, e->services->context) ||
        !vertrix_actor_storage_read(storage, size, offset, DWORD_WIDTH, &value))
    {
        e->ok = 0;
    }
    return value;
}

/* A float helper: the result's low dword is the call's eax and the high dword its out_value. */
static uint32_t helper(Exp *e, uint32_t target, uint32_t eax, uint32_t edx, uint32_t ebx,
                       uint32_t ecx, uint32_t *high)
{
    VertrixCallSite site = {target, eax, edx, ebx, ecx, 0, 0, 0, 0, 0, {0}, 0};
    uint32_t low = e->calls->call(&site, e->calls->context);
    *high = site.out_value;
    return low;
}

static uint32_t integer_part(Exp *e, uint32_t offset)
{
    return get(e, e->frame - VERTRIX_FLOAT_EXP_FRAME, offset);
}

int vertrix_float_exp(const VertrixCalls *calls, const VertrixFactoryServices *services,
                      uint32_t frame, uint32_t low, uint32_t high, uint32_t ebx, uint32_t ecx,
                      uint64_t *result)
{
    Exp state = {calls, services, frame, 1};
    Exp *e = &state;
    uint32_t absolute_low, absolute_high, value_low, value_high, fraction_low, fraction_high;
    uint32_t classify, power, nibble = 0, ecx_fraction, ebx_next, i;
    uint32_t a_low, a_high, w_low, w_high, p_low, p_high, q_low, q_high, s_low, s_high;
    uint32_t t_low, t_high, entry, edx;
    uint32_t flag;
    *result = 0;
    absolute_low = helper(e, ABSOLUTE, low, high, ebx, ecx, &absolute_high);
    if ((int32_t)vertrix_call(calls, COMPARE, absolute_low, absolute_high, SMALL_LOW, SMALL_HIGH,
                              0) < 0)
    {
        *result = (uint64_t)ONE_HIGH << SHIFT;
        return 1;
    }
    if ((int32_t)vertrix_call(calls, COMPARE, absolute_low, absolute_high, LARGE_LOW, LARGE_HIGH,
                              0) > 0)
    {
        if ((int32_t)high >= 0)
        {
            value_low = helper(e, RAISE, OVERFLOW_CODE, frame - LOCAL_VALUE, LARGE_LOW, LARGE_HIGH,
                               &value_high);
            *result = ((uint64_t)value_high << SHIFT) | value_low;
        }
        return 1;
    }
    {
        uint32_t byte;
        void *storage;
        size_t size;
        if (!services->resolve(VERTRIX_FLOAT_EXP_FLAG, &storage, &size, services->context) ||
            !vertrix_actor_storage_read(storage, size, 0, BYTE_WIDTH, &byte))
        {
            return 0;
        }
        flag = byte;
    }
    if (flag != 0)
    {
        value_low = helper(e, HARDWARE, low, high, LARGE_LOW, LARGE_HIGH, &value_high);
        *result = ((uint64_t)value_high << SHIFT) | value_low;
        return 1;
    }
    value_low = helper(e, MULTIPLY, low, high, LOG2E_LOW, LOG2E_HIGH, &value_high);
    classify = vertrix_call(calls, CLASSIFY, value_low, value_high, LOG2E_LOW, LOG2E_HIGH, 0);
    absolute_low = helper(e, ABSOLUTE, value_low, value_high, frame - LOCAL_INTEGER, LOG2E_HIGH,
                          &absolute_high);
    fraction_low = helper(e, SPLIT, absolute_low, absolute_high, frame - LOCAL_INTEGER, LOG2E_HIGH,
                          &fraction_high);
    power = vertrix_call(calls, TO_INTEGER, integer_part(e, 0), integer_part(e, DWORD_WIDTH),
                         fraction_low, fraction_high, 0);
    ecx_fraction = fraction_high;
    if ((int32_t)classify < 0)
    {
        power = 0u - power;
        if (fraction_high != 0)
        {
            power -= 1;
            fraction_low =
                helper(e, SUBTRACT, 0, ONE_HIGH, fraction_low, fraction_high, &fraction_high);
            /* the original keeps the old high dword in ecx; fraction_high now holds 1 - f */
        }
    }
    if (fraction_high != 0)
    {
        ebx_next = frame - LOCAL_INTEGER;
        a_low = helper(e, SCALE, fraction_low, fraction_high, SIXTEEN, ecx_fraction, &a_high);
        fraction_low =
            helper(e, SPLIT, a_low, a_high, frame - LOCAL_INTEGER, ecx_fraction, &fraction_high);
        if (fraction_high != 0)
        {
            ebx_next = 0xfffffffcu;
            fraction_low = helper(e, SCALE, fraction_low, fraction_high, ebx_next, ecx_fraction,
                                  &fraction_high);
        }
        nibble = vertrix_call(calls, TO_INTEGER, integer_part(e, 0), integer_part(e, DWORD_WIDTH),
                              ebx_next, ecx_fraction, 0);
    }
    s_low = helper(e, MULTIPLY, fraction_low, fraction_high, fraction_low, fraction_high, &s_high);
    a_low = helper(e, ADD, s_low, s_high, POLY_A_LOW, POLY_A_HIGH, &a_high);
    t_low = helper(e, MULTIPLY, s_low, s_high, POLY_B_LOW, POLY_B_HIGH, &t_high);
    t_low = helper(e, ADD, t_low, t_high, POLY_C_LOW, POLY_C_HIGH, &t_high);
    w_low = helper(e, MULTIPLY, t_low, t_high, fraction_low, fraction_high, &w_high);
    p_low = helper(e, ADD, a_low, a_high, w_low, w_high, &p_high);
    q_low = helper(e, SUBTRACT, a_low, a_high, w_low, w_high, &q_high);
    value_low = helper(e, DIVIDE, p_low, p_high, q_low, q_high, &value_high);
    ecx = q_high;
    entry = VERTRIX_FLOAT_EXP_TABLE;
    for (i = 0, edx = nibble; edx != 0; edx = (uint32_t)((int32_t)edx >> 1), i++)
    {
        if ((edx & 1) != 0)
        {
            uint32_t table_low = get(e, entry, 8 * i), table_high = get(e, entry, 8 * i + 4);
            value_low =
                helper(e, MULTIPLY, value_low, value_high, table_low, table_high, &value_high);
            ecx = table_high;
        }
    }
    value_low = helper(e, SCALE, value_low, value_high, power, ecx, &value_high);
    *result = ((uint64_t)value_high << SHIFT) | value_low;
    return e->ok;
}
