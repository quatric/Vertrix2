#include "rtlprints.h"

/* The runtime library's formatted output wrappers. */

static uint32_t call_frame(Port *port, const LiftEntry *entry, uint32_t target, uint32_t eax,
                           uint32_t edx, uint32_t ebx, uint32_t ecx, uint32_t esi,
                           const uint32_t *stack, unsigned count)
{
    return port_call_registers(port, target, eax, edx, ebx, ecx, esi, entry->edi, entry->ebp, stack,
                               count);
}

/* The variadic call of `target` (cdecl, ebx and edx saved, a frame dword below): eax `eax` (or the
 * first argument when `fixed` is 2), edx the next argument, ebx the frame dword holding the
 * argument list past them (handed as the stack argument when `pass` is set). */
static uint32_t print_call(PORT_SIGNATURE, uint32_t target, unsigned fixed, uint32_t eax, int pass)
{
    enum
    {
        BELOW = 0xc
    };
    Port port;
    uint8_t stack[BELOW + 8 + 8];
    uint32_t esp = entry->esp - 0xc;
    uint32_t list = entry->esp + 4 + 4 * fixed;
    uint32_t args[1];
    port_open_arguments(&port, stack, calls, services, globals, entry, BELOW, 2);
    port_set32(&port, esp, 8, entry->ebx);
    port_set32(&port, esp, 4, entry->edx);
    port_set32(&port, esp, 0, list);
    if (fixed == 2)
    {
        eax = port_u32(&port, entry->esp, 4);
    }
    args[0] = list;
    eax = call_frame(&port, entry, target, eax, port_u32(&port, entry->esp, 4 * fixed), esp,
                     entry->ecx, entry->esi, args, pass ? 1 : 0);
    return port_return(&port, eax, port_u32(&port, esp, 4));
}

/* Original 0x4d85c0: 0x4e2434 of the stream 0x50524e with the format and its arguments. */
uint32_t vertrix_port_rtl_print_4d85c0(PORT_SIGNATURE)
{
    return print_call(calls, services, globals, entry, 0x4e2434, 1, 0x50524e, 1);
}

/* Original 0x4dac10: 0x4cd0a4 of the first argument with the format and its arguments. */
uint32_t vertrix_port_rtl_print_4dac10(PORT_SIGNATURE)
{
    return print_call(calls, services, globals, entry, 0x4cd0a4, 2, 0, 1);
}

/* Original 0x4dacf8: 0x4dacd0 of the first argument with the format and its arguments. */
uint32_t vertrix_port_rtl_print_4dacf8(PORT_SIGNATURE)
{
    return print_call(calls, services, globals, entry, 0x4dacd0, 2, 0, 1);
}

/* Original 0x4cdfb0: 0x4cdbe0 of the first argument with the format and its arguments, the frame
 * dword cleared after. */
uint32_t vertrix_port_rtl_print_4cdfb0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0xc
    };
    Port port;
    uint8_t stack[BELOW + 8 + 8];
    uint32_t esp = entry->esp - 0xc;
    uint32_t eax;
    port_open_arguments(&port, stack, calls, services, globals, entry, BELOW, 2);
    port_set32(&port, esp, 8, entry->ebx);
    port_set32(&port, esp, 4, entry->edx);
    port_set32(&port, esp, 0, entry->esp + 0xc);
    eax = port_call_with(&port, 0x4cdbe0, port_u32(&port, entry->esp, 4),
                         port_u32(&port, entry->esp, 8), esp, entry->ecx, entry->esi, entry->edi,
                         entry->ebp);
    port_set32(&port, esp, 0, 0);
    return port_return(&port, eax, port_u32(&port, esp, 4));
}

/* Original 0x4dacd0: 0x4e4110 with the output pair 0x4daca0/0x4daccc and the target eax laid out in
 * the frame (eax the frame, ecx and esi the pair, the five frame dwords as arguments). */
uint32_t vertrix_port_rtl_print_string_4dacd0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x1c
    };
    Port port;
    uint8_t stack[BELOW + 8];
    uint32_t esp = entry->esp - 0x1c;
    uint32_t args[5];
    uint32_t at;
    uint32_t eax;
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    port_set32(&port, esp, 0x18, entry->ecx);
    port_set32(&port, esp, 0x14, entry->esi);
    port_set32(&port, esp, 8, entry->eax);
    port_set32(&port, esp, 0, 0x4daca0);
    port_set32(&port, esp, 4, 0x4daccc);
    for (at = 0; at < 5; at++)
    {
        args[at] = port_u32(&port, esp, 4 * at);
    }
    eax = call_frame(&port, entry, 0x4e4110, esp, entry->edx, entry->ebx, 0x4daca0, 0x4daccc, args,
                     5);
    return port_return(&port, eax, vertrix_lift_edx);
}

/* Original 0x4e1230 (ret 4): when 0x4e11b0 of 0 answers, 0x4df140 of it with the argument fills
 * the frame dword (0 otherwise), which is eax. */
uint32_t vertrix_port_rtl_query_dword_4e1230(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 8
    };
    Port port;
    uint8_t stack[BELOW + 8 + 4];
    uint32_t esp = entry->esp - 8;
    uint32_t eax;
    port_open_arguments(&port, stack, calls, services, globals, entry, BELOW, 1);
    port_set32(&port, esp, 4, entry->ebx);
    eax = port_call_with(&port, 0x4e11b0, 0, entry->edx, entry->ebx, entry->ecx, entry->esi,
                         entry->edi, entry->ebp);
    port_set32(&port, esp, 0, 0);
    if (eax != 0)
    {
        port_call_with(&port, 0x4df140, eax, port_u32(&port, entry->esp, 4), esp, entry->ecx,
                       entry->esi, entry->edi, entry->ebp);
    }
    return port_return(&port, port_u32(&port, esp, 0), vertrix_lift_edx);
}

/* Original 0x4ecf60: the value al (with ah) as two decimal digits at ebx: below ten it is ah and
 * al as they are, else ax divided by ten (`div cl`, unchanged when it would fault). eax as left. */
uint32_t vertrix_port_rtl_two_digits_4ecf60(PORT_SIGNATURE)
{
    Port port;
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    LiftFlags flags = {0, 0, 0, 0, 0, 0};
    port_open(&port, calls, services, globals, entry);
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

/* Original 0x4e3698: the record eax linked (+8) at the head +0x20 of [edx], holding ebx (or the
 * exception chain when 0) at +0, edx at +4 and cl at +0xc; eax the record. */
uint32_t vertrix_port_rtl_record_link_4e3698(PORT_SIGNATURE)
{
    Port port;
    uint32_t record = entry->eax;
    uint32_t edx = entry->edx;
    port_open(&port, calls, services, globals, entry);
    port_set32(&port, record, 0, entry->ebx);
    port_set32(&port, record, 4, edx);
    port_set32(&port, record, 8, port_u32(&port, port_u32(&port, edx, 0), 0x20));
    port_set8(&port, record, 0xc, entry->ecx);
    port_set32(&port, port_u32(&port, edx, 0), 0x20, record);
    if (entry->ebx == 0)
    {
        port_set32(&port, record, 0, port.env.chain);
    }
    return port_return(&port, record, edx);
}
