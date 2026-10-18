#include "bobs.h"

/* Actor wobbles, grows, shows, menu waits and moves, the cursor ease and the attack enter. */

/* The guard record (0x4ec1ec, `guard`) of a frame routine at `record`. */
static void guard_record(Port *port, uint32_t record, uint32_t guard)
{
    port_set32(port, record, 0, port->env.chain);
    port_set32(port, record, 4, 0x4ec1ec);
    port_set32(port, record, 8, guard);
    port_set32(port, record, 0xc, 0);
}

/* Original 0x44a610: when due (0x4ac500, 0x4ac520) the actor restarts (0x4ac510 with 150, then
 * 0x4ac7d0 with 100 plus a draw of 0x4826c0 on 0x598d30), its x (+0xe) is +0x58 and its y (+0x16)
 * +0x64, one more when it was there; a draw of 2 tilts +0x48 down to -4 or up to 8 and 0x4adfe0
 * applies it. */
uint32_t vertrix_port_actor_wobble_44a610(PORT_SIGNATURE)
{
    Port port;
    uint32_t actor = entry->eax;
    uint32_t result;
    uint32_t tilt;
    port_open(&port, calls, services, globals, entry);
    port_forward(&port, entry, 0x4ac500, actor, entry->edx, entry->ebx, actor);
    result =
        port_forward_esi(&port, entry, 0x4ac520, actor, vertrix_lift_edx, 8, actor, 0xfffffffc);
    if (result != 1)
    {
        return port_return(&port, result, entry->edx);
    }
    port_forward_esi(&port, entry, 0x4ac510, actor, 0x96, 8, actor, 0xfffffffc);
    result =
        port_forward_esi(&port, entry, 0x4826c0, 0x598d30, vertrix_lift_edx, 8, actor, 0xfffffffc);
    port_forward_esi(&port, entry, 0x4ac7d0, actor, (result & 0xffff) + 0x64, 8, actor, 0xfffffffc);
    port_set16(&port, actor, 0xe, port_u16(&port, actor, 0x58));
    if ((uint32_t)(int32_t)(int16_t)port_u16(&port, actor, 0x16) == port_u32(&port, actor, 0x64))
    {
        port_set16(&port, actor, 0x16, port_u16(&port, actor, 0x64) + 1);
    }
    else
    {
        port_set16(&port, actor, 0x16, port_u16(&port, actor, 0x64));
    }
    result = port_forward_esi(&port, entry, 0x4826c0, 0x598d30, 2, 8, actor, 0xfffffffc);
    if ((result & 0xffff) != 0)
    {
        tilt = port_u16(&port, actor, 0x48) - 1;
        port_set16(&port, actor, 0x48, tilt);
        if ((int16_t)tilt < -4)
        {
            port_set16(&port, actor, 0x48, 0xfffc);
        }
    }
    else
    {
        tilt = port_u16(&port, actor, 0x48) + 1;
        port_set16(&port, actor, 0x48, tilt);
        if ((int16_t)tilt > 8)
        {
            port_set16(&port, actor, 0x48, 8);
        }
    }
    result =
        port_forward_esi(&port, entry, 0x4adfe0, actor, vertrix_lift_edx, 8, actor, 0xfffffffc);
    return port_return(&port, result, entry->edx);
}

/* Original 0x44bba0: when due (guarded 0x515340) the actor's +0x45 is 16 and +0x46 1 (0x4adfe0);
 * when 0x4acc10 is done it takes the state 0x44bc50. */
uint32_t vertrix_port_actor_grow_start_44bba0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x28
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t actor = entry->eax;
    uint32_t guard = 0x515340;
    uint32_t amount;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    guard_record(&port, ebp - 0x24, guard);
    port_call_with(&port, 0x4ac500, actor, 0x4ec1ec, guard, actor, 0, entry->edi, ebp);
    if (port_call_with(&port, 0x4ac520, actor, vertrix_lift_edx, guard, actor, 0, entry->edi,
                       ebp) == 1)
    {
        amount = port_call_with(&port, 0x4ac540, actor, vertrix_lift_edx, guard, actor, 0,
                                entry->edi, ebp);
        port_call_with(&port, 0x4ac5b0, actor, amount, guard, actor, 0, entry->edi, ebp);
        port_set8(&port, actor, 0x45, 0x10);
        port_set16(&port, actor, 0x46, 1);
        port_call_with(&port, 0x4adfe0, actor, vertrix_lift_edx, guard, actor, 0, entry->edi, ebp);
        if (port_call_with(&port, 0x4acc10, actor, vertrix_lift_edx, guard, actor, 0, entry->edi,
                           ebp) == 0)
        {
            port_call_with(&port, 0x4ac8f0, actor, 0x44bc50, guard, actor, 0, entry->edi, ebp);
        }
    }
    return port_return(&port, port_u32(&port, ebp, -0x24u), entry->edx);
}

/* Original 0x44beb0: after the timer step (guarded 0x515348; at a beat 0x4ac510) and 0x4adfe0 on
 * the edx each leaves, the actor those give is shown (+0x93 1, +0x4e 80, +0x44 16), takes the
 * state 0x44bf70 and the sounds 0 and 4 of 0x533164 (by 0x4f819c) play at the volume 0x532b9c
 * (0x482a60). */
uint32_t vertrix_port_actor_show_sounds_44beb0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x28
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t actor = entry->eax;
    uint32_t guard = 0x515348;
    uint32_t shown;
    uint32_t edx;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    guard_record(&port, ebp - 0x24, guard);
    port_call_with(&port, 0x4ac500, actor, actor, guard, 0x4ec1ec, 0, entry->edi, ebp);
    shown = vertrix_lift_edx;
    if (port_call_with(&port, 0x4ac520, shown, shown, guard, shown, 0, entry->edi, ebp) == 1)
    {
        edx = vertrix_lift_edx;
        port_call_with(&port, 0x4ac510, edx, edx, guard, shown, 0, entry->edi, ebp);
    }
    edx = vertrix_lift_edx;
    port_call_with(&port, 0x4adfe0, edx, edx, guard, shown, 0, entry->edi, ebp);
    port_set8(&port, shown, 0x93, 1);
    port_set8(&port, shown, 0x4e, 0x50);
    port_set8(&port, shown, 0x44, 0x10);
    port_call_with(&port, 0x4ac8f0, shown, 0x44bf70, guard, shown, 0, entry->edi, ebp);
    port_call_with(&port, 0x482a60, 0, port_u32(&port, port_u32(&port, 0, 0x4f819c) * 4, 0x533164),
                   port_u32(&port, 0, 0x532b9c), shown, 0, entry->edi, ebp);
    port_call_with(&port, 0x482a60, 4, port_u32(&port, port_u32(&port, 0, 0x4f819c) * 4, 0x533164),
                   port_u32(&port, 0, 0x532b9c), shown, 0, entry->edi, ebp);
    return port_return(&port, port_u32(&port, ebp, -0x24u), entry->edx);
}

/* Original 0x44c1a0: after the timer step (guarded 0x515368; at a beat 0x4ac510 on the edx it
 * leaves), while 0x532a84 is 1: with 0x532a80 also 1 and 0x418130 0 the actor the edx gives is
 * shown (0x4adfe0, +0x48 0, +0x4e 80) and +0x44 0 with the state 0x44bba0; otherwise 0x418110 at
 * 1 gives the state 0x44c260. */
uint32_t vertrix_port_actor_menu_wait_44c1a0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x2c
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t actor = entry->eax;
    uint32_t guard = 0x515368;
    uint32_t shown;
    uint32_t edx;
    uint32_t result;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    guard_record(&port, ebp - 0x28, guard);
    port_call_with(&port, 0x4ac500, actor, actor, guard, 0x4ec1ec, 0, entry->edi, ebp);
    shown = vertrix_lift_edx;
    result = port_call_with(&port, 0x4ac520, shown, shown, guard, shown, 0, entry->edi, ebp);
    if (result == 1)
    {
        edx = vertrix_lift_edx;
        result = port_call_with(&port, 0x4ac510, edx, edx, guard, shown, 0, entry->edi, ebp);
    }
    if (port_u32(&port, 0, 0x532a84) != 1)
    {
        return port_return(&port, port_u32(&port, ebp, -0x28u), entry->edx);
    }
    if (port_u32(&port, 0, 0x532a80) == 1)
    {
        result = port_call_with(&port, 0x418130, result, vertrix_lift_edx, guard, shown, 0, 1, ebp);
        if (result == 0)
        {
            edx = vertrix_lift_edx;
            port_call_with(&port, 0x4adfe0, edx, edx, guard, shown, 0, 1, ebp);
            edx = vertrix_lift_edx;
            port_set16(&port, edx, 0x48, 0);
            port_set8(&port, edx, 0x4e, 0x50);
            port_set8(&port, shown, 0x44, 0);
            port_call_with(&port, 0x4ac8f0, shown, 0x44bba0, guard, shown, 0, 1, ebp);
            return port_return(&port, port_u32(&port, ebp, -0x28u), entry->edx);
        }
    }
    if (port_call_with(&port, 0x418110, result, vertrix_lift_edx, guard, shown, 0, 1, ebp) == 1)
    {
        port_call_with(&port, 0x4ac8f0, shown, 0x44c260, guard, shown, 0, 1, ebp);
    }
    return port_return(&port, port_u32(&port, ebp, -0x28u), entry->edx);
}

/* Original 0x44e2d0: after 0x4ac1f0 and, when due, the move: the distance between the words +0xe
 * and +0x10 (made positive, then signed) gives +0x48 (100 a unit over 60) and +0x12 (4 a unit over
 * 60, plus 1); when 0x4aca60 is done the state 0x44c860. Then 0x4ac8a0. */
uint32_t vertrix_port_actor_move_span_44e2d0(PORT_SIGNATURE)
{
    Port port;
    uint32_t actor = entry->eax;
    uint32_t amount;
    uint32_t span;
    int32_t distance;
    port_open(&port, calls, services, globals, entry);
    port_forward(&port, entry, 0x4ac1f0, actor, entry->edx, entry->ebx, actor);
    port_forward(&port, entry, 0x4ac500, actor, vertrix_lift_edx, entry->ebx, actor);
    if (port_forward(&port, entry, 0x4ac520, actor, vertrix_lift_edx, entry->ebx, actor) == 1)
    {
        uint32_t result;
        amount = port_forward(&port, entry, 0x4ac540, actor, vertrix_lift_edx, entry->ebx, actor);
        port_forward(&port, entry, 0x4ac5b0, actor, vertrix_lift_edx, amount, actor);
        distance = (int16_t)port_u16(&port, actor, 0x10) - (int16_t)port_u16(&port, actor, 0xe);
        span = (uint32_t)(int32_t)(int16_t)(distance < 0 ? -distance : distance);
        port_set16(&port, actor, 0x48, span * 100 / 0x3c);
        port_set16(&port, actor, 0x12, span * 4 / 0x3c + 1);
        result =
            port_call_with(&port, 0x4aca60, actor, amount, amount, actor, span, 0x3c, entry->ebp);
        if (result == 0)
        {
            port_call_with(&port, 0x4ac8f0, actor, 0x44c860, amount, actor, span, 0x3c, entry->ebp);
            return port_return(&port,
                               port_call_with(&port, 0x4ac8a0, actor, vertrix_lift_edx, amount,
                                              actor, span, 0x3c, entry->ebp),
                               entry->edx);
        }
        return port_return(&port,
                           port_call_with(&port, 0x4ac8a0, actor, vertrix_lift_edx, amount, actor,
                                          span, 0x3c, entry->ebp),
                           entry->edx);
    }
    return port_return(
        &port, port_forward(&port, entry, 0x4ac8a0, actor, vertrix_lift_edx, entry->ebx, actor),
        entry->edx);
}

/* Original 0x44e6e0: after 0x4ac1f0 and, when due, the speed +0xd0 over 12 less the step (at
 * least 1; just 1 at a speed of 1 or less, without 0x4ac470) is set (0x4ac470) and the actor bobs
 * to height 50 at speed 2 (0x4ad530); once that is done at speed 1 the state 0x44c860. Then
 * 0x4ac8a0. */
uint32_t vertrix_port_block_accelerate_update_44e6e0(PORT_SIGNATURE)
{
    Port port;
    uint32_t actor = entry->eax;
    uint32_t ebx = entry->ebx;
    uint32_t amount;
    int32_t speed;
    port_open(&port, calls, services, globals, entry);
    port_forward(&port, entry, 0x4ac1f0, actor, entry->edx, ebx, actor);
    port_forward(&port, entry, 0x4ac500, actor, vertrix_lift_edx, ebx, actor);
    if (port_forward(&port, entry, 0x4ac520, actor, vertrix_lift_edx, ebx, actor) == 1)
    {
        amount = port_forward(&port, entry, 0x4ac540, actor, vertrix_lift_edx, ebx, actor);
        port_call_with(&port, 0x4ac5b0, actor, vertrix_lift_edx, ebx, actor, amount, amount,
                       entry->ebp);
        speed = (int32_t)port_u32(&port, actor, 0xd0) / 12;
        if (speed <= 1)
        {
            ebx = 1;
        }
        else
        {
            ebx = (uint32_t)speed - amount;
            if ((int32_t)ebx < 1)
            {
                ebx = 1;
            }
            port_call_with(&port, 0x4ac470, actor, ebx, ebx, actor, amount, amount, entry->ebp);
        }
        port_set16(&port, actor, 0x4a, 0x32);
        port_set16(&port, actor, 0x4c, 2);
        if (port_call_with(&port, 0x4ad530, actor, amount, ebx, actor, amount, amount,
                           entry->ebp) == 0 &&
            ebx == 1)
        {
            port_call_with(&port, 0x4ac8f0, actor, 0x44c860, ebx, actor, amount, amount,
                           entry->ebp);
        }
        return port_return(&port,
                           port_call_with(&port, 0x4ac8a0, actor, vertrix_lift_edx, ebx, actor,
                                          amount, amount, entry->ebp),
                           entry->edx);
    }
    return port_return(&port,
                       port_forward(&port, entry, 0x4ac8a0, actor, vertrix_lift_edx, ebx, actor),
                       entry->edx);
}

/* Original 0x450d40: when due (0x4ac500, 0x4ac520 on the edx each leaves) the cursor the edx
 * gives eases its height +0x58 by the step towards its player's (+4, 0x540f88) target 0x43b870
 * and spans (+0x8e 3) from its x (+0xe; +0xa8, +0xaa with 0x4f89a8 less 1) and y (+0x16 plus
 * 0x4f89ac; +0xae and less the height +0xac). */
uint32_t vertrix_port_cursor_ease_450d40(PORT_SIGNATURE)
{
    Port port;
    uint32_t actor = entry->eax;
    uint32_t edx;
    uint32_t amount;
    uint32_t target;
    uint32_t height;
    uint32_t x;
    uint32_t y;
    port_open(&port, calls, services, globals, entry);
    port_forward(&port, entry, 0x4ac500, actor, actor, entry->ebx, entry->ecx);
    edx = vertrix_lift_edx;
    target = port_forward(&port, entry, 0x4ac520, edx, edx, entry->ebx, entry->ecx);
    if (target != 1)
    {
        return port_return(&port, target, entry->edx);
    }
    edx = vertrix_lift_edx;
    amount = port_forward(&port, entry, 0x4ac540, edx, edx, entry->ebx, entry->ecx);
    edx = vertrix_lift_edx;
    port_forward(&port, entry, 0x4ac5b0, edx, edx, entry->ebx, amount);
    edx = vertrix_lift_edx;
    target =
        port_forward(&port, entry, 0x43b870, port_u32(&port, port_u32(&port, edx, 4) * 4, 0x540f88),
                     edx, entry->ebx, amount);
    edx = vertrix_lift_edx;
    height = port_u32(&port, edx, 0x58);
    if ((int32_t)target < (int32_t)height)
    {
        height -= amount;
        port_set32(&port, edx, 0x58, height);
        if ((int32_t)target > (int32_t)height)
        {
            port_set32(&port, edx, 0x58, target);
        }
    }
    else if (target != height)
    {
        height += amount;
        port_set32(&port, edx, 0x58, height);
        if ((int32_t)target < (int32_t)height)
        {
            port_set32(&port, edx, 0x58, target);
        }
    }
    x = (uint32_t)(int32_t)(int16_t)port_u16(&port, edx, 0xe);
    y = (uint32_t)(int32_t)(int16_t)port_u16(&port, edx, 0x16) + port_u32(&port, 0, 0x4f89ac);
    port_set8(&port, edx, 0x8e, 3);
    port_set16(&port, edx, 0xa8, x);
    port_set16(&port, edx, 0xae, y);
    port_set16(&port, edx, 0xaa, port_u32(&port, 0, 0x4f89a8) + x - 1);
    port_set16(&port, edx, 0xac, y - port_u32(&port, edx, 0x58));
    return port_return(&port, x, entry->edx);
}

/* Original 0x4522c0: the attack enter: when the opponent (+0x3b0) is armed (+0x4c5), not
 * blocked (+0x4cc 1) and not yet hit (+0x3f4), 0x43bce0 and 0x43bd00 hit it (+0x3f4 1) and its
 * board's +0xb80, +0xb84 and +0xb88 are 1. The board draws (method +4); when the opponent was not
 * armed 0x43bbf0 follows. */
uint32_t vertrix_port_object_enter_attack_4522c0(PORT_SIGNATURE)
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
    uint32_t ebx;
    uint32_t edi = 0;
    uint32_t methods;
    uint32_t result;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, -0x18u, actor);
    opponent = port_u32(&port, actor, 0x3b0);
    board = port_u32(&port, actor, 0x15c);
    ebx = (entry->ebx & 0xffffff00u) | port_u8(&port, opponent, 0x4c5);
    other = port_u32(&port, opponent, 0x15c);
    if ((ebx & 0xff) == 0)
    {
        edi = 1;
    }
    else
    {
        ebx = (ebx & 0xffffff00u) | port_u8(&port, opponent, 0x4cc);
        if ((ebx & 0xff) != 1 && port_u32(&port, opponent, 0x3f4) == 0)
        {
            uint32_t edx;
            port_call_with(&port, 0x43bce0, opponent, actor, ebx, board, other, edi, ebp);
            edx = vertrix_lift_edx;
            port_set32(&port, edx, 0x3f4, 1);
            port_call_with(&port, 0x43bd00, edx, edx, ebx, board, other, edi, ebp);
            port_set32(&port, other, 0xb80, 1);
            port_set32(&port, other, 0xb84, 1);
            port_set32(&port, other, 0xb88, 1);
        }
    }
    methods = port_u32(&port, board, 0x158);
    result = port_call_with(&port, port_u32(&port, methods, 4), board, methods, ebx, board, other,
                            edi, ebp);
    if (edi != 1)
    {
        return port_return(&port, result, entry->edx);
    }
    result = port_call_with(&port, 0x43bbf0, port_u32(&port, ebp, -0x18u), vertrix_lift_edx, ebx,
                            board, other, edi, ebp);
    return port_return(&port, result, entry->edx);
}
