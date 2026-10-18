#include "rtlextras.h"

/* Board cells' extra objects. */

/* Original 0x4398c0: on the board eax every cell marked 2 (+0xb94, 5 rows of 13) has its extra
 * object +0xbdc (rows of 0x34 bytes) destroyed (its class +0x158's first method with 2) and the
 * slot cleared. eax as last left (the row's end, an object or its answer), edx kept. */
uint32_t vertrix_port_board_clear_marked_extra_4398c0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x2c
    };
    Port port;
    uint8_t stack[BELOW + 8];
    uint32_t ebp = entry->esp - 4;
    uint32_t board = entry->eax;
    uint32_t eax = entry->eax;
    uint32_t ebx = entry->ebx;
    uint32_t edi = entry->edi;
    uint32_t row;
    uint32_t column;
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -4u, entry->ebx);
    port_set32(&port, ebp, -8u, entry->ecx);
    port_set32(&port, ebp, -0xcu, entry->edx);
    port_set32(&port, ebp, -0x10u, entry->esi);
    port_set32(&port, ebp, -0x14u, entry->edi);
    for (row = 0; row < 5 && !port.env.failed; row++)
    {
        uint32_t cells = board + row * 0x34;
        eax = cells + 0x34;
        ebx = board + row * 0xd;
        for (column = 0; column < 13 && !port.env.failed; column++, ebx++)
        {
            uint32_t slot = cells + column * 4;
            if (port_u8(&port, ebx, 0xb94) != 2)
            {
                continue;
            }
            eax = port_u32(&port, slot, 0xbdc);
            if (eax != 0)
            {
                edi = port_u32(&port, eax, 0x158);
                eax = port_call_with(&port, port_u32(&port, edi, 0), eax, 2, ebx, slot, slot, edi,
                                     ebp);
            }
            port_set32(&port, slot, 0xbdc, 0);
        }
        edi = board + 0x104;
    }
    return port_return(&port, eax, entry->edx);
}
