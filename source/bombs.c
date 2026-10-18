#include "bombs.h"

/* The board's turn of a piece into a bomb. */

static uint32_t call_frame(Port *port, uint32_t target, uint32_t eax, uint32_t edx, uint32_t ebx,
                           uint32_t ecx, uint32_t esi, uint32_t edi, uint32_t ebp,
                           const uint32_t *stack, unsigned count)
{
    return port_call_registers(port, target, eax, edx, ebx, ecx, esi, edi, ebp, stack, count);
}

/* Original 0x439690: the piece of the board eax at the row dx and column bx becomes a bomb: a
 * glow (0x15c bytes, 0x4ca000, 0x4abd70; 0x4adf20 with five zeros) takes its step (+0xd0,
 * 0x4ac490), the level 0x532bbc's speed 0x4f7d38 (0x4ac7b0), the image 0x5465e0 (0x4ac8d0), the
 * board's box (+0xc to 0x77 past, +0x14 to 0x137 past; +0x8e 3) and its frame (+0xb8, 0x4ac710),
 * rises (+0x48 -0x50, +0x95 4, +0x93 1, +0x4e 0x32) from the cell (0x18 a column and row past
 * the board's +0xe and +0x16; 0x4ac510, 0x4ac380 of 0x45bc80, 0x4ac8f0) as the piece is held
 * (0x4ac380, 0x4ac510); the piece leaves (+0x87c, the state 0x44d480, +0x4e 0x64, speed 5,
 * +0x44 0x10) and a bomb (kind 5, 0x430800) takes its cell, step, speed 5 and frame, both held
 * (0x4ac510, 0x4ac380, the piece's state 0x44d5f0) and the bomb's +0x44 cleared. The glow. */
uint32_t vertrix_port_board_cell_bomb_439690(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x2c
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t board = entry->eax;
    uint32_t zeros[5] = {0, 0, 0, 0, 0};
    uint32_t row;
    uint32_t column;
    uint32_t place;
    uint32_t piece;
    uint32_t glow;
    uint32_t bomb;
    uint32_t left;
    uint32_t top;
    uint32_t level;
    uint32_t across;
    uint32_t down;
    uint32_t slot;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, -4u, entry->ecx);
    port_set32(&port, ebp, -8u, entry->esi);
    port_set32(&port, ebp, -0xcu, entry->edi);
    port_set16(&port, ebp, -0x14u, entry->edx);
    port_set16(&port, ebp, -0x10u, entry->ebx);
    row = (uint32_t)(int32_t)(int16_t)entry->edx;
    column = (uint32_t)(int32_t)(int16_t)entry->ebx;
    place = board + row * 0x34;
    piece = port_u32(&port, place + column * 4, 0x220);
    port_set32(&port, ebp, -0x18u, piece);
    left = (uint32_t)((int32_t)port_u32(&port, board, 0xc) >> 16);
    top = (uint32_t)((int32_t)port_u32(&port, board, 0x14) >> 16);
    port_set32(&port, ebp, -0x1cu, left);
    port_set32(&port, ebp, -0x28u, left + 0x77);
    port_set32(&port, ebp, -0x20u, top);
    port_set32(&port, ebp, -0x24u, top + 0x137);
    glow = port_call_with(&port, 0x4ca000, 0x15c, entry->edx, entry->ebx, place, entry->esi, board,
                          ebp);
    if (glow != 0)
    {
        glow = port_call_with(&port, 0x4abd70, glow, vertrix_lift_edx, entry->ebx, place,
                              entry->esi, board, ebp);
    }
    call_frame(&port, 0x4adf20, glow, 0, 0, 0, glow, board, ebp, zeros, 5);
    port_call_with(&port, 0x4ac490, glow, port_u32(&port, piece, 0xd0), 0, 0, glow, board, ebp);
    level = port_u32(&port, 0, 0x532bbc);
    port_call_with(&port, 0x4ac7b0, glow, port_u32(&port, 0, level * 4 + 0x4f7d38), 0, 0, glow,
                   board, ebp);
    port_call_with(&port, 0x4ac8d0, glow, 0x5465e0, 0, 0, glow, board, ebp);
    port_set8(&port, glow, 0x8e, 3);
    port_set16(&port, glow, 0xa8, left);
    port_set16(&port, glow, 0xaa, left + 0x77);
    port_set16(&port, glow, 0xac, top);
    port_set16(&port, glow, 0xae, top + 0x137);
    across = port_u32(&port, ebp, -0x14u);
    port_call_with(&port, 0x4ac710, glow, port_u32(&port, piece, 0xb8), across, 0, glow, board,
                   ebp);
    port_set16(&port, glow, 0x48, 0xffb0);
    port_set8(&port, glow, 0x95, 4);
    port_set8(&port, glow, 0x93, 1);
    port_set8(&port, glow, 0x4e, 0x32);
    down = port_u32(&port, ebp, -0x10u);
    port_set16(&port, glow, 0xe, port_u16(&port, board, 0xe) + across * 0x18);
    port_set16(&port, glow, 0x16, port_u16(&port, board, 0x16) + down * 0x18);
    port_call_with(&port, 0x4ac510, glow, down * 0x18, across, down, glow, board, ebp);
    port_call_with(&port, 0x4ac380, glow, 0x45bc80, across, down, glow, board, ebp);
    port_call_with(&port, 0x4ac8f0, glow, vertrix_lift_edx, across, down, glow, board, ebp);
    port_call_with(&port, 0x4ac380, piece, vertrix_lift_edx, across, down, glow, board, ebp);
    port_call_with(&port, 0x4ac510, piece, vertrix_lift_edx, across, down, glow, board, ebp);
    slot = place + column * 4;
    piece = port_u32(&port, slot, 0x220);
    port_set32(&port, slot, 0x220, 0);
    port_set32(&port, slot, 0x87c, piece);
    port_call_with(&port, 0x4ac8f0, piece, 0x44d480, piece, slot, glow, board, ebp);
    port_set8(&port, piece, 0x4e, 0x64);
    port_call_with(&port, 0x4ac7b0, piece, 5, piece, slot, glow, board, ebp);
    port_set8(&port, piece, 0x44, 0x10);
    bomb = port_call_with(&port, 0x430800, board, 5, piece, slot, glow, board, ebp);
    port_set32(&port, slot, 0x220, bomb);
    port_call_with(&port, 0x4ac490, bomb, port_u32(&port, piece, 0xd0), piece, bomb, glow, board,
                   ebp);
    port_call_with(&port, 0x4ac7b0, bomb, 5, piece, bomb, glow, board, ebp);
    port_call_with(&port, 0x4ac710, bomb, port_u32(&port, piece, 0xb8), piece, bomb, glow, board,
                   ebp);
    port_call_with(&port, 0x4ac510, bomb, vertrix_lift_edx, piece, bomb, glow, board, ebp);
    port_call_with(&port, 0x4ac380, bomb, vertrix_lift_edx, piece, bomb, glow, board, ebp);
    port_call_with(&port, 0x4ac510, piece, vertrix_lift_edx, piece, bomb, glow, board, ebp);
    port_call_with(&port, 0x4ac380, piece, 0x44d5f0, piece, bomb, glow, board, ebp);
    port_call_with(&port, 0x4ac8f0, bomb, vertrix_lift_edx, piece, bomb, glow, board, ebp);
    port_set8(&port, bomb, 0x44, 0);
    return port_return(&port, glow, vertrix_lift_edx);
}
