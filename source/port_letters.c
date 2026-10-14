#include "port_letters.h"

/* The board settle end, the slide begin, an actor's move end, the kind light, the fade sound, the
 * title letter restarts, the place pick and the child bobs. */

/* The guard record (0x4ec1ec, `guard`) of a frame routine at `record`. */
static void guard_record(Port *port, uint32_t record, uint32_t guard)
{
    port_set32(port, record, 0, port->env.chain);
    port_set32(port, record, 4, 0x4ec1ec);
    port_set32(port, record, 8, guard);
    port_set32(port, record, 0xc, 0);
}

static uint32_t sign16(uint32_t value)
{
    return (uint32_t)(int32_t)(int16_t)value;
}

/* The board's method +4 (its draw) with the registers given. */
static uint32_t board_draw(Port *port, uint32_t board, uint32_t ebx, uint32_t ecx, uint32_t esi,
                           uint32_t edi, uint32_t ebp)
{
    uint32_t methods = port_u32(port, board, 0x158);
    return port_call_with(port, port_u32(port, methods, 4), board, methods, ebx, ecx, esi, edi,
                          ebp);
}

/* Original 0x455830: when the board is due 0x437b70; once it takes the state 0x44c860 (0x42eca0,
 * 0x42ecc0) 0x42ebe0 settles it and, after its draw, 0x43bbf0 with 0x452160, 0x4ac8f0 and
 * 0x43bae0 with 1 end the player's turn (+0x184 0, the board's +0xb8c 0). */
uint32_t vertrix_port_board_settle_end_455830(PORT_SIGNATURE)
{
    Port port;
    uint32_t actor = entry->eax;
    uint32_t board;
    uint32_t esi = 0;
    uint32_t edi = entry->edi;
    uint32_t ebp = entry->ebp;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    board = port_u32(&port, actor, 0x15c);
    port_call_with(&port, 0x4ac500, board, entry->edx, actor, board, entry->esi, edi, ebp);
    if (port_call_with(&port, 0x4ac520, board, vertrix_lift_edx, actor, board, esi, edi, ebp) == 1)
    {
        port_call_with(&port, 0x4ac540, board, vertrix_lift_edx, actor, board, esi, edi, ebp);
        port_call_with(&port, 0x4ac5b0, board, vertrix_lift_edx, actor, board, esi, edi, ebp);
        port_call_with(&port, 0x437b70, board, vertrix_lift_edx, actor, board, esi, edi, ebp);
    }
    if (port_call_with(&port, 0x42eca0, board, 0x44c860, actor, board, esi, edi, ebp) != 0 &&
        port_call_with(&port, 0x42ecc0, board, 0x44c860, actor, board, esi, edi, ebp) != 0)
    {
        esi = 1;
        port_call_with(&port, 0x42ebe0, board, vertrix_lift_edx, actor, board, esi, edi, ebp);
    }
    result = board_draw(&port, board, actor, board, esi, edi, ebp);
    if (esi != 1)
    {
        return port_return(&port, result, entry->edx);
    }
    port_call_with(&port, 0x43bbf0, actor, 0x452160, actor, board, esi, edi, ebp);
    port_call_with(&port, 0x4ac8f0, actor, vertrix_lift_edx, actor, board, esi, edi, ebp);
    result = port_call_with(&port, 0x43bae0, actor, esi, actor, board, esi, edi, ebp);
    port_set32(&port, actor, 0x184, 0);
    port_set32(&port, board, 0xb8c, 0);
    return port_return(&port, result, entry->edx);
}

/* Original 0x455e50: the slide begin (+0x444 0): when 0x438910 takes the player's +0x3e4 the
 * board's speed is that of the level 0x532bbc (0x4f7cfc), its +0x1a the start of 0x4f7d08, +0x58
 * 0, 0x4ac510 with 0x455f10, then the player 0x4ac8f0 and 0x43d2b0 and the board 0x4300b0;
 * otherwise 0x43acd0 and 0x43bbf0 follows the board's draw. */
uint32_t vertrix_port_effect_slide_begin_455e50(PORT_SIGNATURE)
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
    uint32_t edi = 0;
    uint32_t result;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, -0x18u, actor);
    board = port_u32(&port, actor, 0x15c);
    ebx = port_u32(&port, actor, 0x3e4);
    port_set32(&port, actor, 0x444, 0);
    if (port_call_with(&port, 0x438910, board, 0, ebx, board, actor, edi, ebp) == 1)
    {
        port_call_with(&port, 0x4ac7b0, board,
                       port_u32(&port, port_u32(&port, 0, 0x532bbc) * 4, 0x4f7cfc), ebx, board,
                       actor, edi, ebp);
        port_set16(&port, board, 0x1a, port_u16(&port, port_u32(&port, 0, 0x532bbc) * 4, 0x4f7d08));
        port_set32(&port, board, 0x58, 0);
        port_call_with(&port, 0x4ac510, board, 0x455f10, ebx, board, actor, edi, ebp);
        port_call_with(&port, 0x4ac8f0, actor, vertrix_lift_edx, ebx, board, actor, edi, ebp);
        port_call_with(&port, 0x43d2b0, actor, vertrix_lift_edx, ebx, board, actor, edi, ebp);
        port_call_with(&port, 0x4300b0, board, vertrix_lift_edx, ebx, board, actor, edi, ebp);
    }
    else
    {
        edi = 1;
        port_call_with(&port, 0x43acd0, actor, vertrix_lift_edx, ebx, board, actor, edi, ebp);
    }
    result = board_draw(&port, board, ebx, board, actor, edi, ebp);
    if (edi != 1)
    {
        return port_return(&port, result, entry->edx);
    }
    result = port_call_with(&port, 0x43bbf0, port_u32(&port, ebp, -0x18u), vertrix_lift_edx, ebx,
                            board, actor, edi, ebp);
    return port_return(&port, result, entry->edx);
}

/* Original 0x4560c0: the actor's mode 1 (0x4ac7b0); when due it moves (0x4aca60, 0x4acab0,
 * 0x4acb00 with the step) and once all three are done takes the state 0x456170 and mode 2. When
 * 0x4b5500 holds its +0x14c goes to 0x532a60 and is returned. */
uint32_t vertrix_port_actor_move_end_4560c0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x1c
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t actor = entry->eax;
    uint32_t amount;
    uint32_t first;
    uint32_t last;
    uint32_t result;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_call_with(&port, 0x4ac7b0, actor, 1, entry->ebx, actor, actor, entry->edi, ebp);
    port_call_with(&port, 0x4ac500, actor, vertrix_lift_edx, entry->ebx, actor, actor, entry->edi,
                   ebp);
    result = port_call_with(&port, 0x4ac520, actor, vertrix_lift_edx, entry->ebx, actor, actor,
                            entry->edi, ebp);
    if (result != 1)
    {
        return port_return(&port, result, entry->edx);
    }
    amount = port_call_with(&port, 0x4ac540, actor, vertrix_lift_edx, entry->ebx, actor, actor,
                            entry->edi, ebp);
    port_call_with(&port, 0x4ac5b0, actor, vertrix_lift_edx, amount, actor, actor, entry->edi, ebp);
    first = port_call_with(&port, 0x4aca60, actor, amount, amount, actor, actor, entry->edi, ebp);
    port_set32(&port, ebp, -0x18u,
               port_call_with(&port, 0x4acab0, actor, amount, amount, actor, actor, first, ebp));
    last = port_call_with(&port, 0x4acb00, actor, amount, amount, actor, actor, first, ebp);
    if (first == 0 && port_u32(&port, ebp, -0x18u) == 0 && last == 0)
    {
        port_call_with(&port, 0x4ac8f0, actor, 0x456170, amount, actor, actor, first, ebp);
        port_call_with(&port, 0x4ac7b0, actor, 2, amount, actor, actor, first, ebp);
    }
    result =
        port_call_with(&port, 0x4b5500, actor, vertrix_lift_edx, amount, actor, actor, first, ebp);
    if (result != 0)
    {
        result = port_u32(&port, actor, 0x14c);
        port_set32(&port, 0, 0x532a60, result);
    }
    return port_return(&port, result, entry->edx);
}

/* Original 0x456bf0: the kind light: the actor's byte +0x15c or +0x15d 1 puts it out (+0x48 0,
 * 0x4adfe0) with the state 0x456a00 or 0x456a80; otherwise its player's (+4, 0x540f88) board's
 * +0xb78 kind (0x42b070) matching +0x64 lights it (+0x48 20) and any other puts it out. */
uint32_t vertrix_port_actor_kind_light_456bf0(PORT_SIGNATURE)
{
    Port port;
    uint32_t actor = entry->eax;
    uint32_t value;
    uint32_t edx = entry->edx;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    if (port_u8(&port, actor, 0x15c) == 1 || port_u8(&port, actor, 0x15d) == 1)
    {
        uint32_t next = port_u8(&port, actor, 0x15c) == 1 ? 0x456a00 : 0x456a80;
        port_set16(&port, actor, 0x48, 0);
        port_forward(&port, entry, 0x4adfe0, actor, next, entry->ebx, actor);
        result = port_forward(&port, entry, 0x4ac8f0, actor, vertrix_lift_edx, entry->ebx, actor);
        return port_return(&port, result, entry->edx);
    }
    value = port_u32(&port, port_u32(&port, port_u32(&port, actor, 4) * 4, 0x540f88), 0x15c);
    value = port_u32(&port, value, 0xb78);
    if (value != 0)
    {
        value = port_forward(&port, entry, 0x42b070, value, entry->edx, entry->ebx, actor);
        edx = vertrix_lift_edx;
        if (value == port_u32(&port, actor, 0x64))
        {
            if (port_u16(&port, actor, 0x48) != 0)
            {
                return port_return(&port, value, entry->edx);
            }
            port_set16(&port, actor, 0x48, 0x14);
            result = port_forward(&port, entry, 0x4adfe0, actor, edx, entry->ebx, actor);
            return port_return(&port, result, entry->edx);
        }
    }
    if (port_u16(&port, actor, 0x48) == 0)
    {
        return port_return(&port, value, entry->edx);
    }
    port_set16(&port, actor, 0x48, 0);
    result = port_forward(&port, entry, 0x4adfe0, actor, edx, entry->ebx, actor);
    return port_return(&port, result, entry->edx);
}

/* Original 0x456cd0: when due the actor bobs to -200 at speed 1 (0x4ad530, which when done clears
 * its state) and its height +0x48 sets the music (0x478b40) and sound (0x4828f0) volumes: 0x532b98
 * and 0x532b9c scaled by 100 plus the height over 2, in hundredths. */
uint32_t vertrix_port_actor_fade_volume_456cd0(PORT_SIGNATURE)
{
    Port port;
    uint32_t actor = entry->eax;
    uint32_t amount;
    uint32_t share;
    uint32_t volume;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    port_forward(&port, entry, 0x4ac500, actor, entry->edx, actor, actor);
    result = port_forward(&port, entry, 0x4ac520, actor, vertrix_lift_edx, actor, actor);
    if (result != 1)
    {
        return port_return(&port, result, entry->edx);
    }
    amount = port_forward(&port, entry, 0x4ac540, actor, vertrix_lift_edx, actor, actor);
    port_forward(&port, entry, 0x4ac5b0, actor, amount, actor, actor);
    port_set16(&port, actor, 0x4a, 0xff38);
    port_set16(&port, actor, 0x4c, 1);
    if (port_forward(&port, entry, 0x4ad530, actor, vertrix_lift_edx, actor, actor) == 0)
    {
        port_forward(&port, entry, 0x4ac8f0, actor, 0, actor, actor);
    }
    share = 0x64 - (uint32_t)((int32_t)(sign16(port_u16(&port, actor, 0x48)) * 0x64) / -200);
    volume = port_u32(&port, 0, 0x532b98) * share;
    port_forward(&port, entry, 0x478b40, volume / 0x64, volume % 0x64, 0x64, share);
    volume = port_u32(&port, 0, 0x532b9c) * share;
    result = port_forward(&port, entry, 0x4828f0, volume / 0x64, volume % 0x64, 0x64, share);
    return port_return(&port, result, entry->edx);
}

/* Original 0x459e00: the title letter (guarded 0x515374), when due and its bob 0x4ad530 is done,
 * returns to its place (0x4ad510 with 1 and the words +8 and +0xa), +0x24 0, 0x4ac510, +0x48 0,
 * +0x4a 150, +0x4c 1 and the state 0x459ec0; then 0x457890. */
uint32_t vertrix_port_title_letter_restart_459e00(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x28
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t actor = entry->eax;
    uint32_t guard = 0x515374;
    uint32_t ebx = 0;
    uint32_t ecx = guard;
    uint32_t amount;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    guard_record(&port, ebp - 0x24, guard);
    port_call_with(&port, 0x4ac500, actor, 0x4ec1ec, ebx, ecx, actor, entry->edi, ebp);
    if (port_call_with(&port, 0x4ac520, actor, vertrix_lift_edx, ebx, ecx, actor, entry->edi,
                       ebp) == 1)
    {
        amount = port_call_with(&port, 0x4ac540, actor, vertrix_lift_edx, ebx, ecx, actor,
                                entry->edi, ebp);
        port_call_with(&port, 0x4ac5b0, actor, amount, ebx, ecx, actor, entry->edi, ebp);
        if (port_call_with(&port, 0x4ad530, actor, vertrix_lift_edx, ebx, ecx, actor, entry->edi,
                           ebp) == 0)
        {
            ecx = sign16(port_u16(&port, actor, 0xa));
            ebx = sign16(port_u16(&port, actor, 8));
            port_call_with(&port, 0x4ad510, actor, 1, ebx, ecx, actor, entry->edi, ebp);
            port_set16(&port, actor, 0x24, 0);
            port_call_with(&port, 0x4ac510, actor, vertrix_lift_edx, ebx, ecx, actor, entry->edi,
                           ebp);
            port_set16(&port, actor, 0x48, 0);
            port_set16(&port, actor, 0x4a, 0x96);
            port_set16(&port, actor, 0x4c, 1);
            port_call_with(&port, 0x4ac8f0, actor, 0x459ec0, ebx, ecx, actor, entry->edi, ebp);
        }
    }
    port_call_with(&port, 0x457890, actor, vertrix_lift_edx, ebx, ecx, actor, entry->edi, ebp);
    return port_return(&port, port_u32(&port, ebp, -0x24u), entry->edx);
}

/* Original 0x45a440: the fighting title letter, when due and its bob 0x4ad530 is done, returns
 * to its place (+0x30 160, 0x4ad510 with 1 and the words +8 and +0xa), takes a turn +0x24 below
 * 360 and a spin +0x28 10 more than a draw below 10 (0x4826c0 on 0x598d30), +0x32 2 and the state
 * 0x45a4f0; then 0x457890. */
uint32_t vertrix_port_title_letter_fight_restart_45a440(PORT_SIGNATURE)
{
    Port port;
    uint32_t actor = entry->eax;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t amount;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    port_forward_esi(&port, entry, 0x4ac500, actor, entry->edx, ebx, ecx, actor);
    if (port_forward_esi(&port, entry, 0x4ac520, actor, vertrix_lift_edx, ebx, ecx, actor) == 1)
    {
        amount = port_forward_esi(&port, entry, 0x4ac540, actor, vertrix_lift_edx, ebx, ecx, actor);
        port_forward_esi(&port, entry, 0x4ac5b0, actor, amount, ebx, ecx, actor);
        if (port_forward_esi(&port, entry, 0x4ad530, actor, vertrix_lift_edx, ebx, ecx, actor) == 0)
        {
            ecx = sign16(port_u16(&port, actor, 0xa));
            ebx = sign16(port_u16(&port, actor, 8));
            port_set16(&port, actor, 0x30, 0xa0);
            port_forward_esi(&port, entry, 0x4ad510, actor, 1, ebx, ecx, actor);
            result = port_forward_esi(&port, entry, 0x4826c0, 0x598d30, 0x168, ebx, ecx, actor);
            port_set16(&port, actor, 0x24, result);
            result = port_forward_esi(&port, entry, 0x4826c0, 0x598d30, 0xa, ebx, ecx, actor);
            port_set16(&port, actor, 0x28, result + 0xa);
            port_set16(&port, actor, 0x32, 2);
            port_forward_esi(&port, entry, 0x4ac8f0, actor, 0x45a4f0, ebx, ecx, actor);
        }
    }
    result = port_forward_esi(&port, entry, 0x457890, actor, vertrix_lift_edx, ebx, ecx, actor);
    return port_return(&port, result, entry->edx);
}

/* Original 0x45bad0: unless 0x4393f0 picks the place (+0x404, +0x418, +0x41c) the player takes the
 * state 0x45bb80 with the sound 0x4f81ac when +0x41c is +0x418, otherwise 0x4f81a4; with a pick
 * 0x43bbf0 follows the board's draw. */
uint32_t vertrix_port_player_place_pick_45bad0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x20
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t actor = entry->eax;
    uint32_t board;
    uint32_t ebx;
    uint32_t ecx;
    uint32_t esi;
    uint32_t result;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, -0x1cu, actor);
    board = port_u32(&port, actor, 0x15c);
    port_set32(&port, ebp, -0x18u, 0);
    ecx = actor + 0x418;
    ebx = port_u32(&port, actor, 0x41c);
    if (port_call_with(&port, 0x4393f0, board, actor + 0x404, ebx, ecx, actor, board, ebp) != 0)
    {
        port_set32(&port, ebp, -0x18u, 1);
    }
    else
    {
        uint32_t sound;
        port_call_with(&port, 0x4ac8f0, actor, 0x45bb80, ebx, ecx, actor, board, ebp);
        sound =
            port_u32(&port, actor, 0x41c) == port_u32(&port, actor, 0x418) ? 0x4f81ac : 0x4f81a4;
        port_call_with(&port, 0x43c0e0, actor, port_u32(&port, 0, sound), ebx, ecx, actor, board,
                       ebp);
    }
    esi = port_u32(&port, ebp, -0x18u);
    result = board_draw(&port, board, ebx, ecx, esi, board, ebp);
    if (esi != 1)
    {
        return port_return(&port, result, entry->edx);
    }
    result = port_call_with(&port, 0x43bbf0, port_u32(&port, ebp, -0x1cu), vertrix_lift_edx, ebx,
                            ecx, esi, board, ebp);
    return port_return(&port, result, entry->edx);
}

/* The child bob of 0x45cc40 and 0x45cd00 (guarded `guard`): when due the child +0x160 bobs to
 * `height` (0x4ad530), which when done hands over to `next`; when 0x4b4500 holds 0x45c9a0. */
static uint32_t actor_child_bob(PORT_SIGNATURE, uint32_t guard, uint32_t height, uint32_t next)
{
    enum
    {
        BELOW = 0x28
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t actor = entry->eax;
    uint32_t child;
    uint32_t amount;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    guard_record(&port, ebp - 0x24, guard);
    child = port_u32(&port, actor, 0x160);
    port_call_with(&port, 0x4ac500, actor, 0x4ec1ec, child, actor, 0, entry->edi, ebp);
    if (port_call_with(&port, 0x4ac520, actor, vertrix_lift_edx, child, actor, actor, entry->edi,
                       ebp) == 1)
    {
        amount = port_call_with(&port, 0x4ac540, actor, vertrix_lift_edx, child, actor, actor,
                                entry->edi, ebp);
        port_call_with(&port, 0x4ac5b0, actor, amount, child, actor, actor, entry->edi, ebp);
        port_set16(&port, child, 0x4a, height);
        if (port_call_with(&port, 0x4ad530, child, vertrix_lift_edx, child, actor, actor,
                           entry->edi, ebp) == 0)
        {
            port_call_with(&port, 0x4ac8f0, actor, next, child, actor, actor, entry->edi, ebp);
        }
    }
    if (port_call_with(&port, 0x4b4500, actor, vertrix_lift_edx, child, actor, actor, entry->edi,
                       ebp) == 1)
    {
        port_call_with(&port, 0x45c9a0, actor, vertrix_lift_edx, child, actor, actor, entry->edi,
                       ebp);
    }
    return port_return(&port, port_u32(&port, ebp, -0x24u), entry->edx);
}

/* Original 0x45cc40: guard 0x5153a8, height -20, next 0x45cd00. */
uint32_t vertrix_port_actor_child_bob_45cc40(PORT_SIGNATURE)
{
    return actor_child_bob(calls, services, globals, entry, 0x5153a8, 0xffec, 0x45cd00);
}

/* Original 0x45cd00: guard 0x5153ac, height -60, next 0x45cc40. */
uint32_t vertrix_port_actor_child_bob_45cd00(PORT_SIGNATURE)
{
    return actor_child_bob(calls, services, globals, entry, 0x5153ac, 0xffc4, 0x45cc40);
}
