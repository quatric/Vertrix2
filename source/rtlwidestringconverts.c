#include "rtlwidestringconverts.h"

enum
{
    /* The frame under the return slot: the saved ecx, esi, edi and ebp, then a 4-byte buffer for
     * one converted character. */
    BELOW = 0x1c,
    SAVED_ECX = 4,
    SAVED_ESI = 8,
    SAVED_EDI = 0xc,
    SAVED_EBP = 0x10,
    BUFFER = 0x14,

    FAILED = 0xffffffffu,
    WIDE_TO_MULTIBYTE = 0x4e62e0
};

/* Original 0x4ea350 (eax = the destination or 0, edx = the wide string, ebx = the room): the
 * runtime's wcstombs. Each character is converted into the frame buffer (0x4e62e0, which returns
 * its length or -1); with a destination it is copied (rep movsd and movsb, so a length over 4 reads
 * on into the saved registers) while it fits, and a zero character is stored as the terminator.
 * Returns the bytes converted, or -1; edx (callers read it) is the last length, -1, or what it was
 * when nothing set it, and without a destination the edx 0x4e62e0 hands back. */
uint32_t vertrix_port_rtl_wide_to_multibyte_4ea350(PORT_SIGNATURE)
{
    Port port;
    uint8_t stack[BELOW + 8];
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    port_set32(&port, entry->esp - SAVED_ECX, 0, entry->ecx);
    port_set32(&port, entry->esp - SAVED_ESI, 0, entry->esi);
    port_set32(&port, entry->esp - SAVED_EDI, 0, entry->edi);
    port_set32(&port, entry->esp - SAVED_EBP, 0, entry->ebp);
    const uint32_t buffer = entry->esp - BUFFER;
    uint32_t destination = entry->eax;
    uint32_t text = entry->edx;
    uint32_t room = entry->ebx;
    uint32_t total = 0;
    uint32_t edx = entry->edx;

    if (destination == 0)
    {
        while (port_u16(&port, text, 0) != 0 && !port.env.failed)
        {
            const uint32_t length =
                port_call(&port, WIDE_TO_MULTIBYTE, buffer, port_u16(&port, text, 0), 0, 0);
            edx = vertrix_lift_edx;
            if (length == FAILED)
            {
                return port_return(&port, FAILED, edx);
            }
            text += 2;
            total += length;
        }
        return port_return(&port, total, edx);
    }

    while (room != 0 && !port.env.failed)
    {
        const uint32_t wide = port_u16(&port, text, 0);
        if (wide == 0)
        {
            port_set8(&port, destination, 0, 0);
            break;
        }
        const uint32_t length = port_call(&port, WIDE_TO_MULTIBYTE, buffer, wide, 0, 0);
        edx = length;
        if (length == FAILED)
        {
            return port_return(&port, FAILED, edx);
        }
        if (length > room)
        {
            break;
        }
        for (uint32_t i = 0; i < length && !port.env.failed; i++)
        {
            port_set8(&port, destination + i, 0, port_u8(&port, buffer + i, 0));
        }
        text += 2;
        total += length;
        destination += length;
        room -= length;
    }
    return port_return(&port, total, edx);
}
