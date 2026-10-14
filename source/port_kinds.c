#include "port_kinds.h"

/* Board kind marks, marked cell clearing and bursts, the first turn draw, the computer player's
 * reaction time, match rewards and the effect teardown. */

/* The guard record (0x4ec1ec, `guard`) of a frame routine at `record`. */
static void guard_record(Port *port, uint32_t record, uint32_t guard)
{
    port_set32(port, record, 0, port->env.chain);
    port_set32(port, record, 4, 0x4ec1ec);
    port_set32(port, record, 8, guard);
    port_set32(port, record, 0xc, 0);
}

/* Original 0x435e80: the board's kinds (0x4327e0) marked (+0xb94) for the effect edx: fives for
 * 2, sixes for 1 and 2, others for 0, 1 and 2; empty cells unmarked. eax ends with the last kind
 * and mark, edx past the last column. */
uint32_t vertrix_port_board_mark_effect_kinds_435e80(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x20
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t board = entry->eax;
    uint32_t effect = entry->edx;
    uint32_t eax;
    uint32_t column;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_call_with(&port, 0x4327e0, board + 0x220, board + 0x1de, 0x41, effect, board, entry->edi,
                   ebp);
    eax = board + 0xd;
    port_set32(&port, ebp, -0x1cu, board);
    port_set32(&port, ebp, -0x18u, board + 0xd);
    port_set32(&port, ebp, -0x14u, board + 0x41);
    for (column = 0; column < 5; column++)
    {
        uint32_t cell = port_u32(&port, ebp, -0x1cu);
        uint32_t end = port_u32(&port, ebp, -0x18u);
        while (cell != end)
        {
            uint32_t kind = port_u8(&port, cell, 0x1de);
            uint32_t mark = 0;
            if (kind != 0xff)
            {
                if (kind == 5)
                {
                    mark = effect == 2;
                }
                else if (kind == 6)
                {
                    mark = effect == 2 || effect == 1;
                }
                else
                {
                    mark = effect == 2 || effect == 1 || effect == 0;
                }
            }
            eax = (eax & 0xffff0000u) | (kind << 8) | mark;
            cell++;
            port_set8(&port, cell, 0xb93, mark);
        }
        port_set32(&port, ebp, -0x18u, end + 0xd);
        port_set32(&port, ebp, -0x1cu, port_u32(&port, ebp, -0x1cu) + 0xd);
    }
    return port_return(&port, eax, port_u32(&port, ebp, -0x18u));
}

/* Original 0x435f30: the board's kinds (0x4327e0) and marks (+0xb94) cleared; in each column the
 * first filled cell below the empty top, unless a five, is marked 1. */
uint32_t vertrix_port_board_mark_column_tops_435f30(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x20
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t board = entry->eax;
    uint32_t column;
    uint32_t eax;
    uint32_t esi;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, -0x18u, board);
    port_call_with(&port, 0x4327e0, board + 0x220, board + 0x1de, 0x41, 0, board, entry->edi, ebp);
    for (column = 0; column < 5; column++)
    {
        uint32_t end = board + (column + 1) * 0xd;
        eax = column * 0xd + port_u32(&port, ebp, -0x18u);
        do
        {
            eax++;
            port_set8(&port, eax, 0xb93, 0);
        } while (eax != end);
    }
    esi = port_u32(&port, ebp, -0x18u);
    port_set32(&port, ebp, -0x1cu, esi + 0x41);
    do
    {
        uint32_t count = 0;
        eax = esi;
        if (port_u8(&port, esi, 0x1de) == 0xff)
        {
            do
            {
                eax++;
                count++;
            } while (eax < esi + 0xd && port_u8(&port, eax, 0x1de) == 0xff);
        }
        if (count < 0xd && port_u8(&port, esi + count, 0x1de) != 5)
        {
            port_set8(&port, esi + count, 0xb94, 1);
        }
        esi += 0xd;
    } while (esi != port_u32(&port, ebp, -0x1cu));
    return port_return(&port, eax, entry->edx);
}

/* Original 0x4374e0: each of the 0x436030 marked cells (0x4360b0 gives its column and row into
 * the frame) has its block (+0x220) and companion (+0x87c) destroyed (their method +0 with 2)
 * and cleared. 1 when there were any, otherwise 0. */
uint32_t vertrix_port_board_clear_marked_4374e0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x24
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t board = entry->eax;
    uint32_t count;
    uint32_t done;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    count = port_call_with(&port, 0x436030, board, entry->edx, entry->ebx, entry->ecx, board,
                           entry->edi, ebp);
    port_set32(&port, ebp, -0x18u, count);
    if (count == 0)
    {
        return port_return(&port, 0, entry->edx);
    }
    for (done = 0; done < port_u32(&port, ebp, -0x18u); done++)
    {
        uint32_t cell;
        uint32_t item;
        port_call_with(&port, 0x4360b0, board, done, ebp - 0x20, ebp - 0x1c, board, done, ebp);
        cell = board + port_u32(&port, ebp, -0x20u) * 0x34 + port_u32(&port, ebp, -0x1cu) * 4;
        item = port_u32(&port, cell, 0x220);
        if (item != 0)
        {
            uint32_t methods = port_u32(&port, item, 0x158);
            port_call_with(&port, port_u32(&port, methods, 0), item, 2, ebp - 0x20, methods, board,
                           done, ebp);
        }
        cell = board + port_u32(&port, ebp, -0x20u) * 0x34 + port_u32(&port, ebp, -0x1cu) * 4;
        item = port_u32(&port, cell, 0x87c);
        if (item != 0)
        {
            uint32_t methods = port_u32(&port, item, 0x158);
            port_call_with(&port, port_u32(&port, methods, 0), item, 2, ebp - 0x20, methods, board,
                           done, ebp);
        }
        cell = board + port_u32(&port, ebp, -0x20u) * 0x34 + port_u32(&port, ebp, -0x1cu) * 4;
        port_set32(&port, cell, 0x220, 0);
        cell = board + port_u32(&port, ebp, -0x20u) * 0x34 + port_u32(&port, ebp, -0x1cu) * 4;
        port_set32(&port, cell, 0x87c, 0);
    }
    return port_return(&port, 1, entry->edx);
}

/* Original 0x439080: the first column (of 5) where 0x439140 finds a cell (its column and row into
 * the frame) has it burst: 0x438ef0 with the signed column and row and its block gives the burst
 * (+0xbdc) and the mark is 2; 0. Otherwise 1. */
uint32_t vertrix_port_board_burst_first_439080(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x24
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t board = entry->eax;
    uint32_t column;
    uint32_t burst;
    uint32_t cell;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, -0x18u, 1);
    for (column = 0; column < 5; column++)
    {
        if (port_call_with(&port, 0x439140, board, ebp - 0x20, ebp - 0x1c, column, column, board,
                           ebp) == 1)
        {
            break;
        }
    }
    if (column == 5)
    {
        return port_return(&port, port_u32(&port, ebp, -0x18u), entry->edx);
    }
    cell = board + port_u32(&port, ebp, -0x20u) * 0x34 + port_u32(&port, ebp, -0x1cu) * 4;
    burst = port_call_with(&port, 0x438ef0, board,
                           (uint32_t)(int32_t)(int16_t)port_u16(&port, ebp, -0x20u),
                           (uint32_t)(int32_t)(int16_t)port_u16(&port, ebp, -0x1cu),
                           port_u32(&port, cell, 0x220), column, board, ebp);
    cell = board + port_u32(&port, ebp, -0x20u) * 0x34 + port_u32(&port, ebp, -0x1cu) * 4;
    port_set32(&port, cell, 0xbdc, burst);
    port_set8(&port, board + port_u32(&port, ebp, -0x20u) * 0xd + port_u32(&port, ebp, -0x1cu),
              0xb94, 2);
    return port_return(&port, 0, entry->edx);
}

/* Original 0x43b1a0: whether the player moves first: in a goal game (0x532bc8) one short of the
 * goal 0x532b34, or behind the opponent (+0x3b0, progress +0x178 kept in 0x540f44 and 0x540f48),
 * a draw of 0 or 1 (0x4826c0 on 0x598d48 into 0x540f4c, against 0x540f50 1) decides; otherwise
 * 1. */
uint32_t vertrix_port_player_first_turn_43b1a0(PORT_SIGNATURE)
{
    Port port;
    uint32_t player = entry->eax;
    uint32_t mine;
    uint32_t theirs;
    uint32_t draw;
    port_open(&port, calls, services, globals, entry);
    if (port_u32(&port, 0, 0x532bc8) == 1)
    {
        port_set32(&port, 0, 0x540f44, port_u32(&port, 0, 0x532b34) - 1);
        port_set32(&port, 0, 0x540f48, port_u32(&port, player, 0x178));
        if (port_u32(&port, 0, 0x540f44) == port_u32(&port, 0, 0x540f48))
        {
            goto draw;
        }
    }
    mine = port_u32(&port, player, 0x178) + 1;
    theirs = port_u32(&port, port_u32(&port, player, 0x3b0), 0x178);
    port_set32(&port, 0, 0x540f44, mine);
    port_set32(&port, 0, 0x540f48, theirs);
    if ((int32_t)theirs <= (int32_t)mine)
    {
        return port_return(&port, 1, entry->edx);
    }
draw:
    draw = port_forward(&port, entry, 0x4826c0, 0x598d48, 2, entry->ebx, entry->ecx) & 0xffff;
    port_set32(&port, 0, 0x540f4c, draw);
    port_set32(&port, 0, 0x540f50, 1);
    return port_return(&port, draw == 1, entry->edx);
}

/* Original 0x43b5b0: the computer player's reaction time (+0x458): its skill (+0x488, 0x4f8d38
 * into 0x540f74) and the level 0x532bbc pick the base (0x4f8d84) and range (0x4f8dac); half the
 * range less a ninth of it times the progress +0x17c is added to the base and 0x482770 draws
 * between them on 0x598d48. */
uint32_t vertrix_port_ai_reaction_time_43b5b0(PORT_SIGNATURE)
{
    Port port;
    uint32_t player = entry->eax;
    uint32_t index;
    uint32_t half;
    uint32_t less;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    port_set32(&port, 0, 0x540f74, port_u32(&port, port_u32(&port, player, 0x488) * 4, 0x4f8d38));
    index = port_u32(&port, 0, 0x532bbc) * 0xf0 + port_u32(&port, 0, 0x540f74) * 4;
    port_set32(&port, 0, 0x540f64, port_u32(&port, index, 0x4f8d84));
    port_set32(&port, 0, 0x540f68, port_u32(&port, index, 0x4f8dac));
    half = port_u32(&port, index, 0x4f8dac) >> 1;
    port_set32(&port, 0, 0x540f6c, half);
    less = half * port_u32(&port, player, 0x17c) / 9;
    port_set32(&port, 0, 0x540f70, port_u32(&port, 0, 0x540f6c) - less);
    port_set32(&port, 0, 0x540f64,
               port_u32(&port, 0, 0x540f64) + port_u32(&port, 0, 0x540f6c) - less);
    result = port_forward(&port, entry, 0x482770, 0x598d48, port_u16(&port, 0, 0x540f64),
                          port_u16(&port, 0, 0x540f6c), player);
    port_set32(&port, player, 0x458, result);
    return port_return(&port, result, entry->edx);
}

/* Original 0x43b9c0: the player's match count (+0x180) drops by edx; each time it falls below 1
 * the player scores (0x43b720 and 0x43b800 with 1, the sound 0x4f8190, 0x4726d0, +0x3ac 1) and it
 * rises by 12. Without +0x44c the bonus +0x18c grows by edx (at most 3), otherwise it is 0. */
uint32_t vertrix_port_player_match_reward_43b9c0(PORT_SIGNATURE)
{
    Port port;
    uint32_t player = entry->eax;
    uint32_t amount = entry->edx;
    uint32_t count;
    uint32_t eax = entry->eax;
    uint32_t bonus;
    uint32_t edi = entry->edi;
    port_open(&port, calls, services, globals, entry);
    count = port_u32(&port, player, 0x180) - amount;
    while ((int32_t)count < 1)
    {
        edi = 1;
        port_call_with(&port, 0x43b720, player, 1, count, player, amount, edi, entry->ebp);
        port_call_with(&port, 0x43b800, player, 1, count, player, amount, edi, entry->ebp);
        count += 0xc;
        eax = port_call_with(&port, 0x43c0e0, player, port_u32(&port, 0, 0x4f8190), count, player,
                             amount, edi, entry->ebp);
        eax = port_call_with(&port, 0x4726d0, eax, vertrix_lift_edx, count, player, amount, edi,
                             entry->ebp);
        port_set32(&port, player, 0x3ac, edi);
    }
    port_set32(&port, player, 0x180, count);
    if (port_u32(&port, player, 0x44c) == 1)
    {
        port_set32(&port, player, 0x18c, 0);
        return port_return(&port, eax, 1);
    }
    bonus = port_u32(&port, player, 0x18c) + amount;
    port_set32(&port, player, 0x18c, bonus > 3 ? 3 : bonus);
    return port_return(&port, eax, bonus);
}

/* Original 0x43e1a0: the effect actor's teardown by the flags dl: with bit 2 0x4ccb9f (0x514eb0)
 * and 0x4ca040; otherwise (guarded, 0x514e3c) its methods 0x514e94 (+0x158), 0x43e260, 0x4ac130
 * with 1 and, with bit 1, 0x4ca050 on what it gives. The actor, or that. */
uint32_t vertrix_port_effect_actor_teardown_43e1a0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x48
    };
    Port port;
    uint8_t stack[BELOW + 8];
    uint32_t ebp = entry->esp - 4;
    uint32_t actor = entry->eax;
    uint32_t flags = entry->edx;
    uint32_t guard = 0x514e3c;
    uint32_t result;
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    if ((flags & 4) != 0)
    {
        port_set32(&port, ebp, -0x44u, actor);
        port_set32(&port, ebp, -0x24u, 1);
        result = port_call_with(&port, 0x4ccb9f, actor, 0x514eb0, 1, actor, 0, entry->edi, ebp);
        port_set32(&port, ebp, -0x24u, 0);
        port_call_with(&port, 0x4ca040, result, vertrix_lift_edx, 1, actor, 0, entry->edi, ebp);
        return port_return(&port, actor, vertrix_lift_edx);
    }
    port_set32(&port, actor, 0x158, 0x514e94);
    port_set32(&port, ebp, -0x1cu, actor);
    port_set8(&port, ebp, -0x18u, flags);
    guard_record(&port, ebp - 0x30, guard);
    port_set32(&port, ebp, -0x24u, 3);
    port_call_with(&port, 0x43e260, actor, 0x4ec1ec, flags, actor, guard, 3, ebp);
    port_set32(&port, ebp, -0x24u, 0);
    result = port_call_with(&port, 0x4ac130, actor, 1, flags, actor, guard, 3, ebp);
    port_set32(&port, ebp, -0x24u, 0);
    if ((flags & 2) == 0)
    {
        return port_return(&port, result, 0);
    }
    port_call_with(&port, 0x4ca050, result, 0, flags, result, guard, 3, ebp);
    return port_return(&port, result, vertrix_lift_edx);
}
