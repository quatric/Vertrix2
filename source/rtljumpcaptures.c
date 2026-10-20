#include "rtljumpcaptures.h"

enum
{
    BELOW = 0,

    /* The buffer: the registers, the return address, the stack after the return, the six segment
     * registers (words) and the exception chain. */
    SAVED_EBX = 0,
    SAVED_ECX = 4,
    SAVED_EDX = 8,
    SAVED_ESI = 0xc,
    SAVED_EDI = 0x10,
    SAVED_EBP = 0x14,
    SAVED_RETURN = 0x18,
    SAVED_ESP = 0x1c,
    SAVED_SEGMENTS = 0x20,
    SEGMENT_COUNT = 6,
    SAVED_CHAIN = 0x2c
};

/* Original 0x4d9f06 (eax = the buffer): setjmp(). The caller's registers, the return address, the
 * stack pointer past it, the segment registers (0 in the lifted runtime, which has none) and the
 * exception chain (fs:[0]) go to the buffer; returns 0. The oracle cannot check it: its stack and
 * segments are not the lifted runtime's (docs/LIFTED.md). */
uint32_t vertrix_port_rtl_jump_capture_4d9f06(PORT_SIGNATURE)
{
    Port port;
    uint8_t stack[BELOW + 8];
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    const uint32_t buffer = entry->eax;
    port_set32(&port, buffer, SAVED_EBX, entry->ebx);
    port_set32(&port, buffer, SAVED_ECX, entry->ecx);
    port_set32(&port, buffer, SAVED_EDX, entry->edx);
    port_set32(&port, buffer, SAVED_ESI, entry->esi);
    port_set32(&port, buffer, SAVED_EDI, entry->edi);
    port_set32(&port, buffer, SAVED_EBP, entry->ebp);
    port_set32(&port, buffer, SAVED_RETURN, port_u32(&port, entry->esp, 0));
    port_set32(&port, buffer, SAVED_ESP, entry->esp + 4);
    for (uint32_t i = 0; i < SEGMENT_COUNT; i++)
    {
        port_set16(&port, buffer, SAVED_SEGMENTS + 2 * i, 0);
    }
    port_set32(&port, buffer, SAVED_CHAIN, port.env.chain);
    return port_return(&port, 0, entry->edx);
}
