#include "port_rtllinks.h"

/* The runtime library's handler links and lookups. */

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

/* Original 0x4cd520: 0x4cd544 of the first two arguments, 0 and the third (cdecl; eax the third,
 * edx the second, ebx the first); edx kept. */
uint32_t vertrix_port_rtl_forward_three_4cd520(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 8
    };
    Port port;
    uint8_t stack[BELOW + 8 + 12];
    uint32_t args[4];
    uint32_t eax;
    port_open_arguments(&port, stack, calls, services, globals, entry, BELOW, 3);
    args[0] = port_u32(&port, entry->esp, 4);
    args[1] = port_u32(&port, entry->esp, 8);
    args[2] = 0;
    args[3] = port_u32(&port, entry->esp, 0xc);
    eax = call_frame(&port, 0x4cd544, args[3], args[1], args[0], entry->ecx, entry->esi, entry->edi,
                     entry->ebp, args, 4);
    return port_return(&port, eax, entry->edx);
}

/* Original 0x4bd210: the decoder eax's upsampler (0x1c bytes from the memory manager +4's method
 * +0) kept in +0x1b4 with its methods 0x4bcea0, 0x4bd1c0, 0x4bcbc0, 0x4bce90, +0x10 and +0x14
 * clear and +0x18 1; edx kept. */
uint32_t vertrix_port_jpeg_marker_reader_init_4bd210(PORT_SIGNATURE)
{
    Port port;
    uint32_t cinfo = entry->eax;
    uint32_t memory;
    uint32_t eax;
    port_open(&port, calls, services, globals, entry);
    memory = port_u32(&port, cinfo, 4);
    eax = port_call_with(&port, port_u32(&port, memory, 0), cinfo, 0, 0x1c, cinfo, memory,
                         entry->edi, entry->ebp);
    port_set32(&port, cinfo, 0x1b4, eax);
    port_set32(&port, eax, 0, 0x4bcea0);
    port_set32(&port, eax, 4, 0x4bd1c0);
    port_set32(&port, eax, 8, 0x4bcbc0);
    port_set32(&port, eax, 0xc, 0x4bce90);
    port_set32(&port, eax, 0x10, 0);
    port_set32(&port, eax, 0x14, 0);
    port_set32(&port, eax, 0x18, 1);
    return port_return(&port, eax, entry->edx);
}

/* The dword 0x4d1e80 finds for the key at ebx+`field` into the frame, else 0x4cf850 of the object
 * eax with that frame dword. */
static uint32_t lookup_dword(PORT_SIGNATURE, uint32_t field)
{
    enum
    {
        BELOW = 0xc
    };
    Port port;
    uint8_t stack[BELOW + 8];
    uint32_t esp = entry->esp - 0xc;
    uint32_t self = entry->eax;
    uint32_t args[2];
    uint32_t eax;
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    port_set32(&port, esp, 8, entry->ecx);
    port_set32(&port, esp, 4, entry->esi);
    args[0] = port_u32(&port, entry->ebx, field);
    args[1] = esp;
    eax = call_frame(&port, 0x4d1e80, esp, entry->edx, entry->ebx, entry->ecx, self, entry->edi,
                     entry->ebp, args, 2);
    if (eax != 0)
    {
        return port_return(&port, port_u32(&port, esp, 0), vertrix_lift_edx);
    }
    args[0] = port_u32(&port, esp, 0);
    eax = call_frame(&port, 0x4cf850, self, vertrix_lift_edx, entry->ebx, entry->ecx, self,
                     entry->edi, entry->ebp, args, 1);
    return port_return(&port, eax, vertrix_lift_edx);
}

/* Original 0x4d0620: lookup_dword of ebx's +8. */
uint32_t vertrix_port_rtl_lookup_dword_4d0620(PORT_SIGNATURE)
{
    return lookup_dword(calls, services, globals, entry, 8);
}

/* Original 0x4d23f0: lookup_dword of ebx's +4. */
uint32_t vertrix_port_rtl_lookup_dword_4d23f0(PORT_SIGNATURE)
{
    return lookup_dword(calls, services, globals, entry, 4);
}

/* Original 0x4c1e10 (ret 0xc): the decoder eax's main controller (+0x1c4) method +0xc for the row
 * [ebx] and the output rows (first argument) at the count in [second], both counts then raised;
 * eax the second argument. */
uint32_t vertrix_port_jpeg_process_row_4c1e10(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0xc
    };
    Port port;
    uint8_t stack[BELOW + 8 + 12];
    uint32_t ebp = entry->esp - 4;
    uint32_t rows;
    uint32_t counter;
    uint32_t controller;
    port_open_arguments(&port, stack, calls, services, globals, entry, BELOW, 3);
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -4, entry->esi);
    port_set32(&port, ebp, -8, entry->edi);
    rows = port_u32(&port, ebp, 8);
    counter = port_u32(&port, ebp, 0xc);
    controller = port_u32(&port, entry->eax, 0x1c4);
    port_call_with(&port, port_u32(&port, controller, 0xc), entry->eax, entry->edx,
                   port_u32(&port, entry->ebx, 0), port_u32(&port, counter, 0) * 4 + rows,
                   entry->ebx, controller, ebp);
    port_set32(&port, counter, 0, port_u32(&port, counter, 0) + 1);
    port_set32(&port, entry->ebx, 0, port_u32(&port, entry->ebx, 0) + 1);
    return port_return(&port, counter, vertrix_lift_edx);
}

/* Original 0x4e6ae0: the thread data's (0x507c9c) handler record +0x54 set to eax's call result
 * edx, linked to the exception chain with the handler 0x4e6918 and made its head, then the filter
 * 0x4e6734 installed (0x4f1cc0); edx kept. */
uint32_t vertrix_port_rtl_handler_install_4e6ae0(PORT_SIGNATURE)
{
    Port port;
    uint32_t edx;
    uint32_t eax;
    uint32_t args[1] = {0x4e6734};
    port_open(&port, calls, services, globals, entry);
    eax = port_call_with(&port, port_u32(&port, 0, 0x507c9c), entry->eax, entry->eax, entry->ebx,
                         entry->ecx, entry->esi, entry->edi, entry->ebp);
    edx = vertrix_lift_edx;
    port_set32(&port, eax, 0x54, edx);
    eax = port.env.chain;
    eax = port_call_with(&port, port_u32(&port, 0, 0x507c9c), eax, eax, entry->ebx, entry->ecx,
                         entry->esi, entry->edi, entry->ebp);
    edx = vertrix_lift_edx;
    port_set32(&port, port_u32(&port, eax, 0x54), 0, edx);
    eax = port_call_with(&port, port_u32(&port, 0, 0x507c9c), port_u32(&port, eax, 0x54), edx,
                         entry->ebx, entry->ecx, entry->esi, entry->edi, entry->ebp);
    eax = port_u32(&port, eax, 0x54);
    port_set32(&port, eax, 4, 0x4e6918);
    eax = port_call_with(&port, port_u32(&port, 0, 0x507c9c), eax, 0, entry->ebx, entry->ecx,
                         entry->esi, entry->edi, entry->ebp);
    eax = port_u32(&port, eax, 0x54);
    port.env.chain = eax;
    eax = call_frame(&port, 0x4f1cc0, eax, vertrix_lift_edx, entry->ebx, entry->ecx, entry->esi,
                     entry->edi, entry->ebp, args, 1);
    return port_return(&port, eax, entry->edx);
}

/* Original 0x4e9f00: 0x4f1b40 of eax; a failure gives 0x4e0884's eax, success 0; edx kept. */
uint32_t vertrix_port_rtl_handle_call_4e9f00(PORT_SIGNATURE)
{
    Port port;
    uint32_t args[1];
    uint32_t eax;
    port_open(&port, calls, services, globals, entry);
    args[0] = entry->eax;
    eax = call_frame(&port, 0x4f1b40, entry->eax, entry->edx, entry->ebx, entry->ecx, entry->esi,
                     entry->edi, entry->ebp, args, 1);
    if (eax != 0)
    {
        return port_return(&port, 0, entry->edx);
    }
    eax = port_call_with(&port, 0x4e0884, eax, vertrix_lift_edx, entry->ebx, entry->ecx, entry->esi,
                         entry->edi, entry->ebp);
    return port_return(&port, eax, entry->edx);
}
