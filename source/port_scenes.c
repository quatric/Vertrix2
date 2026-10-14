#include "port_scenes.h"

/* Scene change sequences, choice grid, piece slot and computer player row helpers. */

/* A call handing the callee esi, edi and ebp as given and `count` stack dwords. */
static uint32_t call_frame(Port *port, uint32_t target, uint32_t eax, uint32_t edx, uint32_t ebx,
                           uint32_t ecx, uint32_t esi, uint32_t edi, uint32_t ebp,
                           const uint32_t *stack, unsigned count)
{
    uint32_t result;
    vertrix_lift_in_esi = esi;
    vertrix_lift_in_edi = edi;
    vertrix_lift_in_ebp = ebp;
    result = lift_call_arguments(&port->env, target, eax, edx, ebx, ecx, stack, count);
    vertrix_lift_in_esi = vertrix_lift_in_edi = vertrix_lift_in_ebp = 0;
    return result;
}

/* The guard record (0x4ec1ec, `guard`) of a frame routine at ebp -0x24. */
static void guard_record(Port *port, uint32_t ebp, uint32_t guard)
{
    port_set32(port, ebp, -0x24u, port->env.chain);
    port_set32(port, ebp, -0x20u, 0x4ec1ec);
    port_set32(port, ebp, -0x1cu, guard);
    port_set32(port, ebp, -0x18u, 0);
}

/* What a call of a sequence takes in eax: the scene, the answer before, or `eax`. */
enum
{
    TAKE_SCENE,
    TAKE_LAST,
    TAKE_VALUE
};

/* What it takes in edx: the edx left before, or `edx`. */
enum
{
    EDX_LEFT,
    EDX_VALUE
};

typedef struct
{
    uint32_t target;
    uint8_t take;
    uint32_t eax;
    uint8_t edx_kind;
    uint32_t edx;
} Call;

/* The calls of a sequence on the scene, with ebx, ecx, esi, edi and ebp as given; the last
 * answer. */
static uint32_t run_calls(Port *port, const Call *list, unsigned count, uint32_t scene,
                          uint32_t edx, uint32_t ebx, uint32_t ecx, uint32_t esi, uint32_t edi,
                          uint32_t ebp)
{
    uint32_t result = scene;
    unsigned k;
    for (k = 0; k < count; k++)
    {
        uint32_t eax = list[k].take == TAKE_SCENE  ? scene
                       : list[k].take == TAKE_LAST ? result
                                                   : list[k].eax;
        uint32_t value = k == 0 && list[k].edx_kind == EDX_LEFT ? edx
                         : list[k].edx_kind == EDX_LEFT         ? vertrix_lift_edx
                                                                : list[k].edx;
        result = call_frame(port, list[k].target, eax, value, ebx, ecx, esi, edi, ebp, NULL, 0);
    }
    return result;
}

/* A sequence on the scene eax under the guard record `guard`; eax the chain it restores. */
static uint32_t guarded_sequence(PORT_SIGNATURE, uint32_t guard, const Call *list, unsigned count)
{
    enum
    {
        BELOW = 0x28
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    guard_record(&port, ebp, guard);
    run_calls(&port, list, count, entry->eax, 0x4ec1ec, guard, entry->eax, 0, entry->edi, ebp);
    return port_return(&port, port_u32(&port, ebp, -0x24u), entry->edx);
}

/* Original 0x41efe0: under the guard 0x5140fc, the scene left (0x41ab90, 0x41ac20, 0x41a9e0,
 * 0x4719e0, 0x45f9f0, 0x45e8f0, 0x45e910, 0x477ed0 on 0x5588f8 with 0, 0x4766b0 on 0x54d640),
 * the next scene 0x421f10 (0x418840) and 0x41d5b0. */
uint32_t vertrix_port_scene_leave_41efe0(PORT_SIGNATURE)
{
    static const Call list[] = {{0x41ab90, TAKE_SCENE, 0, EDX_LEFT, 0},
                                {0x41ac20, TAKE_SCENE, 0, EDX_LEFT, 0},
                                {0x41a9e0, TAKE_SCENE, 0, EDX_LEFT, 0},
                                {0x4719e0, TAKE_LAST, 0, EDX_LEFT, 0},
                                {0x45f9f0, TAKE_LAST, 0, EDX_LEFT, 0},
                                {0x45e8f0, TAKE_LAST, 0, EDX_LEFT, 0},
                                {0x45e910, TAKE_LAST, 0, EDX_LEFT, 0},
                                {0x477ed0, TAKE_VALUE, 0x5588f8, EDX_VALUE, 0},
                                {0x4766b0, TAKE_VALUE, 0x54d640, EDX_LEFT, 0},
                                {0x418840, TAKE_SCENE, 0, EDX_VALUE, 0x421f10},
                                {0x41d5b0, TAKE_SCENE, 0, EDX_LEFT, 0}};
    return guarded_sequence(calls, services, globals, entry, 0x5140fc, list, 11);
}

/* The longer leave of 0x41f460 and 0x41f910: 0x41ab90, 0x41abe0, 0x41ac20, 0x41ac40, 0x41ac70,
 * 0x41a9e0 with 0x421f10, 0x471a90, 0x4719e0, 0x45f9f0, 0x45ea80 and 0x418840 with the edx left. */
#define LONG_LEAVE                                                                                 \
    {0x41ab90, TAKE_SCENE, 0, EDX_LEFT, 0}, {0x41abe0, TAKE_SCENE, 0, EDX_LEFT, 0},                \
        {0x41ac20, TAKE_SCENE, 0, EDX_LEFT, 0}, {0x41ac40, TAKE_SCENE, 0, EDX_LEFT, 0},            \
        {0x41ac70, TAKE_SCENE, 0, EDX_LEFT, 0}, {0x41a9e0, TAKE_SCENE, 0, EDX_VALUE, 0x421f10},    \
        {0x471a90, TAKE_LAST, 0, EDX_LEFT, 0}, {0x4719e0, TAKE_LAST, 0, EDX_LEFT, 0},              \
        {0x45f9f0, TAKE_LAST, 0, EDX_LEFT, 0}, {0x45ea80, TAKE_LAST, 0, EDX_LEFT, 0},              \
        {0x418840, TAKE_SCENE, 0, EDX_LEFT, 0}

/* Original 0x41f460: under the guard 0x51410c, then 0x418820 with 0x41c740. */
uint32_t vertrix_port_scene_leave_41f460(PORT_SIGNATURE)
{
    static const Call list[] = {LONG_LEAVE, {0x418820, TAKE_SCENE, 0, EDX_VALUE, 0x41c740}};
    return guarded_sequence(calls, services, globals, entry, 0x51410c, list, 12);
}

/* Original 0x41f910: under the guard 0x51411c, then 0x41d5b0. */
uint32_t vertrix_port_scene_leave_41f910(PORT_SIGNATURE)
{
    static const Call list[] = {LONG_LEAVE, {0x41d5b0, TAKE_SCENE, 0, EDX_LEFT, 0}};
    return guarded_sequence(calls, services, globals, entry, 0x51411c, list, 12);
}

/* Original 0x421e80: under the guard 0x5141e8: 0x41ab90, 0x41ac20, 0x41a9e0 with 0x421f10,
 * 0x45f9f0, 0x4719e0, 0x45e8f0, 0x45e910, 0x418840 and 0x418820 with 0x41c6d0. */
uint32_t vertrix_port_scene_leave_421e80(PORT_SIGNATURE)
{
    static const Call list[] = {
        {0x41ab90, TAKE_SCENE, 0, EDX_LEFT, 0},         {0x41ac20, TAKE_SCENE, 0, EDX_LEFT, 0},
        {0x41a9e0, TAKE_SCENE, 0, EDX_VALUE, 0x421f10}, {0x45f9f0, TAKE_LAST, 0, EDX_LEFT, 0},
        {0x4719e0, TAKE_LAST, 0, EDX_LEFT, 0},          {0x45e8f0, TAKE_LAST, 0, EDX_LEFT, 0},
        {0x45e910, TAKE_LAST, 0, EDX_LEFT, 0},          {0x418840, TAKE_SCENE, 0, EDX_LEFT, 0},
        {0x418820, TAKE_SCENE, 0, EDX_VALUE, 0x41c6d0}};
    return guarded_sequence(calls, services, globals, entry, 0x5141e8, list, 9);
}

/* Original 0x425a50: the picture 0x558c80 shown by 0x47ce10 (on the screen's +0x268 of 0x544070,
 * at 0, 0, its +4 and +8 as stack arguments) and released (0x4719f0), then the scene left
 * (0x41a9e0, 0x4719e0, 0x45f9f0, 0x45e670 with 0 and with 1, 0x45ea80, 0x45e8f0, 0x45e910),
 * 0x418840 and 0x418820 with 0x41c6d0. */
uint32_t vertrix_port_scene_leave_picture_425a50(PORT_SIGNATURE)
{
    static const Call list[] = {{0x41a9e0, TAKE_SCENE, 0, EDX_LEFT, 0},
                                {0x4719e0, TAKE_LAST, 0, EDX_LEFT, 0},
                                {0x45f9f0, TAKE_LAST, 0, EDX_LEFT, 0},
                                {0x45e670, TAKE_VALUE, 0, EDX_LEFT, 0},
                                {0x45e670, TAKE_VALUE, 1, EDX_VALUE, 0x421f10},
                                {0x45ea80, TAKE_LAST, 0, EDX_LEFT, 0},
                                {0x45e8f0, TAKE_LAST, 0, EDX_LEFT, 0},
                                {0x45e910, TAKE_LAST, 0, EDX_LEFT, 0},
                                {0x418840, TAKE_SCENE, 0, EDX_LEFT, 0},
                                {0x418820, TAKE_SCENE, 0, EDX_VALUE, 0x41c6d0}};
    Port port;
    uint32_t scene = entry->eax;
    uint32_t picture;
    uint32_t arguments[4];
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    picture = port_u32(&port, 0, 0x558c80);
    arguments[0] = 0;
    arguments[1] = 0;
    arguments[2] = port_u32(&port, picture, 4);
    arguments[3] = port_u32(&port, picture, 8);
    call_frame(&port, 0x47ce10, picture, port_u32(&port, port_u32(&port, 0, 0x544070), 0x268), 0, 0,
               scene, entry->edi, entry->ebp, arguments, 4);
    call_frame(&port, 0x4719f0, port_u32(&port, 0, 0x558c80), vertrix_lift_edx, 0, 0, scene,
               entry->edi, entry->ebp, NULL, 0);
    result =
        run_calls(&port, list, 10, scene, vertrix_lift_edx, 0, 0, scene, entry->edi, entry->ebp);
    return port_return(&port, result, entry->edx);
}

/* Original 0x41d5b0: under the guard 0x514088, 0x418820 with 0x41b5e0; outside a demo
 * (0x532a8c 0), when the score 0x532aa4 makes the high score table (0x4177b0), its place to
 * 0x532ab4 and 0x418820 with 0x41acc0. eax the chain it restores. */
uint32_t vertrix_port_gate_dispatch_call_full_41d5b0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x28
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t scene = entry->eax;
    uint32_t place;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    guard_record(&port, ebp, 0x514088);
    call_frame(&port, 0x418820, scene, 0x41b5e0, 0x514088, scene, 0, entry->edi, ebp, NULL, 0);
    if (port_u32(&port, 0, 0x532a8c) == 0)
    {
        place = call_frame(&port, 0x4177b0, port_u32(&port, 0, 0x532aa4), vertrix_lift_edx,
                           0x514088, scene, 0, entry->edi, ebp, NULL, 0) &
                0xff;
        if (place != 0xff)
        {
            port_set32(&port, 0, 0x532ab4, (uint32_t)(int32_t)(int8_t)place);
            call_frame(&port, 0x418820, scene, 0x41acc0, 0x514088, scene, 0, entry->edi, ebp, NULL,
                       0);
        }
    }
    return port_return(&port, port_u32(&port, ebp, -0x24u), entry->edx);
}

/* Original 0x421de0: once (0x5405a9) 0x4b7cd0 with 1 (0x5405a9 the dl it leaves); then 0x4b7d10,
 * 0x41dec0, 0x419490, 0x471a70, 0x41aaf0, the music 0x5b9c50 stopped (0x486d00), 0x4719f0 on
 * 0x558c7c, 0x486da0 and 0x487020 with 1; when 0x476480 holds for 0x54d640, 0x4762e0 with 1,
 * 0x5405a9 0 and the next scene 0x421e80 (0x418840). */
uint32_t vertrix_port_scene_title_end_421de0(PORT_SIGNATURE)
{
    Port port;
    uint32_t scene = entry->eax;
    uint32_t result = entry->eax;
    uint32_t edx = entry->edx;
    port_open(&port, calls, services, globals, entry);
    if (port_u8(&port, 0, 0x5405a9) == 0)
    {
        result = port_forward(&port, entry, 0x4b7cd0, scene, (entry->edx & 0xffffff00u) | 1,
                              entry->ebx, scene);
        port_set8(&port, 0, 0x5405a9, vertrix_lift_edx);
        edx = vertrix_lift_edx;
    }
    port_forward(&port, entry, 0x4b7d10, result, edx, entry->ebx, scene);
    port_forward(&port, entry, 0x41dec0, scene, vertrix_lift_edx, entry->ebx, scene);
    result = port_forward(&port, entry, 0x419490, scene, vertrix_lift_edx, entry->ebx, scene);
    port_forward(&port, entry, 0x471a70, result, vertrix_lift_edx, entry->ebx, scene);
    port_forward(&port, entry, 0x41aaf0, scene, vertrix_lift_edx, entry->ebx, scene);
    port_forward(&port, entry, 0x486d00, 0x5b9c50, vertrix_lift_edx, entry->ebx, scene);
    port_forward(&port, entry, 0x4719f0, port_u32(&port, 0, 0x558c7c), vertrix_lift_edx, entry->ebx,
                 scene);
    port_forward(&port, entry, 0x486da0, 0x5b9c50, vertrix_lift_edx, entry->ebx, scene);
    port_forward(&port, entry, 0x487020, 0x5b9c50, 1, entry->ebx, scene);
    result = port_forward(&port, entry, 0x476480, 0x54d640, vertrix_lift_edx, entry->ebx, scene);
    if (result != 0)
    {
        port_forward(&port, entry, 0x4762e0, 0x54d640, 1, entry->ebx, scene);
        port_set8(&port, 0, 0x5405a9, 0);
        result = port_forward(&port, entry, 0x418840, scene, 0x421e80, entry->ebx, scene);
    }
    return port_return(&port, result, entry->edx);
}

/* Original 0x41e280: 0x45e630 on eax with 8 and 0x534620; the two names of the entry edx (0x534620
 * and 0x534670) formatted by 0x45f540 with 0x4fc7b8 into the frame and looked up by 0x423ea0; when
 * found, 0x45f250 with eax and 8 and 0x478d80. */
uint32_t vertrix_port_scene_load_named_41e280(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x218
    };
    Port port;
    uint8_t stack[BELOW + 8];
    uint32_t ebp = entry->esp - 4;
    uint32_t scene = entry->eax;
    uint32_t offset = entry->edx * 4;
    uint32_t first = ebp - 0x214;
    uint32_t second = ebp - 0x110;
    uint32_t found;
    uint32_t result;
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    call_frame(&port, 0x45e630, scene, 8, 0x534620, entry->edx, scene, entry->edi, ebp, NULL, 0);
    call_frame(&port, 0x45f540, first, 0x4fc7b8, port_u32(&port, offset, 0x534620), offset, scene,
               entry->edi, ebp, NULL, 0);
    call_frame(&port, 0x45f540, second, 0x4fc7b8, port_u32(&port, offset, 0x534670),
               offset + 0x534670, scene, entry->edi, ebp, NULL, 0);
    found = call_frame(&port, 0x423ea0, first, second, port_u32(&port, offset, 0x534670),
                       offset + 0x534670, scene, entry->edi, ebp, NULL, 0);
    if (found == 0)
    {
        return port_return(&port, 0, vertrix_lift_edx);
    }
    call_frame(&port, 0x45f250, found, scene, 8, found, scene, entry->edi, ebp, NULL, 0);
    result = call_frame(&port, 0x478d80, found, vertrix_lift_edx, 8, found, scene, entry->edi, ebp,
                        NULL, 0);
    return port_return(&port, result, vertrix_lift_edx);
}

/* Original 0x4261b0: the reach of the row (stack argument) from the column ecx of the board edx
 * (13 cells a column) into the five bytes ebx: all 1 (0x4eb5c0), then cleared from the first
 * filled cell (not -1) on each side outward. */
uint32_t vertrix_port_ai_row_reach_4261b0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x10
    };
    Port port;
    uint8_t stack[BELOW + 8 + 4];
    uint32_t ebp = entry->esp - 4;
    uint32_t board = entry->edx;
    uint32_t out = entry->ebx;
    uint32_t row;
    int32_t column;
    uint32_t edx;
    port_open_arguments(&port, stack, calls, services, globals, entry, BELOW, 1);
    port_set32(&port, ebp, -0xcu, entry->ecx);
    row = port_u32(&port, entry->esp, 4);
    call_frame(&port, 0x4eb5c0, out, 1, 5, row, board, out, ebp, NULL, 0);
    edx = vertrix_lift_edx;
    column = (int32_t)port_u32(&port, ebp, -0xcu) - 1;
    while (column >= 0)
    {
        if ((int32_t)row < 0xa)
        {
            edx = (uint32_t)column * 0xd + board;
            if (port_u8(&port, row + edx, 0) != 0xff)
            {
                edx = (uint32_t)column + out;
                while (column >= 0)
                {
                    column--;
                    port_set8(&port, edx, 0, 0);
                    edx--;
                }
                break;
            }
        }
        column--;
    }
    column = (int32_t)port_u32(&port, ebp, -0xcu) + 1;
    while (column < 5)
    {
        if ((int32_t)row < 0xa)
        {
            edx = (uint32_t)column * 0xd + board;
            if (port_u8(&port, row + edx, 0) != 0xff)
            {
                edx = (uint32_t)column + out;
                while (column < 5)
                {
                    column++;
                    port_set8(&port, edx, 0, 0);
                    edx++;
                }
                break;
            }
        }
        column++;
    }
    return port_return(&port, (uint32_t)column, edx);
}

/* Original 0x429880: the piece actor built (0x4abd70) with the table 0x514624, byte +0x274 -1,
 * +0x278 1, and its seven rows of four slots (+0x15c and +0x1cc dwords, +0x23c and +0x258 bytes)
 * cleared. */
uint32_t vertrix_port_piece_actor_construct_slots_429880(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x1c
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t actor;
    uint32_t row;
    uint32_t slot;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, -0x18u, entry->eax);
    actor = call_frame(&port, 0x4abd70, entry->eax, entry->edx, entry->ebx, entry->ecx, entry->esi,
                       entry->edi, ebp, NULL, 0);
    port_set32(&port, actor, 0x158, 0x514624);
    port_set8(&port, actor, 0x274, 0xff);
    port_set32(&port, ebp, -0x18u, actor);
    port_set32(&port, actor, 0x278, 1);
    port_set32(&port, ebp, -0x14u, actor);
    for (row = 0; row < 7; row++)
    {
        uint32_t base = port_u32(&port, ebp, -0x14u);
        for (slot = 0; slot < 4; slot++)
        {
            uint32_t at = port_u32(&port, ebp, -0x18u) + row * 0x10 + slot * 4;
            port_set32(&port, at, 0x15c, 0);
            port_set32(&port, at, 0x1cc, 0);
            port_set8(&port, base + slot + 1, 0x23b, 0);
            port_set8(&port, base + slot + 1, 0x257, 0);
        }
        port_set32(&port, ebp, -0x14u, base + 4);
    }
    return port_return(&port, port_u32(&port, ebp, -0x18u), entry->edx);
}

/* Original 0x429d50: each of the 28 choices of the grid eax with a block (+0x15c): chosen (+0x1cc
 * 1) shown (+0x4e 100, +0x93 0, +0x15c 0) or not (+0x4e 0, +0x93 1, +0x15c 1), +0x15d 0, and the
 * handler 0x456ca0. */
uint32_t vertrix_port_choice_grid_apply_429d50(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x20
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t grid = entry->eax;
    uint32_t row;
    uint32_t result = entry->eax;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, -0x18u, grid);
    port_set32(&port, ebp, -0x1cu, grid + 0x10);
    for (row = 0; row < 7; row++)
    {
        uint32_t end = port_u32(&port, ebp, -0x1cu);
        uint32_t at;
        for (at = port_u32(&port, ebp, -0x18u) + row * 0x10; at != end; at += 4)
        {
            uint32_t block = port_u32(&port, at, 0x15c);
            result = block;
            if (block == 0)
            {
                continue;
            }
            if (port_u32(&port, at, 0x1cc) == 1)
            {
                port_set8(&port, block, 0x4e, 0x64);
                port_set8(&port, block, 0x93, 0);
                port_set8(&port, block, 0x15c, 0);
            }
            else
            {
                port_set8(&port, block, 0x4e, 0);
                port_set8(&port, block, 0x93, 1);
                port_set8(&port, block, 0x15c, 1);
            }
            port_set8(&port, block, 0x15d, 0);
            result = call_frame(&port, 0x4ac8f0, block, 0x456ca0, end, at, row, 0, ebp, NULL, 0);
        }
        port_set32(&port, ebp, -0x1cu, end + 0x10);
    }
    return port_return(&port, result, entry->edx);
}

/* Original 0x429df0: the 28 choices of the grid eax take the values edx (+0x1cc), each block
 * (+0x15c) shown (+0x15c 0) for 1 and hidden (1) otherwise. eax and edx past the last row. */
uint32_t vertrix_port_choice_grid_load_values_429df0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x20
    };
    Port port;
    uint32_t local = entry->esp - BELOW;
    uint32_t row;
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, local, 0, entry->edx);
    port_set32(&port, local, 4, entry->edx + 0x10);
    port_set32(&port, local, 8, entry->eax);
    for (row = 0; row < 7; row++)
    {
        uint32_t end = port_u32(&port, local, 4);
        edx = row * 0x10 + port_u32(&port, local, 0);
        eax = port_u32(&port, local, 8);
        for (; edx != end; edx += 4, eax += 4)
        {
            uint32_t value = port_u32(&port, edx, 0);
            uint32_t block;
            port_set32(&port, eax, 0x1cc, value);
            block = port_u32(&port, eax, 0x15c);
            if (block != 0)
            {
                port_set8(&port, block, 0x15c, value == 1 ? 0 : 1);
            }
        }
        port_set32(&port, local, 4, end + 0x10);
        port_set32(&port, local, 8, port_u32(&port, local, 8) + 0x10);
    }
    return port_return(&port, eax, edx);
}

/* Original 0x42aa20: the state edx of the three blocks (+0x15c) of eax: for 1 (from 0, +0x184 1)
 * their words +0x48 0; for another from 1 (+0x184 0) their +0x48 20 when +0x17c is 1, else 0.
 * +0x180 the state. */
uint32_t vertrix_port_blocks_set_state_42aa20(PORT_SIGNATURE)
{
    Port port;
    uint32_t object = entry->eax;
    uint32_t state = entry->edx;
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    port_open(&port, calls, services, globals, entry);
    if (state == 1)
    {
        if (port_u32(&port, object, 0x180) == 0)
        {
            port_set32(&port, object, 0x184, state);
            for (eax = object; eax != object + 0xc; eax += 4)
            {
                edx = port_u32(&port, eax, 0x15c);
                if (edx != 0)
                {
                    port_set16(&port, edx, 0x48, 0);
                }
            }
        }
    }
    else if (port_u32(&port, object, 0x180) == 1)
    {
        port_set32(&port, object, 0x184, 0);
        for (eax = object; eax != object + 0xc; eax += 4)
        {
            uint32_t block = port_u32(&port, eax, 0x15c);
            if (block != 0)
            {
                edx = port_u32(&port, object, 0x17c);
                port_set16(&port, block, 0x48, edx == 1 ? 0x14 : 0);
            }
        }
    }
    port_set32(&port, object, 0x180, state);
    return port_return(&port, eax, edx);
}
