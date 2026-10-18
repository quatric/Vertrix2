#include "twins.h"

/* The player's lock and twin handling, the block conversion effect, a click step and the fly
 * in. */

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

static uint32_t high16(uint32_t value)
{
    return (uint32_t)((int32_t)value >> 16);
}

/* Original 0x451920: the player eax after a lock: its board +0x15c is checked (0x432480 with the
 * kind +0x4dc) for lines; without any, a twin +0x44c of 1 ends (0x452250), otherwise a ready
 * player (0x43ba70) takes the state 0x451a60 with 2 (0x43bae0, 0x43ba80), else 0x450ff0 with 0;
 * with lines, the kind 0x24 scores 0x4f8194 (0x43c0e0, 0x43ce00), the lines and count are taken
 * (0x43ba70, 0x43b9c0, 0x43ba90), +0x184 and +0x188 go up (3 scoring 0x4f81b4), the score is
 * 0x532d88 (or 0x4f81ac with a combo) and the state 0x4520f0. Then the board's method +4. */
uint32_t vertrix_port_object_post_lock_twin_451920(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x2c
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t player = entry->eax;
    uint32_t board;
    uint32_t kind;
    uint32_t methods;
    uint32_t eax;
    uint32_t args[2];
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    board = port_u32(&port, player, 0x15c);
    port_set32(&port, ebp, -0x18u, board);
    kind = port_u8(&port, player, 0x4dc);
    args[0] = ebp - 0x20;
    args[1] = ebp - 0x1c;
    if (call_frame(&port, 0x432480, board, ebp - 0x28, ebp - 0x24, kind, player, player, ebp, args,
                   2) == 0)
    {
        if (port_u32(&port, player, 0x44c) == 1)
        {
            port_call_with(&port, 0x452250, player, vertrix_lift_edx, ebp - 0x24, kind, player,
                           player, ebp);
        }
        else if (port_call_with(&port, 0x43ba70, player, vertrix_lift_edx, ebp - 0x24, kind, player,
                                player, ebp) == 1)
        {
            port_call_with(&port, 0x4ac8f0, player, 0x451a60, ebp - 0x24, kind, player, player,
                           ebp);
            port_call_with(&port, 0x43bae0, player, 2, ebp - 0x24, kind, player, player, ebp);
            port_call_with(&port, 0x43ba80, player, vertrix_lift_edx, ebp - 0x24, kind, player,
                           player, ebp);
        }
        else
        {
            port_call_with(&port, 0x4ac8f0, player, 0x450ff0, ebp - 0x24, kind, player, player,
                           ebp);
            port_call_with(&port, 0x43bae0, player, 0, ebp - 0x24, kind, player, player, ebp);
        }
    }
    else
    {
        if (port_u32(&port, player, 0x4c8) == 0x24)
        {
            port_call_with(&port, 0x43c0e0, player, port_u32(&port, 0, 0x4f8194), ebp - 0x24, kind,
                           player, player, ebp);
            port_call_with(&port, 0x43ce00, player, vertrix_lift_edx, ebp - 0x24, kind, player,
                           player, ebp);
        }
        port_call_with(&port, 0x43ba70, player, vertrix_lift_edx, ebp - 0x24, kind, player, player,
                       ebp);
        port_call_with(&port, 0x43b9c0, player, port_u32(&port, ebp, -0x24u), ebp - 0x24, kind,
                       player, player, ebp);
        port_call_with(&port, 0x43ba90, player, port_u32(&port, ebp, -0x28u), ebp - 0x24, kind,
                       player, player, ebp);
        port_set32(&port, player, 0x184, port_u32(&port, player, 0x184) + 1);
        port_set32(&port, player, 0x188,
                   port_u32(&port, player, 0x188) + port_u32(&port, ebp, -0x24u));
        if (port_u32(&port, player, 0x184) == 3)
        {
            port_call_with(&port, 0x43c0e0, player, port_u32(&port, 0, 0x4f81b4), ebp - 0x24, kind,
                           player, player, ebp);
        }
        port_call_with(&port, 0x43c0e0, player,
                       port_u32(&port, 0, port_u32(&port, ebp, -0x1cu) == 0 ? 0x532d88 : 0x4f81ac),
                       ebp - 0x24, kind, player, player, ebp);
        port_call_with(&port, 0x4ac8f0, player, 0x4520f0, ebp - 0x24, kind, player, player, ebp);
    }
    board = port_u32(&port, ebp, -0x18u);
    methods = port_u32(&port, board, 0x158);
    eax = port_call_with(&port, port_u32(&port, methods, 4), board, methods, ebp - 0x24, kind,
                         player, player, ebp);
    return port_return(&port, eax, entry->edx);
}

/* Original 0x453150: the player eax's block conversion against its rival +0x3b0: both boards'
 * counts of the kind +0x3dc (0x436a10); equal counts end both (0x43acd0) and the rival steps
 * (0x43bbf0) after; otherwise the player wins (0x43ac00) or loses (0x43acd0), the rival scores
 * 0x4f81ac (0x43c0e0), the counts go to +0x43c and +0x440, the blocks are converted (0x436b40)
 * with the player in the state 0x453280, the rival stopped (0x43bb60), its board's +0xb80 to
 * +0xb88 set and the state 0x452050. The board's method +4 either way. */
uint32_t vertrix_port_effect_convert_blocks_453150(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x2c
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t player = entry->eax;
    uint32_t rival;
    uint32_t board;
    uint32_t other;
    uint32_t mine;
    uint32_t theirs;
    uint32_t ebx;
    uint32_t ecx = player;
    uint32_t edi;
    uint32_t methods;
    uint32_t eax;
    uint32_t args[1];
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    rival = port_u32(&port, player, 0x3b0);
    port_set32(&port, ebp, -0x18u, rival);
    port_set32(&port, ebp, -0x20u, 0);
    board = port_u32(&port, player, 0x15c);
    port_set32(&port, ebp, -0x1cu, board);
    other = port_u32(&port, rival, 0x15c);
    port_call_with(&port, 0x436a10, board, port_u32(&port, player, 0x3dc), ebp - 0x28, player,
                   player, other, ebp);
    port_call_with(&port, 0x436a10, other, port_u32(&port, player, 0x3dc), ebp - 0x24, player,
                   player, other, ebp);
    mine = port_u32(&port, ebp, -0x28u);
    theirs = port_u32(&port, ebp, -0x24u);
    if (mine == theirs)
    {
        ebx = 1;
        port_call_with(&port, 0x43acd0, player, vertrix_lift_edx, ebx, player, player, other, ebp);
        port_set32(&port, ebp, -0x20u, ebx);
    }
    else
    {
        ebx = theirs;
        port_call_with(&port, mine <= theirs ? 0x43acd0 : 0x43ac00, player, vertrix_lift_edx, ebx,
                       player, player, other, ebp);
        port_call_with(&port, 0x43c0e0, port_u32(&port, ebp, -0x18u), port_u32(&port, 0, 0x4f81ac),
                       ebx, player, player, other, ebp);
        port_set32(&port, player, 0x43c, port_u32(&port, ebp, -0x28u));
        ebx = port_u32(&port, player, 0x3dc);
        ecx = port_u32(&port, player, 0x43c);
        args[0] = port_u32(&port, ebp, -0x24u);
        port_set32(&port, player, 0x440, args[0]);
        call_frame(&port, 0x436b40, port_u32(&port, ebp, -0x1cu), other, ebx, ecx, player, other,
                   ebp, args, 1);
        port_call_with(&port, 0x4ac8f0, player, 0x453280, ebx, ecx, player, other, ebp);
        port_call_with(&port, 0x43bb60, port_u32(&port, ebp, -0x18u), vertrix_lift_edx, ebx, ecx,
                       player, other, ebp);
        port_set32(&port, other, 0xb80, 1);
        port_set32(&port, other, 0xb84, 1);
        port_set32(&port, other, 0xb88, 1);
        port_call_with(&port, 0x4ac8f0, port_u32(&port, ebp, -0x18u), 0x452050, ebx, ecx, player,
                       other, ebp);
    }
    board = port_u32(&port, ebp, -0x1cu);
    methods = port_u32(&port, board, 0x158);
    edi = port_u32(&port, ebp, -0x20u);
    eax = port_call_with(&port, port_u32(&port, methods, 4), board, methods, ebx, ecx, player, edi,
                         ebp);
    if (edi == 1)
    {
        eax = port_call_with(&port, 0x43bbf0, player, vertrix_lift_edx, ebx, ecx, player, edi, ebp);
    }
    return port_return(&port, eax, entry->edx);
}

/* Original 0x456170: the actor eax's click step: it moves and bobs (+0x4a 0, +0x4c 5; 0x4ad530)
 * when due; the pointer 0x558944 and 0x558946 (0x7d00 each while 0x558958) over it (0x4b0b70)
 * sets +0x48 35; a click of 0x74 (0x476480 on 0x54d640) at it (0x4764a0, 0x4b0b70) gives the
 * state 0x456290 and +0x48 60; a chosen actor (0x4b5500) puts its +0x14c in 0x532a60. */
uint32_t vertrix_port_actor_choice_step_456170(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x20
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t actor = entry->eax;
    uint32_t eax;
    uint32_t x;
    uint32_t y;
    uint32_t ecx;
    uint32_t args[1];
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_call_with(&port, 0x4ac500, actor, entry->edx, entry->ebx, actor, actor, entry->edi, ebp);
    if (port_call_with(&port, 0x4ac520, actor, vertrix_lift_edx, entry->ebx, actor, actor,
                       entry->edi, ebp) == 1)
    {
        eax = port_call_with(&port, 0x4ac540, actor, vertrix_lift_edx, entry->ebx, actor, actor,
                             entry->edi, ebp);
        port_call_with(&port, 0x4ac5b0, actor, eax, entry->ebx, actor, actor, entry->edi, ebp);
        port_set16(&port, actor, 0x4a, 0);
        port_set16(&port, actor, 0x4c, 5);
        port_call_with(&port, 0x4ad530, actor, vertrix_lift_edx, entry->ebx, actor, actor,
                       entry->edi, ebp);
    }
    ecx = port_u32(&port, 0, 0x558958);
    y = sign16(ecx != 0 ? 0x7d00 : port_u16(&port, 0, 0x558946));
    x = sign16(ecx != 0 ? 0x7d00 : port_u16(&port, 0, 0x558944));
    if ((port_call_with(&port, 0x4b0b70, actor, x, y, ecx, actor, entry->edi, ebp) & 0xff) != 0)
    {
        port_set16(&port, actor, 0x48, 0x23);
    }
    if (port_call_with(&port, 0x476480, 0x54d640, 0x74, y, ecx, actor, entry->edi, ebp) == 1)
    {
        args[0] = ebp - 0x14;
        call_frame(&port, 0x4764a0, 0x54d640, 0x74, ebp - 0x1c, ebp - 0x18, actor, entry->edi, ebp,
                   args, 1);
        y = high16(port_u32(&port, ebp, -0x1au));
        x = high16(port_u32(&port, ebp, -0x1eu));
        ecx = ebp - 0x18;
        if ((port_call_with(&port, 0x4b0b70, actor, x, y, ecx, actor, entry->edi, ebp) & 0xff) != 0)
        {
            port_call_with(&port, 0x4ac8f0, actor, 0x456290, y, ecx, actor, entry->edi, ebp);
            port_set16(&port, actor, 0x48, 0x3c);
        }
    }
    eax = port_call_with(&port, 0x4b5500, actor, vertrix_lift_edx, y, ecx, actor, entry->edi, ebp);
    if (eax != 0)
    {
        eax = port_u32(&port, actor, 0x14c);
        port_set32(&port, 0, 0x532a60, eax);
    }
    return port_return(&port, eax, entry->edx);
}

/* Original 0x4578f0: the actor eax's fly in: when due (0x4ac500, 0x4ac520) it moves by the time
 * 0x4ac540 (0x4ac5b0) from its place +8, +0xa (0x4aca60, 0x4acab0) and keeps the new place; short
 * of 400 it is launched (0x4ad510 with speed 160; +0x30 160, a turn +0x24 below 360 and a lift
 * +0x28 of 5 to 7 by 0x4826c0 on 0x598d30, +0x70 0, +0x74 and +0x78 1, +0x32 1, +0x48, +0x4a and
 * +0x44 0, +0x4c 2, +0x95 4, +0x93 set) into the state 0x457a00. Then 0x457890. */
uint32_t vertrix_port_actor_fly_in_4578f0(PORT_SIGNATURE)
{
    Port port;
    uint32_t actor = entry->eax;
    uint32_t time;
    uint32_t across;
    uint32_t down;
    uint32_t eax;
    port_open(&port, calls, services, globals, entry);
    port_call_with(&port, 0x4ac500, actor, entry->edx, entry->ebx, entry->ecx, actor, entry->edi,
                   entry->ebp);
    if (port_call_with(&port, 0x4ac520, actor, vertrix_lift_edx, entry->ebx, entry->ecx, actor,
                       entry->edi, entry->ebp) != 1)
    {
        eax = port_call_with(&port, 0x457890, actor, vertrix_lift_edx, entry->ebx, entry->ecx,
                             actor, entry->edi, entry->ebp);
        return port_return(&port, eax, entry->edx);
    }
    time = port_call_with(&port, 0x4ac540, actor, vertrix_lift_edx, entry->ebx, entry->ecx, actor,
                          entry->edi, entry->ebp);
    port_call_with(&port, 0x4ac5b0, actor, vertrix_lift_edx, entry->ebx, time, actor, entry->edi,
                   entry->ebp);
    port_set16(&port, actor, 0xe, port_u16(&port, actor, 8));
    port_set16(&port, actor, 0x16, port_u16(&port, actor, 0xa));
    port_call_with(&port, 0x4aca60, actor, time, entry->ebx, time, actor, entry->edi, entry->ebp);
    port_call_with(&port, 0x4acab0, actor, time, entry->ebx, time, actor, entry->edi, entry->ebp);
    port_set16(&port, actor, 8, port_u16(&port, actor, 0xe));
    port_set16(&port, actor, 0xa, port_u16(&port, actor, 0x16));
    down = high16(port_u32(&port, actor, 8));
    if ((int32_t)down >= 0x190)
    {
        eax = port_call_with(&port, 0x457890, actor, vertrix_lift_edx, entry->ebx, down, actor,
                             entry->edi, entry->ebp);
        return port_return(&port, eax, entry->edx);
    }
    across = high16(port_u32(&port, actor, 6));
    port_call_with(&port, 0x4ad510, actor, 0xa0, across, down, actor, entry->edi, entry->ebp);
    port_set16(&port, actor, 0x30, 0xa0);
    port_set16(&port, actor, 0x24,
               port_call_with(&port, 0x4826c0, 0x598d30, 0x168, across, down, actor, entry->edi,
                              entry->ebp));
    eax = port_call_with(&port, 0x4826c0, 0x598d30, 3, across, down, actor, entry->edi, entry->ebp);
    port_set32(&port, actor, 0x70, 0);
    port_set32(&port, actor, 0x74, 1);
    port_set32(&port, actor, 0x78, 1);
    port_set16(&port, actor, 0x32, 1);
    port_set16(&port, actor, 0x48, 0);
    port_set16(&port, actor, 0x4a, 0);
    port_set16(&port, actor, 0x4c, 2);
    port_set8(&port, actor, 0x44, 0);
    port_set8(&port, actor, 0x95, 4);
    port_set16(&port, actor, 0x28, eax + 5);
    port_set8(&port, actor, 0x93, 1);
    port_call_with(&port, 0x4ac8f0, actor, 0x457a00, across, down, actor, entry->edi, entry->ebp);
    eax = port_call_with(&port, 0x457890, actor, vertrix_lift_edx, across, down, actor, entry->edi,
                         entry->ebp);
    return port_return(&port, eax, entry->edx);
}
