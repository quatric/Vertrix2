#include "beats.h"

/* Actor states that step on the beats of their timers: bursts, fades, list cursors and
 * pointer hovers. */

/* The guard record (0x4ec1ec, `guard`) of a frame routine at `record`. */
static void guard_record(Port *port, uint32_t record, uint32_t guard)
{
    port_set32(port, record, 0, port->env.chain);
    port_set32(port, record, 4, 0x4ec1ec);
    port_set32(port, record, 8, guard);
    port_set32(port, record, 0xc, 0);
}

/* Original 0x4476b0: after the timer step (0x4ac500, 0x4ac520; at a beat 0x4ac510 on the edx it
 * leaves), when 0x471c40 gives 1 for the actor's +0x14c it becomes 0x532a4c. */
uint32_t vertrix_port_actor_burst_wait_4476b0(PORT_SIGNATURE)
{
    Port port;
    uint32_t actor = entry->eax;
    uint32_t result;
    uint32_t edx;
    port_open(&port, calls, services, globals, entry);
    port_forward(&port, entry, 0x4ac500, actor, actor, entry->ebx, actor);
    edx = vertrix_lift_edx;
    if (port_forward(&port, entry, 0x4ac520, edx, edx, entry->ebx, actor) == 1)
    {
        edx = vertrix_lift_edx;
        port_forward(&port, entry, 0x4ac510, edx, edx, entry->ebx, actor);
    }
    result = port_forward(&port, entry, 0x471c40, port_u32(&port, actor, 0x14c), vertrix_lift_edx,
                          entry->ebx, actor);
    if (result == 1)
    {
        result = port_u32(&port, actor, 0x14c);
        port_set32(&port, 0, 0x532a4c, result);
    }
    return port_return(&port, result, entry->edx);
}

/* Original 0x447bc0 (guarded, 0x515234): on each beat of the actor's timer it restarts it with
 * the fade 0x32 (+0x4f) and step 5 (+0x50) and, once 0x4ad580 gives 0, moves to 0x447c60. */
uint32_t vertrix_port_actor_fade_state_447bc0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x28
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t actor = entry->eax;
    uint32_t guard = 0x515234;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    guard_record(&port, ebp - 0x24, guard);
    port_call_with(&port, 0x4ac500, actor, 0x4ec1ec, guard, actor, 0, entry->edi, ebp);
    if (port_call_with(&port, 0x4ac520, actor, vertrix_lift_edx, guard, actor, 0, entry->edi,
                       ebp) == 1)
    {
        uint32_t time = port_call_with(&port, 0x4ac540, actor, vertrix_lift_edx, guard, actor, 0,
                                       entry->edi, ebp);
        port_call_with(&port, 0x4ac5b0, actor, time, guard, actor, 0, entry->edi, ebp);
        port_set8(&port, actor, 0x4f, 0x32);
        port_set16(&port, actor, 0x50, 5);
        if (port_call_with(&port, 0x4ad580, actor, vertrix_lift_edx, guard, actor, 0, entry->edi,
                           ebp) == 0)
        {
            port_call_with(&port, 0x4ac8f0, actor, 0x447c60, guard, actor, 0, entry->edi, ebp);
        }
    }
    return port_return(&port, port_u32(&port, ebp, -0x24u), entry->edx);
}

/* Original 0x448ca0: the actor's picture state cleared (0x4ac8d0, 0x4ac950, 0x4ac700); when
 * the choice 0x532a6c is set (and, with 0x532a84 and 0x532a80 both 1, 0x418130 gives the edx it
 * leaves) the picture 0x544a34 is shown at that choice (0x4ac8d0, 0x4ac710, 0x4ac8a0); 0x4adfe0
 * when its picture (0x4ac960) changed. */
uint32_t vertrix_port_actor_choice_picture_448ca0(PORT_SIGNATURE)
{
    Port port;
    uint32_t actor = entry->eax;
    uint32_t before;
    uint32_t result;
    uint32_t edx;
    port_open(&port, calls, services, globals, entry);
    before = port_forward(&port, entry, 0x4ac960, actor, entry->edx, entry->ebx, actor);
    port_forward(&port, entry, 0x4ac8d0, actor, 0, before, actor);
    port_forward(&port, entry, 0x4ac950, actor, 0, before, actor);
    result = port_forward(&port, entry, 0x4ac700, actor, vertrix_lift_edx, before, actor);
    edx = port_u32(&port, 0, 0x532a84);
    if (edx == 1 && edx == port_u32(&port, 0, 0x532a80))
    {
        result = port_forward(&port, entry, 0x418130, result, edx, before, actor);
        edx = vertrix_lift_edx;
        if (result != edx)
        {
            goto compare;
        }
    }
    if (port_u32(&port, 0, 0x532a6c) != 0xffffffffu)
    {
        port_forward(&port, entry, 0x4ac8d0, actor, 0x544a34, before, actor);
        port_forward(&port, entry, 0x4ac710, actor, port_u32(&port, 0, 0x532a6c), before, actor);
        port_forward(&port, entry, 0x4ac8a0, actor, vertrix_lift_edx, before, actor);
        edx = vertrix_lift_edx;
    }
compare:
    result = port_forward(&port, entry, 0x4ac960, actor, edx, before, actor);
    if (before != result)
    {
        result = port_forward(&port, entry, 0x4adfe0, actor, vertrix_lift_edx, before, actor);
    }
    return port_return(&port, result, entry->edx);
}

/* Original 0x4493d0: on each beat of the actor's timer it restarts it and draws (0x449360); when
 * it holds the pointer (0x4b0b70 on 0x558944 and 0x558946, 0x7d00 while 0x558958 is set) its
 * +0x48 is 0x28 and 0x4adfe0 runs. */
uint32_t vertrix_port_actor_pointer_beat_4493d0(PORT_SIGNATURE)
{
    Port port;
    uint32_t actor = entry->eax;
    uint32_t result;
    uint32_t esi;
    uint32_t x;
    uint32_t y;
    port_open(&port, calls, services, globals, entry);
    port_forward(&port, entry, 0x4ac500, actor, entry->edx, entry->ebx, actor);
    if (port_forward(&port, entry, 0x4ac520, actor, vertrix_lift_edx, entry->ebx, actor) == 1)
    {
        result = port_forward(&port, entry, 0x4ac540, actor, vertrix_lift_edx, entry->ebx, actor);
        port_forward(&port, entry, 0x4ac5b0, actor, result, entry->ebx, actor);
        port_forward(&port, entry, 0x449360, actor, vertrix_lift_edx, entry->ebx, actor);
    }
    y = port_u32(&port, 0, 0x558958) == 0 ? port_u16(&port, 0, 0x558946) : 0x7d00;
    esi = port_u32(&port, 0, 0x558958);
    x = esi == 0 ? port_u16(&port, 0, 0x558944) : 0x7d00;
    y = (uint32_t)(int32_t)(int16_t)y;
    x = (uint32_t)(int32_t)(int16_t)x;
    result = port_forward_esi(&port, entry, 0x4b0b70, actor, x, y, actor, esi);
    if ((result & 0xff) == 0)
    {
        return port_return(&port, result, entry->edx);
    }
    port_set16(&port, actor, 0x48, 0x28);
    result = port_forward_esi(&port, entry, 0x4adfe0, actor, vertrix_lift_edx, y, actor, esi);
    return port_return(&port, result, entry->edx);
}

/* Original 0x44a0e0: the list's back arrow: unless 0x449460 (with 0x4fbf00) gives 1, it hovers
 * (0x4493d0 with 0x74) and, when the key 0x54d640 is up, takes the state 0x44a040 and the
 * choice 0x532a70 steps back (wrapping to 0x532a88 less 1) with the sound 0x5bb254 (0x48c2e0)
 * while 0x532a80 is 1; then 0x449390 with 0x4fbf04. */
uint32_t vertrix_port_list_arrow_back_44a0e0(PORT_SIGNATURE)
{
    Port port;
    uint32_t actor = entry->eax;
    uint32_t result;
    uint32_t ebx = entry->ebx;
    port_open(&port, calls, services, globals, entry);
    result = port_forward(&port, entry, 0x449460, actor, port_u32(&port, 0, 0x4fbf00), entry->ebx,
                          actor);
    if (result == 1)
    {
        return port_return(&port, result, entry->edx);
    }
    port_forward(&port, entry, 0x4493d0, actor, 0x74, entry->ebx, actor);
    if (port_forward(&port, entry, 0x476480, 0x54d640, vertrix_lift_edx, entry->ebx, actor) == 0)
    {
        uint32_t choice;
        port_forward(&port, entry, 0x4ac8f0, actor, 0x44a040, entry->ebx, actor);
        choice = port_u32(&port, 0, 0x532a70);
        if ((int32_t)choice <= 0)
        {
            port_set32(&port, 0, 0x532a70, port_u32(&port, 0, 0x532a88) - 1);
        }
        else
        {
            ebx = choice - 1;
            port_set32(&port, 0, 0x532a70, ebx);
        }
        if (port_u32(&port, 0, 0x532a80) == 1)
        {
            port_forward(&port, entry, 0x48c2e0, 0x5bb254, choice, ebx, actor);
        }
    }
    result = port_forward(&port, entry, 0x449390, actor, port_u32(&port, 0, 0x4fbf04), ebx, actor);
    return port_return(&port, result, entry->edx);
}

/* Original 0x44a210: the list's forward arrow: as 0x44a0e0 with 0x4fbf10, the state 0x44a170,
 * the choice stepping on (wrapping to 0 at 0x532a88 less 1) and 0x4fbf14. */
uint32_t vertrix_port_list_arrow_forward_44a210(PORT_SIGNATURE)
{
    Port port;
    uint32_t actor = entry->eax;
    uint32_t result;
    uint32_t ebx = entry->ebx;
    uint32_t esi = entry->esi;
    port_open(&port, calls, services, globals, entry);
    result = port_forward(&port, entry, 0x449460, actor, port_u32(&port, 0, 0x4fbf10), entry->ebx,
                          actor);
    if (result == 1)
    {
        return port_return(&port, result, entry->edx);
    }
    port_forward(&port, entry, 0x4493d0, actor, 0x74, entry->ebx, actor);
    if (port_forward(&port, entry, 0x476480, 0x54d640, vertrix_lift_edx, entry->ebx, actor) == 0)
    {
        uint32_t choice;
        port_forward(&port, entry, 0x4ac8f0, actor, 0x44a170, entry->ebx, actor);
        choice = port_u32(&port, 0, 0x532a70);
        if (port_u32(&port, 0, 0x532a88) - 1 <= choice)
        {
            ebx = 0;
            port_set32(&port, 0, 0x532a70, 0);
        }
        else
        {
            esi = choice + 1;
            port_set32(&port, 0, 0x532a70, esi);
        }
        if (port_u32(&port, 0, 0x532a80) == 1)
        {
            port_forward_esi(&port, entry, 0x48c2e0, 0x5bb254, choice, ebx, actor, esi);
        }
    }
    result = port_forward_esi(&port, entry, 0x449390, actor, port_u32(&port, 0, 0x4fbf14), ebx,
                              actor, esi);
    return port_return(&port, result, entry->edx);
}

/* Original 0x44ab50: after the timer step (0x4ac500, 0x4ac520; at a beat 0x4ac510 on the edx it
 * leaves) the actor's flags set (+0x93 1, +0x4e 100, +0x94 0, +0x95 3, +0x44 0x10), its state
 * 0x44abe0 and the sounds 0 and 4 of 0x533164 (by 0x4f819c) at the volume 0x532b9c (0x482a60). */
uint32_t vertrix_port_actor_burst_start_44ab50(PORT_SIGNATURE)
{
    Port port;
    uint32_t actor = entry->eax;
    uint32_t result;
    uint32_t edx;
    port_open(&port, calls, services, globals, entry);
    port_forward(&port, entry, 0x4ac500, actor, actor, entry->ebx, actor);
    edx = vertrix_lift_edx;
    if (port_forward(&port, entry, 0x4ac520, edx, edx, entry->ebx, actor) == 1)
    {
        edx = vertrix_lift_edx;
        port_forward(&port, entry, 0x4ac510, edx, edx, entry->ebx, actor);
    }
    port_set8(&port, actor, 0x93, 1);
    port_set8(&port, actor, 0x4e, 0x64);
    port_set8(&port, actor, 0x94, 0);
    port_set8(&port, actor, 0x95, 3);
    port_set8(&port, actor, 0x44, 0x10);
    port_forward(&port, entry, 0x4ac8f0, actor, 0x44abe0, entry->ebx, actor);
    port_forward(&port, entry, 0x482a60, 0,
                 port_u32(&port, port_u32(&port, 0, 0x4f819c) * 4, 0x533164),
                 port_u32(&port, 0, 0x532b9c), actor);
    result = port_forward(&port, entry, 0x482a60, 4,
                          port_u32(&port, port_u32(&port, 0, 0x4f819c) * 4, 0x533164),
                          port_u32(&port, 0, 0x532b9c), actor);
    return port_return(&port, result, entry->edx);
}

/* Original 0x44c6e0: the actor follows its player's (+4, 0x540f88) piece kind (+0x4c8 low byte):
 * on a change to a kind it takes the kind (+0x58), the frame of 0x53bb10 (8 a kind) less
 * 0x53bc20 (+0x64, 0x4ac510) and the state 0x44c780; to none the frame 0x44c7f0. Then
 * 0x4ac8a0. */
uint32_t vertrix_port_actor_piece_kind_44c6e0(PORT_SIGNATURE)
{
    Port port;
    uint32_t actor = entry->eax;
    uint32_t player;
    uint32_t kind;
    uint32_t edx;
    uint32_t ebx = entry->ebx;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    player = port_u32(&port, port_u32(&port, actor, 4) * 4, 0x540f88);
    kind = port_u32(&port, player, 0x4c8) & 0xff;
    edx = port_u32(&port, actor, 0x58);
    if (kind == edx)
    {
        result = port_forward(&port, entry, 0x4ac8a0, actor, edx, ebx, actor);
        return port_return(&port, result, entry->edx);
    }
    if (kind == 0)
    {
        port_forward(&port, entry, 0x4ac510, actor, 0x44c7f0, ebx, actor);
        edx = vertrix_lift_edx;
    }
    else
    {
        ebx = port_u8(&port, 0, 0x53bc20);
        edx = port_u8(&port, kind * 8, 0x53bb10) - ebx;
        port_set32(&port, actor, 0x58, kind);
        port_set32(&port, actor, 0x64, edx);
        port_forward(&port, entry, 0x4ac510, actor, edx, ebx, actor);
        edx = 0x44c780;
    }
    port_forward(&port, entry, 0x4ac8f0, actor, edx, ebx, actor);
    result = port_forward(&port, entry, 0x4ac8a0, actor, vertrix_lift_edx, ebx, actor);
    return port_return(&port, result, entry->edx);
}

/* The flash states 0x44cab0, 0x44cb50, 0x44f7e0 and 0x44f880: +0x95 3 and +0x93 1, 0x4ac1f0,
 * and on each beat of the actor's timer it restarts it with the fade `fade` and step `fade_step`
 * (0x4ad580) and the speed `speed` and step `step` (0x4ad530); once both give 0 it moves to
 * `next` and +0x95 takes `after` (when not negative). Then 0x4ac8a0. */
static uint32_t actor_flash_state(PORT_SIGNATURE, uint32_t fade, uint32_t fade_step, uint32_t speed,
                                  uint32_t step, uint32_t next, int after)
{
    Port port;
    uint32_t actor = entry->eax;
    uint32_t time;
    uint32_t faded;
    uint32_t moved;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    port_set8(&port, actor, 0x95, 3);
    port_set8(&port, actor, 0x93, 1);
    port_forward(&port, entry, 0x4ac1f0, actor, entry->edx, entry->ebx, actor);
    port_forward(&port, entry, 0x4ac500, actor, vertrix_lift_edx, entry->ebx, actor);
    if (port_forward(&port, entry, 0x4ac520, actor, vertrix_lift_edx, entry->ebx, actor) != 1)
    {
        result = port_forward(&port, entry, 0x4ac8a0, actor, vertrix_lift_edx, entry->ebx, actor);
        return port_return(&port, result, entry->edx);
    }
    time = port_forward(&port, entry, 0x4ac540, actor, vertrix_lift_edx, entry->ebx, actor);
    port_forward(&port, entry, 0x4ac5b0, actor, vertrix_lift_edx, time, actor);
    port_set8(&port, actor, 0x4f, fade);
    port_set16(&port, actor, 0x50, fade_step);
    faded = port_forward(&port, entry, 0x4ad580, actor, time, time, actor);
    port_set16(&port, actor, 0x4a, speed);
    port_set16(&port, actor, 0x4c, step);
    moved = port_forward_esi(&port, entry, 0x4ad530, actor, time, time, actor, faded);
    if (faded == 0 && moved == 0)
    {
        port_forward_esi(&port, entry, 0x4ac8f0, actor, next, time, actor, faded);
        if (after >= 0)
        {
            port_set8(&port, actor, 0x95, (uint32_t)after);
        }
    }
    result = port_forward_esi(&port, entry, 0x4ac8a0, actor, vertrix_lift_edx, time, actor, faded);
    return port_return(&port, result, entry->edx);
}

/* Original 0x44cab0: fade 100, speed 0 and step 0x10. */
uint32_t vertrix_port_actor_flash_state_44cab0(PORT_SIGNATURE)
{
    return actor_flash_state(calls, services, globals, entry, 0x64, 8, 0, 0x10, 0x44c860, -1);
}

/* Original 0x44cb50: fade 0, speed 100 and step 8. */
uint32_t vertrix_port_actor_flash_state_44cb50(PORT_SIGNATURE)
{
    return actor_flash_state(calls, services, globals, entry, 0, 8, 0x64, 8, 0x44c860, -1);
}

/* The fade frame states 0x44d560, 0x44d6d0 and 0x44e800 (+0x93 `shown` when not negative,
 * +0x4e `alpha` when `set_alpha`): 0x4ac1f0, and on each beat of the actor's timer it restarts it
 * with the fade `alpha` and step `step` (0x4ad580) and the frame `frame` and step 1 (0x4acc10);
 * once both give 0 it moves to `next`. Then 0x4ac8a0. */
static uint32_t actor_fade_frame(PORT_SIGNATURE, int shown, int set_alpha, uint32_t alpha,
                                 uint32_t step, uint32_t frame, uint32_t next)
{
    Port port;
    uint32_t actor = entry->eax;
    uint32_t time;
    uint32_t faded;
    uint32_t turned;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    if (shown >= 0)
    {
        port_set8(&port, actor, 0x93, (uint32_t)shown);
    }
    if (set_alpha)
    {
        port_set8(&port, actor, 0x4e, alpha);
    }
    port_forward(&port, entry, 0x4ac1f0, actor, entry->edx, entry->ebx, actor);
    port_forward(&port, entry, 0x4ac500, actor, vertrix_lift_edx, entry->ebx, actor);
    if (port_forward(&port, entry, 0x4ac520, actor, vertrix_lift_edx, entry->ebx, actor) != 1)
    {
        result = port_forward(&port, entry, 0x4ac8a0, actor, vertrix_lift_edx, entry->ebx, actor);
        return port_return(&port, result, entry->edx);
    }
    time = port_forward(&port, entry, 0x4ac540, actor, vertrix_lift_edx, entry->ebx, actor);
    port_forward(&port, entry, 0x4ac5b0, actor, vertrix_lift_edx, time, actor);
    port_set8(&port, actor, 0x4f, alpha);
    port_set16(&port, actor, 0x50, step);
    faded = port_forward(&port, entry, 0x4ad580, actor, time, time, actor);
    port_set8(&port, actor, 0x45, frame);
    port_set16(&port, actor, 0x46, 1);
    turned = port_forward_esi(&port, entry, 0x4acc10, actor, time, time, actor, faded);
    if (faded == 0 && turned == 0)
    {
        port_forward_esi(&port, entry, 0x4ac8f0, actor, next, time, actor, faded);
    }
    result = port_forward_esi(&port, entry, 0x4ac8a0, actor, vertrix_lift_edx, time, actor, faded);
    return port_return(&port, result, entry->edx);
}

/* Original 0x44d560: hidden, fade 0, frame 0, then 0x44c860. */
uint32_t vertrix_port_actor_fade_frame_44d560(PORT_SIGNATURE)
{
    return actor_fade_frame(calls, services, globals, entry, 0, 0, 0, 8, 0, 0x44c860);
}

/* Original 0x44d6d0: shown, alpha and fade 0x50, frame 0x10, then 0x44d760. */
uint32_t vertrix_port_actor_fade_frame_44d6d0(PORT_SIGNATURE)
{
    return actor_fade_frame(calls, services, globals, entry, 1, 1, 0x50, 8, 0x10, 0x44d760);
}

/* The pulse states 0x44d8b0 and 0x44d940: +0x95 3, 0x4ac1f0, and on each beat of the actor's
 * timer it restarts it, takes the frame `frame` and step 1 and counts the edx 0x4ac5b0 leaves
 * into +0x58; once 0x4acc10 gives 0 it moves to `next`. From a count of 30 it moves to 0x44c860.
 * Then 0x4ac8a0. */
static uint32_t block_pulse(PORT_SIGNATURE, uint32_t frame, uint32_t next)
{
    Port port;
    uint32_t actor = entry->eax;
    uint32_t time;
    uint32_t ebx;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    port_set8(&port, actor, 0x95, 3);
    port_forward(&port, entry, 0x4ac1f0, actor, entry->edx, entry->ebx, actor);
    port_forward(&port, entry, 0x4ac500, actor, vertrix_lift_edx, entry->ebx, actor);
    if (port_forward(&port, entry, 0x4ac520, actor, vertrix_lift_edx, entry->ebx, actor) != 1)
    {
        result = port_forward(&port, entry, 0x4ac8a0, actor, vertrix_lift_edx, entry->ebx, actor);
        return port_return(&port, result, entry->edx);
    }
    time = port_forward(&port, entry, 0x4ac540, actor, vertrix_lift_edx, entry->ebx, actor);
    port_forward(&port, entry, 0x4ac5b0, actor, time, entry->ebx, actor);
    port_set8(&port, actor, 0x45, frame);
    ebx = port_u32(&port, actor, 0x58) + vertrix_lift_edx;
    port_set16(&port, actor, 0x46, 1);
    port_set32(&port, actor, 0x58, ebx);
    if (port_forward(&port, entry, 0x4acc10, actor, vertrix_lift_edx, ebx, actor) == 0)
    {
        port_forward(&port, entry, 0x4ac8f0, actor, next, ebx, actor);
    }
    if ((int32_t)port_u32(&port, actor, 0x58) >= 0x1e)
    {
        port_forward(&port, entry, 0x4ac8f0, actor, 0x44c860, ebx, actor);
    }
    result = port_forward(&port, entry, 0x4ac8a0, actor, vertrix_lift_edx, ebx, actor);
    return port_return(&port, result, entry->edx);
}

/* Original 0x44d8b0: frame 0, then 0x44d940. */
uint32_t vertrix_port_block_mode_pulse_update_44d8b0(PORT_SIGNATURE)
{
    return block_pulse(calls, services, globals, entry, 0, 0x44d940);
}

/* Original 0x44d940: frame 0x10, then 0x44d8b0. */
uint32_t vertrix_port_block_mode_pulse_update_44d940(PORT_SIGNATURE)
{
    return block_pulse(calls, services, globals, entry, 0x10, 0x44d8b0);
}

/* Original 0x44d9d0: +0x95 3, 0x4ac1f0, and on each beat of the actor's timer it restarts it
 * with the frame 0x10 (0x4acc10), the speed 0x32 and step 0x14 (0x4ad530) and the fade 0 and
 * step 8; once 0x4ad580 gives 0 it moves to 0x44c860. Then 0x4ac8a0. */
uint32_t vertrix_port_block_fade_out_44d9d0(PORT_SIGNATURE)
{
    Port port;
    uint32_t actor = entry->eax;
    uint32_t time;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    port_set8(&port, actor, 0x95, 3);
    port_forward(&port, entry, 0x4ac1f0, actor, entry->edx, entry->ebx, actor);
    port_forward(&port, entry, 0x4ac500, actor, vertrix_lift_edx, entry->ebx, actor);
    if (port_forward(&port, entry, 0x4ac520, actor, vertrix_lift_edx, entry->ebx, actor) != 1)
    {
        result = port_forward(&port, entry, 0x4ac8a0, actor, vertrix_lift_edx, entry->ebx, actor);
        return port_return(&port, result, entry->edx);
    }
    time = port_forward(&port, entry, 0x4ac540, actor, vertrix_lift_edx, entry->ebx, actor);
    port_forward(&port, entry, 0x4ac5b0, actor, vertrix_lift_edx, time, actor);
    port_set8(&port, actor, 0x45, 0x10);
    port_set16(&port, actor, 0x46, 1);
    port_forward(&port, entry, 0x4acc10, actor, time, time, actor);
    port_set16(&port, actor, 0x4a, 0x32);
    port_set16(&port, actor, 0x4c, 0x14);
    port_forward(&port, entry, 0x4ad530, actor, time, time, actor);
    port_set8(&port, actor, 0x4f, 0);
    port_set16(&port, actor, 0x50, 8);
    if (port_forward(&port, entry, 0x4ad580, actor, time, time, actor) == 0)
    {
        port_forward(&port, entry, 0x4ac8f0, actor, 0x44c860, time, actor);
    }
    result = port_forward(&port, entry, 0x4ac8a0, actor, vertrix_lift_edx, time, actor);
    return port_return(&port, result, entry->edx);
}

/* The half pulse states 0x44da70 and 0x44db10: +0x95 3, 0x4ac1f0, and on each beat of the
 * actor's timer it restarts it, counts the beat into +0x58, takes the fade 0x32 and step 10
 * (0x4ad580) and the frame `frame` and step 1; once 0x4acc10 gives 0 it moves to `next`. From a
 * count of 30 it moves to 0x44c860. Then 0x4ac8a0. */
static uint32_t block_half_pulse(PORT_SIGNATURE, uint32_t frame, uint32_t next)
{
    Port port;
    uint32_t actor = entry->eax;
    uint32_t time;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    port_set8(&port, actor, 0x95, 3);
    port_forward(&port, entry, 0x4ac1f0, actor, entry->edx, entry->ebx, actor);
    port_forward(&port, entry, 0x4ac500, actor, vertrix_lift_edx, entry->ebx, actor);
    if (port_forward(&port, entry, 0x4ac520, actor, vertrix_lift_edx, entry->ebx, actor) != 1)
    {
        result = port_forward(&port, entry, 0x4ac8a0, actor, vertrix_lift_edx, entry->ebx, actor);
        return port_return(&port, result, entry->edx);
    }
    time = port_forward(&port, entry, 0x4ac540, actor, vertrix_lift_edx, entry->ebx, actor);
    port_forward(&port, entry, 0x4ac5b0, actor, vertrix_lift_edx, time, actor);
    port_set8(&port, actor, 0x4f, 0x32);
    port_set32(&port, actor, 0x58, port_u32(&port, actor, 0x58) + time);
    port_set16(&port, actor, 0x50, 0xa);
    port_forward(&port, entry, 0x4ad580, actor, time, time, actor);
    port_set8(&port, actor, 0x45, frame);
    port_set16(&port, actor, 0x46, 1);
    if (port_forward(&port, entry, 0x4acc10, actor, time, time, actor) == 0)
    {
        port_forward(&port, entry, 0x4ac8f0, actor, next, time, actor);
    }
    if ((int32_t)port_u32(&port, actor, 0x58) >= 0x1e)
    {
        port_forward(&port, entry, 0x4ac8f0, actor, 0x44c860, time, actor);
    }
    result = port_forward(&port, entry, 0x4ac8a0, actor, vertrix_lift_edx, time, actor);
    return port_return(&port, result, entry->edx);
}

/* Original 0x44da70: frame 0x10, then 0x44db10. */
uint32_t vertrix_port_block_half_pulse_update_44da70(PORT_SIGNATURE)
{
    return block_half_pulse(calls, services, globals, entry, 0x10, 0x44db10);
}

/* Original 0x44db10: frame 0, then 0x44da70. */
uint32_t vertrix_port_block_half_pulse_update_44db10(PORT_SIGNATURE)
{
    return block_half_pulse(calls, services, globals, entry, 0, 0x44da70);
}

/* Original 0x44e380: 0x4ac1f0, and on each beat of the actor's timer it restarts it with the
 * speed 0x32 and step 0x14 (moving to 0x44e410 once 0x4ad530 gives 0) and the frame 0 and step
 * 1; once 0x4acc10 gives 0 it moves to 0x44c860. Then 0x4ac8a0. */
uint32_t vertrix_port_block_collapse_update_44e380(PORT_SIGNATURE)
{
    Port port;
    uint32_t actor = entry->eax;
    uint32_t time;
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
    port_forward(&port, entry, 0x4ac5b0, actor, time, time, actor);
    port_set16(&port, actor, 0x4a, 0x32);
    port_set16(&port, actor, 0x4c, 0x14);
    if (port_forward(&port, entry, 0x4ad530, actor, vertrix_lift_edx, time, actor) == 0)
    {
        port_forward(&port, entry, 0x4ac8f0, actor, 0x44e410, time, actor);
    }
    port_set8(&port, actor, 0x45, 0);
    port_set16(&port, actor, 0x46, 1);
    if (port_forward(&port, entry, 0x4acc10, actor, time, time, actor) == 0)
    {
        port_forward(&port, entry, 0x4ac8f0, actor, 0x44c860, time, actor);
    }
    result = port_forward(&port, entry, 0x4ac8a0, actor, vertrix_lift_edx, time, actor);
    return port_return(&port, result, entry->edx);
}

/* Original 0x44e410: +0x93 1, +0x94 0, +0x95 0, 0x4ac1f0, and on each beat of the actor's timer
 * it restarts it with the speed -200 and step 10 (0x4ad530) and the frame 0 and step 1; once
 * 0x4acc10 gives 0 it moves to 0x44c860. Then 0x4ac8a0. */
uint32_t vertrix_port_block_drop_update_44e410(PORT_SIGNATURE)
{
    Port port;
    uint32_t actor = entry->eax;
    uint32_t time;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    port_set8(&port, actor, 0x93, 1);
    port_set8(&port, actor, 0x94, 0);
    port_set8(&port, actor, 0x95, 0);
    port_forward(&port, entry, 0x4ac1f0, actor, entry->edx, entry->ebx, actor);
    port_forward(&port, entry, 0x4ac500, actor, vertrix_lift_edx, entry->ebx, actor);
    if (port_forward(&port, entry, 0x4ac520, actor, vertrix_lift_edx, entry->ebx, actor) != 1)
    {
        result = port_forward(&port, entry, 0x4ac8a0, actor, vertrix_lift_edx, entry->ebx, actor);
        return port_return(&port, result, entry->edx);
    }
    time = port_forward(&port, entry, 0x4ac540, actor, vertrix_lift_edx, entry->ebx, actor);
    port_forward(&port, entry, 0x4ac5b0, actor, vertrix_lift_edx, time, actor);
    port_set16(&port, actor, 0x4a, 0xff38);
    port_set16(&port, actor, 0x4c, 0xa);
    port_forward(&port, entry, 0x4ad530, actor, time, time, actor);
    port_set8(&port, actor, 0x45, 0);
    port_set16(&port, actor, 0x46, 1);
    if (port_forward(&port, entry, 0x4acc10, actor, time, time, actor) == 0)
    {
        port_forward(&port, entry, 0x4ac8f0, actor, 0x44c860, time, actor);
    }
    result = port_forward(&port, entry, 0x4ac8a0, actor, vertrix_lift_edx, time, actor);
    return port_return(&port, result, entry->edx);
}

/* Original 0x44e800: fade 100 and step 6, frame 0x10, then 0x44e890. */
uint32_t vertrix_port_actor_fade_frame_44e800(PORT_SIGNATURE)
{
    return actor_fade_frame(calls, services, globals, entry, -1, 0, 0x64, 6, 0x10, 0x44e890);
}

/* Original 0x44e890: 0x4ac1f0, and on each beat of the actor's timer it restarts it and its
 * period (0x4ac470) grows from a twelfth of +0xd0 by the beat up to +0x58; there it moves to
 * 0x44c860. Then 0x4ac8a0. */
uint32_t vertrix_port_block_period_update_44e890(PORT_SIGNATURE)
{
    Port port;
    uint32_t actor = entry->eax;
    uint32_t time;
    uint32_t limit;
    uint32_t ebx;
    uint32_t result;
    int32_t twelfth;
    port_open(&port, calls, services, globals, entry);
    port_forward(&port, entry, 0x4ac1f0, actor, entry->edx, entry->ebx, actor);
    port_forward(&port, entry, 0x4ac500, actor, vertrix_lift_edx, entry->ebx, actor);
    if (port_forward(&port, entry, 0x4ac520, actor, vertrix_lift_edx, entry->ebx, actor) != 1)
    {
        result = port_forward(&port, entry, 0x4ac8a0, actor, vertrix_lift_edx, entry->ebx, actor);
        return port_return(&port, result, entry->edx);
    }
    time = port_forward(&port, entry, 0x4ac540, actor, vertrix_lift_edx, entry->ebx, actor);
    port_forward_esi(&port, entry, 0x4ac5b0, actor, vertrix_lift_edx, entry->ebx, actor, time);
    twelfth = (int32_t)port_u32(&port, actor, 0xd0) / 0xc;
    limit = port_u32(&port, actor, 0x58);
    if (twelfth >= (int32_t)limit)
    {
        ebx = limit;
    }
    else
    {
        ebx = (uint32_t)twelfth + time;
        if ((int32_t)ebx > (int32_t)limit)
        {
            ebx = limit;
        }
        port_forward_esi(&port, entry, 0x4ac470, actor, ebx, ebx, actor, time);
        if (ebx != port_u32(&port, actor, 0x58))
        {
            result =
                port_forward_esi(&port, entry, 0x4ac8a0, actor, vertrix_lift_edx, ebx, actor, time);
            return port_return(&port, result, entry->edx);
        }
    }
    port_forward_esi(&port, entry, 0x4ac8f0, actor, 0x44c860, ebx, actor, time);
    result = port_forward_esi(&port, entry, 0x4ac8a0, actor, vertrix_lift_edx, ebx, actor, time);
    return port_return(&port, result, entry->edx);
}

/* Original 0x44ec40: 0x4ac1f0, and on each beat of the actor's timer it restarts it and moves
 * from its home (+8, +0xa) by 0x4aca60 and 0x4acab0, which then becomes its home; once both give
 * 0 it moves to 0x44c860. Then 0x4ac8a0. */
uint32_t vertrix_port_block_slide_update_44ec40(PORT_SIGNATURE)
{
    Port port;
    uint32_t actor = entry->eax;
    uint32_t time;
    uint32_t across;
    uint32_t down;
    uint32_t ebx;
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
    port_set16(&port, actor, 0xe, port_u16(&port, actor, 8));
    port_set16(&port, actor, 0x16, port_u16(&port, actor, 0xa));
    across = port_forward(&port, entry, 0x4aca60, actor, time, time, actor);
    down = port_forward_esi(&port, entry, 0x4acab0, actor, time, time, actor, across);
    port_set16(&port, actor, 8, port_u16(&port, actor, 0xe));
    port_set16(&port, actor, 0xa, port_u16(&port, actor, 0x16));
    port_set16(&port, actor, 0xe, port_u16(&port, actor, 8));
    port_set16(&port, actor, 0x16, port_u16(&port, actor, 0xa));
    ebx = (time & 0xffff0000u) | port_u16(&port, actor, 0xa);
    if (across == 0 && down == 0)
    {
        port_forward_esi(&port, entry, 0x4ac8f0, actor, 0x44c860, ebx, actor, across);
    }
    result = port_forward_esi(&port, entry, 0x4ac8a0, actor, vertrix_lift_edx, ebx, actor, across);
    return port_return(&port, result, entry->edx);
}

/* Original 0x44f7e0: fade 0 and step 8, speed -100 and step 8, then 0x44c860 with +0x95 3. */
uint32_t vertrix_port_actor_flash_state_44f7e0(PORT_SIGNATURE)
{
    return actor_flash_state(calls, services, globals, entry, 0, 8, 0xff9c, 8, 0x44c860, 3);
}

/* Original 0x44f880: fade 100 and step 4, speed 100 and step 4, then 0x44f920 with +0x95 1. */
uint32_t vertrix_port_actor_flash_state_44f880(PORT_SIGNATURE)
{
    return actor_flash_state(calls, services, globals, entry, 0x64, 4, 0x64, 4, 0x44f920, 1);
}

/* Original 0x44fc60: the number actor shows its player's progress: the player (0x4b5eb0 on the
 * list 0x54671c by +4; its +4 into 0x540f88) unchanged (+0x180 against +0x178) leaves it at
 * 0x4adfa0 with 0; otherwise it rises (+0x48 -100, 0x4adfa0 with 1, 0x4ac510) toward 0x44fe30
 * at the goal (0x532bc8 1 and 0x532b34), otherwise 0x44fcf0. */
uint32_t vertrix_port_number_transition_configured_44fc60(PORT_SIGNATURE)
{
    Port port;
    uint32_t actor = entry->eax;
    uint32_t number;
    uint32_t player;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    number = port_forward(&port, entry, 0x4b5eb0, 0x54671c, port_u32(&port, actor, 4), entry->ebx,
                          actor);
    player = port_u32(&port, port_u32(&port, number, 4) * 4, 0x540f88);
    result = port_forward_esi(&port, entry, 0x4adfa0, actor, 0, number, actor, player);
    if (port_u32(&port, number, 0x180) == port_u32(&port, player, 0x178))
    {
        return port_return(&port, result, entry->edx);
    }
    port_set16(&port, actor, 0x48, 0xff9c);
    port_forward_esi(&port, entry, 0x4adfa0, actor, 1, number, actor, player);
    port_forward_esi(&port, entry, 0x4ac510, actor, vertrix_lift_edx, number, actor, player);
    if (port_u32(&port, 0, 0x532bc8) == 1 &&
        port_u32(&port, 0, 0x532b34) == port_u32(&port, player, 0x178))
    {
        result = port_forward_esi(&port, entry, 0x4ac8f0, actor, 0x44fe30, number, actor, player);
    }
    else
    {
        result = port_forward_esi(&port, entry, 0x4ac8f0, actor, 0x44fcf0, number, actor, player);
    }
    return port_return(&port, result, entry->edx);
}
