#include "display.h"

/* Display chain, palette, list release and actor helpers. */

/* A call handing the callee esi and edi as given, the ebp `ebp`, and `count` stack arguments
 * (the nearest to the stack pointer first). */
static uint32_t call_registers(Port *port, uint32_t target, uint32_t eax, uint32_t edx,
                               uint32_t ebx, uint32_t ecx, uint32_t esi, uint32_t edi, uint32_t ebp,
                               const uint32_t *stack, unsigned count)
{
    return port_call_registers(port, target, eax, edx, ebx, ecx, esi, edi, ebp, stack, count);
}

/* Original 0x47f370: the index in the chain from +0xc (linked by +0x60) of the display whose 16
 * bytes at +8 match those at +0xa4 of eax, or -1. */
uint32_t vertrix_port_display_chain_index_47f370(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x1c
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t node;
    uint32_t index = 0;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    node = port_u32(&port, entry->eax, 0xc);
    if (node == 0)
    {
        return port_return(&port, 0xffffffffu, entry->edx);
    }
    port_set32(&port, ebp, -0x18u, entry->eax + 0xa4);
    for (; node != 0; node = port_u32(&port, node, 0x60), index++)
    {
        uint32_t offset;
        for (offset = 0; offset < 16; offset++)
        {
            if (port_u8(&port, entry->eax + 0xa4, offset) != port_u8(&port, node + 8, offset))
            {
                break;
            }
        }
        if (offset == 16)
        {
            return port_return(&port, index, entry->edx);
        }
    }
    return port_return(&port, 0xffffffffu, entry->edx);
}

/* Original 0x4823b0: 0x4cea15 on eax with 10 and 0x516ba0 under the guard record
 * (0x4ec1ec, 0x516b4c); eax and edx its result. */
uint32_t vertrix_port_resource_entry_10_4823b0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x20
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t result;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, -0x1cu, port.env.chain);
    port_set32(&port, ebp, -0x18u, 0x4ec1ec);
    port_set32(&port, ebp, -0x14u, 0x516b4c);
    port_set32(&port, ebp, -0x10u, 0);
    result = call_registers(&port, 0x4cea15, entry->eax, 0xa, 0x516ba0, entry->eax, 0, entry->edi,
                            ebp, NULL, 0);
    return port_return(&port, result, result);
}

/* Original 0x4828a0: 0 when the joystick is on (0x598d60 1), the button al is mapped
 * (0x598d68) and 0x40ae60 reads its control (0x598d88) as 0; otherwise 1. */
uint32_t vertrix_port_button_released_4828a0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x10
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t index;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    if (port_u32(&port, 0, 0x598d60) != 1)
    {
        return port_return(&port, 1, entry->edx);
    }
    index = (entry->eax & 0xff) << 2;
    if (port_u32(&port, index, 0x598d68) == 0)
    {
        return port_return(&port, 1, entry->edx);
    }
    call_registers(&port, 0x40ae60, port_u32(&port, index, 0x598d88), ebp - 0xc, entry->ebx, 1,
                   entry->esi, entry->edi, ebp, NULL, 0);
    if (port_u32(&port, ebp, -0xcu) != 0)
    {
        return port_return(&port, 1, entry->edx);
    }
    return port_return(&port, 0, entry->edx);
}

/* Release the items edx to edx + ebx of the list eax (+4) by their method [+`methods`] with 2,
 * then 0x4d8950 on the list with edx and ebx. */
static uint32_t list_release_range(PORT_SIGNATURE, uint32_t methods)
{
    enum
    {
        BELOW = 0x1c
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t list = entry->eax;
    uint32_t end = entry->edx + entry->ebx;
    uint32_t index;
    uint32_t esi = end;
    uint32_t result;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, -0x14u, entry->edx);
    port_set32(&port, ebp, -0x18u, entry->ebx);
    port_set32(&port, ebp, -0x10u, end);
    for (index = entry->edx; index < end; index++)
    {
        uint32_t item = port_u32(&port, port_u32(&port, list, 4), index * 4);
        if (item != 0)
        {
            esi = port_u32(&port, item, methods);
            call_registers(&port, port_u32(&port, esi, 0), item, 2, index, index * 4, esi, list,
                           ebp, NULL, 0);
        }
        end = port_u32(&port, ebp, -0x10u);
    }
    result = call_registers(&port, 0x4d8950, list, port_u32(&port, ebp, -0x14u),
                            port_u32(&port, ebp, -0x18u), index * 4, esi, list, ebp, NULL, 0);
    return port_return(&port, result, vertrix_lift_edx);
}

/* Release every item of the list eax (count +8, items +4) by its method [+`methods`] with 2, then
 * 0x4d8770 on the list with 0 and -1. */
static uint32_t list_release_all(PORT_SIGNATURE, uint32_t methods)
{
    enum
    {
        BELOW = 0x1c
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t list = entry->eax;
    uint32_t count;
    uint32_t index;
    uint32_t ecx = entry->ecx;
    uint32_t esi = entry->esi;
    uint32_t result;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    count = port_u32(&port, list, 8);
    port_set32(&port, ebp, -0x18u, count);
    for (index = 0; index < count; index++)
    {
        uint32_t item = port_u32(&port, port_u32(&port, list, 4), index * 4);
        if (item != 0)
        {
            esi = port_u32(&port, item, methods);
            call_registers(&port, port_u32(&port, esi, 0), item, 2, index, index * 4, esi, list,
                           ebp, NULL, 0);
        }
        count = port_u32(&port, ebp, -0x18u);
        ecx = (index + 1) * 4;
    }
    result = call_registers(&port, 0x4d8770, list, 0, 0xffffffffu, ecx, esi, list, ebp, NULL, 0);
    return port_return(&port, result, entry->edx);
}

/* Original 0x487a40: the items' method +0xc. */
uint32_t vertrix_port_list_release_range_487a40(PORT_SIGNATURE)
{
    return list_release_range(calls, services, globals, entry, 0xc);
}

/* Original 0x487aa0: the items' method +0xc. */
uint32_t vertrix_port_list_release_all_487aa0(PORT_SIGNATURE)
{
    return list_release_all(calls, services, globals, entry, 0xc);
}

/* Original 0x48d650: the items' method +0x34. */
uint32_t vertrix_port_list_release_range_48d650(PORT_SIGNATURE)
{
    return list_release_range(calls, services, globals, entry, 0x34);
}

/* Original 0x48d6c0: the items' method +0x34. */
uint32_t vertrix_port_list_release_all_48d6c0(PORT_SIGNATURE)
{
    return list_release_all(calls, services, globals, entry, 0x34);
}

/* Original 0x487fd0: the index of the first named entry of the list eax (count +0x14, entries
 * +0x20) that 0x489d00 matches with the name edx, or -1. */
uint32_t vertrix_port_list_find_name_487fd0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x18
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t list = entry->eax;
    uint32_t index;
    uint32_t edx = 0xffffffffu;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, -0x14u, 0xffffffffu);
    for (index = 0; index < port_u32(&port, list, 0x14); index++)
    {
        edx = port_u32(&port, port_u32(&port, list, 0x20), index * 4);
        if (edx != 0)
        {
            uint32_t result = call_registers(&port, 0x489d00, edx, entry->edx, index * 4, index,
                                             list, entry->edx, ebp, NULL, 0);
            edx = vertrix_lift_edx;
            if (result == 1)
            {
                port_set32(&port, ebp, -0x14u, index);
                return port_return(&port, index, edx);
            }
        }
    }
    return port_return(&port, port_u32(&port, ebp, -0x14u), edx);
}

/* Original 0x4ac310: 0x4ac370, and when 0x4ac390 gives 1 the count from 0x4ac3b0 by 0x4ac420,
 * then for each count 0x4ac720 or (when 0x4ac7a0 gives 0) 0x4ac750. The actor is the edx each call
 * leaves. */
uint32_t vertrix_port_animation_tick_4ac310(PORT_SIGNATURE)
{
    Port port;
    uint32_t actor = entry->eax;
    uint32_t count;
    uint32_t left;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    port_forward(&port, entry, 0x4ac370, actor, actor, entry->ebx, entry->ecx);
    actor = vertrix_lift_edx;
    result = port_forward(&port, entry, 0x4ac390, actor, actor, entry->ebx, entry->ecx);
    if (result != 1)
    {
        return port_return(&port, result, entry->edx);
    }
    actor = vertrix_lift_edx;
    count = port_forward(&port, entry, 0x4ac3b0, actor, actor, entry->ebx, entry->ecx);
    actor = vertrix_lift_edx;
    result = port_forward(&port, entry, 0x4ac420, actor, actor, count, count);
    for (left = count; left != 0; left--)
    {
        actor = vertrix_lift_edx;
        if (port_forward(&port, entry, 0x4ac7a0, actor, actor, count, left) != 0)
        {
            actor = vertrix_lift_edx;
            result = port_forward(&port, entry, 0x4ac720, actor, actor, count, left);
        }
        else
        {
            actor = vertrix_lift_edx;
            result = port_forward(&port, entry, 0x4ac750, actor, actor, count, left);
        }
    }
    return port_return(&port, result, entry->edx);
}

/* Original 0x4acc70: move +0x80 toward +0x84 by edx times +0x88, stopping at it; whether it is
 * still short (edx +0x84). */
uint32_t vertrix_port_dword_transition_4acc70(PORT_SIGNATURE)
{
    Port port;
    uint32_t actor = entry->eax;
    uint32_t step;
    uint32_t value;
    uint32_t goal;
    port_open(&port, calls, services, globals, entry);
    step = entry->edx * port_u32(&port, actor, 0x88);
    value = port_u32(&port, actor, 0x80);
    goal = port_u32(&port, actor, 0x84);
    if ((int32_t)value > (int32_t)goal)
    {
        value -= step;
        if ((int32_t)value < (int32_t)goal)
        {
            value = goal;
        }
    }
    else if ((int32_t)value < (int32_t)goal)
    {
        value += step;
        if ((int32_t)value > (int32_t)goal)
        {
            value = goal;
        }
    }
    goal = port_u32(&port, actor, 0x84);
    port_set32(&port, actor, 0x80, value);
    return port_return(&port, value != goal, goal);
}

/* Original 0x4ad260: the point of the actor's angle (+0x28 high word) by 0x4ad1c0 into 0x5bb604
 * and 0x5bb608, the word at edx its +0x2c plus the first and the word at ebx its +0x2e less the
 * second. */
uint32_t vertrix_port_actor_orbit_point_4ad260(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x14
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t actor = entry->eax;
    uint32_t angle;
    uint32_t pushed[1] = {0x5bb608};
    uint32_t result;
    uint32_t edx;
    uint32_t ebx;
    uint32_t ecx;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, -0x10u, entry->ebx);
    angle = (uint32_t)((int32_t)port_u32(&port, actor, 0x28) >> 16);
    result = call_registers(&port, 0x4ad1c0, actor, angle, angle, 0x5bb604, actor, entry->edx, ebp,
                            pushed, 1);
    ebx = (angle & 0xffff0000u) | port_u16(&port, 0, 0x5bb604);
    edx = ((vertrix_lift_edx & 0xffff0000u) | port_u16(&port, actor, 0x2c)) + ebx;
    port_set16(&port, entry->edx, 0, edx);
    ecx = 0x5b0000u | port_u16(&port, 0, 0x5bb608);
    edx = ((edx & 0xffff0000u) | port_u16(&port, actor, 0x2e)) - ecx;
    port_set16(&port, port_u32(&port, ebp, -0x10u), 0, edx);
    return port_return(&port, result, edx);
}

/* Original 0x4b4100: 0x4b3360, then method +0xc of the children +0x17c and +0x180 with edx and
 * ebx. */
uint32_t vertrix_port_pair_children_call_4b4100(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x14
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t object = entry->eax;
    uint32_t child;
    uint32_t methods;
    uint32_t result;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, -0x10u, object);
    call_registers(&port, 0x4b3360, object, entry->edx, entry->ebx, entry->ebx, entry->edx,
                   entry->edi, ebp, NULL, 0);
    child = port_u32(&port, port_u32(&port, ebp, -0x10u), 0x17c);
    methods = port_u32(&port, child, 0x158);
    call_registers(&port, port_u32(&port, methods, 0xc), child, entry->edx, entry->ebx, entry->ebx,
                   entry->edx, methods, ebp, NULL, 0);
    child = port_u32(&port, port_u32(&port, ebp, -0x10u), 0x180);
    methods = port_u32(&port, child, 0x158);
    result = call_registers(&port, port_u32(&port, methods, 0xc), child, entry->edx, entry->ebx,
                            entry->ebx, entry->edx, methods, ebp, NULL, 0);
    return port_return(&port, result, vertrix_lift_edx);
}

/* Original 0x480890: the 256 VGA colours at eax (6 bits a channel) as 8-bit entries at
 * 0x598630, each with the flag byte 2. */
uint32_t vertrix_port_palette_expand_vga_480890(PORT_SIGNATURE)
{
    Port port;
    uint32_t index;
    port_open(&port, calls, services, globals, entry);
    for (index = 0; index < 0x100; index++)
    {
        uint32_t channel;
        for (channel = 0; channel < 3; channel++)
        {
            port_set8(&port, index * 4 + channel, 0x598630,
                      port_u8(&port, entry->eax + index * 3, channel) << 2);
        }
        port_set8(&port, index * 4, 0x598633, 2);
    }
    return port_return(&port, 0x100, entry->edx);
}

/* Original 0x4808f0: the palette 0x598630 made by the method +0x14 of the device edx (flags 0x44,
 * into 0x598628); 1 when that fails, otherwise 0x486e20 and 0x485700 and 0. */
uint32_t vertrix_port_palette_create_4808f0(PORT_SIGNATURE)
{
    Port port;
    uint32_t device = entry->edx;
    uint32_t methods;
    uint32_t pushed[5];
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    methods = port_u32(&port, device, 0);
    pushed[0] = device;
    pushed[1] = 0x44;
    pushed[2] = 0x598630;
    pushed[3] = 0x598628;
    pushed[4] = 0;
    result = call_registers(&port, port_u32(&port, methods, 0x14), methods, device, entry->eax,
                            entry->ecx, entry->esi, entry->edi, entry->ebp, pushed, 5);
    if (result == 0)
    {
        return port_return(&port, 1, vertrix_lift_edx);
    }
    port_forward(&port, entry, 0x486e20, 0x5b9c50, entry->eax, entry->eax, result);
    port_forward(&port, entry, 0x485700, 0x5b9c50, 1, 0x50f6bb, result);
    return port_return(&port, 0, vertrix_lift_edx);
}
