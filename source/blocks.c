#include "blocks.h"

/* Block and actor update handlers: steps that call 0x4ac8a0 either way, and their neighbours. */

/* A byte, word or dword stored at an offset of the actor (size 0: nothing). */
typedef struct
{
    uint8_t size;
    uint16_t offset;
    uint32_t value;
} Store;

/* An update: the `before` stores and `first` (when set) before stepping (0x4ac500 and
 * 0x4ac520); when the step is due, 0x4ac5b0 with what 0x4ac540 gives, the `due` stores and
 * `check`; when that gives 0 the `pre` stores, the next handler `next` by 0x4ac8f0 and the
 * `post` stores. 0x4ac8a0 ends it either way unless `no_finish`; `ebx_actor` hands every call
 * the actor in ebx, and `lead` (when set) comes before everything; `finish` (when set) ends it
 * in place of 0x4ac8a0. */
typedef struct
{
    Store before[3];
    uint32_t first;
    Store due[2];
    uint32_t check;
    Store pre[3];
    uint32_t next;
    Store post[3];
    uint8_t no_finish;
    uint8_t ebx_actor;
    uint32_t lead;
    uint32_t finish;
} Update;

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
}

static void stores(Port *port, uint32_t actor, const Store *list, unsigned count)
{
    unsigned i;
    for (i = 0; i < count; i++)
    {
        store(port, actor, &list[i]);
    }
}

static uint32_t update(PORT_SIGNATURE, const Update *step)
{
    Port port;
    uint32_t actor = entry->eax;
    uint32_t ebx = step->ebx_actor ? actor : entry->ebx;
    uint32_t result;
    uint32_t edx = entry->edx;
    port_open(&port, calls, services, globals, entry);
    if (step->lead != 0)
    {
        port_forward(&port, entry, step->lead, actor, edx, ebx, actor);
        edx = vertrix_lift_edx;
    }
    stores(&port, actor, step->before, 3);
    if (step->first != 0)
    {
        port_forward(&port, entry, step->first, actor, edx, ebx, actor);
        edx = vertrix_lift_edx;
    }
    port_forward(&port, entry, 0x4ac500, actor, edx, ebx, actor);
    result = port_forward(&port, entry, 0x4ac520, actor, vertrix_lift_edx, ebx, actor);
    if (result == 1)
    {
        result = port_forward(&port, entry, 0x4ac540, actor, vertrix_lift_edx, ebx, actor);
        port_forward(&port, entry, 0x4ac5b0, actor, result, ebx, actor);
        stores(&port, actor, step->due, 2);
        result = port_forward(&port, entry, step->check, actor, vertrix_lift_edx, ebx, actor);
        if (result == 0)
        {
            stores(&port, actor, step->pre, 3);
            result = port_forward(&port, entry, 0x4ac8f0, actor, step->next, ebx, actor);
            stores(&port, actor, step->post, 3);
        }
    }
    if (!step->no_finish)
    {
        result = port_forward(&port, entry, step->finish != 0 ? step->finish : 0x4ac8a0, actor,
                              vertrix_lift_edx, ebx, actor);
    }
    return port_return(&port, result, entry->edx);
}

/* Original 0x44ce80: byte +0x95 1 and 0x4ac1f0 first; 0x4ad6e0; byte +0x4e 100, next 0x44cf00,
 * then words +0x48 0, +0x4a 50 and +0x4c 10. */
uint32_t vertrix_port_block_scale_update_44ce80(PORT_SIGNATURE)
{
    static const Update step = {{{1, 0x95, 1}},
                                0x4ac1f0,
                                {{0}},
                                0x4ad6e0,
                                {{1, 0x4e, 0x64}},
                                0x44cf00,
                                {{2, 0x48, 0}, {2, 0x4a, 0x32}, {2, 0x4c, 0xa}},
                                0,
                                0,
                                0,
                                0};
    return update(calls, services, globals, entry, &step);
}

/* Original 0x44cf00: byte +0x95 1 and 0x4ac1f0 first; 0x4ad530; next 0x44cf70, then words +0x4a
 * 0 and +0x4c 10. */
uint32_t vertrix_port_block_return_update_44cf00(PORT_SIGNATURE)
{
    static const Update step = {{{1, 0x95, 1}},
                                0x4ac1f0,
                                {{0}},
                                0x4ad530,
                                {{0}},
                                0x44cf70,
                                {{2, 0x4a, 0}, {2, 0x4c, 0xa}},
                                0,
                                0,
                                0,
                                0};
    return update(calls, services, globals, entry, &step);
}

/* Original 0x44d330: 0x4ac1f0 first; dwords +0x5c 100 and +0x60 10, 0x4ad6e0; dword +0x58 0 and
 * next 0x44d3a0. */
uint32_t vertrix_port_block_count_update_44d330(PORT_SIGNATURE)
{
    static const Update step = {{{0}},
                                0x4ac1f0,
                                {{4, 0x5c, 0x64}, {4, 0x60, 0xa}},
                                0x4ad6e0,
                                {{4, 0x58, 0}},
                                0x44d3a0,
                                {{0}},
                                0,
                                0,
                                0,
                                0};
    return update(calls, services, globals, entry, &step);
}

/* Original 0x44e4a0: byte +0x93 1 and 0x4ac1f0 first; byte +0x4f 100 and word +0x50 2,
 * 0x4ad580; next 0x44c860, then byte +0x93 0. */
uint32_t vertrix_port_block_visibility_update_44e4a0(PORT_SIGNATURE)
{
    static const Update step = {{{1, 0x93, 1}},
                                0x4ac1f0,
                                {{1, 0x4f, 0x64}, {2, 0x50, 2}},
                                0x4ad580,
                                {{0}},
                                0x44c860,
                                {{1, 0x93, 0}},
                                0,
                                0,
                                0,
                                0};
    return update(calls, services, globals, entry, &step);
}

/* Original 0x44e510: bytes +0x93 1, +0x94 0 and +0x95 0 and 0x4ac1f0 first; byte +0x4f 0 and
 * word +0x50 8, 0x4ad580; next 0x44c860. */
uint32_t vertrix_port_block_fade_update_44e510(PORT_SIGNATURE)
{
    static const Update step = {{{1, 0x93, 1}, {1, 0x94, 0}, {1, 0x95, 0}},
                                0x4ac1f0,
                                {{1, 0x4f, 0}, {2, 0x50, 8}},
                                0x4ad580,
                                {{0}},
                                0x44c860,
                                {{0}},
                                0,
                                0,
                                0,
                                0};
    return update(calls, services, globals, entry, &step);
}

/* Original 0x44e590: bytes +0x93 0 and +0x4e 100 and 0x4ac1f0 first; byte +0x45 16 and word
 * +0x46 1, 0x4acc10; next 0x44e600. */
uint32_t vertrix_port_block_swell_update_44e590(PORT_SIGNATURE)
{
    static const Update step = {{{1, 0x93, 0}, {1, 0x4e, 0x64}},
                                0x4ac1f0,
                                {{1, 0x45, 0x10}, {2, 0x46, 1}},
                                0x4acc10,
                                {{0}},
                                0x44e600,
                                {{0}},
                                0,
                                0,
                                0,
                                0};
    return update(calls, services, globals, entry, &step);
}

/* Original 0x44e790: 0x4ac1f0 first; byte +0x45 0 and word +0x46 1, 0x4acc10; next 0x44c860. */
uint32_t vertrix_port_block_mode_amount_update_44e790(PORT_SIGNATURE)
{
    static const Update step = {
        {{0}}, 0x4ac1f0, {{1, 0x45, 0}, {2, 0x46, 1}}, 0x4acc10, {{0}}, 0x44c860, {{0}}, 0, 0,
        0,     0};
    return update(calls, services, globals, entry, &step);
}

/* Original 0x44f240: byte +0x94 0 and 0x4ac1f0 first; 0x4ad530; word +0x4a 0 and next
 * 0x44f2b0. */
uint32_t vertrix_port_block_effect_update_44f240(PORT_SIGNATURE)
{
    static const Update step = {
        {{1, 0x94, 0}}, 0x4ac1f0, {{0}}, 0x4ad530, {{2, 0x4a, 0}}, 0x44f2b0, {{0}}, 0, 0, 0, 0};
    return update(calls, services, globals, entry, &step);
}

/* Original 0x44f2b0: the same with word +0x4a -100 and next 0x44f240. */
uint32_t vertrix_port_block_effect_update_44f2b0(PORT_SIGNATURE)
{
    static const Update step = {{{1, 0x94, 0}},
                                0x4ac1f0,
                                {{0}},
                                0x4ad530,
                                {{2, 0x4a, 0xff9c}},
                                0x44f240,
                                {{0}},
                                0,
                                0,
                                0,
                                0};
    return update(calls, services, globals, entry, &step);
}

/* Original 0x44f320: 0x4ac1f0 first; word +0x4a 0, 0x4ad530; byte +0x52 13 and next 0x44c860. */
uint32_t vertrix_port_block_effect_update_44f320(PORT_SIGNATURE)
{
    static const Update step = {
        {{0}}, 0x4ac1f0, {{2, 0x4a, 0}}, 0x4ad530, {{1, 0x52, 0xd}}, 0x44c860, {{0}}, 0, 0, 0, 0};
    return update(calls, services, globals, entry, &step);
}

/* Original 0x44f430: 0x4ac1f0 first; dword +0x84 0, 0x4acc70; dword +0x80 0, byte +0x8c 0 and
 * next 0x44c860. */
uint32_t vertrix_port_block_cycle_update_44f430(PORT_SIGNATURE)
{
    static const Update step = {{{0}},
                                0x4ac1f0,
                                {{4, 0x84, 0}},
                                0x4acc70,
                                {{4, 0x80, 0}, {1, 0x8c, 0}},
                                0x44c860,
                                {{0}},
                                0,
                                0,
                                0,
                                0};
    return update(calls, services, globals, entry, &step);
}

/* Original 0x44f560: 0x4ac1f0 first; word +0x4a 0, 0x4ad530; next 0x44c860, then byte +0x52
 * 13. */
uint32_t vertrix_port_block_effect_update_44f560(PORT_SIGNATURE)
{
    static const Update step = {
        {{0}}, 0x4ac1f0, {{2, 0x4a, 0}}, 0x4ad530, {{0}}, 0x44c860, {{1, 0x52, 0xd}}, 0, 0, 0, 0};
    return update(calls, services, globals, entry, &step);
}

/* Original 0x44f690: the same as 0x44f560. */
uint32_t vertrix_port_block_effect_update_44f690(PORT_SIGNATURE)
{
    static const Update step = {
        {{0}}, 0x4ac1f0, {{2, 0x4a, 0}}, 0x4ad530, {{0}}, 0x44c860, {{1, 0x52, 0xd}}, 0, 0, 0, 0};
    return update(calls, services, globals, entry, &step);
}

/* Original 0x44f990: 0x4ac1f0 first; byte +0x45 16 and word +0x46 1, 0x4acc10; next
 * 0x44fa00. */
uint32_t vertrix_port_block_swell_update_44f990(PORT_SIGNATURE)
{
    static const Update step = {
        {{0}}, 0x4ac1f0, {{1, 0x45, 0x10}, {2, 0x46, 1}}, 0x4acc10, {{0}}, 0x44fa00, {{0}}, 0, 0,
        0,     0};
    return update(calls, services, globals, entry, &step);
}

/* Original 0x44e250: byte +0x95 2 and 0x4ac1f0 first; when due both 0x4ad580 and 0x4ad530 (with
 * what 0x4ac540 gave) must give 0 for the next handler 0x44e2d0; 0x4ac8a0 either way. */
uint32_t vertrix_port_block_slide_update_44e250(PORT_SIGNATURE)
{
    Port port;
    uint32_t actor = entry->eax;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    port_set8(&port, actor, 0x95, 2);
    port_forward(&port, entry, 0x4ac1f0, actor, entry->edx, entry->ebx, actor);
    port_forward(&port, entry, 0x4ac500, actor, vertrix_lift_edx, entry->ebx, actor);
    if (port_forward(&port, entry, 0x4ac520, actor, vertrix_lift_edx, entry->ebx, actor) == 1)
    {
        uint32_t amount =
            port_forward(&port, entry, 0x4ac540, actor, vertrix_lift_edx, entry->ebx, actor);
        uint32_t fade;
        port_forward(&port, entry, 0x4ac5b0, actor, vertrix_lift_edx, amount, actor);
        fade = port_forward(&port, entry, 0x4ad580, actor, amount, amount, actor);
        result = port_forward_esi(&port, entry, 0x4ad530, actor, amount, amount, actor, fade);
        if (fade == 0 && result == 0)
        {
            port_forward_esi(&port, entry, 0x4ac8f0, actor, 0x44e2d0, amount, actor, fade);
        }
        result =
            port_forward_esi(&port, entry, 0x4ac8a0, actor, vertrix_lift_edx, amount, actor, fade);
        return port_return(&port, result, entry->edx);
    }
    result = port_forward(&port, entry, 0x4ac8a0, actor, vertrix_lift_edx, entry->ebx, actor);
    return port_return(&port, result, entry->edx);
}

/* The restart of 0x449870 and 0x449e10: 1 when 0x449460 restarts with the dword at `table`;
 * otherwise 0x4493d0 with 0x74, the next handler `next` unless 0x476480 (0x54d640) holds with the
 * edx left or, when +0x70 is set, with the word +0x64; then 0x449390 with the dword after `table`
 * and dword +0x58 10. */
static uint32_t actor_restart_sound(PORT_SIGNATURE, uint32_t table, uint32_t next)
{
    Port port;
    uint32_t actor = entry->eax;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    result =
        port_forward(&port, entry, 0x449460, actor, port_u32(&port, 0, table), entry->ebx, actor);
    if (result == 1)
    {
        return port_return(&port, result, entry->edx);
    }
    port_forward(&port, entry, 0x4493d0, actor, 0x74, entry->ebx, actor);
    if (port_forward(&port, entry, 0x476480, 0x54d640, vertrix_lift_edx, entry->ebx, actor) == 0)
    {
        if (port_u32(&port, actor, 0x70) == 0 ||
            port_forward(&port, entry, 0x476480, 0x54d640, port_u16(&port, actor, 0x64), entry->ebx,
                         actor) == 0)
        {
            port_forward(&port, entry, 0x4ac8f0, actor, next, entry->ebx, actor);
        }
    }
    result = port_forward(&port, entry, 0x449390, actor, port_u32(&port, 0, table + 4), entry->ebx,
                          actor);
    port_set32(&port, actor, 0x58, 0xa);
    return port_return(&port, result, entry->edx);
}

/* Original 0x449870: the table 0x4fbed8, next 0x4498e0. */
uint32_t vertrix_port_actor_restart_sound_449870(PORT_SIGNATURE)
{
    return actor_restart_sound(calls, services, globals, entry, 0x4fbed8, 0x4498e0);
}

/* Original 0x449e10: the table 0x4fbef0, next 0x449e80. */
uint32_t vertrix_port_actor_restart_sound_449e10(PORT_SIGNATURE)
{
    return actor_restart_sound(calls, services, globals, entry, 0x4fbef0, 0x449e80);
}

/* The bob of 0x44aa20, 0x44aa90, 0x45d740 and 0x45d7b0: when due words +0x4a `height` and +0x4c
 * `speed` and 0x4ad530, which when done hands over to `next`; `follow` with what 0x4ac540 gave (0
 * when not due). */
static uint32_t actor_bob_follow(PORT_SIGNATURE, uint32_t height, uint32_t speed, uint32_t next,
                                 uint32_t follow)
{
    Port port;
    uint32_t actor = entry->eax;
    uint32_t amount = 0;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    port_forward(&port, entry, 0x4ac500, actor, entry->edx, entry->ebx, actor);
    if (port_forward(&port, entry, 0x4ac520, actor, vertrix_lift_edx, entry->ebx, actor) == 1)
    {
        amount = port_forward(&port, entry, 0x4ac540, actor, vertrix_lift_edx, 0, actor);
        port_forward(&port, entry, 0x4ac5b0, actor, amount, amount, actor);
        port_set16(&port, actor, 0x4a, height);
        port_set16(&port, actor, 0x4c, speed);
        if (port_forward(&port, entry, 0x4ad530, actor, vertrix_lift_edx, amount, actor) == 0)
        {
            port_forward(&port, entry, 0x4ac8f0, actor, next, amount, actor);
        }
    }
    result = port_forward(&port, entry, follow, actor, amount, amount, actor);
    return port_return(&port, result, entry->edx);
}

/* Original 0x44aa20: height 0, speed 5, next 0x44aa90, 0x44a720. */
uint32_t vertrix_port_actor_bob_follow_44aa20(PORT_SIGNATURE)
{
    return actor_bob_follow(calls, services, globals, entry, 0, 5, 0x44aa90, 0x44a720);
}

/* Original 0x44aa90: height 35, speed 5, next 0x44aa20, 0x44a720. */
uint32_t vertrix_port_actor_bob_follow_44aa90(PORT_SIGNATURE)
{
    return actor_bob_follow(calls, services, globals, entry, 0x23, 5, 0x44aa20, 0x44a720);
}

/* Original 0x45d740: height 0, speed 2, next 0x45d7b0, 0x45d820. */
uint32_t vertrix_port_actor_bob_follow_45d740(PORT_SIGNATURE)
{
    return actor_bob_follow(calls, services, globals, entry, 0, 2, 0x45d7b0, 0x45d820);
}

/* Original 0x45d7b0: height 20, speed 2, next 0x45d740, 0x45d820. */
uint32_t vertrix_port_actor_bob_follow_45d7b0(PORT_SIGNATURE)
{
    return actor_bob_follow(calls, services, globals, entry, 0x14, 2, 0x45d740, 0x45d820);
}

/* The selection display of 0x44bac0 and 0x44bb30: when the selection 0x532a6c is not the one kept
 * at +0x7c it is kept, 0x4adfe0, and 0x4b54d0 places the actor at the signed words `place` + 2
 * and + 6 with the size (the word at `place` + 0xe as a stack argument) and the width `width`
 * scaled by the selection's entry of `table` over `parts`. */
static uint32_t actor_show_selection(PORT_SIGNATURE, uint32_t place, uint32_t width, uint32_t table,
                                     uint32_t parts)
{
    Port port;
    uint32_t actor = entry->eax;
    uint32_t selection;
    uint32_t scaled;
    uint32_t size;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    selection = port_u32(&port, 0, 0x532a6c);
    if (selection == port_u32(&port, actor, 0x7c))
    {
        return port_return(&port, actor, entry->edx);
    }
    port_set32(&port, actor, 0x7c, selection);
    port_forward_esi(&port, entry, 0x4adfe0, actor, selection, entry->ebx, entry->ecx, actor);
    selection = port_u32(&port, 0, 0x532a6c);
    scaled = port_u32(&port, 0, width) * port_u32(&port, selection * 4, table) / parts;
    size = port_u16(&port, 0, place + 0xe);
    result = port_forward_stack(&port, entry, 0x4b54d0, actor,
                                (uint32_t)(int32_t)(int16_t)port_u16(&port, 0, place + 2),
                                (uint32_t)(int32_t)(int16_t)port_u16(&port, 0, place + 6),
                                scaled & 0xffff, actor, &size, 1);
    return port_return(&port, result, entry->edx);
}

/* Original 0x44bac0: the place 0x4f86c2, width 0x4f86cc, the table 0x4f8cec over 12. */
uint32_t vertrix_port_actor_show_selection_44bac0(PORT_SIGNATURE)
{
    return actor_show_selection(calls, services, globals, entry, 0x4f86c2, 0x4f86cc, 0x4f8cec, 0xc);
}

/* Original 0x44bb30: the place 0x4f86b2, width 0x4f86bc, the table 0x4f8d38 over 9. */
uint32_t vertrix_port_actor_show_selection_44bb30(PORT_SIGNATURE)
{
    return actor_show_selection(calls, services, globals, entry, 0x4f86b2, 0x4f86bc, 0x4f8d38, 9);
}

/* Original 0x44c5a0: the player's (+4, 0x540f88) kind (+0x4c8, a byte): when set the animation
 * set 0x544aa4 at its frame (0x53bb10, 8 bytes a kind) less the base 0x53bc20, dword +0x58 the
 * kind, 0x4ac510 with 0x44c610 and the handler it leaves; 0x4ac8a0 either way. */
uint32_t vertrix_port_actor_kind_animation_44c5a0(PORT_SIGNATURE)
{
    Port port;
    uint32_t actor = entry->eax;
    uint32_t player;
    uint32_t kind;
    uint32_t frame;
    uint32_t base;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    player = port_u32(&port, port_u32(&port, actor, 4) * 4, 0x540f88);
    kind = port_u32(&port, player, 0x4c8) & 0xff;
    if (kind == 0)
    {
        result = port_forward(&port, entry, 0x4ac8a0, actor, player, kind, actor);
        return port_return(&port, result, entry->edx);
    }
    frame = port_u8(&port, kind * 8, 0x53bb10);
    base = port_u8(&port, 0, 0x53bc20);
    port_call_with(&port, 0x4ac8d0, actor, 0x544aa4, kind, actor, frame, base, entry->ebp);
    port_call_with(&port, 0x4ac710, actor, frame - base, kind, actor, frame, base, entry->ebp);
    port_set32(&port, actor, 0x58, kind);
    port_call_with(&port, 0x4ac510, actor, 0x44c610, kind, actor, frame, base, entry->ebp);
    port_call_with(&port, 0x4ac8f0, actor, vertrix_lift_edx, kind, actor, frame, base, entry->ebp);
    result = port_call_with(&port, 0x4ac8a0, actor, vertrix_lift_edx, kind, actor, frame, base,
                            entry->ebp);
    return port_return(&port, result, entry->edx);
}

/* Original 0x44c610: when due byte +0x4f 100 and words +0x50 4, +0x4a 100 and +0x4c 4; when both
 * 0x4ad580 and 0x4ad530 (with what 0x4ac540 gave) give 0, the next handler 0x44c680. */
uint32_t vertrix_port_actor_rise_fade_44c610(PORT_SIGNATURE)
{
    Port port;
    uint32_t actor = entry->eax;
    uint32_t amount;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    port_forward(&port, entry, 0x4ac500, actor, entry->edx, entry->ebx, actor);
    result = port_forward(&port, entry, 0x4ac520, actor, vertrix_lift_edx, entry->ebx, actor);
    if (result != 1)
    {
        return port_return(&port, result, entry->edx);
    }
    amount = port_forward(&port, entry, 0x4ac540, actor, vertrix_lift_edx, entry->ebx, actor);
    port_forward(&port, entry, 0x4ac5b0, actor, vertrix_lift_edx, amount, actor);
    port_set8(&port, actor, 0x4f, 0x64);
    port_set16(&port, actor, 0x50, 4);
    port_set16(&port, actor, 0x4a, 0x64);
    port_set16(&port, actor, 0x4c, 4);
    result = port_forward(&port, entry, 0x4ad580, actor, amount, amount, actor);
    if (result == 0)
    {
        result = port_forward(&port, entry, 0x4ad530, actor, amount, amount, actor);
        if (result == 0)
        {
            result = port_forward(&port, entry, 0x4ac8f0, actor, 0x44c680, amount, actor);
        }
    }
    return port_return(&port, result, entry->edx);
}

/* Original 0x44c780: when due words +0x4a 152 and +0x4c 4 and 0x4ad530; when that gives 0, the
 * animation set 0x544aa4 at the frame +0x64, 0x4ac8a0 with 0x44c680 and the handler it leaves. */
uint32_t vertrix_port_actor_rise_settle_44c780(PORT_SIGNATURE)
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
    port_set16(&port, actor, 0x4a, 0x98);
    port_set16(&port, actor, 0x4c, 4);
    result = port_forward(&port, entry, 0x4ad530, actor, vertrix_lift_edx, entry->ebx, actor);
    if (result != 0)
    {
        return port_return(&port, result, entry->edx);
    }
    port_forward(&port, entry, 0x4ac8d0, actor, 0x544aa4, entry->ebx, actor);
    port_forward(&port, entry, 0x4ac710, actor, port_u32(&port, actor, 0x64), entry->ebx, actor);
    port_forward(&port, entry, 0x4ac8a0, actor, 0x44c680, entry->ebx, actor);
    result = port_forward(&port, entry, 0x4ac8f0, actor, vertrix_lift_edx, entry->ebx, actor);
    return port_return(&port, result, entry->edx);
}

/* Original 0x44c7f0: when due byte +0x4f 0, word +0x50 2 and 0x4ad580; when that gives 0, no
 * animation set (0x4ac8d0, 0x4ac710 and 0x4ac950 with 0), dword +0x58 0 and the next handler
 * 0x44c5a0. */
uint32_t vertrix_port_actor_fade_clear_44c7f0(PORT_SIGNATURE)
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
    port_set8(&port, actor, 0x4f, 0);
    port_set16(&port, actor, 0x50, 2);
    result = port_forward(&port, entry, 0x4ad580, actor, vertrix_lift_edx, entry->ebx, actor);
    if (result != 0)
    {
        return port_return(&port, result, entry->edx);
    }
    port_forward(&port, entry, 0x4ac8d0, actor, 0, entry->ebx, actor);
    port_forward(&port, entry, 0x4ac710, actor, 0, entry->ebx, actor);
    port_forward(&port, entry, 0x4ac950, actor, 0, entry->ebx, actor);
    port_set32(&port, actor, 0x58, 0);
    result = port_forward(&port, entry, 0x4ac8f0, actor, 0x44c5a0, entry->ebx, actor);
    return port_return(&port, result, entry->edx);
}

/* Original 0x44fa00: 0x4ac1f0 first; byte +0x45 0 and word +0x46 1, 0x4acc10; next 0x44f990. */
uint32_t vertrix_port_block_swell_update_44fa00(PORT_SIGNATURE)
{
    static const Update step = {
        {{0}}, 0x4ac1f0, {{1, 0x45, 0}, {2, 0x46, 1}}, 0x4acc10, {{0}}, 0x44f990, {{0}}, 0, 0,
        0,     0};
    return update(calls, services, globals, entry, &step);
}

/* Original 0x450330: bytes +0x93 0, +0x4e 50 and +0x95 3 and 0x4ac1f0 first; words +0x4a 200 and
 * +0x4c 8, 0x4ad530; next 0x4503b0, then bytes +0x93 1 and +0x4e 100. */
uint32_t vertrix_port_block_finish_effect_update_450330(PORT_SIGNATURE)
{
    static const Update step = {{{1, 0x93, 0}, {1, 0x4e, 0x32}, {1, 0x95, 3}},
                                0x4ac1f0,
                                {{2, 0x4a, 0xc8}, {2, 0x4c, 8}},
                                0x4ad530,
                                {{0}},
                                0x4503b0,
                                {{1, 0x93, 1}, {1, 0x4e, 0x64}},
                                0,
                                0,
                                0,
                                0};
    return update(calls, services, globals, entry, &step);
}

/* Original 0x4504e0: words +0x4a 100 and +0x4c 3, 0x4ad530; bytes +0x95 4 and +0x4e 50 and next
 * 0x450550. */
uint32_t vertrix_port_block_finish_effect_update_4504e0(PORT_SIGNATURE)
{
    static const Update step = {{{0}},
                                0,
                                {{2, 0x4a, 0x64}, {2, 0x4c, 3}},
                                0x4ad530,
                                {{1, 0x95, 4}, {1, 0x4e, 0x32}},
                                0x450550,
                                {{0}},
                                0,
                                0,
                                0,
                                0};
    return update(calls, services, globals, entry, &step);
}

/* Original 0x450630: the same, next 0x4506a0. */
uint32_t vertrix_port_block_finish_effect_update_450630(PORT_SIGNATURE)
{
    static const Update step = {{{0}},
                                0,
                                {{2, 0x4a, 0x64}, {2, 0x4c, 3}},
                                0x4ad530,
                                {{1, 0x95, 4}, {1, 0x4e, 0x32}},
                                0x4506a0,
                                {{0}},
                                0,
                                0,
                                0,
                                0};
    return update(calls, services, globals, entry, &step);
}

/* Original 0x450550 (the actor in ebx throughout): words +0x4a -100 and +0x4c 4, 0x4ad530; next
 * 0x4505c0. */
uint32_t vertrix_port_block_finish_effect_update_450550(PORT_SIGNATURE)
{
    static const Update step = {
        {{0}}, 0, {{2, 0x4a, 0xff9c}, {2, 0x4c, 4}}, 0x4ad530, {{0}}, 0x4505c0, {{0}}, 0, 1, 0, 0};
    return update(calls, services, globals, entry, &step);
}

/* Original 0x4505c0 (the actor in ebx): words +0x4a -200 and +0x4c 10, 0x4ad530; no handler,
 * then byte +0x15d 2. */
uint32_t vertrix_port_block_finish_effect_update_4505c0(PORT_SIGNATURE)
{
    static const Update step = {
        {{0}}, 0, {{2, 0x4a, 0xff38}, {2, 0x4c, 0xa}}, 0x4ad530, {{0}}, 0, {{1, 0x15d, 2}}, 0, 1,
        0,     0};
    return update(calls, services, globals, entry, &step);
}

/* Original 0x4506a0 (the actor in ebx): words +0x4a 0 and +0x4c 4, 0x4ad530; no handler, then
 * byte +0x15d 2. */
uint32_t vertrix_port_block_finish_effect_update_4506a0(PORT_SIGNATURE)
{
    static const Update step = {
        {{0}}, 0, {{2, 0x4a, 0}, {2, 0x4c, 4}}, 0x4ad530, {{0}}, 0, {{1, 0x15d, 2}}, 0, 1, 0, 0};
    return update(calls, services, globals, entry, &step);
}

/* Original 0x44fad0: the number's owner (0x4b5eb0 on 0x54671c with +4) and its player (+4,
 * 0x540f88); 0x4adfa0 with 0, and when the owner's +0x180 is not the player's +0x17c word +0x48
 * -100, 0x4adfa0 with 1, 0x4ac510 with 0x44fb40 and the handler it leaves. */
uint32_t vertrix_port_number_transition_update_44fad0(PORT_SIGNATURE)
{
    Port port;
    uint32_t actor = entry->eax;
    uint32_t owner;
    uint32_t player;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    owner = port_forward(&port, entry, 0x4b5eb0, 0x54671c, port_u32(&port, actor, 4), entry->ebx,
                         actor);
    player = port_u32(&port, port_u32(&port, owner, 4) * 4, 0x540f88);
    result = port_forward_esi(&port, entry, 0x4adfa0, actor, 0, owner, actor, player);
    if (port_u32(&port, owner, 0x180) == port_u32(&port, player, 0x17c))
    {
        return port_return(&port, result, entry->edx);
    }
    port_set16(&port, actor, 0x48, 0xff9c);
    port_forward_esi(&port, entry, 0x4adfa0, actor, 1, owner, actor, player);
    port_forward_esi(&port, entry, 0x4ac510, actor, 0x44fb40, owner, actor, player);
    result =
        port_forward_esi(&port, entry, 0x4ac8f0, actor, vertrix_lift_edx, owner, actor, player);
    return port_return(&port, result, entry->edx);
}

/* The numbers' moves of 0x44fb40, 0x44fcf0 and 0x44fdb0: when due words +0x4a 50 and +0x4c
 * `speed` and 0x4ad530; when done the owner (0x4b5eb0 on 0x54671c with +4) gets `other` (for
 * `compare`, only when its +0x180 is not its player's +0x178) and the actor `next`. */
static uint32_t number_move(PORT_SIGNATURE, uint32_t speed, uint32_t other, uint32_t next,
                            int compare)
{
    Port port;
    uint32_t actor = entry->eax;
    uint32_t ebx = entry->ebx;
    uint32_t owner;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    port_forward(&port, entry, 0x4ac500, actor, entry->edx, ebx, actor);
    result = port_forward(&port, entry, 0x4ac520, actor, vertrix_lift_edx, ebx, actor);
    if (result != 1)
    {
        return port_return(&port, result, entry->edx);
    }
    result = port_forward(&port, entry, 0x4ac540, actor, vertrix_lift_edx, ebx, actor);
    port_forward(&port, entry, 0x4ac5b0, actor, result, ebx, actor);
    port_set16(&port, actor, 0x4a, 0x32);
    port_set16(&port, actor, 0x4c, speed);
    result = port_forward(&port, entry, 0x4ad530, actor, vertrix_lift_edx, ebx, actor);
    if (result != 0)
    {
        return port_return(&port, result, entry->edx);
    }
    owner = port_forward(&port, entry, 0x4b5eb0, 0x54671c, port_u32(&port, actor, 4), ebx, actor);
    if (compare)
    {
        uint32_t player = port_u32(&port, port_u32(&port, owner, 4) * 4, 0x540f88);
        ebx = port_u32(&port, owner, 0x180);
        if (ebx != port_u32(&port, player, 0x178))
        {
            port_forward(&port, entry, 0x4ac8f0, owner, other, ebx, actor);
        }
    }
    else
    {
        port_forward(&port, entry, 0x4ac8f0, owner, other, ebx, actor);
    }
    result = port_forward(&port, entry, 0x4ac8f0, actor, next, ebx, actor);
    return port_return(&port, result, entry->edx);
}

/* Original 0x44fb40: speed 2, the owner 0x44faa0, next 0x44fbb0. */
uint32_t vertrix_port_number_transition_update_44fb40(PORT_SIGNATURE)
{
    return number_move(calls, services, globals, entry, 2, 0x44faa0, 0x44fbb0, 0);
}

/* Original 0x44fcf0: speed 2, the owner 0x44fc30, next 0x44fd60. */
uint32_t vertrix_port_number_transition_configured_44fcf0(PORT_SIGNATURE)
{
    return number_move(calls, services, globals, entry, 2, 0x44fc30, 0x44fd60, 0);
}

/* Original 0x44fdb0: speed 4, the owner 0x44fc30 when it differs, next 0x44fe30. */
uint32_t vertrix_port_number_transition_configured_44fdb0(PORT_SIGNATURE)
{
    return number_move(calls, services, globals, entry, 4, 0x44fc30, 0x44fe30, 1);
}

/* Original 0x450040: with the indicator's storage (0x4b5eb0 on 0x54671c with +4) of state 1
 * (+0x58), or whose +0x64 is below the actor's +0x58 (signed), 0x4ac510 with 0x4500b0, byte +0x4f
 * 0, word +0x50 1 (3 for the second) and the handler left. */
uint32_t vertrix_port_ui_indicator_storage_update_450040(PORT_SIGNATURE)
{
    Port port;
    uint32_t actor = entry->eax;
    uint32_t storage;
    uint32_t speed;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    storage = port_forward(&port, entry, 0x4b5eb0, 0x54671c, port_u32(&port, actor, 4), entry->ebx,
                           actor);
    if (storage == 0)
    {
        return port_return(&port, storage, entry->edx);
    }
    if (port_u32(&port, storage, 0x58) == 1)
    {
        speed = 1;
    }
    else
    {
        result = port_u32(&port, storage, 0x64);
        if ((int32_t)result >= (int32_t)port_u32(&port, actor, 0x58))
        {
            return port_return(&port, result, entry->edx);
        }
        speed = 3;
    }
    port_forward(&port, entry, 0x4ac510, actor, 0x4500b0, entry->ebx, actor);
    port_set8(&port, actor, 0x4f, 0);
    port_set16(&port, actor, 0x50, speed);
    result = port_forward(&port, entry, 0x4ac8f0, actor, vertrix_lift_edx, entry->ebx, actor);
    return port_return(&port, result, entry->edx);
}

/* Original 0x450130: with the border's storage (0x4b5eb0 on 0x54671c with +4) of state 1
 * (+0x58): dword +0x58 3, 0x4adfa0 with 1, words +0x48 -40, +0x4a 0 and +0x4c the width of 3
 * (0x4826c0 on 0x598d30) and 2, 0x4ac510 with 0x4501a0 and the handler left. */
uint32_t vertrix_port_ui_border_storage_update_450130(PORT_SIGNATURE)
{
    Port port;
    uint32_t actor = entry->eax;
    uint32_t storage;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    storage = port_forward(&port, entry, 0x4b5eb0, 0x54671c, port_u32(&port, actor, 4), entry->ebx,
                           actor);
    if (storage == 0 || port_u32(&port, storage, 0x58) != 1)
    {
        return port_return(&port, storage, entry->edx);
    }
    port_set32(&port, actor, 0x58, 3);
    port_forward(&port, entry, 0x4adfa0, actor, 1, entry->ebx, actor);
    port_set16(&port, actor, 0x48, 0xffd8);
    port_set16(&port, actor, 0x4a, 0);
    result = port_forward(&port, entry, 0x4826c0, 0x598d30, 3, entry->ebx, actor);
    port_set16(&port, actor, 0x4c, result + 2);
    port_forward(&port, entry, 0x4ac510, actor, 0x4501a0, entry->ebx, actor);
    result = port_forward(&port, entry, 0x4ac8f0, actor, vertrix_lift_edx, entry->ebx, actor);
    return port_return(&port, result, entry->edx);
}

/* Original 0x450200: when due and 0x4ad790 is done, word +0x4a -100, word +0x4c half (to zero)
 * of five times itself, word +0x48 0 and the next handler 0x450270. */
uint32_t vertrix_port_ui_border_storage_update_450200(PORT_SIGNATURE)
{
    Port port;
    uint32_t actor = entry->eax;
    int32_t speed;
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
    result = port_forward(&port, entry, 0x4ad790, actor, vertrix_lift_edx, entry->ebx, actor);
    if (result != 0)
    {
        return port_return(&port, result, entry->edx);
    }
    port_set16(&port, actor, 0x4a, 0xff9c);
    speed = (int16_t)port_u16(&port, actor, 0x4c) * 5 / 2;
    port_set16(&port, actor, 0x4c, (uint32_t)speed);
    port_set16(&port, actor, 0x48, 0);
    result = port_forward(&port, entry, 0x4ac8f0, actor, 0x450270, entry->ebx, actor);
    return port_return(&port, result, entry->edx);
}

/* Original 0x450bf0: when due and 0x4ad790 is done, words +0x48 5, +0x4a -60 and +0x4c 2 (for
 * +0x7c 1, otherwise 1) and the next handler 0x450c70. */
uint32_t vertrix_port_linked_alternating_update_450bf0(PORT_SIGNATURE)
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
    result = port_forward(&port, entry, 0x4ad790, actor, vertrix_lift_edx, entry->ebx, actor);
    if (result != 0)
    {
        return port_return(&port, result, entry->edx);
    }
    port_set16(&port, actor, 0x48, 5);
    port_set16(&port, actor, 0x4a, 0xffc4);
    port_set16(&port, actor, 0x4c, port_u32(&port, actor, 0x7c) == 1 ? 2 : 1);
    result = port_forward(&port, entry, 0x4ac8f0, actor, 0x450c70, entry->ebx, actor);
    return port_return(&port, result, entry->edx);
}

/* Original 0x456980 (the actor in ebx): 0x4adfe0 first, byte +0x93 1; byte +0x4f 100 and word
 * +0x50 5, 0x4ad580; byte +0x93 0 and next 0x456bf0. */
uint32_t vertrix_port_actor_fade_in_456980(PORT_SIGNATURE)
{
    static const Update step = {{{1, 0x93, 1}},
                                0,
                                {{1, 0x4f, 0x64}, {2, 0x50, 5}},
                                0x4ad580,
                                {{1, 0x93, 0}},
                                0x456bf0,
                                {{0}},
                                0,
                                1,
                                0x4adfe0,
                                0};
    return update(calls, services, globals, entry, &step);
}

/* Original 0x456a00 (the actor in ebx): 0x4adfe0 first, byte +0x93 1; byte +0x4f 0 and word +0x50
 * 5, 0x4ad580; next 0x456ca0, then byte +0x93 1. */
uint32_t vertrix_port_actor_fade_out_456a00(PORT_SIGNATURE)
{
    static const Update step = {{{1, 0x93, 1}}, 0,     {{1, 0x4f, 0}, {2, 0x50, 5}},
                                0x4ad580,       {{0}}, 0x456ca0,
                                {{1, 0x93, 1}}, 0,     1,
                                0x4adfe0,       0};
    return update(calls, services, globals, entry, &step);
}

/* Original 0x456b80 (the actor in ebx): 0x4adfe0 first; words +0x4a 0 and +0x4c 6, 0x4ad530;
 * byte +0x15d 0 and next 0x456bf0. */
uint32_t vertrix_port_actor_rise_stop_456b80(PORT_SIGNATURE)
{
    static const Update step = {
        {{0}},    0, {{2, 0x4a, 0}, {2, 0x4c, 6}}, 0x4ad530, {{1, 0x15d, 0}}, 0x456bf0, {{0}}, 0, 1,
        0x4adfe0, 0};
    return update(calls, services, globals, entry, &step);
}

/* The swing of 0x456a80 and 0x456b00 (the actor in esi): 0x4adfe0 first; when due words +0x4a
 * `height` and +0x4c `speed` and 0x4ad530 (its answer unused), byte +0x45 `bend` and word +0x46 1
 * and 0x4acc10, which when done hands over to `next`; 0x4ac8a0 either way. */
static uint32_t actor_swing(PORT_SIGNATURE, uint32_t height, uint32_t speed, uint32_t bend,
                            uint32_t next)
{
    Port port;
    uint32_t actor = entry->eax;
    uint32_t ebx = entry->ebx;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    port_forward_esi(&port, entry, 0x4adfe0, actor, entry->edx, ebx, actor, actor);
    port_forward_esi(&port, entry, 0x4ac500, actor, vertrix_lift_edx, ebx, actor, actor);
    if (port_forward_esi(&port, entry, 0x4ac520, actor, vertrix_lift_edx, ebx, actor, actor) == 1)
    {
        ebx = port_forward_esi(&port, entry, 0x4ac540, actor, vertrix_lift_edx, ebx, actor, actor);
        port_forward_esi(&port, entry, 0x4ac5b0, actor, vertrix_lift_edx, ebx, actor, actor);
        port_set16(&port, actor, 0x4a, height);
        port_set16(&port, actor, 0x4c, speed);
        port_forward_esi(&port, entry, 0x4ad530, actor, ebx, ebx, actor, actor);
        port_set8(&port, actor, 0x45, bend);
        port_set16(&port, actor, 0x46, 1);
        if (port_forward_esi(&port, entry, 0x4acc10, actor, ebx, ebx, actor, actor) == 0)
        {
            port_forward_esi(&port, entry, 0x4ac8f0, actor, next, ebx, actor, actor);
        }
    }
    result = port_forward_esi(&port, entry, 0x4ac8a0, actor, vertrix_lift_edx, ebx, actor, actor);
    return port_return(&port, result, entry->edx);
}

/* Original 0x456a80: height -200, speed 6, bend 0, next 0x456b00. */
uint32_t vertrix_port_actor_swing_456a80(PORT_SIGNATURE)
{
    return actor_swing(calls, services, globals, entry, 0xff38, 6, 0, 0x456b00);
}

/* Original 0x456b00: height 200, speed 12, bend 16, next 0x456b80. */
uint32_t vertrix_port_actor_swing_456b00(PORT_SIGNATURE)
{
    return actor_swing(calls, services, globals, entry, 0xc8, 0xc, 0x10, 0x456b80);
}

/* Original 0x456900: when due words +0x4a 0 and +0x4c 5 and 0x4ad530 (its answer unused); when
 * 0x4aca60, 0x4acab0 and 0x4acb00 (with what 0x4ac540 gave) all give 0, no next handler. */
uint32_t vertrix_port_actor_settle_all_456900(PORT_SIGNATURE)
{
    Port port;
    uint32_t actor = entry->eax;
    uint32_t amount;
    uint32_t first;
    uint32_t second;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    port_forward(&port, entry, 0x4ac500, actor, entry->edx, entry->ebx, actor);
    result = port_forward(&port, entry, 0x4ac520, actor, vertrix_lift_edx, entry->ebx, actor);
    if (result != 1)
    {
        return port_return(&port, result, entry->edx);
    }
    amount = port_forward(&port, entry, 0x4ac540, actor, vertrix_lift_edx, entry->ebx, actor);
    port_forward(&port, entry, 0x4ac5b0, actor, vertrix_lift_edx, amount, actor);
    port_set16(&port, actor, 0x4a, 0);
    port_set16(&port, actor, 0x4c, 5);
    port_forward(&port, entry, 0x4ad530, actor, amount, amount, actor);
    first = port_forward(&port, entry, 0x4aca60, actor, amount, amount, actor);
    second = port_forward_esi(&port, entry, 0x4acab0, actor, amount, amount, actor, first);
    result =
        port_call_with(&port, 0x4acb00, actor, amount, amount, actor, first, second, entry->ebp);
    if (first == 0 && second == 0 && result == 0)
    {
        result = port_call_with(&port, 0x4ac8f0, actor, 0, amount, actor, 0, 0, entry->ebp);
    }
    return port_return(&port, result, entry->edx);
}

/* Original 0x45b710: 0x4ac1f0 first; words +0x4a 0 and +0x4c 4, 0x4ad530; dwords +0x5c 18, +0x58
 * 0 and +0x60 1 and next 0x45b790. */
uint32_t vertrix_port_block_wait_update_45b710(PORT_SIGNATURE)
{
    static const Update step = {{{0}},
                                0x4ac1f0,
                                {{2, 0x4a, 0}, {2, 0x4c, 4}},
                                0x4ad530,
                                {{4, 0x5c, 0x12}, {4, 0x58, 0}, {4, 0x60, 1}},
                                0x45b790,
                                {{0}},
                                0,
                                0,
                                0,
                                0};
    return update(calls, services, globals, entry, &step);
}

/* Original 0x45b8d0: 0x4ac1f0 first; words +0x4a 50 and +0x4c 4, 0x4ad530; bytes +0x93 1 and +0x95
 * 3 and next 0x45b950. */
uint32_t vertrix_port_block_rise_update_45b8d0(PORT_SIGNATURE)
{
    static const Update step = {{{0}},
                                0x4ac1f0,
                                {{2, 0x4a, 0x32}, {2, 0x4c, 4}},
                                0x4ad530,
                                {{1, 0x93, 1}, {1, 0x95, 3}},
                                0x45b950,
                                {{0}},
                                0,
                                0,
                                0,
                                0};
    return update(calls, services, globals, entry, &step);
}

/* Original 0x45b950: 0x4ac1f0 first; byte +0x4f 0 and word +0x50 8, 0x4ad580; next 0x44c860. */
uint32_t vertrix_port_block_fade_update_45b950(PORT_SIGNATURE)
{
    static const Update step = {
        {{0}}, 0x4ac1f0, {{1, 0x4f, 0}, {2, 0x50, 8}}, 0x4ad580, {{0}}, 0x44c860, {{0}}, 0, 0,
        0,     0};
    return update(calls, services, globals, entry, &step);
}

/* Original 0x45bc00: 0x4ac1f0 first; words +0x4a 0 and +0x4c 4, 0x4ad530; dwords +0x5c 5, +0x58 0
 * and +0x60 1 and next 0x45bd00. */
uint32_t vertrix_port_block_wait_update_45bc00(PORT_SIGNATURE)
{
    static const Update step = {{{0}},
                                0x4ac1f0,
                                {{2, 0x4a, 0}, {2, 0x4c, 4}},
                                0x4ad530,
                                {{4, 0x5c, 5}, {4, 0x58, 0}, {4, 0x60, 1}},
                                0x45bd00,
                                {{0}},
                                0,
                                0,
                                0,
                                0};
    return update(calls, services, globals, entry, &step);
}

/* Original 0x45bc80: the same with word +0x4c 2 and dword +0x5c 4. */
uint32_t vertrix_port_block_wait_update_45bc80(PORT_SIGNATURE)
{
    static const Update step = {{{0}},
                                0x4ac1f0,
                                {{2, 0x4a, 0}, {2, 0x4c, 2}},
                                0x4ad530,
                                {{4, 0x5c, 4}, {4, 0x58, 0}, {4, 0x60, 1}},
                                0x45bd00,
                                {{0}},
                                0,
                                0,
                                0,
                                0};
    return update(calls, services, globals, entry, &step);
}

/* Original 0x45beb0: 0x4ac1f0 first; words +0x4a 0 and +0x4c 4, 0x4ad530; dwords +0x58 0, +0x5c 0
 * and +0x60 1 and next 0x45bf20. */
uint32_t vertrix_port_block_wait_update_45beb0(PORT_SIGNATURE)
{
    static const Update step = {{{0}},
                                0x4ac1f0,
                                {{2, 0x4a, 0}, {2, 0x4c, 4}},
                                0x4ad530,
                                {{4, 0x58, 0}, {4, 0x5c, 0}, {4, 0x60, 1}},
                                0x45bf20,
                                {{0}},
                                0,
                                0,
                                0,
                                0};
    return update(calls, services, globals, entry, &step);
}

/* Original 0x45bff0: 0x4ac1f0 first; byte +0x4f 100 and word +0x50 5, 0x4ad580; next 0x44c860. */
uint32_t vertrix_port_block_fade_update_45bff0(PORT_SIGNATURE)
{
    static const Update step = {
        {{0}}, 0x4ac1f0, {{1, 0x4f, 0x64}, {2, 0x50, 5}}, 0x4ad580, {{0}}, 0x44c860, {{0}}, 0, 0,
        0,     0};
    return update(calls, services, globals, entry, &step);
}

/* Original 0x458260: 0x457810 first; 0x4ad530; words +0x4a 0 and +0x4c 5 and next 0x4582d0;
 * 0x457890 either way. */
uint32_t vertrix_port_object_flip_update_458260(PORT_SIGNATURE)
{
    static const Update step = {{{0}},    0x457810, {{0}}, 0x4ad530, {{2, 0x4a, 0}, {2, 0x4c, 5}},
                                0x4582d0, {{0}},    0,     0,        0,
                                0x457890};
    return update(calls, services, globals, entry, &step);
}

/* Original 0x4584f0: 0x457810 first; 0x4ad530; words +0x4a -150 and +0x4c 2, byte +0x93 1 and next
 * 0x458560; 0x457890 either way. */
uint32_t vertrix_port_object_flip_update_4584f0(PORT_SIGNATURE)
{
    static const Update step = {
        {{0}},    0x457810, {{0}}, 0x4ad530, {{2, 0x4a, 0xff6a}, {2, 0x4c, 2}, {1, 0x93, 1}},
        0x458560, {{0}},    0,     0,        0,
        0x457890};
    return update(calls, services, globals, entry, &step);
}

/* Original 0x4597e0: byte +0x4e 0; when due 0x4ac5b0 with 640, words +0xe and +0x16 the sizes
 * 640 and 480 by 0x4826c0 on 0x598d30, the next handler 0x459860, 0x4ac7e0 and byte +0x4e 50;
 * 0x4ac8a0 either way. */
uint32_t vertrix_port_actor_screen_place_4597e0(PORT_SIGNATURE)
{
    Port port;
    uint32_t actor = entry->eax;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    port_set8(&port, actor, 0x4e, 0);
    port_forward(&port, entry, 0x4ac500, actor, entry->edx, entry->ebx, actor);
    if (port_forward(&port, entry, 0x4ac520, actor, vertrix_lift_edx, entry->ebx, actor) == 1)
    {
        port_forward(&port, entry, 0x4ac540, actor, vertrix_lift_edx, entry->ebx, actor);
        port_forward(&port, entry, 0x4ac5b0, actor, 0x280, entry->ebx, actor);
        result =
            port_forward(&port, entry, 0x4826c0, 0x598d30, vertrix_lift_edx, entry->ebx, actor);
        port_set16(&port, actor, 0xe, result);
        result = port_forward(&port, entry, 0x4826c0, 0x598d30, 0x1e0, entry->ebx, actor);
        port_set16(&port, actor, 0x16, result);
        port_forward(&port, entry, 0x4ac8f0, actor, 0x459860, entry->ebx, actor);
        port_forward(&port, entry, 0x4ac7e0, actor, vertrix_lift_edx, entry->ebx, actor);
        port_set8(&port, actor, 0x4e, 0x32);
    }
    result = port_forward(&port, entry, 0x4ac8a0, actor, vertrix_lift_edx, entry->ebx, actor);
    return port_return(&port, result, entry->edx);
}

/* The frame steps of 0x459a30 and 0x459b60: `before` stored; when due and `check` gives 0, the
 * frame +0x64 moves on by 2 (back by 2 past +0x68, signed), 0x4ac710 with it, 0x4ac8a0 with
 * `next`, the handler it leaves and dword +0x58 0. */
static uint32_t actor_frame_step(PORT_SIGNATURE, const Store *before, uint32_t check, uint32_t next)
{
    Port port;
    uint32_t actor = entry->eax;
    uint32_t frame;
    uint32_t last;
    uint32_t esi = entry->esi;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    store(&port, actor, before);
    port_forward(&port, entry, 0x4ac500, actor, entry->edx, entry->ebx, actor);
    result = port_forward(&port, entry, 0x4ac520, actor, vertrix_lift_edx, entry->ebx, actor);
    if (result != 1)
    {
        return port_return(&port, result, entry->edx);
    }
    result = port_forward(&port, entry, 0x4ac540, actor, vertrix_lift_edx, entry->ebx, actor);
    port_forward(&port, entry, 0x4ac5b0, actor, result, entry->ebx, actor);
    result = port_forward(&port, entry, check, actor, vertrix_lift_edx, entry->ebx, actor);
    if (result != 0)
    {
        return port_return(&port, result, entry->edx);
    }
    frame = port_u32(&port, actor, 0x64) + 2;
    last = port_u32(&port, actor, 0x68);
    port_set32(&port, actor, 0x64, frame);
    if ((int32_t)frame >= (int32_t)last)
    {
        esi = frame - 4;
        port_set32(&port, actor, 0x64, esi);
    }
    port_forward_esi(&port, entry, 0x4ac710, actor, port_u32(&port, actor, 0x64), last, actor, esi);
    port_forward_esi(&port, entry, 0x4ac8a0, actor, next, last, actor, esi);
    result = port_forward_esi(&port, entry, 0x4ac8f0, actor, vertrix_lift_edx, last, actor, esi);
    port_set32(&port, actor, 0x58, 0);
    return port_return(&port, result, entry->edx);
}

/* Original 0x459a30: dword +0x5c 100, 0x4ad6e0, next 0x459ab0. */
uint32_t vertrix_port_actor_frame_step_459a30(PORT_SIGNATURE)
{
    static const Store before = {4, 0x5c, 0x64};
    return actor_frame_step(calls, services, globals, entry, &before, 0x4ad6e0, 0x459ab0);
}

/* Original 0x459b60: byte +0x4f 0, 0x4ad580, next 0x459b00. */
uint32_t vertrix_port_actor_frame_step_459b60(PORT_SIGNATURE)
{
    static const Store before = {1, 0x4f, 0};
    return actor_frame_step(calls, services, globals, entry, &before, 0x4ad580, 0x459b00);
}

/* Original 0x457810: when 0x4ac390 gives 1 (after 0x4ac370): 0x4ac3b0, 0x4ac380 and 0x4ac810, the
 * side +0x64 flipped (1 less it), byte +0x52 the size of 13 (0x4826c0 on 0x598d30), the frame of
 * 0x43f420 for the side (signed byte) and the byte +0x58 by 0x4ac950, and word +0xc the size of
 * 11 less 5 (the answer). */
uint32_t vertrix_port_object_flip_side_457810(PORT_SIGNATURE)
{
    Port port;
    uint32_t actor = entry->eax;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    port_forward(&port, entry, 0x4ac370, actor, entry->edx, entry->ebx, actor);
    result = port_forward(&port, entry, 0x4ac390, actor, vertrix_lift_edx, entry->ebx, actor);
    if (result != 1)
    {
        return port_return(&port, result, entry->edx);
    }
    port_forward(&port, entry, 0x4ac3b0, actor, vertrix_lift_edx, entry->ebx, actor);
    port_forward(&port, entry, 0x4ac380, actor, vertrix_lift_edx, entry->ebx, actor);
    port_forward(&port, entry, 0x4ac810, actor, vertrix_lift_edx, entry->ebx, actor);
    port_set32(&port, actor, 0x64, 1 - port_u32(&port, actor, 0x64));
    result = port_forward(&port, entry, 0x4826c0, 0x598d30, 0xd, entry->ebx, actor);
    port_set8(&port, actor, 0x52, result);
    result =
        port_forward(&port, entry, 0x43f420, (uint32_t)(int32_t)(int8_t)port_u8(&port, actor, 0x64),
                     port_u8(&port, actor, 0x58), entry->ebx, actor);
    port_forward(&port, entry, 0x4ac950, actor, result, entry->ebx, actor);
    result = port_forward(&port, entry, 0x4826c0, 0x598d30, 0xb, entry->ebx, actor) - 5;
    port_set16(&port, actor, 0xc, result);
    return port_return(&port, result, entry->edx);
}

/* Original 0x45c060: 0x4ac1f0 first; when due and 0x4ad750 gives 0, 0x4ac940 and, with a sound
 * (+0x70, not -1), 0x482a60 plays its byte on the player's (0x4f8190, 0x533164) channel at the
 * volume 0x532b9c; 0x4ac8a0 either way. */
uint32_t vertrix_port_actor_play_sound_45c060(PORT_SIGNATURE)
{
    Port port;
    uint32_t actor = entry->eax;
    uint32_t ebx = entry->ebx;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    port_forward(&port, entry, 0x4ac1f0, actor, entry->edx, ebx, actor);
    port_forward(&port, entry, 0x4ac500, actor, vertrix_lift_edx, ebx, actor);
    if (port_forward(&port, entry, 0x4ac520, actor, vertrix_lift_edx, ebx, actor) == 1)
    {
        result = port_forward(&port, entry, 0x4ac540, actor, vertrix_lift_edx, ebx, actor);
        port_forward(&port, entry, 0x4ac5b0, actor, result, ebx, actor);
        if (port_forward(&port, entry, 0x4ad750, actor, vertrix_lift_edx, ebx, actor) == 0)
        {
            port_forward(&port, entry, 0x4ac940, actor, vertrix_lift_edx, ebx, actor);
            if (port_u32(&port, actor, 0x70) != 0xffffffffu)
            {
                ebx = port_u32(&port, 0, 0x532b9c);
                port_forward(&port, entry, 0x482a60, port_u8(&port, actor, 0x70),
                             port_u32(&port, port_u32(&port, 0, 0x4f8190) * 4, 0x533164), ebx,
                             actor);
            }
        }
    }
    result = port_forward(&port, entry, 0x4ac8a0, actor, vertrix_lift_edx, ebx, actor);
    return port_return(&port, result, entry->edx);
}
