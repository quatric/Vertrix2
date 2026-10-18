#include "guards.h"

/* Board, piece and player routines guarded by a check, and short fills and counts. */

/* Bytes 1 to 13 of each of the five rows of 13 from `base` of the board set to `value`; eax
 * left past the last row. */
static uint32_t rows_fill(Port *port, uint32_t board, uint32_t base, uint32_t value)
{
    uint32_t row;
    uint32_t at = board;
    for (row = 0; row < 5; row++)
    {
        uint32_t end = board + row * 13 + 13;
        at = board + row * 13;
        do
        {
            at++;
            port_set8(port, at, base, value);
        } while (at != end);
    }
    return at;
}

/* Original 0x42f2e0: fill the five rows of 13 bytes from +0x19d with byte +0x58. */
uint32_t vertrix_port_board_fill_cells_42f2e0(PORT_SIGNATURE)
{
    Port port;
    uint32_t end;
    port_open(&port, calls, services, globals, entry);
    end = rows_fill(&port, entry->eax, 0x19c, port_u8(&port, entry->eax, 0x58));
    return port_return(&port, end, entry->edx);
}

/* Original 0x42f8b0: fill the five rows of 13 bytes from +0x15c with dl; edx left past the last
 * row. */
uint32_t vertrix_port_board_cell_values_fill_42f8b0(PORT_SIGNATURE)
{
    Port port;
    uint32_t end;
    port_open(&port, calls, services, globals, entry);
    end = rows_fill(&port, entry->eax, 0x15b, entry->edx & 0xff);
    return port_return(&port, end, end);
}

/* Original 0x42f8e0: the same from +0x19d. */
uint32_t vertrix_port_board_cell_values_fill_full_42f8e0(PORT_SIGNATURE)
{
    Port port;
    uint32_t end;
    port_open(&port, calls, services, globals, entry);
    end = rows_fill(&port, entry->eax, 0x19c, entry->edx & 0xff);
    return port_return(&port, end, end);
}

/* 0x4320c0 on the board, then `check`; when both give 1, the active piece (+0xa60) word at
 * `field` moved by `step`. Always 1. */
static uint32_t piece_move(PORT_SIGNATURE, uint32_t check, uint32_t field, uint32_t step)
{
    Port port;
    uint32_t board = entry->eax;
    uint32_t piece;
    port_open(&port, calls, services, globals, entry);
    if (port_forward(&port, entry, 0x4320c0, board, entry->edx, entry->ebx, board) != 1)
    {
        return port_return(&port, 1, vertrix_lift_edx);
    }
    if (port_forward(&port, entry, check, board, vertrix_lift_edx, entry->ebx, board) != 1)
    {
        return port_return(&port, 1, vertrix_lift_edx);
    }
    piece = port_u32(&port, board, 0xa60);
    port_set16(&port, piece, field, port_u16(&port, piece, field) + step);
    return port_return(&port, 1, piece);
}

/* Original 0x42f3d0: up by 24 (word +0x16) when 0x42efa0 allows it. */
uint32_t vertrix_port_board_piece_raise_42f3d0(PORT_SIGNATURE)
{
    return piece_move(calls, services, globals, entry, 0x42efa0, 0x16, 0xffe8);
}

/* Original 0x42f6e0: right by 24 (word +0xe) when 0x42f030 allows it. */
uint32_t vertrix_port_board_piece_shift_42f6e0(PORT_SIGNATURE)
{
    return piece_move(calls, services, globals, entry, 0x42f030, 0xe, 0x18);
}

/* Original 0x42f720: left by 24 when 0x42f120 allows it. */
uint32_t vertrix_port_board_piece_shift_42f720(PORT_SIGNATURE)
{
    return piece_move(calls, services, globals, entry, 0x42f120, 0xe, 0xffe8);
}

/* Original 0x42f410: up by 24 after 0x4320c0 alone (edx the board), the board the edx it leaves.
 * Always 1. */
uint32_t vertrix_port_board_piece_raise_always_42f410(PORT_SIGNATURE)
{
    Port port;
    uint32_t piece;
    port_open(&port, calls, services, globals, entry);
    if (port_forward(&port, entry, 0x4320c0, entry->eax, entry->eax, entry->ebx, entry->ecx) == 1)
    {
        piece = port_u32(&port, vertrix_lift_edx, 0xa60);
        port_set16(&port, piece, 0x16, port_u16(&port, piece, 0x16) - 0x18);
    }
    return port_return(&port, 1, entry->edx);
}

/* 0x4320c0 on the board, then `check`; when both give 1, store byte +0x58 at +0xa64 (al). */
static uint32_t piece_touch(PORT_SIGNATURE, uint32_t check)
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
    result = port_forward(&port, entry, check, board, vertrix_lift_edx, entry->ebx, board);
    if (result != 1)
    {
        return port_return(&port, result, vertrix_lift_edx);
    }
    value = port_u8(&port, board, 0x58);
    port_set8(&port, board, 0xa64, value);
    return port_return(&port, (result & 0xffffff00u) | value, vertrix_lift_edx);
}

/* Original 0x42f520: through 0x42f030. */
uint32_t vertrix_port_board_piece_store_touch_42f520(PORT_SIGNATURE)
{
    return piece_touch(calls, services, globals, entry, 0x42f030);
}

/* Original 0x42f550: through 0x42f120. */
uint32_t vertrix_port_board_piece_store_touch_42f550(PORT_SIGNATURE)
{
    return piece_touch(calls, services, globals, entry, 0x42f120);
}

/* Release the object at `field`: its first method (edx 2) and clear the field; nothing for
 * null. */
static uint32_t release_field(PORT_SIGNATURE, uint32_t field)
{
    Port port;
    uint32_t owner = entry->eax;
    uint32_t object;
    uint32_t methods;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    object = port_u32(&port, owner, field);
    if (object == 0)
    {
        return port_return(&port, owner, entry->edx);
    }
    methods = port_u32(&port, object, 0x158);
    result = port_forward(&port, entry, port_u32(&port, methods, 0), object, 2, methods, owner);
    port_set32(&port, owner, field, 0);
    return port_return(&port, result, entry->edx);
}

/* Original 0x42eb60: the active piece +0xa60. */
uint32_t vertrix_port_board_release_active_42eb60(PORT_SIGNATURE)
{
    return release_field(calls, services, globals, entry, 0xa60);
}

/* Original 0x430150: the extra object +0xce0. */
uint32_t vertrix_port_board_release_extra_430150(PORT_SIGNATURE)
{
    return release_field(calls, services, globals, entry, 0xce0);
}

/* With an active piece, `check` (ecx 0); when it gives 1 the piece word +0xe moved by `step`
 * (1); otherwise 0. */
static uint32_t piece_try_move(PORT_SIGNATURE, uint32_t check, uint32_t step)
{
    Port port;
    uint32_t board = entry->eax;
    uint32_t piece;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    piece = port_u32(&port, board, 0xa60);
    if (piece == 0)
    {
        return port_return(&port, 0, entry->edx);
    }
    result = port_forward(&port, entry, check, board, board, piece, 0);
    if (result != 1)
    {
        return port_return(&port, 0, entry->edx);
    }
    piece = port_u32(&port, vertrix_lift_edx, 0xa60);
    port_set16(&port, piece, 0xe, port_u16(&port, piece, 0xe) + step);
    return port_return(&port, result, entry->edx);
}

/* Original 0x431100: left by 24 when 0x4311c0 allows it. */
uint32_t vertrix_port_board_piece_try_left_431100(PORT_SIGNATURE)
{
    return piece_try_move(calls, services, globals, entry, 0x4311c0, 0xffe8);
}

/* Original 0x431140: right by 24 when 0x431280 allows it. */
uint32_t vertrix_port_board_piece_try_right_431140(PORT_SIGNATURE)
{
    return piece_try_move(calls, services, globals, entry, 0x431280, 0x18);
}

/* Original 0x4320d0: without an actor at +0xb70, allocate 0x174 bytes by 0x4ca000, construct
 * them by 0x42b5c0 when that worked, keep the result at +0xb70 and set it up by 0x42b6b0 (edx
 * the low byte the constructor leaves, sign extended). */
uint32_t vertrix_port_piece_actor_spawn_4320d0(PORT_SIGNATURE)
{
    Port port;
    uint32_t board = entry->eax;
    uint32_t actor;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    if (port_u32(&port, board, 0xb70) != 0)
    {
        return port_return(&port, board, entry->edx);
    }
    actor = port_forward(&port, entry, 0x4ca000, 0x174, entry->edx, entry->ebx, board);
    if (actor != 0)
    {
        actor = port_forward(&port, entry, 0x42b5c0, actor, vertrix_lift_edx, entry->ebx, board);
    }
    port_set32(&port, board, 0xb70, actor);
    result = port_forward(&port, entry, 0x42b6b0, actor, (uint32_t)(int8_t)vertrix_lift_edx,
                          entry->ebx, board);
    return port_return(&port, result, vertrix_lift_edx);
}

/* The count of the bytes equal to `value` in the five rows of 13 from +0xb94. */
static uint32_t markers_count(PORT_SIGNATURE, uint32_t value)
{
    Port port;
    uint32_t count = 0;
    uint32_t offset;
    port_open(&port, calls, services, globals, entry);
    for (offset = 0; offset < 5 * 13; offset++)
    {
        if (port_u8(&port, entry->eax + offset, 0xb94) == value)
        {
            count++;
        }
    }
    return port_return(&port, count, entry->edx);
}

/* Original 0x436030: of 1. */
uint32_t vertrix_port_board_marker_count_436030(PORT_SIGNATURE)
{
    return markers_count(calls, services, globals, entry, 1);
}

/* Original 0x436070: of 2. */
uint32_t vertrix_port_board_marker_count_436070(PORT_SIGNATURE)
{
    return markers_count(calls, services, globals, entry, 2);
}

/* Original 0x43a160: construct by 0x4abd70, set the class 0x514b94 at +0x158, clear the three
 * child dwords from +0x15c and set the three bytes from +0x168 to -1. */
uint32_t vertrix_port_piece_child_slots_init_43a160(PORT_SIGNATURE)
{
    Port port;
    uint32_t object;
    uint32_t slot;
    port_open(&port, calls, services, globals, entry);
    object = port_forward_esi(&port, entry, 0x4abd70, entry->eax, entry->edx, entry->ebx,
                              entry->ecx, entry->eax);
    port_set32(&port, object, 0x158, 0x514b94);
    for (slot = 0; slot < 3; slot++)
    {
        port_set32(&port, object + slot * 4, 0x15c, 0);
        port_set8(&port, object + slot, 0x168, 0xff);
    }
    return port_return(&port, object, entry->edx);
}

/* Original 0x43a2d0: the second method of each of the three children from +0x15c that are set
 * (ebx past the children). */
uint32_t vertrix_port_piece_children_update_43a2d0(PORT_SIGNATURE)
{
    Port port;
    uint32_t object = entry->eax;
    uint32_t end = object + 0xc;
    uint32_t at = object;
    uint32_t result = entry->eax;
    port_open(&port, calls, services, globals, entry);
    do
    {
        uint32_t child = port_u32(&port, at, 0x15c);
        if (child != 0)
        {
            uint32_t methods = port_u32(&port, child, 0x158);
            result =
                port_forward(&port, entry, port_u32(&port, methods, 4), child, at, end, methods);
            at = vertrix_lift_edx;
        }
        at += 4;
    } while (at != end);
    return port_return(&port, result, entry->edx);
}

/* Original 0x43a520: restore the children by 0x43a410 with the three signed bytes from +0x168
 * (edx, ebx, ecx), then set them to -1; eax left past them. */
uint32_t vertrix_port_piece_children_restore_and_clear_43a520(PORT_SIGNATURE)
{
    Port port;
    uint32_t object = entry->eax;
    uint32_t slot;
    port_open(&port, calls, services, globals, entry);
    port_forward_esi(&port, entry, 0x43a410, object,
                     (uint32_t)(int8_t)port_u8(&port, object, 0x168),
                     (uint32_t)(int8_t)port_u8(&port, object, 0x169),
                     (uint32_t)(int8_t)port_u8(&port, object, 0x16a), object);
    for (slot = 0; slot < 3; slot++)
    {
        port_set8(&port, object + slot, 0x168, 0xff);
    }
    return port_return(&port, object + 3, entry->edx);
}

/* Original 0x43abd0: for kind 1 or 2, 0x417350 or 0x417460 on the dword of slot edx at
 * 0x532d3c (edx the slot offset). */
uint32_t vertrix_port_slot_dispatch_43abd0(PORT_SIGNATURE)
{
    Port port;
    uint32_t offset = entry->edx << 2;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    if (entry->eax != 1 && entry->eax != 2)
    {
        return port_return(&port, entry->eax, offset);
    }
    result = port_forward(&port, entry, entry->eax == 1 ? 0x417350 : 0x417460,
                          port_u32(&port, offset, 0x532d3c), offset, entry->ebx, entry->ecx);
    return port_return(&port, result, vertrix_lift_edx);
}

/* Original 0x43b7c0: draw levels by 0x482750 (0x598d30, below 9) until one differs from the
 * player's +0x17c, then set it by 0x43b810. */
uint32_t vertrix_port_player_randomize_level_43b7c0(PORT_SIGNATURE)
{
    Port port;
    uint32_t player = entry->eax;
    uint32_t level;
    uint32_t drawn;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    level = port_u32(&port, player, 0x17c);
    do
    {
        drawn = port_forward_esi(&port, entry, 0x482750, 0x598d30, 0, 9, level, player);
    } while (drawn == level);
    result = port_forward_esi(&port, entry, 0x43b810, player, drawn, 9, level, player);
    return port_return(&port, result, entry->edx);
}

/* Original 0x43b930: release the side by 0x43b980, allocate 0x15c bytes by 0x4ca000, construct
 * them by 0x4abd70 when that worked, keep the result at +0x4e8 and show it by 0x4ac7b0. */
uint32_t vertrix_port_player_alloc_side_43b930(PORT_SIGNATURE)
{
    Port port;
    uint32_t player = entry->eax;
    uint32_t side;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    port_forward(&port, entry, 0x43b980, player, entry->edx, entry->ebx, player);
    side = port_forward(&port, entry, 0x4ca000, 0x15c, vertrix_lift_edx, entry->ebx, player);
    if (side != 0)
    {
        side = port_forward(&port, entry, 0x4abd70, side, vertrix_lift_edx, entry->ebx, player);
    }
    port_set32(&port, player, 0x4e8, side);
    result = port_forward(&port, entry, 0x4ac7b0, side, vertrix_lift_edx, entry->ebx, player);
    return port_return(&port, result, vertrix_lift_edx);
}

/* Original 0x43b980: with a side at +0x4e8, its first method (edx 2), clear it and 0x43ce00 on
 * the player. */
uint32_t vertrix_port_player_release_side_43b980(PORT_SIGNATURE)
{
    Port port;
    uint32_t player = entry->eax;
    uint32_t side;
    uint32_t methods;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    side = port_u32(&port, player, 0x4e8);
    if (side == 0)
    {
        return port_return(&port, player, entry->edx);
    }
    methods = port_u32(&port, side, 0x158);
    port_forward(&port, entry, port_u32(&port, methods, 0), side, 2, methods, player);
    port_set32(&port, player, 0x4e8, 0);
    result = port_forward(&port, entry, 0x43ce00, player, vertrix_lift_edx, methods, player);
    return port_return(&port, result, entry->edx);
}

/* Original 0x43ba90: add edx times the multiplier of level 0x532bbc (at 0x4f80cc) to the score
 * +0x174, at most 99999999; edx the amount. */
uint32_t vertrix_port_player_add_score_43ba90(PORT_SIGNATURE)
{
    Port port;
    uint32_t player = entry->eax;
    uint32_t amount;
    uint32_t score;
    port_open(&port, calls, services, globals, entry);
    amount = entry->edx * port_u32(&port, port_u32(&port, 0, 0x532bbc) * 4, 0x4f80cc);
    score = port_u32(&port, player, 0x174) + amount;
    port_set32(&port, player, 0x174, score);
    if (score > 0x5f5e0ff)
    {
        port_set32(&port, player, 0x174, 0x5f5e0ff);
    }
    return port_return(&port, player, amount);
}

/* Original 0x43bb00: keep dl at +0x4c5; when it is clear and 0x43d3b0 gives 1, 0x43ce00 on the
 * partner +0x3b0 first, and in any clear case release the side, 0x43ce00 on the player; then
 * 0x4726d0. */
uint32_t vertrix_port_player_conditional_reset_43bb00(PORT_SIGNATURE)
{
    Port port;
    uint32_t player = entry->eax;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    port_set8(&port, player, 0x4c5, entry->edx);
    if ((entry->edx & 0xff) != 0)
    {
        result = port_forward(&port, entry, 0x4726d0, player, entry->edx, entry->ebx, player);
        return port_return(&port, result, vertrix_lift_edx);
    }
    if (port_forward(&port, entry, 0x43d3b0, player, entry->edx, entry->ebx, player) == 1)
    {
        port_forward(&port, entry, 0x43ce00, port_u32(&port, player, 0x3b0), vertrix_lift_edx,
                     entry->ebx, player);
    }
    port_forward(&port, entry, 0x43b980, player, vertrix_lift_edx, entry->ebx, player);
    result = port_forward(&port, entry, 0x43ce00, player, vertrix_lift_edx, entry->ebx, player);
    result = port_forward(&port, entry, 0x4726d0, result, vertrix_lift_edx, entry->ebx, player);
    return port_return(&port, result, vertrix_lift_edx);
}

/* Event edx unless it is the one at 0x4f81cc: kind 1 or 2 (the dword at eax) by `first` or
 * `second`, ebx the kind. */
static uint32_t event_dispatch(PORT_SIGNATURE, uint32_t first, uint32_t second)
{
    Port port;
    uint32_t kind;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    if (entry->edx == port_u32(&port, 0, 0x4f81cc))
    {
        return port_return(&port, entry->edx, entry->edx);
    }
    kind = port_u32(&port, entry->eax, 0);
    if (kind != 1 && kind != 2)
    {
        return port_return(&port, entry->edx, entry->edx);
    }
    result = port_forward(&port, entry, kind == 1 ? first : second, entry->edx, entry->edx, kind,
                          entry->eax);
    return port_return(&port, result, vertrix_lift_edx);
}

/* Original 0x43c0e0: by 0x417260 or 0x417290. */
uint32_t vertrix_port_sfx_dispatch_event_43c0e0(PORT_SIGNATURE)
{
    return event_dispatch(calls, services, globals, entry, 0x417260, 0x417290);
}

/* Original 0x43c110: by 0x4172c0 or 0x4173d0. */
uint32_t vertrix_port_sfx_dispatch_secondary_43c110(PORT_SIGNATURE)
{
    return event_dispatch(calls, services, globals, entry, 0x4172c0, 0x4173d0);
}

/* Original 0x43ccb0: when the partner's (+0x3b0) state byte +0x4cc is 1, enter 0x4520b0 by
 * 0x43bb60, set the state to 5 and 0x4ac8f0 (1); otherwise 0. */
uint32_t vertrix_port_player_enter_4520b0_43ccb0(PORT_SIGNATURE)
{
    Port port;
    uint32_t player = entry->eax;
    port_open(&port, calls, services, globals, entry);
    if (port_u8(&port, port_u32(&port, player, 0x3b0), 0x4cc) != 1)
    {
        return port_return(&port, 0, entry->edx);
    }
    port_forward(&port, entry, 0x43bb60, player, 0x4520b0, entry->ebx, player);
    port_set8(&port, player, 0x4cc, 5);
    port_forward(&port, entry, 0x4ac8f0, player, vertrix_lift_edx, entry->ebx, player);
    return port_return(&port, 1, entry->edx);
}

/* Original 0x43cd30: when 0x43d3b0 gives 1, 0x43ce00 on the edx it leaves and 0x4726d0 (1);
 * otherwise 0. */
uint32_t vertrix_port_player_gated_reset_43cd30(PORT_SIGNATURE)
{
    Port port;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    if (port_forward(&port, entry, 0x43d3b0, entry->eax, entry->eax, entry->ebx, entry->ecx) != 1)
    {
        return port_return(&port, 0, entry->edx);
    }
    result = port_forward(&port, entry, 0x43ce00, vertrix_lift_edx, vertrix_lift_edx, entry->ebx,
                          entry->ecx);
    port_forward(&port, entry, 0x4726d0, result, vertrix_lift_edx, entry->ebx, entry->ecx);
    return port_return(&port, 1, entry->edx);
}

/* Original 0x43d330: allocate 16 bytes by 0x4ca000 (set up by 0x487870 when that worked), store
 * edx, ebx and ecx in them and add them to the list +0x468 by 0x4879f0. */
uint32_t vertrix_port_object_table_store_43d330(PORT_SIGNATURE)
{
    Port port;
    uint32_t owner = entry->eax;
    uint32_t record;
    uint32_t list;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    record =
        port_forward_esi(&port, entry, 0x4ca000, 0x10, entry->edx, entry->ebx, entry->ecx, owner);
    if (record != 0)
    {
        record = port_forward_esi(&port, entry, 0x487870, record, vertrix_lift_edx, entry->ebx,
                                  entry->ecx, owner);
    }
    port_set32(&port, record, 0, vertrix_lift_edx);
    port_set32(&port, record, 4, entry->ebx);
    port_set32(&port, record, 8, entry->ecx);
    list = port_u32(&port, owner, 0x468);
    result = port_forward_esi(&port, entry, 0x4879f0, list, record, entry->ebx, list, owner);
    return port_return(&port, result, vertrix_lift_edx);
}

/* Original 0x43f3f0: 0x4830f0 on each set dword of the 548 at 0x5410f8, then clear 0x54406c. */
uint32_t vertrix_port_release_table_a_43f3f0(PORT_SIGNATURE)
{
    Port port;
    uint32_t offset = 0;
    uint32_t result = entry->eax;
    port_open(&port, calls, services, globals, entry);
    do
    {
        uint32_t object = port_u32(&port, offset, 0x5410f8);
        if (object != 0)
        {
            result = port_forward(&port, entry, 0x4830f0, object, offset, entry->ebx, object);
            offset = vertrix_lift_edx;
        }
        offset += 4;
    } while (offset != 0x890);
    port_set32(&port, 0, 0x54406c, 0);
    return port_return(&port, result, entry->edx);
}

/* Original 0x441b30: with an image (+0x274) and a target (+0x278), draw the image by 0x47ce10
 * at 0, 0 with its size (+4, +8). */
uint32_t vertrix_port_record_draw_441b30(PORT_SIGNATURE)
{
    Port port;
    uint32_t image;
    uint32_t target;
    uint32_t width;
    uint32_t result;
    uint32_t pushed[4];
    port_open(&port, calls, services, globals, entry);
    image = port_u32(&port, entry->eax, 0x274);
    if (image == 0)
    {
        return port_return(&port, entry->eax, entry->edx);
    }
    target = port_u32(&port, entry->eax, 0x278);
    if (target == 0)
    {
        return port_return(&port, entry->eax, entry->edx);
    }
    width = port_u32(&port, image, 4);
    pushed[0] = 0;
    pushed[1] = 0;
    pushed[2] = width;
    pushed[3] = port_u32(&port, image, 8);
    result = port_call_registers(&port, 0x47ce10, image, target, 0, 0, entry->esi, width,
                                 entry->ebp, pushed, 4);
    return port_return(&port, result, entry->edx);
}

/* Original 0x442110: free each of the 115 dwords at 0x54414c by 0x4ea190 (edx the index); eax
 * the count. */
uint32_t vertrix_port_release_table_b_442110(PORT_SIGNATURE)
{
    Port port;
    uint32_t index = 0;
    port_open(&port, calls, services, globals, entry);
    while ((index & 0xffff) < 0x73)
    {
        port_forward(&port, entry, 0x4ea190, port_u32(&port, (index & 0xffff) * 4, 0x54414c), index,
                     entry->ebx, entry->ecx);
        index = vertrix_lift_edx + 1;
    }
    return port_return(&port, index & 0xffff, entry->edx);
}

/* Original 0x449360: with a frame count (+0x48), clear +0x4a, set +0x4c to 4, then 0x4ad530 and
 * 0x4adfe0. */
uint32_t vertrix_port_actor_frame_decay_full_449360(PORT_SIGNATURE)
{
    Port port;
    uint32_t actor = entry->eax;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    if (port_u16(&port, actor, 0x48) == 0)
    {
        return port_return(&port, actor, entry->edx);
    }
    port_set16(&port, actor, 0x4a, 0);
    port_set16(&port, actor, 0x4c, 4);
    port_forward(&port, entry, 0x4ad530, actor, entry->edx, entry->ebx, actor);
    result = port_forward(&port, entry, 0x4adfe0, actor, vertrix_lift_edx, entry->ebx, actor);
    return port_return(&port, result, vertrix_lift_edx);
}

/* Original 0x449390: when frame set edx differs from +0xb8, load the images at 0x544a18 by
 * 0x4ac8d0, switch by 0x4ac710, then 0x4ac8a0 and 0x4adfe0. */
uint32_t vertrix_port_actor_frame_switch_full_449390(PORT_SIGNATURE)
{
    Port port;
    uint32_t actor = entry->eax;
    uint32_t current;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    current = port_u32(&port, actor, 0xb8);
    if (current == entry->edx)
    {
        return port_return(&port, current, entry->edx);
    }
    port_forward(&port, entry, 0x4ac8d0, actor, 0x544a18, entry->edx, actor);
    port_forward(&port, entry, 0x4ac710, actor, entry->edx, entry->edx, actor);
    port_forward(&port, entry, 0x4ac8a0, actor, vertrix_lift_edx, entry->edx, actor);
    result = port_forward(&port, entry, 0x4adfe0, actor, vertrix_lift_edx, entry->edx, actor);
    return port_return(&port, result, vertrix_lift_edx);
}

/* Original 0x4494c0: 0x4ac500, and when 0x4ac520 gives 1, 0x4ac5b0 with what 0x4ac540 gives,
 * then 0x449360. */
uint32_t vertrix_port_actor_step_then_decay_4494c0(PORT_SIGNATURE)
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
    result = port_forward(&port, entry, 0x449360, actor, vertrix_lift_edx, entry->ebx, actor);
    return port_return(&port, result, entry->edx);
}

/* 0x4ac500 and, when 0x4ac520 gives 1, 0x4ac510 (each on the edx the call before leaves); then
 * keep the dword +0x14c at `global`. */
static uint32_t step_keep(PORT_SIGNATURE, uint32_t global)
{
    Port port;
    uint32_t actor = entry->eax;
    uint32_t value;
    port_open(&port, calls, services, globals, entry);
    port_forward(&port, entry, 0x4ac500, actor, actor, entry->ebx, actor);
    if (port_forward(&port, entry, 0x4ac520, vertrix_lift_edx, vertrix_lift_edx, entry->ebx,
                     actor) == 1)
    {
        port_forward(&port, entry, 0x4ac510, vertrix_lift_edx, vertrix_lift_edx, entry->ebx, actor);
    }
    value = port_u32(&port, actor, 0x14c);
    port_set32(&port, 0, global, value);
    return port_return(&port, value, entry->edx);
}

/* Original 0x44ae80: at 0x532a50. */
uint32_t vertrix_port_actor_step_keep_44ae80(PORT_SIGNATURE)
{
    return step_keep(calls, services, globals, entry, 0x532a50);
}

/* Original 0x44c260: at 0x532a54. */
uint32_t vertrix_port_actor_step_keep_44c260(PORT_SIGNATURE)
{
    return step_keep(calls, services, globals, entry, 0x532a54);
}

/* Original 0x44ff30: 0x4ac600, and when 0x4ac620 gives 1, set the handler 0x44ff60 by 0x4ac610
 * and 0x4ac8f0. */
uint32_t vertrix_port_player_indicator_update_44ff30(PORT_SIGNATURE)
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
    port_forward(&port, entry, 0x4ac610, object, 0x44ff60, entry->ebx, object);
    result = port_forward(&port, entry, 0x4ac8f0, object, vertrix_lift_edx, entry->ebx, object);
    return port_return(&port, result, entry->edx);
}

/* Original 0x44ff60: when 0x43ba70 on the player of slot +4 (at 0x540f88) gives 0, the handler
 * 0x44fe80 by 0x4ac8f0. */
uint32_t vertrix_port_player_indicator_update_44ff60(PORT_SIGNATURE)
{
    Port port;
    uint32_t object = entry->eax;
    uint32_t player;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    player = port_u32(&port, port_u32(&port, object, 4) * 4, 0x540f88);
    result = port_forward(&port, entry, 0x43ba70, player, entry->edx, entry->ebx, object);
    if (result == 0)
    {
        result = port_forward(&port, entry, 0x4ac8f0, object, 0x44fe80, entry->ebx, object);
    }
    return port_return(&port, result, entry->edx);
}

/* Original 0x450100: when 0x4b5eb0 finds slot +4 in 0x54671c with a clear +0x58, the handler
 * 0x44ff90 by 0x4ac8f0. */
uint32_t vertrix_port_ui_indicator_storage_update_450100(PORT_SIGNATURE)
{
    Port port;
    uint32_t object = entry->eax;
    uint32_t found;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    found = port_forward(&port, entry, 0x4b5eb0, 0x54671c, port_u32(&port, object, 4), entry->ebx,
                         object);
    if (found == 0 || port_u32(&port, found, 0x58) != 0)
    {
        return port_return(&port, found, entry->edx);
    }
    result = port_forward(&port, entry, 0x4ac8f0, object, 0x44ff90, entry->ebx, object);
    return port_return(&port, result, entry->edx);
}
