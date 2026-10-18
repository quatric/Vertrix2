#include "rtlbonus.h"

/* Bonus letters, window message dispatch and the piece lock. */

/* Original 0x4585c0: the title letter eax counting down the bonus: refreshed (0x457810, +0xc 0),
 * when its period is up (0x4ac500, 0x4ac520) its steps (0x4ac540) are taken (0x4ac5b0), its place
 * (0x4ad060) and size (0x4ad260) read; within the distance +0x30 its fade +0x44 is 16 less 16 * the
 * travelled +0x2a / +0x30, else none (and +0x48 0); its travel +0x2a less +0x32 a step (0 once
 * below 0), its move made (0x4ad530) and its place +8/+0xa set. At the end of its travel it is
 * reset to its start +0x2c/+0x2e, faded in (+0x44 16), timed at 20 (0x4ac7d0), handed 0x458260
 * (0x4ac8f0), +0x93 0, +0x4a 100 and +0x4c
 * 5. 0x457890 always follows. edx kept. */
uint32_t vertrix_port_title_letter_bonus_count_4585c0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x20
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t letter = entry->eax;
    uint32_t distance;
    uint32_t steps;
    uint32_t place;
    uint32_t eax;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -4u, entry->ebx);
    port_set32(&port, ebp, -8u, entry->ecx);
    port_set32(&port, ebp, -0xcu, entry->edx);
    port_set32(&port, ebp, -0x10u, entry->esi);
    port_set32(&port, ebp, -0x14u, entry->edi);
    distance = port_u32(&port, letter, 0x2e);
    port_call_with(&port, 0x457810, letter, entry->edx, entry->ebx, letter, entry->esi, distance,
                   ebp);
    port_set16(&port, letter, 0xc, 0);
    port_call_with(&port, 0x4ac500, letter, vertrix_lift_edx, entry->ebx, letter, entry->esi,
                   distance, ebp);
    distance = (uint32_t)((int32_t)distance >> 16);
    eax = port_call_with(&port, 0x4ac520, letter, vertrix_lift_edx, entry->ebx, letter, entry->esi,
                         distance, ebp);
    if (eax != 1)
    {
        eax = port_call_with(&port, 0x457890, letter, vertrix_lift_edx, entry->ebx, letter,
                             entry->esi, distance, ebp);
        return port_return(&port, eax, entry->edx);
    }
    steps = port_call_with(&port, 0x4ac540, letter, vertrix_lift_edx, entry->ebx, letter,
                           entry->esi, distance, ebp);
    port_call_with(&port, 0x4ac5b0, letter, steps, entry->ebx, letter, steps, distance, ebp);
    port_call_with(&port, 0x4ad060, letter, vertrix_lift_edx, ebp - 0x18, letter, steps, distance,
                   ebp);
    port_call_with(&port, 0x4ad260, letter, ebp - 0x1c, ebp - 0x18, letter, steps, distance, ebp);
    place = (uint32_t)((int32_t)port_u32(&port, letter, 0x28) >> 16);
    if (place <= distance)
    {
        LiftFlags flags = {0};
        uint32_t edx = 0;
        eax = place << 4;
        lift_div1(32, distance, &eax, &edx, &flags);
        eax = 0x10 - eax;
        if ((int32_t)eax >= 0x10)
        {
            eax = 0x10;
        }
        port_set8(&port, letter, 0x44, eax);
    }
    else
    {
        port_set8(&port, letter, 0x44, 0);
        port_set16(&port, letter, 0x48, 0);
    }
    port_set16(&port, letter, 0x2a,
               port_u16(&port, letter, 0x2a) - port_u16(&port, letter, 0x32) * steps);
    if ((int32_t)port_u32(&port, letter, 0x28) < 0)
    {
        port_set16(&port, letter, 0x2a, 0);
    }
    port_call_with(&port, 0x4ad530, letter, steps, place, letter, steps, distance, ebp);
    port_set16(&port, letter, 8, port_u32(&port, ebp, -0x1cu));
    port_set16(&port, letter, 0xa, port_u32(&port, ebp, -0x18u));
    if (place == 0)
    {
        port_set16(&port, letter, 8, port_u16(&port, letter, 0x2c));
        port_set16(&port, letter, 0xa, port_u16(&port, letter, 0x2e));
        port_set8(&port, letter, 0x44, 0x10);
        port_call_with(&port, 0x4ac7d0, letter, 0x14, place, letter, steps, distance, ebp);
        port_call_with(&port, 0x4ac8f0, letter, 0x458260, place, letter, steps, distance, ebp);
        port_set8(&port, letter, 0x93, 0);
        port_set16(&port, letter, 0x48, 0);
        port_set16(&port, letter, 0x4a, 0x64);
        port_set16(&port, letter, 0x4c, 5);
    }
    eax = port_call_with(&port, 0x457890, letter, vertrix_lift_edx, place, letter, steps, distance,
                         ebp);
    return port_return(&port, eax, entry->edx);
}

/* Original 0x4d2020 (one stack argument, the result, popped): the window message edx of the
 * control eax (ebx and ecx its parameters) handed on: 0x2b..0x2f, 0x39, 0x114, 0x115 and 0x210
 * forwarded as 0xbc00 + the message (0x4d0c84); a command (0x111) as 0xbd11 with its notification
 * code (0x4cb820, the result 1 when handled); a notification (0x4e) as 0xbc4e with its code; the
 * colour messages 0x132..0x138 as 0xbc19 with the parameter and their index in the frame, kept
 * when the result is set. Anything else 0. */
uint32_t vertrix_port_message_dispatch_4d2020(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x1c
    };
    Port port;
    uint8_t stack[BELOW + 8 + 4];
    uint32_t frame = entry->esp - BELOW;
    uint32_t control = entry->eax;
    uint32_t message = entry->edx;
    uint32_t result;
    uint32_t eax;
    uint32_t zero[1] = {0};
    port_open_arguments(&port, stack, calls, services, globals, entry, BELOW, 1);
    port_set32(&port, entry->esp, -4u, entry->esi);
    port_set32(&port, entry->esp, -8u, entry->edi);
    result = port_u32(&port, entry->esp, 4);
    if ((message >= 0x2b && message <= 0x2f) || message == 0x39 || message == 0x114 ||
        message == 0x115 || message == 0x210)
    {
        uint32_t args[1] = {result};
        eax = port_call_registers(&port, 0x4d0c84, control, message + 0xbc00, entry->ebx,
                                  entry->ecx, control, result, entry->ebp, args, 1);
        return port_return(&port, eax, vertrix_lift_edx);
    }
    if (message == 0x111)
    {
        eax = port_call_registers(&port, 0x4cb820, control, 0,
                                  ((entry->ebx >> 16) & 0xffff) | 0xbd110000u, 0, control, result,
                                  entry->ebp, zero, 1);
        if (eax == 0)
        {
            return port_return(&port, 0, vertrix_lift_edx);
        }
        if (result != 0)
        {
            port_set32(&port, result, 0, 1);
        }
        return port_return(&port, 1, vertrix_lift_edx);
    }
    if (message == 0x4e)
    {
        port_set32(&port, frame, 0x10, entry->ecx);
        port_set32(&port, frame, 0xc, result);
        eax = port_call_registers(&port, 0x4cb820, control, 0,
                                  port_u16(&port, entry->ecx, 8) | 0xbc4e0000u, frame + 0xc,
                                  control, result, entry->ebp, zero, 1);
        return port_return(&port, eax, vertrix_lift_edx);
    }
    if (message < 0x132 || message > 0x138)
    {
        return port_return(&port, 0, message);
    }
    port_set32(&port, frame, 4, entry->ebx);
    port_set32(&port, frame, 8, message - 0x132);
    {
        uint32_t args[1] = {result};
        eax = port_call_registers(&port, 0x4d0c84, control, 0xbc19, 0, frame, control, result,
                                  entry->ebp, args, 1);
    }
    if (port_u32(&port, result, 0) != 0)
    {
        return port_return(&port, eax, vertrix_lift_edx);
    }
    return port_return(&port, 0, vertrix_lift_edx);
}

/* Original 0x4517c0: the actor eax's piece posted and locked: its player +0x15c asked (0x432480
 * with the colour +0x4dc) for the rows, score, and the two flags. Without a lock the actor either
 * finishes its match (0x452250, when +0x44c is 1) or, after 0x43ba70, gets the handler 0x451a60
 * with state 2 and 0x43ba80, or 0x450ff0 with state 0. With a lock: sound 0x4f8194 and 0x43ce00
 * for the colour 0x24, the rows and score given (0x43ba70, 0x43b9c0, 0x43ba90), the lock count
 * +0x184 and total +0x188 kept, sound 0x4f81b4 at the third and sixth lock, the flags' sounds
 * 0x4f81ac or 0x532d88, and the handler 0x4520f0. The player is stepped (its method +4 of
 * +0x158). edx kept. */
uint32_t vertrix_port_object_post_lock_4517c0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x2c
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t actor = entry->eax;
    uint32_t player;
    uint32_t colour;
    uint32_t eax;
    uint32_t vtable;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -4u, entry->ebx);
    port_set32(&port, ebp, -8u, entry->ecx);
    port_set32(&port, ebp, -0xcu, entry->edx);
    port_set32(&port, ebp, -0x10u, entry->esi);
    port_set32(&port, ebp, -0x14u, entry->edi);
    player = port_u32(&port, actor, 0x15c);
    port_set32(&port, ebp, -0x18u, player);
    colour = port_u8(&port, actor, 0x4dc);
#define CALL(target, a, d)                                                                         \
    port_call_with(&port, target, a, d, ebp - 0x24, colour, actor, actor, ebp)
    {
        uint32_t args[2] = {ebp - 0x20, ebp - 0x1c};
        eax = port_call_registers(&port, 0x432480, player, ebp - 0x28, ebp - 0x24, colour, actor,
                                  actor, ebp, args, 2);
    }
    if (eax == 0)
    {
        if (port_u32(&port, actor, 0x44c) == 1)
        {
            CALL(0x452250, actor, vertrix_lift_edx);
        }
        else if (CALL(0x43ba70, actor, vertrix_lift_edx) == 1)
        {
            CALL(0x4ac8f0, actor, 0x451a60);
            CALL(0x43bae0, actor, 2);
            CALL(0x43ba80, actor, vertrix_lift_edx);
        }
        else
        {
            CALL(0x4ac8f0, actor, 0x450ff0);
            CALL(0x43bae0, actor, 0);
        }
    }
    else
    {
        uint32_t sound = 0;
        if (port_u32(&port, actor, 0x4c8) == 0x24)
        {
            CALL(0x43c0e0, actor, port_u32(&port, 0, 0x4f8194));
            CALL(0x43ce00, actor, vertrix_lift_edx);
        }
        CALL(0x43ba70, actor, vertrix_lift_edx);
        CALL(0x43b9c0, actor, port_u32(&port, ebp, -0x24u));
        CALL(0x43ba90, actor, port_u32(&port, ebp, -0x28u));
        port_set32(&port, actor, 0x184, port_u32(&port, actor, 0x184) + 1);
        port_set32(&port, actor, 0x188,
                   port_u32(&port, actor, 0x188) + port_u32(&port, ebp, -0x24u));
        if (port_u32(&port, actor, 0x184) == 3)
        {
            CALL(0x43c0e0, actor, port_u32(&port, 0, 0x4f81b4));
        }
        if (port_u32(&port, actor, 0x184) == 6)
        {
            CALL(0x43c0e0, actor, port_u32(&port, 0, 0x4f81b4));
        }
        if (port_u32(&port, ebp, -0x1cu) == 1)
        {
            sound = port_u32(&port, 0, 0x4f81ac);
            CALL(0x43c0e0, actor, sound);
        }
        else if (port_u32(&port, ebp, -0x20u) == 1)
        {
            sound = port_u32(&port, 0, 0x532d88);
            CALL(0x43c0e0, actor, sound);
        }
        CALL(0x4ac8f0, actor, 0x4520f0);
    }
    vtable = port_u32(&port, port_u32(&port, ebp, -0x18u), 0x158);
    eax = CALL(port_u32(&port, vtable, 4), port_u32(&port, ebp, -0x18u), vtable);
#undef CALL
    return port_return(&port, eax, entry->edx);
}
