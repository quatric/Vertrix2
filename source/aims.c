#include "aims.h"

/* The aimed throws, waves, blinks and slides of the title letters, the score step, the key wait
 * of the menu and the label box. */

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

/* The aim at the screen centre (320, 240) from the letter's place (+8, +0xa): the distance
 * (0x484680) as the turn (0x4ad510) and the angle (0x484700) in degrees into +0x24. `edi` is the
 * register the routine holds. */
static void letter_aim(Port *port, uint32_t letter, uint32_t edi, uint32_t ebp, int store)
{
    uint32_t distance;
    uint32_t angle;
    if (store)
    {
        port_set32(port, ebp, -0x18u, edi == 0x140 ? 0xf0 : 0x140);
    }
    distance = port_call_with(port, 0x484680, 0x140, 0xf0, sign16(port_u16(port, letter, 8)),
                              sign16(port_u16(port, letter, 0xa)), letter, edi, ebp);
    port_call_with(port, 0x4ad510, letter, sign16(distance), 0x140, 0xf0, letter, edi, ebp);
    angle = port_call_with(port, 0x484700, 0x140, 0xf0, sign16(port_u16(port, letter, 8)),
                           sign16(port_u16(port, letter, 0xa)), letter, edi, ebp);
    port_set16(port, letter, 0x24, angle);
    port_set16(port, letter, 0x24, (angle & 0xffff) % 0x168);
}

/* Original 0x458d40: the letter aims at the centre and takes the throw: +0x28 a random of 6
 * (0x4826c0 of 0x598d30) plus 5, +0x30 576, +0x32 a random of 4 plus 1, +0x64 0, +0x68 6, +0x6c
 * 1, a wait of 10 (0x4ac7d0) and the state 0x458e30 (0x4ac510, 0x4ac8f0). */
uint32_t vertrix_port_title_letter_throw_458d40(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x1c
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t letter = entry->eax;
    uint32_t ebx;
    uint32_t random;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    letter_aim(&port, letter, 0x140, ebp, 1);
    ebx = sign16(port_u16(&port, letter, 8));
    random = port_call_with(&port, 0x4826c0, 0x598d30, 6, ebx, 0x168, letter, 0x140, ebp);
    port_set16(&port, letter, 0x28, random + 5);
    port_set16(&port, letter, 0x30, 0x240);
    random = port_call_with(&port, 0x4826c0, 0x598d30, 4, ebx, 0x168, letter, 0x140, ebp);
    port_set32(&port, letter, 0x64, 0);
    port_set32(&port, letter, 0x68, 6);
    port_set16(&port, letter, 0x32, random + 1);
    port_set32(&port, letter, 0x6c, 1);
    port_call_with(&port, 0x4ac7d0, letter, 0xa, ebx, 0x168, letter, 0x140, ebp);
    port_call_with(&port, 0x4ac510, letter, 0x458e30, ebx, 0x168, letter, 0x140, ebp);
    return port_return(
        &port,
        port_call_with(&port, 0x4ac8f0, letter, vertrix_lift_edx, ebx, 0x168, letter, 0x140, ebp),
        entry->edx);
}

/* The steady throw of 0x458f00 and 0x45a0c0: +0x28 0, +0x30 576, +0x32 1, +0x64 0, +0x68 6, +0x6c
 * 1 and a wait of 10 (0x4ac7d0). */
static void letter_steady(Port *port, uint32_t letter, uint32_t ebx, uint32_t edi, uint32_t ebp)
{
    port_set16(port, letter, 0x28, 0);
    port_set16(port, letter, 0x30, 0x240);
    port_set16(port, letter, 0x32, 1);
    port_set32(port, letter, 0x64, 0);
    port_set32(port, letter, 0x68, 6);
    port_set32(port, letter, 0x6c, 1);
    port_call_with(port, 0x4ac7d0, letter, 0xa, ebx, 0x168, letter, edi, ebp);
}

/* Original 0x458f00: the letter aims at the centre and takes the steady throw into the state
 * 0x458fd0 (0x4ac510, 0x4ac8f0). */
uint32_t vertrix_port_title_letter_steady_458f00(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x1c
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t letter = entry->eax;
    uint32_t ebx;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    letter_aim(&port, letter, 0x140, ebp, 1);
    ebx = sign16(port_u16(&port, letter, 8));
    letter_steady(&port, letter, ebx, 0x140, ebp);
    port_call_with(&port, 0x4ac510, letter, 0x458fd0, ebx, 0x168, letter, 0x140, ebp);
    return port_return(
        &port,
        port_call_with(&port, 0x4ac8f0, letter, vertrix_lift_edx, ebx, 0x168, letter, 0x140, ebp),
        entry->edx);
}

/* Original 0x45a0c0: the letter aims at the centre and takes the steady throw, restarts its
 * timer (0x4ac510), sounds the throw 0x533164[0x4f81b0] on the channels 0 and 4 (0x482a60 at the
 * volume 0x532b9c) and takes the state 0x45a1c0. */
uint32_t vertrix_port_title_letter_launch_call_45a0c0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x1c
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t letter = entry->eax;
    uint32_t ebx;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    letter_aim(&port, letter, 0xf0, ebp, 1);
    ebx = sign16(port_u16(&port, letter, 8));
    letter_steady(&port, letter, ebx, 0xf0, ebp);
    port_call_with(&port, 0x4ac510, letter, vertrix_lift_edx, ebx, 0x168, letter, 0xf0, ebp);
    ebx = port_u32(&port, 0, 0x532b9c);
    port_call_with(&port, 0x482a60, 0, port_u32(&port, port_u32(&port, 0, 0x4f81b0) * 4, 0x533164),
                   ebx, 0x168, letter, 0xf0, ebp);
    ebx = port_u32(&port, 0, 0x532b9c);
    port_call_with(&port, 0x482a60, 4, port_u32(&port, port_u32(&port, 0, 0x4f81b0) * 4, 0x533164),
                   ebx, 0x168, letter, 0xf0, ebp);
    return port_return(
        &port, port_call_with(&port, 0x4ac8f0, letter, 0x45a1c0, ebx, 0x168, letter, 0xf0, ebp),
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

/* The size of the walker (0x4b14c0 into `width` and `height`) centres it on its start (+8,
 * +0xa). The last half height. */
static uint32_t walker_centre(Port *port, uint32_t walker, uint32_t width, uint32_t height,
                              uint32_t esi, uint32_t edi, uint32_t ebp)
{
    uint32_t half;
    port_set32(port, width, 0, 0);
    port_set32(port, height, 0, 0);
    port_call_with(port, 0x4b14c0, walker, width, height, walker, esi, edi, ebp);
    port_set16(port, walker, 0xe,
               sign16(port_u16(port, walker, 8)) - (port_u32(port, width, 0) >> 1));
    half = port_u32(port, height, 0) >> 1;
    port_set16(port, walker, 0x16, sign16(port_u16(port, walker, 0xa)) - half);
    return half;
}

/* Original 0x459100: when due the walker steps (0x4ac5b0 with 36) and flickers: a random
 * (0x4826c0 of 0x598d30) frame of 0x4fbb60 into +0x58 shown, a random height of 100, centred
 * (0x4b14c0); once the flicker is done (0x4ad790) it shows the frame 32 at height 0 and its state
 * is cleared. */
uint32_t vertrix_port_title_walker_flicker_459100(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x1c
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t walker = entry->eax;
    uint32_t amount;
    uint32_t random;
    uint32_t result;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_call_with(&port, 0x4ac500, walker, entry->edx, entry->ebx, walker, entry->esi, entry->edi,
                   ebp);
    result = port_call_with(&port, 0x4ac520, walker, vertrix_lift_edx, entry->ebx, walker,
                            entry->esi, entry->edi, ebp);
    if (result != 1)
    {
        return port_return(&port, result, entry->edx);
    }
    amount = port_call_with(&port, 0x4ac540, walker, vertrix_lift_edx, entry->ebx, walker,
                            entry->esi, entry->edi, ebp);
    port_call_with(&port, 0x4ac5b0, walker, 0x24, entry->ebx, walker, amount, entry->edi, ebp);
    random = port_call_with(&port, 0x4826c0, 0x598d30, vertrix_lift_edx, entry->ebx, walker, amount,
                            entry->edi, ebp);
    port_set32(&port, walker, 0x58, port_u32(&port, (random & 0xffff) * 4, 0x4fbb60));
    walker_look(&port, walker, entry->ebx, amount, entry->edi, ebp);
    random = port_call_with(&port, 0x4826c0, 0x598d30, 0x64, entry->ebx, walker, amount, entry->edi,
                            ebp);
    port_set16(&port, walker, 0x48, random);
    walker_centre(&port, walker, ebp - 0x18, ebp - 0x14, amount, entry->edi, ebp);
    result = port_call_with(&port, 0x4ad790, walker, amount, ebp - 0x14, walker, amount, entry->edi,
                            ebp);
    if (result != 0)
    {
        return port_return(&port, result, entry->edx);
    }
    port_set32(&port, walker, 0x58, 0x20);
    walker_look(&port, walker, ebp - 0x14, amount, entry->edi, ebp);
    port_set16(&port, walker, 0x48, 0);
    return port_return(
        &port,
        port_call_with(&port, 0x4ac8f0, walker, 0, ebp - 0x14, walker, amount, entry->edi, ebp),
        entry->edx);
}

/* Original 0x4593b0: when due the walker steps, moves from its start (0x4aca60, 0x4acab0, the
 * new place the start) and bobs (0x4ad530), centred (0x4b14c0); a finished move across clears its
 * state, one finished both ways sets the speeds +0x1a 4, +0x18 455 and the state 0x4594a0. */
uint32_t vertrix_port_title_walker_glide_4593b0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x20
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t walker = entry->eax;
    uint32_t amount;
    uint32_t across;
    uint32_t down;
    uint32_t result;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_call_with(&port, 0x4ac500, walker, entry->edx, entry->ebx, walker, entry->esi, entry->edi,
                   ebp);
    result = port_call_with(&port, 0x4ac520, walker, vertrix_lift_edx, entry->ebx, walker,
                            entry->esi, entry->edi, ebp);
    if (result != 1)
    {
        return port_return(&port, result, entry->edx);
    }
    amount = port_call_with(&port, 0x4ac540, walker, vertrix_lift_edx, entry->ebx, walker,
                            entry->esi, entry->edi, ebp);
    port_call_with(&port, 0x4ac5b0, walker, vertrix_lift_edx, amount, walker, entry->esi,
                   entry->edi, ebp);
    port_set16(&port, walker, 0xe, port_u16(&port, walker, 8));
    port_set16(&port, walker, 0x16, port_u16(&port, walker, 0xa));
    across = port_call_with(&port, 0x4aca60, walker, amount, amount, walker, entry->esi, entry->edi,
                            ebp);
    down = port_call_with(&port, 0x4acab0, walker, amount, amount, walker, across, entry->edi, ebp);
    port_set16(&port, walker, 8, port_u16(&port, walker, 0xe));
    port_set16(&port, walker, 0xa, port_u16(&port, walker, 0x16));
    port_call_with(&port, 0x4ad530, walker, amount, ebp - 0x18, walker, across, down, ebp);
    result = walker_centre(&port, walker, ebp - 0x1c, ebp - 0x18, across, down, ebp);
    if (across == 0)
    {
        return port_return(
            &port,
            port_call_with(&port, 0x4ac8f0, walker, 0, ebp - 0x18, walker, across, down, ebp),
            entry->edx);
    }
    if (down != 0)
    {
        return port_return(&port, result, entry->edx);
    }
    port_set16(&port, walker, 0x1a, 4);
    port_set16(&port, walker, 0x18, 0x1c7);
    return port_return(
        &port,
        port_call_with(&port, 0x4ac8f0, walker, 0x4594a0, ebp - 0x18, walker, across, down, ebp),
        entry->edx);
}

/* The wave of 0x45a750 and 0x45a830: when due the letter steps; while the title waves (0x532bd0)
 * it bobs (0x4ad530) and, there, turns to `height` at speed 2 into `next`; otherwise it settles
 * (height 0 at 5), turns (0x4ad510 with 1 at its place, +0x30 160) and takes the spin: +0x24 a
 * random of 360, +0x28 a random of 10 plus 10, +0x32 2 and the state 0x45a910. 0x457890 last. */
static uint32_t letter_wave(PORT_SIGNATURE, uint32_t height, uint32_t next)
{
    Port port;
    uint32_t letter = entry->eax;
    uint32_t amount;
    uint32_t ebx;
    uint32_t ecx;
    uint32_t random;
    port_open(&port, calls, services, globals, entry);
    port_forward_esi(&port, entry, 0x4ac500, letter, entry->edx, entry->ebx, entry->ecx, letter);
    if (port_forward_esi(&port, entry, 0x4ac520, letter, vertrix_lift_edx, entry->ebx, entry->ecx,
                         letter) != 1)
    {
        return port_return(&port,
                           port_forward_esi(&port, entry, 0x457890, letter, vertrix_lift_edx,
                                            entry->ebx, entry->ecx, letter),
                           entry->edx);
    }
    amount = port_forward_esi(&port, entry, 0x4ac540, letter, vertrix_lift_edx, entry->ebx,
                              entry->ecx, letter);
    port_forward_esi(&port, entry, 0x4ac5b0, letter, amount, entry->ebx, entry->ecx, letter);
    if (port_u32(&port, 0, 0x532bd0) != 0)
    {
        if (port_forward_esi(&port, entry, 0x4ad530, letter, vertrix_lift_edx, entry->ebx,
                             entry->ecx, letter) == 0)
        {
            port_set16(&port, letter, 0x4a, height);
            port_set16(&port, letter, 0x4c, 2);
            port_forward_esi(&port, entry, 0x4ac8f0, letter, next, entry->ebx, entry->ecx, letter);
        }
        return port_return(&port,
                           port_forward_esi(&port, entry, 0x457890, letter, vertrix_lift_edx,
                                            entry->ebx, entry->ecx, letter),
                           entry->edx);
    }
    port_set16(&port, letter, 0x4a, 0);
    port_set16(&port, letter, 0x4c, 5);
    ecx = sign16(port_u16(&port, letter, 0xa));
    ebx = sign16(port_u16(&port, letter, 8));
    port_set16(&port, letter, 0x30, 0xa0);
    port_forward_esi(&port, entry, 0x4ad510, letter, 1, ebx, ecx, letter);
    random = port_forward_esi(&port, entry, 0x4826c0, 0x598d30, 0x168, ebx, ecx, letter);
    port_set16(&port, letter, 0x24, random);
    random = port_forward_esi(&port, entry, 0x4826c0, 0x598d30, 0xa, ebx, ecx, letter);
    port_set16(&port, letter, 0x28, random + 0xa);
    port_set16(&port, letter, 0x32, 2);
    port_forward_esi(&port, entry, 0x4ac8f0, letter, 0x45a910, ebx, ecx, letter);
    return port_return(
        &port, port_forward_esi(&port, entry, 0x457890, letter, vertrix_lift_edx, ebx, ecx, letter),
        entry->edx);
}

/* Original 0x45a750: the wave turning to height -20 into 0x45a830. */
uint32_t vertrix_port_title_letter_wave_call_45a750(PORT_SIGNATURE)
{
    return letter_wave(calls, services, globals, entry, 0xffec, 0x45a830);
}

/* Original 0x45a830: the wave turning to height 50 into 0x45a750. */
uint32_t vertrix_port_title_letter_wave_call_45a830(PORT_SIGNATURE)
{
    return letter_wave(calls, services, globals, entry, 0x32, 0x45a750);
}

/* Original 0x45b4c0: the score step: the count +0x420 restarts; when the child +0x15c scores
 * (0x438d50 with the target +0x400) the count takes it, the child slides at the level's speed
 * 0x4f7d2c (0x4ac7b0, +0x58 0, 0x4ac510, 0x438dd0), the actor scores 0x4f81ac (0x43c0e0) into
 * the state 0x45b590, or 0x45b5f0 when the child is done (0x439080 1); otherwise the actor
 * finishes (0x43acd0) and ends after the child's step (0x43bbf0). */
uint32_t vertrix_port_state_score_step_45b4c0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x1c
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t actor = entry->eax;
    uint32_t child;
    uint32_t ebx;
    uint32_t edi = 0;
    uint32_t result;
    uint32_t methods;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, -0x18u, actor);
    child = port_u32(&port, actor, 0x15c);
    ebx = port_u32(&port, actor, 0x400);
    port_set32(&port, actor, 0x420, 0);
    result = port_call_with(&port, 0x438d50, child, 0, ebx, actor, child, 0, ebp);
    if (result != 1)
    {
        edi = 1;
        port_call_with(&port, 0x43acd0, actor, vertrix_lift_edx, ebx, actor, child, 1, ebp);
    }
    else
    {
        uint32_t level;
        ebx = port_u32(&port, actor, 0x420) + result;
        level = port_u32(&port, 0, 0x532bbc);
        port_set32(&port, actor, 0x420, ebx);
        port_call_with(&port, 0x4ac7b0, child, port_u32(&port, level * 4, 0x4f7d2c), ebx, actor,
                       child, 0, ebp);
        port_set32(&port, child, 0x58, 0);
        port_call_with(&port, 0x4ac510, child, vertrix_lift_edx, ebx, actor, child, 0, ebp);
        port_call_with(&port, 0x438dd0, child, vertrix_lift_edx, ebx, actor, child, 0, ebp);
        port_call_with(&port, 0x43c0e0, actor, port_u32(&port, 0, 0x4f81ac), ebx, actor, child, 0,
                       ebp);
        port_call_with(&port, 0x4ac8f0, actor, 0x45b590, ebx, actor, child, 0, ebp);
        if (port_call_with(&port, 0x439080, child, vertrix_lift_edx, ebx, actor, child, 0, ebp) ==
            1)
        {
            port_call_with(&port, 0x4ac8f0, actor, 0x45b5f0, ebx, actor, child, 0, ebp);
        }
    }
    methods = port_u32(&port, child, 0x158);
    result = port_call_with(&port, port_u32(&port, methods, 4), child, methods, ebx, actor, child,
                            edi, ebp);
    if (edi == 1)
    {
        result = port_call_with(&port, 0x43bbf0, port_u32(&port, ebp, -0x18u), vertrix_lift_edx,
                                ebx, actor, child, 1, ebp);
    }
    return port_return(&port, result, entry->edx);
}

/* Original 0x45c600: the key wait: when due the timer restarts (0x4ac510); the height is 60 and
 * the press (0x4764a0 of the key 0x54d640 0x74) read; off the item (0x4b0b70 at the pointer
 * 0x558944, 0x558946, 0x7d00 while 0x558958 is set) it takes the state 0x45c3c0; on it, with the
 * key up (0x476480 0), the look 9, the state 0x45c7e0 (0x4ac910) and the flag 0x532a48 1. */
uint32_t vertrix_port_menu_key_wait_45c600(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x20
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t item = entry->eax;
    uint32_t pointer;
    uint32_t x;
    uint32_t y;
    uint32_t ebx;
    uint32_t result;
    uint32_t press[1];
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_call_with(&port, 0x4ac500, item, item, entry->ebx, entry->ecx, item, entry->edi, ebp);
    if (port_call_with(&port, 0x4ac520, vertrix_lift_edx, vertrix_lift_edx, entry->ebx, entry->ecx,
                       item, entry->edi, ebp) == 1)
    {
        port_call_with(&port, 0x4ac510, vertrix_lift_edx, vertrix_lift_edx, entry->ebx, entry->ecx,
                       item, entry->edi, ebp);
    }
    port_set16(&port, item, 0x48, 0x3c);
    press[0] = ebp - 0x14;
    call_frame(&port, 0x4764a0, 0x54d640, 0x74, ebp - 0x1c, ebp - 0x18, item, entry->edi, ebp,
               press, 1);
    y = port_u32(&port, 0, 0x558958) != 0 ? 0x7d00 : port_u16(&port, 0, 0x558946);
    pointer = port_u32(&port, 0, 0x558958);
    ebx = sign16(y);
    x = pointer != 0 ? 0x7d00 : port_u16(&port, 0, 0x558944);
    result = port_call_with(&port, 0x4b0b70, item, sign16(x), ebx, pointer, item, entry->edi, ebp);
    if ((result & 0xff) == 0)
    {
        return port_return(
            &port,
            port_call_with(&port, 0x4ac8f0, item, 0x45c3c0, ebx, pointer, item, entry->edi, ebp),
            entry->edx);
    }
    result = port_call_with(&port, 0x476480, 0x54d640, 0x74, ebx, pointer, item, entry->edi, ebp);
    if (result != 0)
    {
        return port_return(&port, result, entry->edx);
    }
    port_set8(&port, item, 0x52, 9);
    result = port_call_with(&port, 0x4ac910, item, 0x45c7e0, 1, pointer, item, entry->edi, ebp);
    port_set32(&port, 0, 0x532a48, 1);
    return port_return(&port, result, entry->edx);
}

/* The box at (ax, dx) to (bx, cx), 2 inside and 4 short: a frame object (0x160 bytes, 0x4ca000,
 * 0x4b5400) placed (0x4adf20), sized (0x4b54d0), mode 2 (0x4ac7b0), +0x94, +0x95 and +0x110 1,
 * drawn by `draw` (0x4ac4f0) in the colour `colour` (0x4ac4e0). */
static uint32_t label_box(PORT_SIGNATURE, uint32_t draw, uint32_t colour)
{
    enum
    {
        BELOW = 0x18
    };
    static const uint32_t zeros[5] = {0, 0, 0, 0, 0};
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t edi = entry->ebx - 4;
    uint32_t ebx;
    uint32_t box;
    uint32_t right[1];
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set16(&port, ebp, -0x10u, entry->eax);
    port_set16(&port, ebp, -0xcu, entry->edx);
    port_set32(&port, ebp, -0x14u, entry->ecx);
    ebx = port_u32(&port, ebp, -0xcu) + 2;
    port_set32(&port, ebp, -0x14u, entry->ecx - 4);
    box = port_call_with(&port, 0x4ca000, 0x160, entry->eax + 2, ebx, entry->ecx - 4, entry->esi,
                         edi, ebp);
    port_set16(&port, ebp, -0x10u, vertrix_lift_edx);
    port_set16(&port, ebp, -0xcu, ebx);
    if (box != 0)
    {
        box = port_call_with(&port, 0x4b5400, box, vertrix_lift_edx, ebx, entry->ecx - 4,
                             entry->esi, edi, ebp);
    }
    call_frame(&port, 0x4adf20, box, 0, 0, 0, box, edi, ebp, zeros, 5);
    right[0] = port_u16(&port, ebp, -0x14u);
    call_frame(&port, 0x4b54d0, box, sign16(port_u16(&port, ebp, -0x10u)),
               sign16(port_u16(&port, ebp, -0xcu)), edi & 0xffff, box, edi, ebp, right, 1);
    port_call_with(&port, 0x4ac7b0, box, 2, sign16(port_u16(&port, ebp, -0xcu)), edi & 0xffff, box,
                   edi, ebp);
    port_set8(&port, box, 0x94, 1);
    port_set8(&port, box, 0x95, 1);
    port_set8(&port, box, 0x110, 1);
    port_call_with(&port, 0x4ac4f0, box, draw, 0, edi & 0xffff, box, edi, ebp);
    port_call_with(&port, 0x4ac4e0, box, colour, 0, edi & 0xffff, box, edi, ebp);
    return port_return(&port, box, vertrix_lift_edx);
}

/* Original 0x45fe10: the label box drawn by 0x450080 in the colour 0x3003e. */
uint32_t vertrix_port_label_box_45fe10(PORT_SIGNATURE)
{
    return label_box(calls, services, globals, entry, 0x450080, 0x3003e);
}

/* Original 0x45fee0: the box drawn by 0x7f in the colour 0x3f. */
uint32_t vertrix_port_plain_box_45fee0(PORT_SIGNATURE)
{
    return label_box(calls, services, globals, entry, 0x7f, 0x3f);
}
