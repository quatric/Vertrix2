#include "port_float.h"

enum
{
    EXPONENT = 0x7ff00000,
    SIGN = 0x80000000u,
    SINGLE_MAGNITUDE = 0x7fffffff,
    SINGLE_INFINITY = 0x7f800000,
    SINGLE_HIDDEN = 0x800000,
    /* 1023 - 127 in the double's exponent field */
    REBIAS = 0x38000000,
    FLOAT_TO_INTEGER = 0x4d67f0,
    FLOAT_TO_SIGNED = 0x4d67e4,
    INT32_LIMIT = 0x9e,
    UINT32_LIMIT = 0x9f,
    UNSIGNED_TO_SINGLE = 0x4d74a6,
    MANTISSA_HIGH = 0xfffff,
    EXPONENT_UNIT = 0x100000,
    DOUBLE_NORMALIZE = 0x4e5177,
    DOUBLE_SPLIT = 0x4e509c,
    SCALE_OVERFLOW = 0x4dae94,
    DOUBLE_NEGATE = 0x4dae4a,
    DOUBLE_INFINITY = 0x51ab90,
    DOUBLE_MULTIPLY = 0x4db507,
    DOUBLE_ADD = 0x4db350
};

uint32_t vertrix_port_double_compare(PORT_SIGNATURE)
{
    Port port;
    LiftFlags fl = {0, 0, 0, 0, 0, 0};
    uint32_t low = entry->eax;
    uint32_t high = entry->edx;
    uint32_t other_low = entry->ebx;
    uint32_t other_high = entry->ecx;
    uint32_t negative;
    uint32_t answer;
    port_open(&port, calls, services, globals, entry);
    if ((high & EXPONENT) == 0)
    {
        high = 0;
    }
    if ((other_high & EXPONENT) == 0)
    {
        other_high = 0;
    }
    if (((high ^ other_high) & SIGN) == 0)
    {
        uint32_t below;
        if (high == other_high && low == other_low)
        {
            (void)lift_sub(32, low, other_low, &fl);
            vertrix_lift_fl = fl;
            return port_return(&port, 0, high);
        }
        /* rcr puts "below" (unsigned) on top of the other high dword; its top bit against the sign
         * gives the answer. */
        below = high != other_high ? high < other_high : low < other_low;
        high ^= (below << 31) | (other_high >> 1);
    }
    negative = high >> 31;
    high <<= 1;
    answer = lift_add(32, 0u - negative, 0u - negative, &fl);
    answer = lift_inc(32, answer, &fl, 1);
    vertrix_lift_fl = fl;
    return port_return(&port, answer, high);
}

uint32_t vertrix_port_single_to_double(PORT_SIGNATURE)
{
    Port port;
    uint32_t low = entry->eax;
    uint32_t high = low & SINGLE_MAGNITUDE;
    uint32_t sign;
    port_open(&port, calls, services, globals, entry);
    if (high == 0)
    {
        return port_return(&port, low, 0);
    }
    if (high == SINGLE_INFINITY)
    {
        return port_return(&port, 0, low | EXPONENT);
    }
    if ((high & SINGLE_INFINITY) == 0)
    {
        uint32_t scale = 0;
        low ^= high;
        do
        {
            scale += SINGLE_HIDDEN;
            high <<= 1;
        } while ((high & SINGLE_HIDDEN) == 0);
        low |= high;
        high -= scale;
    }
    high = (uint32_t)((int32_t)high >> 2);
    sign = low >> 31;
    low <<= 1;
    high = (sign << 31) | (high >> 1);
    low &= 0xe;
    low = (low >> 4) | (low << 28);
    return port_return(&port, low, high + REBIAS);
}

/* The body of 0x4d67f0: `limit` is cl. */
static uint32_t float_to_integer(uint32_t bits, uint32_t limit)
{
    uint32_t exponent;
    uint32_t significand;
    if (bits == 0)
    {
        return 0;
    }
    bits <<= 1;
    bits = (bits << 8) | (bits >> 24);
    exponent = bits & 0xff;
    if (exponent < 0x7f)
    {
        return 0;
    }
    significand = (SIGN | (bits >> 1)) >> 8;
    limit &= 0xff;
    if (exponent >= limit)
    {
        return port_shr(0xffffffffu, (0x9f - limit) & 0xff);
    }
    if (exponent >= 0x96)
    {
        return port_shl(significand, exponent - 0x96);
    }
    return port_shr(significand, (0x96 - exponent) & 0xff);
}

uint32_t vertrix_port_float_to_integer(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    return port_return(&port, float_to_integer(entry->eax, entry->ecx), entry->edx);
}

uint32_t vertrix_port_float_to_signed(PORT_SIGNATURE)
{
    Port port;
    uint32_t value;
    port_open(&port, calls, services, globals, entry);
    if ((int32_t)entry->eax >= 0)
    {
        return port_return(&port, float_to_integer(entry->eax, entry->ecx), entry->edx);
    }
    value = port_call(&port, FLOAT_TO_INTEGER, entry->eax, entry->edx, entry->ebx, entry->ecx);
    return port_return(&port, 0u - value, vertrix_lift_edx);
}

uint32_t vertrix_port_float_to_int32(PORT_SIGNATURE)
{
    Port port;
    uint32_t value;
    port_open(&port, calls, services, globals, entry);
    value = port_call(&port, FLOAT_TO_SIGNED, entry->eax, entry->edx, entry->ebx,
                      (entry->ecx & 0xffffff00u) | INT32_LIMIT);
    return port_return(&port, value, vertrix_lift_edx);
}

uint32_t vertrix_port_int_to_double(PORT_SIGNATURE)
{
    Port port;
    uint32_t value = entry->eax;
    uint32_t biased = 0x3ff;
    uint32_t top;
    uint32_t high;
    port_open(&port, calls, services, globals, entry);
    if ((int32_t)value < 0)
    {
        value = 0u - value;
        biased = 0xbff;
    }
    if (value == 0)
    {
        return port_return(&port, 0, 0);
    }
    top = lift_bsr(value);
    value <<= 31 - top;
    value <<= 1;
    high = (value & 0xfffff000u) | (top + biased);
    return port_return(&port, value << 20, (high >> 12) | (high << 20));
}

uint32_t vertrix_port_double_absolute(PORT_SIGNATURE)
{
    Port port;
    uint32_t high = entry->edx;
    port_open(&port, calls, services, globals, entry);
    if ((int32_t)high < 0)
    {
        high ^= SIGN;
    }
    return port_return(&port, entry->eax, high);
}

uint32_t vertrix_port_double_sign(PORT_SIGNATURE)
{
    Port port;
    int32_t high = (int32_t)entry->edx;
    port_open(&port, calls, services, globals, entry);
    return port_return(&port, high == 0 ? 0u : high < 0 ? 0xffffffffu : 1u, entry->edx);
}

uint32_t vertrix_port_single_negate(PORT_SIGNATURE)
{
    Port port;
    uint32_t value = entry->eax;
    port_open(&port, calls, services, globals, entry);
    return port_return(&port, value == 0 ? 0 : value ^ SIGN, entry->edx);
}

uint32_t vertrix_port_double_to_single(PORT_SIGNATURE)
{
    Port port;
    uint64_t value = ((uint64_t)entry->edx << 32) | entry->eax;
    uint32_t sign = entry->edx & SIGN;
    uint32_t high;
    port_open(&port, calls, services, globals, entry);
    if ((entry->edx & EXPONENT) == 0)
    {
        return port_return(&port, 0, entry->edx);
    }
    /* Shift the sign out and round: the mantissa's 24th bit is bit 29 of the low dword. */
    value = (value << 1) + 0x20000000u;
    high = (uint32_t)(value >> 32);
    if (high == 0 || high >= 0x8fe00000u)
    {
        return port_return(&port, SINGLE_INFINITY | sign, high);
    }
    if (high < 0x70200000u)
    {
        return port_return(&port, 0, high);
    }
    value -= (uint64_t)0x70000000u << 32;
    high = (uint32_t)((value << 2) >> 32) | sign;
    return port_return(&port, high, high);
}

uint32_t vertrix_port_double_to_int(PORT_SIGNATURE)
{
    Port port;
    uint32_t sign = entry->edx >> 31;
    uint32_t high = entry->edx & ~SIGN;
    int32_t shift = (int32_t)((high >> 20) & 0x7ff) - 0x3fe;
    uint32_t top;
    uint32_t value;
    port_open(&port, calls, services, globals, entry);
    if (shift < 0)
    {
        return port_return(&port, 0, high);
    }
    if (shift >= 0x20)
    {
        return port_return(&port, SIGN, high);
    }
    /* The implicit one and the 31 mantissa bits after it. */
    top = SIGN | ((((high & 0xfffff) << 12) | (entry->eax >> 20)) >> 1);
    value = shift == 0 ? 0 : top >> (32 - shift);
    return port_return(&port, sign ? 0u - value : value, (top << shift) << 1);
}

/* The body of 0x4d74a6. */
static uint32_t unsigned_to_single(uint32_t value)
{
    uint32_t top;
    uint32_t turn;
    if (value == 0)
    {
        return 0;
    }
    top = lift_bsr(value);
    /* rol by (23 - top) mod 32 puts the top bit at bit 23; the bits above are masked off. */
    turn = (0x17 - top) & 0x1f;
    value = turn == 0 ? value : (value << turn) | (value >> (32 - turn));
    return (value & 0x7fffff) | (((top + 0x7f) & 0xff) << 23);
}

uint32_t vertrix_port_unsigned_to_single(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    return port_return(&port, unsigned_to_single(entry->eax), entry->edx);
}

uint32_t vertrix_port_signed_to_single(PORT_SIGNATURE)
{
    Port port;
    uint32_t value;
    port_open(&port, calls, services, globals, entry);
    if ((int32_t)entry->eax >= 0)
    {
        return port_return(&port, unsigned_to_single(entry->eax), entry->edx);
    }
    value =
        port_call(&port, UNSIGNED_TO_SINGLE, 0u - entry->eax, entry->edx, entry->ebx, entry->ecx);
    return port_return(&port, value | SIGN, vertrix_lift_edx);
}

uint32_t vertrix_port_double_normalize(PORT_SIGNATURE)
{
    Port port;
    uint64_t mantissa = ((uint64_t)entry->edx << 32) | entry->eax;
    uint32_t exponent = entry->edi;
    port_open(&port, calls, services, globals, entry);
    if (mantissa == 0)
    {
        return port_return(&port, 0, 0);
    }
    if ((mantissa >> 52) == 0)
    {
        while ((mantissa >> 52) == 0)
        {
            exponent -= EXPONENT_UNIT;
            mantissa <<= 1;
        }
    }
    else if ((mantissa >> 53) != 0)
    {
        uint32_t last = 0;
        while ((mantissa >> 53) != 0)
        {
            exponent += EXPONENT_UNIT;
            last = (uint32_t)mantissa & 1;
            mantissa >>= 1;
        }
        mantissa += last;
    }
    return port_return(&port, (uint32_t)mantissa,
                       ((uint32_t)(mantissa >> 32) & MANTISSA_HIGH) | exponent);
}

uint32_t vertrix_port_double_split(PORT_SIGNATURE)
{
    Port port;
    uint32_t value = entry->eax;
    uint32_t whole = entry->edx;
    uint32_t low;
    uint32_t high;
    uint32_t field;
    uint32_t power;
    uint32_t keep_high;
    uint32_t keep_low = 0;
    uint32_t fraction;
    uint32_t fraction_high;
    port_open(&port, calls, services, globals, entry);
    low = port_u32(&port, value, 0);
    high = port_u32(&port, value, 4);
    port_set32(&port, whole, 0, low);
    port_set32(&port, whole, 4, high);
    field = high & EXPONENT;
    if (field >= 0x43300000u)
    {
        /* From 2^52 there are no fraction bits: the fraction is 0. */
        port_set32(&port, value, 4, 0);
        port_set32(&port, value, 0, 0);
        return port_return(&port, 0, high);
    }
    if (field < 0x3ff00000u)
    {
        /* Below 1 (or a zero exponent) the integer part is 0 and the double is the fraction. */
        port_set32(&port, whole, 4, 0);
        port_set32(&port, whole, 0, 0);
        return port_return(&port, 0, high);
    }
    /* The masks keep the sign, the exponent and the integer bits of the mantissa. */
    power = (field >> 20) - 0x3ff;
    if (power <= 20)
    {
        keep_high = (uint32_t)((int32_t)0xfff00000u >> power);
    }
    else
    {
        power -= 21;
        keep_high = 0xffffffffu;
        keep_low = (uint32_t)((int32_t)0x80000000u >> power);
    }
    port_set32(&port, whole, 4, port_u32(&port, whole, 4) & keep_high);
    port_set32(&port, whole, 0, port_u32(&port, whole, 0) & keep_low);
    fraction_high = ~keep_high & port_u32(&port, value, 4);
    fraction = ~keep_low & port_u32(&port, value, 0);
    fraction = port_call_with(&port, DOUBLE_NORMALIZE, fraction, fraction_high, entry->ebx, power,
                              value, field, value);
    fraction_high = vertrix_lift_edx;
    if (fraction_high != 0)
    {
        fraction_high |= high & SIGN;
    }
    port_set32(&port, value, 4, fraction_high);
    port_set32(&port, value, 0, fraction);
    return port_return(&port, fraction, fraction_high);
}

uint32_t vertrix_port_double_split_call(PORT_SIGNATURE)
{
    Port port;
    uint32_t base = entry->esp - 4; /* the original's ebp */
    uint32_t fraction;
    uint32_t fraction_high;
    port_open_frame(&port, calls, services, globals, entry, 0x14);
    port_set32(&port, base, 0, entry->ebp);
    port_set32(&port, base, (uint32_t)-8, entry->eax);
    port_set32(&port, base, (uint32_t)-4, entry->edx);
    port_call(&port, DOUBLE_SPLIT, base - 8, base - 0x10, entry->ebx, entry->ecx);
    port_set32(&port, entry->ebx, 0, port_u32(&port, base, (uint32_t)-0x10));
    port_set32(&port, entry->ebx, 4, port_u32(&port, base, (uint32_t)-0xc));
    fraction = port_u32(&port, base, (uint32_t)-8);
    fraction_high = port_u32(&port, base, (uint32_t)-4);
    return port_return(&port, fraction, fraction_high);
}

uint32_t vertrix_port_double_scale(PORT_SIGNATURE)
{
    const int32_t scale_limit = 16000;
    Port port;
    uint32_t low = entry->eax;
    uint32_t high = entry->edx;
    int32_t power = (int32_t)entry->ebx;
    int32_t exponent;
    uint32_t top;
    port_open(&port, calls, services, globals, entry);
    if (high == 0)
    {
        return port_return(&port, low, high);
    }
    top = high >> 16;
    exponent = (int32_t)((top & 0x7ff0) >> 4);
    power = power > scale_limit ? scale_limit : power < -scale_limit ? -scale_limit : power;
    exponent += power;
    if (exponent <= 0)
    {
        return port_return(&port, 0, 0);
    }
    if (exponent >= 0x7ff)
    {
        uint32_t edx;
        port_call(&port, SCALE_OVERFLOW, (uint32_t)exponent, high, (uint32_t)power,
                  (entry->ecx << 16) | top);
        low = port_u32(&port, 0, DOUBLE_INFINITY);
        edx = port_u32(&port, 0, DOUBLE_INFINITY + 4);
        /* The sign test reads cx, the high dword's top 16 bits (lifted callers keep ecx). */
        if ((int16_t)top > 0)
        {
            return port_return(&port, low, edx);
        }
        low = port_call(&port, DOUBLE_NEGATE, low, edx, (uint32_t)power, (entry->ecx << 16) | top);
        return port_return(&port, low, vertrix_lift_edx);
    }
    high = (high & 0x800fffffu) | ((uint32_t)exponent << 20);
    return port_return(&port, low, high);
}

uint32_t vertrix_port_double_exponent_split(PORT_SIGNATURE)
{
    Port port;
    uint32_t low = entry->eax;
    uint32_t high = entry->edx;
    uint32_t exponent = 0;
    port_open(&port, calls, services, globals, entry);
    if (high != 0)
    {
        exponent = ((high >> 20) & 0x7ff) - 0x3fe;
        high = (high & 0x800fffffu) | 0x3fe00000u;
    }
    port_set32(&port, entry->ebx, 0, exponent);
    return port_return(&port, low, high);
}

uint32_t vertrix_port_double_polynomial(PORT_SIGNATURE)
{
    Port port;
    uint32_t coefficient = entry->ebx;
    uint32_t count = entry->ecx;
    uint32_t low;
    uint32_t high;
    port_open(&port, calls, services, globals, entry);
    low = port_u32(&port, coefficient, 0);
    high = port_u32(&port, coefficient, 4);
    do
    {
        low = port_call(&port, DOUBLE_MULTIPLY, low, high, entry->eax, entry->edx);
        coefficient += 8;
        low = port_call(&port, DOUBLE_ADD, low, vertrix_lift_edx, port_u32(&port, coefficient, 0),
                        port_u32(&port, coefficient, 4));
        high = vertrix_lift_edx;
    } while (--count != 0);
    return port_return(&port, low, high);
}

uint32_t vertrix_port_float_to_uint32(PORT_SIGNATURE)
{
    Port port;
    uint32_t value;
    port_open(&port, calls, services, globals, entry);
    value = port_call(&port, FLOAT_TO_SIGNED, entry->eax, entry->edx, entry->ebx,
                      (entry->ecx & 0xffffff00u) | UINT32_LIMIT);
    return port_return(&port, value, vertrix_lift_edx);
}
