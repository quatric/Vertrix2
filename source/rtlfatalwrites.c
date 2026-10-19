#include "rtlfatalwrites.h"

#include "rtlterminatehandlers.h"

enum
{
    /* The count WriteFile reports, under the saved ebx, ecx, esi and edi. */
    BELOW = 0x14,
    WRITTEN = 0x14,

    STANDARD_HANDLES = 0x507c8c, /* the error output's handle at +8 */
    ERROR_OUTPUT = 8,
    WRITE_FILE = 0x4f1d08 /* an import slot */
};

/* Original 0x4e6250 (eax = the message, edx = the exit code): the message (to its terminator) is
 * written to the error output (WriteFile with the handle at 0x507c8c's +8), then exit(code) (a
 * jump into 0x4e078c). */
uint32_t vertrix_port_rtl_fatal_write_4e6250(PORT_SIGNATURE)
{
    Port port;
    uint8_t stack[BELOW + 8];
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    const uint32_t text = entry->eax;
    const uint32_t code = entry->edx;
    uint32_t length = 0;
    while (port_u8(&port, text, length) != 0 && !port.env.failed)
    {
        length++;
    }
    const uint32_t handle = port_u32(&port, port_u32(&port, STANDARD_HANDLES, 0), ERROR_OUTPUT);
    const uint32_t arguments[5] = {handle, text, length, entry->esp - WRITTEN, 0};
    const uint32_t ecx = entry->ecx & 0xffffff00u;
    port_call_stack(&port, port_u32(&port, WRITE_FILE, 0), text, handle, text + length, ecx,
                    arguments, 5);
    return vertrix_rtl_exit(&port, code, vertrix_lift_edx, ecx);
}
