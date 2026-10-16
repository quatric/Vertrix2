#include "port_rtlfaults.h"

/* The runtime library's fault reports. */

/* The message for the exception code `code` of the context `context` (0 for the codes with their
 * own wording: an access violation, or none known). */
static uint32_t fault_message(Port *port, uint32_t code, uint32_t context)
{
    switch (code)
    {
        case 0xc000008du:
            return 0x512af0;
        case 0xc000008eu:
            return 0x512b44;
        case 0xc000008fu:
            return 0x512b98;
        case 0xc0000090u:
            return 0x512c88;
        case 0xc0000091u:
            return 0x512bec;
        case 0xc0000092u:
            return (port_u8(port, context, 0x21) & 2) != 0 ? 0x512a48 : 0x512a9c;
        case 0xc0000093u:
            return 0x512c38;
        case 0xc0000094u:
            return 0x512dcc;
        case 0xc0000096u:
            return 0x512d50;
        case 0xc000001du:
            return 0x512d90;
        case 0xc00000fdu:
            return 0x512e10;
        default:
            return 0;
    }
}

/* Original 0x4e6734 (ret 4): the exception filter for the pointers at the stack argument (record
 * and context). Unless 0x4e66a0 claims it or 0x4e89f4 gives -1 (both 0), the record's code is
 * worded into the frame by 0x4e66dc (an access violation with its address +0x18 and read or
 * write +0x14, an unknown code with the code itself, each with the address +0xc) and written to
 * the standard error handle (+8 of [0x507c8c]) by 0x4f1d08. eax 1. */
uint32_t vertrix_port_rtl_fault_filter_4e6734(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x10c
    };
    Port port;
    uint8_t stack[BELOW + 8 + 4];
    uint32_t esp = entry->esp - 0x10c;
    uint32_t record;
    uint32_t context;
    uint32_t message;
    uint32_t eax;
    uint32_t edx;
    uint32_t length;
    uint32_t handle;
    uint32_t args[5];
    port_open_arguments(&port, stack, calls, services, globals, entry, BELOW, 1);
    port_set32(&port, esp, 0x108, entry->ebx);
    port_set32(&port, esp, 0x104, entry->edi);
    eax = port_u32(&port, entry->esp, 4);
    record = port_u32(&port, eax, 0);
    context = port_u32(&port, eax, 4);
    eax = port_call_with(&port, 0x4e66a0, entry->eax, entry->edx, context, record, entry->esi,
                         entry->edi, entry->ebp);
    if (eax != 0)
    {
        return port_return(&port, 0, vertrix_lift_edx);
    }
    eax = port_call_with(&port, 0x4e89f4, eax, vertrix_lift_edx, context, record, entry->esi,
                         entry->edi, entry->ebp);
    if (eax == 0xffffffffu)
    {
        return port_return(&port, 0, vertrix_lift_edx);
    }
    port_set8(&port, esp, 0, 0);
    message = fault_message(&port, port_u32(&port, record, 0), context);
    if (port_u32(&port, record, 0) == 0xc0000005u)
    {
        port_call_with(&port, 0x4e66dc, esp, 0x512ce0, port_u32(&port, record, 0xc), record,
                       entry->esi, entry->edi, entry->ebp);
        port_call_with(&port, 0x4e66dc, esp, 0x512d14, port_u32(&port, record, 0x18), record,
                       entry->esi, entry->edi, entry->ebp);
        message = port_u32(&port, record, 0x14) == 0 ? 0x512d3c : 0x512d44;
        port_call_with(&port, 0x4e66dc, esp, message, 0, record, entry->esi, entry->edi,
                       entry->ebp);
    }
    else
    {
        if (message == 0)
        {
            port_call_with(&port, 0x4e66dc, esp, 0x512e4c, port_u32(&port, record, 0), record,
                           entry->esi, entry->edi, entry->ebp);
            message = 0x512e80;
        }
        port_call_with(&port, 0x4e66dc, esp, message, port_u32(&port, record, 0xc), record,
                       entry->esi, entry->edi, entry->ebp);
    }
    edx = vertrix_lift_edx;
    for (length = 0; port_u8(&port, esp, length) != 0 && !port.env.failed; length++)
    {
    }
    eax = port_u32(&port, 0, 0x507c8c);
    handle = port_u32(&port, eax, 8);
    args[0] = handle;
    args[1] = esp;
    args[2] = length;
    args[3] = esp + 0x100;
    args[4] = 0;
    vertrix_lift_in_esi = entry->esi;
    vertrix_lift_in_edi = esp + length + 1;
    vertrix_lift_in_ebp = entry->ebp;
    lift_call_arguments(&port.env, 0x4f1d08, eax, edx, handle, length, args, 5);
    vertrix_lift_in_esi = vertrix_lift_in_edi = vertrix_lift_in_ebp = 0;
    return port_return(&port, 1, vertrix_lift_edx);
}
