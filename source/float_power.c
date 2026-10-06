#include "float_power.h"

#include "actor_storage.h"

enum
{
    DWORD_WIDTH = 4,
    CLASSIFY = 0x4dad19,
    SPLIT = 0x4dae1e,
    TO_INTEGER = 0x4eb892,
    NEGATE = 0x4dae4a,
    LOGARITHM = 0x4c9e2f,
    MULTIPLY = 0x4db507,
    ABSOLUTE = 0x4dae62,
    COMPARE = 0x4eb57c,
    EXPONENTIAL = 0x4daed8,
    DIVIDE = 0x4eb652,
    RAISE = 0x4dad38,
    UNDERFLOW = 0x4dae94,
    LARGE_LOW = 0xfefa39efu,
    LARGE_HIGH = 0x40862e42u,
    ONE_HIGH = 0x3ff00000u,
    LOCAL_X = 0x24,
    LOCAL_WORK = 0x1c,
    LOCAL_Y = 0x14,
    LOCAL_EXPONENT = 0xc,
    ERROR_ZERO_NEGATIVE = 0x8047,
    ERROR_ZERO = 0x4047,
    ERROR_NEGATIVE_ROOT = 0x2047,
    ERROR_OVERFLOW = 0x8107,
    ERROR_NEGATIVE_OVERFLOW = 0x1107,
    NO_EXPONENT = 0x80000000u,
    SHIFT = 32
};

typedef struct Power
{
    const VertrixCalls *calls;
    const VertrixFactoryServices *services;
    uint32_t frame;
    int ok;
} Power;

static uint32_t local_get(Power *p, uint32_t below)
{
    void *storage;
    size_t size;
    uint32_t value = 0;
    if (!p->services->resolve(p->frame - VERTRIX_FLOAT_POWER_FRAME, &storage, &size,
                              p->services->context) ||
        !vertrix_actor_storage_read(storage, size, VERTRIX_FLOAT_POWER_FRAME - below, DWORD_WIDTH,
                                    &value))
    {
        p->ok = 0;
    }
    return value;
}

static void local_put(Power *p, uint32_t below, uint32_t value)
{
    void *storage;
    size_t size;
    if (!p->services->resolve(p->frame - VERTRIX_FLOAT_POWER_FRAME, &storage, &size,
                              p->services->context) ||
        !vertrix_actor_storage_write(storage, size, VERTRIX_FLOAT_POWER_FRAME - below, DWORD_WIDTH,
                                     value))
    {
        p->ok = 0;
    }
}

static void put_pair(Power *p, uint32_t below, uint32_t low, uint32_t high)
{
    local_put(p, below, low);
    local_put(p, below - DWORD_WIDTH, high);
}

/* A float helper: the result's low dword is the call's eax and the high dword its out_value. */
static uint32_t helper(Power *p, uint32_t target, uint32_t eax, uint32_t edx, uint32_t ebx,
                       uint32_t ecx, uint32_t *high)
{
    VertrixCallSite site = {target, eax, edx, ebx, ecx, 0, 0, 0, 0, 0, {0}, 0};
    uint32_t low = p->calls->call(&site, p->calls->context);
    *high = site.out_value;
    return low;
}

/* The finish every helper call that answers the result shares: store it and answer it. */
static int finish(Power *p, uint64_t *result, uint32_t low, uint32_t high)
{
    put_pair(p, LOCAL_X, low, high);
    *result = ((uint64_t)high << SHIFT) | low;
    return p->ok;
}

int vertrix_float_power(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        uint32_t frame, uint32_t x_low, uint32_t x_high, uint32_t y_low,
                        uint32_t y_high, uint64_t *result)
{
    Power state = {calls, services, frame, 1};
    Power *p = &state;
    uint32_t classify, sign, fraction_low, fraction_high, exponent, work_low, work_high;
    uint32_t log_low, log_high, ebx, ecx, high, low, compare, base_low, base_high;
    put_pair(p, LOCAL_X, x_low, x_high);
    put_pair(p, LOCAL_Y, y_low, y_high);
    classify = vertrix_call(calls, CLASSIFY, x_low, x_high, y_low, y_high, 0);
    sign = classify;
    if (classify == 0)
    {
        if (y_high != 0 && (int32_t)y_high >= 0)
        {
            *result = ((uint64_t)x_high << SHIFT) | x_low;
            return p->ok;
        }
        low = helper(p, RAISE, (int32_t)y_high < 0 ? ERROR_ZERO_NEGATIVE : ERROR_ZERO,
                     frame - LOCAL_X, frame - LOCAL_Y, classify, &high);
        return finish(p, result, low, high);
    }
    fraction_low = helper(p, SPLIT, y_low, y_high, frame - LOCAL_WORK, classify, &fraction_high);
    (void)fraction_low;
    exponent = vertrix_call(calls, TO_INTEGER, local_get(p, LOCAL_WORK),
                            local_get(p, LOCAL_WORK - DWORD_WIDTH), fraction_high, classify, 0);
    local_put(p, LOCAL_EXPONENT, exponent);
    ebx = fraction_high;
    if ((int32_t)classify < 0)
    {
        if (fraction_high != 0)
        {
            low = helper(p, RAISE, ERROR_NEGATIVE_ROOT, frame - LOCAL_X, frame - LOCAL_Y, classify,
                         &high);
            *result = ((uint64_t)high << SHIFT) | low;
            return p->ok;
        }
        low = helper(p, NEGATE, x_low, x_high, ebx, classify, &high);
        put_pair(p, LOCAL_X, low, high);
        if ((local_get(p, LOCAL_EXPONENT) & 1) == 0)
        {
            sign = 0;
        }
    }
    log_low = helper(p, LOGARITHM, local_get(p, LOCAL_X), local_get(p, LOCAL_X - DWORD_WIDTH), ebx,
                     classify, &log_high);
    work_low = helper(p, MULTIPLY, log_low, log_high, y_low, y_high, &work_high);
    put_pair(p, LOCAL_WORK, work_low, work_high);
    low = helper(p, ABSOLUTE, work_low, work_high, LARGE_LOW, LARGE_HIGH, &high);
    compare = vertrix_call(calls, COMPARE, low, high, LARGE_LOW, LARGE_HIGH, 0);
    ebx = LARGE_LOW;
    ecx = LARGE_HIGH;
    if ((int32_t)compare > 0)
    {
        if ((int32_t)work_high >= 0)
        {
            low = helper(p, RAISE, (int32_t)sign > 0 ? ERROR_OVERFLOW : ERROR_NEGATIVE_OVERFLOW,
                         frame - LOCAL_X, frame - LOCAL_Y, ecx, &high);
            return finish(p, result, low, high);
        }
        vertrix_call(calls, UNDERFLOW, compare, high, ebx, 0, 0);
        put_pair(p, LOCAL_X, 0, 0);
        *result = 0;
        return p->ok;
    }
    exponent = local_get(p, LOCAL_EXPONENT);
    if (fraction_high != 0 || exponent == NO_EXPONENT)
    {
        low = helper(p, EXPONENTIAL, work_low, work_high, ebx, ecx, &high);
        put_pair(p, LOCAL_X, low, high);
    }
    else
    {
        if ((int32_t)exponent < 0)
        {
            ebx = local_get(p, LOCAL_X);
            ecx = local_get(p, LOCAL_X - DWORD_WIDTH);
            exponent = 0u - exponent;
            local_put(p, LOCAL_EXPONENT, exponent);
            low = helper(p, DIVIDE, 0, ONE_HIGH, ebx, ecx, &high);
            put_pair(p, LOCAL_X, low, high);
        }
        if (exponent != 1)
        {
            put_pair(p, LOCAL_WORK, 0, ONE_HIGH);
            while (p->ok && (exponent = local_get(p, LOCAL_EXPONENT)) != 0)
            {
                base_low = local_get(p, LOCAL_X);
                base_high = local_get(p, LOCAL_X - DWORD_WIDTH);
                if ((exponent & 1) != 0)
                {
                    low =
                        helper(p, MULTIPLY, local_get(p, LOCAL_WORK),
                               local_get(p, LOCAL_WORK - DWORD_WIDTH), base_low, base_high, &high);
                    put_pair(p, LOCAL_WORK, low, high);
                }
                ebx = base_low;
                ecx = base_high;
                low = helper(p, MULTIPLY, base_low, base_high, ebx, ecx, &high);
                ebx = (uint32_t)((int32_t)exponent >> 1);
                put_pair(p, LOCAL_X, low, high);
                local_put(p, LOCAL_EXPONENT, ebx);
            }
            put_pair(p, LOCAL_X, local_get(p, LOCAL_WORK), local_get(p, LOCAL_WORK - DWORD_WIDTH));
        }
    }
    if ((int32_t)sign < 0)
    {
        low = helper(p, NEGATE, local_get(p, LOCAL_X), local_get(p, LOCAL_X - DWORD_WIDTH), ebx,
                     ecx, &high);
        put_pair(p, LOCAL_X, low, high);
    }
    *result = ((uint64_t)local_get(p, LOCAL_X - DWORD_WIDTH) << SHIFT) | local_get(p, LOCAL_X);
    return p->ok;
}
