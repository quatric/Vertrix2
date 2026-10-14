#include "port_handlers.h"

/* State handlers of the interface objects, table releases and device notifications. */

/* The slot +4 found by 0x4b5eb0 in the storage list 0x54671c. */
static uint32_t storage_find(Port *port, const LiftEntry *entry, uint32_t object)
{
    return port_forward(port, entry, 0x4b5eb0, 0x54671c, port_u32(port, object, 4), entry->ebx,
                        object);
}

/* Original 0x450300: when the slot is found with a clear +0x58, the handler 0x450130 by
 * 0x4ac8f0. */
uint32_t vertrix_port_ui_border_storage_update_450300(PORT_SIGNATURE)
{
    Port port;
    uint32_t object = entry->eax;
    uint32_t found;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    found = storage_find(&port, entry, object);
    if (found == 0 || port_u32(&port, found, 0x58) != 0)
    {
        return port_return(&port, found, entry->edx);
    }
    result = port_forward(&port, entry, 0x4ac8f0, object, 0x450130, entry->ebx, object);
    return port_return(&port, result, entry->edx);
}

/* Original 0x450920: when the slot is found with +0x58 1, the handler 0x450960 by 0x4ac610 and
 * 0x4ac8f0. */
uint32_t vertrix_port_ui_companion_storage_update_450920(PORT_SIGNATURE)
{
    Port port;
    uint32_t object = entry->eax;
    uint32_t found;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    found = storage_find(&port, entry, object);
    if (found == 0 || port_u32(&port, found, 0x58) != 1)
    {
        return port_return(&port, found, entry->edx);
    }
    port_forward(&port, entry, 0x4ac610, object, 0x450960, entry->ebx, object);
    result = port_forward(&port, entry, 0x4ac8f0, object, vertrix_lift_edx, entry->ebx, object);
    return port_return(&port, result, entry->edx);
}

/* Original 0x4509d0: when the slot is found with a clear +0x58, clear +0x124 and the handler
 * 0x450860 by 0x4ac8f0. */
uint32_t vertrix_port_ui_companion_storage_update_4509d0(PORT_SIGNATURE)
{
    Port port;
    uint32_t object = entry->eax;
    uint32_t found;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    found = storage_find(&port, entry, object);
    if (found == 0 || port_u32(&port, found, 0x58) != 0)
    {
        return port_return(&port, found, entry->edx);
    }
    port_set32(&port, object, 0x124, 0);
    result = port_forward(&port, entry, 0x4ac8f0, object, 0x450860, entry->ebx, object);
    return port_return(&port, result, entry->edx);
}

/* `first`, and when `check` gives 1, the handler by 0x4ac510, then 0x4ac8f0. */
static uint32_t gate_handler(PORT_SIGNATURE, uint32_t first, uint32_t check, uint32_t handler)
{
    Port port;
    uint32_t object = entry->eax;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    port_forward(&port, entry, first, object, entry->edx, entry->ebx, object);
    result = port_forward(&port, entry, check, object, vertrix_lift_edx, entry->ebx, object);
    if (result != 1)
    {
        return port_return(&port, result, entry->edx);
    }
    port_forward(&port, entry, 0x4ac510, object, handler, entry->ebx, object);
    result = port_forward(&port, entry, 0x4ac8f0, object, vertrix_lift_edx, entry->ebx, object);
    return port_return(&port, result, entry->edx);
}

/* Original 0x450830: 0x4ac500 and 0x4ac520, handler 0x450750. */
uint32_t vertrix_port_player_countdown_update_450830(PORT_SIGNATURE)
{
    return gate_handler(calls, services, globals, entry, 0x4ac500, 0x4ac520, 0x450750);
}

/* Original 0x4509a0: 0x4ac600 and 0x4ac620, handler 0x4509d0. */
uint32_t vertrix_port_ui_companion_storage_update_4509a0(PORT_SIGNATURE)
{
    return gate_handler(calls, services, globals, entry, 0x4ac600, 0x4ac620, 0x4509d0);
}

/* Original 0x450960: 0x4ac600, and when 0x4ac620 gives 1, 0x4adfa0 (edx 0), 0x4adfe0 with
 * 0x4509a0, 0x4ac8f0 and 0x4ac610. */
uint32_t vertrix_port_ui_companion_storage_update_450960(PORT_SIGNATURE)
{
    Port port;
    uint32_t object = entry->eax;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    port_forward(&port, entry, 0x4ac600, object, entry->edx, entry->ebx, object);
    result = port_forward(&port, entry, 0x4ac620, object, vertrix_lift_edx, entry->ebx, object);
    if (result != 1)
    {
        return port_return(&port, result, entry->edx);
    }
    port_forward(&port, entry, 0x4adfa0, object, 0, entry->ebx, object);
    port_forward(&port, entry, 0x4adfe0, object, 0x4509a0, entry->ebx, object);
    port_forward(&port, entry, 0x4ac8f0, object, vertrix_lift_edx, entry->ebx, object);
    result = port_forward(&port, entry, 0x4ac610, object, vertrix_lift_edx, entry->ebx, object);
    return port_return(&port, result, entry->edx);
}

/* The second method of the child +0x15c; its result. */
static uint32_t child_update(Port *port, const LiftEntry *entry, uint32_t child, uint32_t edx,
                             uint32_t ebx, uint32_t ecx)
{
    uint32_t methods = port_u32(port, child, 0x158);
    return port_forward(port, entry, port_u32(port, methods, 4), child, edx, ebx, ecx);
}

/* Original 0x451f10: when 0x43bc90 gives 0, the handler 0x451f50 by 0x4ac8f0; then the child
 * update (its result). */
uint32_t vertrix_port_player_child_update_451f10(PORT_SIGNATURE)
{
    Port port;
    uint32_t object = entry->eax;
    uint32_t child;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    child = port_u32(&port, object, 0x15c);
    result = port_forward(&port, entry, 0x43bc90, object, entry->edx, child, object);
    if (result == 0)
    {
        port_forward(&port, entry, 0x4ac8f0, object, 0x451f50, child, object);
    }
    result =
        child_update(&port, entry, child, vertrix_lift_edx, child, port_u32(&port, child, 0x158));
    return port_return(&port, result, entry->edx);
}

/* `check` and, when it gives 1, 0x43bd80 on the edx it leaves; then the child update (its result).
 */
static uint32_t check_child(PORT_SIGNATURE, uint32_t check)
{
    Port port;
    uint32_t object = entry->eax;
    uint32_t child;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    child = port_u32(&port, object, 0x15c);
    result = port_forward(&port, entry, check, object, object, entry->ebx, child);
    if (result == 1)
    {
        result = port_forward(&port, entry, 0x43bd80, vertrix_lift_edx, vertrix_lift_edx,
                              entry->ebx, child);
    }
    result = child_update(&port, entry, child, port_u32(&port, child, 0x158), entry->ebx, child);
    return port_return(&port, result, entry->edx);
}

/* Original 0x452070: through 0x43bd60. */
uint32_t vertrix_port_player_check_child_452070(PORT_SIGNATURE)
{
    return check_child(calls, services, globals, entry, 0x43bd60);
}

/* Original 0x4520b0: through 0x43cc90. */
uint32_t vertrix_port_player_check_child_4520b0(PORT_SIGNATURE)
{
    return check_child(calls, services, globals, entry, 0x43cc90);
}

/* Original 0x456ca0: with byte +0x15c clear, the handler 0x456980 by 0x4ac8f0; otherwise clear
 * byte +0x15d when it is 1. */
uint32_t vertrix_port_toggle_handler_456ca0(PORT_SIGNATURE)
{
    Port port;
    uint32_t object = entry->eax;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    if (port_u8(&port, object, 0x15c) == 0)
    {
        result = port_forward(&port, entry, 0x4ac8f0, object, 0x456980, entry->ebx, entry->ecx);
        return port_return(&port, result, entry->edx);
    }
    if (port_u8(&port, object, 0x15d) == 1)
    {
        port_set8(&port, object, 0x15d, 0);
    }
    return port_return(&port, object, entry->edx);
}

/* Original 0x457730: when 0x476530 on 0x54d640 (edx 0) gives a nonzero word, keep 0x4f7bdc at
 * 0x532a5c and 0x476320 with the word. */
uint32_t vertrix_port_point_list_take_457730(PORT_SIGNATURE)
{
    Port port;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    result = port_forward(&port, entry, 0x476530, 0x54d640, 0, entry->ebx, entry->ecx);
    if ((result & 0xffff) != 0)
    {
        port_set32(&port, 0, 0x532a5c, port_u32(&port, 0, 0x4f7bdc));
        result =
            port_forward(&port, entry, 0x476320, 0x54d640, result & 0xffff, entry->ebx, entry->ecx);
    }
    return port_return(&port, result, entry->edx);
}

/* Original 0x45c210: 0x4ac500, and when 0x4ac520 gives 1, 0x4ac5b0 with what 0x4ac540 gives,
 * then 0x4ad750 and, when that gives 0, 0x4ac940. */
uint32_t vertrix_port_actor_step_then_finish_45c210(PORT_SIGNATURE)
{
    Port port;
    uint32_t actor = entry->eax;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    port_forward(&port, entry, 0x4ac500, actor, entry->edx, entry->ebx, actor);
    result = port_forward(&port, entry, 0x4ac520, actor, vertrix_lift_edx, entry->ebx, actor);
    if (result != 1)
    {
        return port_return(&port, result, entry->edx);
    }
    result = port_forward(&port, entry, 0x4ac540, actor, vertrix_lift_edx, entry->ebx, actor);
    port_forward(&port, entry, 0x4ac5b0, actor, result, entry->ebx, actor);
    result = port_forward(&port, entry, 0x4ad750, actor, vertrix_lift_edx, entry->ebx, actor);
    if (result == 0)
    {
        result = port_forward(&port, entry, 0x4ac940, actor, vertrix_lift_edx, entry->ebx, actor);
    }
    return port_return(&port, result, entry->edx);
}

/* Original 0x45c2b0: set 0x532b44 when 0x476530 on 0x54d640 gives a nonzero word other than
 * 0x532b94 and below 0x6b. */
uint32_t vertrix_port_point_list_check_45c2b0(PORT_SIGNATURE)
{
    Port port;
    uint32_t result;
    uint32_t word;
    port_open(&port, calls, services, globals, entry);
    result = port_forward(&port, entry, 0x476530, 0x54d640, 0, entry->ebx, entry->ecx);
    word = result & 0xffff;
    if (word != 0 && word != port_u32(&port, 0, 0x532b94) && word < 0x6b)
    {
        port_set32(&port, 0, 0x532b44, 1);
    }
    return port_return(&port, result, entry->edx);
}

/* Original 0x45e630: build the table at 0x544d44 (0x544d60 for a nonzero eax) by 0x4875a0 with
 * 0x78 by 0x30 cells. */
uint32_t vertrix_port_table_build_by_flag_45e630(PORT_SIGNATURE)
{
    Port port;
    uint32_t result;
    uint32_t pushed[10] = {0, 0, 0, 0, 0x78, 0x30, 0, 0, 1, 4};
    port_open(&port, calls, services, globals, entry);
    result = port_forward_stack(&port, entry, 0x4875a0, entry->eax != 0 ? 0x544d60 : 0x544d44,
                                entry->edx, 0x78, 0x30, entry->esi, pushed, 10);
    return port_return(&port, result, vertrix_lift_edx);
}

/* 0x4874f0 on each entry of 28 bytes from `start` to `end` (edx the next entry, ecx the end);
 * the next entry is the edx the call leaves. */
static uint32_t entries_release(Port *port, const LiftEntry *entry, uint32_t start, uint32_t end,
                                uint32_t ebx)
{
    uint32_t at = start;
    uint32_t result;
    do
    {
        uint32_t current = at;
        at += 0x1c;
        result = port_forward(port, entry, 0x4874f0, current, at, ebx, end);
        at = vertrix_lift_edx;
    } while (at != end);
    return result;
}

/* Original 0x45e910: the 19 rows of ten entries at 0x544f90 (ebx the row). */
uint32_t vertrix_port_table_release_rows_45e910(PORT_SIGNATURE)
{
    Port port;
    uint32_t row;
    uint32_t result = entry->eax;
    port_open(&port, calls, services, globals, entry);
    for (row = 0; row < 0x13; row++)
    {
        uint32_t start = 0x544f90 + row * 0x118;
        result = entries_release(&port, entry, start, start + 0x118, row);
    }
    return port_return(&port, result, entry->edx);
}

/* Original 0x45ea80: the seven entries at 0x544ac0 and the seven at 0x546554. */
uint32_t vertrix_port_table_release_pair_45ea80(PORT_SIGNATURE)
{
    Port port;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    entries_release(&port, entry, 0x544ac0, 0x544ac0 + 0xc4, entry->ebx);
    result = entries_release(&port, entry, 0x546554, 0x546554 + 0xc4, entry->ebx);
    return port_return(&port, result, entry->edx);
}

/* Original 0x4725f0: clear +0x94c of the scene 0x190 found by 0x4b5eb0 in 0x546744. */
uint32_t vertrix_port_scene_clear_marker_4725f0(PORT_SIGNATURE)
{
    Port port;
    uint32_t scene;
    port_open(&port, calls, services, globals, entry);
    scene = port_forward(&port, entry, 0x4b5eb0, 0x546744, 0x190, entry->ebx, entry->ecx);
    if (scene != 0)
    {
        port_set32(&port, scene, 0x94c, 0);
    }
    return port_return(&port, scene, entry->edx);
}

/* Original 0x472bd0: allocate 0x954 bytes by 0x4ca000 (constructed by 0x43d6a0 when that
 * worked), set them up by 0x43dff0, give them the id 0x190 and add them to 0x546744 by
 * 0x4b5e70. */
uint32_t vertrix_port_scene_create_472bd0(PORT_SIGNATURE)
{
    Port port;
    uint32_t scene;
    uint32_t result;
    uint32_t edx;
    port_open(&port, calls, services, globals, entry);
    scene = port_forward(&port, entry, 0x4ca000, 0x954, entry->edx, entry->ebx, entry->ecx);
    if (scene != 0)
    {
        scene =
            port_forward(&port, entry, 0x43d6a0, scene, vertrix_lift_edx, entry->ebx, entry->ecx);
    }
    port_forward(&port, entry, 0x43dff0, scene, scene, entry->ebx, entry->ecx);
    edx = vertrix_lift_edx;
    port_set32(&port, edx, 0, 0x190);
    result = port_forward(&port, entry, 0x4b5e70, 0x546744, edx, entry->ebx, entry->ecx);
    return port_return(&port, result, entry->edx);
}

/* Original 0x472d50: with a panel at 0x546794, its first method (edx 2), then clear it. */
uint32_t vertrix_port_ui_panel_release_full_472d50(PORT_SIGNATURE)
{
    Port port;
    uint32_t panel;
    uint32_t methods;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    panel = port_u32(&port, 0, 0x546794);
    if (panel == 0)
    {
        return port_return(&port, entry->eax, entry->edx);
    }
    methods = port_u32(&port, panel, 0x158);
    result = port_forward(&port, entry, port_u32(&port, methods, 0), panel, 2, entry->ebx, methods);
    port_set32(&port, 0, 0x546794, 0);
    return port_return(&port, result, entry->edx);
}

/* Original 0x4735e0: when 0x476480 on 0x54d640 with the word eax gives 1, 0x476720 with the word
 * edx (ebx edx). */
uint32_t vertrix_port_point_list_conditional_4735e0(PORT_SIGNATURE)
{
    Port port;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    result =
        port_forward(&port, entry, 0x476480, 0x54d640, entry->eax & 0xffff, entry->edx, entry->ecx);
    if (result == 1)
    {
        result = port_forward(&port, entry, 0x476720, 0x54d640, entry->edx & 0xffff, entry->edx,
                              entry->ecx);
    }
    return port_return(&port, result, vertrix_lift_edx);
}

/* Original 0x4754e0: the 256 dwords at 0x54cdd0 set to those at 0x54d1d0 plus 4 eax, and
 * 0x54cdcc pointed at them. */
uint32_t vertrix_port_palette_tables_cycle_4754e0(PORT_SIGNATURE)
{
    Port port;
    uint32_t step = entry->eax * 4;
    uint32_t offset;
    port_open(&port, calls, services, globals, entry);
    for (offset = 0; offset != 0x400; offset += 4)
    {
        port_set32(&port, offset, 0x54cdd0, port_u32(&port, offset, 0x54d1d0) + step);
    }
    port_set32(&port, 0, 0x54cdcc, 0x54cdd0);
    return port_return(&port, 0x400, entry->edx);
}

/* Original 0x4762e0: select slot word edx (of 96 bytes) from eax at 0x54d630; when its first
 * byte is 1, 0x475790 on +4 (one zero argument). */
uint32_t vertrix_port_slot_select_4762e0(PORT_SIGNATURE)
{
    Port port;
    uint32_t index = entry->edx & 0xffff;
    uint32_t slot = entry->eax + index * 96;
    uint32_t kind;
    uint32_t result;
    uint32_t pushed[1] = {0};
    port_open(&port, calls, services, globals, entry);
    port_set32(&port, 0, 0x54d630, slot);
    kind = port_u8(&port, slot, 0);
    if (kind != 1)
    {
        return port_return(&port, slot, (index & 0xff00) | kind);
    }
    result = port_forward_stack(&port, entry, 0x475790, slot + 4, 0, 0, 0, entry->esi, pushed, 1);
    return port_return(&port, result, vertrix_lift_edx);
}

/* Original 0x476c80: whether method 7 of the interface +0x10 succeeds (not negative), kept at
 * +4; 0 without one. */
uint32_t vertrix_port_sound_check_primary_476c80(PORT_SIGNATURE)
{
    Port port;
    uint32_t object = entry->eax;
    uint32_t face;
    uint32_t methods;
    uint32_t result;
    uint32_t pushed[1];
    port_open(&port, calls, services, globals, entry);
    face = port_u32(&port, object, 0x10);
    if (face != 0)
    {
        methods = port_u32(&port, face, 0);
        pushed[0] = face;
        result = port_forward_stack(&port, entry, port_u32(&port, methods, 0x1c), face, methods,
                                    object, entry->ecx, entry->esi, pushed, 1);
        if ((int32_t)result >= 0)
        {
            port_set32(&port, object, 4, 1);
            return port_return(&port, 1, entry->edx);
        }
    }
    port_set32(&port, object, 4, 0);
    return port_return(&port, 0, entry->edx);
}

/* Original 0x477ed0: when +0x60 is 1, clear it, 0x477d70, move to the words +0x50 and +0x52 by
 * 0x478480 and 0x478460. */
uint32_t vertrix_port_object_reset_center_477ed0(PORT_SIGNATURE)
{
    Port port;
    uint32_t object = entry->eax;
    uint32_t y;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    if (port_u32(&port, object, 0x60) != 1)
    {
        return port_return(&port, object, entry->edx);
    }
    port_set32(&port, object, 0x60, 0);
    port_forward(&port, entry, 0x477d70, object, entry->edx, entry->ebx, object);
    y = port_u16(&port, object, 0x52);
    port_forward(&port, entry, 0x478480, object, port_u16(&port, object, 0x50), y, object);
    result = port_forward(&port, entry, 0x478460, object, vertrix_lift_edx, y, object);
    return port_return(&port, result, entry->edx);
}

/* Original 0x478c90: copy the text at 0x50e99f to 0x558970 (two bytes a step) and 0x40a860 with
 * it (ebx 100). */
uint32_t vertrix_port_literal_copy_call_478c90(PORT_SIGNATURE)
{
    Port port;
    uint32_t from = 0x50e99f;
    uint32_t to = 0x558970;
    uint32_t value;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    for (;;)
    {
        value = port_u8(&port, from, 0);
        port_set8(&port, to, 0, value);
        if (value == 0)
        {
            break;
        }
        value = port_u8(&port, from, 1);
        from += 2;
        port_set8(&port, to, 1, value);
        to += 2;
        if (value == 0)
        {
            break;
        }
    }
    vertrix_lift_in_esi = from;
    vertrix_lift_in_edi = 0x558970;
    vertrix_lift_in_ebp = entry->ebp;
    result = port_call(&port, 0x40a860, entry->eax, 0x558970, 0x64, entry->eax);
    vertrix_lift_in_esi = vertrix_lift_in_edi = vertrix_lift_in_ebp = 0;
    return port_return(&port, result, entry->edx);
}

/* Original 0x478ed0: the target of 0x478eb0 kept at 0x5589e8 and the size byte +0xc at
 * 0x5589e4; ecx written there in 4, 1 or 2 bytes. */
uint32_t vertrix_port_surface_write_478ed0(PORT_SIGNATURE)
{
    Port port;
    uint32_t target;
    uint32_t size;
    port_open(&port, calls, services, globals, entry);
    target = port_forward_esi(&port, entry, 0x478eb0, entry->eax, entry->edx, entry->ebx,
                              entry->ecx, entry->eax);
    size = port_u8(&port, entry->eax, 0xc);
    port_set32(&port, 0, 0x5589e8, target);
    port_set8(&port, 0, 0x5589e4, size);
    if (size == 4)
    {
        port_set32(&port, target, 0, entry->ecx);
    }
    else if (size == 1)
    {
        port_set8(&port, target, 0, entry->ecx);
    }
    else if (size == 2)
    {
        port_set16(&port, target, 0, entry->ecx);
    }
    return port_return(&port, target, (vertrix_lift_edx & 0xffffff00u) | size);
}

/* Original 0x47f160: the length of the chain from +0xc through +0x60. */
uint32_t vertrix_port_display_chain_count_47f160(PORT_SIGNATURE)
{
    Port port;
    uint32_t link;
    uint32_t count = 0;
    port_open(&port, calls, services, globals, entry);
    for (link = port_u32(&port, entry->eax, 0xc); link != 0; link = port_u32(&port, link, 0x60))
    {
        count++;
    }
    return port_return(&port, count, entry->edx);
}

/* Original 0x47f3d0: with a device (+0), release its buffer +0x10 by method 5 (clearing it) and
 * finish by 0x47f0f0. */
uint32_t vertrix_port_display_release_buffer_47f3d0(PORT_SIGNATURE)
{
    Port port;
    uint32_t object = entry->eax;
    uint32_t device;
    uint32_t buffer;
    uint32_t esi = entry->esi;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    device = port_u32(&port, object, 0);
    if (device == 0)
    {
        return port_return(&port, object, entry->edx);
    }
    buffer = port_u32(&port, object, 0x10);
    if (buffer != 0)
    {
        uint32_t methods = port_u32(&port, device, 0);
        uint32_t pushed[3] = {device, buffer, 0};
        esi = buffer;
        port_forward_stack(&port, entry, port_u32(&port, methods, 0x14), device, methods, object,
                           entry->ecx, esi, pushed, 3);
        port_set32(&port, object, 0x10, 0);
    }
    result = port_forward_esi(&port, entry, 0x47f0f0, object,
                              buffer != 0 ? vertrix_lift_edx : device, object, entry->ecx, esi);
    return port_return(&port, result, entry->edx);
}

/* Original 0x47f9b0: whether 0x47e7d0 and then 0x47fd70 (edx 0x51698c) both give 1. */
uint32_t vertrix_port_checked_calls_47f9b0(PORT_SIGNATURE)
{
    Port port;
    uint32_t object = entry->eax;
    port_open(&port, calls, services, globals, entry);
    if (port_forward(&port, entry, 0x47e7d0, object, entry->edx, entry->ebx, object) != 1)
    {
        return port_return(&port, 0, entry->edx);
    }
    if (port_forward(&port, entry, 0x47fd70, object, 0x51698c, 0, object) != 1)
    {
        return port_return(&port, 0, entry->edx);
    }
    return port_return(&port, 1, entry->edx);
}

/* Original 0x47f9e0: 0x47ea20, then whether 0x47f750 (edx the given ebx) and 0x47f770 (edx the
 * given edx) both give 1; edi the given edx throughout. */
uint32_t vertrix_port_checked_calls_47f9e0(PORT_SIGNATURE)
{
    Port port;
    uint32_t object = entry->eax;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    port_call_with(&port, 0x47ea20, object, entry->edx, entry->ebx, object, entry->esi, entry->edx,
                   entry->ebp);
    result = port_call_with(&port, 0x47f750, object, entry->ebx, entry->ebx, object, entry->esi,
                            entry->edx, entry->ebp);
    if (result != 1)
    {
        return port_return(&port, 0, vertrix_lift_edx);
    }
    result = port_call_with(&port, 0x47f770, object, entry->edx, entry->ebx, object, 0, entry->edx,
                            entry->ebp);
    return port_return(&port, result == 1, vertrix_lift_edx);
}

/* With an interface (+0x1bc) and a value (+0x1c0), its method 8 with the value, `kind` and 0. */
static uint32_t notify(PORT_SIGNATURE, uint32_t kind)
{
    Port port;
    uint32_t object = entry->eax;
    uint32_t face;
    uint32_t value;
    uint32_t methods;
    uint32_t result;
    uint32_t pushed[4];
    port_open(&port, calls, services, globals, entry);
    face = port_u32(&port, object, 0x1bc);
    if (face == 0)
    {
        return port_return(&port, object, entry->edx);
    }
    value = port_u32(&port, object, 0x1c0);
    if (value == 0)
    {
        return port_return(&port, object, entry->edx);
    }
    methods = port_u32(&port, face, 0);
    pushed[0] = face;
    pushed[1] = value;
    pushed[2] = kind;
    pushed[3] = 0;
    result = port_forward_stack(&port, entry, port_u32(&port, methods, 0x20), object, face, value,
                                methods, entry->esi, pushed, 4);
    return port_return(&port, result, entry->edx);
}

/* Original 0x47fe20: kind 1. */
uint32_t vertrix_port_display_notify_47fe20(PORT_SIGNATURE)
{
    return notify(calls, services, globals, entry, 1);
}

/* Original 0x47fe50: kind 2. */
uint32_t vertrix_port_display_notify_47fe50(PORT_SIGNATURE)
{
    return notify(calls, services, globals, entry, 2);
}

/* Original 0x480030: clear the 0x5c bytes from +0x48 by 0x4eb5c0, set their size and, with an
 * interface (+0), its method 34 with +0x38, them and 0. */
uint32_t vertrix_port_display_describe_480030(PORT_SIGNATURE)
{
    Port port;
    uint32_t object = entry->eax;
    uint32_t block = object + 0x48;
    uint32_t face;
    uint32_t methods;
    uint32_t result;
    uint32_t pushed[4];
    port_open(&port, calls, services, globals, entry);
    result = port_forward_esi(&port, entry, 0x4eb5c0, block, 0, 0x5c, object, block);
    face = port_u32(&port, object, 0);
    if (face == 0)
    {
        return port_return(&port, result, entry->edx);
    }
    pushed[0] = face;
    pushed[1] = port_u32(&port, object, 0x38);
    pushed[2] = block;
    pushed[3] = 0;
    port_set32(&port, object, 0x48, 0x5c);
    methods = port_u32(&port, face, 0);
    result = port_forward_stack(&port, entry, port_u32(&port, methods, 0x88), face, methods,
                                pushed[1], object, block, pushed, 4);
    return port_return(&port, result, entry->edx);
}

/* Original 0x48c280: when +0x44 is 1, keep 0x598d40 at +0x1d4 and send the 8 bytes from +0x1d0
 * by 0x48c9b0; otherwise 0. */
uint32_t vertrix_port_object_notify_global_48c280(PORT_SIGNATURE)
{
    Port port;
    uint32_t object = entry->eax;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    if (port_u32(&port, object, 0x44) != 1)
    {
        return port_return(&port, 0, entry->edx);
    }
    port_set32(&port, object, 0x1d4, port_u32(&port, 0, 0x598d40));
    result = port_forward(&port, entry, 0x48c9b0, object, object + 0x1d0, 8, entry->ecx);
    return port_return(&port, result, entry->edx);
}

/* Original 0x48c2b0: keep byte 0x532a68 (0x532a6c unless +0x44 is 1) at +0x1e1 and send the 2
 * bytes from +0x1e0. */
uint32_t vertrix_port_object_notify_choice_48c2b0(PORT_SIGNATURE)
{
    Port port;
    uint32_t object = entry->eax;
    uint32_t value;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    value = port_u8(&port, 0, port_u32(&port, object, 0x44) == 1 ? 0x532a68 : 0x532a6c);
    port_set8(&port, object, 0x1e1, value);
    result = port_forward(&port, entry, 0x48c9b0, object, object + 0x1e0, 2, entry->ecx);
    return port_return(&port, result, entry->edx);
}

/* Original 0x48c2e0: keep byte 0x532a70 at +0x1e3 and, when +0x44 is 1, send the 2 bytes from
 * +0x1e2; otherwise 0. */
uint32_t vertrix_port_object_notify_byte_48c2e0(PORT_SIGNATURE)
{
    Port port;
    uint32_t object = entry->eax;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    port_set8(&port, object, 0x1e3, port_u8(&port, 0, 0x532a70));
    if (port_u32(&port, object, 0x44) != 1)
    {
        return port_return(&port, 0, entry->edx);
    }
    result = port_forward(&port, entry, 0x48c9b0, object, object + 0x1e2, 2, entry->ecx);
    return port_return(&port, result, entry->edx);
}

/* Original 0x48c330: send the byte +0x1e5. */
uint32_t vertrix_port_object_notify_field_48c330(PORT_SIGNATURE)
{
    Port port;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    result = port_forward(&port, entry, 0x48c9b0, entry->eax, entry->eax + 0x1e5, 1, entry->ecx);
    return port_return(&port, result, entry->edx);
}
