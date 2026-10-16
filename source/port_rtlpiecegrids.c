#include "port_rtlpiecegrids.h"

/* The grids of the pieces each player may still take. */

/* A call that leaves its eax and edx in *eax and *edx; the eax. */
static uint32_t grid_call(Port *port, uint32_t *eax, uint32_t *edx, uint32_t target, uint32_t a,
                          uint32_t d, uint32_t ebx, uint32_t ecx, uint32_t esi, uint32_t edi,
                          uint32_t ebp)
{
    *eax = port_call_with(port, target, a, d, ebx, ecx, esi, edi, ebp);
    *edx = vertrix_lift_edx;
    return *eax;
}

/* Original 0x4726d0: the two players 0x540f8c and 0x540f90 each given a grid of 7 rows by 4
 * (ebp-0x148 and ebp-0xd8): a cell is 1 when 0x4178d0 has a piece for the player's level byte
 * +0x488 and the cell's index, and its column is within the player's +0x178 (at most 3; 3 when
 * 0x532bc4). A player out (+0x4c4 1) or not playing (+0x4c5 0) has an empty grid; otherwise each
 * cell that the level tables 0x4f9320/0x4f9538 give a kind for is cleared when the other player
 * is out and 0x4f9750 is 0 for it, not playing and 0x4f9788 is 0, or playing and 0x43d3d0 gives
 * 1 and 0x4f97c0 is 0 (else what 0x43d3d0 left in dl). Either player at its end (0x43d3b0 1)
 * empties both. The grids handed to the players' +0x3b8 (0x429df0). edx kept. */
uint32_t vertrix_port_piece_grids_4726d0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x14c
    };
    Port port;
    uint8_t stack[BELOW + 8];
    uint32_t ebp = entry->esp - 4;
    uint32_t first;
    uint32_t second;
    uint32_t eax;
    uint32_t edx;
    uint32_t ebx;
    uint32_t ecx;
    uint32_t esi;
    uint32_t edi;
    uint32_t limit;
#define CALL(target, a, d) grid_call(&port, &eax, &edx, target, a, d, ebx, ecx, esi, edi, ebp)
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -4u, entry->ebx);
    port_set32(&port, ebp, -8u, entry->ecx);
    port_set32(&port, ebp, -0xcu, entry->edx);
    port_set32(&port, ebp, -0x10u, entry->esi);
    port_set32(&port, ebp, -0x14u, entry->edi);
    first = port_u32(&port, 0, 0x540f8c);
    second = port_u32(&port, 0, 0x540f90);
    esi = first;
    ebx = second;
    port_set32(&port, ebp, -0x64u, port_u32(&port, esi, 0x3b8));
    port_set32(&port, ebp, -0x60u, port_u32(&port, ebx, 0x3b8));
    edx = port_u32(&port, esi, 0x178);
    limit = edx > 3 || port_u32(&port, 0, 0x532bc4) == 1 ? 3 : edx;
    port_set32(&port, ebp, -0x38u, limit);
    ecx = 0;
    port_set32(&port, ebp, -0x40u, ecx);
    do
    {
        eax = port_u32(&port, ebp, -0x40u);
        edi = 0;
        port_set32(&port, ebp, -0x24u, eax);
        port_set32(&port, ebp, -0x2cu, eax);
        do
        {
            port_set32(&port, ebp, -0x68u, port_u32(&port, esi, 0x488));
            if (CALL(0x4178d0, port_u8(&port, ebp, -0x68u), ecx & 0xff) == 0xffffffffu ||
                edi > port_u32(&port, ebp, -0x38u))
            {
                edx = 0;
                port_set32(&port, ebp + port_u32(&port, ebp, -0x24u), -0x148u, 0);
            }
            else
            {
                port_set32(&port, ebp + port_u32(&port, ebp, -0x2cu), -0x148u, 1);
            }
            eax = port_u32(&port, ebp, -0x24u) + 4;
            edx = port_u32(&port, ebp, -0x2cu) + 4;
            ecx++;
            edi++;
            port_set32(&port, ebp, -0x24u, eax);
            port_set32(&port, ebp, -0x2cu, edx);
        } while (edi < 4 && !port.env.failed);
        edi = port_u32(&port, ebp, -0x40u) + 0x10;
        port_set32(&port, ebp, -0x40u, edi);
    } while (edi != 0x70 && !port.env.failed);
    eax = (eax & 0xffffff00u) | port_u8(&port, esi, 0x4c4);
    if ((eax & 0xff) != 1 &&
        (eax = (eax & 0xffffff00u) | port_u8(&port, esi, 0x4c5), (eax & 0xff) != 0))
    {
        ecx = 0;
        edi = 0x10;
        port_set32(&port, ebp, -0x4cu, ecx);
        port_set32(&port, ebp, -0x58u, edi);
        do
        {
            edi = port_u32(&port, ebp, -0x4cu) << 4;
            eax = port_u32(&port, ebp, -0x58u);
            port_set32(&port, ebp, -0x34u, eax);
            do
            {
                uint32_t kind;
                eax = port_u32(&port, esi, 0x488) * 0x1c;
                edx = eax + ecx;
                kind = port_u8(&port, edx, 0x4f9320);
                eax = (eax & 0xffff0000u) | ((uint32_t)port_u8(&port, edx, 0x4f9538) << 8) | kind;
                if (kind != 0 && (eax & 0xff00) != 0)
                {
                    eax = kind - 1;
                    edx = (edx & 0xffffff00u) | 1;
                    port_set32(&port, ebp, -0x1cu, eax);
                    eax = port_u8(&port, ebx, 0x4c4);
                    if (eax == (edx & 0xff))
                    {
                        edx = (port_u32(&port, ebp, -0x1cu) & 0xffffff00u) |
                              port_u8(&port, port_u32(&port, ebp, -0x1cu), 0x4f9750);
                    }
                    else if (port_u8(&port, ebx, 0x4c5) == 0)
                    {
                        edx = (port_u32(&port, ebp, -0x1cu) & 0xffffff00u) |
                              port_u8(&port, port_u32(&port, ebp, -0x1cu), 0x4f9788);
                    }
                    else if (CALL(0x43d3d0, ebx, edx) == 1)
                    {
                        edx = (port_u32(&port, ebp, -0x1cu) & 0xffffff00u) |
                              port_u8(&port, port_u32(&port, ebp, -0x1cu), 0x4f97c0);
                    }
                    if ((edx & 0xff) == 0)
                    {
                        edx = 0;
                        port_set32(&port, ebp + edi, -0x148u, 0);
                    }
                }
                eax = port_u32(&port, ebp, -0x34u);
                edi += 4;
                ecx++;
            } while (edi != eax && !port.env.failed);
            edx = port_u32(&port, ebp, -0x58u) + 0x10;
            edi = port_u32(&port, ebp, -0x4cu) + 1;
            port_set32(&port, ebp, -0x58u, edx);
            port_set32(&port, ebp, -0x4cu, edi);
        } while (edi < 7 && !port.env.failed);
    }
    else
    {
        eax = 0x10;
        edi = 0;
        port_set32(&port, ebp, -0x54u, eax);
        do
        {
            ecx = edi << 4;
            eax = port_u32(&port, ebp, -0x54u);
            do
            {
                ecx += 4;
                edx = 0;
                port_set32(&port, ebp + ecx, -0x14cu, 0);
            } while (ecx != eax && !port.env.failed);
            ecx = port_u32(&port, ebp, -0x54u) + 0x10;
            edi++;
            port_set32(&port, ebp, -0x54u, ecx);
        } while (edi < 7 && !port.env.failed);
    }
    edi = port_u32(&port, ebx, 0x178);
    limit = edi > 3 || port_u32(&port, 0, 0x532bc4) == 1 ? 3 : edi;
    port_set32(&port, ebp, -0x3cu, limit);
    ecx = 0;
    port_set32(&port, ebp, -0x44u, ecx);
    do
    {
        eax = port_u32(&port, ebp, -0x44u);
        edi = 0;
        port_set32(&port, ebp, -0x20u, eax);
        port_set32(&port, ebp, -0x28u, eax);
        do
        {
            port_set32(&port, ebp, -0x68u, port_u32(&port, ebx, 0x488));
            if (CALL(0x4178d0, port_u8(&port, ebp, -0x68u), ecx & 0xff) == 0xffffffffu ||
                edi > port_u32(&port, ebp, -0x3cu))
            {
                edx = 0;
                port_set32(&port, ebp + port_u32(&port, ebp, -0x20u), -0xd8u, 0);
            }
            else
            {
                port_set32(&port, ebp + port_u32(&port, ebp, -0x28u), -0xd8u, 1);
            }
            eax = port_u32(&port, ebp, -0x20u) + 4;
            edx = port_u32(&port, ebp, -0x28u) + 4;
            ecx++;
            edi++;
            port_set32(&port, ebp, -0x20u, eax);
            port_set32(&port, ebp, -0x28u, edx);
        } while (edi < 4 && !port.env.failed);
        edi = port_u32(&port, ebp, -0x44u) + 0x10;
        port_set32(&port, ebp, -0x44u, edi);
    } while (edi != 0x70 && !port.env.failed);
    eax = (eax & 0xffffff00u) | port_u8(&port, ebx, 0x4c4);
    if ((eax & 0xff) != 1 &&
        (eax = (eax & 0xffffff00u) | port_u8(&port, ebx, 0x4c5), (eax & 0xff) != 0))
    {
        ecx = 0;
        edi = 0x10;
        port_set32(&port, ebp, -0x48u, ecx);
        port_set32(&port, ebp, -0x50u, edi);
        do
        {
            edi = port_u32(&port, ebp, -0x48u) << 4;
            eax = port_u32(&port, ebp, -0x50u);
            port_set32(&port, ebp, -0x30u, eax);
            do
            {
                uint32_t kind;
                eax = port_u32(&port, ebx, 0x488) * 0x1c;
                kind = port_u8(&port, ecx + eax, 0x4f9320);
                edx = (edx & 0xffffff00u) | kind;
                eax = (eax & 0xffffff00u) | port_u8(&port, ecx + eax, 0x4f9538);
                if (kind != 0 && (eax & 0xff) != 0)
                {
                    edx = kind - 1;
                    eax = (eax & 0xffffff00u) | port_u8(&port, esi, 0x4c4);
                    port_set32(&port, ebp, -0x18u, edx);
                    edx = (edx & 0xffffff00u) | 1;
                    if ((eax & 0xff) == 1)
                    {
                        edx = (port_u32(&port, ebp, -0x18u) & 0xffffff00u) |
                              port_u8(&port, port_u32(&port, ebp, -0x18u), 0x4f9750);
                    }
                    else if ((eax = (eax & 0xffffff00u) | port_u8(&port, esi, 0x4c5),
                              (eax & 0xff) == 0))
                    {
                        edx = (port_u32(&port, ebp, -0x18u) & 0xffffff00u) |
                              port_u8(&port, port_u32(&port, ebp, -0x18u), 0x4f9788);
                    }
                    else if (CALL(0x43d3d0, esi, edx) == 1)
                    {
                        edx = (port_u32(&port, ebp, -0x18u) & 0xffffff00u) |
                              port_u8(&port, port_u32(&port, ebp, -0x18u), 0x4f97c0);
                    }
                    if ((edx & 0xff) == 0)
                    {
                        edx = 0;
                        port_set32(&port, ebp + edi, -0xd8u, 0);
                    }
                }
                eax = port_u32(&port, ebp, -0x30u);
                edi += 4;
                ecx++;
            } while (edi != eax && !port.env.failed);
            edx = port_u32(&port, ebp, -0x50u) + 0x10;
            edi = port_u32(&port, ebp, -0x48u) + 1;
            port_set32(&port, ebp, -0x50u, edx);
            port_set32(&port, ebp, -0x48u, edi);
        } while (edi < 7 && !port.env.failed);
    }
    else
    {
        eax = 0x10;
        edx = 0;
        port_set32(&port, ebp, -0x5cu, eax);
        do
        {
            ecx = edx << 4;
            eax = port_u32(&port, ebp, -0x5cu);
            do
            {
                ecx += 4;
                edi = 0;
                port_set32(&port, ebp + ecx, -0xdcu, 0);
            } while (ecx != eax && !port.env.failed);
            eax = port_u32(&port, ebp, -0x5cu) + 0x10;
            edx++;
            port_set32(&port, ebp, -0x5cu, eax);
        } while (edx < 7 && !port.env.failed);
    }
    if (CALL(0x43d3b0, esi, edx) == 1 || CALL(0x43d3b0, ebx, edx) == 1)
    {
        esi = 0x10;
        ebx = 0;
        edi = 0;
        do
        {
            ecx = ebx << 4;
            edx = esi;
            do
            {
                ecx += 4;
                port_set32(&port, ebp + ecx, -0xdcu, edi);
                port_set32(&port, ebp + ecx, -0x14cu, edi);
            } while (ecx != edx && !port.env.failed);
            ebx++;
            esi += 0x10;
        } while (ebx < 7 && !port.env.failed);
    }
    CALL(0x429df0, port_u32(&port, ebp, -0x64u), ebp - 0x148);
    CALL(0x429df0, port_u32(&port, ebp, -0x60u), ebp - 0xd8);
#undef CALL
    return port_return(&port, eax, entry->edx);
}
