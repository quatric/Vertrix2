#include "port_rtljpeglargestinputs.h"

/* Original 0x4c5d60 (ebx = j, ecx = maxj): libjpeg's largest_input_value for the ordered dither,
 * ((2j + 1) * 255 + maxj) / (2 * maxj), in 32-bit arithmetic with a signed division. A division
 * that faults (maxj 0, or a quotient past 32 bits) leaves the dividend, as the lifted idiv does. */
uint32_t vertrix_port_jpeg_largest_input_value_4c5d60(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    const uint32_t j = entry->ebx;
    const uint32_t maxj = entry->ecx;
    const int32_t value = (int32_t)((2 * j + 1) * 255 + maxj);
    const int32_t divisor = (int32_t)(2 * maxj);
    if (divisor == 0 || (value == INT32_MIN && divisor == -1))
    {
        return port_return(&port, (uint32_t)value, 0);
    }
    return port_return(&port, (uint32_t)(value / divisor), 0);
}
