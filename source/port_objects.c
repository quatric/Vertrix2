#include "port_objects.h"

/* Object pair, cursor, release and init helpers. */

/* A call handing the callee esi and edi as given and the caller's ebp. */
static uint32_t call_registers(Port *port, const LiftEntry *entry, uint32_t target, uint32_t eax,
                               uint32_t edx, uint32_t ebx, uint32_t ecx, uint32_t esi, uint32_t edi)
{
    uint32_t result;
    vertrix_lift_in_esi = esi;
    vertrix_lift_in_edi = edi;
    vertrix_lift_in_ebp = entry->ebp;
    result = lift_call_arguments(&port->env, target, eax, edx, ebx, ecx, NULL, 0);
    vertrix_lift_in_esi = vertrix_lift_in_edi = vertrix_lift_in_ebp = 0;
    return result;
}

/* Original 0x4b4150: with +0x124 1 and 0x4adfb0 giving 1, 0x4b3340 and method +8 of the children
 * +0x17c and +0x180 with edx. */
uint32_t vertrix_port_pair_children_show_4b4150(PORT_SIGNATURE)
{
    Port port;
    uint32_t object = entry->eax;
    uint32_t state;
    uint32_t child;
    uint32_t first;
    uint32_t second;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    state = port_u32(&port, object, 0x124);
    if (state != 1)
    {
        return port_return(&port, state, entry->edx);
    }
    result = port_forward(&port, entry, 0x4adfb0, object, entry->edx, entry->edx, object);
    if (result != 1)
    {
        return port_return(&port, result, vertrix_lift_edx);
    }
    port_forward(&port, entry, 0x4b3340, object, vertrix_lift_edx, entry->edx, object);
    child = port_u32(&port, object, 0x17c);
    first = port_u32(&port, child, 0x158);
    call_registers(&port, entry, port_u32(&port, first, 8), child, entry->edx, entry->edx, object,
                   first, entry->edi);
    child = port_u32(&port, object, 0x180);
    second = port_u32(&port, child, 0x158);
    result = call_registers(&port, entry, port_u32(&port, second, 8), child, entry->edx, entry->edx,
                            second, first, entry->edi);
    return port_return(&port, result, vertrix_lift_edx);
}

/* Original 0x4b41a0: with +0x124 0, 0x4b3340 and method +8 of the children +0x17c and +0x180
 * with edx. */
uint32_t vertrix_port_pair_children_hide_4b41a0(PORT_SIGNATURE)
{
    Port port;
    uint32_t object = entry->eax;
    uint32_t state;
    uint32_t child;
    uint32_t first;
    uint32_t second;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    state = port_u32(&port, object, 0x124);
    if (state != 0)
    {
        return port_return(&port, state, entry->edx);
    }
    port_forward(&port, entry, 0x4b3340, object, entry->edx, object, entry->edx);
    child = port_u32(&port, object, 0x17c);
    first = port_u32(&port, child, 0x158);
    call_registers(&port, entry, port_u32(&port, first, 8), child, entry->edx, object, entry->edx,
                   first, entry->edi);
    child = port_u32(&port, object, 0x180);
    second = port_u32(&port, child, 0x158);
    result = call_registers(&port, entry, port_u32(&port, second, 8), child, entry->edx, second,
                            entry->edx, first, entry->edi);
    return port_return(&port, result, vertrix_lift_edx);
}

/* Original 0x4b4690: hold the cursor +0x170 within the text of the partner +0x160 (+0x15c): -1
 * below -1, the last index past it. */
uint32_t vertrix_port_object_cursor_clamp_4b4690(PORT_SIGNATURE)
{
    Port port;
    uint32_t object = entry->eax;
    uint32_t text;
    uint32_t length = 0;
    uint32_t cursor;
    port_open(&port, calls, services, globals, entry);
    text = port_u32(&port, port_u32(&port, object, 0x160), 0x15c);
    while (port_u8(&port, text, length) != 0)
    {
        length++;
    }
    cursor = port_u32(&port, object, 0x170);
    if ((int32_t)cursor < -1)
    {
        port_set32(&port, object, 0x170, 0xffffffffu);
    }
    else if ((int32_t)length <= (int32_t)cursor)
    {
        port_set32(&port, object, 0x170, length - 1);
    }
    return port_return(&port, 0, entry->edx);
}

/* Original 0x4b6020: release the resource +0xb4 of each item of the list eax (count +8, items +4)
 * by 0x4830f0 and clear it (at the edx the call leaves). */
uint32_t vertrix_port_object_release_items_4b6020(PORT_SIGNATURE)
{
    Port port;
    uint32_t list = entry->eax;
    uint32_t count;
    uint32_t index;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    count = port_u32(&port, list, 8);
    result = count;
    for (index = 0; index < count; index++)
    {
        uint32_t item = port_u32(&port, port_u32(&port, list, 4), index * 4);
        result = port_u32(&port, item, 0xb4);
        if (result != 0)
        {
            result =
                call_registers(&port, entry, 0x4830f0, result, item, index * 4, index, list, count);
            port_set32(&port, vertrix_lift_edx, 0xb4, 0);
        }
    }
    return port_return(&port, result, entry->edx);
}

/* Original 0x4b9d70: the state +0x1c of the view +0x1ac: 1 past the first frame (+0x148 over 1),
 * otherwise +0x48 of the source +0x14c on its last frame (+0x94 at +0x140 less 1 or more) or its
 * +0xc; +0x14 and +0x18 cleared. */
uint32_t vertrix_port_view_frame_state_4b9d70(PORT_SIGNATURE)
{
    Port port;
    uint32_t object = entry->eax;
    uint32_t view;
    uint32_t result = object;
    port_open(&port, calls, services, globals, entry);
    view = port_u32(&port, object, 0x1ac);
    if ((int32_t)port_u32(&port, object, 0x148) > 1)
    {
        port_set32(&port, view, 0x1c, 1);
    }
    else
    {
        uint32_t source = port_u32(&port, object, 0x14c);
        if (port_u32(&port, object, 0x140) - 1 <= port_u32(&port, object, 0x94))
        {
            result = port_u32(&port, source, 0x48);
        }
        else
        {
            result = port_u32(&port, source, 0xc);
        }
        port_set32(&port, view, 0x1c, result);
    }
    port_set32(&port, view, 0x14, 0);
    port_set32(&port, view, 0x18, 0);
    return port_return(&port, result, entry->edx);
}

/* Original 0x4bd1c0: the state record +0x1b4 reset (handler 0x4bcea0, +0x10 and +0x14 0, +0x18
 * 1); then method +0x10, the method of +0x1b8 and +0xa0 cleared (the object the edx each call
 * leaves). */
uint32_t vertrix_port_object_state_reset_4bd1c0(PORT_SIGNATURE)
{
    Port port;
    uint32_t object = entry->eax;
    uint32_t record;
    uint32_t methods;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    record = port_u32(&port, object, 0x1b4);
    port_set32(&port, record, 0, 0x4bcea0);
    port_set32(&port, record, 0x10, 0);
    port_set32(&port, record, 0x14, 0);
    port_set32(&port, record, 0x18, 1);
    methods = port_u32(&port, object, 0);
    port_forward(&port, entry, port_u32(&port, methods, 0x10), object, object, entry->ebx, methods);
    object = vertrix_lift_edx;
    methods = port_u32(&port, object, 0x1b8);
    result = port_forward(&port, entry, port_u32(&port, methods, 0), object, object, entry->ebx,
                          methods);
    port_set32(&port, vertrix_lift_edx, 0xa0, 0);
    return port_return(&port, result, entry->edx);
}

/* Original 0x4c0990: clear +0xd8, +0x90 and +0x1a0, and +0xc, +0x10, +0x18 and +0xa4 of the
 * link +0x1b8. */
uint32_t vertrix_port_object_release_links_4c0990(PORT_SIGNATURE)
{
    Port port;
    uint32_t object = entry->eax;
    uint32_t link;
    port_open(&port, calls, services, globals, entry);
    port_set32(&port, object, 0xd8, 0);
    port_set32(&port, object, 0x90, 0);
    link = port_u32(&port, object, 0x1b8);
    port_set32(&port, object, 0x1a0, 0);
    port_set32(&port, link, 0xc, 0);
    port_set32(&port, link, 0x10, 0);
    port_set32(&port, link, 0x18, 0);
    port_set32(&port, link, 0xa4, 0);
    return port_return(&port, object, entry->edx);
}

/* Original 0x4c3850: for each of the +0x138 rows, the bytes of the row ebx[i] doubled into the
 * row [ecx][i], +0x70 bytes wide. edx the source past the last row. */
uint32_t vertrix_port_rows_double_4c3850(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x10
    };
    Port port;
    uint32_t object = entry->eax;
    uint32_t targets;
    uint32_t sources = entry->ebx;
    uint32_t row;
    uint32_t source = 0;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, entry->esp, -0x10u, object);
    targets = port_u32(&port, entry->ecx, 0);
    if ((int32_t)port_u32(&port, object, 0x138) <= 0)
    {
        return port_return(&port, object, port_u32(&port, object, 0x138));
    }
    for (row = 0; (int32_t)row < (int32_t)port_u32(&port, object, 0x138); row++)
    {
        uint32_t target = port_u32(&port, targets, 0);
        uint32_t end = port_u32(&port, object, 0x70) + target;
        source = port_u32(&port, sources, 0);
        while (target < end)
        {
            uint32_t value = port_u8(&port, source, 0);
            target += 2;
            port_set8(&port, target, -2u, value);
            source++;
            port_set8(&port, target, -1u, value);
        }
        targets += 4;
        sources += 4;
    }
    return port_return(&port, object, source);
}

/* Original 0x4c3fa0: the method table (0x4c3e40, 0x4c3ea0, 0x4c3e60, 0x4c3ed0, 0x4c3f80), the
 * name 0x4ffdbc with 123 and the rest cleared. */
uint32_t vertrix_port_object_init_4c3fa0(PORT_SIGNATURE)
{
    Port port;
    uint32_t object = entry->eax;
    port_open(&port, calls, services, globals, entry);
    port_set32(&port, object, 0, 0x4c3e40);
    port_set32(&port, object, 4, 0x4c3ea0);
    port_set32(&port, object, 8, 0x4c3e60);
    port_set32(&port, object, 0xc, 0x4c3ed0);
    port_set32(&port, object, 0x10, 0x4c3f80);
    port_set32(&port, object, 0x68, 0);
    port_set32(&port, object, 0x6c, 0);
    port_set32(&port, object, 0x14, 0);
    port_set32(&port, object, 0x70, 0x4ffdbc);
    port_set32(&port, object, 0x74, 0x7b);
    port_set32(&port, object, 0x78, 0);
    port_set32(&port, object, 0x7c, 0);
    port_set32(&port, object, 0x80, 0);
    return port_return(&port, object, entry->edx);
}

/* Original 0x4c69c0: a buffer of twice (+0x70 + 2) bytes by method +4 of +4 (edx 1) for each of
 * the +0x78 channels, kept from +0x48 of the table +0x1cc on. */
uint32_t vertrix_port_channels_allocate_4c69c0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x20
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t object = entry->eax;
    uint32_t table;
    uint32_t size;
    uint32_t slot;
    uint32_t index;
    uint32_t result;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    table = port_u32(&port, object, 0x1cc);
    size = (port_u32(&port, object, 0x70) + 2) * 2;
    port_set32(&port, ebp, -0x18u, 0);
    port_set32(&port, ebp, -0x1cu, size);
    if ((int32_t)port_u32(&port, object, 0x78) <= 0)
    {
        return port_return(&port, table, entry->edx);
    }
    slot = table;
    result = table;
    do
    {
        uint32_t methods = port_u32(&port, object, 4);
        slot += 4;
        result = call_registers(&port, entry, port_u32(&port, methods, 4), object, 1,
                                port_u32(&port, ebp, -0x1cu), object, slot, methods);
        port_set32(&port, slot, 0x40, result);
        index = port_u32(&port, ebp, -0x18u) + 1;
        port_set32(&port, ebp, -0x18u, index);
    } while ((int32_t)index < (int32_t)port_u32(&port, object, 0x78));
    return port_return(&port, result, entry->edx);
}

/* Original 0x4ca3a0: assign the wide text edx (0x4d8580 its length) to the string eax by
 * 0x4ca1e0 (twice the length), 0x4ca730 and 0x4ca6c0 with -1. */
uint32_t vertrix_port_rtl_wide_assign_4ca3a0(PORT_SIGNATURE)
{
    Port port;
    uint32_t string = entry->eax;
    uint32_t text = entry->edx;
    uint32_t length = 0;
    uint32_t size;
    port_open(&port, calls, services, globals, entry);
    if (text != 0)
    {
        length = call_registers(&port, entry, 0x4d8580, text, text, entry->ebx, string, text,
                                entry->edi);
    }
    size = length * 2;
    call_registers(&port, entry, 0x4ca1e0, string, size, size, string, text, entry->edi);
    call_registers(&port, entry, 0x4ca730, port_u32(&port, string, 0), text, size + 1, string, text,
                   entry->edi);
    call_registers(&port, entry, 0x4ca6c0, string, 0xffffffffu, size + 1, string, text, entry->edi);
    return port_return(&port, string, vertrix_lift_edx);
}
