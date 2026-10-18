#include "rtlpaths.h"

/* Path searches, start-up table runs, list links and window messages. */

static uint32_t call_frame(Port *port, uint32_t target, uint32_t eax, uint32_t edx, uint32_t ebx,
                           uint32_t ecx, uint32_t esi, uint32_t edi, uint32_t ebp,
                           const uint32_t *stack, unsigned count)
{
    return port_call_registers(port, target, eax, edx, ebx, ecx, esi, edi, ebp, stack, count);
}

/* Original 0x4db9fc: the part edx (0x4e7120 into the frame, cut at its lead byte length by
 * 0x4e6f30 with the byte from that call's edx) searched for along the path eax: while 0x4e7b50
 * refuses a position and 0x4e8730 does not match it, the next (0x4e3a90). eax the position found
 * (0 when 0x4e7b50 accepts it and edx is set). */
uint32_t vertrix_port_rtl_path_search_4db9fc(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0xc
    };
    Port port;
    uint8_t stack[BELOW + 8];
    uint32_t esp = entry->esp - 0xc;
    uint32_t ebx = entry->eax;
    uint32_t text = entry->edx;
    uint32_t eax;
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    port_set32(&port, esp, 8, entry->ebx);
    port_set32(&port, esp, 4, entry->ecx);
    port_call_with(&port, 0x4e7120, text, esp, ebx, text, entry->esi, entry->edi, entry->ebp);
    eax = port_call_with(&port, 0x4e6f30, esp, vertrix_lift_edx & 0xffffff00u, ebx, text,
                         entry->esi, entry->edi, entry->ebp);
    port_set8(&port, esp + eax, 0, vertrix_lift_edx);
    for (;;)
    {
        eax = port_call_with(&port, 0x4e7b50, ebx, vertrix_lift_edx, ebx, text, entry->esi,
                             entry->edi, entry->ebp);
        if (eax != 0 || port.env.failed)
        {
            break;
        }
        eax = port_call_with(&port, 0x4e8730, ebx, esp, ebx, text, entry->esi, entry->edi,
                             entry->ebp);
        if (eax == 0)
        {
            break;
        }
        ebx = port_call_with(&port, 0x4e3a90, ebx, vertrix_lift_edx, ebx, text, entry->esi,
                             entry->edi, entry->ebp);
    }
    eax = port_call_with(&port, 0x4e7b50, ebx, vertrix_lift_edx, ebx, text, entry->esi, entry->edi,
                         entry->ebp);
    return port_return(&port, eax == 0 || text == 0 ? ebx : 0, vertrix_lift_edx);
}

/* Original 0x4e6bac: the start-up table 0x51c440..0x51c46a (six-byte entries: done mark 2,
 * priority, routine) run in priority order up to al (0x4e6b50 for those at or above dl), each
 * marked done. */
uint32_t vertrix_port_rtl_table_run_4e6bac(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x10
    };
    Port port;
    uint8_t stack[BELOW + 8];
    uint32_t esp = entry->esp - 0x10;
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ecx = entry->ecx;
    uint32_t ebx;
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    port_set32(&port, esp, 0xc, entry->ebx);
    port_set32(&port, esp, 8, entry->ecx);
    port_set32(&port, esp, 4, entry->esi);
    port_set32(&port, esp, 0, 0);
    ecx = (ecx & 0xffffff00u) | (eax & 0xff);
    edx = (edx & 0xffff00ffu) | ((edx & 0xff) << 8);
    for (;;)
    {
        ebx = 0x51c46a;
        edx = (edx & 0xffffff00u) | (ecx & 0xff);
        for (eax = 0x51c440; eax < 0x51c46a && !port.env.failed; eax += 6)
        {
            if (port_u8(&port, eax, 0) != 2)
            {
                ecx = (ecx & 0xffff00ffu) | ((uint32_t)port_u8(&port, eax, 1) << 8);
                if ((edx & 0xff) <= ((ecx >> 8) & 0xff))
                {
                    ebx = eax;
                    edx = (edx & 0xffffff00u) | ((ecx >> 8) & 0xff);
                }
            }
        }
        if (ebx == 0x51c46a || port.env.failed)
        {
            break;
        }
        if (((edx >> 8) & 0xff) >= port_u8(&port, ebx, 1))
        {
            eax = port_call_with(&port, 0x4e6b50, ebx + 2, edx, ebx, ecx, 0x51c46a, entry->edi,
                                 entry->ebp);
            edx = vertrix_lift_edx;
        }
        port_set8(&port, ebx, 0, 2);
    }
    return port_return(&port, eax, edx);
}

/* Original 0x4e8fa7: the node edx (0x4e0bf8 when none) linked as the list eax's current (+0, the
 * neighbours +8's +4 and +8 taking it and its +8); by the kind at [[+8]+8]: 0 goes to 0x4e8eca,
 * 1, 2 and 4 clear al, 3 and others report (0x4e0bf8) and go to 0x4e8eca. */
uint32_t vertrix_port_rtl_list_link_4e8fa7(PORT_SIGNATURE)
{
    Port port;
    uint32_t list = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t eax = entry->eax;
    uint32_t kind;
    port_open(&port, calls, services, globals, entry);
    if (edx == 0)
    {
        eax = port_call_with(&port, 0x4e0bf8, eax, edx, ebx, list, entry->esi, entry->edi,
                             entry->ebp);
        edx = vertrix_lift_edx;
    }
    eax = port_u32(&port, list, 8);
    port_set32(&port, list, 0, edx);
    port_set32(&port, eax, 4, edx);
    ebx = port_u32(&port, edx, 8);
    port_set32(&port, eax, 8, ebx);
    kind = port_u32(&port, port_u32(&port, port_u32(&port, list, 8), 8), 0);
    if (kind == 1 || kind == 2 || kind == 4)
    {
        return port_return(&port, kind & 0xffffff00u, edx);
    }
    if (kind != 0)
    {
        port_call_with(&port, 0x4e0bf8, kind, edx, ebx, list, entry->esi, entry->edi, entry->ebp);
        edx = vertrix_lift_edx;
    }
    eax = port_call_with(&port, 0x4e8eca, list, edx, ebx, list, entry->esi, entry->edi, entry->ebp);
    return port_return(&port, eax, vertrix_lift_edx);
}

/* Original 0x4cf560 (ret 0xc): unless the first window's style (0x4cccc0) has bit 30, when its
 * owner form (0x4d1900) differs from the third's, that form's handle gets the message 0x36e
 * (0x4f1a94) with the second argument and a frame pair of the two handles. */
uint32_t vertrix_port_rtl_focus_notify_4cf560(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x10
    };
    Port port;
    uint8_t stack[BELOW + 8 + 12];
    uint32_t esp = entry->esp - 0x10;
    uint32_t first;
    uint32_t third;
    uint32_t form;
    uint32_t eax;
    uint32_t args[4];
    port_open_arguments(&port, stack, calls, services, globals, entry, BELOW, 3);
    port_set32(&port, esp, 0xc, entry->ebx);
    port_set32(&port, esp, 8, entry->esi);
    first = port_u32(&port, entry->esp, 4);
    third = port_u32(&port, entry->esp, 0xc);
    eax = port_call_with(&port, 0x4cccc0, first, first, third, entry->ecx, entry->esi, entry->edi,
                         entry->ebp);
    if ((eax & 0x40000000u) != 0)
    {
        return port_return(&port, eax, vertrix_lift_edx);
    }
    form = port_call_with(&port, 0x4d1900, vertrix_lift_edx, vertrix_lift_edx, third, entry->ecx,
                          entry->esi, entry->edi, entry->ebp);
    eax = port_call_with(&port, 0x4d1900, third, vertrix_lift_edx, third, form, form, entry->edi,
                         entry->ebp);
    if (eax == form)
    {
        return port_return(&port, eax, vertrix_lift_edx);
    }
    port_set32(&port, esp, 0, port_u32(&port, vertrix_lift_edx, 0x1c));
    port_set32(&port, esp, 4, third != 0 ? port_u32(&port, third, 0x1c) : 0);
    args[0] = port_u32(&port, form, 0x1c);
    args[1] = 0x36e;
    args[2] = port_u32(&port, entry->esp, 8);
    args[3] = esp;
    eax = call_frame(&port, 0x4f1a94, esp, vertrix_lift_edx, third, form, form, entry->edi,
                     entry->ebp, args, 4);
    return port_return(&port, eax, vertrix_lift_edx);
}

/* Original 0x4cc450 (ret 0xc): a command (first argument) for the application window (0x4ce740's
 * +0x14 clear, not negative) goes to the active form's (0x4cbe80) method +0x74 with the third;
 * otherwise 0x4f18ec of the application's (0x4ce220) handle +0x34 with the three arguments. */
uint32_t vertrix_port_rtl_command_route_4cc450(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 8
    };
    Port port;
    uint8_t stack[BELOW + 8 + 12];
    uint32_t esi;
    uint32_t eax;
    uint32_t args[4];
    port_open_arguments(&port, stack, calls, services, globals, entry, BELOW, 3);
    port_set32(&port, entry->esp - 4, 0, entry->ebx);
    port_set32(&port, entry->esp - 8, 0, entry->esi);
    esi = port_u32(&port, entry->esp, 4);
    eax = port_call_with(&port, 0x4ce740, entry->eax, entry->edx, entry->ebx, entry->ecx, esi,
                         entry->edi, entry->ebp);
    if (port_u8(&port, eax, 0x14) == 0 && (int32_t)esi >= 0)
    {
        uint32_t methods;
        eax = port_call_with(&port, 0x4cbe80, eax, vertrix_lift_edx, entry->ebx, entry->ecx, esi,
                             entry->edi, entry->ebp);
        methods = port_u32(&port, eax, 0);
        eax =
            port_call_with(&port, port_u32(&port, methods, 0x74), eax, esi,
                           port_u32(&port, entry->esp, 0xc), methods, esi, entry->edi, entry->ebp);
        return port_return(&port, eax, vertrix_lift_edx);
    }
    eax = port_call_with(&port, 0x4ce220, eax, vertrix_lift_edx, entry->ebx, entry->ecx, esi,
                         entry->edi, entry->ebp);
    args[0] = port_u32(&port, eax, 0x34);
    args[1] = esi;
    args[2] = port_u32(&port, entry->esp, 8);
    args[3] = port_u32(&port, entry->esp, 0xc);
    eax = call_frame(&port, 0x4f18ec, eax, vertrix_lift_edx, entry->ebx, entry->ecx, esi,
                     entry->edi, entry->ebp, args, 4);
    return port_return(&port, eax, vertrix_lift_edx);
}
