#include "matches.h"

/* The match's turn of a player. */

/* Original 0x452e00: the turn of the player eax against its opponent +0x3b0: its column +0x15c
 * on the opponent's board +0x15c; when the column cannot fall (0x438cd0) the player's turn ends
 * (0x43acd0 with ecx 1) and, once the column is drawn (its methods +0x158, the second), the
 * player is through (0x43bbf0); else the player's turn closes (0x43ab60 gives 1: 0x43ac00, else
 * 0x43acd0), the opponent is told 0x4f81ac (0x43c0e0), a filled board (0x4320c0 gives 1) that
 * takes the column (0x4330d0 gives 1) deals the column's three kinds to +0x3b4 for an opponent
 * with +0x170 1 (0x43a560, +0x170 cleared) and its next row (0x431d80 with 2, 0x42ee20); both
 * board and column take the state 0x44f040 (0x42eda0) and restart at 5 (0x42ee80), the column
 * is laid (0x433040), the opponent plays (0x43bb60), the board's +0xb80, +0xb84 and +0xb88 are
 * set and the opponent and player take the states 0x452050 and 0x452fc0 (0x4ac8f0) before the
 * column is drawn. The registers but eax kept. */
uint32_t vertrix_port_effect_board_match_452e00(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x2c
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t player = entry->eax;
    uint32_t opponent;
    uint32_t column;
    uint32_t board;
    uint32_t kinds;
    uint32_t methods;
    uint32_t through;
    uint32_t eax;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = player;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, -4u, entry->ebx);
    port_set32(&port, ebp, -8u, entry->ecx);
    port_set32(&port, ebp, -0xcu, entry->edx);
    port_set32(&port, ebp, -0x10u, entry->esi);
    port_set32(&port, ebp, -0x14u, entry->edi);
    port_set32(&port, ebp, -0x20u, player);
    column = port_u32(&port, player, 0x15c);
    port_set32(&port, ebp, -0x24u, 0);
    opponent = port_u32(&port, player, 0x3b0);
    port_set32(&port, ebp, -0x1cu, opponent);
    board = port_u32(&port, opponent, 0x15c);
    port_set32(&port, ebp, -0x28u, port_u32(&port, opponent, 0x3b4));
    if (port_call_with(&port, 0x438cd0, column, board, ebx, ecx, board, column, ebp) != 0)
    {
        ecx = 1;
        port_call_with(&port, 0x43acd0, player, vertrix_lift_edx, ebx, ecx, board, column, ebp);
        port_set32(&port, ebp, -0x24u, ecx);
    }
    else
    {
        if (port_call_with(&port, 0x43ab60, player, vertrix_lift_edx, ebx, ecx, board, column,
                           ebp) == 1)
        {
            port_call_with(&port, 0x43ac00, player, vertrix_lift_edx, ebx, ecx, board, column, ebp);
        }
        else
        {
            port_call_with(&port, 0x43acd0, player, vertrix_lift_edx, ebx, ecx, board, column, ebp);
        }
        port_call_with(&port, 0x43c0e0, opponent, port_u32(&port, 0, 0x4f81ac), ebx, ecx, board,
                       column, ebp);
        if (port_call_with(&port, 0x4320c0, board, vertrix_lift_edx, ebx, ecx, board, column,
                           ebp) == 1 &&
            port_call_with(&port, 0x4330d0, board, column, ebx, ecx, board, column, ebp) == 1)
        {
            if (port_u32(&port, opponent, 0x170) == 1)
            {
                kinds = port_u32(&port, board, 0xa60);
                port_set8(&port, ebp, -0x18u, port_u8(&port, port_u32(&port, kinds, 0x15c), 0x15c));
                ebx =
                    (uint32_t)(int32_t)(int8_t)port_u8(&port, port_u32(&port, kinds, 0x160), 0x15c);
                ecx =
                    (uint32_t)(int32_t)(int8_t)port_u8(&port, port_u32(&port, kinds, 0x164), 0x15c);
                port_call_with(&port, 0x43a560, port_u32(&port, ebp, -0x28u),
                               (uint32_t)(int32_t)(int8_t)port_u8(&port, ebp, -0x18u), ebx, ecx,
                               board, column, ebp);
                port_set32(&port, opponent, 0x170, 0);
            }
            port_call_with(&port, 0x431d80, board, 2, ebx, ecx, board, column, ebp);
            port_call_with(&port, 0x42ee20, board, vertrix_lift_edx, ebx, ecx, board, column, ebp);
        }
        port_call_with(&port, 0x42eda0, column, 0x44f040, ebx, ecx, board, column, ebp);
        port_call_with(&port, 0x42eda0, board, 0x44f040, ebx, ecx, board, column, ebp);
        port_call_with(&port, 0x42ee80, column, 5, ebx, ecx, board, column, ebp);
        port_call_with(&port, 0x42ee80, board, 5, ebx, ecx, board, column, ebp);
        port_call_with(&port, 0x433040, column, board, ebx, ecx, board, column, ebp);
        port_call_with(&port, 0x43bb60, opponent, vertrix_lift_edx, ebx, ecx, board, column, ebp);
        port_set32(&port, board, 0xb80, 1);
        port_set32(&port, board, 0xb84, 1);
        port_set32(&port, board, 0xb88, 1);
        port_call_with(&port, 0x4ac8f0, opponent, 0x452050, ebx, ecx, board, column, ebp);
        port_call_with(&port, 0x4ac8f0, player, 0x452fc0, ebx, ecx, board, column, ebp);
    }
    through = port_u32(&port, ebp, -0x24u);
    methods = port_u32(&port, column, 0x158);
    eax = port_call_with(&port, port_u32(&port, methods, 4), column, methods, ebx, ecx, through,
                         column, ebp);
    if (through == 1)
    {
        eax = port_call_with(&port, 0x43bbf0, player, vertrix_lift_edx, ebx, ecx, through, column,
                             ebp);
    }
    return port_return(&port, eax, entry->edx);
}

/* The column's kind at `slot` (0x431c10) is not a bomb (5). */
static uint32_t match_not_bomb(Port *port, uint32_t board, uint32_t slot, uint32_t ebx,
                               uint32_t ecx, uint32_t edi, uint32_t ebp)
{
    return port_call_with(port, 0x431c10, board, slot, ebx, ecx, board, edi, ebp) != 5;
}

/* Original 0x4550a0: the turn of the player eax on its own board +0x15c: with the board not
 * filled (0x4320c0) the next column's three kinds come from +0x3b4 (0x43a560); all bombs end the
 * opponent +0x3b0's turn (0x43acd0 with ecx 1), else the player marks which are not bombs
 * (+0x4d0, +0x4d4, +0x4d8), takes the state 0x455320, the opponent's turn closes (0x43ac00) and
 * the player is told 0x4f81ac (0x43c0e0). Filled, the player is told (0x43bad0); a column of
 * three bombs (0x431c10) ends the opponent's turn likewise; else a lost board (0x431d60) takes the
 * state 0x4552b0, a board not lost marks the column's non-bombs and takes 0x4553a0, and the board
 * is cleared (0x4368e0 of 5), the opponent's turn closes and the player is told 0x4f81ac. The
 * board is drawn (its methods +0x158, the second) and, with the opponent's turn ended, the player
 * is through (0x43bbf0) and the board's +0xb90 cleared. The registers but eax kept. */
uint32_t vertrix_port_player_own_turn_4550a0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x30
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t player = entry->eax;
    uint32_t board;
    uint32_t opponent;
    uint32_t methods;
    uint32_t state;
    uint32_t eax;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = player;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, -4u, entry->ebx);
    port_set32(&port, ebp, -8u, entry->ecx);
    port_set32(&port, ebp, -0xcu, entry->edx);
    port_set32(&port, ebp, -0x10u, entry->esi);
    port_set32(&port, ebp, -0x14u, entry->edi);
    board = port_u32(&port, player, 0x15c);
    port_set32(&port, ebp, -0x2cu, port_u32(&port, player, 0x3b4));
    opponent = port_u32(&port, player, 0x3b0);
    port_set32(&port, ebp, -0x24u, opponent);
    port_set32(&port, ebp, -0x28u, 0);
    if (port_call_with(&port, 0x4320c0, board, 0, ebx, ecx, board, player, ebp) != 1)
    {
        ebx = ebp - 0x18;
        ecx = ebp - 0x20;
        port_call_with(&port, 0x43a5b0, port_u32(&port, ebp, -0x2cu), ebp - 0x1c, ebx, ecx, board,
                       player, ebp);
        if (port_u8(&port, ebp, -0x1cu) == 5 && port_u8(&port, ebp, -0x18u) == 5 &&
            port_u8(&port, ebp, -0x20u) == 5)
        {
            ecx = 1;
            port_call_with(&port, 0x43acd0, opponent, vertrix_lift_edx, ebx, ecx, board, player,
                           ebp);
            port_set32(&port, ebp, -0x28u, ecx);
        }
        else
        {
            port_set32(&port, player, 0x4d0, port_u8(&port, ebp, -0x1cu) != 5);
            port_set32(&port, player, 0x4d4, port_u8(&port, ebp, -0x18u) != 5);
            port_set32(&port, player, 0x4d8, port_u8(&port, ebp, -0x20u) != 5);
            port_call_with(&port, 0x4ac8f0, player, 0x455320, ebx, ecx, board, player, ebp);
            port_call_with(&port, 0x43ac00, opponent, vertrix_lift_edx, ebx, ecx, board, player,
                           ebp);
            port_call_with(&port, 0x43c0e0, player, port_u32(&port, 0, 0x4f81ac), ebx, ecx, board,
                           player, ebp);
        }
    }
    else
    {
        port_call_with(&port, 0x43bad0, player, vertrix_lift_edx, ebx, ecx, board, player, ebp);
        if (!match_not_bomb(&port, board, 0, ebx, ecx, player, ebp) &&
            !match_not_bomb(&port, board, 1, ebx, ecx, player, ebp) &&
            !match_not_bomb(&port, board, 2, ebx, ecx, player, ebp))
        {
            ebx = 1;
            port_call_with(&port, 0x43acd0, opponent, vertrix_lift_edx, ebx, ecx, board, player,
                           ebp);
            port_set32(&port, ebp, -0x28u, ebx);
        }
        else
        {
            if (port_call_with(&port, 0x431d60, board, vertrix_lift_edx, ebx, ecx, board, player,
                               ebp) != 0)
            {
                state = 0x4552b0;
            }
            else
            {
                port_set32(&port, player, 0x4d0,
                           match_not_bomb(&port, board, 0, ebx, ecx, player, ebp));
                port_set32(&port, player, 0x4d4,
                           match_not_bomb(&port, board, 1, ebx, ecx, player, ebp));
                port_set32(&port, player, 0x4d8,
                           match_not_bomb(&port, board, 2, ebx, ecx, player, ebp));
                state = 0x4553a0;
            }
            port_call_with(&port, 0x4ac8f0, player, state, ebx, ecx, board, player, ebp);
            ebx = 5;
            ecx = 5;
            port_call_with(&port, 0x4368e0, board, 5, ebx, ecx, board, player, ebp);
            port_call_with(&port, 0x43ac00, opponent, vertrix_lift_edx, ebx, ecx, board, player,
                           ebp);
            port_call_with(&port, 0x43c0e0, player, port_u32(&port, 0, 0x4f81ac), ebx, ecx, board,
                           player, ebp);
        }
    }
    methods = port_u32(&port, board, 0x158);
    eax = port_call_with(&port, port_u32(&port, methods, 4), board, methods, ebx, ecx, board,
                         player, ebp);
    if (port_u32(&port, ebp, -0x28u) == 1)
    {
        eax =
            port_call_with(&port, 0x43bbf0, player, vertrix_lift_edx, ebx, ecx, board, player, ebp);
        port_set32(&port, board, 0xb90, 0);
    }
    return port_return(&port, eax, entry->edx);
}
