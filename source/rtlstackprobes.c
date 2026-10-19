#include "rtlstackprobes.h"

enum
{
    BELOW = 0x48,
    SIZE = 4,
    PAGE = 0x1000,
    /* Under the saved eax and ebx. */
    FIRST_TOUCH = 0xc
};

/* Original 0x4e08f0 (stack: size; stdcall): the runtime's stack probe. It touches the stack a page
 * at a time below its saved registers, storing each touch's own offset there (-4, -0x1004, ...),
 * while the size counted down a page at a time stays above a page (a signed compare), so a size of
 * a page or less still touches once. eax and edx are kept. */
uint32_t vertrix_port_rtl_stack_probe_4e08f0(PORT_SIGNATURE)
{
    Port port;
    uint8_t stack[BELOW + 8 + 4 * 1];
    port_open_arguments(&port, stack, calls, services, globals, entry, BELOW, 1);
    int32_t size = (int32_t)port_u32(&port, entry->esp, SIZE);
    uint32_t touch = 0xfffffffcu;
    int32_t before;
    do
    {
        port_set32(&port, entry->esp - FIRST_TOUCH + 4, touch, touch);
        touch -= PAGE;
        before = size;
        size = (int32_t)((uint32_t)size - PAGE);
    } while (before > PAGE);
    return port_return(&port, entry->eax, entry->edx);
}
