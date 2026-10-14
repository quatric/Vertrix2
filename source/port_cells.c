#include "port_cells.h"

/* Board cell, marker, pattern and actor step helpers. */

/* A call handing the callee esi, edi and ebp as given. */
static uint32_t call_registers(Port *port, uint32_t target, uint32_t eax, uint32_t edx,
                               uint32_t ebx, uint32_t ecx, uint32_t esi, uint32_t edi, uint32_t ebp)
{
    uint32_t result;
    vertrix_lift_in_esi = esi;
    vertrix_lift_in_edi = edi;
    vertrix_lift_in_ebp = ebp;
    result = lift_call_arguments(&port->env, target, eax, edx, ebx, ecx, NULL, 0);
    vertrix_lift_in_esi = vertrix_lift_in_edi = vertrix_lift_in_ebp = 0;
    return result;
}

/* Original 0x4387b0: for each block of the five columns: one landing (+0x44 16) of kind 5
 * (+0x15c) gets +0x93 0, +0x4e 50 and +0x95 1; any other the handler 0x44eaf0 by 0x4ac8f0. 1. */
uint32_t vertrix_port_board_prepare_slots_4387b0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x1c
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t board = entry->eax;
    uint32_t column;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, -0x18u, board);
    for (column = 0; column < 5; column++)
    {
        uint32_t end = board + 0x34 + column * 0x34;
        uint32_t slot;
        for (slot = board + column * 0x34; slot != end; slot += 4)
        {
            uint32_t block = port_u32(&port, slot, 0x220);
            if (block == 0)
            {
                continue;
            }
            if (port_u8(&port, block, 0x44) == 0x10)
            {
                if (port_u8(&port, block, 0x15c) == 5)
                {
                    port_set8(&port, block, 0x93, 0);
                    port_set8(&port, block, 0x4e, 0x32);
                    port_set8(&port, block, 0x95, 1);
                }
            }
            else
            {
                call_registers(&port, 0x4ac8f0, block, 0x44eaf0, end, slot, column, end, ebp);
            }
        }
    }
    return port_return(&port, 1, entry->edx);
}

/* The `wanted` marker number edx of the column (stack argument) of the board eax, counted from the
 * bottom of its marks +0xb94 (13 per column): its column at [ebx] and row at [ecx], and 1; or 0. */
static uint32_t board_marker_in_column(PORT_SIGNATURE, uint32_t wanted)
{
    enum
    {
        BELOW = 0x10
    };
    Port port;
    uint8_t stack[BELOW + 8 + 4];
    uint32_t board = entry->eax;
    uint32_t column;
    uint32_t cell;
    uint32_t row;
    uint32_t seen = 0;
    port_open_arguments(&port, stack, calls, services, globals, entry, BELOW, 1);
    port_set32(&port, entry->esp, -0x10u, entry->ebx);
    column = port_u32(&port, entry->esp, 4);
    cell = column * 0xd + board + 0xc;
    for (row = 0xc; (int32_t)row >= 0; row--, cell--)
    {
        if (port_u8(&port, cell, 0xb94) == wanted)
        {
            if (seen == entry->edx)
            {
                port_set32(&port, port_u32(&port, entry->esp, -0x10u), 0, column);
                port_set32(&port, entry->ecx, 0, row);
                return port_return(&port, 1, column);
            }
            seen++;
        }
    }
    return port_return(&port, 0, cell);
}

/* Original 0x438830: the mark 1. */
uint32_t vertrix_port_board_marker_in_column_438830(PORT_SIGNATURE)
{
    return board_marker_in_column(calls, services, globals, entry, 1);
}

/* Original 0x4388a0: the mark 2. */
uint32_t vertrix_port_board_marker_in_column_4388a0(PORT_SIGNATURE)
{
    return board_marker_in_column(calls, services, globals, entry, 2);
}

/* Original 0x438c60: the pattern dl (65 cells from 0x4f7e40): each block in a cell it marks 1
 * gets +0x48 100. eax 5, edx past the last row. */
uint32_t vertrix_port_board_apply_pattern_438c60(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x20
    };
    Port port;
    uint32_t local = entry->esp - 0x20;
    uint32_t board = entry->eax;
    uint32_t pattern = entry->edx & 0xff;
    uint32_t row;
    uint32_t edx = board;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, local, 4, board);
    port_set8(&port, local, 8, pattern);
    port_set32(&port, local, 0, 0);
    for (row = 0; row != 0x34; row += 4)
    {
        uint32_t column;
        uint32_t base = port_u32(&port, local, 0);
        edx = port_u32(&port, local, 4) + row;
        for (column = 0; column < 5; column++, edx += 0x34)
        {
            uint32_t block = port_u32(&port, edx, 0x220);
            if (block != 0 &&
                port_u8(&port, port_u8(&port, local, 8) * 0x41 + base + column, 0x4f7e40) == 1)
            {
                port_set16(&port, block, 0x48, 0x64);
            }
        }
        port_set32(&port, local, 0, base + 5);
    }
    return port_return(&port, 5, edx);
}

/* Original 0x438cd0: the kinds of the boards eax and edx by 0x4327e0 (both into the same local)
 * compared with the local below it, 13 cells a row; 1 when all match, otherwise 0 (edx the cell
 * of the row). */
uint32_t vertrix_port_board_kinds_match_438cd0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x94
    };
    Port port;
    uint8_t stack[BELOW + 8];
    uint32_t ebp = entry->esp - 4;
    uint32_t row;
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    call_registers(&port, 0x4327e0, entry->eax + 0x220, ebp - 0x4c, 0x41, entry->edx, entry->esi,
                   entry->edi, ebp);
    call_registers(&port, 0x4327e0, entry->edx + 0x220, ebp - 0x4c, 0x41, entry->edx, entry->esi,
                   entry->edi, ebp);
    for (row = 0; (int32_t)row < 0x41; row += 0xd)
    {
        uint32_t cell;
        for (cell = 0; cell < 0xd; cell++)
        {
            if (port_u8(&port, ebp - 0x4c + row, cell) != port_u8(&port, ebp - 0x90 + row, cell))
            {
                return port_return(&port, 0, cell);
            }
        }
    }
    return port_return(&port, 1, 0xd);
}

/* Original 0x438d50: for edx below ebx, whether any of the five columns of the board eax holds a
 * block (kinds by 0x4327e0, 0xff empty); edx the count of the last column. */
uint32_t vertrix_port_board_any_block_438d50(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x18
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t board = entry->eax;
    uint32_t column;
    uint32_t count = 0;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, -0x14u, board);
    if ((int32_t)entry->edx >= (int32_t)entry->ebx)
    {
        return port_return(&port, 0, entry->edx);
    }
    call_registers(&port, 0x4327e0, board + 0x220, board + 0x1de, 0x41, entry->ecx, 0, board, ebp);
    port_set32(&port, ebp, -0x10u, 0);
    for (column = 0; column < 5; column++)
    {
        uint32_t cell;
        count = 0;
        for (cell = 0; cell < 0xd; cell++)
        {
            if (port_u8(&port, board + column * 0xd + cell, 0x1de) != 0xff)
            {
                count++;
            }
        }
        if (count > port_u32(&port, ebp, -0x10u))
        {
            port_set32(&port, ebp, -0x10u, count);
        }
    }
    return port_return(&port, port_u32(&port, ebp, -0x10u) != 0, count);
}

/* Original 0x439370: the marks +0xb94 of the 65 cells of the board eax set to whether their kind
 * (0x4327e0, signed) is the dword ebx of the table edx. */
uint32_t vertrix_port_board_mark_kind_439370(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x18
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t board = entry->eax;
    uint32_t wanted;
    uint32_t cell;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    call_registers(&port, 0x4327e0, board + 0x220, board + 0x1de, 0x41, board, entry->edx,
                   entry->ebx << 2, ebp);
    wanted = entry->edx + (entry->ebx << 2);
    port_set32(&port, ebp, -0x10u, board + 0xd);
    port_set32(&port, ebp, -0x14u, board + 0x41);
    for (cell = 0; cell < 0x41; cell++)
    {
        uint32_t kind = (uint32_t)(int32_t)(int8_t)port_u8(&port, board + cell, 0x1de);
        port_set8(&port, board + cell + 1, 0xb93, kind == port_u32(&port, wanted, 0));
        if (cell % 0xd == 0xc)
        {
            port_set32(&port, ebp, -0x10u, port_u32(&port, ebp, -0x10u) + 0xd);
        }
    }
    return port_return(&port, board + 0x41, port_u32(&port, ebp, -0x10u));
}

/* Original 0x43aab0: the side dl of the player eax (+0x190): its display (+0x15c) placed at the
 * side's corner (0x4f8a48/0x4f8a4c, or 0x4f8a50/0x4f8a54), given its id and owner, and the side
 * passed to the partner +0x450 (+0x17c). */
uint32_t vertrix_port_player_set_side_43aab0(PORT_SIGNATURE)
{
    Port port;
    uint32_t player = entry->eax;
    uint32_t side = entry->edx & 0xff;
    uint32_t partner;
    port_open(&port, calls, services, globals, entry);
    port_set8(&port, player, 0x190, side);
    port_set16(&port, port_u32(&port, player, 0x15c), 0xe,
               port_u16(&port, 0, side == 0 ? 0x4f8a48 : 0x4f8a50));
    port_set16(&port, port_u32(&port, player, 0x15c), 0x16,
               port_u16(&port, 0, side == 0 ? 0x4f8a4c : 0x4f8a54));
    port_set32(&port, port_u32(&port, player, 0x15c), 4, port_u32(&port, player, 0));
    port_set32(&port, port_u32(&port, player, 0x15c), 0xce8, player);
    partner = port_u32(&port, player, 0x450);
    side = port_u8(&port, player, 0x190);
    port_set8(&port, partner, 0x17c, side);
    return port_return(&port, (player & 0xffffff00u) | side, partner);
}

/* Original 0x43acd0: 0x43d320, then 0x43d330 with the table entry of the player's mode
 * (+0x488, 0x532cf0) and the chain record 0x418000 picks (28 bytes each, 0x118 a mode, from
 * 0x544f90) when 0x417fc0 finds one, otherwise none. */
uint32_t vertrix_port_object_chain_select_pair_43acd0(PORT_SIGNATURE)
{
    Port port;
    uint32_t player = entry->eax;
    uint32_t record = 0;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    port_forward_esi(&port, entry, 0x43d320, player, entry->edx, entry->ebx, entry->ecx, player);
    if (port_forward_esi(&port, entry, 0x417fc0, port_u32(&port, player, 0x488), 2, entry->ebx,
                         entry->ecx, player) != 0)
    {
        uint32_t pick = port_forward_esi(&port, entry, 0x418000, port_u32(&port, player, 0x488), 2,
                                         0, entry->ecx, player);
        record = pick * 28 + 0x544f90 + port_u32(&port, player, 0x488) * 0x118;
    }
    result =
        port_forward_esi(&port, entry, 0x43d330, player, record,
                         port_u32(&port, port_u32(&port, player, 0x488) * 4, 0x532cf0), 0, player);
    return port_return(&port, result, entry->edx);
}

/* Original 0x43b6a0: the two values (entries edx and ebx of the level's 40-byte rows, 0x4f8d84)
 * of the player's table (+0x488, 0x4f8d38 at 0x540f80) kept at 0x540f78 and 0x540f7c and drawn
 * by 0x482770 on 0x598d48. */
uint32_t vertrix_port_player_draw_table_value_43b6a0(PORT_SIGNATURE)
{
    Port port;
    uint32_t table;
    uint32_t level;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    table = port_u32(&port, port_u32(&port, entry->eax, 0x488) * 4, 0x4f8d38);
    port_set32(&port, 0, 0x540f80, table);
    level = port_u32(&port, 0, 0x532bbc) * 0xf0;
    port_set32(
        &port, 0, 0x540f78,
        port_u32(&port, entry->edx * 40 + level + port_u32(&port, 0, 0x540f80) * 4, 0x4f8d84));
    port_set32(
        &port, 0, 0x540f7c,
        port_u32(&port, entry->ebx * 40 + level + port_u32(&port, 0, 0x540f80) * 4, 0x4f8d84));
    result = port_forward_esi(&port, entry, 0x482770, 0x598d48, port_u16(&port, 0, 0x540f78),
                              port_u16(&port, 0, 0x540f7c), level, entry->edx);
    return port_return(&port, result, vertrix_lift_edx);
}

/* The wait step of 0x4434e0 and 0x443d50: the flag `flag` set, and when the step is due 0x4ad790
 * with the step value (kept at `flag` + 4) decides it (kept at `flag`); with it clear `before`
 * (when set) is stored at +0x44 and the handler `next` by 0x4ac8f0. The due test compares with
 * the edx 0x4ac520 leaves. */
static uint32_t global_wait(PORT_SIGNATURE, uint32_t flag, uint32_t next, int land)
{
    Port port;
    uint32_t actor = entry->eax;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    port_set32(&port, 0, flag, 1);
    port_forward(&port, entry, 0x4ac500, actor, 1, entry->ebx, actor);
    result = port_forward(&port, entry, 0x4ac520, actor, vertrix_lift_edx, entry->ebx, actor);
    if (result == vertrix_lift_edx)
    {
        port_set32(
            &port, 0, flag + 4,
            port_forward(&port, entry, 0x4ac540, actor, vertrix_lift_edx, entry->ebx, actor));
        port_forward(&port, entry, 0x4ac5b0, actor, vertrix_lift_edx, entry->ebx, actor);
        result = port_forward(&port, entry, 0x4ad790, actor, port_u32(&port, 0, flag + 4),
                              entry->ebx, actor);
        port_set32(&port, 0, flag, result);
    }
    if (port_u32(&port, 0, flag) == 0)
    {
        if (land)
        {
            port_set8(&port, actor, 0x44, 0x10);
        }
        result = port_forward(&port, entry, 0x4ac8f0, actor, next, entry->ebx, actor);
    }
    return port_return(&port, result, entry->edx);
}

/* Original 0x4434e0: the flag 0x544894, next 0x443550. */
uint32_t vertrix_port_actor_global_wait_4434e0(PORT_SIGNATURE)
{
    return global_wait(calls, services, globals, entry, 0x544894, 0x443550, 0);
}

/* Original 0x443d50: the flag 0x544914, landing (+0x44 16) and next 0x443dc0. */
uint32_t vertrix_port_actor_global_wait_443d50(PORT_SIGNATURE)
{
    return global_wait(calls, services, globals, entry, 0x544914, 0x443dc0, 1);
}

/* Step the actor (0x4ac540 and 0x4ac5b0 when due; the actor the edx each call leaves), then +0x52
 * 9, the callback +0x178 (when set) on the partner's (+0x160) +0x15c, and the handler `next`. */
static uint32_t actor_callback_step(PORT_SIGNATURE, uint32_t next)
{
    Port port;
    uint32_t actor = entry->eax;
    uint32_t callback;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    port_forward(&port, entry, 0x4ac500, actor, actor, entry->ebx, actor);
    if (port_forward(&port, entry, 0x4ac520, vertrix_lift_edx, vertrix_lift_edx, entry->ebx,
                     actor) == 1)
    {
        port_forward(&port, entry, 0x4ac540, vertrix_lift_edx, vertrix_lift_edx, entry->ebx, actor);
        port_forward(&port, entry, 0x4ac5b0, vertrix_lift_edx, vertrix_lift_edx, entry->ebx, actor);
    }
    callback = port_u32(&port, actor, 0x178);
    port_set8(&port, actor, 0x52, 9);
    if (callback != 0)
    {
        port_forward(&port, entry, callback, port_u32(&port, port_u32(&port, actor, 0x160), 0x15c),
                     actor, callback, actor);
    }
    result = port_forward(&port, entry, 0x4ac8f0, actor, next, callback, actor);
    return port_return(&port, result, entry->edx);
}

/* Original 0x445890: next 0x445770. */
uint32_t vertrix_port_actor_callback_step_445890(PORT_SIGNATURE)
{
    return actor_callback_step(calls, services, globals, entry, 0x445770);
}

/* Original 0x445d10: next 0x445b90. */
uint32_t vertrix_port_actor_callback_step_445d10(PORT_SIGNATURE)
{
    return actor_callback_step(calls, services, globals, entry, 0x445b90);
}

/* Original 0x445e90: next 0x445d80. */
uint32_t vertrix_port_actor_callback_step_445e90(PORT_SIGNATURE)
{
    return actor_callback_step(calls, services, globals, entry, 0x445d80);
}

/* The bob of 0x445a90 and 0x445b10: when due, words +0x4a `height` and +0x4c 5 and 0x4ad530,
 * which when done hands over to `next`; then 0x445900, and unless 0x47f410 holds for 0x5bb254 the
 * handler 0x445a00. */
static uint32_t actor_bob(PORT_SIGNATURE, uint32_t height, uint32_t next)
{
    Port port;
    uint32_t actor = entry->eax;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    port_forward(&port, entry, 0x4ac500, actor, entry->edx, actor, actor);
    if (port_forward(&port, entry, 0x4ac520, actor, vertrix_lift_edx, actor, actor) == 1)
    {
        result = port_forward(&port, entry, 0x4ac540, actor, vertrix_lift_edx, actor, actor);
        port_forward(&port, entry, 0x4ac5b0, actor, result, actor, actor);
        port_set16(&port, actor, 0x4a, height);
        port_set16(&port, actor, 0x4c, 5);
        if (port_forward(&port, entry, 0x4ad530, actor, vertrix_lift_edx, actor, actor) == 0)
        {
            port_forward(&port, entry, 0x4ac8f0, actor, next, actor, actor);
        }
    }
    port_forward(&port, entry, 0x445900, actor, vertrix_lift_edx, actor, actor);
    result = port_forward(&port, entry, 0x47f410, 0x5bb254, vertrix_lift_edx, actor, actor);
    if (result == 0)
    {
        result = port_forward(&port, entry, 0x4ac8f0, actor, 0x445a00, actor, actor);
    }
    return port_return(&port, result, entry->edx);
}

/* Original 0x445a90: height 50, next 0x445b10. */
uint32_t vertrix_port_actor_bob_445a90(PORT_SIGNATURE)
{
    return actor_bob(calls, services, globals, entry, 0x32, 0x445b10);
}

/* Original 0x445b10: height 0, next 0x445a90. */
uint32_t vertrix_port_actor_bob_445b10(PORT_SIGNATURE)
{
    return actor_bob(calls, services, globals, entry, 0, 0x445a90);
}

/* Original 0x448c20: the animation set from the selection 0x532a68 (none for -1: 0x4ac8d0 and
 * 0x4ac950 with 0 and 0x4ac700; otherwise the set 0x544a34, 0x4ac710 with it and 0x4ac8a0);
 * 0x4adfe0 when the frame (0x4ac960) changed. */
uint32_t vertrix_port_actor_select_animation_448c20(PORT_SIGNATURE)
{
    Port port;
    uint32_t actor = entry->eax;
    uint32_t frame;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    frame = port_forward(&port, entry, 0x4ac960, actor, entry->edx, entry->ebx, actor);
    if (port_u32(&port, 0, 0x532a68) == 0xffffffffu)
    {
        port_forward(&port, entry, 0x4ac8d0, actor, 0, frame, actor);
        port_forward(&port, entry, 0x4ac950, actor, 0, frame, actor);
        port_forward(&port, entry, 0x4ac700, actor, vertrix_lift_edx, frame, actor);
    }
    else
    {
        port_forward(&port, entry, 0x4ac8d0, actor, 0x544a34, frame, actor);
        port_forward(&port, entry, 0x4ac710, actor, port_u32(&port, 0, 0x532a68), frame, actor);
        port_forward(&port, entry, 0x4ac8a0, actor, vertrix_lift_edx, frame, actor);
    }
    result = port_forward(&port, entry, 0x4ac960, actor, vertrix_lift_edx, frame, actor);
    if (frame != result)
    {
        result = port_forward(&port, entry, 0x4adfe0, actor, vertrix_lift_edx, frame, actor);
    }
    return port_return(&port, result, entry->edx);
}

/* Original 0x4492f0: the same from the selection 0x532a70 (the set 0x544a6c), with 0x4adfe0
 * when it is not the one kept at +0x7c (then kept). */
uint32_t vertrix_port_actor_select_animation_4492f0(PORT_SIGNATURE)
{
    Port port;
    uint32_t actor = entry->eax;
    uint32_t selection;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    if (port_u32(&port, 0, 0x532a70) == 0xffffffffu)
    {
        port_forward(&port, entry, 0x4ac8d0, actor, 0, entry->ebx, actor);
        result = port_forward(&port, entry, 0x4ac950, actor, 0, entry->ebx, actor);
    }
    else
    {
        port_forward(&port, entry, 0x4ac8d0, actor, 0x544a6c, entry->ebx, actor);
        port_forward(&port, entry, 0x4ac710, actor, port_u32(&port, 0, 0x532a70), entry->ebx,
                     actor);
        result = port_forward(&port, entry, 0x4ac8a0, actor, vertrix_lift_edx, entry->ebx, actor);
    }
    selection = port_u32(&port, 0, 0x532a70);
    if (selection != port_u32(&port, actor, 0x7c))
    {
        port_set32(&port, actor, 0x7c, selection);
        result = port_forward(&port, entry, 0x4adfe0, actor, vertrix_lift_edx, selection, actor);
    }
    return port_return(&port, result, entry->edx);
}
