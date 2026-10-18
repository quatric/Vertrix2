#include "widgets.h"

/* Scroll, layout, hit test and release helpers of interface objects, and actor counters. */

/* A call handing the callee esi, edi and ebp as given. */
static uint32_t call_registers(Port *port, uint32_t target, uint32_t eax, uint32_t edx,
                               uint32_t ebx, uint32_t ecx, uint32_t esi, uint32_t edi, uint32_t ebp)
{
    return port_call_registers(port, target, eax, edx, ebx, ecx, esi, edi, ebp, NULL, 0);
}

/* The guard record (0x4ec1ec, `guard`) of a frame routine at ebp -0x24. */
static void guard_record(Port *port, uint32_t ebp, uint32_t guard)
{
    port_set32(port, ebp, -0x24u, port->env.chain);
    port_set32(port, ebp, -0x20u, 0x4ec1ec);
    port_set32(port, ebp, -0x1cu, guard);
    port_set32(port, ebp, -0x18u, 0);
}

/* Original 0x48c610: when 0x47f900 gives 1, the options word +0x20 of eax unpacked into the
 * level 0x532bbc (bits 7-8), 0x532bc0 (bits 3-6), 0x532bc4 (bit 2), 0x532bc8 (bit 1) and 0x532bcc
 * (bit 0), and 0x532b8c its +0x28; the answer of 0x47f900. */
uint32_t vertrix_port_options_unpack_48c610(PORT_SIGNATURE)
{
    Port port;
    uint32_t options = entry->eax;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    result = port_forward(&port, entry, 0x47f900, options, options, entry->ebx, entry->ecx);
    if (result != 1)
    {
        return port_return(&port, result, entry->edx);
    }
    port_set32(&port, 0, 0x532bbc, (port_u32(&port, options, 0x20) & 0x180) >> 7);
    port_set32(&port, 0, 0x532bc0, (port_u32(&port, options, 0x20) & 0x78) >> 3);
    port_set32(&port, 0, 0x532bc4, (port_u32(&port, options, 0x20) & 4) >> 2);
    port_set32(&port, 0, 0x532bc8, (port_u32(&port, options, 0x20) & 2) >> 1);
    port_set32(&port, 0, 0x532bcc, port_u32(&port, options, 0x20) & result);
    port_set32(&port, 0, 0x532b8c, port_u32(&port, options, 0x28));
    return port_return(&port, result, entry->edx);
}

/* Original 0x4ac980: ebx stepped toward ecx by edx times the stack argument, not past it (signed);
 * edx the step. */
uint32_t vertrix_port_step_toward_4ac980(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0
    };
    Port port;
    uint8_t stack[BELOW + 8 + 4];
    int32_t value = (int32_t)entry->ebx;
    int32_t target = (int32_t)entry->ecx;
    uint32_t step;
    port_open_arguments(&port, stack, calls, services, globals, entry, BELOW, 1);
    step = entry->edx * port_u32(&port, entry->esp, 4);
    if (value > target)
    {
        value -= (int32_t)step;
        if (value < target)
        {
            value = target;
        }
    }
    else if (value < target)
    {
        value += (int32_t)step;
        if (value > target)
        {
            value = target;
        }
    }
    return port_return(&port, (uint32_t)value, step);
}

/* Original 0x4accc0: edx times the actor's counter +0x80 grows by +0x88; past 254 it wraps
 * (remainder of 255) and the answer is 0, otherwise 1. 0x5bb5cc keeps the answer and 0x5bb5d0
 * the count. */
uint32_t vertrix_port_actor_counter_advance_4accc0(PORT_SIGNATURE)
{
    Port port;
    uint32_t actor = entry->eax;
    uint32_t times = entry->edx;
    uint32_t edx = entry->edx;
    uint32_t done = 1;
    uint32_t count;
    port_open(&port, calls, services, globals, entry);
    for (count = 0; count < times; count++)
    {
        int32_t value = (int32_t)(port_u32(&port, actor, 0x80) + port_u32(&port, actor, 0x88));
        port_set32(&port, actor, 0x80, (uint32_t)value);
        edx = (uint32_t)value;
        if (value >= 0xff)
        {
            value -= 0xff;
            port_set32(&port, actor, 0x80, (uint32_t)value);
            edx = (uint32_t)(value % 0xff);
            done = 0;
            port_set32(&port, actor, 0x80, edx);
        }
    }
    port_set32(&port, 0, 0x5bb5cc, done);
    port_set32(&port, 0, 0x5bb5d0, count);
    return port_return(&port, done, edx);
}

/* The scrolls of 0x4b3ce0, 0x4b3d60 and 0x4b5050 under the guard record `guard`: the position
 * `at` moves toward the limit `limit` (down for `down`) by at most edx, by `move` with 1;
 * 1 when it moved, otherwise 0. */
static uint32_t object_scroll(PORT_SIGNATURE, uint32_t guard, uint32_t at, uint32_t limit, int down,
                              uint32_t move)
{
    enum
    {
        BELOW = 0x28
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t object = entry->eax;
    uint32_t most = entry->edx;
    uint32_t position;
    uint32_t edge;
    uint32_t moved = 0;
    uint32_t edx;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    guard_record(&port, ebp, guard);
    position = port_u32(&port, object, at);
    edge = port_u32(&port, object, limit);
    edx = position;
    if (down ? position > edge : position < edge)
    {
        if (down)
        {
            edx = position - edge > most ? position - most : edge;
        }
        else
        {
            edx = edge - position > most ? position + most : edge;
        }
        moved = 1;
        call_registers(&port, move, object, edx, 1, object, most, 0, ebp);
        edx = vertrix_lift_edx;
    }
    return port_return(&port, moved, edx);
}

/* Original 0x4b3ce0: +0x18c down to +0x184 by 0x4b3c40, guard 0x517d7c. */
uint32_t vertrix_port_object_scroll_up_4b3ce0(PORT_SIGNATURE)
{
    return object_scroll(calls, services, globals, entry, 0x517d7c, 0x18c, 0x184, 1, 0x4b3c40);
}

/* Original 0x4b3d60: +0x18c up to +0x188 by 0x4b3c40, guard 0x517d80. */
uint32_t vertrix_port_object_scroll_down_4b3d60(PORT_SIGNATURE)
{
    return object_scroll(calls, services, globals, entry, 0x517d80, 0x18c, 0x188, 0, 0x4b3c40);
}

/* Original 0x4b5050: +0x190 down to +0x188 by 0x4b4fb0, guard 0x5180ac. */
uint32_t vertrix_port_object_scroll_up_4b5050(PORT_SIGNATURE)
{
    return object_scroll(calls, services, globals, entry, 0x5180ac, 0x190, 0x188, 1, 0x4b4fb0);
}

/* The layouts of 0x4b3f30 and 0x4b41f0: method +4 of the parts `first` and `second`, 0x4b3390,
 * then the first part at the object's place (+0xe, +0x16) and the second at its right edge (+0xe
 * and +0xf4 less the second's width, +4 of its +0xb4) at the same height. The object is the edx
 * each call leaves. */
static uint32_t object_layout(PORT_SIGNATURE, uint32_t first, uint32_t second)
{
    Port port;
    uint32_t object = entry->eax;
    uint32_t part;
    uint32_t methods;
    uint32_t right;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    part = port_u32(&port, object, first);
    methods = port_u32(&port, part, 0x158);
    port_forward(&port, entry, port_u32(&port, methods, 4), part, object, entry->ebx, methods);
    object = vertrix_lift_edx;
    part = port_u32(&port, object, second);
    methods = port_u32(&port, part, 0x158);
    port_forward(&port, entry, port_u32(&port, methods, 4), part, object, entry->ebx, methods);
    object = vertrix_lift_edx;
    result = port_forward(&port, entry, 0x4b3390, object, object, entry->ebx, methods);
    object = vertrix_lift_edx;
    port_set16(&port, port_u32(&port, object, first), 0xe, port_u16(&port, object, 0xe));
    port_set16(&port, port_u32(&port, object, first), 0x16, port_u16(&port, object, 0x16));
    part = port_u32(&port, object, second);
    right = port_u16(&port, object, 0xf4) + port_u16(&port, object, 0xe) -
            port_u16(&port, port_u32(&port, part, 0xb4), 4);
    port_set16(&port, part, 0xe, right);
    part = port_u32(&port, object, second);
    result = (part & 0xffff0000u) | port_u16(&port, object, 0x16);
    port_set16(&port, part, 0x16, result);
    return port_return(&port, result, entry->edx);
}

/* Original 0x4b3f30: the parts +0x170 and +0x174. */
uint32_t vertrix_port_object_layout_4b3f30(PORT_SIGNATURE)
{
    return object_layout(calls, services, globals, entry, 0x170, 0x174);
}

/* Original 0x4b41f0: the parts +0x17c and +0x180. */
uint32_t vertrix_port_object_layout_4b41f0(PORT_SIGNATURE)
{
    return object_layout(calls, services, globals, entry, 0x17c, 0x180);
}

/* Original 0x4b4270: whether the point edx, ebx (signed) lies in the object: from its place (+0xe
 * and +0x16 words) plus the first part's width (+0x17c, +0xb4, +4) to its size (+0xf4, +0xf8)
 * less the second part's width (+0x180) and 1. */
uint32_t vertrix_port_object_contains_point_4b4270(PORT_SIGNATURE)
{
    Port port;
    uint32_t object = entry->eax;
    int32_t x = (int32_t)entry->edx;
    int32_t y = (int32_t)entry->ebx;
    int32_t left;
    int32_t top;
    int32_t right;
    int32_t bottom;
    int32_t place;
    port_open(&port, calls, services, globals, entry);
    place = (int16_t)port_u16(&port, object, 0xe);
    left =
        (int32_t)port_u32(&port, port_u32(&port, port_u32(&port, object, 0x17c), 0xb4), 4) + place;
    right = (int32_t)port_u32(&port, object, 0xf4) + place -
            (int32_t)port_u32(&port, port_u32(&port, port_u32(&port, object, 0x180), 0xb4), 4) - 1;
    top = (int16_t)port_u16(&port, object, 0x16);
    bottom = (int32_t)port_u32(&port, object, 0xf8) + top - 1;
    if (x < left || y < top || x > right || y > bottom)
    {
        return port_return(&port, 0, entry->edx);
    }
    return port_return(&port, 1, entry->edx);
}

/* Original 0x4b5d40: 0 without a slot (word +0x15c) or when 0x476480 (0x54d640) does not hold
 * for it; otherwise 1, after 0x4762e0 frees it when the object has no owner (+0x160). */
uint32_t vertrix_port_object_slot_present_unowned_4b5d40(PORT_SIGNATURE)
{
    Port port;
    uint32_t object = entry->eax;
    uint32_t slot;
    port_open(&port, calls, services, globals, entry);
    slot = port_u16(&port, object, 0x15c);
    if (slot == 0)
    {
        return port_return(&port, 0, entry->edx);
    }
    if (port_forward(&port, entry, 0x476480, 0x54d640, slot, 0, object) != 1)
    {
        return port_return(&port, 0, entry->edx);
    }
    if (port_u32(&port, object, 0x160) == 0)
    {
        port_forward(&port, entry, 0x4762e0, 0x54d640,
                     (vertrix_lift_edx & 0xffff0000u) | port_u16(&port, object, 0x15c), 0, object);
    }
    return port_return(&port, 1, entry->edx);
}

/* Original 0x4b5ee0: the entries edx to edx + ebx of the list +4 (those set) destroyed by their
 * method +0 (table +0x158) with 2, then 0x4d8950 with edx and ebx. */
uint32_t vertrix_port_object_list_release_4b5ee0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x1c
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t list = entry->eax;
    uint32_t index = entry->edx;
    uint32_t end = entry->edx + entry->ebx;
    uint32_t offset = entry->edx << 2;
    uint32_t esi = end;
    uint32_t result;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, -0x14u, entry->edx);
    port_set32(&port, ebp, -0x18u, entry->ebx);
    port_set32(&port, ebp, -0x10u, end);
    for (; index < end; index++, offset += 4)
    {
        uint32_t item = port_u32(&port, port_u32(&port, list, 4), offset);
        if (item != 0)
        {
            esi = port_u32(&port, item, 0x158);
            call_registers(&port, port_u32(&port, esi, 0), item, 2, index, offset, esi, list, ebp);
        }
    }
    result = call_registers(&port, 0x4d8950, list, entry->edx, entry->ebx, offset, esi, list, ebp);
    return port_return(&port, result, vertrix_lift_edx);
}

/* Original 0x48b770: 0x48b970, 0x48d6c0 on +0x1ec, +0x200 and +0x214, then 0x47e780; the object
 * is the edx each call leaves. */
uint32_t vertrix_port_object_release_parts_48b770(PORT_SIGNATURE)
{
    Port port;
    uint32_t object = entry->eax;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    port_forward(&port, entry, 0x48b970, object, object, entry->ebx, entry->ecx);
    object = vertrix_lift_edx;
    port_forward(&port, entry, 0x48d6c0, object + 0x1ec, object, entry->ebx, entry->ecx);
    object = vertrix_lift_edx;
    port_forward(&port, entry, 0x48d6c0, object + 0x200, object, entry->ebx, entry->ecx);
    object = vertrix_lift_edx;
    port_forward(&port, entry, 0x48d6c0, object + 0x214, object, entry->ebx, entry->ecx);
    object = vertrix_lift_edx;
    result = port_forward(&port, entry, 0x47e780, object, object, entry->ebx, entry->ecx);
    return port_return(&port, result, entry->edx);
}
