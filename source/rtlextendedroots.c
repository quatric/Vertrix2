#include "rtlextendedroots.h"

enum
{
    /* An 80-bit extended value: the mantissa's low and high dwords, then the sign and exponent. */
    VALUE_LOW = 0,
    VALUE_HIGH = 4,
    VALUE_EXPONENT = 8,
    VALUE_TOP_BYTE = 7,

    EXPONENT_MASK = 0x7fff,
    EXPONENT_BIAS = 0x3fff,
    SIGN = 0x8000,
    /* The quiet NaN bits of the mantissa's top byte, and the indefinite value's exponent. */
    QUIET = 0xc0,
    INDEFINITE_EXPONENT = 0xffff,
    TOP = 0x80000000u
};

/* Make the value a quiet NaN (its mantissa's two top bits set). */
static void quiet(Port *port, uint32_t value)
{
    port_set8(port, value, VALUE_TOP_BYTE, port_u8(port, value, VALUE_TOP_BYTE) | QUIET);
}

/* Original 0x4db131 (eax = an 80-bit extended value): its square root in place, by integer Newton
 * steps. Zero (of either sign) and infinity stay; a NaN, an infinity's negative or any negative
 * value becomes a quiet NaN; a value whose mantissa lacks its integer bit becomes the indefinite
 * NaN (exponent 0xffff, mantissa 0xc000...). Otherwise the exponent is halved about its bias (an
 * odd one shifting the mantissa right first) and the 64-bit root of the 96-bit mantissa found:
 * guesses (high / 2 with the top bit) averaged with high:low / guess until they cross, then the low
 * dword from the remainder, and the root halved with its top bit set and rounded. Every register is
 * kept but eax, which is the root's low dword (the value's address when nothing is computed). */
uint32_t vertrix_port_rtl_extended_square_root_4db131(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    const uint32_t value = entry->eax;
    uint32_t exponent = port_u16(&port, value, VALUE_EXPONENT);
    uint32_t high = port_u32(&port, value, VALUE_HIGH);
    uint32_t low = port_u32(&port, value, VALUE_LOW);
    int indefinite = 0;
    if (low == 0 && high == 0)
    {
        if ((exponent & EXPONENT_MASK) != 0)
        {
            indefinite = 1;
        }
        else
        {
            return port_return(&port, value, entry->edx);
        }
    }
    else if (low == 0 && exponent == EXPONENT_MASK)
    {
        return port_return(&port, value, entry->edx);
    }
    else if ((exponent & EXPONENT_MASK) == EXPONENT_MASK || (exponent & SIGN) != 0)
    {
        quiet(&port, value);
        return port_return(&port, value, entry->edx);
    }
    else if (exponent != 0 && (high & TOP) == 0)
    {
        indefinite = 1;
    }
    if (indefinite)
    {
        port_set16(&port, value, VALUE_EXPONENT, INDEFINITE_EXPONENT);
        port_set32(&port, value, VALUE_HIGH, 0);
        port_set32(&port, value, VALUE_LOW, 0);
        quiet(&port, value);
        return port_return(&port, value, entry->edx);
    }

    /* The exponent halved about the bias; the bit shifted out says whether the mantissa (with a
     * third, lower dword) is shifted right first. */
    uint32_t extra = 0;
    const uint32_t unbiased = (exponent - EXPONENT_BIAS) & 0xffff;
    if ((unbiased & 1) == 0)
    {
        extra = low << 31;
        low = (low >> 1) | (high << 31);
        high >>= 1;
    }
    exponent = ((uint32_t)((int32_t)(int16_t)unbiased >> 1) + EXPONENT_BIAS) & 0xffff;
    port_set16(&port, value, VALUE_EXPONENT, exponent);

    uint32_t guess = (high >> 1) | TOP;
    uint32_t root_low;
    uint32_t root_high;
    uint32_t carry;
    if (high == 0xffffffffu)
    {
        if (low == guess)
        {
            port_set32(&port, value, VALUE_LOW, low);
            port_set32(&port, value, VALUE_HIGH, guess);
            return port_return(&port, low, entry->edx);
        }
        const uint64_t dividend = ((uint64_t)low << 32) | extra;
        root_low = (uint32_t)(dividend / guess);
    }
    else
    {
        uint64_t dividend = ((uint64_t)high << 32) | low;
        uint32_t quotient = (uint32_t)(dividend / guess);
        uint32_t remainder = (uint32_t)(dividend % guess);
        while (guess - 1 > quotient)
        {
            guess = (uint32_t)(((uint64_t)guess + quotient) >> 1);
            quotient = (uint32_t)(dividend / guess);
            remainder = (uint32_t)(dividend % guess);
        }
        const uint64_t rest = ((uint64_t)remainder << 32) | extra;
        root_low = (uint32_t)(rest / guess);
        guess += quotient;
    }
    /* The root halved with its top bit set, its low dword rounded by the bit shifted out. */
    carry = guess & 1;
    guess = (guess >> 1) | TOP;
    const uint32_t round = root_low & 1;
    root_low = (root_low >> 1) | (carry << 31);
    const uint64_t rounded = (uint64_t)root_low + round;
    root_low = (uint32_t)rounded;
    root_high = guess + (uint32_t)(rounded >> 32);
    port_set32(&port, value, VALUE_LOW, root_low);
    port_set32(&port, value, VALUE_HIGH, root_high);
    return port_return(&port, root_low, entry->edx);
}
