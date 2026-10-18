#include "system.h"

/* Runtime helpers: object release, focus restore, event tables, handle slots and closing, stream
 * buffers, text comparison and conversion, and extended float wrappers. */

/* A call handing the callee esi, edi and ebp as given and `count` stack dwords. */
static uint32_t call_frame(Port *port, uint32_t target, uint32_t eax, uint32_t edx, uint32_t ebx,
                           uint32_t ecx, uint32_t esi, uint32_t edi, uint32_t ebp,
                           const uint32_t *stack, unsigned count)
{
    return port_call_registers(port, target, eax, edx, ebx, ecx, esi, edi, ebp, stack, count);
}

/* Original 0x4d9350: an object with a positive count (+4) is released by its method +4 with 2. */
uint32_t vertrix_port_rtl_release_counted_4d9350(PORT_SIGNATURE)
{
    Port port;
    uint32_t object = entry->eax;
    uint32_t methods;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    if ((int32_t)port_u32(&port, object, 4) <= 0)
    {
        return port_return(&port, object, entry->edx);
    }
    methods = port_u32(&port, object, 0);
    result =
        port_forward(&port, entry, port_u32(&port, methods, 4), object, 2, entry->ebx, methods);
    return port_return(&port, result, entry->edx);
}

/* Original 0x4dc420 (one stack argument, the window): the focused window (slot 0x4f1990), unless
 * it is none or the window, or its parent when 0x4dc290 does not take it with 3, is sent 0x14f
 * (slot 0x4f1a94) when 0x4dc290 takes it with 2, unless the window is a child (style bit 30,
 * slot 0x4f19f0) whose parent (slot 0x4f19c8) is the desktop (slot 0x4f1978). */
uint32_t vertrix_port_rtl_focus_notify_4dc420(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0xc
    };
    Port port;
    uint8_t stack[BELOW + 8 + 4];
    uint32_t window;
    uint32_t focus;
    uint32_t esi;
    uint32_t ebx;
    uint32_t eax;
    uint32_t pushed[4];
    port_open_arguments(&port, stack, calls, services, globals, entry, BELOW, 1);
    window = port_u32(&port, entry->esp, 4);
    focus = call_frame(&port, 0x4f1990, entry->eax, entry->edx, entry->ebx, entry->ecx, entry->esi,
                       window, entry->ebp, NULL, 0);
    ebx = focus;
    esi = focus;
    if (focus == 0 || focus == window)
    {
        return port_return(&port, focus, vertrix_lift_edx);
    }
    pushed[0] = focus;
    pushed[1] = 3;
    eax = call_frame(&port, 0x4dc290, focus, vertrix_lift_edx, ebx, entry->ecx, esi, window,
                     entry->ebp, pushed, 2);
    if (eax == 0)
    {
        pushed[0] = ebx;
        esi = call_frame(&port, 0x4f19c8, eax, vertrix_lift_edx, ebx, entry->ecx, esi, window,
                         entry->ebp, pushed, 1);
        if (esi == window)
        {
            return port_return(&port, esi, vertrix_lift_edx);
        }
        pushed[0] = esi;
        pushed[1] = 2;
        eax = call_frame(&port, 0x4dc290, esi, vertrix_lift_edx, ebx, entry->ecx, esi, window,
                         entry->ebp, pushed, 2);
        if (eax == 0)
        {
            return port_return(&port, eax, vertrix_lift_edx);
        }
    }
    if (window != 0)
    {
        pushed[0] = window;
        pushed[1] = 0xfffffff0u;
        eax = call_frame(&port, 0x4f19f0, eax, vertrix_lift_edx, ebx, entry->ecx, esi, window,
                         entry->ebp, pushed, 2);
        if ((eax & 0x40000000u) != 0)
        {
            pushed[0] = window;
            ebx = call_frame(&port, 0x4f19c8, eax, vertrix_lift_edx, ebx, entry->ecx, esi, window,
                             entry->ebp, pushed, 1);
            eax = call_frame(&port, 0x4f1978, ebx, vertrix_lift_edx, ebx, entry->ecx, esi, window,
                             entry->ebp, NULL, 0);
            if (ebx == eax)
            {
                return port_return(&port, eax, vertrix_lift_edx);
            }
        }
    }
    pushed[0] = esi;
    pushed[1] = 0x14f;
    pushed[2] = 0;
    pushed[3] = 0;
    eax = call_frame(&port, 0x4f1a94, eax, vertrix_lift_edx, ebx, entry->ecx, esi, window,
                     entry->ebp, pushed, 4);
    return port_return(&port, eax, vertrix_lift_edx);
}

/* Original 0x4decd0 (guarded, 0x51baa0): an event table built on eax (0x4deec0 with 10, 0x4deec0
 * with 4 on +0x1c, 0x4def50 with 7) keeps edx, ebx and ecx at +0x38, +0x3c and +0x40. The
 * table. */
uint32_t vertrix_port_rtl_construct_event_table_4decd0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x2c
    };
    Port port;
    uint32_t record = entry->esp - BELOW;
    uint32_t table;
    uint32_t part;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, record, 0, port.env.chain);
    port_set32(&port, record, 4, 0x4ec1ec);
    port_set32(&port, record, 8, 0x51baa0);
    port_set32(&port, record, 0xc, 0);
    port_set8(&port, record, 0x18, 0);
    port_set32(&port, record, 0x14, entry->eax);
    part = port_call_with(&port, 0x4deec0, entry->eax, 0xa, 0, entry->ecx, entry->eax, entry->edx,
                          entry->ebx);
    port_set32(&port, record, 0xc, 1);
    part = port_call_with(&port, 0x4deec0, part + 0x1c, 4, 0, entry->ecx, entry->eax, entry->edx,
                          entry->ebx);
    table = part - 0x1c;
    port_set32(&port, record, 0xc, 2);
    port_call_with(&port, 0x4def50, part, 7, 0, entry->ecx, table, entry->edx, entry->ebx);
    port_set32(&port, table, 0x38, entry->edx);
    port_set32(&port, table, 0x3c, entry->ebx);
    port_set32(&port, table, 0x40, entry->ecx);
    return port_return(&port, table, vertrix_lift_edx);
}

/* Original 0x4e02a4: under the handle lock (0x507cd0, 0x507cd4) eax takes the first free slot of
 * the handle table 0x507c8c (0x507c90 slots), or a new slot the table grows by (0x4ec0e0). The
 * new slot, or for a free one the edx the unlock leaves (its index). */
uint32_t vertrix_port_crt_handle_slot_add_4e02a4(PORT_SIGNATURE)
{
    Port port;
    uint32_t value = entry->eax;
    uint32_t count;
    uint32_t ebx;
    uint32_t ecx = entry->ecx;
    uint32_t table;
    uint32_t index = 0;
    port_open(&port, calls, services, globals, entry);
    port_forward_esi(&port, entry, port_u32(&port, 0, 0x507cd0), value, entry->edx, entry->ebx,
                     entry->ecx, value);
    count = port_u32(&port, 0, 0x507c90);
    ebx = count;
    if ((int32_t)count > 0)
    {
        uint32_t offset;
        ecx = count * 4;
        for (offset = 0; (int32_t)offset < (int32_t)ecx; offset += 4, index++)
        {
            ebx = port_u32(&port, 0, 0x507c8c) + offset;
            if (port_u32(&port, ebx, 0) == 0)
            {
                port_set32(&port, ebx, 0, value);
                port_forward_esi(&port, entry, port_u32(&port, 0, 0x507cd4), offset, index, ebx,
                                 ecx, value);
                return port_return(&port, vertrix_lift_edx, entry->edx);
            }
        }
    }
    count = port_u32(&port, 0, 0x507c90);
    table = port_forward_esi(&port, entry, 0x4ec0e0, port_u32(&port, 0, 0x507c8c), (count + 1) * 4,
                             ebx, ecx, value);
    count = port_u32(&port, 0, 0x507c90);
    port_set32(&port, 0, 0x507c8c, table);
    port_set32(&port, table + count * 4, 0, value);
    port_set32(&port, 0, 0x507c90, count + 1);
    port_forward_esi(&port, entry, port_u32(&port, 0, 0x507cd4), table, count, ebx, count + 1,
                     value);
    return port_return(&port, port_u32(&port, 0, 0x507c90) - 1, entry->edx);
}

/* Original 0x4e0fc0: the handle eax closed: out of range (above 0x507c34) sets the error 4 and
 * gives -1; a close hook (0x507d08) with a handler (0x507cfc) closes through 0x507d00 and the
 * hook, otherwise CloseHandle (slot 0x4f1b2c), failing with the error 4 and -1; the slot is
 * freed (0x4e0228 with 0). 0. */
uint32_t vertrix_port_crt_handle_close_4e0fc0(PORT_SIGNATURE)
{
    Port port;
    uint32_t handle = entry->eax;
    uint32_t table;
    uint32_t hook;
    uint32_t system;
    uint32_t eax = entry->eax;
    uint32_t edx;
    uint32_t pushed[1];
    int closed = 0;
    port_open(&port, calls, services, globals, entry);
    if ((int32_t)handle < 0 || handle > port_u32(&port, 0, 0x507c34))
    {
        port_forward(&port, entry, 0x4dae70, 4, entry->edx, handle, entry->ecx);
        return port_return(&port, 0xffffffffu, entry->edx);
    }
    table = port_u32(&port, 0, 0x507c8c);
    hook = port_u32(&port, 0, 0x507d08);
    system = port_u32(&port, table + handle * 4, 0);
    edx = table;
    if (hook != 0)
    {
        uint32_t closer = port_call_with(&port, port_u32(&port, 0, 0x507cfc), handle, table, handle,
                                         0, 0, system, hook);
        eax = closer;
        edx = closer;
        if (closer != 0)
        {
            port_call_with(&port, port_u32(&port, 0, 0x507d00), handle, closer, handle, 0, 0,
                           system, hook);
            port_call_with(&port, port_u32(&port, 0, 0x507d08), vertrix_lift_edx, vertrix_lift_edx,
                           handle, 0, 0, system, hook);
            closed = 1;
        }
    }
    if (!closed)
    {
        pushed[0] = system;
        if (call_frame(&port, 0x4f1b2c, eax, edx, handle, 0, 0, system, hook, pushed, 1) == 0)
        {
            port_call_with(&port, 0x4dae70, 4, vertrix_lift_edx, handle, 0, 0xffffffffu, system,
                           hook);
            return port_return(&port, 0xffffffffu, entry->edx);
        }
    }
    port_call_with(&port, 0x4e0228, handle, 0, handle, 0, 0, system, hook);
    return port_return(&port, 0, entry->edx);
}

/* Original 0x4e3b60: the stream eax (0x4e7bf0 on it; the edx it leaves) takes a buffer of its
 * size +0x14 (0x86 when bit 1 of +0xd, 1 when bit 2, otherwise 0x1000) from 0x4e7c90 (on the edx
 * it leaves) at +8 of +8, or, without one, its own byte +0x18 (size 1, +0xd bits 0 to 2 4);
 * with one +0xc gains bit 3. The pointer (+0) is the buffer, the count (+4) 0. */
uint32_t vertrix_port_crt_stream_buffer_4e3b60(PORT_SIGNATURE)
{
    Port port;
    uint32_t stream;
    uint32_t info;
    uint32_t buffer;
    port_open(&port, calls, services, globals, entry);
    port_forward(&port, entry, 0x4e7bf0, entry->eax, entry->eax, entry->ebx, entry->ecx);
    stream = vertrix_lift_edx;
    if (port_u32(&port, stream, 0x14) == 0)
    {
        uint32_t mode = port_u8(&port, stream, 0xd);
        if ((mode & 2) != 0)
        {
            port_set32(&port, stream, 0x14, 0x86);
        }
        else if ((mode & 4) != 0)
        {
            port_set32(&port, stream, 0x14, 1);
        }
        else
        {
            port_set32(&port, stream, 0x14, 0x1000);
        }
    }
    buffer = port_forward(&port, entry, 0x4e7c90, port_u32(&port, stream, 0x14), stream, entry->ebx,
                          entry->ecx);
    stream = vertrix_lift_edx;
    info = port_u32(&port, stream, 8);
    port_set32(&port, info, 8, buffer);
    if (port_u32(&port, port_u32(&port, stream, 8), 8) == 0)
    {
        uint32_t mode = port_u8(&port, stream, 0xd) & 0xf8;
        port_set8(&port, stream, 0xd, mode);
        port_set8(&port, stream, 0xd, mode | 4);
        port_set32(&port, port_u32(&port, stream, 8), 8, stream + 0x18);
        port_set32(&port, stream, 0x14, 1);
    }
    else
    {
        port_set8(&port, stream, 0xc, port_u8(&port, stream, 0xc) | 8);
    }
    buffer = port_u32(&port, port_u32(&port, stream, 8), 8);
    port_set32(&port, stream, 4, 0);
    port_set32(&port, stream, 0, buffer);
    return port_return(&port, buffer, entry->edx);
}

/* Original 0x4e4080: up to ebx characters of the texts eax and edx compared: until either ends
 * (0x4e7b50) by 0x4e81d0, stepping both (0x4e3a90); then the difference of the current bytes
 * when either ended early. eax and edx the result. */
uint32_t vertrix_port_crt_text_compare_4e4080(PORT_SIGNATURE)
{
    Port port;
    uint32_t left = entry->eax;
    uint32_t right = entry->edx;
    uint32_t count = entry->ebx;
    uint32_t edx = 0;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    while (count != 0)
    {
        if (port_forward_esi(&port, entry, 0x4e7b50, left, edx, count, left, right) != 0)
        {
            edx = vertrix_lift_edx;
            break;
        }
        if (port_forward_esi(&port, entry, 0x4e7b50, right, vertrix_lift_edx, count, left, right) !=
            0)
        {
            edx = vertrix_lift_edx;
            break;
        }
        result = port_forward_esi(&port, entry, 0x4e81d0, left, right, count, left, right);
        if (result != 0)
        {
            return port_return(&port, result, result);
        }
        left = port_forward_esi(&port, entry, 0x4e3a90, left, 0, count, left, right);
        count--;
        right =
            port_forward_esi(&port, entry, 0x4e3a90, right, vertrix_lift_edx, count, left, right);
        edx = vertrix_lift_edx;
    }
    if (count == 0)
    {
        return port_return(&port, edx, edx);
    }
    if (port_forward_esi(&port, entry, 0x4e7b50, left, edx, count, left, right) == 0 &&
        port_forward_esi(&port, entry, 0x4e7b50, right, vertrix_lift_edx, count, left, right) == 0)
    {
        return port_return(&port, vertrix_lift_edx, vertrix_lift_edx);
    }
    result = port_u8(&port, left, 0) - port_u8(&port, right, 0);
    return port_return(&port, result, result);
}

/* Original 0x4e6510: the text eax converted into the wide buffer edx of ebx characters: before
 * the wide system (version 0x8000 and up, slot 0x4f1c00) by slot 0x4f1bc8; otherwise through a
 * 0x208 byte buffer (0x4e7c90, slot 0x4f1bc4, MultiByteToWideChar slot 0x4f1c6c, freed by
 * 0x4ea190), the last character cleared and the length 0x4d8580 gives. 0 on failure. */
uint32_t vertrix_port_crt_text_to_wide_4e6510(PORT_SIGNATURE)
{
    Port port;
    uint32_t text = entry->eax;
    uint32_t wide = entry->edx;
    uint32_t size = entry->ebx;
    uint32_t version;
    uint32_t buffer;
    uint32_t result;
    uint32_t pushed[6];
    port_open(&port, calls, services, globals, entry);
    version = call_frame(&port, 0x4f1c00, entry->eax, entry->edx, entry->ebx, entry->ecx, wide,
                         size, text, NULL, 0);
    version = (version >> 16) & 0xffff;
    if (version < 0x8000)
    {
        pushed[0] = text;
        pushed[1] = wide;
        pushed[2] = size;
        result = call_frame(&port, 0x4f1bc8, version, vertrix_lift_edx, entry->ebx, entry->ecx,
                            wide, size, text, pushed, 3);
        return port_return(&port, result, vertrix_lift_edx);
    }
    buffer = port_call_with(&port, 0x4e7c90, 0x208, vertrix_lift_edx, entry->ebx, entry->ecx, wide,
                            size, text);
    if (buffer == 0)
    {
        return port_return(&port, 0, vertrix_lift_edx);
    }
    pushed[0] = text;
    pushed[1] = buffer;
    pushed[2] = 0x208;
    result = call_frame(&port, 0x4f1bc4, buffer, vertrix_lift_edx, buffer, entry->ecx, wide, size,
                        text, pushed, 3);
    if (result == 0)
    {
        port_call_with(&port, 0x4ea190, buffer, vertrix_lift_edx, buffer, entry->ecx, wide, size,
                       text);
        return port_return(&port, 0, vertrix_lift_edx);
    }
    pushed[0] = 1;
    pushed[1] = 1;
    pushed[2] = buffer;
    pushed[3] = 0xffffffffu;
    pushed[4] = wide;
    pushed[5] = size;
    result = call_frame(&port, 0x4f1c6c, result, vertrix_lift_edx, buffer, entry->ecx, wide, size,
                        text, pushed, 6);
    port_call_with(&port, 0x4ea190, buffer, vertrix_lift_edx, buffer, entry->ecx, wide, size,
                   result);
    if (result == 0)
    {
        return port_return(&port, 0, vertrix_lift_edx);
    }
    port_set16(&port, wide + size * 2, -2u, 0);
    result = port_call_with(&port, 0x4d8580, wide, vertrix_lift_edx, buffer, entry->ecx, wide, size,
                            result);
    return port_return(&port, result, vertrix_lift_edx);
}

/* The extended float wrappers 0x4edd24 and 0x4ee0dc: the ten byte values eax and edx loaded into
 * registers (their exponents in esi) for `operation`, the result stored at ebx. */
static uint32_t extended_operation(PORT_SIGNATURE, uint32_t operation)
{
    Port port;
    uint32_t left = entry->eax;
    uint32_t right = entry->edx;
    uint32_t esi;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    esi = (port_u16(&port, right, 8) << 16) | port_u16(&port, left, 8);
    result = port_forward_esi(&port, entry, operation, port_u32(&port, left, 0),
                              port_u32(&port, left, 4), port_u32(&port, right, 0),
                              port_u32(&port, right, 4), esi);
    port_set32(&port, entry->ebx, 0, result);
    port_set32(&port, entry->ebx, 4, vertrix_lift_edx);
    port_set16(&port, entry->ebx, 8, esi);
    return port_return(&port, result, vertrix_lift_edx);
}

/* Original 0x4edd24: 0x4eddc4. */
uint32_t vertrix_port_rtl_extended_op_4edd24(PORT_SIGNATURE)
{
    return extended_operation(calls, services, globals, entry, 0x4eddc4);
}

/* Original 0x4ee0dc: 0x4ee160. */
uint32_t vertrix_port_rtl_extended_op_4ee0dc(PORT_SIGNATURE)
{
    return extended_operation(calls, services, globals, entry, 0x4ee160);
}
