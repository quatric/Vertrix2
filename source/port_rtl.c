#include "port_rtl.h"

/* Runtime library window, owner, string and scope helpers. */

/* A call handing the callee esi and edi as given, the caller's ebp, and `count` stack arguments
 * (the nearest to the stack pointer first). */
static uint32_t call_registers(Port *port, const LiftEntry *entry, uint32_t target, uint32_t eax,
                               uint32_t edx, uint32_t ebx, uint32_t ecx, uint32_t esi, uint32_t edi,
                               const uint32_t *stack, unsigned count)
{
    uint32_t result;
    vertrix_lift_in_esi = esi;
    vertrix_lift_in_edi = edi;
    vertrix_lift_in_ebp = entry->ebp;
    result = lift_call_arguments(&port->env, target, eax, edx, ebx, ecx, stack, count);
    vertrix_lift_in_esi = vertrix_lift_in_edi = vertrix_lift_in_ebp = 0;
    return result;
}

/* Original 0x4ccaf0: without a parent (+0xa0), method [+0x24] of edx with 0; otherwise method +8
 * of the parent's +0x1c with edx. */
uint32_t vertrix_port_rtl_child_notify_4ccaf0(PORT_SIGNATURE)
{
    Port port;
    uint32_t parent;
    uint32_t methods;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    parent = port_u32(&port, entry->eax, 0xa0);
    if (parent == 0)
    {
        methods = port_u32(&port, entry->edx, 0x24);
        result = port_forward(&port, entry, port_u32(&port, methods, 0), entry->edx, 0, entry->ebx,
                              methods);
    }
    else
    {
        methods = port_u32(&port, parent, 0x1c);
        result = port_forward(&port, entry, port_u32(&port, methods, 8), parent, entry->edx,
                              methods, parent);
    }
    return port_return(&port, result, vertrix_lift_edx);
}

/* Original 0x4ccb40: the command edx less 0xe110 as an index of the parent's (+0xa0) list +4:
 * unless method +0x80 takes that item, method [+0x1c] of the parent with the index; 1. */
uint32_t vertrix_port_rtl_command_dispatch_4ccb40(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x10
    };
    Port port;
    uint32_t object = entry->eax;
    uint32_t index = entry->edx - 0xe110;
    uint32_t methods;
    uint32_t parent;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    methods = port_u32(&port, object, 0);
    parent = port_u32(&port, object, 0xa0);
    port_set32(&port, entry->esp, -0x10u, index * 4);
    if (call_registers(&port, entry, port_u32(&port, methods, 0x80), object,
                       port_u32(&port, port_u32(&port, parent, 4) + index * 4, 0), index, object,
                       methods, entry->edi, NULL, 0) == 0)
    {
        uint32_t list;
        parent = port_u32(&port, object, 0xa0);
        list = port_u32(&port, parent, 0x1c);
        call_registers(&port, entry, port_u32(&port, list, 0), parent, index, index, list, methods,
                       entry->edi, NULL, 0);
    }
    return port_return(&port, 1, vertrix_lift_edx);
}

/* Original 0x4ccee0: link the window eax as the owner of the control 0x4df140 finds for its
 * handle +0x1c in edx's table (+0x34 +0x20): unlink its old owner and point both at each other.
 * Nothing when either is missing or eax is linked (+0x38). */
uint32_t vertrix_port_rtl_link_owner_4ccee0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x10
    };
    Port port;
    uint32_t window = entry->eax;
    uint32_t local = entry->esp - 0x10;
    uint32_t control;
    uint32_t owner;
    uint32_t handle;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    if (window == 0 || port_u32(&port, window, 0x38) != 0 || entry->edx == 0 ||
        port_u32(&port, entry->edx, 0x34) == 0)
    {
        return port_return(&port, window, entry->edx);
    }
    handle = port_u32(&port, window, 0x1c);
    if (call_registers(&port, entry, 0x4df140, port_u32(&port, entry->edx, 0x34) + 0x20, handle,
                       local, window, handle, entry->edi, NULL, 0) == 0)
    {
        return port_return(&port, 0, vertrix_lift_edx);
    }
    control = port_u32(&port, local, 0);
    owner = port_u32(&port, control, 0x24);
    if (owner != 0 && port_u32(&port, owner, 0x38) == port_u32(&port, local, 0))
    {
        port_set32(&port, owner, 0x38, 0);
    }
    control = port_u32(&port, local, 0);
    port_set32(&port, window, 0x38, control);
    port_set32(&port, control, 0x24, window);
    return port_return(&port, control, owner);
}

/* Original 0x4cce90: for an unlinked window eax, the control 0x4df140 finds for its parent
 * window (by the import 0x4f19c8) in the table edx, linked by 0x4ccee0. */
uint32_t vertrix_port_rtl_link_parent_4cce90(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x14
    };
    Port port;
    uint32_t window = entry->eax;
    uint32_t local = entry->esp - 0x14;
    uint32_t pushed[1];
    uint32_t parent;
    uint32_t result;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    if (window == 0 || port_u32(&port, window, 0x38) != 0)
    {
        return port_return(&port, window, entry->edx);
    }
    pushed[0] = port_u32(&port, window, 0x1c);
    parent = call_registers(&port, entry, 0x4f19c8, window, entry->edx, local, entry->ecx, window,
                            entry->edx, pushed, 1);
    result = call_registers(&port, entry, 0x4df140, entry->edx, parent, local, entry->ecx, window,
                            entry->edx, NULL, 0);
    if (result == 0)
    {
        return port_return(&port, 0, vertrix_lift_edx);
    }
    result = call_registers(&port, entry, 0x4ccee0, window, port_u32(&port, local, 0), local,
                            entry->ecx, window, entry->edx, NULL, 0);
    return port_return(&port, result, vertrix_lift_edx);
}

/* The record at `field` of the thread data (0x4ce780), made when missing and eax is set: 0x44
 * bytes by 0x4ca000 built by 0x4decd0 with `table`, `size` and `kind`. */
static uint32_t thread_record(PORT_SIGNATURE, uint32_t field, uint32_t table, uint32_t size,
                              uint32_t kind)
{
    Port port;
    uint32_t data;
    uint32_t record;
    port_open(&port, calls, services, globals, entry);
    data = port_forward(&port, entry, 0x4ce780, entry->eax, entry->edx, entry->eax, entry->ecx);
    if (port_u32(&port, data, field) == 0 && entry->eax != 0)
    {
        record = call_registers(&port, entry, 0x4ca000, 0x44, vertrix_lift_edx, entry->eax,
                                entry->ecx, data, entry->edi, NULL, 0);
        if (record != 0)
        {
            record = call_registers(&port, entry, 0x4decd0, record, table, size, kind, data,
                                    entry->edi, NULL, 0);
        }
        port_set32(&port, data, field, record);
    }
    return port_return(&port, port_u32(&port, data, field), entry->edx);
}

/* Original 0x4cf880: the string record +0x14 (0x502ae8, 0x1c, 1). */
uint32_t vertrix_port_rtl_thread_string_4cf880(PORT_SIGNATURE)
{
    return thread_record(calls, services, globals, entry, 0x14, 0x502ae8, 0x1c, 1);
}

/* Original 0x4cf980: release the string member +0x1c by 0x4df1c0 (with the thread's string
 * record), clear it and +0x38; eax the member. */
uint32_t vertrix_port_rtl_release_string_member_4cf980(PORT_SIGNATURE)
{
    Port port;
    uint32_t object = entry->eax;
    uint32_t member;
    uint32_t record;
    port_open(&port, calls, services, globals, entry);
    member = port_u32(&port, object, 0x1c);
    if (member != 0)
    {
        record = port_forward(&port, entry, 0x4cf880, 0, entry->edx, member, object);
        if (record != 0)
        {
            port_forward(&port, entry, 0x4df1c0, record, port_u32(&port, object, 0x1c), member,
                         object);
        }
        port_set32(&port, object, 0x1c, 0);
    }
    port_set32(&port, object, 0x38, 0);
    return port_return(&port, member, entry->edx);
}

/* Original 0x4d16b0: the record 0x4cba70 gives marked with 0x519724 at +0x24 and 1 at +0x28. */
uint32_t vertrix_port_rtl_record_mark_4d16b0(PORT_SIGNATURE)
{
    Port port;
    uint32_t record;
    port_open(&port, calls, services, globals, entry);
    record = port_forward(&port, entry, 0x4cba70, entry->eax, entry->edx, entry->ebx, entry->ecx);
    port_set32(&port, record, 0x24, 0x519724);
    port_set32(&port, record, 0x28, 1);
    return port_return(&port, record, vertrix_lift_edx);
}

/* Original 0x4d2260: unless the thread data (0x4ce740) is closing (+0x14), the hook record from
 * 0x4dc030 (0x5c7b84, 0x4cc760) runs its callback +0x24 when 0x4cbe80 names eax at +0x1c; then
 * 0x4d2390 on eax. */
uint32_t vertrix_port_rtl_scope_leave_4d2260(PORT_SIGNATURE)
{
    Port port;
    uint32_t object = entry->eax;
    uint32_t data;
    uint32_t edi = entry->edi;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    data = call_registers(&port, entry, 0x4ce740, object, entry->edx, entry->ebx, entry->ecx,
                          object, edi, NULL, 0);
    if (port_u8(&port, data, 0x14) == 0)
    {
        uint32_t hook = call_registers(&port, entry, 0x4dc030, 0x5c7b84, 0x4cc760, entry->ebx,
                                       entry->ecx, object, edi, NULL, 0);
        edi = hook;
        result = call_registers(&port, entry, 0x4cbe80, hook, vertrix_lift_edx, hook, entry->ecx,
                                object, edi, NULL, 0);
        if (result != 0)
        {
            result = call_registers(&port, entry, 0x4cbe80, result, vertrix_lift_edx, hook,
                                    entry->ecx, object, edi, NULL, 0);
            if (object == port_u32(&port, result, 0x1c) && port_u32(&port, hook, 0x24) != 0)
            {
                call_registers(&port, entry, port_u32(&port, hook, 0x24), result, vertrix_lift_edx,
                               hook, entry->ecx, object, edi, NULL, 0);
            }
        }
    }
    result = call_registers(&port, entry, 0x4d2390, object, 0, 0, entry->ecx, object, edi, NULL, 0);
    return port_return(&port, result, vertrix_lift_edx);
}

/* Original 0x4d22b0: when 0x4cbe80 names eax, 0x4cb230 on the thread's window (0x4ce740 +4) with
 * edx; then unless 0x4cccc0 has bit 30, 0x4d1ae0 on the handle +0x1c with the rectangle of
 * 0x4cf800 (+4, +8, +0xc) and 1, 1. */
uint32_t vertrix_port_rtl_scope_enter_4d22b0(PORT_SIGNATURE)
{
    Port port;
    uint32_t object = entry->eax;
    uint32_t value = entry->edx;
    uint32_t result;
    uint32_t pushed[6];
    port_open(&port, calls, services, globals, entry);
    result = call_registers(&port, entry, 0x4cbe80, object, value, object, entry->ecx, value,
                            entry->edi, NULL, 0);
    if (result != 0)
    {
        result = call_registers(&port, entry, 0x4cbe80, result, vertrix_lift_edx, object,
                                entry->ecx, value, entry->edi, NULL, 0);
        if (object == port_u32(&port, result, 0x1c))
        {
            result = call_registers(&port, entry, 0x4ce740, result, vertrix_lift_edx, object,
                                    entry->ecx, value, entry->edi, NULL, 0);
            call_registers(&port, entry, 0x4cb230, port_u32(&port, result, 4), value, object,
                           entry->ecx, value, entry->edi, NULL, 0);
        }
    }
    result = call_registers(&port, entry, 0x4cccc0, object, vertrix_lift_edx, object, entry->ecx,
                            value, entry->edi, NULL, 0);
    if (result & 0x40000000u)
    {
        return port_return(&port, result, vertrix_lift_edx);
    }
    result = call_registers(&port, entry, 0x4cf800, result, vertrix_lift_edx, object, entry->ecx,
                            value, entry->edi, NULL, 0);
    pushed[0] = port_u32(&port, object, 0x1c);
    pushed[1] = port_u32(&port, result, 4);
    pushed[2] = port_u32(&port, result, 8);
    pushed[3] = port_u32(&port, result, 0xc);
    pushed[4] = 1;
    pushed[5] = 1;
    result = call_registers(&port, entry, 0x4d1ae0, pushed[3], pushed[2], object, entry->ecx,
                            pushed[1], entry->edi, pushed, 6);
    return port_return(&port, result, vertrix_lift_edx);
}

/* Original 0x4d2390: 0x4de900 on 0x5c7944 when the thread's window (0x4ce740 +4) has eax at
 * +0x1c; unless 0x4cccc0 has bit 30, 0x4d1ae0 on the handle +0x1c with the rectangle of 0x4cf800
 * and 1, 1; then 0x4cf850. */
uint32_t vertrix_port_rtl_scope_refresh_4d2390(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0xc
    };
    Port port;
    uint32_t object = entry->eax;
    uint32_t local = entry->esp - 0xc;
    uint32_t result;
    uint32_t pushed[6];
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    result = call_registers(&port, entry, 0x4ce740, object, entry->edx, entry->ebx, entry->ecx,
                            object, entry->edi, NULL, 0);
    if (object == port_u32(&port, port_u32(&port, result, 4), 0x1c))
    {
        call_registers(&port, entry, 0x4de900, 0x5c7944, vertrix_lift_edx, entry->ebx, entry->ecx,
                       object, entry->edi, NULL, 0);
    }
    result = call_registers(&port, entry, 0x4cccc0, object, vertrix_lift_edx, entry->ebx,
                            entry->ecx, object, entry->edi, NULL, 0);
    if ((result & 0x40000000u) == 0)
    {
        result = call_registers(&port, entry, 0x4cf800, result, vertrix_lift_edx, entry->ebx,
                                entry->ecx, object, entry->edi, NULL, 0);
        port_set32(&port, local, 0, port_u32(&port, result, 4));
        pushed[0] = port_u32(&port, object, 0x1c);
        pushed[1] = port_u32(&port, local, 0);
        pushed[2] = port_u32(&port, result, 8);
        pushed[3] = port_u32(&port, result, 0xc);
        pushed[4] = 1;
        pushed[5] = 1;
        call_registers(&port, entry, 0x4d1ae0, pushed[3], pushed[2], entry->ebx, entry->ecx, object,
                       entry->edi, pushed, 6);
    }
    result = call_registers(&port, entry, 0x4cf850, object, vertrix_lift_edx, entry->ebx,
                            entry->ecx, object, entry->edi, NULL, 0);
    return port_return(&port, result, vertrix_lift_edx);
}

/* Original 0x4d42a0: the command ebx (or, for 0, +0x90 + 0x10000 when 0x4d2d70 holds, else +0x8c
 * + 0x20000) sent by method +0x9c of the thread's window (0x4ce740 +4) with 1; 1, or 0 for no
 * command. */
uint32_t vertrix_port_rtl_send_command_4d42a0(PORT_SIGNATURE)
{
    Port port;
    uint32_t object = entry->eax;
    uint32_t command = entry->ebx;
    uint32_t eax = object;
    uint32_t edx = entry->edx;
    uint32_t window;
    uint32_t methods;
    port_open(&port, calls, services, globals, entry);
    if (command == 0)
    {
        eax = call_registers(&port, entry, 0x4d2d70, object, entry->edx, 0, object, 0, entry->edi,
                             NULL, 0);
        edx = vertrix_lift_edx;
        if (eax != 0)
        {
            command = port_u32(&port, object, 0x90) + 0x10000;
        }
        else
        {
            command = port_u32(&port, object, 0x8c) + 0x20000;
        }
    }
    if (command == 0)
    {
        return port_return(&port, 0, edx);
    }
    window = call_registers(&port, entry, 0x4ce740, eax, edx, entry->ebx, object, command,
                            entry->edi, NULL, 0);
    window = port_u32(&port, window, 4);
    methods = port_u32(&port, window, 0);
    call_registers(&port, entry, port_u32(&port, methods, 0x9c), window, command, 1, methods,
                   command, entry->edi, NULL, 0);
    return port_return(&port, 1, vertrix_lift_edx);
}

/* Original 0x4d70e0: method +0x78 when +0x24 has bit 3 or 4, then the import 0x4f1950 on the
 * handle +0x1c with edx. */
uint32_t vertrix_port_rtl_window_import_4d70e0(PORT_SIGNATURE)
{
    Port port;
    uint32_t object = entry->eax;
    uint32_t eax = object;
    uint32_t esi = entry->esi;
    uint32_t edx = entry->edx;
    uint32_t pushed[2];
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    if (port_u8(&port, object, 0x24) & 0x18)
    {
        esi = port_u32(&port, object, 0);
        eax = call_registers(&port, entry, port_u32(&port, esi, 0x78), object, entry->edx,
                             entry->edx, object, esi, entry->edi, NULL, 0);
        edx = vertrix_lift_edx;
    }
    pushed[0] = port_u32(&port, object, 0x1c);
    pushed[1] = entry->edx;
    result = call_registers(&port, entry, 0x4f1950, eax, edx, entry->edx, object, esi, entry->edi,
                            pushed, 2);
    return port_return(&port, result, vertrix_lift_edx);
}

/* Original 0x4d8b30: free the text +8 of each block of the chain +4 by 0x4ca210, clear the
 * pointers +4, +8, +0xc and +0x10, and release +0x14 by 0x4e2400. */
uint32_t vertrix_port_rtl_blocks_clear_4d8b30(PORT_SIGNATURE)
{
    Port port;
    uint32_t object = entry->eax;
    uint32_t block;
    uint32_t edx = entry->edx;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    for (block = port_u32(&port, object, 4); block != 0; block = port_u32(&port, block, 0))
    {
        port_forward(&port, entry, 0x4ca210, block + 8, 0, object, block);
        edx = vertrix_lift_edx;
    }
    port_set32(&port, object, 0x10, 0);
    port_set32(&port, object, 8, port_u32(&port, object, 0x10));
    port_set32(&port, object, 4, port_u32(&port, object, 0x10));
    port_set32(&port, object, 0xc, 0);
    result = port_forward(&port, entry, 0x4e2400, port_u32(&port, object, 0x14), edx, object, 0);
    port_set32(&port, object, 0x14, 0);
    return port_return(&port, result, entry->edx);
}

/* Original 0x4d82c6: the float helpers 0x503ea0, 0x503ea4 and 0x503ea8 for the coprocessor
 * (0x5054a1) and its flag 0x508798 bit 0, or for emulation. */
uint32_t vertrix_port_rtl_select_float_helpers_4d82c6(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    if (port_u8(&port, 0, 0x5054a1) != 0)
    {
        port_set32(&port, 0, 0x503ea0, 0x4d80b7);
        port_set32(&port, 0, 0x503ea4, 0x4d8188);
        port_set32(&port, 0, 0x503ea8,
                   (port_u8(&port, 0, 0x508798) & 1) != 0 ? 0x4d8204 : 0x4d8217);
    }
    else
    {
        port_set32(&port, 0, 0x503ea0, 0x4d80d5);
        port_set32(&port, 0, 0x503ea4, 0x4d8198);
        port_set32(&port, 0, 0x503ea8, 0x4d8227);
    }
    return port_return(&port, entry->eax, entry->edx);
}

/* Original 0x4dd3e0: the record +0x1c (0x506a78, 4, 2). */
uint32_t vertrix_port_rtl_thread_record_4dd3e0(PORT_SIGNATURE)
{
    return thread_record(calls, services, globals, entry, 0x1c, 0x506a78, 4, 2);
}

/* Original 0x4ddbe0: the record +0x20 (0x506ad8, 4, 1). */
uint32_t vertrix_port_rtl_thread_record_4ddbe0(PORT_SIGNATURE)
{
    return thread_record(calls, services, globals, entry, 0x20, 0x506ad8, 4, 1);
}

/* Original 0x4dba20: unlink the item edx from the chain eax (head +0, links at +4 bytes past
 * each item); 1 when it was there. */
uint32_t vertrix_port_rtl_chain_unlink_4dba20(PORT_SIGNATURE)
{
    Port port;
    uint32_t chain = entry->eax;
    uint32_t item = entry->edx;
    uint32_t links;
    uint32_t node;
    port_open(&port, calls, services, globals, entry);
    if (port_u32(&port, chain, 0) == 0)
    {
        return port_return(&port, 0, 0);
    }
    links = port_u32(&port, chain, 4);
    if (item == port_u32(&port, chain, 0))
    {
        port_set32(&port, chain, 0, port_u32(&port, item + links, 0));
        return port_return(&port, 1, 1);
    }
    for (node = port_u32(&port, chain, 0); node != 0;)
    {
        uint32_t link = port_u32(&port, chain, 4) + node;
        if (item == port_u32(&port, link, 0))
        {
            break;
        }
        node = port_u32(&port, link, 0);
    }
    if (node == 0)
    {
        return port_return(&port, 0, 0);
    }
    links = port_u32(&port, chain, 4);
    port_set32(&port, node + links, 0, port_u32(&port, item + links, 0));
    return port_return(&port, 1, 1);
}

/* Original 0x4dec70: count down the thread's nesting (+0x10 of 0x4ce780); on the last level the
 * window's (0x4ce740 +4) method +0xb8 with 0, 0, then 0x4ddc30, 0x4dd430, 0x4e1200 and 0x4cf8d0.
 * Whether the count is still set. */
uint32_t vertrix_port_rtl_thread_leave_4dec70(PORT_SIGNATURE)
{
    Port port;
    uint32_t data;
    uint32_t eax;
    uint32_t edx;
    port_open(&port, calls, services, globals, entry);
    data = port_forward(&port, entry, 0x4ce780, entry->eax, entry->edx, entry->ebx, entry->ecx);
    if (port_u32(&port, data, 0x10) != 0)
    {
        uint32_t count = port_u32(&port, data, 0x10) - 1;
        port_set32(&port, data, 0x10, count);
        if (count == 0)
        {
            uint32_t pushed[2] = {0, 0};
            eax = port_forward(&port, entry, 0x4ce740, data, vertrix_lift_edx, data, entry->ecx);
            eax = port_u32(&port, eax, 4);
            edx = eax;
            if (eax != 0 && port_u32(&port, eax, 0xb8) != 0)
            {
                eax = port_forward_stack(&port, entry, port_u32(&port, eax, 0xb8), eax, eax, data,
                                         entry->ecx, entry->esi, pushed, 2);
                edx = vertrix_lift_edx;
            }
            eax = port_forward(&port, entry, 0x4ddc30, eax, edx, data, entry->ecx);
            eax = port_forward(&port, entry, 0x4dd430, eax, vertrix_lift_edx, data, entry->ecx);
            eax = port_forward(&port, entry, 0x4e1200, eax, vertrix_lift_edx, data, entry->ecx);
            port_forward(&port, entry, 0x4cf8d0, eax, vertrix_lift_edx, data, entry->ecx);
        }
    }
    return port_return(&port, port_u32(&port, data, 0x10) != 0, vertrix_lift_edx);
}

/* Original 0x4df070: a node of 16 bytes from the pool eax: when the free list +0x10 is empty a
 * block of +0x18 nodes by 0x4e23e0 (on +0x14) is threaded onto it; the node is taken, counted
 * (+0xc) and its +8 and +0xc cleared. */
uint32_t vertrix_port_node_pool_take_quad_4df070(PORT_SIGNATURE)
{
    Port port;
    uint32_t pool = entry->eax;
    uint32_t node;
    port_open(&port, calls, services, globals, entry);
    if (port_u32(&port, pool, 0x10) == 0)
    {
        uint32_t pushed[3];
        uint32_t block;
        int32_t index;
        pushed[0] = pool + 0x14;
        pushed[1] = port_u32(&port, pool, 0x18);
        pushed[2] = 0x10;
        block = port_forward_stack(&port, entry, 0x4e23e0, pool + 0x14, entry->edx, pool,
                                   entry->ecx, entry->esi, pushed, 3);
        index = (int32_t)port_u32(&port, pool, 0x18) - 1;
        for (node = (uint32_t)index * 16 + block + 4; index >= 0; index--, node -= 16)
        {
            port_set32(&port, node, 0, port_u32(&port, pool, 0x10));
            port_set32(&port, pool, 0x10, node);
        }
    }
    node = port_u32(&port, pool, 0x10);
    port_set32(&port, pool, 0x10, port_u32(&port, node, 0));
    port_set32(&port, pool, 0xc, port_u32(&port, pool, 0xc) + 1);
    port_set32(&port, node, 8, 0);
    port_set32(&port, node, 0xc, 0);
    return port_return(&port, node, entry->edx);
}

/* `div` of eax by the bucket count: the remainder (eax and edx left as they are when it would
 * fault). */
static uint32_t bucket_of(uint32_t key, uint32_t count, uint32_t *edx)
{
    uint32_t eax = key >> 4;
    LiftFlags flags = {0, 0, 0, 0, 0, 0};
    *edx = 0;
    lift_div1(32, count, &eax, edx, &flags);
    return *edx;
}

/* Original 0x4df0f0: the node of the map eax for the key edx (bucket (key >> 4) mod +8 of the
 * table +4, stored at ebx), or 0. */
uint32_t vertrix_port_map_find_4df0f0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0xc
    };
    Port port;
    uint32_t map = entry->eax;
    uint32_t key = entry->edx;
    uint32_t bucket;
    uint32_t edx;
    uint32_t node;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, entry->esp, -0xcu, port_u32(&port, map, 8));
    bucket = bucket_of(key, port_u32(&port, map, 8), &edx);
    port_set32(&port, entry->ebx, 0, bucket);
    if (port_u32(&port, map, 4) == 0)
    {
        return port_return(&port, 0, edx);
    }
    for (node = port_u32(&port, port_u32(&port, map, 4), bucket * 4); node != 0;
         node = port_u32(&port, node, 0))
    {
        if (key == port_u32(&port, node, 8))
        {
            return port_return(&port, node, edx);
        }
    }
    return port_return(&port, 0, edx);
}

/* Original 0x4df160: the value slot (+0xc) of the node for the key edx in the map eax, made when
 * missing: the table by 0x4def50 when there is none, a node by 0x4df070 linked first in its
 * bucket. edx the node. */
uint32_t vertrix_port_map_find_or_add_4df160(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x10
    };
    Port port;
    uint32_t map = entry->eax;
    uint32_t key = entry->edx;
    uint32_t local = entry->esp - 0x10;
    uint32_t node;
    uint32_t ebx = local;
    uint32_t edx;
    uint32_t bucket;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    node = port_forward_esi(&port, entry, 0x4df0f0, map, key, local, map, key);
    if (node == 0)
    {
        edx = 0;
        if (port_u32(&port, map, 4) == 0)
        {
            ebx = 1;
            port_forward_esi(&port, entry, 0x4def50, map, port_u32(&port, map, 8), ebx, map, key);
            edx = vertrix_lift_edx;
        }
        node = port_forward_esi(&port, entry, 0x4df070, map, edx, ebx, map, key);
        port_set32(&port, node, 4, port_u32(&port, local, 0));
        port_set32(&port, node, 8, key);
        bucket = port_u32(&port, local, 0);
        port_set32(&port, node, 0, port_u32(&port, port_u32(&port, map, 4), bucket * 4));
        port_set32(&port, port_u32(&port, map, 4), port_u32(&port, local, 0) * 4, node);
    }
    return port_return(&port, node + 0xc, node);
}

/* Original 0x4df1c0: remove the node for the key edx from the map eax and give it back by
 * 0x4df0d0; 1 when it was there. */
uint32_t vertrix_port_map_remove_4df1c0(PORT_SIGNATURE)
{
    Port port;
    uint32_t map = entry->eax;
    uint32_t key = entry->edx;
    uint32_t previous;
    uint32_t node;
    uint32_t edx;
    port_open(&port, calls, services, globals, entry);
    if (port_u32(&port, map, 4) == 0)
    {
        return port_return(&port, 0, entry->edx);
    }
    previous = bucket_of(key, port_u32(&port, map, 8), &edx) * 4 + port_u32(&port, map, 4);
    node = port_u32(&port, previous, 0);
    while (node != 0)
    {
        if (key == port_u32(&port, node, 8))
        {
            port_set32(&port, previous, 0, port_u32(&port, node, 0));
            port_forward(&port, entry, 0x4df0d0, map, node, map, port_u32(&port, node, 0));
            return port_return(&port, 1, vertrix_lift_edx);
        }
        previous = node;
        node = port_u32(&port, node, 0);
    }
    return port_return(&port, 0, 0);
}

/* Original 0x4e01d0: the entry of the handle eax in the table 0x507c88 (0 past the count
 * 0x507c34); a standard handle (below 3) seen for the first time is marked (bit 6 of byte 1) and,
 * when 0x4e0a30 holds for it, flagged (bit 5). */
uint32_t vertrix_port_rtl_handle_entry_4e01d0(PORT_SIGNATURE)
{
    Port port;
    uint32_t handle = entry->eax;
    port_open(&port, calls, services, globals, entry);
    if (handle >= port_u32(&port, 0, 0x507c34))
    {
        return port_return(&port, 0, entry->edx);
    }
    if ((int32_t)handle < 3)
    {
        uint32_t slot = port_u32(&port, 0, 0x507c88) + handle * 4;
        uint32_t flags = port_u8(&port, slot, 1);
        if ((flags & 0x40) == 0)
        {
            port_set8(&port, slot, 1, flags | 0x40);
            if (port_forward(&port, entry, 0x4e0a30, handle, handle, handle * 4,
                             (entry->ecx & 0xffff0000u) | ((flags | 0x40) << 8) | flags) != 0)
            {
                slot = port_u32(&port, 0, 0x507c88) + handle * 4;
                port_set8(&port, slot, 1, port_u8(&port, slot, 1) | 0x20);
            }
        }
    }
    return port_return(&port, port_u32(&port, port_u32(&port, 0, 0x507c88), handle * 4),
                       entry->edx);
}

/* Original 0x4e0250: 1 when every one of the 0x507c90 slots of 0x507c8c is in use (0 when that
 * count is under 0x507c34); 0x507c8c kept. */
uint32_t vertrix_port_rtl_handles_full_4e0250(PORT_SIGNATURE)
{
    Port port;
    uint32_t table;
    uint32_t count;
    uint32_t offset;
    uint32_t result = 1;
    port_open(&port, calls, services, globals, entry);
    table = port_u32(&port, 0, 0x507c8c);
    count = port_u32(&port, 0, 0x507c90);
    if (count < port_u32(&port, 0, 0x507c34))
    {
        result = 0;
    }
    else if ((int32_t)count > 0)
    {
        for (offset = 0; (int32_t)offset < (int32_t)(count << 2); offset += 4)
        {
            if (port_u32(&port, table, offset) == 0)
            {
                result = 0;
                break;
            }
        }
    }
    port_set32(&port, 0, 0x507c8c, table);
    return port_return(&port, result, entry->edx);
}

/* Original 0x4e0490: the import 0x4f1b30 with four 0 arguments, or (when it gives 0) the next
 * count 0x507c94. */
uint32_t vertrix_port_rtl_make_handle_4e0490(PORT_SIGNATURE)
{
    Port port;
    uint32_t pushed[4] = {0, 0, 0, 0};
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    result = port_forward_stack(&port, entry, 0x4f1b30, entry->eax, entry->edx, entry->ebx,
                                entry->ecx, entry->esi, pushed, 4);
    if (result == 0)
    {
        result = port_u32(&port, 0, 0x507c94) + 1;
        port_set32(&port, 0, 0x507c94, result);
    }
    return port_return(&port, result, entry->edx);
}

/* Original 0x4e0994: the access of the open mode eax (bits 4 to 6) stored at edx: 0 1 (with 2
 * more when bits 0 to 2 are 0), 0x10 0, 0x20 1, 0x30 2, 0x40 3; nothing for the others. */
uint32_t vertrix_port_rtl_open_access_4e0994(PORT_SIGNATURE)
{
    Port port;
    uint32_t mode = entry->eax & 0x70;
    uint32_t share = entry->eax & 7;
    port_open(&port, calls, services, globals, entry);
    if (mode == 0)
    {
        port_set32(&port, entry->edx, 0, 1);
        if (share == 0)
        {
            port_set8(&port, entry->edx, 0, port_u8(&port, entry->edx, 0) | 2);
        }
    }
    else if (mode == 0x10)
    {
        port_set32(&port, entry->edx, 0, 0);
    }
    else if (mode == 0x20)
    {
        port_set32(&port, entry->edx, 0, 1);
    }
    else if (mode == 0x30)
    {
        port_set32(&port, entry->edx, 0, 2);
    }
    else if (mode == 0x40)
    {
        port_set32(&port, entry->edx, 0, 3);
    }
    return port_return(&port, mode, entry->edx);
}

/* Original 0x4e0a95: the address of the entry edx (from 1, 8 bytes each, after 4) of eax, or 0
 * for 0; edx the offset. */
uint32_t vertrix_port_rtl_entry_address_4e0a95(PORT_SIGNATURE)
{
    Port port;
    uint32_t offset;
    port_open(&port, calls, services, globals, entry);
    if (entry->edx == 0)
    {
        return port_return(&port, 0, 0);
    }
    offset = (entry->edx << 3) - 8;
    return port_return(&port, entry->eax + 4 + offset, offset);
}

/* Original 0x4e0e69: move the block edx from the chain at [eax] +8 to the free list of its heap
 * (+0x14), kept in address order (+4 of the heap), under the heap's lock (+8, 0x4e14b0 and
 * 0x4e14b7). */
uint32_t vertrix_port_rtl_block_release_4e0e69(PORT_SIGNATURE)
{
    Port port;
    uint32_t block = entry->edx;
    uint32_t link;
    uint32_t heap;
    uint32_t header;
    uint32_t next;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    link = port_u32(&port, entry->eax, 0) + 8;
    while (block != port_u32(&port, link, 0))
    {
        link = port_u32(&port, link, 0);
    }
    port_set32(&port, link, 0, port_u32(&port, block, 0));
    heap = port_u32(&port, block, 0x14);
    header = block - 4;
    port_forward(&port, entry, 0x4e14b0, heap + 8, block, heap, header);
    port_set32(&port, header, 4, port_u32(&port, header, 0));
    link = heap + 4;
    for (;;)
    {
        next = port_u32(&port, link, 0);
        if (next == 0 || next > header)
        {
            break;
        }
        link = next;
    }
    port_set32(&port, link, 0, header);
    port_set32(&port, header, 0, next);
    result = port_forward(&port, entry, 0x4e14b7, heap + 8, next, heap, header);
    return port_return(&port, result, vertrix_lift_edx);
}

/* Original 0x4e11b0: the record +0x18 (0x508158, 4, 1). */
uint32_t vertrix_port_rtl_thread_record_4e11b0(PORT_SIGNATURE)
{
    return thread_record(calls, services, globals, entry, 0x18, 0x508158, 4, 1);
}
