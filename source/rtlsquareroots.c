#include "rtlsquareroots.h"

#include <math.h>
#include <string.h>

enum
{
    /* The value, under the saved ebp. */
    BELOW = 0xc,
    VALUE = 0xc,

    COPROCESSOR = 0x5054a1,
    /* sqrt's domain error. */
    DOMAIN_ERROR = 0x2043,
    MATH_ERROR = 0x4dad2e,
    SOFTWARE_ROOT = 0x4db10a
};

/* Original 0x4c9b10 (edx:eax = the double): sqrt(). A negative value (by its sign) is the domain
 * error (0x4dad2e with the value's address), whose answer is the result. With the coprocessor
 * (0x5054a1, never set in the lifted runtime) it is fsqrt; without it a value whose high dword is
 * 0 is its own root and any other goes to the software root (0x4db10a). */
uint32_t vertrix_port_rtl_square_root_4c9b10(PORT_SIGNATURE)
{
    Port port;
    uint8_t stack[BELOW + 8];
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    const uint32_t low = entry->eax;
    const uint32_t high = entry->edx;
    const uint32_t value = entry->esp - VALUE;
    port_set32(&port, value, 0, low);
    port_set32(&port, value, 4, high);
    if ((int32_t)high < 0)
    {
        const uint32_t result =
            port_call(&port, MATH_ERROR, DOMAIN_ERROR, value, entry->ebx, entry->ecx);
        return port_return(&port, result, vertrix_lift_edx);
    }
    if (port_u8(&port, COPROCESSOR, 0) != 0)
    {
        const uint64_t bits = (uint64_t)high << 32 | low;
        double number;
        memcpy(&number, &bits, sizeof number);
        number = sqrt(number);
        uint64_t root;
        memcpy(&root, &number, sizeof root);
        return port_return(&port, (uint32_t)root, (uint32_t)(root >> 32));
    }
    if (high == 0)
    {
        return port_return(&port, low, high);
    }
    const uint32_t result = port_call(&port, SOFTWARE_ROOT, low, high, entry->ebx, entry->ecx);
    return port_return(&port, result, vertrix_lift_edx);
}
