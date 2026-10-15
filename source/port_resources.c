#include "port_resources.h"

/* The stream's guarded read, the path's new extension, and the resource load by name. */

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

/* The pairwise text copy of the originals: the bytes from `source` to `target` up to the end;
 * esi is left past the last whole pair copied. */
static uint32_t text_copy(Port *port, uint32_t target, uint32_t source)
{
    uint32_t value;
    for (;;)
    {
        value = port_u8(port, source, 0);
        port_set8(port, target, 0, value);
        if (value == 0)
        {
            return source;
        }
        value = port_u8(port, source, 1);
        source += 2;
        port_set8(port, target, 1, value);
        target += 2;
        if (value == 0)
        {
            return source;
        }
    }
}

/* Original 0x489230: the stream eax's read of ecx items of ebx bytes into edx (0x4d7980) inside
 * an exception frame (0x4d93f0, 0x4d9f06; 0x4d9430 after): 1 when all were read, 0 when fewer
 * were or the read raised (the handler 0x4da6b6 on the frame's code ebp-0x10). */
uint32_t vertrix_port_stream_read_exact_489230(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x78
    };
    Port port;
    uint8_t stack[BELOW + 8];
    uint32_t ebp = entry->esp - 4;
    uint32_t stream = entry->eax;
    uint32_t size = entry->ebx * entry->ecx;
    uint32_t result = 1;
    uint32_t eax;
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, -0x24u, entry->edx);
    port_set32(&port, ebp, -0xcu, entry->ebx);
    port_set32(&port, ebp, -0x20u, entry->ecx);
    port_set32(&port, ebp, -0x40u, port.env.chain);
    port_set32(&port, ebp, -0x3cu, 0x4ec1ec);
    port_set32(&port, ebp, -0x38u, 0x517168);
    port_set32(&port, ebp, -0x34u, 0);
    port_set32(&port, ebp, -0x18u, 1);
    port_call_with(&port, 0x4d93f0, ebp - 0x2c, 0x4ec1ec, 0, 0x517168, stream, 1, ebp);
    port_set32(&port, ebp, -0x34u, 2);
    if (port_call_with(&port, 0x4d9f06, ebp - 0x74, vertrix_lift_edx, 0, 0x517168, stream, 1,
                       ebp) == 1)
    {
        port_set32(&port, ebp, -0x34u, 4);
        port_set32(&port, ebp, -0x28u, port_u32(&port, ebp, -0x10u));
        port_set32(&port, ebp, -0x18u, 0);
        eax = port_call_with(&port, 0x4da6b6, port_u32(&port, ebp, -0x10u), vertrix_lift_edx, 0, 4,
                             2, 1, ebp);
        port_set32(&port, ebp, -0x34u, 2);
        port_set32(&port, ebp, -0x34u, 0);
        port_call_with(&port, 0x4d9430, eax, vertrix_lift_edx, 0, 4, 2, 0, ebp);
        port_set32(&port, ebp, -0x34u, 0);
        result = 0;
    }
    else
    {
        eax = port_call_with(&port, 0x4d7980, stream, entry->edx, size, 0x517168, stream, 1, ebp);
        port_set32(&port, ebp, -0x14u, eax);
        port_set32(&port, ebp, -0x34u, 0);
        port_call_with(&port, 0x4d9430, eax, vertrix_lift_edx, size, 0x517168, stream, 0, ebp);
        port_set32(&port, ebp, -0x34u, 0);
        if (size != eax)
        {
            result = 0;
            port_set32(&port, ebp, -0x18u, 0);
        }
    }
    port_set32(&port, ebp, -0x1cu, result);
    return port_return(&port, result, vertrix_lift_edx);
}

/* Original 0x489ba0: the text [eax] is split (0x4daae8) into the drive 0x5bab10, folder 0x5bab18,
 * name 0x5bac18 and extension 0x5bad18 by way of 0x5baa08, and eax set to the drive (0x4ca370),
 * folder, name and the extension edx (0x4ca600). */
uint32_t vertrix_port_path_with_extension_489ba0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x1c
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t text = entry->eax;
    uint32_t esi;
    uint32_t args[1];
    uint32_t eax;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, -0x14u, text);
    port_set32(&port, ebp, -0x18u, entry->edx);
    esi = text_copy(&port, 0x5baa08, port_u32(&port, text, 0));
    args[0] = 0x5bad18;
    call_frame(&port, 0x4daae8, 0x5baa08, 0x5bab10, 0x5bab18, 0x5bac18, esi, 0x5baa08, ebp, args,
               1);
    port_call_with(&port, 0x4ca370, text, 0x5bab10, 0x5bab18, 0x5bac18, esi, 0x5baa08, ebp);
    port_call_with(&port, 0x4ca600, text, 0x5bab18, 0x5bab18, 0x5bac18, esi, 0x5baa08, ebp);
    port_call_with(&port, 0x4ca600, text, 0x5bac18, 0x5bab18, 0x5bac18, esi, 0x5baa08, ebp);
    eax = port_call_with(&port, 0x4ca600, text, entry->edx, 0x5bab18, 0x5bac18, esi, 0x5baa08, ebp);
    return port_return(&port, eax, vertrix_lift_edx);
}

/* The resource's data of `count` bytes: a block (0x478d10) into the resource eax, read from the
 * stream (0x489230) and taken in (0x48a8a0). */
static void resource_take(Port *port, uint32_t resource, uint32_t stream, uint32_t count,
                          uint32_t esi, uint32_t ebp)
{
    uint32_t block;
    block = port_call_with(port, 0x478d10, count, 1, 1, count, esi, resource, ebp);
    port_set32(port, resource, 0, block);
    port_call_with(port, 0x489230, stream, port_u32(port, block, 0), 1, count, esi, resource, ebp);
    port_call_with(port, 0x48a8a0, resource, vertrix_lift_edx, 1, count, esi, resource, ebp);
}

/* Original 0x48a710: the resource eax of the name edx: from the archive ebx when it holds the
 * name (0x488050; its entry 0x487fd0, size 0x488030, seek 0x488040), else from the file of the
 * name when it exists (0x4895e0; a stream of 16 bytes 0x4ca000, 0x488b10, opened 0x488c50, sized
 * 0x489a10, closed by the method +0x54 and destroyed by +4); the name, or 0x510ab9 when none was
 * read, is copied to +0xc. 1 when read, else 0. */
uint32_t vertrix_port_resource_load_48a710(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x34
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t resource = entry->eax;
    uint32_t name = entry->edx;
    uint32_t archive = entry->ebx;
    uint32_t ebx = 0;
    uint32_t ecx = 0x51765c;
    uint32_t esi = archive;
    uint32_t stream;
    uint32_t methods;
    uint32_t entry_index;
    uint32_t count;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, -0x10u, name);
    port_set32(&port, ebp, -0x30u, port.env.chain);
    port_set32(&port, ebp, -0x2cu, 0x4ec1ec);
    port_set32(&port, ebp, -0x28u, 0x51765c);
    port_set32(&port, ebp, -0x24u, 0);
    if (archive != 0)
    {
        if (port_call_with(&port, 0x488050, archive, name, 0, ecx, esi, resource, ebp) == 1)
        {
            entry_index =
                port_call_with(&port, 0x487fd0, archive, name, 0, ecx, esi, resource, ebp);
            port_set32(&port, ebp, -0x18u, entry_index);
            count =
                port_call_with(&port, 0x488030, archive, entry_index, 0, ecx, esi, resource, ebp);
            port_call_with(&port, 0x488040, archive, entry_index, 0, count, esi, resource, ebp);
            if (count != 0)
            {
                resource_take(&port, resource, archive, count, esi, ebp);
                ebx = 1;
            }
        }
    }
    else if (port_call_with(&port, 0x4895e0, name, 0x4ec1ec, 0, ecx, 0, resource, ebp) == 1)
    {
        stream = port_call_with(&port, 0x4ca000, 0x10, vertrix_lift_edx, 0, ecx, 0, resource, ebp);
        if (stream != 0)
        {
            port_set32(&port, ebp, -0x1cu, stream);
            port_set32(&port, ebp, -0x24u, 1);
            stream =
                port_call_with(&port, 0x488b10, stream, vertrix_lift_edx, 0, ecx, 1, resource, ebp);
            port_set32(&port, ebp, -0x24u, 0);
        }
        esi = stream;
        port_set32(&port, ebp, -0x14u, stream);
        if (port_call_with(&port, 0x488c50, stream, name, 0, ecx, esi, resource, ebp) == 1)
        {
            count = port_call_with(&port, 0x489a10, stream, vertrix_lift_edx, 0, ecx, esi, resource,
                                   ebp);
            ecx = count;
            if (count != 0)
            {
                resource_take(&port, resource, stream, count, esi, ebp);
                ebx = 1;
            }
            methods = port_u32(&port, stream, 0);
            port_call_with(&port, port_u32(&port, methods, 0x54), stream, methods, ebx, ecx, esi,
                           resource, ebp);
        }
        if (stream != 0)
        {
            methods = port_u32(&port, stream, 0);
            port_call_with(&port, port_u32(&port, methods, 4), stream, 2, ebx, methods, esi,
                           resource, ebp);
        }
        port_set32(&port, ebp, -0x24u, 0);
    }
    text_copy(&port, resource + 0xc, ebx == 1 ? name : 0x510ab9);
    return port_return(&port, ebx, vertrix_lift_edx);
}
