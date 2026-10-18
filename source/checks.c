#include "checks.h"

/* Small routines with a test or a short loop. */

/* A call handing the callee the caller's esi, edi and ebp unchanged. */
static uint32_t forward(Port *port, const LiftEntry *entry, uint32_t target, uint32_t eax,
                        uint32_t edx, uint32_t ebx, uint32_t ecx)
{
    return port_call_with(port, target, eax, edx, ebx, ecx, entry->esi, entry->edi, entry->ebp);
}

/* The same with esi given. */
static uint32_t forward_esi(Port *port, const LiftEntry *entry, uint32_t target, uint32_t eax,
                            uint32_t edx, uint32_t ebx, uint32_t ecx, uint32_t esi)
{
    return port_call_with(port, target, eax, edx, ebx, ecx, esi, entry->edi, entry->ebp);
}

/* The same with stack arguments, the nearest to the stack pointer first. */
static uint32_t forward_stack(Port *port, const LiftEntry *entry, uint32_t target, uint32_t eax,
                              uint32_t edx, uint32_t ebx, uint32_t ecx, uint32_t esi,
                              const uint32_t *stack, unsigned count)
{
    return port_call_registers(port, target, eax, edx, ebx, ecx, esi, entry->edi, entry->ebp, stack,
                               count);
}

/* Original 0x40c1c0: open the object of 0x4ebb78 (edx 0x50c808) and keep it at 0x52f90c; 0, or 10
 * when it failed. */
uint32_t vertrix_port_global_open_40c1c0(PORT_SIGNATURE)
{
    Port port;
    uint32_t object;
    port_open(&port, calls, services, globals, entry);
    object = forward(&port, entry, 0x4ebb78, entry->eax, 0x50c808, entry->ebx, entry->ecx);
    port_set32(&port, 0, 0x52f90c, object);
    return port_return(&port, object != 0 ? 0 : 0xa, entry->edx);
}

/* Original 0x40c970: whether the object is missing or its dword +4 is clear. */
uint32_t vertrix_port_object_missing_40c970(PORT_SIGNATURE)
{
    Port port;
    uint32_t missing;
    port_open(&port, calls, services, globals, entry);
    missing = entry->eax == 0 || port_u32(&port, entry->eax, 4) == 0;
    return port_return(&port, missing, entry->edx);
}

/* The seven calls of 0x415330 and 0x45f0a0: the callee with eax and ebx the object, edx the step
 * (0 to 6) and ecx one more. */
static uint32_t seven_calls(Port *port, const LiftEntry *entry, uint32_t target)
{
    uint32_t result = entry->eax;
    uint32_t step;
    for (step = 0; step < 7; step++)
    {
        result = forward(port, entry, target, entry->eax, step, entry->eax, step + 1);
    }
    return result;
}

/* Original 0x415330: 0x415350 for each of the seven steps. */
uint32_t vertrix_port_seven_calls_415330(PORT_SIGNATURE)
{
    Port port;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    result = seven_calls(&port, entry, 0x415350);
    return port_return(&port, result, entry->edx);
}

/* Original 0x45f0a0: 0x45f0c0 for each of the seven steps, then 0x45f1e0. */
uint32_t vertrix_port_seven_steps_45f0a0(PORT_SIGNATURE)
{
    Port port;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    result = seven_calls(&port, entry, 0x45f0c0);
    result = forward(&port, entry, 0x45f1e0, result, vertrix_lift_edx, entry->eax, 7);
    return port_return(&port, result, entry->edx);
}

/* Original 0x45f1e0: the seven bytes at 0x53bcc8 set to their own index. */
uint32_t vertrix_port_table_identity_cells_45f1e0(PORT_SIGNATURE)
{
    Port port;
    uint32_t index;
    port_open(&port, calls, services, globals, entry);
    for (index = 0; index < 7; index++)
    {
        port_set8(&port, index, 0x53bcc8, index);
    }
    return port_return(&port, index, entry->edx);
}

/* Original 0x415530: when [0x532b40] is 1, clear the pair at 0x532b44. */
uint32_t vertrix_port_global_reset_pair_415530(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    if (port_u32(&port, 0, 0x532b40) == 1)
    {
        port_set32(&port, 0, 0x532b48, 0);
        port_set32(&port, 0, 0x532b44, 0);
    }
    return port_return(&port, entry->eax, entry->edx);
}

/* Original 0x415b10: clear the 18 dwords from 0x5344a4 and from 0x5344f0. */
uint32_t vertrix_port_global_clear_tables_415b10(PORT_SIGNATURE)
{
    Port port;
    uint32_t offset;
    port_open(&port, calls, services, globals, entry);
    for (offset = 4; offset <= 0x48; offset += 4)
    {
        port_set32(&port, offset, 0x5344a0, 0);
        port_set32(&port, offset, 0x5344ec, 0);
    }
    return port_return(&port, 0x4c, entry->edx);
}

/* Original 0x415eb0: the value (ebx table) of the entry 0x415e40 finds (ecx names), 0 when none. */
uint32_t vertrix_port_table_value_matching_415eb0(PORT_SIGNATURE)
{
    Port port;
    uint32_t index;
    port_open(&port, calls, services, globals, entry);
    index = forward_esi(&port, entry, 0x415e40, entry->eax, entry->edx, entry->ecx, entry->ecx,
                        entry->ebx);
    index = index == 0xffffffff ? 0 : port_u32(&port, entry->ebx, index * 4);
    return port_return(&port, index, vertrix_lift_edx);
}

/* Original 0x415ed0: the value (edx table) of the entry 0x415e80 finds, 0 when none. */
uint32_t vertrix_port_table_value_equal_415ed0(PORT_SIGNATURE)
{
    Port port;
    uint32_t index;
    port_open(&port, calls, services, globals, entry);
    index = forward_esi(&port, entry, 0x415e80, entry->eax, entry->ebx, entry->ecx, entry->ecx,
                        entry->edx);
    index = index == 0xffffffff ? 0 : port_u32(&port, entry->edx, index * 4);
    return port_return(&port, index, vertrix_lift_edx);
}

/* Original 0x417790: print the score (at most 99999999) into the text at edx by the format at
 * 0x50d672 (0x4cdfb0). */
uint32_t vertrix_port_score_text_417790(PORT_SIGNATURE)
{
    Port port;
    uint32_t score = entry->eax;
    uint32_t pushed[3];
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    if (score > 0x5f5e0ff)
    {
        score = 0x5f5e0ff;
    }
    pushed[0] = entry->edx;
    pushed[1] = 0x50d672;
    pushed[2] = score;
    result = forward_stack(&port, entry, 0x4cdfb0, score, entry->edx, entry->ebx, entry->ecx,
                           entry->esi, pushed, 3);
    return port_return(&port, result, vertrix_lift_edx);
}

/* Original 0x418150: 1, 0 or -1 as eax is above, equal to or below edx (unsigned). */
uint32_t vertrix_port_compare_unsigned_418150(PORT_SIGNATURE)
{
    Port port;
    uint32_t order = 0xffffffff;
    port_open(&port, calls, services, globals, entry);
    if (entry->eax > entry->edx)
    {
        order = 1;
    }
    else if (entry->eax == entry->edx)
    {
        order = 0;
    }
    return port_return(&port, order, entry->edx);
}

/* Original 0x425de0: the seven slots set to -1; eax is left past them. */
uint32_t vertrix_port_object_reset_slots_425de0(PORT_SIGNATURE)
{
    Port port;
    uint32_t slot;
    port_open(&port, calls, services, globals, entry);
    for (slot = 0; slot < 7; slot++)
    {
        port_set32(&port, entry->eax, slot * 4, 0xffffffff);
    }
    return port_return(&port, entry->eax + 0x1c, entry->edx);
}

/* Original 0x425e00: how many of the seven slots are not -1. */
uint32_t vertrix_port_table_used_count_425e00(PORT_SIGNATURE)
{
    Port port;
    uint32_t slot;
    uint32_t used = 0;
    port_open(&port, calls, services, globals, entry);
    for (slot = 0; slot < 7; slot++)
    {
        if (port_u32(&port, entry->eax, slot * 4) != 0xffffffff)
        {
            used++;
        }
    }
    return port_return(&port, used, entry->edx);
}

/* The calls on the board's piece (+0xa60) when there is one. */
static uint32_t board_piece_call(PORT_SIGNATURE, uint32_t target)
{
    Port port;
    uint32_t piece;
    uint32_t result = entry->eax;
    port_open(&port, calls, services, globals, entry);
    piece = port_u32(&port, entry->eax, 0xa60);
    if (piece != 0)
    {
        result = forward(&port, entry, target, piece, piece, entry->ebx, entry->ecx);
    }
    return port_return(&port, result, entry->edx);
}

/* Original 0x42eba0: release the piece's children (0x42a4a0). */
uint32_t vertrix_port_board_release_piece_children_42eba0(PORT_SIGNATURE)
{
    return board_piece_call(calls, services, globals, entry, 0x42a4a0);
}

/* Original 0x431180: 0x42a8b0 on the piece. */
uint32_t vertrix_port_board_piece_call_431180(PORT_SIGNATURE)
{
    return board_piece_call(calls, services, globals, entry, 0x42a8b0);
}

/* Original 0x4311a0: 0x42a8e0 on the piece. */
uint32_t vertrix_port_board_piece_call_4311a0(PORT_SIGNATURE)
{
    return board_piece_call(calls, services, globals, entry, 0x42a8e0);
}

/* The byte fills of the player: dl into `count` bytes from +first; eax is left the object plus the
 * count. */
static uint32_t fill_bytes(PORT_SIGNATURE, uint32_t first, uint32_t count)
{
    Port port;
    uint32_t index;
    port_open(&port, calls, services, globals, entry);
    for (index = 0; index < count; index++)
    {
        port_set8(&port, entry->eax, first + index, entry->edx);
    }
    return port_return(&port, entry->eax + count, entry->edx);
}

/* Original 0x42ef60: dl into the five bytes from +0x99c. */
uint32_t vertrix_port_player_fill_bytes_42ef60(PORT_SIGNATURE)
{
    return fill_bytes(calls, services, globals, entry, 0x99c, 5);
}

/* Original 0x42ef80: dl into the five bytes from +0x9a1. */
uint32_t vertrix_port_player_fill_bytes_42ef80(PORT_SIGNATURE)
{
    return fill_bytes(calls, services, globals, entry, 0x9a1, 5);
}

/* Original 0x42f7d0: dl into the 13 bytes from +0x9a6. */
uint32_t vertrix_port_player_fill_bytes_42f7d0(PORT_SIGNATURE)
{
    return fill_bytes(calls, services, globals, entry, 0x9a6, 13);
}

/* Original 0x42f7f0: dl into the 13 bytes from +0x9b3. */
uint32_t vertrix_port_player_fill_bytes_42f7f0(PORT_SIGNATURE)
{
    return fill_bytes(calls, services, globals, entry, 0x9b3, 13);
}

/* Original 0x42f810: dl into the 13 bytes from +0x9c0. */
uint32_t vertrix_port_player_fill_bytes_42f810(PORT_SIGNATURE)
{
    return fill_bytes(calls, services, globals, entry, 0x9c0, 13);
}

/* Original 0x42f830: dl into the 13 bytes from +0x9cd. */
uint32_t vertrix_port_player_fill_bytes_42f830(PORT_SIGNATURE)
{
    return fill_bytes(calls, services, globals, entry, 0x9cd, 13);
}

/* Original 0x43bd60: whether the partner (+0x3b0) is free: its byte +0x4cc neither 1 nor 4. */
uint32_t vertrix_port_player_partner_free_43bd60(PORT_SIGNATURE)
{
    Port port;
    uint32_t state;
    port_open(&port, calls, services, globals, entry);
    state = port_u8(&port, port_u32(&port, entry->eax, 0x3b0), 0x4cc);
    return port_return(&port, state != 1 && state != 4, entry->edx);
}

/* The mode groups: whether the mode +0x4c8 is one of three from `first` (the miss returns through
 * 0x43bd74). */
static uint32_t mode_in_group(PORT_SIGNATURE, uint32_t first)
{
    Port port;
    uint32_t mode;
    port_open(&port, calls, services, globals, entry);
    mode = port_u32(&port, entry->eax, 0x4c8);
    return port_return(&port, mode >= first && mode <= first + 2, entry->edx);
}

/* Original 0x43d3b0: whether the mode is 0x25 to 0x27. */
uint32_t vertrix_port_player_mode_in_group_a_43d3b0(PORT_SIGNATURE)
{
    return mode_in_group(calls, services, globals, entry, 0x25);
}

/* Original 0x43d3d0: whether the mode is 0x32 to 0x34. */
uint32_t vertrix_port_player_mode_in_group_b_43d3d0(PORT_SIGNATURE)
{
    return mode_in_group(calls, services, globals, entry, 0x32);
}

/* Original 0x448160: when [0x532c40] is 1, 0x48c4a0 on 0x5bb254. */
uint32_t vertrix_port_when_flag_48c4a0_448160(PORT_SIGNATURE)
{
    Port port;
    uint32_t result = entry->eax;
    uint32_t edx = entry->edx;
    port_open(&port, calls, services, globals, entry);
    if (port_u32(&port, 0, 0x532c40) == 1)
    {
        result = forward(&port, entry, 0x48c4a0, 0x5bb254, entry->edx, entry->ebx, entry->ecx);
        edx = vertrix_lift_edx;
    }
    return port_return(&port, result, edx);
}

/* Original 0x450f60: when [0x532a40] is 1, enter the handler 0x450ff0 (0x4ac8f0). */
uint32_t vertrix_port_when_flag_enter_450f60(PORT_SIGNATURE)
{
    Port port;
    uint32_t result = entry->eax;
    port_open(&port, calls, services, globals, entry);
    if (port_u32(&port, 0, 0x532a40) == 1)
    {
        result = forward(&port, entry, 0x4ac8f0, entry->eax, 0x450ff0, entry->ebx, entry->ecx);
    }
    return port_return(&port, result, entry->edx);
}

/* Original 0x45e670: release the table 0x544d60, or 0x544d44 when eax is 0 (0x4874f0). */
uint32_t vertrix_port_table_release_by_flag_45e670(PORT_SIGNATURE)
{
    Port port;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    result = forward(&port, entry, 0x4874f0, entry->eax != 0 ? 0x544d60 : 0x544d44, entry->edx,
                     entry->ebx, entry->ecx);
    return port_return(&port, result, vertrix_lift_edx);
}

/* The table runs: release each 0x1c-byte table from `first` to `end` (0x4874f0). */
static uint32_t release_run(PORT_SIGNATURE, uint32_t first, uint32_t end)
{
    Port port;
    uint32_t table;
    uint32_t result = entry->eax;
    port_open(&port, calls, services, globals, entry);
    for (table = first; table != end; table += 0x1c)
    {
        result = forward(&port, entry, 0x4874f0, table, table + 0x1c, entry->ebx, end);
    }
    return port_return(&port, result, entry->edx);
}

/* Original 0x45e830: the five tables from 0x546458. */
uint32_t vertrix_port_table_release_run_45e830(PORT_SIGNATURE)
{
    return release_run(calls, services, globals, entry, 0x546458, 0x546458 + 0x8c);
}

/* Original 0x45e8f0: the 19 tables from 0x544d7c. */
uint32_t vertrix_port_table_release_run_45e8f0(PORT_SIGNATURE)
{
    return release_run(calls, services, globals, entry, 0x544d7c, 0x544d7c + 0x214);
}

/* Original 0x472d90: method +4 of the object at [0x546794] (class +0x158) when there is one. */
uint32_t vertrix_port_global_object_method_472d90(PORT_SIGNATURE)
{
    Port port;
    uint32_t object;
    uint32_t result = entry->eax;
    port_open(&port, calls, services, globals, entry);
    object = port_u32(&port, 0, 0x546794);
    if (object != 0)
    {
        result = forward(&port, entry, port_u32(&port, port_u32(&port, object, 0x158), 4), object,
                         port_u32(&port, object, 0x158), entry->ebx, entry->ecx);
    }
    return port_return(&port, result, entry->edx);
}

/* Original 0x473610: when edx is 1, 0x476720 on the point list 0x54d640 with ax. */
uint32_t vertrix_port_point_list_when_one_473610(PORT_SIGNATURE)
{
    Port port;
    uint32_t result = entry->eax;
    uint32_t edx = entry->edx;
    port_open(&port, calls, services, globals, entry);
    if (entry->edx == 1)
    {
        result =
            forward(&port, entry, 0x476720, 0x54d640, entry->eax & 0xffff, entry->ebx, entry->ecx);
        edx = vertrix_lift_edx;
    }
    return port_return(&port, result, edx);
}

/* Original 0x474540: when the dword at ebx reaches 100, clear it and call 0x489170 with ebx 1. */
uint32_t vertrix_port_counter_wrap_474540(PORT_SIGNATURE)
{
    Port port;
    uint32_t result = entry->eax;
    uint32_t edx = entry->edx;
    port_open(&port, calls, services, globals, entry);
    if (port_u32(&port, entry->ebx, 0) == 0x64)
    {
        port_set32(&port, entry->ebx, 0, 0);
        result = forward(&port, entry, 0x489170, entry->eax, entry->edx, 1, 0x64);
        edx = vertrix_lift_edx;
    }
    return port_return(&port, result, edx);
}

/* Original 0x475e10: the dword +0x44 divided by +0x48 (by 1 when that is 0). */
uint32_t vertrix_port_progress_quotient_475e10(PORT_SIGNATURE)
{
    Port port;
    uint32_t divisor;
    port_open(&port, calls, services, globals, entry);
    divisor = port_u32(&port, entry->eax, 0x48);
    if (divisor == 0)
    {
        divisor = 1;
    }
    return port_return(&port, port_u32(&port, entry->eax, 0x44) / divisor, entry->edx);
}

/* Original 0x4788f0: when [0x5589e0] is 1, 0x40aae0 with ecx 0, then clear the flag. */
uint32_t vertrix_port_when_flag_clear_4788f0(PORT_SIGNATURE)
{
    Port port;
    uint32_t result = entry->eax;
    uint32_t edx = entry->edx;
    port_open(&port, calls, services, globals, entry);
    if (port_u32(&port, 0, 0x5589e0) == 1)
    {
        result = forward(&port, entry, 0x40aae0, entry->eax, entry->edx, entry->ebx, 0);
        edx = vertrix_lift_edx;
        port_set32(&port, 0, 0x5589e0, 0);
    }
    return port_return(&port, result, edx);
}

/* Original 0x478bd0: when [0x5589d4] is 1, 0x40eea0 with eax and edx 0. */
uint32_t vertrix_port_when_flag_call_478bd0(PORT_SIGNATURE)
{
    Port port;
    uint32_t result = entry->eax;
    port_open(&port, calls, services, globals, entry);
    if (port_u32(&port, 0, 0x5589d4) == 1)
    {
        result = forward(&port, entry, 0x40eea0, 0, 0, entry->ebx, entry->ecx);
    }
    return port_return(&port, result, entry->edx);
}

/* Original 0x47ecd0: when the dword +4 of edx is the object's +0x38, append the text 0x50ee0b to
 * its list +0x40 (0x4ca370); 0. */
uint32_t vertrix_port_object_match_append_47ecd0(PORT_SIGNATURE)
{
    Port port;
    uint32_t edx;
    port_open(&port, calls, services, globals, entry);
    edx = port_u32(&port, entry->edx, 4);
    if (edx == port_u32(&port, entry->eax, 0x38))
    {
        forward(&port, entry, 0x4ca370, entry->eax + 0x40, 0x50ee0b, entry->ebx, entry->ecx);
        edx = vertrix_lift_edx;
    }
    return port_return(&port, 0, edx);
}

/* Original 0x47ecf0: set the dword +0x30 when it is clear; 0. */
uint32_t vertrix_port_object_arm_30_47ecf0(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    if (port_u32(&port, entry->eax, 0x30) == 0)
    {
        port_set32(&port, entry->eax, 0x30, 1);
    }
    return port_return(&port, 0, entry->edx);
}

/* Original 0x47ed30: when the byte at edx is 1, method +0x1c of the object +0x1c8; whether it
 * was. */
uint32_t vertrix_port_object_handler_1c_47ed30(PORT_SIGNATURE)
{
    Port port;
    uint32_t handler;
    uint32_t edx = entry->edx;
    uint32_t called = 0;
    port_open(&port, calls, services, globals, entry);
    if (port_u8(&port, entry->edx, 0) == 1)
    {
        handler = port_u32(&port, entry->eax, 0x1c8);
        forward(&port, entry, port_u32(&port, handler, 0x1c), entry->eax, entry->edx, entry->ebx,
                handler);
        edx = vertrix_lift_edx;
        called = 1;
    }
    return port_return(&port, called, edx);
}

/* Original 0x47f190: member edx of the chain from +0xc (linked by +0x60), or 0; edx is left the
 * index reached. */
uint32_t vertrix_port_object_chain_at_47f190(PORT_SIGNATURE)
{
    Port port;
    uint32_t member;
    uint32_t index = 0;
    port_open(&port, calls, services, globals, entry);
    member = port_u32(&port, entry->eax, 0xc);
    while (member != 0 && index != entry->edx)
    {
        member = port_u32(&port, member, 0x60);
        index++;
    }
    return port_return(&port, member, index);
}

/* Original 0x47f260: the address +0x50 of member edx of the chain (0x47f190), or 0; edx is left
 * the member. */
uint32_t vertrix_port_object_chain_member_47f260(PORT_SIGNATURE)
{
    Port port;
    uint32_t member;
    port_open(&port, calls, services, globals, entry);
    member = forward(&port, entry, 0x47f190, entry->eax, entry->edx, entry->ebx, entry->ecx);
    return port_return(&port, member != 0 ? member + 0x50 : 0, member);
}

/* Original 0x482b30: 0x4b8170 unless eax is 0. */
uint32_t vertrix_port_call_unless_zero_482b30(PORT_SIGNATURE)
{
    Port port;
    uint32_t result = 0;
    uint32_t edx = entry->edx;
    port_open(&port, calls, services, globals, entry);
    if (entry->eax != 0)
    {
        result = forward(&port, entry, 0x4b8170, entry->eax, entry->edx, entry->ebx, entry->ecx);
        edx = vertrix_lift_edx;
    }
    return port_return(&port, result, edx);
}

/* Original 0x487060: method +0x48 of the object +0x68 with 2, again while it answers 0x8876021c
 * (still drawing). */
uint32_t vertrix_port_surface_wait_487060(PORT_SIGNATURE)
{
    Port port;
    uint32_t object;
    uint32_t pushed[2];
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    do
    {
        object = port_u32(&port, entry->eax, 0x68);
        pushed[0] = object;
        pushed[1] = 2;
        result = forward_stack(&port, entry, port_u32(&port, port_u32(&port, object, 0), 0x48),
                               object, port_u32(&port, object, 0), entry->eax, entry->ecx,
                               entry->esi, pushed, 2);
    } while (result == 0x8876021c);
    return port_return(&port, result, entry->edx);
}

/* Item edx of the list (+4 items, +8 count), or 0 past its end. */
static uint32_t list_item(PORT_SIGNATURE)
{
    Port port;
    uint32_t item = 0;
    port_open(&port, calls, services, globals, entry);
    if (entry->edx < port_u32(&port, entry->eax, 8))
    {
        item = port_u32(&port, port_u32(&port, entry->eax, 4), entry->edx * 4);
    }
    return port_return(&port, item, entry->edx);
}

/* Original 0x487a20. */
uint32_t vertrix_port_list_item_487a20(PORT_SIGNATURE)
{
    return list_item(calls, services, globals, entry);
}

/* Original 0x48d630. */
uint32_t vertrix_port_list_item_48d630(PORT_SIGNATURE)
{
    return list_item(calls, services, globals, entry);
}

/* The delegates: the callee with ebx the delegate +0x38 and ecx the caller's ebx, or 0 when there
 * is no delegate. */
static uint32_t delegate(PORT_SIGNATURE, uint32_t target)
{
    Port port;
    uint32_t object;
    uint32_t result = 0;
    uint32_t edx = entry->edx;
    port_open(&port, calls, services, globals, entry);
    object = port_u32(&port, entry->eax, 0x38);
    if (object != 0)
    {
        result = forward(&port, entry, target, entry->eax, entry->edx, object, entry->ebx);
        edx = vertrix_lift_edx;
    }
    return port_return(&port, result, edx);
}

/* Original 0x48c9b0: 0x47fa40 through the delegate. */
uint32_t vertrix_port_object_delegate_48c9b0(PORT_SIGNATURE)
{
    return delegate(calls, services, globals, entry, 0x47fa40);
}

/* Original 0x48c9d0: 0x47fa90 through the delegate. */
uint32_t vertrix_port_object_delegate_48c9d0(PORT_SIGNATURE)
{
    return delegate(calls, services, globals, entry, 0x47fa90);
}

/* Original 0x4ac1c0: clear the six dwords from 0x5bb714. */
uint32_t vertrix_port_clear_cells_4ac1c0(PORT_SIGNATURE)
{
    Port port;
    uint32_t offset;
    port_open(&port, calls, services, globals, entry);
    for (offset = 4; offset <= 0x18; offset += 4)
    {
        port_set32(&port, offset, 0x5bb710, 0);
    }
    return port_return(&port, 0x18, entry->edx);
}

/* Original 0x4ac590: the dword +0xbc times edx over +0xc0 (1 when that is 0), unsigned; edx is
 * left the remainder. */
uint32_t vertrix_port_actor_scaled_4ac590(PORT_SIGNATURE)
{
    Port port;
    uint32_t divisor;
    uint32_t product;
    port_open(&port, calls, services, globals, entry);
    divisor = port_u32(&port, entry->eax, 0xc0);
    if (divisor == 0)
    {
        divisor = 1;
    }
    product = port_u32(&port, entry->eax, 0xbc) * entry->edx;
    return port_return(&port, product / divisor, product % divisor);
}

/* Original 0x4b46e0: the row 0x4b6930 finds in the parent (+0x160) for the position edx plus 1,
 * or 0 when that is not positive. */
uint32_t vertrix_port_object_text_row_4b46e0(PORT_SIGNATURE)
{
    Port port;
    uint32_t position = entry->edx + 1;
    uint32_t result = 0;
    port_open(&port, calls, services, globals, entry);
    if ((int32_t)position > 0)
    {
        result = forward(&port, entry, 0x4b6930, port_u32(&port, entry->eax, 0x160), position,
                         entry->ebx, entry->eax);
        position = vertrix_lift_edx;
    }
    return port_return(&port, result, position);
}

/* The allocations of 0x4dba80 (size pushed) given a class when they succeed. */
static uint32_t allocate_class(PORT_SIGNATURE, uint32_t size, uint32_t class_address)
{
    Port port;
    uint32_t pushed[1];
    uint32_t block;
    port_open(&port, calls, services, globals, entry);
    pushed[0] = size;
    block = forward_stack(&port, entry, 0x4dba80, entry->eax, entry->edx, entry->ebx, entry->ecx,
                          entry->esi, pushed, 1);
    if (block != 0)
    {
        port_set32(&port, block, 0, class_address);
    }
    return port_return(&port, block, vertrix_lift_edx);
}

/* Original 0x4cc760: 0x30 bytes of the class 0x518ec4. */
uint32_t vertrix_port_allocate_518ec4_4cc760(PORT_SIGNATURE)
{
    return allocate_class(calls, services, globals, entry, 0x30, 0x518ec4);
}

/* Original 0x4cc780: 4 bytes of the class 0x518eb4. */
uint32_t vertrix_port_allocate_518eb4_4cc780(PORT_SIGNATURE)
{
    return allocate_class(calls, services, globals, entry, 4, 0x518eb4);
}

/* Original 0x4ccad0: method +0x2c of the object +0x78 when there is one. */
uint32_t vertrix_port_object_method_2c_4ccad0(PORT_SIGNATURE)
{
    Port port;
    uint32_t object;
    uint32_t result = entry->eax;
    uint32_t edx = entry->edx;
    port_open(&port, calls, services, globals, entry);
    object = port_u32(&port, entry->eax, 0x78);
    if (object != 0)
    {
        result = forward(&port, entry, port_u32(&port, port_u32(&port, object, 0), 0x2c), object,
                         entry->edx, entry->ebx, port_u32(&port, object, 0));
        edx = vertrix_lift_edx;
    }
    return port_return(&port, result, edx);
}

/* Original 0x4d04d0: the handler +4 of the record of 0x4ce760, when set, with edx and eax pushed;
 * 0. */
uint32_t vertrix_port_record_handler_4d04d0(PORT_SIGNATURE)
{
    Port port;
    uint32_t record;
    uint32_t pushed[2];
    uint32_t edx;
    port_open(&port, calls, services, globals, entry);
    record = forward_esi(&port, entry, 0x4ce760, entry->eax, entry->edx, entry->eax, entry->ecx,
                         entry->edx);
    edx = record;
    if (port_u32(&port, record, 4) != 0)
    {
        pushed[0] = entry->edx;
        pushed[1] = entry->eax;
        forward_stack(&port, entry, port_u32(&port, record, 4), record, record, entry->eax,
                      entry->ecx, entry->edx, pushed, 2);
        edx = vertrix_lift_edx;
    }
    return port_return(&port, 0, edx);
}

/* Original 0x4d0650: 0x4d1e80 with the dword +0xc of ebx and 0 pushed; when it fails, 0x4cf850. */
uint32_t vertrix_port_check_or_fail_4d0650(PORT_SIGNATURE)
{
    Port port;
    uint32_t pushed[2];
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    pushed[0] = port_u32(&port, entry->ebx, 0xc);
    pushed[1] = 0;
    result = forward_stack(&port, entry, 0x4d1e80, entry->eax, entry->edx, entry->ebx, entry->ecx,
                           entry->eax, pushed, 2);
    if (result == 0)
    {
        result = forward_esi(&port, entry, 0x4cf850, entry->eax, vertrix_lift_edx, entry->ebx,
                             entry->ecx, entry->eax);
    }
    return port_return(&port, result, vertrix_lift_edx);
}

/* The checks of 0x4d2420 and 0x4d2440: 0x4d1e50 on ecx (edx 0) when it is set, and 0x4cf850 on eax
 * when that fails or ecx is 0. */
static uint32_t check_or_fail(PORT_SIGNATURE)
{
    Port port;
    uint32_t result = 0;
    uint32_t edx = entry->edx;
    port_open(&port, calls, services, globals, entry);
    if (entry->ecx != 0)
    {
        result =
            forward_esi(&port, entry, 0x4d1e50, entry->ecx, 0, entry->ebx, entry->ecx, entry->eax);
        edx = vertrix_lift_edx;
    }
    if (result == 0)
    {
        result = forward_esi(&port, entry, 0x4cf850, entry->eax, edx, entry->ebx, entry->ecx,
                             entry->eax);
        edx = vertrix_lift_edx;
    }
    return port_return(&port, result, edx);
}

/* Original 0x4d2420. */
uint32_t vertrix_port_check_or_fail_4d2420(PORT_SIGNATURE)
{
    return check_or_fail(calls, services, globals, entry);
}

/* Original 0x4d2440. */
uint32_t vertrix_port_check_or_fail_4d2440(PORT_SIGNATURE)
{
    return check_or_fail(calls, services, globals, entry);
}

/* Original 0x4d3020: edx when 0x4d3010 (eax and edx swapped) accepts it, else 0. */
uint32_t vertrix_port_rtl_swapped_call_4d3020(PORT_SIGNATURE)
{
    Port port;
    uint32_t result = 0;
    uint32_t edx = 0;
    port_open(&port, calls, services, globals, entry);
    if (entry->edx != 0)
    {
        result = forward(&port, entry, 0x4d3010, entry->edx, entry->eax, entry->ebx, entry->edx);
        edx = vertrix_lift_edx;
        result = result != 0 ? entry->edx : 0;
    }
    return port_return(&port, result, edx);
}

/* Original 0x4d3120: whether edx is in the class chain from eax (linked by +0x10). */
uint32_t vertrix_port_rtl_class_chain_contains_4d3120(PORT_SIGNATURE)
{
    Port port;
    uint32_t link;
    port_open(&port, calls, services, globals, entry);
    for (link = entry->eax; link != 0; link = port_u32(&port, link, 0x10))
    {
        if (link == entry->edx)
        {
            return port_return(&port, 1, entry->edx);
        }
    }
    return port_return(&port, 0, entry->edx);
}

/* Original 0x4d41a0: 0x4cf850, then method +0x70 of the object +0x68 when there is one. */
uint32_t vertrix_port_check_then_method_70_4d41a0(PORT_SIGNATURE)
{
    Port port;
    uint32_t object;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    result = forward(&port, entry, 0x4cf850, entry->eax, entry->edx, entry->ebx, entry->eax);
    object = port_u32(&port, entry->eax, 0x68);
    if (object != 0)
    {
        result = forward(&port, entry, port_u32(&port, port_u32(&port, object, 0), 0x70), object,
                         vertrix_lift_edx, entry->ebx, port_u32(&port, object, 0));
    }
    return port_return(&port, result, vertrix_lift_edx);
}

/* Original 0x4d62e0: 0x4cf850, then method +0xcc with edx 1 unless its edx is already 1. */
uint32_t vertrix_port_check_then_method_cc_4d62e0(PORT_SIGNATURE)
{
    Port port;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    result = forward_esi(&port, entry, 0x4cf850, entry->eax, entry->edx, entry->ebx, entry->ecx,
                         entry->eax);
    if (vertrix_lift_edx != 1)
    {
        result = forward_esi(&port, entry, port_u32(&port, port_u32(&port, entry->eax, 0), 0xcc),
                             entry->eax, 1, entry->ebx, port_u32(&port, entry->eax, 0), entry->eax);
    }
    return port_return(&port, result, vertrix_lift_edx);
}

/* Original 0x4d63b0: the result of 0x4d1840, or the dword +0x6c of its edx when that is 0. */
uint32_t vertrix_port_value_or_field_4d63b0(PORT_SIGNATURE)
{
    Port port;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    result = forward(&port, entry, 0x4d1840, entry->eax, entry->eax, entry->ebx, entry->ecx);
    if (result == 0)
    {
        result = port_u32(&port, vertrix_lift_edx, 0x6c);
    }
    return port_return(&port, result, entry->edx);
}

/* Original 0x4d8580: the length of the wide string at eax. */
uint32_t vertrix_port_rtl_wide_length_4d8580(PORT_SIGNATURE)
{
    Port port;
    uint32_t end = entry->eax;
    port_open(&port, calls, services, globals, entry);
    if (port_u16(&port, end, 0) != 0)
    {
        do
        {
            end += 2;
        } while (port_u16(&port, end, 0) != 0);
    }
    return port_return(&port, (uint32_t)((int32_t)(end - entry->eax) >> 1), entry->edx);
}

/* Original 0x4d85a0: copy the wide string at edx to eax; edx is left past the source's end. */
uint32_t vertrix_port_rtl_wide_copy_4d85a0(PORT_SIGNATURE)
{
    Port port;
    uint32_t target = entry->eax;
    uint32_t source = entry->edx;
    uint32_t unit;
    port_open(&port, calls, services, globals, entry);
    do
    {
        unit = port_u16(&port, source, 0);
        source += 2;
        port_set16(&port, target, 0, unit);
        target += 2;
    } while (unit != 0);
    return port_return(&port, entry->eax, source);
}

/* Original 0x4dae4a: negate the double in edx:eax (flip the sign bit) unless it is zero. */
uint32_t vertrix_port_rtl_negate_double_4dae4a(PORT_SIGNATURE)
{
    Port port;
    uint32_t high = entry->edx;
    port_open(&port, calls, services, globals, entry);
    if (entry->edx != 0 || entry->eax != 0)
    {
        high ^= 0x80000000u;
    }
    return port_return(&port, entry->eax, high);
}

/* Original 0x4e0eaf: the record of the list +8 of the object at [eax] whose +0x20 is edx and +0x18
 * ebx, or 0. */
uint32_t vertrix_port_record_find_4e0eaf(PORT_SIGNATURE)
{
    Port port;
    uint32_t record;
    port_open(&port, calls, services, globals, entry);
    record = port_u32(&port, port_u32(&port, entry->eax, 0), 8);
    while (record != 0 && (entry->edx != port_u32(&port, record, 0x20) ||
                           entry->ebx != port_u32(&port, record, 0x18)))
    {
        record = port_u32(&port, record, 0);
    }
    return port_return(&port, record, entry->edx);
}

/* Original 0x4e6cd4: follow the import thunks (jmp [address], ff 25) from eax to the routine. */
uint32_t vertrix_port_thunk_target_4e6cd4(PORT_SIGNATURE)
{
    Port port;
    uint32_t code = entry->eax;
    port_open(&port, calls, services, globals, entry);
    while (port_u8(&port, code, 0) == 0xff && port_u8(&port, code, 1) == 0x25)
    {
        code = port_u32(&port, port_u32(&port, code, 2), 0);
    }
    return port_return(&port, code, entry->edx);
}

/* Original 0x4e7f0c: the digit eax as a lower-case hexadecimal character. */
uint32_t vertrix_port_hex_digit_4e7f0c(PORT_SIGNATURE)
{
    Port port;
    uint32_t digit = entry->eax + 0x30;
    port_open(&port, calls, services, globals, entry);
    if ((int32_t)digit > 0x39)
    {
        digit += 0x27;
    }
    return port_return(&port, digit, entry->edx);
}

/* Original 0x4e82f0: the character eax in lower case. */
uint32_t vertrix_port_lower_case_4e82f0(PORT_SIGNATURE)
{
    Port port;
    uint32_t character = entry->eax;
    port_open(&port, calls, services, globals, entry);
    if ((int32_t)character >= 0x41 && (int32_t)character <= 0x5a)
    {
        character += 0x20;
    }
    return port_return(&port, character, entry->edx);
}

/* Original 0x4e8310: the 26-byte record eax (0 to 3) at 0x505234, or 0. */
uint32_t vertrix_port_record_address_4e8310(PORT_SIGNATURE)
{
    Port port;
    uint32_t address = 0;
    port_open(&port, calls, services, globals, entry);
    if (entry->eax <= 3)
    {
        address = entry->eax * 26 + 0x505234;
    }
    return port_return(&port, address, entry->edx);
}

/* Original 0x4e8aa0: 0x4e8a58 when 0x4e8a7c returns its own edx, else 0. */
uint32_t vertrix_port_check_pair_4e8aa0(PORT_SIGNATURE)
{
    Port port;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    result = forward(&port, entry, 0x4e8a7c, entry->eax, entry->edx, entry->eax, entry->ecx);
    if (vertrix_lift_edx == result)
    {
        result =
            forward(&port, entry, 0x4e8a58, entry->eax, vertrix_lift_edx, entry->eax, entry->ecx);
    }
    else
    {
        result = 0;
    }
    return port_return(&port, result, vertrix_lift_edx);
}
