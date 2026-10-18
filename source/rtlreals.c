#include "rtlreals.h"

/* The runtime library's real conversions. */

static uint32_t shrd(uint32_t low, uint32_t high, unsigned count)
{
    count &= 31;
    return count == 0 ? low : (low >> count) | (high << (32 - count));
}

/* Original 0x4e543c: the extended real at eax (mantissa +0/+4, sign and exponent +8) rounded to
 * the nearest double (ties to even) into [edx], also eax (low) and edx (high). An exponent past a
 * double's range is infinity (0x4e2389 reports it unless the value was already infinite or not a
 * number), one below gives a denormal (rounded once, the sign dropped as the original does) or a
 * signed zero. */
uint32_t vertrix_port_rtl_extended_to_double_4e543c(PORT_SIGNATURE)
{
    Port port;
    uint32_t source = entry->eax;
    uint32_t target = entry->edx;
    uint32_t ecx;
    uint32_t low;
    uint32_t high;
    uint32_t mask = 0xfffff800u;
    uint32_t ebx;
    uint32_t exponent;
    uint32_t sign;
    uint32_t shift;
    uint32_t carry;
    port_open(&port, calls, services, globals, entry);
    ecx = (entry->ecx & 0xffff0000u) | port_u16(&port, source, 8);
    high = port_u32(&port, source, 4);
    low = port_u32(&port, source, 0);
    if (low & 0x400)
    {
        if ((low & 0x3ff) == 0)
        {
            mask += mask;
        }
        carry = low + 0x800 < low;
        low += 0x800;
        if (high + carry < high || (carry && high == 0xffffffffu))
        {
            high = 0x80000000u;
            ecx = (ecx & 0xffff0000u) | ((ecx + 1) & 0xffff);
        }
        else
        {
            high += carry;
        }
    }
    low &= mask;
    ebx = ecx;
    sign = (ebx >> 15) & 1;
    exponent = ((ecx & 0x7fff) + 0xc400) & 0xffff;
    ecx = (ecx & 0xffff0000u) | exponent;
    if (exponent < 0x7ff)
    {
        if (exponent == 0)
        {
            low = shrd(low, high, 12);
            high = (high + high) >> 12;
        }
        else
        {
            low = shrd(low, high, 11);
            high = shrd(high + high, ecx, 11);
        }
        high = (sign << 31) | (high >> 1);
    }
    else if (exponent < 0xc400)
    {
        low = shrd(low, high, 11);
        high = (high + high) >> 11;
        high = (sign << 31) | (high >> 1);
        high |= 0x7ff00000u;
        if (exponent != 0x43ff)
        {
            ebx = (ebx & 0xffff0000u) | ((ebx << 1) & 0xffff);
            port_call_with(&port, 0x4e2389, low, high, ebx, ecx, mask, entry->edi, entry->ebp);
        }
    }
    else if ((int16_t)exponent < -0x34)
    {
        low = 0;
        high = sign << 31;
    }
    else
    {
        shift = ((uint32_t)-(int32_t)((exponent - 0xc) & 0xffff)) & 0xff;
        if (shift >= 0x20)
        {
            shift -= 0x20;
            mask = low;
            low = high;
            high = 0;
        }
        mask = shrd(mask, low, shift);
        low = shrd(low, high, shift);
        high >>= shift & 31;
        carry = mask >> 31;
        low += carry;
        high += carry && low == 0;
    }
    port_set32(&port, target, 0, low);
    port_set32(&port, target, 4, high);
    return port_return(&port, low, high);
}
