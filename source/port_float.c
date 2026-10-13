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
    DOUBLE_ADD = 0x4db350,
    FPU_PRESENT = 0x5054a1,
    ADD_OVERFLOW = 0x4e2389,
    DOUBLE_DIVIDE = 0x4eb652,
    DOUBLE_COMPARE = 0x4eb57c,
    DOUBLE_EXPONENT_SPLIT = 0x4db1fd,
    DOUBLE_POLYNOMIAL = 0x4db6a4,
    INT_TO_DOUBLE = 0x4d6768,
    MATH_ERROR = 0x4db866,
    FPU_LOG = 0x4db896,
    DOUBLE_ABSOLUTE = 0x4dae62,
    DOUBLE_SIGN = 0x4dad19,
    DOUBLE_TO_INT = 0x4eb892,
    DOUBLE_SUBTRACT = 0x4db34a,
    DOUBLE_SCALE = 0x4e5271,
    FLOAT_ERROR = 0x4dad2e,
    FPU_EXP = 0x4e51c8,
    EXP_TABLE = 0x51ab70,
    DOUBLE_SPLIT_CALL = 0x4dae1e,
    POWER_ERROR = 0x4dad38,
    LOG = 0x4c9e2f,
    EXP = 0x4daed8,
    DOUBLE_REMAINDER = 0x4db250,
    DOUBLE_POLYNOMIAL_ODD = 0x4db6d9,
    TRIG_ERRORS = 0x518824,
    TRIG_DEGREES = 0x518800,
    TRIG_COSINE = 0x5187b8,
    TRIG_SINE = 0x518770
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

/* 0x4db350 on edx:eax (a) and ecx:ebx (b); see port_float.h. */
static uint32_t double_add(Port *port, const LiftEntry *entry, uint32_t eax, uint32_t edx,
                           uint32_t ebx, uint32_t ecx)
{
    uint32_t differ = (edx ^ ecx) & SIGN;
    uint32_t a_exponent = (edx >> 20) & 0x7ff;
    uint32_t b_exponent = (ecx >> 20) & 0x7ff;
    uint32_t ebp = (ecx & SIGN) | b_exponent;
    uint32_t count = 0;
    uint32_t sticky = 0;
    uint32_t mixed;
    uint32_t exponent;
    uint64_t a;
    uint64_t b;
    uint64_t sum;
    if (ebx == 0 && (ecx << 1) == 0)
    {
        return port_return(port, eax, edx);
    }
    if (eax == 0 && (edx << 1) == 0)
    {
        return port_return(port, ebx, ecx);
    }
    if (port_u8(port, FPU_PRESENT, 0) != 0)
    {
        lift_x87(&port->env, 0x4db374);
        return port_return(port, eax, edx);
    }
    a = ((uint64_t)((edx & MANTISSA_HIGH) | (a_exponent != 0 ? EXPONENT_UNIT : 0)) << 32 | eax)
        << 1;
    b = ((uint64_t)((ecx & MANTISSA_HIGH) | (b_exponent != 0 ? EXPONENT_UNIT : 0)) << 32 | ebx)
        << 1;
    if (b_exponent != a_exponent)
    {
        if (b_exponent > a_exponent)
        {
            count = b_exponent - a_exponent;
        }
        else
        {
            uint64_t swap = a;
            ebp = (edx & SIGN) | a_exponent;
            count = a_exponent - b_exponent;
            a = b;
            b = swap;
        }
        if (count > 0x36)
        {
            /* The larger operand alone, its hidden bit dropped. */
            uint32_t high = (uint32_t)(b >> 32);
            uint32_t low = (uint32_t)b;
            return port_return(port, (high << 31) | (low >> 1),
                               (((ebp & SIGN) | (high >> 1)) & 0x800fffffu) |
                                   ((ebp & 0x7ff) << 20));
        }
    }
    if (differ != 0)
    {
        b = 0u - b;
        ebp ^= SIGN;
    }
    if (count != 0)
    {
        uint32_t shift = count;
        if (count >= 32)
        {
            sticky = (uint32_t)a != 0;
            a >>= 32;
            shift -= 32;
        }
        if (shift != 0)
        {
            sticky |= (uint32_t)a << (32 - shift);
            a >>= shift;
        }
    }
    sum = a + b;
    if ((sum >> 63) != 0)
    {
        if (count >= 0x35 && (sticky & 0x7fffffffu) != 0)
        {
            sum++;
        }
        sum = 0u - sum;
        ebp ^= SIGN;
    }
    if (sum == 0)
    {
        return port_return(port, 0, 0);
    }
    /* ebx keeps this until the rounding below: the overflow callee sees it. */
    mixed = (uint32_t)sum | (uint32_t)(sum >> 32);
    exponent = ebp & 0xffff;
    while (exponent != 0 && ((uint32_t)(sum >> 32) & 0x7fe00000u) == 0)
    {
        exponent--;
        if (exponent != 0)
        {
            sum <<= 1;
        }
    }
    if (exponent == 0)
    {
        /* Denormal: shifted right once with the sign above, not rounded. */
        sum = (sum >> 1) | ((uint64_t)(ebp & SIGN) << 32);
        return port_return(port, (uint32_t)sum, (uint32_t)(sum >> 32));
    }
    ebp = (ebp & 0xffff0000u) | exponent;
    if (((uint32_t)(sum >> 32) & 0x400000) != 0)
    {
        sticky += (uint32_t)sum & 1;
        sum >>= 1;
        ebp++;
        if ((ebp & 0xffff) == 0x7ff)
        {
            goto overflow;
        }
    }
    if ((sum & 1) != 0)
    {
        sum >>= 1;
        mixed = ((mixed & 0xffffff00u) | (sticky != 0)) | (uint32_t)sum;
        if ((mixed & 1) != 0)
        {
            sum++;
        }
        mixed >>= 1;
        if (((uint32_t)(sum >> 32) & 0x200000) != 0)
        {
            sum >>= 1;
            ebp++;
            if ((ebp & 0xffff) == 0x7ff)
            {
                goto overflow;
            }
        }
    }
    else
    {
        sum >>= 1;
    }
    return port_return(port, (uint32_t)sum,
                       ((uint32_t)(sum >> 32) & MANTISSA_HIGH) | (ebp & SIGN) |
                           ((ebp & 0x7ff) << 20));
overflow:
    {
        uint32_t result = port_call_with(port, ADD_OVERFLOW, ebp, (uint32_t)(sum >> 32), mixed,
                                         differ | count, entry->esi, entry->edi, entry->ebp);
        return port_return(port, result, vertrix_lift_edx);
    }
}

uint32_t vertrix_port_double_subtract(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    return double_add(&port, entry, entry->eax, entry->edx, entry->ebx, entry->ecx ^ SIGN);
}

/* A helper call: eax and edx come back, the other registers keep what the caller put in them. */
static uint32_t log_call(Port *port, uint32_t target, uint32_t *eax, uint32_t *edx, uint32_t ebx,
                         uint32_t ecx)
{
    *eax = port_call(port, target, *eax, *edx, ebx, ecx);
    *edx = vertrix_lift_edx;
    return *eax;
}

uint32_t vertrix_port_log(PORT_SIGNATURE)
{
    Port port;
    uint32_t base = entry->esp - 4; /* the original's ebp */
    uint32_t exponent = base - 0x24;
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi;
    uint32_t edi;
    uint32_t sum_low;
    uint32_t sum_high;
    uint32_t term_low;
    uint32_t term_high;
    LiftFlags fl;
    port_open_frame(&port, calls, services, globals, entry, 0x28);
    port_set32(&port, base, 0, entry->ebp);
    port_set32(&port, base, (uint32_t)-4, entry->ebx);
    port_set32(&port, base, (uint32_t)-8, entry->ecx);
    port_set32(&port, base, (uint32_t)-0xc, entry->esi);
    port_set32(&port, base, (uint32_t)-0x10, entry->edi);
    edi = eax;
    esi = edx;
    if ((int32_t)edx <= 0)
    {
        log_call(&port, MATH_ERROR, &eax, &edx, 0xa, ecx);
        return port_return(&port, eax, edx);
    }
    if (port_u8(&port, FPU_PRESENT, 0) != 0)
    {
        eax = edi;
        log_call(&port, FPU_LOG, &eax, &edx, ebx, ecx);
        return port_return(&port, eax, edx);
    }
    ebx = exponent;
    eax = edi;
    ecx = 0xbfe00000u;
    log_call(&port, DOUBLE_EXPONENT_SPLIT, &eax, &edx, ebx, ecx);
    edi = eax;
    ebx = 0;
    esi = edx;
    log_call(&port, DOUBLE_ADD, &eax, &edx, ebx, ecx);
    ebx = 0x667f3bcdu;
    ecx = 0x3fe6a09eu;
    sum_low = eax;
    sum_high = edx;
    eax = edi;
    edx = esi;
    log_call(&port, DOUBLE_COMPARE, &eax, &edx, ebx, ecx);
    fl = vertrix_lift_fl;
    if (!fl.zf && fl.sf == fl.of)
    {
        eax = sum_low;
        edx = sum_high;
        ecx = 0xbfe00000u;
        ebx = 0;
        log_call(&port, DOUBLE_ADD, &eax, &edx, ebx, ecx);
        sum_low = eax;
        sum_high = edx;
    }
    else
    {
        edx = port_u32(&port, exponent, 0) - 1;
        edi = sum_low;
        esi = sum_high;
        port_set32(&port, exponent, 0, edx);
    }
    ecx = 0x3fe00000u;
    eax = edi;
    edx = esi;
    ebx = 0;
    log_call(&port, DOUBLE_MULTIPLY, &eax, &edx, ebx, ecx);
    ecx = 0x3fe00000u;
    ebx = 0;
    log_call(&port, DOUBLE_ADD, &eax, &edx, ebx, ecx);
    ebx = eax;
    ecx = edx;
    eax = sum_low;
    edx = sum_high;
    log_call(&port, DOUBLE_DIVIDE, &eax, &edx, ebx, ecx);
    sum_low = eax;
    ebx = eax;
    ecx = edx;
    sum_high = edx;
    log_call(&port, DOUBLE_MULTIPLY, &eax, &edx, ebx, ecx);
    edi = eax;
    esi = edx;
    eax = sum_low;
    edx = sum_high;
    ebx = edi;
    ecx = esi;
    log_call(&port, DOUBLE_MULTIPLY, &eax, &edx, ebx, ecx);
    ecx = 2;
    ebx = 0x518830;
    term_low = eax;
    term_high = edx;
    eax = edi;
    edx = esi;
    log_call(&port, DOUBLE_POLYNOMIAL, &eax, &edx, ebx, ecx);
    ebx = eax;
    ecx = edx;
    eax = term_low;
    edx = term_high;
    log_call(&port, DOUBLE_MULTIPLY, &eax, &edx, ebx, ecx);
    ecx = 3;
    ebx = 0x518848;
    term_low = eax;
    term_high = edx;
    eax = edi;
    edx = esi;
    log_call(&port, DOUBLE_POLYNOMIAL, &eax, &edx, ebx, ecx);
    ebx = eax;
    ecx = edx;
    eax = term_low;
    edx = term_high;
    log_call(&port, DOUBLE_DIVIDE, &eax, &edx, ebx, ecx);
    ebx = eax;
    ecx = edx;
    eax = sum_low;
    edx = sum_high;
    log_call(&port, DOUBLE_ADD, &eax, &edx, ebx, ecx);
    ebx = port_u32(&port, exponent, 0);
    edi = eax;
    esi = edx;
    if (ebx == 0)
    {
        return port_return(&port, edi, esi);
    }
    eax = ebx;
    ecx = 0xbf2bd010u;
    log_call(&port, INT_TO_DOUBLE, &eax, &edx, ebx, ecx);
    ebx = 0x5c610ca9u;
    term_low = eax;
    term_high = edx;
    log_call(&port, DOUBLE_MULTIPLY, &eax, &edx, ebx, ecx);
    ebx = edi;
    ecx = esi;
    log_call(&port, DOUBLE_ADD, &eax, &edx, ebx, ecx);
    ecx = 0x3fe63000u;
    edi = eax;
    esi = edx;
    ebx = 0;
    eax = term_low;
    edx = term_high;
    log_call(&port, DOUBLE_MULTIPLY, &eax, &edx, ebx, ecx);
    ebx = eax;
    ecx = edx;
    eax = edi;
    edx = esi;
    log_call(&port, DOUBLE_ADD, &eax, &edx, ebx, ecx);
    return port_return(&port, eax, edx);
}

uint32_t vertrix_port_exp(PORT_SIGNATURE)
{
    Port port;
    uint32_t base = entry->esp - 4; /* the original's ebp */
    uint32_t x = base - 0x3c;       /* x, then the working value, handed to 0x4dad2e */
    uint32_t whole = base - 0x34;   /* the integer part 0x4dae1e stores */
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t power;
    uint32_t square_high;
    uint32_t p_low;
    uint32_t q_low;
    uint32_t q_high;
    uint32_t sum_low;
    uint32_t sum_high;
    LiftFlags fl;
    port_open_frame(&port, calls, services, globals, entry, 0x40);
    port_set32(&port, base, 0, entry->ebp);
    port_set32(&port, base, (uint32_t)-4, entry->ebx);
    port_set32(&port, base, (uint32_t)-8, entry->ecx);
    port_set32(&port, base, (uint32_t)-0xc, entry->esi);
    port_set32(&port, base, (uint32_t)-0x10, entry->edi);
    port_set32(&port, x, 0, eax);
    port_set32(&port, x, 4, edx);
    log_call(&port, DOUBLE_ABSOLUTE, &eax, &edx, ebx, ecx);
    ebx = 0xf368cb40u;
    ecx = 0x3cc003c9u;
    edi = eax;
    esi = edx;
    log_call(&port, DOUBLE_COMPARE, &eax, &edx, ebx, ecx);
    fl = vertrix_lift_fl;
    if (fl.sf != fl.of)
    {
        port_set32(&port, x, 0, 0);
        port_set32(&port, x, 4, 0x3ff00000u);
        goto done;
    }
    ebx = 0xfefa39efu;
    ecx = 0x40862e42u;
    eax = edi;
    edx = esi;
    log_call(&port, DOUBLE_COMPARE, &eax, &edx, ebx, ecx);
    fl = vertrix_lift_fl;
    if (!fl.zf && fl.sf == fl.of)
    {
        if ((int32_t)port_u32(&port, x, 4) < 0)
        {
            port_set32(&port, x, 0, 0);
            port_set32(&port, x, 4, 0);
            goto done;
        }
        edx = x;
        eax = 0x8104;
        log_call(&port, FLOAT_ERROR, &eax, &edx, ebx, ecx);
        goto store;
    }
    if (port_u8(&port, FPU_PRESENT, 0) != 0)
    {
        eax = port_u32(&port, x, 0);
        edx = port_u32(&port, x, 4);
        log_call(&port, FPU_EXP, &eax, &edx, ebx, ecx);
        goto store;
    }
    eax = port_u32(&port, x, 0);
    edx = port_u32(&port, x, 4);
    ebx = 0x652b8301u;
    ecx = 0x3ff71547u;
    log_call(&port, DOUBLE_MULTIPLY, &eax, &edx, ebx, ecx);
    port_set32(&port, x, 0, eax);
    port_set32(&port, x, 4, edx);
    log_call(&port, DOUBLE_SIGN, &eax, &edx, ebx, ecx);
    edx = port_u32(&port, x, 4);
    esi = eax;
    eax = port_u32(&port, x, 0);
    ebx = whole;
    log_call(&port, DOUBLE_ABSOLUTE, &eax, &edx, ebx, ecx);
    log_call(&port, DOUBLE_SPLIT_CALL, &eax, &edx, ebx, ecx);
    ebx = eax;
    ecx = edx;
    port_set32(&port, x, 0, eax);
    port_set32(&port, x, 4, edx);
    eax = port_u32(&port, whole, 0);
    edx = port_u32(&port, whole, 4);
    log_call(&port, DOUBLE_TO_INT, &eax, &edx, ebx, ecx);
    power = eax;
    if ((int32_t)esi < 0)
    {
        edx = 0u - eax;
        power = edx;
        if (ecx != 0)
        {
            esi = edx - 1;
            eax = 0;
            edx = 0x3ff00000u;
            power = esi;
            log_call(&port, DOUBLE_SUBTRACT, &eax, &edx, ebx, ecx);
            port_set32(&port, x, 0, eax);
            port_set32(&port, x, 4, edx);
        }
    }
    eax = port_u32(&port, x, 4);
    edi = 0;
    if (eax != 0)
    {
        ebx = 4;
        eax = port_u32(&port, x, 0);
        edx = port_u32(&port, x, 4);
        log_call(&port, DOUBLE_SCALE, &eax, &edx, ebx, ecx);
        ebx = whole;
        log_call(&port, DOUBLE_SPLIT_CALL, &eax, &edx, ebx, ecx);
        port_set32(&port, x, 0, eax);
        port_set32(&port, x, 4, edx);
        if (edx != 0)
        {
            ebx = 0xfffffffcu;
            log_call(&port, DOUBLE_SCALE, &eax, &edx, ebx, ecx);
            port_set32(&port, x, 0, eax);
            port_set32(&port, x, 4, edx);
        }
        eax = port_u32(&port, whole, 0);
        edx = port_u32(&port, whole, 4);
        log_call(&port, DOUBLE_TO_INT, &eax, &edx, ebx, ecx);
        edi = eax;
    }
    eax = port_u32(&port, x, 0);
    edx = port_u32(&port, x, 4);
    ebx = eax;
    ecx = edx;
    log_call(&port, DOUBLE_MULTIPLY, &eax, &edx, ebx, ecx);
    ebx = 0x4f237e45u;
    ecx = 0x4034d053u;
    esi = eax;
    square_high = edx;
    log_call(&port, DOUBLE_ADD, &eax, &edx, ebx, ecx);
    ebx = 0x1ac13af9u;
    ecx = 0x3fad92deu;
    q_low = eax;
    q_high = edx;
    edx = square_high;
    eax = esi;
    log_call(&port, DOUBLE_MULTIPLY, &eax, &edx, ebx, ecx);
    ebx = 0xa35ca6dcu;
    ecx = 0x401cdaa0u;
    log_call(&port, DOUBLE_ADD, &eax, &edx, ebx, ecx);
    ebx = port_u32(&port, x, 0);
    ecx = port_u32(&port, x, 4);
    log_call(&port, DOUBLE_MULTIPLY, &eax, &edx, ebx, ecx);
    p_low = eax;
    esi = edx;
    eax = q_low;
    edx = q_high;
    ebx = p_low;
    ecx = esi;
    log_call(&port, DOUBLE_ADD, &eax, &edx, ebx, ecx);
    ebx = p_low;
    sum_low = eax;
    sum_high = edx;
    ecx = esi;
    eax = q_low;
    edx = q_high;
    log_call(&port, DOUBLE_SUBTRACT, &eax, &edx, ebx, ecx);
    ebx = eax;
    ecx = edx;
    eax = sum_low;
    edx = sum_high;
    esi = EXP_TABLE;
    log_call(&port, DOUBLE_DIVIDE, &eax, &edx, ebx, ecx);
    port_set32(&port, x, 0, eax);
    port_set32(&port, x, 4, edx);
    while (edi != 0)
    {
        if ((edi & 1) != 0)
        {
            eax = port_u32(&port, x, 0);
            edx = port_u32(&port, x, 4);
            ebx = port_u32(&port, esi, 0);
            ecx = port_u32(&port, esi, 4);
            log_call(&port, DOUBLE_MULTIPLY, &eax, &edx, ebx, ecx);
            port_set32(&port, x, 0, eax);
            port_set32(&port, x, 4, edx);
        }
        edi = (uint32_t)((int32_t)edi >> 1);
        esi += 8;
    }
    ebx = power;
    eax = port_u32(&port, x, 0);
    edx = port_u32(&port, x, 4);
    log_call(&port, DOUBLE_SCALE, &eax, &edx, ebx, ecx);
    goto store;
done:
    return port_return(&port, port_u32(&port, x, 0), port_u32(&port, x, 4));
store:
    port_set32(&port, x, 0, eax);
    port_set32(&port, x, 4, edx);
    goto done;
}

uint32_t vertrix_port_power(PORT_SIGNATURE)
{
    Port port;
    uint32_t base = entry->esp - 4; /* the original's ebp */
    uint32_t x = base - 0x24;       /* x, then the result */
    uint32_t whole = base - 0x1c;   /* y's integer part, then y * log(x), then the product */
    uint32_t y = base - 0x14;
    uint32_t n = base - 0xc;
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi;
    uint32_t edi;
    LiftFlags fl;
    port_open_frame(&port, calls, services, globals, entry, 0x28);
    port_set32(&port, base, 0, entry->ebp);
    port_set32(&port, base, (uint32_t)-4, entry->esi);
    port_set32(&port, base, (uint32_t)-8, entry->edi);
    port_set32(&port, x, 0, eax);
    port_set32(&port, x, 4, edx);
    port_set32(&port, y, 0, ebx);
    port_set32(&port, y, 4, ecx);
    log_call(&port, DOUBLE_SIGN, &eax, &edx, ebx, ecx);
    ecx = eax;
    esi = eax;
    if (eax == 0)
    {
        edi = port_u32(&port, y, 4);
        if ((int32_t)edi > 0)
        {
            goto result;
        }
        eax = (int32_t)edi < 0 ? 0x8047 : 0x4047;
        goto error;
    }
    ebx = whole;
    eax = port_u32(&port, y, 0);
    edx = port_u32(&port, y, 4);
    log_call(&port, DOUBLE_SPLIT_CALL, &eax, &edx, ebx, ecx);
    eax = port_u32(&port, whole, 0);
    ebx = edx;
    edi = edx;
    edx = port_u32(&port, whole, 4);
    log_call(&port, DOUBLE_TO_INT, &eax, &edx, ebx, ecx);
    port_set32(&port, n, 0, eax);
    if ((int32_t)ecx < 0)
    {
        if (ebx != 0)
        {
            eax = 0x2047;
            ebx = y;
            edx = x;
            log_call(&port, POWER_ERROR, &eax, &edx, ebx, ecx);
            return port_return(&port, eax, edx);
        }
        eax = port_u32(&port, x, 0);
        edx = port_u32(&port, x, 4);
        log_call(&port, DOUBLE_NEGATE, &eax, &edx, ebx, ecx);
        port_set32(&port, x, 0, eax);
        port_set32(&port, x, 4, edx);
        if ((port_u8(&port, n, 0) & 1) == 0)
        {
            esi ^= ecx;
        }
    }
    eax = port_u32(&port, x, 0);
    edx = port_u32(&port, x, 4);
    log_call(&port, LOG, &eax, &edx, ebx, ecx);
    ebx = port_u32(&port, y, 0);
    ecx = port_u32(&port, y, 4);
    log_call(&port, DOUBLE_MULTIPLY, &eax, &edx, ebx, ecx);
    ebx = 0xfefa39efu;
    ecx = 0x40862e42u;
    port_set32(&port, whole, 0, eax);
    port_set32(&port, whole, 4, edx);
    log_call(&port, DOUBLE_ABSOLUTE, &eax, &edx, ebx, ecx);
    log_call(&port, DOUBLE_COMPARE, &eax, &edx, ebx, ecx);
    fl = vertrix_lift_fl;
    if (!fl.zf && fl.sf == fl.of)
    {
        if ((int32_t)port_u32(&port, whole, 4) < 0)
        {
            ecx = 0;
            log_call(&port, SCALE_OVERFLOW, &eax, &edx, ebx, ecx);
            port_set32(&port, x, 0, ecx);
            port_set32(&port, x, 4, ecx);
            goto result;
        }
        eax = (int32_t)esi > 0 ? 0x8107 : 0x1107;
        goto error;
    }
    if (edi != 0 || port_u32(&port, n, 0) == 0x80000000u)
    {
        eax = port_u32(&port, whole, 0);
        edx = port_u32(&port, whole, 4);
        log_call(&port, EXP, &eax, &edx, ebx, ecx);
        port_set32(&port, x, 0, eax);
        port_set32(&port, x, 4, edx);
        goto sign;
    }
    edx = port_u32(&port, n, 0);
    if ((int32_t)edx < 0)
    {
        ebx = port_u32(&port, x, 0);
        ecx = 0u - edx;
        eax = 0;
        edx = 0x3ff00000u;
        port_set32(&port, n, 0, ecx);
        ecx = port_u32(&port, x, 4);
        log_call(&port, DOUBLE_DIVIDE, &eax, &edx, ebx, ecx);
        port_set32(&port, x, 0, eax);
        port_set32(&port, x, 4, edx);
    }
    if (port_u32(&port, n, 0) != 1)
    {
        eax = 0;
        edx = 0x3ff00000u;
        port_set32(&port, whole, 0, eax);
        port_set32(&port, whole, 4, edx);
        while (port_u32(&port, n, 0) != 0)
        {
            if ((port_u8(&port, n, 0) & 1) != 0)
            {
                eax = port_u32(&port, whole, 0);
                edx = port_u32(&port, whole, 4);
                ebx = port_u32(&port, x, 0);
                ecx = port_u32(&port, x, 4);
                log_call(&port, DOUBLE_MULTIPLY, &eax, &edx, ebx, ecx);
                port_set32(&port, whole, 0, eax);
                port_set32(&port, whole, 4, edx);
            }
            eax = port_u32(&port, x, 0);
            edx = port_u32(&port, x, 4);
            ebx = eax;
            ecx = edx;
            log_call(&port, DOUBLE_MULTIPLY, &eax, &edx, ebx, ecx);
            ebx = (uint32_t)((int32_t)port_u32(&port, n, 0) >> 1);
            port_set32(&port, x, 0, eax);
            port_set32(&port, x, 4, edx);
            port_set32(&port, n, 0, ebx);
        }
        port_set32(&port, x, 0, port_u32(&port, whole, 0));
        port_set32(&port, x, 4, port_u32(&port, whole, 4));
    }
sign:
    if ((int32_t)esi >= 0)
    {
        goto result;
    }
    eax = port_u32(&port, x, 0);
    edx = port_u32(&port, x, 4);
    log_call(&port, DOUBLE_NEGATE, &eax, &edx, ebx, ecx);
    goto store;
error:
    ebx = y;
    edx = x;
    log_call(&port, POWER_ERROR, &eax, &edx, ebx, ecx);
store:
    port_set32(&port, x, 0, eax);
    port_set32(&port, x, 4, edx);
result:
    return port_return(&port, port_u32(&port, x, 0), port_u32(&port, x, 4));
}

uint32_t vertrix_port_trig(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x48
    };
    uint8_t stack[BELOW + 8];
    Port port;
    uint32_t base = entry->esp - 4; /* the original's ebp */
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi;
    uint32_t edi = entry->edi;
    uint32_t arguments[6];
#define LOCAL(offset) base, (uint32_t)-(offset)
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    port_set32(&port, base, 0, entry->ebp);
    port_set32(&port, LOCAL(4), entry->ecx);
    port_set32(&port, LOCAL(8), entry->esi);
    port_set32(&port, LOCAL(0xc), entry->edi);
    port_set32(&port, LOCAL(0x44), eax);
    port_set32(&port, LOCAL(0x40), edx);
    esi = ebx;
    ebx = base - 0x2c;
    log_call(&port, DOUBLE_EXPONENT_SPLIT, &eax, &edx, ebx, ecx);
    if ((int32_t)port_u32(&port, LOCAL(0x2c)) >= 0x20)
    {
        eax = port_u32(&port, esi * 4, TRIG_ERRORS) | 0x2400;
        edx = base - 0x44;
        log_call(&port, FLOAT_ERROR, &eax, &edx, ebx, ecx);
        return port_return(&port, eax, edx);
    }
    eax = base - 0x28;
    ebx = port_u32(&port, LOCAL(0x40));
    ecx = port_u32(&port, LOCAL(0x44));
    arguments[0] = ecx;
    arguments[1] = ebx;
    arguments[2] = 0x54442d18u;
    arguments[3] = 0x3fe921fbu;
    arguments[4] = base - 0x28;
    arguments[5] = base - 0x34;
    eax = port_call_stack(&port, DOUBLE_REMAINDER, eax, edx, ebx, ecx, arguments, 6);
    edx = port_u32(&port, LOCAL(0x28));
    eax = ((esi & 2) + edx) & 7;
    port_set32(&port, LOCAL(0x28), eax);
    if ((port_u8(&port, LOCAL(0x28)) & 1) != 0)
    {
        eax = 0x54442d18u;
        edx = 0x3fe921fbu;
        ebx = port_u32(&port, LOCAL(0x34));
        ecx = port_u32(&port, LOCAL(0x30));
        log_call(&port, DOUBLE_SUBTRACT, &eax, &edx, ebx, ecx);
        port_set32(&port, LOCAL(0x34), eax);
        port_set32(&port, LOCAL(0x30), edx);
    }
    ebx = base - 0x1c;
    eax = port_u32(&port, LOCAL(0x34));
    edx = port_u32(&port, LOCAL(0x30));
    log_call(&port, DOUBLE_EXPONENT_SPLIT, &eax, &edx, ebx, ecx);
    ebx = port_u32(&port, LOCAL(0x1c));
    if ((int32_t)ebx < -0x1a)
    {
        edi = port_u32(&port, LOCAL(0x34));
        eax = port_u32(&port, LOCAL(0x30));
        ecx = 0;
        port_set32(&port, LOCAL(0x14), eax);
        eax = 0x3ff00000u;
        port_set32(&port, LOCAL(0x18), ecx);
        port_set32(&port, LOCAL(0x10), eax);
    }
    else
    {
        if ((int32_t)ebx > 0)
        {
            port_set32(&port, LOCAL(0x1c), 0);
        }
        edx = 0u - port_u32(&port, LOCAL(0x1c));
        port_set32(&port, LOCAL(0x1c), edx);
        if ((int32_t)edx > 8)
        {
            port_set32(&port, LOCAL(0x1c), 8);
        }
        eax = port_u32(&port, port_u32(&port, LOCAL(0x1c)) * 4, TRIG_DEGREES);
        port_set32(&port, LOCAL(0x1c), eax);
        eax = port_u32(&port, LOCAL(0x28)) + 1;
        if ((eax & 2) != 0 || esi == 1)
        {
            edx = port_u32(&port, LOCAL(0x1c));
            port_set32(&port, LOCAL(0x24), 8 - edx);
            edx = TRIG_COSINE + (edx << 3);
            eax = port_u32(&port, LOCAL(0x34));
            port_set32(&port, LOCAL(0x20), edx);
            edx = port_u32(&port, LOCAL(0x30));
            ebx = eax;
            ecx = edx;
            log_call(&port, DOUBLE_MULTIPLY, &eax, &edx, ebx, ecx);
            ecx = port_u32(&port, LOCAL(0x24));
            ebx = port_u32(&port, LOCAL(0x20));
            log_call(&port, DOUBLE_POLYNOMIAL, &eax, &edx, ebx, ecx);
            port_set32(&port, LOCAL(0x18), eax);
            port_set32(&port, LOCAL(0x10), edx);
        }
        eax = port_u32(&port, LOCAL(0x28)) + 1;
        if ((eax & 2) == 0 || esi == 1)
        {
            ebx = port_u32(&port, LOCAL(0x1c));
            eax = port_u32(&port, LOCAL(0x34));
            ecx = 8 - ebx;
            ebx = (ebx << 3) + TRIG_SINE;
            edx = port_u32(&port, LOCAL(0x30));
            log_call(&port, DOUBLE_POLYNOMIAL_ODD, &eax, &edx, ebx, ecx);
            edi = eax;
            port_set32(&port, LOCAL(0x14), edx);
        }
    }
    eax = port_u32(&port, LOCAL(0x28)) + 1;
    if ((eax & 2) != 0)
    {
        port_set32(&port, LOCAL(0x3c), port_u32(&port, LOCAL(0x18)));
        eax = port_u32(&port, LOCAL(0x10));
    }
    else
    {
        eax = port_u32(&port, LOCAL(0x14));
        port_set32(&port, LOCAL(0x3c), edi);
    }
    port_set32(&port, LOCAL(0x38), eax);
    if ((port_u8(&port, LOCAL(0x28)) & 4) != 0)
    {
        eax = port_u32(&port, LOCAL(0x3c));
        edx = port_u32(&port, LOCAL(0x38));
        log_call(&port, DOUBLE_NEGATE, &eax, &edx, ebx, ecx);
        port_set32(&port, LOCAL(0x3c), eax);
        port_set32(&port, LOCAL(0x38), edx);
    }
    if (esi == 1)
    {
        edx = port_u32(&port, LOCAL(0x28)) + 2;
        eax = port_u32(&port, LOCAL(0x28)) + 3;
        port_set32(&port, LOCAL(0x28), edx);
        if ((eax & 2) != 0)
        {
            ebx = port_u32(&port, LOCAL(0x18));
            ecx = port_u32(&port, LOCAL(0x10));
        }
        else
        {
            ecx = port_u32(&port, LOCAL(0x14));
            ebx = edi;
        }
        if ((port_u8(&port, LOCAL(0x28)) & 4) != 0)
        {
            eax = ebx;
            edx = ecx;
            log_call(&port, DOUBLE_NEGATE, &eax, &edx, ebx, ecx);
            ebx = eax;
            ecx = edx;
        }
        if (ecx == 0)
        {
            log_call(&port, SCALE_OVERFLOW, &eax, &edx, ebx, ecx);
            eax = port_u32(&port, DOUBLE_INFINITY, 0);
            edx = port_u32(&port, DOUBLE_INFINITY, 4);
            if ((int32_t)port_u32(&port, LOCAL(0x38)) <= 0)
            {
                log_call(&port, DOUBLE_NEGATE, &eax, &edx, ebx, ecx);
            }
            return port_return(&port, eax, edx);
        }
        eax = port_u32(&port, LOCAL(0x3c));
        edx = port_u32(&port, LOCAL(0x38));
        log_call(&port, DOUBLE_DIVIDE, &eax, &edx, ebx, ecx);
        port_set32(&port, LOCAL(0x3c), eax);
        port_set32(&port, LOCAL(0x38), edx);
    }
    if ((int32_t)port_u32(&port, LOCAL(0x2c)) >= 0x1c)
    {
        ebx = base - 0x3c;
        eax = port_u32(&port, esi * 4, TRIG_ERRORS) | 0x200;
        edx = base - 0x44;
        log_call(&port, POWER_ERROR, &eax, &edx, ebx, ecx);
        return port_return(&port, eax, edx);
    }
    return port_return(&port, port_u32(&port, LOCAL(0x3c)), port_u32(&port, LOCAL(0x38)));
#undef LOCAL
}

uint32_t vertrix_port_double_remainder(PORT_SIGNATURE)
{
    enum
    {
        COMPARE,
        SUBTRACT,
        SHIFT_IN,
        BELOW = 0x24,
        ARGUMENTS = 6
    };
    uint8_t stack[BELOW + 8 + 4 * ARGUMENTS];
    Port port;
    uint32_t base = entry->esp - 4; /* the original's ebp */
    uint32_t a_low;
    uint32_t a_high;
    uint32_t b_low;
    uint32_t b_high;
    uint32_t quotient = 0;
    uint32_t exponent;
    uint32_t remainder;
    uint32_t high;
    uint64_t a;
    uint64_t b;
    port_open_arguments(&port, stack, calls, services, globals, entry, BELOW, ARGUMENTS);
    /* The pushes: the registers come back from these slots after the stores below. */
    port_set32(&port, base, 0, entry->ebp);
    port_set32(&port, base, (uint32_t)-4, entry->edx);
    port_set32(&port, base, (uint32_t)-8, entry->ecx);
    port_set32(&port, base, (uint32_t)-0xc, entry->ebx);
    port_set32(&port, base, (uint32_t)-0x10, entry->eax);
    a_low = port_u32(&port, base, 8);
    a_high = port_u32(&port, base, 0xc);
    b_low = port_u32(&port, base, 0x10);
    b_high = port_u32(&port, base, 0x14);
    if (b_high == 0)
    {
        port_set32(&port, port_u32(&port, base, 0x18), 0, 0);
        remainder = port_u32(&port, base, 0x1c);
        port_set32(&port, remainder, 0, 0);
        port_set32(&port, remainder, 4, 0);
        return port_return(&port, port_u32(&port, base, (uint32_t)-0x10),
                           port_u32(&port, base, (uint32_t)-4));
    }
    port_set32(&port, base, (uint32_t)-0x14, entry->esi);
    port_set32(&port, base, (uint32_t)-0x18, entry->edi);
    port_set32(&port, base, (uint32_t)-0x1c, a_high);
    port_set32(&port, base, (uint32_t)-0x20, b_high);
    exponent = (a_high & EXPONENT) - (b_high & EXPONENT);
    a = (uint64_t)((a_high & MANTISSA_HIGH) | EXPONENT_UNIT) << 32 | a_low;
    b = (uint64_t)((b_high & MANTISSA_HIGH) | EXPONENT_UNIT) << 32 | b_low;
    if ((int32_t)exponent < 0)
    {
        /* |a| below |b|'s exponent: a is the remainder. */
        exponent += b_high & EXPONENT;
    }
    else
    {
        int state = COMPARE;
        for (;;)
        {
            uint32_t bit = 0;
            if (state == SUBTRACT || (state == COMPARE && a >= b))
            {
                a -= b;
                bit = 1;
            }
            quotient = quotient * 2 + bit;
            exponent -= EXPONENT_UNIT;
            if ((int32_t)exponent < 0)
            {
                break;
            }
            a <<= 1;
            high = (uint32_t)(a >> 32);
            state = high >= 0x200000 ? SUBTRACT : high >= EXPONENT_UNIT ? COMPARE : SHIFT_IN;
        }
        exponent = 0;
        if (a != 0)
        {
            while (((uint32_t)(a >> 32) & 0x200000) == 0)
            {
                a <<= 1;
                exponent -= EXPONENT_UNIT;
            }
            a >>= 1;
            exponent += EXPONENT_UNIT + (b_high & EXPONENT);
        }
    }
    high = ((uint32_t)(a >> 32) & MANTISSA_HIGH) + exponent;
    if (high != 0)
    {
        high |= a_high & SIGN;
    }
    if (((a_high ^ b_high) & SIGN) != 0)
    {
        quotient = 0u - quotient;
    }
    port_set32(&port, port_u32(&port, base, 0x18), 0, quotient);
    remainder = port_u32(&port, base, 0x1c);
    port_set32(&port, remainder, 0, (uint32_t)a);
    port_set32(&port, remainder, 4, high);
    return port_return(&port, port_u32(&port, base, (uint32_t)-0x10),
                       port_u32(&port, base, (uint32_t)-4));
}
