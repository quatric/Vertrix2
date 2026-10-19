#include "rtllongdivides.h"

/* Original 0x4e88bf (edx:eax = dividend, ecx:ebx = divisor): the runtime's unsigned 64-bit divide,
 * the quotient in edx:eax (callers read only those; the original leaves the remainder in ecx:ebx).
 * A divisor of 0 reaches the original's div by 0, which does not fault in the lifted runtime and
 * leaves the dividend where it was. */
uint32_t vertrix_port_rtl_long_divide_4e88bf(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    const uint64_t dividend = ((uint64_t)entry->edx << 32) | entry->eax;
    const uint64_t divisor = ((uint64_t)entry->ecx << 32) | entry->ebx;
    if (divisor == 0)
    {
        return port_return(&port, entry->eax, entry->edx);
    }
    const uint64_t quotient = dividend / divisor;
    return port_return(&port, (uint32_t)quotient, (uint32_t)(quotient >> 32));
}
