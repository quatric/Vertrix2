#include "port_texts.h"

/* Text conversion, object teardown, interface queries, stream reads, display settings, record
 * copies, list cycling and label formatting. */

/* A call handing the callee esi, edi and ebp as given and `count` stack dwords. */
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

/* The guard record (0x4ec1ec, `guard`) of a frame routine at `record`. */
static void guard_record(Port *port, uint32_t record, uint32_t guard)
{
    port_set32(port, record, 0, port->env.chain);
    port_set32(port, record, 4, 0x4ec1ec);
    port_set32(port, record, 8, guard);
    port_set32(port, record, 0xc, 0);
}

/* Original 0x47fc50: the wide text ebx converted into the buffer edx of ecx bytes (its length and
 * the terminator by 0x4d8580 when ecx is -1) by WideCharToMultiByte (slot 0x4f1d00), the last
 * byte cleared. Nothing without both buffers. */
uint32_t vertrix_port_text_from_wide_47fc50(PORT_SIGNATURE)
{
    Port port;
    uint32_t buffer = entry->edx;
    uint32_t text = entry->ebx;
    uint32_t size = entry->ecx;
    uint32_t pushed[8];
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    if (buffer == 0 || text == 0)
    {
        return port_return(&port, entry->eax, text);
    }
    if (entry->ecx == 0xffffffffu)
    {
        size =
            port_forward_esi(&port, entry, 0x4d8580, text, text, entry->ecx, entry->ecx, buffer) +
            1;
        text = vertrix_lift_edx;
    }
    pushed[0] = 0;
    pushed[1] = 0;
    pushed[2] = text;
    pushed[3] = 0xffffffffu;
    pushed[4] = buffer;
    pushed[5] = size - 1;
    pushed[6] = 0;
    pushed[7] = 0;
    result = port_forward_stack(&port, entry, 0x4f1d00, size - 1, text, size, entry->ecx, buffer,
                                pushed, 8);
    port_set8(&port, buffer + size, -1u, 0);
    return port_return(&port, result, vertrix_lift_edx);
}

/* Original 0x481fb0: the object's teardown by the flags dl: with bit 2 0x4ccb9f (0x516bc0) and
 * 0x4ca040; otherwise (guarded, 0x516b24) its methods 0x516b84 (+0x20c), 0x4823b0 with 0 and,
 * with bit 1, 0x4ca050 on what it gives. The object, or that. */
uint32_t vertrix_port_object_destroy_b_481fb0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x48
    };
    Port port;
    uint8_t stack[BELOW + 8];
    uint32_t ebp = entry->esp - 4;
    uint32_t object = entry->eax;
    uint32_t flags = entry->edx;
    uint32_t result;
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    if ((flags & 4) != 0)
    {
        port_set32(&port, ebp, -0x44u, object);
        port_set32(&port, ebp, -0x24u, 1);
        result = port_call_with(&port, 0x4ccb9f, object, 0x516bc0, 1, object, 0, entry->edi, ebp);
        port_set32(&port, ebp, -0x24u, 0);
        port_call_with(&port, 0x4ca040, result, vertrix_lift_edx, 1, object, 0, entry->edi, ebp);
        return port_return(&port, object, vertrix_lift_edx);
    }
    port_set32(&port, object, 0x20c, 0x516b84);
    port_set32(&port, ebp, -0x1cu, object);
    port_set8(&port, ebp, -0x18u, flags);
    guard_record(&port, ebp - 0x30, 0x516b24);
    result = port_call_with(&port, 0x4823b0, object, 0, flags, object, 0x516b24, 0, ebp);
    port_set32(&port, ebp, -0x24u, 0);
    if ((flags & 2) != 0)
    {
        port_call_with(&port, 0x4ca050, result, vertrix_lift_edx, flags, result, 0x516b24, 0, ebp);
    }
    return port_return(&port, result, vertrix_lift_edx);
}

/* Original 0x487130: whether the device (+0x68) answers the query (+0x5c 1: its method +0x1c on
 * the state +0x64 into a 16 byte frame; otherwise its method +0x14 with 0x1000000 and 100) with
 * 0. The frame holds the size words +0x3e and +0x40. */
uint32_t vertrix_port_device_query_487130(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x88
    };
    Port port;
    uint8_t stack[BELOW + 8];
    uint32_t ebp = entry->esp - 4;
    uint32_t object = entry->eax;
    uint32_t device;
    uint32_t methods;
    uint32_t state;
    uint32_t pushed[6];
    uint32_t result;
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, -0x84u, 0x64);
    port_set32(&port, ebp, -0x20u, 0);
    port_set32(&port, ebp, -0x1cu, 0);
    port_set32(&port, ebp, -0x18u, port_u16(&port, object, 0x3e));
    port_set32(&port, ebp, -0x14u, port_u16(&port, object, 0x40));
    state = port_u32(&port, object, 0x64);
    device = port_u32(&port, object, 0x68);
    methods = port_u32(&port, device, 0);
    if (port_u32(&port, object, 0x5c) == 1)
    {
        pushed[0] = device;
        pushed[1] = 0;
        pushed[2] = 0;
        pushed[3] = state;
        pushed[4] = ebp - 0x20;
        pushed[5] = 0x10;
        result = call_frame(&port, port_u32(&port, methods, 0x1c), device, object, methods,
                            ebp - 0x20, state, entry->edi, ebp, pushed, 6);
    }
    else
    {
        pushed[0] = device;
        pushed[1] = ebp - 0x20;
        pushed[2] = state;
        pushed[3] = ebp - 0x20;
        pushed[4] = 0x1000000;
        pushed[5] = ebp - 0x84;
        result = call_frame(&port, port_u32(&port, methods, 0x14), device, ebp - 0x20, state,
                            methods, entry->esi, entry->edi, ebp, pushed, 6);
    }
    return port_return(&port, result == 0, entry->edx);
}

/* Original 0x48a9d0: up to ebx times ecx bytes (0x5bb244) of the stream's data (+4 to its end
 * +8, the room in 0x5bb248) copied to edx and the stream advanced; the count is in 0x5bb240 and
 * 0x5bb23c. */
uint32_t vertrix_port_stream_read_48a9d0(PORT_SIGNATURE)
{
    Port port;
    uint32_t stream = entry->eax;
    uint32_t want = entry->ebx * entry->ecx;
    uint32_t room;
    uint32_t count;
    uint32_t from;
    uint32_t k;
    port_open(&port, calls, services, globals, entry);
    port_set32(&port, 0, 0x5bb244, want);
    room = port_u32(&port, stream, 8) - port_u32(&port, stream, 4);
    port_set32(&port, 0, 0x5bb248, room);
    count = port_u32(&port, 0, 0x5bb244);
    if (count > port_u32(&port, 0, 0x5bb248))
    {
        count = port_u32(&port, 0, 0x5bb248);
    }
    port_set32(&port, 0, 0x5bb240, count);
    if (count == 0)
    {
        port_set32(&port, 0, 0x5bb23c, count);
        return port_return(&port, port_u32(&port, 0, 0x5bb240), entry->edx);
    }
    port_set32(&port, 0, 0x5bb23c, count);
    from = port_u32(&port, stream, 4);
    for (k = 0; k < (count & ~3u); k += 4)
    {
        port_set32(&port, entry->edx + k, 0, port_u32(&port, from + k, 0));
    }
    for (; k < count; k++)
    {
        port_set8(&port, entry->edx + k, 0, port_u8(&port, from + k, 0));
    }
    count = port_u32(&port, 0, 0x5bb23c);
    port_set32(&port, stream, 4, port_u32(&port, stream, 4) + count);
    port_set32(&port, 0, 0x5bb23c, count);
    return port_return(&port, port_u32(&port, 0, 0x5bb240), stream);
}

/* Original 0x48c3d0: the display's settings: 0x47ed50 with 0x532be8, 0x47f8e0 with 2, 0x47ed60
 * with the flags 0x532be4, 0x532be0 (bit 1), 0x532bdc (2), 0x532bd8 (3) and 0x532bd4 (7),
 * 0x47ed70 with 0x4f7b40, 0x47ed80 with 0x532b88, 0x47ed90 with 1 and 0x47eda0. */
uint32_t vertrix_port_display_settings_apply_48c3d0(PORT_SIGNATURE)
{
    Port port;
    uint32_t display = entry->eax;
    uint32_t flags;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    port_forward(&port, entry, 0x47ed50, display, port_u32(&port, 0, 0x532be8), entry->ebx,
                 display);
    port_forward(&port, entry, 0x47f8e0, display, 2, entry->ebx, display);
    flags = port_u32(&port, 0, 0x532be4) | (port_u32(&port, 0, 0x532be0) * 2) |
            (port_u32(&port, 0, 0x532bdc) << 2) | (port_u32(&port, 0, 0x532bd8) << 3) |
            (port_u32(&port, 0, 0x532bd4) << 7);
    port_forward(&port, entry, 0x47ed60, display, flags, entry->ebx, display);
    port_forward(&port, entry, 0x47ed70, display, port_u32(&port, 0, 0x4f7b40), entry->ebx,
                 display);
    port_forward(&port, entry, 0x47ed80, display, port_u32(&port, 0, 0x532b88), entry->ebx,
                 display);
    port_forward(&port, entry, 0x47ed90, display, 1, entry->ebx, display);
    result = port_forward(&port, entry, 0x47eda0, display, vertrix_lift_edx, entry->ebx, display);
    return port_return(&port, result, entry->edx);
}

/* Original 0x48d3e0: the 0x34 byte record edx copied to eax (bytes 0 to 3, 8 to 0xb, 4 to 7 and
 * 0xc to 0xf one at a time, then dwords); edx the last dword. */
uint32_t vertrix_port_record_copy_48d3e0(PORT_SIGNATURE)
{
    static const uint8_t bytes[16] = {0, 1, 2, 3, 8, 9, 0xa, 0xb, 4, 5, 6, 7, 0xc, 0xd, 0xe, 0xf};
    Port port;
    uint32_t to = entry->eax;
    uint32_t from = entry->edx;
    uint32_t k;
    uint32_t last;
    port_open(&port, calls, services, globals, entry);
    for (k = 0; k < 16; k++)
    {
        port_set8(&port, to, bytes[k], port_u8(&port, from, bytes[k]));
    }
    for (k = 0x10; k < 0x30; k += 4)
    {
        port_set32(&port, to, k, port_u32(&port, from, k));
    }
    last = port_u32(&port, from, 0x30);
    port_set32(&port, to, 0x30, last);
    return port_return(&port, to, last);
}

/* The list cycles 0x4b3740 and 0x4b37e0: the last entry of the list (+0x170, +0x174) matching the
 * object's text (+0x160, +0x15c; 0x4ccfe0 gives 0) is found; the entry before it (`step` -1, from
 * the second on) or after it (`step` 1, up to the one before last) becomes the text (0x4ca370).
 * 1 when it moved, otherwise 0. */
static uint32_t list_cycle(PORT_SIGNATURE, int step)
{
    enum
    {
        BELOW = 0x1c
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t object = entry->eax;
    uint32_t found = 0xffffffffu;
    uint32_t k;
    uint32_t target;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, -0x18u, 0);
    for (k = 0; k < port_u32(&port, object, 0x174); k++)
    {
        uint32_t text = port_u32(&port, port_u32(&port, object, 0x160), 0x15c);
        uint32_t item = port_u32(&port, port_u32(&port, object, 0x170) + k * 4, 0);
        if (port_call_with(&port, 0x4ccfe0, item, text, object, k, k * 4, found, ebp) == 0)
        {
            found = k;
        }
    }
    if (found == 0xffffffffu)
    {
        return port_return(&port, port_u32(&port, ebp, -0x18u), entry->edx);
    }
    if (step < 0)
    {
        if ((int32_t)found <= 0)
        {
            return port_return(&port, port_u32(&port, ebp, -0x18u), entry->edx);
        }
        target = port_u32(&port, port_u32(&port, object, 0x170) + found * 4, -4u);
    }
    else
    {
        if (found >= port_u32(&port, object, 0x174) - 1)
        {
            return port_return(&port, port_u32(&port, ebp, -0x18u), entry->edx);
        }
        target = port_u32(&port, port_u32(&port, object, 0x170) + found * 4, 4);
    }
    port_call_with(&port, 0x4ca370, port_u32(&port, object, 0x160) + 0x15c, target, object, k,
                   k * 4, found, ebp);
    port_set32(&port, ebp, -0x18u, 1);
    return port_return(&port, 1, entry->edx);
}

/* Original 0x4b3740: back. */
uint32_t vertrix_port_list_cycle_4b3740(PORT_SIGNATURE)
{
    return list_cycle(calls, services, globals, entry, -1);
}

/* Original 0x4b37e0: on. */
uint32_t vertrix_port_list_cycle_4b37e0(PORT_SIGNATURE)
{
    return list_cycle(calls, services, globals, entry, 1);
}

/* The label formats 0x4b3c40 and 0x4b4fb0 (guarded, `guard`): the value edx kept at `field` and
 * printed by 0x4cdfb0 with `format` into a frame text (0x4ca070), set as the object's text
 * (+0x160, +0x15c; 0x4ca370) and released (0x4ca210). */
static uint32_t label_format(PORT_SIGNATURE, uint32_t guard, uint32_t field, uint32_t format)
{
    enum
    {
        BELOW = 0x2c
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t object = entry->eax;
    uint32_t pushed[3];
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    guard_record(&port, ebp - 0x28, guard);
    port_set32(&port, object, field, entry->edx);
    port_call_with(&port, 0x4ca070, ebp - 0x14, entry->edx, 0x4ec1ec, object, guard, 0, ebp);
    port_set32(&port, ebp, -0x1cu, 1);
    pushed[0] = ebp - 0x14;
    pushed[1] = format;
    pushed[2] = port_u32(&port, object, field);
    call_frame(&port, 0x4cdfb0, ebp - 0x14, pushed[2], 0x4ec1ec, object, guard, 0, ebp, pushed, 3);
    port_call_with(&port, 0x4ca370, port_u32(&port, object, 0x160) + 0x15c,
                   port_u32(&port, ebp, -0x14u), 0x4ec1ec, object, guard, 0, ebp);
    port_set32(&port, ebp, -0x1cu, 0);
    port_call_with(&port, 0x4ca210, ebp - 0x14, 0, 0x4ec1ec, object, guard, 0, ebp);
    port_set32(&port, ebp, -0x1cu, 0);
    return port_return(&port, port_u32(&port, ebp, -0x28u), vertrix_lift_edx);
}

/* Original 0x4b3c40: guard 0x517d70, +0x18c with 0x51108e. */
uint32_t vertrix_port_object_label_format_alternate_4b3c40(PORT_SIGNATURE)
{
    return label_format(calls, services, globals, entry, 0x517d70, 0x18c, 0x51108e);
}

/* Original 0x4b4fb0: guard 0x5180a0, +0x190 with 0x511094. */
uint32_t vertrix_port_object_label_format_4b4fb0(PORT_SIGNATURE)
{
    return label_format(calls, services, globals, entry, 0x5180a0, 0x190, 0x511094);
}

/* Original 0x4b7420 (guarded, 0x518544): the text edx set to 0x5110c2 (0x4ca280) and, when the
 * list eax holds the item ebx (0x4b6fa0), printed by 0x4cdfb0 with 0x5110c3 and its +0x18. The
 * text. */
uint32_t vertrix_port_list_text_format_4b7420(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x24
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t text = entry->edx;
    uint32_t item;
    uint32_t result;
    uint32_t pushed[3];
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    guard_record(&port, ebp - 0x20, 0x518544);
    item = port_call_with(&port, 0x4b6fa0, entry->eax, entry->ebx, 0x4ec1ec, text, entry->eax,
                          0x518544, ebp);
    result = port_call_with(&port, 0x4ca280, text, 0x5110c2, 0x4ec1ec, text, item, 0x518544, ebp);
    if (item != 0)
    {
        pushed[0] = text;
        pushed[1] = 0x5110c3;
        pushed[2] = port_u32(&port, item, 0x18);
        call_frame(&port, 0x4cdfb0, result, pushed[2], 0x4ec1ec, text, item, 0x518544, ebp, pushed,
                   3);
    }
    return port_return(&port, text, vertrix_lift_edx);
}

/* Original 0x4b9540: unless the decoder's state (+0x14) is 0xc8 or 0xc9 its handler (+0 of +0)
 * reports 0x14 with the state; then 0x4b95e0: 2 with edx set reports 0x33, and 0x4b9170 with 2
 * follows; 1 gives 1. eax and edx the result. */
uint32_t vertrix_port_decoder_header_check_4b9540(PORT_SIGNATURE)
{
    Port port;
    uint32_t decoder = entry->eax;
    uint32_t report;
    uint32_t result;
    uint32_t edx;
    port_open(&port, calls, services, globals, entry);
    edx = port_u32(&port, decoder, 0x14);
    if (edx != 0xc8 && edx != 0xc9)
    {
        report = port_u32(&port, decoder, 0);
        port_set32(&port, report, 0x14, 0x14);
        port_set32(&port, port_u32(&port, decoder, 0), 0x18, port_u32(&port, decoder, 0x14));
        report = port_u32(&port, decoder, 0);
        port_forward(&port, entry, port_u32(&port, report, 0), decoder, report, entry->edx,
                     decoder);
        edx = vertrix_lift_edx;
    }
    result = port_forward(&port, entry, 0x4b95e0, decoder, edx, entry->edx, decoder);
    if (result == 1)
    {
        return port_return(&port, 1, 1);
    }
    if (result != 2)
    {
        return port_return(&port, result, result);
    }
    if (entry->edx != 0)
    {
        port_set32(&port, port_u32(&port, decoder, 0), 0x14, 0x33);
        report = port_u32(&port, decoder, 0);
        port_forward(&port, entry, port_u32(&port, report, 0), decoder, report, entry->edx,
                     decoder);
    }
    port_forward(&port, entry, 0x4b9170, decoder, 2, entry->edx, decoder);
    return port_return(&port, vertrix_lift_edx, vertrix_lift_edx);
}
