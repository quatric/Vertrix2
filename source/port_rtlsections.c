#include "port_rtlsections.h"

/* The runtime library's locks, module references and digit pairs. */

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

/* The lock `lock` left once (its count +0xc down); reaching 0 clears its owner +8 and releases its
 * section +0 (0x4f1c40); edx kept. */
static uint32_t lock_leave(PORT_SIGNATURE, uint32_t lock)
{
    Port port;
    uint32_t count;
    uint32_t eax = lock;
    uint32_t args[1];
    port_open(&port, calls, services, globals, entry);
    count = port_u32(&port, lock, 0xc);
    if (count != 0)
    {
        port_set32(&port, lock, 0xc, count - 1);
        if (count - 1 == 0)
        {
            args[0] = port_u32(&port, lock, 0);
            port_set32(&port, lock, 8, 0);
            eax = call_frame(&port, 0x4f1c40, lock, count, 0, entry->ecx, args[0], entry->edi,
                             entry->ebp, args, 1);
        }
    }
    return port_return(&port, eax, entry->edx);
}

/* Original 0x4e571c: lock_leave of 0x5c81e0. */
uint32_t vertrix_port_rtl_lock_leave_4e571c(PORT_SIGNATURE)
{
    return lock_leave(calls, services, globals, entry, 0x5c81e0);
}

/* Original 0x4e5774: lock_leave of 0x5c8300. */
uint32_t vertrix_port_rtl_lock_leave_4e5774(PORT_SIGNATURE)
{
    return lock_leave(calls, services, globals, entry, 0x5c8300);
}

/* Original 0x4e5788: lock_leave of 0x5c81f0. */
uint32_t vertrix_port_rtl_lock_leave_4e5788(PORT_SIGNATURE)
{
    return lock_leave(calls, services, globals, entry, 0x5c81f0);
}

/* Original 0x4e5738: lock_leave of the class eax's lock (low four bits, 0x10 apart from
 * 0x5c8200). */
uint32_t vertrix_port_rtl_lock_leave_4e5738(PORT_SIGNATURE)
{
    return lock_leave(calls, services, globals, entry, ((entry->eax & 0xf) << 4) + 0x5c8200);
}

/* Original 0x4dc4b0 (ret 4): the module (stack argument) released: its reference count (0x4f1c14,
 * low byte) less one more times by 0x4f1c2c, then 0x4f1c18. */
uint32_t vertrix_port_rtl_module_release_4dc4b0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 8
    };
    Port port;
    uint8_t stack[BELOW + 8 + 4];
    uint32_t module;
    uint32_t count;
    uint32_t eax;
    uint32_t args[1];
    port_open_arguments(&port, stack, calls, services, globals, entry, BELOW, 1);
    module = port_u32(&port, entry->esp, 4);
    if (module == 0)
    {
        return port_return(&port, entry->eax, entry->edx);
    }
    args[0] = module;
    eax = call_frame(&port, 0x4f1c14, entry->eax, entry->edx, entry->ebx, entry->ecx, module,
                     entry->edi, entry->ebp, args, 1);
    count = eax & 0xff;
    for (count--; count != 0xffffffffu && !port.env.failed; count--)
    {
        eax = call_frame(&port, 0x4f1c2c, eax, vertrix_lift_edx, count, entry->ecx, module,
                         entry->edi, entry->ebp, args, 1);
    }
    eax = call_frame(&port, 0x4f1c18, eax, vertrix_lift_edx, count, entry->ecx, module, entry->edi,
                     entry->ebp, args, 1);
    return port_return(&port, eax, vertrix_lift_edx);
}

/* Original 0x4ecf49: the value eax (below 10000) as four decimal digits at ebx: the hundreds by
 * 0x4ecf60, then the rest as two digits (`div cx` and `div cl` unchanged when they would fault).
 * eax as left, edx 0x4ecf60's. */
uint32_t vertrix_port_rtl_four_digits_4ecf49(PORT_SIGNATURE)
{
    Port port;
    uint32_t eax = entry->eax;
    uint32_t edx = 0;
    uint32_t low;
    LiftFlags flags = {0, 0, 0, 0, 0, 0};
    port_open(&port, calls, services, globals, entry);
    if (eax < 0x64)
    {
        edx = eax;
        eax = 0;
    }
    else
    {
        lift_div1(16, 0x64, &eax, &edx, &flags);
    }
    low = edx;
    port_call_with(&port, 0x4ecf60, eax, edx, entry->ebx, 0x64, entry->esi, entry->edi, entry->ebp);
    edx = vertrix_lift_edx;
    eax = low;
    if ((eax & 0xff) < 0xa)
    {
        eax = (eax & 0xffff0000u) | ((eax & 0xff) << 8) | ((eax >> 8) & 0xff);
    }
    else
    {
        lift_div1(8, 0xa, &eax, &edx, &flags);
    }
    eax = (eax & 0xffff00ffu) | ((((eax >> 8) + 0x30) & 0xff) << 8);
    eax = (eax & 0xffffff00u) | ((eax + 0x30) & 0xff);
    port_set8(&port, entry->ebx, 0, eax);
    port_set8(&port, entry->ebx, 1, eax >> 8);
    return port_return(&port, eax, edx);
}

/* Original 0x4cf800: the application 0x4ce220's instance (0x4f19c0) kept in +0x48 and the dialog
 * base units (0x4f19bc, two sign-extended words) in +0x4c and +0x50; eax its +0x38, edx the units.
 */
uint32_t vertrix_port_rtl_dialog_units_4cf800(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x14
    };
    Port port;
    uint8_t stack[BELOW + 8];
    uint32_t esp = entry->esp - 0x14;
    uint32_t application;
    uint32_t instance;
    uint32_t units;
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    port_set32(&port, esp, 0x10, entry->ebx);
    port_set32(&port, esp, 0xc, entry->esi);
    port_set32(&port, esp, 8, entry->edi);
    application = port_call_with(&port, 0x4ce220, entry->eax, entry->edx, entry->ebx, entry->ecx,
                                 entry->esi, entry->edi, entry->ebp);
    instance = port_call_with(&port, 0x4f19c0, application, vertrix_lift_edx, application,
                              entry->ecx, entry->esi, entry->edi, entry->ebp);
    port_set32(&port, application, 0x48, instance);
    units = port_call_with(&port, 0x4f19bc, instance, vertrix_lift_edx, application, entry->ecx,
                           entry->esi, entry->edi, entry->ebp);
    port_set32(&port, esp, 0, (uint32_t)(int32_t)(int16_t)units);
    port_set32(&port, esp, 4, (uint32_t)(int32_t)(int16_t)(units >> 16));
    port_set32(&port, application, 0x4c, port_u32(&port, esp, 0));
    port_set32(&port, application, 0x50, port_u32(&port, esp, 4));
    return port_return(&port, application + 0x38, units);
}

/* Original 0x4e81d0: the texts eax and edx copied into the two frame dwords (0x4e8790), each cut at
 * its lead byte length (0x4e6f30, the byte from that call's edx), folded (0x4ea0d0) and compared
 * by 0x4e8730. */
uint32_t vertrix_port_rtl_text_compare_4e81d0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x10
    };
    Port port;
    uint8_t stack[BELOW + 8];
    uint32_t esp = entry->esp - 0x10;
    uint32_t first = entry->eax;
    uint32_t second = entry->edx;
    uint32_t eax;
    uint32_t args[2];
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    port_set32(&port, esp, 0xc, entry->ebx);
    port_set32(&port, esp, 8, entry->ecx);
    port_call_with(&port, 0x4e8790, esp, first, first, second, entry->esi, entry->edi, entry->ebp);
    eax = port_call_with(&port, 0x4e6f30, first, vertrix_lift_edx & 0xffffff00u, first, second,
                         entry->esi, entry->edi, entry->ebp);
    port_set8(&port, esp + eax, 0, vertrix_lift_edx);
    port_call_with(&port, 0x4e8790, esp + 4, second, first, second, entry->esi, entry->edi,
                   entry->ebp);
    eax = port_call_with(&port, 0x4e6f30, second, vertrix_lift_edx & 0xffff00ffu, first, second,
                         entry->esi, entry->edi, entry->ebp);
    port_set8(&port, esp + eax, 4, vertrix_lift_edx >> 8);
    port_call_with(&port, 0x4ea0d0, esp, vertrix_lift_edx, first, second, entry->esi, entry->edi,
                   entry->ebp);
    port_call_with(&port, 0x4ea0d0, esp + 4, esp + 4, first, second, entry->esi, entry->edi,
                   entry->ebp);
    args[0] = port_u32(&port, esp, 0);
    args[1] = port_u32(&port, esp, 4);
    eax = call_frame(&port, 0x4e8730, esp, vertrix_lift_edx, first, second, entry->esi, entry->edi,
                     entry->ebp, args, 2);
    return port_return(&port, eax, vertrix_lift_edx);
}
