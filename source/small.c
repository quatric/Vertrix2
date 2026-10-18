#include "small.h"

/* Small field accessors, flags and global copies (one to a few instructions each). */

/* Original 0x4126d0: Toggle the flag dword +0x5cc[edx] between 1 and 0 (anything but 1 becomes 1);
 * edx is left the new flag. */
uint32_t vertrix_port_object_toggle_flag_4126d0(PORT_SIGNATURE)
{
    Port port;
    uint32_t eax;
    uint32_t edx;
    port_open(&port, calls, services, globals, entry);
    eax = entry->eax + entry->edx * 4;
    edx = port_u32(&port, eax, 0x5cc) != 1;
    port_set32(&port, eax, 0x5cc, edx);
    return port_return(&port, eax, edx);
}

/* Original 0x4126f0: The flag dword +0x5cc[edx]. */
uint32_t vertrix_port_object_flag_4126f0(PORT_SIGNATURE)
{
    Port port;
    uint32_t eax;
    port_open(&port, calls, services, globals, entry);
    eax = port_u32(&port, entry->eax + entry->edx * 4, 0x5cc);
    return port_return(&port, eax, entry->edx);
}

/* Original 0x415b30: Set cell eax of the dword table at 0x5344a4. */
uint32_t vertrix_port_global_set_first_cell_415b30(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    port_set32(&port, entry->eax * 4, 0x5344a4, 1);
    return port_return(&port, entry->eax, entry->edx);
}

/* Original 0x415b40: Set cell eax of the dword table at 0x5344f0. */
uint32_t vertrix_port_global_set_second_cell_415b40(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    port_set32(&port, entry->eax * 4, 0x5344f0, 1);
    return port_return(&port, entry->eax, entry->edx);
}

/* Original 0x415d40: Advance the index at 0x53bb10; whether it has not reached 7. */
uint32_t vertrix_port_global_next_index_415d40(PORT_SIGNATURE)
{
    Port port;
    uint32_t eax;
    uint32_t edx;
    port_open(&port, calls, services, globals, entry);
    edx = port_u32(&port, 0, 0x53bb10) + 1;
    port_set32(&port, 0, 0x53bb10, edx);
    eax = edx != 7;
    edx = entry->edx;
    return port_return(&port, eax, edx);
}

/* Original 0x415d90: Set the cell of the dword table at 0x53baf4 the index at 0x53bb10 selects. */
uint32_t vertrix_port_global_set_current_cell_415d90(PORT_SIGNATURE)
{
    Port port;
    uint32_t eax;
    port_open(&port, calls, services, globals, entry);
    eax = port_u32(&port, 0, 0x53bb10);
    port_set32(&port, eax * 4, 0x53baf4, 1);
    return port_return(&port, eax, entry->edx);
}

/* Original 0x417cf0: The dword at row eax, column edx of the 22-column grid at 0x533e1c; edx is
 * left the row. */
uint32_t vertrix_port_table_grid_value_417cf0(PORT_SIGNATURE)
{
    Port port;
    uint32_t eax;
    uint32_t edx;
    port_open(&port, calls, services, globals, entry);
    eax = port_u32(&port, (entry->eax * 22 + entry->edx) * 4, 0x533e1c);
    edx = entry->eax;
    return port_return(&port, eax, edx);
}

/* Original 0x42a940: piece clear offset x. */
uint32_t vertrix_port_piece_clear_offset_x_42a940(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    port_set8(&port, entry->eax, 0x16c, 0);
    return port_return(&port, entry->eax, entry->edx);
}

/* Original 0x42a950: piece clear offset y. */
uint32_t vertrix_port_piece_clear_offset_y_42a950(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    port_set8(&port, entry->eax, 0x16d, 0);
    return port_return(&port, entry->eax, entry->edx);
}

/* Original 0x42a960: piece set offset x. */
uint32_t vertrix_port_piece_set_offset_x_42a960(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    port_set8(&port, entry->eax, 0x16c, entry->edx);
    return port_return(&port, entry->eax, entry->edx);
}

/* Original 0x42a970: piece set offset y. */
uint32_t vertrix_port_piece_set_offset_y_42a970(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    port_set8(&port, entry->eax, 0x16d, entry->edx);
    return port_return(&port, entry->eax, entry->edx);
}

/* Original 0x42b050: Whether the signed word +0x16 is above the word +0xae. */
uint32_t vertrix_port_player_preview_below_limit_42b050(PORT_SIGNATURE)
{
    Port port;
    uint32_t eax;
    port_open(&port, calls, services, globals, entry);
    eax = (int16_t)port_u16(&port, entry->eax, 0x16) > (int16_t)port_u16(&port, entry->eax, 0xae);
    return port_return(&port, eax, entry->edx);
}

/* Original 0x42b070: Field +0xb8 of the preview object +0x158[+0x188]. */
uint32_t vertrix_port_player_preview_frame_42b070(PORT_SIGNATURE)
{
    Port port;
    uint32_t eax;
    port_open(&port, calls, services, globals, entry);
    eax = port_u32(&port, entry->eax + port_u32(&port, entry->eax, 0x188) * 4, 0x158);
    eax = port_u32(&port, eax, 0xb8);
    return port_return(&port, eax, entry->edx);
}

/* Original 0x42b0f0: Flip the dword +0x184 to 1 less itself; the new value. */
uint32_t vertrix_port_player_preview_toggle_42b0f0(PORT_SIGNATURE)
{
    Port port;
    uint32_t eax;
    port_open(&port, calls, services, globals, entry);
    eax = 1 - port_u32(&port, entry->eax, 0x184);
    port_set32(&port, entry->eax, 0x184, eax);
    return port_return(&port, eax, entry->edx);
}

/* Original 0x42f890: board piece set offset x. */
uint32_t vertrix_port_board_piece_set_offset_x_42f890(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    port_set8(&port, entry->eax, 0xa64, entry->edx);
    return port_return(&port, entry->eax, entry->edx);
}

/* Original 0x42f8a0: board piece set offset y. */
uint32_t vertrix_port_board_piece_set_offset_y_42f8a0(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    port_set8(&port, entry->eax, 0xa65, entry->edx);
    return port_return(&port, entry->eax, entry->edx);
}

/* Original 0x431380: Field +0x168 of the object +0xa60. */
uint32_t vertrix_port_board_object_field_431380(PORT_SIGNATURE)
{
    Port port;
    uint32_t eax;
    port_open(&port, calls, services, globals, entry);
    eax = port_u32(&port, port_u32(&port, entry->eax, 0xa60), 0x168);
    return port_return(&port, eax, entry->edx);
}

/* Original 0x431480: Field +0x170 of the object +0xb70. */
uint32_t vertrix_port_board_object_field_431480(PORT_SIGNATURE)
{
    Port port;
    uint32_t eax;
    port_open(&port, calls, services, globals, entry);
    eax = port_u32(&port, port_u32(&port, entry->eax, 0xb70), 0x170);
    return port_return(&port, eax, entry->edx);
}

/* Original 0x431490: Field +0x178 of the object +0xb78. */
uint32_t vertrix_port_board_object_field_431490(PORT_SIGNATURE)
{
    Port port;
    uint32_t eax;
    port_open(&port, calls, services, globals, entry);
    eax = port_u32(&port, port_u32(&port, entry->eax, 0xb78), 0x178);
    return port_return(&port, eax, entry->edx);
}

/* Original 0x431d60: Whether the signed word +0x16 is at most that of the object +0xa60. */
uint32_t vertrix_port_board_row_not_below_431d60(PORT_SIGNATURE)
{
    Port port;
    uint32_t eax;
    port_open(&port, calls, services, globals, entry);
    eax = (int16_t)port_u16(&port, entry->eax, 0x16) <=
          (int16_t)port_u16(&port, port_u32(&port, entry->eax, 0xa60), 0x16);
    return port_return(&port, eax, entry->edx);
}

/* Original 0x431d80: board set a68. */
uint32_t vertrix_port_board_set_a68_431d80(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    port_set32(&port, entry->eax, 0xa68, entry->edx);
    return port_return(&port, entry->eax, entry->edx);
}

/* Original 0x432000: Field +0x17c of the object +0xa60. */
uint32_t vertrix_port_board_object_field_432000(PORT_SIGNATURE)
{
    Port port;
    uint32_t eax;
    port_open(&port, calls, services, globals, entry);
    eax = port_u32(&port, port_u32(&port, entry->eax, 0xa60), 0x17c);
    return port_return(&port, eax, entry->edx);
}

/* Original 0x4320c0: Whether the object +0xa60 is set. */
uint32_t vertrix_port_player_test_a60_4320c0(PORT_SIGNATURE)
{
    Port port;
    uint32_t eax;
    port_open(&port, calls, services, globals, entry);
    eax = port_u32(&port, entry->eax, 0xa60) != 0;
    return port_return(&port, eax, entry->edx);
}

/* Original 0x4334a0: Clear the byte +0x838 and store dl at +0x839. */
uint32_t vertrix_port_board_reset_counter_4334a0(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    port_set8(&port, entry->eax, 0x838, 0);
    port_set8(&port, entry->eax, 0x839, entry->edx);
    return port_return(&port, entry->eax, entry->edx);
}

/* Original 0x4342f0: board bump counter. */
uint32_t vertrix_port_board_bump_counter_4342f0(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    port_set8(&port, entry->eax, 0x838, port_u8(&port, entry->eax, 0x838) + 1);
    return port_return(&port, entry->eax, entry->edx);
}

/* Original 0x43a4f0: Store dl, bl and cl at +0x168, +0x169 and +0x16a. */
uint32_t vertrix_port_player_write_bytes_168_43a4f0(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    port_set8(&port, entry->eax, 0x168, entry->edx);
    port_set8(&port, entry->eax, 0x169, entry->ebx);
    port_set8(&port, entry->eax, 0x16a, entry->ecx);
    return port_return(&port, entry->eax, entry->edx);
}

/* Original 0x43ad50: Set the dword +0x178 of the object +0x450; that object. */
uint32_t vertrix_port_player_reset_piece_progress_43ad50(PORT_SIGNATURE)
{
    Port port;
    uint32_t eax;
    port_open(&port, calls, services, globals, entry);
    eax = port_u32(&port, entry->eax, 0x450);
    port_set32(&port, eax, 0x178, 1);
    return port_return(&port, eax, entry->edx);
}

/* Original 0x43b860: player set e0. */
uint32_t vertrix_port_player_set_e0_43b860(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    port_set32(&port, entry->eax, 0x4e0, entry->edx);
    return port_return(&port, entry->eax, entry->edx);
}

/* Original 0x43b870: player e0. */
uint32_t vertrix_port_player_e0_43b870(PORT_SIGNATURE)
{
    Port port;
    uint32_t eax;
    port_open(&port, calls, services, globals, entry);
    eax = port_u32(&port, entry->eax, 0x4e0);
    return port_return(&port, eax, entry->edx);
}

/* Original 0x43b970: player test 4e8. */
uint32_t vertrix_port_player_test_4e8_43b970(PORT_SIGNATURE)
{
    Port port;
    uint32_t eax;
    port_open(&port, calls, services, globals, entry);
    eax = port_u32(&port, entry->eax, 0x4e8) != 0;
    return port_return(&port, eax, entry->edx);
}

/* Original 0x43ba80: player clear field 18c. */
uint32_t vertrix_port_player_clear_field_18c_43ba80(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    port_set32(&port, entry->eax, 0x18c, 0);
    return port_return(&port, entry->eax, entry->edx);
}

/* Original 0x43bad0: player set cd. */
uint32_t vertrix_port_player_set_cd_43bad0(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    port_set8(&port, entry->eax, 0x4cd, entry->edx);
    return port_return(&port, entry->eax, entry->edx);
}

/* Original 0x43bae0: player set cc. */
uint32_t vertrix_port_player_set_cc_43bae0(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    port_set8(&port, entry->eax, 0x4cc, entry->edx);
    return port_return(&port, entry->eax, entry->edx);
}

/* Original 0x43bd40: Whether the byte +0x4c4 is 1. */
uint32_t vertrix_port_player_test_4c4_43bd40(PORT_SIGNATURE)
{
    Port port;
    uint32_t eax;
    port_open(&port, calls, services, globals, entry);
    eax = port_u8(&port, entry->eax, 0x4c4) == 1;
    return port_return(&port, eax, entry->edx);
}

/* Original 0x43cc90: Whether the partner's (+0x3b0) byte +0x4cc is not 1. */
uint32_t vertrix_port_player_partner_not_cc_one_43cc90(PORT_SIGNATURE)
{
    Port port;
    uint32_t eax;
    port_open(&port, calls, services, globals, entry);
    eax = port_u8(&port, port_u32(&port, entry->eax, 0x3b0), 0x4cc) != 1;
    return port_return(&port, eax, entry->edx);
}

/* Original 0x43cde0: player enter state. */
uint32_t vertrix_port_player_enter_state_43cde0(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    port_set8(&port, entry->eax, 0x4dc, 2);
    port_set32(&port, entry->eax, 0x470, 3);
    return port_return(&port, entry->eax, entry->edx);
}

/* Original 0x448670: Copy the dword at 0x4f7ba4 to 0x532a4c. */
uint32_t vertrix_port_copy_global_532a4c_448670(PORT_SIGNATURE)
{
    Port port;
    uint32_t eax;
    port_open(&port, calls, services, globals, entry);
    eax = port_u32(&port, 0, 0x4f7ba4);
    port_set32(&port, 0, 0x532a4c, eax);
    return port_return(&port, eax, entry->edx);
}

/* Original 0x448680: Copy the dword at 0x532b68 to 0x55893c and 0x532b64. */
uint32_t vertrix_port_copy_global_532b68_448680(PORT_SIGNATURE)
{
    Port port;
    uint32_t eax;
    port_open(&port, calls, services, globals, entry);
    eax = port_u32(&port, 0, 0x532b68);
    port_set32(&port, 0, 0x55893c, eax);
    port_set32(&port, 0, 0x532b64, eax);
    return port_return(&port, eax, entry->edx);
}

/* Original 0x471e60: Flip the dword +0x454 of the object at [0x540f8c] to 1 less itself; the
 * object. */
uint32_t vertrix_port_object_flip_454_471e60(PORT_SIGNATURE)
{
    Port port;
    uint32_t eax;
    port_open(&port, calls, services, globals, entry);
    eax = port_u32(&port, 0, 0x540f8c);
    port_set32(&port, eax, 0x454, 1 - port_u32(&port, eax, 0x454));
    return port_return(&port, eax, entry->edx);
}

/* Original 0x471e80: The same for the object at [0x540f90]. */
uint32_t vertrix_port_object_flip_454_471e80(PORT_SIGNATURE)
{
    Port port;
    uint32_t eax;
    port_open(&port, calls, services, globals, entry);
    eax = port_u32(&port, 0, 0x540f90);
    port_set32(&port, eax, 0x454, 1 - port_u32(&port, eax, 0x454));
    return port_return(&port, eax, entry->edx);
}

/* Original 0x471ea0: Store edx at +0x464 of object eax of the table at 0x540f88; the object. */
uint32_t vertrix_port_object_set_464_471ea0(PORT_SIGNATURE)
{
    Port port;
    uint32_t eax;
    port_open(&port, calls, services, globals, entry);
    eax = port_u32(&port, entry->eax * 4, 0x540f88);
    port_set32(&port, eax, 0x464, entry->edx);
    return port_return(&port, eax, entry->edx);
}

/* Original 0x471eb0: object get 464. */
uint32_t vertrix_port_object_get_464_471eb0(PORT_SIGNATURE)
{
    Port port;
    uint32_t eax;
    port_open(&port, calls, services, globals, entry);
    eax = port_u32(&port, port_u32(&port, entry->eax * 4, 0x540f88), 0x464);
    return port_return(&port, eax, entry->edx);
}

/* Original 0x471ec0: object get 174. */
uint32_t vertrix_port_object_get_174_471ec0(PORT_SIGNATURE)
{
    Port port;
    uint32_t eax;
    port_open(&port, calls, services, globals, entry);
    eax = port_u32(&port, port_u32(&port, entry->eax * 4, 0x540f88), 0x174);
    return port_return(&port, eax, entry->edx);
}

/* Original 0x475dd0: progress set 40. */
uint32_t vertrix_port_progress_set_40_475dd0(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    port_set32(&port, entry->eax, 0x40, entry->edx);
    return port_return(&port, entry->eax, entry->edx);
}

/* Original 0x475de0: input repeat counter clear. */
uint32_t vertrix_port_input_repeat_counter_clear_475de0(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    port_set32(&port, entry->eax, 0x44, 0);
    return port_return(&port, entry->eax, entry->edx);
}

/* Original 0x475e30: input repeat counter advance. */
uint32_t vertrix_port_input_repeat_counter_advance_475e30(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    port_set32(&port, entry->eax, 0x44, port_u32(&port, entry->eax, 0x44) + entry->edx);
    return port_return(&port, entry->eax, entry->edx);
}

/* Original 0x475e40: progress set 3c. */
uint32_t vertrix_port_progress_set_3c_475e40(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    port_set32(&port, entry->eax, 0x3c, entry->edx);
    return port_return(&port, entry->eax, entry->edx);
}

/* Original 0x479b30: The address of cell (edx, ebx) of the surface: base +0 plus ebx rows of pitch
 * +0x14 plus edx dwords. */
uint32_t vertrix_port_surface_cell_address_479b30(PORT_SIGNATURE)
{
    Port port;
    uint32_t eax;
    port_open(&port, calls, services, globals, entry);
    eax = entry->ebx * port_u32(&port, entry->eax, 0x14) + port_u32(&port, entry->eax, 0) +
          entry->edx * 4;
    return port_return(&port, eax, entry->edx);
}

/* Original 0x47e990: Whether the dword at eax is set. */
uint32_t vertrix_port_dword_set_47e990(PORT_SIGNATURE)
{
    Port port;
    uint32_t eax;
    port_open(&port, calls, services, globals, entry);
    eax = port_u32(&port, entry->eax, 0) != 0;
    return port_return(&port, eax, entry->edx);
}

/* Original 0x47e9a0: object dword. */
uint32_t vertrix_port_object_dword_47e9a0(PORT_SIGNATURE)
{
    Port port;
    uint32_t eax;
    port_open(&port, calls, services, globals, entry);
    eax = port_u32(&port, entry->eax, 0x1c4);
    return port_return(&port, eax, entry->edx);
}

/* Original 0x47ed60: object set dword. */
uint32_t vertrix_port_object_set_dword_47ed60(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    port_set32(&port, entry->eax, 0x20, entry->edx);
    return port_return(&port, entry->eax, entry->edx);
}

/* Original 0x47ed70: object set dword. */
uint32_t vertrix_port_object_set_dword_47ed70(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    port_set32(&port, entry->eax, 0x24, entry->edx);
    return port_return(&port, entry->eax, entry->edx);
}

/* Original 0x47ed80: object set dword. */
uint32_t vertrix_port_object_set_dword_47ed80(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    port_set32(&port, entry->eax, 0x28, entry->edx);
    return port_return(&port, entry->eax, entry->edx);
}

/* Original 0x47ed90: object set dword. */
uint32_t vertrix_port_object_set_dword_47ed90(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    port_set32(&port, entry->eax, 0x2c, entry->edx);
    return port_return(&port, entry->eax, entry->edx);
}

/* Original 0x480070: object dword. */
uint32_t vertrix_port_object_dword_480070(PORT_SIGNATURE)
{
    Port port;
    uint32_t eax;
    port_open(&port, calls, services, globals, entry);
    eax = port_u32(&port, entry->eax, 0x4c);
    return port_return(&port, eax, entry->edx);
}

/* Original 0x482050: object clear 208. */
uint32_t vertrix_port_object_clear_208_482050(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    port_set8(&port, entry->eax, 0x208, 0);
    return port_return(&port, entry->eax, entry->edx);
}

/* Original 0x487870: The table object: class 0x516dc4 at +0xc, no items (+0 and +8) and the pointer
 * at 0x4f81cc at +4. */
uint32_t vertrix_port_table_object_construct_487870(PORT_SIGNATURE)
{
    Port port;
    uint32_t edx;
    port_open(&port, calls, services, globals, entry);
    port_set32(&port, entry->eax, 0xc, 0x516dc4);
    port_set32(&port, entry->eax, 0, 0);
    edx = port_u32(&port, 0, 0x4f81cc);
    port_set32(&port, entry->eax, 8, 0);
    port_set32(&port, entry->eax, 4, edx);
    edx = entry->edx;
    return port_return(&port, entry->eax, edx);
}

/* Original 0x4879e0: Whether the count +8 is zero. */
uint32_t vertrix_port_list_empty_4879e0(PORT_SIGNATURE)
{
    Port port;
    uint32_t eax;
    port_open(&port, calls, services, globals, entry);
    eax = port_u32(&port, entry->eax, 8) == 0;
    return port_return(&port, eax, entry->edx);
}

/* Original 0x488030: Item edx of the table +0x18. */
uint32_t vertrix_port_table_item_488030(PORT_SIGNATURE)
{
    Port port;
    uint32_t eax;
    port_open(&port, calls, services, globals, entry);
    eax = port_u32(&port, port_u32(&port, entry->eax, 0x18), entry->edx * 4);
    return port_return(&port, eax, entry->edx);
}

/* Original 0x488040: Item edx of the table +0x1c. */
uint32_t vertrix_port_table_item_488040(PORT_SIGNATURE)
{
    Port port;
    uint32_t eax;
    port_open(&port, calls, services, globals, entry);
    eax = port_u32(&port, port_u32(&port, entry->eax, 0x1c), entry->edx * 4);
    return port_return(&port, eax, entry->edx);
}

/* Original 0x48c370: Copy the dword at 0x5bb518 to 0x5bd834. */
uint32_t vertrix_port_copy_dword_48c370(PORT_SIGNATURE)
{
    Port port;
    uint32_t eax;
    port_open(&port, calls, services, globals, entry);
    eax = port_u32(&port, 0, 0x5bb518);
    port_set32(&port, 0, 0x5bd834, eax);
    return port_return(&port, eax, entry->edx);
}

/* Original 0x48d5f0: Whether the count +8 is zero. */
uint32_t vertrix_port_list_empty_48d5f0(PORT_SIGNATURE)
{
    Port port;
    uint32_t eax;
    port_open(&port, calls, services, globals, entry);
    eax = port_u32(&port, entry->eax, 8) == 0;
    return port_return(&port, eax, entry->edx);
}

/* Original 0x4ac1e0: Set cell eax of the dword table at 0x5bb714. */
uint32_t vertrix_port_set_global_cell_5bb714_4ac1e0(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    port_set32(&port, entry->eax * 4, 0x5bb714, 1);
    return port_return(&port, entry->eax, entry->edx);
}

/* Original 0x4ac610: actor clear dc. */
uint32_t vertrix_port_actor_clear_dc_4ac610(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    port_set32(&port, entry->eax, 0xdc, 0);
    return port_return(&port, entry->eax, entry->edx);
}

/* Original 0x4ac960: actor get b4. */
uint32_t vertrix_port_actor_get_b4_4ac960(PORT_SIGNATURE)
{
    Port port;
    uint32_t eax;
    port_open(&port, calls, services, globals, entry);
    eax = port_u32(&port, entry->eax, 0xb4);
    return port_return(&port, eax, entry->edx);
}

/* Original 0x4ad510: Store dx, bx and cx at +0x2a, +0x2c and +0x2e. */
uint32_t vertrix_port_actor_set_words_2a_4ad510(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    port_set16(&port, entry->eax, 0x2a, entry->edx);
    port_set16(&port, entry->eax, 0x2c, entry->ebx);
    port_set16(&port, entry->eax, 0x2e, entry->ecx);
    return port_return(&port, entry->eax, entry->edx);
}

/* Original 0x4ad520: Store dx, bx and cx at +0x3a, +0x3c and +0x3e. */
uint32_t vertrix_port_actor_set_words_3a_4ad520(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    port_set16(&port, entry->eax, 0x3a, entry->edx);
    port_set16(&port, entry->eax, 0x3c, entry->ebx);
    port_set16(&port, entry->eax, 0x3e, entry->ecx);
    return port_return(&port, entry->eax, entry->edx);
}

/* Original 0x4adfa0: actor set 134. */
uint32_t vertrix_port_actor_set_134_4adfa0(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    port_set32(&port, entry->eax, 0x134, entry->edx);
    return port_return(&port, entry->eax, entry->edx);
}

/* Original 0x4b3c30: object set pair. */
uint32_t vertrix_port_object_set_pair_4b3c30(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    port_set32(&port, entry->eax, 0x184, entry->edx);
    port_set32(&port, entry->eax, 0x188, entry->ebx);
    return port_return(&port, entry->eax, entry->edx);
}

/* Original 0x4b4500: object dword. */
uint32_t vertrix_port_object_dword_4b4500(PORT_SIGNATURE)
{
    Port port;
    uint32_t eax;
    port_open(&port, calls, services, globals, entry);
    eax = port_u32(&port, entry->eax, 0x174);
    return port_return(&port, eax, entry->edx);
}

/* Original 0x4b4fa0: object set pair. */
uint32_t vertrix_port_object_set_pair_4b4fa0(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    port_set32(&port, entry->eax, 0x188, entry->edx);
    port_set32(&port, entry->eax, 0x18c, entry->ebx);
    return port_return(&port, entry->eax, entry->edx);
}

/* Original 0x4b6530: Clear the word +0x17a and store dl at +0x178. */
uint32_t vertrix_port_timer_reset_4b6530(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    port_set16(&port, entry->eax, 0x17a, 0);
    port_set8(&port, entry->eax, 0x178, entry->edx);
    return port_return(&port, entry->eax, entry->edx);
}

/* Original 0x4b6540: object set word. */
uint32_t vertrix_port_object_set_word_4b6540(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    port_set16(&port, entry->eax, 0x17a, entry->edx);
    return port_return(&port, entry->eax, entry->edx);
}

/* Original 0x4b6550: object set word. */
uint32_t vertrix_port_object_set_word_4b6550(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    port_set16(&port, entry->eax, 0x17c, entry->edx);
    return port_return(&port, entry->eax, entry->edx);
}

/* Original 0x4b6590: The word +0x17c in ax. */
uint32_t vertrix_port_object_word_4b6590(PORT_SIGNATURE)
{
    Port port;
    uint32_t eax;
    port_open(&port, calls, services, globals, entry);
    eax = (entry->eax & 0xffff0000u) | port_u16(&port, entry->eax, 0x17c);
    return port_return(&port, eax, entry->edx);
}

/* Original 0x4b65a0: The word +0x17a in ax. */
uint32_t vertrix_port_object_word_4b65a0(PORT_SIGNATURE)
{
    Port port;
    uint32_t eax;
    port_open(&port, calls, services, globals, entry);
    eax = (entry->eax & 0xffff0000u) | port_u16(&port, entry->eax, 0x17a);
    return port_return(&port, eax, entry->edx);
}

/* Original 0x4b65b0: object set dword. */
uint32_t vertrix_port_object_set_dword_4b65b0(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    port_set32(&port, entry->eax, 0x174, 1);
    return port_return(&port, entry->eax, entry->edx);
}

/* Original 0x4b9c10: Set the dword +0x24 of the object +0x18; that object. */
uint32_t vertrix_port_object_arm_child_24_4b9c10(PORT_SIGNATURE)
{
    Port port;
    uint32_t eax;
    port_open(&port, calls, services, globals, entry);
    eax = port_u32(&port, entry->eax, 0x18);
    port_set32(&port, eax, 0x24, 1);
    return port_return(&port, eax, entry->edx);
}

/* Original 0x4bce90: Point the object +0x1b4 at the handler 0x4bcea0; that object. */
uint32_t vertrix_port_object_set_handler_4bce90(PORT_SIGNATURE)
{
    Port port;
    uint32_t eax;
    port_open(&port, calls, services, globals, entry);
    eax = port_u32(&port, entry->eax, 0x1b4);
    port_set32(&port, eax, 0, 0x4bcea0);
    return port_return(&port, eax, entry->edx);
}

/* Original 0x4c1d20: Clear the dword +0x24 of the child +0x1c4 and copy +0x74 to its +0x2c; the
 * value copied. */
uint32_t vertrix_port_object_child_reset_4c1d20(PORT_SIGNATURE)
{
    Port port;
    uint32_t eax;
    uint32_t edx;
    port_open(&port, calls, services, globals, entry);
    edx = port_u32(&port, entry->eax, 0x1c4);
    port_set32(&port, edx, 0x24, 0);
    eax = port_u32(&port, entry->eax, 0x74);
    port_set32(&port, edx, 0x2c, eax);
    edx = entry->edx;
    return port_return(&port, eax, edx);
}

/* Original 0x4c35f0: Copy +0x138 and +0x74 to the child (+0x1c4) at +0x5c and +0x60; the second
 * value. */
uint32_t vertrix_port_object_child_copy_4c35f0(PORT_SIGNATURE)
{
    Port port;
    uint32_t eax;
    uint32_t edx;
    port_open(&port, calls, services, globals, entry);
    edx = port_u32(&port, entry->eax, 0x1c4);
    port_set32(&port, edx, 0x5c, port_u32(&port, entry->eax, 0x138));
    eax = port_u32(&port, entry->eax, 0x74);
    port_set32(&port, edx, 0x60, eax);
    edx = entry->edx;
    return port_return(&port, eax, edx);
}

/* Original 0x4c3760: store ebx at ecx. */
uint32_t vertrix_port_store_ebx_at_ecx_4c3760(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    port_set32(&port, entry->ecx, 0, entry->ebx);
    return port_return(&port, entry->eax, entry->edx);
}

/* Original 0x4c3770: clear at ecx. */
uint32_t vertrix_port_clear_at_ecx_4c3770(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    port_set32(&port, entry->ecx, 0, 0);
    return port_return(&port, entry->eax, entry->edx);
}

/* Original 0x4c3f80: Clear the dwords +0x6c and +0x14 of the object at [eax]; that object. */
uint32_t vertrix_port_object_clear_6c_14_4c3f80(PORT_SIGNATURE)
{
    Port port;
    uint32_t eax;
    port_open(&port, calls, services, globals, entry);
    port_set32(&port, port_u32(&port, entry->eax, 0), 0x6c, 0);
    eax = port_u32(&port, entry->eax, 0);
    port_set32(&port, eax, 0x14, 0);
    return port_return(&port, eax, entry->edx);
}

/* Original 0x4c5bf0: return ebx. */
uint32_t vertrix_port_return_ebx_4c5bf0(PORT_SIGNATURE)
{
    Port port;
    uint32_t eax;
    port_open(&port, calls, services, globals, entry);
    eax = entry->ebx;
    return port_return(&port, eax, entry->edx);
}

/* Original 0x4c9690: Set the dword +0x1c of the object +0x1cc; that object. */
uint32_t vertrix_port_object_arm_child_1c_4c9690(PORT_SIGNATURE)
{
    Port port;
    uint32_t eax;
    port_open(&port, calls, services, globals, entry);
    eax = port_u32(&port, entry->eax, 0x1cc);
    port_set32(&port, eax, 0x1c, 1);
    return port_return(&port, eax, entry->edx);
}

/* Original 0x4d5350: object dword. */
uint32_t vertrix_port_object_dword_4d5350(PORT_SIGNATURE)
{
    Port port;
    uint32_t eax;
    port_open(&port, calls, services, globals, entry);
    eax = port_u32(&port, entry->eax, 0x98);
    return port_return(&port, eax, entry->edx);
}

/* Original 0x4d7440: Field +0xc8 of the class at [eax]. */
uint32_t vertrix_port_object_class_c8_4d7440(PORT_SIGNATURE)
{
    Port port;
    uint32_t eax;
    port_open(&port, calls, services, globals, entry);
    eax = port_u32(&port, port_u32(&port, entry->eax, 0), 0xc8);
    return port_return(&port, eax, entry->edx);
}

/* Original 0x4d7450: Field +0xcc of the class at [eax]. */
uint32_t vertrix_port_object_class_cc_4d7450(PORT_SIGNATURE)
{
    Port port;
    uint32_t eax;
    port_open(&port, calls, services, globals, entry);
    eax = port_u32(&port, port_u32(&port, entry->eax, 0), 0xcc);
    return port_return(&port, eax, entry->edx);
}

/* Original 0x4e36c4: Store +8 at +0x20 of the record at [+4]; edx is left that record. */
uint32_t vertrix_port_rtl_store_frame_20_4e36c4(PORT_SIGNATURE)
{
    Port port;
    uint32_t edx;
    port_open(&port, calls, services, globals, entry);
    edx = port_u32(&port, port_u32(&port, entry->eax, 4), 0);
    port_set32(&port, edx, 0x20, port_u32(&port, entry->eax, 8));
    return port_return(&port, entry->eax, edx);
}

/* Original 0x4e5700: rtl clear pair 8. */
uint32_t vertrix_port_rtl_clear_pair_8_4e5700(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    port_set32(&port, entry->eax, 8, 0);
    port_set32(&port, entry->eax, 0xc, 0);
    return port_return(&port, entry->eax, entry->edx);
}

/* Original 0x4e6bff: Bit edx of the bit set at eax, by the mask table at 0x509810: al the masked
 * byte, eax the byte index above it and edx the masked byte. */
uint32_t vertrix_port_rtl_bit_test_4e6bff(PORT_SIGNATURE)
{
    Port port;
    uint32_t eax;
    uint32_t edx;
    port_open(&port, calls, services, globals, entry);
    edx = port_u8(&port, entry->edx & 7, 0x509810) & port_u8(&port, entry->eax, entry->edx >> 3);
    eax = ((entry->edx >> 3) & 0xffffff00u) | edx;
    return port_return(&port, eax, edx);
}

/* Original 0x4e6c1d: Clear bit edx of the bit set at eax by the mask table at 0x509818; edx is left
 * the mask. */
uint32_t vertrix_port_rtl_bit_clear_4e6c1d(PORT_SIGNATURE)
{
    Port port;
    uint32_t edx;
    port_open(&port, calls, services, globals, entry);
    edx = port_u8(&port, entry->edx & 7, 0x509818);
    port_set8(&port, entry->eax, entry->edx >> 3,
              port_u8(&port, entry->eax, entry->edx >> 3) & edx);
    return port_return(&port, entry->eax, edx);
}

/* Original 0x4ebcd0: Clear bit 4 of the byte +0xc and +4, and point +0 at the dword +8 of the
 * record +8. */
uint32_t vertrix_port_rtl_record_reset_4ebcd0(PORT_SIGNATURE)
{
    Port port;
    uint32_t edx;
    port_open(&port, calls, services, globals, entry);
    port_set8(&port, entry->eax, 0xc, port_u8(&port, entry->eax, 0xc) & 0xef);
    edx = port_u32(&port, port_u32(&port, entry->eax, 8), 8);
    port_set32(&port, entry->eax, 4, 0);
    port_set32(&port, entry->eax, 0, edx);
    edx = entry->edx;
    return port_return(&port, entry->eax, edx);
}

/* Original 0x4ec640: The size word before a heap block (its low bit cleared) less 4. */
uint32_t vertrix_port_rtl_block_header_4ec640(PORT_SIGNATURE)
{
    Port port;
    uint32_t eax;
    port_open(&port, calls, services, globals, entry);
    eax = (port_u32(&port, entry->eax - 4, 0) & 0xfffffffeu) - 4;
    return port_return(&port, eax, entry->edx);
}
