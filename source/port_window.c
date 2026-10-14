#include "port_window.h"

/* Slot lists, window and device helpers of the runtime library, and checks on interfaces. */

/* A call with stack arguments and all of esi, edi and ebp given. */
static uint32_t call_stack_with(Port *port, uint32_t target, uint32_t eax, uint32_t edx,
                                uint32_t ebx, uint32_t ecx, uint32_t esi, uint32_t edi,
                                uint32_t ebp, const uint32_t *stack, unsigned count)
{
    uint32_t result;
    vertrix_lift_in_esi = esi;
    vertrix_lift_in_edi = edi;
    vertrix_lift_in_ebp = ebp;
    result = lift_call_arguments(&port->env, target, eax, edx, ebx, ecx, stack, count);
    vertrix_lift_in_esi = vertrix_lift_in_edi = vertrix_lift_in_ebp = 0;
    return result;
}

/* Original 0x48c680: the record 0x47f260 finds for eax and edx, inside the lock 0x558c9c
 * (imports 0x4f1b48 and 0x4f1c40); its dword +4, or 0. */
uint32_t vertrix_port_locked_record_value_48c680(PORT_SIGNATURE)
{
    Port port;
    uint32_t record;
    uint32_t lock[1] = {0x558c9c};
    port_open(&port, calls, services, globals, entry);
    port_forward_stack(&port, entry, 0x4f1b48, entry->eax, entry->edx, entry->edx, entry->ecx,
                       entry->eax, lock, 1);
    record = port_forward_esi(&port, entry, 0x47f260, entry->eax, entry->edx, entry->edx,
                              entry->ecx, entry->eax);
    port_forward_stack(&port, entry, 0x4f1c40, record, vertrix_lift_edx, record, entry->ecx,
                       entry->eax, lock, 1);
    return port_return(&port, record != 0 ? port_u32(&port, record, 4) : 0, vertrix_lift_edx);
}

/* Original 0x4b22c0: release each set object of the edx slots at eax by its first method (edx
 * 2) and clear the slot; edx the last slot or what its release leaves. */
uint32_t vertrix_port_object_release_slots_full_4b22c0(PORT_SIGNATURE)
{
    Port port;
    uint32_t result = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t at = entry->eax;
    uint32_t end = entry->eax + entry->edx * 4;
    port_open(&port, calls, services, globals, entry);
    if (entry->edx != 0)
    {
        do
        {
            uint32_t object = port_u32(&port, at, 0);
            edx = object;
            if (object != 0)
            {
                uint32_t methods = port_u32(&port, object, 0x158);
                result =
                    port_forward(&port, entry, port_u32(&port, methods, 0), object, 2, methods, at);
                edx = vertrix_lift_edx;
                port_set32(&port, at, 0, 0);
            }
            at += 4;
        } while (at < end);
    }
    return port_return(&port, result, edx);
}

/* Original 0x4b2300: whether every set object of the edx slots at eax has +0x154 equal to ebx;
 * edx the last slot read. */
uint32_t vertrix_port_object_slots_all_match_4b2300(PORT_SIGNATURE)
{
    Port port;
    uint32_t edx = entry->edx;
    uint32_t at = entry->eax;
    uint32_t end = entry->eax + entry->edx * 4;
    port_open(&port, calls, services, globals, entry);
    if (entry->edx != 0)
    {
        do
        {
            uint32_t object = port_u32(&port, at, 0);
            edx = object;
            if (object != 0 && entry->ebx != port_u32(&port, object, 0x154))
            {
                return port_return(&port, 0, edx);
            }
            at += 4;
        } while (at < end);
    }
    return port_return(&port, 1, edx);
}

/* Original 0x4b2340: the handler ebx for each set object of the edx slots at eax by 0x4ac8f0. */
uint32_t vertrix_port_object_slots_set_handler_4b2340(PORT_SIGNATURE)
{
    Port port;
    uint32_t result = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t at = entry->eax;
    uint32_t end = entry->eax + entry->edx * 4;
    port_open(&port, calls, services, globals, entry);
    if (entry->edx != 0)
    {
        do
        {
            uint32_t object = port_u32(&port, at, 0);
            edx = object;
            if (object != 0)
            {
                result = port_forward_esi(&port, entry, 0x4ac8f0, object, entry->ebx, entry->ebx,
                                          at, end);
                edx = vertrix_lift_edx;
            }
            at += 4;
        } while (at < end);
    }
    return port_return(&port, result, edx);
}

/* Original 0x4b66c0: whether the point (dx, bx) lies in the box +0x16a to +0x170, kept at
 * 0x5bd828. */
uint32_t vertrix_port_object_contains_4b66c0(PORT_SIGNATURE)
{
    Port port;
    int16_t x = (int16_t)entry->edx;
    int16_t y = (int16_t)entry->ebx;
    uint32_t inside;
    port_open(&port, calls, services, globals, entry);
    inside = !(x < (int16_t)port_u16(&port, entry->eax, 0x16a) ||
               y < (int16_t)port_u16(&port, entry->eax, 0x16e) ||
               x > (int16_t)port_u16(&port, entry->eax, 0x16c) ||
               y > (int16_t)port_u16(&port, entry->eax, 0x170));
    port_set32(&port, 0, 0x5bd828, inside);
    return port_return(&port, inside, entry->edx);
}

/* Original 0x4b9170: with a driver (+4), its call +0x24 (edx 1), then the rate +0x14 200 (and
 * +0x130 cleared) when +0x10 is set, else 100. */
uint32_t vertrix_port_driver_start_4b9170(PORT_SIGNATURE)
{
    Port port;
    uint32_t object = entry->eax;
    uint32_t driver;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    driver = port_u32(&port, object, 4);
    if (driver == 0)
    {
        return port_return(&port, object, entry->edx);
    }
    result = port_forward(&port, entry, port_u32(&port, driver, 0x24), object, 1, driver, object);
    if (port_u32(&port, object, 0x10) != 0)
    {
        port_set32(&port, object, 0x14, 0xc8);
        port_set32(&port, object, 0x130, 0);
    }
    else
    {
        port_set32(&port, object, 0x14, 0x64);
    }
    return port_return(&port, result, entry->edx);
}

/* Original 0x4b91b0: with a driver (+4), its call +0x28; then clear +4 and +0x14 (of the edx the
 * call leaves). */
uint32_t vertrix_port_driver_stop_4b91b0(PORT_SIGNATURE)
{
    Port port;
    uint32_t object = entry->eax;
    uint32_t driver;
    uint32_t result = object;
    port_open(&port, calls, services, globals, entry);
    driver = port_u32(&port, object, 4);
    if (driver != 0)
    {
        result = port_forward(&port, entry, port_u32(&port, driver, 0x28), object, object,
                              entry->ebx, driver);
        object = vertrix_lift_edx;
    }
    port_set32(&port, object, 4, 0);
    port_set32(&port, object, 0x14, 0);
    return port_return(&port, result, entry->edx);
}

/* Original 0x4c3ea0: the message of level edx by the error table's (+0) call +8: up to the trace
 * level +0x68; a warning (negative) the first time or from trace level 3, always counted at
 * +0x6c. */
uint32_t vertrix_port_error_emit_message_4c3ea0(PORT_SIGNATURE)
{
    Port port;
    uint32_t object = entry->eax;
    int32_t level = (int32_t)entry->edx;
    uint32_t table;
    uint32_t result = object;
    port_open(&port, calls, services, globals, entry);
    table = port_u32(&port, object, 0);
    if (level >= 0)
    {
        if (level > (int32_t)port_u32(&port, table, 0x68))
        {
            return port_return(&port, object, table);
        }
        result = port_forward(&port, entry, port_u32(&port, table, 8), object, table, entry->ebx,
                              entry->edx);
        return port_return(&port, result, vertrix_lift_edx);
    }
    if (port_u32(&port, table, 0x6c) == 0 || (int32_t)port_u32(&port, table, 0x68) >= 3)
    {
        result = port_forward(&port, entry, port_u32(&port, table, 8), object, table, entry->ebx,
                              entry->edx);
        table = vertrix_lift_edx;
    }
    port_set32(&port, table, 0x6c, port_u32(&port, table, 0x6c) + 1);
    return port_return(&port, result, table);
}

/* Original 0x4c5a00: 0x4c58e0 with edx 1 (ecx 0) and 0 (ecx -1), free the block +4 by 0x4c5bc0
 * (ebx 0x54), clear it and finish by 0x4c5c20. */
uint32_t vertrix_port_pool_close_4c5a00(PORT_SIGNATURE)
{
    Port port;
    uint32_t object = entry->eax;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    port_forward_esi(&port, entry, 0x4c58e0, object, 1, entry->ebx, 0, object);
    port_forward_esi(&port, entry, 0x4c58e0, object, 0, entry->ebx, 0xffffffff, object);
    port_forward_esi(&port, entry, 0x4c5bc0, object, port_u32(&port, object, 4), 0x54, 0xffffffff,
                     object);
    port_set32(&port, object, 4, 0);
    result = port_forward_esi(&port, entry, 0x4c5c20, object, vertrix_lift_edx, 0x54, 0xffffffff,
                              object);
    return port_return(&port, result, entry->edx);
}

/* Original 0x4ca730: convert the wide text edx into ebx bytes at eax by import 0x4f1d00,
 * terminated; the length (in edx too). 0 for no room at a buffer. */
uint32_t vertrix_port_wide_to_bytes_4ca730(PORT_SIGNATURE)
{
    Port port;
    uint32_t length;
    uint32_t pushed[8] = {0, 0, entry->edx, 0xffffffff, entry->eax, entry->ebx, 0, 0};
    port_open(&port, calls, services, globals, entry);
    if (entry->ebx == 0 && entry->eax != 0)
    {
        return port_return(&port, 0, entry->edx);
    }
    length = port_forward_stack(&port, entry, 0x4f1d00, entry->eax, entry->edx, entry->ebx,
                                entry->ecx, entry->eax, pushed, 8);
    if ((int32_t)length > 0)
    {
        port_set8(&port, entry->eax + length - 1, 0, 0);
    }
    return port_return(&port, length, length);
}

/* Original 0x4ca770: convert the text edx into ebx wide characters at eax by import 0x4f1c6c,
 * terminated; the length (in edx too). */
uint32_t vertrix_port_bytes_to_wide_4ca770(PORT_SIGNATURE)
{
    Port port;
    uint32_t length;
    uint32_t pushed[6] = {0, 0, entry->edx, 0xffffffff, entry->eax, entry->ebx};
    port_open(&port, calls, services, globals, entry);
    if (entry->ebx == 0 && entry->eax != 0)
    {
        return port_return(&port, 0, entry->edx);
    }
    length = port_forward_stack(&port, entry, 0x4f1c6c, entry->eax, entry->edx, entry->ebx,
                                entry->ecx, entry->eax, pushed, 6);
    if ((int32_t)length > 0)
    {
        port_set16(&port, entry->eax + length * 2 - 2, 0, 0);
    }
    return port_return(&port, length, length);
}

/* Original 0x4cc420: -1 for message kind 1 (+4 of ebx); for kind 15 the import 0x4f1b18 on the
 * window +0 with 0; otherwise 0. */
uint32_t vertrix_port_message_default_4cc420(PORT_SIGNATURE)
{
    Port port;
    uint32_t kind;
    uint32_t pushed[2];
    port_open(&port, calls, services, globals, entry);
    kind = port_u32(&port, entry->ebx, 4);
    if (kind == 1)
    {
        return port_return(&port, 0xffffffff, entry->edx);
    }
    if (kind != 0xf)
    {
        return port_return(&port, 0, entry->edx);
    }
    pushed[0] = port_u32(&port, entry->ebx, 0);
    pushed[1] = 0;
    port_forward_stack(&port, entry, 0x4f1b18, entry->eax, entry->edx, entry->ebx, entry->ecx,
                       entry->esi, pushed, 2);
    return port_return(&port, 0, vertrix_lift_edx);
}

/* Original 0x4cce00: the window's (+0x1c) import 0x4f1a24, or the method +0xa8 of the object
 * +0x38 when there is one. */
uint32_t vertrix_port_window_call_4cce00(PORT_SIGNATURE)
{
    Port port;
    uint32_t object;
    uint32_t methods;
    uint32_t result;
    uint32_t pushed[1];
    port_open(&port, calls, services, globals, entry);
    object = port_u32(&port, entry->eax, 0x38);
    if (object == 0)
    {
        pushed[0] = port_u32(&port, entry->eax, 0x1c);
        result = port_forward_stack(&port, entry, 0x4f1a24, entry->eax, entry->edx, entry->ebx,
                                    entry->ecx, entry->esi, pushed, 1);
        return port_return(&port, result, entry->edx);
    }
    methods = port_u32(&port, object, 0);
    result = port_forward(&port, entry, port_u32(&port, methods, 0xa8), object, methods, entry->ebx,
                          entry->ecx);
    return port_return(&port, result, entry->edx);
}

/* Original 0x4cce60: the object 0x4cf8e0 makes of the window's (+0x1c) import 0x4f1aa8, or the
 * method +0xb0 of the object +0x38 when there is one. */
uint32_t vertrix_port_window_object_4cce60(PORT_SIGNATURE)
{
    Port port;
    uint32_t object;
    uint32_t methods;
    uint32_t result;
    uint32_t pushed[1];
    port_open(&port, calls, services, globals, entry);
    object = port_u32(&port, entry->eax, 0x38);
    if (object == 0)
    {
        pushed[0] = port_u32(&port, entry->eax, 0x1c);
        result = port_forward_stack(&port, entry, 0x4f1aa8, entry->eax, entry->edx, entry->ebx,
                                    entry->ecx, entry->esi, pushed, 1);
        pushed[0] = result;
        result = port_forward_stack(&port, entry, 0x4cf8e0, result, vertrix_lift_edx, entry->ebx,
                                    entry->ecx, entry->esi, pushed, 1);
        return port_return(&port, result, entry->edx);
    }
    methods = port_u32(&port, object, 0);
    result = port_forward(&port, entry, port_u32(&port, methods, 0xb0), object, methods, entry->ebx,
                          entry->ecx);
    return port_return(&port, result, entry->edx);
}

/* Original 0x4cf940: attach the window edx: 0 for none; otherwise keep the handle 0x4cf880 (1)
 * leaves in edx at +0x1c, map it to the object by 0x4df160 and 0x4cce90 (1). */
uint32_t vertrix_port_window_attach_4cf940(PORT_SIGNATURE)
{
    Port port;
    uint32_t object = entry->eax;
    uint32_t map;
    uint32_t handle;
    uint32_t slot;
    port_open(&port, calls, services, globals, entry);
    if (entry->edx == 0)
    {
        return port_return(&port, 0, entry->edx);
    }
    map = port_forward(&port, entry, 0x4cf880, 1, entry->edx, entry->ebx, object);
    handle = vertrix_lift_edx;
    port_set32(&port, object, 0x1c, handle);
    slot = port_forward(&port, entry, 0x4df160, map, handle, map, object);
    port_set32(&port, slot, 0, object);
    port_forward(&port, entry, 0x4cce90, object, map, map, object);
    return port_return(&port, 1, vertrix_lift_edx);
}

/* Original 0x4d1900: the object 0x4cf8e0 makes of the topmost parent (0x4d1890) of the window
 * +0x1c; 0 without one. */
uint32_t vertrix_port_window_top_parent_4d1900(PORT_SIGNATURE)
{
    Port port;
    uint32_t window;
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t result;
    uint32_t pushed[1];
    port_open(&port, calls, services, globals, entry);
    if (entry->eax == 0)
    {
        return port_return(&port, 0, entry->edx);
    }
    window = port_u32(&port, entry->eax, 0x1c);
    if (window == 0)
    {
        return port_return(&port, 0, entry->edx);
    }
    for (;;)
    {
        pushed[0] = window;
        result = port_forward_stack(&port, entry, 0x4d1890, eax, edx, window, entry->ecx,
                                    entry->esi, pushed, 1);
        edx = vertrix_lift_edx;
        if (result == 0)
        {
            break;
        }
        window = result;
        eax = result;
    }
    pushed[0] = window;
    result = port_forward_stack(&port, entry, 0x4cf8e0, 0, edx, window, entry->ecx, entry->esi,
                                pushed, 1);
    return port_return(&port, result, entry->edx);
}

/* Original 0x4d2170: for the word kind edx 1 or 2, 0x4d1e80 on ebx and 0; when that is 0 or for
 * other kinds, 0x4cf850. */
uint32_t vertrix_port_command_route_4d2170(PORT_SIGNATURE)
{
    Port port;
    uint32_t kind = entry->edx & 0xffff;
    uint32_t edx = entry->edx;
    uint32_t result;
    uint32_t pushed[2] = {entry->ebx, 0};
    port_open(&port, calls, services, globals, entry);
    if (kind == 1 || kind == 2)
    {
        result = port_forward_stack(&port, entry, 0x4d1e80, kind, entry->edx, entry->ebx,
                                    entry->ecx, entry->eax, pushed, 2);
        if (result != 0)
        {
            return port_return(&port, result, vertrix_lift_edx);
        }
        edx = vertrix_lift_edx;
    }
    result = port_forward_esi(&port, entry, 0x4cf850, entry->eax, edx, entry->ebx, entry->ecx,
                              entry->eax);
    return port_return(&port, result, vertrix_lift_edx);
}

/* Original 0x4d21a0: for word edx 0, 0x4d04f0 with 1 unless bit 6 of +0xe3 of the state 0x4ce220
 * gives is set. Always 0. */
uint32_t vertrix_port_idle_check_4d21a0(PORT_SIGNATURE)
{
    Port port;
    uint32_t state;
    uint32_t pushed[1] = {1};
    port_open(&port, calls, services, globals, entry);
    if ((entry->edx & 0xffff) != 0)
    {
        return port_return(&port, 0, entry->edx);
    }
    state = port_forward(&port, entry, 0x4ce220, 0, entry->edx, entry->ebx, entry->ecx);
    if ((port_u8(&port, state, 0xe3) & 0x40) == 0)
    {
        port_forward_stack(&port, entry, 0x4d04f0, state, vertrix_lift_edx, entry->ebx, entry->ecx,
                           entry->esi, pushed, 1);
    }
    return port_return(&port, 0, vertrix_lift_edx);
}

/* Original 0x4d4270: when +0x50 of what 0x4d1930 gives is set, the import 0x4f1a9c on 0x5c79a4
 * (1); otherwise 0x4cf850. */
uint32_t vertrix_port_window_help_4d4270(PORT_SIGNATURE)
{
    Port port;
    uint32_t object = entry->eax;
    uint32_t state;
    uint32_t result;
    uint32_t pushed[1];
    port_open(&port, calls, services, globals, entry);
    state = port_forward_esi(&port, entry, 0x4d1930, object, entry->edx, entry->ebx, entry->ecx,
                             object);
    if (port_u32(&port, state, 0x50) == 0)
    {
        result = port_forward_esi(&port, entry, 0x4cf850, object, vertrix_lift_edx, entry->ebx,
                                  entry->ecx, object);
        return port_return(&port, result, vertrix_lift_edx);
    }
    pushed[0] = port_u32(&port, 0, 0x5c79a4);
    port_forward_stack(&port, entry, 0x4f1a9c, state, vertrix_lift_edx, entry->ebx, entry->ecx,
                       object, pushed, 1);
    return port_return(&port, 1, vertrix_lift_edx);
}

/* With the window 0x4d5350 gives, send it `message` with the two values of 0x4cf800's state (+8
 * and +0xc) by import 0x4f1a94. */
static uint32_t window_send(PORT_SIGNATURE, uint32_t message)
{
    Port port;
    uint32_t window;
    uint32_t state;
    uint32_t first;
    uint32_t second;
    uint32_t result;
    uint32_t pushed[4];
    port_open(&port, calls, services, globals, entry);
    window = port_forward(&port, entry, 0x4d5350, entry->eax, entry->edx, entry->ebx, entry->ecx);
    if (window == 0)
    {
        return port_return(&port, 0, vertrix_lift_edx);
    }
    state = port_forward(&port, entry, 0x4cf800, window, vertrix_lift_edx, window, entry->ecx);
    first = port_u32(&port, state, 8);
    second = port_u32(&port, state, 0xc);
    pushed[0] = port_u32(&port, window, 0x1c);
    pushed[1] = message;
    pushed[2] = first;
    pushed[3] = second;
    result = port_forward_stack(&port, entry, 0x4f1a94, second, first, window, entry->ecx,
                                entry->esi, pushed, 4);
    return port_return(&port, result, vertrix_lift_edx);
}

/* Original 0x4d4e00: message 0x114. */
uint32_t vertrix_port_window_send_4d4e00(PORT_SIGNATURE)
{
    return window_send(calls, services, globals, entry, 0x114);
}

/* Original 0x4d4e30: message 0x115. */
uint32_t vertrix_port_window_send_4d4e30(PORT_SIGNATURE)
{
    return window_send(calls, services, globals, entry, 0x115);
}

/* Original 0x4d4fd0: 0x4cce00 (edx 1 with bit 5 of +0x24), then the method +0xa4 with message
 * 0x86 and ebx the edx that leaves (0 when it gave 0). */
uint32_t vertrix_port_window_activate_4d4fd0(PORT_SIGNATURE)
{
    Port port;
    uint32_t object = entry->eax;
    uint32_t methods;
    uint32_t state;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    result = port_forward_esi(&port, entry, 0x4cce00, object,
                              (port_u8(&port, object, 0x24) & 0x20) != 0 ? 1 : entry->edx,
                              entry->ebx, entry->ecx, object);
    state = result != 0 ? vertrix_lift_edx : 0;
    methods = port_u32(&port, object, 0);
    result = port_call_with(&port, port_u32(&port, methods, 0xa4), object, 0x86, state, 0, object,
                            methods, entry->ebp);
    return port_return(&port, result, vertrix_lift_edx);
}

/* Original 0x4d5150: when eax is the window (+0x1c) of the frame (+4 of 0x4ce740's state), its
 * method +0x8c; otherwise 1. */
uint32_t vertrix_port_frame_window_call_4d5150(PORT_SIGNATURE)
{
    Port port;
    uint32_t state;
    uint32_t frame;
    uint32_t methods;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    state = port_forward(&port, entry, 0x4ce740, entry->eax, entry->edx, entry->eax, entry->ecx);
    frame = port_u32(&port, state, 4);
    if (entry->eax != port_u32(&port, frame, 0x1c))
    {
        return port_return(&port, 1, entry->edx);
    }
    methods = port_u32(&port, frame, 0);
    result = port_forward(&port, entry, port_u32(&port, methods, 0x8c), frame, methods, entry->eax,
                          entry->ecx);
    return port_return(&port, result, entry->edx);
}

/* Original 0x4d5180: for a nonzero edx when eax is the frame's window, 0x4dd170 with 1, 0x4ccad0
 * (edx 1) and the frame's method +0x6c. */
uint32_t vertrix_port_frame_window_activate_4d5180(PORT_SIGNATURE)
{
    Port port;
    uint32_t state;
    uint32_t frame;
    uint32_t methods;
    uint32_t result;
    uint32_t pushed[1] = {1};
    port_open(&port, calls, services, globals, entry);
    state = port_call_with(&port, 0x4ce740, entry->eax, entry->edx, entry->ebx, entry->ecx,
                           entry->edx, entry->eax, entry->ebp);
    frame = port_u32(&port, state, 4);
    if (entry->edx == 0 || entry->eax != port_u32(&port, frame, 0x1c))
    {
        return port_return(&port, state, vertrix_lift_edx);
    }
    call_stack_with(&port, 0x4dd170, state, vertrix_lift_edx, frame, entry->ecx, entry->edx,
                    entry->eax, entry->ebp, pushed, 1);
    port_call_with(&port, 0x4ccad0, frame, 1, frame, entry->ecx, entry->edx, entry->eax,
                   entry->ebp);
    methods = port_u32(&port, frame, 0);
    result = port_call_with(&port, port_u32(&port, methods, 0x6c), frame, methods, frame,
                            entry->ecx, entry->edx, entry->eax, entry->ebp);
    return port_return(&port, result, vertrix_lift_edx);
}

/* Original 0x4d58e0: 0x4d2460, and for edx 2 with +0x90 other than +0x94, 0x4d5910 with it. */
uint32_t vertrix_port_window_size_check_4d58e0(PORT_SIGNATURE)
{
    Port port;
    uint32_t object = entry->eax;
    uint32_t value;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    result = port_forward_esi(&port, entry, 0x4d2460, object, entry->edx, entry->ebx, object,
                              entry->edx);
    if (entry->edx != 2)
    {
        return port_return(&port, result, vertrix_lift_edx);
    }
    value = port_u32(&port, object, 0x90);
    if (value == port_u32(&port, object, 0x94))
    {
        return port_return(&port, result, value);
    }
    result = port_forward_esi(&port, entry, 0x4d5910, object, value, entry->ebx, object, 2);
    return port_return(&port, result, vertrix_lift_edx);
}

/* Original 0x4d59f0: the control of the list +0x70 whose window (+0x1c of +8) has the id edx
 * (import 0x4f1980), or 0. */
uint32_t vertrix_port_control_find_by_id_4d59f0(PORT_SIGNATURE)
{
    Port port;
    uint32_t id = entry->edx;
    uint32_t node;
    uint32_t eax;
    uint32_t edx = entry->edx;
    uint32_t pushed[1];
    port_open(&port, calls, services, globals, entry);
    if (id == 0)
    {
        return port_return(&port, 0, entry->edx);
    }
    node = port_u32(&port, entry->eax, 0x70);
    if (node == 0)
    {
        return port_return(&port, 0, entry->edx);
    }
    eax = node;
    for (;;)
    {
        uint32_t control = port_u32(&port, node, 8);
        uint32_t next = port_u32(&port, node, 0);
        uint32_t found;
        pushed[0] = port_u32(&port, control, 0x1c);
        found = call_stack_with(&port, 0x4f1980, eax, edx, next, entry->ecx, control, id,
                                entry->ebp, pushed, 1);
        edx = vertrix_lift_edx;
        if ((found & 0xffff) == id)
        {
            return port_return(&port, control, edx);
        }
        if (next == 0)
        {
            return port_return(&port, 0, edx);
        }
        node = next;
        eax = found & 0xffff;
    }
}

/* Original 0x4d5a30: the control of id [edx]: without one set +0x18 of edx; otherwise the call
 * +4 of its table +0x24 with whether bit 28 of 0x4cccc0's style is set. */
uint32_t vertrix_port_control_command_4d5a30(PORT_SIGNATURE)
{
    Port port;
    uint32_t command = entry->edx;
    uint32_t control;
    uint32_t table;
    uint32_t style;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    control = port_forward(&port, entry, 0x4d59f0, entry->eax, port_u32(&port, command, 0),
                           entry->ebx, command);
    if (control == 0)
    {
        port_set32(&port, command, 0x18, 1);
        return port_return(&port, 0, vertrix_lift_edx);
    }
    table = port_u32(&port, command, 0x24);
    style = port_forward(&port, entry, 0x4cccc0, control, vertrix_lift_edx, table, command);
    result = port_forward(&port, entry, port_u32(&port, table, 4), command,
                          (style & 0x10000000) != 0, table, command);
    return port_return(&port, result, vertrix_lift_edx);
}

/* Original 0x4d5a70: the control of id edx: 0 without one; otherwise 0x4d5390 with whether bit
 * 28 of its style is clear (1). */
uint32_t vertrix_port_control_update_4d5a70(PORT_SIGNATURE)
{
    Port port;
    uint32_t object = entry->eax;
    uint32_t control;
    uint32_t style;
    port_open(&port, calls, services, globals, entry);
    control = port_forward_esi(&port, entry, 0x4d59f0, object, entry->edx, entry->ebx, entry->ecx,
                               object);
    if (control == 0)
    {
        return port_return(&port, 0, 0);
    }
    style =
        port_forward_esi(&port, entry, 0x4cccc0, control, control, entry->ebx, entry->ecx, object);
    port_forward_esi(&port, entry, 0x4d5390, object, vertrix_lift_edx, (style & 0x10000000) == 0, 0,
                     object);
    return port_return(&port, 1, vertrix_lift_edx);
}

/* Original 0x4d6775: the double of the unsigned eax, in edx:eax. */
uint32_t vertrix_port_rtl_integer_to_double_4d6775(PORT_SIGNATURE)
{
    Port port;
    uint32_t value = entry->eax;
    uint32_t top;
    uint32_t mantissa;
    port_open(&port, calls, services, globals, entry);
    if (value == 0)
    {
        return port_return(&port, 0, 0);
    }
    top = 31 - (uint32_t)__builtin_clz(value);
    mantissa = (value << (31 - top)) << 1;
    return port_return(&port, mantissa << 20, ((0x3ff + top) << 20) | (mantissa >> 12));
}

/* Original 0x4d73c0: the frame's (+4 of 0x4ce740's state) method +0x9c with the text id ebx (or
 * +0x3c plus 0x20000) and 1; 0 without one. */
uint32_t vertrix_port_frame_show_text_4d73c0(PORT_SIGNATURE)
{
    Port port;
    uint32_t text = entry->ebx;
    uint32_t state;
    uint32_t frame;
    uint32_t methods;
    port_open(&port, calls, services, globals, entry);
    if (text == 0 && port_u32(&port, entry->eax, 0x3c) != 0)
    {
        text = port_u32(&port, entry->eax, 0x3c) + 0x20000;
    }
    if (text == 0)
    {
        return port_return(&port, 0, entry->edx);
    }
    state = port_forward_esi(&port, entry, 0x4ce740, entry->eax, entry->edx, entry->ebx, entry->ecx,
                             text);
    frame = port_u32(&port, state, 4);
    methods = port_u32(&port, frame, 0);
    port_forward_esi(&port, entry, port_u32(&port, methods, 0x9c), frame, text, 1, methods, text);
    return port_return(&port, 1, vertrix_lift_edx);
}
