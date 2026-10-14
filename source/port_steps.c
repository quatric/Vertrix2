#include "port_steps.h"

/* Actor step handlers and player and board checks. */

/* A store of `size` bytes (0 for none) at `offset` of the actor; size STORE_GLOBAL_WORD stores the
 * dword of the word at the global `value`. */
typedef struct
{
    uint8_t size;
    uint16_t offset;
    uint32_t value;
} Store;

/* A step handler: `before` stored and `first` called before stepping (0x4ac500 and 0x4ac520);
 * when the step is due, 0x4ac5b0 with what 0x4ac540 gives and the `after` stores; then, when
 * `check` gives 0, `then` and the next handler `next` by 0x4ac8f0 (NEXT_LEFT: the edx left by
 * the call before), or nothing more for `no_next`. `finish` (when set) ends either way. */
typedef struct
{
    Store before;
    uint32_t first;
    Store after[2];
    uint32_t check;
    uint32_t next;
    uint32_t finish;
    void (*then)(Port *port, const LiftEntry *entry, uint32_t actor);
    uint8_t no_next;
} Step;

enum
{
    NEXT_LEFT = 0xffffffff,
    STORE_GLOBAL_WORD = 6
};

static void store(Port *port, uint32_t actor, const Store *store)
{
    if (store->size == 1)
    {
        port_set8(port, actor, store->offset, store->value);
    }
    else if (store->size == 2)
    {
        port_set16(port, actor, store->offset, store->value);
    }
    else if (store->size == 4)
    {
        port_set32(port, actor, store->offset, store->value);
    }
    else if (store->size == STORE_GLOBAL_WORD)
    {
        port_set32(port, actor, store->offset, port_u16(port, 0, store->value));
    }
}

static uint32_t actor_step_open(Port *port, const LiftEntry *entry, const Step *step);

static uint32_t actor_step(PORT_SIGNATURE, const Step *step)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    return actor_step_open(&port, entry, step);
}

/* actor_step on a port already open. */
static uint32_t actor_step_open(Port *port, const LiftEntry *entry, const Step *step)
{
    uint32_t actor = entry->eax;
    uint32_t result;
    store(port, actor, &step->before);
    if (step->first != 0)
    {
        port_forward(port, entry, step->first, actor, entry->edx, entry->ebx, actor);
        port_forward(port, entry, 0x4ac500, actor, vertrix_lift_edx, entry->ebx, actor);
    }
    else
    {
        port_forward(port, entry, 0x4ac500, actor, entry->edx, entry->ebx, actor);
    }
    result = port_forward(port, entry, 0x4ac520, actor, vertrix_lift_edx, entry->ebx, actor);
    if (result == 1)
    {
        result = port_forward(port, entry, 0x4ac540, actor, vertrix_lift_edx, entry->ebx, actor);
        port_forward(port, entry, 0x4ac5b0, actor, result, entry->ebx, actor);
        store(port, actor, &step->after[0]);
        store(port, actor, &step->after[1]);
        result = port_forward(port, entry, step->check, actor, vertrix_lift_edx, entry->ebx, actor);
        if (result == 0 && !step->no_next)
        {
            uint32_t next = step->next;
            if (step->then != NULL)
            {
                step->then(port, entry, actor);
            }
            if (next == NEXT_LEFT)
            {
                next = vertrix_lift_edx;
            }
            result = port_forward(port, entry, 0x4ac8f0, actor, next, entry->ebx, actor);
        }
    }
    if (step->finish != 0)
    {
        result =
            port_forward(port, entry, step->finish, actor, vertrix_lift_edx, entry->ebx, actor);
    }
    return port_return(port, result, entry->edx);
}

/* Original 0x444a30: byte +0x45 0 and word +0x46 1, 0x4acc10, no next handler. */
uint32_t vertrix_port_actor_step_flash_444a30(PORT_SIGNATURE)
{
    static const Step step = {{0}, 0, {{1, 0x45, 0}, {2, 0x46, 1}}, 0x4acc10, 0, 0, NULL, 0};
    return actor_step(calls, services, globals, entry, &step);
}

/* Original 0x4479f0: byte +0x93 1 first; byte +0x4f 50 and word +0x50 5, 0x4ad580, next
 * 0x447a50. */
uint32_t vertrix_port_actor_step_fade_4479f0(PORT_SIGNATURE)
{
    static const Step step = {
        {1, 0x93, 1}, 0, {{1, 0x4f, 0x32}, {2, 0x50, 5}}, 0x4ad580, 0x447a50, 0, NULL, 0};
    return actor_step(calls, services, globals, entry, &step);
}

/* Original 0x447a50: words +0x4a 30 and +0x4c 3, 0x4ad530, next 0x447aa0. */
uint32_t vertrix_port_actor_step_rise_447a50(PORT_SIGNATURE)
{
    static const Step step = {{0},  0, {{2, 0x4a, 0x1e}, {2, 0x4c, 3}}, 0x4ad530, 0x447aa0, 0,
                              NULL, 0};
    return actor_step(calls, services, globals, entry, &step);
}

/* Original 0x447aa0: words +0x4a 0 and +0x4c 3, 0x4ad530, next 0x447a50. */
uint32_t vertrix_port_actor_step_fall_447aa0(PORT_SIGNATURE)
{
    static const Step step = {{0}, 0, {{2, 0x4a, 0}, {2, 0x4c, 3}}, 0x4ad530, 0x447a50, 0, NULL, 0};
    return actor_step(calls, services, globals, entry, &step);
}

/* Original 0x44a6d0: byte +0x45 16 and word +0x46 1, 0x4acc10, next 0x44aa20. */
uint32_t vertrix_port_actor_step_flash_44a6d0(PORT_SIGNATURE)
{
    static const Step step = {{0},  0, {{1, 0x45, 0x10}, {2, 0x46, 1}}, 0x4acc10, 0x44aa20, 0,
                              NULL, 0};
    return actor_step(calls, services, globals, entry, &step);
}

/* Original 0x44acd0: the same, next 0x44ad20. */
uint32_t vertrix_port_actor_step_flash_44acd0(PORT_SIGNATURE)
{
    static const Step step = {{0},  0, {{1, 0x45, 0x10}, {2, 0x46, 1}}, 0x4acc10, 0x44ad20, 0,
                              NULL, 0};
    return actor_step(calls, services, globals, entry, &step);
}

/* Original 0x44c2b0: dwords +0x5c 60 and +0x60 4, 0x4ad6e0, next 0x44c310, then 0x4ac8a0. */
uint32_t vertrix_port_piece_child_update_44c2b0(PORT_SIGNATURE)
{
    static const Step step = {
        {0}, 0, {{4, 0x5c, 0x3c}, {4, 0x60, 4}}, 0x4ad6e0, 0x44c310, 0x4ac8a0, NULL, 0};
    return actor_step(calls, services, globals, entry, &step);
}

/* Original 0x44c310: dwords +0x5c 0 and +0x60 4, next 0x44c2b0. */
uint32_t vertrix_port_piece_child_update_44c310(PORT_SIGNATURE)
{
    static const Step step = {{0},  0, {{4, 0x5c, 0}, {4, 0x60, 4}}, 0x4ad6e0, 0x44c2b0, 0x4ac8a0,
                              NULL, 0};
    return actor_step(calls, services, globals, entry, &step);
}

/* Original 0x44c370: dwords +0x5c 0 and +0x60 8, next 0x44c2a0. */
uint32_t vertrix_port_piece_child_update_44c370(PORT_SIGNATURE)
{
    static const Step step = {{0},  0, {{4, 0x5c, 0}, {4, 0x60, 8}}, 0x4ad6e0, 0x44c2a0, 0x4ac8a0,
                              NULL, 0};
    return actor_step(calls, services, globals, entry, &step);
}

/* Original 0x44c680: words +0x4a 0 and +0x4c 4, 0x4ad530, next 0x44c6e0, then 0x4ac8a0. */
uint32_t vertrix_port_actor_step_settle_44c680(PORT_SIGNATURE)
{
    static const Step step = {{0},  0, {{2, 0x4a, 0}, {2, 0x4c, 4}}, 0x4ad530, 0x44c6e0, 0x4ac8a0,
                              NULL, 0};
    return actor_step(calls, services, globals, entry, &step);
}

/* Original 0x44cf70: byte +0x95 1 and 0x4ac1f0 first; 0x4ad530, next 0x44c860, then
 * 0x4ac8a0. */
uint32_t vertrix_port_actor_step_show_44cf70(PORT_SIGNATURE)
{
    static const Step step = {{1, 0x95, 1}, 0x4ac1f0, {{0}, {0}}, 0x4ad530,
                              0x44c860,     0x4ac8a0, NULL,       0};
    return actor_step(calls, services, globals, entry, &step);
}

/* Original 0x438910: 0 unless edx is below ebx (signed); otherwise 0x4327e0 on the 65 cells and
 * whether the last cell (+0x1ea) of any of the five rows is not -1; edx left at +0x41. */
uint32_t vertrix_port_board_any_bottom_438910(PORT_SIGNATURE)
{
    Port port;
    uint32_t board = entry->eax;
    uint32_t row;
    uint32_t count = 0;
    port_open(&port, calls, services, globals, entry);
    if ((int32_t)entry->edx >= (int32_t)entry->ebx)
    {
        return port_return(&port, 0, entry->edx);
    }
    port_forward_esi(&port, entry, 0x4327e0, board + 0x220, board + 0x1de, 0x41, 0, board);
    for (row = 0; row < 5; row++)
    {
        if (port_u8(&port, board + row * 13, 0x1ea) != 0xff)
        {
            count++;
        }
    }
    return port_return(&port, count > 0 ? 1 : 0, board + 0x41);
}

/* Original 0x439140: the last marker 1 (+0xb94) of row ecx: its row at edx and column at ebx
 * (1), or 0; edx left at the cell. */
uint32_t vertrix_port_board_row_last_marker_439140(PORT_SIGNATURE)
{
    Port port;
    uint32_t row = entry->ecx;
    uint32_t start = entry->eax + row * 13;
    int32_t column;
    port_open(&port, calls, services, globals, entry);
    for (column = 12; column >= 0; column--)
    {
        if (port_u8(&port, start + (uint32_t)column, 0xb94) == 1)
        {
            port_set32(&port, entry->edx, 0, row);
            port_set32(&port, entry->ebx, 0, (uint32_t)column);
            return port_return(&port, 1, start + (uint32_t)column);
        }
    }
    return port_return(&port, 0, start - 1);
}

/* Original 0x43a560: remember the kinds of the three children at +0x168 to +0x16a, then
 * 0x43a410 with the signed dl, bl and cl. */
uint32_t vertrix_port_piece_children_remember_and_setup_43a560(PORT_SIGNATURE)
{
    Port port;
    uint32_t piece = entry->eax;
    uint32_t third;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    port_set8(&port, piece, 0x168, port_u8(&port, port_u32(&port, piece, 0x15c), 0x15c));
    port_set8(&port, piece, 0x169, port_u8(&port, port_u32(&port, piece, 0x160), 0x15c));
    third = port_u32(&port, piece, 0x164);
    port_set8(&port, piece, 0x16a, port_u8(&port, third, 0x15c));
    result = port_forward_esi(&port, entry, 0x43a410, piece, (uint32_t)(int32_t)(int8_t)entry->edx,
                              (uint32_t)(int32_t)(int8_t)entry->ebx,
                              (uint32_t)(int32_t)(int8_t)entry->ecx, third);
    return port_return(&port, result, vertrix_lift_edx);
}

/* Original 0x43ab80: 3 when the player (byte +0x4c5) is out, 5 when the partner (+0x3b0) is;
 * otherwise by 0x427ae0 on the region +0x450: 3 for -1, 4 for 0, else 5. */
uint32_t vertrix_port_object_region_verdict_43ab80(PORT_SIGNATURE)
{
    Port port;
    uint32_t player = entry->eax;
    uint32_t region;
    uint32_t verdict;
    port_open(&port, calls, services, globals, entry);
    if (port_u8(&port, player, 0x4c5) == 0)
    {
        return port_return(&port, 3, entry->edx);
    }
    if (port_u8(&port, port_u32(&port, player, 0x3b0), 0x4c5) == 0)
    {
        return port_return(&port, 5, entry->edx);
    }
    region = port_u32(&port, player, 0x450);
    verdict = port_forward(&port, entry, 0x427ae0, region, player, entry->ebx, region);
    if (verdict == 0xffffffff)
    {
        return port_return(&port, 3, entry->edx);
    }
    return port_return(&port, verdict != 0 ? 5 : 4, entry->edx);
}

/* Original 0x43b810: set the level +0x17c to edx (0 when negative, at most 9); when it changes,
 * 0x431400 on the board +0x15c (1); otherwise 0. */
uint32_t vertrix_port_player_set_level_43b810(PORT_SIGNATURE)
{
    Port port;
    uint32_t player = entry->eax;
    uint32_t old;
    uint32_t level = entry->edx;
    port_open(&port, calls, services, globals, entry);
    old = port_u32(&port, player, 0x17c);
    if ((int32_t)level < 0)
    {
        level = 0;
    }
    else if ((int32_t)level >= 0xa)
    {
        level = 9;
    }
    port_set32(&port, player, 0x17c, level);
    if (old == level)
    {
        return port_return(&port, 0, entry->edx);
    }
    port_forward(&port, entry, 0x431400, port_u32(&port, player, 0x15c), level, old, level);
    return port_return(&port, 1, vertrix_lift_edx);
}

/* Original 0x43bc90: unless 0x43bd40 on the partner (+0x3b0) gives 1, when its state byte +0x4cc
 * is 1 or 4, enter 0x452070 by 0x43bb60, set the state to 5 and 0x4ac8f0 (1); otherwise 0. */
uint32_t vertrix_port_player_enter_452070_43bc90(PORT_SIGNATURE)
{
    Port port;
    uint32_t player = entry->eax;
    uint32_t state;
    port_open(&port, calls, services, globals, entry);
    if (port_forward(&port, entry, 0x43bd40, port_u32(&port, player, 0x3b0), entry->edx, entry->ebx,
                     player) == 1)
    {
        return port_return(&port, 0, entry->edx);
    }
    state = port_u8(&port, port_u32(&port, player, 0x3b0), 0x4cc);
    if (state != 1 && state != 4)
    {
        return port_return(&port, 0, entry->edx);
    }
    port_forward(&port, entry, 0x43bb60, player, 0x452070, entry->ebx, player);
    port_set8(&port, player, 0x4cc, 5);
    port_forward(&port, entry, 0x4ac8f0, player, vertrix_lift_edx, entry->ebx, player);
    return port_return(&port, 1, entry->edx);
}

/* Original 0x43d130: a random kind below 6 (below 5 unless the mode +0x4c8 is 0x22 or 0x28) by
 * 0x4826c0 on 0x598d30, stored at edx; a 5 in mode 0x22 becomes 6. */
uint32_t vertrix_port_player_random_kind_43d130(PORT_SIGNATURE)
{
    Port port;
    uint32_t player = entry->eax;
    uint32_t mode;
    uint32_t limit;
    uint32_t drawn;
    uint32_t kind;
    uint32_t edx;
    port_open(&port, calls, services, globals, entry);
    mode = port_u32(&port, player, 0x4c8);
    limit = mode == 0x22 || mode == 0x28 ? 6 : 5;
    drawn = port_forward(&port, entry, 0x4826c0, 0x598d30, limit, entry->edx, player);
    edx = vertrix_lift_edx;
    kind = drawn & 0xff;
    if (kind == 5)
    {
        edx = port_u32(&port, player, 0x4c8);
        if (edx == 0x22)
        {
            kind = 6;
        }
    }
    port_set8(&port, entry->edx, 0, kind);
    return port_return(&port, (drawn & 0xffff00ffu) | (kind << 8), edx);
}

/* Original 0x43d260: generate the next three kinds into 0x540f84 to 0x540f86 by 0x43d180 and
 * show them (signed) on the preview +0x3b4 by 0x43a4f0. */
uint32_t vertrix_port_player_generate_preview_43d260(PORT_SIGNATURE)
{
    Port port;
    uint32_t player = entry->eax;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    port_forward_esi(&port, entry, 0x43d180, player, 0x540f84, 0x540f85, 0x540f86, player);
    result = port_forward_esi(&port, entry, 0x43a4f0, port_u32(&port, player, 0x3b4),
                              (uint32_t)(int32_t)(int8_t)port_u8(&port, 0, 0x540f84),
                              (uint32_t)(int32_t)(int8_t)port_u8(&port, 0, 0x540f85),
                              (uint32_t)(int32_t)(int8_t)port_u8(&port, 0, 0x540f86), player);
    return port_return(&port, result, entry->edx);
}

/* Original 0x43d2b0: the overlay by 0x42ff50 on the board +0x15c with the image of 0x532a70
 * (0x5347a0); edx 0 for kind 1, 1 for kind 2. */
uint32_t vertrix_port_player_create_overlay_43d2b0(PORT_SIGNATURE)
{
    Port port;
    uint32_t kind;
    uint32_t edx = entry->edx;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    kind = port_u32(&port, entry->eax, 0);
    if (kind == 1)
    {
        edx = 0;
    }
    else if (kind == 2)
    {
        edx = 1;
    }
    result = port_forward(&port, entry, 0x42ff50, port_u32(&port, entry->eax, 0x15c), edx,
                          port_u32(&port, port_u32(&port, 0, 0x532a70) * 4, 0x5347a0), kind);
    return port_return(&port, result, entry->edx);
}

/* Original 0x448610: 0x4ac500 and 0x4ac510 when 0x4ac520 gives 1 (on the edx each leaves); the
 * word +0x48 60 and, unless 0x476480 finds 0x74 in 0x54d640, the callback +0x184 (when set) and
 * the handler 0x448260 by 0x4ac8f0. */
uint32_t vertrix_port_actor_wait_point_448610(PORT_SIGNATURE)
{
    Port port;
    uint32_t actor = entry->eax;
    uint32_t callback;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    port_forward(&port, entry, 0x4ac500, actor, actor, entry->ebx, actor);
    if (port_forward(&port, entry, 0x4ac520, vertrix_lift_edx, vertrix_lift_edx, entry->ebx,
                     actor) == 1)
    {
        port_forward(&port, entry, 0x4ac510, vertrix_lift_edx, vertrix_lift_edx, entry->ebx, actor);
    }
    port_set16(&port, actor, 0x48, 0x3c);
    result = port_forward(&port, entry, 0x476480, 0x54d640, 0x74, entry->ebx, actor);
    if (result == 0)
    {
        callback = port_u32(&port, actor, 0x184);
        if (callback != 0)
        {
            port_forward(&port, entry, callback, actor, actor, callback, actor);
        }
        result = port_forward(&port, entry, 0x4ac8f0, actor, 0x448260, callback, actor);
    }
    return port_return(&port, result, entry->edx);
}

/* Original 0x448740: move from the x +0xe to the y of 0x558c7c (+8) in steps of 8, show it by
 * 0x4ac7b0 (2) and the handler 0x448790 by 0x4ac510 and 0x4ac8f0. */
uint32_t vertrix_port_actor_move_to_point_448740(PORT_SIGNATURE)
{
    Port port;
    uint32_t actor = entry->eax;
    uint32_t y;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    y = port_u16(&port, port_u32(&port, 0, 0x558c7c), 8);
    port_set16(&port, actor, 0x12, 8);
    port_set16(&port, actor, 0x18, y);
    port_set16(&port, actor, 0x10, port_u16(&port, actor, 0xe));
    port_set16(&port, actor, 0x1a, 8);
    port_forward(&port, entry, 0x4ac7b0, actor, 2, entry->ebx, actor);
    port_forward(&port, entry, 0x4ac510, actor, 0x448790, entry->ebx, actor);
    result = port_forward(&port, entry, 0x4ac8f0, actor, vertrix_lift_edx, entry->ebx, actor);
    return port_return(&port, result, entry->edx);
}

/* Original 0x449460: when 0x532a9c is 1, 0x4adfe0, the images 0x544a18 by 0x4ac8d0, the frame
 * set edx by 0x4ac710, the handler 0x4494c0 by 0x4ac8a0, clear bytes +0x52 and +0x94 and
 * 0x4ac8f0 (1); otherwise 0. */
uint32_t vertrix_port_actor_restart_449460(PORT_SIGNATURE)
{
    Port port;
    uint32_t actor = entry->eax;
    uint32_t frames = entry->edx;
    port_open(&port, calls, services, globals, entry);
    if (port_u32(&port, 0, 0x532a9c) != 1)
    {
        return port_return(&port, 0, entry->edx);
    }
    port_forward(&port, entry, 0x4adfe0, actor, frames, frames, actor);
    port_forward(&port, entry, 0x4ac8d0, actor, 0x544a18, frames, actor);
    port_forward(&port, entry, 0x4ac710, actor, frames, frames, actor);
    port_forward(&port, entry, 0x4ac8a0, actor, 0x4494c0, frames, actor);
    port_set8(&port, actor, 0x52, 0);
    port_set8(&port, actor, 0x94, 0);
    port_forward(&port, entry, 0x4ac8f0, actor, vertrix_lift_edx, frames, actor);
    return port_return(&port, 1, vertrix_lift_edx);
}

/* Unless 0x449460 restarts with the frame set at `first`, 0x4493d0 (0x74), the handler
 * `handler` by 0x4ac8f0 unless 0x476480 finds it in 0x54d640, and the frame set at `second` by
 * 0x449390; then +0x58 set to 10 when `delay` is set. */
static uint32_t actor_restart_or_wait(PORT_SIGNATURE, uint32_t first, uint32_t handler,
                                      uint32_t second, int delay)
{
    Port port;
    uint32_t actor = entry->eax;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    result =
        port_forward(&port, entry, 0x449460, actor, port_u32(&port, 0, first), entry->ebx, actor);
    if (result == 1)
    {
        return port_return(&port, result, entry->edx);
    }
    port_forward(&port, entry, 0x4493d0, actor, 0x74, entry->ebx, actor);
    if (port_forward(&port, entry, 0x476480, 0x54d640, vertrix_lift_edx, entry->ebx, actor) == 0)
    {
        port_forward(&port, entry, 0x4ac8f0, actor, handler, entry->ebx, actor);
    }
    result =
        port_forward(&port, entry, 0x449390, actor, port_u32(&port, 0, second), entry->ebx, actor);
    if (delay)
    {
        port_set32(&port, actor, 0x58, 0xa);
    }
    return port_return(&port, result, entry->edx);
}

/* Original 0x449a50: frame sets 0x4fbed8 and 0x4fbedc, handler 0x4497c0. */
uint32_t vertrix_port_actor_restart_or_wait_449a50(PORT_SIGNATURE)
{
    return actor_restart_or_wait(calls, services, globals, entry, 0x4fbed8, 0x4497c0, 0x4fbedc, 0);
}

/* Original 0x449ff0: frame sets 0x4fbef0 and 0x4fbef4, handler 0x449d60. */
uint32_t vertrix_port_actor_restart_or_wait_449ff0(PORT_SIGNATURE)
{
    return actor_restart_or_wait(calls, services, globals, entry, 0x4fbef0, 0x449d60, 0x4fbef4, 0);
}

/* Original 0x44a340: frame sets 0x4fbf08 and 0x4fbf0c, handler 0x44a3a0, then +0x58 10 after a
 * wait. */
uint32_t vertrix_port_actor_restart_or_wait_44a340(PORT_SIGNATURE)
{
    return actor_restart_or_wait(calls, services, globals, entry, 0x4fbf08, 0x44a3a0, 0x4fbf0c, 1);
}

/* Original 0x44a520: frame sets 0x4fbf08 and 0x4fbf0c, handler 0x44a2a0. */
uint32_t vertrix_port_actor_restart_or_wait_44a520(PORT_SIGNATURE)
{
    return actor_restart_or_wait(calls, services, globals, entry, 0x4fbf08, 0x44a2a0, 0x4fbf0c, 0);
}

/* 0x4ac500, and 0x4ac510 when 0x4ac520 gives 1 (on the edx each leaves); then, unless the kind
 * byte +0x15c (signed) already is `global`, take it and 0x4adfe0 with it. */
static uint32_t kind_follow(PORT_SIGNATURE, uint32_t global)
{
    Port port;
    uint32_t actor = entry->eax;
    uint32_t kind;
    uint32_t wanted;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    port_forward(&port, entry, 0x4ac500, actor, actor, entry->ebx, actor);
    if (port_forward(&port, entry, 0x4ac520, vertrix_lift_edx, vertrix_lift_edx, entry->ebx,
                     actor) == 1)
    {
        port_forward(&port, entry, 0x4ac510, vertrix_lift_edx, vertrix_lift_edx, entry->ebx, actor);
    }
    kind = (uint32_t)(int32_t)(int8_t)port_u8(&port, actor, 0x15c);
    wanted = port_u32(&port, 0, global);
    if (kind == wanted)
    {
        return port_return(&port, kind, entry->edx);
    }
    port_set8(&port, actor, 0x15c, port_u8(&port, 0, global));
    result = port_forward(&port, entry, 0x4adfe0, actor, wanted, entry->ebx, actor);
    return port_return(&port, result, entry->edx);
}

/* Original 0x44a570: the kind 0x532a68. */
uint32_t vertrix_port_actor_kind_follow_44a570(PORT_SIGNATURE)
{
    return kind_follow(calls, services, globals, entry, 0x532a68);
}

/* Original 0x44a5c0: the kind 0x532a6c. */
uint32_t vertrix_port_actor_kind_follow_44a5c0(PORT_SIGNATURE)
{
    return kind_follow(calls, services, globals, entry, 0x532a6c);
}

/* Original 0x44ab00: 0x4ac500, and 0x4ac510 when 0x4ac520 gives 1; then, unless 0x476480 finds
 * 0x74 in 0x54d640, the handler 0x44aa20 by 0x4ac8f0. */
uint32_t vertrix_port_actor_step_then_wait_44ab00(PORT_SIGNATURE)
{
    Port port;
    uint32_t actor = entry->eax;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    port_forward(&port, entry, 0x4ac500, actor, actor, entry->ebx, actor);
    if (port_forward(&port, entry, 0x4ac520, vertrix_lift_edx, vertrix_lift_edx, entry->ebx,
                     actor) == 1)
    {
        port_forward(&port, entry, 0x4ac510, vertrix_lift_edx, vertrix_lift_edx, entry->ebx, actor);
    }
    result = port_forward(&port, entry, 0x476480, 0x54d640, 0x74, entry->ebx, actor);
    if (result == 0)
    {
        result = port_forward(&port, entry, 0x4ac8f0, actor, 0x44aa20, entry->ebx, actor);
    }
    return port_return(&port, result, entry->edx);
}

/* The 0x4adfa0 call with edx 0 before the next handler. */
static void then_reset(Port *port, const LiftEntry *entry, uint32_t actor)
{
    port_forward(port, entry, 0x4adfa0, actor, 0, entry->ebx, actor);
}

/* +0x74 and +0x78 set and +0x70 cleared before the next handler. */
static void then_link(Port *port, const LiftEntry *entry, uint32_t actor)
{
    (void)entry;
    port_set32(port, actor, 0x74, 1);
    port_set32(port, actor, 0x70, 0);
    port_set32(port, actor, 0x78, 1);
}

/* 0x4adfa0 (edx 0) and the toggle +0x7c flipped before the next handler. */
static void then_reset_flip(Port *port, const LiftEntry *entry, uint32_t actor)
{
    port_forward(port, entry, 0x4adfa0, actor, 0, entry->ebx, actor);
    port_set32(port, actor, 0x7c, 1 - port_u32(port, actor, 0x7c));
}

/* The handler 0x450920 by 0x4ac510, +0x124 set and 0x4adfe0 before the next call. */
static void then_companion(Port *port, const LiftEntry *entry, uint32_t actor)
{
    port_forward(port, entry, 0x4ac510, actor, 0x450920, entry->ebx, actor);
    port_set32(port, actor, 0x124, 1);
    port_forward(port, entry, 0x4adfe0, actor, vertrix_lift_edx, entry->ebx, actor);
}

/* Original 0x44cfd0: byte +0x95 1 and 0x4ac1f0 first; 0x4ad6e0, next 0x44d030, then
 * 0x4ac8a0. */
uint32_t vertrix_port_actor_step_show_44cfd0(PORT_SIGNATURE)
{
    static const Step step = {{1, 0x95, 1}, 0x4ac1f0, {{0}, {0}}, 0x4ad6e0,
                              0x44d030,     0x4ac8a0, NULL,       0};
    return actor_step(calls, services, globals, entry, &step);
}

/* Original 0x44f390: byte +0x94 0 and 0x4ac1f0 first; 0x4accc0 without a next handler, then
 * 0x4ac8a0. */
uint32_t vertrix_port_block_cycle_update_44f390(PORT_SIGNATURE)
{
    static const Step step = {{1, 0x94, 0}, 0x4ac1f0, {{0}, {0}}, 0x4accc0, 0, 0x4ac8a0, 0, 1};
    return actor_step(calls, services, globals, entry, &step);
}

/* Original 0x44f3e0: the same with 0x4acd30. */
uint32_t vertrix_port_block_cycle_update_44f3e0(PORT_SIGNATURE)
{
    static const Step step = {{1, 0x94, 0}, 0x4ac1f0, {{0}, {0}}, 0x4acd30, 0, 0x4ac8a0, 0, 1};
    return actor_step(calls, services, globals, entry, &step);
}

/* Original 0x44fbb0: words +0x4a -100 and +0x4c 2, 0x4ad530, next 0x44fad0. */
uint32_t vertrix_port_number_transition_update_44fbb0(PORT_SIGNATURE)
{
    static const Step step = {{0},  0, {{2, 0x4a, 0xff9c}, {2, 0x4c, 2}}, 0x4ad530, 0x44fad0, 0,
                              NULL, 0};
    return actor_step(calls, services, globals, entry, &step);
}

/* Original 0x44fd60: the same, next 0x44fc60. */
uint32_t vertrix_port_number_transition_configured_44fd60(PORT_SIGNATURE)
{
    static const Step step = {{0},  0, {{2, 0x4a, 0xff9c}, {2, 0x4c, 2}}, 0x4ad530, 0x44fc60, 0,
                              NULL, 0};
    return actor_step(calls, services, globals, entry, &step);
}

/* Original 0x44fe30: words +0x4a -100 and +0x4c 4, next 0x44fdb0. */
uint32_t vertrix_port_number_transition_configured_44fe30(PORT_SIGNATURE)
{
    static const Step step = {{0},  0, {{2, 0x4a, 0xff9c}, {2, 0x4c, 4}}, 0x4ad530, 0x44fdb0, 0,
                              NULL, 0};
    return actor_step(calls, services, globals, entry, &step);
}

/* Original 0x44fff0: 0x4ad580, next 0x450040. */
uint32_t vertrix_port_ui_indicator_storage_update_44fff0(PORT_SIGNATURE)
{
    static const Step step = {{0}, 0, {{0}, {0}}, 0x4ad580, 0x450040, 0, NULL, 0};
    return actor_step(calls, services, globals, entry, &step);
}

/* Original 0x4500b0: 0x4ad580, 0x4adfa0 (edx 0) and next 0x450100. */
uint32_t vertrix_port_ui_indicator_storage_update_4500b0(PORT_SIGNATURE)
{
    static const Step step = {{0}, 0, {{0}, {0}}, 0x4ad580, 0x450100, 0, then_reset, 0};
    return actor_step(calls, services, globals, entry, &step);
}

/* Original 0x4501a0: 0x4ad530, the link flags and next 0x450200. */
uint32_t vertrix_port_ui_border_storage_update_4501a0(PORT_SIGNATURE)
{
    static const Step step = {{0}, 0, {{0}, {0}}, 0x4ad530, 0x450200, 0, then_link, 0};
    return actor_step(calls, services, globals, entry, &step);
}

/* Original 0x4508c0: 0x4acab0, the handler 0x450920, +0x124 and 0x4adfe0, then 0x4ac8f0 with the
 * edx that leaves. */
uint32_t vertrix_port_ui_companion_storage_update_4508c0(PORT_SIGNATURE)
{
    static const Step step = {{0}, 0, {{0}, {0}}, 0x4acab0, NEXT_LEFT, 0, then_companion, 0};
    return actor_step(calls, services, globals, entry, &step);
}

/* Original 0x450b90: 0x4ad530, the link flags and next 0x450bf0. */
uint32_t vertrix_port_linked_alternating_update_450b90(PORT_SIGNATURE)
{
    static const Step step = {{0}, 0, {{0}, {0}}, 0x4ad530, 0x450bf0, 0, then_link, 0};
    return actor_step(calls, services, globals, entry, &step);
}

/* Original 0x450c70: 0x4ad530, 0x4adfa0 (edx 0), the toggle +0x7c flipped and next
 * 0x450a10. */
uint32_t vertrix_port_linked_alternating_update_450c70(PORT_SIGNATURE)
{
    static const Step step = {{0}, 0, {{0}, {0}}, 0x4ad530, 0x450a10, 0, then_reset_flip, 0};
    return actor_step(calls, services, globals, entry, &step);
}

/* Original 0x44fe80: clear +0x58 and keep the player's (slot +4 at 0x540f88) +0x18c at +0x64;
 * when 0x43ba70 on it gives 1, the handler 0x44fed0 by 0x4ac510 and 0x4ac8f0. */
uint32_t vertrix_port_player_indicator_update_44fe80(PORT_SIGNATURE)
{
    Port port;
    uint32_t object = entry->eax;
    uint32_t player;
    uint32_t value;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    player = port_u32(&port, port_u32(&port, object, 4) * 4, 0x540f88);
    port_set32(&port, object, 0x58, 0);
    value = port_u32(&port, player, 0x18c);
    port_set32(&port, object, 0x64, value);
    result = port_forward(&port, entry, 0x43ba70, player, value, entry->ebx, object);
    if (result != 1)
    {
        return port_return(&port, result, entry->edx);
    }
    port_forward(&port, entry, 0x4ac510, object, 0x44fed0, entry->ebx, object);
    result = port_forward(&port, entry, 0x4ac8f0, object, vertrix_lift_edx, entry->ebx, object);
    return port_return(&port, result, entry->edx);
}

/* Original 0x44fed0: 0x4ac500, and when 0x4ac520 gives 1, 0x4ac510, 0x4ac610, +0x58 set, +0x64
 * cleared, the event 0x4f81a0 for the player by 0x43c0e0 and the handler 0x44ff30 by
 * 0x4ac8f0. */
uint32_t vertrix_port_player_indicator_update_44fed0(PORT_SIGNATURE)
{
    Port port;
    uint32_t object = entry->eax;
    uint32_t slot;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    port_forward(&port, entry, 0x4ac500, object, entry->edx, entry->ebx, object);
    result = port_forward(&port, entry, 0x4ac520, object, vertrix_lift_edx, entry->ebx, object);
    if (result != 1)
    {
        return port_return(&port, result, entry->edx);
    }
    port_forward(&port, entry, 0x4ac510, object, vertrix_lift_edx, entry->ebx, object);
    port_forward(&port, entry, 0x4ac610, object, vertrix_lift_edx, entry->ebx, object);
    port_set32(&port, object, 0x58, 1);
    slot = port_u32(&port, object, 4);
    port_set32(&port, object, 0x64, 0);
    port_forward(&port, entry, 0x43c0e0, port_u32(&port, slot * 4, 0x540f88),
                 port_u32(&port, 0, 0x4f81a0), entry->ebx, object);
    result = port_forward(&port, entry, 0x4ac8f0, object, 0x44ff30, entry->ebx, object);
    return port_return(&port, result, entry->edx);
}

/* Original 0x44ff90: when the slot (+4 in 0x54671c by 0x4b5eb0) has reached +0x58 (its +0x64),
 * show it (byte +0x52 13, 0x4ac510, bytes +0x4e 0 and +0x4f 100, word +0x50 3, 0x4adfa0 with 1)
 * and the handler 0x44fff0 by 0x4ac8f0. */
uint32_t vertrix_port_ui_indicator_storage_update_44ff90(PORT_SIGNATURE)
{
    Port port;
    uint32_t object = entry->eax;
    uint32_t found;
    uint32_t value;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    found = port_forward(&port, entry, 0x4b5eb0, 0x54671c, port_u32(&port, object, 4), entry->ebx,
                         object);
    if (found == 0)
    {
        return port_return(&port, 0, entry->edx);
    }
    value = port_u32(&port, found, 0x64);
    if ((int32_t)value < (int32_t)port_u32(&port, object, 0x58))
    {
        return port_return(&port, value, entry->edx);
    }
    port_set8(&port, object, 0x52, 0xd);
    port_forward(&port, entry, 0x4ac510, object, vertrix_lift_edx, entry->ebx, object);
    port_set8(&port, object, 0x4e, 0);
    port_set8(&port, object, 0x4f, 0x64);
    port_set16(&port, object, 0x50, 3);
    port_forward(&port, entry, 0x4adfa0, object, 1, entry->ebx, object);
    result = port_forward(&port, entry, 0x4ac8f0, object, 0x44fff0, entry->ebx, object);
    return port_return(&port, result, entry->edx);
}

/* Original 0x4507e0: 0x4ac500, and when 0x4ac520 gives 1, 0x4ac510, +0x58 1, +0x64 and +0x70 12
 * and the handler 0x450830 by 0x4ac8f0. */
uint32_t vertrix_port_player_countdown_update_4507e0(PORT_SIGNATURE)
{
    Port port;
    uint32_t object = entry->eax;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    port_forward(&port, entry, 0x4ac500, object, entry->edx, entry->ebx, object);
    result = port_forward(&port, entry, 0x4ac520, object, vertrix_lift_edx, entry->ebx, object);
    if (result != 1)
    {
        return port_return(&port, result, entry->edx);
    }
    port_forward(&port, entry, 0x4ac510, object, vertrix_lift_edx, entry->ebx, object);
    port_set32(&port, object, 0x58, 1);
    port_set32(&port, object, 0x64, 0xc);
    port_set32(&port, object, 0x70, 0xc);
    result = port_forward(&port, entry, 0x4ac8f0, object, 0x450830, entry->ebx, object);
    return port_return(&port, result, entry->edx);
}

/* Original 0x450860: when the slot has not reached +0x58, move to the y 0x533d78 from +0xa at
 * speed 1, 0x4adfa0 with 1, the handler 0x4508c0 by 0x4ac510 and 0x4ac8f0. */
uint32_t vertrix_port_ui_companion_storage_update_450860(PORT_SIGNATURE)
{
    Port port;
    uint32_t object = entry->eax;
    uint32_t found;
    uint32_t value;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    found = port_forward(&port, entry, 0x4b5eb0, 0x54671c, port_u32(&port, object, 4), entry->ebx,
                         object);
    if (found == 0)
    {
        return port_return(&port, 0, entry->edx);
    }
    value = port_u32(&port, found, 0x64);
    if ((int32_t)value >= (int32_t)port_u32(&port, object, 0x58))
    {
        return port_return(&port, value, entry->edx);
    }
    port_set16(&port, object, 0x16, port_u16(&port, 0, 0x533d78));
    port_set16(&port, object, 0x18, port_u16(&port, object, 0xa));
    port_set16(&port, object, 0x1a, 1);
    port_forward(&port, entry, 0x4adfa0, object, 1, entry->ebx, object);
    port_forward(&port, entry, 0x4ac510, object, 0x4508c0, entry->ebx, object);
    result = port_forward(&port, entry, 0x4ac8f0, object, vertrix_lift_edx, entry->ebx, object);
    return port_return(&port, result, entry->edx);
}

/* Original 0x450b30: 0x4ac600, and when 0x4ac620 gives 1, 0x4ac610 with 1, 0x4adfa0, the words
 * +0x48 -40, +0x4a 5 and +0x4c 1, the handler 0x450b90 by 0x4ac510 and 0x4ac8f0. */
uint32_t vertrix_port_linked_alternating_update_450b30(PORT_SIGNATURE)
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
    port_forward(&port, entry, 0x4ac610, object, 1, entry->ebx, object);
    port_forward(&port, entry, 0x4adfa0, object, vertrix_lift_edx, entry->ebx, object);
    port_set16(&port, object, 0x48, 0xffd8);
    port_set16(&port, object, 0x4a, 5);
    port_set16(&port, object, 0x4c, 1);
    port_forward(&port, entry, 0x4ac510, object, 0x450b90, entry->ebx, object);
    result = port_forward(&port, entry, 0x4ac8f0, object, vertrix_lift_edx, entry->ebx, object);
    return port_return(&port, result, entry->edx);
}

/* The second method of the child +0x15c with edx, ebx and ecx given; its result. */
static uint32_t child_method(Port *port, const LiftEntry *entry, uint32_t child, uint32_t edx,
                             uint32_t ebx, uint32_t ecx)
{
    uint32_t methods = port_u32(port, child, 0x158);
    return port_forward(port, entry, port_u32(port, methods, 4), child, edx, ebx, ecx);
}

/* Original 0x451520: unless 0x4334b0 on the child holds, keep what 0x433550 gives at its byte
 * +0x838, set its handler 0x451580 by 0x433e20 and 0x4ac8f0; then the child update. */
uint32_t vertrix_port_state_gate_451520(PORT_SIGNATURE)
{
    Port port;
    uint32_t object = entry->eax;
    uint32_t child;
    uint32_t methods;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    child = port_u32(&port, object, 0x15c);
    if (port_forward(&port, entry, 0x4334b0, child, entry->edx, object, child) == 0)
    {
        result = port_forward(&port, entry, 0x433550, child, vertrix_lift_edx, object, child);
        port_set8(&port, child, 0x838, result);
        port_forward(&port, entry, 0x433e20, child, 0x451580, object, child);
        port_forward(&port, entry, 0x4ac8f0, object, vertrix_lift_edx, object, child);
    }
    methods = port_u32(&port, child, 0x158);
    result = port_forward(&port, entry, port_u32(&port, methods, 4), child, vertrix_lift_edx,
                          methods, child);
    return port_return(&port, result, entry->edx);
}

/* Original 0x451630: when 0x42eca0 and 0x42ecc0 both find 0x44c860 on the child, its handler
 * 0x4517c0 by 0x42ebe0 and 0x4ac8f0; then the child update. */
uint32_t vertrix_port_state_check_451630(PORT_SIGNATURE)
{
    Port port;
    uint32_t object = entry->eax;
    uint32_t child;
    uint32_t methods;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    child = port_u32(&port, object, 0x15c);
    if (port_forward(&port, entry, 0x42eca0, child, 0x44c860, object, child) != 0 &&
        port_forward(&port, entry, 0x42ecc0, child, 0x44c860, object, child) != 0)
    {
        port_forward(&port, entry, 0x42ebe0, child, 0x4517c0, object, child);
        port_forward(&port, entry, 0x4ac8f0, object, vertrix_lift_edx, object, child);
    }
    methods = port_u32(&port, child, 0x158);
    result = port_forward(&port, entry, port_u32(&port, methods, 4), child, vertrix_lift_edx,
                          methods, child);
    return port_return(&port, result, entry->edx);
}

/* Original 0x451dd0: unless 0x42a1b0 finds a marked choice in the grid +0x3b8, the handler
 * 0x451e20 by 0x4ac8f0; then the child update. */
uint32_t vertrix_port_state_choice_check_451dd0(PORT_SIGNATURE)
{
    Port port;
    uint32_t object = entry->eax;
    uint32_t child;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    child = port_u32(&port, object, 0x15c);
    if (port_forward(&port, entry, 0x42a1b0, port_u32(&port, object, 0x3b8), entry->edx, child,
                     object) == 0)
    {
        port_forward(&port, entry, 0x4ac8f0, object, 0x451e20, child, object);
    }
    result =
        child_method(&port, entry, child, vertrix_lift_edx, child, port_u32(&port, child, 0x158));
    return port_return(&port, result, entry->edx);
}

/* The child update (method +4 of +0x15c, edx its methods) and 0x43bbf0 on the player. */
static uint32_t effect_finish(Port *port, const LiftEntry *entry, uint32_t player, uint32_t child,
                              uint32_t ebx, uint32_t ecx, uint32_t esi)
{
    uint32_t methods = port_u32(port, child, 0x158);
    port_forward_esi(port, entry, port_u32(port, methods, 4), child, methods, ebx, ecx, esi);
    return port_forward_esi(port, entry, 0x43bbf0, player, vertrix_lift_edx, ebx, ecx, esi);
}

/* The effect gate: `check` on the partner +0x3b0 (the player itself for `own`) with the dword at
 * `field` (negated for `negate`); when it gives 1 the event at `event` by 0x43c0e0 (and 0x43ac00
 * with `apply`), otherwise 0x43acd0; then the child update and 0x43bbf0. */
static uint32_t effect_gate(PORT_SIGNATURE, uint32_t check, int own, uint32_t field, int negate,
                            uint32_t event, int apply)
{
    Port port;
    uint32_t player = entry->eax;
    uint32_t amount;
    uint32_t child;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    amount = port_u32(&port, player, field);
    if (negate)
    {
        amount = 0 - amount;
    }
    child = port_u32(&port, player, 0x15c);
    if (port_forward_esi(&port, entry, check, own ? player : port_u32(&port, player, 0x3b0), amount,
                         child, player, player) == 1)
    {
        port_forward_esi(&port, entry, 0x43c0e0, player, port_u32(&port, 0, event), child, player,
                         player);
        if (apply)
        {
            port_forward_esi(&port, entry, 0x43ac00, player, vertrix_lift_edx, child, player,
                             player);
        }
    }
    else
    {
        port_forward_esi(&port, entry, 0x43acd0, player, vertrix_lift_edx, child, player, player);
    }
    result = effect_finish(&port, entry, player, child, child, player, player);
    return port_return(&port, result, entry->edx);
}

/* Original 0x452830: 0x43b800 on the player with -+0x3bc, the event 0x4f8194. */
uint32_t vertrix_port_effect_negated_gate_452830(PORT_SIGNATURE)
{
    return effect_gate(calls, services, globals, entry, 0x43b800, 1, 0x3bc, 1, 0x4f8194, 0);
}

/* Original 0x452880: 0x43b800 on the partner with +0x3c0, the event 0x4f8198 and 0x43ac00. */
uint32_t vertrix_port_effect_value_gate_452880(PORT_SIGNATURE)
{
    return effect_gate(calls, services, globals, entry, 0x43b800, 0, 0x3c0, 0, 0x4f8198, 1);
}

/* Original 0x452d10: 0x43b720 on the partner with -+0x3c8, the event 0x4f8194 and 0x43ac00. */
uint32_t vertrix_port_effect_progress_update_gate_452d10(PORT_SIGNATURE)
{
    return effect_gate(calls, services, globals, entry, 0x43b720, 0, 0x3c8, 1, 0x4f8194, 1);
}

/* In mode `mode` (+0x4c8) 0x43acd0 (edx the mode); otherwise the event 0x4f8198 by 0x43c0e0 and
 * `other`; then the child update and 0x43bbf0. */
static uint32_t mode_gate(PORT_SIGNATURE, uint32_t mode, uint32_t other)
{
    Port port;
    uint32_t player = entry->eax;
    uint32_t current;
    uint32_t child;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    current = port_u32(&port, player, 0x4c8);
    child = port_u32(&port, player, 0x15c);
    if (current == mode)
    {
        port_forward_esi(&port, entry, 0x43acd0, player, current, child, player, player);
    }
    else
    {
        port_forward_esi(&port, entry, 0x43c0e0, player, port_u32(&port, 0, 0x4f8198), child,
                         player, player);
        port_forward_esi(&port, entry, other, player, vertrix_lift_edx, child, player, player);
    }
    result = effect_finish(&port, entry, player, child, child, player, player);
    return port_return(&port, result, entry->edx);
}

/* Original 0x453620: mode 0x22, otherwise 0x43cf70. */
uint32_t vertrix_port_effect_state_gate_453620(PORT_SIGNATURE)
{
    return mode_gate(calls, services, globals, entry, 0x22, 0x43cf70);
}

/* Original 0x453670: mode 0x30, otherwise 0x43ce30. */
uint32_t vertrix_port_effect_state_gate_453670(PORT_SIGNATURE)
{
    return mode_gate(calls, services, globals, entry, 0x30, 0x43ce30);
}

/* In mode `mode` 0x43acd0; otherwise 0x43ac00 and `other` (on the edx it leaves); then the child
 * update and 0x43bbf0. */
static uint32_t mode_gate_apply(PORT_SIGNATURE, uint32_t mode, uint32_t other)
{
    Port port;
    uint32_t player = entry->eax;
    uint32_t child;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    child = port_u32(&port, player, 0x15c);
    if (port_u32(&port, player, 0x4c8) == mode)
    {
        port_forward(&port, entry, 0x43acd0, player, player, player, child);
    }
    else
    {
        port_forward(&port, entry, 0x43ac00, player, player, player, child);
        port_forward(&port, entry, other, vertrix_lift_edx, vertrix_lift_edx, player, child);
    }
    result = effect_finish(&port, entry, player, child, player, child, entry->esi);
    return port_return(&port, result, entry->edx);
}

/* Original 0x4536c0: mode 0x32. */
uint32_t vertrix_port_effect_state_gate_4536c0(PORT_SIGNATURE)
{
    return mode_gate_apply(calls, services, globals, entry, 0x32, 0x43ce70);
}

/* Original 0x453710: mode 0x33. */
uint32_t vertrix_port_effect_state_gate_453710(PORT_SIGNATURE)
{
    return mode_gate_apply(calls, services, globals, entry, 0x33, 0x43ce70);
}

/* Original 0x453760: mode 0x34. */
uint32_t vertrix_port_effect_state_gate_453760(PORT_SIGNATURE)
{
    return mode_gate_apply(calls, services, globals, entry, 0x34, 0x43ce70);
}

/* Original 0x4538f0: mode 0x29, otherwise 0x43d030. */
uint32_t vertrix_port_effect_state_gate_4538f0(PORT_SIGNATURE)
{
    return mode_gate(calls, services, globals, entry, 0x29, 0x43d030);
}

/* Original 0x453940: mode 0x2a, otherwise 0x43d070. */
uint32_t vertrix_port_effect_state_gate_453940(PORT_SIGNATURE)
{
    return mode_gate(calls, services, globals, entry, 0x2a, 0x43d070);
}

/* Original 0x453a30: mode 0x2b, otherwise 0x43ac00 and 0x43cd60. */
uint32_t vertrix_port_effect_state_gate_453a30(PORT_SIGNATURE)
{
    return mode_gate_apply(calls, services, globals, entry, 0x2b, 0x43cd60);
}

/* Whether 0x42eca0 finds 0x44c860 on the child; the child update, and 0x43bbf0 when it did
 * (`clear`: then +0xb8c of the child cleared). */
static uint32_t state_ask(PORT_SIGNATURE, int clear)
{
    Port port;
    uint32_t object = entry->eax;
    uint32_t child;
    uint32_t methods;
    uint32_t found;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    child = port_u32(&port, object, 0x15c);
    found = port_forward_esi(&port, entry, 0x42eca0, child, 0x44c860, 0, child, object) != 0;
    methods = port_u32(&port, child, 0x158);
    result = port_forward_esi(&port, entry, port_u32(&port, methods, 4), child, methods, found,
                              child, object);
    if (found)
    {
        result = port_forward_esi(&port, entry, 0x43bbf0, object, vertrix_lift_edx, found, child,
                                  object);
        if (clear)
        {
            port_set32(&port, child, 0xb8c, 0);
        }
    }
    return port_return(&port, result, entry->edx);
}

/* Original 0x453ef0. */
uint32_t vertrix_port_state_ask_453ef0(PORT_SIGNATURE)
{
    return state_ask(calls, services, globals, entry, 0);
}

/* Original 0x454200. */
uint32_t vertrix_port_state_ask_454200(PORT_SIGNATURE)
{
    return state_ask(calls, services, globals, entry, 0);
}

/* Original 0x454510. */
uint32_t vertrix_port_state_ask_454510(PORT_SIGNATURE)
{
    return state_ask(calls, services, globals, entry, 0);
}

/* Original 0x454760. */
uint32_t vertrix_port_state_ask_454760(PORT_SIGNATURE)
{
    return state_ask(calls, services, globals, entry, 0);
}

/* Original 0x455e00: the same, clearing +0xb8c. */
uint32_t vertrix_port_state_ask_455e00(PORT_SIGNATURE)
{
    return state_ask(calls, services, globals, entry, 1);
}

/* Original 0x455db0: when 0x42eca0 finds 0x44c860 on the child, its handler 0x455e00 by 0x4387b0
 * and 0x4ac8f0; then the child update. */
uint32_t vertrix_port_state_replace_455db0(PORT_SIGNATURE)
{
    Port port;
    uint32_t object = entry->eax;
    uint32_t child;
    uint32_t methods;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    child = port_u32(&port, object, 0x15c);
    if (port_forward(&port, entry, 0x42eca0, child, 0x44c860, object, child) != 0)
    {
        port_forward(&port, entry, 0x4387b0, child, 0x455e00, object, child);
        port_forward(&port, entry, 0x4ac8f0, object, vertrix_lift_edx, object, child);
    }
    methods = port_u32(&port, child, 0x158);
    result = port_forward(&port, entry, port_u32(&port, methods, 4), child, vertrix_lift_edx,
                          methods, child);
    return port_return(&port, result, entry->edx);
}

/* Original 0x456060: step the child (0x4ac5b0 when due); when 0x430090 then gives 1, the child
 * update and 0x43bbf0, otherwise the child update alone. The child pointer is the edx each call
 * leaves. */
uint32_t vertrix_port_effect_slide_end_456060(PORT_SIGNATURE)
{
    Port port;
    uint32_t object = entry->eax;
    uint32_t child;
    uint32_t done = 0;
    uint32_t methods;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    child = port_u32(&port, object, 0x15c);
    port_forward(&port, entry, 0x4ac500, child, child, entry->ebx, object);
    child = vertrix_lift_edx;
    if (port_forward(&port, entry, 0x4ac520, child, child, 0, object) == 1)
    {
        child = vertrix_lift_edx;
        port_forward(&port, entry, 0x4ac5b0, child, child, 0, object);
    }
    child = vertrix_lift_edx;
    result = port_forward(&port, entry, 0x430090, child, child, 0, object);
    child = vertrix_lift_edx;
    if (result == 1)
    {
        done = 1;
    }
    methods = port_u32(&port, child, 0x158);
    result = port_forward_esi(&port, entry, port_u32(&port, methods, 4), child, child, done, object,
                              methods);
    if (done == 1)
    {
        result = port_forward_esi(&port, entry, 0x43bbf0, object, vertrix_lift_edx, done, object,
                                  methods);
    }
    return port_return(&port, result, entry->edx);
}

/* The menu wait of 0x456490, 0x456670 and 0x456860: step the actor (0x4ac510 when due; the actor
 * is the edx each call leaves), then whether 0x476480 finds 0x74 in 0x54d640. */
static uint32_t menu_wait(Port *port, const LiftEntry *entry, uint32_t actor)
{
    uint32_t edx;
    port_forward(port, entry, 0x4ac500, actor, actor, entry->ebx, actor);
    edx = vertrix_lift_edx;
    if (port_forward(port, entry, 0x4ac520, edx, edx, entry->ebx, actor) == 1)
    {
        edx = vertrix_lift_edx;
        port_forward(port, entry, 0x4ac510, edx, edx, entry->ebx, actor);
    }
    return port_forward(port, entry, 0x476480, 0x54d640, 0x74, entry->ebx, actor);
}

/* Original 0x456490: once the key is up, 0x478bd0 and the handler 0x456390. */
uint32_t vertrix_port_menu_wait_456490(PORT_SIGNATURE)
{
    Port port;
    uint32_t actor = entry->eax;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    result = menu_wait(&port, entry, actor);
    if (result == 0)
    {
        port_forward(&port, entry, 0x478bd0, 0, vertrix_lift_edx, entry->ebx, actor);
        result = port_forward(&port, entry, 0x4ac8f0, actor, 0x456390, entry->ebx, actor);
    }
    return port_return(&port, result, entry->edx);
}

/* Once the key is up, the toggle at `toggle` flipped, `call` on the dword at `source` with
 * `handler`, and 0x4ac8f0 on the edx it leaves. */
static uint32_t menu_toggle(PORT_SIGNATURE, uint32_t toggle, uint32_t source, uint32_t call,
                            uint32_t handler)
{
    Port port;
    uint32_t actor = entry->eax;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    result = menu_wait(&port, entry, actor);
    if (result == 0)
    {
        port_set32(&port, 0, toggle, 1 - port_u32(&port, 0, toggle));
        port_forward(&port, entry, call, port_u32(&port, 0, source), handler, entry->ebx, actor);
        result = port_forward(&port, entry, 0x4ac8f0, actor, vertrix_lift_edx, entry->ebx, actor);
    }
    return port_return(&port, result, entry->edx);
}

/* Original 0x456670: the toggle 0x5589dc, 0x478b40 on 0x532b98 with 0x456570. */
uint32_t vertrix_port_menu_toggle_456670(PORT_SIGNATURE)
{
    return menu_toggle(calls, services, globals, entry, 0x5589dc, 0x532b98, 0x478b40, 0x456570);
}

/* Original 0x456860: the toggle 0x598da8, 0x4828f0 on 0x532b9c with 0x456760. */
uint32_t vertrix_port_menu_toggle_456860(PORT_SIGNATURE)
{
    return menu_toggle(calls, services, globals, entry, 0x598da8, 0x532b9c, 0x4828f0, 0x456760);
}

/* Original 0x456d80: +0x5c the word 0x5b9c8e and +0x60 10, 0x4ad6e0, next 0. */
uint32_t vertrix_port_actor_step_wait_456d80(PORT_SIGNATURE)
{
    static const Step step = {
        {0}, 0, {{STORE_GLOBAL_WORD, 0x5c, 0x5b9c8e}, {4, 0x60, 10}}, 0x4ad6e0, 0, 0, NULL, 0};
    return actor_step(calls, services, globals, entry, &step);
}

/* Original 0x456de0: the same with +0x60 4. */
uint32_t vertrix_port_actor_step_wait_456de0(PORT_SIGNATURE)
{
    static const Step step = {
        {0}, 0, {{STORE_GLOBAL_WORD, 0x5c, 0x5b9c8e}, {4, 0x60, 4}}, 0x4ad6e0, 0, 0, NULL, 0};
    return actor_step(calls, services, globals, entry, &step);
}

/* Original 0x456e40: the same with +0x60 8. */
uint32_t vertrix_port_actor_step_wait_456e40(PORT_SIGNATURE)
{
    static const Step step = {
        {0}, 0, {{STORE_GLOBAL_WORD, 0x5c, 0x5b9c8e}, {4, 0x60, 8}}, 0x4ad6e0, 0, 0, NULL, 0};
    return actor_step(calls, services, globals, entry, &step);
}

/* Original 0x456fa0: +0x5c the word 0x5b9c90 and +0x60 4. */
uint32_t vertrix_port_actor_step_wait_456fa0(PORT_SIGNATURE)
{
    static const Step step = {
        {0}, 0, {{STORE_GLOBAL_WORD, 0x5c, 0x5b9c90}, {4, 0x60, 4}}, 0x4ad6e0, 0, 0, NULL, 0};
    return actor_step(calls, services, globals, entry, &step);
}

/* Original 0x457000: 0x4ac5b0 with 0; +0x5c half the edx it leaves with its low word the word
 * 0x5b9c90 (signed, toward zero), +0x60 4; 0x4ad6e0 on the step value, next 0. */
uint32_t vertrix_port_actor_step_wait_half_457000(PORT_SIGNATURE)
{
    Port port;
    uint32_t actor = entry->eax;
    uint32_t value;
    uint32_t edx;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    port_forward(&port, entry, 0x4ac500, actor, entry->edx, entry->ebx, actor);
    result = port_forward(&port, entry, 0x4ac520, actor, vertrix_lift_edx, entry->ebx, actor);
    if (result == 1)
    {
        value = port_forward(&port, entry, 0x4ac540, actor, vertrix_lift_edx, entry->ebx, actor);
        port_forward(&port, entry, 0x4ac5b0, actor, 0, value, actor);
        edx = (vertrix_lift_edx & 0xffff0000u) | port_u16(&port, 0, 0x5b9c90);
        port_set32(&port, actor, 0x5c, (uint32_t)((int32_t)(edx + (edx >> 31)) >> 1));
        port_set32(&port, actor, 0x60, 4);
        result = port_forward(&port, entry, 0x4ad6e0, actor, value, value, actor);
        if (result == 0)
        {
            result = port_forward(&port, entry, 0x4ac8f0, actor, 0, value, actor);
        }
    }
    return port_return(&port, result, entry->edx);
}

/* Original 0x457060: +0x5c 16 and +0x60 1, 0x4ad6e0, next 0. */
uint32_t vertrix_port_actor_step_wait_457060(PORT_SIGNATURE)
{
    static const Step step = {{0}, 0, {{4, 0x5c, 0x10}, {4, 0x60, 1}}, 0x4ad6e0, 0, 0, NULL, 0};
    return actor_step(calls, services, globals, entry, &step);
}

/* When the step is due, the step value from 0x4ac540 by 0x4ac5b0; when 0x4b5d40 then holds,
 * `call` (1, 0) once for each count up to that value (once at least), unless the edx 0x4b5d40
 * leaves is 0. */
static uint32_t actor_step_repeat(PORT_SIGNATURE, uint32_t call)
{
    Port port;
    uint32_t actor = entry->eax;
    uint32_t value;
    uint32_t count;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    port_forward(&port, entry, 0x4ac500, actor, entry->edx, entry->ebx, actor);
    result = port_forward(&port, entry, 0x4ac520, actor, vertrix_lift_edx, entry->ebx, actor);
    if (result == 1)
    {
        value = port_forward(&port, entry, 0x4ac540, actor, vertrix_lift_edx, entry->ebx, actor);
        port_forward(&port, entry, 0x4ac5b0, actor, value, value, actor);
        result = port_forward(&port, entry, 0x4b5d40, actor, vertrix_lift_edx, value, actor);
        if (result != 0 && vertrix_lift_edx != 0)
        {
            count = 0;
            do
            {
                count++;
                result = port_forward(&port, entry, call, 1, 0, value, count);
            } while (count < value);
        }
    }
    return port_return(&port, result, entry->edx);
}

/* Original 0x457670: 0x478bf0. */
uint32_t vertrix_port_actor_step_repeat_457670(PORT_SIGNATURE)
{
    return actor_step_repeat(calls, services, globals, entry, 0x478bf0);
}

/* Original 0x4576d0: 0x478c40. */
uint32_t vertrix_port_actor_step_repeat_4576d0(PORT_SIGNATURE)
{
    return actor_step_repeat(calls, services, globals, entry, 0x478c40);
}

/* Words +0x4a -5 and +0x4c 2 before the next handler. */
static void then_sink(Port *port, const LiftEntry *entry, uint32_t actor)
{
    (void)entry;
    port_set16(port, actor, 0x4a, 0xfffb);
    port_set16(port, actor, 0x4c, 2);
}

/* Words +0x4a 50 and +0x4c 2 before the next handler. */
static void then_lift(Port *port, const LiftEntry *entry, uint32_t actor)
{
    (void)entry;
    port_set16(port, actor, 0x4a, 0x32);
    port_set16(port, actor, 0x4c, 2);
}

/* Original 0x4580b0: 0x4ad530, then the sink and next 0x458100. */
uint32_t vertrix_port_actor_step_bob_4580b0(PORT_SIGNATURE)
{
    static const Step step = {{0}, 0, {{0}, {0}}, 0x4ad530, 0x458100, 0, then_sink, 0};
    return actor_step(calls, services, globals, entry, &step);
}

/* Original 0x458100: 0x4ad530, then the lift and next 0x4580b0. */
uint32_t vertrix_port_actor_step_bob_458100(PORT_SIGNATURE)
{
    static const Step step = {{0}, 0, {{0}, {0}}, 0x4ad530, 0x4580b0, 0, then_lift, 0};
    return actor_step(calls, services, globals, entry, &step);
}

/* Original 0x4583c0: 0x4ad530, next 0x458410. */
uint32_t vertrix_port_actor_step_move_4583c0(PORT_SIGNATURE)
{
    static const Step step = {{0}, 0, {{0}, {0}}, 0x4ad530, 0x458410, 0, NULL, 0};
    return actor_step(calls, services, globals, entry, &step);
}

/* Original 0x458490: 0x457810; bytes +0x95 4, +0x93 0 and +0x94 1, words +0x48 0, +0x4a 150 and
 * +0x4c 5; 0x4ac7d0 with 10, the handler 0x4584f0, 0x4ac8f0 and 0x457890. */
uint32_t vertrix_port_actor_drop_start_458490(PORT_SIGNATURE)
{
    Port port;
    uint32_t actor = entry->eax;
    port_open(&port, calls, services, globals, entry);
    port_forward(&port, entry, 0x457810, actor, entry->edx, entry->ebx, actor);
    port_set8(&port, actor, 0x95, 4);
    port_set8(&port, actor, 0x93, 0);
    port_set8(&port, actor, 0x94, 1);
    port_set16(&port, actor, 0x48, 0);
    port_set16(&port, actor, 0x4a, 0x96);
    port_set16(&port, actor, 0x4c, 5);
    port_forward(&port, entry, 0x4ac7d0, actor, 10, entry->ebx, actor);
    port_forward(&port, entry, 0x4ac510, actor, 0x4584f0, entry->ebx, actor);
    port_forward(&port, entry, 0x4ac8f0, actor, vertrix_lift_edx, entry->ebx, actor);
    return port_return(
        &port, port_forward(&port, entry, 0x457890, actor, vertrix_lift_edx, entry->ebx, actor),
        entry->edx);
}

/* Original 0x458560: 0x457810 first; 0x4ad530, next 0, then 0x457890. */
uint32_t vertrix_port_actor_drop_step_458560(PORT_SIGNATURE)
{
    static const Step step = {{0}, 0x457810, {{0}, {0}}, 0x4ad530, 0, 0x457890, NULL, 0};
    return actor_step(calls, services, globals, entry, &step);
}

/* Original 0x4590a0: with +0x58 32, 0x4ac8f0 with 0; otherwise +0x70 0, +0x74 50 and +0x78 1, a
 * wait of 10 more than the low word 0x4826c0 gives on 0x598d30 with 20, the handler 0x459100 and
 * 0x4ac8f0. */
uint32_t vertrix_port_actor_wait_random_4590a0(PORT_SIGNATURE)
{
    Port port;
    uint32_t actor = entry->eax;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    if (port_u32(&port, actor, 0x58) == 0x20)
    {
        result = port_forward(&port, entry, 0x4ac8f0, actor, 0, entry->ebx, actor);
        return port_return(&port, result, entry->edx);
    }
    port_set32(&port, actor, 0x70, 0);
    port_set32(&port, actor, 0x74, 0x32);
    port_set32(&port, actor, 0x78, 1);
    result = port_forward(&port, entry, 0x4826c0, 0x598d30, 0x14, entry->ebx, actor);
    port_forward(&port, entry, 0x4ac7d0, actor, (result & 0xffff) + 10, entry->ebx, actor);
    port_forward(&port, entry, 0x4ac510, actor, 0x459100, entry->ebx, actor);
    result = port_forward(&port, entry, 0x4ac8f0, actor, vertrix_lift_edx, entry->ebx, actor);
    return port_return(&port, result, entry->edx);
}

/* Original 0x4598a0: unless 0x4ac2b0 holds, 0x4ac710 with 0, byte +0x4e 0 and the count +0x58
 * up; below the limit +0x5c the handler 0x4597e0 by 0x4ac8f0, otherwise 0x4ac8f0 with 0. Then
 * 0x4ac8a0 either way. */
uint32_t vertrix_port_actor_count_step_4598a0(PORT_SIGNATURE)
{
    Port port;
    uint32_t actor = entry->eax;
    uint32_t count;
    uint32_t limit;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    if (port_forward(&port, entry, 0x4ac2b0, actor, entry->edx, entry->ebx, actor) != 0)
    {
        result = port_forward(&port, entry, 0x4ac8a0, actor, vertrix_lift_edx, entry->ebx, actor);
        return port_return(&port, result, entry->edx);
    }
    port_forward(&port, entry, 0x4ac710, actor, 0, entry->ebx, actor);
    count = port_u32(&port, actor, 0x58) + 1;
    port_set8(&port, actor, 0x4e, 0);
    limit = port_u32(&port, actor, 0x5c);
    port_set32(&port, actor, 0x58, count);
    port_forward(&port, entry, 0x4ac8f0, actor, (int32_t)count < (int32_t)limit ? 0x4597e0 : 0,
                 limit, actor);
    result = port_forward(&port, entry, 0x4ac8a0, actor, vertrix_lift_edx, limit, actor);
    return port_return(&port, result, entry->edx);
}

/* Original 0x459900: byte +0x4f 0 and word +0x50 1 first; 0x4ad580, next 0x459950. */
uint32_t vertrix_port_actor_step_fade_459900(PORT_SIGNATURE)
{
    static const Step step = {{0}, 0, {{0}, {0}}, 0x4ad580, 0x459950, 0, NULL, 0};
    Port port;
    port_open(&port, calls, services, globals, entry);
    port_set8(&port, entry->eax, 0x4f, 0);
    port_set16(&port, entry->eax, 0x50, 1);
    return actor_step_open(&port, entry, &step);
}

/* Original 0x4599e0: byte +0x93 1, byte +0x4f 0 and word +0x50 2 first; 0x4ad580, next 0. */
uint32_t vertrix_port_actor_step_fade_4599e0(PORT_SIGNATURE)
{
    static const Step step = {{0}, 0, {{0}, {0}}, 0x4ad580, 0, 0, NULL, 0};
    Port port;
    port_open(&port, calls, services, globals, entry);
    port_set8(&port, entry->eax, 0x93, 1);
    port_set8(&port, entry->eax, 0x4f, 0);
    port_set16(&port, entry->eax, 0x50, 2);
    return actor_step_open(&port, entry, &step);
}

/* A call handing the callee esi and edi as given, the caller's ebp, and `count` stack arguments
 * (the nearest to the stack pointer first). */
static uint32_t call_esi_edi(Port *port, const LiftEntry *entry, uint32_t target, uint32_t eax,
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

/* When the step is due, 0x4ac5b0 with what 0x4ac540 gives; when `check` then gives 0, the next
 * handler `next` by 0x4ac8f0 and the count +0x58 cleared. */
static uint32_t actor_step_counted(Port *port, const LiftEntry *entry, uint32_t check,
                                   uint32_t next)
{
    uint32_t actor = entry->eax;
    uint32_t result;
    port_forward(port, entry, 0x4ac500, actor, entry->edx, entry->ebx, actor);
    result = port_forward(port, entry, 0x4ac520, actor, vertrix_lift_edx, entry->ebx, actor);
    if (result == 1)
    {
        result = port_forward(port, entry, 0x4ac540, actor, vertrix_lift_edx, entry->ebx, actor);
        port_forward(port, entry, 0x4ac5b0, actor, result, entry->ebx, actor);
        result = port_forward(port, entry, check, actor, vertrix_lift_edx, entry->ebx, actor);
        if (result == 0)
        {
            result = port_forward(port, entry, 0x4ac8f0, actor, next, entry->ebx, actor);
            port_set32(port, actor, 0x58, 0);
        }
    }
    return port_return(port, result, entry->edx);
}

/* Original 0x459ab0: +0x5c 100 first; 0x4ad6e0, next 0x459a30. */
uint32_t vertrix_port_actor_step_counted_459ab0(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    port_set32(&port, entry->eax, 0x5c, 0x64);
    return actor_step_counted(&port, entry, 0x4ad6e0, 0x459a30);
}

/* Original 0x459b00: byte +0x4f 100 and byte +0x93 1 first; 0x4ad580, next 0x459b60. */
uint32_t vertrix_port_actor_step_counted_459b00(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    port_set8(&port, entry->eax, 0x4f, 0x64);
    port_set8(&port, entry->eax, 0x93, 1);
    return actor_step_counted(&port, entry, 0x4ad580, 0x459b60);
}

/* Original 0x45aa20: 0x4ac1f0 first; 0x4accc0 without a next handler, then 0x4ac8a0. */
uint32_t vertrix_port_actor_step_cycle_45aa20(PORT_SIGNATURE)
{
    static const Step step = {{0}, 0x4ac1f0, {{0}, {0}}, 0x4accc0, 0, 0x4ac8a0, NULL, 1};
    return actor_step(calls, services, globals, entry, &step);
}

/* Original 0x45b590: step the child (0x4ac5b0 on the edx 0x4ac520 leaves when due); when
 * 0x439080 then gives 1, the handler 0x45b5f0 by 0x4ac8f0. Then the child update. */
uint32_t vertrix_port_state_child_step_45b590(PORT_SIGNATURE)
{
    Port port;
    uint32_t object = entry->eax;
    uint32_t child;
    uint32_t methods;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    child = port_u32(&port, object, 0x15c);
    port_forward(&port, entry, 0x4ac500, child, entry->edx, object, child);
    if (port_forward(&port, entry, 0x4ac520, child, vertrix_lift_edx, object, child) == 1)
    {
        port_forward(&port, entry, 0x4ac5b0, child, vertrix_lift_edx, object, child);
        if (port_forward(&port, entry, 0x439080, child, vertrix_lift_edx, object, child) == 1)
        {
            port_forward(&port, entry, 0x4ac8f0, object, 0x45b5f0, object, child);
        }
    }
    methods = port_u32(&port, child, 0x158);
    result = port_forward(&port, entry, port_u32(&port, methods, 4), child, vertrix_lift_edx,
                          methods, child);
    return port_return(&port, result, entry->edx);
}

/* Original 0x45c150: 0x4ac1f0 first; byte +0x4f 0 and word +0x50 5, 0x4ad580, next 0, then
 * 0x4ac8a0. */
uint32_t vertrix_port_actor_step_fade_45c150(PORT_SIGNATURE)
{
    static const Step step = {{0},  0x4ac1f0, {{1, 0x4f, 0}, {2, 0x50, 5}}, 0x4ad580, 0, 0x4ac8a0,
                              NULL, 0};
    return actor_step(calls, services, globals, entry, &step);
}

/* Original 0x45c1b0: 0x4ac1f0 first; words +0x4a 0 and +0x4c 2, 0x4ad530, next 0, then
 * 0x4ac8a0. */
uint32_t vertrix_port_actor_step_move_45c1b0(PORT_SIGNATURE)
{
    static const Step step = {{0},  0x4ac1f0, {{2, 0x4a, 0}, {2, 0x4c, 2}}, 0x4ad530, 0, 0x4ac8a0,
                              NULL, 0};
    return actor_step(calls, services, globals, entry, &step);
}

/* Original 0x45c250: step the actor (when due 0x4ac510 with 1 and the edx it leaves kept at
 * 0x532b48; the actor is the edx each call leaves); then the key 0x476530 reads from 0x54d640:
 * any key but 0x532b94 and 0x3b sets 0x532b44. */
uint32_t vertrix_port_menu_key_wait_45c250(PORT_SIGNATURE)
{
    Port port;
    uint32_t actor = entry->eax;
    uint32_t key;
    port_open(&port, calls, services, globals, entry);
    port_forward(&port, entry, 0x4ac500, actor, actor, entry->ebx, entry->ecx);
    actor = vertrix_lift_edx;
    if (port_forward(&port, entry, 0x4ac520, actor, actor, entry->ebx, entry->ecx) == 1)
    {
        port_forward(&port, entry, 0x4ac510, vertrix_lift_edx, 1, entry->ebx, entry->ecx);
        port_set32(&port, 0, 0x532b48, vertrix_lift_edx);
    }
    key = port_forward(&port, entry, 0x476530, 0x54d640, 0, entry->ebx, entry->ecx);
    if ((key & 0xffff) != 0 && (key & 0xffff) != port_u32(&port, 0, 0x532b94) &&
        (key & 0xffff) != 0x3b)
    {
        port_set32(&port, 0, 0x532b44, 1);
    }
    return port_return(&port, key, entry->edx);
}

/* Original 0x45c6e0: 0x482a60 on 1 and on 5 with the entry 0x4f81ac of 0x533164 and 0x532b9c,
 * then the handler 0x45c730. */
uint32_t vertrix_port_menu_play_45c6e0(PORT_SIGNATURE)
{
    Port port;
    uint32_t actor = entry->eax;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    port_forward(&port, entry, 0x482a60, 1,
                 port_u32(&port, port_u32(&port, 0, 0x4f81ac) * 4, 0x533164),
                 port_u32(&port, 0, 0x532b9c), actor);
    port_forward(&port, entry, 0x482a60, 5,
                 port_u32(&port, port_u32(&port, 0, 0x4f81ac) * 4, 0x533164),
                 port_u32(&port, 0, 0x532b9c), actor);
    result =
        port_forward(&port, entry, 0x4ac8f0, actor, 0x45c730, port_u32(&port, 0, 0x532b9c), actor);
    return port_return(&port, result, entry->edx);
}

/* When the step is due, 0x4ac5b0 with what 0x4ac540 gives, the word +0x4a of the partner +0x160
 * `value` and 0x4ad530 on it; when that gives 0, the next handler `next`. */
static uint32_t partner_step(PORT_SIGNATURE, uint32_t value, uint32_t next)
{
    Port port;
    uint32_t actor = entry->eax;
    uint32_t partner;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    partner = port_u32(&port, actor, 0x160);
    port_forward(&port, entry, 0x4ac500, actor, entry->edx, partner, actor);
    result = port_forward(&port, entry, 0x4ac520, actor, vertrix_lift_edx, partner, actor);
    if (result == 1)
    {
        result = port_forward(&port, entry, 0x4ac540, actor, vertrix_lift_edx, partner, actor);
        port_forward(&port, entry, 0x4ac5b0, actor, result, partner, actor);
        port_set16(&port, partner, 0x4a, value);
        result = port_forward(&port, entry, 0x4ad530, partner, vertrix_lift_edx, partner, actor);
        if (result == 0)
        {
            result = port_forward(&port, entry, 0x4ac8f0, actor, next, partner, actor);
        }
    }
    return port_return(&port, result, entry->edx);
}

/* Original 0x45c8e0: -20, next 0x45c940. */
uint32_t vertrix_port_partner_step_45c8e0(PORT_SIGNATURE)
{
    return partner_step(calls, services, globals, entry, 0xffec, 0x45c940);
}

/* Original 0x45c940: -60, next 0x45c8e0. */
uint32_t vertrix_port_partner_step_45c940(PORT_SIGNATURE)
{
    return partner_step(calls, services, globals, entry, 0xffc4, 0x45c8e0);
}

/* Original 0x45d820: with edx nonzero, 0x4b65a0 (pushing 1, which stays on the stack for the
 * next two calls; ecx 0 in state +0x64 1, otherwise -10), 0x4ac980 and 0x4b6540 on the words they
 * give; when 0x4ac980 gave that ecx the state
 * flips and eax is the new state. */
uint32_t vertrix_port_object_step_toggle_45d820(PORT_SIGNATURE)
{
    Port port;
    uint32_t object = entry->eax;
    uint32_t offset;
    uint32_t pushed[1] = {1};
    uint32_t ebx;
    uint32_t moved;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    if (entry->edx == 0)
    {
        return port_return(&port, object, entry->edx);
    }
    offset = port_u32(&port, object, 0x64) == 1 ? 0 : 0xfffffff6u;
    ebx = (uint32_t)(int16_t)call_esi_edi(&port, entry, 0x4b65a0, object, entry->edx, entry->ebx,
                                          offset, object, offset, pushed, 1);
    moved = call_esi_edi(&port, entry, 0x4ac980, object, vertrix_lift_edx, ebx, offset, object,
                         offset, pushed, 1);
    result = call_esi_edi(&port, entry, 0x4b6540, object, (uint32_t)(int16_t)moved, ebx, moved,
                          object, offset, pushed, 1);
    if (moved == offset)
    {
        result = 1 - port_u32(&port, object, 0x64);
        port_set32(&port, object, 0x64, result);
    }
    return port_return(&port, result, vertrix_lift_edx);
}

/* Original 0x45e440: the seven records of 0x1c bytes from 0x544ac0 set up by 0x4875a0. */
uint32_t vertrix_port_table_build_pair_45e440(PORT_SIGNATURE)
{
    Port port;
    uint32_t record;
    uint32_t pushed[10] = {0, 0, 0, 0, 0x18, 0x18, 0, 0, 1, 4};
    uint32_t result = 0;
    port_open(&port, calls, services, globals, entry);
    for (record = 0x544ac0; record != 0x544b84; record += 0x1c)
    {
        result = call_esi_edi(&port, entry, 0x4875a0, record, 8, 0x18, 0x18, record + 0x1c,
                              0x544b84, pushed, 10);
    }
    return port_return(&port, result, entry->edx);
}

/* Original 0x45e750: fill the slot eax of the table 0x5464e4 by 0x487660 with the size +4 and +8
 * of edx, take it by 0x4877f0, then 0x482e10 with edx and 0x483ed0 with 0x5b9c60 on it. */
uint32_t vertrix_port_table_fill_slot_45e750(PORT_SIGNATURE)
{
    Port port;
    uint32_t slot = entry->eax;
    uint32_t source = entry->edx;
    uint32_t width;
    uint32_t height;
    uint32_t pushed[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 4};
    uint32_t taken;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    width = port_u32(&port, source, 4);
    height = port_u32(&port, source, 8);
    pushed[4] = width;
    pushed[5] = height;
    call_esi_edi(&port, entry, 0x487660, 0x5464e4, slot, width, height, source, slot, pushed, 10);
    taken =
        call_esi_edi(&port, entry, 0x4877f0, 0x5464e4, slot, width, height, source, slot, NULL, 0);
    call_esi_edi(&port, entry, 0x482e10, taken, source, 0, 0, source, taken, NULL, 0);
    result = call_esi_edi(&port, entry, 0x483ed0, taken, 0x5b9c60, 0, 0, source, taken, NULL, 0);
    return port_return(&port, result, vertrix_lift_edx);
}

/* Original 0x471bf0: 0x4ac920 on each actor of the list 0x546720 (count 0x546724) whose
 * +0x14c is not eax; eax the last actor or result (0 for none). The count goes on from the edx
 * each call leaves. */
uint32_t vertrix_port_actors_handler_from_ec_unlinked_471bf0(PORT_SIGNATURE)
{
    Port port;
    uint32_t owner = entry->eax;
    uint32_t count;
    uint32_t index = 0;
    uint32_t offset = 0;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    count = port_u32(&port, 0, 0x546724);
    result = count;
    while (index < count)
    {
        uint32_t actor = port_u32(&port, port_u32(&port, 0, 0x546720), offset);
        uint32_t link = port_u32(&port, actor, 0x14c);
        result = actor;
        if (link != owner)
        {
            result = call_esi_edi(&port, entry, 0x4ac920, actor, index, link, offset, owner, count,
                                  NULL, 0);
            index = vertrix_lift_edx;
        }
        index++;
        offset += 4;
    }
    return port_return(&port, result, entry->edx);
}

/* Original 0x471e10: 0x4123d0 (edx 0) with each of the records 0x15 and 0x16 0x4b5eb0 finds in
 * 0x54671c. */
uint32_t vertrix_port_scene_lookup_pair_471e10(PORT_SIGNATURE)
{
    Port port;
    uint32_t object = entry->eax;
    uint32_t record;
    uint32_t ebx = entry->ebx;
    port_open(&port, calls, services, globals, entry);
    record = port_forward(&port, entry, 0x4b5eb0, 0x54671c, 0x15, ebx, object);
    if (record != 0)
    {
        ebx = record;
        port_forward(&port, entry, 0x4123d0, object, 0, ebx, object);
    }
    record = port_forward(&port, entry, 0x4b5eb0, 0x54671c, 0x16, ebx, object);
    if (record != 0)
    {
        record = port_forward(&port, entry, 0x4123d0, object, 0, record, object);
    }
    return port_return(&port, record, entry->edx);
}
