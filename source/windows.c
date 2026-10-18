#include "windows.h"

/* The decoder's range limit table, a window object's teardown, style, close, idle and command
 * routing, and the frame's view checks. */

/* Original 0x4c9030: the decoder's range limit table (0x7fc bytes from the pool method +0, its
 * middle +0x3fc into the dequantizer's +0x28): index i and -i hold i and -i below 16, then half
 * steps to 48 and the last value to 255. */
uint32_t vertrix_port_decoder_range_table_4c9030(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x20
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t info = entry->eax;
    uint32_t pool;
    uint32_t quantizer;
    uint32_t table;
    uint32_t index;
    uint32_t value;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    pool = port_u32(&port, info, 4);
    quantizer = port_u32(&port, info, 0x1cc);
    table = port_call_with(&port, port_u32(&port, pool, 0), info, 1, 0x7fc, pool, quantizer,
                           entry->edi, ebp) +
            0x3fc;
    port_set32(&port, quantizer, 0x28, table);
    value = 0;
    for (index = 0; index < 0x10; index++)
    {
        port_set32(&port, table, index * 4, value);
        port_set32(&port, table, -index * 4, -value);
        value++;
    }
    for (; index < 0x30; index++)
    {
        uint32_t odd;
        port_set32(&port, table, index * 4, value);
        port_set32(&port, table, -index * 4, -value);
        odd = ((index + 1) & 1) == 0;
        port_set8(&port, ebp, -0x18u, odd);
        value += odd;
    }
    for (; index <= 0xff; index++)
    {
        port_set32(&port, table, index * 4, value);
        port_set32(&port, ebp, -0x1cu, -value);
        port_set32(&port, table, -index * 4, -value);
    }
    return port_return(&port, index, entry->edx);
}

/* Original 0x4cb4f0: a window object's teardown by the flags dl: with bit 2 0x4ccb9f (0x518d30)
 * and 0x4ca040; otherwise (guarded 0x518c18) its methods 0x518cb4, its owned object (+0x10)
 * method +0x1c, the methods 0x517454 and, with bit 1, 0x4ca050. The object. */
uint32_t vertrix_port_window_object_teardown_4cb4f0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x38
    };
    Port port;
    uint32_t object = entry->eax;
    uint32_t flags = entry->edx;
    uint32_t local = entry->esp - 0x38;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    if ((flags & 4) != 0)
    {
        uint32_t result;
        port_set32(&port, local, 0x20, 1);
        port_set32(&port, local, 0, object);
        result = port_forward(&port, entry, 0x4ccb9f, object, 0x518d30, entry->ebx, object);
        port_set32(&port, local, 0x20, 0);
        port_forward(&port, entry, 0x4ca040, result, vertrix_lift_edx, entry->ebx, object);
        return port_return(&port, object, vertrix_lift_edx);
    }
    port_set32(&port, object, 0, 0x518cb4);
    port_set32(&port, local, 0x24, object);
    port_set8(&port, local, 0x28, flags);
    port_set32(&port, local, 0x14, port.env.chain);
    port_set32(&port, local, 0x18, 0x4ec1ec);
    port_set32(&port, local, 0x1c, 0x518c18);
    port_set32(&port, local, 0x20, 3);
    if (port_u32(&port, object, 0x10) != 0)
    {
        uint32_t owned = port_u32(&port, object, 0x10);
        port_forward(&port, entry, port_u32(&port, owned, 0x1c), object + 0x10, flags, owned,
                     object);
        flags = vertrix_lift_edx;
    }
    port_set32(&port, local, 0x20, 0);
    port_set32(&port, object, 0, 0x517454);
    if ((flags & 2) != 0)
    {
        port_forward(&port, entry, 0x4ca050, object, flags, entry->ebx, object);
        flags = vertrix_lift_edx;
    }
    return port_return(&port, object, flags);
}

/* Original 0x4cccc0: the window's style: the window's own method +0x74 (+0x38) or
 * GetWindowLong(+0x1c, GWL_STYLE). */
uint32_t vertrix_port_window_style_4cccc0(PORT_SIGNATURE)
{
    Port port;
    uint32_t window = entry->eax;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    if (port_u32(&port, window, 0x38) == 0)
    {
        uint32_t stack[2];
        stack[0] = port_u32(&port, window, 0x1c);
        stack[1] = 0xfffffff0u;
        result = port_forward_stack(&port, entry, 0x4f19f0, window, entry->edx, entry->ebx,
                                    entry->ecx, entry->esi, stack, 2);
        return port_return(&port, result, entry->edx);
    }
    {
        uint32_t site = port_u32(&port, window, 0x38);
        uint32_t methods = port_u32(&port, site, 0);
        result = port_forward(&port, entry, port_u32(&port, methods, 0x74), site, methods,
                              entry->ebx, entry->ecx);
    }
    return port_return(&port, result, entry->edx);
}

/* Original 0x4d0410: the window's close: with a handle (+0x1c) 0x4cf880 into the frame and
 * 0x4df140 on it, then the window's own method +0x54 (+0x38) or DestroyWindow; when 0x4df140
 * gave 0, 0x4cf980. The result, or 0 without a handle. */
uint32_t vertrix_port_window_close_4d0410(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x14
    };
    Port port;
    uint32_t window = entry->eax;
    uint32_t local = entry->esp - 0x14;
    uint32_t found;
    uint32_t result;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    if (port_u32(&port, window, 0x1c) == 0)
    {
        return port_return(&port, 0, entry->edx);
    }
    result = port_forward_esi(&port, entry, 0x4cf880, 0, entry->edx, local, entry->ecx, window);
    found = port_forward_esi(&port, entry, 0x4df140, result, port_u32(&port, window, 0x1c), local,
                             entry->ecx, window);
    if (port_u32(&port, window, 0x38) == 0)
    {
        uint32_t stack[1];
        stack[0] = port_u32(&port, window, 0x1c);
        result = port_forward_stack(&port, entry, 0x4f1938, found, vertrix_lift_edx, found,
                                    entry->ecx, window, stack, 1);
    }
    else
    {
        uint32_t site = port_u32(&port, window, 0x38);
        uint32_t methods = port_u32(&port, site, 0);
        result = port_forward_esi(&port, entry, port_u32(&port, methods, 0x54), site, methods,
                                  found, entry->ecx, window);
    }
    if (found == 0)
    {
        port_forward_esi(&port, entry, 0x4cf980, window, result, 0, entry->ecx, window);
    }
    return port_return(&port, result, entry->edx);
}

/* Original 0x4d41c0: the frame's idle: 1 when its view (+0x68) method +0x74 holds, otherwise
 * 0x4cf850 on the object the edx left gives. */
uint32_t vertrix_port_frame_view_idle_4d41c0(PORT_SIGNATURE)
{
    Port port;
    uint32_t edx = entry->eax;
    uint32_t ecx = entry->ecx;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    if (port_u32(&port, edx, 0x68) != 0)
    {
        uint32_t view = port_u32(&port, edx, 0x68);
        ecx = port_u32(&port, view, 0);
        if (port_forward(&port, entry, port_u32(&port, ecx, 0x74), view, edx, entry->ebx, ecx) != 0)
        {
            return port_return(&port, 1, entry->edx);
        }
        edx = vertrix_lift_edx;
    }
    result = port_forward(&port, entry, 0x4cf850, edx, edx, entry->ebx, ecx);
    return port_return(&port, result, entry->edx);
}

/* Original 0x4d5010: the window's system command edx: with the application (0x4d1930) in help
 * mode (+0x50) the commands 0xf000 to 0xf060 and 0xf120, 0xf130 send 0x365 with their help id
 * (0x1ef00 + (command - 0xf000) / 16, falling back to 0x111 with 0xe147); otherwise 0x4cf850. */
uint32_t vertrix_port_window_system_command_4d5010(PORT_SIGNATURE)
{
    Port port;
    uint32_t window = entry->eax;
    uint32_t command = entry->edx;
    uint32_t application;
    uint32_t masked;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    application =
        port_forward_esi(&port, entry, 0x4d1930, window, command, entry->ebx, command, window);
    masked = command & 0xfff0;
    if (port_u32(&port, application, 0x50) != 0 &&
        (masked == 0xf000 || masked == 0xf010 || masked == 0xf020 || masked == 0xf030 ||
         masked == 0xf040 || masked == 0xf050 || masked == 0xf060 || masked == 0xf120 ||
         masked == 0xf130))
    {
        uint32_t stack[4];
        uint32_t help = ((masked - 0xf000) >> 4) + 0x1ef00;
        stack[0] = port_u32(&port, window, 0x1c);
        stack[1] = 0x365;
        stack[2] = 0;
        stack[3] = help;
        result = port_forward_stack(&port, entry, 0x4f1a94, help, application, entry->ebx, command,
                                    window, stack, 4);
        if (result != 0)
        {
            return port_return(&port, result, vertrix_lift_edx);
        }
        stack[0] = port_u32(&port, window, 0x1c);
        stack[1] = 0x111;
        stack[2] = 0xe147;
        stack[3] = 0;
        result = port_forward_stack(&port, entry, 0x4f1a94, 0, vertrix_lift_edx, entry->ebx,
                                    command, window, stack, 4);
        return port_return(&port, result, vertrix_lift_edx);
    }
    result =
        port_forward_esi(&port, entry, 0x4cf850, window, application, entry->ebx, command, window);
    return port_return(&port, result, vertrix_lift_edx);
}

/* Original 0x4d63d0: when the frame's method +0xd4 holds, the +0x78 of the object the edx left
 * gives; otherwise whether its view (+0x70) has +0x78 set. */
uint32_t vertrix_port_frame_view_flag_4d63d0(PORT_SIGNATURE)
{
    Port port;
    uint32_t frame = entry->eax;
    uint32_t methods;
    uint32_t edx;
    uint32_t view;
    port_open(&port, calls, services, globals, entry);
    methods = port_u32(&port, frame, 0);
    if (port_forward(&port, entry, port_u32(&port, methods, 0xd4), frame, frame, entry->ebx,
                     methods) != 0)
    {
        return port_return(&port, port_u32(&port, vertrix_lift_edx, 0x78), entry->edx);
    }
    edx = vertrix_lift_edx;
    view = port_u32(&port, edx, 0x70);
    if (view == 0 || port_u32(&port, view, 0x78) == 0)
    {
        return port_return(&port, 0, entry->edx);
    }
    return port_return(&port, 1, entry->edx);
}
