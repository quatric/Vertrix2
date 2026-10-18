#include "combines.h"

/* Player states that settle both boards, combine and apply effects, copy speeds and attacks. */

/* A call handing the callee esi, edi and ebp as given and `count` stack dwords. */
static uint32_t call_frame(Port *port, uint32_t target, uint32_t eax, uint32_t edx, uint32_t ebx,
                           uint32_t ecx, uint32_t esi, uint32_t edi, uint32_t ebp,
                           const uint32_t *stack, unsigned count)
{
    return port_call_registers(port, target, eax, edx, ebx, ecx, esi, edi, ebp, stack, count);
}

/* The board's method +4 (its draw) with the registers given. */
static uint32_t board_draw(Port *port, uint32_t board, uint32_t edx, uint32_t ebx, uint32_t ecx,
                           uint32_t esi, uint32_t edi, uint32_t ebp)
{
    uint32_t methods = port_u32(port, board, 0x158);
    return port_call_with(port, port_u32(port, methods, 4), board, edx, ebx, ecx, esi, edi, ebp);
}

/* Original 0x452fc0: once both boards (the player's +0x15c and the opponent's) take the state
 * 0x44c860 (0x42eca0), 0x432c00 joins them, both +0xb8c are 1 and the player takes 0x453050.
 * Then the board draws. */
uint32_t vertrix_port_player_boards_join_452fc0(PORT_SIGNATURE)
{
    Port port;
    uint32_t player = entry->eax;
    uint32_t board;
    uint32_t other;
    uint32_t methods;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    board = port_u32(&port, player, 0x15c);
    other = port_u32(&port, port_u32(&port, player, 0x3b0), 0x15c);
    if (port_forward_esi(&port, entry, 0x42eca0, board, 0x44c860, player, board, other) != 0 &&
        port_forward_esi(&port, entry, 0x42eca0, other, 0x44c860, player, board, other) != 0)
    {
        port_forward_esi(&port, entry, 0x432c00, board, other, player, board, other);
        port_set32(&port, board, 0xb8c, 1);
        port_set32(&port, other, 0xb8c, 1);
        port_forward_esi(&port, entry, 0x4ac8f0, player, 0x453050, player, board, other);
    }
    methods = port_u32(&port, board, 0x158);
    result = port_forward_esi(&port, entry, port_u32(&port, methods, 4), board, vertrix_lift_edx,
                              methods, board, other);
    return port_return(&port, result, entry->edx);
}

/* Original 0x453280: once both boards take and keep the state 0x44c860 (0x42eca0, 0x42ecc0), both
 * restart (0x42ebe0, the opponent's with 0x453320) and the player takes the state 0x42ebe0
 * leaves. Then the board draws. */
uint32_t vertrix_port_player_boards_restart_453280(PORT_SIGNATURE)
{
    Port port;
    uint32_t player = entry->eax;
    uint32_t board;
    uint32_t other;
    uint32_t methods;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    board = port_u32(&port, player, 0x15c);
    other = port_u32(&port, port_u32(&port, player, 0x3b0), 0x15c);
    if (port_forward_esi(&port, entry, 0x42eca0, board, 0x44c860, other, board, player) != 0 &&
        port_forward_esi(&port, entry, 0x42ecc0, board, 0x44c860, other, board, player) != 0 &&
        port_forward_esi(&port, entry, 0x42eca0, other, 0x44c860, other, board, player) != 0 &&
        port_forward_esi(&port, entry, 0x42ecc0, other, 0x44c860, other, board, player) != 0)
    {
        port_forward_esi(&port, entry, 0x42ebe0, board, vertrix_lift_edx, other, board, player);
        port_forward_esi(&port, entry, 0x42ebe0, other, 0x453320, other, board, player);
        port_forward_esi(&port, entry, 0x4ac8f0, player, vertrix_lift_edx, other, board, player);
    }
    methods = port_u32(&port, board, 0x158);
    result = port_forward_esi(&port, entry, port_u32(&port, methods, 4), board, vertrix_lift_edx,
                              methods, board, player);
    return port_return(&port, result, entry->edx);
}

/* Original 0x453320: the opponent takes the sound 0x4f81ac (0x43c0e0); both boards mark the
 * player's kind +0x3dc (0x436aa0) and 0x436d80 combines them with +0x43c and +0x440; the player
 * takes the state 0x4533b0 and its board draws. */
uint32_t vertrix_port_state_combine_453320(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x1c
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t player = entry->eax;
    uint32_t opponent;
    uint32_t board;
    uint32_t kind;
    uint32_t pushed[1];
    uint32_t result;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    opponent = port_u32(&port, player, 0x3b0);
    port_set32(&port, ebp, -0x18u, port_u32(&port, opponent, 0x15c));
    board = port_u32(&port, player, 0x15c);
    call_frame(&port, 0x43c0e0, opponent, port_u32(&port, 0, 0x4f81ac), entry->ebx, entry->ecx,
               player, board, ebp, NULL, 0);
    call_frame(&port, 0x436aa0, board, port_u32(&port, player, 0x3dc), entry->ebx, entry->ecx,
               player, board, ebp, NULL, 0);
    call_frame(&port, 0x436aa0, port_u32(&port, ebp, -0x18u), port_u32(&port, player, 0x3dc),
               entry->ebx, entry->ecx, player, board, ebp, NULL, 0);
    kind = port_u32(&port, player, 0x3dc);
    pushed[0] = port_u32(&port, player, 0x440);
    call_frame(&port, 0x436d80, board, port_u32(&port, ebp, -0x18u), kind,
               port_u32(&port, player, 0x43c), player, board, ebp, pushed, 1);
    call_frame(&port, 0x4ac8f0, player, 0x4533b0, kind, port_u32(&port, player, 0x43c), player,
               board, ebp, NULL, 0);
    result = board_draw(&port, board, port_u32(&port, board, 0x158), kind,
                        port_u32(&port, player, 0x43c), player, board, ebp);
    return port_return(&port, result, entry->edx);
}

/* Original 0x4534e0: once the board takes and keeps the state 0x44c860 (0x42eca0, 0x42ecc0) and
 * 0x4371b0 starts its marked cells of +0x3e0, the player takes the state 0x453570 and the sound
 * 0x4f8194; when none start the view is set up again (0x43bbf0) after the board draws. */
uint32_t vertrix_port_effect_stone_apply_4534e0(PORT_SIGNATURE)
{
    Port port;
    uint32_t player = entry->eax;
    uint32_t board;
    uint32_t again = 0;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    board = port_u32(&port, player, 0x15c);
    if (port_call_with(&port, 0x42eca0, board, 0x44c860, player, board, player, 0, entry->ebp) !=
            0 &&
        port_call_with(&port, 0x42ecc0, board, 0x44c860, player, board, player, 0, entry->ebp) != 0)
    {
        if (port_call_with(&port, 0x4371b0, board, port_u32(&port, player, 0x3e0), player, board,
                           player, 0, entry->ebp) == 1)
        {
            port_call_with(&port, 0x4ac8f0, player, 0x453570, player, board, player, 0, entry->ebp);
            port_call_with(&port, 0x43c0e0, player, port_u32(&port, 0, 0x4f8194), player, board,
                           player, 0, entry->ebp);
        }
        else
        {
            again = 1;
        }
    }
    result = board_draw(&port, board, port_u32(&port, board, 0x158), player, board, player, again,
                        entry->ebp);
    if (again == 1)
    {
        result = port_call_with(&port, 0x43bbf0, player, vertrix_lift_edx, player, board, player,
                                again, entry->ebp);
    }
    return port_return(&port, result, entry->edx);
}

/* The attacks 0x453c00, 0x453f40 and 0x454250: the player gains (0x43ac00); the opponent
 * (+0x3b0) is struck (0x43bb60 with 4, 0x43bae0), takes the state `next` and the value `from`
 * of the player at `to` (with +4 cleared); the opponent's board redraws everything (+0xb80,
 * +0xb84, +0xb88 1); the player's board draws and its view is set up again (0x43bbf0). */
static uint32_t effect_attack(PORT_SIGNATURE, uint32_t next, uint32_t from, uint32_t to)
{
    Port port;
    uint32_t player = entry->eax;
    uint32_t opponent;
    uint32_t board;
    uint32_t other;
    uint32_t methods;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    opponent = port_u32(&port, player, 0x3b0);
    board = port_u32(&port, player, 0x15c);
    other = port_u32(&port, opponent, 0x15c);
    port_call_with(&port, 0x43ac00, player, entry->edx, player, opponent, board, other, entry->ebp);
    port_call_with(&port, 0x43bb60, opponent, 4, player, opponent, board, other, entry->ebp);
    port_call_with(&port, 0x43bae0, opponent, vertrix_lift_edx, player, opponent, board, other,
                   entry->ebp);
    port_call_with(&port, 0x4ac8f0, opponent, next, player, opponent, board, other, entry->ebp);
    port_set32(&port, opponent, to + 4, 0);
    port_set32(&port, opponent, to, port_u32(&port, player, from));
    port_set32(&port, other, 0xb80, 1);
    port_set32(&port, other, 0xb84, 1);
    port_set32(&port, other, 0xb88, 1);
    methods = port_u32(&port, board, 0x158);
    board_draw(&port, board, vertrix_lift_edx, player, methods, board, other, entry->ebp);
    result = port_call_with(&port, 0x43bbf0, player, vertrix_lift_edx, player, methods, board,
                            other, entry->ebp);
    return port_return(&port, result, entry->edx);
}

/* Original 0x453c00: the state 0x453c90 and +0x3cc into +0x424. */
uint32_t vertrix_port_effect_copy_speed_453c00(PORT_SIGNATURE)
{
    return effect_attack(calls, services, globals, entry, 0x453c90, 0x3cc, 0x424);
}

/* Original 0x453f40: the state 0x453fd0 and +0x3d0 into +0x42c. */
uint32_t vertrix_port_effect_attack_453f40(PORT_SIGNATURE)
{
    return effect_attack(calls, services, globals, entry, 0x453fd0, 0x3d0, 0x42c);
}

/* Original 0x454250: the state 0x4542e0 and +0x3d0 into +0x42c. */
uint32_t vertrix_port_effect_attack_454250(PORT_SIGNATURE)
{
    return effect_attack(calls, services, globals, entry, 0x4542e0, 0x3d0, 0x42c);
}

/* Original 0x454560: as the attacks with 0x43ce00 first and, after the strike, 0x43baf0 with 1
 * and 0x43b860 with 0; the state 0x454600 and +0x3e8 into +0x3ec. */
uint32_t vertrix_port_effect_attack_454560(PORT_SIGNATURE)
{
    Port port;
    uint32_t player = entry->eax;
    uint32_t opponent;
    uint32_t board;
    uint32_t other;
    uint32_t methods;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    opponent = port_u32(&port, player, 0x3b0);
    board = port_u32(&port, player, 0x15c);
    other = port_u32(&port, opponent, 0x15c);
    port_call_with(&port, 0x43ac00, player, entry->edx, player, opponent, board, other, entry->ebp);
    port_call_with(&port, 0x43ce00, opponent, vertrix_lift_edx, player, opponent, board, other,
                   entry->ebp);
    port_call_with(&port, 0x43bb60, opponent, 4, player, opponent, board, other, entry->ebp);
    port_call_with(&port, 0x43bae0, opponent, vertrix_lift_edx, player, opponent, board, other,
                   entry->ebp);
    port_call_with(&port, 0x43baf0, opponent, 1, player, opponent, board, other, entry->ebp);
    port_call_with(&port, 0x43b860, opponent, 0, player, opponent, board, other, entry->ebp);
    port_call_with(&port, 0x4ac8f0, opponent, 0x454600, player, opponent, board, other, entry->ebp);
    port_set32(&port, opponent, 0x3ec, port_u32(&port, player, 0x3e8));
    port_set32(&port, other, 0xb80, 1);
    port_set32(&port, other, 0xb84, 1);
    port_set32(&port, other, 0xb88, 1);
    methods = port_u32(&port, board, 0x158);
    board_draw(&port, board, vertrix_lift_edx, player, methods, board, other, entry->ebp);
    result = port_call_with(&port, 0x43bbf0, player, vertrix_lift_edx, player, methods, board,
                            other, entry->ebp);
    return port_return(&port, result, entry->edx);
}

/* Original 0x454600: the struck player's board takes the speed 0x4f7c84 by 0x532bbc (0x4ac7b0)
 * and the player 0x43b930 with 0x4f7c90 (20 a level, by +0x3ec); +0x448 0, the board's +0x64 0,
 * +0x68 4 and +0x6c 1, the sound 0x4f8194, 0x438960 with the byte +0x3ec, the state 0x4546a0 and
 * the board draws. */
uint32_t vertrix_port_effect_struck_start_454600(PORT_SIGNATURE)
{
    Port port;
    uint32_t player = entry->eax;
    uint32_t board;
    uint32_t level;
    uint32_t methods;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    board = port_u32(&port, player, 0x15c);
    port_forward(&port, entry, 0x4ac7b0, board,
                 port_u32(&port, port_u32(&port, 0, 0x532bbc) * 4, 0x4f7c84), board, player);
    level = port_u32(&port, 0, 0x532bbc);
    port_forward(&port, entry, 0x43b930, player,
                 port_u32(&port, level * 0x14 + port_u32(&port, player, 0x3ec) * 4, 0x4f7c90),
                 board, player);
    port_set32(&port, player, 0x448, 0);
    port_set32(&port, board, 0x64, 0);
    port_set32(&port, board, 0x68, 4);
    port_set32(&port, board, 0x6c, 1);
    port_forward(&port, entry, 0x43c0e0, player, port_u32(&port, 0, 0x4f8194), board, player);
    port_forward(&port, entry, 0x438960, board, port_u8(&port, player, 0x3ec), board, player);
    port_forward(&port, entry, 0x4ac8f0, player, 0x4546a0, board, player);
    methods = port_u32(&port, board, 0x158);
    result = port_forward(&port, entry, port_u32(&port, methods, 4), board, methods, board, player);
    return port_return(&port, result, entry->edx);
}

/* Original 0x4548e0: on each beat of the board's timer it restarts it and, for each tick of the
 * beat while 0x436150 gives 1, the player takes the sound 0x4f8190; when the ticks ran out early
 * the player takes the state 0x454970. Then the board draws. */
uint32_t vertrix_port_effect_struck_ticks_4548e0(PORT_SIGNATURE)
{
    Port port;
    uint32_t player = entry->eax;
    uint32_t board;
    uint32_t ecx = entry->ecx;
    uint32_t methods;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    board = port_u32(&port, player, 0x15c);
    port_forward_esi(&port, entry, 0x4ac500, board, entry->edx, board, ecx, player);
    if (port_forward_esi(&port, entry, 0x4ac520, board, vertrix_lift_edx, board, ecx, player) == 1)
    {
        uint32_t edx;
        ecx = port_forward_esi(&port, entry, 0x4ac540, board, vertrix_lift_edx, board, ecx, player);
        port_forward_esi(&port, entry, 0x4ac5b0, board, ecx, board, ecx, player);
        edx = vertrix_lift_edx;
        if (edx != 0)
        {
            do
            {
                if (port_forward_esi(&port, entry, 0x436150, board, edx, board, ecx, player) != 1)
                {
                    break;
                }
                ecx--;
                port_forward_esi(&port, entry, 0x43c0e0, player, port_u32(&port, 0, 0x4f8190),
                                 board, ecx, player);
                edx = vertrix_lift_edx;
            } while (ecx != 0);
        }
        if (ecx != 0)
        {
            port_forward_esi(&port, entry, 0x4ac8f0, player, 0x454970, board, ecx, player);
        }
    }
    methods = port_u32(&port, board, 0x158);
    result = port_forward_esi(&port, entry, port_u32(&port, methods, 4), board, methods, board, ecx,
                              player);
    return port_return(&port, result, entry->edx);
}

/* The board restarts 0x455700, 0x455970 and 0x455a90: once the board takes and keeps the state
 * 0x44c860 (0x42eca0, 0x42ecc0) it restarts (0x42ebe0, after 0x42ebc0 when `stop`); after the
 * board draws, the player's view is set up again (0x43bbf0 with 0x452160), it takes the state
 * that leaves, 0x43bae0 with 1, +0x184 0 and the board's +0xb8c 0. */
static uint32_t effect_board_restart(PORT_SIGNATURE, int stop)
{
    Port port;
    uint32_t player = entry->eax;
    uint32_t board;
    uint32_t done = 0;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    board = port_u32(&port, player, 0x15c);
    if (port_forward_esi(&port, entry, 0x42eca0, board, 0x44c860, player, board, 0) != 0 &&
        port_forward_esi(&port, entry, 0x42ecc0, board, 0x44c860, player, board, 0) != 0)
    {
        if (stop)
        {
            port_forward_esi(&port, entry, 0x42ebc0, board, vertrix_lift_edx, player, board, 0);
        }
        done = 1;
        port_forward_esi(&port, entry, 0x42ebe0, board, vertrix_lift_edx, player, board, done);
    }
    result = port_forward_esi(&port, entry, port_u32(&port, port_u32(&port, board, 0x158), 4),
                              board, port_u32(&port, board, 0x158), player, board, done);
    if (done != 1)
    {
        return port_return(&port, result, entry->edx);
    }
    port_forward_esi(&port, entry, 0x43bbf0, player, 0x452160, player, board, done);
    port_forward_esi(&port, entry, 0x4ac8f0, player, vertrix_lift_edx, player, board, done);
    result = port_forward_esi(&port, entry, 0x43bae0, player, done, player, board, done);
    port_set32(&port, player, 0x184, 0);
    port_set32(&port, board, 0xb8c, 0);
    return port_return(&port, result, entry->edx);
}

/* Original 0x455700. */
uint32_t vertrix_port_effect_board_restart_455700(PORT_SIGNATURE)
{
    return effect_board_restart(calls, services, globals, entry, 0);
}

/* Original 0x455970: as 0x455700. */
uint32_t vertrix_port_effect_board_restart_455970(PORT_SIGNATURE)
{
    return effect_board_restart(calls, services, globals, entry, 0);
}

/* Original 0x455a90: with 0x42ebc0 first. */
uint32_t vertrix_port_effect_board_restart_455a90(PORT_SIGNATURE)
{
    return effect_board_restart(calls, services, globals, entry, 1);
}

/* Original 0x455790: the board checks its binds (0x4375a0, 0x4378c0): bound, the player takes the
 * sounds 0x4f8184 and 0x4f81b0, the state 0x455830, the board the speed 0x4f7c78 by 0x532bbc
 * (0x4ac7b0), 0x4ac510 and +0xb8c 1; otherwise the player 0x43acd0. After the board draws, the
 * unbound player's view is set up again (0x43bbf0). */
uint32_t vertrix_port_effect_check_bind_455790(PORT_SIGNATURE)
{
    Port port;
    uint32_t player = entry->eax;
    uint32_t board;
    uint32_t again = 0;
    uint32_t result;
    uint32_t ebp = entry->ebp;
    port_open(&port, calls, services, globals, entry);
    board = port_u32(&port, player, 0x15c);
    port_call_with(&port, 0x4375a0, board, entry->edx, player, board, player, entry->edi, ebp);
    if (port_call_with(&port, 0x4378c0, board, vertrix_lift_edx, player, board, player, 0, ebp) !=
        1)
    {
        again = 1;
        port_call_with(&port, 0x43acd0, player, vertrix_lift_edx, player, board, player, again,
                       ebp);
    }
    else
    {
        port_call_with(&port, 0x43c0e0, player, port_u32(&port, 0, 0x4f8184), player, board, player,
                       0, ebp);
        port_call_with(&port, 0x43c0e0, player, port_u32(&port, 0, 0x4f81b0), player, board, player,
                       0, ebp);
        port_call_with(&port, 0x4ac8f0, player, 0x455830, player, board, player, 0, ebp);
        port_call_with(&port, 0x4ac7b0, board,
                       port_u32(&port, port_u32(&port, 0, 0x532bbc) * 4, 0x4f7c78), player, board,
                       player, 0, ebp);
        port_call_with(&port, 0x4ac510, board, vertrix_lift_edx, player, board, player, 0, ebp);
        port_set32(&port, board, 0xb8c, 1);
    }
    result =
        board_draw(&port, board, port_u32(&port, board, 0x158), player, board, player, again, ebp);
    if (again == 1)
    {
        result = port_call_with(&port, 0x43bbf0, player, vertrix_lift_edx, player, board, player,
                                again, ebp);
    }
    return port_return(&port, result, entry->edx);
}

/* The effect checks 0x455b90 and 0x455d10: the board marks (`mark` with 0) and checks (`check`):
 * when it holds, the player takes the state `next` and the sound 0x4f81ac, the board's +0xb8c
 * is 1 and the opponent (+0x3b0) gains (0x43ac00); otherwise the opponent 0x43acd0. The board
 * draws (with ebx 1 when it failed, else the edx `mark` left) and on 1 the view is set up again
 * (0x43bbf0). */
static uint32_t effect_check(PORT_SIGNATURE, uint32_t mark, uint32_t check, uint32_t next)
{
    enum
    {
        BELOW = 0x1c
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t player = entry->eax;
    uint32_t board;
    uint32_t opponent;
    uint32_t ecx = player;
    uint32_t ebx;
    uint32_t methods;
    uint32_t result;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    board = port_u32(&port, player, 0x15c);
    opponent = port_u32(&port, player, 0x3b0);
    port_call_with(&port, mark, board, 0, board, player, opponent, player, ebp);
    port_set32(&port, ebp, -0x18u, vertrix_lift_edx);
    if (port_call_with(&port, check, board, vertrix_lift_edx, board, player, opponent, player,
                       ebp) == 1)
    {
        port_call_with(&port, 0x4ac8f0, player, next, board, player, opponent, player, ebp);
        port_call_with(&port, 0x43c0e0, player, port_u32(&port, 0, 0x4f81ac), board, player,
                       opponent, player, ebp);
        port_set32(&port, board, 0xb8c, 1);
        port_call_with(&port, 0x43ac00, opponent, vertrix_lift_edx, board, player, opponent, player,
                       ebp);
    }
    else
    {
        ecx = 1;
        port_call_with(&port, 0x43acd0, opponent, vertrix_lift_edx, board, ecx, opponent, player,
                       ebp);
        port_set32(&port, ebp, -0x18u, ecx);
    }
    methods = port_u32(&port, board, 0x158);
    ebx = port_u32(&port, ebp, -0x18u);
    result = port_call_with(&port, port_u32(&port, methods, 4), board, methods, ebx, ecx, opponent,
                            player, ebp);
    if (ebx == 1)
    {
        result = port_call_with(&port, 0x43bbf0, player, vertrix_lift_edx, ebx, ecx, opponent,
                                player, ebp);
    }
    return port_return(&port, result, entry->edx);
}

/* Original 0x455b90: 0x437f60 and 0x437fe0, then 0x455c30. */
uint32_t vertrix_port_effect_check_455b90(PORT_SIGNATURE)
{
    return effect_check(calls, services, globals, entry, 0x437f60, 0x437fe0, 0x455c30);
}

/* Original 0x455d10: 0x4383f0 and 0x438540, then 0x455db0. */
uint32_t vertrix_port_effect_check_455d10(PORT_SIGNATURE)
{
    return effect_check(calls, services, globals, entry, 0x4383f0, 0x438540, 0x455db0);
}

/* Original 0x456f10: on each beat of the fader's timer it restarts it with 100 (+0x5c) and the
 * step 2 (+0x60) and, once 0x4ad6e0 gives 0, its state is cleared; the music (0x478b40) and
 * sound (0x4828f0) volumes 0x532b98 and 0x532b9c are scaled by 100 less +0x58 percent. */
uint32_t vertrix_port_volume_fade_update_456f10(PORT_SIGNATURE)
{
    Port port;
    uint32_t actor = entry->eax;
    uint32_t result;
    uint32_t share;
    uint32_t value;
    port_open(&port, calls, services, globals, entry);
    port_forward(&port, entry, 0x4ac500, actor, entry->edx, entry->ebx, actor);
    result = port_forward(&port, entry, 0x4ac520, actor, vertrix_lift_edx, entry->ebx, actor);
    if (result != 1)
    {
        return port_return(&port, result, entry->edx);
    }
    result = port_forward(&port, entry, 0x4ac540, actor, vertrix_lift_edx, entry->ebx, actor);
    port_forward(&port, entry, 0x4ac5b0, actor, result, entry->ebx, actor);
    port_set32(&port, actor, 0x5c, 0x64);
    port_set32(&port, actor, 0x60, 2);
    if (port_forward(&port, entry, 0x4ad6e0, actor, vertrix_lift_edx, entry->ebx, actor) == 0)
    {
        port_forward(&port, entry, 0x4ac8f0, actor, 0, entry->ebx, actor);
    }
    share = 0x64 - port_u32(&port, actor, 0x58);
    value = port_u32(&port, 0, 0x532b98) * share;
    port_forward(&port, entry, 0x478b40, value / 0x64, value % 0x64, 0x64, share);
    value = port_u32(&port, 0, 0x532b9c) * share;
    result = port_forward(&port, entry, 0x4828f0, value / 0x64, value % 0x64, 0x64, share);
    return port_return(&port, result, entry->edx);
}

/* Original 0x457770: a key pressed (0x476530 on 0x54d640) is taken back (0x476320); in a game
 * (0x532b3c or 0x532b38) the key 0x61 sets the delay 0x532a58 to 0x4f7bd8 and any other key, as
 * any key with 0x53d944 set, to 0x4f7bd4. On each beat of the actor's timer it restarts it and the
 * delay is 0x4f7bd8. */
uint32_t vertrix_port_key_delay_update_457770(PORT_SIGNATURE)
{
    Port port;
    uint32_t actor = entry->eax;
    uint32_t key;
    uint32_t edx;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    key = port_forward(&port, entry, 0x476530, 0x54d640, 0, entry->ebx, actor);
    edx = key;
    if ((key & 0xffff) != 0)
    {
        int playing = port_u32(&port, 0, 0x532b3c) == 1 || port_u32(&port, 0, 0x532b38) == 1;
        if (playing && (key & 0xffff) == 0x61)
        {
            port_set32(&port, 0, 0x532a58, port_u32(&port, 0, 0x4f7bd8));
        }
        else if (port_u32(&port, 0, 0x53d944) == 1 || playing)
        {
            port_set32(&port, 0, 0x532a58, port_u32(&port, 0, 0x4f7bd4));
        }
        port_forward(&port, entry, 0x476320, 0x54d640, key & 0xffff, entry->ebx, actor);
        edx = vertrix_lift_edx;
    }
    port_forward(&port, entry, 0x4ac500, actor, edx, entry->ebx, actor);
    result = port_forward(&port, entry, 0x4ac520, actor, vertrix_lift_edx, entry->ebx, actor);
    if (result != 1)
    {
        return port_return(&port, result, entry->edx);
    }
    port_forward(&port, entry, 0x4ac540, actor, vertrix_lift_edx, entry->ebx, actor);
    port_forward(&port, entry, 0x4ac5b0, actor, vertrix_lift_edx, entry->ebx, actor);
    result = port_u32(&port, 0, 0x4f7bd8);
    port_set32(&port, 0, 0x532a58, result);
    return port_return(&port, result, entry->edx);
}

/* Original 0x457b70: on each beat of the actor's timer it restarts it and moves from its home
 * (+8, +0xa) by 0x4aca60 and 0x4acab0, which then becomes its home; once 0x4ad530 gives 0 it
 * takes 0 (+0x4a), the step 1 (+0x4c) and the state 0x457c10. Then 0x457890. */
uint32_t vertrix_port_actor_drift_update_457b70(PORT_SIGNATURE)
{
    Port port;
    uint32_t actor = entry->eax;
    uint32_t time;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    port_forward(&port, entry, 0x4ac500, actor, entry->edx, entry->ebx, actor);
    if (port_forward(&port, entry, 0x4ac520, actor, vertrix_lift_edx, entry->ebx, actor) != 1)
    {
        result = port_forward(&port, entry, 0x457890, actor, vertrix_lift_edx, entry->ebx, actor);
        return port_return(&port, result, entry->edx);
    }
    time = port_forward(&port, entry, 0x4ac540, actor, vertrix_lift_edx, entry->ebx, actor);
    port_forward(&port, entry, 0x4ac5b0, actor, vertrix_lift_edx, time, actor);
    port_set16(&port, actor, 0xe, port_u16(&port, actor, 8));
    port_set16(&port, actor, 0x16, port_u16(&port, actor, 0xa));
    port_forward(&port, entry, 0x4aca60, actor, time, time, actor);
    port_forward(&port, entry, 0x4acab0, actor, time, time, actor);
    port_set16(&port, actor, 8, port_u16(&port, actor, 0xe));
    port_set16(&port, actor, 0xa, port_u16(&port, actor, 0x16));
    if (port_forward(&port, entry, 0x4ad530, actor, time, time, actor) == 0)
    {
        port_set16(&port, actor, 0x4a, 0);
        port_set16(&port, actor, 0x4c, 1);
        port_forward(&port, entry, 0x4ac8f0, actor, 0x457c10, time, actor);
    }
    result = port_forward(&port, entry, 0x457890, actor, vertrix_lift_edx, time, actor);
    return port_return(&port, result, entry->edx);
}

/* Original 0x458330: 0x457810 and 0x457890 on the actor, then its timer steps (0x4ac500,
 * 0x4ac520; at a beat 0x4ac540 and 0x4ac5b0), all on the edx each leaves. */
uint32_t vertrix_port_actor_tick_458330(PORT_SIGNATURE)
{
    Port port;
    uint32_t actor = entry->eax;
    uint32_t edx;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    port_forward(&port, entry, 0x457810, actor, actor, entry->ebx, entry->ecx);
    edx = vertrix_lift_edx;
    port_forward(&port, entry, 0x457890, edx, edx, entry->ebx, entry->ecx);
    edx = vertrix_lift_edx;
    port_forward(&port, entry, 0x4ac500, edx, edx, entry->ebx, entry->ecx);
    edx = vertrix_lift_edx;
    result = port_forward(&port, entry, 0x4ac520, edx, edx, entry->ebx, entry->ecx);
    if (result == 1)
    {
        edx = vertrix_lift_edx;
        port_forward(&port, entry, 0x4ac540, edx, edx, entry->ebx, entry->ecx);
        edx = vertrix_lift_edx;
        result = port_forward(&port, entry, 0x4ac5b0, edx, edx, entry->ebx, entry->ecx);
    }
    return port_return(&port, result, entry->edx);
}

/* Original 0x458710: 0x457810, +0xc 0, and on each beat of the actor's timer it restarts it;
 * once 0x4acc10 gives 0 it takes 0x4ac7d0 with 0x14, the state 0x458260, +0x93 0 and the speeds
 * 0 (+0x48), 100 (+0x4a) and the step 5 (+0x4c). Then 0x457890. */
uint32_t vertrix_port_actor_rise_update_458710(PORT_SIGNATURE)
{
    Port port;
    uint32_t actor = entry->eax;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    port_forward(&port, entry, 0x457810, actor, entry->edx, entry->ebx, actor);
    port_set16(&port, actor, 0xc, 0);
    port_forward(&port, entry, 0x4ac500, actor, vertrix_lift_edx, entry->ebx, actor);
    if (port_forward(&port, entry, 0x4ac520, actor, vertrix_lift_edx, entry->ebx, actor) == 1)
    {
        result = port_forward(&port, entry, 0x4ac540, actor, vertrix_lift_edx, entry->ebx, actor);
        port_forward(&port, entry, 0x4ac5b0, actor, result, entry->ebx, actor);
        if (port_forward(&port, entry, 0x4acc10, actor, vertrix_lift_edx, entry->ebx, actor) == 0)
        {
            port_forward(&port, entry, 0x4ac7d0, actor, 0x14, entry->ebx, actor);
            port_forward(&port, entry, 0x4ac8f0, actor, 0x458260, entry->ebx, actor);
            port_set8(&port, actor, 0x93, 0);
            port_set16(&port, actor, 0x48, 0);
            port_set16(&port, actor, 0x4a, 0x64);
            port_set16(&port, actor, 0x4c, 5);
        }
    }
    result = port_forward(&port, entry, 0x457890, actor, vertrix_lift_edx, entry->ebx, actor);
    return port_return(&port, result, entry->edx);
}

/* Original 0x4589e0: the spark starts at its place (0x4ad510 with 1 on the signed words +8 and
 * +0xa), +0x24 0, +0x28 a speed of 3 to 10 (0x4826c0 on 0x598d30 with 8), +0x64 0, +0x68 and +0x6c
 * 1, 0x4ac7d0 with 10, 0x4ac510, the speeds 0 (+0x48), 0x96 (+0x4a), the step 1 (+0x4c) and the
 * state 0x458a70. */
uint32_t vertrix_port_spark_start_4589e0(PORT_SIGNATURE)
{
    Port port;
    uint32_t actor = entry->eax;
    uint32_t x;
    uint32_t y;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    y = (uint32_t)(int32_t)(int16_t)port_u16(&port, actor, 0xa);
    x = (uint32_t)(int32_t)(int16_t)port_u16(&port, actor, 8);
    port_forward_esi(&port, entry, 0x4ad510, actor, 1, x, y, actor);
    port_set16(&port, actor, 0x24, 0);
    result = port_forward_esi(&port, entry, 0x4826c0, 0x598d30, 8, x, y, actor);
    port_set32(&port, actor, 0x64, 0);
    port_set32(&port, actor, 0x68, 1);
    port_set16(&port, actor, 0x28, result + 3);
    port_set32(&port, actor, 0x6c, 1);
    port_forward_esi(&port, entry, 0x4ac7d0, actor, 0xa, x, y, actor);
    port_forward_esi(&port, entry, 0x4ac510, actor, vertrix_lift_edx, x, y, actor);
    port_set16(&port, actor, 0x48, 0);
    port_set16(&port, actor, 0x4a, 0x96);
    port_set16(&port, actor, 0x4c, 1);
    result = port_forward_esi(&port, entry, 0x4ac8f0, actor, 0x458a70, x, y, actor);
    return port_return(&port, result, entry->edx);
}

/* Original 0x459200: the bird flies in toward 0x2b2 (from the right half, past 0x140) or -50
 * (+0x10) at the row 0x1c7 (+0x18) with the steps 1 (+0x1a) and 6 (+0x12): 0x4ac7d0 with 10,
 * 0x4ac510, +0x64 0, +0x68 4, +0x6c 1, +0x70 0, +0x74 2, +0x78 1, the frame 0 and step 1 and the
 * state 0x459290. */
uint32_t vertrix_port_bird_start_459200(PORT_SIGNATURE)
{
    Port port;
    uint32_t actor = entry->eax;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    port_set16(&port, actor, 0x18, 0x1c7);
    port_set16(&port, actor, 0x1a, 1);
    port_set16(&port, actor, 0x10,
               (int32_t)(int16_t)port_u16(&port, actor, 8) > 0x140 ? 0x2b2 : 0xffce);
    port_set16(&port, actor, 0x12, 6);
    port_forward(&port, entry, 0x4ac7d0, actor, 0xa, entry->ebx, actor);
    port_forward(&port, entry, 0x4ac510, actor, vertrix_lift_edx, entry->ebx, actor);
    port_set32(&port, actor, 0x64, 0);
    port_set32(&port, actor, 0x68, 4);
    port_set32(&port, actor, 0x6c, 1);
    port_set32(&port, actor, 0x70, 0);
    port_set32(&port, actor, 0x74, 2);
    port_set32(&port, actor, 0x78, 1);
    port_set8(&port, actor, 0x45, 0);
    port_set16(&port, actor, 0x46, 1);
    result = port_forward(&port, entry, 0x4ac8f0, actor, 0x459290, entry->ebx, actor);
    return port_return(&port, result, entry->edx);
}

/* Original 0x459950: the fade 100 and step 1 (+0x4f, +0x50); on each beat of the actor's timer it
 * restarts it and, once 0x4ad580 gives 0, takes the state 0x459900. */
uint32_t vertrix_port_actor_fade_in_459950(PORT_SIGNATURE)
{
    Port port;
    uint32_t actor = entry->eax;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    port_set8(&port, actor, 0x4f, 0x64);
    port_set16(&port, actor, 0x50, 1);
    port_forward(&port, entry, 0x4ac500, actor, entry->edx, entry->ebx, actor);
    result = port_forward(&port, entry, 0x4ac520, actor, vertrix_lift_edx, entry->ebx, actor);
    if (result != 1)
    {
        return port_return(&port, result, entry->edx);
    }
    result = port_forward(&port, entry, 0x4ac540, actor, vertrix_lift_edx, entry->ebx, actor);
    port_forward(&port, entry, 0x4ac5b0, actor, result, entry->ebx, actor);
    result = port_forward(&port, entry, 0x4ad580, actor, vertrix_lift_edx, entry->ebx, actor);
    if (result != 0)
    {
        return port_return(&port, result, entry->edx);
    }
    result = port_forward(&port, entry, 0x4ac8f0, actor, 0x459900, entry->ebx, actor);
    return port_return(&port, result, entry->edx);
}

/* Original 0x45abd0: the actor's frame (0x4ac510) and 0x4ac380; when its player (+4, 0x540f88)
 * has a message (0x43d300 gives 1) 0x43d370 gives its picture, place and sound: a picture is
 * shown (0x4ac490, 0x4ac8d0, 0x4ac700, 0x4ac4a0, 0x4ac8a0, 0x4adfe0 with 0x45ac70, 0x4ac8f0); then
 * 0x43c110 with the sound. */
uint32_t vertrix_port_player_message_show_45abd0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x24
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t actor = entry->eax;
    uint32_t player;
    uint32_t ebx = ebp - 0x1c;
    uint32_t ecx = ebp - 0x18;
    uint32_t result;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    player = port_u32(&port, port_u32(&port, actor, 4) * 4, 0x540f88);
    port_call_with(&port, 0x4ac510, actor, entry->edx, entry->ebx, entry->ecx, actor, player, ebp);
    port_call_with(&port, 0x4ac380, actor, vertrix_lift_edx, entry->ebx, entry->ecx, actor, player,
                   ebp);
    result = port_call_with(&port, 0x43d300, player, vertrix_lift_edx, entry->ebx, entry->ecx,
                            actor, player, ebp);
    if (result != 1)
    {
        return port_return(&port, result, entry->edx);
    }
    port_call_with(&port, 0x43d370, player, ebp - 0x20, ebx, ecx, actor, player, ebp);
    if (port_u32(&port, ebp, -0x20u) != 0)
    {
        port_call_with(&port, 0x4ac490, actor, port_u32(&port, ebp, -0x18u), ebx, ecx, actor,
                       player, ebp);
        port_call_with(&port, 0x4ac8d0, actor, port_u32(&port, ebp, -0x20u), ebx, ecx, actor,
                       player, ebp);
        port_call_with(&port, 0x4ac700, actor, vertrix_lift_edx, ebx, ecx, actor, player, ebp);
        port_call_with(&port, 0x4ac4a0, actor, vertrix_lift_edx, ebx, ecx, actor, player, ebp);
        port_call_with(&port, 0x4ac8a0, actor, vertrix_lift_edx, ebx, ecx, actor, player, ebp);
        port_call_with(&port, 0x4adfe0, actor, 0x45ac70, ebx, ecx, actor, player, ebp);
        port_call_with(&port, 0x4ac8f0, actor, vertrix_lift_edx, ebx, ecx, actor, player, ebp);
    }
    result = port_call_with(&port, 0x43c110, player, port_u32(&port, ebp, -0x1cu), ebx, ecx, actor,
                            player, ebp);
    return port_return(&port, result, entry->edx);
}
