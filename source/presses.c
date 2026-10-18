#include "presses.h"

/* The buttons' hover and arrival states and the option dials' turns. */

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

/* The hover state shared by 0x446c10 and 0x446fe0: the actor eax with the owner +0x10c steps
 * (0x4ac510); the pointer 0x558944 and 0x558946 (0x7d00 each while 0x558958) over it (0x4b0b70)
 * gives the frame 1 (else 0) (0x4ac710); a click of 0x74 (0x476480 on 0x54d640) at its place
 * (0x4764a0, 0x4b0b70) presses it: a button of kind +0x70 0 or 2 whose owner check (`first` or
 * `second` with 1) passes waits 60 (0x4ac7b0) and calls the owner's handler +0x178 with the
 * owner's +0x160 +0x15c; the pressed button has the frame 2 and the state `arrive` (0x4ac8f0).
 * Each way ends in 0x4ac8a0. */
static uint32_t hover_state(PORT_SIGNATURE, uint32_t first, uint32_t second, uint32_t arrive)
{
    enum
    {
        BELOW = 0x24
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t actor = entry->eax;
    uint32_t owner;
    uint32_t pressed;
    uint32_t kind;
    uint32_t handler;
    uint32_t ebx;
    uint32_t ecx;
    uint32_t eax;
    uint32_t x;
    uint32_t y;
    uint32_t args[1];
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    owner = port_u32(&port, actor, 0x10c);
    port_call_with(&port, 0x4ac510, actor, entry->edx, entry->ebx, entry->ecx, actor, owner, ebp);
    pressed = port_u32(&port, 0, 0x558958);
    y = sign16(pressed != 0 ? 0x7d00 : port_u16(&port, 0, 0x558946));
    x = sign16(pressed != 0 ? 0x7d00 : port_u16(&port, 0, 0x558944));
    eax = port_call_with(&port, 0x4b0b70, actor, x, y, pressed, actor, owner, ebp);
    port_call_with(&port, 0x4ac710, actor, (eax & 0xff) != 0 ? 1 : 0, y, pressed, actor, owner,
                   ebp);
    eax = port_call_with(&port, 0x476480, 0x54d640, 0x74, y, pressed, actor, owner, ebp);
    ebx = y;
    ecx = pressed;
    if (eax == 1)
    {
        args[0] = ebp - 0x18;
        call_frame(&port, 0x4764a0, 0x54d640, 0x74, ebp - 0x20, ebp - 0x1c, actor, owner, ebp, args,
                   1);
        y = sign16(port_u16(&port, ebp, -0x1cu));
        x = sign16(port_u16(&port, ebp, -0x20u));
        ebx = y;
        ecx = ebp - 0x1c;
        eax = port_call_with(&port, 0x4b0b70, actor, x, y, ecx, actor, owner, ebp);
        if ((eax & 0xff) != 0)
        {
            kind = port_u32(&port, actor, 0x70);
            ebx = kind;
            handler = 0;
            if (kind == 0)
            {
                if (port_call_with(&port, first, owner, 1, kind, ecx, actor, owner, ebp) == 1)
                {
                    port_call_with(&port, 0x4ac7b0, actor, 0x3c, kind, ecx, actor, owner, ebp);
                    handler = port_u32(&port, owner, 0x178);
                    ebx = handler;
                }
            }
            else if (kind == 2)
            {
                if (port_call_with(&port, second, owner, 1, kind, ecx, actor, owner, ebp) == 1)
                {
                    port_call_with(&port, 0x4ac7b0, actor, 0x3c, kind, ecx, actor, owner, ebp);
                    handler = port_u32(&port, owner, 0x178);
                    ecx = handler;
                }
            }
            if (handler != 0)
            {
                port_call_with(&port, handler,
                               port_u32(&port, port_u32(&port, owner, 0x160), 0x15c), owner, ebx,
                               ecx, actor, owner, ebp);
            }
            port_call_with(&port, 0x4ac710, actor, 2, ebx, ecx, actor, owner, ebp);
            port_call_with(&port, 0x4ac8f0, actor, arrive, ebx, ecx, actor, owner, ebp);
        }
    }
    eax = port_call_with(&port, 0x4ac8a0, actor, vertrix_lift_edx, ebx, ecx, actor, owner, ebp);
    return port_return(&port, eax, entry->edx);
}

/* Original 0x446c10: the hover state with the owner checks 0x4b3ce0 and 0x4b3d60 and the arrival
 * 0x446d70. */
uint32_t vertrix_port_button_hover_446c10(PORT_SIGNATURE)
{
    return hover_state(calls, services, globals, entry, 0x4b3ce0, 0x4b3d60, 0x446d70);
}

/* Original 0x446fe0: the hover state with the owner checks 0x4b5050 and 0x4b50d0 and the arrival
 * 0x447140. */
uint32_t vertrix_port_button_hover_446fe0(PORT_SIGNATURE)
{
    return hover_state(calls, services, globals, entry, 0x4b5050, 0x4b50d0, 0x447140);
}

/* The arrival state shared by 0x446d70 and 0x447140: when the actor eax is due (0x4ac500,
 * 0x4ac520) it steps 4 (0x4ac510, 0x4ac7b0) and takes the state `step`; unless a click of 0x74 is
 * held (0x476480 on 0x54d640), the pointer 0x558944 and 0x558946 (0x7d00 each while 0x558958)
 * over it (0x4b0b70) gives the frame 1 (else 0) (0x4ac710), the state `hover` (0x4ac8a0) and the
 * speed 1 (0x4ac8f0, 0x4ac7b0). */
static uint32_t arrive_state(PORT_SIGNATURE, uint32_t step, uint32_t hover)
{
    Port port;
    uint32_t actor = entry->eax;
    uint32_t pressed;
    uint32_t eax;
    uint32_t x;
    uint32_t y;
    port_open(&port, calls, services, globals, entry);
    port_call_with(&port, 0x4ac500, actor, entry->edx, entry->ebx, actor, actor, entry->edi,
                   entry->ebp);
    if (port_call_with(&port, 0x4ac520, actor, vertrix_lift_edx, entry->ebx, actor, actor,
                       entry->edi, entry->ebp) == 1)
    {
        port_call_with(&port, 0x4ac510, actor, 4, entry->ebx, actor, actor, entry->edi, entry->ebp);
        port_call_with(&port, 0x4ac7b0, actor, vertrix_lift_edx, entry->ebx, actor, actor,
                       entry->edi, entry->ebp);
        port_call_with(&port, 0x4ac8f0, actor, step, entry->ebx, actor, actor, entry->edi,
                       entry->ebp);
    }
    eax = port_call_with(&port, 0x476480, 0x54d640, 0x74, entry->ebx, actor, actor, entry->edi,
                         entry->ebp);
    if (eax != 0)
    {
        return port_return(&port, eax, entry->edx);
    }
    pressed = port_u32(&port, 0, 0x558958);
    y = sign16(pressed != 0 ? 0x7d00 : port_u16(&port, 0, 0x558946));
    x = sign16(pressed != 0 ? 0x7d00 : port_u16(&port, 0, 0x558944));
    eax = port_call_with(&port, 0x4b0b70, actor, x, y, pressed, actor, entry->edi, entry->ebp);
    port_call_with(&port, 0x4ac710, actor, (eax & 0xff) != 0 ? 1 : 0, y, pressed, actor, entry->edi,
                   entry->ebp);
    port_call_with(&port, 0x4ac8a0, actor, hover, y, pressed, actor, entry->edi, entry->ebp);
    port_call_with(&port, 0x4ac8f0, actor, vertrix_lift_edx, y, pressed, actor, entry->edi,
                   entry->ebp);
    eax = port_call_with(&port, 0x4ac7b0, actor, 1, y, pressed, actor, entry->edi, entry->ebp);
    return port_return(&port, eax, entry->edx);
}

/* Original 0x446d70: the arrival state with the step 0x446ec0 and the hover 0x446c10. */
uint32_t vertrix_port_button_arrive_446d70(PORT_SIGNATURE)
{
    return arrive_state(calls, services, globals, entry, 0x446ec0, 0x446c10);
}

/* Original 0x447140: the arrival state with the step 0x447290 and the hover 0x446fe0. */
uint32_t vertrix_port_button_arrive_447140(PORT_SIGNATURE)
{
    return arrive_state(calls, services, globals, entry, 0x447290, 0x446fe0);
}

enum
{
    DIAL_PICK,
    DIAL_RANDOM
};

/* The dial turn shared by 0x4498e0, 0x449e80 and 0x44a3a0: 1 when 0x449460 restarts the actor
 * eax with the dword `table`; otherwise it moves when due (0x4ac500, 0x4ac520, 0x4ac540, 0x4ac5b0,
 * 0x449360) and counts (0x4ac370): on a count (0x4ac390) the step (0x4ac3b0, 0x4ac380) comes off
 * +0x58 and the choice `store` is made (`pick`, or for DIAL_RANDOM a random below 0x532a88 by
 * 0x4826c0 on 0x598d30), sounding `sound` on 0x5bb254 while `flag` is 1, and at +0x58 0 or less
 * the actor takes the state `expire`. The pointer 0x558944 and 0x558946 (0x7d00 each while
 * 0x558958) over it (0x4b0b70) lights it (0x4adfe0 when `light`) with +0x48 50; a click of 0x74
 * (0x476480 on 0x54d640) at its place (0x4764a0, 0x4b0b70) gives the state `click`; then
 * 0x449390 with the dword `table`. */
static uint32_t dial_turn(PORT_SIGNATURE, uint32_t table, unsigned mode, uint32_t pick,
                          uint32_t flag, uint32_t store, uint32_t sound, int light, uint32_t click,
                          uint32_t expire)
{
    enum
    {
        BELOW = 0x20
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t actor = entry->eax;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t eax;
    uint32_t step;
    uint32_t pressed;
    uint32_t x;
    uint32_t y;
    uint32_t args[1];
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    eax = port_call_with(&port, 0x449460, actor, port_u32(&port, 0, table), ebx, ecx, actor,
                         entry->edi, ebp);
    if (eax == 1)
    {
        return port_return(&port, eax, entry->edx);
    }
    port_call_with(&port, 0x4ac500, actor, vertrix_lift_edx, ebx, ecx, actor, entry->edi, ebp);
    if (port_call_with(&port, 0x4ac520, actor, vertrix_lift_edx, ebx, ecx, actor, entry->edi,
                       ebp) == 1)
    {
        eax = port_call_with(&port, 0x4ac540, actor, vertrix_lift_edx, ebx, ecx, actor, entry->edi,
                             ebp);
        port_call_with(&port, 0x4ac5b0, actor, eax, ebx, ecx, actor, entry->edi, ebp);
        port_call_with(&port, 0x449360, actor, vertrix_lift_edx, ebx, ecx, actor, entry->edi, ebp);
    }
    port_call_with(&port, 0x4ac370, actor, vertrix_lift_edx, ebx, ecx, actor, entry->edi, ebp);
    if (port_call_with(&port, 0x4ac390, actor, vertrix_lift_edx, ebx, ecx, actor, entry->edi,
                       ebp) == 1)
    {
        step = port_call_with(&port, 0x4ac3b0, actor, vertrix_lift_edx, ebx, ecx, actor, entry->edi,
                              ebp);
        eax = port_call_with(&port, 0x4ac380, actor, step, ebx, ecx, actor, entry->edi, ebp);
        if (mode == DIAL_PICK)
        {
            port_set32(&port, actor, 0x58, port_u32(&port, actor, 0x58) - vertrix_lift_edx);
            eax = port_call_with(&port, pick, eax, vertrix_lift_edx, ebx, ecx, actor, entry->edi,
                                 ebp);
        }
        else
        {
            ecx = port_u32(&port, actor, 0x58) - vertrix_lift_edx;
            port_set32(&port, actor, 0x58, ecx);
            eax = port_call_with(&port, 0x4826c0, 0x598d30, port_u16(&port, 0, 0x532a88), ebx, ecx,
                                 actor, entry->edi, ebp) &
                  0xffff;
        }
        ebx = port_u32(&port, 0, flag);
        port_set32(&port, 0, store, eax);
        if (ebx == 1)
        {
            port_call_with(&port, sound, 0x5bb254, vertrix_lift_edx, ebx, ecx, actor, entry->edi,
                           ebp);
        }
        if ((int32_t)port_u32(&port, actor, 0x58) <= 0)
        {
            port_call_with(&port, 0x4ac8f0, actor, expire, ebx, ecx, actor, entry->edi, ebp);
        }
    }
    pressed = port_u32(&port, 0, 0x558958);
    y = sign16(pressed != 0 ? 0x7d00 : port_u16(&port, 0, 0x558946));
    x = sign16(pressed != 0 ? 0x7d00 : port_u16(&port, 0, 0x558944));
    ebx = y;
    eax = port_call_with(&port, 0x4b0b70, actor, x, y, ecx, actor, entry->edi, ebp);
    if ((eax & 0xff) != 0)
    {
        if (light)
        {
            port_call_with(&port, 0x4adfe0, actor, vertrix_lift_edx, ebx, ecx, actor, entry->edi,
                           ebp);
        }
        port_set16(&port, actor, 0x48, 0x32);
    }
    eax = port_call_with(&port, 0x476480, 0x54d640, 0x74, ebx, ecx, actor, entry->edi, ebp);
    if (eax == 1)
    {
        args[0] = ebp - 0x18;
        call_frame(&port, 0x4764a0, 0x54d640, 0x74, ebp - 0x1c, ebp - 0x14, actor, entry->edi, ebp,
                   args, 1);
        ebx = sign16(port_u16(&port, ebp, -0x14u));
        ecx = ebp - 0x14;
        x = sign16(port_u16(&port, ebp, -0x1cu));
        eax = port_call_with(&port, 0x4b0b70, actor, x, ebx, ecx, actor, entry->edi, ebp);
        if ((eax & 0xff) != 0)
        {
            port_call_with(&port, 0x4ac8f0, actor, click, ebx, ecx, actor, entry->edi, ebp);
        }
    }
    eax = port_call_with(&port, 0x449390, actor, port_u32(&port, 0, table), ebx, ecx, actor,
                         entry->edi, ebp);
    return port_return(&port, eax, entry->edx);
}

/* Original 0x4498e0: the dial turn of 0x4fbed8 picking 0x532a68 by 0x417e60 under 0x532a80
 * (0x48c2b0), lit, with the click 0x449a50 and the expiry 0x4497c0. */
uint32_t vertrix_port_dial_turn_4498e0(PORT_SIGNATURE)
{
    return dial_turn(calls, services, globals, entry, 0x4fbed8, DIAL_PICK, 0x417e60, 0x532a80,
                     0x532a68, 0x48c2b0, 1, 0x449a50, 0x4497c0);
}

/* Original 0x449e80: the dial turn of 0x4fbef0 picking 0x532a6c by 0x417ed0 under 0x532a7c
 * (0x48c2b0), with the click 0x449ff0 and the expiry 0x449d60. */
uint32_t vertrix_port_dial_turn_449e80(PORT_SIGNATURE)
{
    return dial_turn(calls, services, globals, entry, 0x4fbef0, DIAL_PICK, 0x417ed0, 0x532a7c,
                     0x532a6c, 0x48c2b0, 0, 0x449ff0, 0x449d60);
}

/* Original 0x44a3a0: the dial turn of 0x4fbf08 drawing 0x532a70 at random under 0x532a80
 * (0x48c2e0), with the click 0x44a520 and the expiry 0x44a2a0. */
uint32_t vertrix_port_dial_turn_44a3a0(PORT_SIGNATURE)
{
    return dial_turn(calls, services, globals, entry, 0x4fbf08, DIAL_RANDOM, 0, 0x532a80, 0x532a70,
                     0x48c2e0, 0, 0x44a520, 0x44a2a0);
}
