#include "port_actor.h"

enum
{
    ACTOR_FRAME_INDEX = 0xb8,
    ACTOR_ELAPSED = 0xbc,
    ACTOR_TIME_SCALE = 0xc0,
    STEP_VALUE = 0x58,
    STEP_GOAL = 0x5c,
    STEP_SPEED = 0x60,
    SINGLE_ONE = 0x3f800000,
    UNSIGNED_TO_SINGLE = 0x4d74a6,
    SIGNED_TO_SINGLE = 0x4d74d1,
    SINGLE_DIVIDE = 0x4d81fe,
    SINGLE_MULTIPLY = 0x4d8177,
    SINGLE_TO_INT32 = 0x4d67a8,
    STEP_TOWARD = 0x4aca00,
    ACTOR_NEXT = 0x108,
    ACTOR_RESOURCE = 0xb0,
    ACTOR_IMAGE = 0xb4,
    ACTOR_MARKER = 0x120,
    ACTOR_BUSY = 0x124,
    ACTOR_VALUE_INDEX = 0x146,
    ACTOR_IDLE_RECORD = 0x158,
    IDLE_ROUTINE = 0x08,
    ACTOR_VALUES = 0x5bb714,
    ACTOR_HOOK = 0x154,
    MARKER_RESET = 0x5bb710,
    ACTOR_RESET_MARKER = 0x4adf70,
    ACTOR_CHAIN_UPDATE = 0x4ade20,
    ACTOR_UPDATE = 0x4ad870,
    ACTOR_GATE_ARGUMENT = 0x144,
    PAINT_ARGUMENT = 0x5bc010,
    ACTOR_GATE = 0x4ae3e0,
    ACTOR_PAINT = 0x4af560,
    FRAME_TIME = 0x5bd834,
    ACTOR_LOOKUP_IMAGE = 0x4ac8a0,
    ACTOR_CHAIN_PAINT = 0x4af8c0,
    ACTOR_CHAIN_WALK = 0x4ade60,
    ACTOR_IDLE_DEFAULT = 0x517af4,
    ACTOR_TYPE_INFO = 0x517b10,
    FREE_MEMORY = 0x4ca050,
    FREE_MEMORY_JUMP = 0x4ca040,
    FINALIZE_RECORD = 0x4ccb9f,
    GUARD_HANDLER = 0x4ec1ec,
    GUARD_TABLE = 0x517ad0,
    DESTROY_FREE = 2,
    DESTROY_FINALIZE = 4,
    ACTOR_VALUE = 0x4adfb0,
    ACTOR_SPOT_X = 0x126,
    ACTOR_SPOT_Y = 0x128,
    ACTOR_SPOT_WIDTH = 0x12c,
    ACTOR_SPOT_HEIGHT = 0x130,
    ACTOR_SPOT_VALUE = 0x138,
    ACTOR_SPOT_MIRROR = 0x140,
    DRAW_SPOT = 0x47ce10,
    SCREEN = 0x544070,
    SCREEN_SURFACE = 0x274,
    SCREEN_SURFACE_ARGUMENT = 0x278
};

uint32_t vertrix_port_actor_advance_elapsed(PORT_SIGNATURE)
{
    Port port;
    uint32_t actor = entry->eax;
    uint32_t time;
    port_open(&port, calls, services, globals, entry);
    time = port_u32(&port, 0, FRAME_TIME);
    port_set32(&port, actor, ACTOR_ELAPSED, port_u32(&port, actor, ACTOR_ELAPSED) + time);
    return port_return(&port, actor, entry->edx);
}

uint32_t vertrix_port_actor_chain_walk(PORT_SIGNATURE)
{
    Port port;
    uint32_t actor = entry->eax;
    uint32_t argument = entry->edx;
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    port_open(&port, calls, services, globals, entry);
    while (actor != 0)
    {
        port_call(&port, ACTOR_LOOKUP_IMAGE, actor, edx, argument, actor);
        eax = port_call(&port, ACTOR_CHAIN_PAINT, actor, argument, argument, actor);
        edx = vertrix_lift_edx;
        actor = port_u32(&port, actor, ACTOR_NEXT);
    }
    return port_return(&port, eax, edx);
}

uint32_t vertrix_port_actor_chain_walk_call(PORT_SIGNATURE)
{
    Port port;
    uint32_t eax;
    port_open(&port, calls, services, globals, entry);
    eax = port_call(&port, ACTOR_CHAIN_WALK, entry->eax, entry->edx, entry->ebx, entry->ecx);
    return port_return(&port, eax, vertrix_lift_edx);
}

uint32_t vertrix_port_actor_chain_paint(PORT_SIGNATURE)
{
    Port port;
    uint32_t actor = entry->eax;
    uint32_t eax;
    port_open(&port, calls, services, globals, entry);
    port_set32(&port, 0, PAINT_ARGUMENT, entry->edx);
    eax = port_call(&port, ACTOR_GATE, actor, port_u32(&port, actor, ACTOR_GATE_ARGUMENT),
                    entry->ebx, actor);
    if (eax != 0)
    {
        eax = port_call(&port, ACTOR_PAINT, actor, vertrix_lift_edx, entry->ebx, actor);
    }
    return port_return(&port, eax, vertrix_lift_edx);
}

uint32_t vertrix_port_actor_set_frame_index(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    port_set32(&port, entry->eax, ACTOR_FRAME_INDEX, entry->edx);
    return port_return(&port, entry->eax, entry->edx);
}

uint32_t vertrix_port_actor_clear_elapsed(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    port_set32(&port, entry->eax, ACTOR_ELAPSED, 0);
    return port_return(&port, entry->eax, entry->edx);
}

uint32_t vertrix_port_actor_scaled_time(PORT_SIGNATURE)
{
    Port port;
    uint32_t actor = entry->eax;
    uint32_t scale;
    uint32_t elapsed;
    uint32_t quotient;
    port_open(&port, calls, services, globals, entry);
    scale = port_call(&port, UNSIGNED_TO_SINGLE, port_u32(&port, actor, ACTOR_TIME_SCALE),
                      entry->edx, entry->ebx, actor);
    if (scale == 0)
    {
        scale = SINGLE_ONE;
    }
    elapsed = port_call(&port, UNSIGNED_TO_SINGLE, port_u32(&port, actor, ACTOR_ELAPSED), scale,
                        entry->ebx, actor);
    quotient = port_call(&port, SINGLE_DIVIDE, elapsed, vertrix_lift_edx, entry->ebx, actor);
    return port_return(&port, quotient, entry->edx);
}

uint32_t vertrix_port_step_toward(PORT_SIGNATURE)
{
    Port port;
    int32_t value = (int32_t)entry->ebx;
    int32_t goal = (int32_t)entry->ecx;
    uint32_t speed;
    uint32_t step;
    port_open(&port, calls, services, globals, entry);
    if (value == goal)
    {
        return port_return(&port, (uint32_t)value, entry->edx);
    }
    speed =
        port_call(&port, SIGNED_TO_SINGLE, entry->arguments[0], entry->edx, entry->ebx, entry->ecx);
    step = port_call(&port, SINGLE_MULTIPLY, vertrix_lift_edx, speed, entry->ebx, entry->ecx);
    step = port_call(&port, SINGLE_TO_INT32, step, vertrix_lift_edx, entry->ebx, entry->ecx);
    if (value > goal)
    {
        value -= (int32_t)step;
        value = value < goal ? goal : value;
    }
    else
    {
        value += (int32_t)step;
        value = value > goal ? goal : value;
    }
    return port_return(&port, (uint32_t)value, vertrix_lift_edx);
}

uint32_t vertrix_port_object_step_field(PORT_SIGNATURE)
{
    Port port;
    uint32_t object = entry->eax;
    uint32_t speed;
    uint32_t value;
    uint32_t goal;
    uint32_t edx;
    port_open(&port, calls, services, globals, entry);
    speed = port_u32(&port, object, STEP_SPEED);
    value = port_u32(&port, object, STEP_VALUE);
    goal = port_u32(&port, object, STEP_GOAL);
    value = port_call_stack(&port, STEP_TOWARD, object, entry->edx, value, goal, &speed, 1);
    edx = vertrix_lift_edx;
    goal = port_u32(&port, object, STEP_GOAL);
    port_set32(&port, object, STEP_VALUE, value);
    return port_return(&port, value != goal, edx);
}

uint32_t vertrix_port_actor_initialize(PORT_SIGNATURE)
{
    Port port;
    uint32_t actor = entry->eax;
    port_open(&port, calls, services, globals, entry);
    port_set16(&port, actor, 0x08, entry->edx);
    port_set16(&port, actor, 0x0a, entry->ebx);
    port_set16(&port, actor, 0x0c, entry->ecx);
    port_set16(&port, actor, 0x0e, entry->edx);
    port_set16(&port, actor, 0x16, entry->ebx);
    port_set16(&port, actor, 0x1e, entry->ecx);
    port_set32(&port, actor, ACTOR_RESOURCE, entry->arguments[0]);
    port_set32(&port, actor, ACTOR_FRAME_INDEX, entry->arguments[1]);
    port_set32(&port, actor, ACTOR_IMAGE, entry->arguments[2]);
    port_set32(&port, actor, ACTOR_HOOK, entry->arguments[3]);
    return port_return(&port, actor, entry->arguments[3]);
}

uint32_t vertrix_port_actor_reset_marker(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    if (port_u32(&port, 0, MARKER_RESET) == 1)
    {
        port_set32(&port, entry->eax, ACTOR_MARKER, 0);
    }
    return port_return(&port, entry->eax, entry->edx);
}

uint32_t vertrix_port_actor_chain_update_call(PORT_SIGNATURE)
{
    Port port;
    uint32_t eax;
    port_open(&port, calls, services, globals, entry);
    port_call(&port, ACTOR_RESET_MARKER, entry->eax, entry->eax, entry->ebx, entry->ecx);
    eax = vertrix_lift_edx;
    eax = port_call(&port, ACTOR_CHAIN_UPDATE, eax, eax, entry->ebx, entry->ecx);
    return port_return(&port, eax, entry->edx);
}

uint32_t vertrix_port_actor_chain_update(PORT_SIGNATURE)
{
    Port port;
    uint32_t first = entry->eax;
    uint32_t actor = entry->eax;
    uint32_t eax = entry->eax;
    port_open(&port, calls, services, globals, entry);
    while (actor != 0)
    {
        uint32_t hook;
        eax = port_call(&port, ACTOR_UPDATE, actor, actor, entry->ebx, first);
        hook = port_u32(&port, first, ACTOR_HOOK);
        if (hook != 0)
        {
            eax = port_call(&port, hook, vertrix_lift_edx, vertrix_lift_edx, entry->ebx, first);
        }
        actor = port_u32(&port, vertrix_lift_edx, ACTOR_NEXT);
    }
    return port_return(&port, eax, entry->edx);
}

uint32_t vertrix_port_actor_value(PORT_SIGNATURE)
{
    Port port;
    uint32_t actor = entry->eax;
    port_open(&port, calls, services, globals, entry);
    if (port_u16(&port, actor, ACTOR_VALUE_INDEX + 2) == 0xffff)
    {
        return port_return(&port, port_u32(&port, actor, ACTOR_MARKER), entry->edx);
    }
    return port_return(
        &port,
        port_u32(&port, 0,
                 (uint32_t)(((int32_t)port_u32(&port, actor, ACTOR_VALUE_INDEX) >> 16) * 4) +
                     ACTOR_VALUES),
        entry->edx);
}

uint32_t vertrix_port_actor_idle_call(PORT_SIGNATURE)
{
    Port port;
    uint32_t actor = entry->eax;
    uint32_t record;
    uint32_t eax;
    port_open(&port, calls, services, globals, entry);
    if (port_u32(&port, actor, ACTOR_BUSY) != 0)
    {
        return port_return(&port, actor, entry->edx);
    }
    record = port_u32(&port, actor, ACTOR_IDLE_RECORD);
    eax = port_call(&port, port_u32(&port, record, IDLE_ROUTINE), actor, entry->edx, entry->ebx,
                    record);
    return port_return(&port, eax, vertrix_lift_edx);
}

uint32_t vertrix_port_actor_elapsed_done(PORT_SIGNATURE)
{
    Port port;
    uint32_t elapsed;
    port_open(&port, calls, services, globals, entry);
    elapsed = port_u32(&port, entry->eax, ACTOR_ELAPSED);
    return port_return(&port, elapsed >= port_u32(&port, entry->eax, ACTOR_TIME_SCALE), entry->edx);
}

uint32_t vertrix_port_actor_base_destroy(PORT_SIGNATURE)
{
    Port port;
    uint32_t actor = entry->eax;
    uint32_t mode = entry->edx;
    uint32_t ebp = entry->esp - 4;
    uint32_t result;
    /* push ebp, ebx, ecx, esi, edi, then 0x24 bytes of locals. */
    port_open_frame(&port, calls, services, globals, entry, 0x38);
    if (mode & DESTROY_FINALIZE)
    {
        port_set32(&port, ebp, -0x34u, actor);
        port_set32(&port, ebp, -0x14u, 1);
        result = port_call(&port, FINALIZE_RECORD, actor, ACTOR_TYPE_INFO, entry->ebx, actor);
        port_set32(&port, ebp, -0x14u, 0);
        port_call(&port, FREE_MEMORY_JUMP, result, 0, entry->ebx, actor);
        return port_return(&port, actor, vertrix_lift_edx);
    }
    port_set32(&port, actor, ACTOR_IDLE_RECORD, ACTOR_IDLE_DEFAULT);
    /* The guard record the original links into fs:[0] for the free and unlinks after it. */
    port_set32(&port, ebp, -0x20u, port.env.chain);
    port_set32(&port, ebp, -0x1cu, GUARD_HANDLER);
    port_set32(&port, ebp, -0x18u, GUARD_TABLE);
    port_set32(&port, ebp, -0x14u, 0);
    if ((mode & DESTROY_FREE) == 0)
    {
        return port_return(&port, actor, mode);
    }
    port_call(&port, FREE_MEMORY, actor, mode, GUARD_HANDLER, actor);
    return port_return(&port, actor, vertrix_lift_edx);
}

uint32_t vertrix_port_actor_spot_draw(PORT_SIGNATURE)
{
    Port port;
    uint32_t actor = entry->eax;
    uint32_t value;
    uint32_t width;
    uint32_t height;
    uint32_t screen;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    value = port_u32(&port, actor, ACTOR_BUSY);
    if (value != 1)
    {
        return port_return(&port, value, entry->ebx);
    }
    value = port_call(&port, ACTOR_VALUE, actor, entry->ebx, entry->ebx, entry->ecx);
    if (value != 1 || value != port_u32(&port, actor, ACTOR_SPOT_VALUE))
    {
        return port_return(&port, value, vertrix_lift_edx);
    }
    width = port_u32(&port, actor, ACTOR_SPOT_WIDTH);
    if (width == 0)
    {
        return port_return(&port, value, vertrix_lift_edx);
    }
    height = port_u32(&port, actor, ACTOR_SPOT_HEIGHT);
    if (height == 0)
    {
        return port_return(&port, height, vertrix_lift_edx);
    }
    {
        uint32_t x = (uint32_t)((int32_t)port_u32(&port, actor, ACTOR_SPOT_X) >> 16);
        uint32_t y = (uint32_t)((int32_t)port_u32(&port, actor, ACTOR_SPOT_Y) >> 16);
        uint32_t stack[4] = {x, y, width, height};
        result = port_call_stack(&port, DRAW_SPOT, entry->edx, vertrix_lift_edx, x, y, stack, 4);
        if (port_u32(&port, actor, ACTOR_SPOT_MIRROR) != 1)
        {
            return port_return(&port, result, vertrix_lift_edx);
        }
        stack[2] = port_u32(&port, actor, ACTOR_SPOT_WIDTH);
        stack[3] = port_u32(&port, actor, ACTOR_SPOT_HEIGHT);
        stack[1] = (uint32_t)((int32_t)port_u32(&port, actor, ACTOR_SPOT_Y) >> 16);
        stack[0] = (uint32_t)((int32_t)port_u32(&port, actor, ACTOR_SPOT_X) >> 16);
        screen = port_u32(&port, 0, SCREEN);
        result = port_call_stack(&port, DRAW_SPOT, port_u32(&port, screen, SCREEN_SURFACE),
                                 port_u32(&port, screen, SCREEN_SURFACE_ARGUMENT), stack[0],
                                 stack[1], stack, 4);
    }
    return port_return(&port, result, vertrix_lift_edx);
}

/* The fields 0x4abd70 sets, in its order: offset, width in bytes and value. Most are cleared; the
 * idle record is 0x517af4, the scales +0x44 and +0x45 are 16 (full size), +0x8e, +0x95, +0x120,
 * +0x134, +0x138, +0x13c and +0x144 are 1, +0x94 is 2, +0x118 and +0x11c are the colours
 * 0xffffff and 0xff000000, and +0x148 is 0xffff. */
static const struct
{
    uint16_t offset;
    uint8_t size;
    uint32_t value;
} ACTOR_RESET[] = {
    {0x158, 4, 0x517af4}, {0x0, 4, 0x0},          {0x4, 4, 0x0},   {0x8, 2, 0x0},   {0xa, 2, 0x0},
    {0xc, 2, 0x0},        {0xe, 2, 0x0},          {0x16, 2, 0x0},  {0x1e, 2, 0x0},  {0x10, 2, 0x0},
    {0x18, 2, 0x0},       {0x20, 2, 0x0},         {0x14, 2, 0x0},  {0x1c, 2, 0x0},  {0x12, 2, 0x0},
    {0x1a, 2, 0x0},       {0x22, 2, 0x0},         {0x24, 2, 0x0},  {0x26, 2, 0x0},  {0x28, 2, 0x0},
    {0x2a, 2, 0x0},       {0x2c, 2, 0x0},         {0x2e, 2, 0x0},  {0x30, 2, 0x0},  {0x32, 2, 0x0},
    {0x34, 2, 0x0},       {0x36, 2, 0x0},         {0x38, 2, 0x0},  {0x3a, 2, 0x0},  {0x3c, 2, 0x0},
    {0x3e, 2, 0x0},       {0x40, 2, 0x0},         {0x42, 2, 0x0},  {0x44, 1, 0x10}, {0x45, 1, 0x10},
    {0x46, 2, 0x0},       {0x48, 2, 0x0},         {0x4a, 2, 0x0},  {0x4c, 2, 0x0},  {0x4e, 1, 0x32},
    {0x4f, 1, 0x32},      {0x50, 2, 0x0},         {0x52, 1, 0xd},  {0x53, 1, 0xd},  {0x54, 2, 0x0},
    {0x80, 4, 0x0},       {0x84, 4, 0x0},         {0x88, 4, 0x0},  {0x8c, 1, 0x0},  {0x8d, 1, 0x0},
    {0x8e, 1, 0x1},       {0x90, 1, 0x0},         {0x91, 1, 0x0},  {0x92, 1, 0x0},  {0x93, 1, 0x0},
    {0x8f, 1, 0x0},       {0x94, 1, 0x2},         {0x95, 1, 0x1},  {0x98, 4, 0x0},  {0x9c, 4, 0x0},
    {0xa0, 4, 0x0},       {0xa4, 4, 0x0},         {0xa8, 2, 0x0},  {0xaa, 2, 0x0},  {0xac, 2, 0x0},
    {0xae, 2, 0x0},       {0xb0, 4, 0x0},         {0xb4, 4, 0x0},  {0xb8, 4, 0x0},  {0xbc, 4, 0x0},
    {0xc0, 4, 0x0},       {0xc4, 4, 0x0},         {0xc8, 4, 0x0},  {0xcc, 4, 0x0},  {0xd0, 4, 0x0},
    {0xd4, 4, 0x0},       {0xd8, 4, 0x0},         {0xdc, 4, 0x0},  {0xe0, 4, 0x0},  {0xe4, 4, 0x0},
    {0xe8, 4, 0x0},       {0xec, 4, 0x0},         {0x154, 4, 0x0}, {0xf0, 4, 0x0},  {0xf4, 4, 0x0},
    {0xf8, 4, 0x0},       {0xfc, 1, 0x0},         {0xfd, 1, 0x0},  {0xfe, 2, 0x0},  {0x100, 2, 0x0},
    {0x104, 4, 0x0},      {0x108, 4, 0x0},        {0x10c, 4, 0x0}, {0x110, 1, 0x0}, {0x114, 4, 0x0},
    {0x118, 4, 0xffffff}, {0x11c, 4, 0xff000000}, {0x58, 4, 0x0},  {0x5c, 4, 0x0},  {0x60, 4, 0x0},
    {0x64, 4, 0x0},       {0x68, 4, 0x0},         {0x6c, 4, 0x0},  {0x70, 4, 0x0},  {0x74, 4, 0x0},
    {0x78, 4, 0x0},       {0x7c, 4, 0x0},         {0x120, 4, 0x1}, {0x124, 4, 0x0}, {0x138, 4, 0x1},
    {0x128, 2, 0x0},      {0x12a, 2, 0x0},        {0x12c, 4, 0x0}, {0x130, 4, 0x0}, {0x13c, 4, 0x1},
    {0x140, 4, 0x0},      {0x144, 4, 0x1},        {0x14c, 4, 0x0}, {0x134, 4, 0x1}, {0x150, 4, 0x0},
    {0x148, 2, 0xffff}};

uint32_t vertrix_port_actor_reset(PORT_SIGNATURE)
{
    Port port;
    unsigned i;
    port_open(&port, calls, services, globals, entry);
    for (i = 0; i < sizeof ACTOR_RESET / sizeof ACTOR_RESET[0]; i++)
    {
        lift_store(&port.env, entry->eax, ACTOR_RESET[i].offset, ACTOR_RESET[i].size,
                   ACTOR_RESET[i].value);
    }
    return port_return(&port, entry->eax, entry->edx);
}

uint32_t vertrix_port_actor_value_idle_call(PORT_SIGNATURE)
{
    Port port;
    uint32_t actor = entry->eax;
    uint32_t value;
    uint32_t record;
    port_open(&port, calls, services, globals, entry);
    value = port_u32(&port, actor, ACTOR_BUSY);
    if (value != 1)
    {
        return port_return(&port, value, entry->edx);
    }
    value = port_call(&port, ACTOR_VALUE, actor, entry->edx, entry->ebx, actor);
    if (value != 1)
    {
        return port_return(&port, value, vertrix_lift_edx);
    }
    record = port_u32(&port, actor, ACTOR_IDLE_RECORD);
    value = port_call(&port, port_u32(&port, record, IDLE_ROUTINE), actor, vertrix_lift_edx, record,
                      actor);
    return port_return(&port, value, vertrix_lift_edx);
}
