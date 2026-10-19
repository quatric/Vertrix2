#include "rtllongtexts.h"

enum
{
    /* The digits, "0123456789abcdefghijklmnopqrstuvwxyz". */
    DIGITS = 0x50979c,
    /* 64 binary digits and the terminator. */
    MOST = 65
};

/* Original 0x4e63b0 (eax = the 64-bit value, edx = the buffer, ebx = the radix): _ui64toa(). The
 * value is divided by the radix until nothing is left (0x4e88bf, whose remainder in ecx:ebx picks
 * each digit), the digits gathered in a local behind a terminator, then copied out in reverse with
 * the terminator. Returns the buffer. The lift of the original takes the remainder for the radix
 * (it carries only edx:eax back from a call), so the port divides itself. */
uint32_t vertrix_port_rtl_long_text_4e63b0(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    const uint32_t buffer = entry->edx;
    const uint32_t radix = entry->ebx;
    uint64_t value =
        (uint64_t)port_u32(&port, entry->eax, 4) << 32 | port_u32(&port, entry->eax, 0);
    uint8_t digits[MOST];
    uint32_t count = 0;
    if (radix < 2)
    {
        /* Radix 0 divides by zero and radix 1 never ends in the original. */
        port.env.failed = 1;
        return port_return(&port, 0, 0);
    }
    do
    {
        digits[count++] = port_u8(&port, DIGITS, (uint32_t)(value % radix));
        value /= radix;
    } while (value != 0 && !port.env.failed);
    for (uint32_t i = 0; i < count; i++)
    {
        port_set8(&port, buffer, i, digits[count - 1 - i]);
    }
    port_set8(&port, buffer, count, 0);
    return port_return(&port, buffer, 0);
}
