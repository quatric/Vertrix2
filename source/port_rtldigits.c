#include "port_rtldigits.h"

/* Digit values, parent form searches, handle writes and string copies. */

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

/* Original 0x4ea6b0: the value of the digit al in base 36 (letters folded by 0x4e82f0), 0x25 for
 * anything else. edx kept. */
uint32_t vertrix_port_rtl_digit_value_4ea6b0(PORT_SIGNATURE)
{
    Port port;
    uint32_t c = entry->eax & 0xff;
    uint32_t folded;
    port_open(&port, calls, services, globals, entry);
    if (c >= 0x30 && c <= 0x39)
    {
        return port_return(&port, c - 0x30, entry->edx);
    }
    folded = port_call_with(&port, 0x4e82f0, c, entry->edx, entry->ebx, entry->ecx, entry->esi,
                            entry->edi, entry->ebp);
    if ((folded & 0xff) >= 0x61 && (folded & 0xff) <= 0x7a)
    {
        return port_return(&port, (folded & 0xff) - 0x57, entry->edx);
    }
    return port_return(&port, 0x25, entry->edx);
}

/* Original 0x4d1840: the first control up the parents of eax's handle (+0x1c, 0x4f19c8 and
 * 0x4cf8e0 at each step) whose method +0xb4 agrees (the edx it answers), else 0. edx kept. */
uint32_t vertrix_port_rtl_parent_form_4d1840(PORT_SIGNATURE)
{
    Port port;
    uint32_t eax = entry->eax;
    uint32_t control;
    uint32_t args[1];
    port_open(&port, calls, services, globals, entry);
    if (eax == 0 || port_u32(&port, eax, 0x1c) == 0)
    {
        return port_return(&port, 0, entry->edx);
    }
    args[0] = port_u32(&port, eax, 0x1c);
    eax = call_frame(&port, 0x4f19c8, args[0], entry->edx, entry->ebx, entry->ecx, entry->esi,
                     entry->edi, entry->ebp, args, 1);
    args[0] = eax;
    control = call_frame(&port, 0x4cf8e0, eax, vertrix_lift_edx, entry->ebx, entry->ecx, entry->esi,
                         entry->edi, entry->ebp, args, 1);
    while (control != 0 && !port.env.failed)
    {
        uint32_t methods = port_u32(&port, control, 0);
        eax = port_call_with(&port, port_u32(&port, methods, 0xb4), control, control, entry->ebx,
                             methods, entry->esi, entry->edi, entry->ebp);
        control = vertrix_lift_edx;
        if (eax != 0)
        {
            return port_return(&port, control, entry->edx);
        }
        args[0] = port_u32(&port, control, 0x1c);
        eax = call_frame(&port, 0x4f19c8, eax, control, entry->ebx, methods, entry->esi, entry->edi,
                         entry->ebp, args, 1);
        args[0] = eax;
        control = call_frame(&port, 0x4cf8e0, eax, vertrix_lift_edx, entry->ebx, methods,
                             entry->esi, entry->edi, entry->ebp, args, 1);
    }
    return port_return(&port, 0, entry->edx);
}

/* Original 0x4d79c0: ebx bytes from edx written to the file eax's handle +4 (0x4f1d08); a failure
 * reports the last error (0x4f1bbc, 0x4d9930) and a short count the error 0xd (0x4d9a10), both
 * against the name +0xc. */
uint32_t vertrix_port_rtl_file_write_4d79c0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0xc
    };
    Port port;
    uint8_t stack[BELOW + 8];
    uint32_t esp = entry->esp - 0xc;
    uint32_t self = entry->eax;
    uint32_t size = entry->ebx;
    uint32_t eax;
    uint32_t args[5];
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    port_set32(&port, entry->esp - 4, 0, entry->ecx);
    port_set32(&port, entry->esp - 8, 0, entry->esi);
    if (size == 0)
    {
        return port_return(&port, self, entry->edx);
    }
    args[0] = port_u32(&port, self, 4);
    args[1] = entry->edx;
    args[2] = size;
    args[3] = esp;
    args[4] = 0;
    eax = call_frame(&port, 0x4f1d08, esp, entry->edx, size, entry->ecx, self, entry->edi,
                     entry->ebp, args, 5);
    if (eax == 0)
    {
        uint32_t name = port_u32(&port, self, 0xc);
        eax = port_call_with(&port, 0x4f1bbc, name, vertrix_lift_edx, size, entry->ecx, self,
                             entry->edi, entry->ebp);
        args[0] = eax;
        args[1] = name;
        eax = call_frame(&port, 0x4d9930, eax, vertrix_lift_edx, size, entry->ecx, self, entry->edi,
                         entry->ebp, args, 2);
    }
    if (size != port_u32(&port, esp, 0))
    {
        args[0] = 0xd;
        args[1] = 0xffffffffu;
        args[2] = port_u32(&port, self, 0xc);
        eax = call_frame(&port, 0x4d9a10, args[2], vertrix_lift_edx, size, entry->ecx, self,
                         entry->edi, entry->ebp, args, 3);
    }
    return port_return(&port, eax, vertrix_lift_edx);
}

/* Original 0x4e65b0: a copy of the text eax in a new block of its length and end (0x4e7c90); 0
 * when none. edx kept. */
uint32_t vertrix_port_rtl_text_duplicate_4e65b0(PORT_SIGNATURE)
{
    Port port;
    uint32_t text = entry->eax;
    uint32_t length = 0;
    uint32_t copy;
    uint32_t index;
    port_open(&port, calls, services, globals, entry);
    while (port_u8(&port, text, length) != 0 && !port.env.failed)
    {
        length++;
    }
    length++;
    copy = port_call_with(&port, 0x4e7c90, length, entry->edx, entry->ebx, length, text,
                          text + length, entry->ebp);
    if (copy != 0)
    {
        for (index = 0; index < length && !port.env.failed; index++)
        {
            port_set8(&port, copy, index, port_u8(&port, text, index));
        }
    }
    return port_return(&port, copy, entry->edx);
}
