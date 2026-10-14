#include "port_branches.h"

/* Small routines with a guard, a choice of call or a short table scan. */

/* Original 0x40a860: copy the text of code eax (the text of code 0 above 11) to edx by 0x4eb860;
 * 0, or 2 above 11. Nothing when edx is null (2). */
uint32_t vertrix_port_text_for_code_40a860(PORT_SIGNATURE)
{
    Port port;
    uint32_t code = entry->eax;
    uint32_t text;
    port_open(&port, calls, services, globals, entry);
    if (entry->edx == 0)
    {
        return port_return(&port, 2, entry->edx);
    }
    text = port_u32(&port, 0, 0x4f641c + (code <= 0xb ? code * 4 : 0));
    port_forward(&port, entry, 0x4eb860, entry->edx, text, entry->ebx, code);
    return port_return(&port, code <= 0xb ? 0 : 2, vertrix_lift_edx);
}

/* Original 0x40aae0: set 0x4f6418 to 0xffff, call [0x52f034] and, when it gave 0, [0x52f01c];
 * then 0x40a800 with the result. */
uint32_t vertrix_port_open_then_40a800_40aae0(PORT_SIGNATURE)
{
    Port port;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    port_set32(&port, 0, 0x4f6418, 0xffff);
    result = port_forward(&port, entry, port_u32(&port, 0, 0x52f034), entry->eax, entry->edx,
                          entry->ebx, entry->ecx);
    if (result == 0)
    {
        result = port_forward(&port, entry, port_u32(&port, 0, 0x52f01c), result, vertrix_lift_edx,
                              entry->ebx, entry->ecx);
    }
    result = port_forward(&port, entry, 0x40a800, result, vertrix_lift_edx, entry->ebx, entry->ecx);
    return port_return(&port, result, vertrix_lift_edx);
}

/* Original 0x40aca0: 1 for a null cell; otherwise close it by [0x52f058] and, when its first
 * dword is set, free that by 0x4ea190; the close result. */
uint32_t vertrix_port_close_cell_40aca0(PORT_SIGNATURE)
{
    Port port;
    uint32_t cell = entry->eax;
    uint32_t result;
    uint32_t edx;
    uint32_t first;
    port_open(&port, calls, services, globals, entry);
    if (cell == 0)
    {
        return port_return(&port, 1, entry->edx);
    }
    result = port_forward(&port, entry, port_u32(&port, 0, 0x52f058), cell, cell, entry->ebx,
                          entry->ecx);
    edx = vertrix_lift_edx;
    first = port_u32(&port, edx, 0);
    if (first != 0)
    {
        port_forward(&port, entry, 0x4ea190, first, edx, first, result);
    }
    return port_return(&port, result, entry->edx);
}

/* Original 0x40bb30: set the flag at 0x52f1f8 to eax; when it goes from clear to set, keep the
 * time of import 0x4f1bf8 at 0x52f900 and clear 0x52f904. Always 0. */
uint32_t vertrix_port_timer_flag_set_40bb30(PORT_SIGNATURE)
{
    Port port;
    uint32_t flag = entry->eax;
    uint32_t time;
    port_open(&port, calls, services, globals, entry);
    if (flag != 0)
    {
        if (port_u32(&port, 0, 0x52f1f8) == 0)
        {
            time = port_forward(&port, entry, 0x4f1bf8, flag, entry->edx, flag, entry->ecx);
            port_set32(&port, 0, 0x52f900, time);
            port_set32(&port, 0, 0x52f904, 0);
        }
        port_set32(&port, 0, 0x52f1f8, flag);
    }
    return port_return(&port, 0, entry->edx);
}

/* Original 0x40bb70: for a rate of 0x20 to 0xff keep 5000 / (2 * rate) at 0x52f908 (0);
 * otherwise 2. */
uint32_t vertrix_port_rate_set_40bb70(PORT_SIGNATURE)
{
    Port port;
    uint32_t rate = entry->eax;
    port_open(&port, calls, services, globals, entry);
    if (rate < 0x20 || rate > 0xff)
    {
        return port_return(&port, 2, entry->edx);
    }
    port_set32(&port, 0, 0x52f908, 0x1388 / (rate + rate));
    return port_return(&port, 0, entry->edx);
}

/* Original 0x40c320: read one byte from the object at 0x52f90c into eax by 0x4ebec0; when that
 * does not read 1 byte, clear the byte by 0x4eb5c0. Always 0. */
uint32_t vertrix_port_read_byte_40c320(PORT_SIGNATURE)
{
    Port port;
    uint32_t object;
    uint32_t count;
    port_open(&port, calls, services, globals, entry);
    object = port_u32(&port, 0, 0x52f90c);
    count = port_forward_esi(&port, entry, 0x4ebec0, entry->eax, 1, 1, object, entry->eax);
    if (count != 1)
    {
        port_forward_esi(&port, entry, 0x4eb5c0, entry->eax, 0, 1, object, entry->eax);
    }
    return port_return(&port, 0, entry->edx);
}

/* Original 0x40c910: clear the 32 entries of 24 bytes at 0x52f918 by 0x4eb5c0, then set byte
 * +0x16 of each to 1. 0. */
uint32_t vertrix_port_entries_reset_40c910(PORT_SIGNATURE)
{
    Port port;
    uint32_t offset;
    port_open(&port, calls, services, globals, entry);
    port_forward(&port, entry, 0x4eb5c0, 0x52f918, 0, 0x300, entry->ecx);
    for (offset = 0; offset != 0x300; offset += 0x18)
    {
        port_set8(&port, offset, 0x52f92e, 1);
    }
    return port_return(&port, 0, entry->edx);
}

/* Original 0x40ccf0: store at edx whether bit 0 of byte +0x16 of entry eax (of 24 bytes at
 * 0x52f918) is set; 0, 1 past the count at 0x52fc18, 2 for a null edx. */
uint32_t vertrix_port_entry_flag_get_40ccf0(PORT_SIGNATURE)
{
    Port port;
    uint32_t index = entry->eax;
    uint32_t set;
    port_open(&port, calls, services, globals, entry);
    if (index >= port_u32(&port, 0, 0x52fc18))
    {
        return port_return(&port, 1, entry->edx);
    }
    if (entry->edx == 0)
    {
        return port_return(&port, 2, entry->edx);
    }
    set = (port_u8(&port, index * 24, 0x52f92e) & 1) != 0;
    port_set32(&port, entry->edx, 0, set);
    return port_return(&port, 0, entry->edx);
}

/* Original 0x40e640: release the note: clear its first byte; without an instrument (+0x34) set
 * bit 4 of byte +1; with one whose bit 0 of +0xbc is clear, clear +0x14 and +0x10 and set bits 1
 * and 4 of byte +1. */
uint32_t vertrix_port_mixer_note_release_40e640(PORT_SIGNATURE)
{
    Port port;
    uint32_t note = entry->eax;
    uint32_t instrument;
    port_open(&port, calls, services, globals, entry);
    port_set8(&port, note, 0, 0);
    instrument = port_u32(&port, note, 0x34);
    if (instrument == 0)
    {
        port_set8(&port, note, 1, port_u8(&port, note, 1) | 0x10);
    }
    else if ((port_u8(&port, instrument, 0xbc) & 1) == 0)
    {
        port_set32(&port, note, 0x14, 0);
        port_set32(&port, note, 0x10, port_u32(&port, note, 0x14));
        port_set8(&port, note, 1, port_u8(&port, note, 1) | 0x12);
    }
    return port_return(&port, note, entry->edx);
}

/* Original 0x40ee30: 3 when the device (bit 7 of 0x531b44) is closed; otherwise clear bits 4
 * and 5, then set bit 4 (0). */
uint32_t vertrix_port_device_mark_dirty_40ee30(PORT_SIGNATURE)
{
    Port port;
    uint32_t state;
    port_open(&port, calls, services, globals, entry);
    state = port_u8(&port, 0, 0x531b44);
    if ((state & 0x80) == 0)
    {
        return port_return(&port, 3, entry->edx);
    }
    port_set8(&port, 0, 0x531b44, state & 0xcf);
    port_set8(&port, 0, 0x531b44, (state & 0xcf) | 0x10);
    return port_return(&port, 0, entry->edx);
}

/* Original 0x40ef00: 3 when the device is closed, 2 for a null eax or edx; otherwise store
 * 0x531b5c at eax and 0x531b50 at edx (0, edx the second). */
uint32_t vertrix_port_device_get_values_40ef00(PORT_SIGNATURE)
{
    Port port;
    uint32_t second;
    port_open(&port, calls, services, globals, entry);
    if ((port_u8(&port, 0, 0x531b44) & 0x80) == 0)
    {
        return port_return(&port, 3, entry->edx);
    }
    if (entry->eax == 0 || entry->edx == 0)
    {
        return port_return(&port, 2, entry->edx);
    }
    port_set32(&port, entry->eax, 0, port_u32(&port, 0, 0x531b5c));
    second = port_u32(&port, 0, 0x531b50);
    port_set32(&port, entry->edx, 0, second);
    return port_return(&port, 0, second);
}

/* Original 0x40f170: one more than the index of the first of the 96 words at 0x4f74d4 not above
 * eax; 0 for eax 0 or when there is none. */
uint32_t vertrix_port_table_level_for_40f170(PORT_SIGNATURE)
{
    Port port;
    uint32_t value = entry->eax;
    uint32_t index;
    port_open(&port, calls, services, globals, entry);
    if (value == 0)
    {
        return port_return(&port, 0, entry->edx);
    }
    index = 0;
    for (;;)
    {
        uint32_t level = port_u16(&port, index * 2, 0x4f74d4);
        index++;
        if (value >= level)
        {
            return port_return(&port, index, entry->edx);
        }
        if (index >= 0x60)
        {
            return port_return(&port, 0, entry->edx);
        }
    }
}

/* Original 0x415550: when the latch at 0x532b40 is 1, clear it, 0x532b48 and 0x532b44. */
uint32_t vertrix_port_session_latch_release_415550(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    if (port_u32(&port, 0, 0x532b40) == 1)
    {
        port_set32(&port, 0, 0x532b40, 0);
        port_set32(&port, 0, 0x532b48, 0);
        port_set32(&port, 0, 0x532b44, 0);
    }
    return port_return(&port, entry->eax, entry->edx);
}

/* Original 0x415c00: whether all 19 dwords at 0x5344a4 are set. */
uint32_t vertrix_port_table_all_filled_415c00(PORT_SIGNATURE)
{
    Port port;
    uint32_t index;
    port_open(&port, calls, services, globals, entry);
    for (index = 0; index < 0x13; index++)
    {
        if (port_u32(&port, index * 4, 0x5344a4) == 0)
        {
            return port_return(&port, 0, entry->edx);
        }
    }
    return port_return(&port, 1, entry->edx);
}

/* Original 0x415e10: for each of the 76 dwords at 0x533164 call 0x482b30 with it (edx the next
 * offset, ecx 0), then clear the dword before the offset the call leaves in edx. */
uint32_t vertrix_port_clear_each_call_415e10(PORT_SIGNATURE)
{
    Port port;
    uint32_t offset = 0;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    do
    {
        uint32_t value = port_u32(&port, offset, 0x533164);
        offset += 4;
        result = port_forward(&port, entry, 0x482b30, value, offset, entry->ebx, 0);
        offset = vertrix_lift_edx;
        port_set32(&port, offset, 0x533160, 0);
    } while (offset != 0x130);
    return port_return(&port, result, entry->edx);
}

/* Original 0x415e80: the index of the last of the ebx dwords at edx equal to eax, or -1; edx
 * left past the dwords. */
uint32_t vertrix_port_table_find_equal_415e80(PORT_SIGNATURE)
{
    Port port;
    uint32_t found = 0xffffffff;
    uint32_t pointer = entry->edx;
    uint32_t index;
    port_open(&port, calls, services, globals, entry);
    for (index = 0; index < entry->ebx; index++)
    {
        if (entry->eax == port_u32(&port, pointer, 0))
        {
            found = index;
        }
        pointer += 4;
    }
    return port_return(&port, found, pointer);
}

/* Original 0x417840: the last step up to eax (byte counted) whose dword at 0x533290 differs from
 * the one before, in ah, and one more in al. */
uint32_t vertrix_port_table_last_change_417840(PORT_SIGNATURE)
{
    Port port;
    uint8_t step = 0;
    uint8_t last = 0;
    port_open(&port, calls, services, globals, entry);
    while (step <= entry->eax)
    {
        if (step > 0 &&
            port_u32(&port, step * 4u, 0x533294) != port_u32(&port, step * 4u, 0x533290))
        {
            last = step;
        }
        step++;
    }
    return port_return(&port,
                       (entry->eax & 0xffff0000u) | ((uint32_t)last << 8) | (uint8_t)(last + 1),
                       entry->edx);
}

/* Original 0x417df0: whether any of the 13 bytes of row eax at 0x4f9ad8 is set. */
uint32_t vertrix_port_table_row_used_417df0(PORT_SIGNATURE)
{
    Port port;
    uint32_t start = entry->eax * 13;
    uint32_t count = 0;
    uint32_t offset;
    port_open(&port, calls, services, globals, entry);
    for (offset = start; offset != start + 0xd; offset++)
    {
        if (port_u8(&port, offset, 0x4f9ad8) != 0)
        {
            count++;
        }
    }
    return port_return(&port, count > 0, entry->edx);
}

/* Original 0x417e20: eax plus the steps of edx below 0x532b34 times the multiplier of level
 * 0x532bbc (at 0x4f80d8), plus half of that, at most 99999999; edx the half. */
uint32_t vertrix_port_table_bonus_417e20(PORT_SIGNATURE)
{
    Port port;
    uint32_t limit;
    uint32_t steps;
    uint32_t level;
    uint32_t value;
    uint32_t half;
    port_open(&port, calls, services, globals, entry);
    limit = port_u32(&port, 0, 0x532b34);
    steps = entry->edx < limit ? limit - entry->edx : 0;
    level = port_u32(&port, 0, 0x532bbc);
    value = steps * port_u32(&port, level * 4, 0x4f80d8) + entry->eax;
    half = value >> 1;
    value += half;
    if (value > 0x5f5e0ff)
    {
        value = 0x5f5e0ff;
    }
    return port_return(&port, value, half);
}

/* Original 0x41a960: allocate 0x280 bytes by 0x4ca000 (0x4413b0 with a nonzero result), keep the
 * result at 0x544070, set it up by 0x441530 and finish by 0x441600. */
uint32_t vertrix_port_buffer_setup_41a960(PORT_SIGNATURE)
{
    Port port;
    uint32_t result;
    uint32_t pushed[4] = {0, 0, 0xd, 0x50dc88};
    port_open(&port, calls, services, globals, entry);
    result = port_forward(&port, entry, 0x4ca000, 0x280, entry->edx, entry->ebx, entry->ecx);
    if (result != 0)
    {
        result =
            port_forward(&port, entry, 0x4413b0, result, vertrix_lift_edx, entry->ebx, entry->ecx);
    }
    port_set32(&port, 0, 0x544070, result);
    port_forward_stack(&port, entry, 0x441530, result, vertrix_lift_edx, 0, 0x10, entry->esi,
                       pushed, 4);
    result = port_forward(&port, entry, 0x441600, port_u32(&port, 0, 0x544070), vertrix_lift_edx, 0,
                          0x10);
    return port_return(&port, result, vertrix_lift_edx);
}

/* Original 0x41ac40: when 0x4854a0 on 0x5b9c50 gives 1, 0x478f50 on 0x558c84 (edx 0), then
 * 0x485520 on 0x5b9c50. */
uint32_t vertrix_port_guarded_update_41ac40(PORT_SIGNATURE)
{
    Port port;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    result = port_forward(&port, entry, 0x4854a0, 0x5b9c50, entry->edx, entry->ebx, entry->ecx);
    if (result == 1)
    {
        port_forward(&port, entry, 0x478f50, port_u32(&port, 0, 0x558c84), 0, entry->ebx,
                     entry->ecx);
        result = port_forward(&port, entry, 0x485520, 0x5b9c50, vertrix_lift_edx, entry->ebx,
                              entry->ecx);
    }
    return port_return(&port, result, entry->edx);
}

/* Original 0x42a140: the cell at row edx, column ebx of the grid at +0x15c; 0 when it is null
 * or its byte +0x15c is set, otherwise set its byte +0x15d (1). */
uint32_t vertrix_port_choice_grid_mark_42a140(PORT_SIGNATURE)
{
    Port port;
    uint32_t edx = entry->edx << 4;
    uint32_t cell;
    uint32_t shown;
    port_open(&port, calls, services, globals, entry);
    cell = port_u32(&port, entry->eax + edx, entry->ebx * 4 + 0x15c);
    if (cell == 0)
    {
        return port_return(&port, 0, edx);
    }
    shown = port_u8(&port, cell, 0x15c);
    edx = (edx & 0xffffff00u) | shown;
    if (shown != 0)
    {
        return port_return(&port, 0, edx);
    }
    port_set8(&port, cell, 0x15d, 1);
    return port_return(&port, 1, edx);
}

/* Original 0x42b110: set the preview mode +0x180 to edx; entering mode 1 from 0 sets +0x184,
 * leaving mode 1 clears it. */
uint32_t vertrix_port_player_preview_set_mode_42b110(PORT_SIGNATURE)
{
    Port port;
    uint32_t preview = entry->eax;
    port_open(&port, calls, services, globals, entry);
    if (entry->edx == 1)
    {
        if (port_u32(&port, preview, 0x180) == 0)
        {
            port_set32(&port, preview, 0x184, entry->edx);
        }
    }
    else if (port_u32(&port, preview, 0x180) == 1)
    {
        port_set32(&port, preview, 0x184, 0);
    }
    port_set32(&port, preview, 0x180, entry->edx);
    return port_return(&port, preview, entry->edx);
}

/* Original 0x42b150: construct by 0x4abd70, set the class 0x514814 at +0x158 and clear the
 * three dwords from +0x15c and from +0x168. */
uint32_t vertrix_port_ui_player_preview_parent_construct_42b150(PORT_SIGNATURE)
{
    Port port;
    uint32_t object;
    uint32_t offset;
    port_open(&port, calls, services, globals, entry);
    object = port_forward(&port, entry, 0x4abd70, entry->eax, entry->edx, entry->ebx, entry->eax);
    port_set32(&port, object, 0x158, 0x514814);
    for (offset = 4; offset != 0x10; offset += 4)
    {
        port_set32(&port, object + offset, 0x158, 0);
        port_set32(&port, object + offset, 0x164, 0);
    }
    return port_return(&port, object, entry->edx);
}

/* Original 0x42b920: set the variant +0x168 to edx; variants 0 and 1 load the images at 0x544ba0
 * and 0x544bbc by 0x4ac8d0. */
uint32_t vertrix_port_piece_set_variant_42b920(PORT_SIGNATURE)
{
    Port port;
    uint32_t piece = entry->eax;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    port_set32(&port, piece, 0x168, entry->edx);
    if (entry->edx != 0 && entry->edx != 1)
    {
        return port_return(&port, piece, entry->edx);
    }
    result = port_forward(&port, entry, 0x4ac8d0, piece, entry->edx == 0 ? 0x544ba0 : 0x544bbc,
                          entry->ebx, entry->ecx);
    return port_return(&port, result, vertrix_lift_edx);
}

/* Original 0x42b950: when the word +0xe differs from +0xa8, take it and set the variant by
 * 0x42b920 (1 when byte +0x16c is set, else 0). */
uint32_t vertrix_port_piece_snap_to_left_42b950(PORT_SIGNATURE)
{
    Port port;
    uint32_t piece = entry->eax;
    uint32_t left;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    left = port_u16(&port, piece, 0xa8);
    if (port_u16(&port, piece, 0xe) == left)
    {
        return port_return(&port, piece, entry->edx);
    }
    port_set16(&port, piece, 0xe, left);
    result = port_forward(&port, entry, 0x42b920, piece, port_u8(&port, piece, 0x16c) != 0,
                          (entry->ebx & 0xffff0000u) | left, entry->ecx);
    return port_return(&port, result, entry->edx);
}

/* Original 0x42ba70: set the word +0x48 to -200 when the toggle +0x164 is clear, else 0, then
 * flip the toggle; the new toggle. */
uint32_t vertrix_port_toggle_offset_42ba70(PORT_SIGNATURE)
{
    Port port;
    uint32_t object = entry->eax;
    uint32_t toggle;
    port_open(&port, calls, services, globals, entry);
    toggle = port_u32(&port, object, 0x164);
    port_set16(&port, object, 0x48, toggle == 0 ? 0xff38 : 0);
    toggle = 1 - port_u32(&port, object, 0x164);
    port_set32(&port, object, 0x164, toggle);
    return port_return(&port, toggle, entry->edx);
}

/* Original 0x42ed40, 0x42ed70 and 0x42edf0: 1 without an active piece (+0xa60); otherwise
 * 0x4b2300 on its list at `list` with edx 3 and ebx the given edx. */
static uint32_t active_piece_list(PORT_SIGNATURE, uint32_t list)
{
    Port port;
    uint32_t piece;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    piece = port_u32(&port, entry->eax, 0xa60);
    if (piece == 0)
    {
        return port_return(&port, 1, entry->edx);
    }
    result = port_forward(&port, entry, 0x4b2300, piece + list, 3, entry->edx, piece);
    return port_return(&port, result, vertrix_lift_edx);
}

uint32_t vertrix_port_board_piece_all_handler_42ed40(PORT_SIGNATURE)
{
    return active_piece_list(calls, services, globals, entry, 0x15c);
}

uint32_t vertrix_port_board_piece_all_handler_42ed70(PORT_SIGNATURE)
{
    return active_piece_list(calls, services, globals, entry, 0x170);
}

uint32_t vertrix_port_board_piece_all_handler_42edf0(PORT_SIGNATURE)
{
    return active_piece_list(calls, services, globals, entry, 0x15c);
}

/* Original 0x42f280: when 0x4320c0 and 0x42efa0 both give 1, store the byte +0x58 and then its
 * negation at +0xa65; al the byte and ah its negation. */
uint32_t vertrix_port_board_piece_store_negated_42f280(PORT_SIGNATURE)
{
    Port port;
    uint32_t board = entry->eax;
    uint32_t result;
    uint32_t value;
    port_open(&port, calls, services, globals, entry);
    result = port_forward(&port, entry, 0x4320c0, board, entry->edx, entry->ebx, board);
    if (result != 1)
    {
        return port_return(&port, result, vertrix_lift_edx);
    }
    result = port_forward(&port, entry, 0x42efa0, board, vertrix_lift_edx, entry->ebx, board);
    if (result != 1)
    {
        return port_return(&port, result, vertrix_lift_edx);
    }
    value = port_u8(&port, board, 0x58);
    port_set8(&port, board, 0xa65, value);
    port_set8(&port, board, 0xa65, (uint8_t)-value);
    return port_return(&port, ((uint32_t)(uint8_t)-value << 8) | value, vertrix_lift_edx);
}

/* Original 0x42f2b0: the same without the 0x42efa0 check, the board the edx 0x4320c0 leaves. */
uint32_t vertrix_port_board_piece_store_negated_always_42f2b0(PORT_SIGNATURE)
{
    Port port;
    uint32_t result;
    uint32_t board;
    uint32_t value;
    port_open(&port, calls, services, globals, entry);
    result = port_forward(&port, entry, 0x4320c0, entry->eax, entry->eax, entry->ebx, entry->ecx);
    if (result != 1)
    {
        return port_return(&port, result, entry->edx);
    }
    board = vertrix_lift_edx;
    value = port_u8(&port, board, 0x58);
    port_set8(&port, board, 0xa65, value);
    port_set8(&port, board, 0xa65, (uint8_t)-value);
    return port_return(&port, ((uint32_t)(uint8_t)-value << 8) | value, entry->edx);
}
