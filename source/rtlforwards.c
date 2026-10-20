#include "rtlforwards.h"

#include "rtlextendeds.h"

/* The runtime library's argument forwarding routines. */

static uint32_t call_frame(Port *port, uint32_t target, uint32_t eax, uint32_t edx, uint32_t ebx,
                           uint32_t ecx, uint32_t esi, uint32_t edi, uint32_t ebp,
                           const uint32_t *stack, unsigned count)
{
    return port_call_registers(port, target, eax, edx, ebx, ecx, esi, edi, ebp, stack, count);
}

/* Original 0x4cc7a0: 0x4f1a94 of the window handle (+0x1c of the object +0x1c of eax) with 0x10
 * and two zeros; edx kept. */
uint32_t vertrix_port_rtl_window_close_4cc7a0(PORT_SIGNATURE)
{
    Port port;
    uint32_t owner;
    uint32_t args[4];
    uint32_t eax;
    port_open(&port, calls, services, globals, entry);
    owner = port_u32(&port, entry->eax, 0x1c);
    args[0] = port_u32(&port, owner, 0x1c);
    args[1] = 0x10;
    args[2] = 0;
    args[3] = 0;
    eax = call_frame(&port, 0x4f1a94, owner, entry->edx, entry->ebx, entry->ecx, entry->esi,
                     entry->edi, entry->ebp, args, 4);
    return port_return(&port, eax, entry->edx);
}

/* Original 0x4edb48: the product (0x4edc0e) of the extended reals eax and edx (unpacked:
 * eax/edx/si and ebx/ecx/esi's high word) stored at ebx with the product's sign and exponent word
 * (0x4edc0e's si). */
uint32_t vertrix_port_rtl_extended_op_4edb48(PORT_SIGNATURE)
{
    Port port;
    uint32_t left = entry->eax;
    uint32_t right = entry->edx;
    port_open(&port, calls, services, globals, entry);
    const uint32_t esi = ((uint32_t)port_u16(&port, right, 8) << 16) | port_u16(&port, left, 8);
    const VertrixExtended value =
        vertrix_extended_multiply(port_u32(&port, left, 0), port_u32(&port, left, 4),
                                  port_u32(&port, right, 0), port_u32(&port, right, 4), esi);
    port_set32(&port, entry->ebx, 0, value.eax);
    port_set32(&port, entry->ebx, 4, value.edx);
    port_set16(&port, entry->ebx, 8, value.esi);
    return port_return(&port, value.eax, value.edx);
}

/* Original 0x4da71b: 0x4da3ba of eax (ebx 0, ecx eax) under the guard record 0x51a930 linked into
 * the exception chain; eax the chain head restored. */
uint32_t vertrix_port_rtl_guarded_call_4da71b(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x1c
    };
    Port port;
    uint8_t stack[BELOW + 8];
    uint32_t esp = entry->esp - 0x1c;
    uint32_t eax;
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    port_set32(&port, esp, 0x18, entry->ebx);
    port_set32(&port, esp, 0x14, entry->ecx);
    port_set32(&port, esp, 0, port.env.chain);
    port.env.chain = esp;
    port_set32(&port, esp, 4, 0x4ec1ec);
    port_set32(&port, esp, 8, 0x51a930);
    port_set32(&port, esp, 0xc, 0);
    port_call_with(&port, 0x4da3ba, entry->eax, entry->edx, 0, entry->eax, entry->esi, entry->edi,
                   entry->ebp);
    eax = port_u32(&port, esp, 0);
    port.env.chain = eax;
    return port_return(&port, eax, vertrix_lift_edx);
}

/* Original 0x4cf9d0 (ret 0x10): a window procedure: the message 0x360 (second argument) gives 1,
 * others go to 0x4cf650 with the window of the first (0x4cf910) and the four arguments. */
uint32_t vertrix_port_rtl_window_proc_4cf9d0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0
    };
    Port port;
    uint8_t stack[BELOW + 8 + 16];
    uint32_t args[5];
    uint32_t at;
    uint32_t eax;
    port_open_arguments(&port, stack, calls, services, globals, entry, BELOW, 4);
    if (port_u32(&port, entry->esp, 8) == 0x360)
    {
        return port_return(&port, 1, entry->edx);
    }
    args[0] = port_u32(&port, entry->esp, 4);
    eax = call_frame(&port, 0x4cf910, entry->eax, entry->edx, entry->ebx, entry->ecx, entry->esi,
                     entry->edi, entry->ebp, args, 1);
    args[0] = eax;
    for (at = 1; at <= 4; at++)
    {
        args[at] = port_u32(&port, entry->esp, 4 * at);
    }
    eax = call_frame(&port, 0x4cf650, eax, vertrix_lift_edx, entry->ebx, entry->ecx, entry->esi,
                     entry->edi, entry->ebp, args, 5);
    return port_return(&port, eax, vertrix_lift_edx);
}

/* The window ebx's dword (0x4d1e50 into the frame) when it answers, else 0x4cf850 of the object
 * eax with that frame dword. */
static uint32_t window_dword(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 8
    };
    Port port;
    uint8_t stack[BELOW + 8];
    uint32_t esp = entry->esp - 8;
    uint32_t self = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t eax;
    uint32_t args[1];
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    port_set32(&port, esp, 4, entry->esi);
    if (entry->ebx != 0)
    {
        eax = port_call_with(&port, 0x4d1e50, entry->ebx, esp, entry->ebx, entry->ecx, self,
                             entry->edi, entry->ebp);
        edx = vertrix_lift_edx;
        if (eax != 0)
        {
            return port_return(&port, port_u32(&port, esp, 0), edx);
        }
    }
    args[0] = port_u32(&port, esp, 0);
    eax = call_frame(&port, 0x4cf850, self, edx, entry->ebx, entry->ecx, self, entry->edi,
                     entry->ebp, args, 1);
    return port_return(&port, eax, vertrix_lift_edx);
}

/* Originals 0x4d0670 and 0x4d06a0: window_dword. */
uint32_t vertrix_port_rtl_window_dword_4d0670(PORT_SIGNATURE)
{
    return window_dword(calls, services, globals, entry);
}

uint32_t vertrix_port_rtl_window_dword_4d06a0(PORT_SIGNATURE)
{
    return window_dword(calls, services, globals, entry);
}

/* Original 0x4db950 (ret 0xc): 0x4f1a44 of the handle +0xc of 0x4ce740's object with the three
 * arguments, the text (second) emptied when it gives 0; eax and edx its result. */
uint32_t vertrix_port_rtl_window_text_4db950(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 4
    };
    Port port;
    uint8_t stack[BELOW + 8 + 12];
    uint32_t ebp = entry->esp - 4;
    uint32_t args[4];
    uint32_t eax;
    port_open_arguments(&port, stack, calls, services, globals, entry, BELOW, 3);
    port_set32(&port, ebp, 0, entry->ebp);
    eax = port_call_with(&port, 0x4ce740, entry->eax, entry->edx, entry->ebx, entry->ecx,
                         entry->esi, entry->edi, ebp);
    eax = port_u32(&port, eax, 0xc);
    args[0] = eax;
    args[1] = port_u32(&port, ebp, 8);
    args[2] = port_u32(&port, ebp, 0xc);
    args[3] = port_u32(&port, ebp, 0x10);
    eax = call_frame(&port, 0x4f1a44, eax, vertrix_lift_edx, entry->ebx, entry->ecx, entry->esi,
                     entry->edi, ebp, args, 4);
    if (eax == 0)
    {
        port_set8(&port, port_u32(&port, ebp, 0xc), 0, 0);
    }
    return port_return(&port, eax, eax);
}

/* Original 0x4bb470 (ret 4): 0x4c9860 of the rows [edx] (edx ebx, ebx ecx, ecx 0) with the stack
 * argument and the decoder eax's width +0x70. */
uint32_t vertrix_port_jpeg_rows_copy_4bb470(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0xc
    };
    Port port;
    uint8_t stack[BELOW + 8 + 4];
    uint32_t ebp = entry->esp - 4;
    uint32_t args[2];
    uint32_t eax;
    port_open_arguments(&port, stack, calls, services, globals, entry, BELOW, 1);
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -4, entry->esi);
    port_set32(&port, ebp, -8, entry->edi);
    args[0] = port_u32(&port, ebp, 8);
    args[1] = port_u32(&port, entry->eax, 0x70);
    eax = call_frame(&port, 0x4c9860, port_u32(&port, entry->edx, 0), entry->ebx, entry->ecx, 0,
                     entry->edx, args[0], ebp, args, 2);
    return port_return(&port, eax, vertrix_lift_edx);
}
