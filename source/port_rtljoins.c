#include "port_rtljoins.h"

/* Two boards' slots swapped and their pieces joined. */

/* A call that leaves its eax and edx in *eax and *edx; the eax. */
static uint32_t join_call(Port *port, uint32_t *eax, uint32_t *edx, uint32_t target, uint32_t a,
                          uint32_t d, uint32_t ebx, uint32_t ecx, uint32_t esi, uint32_t edi,
                          uint32_t ebp)
{
    vertrix_lift_in_esi = esi;
    vertrix_lift_in_edi = edi;
    vertrix_lift_in_ebp = ebp;
    *eax = lift_call_arguments(&port->env, target, a, d, ebx, ecx, NULL, 0);
    vertrix_lift_in_esi = vertrix_lift_in_edi = vertrix_lift_in_ebp = 0;
    *edx = vertrix_lift_edx;
    return *eax;
}

static uint32_t extend16(uint32_t value)
{
    return (uint32_t)(int32_t)(int16_t)(value & 0xffffu);
}

static uint32_t low16(uint32_t value, uint32_t word)
{
    return (value & 0xffff0000u) | (word & 0xffffu);
}

/* Original 0x432ba0 (two stack arguments, popped: the second row and column): the slot of the
 * board eax at the row edx and column ebx swapped with the one of the board ecx at the stack row
 * and column (rows of 0x34 bytes). eax the second slot, edx its old value. */
uint32_t vertrix_port_board_swap_slots_432ba0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 8
    };
    Port port;
    uint8_t stack[BELOW + 8 + 2 * 4];
    uint32_t first;
    uint32_t second;
    uint32_t value;
    port_open_arguments(&port, stack, calls, services, globals, entry, BELOW, 2);
    port_set32(&port, entry->esp, -4u, entry->esi);
    port_set32(&port, entry->esp, -8u, entry->edi);
    first = entry->eax + entry->edx * 0x34 + entry->ebx * 4;
    second =
        entry->ecx + port_u32(&port, entry->esp, 4) * 0x34 + port_u32(&port, entry->esp, 8) * 4;
    value = port_u32(&port, second, 0);
    port_set32(&port, second, 0, port_u32(&port, first, 0));
    port_set32(&port, first, 0, value);
    return port_return(&port, second, value);
}

/* A piece of a joined board blown away: its spot +0xe/+0x16 kept at +8/+0xa, handed 0x44ece0
 * (0x4ac8f0) with +0x4e 100, shown (0x4ac7b0 with 5), sent from its middle (0x4ad510), turned a
 * random 360 (0x4826c0 of 0x598d30) at the spin 10, waited 12 (0x4ac860) at the speed 100 and
 * the fall 1. */
static void blow_away(Port *port, uint32_t piece, uint32_t *ebx, uint32_t *ecx, uint32_t edi,
                      uint32_t ebp)
{
    uint32_t eax;
    uint32_t edx;
    port_set16(port, piece, 8, port_u16(port, piece, 0xe));
    port_set16(port, piece, 0xa, port_u16(port, piece, 0x16));
    join_call(port, &eax, &edx, 0x4ac8f0, piece, 0x44ece0, *ebx, *ecx, piece, edi, ebp);
    port_set8(port, piece, 0x4e, 0x64);
    join_call(port, &eax, &edx, 0x4ac7b0, piece, 5, *ebx, *ecx, piece, edi, ebp);
    *ecx = extend16(port_u16(port, piece, 0x16) + 0xc);
    *ebx = extend16(port_u16(port, piece, 0xe) + 0xc);
    join_call(port, &eax, &edx, 0x4ad510, piece, 0, *ebx, *ecx, piece, edi, ebp);
    join_call(port, &eax, &edx, 0x4826c0, 0x598d30, 0x168, *ebx, *ecx, piece, edi, ebp);
    port_set16(port, piece, 0x24, eax);
    port_set16(port, piece, 0x28, 0xa);
    join_call(port, &eax, &edx, 0x4ac860, piece, 0xc, *ebx, *ecx, piece, edi, ebp);
    port_set16(port, piece, 0x30, 0x64);
    port_set16(port, piece, 0x32, 1);
}

/* The piece of the kind +0x15c of the old piece (0x430800) put in the board's row slot at the
 * offset, placed (0x4ac490 with +0xd0), shown (0x4ac7b0) with its frame +0xb8 (0x4ac710),
 * started (0x4ac510, 0x4ac380) with +0x44 and +0x4e 0; at the spot of the base board +0xe/+0x16
 * moved on by across/down (kept at +8/+0xa), handed 0x44ee20, sent from its middle (0x4ad510
 * with 100), turned a random 360 at the spin -10, waited 12 at the speed 0 and the fall 1. With
 * second, ebx is across at the hand. */
static void bring_in(Port *port, uint32_t board, uint32_t row, uint32_t offset, uint32_t old,
                     uint32_t base, uint32_t across, uint32_t down, int second, uint32_t *ebx,
                     uint32_t *ecx, uint32_t ebp)
{
    uint32_t eax;
    uint32_t edx;
    uint32_t fresh;
    *ecx = old;
    join_call(port, &eax, &edx, 0x430800, board,
              (uint32_t)(int32_t)(int8_t)port_u8(port, old, 0x15c), *ebx, *ecx, row, offset, ebp);
    fresh = eax;
    port_set32(port, offset + row, 0x220, fresh);
    join_call(port, &eax, &edx, 0x4ac490, fresh, port_u32(port, old, 0xd0), *ebx, *ecx, fresh,
              offset, ebp);
    join_call(port, &eax, &edx, 0x4ac7b0, fresh, 5, *ebx, *ecx, fresh, offset, ebp);
    join_call(port, &eax, &edx, 0x4ac710, fresh, port_u32(port, old, 0xb8), *ebx, *ecx, fresh,
              offset, ebp);
    join_call(port, &eax, &edx, 0x4ac510, fresh, edx, *ebx, *ecx, fresh, offset, ebp);
    join_call(port, &eax, &edx, 0x4ac380, fresh, edx, *ebx, *ecx, fresh, offset, ebp);
    port_set8(port, fresh, 0x44, 0);
    port_set8(port, fresh, 0x4e, 0);
    if (second)
    {
        *ebx = across;
    }
    port_set16(port, fresh, 0xe, port_u16(port, base, 0xe) + across);
    *ecx = low16(base, port_u16(port, base, 0x16)) + down;
    port_set16(port, fresh, 8, port_u16(port, fresh, 0xe));
    port_set16(port, fresh, 0x16, *ecx);
    port_set16(port, fresh, 0xa, port_u16(port, fresh, 0x16));
    join_call(port, &eax, &edx, 0x4ac8f0, fresh, 0x44ee20, *ebx, *ecx, fresh, offset, ebp);
    *ecx = extend16(port_u16(port, fresh, 0x16) + 0xc);
    *ebx = extend16(port_u16(port, fresh, 0xe) + 0xc);
    join_call(port, &eax, &edx, 0x4ad510, fresh, 0x64, *ebx, *ecx, fresh, offset, ebp);
    join_call(port, &eax, &edx, 0x4826c0, 0x598d30, 0x168, *ebx, *ecx, fresh, offset, ebp);
    port_set16(port, fresh, 0x24, eax);
    port_set16(port, fresh, 0x28, 0xfff6);
    join_call(port, &eax, &edx, 0x4ac860, fresh, 0xc, *ebx, *ecx, fresh, offset, ebp);
    port_set16(port, fresh, 0x30, 0);
    port_set16(port, fresh, 0x32, 1);
}

/* Original 0x432c00: the boards eax and edx joined. Every piece of both (5 rows of 13 slots at
 * +0x220) moved to its leaving slot +0x87c and blown away (blow_away); then each board takes,
 * in the same slot, a new piece like the other's leaving one, at its own spot moved on by 0x18 a
 * row and a column (bring_in). eax 13, edx 13 * 0x18. */
uint32_t vertrix_port_boards_join_432c00(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x54
    };
    Port port;
    uint8_t stack[BELOW + 8];
    uint32_t ebp = entry->esp - 4;
    uint32_t first = entry->eax;
    uint32_t second = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t row;
    uint32_t column;
    uint32_t cell;
    uint32_t piece;
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -4u, entry->ebx);
    port_set32(&port, ebp, -8u, entry->ecx);
    port_set32(&port, ebp, -0xcu, entry->esi);
    port_set32(&port, ebp, -0x10u, entry->edi);
    for (row = 0; row < 5 && !port.env.failed; row++)
    {
        for (column = 0; column < 13 && !port.env.failed; column++)
        {
            cell = first + row * 0x34 + column * 4;
            piece = port_u32(&port, cell, 0x220);
            port_set32(&port, cell, 0x220, 0);
            port_set32(&port, cell, 0x87c, piece);
            if (piece != 0)
            {
                blow_away(&port, piece, &ebx, &ecx, second + row * 0x34 + column * 4, ebp);
            }
            cell = second + row * 0x34 + column * 4;
            piece = port_u32(&port, cell, 0x220);
            port_set32(&port, cell, 0x220, 0);
            port_set32(&port, cell, 0x87c, piece);
            if (piece != 0)
            {
                blow_away(&port, piece, &ebx, &ecx, cell, ebp);
            }
            ebx = first + row * 0x34 + column * 4 + 4;
        }
    }
    for (row = 0; row < 5 && !port.env.failed; row++)
    {
        ebx = 0;
        for (column = 0; column < 13 && !port.env.failed; column++)
        {
            piece = port_u32(&port, second + row * 0x34 + column * 4, 0x87c);
            ecx = piece;
            if (piece != 0)
            {
                bring_in(&port, first, first + row * 0x34, column * 4, piece, first, row * 0x18,
                         column * 0x18, 0, &ebx, &ecx, ebp);
            }
            piece = port_u32(&port, first + row * 0x34 + column * 4, 0x87c);
            ecx = piece;
            if (piece != 0)
            {
                bring_in(&port, second, second + row * 0x34, column * 4, piece, second, row * 0x18,
                         column * 0x18, 1, &ebx, &ecx, ebp);
            }
        }
    }
    return port_return(&port, 13, 13 * 0x18);
}
