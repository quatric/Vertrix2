#include "rtlspins.h"

/* Marked board cells spun out and replaced. */

/* A call that leaves its eax and edx in *eax and *edx; the eax. */
static uint32_t spin_call(Port *port, uint32_t *eax, uint32_t *edx, uint32_t target, uint32_t a,
                          uint32_t d, uint32_t ebx, uint32_t ecx, uint32_t esi, uint32_t edi,
                          uint32_t ebp)
{
    *eax = port_call_with(port, target, a, d, ebx, ecx, esi, edi, ebp);
    *edx = vertrix_lift_edx;
    return *eax;
}

/* The cell edi of the candidates locate (0x4360b0 or 0x436100; its row at ebp +
 * rowslot, column at ebp + colslot) spun: a random direction 0..7 (0x4826c0 of
 * 0x598d30, at ebp + turnslot, the old piece's +4 later at ebp + oldslot); the
 * old piece moved to the leaving slot +0x87c, handed 0x44cfd0 (0x4ac8f0), +0x4e
 * 100, shown (0x4ac7b0 with 4..7), +0x93 1, started (0x4ac510, 0x4ac380), set
 * spinning out; a new piece of a random kind of five, or of kind 5 (fixed), put
 * at its spot (0x430800), its picture, layer and frame those of the old
 * (0x4ac490, 0x4ac7d0, 0x4ac710), +0x93 1, +0x4e 0x32, handed 0x44ccd0, started
 * and set spinning in. *ebx and *ecx are left as the old and new piece. */
static void spin_cell(Port *port, uint32_t *eax, uint32_t *edx, uint32_t *ebx, uint32_t *ecx,
                      uint32_t board, uint32_t edi, uint32_t ebp, uint32_t locate, uint32_t rowslot,
                      uint32_t colslot, uint32_t turnslot, uint32_t oldslot, int fixed)
{
    uint32_t old;
    uint32_t fresh;
    uint32_t slot;
#define CALL(target, a, d) spin_call(port, eax, edx, target, a, d, *ebx, *ecx, board, edi, ebp)
    *eax = CALL(0x4826c0, 0x598d30, 8) & 0xffff;
    port_set32(port, ebp, turnslot, *eax);
    *eax += 4;
    port_set32(port, ebp, oldslot, *eax);
    if ((int32_t)*eax > 7)
    {
        port_set32(port, ebp, oldslot, *eax - 7);
    }
    *ecx = ebp + colslot;
    *ebx = ebp + rowslot;
    CALL(locate, board, edi);
    slot = board + port_u32(port, ebp, rowslot) * 0x34 + port_u32(port, ebp, colslot) * 4;
    old = port_u32(port, slot, 0x220);
    *ebx = old;
    port_set32(port, slot, 0x87c, old);
    port_set32(port, slot, 0x220, 0);
    CALL(0x4ac8f0, old, 0x44cfd0);
    port_set8(port, old, 0x4e, 0x64);
    CALL(0x4826c0, 0x598d30, 4);
    CALL(0x4ac7b0, old, (*eax & 0xffff) + 4);
    port_set8(port, old, 0x93, 1);
    CALL(0x4ac510, old, *edx);
    CALL(0x4ac380, old, *edx);
    port_set8(port, old, 0x44, 0x10);
    port_set8(port, old, 0x45, 0);
    port_set16(port, old, 0x46, 1);
    port_set32(port, old, 0x58, 0);
    port_set32(port, old, 0x5c, 4);
    port_set32(port, old, 0x60, 1);
    port_set32(port, old, 0x64, 0);
    port_set16(port, old, 8, port_u16(port, old, 0xe));
    port_set16(port, old, 0xa, port_u16(port, old, 0x16));
    port_set32(port, old, 0x68, 2);
    port_set16(port, old, 0x24, port_u32(port, ebp, oldslot));
    port_set32(port, old, 0x6c, 1);
    if (fixed)
    {
        fresh = CALL(0x430800, board, 5);
        slot = board + port_u32(port, ebp, rowslot) * 0x34;
        port_set32(port, ebp, -0x20u, slot);
    }
    else
    {
        fresh = CALL(0x430800, board, CALL(0x4826c0, 0x598d30, 5) & 0xffff);
        slot = board + port_u32(port, ebp, rowslot) * 0x34;
    }
    slot += port_u32(port, ebp, colslot) * 4;
    *edx = fixed ? port_u32(port, ebp, -0x20u) : port_u32(port, ebp, colslot) << 2;
    port_set32(port, slot, 0x220, fresh);
    *ecx = fresh;
    port_set16(port, fresh, 0xe, port_u16(port, old, 0xe));
    port_set16(port, fresh, 0x16, port_u16(port, old, 0x16));
    port_set16(port, fresh, 8, port_u16(port, fresh, 0xe));
    port_set16(port, fresh, 0xa, port_u16(port, fresh, 0x16));
    CALL(0x4ac490, fresh, port_u32(port, old, 0xd0));
    CALL(0x4ac7d0, fresh, port_u32(port, old, 0xc0));
    port_set8(port, fresh, 0x93, 1);
    port_set8(port, fresh, 0x4e, 0x32);
    CALL(0x4ac710, fresh, port_u32(port, old, 0xb8));
    CALL(0x4ac8f0, fresh, 0x44ccd0);
    CALL(0x4ac510, fresh, *edx);
    CALL(0x4ac380, fresh, *edx);
    port_set8(port, fresh, 0x44, 0);
    port_set8(port, fresh, 0x45, 0x10);
    port_set16(port, fresh, 0x46, 1);
    port_set32(port, fresh, 0x58, 0);
    port_set32(port, fresh, 0x5c, 4);
    port_set32(port, fresh, 0x60, 1);
    port_set32(port, fresh, 0x64, 0);
    port_set32(port, fresh, 0x68, 2);
    *eax = port_u32(port, ebp, turnslot);
    port_set32(port, fresh, 0x6c, 1);
    port_set16(port, fresh, 0x24, *eax);
#undef CALL
}

/* Original 0x437fe0: the marked cells of the board eax spun (spin_cell): the
 * 0x436030 candidates of 0x4360b0 into random kinds, then the 0x436070
 * candidates of 0x436100 into kind 5. eax 1, or 0 with no second candidates and
 * 0x436070 leaving edx 0; edx kept. */
uint32_t vertrix_port_board_spin_marked_437fe0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x44
    };
    Port port;
    uint8_t stack[BELOW + 8];
    uint32_t ebp = entry->esp - 4;
    uint32_t board = entry->eax;
    uint32_t eax;
    uint32_t edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t edi = entry->edi;
    uint32_t first;
    uint32_t second;
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -4u, entry->ebx);
    port_set32(&port, ebp, -8u, entry->ecx);
    port_set32(&port, ebp, -0xcu, entry->edx);
    port_set32(&port, ebp, -0x10u, entry->esi);
    port_set32(&port, ebp, -0x14u, entry->edi);
    first = spin_call(&port, &eax, &edx, 0x436030, board, entry->edx, ebx, ecx, board, edi, ebp);
    port_set32(&port, ebp, -0x18u, first);
    second = spin_call(&port, &eax, &edx, 0x436070, board, first, ebx, ecx, board, edi, ebp);
    port_set32(&port, ebp, -0x24u, second);
    if (edx == 0 && second == 0)
    {
        return port_return(&port, 0, entry->edx);
    }
    for (edi = 0; edi < port_u32(&port, ebp, -0x18u) && !port.env.failed; edi++)
    {
        spin_cell(&port, &eax, &edx, &ebx, &ecx, board, edi, ebp, 0x4360b0, -0x34u, -0x30u, -0x40u,
                  -0x38u, 0);
    }
    ebx = port_u32(&port, ebp, -0x24u);
    for (edi = 0; edi < port_u32(&port, ebp, -0x24u) && !port.env.failed; edi++)
    {
        spin_cell(&port, &eax, &edx, &ebx, &ecx, board, edi, ebp, 0x436100, -0x2cu, -0x28u, -0x1cu,
                  -0x3cu, 1);
    }
    return port_return(&port, 1, entry->edx);
}
