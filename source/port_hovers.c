#include "port_hovers.h"

/* The bob and hover states of the menu actors, the switch toggle, the path walk with its sound,
 * the grow and drop states and the centring slides. */

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

/* Original 0x448180: when due the actor steps and bobs to height 0 at speed 5 (0x4ad530); a
 * pointer hit (0x558944, 0x558946; 0x7d00 while 0x558958 is set) sets the height 35; the scroll
 * 0x532bfc is held to at most the count 0x532c18 less 5 (0 for 4 or fewer) and set (0x4b4fa0 with
 * 0, 0x4b4fb0). */
uint32_t vertrix_port_list_scroll_hover_448180(PORT_SIGNATURE)
{
    Port port;
    uint32_t actor = entry->eax;
    uint32_t edi = entry->edi;
    uint32_t ebp = entry->ebp;
    uint32_t amount;
    uint32_t pointer;
    uint32_t x;
    uint32_t y;
    uint32_t ebx;
    uint32_t limit;
    port_open(&port, calls, services, globals, entry);
    port_call_with(&port, 0x4ac500, actor, entry->edx, entry->ebx, actor, actor, edi, ebp);
    if (port_call_with(&port, 0x4ac520, actor, vertrix_lift_edx, entry->ebx, actor, actor, edi,
                       ebp) == 1)
    {
        amount = port_call_with(&port, 0x4ac540, actor, vertrix_lift_edx, entry->ebx, actor, actor,
                                edi, ebp);
        port_call_with(&port, 0x4ac5b0, actor, amount, entry->ebx, actor, actor, edi, ebp);
        port_set16(&port, actor, 0x4a, 0);
        port_set16(&port, actor, 0x4c, 5);
        port_call_with(&port, 0x4ad530, actor, vertrix_lift_edx, entry->ebx, actor, actor, edi,
                       ebp);
    }
    y = port_u32(&port, 0, 0x558958) != 0 ? 0x7d00 : port_u16(&port, 0, 0x558946);
    pointer = port_u32(&port, 0, 0x558958);
    ebx = sign16(y);
    x = pointer != 0 ? 0x7d00 : port_u16(&port, 0, 0x558944);
    if ((port_call_with(&port, 0x4b0b70, actor, sign16(x), ebx, pointer, actor, edi, ebp) & 0xff) !=
        0)
    {
        port_set16(&port, actor, 0x48, 0x23);
    }
    limit = port_u32(&port, 0, 0x532c18);
    limit = limit > 4 ? limit - 5 : 0;
    if (limit < port_u32(&port, 0, 0x532bfc))
    {
        port_set32(&port, 0, 0x532bfc, limit);
    }
    port_call_with(&port, 0x4b4fa0, actor, 0, limit, pointer, actor, edi, ebp);
    return port_return(&port,
                       port_call_with(&port, 0x4b4fb0, actor, port_u32(&port, 0, 0x532bfc), limit,
                                      pointer, actor, edi, ebp),
                       entry->edx);
}

/* The end of the switch states: a change of the actor's frame (0x4ac960) from `before` restarts
 * its image (0x4adfe0). */
static uint32_t frame_changed(Port *port, const LiftEntry *entry, uint32_t actor, uint32_t before,
                              uint32_t edx, uint32_t esi)
{
    uint32_t result = port_forward_esi(port, entry, 0x4ac960, actor, edx, before, actor, esi);
    if (before != result)
    {
        result =
            port_forward_esi(port, entry, 0x4adfe0, actor, vertrix_lift_edx, before, actor, esi);
    }
    return result;
}

/* The bob of the switch states: when due the actor steps, restarts its image (0x4adfe0) and bobs
 * to `height` at speed 2 (0x4ad530); once there it takes the state `next`. */
static void switch_bob(Port *port, const LiftEntry *entry, uint32_t actor, uint32_t before,
                       uint32_t height, uint32_t next)
{
    uint32_t amount;
    port_forward(port, entry, 0x4ac500, actor, vertrix_lift_edx, before, actor);
    if (port_forward(port, entry, 0x4ac520, actor, vertrix_lift_edx, before, actor) != 1)
    {
        return;
    }
    amount = port_forward(port, entry, 0x4ac540, actor, vertrix_lift_edx, before, actor);
    port_forward(port, entry, 0x4ac5b0, actor, amount, before, actor);
    port_forward(port, entry, 0x4adfe0, actor, vertrix_lift_edx, before, actor);
    port_set16(port, actor, 0x4a, height);
    port_set16(port, actor, 0x4c, 2);
    if (port_forward(port, entry, 0x4ad530, actor, vertrix_lift_edx, before, actor) == 0)
    {
        port_forward(port, entry, 0x4ac8f0, actor, next, before, actor);
    }
}

/* The switch on state of 0x448d30 and 0x448e00: bob, then with the switch 0x532a68 set the image
 * 0x544a50 at its frame (0x4ac8d0, 0x4ac710, 0x4ac8a0), otherwise none (0x4ac8d0 and 0x4ac950
 * with 0, 0x4ac700). */
static uint32_t switch_show(PORT_SIGNATURE, uint32_t height, uint32_t next)
{
    Port port;
    uint32_t actor = entry->eax;
    uint32_t before;
    uint32_t value;
    port_open(&port, calls, services, globals, entry);
    before = port_forward(&port, entry, 0x4ac960, actor, entry->edx, entry->ebx, actor);
    switch_bob(&port, entry, actor, before, height, next);
    value = port_u32(&port, 0, 0x532a68);
    if (value == 0xffffffffu)
    {
        port_forward(&port, entry, 0x4ac8d0, actor, 0, before, actor);
        port_forward(&port, entry, 0x4ac950, actor, 0, before, actor);
        port_forward(&port, entry, 0x4ac700, actor, vertrix_lift_edx, before, actor);
    }
    else
    {
        port_forward(&port, entry, 0x4ac8d0, actor, 0x544a50, before, actor);
        port_forward(&port, entry, 0x4ac710, actor, port_u32(&port, 0, 0x532a68), before, actor);
        port_forward(&port, entry, 0x4ac8a0, actor, vertrix_lift_edx, before, actor);
    }
    return port_return(&port,
                       frame_changed(&port, entry, actor, before, vertrix_lift_edx, entry->esi),
                       entry->edx);
}

/* Original 0x448d30: the switch shown at height 0, then 0x448e00. */
uint32_t vertrix_port_switch_show_rest_448d30(PORT_SIGNATURE)
{
    return switch_show(calls, services, globals, entry, 0, 0x448e00);
}

/* Original 0x448e00: the switch shown at height -20, then 0x448d30. */
uint32_t vertrix_port_switch_show_raised_448e00(PORT_SIGNATURE)
{
    return switch_show(calls, services, globals, entry, 0xffec, 0x448d30);
}

/* The second switch state of 0x448ed0 and 0x448fb0: bob, clear the image, and unless the two
 * player game (0x532a84 and 0x532a80 1) has 0x418130 off, the switch 0x532a6c's image when set. */
static uint32_t switch_second(PORT_SIGNATURE, uint32_t height, uint32_t next)
{
    Port port;
    uint32_t actor = entry->eax;
    uint32_t before;
    uint32_t result;
    uint32_t show = 1;
    port_open(&port, calls, services, globals, entry);
    before = port_forward(&port, entry, 0x4ac960, actor, entry->edx, entry->ebx, actor);
    switch_bob(&port, entry, actor, before, height, next);
    port_forward(&port, entry, 0x4ac8d0, actor, 0, before, actor);
    port_forward(&port, entry, 0x4ac950, actor, 0, before, actor);
    result = port_forward(&port, entry, 0x4ac700, actor, vertrix_lift_edx, before, actor);
    if (port_u32(&port, 0, 0x532a84) == 1 && port_u32(&port, 0, 0x532a80) == 1)
    {
        result = port_forward(&port, entry, 0x418130, result, 1, before, actor);
        show = result == vertrix_lift_edx;
    }
    if (show && port_u32(&port, 0, 0x532a6c) != 0xffffffffu)
    {
        port_forward(&port, entry, 0x4ac8d0, actor, 0x544a50, before, actor);
        port_forward(&port, entry, 0x4ac710, actor, port_u32(&port, 0, 0x532a6c), before, actor);
        port_forward(&port, entry, 0x4ac8a0, actor, vertrix_lift_edx, before, actor);
    }
    return port_return(&port,
                       frame_changed(&port, entry, actor, before, vertrix_lift_edx, entry->esi),
                       entry->edx);
}

/* Original 0x448ed0: the second switch at height 0, then 0x448fb0. */
uint32_t vertrix_port_switch_second_rest_448ed0(PORT_SIGNATURE)
{
    return switch_second(calls, services, globals, entry, 0, 0x448fb0);
}

/* Original 0x448fb0: the second switch at height -20, then 0x448ed0. */
uint32_t vertrix_port_switch_second_raised_448fb0(PORT_SIGNATURE)
{
    return switch_second(calls, services, globals, entry, 0xffec, 0x448ed0);
}

/* Original 0x449090: the option switch: the image cleared (0x4ac8d0, 0x4ac950 with 0); with no
 * switch 0x532a68 the image 0x544a18 at the frame 0x4fbf18; otherwise, in the menus 0x532b3c or
 * 0x532b38, the key 0x54d640 0x3e (0x476480, released by 0x4762e0) flips the option
 * 0x5344a4[switch], and an option of 1 shows 0x544a18 at the frame 0x5466c0. */
uint32_t vertrix_port_option_switch_toggle_449090(PORT_SIGNATURE)
{
    Port port;
    uint32_t actor = entry->eax;
    uint32_t before;
    uint32_t esi = entry->esi;
    uint32_t frame;
    port_open(&port, calls, services, globals, entry);
    before = port_forward_esi(&port, entry, 0x4ac960, actor, entry->edx, entry->ebx, actor, esi);
    port_forward_esi(&port, entry, 0x4ac8d0, actor, 0, before, actor, esi);
    port_forward_esi(&port, entry, 0x4ac950, actor, 0, before, actor, esi);
    if (port_u32(&port, 0, 0x532a68) == 0xffffffffu)
    {
        port_forward_esi(&port, entry, 0x4ac8d0, actor, 0x544a18, before, actor, esi);
        frame = port_u32(&port, 0, 0x4fbf18);
    }
    else
    {
        uint32_t index;
        uint32_t edx;
        int flipped = 0;
        if ((port_u32(&port, 0, 0x532b3c) == 1 || port_u32(&port, 0, 0x532b38) == 1) &&
            port_forward_esi(&port, entry, 0x476480, 0x54d640, 0x3e, before, actor, esi) != 0)
        {
            port_forward_esi(&port, entry, 0x4762e0, 0x54d640, 0x3e, before, actor, esi);
            index = port_u32(&port, 0, 0x532a68) * 4;
            esi = port_u32(&port, index, 0x5344a4);
            edx = 1 - esi;
            port_set32(&port, index, 0x5344a4, edx);
            flipped = 1;
        }
        if (!flipped)
        {
            edx = vertrix_lift_edx;
        }
        index = port_u32(&port, 0, 0x532a68) * 4;
        if (port_u32(&port, index, 0x5344a4) != 1)
        {
            return port_return(&port, frame_changed(&port, entry, actor, before, edx, esi),
                               entry->edx);
        }
        port_forward_esi(&port, entry, 0x4ac8d0, actor, 0x544a18, before, actor, esi);
        frame = port_u32(&port, 0, 0x5466c0);
    }
    port_forward_esi(&port, entry, 0x4ac710, actor, frame, before, actor, esi);
    port_forward_esi(&port, entry, 0x4ac8a0, actor, vertrix_lift_edx, before, actor, esi);
    return port_return(&port, frame_changed(&port, entry, actor, before, vertrix_lift_edx, esi),
                       entry->edx);
}

/* Original 0x44abe0: when due the actor steps, bobs to height 0 at speed 5 (0x4ad530), follows its
 * path (0x4b6590, 0x4b65a0, 0x4ac980 with 10, 0x4b6540) and fades (+0x4f 0, +0x50 5, 0x4ad580);
 * once the path ends (0x4b6560 1) it takes the state 0x44ae80, or with 0x532a7c 1 the state
 * 0x44acd0 (+0x44 0, +0x4e 100) and the caption 0x50e197 (0x4ca370 into +0x15c); with 0x532a7c or
 * 0x532a80 1 the sound 0x5bb254 plays (0x48c310). */
uint32_t vertrix_port_actor_path_walk_44abe0(PORT_SIGNATURE)
{
    static const uint32_t ten[1] = {0xa};
    Port port;
    uint32_t actor = entry->eax;
    uint32_t ebx = entry->ebx;
    uint32_t ebp = entry->ebp;
    uint32_t amount;
    uint32_t result;
    uint32_t ecx;
    port_open(&port, calls, services, globals, entry);
    port_call_with(&port, 0x4ac500, actor, entry->edx, ebx, entry->ecx, actor, entry->edi, ebp);
    result = port_call_with(&port, 0x4ac520, actor, vertrix_lift_edx, ebx, entry->ecx, actor,
                            entry->edi, ebp);
    if (result != 1)
    {
        return port_return(&port, result, entry->edx);
    }
    amount = port_call_with(&port, 0x4ac540, actor, vertrix_lift_edx, ebx, entry->ecx, actor,
                            entry->edi, ebp);
    port_call_with(&port, 0x4ac5b0, actor, vertrix_lift_edx, ebx, entry->ecx, actor, amount, ebp);
    port_set16(&port, actor, 0x4a, 0);
    port_set16(&port, actor, 0x4c, 5);
    port_call_with(&port, 0x4ad530, actor, amount, ebx, entry->ecx, actor, amount, ebp);
    port_set8(&port, actor, 0x4f, 0);
    port_set16(&port, actor, 0x50, 5);
    result = port_call_with(&port, 0x4b6590, actor, vertrix_lift_edx, ebx, entry->ecx, actor,
                            amount, ebp);
    ecx = sign16(result);
    result = call_frame(&port, 0x4b65a0, actor, amount, ebx, ecx, actor, amount, ebp, ten, 1);
    ebx = sign16(result);
    result =
        call_frame(&port, 0x4ac980, actor, vertrix_lift_edx, ebx, ecx, actor, amount, ebp, ten, 1);
    port_call_with(&port, 0x4b6540, actor, sign16(result), ebx, ecx, actor, amount, ebp);
    result = port_call_with(&port, 0x4ad580, actor, amount, ebx, ecx, actor, amount, ebp);
    if (result != 0)
    {
        return port_return(&port, result, entry->edx);
    }
    result = port_call_with(&port, 0x4b6560, actor, vertrix_lift_edx, ebx, ecx, actor, amount, ebp);
    if (result != 1)
    {
        return port_return(&port, result, entry->edx);
    }
    if (port_u32(&port, 0, 0x532a7c) == 1)
    {
        port_set8(&port, actor, 0x44, 0);
        port_set8(&port, actor, 0x4e, 0x64);
        port_call_with(&port, 0x4ac8f0, actor, 0x44acd0, ebx, ecx, actor, amount, ebp);
        result =
            port_call_with(&port, 0x4ca370, actor + 0x15c, 0x50e197, ebx, ecx, actor, amount, ebp);
    }
    else
    {
        result = port_call_with(&port, 0x4ac8f0, actor, 0x44ae80, ebx, ecx, actor, amount, ebp);
    }
    if (port_u32(&port, 0, 0x532a7c) == 1 || port_u32(&port, 0, 0x532a80) == 1)
    {
        result = port_call_with(&port, 0x48c310, 0x5bb254, vertrix_lift_edx, ebx, ecx, actor,
                                amount, ebp);
    }
    return port_return(&port, result, entry->edx);
}

/* Original 0x44dbb0: the drop state (+0x95 4, 0x4ac1f0): when due the actor steps, grows (+0x45
 * 16, +0x46 1, 0x4acc10) and bobs to 50 at speed 5 (0x4ad530); its look +0x52 is 1 from height
 * 15, 2 from 30 and 3 at 50; it fades (+0x4f 0, +0x50 4, 0x4ad580) and when done takes the state
 * 0x44dc80. 0x4ac8a0 last. */
uint32_t vertrix_port_actor_drop_grow_44dbb0(PORT_SIGNATURE)
{
    Port port;
    uint32_t actor = entry->eax;
    uint32_t amount;
    uint32_t height;
    port_open(&port, calls, services, globals, entry);
    port_set8(&port, actor, 0x95, 4);
    port_forward(&port, entry, 0x4ac1f0, actor, entry->edx, entry->ebx, actor);
    port_forward(&port, entry, 0x4ac500, actor, vertrix_lift_edx, entry->ebx, actor);
    if (port_forward(&port, entry, 0x4ac520, actor, vertrix_lift_edx, entry->ebx, actor) != 1)
    {
        return port_return(
            &port, port_forward(&port, entry, 0x4ac8a0, actor, vertrix_lift_edx, entry->ebx, actor),
            entry->edx);
    }
    amount = port_forward(&port, entry, 0x4ac540, actor, vertrix_lift_edx, entry->ebx, actor);
    port_forward_esi(&port, entry, 0x4ac5b0, actor, vertrix_lift_edx, amount, actor, amount);
    port_set8(&port, actor, 0x45, 0x10);
    port_set16(&port, actor, 0x46, 1);
    port_forward_esi(&port, entry, 0x4acc10, actor, amount, amount, actor, amount);
    port_set16(&port, actor, 0x4a, 0x32);
    port_set16(&port, actor, 0x4c, 5);
    port_forward_esi(&port, entry, 0x4ad530, actor, amount, amount, actor, amount);
    height = sign16(port_u16(&port, actor, 0x48));
    if ((int32_t)height >= 0xf)
    {
        port_set8(&port, actor, 0x52, 1);
    }
    if ((int32_t)sign16(port_u16(&port, actor, 0x48)) >= 0x1e)
    {
        port_set8(&port, actor, 0x52, 2);
    }
    if (port_u16(&port, actor, 0x48) == 0x32)
    {
        port_set8(&port, actor, 0x52, 3);
    }
    port_set8(&port, actor, 0x4f, 0);
    port_set16(&port, actor, 0x50, 4);
    if (port_forward_esi(&port, entry, 0x4ad580, actor, amount, amount, actor, amount) == 0)
    {
        port_forward_esi(&port, entry, 0x4ac8f0, actor, 0x44dc80, amount, actor, amount);
    }
    return port_return(
        &port,
        port_forward_esi(&port, entry, 0x4ac8a0, actor, vertrix_lift_edx, amount, actor, amount),
        entry->edx);
}

/* The centring of the slide states: the actor's size (0x4b14c0) centres it in its 24 by 24 cell
 * from its start (+8, +0xa). The last edx. */
static uint32_t slide_centre(Port *port, uint32_t actor, uint32_t ebp, uint32_t esi, uint32_t edi,
                             uint32_t *ebx)
{
    uint32_t edx;
    port_set32(port, ebp, -0x1cu, 0);
    port_set32(port, ebp, -0x18u, 0);
    port_call_with(port, 0x4b14c0, actor, ebp - 0x1c, ebp - 0x18, actor, esi, edi, ebp);
    port_set16(port, actor, 0xe,
               sign16(port_u16(port, actor, 8)) + ((0x18 - port_u32(port, ebp, -0x1cu)) >> 1));
    edx = sign16(port_u16(port, actor, 0xa));
    port_set16(port, actor, 0x16, edx + ((0x18 - port_u32(port, ebp, -0x18u)) >> 1));
    *ebx = ebp - 0x18;
    return edx;
}

/* The grow slide of 0x44e920 and 0x44eaf0: after 0x4ac1f0, when due the actor steps and grows
 * (0x4acc10), taking `next` once grown (with `shown` also shown at +0x4e 50, +0x95 1); centred,
 * it sinks by four times 16 less its colour +0x44. 0x4ac8a0 last. */
static uint32_t grow_slide(PORT_SIGNATURE, uint32_t next, int shown)
{
    enum
    {
        BELOW = 0x20
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t actor = entry->eax;
    uint32_t amount;
    uint32_t ebx;
    uint32_t edx;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_call_with(&port, 0x4ac1f0, actor, entry->edx, entry->ebx, actor, entry->esi, entry->edi,
                   ebp);
    port_call_with(&port, 0x4ac500, actor, vertrix_lift_edx, entry->ebx, actor, entry->esi,
                   entry->edi, ebp);
    if (port_call_with(&port, 0x4ac520, actor, vertrix_lift_edx, entry->ebx, actor, entry->esi,
                       entry->edi, ebp) != 1)
    {
        return port_return(&port,
                           port_call_with(&port, 0x4ac8a0, actor, vertrix_lift_edx, entry->ebx,
                                          actor, entry->esi, entry->edi, ebp),
                           entry->edx);
    }
    amount = port_call_with(&port, 0x4ac540, actor, vertrix_lift_edx, entry->ebx, actor, entry->esi,
                            entry->edi, ebp);
    port_call_with(&port, 0x4ac5b0, actor, amount, entry->ebx, actor, entry->esi, entry->edi, ebp);
    if (port_call_with(&port, 0x4acc10, actor, vertrix_lift_edx, entry->ebx, actor, entry->esi,
                       entry->edi, ebp) == 0)
    {
        port_call_with(&port, 0x4ac8f0, actor, next, entry->ebx, actor, entry->esi, entry->edi,
                       ebp);
        if (shown)
        {
            port_set8(&port, actor, 0x93, 0);
            port_set8(&port, actor, 0x4e, 0x32);
            port_set8(&port, actor, 0x95, 1);
        }
    }
    slide_centre(&port, actor, ebp, entry->esi, entry->edi, &ebx);
    edx = (0x10 - port_u8(&port, actor, 0x44)) * 4;
    port_set16(&port, actor, 0x48, edx);
    port_set16(&port, actor, 0x48, -edx);
    return port_return(&port,
                       port_call_with(&port, 0x4ac8a0, actor, -edx, ebx, actor,
                                      port_u32(&port, ebp, -0x1cu), port_u32(&port, ebp, -0x18u),
                                      ebp),
                       entry->edx);
}

/* Original 0x44e920: the grow slide into the state 0x44e9f0. */
uint32_t vertrix_port_actor_grow_slide_44e920(PORT_SIGNATURE)
{
    return grow_slide(calls, services, globals, entry, 0x44e9f0, 0);
}

/* Original 0x44e9f0: after 0x4ac1f0, when due the actor steps and moves from its start (+8,
 * +0xa; 0x4aca60, 0x4acab0), the new place becoming the start; centred, once both moves are done
 * it takes the state 0x44c860 and grows (+0x45 16, +0x46 1). 0x4ac8a0 last. */
uint32_t vertrix_port_actor_move_slide_44e9f0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x20
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t actor = entry->eax;
    uint32_t amount;
    uint32_t across;
    uint32_t down;
    uint32_t ebx;
    uint32_t edx;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_call_with(&port, 0x4ac1f0, actor, entry->edx, entry->ebx, actor, entry->esi, entry->edi,
                   ebp);
    port_call_with(&port, 0x4ac500, actor, vertrix_lift_edx, entry->ebx, actor, entry->esi,
                   entry->edi, ebp);
    if (port_call_with(&port, 0x4ac520, actor, vertrix_lift_edx, entry->ebx, actor, entry->esi,
                       entry->edi, ebp) != 1)
    {
        return port_return(&port,
                           port_call_with(&port, 0x4ac8a0, actor, vertrix_lift_edx, entry->ebx,
                                          actor, entry->esi, entry->edi, ebp),
                           entry->edx);
    }
    amount = port_call_with(&port, 0x4ac540, actor, vertrix_lift_edx, entry->ebx, actor, entry->esi,
                            entry->edi, ebp);
    port_call_with(&port, 0x4ac5b0, actor, vertrix_lift_edx, amount, actor, entry->esi, entry->edi,
                   ebp);
    port_set16(&port, actor, 0xe, port_u16(&port, actor, 8));
    port_set16(&port, actor, 0x16, port_u16(&port, actor, 0xa));
    across =
        port_call_with(&port, 0x4aca60, actor, amount, amount, actor, entry->esi, entry->edi, ebp);
    down = port_call_with(&port, 0x4acab0, actor, amount, amount, actor, entry->esi, across, ebp);
    port_set16(&port, actor, 8, port_u16(&port, actor, 0xe));
    port_set16(&port, actor, 0xa, port_u16(&port, actor, 0x16));
    port_set32(&port, ebp, -0x1cu, 0);
    port_set32(&port, ebp, -0x18u, 0);
    port_call_with(&port, 0x4b14c0, actor, ebp - 0x1c, ebp - 0x18, actor, down, across, ebp);
    port_set16(&port, actor, 0xe,
               sign16(port_u16(&port, actor, 8)) + ((0x18 - port_u32(&port, ebp, -0x1cu)) >> 1));
    edx = sign16(port_u16(&port, actor, 0xa));
    port_set16(&port, actor, 0x16, edx + ((0x18 - port_u32(&port, ebp, -0x18u)) >> 1));
    ebx = port_u32(&port, ebp, -0x18u);
    if (across != 0 || down != 0)
    {
        return port_return(
            &port, port_call_with(&port, 0x4ac8a0, actor, edx, ebx, actor, down, across, ebp),
            entry->edx);
    }
    port_call_with(&port, 0x4ac8f0, actor, 0x44c860, ebx, actor, down, across, ebp);
    port_set8(&port, actor, 0x45, 0x10);
    port_set16(&port, actor, 0x46, 1);
    return port_return(
        &port,
        port_call_with(&port, 0x4ac8a0, actor, vertrix_lift_edx, ebx, actor, down, across, ebp),
        entry->edx);
}

/* Original 0x44eaf0: the grow slide into the state 0x44c860, shown. */
uint32_t vertrix_port_actor_grow_slide_shown_44eaf0(PORT_SIGNATURE)
{
    return grow_slide(calls, services, globals, entry, 0x44c860, 1);
}
