#include "port_states.h"

/* Player state, hold, attack and effect handlers. */

/* A call handing the callee esi and edi as given and the caller's own ebp. */
static uint32_t call_all(Port *port, const LiftEntry *entry, uint32_t target, uint32_t eax,
                         uint32_t edx, uint32_t ebx, uint32_t ecx, uint32_t esi, uint32_t edi)
{
    return port_call_with(port, target, eax, edx, ebx, ecx, esi, edi, entry->ebp);
}

/* Method +4 of the board `board` (its table at +0x158), the table in edx. */
static uint32_t board_method(Port *port, const LiftEntry *entry, uint32_t board, uint32_t ebx,
                             uint32_t ecx, uint32_t esi, uint32_t edi)
{
    uint32_t methods = port_u32(port, board, 0x158);
    return call_all(port, entry, port_u32(port, methods, 4), board, methods, ebx, ecx, esi, edi);
}

/* Original 0x450cd0: when due, the number's owner (the edx the step calls leave) grows from its
 * +0x180 by five times what 0x4ac540 gave, up to its player's (+4, 0x540f88) +0x174, by 0x4b58a0
 * and 0x4adfe0; nothing once it is there. */
uint32_t vertrix_port_number_owner_grow_450cd0(PORT_SIGNATURE)
{
    Port port;
    uint32_t actor = entry->eax;
    uint32_t amount;
    uint32_t owner;
    uint32_t player;
    uint32_t value;
    uint32_t limit;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    port_forward(&port, entry, 0x4ac500, actor, actor, entry->ebx, actor);
    result =
        port_forward(&port, entry, 0x4ac520, vertrix_lift_edx, vertrix_lift_edx, entry->ebx, actor);
    if (result != 1)
    {
        return port_return(&port, result, entry->edx);
    }
    amount =
        port_forward(&port, entry, 0x4ac540, vertrix_lift_edx, vertrix_lift_edx, entry->ebx, actor);
    port_forward_esi(&port, entry, 0x4ac5b0, vertrix_lift_edx, vertrix_lift_edx, entry->ebx, actor,
                     amount);
    owner = vertrix_lift_edx;
    player = port_u32(&port, port_u32(&port, owner, 4) * 4, 0x540f88);
    value = port_u32(&port, owner, 0x180);
    limit = port_u32(&port, player, 0x174);
    if (value >= limit)
    {
        return port_return(&port, player, entry->edx);
    }
    value += amount * 5;
    if (value > limit)
    {
        value = limit;
    }
    port_forward_esi(&port, entry, 0x4b58a0, actor, value, limit, actor, amount);
    result =
        port_forward_esi(&port, entry, 0x4adfe0, actor, vertrix_lift_edx, limit, actor, amount);
    return port_return(&port, result, entry->edx);
}

/* Original 0x450df0: once the first player (0x540f8c) is on (+0x4c5) and 0x43d3b0 gives 1:
 * 0x4ac510, 0x4ac7b0 with the level's (0x532bbc) entry of 0x4f7ccc, dwords +0x58 0, +0x5c the
 * player's choice (+0x4e4) of the level's three at 0x4f7cd8 and +0x60 1, and the next handler
 * 0x450e70. */
uint32_t vertrix_port_actor_level_start_450df0(PORT_SIGNATURE)
{
    Port port;
    uint32_t actor = entry->eax;
    uint32_t player;
    uint32_t on;
    uint32_t level;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    player = port_u32(&port, 0, 0x540f8c);
    on = port_u8(&port, player, 0x4c5);
    if (on == 0)
    {
        return port_return(&port, actor & 0xffffff00u, entry->edx);
    }
    result = port_forward(&port, entry, 0x43d3b0, player, entry->edx, player, actor);
    if (result != 1)
    {
        return port_return(&port, result, entry->edx);
    }
    port_forward(&port, entry, 0x4ac510, actor, vertrix_lift_edx, player, actor);
    port_forward(&port, entry, 0x4ac7b0, actor,
                 port_u32(&port, port_u32(&port, 0, 0x532bbc) * 4, 0x4f7ccc), player, actor);
    level = port_u32(&port, 0, 0x532bbc);
    port_set32(&port, actor, 0x58, 0);
    port_set32(&port, actor, 0x5c,
               port_u32(&port, level * 12 + port_u32(&port, player, 0x4e4) * 4, 0x4f7cd8));
    port_set32(&port, actor, 0x60, 1);
    result = port_forward(&port, entry, 0x4ac8f0, actor, 0x450e70, player, actor);
    return port_return(&port, result, entry->edx);
}

/* Original 0x450f80: 0 while the owner (+0x3b0) is on (+0x4c5); otherwise the next handler
 * 0x4513d0, and 0x43bb00 with 0 (when the owner's +0x464 is 1, or the actor is on, then with its
 * +0x464 1); 0x532a3c 1, and 1. */
uint32_t vertrix_port_object_start_hold_450f80(PORT_SIGNATURE)
{
    Port port;
    uint32_t actor = entry->eax;
    uint32_t owner;
    port_open(&port, calls, services, globals, entry);
    owner = port_u32(&port, actor, 0x3b0);
    if (port_u8(&port, owner, 0x4c5) != 0)
    {
        return port_return(&port, 0, entry->edx);
    }
    if (port_u32(&port, owner, 0x464) == 1)
    {
        port_forward(&port, entry, 0x4ac8f0, actor, 0x4513d0, entry->ebx, actor);
        port_forward(&port, entry, 0x43bb00, actor, 0, entry->ebx, actor);
    }
    else
    {
        port_forward(&port, entry, 0x4ac8f0, actor, 0x4513d0, entry->ebx, actor);
        if (port_u8(&port, actor, 0x4c5) != 0)
        {
            port_set32(&port, actor, 0x464, 1);
            port_forward(&port, entry, 0x43bb00, actor, 0, entry->ebx, actor);
        }
    }
    port_set32(&port, 0, 0x532a3c, 1);
    return port_return(&port, 1, entry->edx);
}

/* Original 0x451c00: when 0x429ee0 (on +0x3b8 with +0x46c and the byte +0x470) gives 1, 0x432160
 * places the piece on the board (+0x15c) with the signed byte +0x190, +0x17c and +0x46c, then the
 * next handler 0x451c80 and 0x43ad50; otherwise the next handler 0x450ff0 and 0x43bae0 with 0. */
uint32_t vertrix_port_player_place_piece_451c00(PORT_SIGNATURE)
{
    Port port;
    uint32_t actor = entry->eax;
    uint32_t board;
    uint32_t kind;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    kind = port_u8(&port, actor, 0x470);
    board = port_u32(&port, actor, 0x15c);
    result = call_all(&port, entry, 0x429ee0, port_u32(&port, actor, 0x3b8),
                      port_u32(&port, actor, 0x46c), kind, entry->ecx, actor, board);
    if (result == 1)
    {
        uint32_t ebx = port_u32(&port, actor, 0x17c);
        uint32_t ecx = port_u32(&port, actor, 0x46c);
        call_all(&port, entry, 0x432160, board,
                 (uint32_t)(int32_t)(int8_t)port_u8(&port, actor, 0x190), ebx, ecx, actor, board);
        call_all(&port, entry, 0x4ac8f0, actor, 0x451c80, ebx, ecx, actor, board);
        result = call_all(&port, entry, 0x43ad50, actor, vertrix_lift_edx, ebx, ecx, actor, board);
        return port_return(&port, result, entry->edx);
    }
    call_all(&port, entry, 0x4ac8f0, actor, 0x450ff0, kind, entry->ecx, actor, board);
    result = call_all(&port, entry, 0x43bae0, actor, 0, kind, entry->ecx, actor, board);
    return port_return(&port, result, entry->edx);
}

/* Original 0x4520f0: unless the board (+0x15c) has a type one block (0x432280) or 0x4334b0 holds,
 * when 0x42ec80 with 0 holds: 0x432200, 0x42eee0, 0x42ec60 with 0x452160 and the handler left;
 * method +4 of the board (the table in ebx) either way. */
uint32_t vertrix_port_player_board_settle_4520f0(PORT_SIGNATURE)
{
    Port port;
    uint32_t actor = entry->eax;
    uint32_t board;
    uint32_t methods;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    board = port_u32(&port, actor, 0x15c);
    if (port_forward(&port, entry, 0x432280, board, entry->edx, actor, board) == 0 &&
        port_forward(&port, entry, 0x4334b0, board, vertrix_lift_edx, actor, board) == 0 &&
        port_forward(&port, entry, 0x42ec80, board, 0, actor, board) != 0)
    {
        port_forward(&port, entry, 0x432200, board, vertrix_lift_edx, actor, board);
        port_forward(&port, entry, 0x42eee0, board, vertrix_lift_edx, actor, board);
        port_forward(&port, entry, 0x42ec60, board, 0x452160, actor, board);
        port_forward(&port, entry, 0x4ac8f0, actor, vertrix_lift_edx, actor, board);
    }
    methods = port_u32(&port, board, 0x158);
    result = port_forward(&port, entry, port_u32(&port, methods, 4), board, vertrix_lift_edx,
                          methods, board);
    return port_return(&port, result, entry->edx);
}

/* Original 0x452250: the next handler 0x450ff0 and 0x43bae0 with 0; when the owner (+0x3b0) is on
 * (+0x4c5) and +0x188 is set: 0x43bb60, dwords +0x3f0 +0x188 and +0x3f4 0, 0x43bae0 with 4 and
 * the next handler 0x4522c0. */
uint32_t vertrix_port_object_arm_hold_452250(PORT_SIGNATURE)
{
    Port port;
    uint32_t actor = entry->eax;
    uint32_t owner;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    owner = port_u32(&port, actor, 0x3b0);
    port_forward(&port, entry, 0x4ac8f0, actor, 0x450ff0, owner, actor);
    result = port_forward(&port, entry, 0x43bae0, actor, 0, owner, actor);
    if (port_u8(&port, owner, 0x4c5) == 0)
    {
        return port_return(&port, result & 0xffffff00u, entry->edx);
    }
    result = port_u32(&port, actor, 0x188);
    if (result == 0)
    {
        return port_return(&port, result, entry->edx);
    }
    port_forward(&port, entry, 0x43bb60, actor, vertrix_lift_edx, owner, actor);
    port_set32(&port, actor, 0x3f0, port_u32(&port, actor, 0x188));
    port_set32(&port, actor, 0x3f4, 0);
    port_forward(&port, entry, 0x43bae0, actor, 4, owner, actor);
    result = port_forward(&port, entry, 0x4ac8f0, actor, 0x4522c0, owner, actor);
    return port_return(&port, result, entry->edx);
}

/* Original 0x4523d0: the owner's (+0x3b0) +0x428 and the actor's +0x444 0, the owner's board's
 * (+0x15c) +0xb80, +0xb84 and +0xb88 1, the next handler 0x452440, and method +4 of both
 * boards. */
uint32_t vertrix_port_player_hold_release_4523d0(PORT_SIGNATURE)
{
    Port port;
    uint32_t actor = entry->eax;
    uint32_t owner;
    uint32_t board;
    uint32_t other;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    owner = port_u32(&port, actor, 0x3b0);
    board = port_u32(&port, actor, 0x15c);
    port_set32(&port, owner, 0x428, 0);
    other = port_u32(&port, owner, 0x15c);
    port_set32(&port, actor, 0x444, 0);
    port_set32(&port, other, 0xb80, 1);
    port_set32(&port, other, 0xb84, 1);
    port_set32(&port, other, 0xb88, 1);
    port_forward(&port, entry, 0x4ac8f0, actor, 0x452440, board, other);
    board_method(&port, entry, board, board, other, entry->esi, entry->edi);
    result = board_method(&port, entry, other, board, other, entry->esi, entry->edi);
    return port_return(&port, result, entry->edx);
}

/* Original 0x4528e0: when 0x43b7c0 on the owner (+0x3b0) gives 1, 0x43c0e0 with 0x4f8194 when
 * the owner's +0x17c (as it was) is above its +0x17c now (the edx left) and then 0x43acd0, or
 * with 0x4f8198 and 0x43ac00; otherwise 0x43acd0. Then method +4 of the board (+0x15c) and
 * 0x43bbf0. */
uint32_t vertrix_port_effect_progress_gate_4528e0(PORT_SIGNATURE)
{
    Port port;
    uint32_t actor = entry->eax;
    uint32_t owner;
    uint32_t board;
    uint32_t before;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    owner = port_u32(&port, actor, 0x3b0);
    board = port_u32(&port, actor, 0x15c);
    before = port_u32(&port, owner, 0x17c);
    result = call_all(&port, entry, 0x43b7c0, owner, owner, board, actor, actor, before);
    if (result == 1 && before <= port_u32(&port, vertrix_lift_edx, 0x17c))
    {
        call_all(&port, entry, 0x43c0e0, actor, port_u32(&port, 0, 0x4f8198), board, actor, actor,
                 before);
        call_all(&port, entry, 0x43ac00, actor, vertrix_lift_edx, board, actor, actor, before);
    }
    else
    {
        if (result == 1)
        {
            call_all(&port, entry, 0x43c0e0, actor, port_u32(&port, 0, 0x4f8194), board, actor,
                     actor, before);
        }
        call_all(&port, entry, 0x43acd0, actor, vertrix_lift_edx, board, actor, actor, before);
    }
    board_method(&port, entry, board, board, actor, actor, before);
    result = call_all(&port, entry, 0x43bbf0, actor, vertrix_lift_edx, board, actor, actor, before);
    return port_return(&port, result, entry->edx);
}

/* The checks of 0x453460, 0x4554a0 and 0x455600: `prepare` on the board (+0x15c); when `check`
 * (with the actor's `field`, or the edx left when 0) holds, 0x43c0e0 with 0x4f81ac and the next
 * handler `next`, otherwise 0x43acd0; method +4 of the board, and 0x43bbf0 in the second case. */
static uint32_t effect_check(PORT_SIGNATURE, uint32_t prepare, uint32_t check, uint32_t field,
                             uint32_t next)
{
    Port port;
    uint32_t actor = entry->eax;
    uint32_t board;
    uint32_t armed;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    board = port_u32(&port, actor, 0x15c);
    call_all(&port, entry, prepare, board, entry->edx, board, actor, actor, entry->edi);
    if (call_all(&port, entry, check, board,
                 field != 0 ? port_u32(&port, actor, field) : vertrix_lift_edx, board, actor, actor,
                 0) == 1)
    {
        armed = 0;
        call_all(&port, entry, 0x43c0e0, actor, port_u32(&port, 0, 0x4f81ac), board, actor, actor,
                 armed);
        call_all(&port, entry, 0x4ac8f0, actor, next, board, actor, actor, armed);
    }
    else
    {
        armed = 1;
        call_all(&port, entry, 0x43acd0, actor, vertrix_lift_edx, board, actor, actor, armed);
    }
    result = board_method(&port, entry, board, board, actor, actor, armed);
    if (armed == 1)
    {
        result =
            call_all(&port, entry, 0x43bbf0, actor, vertrix_lift_edx, board, actor, actor, armed);
    }
    return port_return(&port, result, entry->edx);
}

/* Original 0x453460: 0x436fe0, 0x437060 with +0x3e0, next 0x4534e0. */
uint32_t vertrix_port_effect_stone_arm_453460(PORT_SIGNATURE)
{
    return effect_check(calls, services, globals, entry, 0x436fe0, 0x437060, 0x3e0, 0x4534e0);
}

/* Original 0x4554a0: 0x4372c0, 0x437350, next 0x455510. */
uint32_t vertrix_port_effect_check_bind_4554a0(PORT_SIGNATURE)
{
    return effect_check(calls, services, globals, entry, 0x4372c0, 0x437350, 0, 0x455510);
}

/* Original 0x455600: 0x437240, 0x437350, next 0x455510. */
uint32_t vertrix_port_effect_check_bind_455600(PORT_SIGNATURE)
{
    return effect_check(calls, services, globals, entry, 0x437240, 0x437350, 0, 0x455510);
}

/* Original 0x453b90: 0x43acd0 when 0x43d3b0 gives 1; otherwise 0x43c0e0 with 0x4f818c and
 * 0x43ccf0 on the actor and its owner (+0x3b0) with +0x3f8. Then method +4 of the board (+0x15c)
 * and 0x43bbf0. */
uint32_t vertrix_port_effect_pair_sound_453b90(PORT_SIGNATURE)
{
    Port port;
    uint32_t actor = entry->eax;
    uint32_t owner;
    uint32_t board;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    owner = port_u32(&port, actor, 0x3b0);
    board = port_u32(&port, actor, 0x15c);
    if (call_all(&port, entry, 0x43d3b0, actor, entry->edx, board, actor, actor, owner) == 1)
    {
        call_all(&port, entry, 0x43acd0, actor, vertrix_lift_edx, board, actor, actor, owner);
    }
    else
    {
        call_all(&port, entry, 0x43c0e0, actor, port_u32(&port, 0, 0x4f818c), board, actor, actor,
                 owner);
        call_all(&port, entry, 0x43ccf0, actor, port_u32(&port, actor, 0x3f8), board, actor, actor,
                 owner);
        call_all(&port, entry, 0x43ccf0, owner, port_u32(&port, actor, 0x3f8), board, actor, actor,
                 owner);
    }
    board_method(&port, entry, board, board, actor, actor, owner);
    result = call_all(&port, entry, 0x43bbf0, actor, vertrix_lift_edx, board, actor, actor, owner);
    return port_return(&port, result, entry->edx);
}

/* The attacks of 0x4547b0, 0x4549d0, 0x454c30 and 0x455020: the owner (+0x3b0) gets 0x43bb60
 * with 4, 0x43bae0 and the next handler `next`; the actor's `from` copied to the owner's `to`
 * (when set); the owner's board's (+0x15c) +0xb80, +0xb84 and +0xb88 1 (and +0xb90 0 for
 * `clear`); method +4 of the actor's board and 0x43bbf0. `swap` holds the boards in edi and esi
 * the other way round. */
static uint32_t effect_attack(PORT_SIGNATURE, uint32_t from, uint32_t to, uint32_t next, int clear,
                              int swap)
{
    Port port;
    uint32_t actor = entry->eax;
    uint32_t owner;
    uint32_t board;
    uint32_t other;
    uint32_t esi;
    uint32_t edi;
    uint32_t methods;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    owner = port_u32(&port, actor, 0x3b0);
    board = port_u32(&port, actor, 0x15c);
    other = port_u32(&port, owner, 0x15c);
    esi = swap ? other : board;
    edi = swap ? board : other;
    call_all(&port, entry, 0x43bb60, owner, 4, actor, owner, esi, edi);
    call_all(&port, entry, 0x43bae0, owner, vertrix_lift_edx, actor, owner, esi, edi);
    call_all(&port, entry, 0x4ac8f0, owner, next, actor, owner, esi, edi);
    if (from != 0)
    {
        port_set32(&port, owner, to, port_u32(&port, actor, from));
    }
    port_set32(&port, other, 0xb80, 1);
    port_set32(&port, other, 0xb84, 1);
    port_set32(&port, other, 0xb88, 1);
    if (clear)
    {
        port_set32(&port, other, 0xb90, 0);
    }
    methods = port_u32(&port, board, 0x158);
    call_all(&port, entry, port_u32(&port, methods, 4), board, vertrix_lift_edx, actor, methods,
             esi, edi);
    result = call_all(&port, entry, 0x43bbf0, actor, vertrix_lift_edx, actor, methods, esi, edi);
    return port_return(&port, result, entry->edx);
}

/* Original 0x4547b0: +0x3d4 to +0x434, next 0x454830. */
uint32_t vertrix_port_effect_attack_4547b0(PORT_SIGNATURE)
{
    return effect_attack(calls, services, globals, entry, 0x3d4, 0x434, 0x454830, 0, 0);
}

/* Original 0x4549d0: +0x3d8 to +0x438, next 0x454a50. */
uint32_t vertrix_port_effect_attack_4549d0(PORT_SIGNATURE)
{
    return effect_attack(calls, services, globals, entry, 0x3d8, 0x438, 0x454a50, 0, 0);
}

/* Original 0x454c30: +0x3d8 to +0x438, next 0x454cb0. */
uint32_t vertrix_port_effect_attack_454c30(PORT_SIGNATURE)
{
    return effect_attack(calls, services, globals, entry, 0x3d8, 0x438, 0x454cb0, 0, 0);
}

/* Original 0x455020: nothing copied, +0xb90 0, next 0x4550a0. */
uint32_t vertrix_port_effect_attack_455020(PORT_SIGNATURE)
{
    return effect_attack(calls, services, globals, entry, 0, 0, 0x4550a0, 1, 1);
}

/* The ends of 0x4552b0, 0x455c30 and 0x455580: when `first` and `second` (with 0x44c860) both hold
 * for the board (+0x15c), `act`; method +4 of the board, then in that case 0x43bbf0 and the
 * board's `clear` 0, or (`clear` 0) 0x43bbf0 with 0x452160, the handler left, 0x43bae0 with 1
 * and the actor's +0x184 0. */
static uint32_t state_done(PORT_SIGNATURE, uint32_t first, uint32_t second, uint32_t act,
                           uint32_t clear)
{
    Port port;
    uint32_t actor = entry->eax;
    uint32_t board;
    uint32_t done = 0;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    board = port_u32(&port, actor, 0x15c);
    if (call_all(&port, entry, first, board, 0x44c860, actor, board, 0, entry->edi) != 0 &&
        call_all(&port, entry, second, board, 0x44c860, actor, board, 0, entry->edi) != 0)
    {
        done = 1;
        call_all(&port, entry, act, board, vertrix_lift_edx, actor, board, done, entry->edi);
    }
    result = board_method(&port, entry, board, actor, board, done, entry->edi);
    if (done == 1)
    {
        if (clear != 0)
        {
            result = call_all(&port, entry, 0x43bbf0, actor, vertrix_lift_edx, actor, board, done,
                              entry->edi);
            port_set32(&port, board, clear, 0);
        }
        else
        {
            call_all(&port, entry, 0x43bbf0, actor, 0x452160, actor, board, done, entry->edi);
            call_all(&port, entry, 0x4ac8f0, actor, vertrix_lift_edx, actor, board, done,
                     entry->edi);
            result = call_all(&port, entry, 0x43bae0, actor, done, actor, board, done, entry->edi);
            port_set32(&port, actor, 0x184, 0);
        }
    }
    return port_return(&port, result, entry->edx);
}

/* Original 0x4552b0: 0x42ed40, 0x42ed70, 0x42eba0, +0xb90. */
uint32_t vertrix_port_state_done_4552b0(PORT_SIGNATURE)
{
    return state_done(calls, services, globals, entry, 0x42ed40, 0x42ed70, 0x42eba0, 0xb90);
}

/* Original 0x455c30: 0x42eca0, 0x42ecc0, 0x42ebe0, +0xb8c. */
uint32_t vertrix_port_state_done_455c30(PORT_SIGNATURE)
{
    return state_done(calls, services, globals, entry, 0x42eca0, 0x42ecc0, 0x42ebe0, 0xb8c);
}

/* Original 0x455580: 0x42eca0, 0x42ecc0, 0x4374e0, then the hand over. */
uint32_t vertrix_port_state_done_455580(PORT_SIGNATURE)
{
    return state_done(calls, services, globals, entry, 0x42eca0, 0x42ecc0, 0x4374e0, 0);
}

/* Original 0x455320: when +0x4d0, +0x4d4 and +0x4d8 are all clear, 0x43a510 on +0x3b4 with 5 and
 * 0x42eba0 on the board (+0x15c) with 1; method +4 of the board, then when the edx it leaves is 1,
 * 0x43bbf0 and +0xb90 0. */
uint32_t vertrix_port_state_guard_455320(PORT_SIGNATURE)
{
    Port port;
    uint32_t actor = entry->eax;
    uint32_t board;
    uint32_t edx = 0;
    uint32_t ebx = entry->ebx;
    uint32_t methods;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    board = port_u32(&port, actor, 0x15c);
    if (port_u32(&port, actor, 0x4d0) == 0 && port_u32(&port, actor, 0x4d4) == 0 &&
        port_u32(&port, actor, 0x4d8) == 0)
    {
        ebx = 5;
        call_all(&port, entry, 0x43a510, port_u32(&port, actor, 0x3b4), 5, 5, 5, board, actor);
        call_all(&port, entry, 0x42eba0, board, 1, 5, 5, board, actor);
        edx = vertrix_lift_edx;
    }
    methods = port_u32(&port, board, 0x158);
    result =
        call_all(&port, entry, port_u32(&port, methods, 4), board, edx, ebx, methods, board, actor);
    if (vertrix_lift_edx == 1)
    {
        result = call_all(&port, entry, 0x43bbf0, actor, 1, ebx, methods, board, actor);
        port_set32(&port, board, 0xb90, 0);
    }
    return port_return(&port, result, entry->edx);
}

/* Original 0x455510: when 0x42eca0 and 0x42ecc0 (with 0x44c860) both hold for the board
 * (+0x15c), 0x43c0e0 with 0x4f8184, 0x437460 with 0x455580 and the handler left; method +4 of
 * the board either way. */
uint32_t vertrix_port_effect_field_bind_455510(PORT_SIGNATURE)
{
    Port port;
    uint32_t actor = entry->eax;
    uint32_t board;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    board = port_u32(&port, actor, 0x15c);
    if (port_forward(&port, entry, 0x42eca0, board, 0x44c860, actor, board) != 0 &&
        port_forward(&port, entry, 0x42ecc0, board, 0x44c860, actor, board) != 0)
    {
        port_forward(&port, entry, 0x43c0e0, actor, port_u32(&port, 0, 0x4f8184), actor, board);
        port_forward(&port, entry, 0x437460, board, 0x455580, actor, board);
        port_forward(&port, entry, 0x4ac8f0, actor, vertrix_lift_edx, actor, board);
    }
    result = board_method(&port, entry, board, actor, board, entry->esi, entry->edi);
    return port_return(&port, result, entry->edx);
}

/* Original 0x455f10: the board (+0x15c) steps (0x4ac500, 0x4ac520 and when due 0x4ac5b0); when
 * 0x430090 gives 1, 0x43c0e0 with 0x4f8188 and the next handler 0x455f80; method +4 of the
 * board either way. */
uint32_t vertrix_port_effect_slide_wait_455f10(PORT_SIGNATURE)
{
    Port port;
    uint32_t actor = entry->eax;
    uint32_t board;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    board = port_u32(&port, actor, 0x15c);
    port_forward(&port, entry, 0x4ac500, board, entry->edx, actor, board);
    if (port_forward(&port, entry, 0x4ac520, board, vertrix_lift_edx, actor, board) == 1)
    {
        port_forward(&port, entry, 0x4ac5b0, board, vertrix_lift_edx, actor, board);
    }
    if (port_forward(&port, entry, 0x430090, board, vertrix_lift_edx, actor, board) == 1)
    {
        port_forward(&port, entry, 0x43c0e0, actor, port_u32(&port, 0, 0x4f8188), actor, board);
        port_forward(&port, entry, 0x4ac8f0, actor, 0x455f80, actor, board);
    }
    result = board_method(&port, entry, board, actor, board, entry->esi, entry->edi);
    return port_return(&port, result, entry->edx);
}

/* Original 0x456290: 0x4ac510 when due (on the edx the step leaves); unless 0x476480 holds for
 * 0x74 on 0x54d640, 0x532a60 the actor's +0x14c and the next handler 0x456170; when 0x4b5500
 * then holds, 0x532a60 +0x14c (the answer), otherwise 0. */
uint32_t vertrix_port_actor_sound_wait_456290(PORT_SIGNATURE)
{
    Port port;
    uint32_t actor = entry->eax;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    port_forward(&port, entry, 0x4ac500, actor, actor, entry->ebx, actor);
    if (port_forward(&port, entry, 0x4ac520, vertrix_lift_edx, vertrix_lift_edx, entry->ebx,
                     actor) == 1)
    {
        port_forward(&port, entry, 0x4ac510, vertrix_lift_edx, vertrix_lift_edx, entry->ebx, actor);
    }
    if (port_forward(&port, entry, 0x476480, 0x54d640, 0x74, entry->ebx, actor) == 0)
    {
        port_set32(&port, 0, 0x532a60, port_u32(&port, actor, 0x14c));
        port_forward(&port, entry, 0x4ac8f0, actor, 0x456170, entry->ebx, actor);
    }
    result = port_forward(&port, entry, 0x4b5500, actor, vertrix_lift_edx, entry->ebx, actor);
    if (result != 0)
    {
        result = port_u32(&port, actor, 0x14c);
        port_set32(&port, 0, 0x532a60, result);
    }
    return port_return(&port, result, entry->edx);
}

/* The bonus of 0x457170 and 0x4572b0: for the kinds `kind` to `kind` + 2 (the actor's dword),
 * when the player's (`player`) +0x4d0, +0x4d4 or +0x4d8 (the matching one) is 1: the animation
 * set 0x544bf4, 0x4ac700 with `then`, the handler left and 0x4ac510; otherwise 0 or that
 * value. */
static uint32_t actor_bonus_start(PORT_SIGNATURE, uint32_t player, uint32_t kind, uint32_t then)
{
    Port port;
    uint32_t actor = entry->eax;
    uint32_t which;
    uint32_t value;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    player = port_u32(&port, 0, player);
    which = port_u32(&port, actor, 0);
    if (which - kind > 2)
    {
        return port_return(&port, 0, entry->edx);
    }
    value = port_u32(&port, player, 0x4d0 + (which - kind) * 4);
    if (value != 1)
    {
        return port_return(&port, value, entry->edx);
    }
    port_forward(&port, entry, 0x4ac8d0, actor, 0x544bf4, which, actor);
    port_forward(&port, entry, 0x4ac700, actor, then, which, actor);
    port_forward(&port, entry, 0x4ac8f0, actor, vertrix_lift_edx, which, actor);
    result = port_forward(&port, entry, 0x4ac510, actor, vertrix_lift_edx, which, actor);
    return port_return(&port, result, entry->edx);
}

/* Original 0x457170: the first player 0x540f8c, kinds 100 to 102, then 0x4570b0. */
uint32_t vertrix_port_actor_bonus_start_457170(PORT_SIGNATURE)
{
    return actor_bonus_start(calls, services, globals, entry, 0x540f8c, 0x64, 0x4570b0);
}

/* Original 0x4572b0: the second player 0x540f90, kinds 103 to 105, then 0x4571f0. */
uint32_t vertrix_port_actor_bonus_start_4572b0(PORT_SIGNATURE)
{
    return actor_bonus_start(calls, services, globals, entry, 0x540f90, 0x67, 0x4571f0);
}

/* Original 0x45bb80: when 0x42ec80, 0x42ecc0 and 0x42eca0 (with 0x44c860) all hold for the board
 * (+0x15c): 0x42ebe0, 0x4398c0 with 0x45bad0 and the handler left; method +4 of the board (the
 * table in ebx) either way. */
uint32_t vertrix_port_board_clear_wait_45bb80(PORT_SIGNATURE)
{
    Port port;
    uint32_t actor = entry->eax;
    uint32_t board;
    uint32_t methods;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    board = port_u32(&port, actor, 0x15c);
    if (port_forward(&port, entry, 0x42ec80, board, 0x44c860, actor, board) != 0 &&
        port_forward(&port, entry, 0x42ecc0, board, 0x44c860, actor, board) != 0 &&
        port_forward(&port, entry, 0x42eca0, board, 0x44c860, actor, board) != 0)
    {
        port_forward(&port, entry, 0x42ebe0, board, vertrix_lift_edx, actor, board);
        port_forward(&port, entry, 0x4398c0, board, 0x45bad0, actor, board);
        port_forward(&port, entry, 0x4ac8f0, actor, vertrix_lift_edx, actor, board);
    }
    methods = port_u32(&port, board, 0x158);
    result = port_forward(&port, entry, port_u32(&port, methods, 4), board, vertrix_lift_edx,
                          methods, board);
    return port_return(&port, result, entry->edx);
}
