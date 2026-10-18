#include "rows.h"

/* Board cell scans, falling cell marks, column checks and player progress helpers. */

/* A call handing the callee esi, edi and ebp as given and `count` stack dwords. */
static uint32_t call_frame(Port *port, uint32_t target, uint32_t eax, uint32_t edx, uint32_t ebx,
                           uint32_t ecx, uint32_t esi, uint32_t edi, uint32_t ebp,
                           const uint32_t *stack, unsigned count)
{
    return port_call_registers(port, target, eax, edx, ebx, ecx, esi, edi, ebp, stack, count);
}

/* Original 0x42efa0: whether the shape edx in the turn ebx fits the column of the piece (+0xa60,
 * signed words +0xe and +0x16, and 0x47 lower) by 0x431ae0 and the table 0x4f9800 (30 bytes a
 * shape, 5 a turn); edx the column found. */
uint32_t vertrix_port_board_piece_shape_fits_42efa0(PORT_SIGNATURE)
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
    uint32_t pushed[1];
    uint32_t column;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, -0x10u, entry->edx);
    port_set32(&port, ebp, -0x14u, entry->ebx);
    piece = port_u32(&port, board, 0xa60);
    x = (uint32_t)(int32_t)(int16_t)port_u16(&port, piece, 0xe);
    y = (uint32_t)(int32_t)(int16_t)port_u16(&port, piece, 0x16);
    port_set32(&port, ebp, -0x18u, x);
    pushed[0] = ebp - 0x24;
    call_frame(&port, 0x431ae0, board, x, y, ebp - 0x28, board, y, ebp, pushed, 1);
    pushed[0] = ebp - 0x1c;
    call_frame(&port, 0x431ae0, board, port_u32(&port, ebp, -0x18u), y + 0x47, ebp - 0x20, board, y,
               ebp, pushed, 1);
    column = port_u32(&port, ebp, -0x28u);
    return port_return(
        &port,
        port_u8(&port,
                port_u32(&port, ebp, -0x10u) * 0x1e + port_u32(&port, ebp, -0x14u) * 5 + column,
                0x4f9800) != 0,
        column);
}

/* Original 0x42f580: for the 13 rows of each column holding a new block (+0x9e8): its old block
 * (+0x2f0, when set) destroyed by its method +0 with 2 and cleared, the four cells above moved
 * down one (+0x254 to +0x288 of each), and the new block moved to +0x220. */
uint32_t vertrix_port_board_settle_new_blocks_42f580(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x1c
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t board = entry->eax;
    uint32_t offset;
    uint32_t eax = entry->eax;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    for (offset = 0; offset != 0x34; offset += 4)
    {
        uint32_t row = board + offset;
        uint32_t old;
        uint32_t k;
        uint32_t moved;
        if (port_u32(&port, row, 0x9e8) == 0)
        {
            continue;
        }
        old = port_u32(&port, row, 0x2f0);
        if (old != 0)
        {
            uint32_t methods = port_u32(&port, old, 0x158);
            call_frame(&port, port_u32(&port, methods, 0), old, 2, row, methods, offset, board, ebp,
                       NULL, 0);
            port_set32(&port, row, 0x2f0, 0);
        }
        port_set32(&port, ebp, -0x18u, offset);
        eax = offset + 0x9c + board;
        for (k = 0; k < 4; k++)
        {
            uint32_t value;
            eax -= 0x34;
            value = port_u32(&port, eax, 0x254);
            port_set32(&port, eax, 0x254, 0);
            port_set32(&port, eax, 0x288, value);
        }
        eax = port_u32(&port, ebp, -0x18u);
        moved = port_u32(&port, board + eax, 0x9e8);
        port_set32(&port, board + eax, 0x9e8, 0);
        port_set32(&port, board + eax, 0x220, moved);
    }
    return port_return(&port, eax, entry->edx);
}

/* Original 0x431b80: 1 when the piece (+0xa60) is still above the board's top (+0x16 and 0x48
 * against the board's +0x16, unsigned) or the cell 0x431ae0 finds below it is free; otherwise 0. */
uint32_t vertrix_port_board_piece_can_fall_431b80(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x20
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t board = entry->eax;
    uint32_t piece;
    uint32_t y;
    uint32_t x;
    uint32_t pushed[1];
    int32_t row;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    piece = port_u32(&port, board, 0xa60);
    y = (uint32_t)(int32_t)(int16_t)port_u16(&port, piece, 0x16) + 0x48;
    x = (uint32_t)(int32_t)(int16_t)port_u16(&port, piece, 0xe);
    if (y < (uint32_t)(int32_t)(int16_t)port_u16(&port, board, 0x16))
    {
        return port_return(&port, 1, entry->edx);
    }
    pushed[0] = ebp - 0x18;
    call_frame(&port, 0x431ae0, board, x, y, ebp - 0x1c, board, 1, ebp, pushed, 1);
    row = (int32_t)port_u32(&port, ebp, -0x18u);
    if (row >= 0xd ||
        port_u32(&port, board + port_u32(&port, ebp, -0x1cu) * 0x34 + (uint32_t)row * 4, 0x220) !=
            0)
    {
        return port_return(&port, 0, entry->edx);
    }
    return port_return(&port, 1, entry->edx);
}

/* Original 0x4328e0: the cells of the 5 columns of eax (13 bytes each, -1 empty) resting on a gap
 * marked 1 in the dwords of edx (cleared first by 0x432840; the edx it leaves): from the lowest
 * empty cell up. 1 when any is marked. */
uint32_t vertrix_port_board_mark_floating_4328e0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x1c
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t marks;
    uint32_t end;
    uint32_t any = 0;
    uint32_t edx;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    call_frame(&port, 0x432840, entry->edx, entry->edx, entry->ebx, entry->eax, entry->esi,
               entry->edi, ebp, NULL, 0);
    port_set32(&port, ebp, -0x18u, entry->eax);
    marks = vertrix_lift_edx;
    end = marks + 0x104;
    port_set32(&port, ebp, -0x14u, end);
    do
    {
        uint32_t cells = port_u32(&port, ebp, -0x18u);
        int32_t index = 0xc;
        if (port_u8(&port, cells, 0xc) != 0xff)
        {
            do
            {
                index--;
            } while (index >= 0 && port_u8(&port, cells, (uint32_t)index) != 0xff);
        }
        for (; index >= 0; index--)
        {
            if (port_u8(&port, cells, (uint32_t)index) != 0xff)
            {
                any = 1;
                port_set32(&port, marks + (uint32_t)index * 4, 0, 1);
            }
        }
        edx = port_u32(&port, ebp, -0x18u) + 0xd;
        marks += 0x34;
        port_set32(&port, ebp, -0x18u, edx);
    } while (marks != port_u32(&port, ebp, -0x14u));
    return port_return(&port, any, edx);
}

/* Original 0x432b10: the board's kinds (0x4327e0, 65 cells at +0x1de); when 0x4328e0 marks
 * floating cells in the frame, each marked cell's +0x19d (13 a column) takes the byte +0x58. */
uint32_t vertrix_port_board_mark_falling_cells_432b10(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x124
    };
    Port port;
    uint8_t stack[BELOW + 8];
    uint32_t ebp = entry->esp - 4;
    uint32_t board = entry->eax;
    uint32_t cells = board + 0x1de;
    uint32_t column;
    uint32_t eax;
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    call_frame(&port, 0x4327e0, board + 0x220, cells, 0x41, cells, board, entry->edi, ebp, NULL, 0);
    eax = call_frame(&port, 0x4328e0, cells, ebp - 0x120, 0x41, cells, board, entry->edi, ebp, NULL,
                     0);
    if (eax == 0)
    {
        return port_return(&port, 0, entry->edx);
    }
    port_set32(&port, ebp, -0x18u, board);
    port_set32(&port, ebp, -0x1cu, 0x34);
    for (column = 0; column < 5; column++)
    {
        uint32_t edx = port_u32(&port, ebp, -0x18u);
        uint32_t end = port_u32(&port, ebp, -0x1cu);
        for (eax = column * 0x34; eax != end; eax += 4, edx++)
        {
            if (port_u32(&port, ebp - 0x120 + eax, 0) == 1)
            {
                port_set8(&port, edx, 0x19d, port_u8(&port, board, 0x58));
            }
        }
        eax = end + 0x34;
        port_set32(&port, ebp, -0x1cu, eax);
        port_set32(&port, ebp, -0x18u, port_u32(&port, ebp, -0x18u) + 0xd);
    }
    return port_return(&port, eax, entry->edx);
}

/* Original 0x433040: for each cell of the boards eax and edx, 0x430660 bursts the cell on the
 * other board's column and row (the signed row and column words) where this board holds a block
 * (+0x220): eax's cell when edx holds one there, edx's when eax does. */
uint32_t vertrix_port_board_burst_occupied_433040(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x28
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t eax = entry->eax;
    uint32_t edx;
    uint32_t column;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, -0x1cu, entry->eax);
    port_set32(&port, ebp, -0x18u, entry->edx);
    port_set32(&port, ebp, -0x14u, 0);
    port_set32(&port, ebp, -0x24u, entry->eax);
    port_set32(&port, ebp, -0x20u, entry->edx);
    for (column = 0; column < 5;)
    {
        uint32_t esi = port_u32(&port, ebp, -0x20u);
        uint32_t edi = port_u32(&port, ebp, -0x24u);
        uint32_t row;
        for (row = 0; row < 0xd; row++, esi += 4, edi += 4)
        {
            uint32_t ebx = (uint32_t)(int32_t)(int16_t)row;
            if (port_u32(&port, esi, 0x220) != 0)
            {
                eax = call_frame(&port, 0x430660, port_u32(&port, ebp, -0x1cu),
                                 (uint32_t)(int32_t)(int16_t)port_u16(&port, ebp, -0x14u), ebx, row,
                                 esi, edi, ebp, NULL, 0);
            }
            if (port_u32(&port, edi, 0x220) != 0)
            {
                eax = call_frame(&port, 0x430660, port_u32(&port, ebp, -0x18u),
                                 (uint32_t)(int32_t)(int16_t)port_u16(&port, ebp, -0x14u), ebx, row,
                                 esi, edi, ebp, NULL, 0);
            }
        }
        edx = port_u32(&port, ebp, -0x20u) + 0x34;
        port_set32(&port, ebp, -0x20u, edx);
        port_set32(&port, ebp, -0x24u, port_u32(&port, ebp, -0x24u) + 0x34);
        column = port_u32(&port, ebp, -0x14u) + 1;
        port_set32(&port, ebp, -0x14u, column);
    }
    return port_return(&port, eax, edx);
}

/* Original 0x4334b0: 1 when any of the 5 x 13 x 4 extra slots (+0x324, 0xd0 a column, 0x10 a row)
 * holds a block of type 1 (+0x15d), otherwise 0. */
uint32_t vertrix_port_board_has_type_one_extra_4334b0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x28
    };
    Port port;
    uint32_t local = entry->esp - BELOW;
    uint32_t board = entry->eax;
    uint32_t column;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, local, 8, 0);
    port_set32(&port, local, 4, 0);
    for (column = 0; column < 5; column++)
    {
        uint32_t row;
        port_set32(&port, local, 0, 0);
        port_set32(&port, local, 0xc, 0);
        for (row = 0; row < 0xd; row++)
        {
            uint32_t slot;
            for (slot = 0; slot < 4; slot++)
            {
                uint32_t block = port_u32(&port,
                                          board + port_u32(&port, local, 4) +
                                              port_u32(&port, local, 0xc) + slot * 4,
                                          0x324);
                if (block != 0 && port_u8(&port, block, 0x15d) == 1)
                {
                    return port_return(&port, 1, entry->edx);
                }
            }
            port_set32(&port, local, 0xc, port_u32(&port, local, 0xc) + 0x10);
            port_set32(&port, local, 0, row + 1);
        }
        port_set32(&port, local, 4, port_u32(&port, local, 4) + 0xd0);
        port_set32(&port, local, 8, column + 1);
    }
    return port_return(&port, 0, entry->edx);
}

/* The checker marks of 0x436850 and 0x4372c0: the board's kinds (0x4327e0 with 1 in ecx), then
 * the marks +0xb94 of the 65 cells alternate (from 1, across the columns) between a filled cell
 * (not -1, nor 5 for `not_five`) marked 1 and 0. */
static uint32_t board_checker_marks(PORT_SIGNATURE, int not_five)
{
    enum
    {
        BELOW = 0x24
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t board = entry->eax;
    uint32_t phase = 1;
    uint32_t index = 0;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, -0x1cu, board);
    call_frame(&port, 0x4327e0, board + 0x220, board + 0x1de, 0x41, 1, board + 0x41, entry->edi,
               ebp, NULL, 0);
    port_set32(&port, ebp, -0x20u, board + 0x41);
    do
    {
        uint32_t base = port_u32(&port, ebp, -0x1cu);
        port_set32(&port, ebp, -0x18u, base);
        for (index = 0; index < 0xd; index++)
        {
            uint32_t cell = port_u32(&port, ebp, -0x18u) + index;
            uint32_t kind = port_u8(&port, cell, 0x1de);
            port_set8(&port, cell, 0xb94,
                      phase == 1 && kind != 0xff && (!not_five || kind != 5) ? 1 : 0);
            phase = 1 - phase;
        }
        port_set32(&port, ebp, -0x1cu, base + 0xd);
    } while (port_u32(&port, ebp, -0x1cu) != port_u32(&port, ebp, -0x20u));
    return port_return(&port, index, entry->edx);
}

/* Original 0x436850: fives left unmarked. */
uint32_t vertrix_port_board_checker_marks_436850(PORT_SIGNATURE)
{
    return board_checker_marks(calls, services, globals, entry, 1);
}

/* Original 0x4372c0: any filled cell. */
uint32_t vertrix_port_board_checker_marks_4372c0(PORT_SIGNATURE)
{
    return board_checker_marks(calls, services, globals, entry, 0);
}

/* Original 0x436a10: the marks +0xb94 of the board's cells (0x4327e0) set to whether their kind
 * (signed) is edx, then the count of 0x436030 stored at ebx (the edx it leaves). */
uint32_t vertrix_port_board_mark_kind_count_436a10(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x20
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t board = entry->eax;
    uint32_t kind = entry->edx;
    uint32_t ecx = entry->ecx;
    uint32_t ebx = 0;
    uint32_t row;
    uint32_t result;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, -0x18u, board);
    port_set32(&port, ebp, -0x10u, entry->ebx);
    call_frame(&port, 0x4327e0, board + 0x220, board + 0x1de, 0x41, entry->ecx, kind, 0, ebp, NULL,
               0);
    port_set32(&port, ebp, -0x14u, 0x41);
    port_set32(&port, ebp, -0x1cu, board);
    for (row = 0; row < 0xd; row++)
    {
        uint32_t eax = port_u32(&port, ebp, -0x18u) + row;
        ebx = port_u32(&port, ebp, -0x1cu) + port_u32(&port, ebp, -0x14u);
        do
        {
            uint32_t cell = port_u8(&port, eax, 0x1de);
            uint32_t mark = 0;
            if (cell != 0xff)
            {
                ecx = (uint32_t)(int32_t)(int8_t)cell;
                mark = ecx == kind;
            }
            eax += 0xd;
            port_set8(&port, eax, 0xb87, mark);
        } while (eax != ebx);
        ebx = port_u32(&port, ebp, -0x14u) + 1;
        port_set32(&port, ebp, -0x14u, ebx);
    }
    result = call_frame(&port, 0x436030, port_u32(&port, ebp, -0x18u), port_u32(&port, ebp, -0x10u),
                        ebx, ecx, kind, 0xd, ebp, NULL, 0);
    port_set32(&port, vertrix_lift_edx, 0, result);
    return port_return(&port, result, vertrix_lift_edx);
}

/* Original 0x436aa0: the marks +0xb94 of the board's cells (0x4327e0) for the kind edx: empty
 * cells and fives 0, sixes 1 for kind 5, others 1 for kinds 5 and 6. edx the last mark in dl
 * with its cell in dh. */
uint32_t vertrix_port_board_mark_kind_match_436aa0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x20
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t board = entry->eax;
    uint32_t kind = entry->edx;
    uint32_t eax = 0;
    uint32_t edx = 0;
    uint32_t row;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, -0x1cu, board);
    call_frame(&port, 0x4327e0, board + 0x220, board + 0x1de, 0x41, kind, entry->esi, 0, ebp, NULL,
               0);
    port_set32(&port, ebp, -0x18u, 0x41);
    port_set32(&port, ebp, -0x14u, board);
    for (row = 0; row < 0xd; row++)
    {
        uint32_t end = port_u32(&port, ebp, -0x14u) + port_u32(&port, ebp, -0x18u);
        eax = port_u32(&port, ebp, -0x1cu) + row;
        do
        {
            uint32_t cell = port_u8(&port, eax, 0x1de);
            uint32_t mark = 0;
            if (cell == 6)
            {
                mark = kind == 5;
            }
            else if (cell != 0xff && cell != 5)
            {
                mark = kind == 5 || kind == 6;
            }
            edx = (cell << 8) | mark;
            eax += 0xd;
            port_set8(&port, eax, 0xb87, mark);
        } while (eax != end);
        port_set32(&port, ebp, -0x18u, port_u32(&port, ebp, -0x18u) + 1);
    }
    return port_return(&port, eax, edx);
}

/* Original 0x4371b0: for each of the 0x436030 marked cells (0x4360b0 gives its column and row
 * into the frame): mark 2, its companion (+0x87c) the handler 0x44e790 and its block (+0x220)
 * 0x44e800. 1 when there were any, otherwise 0. */
uint32_t vertrix_port_board_start_marked_4371b0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x20
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t board = entry->eax;
    uint32_t count;
    uint32_t done = 0;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    count = call_frame(&port, 0x436030, board, entry->edx, entry->ebx, entry->ecx, board,
                       entry->edi, ebp, NULL, 0);
    port_set32(&port, ebp, -0x14u, count);
    if (count == 0)
    {
        return port_return(&port, 0, vertrix_lift_edx);
    }
    do
    {
        uint32_t column;
        uint32_t row;
        call_frame(&port, 0x4360b0, board, 0, ebp - 0x1c, ebp - 0x18, board, done, ebp, NULL, 0);
        column = port_u32(&port, ebp, -0x1cu);
        row = port_u32(&port, ebp, -0x18u);
        port_set8(&port, column * 0xd + board + row, 0xb94, 2);
        call_frame(&port, 0x4ac8f0, port_u32(&port, column * 0x34 + board + row * 4, 0x87c),
                   0x44e790, ebp - 0x1c, row, board, done, ebp, NULL, 0);
        column = port_u32(&port, ebp, -0x1cu);
        row = port_u32(&port, ebp, -0x18u);
        done++;
        call_frame(&port, 0x4ac8f0, port_u32(&port, column * 0x34 + board + row * 4, 0x220),
                   0x44e800, ebp - 0x1c, port_u32(&port, ebp, -0x14u), board, done, ebp, NULL, 0);
    } while (done < port_u32(&port, ebp, -0x14u));
    return port_return(&port, 1, vertrix_lift_edx);
}

/* Original 0x43b720: the player's progress +0x178 grows by edx (not below 0); at the goal
 * (0x532b34, with goals on 0x532bc8) +0x464 1 and it stops there: on the screen (the owner's
 * +0x4c5) 0x43bb00 with 0, 0x4715a0 on +0, 0x43c0e0 with 0x4f81b4, +0x474 1 and 0x43ac00,
 * otherwise 0x532a3c 1. 1 after 0x4726d0 when it changed, otherwise 0. */
uint32_t vertrix_port_player_progress_update_43b720(PORT_SIGNATURE)
{
    Port port;
    uint32_t player = entry->eax;
    uint32_t before;
    uint32_t value;
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t edi = entry->edi;
    port_open(&port, calls, services, globals, entry);
    before = port_u32(&port, player, 0x178);
    value = before + entry->edx;
    if ((int32_t)value < 0)
    {
        value = 0;
    }
    else
    {
        edx = port_u32(&port, 0, 0x532bc8);
        if (edx == 1 && value >= port_u32(&port, 0, 0x532b34))
        {
            uint32_t owner;
            edi = port_u32(&port, 0, 0x532b34);
            port_set32(&port, player, 0x464, edx);
            owner = port_u32(&port, player, 0x3b0);
            eax = (owner & 0xffffff00u) | port_u8(&port, owner, 0x4c5);
            value = edi;
            if ((eax & 0xff) == 0)
            {
                port_set32(&port, 0, 0x532a3c, edx);
            }
            else
            {
                call_frame(&port, 0x43bb00, player, 0, value, player, before, edi, entry->ebp, NULL,
                           0);
                call_frame(&port, 0x4715a0, port_u32(&port, player, 0), vertrix_lift_edx, value,
                           player, before, edi, entry->ebp, NULL, 0);
                call_frame(&port, 0x43c0e0, player, port_u32(&port, 0, 0x4f81b4), value, player,
                           before, edi, entry->ebp, NULL, 0);
                port_set32(&port, player, 0x474, 1);
                eax = call_frame(&port, 0x43ac00, player, vertrix_lift_edx, value, player, before,
                                 edi, entry->ebp, NULL, 0);
                edx = vertrix_lift_edx;
            }
        }
    }
    port_set32(&port, player, 0x178, value);
    if (before == value)
    {
        return port_return(&port, 0, edx);
    }
    call_frame(&port, 0x4726d0, eax, edx, value, player, before, edi, entry->ebp, NULL, 0);
    return port_return(&port, 1, vertrix_lift_edx);
}

/* Original 0x43b8a0: without a timer (+0x4e8) just 0x4ae150; with one, after it steps (0x4ac500,
 * 0x4ac520): done, 0x43b860 with 0 and 0x43b980; otherwise 0x43b860 with its share (+0xbc times
 * 0x4f89ac over +0xc0); then 0x4ae150. */
uint32_t vertrix_port_player_timer_update_43b8a0(PORT_SIGNATURE)
{
    Port port;
    uint32_t player = entry->eax;
    uint32_t timer;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    timer = port_u32(&port, player, 0x4e8);
    if (timer == 0)
    {
        result = port_forward(&port, entry, 0x4ae150, player, 0, entry->ebx, player);
        return port_return(&port, result, entry->edx);
    }
    port_forward(&port, entry, 0x4ac500, timer, timer, entry->ebx, player);
    if (port_forward(&port, entry, 0x4ac520, port_u32(&port, player, 0x4e8), vertrix_lift_edx,
                     entry->ebx, player) == 1)
    {
        port_forward(&port, entry, 0x43b860, player, 0, entry->ebx, player);
        port_forward(&port, entry, 0x43b980, player, vertrix_lift_edx, entry->ebx, player);
        result = port_forward(&port, entry, 0x4ae150, player, vertrix_lift_edx, entry->ebx, player);
    }
    else
    {
        LiftFlags flags = {0, 0, 0, 0, 0, 0};
        uint32_t scale = port_u32(&port, 0, 0x4f89ac);
        uint32_t whole;
        uint32_t share;
        uint32_t remainder = 0;
        timer = port_u32(&port, player, 0x4e8);
        share = port_u32(&port, timer, 0xbc) * scale;
        whole = port_u32(&port, timer, 0xc0);
        lift_div1(32, whole, &share, &remainder, &flags);
        port_call_with(&port, 0x43b860, player, share, timer, player, scale, whole, entry->ebp);
        result = port_call_with(&port, 0x4ae150, player, vertrix_lift_edx, timer, player, scale,
                                whole, entry->ebp);
    }
    return port_return(&port, result, entry->edx);
}

/* Original 0x43bb60: the player's event pushed by 0x482060 (on +0x19c) with its signed bytes
 * +0x4c4, +0x4c5 and +0x4cc, +0x4c8, +0x194, +0x198, the signed byte +0x4cd, +0x154, and the
 * board's (+0x15c) +0xb80, +0xc0, signed words +0x12 and +0x1a, +0xb84 and +0xb88. */
uint32_t vertrix_port_player_push_event_43bb60(PORT_SIGNATURE)
{
    Port port;
    uint32_t player = entry->eax;
    uint32_t board;
    uint32_t arguments[11];
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    board = port_u32(&port, player, 0x15c);
    arguments[0] = (uint32_t)(int32_t)(int8_t)port_u8(&port, player, 0x4cc);
    arguments[1] = port_u32(&port, player, 0x194);
    arguments[2] = port_u32(&port, player, 0x198);
    arguments[3] = (uint32_t)(int32_t)(int8_t)port_u8(&port, player, 0x4cd);
    arguments[4] = port_u32(&port, player, 0x154);
    arguments[5] = port_u32(&port, board, 0xb80);
    arguments[6] = port_u32(&port, board, 0xc0);
    arguments[7] = (uint32_t)(int32_t)(int16_t)port_u16(&port, board, 0x12);
    arguments[8] = (uint32_t)(int32_t)(int16_t)port_u16(&port, board, 0x1a);
    arguments[9] = port_u32(&port, board, 0xb84);
    arguments[10] = port_u32(&port, board, 0xb88);
    result = call_frame(
        &port, 0x482060, player + 0x19c, (uint32_t)(int32_t)(int8_t)port_u8(&port, player, 0x4c4),
        (uint32_t)(int32_t)(int8_t)port_u8(&port, player, 0x4c5), port_u32(&port, player, 0x4c8),
        arguments[6], arguments[5], entry->ebp, arguments, 11);
    return port_return(&port, result, entry->edx);
}
