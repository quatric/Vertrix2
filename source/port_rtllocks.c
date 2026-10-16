#include "port_rtllocks.h"

/* Child notifications, window placement, recursive locks and surface locks. */

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

/* Original 0x4b7020: each set child of eax (+4, +8 of them) told 2 by its handler's (+0x24) method
 * +0, then 0x4d8770 of eax with 0. edx kept. */
uint32_t vertrix_port_children_release_4b7020(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x1c
    };
    Port port;
    uint8_t stack[BELOW + 8];
    uint32_t ebp = entry->esp - 4;
    uint32_t self = entry->eax;
    uint32_t count;
    uint32_t index;
    uint32_t ecx = entry->ecx;
    uint32_t esi = entry->esi;
    uint32_t eax;
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -4, entry->ebx);
    port_set32(&port, ebp, -8, entry->ecx);
    port_set32(&port, ebp, -0xc, entry->edx);
    port_set32(&port, ebp, -0x10, entry->esi);
    port_set32(&port, ebp, -0x14, entry->edi);
    count = port_u32(&port, self, 8);
    port_set32(&port, ebp, -0x18, count);
    if (count != 0)
    {
        ecx = 0;
        for (index = 0; index < count && !port.env.failed; index++, ecx += 4)
        {
            uint32_t child = port_u32(&port, port_u32(&port, self, 4), ecx);
            if (child != 0)
            {
                esi = port_u32(&port, child, 0x24);
                port_call_with(&port, port_u32(&port, esi, 0), child, 2, index, ecx, esi, self,
                               ebp);
            }
            count = port_u32(&port, ebp, -0x18);
        }
    }
    eax = port_call_with(&port, 0x4d8770, self, 0, 0xffffffffu, ecx, esi, self, ebp);
    return port_return(&port, eax, entry->edx);
}

/* Original 0x4ccd80 (ret 0xc): the window eax placed: by its control (+0x38) method +0xa0 with the
 * three arguments when it has one, else 0x4f1ad8 of its handle +0x1c after edx's handle (+0x1c, 0
 * without edx) with ebx, ecx and the three arguments. */
uint32_t vertrix_port_rtl_window_place_4ccd80(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 8
    };
    Port port;
    uint8_t stack[BELOW + 8 + 12];
    uint32_t ebp = entry->esp - 8;
    uint32_t self = entry->eax;
    uint32_t control;
    uint32_t edx = entry->edx;
    uint32_t eax;
    uint32_t args[7];
    port_open_arguments(&port, stack, calls, services, globals, entry, BELOW, 3);
    port_set32(&port, entry->esp - 4, 0, entry->esi);
    port_set32(&port, ebp, 0, entry->ebp);
    control = port_u32(&port, self, 0x38);
    if (control == 0)
    {
        if (edx != 0)
        {
            edx = port_u32(&port, edx, 0x1c);
        }
        args[0] = port_u32(&port, self, 0x1c);
        args[1] = edx;
        args[2] = entry->ebx;
        args[3] = entry->ecx;
        args[4] = port_u32(&port, entry->esp, 4);
        args[5] = port_u32(&port, entry->esp, 8);
        args[6] = port_u32(&port, entry->esp, 0xc);
        eax = call_frame(&port, 0x4f1ad8, self, edx, entry->ebx, entry->ecx, entry->esi, entry->edi,
                         ebp, args, 7);
        return port_return(&port, eax, vertrix_lift_edx);
    }
    {
        uint32_t methods = port_u32(&port, control, 0);
        args[0] = port_u32(&port, entry->esp, 4);
        args[1] = port_u32(&port, entry->esp, 8);
        args[2] = port_u32(&port, entry->esp, 0xc);
        eax = call_frame(&port, port_u32(&port, methods, 0xa0), control, edx, entry->ebx,
                         entry->ecx, methods, entry->edi, ebp, args, 3);
    }
    return port_return(&port, eax, vertrix_lift_edx);
}

/* The recursive lock `lock` taken by this thread (0x4f1ba0): a new owner makes its section
 * (0x4e55d4, once, under the lock 0x5c8910: 0x4e57ac and 0x4e5810) and enters it (0x4f1b48),
 * becoming the owner +8; the depth +0xc counts up. The original continues into 0x4e57ac. edx
 * kept. */
static uint32_t lock_enter_at(PORT_SIGNATURE, uint32_t lock)
{
    enum
    {
        BELOW = 0x14
    };
    Port port;
    uint8_t stack[BELOW + 8];
    uint32_t thread;
    uint32_t edx;
    uint32_t eax;
    uint32_t section;
    uint32_t args[1];
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    port_set32(&port, entry->esp - 4, 0, entry->ebx);
    port_set32(&port, entry->esp - 8, 0, entry->ecx);
    port_set32(&port, entry->esp - 0xc, 0, entry->edx);
    port_set32(&port, entry->esp - 0x10, 0, entry->esi);
    port_set32(&port, entry->esp - 0x14, 0, entry->ebp);
    thread = port_call_with(&port, 0x4f1ba0, lock, entry->edx, lock, entry->ecx, entry->esi,
                            entry->edi, entry->ebp);
    eax = thread;
    edx = port_u32(&port, lock, 8);
    if (thread != edx)
    {
        if (port_u32(&port, lock, 4) == 0)
        {
            eax = port_call_with(&port, 0x4e57ac, 0x5c8910, edx, lock, entry->ecx, thread,
                                 entry->edi, entry->ebp);
            edx = vertrix_lift_edx;
            if (port_u32(&port, lock, 4) == 0)
            {
                eax = port_call_with(&port, 0x4e55d4, eax, edx, lock, entry->ecx, thread,
                                     entry->edi, entry->ebp);
                edx = vertrix_lift_edx;
                port_set32(&port, lock, 4, 1);
                port_set32(&port, lock, 0, eax);
            }
            eax = port_call_with(&port, 0x4e5810, 0x5c8910, edx, lock, entry->ecx, thread,
                                 entry->edi, entry->ebp);
            edx = vertrix_lift_edx;
        }
        section = port_u32(&port, lock, 0);
        args[0] = section;
        eax = call_frame(&port, 0x4f1b48, eax, edx, lock, entry->ecx, thread, entry->edi, section,
                         args, 1);
        port_set32(&port, lock, 8, thread);
    }
    port_set32(&port, lock, 0xc, port_u32(&port, lock, 0xc) + 1);
    return port_return(&port, eax, entry->edx);
}

/* Original 0x4e5728: the lock of slot eax (low four bits, 0x10 apart from 0x5c8200) taken. */
uint32_t vertrix_port_rtl_lock_slot_enter_4e5728(PORT_SIGNATURE)
{
    return lock_enter_at(calls, services, globals, entry, ((entry->eax & 0xf) << 4) + 0x5c8200);
}

/* Original 0x4e57a4: the lock 0x5c8930 taken. */
uint32_t vertrix_port_rtl_lock_enter_4e57a4(PORT_SIGNATURE)
{
    return lock_enter_at(calls, services, globals, entry, 0x5c8930);
}

/* Original 0x4e5710: the lock 0x5c81e0 taken. */
uint32_t vertrix_port_rtl_lock_enter_4e5710(PORT_SIGNATURE)
{
    return lock_enter_at(calls, services, globals, entry, 0x5c81e0);
}

/* Original 0x4e576c: the lock 0x5c8300 taken. */
uint32_t vertrix_port_rtl_lock_enter_4e576c(PORT_SIGNATURE)
{
    return lock_enter_at(calls, services, globals, entry, 0x5c8300);
}

/* Original 0x4e5780: the lock 0x5c81f0 taken. */
uint32_t vertrix_port_rtl_lock_enter_4e5780(PORT_SIGNATURE)
{
    return lock_enter_at(calls, services, globals, entry, 0x5c81f0);
}

/* Original 0x47fa40: the surface eax (+0, unless already locked at +0x30) locked through its
 * method +0x1c (whole surface, wait flags 0x80000028) into the frame pair of ecx and edx. eax 1
 * when that answers 0, else 0. */
uint32_t vertrix_port_surface_lock_47fa40(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x10
    };
    Port port;
    uint8_t stack[BELOW + 8];
    uint32_t ebp = entry->esp - 4;
    uint32_t self = entry->eax;
    uint32_t surface;
    uint32_t methods;
    uint32_t eax;
    uint32_t args[8];
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -4, entry->edi);
    surface = port_u32(&port, self, 0);
    if (surface == 0 || port_u32(&port, self, 0x30) != 0)
    {
        return port_return(&port, 0, entry->edx);
    }
    port_set32(&port, ebp, -0xc, entry->ecx);
    port_set32(&port, ebp, -8, entry->edx);
    methods = port_u32(&port, surface, 0);
    args[0] = surface;
    args[1] = entry->ebx;
    args[2] = ebp - 0xc;
    args[3] = 1;
    args[4] = 0;
    args[5] = 0;
    args[6] = 0;
    args[7] = 0x80000028u;
    eax = call_frame(&port, port_u32(&port, methods, 0x1c), surface, methods, entry->ebx, ebp - 0xc,
                     entry->esi, 0, ebp, args, 8);
    return port_return(&port, eax != 0 ? 0 : 1, vertrix_lift_edx);
}
