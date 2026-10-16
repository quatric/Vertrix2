#include "port_rtlswaps.h"

/* Marked board cells swapped. */

/* One new piece of 0x436150 for the slot `slot`, made (0x430800, with ecx as left) of the kind
 * of `kind_of` to replace `old` (the second piece is then carried in esi, ecx its row `row`):
 * placed in the slot, given the old piece's frame +0xd0 (0x4ac490), shown (0x4ac7b0 with 5), given
 * its +0xb8 (0x4ac710), both started (0x4ac510, 0x4ac380), and stepped (0x4ac8f0) by 0x44c860 when
 * both kinds share their group at 0x53bcc8, else by 0x44d330. */
static uint32_t swap_piece(Port *port, uint32_t board, uint32_t slot, uint32_t old,
                           uint32_t kind_of, uint32_t ebx, uint32_t ecx, uint32_t row, uint32_t edi,
                           uint32_t ebp, int new_in_esi)
{
    uint32_t piece;
    uint32_t esi = board;
    uint32_t mine;
    uint32_t theirs;
    piece = port_call_with(port, 0x430800, board,
                           (uint32_t)(int32_t)(int8_t)port_u8(port, kind_of, 0x15c), ebx, ecx, esi,
                           edi, ebp);
    port_set32(port, slot, 0x220, piece);
    if (new_in_esi)
    {
        ecx = row;
        esi = piece;
    }
    else
    {
        ecx = piece;
    }
#define CALL(target, a, d) port_call_with(port, target, a, d, ebx, ecx, esi, edi, ebp)
    CALL(0x4ac490, piece, port_u32(port, old, 0xd0));
    CALL(0x4ac7b0, piece, 5);
    CALL(0x4ac710, piece, port_u32(port, old, 0xb8));
    CALL(0x4ac510, piece, vertrix_lift_edx);
    CALL(0x4ac380, piece, vertrix_lift_edx);
    CALL(0x4ac510, old, vertrix_lift_edx);
    CALL(0x4ac380, old, vertrix_lift_edx);
    mine = (uint32_t)(int32_t)(int8_t)port_u8(port, old, 0x15c);
    theirs = (uint32_t)(int32_t)(int8_t)port_u8(port, piece, 0x15c);
    if (new_in_esi)
    {
        ecx = theirs;
    }
    CALL(0x4ac8f0, piece,
         port_u8(port, mine, 0x53bcc8) == port_u8(port, theirs, 0x53bcc8) ? 0x44c860 : 0x44d330);
#undef CALL
    return piece;
}

/* Original 0x436150: with at least two marked cells on the board eax (0x436030), two of them
 * picked at random (0x4826c0 of 0x598d30, 0x4360b0 to place each) and marked 2 at +0xb94; each
 * one's piece moved to its waiting slot (+0x87c), stepped by 0x44d1e0 (0x4ac8f0) with +0x4e 100
 * and shown (0x4ac7b0 with 5); then each slot given a new piece of the other one's kind
 * (swap_piece). eax 1, or 0 with fewer than two; edx kept. */
uint32_t vertrix_port_board_swap_marked_436150(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x30
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t board = entry->eax;
    uint32_t count;
    uint32_t pick;
    uint32_t first_slot;
    uint32_t second_slot;
    uint32_t first;
    uint32_t second;
    uint32_t piece;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -4u, entry->ebx);
    port_set32(&port, ebp, -8u, entry->ecx);
    port_set32(&port, ebp, -0xcu, entry->edx);
    port_set32(&port, ebp, -0x10u, entry->esi);
    port_set32(&port, ebp, -0x14u, entry->edi);
    count = port_call_with(&port, 0x436030, board, entry->edx, entry->ebx, entry->ecx, entry->esi,
                           entry->edi, ebp);
    if (count < 2)
    {
        return port_return(&port, 0, entry->edx);
    }
    pick = port_call_with(&port, 0x4826c0, 0x598d30, count & 0xffff, entry->ebx, ebp - 0x28, board,
                          count, ebp);
    port_call_with(&port, 0x4360b0, board, pick & 0xffff, ebp - 0x2c, ebp - 0x28, board, count,
                   ebp);
    port_set8(&port, board + port_u32(&port, ebp, -0x2cu) * 0xd + port_u32(&port, ebp, -0x28u),
              0xb94, 2);
    pick = port_call_with(&port, 0x4826c0, 0x598d30, (count - 1) & 0xffff, ebp - 0x2c, ebp - 0x20,
                          board, count - 1, ebp);
    port_call_with(&port, 0x4360b0, board, pick & 0xffff, ebp - 0x24, ebp - 0x20, board, count - 1,
                   ebp);
    port_set8(&port, board + port_u32(&port, ebp, -0x24u) * 0xd + port_u32(&port, ebp, -0x20u),
              0xb94, 2);
    first_slot = board + port_u32(&port, ebp, -0x2cu) * 0x34 + port_u32(&port, ebp, -0x28u) * 4;
    first = port_u32(&port, first_slot, 0x220);
    port_set32(&port, first_slot, 0x87c, first);
    port_set32(&port, first_slot, 0x220, 0);
    second_slot = board + port_u32(&port, ebp, -0x24u) * 0x34 + port_u32(&port, ebp, -0x20u) * 4;
    second = port_u32(&port, second_slot, 0x220);
    port_set32(&port, second_slot, 0x87c, second);
    port_set32(&port, second_slot, 0x220, 0);
#define CALL(target, a, d)                                                                         \
    port_call_with(&port, target, a, d, first, board + port_u32(&port, ebp, -0x24u) * 0x34, board, \
                   second, ebp)
    CALL(0x4ac8f0, first, 0x44d1e0);
    port_set8(&port, first, 0x4e, 0x64);
    CALL(0x4ac7b0, first, 5);
    CALL(0x4ac8f0, second, 0x44d1e0);
    port_set8(&port, second, 0x4e, 0x64);
    CALL(0x4ac7b0, second, 5);
#undef CALL
    piece = swap_piece(&port, board, first_slot, first, second, first,
                       board + port_u32(&port, ebp, -0x24u) * 0x34, 0, second, ebp, 0);
    port_set32(&port, ebp, -0x1cu, (uint32_t)(int32_t)(int8_t)port_u8(&port, first, 0x15c));
    port_set32(&port, ebp, -0x18u, (uint32_t)(int32_t)(int8_t)port_u8(&port, piece, 0x15c));
    swap_piece(&port, board, second_slot, second, first, first, piece,
               board + port_u32(&port, ebp, -0x24u) * 0x34, second, ebp, 1);
    return port_return(&port, 1, entry->edx);
}
