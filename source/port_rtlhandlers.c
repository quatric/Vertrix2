#include "port_rtlhandlers.h"

/* The runtime library's exception handlers. */

/* The registers the handler carries between its calls. */
typedef struct
{
    uint32_t eax;
    uint32_t edx;
    uint32_t ebx;
    uint32_t ecx;
} HandlerRegs;

/* A call of `target` with `count` stack arguments (nearest first); eax and edx take the call's. */
static uint32_t handler_call(Port *port, const LiftEntry *entry, HandlerRegs *regs, uint32_t target,
                             uint32_t esi, uint32_t edi, const uint32_t *stack, unsigned count)
{
    vertrix_lift_in_esi = esi;
    vertrix_lift_in_edi = edi;
    vertrix_lift_in_ebp = entry->ebp;
    regs->eax = lift_call_arguments(&port->env, target, regs->eax, regs->edx, regs->ebx, regs->ecx,
                                    stack, count);
    vertrix_lift_in_esi = vertrix_lift_in_edi = vertrix_lift_in_ebp = 0;
    regs->edx = vertrix_lift_edx;
    return regs->eax;
}

/* The run-time error for the invalid operation at the context `context`'s faulting instruction
 * (+0x28): 0x88 or 0x8e for two opcodes, 0x8d for an integer store, 0x83 when a register operand
 * is empty by the tag word (+0x24, the top +0x20), else 0x81; the registers as the test leaves
 * them. */
static uint32_t invalid_operation(Port *port, HandlerRegs *regs, uint32_t context)
{
    uint32_t place = port_u32(port, context, 0x28);
    uint32_t error = 0x81;
    uint32_t opcode = port_u8(port, place, 0);
    regs->eax = place;
    regs->edx = (regs->edx & 0xffff0000u) | port_u16(port, place, 0);
    if ((regs->edx & 0xffff) == 0xfad9)
    {
        return 0x88;
    }
    if ((regs->edx & 0xffff) == 0xf1d9)
    {
        return 0x8e;
    }
    regs->edx = (regs->edx & 0xffff00ffu) | (opcode << 8);
    if (opcode == 0xdb || opcode == 0xdf)
    {
        regs->edx = (regs->edx & 0xffffff00u) | (port_u8(port, place, 1) & 0x30);
        if ((regs->edx & 0xff) == 0x10)
        {
            error = 0x8d;
        }
    }
    if ((port_u8(port, place, 0) & 1) == 0)
    {
        regs->eax = (regs->eax & 0xffffff00u) | (port_u8(port, place, 1) & 0x30);
        if ((regs->eax & 0xff) == 0x30)
        {
            regs->eax = (port_u32(port, context, 0x20) & 0xffff) << 2;
            regs->eax = (regs->eax & 0xffff0000u) | ((regs->eax & 0xffff) >> 13);
            regs->ecx = (regs->eax & 0xffff) * 2;
            regs->edx = ((port_u32(port, context, 0x24) & 0xffff) >> (regs->ecx & 31)) & 1;
            if (regs->edx == 1)
            {
                error = 0x83;
            }
        }
    }
    return error;
}

/* Original 0x4e6918: the exception handler for the record and context (stack arguments one and
 * three). An unwind is left (1). A floating point fault (0xc000008d..0xc0000093) becomes its
 * run-time error, raised (0x4e8a00, 0x4e8bd4 with 0x5c8a74 set) and resumed with the control
 * word's exception bits cleared (0) unless refused; other codes go to the hooks 0x5097ec (asked
 * for the classes 1..12) and 0x5097f0 (0 when it resumes). What is left goes to 0x4f1ce4, whose
 * acceptance ends the program (0x4f1b4c with -1); eax 1. */
uint32_t vertrix_port_rtl_exception_handler_4e6918(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x14
    };
    Port port;
    uint8_t stack[BELOW + 8 + 12];
    uint32_t esp = entry->esp - 0x14;
    uint32_t record;
    uint32_t context;
    uint32_t index;
    uint32_t args[1];
    HandlerRegs regs;
    port_open_arguments(&port, stack, calls, services, globals, entry, BELOW, 3);
    port_set32(&port, esp, 0x10, entry->ebx);
    port_set32(&port, esp, 0xc, entry->esi);
    port_set32(&port, esp, 8, entry->edi);
    record = port_u32(&port, entry->esp, 4);
    context = port_u32(&port, entry->esp, 0xc);
    regs.edx = entry->edx;
    regs.ebx = entry->ebx;
    regs.ecx = entry->ecx;
    if ((port_u8(&port, record, 4) & 6) != 0)
    {
        return port_return(&port, 1, regs.edx);
    }
    index = port_u32(&port, record, 0) + 0x3fffff73u;
    regs.eax = index;
    if (index <= 6)
    {
        switch (index)
        {
            case 0:
                regs.ebx = 0x82;
                break;
            case 1:
                regs.ebx = 0x83;
                break;
            case 2:
                regs.ebx = 0x86;
                break;
            case 3:
                regs.ebx = invalid_operation(&port, &regs, context);
                break;
            case 4:
                regs.ebx = 0x84;
                break;
            case 5:
                regs.ebx = (port_u8(&port, context, 0x21) & 2) != 0 ? 0x8a : 0x8b;
                break;
            default:
                regs.ebx = 0x85;
                break;
        }
        port_set8(&port, 0, 0x5c8a74, 1);
        handler_call(&port, entry, &regs, 0x4e8a00, record, context, args, 0);
        regs.eax = regs.ebx;
        if (handler_call(&port, entry, &regs, 0x4e8bd4, record, context, args, 0) != 0xffffffffu &&
            port_u8(&port, 0, 0x5c8a74) != 0)
        {
            regs.ebx = (regs.ebx & 0xffff0000u) | (port_u16(&port, context, 0x20) & 0x7f00);
            port_set16(&port, context, 0x20, regs.ebx);
            return port_return(&port, 0, regs.edx);
        }
    }
    else if (port_u32(&port, 0, 0x5097f0) != 0)
    {
        regs.ebx = 1;
        regs.ecx = 1;
        do
        {
            regs.eax = regs.ebx;
            regs.edx = port_u32(&port, record, 0);
            handler_call(&port, entry, &regs, port_u32(&port, 0, 0x5097ec), record, context, args,
                         0);
            if (regs.eax != 0)
            {
                if (regs.eax <= 3)
                {
                    break;
                }
                regs.eax = regs.ebx;
                port_set8(&port, 0, 0x5c8a74, regs.ecx);
                handler_call(&port, entry, &regs, port_u32(&port, 0, 0x5097f0), record, context,
                             args, 0);
                if (port_u8(&port, 0, 0x5c8a74) != 0)
                {
                    return port_return(&port, 0, regs.edx);
                }
            }
            regs.ebx++;
        } while ((int32_t)regs.ebx <= 0xc && !port.env.failed);
    }
    regs.eax = esp;
    port_set32(&port, esp, 0, record);
    port_set32(&port, esp, 4, context);
    args[0] = esp;
    if (handler_call(&port, entry, &regs, 0x4f1ce4, record, context, args, 1) != 0)
    {
        args[0] = 0xffffffffu;
        handler_call(&port, entry, &regs, 0x4f1b4c, record, context, args, 1);
    }
    return port_return(&port, 1, regs.edx);
}
