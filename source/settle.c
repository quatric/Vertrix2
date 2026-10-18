#include "settle.h"

/* Piece children placement and update, board column and row shifts, piece fit checks, stone
 * placement and extra block starts. */

/* A call handing the callee esi, edi and ebp as given and `count` stack dwords. */
static uint32_t call_frame(Port *port, uint32_t target, uint32_t eax, uint32_t edx, uint32_t ebx,
                           uint32_t ecx, uint32_t esi, uint32_t edi, uint32_t ebp,
                           const uint32_t *stack, unsigned count)
{
    return port_call_registers(port, target, eax, edx, ebx, ecx, esi, edi, ebp, stack, count);
}

/* Original 0x42a800: the piece's three child pairs (+0x15c and +0x170 on, 0x18 lower each) are
 * placed at the piece (+0xe, +0x16) offset by the signed bytes +0x16c and +0x16d. */
uint32_t vertrix_port_piece_children_place_42a800(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x18
    };
    Port port;
    uint32_t local = entry->esp - BELOW;
    uint32_t piece = entry->eax;
    uint32_t esi = entry->esi;
    uint32_t ebx = 0;
    uint32_t k;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    for (k = 0; k < 3; k++, ebx += 0x18)
    {
        uint32_t slot = piece + k * 4;
        uint32_t field;
        for (field = 0x15c; field <= 0x170; field += 0x14)
        {
            uint32_t child = port_u32(&port, slot, field);
            uint32_t edi;
            if (child == 0)
            {
                continue;
            }
            esi = (esi & 0xffff0000u) | (((uint32_t)(int32_t)(int8_t)port_u8(&port, piece, 0x16c) +
                                          port_u16(&port, piece, 0xe)) &
                                         0xffff);
            port_set16(&port, child, 0xe, esi);
            esi = ((esi & 0xffff0000u) | port_u16(&port, piece, 0x16)) + ebx;
            port_set32(&port, local, 0, esi);
            edi = esi;
            esi = ((esi & 0xffff0000u) |
                   ((uint32_t)(int32_t)(int8_t)port_u8(&port, piece, 0x16d) & 0xffff)) +
                  edi;
            port_set16(&port, port_u32(&port, slot, field), 0x16, esi);
        }
    }
    return port_return(&port, piece, entry->edx);
}

/* Original 0x42ac40: on a beat of the piece's timer it restarts it and, while it is not held
 * (+0x17c), falls by its speed +0x1a times the edx 0x4ac5b0 leaves (+0x16); its children
 * (+0x15c on, seven) draw (their method +4) and take the speed -200 (+0x48) when both +0x180 and
 * +0x184 are 1, otherwise their own +0x58; then 0x42af30. */
uint32_t vertrix_port_piece_actor_update_42ac40(PORT_SIGNATURE)
{
    Port port;
    uint32_t piece = entry->eax;
    uint32_t result;
    uint32_t edx;
    uint32_t ebx = entry->ebx;
    uint32_t edi = entry->edi;
    uint32_t eax;
    port_open(&port, calls, services, globals, entry);
    port_forward(&port, entry, 0x4ac500, piece, entry->edx, entry->ebx, piece);
    result = port_forward(&port, entry, 0x4ac520, piece, vertrix_lift_edx, entry->ebx, piece);
    if (result == 1)
    {
        uint32_t time =
            port_forward(&port, entry, 0x4ac540, piece, vertrix_lift_edx, entry->ebx, piece);
        result = port_forward(&port, entry, 0x4ac5b0, piece, time, entry->ebx, piece);
        if (port_u32(&port, piece, 0x17c) == 0)
        {
            eax = ((result & 0xffff0000u) | port_u16(&port, piece, 0x1a)) * vertrix_lift_edx;
            port_set16(&port, piece, 0x16, port_u16(&port, piece, 0x16) + eax);
        }
    }
    for (edx = piece; edx != piece + 0x1c;)
    {
        uint32_t child = port_u32(&port, edx, 0x15c);
        if (child != 0)
        {
            edi = child;
            ebx = port_u32(&port, child, 0x158);
            port_call_with(&port, port_u32(&port, ebx, 4), child, edx, ebx, piece, piece + 0x1c,
                           edi, entry->ebp);
            edx = vertrix_lift_edx;
        }
        edx += 4;
    }
    for (eax = piece; eax != piece + 0x1c; eax += 4)
    {
        edx = port_u32(&port, eax, 0x15c);
        if (edx == 0)
        {
            continue;
        }
        ebx = port_u32(&port, piece, 0x180);
        if (ebx == 1 && ebx == port_u32(&port, piece, 0x184))
        {
            port_set16(&port, edx, 0x48, 0xff38);
        }
        else
        {
            ebx = (ebx & 0xffff0000u) | port_u16(&port, edx, 0x58);
            port_set16(&port, edx, 0x48, ebx);
        }
    }
    result = port_call_with(&port, 0x42af30, piece, edx, ebx, piece, piece + 0x1c, edi, entry->ebp);
    return port_return(&port, result, entry->edx);
}

/* Original 0x42f310: each column with a new top block (+0x988) has its bottom block (+0x220)
 * destroyed (its method +0 with 2) and cleared, its blocks moved down one and the new one put on
 * top (+0x250). */
uint32_t vertrix_port_board_columns_push_42f310(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x20
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t board = entry->eax;
    uint32_t column;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, -0x18u, board + 0x30);
    for (column = 0; column < 5; column++)
    {
        uint32_t esi = board + column * 4;
        if (port_u32(&port, esi, 0x988) != 0)
        {
            uint32_t base = board + column * 0x34;
            uint32_t bottom = port_u32(&port, base, 0x220);
            uint32_t cell;
            uint32_t end;
            if (bottom != 0)
            {
                uint32_t methods = port_u32(&port, bottom, 0x158);
                port_call_with(&port, port_u32(&port, methods, 0), bottom, 2, column, methods, esi,
                               board, entry->ebp);
                port_set32(&port, base, 0x220, 0);
            }
            end = port_u32(&port, ebp, -0x18u);
            port_set32(&port, ebp, -0x1cu, base);
            cell = base;
            do
            {
                uint32_t value;
                cell += 4;
                value = port_u32(&port, cell, 0x220);
                port_set32(&port, cell, 0x220, 0);
                port_set32(&port, cell, 0x21c, value);
            } while (cell != end);
            port_set32(&port, port_u32(&port, ebp, -0x1cu), 0x250, port_u32(&port, esi, 0x988));
            port_set32(&port, esi, 0x988, 0);
        }
        port_set32(&port, ebp, -0x18u, port_u32(&port, ebp, -0x18u) + 0x34);
    }
    return port_return(&port, port_u32(&port, ebp, -0x18u), entry->edx);
}

/* Original 0x42f620: each row with a new block (+0xa2c) has its first block (+0x220) destroyed
 * (its method +0 with 2) and cleared, its blocks moved one column on and the new one put last
 * (+0x2f0). */
uint32_t vertrix_port_board_rows_push_42f620(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x24
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t board = entry->eax;
    uint32_t row;
    uint32_t eax = entry->eax;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, -0x1cu, board);
    port_set32(&port, ebp, -0x20u, board);
    for (row = 0; row < 0xd; row++)
    {
        uint32_t ebx = board + row * 4;
        uint32_t end;
        uint32_t first;
        if (port_u32(&port, ebx, 0xa2c) == 0)
        {
            continue;
        }
        first = port_u32(&port, ebx, 0x220);
        if (first != 0)
        {
            uint32_t methods = port_u32(&port, first, 0x158);
            port_call_with(&port, port_u32(&port, methods, 0), first, 2, ebx, methods, row,
                           0x104 + row * 4, entry->ebp);
            port_set32(&port, ebx, 0x220, 0);
        }
        port_set32(&port, ebp, -0x18u, row * 4);
        end = port_u32(&port, ebp, -0x20u) + 0x104 + row * 4;
        eax = row * 4 + 0x34 + port_u32(&port, ebp, -0x1cu);
        do
        {
            uint32_t value;
            eax += 0x34;
            value = port_u32(&port, eax, 0x1ec);
            port_set32(&port, eax, 0x1ec, 0);
            port_set32(&port, eax, 0x1b8, value);
        } while (eax != end);
        eax = port_u32(&port, ebp, -0x1cu) + port_u32(&port, ebp, -0x18u);
        first = port_u32(&port, eax, 0xa2c);
        port_set32(&port, eax, 0xa2c, 0);
        port_set32(&port, eax, 0x2f0, first);
    }
    return port_return(&port, eax, entry->edx);
}

/* The piece fit checks 0x4311c0 and 0x431280: the cells the piece (+0xa60) spans (0x431ae0 at its
 * top and 0x47 lower) in the column `step` beside it are all free (+0x220), or out of the rows;
 * 0 when that column is off the board. */
static uint32_t piece_side_free(PORT_SIGNATURE, int step)
{
    enum
    {
        BELOW = 0x30
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t board = entry->eax;
    uint32_t piece;
    uint32_t x;
    uint32_t y;
    uint32_t pushed[1];
    uint32_t column;
    uint32_t free = 1;
    int32_t row;
    int32_t last;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    piece = port_u32(&port, board, 0xa60);
    x = (uint32_t)(int32_t)(int16_t)port_u16(&port, piece, 0xe);
    y = (uint32_t)(int32_t)(int16_t)port_u16(&port, piece, 0x16);
    port_set32(&port, ebp, -0x18u, y);
    pushed[0] = ebp - 0x28;
    call_frame(&port, 0x431ae0, board, x, y, ebp - 0x2c, entry->esi, board, ebp, pushed, 1);
    port_set32(&port, ebp, -0x1cu, x);
    port_set32(&port, ebp, -0x18u, y + 0x47);
    pushed[0] = ebp - 0x20;
    call_frame(&port, 0x431ae0, board, x, y + 0x47, ebp - 0x24, 1, board, ebp, pushed, 1);
    column = port_u32(&port, ebp, -0x2cu) + (uint32_t)step;
    port_set32(&port, ebp, -0x2cu, column);
    if (step < 0 ? (int32_t)column < 0 : (int32_t)column >= 5)
    {
        return port_return(&port, 0, entry->edx);
    }
    row = (int32_t)port_u32(&port, ebp, -0x28u);
    last = (int32_t)port_u32(&port, ebp, -0x20u);
    for (; row <= last; row++)
    {
        if (row >= 0 && port_u32(&port, board + column * 0x34 + (uint32_t)row * 4, 0x220) != 0)
        {
            free = 0;
        }
    }
    return port_return(&port, free, entry->edx);
}

/* Original 0x4311c0: the column to the left. */
uint32_t vertrix_port_board_piece_left_free_4311c0(PORT_SIGNATURE)
{
    return piece_side_free(calls, services, globals, entry, -1);
}

/* Original 0x431280: the column to the right. */
uint32_t vertrix_port_board_piece_right_free_431280(PORT_SIGNATURE)
{
    return piece_side_free(calls, services, globals, entry, 1);
}

/* Original 0x4316c0: unless 0x42ec00 leaves an edx below ebx, nothing (0); otherwise the board's
 * kinds are taken (0x4327e0), the five new top kinds (+0x980) are 5 and each column takes a new
 * top block (0x430800 with its kind, +0x988) in the state 0x44f700 with the speed 4 (0x4ac7b0).
 * 1. */
uint32_t vertrix_port_board_place_stones_4316c0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x14
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t board = entry->eax;
    uint32_t ebx = entry->ebx;
    uint32_t column;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_forward(&port, entry, 0x42ec00, board, entry->edx, entry->ebx, entry->ecx);
    if ((int32_t)vertrix_lift_edx >= (int32_t)entry->ebx)
    {
        return port_return(&port, 0, vertrix_lift_edx);
    }
    port_call_with(&port, 0x4327e0, board + 0x220, board + 0x1de, 0x41, entry->ecx, 0, board,
                   entry->ebp);
    ebx = 0x41;
    for (column = 1; column <= 5; column++)
    {
        port_set8(&port, board + column, 0x97f, 5);
    }
    port_set32(&port, ebp, -0x10u, board + 0x14);
    for (column = 0; column < 5; column++)
    {
        uint32_t ecx = board + column * 4;
        uint32_t esi = board + column;
        if (port_u8(&port, esi, 0x980) == 0xff)
        {
            port_set32(&port, ecx, 0x988, 0);
            continue;
        }
        ebx = port_call_with(&port, 0x430800, board,
                             (uint32_t)(int32_t)(int8_t)port_u8(&port, esi, 0x980), ebx, ecx, esi,
                             board, entry->ebp);
        port_set32(&port, ecx, 0x988, ebx);
        port_call_with(&port, 0x4ac8f0, ebx, 0x44f700, ebx, ecx, esi, board, entry->ebp);
        port_call_with(&port, 0x4ac7b0, ebx, 4, ebx, ecx, esi, board, entry->ebp);
    }
    return port_return(&port, 1, port_u32(&port, ebp, -0x10u));
}

/* Original 0x4323d0: every cell holding an extra block (+0x324, 16 bytes a cell, 0xd0 a column)
 * starts its four slots: the speed 1 (0x4ac7b0), +0x15d 1 and the state 0x450630. 1 when any did,
 * otherwise 0. */
uint32_t vertrix_port_board_extras_start_4323d0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x28
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t board = entry->eax;
    uint32_t base;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, -0x20u, board);
    port_set32(&port, ebp, -0x1cu, 0);
    port_set32(&port, ebp, -0x24u, board + 0x410);
    do
    {
        uint32_t row;
        base = port_u32(&port, ebp, -0x20u);
        port_set32(&port, ebp, -0x18u, base);
        for (row = 0; row < 0xd; row++)
        {
            uint32_t ebx;
            uint32_t ecx;
            uint32_t edi = base + row * 0x10;
            if (port_u32(&port, edi, 0x324) == 0)
            {
                continue;
            }
            ebx = row * 0x10 + port_u32(&port, ebp, -0x18u);
            port_set32(&port, ebp, -0x1cu, 1);
            ecx = ebx;
            ebx += 0x10;
            do
            {
                uint32_t block = port_u32(&port, ecx, 0x324);
                port_call_with(&port, 0x4ac7b0, block, 1, ebx, ecx, row, edi, entry->ebp);
                port_set8(&port, port_u32(&port, ecx, 0x324), 0x15d, 1);
                block = port_u32(&port, ecx, 0x324);
                ecx += 4;
                port_call_with(&port, 0x4ac8f0, block, 0x450630, ebx, ecx, row, edi, entry->ebp);
            } while (ecx != ebx);
        }
        port_set32(&port, ebp, -0x20u, port_u32(&port, ebp, -0x20u) + 0xd0);
    } while (port_u32(&port, ebp, -0x20u) != port_u32(&port, ebp, -0x24u));
    return port_return(&port, port_u32(&port, ebp, -0x1cu), entry->edx);
}

/* Original 0x4330d0: whether the cells the board's piece (+0xa60) spans (0x431ae0 at its top and
 * 0x47 lower) hit a block (+0x220) of the grid edx. edx the row it stopped at. */
uint32_t vertrix_port_board_piece_hits_grid_4330d0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x30
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t board = entry->eax;
    uint32_t piece;
    uint32_t x;
    uint32_t y;
    uint32_t pushed[1];
    uint32_t cells;
    int32_t row;
    int32_t last;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, -0x18u, entry->edx);
    piece = port_u32(&port, board, 0xa60);
    x = (uint32_t)(int32_t)(int16_t)port_u16(&port, piece, 0xe);
    port_set32(&port, ebp, -0x14u, 0);
    y = (uint32_t)(int32_t)(int16_t)port_u16(&port, piece, 0x16);
    port_set32(&port, ebp, -0x1cu, x);
    pushed[0] = ebp - 0x28;
    call_frame(&port, 0x431ae0, board, x, y, ebp - 0x2c, y, board, ebp, pushed, 1);
    pushed[0] = ebp - 0x20;
    call_frame(&port, 0x431ae0, board, port_u32(&port, ebp, -0x1cu), y + 0x47, ebp - 0x24, y, board,
               ebp, pushed, 1);
    row = (int32_t)port_u32(&port, ebp, -0x28u);
    last = (int32_t)port_u32(&port, ebp, -0x20u);
    if (row > last)
    {
        return port_return(&port, port_u32(&port, ebp, -0x14u), (uint32_t)row);
    }
    cells = port_u32(&port, ebp, -0x18u) + port_u32(&port, ebp, -0x2cu) * 0x34;
    for (; row <= last; row++)
    {
        if (row >= 0 && port_u32(&port, cells + (uint32_t)row * 4, 0x220) != 0)
        {
            return port_return(&port, 1, (uint32_t)row);
        }
    }
    return port_return(&port, port_u32(&port, ebp, -0x14u), (uint32_t)row);
}
