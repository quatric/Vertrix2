#include "library.h"

/* Small routines of the runtime library: text, number and table helpers and list unlinking. */

/* Original 0x4d7400: +0x3c plus 0x20000 when it is set, else 0. */
uint32_t vertrix_port_text_id_4d7400(PORT_SIGNATURE)
{
    Port port;
    uint32_t id;
    port_open(&port, calls, services, globals, entry);
    id = port_u32(&port, entry->eax, 0x3c);
    return port_return(&port, id != 0 ? id + 0x20000 : 0, entry->edx);
}

/* Original 0x4daca0: the next byte of the text +8 (advancing it), or -1 at its end with bit 1 of
 * byte +0x10 set. */
uint32_t vertrix_port_text_next_byte_4daca0(PORT_SIGNATURE)
{
    Port port;
    uint32_t object = entry->eax;
    uint32_t at;
    uint32_t value;
    port_open(&port, calls, services, globals, entry);
    at = port_u32(&port, object, 8);
    value = port_u8(&port, at, 0);
    if (value == 0)
    {
        port_set8(&port, object, 0x10, port_u8(&port, object, 0x10) | 2);
        return port_return(&port, 0xffffffff, entry->edx);
    }
    port_set32(&port, object, 8, at + 1);
    return port_return(&port, value, entry->edx);
}

/* Original 0x4dc000: remove the handle +0 from the map 0x5c77a8 by 0x4dbc60 when both are set,
 * then clear it. */
uint32_t vertrix_port_handle_unmap_4dc000(PORT_SIGNATURE)
{
    Port port;
    uint32_t object = entry->eax;
    uint32_t handle;
    uint32_t map;
    uint32_t edx = entry->edx;
    port_open(&port, calls, services, globals, entry);
    handle = port_u32(&port, object, 0);
    map = port_u32(&port, 0, 0x5c77a8);
    if (handle != 0 && map != 0)
    {
        port_forward(&port, entry, 0x4dbc60, map, handle, entry->ebx, object);
        edx = vertrix_lift_edx;
    }
    port_set32(&port, object, 0, 0);
    return port_return(&port, object, edx);
}

/* Original 0x4dc160: the object of the handle +0 in the map 0x5c77e8 by 0x4dbcd0, or 0. */
uint32_t vertrix_port_rtl_lookup_call_4dc160(PORT_SIGNATURE)
{
    Port port;
    uint32_t handle;
    uint32_t map;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    handle = port_u32(&port, entry->eax, 0);
    map = port_u32(&port, 0, 0x5c77e8);
    if (handle == 0 || map == 0)
    {
        return port_return(&port, 0, entry->edx);
    }
    result = port_forward(&port, entry, 0x4dbcd0, map, handle, entry->ebx, entry->ecx);
    return port_return(&port, result, entry->edx);
}

/* Original 0x4dd460: detach the handle +4: unmap it by 0x4df1c0 from the map 0x4dd3e0 gives
 * (when there is one), the method +0x1c, clear it; the handle. */
uint32_t vertrix_port_handle_detach_4dd460(PORT_SIGNATURE)
{
    Port port;
    uint32_t object = entry->eax;
    uint32_t handle;
    uint32_t map;
    uint32_t methods;
    port_open(&port, calls, services, globals, entry);
    handle = port_u32(&port, object, 4);
    if (handle != 0)
    {
        map = port_forward(&port, entry, 0x4dd3e0, 0, entry->edx, handle, object);
        if (map != 0)
        {
            port_forward(&port, entry, 0x4df1c0, map, port_u32(&port, object, 4), handle, object);
        }
    }
    methods = port_u32(&port, object, 0);
    port_forward(&port, entry, port_u32(&port, methods, 0x1c), object, methods, handle, object);
    port_set32(&port, object, 4, 0);
    return port_return(&port, handle, entry->edx);
}

/* Original 0x4def50: free the block +4 by 0x4ca040 (clearing it); for a nonzero ebx allocate edx
 * dwords by 0x4c9ff0 there and clear them by 0x4eb5c0; keep edx at +8. */
uint32_t vertrix_port_block_resize_4def50(PORT_SIGNATURE)
{
    Port port;
    uint32_t object = entry->eax;
    uint32_t count = entry->edx;
    uint32_t block;
    uint32_t result = entry->eax;
    uint32_t edx = entry->edx;
    port_open(&port, calls, services, globals, entry);
    block = port_u32(&port, object, 4);
    if (block != 0)
    {
        result = port_forward_esi(&port, entry, 0x4ca040, block, count, entry->ebx, object, count);
        edx = vertrix_lift_edx;
        port_set32(&port, object, 4, 0);
    }
    if (entry->ebx != 0)
    {
        uint32_t size = count * 4;
        block = port_forward_esi(&port, entry, 0x4c9ff0, size, 0, size, object, count);
        port_set32(&port, object, 4, block);
        result =
            port_forward_esi(&port, entry, 0x4eb5c0, block, vertrix_lift_edx, size, object, count);
        edx = vertrix_lift_edx;
    }
    port_set32(&port, object, 8, count);
    return port_return(&port, result, edx);
}

/* Original 0x4def90: free the block +4 by 0x4ca040 (clearing it), clear +0xc and +0x10, release
 * +0x14 by 0x4e2400 and clear it (each through the edx the call before leaves). */
uint32_t vertrix_port_block_release_4def90(PORT_SIGNATURE)
{
    Port port;
    uint32_t object = entry->eax;
    uint32_t block;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    block = port_u32(&port, object, 4);
    if (block != 0)
    {
        port_forward(&port, entry, 0x4ca040, block, object, entry->ebx, entry->ecx);
        object = vertrix_lift_edx;
        port_set32(&port, object, 4, 0);
    }
    port_set32(&port, object, 0xc, 0);
    block = port_u32(&port, object, 0x14);
    port_set32(&port, object, 0x10, 0);
    result = port_forward(&port, entry, 0x4e2400, block, object, entry->ebx, entry->ecx);
    port_set32(&port, vertrix_lift_edx, 0x14, 0);
    return port_return(&port, result, entry->edx);
}

/* Original 0x4e012c: each byte of the text eax replaced by what 0x4dabb0 makes of it (ebx the
 * next byte in bl). */
uint32_t vertrix_port_text_map_bytes_4e012c(PORT_SIGNATURE)
{
    Port port;
    uint32_t at = entry->eax;
    uint32_t ebx = entry->ebx;
    uint32_t result = entry->eax;
    uint32_t next;
    port_open(&port, calls, services, globals, entry);
    if (port_u8(&port, at, 0) == 0)
    {
        return port_return(&port, result, entry->edx);
    }
    do
    {
        result = port_forward(&port, entry, 0x4dabb0, port_u8(&port, at, 0), at, ebx, entry->ecx);
        at = vertrix_lift_edx;
        port_set8(&port, at, 0, result);
        next = port_u8(&port, at, 1);
        ebx = (ebx & 0xffffff00u) | next;
        at++;
    } while (next != 0);
    return port_return(&port, result, entry->edx);
}

/* Original 0x4e0228: store edx (with bit 14 set unless it is 0) in slot eax of the table at
 * 0x507c88; eax the slot offset. */
uint32_t vertrix_port_handle_table_set_4e0228(PORT_SIGNATURE)
{
    Port port;
    uint32_t offset = entry->eax << 2;
    uint32_t value = entry->edx != 0 ? entry->edx | 0x4000 : 0;
    port_open(&port, calls, services, globals, entry);
    port_set32(&port, port_u32(&port, 0, 0x507c88), offset, value);
    return port_return(&port, offset, value);
}

/* Original 0x4e03fc: inside the lock ([0x507cd0], [0x507cd4]) clear slot edx of the table
 * 0x507c8c when it is between 1 and the count 0x507c90 (the edx the lock call leaves). */
uint32_t vertrix_port_handle_table_clear_4e03fc(PORT_SIGNATURE)
{
    Port port;
    uint32_t slot;
    uint32_t eax;
    uint32_t edx;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    eax = port_forward(&port, entry, port_u32(&port, 0, 0x507cd0), entry->eax, entry->eax,
                       entry->ebx, entry->ecx);
    slot = vertrix_lift_edx;
    edx = slot;
    if ((int32_t)slot > 0 && (int32_t)slot < (int32_t)port_u32(&port, 0, 0x507c90))
    {
        eax = slot * 4;
        edx = port_u32(&port, 0, 0x507c8c);
        port_set32(&port, edx, eax, 0);
    }
    result =
        port_forward(&port, entry, port_u32(&port, 0, 0x507cd4), eax, edx, entry->ebx, entry->ecx);
    return port_return(&port, result, entry->edx);
}

/* Original 0x4e0960: the access (at edx) and creation (at ebx) flags of open mode eax. */
uint32_t vertrix_port_open_mode_flags_4e0960(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    if (entry->eax == 2)
    {
        port_set32(&port, entry->edx, 0, 0xc0000000);
        port_set32(&port, entry->ebx, 0, 0x80);
    }
    else if (entry->eax == 1)
    {
        port_set32(&port, entry->edx, 0, 0x40000000);
        port_set32(&port, entry->ebx, 0, 0x80);
    }
    else
    {
        port_set32(&port, entry->edx, 0, 0x80000000);
        port_set32(&port, entry->ebx, 0, 1);
    }
    return port_return(&port, entry->eax, entry->edx);
}

/* Original 0x4e09f0: compare the texts eax and edx ignoring ASCII case; the difference of the
 * first differing bytes (in edx too). */
uint32_t vertrix_port_text_compare_nocase_4e09f0(PORT_SIGNATURE)
{
    Port port;
    uint32_t left = entry->eax;
    uint32_t right = entry->edx;
    uint32_t a;
    uint32_t b;
    uint32_t difference;
    port_open(&port, calls, services, globals, entry);
    for (;;)
    {
        a = port_u8(&port, left, 0);
        b = port_u8(&port, right, 0);
        if (a >= 0x41 && a <= 0x5a)
        {
            a += 0x20;
        }
        if (b >= 0x41 && b <= 0x5a)
        {
            b += 0x20;
        }
        if (a != b || b == 0)
        {
            break;
        }
        left++;
        right++;
    }
    difference = a - b;
    return port_return(&port, difference, difference);
}

/* Original 0x4e5678: the import 0x4f1b3c on each of the 0x5c8940 locks of 24 bytes at
 * 0x5c8310. */
uint32_t vertrix_port_locks_delete_4e5678(PORT_SIGNATURE)
{
    Port port;
    uint32_t count;
    uint32_t index = 0;
    uint32_t lock = 0x5c8310;
    uint32_t eax = entry->eax;
    uint32_t edx;
    uint32_t ecx = entry->ecx;
    uint32_t pushed[1];
    port_open(&port, calls, services, globals, entry);
    count = port_u32(&port, 0, 0x5c8940);
    edx = count;
    if ((int32_t)count > 0)
    {
        do
        {
            pushed[0] = lock;
            index++;
            eax = port_forward_stack(&port, entry, 0x4f1b3c, eax, edx, lock, ecx, index, pushed, 1);
            edx = vertrix_lift_edx;
            ecx = port_u32(&port, 0, 0x5c8940);
            lock += 0x18;
        } while ((int32_t)index < (int32_t)ecx);
    }
    return port_return(&port, eax, entry->edx);
}

/* Original 0x4e6600: a copy of the text eax: 0x4e7c90 allocates twice its length by 0x4d8580
 * plus one and 0x4eb5e0 copies it; the copy or 0. */
uint32_t vertrix_port_text_duplicate_4e6600(PORT_SIGNATURE)
{
    Port port;
    uint32_t length;
    uint32_t size;
    uint32_t copy;
    port_open(&port, calls, services, globals, entry);
    length = port_forward(&port, entry, 0x4d8580, entry->eax, entry->eax, entry->ebx, entry->ecx);
    size = (length + 1) * 2;
    copy = port_forward(&port, entry, 0x4e7c90, size, vertrix_lift_edx, size, entry->ecx);
    if (copy != 0)
    {
        port_forward(&port, entry, 0x4eb5e0, copy, vertrix_lift_edx, size, copy);
    }
    return port_return(&port, copy, entry->edx);
}

/* Original 0x4e66a0: whether the entry 0x512a38 of the module 0x512a2c (imports 0x4f1c44 and
 * 0x4f1bdc) exists and gives nonzero. */
uint32_t vertrix_port_module_entry_check_4e66a0(PORT_SIGNATURE)
{
    Port port;
    uint32_t module;
    uint32_t function;
    uint32_t result = 0;
    uint32_t pushed[2] = {0x512a2c, 0};
    port_open(&port, calls, services, globals, entry);
    module = port_forward_stack(&port, entry, 0x4f1c44, entry->eax, entry->edx, entry->ebx,
                                entry->ecx, entry->esi, pushed, 1);
    if (module != 0)
    {
        pushed[0] = module;
        pushed[1] = 0x512a38;
        function = port_forward_stack(&port, entry, 0x4f1bdc, module, vertrix_lift_edx, 0,
                                      entry->ecx, entry->esi, pushed, 2);
        if (function != 0)
        {
            result = port_forward(&port, entry, function, function, function, 0, entry->ecx);
        }
    }
    return port_return(&port, result != 0, entry->edx);
}

/* Original 0x4e7bf0: unless bit 5 of byte +0xd is set, when 0x4e0a30 says the handle +0x10 is a
 * device set it, and bit 1 too when bits 0 to 2 are clear. */
uint32_t vertrix_port_stream_mark_device_4e7bf0(PORT_SIGNATURE)
{
    Port port;
    uint32_t stream = entry->eax;
    uint32_t result;
    uint32_t flags;
    port_open(&port, calls, services, globals, entry);
    if ((port_u8(&port, stream, 0xd) & 0x20) != 0)
    {
        return port_return(&port, stream, entry->edx);
    }
    result = port_forward(&port, entry, 0x4e0a30, port_u32(&port, stream, 0x10), stream, entry->ebx,
                          entry->ecx);
    if (result == 0)
    {
        return port_return(&port, result, entry->edx);
    }
    stream = vertrix_lift_edx;
    flags = port_u8(&port, stream, 0xd) | 0x20;
    port_set8(&port, stream, 0xd, flags);
    if ((flags & 7) == 0)
    {
        port_set8(&port, stream, 0xd, flags | 2);
    }
    return port_return(&port, result, entry->edx);
}

/* Original 0x4e8400: when 0x4e5918 (eax 0) gives nonzero, the value of the slot 0x507c98 by
 * import 0x4f1cdc; without one the fatal error 0x512ff8 by 0x4e628c. */
uint32_t vertrix_port_thread_data_4e8400(PORT_SIGNATURE)
{
    Port port;
    uint32_t data = 0;
    uint32_t result;
    uint32_t pushed[1];
    port_open(&port, calls, services, globals, entry);
    result = port_forward(&port, entry, 0x4e5918, 0, entry->edx, entry->ebx, entry->ecx);
    if (result != 0)
    {
        pushed[0] = port_u32(&port, 0, 0x507c98);
        data = port_forward_stack(&port, entry, 0x4f1cdc, result, pushed[0], 0, entry->ecx,
                                  entry->esi, pushed, 1);
    }
    if (data == 0)
    {
        port_forward(&port, entry, 0x4e628c, 0x512ff8, 1, 0, entry->ecx);
    }
    return port_return(&port, data, entry->edx);
}

/* Original 0x4e86fc: unless 0x4e869c refuses, unlink the node from the list 0x50aefc (+4 the
 * previous, +8 the next); 0 when unlinked. */
uint32_t vertrix_port_list_unlink_4e86fc(PORT_SIGNATURE)
{
    Port port;
    uint32_t previous;
    uint32_t next;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    previous = port_u32(&port, entry->eax, 4);
    next = port_u32(&port, entry->eax, 8);
    result = port_forward(&port, entry, 0x4e869c, entry->eax, next, previous, entry->ecx);
    if (result != 0)
    {
        return port_return(&port, result, entry->edx);
    }
    next = vertrix_lift_edx;
    if (previous == 0)
    {
        port_set32(&port, 0, 0x50aefc, next);
    }
    else
    {
        port_set32(&port, previous, 8, next);
    }
    if (next != 0)
    {
        port_set32(&port, next, 4, previous);
    }
    return port_return(&port, result, entry->edx);
}

/* Original 0x4e8790: copy the character at edx to eax: two bytes for a lead byte of the double
 * byte table 0x5c8961 (when 0x5c8950 is set), else one; dl the last byte. */
uint32_t vertrix_port_char_copy_4e8790(PORT_SIGNATURE)
{
    Port port;
    uint32_t first;
    uint32_t second;
    port_open(&port, calls, services, globals, entry);
    first = port_u8(&port, entry->edx, 0);
    if (port_u32(&port, 0, 0x5c8950) != 0 && (port_u8(&port, first, 0x5c8961) & 1) != 0)
    {
        port_set8(&port, entry->eax, 0, port_u8(&port, entry->edx, 0));
        second = port_u8(&port, entry->edx, 1);
        port_set8(&port, entry->eax, 1, second);
        return port_return(&port, entry->eax, (entry->edx & 0xffffff00u) | second);
    }
    port_set8(&port, entry->eax, 0, first);
    return port_return(&port, entry->eax, (entry->edx & 0xffffff00u) | first);
}

/* Original 0x4e8950: whether the record is of kind 1 with +4 set and its word +0xa outside 0x10
 * to 0x12. */
uint32_t vertrix_port_record_kind_check_4e8950(PORT_SIGNATURE)
{
    Port port;
    uint32_t value;
    port_open(&port, calls, services, globals, entry);
    if (port_u16(&port, entry->eax, 0) != 1 || port_u32(&port, entry->eax, 4) == 0)
    {
        return port_return(&port, 0, entry->edx);
    }
    value = port_u16(&port, entry->eax, 0xa);
    return port_return(&port, value < 0x10 || value > 0x12, entry->edx);
}

/* The dword at `offset` of signal eax's pair: in the table at 0x50af1c for signals 4 and 7,
 * otherwise in the thread's data ([0x507c9c]) from +0x58. */
static uint32_t signal_field(PORT_SIGNATURE, uint32_t offset)
{
    Port port;
    uint32_t data;
    port_open(&port, calls, services, globals, entry);
    if (entry->eax == 7 || entry->eax == 4)
    {
        return port_return(&port, port_u32(&port, entry->eax * 8, 0x50af1c + offset), entry->edx);
    }
    data = port_forward(&port, entry, port_u32(&port, 0, 0x507c9c), entry->eax, entry->eax,
                        entry->ebx, entry->ecx);
    return port_return(&port, port_u32(&port, data + vertrix_lift_edx * 8, 0x58 + offset),
                       entry->edx);
}

/* Original 0x4e8a58: the first dword. */
uint32_t vertrix_port_signal_handler_get_4e8a58(PORT_SIGNATURE)
{
    return signal_field(calls, services, globals, entry, 0);
}

/* Original 0x4e8a7c: the second dword. */
uint32_t vertrix_port_signal_flags_get_4e8a7c(PORT_SIGNATURE)
{
    return signal_field(calls, services, globals, entry, 4);
}

/* Original 0x4e8d80: when 0x4e8b24 gives nonzero, 0x4e8b8c and 0x4e8a10 for signals 4 and 7
 * with 2. */
uint32_t vertrix_port_signals_reset_4e8d80(PORT_SIGNATURE)
{
    Port port;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    result = port_forward(&port, entry, 0x4e8b24, entry->eax, entry->edx, entry->ebx, entry->ecx);
    if (result != 0)
    {
        port_forward(&port, entry, 0x4e8b8c, result, vertrix_lift_edx, entry->ebx, entry->ecx);
        port_forward(&port, entry, 0x4e8a10, 4, 2, entry->ebx, entry->ecx);
        result = port_forward(&port, entry, 0x4e8a10, 7, 2, entry->ebx, entry->ecx);
    }
    return port_return(&port, result, entry->edx);
}

/* Original 0x4e9020: whether the word eax is a double byte character: its high byte a lead byte
 * (0x5c8961, when 0x5c8950 is set) and 0x4ea310 accepting its low byte. */
uint32_t vertrix_port_char_is_double_4e9020(PORT_SIGNATURE)
{
    Port port;
    uint32_t lead;
    port_open(&port, calls, services, globals, entry);
    if (port_u32(&port, 0, 0x5c8950) == 0)
    {
        return port_return(&port, 0, entry->edx);
    }
    lead = port_u8(&port, (entry->eax >> 8) & 0xff, 0x5c8961) & 1;
    if (lead == 0)
    {
        return port_return(&port, 0, entry->edx);
    }
    if (port_forward(&port, entry, 0x4ea310, entry->eax & 0xff, lead, entry->ebx, entry->ecx) == 0)
    {
        return port_return(&port, 0, entry->edx);
    }
    return port_return(&port, 1, entry->edx);
}

/* Original 0x4e9670: read the decimal digits at eax into the dword at edx; eax left past them,
 * edx the value. */
uint32_t vertrix_port_parse_decimal_4e9670(PORT_SIGNATURE)
{
    Port port;
    uint32_t at = entry->eax;
    uint32_t value = 0;
    port_open(&port, calls, services, globals, entry);
    if (port_u8(&port, at, 0) >= 0x30)
    {
        while (port_u8(&port, at, 0) <= 0x39)
        {
            value = value * 10 + port_u8(&port, at, 0);
            at++;
            value -= 0x30;
            if (port_u8(&port, at, 0) < 0x30)
            {
                break;
            }
        }
    }
    port_set32(&port, entry->edx, 0, value);
    return port_return(&port, at, value);
}

/* Original 0x4ea310: whether the byte eax may follow a lead byte: 0 without the double byte
 * table (0x5c8950), bit 3 of 0x50b2a9 for code page 932 (0x50a820), else whether it is
 * nonzero. */
uint32_t vertrix_port_char_trail_check_4ea310(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    if (port_u32(&port, 0, 0x5c8950) == 0)
    {
        return port_return(&port, 0, entry->edx);
    }
    if (port_u32(&port, 0, 0x50a820) == 0x3a4)
    {
        return port_return(&port, port_u8(&port, entry->eax & 0xff, 0x50b2a9) & 8, entry->edx);
    }
    return port_return(&port, entry->eax != 0, entry->edx);
}

/* Original 0x4ebc90: move the buffer (+0 the position, +4 the remaining) by eax when it stays
 * inside it (from the start +8 of +8), clearing bit 4 of byte +0xc (0); otherwise 1. */
uint32_t vertrix_port_buffer_seek_4ebc90(PORT_SIGNATURE)
{
    Port port;
    int32_t step = (int32_t)entry->eax;
    uint32_t buffer = entry->edx;
    port_open(&port, calls, services, globals, entry);
    if (step > (int32_t)port_u32(&port, buffer, 4))
    {
        return port_return(&port, 1, entry->edx);
    }
    if (step <
        (int32_t)(port_u32(&port, port_u32(&port, buffer, 8), 8) - port_u32(&port, buffer, 0)))
    {
        return port_return(&port, 1, entry->edx);
    }
    port_set8(&port, buffer, 0xc, port_u8(&port, buffer, 0xc) & 0xef);
    port_set32(&port, buffer, 0, port_u32(&port, buffer, 0) + entry->eax);
    port_set32(&port, buffer, 4, port_u32(&port, buffer, 4) - entry->eax);
    return port_return(&port, 0, entry->edx);
}
