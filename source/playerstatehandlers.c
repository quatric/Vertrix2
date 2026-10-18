#include "playerstatehandlers.h"

/* Border, finish effect, countdown and linked actor states, and the player's start, step and
 * effect handlers. */

/* A call handing the callee esi, edi and ebp as given and `count` stack dwords. */
static uint32_t call_frame(Port *port, uint32_t target, uint32_t eax, uint32_t edx, uint32_t ebx,
                           uint32_t ecx, uint32_t esi, uint32_t edi, uint32_t ebp,
                           const uint32_t *stack, unsigned count)
{
    return port_call_registers(port, target, eax, edx, ebx, ecx, esi, edi, ebp, stack, count);
}

/* Original 0x450270: on each beat of the border's timer it restarts it and, once 0x4ad530 gives
 * 0, counts +0x58 down: at 0 0x4adfa0 with 0 and the state 0x450300; otherwise the speed -40
 * (+0x48), 0 (+0x4a), a step of 2 to 4 (0x4826c0 on 0x598d30 with 3, +0x4c) and the state
 * 0x4501a0. */
uint32_t vertrix_port_ui_border_storage_update_450270(PORT_SIGNATURE)
{
    Port port;
    uint32_t actor = entry->eax;
    uint32_t result;
    uint32_t count;
    port_open(&port, calls, services, globals, entry);
    port_forward(&port, entry, 0x4ac500, actor, entry->edx, entry->ebx, actor);
    result = port_forward(&port, entry, 0x4ac520, actor, vertrix_lift_edx, entry->ebx, actor);
    if (result != 1)
    {
        return port_return(&port, result, entry->edx);
    }
    result = port_forward(&port, entry, 0x4ac540, actor, vertrix_lift_edx, entry->ebx, actor);
    port_forward(&port, entry, 0x4ac5b0, actor, result, entry->ebx, actor);
    result = port_forward(&port, entry, 0x4ad530, actor, vertrix_lift_edx, entry->ebx, actor);
    if (result != 0)
    {
        return port_return(&port, result, entry->edx);
    }
    count = port_u32(&port, actor, 0x58) - 1;
    port_set32(&port, actor, 0x58, count);
    if (count == 0)
    {
        port_forward(&port, entry, 0x4adfa0, actor, 0, entry->ebx, actor);
        result = port_forward(&port, entry, 0x4ac8f0, actor, 0x450300, entry->ebx, actor);
        return port_return(&port, result, entry->edx);
    }
    port_set16(&port, actor, 0x48, 0xffd8);
    port_set16(&port, actor, 0x4a, 0);
    result = port_forward(&port, entry, 0x4826c0, 0x598d30, 3, entry->ebx, actor);
    port_set16(&port, actor, 0x4c, result + 2);
    result = port_forward(&port, entry, 0x4ac8f0, actor, 0x4501a0, entry->ebx, actor);
    return port_return(&port, result, entry->edx);
}

/* Original 0x4503b0: +0x93 1 and +0x95 3, 0x4ac1f0, and on each beat of the block's timer it
 * restarts it with the fade 0 and step 4 (0x4ad580) and the speed 0 and step 8 (0x4ad530); once
 * both give 0 its state is cleared and +0x15d is 2. Then 0x4ac8a0. */
uint32_t vertrix_port_block_finish_effect_update_4503b0(PORT_SIGNATURE)
{
    Port port;
    uint32_t actor = entry->eax;
    uint32_t time;
    uint32_t faded;
    uint32_t moved;
    uint32_t result;
    uint32_t ebp = entry->ebp;
    port_open(&port, calls, services, globals, entry);
    port_set8(&port, actor, 0x93, 1);
    port_set8(&port, actor, 0x95, 3);
    port_call_with(&port, 0x4ac1f0, actor, entry->edx, entry->ebx, actor, entry->esi, actor, ebp);
    port_call_with(&port, 0x4ac500, actor, vertrix_lift_edx, entry->ebx, actor, entry->esi, actor,
                   ebp);
    if (port_call_with(&port, 0x4ac520, actor, vertrix_lift_edx, entry->ebx, actor, entry->esi,
                       actor, ebp) != 1)
    {
        result = port_call_with(&port, 0x4ac8a0, actor, vertrix_lift_edx, entry->ebx, actor,
                                entry->esi, actor, ebp);
        return port_return(&port, result, entry->edx);
    }
    time = port_call_with(&port, 0x4ac540, actor, vertrix_lift_edx, entry->ebx, actor, entry->esi,
                          actor, ebp);
    port_call_with(&port, 0x4ac5b0, actor, vertrix_lift_edx, time, actor, entry->esi, actor, ebp);
    port_set8(&port, actor, 0x4f, 0);
    port_set16(&port, actor, 0x50, 4);
    faded = port_call_with(&port, 0x4ad580, actor, time, time, actor, entry->esi, actor, ebp);
    port_set16(&port, actor, 0x4a, 0);
    port_set16(&port, actor, 0x4c, 8);
    moved = port_call_with(&port, 0x4ad530, actor, time, time, actor, faded, actor, ebp);
    if (faded == 0 && moved == 0)
    {
        port_call_with(&port, 0x4ac8f0, actor, 0, time, actor, faded, actor, ebp);
        port_set8(&port, actor, 0x15d, 2);
    }
    result =
        port_call_with(&port, 0x4ac8a0, actor, vertrix_lift_edx, time, actor, faded, actor, ebp);
    return port_return(&port, result, entry->edx);
}

/* Original 0x450450: 0x4ac1f0, and on each beat of the block's timer it restarts it with the
 * fade 0 and step 2 (0x4ad580) and the speed 0 and step 1 (0x4ad530); once both give 0 its state
 * is cleared, +0x93 1 and +0x4e 0. Then 0x4ac8a0. */
uint32_t vertrix_port_block_finish_effect_update_450450(PORT_SIGNATURE)
{
    Port port;
    uint32_t actor = entry->eax;
    uint32_t time;
    uint32_t faded;
    uint32_t moved;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    port_forward(&port, entry, 0x4ac1f0, actor, entry->edx, entry->ebx, actor);
    port_forward(&port, entry, 0x4ac500, actor, vertrix_lift_edx, entry->ebx, actor);
    if (port_forward(&port, entry, 0x4ac520, actor, vertrix_lift_edx, entry->ebx, actor) != 1)
    {
        result = port_forward(&port, entry, 0x4ac8a0, actor, vertrix_lift_edx, entry->ebx, actor);
        return port_return(&port, result, entry->edx);
    }
    time = port_forward(&port, entry, 0x4ac540, actor, vertrix_lift_edx, entry->ebx, actor);
    port_forward(&port, entry, 0x4ac5b0, actor, vertrix_lift_edx, time, actor);
    port_set8(&port, actor, 0x4f, 0);
    port_set16(&port, actor, 0x50, 2);
    faded = port_forward(&port, entry, 0x4ad580, actor, time, time, actor);
    port_set16(&port, actor, 0x4a, 0);
    port_set16(&port, actor, 0x4c, 1);
    moved = port_forward_esi(&port, entry, 0x4ad530, actor, time, time, actor, faded);
    if (faded == 0 && moved == 0)
    {
        port_forward_esi(&port, entry, 0x4ac8f0, actor, 0, time, actor, faded);
        port_set8(&port, actor, 0x93, 1);
        port_set8(&port, actor, 0x4e, 0);
    }
    result = port_forward_esi(&port, entry, 0x4ac8a0, actor, vertrix_lift_edx, time, actor, faded);
    return port_return(&port, result, entry->edx);
}

/* Original 0x450750: the countdown of the player (+4, 0x540f88) toward its progress +0x180 (0
 * once +0x3ac is 1) in +0x70, +0x58 0: 0x4ac600 and, on a beat (0x4ac620), 0x4ac610 and +0x64 one
 * less while above +0x70. With +0x3ac 1 and +0x64 reaching +0x70, +0x3ac is 0 and the actor
 * takes the frame (0x4ac510) and the state 0x4507e0. */
uint32_t vertrix_port_player_countdown_update_450750(PORT_SIGNATURE)
{
    Port port;
    uint32_t actor = entry->eax;
    uint32_t player;
    uint32_t result;
    uint32_t edi = entry->edi;
    uint32_t edx;
    port_open(&port, calls, services, globals, entry);
    player = port_u32(&port, port_u32(&port, actor, 4) * 4, 0x540f88);
    port_set32(&port, actor, 0x58, 0);
    if (port_u32(&port, player, 0x3ac) == 1)
    {
        port_set32(&port, actor, 0x70, 0);
    }
    else
    {
        port_set32(&port, actor, 0x70, port_u32(&port, player, 0x180));
    }
    port_forward(&port, entry, 0x4ac600, actor, player, entry->ebx, actor);
    result = port_forward(&port, entry, 0x4ac620, actor, vertrix_lift_edx, entry->ebx, actor);
    edx = vertrix_lift_edx;
    if (result == 1)
    {
        port_forward(&port, entry, 0x4ac610, actor, edx, entry->ebx, actor);
        edx = vertrix_lift_edx;
        result = port_u32(&port, actor, 0x64);
        if ((int32_t)result > (int32_t)port_u32(&port, actor, 0x70))
        {
            edi = result - 1;
            port_set32(&port, actor, 0x64, edi);
        }
    }
    if (port_u32(&port, edx, 0x3ac) != 1)
    {
        return port_return(&port, result, entry->edx);
    }
    result = port_u32(&port, actor, 0x64);
    if (result != port_u32(&port, actor, 0x70))
    {
        return port_return(&port, result, entry->edx);
    }
    port_set32(&port, edx, 0x3ac, 0);
    port_call_with(&port, 0x4ac510, actor, edx, entry->ebx, actor, entry->esi, edi, entry->ebp);
    result = port_call_with(&port, 0x4ac8f0, actor, 0x4507e0, entry->ebx, actor, entry->esi, edi,
                            entry->ebp);
    return port_return(&port, result, entry->edx);
}

/* Original 0x450a10: the linked actor (0x4b5eb0 on the list 0x54671c by +4): with +0x7c 1 and the
 * link's +0x58 1 it shows 0x546618 (0x4ac8d0, 0x4ac710 with 0, 0x4ac8a0) and takes 0x4ac610
 * with 0x450b30 and 0x4ac8f0; otherwise, while the link's +0x64 is below +0x58, it takes the
 * frame +0x7c (0x4ac510), the row 0x533d78 (+0x16), its home +0xa (+0x18), the step 1 (+0x1a)
 * and the state 0x450aa0. */
uint32_t vertrix_port_linked_alternating_update_450a10(PORT_SIGNATURE)
{
    Port port;
    uint32_t actor = entry->eax;
    uint32_t link;
    uint32_t edx;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    link = port_forward(&port, entry, 0x4b5eb0, 0x54671c, port_u32(&port, actor, 4), entry->ebx,
                        actor);
    if (link == 0)
    {
        return port_return(&port, link, entry->edx);
    }
    edx = port_u32(&port, actor, 0x7c);
    if (edx == 1)
    {
        if (port_u32(&port, link, 0x58) != 1)
        {
            return port_return(&port, link, entry->edx);
        }
        port_forward(&port, entry, 0x4ac8d0, actor, 0x546618, entry->ebx, actor);
        port_forward(&port, entry, 0x4ac710, actor, 0, entry->ebx, actor);
        port_forward(&port, entry, 0x4ac8a0, actor, vertrix_lift_edx, entry->ebx, actor);
        port_forward(&port, entry, 0x4ac610, actor, 0x450b30, entry->ebx, actor);
        result = port_forward(&port, entry, 0x4ac8f0, actor, vertrix_lift_edx, entry->ebx, actor);
        return port_return(&port, result, entry->edx);
    }
    result = port_u32(&port, link, 0x64);
    if ((int32_t)result >= (int32_t)port_u32(&port, actor, 0x58))
    {
        return port_return(&port, result, entry->edx);
    }
    port_forward(&port, entry, 0x4ac510, actor, edx, entry->ebx, actor);
    port_set16(&port, actor, 0x16, port_u16(&port, 0, 0x533d78));
    port_set16(&port, actor, 0x18, port_u16(&port, actor, 0xa));
    port_set16(&port, actor, 0x1a, 1);
    result = port_forward(&port, entry, 0x4ac8f0, actor, 0x450aa0, entry->ebx, actor);
    return port_return(&port, result, entry->edx);
}

/* Original 0x450aa0: on each beat of the actor's timer it restarts it and, once 0x4acab0 gives 0,
 * shows 0x546634 (0x4ac8d0, 0x4ac710 with 0, 0x4ac8a0 with 1), 0x4adfa0, the speed -40, 5 and
 * the step 4, the frame 0x450b90 (0x4ac510) and 0x4ac8f0. */
uint32_t vertrix_port_linked_alternating_update_450aa0(PORT_SIGNATURE)
{
    Port port;
    uint32_t actor = entry->eax;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    port_forward(&port, entry, 0x4ac500, actor, entry->edx, entry->ebx, actor);
    result = port_forward(&port, entry, 0x4ac520, actor, vertrix_lift_edx, entry->ebx, actor);
    if (result != 1)
    {
        return port_return(&port, result, entry->edx);
    }
    result = port_forward(&port, entry, 0x4ac540, actor, vertrix_lift_edx, entry->ebx, actor);
    port_forward(&port, entry, 0x4ac5b0, actor, result, entry->ebx, actor);
    result = port_forward(&port, entry, 0x4acab0, actor, vertrix_lift_edx, entry->ebx, actor);
    if (result != 0)
    {
        return port_return(&port, result, entry->edx);
    }
    port_forward(&port, entry, 0x4ac8d0, actor, 0x546634, entry->ebx, actor);
    port_forward(&port, entry, 0x4ac710, actor, 0, entry->ebx, actor);
    port_forward(&port, entry, 0x4ac8a0, actor, 1, entry->ebx, actor);
    port_forward(&port, entry, 0x4adfa0, actor, vertrix_lift_edx, entry->ebx, actor);
    port_set16(&port, actor, 0x48, 0xffd8);
    port_set16(&port, actor, 0x4a, 5);
    port_set16(&port, actor, 0x4c, 4);
    port_forward(&port, entry, 0x4ac510, actor, 0x450b90, entry->ebx, actor);
    result = port_forward(&port, entry, 0x4ac8f0, actor, vertrix_lift_edx, entry->ebx, actor);
    return port_return(&port, result, entry->edx);
}

/* The board's method +4 (its draw) on the board. */
static uint32_t board_draw(Port *port, const LiftEntry *entry, uint32_t board, uint32_t ebx,
                           uint32_t esi)
{
    uint32_t methods = port_u32(port, board, 0x158);
    return port_call_with(port, port_u32(port, methods, 4), board, methods, ebx, board, esi,
                          entry->edi, entry->ebp);
}

/* The start states 0x4513f0 and 0x451690: a player whose piece starts (+0x4cd) and fits
 * (0x4322f0 on the board +0x15c) takes the sound 0x4f8184 (0x43c0e0), 0x42eee0, 0x4334a0 with the
 * piece, 0x43bad0 with 0, the board's speed 0x4f7be8 by 0x532bbc (0x4ac7b0) and the state
 * `next`; otherwise, with the board's +0xbd8 clear, the sound 0x4f819c and the state 0x451920.
 * Then the board draws. */
static uint32_t player_start(PORT_SIGNATURE, uint32_t next)
{
    Port port;
    uint32_t player = entry->eax;
    uint32_t board;
    uint32_t state = 0x451920;
    port_open(&port, calls, services, globals, entry);
    board = port_u32(&port, player, 0x15c);
    if (port_u8(&port, player, 0x4cd) != 0 &&
        port_call_with(&port, 0x4322f0, board, entry->edx, player, board, player, entry->edi,
                       entry->ebp) == 1)
    {
        port_call_with(&port, 0x43c0e0, player, port_u32(&port, 0, 0x4f8184), player, board, player,
                       entry->edi, entry->ebp);
        port_call_with(&port, 0x42eee0, board, vertrix_lift_edx, player, board, player, entry->edi,
                       entry->ebp);
        port_call_with(&port, 0x4334a0, board,
                       (uint32_t)(int32_t)(int8_t)port_u8(&port, player, 0x4cd), player, board,
                       player, entry->edi, entry->ebp);
        port_call_with(&port, 0x43bad0, player, 0, player, board, player, entry->edi, entry->ebp);
        port_call_with(&port, 0x4ac7b0, board,
                       port_u32(&port, port_u32(&port, 0, 0x532bbc) * 4, 0x4f7be8), player, board,
                       player, entry->edi, entry->ebp);
        state = next;
    }
    else if (port_u32(&port, board, 0xbd8) == 0)
    {
        port_call_with(&port, 0x43c0e0, player, port_u32(&port, 0, 0x4f819c), player, board, player,
                       entry->edi, entry->ebp);
    }
    port_call_with(&port, 0x4ac8f0, player, state, player, board, player, entry->edi, entry->ebp);
    return port_return(&port, board_draw(&port, entry, board, player, player), entry->edx);
}

/* Original 0x4513f0: then 0x451490. */
uint32_t vertrix_port_state_start_4513f0(PORT_SIGNATURE)
{
    return player_start(calls, services, globals, entry, 0x451490);
}

/* Original 0x451690: then 0x451730. */
uint32_t vertrix_port_state_start_451690(PORT_SIGNATURE)
{
    return player_start(calls, services, globals, entry, 0x451730);
}

/* The step states 0x451490 and 0x451730: on each beat of the board's (+0x15c) timer it restarts
 * it and steps (0x4342f0) once a tick of the edx 0x4ac5b0 leaves; when 0x433e20 then gives 0
 * the player takes the state `next` (after 0x4323d0 with 0x451520 when `restart`). Then the
 * board draws. */
static uint32_t player_steps(PORT_SIGNATURE, int restart, uint32_t next)
{
    Port port;
    uint32_t player = entry->eax;
    uint32_t board;
    uint32_t ebx = entry->ebx;
    uint32_t edx;
    port_open(&port, calls, services, globals, entry);
    board = port_u32(&port, player, 0x15c);
    port_forward_esi(&port, entry, 0x4ac500, board, entry->edx, ebx, board, player);
    if (port_forward_esi(&port, entry, 0x4ac520, board, vertrix_lift_edx, ebx, board, player) == 1)
    {
        ebx = port_forward_esi(&port, entry, 0x4ac540, board, vertrix_lift_edx, ebx, board, player);
        port_forward_esi(&port, entry, 0x4ac5b0, board, ebx, ebx, board, player);
        if (ebx != 0)
        {
            edx = vertrix_lift_edx;
            do
            {
                port_forward_esi(&port, entry, 0x4342f0, board, edx - 1, ebx, board, player);
                edx = vertrix_lift_edx;
            } while (edx != 0);
        }
    }
    if (port_forward_esi(&port, entry, 0x433e20, board, vertrix_lift_edx, ebx, board, player) == 0)
    {
        if (restart)
        {
            port_forward_esi(&port, entry, 0x4323d0, board, 0x451520, ebx, board, player);
            port_forward_esi(&port, entry, 0x4ac8f0, player, vertrix_lift_edx, ebx, board, player);
        }
        else
        {
            port_forward_esi(&port, entry, 0x4ac8f0, player, next, ebx, board, player);
        }
    }
    return port_return(&port, board_draw(&port, entry, board, ebx, player), entry->edx);
}

/* Original 0x451490: 0x4323d0 with 0x451520, then the edx it leaves. */
uint32_t vertrix_port_state_steps_451490(PORT_SIGNATURE)
{
    return player_steps(calls, services, globals, entry, 1, 0);
}

/* Original 0x451730: then 0x4517c0. */
uint32_t vertrix_port_state_steps_451730(PORT_SIGNATURE)
{
    return player_steps(calls, services, globals, entry, 0, 0x4517c0);
}

/* Original 0x4526e0: when the opponent's (+0x3b0) board takes the state 0x44c860 (0x42eca0) the
 * player's +0x3f4 is 0; both boards draw (the opponent's with whether it did) and, when that
 * gives edx 1, both players' views are set up again (0x43bbf0). */
uint32_t vertrix_port_player_opponent_settle_4526e0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x20
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t player = entry->eax;
    uint32_t opponent;
    uint32_t board;
    uint32_t other;
    uint32_t methods;
    uint32_t result;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, -0x1cu, player);
    opponent = port_u32(&port, player, 0x3b0);
    board = port_u32(&port, player, 0x15c);
    port_set32(&port, ebp, -0x18u, 0);
    other = port_u32(&port, opponent, 0x15c);
    result = port_call_with(&port, 0x42eca0, other, 0x44c860, other, player, board, opponent, ebp);
    if (result != 0)
    {
        port_set32(&port, player, 0x3f4, 0);
        port_set32(&port, ebp, -0x18u, 1);
    }
    methods = port_u32(&port, board, 0x158);
    result = port_call_with(&port, port_u32(&port, methods, 4), board, vertrix_lift_edx, other,
                            methods, board, opponent, ebp);
    methods = port_u32(&port, other, 0x158);
    result = port_call_with(&port, port_u32(&port, methods, 4), other, port_u32(&port, ebp, -0x18u),
                            other, methods, board, opponent, ebp);
    if (vertrix_lift_edx != 1)
    {
        return port_return(&port, result, entry->edx);
    }
    port_call_with(&port, 0x43bbf0, port_u32(&port, ebp, -0x1cu), vertrix_lift_edx, other, methods,
                   board, opponent, ebp);
    result = port_call_with(&port, 0x43bbf0, opponent, vertrix_lift_edx, other, methods, board,
                            opponent, ebp);
    return port_return(&port, result, entry->edx);
}

/* The armed effect handlers 0x452b20, 0x452bd0 and 0x452c80: with no effect pending (+0x4d0,
 * +0x4d4, +0x4d8) and +0x3c4 1, 0x43a5f0 on +0x3b4 with the registers `value` (edx, ebx), 6 (ecx)
 * and the stack `pushed`; the board (+0x15c) draws with whether none was pending and, when that
 * gives edx 1, the view is set up again (0x43bbf0). */
static uint32_t effect_armed(PORT_SIGNATURE, uint32_t value, const uint32_t *pushed)
{
    enum
    {
        BELOW = 0x1c
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t player = entry->eax;
    uint32_t board;
    uint32_t idle = 0;
    uint32_t ebx = entry->ebx;
    uint32_t methods;
    uint32_t result;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    board = port_u32(&port, player, 0x15c);
    port_set32(&port, ebp, -0x18u, port_u32(&port, player, 0x3b4));
    if (port_u32(&port, player, 0x4d0) == 0 && port_u32(&port, player, 0x4d4) == 0 &&
        port_u32(&port, player, 0x4d8) == 0)
    {
        if (port_u32(&port, player, 0x3c4) == 1)
        {
            ebx = value;
            call_frame(&port, 0x43a5f0, port_u32(&port, ebp, -0x18u), value, value, 6, board,
                       player, ebp, pushed, 3);
        }
        idle = 1;
    }
    methods = port_u32(&port, board, 0x158);
    result = call_frame(&port, port_u32(&port, methods, 4), board, idle, ebx, methods, board,
                        player, ebp, NULL, 0);
    if (vertrix_lift_edx != 1)
    {
        return port_return(&port, result, entry->edx);
    }
    result = call_frame(&port, 0x43bbf0, player, vertrix_lift_edx, ebx, methods, board, player, ebp,
                        NULL, 0);
    return port_return(&port, result, entry->edx);
}

/* Original 0x452b20: 6 and the stack 1, 1, 1. */
uint32_t vertrix_port_effect_armed_handler_452b20(PORT_SIGNATURE)
{
    static const uint32_t pushed[3] = {1, 1, 1};
    return effect_armed(calls, services, globals, entry, 6, pushed);
}

/* Original 0x452bd0: -1 and the stack 0, 0, 1. */
uint32_t vertrix_port_effect_armed_handler_452bd0(PORT_SIGNATURE)
{
    static const uint32_t pushed[3] = {0, 0, 1};
    return effect_armed(calls, services, globals, entry, 0xffffffffu, pushed);
}

/* Original 0x452c80: as 0x452b20. */
uint32_t vertrix_port_effect_armed_handler_452c80(PORT_SIGNATURE)
{
    static const uint32_t pushed[3] = {1, 1, 1};
    return effect_armed(calls, services, globals, entry, 6, pushed);
}

/* Original 0x452d70: the player's and the opponent's (+0x3b0) progress +0x17c compared: equal or
 * behind, 0x43acd0; ahead, 0x43ac00. Unless equal both take the other's progress (0x43b810);
 * unless equal the opponent takes the sound 0x4f81ac (0x43c0e0). Then the board (+0x15c) draws
 * and the view is set up again (0x43bbf0). */
uint32_t vertrix_port_effect_progress_compare_452d70(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x20
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t player = entry->eax;
    uint32_t opponent;
    uint32_t board;
    uint32_t mine;
    uint32_t theirs;
    uint32_t methods;
    uint32_t result;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    opponent = port_u32(&port, player, 0x3b0);
    board = port_u32(&port, player, 0x15c);
    mine = port_u32(&port, player, 0x17c);
    theirs = port_u32(&port, opponent, 0x17c);
    port_set32(&port, ebp, -0x18u, mine);
    port_set32(&port, ebp, -0x1cu, theirs);
    if (mine == theirs)
    {
        port_call_with(&port, 0x43acd0, player, theirs, player, opponent, mine, board, ebp);
    }
    else
    {
        port_call_with(&port, mine < theirs ? 0x43acd0 : 0x43ac00, player, theirs, player, opponent,
                       mine, board, ebp);
        port_call_with(&port, 0x43b810, player, port_u32(&port, ebp, -0x1cu), player, opponent,
                       mine, board, ebp);
        port_call_with(&port, 0x43b810, opponent, port_u32(&port, ebp, -0x18u), player, opponent,
                       mine, board, ebp);
        port_call_with(&port, 0x43c0e0, opponent, port_u32(&port, 0, 0x4f81ac), player, opponent,
                       mine, board, ebp);
    }
    methods = port_u32(&port, board, 0x158);
    port_call_with(&port, port_u32(&port, methods, 4), board, methods, player, opponent, mine,
                   board, ebp);
    result = port_call_with(&port, 0x43bbf0, player, vertrix_lift_edx, player, opponent, mine,
                            board, ebp);
    return port_return(&port, result, entry->edx);
}
