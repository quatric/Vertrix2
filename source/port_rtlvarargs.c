#include "port_rtlvarargs.h"

/* A cdecl varargs entry: hands its first three arguments and a pointer to the rest to 0x4cd56c. */

enum
{
    BELOW = 0x10,
    ARGUMENT_FIRST = 4,
    ARGUMENT_SECOND = 8,
    ARGUMENT_THIRD = 0xc,
    ARGUMENT_REST = 0x10,
    /* The local holding the va_list, under the saved ebx, ecx and edx. */
    VA_LIST = 0x10,
    FORWARD = 0x4cd56c
};

/* Original 0x4cd544 (stack: first, second, third, ...): returns 0x4cd56c(first, second, third,
 * &va_list) in eax, edx, ebx and ecx, keeping the caller's edx. */
uint32_t vertrix_port_rtl_vararg_call_4cd544(PORT_SIGNATURE)
{
    Port port;
    uint8_t stack[BELOW + 8 + 4 * 3];
    port_open_arguments(&port, stack, calls, services, globals, entry, BELOW, 3);
    const uint32_t va_list = entry->esp - VA_LIST;
    port_set32(&port, va_list, 0, entry->esp + ARGUMENT_REST);
    const uint32_t result = port_call(&port, FORWARD, port_u32(&port, entry->esp, ARGUMENT_FIRST),
                                      port_u32(&port, entry->esp, ARGUMENT_SECOND),
                                      port_u32(&port, entry->esp, ARGUMENT_THIRD), va_list);
    return port_return(&port, result, entry->edx);
}
