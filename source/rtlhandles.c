#include "rtlhandles.h"

/* The runtime library's handle reads. */

static uint32_t call_frame(Port *port, uint32_t target, uint32_t eax, uint32_t edx, uint32_t ebx,
                           uint32_t ecx, uint32_t esi, uint32_t edi, uint32_t ebp,
                           const uint32_t *stack, unsigned count)
{
    return port_call_registers(port, target, eax, edx, ebx, ecx, esi, edi, ebp, stack, count);
}

/* Original 0x4ec3e0: read ebx bytes into edx from the file number eax. A number past 0x507c34 is
 * error 4 (0x4dae70) and -1. Under the lock (0x507ca0, 0x507ca4) a file the hook 0x507cfc claims
 * is read by 0x507d24 (eax the unlock's edx); else its handle (0x507c8c's table) goes to
 * 0x4f1c78, a failure giving 0x4e0884's eax and success the count read. */
uint32_t vertrix_port_rtl_handle_read_4ec3e0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0xc
    };
    Port port;
    uint8_t stack[BELOW + 8];
    uint32_t esp = entry->esp - 0xc;
    uint32_t file = entry->eax;
    uint32_t eax;
    uint32_t edx;
    uint32_t handle;
    uint32_t unlocked;
    uint32_t args[5];
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    port_set32(&port, esp, 8, entry->ecx);
    port_set32(&port, esp, 4, entry->esi);
    if ((int32_t)file < 0 || file > port_u32(&port, 0, 0x507c34))
    {
        port_call_with(&port, 0x4dae70, 4, entry->edx, entry->ebx, entry->ecx, file, entry->edi,
                       entry->ebp);
        return port_return(&port, 0xffffffffu, vertrix_lift_edx);
    }
    port_call_with(&port, port_u32(&port, 0, 0x507ca0), file, entry->edx, entry->ebx, entry->ecx,
                   file, entry->edi, entry->ebp);
    edx = vertrix_lift_edx;
    if (port_u32(&port, 0, 0x507d24) != 0)
    {
        eax = port_call_with(&port, port_u32(&port, 0, 0x507cfc), file, edx, entry->ebx, entry->ecx,
                             file, entry->edi, entry->ebp);
        edx = vertrix_lift_edx;
        if (eax != 0)
        {
            edx = port_call_with(&port, port_u32(&port, 0, 0x507d24), eax, edx, entry->ebx,
                                 entry->ecx, file, entry->edi, entry->ebp);
            port_call_with(&port, port_u32(&port, 0, 0x507ca4), file, edx, entry->ebx, entry->ecx,
                           file, entry->edi, entry->ebp);
            return port_return(&port, vertrix_lift_edx, vertrix_lift_edx);
        }
    }
    handle = port_u32(&port, port_u32(&port, 0, 0x507c8c), file * 4);
    args[0] = handle;
    args[1] = edx;
    args[2] = entry->ebx;
    args[3] = esp;
    args[4] = 0;
    eax = call_frame(&port, 0x4f1c78, handle, edx, entry->ebx, esp, file, entry->edi, entry->ebp,
                     args, 5);
    edx = vertrix_lift_edx;
    unlocked = port_call_with(&port, port_u32(&port, 0, 0x507ca4), file, edx, entry->ebx, esp, file,
                              entry->edi, entry->ebp);
    if (eax == 0)
    {
        args[0] = port_u32(&port, esp, 0);
        eax = call_frame(&port, 0x4e0884, unlocked, vertrix_lift_edx, entry->ebx, esp, file,
                         entry->edi, entry->ebp, args, 1);
        return port_return(&port, eax, vertrix_lift_edx);
    }
    return port_return(&port, port_u32(&port, esp, 0), vertrix_lift_edx);
}
