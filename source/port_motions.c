#include "port_motions.h"

/* Board view setup and the timed motion states of the menu and effect actors. */

/* A call handing the callee esi, edi and ebp as given and `count` stack dwords. */
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

/* The guard record (0x4ec1ec, `guard`) of a frame routine at `record`. */
static void guard_record(Port *port, uint32_t record, uint32_t guard)
{
    port_set32(port, record, 0, port->env.chain);
    port_set32(port, record, 4, 0x4ec1ec);
    port_set32(port, record, 8, guard);
    port_set32(port, record, 0xc, 0);
}

/* Original 0x43bbf0: the player's view set up by 0x482110 (on +0x19c with +0x4c4, +0x4c5, +0x4cc,
 * +0x194, +0x198, the board's +0xb80, +0xc0, +0xb84 and +0xb88), its state set to the handler
 * it gives, the board's +0xb90 1, then 0x4726d0 and 0x43ad50. */
uint32_t vertrix_port_board_view_setup_43bbf0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x18
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t player = entry->eax;
    uint32_t board;
    uint32_t pushed[11];
    uint32_t result;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    board = port_u32(&port, player, 0x15c);
    pushed[0] = player + 0x4cc;
    pushed[1] = player + 0x194;
    pushed[2] = player + 0x198;
    pushed[3] = 0;
    pushed[4] = ebp - 0x14;
    pushed[5] = board + 0xb80;
    pushed[6] = board + 0xc0;
    pushed[7] = 0;
    pushed[8] = 0;
    pushed[9] = board + 0xb84;
    pushed[10] = board + 0xb88;
    call_frame(&port, 0x482110, player + 0x19c, player + 0x4c4, player + 0x4c5, 0, player,
               entry->edi, ebp, pushed, 11);
    call_frame(&port, 0x4ac8f0, player, port_u32(&port, ebp, -0x14u), player + 0x4c5, 0, player,
               entry->edi, ebp, NULL, 0);
    board = port_u32(&port, player, 0x15c);
    port_set32(&port, board, 0xb90, 1);
    call_frame(&port, 0x4726d0, board, vertrix_lift_edx, player + 0x4c5, 0, player, entry->edi, ebp,
               NULL, 0);
    result = call_frame(&port, 0x43ad50, player, vertrix_lift_edx, player + 0x4c5, 0, player,
                        entry->edi, ebp, NULL, 0);
    return port_return(&port, result, entry->edx);
}

/* The cursor follow states 0x443320 and 0x4433c0: the actor at the pointer (0x558944 and
 * 0x558946, 0x7d00 while 0x558958 is set), and on each beat of its timer (0x4ac500, 0x4ac520) it
 * restarts it (0x4ac540, 0x4ac5b0), takes `frame` (+0x45) and the step 1 (+0x46) and, once
 * 0x4acc10 gives 0, moves to `next`; then 0x4ac1f0 and 0x4ac8a0. */
static uint32_t actor_follow_pointer(PORT_SIGNATURE, uint32_t frame, uint32_t next)
{
    Port port;
    uint32_t actor = entry->eax;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    port_set16(&port, actor, 0xe,
               port_u32(&port, 0, 0x558958) == 0 ? port_u16(&port, 0, 0x558944) : 0x7d00);
    port_set16(&port, actor, 0x16,
               port_u32(&port, 0, 0x558958) == 0 ? port_u16(&port, 0, 0x558946) : 0x7d00);
    port_forward(&port, entry, 0x4ac500, actor, entry->edx, entry->ebx, actor);
    if (port_forward(&port, entry, 0x4ac520, actor, vertrix_lift_edx, entry->ebx, actor) == 1)
    {
        result = port_forward(&port, entry, 0x4ac540, actor, vertrix_lift_edx, entry->ebx, actor);
        port_forward(&port, entry, 0x4ac5b0, actor, result, entry->ebx, actor);
        port_set8(&port, actor, 0x45, frame);
        port_set16(&port, actor, 0x46, 1);
        if (port_forward(&port, entry, 0x4acc10, actor, vertrix_lift_edx, entry->ebx, actor) == 0)
        {
            port_forward(&port, entry, 0x4ac8f0, actor, next, entry->ebx, actor);
        }
    }
    port_forward(&port, entry, 0x4ac1f0, actor, vertrix_lift_edx, entry->ebx, actor);
    result = port_forward(&port, entry, 0x4ac8a0, actor, vertrix_lift_edx, entry->ebx, actor);
    return port_return(&port, result, entry->edx);
}

/* Original 0x443320: frame 0, then 0x4433c0. */
uint32_t vertrix_port_actor_follow_pointer_443320(PORT_SIGNATURE)
{
    return actor_follow_pointer(calls, services, globals, entry, 0, 0x4433c0);
}

/* Original 0x4433c0: frame 0x10, then 0x443320. */
uint32_t vertrix_port_actor_follow_pointer_4433c0(PORT_SIGNATURE)
{
    return actor_follow_pointer(calls, services, globals, entry, 0x10, 0x443320);
}

/* Original 0x444b50: on each beat of the actor's timer (0x4ac500, 0x4ac520) it restarts it
 * (0x4ac540, 0x4ac5b0), takes its place from 0x4ad060 and 0x4ad260, the speed -100 (+0x4a) and
 * the step 5 (+0x4c), and once 0x4ad530 gives 0 its state is cleared (0x4ac8f0 with 0). */
uint32_t vertrix_port_actor_rise_start_444b50(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x1c
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t actor = entry->eax;
    uint32_t result;
    uint32_t time;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_forward(&port, entry, 0x4ac500, actor, entry->edx, entry->ebx, actor);
    result = port_forward(&port, entry, 0x4ac520, actor, vertrix_lift_edx, entry->ebx, actor);
    if (result != 1)
    {
        return port_return(&port, result, entry->edx);
    }
    time = port_forward(&port, entry, 0x4ac540, actor, vertrix_lift_edx, entry->ebx, actor);
    port_forward_esi(&port, entry, 0x4ac5b0, actor, vertrix_lift_edx, entry->ebx, actor, time);
    port_forward_esi(&port, entry, 0x4ad060, actor, time, ebp - 0x14, actor, time);
    port_forward_esi(&port, entry, 0x4ad260, actor, ebp - 0x18, ebp - 0x14, actor, time);
    port_set16(&port, actor, 0xe, port_u16(&port, ebp, -0x18u));
    port_set16(&port, actor, 0x4a, 0xff9c);
    port_set16(&port, actor, 0x16, port_u16(&port, ebp, -0x14u));
    port_set16(&port, actor, 0x4c, 5);
    result = port_forward_esi(&port, entry, 0x4ad530, actor, time, ebp - 0x14, actor, time);
    if (result != 0)
    {
        return port_return(&port, result, entry->edx);
    }
    result = port_forward_esi(&port, entry, 0x4ac8f0, actor, 0, ebp - 0x14, actor, time);
    return port_return(&port, result, entry->edx);
}

/* Original 0x444be0: the actor shakes around its home (+0x10, +0x18) by the offsets 0x4fbbf0 and
 * 0x4fbc00 of its phase +0x64, which steps (mod 4) on each beat of its timer (0x4ac7b0 with 4,
 * 0x4ac500, 0x4ac520, 0x4ac540, 0x4ac5b0). */
uint32_t vertrix_port_actor_shake_444be0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x38
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t actor = entry->eax;
    uint32_t esi = 0x4fbc10;
    uint32_t edi = ebp - 0x14;
    uint32_t eax;
    uint32_t phase;
    uint32_t k;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    /* The phase can index past the offsets into the saved registers. */
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -4u, entry->ebx);
    port_set32(&port, ebp, -8u, entry->ecx);
    port_set32(&port, ebp, -0xcu, entry->edx);
    port_set32(&port, ebp, -0x10u, entry->esi);
    port_set32(&port, ebp, -0x14u, entry->edi);
    for (k = 0; k < 0x10; k += 4)
    {
        port_set32(&port, ebp - 0x34 + k, 0, port_u32(&port, 0x4fbbf0 + k, 0));
        port_set32(&port, ebp - 0x24 + k, 0, port_u32(&port, 0x4fbc00 + k, 0));
    }
    port_call_with(&port, 0x4ac7b0, actor, 4, entry->ebx, actor, esi, edi, ebp);
    port_call_with(&port, 0x4ac500, actor, vertrix_lift_edx, entry->ebx, actor, esi, edi, ebp);
    eax =
        port_call_with(&port, 0x4ac520, actor, vertrix_lift_edx, entry->ebx, actor, esi, edi, ebp);
    if (eax == 1)
    {
        port_call_with(&port, 0x4ac540, actor, vertrix_lift_edx, entry->ebx, actor, esi, edi, ebp);
        eax = port_call_with(&port, 0x4ac5b0, actor, vertrix_lift_edx, entry->ebx, actor, esi, edi,
                             ebp);
        phase = port_u32(&port, actor, 0x64) + 1;
        port_set32(&port, actor, 0x64, phase == 4 ? 0 : phase);
    }
    phase = port_u32(&port, actor, 0x64);
    eax = ((eax & 0xffff0000u) | port_u16(&port, actor, 0x10)) +
          ((entry->ebx & 0xffff0000u) | port_u16(&port, ebp - 0x34 + phase * 4, 0));
    port_set16(&port, actor, 0xe, eax);
    phase = port_u32(&port, actor, 0x64);
    eax = ((eax & 0xffff0000u) | port_u16(&port, actor, 0x18)) +
          ((esi & 0xffff0000u) | port_u16(&port, ebp - 0x24 + phase * 4, 0));
    port_set16(&port, actor, 0x16, eax);
    return port_return(&port, eax, entry->edx);
}

/* The swing states 0x445090, 0x445130, 0x445630 and 0x4456d0 (guarded, `guard`): on each beat of
 * the actor's timer (0x4ac500, 0x4ac520) it restarts it (0x4ac540, 0x4ac5b0), takes the speed
 * `speed` (+0x4a) and the step 1 (+0x4c) and, once 0x4ad530 gives 0, moves to `next`; then
 * `draw`. */
static uint32_t actor_swing_state(PORT_SIGNATURE, uint32_t guard, uint32_t speed, uint32_t next,
                                  uint32_t draw)
{
    enum
    {
        BELOW = 0x28
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t actor = entry->eax;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    guard_record(&port, ebp - 0x24, guard);
    port_call_with(&port, 0x4ac500, actor, 0x4ec1ec, guard, actor, 0, entry->edi, ebp);
    if (port_call_with(&port, 0x4ac520, actor, vertrix_lift_edx, guard, actor, 0, entry->edi,
                       ebp) == 1)
    {
        uint32_t time = port_call_with(&port, 0x4ac540, actor, vertrix_lift_edx, guard, actor, 0,
                                       entry->edi, ebp);
        port_call_with(&port, 0x4ac5b0, actor, time, guard, actor, 0, entry->edi, ebp);
        port_set16(&port, actor, 0x4a, speed);
        port_set16(&port, actor, 0x4c, 1);
        if (port_call_with(&port, 0x4ad530, actor, vertrix_lift_edx, guard, actor, 0, entry->edi,
                           ebp) == 0)
        {
            port_call_with(&port, 0x4ac8f0, actor, next, guard, actor, 0, entry->edi, ebp);
        }
    }
    port_call_with(&port, draw, actor, vertrix_lift_edx, guard, actor, 0, entry->edi, ebp);
    return port_return(&port, port_u32(&port, ebp, -0x24u), entry->edx);
}

/* Original 0x445090: guard 0x515184, speed 0x28, then 0x445130; draw 0x444e00. */
uint32_t vertrix_port_actor_swing_state_445090(PORT_SIGNATURE)
{
    return actor_swing_state(calls, services, globals, entry, 0x515184, 0x28, 0x445130, 0x444e00);
}

/* Original 0x445130: guard 0x515188, speed 0, then 0x445090; draw 0x444e00. */
uint32_t vertrix_port_actor_swing_state_445130(PORT_SIGNATURE)
{
    return actor_swing_state(calls, services, globals, entry, 0x515188, 0, 0x445090, 0x444e00);
}

/* Original 0x445630: guard 0x5151b4, speed 0x28, then 0x4456d0; draw 0x445350. */
uint32_t vertrix_port_actor_swing_state_445630(PORT_SIGNATURE)
{
    return actor_swing_state(calls, services, globals, entry, 0x5151b4, 0x28, 0x4456d0, 0x445350);
}

/* Original 0x4456d0: guard 0x5151b8, speed 0, then 0x445630; draw 0x445350. */
uint32_t vertrix_port_actor_swing_state_4456d0(PORT_SIGNATURE)
{
    return actor_swing_state(calls, services, globals, entry, 0x5151b8, 0, 0x445630, 0x445350);
}

/* Original 0x445a00: while the sound 0x5bb254 plays (0x47e990), on each beat of the actor's timer
 * it restarts it with the speed 0 and step 5 (0x4ad530), draws (0x445900) and, when 0x47f410
 * gives 1, moves to 0x445a90; otherwise its state is cleared and +0x52 0. */
uint32_t vertrix_port_actor_sound_wait_445a00(PORT_SIGNATURE)
{
    Port port;
    uint32_t actor = entry->eax;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    if (port_forward(&port, entry, 0x47e990, 0x5bb254, entry->edx, actor, actor) == 0)
    {
        result = port_forward(&port, entry, 0x4ac8f0, actor, 0, actor, actor);
        port_set8(&port, actor, 0x52, 0);
        return port_return(&port, result, entry->edx);
    }
    port_forward(&port, entry, 0x4ac500, actor, vertrix_lift_edx, actor, actor);
    if (port_forward(&port, entry, 0x4ac520, actor, vertrix_lift_edx, actor, actor) == 1)
    {
        result = port_forward(&port, entry, 0x4ac540, actor, vertrix_lift_edx, actor, actor);
        port_forward(&port, entry, 0x4ac5b0, actor, result, actor, actor);
        port_set16(&port, actor, 0x4a, 0);
        port_set16(&port, actor, 0x4c, 5);
        port_forward(&port, entry, 0x4ad530, actor, vertrix_lift_edx, actor, actor);
    }
    port_forward(&port, entry, 0x445900, actor, vertrix_lift_edx, actor, actor);
    result = port_forward(&port, entry, 0x47f410, 0x5bb254, vertrix_lift_edx, actor, actor);
    if (result != 1)
    {
        return port_return(&port, result, entry->edx);
    }
    result = port_forward(&port, entry, 0x4ac8f0, actor, 0x445a90, actor, actor);
    return port_return(&port, result, entry->edx);
}

/* Original 0x446500 (guarded, 0x51521c): the text of the count 0x532c24 (0x4b7710 into the
 * frame) set as the actor's object (+0x160) name +0x15c (0x4ca370), then released (0x4ca210).
 * The count is the time 0x532c2c past 0x4f9c10 plus the actor's +0x70, or +0x70 alone. */
uint32_t vertrix_port_actor_count_text_446500(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x30
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t actor = entry->eax;
    uint32_t start;
    uint32_t ebx;
    uint32_t esi = 0;
    uint32_t object;
    uint32_t text;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    start = port_u32(&port, 0, 0x4f9c10);
    guard_record(&port, ebp - 0x2c, 0x51521c);
    ebx = port_u32(&port, 0, 0x532c2c);
    object = port_u32(&port, actor, 0x160);
    if (ebx > start)
    {
        esi = port_u32(&port, actor, 0x70);
        ebx = ebx - start + esi;
    }
    else
    {
        ebx = port_u32(&port, actor, 0x70);
    }
    text = port_call_with(&port, 0x4b7710, 0x532c24, ebp - 0x18, ebx, object, esi, 1, ebp);
    port_set32(&port, ebp, -0x20u, 1);
    port_call_with(&port, 0x4ca370, object + 0x15c, port_u32(&port, text, 0), ebx, object, esi, 1,
                   ebp);
    port_set32(&port, ebp, -0x20u, 0);
    port_call_with(&port, 0x4ca210, ebp - 0x18, 0, ebx, object, esi, 1, ebp);
    port_set32(&port, ebp, -0x20u, 0);
    return port_return(&port, port_u32(&port, ebp, -0x2cu), entry->edx);
}

/* The count states 0x446730 and 0x4467c0: +0x52 10; on each beat of the actor's timer it
 * restarts it with the speed `speed` and step 5 and, once 0x4ad530 gives 0, moves to `next`.
 * Unless the count (0x532bfc plus the edx the timer leaves) is 0x532c00 and below 0x532c18, the
 * actor moves to 0x4465a0. */
static uint32_t actor_count_state(PORT_SIGNATURE, uint32_t speed, uint32_t next)
{
    Port port;
    uint32_t actor = entry->eax;
    uint32_t ebx;
    uint32_t result;
    uint32_t ecx;
    port_open(&port, calls, services, globals, entry);
    ebx = port_u32(&port, 0, 0x532bfc);
    port_set8(&port, actor, 0x52, 0xa);
    port_forward_esi(&port, entry, 0x4ac500, actor, port_u32(&port, actor, 0x70), ebx, actor,
                     actor);
    result = port_forward_esi(&port, entry, 0x4ac520, actor, vertrix_lift_edx, ebx, actor, actor);
    ebx += vertrix_lift_edx;
    if (result == 1)
    {
        result =
            port_forward_esi(&port, entry, 0x4ac540, actor, vertrix_lift_edx, ebx, actor, actor);
        port_forward_esi(&port, entry, 0x4ac5b0, actor, result, ebx, actor, actor);
        port_set16(&port, actor, 0x4a, speed);
        port_set16(&port, actor, 0x4c, 5);
        result =
            port_forward_esi(&port, entry, 0x4ad530, actor, vertrix_lift_edx, ebx, actor, actor);
        if (result == 0)
        {
            result = port_forward_esi(&port, entry, 0x4ac8f0, actor, next, ebx, actor, actor);
        }
    }
    ecx = port_u32(&port, 0, 0x532c00);
    if (ebx == ecx && ecx < port_u32(&port, 0, 0x532c18))
    {
        return port_return(&port, result, entry->edx);
    }
    result = port_forward_esi(&port, entry, 0x4ac8f0, actor, 0x4465a0, ebx, ecx, actor);
    return port_return(&port, result, entry->edx);
}

/* Original 0x446730: speed 0x32, then 0x4467c0. */
uint32_t vertrix_port_actor_count_state_446730(PORT_SIGNATURE)
{
    return actor_count_state(calls, services, globals, entry, 0x32, 0x4467c0);
}

/* Original 0x4467c0: speed 0, then 0x446730. */
uint32_t vertrix_port_actor_count_state_4467c0(PORT_SIGNATURE)
{
    return actor_count_state(calls, services, globals, entry, 0, 0x446730);
}

/* Original 0x446a80: the actor's frame 0x74 (0x4ac510); unless the key 0x54d640 is down
 * (0x476480), its highlight (0x4ac710) is whether it holds the pointer (0x4b0b70 on 0x558944 and
 * 0x558946, 0x7d00 while 0x558958 is set), then 0x4ac8a0 with 0x446850 and 0x4ac8f0. */
uint32_t vertrix_port_actor_pointer_hover_446a80(PORT_SIGNATURE)
{
    Port port;
    uint32_t actor = entry->eax;
    uint32_t result;
    uint32_t esi;
    uint32_t x;
    uint32_t y;
    port_open(&port, calls, services, globals, entry);
    port_forward(&port, entry, 0x4ac510, actor, 0x74, entry->ebx, actor);
    result = port_forward(&port, entry, 0x476480, 0x54d640, vertrix_lift_edx, entry->ebx, actor);
    if (result != 0)
    {
        return port_return(&port, result, entry->edx);
    }
    y = port_u32(&port, 0, 0x558958) == 0 ? port_u16(&port, 0, 0x558946) : 0x7d00;
    esi = port_u32(&port, 0, 0x558958);
    x = esi == 0 ? port_u16(&port, 0, 0x558944) : 0x7d00;
    y = (uint32_t)(int32_t)(int16_t)y;
    x = (uint32_t)(int32_t)(int16_t)x;
    result = port_forward_esi(&port, entry, 0x4b0b70, actor, x, y, actor, esi);
    port_forward_esi(&port, entry, 0x4ac710, actor, (result & 0xff) != 0, y, actor, esi);
    port_forward_esi(&port, entry, 0x4ac8a0, actor, 0x446850, y, actor, esi);
    result = port_forward_esi(&port, entry, 0x4ac8f0, actor, vertrix_lift_edx, y, actor, esi);
    return port_return(&port, result, entry->edx);
}

/* Original 0x447560: after the timer step (0x4ac500, 0x4ac520; at a beat 0x4ac510 on the edx it
 * leaves) the actor's flags set (+0x93 1, +0x4e 100, +0x52 7, +0x94 0, +0x95 3, +0x44 0x10), its
 * state 0x447600, 0x471bf0 on +0x14c and the sounds 0 and 4 of 0x533164 (by 0x4f819c) at the
 * volume 0x532b9c (0x482a60). */
uint32_t vertrix_port_actor_burst_start_447560(PORT_SIGNATURE)
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
    port_set8(&port, actor, 0x52, 7);
    port_set8(&port, actor, 0x94, 0);
    port_set8(&port, actor, 0x95, 3);
    port_set8(&port, actor, 0x44, 0x10);
    port_forward(&port, entry, 0x4ac8f0, actor, 0x447600, entry->ebx, actor);
    port_forward(&port, entry, 0x471bf0, port_u32(&port, actor, 0x14c), vertrix_lift_edx,
                 entry->ebx, actor);
    port_forward(&port, entry, 0x482a60, 0,
                 port_u32(&port, port_u32(&port, 0, 0x4f819c) * 4, 0x533164),
                 port_u32(&port, 0, 0x532b9c), actor);
    result = port_forward(&port, entry, 0x482a60, 4,
                          port_u32(&port, port_u32(&port, 0, 0x4f819c) * 4, 0x533164),
                          port_u32(&port, 0, 0x532b9c), actor);
    return port_return(&port, result, entry->edx);
}
