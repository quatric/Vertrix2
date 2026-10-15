#include "port_boards.h"

/* The board states of the play actors: the choice apply and take, the match and attack checks,
 * the effect flags, the drain waits, the guard, the slide advance, and the walkers
 * of the title. */

static uint32_t call_frame(Port *port, uint32_t target, uint32_t eax, uint32_t edx, uint32_t ebx,
                           uint32_t ecx, uint32_t esi, uint32_t edi, uint32_t ebp,
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

static uint32_t sign16(uint32_t value)
{
    return (uint32_t)(int32_t)(int16_t)value;
}

/* The second method (+4 of +0x158) of the object. */
static uint32_t object_step(Port *port, uint32_t object, uint32_t ebx, uint32_t ecx, uint32_t esi,
                            uint32_t edi, uint32_t ebp)
{
    uint32_t methods = port_u32(port, object, 0x158);
    return port_call_with(port, port_u32(port, methods, 4), object, methods, ebx, ecx, esi, edi,
                          ebp);
}

/* Original 0x451e20: the board +0x3b8's choice at (+0x194, +0x198): when it is not ready
 * (0x42a190) the actor finishes (0x43acd0 with 1); when it is, unless busy (0x43ccb0), its cell
 * (0x42a170) is tried (0x43c140) and a refusal finishes it. The child +0x15c steps; a finished
 * actor ends (0x43bbf0). */
uint32_t vertrix_port_state_choice_apply_451e20(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x2c
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t actor = entry->eax;
    uint32_t board;
    uint32_t ebx;
    uint32_t ecx = entry->ecx;
    uint32_t result;
    uint32_t cell[1];
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, -0x28u, actor);
    board = port_u32(&port, actor, 0x3b8);
    ebx = port_u32(&port, actor, 0x198);
    port_set32(&port, ebp, -0x20u, 0);
    port_set32(&port, ebp, -0x24u, port_u32(&port, actor, 0x15c));
    result = port_call_with(&port, 0x42a190, board, port_u32(&port, actor, 0x194), ebx, ecx, actor,
                            board, ebp);
    if (result != 1)
    {
        ecx = 1;
        port_call_with(&port, 0x43acd0, actor, vertrix_lift_edx, ebx, 1, actor, board, ebp);
        port_set32(&port, ebp, -0x20u, 1);
    }
    else if (port_call_with(&port, 0x43ccb0, actor, vertrix_lift_edx, ebx, ecx, actor, board,
                            ebp) == 0)
    {
        ebx = port_u32(&port, actor, 0x198);
        ecx = ebp - 0x18;
        cell[0] = ebp - 0x1c;
        call_frame(&port, 0x42a170, board, port_u32(&port, actor, 0x194), ebx, ecx, actor, board,
                   ebp, cell, 1);
        ebx = port_u8(&port, ebp, -0x1cu);
        if (port_call_with(&port, 0x43c140, actor, port_u8(&port, ebp, -0x18u), ebx, ecx, actor,
                           board, ebp) == 0)
        {
            ebx = 1;
            port_call_with(&port, 0x43acd0, actor, vertrix_lift_edx, 1, ecx, actor, board, ebp);
            port_set32(&port, ebp, -0x20u, 1);
        }
    }
    result = object_step(&port, port_u32(&port, ebp, -0x24u), ebx, ecx,
                         port_u32(&port, ebp, -0x20u), board, ebp);
    if (port_u32(&port, ebp, -0x20u) == 1)
    {
        result = port_call_with(&port, 0x43bbf0, port_u32(&port, ebp, -0x28u), vertrix_lift_edx,
                                ebx, ecx, 1, board, ebp);
    }
    return port_return(&port, result, entry->edx);
}

/* Original 0x451f50: the board +0x3b8's choice at (+0x194, +0x198): when not ready (0x42a190)
 * the actor finishes; when ready it is taken (0x42a140), the actor takes the state 0x451dd0, its
 * mark (0x43bae0 with 4) and cell (0x42a170) give the two scores (0x43bd90) for it and the
 * opponent +0x3b0 (0x43c0e0). The child +0x15c steps; a finished actor ends (0x43bbf0). */
uint32_t vertrix_port_state_choice_take_451f50(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x38
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t actor = entry->eax;
    uint32_t board;
    uint32_t ebx;
    uint32_t ecx = entry->ecx;
    uint32_t result;
    uint32_t cell[1];
    uint32_t scores[2];
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, -0x2cu, actor);
    board = port_u32(&port, actor, 0x3b8);
    ebx = port_u32(&port, actor, 0x198);
    port_set32(&port, ebp, -0x24u, 0);
    port_set32(&port, ebp, -0x28u, port_u32(&port, actor, 0x3b0));
    port_set32(&port, ebp, -0x20u, port_u32(&port, actor, 0x15c));
    result = port_call_with(&port, 0x42a190, board, port_u32(&port, actor, 0x194), ebx, ecx, actor,
                            board, ebp);
    if (result != 1)
    {
        port_set32(&port, ebp, -0x24u, 1);
    }
    else
    {
        port_call_with(&port, 0x42a140, board, port_u32(&port, actor, 0x194),
                       port_u32(&port, actor, 0x198), ecx, actor, board, ebp);
        port_call_with(&port, 0x4ac8f0, actor, 0x451dd0, port_u32(&port, actor, 0x198), ecx, actor,
                       board, ebp);
        ecx = ebp - 0x18;
        port_call_with(&port, 0x43bae0, actor, 4, port_u32(&port, actor, 0x198), ecx, actor, board,
                       ebp);
        cell[0] = ebp - 0x1c;
        call_frame(&port, 0x42a170, board, port_u32(&port, actor, 0x194),
                   port_u32(&port, actor, 0x198), ecx, actor, board, ebp, cell, 1);
        ebx = port_u8(&port, ebp, -0x1cu);
        ecx = ebp - 0x34;
        scores[0] = ebp - 0x30;
        scores[1] = 0;
        call_frame(&port, 0x43bd90, actor, port_u8(&port, ebp, -0x18u), ebx, ecx, actor, board, ebp,
                   scores, 2);
        port_call_with(&port, 0x43c0e0, actor, port_u32(&port, ebp, -0x34u), ebx, ecx, actor, board,
                       ebp);
        port_call_with(&port, 0x43c0e0, port_u32(&port, ebp, -0x28u), port_u32(&port, ebp, -0x30u),
                       ebx, ecx, actor, board, ebp);
    }
    ebx = port_u32(&port, ebp, -0x24u);
    result = object_step(&port, port_u32(&port, ebp, -0x20u), ebx, ecx, actor, board, ebp);
    if (ebx == 1)
    {
        result = port_call_with(&port, 0x43bbf0, port_u32(&port, ebp, -0x2cu), vertrix_lift_edx,
                                ebx, ecx, actor, board, ebp);
    }
    return port_return(&port, result, entry->edx);
}

/* Original 0x452160: the match check of the child +0x15c: matched (0x4328a0 1) it slides at the
 * level's speed 0x4f7bf4 (0x4ac7d0, +0x1a 0x4f7c00, +0x58 0, 0x4ac510) and the actor takes the
 * state 0x452770; with +0x44c 1 the board moves on (0x452250); otherwise a full board (0x43ba70)
 * marks 2 (0x43bae0, 0x43ba80) into the state 0x451a60, else marks 0 into 0x450ff0. The child
 * steps. */
uint32_t vertrix_port_state_match_452160(PORT_SIGNATURE)
{
    Port port;
    uint32_t actor = entry->eax;
    uint32_t child;
    uint32_t level;
    port_open(&port, calls, services, globals, entry);
    child = port_u32(&port, actor, 0x15c);
    if (port_forward(&port, entry, 0x4328a0, child, entry->edx, child, actor) == 1)
    {
        level = port_u32(&port, 0, 0x532bbc);
        port_forward(&port, entry, 0x4ac7d0, child, port_u32(&port, level * 4, 0x4f7bf4), child,
                     actor);
        level = port_u32(&port, 0, 0x532bbc);
        port_set16(&port, child, 0x1a, port_u16(&port, level * 4, 0x4f7c00));
        port_set32(&port, child, 0x58, 0);
        port_forward(&port, entry, 0x4ac510, child, 0x452770, child, actor);
        port_forward(&port, entry, 0x4ac8f0, actor, vertrix_lift_edx, child, actor);
    }
    else if (port_u32(&port, actor, 0x44c) == 1)
    {
        port_forward(&port, entry, 0x452250, actor, vertrix_lift_edx, child, actor);
    }
    else if (port_forward(&port, entry, 0x43ba70, actor, vertrix_lift_edx, child, actor) == 1)
    {
        port_forward(&port, entry, 0x4ac8f0, actor, 0x451a60, child, actor);
        port_forward(&port, entry, 0x43bae0, actor, 2, child, actor);
        port_forward(&port, entry, 0x43ba80, actor, vertrix_lift_edx, child, actor);
    }
    else
    {
        port_forward(&port, entry, 0x4ac8f0, actor, 0x450ff0, child, actor);
        port_forward(&port, entry, 0x43bae0, actor, 0, child, actor);
    }
    return port_return(&port,
                       object_step(&port, child, child, actor, entry->esi, entry->edi, entry->ebp),
                       entry->edx);
}

/* Original 0x452440: the attack check: when the opponent +0x3b0's child at its +0x428 meets
 * (0x4316c0) the actor's +0x3f0, the actor's child slides at the level's speed 0x4f7c24 (0x4ac7b0,
 * +0x1a 0x4f7c30, +0x58 0, 0x4ac510), the actor takes the state 0x452520 and the opponent scores
 * 0x4f8188 (0x43c0e0); otherwise both finish. Both children step; finished, both end
 * (0x43bbf0). */
uint32_t vertrix_port_state_attack_452440(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x24
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t actor = entry->eax;
    uint32_t other;
    uint32_t child;
    uint32_t ebx;
    uint32_t level;
    uint32_t result;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, -0x20u, actor);
    other = port_u32(&port, actor, 0x3b0);
    child = port_u32(&port, actor, 0x15c);
    ebx = port_u32(&port, actor, 0x3f0);
    port_set32(&port, ebp, -0x1cu, 0);
    port_set32(&port, ebp, -0x18u, port_u32(&port, other, 0x15c));
    if (port_call_with(&port, 0x4316c0, port_u32(&port, other, 0x15c),
                       port_u32(&port, other, 0x428), ebx, child, actor, other, ebp) == 1)
    {
        level = port_u32(&port, 0, 0x532bbc);
        port_call_with(&port, 0x4ac7b0, child, port_u32(&port, level * 4, 0x4f7c24), ebx, child,
                       actor, other, ebp);
        level = port_u32(&port, 0, 0x532bbc);
        port_set16(&port, child, 0x1a, port_u16(&port, level * 4, 0x4f7c30));
        port_set32(&port, child, 0x58, 0);
        port_call_with(&port, 0x4ac510, child, 0x452520, ebx, child, actor, other, ebp);
        port_call_with(&port, 0x4ac8f0, actor, vertrix_lift_edx, ebx, child, actor, other, ebp);
        port_call_with(&port, 0x43c0e0, other, port_u32(&port, 0, 0x4f8188), ebx, child, actor,
                       other, ebp);
    }
    else
    {
        port_set32(&port, ebp, -0x1cu, 1);
    }
    object_step(&port, child, ebx, child, actor, other, ebp);
    result = object_step(&port, port_u32(&port, ebp, -0x18u), ebx, child,
                         port_u32(&port, ebp, -0x1cu), other, ebp);
    if (port_u32(&port, ebp, -0x1cu) == 1)
    {
        port_call_with(&port, 0x43bbf0, port_u32(&port, ebp, -0x20u), vertrix_lift_edx, ebx, child,
                       1, other, ebp);
        result =
            port_call_with(&port, 0x43bbf0, other, vertrix_lift_edx, ebx, child, 1, other, ebp);
    }
    return port_return(&port, result, entry->edx);
}

/* Original 0x452960: the effect flags +0x4d0, +0x4d4 and +0x4d8 by the effect +0x4cd when the
 * phase +0x3c4 is 1 (effect 1 the third, 2 and 4 all, 3 the third) or, for effect 1, 2 (the first
 * and third); the actor takes the state edx, its child +0x15c steps and it scores 0x4f81a4
 * (0x43c0e0). */
uint32_t vertrix_port_state_effect_flags_452960(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x1c
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t actor = entry->eax;
    uint32_t effect;
    uint32_t ebx = entry->ebx;
    uint32_t first = 0;
    uint32_t second = 0;
    uint32_t third = 0;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, -0x18u, entry->edx);
    port_set32(&port, ebp, -0x14u, port_u32(&port, actor, 0x15c));
    effect = port_u8(&port, actor, 0x4cd);
    ebx = (ebx & 0xffffff00u) | effect;
    if (effect >= 1 && effect <= 4)
    {
        ebx = port_u32(&port, actor, 0x3c4);
        if (ebx == 1)
        {
            third = 1;
            if (effect == 2 || effect == 4)
            {
                first = 1;
                second = 1;
            }
        }
        else if (ebx == 2 && effect == 1)
        {
            first = 1;
            third = 1;
        }
    }
    port_set32(&port, actor, 0x4d0, first);
    port_set32(&port, actor, 0x4d4, second);
    port_set32(&port, actor, 0x4d8, third);
    port_call_with(&port, 0x4ac8f0, actor, port_u32(&port, ebp, -0x18u), ebx, actor, third, first,
                   ebp);
    object_step(&port, port_u32(&port, ebp, -0x14u), ebx, actor, third, first, ebp);
    return port_return(&port,
                       port_call_with(&port, 0x43c0e0, actor, port_u32(&port, 0, 0x4f81a4), ebx,
                                      actor, third, first, ebp),
                       vertrix_lift_edx);
}

/* The drain wait of 0x454a50 and 0x454cb0 after `start` (0x435e80 with 1 or 0x435f30 with 0):
 * while drains +0x438 remain and `check` (with 5) gives 1, one is used: the child slides at the
 * level's speed 0x4f7c60 (0x4ac7b0, 0x4ac510 with `next`), the actor's state is cleared, it scores
 * 0x4f8194 (0x43c0e0) and the opponent +0x3b0 picks (0x43ac00); otherwise the opponent finishes
 * (0x43acd0 with 1). The child steps; a finish of 1 ends the actor (0x43bbf0). */
static uint32_t drain_wait(PORT_SIGNATURE, uint32_t start, uint32_t flag, uint32_t check,
                           uint32_t next)
{
    enum
    {
        BELOW = 0x1c
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t actor = entry->eax;
    uint32_t child;
    uint32_t other;
    uint32_t result;
    int used = 0;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    child = port_u32(&port, actor, 0x15c);
    other = port_u32(&port, actor, 0x3b0);
    port_set32(&port, ebp, -0x18u, 0);
    port_call_with(&port, start, child, flag, actor, child, other, actor, ebp);
    if (start == 0x435f30)
    {
        port_set32(&port, ebp, -0x18u, vertrix_lift_edx);
    }
    if ((int32_t)port_u32(&port, actor, 0x438) > 0 &&
        port_call_with(&port, check, child, 5, actor, child, other, actor, ebp) == 1)
    {
        uint32_t level;
        port_set32(&port, actor, 0x438, port_u32(&port, actor, 0x438) - 1);
        level = port_u32(&port, 0, 0x532bbc);
        port_call_with(&port, 0x4ac7b0, child, port_u32(&port, level * 4, 0x4f7c60), actor, child,
                       other, actor, ebp);
        port_call_with(&port, 0x4ac510, child, next, actor, child, other, actor, ebp);
        port_call_with(&port, 0x4ac8f0, actor, vertrix_lift_edx, actor, child, other, actor, ebp);
        port_call_with(&port, 0x43c0e0, actor, port_u32(&port, 0, 0x4f8194), actor, child, other,
                       actor, ebp);
        port_call_with(&port, 0x43ac00, other, vertrix_lift_edx, actor, child, other, actor, ebp);
        used = 1;
    }
    if (!used)
    {
        port_call_with(&port, 0x43acd0, other, 1, actor, child, other, actor, ebp);
        port_set32(&port, ebp, -0x18u, vertrix_lift_edx);
    }
    result = object_step(&port, child, actor, child, other, actor, ebp);
    if (port_u32(&port, ebp, -0x18u) == 1)
    {
        result = port_call_with(&port, 0x43bbf0, actor, vertrix_lift_edx, actor, child, other,
                                actor, ebp);
    }
    return port_return(&port, result, entry->edx);
}

/* Original 0x454a50: the drain wait after 0x435e80, checked by 0x436440, into 0x454b20. */
uint32_t vertrix_port_state_drain_wait_454a50(PORT_SIGNATURE)
{
    return drain_wait(calls, services, globals, entry, 0x435e80, 1, 0x436440, 0x454b20);
}

/* Original 0x454cb0: the drain wait after 0x435f30, checked by 0x4365c0, into 0x454d80. */
uint32_t vertrix_port_state_drain_wait_454cb0(PORT_SIGNATURE)
{
    return drain_wait(calls, services, globals, entry, 0x435f30, 0, 0x4365c0, 0x454d80);
}

/* Original 0x4553a0: the guard: with no effect flags (+0x4d0, +0x4d4, +0x4d8) the opponent's
 * children +0x3b4 take 5 (0x43a510) and a settled child +0x15c (0x42ed40, 0x42ed70 with 0x44c860)
 * is released (0x42eba0) to end the actor, an unsettled one takes the state 0x4552b0; with flags a
 * settled child takes the state 0x455320. The child steps; on release the actor ends (0x43bbf0)
 * and the child's +0xb90 clears. */
uint32_t vertrix_port_state_guard_4553a0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x1c
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t actor = entry->eax;
    uint32_t child;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t result;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, -0x18u, 0);
    child = port_u32(&port, actor, 0x15c);
    if (port_u32(&port, actor, 0x4d0) == 0 && port_u32(&port, actor, 0x4d4) == 0 &&
        port_u32(&port, actor, 0x4d8) == 0)
    {
        ebx = 5;
        ecx = 5;
        port_call_with(&port, 0x43a510, port_u32(&port, actor, 0x3b4), 5, 5, 5, child, actor, ebp);
        if (port_call_with(&port, 0x42ed40, child, 0x44c860, ebx, ecx, child, actor, ebp) != 0 &&
            port_call_with(&port, 0x42ed70, child, 0x44c860, ebx, ecx, child, actor, ebp) != 0)
        {
            ecx = 1;
            port_call_with(&port, 0x42eba0, child, vertrix_lift_edx, ebx, 1, child, actor, ebp);
            port_set32(&port, ebp, -0x18u, 1);
        }
        else
        {
            port_call_with(&port, 0x4ac8f0, actor, 0x4552b0, ebx, ecx, child, actor, ebp);
        }
    }
    else if (port_call_with(&port, 0x42ed40, child, 0x44c860, ebx, ecx, child, actor, ebp) != 0 &&
             port_call_with(&port, 0x42ed70, child, 0x44c860, ebx, ecx, child, actor, ebp) != 0)
    {
        port_call_with(&port, 0x4ac8f0, actor, 0x455320, ebx, ecx, child, actor, ebp);
    }
    ebx = port_u32(&port, ebp, -0x18u);
    result = object_step(&port, child, ebx, ecx, child, actor, ebp);
    if (ebx == 1)
    {
        result =
            port_call_with(&port, 0x43bbf0, actor, vertrix_lift_edx, ebx, ecx, child, actor, ebp);
        port_set32(&port, child, 0xb90, 0);
    }
    return port_return(&port, result, entry->edx);
}

/* Original 0x455f80: the slide of the child +0x15c: when due its run +0x58 grows by the step times
 * its speed +0x1a; under a cell (24) it moves on (0x42f2e0); at a cell it lands (0x42f760), the
 * actor's count +0x444 rises, the run keeps its remainder, and unless the path (0x438910 with
 * +0x3e4) goes on, its end 0x456060 (0x430100) clears the actor's state; on the path the actor
 * scores 0x4f8188 (0x43c0e0). The child steps. */
uint32_t vertrix_port_effect_slide_advance_455f80(PORT_SIGNATURE)
{
    Port port;
    uint32_t actor = entry->eax;
    uint32_t child;
    uint32_t edx;
    uint32_t ebx = entry->ebx;
    uint32_t run;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    child = port_u32(&port, actor, 0x15c);
    port_forward_esi(&port, entry, 0x4ac500, child, entry->edx, ebx, child, actor);
    result = port_forward_esi(&port, entry, 0x4ac520, child, vertrix_lift_edx, ebx, child, actor);
    edx = vertrix_lift_edx;
    if (result == 1)
    {
        uint32_t amount =
            port_forward_esi(&port, entry, 0x4ac540, child, vertrix_lift_edx, ebx, child, actor);
        port_forward_esi(&port, entry, 0x4ac5b0, child, amount, ebx, child, actor);
        edx = vertrix_lift_edx * sign16(port_u16(&port, child, 0x1a));
        port_set32(&port, child, 0x58, port_u32(&port, child, 0x58) + edx);
    }
    if ((int32_t)port_u32(&port, child, 0x58) < 0x18)
    {
        port_forward_esi(&port, entry, 0x42f2e0, child, edx, ebx, child, actor);
        return port_return(&port,
                           object_step(&port, child, ebx, child, actor, entry->edi, entry->ebp),
                           entry->edx);
    }
    port_forward_esi(&port, entry, 0x42f760, child, edx, ebx, child, actor);
    port_set32(&port, actor, 0x444, port_u32(&port, actor, 0x444) + 1);
    run = port_u32(&port, child, 0x58);
    if ((int32_t)run >= 0x18)
    {
        run = (uint32_t)((int32_t)run % 0x18);
        port_set32(&port, child, 0x58, run);
    }
    ebx = port_u32(&port, actor, 0x3e4);
    if (port_forward_esi(&port, entry, 0x438910, child, port_u32(&port, actor, 0x444), ebx, child,
                         actor) != 0)
    {
        port_forward_esi(&port, entry, 0x43c0e0, actor, port_u32(&port, 0, 0x4f8188), ebx, child,
                         actor);
    }
    else
    {
        port_forward_esi(&port, entry, 0x430100, child, 0x456060, ebx, child, actor);
        port_forward_esi(&port, entry, 0x4ac8f0, actor, vertrix_lift_edx, ebx, child, actor);
    }
    return port_return(&port, object_step(&port, child, ebx, child, actor, entry->edi, entry->ebp),
                       entry->edx);
}

/* Original 0x457c10: the walker walks in (0x4aca60, 0x4acab0, 0x4ad530); above row 80 it turns
 * (0x4ad510 with 1 at its place), and takes the hop: +0x24 0, the random (0x4826c0 of
 * 0x598d30 with 8) +0x28 plus 10, +0x64 0, +0x68 1, +0x6c 1, +0x32 2, heights 0 to 80 at 3, shown
 * and the state 0x457d10. 0x457890 last. */
uint32_t vertrix_port_title_walker_enter_457c10(PORT_SIGNATURE)
{
    Port port;
    uint32_t walker = entry->eax;
    uint32_t amount;
    uint32_t ecx;
    uint32_t ebx;
    uint32_t random;
    port_open(&port, calls, services, globals, entry);
    port_forward_esi(&port, entry, 0x4ac500, walker, entry->edx, entry->ebx, entry->ecx, walker);
    if (port_forward_esi(&port, entry, 0x4ac520, walker, vertrix_lift_edx, entry->ebx, entry->ecx,
                         walker) != 1)
    {
        return port_return(&port,
                           port_forward_esi(&port, entry, 0x457890, walker, vertrix_lift_edx,
                                            entry->ebx, entry->ecx, walker),
                           entry->edx);
    }
    amount = port_forward_esi(&port, entry, 0x4ac540, walker, vertrix_lift_edx, entry->ebx,
                              entry->ecx, walker);
    port_forward_esi(&port, entry, 0x4ac5b0, walker, vertrix_lift_edx, entry->ebx, amount, walker);
    port_set16(&port, walker, 0xe, port_u16(&port, walker, 8));
    port_set16(&port, walker, 0x16, port_u16(&port, walker, 0xa));
    port_forward_esi(&port, entry, 0x4aca60, walker, amount, entry->ebx, amount, walker);
    port_forward_esi(&port, entry, 0x4acab0, walker, amount, entry->ebx, amount, walker);
    port_set16(&port, walker, 8, port_u16(&port, walker, 0xe));
    port_set16(&port, walker, 0xa, port_u16(&port, walker, 0x16));
    port_forward_esi(&port, entry, 0x4ad530, walker, amount, entry->ebx, amount, walker);
    ecx = sign16(port_u16(&port, walker, 0xa));
    if ((int32_t)ecx >= 0x50)
    {
        return port_return(&port,
                           port_forward_esi(&port, entry, 0x457890, walker, vertrix_lift_edx,
                                            entry->ebx, ecx, walker),
                           entry->edx);
    }
    ebx = sign16(port_u16(&port, walker, 8));
    port_forward_esi(&port, entry, 0x4ad510, walker, 1, ebx, ecx, walker);
    port_set16(&port, walker, 0x24, 0);
    random = port_forward_esi(&port, entry, 0x4826c0, 0x598d30, 8, ebx, ecx, walker);
    port_set32(&port, walker, 0x64, 0);
    port_set32(&port, walker, 0x68, 1);
    port_set32(&port, walker, 0x6c, 1);
    port_set16(&port, walker, 0x32, 2);
    port_set16(&port, walker, 0x48, 0);
    port_set16(&port, walker, 0x4a, 0x50);
    port_set16(&port, walker, 0x4c, 3);
    port_set16(&port, walker, 0x28, random + 0xa);
    port_set8(&port, walker, 0x93, 1);
    port_forward_esi(&port, entry, 0x4ac8f0, walker, 0x457d10, ebx, ecx, walker);
    return port_return(
        &port, port_forward_esi(&port, entry, 0x457890, walker, vertrix_lift_edx, ebx, ecx, walker),
        entry->edx);
}

/* Original 0x457e40: the walker walks (0x4aca60, 0x4acab0); once both moves are done it turns
 * (0x4ad510 with 160 at its place), +0x30 160, and takes the run: +0x24 0, the random (0x4826c0
 * of 0x598d30 with 8) +0x28 plus 3, +0x70 0, +0x74 1, +0x78 1, +0x32 2, heights 0 at 2, +0x44 0
 * and the state 0x457f40. 0x457890 last. */
uint32_t vertrix_port_title_walker_run_457e40(PORT_SIGNATURE)
{
    Port port;
    uint32_t walker = entry->eax;
    uint32_t amount;
    uint32_t across;
    uint32_t down;
    uint32_t ecx;
    uint32_t ebx;
    uint32_t random;
    port_open(&port, calls, services, globals, entry);
    port_forward_esi(&port, entry, 0x4ac500, walker, entry->edx, entry->ebx, entry->ecx, walker);
    if (port_forward_esi(&port, entry, 0x4ac520, walker, vertrix_lift_edx, entry->ebx, entry->ecx,
                         walker) != 1)
    {
        return port_return(&port,
                           port_forward_esi(&port, entry, 0x457890, walker, vertrix_lift_edx,
                                            entry->ebx, entry->ecx, walker),
                           entry->edx);
    }
    amount = port_forward_esi(&port, entry, 0x4ac540, walker, vertrix_lift_edx, entry->ebx,
                              entry->ecx, walker);
    port_forward_esi(&port, entry, 0x4ac5b0, walker, vertrix_lift_edx, entry->ebx, amount, walker);
    port_set16(&port, walker, 0xe, port_u16(&port, walker, 8));
    port_set16(&port, walker, 0x16, port_u16(&port, walker, 0xa));
    across = port_forward_esi(&port, entry, 0x4aca60, walker, amount, entry->ebx, amount, walker);
    down = port_forward_esi(&port, entry, 0x4acab0, walker, amount, across, amount, walker);
    port_set16(&port, walker, 8, port_u16(&port, walker, 0xe));
    ecx = (amount & 0xffff0000u) | port_u16(&port, walker, 0x16);
    port_set16(&port, walker, 0xa, ecx);
    if (across != 0 || down != 0)
    {
        return port_return(
            &port,
            port_forward_esi(&port, entry, 0x457890, walker, vertrix_lift_edx, across, ecx, walker),
            entry->edx);
    }
    ecx = sign16(port_u16(&port, walker, 0xa));
    ebx = sign16(port_u16(&port, walker, 8));
    port_forward_esi(&port, entry, 0x4ad510, walker, 0xa0, ebx, ecx, walker);
    port_set16(&port, walker, 0x30, 0xa0);
    port_set16(&port, walker, 0x24, 0);
    random = port_forward_esi(&port, entry, 0x4826c0, 0x598d30, 8, ebx, ecx, walker);
    port_set32(&port, walker, 0x70, 0);
    port_set32(&port, walker, 0x74, 1);
    port_set32(&port, walker, 0x78, 1);
    port_set16(&port, walker, 0x32, 2);
    port_set16(&port, walker, 0x48, 0);
    port_set16(&port, walker, 0x4a, 0);
    port_set16(&port, walker, 0x4c, 2);
    port_set16(&port, walker, 0x28, random + 3);
    port_set8(&port, walker, 0x44, 0);
    port_forward_esi(&port, entry, 0x4ac8f0, walker, 0x457f40, ebx, ecx, walker);
    return port_return(
        &port, port_forward_esi(&port, entry, 0x457890, walker, vertrix_lift_edx, ebx, ecx, walker),
        entry->edx);
}

/* The walker's look: the colour of its kind +0x64 and frame +0x58 (0x43f420) as its image
 * (0x4ac950). */
static void walker_look(Port *port, uint32_t walker, uint32_t ebx, uint32_t esi, uint32_t edi,
                        uint32_t ebp)
{
    uint32_t colour =
        port_call_with(port, 0x43f420, (uint32_t)(int32_t)(int8_t)port_u8(port, walker, 0x64),
                       port_u8(port, walker, 0x58), ebx, walker, esi, edi, ebp);
    port_call_with(port, 0x4ac950, walker, colour, ebx, walker, esi, edi, ebp);
}

/* Original 0x4587a0: after 0x457810, when due the walker steps (0x4ac5b0 with 36) and blinks: a
 * random (0x4826c0 of 0x598d30) frame of 0x4fbad0 into +0x58 shown (0x43f420, 0x4ac950); once the
 * blink is done (0x4ad790) it shows its frame +0x5c, waits 20 (0x4ac7d0), takes the state
 * 0x458260, hidden, heights 0 to 100 at 5. 0x457890 last. */
uint32_t vertrix_port_title_walker_blink_4587a0(PORT_SIGNATURE)
{
    Port port;
    uint32_t walker = entry->eax;
    uint32_t amount;
    uint32_t random;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t ebp = entry->ebp;
    port_open(&port, calls, services, globals, entry);
    port_call_with(&port, 0x457810, walker, entry->edx, entry->ebx, walker, esi, edi, ebp);
    port_call_with(&port, 0x4ac500, walker, vertrix_lift_edx, entry->ebx, walker, esi, edi, ebp);
    if (port_call_with(&port, 0x4ac520, walker, vertrix_lift_edx, entry->ebx, walker, esi, edi,
                       ebp) != 1)
    {
        return port_return(&port,
                           port_call_with(&port, 0x457890, walker, vertrix_lift_edx, entry->ebx,
                                          walker, esi, edi, ebp),
                           entry->edx);
    }
    amount = port_call_with(&port, 0x4ac540, walker, vertrix_lift_edx, entry->ebx, walker, esi, edi,
                            ebp);
    port_call_with(&port, 0x4ac5b0, walker, 0x24, amount, walker, esi, edi, ebp);
    random =
        port_call_with(&port, 0x4826c0, 0x598d30, vertrix_lift_edx, amount, walker, esi, edi, ebp);
    port_set32(&port, walker, 0x58, port_u32(&port, (random & 0xffff) * 4, 0x4fbad0));
    walker_look(&port, walker, amount, esi, edi, ebp);
    if (port_call_with(&port, 0x4ad790, walker, amount, amount, walker, esi, edi, ebp) != 0)
    {
        return port_return(&port,
                           port_call_with(&port, 0x457890, walker, vertrix_lift_edx, amount, walker,
                                          esi, edi, ebp),
                           entry->edx);
    }
    port_set32(&port, walker, 0x58, port_u32(&port, walker, 0x5c));
    walker_look(&port, walker, amount, esi, edi, ebp);
    port_call_with(&port, 0x4ac7d0, walker, 0x14, amount, walker, esi, edi, ebp);
    port_call_with(&port, 0x4ac8f0, walker, 0x458260, amount, walker, esi, edi, ebp);
    port_set8(&port, walker, 0x93, 0);
    port_set16(&port, walker, 0x48, 0);
    port_set16(&port, walker, 0x4a, 0x64);
    port_set16(&port, walker, 0x4c, 5);
    return port_return(
        &port,
        port_call_with(&port, 0x457890, walker, vertrix_lift_edx, amount, walker, esi, edi, ebp),
        entry->edx);
}
