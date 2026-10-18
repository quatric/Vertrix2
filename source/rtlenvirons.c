#include "rtlenvirons.h"

/* The runtime library's environment settings. */

/* The registers the parse carries between its calls. */
typedef struct
{
    uint32_t edx;
    uint32_t ebx;
    uint32_t ecx;
    uint32_t esi;
    uint32_t edi;
    uint32_t ebp;
} EnvironRegs;

static uint32_t environ_call(Port *port, EnvironRegs *regs, uint32_t target, uint32_t eax)
{
    eax = port_call_with(port, target, eax, regs->edx, regs->ebx, regs->ecx, regs->esi, regs->edi,
                         regs->ebp);
    regs->edx = vertrix_lift_edx;
    return eax;
}

/* The field from regs->ecx up to `mark` (none: the place 0, as the original) copied into the frame
 * `buffer` (0x4eb860), ended and read in hexadecimal (0x4ea6a0); ebp is left at the mark. */
static uint32_t hex_field(Port *port, EnvironRegs *regs, uint32_t buffer, uint32_t mark)
{
    uint32_t place = regs->ecx;
    uint32_t length;
    while (port_u8(port, place, 0) != mark && !port->env.failed)
    {
        if (port_u8(port, place, 0) == 0)
        {
            place = 0;
            break;
        }
        place++;
    }
    regs->ebp = place;
    length = place - regs->ecx;
    regs->esi = length;
    regs->edx = regs->ecx;
    regs->ebx = length;
    environ_call(port, regs, 0x4eb860, buffer);
    regs->ebx = 0x10;
    port_set8(port, buffer + length, 0, 0);
    regs->edx = 0;
    return environ_call(port, regs, 0x4ea6a0, buffer);
}

/* Original 0x4e9f10: the setting 0x5130a8 (0x4dac40), when present, is a run of "a:b:c*" hex
 * triples: each passes b and a to 0x4e0328 and then a and c to 0x4e0228. A set one ends with
 * 0x4ea710 of 0x5130b4 (its eax; else 0). edx as restored from the frame. */
uint32_t vertrix_port_rtl_environ_parse_4e9f10(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x28
    };
    Port port;
    uint8_t stack[BELOW + 8];
    uint32_t esp = entry->esp - 0x28;
    uint32_t eax;
    uint32_t first;
    uint32_t third;
    EnvironRegs regs;
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    port_set32(&port, esp, 0x24, entry->ebx);
    port_set32(&port, esp, 0x20, entry->ecx);
    port_set32(&port, esp, 0x1c, entry->edx);
    port_set32(&port, esp, 0x18, entry->esi);
    port_set32(&port, esp, 0x14, entry->edi);
    port_set32(&port, esp, 0x10, entry->ebp);
    regs.edx = entry->edx;
    regs.ebx = entry->ebx;
    regs.ecx = entry->ecx;
    regs.esi = entry->esi;
    regs.edi = entry->edi;
    regs.ebp = entry->ebp;
    eax = environ_call(&port, &regs, 0x4dac40, 0x5130a8);
    regs.ecx = eax;
    if (eax != 0)
    {
        while (port_u8(&port, regs.ecx, 0) != 0 && !port.env.failed)
        {
            first = hex_field(&port, &regs, esp, 0x3a);
            regs.edi = first;
            regs.ecx = regs.ebp + 1;
            port_set32(&port, esp, 0xc, hex_field(&port, &regs, esp, 0x3a));
            regs.ecx = regs.ebp + 1;
            third = hex_field(&port, &regs, esp, 0x2a);
            regs.ecx = third;
            regs.edx = first;
            environ_call(&port, &regs, 0x4e0328, port_u32(&port, esp, 0xc));
            regs.edx = third;
            regs.esi = regs.ebp + 1;
            environ_call(&port, &regs, 0x4e0228, first);
            regs.ecx = regs.esi;
        }
        eax = environ_call(&port, &regs, 0x4ea710, 0x5130b4);
    }
    return port_return(&port, eax, port_u32(&port, esp, 0x1c));
}
