#include "picks.h"

/* The computer player's piece pick, the board's line check, and the palette channel tables. */

static uint32_t call_frame(Port *port, uint32_t target, uint32_t eax, uint32_t edx, uint32_t ebx,
                           uint32_t ecx, uint32_t esi, uint32_t edi, uint32_t ebp,
                           const uint32_t *stack, unsigned count)
{
    return port_call_registers(port, target, eax, edx, ebx, ecx, esi, edi, ebp, stack, count);
}

/* Original 0x45aab0: the actor eax's pick for its player (0x540f88 by +4): when due (0x4ac500,
 * 0x4ac520, 0x4ac540, 0x4ac5b0) and the player free (0x43d300 of 0), a piece of its level +0x488
 * is chosen: of the kind 0x43ab80 (0x417fc0 counts, 0x4826c0 on 0x598d30 picks, 0x418000 finds)
 * or any (0x418050, 0x4180a0); the player takes it (0x43d330 with the table 0x544f90 entry of
 * 280 bytes a level and 28 a piece, speed 0x4f81cc) and the actor the state 0x45aa70. */
uint32_t vertrix_port_actor_player_pick_45aab0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x24
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t actor = entry->eax;
    uint32_t player;
    uint32_t level;
    uint32_t kind;
    uint32_t count;
    uint32_t ebx = entry->ebx;
    uint32_t eax;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_call_with(&port, 0x4ac500, actor, entry->edx, ebx, entry->ecx, actor, entry->edi, ebp);
    eax = port_call_with(&port, 0x4ac520, actor, vertrix_lift_edx, ebx, entry->ecx, actor,
                         entry->edi, ebp);
    if (eax != 1)
    {
        return port_return(&port, eax, entry->edx);
    }
    port_call_with(&port, 0x4ac540, actor, vertrix_lift_edx, ebx, entry->ecx, actor, entry->edi,
                   ebp);
    port_call_with(&port, 0x4ac5b0, actor, vertrix_lift_edx, ebx, entry->ecx, actor, entry->edi,
                   ebp);
    player = port_u32(&port, 0, 0x540f88 + port_u32(&port, actor, 4) * 4);
    level = port_u32(&port, player, 0x488);
    eax = port_call_with(&port, 0x43d300, player, vertrix_lift_edx, ebx, level, actor, player, ebp);
    port_set32(&port, ebp, -0x20u, level);
    if (eax != 0)
    {
        return port_return(&port, eax, entry->edx);
    }
    kind =
        port_call_with(&port, 0x43ab80, player, vertrix_lift_edx, ebx, level, actor, player, ebp);
    port_set32(&port, ebp, -0x1cu, kind);
    count = port_call_with(&port, 0x417fc0, level, kind, ebx, level, actor, player, ebp);
    port_set32(&port, ebp, -0x18u, count);
    if (count != 0)
    {
        eax =
            port_call_with(&port, 0x4826c0, 0x598d30, count & 0xffff, 0, level, actor, player, ebp);
        ebx = port_call_with(&port, 0x418000, level, port_u32(&port, ebp, -0x1cu), eax & 0xffff,
                             level, actor, player, ebp);
    }
    else
    {
        count = port_call_with(&port, 0x418050, level, vertrix_lift_edx, ebx, level, actor, player,
                               ebp);
        port_set32(&port, ebp, -0x18u, count);
        eax = count;
        if (count != 0)
        {
            eax = port_call_with(&port, 0x4826c0, 0x598d30, count & 0xffff, ebx, level, actor,
                                 player, ebp);
            ebx = port_call_with(&port, 0x4180a0, level, eax & 0xffff, ebx, level, actor, player,
                                 ebp);
        }
    }
    if (port_u32(&port, ebp, -0x18u) == 0)
    {
        return port_return(&port, eax, entry->edx);
    }
    level = port_u32(&port, ebp, -0x20u);
    port_call_with(&port, 0x43d330, player, 0x544f90 + level * 280 + ebx * 28,
                   port_u32(&port, 0, 0x4f81cc), 0, actor, player, ebp);
    eax = port_call_with(&port, 0x4ac8f0, actor, 0x45aa70, port_u32(&port, 0, 0x4f81cc), 0, actor,
                         player, ebp);
    return port_return(&port, eax, entry->edx);
}

/* Original 0x45b5f0: the player eax's board +0x15c line check: when due the board moves (0x4ac500,
 * 0x4ac520, 0x4ac540, 0x4ac5b0); once its pieces have settled (0x42ec80, 0x42eca0 with 0x44c860)
 * it is filled (0x439190) and a line of the kind +0x400 at +0x420 (0x438d50) counts on: the
 * board's speed of the level 0x532bbc (0x4f7d2c; 0x4ac7b0), +0x58 cleared, stepped (0x4ac510),
 * the fullest row marked (0x438dd0), 0x4f81ac scored (0x43c0e0) and the player in the state
 * 0x45b590, or 0x45b5f0 again when the board is done (0x439080); without a line the player steps
 * (0x43bbf0) after the board's method +4. */
uint32_t vertrix_port_player_line_check_45b5f0(PORT_SIGNATURE)
{
    Port port;
    uint32_t player = entry->eax;
    uint32_t board;
    uint32_t ebx = entry->ebx;
    uint32_t edi = 0;
    uint32_t methods;
    uint32_t eax;
    port_open(&port, calls, services, globals, entry);
    board = port_u32(&port, player, 0x15c);
    port_call_with(&port, 0x4ac500, board, entry->edx, ebx, board, player, entry->edi, entry->ebp);
    if (port_call_with(&port, 0x4ac520, board, vertrix_lift_edx, ebx, board, player, 0,
                       entry->ebp) == 1)
    {
        port_call_with(&port, 0x4ac540, board, vertrix_lift_edx, ebx, board, player, 0, entry->ebp);
        port_call_with(&port, 0x4ac5b0, board, vertrix_lift_edx, ebx, board, player, 0, entry->ebp);
    }
    if (port_call_with(&port, 0x42ec80, board, 0x44c860, ebx, board, player, 0, entry->ebp) != 0 &&
        port_call_with(&port, 0x42eca0, board, 0x44c860, ebx, board, player, 0, entry->ebp) != 0)
    {
        port_call_with(&port, 0x439190, board, vertrix_lift_edx, ebx, board, player, 0, entry->ebp);
        ebx = port_u32(&port, player, 0x400);
        eax = port_call_with(&port, 0x438d50, board, port_u32(&port, player, 0x420), ebx, board,
                             player, 0, entry->ebp);
        if (eax != 1)
        {
            edi = 1;
        }
        else
        {
            ebx = port_u32(&port, player, 0x420) + eax;
            port_set32(&port, player, 0x420, ebx);
            port_call_with(&port, 0x4ac7b0, board,
                           port_u32(&port, 0, 0x4f7d2c + port_u32(&port, 0, 0x532bbc) * 4), ebx,
                           board, player, 0, entry->ebp);
            port_set32(&port, board, 0x58, 0);
            port_call_with(&port, 0x4ac510, board, vertrix_lift_edx, ebx, board, player, 0,
                           entry->ebp);
            port_call_with(&port, 0x438dd0, board, vertrix_lift_edx, ebx, board, player, 0,
                           entry->ebp);
            port_call_with(&port, 0x43c0e0, player, port_u32(&port, 0, 0x4f81ac), ebx, board,
                           player, 0, entry->ebp);
            port_call_with(&port, 0x4ac8f0, player, 0x45b590, ebx, board, player, 0, entry->ebp);
            if (port_call_with(&port, 0x439080, board, vertrix_lift_edx, ebx, board, player, 0,
                               entry->ebp) == 1)
            {
                port_call_with(&port, 0x4ac8f0, player, 0x45b5f0, ebx, board, player, 0,
                               entry->ebp);
            }
        }
    }
    methods = port_u32(&port, board, 0x158);
    eax = port_call_with(&port, port_u32(&port, methods, 4), board, methods, ebx, board, player,
                         edi, entry->ebp);
    if (edi == 1)
    {
        eax = port_call_with(&port, 0x43bbf0, player, vertrix_lift_edx, ebx, board, player, edi,
                             entry->ebp);
    }
    return port_return(&port, eax, entry->edx);
}

/* Original 0x474cd0: the palette channel tables: under a guard record the 201 by 101 table
 * 0x5468b0 is cleared to 0xff, its first 101 rows filled by 0x474910 for each pair, the
 * diagonals of rows 100 to 200 given the colours 0x549024, and the 765 words 0x54c1d4 cleared.
 * The guard record's chain. */
uint32_t vertrix_port_palette_channels_474cd0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x48
    };
    Port port;
    uint8_t stack[BELOW + 8];
    uint32_t ebp = entry->esp - 4;
    uint32_t row;
    uint32_t column;
    uint32_t args[2];
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, -0x44u, port.env.chain);
    port_set32(&port, ebp, -0x40u, 0x4ec1ec);
    port_set32(&port, ebp, -0x3cu, 0x516410);
    port_set32(&port, ebp, -0x38u, 0);
    for (row = 0; row < 0xc9; ++row)
    {
        for (column = 0; column < 0x65; ++column)
        {
            port_set8(&port, 0, 0x5468b0 + row * 0x65 + column, 0xff);
        }
    }
    for (row = 0; row < 0x65; ++row)
    {
        port_set32(&port, ebp, -0x1cu, row);
        port_set32(&port, ebp, -0x24u, 0);
        for (column = 0; column < 0x65; ++column)
        {
            args[0] = ebp - 0x18;
            args[1] = ebp - 0x20;
            call_frame(&port, 0x474910, 0, column, row, ebp - 0x28, column, row * 0x65, ebp, args,
                       2);
            port_set8(&port, 0, 0x5468b0 + row * 0x65 + column, port_u8(&port, ebp, -0x18u));
            port_set32(&port, ebp, -0x24u, column + 1);
        }
    }
    port_set32(&port, ebp, -0x1cu, 0x65);
    for (row = 0; row < 0x65; ++row)
    {
        uint32_t colour = port_u8(&port, 0, 0x549024 + row);
        for (column = 0; column < 0x65 - row; ++column)
        {
            port_set8(&port, 0, 0x5468b0 + (column + 100) * 0x65 + row + column, colour);
        }
    }
    for (row = 0; row < 0x2fd; ++row)
    {
        port_set32(&port, 0, 0x54c1d4 + row * 4, 0);
    }
    return port_return(&port, port_u32(&port, ebp, -0x44u), entry->edx);
}
