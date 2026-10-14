#include "port_marks.h"

/* Board marking, column, piece cycle and saved block helpers. */

/* A call handing the callee esi, edi and ebp as given, and `count` stack arguments (the nearest
 * to the stack pointer first). */
static uint32_t call_registers(Port *port, uint32_t target, uint32_t eax, uint32_t edx,
                               uint32_t ebx, uint32_t ecx, uint32_t esi, uint32_t edi, uint32_t ebp,
                               const uint32_t *stack, unsigned count)
{
    uint32_t result;
    vertrix_lift_in_esi = esi;
    vertrix_lift_in_edi = edi;
    vertrix_lift_in_ebp = ebp;
    result = lift_call_arguments(&port->env, target, eax, edx, ebx, ecx, stack, count);
    vertrix_lift_in_esi = vertrix_lift_in_edi = vertrix_lift_in_ebp = 0;
    return result;
}

/* Original 0x4259d0: the scene restart after a load: 0x47ce10 on the save 0x558c80 (its +4 and +8
 * with the slot +0x268 of 0x544070), 0x4719f0 on it, then 0x41a9e0, 0x4719e0, 0x45f9f0, 0x45e670
 * with 0 and with 1 (0x421f10), 0x45ea80, 0x45e8f0, 0x45e910, 0x418840 and 0x41d5b0 (each on the
 * edx the one before leaves). */
uint32_t vertrix_port_scene_reload_4259d0(PORT_SIGNATURE)
{
    Port port;
    uint32_t scene = entry->eax;
    uint32_t save;
    uint32_t pushed[4];
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    save = port_u32(&port, 0, 0x558c80);
    pushed[0] = 0;
    pushed[1] = 0;
    pushed[2] = port_u32(&port, save, 4);
    pushed[3] = port_u32(&port, save, 8);
    port_forward_stack(&port, entry, 0x47ce10, save,
                       port_u32(&port, port_u32(&port, 0, 0x544070), 0x268), 0, 0, scene, pushed,
                       4);
    port_forward_esi(&port, entry, 0x4719f0, port_u32(&port, 0, 0x558c80), vertrix_lift_edx, 0, 0,
                     scene);
    result = port_forward_esi(&port, entry, 0x41a9e0, scene, vertrix_lift_edx, 0, 0, scene);
    result = port_forward_esi(&port, entry, 0x4719e0, result, vertrix_lift_edx, 0, 0, scene);
    port_forward_esi(&port, entry, 0x45f9f0, result, vertrix_lift_edx, 0, 0, scene);
    port_forward_esi(&port, entry, 0x45e670, 0, vertrix_lift_edx, 0, 0, scene);
    result = port_forward_esi(&port, entry, 0x45e670, 1, 0x421f10, 0, 0, scene);
    result = port_forward_esi(&port, entry, 0x45ea80, result, vertrix_lift_edx, 0, 0, scene);
    result = port_forward_esi(&port, entry, 0x45e8f0, result, vertrix_lift_edx, 0, 0, scene);
    port_forward_esi(&port, entry, 0x45e910, result, vertrix_lift_edx, 0, 0, scene);
    port_forward_esi(&port, entry, 0x418840, scene, vertrix_lift_edx, 0, 0, scene);
    result = port_forward_esi(&port, entry, 0x41d5b0, scene, vertrix_lift_edx, 0, 0, scene);
    return port_return(&port, result, entry->edx);
}

/* Original 0x4293e0: load the saved block eax from the file edx (opened by 0x48a8a0) when its
 * size (0x48aa70, on the edx that leaves) is 0x228: the dword and the 0x224 bytes after by
 * 0x48a930, the 20 bytes from +0x70 inverted, and state 1 moved on to 2 (+0x50 cleared). */
uint32_t vertrix_port_saved_block_load_4293e0(PORT_SIGNATURE)
{
    Port port;
    uint32_t block = entry->eax;
    uint32_t file = entry->edx;
    uint32_t size;
    uint32_t index;
    port_open(&port, calls, services, globals, entry);
    call_registers(&port, 0x48a8a0, file, file, entry->ebx, entry->ecx, file, block, entry->ebp,
                   NULL, 0);
    size = call_registers(&port, 0x48aa70, vertrix_lift_edx, vertrix_lift_edx, entry->ebx,
                          entry->ecx, file, block, entry->ebp, NULL, 0);
    if (size != 0x228)
    {
        return port_return(&port, size, vertrix_lift_edx);
    }
    call_registers(&port, 0x48a930, file, block, 1, 4, file, block, entry->ebp, NULL, 0);
    call_registers(&port, 0x48a930, file, block + 4, 1, 0x224, file, block, entry->ebp, NULL, 0);
    for (index = 0; index < 0x14; index++)
    {
        port_set8(&port, block + 0x70, index, 0xff - port_u8(&port, block + 0x70, index));
    }
    if (port_u32(&port, block, 0) == 1)
    {
        port_set32(&port, block, 0, 2);
        port_set32(&port, block, 0x50, 0);
    }
    return port_return(&port, block + 0x84, 0x14);
}

/* Original 0x42af80: with two or more children (+0x188), rotate them (+0x15c on) one place
 * down, the first to the end; then the handler 0x44c370 for the one before last and 0x44c2b0 for
 * the last by 0x4ac8f0. */
uint32_t vertrix_port_piece_actor_cycle_42af80(PORT_SIGNATURE)
{
    Port port;
    uint32_t piece = entry->eax;
    uint32_t first;
    uint32_t index;
    uint32_t count;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    if (port_u32(&port, piece, 0x188) < 2)
    {
        return port_return(&port, piece, entry->edx);
    }
    first = port_u32(&port, piece, 0x15c);
    for (index = 0; index < port_u32(&port, piece, 0x188) - 1; index++)
    {
        port_set32(&port, piece + index * 4, 0x15c, port_u32(&port, piece + index * 4, 0x160));
    }
    count = port_u32(&port, piece, 0x188);
    port_set32(&port, piece + count * 4, 0x158, first);
    port_forward_esi(&port, entry, 0x4ac8f0,
                     port_u32(&port, piece + port_u32(&port, piece, 0x188) * 4, 0x154), 0x44c370,
                     piece, count - 1, first);
    result = port_forward_esi(&port, entry, 0x4ac8f0,
                              port_u32(&port, piece + port_u32(&port, piece, 0x188) * 4, 0x158),
                              0x44c2b0, piece, count - 1, first);
    return port_return(&port, result, entry->edx);
}

/* Original 0x42ecc0: 0x4b2300 on the collection +0x87c (65 entries) with the handler edx. */
uint32_t vertrix_port_board_collection_all_handler_42ecc0(PORT_SIGNATURE)
{
    Port port;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    result = port_forward(&port, entry, 0x4b2300, entry->eax + 0x87c, 0x41, entry->edx, entry->ecx);
    return port_return(&port, result, vertrix_lift_edx);
}

/* Original 0x42f210: 0x42ef80 with minus the colour +0x58, then for each of the five columns
 * whose slot +0x988 is set, its 13 marks (+0x19d on) set to minus the colour. */
uint32_t vertrix_port_board_mark_columns_42f210(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x1c
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t board = entry->eax;
    uint32_t column;
    uint32_t eax;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    call_registers(&port, 0x42ef80, board,
                   (uint32_t)(int32_t)(int8_t)(0 - port_u8(&port, board, 0x58)), entry->ebx, board,
                   entry->esi, board, ebp, NULL, 0);
    eax = board + 0xd;
    port_set32(&port, ebp, -0x18u, eax);
    for (column = 0; column < 5; column++)
    {
        if (port_u32(&port, board + column * 4, 0x988) != 0)
        {
            uint32_t end = port_u32(&port, ebp, -0x18u);
            eax = column * 0xd + board;
            do
            {
                uint8_t colour = (uint8_t)(0 - port_u8(&port, board, 0x58));
                eax++;
                port_set8(&port, eax, 0x19c, colour);
            } while (eax != end);
        }
        port_set32(&port, ebp, -0x18u, port_u32(&port, ebp, -0x18u) + 0xd);
    }
    return port_return(&port, eax, entry->edx);
}

/* The rows of the board eax after `call` (with the colour, the signed byte +0x58): for each of the
 * 13 rows whose slot at `slots` is set, its five marks (+0x15c on, 13 apart) set to the colour. */
static uint32_t board_mark_rows(PORT_SIGNATURE, uint32_t call, uint32_t slots)
{
    enum
    {
        BELOW = 0x20
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t board = entry->eax;
    uint32_t row;
    uint32_t eax;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, -0x1cu, board);
    eax =
        call_registers(&port, call, board, (uint32_t)((int32_t)port_u32(&port, board, 0x55) >> 24),
                       entry->ebx, board, entry->esi, board, ebp, NULL, 0);
    port_set32(&port, ebp, -0x18u, 0x41);
    for (row = 0; row < 0xd; row++)
    {
        if (port_u32(&port, board + row * 4, slots) != 0)
        {
            uint32_t end = port_u32(&port, ebp, -0x1cu) + port_u32(&port, ebp, -0x18u);
            eax = row + board;
            do
            {
                eax += 0xd;
                port_set8(&port, eax, 0x14f, port_u8(&port, board, 0x58));
            } while (eax != end);
        }
        port_set32(&port, ebp, -0x18u, port_u32(&port, ebp, -0x18u) + 1);
    }
    return port_return(&port, eax, entry->edx);
}

/* Original 0x42f440: 0x42f7d0 and the slots +0x9e8. */
uint32_t vertrix_port_board_mark_rows_first_42f440(PORT_SIGNATURE)
{
    return board_mark_rows(calls, services, globals, entry, 0x42f7d0, 0x9e8);
}

/* Original 0x42f4b0: 0x42f810 and the slots +0xa2c. */
uint32_t vertrix_port_board_mark_rows_second_42f4b0(PORT_SIGNATURE)
{
    return board_mark_rows(calls, services, globals, entry, 0x42f810, 0xa2c);
}

/* Original 0x42f760: for each of the five columns (0x34 bytes from +0x220), release the block in
 * its top slot (+0x250) by its first method (edx 2) and shift the 13 slots one place up. */
uint32_t vertrix_port_board_drop_columns_42f760(PORT_SIGNATURE)
{
    Port port;
    uint32_t board = entry->eax;
    uint32_t column;
    uint32_t eax = board;
    port_open(&port, calls, services, globals, entry);
    for (column = 0; column < 5; column++)
    {
        uint32_t base = column * 0x34 + board;
        uint32_t top = port_u32(&port, base, 0x250);
        uint32_t at;
        if (top != 0)
        {
            uint32_t methods = port_u32(&port, top, 0x158);
            call_registers(&port, port_u32(&port, methods, 0), top, 2, column, methods, board, 0,
                           entry->ebp, NULL, 0);
            port_set32(&port, base, 0x250, 0);
        }
        for (at = base + 0x2c;; at -= 4)
        {
            port_set32(&port, at, 0x224, port_u32(&port, at, 0x220));
            port_set32(&port, at, 0x220, 0);
            if (at == base)
            {
                break;
            }
        }
        eax = base;
    }
    return port_return(&port, eax, entry->edx);
}

/* Original 0x431390: start the level effect +0xa60 when it is idle (+0x168): the wait of the
 * level 0x532bbc (0x4f7d14) by 0x4ac7d0, its speed (0x4f7d20) at +0x1a, and 0x4ac510. */
uint32_t vertrix_port_player_level_effect_431390(PORT_SIGNATURE)
{
    Port port;
    uint32_t player = entry->eax;
    uint32_t effect;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    effect = port_u32(&port, player, 0xa60);
    if (effect == 0)
    {
        return port_return(&port, player, entry->edx);
    }
    if (port_u32(&port, effect, 0x168) != 0)
    {
        return port_return(&port, effect, entry->edx);
    }
    port_set32(&port, effect, 0x168, 1);
    port_forward(&port, entry, 0x4ac7d0, port_u32(&port, player, 0xa60),
                 port_u32(&port, port_u32(&port, 0, 0x532bbc) * 4, 0x4f7d14), 0, player);
    effect = port_u32(&port, player, 0xa60);
    port_set16(&port, effect, 0x1a, port_u16(&port, port_u32(&port, 0, 0x532bbc) * 4, 0x4f7d20));
    result =
        port_forward(&port, entry, 0x4ac510, port_u32(&port, player, 0xa60), effect, 0, player);
    return port_return(&port, result, entry->edx);
}

/* Original 0x431400: the same for the side edx, from the tables 0x4f7d50 and 0x4f7dc8 (40 bytes
 * a level). */
uint32_t vertrix_port_player_level_side_431400(PORT_SIGNATURE)
{
    Port port;
    uint32_t player = entry->eax;
    uint32_t side = entry->edx * 4;
    uint32_t effect;
    uint32_t level;
    uint32_t edx;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    effect = port_u32(&port, player, 0xa60);
    if (effect == 0 || port_u32(&port, effect, 0x168) != 0)
    {
        return port_return(&port, entry->eax, effect);
    }
    level = port_u32(&port, 0, 0x532bbc);
    call_registers(&port, 0x4ac7d0, effect, port_u32(&port, side + level * 40, 0x4f7d50), effect,
                   player, side, 0, entry->ebp, NULL, 0);
    level = port_u32(&port, 0, 0x532bbc);
    edx = (vertrix_lift_edx & 0xffff0000u) | port_u16(&port, side + level * 40, 0x4f7dc8);
    port_set16(&port, port_u32(&port, player, 0xa60), 0x1a, edx);
    result = call_registers(&port, 0x4ac510, port_u32(&port, player, 0xa60), edx, effect, player,
                            side + level * 40, 0, entry->ebp, NULL, 0);
    return port_return(&port, result, vertrix_lift_edx);
}

/* Original 0x432200: release by its first method (edx 2) and clear every block of the five
 * columns (13 slots from +0x220, 0x34 bytes a column) whose type (+0x15d) is 2. */
uint32_t vertrix_port_board_purge_type_two_432200(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x20
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t board = entry->eax;
    uint32_t column;
    uint32_t eax = board;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, -0x18u, board);
    port_set32(&port, ebp, -0x1cu, board + 0x104);
    for (column = board; column != board + 0x104; column += 0x34)
    {
        uint32_t slot;
        port_set32(&port, ebp, -0x18u, column);
        for (slot = 0; slot < 0xd; slot++)
        {
            uint32_t block = port_u32(&port, column + slot * 4, 0x220);
            eax = slot * 4 + column;
            if (block != 0)
            {
                eax = block;
                if (port_u8(&port, block, 0x15d) == 2)
                {
                    uint32_t methods = port_u32(&port, block, 0x158);
                    eax = call_registers(&port, port_u32(&port, methods, 0), block, 2,
                                         column + slot * 4, slot, methods, column, ebp, NULL, 0);
                    port_set32(&port, column + slot * 4, 0x220, 0);
                }
            }
        }
        port_set32(&port, ebp, -0x18u, column + 0x34);
    }
    return port_return(&port, eax, entry->edx);
}

/* Original 0x432280: whether any block of the five columns has the type (+0x15d) 1. */
uint32_t vertrix_port_board_has_type_one_432280(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x1c
    };
    Port port;
    uint32_t local = entry->esp - 0x1c;
    uint32_t board = entry->eax;
    uint32_t column;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, local, 0, 0);
    for (column = 0; column < 5; column++)
    {
        uint32_t slot;
        for (slot = 0; slot < 0xd; slot++)
        {
            uint32_t block = port_u32(&port, board + port_u32(&port, local, 0) + slot * 4, 0x220);
            if (block != 0 && port_u8(&port, block, 0x15d) == 1)
            {
                return port_return(&port, 1, entry->edx);
            }
        }
        port_set32(&port, local, 0, port_u32(&port, local, 0) + 0x34);
    }
    return port_return(&port, 0, entry->edx);
}

/* The 65 cells of the board eax after 0x4327e0 (the blocks +0x220 into the kinds +0x1de): the
 * mark +0xb94 of each set from its kind: `five` for kind 5, 0 for an empty cell (0xff), `six` for
 * kind 6 and `other` for the rest. eax keeps the last kind and mark in ah and al. */
static uint32_t board_mark_kinds(PORT_SIGNATURE, uint32_t six, uint32_t other, uint32_t eax_bytes)
{
    enum
    {
        BELOW = 0x20
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t board = entry->eax;
    uint32_t cell;
    uint32_t eax;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    /* The kinds-in-eax copies keep the board in ecx, the others in esi. */
    call_registers(&port, 0x4327e0, board + 0x220, board + 0x1de, 0x41,
                   eax_bytes ? board : entry->ecx, eax_bytes ? entry->esi : board, entry->edi, ebp,
                   NULL, 0);
    eax = board + 0xd;
    port_set32(&port, ebp, -0x18u, board + 0xd);
    port_set32(&port, ebp, -0x1cu, board + 0x41);
    for (cell = 0; cell < 0x41; cell++)
    {
        uint32_t kind = port_u8(&port, board + cell, 0x1de);
        uint32_t mark;
        if (kind == 0xff)
        {
            mark = 0;
        }
        else if (kind == 5)
        {
            mark = 1;
        }
        else if (kind == 6)
        {
            mark = six;
        }
        else
        {
            mark = other;
        }
        port_set8(&port, board + cell + 1, 0xb93, mark);
        if (eax_bytes)
        {
            eax = (eax & 0xffff0000u) | (kind << 8) | mark;
        }
        if (cell % 0xd == 0xc)
        {
            port_set32(&port, ebp, -0x18u, port_u32(&port, ebp, -0x18u) + 0xd);
        }
    }
    return port_return(&port, eax_bytes ? eax : board + 0x41, entry->edx);
}

/* Original 0x436fe0: kind 5 marked 1, the rest 0. */
uint32_t vertrix_port_board_mark_fives_436fe0(PORT_SIGNATURE)
{
    return board_mark_kinds(calls, services, globals, entry, 0, 0, 0);
}

/* Original 0x437240: the same. */
uint32_t vertrix_port_board_mark_fives_437240(PORT_SIGNATURE)
{
    return board_mark_kinds(calls, services, globals, entry, 0, 0, 0);
}

/* Original 0x437f60: kind 5 marked 1, kind 6 and empty cells 0, the rest 2. */
uint32_t vertrix_port_board_mark_stones_not_bombs_437f60(PORT_SIGNATURE)
{
    return board_mark_kinds(calls, services, globals, entry, 0, 2, 1);
}

/* Original 0x4383f0: kind 5 marked 1, empty cells 0, the rest 2. */
uint32_t vertrix_port_board_mark_stones_4383f0(PORT_SIGNATURE)
{
    return board_mark_kinds(calls, services, globals, entry, 2, 2, 1);
}

/* Original 0x437460: for each of the marked cells (0x436030 counts them, 0x4360b0 gives each
 * column and row into locals), the block there the handler 0x44d9d0 and its companion (+0x87c)
 * 0x44dbb0 by 0x4ac8f0; 1, or 0 when there are none. */
uint32_t vertrix_port_board_flag_marked_437460(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x24
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t board = entry->eax;
    uint32_t count;
    uint32_t index = 0;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    count = call_registers(&port, 0x436030, board, entry->edx, entry->ebx, entry->ecx, entry->esi,
                           board, ebp, NULL, 0);
    port_set32(&port, ebp, -0x18u, count);
    if (count == 0)
    {
        return port_return(&port, 0, entry->edx);
    }
    do
    {
        uint32_t cell;
        uint32_t companion;
        call_registers(&port, 0x4360b0, board, index, ebp - 0x20, ebp - 0x1c, index, board, ebp,
                       NULL, 0);
        cell = port_u32(&port, ebp, -0x20u) * 0x34 + board + port_u32(&port, ebp, -0x1cu) * 4;
        companion = port_u32(&port, cell, 0x87c);
        index++;
        call_registers(&port, 0x4ac8f0, port_u32(&port, cell, 0x220), 0x44d9d0, ebp - 0x20,
                       companion, index, board, ebp, NULL, 0);
        call_registers(&port, 0x4ac8f0, companion, 0x44dbb0, ebp - 0x20,
                       port_u32(&port, ebp, -0x18u), index, board, ebp, NULL, 0);
    } while (index < port_u32(&port, ebp, -0x18u));
    return port_return(&port, 1, entry->edx);
}

/* Original 0x437b70: for each of the 13 rows a random draw (0x4826c0 on 0x598d30 with 48), and
 * the companions (+0x87c) of its five cells given +0x68 48. */
uint32_t vertrix_port_board_stamp_companions_437b70(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x1c
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t board = entry->eax;
    uint32_t row;
    uint32_t eax = board;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, -0x14u, board);
    port_set32(&port, ebp, -0x18u, board);
    for (row = 0; row < 0xd; row++)
    {
        uint32_t end;
        call_registers(&port, 0x4826c0, 0x598d30, 0x30, row, port_u32(&port, ebp, -0x18u),
                       0x104 + row * 4, entry->edi, ebp, NULL, 0);
        end = port_u32(&port, ebp, -0x18u) + 0x104 + row * 4;
        for (eax = row * 4 + port_u32(&port, ebp, -0x14u); eax != end; eax += 0x34)
        {
            uint32_t companion = port_u32(&port, eax, 0x87c);
            if (companion != 0)
            {
                port_set32(&port, companion, 0x68, 0x30);
            }
        }
    }
    return port_return(&port, eax, entry->edx);
}
