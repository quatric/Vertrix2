#include "menus.h"

/* The menu buttons' press states, the option toggles, the name entry key states
 * and a level tag. */

static uint32_t call_frame(Port *port, uint32_t target, uint32_t eax, uint32_t edx, uint32_t ebx,
                           uint32_t ecx, uint32_t esi, uint32_t edi, uint32_t ebp,
                           const uint32_t *stack, unsigned count)
{
    return port_call_registers(port, target, eax, edx, ebx, ecx, esi, edi, ebp, stack, count);
}

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

/* Original 0x446850: the menu button eax with the owner +0x10c steps (0x4ac510); the pointer
 * 0x558944 and 0x558946 (0x7d00 each while 0x558958) over it (0x4b0b70) gives the frame 1 (else
 * 0) (0x4ac710); a click of 0x74 (0x476480 on 0x54d640) at its place (0x4764a0, 0x4b0b70) presses
 * it: by its kind +0x70 the owner moves (0 and 2 after a wait of 60 (0x4ac7b0): 0x4b3740 and
 * 0x4b37e0 to 0x4469c0; 1 and 3: 0x4b3880 and 0x4b3940 to 0x446a80) and the button takes the
 * state that leaves, the owner's handler +0x178 is called with the owner's +0x160 +0x15c, and the
 * button has the frame 2. Each way ends in 0x4ac8a0. */
uint32_t vertrix_port_menu_button_press_446850(PORT_SIGNATURE)
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
    uint32_t move;
    uint32_t target;
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
            move = 0;
            target = 0;
            switch (kind)
            {
                case 0:
                    move = 0x4b3740;
                    target = 0x4469c0;
                    break;
                case 1:
                    move = 0x4b3880;
                    target = 0x446a80;
                    break;
                case 2:
                    move = 0x4b37e0;
                    target = 0x4469c0;
                    break;
                case 3:
                    move = 0x4b3940;
                    target = 0x446a80;
                    break;
            }
            if (move != 0)
            {
                if (kind == 0 || kind == 2)
                {
                    port_call_with(&port, 0x4ac7b0, actor, 0x3c, kind, ecx, actor, owner, ebp);
                }
                port_call_with(&port, move, owner, target, kind, ecx, actor, owner, ebp);
                port_call_with(&port, 0x4ac8f0, actor, vertrix_lift_edx, kind, ecx, actor, owner,
                               ebp);
            }
            handler = port_u32(&port, owner, 0x178);
            ebx = handler;
            if (handler != 0)
            {
                port_call_with(&port, handler,
                               port_u32(&port, port_u32(&port, owner, 0x160), 0x15c), owner, ebx,
                               ecx, actor, owner, ebp);
            }
            port_call_with(&port, 0x4ac710, actor, 2, ebx, ecx, actor, owner, ebp);
        }
    }
    eax = port_call_with(&port, 0x4ac8a0, actor, vertrix_lift_edx, ebx, ecx, actor, owner, ebp);
    return port_return(&port, eax, entry->edx);
}

/* Original 0x449180: the toggle actor eax keeps its frame (0x4ac960) and is reset (0x4ac8d0,
 * 0x4ac950 with 0). With 0x532a84 and 0x532a80 both 1 and the choice 0x532a6c set, the choice
 * flips when 0x532b3c or 0x532b38 is 1 and the key 0x3f is down (0x476480, 0x4762e0 on 0x54d640);
 * without a ready check (0x418130) or a choice the actor shows 0x544a18 (0x4ac8d0) at the frame
 * 0x4fbf18. Otherwise the key flips the choice when 0x532b3c or 0x532b38 is 1. The flag 0x5344f0
 * of the choice at 1 shows 0x544a18 at the frame 0x5466c0 (0x4ac710, 0x4ac8a0). A changed frame
 * lights the actor (0x4adfe0). */
uint32_t vertrix_port_option_toggle_449180(PORT_SIGNATURE)
{
    Port port;
    uint32_t actor = entry->eax;
    uint32_t frame;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t eax;
    uint32_t index;
    uint32_t value;
    uint32_t edx;
    int flip = 0;
    int show = 0;
    int ready = 0;
    port_open(&port, calls, services, globals, entry);
    frame =
        port_call_with(&port, 0x4ac960, actor, entry->edx, entry->ebx, actor, esi, edi, entry->ebp);
    port_call_with(&port, 0x4ac8d0, actor, 0, frame, actor, esi, edi, entry->ebp);
    eax = port_call_with(&port, 0x4ac950, actor, 0, frame, actor, esi, edi, entry->ebp);
    edx = port_u32(&port, 0, 0x532a84);
    if (edx == 1 && (esi = port_u32(&port, 0, 0x532a80)) == 1)
    {
        eax = port_call_with(&port, 0x418130, eax, 1, frame, actor, esi, edi, entry->ebp);
        edx = vertrix_lift_edx;
        if (eax != edx || port_u32(&port, 0, 0x532a6c) == 0xffffffffu)
        {
            port_call_with(&port, 0x4ac8d0, actor, 0x544a18, frame, actor, esi, edi, entry->ebp);
            value = port_u32(&port, 0, 0x4fbf18);
            show = 1;
        }
        else
        {
            ready = 1;
            flip = port_u32(&port, 0, 0x532b3c) == esi || port_u32(&port, 0, 0x532b38) == 1;
        }
    }
    else
    {
        flip = port_u32(&port, 0, 0x532b3c) == 1 || port_u32(&port, 0, 0x532b38) == 1;
    }
    if (!show)
    {
        if (flip)
        {
            eax =
                port_call_with(&port, 0x476480, 0x54d640, 0x3f, frame, actor, esi, edi, entry->ebp);
            edx = vertrix_lift_edx;
        }
        if (flip && eax != 0)
        {
            port_call_with(&port, 0x4762e0, 0x54d640, 0x3f, frame, actor, esi, edi, entry->ebp);
            index = port_u32(&port, 0, 0x532a6c);
            value = port_u32(&port, 0, 0x5344f0 + index * 4);
            if (ready)
            {
                edi = value;
            }
            else
            {
                esi = value;
            }
            edx = 1 - value;
            port_set32(&port, 0, 0x5344f0 + index * 4, edx);
        }
        index = port_u32(&port, 0, 0x532a6c);
        if (port_u32(&port, 0, 0x5344f0 + index * 4) == 1)
        {
            port_call_with(&port, 0x4ac8d0, actor, 0x544a18, frame, actor, esi, edi, entry->ebp);
            value = port_u32(&port, 0, 0x5466c0);
            show = 1;
        }
    }
    if (show)
    {
        port_call_with(&port, 0x4ac710, actor, value, frame, actor, esi, edi, entry->ebp);
        port_call_with(&port, 0x4ac8a0, actor, vertrix_lift_edx, frame, actor, esi, edi,
                       entry->ebp);
        edx = vertrix_lift_edx;
    }
    eax = port_call_with(&port, 0x4ac960, actor, edx, frame, actor, esi, edi, entry->ebp);
    if (frame == eax)
    {
        return port_return(&port, eax, entry->edx);
    }
    eax = port_call_with(&port, 0x4adfe0, actor, vertrix_lift_edx, frame, actor, esi, edi,
                         entry->ebp);
    return port_return(&port, eax, entry->edx);
}

/* The key state shared by 0x448970 and 0x448ad0: under a guard record the actor eax moves and bobs
 * when due (0x4ac500, 0x4ac520, 0x4ac540, 0x4ac5b0; +0x4a `height`, +0x4c 3; 0x4ad530), taking
 * the state `next` when the bob ends; a key (0x476530 on 0x54d640) is taken (0x4762e0) and, unless
 * it is 1, its text (0x476160) is added to the owner's text +0x160 +0x15c (0x4ca370), released
 * (0x4ca210) and the handler +0x178 called; then the keys are flushed (0x4766f0 when `flush`),
 * the entry 0x5588f8 leaves for 0x448810 (0x477ed0) and the actor takes that state with +0x48 60
 * and +0x52 9. The guard record's chain. */
static uint32_t key_state(PORT_SIGNATURE, uint32_t guard, uint32_t height, uint32_t next, int flush)
{
    enum
    {
        BELOW = 0x30
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t actor = entry->eax;
    uint32_t key;
    uint32_t ebx = guard;
    uint32_t ecx = actor;
    uint32_t edx;
    uint32_t edi = entry->edi;
    uint32_t eax;
    uint32_t handler;
    uint32_t text;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    guard_record(&port, ebp - 0x2c, guard);
    port_set32(&port, ebp, -0x20u, 0);
    port_call_with(&port, 0x4ac500, actor, 0x4ec1ec, ebx, ecx, 0, edi, ebp);
    if (port_call_with(&port, 0x4ac520, actor, vertrix_lift_edx, ebx, ecx, actor, edi, ebp) == 1)
    {
        eax = port_call_with(&port, 0x4ac540, actor, vertrix_lift_edx, ebx, ecx, actor, edi, ebp);
        port_call_with(&port, 0x4ac5b0, actor, eax, ebx, ecx, actor, edi, ebp);
        port_set16(&port, actor, 0x4a, height);
        port_set16(&port, actor, 0x4c, 3);
        if (port_call_with(&port, 0x4ad530, actor, vertrix_lift_edx, ebx, ecx, actor, edi, ebp) ==
            0)
        {
            port_call_with(&port, 0x4ac8f0, actor, next, ebx, ecx, actor, edi, ebp);
        }
    }
    key = port_call_with(&port, 0x476530, 0x54d640, 0, ebx, ecx, actor, edi, ebp);
    ecx = key;
    if ((key & 0xffff) == 0)
    {
        return port_return(&port, port_u32(&port, ebp, -0x2cu), entry->edx);
    }
    ebx = key & 0xffff;
    port_call_with(&port, 0x4762e0, 0x54d640, ebx, ebx, ecx, actor, edi, ebp);
    edx = vertrix_lift_edx;
    if ((key & 0xffff) != 1)
    {
        edi = 1;
        eax = port_call_with(&port, 0x476160, 0x54d640, ebp - 0x18, ebx, ecx, actor, edi, ebp);
        port_set32(&port, ebp, -0x20u, 1);
        text = port_u32(&port, actor, 0x160) + 0x15c;
        port_call_with(&port, 0x4ca370, text, port_u32(&port, eax, 0), ebx, ecx, actor, edi, ebp);
        port_set32(&port, ebp, -0x20u, 0);
        port_call_with(&port, 0x4ca210, ebp - 0x18, 0, ebx, ecx, actor, edi, ebp);
        port_set32(&port, ebp, -0x20u, 0);
        handler = port_u32(&port, actor, 0x178);
        ecx = handler;
        edx = actor;
        if (handler != 0)
        {
            port_call_with(&port, handler, port_u32(&port, port_u32(&port, actor, 0x160), 0x15c),
                           actor, ebx, ecx, actor, edi, ebp);
            edx = vertrix_lift_edx;
        }
        ebx = 0;
        port_set32(&port, ebp, -0x20u, 0);
    }
    if (flush)
    {
        port_call_with(&port, 0x4766f0, 0x54d640, edx, ebx, ecx, actor, edi, ebp);
    }
    port_call_with(&port, 0x477ed0, 0x5588f8, 0x448810, ebx, ecx, actor, edi, ebp);
    port_set16(&port, actor, 0x48, 0x3c);
    port_set8(&port, actor, 0x52, 9);
    port_call_with(&port, 0x4ac8f0, actor, vertrix_lift_edx, ebx, ecx, actor, edi, ebp);
    return port_return(&port, port_u32(&port, ebp, -0x2cu), entry->edx);
}

/* Original 0x448970: the key state bobbing at 40 to 0x448ad0, flushing the keys. */
uint32_t vertrix_port_entry_key_state_448970(PORT_SIGNATURE)
{
    return key_state(calls, services, globals, entry, 0x515274, 0x28, 0x448ad0, 1);
}

/* Original 0x448ad0: the key state bobbing at 0 to 0x448970. */
uint32_t vertrix_port_entry_key_state_448ad0(PORT_SIGNATURE)
{
    return key_state(calls, services, globals, entry, 0x515280, 0, 0x448970, 0);
}

/* Original 0x448810: the entry button eax under a guard record moves and bobs when due (0x4ac500,
 * 0x4ac520, 0x4ac540, 0x4ac5b0; +0x4a 0, +0x4c 5; 0x4ad530); with no button held (0x558958) the
 * pointer 0x558944 and 0x558946 over it (0x4b0b70) gives +0x48 35, and a click of 0x74 (0x476480
 * on 0x54d640) on it (0x4764a0, 0x4b0b70) is taken (0x476320), opens the entry 0x5588f8 at 100
 * (0x477e30) and gives the state 0x448ad0 with +0x52 10. The guard record's chain. */
uint32_t vertrix_port_entry_button_448810(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x38
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t actor = entry->eax;
    uint32_t edi = entry->edi;
    uint32_t eax;
    uint32_t x;
    uint32_t y;
    uint32_t args[1];
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    guard_record(&port, ebp - 0x34, 0x515270);
    port_set32(&port, ebp, -0x28u, 0);
    port_call_with(&port, 0x4ac500, actor, 0x4ec1ec, 0x515270, actor, 0, edi, ebp);
    if (port_call_with(&port, 0x4ac520, actor, vertrix_lift_edx, 0x515270, actor, actor, edi,
                       ebp) == 1)
    {
        eax = port_call_with(&port, 0x4ac540, actor, vertrix_lift_edx, 0x515270, actor, actor, edi,
                             ebp);
        port_call_with(&port, 0x4ac5b0, actor, eax, 0x515270, actor, actor, edi, ebp);
        port_set16(&port, actor, 0x4a, 0);
        port_set16(&port, actor, 0x4c, 5);
        port_call_with(&port, 0x4ad530, actor, vertrix_lift_edx, 0x515270, actor, actor, edi, ebp);
    }
    if (port_u32(&port, 0, 0x558958) != 0)
    {
        return port_return(&port, port_u32(&port, ebp, -0x34u), entry->edx);
    }
    y = sign16(port_u16(&port, 0, 0x558946));
    x = sign16(port_u16(&port, 0, 0x558944));
    eax = port_call_with(&port, 0x4b0b70, actor, x, y, actor, actor, 0, ebp);
    if ((eax & 0xff) != 0)
    {
        port_set16(&port, actor, 0x48, 0x23);
    }
    if (port_call_with(&port, 0x476480, 0x54d640, 0x74, y, actor, actor, 0, ebp) != 1)
    {
        return port_return(&port, port_u32(&port, ebp, -0x34u), entry->edx);
    }
    args[0] = ebp - 0x18;
    call_frame(&port, 0x4764a0, 0x54d640, 0x74, ebp - 0x20, ebp - 0x1c, actor, 0, ebp, args, 1);
    y = sign16(port_u16(&port, ebp, -0x1cu));
    x = sign16(port_u16(&port, ebp, -0x20u));
    eax = port_call_with(&port, 0x4b0b70, actor, x, y, ebp - 0x1c, actor, 0, ebp);
    if ((eax & 0xff) == 0)
    {
        return port_return(&port, port_u32(&port, ebp, -0x34u), entry->edx);
    }
    port_call_with(&port, 0x476320, 0x54d640, 0x74, 0x32, ebp - 0x1c, actor, 0, ebp);
    port_call_with(&port, 0x477e30, 0x5588f8, 0x64, 0x32, ebp - 0x1c, actor, 0, ebp);
    port_call_with(&port, 0x4ac8f0, actor, 0x448ad0, 0x32, ebp - 0x1c, actor, 0, ebp);
    port_set8(&port, actor, 0x52, 0xa);
    return port_return(&port, port_u32(&port, ebp, -0x34u), entry->edx);
}

/* Original 0x44aec0: the level tag eax under a guard record bobs when due (0x4ac500, 0x4ac520,
 * 0x4ac540, 0x4ac5b0; with +0x48 set +0x4a 0, +0x4c 5, 0x4ad530, 0x4adfe0); its text +0x15c
 * (0x4ca280) is compared (0x4ccfe0) with the level 0x532a68's entry of 0x53453c (0x4ca310), or
 * 0x50e19c when it is -1 (0x4ca370); a change ends the bob (0x4adfe0) and is taken in (0x4ca370),
 * and unless it is 0x50e19d the tag bobs at 80 with +0x7c 1 (0x4ac610). With +0x7c 1 the tag,
 * once its count is done (0x4ac600, 0x4ac620), stops (0x4ac610), plays the level (0x43abd0 with
 * 1), waits 800 (0x4ac860) and clears +0x7c. The temporaries are released (0x4cda10); the guard
 * record's chain. */
uint32_t vertrix_port_level_tag_step_44aec0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x34
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t actor = entry->eax;
    uint32_t ecx = actor;
    uint32_t index;
    uint32_t eax;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    guard_record(&port, ebp - 0x30, 0x51528c);
    port_call_with(&port, 0x4ac500, actor, 0x4ec1ec, 0x51528c, actor, 0, entry->edi, ebp);
    if (port_call_with(&port, 0x4ac520, actor, vertrix_lift_edx, actor, actor, 0, entry->edi,
                       ebp) == 1)
    {
        eax = port_call_with(&port, 0x4ac540, actor, vertrix_lift_edx, actor, actor, 0, entry->edi,
                             ebp);
        port_call_with(&port, 0x4ac5b0, actor, eax, actor, actor, 0, entry->edi, ebp);
        if (port_u16(&port, actor, 0x48) != 0)
        {
            port_set16(&port, actor, 0x4a, 0);
            port_set16(&port, actor, 0x4c, 5);
            port_call_with(&port, 0x4ad530, actor, vertrix_lift_edx, actor, actor, 0, entry->edi,
                           ebp);
            port_call_with(&port, 0x4adfe0, actor, vertrix_lift_edx, actor, actor, 0, entry->edi,
                           ebp);
        }
    }
    port_call_with(&port, 0x4ca280, ebp - 0x1c, port_u32(&port, actor, 0x15c), actor, actor, 0, 1,
                   ebp);
    port_set32(&port, ebp, -0x24u, 1);
    port_call_with(&port, 0x4ca070, ebp - 0x18, vertrix_lift_edx, actor, actor, 0, 1, ebp);
    index = port_u32(&port, 0, 0x532a68);
    port_set32(&port, ebp, -0x24u, 2);
    if (index == 0xffffffffu)
    {
        port_call_with(&port, 0x4ca370, ebp - 0x18, 0x50e19c, actor, actor, 0, 1, ebp);
    }
    else
    {
        port_call_with(&port, 0x4ca310, ebp - 0x18, 0x53453c + index * 4, actor, actor, 0, 1, ebp);
    }
    eax = port_call_with(&port, 0x4ccfe0, port_u32(&port, ebp, -0x1cu),
                         port_u32(&port, ebp, -0x18u), actor, actor, 0, 1, ebp);
    if (eax != 0)
    {
        port_call_with(&port, 0x4adfe0, actor, vertrix_lift_edx, actor, actor, 0, 1, ebp);
        port_call_with(&port, 0x4ca370, actor + 0x15c, port_u32(&port, ebp, -0x18u), actor, actor,
                       0, 1, ebp);
        eax = port_call_with(&port, 0x4ccfe0, port_u32(&port, ebp, -0x18u), 0x50e19d, actor, actor,
                             0, 1, ebp);
        if (eax != 0)
        {
            port_set16(&port, actor, 0x48, 0x50);
            port_set32(&port, actor, 0x7c, 1);
            eax = port_call_with(&port, 0x4ac610, actor, vertrix_lift_edx, actor, actor, 0, 1, ebp);
        }
    }
    ecx = port_u32(&port, actor, 0x7c);
    if (ecx == 1)
    {
        port_call_with(&port, 0x4ac600, actor, vertrix_lift_edx, actor, ecx, 0, 1, ebp);
        eax = port_call_with(&port, 0x4ac620, actor, vertrix_lift_edx, actor, ecx, 0, 1, ebp);
        if (eax == ecx)
        {
            port_call_with(&port, 0x4ac610, actor, vertrix_lift_edx, actor, ecx, 0, 1, ebp);
            port_call_with(&port, 0x43abd0, ecx, port_u32(&port, 0, 0x532a68), actor, ecx, 0, 1,
                           ebp);
            eax = port_call_with(&port, 0x4ac860, actor, 0x320, actor, ecx, 0, 1, ebp);
            port_set32(&port, actor, 0x7c, 0);
        }
    }
    port_call_with(&port, 0x4cda10, eax, vertrix_lift_edx, actor, ecx, 0, 1, ebp);
    return port_return(&port, port_u32(&port, ebp, -0x30u), entry->edx);
}
