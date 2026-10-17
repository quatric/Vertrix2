#include "port_rtlstackpairs.h"

/* A cdecl varargs entry of the runtime's printf core: hands its first two arguments and a pointer
 * to the rest to 0x4e2434. */

enum
{
    BELOW = 0xc,
    ARGUMENT_FIRST = 4,
    ARGUMENT_SECOND = 8,
    ARGUMENT_REST = 0xc,
    /* The local holding the va_list, under the saved ebx and edx. */
    VA_LIST = 0xc,
    FORMAT_OUTPUT = 0x4e2434
};

/* Original 0x4dabe0 (stack: first, second, ...): 0x4e2434(first, second, &va_list) with eax, edx
 * and ebx. Nothing reads its result. */
uint32_t vertrix_port_rtl_stack_pair_call_4dabe0(PORT_SIGNATURE)
{
    Port port;
    uint8_t stack[BELOW + 8 + 4 * 2];
    port_open_arguments(&port, stack, calls, services, globals, entry, BELOW, 2);
    const uint32_t va_list = entry->esp - VA_LIST;
    port_set32(&port, va_list, 0, entry->esp + ARGUMENT_REST);
    port_call(&port, FORMAT_OUTPUT, port_u32(&port, entry->esp, ARGUMENT_FIRST),
              port_u32(&port, entry->esp, ARGUMENT_SECOND), va_list, 0);
    return port_return(&port, 0, 0);
}
