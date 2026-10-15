#include "port_rtlfiles.h"

/* The runtime library's file opens. */

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

/* Original 0x4d77d0: the file object eax opens the path edx with the flags ebx, reporting into
 * the exception ecx. It starts closed (+8 0, handle +4 -1); the full path (0x4ca180 on its name
 * +0xc, 0x4d7c40 into the frame) becomes its name (0x4ca370). The access (read, write, both; a
 * mode 3 leaves the frame's), sharing (by the bits 0x70; others leave the frame's), inheritance
 * (not 0x80) and creation (0x1000: 2, with 0x2000 4; else 3) open it (0x4f1b34, normal
 * attributes). A failure gives 0, filling the exception's error +0xc (0x4f1bbc), cause +8
 * (0x4d9ae0) and name +0x10; success keeps the handle, marks it open and gives 1. */
uint32_t vertrix_port_rtl_file_open_4d77d0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x12c
    };
    Port port;
    uint8_t stack[BELOW + 8];
    uint32_t esp = entry->esp - 0x12c;
    uint32_t file = entry->eax;
    uint32_t path = entry->edx;
    uint32_t error = entry->ecx;
    uint32_t flags;
    uint32_t mode;
    uint32_t share;
    uint32_t creation;
    uint32_t handle;
    uint32_t eax;
    uint32_t args[7];
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    port_set32(&port, esp, 0x11c, entry->ebx);
    port_set32(&port, file, 8, 0);
    port_set32(&port, file, 4, 0xffffffffu);
    port_set32(&port, esp, 0x110, file + 0xc);
    port_call_with(&port, 0x4ca180, file + 0xc, path, error, entry->ecx, file, path, entry->ebp);
    flags = port_u32(&port, esp, 0x11c);
    port_set8(&port, esp, 0x11d, port_u8(&port, esp, 0x11d) & 0x7f);
    args[0] = esp;
    args[1] = vertrix_lift_edx;
    call_frame(&port, 0x4d7c40, esp, vertrix_lift_edx, error, entry->ecx, file, path, flags, args,
               2);
    mode = flags & 3;
    port_call_with(&port, 0x4ca370, port_u32(&port, esp, 0x110), esp, error, entry->ecx, file, path,
                   mode);
    if (mode == 0)
    {
        port_set32(&port, esp, 0x114, 0x80000000u);
    }
    else if (mode == 1)
    {
        port_set32(&port, esp, 0x114, 0x40000000u);
    }
    else if (mode == 2)
    {
        port_set32(&port, esp, 0x114, 0xc0000000u);
    }
    share = port_u32(&port, esp, 0x11c) & 0x70;
    if (share == 0 || share == 0x10)
    {
        port_set32(&port, esp, 0x118, 0);
    }
    else if (share == 0x20)
    {
        port_set32(&port, esp, 0x118, 1);
    }
    else if (share == 0x30)
    {
        port_set32(&port, esp, 0x118, 2);
    }
    else if (share == 0x40)
    {
        port_set32(&port, esp, 0x118, 3);
    }
    port_set32(&port, esp, 0x104, 0xc);
    port_set32(&port, esp, 0x108, 0);
    port_set32(&port, esp, 0x10c, (port_u8(&port, esp, 0x11c) & 0x80) == 0);
    if (port_u8(&port, esp, 0x11d) & 0x10)
    {
        creation = port_u8(&port, esp, 0x11d) & 0x20 ? 4 : 2;
    }
    else
    {
        creation = 3;
    }
    args[0] = path;
    args[1] = port_u32(&port, esp, 0x114);
    args[2] = port_u32(&port, esp, 0x118);
    args[3] = esp + 0x104;
    args[4] = creation;
    args[5] = 0x80;
    args[6] = 0;
    handle = call_frame(&port, 0x4f1b34, esp + 0x104, vertrix_lift_edx, error, entry->ecx, file,
                        path, mode, args, 7);
    if (handle != 0xffffffffu)
    {
        port_set32(&port, file, 8, 1);
        port_set32(&port, file, 4, handle);
        return port_return(&port, 1, vertrix_lift_edx);
    }
    if (error != 0)
    {
        eax = call_frame(&port, 0x4f1bbc, handle, vertrix_lift_edx, error, entry->ecx, file, path,
                         mode, args, 0);
        port_set32(&port, error, 0xc, eax);
        args[0] = eax;
        eax = call_frame(&port, 0x4d9ae0, eax, vertrix_lift_edx, error, entry->ecx, file, path,
                         mode, args, 1);
        port_set32(&port, error, 8, eax);
        port_call_with(&port, 0x4ca370, error + 0x10, path, error, entry->ecx, file, path, mode);
    }
    return port_return(&port, 0, vertrix_lift_edx);
}
