#include "rtlconverts.h"

/* Cells converted on the two boards. */

/* Original 0x436b40 (one stack argument, popped: the second count): ecx cells of the board eax
 * and the stack count of the board edx converted: each a cell picked (0x4360b0 into a row and a
 * column) is marked 2 (+0xb94 by 13), its piece (+0x220 by 0x34 and 4) moved to the leaving slot
 * +0x87c, handed 0x44e380 (0x4ac8f0) with +0x4e 100 and shown (0x4ac7b0 with 5); a new piece of a
 * random kind of five (0x4826c0 of 0x598d30, 0x430800) put in its place, at its spot (0x4ac490
 * with +0xd0) shown with its frame +0xb8 (0x4ac7b0, 0x4ac710), both started (0x4ac510,
 * 0x4ac380; the old with 0x44e4a0) and the new handed on (0x4ac8f0). */
uint32_t vertrix_port_boards_convert_counts_436b40(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x28
    };
    Port port;
    uint8_t stack[BELOW + 8 + 4];
    uint32_t ebp = entry->esp - 4;
    uint32_t first = entry->eax;
    uint32_t second = entry->edx;
    uint32_t eax = entry->eax;
    uint32_t edx = 0;
    uint32_t ebx;
    uint32_t ecx = entry->ecx;
    uint32_t edi;
    uint32_t old;
    uint32_t fresh;
    uint32_t slot;
#define CALL(target, a, d) port_call_with(&port, target, a, d, ebx, ecx, second, edi, ebp)
    port_open_arguments(&port, stack, calls, services, globals, entry, BELOW, 1);
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -4u, entry->esi);
    port_set32(&port, ebp, -8u, entry->edi);
    port_set32(&port, ebp, -0x14u, ecx);
    port_set32(&port, ebp, -0xcu, 0);
    edi = first;
    if (ecx != 0)
    {
        do
        {
            ecx = ebp - 0x20;
            ebx = ebp - 0x24;
            CALL(0x4360b0, first, 0);
            slot = first + port_u32(&port, ebp, -0x24u) * 0x34 + port_u32(&port, ebp, -0x20u) * 4;
            port_set8(&port,
                      first + port_u32(&port, ebp, -0x24u) * 0xd + port_u32(&port, ebp, -0x20u),
                      0xb94, 2);
            old = port_u32(&port, slot, 0x220);
            ecx = old;
            port_set32(&port, slot, 0x87c, old);
            port_set32(&port, slot, 0x220, 0);
            CALL(0x4ac8f0, old, 0x44e380);
            port_set8(&port, old, 0x4e, 0x64);
            CALL(0x4ac7b0, old, 5);
            eax = CALL(0x4826c0, 0x598d30, 5);
            fresh = CALL(0x430800, first, eax & 0xffff);
            ebx = first + port_u32(&port, ebp, -0x24u) * 0x34;
            port_set32(&port, ebp, -0x10u, ebx);
            ebx = port_u32(&port, ebp, -0x20u) * 4 + ebx;
            port_set32(&port, ebx, 0x220, fresh);
            ebx = fresh;
            CALL(0x4ac490, fresh, port_u32(&port, old, 0xd0));
            CALL(0x4ac7b0, fresh, 5);
            CALL(0x4ac710, fresh, port_u32(&port, old, 0xb8));
            CALL(0x4ac510, fresh, vertrix_lift_edx);
            CALL(0x4ac380, fresh, vertrix_lift_edx);
            CALL(0x4ac510, old, vertrix_lift_edx);
            CALL(0x4ac380, old, 0x44e4a0);
            ecx = port_u32(&port, ebp, -0xcu);
            eax = CALL(0x4ac8f0, fresh, vertrix_lift_edx);
            edx = vertrix_lift_edx;
            ecx++;
            ebx = port_u32(&port, ebp, -0x14u);
            port_set32(&port, ebp, -0xcu, ecx);
        } while (ecx < ebx && !port.env.failed);
    }
    eax = port_u32(&port, ebp, 8);
    edi = 0;
    if (eax == 0)
    {
        return port_return(&port, eax, edx);
    }
    do
    {
        ecx = ebp - 0x18;
        ebx = ebp - 0x1c;
        CALL(0x4360b0, second, 0);
        ecx = port_u32(&port, ebp, -0x18u);
        port_set8(&port, second + port_u32(&port, ebp, -0x1cu) * 0xd + ecx, 0xb94, 2);
        slot = second + port_u32(&port, ebp, -0x1cu) * 0x34 + ecx * 4;
        old = port_u32(&port, slot, 0x220);
        ebx = old;
        port_set32(&port, slot, 0x87c, old);
        port_set32(&port, slot, 0x220, 0);
        CALL(0x4ac8f0, old, 0x44e380);
        port_set8(&port, old, 0x4e, 0x64);
        CALL(0x4ac7b0, old, 5);
        eax = CALL(0x4826c0, 0x598d30, 5);
        fresh = CALL(0x430800, second, eax & 0xffff);
        ecx = second + port_u32(&port, ebp, -0x1cu) * 0x34;
        port_set32(&port, ebp, -0x10u, ecx);
        ecx = port_u32(&port, ebp, -0x18u) * 4 + ecx;
        port_set32(&port, ecx, 0x220, fresh);
        ecx = fresh;
        CALL(0x4ac490, fresh, port_u32(&port, old, 0xd0));
        CALL(0x4ac7b0, fresh, 5);
        CALL(0x4ac710, fresh, port_u32(&port, old, 0xb8));
        CALL(0x4ac510, fresh, vertrix_lift_edx);
        CALL(0x4ac380, fresh, vertrix_lift_edx);
        edi++;
        CALL(0x4ac510, old, vertrix_lift_edx);
        CALL(0x4ac380, old, 0x44e4a0);
        ecx = port_u32(&port, ebp, 8);
        eax = CALL(0x4ac8f0, fresh, vertrix_lift_edx);
        edx = vertrix_lift_edx;
    } while (edi < ecx && !port.env.failed);
#undef CALL
    return port_return(&port, eax, edx);
}

/* One random cell of the board converted for 0x436d80 (count candidates, the row and column at
 * ebp + rowslot / colslot): a candidate picked (0x4826c0 of 0x598d30, 0x4360b0), marked 2, its
 * piece moved to the leaving slot, handed 0x44e510 with +0x4e 100 and shown; a new piece of the
 * kind (0x430800) put in its place, placed, shown with its frame, both started (the old with
 * 0x44e590), the new handed on and its layer +0x44 0. Returns eax; *ebx (left the old
 * piece), *ecx and *edx updated. */
static uint32_t convert_one(Port *port, const LiftEntry *entry, uint32_t board, uint32_t count,
                            uint32_t rowslot, uint32_t colslot, uint32_t *ebx, uint32_t esi,
                            uint32_t edi, uint32_t *ecx, uint32_t *edx)
{
    uint32_t ebp = entry->esp - 4;
    uint32_t pick;
    uint32_t row;
    uint32_t column;
    uint32_t slot;
    uint32_t old;
    uint32_t fresh;
    uint32_t eax;
    *ecx = ebp + colslot;
    pick = port_call_with(port, 0x4826c0, 0x598d30, count & 0xffff, *ebx, *ecx, esi, edi, ebp);
    port_call_with(port, 0x4360b0, board, pick & 0xffff, ebp + rowslot, *ecx, esi, edi, ebp);
    row = port_u32(port, ebp + rowslot, 0);
    column = port_u32(port, ebp + colslot, 0);
    port_set8(port, board + row * 0xd + column, 0xb94, 2);
    slot = board + row * 0x34 + column * 4;
    old = port_u32(port, slot, 0x220);
    port_set32(port, slot, 0x87c, old);
    port_set32(port, slot, 0x220, 0);
    port_call_with(port, 0x4ac8f0, old, 0x44e510, old, *ecx, esi, edi, ebp);
    port_set8(port, old, 0x4e, 0x64);
    port_call_with(port, 0x4ac7b0, old, 5, old, *ecx, esi, edi, ebp);
    fresh =
        port_call_with(port, 0x430800, board, port_u32(port, ebp, -0xcu), old, *ecx, esi, edi, ebp);
    row = port_u32(port, ebp + rowslot, 0);
    port_set32(port, ebp, -0x14u, board + row * 0x34);
    slot = port_u32(port, ebp + colslot, 0) * 4 + board + row * 0x34;
    port_set32(port, slot, 0x220, fresh);
    *ecx = fresh;
    port_call_with(port, 0x4ac490, fresh, port_u32(port, old, 0xd0), old, fresh, esi, edi, ebp);
    port_call_with(port, 0x4ac7b0, fresh, 5, old, fresh, esi, edi, ebp);
    port_call_with(port, 0x4ac710, fresh, port_u32(port, old, 0xb8), old, fresh, esi, edi, ebp);
    port_call_with(port, 0x4ac510, fresh, vertrix_lift_edx, old, fresh, esi, edi, ebp);
    port_call_with(port, 0x4ac380, fresh, vertrix_lift_edx, old, fresh, esi, edi, ebp);
    port_call_with(port, 0x4ac510, old, vertrix_lift_edx, old, fresh, esi, edi, ebp);
    port_call_with(port, 0x4ac380, old, 0x44e590, old, fresh, esi, edi, ebp);
    eax = port_call_with(port, 0x4ac8f0, fresh, vertrix_lift_edx, old, fresh, esi, edi, ebp);
    *edx = vertrix_lift_edx;
    *ebx = old;
    port_set8(port, fresh, 0x44, 0);
    return eax;
}

/* Original 0x436d80 (one stack argument, popped: the first count): the stack count of tries on
 * the board eax and ecx on the board edx, each converting a random cell among the candidates
 * 0x436030 counts (convert_one) into pieces of the kind ebx. */
uint32_t vertrix_port_boards_convert_random_436d80(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x2c
    };
    Port port;
    uint8_t stack[BELOW + 8 + 4];
    uint32_t ebp = entry->esp - 4;
    uint32_t first = entry->eax;
    uint32_t second = entry->edx;
    uint32_t eax = entry->eax;
    uint32_t edx = 0;
    uint32_t ebx = entry->ebx;
    uint32_t ecx;
    uint32_t esi;
    port_open_arguments(&port, stack, calls, services, globals, entry, BELOW, 1);
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -4u, entry->esi);
    port_set32(&port, ebp, -8u, entry->edi);
    port_set32(&port, ebp, -0xcu, entry->ebx);
    port_set32(&port, ebp, -0x10u, entry->ecx);
    ecx = port_u32(&port, ebp, 8);
    port_set32(&port, ebp, -0x18u, 0);
    if (ecx != 0)
    {
        do
        {
            eax = port_call_with(&port, 0x436030, first, edx, ebx, ecx, first, second, ebp);
            edx = eax;
            if (eax != 0)
            {
                eax = convert_one(&port, entry, first, edx, -0x28u, -0x24u, &ebx, first, second,
                                  &ecx, &edx);
            }
            ebx = port_u32(&port, ebp, -0x18u) + 1;
            edx = port_u32(&port, ebp, 8);
            port_set32(&port, ebp, -0x18u, ebx);
        } while (ebx < edx && !port.env.failed);
    }
    ecx = port_u32(&port, ebp, -0x10u);
    esi = 0;
    if (ecx != 0)
    {
        do
        {
            eax = port_call_with(&port, 0x436030, second, edx, ebx, ecx, esi, second, ebp);
            edx = eax;
            if (eax != 0)
            {
                eax = convert_one(&port, entry, second, edx, -0x20u, -0x1cu, &ebx, esi, second,
                                  &ecx, &edx);
            }
            ecx = port_u32(&port, ebp, -0x10u);
            esi++;
        } while (esi < ecx && !port.env.failed);
    }
    return port_return(&port, eax, edx);
}
