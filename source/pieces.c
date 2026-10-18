#include "pieces.h"

/* Piece, preview and board routines: child slots, motion starts, markers and fills. */

/* Original 0x42a980: the kinds (byte +0x15c) of the three children +0x15c, +0x160 and +0x164
 * stored at edx, ebx and ecx. */
uint32_t vertrix_port_piece_child_kinds_42a980(PORT_SIGNATURE)
{
    Port port;
    uint32_t piece = entry->eax;
    uint32_t second;
    uint32_t third;
    uint32_t kind;
    port_open(&port, calls, services, globals, entry);
    port_set8(&port, entry->edx, 0, port_u8(&port, port_u32(&port, piece, 0x15c), 0x15c));
    second = port_u32(&port, piece, 0x160);
    kind = port_u8(&port, second, 0x15c);
    port_set8(&port, entry->ebx, 0, kind);
    second = (second & 0xffffff00u) | kind;
    third = port_u32(&port, piece, 0x164);
    kind = port_u8(&port, third, 0x15c);
    port_set8(&port, entry->ecx, 0, kind);
    return port_return(&port, (third & 0xffffff00u) | kind, second);
}

/* Original 0x42a9d0: set the word +0x48 of each of the three children to -200 when the toggle
 * +0x184 is clear, else 0, then flip the toggle; the new toggle. */
uint32_t vertrix_port_piece_children_offset_42a9d0(PORT_SIGNATURE)
{
    Port port;
    uint32_t piece = entry->eax;
    uint32_t slot;
    uint32_t toggle;
    port_open(&port, calls, services, globals, entry);
    for (slot = 0; slot < 3; slot++)
    {
        uint32_t child = port_u32(&port, piece + slot * 4, 0x15c);
        if (child != 0)
        {
            port_set16(&port, child, 0x48, port_u32(&port, piece, 0x184) != 0 ? 0 : 0xff38);
        }
    }
    toggle = 1 - port_u32(&port, piece, 0x184);
    port_set32(&port, piece, 0x184, toggle);
    return port_return(&port, toggle, entry->edx);
}

/* Original 0x42aab0: construct by 0x4abd70, set the class 0x514774 at +0x158 and clear the
 * seven slots from +0x15c and the five dwords from +0x178. */
uint32_t vertrix_port_piece_actor_parent_construct_42aab0(PORT_SIGNATURE)
{
    Port port;
    uint32_t object;
    uint32_t offset;
    port_open(&port, calls, services, globals, entry);
    object = port_forward(&port, entry, 0x4abd70, entry->eax, entry->edx, entry->ebx, entry->eax);
    port_set32(&port, object, 0x158, 0x514774);
    for (offset = 4; offset <= 0x1c; offset += 4)
    {
        port_set32(&port, object + offset, 0x158, 0);
    }
    for (offset = 0x178; offset <= 0x188; offset += 4)
    {
        port_set32(&port, object, offset, 0);
    }
    return port_return(&port, object, entry->edx);
}

/* Original 0x42abf0: method +8 of each of the seven children with edx; edx the last slot or what
 * its call leaves. */
uint32_t vertrix_port_piece_actor_forward_slot2_42abf0(PORT_SIGNATURE)
{
    Port port;
    uint32_t at = entry->eax;
    uint32_t end = entry->eax + 0x1c;
    uint32_t result = entry->eax;
    uint32_t edx = entry->edx;
    port_open(&port, calls, services, globals, entry);
    do
    {
        uint32_t child = port_u32(&port, at, 0x15c);
        edx = child;
        if (child != 0)
        {
            uint32_t methods = port_u32(&port, child, 0x158);
            result = port_forward_esi(&port, entry, port_u32(&port, methods, 8), child, entry->edx,
                                      entry->edx, at, methods);
            edx = vertrix_lift_edx;
        }
        at += 4;
    } while (at != end);
    return port_return(&port, result, edx);
}

/* Original 0x42af30: place each of the seven children at the parent's x (+0xe) and y (+0x16)
 * plus its index times the step 0x4f90ac. */
uint32_t vertrix_port_piece_actor_layout_42af30(PORT_SIGNATURE)
{
    Port port;
    uint32_t parent = entry->eax;
    uint32_t index;
    port_open(&port, calls, services, globals, entry);
    for (index = 0; index < 7; index++)
    {
        uint32_t child = port_u32(&port, parent + index * 4, 0x15c);
        if (child != 0)
        {
            port_set16(&port, child, 0xe, port_u16(&port, parent, 0xe));
            port_set16(&port, port_u32(&port, parent + index * 4, 0x15c), 0x16,
                       port_u16(&port, parent, 0x16) + port_u16(&port, 0, 0x4f90ac) * index);
        }
    }
    return port_return(&port, parent + 0x1c, entry->edx);
}

/* Unless the flag at `field` is set, set it, start the motion of the level 0x532bbc (0x4f7d14)
 * by 0x4ac7d0, keep its speed word (0x4f7d20) at +0x1a and 0x4ac510 with it. */
static uint32_t motion_start(PORT_SIGNATURE, uint32_t field)
{
    Port port;
    uint32_t object = entry->eax;
    uint32_t speed;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    if (port_u32(&port, object, field) != 0)
    {
        return port_return(&port, object, entry->edx);
    }
    port_set32(&port, object, field, 1);
    port_forward(&port, entry, 0x4ac7d0, object,
                 port_u32(&port, port_u32(&port, 0, 0x532bbc) * 4, 0x4f7d14), entry->ebx, object);
    speed = port_u32(&port, 0, 0x532bbc);
    speed = (speed & 0xffff0000u) | port_u16(&port, speed * 4, 0x4f7d20);
    port_set16(&port, object, 0x1a, speed);
    result = port_forward(&port, entry, 0x4ac510, object, speed, entry->ebx, object);
    return port_return(&port, result, entry->edx);
}

/* Original 0x42b000: the flag +0x178. */
uint32_t vertrix_port_player_preview_motion_start_42b000(PORT_SIGNATURE)
{
    return motion_start(calls, services, globals, entry, 0x178);
}

/* Original 0x42b9f0: the flag +0x170. */
uint32_t vertrix_port_piece_arm_once_42b9f0(PORT_SIGNATURE)
{
    return motion_start(calls, services, globals, entry, 0x170);
}

/* Original 0x42b310: 0x4ae150, then method +4 of each of the three children from +0x15c and of
 * the three from +0x168. */
uint32_t vertrix_port_piece_children_draw_42b310(PORT_SIGNATURE)
{
    Port port;
    uint32_t object = entry->eax;
    uint32_t end = object + 0xc;
    uint32_t at = object;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    result = port_forward_esi(&port, entry, 0x4ae150, object, entry->edx, entry->ebx, entry->ecx,
                              object);
    do
    {
        uint32_t child = port_u32(&port, at, 0x15c);
        if (child != 0)
        {
            uint32_t methods = port_u32(&port, child, 0x158);
            result = port_forward_esi(&port, entry, port_u32(&port, methods, 4), child, at, end,
                                      methods, object);
            at = vertrix_lift_edx;
        }
        at += 4;
    } while (at != end);
    at = object;
    do
    {
        uint32_t child = port_u32(&port, at, 0x168);
        if (child != 0)
        {
            uint32_t methods = port_u32(&port, child, 0x158);
            result = port_forward_esi(&port, entry, port_u32(&port, methods, 4), child, at, end,
                                      methods, child);
            at = vertrix_lift_edx;
        }
        at += 4;
    } while (at != end);
    return port_return(&port, result, entry->edx);
}

/* Original 0x42b8d0: 0x4ac500, and when 0x4ac520 gives 1, 0x4ac5b0 with what 0x4ac540 gives and,
 * without a child (+0x15c), the y +0x16 moved by that times the speed +0x1a; then 0x4ae150 (each
 * on the edx the call before leaves, ecx the count or its product). */
uint32_t vertrix_port_actor_step_move_42b8d0(PORT_SIGNATURE)
{
    Port port;
    uint32_t actor;
    uint32_t steps = entry->ecx;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    port_forward(&port, entry, 0x4ac500, entry->eax, entry->eax, entry->ebx, entry->ecx);
    actor = vertrix_lift_edx;
    result = port_forward(&port, entry, 0x4ac520, actor, actor, entry->ebx, entry->ecx);
    actor = vertrix_lift_edx;
    if (result == 1)
    {
        steps = port_forward(&port, entry, 0x4ac540, actor, actor, entry->ebx, entry->ecx);
        actor = vertrix_lift_edx;
        port_forward(&port, entry, 0x4ac5b0, actor, actor, entry->ebx, steps);
        actor = vertrix_lift_edx;
        if (port_u32(&port, actor, 0x15c) == 0)
        {
            /* imul cx: only the low word of the count changes. */
            steps = (steps & 0xffff0000u) | ((steps * port_u16(&port, actor, 0x1a)) & 0xffff);
            port_set16(&port, actor, 0x16, port_u16(&port, actor, 0x16) + steps);
        }
    }
    result = port_forward(&port, entry, 0x4ae150, actor, actor, entry->ebx, steps);
    return port_return(&port, result, entry->edx);
}

/* Original 0x42b990: when the piece's x (signed word +0xe) is not the column x (+0xaa) less
 * 0x4f9098, take that and set the variant by 0x42b920 (0 when byte +0x16c is 1, else 1). */
uint32_t vertrix_port_piece_snap_to_origin_42b990(PORT_SIGNATURE)
{
    Port port;
    uint32_t piece = entry->eax;
    uint32_t origin;
    uint32_t target;
    uint32_t margin;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    origin = port_u32(&port, 0, 0x4f9098);
    target = (uint32_t)(int32_t)(int16_t)port_u16(&port, piece, 0xaa) - origin;
    if ((uint32_t)(int32_t)(int16_t)port_u16(&port, piece, 0xe) == target)
    {
        return port_return(&port, piece, entry->edx);
    }
    margin = (entry->ebx & 0xffff0000u) | port_u16(&port, 0, 0x4f9098);
    port_set16(&port, piece, 0xe, port_u16(&port, piece, 0xaa) - margin);
    result = port_forward(&port, entry, 0x42b920, piece, port_u8(&port, piece, 0x16c) == 1 ? 0 : 1,
                          margin, target);
    return port_return(&port, result, entry->edx);
}

/* Original 0x42bab0: set the mode +0x160 to edx; entering mode 1 from 0 sets +0x164 and clears
 * the word +0x48, leaving mode 1 clears both. */
uint32_t vertrix_port_piece_set_mode_42bab0(PORT_SIGNATURE)
{
    Port port;
    uint32_t piece = entry->eax;
    port_open(&port, calls, services, globals, entry);
    if (entry->edx == 1)
    {
        if (port_u32(&port, piece, 0x160) == 0)
        {
            port_set16(&port, piece, 0x48, 0);
            port_set32(&port, piece, 0x164, entry->edx);
        }
    }
    else if (port_u32(&port, piece, 0x160) == 1)
    {
        port_set32(&port, piece, 0x164, 0);
        port_set16(&port, piece, 0x48, 0);
    }
    port_set32(&port, piece, 0x160, entry->edx);
    return port_return(&port, piece, entry->edx);
}

/* Original 0x42eda0: the handler edx for the 65 cells from +0x220 by 0x4b2340. */
uint32_t vertrix_port_board_collection_set_handler_42eda0(PORT_SIGNATURE)
{
    Port port;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    result = port_forward(&port, entry, 0x4b2340, entry->eax + 0x220, 0x41, entry->edx, entry->ecx);
    return port_return(&port, result, vertrix_lift_edx);
}

/* Original 0x42ee20: for each of the three children of the active piece (+0xa60), show it by
 * 0x4ac7b0 (5), set byte +0x4e to 100, the handler 0x44c960 by 0x4ac510 and 0x4ac8f0. */
uint32_t vertrix_port_board_ready_previews_42ee20(PORT_SIGNATURE)
{
    Port port;
    uint32_t board = entry->eax;
    uint32_t offset;
    uint32_t result = board;
    port_open(&port, calls, services, globals, entry);
    if (port_u32(&port, board, 0xa60) == 0)
    {
        return port_return(&port, board, entry->edx);
    }
    for (offset = 0; offset != 0xc; offset += 4)
    {
        uint32_t child = port_u32(&port, port_u32(&port, board, 0xa60) + offset, 0x15c);
        if (child != 0)
        {
            port_forward_esi(&port, entry, 0x4ac7b0, child, 5, offset, child, board);
            port_set8(&port, child, 0x4e, 0x64);
            port_forward_esi(&port, entry, 0x4ac510, child, 0x44c960, offset, child, board);
            result = port_forward_esi(&port, entry, 0x4ac8f0, child, vertrix_lift_edx, offset,
                                      child, board);
        }
    }
    return port_return(&port, result, entry->edx);
}

/* Original 0x42ee80: restart each set cell of the 5 rows of 13 from +0x220 by 0x4ac7b0 (edx
 * the given edx) and 0x4ac510; edx left at the row end. */
uint32_t vertrix_port_board_restart_slots_42ee80(PORT_SIGNATURE)
{
    Port port;
    uint32_t board = entry->eax;
    uint32_t frame = entry->esp - 4;
    uint32_t row;
    uint32_t eax = entry->eax;
    port_open(&port, calls, services, globals, entry);
    for (row = 0; row != 0x104; row += 0x34)
    {
        uint32_t column;
        for (column = 0; column != 0x34; column += 4)
        {
            uint32_t at = board + row + column;
            eax = port_u32(&port, at, 0x220);
            if (eax != 0)
            {
                port_call_with(&port, 0x4ac7b0, eax, entry->edx, at, column, entry->edx,
                               board + row, frame);
                eax = port_call_with(&port, 0x4ac510, port_u32(&port, at, 0x220), vertrix_lift_edx,
                                     at, column, entry->edx, board + row, frame);
            }
        }
    }
    return port_return(&port, eax, 0x104);
}

/* The extra object (+0xce0) placed `offset` below the board's y (+0x16) with the speed of the
 * level (0x4f7d08) at +0x1a, and the handler `handler` by 0x4ac8f0. */
static uint32_t extra_place(PORT_SIGNATURE, uint32_t offset, uint32_t handler)
{
    Port port;
    uint32_t board = entry->eax;
    uint32_t extra;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    port_set16(&port, port_u32(&port, board, 0xce0), 0x18, port_u16(&port, board, 0x16) + offset);
    extra = port_u32(&port, board, 0xce0);
    port_set16(&port, extra, 0x1a, port_u16(&port, port_u32(&port, 0, 0x532bbc) * 4, 0x4f7d08));
    result = port_forward(&port, entry, 0x4ac8f0, port_u32(&port, board, 0xce0), handler,
                          entry->ebx, extra);
    return port_return(&port, result, entry->edx);
}

/* Original 0x4300b0: 0x108 below, handler 0x44c880. */
uint32_t vertrix_port_board_place_extra_4300b0(PORT_SIGNATURE)
{
    return extra_place(calls, services, globals, entry, 0x108, 0x44c880);
}

/* Original 0x430100: 0x138 below, handler 0x44c8e0. */
uint32_t vertrix_port_board_place_extra_430100(PORT_SIGNATURE)
{
    return extra_place(calls, services, globals, entry, 0x138, 0x44c8e0);
}

/* Original 0x430800: a block of kind dl (signed) with a random value 1 to 10 (0x4826c0 on
 * 0x598d30) passed through 0x415470, made by 0x42bbd0 and added by 0x42ff10; the block. */
uint32_t vertrix_port_block_spawn_full_430800(PORT_SIGNATURE)
{
    Port port;
    uint32_t board = entry->eax;
    uint32_t kind = (uint32_t)(int32_t)(int8_t)entry->edx;
    uint32_t drawn;
    uint32_t value;
    uint32_t block;
    port_open(&port, calls, services, globals, entry);
    drawn = port_forward_esi(&port, entry, 0x4826c0, 0x598d30, 0xa, entry->ebx, entry->edx, board);
    drawn = (drawn & 0xffff) + 1;
    value = port_call_with(&port, 0x415470, entry->edx, vertrix_lift_edx, drawn, entry->edx, board,
                           kind, entry->ebp);
    block = port_call_with(&port, 0x42bbd0, kind, value, drawn, 0, board, kind, entry->ebp);
    port_call_with(&port, 0x42ff10, board, block, drawn, block, board, kind, entry->ebp);
    return port_return(&port, block, vertrix_lift_edx);
}

/* Original 0x431c10: the kind (signed byte +0x15c) of child edx of the active piece, or -1 (in
 * edx too). */
uint32_t vertrix_port_board_piece_child_kind_431c10(PORT_SIGNATURE)
{
    Port port;
    uint32_t piece;
    uint32_t kind;
    port_open(&port, calls, services, globals, entry);
    piece = port_u32(&port, entry->eax, 0xa60);
    if (piece == 0)
    {
        return port_return(&port, 0xffffffff, 0xffffffff);
    }
    kind = (uint32_t)(int32_t)(int8_t)port_u8(&port, port_u32(&port, piece + entry->edx * 4, 0x15c),
                                              0x15c);
    return port_return(&port, kind, kind);
}

/* Original 0x431fb0: flash the three children of the active piece (+0x93 1, +0x95 0, +0x4e 50,
 * word +0x48 20) and set its +0x17c. */
uint32_t vertrix_port_board_flash_children_431fb0(PORT_SIGNATURE)
{
    Port port;
    uint32_t board = entry->eax;
    uint32_t offset;
    uint32_t piece;
    port_open(&port, calls, services, globals, entry);
    for (offset = 0; offset != 0xc; offset += 4)
    {
        uint32_t child = port_u32(&port, offset + port_u32(&port, board, 0xa60), 0x15c);
        port_set8(&port, child, 0x93, 1);
        port_set8(&port, child, 0x95, 0);
        port_set8(&port, child, 0x4e, 0x32);
        port_set16(&port, child, 0x48, 0x14);
    }
    piece = port_u32(&port, board, 0xa60);
    port_set32(&port, piece, 0x17c, 1);
    return port_return(&port, piece, entry->edx);
}

/* Original 0x432110: with a preview (+0xb70), keep its +0x168 at +0xb74, release it by its first
 * method (edx 2) and clear it. */
uint32_t vertrix_port_player_preview_release_432110(PORT_SIGNATURE)
{
    Port port;
    uint32_t player = entry->eax;
    uint32_t preview;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    preview = port_u32(&port, player, 0xb70);
    if (preview == 0)
    {
        return port_return(&port, player, entry->edx);
    }
    port_set32(&port, player, 0xb74, port_u32(&port, preview, 0x168));
    result = port_u32(&port, player, 0xb70);
    if (result != 0)
    {
        uint32_t methods = port_u32(&port, result, 0x158);
        result =
            port_forward(&port, entry, port_u32(&port, methods, 0), result, 2, methods, player);
    }
    port_set32(&port, player, 0xb70, 0);
    return port_return(&port, result, entry->edx);
}

/* Original 0x432160: without a piece (+0xb78), allocate 0x18c bytes by 0x4ca000, construct them
 * by 0x42aab0 when that worked, keep them there and set them up by 0x42acf0 with the kind dl
 * (signed, kept in a local). edx is ecx on the early return. */
uint32_t vertrix_port_player_piece_create_432160(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x10
    };
    Port port;
    uint32_t player = entry->eax;
    uint32_t frame = entry->esp - 4;
    uint32_t kind;
    uint32_t piece;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set8(&port, frame, -0xcu, entry->edx);
    if (port_u32(&port, player, 0xb78) != 0)
    {
        return port_return(&port, player, entry->ecx);
    }
    piece = port_call_with(&port, 0x4ca000, 0x18c, entry->ecx, entry->ebx, entry->ecx, player,
                           entry->edi, frame);
    if (piece != 0)
    {
        piece = port_call_with(&port, 0x42aab0, piece, vertrix_lift_edx, entry->ebx, entry->ecx,
                               player, entry->edi, frame);
    }
    kind = (uint32_t)(int32_t)(int8_t)port_u8(&port, frame, -0xcu);
    port_set32(&port, player, 0xb78, piece);
    piece = port_call_with(&port, 0x42acf0, piece, kind, vertrix_lift_edx, entry->ebx, player, kind,
                           frame);
    return port_return(&port, piece, vertrix_lift_edx);
}

/* Original 0x4321b0: with a piece (+0xb78), keep what 0x42b070 gives at +0xb7c, release it by
 * its first method (edx 2) and clear it. */
uint32_t vertrix_port_player_piece_release_4321b0(PORT_SIGNATURE)
{
    Port port;
    uint32_t player = entry->eax;
    uint32_t piece;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    piece = port_u32(&port, player, 0xb78);
    if (piece == 0)
    {
        return port_return(&port, player, entry->edx);
    }
    result = port_forward(&port, entry, 0x42b070, piece, piece, entry->ebx, player);
    port_set32(&port, player, 0xb7c, result);
    result = port_u32(&port, player, 0xb78);
    if (result != 0)
    {
        uint32_t methods = port_u32(&port, result, 0x158);
        result =
            port_forward(&port, entry, port_u32(&port, methods, 0), result, 2, methods, player);
    }
    port_set32(&port, player, 0xb78, 0);
    return port_return(&port, result, entry->edx);
}

/* Original 0x432840: clear the five rows of 13 dwords from the board; eax left past them. */
uint32_t vertrix_port_board_clear_mask_432840(PORT_SIGNATURE)
{
    Port port;
    uint32_t offset;
    port_open(&port, calls, services, globals, entry);
    for (offset = 0; offset < 5 * 0x34; offset += 4)
    {
        port_set32(&port, entry->eax, offset, 0);
    }
    return port_return(&port, entry->eax + 5 * 0x34, entry->edx);
}

/* Original 0x435fe0: the row (at ebx) and column (at ecx) of the edx-th marker 1 of the five
 * rows of 13 from +0xb94, row by row. */
uint32_t vertrix_port_board_marker_nth_by_row_435fe0(PORT_SIGNATURE)
{
    Port port;
    uint32_t count = 0;
    uint32_t row;
    port_open(&port, calls, services, globals, entry);
    for (row = 0; row < 5; row++)
    {
        uint32_t column;
        for (column = 0; column < 13; column++)
        {
            if (port_u8(&port, entry->eax + row * 13 + column, 0xb94) == 1)
            {
                if (count == entry->edx)
                {
                    port_set32(&port, entry->ebx, 0, row);
                    port_set32(&port, entry->ecx, 0, column);
                }
                count++;
            }
        }
    }
    return port_return(&port, 13, entry->eax + 5 * 13);
}

/* The row (at ebx) and column (at ecx) of the edx-th marker `value`, column by column. */
static uint32_t marker_nth_by_column(PORT_SIGNATURE, uint32_t value)
{
    Port port;
    uint32_t count = 0;
    uint32_t column;
    port_open(&port, calls, services, globals, entry);
    for (column = 0; column < 13; column++)
    {
        uint32_t row;
        for (row = 0; row < 5; row++)
        {
            if (port_u8(&port, entry->eax + column + row * 13, 0xb94) == value)
            {
                if (count == entry->edx)
                {
                    port_set32(&port, entry->ebx, 0, row);
                    port_set32(&port, entry->ecx, 0, column);
                }
                count++;
            }
        }
    }
    return port_return(&port, 5, entry->eax + 12 + 5 * 13);
}

/* Original 0x4360b0: of marker 1. */
uint32_t vertrix_port_board_marker_nth_by_column_4360b0(PORT_SIGNATURE)
{
    return marker_nth_by_column(calls, services, globals, entry, 1);
}

/* Original 0x436100: of marker 2. */
uint32_t vertrix_port_board_marker_nth_by_column_436100(PORT_SIGNATURE)
{
    return marker_nth_by_column(calls, services, globals, entry, 2);
}

/* Original 0x4375a0: 0x4327e0 on the 65 cells from +0x220 into +0x1de, then mark (+0xb94) each
 * cell whose byte there is not -1. */
uint32_t vertrix_port_board_mark_filled_4375a0(PORT_SIGNATURE)
{
    Port port;
    uint32_t board = entry->eax;
    uint32_t offset;
    port_open(&port, calls, services, globals, entry);
    port_call_with(&port, 0x4327e0, board + 0x220, board + 0x1de, 0x41, entry->ecx, board + 0xd,
                   board, entry->ebp);
    for (offset = 0; offset < 5 * 13; offset++)
    {
        port_set8(&port, board + offset, 0xb94, port_u8(&port, board + offset, 0x1de) != 0xff);
    }
    return port_return(&port, board + 5 * 13, entry->edx);
}
