#include "drains.h"

/* Player effect states: the board advance, the armed attack, board pairing, the forced choice,
 * slide starts, the cycle, the kind sweep and the drains. */

static uint32_t call_frame(Port *port, uint32_t target, uint32_t eax, uint32_t edx, uint32_t ebx,
                           uint32_t ecx, uint32_t esi, uint32_t edi, uint32_t ebp,
                           const uint32_t *stack, unsigned count)
{
    return port_call_registers(port, target, eax, edx, ebx, ecx, esi, edi, ebp, stack, count);
}

/* The board's method +4 (its draw) with the registers given. */
static uint32_t board_draw(Port *port, uint32_t board, uint32_t ebx, uint32_t ecx, uint32_t esi,
                           uint32_t edi, uint32_t ebp)
{
    uint32_t methods = port_u32(port, board, 0x158);
    return port_call_with(port, port_u32(port, methods, 4), board, methods, ebx, ecx, esi, edi,
                          ebp);
}

/* Original 0x452770: while the player's board (+0x15c) runs (0x4328a0 1) its timer step 0x4ac590
 * on the word +0x1a (at a step 0x4ac510) adds to +0x58; below 24 0x432b10, otherwise 0x432a30
 * and +0x58 keeps what is left over 24. Otherwise the player takes the state 0x451920. Then the
 * board draws. */
uint32_t vertrix_port_state_advance_452770(PORT_SIGNATURE)
{
    Port port;
    uint32_t actor = entry->eax;
    uint32_t board;
    uint32_t ebx = actor;
    uint32_t edi = entry->edi;
    uint32_t esi = entry->esi;
    uint32_t ebp = entry->ebp;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    board = port_u32(&port, actor, 0x15c);
    if (port_call_with(&port, 0x4328a0, board, entry->edx, ebx, board, esi, edi, ebp) != 1)
    {
        port_call_with(&port, 0x4ac8f0, actor, 0x451920, ebx, board, esi, edi, ebp);
        result = board_draw(&port, board, ebx, board, esi, edi, ebp);
        return port_return(&port, result, entry->edx);
    }
    port_call_with(&port, 0x4ac500, board, vertrix_lift_edx, ebx, board, esi, edi, ebp);
    ebx = port_call_with(&port, 0x4ac590, board,
                         (uint32_t)(int32_t)(int16_t)port_u16(&port, board, 0x1a), ebx, board, esi,
                         edi, ebp);
    if (ebx != 0)
    {
        port_call_with(&port, 0x4ac510, board, vertrix_lift_edx, ebx, board, esi, edi, ebp);
        port_set32(&port, board, 0x58, port_u32(&port, board, 0x58) + ebx);
    }
    if ((int32_t)port_u32(&port, board, 0x58) < 0x18)
    {
        port_call_with(&port, 0x432b10, board, vertrix_lift_edx, ebx, board, esi, edi, ebp);
    }
    else
    {
        port_call_with(&port, 0x432a30, board, vertrix_lift_edx, ebx, board, esi, edi, ebp);
        if ((int32_t)port_u32(&port, board, 0x58) >= 0x18)
        {
            edi = port_u32(&port, board, 0x58) % 0x18;
            port_set32(&port, board, 0x58, edi);
        }
    }
    result = board_draw(&port, board, ebx, board, esi, edi, ebp);
    return port_return(&port, result, entry->edx);
}

/* Original 0x452a50: with none of +0x4d0, +0x4d4 and +0x4d8 held, the armed effect +0x3c4 1 or 2
 * aims the target +0x3b4 (0x43a5f0 with 6, -1 and the stack 0, 0, 1 or 1, 0, 1); then the board
 * draws and, when its edx is 1, 0x43bbf0 follows. */
uint32_t vertrix_port_effect_armed_handler_452a50(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x1c
    };
    static const uint32_t first[3] = {0, 0, 1};
    static const uint32_t second[3] = {1, 0, 1};
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t actor = entry->eax;
    uint32_t board;
    uint32_t target;
    uint32_t methods;
    uint32_t edx = 0;
    uint32_t ebx = entry->ebx;
    uint32_t result;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, -0x18u, actor);
    board = port_u32(&port, actor, 0x15c);
    target = port_u32(&port, actor, 0x3b4);
    if (port_u32(&port, actor, 0x4d0) == 0 && port_u32(&port, actor, 0x4d4) == 0 &&
        port_u32(&port, actor, 0x4d8) == 0)
    {
        uint32_t mode = port_u32(&port, actor, 0x3c4);
        if (mode == 1)
        {
            ebx = 0xffffffffu;
            call_frame(&port, 0x43a5f0, target, ebx, ebx, 6, target, board, ebp, first, 3);
        }
        else if (mode == 2)
        {
            ebx = 0xffffffffu;
            call_frame(&port, 0x43a5f0, target, 6, ebx, 6, target, board, ebp, second, 3);
        }
        edx = 1;
    }
    methods = port_u32(&port, board, 0x158);
    result = port_call_with(&port, port_u32(&port, methods, 4), board, edx, ebx, methods, target,
                            board, ebp);
    if (vertrix_lift_edx != 1)
    {
        return port_return(&port, result, entry->edx);
    }
    result = port_call_with(&port, 0x43bbf0, port_u32(&port, ebp, -0x18u), 1, ebx, methods, target,
                            board, ebp);
    return port_return(&port, result, entry->edx);
}

/* Original 0x4533b0: once both boards (the player's and the opponent's) take the state 0x44c860
 * (0x42eca0, 0x42ecc0) 0x42ebe0 settles each; the board draws and then 0x43bbf0 follows for the
 * player and the opponent. */
uint32_t vertrix_port_state_pair_4533b0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x1c
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t actor = entry->eax;
    uint32_t opponent;
    uint32_t board;
    uint32_t other;
    uint32_t methods;
    uint32_t result;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    opponent = port_u32(&port, actor, 0x3b0);
    board = port_u32(&port, actor, 0x15c);
    port_set32(&port, ebp, -0x18u, 0);
    other = port_u32(&port, opponent, 0x15c);
    if (port_call_with(&port, 0x42eca0, board, 0x44c860, other, board, opponent, actor, ebp) != 0 &&
        port_call_with(&port, 0x42ecc0, board, 0x44c860, other, board, opponent, actor, ebp) != 0 &&
        port_call_with(&port, 0x42eca0, other, 0x44c860, other, board, opponent, actor, ebp) != 0 &&
        port_call_with(&port, 0x42ecc0, other, 0x44c860, other, board, opponent, actor, ebp) != 0)
    {
        port_call_with(&port, 0x42ebe0, board, vertrix_lift_edx, other, board, opponent, actor,
                       ebp);
        port_call_with(&port, 0x42ebe0, other, vertrix_lift_edx, 1, board, opponent, actor, ebp);
        port_set32(&port, ebp, -0x18u, 1);
    }
    methods = port_u32(&port, board, 0x158);
    result = port_call_with(&port, port_u32(&port, methods, 4), board, vertrix_lift_edx, methods,
                            board, opponent, actor, ebp);
    if (port_u32(&port, ebp, -0x18u) != 1)
    {
        return port_return(&port, result, entry->edx);
    }
    port_call_with(&port, 0x43bbf0, actor, vertrix_lift_edx, methods, board, opponent, actor, ebp);
    result = port_call_with(&port, 0x43bbf0, opponent, vertrix_lift_edx, methods, board, opponent,
                            actor, ebp);
    return port_return(&port, result, entry->edx);
}

/* Original 0x453ad0: the forced choice: when 0x429fe0 picks a place on the opponent's +0x3b8
 * (column and row into the frame) 0x43acd0, the opponent's +0x194 and +0x198 take it, 0x43bb60
 * with 0x451f10, 0x4ac8f0 and its board's +0xb80, +0xb84 and +0xb88 are 1; otherwise 0x43ac00.
 * Then the board draws and 0x43bbf0. */
uint32_t vertrix_port_effect_forced_choice_453ad0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x28
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t actor = entry->eax;
    uint32_t opponent;
    uint32_t other;
    uint32_t board;
    uint32_t methods;
    uint32_t result;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    opponent = port_u32(&port, actor, 0x3b0);
    port_set32(&port, ebp, -0x24u, actor);
    port_set32(&port, ebp, -0x20u, port_u32(&port, actor, 0x15c));
    other = port_u32(&port, opponent, 0x15c);
    if (port_call_with(&port, 0x429fe0, port_u32(&port, opponent, 0x3b8), ebp - 0x1c, ebp - 0x18,
                       actor, opponent, other, ebp) == 1)
    {
        port_call_with(&port, 0x43acd0, actor, vertrix_lift_edx, ebp - 0x18, actor, opponent, other,
                       ebp);
        port_set32(&port, opponent, 0x194, port_u8(&port, ebp, -0x1cu));
        port_set32(&port, opponent, 0x198, port_u8(&port, ebp, -0x18u));
        port_call_with(&port, 0x43bb60, opponent, 0x451f10, ebp - 0x18, actor, opponent, other,
                       ebp);
        port_call_with(&port, 0x4ac8f0, opponent, vertrix_lift_edx, ebp - 0x18, actor, opponent,
                       other, ebp);
        port_set32(&port, other, 0xb80, 1);
        port_set32(&port, other, 0xb84, 1);
        port_set32(&port, other, 0xb88, 1);
    }
    else
    {
        port_call_with(&port, 0x43ac00, actor, vertrix_lift_edx, ebp - 0x18, actor, opponent, other,
                       ebp);
    }
    board = port_u32(&port, ebp, -0x20u);
    methods = port_u32(&port, board, 0x158);
    port_call_with(&port, port_u32(&port, methods, 4), board, methods, ebp - 0x18, actor, opponent,
                   other, ebp);
    result = port_call_with(&port, 0x43bbf0, port_u32(&port, ebp, -0x24u), vertrix_lift_edx,
                            ebp - 0x18, actor, opponent, other, ebp);
    return port_return(&port, result, entry->edx);
}

/* The slide start of 0x453c90, 0x453fd0 and 0x4542e0: when `fit` takes the player's place (the
 * dwords at `place` and after) the board's speed is that of the level 0x532bbc (0x4ac7b0 with
 * `speeds`), its word `field` the start of `starts`, +0x58 0, 0x4ac510 with `next`, the player
 * 0x4ac8f0 and the sound 0x4f8188 (0x43c0e0); otherwise 0x43bbf0 follows the board's draw. */
static uint32_t effect_slide_start(PORT_SIGNATURE, uint32_t fit, uint32_t place, uint32_t speeds,
                                   uint32_t starts, uint32_t field, uint32_t next)
{
    enum
    {
        BELOW = 0x1c
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t actor = entry->eax;
    uint32_t board;
    uint32_t ebx;
    uint32_t esi;
    uint32_t result;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    board = port_u32(&port, actor, 0x15c);
    ebx = port_u32(&port, actor, place + 4);
    port_set32(&port, ebp, -0x18u, 0);
    if (port_call_with(&port, fit, board, port_u32(&port, actor, place), ebx, board, actor, actor,
                       ebp) == 1)
    {
        port_call_with(&port, 0x4ac7b0, board,
                       port_u32(&port, port_u32(&port, 0, 0x532bbc) * 4, speeds), ebx, board, actor,
                       actor, ebp);
        port_set16(&port, board, field, port_u16(&port, port_u32(&port, 0, 0x532bbc) * 4, starts));
        port_set32(&port, board, 0x58, 0);
        port_call_with(&port, 0x4ac510, board, next, ebx, board, actor, actor, ebp);
        port_call_with(&port, 0x4ac8f0, actor, vertrix_lift_edx, ebx, board, actor, actor, ebp);
        port_call_with(&port, 0x43c0e0, actor, port_u32(&port, 0, 0x4f8188), ebx, board, actor,
                       actor, ebp);
    }
    else
    {
        port_set32(&port, ebp, -0x18u, 1);
    }
    esi = port_u32(&port, ebp, -0x18u);
    result = board_draw(&port, board, ebx, board, esi, actor, ebp);
    if (esi != 1)
    {
        return port_return(&port, result, entry->edx);
    }
    result = port_call_with(&port, 0x43bbf0, actor, vertrix_lift_edx, ebx, board, esi, actor, ebp);
    return port_return(&port, result, entry->edx);
}

/* Original 0x453c90: fit 0x4314a0 at +0x424, speeds 0x4f7c0c, starts 0x4f7c18 into +0x1a, next
 * 0x453d50. */
uint32_t vertrix_port_effect_slide_start_453c90(PORT_SIGNATURE)
{
    return effect_slide_start(calls, services, globals, entry, 0x4314a0, 0x424, 0x4f7c0c, 0x4f7c18,
                              0x1a, 0x453d50);
}

/* Original 0x453fd0: fit 0x431780 at +0x42c, speeds 0x4f7c3c, starts 0x4f7c48 into +0x12, next
 * 0x454090. */
uint32_t vertrix_port_effect_slide_start_453fd0(PORT_SIGNATURE)
{
    return effect_slide_start(calls, services, globals, entry, 0x431780, 0x42c, 0x4f7c3c, 0x4f7c48,
                              0x12, 0x454090);
}

/* Original 0x4542e0: fit 0x431930 at +0x42c, speeds 0x4f7c3c, starts 0x4f7c48 into +0x12, next
 * 0x4543a0. */
uint32_t vertrix_port_effect_slide_start_4542e0(PORT_SIGNATURE)
{
    return effect_slide_start(calls, services, globals, entry, 0x431930, 0x42c, 0x4f7c3c, 0x4f7c48,
                              0x12, 0x4543a0);
}

/* Original 0x4546a0: when the board is due and 0x4ad750 is done its +0x64 is 0 and, with the
 * player's +0x3ec 1, 0x438c60 with the byte +0x448, which steps on (wrapping at 10). Unless
 * 0x43b970 holds, 0x438b90 with the byte +0x3ec and the state 0x454760. Then the board draws. */
uint32_t vertrix_port_state_cycle_4546a0(PORT_SIGNATURE)
{
    Port port;
    uint32_t actor = entry->eax;
    uint32_t board;
    uint32_t edi = entry->edi;
    uint32_t ebp = entry->ebp;
    uint32_t amount;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    board = port_u32(&port, actor, 0x15c);
    port_call_with(&port, 0x4ac500, board, entry->edx, actor, board, actor, edi, ebp);
    if (port_call_with(&port, 0x4ac520, board, vertrix_lift_edx, actor, board, actor, edi, ebp) ==
        1)
    {
        amount =
            port_call_with(&port, 0x4ac540, board, vertrix_lift_edx, actor, board, actor, edi, ebp);
        port_call_with(&port, 0x4ac5b0, board, amount, actor, board, actor, edi, ebp);
        if (port_call_with(&port, 0x4ad750, board, vertrix_lift_edx, actor, board, actor, edi,
                           ebp) == 0)
        {
            port_set32(&port, board, 0x64, 0);
            if (port_u32(&port, actor, 0x3ec) == 1)
            {
                port_call_with(&port, 0x438c60, board, port_u8(&port, actor, 0x448), actor, board,
                               actor, edi, ebp);
                edi = port_u32(&port, actor, 0x448) + 1;
                port_set32(&port, actor, 0x448, edi);
                if ((int32_t)edi >= 0xa)
                {
                    port_set32(&port, actor, 0x448, 0);
                }
            }
        }
    }
    if (port_call_with(&port, 0x43b970, actor, vertrix_lift_edx, actor, board, actor, edi, ebp) ==
        0)
    {
        port_call_with(&port, 0x438b90, board, port_u8(&port, actor, 0x3ec), actor, board, actor,
                       edi, ebp);
        port_call_with(&port, 0x4ac8f0, actor, 0x454760, actor, board, actor, edi, ebp);
    }
    result = board_draw(&port, board, actor, board, actor, edi, ebp);
    return port_return(&port, result, entry->edx);
}

/* Original 0x454830: the board's kinds are marked for the player's effect +0x434 (0x435e80);
 * when 0x436150 finds them the board's speed is that of the level (0x4f7c54), 0x4ac510 with
 * 0x4548e0, the player 0x4ac8f0 with the sound 0x4f8190 and the opponent 0x43ac00; otherwise the
 * opponent 0x43acd0 and 0x43bbf0 follows the board's draw. */
uint32_t vertrix_port_effect_kind_sweep_454830(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x1c
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t actor = entry->eax;
    uint32_t board;
    uint32_t opponent;
    uint32_t edi = 0;
    uint32_t result;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, -0x18u, actor);
    board = port_u32(&port, actor, 0x15c);
    opponent = port_u32(&port, actor, 0x3b0);
    port_call_with(&port, 0x435e80, board, port_u32(&port, actor, 0x434), actor, board, opponent,
                   entry->edi, ebp);
    if (port_call_with(&port, 0x436150, board, vertrix_lift_edx, actor, board, opponent, edi,
                       ebp) == 1)
    {
        port_call_with(&port, 0x4ac7b0, board,
                       port_u32(&port, port_u32(&port, 0, 0x532bbc) * 4, 0x4f7c54), actor, board,
                       opponent, edi, ebp);
        port_call_with(&port, 0x4ac510, board, 0x4548e0, actor, board, opponent, edi, ebp);
        port_call_with(&port, 0x4ac8f0, actor, vertrix_lift_edx, actor, board, opponent, edi, ebp);
        port_call_with(&port, 0x43c0e0, actor, port_u32(&port, 0, 0x4f8190), actor, board, opponent,
                       edi, ebp);
        port_call_with(&port, 0x43ac00, opponent, vertrix_lift_edx, actor, board, opponent, edi,
                       ebp);
    }
    else
    {
        edi = 1;
        port_call_with(&port, 0x43acd0, opponent, vertrix_lift_edx, actor, board, opponent, edi,
                       ebp);
    }
    result = board_draw(&port, board, actor, board, opponent, edi, ebp);
    if (edi != 1)
    {
        return port_return(&port, result, entry->edx);
    }
    result = port_call_with(&port, 0x43bbf0, port_u32(&port, ebp, -0x18u), vertrix_lift_edx, actor,
                            board, opponent, edi, ebp);
    return port_return(&port, result, entry->edx);
}

/* The drain of 0x454b20 and 0x454d80: when the board is due, while its step lasts, the player's
 * count +0x438 is above 0 and `take` with 5 holds, the count drops with the sound 0x4f8194
 * (0x43c0e0); with step left the player takes `next`. Then the board draws. */
static uint32_t state_drain(PORT_SIGNATURE, uint32_t take, uint32_t next)
{
    Port port;
    uint32_t actor = entry->eax;
    uint32_t board;
    uint32_t ebx = entry->ebx;
    uint32_t edi = entry->edi;
    uint32_t ebp = entry->ebp;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    board = port_u32(&port, actor, 0x15c);
    port_call_with(&port, 0x4ac500, board, entry->edx, ebx, actor, board, edi, ebp);
    if (port_call_with(&port, 0x4ac520, board, vertrix_lift_edx, ebx, actor, board, edi, ebp) == 1)
    {
        ebx = port_call_with(&port, 0x4ac540, board, vertrix_lift_edx, ebx, actor, board, edi, ebp);
        port_call_with(&port, 0x4ac5b0, board, ebx, ebx, actor, board, edi, ebp);
        if (vertrix_lift_edx != 0)
        {
            while ((int32_t)port_u32(&port, actor, 0x438) > 0 &&
                   port_call_with(&port, take, board, 5, ebx, actor, board, edi, ebp) == 1)
            {
                edi = port_u32(&port, actor, 0x438) - 1;
                ebx--;
                port_set32(&port, actor, 0x438, edi);
                port_call_with(&port, 0x43c0e0, actor, port_u32(&port, 0, 0x4f8194), ebx, actor,
                               board, edi, ebp);
                if (ebx == 0)
                {
                    break;
                }
            }
        }
        if (ebx != 0)
        {
            port_call_with(&port, 0x4ac8f0, actor, next, ebx, actor, board, edi, ebp);
        }
    }
    result = board_draw(&port, board, ebx, actor, board, edi, ebp);
    return port_return(&port, result, entry->edx);
}

/* Original 0x454b20: take 0x436440, next 0x454bd0. */
uint32_t vertrix_port_state_drain_454b20(PORT_SIGNATURE)
{
    return state_drain(calls, services, globals, entry, 0x436440, 0x454bd0);
}

/* Original 0x454d80: take 0x4365c0, next 0x454e30. */
uint32_t vertrix_port_state_drain_454d80(PORT_SIGNATURE)
{
    return state_drain(calls, services, globals, entry, 0x4365c0, 0x454e30);
}

/* Original 0x454f00: after 0x436850, when 0x436720 with 5 holds the board's speed is that of the
 * level (0x4f7c6c), 0x4ac510 with 0x454fc0, the player 0x4ac8f0 with the sound 0x4f8194 and the
 * opponent 0x43ac00; otherwise the opponent 0x43acd0 and 0x43bbf0 follows the board's draw. */
uint32_t vertrix_port_effect_kind_take_454f00(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x1c
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t actor = entry->eax;
    uint32_t board;
    uint32_t opponent;
    uint32_t ebx = actor;
    uint32_t esi;
    uint32_t result;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    board = port_u32(&port, actor, 0x15c);
    opponent = port_u32(&port, actor, 0x3b0);
    port_set32(&port, ebp, -0x18u, 0);
    port_call_with(&port, 0x436850, board, 0, ebx, board, opponent, actor, ebp);
    if (port_call_with(&port, 0x436720, board, 5, ebx, board, opponent, actor, ebp) == 1)
    {
        port_call_with(&port, 0x4ac7b0, board,
                       port_u32(&port, port_u32(&port, 0, 0x532bbc) * 4, 0x4f7c6c), ebx, board,
                       opponent, actor, ebp);
        port_call_with(&port, 0x4ac510, board, 0x454fc0, ebx, board, opponent, actor, ebp);
        port_call_with(&port, 0x4ac8f0, actor, vertrix_lift_edx, ebx, board, opponent, actor, ebp);
        port_call_with(&port, 0x43c0e0, actor, port_u32(&port, 0, 0x4f8194), ebx, board, opponent,
                       actor, ebp);
        port_call_with(&port, 0x43ac00, opponent, vertrix_lift_edx, ebx, board, opponent, actor,
                       ebp);
    }
    else
    {
        ebx = 1;
        port_call_with(&port, 0x43acd0, opponent, vertrix_lift_edx, ebx, board, opponent, actor,
                       ebp);
        port_set32(&port, ebp, -0x18u, 1);
    }
    esi = port_u32(&port, ebp, -0x18u);
    result = board_draw(&port, board, ebx, board, esi, actor, ebp);
    if (esi != 1)
    {
        return port_return(&port, result, entry->edx);
    }
    result = port_call_with(&port, 0x43bbf0, actor, vertrix_lift_edx, ebx, board, esi, actor, ebp);
    return port_return(&port, result, entry->edx);
}
