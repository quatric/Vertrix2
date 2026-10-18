#include "clicks.h"

/* The actors' pointer and click steps and the caption bob. */

static void guard_record(Port *port, uint32_t record, uint32_t guard)
{
    port_set32(port, record, 0, port->env.chain);
    port_set32(port, record, 4, 0x4ec1ec);
    port_set32(port, record, 8, guard);
    port_set32(port, record, 0xc, 0);
}

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

/* Original 0x445d80: the actor eax's click step: it moves and bobs (+0x4a 0, +0x4c 5; 0x4ad530)
 * when due (0x4ac500, 0x4ac520, 0x4ac540, 0x4ac5b0); the pointer 0x558944 and 0x558946 (0x7d00
 * each while 0x558958) over it (0x4b0b70) sets +0x48 35; a click of 0x74 (0x476480 on 0x54d640)
 * at its place (0x4764a0, 0x4b0b70) is acknowledged (0x476320) and gives +0x52 10 and the state
 * 0x445e90. */
uint32_t vertrix_port_actor_click_step_445d80(PORT_SIGNATURE)
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
    uint32_t pressed;
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
    pressed = port_u32(&port, 0, 0x558958);
    y = sign16(pressed != 0 ? 0x7d00 : port_u16(&port, 0, 0x558946));
    x = sign16(pressed != 0 ? 0x7d00 : port_u16(&port, 0, 0x558944));
    if ((port_call_with(&port, 0x4b0b70, actor, x, y, pressed, actor, entry->edi, ebp) & 0xff) != 0)
    {
        port_set16(&port, actor, 0x48, 0x23);
    }
    eax = port_call_with(&port, 0x476480, 0x54d640, 0x74, y, pressed, actor, entry->edi, ebp);
    if (eax != 1)
    {
        return port_return(&port, eax, entry->edx);
    }
    args[0] = ebp - 0x18;
    call_frame(&port, 0x4764a0, 0x54d640, 0x74, ebp - 0x1c, ebp - 0x14, actor, entry->edi, ebp,
               args, 1);
    x = sign16(port_u32(&port, ebp, -0x1cu));
    y = sign16(port_u32(&port, ebp, -0x14u));
    eax = port_call_with(&port, 0x4b0b70, actor, x, y, ebp - 0x14, actor, entry->edi, ebp);
    if ((eax & 0xff) == 0)
    {
        return port_return(&port, eax, entry->edx);
    }
    port_call_with(&port, 0x476320, 0x54d640, 0x74, y, ebp - 0x14, actor, entry->edi, ebp);
    port_set8(&port, actor, 0x52, 0xa);
    eax = port_call_with(&port, 0x4ac8f0, actor, 0x445e90, y, ebp - 0x14, actor, entry->edi, ebp);
    return port_return(&port, eax, entry->edx);
}

/* The button step shared by 0x446ec0 and 0x447290: the actor eax with the owner +0x10c moves
 * when due (0x4ac500, 0x4ac520, 0x4ac510, through the registers each leaves in edx); a button
 * of kind +0x70 0 or 2 whose owner check (`first` or `second` with 4) passes calls the owner's
 * handler +0x178 with the owner's +0x160 +0x15c; then, unless a click of 0x74 is held (0x476480
 * on 0x54d640), the pointer 0x558944 and 0x558946 (0x7d00 each while 0x558958) over it
 * (0x4b0b70) gives the frame 1 (else 0) (0x4ac710), the owner state `state` (0x4ac8a0) and the
 * speed 1 (0x4ac8f0, 0x4ac7b0). */
static uint32_t button_step(PORT_SIGNATURE, uint32_t first, uint32_t second, uint32_t state)
{
    Port port;
    uint32_t actor = entry->eax;
    uint32_t owner;
    uint32_t esi = entry->esi;
    uint32_t handler;
    uint32_t eax;
    uint32_t x;
    uint32_t y;
    port_open(&port, calls, services, globals, entry);
    owner = port_u32(&port, actor, 0x10c);
    port_call_with(&port, 0x4ac500, actor, actor, owner, actor, esi, entry->edi, entry->ebp);
    eax = vertrix_lift_edx;
    if (port_call_with(&port, 0x4ac520, eax, eax, owner, actor, esi, entry->edi, entry->ebp) == 1)
    {
        eax = vertrix_lift_edx;
        port_call_with(&port, 0x4ac510, eax, eax, owner, actor, esi, entry->edi, entry->ebp);
        esi = port_u32(&port, vertrix_lift_edx, 0x70);
        handler = 0;
        if (esi == 0)
        {
            if (port_call_with(&port, first, owner, 4, owner, actor, esi, entry->edi, entry->ebp) ==
                1)
            {
                esi = port_u32(&port, owner, 0x178);
                handler = esi;
            }
        }
        else if (esi == 2)
        {
            if (port_call_with(&port, second, owner, 4, owner, actor, esi, entry->edi,
                               entry->ebp) == 1)
            {
                handler = port_u32(&port, owner, 0x178);
            }
        }
        if (handler != 0)
        {
            port_call_with(&port, handler, port_u32(&port, port_u32(&port, owner, 0x160), 0x15c),
                           owner, owner, actor, esi, entry->edi, entry->ebp);
        }
    }
    eax =
        port_call_with(&port, 0x476480, 0x54d640, 0x74, owner, actor, esi, entry->edi, entry->ebp);
    if (eax != 0)
    {
        return port_return(&port, eax, entry->edx);
    }
    y = sign16(port_u32(&port, 0, 0x558958) != 0 ? 0x7d00 : port_u16(&port, 0, 0x558946));
    x = sign16(port_u32(&port, 0, 0x558958) != 0 ? 0x7d00 : port_u16(&port, 0, 0x558944));
    eax = port_call_with(&port, 0x4b0b70, actor, x, y, actor, esi, entry->edi, entry->ebp);
    port_call_with(&port, 0x4ac710, actor, (eax & 0xff) != 0 ? 1 : 0, y, actor, esi, entry->edi,
                   entry->ebp);
    port_call_with(&port, 0x4ac8a0, actor, state, y, actor, esi, entry->edi, entry->ebp);
    port_call_with(&port, 0x4ac8f0, actor, vertrix_lift_edx, y, actor, esi, entry->edi, entry->ebp);
    eax = port_call_with(&port, 0x4ac7b0, actor, 1, y, actor, esi, entry->edi, entry->ebp);
    return port_return(&port, eax, entry->edx);
}

/* Original 0x446ec0: the button step with the owner checks 0x4b3ce0 and 0x4b3d60 and the state
 * 0x446c10. */
uint32_t vertrix_port_button_step_446ec0(PORT_SIGNATURE)
{
    return button_step(calls, services, globals, entry, 0x4b3ce0, 0x4b3d60, 0x446c10);
}

/* Original 0x447290: the button step with the owner checks 0x4b5050 and 0x4b50d0 and the state
 * 0x446fe0. */
uint32_t vertrix_port_button_step_447290(PORT_SIGNATURE)
{
    return button_step(calls, services, globals, entry, 0x4b5050, 0x4b50d0, 0x446fe0);
}

/* The caption bob shared by 0x447c60 and 0x447d70: the text `start` (0x4ca280); when due the
 * actor moves and bobs (+0x4a `height`, +0x4c 2; 0x4ad530), taking the state `ended` when the bob
 * ends; the text becomes 0x532c1c at the step +4 1 or 0x532c20 at 2 (0x4ca310), and when it is
 * empty (0x4ccfe0 with `empty`) the actor takes the state 0x447e80. The text is released
 * (0x4ca210); the guard record's chain. */
static uint32_t caption_bob(PORT_SIGNATURE, uint32_t guard, uint32_t start, uint32_t height,
                            uint32_t ended, uint32_t empty)
{
    enum
    {
        BELOW = 0x30
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t actor = entry->eax;
    uint32_t text = ebp - 0x18;
    uint32_t eax;
    uint32_t step;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    guard_record(&port, ebp - 0x2c, guard);
    port_call_with(&port, 0x4ca280, text, start, guard, actor, 0, 1, ebp);
    port_set32(&port, ebp, -0x20u, 1);
    port_call_with(&port, 0x4ac500, actor, vertrix_lift_edx, guard, actor, 0, 1, ebp);
    if (port_call_with(&port, 0x4ac520, actor, vertrix_lift_edx, actor, actor, 0, 1, ebp) == 1)
    {
        eax = port_call_with(&port, 0x4ac540, actor, vertrix_lift_edx, actor, actor, 0, 1, ebp);
        port_call_with(&port, 0x4ac5b0, actor, eax, actor, actor, 0, 1, ebp);
        port_set16(&port, actor, 0x4a, height);
        port_set16(&port, actor, 0x4c, 2);
        if (port_call_with(&port, 0x4ad530, actor, vertrix_lift_edx, actor, actor, 0, 1, ebp) == 0)
        {
            port_call_with(&port, 0x4ac8f0, actor, ended, actor, actor, 0, 1, ebp);
        }
    }
    step = port_u32(&port, actor, 4);
    if (step == 1 || step == 2)
    {
        port_call_with(&port, 0x4ca310, text, step == 1 ? 0x532c1c : 0x532c20, actor, actor, 0, 1,
                       ebp);
    }
    if (port_call_with(&port, 0x4ccfe0, port_u32(&port, ebp, -0x18u), empty, actor, actor, 0, 1,
                       ebp) == 0)
    {
        port_call_with(&port, 0x4ac8f0, actor, 0x447e80, actor, actor, 0, 1, ebp);
    }
    port_set32(&port, ebp, -0x20u, 0);
    port_call_with(&port, 0x4ca210, text, 0, actor, 0, 0, 1, ebp);
    port_set32(&port, ebp, -0x20u, 0);
    return port_return(&port, port_u32(&port, ebp, -0x2cu), entry->edx);
}

/* Original 0x447c60: the caption bob of the text 0x50e170 at height 20, moving to 0x447d70. */
uint32_t vertrix_port_actor_caption_bob_447c60(PORT_SIGNATURE)
{
    return caption_bob(calls, services, globals, entry, 0x515238, 0x50e170, 0x14, 0x447d70,
                       0x50e171);
}

/* Original 0x447d70: the caption bob of the text 0x50e172 at height 0, moving to 0x447c60. */
uint32_t vertrix_port_actor_caption_rest_447d70(PORT_SIGNATURE)
{
    return caption_bob(calls, services, globals, entry, 0x515244, 0x50e172, 0, 0x447c60, 0x50e173);
}

/* Original 0x448010: the actor eax's notice: with the window's notice check 0x48cc30 of 1 on
 * 0x5bb254, the text 0x50e175 when 0x5bb308 is 1 (else 0x50e187) (0x47fe20, 0x4ca280) is shown
 * (0x4b76d0 on 0x532c24) and 0x532a4c becomes 0x4f7b70's value (else 0x4f7b74's); otherwise the
 * window is reset (0x47fe50), 0x532a4c becomes 0x4f7b78's value and an event (slot 0x4f1b30) is
 * waited on for 2000 ms (slot 0x4f1cfc) and closed (slot 0x4f1b2c). The actor stops (0x4ac8f0
 * with 0); the guard record's chain. */
uint32_t vertrix_port_actor_notice_wait_448010(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x34
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t actor = entry->eax;
    uint32_t ebx = 0;
    uint32_t edi = entry->edi;
    uint32_t value;
    uint32_t text;
    uint32_t handle;
    uint32_t eax;
    uint32_t args[4];
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    guard_record(&port, ebp - 0x30, 0x515254);
    if (port_call_with(&port, 0x48cc30, 0x5bb254, 0x4ec1ec, 0, 0x515254, actor, edi, ebp) == 1)
    {
        uint32_t slot;
        edi = port_u32(&port, 0, 0x5bb308);
        slot = edi == 1 ? ebp - 0x1c : ebp - 0x18;
        port_call_with(&port, 0x47fe20, 0x5bb254, edi == 1 ? 0x50e175 : 0x50e187, 0, 0x515254,
                       actor, edi, ebp);
        text =
            port_call_with(&port, 0x4ca280, slot, vertrix_lift_edx, 0, 0x515254, actor, edi, ebp);
        port_set32(&port, ebp, -0x24u, edi == 1 ? edi : 3);
        port_call_with(&port, 0x4b76d0, 0x532c24, text, 0, 0x515254, actor, edi, ebp);
        port_set32(&port, ebp, -0x24u, 0);
        port_call_with(&port, 0x4ca210, slot, 0, 0, 0x515254, actor, edi, ebp);
        value = port_u32(&port, 0, edi == 1 ? 0x4f7b70 : 0x4f7b74);
        port_set32(&port, ebp, -0x24u, 0);
        port_set32(&port, 0, 0x532a4c, value);
    }
    else
    {
        port_call_with(&port, 0x47fe50, 0x5bb254, vertrix_lift_edx, 0, 0x515254, actor, edi, ebp);
        eax = port_u32(&port, 0, 0x4f7b78);
        port_set32(&port, 0, 0x532a4c, eax);
        args[0] = 0;
        args[1] = 1;
        args[2] = 0;
        args[3] = 0;
        handle = call_frame(&port, 0x4f1b30, eax, vertrix_lift_edx, 0, 0x515254, actor, edi, ebp,
                            args, 4);
        args[0] = handle;
        args[1] = 0x7d0;
        eax = call_frame(&port, 0x4f1cfc, handle, vertrix_lift_edx, handle, 0x515254, actor, edi,
                         ebp, args, 2);
        args[0] = handle;
        call_frame(&port, 0x4f1b2c, eax, vertrix_lift_edx, handle, 0x515254, actor, edi, ebp, args,
                   1);
        ebx = handle;
    }
    port_call_with(&port, 0x4ac8f0, actor, 0, ebx, 0x515254, actor, edi, ebp);
    return port_return(&port, port_u32(&port, ebp, -0x30u), entry->edx);
}

/* The hover step shared by 0x4483d0 and 0x4484f0: the actor eax moves and bobs (+0x4a `height`,
 * +0x4c 5; 0x4ad530) when due (0x4ac500, 0x4ac520, 0x4ac540, 0x4ac5b0), taking the state `ended`
 * when the bob ends; the pointer 0x558944 and 0x558946 (0x7d00 each while 0x558958) off it
 * (0x4b4270 of 0) gives the state 0x448260; a click of 0x74 (0x476480 on 0x54d640) on it
 * (0x4764a0, 0x4b4270 of 1) gives the state 0x448610. */
static uint32_t hover_step(PORT_SIGNATURE, uint32_t height, uint32_t ended)
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
    uint32_t pressed;
    uint32_t args[1];
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_call_with(&port, 0x4ac500, actor, entry->edx, entry->ebx, actor, actor, entry->edi, ebp);
    if (port_call_with(&port, 0x4ac520, actor, vertrix_lift_edx, entry->ebx, actor, actor,
                       entry->edi, ebp) == 1)
    {
        eax = port_call_with(&port, 0x4ac540, actor, vertrix_lift_edx, entry->ebx, actor, actor,
                             entry->edi, ebp);
        port_call_with(&port, 0x4ac5b0, actor, eax, entry->ebx, actor, actor, entry->edi, ebp);
        port_set16(&port, actor, 0x4a, height);
        port_set16(&port, actor, 0x4c, 5);
        if (port_call_with(&port, 0x4ad530, actor, vertrix_lift_edx, entry->ebx, actor, actor,
                           entry->edi, ebp) == 0)
        {
            port_call_with(&port, 0x4ac8f0, actor, ended, entry->ebx, actor, actor, entry->edi,
                           ebp);
        }
    }
    pressed = port_u32(&port, 0, 0x558958);
    y = pressed != 0 ? 0x7d00 : port_u16(&port, 0, 0x558946);
    x = pressed != 0 ? 0x7d00 : port_u16(&port, 0, 0x558944);
    if (port_call_with(&port, 0x4b4270, actor, x, y, pressed, actor, entry->edi, ebp) == 0)
    {
        port_call_with(&port, 0x4ac8f0, actor, 0x448260, y, pressed, actor, entry->edi, ebp);
    }
    eax = port_call_with(&port, 0x476480, 0x54d640, 0x74, y, pressed, actor, entry->edi, ebp);
    if (eax != 1)
    {
        return port_return(&port, eax, entry->edx);
    }
    args[0] = ebp - 0x14;
    call_frame(&port, 0x4764a0, 0x54d640, 0x74, ebp - 0x1c, ebp - 0x18, actor, entry->edi, ebp,
               args, 1);
    x = port_u32(&port, ebp, -0x1cu);
    y = port_u32(&port, ebp, -0x18u);
    eax = port_call_with(&port, 0x4b4270, actor, x, y, ebp - 0x18, actor, entry->edi, ebp);
    if (eax != 1)
    {
        return port_return(&port, eax, entry->edx);
    }
    eax = port_call_with(&port, 0x4ac8f0, actor, 0x448610, y, ebp - 0x18, actor, entry->edi, ebp);
    return port_return(&port, eax, entry->edx);
}

/* Original 0x4483d0: the hover step bobbing at height 50, moving to 0x4484f0. */
uint32_t vertrix_port_actor_hover_step_4483d0(PORT_SIGNATURE)
{
    return hover_step(calls, services, globals, entry, 0x32, 0x4484f0);
}

/* Original 0x4484f0: the hover step bobbing at height 0, moving to 0x4483d0. */
uint32_t vertrix_port_actor_hover_rest_4484f0(PORT_SIGNATURE)
{
    return hover_step(calls, services, globals, entry, 0, 0x4483d0);
}
