#include "pauses.h"

/* The game's event waits and pause teardown, the level file load, the choice grid and piece
 * teardowns, the block maker, the piece side test and the choice row pick. */

/* The guard record (0x4ec1ec, `guard`) of a frame routine at `record`. */
static void guard_record(Port *port, uint32_t record, uint32_t guard)
{
    port_set32(port, record, 0, port->env.chain);
    port_set32(port, record, 4, 0x4ec1ec);
    port_set32(port, record, 8, guard);
    port_set32(port, record, 0xc, 0);
}

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

/* The event wait of 0x424790 and 0x424890: WaitForMultipleObjects on the three handles at
 * `handles`: the second (1) resets 0x5bb488, stops the voice (0x471b90, while 0x532a44 is 1),
 * 0x477ed0 on 0x5588f8 and takes the state 0x425a50 (0x532a80 1) or 0x4259d0; the third (2) sets
 * the channels (0x471ea0: 1 and 2 swapped while 0x532a7c is 1), resets 0x5bb494, stops the voice
 * and takes 0x425810 through 0x477ed0 and the next state; 0 then, otherwise 1. */
static uint32_t game_event_wait(PORT_SIGNATURE, uint32_t handles)
{
    Port port;
    uint32_t game = entry->eax;
    uint32_t ecx = entry->ecx;
    uint32_t edi = entry->edi;
    uint32_t ebp = entry->ebp;
    uint32_t stack[4];
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    stack[0] = 3;
    stack[1] = handles;
    stack[2] = 0;
    stack[3] = 0xffffffffu;
    result = call_frame(&port, 0x4f1cf8, game, entry->edx, game, ecx, 1, edi, ebp, stack, 4);
    if (result == 1)
    {
        uint32_t handle = port_u32(&port, 0, 0x5bb488);
        uint32_t next;
        stack[0] = handle;
        result = call_frame(&port, 0x4f1c7c, result, vertrix_lift_edx, game, ecx, 1, handle, ebp,
                            stack, 1);
        if (port_u32(&port, 0, 0x532a44) == 1)
        {
            port_call_with(&port, 0x471b90, result, vertrix_lift_edx, game, ecx, 1, handle, ebp);
        }
        port_call_with(&port, 0x477ed0, 0x5588f8, vertrix_lift_edx, game, ecx, 1, handle, ebp);
        next = port_u32(&port, 0, 0x532a80) == 1 ? 0x425a50 : 0x4259d0;
        port_call_with(&port, 0x418840, game, next, game, ecx, 1, handle, ebp);
        return port_return(&port, 0, entry->edx);
    }
    if (result != 2)
    {
        return port_return(&port, 1, entry->edx);
    }
    if (port_u32(&port, 0, 0x532a7c) == 1)
    {
        port_call_with(&port, 0x471ea0, 1, 0, game, ecx, 1, edi, ebp);
        result = port_call_with(&port, 0x471ea0, 2, 1, game, ecx, 1, edi, ebp);
    }
    else
    {
        port_call_with(&port, 0x471ea0, 1, 1, game, ecx, 1, edi, ebp);
        result = port_call_with(&port, 0x471ea0, 2, 0, game, ecx, 1, edi, ebp);
    }
    ecx = port_u32(&port, 0, 0x5bb494);
    stack[0] = ecx;
    result =
        call_frame(&port, 0x4f1c7c, result, vertrix_lift_edx, game, ecx, 1, edi, ebp, stack, 1);
    if (port_u32(&port, 0, 0x532a44) == 1)
    {
        port_call_with(&port, 0x471b90, result, vertrix_lift_edx, game, ecx, 1, edi, ebp);
    }
    port_call_with(&port, 0x477ed0, 0x5588f8, 0x425810, game, ecx, 1, edi, ebp);
    port_call_with(&port, 0x418840, game, vertrix_lift_edx, game, ecx, 0, edi, ebp);
    return port_return(&port, 0, entry->edx);
}

/* Original 0x424790: the handles 0x5bb4d4. */
uint32_t vertrix_port_game_event_wait_424790(PORT_SIGNATURE)
{
    return game_event_wait(calls, services, globals, entry, 0x5bb4d4);
}

/* Original 0x424890: the handles 0x5bb4e0. */
uint32_t vertrix_port_game_event_wait_424890(PORT_SIGNATURE)
{
    return game_event_wait(calls, services, globals, entry, 0x5bb4e0);
}

/* Original 0x4253b0: the paused game's teardown (0x540631 set while it runs): its parts close
 * (0x4b7d10, 0x41d670, 0x41dec0, 0x4ac1c0, 0x471b80, 0x471a60; with the music 0x5b9c50 playing
 * (0x4854a0) the voice 0x558c84 stops with 0x558c88 (0x471a20, 0x471a40) and 0x485520; then
 * 0x41aaf0, 0x486d00, 0x471a50 and 0x471ba0 on 0x558c7c, 0x41d6d0, 0x41dd60, 0x486da0, 0x487020,
 * 0x41d660, 0x41de80); when 0x471cd0 gives 1 the voice stops (0x471b90), the game takes the
 * state 0x424990 and 0x540631 clears. */
uint32_t vertrix_port_game_pause_teardown_4253b0(PORT_SIGNATURE)
{
    Port port;
    uint32_t game = entry->eax;
    uint32_t eax;
    port_open(&port, calls, services, globals, entry);
    if (port_u8(&port, 0, 0x540631) == 0)
    {
        port_set8(&port, 0, 0x540631, 1);
    }
#define CALL(target, value, edx)                                                                   \
    port_forward(&port, entry, (target), (value), (edx), entry->ebx, game)
    CALL(0x4b7d10, game, entry->edx);
    CALL(0x41d670, game, vertrix_lift_edx);
    eax = CALL(0x41dec0, game, vertrix_lift_edx);
    eax = CALL(0x4ac1c0, eax, vertrix_lift_edx);
    eax = CALL(0x471b80, eax, vertrix_lift_edx);
    CALL(0x471a60, eax, vertrix_lift_edx);
    if (CALL(0x4854a0, 0x5b9c50, vertrix_lift_edx) == 1)
    {
        CALL(0x471a20, port_u32(&port, 0, 0x558c84), port_u32(&port, 0, 0x558c88));
        CALL(0x471a40, port_u32(&port, 0, 0x558c84), vertrix_lift_edx);
        CALL(0x485520, 0x5b9c50, vertrix_lift_edx);
    }
    CALL(0x41aaf0, game, vertrix_lift_edx);
    CALL(0x486d00, 0x5b9c50, vertrix_lift_edx);
    CALL(0x471a50, port_u32(&port, 0, 0x558c7c), vertrix_lift_edx);
    CALL(0x41d6d0, game, vertrix_lift_edx);
    CALL(0x41dd60, game, vertrix_lift_edx);
    CALL(0x471ba0, port_u32(&port, 0, 0x558c7c), vertrix_lift_edx);
    CALL(0x486da0, 0x5b9c50, vertrix_lift_edx);
    CALL(0x487020, 0x5b9c50, vertrix_lift_edx);
    CALL(0x41d660, game, vertrix_lift_edx);
    eax = CALL(0x41de80, game, vertrix_lift_edx);
    eax = CALL(0x471cd0, eax, vertrix_lift_edx);
    if (eax != 1)
    {
        return port_return(&port, eax, entry->edx);
    }
    CALL(0x471b90, eax, vertrix_lift_edx);
    eax = CALL(0x418840, game, 0x424990);
#undef CALL
    port_set8(&port, 0, 0x540631, 0);
    return port_return(&port, eax, entry->edx);
}

/* Original 0x429460: the level file edx (guarded 0x51451c): unless 0x4895e0 and 0x4895b0 both
 * hold, a file object (0x10 bytes, 0x4ca000 and 0x488b10) opened (0x489040) is read into eax by
 * 0x429600, closed (method +0x54) and destroyed (method +4 with 2); a file that does not open
 * gets method +0x4c. */
uint32_t vertrix_port_level_file_load_429460(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x2c
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t object = entry->eax;
    uint32_t path = entry->edx;
    uint32_t guard = 0x51451c;
    uint32_t esi = guard;
    uint32_t file;
    uint32_t methods;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    guard_record(&port, ebp - 0x28, guard);
    if (port_call_with(&port, 0x4895e0, path, path, object, 0x4ec1ec, esi, 0, ebp) == 1 &&
        port_call_with(&port, 0x4895b0, vertrix_lift_edx, vertrix_lift_edx, object, 0x4ec1ec, esi,
                       0, ebp) == 1)
    {
        return port_return(&port, port_u32(&port, ebp, -0x28u), vertrix_lift_edx);
    }
    file = port_call_with(&port, 0x4ca000, 0x10, vertrix_lift_edx, object, 0x4ec1ec, esi, 0, ebp);
    if (file != 0)
    {
        port_set32(&port, ebp, -0x14u, file);
        esi = 0;
        port_set32(&port, ebp, -0x1cu, 1);
        file = port_call_with(&port, 0x488b10, file, vertrix_lift_edx, object, 1, esi, 0, ebp);
        port_set32(&port, ebp, -0x1cu, 0);
    }
    if (port_call_with(&port, 0x489040, file, vertrix_lift_edx, object, file, esi, 0, ebp) == 1)
    {
        port_call_with(&port, 0x429600, object, file, object, file, esi, 0, ebp);
        methods = port_u32(&port, file, 0);
        port_call_with(&port, port_u32(&port, methods, 0x54), file, methods, object, file, esi, 0,
                       ebp);
        methods = port_u32(&port, file, 0);
        port_call_with(&port, port_u32(&port, methods, 4), file, 2, methods, file, esi, 0, ebp);
    }
    else
    {
        methods = port_u32(&port, file, 0);
        port_call_with(&port, port_u32(&port, methods, 0x4c), file, methods, object, file, esi, 0,
                       ebp);
    }
    return port_return(&port, port_u32(&port, ebp, -0x28u), vertrix_lift_edx);
}

/* Original 0x429910: the choice grid's teardown by the flags dl: with bit 2 0x4ccb9f (0x514640)
 * and 0x4ca040; otherwise (guarded 0x5145e0, methods 0x514624) its 28 cells (+0x15c) are
 * destroyed (their method +0 with 2), then 0x4ac130 with 1 and, with bit 1, 0x4ca050. */
uint32_t vertrix_port_choice_grid_teardown_429910(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x50
    };
    Port port;
    uint8_t stack[BELOW + 8];
    uint32_t ebp = entry->esp - 4;
    uint32_t grid = entry->eax;
    uint32_t flags = entry->edx;
    uint32_t ebx = 3;
    uint32_t row;
    uint32_t column;
    uint32_t result;
    uint32_t edx;
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, -0x14u, grid);
    port_set32(&port, ebp, -0x18u, flags);
    if ((flags & 4) != 0)
    {
        port_set32(&port, ebp, -0x4cu, grid);
        port_set32(&port, ebp, -0x2cu, 1);
        result = port_call_with(&port, 0x4ccb9f, grid, 0x514640, entry->ebx, entry->ecx, 1, 0, ebp);
        port_set32(&port, ebp, -0x2cu, 0);
        port_call_with(&port, 0x4ca040, result, vertrix_lift_edx, entry->ebx, entry->ecx, 1, 0,
                       ebp);
        return port_return(&port, port_u32(&port, ebp, -0x14u), vertrix_lift_edx);
    }
    port_set32(&port, grid, 0x158, 0x514624);
    port_set32(&port, ebp, -0x24u, grid);
    port_set8(&port, ebp, -0x20u, flags);
    guard_record(&port, ebp - 0x38, 0x5145e0);
    port_set32(&port, ebp, -0x2cu, 3);
    for (row = 0; row != 0x70; row += 0x10)
    {
        for (column = 0; column != 0x10; column += 4)
        {
            uint32_t cell = port_u32(&port, grid + row + column, 0x15c);
            if (cell != 0)
            {
                ebx = port_u32(&port, cell, 0x158);
                port_call_with(&port, port_u32(&port, ebx, 0), cell, 2, ebx, column, grid + row,
                               row, ebp);
            }
        }
    }
    port_set32(&port, ebp, -0x2cu, 0);
    result = port_call_with(&port, 0x4ac130, grid, 1, ebx, 0, grid + 0x60, 0x70, ebp);
    edx = (vertrix_lift_edx & 0xffffff00u) | (flags & 0xff);
    port_set32(&port, ebp, -0x14u, result);
    port_set32(&port, ebp, -0x2cu, 0);
    if ((flags & 2) != 0)
    {
        port_call_with(&port, 0x4ca050, result, edx, ebx, 0, grid + 0x60, 0x70, ebp);
        edx = vertrix_lift_edx;
    }
    return port_return(&port, port_u32(&port, ebp, -0x14u), edx);
}

/* The piece teardown of 0x42ab10 and 0x42b190 by the flags dl: with bit 2 0x4ccb9f (`kill`)
 * and 0x4ca040; otherwise (guarded `guard`, methods `methods`) the children from +0x15c (and
 * `second` past them when set) up to `count` are destroyed (method +0 with 2), then 0x4ac130 with
 * 1 and, with bit 1, 0x4ca050. */
static uint32_t piece_teardown(PORT_SIGNATURE, uint32_t methods, uint32_t guard, uint32_t kill,
                               uint32_t count, uint32_t second)
{
    enum
    {
        BELOW = 0x4c
    };
    Port port;
    uint8_t stack[BELOW + 8];
    uint32_t ebp = entry->esp - 4;
    uint32_t piece = entry->eax;
    uint32_t flags = entry->edx;
    uint32_t ebx = 3;
    uint32_t ecx;
    uint32_t result;
    uint32_t edx;
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, -0x14u, flags);
    if ((flags & 4) != 0)
    {
        port_set32(&port, ebp, -0x48u, piece);
        port_set32(&port, ebp, -0x28u, 1);
        result =
            port_call_with(&port, 0x4ccb9f, piece, kill, entry->ebx, entry->ecx, 1, piece, ebp);
        port_set32(&port, ebp, -0x28u, 0);
        port_call_with(&port, 0x4ca040, result, 0, entry->ebx, entry->ecx, 1, piece, ebp);
        return port_return(&port, piece, vertrix_lift_edx);
    }
    port_set32(&port, piece, 0x158, methods);
    port_set8(&port, ebp, -0x1cu, flags);
    port_set32(&port, ebp, -0x20u, piece);
    guard_record(&port, ebp - 0x34, guard);
    port_set32(&port, ebp, -0x28u, 3);
    for (ecx = piece; ecx != piece + count; ecx += 4)
    {
        uint32_t child = port_u32(&port, ecx, 0x15c);
        ebx = child;
        if (child != 0)
        {
            ebx = port_u32(&port, child, 0x158);
            port_call_with(&port, port_u32(&port, ebx, 0), child, 2, ebx, ecx, piece + count, piece,
                           ebp);
        }
        if (second != 0)
        {
            child = port_u32(&port, ecx, second);
            if (child != 0)
            {
                ebx = port_u32(&port, child, 0x158);
                port_call_with(&port, port_u32(&port, ebx, 0), child, 2, ebx, ecx, piece + count,
                               piece, ebp);
            }
        }
    }
    port_set32(&port, ebp, -0x28u, 0);
    if (second != 0)
    {
        result = port_call_with(&port, 0x4ac130, piece, 1, ebx, 0, piece + count, piece, ebp);
    }
    else
    {
        result = port_call_with(&port, 0x4ac130, piece, 1, ebx, piece + count, 0, piece, ebp);
    }
    edx = (vertrix_lift_edx & 0xffffff00u) | (flags & 0xff);
    port_set32(&port, ebp, -0x28u, 0);
    if ((flags & 2) != 0)
    {
        if (second != 0)
        {
            port_call_with(&port, 0x4ca050, result, edx, ebx, 0, piece + count, result, ebp);
        }
        else
        {
            port_call_with(&port, 0x4ca050, result, edx, ebx, piece + count, 0, result, ebp);
        }
        edx = vertrix_lift_edx;
    }
    return port_return(&port, result, edx);
}

/* Original 0x42ab10: methods 0x514774, guard 0x514730, 0x514790; seven children. */
uint32_t vertrix_port_piece_actor_destroy_full_42ab10(PORT_SIGNATURE)
{
    return piece_teardown(calls, services, globals, entry, 0x514774, 0x514730, 0x514790, 0x1c, 0);
}

/* Original 0x42b190: methods 0x514814, guard 0x5147b0, 0x514830; three pairs (+0x15c, +0x168). */
uint32_t vertrix_port_piece_pairs_destroy_42b190(PORT_SIGNATURE)
{
    return piece_teardown(calls, services, globals, entry, 0x514814, 0x5147b0, 0x514830, 0xc,
                          0x168);
}

/* Original 0x42bbd0: a block (0x160 bytes, 0x4ca000 and 0x42bb00) placed by 0x4adf20 (ecx among
 * its stack arguments) with the cell edx (0x4ac490), mode ebx (0x4ac7b0), the image of kind al
 * (0x544ac0, 28 bytes a kind; 0x4ac8d0) and the kind +0x15c. */
uint32_t vertrix_port_block_create_full_42bbd0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x14
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t block;
    uint32_t kind;
    uint32_t stack[5];
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set8(&port, ebp, -0xcu, entry->eax);
    port_set32(&port, ebp, -0x10u, entry->edx);
    block = port_call_with(&port, 0x4ca000, 0x160, entry->edx, entry->ebx, entry->ecx, entry->esi,
                           entry->ebx, ebp);
    if (block != 0)
    {
        block = port_call_with(&port, 0x42bb00, block, vertrix_lift_edx, entry->ebx, entry->ecx,
                               entry->esi, entry->ebx, ebp);
    }
    stack[0] = 0;
    stack[1] = 0;
    stack[2] = 0;
    stack[3] = entry->ecx;
    stack[4] = 0;
    call_frame(&port, 0x4adf20, block, 0, 0, 0, block, entry->ebx, ebp, stack, 5);
    port_call_with(&port, 0x4ac490, block, port_u32(&port, ebp, -0x10u), 0, 0, block, entry->ebx,
                   ebp);
    port_call_with(&port, 0x4ac7b0, block, entry->ebx, 0, 0, block, entry->ebx, ebp);
    kind = (uint32_t)(int32_t)(int8_t)port_u8(&port, ebp, -0xcu);
    port_call_with(&port, 0x4ac8d0, block, 0x544ac0 + kind * 0x1c, 0, 0, block, kind * 4, ebp);
    port_set8(&port, block, 0x15c, port_u8(&port, ebp, -0xcu));
    return port_return(&port, block, vertrix_lift_edx);
}

/* Original 0x42f030: whether the board's piece (+0xa60, at its x +0xe and y +0x16) touches a side:
 * 0x431ae0 gives its top and bottom rows and columns into the frame; along the row span a side
 * cell of the edge table 0x4f9ad8 (by the piece's kind ebx and turn edx) that is filled (+0x220,
 * or any on row 0) gives 1, otherwise 0. */
uint32_t vertrix_port_board_piece_touches_side_42f030(PORT_SIGNATURE)
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
    eax = board + (port_u32(&port, ebp, -0x28u) - 1) * 0x34 + edx * 4;
    do
    {
        if ((int32_t)edx >= 0)
        {
            uint32_t side = port_u8(&port, ecx, 0x4f9ad8);
            int32_t row = (int32_t)port_u32(&port, ebp, -0x28u);
            if (((row > 0 && port_u32(&port, eax, 0x220) != 0) || row == 0) && side != 0)
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

/* Original 0x429ee0: the rows of the choice grid with a chosen cell (+0x1cc 1; 0x425de0 clears
 * edx first) are listed in the frame, shuffled by ten rounds of swaps (0x4826c0 on 0x598d30) when
 * more than one, and the first bl of them (at most all) written to edx as dwords. 0 when none,
 * otherwise 1. */
uint32_t vertrix_port_choice_grid_pick_rows_429ee0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x28
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t grid = entry->eax;
    uint32_t out = entry->edx;
    uint32_t edi = entry->edi;
    uint32_t esi;
    uint32_t edx = 0;
    uint32_t count = 0;
    uint32_t row;
    uint32_t taken;
    uint32_t index;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, -0x18u, grid);
    port_set32(&port, ebp, -0x1cu, out);
    port_set8(&port, ebp, -0x10u, entry->ebx);
    port_call_with(&port, 0x425de0, out, out, 0, entry->ecx, grid, edi, ebp);
    port_set32(&port, ebp, -0x14u, 0);
    esi = grid + 0x10;
    for (row = 0; row < 7; row++)
    {
        uint32_t cell = grid + row * 0x10;
        uint32_t sum = 0;
        edx = esi;
        do
        {
            edi = port_u32(&port, cell, 0x1cc);
            if (edi == 1)
            {
                sum++;
            }
            cell += 4;
        } while (cell != edx);
        if (sum != 0)
        {
            count++;
            port_set8(&port, ebp + count, -0x25u, row);
        }
        port_set32(&port, ebp, -0x14u, row + 1);
        esi += 0x10;
    }
    if (count == 0)
    {
        return port_return(&port, 0, edx);
    }
    if (count > 1)
    {
        uint32_t round;
        port_set32(&port, ebp, -0x14u, 0);
        for (round = 0; round < 0xa; round++)
        {
            for (index = 0; index < count; index++)
            {
                uint32_t other = port_call_with(&port, 0x4826c0, 0x598d30, count & 0xffff, count,
                                                index, 0x598d30, edi, ebp) &
                                 0xffff;
                uint32_t first = port_u8(&port, ebp + other, -0x24u);
                uint32_t second = port_u8(&port, ebp + index, -0x24u);
                port_set8(&port, ebp + other, -0x24u, second);
                port_set8(&port, ebp + index, -0x24u, first);
            }
            edi = round + 1;
            port_set32(&port, ebp, -0x14u, edi);
        }
    }
    taken = port_u8(&port, ebp, -0x10u);
    port_set32(&port, ebp, -0x14u, count);
    if (taken < count)
    {
        port_set32(&port, ebp, -0x14u, taken);
    }
    taken = port_u32(&port, ebp, -0x14u);
    edx = taken;
    if (taken != 0)
    {
        edx = out;
        for (index = 0; index < taken; index++)
        {
            port_set32(&port, edx, 0, port_u8(&port, ebp + index, -0x24u));
            edx += 4;
        }
    }
    return port_return(&port, 1, edx);
}
