#include "port_routines.h"

/* Short straight-line routines: setups, copies and call sequences. */

enum
{
    SIDE_TABLE = 0x4f9c14,
    SIDE = 0x532bbc,
    RANDOM = 0x598d30,
    SOUND_CUES = 0x54d640
};

/* Original 0x40af90: flag 0x52f14c, wait for the handle at [0x52f140] without a time limit (the
 * import 0x4f1cfc) and close it (0x4f1b2c). */
uint32_t vertrix_port_wait_and_close_40af90(PORT_SIGNATURE)
{
    Port port;
    uint32_t pushed[2];
    uint32_t handle;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    port_set32(&port, 0, 0x52f14c, 1);
    handle = port_u32(&port, 0, 0x52f140);
    pushed[0] = handle;
    pushed[1] = 0xffffffff;
    result = port_forward_stack(&port, entry, 0x4f1cfc, entry->eax, entry->edx, entry->ebx, handle,
                                entry->esi, pushed, 2);
    pushed[0] = port_u32(&port, 0, 0x52f140);
    result = port_forward_stack(&port, entry, 0x4f1b2c, result, vertrix_lift_edx, pushed[0], handle,
                                entry->esi, pushed, 1);
    return port_return(&port, result, entry->edx);
}

/* Original 0x40b0a0: fill the record: the text 0x50c7fc (0x1e bytes, 0x4eb860) from +2, the word
 * 0x104 at +0 and 0xfff at +0x20; 0. */
uint32_t vertrix_port_record_setup_40b0a0(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    port_forward(&port, entry, 0x4eb860, entry->eax + 2, 0x50c7fc, 0x1e, entry->eax);
    port_set16(&port, entry->eax, 0, 0x104);
    port_set32(&port, entry->eax, 0x20, 0xfff);
    return port_return(&port, 0, entry->edx);
}

/* Original 0x412390: 0x489170 on edx for the eight entries at +0x5b8 (ebx 1), then for the twelve
 * at +0 (ebx the dword +0x5bc). */
uint32_t vertrix_port_object_pair_489170_412390(PORT_SIGNATURE)
{
    Port port;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    port_call_with(&port, 0x489170, entry->edx, entry->eax + 0x5b8, 1, 8, entry->edx, entry->eax,
                   entry->ebp);
    result =
        port_call_with(&port, 0x489170, entry->edx, entry->eax, port_u32(&port, entry->eax, 0x5bc),
                       0xc, entry->edx, entry->eax, entry->ebp);
    return port_return(&port, result, vertrix_lift_edx);
}

/* Copy the twelve bytes at `source` to `target`. */
static void copy_twelve(Port *port, uint32_t target, uint32_t source)
{
    uint32_t offset;
    for (offset = 0; offset < 12; offset += 4)
    {
        port_set32(port, target, offset, port_u32(port, source, offset));
    }
}

/* Original 0x412650: load record edx (12 bytes each) into the current record at +0x5c0. */
uint32_t vertrix_port_record_load_current_412650(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    copy_twelve(&port, entry->eax + 0x5c0, entry->eax + entry->edx * 12);
    return port_return(&port, 12, entry->edx);
}

/* Original 0x412690: store the current record at +0x5c0 into record edx. */
uint32_t vertrix_port_record_store_current_412690(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    copy_twelve(&port, entry->eax + entry->edx * 12, entry->eax + 0x5c0);
    return port_return(&port, 12, entry->edx);
}

/* Original 0x415470: a random value (0x4826c0 over 0x598d30) in range eax of the table at 0x53bcd0
 * (low and high dwords): low plus a draw below high - low + 1. */
uint32_t vertrix_port_random_in_range_415470(PORT_SIGNATURE)
{
    Port port;
    uint32_t range = entry->eax * 8;
    uint32_t low;
    uint32_t draw;
    port_open(&port, calls, services, globals, entry);
    low = port_u32(&port, range, 0x53bcd0);
    draw = port_forward(&port, entry, 0x4826c0, RANDOM,
                        (port_u32(&port, range, 0x53bcd4) - low + 1) & 0xffff, entry->ebx, range);
    return port_return(&port, (draw & 0xffff) + port_u32(&port, range, 0x53bcd0), entry->edx);
}

/* The session register resets: the value at 0x5332bc into the given registers, and the four
 * dwords from 0x532aa4 cleared. */
static void clear_session_counts(Port *port)
{
    uint32_t offset;
    for (offset = 0; offset < 0x10; offset += 4)
    {
        port_set32(port, offset, 0x532aa4, 0);
    }
}

/* Original 0x415b50: the value into 0x532a68, 0x532a6c and 0x532a70. */
uint32_t vertrix_port_session_registers_reset_415b50(PORT_SIGNATURE)
{
    Port port;
    uint32_t value;
    port_open(&port, calls, services, globals, entry);
    value = port_u32(&port, 0, 0x5332bc);
    port_set32(&port, 0, 0x532a68, value);
    port_set32(&port, 0, 0x532a6c, value);
    port_set32(&port, 0, 0x532a70, value);
    clear_session_counts(&port);
    return port_return(&port, value, entry->edx);
}

/* Original 0x415b90: the value into 0x532a68 and 0x532a70, -1 into 0x532a6c. */
uint32_t vertrix_port_session_registers_reset_open_415b90(PORT_SIGNATURE)
{
    Port port;
    uint32_t value;
    port_open(&port, calls, services, globals, entry);
    value = port_u32(&port, 0, 0x5332bc);
    port_set32(&port, 0, 0x532a68, value);
    port_set32(&port, 0, 0x532a6c, 0xffffffff);
    port_set32(&port, 0, 0x532a70, value);
    clear_session_counts(&port);
    return port_return(&port, value, entry->edx);
}

/* Original 0x415bd0: the value into 0x532a6c only. */
uint32_t vertrix_port_session_registers_reset_secondary_415bd0(PORT_SIGNATURE)
{
    Port port;
    uint32_t value;
    port_open(&port, calls, services, globals, entry);
    value = port_u32(&port, 0, 0x5332bc);
    port_set32(&port, 0, 0x532a6c, value);
    clear_session_counts(&port);
    return port_return(&port, value, entry->edx);
}

/* Original 0x415d60: the current cell (index at 0x53bb10) of the table at 0x53bad8. */
uint32_t vertrix_port_global_read_current_cell_415d60(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    return port_return(&port, port_u32(&port, port_u32(&port, 0, 0x53bb10) * 4, 0x53bad8),
                       entry->edx);
}

/* Original 0x417030: keep the value of 0x4ce080 at 0x532bb4 and 64 times it over 100 at 0x532b98,
 * then 0x478b40 with that. */
uint32_t vertrix_port_volume_setup_417030(PORT_SIGNATURE)
{
    Port port;
    uint32_t value;
    uint32_t scaled;
    port_open(&port, calls, services, globals, entry);
    value = port_forward(&port, entry, 0x4ce080, entry->eax, entry->edx, entry->ebx, entry->ecx);
    port_set32(&port, 0, 0x532bb4, value);
    scaled = (value << 6) / 100;
    port_set32(&port, 0, 0x532b98, scaled);
    value = port_forward(&port, entry, 0x478b40, scaled, (value << 6) % 100, entry->ebx, 100);
    return port_return(&port, value, entry->edx);
}

/* Original 0x4170f0: the matching value of 0x415eb0 for eax over the 0x1c entries at 0x532fec
 * (names at 0x4f8300), kept at 0x532ba4. */
uint32_t vertrix_port_table_value_532ba4_4170f0(PORT_SIGNATURE)
{
    Port port;
    uint32_t value;
    port_open(&port, calls, services, globals, entry);
    value = port_forward(&port, entry, 0x415eb0, entry->eax, 0x532fec, 0x4f8300, 0x1c);
    port_set32(&port, 0, 0x532ba4, value);
    return port_return(&port, value, entry->edx);
}

/* The volume calls: 0x482a60 with the channel (low byte of `lookup`'s result) and the level of
 * slot eax (0x533164) at the volume [0x532b9c] scaled by edx percent. */
static uint32_t channel_volume_scaled(PORT_SIGNATURE, uint32_t lookup)
{
    Port port;
    uint32_t channel;
    uint32_t volume;
    port_open(&port, calls, services, globals, entry);
    channel =
        port_forward(&port, entry, lookup, entry->eax, entry->edx, entry->ebx, entry->eax) & 0xff;
    volume = port_u32(&port, 0, 0x532b9c) * vertrix_lift_edx / 100;
    channel = port_forward_esi(&port, entry, 0x482a60, channel,
                               port_u32(&port, entry->eax * 4, 0x533164), volume, channel, 100);
    return port_return(&port, channel, vertrix_lift_edx);
}

/* Original 0x4171e0: by the channel of 0x4174f0. */
uint32_t vertrix_port_channel_volume_scaled_4171e0(PORT_SIGNATURE)
{
    return channel_volume_scaled(calls, services, globals, entry, 0x4174f0);
}

/* Original 0x417220: by the channel of 0x417550. */
uint32_t vertrix_port_channel_volume_scaled_417220(PORT_SIGNATURE)
{
    return channel_volume_scaled(calls, services, globals, entry, 0x417550);
}

/* The same at the full volume [0x532b9c]. */
static uint32_t channel_volume(PORT_SIGNATURE, uint32_t lookup)
{
    Port port;
    uint32_t channel;
    port_open(&port, calls, services, globals, entry);
    channel = port_forward(&port, entry, lookup, entry->eax, entry->eax, entry->ebx, entry->ecx);
    channel = port_forward(&port, entry, 0x482a60, channel & 0xff,
                           port_u32(&port, vertrix_lift_edx * 4, 0x533164),
                           port_u32(&port, 0, 0x532b9c), entry->ecx);
    return port_return(&port, channel, entry->edx);
}

/* Original 0x417260: by the channel of 0x4174f0. */
uint32_t vertrix_port_channel_volume_417260(PORT_SIGNATURE)
{
    return channel_volume(calls, services, globals, entry, 0x4174f0);
}

/* Original 0x417290: by the channel of 0x417550. */
uint32_t vertrix_port_channel_volume_417290(PORT_SIGNATURE)
{
    return channel_volume(calls, services, globals, entry, 0x417550);
}

/* Original 0x417930: the bytes of row al, column dl of the 28-column tables at 0x4f9320 and
 * 0x4f9538, stored at ebx and ecx; al and dl are left the two bytes. */
uint32_t vertrix_port_table_byte_pair_417930(PORT_SIGNATURE)
{
    Port port;
    uint32_t cell = (entry->eax & 0xff) * 28 + (entry->edx & 0xff);
    uint32_t first;
    uint32_t second;
    port_open(&port, calls, services, globals, entry);
    first = port_u8(&port, cell, 0x4f9320);
    port_set8(&port, entry->ebx, 0, first);
    second = port_u8(&port, cell, 0x4f9538);
    port_set8(&port, entry->ecx, 0, second);
    return port_return(&port, (cell & 0xffffff00u) | second, first);
}

/* The grid values of row eax in the column at `column` of the 22-column grid at 0x533e1c. */
static uint32_t grid_value(PORT_SIGNATURE, uint32_t column)
{
    Port port;
    uint32_t cell;
    port_open(&port, calls, services, globals, entry);
    cell = entry->eax * 22 + port_u32(&port, 0, column);
    return port_return(&port, port_u32(&port, cell * 4, 0x533e1c), entry->edx);
}

/* Original 0x417d10: the column at 0x4f8ce0. */
uint32_t vertrix_port_table_grid_value_417d10(PORT_SIGNATURE)
{
    return grid_value(calls, services, globals, entry, 0x4f8ce0);
}

/* Original 0x417d40: the column at 0x4f8ce4. */
uint32_t vertrix_port_table_grid_value_417d40(PORT_SIGNATURE)
{
    return grid_value(calls, services, globals, entry, 0x4f8ce4);
}

/* Original 0x417d70: the column at 0x4f8ce8. */
uint32_t vertrix_port_table_grid_value_417d70(PORT_SIGNATURE)
{
    return grid_value(calls, services, globals, entry, 0x4f8ce8);
}

/* Original 0x41a010: send the message 0x10 to the window +0x1c (the import 0x4f1a60), then
 * 0x418870 and 0x418840 (edx 0) on the object. */
uint32_t vertrix_port_window_close_41a010(PORT_SIGNATURE)
{
    Port port;
    uint32_t pushed[4];
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    pushed[0] = port_u32(&port, entry->eax, 0x1c);
    pushed[1] = 0x10;
    pushed[2] = 0;
    pushed[3] = 0;
    port_forward_stack(&port, entry, 0x4f1a60, entry->eax, pushed[0], entry->eax, entry->ecx,
                       entry->esi, pushed, 4);
    port_forward(&port, entry, 0x418870, entry->eax, vertrix_lift_edx, entry->eax, entry->ecx);
    result = port_forward(&port, entry, 0x418840, entry->eax, 0, entry->eax, entry->ecx);
    return port_return(&port, result, entry->edx);
}

/* Original 0x41c080: 0x41c020, 0x478ae0 and the window of the record of 0x4ce740 given the
 * handler 0x41a240 (0x419ef0); then flag +0xd8 and 0x418840. */
uint32_t vertrix_port_screen_enter_41c080(PORT_SIGNATURE)
{
    Port port;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    result = port_forward(&port, entry, 0x41c020, entry->eax, entry->edx, entry->eax, entry->ecx);
    result = port_forward(&port, entry, 0x478ae0, result, vertrix_lift_edx, entry->eax, entry->ecx);
    result = port_forward(&port, entry, 0x4ce740, result, vertrix_lift_edx, entry->eax, entry->ecx);
    port_forward(&port, entry, 0x419ef0, port_u32(&port, port_u32(&port, result, 4), 0x1c),
                 0x41a240, entry->eax, entry->ecx);
    port_set32(&port, entry->eax, 0xd8, 1);
    result =
        port_forward(&port, entry, 0x418840, entry->eax, vertrix_lift_edx, entry->eax, entry->ecx);
    return port_return(&port, result, entry->edx);
}

/* Original 0x41c0c0: 0x41c020, then the handlers 0x421f10 (0x418840) and 0x41c390 (0x418820). */
uint32_t vertrix_port_screen_handlers_41c0c0(PORT_SIGNATURE)
{
    Port port;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    port_forward(&port, entry, 0x41c020, entry->eax, entry->edx, entry->ebx, entry->eax);
    port_forward(&port, entry, 0x418840, entry->eax, 0x421f10, entry->ebx, entry->eax);
    result = port_forward(&port, entry, 0x418820, entry->eax, 0x41c390, entry->ebx, entry->eax);
    return port_return(&port, result, entry->edx);
}

/* Original 0x41df00: under the lock 0x5328c0 (imports 0x4f1b48 and 0x4f1c40), 0x478460 on 0x5588f8
 * and 0x473630. */
uint32_t vertrix_port_locked_update_41df00(PORT_SIGNATURE)
{
    Port port;
    uint32_t lock[1] = {0x5328c0};
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    result = port_forward_stack(&port, entry, 0x4f1b48, entry->eax, entry->edx, entry->ebx,
                                entry->ecx, entry->esi, lock, 1);
    result =
        port_forward(&port, entry, 0x478460, 0x5588f8, vertrix_lift_edx, entry->ebx, entry->ecx);
    result = port_forward(&port, entry, 0x473630, result, vertrix_lift_edx, entry->ebx, entry->ecx);
    result = port_forward_stack(&port, entry, 0x4f1c40, result, vertrix_lift_edx, entry->ebx,
                                entry->ecx, entry->esi, lock, 1);
    return port_return(&port, result, entry->edx);
}

/* Original 0x424200: the address 0x419f80. */
uint32_t vertrix_port_constant_424200(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    return port_return(&port, 0x419f80, entry->edx);
}

/* Original 0x424760: centre the title (0x477e30 on 0x5588f8 at 200, 60), then the handler 0x424990
 * (0x418840). */
uint32_t vertrix_port_object_center_titled_424760(PORT_SIGNATURE)
{
    Port port;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    port_forward(&port, entry, 0x477e30, 0x5588f8, 0xc8, 0x3c, entry->eax);
    result = port_forward(&port, entry, 0x418840, entry->eax, 0x424990, 0x3c, entry->eax);
    return port_return(&port, result, entry->edx);
}

/* Original 0x429670: the marker actor: 0x4abd70, class 0x5145a4, bytes +0x94 0, +0x95 3, +0x15c
 * 0xff and the dword +0x160 1. */
uint32_t vertrix_port_marker_actor_construct_429670(PORT_SIGNATURE)
{
    Port port;
    uint32_t actor;
    port_open(&port, calls, services, globals, entry);
    actor = port_forward(&port, entry, 0x4abd70, entry->eax, entry->edx, entry->ebx, entry->ecx);
    port_set32(&port, actor, 0x158, 0x5145a4);
    port_set8(&port, actor, 0x94, 0);
    port_set8(&port, actor, 0x95, 3);
    port_set8(&port, actor, 0x15c, 0xff);
    port_set32(&port, actor, 0x160, 1);
    return port_return(&port, actor, vertrix_lift_edx);
}

/* Original 0x42a510: 0x4b23c0 on the three slots at +0x15c and at +0x170, then 0x42a800. */
uint32_t vertrix_port_piece_slots_42a510(PORT_SIGNATURE)
{
    Port port;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    port_forward(&port, entry, 0x4b23c0, entry->eax + 0x15c, 3, entry->ebx, entry->eax);
    port_forward(&port, entry, 0x4b23c0, entry->eax + 0x170, 3, entry->ebx, entry->eax);
    result =
        port_forward(&port, entry, 0x42a800, entry->eax, vertrix_lift_edx, entry->ebx, entry->eax);
    return port_return(&port, result, entry->edx);
}

/* Original 0x42a8b0: rotate the three dwords from +0x15c down by one. */
uint32_t vertrix_port_piece_rotate_42a8b0(PORT_SIGNATURE)
{
    Port port;
    uint32_t first;
    port_open(&port, calls, services, globals, entry);
    first = port_u32(&port, entry->eax, 0x15c);
    port_set32(&port, entry->eax, 0x15c, port_u32(&port, entry->eax, 0x160));
    port_set32(&port, entry->eax, 0x160, port_u32(&port, entry->eax, 0x164));
    port_set32(&port, entry->eax, 0x164, first);
    return port_return(&port, entry->eax, entry->edx);
}

/* Original 0x42b5c0: the empty piece actor: 0x4abd70, class 0x514894 and +0x170, +0x15c, +0x160 and
 * +0x164 cleared. */
uint32_t vertrix_port_piece_actor_construct_empty_42b5c0(PORT_SIGNATURE)
{
    Port port;
    uint32_t actor;
    port_open(&port, calls, services, globals, entry);
    actor = port_forward(&port, entry, 0x4abd70, entry->eax, entry->edx, entry->ebx, entry->ecx);
    port_set32(&port, actor, 0x158, 0x514894);
    port_set32(&port, actor, 0x170, 0);
    port_set32(&port, actor, 0x15c, 0);
    port_set32(&port, actor, 0x160, 0);
    port_set32(&port, actor, 0x164, 0);
    return port_return(&port, actor, vertrix_lift_edx);
}

/* Original 0x42ba40: whether the signed word +0x16 is above the word +0xae. */
uint32_t vertrix_port_object_y_above_limit_42ba40(PORT_SIGNATURE)
{
    Port port;
    uint32_t above;
    port_open(&port, calls, services, globals, entry);
    above = (int16_t)port_u16(&port, entry->eax, 0x16) > (int16_t)port_u16(&port, entry->eax, 0xae);
    return port_return(&port, above, entry->edx);
}

/* Original 0x42ff10: clip the actor at edx to the board: x from the board's x (+0xc) for 0x77,
 * y from its y (+0x14) for 0x137, with the clip mode 3; eax is left the y. */
uint32_t vertrix_port_board_set_actor_clip_42ff10(PORT_SIGNATURE)
{
    Port port;
    uint32_t x;
    uint32_t y;
    port_open(&port, calls, services, globals, entry);
    x = (uint32_t)((int32_t)port_u32(&port, entry->eax, 0xc) >> 16);
    y = (uint32_t)((int32_t)port_u32(&port, entry->eax, 0x14) >> 16);
    port_set8(&port, entry->edx, 0x8e, 3);
    port_set16(&port, entry->edx, 0xa8, x);
    port_set16(&port, entry->edx, 0xaa, x + 0x77);
    port_set16(&port, entry->edx, 0xac, y);
    port_set16(&port, entry->edx, 0xae, y + 0x137);
    return port_return(&port, y, entry->edx);
}

/* Original 0x431ae0: the cell (24 pixels) of the point (dx, bx) in the board: the column at ecx,
 * the row at the stack argument and in eax; edx is left the argument. */
uint32_t vertrix_port_board_cell_of_point_431ae0(PORT_SIGNATURE)
{
    Port port;
    uint8_t stack[8 + 4];
    uint32_t row_at;
    int32_t column;
    int32_t row;
    port_open_arguments(&port, stack, calls, services, globals, entry, 0, 1);
    row_at = port_u32(&port, entry->esp, 4);
    column = (int16_t)entry->edx - ((int32_t)port_u32(&port, entry->eax, 0xc) >> 16);
    port_set32(&port, entry->ecx, 0, (uint32_t)(column / 24));
    row = (int16_t)entry->ebx - ((int32_t)port_u32(&port, entry->eax, 0x14) >> 16);
    port_set32(&port, row_at, 0, (uint32_t)(row / 24));
    return port_return(&port, (uint32_t)(row / 24), row_at);
}

/* Original 0x432010: whether the piece (+0xa60) is below 0x48 above the board's top. */
uint32_t vertrix_port_board_piece_below_top_432010(PORT_SIGNATURE)
{
    Port port;
    int32_t top;
    int32_t piece;
    port_open(&port, calls, services, globals, entry);
    top = ((int32_t)port_u32(&port, entry->eax, 0x14) >> 16) - 0x48;
    piece = (int32_t)port_u32(&port, port_u32(&port, entry->eax, 0xa60), 0x14) >> 16;
    return port_return(&port, piece > top, entry->edx);
}

/* Original 0x43a080: the kind-one block: 0x4abd70, class 0x514b14, bytes +0x15c 1, +0x15d 0, +0x94
 * 0 and +0x95 3. */
uint32_t vertrix_port_block_construct_kind_one_43a080(PORT_SIGNATURE)
{
    Port port;
    uint32_t block;
    port_open(&port, calls, services, globals, entry);
    block = port_forward(&port, entry, 0x4abd70, entry->eax, entry->edx, entry->ebx, entry->ecx);
    port_set32(&port, block, 0x158, 0x514b14);
    port_set8(&port, block, 0x15c, 1);
    port_set8(&port, block, 0x15d, 0);
    port_set8(&port, block, 0x94, 0);
    port_set8(&port, block, 0x95, 3);
    return port_return(&port, block, vertrix_lift_edx);
}

/* Original 0x43a5b0: the kinds (byte +0x15c) of the three pieces +0x15c, +0x160 and +0x164 into the
 * bytes at edx, ebx and ecx; al and dl are left the third and second. */
uint32_t vertrix_port_piece_kinds_43a5b0(PORT_SIGNATURE)
{
    Port port;
    uint32_t second;
    uint32_t third;
    port_open(&port, calls, services, globals, entry);
    port_set8(&port, entry->edx, 0, port_u8(&port, port_u32(&port, entry->eax, 0x15c), 0x15c));
    second = port_u32(&port, entry->eax, 0x160);
    second = (second & 0xffffff00u) | port_u8(&port, second, 0x15c);
    port_set8(&port, entry->ebx, 0, second);
    third = port_u32(&port, entry->eax, 0x164);
    third = (third & 0xffffff00u) | port_u8(&port, third, 0x15c);
    port_set8(&port, entry->ecx, 0, third);
    return port_return(&port, third, second);
}

/* Original 0x43ab30: set up the piece (+0x450) for the character byte +0x488 (0x425ef0), then the
 * delays (0x43b590). */
uint32_t vertrix_port_player_init_piece_and_delays_43ab30(PORT_SIGNATURE)
{
    Port port;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    port_forward(&port, entry, 0x425ef0, port_u32(&port, entry->eax, 0x450),
                 port_u8(&port, entry->eax, 0x488), entry->ebx, entry->eax);
    result =
        port_forward(&port, entry, 0x43b590, entry->eax, vertrix_lift_edx, entry->ebx, entry->eax);
    return port_return(&port, result, entry->edx);
}

/* Original 0x43bd00: put the player and its partner (+0x3b0) in state 4, entering the handlers
 * 0x4523d0 and 0x4523b0 (0x4ac8f0), the partner after 0x43bb60. */
uint32_t vertrix_port_player_enter_4523d0_43bd00(PORT_SIGNATURE)
{
    Port port;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    port_set8(&port, entry->eax, 0x4cc, 4);
    port_forward(&port, entry, 0x4ac8f0, entry->eax, 0x4523d0, entry->ebx, entry->eax);
    port_forward(&port, entry, 0x43bb60, port_u32(&port, entry->eax, 0x3b0), vertrix_lift_edx,
                 entry->ebx, entry->eax);
    port_set8(&port, port_u32(&port, entry->eax, 0x3b0), 0x4cc, 4);
    result = port_forward(&port, entry, 0x4ac8f0, port_u32(&port, entry->eax, 0x3b0), 0x4523b0,
                          entry->ebx, entry->eax);
    return port_return(&port, result, entry->edx);
}

/* Original 0x43ccf0: adopt the side edx: 0x43b980, keep it at +0x4e4, the mode 0x25 plus it
 * (0x43bb40), 0x43cde0, 0x43ba80, +0x3f4 cleared and 0x4726d0; 1. */
uint32_t vertrix_port_player_adopt_side_43ccf0(PORT_SIGNATURE)
{
    Port port;
    uint32_t side;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    port_forward(&port, entry, 0x43b980, entry->eax, entry->edx, entry->ebx, entry->eax);
    side = vertrix_lift_edx;
    port_set32(&port, entry->eax, 0x4e4, side);
    port_forward(&port, entry, 0x43bb40, entry->eax, side + 0x25, entry->ebx, entry->eax);
    port_forward(&port, entry, 0x43cde0, entry->eax, vertrix_lift_edx, entry->ebx, entry->eax);
    result =
        port_forward(&port, entry, 0x43ba80, entry->eax, vertrix_lift_edx, entry->ebx, entry->eax);
    port_set32(&port, entry->eax, 0x3f4, 0);
    port_forward(&port, entry, 0x4726d0, result, vertrix_lift_edx, entry->ebx, entry->eax);
    return port_return(&port, 1, vertrix_lift_edx);
}

/* The side setups: the delay of the side ([0x532bbc]) from a table (0x43b930), the mode (0x43bb40)
 * and state 0x43cde0 in the given order, then 0x43d260 or a final store when asked; 1. */
enum
{
    MODE_FIRST = 1,
    STATE_FIRST = 2,
    THEN_43D260 = 4,
    SET_470_4 = 8,
    SET_470_1 = 0x10,
    SET_4DC_3 = 0x20
};

static uint32_t side_setup(PORT_SIGNATURE, uint32_t table, uint32_t mode, unsigned steps)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    port_forward(&port, entry, 0x43b930, entry->eax,
                 port_u32(&port, port_u32(&port, 0, SIDE) * 4, table), entry->ebx, entry->eax);
    if (steps & MODE_FIRST)
    {
        port_forward(&port, entry, 0x43bb40, entry->eax, mode, entry->ebx, entry->eax);
        port_forward(&port, entry, 0x43cde0, entry->eax, vertrix_lift_edx, entry->ebx, entry->eax);
    }
    else
    {
        port_forward(&port, entry, 0x43cde0, entry->eax, mode, entry->ebx, entry->eax);
        port_forward(&port, entry, 0x43bb40, entry->eax, vertrix_lift_edx, entry->ebx, entry->eax);
    }
    if (steps & THEN_43D260)
    {
        port_forward(&port, entry, 0x43d260, entry->eax, vertrix_lift_edx, entry->ebx, entry->eax);
    }
    if (steps & (SET_470_4 | SET_470_1))
    {
        port_set32(&port, entry->eax, 0x470, steps & SET_470_4 ? 4 : 1);
    }
    if (steps & SET_4DC_3)
    {
        port_set8(&port, entry->eax, 0x4dc, 3);
    }
    return port_return(&port, 1, entry->edx);
}

/* Original 0x43cd60: mode 0x2b. */
uint32_t vertrix_port_player_setup_side_2b_43cd60(PORT_SIGNATURE)
{
    return side_setup(calls, services, globals, entry, SIDE_TABLE, 0x2b, MODE_FIRST);
}

/* Original 0x43cda0: mode 0x2c. */
uint32_t vertrix_port_player_setup_side_2c_43cda0(PORT_SIGNATURE)
{
    return side_setup(calls, services, globals, entry, SIDE_TABLE, 0x2c, MODE_FIRST);
}

/* Original 0x43cef0: state first with 0x31. */
uint32_t vertrix_port_player_setup_side_31_43cef0(PORT_SIGNATURE)
{
    return side_setup(calls, services, globals, entry, SIDE_TABLE, 0x31, STATE_FIRST);
}

/* Original 0x43cf30: mode 0x23, then 0x43d260. */
uint32_t vertrix_port_player_setup_side_23_43cf30(PORT_SIGNATURE)
{
    return side_setup(calls, services, globals, entry, SIDE_TABLE, 0x23, MODE_FIRST | THEN_43D260);
}

/* Original 0x43cf70: mode 0x22, then 0x43d260. */
uint32_t vertrix_port_player_setup_side_22_43cf70(PORT_SIGNATURE)
{
    return side_setup(calls, services, globals, entry, SIDE_TABLE, 0x22, MODE_FIRST | THEN_43D260);
}

/* Original 0x43cff0: mode 0x28, then 0x43d260. */
uint32_t vertrix_port_player_setup_side_28_43cff0(PORT_SIGNATURE)
{
    return side_setup(calls, services, globals, entry, SIDE_TABLE, 0x28, MODE_FIRST | THEN_43D260);
}

/* Original 0x43d030: mode 0x29 with the delays at 0x4f9c20, then 0x43d260. */
uint32_t vertrix_port_player_setup_side_29_43d030(PORT_SIGNATURE)
{
    return side_setup(calls, services, globals, entry, 0x4f9c20, 0x29, MODE_FIRST | THEN_43D260);
}

/* Original 0x43d070: mode 0x2a with the delays at 0x4f9c2c, then 0x43d260. */
uint32_t vertrix_port_player_setup_side_2a_43d070(PORT_SIGNATURE)
{
    return side_setup(calls, services, globals, entry, 0x4f9c2c, 0x2a, MODE_FIRST | THEN_43D260);
}

/* Original 0x43d0b0: mode 0x2d, then 0x43d260. */
uint32_t vertrix_port_player_setup_side_2d_43d0b0(PORT_SIGNATURE)
{
    return side_setup(calls, services, globals, entry, SIDE_TABLE, 0x2d, MODE_FIRST | THEN_43D260);
}

/* Original 0x43d0f0: mode 0x2e, then 0x43d260. */
uint32_t vertrix_port_player_setup_side_2e_43d0f0(PORT_SIGNATURE)
{
    return side_setup(calls, services, globals, entry, SIDE_TABLE, 0x2e, MODE_FIRST | THEN_43D260);
}

/* Original 0x43ce30: state first with 0x30, then +0x470 set to 4. */
uint32_t vertrix_port_player_setup_side_30_43ce30(PORT_SIGNATURE)
{
    return side_setup(calls, services, globals, entry, SIDE_TABLE, 0x30, STATE_FIRST | SET_470_4);
}

/* Original 0x43ceb0: state first with 0x2f, then +0x470 set to 1. */
uint32_t vertrix_port_player_setup_side_2f_43ceb0(PORT_SIGNATURE)
{
    return side_setup(calls, services, globals, entry, SIDE_TABLE, 0x2f, STATE_FIRST | SET_470_1);
}

/* Original 0x43cfb0: mode 0x24, then the byte +0x4dc set to 3. */
uint32_t vertrix_port_player_setup_side_24_43cfb0(PORT_SIGNATURE)
{
    return side_setup(calls, services, globals, entry, SIDE_TABLE, 0x24, MODE_FIRST | SET_4DC_3);
}

/* Original 0x43ce00: 0x43b980, mode 0 (0x43bb40), 0x43cde0 and 0x43d260; 1. */
uint32_t vertrix_port_player_reset_side_43ce00(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    port_forward(&port, entry, 0x43b980, entry->eax, entry->edx, entry->ebx, entry->eax);
    port_forward(&port, entry, 0x43bb40, entry->eax, 0, entry->ebx, entry->eax);
    port_forward(&port, entry, 0x43cde0, entry->eax, vertrix_lift_edx, entry->ebx, entry->eax);
    port_forward(&port, entry, 0x43d260, entry->eax, vertrix_lift_edx, entry->ebx, entry->eax);
    return port_return(&port, 1, entry->edx);
}

/* Original 0x43ce70: the delay of the player's index +0x3fc (table 0x4f9c38, 0x43b930), 0x43cde0
 * and the mode 0x32 plus the index (0x43bb40); 1. */
uint32_t vertrix_port_player_setup_indexed_43ce70(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    port_forward(&port, entry, 0x43b930, entry->eax,
                 port_u32(&port, port_u32(&port, entry->eax, 0x3fc) * 4, 0x4f9c38), entry->ebx,
                 entry->eax);
    port_forward(&port, entry, 0x43cde0, entry->eax, vertrix_lift_edx, entry->ebx, entry->eax);
    port_forward(&port, entry, 0x43bb40, entry->eax, port_u32(&port, entry->eax, 0x3fc) + 0x32,
                 entry->ebx, entry->eax);
    return port_return(&port, 1, entry->edx);
}

/* Original 0x43e260: release the 0x1c2 slots at +0x15c, the three at +0x864 and the one at +0x870
 * (0x4b22c0). */
uint32_t vertrix_port_arena_release_all_43e260(PORT_SIGNATURE)
{
    Port port;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    port_forward(&port, entry, 0x4b22c0, entry->eax + 0x15c, 0x1c2, entry->ebx, entry->eax);
    port_forward(&port, entry, 0x4b22c0, entry->eax + 0x864, 3, entry->ebx, entry->eax);
    result = port_forward(&port, entry, 0x4b22c0, entry->eax + 0x870, 1, entry->ebx, entry->eax);
    return port_return(&port, result, entry->edx);
}

/* Original 0x448690: 0x417690 on the object +0x15c of the object +0x160. */
uint32_t vertrix_port_call_417690_448690(PORT_SIGNATURE)
{
    Port port;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    result = port_forward(&port, entry, 0x417690,
                          port_u32(&port, port_u32(&port, entry->eax, 0x160), 0x15c), entry->edx,
                          entry->ebx, entry->ecx);
    return port_return(&port, result, vertrix_lift_edx);
}

/* The number players: the number of the item (0x4b5eb0 over 0x54671c by +4) at +0x180 shown
 * (0x4b58a0). */
static uint32_t number_player_update(PORT_SIGNATURE)
{
    Port port;
    uint32_t item;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    item = port_forward(&port, entry, 0x4b5eb0, 0x54671c, port_u32(&port, entry->eax, 4),
                        entry->ebx, entry->eax);
    result = port_forward(&port, entry, 0x4b58a0, entry->eax, port_u32(&port, item, 0x180),
                          entry->ebx, entry->eax);
    return port_return(&port, result, entry->edx);
}

/* Original 0x44fa70. */
uint32_t vertrix_port_number_player_update_44fa70(PORT_SIGNATURE)
{
    return number_player_update(calls, services, globals, entry);
}

/* Original 0x44fc00. */
uint32_t vertrix_port_number_player_update_44fc00(PORT_SIGNATURE)
{
    return number_player_update(calls, services, globals, entry);
}

/* The number players of an object (+4 of the table 0x540f88): the dword `field` shown (0x4b58a0),
 * 0x4adfe0, then no handler (0x4ac8f0). */
static uint32_t number_player_field(PORT_SIGNATURE, uint32_t field)
{
    Port port;
    uint32_t object;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    object = port_u32(&port, port_u32(&port, entry->eax, 4) * 4, 0x540f88);
    port_forward(&port, entry, 0x4b58a0, entry->eax, port_u32(&port, object, field), entry->ebx,
                 entry->eax);
    port_forward(&port, entry, 0x4adfe0, entry->eax, vertrix_lift_edx, entry->ebx, entry->eax);
    result = port_forward(&port, entry, 0x4ac8f0, entry->eax, 0, entry->ebx, entry->eax);
    return port_return(&port, result, entry->edx);
}

/* Original 0x44faa0: the field +0x17c. */
uint32_t vertrix_port_number_player_field_44faa0(PORT_SIGNATURE)
{
    return number_player_field(calls, services, globals, entry, 0x17c);
}

/* Original 0x44fc30: the field +0x178. */
uint32_t vertrix_port_number_player_field_44fc30(PORT_SIGNATURE)
{
    return number_player_field(calls, services, globals, entry, 0x178);
}

/* Original 0x451a60: start the bonus: 0x4320d0 on the board +0x15c with the signed top byte of
 * +0x190 and +0x17c, the handler 0x451aa0 (0x4ac8f0) and 0x43ad50. */
uint32_t vertrix_port_player_start_bonus_451a60(PORT_SIGNATURE)
{
    Port port;
    uint32_t count;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    count = port_u32(&port, entry->eax, 0x17c);
    port_forward(&port, entry, 0x4320d0, port_u32(&port, entry->eax, 0x15c),
                 (uint32_t)((int32_t)port_u32(&port, entry->eax, 0x18d) >> 24), count, entry->eax);
    port_forward(&port, entry, 0x4ac8f0, entry->eax, 0x451aa0, count, entry->eax);
    result = port_forward(&port, entry, 0x43ad50, entry->eax, vertrix_lift_edx, count, entry->eax);
    return port_return(&port, result, entry->edx);
}

/* Original 0x4568c0: copy the words +8 and +0xa to +0x10 and +0x18, then the handler 0x456900
 * (0x4ac8f0), 0x4ac7b0 with 1 and 0x4ac510. */
uint32_t vertrix_port_actor_restart_4568c0(PORT_SIGNATURE)
{
    Port port;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    port_set16(&port, entry->eax, 0x10, port_u16(&port, entry->eax, 8));
    port_set16(&port, entry->eax, 0x18, port_u16(&port, entry->eax, 0xa));
    port_forward(&port, entry, 0x4ac8f0, entry->eax, 0x456900, entry->ebx, entry->eax);
    port_forward(&port, entry, 0x4ac7b0, entry->eax, 1, entry->ebx, entry->eax);
    result =
        port_forward(&port, entry, 0x4ac510, entry->eax, vertrix_lift_edx, entry->ebx, entry->eax);
    return port_return(&port, result, entry->edx);
}

/* Original 0x458410: the actor's bytes +0x95 3, +0x93 1, +0x94 1, +0x4e 100, +0x4f 0 and the word
 * +0x50 2, the period 10 (0x4ac7d0) and the handler 0x458450 (0x4ac8f0). */
uint32_t vertrix_port_actor_setup_458410(PORT_SIGNATURE)
{
    Port port;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    port_set8(&port, entry->eax, 0x95, 3);
    port_set8(&port, entry->eax, 0x93, 1);
    port_set8(&port, entry->eax, 0x94, 1);
    port_set8(&port, entry->eax, 0x4e, 0x64);
    port_set8(&port, entry->eax, 0x4f, 0);
    port_set16(&port, entry->eax, 0x50, 2);
    port_forward(&port, entry, 0x4ac7d0, entry->eax, 0xa, entry->ebx, entry->eax);
    result = port_forward(&port, entry, 0x4ac8f0, entry->eax, 0x458450, entry->ebx, entry->eax);
    return port_return(&port, result, entry->edx);
}

/* Original 0x45aa70: the head's idle wait: the period 2000 plus a draw below 10000 (0x4826c0 over
 * 0x598d30, 0x4ac7d0), the next handler 0x45aab0 (0x4ac510) and 0x4ac8f0. */
uint32_t vertrix_port_head_idle_wait_45aa70(PORT_SIGNATURE)
{
    Port port;
    uint32_t draw;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    draw = port_forward(&port, entry, 0x4826c0, RANDOM, 0x2710, entry->ebx, entry->eax);
    port_forward(&port, entry, 0x4ac7d0, entry->eax, (draw & 0xffff) + 0x7d0, entry->ebx,
                 entry->eax);
    port_forward(&port, entry, 0x4ac510, entry->eax, 0x45aab0, entry->ebx, entry->eax);
    result =
        port_forward(&port, entry, 0x4ac8f0, entry->eax, vertrix_lift_edx, entry->ebx, entry->eax);
    return port_return(&port, result, entry->edx);
}

/* Original 0x45ecd0: the resource entry of eax in the table 0x544a6c (0x4877f0, 4 per entry), its
 * first dword handed to 0x47cd60 with edx, and the entry added to 0x5b9c60 (0x483ed0). */
uint32_t vertrix_port_resource_pair_call_45ecd0(PORT_SIGNATURE)
{
    Port port;
    uint32_t record;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    record =
        port_forward_esi(&port, entry, 0x4877f0, 0x544a6c, entry->eax, 4, entry->ecx, entry->edx);
    port_forward_esi(&port, entry, 0x47cd60, entry->edx, port_u32(&port, record, 0), 4, record,
                     entry->edx);
    result = port_forward_esi(&port, entry, 0x483ed0, record, 0x5b9c60, 4, record, entry->edx);
    return port_return(&port, result, vertrix_lift_edx);
}

/* Original 0x4710d0: place the UI actor (0x4adf20) at the signed (dx, bx) with the class 0x5449fc,
 * ecx and three zeros pushed, then its bytes +0x8e 0 and +0x8f 1. */
uint32_t vertrix_port_ui_actor_place_4710d0(PORT_SIGNATURE)
{
    Port port;
    uint32_t pushed[5];
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    pushed[0] = 0x5449fc;
    pushed[1] = entry->ecx;
    pushed[2] = 0;
    pushed[3] = 0;
    pushed[4] = 0;
    result = port_forward_stack(&port, entry, 0x4adf20, entry->eax, (uint32_t)(int16_t)entry->edx,
                                (uint32_t)(int16_t)entry->ebx, 0, entry->eax, pushed, 5);
    port_set8(&port, entry->eax, 0x8e, 0);
    port_set8(&port, entry->eax, 0x8f, 1);
    return port_return(&port, result, vertrix_lift_edx);
}

/* Original 0x4717f0: slide in from below: steps 8 (+0x12, +0x1a), the start x (+0xe) at +0x10, the
 * y +0x16 kept at +0x18 and moved 0x140 down. */
uint32_t vertrix_port_ui_slide_from_below_4717f0(PORT_SIGNATURE)
{
    Port port;
    uint32_t y;
    port_open(&port, calls, services, globals, entry);
    port_set16(&port, entry->eax, 0x12, 8);
    port_set16(&port, entry->eax, 0x1a, 8);
    port_set16(&port, entry->eax, 0x10, port_u16(&port, entry->eax, 0xe));
    y = port_u16(&port, entry->eax, 0x16);
    port_set16(&port, entry->eax, 0x18, y);
    port_set16(&port, entry->eax, 0x16, y + 0x140);
    return port_return(&port, entry->eax, entry->edx);
}

/* Original 0x4719a0: slide in from above: steps 8 and 4, the start x at +0x10, the y kept at +0x18
 * and moved 0x70 up, and the position copied to +8 and +0xa. */
uint32_t vertrix_port_ui_slide_from_above_4719a0(PORT_SIGNATURE)
{
    Port port;
    uint32_t y;
    port_open(&port, calls, services, globals, entry);
    port_set16(&port, entry->eax, 0x12, 8);
    port_set16(&port, entry->eax, 0x1a, 4);
    port_set16(&port, entry->eax, 0x10, port_u16(&port, entry->eax, 0xe));
    y = port_u16(&port, entry->eax, 0x16);
    port_set16(&port, entry->eax, 0x18, y);
    port_set16(&port, entry->eax, 0x16, y - 0x70);
    port_set16(&port, entry->eax, 8, port_u16(&port, entry->eax, 0xe));
    port_set16(&port, entry->eax, 0xa, port_u16(&port, entry->eax, 0x16));
    return port_return(&port, entry->eax, entry->edx);
}

/* The progress records (96 bytes each) by the word dx: `target` with ebx in edx. */
static uint32_t progress_record_call(PORT_SIGNATURE, uint32_t target)
{
    Port port;
    uint32_t index = entry->edx & 0xffff;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    result = port_forward_esi(&port, entry, target, entry->eax + index * 96, entry->ebx, entry->ebx,
                              index, entry->eax);
    return port_return(&port, result, vertrix_lift_edx);
}

/* Original 0x4764d0: 0x475dd0 (set +0x40). */
uint32_t vertrix_port_progress_record_set_40_4764d0(PORT_SIGNATURE)
{
    return progress_record_call(calls, services, globals, entry, 0x475dd0);
}

/* Original 0x476500: 0x475e40 (set +0x3c). */
uint32_t vertrix_port_progress_record_set_3c_476500(PORT_SIGNATURE)
{
    return progress_record_call(calls, services, globals, entry, 0x475e40);
}

/* The sound cue offsets: `target` on the cues 0x54d640 with the word edx plus the word +0xc8 (in
 * si), the dwords +0x14 and +0x18 in ebx and ecx and 0 pushed. */
static uint32_t sound_cue_offset(PORT_SIGNATURE, uint32_t target)
{
    Port port;
    uint32_t pushed[1] = {0};
    uint32_t esi;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    esi = (entry->esi & 0xffff0000u) | port_u16(&port, entry->eax, 0xc8);
    result = port_forward_stack(&port, entry, target, SOUND_CUES, (entry->edx + esi) & 0xffff,
                                port_u32(&port, entry->eax, 0x14),
                                port_u32(&port, entry->eax, 0x18), esi, pushed, 1);
    return port_return(&port, result, vertrix_lift_edx);
}

/* Original 0x476fb0: by 0x4761d0. */
uint32_t vertrix_port_sound_cue_offset_476fb0(PORT_SIGNATURE)
{
    return sound_cue_offset(calls, services, globals, entry, 0x4761d0);
}

/* Original 0x476fe0: by 0x476280. */
uint32_t vertrix_port_sound_cue_offset_476fe0(PORT_SIGNATURE)
{
    return sound_cue_offset(calls, services, globals, entry, 0x476280);
}

/* The sound cue keys: `target` on the cues with the key word at `key`. */
static uint32_t sound_cue_key(PORT_SIGNATURE, uint32_t key, uint32_t target)
{
    Port port;
    uint32_t pushed[1] = {0};
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    result = port_forward_stack(&port, entry, target, SOUND_CUES, port_u16(&port, entry->eax, key),
                                port_u32(&port, entry->eax, 0x14),
                                port_u32(&port, entry->eax, 0x18), entry->esi, pushed, 1);
    return port_return(&port, result, entry->edx);
}

/* Original 0x477010: key +0xb8 by 0x4761d0. */
uint32_t vertrix_port_sound_cue_key_477010(PORT_SIGNATURE)
{
    return sound_cue_key(calls, services, globals, entry, 0xb8, 0x4761d0);
}

/* Original 0x477040: key +0xb8 by 0x476280. */
uint32_t vertrix_port_sound_cue_key_477040(PORT_SIGNATURE)
{
    return sound_cue_key(calls, services, globals, entry, 0xb8, 0x476280);
}

/* Original 0x477070: key +0xbc by 0x4761d0. */
uint32_t vertrix_port_sound_cue_key_477070(PORT_SIGNATURE)
{
    return sound_cue_key(calls, services, globals, entry, 0xbc, 0x4761d0);
}

/* Original 0x4770a0: key +0xbc by 0x476280. */
uint32_t vertrix_port_sound_cue_key_4770a0(PORT_SIGNATURE)
{
    return sound_cue_key(calls, services, globals, entry, 0xbc, 0x476280);
}

/* Original 0x4770d0: key +0xc0 by 0x4761d0. */
uint32_t vertrix_port_sound_cue_key_4770d0(PORT_SIGNATURE)
{
    return sound_cue_key(calls, services, globals, entry, 0xc0, 0x4761d0);
}

/* Original 0x477100: key +0xc0 by 0x476280. */
uint32_t vertrix_port_sound_cue_key_477100(PORT_SIGNATURE)
{
    return sound_cue_key(calls, services, globals, entry, 0xc0, 0x476280);
}

/* Original 0x477130: key +0xc4 by 0x4761d0. */
uint32_t vertrix_port_sound_cue_key_477130(PORT_SIGNATURE)
{
    return sound_cue_key(calls, services, globals, entry, 0xc4, 0x4761d0);
}

/* Original 0x477160: key +0xc4 by 0x476280. */
uint32_t vertrix_port_sound_cue_key_477160(PORT_SIGNATURE)
{
    return sound_cue_key(calls, services, globals, entry, 0xc4, 0x476280);
}

/* Original 0x47f2f0: 0x47f280 under the lock 0x558c9c (imports 0x4f1b48 and 0x4f1c40). */
uint32_t vertrix_port_locked_47f280_47f2f0(PORT_SIGNATURE)
{
    Port port;
    uint32_t lock[1] = {0x558c9c};
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    port_forward_stack(&port, entry, 0x4f1b48, entry->eax, entry->edx, entry->eax, entry->ecx,
                       entry->edx, lock, 1);
    result = port_forward_esi(&port, entry, 0x47f280, entry->eax, entry->edx, entry->eax,
                              entry->ecx, entry->edx);
    port_forward_stack(&port, entry, 0x4f1c40, result, vertrix_lift_edx, result, entry->ecx,
                       entry->edx, lock, 1);
    return port_return(&port, result, vertrix_lift_edx);
}

/* Original 0x4856d0: release the two surfaces at [0x558c80] and [0x558c88] (0x478d80) and clear
 * both; 1. */
uint32_t vertrix_port_surfaces_release_4856d0(PORT_SIGNATURE)
{
    Port port;
    uint32_t cleared;
    port_open(&port, calls, services, globals, entry);
    port_forward(&port, entry, 0x478d80, port_u32(&port, 0, 0x558c80), entry->edx, entry->ebx,
                 entry->ecx);
    port_forward(&port, entry, 0x478d80, port_u32(&port, 0, 0x558c88), 0, entry->ebx, entry->ecx);
    cleared = vertrix_lift_edx;
    port_set32(&port, 0, 0x558c80, cleared);
    port_set32(&port, 0, 0x558c88, cleared);
    return port_return(&port, 1, entry->edx);
}

/* The randomised periods: `call` with the base +`base` plus a draw below the word +`spread`. */
static uint32_t randomize(PORT_SIGNATURE, uint32_t spread, uint32_t base, uint32_t call)
{
    Port port;
    uint32_t draw;
    uint32_t start;
    port_open(&port, calls, services, globals, entry);
    draw = port_forward(&port, entry, 0x4826c0, RANDOM, port_u16(&port, entry->eax, spread),
                        entry->ebx, entry->eax);
    start = port_u32(&port, entry->eax, base);
    draw = port_forward(&port, entry, call, entry->eax, (draw & 0xffff) + start, start, entry->eax);
    return port_return(&port, draw, entry->edx);
}

/* Original 0x4ac7e0: the period (0x4ac7d0) from +0xc4 and +0xc8. */
uint32_t vertrix_port_actor_randomize_period_4ac7e0(PORT_SIGNATURE)
{
    return randomize(calls, services, globals, entry, 0xc8, 0xc4, 0x4ac7d0);
}

/* Original 0x4ac810: the delay (0x4ac490) from +0xd4 and +0xd8. */
uint32_t vertrix_port_actor_randomize_d0_4ac810(PORT_SIGNATURE)
{
    return randomize(calls, services, globals, entry, 0xd8, 0xd4, 0x4ac490);
}

/* Original 0x4b29d0: tail call of 0x4b2a00. */
uint32_t vertrix_port_forward_4b2a00_4b29d0(PORT_SIGNATURE)
{
    Port port;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    result = port_forward(&port, entry, 0x4b2a00, entry->eax, entry->edx, entry->ebx, entry->ecx);
    return port_return(&port, result, vertrix_lift_edx);
}

/* Original 0x4b34d0: 0x4b3100 with the class 0x517cf4 and +0x170 to +0x178 cleared. */
uint32_t vertrix_port_construct_517cf4_4b34d0(PORT_SIGNATURE)
{
    Port port;
    uint32_t object;
    port_open(&port, calls, services, globals, entry);
    object = port_forward(&port, entry, 0x4b3100, entry->eax, entry->edx, entry->ebx, entry->ecx);
    port_set32(&port, object, 0x158, 0x517cf4);
    port_set32(&port, object, 0x170, 0);
    port_set32(&port, object, 0x174, 0);
    port_set32(&port, object, 0x178, 0);
    return port_return(&port, object, vertrix_lift_edx);
}

/* The length of the parent's text (+0x15c of the parent +0x160) less 1, as repne scasb leaves it;
 * `end` is set past its terminator. */
static uint32_t text_last(Port *port, uint32_t object, uint32_t *end)
{
    uint32_t text = port_u32(port, port_u32(port, object, 0x160), 0x15c);
    uint32_t length = 0;
    while (port_u8(port, text, length) != 0)
    {
        length++;
    }
    *end = text + length + 1;
    return length - 1;
}

/* Original 0x4b4630: put the cursor (+0x170) on the text's last character, then 0x4b4690. */
uint32_t vertrix_port_object_text_length_reset_4b4630(PORT_SIGNATURE)
{
    Port port;
    uint32_t end;
    uint32_t last;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    last = text_last(&port, entry->eax, &end);
    port_set32(&port, entry->eax, 0x170, last);
    result = port_call_with(&port, 0x4b4690, entry->eax, entry->eax, entry->ebx, last, entry->esi,
                            end, entry->ebp);
    return port_return(&port, result, entry->edx);
}

/* Original 0x4b4660: whether the cursor (+0x170) is on the text's last character. */
uint32_t vertrix_port_object_cursor_at_end_4b4660(PORT_SIGNATURE)
{
    Port port;
    uint32_t end;
    uint32_t last;
    port_open(&port, calls, services, globals, entry);
    last = text_last(&port, entry->eax, &end);
    return port_return(&port, last == port_u32(&port, entry->eax, 0x170), entry->edx);
}

/* Original 0x4b5a20: method +8 of the object +0x18c (class +0x158), then 0x4b6800 with edx. */
uint32_t vertrix_port_object_method_then_4b6800_4b5a20(PORT_SIGNATURE)
{
    Port port;
    uint32_t object;
    uint32_t class_address;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    object = port_u32(&port, entry->eax, 0x18c);
    class_address = port_u32(&port, object, 0x158);
    port_forward_esi(&port, entry, port_u32(&port, class_address, 8), object, entry->edx,
                     entry->eax, entry->edx, class_address);
    result = port_forward_esi(&port, entry, 0x4b6800, entry->eax, entry->edx, entry->eax,
                              entry->edx, class_address);
    return port_return(&port, result, vertrix_lift_edx);
}

/* Original 0x4b6690: the four words +0x16a to +0x170 from dx, bx, cx and the stack argument. */
uint32_t vertrix_port_object_set_four_words_4b6690(PORT_SIGNATURE)
{
    Port port;
    uint8_t stack[8 + 4];
    uint32_t fourth;
    port_open_arguments(&port, stack, calls, services, globals, entry, 0, 1);
    fourth = port_u32(&port, entry->esp, 4);
    port_set16(&port, entry->eax, 0x16a, entry->edx);
    port_set16(&port, entry->eax, 0x16c, entry->ebx);
    port_set16(&port, entry->eax, 0x16e, entry->ecx);
    port_set16(&port, entry->eax, 0x170, fourth);
    return port_return(&port, entry->eax, fourth);
}

/* Original 0x4b7c90: 0x484500 on 0x5bd82c, the import 0x4f1724 on [0x5bd848], clear 0x5bd83c and
 * close [0x5bd840] (0x4f1b2c). */
uint32_t vertrix_port_device_close_4b7c90(PORT_SIGNATURE)
{
    Port port;
    uint32_t pushed[1];
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    result = port_forward(&port, entry, 0x484500, 0x5bd82c, entry->edx, entry->ebx, entry->ecx);
    pushed[0] = port_u32(&port, 0, 0x5bd848);
    result = port_forward_stack(&port, entry, 0x4f1724, result, pushed[0], entry->ebx, entry->ecx,
                                entry->esi, pushed, 1);
    pushed[0] = port_u32(&port, 0, 0x5bd840);
    port_set32(&port, 0, 0x5bd83c, 0);
    result = port_forward_stack(&port, entry, 0x4f1b2c, result, vertrix_lift_edx, pushed[0], 0,
                                entry->esi, pushed, 1);
    return port_return(&port, result, entry->edx);
}

/* Original 0x4c4cc0: the byte of the 0x400-entry table at +0x80 of the object +0x144 for the
 * value [[edx+0x50]] times the signed word at ebx (rounded down in eighths) stored at [ecx] plus
 * the stack argument; edx is left that address. */
uint32_t vertrix_port_table_byte_store_4c4cc0(PORT_SIGNATURE)
{
    Port port;
    uint8_t stack[8 + 4];
    uint32_t table;
    uint32_t index;
    uint32_t target;
    uint32_t value;
    port_open_arguments(&port, stack, calls, services, globals, entry, 0, 1);
    table = port_u32(&port, entry->eax, 0x144) + 0x80;
    index = port_u32(&port, port_u32(&port, entry->edx, 0x50), 0) *
                (uint32_t)(int16_t)port_u16(&port, entry->ebx, 0) +
            4;
    index = (uint32_t)((int32_t)index >> 3) & 0x3ff;
    target = port_u32(&port, entry->ecx, 0) + port_u32(&port, entry->esp, 4);
    value = port_u8(&port, table, index);
    port_set8(&port, target, 0, value);
    return port_return(&port, (index & 0xffffff00u) | value, target);
}

/* Original 0x4c98f0: tail call of 0x4eb5c0 with edx in ebx and edx 0. */
uint32_t vertrix_port_rtl_zero_call_4c98f0(PORT_SIGNATURE)
{
    Port port;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    result = port_forward(&port, entry, 0x4eb5c0, entry->eax, 0, entry->edx, entry->ecx);
    return port_return(&port, result, vertrix_lift_edx);
}

/* Original 0x4cf850: method +0xa4 of the object with the three dwords +0x3c to +0x44 of the record
 * of 0x4ce220. */
uint32_t vertrix_port_object_method_a4_4cf850(PORT_SIGNATURE)
{
    Port port;
    uint32_t record;
    uint32_t class_address;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    record = port_forward_esi(&port, entry, 0x4ce220, entry->eax, entry->edx, entry->ebx,
                              entry->ecx, entry->eax);
    class_address = port_u32(&port, entry->eax, 0);
    result = port_call_with(&port, port_u32(&port, class_address, 0xa4), entry->eax,
                            port_u32(&port, record, 0x3c), port_u32(&port, record, 0x40),
                            port_u32(&port, record, 0x44), entry->eax, class_address, entry->ebp);
    return port_return(&port, result, entry->edx);
}

/* Original 0x4cf8e0: 0x4cf880 with 1 and the stack argument, 0x4ded70 on its result and 0x4cce90
 * on both; the result of 0x4ded70. */
uint32_t vertrix_port_rtl_triple_call_4cf8e0(PORT_SIGNATURE)
{
    Port port;
    uint8_t stack[8 + 4];
    uint32_t first;
    uint32_t second;
    port_open_arguments(&port, stack, calls, services, globals, entry, 0, 1);
    first = port_forward(&port, entry, 0x4cf880, 1, port_u32(&port, entry->esp, 4), entry->ebx,
                         entry->ecx);
    second = port_forward(&port, entry, 0x4ded70, first, vertrix_lift_edx, entry->ebx, first);
    port_forward(&port, entry, 0x4cce90, second, first, second, first);
    return port_return(&port, second, vertrix_lift_edx);
}

/* Original 0x4d1e50: method +0xac of the object with edx pushed and the three dwords +0x3c to
 * +0x44 of the record of 0x4ce220. */
uint32_t vertrix_port_object_method_ac_4d1e50(PORT_SIGNATURE)
{
    Port port;
    uint32_t record;
    uint32_t class_address;
    uint32_t pushed[1];
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    record = port_forward_esi(&port, entry, 0x4ce220, entry->eax, entry->edx, entry->edx,
                              entry->ecx, entry->eax);
    class_address = port_u32(&port, entry->eax, 0);
    pushed[0] = entry->edx;
    vertrix_lift_in_esi = entry->eax;
    vertrix_lift_in_edi = class_address;
    vertrix_lift_in_ebp = entry->ebp;
    result = port_call_stack(&port, port_u32(&port, class_address, 0xac), entry->eax,
                             port_u32(&port, record, 0x3c), port_u32(&port, record, 0x40),
                             port_u32(&port, record, 0x44), pushed, 1);
    vertrix_lift_in_esi = vertrix_lift_in_edi = vertrix_lift_in_ebp = 0;
    return port_return(&port, result, vertrix_lift_edx);
}

/* Original 0x4dae94: store the code 0xe at +4 of the record of [0x507c9c]. */
uint32_t vertrix_port_thread_record_code_4dae94(PORT_SIGNATURE)
{
    Port port;
    uint32_t record;
    port_open(&port, calls, services, globals, entry);
    record =
        port_forward(&port, entry, port_u32(&port, 0, 0x507c9c), 0xe, 0xe, entry->ebx, entry->ecx);
    port_set32(&port, record, 4, vertrix_lift_edx);
    return port_return(&port, record, entry->edx);
}

/* Original 0x4de600: the standard handles 2 and 3 (the import 0x4f19e4) at 0x5c7944 and 0x5c7948,
 * with 0x5c79cc cleared. */
uint32_t vertrix_port_standard_handles_4de600(PORT_SIGNATURE)
{
    Port port;
    uint32_t pushed[1];
    uint32_t handle;
    port_open(&port, calls, services, globals, entry);
    pushed[0] = 2;
    handle = port_forward_stack(&port, entry, 0x4f19e4, entry->eax, entry->edx, entry->ebx,
                                entry->ecx, entry->esi, pushed, 1);
    port_set32(&port, 0, 0x5c7944, handle);
    pushed[0] = 3;
    handle = port_forward_stack(&port, entry, 0x4f19e4, handle, vertrix_lift_edx, entry->ebx,
                                entry->ecx, entry->esi, pushed, 1);
    port_set32(&port, 0, 0x5c79cc, 0);
    port_set32(&port, 0, 0x5c7948, handle);
    return port_return(&port, handle, vertrix_lift_edx);
}

/* Original 0x4e6cf2: reset the stream record: +4, +0x18, +0xc and +0x30 cleared, edx at +8 and
 * bits 0, 1 and 3 of the byte +0x25 cleared. */
uint32_t vertrix_port_stream_record_reset_4e6cf2(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    port_set32(&port, entry->eax, 4, 0);
    port_set32(&port, entry->eax, 0x18, 0);
    port_set32(&port, entry->eax, 0xc, 0);
    port_set32(&port, entry->eax, 0x30, 0);
    port_set32(&port, entry->eax, 8, entry->edx);
    port_set8(&port, entry->eax, 0x25, port_u8(&port, entry->eax, 0x25) & 0xf4);
    return port_return(&port, entry->eax, entry->edx);
}
