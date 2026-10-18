#include "rtlshims.h"

/* The runtime library's small shims. */

static uint32_t call_frame(Port *port, const LiftEntry *entry, uint32_t target, uint32_t eax,
                           uint32_t edx, uint32_t ebx, uint32_t ecx, uint32_t esi,
                           const uint32_t *stack, unsigned count)
{
    return port_call_registers(port, target, eax, edx, ebx, ecx, esi, entry->edi, entry->ebp, stack,
                               count);
}

/* Original 0x4e373e: the stream eax's buffer +0x10 released (0x4e0ec7 with its flags +4) and
 * cleared, then 0x4e36e4 of the stream with 1. */
uint32_t vertrix_port_rtl_stream_unbuffer_4e373e(PORT_SIGNATURE)
{
    Port port;
    uint32_t stream = entry->eax;
    uint32_t eax;
    port_open(&port, calls, services, globals, entry);
    port_call_with(&port, 0x4e0ec7, port_u32(&port, stream, 0x10), port_u32(&port, stream, 4),
                   entry->ebx, stream, entry->esi, entry->edi, entry->ebp);
    port_set32(&port, stream, 0x10, 0);
    eax = port_call_with(&port, 0x4e36e4, stream, 1, entry->ebx, stream, entry->esi, entry->edi,
                         entry->ebp);
    return port_return(&port, eax, vertrix_lift_edx);
}

/* Original 0x4e2389: the overflow report (0x4dae94, error 0x84 by 0x4e7280) giving the infinity
 * of eax's sign, edx:eax. */
uint32_t vertrix_port_rtl_overflow_error_4e2389(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 4
    };
    Port port;
    uint8_t stack[BELOW + 8];
    uint32_t esp = entry->esp - 4;
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    port_set32(&port, esp, 0, entry->eax);
    port_call_with(&port, 0x4dae94, entry->eax, entry->edx, entry->ebx, entry->ecx, entry->esi,
                   entry->edi, entry->ebp);
    port_call_with(&port, 0x4e7280, 0x84, vertrix_lift_edx, entry->ebx, entry->ecx, entry->esi,
                   entry->edi, entry->ebp);
    return port_return(&port, 0, (port_u32(&port, esp, 0) & 0x80000000u) | 0x7ff00000u);
}

/* Original 0x4eb250: 0x4eb410 of eax (also in edx), its edx less 0x21 when it answers; edx
 * kept. */
uint32_t vertrix_port_rtl_char_fold_4eb250(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 4
    };
    Port port;
    uint8_t stack[BELOW + 8];
    uint32_t esp = entry->esp - 4;
    uint32_t eax;
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    port_set32(&port, esp, 0, entry->edx);
    eax = port_call_with(&port, 0x4eb410, entry->eax, entry->eax, entry->ebx, entry->ecx,
                         entry->esi, entry->edi, entry->ebp);
    eax = eax != 0 ? vertrix_lift_edx - 0x21 : vertrix_lift_edx;
    return port_return(&port, eax, port_u32(&port, esp, 0));
}

/* Original 0x4e6b2c: the thread data's (0x507c9c) saved exception chain +0x54, when kept, put
 * back (its head) and cleared; edx kept. */
uint32_t vertrix_port_rtl_chain_restore_4e6b2c(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 4
    };
    Port port;
    uint8_t stack[BELOW + 8];
    uint32_t esp = entry->esp - 4;
    uint32_t eax;
    uint32_t edx;
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    port_set32(&port, esp, 0, entry->edx);
    eax = port_call_with(&port, port_u32(&port, 0, 0x507c9c), entry->eax, entry->edx, entry->ebx,
                         entry->ecx, entry->esi, entry->edi, entry->ebp);
    edx = vertrix_lift_edx;
    eax = port_u32(&port, eax, 0x54);
    if (eax != 0)
    {
        eax = port_u32(&port, eax, 0);
        edx = 0;
        port.env.chain = eax;
    }
    eax = port_call_with(&port, port_u32(&port, 0, 0x507c9c), eax, edx, entry->ebx, entry->ecx,
                         entry->esi, entry->edi, entry->ebp);
    port_set32(&port, eax, 0x54, 0);
    return port_return(&port, eax, port_u32(&port, esp, 0));
}

/* Original 0x484530 (ret 0x14): the routine at the third argument called (0x484520) when the first
 * is 0x598db0's; else eax the third, edx the first. */
uint32_t vertrix_port_rtl_message_hook_484530(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 4
    };
    Port port;
    uint8_t stack[BELOW + 8 + 20];
    uint32_t ebp = entry->esp - 4;
    uint32_t eax;
    uint32_t edx;
    port_open_arguments(&port, stack, calls, services, globals, entry, BELOW, 5);
    port_set32(&port, ebp, 0, entry->ebp);
    eax = port_u32(&port, ebp, 0x10);
    edx = port_u32(&port, ebp, 8);
    if (edx != port_u32(&port, 0, 0x598db0))
    {
        return port_return(&port, eax, edx);
    }
    eax = port_call_with(&port, 0x484520, eax, edx, entry->ebx, entry->ecx, entry->esi, entry->edi,
                         ebp);
    return port_return(&port, eax, vertrix_lift_edx);
}

/* Original 0x4e6b50: the routine at [eax] called when set (a zero pushed for es). */
uint32_t vertrix_port_rtl_call_if_set_4e6b50(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 4
    };
    Port port;
    uint8_t stack[BELOW + 8];
    uint32_t args[1] = {0};
    uint32_t eax;
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    port_set32(&port, entry->esp - 4, 0, 0);
    if (port_u32(&port, entry->eax, 0) == 0)
    {
        return port_return(&port, entry->eax, entry->edx);
    }
    eax = call_frame(&port, entry, port_u32(&port, entry->eax, 0), entry->eax, entry->edx,
                     entry->ebx, entry->ecx, entry->esi, args, 1);
    return port_return(&port, eax, vertrix_lift_edx);
}

/* Original 0x4e5bec: the object eax's method +0x10 called when its +0 is set; eax the object. */
uint32_t vertrix_port_rtl_object_flush_4e5bec(PORT_SIGNATURE)
{
    Port port;
    uint32_t object = entry->eax;
    port_open(&port, calls, services, globals, entry);
    if (port_u32(&port, object, 0) == 0)
    {
        return port_return(&port, object, entry->edx);
    }
    port_call_with(&port, port_u32(&port, object, 0x10), object, entry->edx, entry->ebx, object,
                   entry->esi, entry->edi, entry->ebp);
    return port_return(&port, object, vertrix_lift_edx);
}

/* Original 0x4cf910 (ret 4): when 0x4cf880 of 0 answers, 0x4df140 of it with the argument fills
 * the frame dword (0 otherwise), which is eax. */
uint32_t vertrix_port_rtl_query_dword_4cf910(PORT_SIGNATURE)
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
    eax = port_call_with(&port, 0x4cf880, 0, entry->edx, entry->ebx, entry->ecx, entry->esi,
                         entry->edi, entry->ebp);
    port_set32(&port, esp, 0, 0);
    if (eax != 0)
    {
        port_call_with(&port, 0x4df140, eax, port_u32(&port, entry->esp, 4), esp, entry->ecx,
                       entry->esi, entry->edi, entry->ebp);
    }
    return port_return(&port, port_u32(&port, esp, 0), vertrix_lift_edx);
}
