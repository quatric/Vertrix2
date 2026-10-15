#include "port_rtlmessages.h"

/* The runtime library's window message routing. */

/* Original 0x4d1e80 (ret 8, guarded 0x519558): the message map 0x4cf880 gives (none, 0) looks up
 * the window of the first stack argument (0x4df140 into a frame dword): a found handler takes
 * the second argument (0x4d1e50). Otherwise the window's parent (0x4f19c8) must be mapped to an
 * object whose site +0x34 maps the window by its +0x20 table; a message record (0x4cf3a0 in the
 * frame, its +0x38 the found entry) then goes to 0x4d1e50 with the second argument and is
 * released (0x4d01a0, +0x1c cleared first). eax is the handler's result, else 0. */
uint32_t vertrix_port_rtl_window_route_4d1e80(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x68
    };
    Port port;
    uint8_t stack[BELOW + 8 + 4 * 2];
    uint32_t esp = entry->esp - 0x68;
    uint32_t window;
    uint32_t argument;
    uint32_t map;
    uint32_t eax;
    uint32_t object;
    uint32_t result;
    uint32_t args[1];
    port_open_arguments(&port, stack, calls, services, globals, entry, BELOW, 2);
    window = port_u32(&port, entry->esp, 4);
    argument = port_u32(&port, entry->esp, 8);
    port_set32(&port, esp, 0x3c, port.env.chain);
    port_set32(&port, esp, 0x40, 0x4ec1ec);
    port_set32(&port, esp, 0x44, 0x519558);
    port_set32(&port, esp, 0x48, 0);
    map = port_call_with(&port, 0x4cf880, 0, entry->edx, entry->ebx, entry->ecx, entry->esi, window,
                         entry->ebp);
    if (map == 0)
    {
        return port_return(&port, 0, vertrix_lift_edx);
    }
    port_set32(&port, esp, 0x50, 0);
    eax = port_call_with(&port, 0x4df140, map, window, esp + 0x50, entry->ecx, map, window,
                         entry->ebp);
    if (port_u32(&port, esp, 0x50) != 0)
    {
        result = port_call_with(&port, 0x4d1e50, port_u32(&port, esp, 0x50), argument, esp + 0x50,
                                entry->ecx, map, window, entry->ebp);
        return port_return(&port, result, vertrix_lift_edx);
    }
    args[0] = window;
    vertrix_lift_in_esi = map;
    vertrix_lift_in_edi = window;
    vertrix_lift_in_ebp = entry->ebp;
    eax = lift_call_arguments(&port.env, 0x4f19c8, eax, vertrix_lift_edx, esp + 0x54, entry->ecx,
                              args, 1);
    vertrix_lift_in_esi = vertrix_lift_in_edi = vertrix_lift_in_ebp = 0;
    eax =
        port_call_with(&port, 0x4df140, map, eax, esp + 0x54, entry->ecx, map, window, entry->ebp);
    if (eax == 0 || port_u32(&port, esp, 0x54) == 0)
    {
        return port_return(&port, 0, vertrix_lift_edx);
    }
    object = port_u32(&port, esp, 0x54);
    if (port_u32(&port, object, 0x34) == 0)
    {
        return port_return(&port, 0, vertrix_lift_edx);
    }
    eax = port_call_with(&port, 0x4df140, port_u32(&port, object, 0x34) + 0x20, window, esp + 0x58,
                         entry->ecx, map, window, entry->ebp);
    if (eax == 0)
    {
        return port_return(&port, 0, vertrix_lift_edx);
    }
    port_call_with(&port, 0x4cf3a0, esp, window, esp + 0x58, entry->ecx, map, window, entry->ebp);
    port_set32(&port, esp, 0x38, port_u32(&port, esp, 0x58));
    port_set32(&port, esp, 0x48, 1);
    result = port_call_with(&port, 0x4d1e50, esp, argument, esp + 0x58, entry->ecx, map, window,
                            entry->ebp);
    port_set32(&port, esp, 0x1c, 0);
    port_set32(&port, esp, 0x48, 0);
    port_call_with(&port, 0x4d01a0, esp, 0, result, entry->ecx, map, window, entry->ebp);
    return port_return(&port, result, vertrix_lift_edx);
}

/* The registers a menu walk carries between its calls. */
typedef struct
{
    uint32_t eax;
    uint32_t edx;
    uint32_t ebx;
    uint32_t ebp;
} MenuRegs;

/* A call of `target` with `count` stack arguments (nearest first) under the walk's registers;
 * eax and edx take the call's. */
static uint32_t menu_call(Port *port, const LiftEntry *entry, MenuRegs *regs, uint32_t target,
                          uint32_t esi, uint32_t edi, uint32_t first, uint32_t second,
                          unsigned count)
{
    uint32_t args[2] = {first, second};
    vertrix_lift_in_esi = esi;
    vertrix_lift_in_edi = edi;
    vertrix_lift_in_ebp = regs->ebp;
    regs->eax = lift_call_arguments(&port->env, target, regs->eax, regs->edx, regs->ebx, entry->ecx,
                                    args, count);
    vertrix_lift_in_esi = vertrix_lift_in_edi = vertrix_lift_in_ebp = 0;
    regs->edx = vertrix_lift_edx;
    return regs->eax;
}

/* Original 0x4d54c0: a popup menu edx of the window eax about to open (after 0x4dc420 on the
 * window's handle +0x1c; not for a system menu, ecx set) has its items updated through a command
 * state in the frame (0x4cba70, the popup at +8). Its parent (+0x20) is the popup when it is the
 * application's menu (0x4ce220's +0x58), else the submenu of the window's frame menu (0x4d1900,
 * 0x4f19b0, 0x4f19a4, 0x4f19dc) that matches it (0x4e1210). Each item (0x4f19a4, 0x4f19a8; its
 * index +4, count +0x1c, id +0) is updated by 0x4cbc90: a submenu (-1) by its first item (its
 * menu +0xc), a command below 0xf000 with +0x3c forcing it; items an update removed are skipped
 * past (the count drops, the index steps back over the same ids). */
uint32_t vertrix_port_rtl_menu_popup_init_4d54c0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x38
    };
    Port port;
    uint32_t esp = entry->esp - 0x38;
    uint32_t self = entry->eax;
    uint32_t popup = entry->edx;
    uint32_t count;
    uint32_t sub;
    MenuRegs regs;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    regs.eax = self;
    regs.edx = entry->edx;
    regs.ebx = entry->ecx;
    regs.ebp = entry->ebp;
    menu_call(&port, entry, &regs, 0x4dc420, popup, self, port_u32(&port, self, 0x1c), 0, 1);
    if (regs.ebx != 0)
    {
        return port_return(&port, regs.eax, regs.edx);
    }
    regs.eax = esp;
    menu_call(&port, entry, &regs, 0x4cba70, popup, self, 0, 0, 0);
    port_set32(&port, esp, 8, popup);
    menu_call(&port, entry, &regs, 0x4ce220, popup, self, 0, 0, 0);
    regs.eax = port_u32(&port, regs.eax, 0x58);
    if (regs.eax == port_u32(&port, popup, 4))
    {
        port_set32(&port, esp, 0x20, popup);
    }
    else if (menu_call(&port, entry, &regs, 0x4f19b0, popup, self, port_u32(&port, self, 0x1c), 0,
                       1) != 0)
    {
        regs.eax = self;
        if (menu_call(&port, entry, &regs, 0x4d1900, popup, self, 0, 0, 0) != 0 &&
            menu_call(&port, entry, &regs, 0x4f19b0, popup, self, port_u32(&port, regs.eax, 0x1c),
                      0, 1) != 0)
        {
            regs.ebp = regs.eax;
            count = menu_call(&port, entry, &regs, 0x4f19a4, popup, self, regs.ebp, 0, 1);
            port_set32(&port, esp, 0x28, count);
            if ((int32_t)count > 0)
            {
                for (;;)
                {
                    menu_call(&port, entry, &regs, 0x4f19dc, popup, self, regs.ebp, regs.ebx, 2);
                    if (regs.eax == port_u32(&port, popup, 4))
                    {
                        menu_call(&port, entry, &regs, 0x4e1210, popup, self, regs.ebp, 0, 1);
                        port_set32(&port, esp, 0x20, regs.eax);
                        break;
                    }
                    regs.ebx++;
                    if ((int32_t)regs.ebx >= (int32_t)port_u32(&port, esp, 0x28) || port.env.failed)
                    {
                        break;
                    }
                }
            }
        }
    }
    menu_call(&port, entry, &regs, 0x4f19a4, popup, self, port_u32(&port, popup, 4), 0, 1);
    port_set32(&port, esp, 4, 0);
    port_set32(&port, esp, 0x1c, regs.eax);
    if (regs.eax == 0)
    {
        return port_return(&port, regs.eax, regs.edx);
    }
    for (;;)
    {
        menu_call(&port, entry, &regs, 0x4f19a8, popup, self, port_u32(&port, popup, 4),
                  port_u32(&port, esp, 4), 2);
        port_set32(&port, esp, 0, regs.eax);
        if (regs.eax == 0)
        {
            goto next;
        }
        if (regs.eax == 0xffffffffu)
        {
            menu_call(&port, entry, &regs, 0x4f19dc, popup, self, port_u32(&port, popup, 4),
                      port_u32(&port, esp, 4), 2);
            sub = menu_call(&port, entry, &regs, 0x4e1210, popup, self, regs.eax, 0, 1);
            port_set32(&port, esp, 0xc, sub);
            if (sub == 0)
            {
                goto next;
            }
            menu_call(&port, entry, &regs, 0x4f19a8, popup, self, port_u32(&port, sub, 4), 0, 2);
            port_set32(&port, esp, 0, regs.eax);
            if (regs.eax == 0 || regs.eax == 0xffffffffu)
            {
                goto next;
            }
            regs.ebx = 0;
        }
        else
        {
            port_set32(&port, esp, 0xc, 0);
            regs.ebx = port_u32(&port, self, 0x3c) != 0 && regs.eax < 0xf000;
        }
        regs.eax = esp;
        regs.edx = self;
        menu_call(&port, entry, &regs, 0x4cbc90, popup, self, 0, 0, 0);
        regs.ebx =
            menu_call(&port, entry, &regs, 0x4f19a4, popup, self, port_u32(&port, popup, 4), 0, 1);
        if (regs.eax < port_u32(&port, esp, 0x1c))
        {
            regs.edx = port_u32(&port, esp, 0x1c) - regs.eax;
            port_set32(&port, esp, 4, port_u32(&port, esp, 4) - regs.edx);
            if (regs.eax > port_u32(&port, esp, 4))
            {
                do
                {
                    menu_call(&port, entry, &regs, 0x4f19a8, popup, self, port_u32(&port, popup, 4),
                              port_u32(&port, esp, 4), 2);
                    if (regs.eax != port_u32(&port, esp, 0))
                    {
                        break;
                    }
                    port_set32(&port, esp, 4, port_u32(&port, esp, 4) + 1);
                } while (regs.ebx > port_u32(&port, esp, 4) && !port.env.failed);
            }
        }
        port_set32(&port, esp, 0x1c, regs.ebx);
    next:
        regs.eax = port_u32(&port, esp, 4) + 1;
        port_set32(&port, esp, 4, regs.eax);
        if (regs.eax >= port_u32(&port, esp, 0x1c) || port.env.failed)
        {
            break;
        }
    }
    return port_return(&port, regs.eax, regs.edx);
}
