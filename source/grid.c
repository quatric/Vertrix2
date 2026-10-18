#include "grid.h"

/* Device state, channel and handle tables, grid scans and short update sequences. */

/* Original 0x405ee0: the next byte of the stream (buffer +4: data +0, size +4, position +8),
 * refilling it by 0x405ea0 (0x4eb4d4 with 1 when that leaves no buffer); counts +8 down. */
uint32_t vertrix_port_stream_read_byte_405ee0(PORT_SIGNATURE)
{
    Port port;
    uint32_t stream = entry->eax;
    uint32_t buffer;
    uint32_t position;
    uint32_t value;
    port_open(&port, calls, services, globals, entry);
    position = port_u32(&port, port_u32(&port, stream, 4), 8);
    for (;;)
    {
        buffer = port_u32(&port, stream, 4);
        if ((int32_t)position < (int32_t)port_u32(&port, buffer, 4))
        {
            break;
        }
        port_forward(&port, entry, 0x405ea0, stream, stream, entry->ebx, position);
        stream = vertrix_lift_edx;
        buffer = port_u32(&port, stream, 4);
        position = port_u32(&port, buffer, 8);
        if (buffer == 0)
        {
            port_forward(&port, entry, 0x4eb4d4, 1, stream, entry->ebx, position);
            stream = vertrix_lift_edx;
        }
    }
    value = port_u8(&port, position, port_u32(&port, buffer, 0));
    port_set32(&port, stream, 8, port_u32(&port, stream, 8) - 1);
    buffer = port_u32(&port, stream, 4);
    port_set32(&port, buffer, 8, port_u32(&port, buffer, 8) + 1);
    return port_return(&port, value, entry->edx);
}

/* Original 0x40aba0: 3 while any of the 0x52f130 handles at 0x52f0b0 is open; otherwise clear
 * the count and the 32 handles by 0x4eb5c0 and call [0x52f040]. */
uint32_t vertrix_port_handles_shutdown_40aba0(PORT_SIGNATURE)
{
    Port port;
    uint32_t count;
    uint32_t index;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    count = port_u32(&port, 0, 0x52f130);
    for (index = 0; index < count; index++)
    {
        if (port_u32(&port, index * 4, 0x52f0b0) != 0)
        {
            port_set32(&port, 0, 0x52f130, count);
            return port_return(&port, 3, entry->edx);
        }
    }
    port_set32(&port, 0, 0x52f130, 0);
    result = port_forward(&port, entry, 0x4eb5c0, 0x52f0b0, 0, 0x80, 0);
    result =
        port_forward(&port, entry, port_u32(&port, 0, 0x52f040), result, vertrix_lift_edx, 0x80, 0);
    port_set32(&port, 0, 0x52f130, port_u32(&port, 0, 0x52f130));
    return port_return(&port, result, entry->edx);
}

/* Original 0x40ad50: clear handle eax (from 1); 1 past the count 0x52f130. */
uint32_t vertrix_port_handles_release_40ad50(PORT_SIGNATURE)
{
    Port port;
    uint32_t index = entry->eax - 1;
    port_open(&port, calls, services, globals, entry);
    if (index >= port_u32(&port, 0, 0x52f130))
    {
        return port_return(&port, 1, entry->edx);
    }
    port_set32(&port, index * 4, 0x52f0b0, 0);
    return port_return(&port, 0, entry->edx);
}

/* Original 0x40bf80: keep the rate edx (0x200 to 0x80000) of voice eax (below 32) at 0x52f780
 * and set it on its buffer (0x52f178) by method 17; 0, 1 or 2 (in edx too). */
uint32_t vertrix_port_voice_set_rate_40bf80(PORT_SIGNATURE)
{
    Port port;
    uint32_t voice = entry->eax;
    int32_t rate = (int32_t)entry->edx;
    uint32_t buffer;
    uint32_t pushed[2];
    port_open(&port, calls, services, globals, entry);
    if (voice >= 0x20)
    {
        return port_return(&port, 1, 1);
    }
    if (rate < 0x200 || rate > 0x80000)
    {
        return port_return(&port, 2, 2);
    }
    port_set32(&port, voice * 4, 0x52f780, entry->edx);
    buffer = port_u32(&port, voice * 4, 0x52f178);
    if (buffer != 0)
    {
        uint32_t methods = port_u32(&port, buffer, 0);
        pushed[0] = buffer;
        pushed[1] = entry->edx;
        port_forward_stack(&port, entry, port_u32(&port, methods, 0x44), buffer, entry->edx,
                           entry->ebx, methods, entry->esi, pushed, 2);
    }
    return port_return(&port, 0, 0);
}

/* Original 0x40bfd0: keep the pan edx (below 64) of voice eax at 0x52f800 and set its value
 * (0x52f1fc) on the buffer by method 15; 0, 1 or 2. */
uint32_t vertrix_port_voice_set_pan_40bfd0(PORT_SIGNATURE)
{
    Port port;
    uint32_t voice = entry->eax;
    uint32_t pan = entry->edx;
    uint32_t buffer;
    uint32_t methods;
    uint32_t pushed[2];
    port_open(&port, calls, services, globals, entry);
    if (voice >= 0x20)
    {
        return port_return(&port, 1, entry->edx);
    }
    if (pan >= 0x40)
    {
        return port_return(&port, 2, entry->edx);
    }
    port_set32(&port, voice * 4, 0x52f800, pan);
    buffer = port_u32(&port, voice * 4, 0x52f178);
    if (buffer == 0)
    {
        return port_return(&port, 0, 0);
    }
    methods = port_u32(&port, buffer, 0);
    pushed[0] = buffer;
    pushed[1] = port_u32(&port, pan * 4, 0x52f1fc);
    port_forward_stack(&port, entry, port_u32(&port, methods, 0x3c), pan, methods, pushed[1],
                       buffer, entry->esi, pushed, 2);
    return port_return(&port, 0, vertrix_lift_edx);
}

/* Original 0x40ede0: 3 when the device (bit 7 of 0x531b44) is closed; otherwise set bit 5 and
 * 0x40ae00 (edx 0) on each of the 0x531b48 handles at 0x531ac4. */
uint32_t vertrix_port_device_lock_40ede0(PORT_SIGNATURE)
{
    Port port;
    uint32_t state;
    uint32_t index;
    port_open(&port, calls, services, globals, entry);
    state = port_u8(&port, 0, 0x531b44);
    if ((state & 0x80) == 0)
    {
        return port_return(&port, 3, entry->edx);
    }
    port_set8(&port, 0, 0x531b44, state | 0x20);
    for (index = 0; (int32_t)index < (int32_t)port_u32(&port, 0, 0x531b48); index++)
    {
        port_forward(&port, entry, 0x40ae00, port_u32(&port, index * 4, 0x531ac4), 0, index,
                     index * 4);
    }
    return port_return(&port, 0, entry->edx);
}

/* Original 0x40eea0: 3 when the device is closed; otherwise keep eax and edx at 0x531b70 and
 * 0x531b74 and set bit 0 (0). */
uint32_t vertrix_port_device_set_pair_40eea0(PORT_SIGNATURE)
{
    Port port;
    uint32_t state;
    port_open(&port, calls, services, globals, entry);
    state = port_u8(&port, 0, 0x531b44);
    if ((state & 0x80) == 0)
    {
        return port_return(&port, 3, entry->edx);
    }
    port_set32(&port, 0, 0x531b70, entry->eax);
    port_set32(&port, 0, 0x531b74, entry->edx);
    port_set8(&port, 0, 0x531b44, state | 1);
    return port_return(&port, 0, entry->edx);
}

/* Original 0x40ef40: 3 when the device is closed, 2 for a null eax; otherwise store whether it
 * is locked (bit 5) at eax (0). */
uint32_t vertrix_port_device_get_locked_40ef40(PORT_SIGNATURE)
{
    Port port;
    uint32_t state;
    port_open(&port, calls, services, globals, entry);
    state = port_u8(&port, 0, 0x531b44);
    if ((state & 0x80) == 0)
    {
        return port_return(&port, 3, entry->edx);
    }
    if (entry->eax == 0)
    {
        return port_return(&port, 2, entry->edx);
    }
    port_set32(&port, entry->eax, 0, (state & 0x20) != 0);
    return port_return(&port, 0, entry->edx);
}

/* Original 0x4121e0: read the record table of the stream edx: the count +0x5bc by 0x48a8a0
 * (1 of 8 bytes), +0x5b8 by 0x48a930 and the entries (+0x5bc of 12 bytes); then the count kept
 * before. */
uint32_t vertrix_port_record_table_load_4121e0(PORT_SIGNATURE)
{
    Port port;
    uint32_t table = entry->eax;
    uint32_t stream = entry->edx;
    uint32_t frame = entry->esp - 4;
    uint32_t count;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    count = port_u32(&port, table, 0x5bc);
    port_call_with(&port, 0x48a8a0, stream, count, 1, 8, table, stream, frame);
    port_call_with(&port, 0x48a930, stream, table + 0x5b8, 1, 8, table, stream, frame);
    result = port_call_with(&port, 0x48a930, stream, table, port_u32(&port, table, 0x5bc), 0xc,
                            table, stream, frame);
    port_set32(&port, table, 0x5bc, count);
    return port_return(&port, result, count);
}

/* Original 0x4123d0: copy the style of entry edx (12 bytes each from eax) to the actor ebx:
 * bytes 2, 6, 7, 1, 0 and 8 and words 4 and 10 to +0x4e, +0x52, +0x94, +0x95, +0x93, +0x8c,
 * +0x48 and +0x80. */
uint32_t vertrix_port_actor_storage_style_4123d0(PORT_SIGNATURE)
{
    Port port;
    uint32_t style = entry->eax + entry->edx * 12;
    uint32_t actor = entry->ebx;
    uint32_t size;
    uint32_t last;
    port_open(&port, calls, services, globals, entry);
    if (actor == 0)
    {
        return port_return(&port, style, entry->edx);
    }
    port_set8(&port, actor, 0x4e, port_u8(&port, style, 2));
    port_set16(&port, actor, 0x48, port_u16(&port, style, 4));
    port_set8(&port, actor, 0x52, port_u8(&port, style, 6));
    port_set8(&port, actor, 0x94, port_u8(&port, style, 7));
    port_set8(&port, actor, 0x95, port_u8(&port, style, 1));
    port_set8(&port, actor, 0x93, port_u8(&port, style, 0));
    size = port_u16(&port, style, 0xa);
    port_set32(&port, actor, 0x80, size);
    last = port_u8(&port, style, 8);
    port_set8(&port, actor, 0x8c, last);
    return port_return(&port, (style & 0xffffff00u) | last, size);
}

/* The first of the four channels from `first` 0x4828a0 gives 1 for; otherwise the last result
 * with al the low byte of edx. */
static uint32_t channel_allocate(PORT_SIGNATURE, uint32_t first, uint32_t edx)
{
    Port port;
    uint32_t channel;
    uint32_t result = 0;
    port_open(&port, calls, services, globals, entry);
    for (channel = first; channel < first + 4; channel++)
    {
        result = port_forward(&port, entry, 0x4828a0, channel, edx, entry->ebx, entry->ecx);
        edx = vertrix_lift_edx;
        if (channel == first && first == 0)
        {
            edx &= 0xffffff00u;
        }
        if (result == 1)
        {
            /* The first channel of the second set reports the edx the call leaves. */
            return port_return(
                &port, channel == 4 ? (result & 0xffffff00u) | (edx & 0xff) : channel, entry->edx);
        }
    }
    return port_return(&port, (result & 0xffffff00u) | (edx & 0xff), entry->edx);
}

/* Original 0x4174f0: channels 0 to 3. */
uint32_t vertrix_port_sfx_allocate_channel_p1_4174f0(PORT_SIGNATURE)
{
    return channel_allocate(calls, services, globals, entry, 0, entry->edx);
}

/* Original 0x417550: channels 4 to 7. */
uint32_t vertrix_port_sfx_allocate_channel_p2_417550(PORT_SIGNATURE)
{
    return channel_allocate(calls, services, globals, entry, 4, (entry->edx & 0xffffff00u) | 4);
}

/* The byte of `table` for the pair of entries of cell (al, dl) in the tables 0x4f9320 and
 * 0x4f9538 (28 a row), or -1 when either is 0; edx the pair. */
static uint32_t pair_lookup(PORT_SIGNATURE, uint32_t table)
{
    Port port;
    uint32_t cell = (entry->eax & 0xff) * 28 + (entry->edx & 0xff);
    uint32_t first;
    uint32_t second;
    port_open(&port, calls, services, globals, entry);
    first = port_u8(&port, cell, 0x4f9320);
    second = port_u8(&port, cell, 0x4f9538);
    if (first == 0 || second == 0)
    {
        return port_return(&port, 0xffffffff, (second << 8) | first);
    }
    return port_return(&port, port_u8(&port, first * 8 + second, table), (second << 8) | first);
}

/* Original 0x4178d0: in 0x53bb0f. */
uint32_t vertrix_port_table_pair_value_4178d0(PORT_SIGNATURE)
{
    return pair_lookup(calls, services, globals, entry, 0x53bb0f);
}

/* Original 0x417970: in 0x4f90f7. */
uint32_t vertrix_port_table_pair_link_417970(PORT_SIGNATURE)
{
    return pair_lookup(calls, services, globals, entry, 0x4f90f7);
}

/* Original 0x417da0: the count of the six groups of five bytes of row eax (30 a row at
 * 0x4f9800) with any set. */
uint32_t vertrix_port_table_groups_used_417da0(PORT_SIGNATURE)
{
    Port port;
    uint32_t row = entry->eax * 30;
    uint32_t group;
    uint32_t used = 0;
    port_open(&port, calls, services, globals, entry);
    for (group = 0; group < 6; group++)
    {
        uint32_t set = 0;
        uint32_t offset;
        for (offset = 0; offset < 5; offset++)
        {
            if (port_u8(&port, row + group * 5 + offset, 0x4f9800) != 0)
            {
                set++;
            }
        }
        if (set > 0)
        {
            used++;
        }
    }
    return port_return(&port, used, entry->edx);
}

/* Original 0x418000: the index of the ebx-th (from 0) entry of column eax (counts at 0x534f10,
 * values at 0x534c18 with 0x4c a step) equal to edx, or 0; edx the matches before it. */
uint32_t vertrix_port_table_column_nth_418000(PORT_SIGNATURE)
{
    Port port;
    uint32_t column = entry->eax * 4;
    uint32_t matches = 0;
    uint32_t index;
    uint32_t at = column;
    port_open(&port, calls, services, globals, entry);
    for (index = 0; index < port_u32(&port, column, 0x534f10); index++)
    {
        if (entry->edx == port_u32(&port, at, 0x534c18))
        {
            if (matches == entry->ebx)
            {
                return port_return(&port, index, matches);
            }
            matches++;
        }
        at += 0x4c;
    }
    return port_return(&port, 0, matches);
}

/* Original 0x419ea0: after clearing a pending 0x532a84 (then 0x48b770 on 0x5bb254), 0x419ef0,
 * 0x415860, 0x418ae0 and 0x411f50 on 0x5327f0. */
uint32_t vertrix_port_scene_finish_419ea0(PORT_SIGNATURE)
{
    Port port;
    uint32_t ebx = entry->ebx;
    uint32_t edx = entry->eax;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    if (port_u32(&port, 0, 0x532a84) == 1)
    {
        ebx = 0;
        port_set32(&port, 0, 0x532a84, 0);
        port_forward(&port, entry, 0x48b770, 0x5bb254, edx, ebx, entry->ecx);
        edx = vertrix_lift_edx;
    }
    result = port_forward(&port, entry, 0x419ef0, edx, edx, ebx, entry->ecx);
    result = port_forward(&port, entry, 0x415860, result, vertrix_lift_edx, ebx, entry->ecx);
    result =
        port_forward(&port, entry, 0x418ae0, vertrix_lift_edx, vertrix_lift_edx, ebx, entry->ecx);
    result = port_forward(&port, entry, 0x411f50, 0x5327f0, vertrix_lift_edx, ebx, entry->ecx);
    return port_return(&port, result, entry->edx);
}

/* Original 0x41c020: the scene teardown: 0x41ab90, 0x441b30 on 0x544070, 0x41abe0, 0x41ac00,
 * 0x41ac20, 0x41ac40, 0x41ac70 and 0x41a9e0 on the scene (the edx each leaves), then 0x471a90,
 * 0x471b10, 0x4719e0, 0x45f9f0, 0x45e8f0 and 0x45e910. */
uint32_t vertrix_port_scene_teardown_41c020(PORT_SIGNATURE)
{
    static const uint32_t scene_calls[] = {0x41abe0, 0x41ac00, 0x41ac20,
                                           0x41ac40, 0x41ac70, 0x41a9e0};
    static const uint32_t final_calls[] = {0x471a90, 0x471b10, 0x4719e0,
                                           0x45f9f0, 0x45e8f0, 0x45e910};
    Port port;
    uint32_t result;
    unsigned i;
    port_open(&port, calls, services, globals, entry);
    port_forward(&port, entry, 0x41ab90, entry->eax, entry->eax, entry->ebx, entry->ecx);
    result = port_forward(&port, entry, 0x441b30, port_u32(&port, 0, 0x544070), vertrix_lift_edx,
                          entry->ebx, entry->ecx);
    for (i = 0; i < sizeof scene_calls / sizeof scene_calls[0]; i++)
    {
        result = port_forward(&port, entry, scene_calls[i], vertrix_lift_edx, vertrix_lift_edx,
                              entry->ebx, entry->ecx);
    }
    for (i = 0; i < sizeof final_calls / sizeof final_calls[0]; i++)
    {
        result = port_forward(&port, entry, final_calls[i], result, vertrix_lift_edx, entry->ebx,
                              entry->ecx);
    }
    return port_return(&port, result, entry->edx);
}

/* Original 0x41d410: 0x41ab90, 0x41ac20 and 0x41a9e0 on the scene, 0x4719e0, 0x45f9f0, 0x477ed0
 * on 0x5588f8 (edx 0), 0x4766b0 on 0x54d640 and the handlers 0x421f10 and 0x424230 by 0x418840
 * and 0x418820. */
uint32_t vertrix_port_scene_reset_41d410(PORT_SIGNATURE)
{
    Port port;
    uint32_t scene = entry->eax;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    port_forward(&port, entry, 0x41ab90, scene, entry->edx, entry->ebx, scene);
    port_forward(&port, entry, 0x41ac20, scene, vertrix_lift_edx, entry->ebx, scene);
    result = port_forward(&port, entry, 0x41a9e0, scene, vertrix_lift_edx, entry->ebx, scene);
    result = port_forward(&port, entry, 0x4719e0, result, vertrix_lift_edx, entry->ebx, scene);
    port_forward(&port, entry, 0x45f9f0, result, vertrix_lift_edx, entry->ebx, scene);
    port_forward(&port, entry, 0x477ed0, 0x5588f8, 0, entry->ebx, scene);
    port_forward(&port, entry, 0x4766b0, 0x54d640, vertrix_lift_edx, entry->ebx, scene);
    port_forward(&port, entry, 0x418840, scene, 0x421f10, entry->ebx, scene);
    result = port_forward(&port, entry, 0x418820, scene, 0x424230, entry->ebx, scene);
    return port_return(&port, result, entry->edx);
}

/* The 20 bytes from +0x70 inverted (255 minus each); eax left past them. */
static uint32_t invert_twenty(Port *port, uint32_t object)
{
    uint32_t offset;
    for (offset = 0; offset < 0x14; offset++)
    {
        port_set8(port, object + 0x70, offset, 0xff - port_u8(port, object + 0x70, offset));
    }
    return object + 0x84;
}

/* Original 0x429600: read the four bytes at eax and then 0x224 bytes from +4 from the stream
 * edx by 0x489170, inverting the 20 bytes from +0x70 after each. */
uint32_t vertrix_port_settings_read_inverted_429600(PORT_SIGNATURE)
{
    Port port;
    uint32_t object = entry->eax;
    uint32_t stream = entry->edx;
    uint32_t end;
    port_open(&port, calls, services, globals, entry);
    port_call_with(&port, 0x489170, stream, object, 1, 4, object, stream, entry->ebp);
    invert_twenty(&port, object);
    port_call_with(&port, 0x489170, stream, object + 4, 1, 0x224, object, stream, entry->ebp);
    end = invert_twenty(&port, object);
    return port_return(&port, end, 0x14);
}

/* The method at `method` of each set child of the 7 rows of 4 from +0x15c; eax the last slot
 * address or result. */
static uint32_t grid_children_call(Port *port, const LiftEntry *entry, uint32_t object,
                                   uint32_t method)
{
    uint32_t row = 0;
    uint32_t eax = object;
    do
    {
        uint32_t column = 0;
        do
        {
            uint32_t child;
            eax = object + row + column;
            child = port_u32(port, eax, 0x15c);
            if (child != 0)
            {
                uint32_t methods = port_u32(port, child, 0x158);
                eax = port_call_with(port, port_u32(port, methods, method), child, column,
                                     object + row, methods, row, object, entry->ebp);
                column = vertrix_lift_edx;
            }
            column += 4;
        } while (column != 0x10);
        row += column;
    } while (row != 0x70);
    return eax;
}

/* Original 0x429b60: method +0x18 of each child of the grid. */
uint32_t vertrix_port_grid_children_update_429b60(PORT_SIGNATURE)
{
    Port port;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    result = grid_children_call(&port, entry, entry->eax, 0x18);
    return port_return(&port, result, entry->edx);
}

/* Original 0x429e80: the 7 rows of four values from +0x1cc (16 bytes a row) stored into the
 * dwords ecx onwards of edx; eax +0x70 and edx past the last. */
uint32_t vertrix_port_choice_grid_store_values_429e80(PORT_SIGNATURE)
{
    Port port;
    uint32_t index;
    port_open(&port, calls, services, globals, entry);
    for (index = 0; index < 28; index++)
    {
        port_set32(&port, entry->edx + (entry->ecx + index) * 4, 0,
                   port_u32(&port, entry->eax + index * 4, 0x1cc));
    }
    return port_return(&port, entry->eax + 0x70, entry->edx + (entry->ecx + 28) * 4);
}

/* Original 0x42a1b0: whether any child of the 7 rows of 4 from +0x15c has byte +0x15d 1. */
uint32_t vertrix_port_choice_grid_any_marked_42a1b0(PORT_SIGNATURE)
{
    Port port;
    uint32_t offset;
    port_open(&port, calls, services, globals, entry);
    for (offset = 0; offset < 0x70; offset += 4)
    {
        uint32_t child = port_u32(&port, entry->eax + offset, 0x15c);
        if (child != 0 && port_u8(&port, child, 0x15d) == 1)
        {
            return port_return(&port, 1, entry->edx);
        }
    }
    return port_return(&port, 0, entry->edx);
}

/* Original 0x42a4c0: 0x4b2380 on the lists +0x15c and +0x170 with edx 3 and ebx and ecx the
 * given edx. */
uint32_t vertrix_port_lists_handler_42a4c0(PORT_SIGNATURE)
{
    Port port;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    port_forward_esi(&port, entry, 0x4b2380, entry->eax + 0x15c, 3, entry->edx, entry->edx,
                     entry->eax);
    result = port_forward_esi(&port, entry, 0x4b2380, entry->eax + 0x170, 3, entry->edx, entry->edx,
                              entry->eax);
    return port_return(&port, result, vertrix_lift_edx);
}

/* Original 0x42a8e0: unless the piece (+0x164) shows 5 or 6 (byte +0x15c), give it a random one
 * below 5 (0x4826c0 on 0x598d30) with its images (28 bytes each at 0x544ac0) by 0x4ac8d0. */
uint32_t vertrix_port_piece_random_look_42a8e0(PORT_SIGNATURE)
{
    Port port;
    uint32_t piece;
    uint32_t look;
    uint32_t drawn;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    piece = port_u32(&port, entry->eax, 0x164);
    look = port_u8(&port, piece, 0x15c);
    if (look == 5 || look == 6)
    {
        return port_return(&port, (entry->eax & 0xffffff00u) | look, entry->edx);
    }
    drawn = port_forward(&port, entry, 0x4826c0, 0x598d30, 5, 0, piece) & 0xffff;
    result = port_forward(&port, entry, 0x4ac8d0, piece, 0x544ac0 + drawn * 28, drawn, piece);
    port_set8(&port, piece, 0x15c, drawn);
    return port_return(&port, result, entry->edx);
}
