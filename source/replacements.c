#include "replacements.h"

/* The board's marked cell replacements, scatter and flying copies. */

static uint32_t call_frame(Port *port, uint32_t target, uint32_t eax, uint32_t edx, uint32_t ebx,
                           uint32_t ecx, uint32_t esi, uint32_t edi, uint32_t ebp,
                           const uint32_t *stack, unsigned count)
{
    return port_call_registers(port, target, eax, edx, ebx, ecx, esi, edi, ebp, stack, count);
}

static uint32_t sign8(uint32_t value)
{
    return (uint32_t)(int32_t)(int8_t)value;
}

static uint32_t sign16(uint32_t value)
{
    return (uint32_t)(int32_t)(int16_t)value;
}

/* The replacement shared by 0x4365c0 and 0x436440: with marked cells on the board eax (0x436030),
 * the first (0x435fe0) or a random one (0x4826c0 on 0x598d30, 0x4360b0) has its mark +0xb94 set
 * to 2 and its piece +0x220 moved to +0x87c and cleared; the old piece fades (the state 0x44d480,
 * +0x4e 100, 0x4ac7b0 with 3, +0x44 16) and a new piece of the kind edx (0x430800) takes the cell
 * with the old one's place +0xd0 (0x4ac490) and frame +0xb8 (0x4ac710), a wait of 3 (0x4ac7b0),
 * both are stepped (0x4ac510, 0x4ac380, the old one with 0x44d5f0), the new one takes the old
 * one's state (0x4ac8f0) with +0x44 0, and the cell is redrawn (0x430440). 1, or 0 with no marked
 * cell. */
static uint32_t replace_cell(PORT_SIGNATURE, int random)
{
    enum
    {
        BELOW = 0x18
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t board = entry->eax;
    uint32_t kind = entry->edx;
    uint32_t count;
    uint32_t row;
    uint32_t column;
    uint32_t cell;
    uint32_t old;
    uint32_t fresh;
    uint32_t ebx;
    uint32_t ecx;
    uint32_t eax;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    count = port_call_with(&port, 0x436030, board, kind, entry->ebx, entry->ecx, board, kind, ebp);
    if (count == 0)
    {
        return port_return(&port, 0, random ? count : vertrix_lift_edx);
    }
    if (random)
    {
        eax = port_call_with(&port, 0x4826c0, 0x598d30, count & 0xffff, entry->ebx, ebp - 0x14,
                             board, kind, ebp);
        port_call_with(&port, 0x4360b0, board, eax & 0xffff, ebp - 0x18, ebp - 0x14, board, kind,
                       ebp);
    }
    else
    {
        port_call_with(&port, 0x435fe0, board, 0, ebp - 0x18, ebp - 0x14, board, kind, ebp);
    }
    row = port_u32(&port, ebp, -0x18u);
    column = port_u32(&port, ebp, -0x14u);
    port_set8(&port, board, row * 13 + column + 0xb94, 2);
    cell = board + row * 52 + column * 4;
    old = port_u32(&port, cell, 0x220);
    port_set32(&port, cell, 0x87c, old);
    port_set32(&port, cell, 0x220, 0);
    if (random)
    {
        ebx = row * 52;
        ecx = old;
    }
    else
    {
        ebx = old;
        ecx = board + row * 52;
    }
    port_call_with(&port, 0x4ac8f0, old, 0x44d480, ebx, ecx, board, kind, ebp);
    port_set8(&port, old, 0x4e, 0x64);
    port_call_with(&port, 0x4ac7b0, old, 3, ebx, ecx, board, kind, ebp);
    port_set8(&port, old, 0x44, 0x10);
    fresh = port_call_with(&port, 0x430800, board, kind, ebx, ecx, board, kind, ebp);
    port_set32(&port, board + row * 52 + column * 4, 0x220, fresh);
    if (random)
    {
        ebx = fresh;
    }
    else
    {
        ecx = fresh;
    }
    port_call_with(&port, 0x4ac490, fresh, port_u32(&port, old, 0xd0), ebx, ecx, board, kind, ebp);
    port_call_with(&port, 0x4ac7b0, fresh, 3, ebx, ecx, board, kind, ebp);
    port_call_with(&port, 0x4ac710, fresh, port_u32(&port, old, 0xb8), ebx, ecx, board, kind, ebp);
    port_call_with(&port, 0x4ac510, fresh, vertrix_lift_edx, ebx, ecx, board, kind, ebp);
    port_call_with(&port, 0x4ac380, fresh, vertrix_lift_edx, ebx, ecx, board, kind, ebp);
    port_call_with(&port, 0x4ac510, old, vertrix_lift_edx, ebx, ecx, board, kind, ebp);
    port_call_with(&port, 0x4ac380, old, 0x44d5f0, ebx, ecx, board, kind, ebp);
    port_call_with(&port, 0x4ac8f0, fresh, vertrix_lift_edx, ebx, ecx, board, kind, ebp);
    port_set8(&port, fresh, 0x44, 0);
    port_call_with(&port, 0x430440, board, sign16(port_u16(&port, ebp, -0x18u)),
                   sign16(port_u16(&port, ebp, -0x14u)), ecx, board, kind, ebp);
    return port_return(&port, 1, vertrix_lift_edx);
}

/* Original 0x4365c0: the replacement of the first marked cell. */
uint32_t vertrix_port_board_replace_cell_4365c0(PORT_SIGNATURE)
{
    return replace_cell(calls, services, globals, entry, 0);
}

/* Original 0x436440: the replacement of a random marked cell. */
uint32_t vertrix_port_board_replace_random_cell_436440(PORT_SIGNATURE)
{
    return replace_cell(calls, services, globals, entry, 1);
}

/* Original 0x437060: every marked cell of the board eax (0x436030, 0x4360b0) has its piece +0x220
 * moved to +0x87c and cleared, fading (the state 0x44e6e0, +0x4e 100, 0x4ac7b0 with 5); a new
 * piece (0x430800) of the kind edx (6 kept, -2 a random below 5 by 0x4826c0 on 0x598d30,
 * otherwise the kind kept from before) takes the cell at the old one's place +0xd0 / 12 (+0x58,
 * 0x4ac470 with 1), waits 5 (0x4ac7b0), takes the old one's frame +0xb8 (0x4ac710) with +0x4e 0,
 * +0x93 1 and +0x44 0; both are stepped (0x4ac510, 0x4ac380, the old one with 0x44c860) and the
 * new one takes the old one's state (0x4ac8f0). 1, or 0 with no marked cell. */
uint32_t vertrix_port_board_replace_marked_scaled_437060(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x2c
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t board = entry->eax;
    uint32_t count;
    uint32_t index;
    uint32_t cell;
    uint32_t old;
    uint32_t fresh;
    uint32_t kind;
    uint32_t ecx;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, -0x18u, entry->edx);
    count = port_call_with(&port, 0x436030, board, entry->edx, entry->ebx, entry->ecx, board,
                           entry->edi, ebp);
    port_set32(&port, ebp, -0x28u, count);
    if (count == 0)
    {
        return port_return(&port, 0, vertrix_lift_edx);
    }
    ecx = ebp - 0x20;
    for (index = 0; index < count; ++index)
    {
        port_call_with(&port, 0x4360b0, board, index, ebp - 0x24, ebp - 0x20, board, index, ebp);
        ecx = ebp - 0x20;
        cell = board + port_u32(&port, ebp, -0x24u) * 0x34 + port_u32(&port, ebp, -0x20u) * 4;
        old = port_u32(&port, cell, 0x220);
        port_set32(&port, cell, 0x87c, old);
        port_set32(&port, cell, 0x220, 0);
        port_call_with(&port, 0x4ac8f0, old, 0x44e6e0, old, ecx, board, index, ebp);
        port_set8(&port, old, 0x4e, 0x64);
        port_call_with(&port, 0x4ac7b0, old, 5, old, ecx, board, index, ebp);
        kind = port_u32(&port, ebp, -0x18u);
        if (kind == 6)
        {
            port_set32(&port, ebp, -0x14u, kind);
        }
        else if (kind == 0xfffffffeu)
        {
            port_set32(&port, ebp, -0x14u,
                       port_call_with(&port, 0x4826c0, 0x598d30, 5, old, ecx, board, index, ebp) &
                           0xffff);
        }
        fresh = port_call_with(&port, 0x430800, board, port_u32(&port, ebp, -0x14u), old, ecx,
                               board, index, ebp);
        port_set32(&port, ebp, -0x1cu, 0xc);
        port_set32(&port,
                   board + port_u32(&port, ebp, -0x24u) * 0x34 + port_u32(&port, ebp, -0x20u) * 4,
                   0x220, fresh);
        ecx = fresh;
        port_set32(&port, fresh, 0x58, port_u32(&port, old, 0xd0) / 0xc);
        port_call_with(&port, 0x4ac470, fresh, 1, old, ecx, board, index, ebp);
        port_call_with(&port, 0x4ac7b0, fresh, 5, old, ecx, board, index, ebp);
        port_call_with(&port, 0x4ac710, fresh, port_u32(&port, old, 0xb8), old, ecx, board, index,
                       ebp);
        port_set8(&port, fresh, 0x4e, 0);
        port_set8(&port, fresh, 0x93, 1);
        port_set8(&port, fresh, 0x44, 0);
        port_call_with(&port, 0x4ac510, fresh, vertrix_lift_edx, old, ecx, board, index, ebp);
        port_call_with(&port, 0x4ac380, fresh, vertrix_lift_edx, old, ecx, board, index, ebp);
        port_call_with(&port, 0x4ac510, old, vertrix_lift_edx, old, ecx, board, index + 1, ebp);
        port_call_with(&port, 0x4ac380, old, 0x44c860, old, ecx, board, index + 1, ebp);
        port_call_with(&port, 0x4ac8f0, fresh, vertrix_lift_edx, count, ecx, board, index + 1, ebp);
    }
    return port_return(&port, 1, vertrix_lift_edx);
}

/* Original 0x437be0: every marked cell of the board eax (0x436030, 0x4360b0) has its piece +0x220
 * moved to +0x87c and cleared; the piece flies off from the board's centre (+0xc + 60,
 * +0x14 + 156): its angle from there to its own centre (+0xc + 12, +0x14 + 12; 0x484680) is set
 * (0x4ad510), its heading (0x484700) kept modulo 360 at +0x24, its speed +0x28 a random 3 to 10
 * (0x4826c0 on 0x598d30), and it takes the state 0x44e120 with +0x4e 100, a wait of 2
 * (0x4ac7b0), +0x93 1, +0x58 0, +0x5c 300, +0x60 1, +0x64 0, +0x68 1, +0x6c 1, and is stepped
 * (0x4ac510, 0x4ac380). 1, or 0 with no marked cell. */
uint32_t vertrix_port_board_scatter_marked_437be0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x40
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t board = entry->eax;
    uint32_t count;
    uint32_t index;
    uint32_t cell;
    uint32_t piece = entry->esi;
    uint32_t centre_y = entry->edi;
    uint32_t centre_x;
    uint32_t piece_x;
    uint32_t piece_y;
    uint32_t angle;
    uint32_t heading;
    uint32_t speed;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, -0x18u, board);
    count = port_call_with(&port, 0x436030, board, entry->edx, entry->ebx, entry->ecx, entry->esi,
                           entry->edi, ebp);
    port_set32(&port, ebp, -0x20u, count);
    if (count == 0)
    {
        return port_return(&port, 0, entry->edx);
    }
    port_set32(&port, ebp, -0x1cu, (uint32_t)((int32_t)port_u32(&port, board, 0xc) >> 16) + 0x3c);
    port_set32(&port, ebp, -0x30u, (uint32_t)((int32_t)port_u32(&port, board, 0x14) >> 16) + 0x9c);
    port_set32(&port, ebp, -0x2cu, 0);
    for (index = 0; index < count; index = port_u32(&port, ebp, -0x2cu))
    {
        port_call_with(&port, 0x4360b0, board, index, ebp - 0x38, ebp - 0x34, piece, centre_y, ebp);
        cell = board + port_u32(&port, ebp, -0x38u) * 0x34 + port_u32(&port, ebp, -0x34u) * 4;
        piece = port_u32(&port, cell, 0x220);
        port_set32(&port, cell, 0x87c, piece);
        port_set32(&port, cell, 0x220, 0);
        centre_y = sign16(port_u16(&port, ebp, -0x30u));
        piece_y = sign16((uint32_t)((int32_t)port_u32(&port, piece, 0x14) >> 16) + 0xc);
        piece_x = sign16((uint32_t)((int32_t)port_u32(&port, piece, 0xc) >> 16) + 0xc);
        port_set32(&port, ebp, -0x3cu, piece_y);
        port_set32(&port, ebp, -0x28u, piece_x);
        centre_x = sign16(port_u16(&port, ebp, -0x1cu));
        port_set32(&port, ebp, -0x24u, centre_x);
        angle = port_call_with(&port, 0x484680, centre_x, centre_y, piece_x, piece_y, piece,
                               centre_y, ebp);
        port_call_with(&port, 0x4ad510, piece, sign16(angle), centre_x, centre_y, piece, centre_y,
                       ebp);
        heading = port_call_with(&port, 0x484700, centre_x, centre_y, piece_x, piece_y, piece,
                                 centre_y, ebp);
        port_set16(&port, piece, 0x24, (heading & 0xffff) % 0x168);
        speed = port_call_with(&port, 0x4826c0, 0x598d30, 8, piece_x, 0x168, piece, centre_y, ebp);
        port_set16(&port, piece, 0x28, speed + 3);
        port_call_with(&port, 0x4ac8f0, piece, 0x44e120, piece_x, 0x168, piece, centre_y, ebp);
        port_set8(&port, piece, 0x4e, 0x64);
        port_call_with(&port, 0x4ac7b0, piece, 2, piece_x, 0x168, piece, centre_y, ebp);
        port_set8(&port, piece, 0x93, 1);
        port_set32(&port, piece, 0x58, 0);
        port_set32(&port, piece, 0x5c, 0x12c);
        port_set32(&port, piece, 0x60, 1);
        port_set32(&port, piece, 0x64, 0);
        port_set32(&port, piece, 0x68, 1);
        port_set32(&port, piece, 0x6c, 1);
        port_call_with(&port, 0x4ac510, piece, vertrix_lift_edx, piece_x, 0x168, piece, centre_y,
                       ebp);
        port_call_with(&port, 0x4ac380, piece, vertrix_lift_edx, piece_x, 0x168, piece, centre_y,
                       ebp);
        port_set32(&port, ebp, -0x2cu, port_u32(&port, ebp, -0x2cu) + 1);
        count = port_u32(&port, ebp, -0x20u);
    }
    return port_return(&port, 1, entry->edx);
}

/* The flying copy shared by 0x438ef0 and 0x439510: for the board eax's cell at the column edx and
 * row ebx with the piece ecx, a new actor (0x4ca000 of 0x15c, 0x4abd70) is made (0x4adf20 with
 * zeros) at the piece's place +0xd0 (0x4ac490) with the level's speed 0x4f7d38 of 0x532bbc
 * (0x4ac7b0), the image 0x546554 of the piece's kind +0x15c (0x4ac8d0), the clip +0x8e 3 over the
 * board (+0xa8 to +0xae: x, x + 119, y, y + 311), the piece's frame +0xb8 (0x4ac710), +0x48 -80,
 * +0x95 4, +0x93 1, +0x4e 50, and the cell's place (+0xe, +0x16 from the board's plus 24 a cell);
 * it is stepped (0x4ac510) into the state `flight` (0x4ac380, 0x4ac8f0); the piece is stepped
 * (0x4ac380) and for `second` waits the level's speed and takes the state 0x45b860 with +0x58
 * cleared, else takes the state 0x45bdd0 (0x4ac510, 0x4ac8f0) and waits 5. The new actor. */
static uint32_t flying_copy(PORT_SIGNATURE, uint32_t flight, int second)
{
    enum
    {
        BELOW = 0x28
    };
    static const uint32_t zeros[5] = {0, 0, 0, 0, 0};
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t board = entry->eax;
    uint32_t column = entry->edx;
    uint32_t row = entry->ebx;
    uint32_t piece = entry->ecx;
    uint32_t x;
    uint32_t y;
    uint32_t actor;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, -0x14u, board);
    port_set32(&port, ebp, -0x10u, column);
    port_set32(&port, ebp, -0xcu, row);
    x = (uint32_t)((int32_t)port_u32(&port, board, 0xc) >> 16);
    y = (uint32_t)((int32_t)port_u32(&port, board, 0x14) >> 16);
    port_set32(&port, ebp, -0x18u, x);
    port_set32(&port, ebp, -0x20u, x + 0x77);
    port_set32(&port, ebp, -0x1cu, y);
    port_set32(&port, ebp, -0x24u, y + 0x137);
    actor = port_call_with(&port, 0x4ca000, 0x15c, column, row, piece, entry->esi, piece, ebp);
    if (actor != 0)
    {
        actor = port_call_with(&port, 0x4abd70, actor, vertrix_lift_edx, row, piece, entry->esi,
                               piece, ebp);
    }
    call_frame(&port, 0x4adf20, actor, 0, 0, 0, actor, piece, ebp, zeros, 5);
    port_call_with(&port, 0x4ac490, actor, port_u32(&port, piece, 0xd0), 0, 0, actor, piece, ebp);
    port_call_with(&port, 0x4ac7b0, actor,
                   port_u32(&port, 0, 0x4f7d38 + port_u32(&port, 0, 0x532bbc) * 4), 0, 0, actor,
                   piece, ebp);
    port_call_with(&port, 0x4ac8d0, actor, 0x546554 + sign8(port_u8(&port, piece, 0x15c)) * 28, 0,
                   0, actor, piece, ebp);
    port_set8(&port, actor, 0x8e, 3);
    port_set16(&port, actor, 0xa8, x);
    port_set16(&port, actor, 0xaa, x + 0x77);
    port_set16(&port, actor, 0xac, y);
    port_set16(&port, actor, 0xae, y + 0x137);
    port_call_with(&port, 0x4ac710, actor, port_u32(&port, piece, 0xb8), column, 0, actor, piece,
                   ebp);
    port_set16(&port, actor, 0x48, 0xffb0);
    port_set8(&port, actor, 0x95, 4);
    port_set8(&port, actor, 0x93, 1);
    port_set8(&port, actor, 0x4e, 0x32);
    port_set16(&port, actor, 0xe, port_u16(&port, board, 0xe) + column * 0x18);
    port_set16(&port, actor, 0x16, port_u16(&port, board, 0x16) + row * 0x18);
    port_call_with(&port, 0x4ac510, actor, row * 0x18, column, row, actor, piece, ebp);
    port_call_with(&port, 0x4ac380, actor, flight, column, row, actor, piece, ebp);
    port_call_with(&port, 0x4ac8f0, actor, vertrix_lift_edx, column, row, actor, piece, ebp);
    port_call_with(&port, 0x4ac380, piece, vertrix_lift_edx, column, row, actor, piece, ebp);
    if (second)
    {
        port_call_with(&port, 0x4ac510, piece, vertrix_lift_edx, column, row, actor, piece, ebp);
        port_call_with(&port, 0x4ac7b0, piece,
                       port_u32(&port, 0, 0x4f7d38 + port_u32(&port, 0, 0x532bbc) * 4), column, row,
                       actor, piece, ebp);
        port_call_with(&port, 0x4ac8f0, piece, 0x45b860, column, row, actor, piece, ebp);
        port_set32(&port, piece, 0x58, 0);
    }
    else
    {
        port_call_with(&port, 0x4ac510, piece, 0x45bdd0, column, row, actor, piece, ebp);
        port_call_with(&port, 0x4ac8f0, piece, vertrix_lift_edx, column, row, actor, piece, ebp);
        port_call_with(&port, 0x4ac7b0, piece, 5, column, row, actor, piece, ebp);
    }
    return port_return(&port, actor, vertrix_lift_edx);
}

/* Original 0x438ef0: the flying copy in the state 0x45b710, the piece waiting for 0x45b860. */
uint32_t vertrix_port_board_flying_copy_438ef0(PORT_SIGNATURE)
{
    return flying_copy(calls, services, globals, entry, 0x45b710, 1);
}

/* Original 0x439510: the flying copy in the state 0x45bc00, the piece taking 0x45bdd0. */
uint32_t vertrix_port_board_flying_copy_439510(PORT_SIGNATURE)
{
    return flying_copy(calls, services, globals, entry, 0x45bc00, 0);
}
