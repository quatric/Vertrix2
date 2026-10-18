#include "runtimepaths.h"

/* The C runtime's signal raise, full path name and stream open. */

static uint32_t call_frame(Port *port, uint32_t target, uint32_t eax, uint32_t edx, uint32_t ebx,
                           uint32_t ecx, uint32_t esi, uint32_t edi, uint32_t ebp,
                           const uint32_t *stack, unsigned count)
{
    return port_call_registers(port, target, eax, edx, ebx, ecx, esi, edi, ebp, stack, count);
}

/* Original 0x4e8bd4: the signal raise of SIGINT (2) with the code in eax: the handler (0x4e8a58)
 * being 1, 2 or 3 gives -1; otherwise the handler is reset (0x4e8a10) and called with 2 and the
 * code, giving 0. */
uint32_t vertrix_port_signal_raise_4e8bd4(PORT_SIGNATURE)
{
    Port port;
    uint32_t code = entry->eax;
    uint32_t handler;
    port_open(&port, calls, services, globals, entry);
    handler = port_call_with(&port, 0x4e8a58, 2, entry->edx, code, entry->ecx, entry->esi,
                             entry->edi, entry->ebp);
    if (handler == 1 || handler == 2 || handler == 3)
    {
        return port_return(&port, 0xffffffffu, entry->edx);
    }
    port_call_with(&port, 0x4e8a10, 2, 2, code, handler, entry->esi, entry->edi, entry->ebp);
    port_call_with(&port, handler, 2, code, code, handler, entry->esi, entry->edi, entry->ebp);
    return port_return(&port, 0, entry->edx);
}

/* Original 0x4ea470: the full path name of edx into the buffer eax of ebx bytes: no buffer is one
 * of 0x104 bytes (0x4e7c90), its failure error 5 (0x4dae70) and 0; no name or an empty one is the
 * current directory (0x4e3ac0); a name 0x5130dc (0x4e09f0) is copied in when the buffer holds 4
 * bytes, else the made buffer is freed (0x4ea190) and error 14 given with 0; otherwise
 * GetFullPathName (slot 0x4f1bb8), its failure setting the error (0x4e0884) with 0. The buffer. */
uint32_t vertrix_port_full_path_4ea470(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x10
    };
    Port port;
    uint32_t part = entry->esp - BELOW;
    uint32_t buffer = entry->eax;
    uint32_t name = entry->edx;
    uint32_t size = entry->ebx;
    uint32_t made = entry->edi;
    uint32_t edx = entry->edx;
    uint32_t eax;
    uint32_t args[4];
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    if (buffer == 0)
    {
        size = 0x104;
        made = port_call_with(&port, 0x4e7c90, size, edx, size, name, 0, made, entry->ebp);
        if (made == 0)
        {
            port_call_with(&port, 0x4dae70, 5, vertrix_lift_edx, size, name, 0, 0, entry->ebp);
            return port_return(&port, 0, vertrix_lift_edx);
        }
        buffer = made;
    }
    if (name == 0 || port_u8(&port, name, 0) == 0)
    {
        eax = port_call_with(&port, 0x4e3ac0, buffer, size, size, name, buffer, made, entry->ebp);
        return port_return(&port, eax, vertrix_lift_edx);
    }
    eax = port_call_with(&port, 0x4e09f0, name, 0x5130dc, size, name, buffer, made, entry->ebp);
    if (eax == 0)
    {
        if (size < 4)
        {
            port_call_with(&port, 0x4ea190, made, vertrix_lift_edx, size, name, buffer, made,
                           entry->ebp);
            port_call_with(&port, 0x4dae70, 0xe, vertrix_lift_edx, size, name, buffer, made,
                           entry->ebp);
            return port_return(&port, 0, vertrix_lift_edx);
        }
        port_set32(&port, buffer, 0, port_u32(&port, 0, 0x5130dc));
        return port_return(&port, buffer, vertrix_lift_edx);
    }
    args[0] = name;
    args[1] = size;
    args[2] = buffer;
    args[3] = part;
    eax = call_frame(&port, 0x4f1bb8, part, vertrix_lift_edx, size, name, buffer, made, entry->ebp,
                     args, 4);
    if (eax == 0)
    {
        port_call_with(&port, 0x4e0884, 0, vertrix_lift_edx, size, name, buffer, made, entry->ebp);
        return port_return(&port, 0, vertrix_lift_edx);
    }
    return port_return(&port, buffer, vertrix_lift_edx);
}

/* Original 0x4eba4c: the stream open of the path eax with the mode letter dl and the flags ebx
 * into the stream of the second stack word: the flags go into +0xc; the letter's kind (0x4e82f0)
 * 'r' opens (0x4cd544) for reading (2 when bit 1, ored 0x200 when bit 0x40 else 0x100) with no
 * permission, any other with 0x21 plus bit 0, ored 0x10 when bit 0x80 else 0x40 and the same
 * high bits, with permission 0x180, the share being the first stack word. A failed open
 * releases the stream (0x4e7e44) with 0; otherwise the stream's counts are cleared, the buffer
 * record given the lift edx, an append stream seeks to its end (0x4ebce8), and the stream is
 * finished (0x4e7bf0) and returned. ret 8. */
uint32_t vertrix_port_stream_open_4eba4c(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0xc
    };
    Port port;
    uint8_t stack[BELOW + 8 + 8];
    uint32_t path = entry->eax;
    uint32_t flags = entry->ebx;
    uint32_t stream;
    uint32_t share;
    uint32_t mode;
    uint32_t permission;
    uint32_t edi = entry->edi;
    uint32_t ebp = entry->ebp;
    uint32_t handle;
    uint32_t record;
    uint32_t args[4];
    port_open_arguments(&port, stack, calls, services, globals, entry, BELOW, 2);
    share = port_u32(&port, entry->esp, 4);
    stream = port_u32(&port, entry->esp, 8);
    port_set8(&port, stream, 0xc, port_u8(&port, stream, 0xc) & 0xfc);
    port_set32(&port, stream, 0xc, port_u32(&port, stream, 0xc) | flags);
    mode = port_call_with(&port, 0x4e82f0, entry->edx & 0xff, entry->ecx, flags, stream, path, edi,
                          ebp);
    if ((mode & 0xff) == 0x72)
    {
        mode = (flags & 2) != 0 ? 2 : 0;
        permission = 0;
        edi = share;
    }
    else
    {
        mode = 0x21 + ((flags & 1) != 0 ? 1 : 0);
        mode |= (flags & 0x80) != 0 ? 0x10 : 0x40;
        permission = 0x180;
        ebp = share;
    }
    mode |= (flags & 0x40) != 0 ? 0x200 : 0x100;
    args[0] = path;
    args[1] = mode;
    args[2] = share;
    args[3] = permission;
    handle =
        call_frame(&port, 0x4cd544, mode, vertrix_lift_edx, flags, stream, path, edi, ebp, args, 4);
    port_set32(&port, stream, 0x10, handle);
    if (port_u32(&port, stream, 0x10) == 0xffffffffu)
    {
        port_call_with(&port, 0x4e7e44, stream, vertrix_lift_edx, flags, stream, path, edi, ebp);
        return port_return(&port, 0, vertrix_lift_edx);
    }
    port_set32(&port, stream, 4, 0);
    record = port_u32(&port, stream, 8);
    port_set32(&port, stream, 0x14, 0);
    port_set32(&port, record, 0xc, 0);
    port_set32(&port, port_u32(&port, stream, 8), 0x10, vertrix_lift_edx);
    port_set32(&port, port_u32(&port, stream, 8), 0x15, 0);
    port_set32(&port, port_u32(&port, stream, 8), 8, 0);
    if ((flags & 0x80) != 0)
    {
        flags = 2;
        port_call_with(&port, 0x4ebce8, stream, 0, flags, stream, path, edi, ebp);
    }
    port_call_with(&port, 0x4e7bf0, stream, vertrix_lift_edx, flags, stream, path, edi, ebp);
    return port_return(&port, stream, vertrix_lift_edx);
}
