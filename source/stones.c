#include "stones.h"

/* The piece's bottom side test, the bonus marker, the piece lock into the board, the kind six
 * search, the stone maker, the slide start, the effect assignment, the marked cell clear and the
 * piece frames. */

static uint32_t call_frame(Port *port, uint32_t target, uint32_t eax, uint32_t edx, uint32_t ebx,
                           uint32_t ecx, uint32_t esi, uint32_t edi, uint32_t ebp,
                           const uint32_t *stack, unsigned count)
{
    return port_call_registers(port, target, eax, edx, ebx, ecx, esi, edi, ebp, stack, count);
}

static uint32_t sign16(uint32_t value)
{
    return (uint32_t)(int32_t)(int16_t)value;
}

static const uint32_t zeros[5] = {0, 0, 0, 0, 0};

/* Original 0x42f120: as 0x42f030 for the row below the piece: a side cell of the edge table
 * 0x4f9ad8 that is filled (+0x220, or any at row 4) gives 1, otherwise 0. */
uint32_t vertrix_port_board_piece_touches_side_42f120(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x2c
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t board = entry->eax;
    uint32_t piece;
    uint32_t x;
    uint32_t y;
    uint32_t edx;
    uint32_t ecx;
    uint32_t eax;
    uint32_t stack[1];
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, -0x10u, entry->edx);
    port_set32(&port, ebp, -0x14u, entry->ebx);
    piece = port_u32(&port, board, 0xa60);
    x = sign16(port_u16(&port, piece, 0xe));
    y = sign16(port_u16(&port, piece, 0x16));
    port_set32(&port, ebp, -0x18u, x);
    stack[0] = ebp - 0x24;
    call_frame(&port, 0x431ae0, board, x, y, ebp - 0x28, board, y, ebp, stack, 1);
    stack[0] = ebp - 0x1c;
    call_frame(&port, 0x431ae0, board, x, y + 0x47, ebp - 0x20, board, y, ebp, stack, 1);
    edx = port_u32(&port, ebp, -0x24u);
    if ((int32_t)edx > (int32_t)port_u32(&port, ebp, -0x1cu))
    {
        return port_return(&port, 0, edx);
    }
    ecx = edx + (port_u32(&port, ebp, -0x14u) + port_u32(&port, ebp, -0x10u)) * 0xd;
    eax = board + (port_u32(&port, ebp, -0x28u) + 1) * 0x34 + edx * 4;
    do
    {
        if ((int32_t)edx >= 0)
        {
            uint32_t side = port_u8(&port, ecx, 0x4f9ad8);
            int32_t row = (int32_t)port_u32(&port, ebp, -0x28u);
            if (((row < 4 && port_u32(&port, eax, 0x220) != 0) || row == 4) && side != 0)
            {
                return port_return(&port, 1, edx);
            }
        }
        ecx++;
        edx++;
        eax += 4;
    } while ((int32_t)edx <= (int32_t)port_u32(&port, ebp, -0x1cu));
    return port_return(&port, 0, edx);
}

/* Original 0x430850: the bonus marker (0x160 bytes, 0x4ca000 and 0x42bb00) over the piece eax:
 * placed by 0x4adf20, mode 2 (0x4ac470, 0x4ac7b0), the image 0x544b84, its box (+0x8e 3) from the
 * piece's x and y to 0x77 and 0x137 past them, kind 6, the frame edx (0x4ac710), +0x95 1 and the
 * height -50. */
uint32_t vertrix_port_bonus_marker_create_430850(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x24
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t frame = entry->edx;
    uint32_t x;
    uint32_t y;
    uint32_t marker;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    x = sign16(port_u16(&port, entry->eax, 0xe));
    y = sign16(port_u16(&port, entry->eax, 0x16));
    port_set32(&port, ebp, -0x14u, x);
    port_set32(&port, ebp, -0x18u, y);
    port_set32(&port, ebp, -0x1cu, y + 0x137);
    port_set32(&port, ebp, -0x20u, x + 0x77);
    marker =
        port_call_with(&port, 0x4ca000, 0x160, frame, entry->ebx, entry->ecx, x + 0x77, frame, ebp);
    if (marker != 0)
    {
        marker = port_call_with(&port, 0x42bb00, marker, vertrix_lift_edx, entry->ebx, entry->ecx,
                                x + 0x77, frame, ebp);
    }
    call_frame(&port, 0x4adf20, marker, 0, 0, 0, marker, frame, ebp, zeros, 5);
    port_call_with(&port, 0x4ac470, marker, 2, 0, 0, marker, frame, ebp);
    port_call_with(&port, 0x4ac7b0, marker, 2, 0, 0, marker, frame, ebp);
    port_call_with(&port, 0x4ac8d0, marker, 0x544b84, 0, 0, marker, frame, ebp);
    port_set8(&port, marker, 0x8e, 3);
    port_set16(&port, marker, 0xa8, port_u32(&port, ebp, -0x14u));
    port_set16(&port, marker, 0xaa, port_u32(&port, ebp, -0x20u));
    port_set16(&port, marker, 0xac, port_u32(&port, ebp, -0x18u));
    port_set16(&port, marker, 0xae, port_u32(&port, ebp, -0x1cu));
    port_set8(&port, marker, 0x15c, 6);
    port_call_with(&port, 0x4ac710, marker, frame, 0, 0, marker, frame, ebp);
    port_set8(&port, marker, 0x95, 1);
    port_set16(&port, marker, 0x4a, 0xffce);
    return port_return(&port, marker, vertrix_lift_edx);
}

/* Original 0x431c60: the board's piece (+0xa60) locks in: 0x431ae0 gives its row and top column
 * into the frame; each of its three blocks (+0x15c) inside the board (columns 0 to 12) takes its
 * cell (+0x220, shown, +0x4e 50, +0x48 0), others are destroyed (method +0 with 2); the piece is
 * destroyed and cleared. 1, or 0 when the piece is wholly above the board. */
uint32_t vertrix_port_board_piece_lock_431c60(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x24
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t board = entry->eax;
    uint32_t piece;
    uint32_t ebx;
    uint32_t ecx = 0;
    uint32_t edi = entry->edi;
    uint32_t stack[1];
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    piece = port_u32(&port, board, 0xa60);
    port_set32(&port, ebp, -0x18u, 1);
    ebx = sign16(port_u16(&port, piece, 0x16));
    stack[0] = ebp - 0x1c;
    call_frame(&port, 0x431ae0, board, sign16(port_u16(&port, piece, 0xe)), ebx, ebp - 0x20, board,
               edi, ebp, stack, 1);
    if ((int32_t)(port_u32(&port, ebp, -0x1cu) + 3) <= 0)
    {
        port_set32(&port, ebp, -0x18u, 0);
    }
    else
    {
        for (ebx = 0; ebx < 3; ebx++)
        {
            uint32_t column = port_u32(&port, ebp, -0x1cu) + ebx;
            ecx = ebx * 4;
            if ((int32_t)column >= 0 && (int32_t)column < 0xd)
            {
                uint32_t block;
                edi = port_u32(&port, ebp, -0x20u) * 0x34 + board;
                block = port_u32(&port, port_u32(&port, board, 0xa60) + ecx, 0x15c);
                port_set32(&port, column * 4 + edi, 0x220, block);
                port_set8(&port, block, 0x93, 0);
                port_set8(&port, block, 0x4e, 0x32);
                port_set16(&port, block, 0x48, 0);
            }
            else
            {
                uint32_t block = port_u32(&port, port_u32(&port, board, 0xa60) + ecx, 0x15c);
                if (block != 0)
                {
                    edi = port_u32(&port, block, 0x158);
                    port_call_with(&port, port_u32(&port, edi, 0), block, 2, ebx, ecx, board, edi,
                                   ebp);
                }
            }
            ecx += 4;
            port_set32(&port, port_u32(&port, board, 0xa60) + ecx, 0x158, 0);
        }
    }
    piece = port_u32(&port, board, 0xa60);
    if (piece != 0)
    {
        uint32_t methods = port_u32(&port, piece, 0x158);
        port_call_with(&port, port_u32(&port, methods, 0), piece, 2, ebx, methods, board, edi, ebp);
    }
    port_set32(&port, board, 0xa60, 0);
    return port_return(&port, port_u32(&port, ebp, -0x18u), entry->edx);
}

/* Original 0x4322f0: whether any of the board's blocks (+0x220, 5 rows of 13) is of kind 6. */
uint32_t vertrix_port_board_has_kind_six_4322f0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x1c
    };
    Port port;
    uint32_t board = entry->eax;
    uint32_t local = entry->esp - 0x1c;
    uint32_t row;
    uint32_t column;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    for (row = 0; row < 5; row++)
    {
        port_set32(&port, local, 0, row * 0x34);
        for (column = 0; column < 0xd; column++)
        {
            uint32_t block = port_u32(&port, board + row * 0x34 + column * 4, 0x220);
            if (block != 0 && port_u8(&port, block, 0x15c) == 6)
            {
                return port_return(&port, 1, entry->edx);
            }
        }
    }
    port_set32(&port, local, 0, 5 * 0x34);
    return port_return(&port, 0, entry->edx);
}

/* Original 0x433750: the board cell (row dl, column bl, signed) turns to stone: an unpinned
 * (+0x87c) block not of kind 5 is pinned (+0x87c) and fades (state 0x44cb50, +0x4e 100, mode 5,
 * +0x95 3, 0x4ac510, 0x4ac380 with 5) while a stone (0x430800) takes the cell with the block's
 * speed +0xd0 (0x4ac490), mode 5, its frame +0xb8, +0x95 3, height 200, 0x4ac510, 0x4ac380 with
 * 0x44cab0 and 0x4ac8f0. 1, otherwise 0. */
uint32_t vertrix_port_board_make_stone_433750(PORT_SIGNATURE)
{
    Port port;
    uint32_t board = entry->eax;
    uint32_t cell;
    uint32_t block;
    uint32_t stone;
    uint32_t pinned;
    port_open(&port, calls, services, globals, entry);
    cell = board + (uint32_t)(int32_t)(int8_t)entry->edx * 0x34 +
           (uint32_t)(int32_t)(int8_t)entry->ebx * 4;
    pinned = port_u32(&port, cell, 0x87c);
    if (pinned != 0)
    {
        return port_return(&port, 0, pinned);
    }
    block = port_u32(&port, cell, 0x220);
    if (block == 0 || port_u8(&port, block, 0x15c) == 5)
    {
        return port_return(&port, 0, 0);
    }
    port_set32(&port, cell, 0x220, 0);
    port_set32(&port, cell, 0x87c, block);
    port_forward_esi(&port, entry, 0x4ac8f0, block, 0x44cb50, cell, block, board);
    port_set8(&port, block, 0x4e, 0x64);
    port_forward_esi(&port, entry, 0x4ac7b0, block, 5, cell, block, board);
    port_set8(&port, block, 0x95, 3);
    port_forward_esi(&port, entry, 0x4ac510, block, vertrix_lift_edx, cell, block, board);
    port_forward_esi(&port, entry, 0x4ac380, block, 5, cell, block, board);
    stone = port_forward_esi(&port, entry, 0x430800, board, vertrix_lift_edx, cell, block, board);
    port_set32(&port, cell, 0x220, stone);
    port_forward_esi(&port, entry, 0x4ac490, stone, port_u32(&port, block, 0xd0), stone, block,
                     board);
    port_forward_esi(&port, entry, 0x4ac7b0, stone, 5, stone, block, board);
    port_forward_esi(&port, entry, 0x4ac710, stone, port_u32(&port, block, 0xb8), stone, block,
                     board);
    port_set8(&port, stone, 0x95, 3);
    port_set16(&port, stone, 0x48, 0xc8);
    port_forward_esi(&port, entry, 0x4ac510, stone, vertrix_lift_edx, stone, block, board);
    port_forward_esi(&port, entry, 0x4ac380, stone, 0x44cab0, stone, block, board);
    port_forward_esi(&port, entry, 0x4ac8f0, stone, vertrix_lift_edx, stone, block, board);
    return port_return(&port, 1, vertrix_lift_edx);
}

/* Original 0x438470: the actor edx slides from where it is (+8, +0xa) to the actor eax's place
 * plus (ebx, ecx) cells of 24 (+0x10, +0x18): down (state 0x44e920, +0x44 16, +0x45 12, +0x46 1,
 * height -20) or up (0x44ebe0, +0x58 0, +0x5c 4, +0x60 1, shown, +0x4e 50, +0x95 4), mode 4,
 * 0x4ac510 and speeds 4; level, nothing. */
uint32_t vertrix_port_actor_start_slide_438470(PORT_SIGNATURE)
{
    Port port;
    uint32_t actor = entry->edx;
    uint32_t edx;
    uint32_t eax;
    uint32_t ebx;
    uint32_t ecx = entry->ecx * 0x18;
    uint32_t below;
    uint32_t here;
    port_open(&port, calls, services, globals, entry);
    ebx = entry->ebx * 0x18;
    edx = ((actor & 0xffff0000u) | port_u16(&port, entry->eax, 0xe)) + ebx;
    eax = ((entry->eax & 0xffff0000u) | port_u16(&port, entry->eax, 0x16)) + ecx;
    port_set16(&port, actor, 0x10, edx);
    port_set16(&port, actor, 0x18, eax);
    port_set16(&port, actor, 8, port_u16(&port, actor, 0xe));
    here = port_u16(&port, actor, 0x16);
    port_set16(&port, actor, 0xa, here);
    ebx = (ebx & 0xffff0000u) | here;
    edx = (edx & 0xffff0000u) | here;
    below = (int16_t)eax > (int16_t)here;
    if ((int16_t)eax == (int16_t)here)
    {
        return port_return(&port, eax, edx);
    }
    if (below)
    {
        port_forward_esi(&port, entry, 0x4ac8f0, actor, 0x44e920, ebx, ecx, actor);
        port_set8(&port, actor, 0x44, 0x10);
        port_set8(&port, actor, 0x45, 0xc);
        port_set16(&port, actor, 0x46, 1);
        port_set16(&port, actor, 0x48, 0xffec);
    }
    else
    {
        port_forward_esi(&port, entry, 0x4ac8f0, actor, 0x44ebe0, ebx, ecx, actor);
        port_set32(&port, actor, 0x58, 0);
        port_set32(&port, actor, 0x5c, 4);
        port_set32(&port, actor, 0x60, 1);
        port_set8(&port, actor, 0x93, 1);
        port_set8(&port, actor, 0x4e, 0x32);
        port_set8(&port, actor, 0x95, 4);
    }
    port_forward_esi(&port, entry, 0x4ac7b0, actor, 4, ebx, ecx, actor);
    eax = port_forward_esi(&port, entry, 0x4ac510, actor, vertrix_lift_edx, ebx, ecx, actor);
    port_set16(&port, actor, 0x12, 4);
    port_set16(&port, actor, 0x1a, 4);
    return port_return(&port, eax, vertrix_lift_edx);
}

/* Original 0x438b90: every block of the board (+0x220, by columns) takes the effect dl's state:
 * 0 0x44f1e0 and 1 0x44f320 (both +0x4c 10), 2 0x44f430 (+0x88 10), 3 0x44f560, 4 0x44f690. */
uint32_t vertrix_port_board_assign_effect_438b90(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x24
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t board = entry->eax;
    uint32_t effect = entry->edx & 0xff;
    uint32_t ebx = (entry->ebx & 0xffffff00u) | effect;
    uint32_t eax = entry->eax;
    uint32_t column;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, -0x20u, board);
    port_set32(&port, ebp, -0x18u, board);
    port_set32(&port, ebp, -0x14u, 0);
    port_set32(&port, ebp, -0x1cu, 0x104);
    for (column = 0; column < 0xd; column++)
    {
        uint32_t esi = board + column * 4;
        uint32_t edi = board + port_u32(&port, ebp, -0x1cu);
        eax = port_u32(&port, ebp, -0x1cu);
        do
        {
            uint32_t block = port_u32(&port, esi, 0x220);
            if (block != 0)
            {
                uint32_t state = 0;
                switch (effect)
                {
                    case 0:
                        state = 0x44f1e0;
                        break;
                    case 1:
                        state = 0x44f320;
                        break;
                    case 2:
                        state = 0x44f430;
                        break;
                    case 3:
                        state = 0x44f560;
                        break;
                    case 4:
                        state = 0x44f690;
                        break;
                    default:
                        break;
                }
                if (state != 0)
                {
                    eax = port_call_with(&port, 0x4ac8f0, block, state, ebx, block, esi, edi, ebp);
                    if (effect <= 1)
                    {
                        port_set16(&port, block, 0x4c, 0xa);
                    }
                    else if (effect == 2)
                    {
                        port_set32(&port, block, 0x88, 0xa);
                    }
                }
            }
            esi += 0x34;
        } while (esi != edi);
        port_set32(&port, ebp, -0x1cu, port_u32(&port, ebp, -0x1cu) + 4);
        port_set32(&port, ebp, -0x14u, column + 1);
    }
    return port_return(&port, eax, port_u32(&port, ebp, -0x1cu));
}

/* Original 0x439190: every board cell marked 2 (+0xb94) has its block (+0x220) and burst
 * (+0xbdc) destroyed (method +0 with 2) and cleared. 1. */
uint32_t vertrix_port_board_destroy_marked_439190(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x30
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t board = entry->eax;
    uint32_t edi = entry->edi;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, -0x28u, board);
    port_set32(&port, ebp, -0x20u, board);
    port_set32(&port, ebp, -0x24u, board + 0x34);
    port_set32(&port, ebp, -0x2cu, board + 0x104);
    do
    {
        uint32_t cell = port_u32(&port, ebp, -0x20u);
        uint32_t esi = port_u32(&port, ebp, -0x28u);
        port_set32(&port, ebp, -0x18u, cell);
        port_set32(&port, ebp, -0x1cu, port_u32(&port, ebp, -0x24u));
        do
        {
            if (port_u8(&port, esi, 0xb94) == 2)
            {
                uint32_t item = port_u32(&port, port_u32(&port, ebp, -0x18u), 0x220);
                if (item != 0)
                {
                    edi = port_u32(&port, item, 0x158);
                    port_call_with(&port, port_u32(&port, edi, 0), item, 2, cell, cell, esi, edi,
                                   ebp);
                }
                item = port_u32(&port, cell, 0xbdc);
                port_set32(&port, cell, 0x220, 0);
                if (item != 0)
                {
                    edi = port_u32(&port, item, 0x158);
                    port_call_with(&port, port_u32(&port, edi, 0), item, 2, cell, cell, esi, edi,
                                   ebp);
                }
                port_set32(&port, cell, 0xbdc, 0);
            }
            edi = port_u32(&port, ebp, -0x1cu);
            esi++;
            cell += 4;
            port_set32(&port, ebp, -0x18u, port_u32(&port, ebp, -0x18u) + 4);
        } while (cell != edi);
        port_set32(&port, ebp, -0x24u, port_u32(&port, ebp, -0x24u) + 0x34);
        port_set32(&port, ebp, -0x28u, port_u32(&port, ebp, -0x28u) + 0xd);
        port_set32(&port, ebp, -0x20u, port_u32(&port, ebp, -0x20u) + 0x34);
    } while (port_u32(&port, ebp, -0x20u) != port_u32(&port, ebp, -0x2cu));
    return port_return(&port, 1, entry->edx);
}

/* Original 0x43a310: the piece eax's three frames (0x160 bytes each, 0x4ca000 and 0x42bb00, into
 * +0x15c): placed by 0x4adf20 at (dx, cx + i * the second stack word), boxes (+0x8e 3) dx wide by
 * the first stack word less 1, bx tall, colour the third stack byte (+0x44), mode 1 and speed 150
 * (0x4ac490). */
uint32_t vertrix_port_piece_frames_build_43a310(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x30
    };
    Port port;
    uint8_t stack[BELOW + 8 + 0xc];
    uint32_t ebp = entry->esp - 4;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi = entry->esi;
    uint32_t edi;
    uint32_t pointer = 0;
    port_open_arguments(&port, stack, calls, services, globals, entry, BELOW, 3);
    port_set16(&port, ebp, -0x14u, entry->edx);
    port_set16(&port, ebp, -0xcu, entry->ebx);
    port_set16(&port, ebp, -0x10u, entry->ecx);
    port_set32(&port, ebp, -0x18u, entry->eax);
    for (edi = 0; edi < 3; edi++)
    {
        uint32_t frame;
        uint32_t x0;
        uint32_t x1;
        uint32_t y0;
        uint32_t y1;
        frame = port_call_with(&port, 0x4ca000, 0x160, edx, ebx, ecx, esi, edi, ebp);
        if (frame != 0)
        {
            frame =
                port_call_with(&port, 0x42bb00, frame, vertrix_lift_edx, ebx, ecx, esi, edi, ebp);
        }
        esi = frame;
        x0 = sign16(port_u16(&port, ebp, -0x14u));
        port_set32(&port, ebp, -0x28u, x0);
        x1 = sign16(port_u16(&port, ebp, -0x10u)) + x0 - 1;
        port_set32(&port, ebp, -0x24u, x1);
        y0 = sign16(port_u16(&port, ebp, -0xcu)) + sign16(port_u16(&port, ebp, 0xc)) * edi;
        port_set32(&port, ebp, -0x20u, y0);
        y1 = sign16(port_u16(&port, ebp, 8)) + y0 - 1;
        port_set32(&port, ebp, -0x1cu, y1);
        ebx = sign16(port_u16(&port, ebp, -0x20u));
        ecx = 0;
        call_frame(&port, 0x4adf20, frame, sign16(port_u16(&port, ebp, -0x28u)), ebx, 0, frame, edi,
                   ebp, zeros, 5);
        port_set16(&port, frame, 0xa8, port_u32(&port, ebp, -0x28u));
        port_set16(&port, frame, 0xaa, port_u32(&port, ebp, -0x24u));
        port_set16(&port, frame, 0xac, port_u32(&port, ebp, -0x20u));
        port_set16(&port, frame, 0xae, port_u32(&port, ebp, -0x1cu));
        port_set8(&port, frame, 0x44, port_u8(&port, ebp, 0x10));
        port_set8(&port, frame, 0x8e, 3);
        port_call_with(&port, 0x4ac7b0, frame, 1, ebx, 0, frame, edi, ebp);
        port_call_with(&port, 0x4ac490, frame, 0x96, ebx, 0, frame, edi, ebp);
        edx = vertrix_lift_edx;
        pointer = port_u32(&port, ebp, -0x18u);
        ebx = pointer + 4;
        port_set32(&port, pointer, 0x15c, frame);
        port_set32(&port, ebp, -0x18u, ebx);
    }
    return port_return(&port, pointer, edx);
}
