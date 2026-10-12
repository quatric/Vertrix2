#include "port_actor.h"

enum
{
    ACTOR_FRAME_INDEX = 0xb8,
    ACTOR_ELAPSED = 0xbc,
    ACTOR_TIME_SCALE = 0xc0,
    ACTOR_COUNTER = 0xcc,
    ACTOR_PROGRESS_STEPS = 0x4ac640,
    ACTOR_ANGLE = 0x22,
    ACTOR_SPOT_DRAW = 0x4ae010,
    SAVED_HIDDEN = 0x558958,
    SAVED_X = 0x558944,
    SAVED_Y = 0x558946,
    OFF_SCREEN = 0x7d00,
    ANIMATION_TICK = 0x4ac1f0,
    ACTOR_IMAGE_LOOKUP = 0x4ac8a0,
    ACTOR_UPDATE_BASE = 0x4adf70,
    ACTOR_UPDATE_HOOK = 0x154,
    TIMER_ARMED = 0x174,
    TIMER_COUNT = 0x17a,
    TIMER_LIMIT = 0x17c,
    ACTOR_X = 0xe,
    ACTOR_Y = 0x16,
    ACTOR_SCALE = 0x44,
    TEXT_PREPARE = 0x4ae150,
    TEXT_LAYOUT = 0x4408e0,
    TEXT_FONT = 0x15c,
    TITLE_WAIT_NEXT = 0x45cf70,
    RESOURCE_LOADED = 0x4877e0,
    RESOURCE_FRAME = 0x487770,
    ANIMATION_PLAY = 0x4ac250,
    ANIMATION_BACK = 0x4ac2b0,
    ANIMATION_NEXT = 0x4ac720,
    PLAY_BACK_STEP = 0x457460,
    PLAY_BACK_DONE = 0x457330,
    MENU_CHOICE_RUN = 0x471bb0,
    MENU_NEXT = 0x45c760,
    SLOT_PLACE = 0x4ac1e0,
    LAYER_UPDATE = 0x4b6200,
    LAYER_CALL_14 = 0x4b6170,
    LAYER_CALL_10 = 0x4b6120,
    LAYER_CALL_0C = 0x4b60c0,
    ACTOR_COUNTER_STEPS = 0x4ac3b0,
    ACTOR_WANDER = 0x45cff0,
    ACTOR_COUNTER_RESET = 0x4ac510,
    WANDERER_NEXT = 0x45d1a0,
    RESOURCE_FRAMES = 0x487860,
    INPUT_CLICK = 0x4764a0,
    CLICK_KEY = 0x74,
    ACTOR_HIT = 0x4b0b70,
    BUTTON_CLICKED = 0x45c600,
    BUTTON_PRESSED = 0x45c7e0,
    BUTTON_LIT = 0x45c480,
    BUTTON_INPUT = 0x45c2f0,
    ACTOR_SET_NEXT = 0x4ac910,
    MENU_CHOSEN = 0x532a48,
    BUTTON_SHADE = 0x52,
    ACTOR_KEY_PRESSED = 0x4b5500,
    ACTOR_APPROACH = 0x4ad530,
    INPUT = 0x54d640,
    INPUT_READY = 0x476480,
    INPUT_TAKE = 0x4762e0,
    ACTOR_KEY = 0x15c,
    APPROACH_VALUE = 0x48,
    APPROACH_TARGET = 0x4a,
    APPROACH_SPEED = 0x4c,
    ACTOR_COUNTER_ADVANCE = 0x4ac500,
    ACTOR_COUNTER_DUE = 0x4ac520,
    ACTOR_STEPS_CONSUME = 0x4ac5b0,
    ACTOR_SET_UPDATE = 0x4ac8f0,
    TITLE_RESOURCE = 0x546688,
    TITLE_UPDATE = 0x45ceb0,
    TITLE_RUN = 0x45cdc0,
    METHOD_UPDATE = 4,
    LIST_COUNT = 8,
    LIST_ITEMS = 4,
    ACTOR_PROGRESS_ADVANCE = 0x4ac600,
    ACTOR_PROGRESS_DONE = 0x4ac620,
    ACTOR_PROGRESS_CONSUME = 0x4ac6b0,
    ACTOR_TURN_STEP = 0x4ad060,
    ACTOR_SET_STEPS = 0x4ac860,
    ACTOR_POLAR = 0x4ad1c0,
    ACTOR_REPLACE = 0x4adfe0,
    ACTOR_ATTACH = 0x4ac8d0,
    ACTOR_ANIMATION = 0x4ac710,
    ACTOR_IMAGE_SET = 0x4ac8a0,
    ACTOR_TIME_SCALE_SET = 0x4ac7b0,
    RANDOM = 0x4826c0,
    RANDOM_GENERATOR = 0x598d30,
    WANDER_SPEED = 0x30,
    ACTOR_ORIGIN_Y = 0xa,
    ACTOR_ORIGIN_X = 8,
    SCREEN_WIDTH = 0x5b9c8e,
    SCREEN_HEIGHT = 0x5b9c90,
    STAR_WIDTH = 0x541014,
    STAR_HEIGHT = 0x541016,
    STAR_HALF_WIDTH = 0x541018,
    STAR_HALF_HEIGHT = 0x54101a,
    STAR_RESOURCE = 0x544c10,
    OBJECT_STATE = 0x58,
    OBJECT_ACTIVE_RUN = 0x45cff0,
    PAINT = 0x4b17b0,
    PAINT_CALL = 0x4b5550,
    PAINT_GATE = 0x4b17e0,
    PAINT_DRAW = 0x4b1fa0,
    PAINT_TARGET = 0x5bc010,
    PAINT_SETTINGS = 0x144,
    ACTOR_ATTACHED = 0x160,
    ACTOR_METHODS = 0x158,
    METHOD_DRAW = 8,
    TEXT_DRAW = 0x440ca0,
    TEXT_CURSOR = 0x440fc0,
    TIMER_RUNNING = 0x4b6560,
    TIMER_BYTE = 0x178,
    TIMER_WORD = 0x17a,
    STRING_SET_TEXT = 0x4ca370,
    TEXT_ALIGN = 0x160,
    TEXT_BOX = 0x162,
    ACTOR_TEXT_WIDTH = 0xf4,
    ACTOR_TEXT_HEIGHT = 0xf8,
    ACTOR_ANGLE_WORD = 0x24,
    ACTOR_TURN = 0x28,
    FULL_TURN = 360,
    TURN_WHOLE = 0x5bb5f4,
    TURN_STEPS = 0x5bb5f8,
    COSINES = 0x59939c,
    SINES = 0x598dfc,
    FIXED_MULTIPLY = 0x4849e0,
    ACTOR_FRAME_COUNTER = 0xb8,
    ACTOR_RESOURCE_DATA = 0xb0,
    ACTOR_CLEAR_COUNTER = 0x4ac380,
    ACTOR_CLEAR_FRAME_COUNTER = 0x4ac700,
    ACTOR_SPAN_X = 0x128,
    ACTOR_SPAN_Y = 0x12a,
    ACTOR_SPAN_WIDTH = 0x12c,
    ACTOR_SPAN_HEIGHT = 0x130,
    ACTOR_COUNTER_LIMIT = 0xd0,
    ACTOR_PROGRESS = 0xdc,
    ACTOR_PROGRESS_SCALE = 0xe0,
    ACTOR_STEPS = 0x4ac540,
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
    SCREEN_SURFACE_ARGUMENT = 0x278,
    ACTOR_DRAW_ON = 0x134,
    ACTOR_OUTLINE = 0x110,
    ACTOR_OUTLINE_INNER = 0x114,
    ACTOR_OUTLINE_OUTER = 0x118,
    ACTOR_HELPER = 0x150,
    DRAW_SCALE_SET = 0x5bb738,
    DRAW_OPACITY = 0x5bc00e,
    DRAW_BLEND = 0x5bb739,
    DRAW_CLIP = 0x5bc002,
    DRAW_FORMAT = 0x5bc000,
    DRAW_TARGET_FORMAT = 0x5bb730,
    DRAW_DEPTH = 0x5bb733,
    DRAW_OPERATION = 0x5bb72c,
    DRAW_TARGET = 0x5bc010,
    OUTLINE_MODE = 0x5bbffe,
    OUTLINE_PLAIN = 2,
    OUTLINE_LEFT = 0x5bbff4,
    OUTLINE_TOP = 0x5bbff6,
    OUTLINE_RIGHT = 0x5bbff8,
    OUTLINE_BOTTOM = 0x5bbffa,
    CLIP_LEFT = 0x5bb746,
    CLIP_TOP = 0x5bb748,
    CLIP_RIGHT = 0x5bb79e,
    CLIP_BOTTOM = 0x5bb7a0,
    OUTLINE_BOX = 0x5b9c60,
    DRAW_OUTLINE = 0x47c520,
    RENDER_FLAGS = 0x4af370,
    RENDER_RULE = 0x4af2a0,
    RENDER_TRAVERSAL = 0x4af530,
    RENDER_DIRECTION = 0x4af2e0,
    RENDER_MIRROR = 0x4af340,
    RENDER_PREPARE = 0x4ae250,
    SPOT_MARK = 0x4ab200,
    RULE_COUNT = 0x5c,
    RULE_OPERATIONS = 0x4ff024,
    RULE_OPERATIONS_STRIDE = 0x170,
    DIRECTION_SOURCES = 0x4ff6c4,
    MIRROR_ROUTINES = 0x4ff684,
    PLAIN_ROUTINES = 0x4ff5e4,
    HELPER_ROUTINES = 0x4ff604
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

/* The high word of a dword global, sign-extended (a 16.16 coordinate's integer part). */
static uint32_t global_high(Port *port, uint32_t address)
{
    return (uint32_t)((int32_t)port_u32(port, 0, address) >> 16);
}

/* The depth (0x5bb733) as the row of the drawing tables: 4 is 0, 2 is 1, 1 is 2, 0 is 3; any
 * other keeps the caller's ecx. */
static uint32_t depth_row(uint32_t depth, uint32_t ecx)
{
    switch (depth)
    {
        case 4:
            return 0;
        case 2:
            return 1;
        case 1:
            return 2;
        case 0:
            return 3;
        default:
            return ecx;
    }
}

/* The actor's drawing through the rule tables; returns the last eax. */
static uint32_t paint_body(Port *port, uint32_t actor, uint32_t ebx, uint32_t ecx)
{
    uint32_t eax;
    uint32_t rule;
    uint32_t traversal;
    uint32_t direction;
    uint32_t mirror;
    uint32_t routine;
    ebx = (ebx & 0xffff00ffu) | (port_u8(port, 0, DRAW_DEPTH) << 8);
    ecx = depth_row(port_u8(port, 0, DRAW_DEPTH), ecx);
    eax = port_call(port, RENDER_FLAGS, actor, 0, ebx, ecx);
    rule = port_call(port, RENDER_RULE, actor, eax, ebx, ecx);
    port_set32(port, 0, DRAW_OPERATION,
               rule < RULE_COUNT
                   ? port_u32(port, RULE_OPERATIONS, ecx * RULE_OPERATIONS_STRIDE + rule * 4)
                   : 0);
    traversal = port_call(port, RENDER_TRAVERSAL, actor, rule, ebx, ecx);
    direction = port_call(port, RENDER_DIRECTION, actor, traversal, ebx, ecx);
    ebx = direction < 8 ? port_u32(port, DIRECTION_SOURCES, ecx * 32 + direction * 4) : 0;
    mirror = port_call(port, RENDER_MIRROR, actor, traversal & 0xc, ebx, ecx);
    if (mirror >= 4)
    {
        return mirror;
    }
    routine = port_u32(port, MIRROR_ROUTINES, ecx * 16 + mirror * 4);
    if (routine == 0 || ebx == 0 || port_u32(port, 0, DRAW_OPERATION) == 0)
    {
        return mirror;
    }
    if (port_u32(port, actor, ACTOR_HELPER) != 0)
    {
        /* A plain straight copy may use the helper routine of its row instead. */
        if (rule == 0 && mirror < 2 && direction < 8)
        {
            uint32_t helper = port_u32(port, HELPER_ROUTINES, ecx * 32 + direction * 4);
            ecx <<= 5;
            if (helper != 0)
            {
                eax = port_call(port, helper, helper, routine, ebx, ecx);
                goto mark;
            }
        }
    }
    else if (rule == 0 && mirror == 0 && direction < 2)
    {
        eax = port_call(port, port_u32(port, PLAIN_ROUTINES, ecx * 8 + direction * 4),
                        direction * 4, routine, ebx, ecx);
        goto mark;
    }
    port_call(port, RENDER_PREPARE, actor, routine, ebx, ecx);
    eax = port_call(port, vertrix_lift_edx, ebx, vertrix_lift_edx, ebx, ecx);
mark:
    if (port_u32(port, actor, ACTOR_SPOT_MIRROR) != 1)
    {
        return eax;
    }
    return port_call(port, SPOT_MARK,
                     (uint32_t)((int32_t)port_u32(port, actor, ACTOR_SPOT_X) >> 16),
                     (uint32_t)((int32_t)port_u32(port, actor, ACTOR_SPOT_Y) >> 16),
                     (uint32_t)((int32_t)port_u32(port, actor, 0x12a) >> 16),
                     (uint32_t)((int32_t)port_u32(port, actor, 0x12e) >> 16));
}

/* One outline box, `inset` pixels inside the clip, in the colour at `colour_field`. */
static uint32_t outline_box(Port *port, uint32_t actor, uint32_t inset, uint32_t colour_field)
{
    uint32_t stack[7];
    stack[0] = global_high(port, CLIP_LEFT) + inset;
    stack[1] = global_high(port, CLIP_TOP) + inset;
    stack[2] = global_high(port, OUTLINE_LEFT);
    stack[3] = global_high(port, OUTLINE_RIGHT);
    stack[4] = global_high(port, OUTLINE_TOP);
    stack[5] = global_high(port, OUTLINE_BOTTOM);
    stack[6] = port_u32(port, actor, colour_field);
    return port_call_stack(port, DRAW_OUTLINE, port_u32(port, 0, DRAW_TARGET), OUTLINE_BOX,
                           global_high(port, CLIP_RIGHT) - inset,
                           global_high(port, CLIP_BOTTOM) - inset, stack, 7);
}

uint32_t vertrix_port_actor_paint(PORT_SIGNATURE)
{
    Port port;
    uint32_t actor = entry->eax;
    uint32_t eax = actor;
    uint32_t draw;
    port_open(&port, calls, services, globals, entry);
    draw = port_u32(&port, actor, ACTOR_DRAW_ON);
    if (draw != 0 && port_u8(&port, 0, DRAW_SCALE_SET) != 0)
    {
        /* Nothing to draw at full opacity, blended, unclipped and in the target's format. */
        int unchanged = port_u8(&port, 0, DRAW_OPACITY) == 0 &&
                        port_u8(&port, 0, DRAW_BLEND) == 1 && port_u16(&port, 0, DRAW_CLIP) == 0;
        if (unchanged)
        {
            eax = (eax & 0xffffff00u) | port_u8(&port, 0, DRAW_FORMAT);
            unchanged = port_u8(&port, 0, DRAW_FORMAT) == port_u8(&port, 0, DRAW_TARGET_FORMAT);
        }
        if (!unchanged)
        {
            eax = paint_body(&port, actor, draw, entry->ecx);
        }
    }
    if (port_u8(&port, actor, ACTOR_OUTLINE) != 1)
    {
        return port_return(&port, eax, entry->edx);
    }
    if (port_u8(&port, 0, OUTLINE_MODE) == OUTLINE_PLAIN)
    {
        uint32_t left = global_high(&port, CLIP_LEFT);
        uint32_t top = global_high(&port, CLIP_TOP);
        uint32_t right = global_high(&port, CLIP_RIGHT);
        uint32_t bottom = global_high(&port, CLIP_BOTTOM);
        uint32_t stack[7] = {
            left, top, right, bottom, left, top, port_u32(&port, actor, ACTOR_OUTLINE_OUTER)};
        eax = port_call_stack(&port, DRAW_OUTLINE, port_u32(&port, 0, DRAW_TARGET), OUTLINE_BOX,
                              right, bottom, stack, 7);
        return port_return(&port, eax, entry->edx);
    }
    outline_box(&port, actor, 1, ACTOR_OUTLINE_OUTER);
    eax = outline_box(&port, actor, 2, ACTOR_OUTLINE_INNER);
    return port_return(&port, eax, entry->edx);
}

uint32_t vertrix_port_actor_steps(PORT_SIGNATURE)
{
    Port port;
    uint32_t scale;
    port_open(&port, calls, services, globals, entry);
    scale = port_u32(&port, entry->eax, ACTOR_TIME_SCALE);
    if (scale == 0)
    {
        scale = 1;
    }
    return port_return(&port, port_u32(&port, entry->eax, ACTOR_ELAPSED) / scale, entry->edx);
}

uint32_t vertrix_port_actor_progress_steps(PORT_SIGNATURE)
{
    Port port;
    uint32_t scale;
    port_open(&port, calls, services, globals, entry);
    scale = port_u32(&port, entry->eax, ACTOR_PROGRESS_SCALE);
    if (scale == 0)
    {
        scale = 1;
    }
    return port_return(&port, port_u32(&port, entry->eax, ACTOR_PROGRESS) / scale, entry->edx);
}

uint32_t vertrix_port_actor_steps_consume(PORT_SIGNATURE)
{
    Port port;
    uint32_t actor = entry->eax;
    uint32_t scale;
    uint32_t time;
    uint32_t elapsed;
    port_open(&port, calls, services, globals, entry);
    scale = port_u32(&port, actor, ACTOR_TIME_SCALE);
    if (scale == 0)
    {
        scale = 1;
    }
    time = port_call(&port, ACTOR_STEPS, actor, actor, entry->ebx, scale) * scale;
    elapsed = port_u32(&port, actor, ACTOR_ELAPSED);
    port_set32(&port, actor, ACTOR_ELAPSED, time < elapsed ? elapsed - time : 0);
    return port_return(&port, time, entry->edx);
}

uint32_t vertrix_port_actor_counter_done(PORT_SIGNATURE)
{
    Port port;
    uint32_t actor = entry->eax;
    port_open(&port, calls, services, globals, entry);
    return port_return(
        &port, port_u32(&port, actor, ACTOR_COUNTER) >= port_u32(&port, actor, ACTOR_COUNTER_LIMIT),
        entry->edx);
}

uint32_t vertrix_port_actor_counter_advance(PORT_SIGNATURE)
{
    Port port;
    uint32_t actor = entry->eax;
    port_open(&port, calls, services, globals, entry);
    port_set32(&port, actor, ACTOR_COUNTER,
               port_u32(&port, actor, ACTOR_COUNTER) + port_u32(&port, 0, FRAME_TIME));
    return port_return(&port, actor, entry->edx);
}

uint32_t vertrix_port_actor_progress_done(PORT_SIGNATURE)
{
    Port port;
    uint32_t actor = entry->eax;
    port_open(&port, calls, services, globals, entry);
    return port_return(&port,
                       port_u32(&port, actor, ACTOR_PROGRESS) >=
                           port_u32(&port, actor, ACTOR_PROGRESS_SCALE),
                       entry->edx);
}

uint32_t vertrix_port_actor_progress_advance(PORT_SIGNATURE)
{
    Port port;
    uint32_t actor = entry->eax;
    port_open(&port, calls, services, globals, entry);
    port_set32(&port, actor, ACTOR_PROGRESS,
               port_u32(&port, actor, ACTOR_PROGRESS) + port_u32(&port, 0, FRAME_TIME));
    return port_return(&port, actor, entry->edx);
}

uint32_t vertrix_port_actor_set_span(PORT_SIGNATURE)
{
    Port port;
    uint32_t actor = entry->eax;
    port_open(&port, calls, services, globals, entry);
    port_set16(&port, actor, ACTOR_SPAN_X, entry->edx);
    port_set16(&port, actor, ACTOR_SPAN_Y, entry->ebx);
    port_set32(&port, actor, ACTOR_SPAN_WIDTH, entry->ecx);
    port_set32(&port, actor, ACTOR_SPAN_HEIGHT, entry->arguments[0]);
    return port_return(&port, actor, entry->edx);
}

uint32_t vertrix_port_actor_progress_consume(PORT_SIGNATURE)
{
    Port port;
    uint32_t actor = entry->eax;
    uint32_t scale;
    uint32_t progress;
    uint32_t current;
    port_open(&port, calls, services, globals, entry);
    scale = port_u32(&port, actor, ACTOR_PROGRESS_SCALE);
    if (scale == 0)
    {
        scale = 1;
    }
    progress = port_call(&port, ACTOR_PROGRESS_STEPS, actor, actor, entry->ebx, scale) * scale;
    current = port_u32(&port, actor, ACTOR_PROGRESS);
    port_set32(&port, actor, ACTOR_PROGRESS, progress < current ? current - progress : 0);
    return port_return(&port, progress, entry->edx);
}

/* The angle: the word at +0x24, read as the original's `[+0x22] >> 16`. */
static uint32_t actor_angle(Port *port, uint32_t actor)
{
    return (uint32_t)((int32_t)port_u32(port, actor, ACTOR_ANGLE) >> 16);
}

uint32_t vertrix_port_actor_polar_offset(PORT_SIGNATURE)
{
    Port port;
    uint32_t actor = entry->eax;
    uint32_t y_out = entry->arguments[0];
    uint32_t offset;
    port_open(&port, calls, services, globals, entry);
    offset = port_call(&port, FIXED_MULTIPLY,
                       port_u32(&port, 0, COSINES + actor_angle(&port, actor) * 4),
                       entry->edx << 16, entry->ebx, entry->ecx);
    port_set32(&port, entry->ecx, 0, (uint32_t)((int32_t)offset >> 16));
    offset =
        port_call(&port, FIXED_MULTIPLY, port_u32(&port, 0, SINES + actor_angle(&port, actor) * 4),
                  entry->ebx << 16, entry->ebx, entry->ecx);
    offset = (uint32_t)((int32_t)offset >> 16);
    port_set32(&port, y_out, 0, offset);
    return port_return(&port, offset, y_out);
}

uint32_t vertrix_port_actor_clear_frame_counter(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    port_set32(&port, entry->eax, ACTOR_FRAME_COUNTER, 0);
    return port_return(&port, entry->eax, entry->edx);
}

uint32_t vertrix_port_actor_clear_counter(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    port_set32(&port, entry->eax, ACTOR_COUNTER, 0);
    return port_return(&port, entry->eax, entry->edx);
}

uint32_t vertrix_port_actor_attach(PORT_SIGNATURE)
{
    Port port;
    uint32_t actor = entry->eax;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    port_call(&port, ACTOR_CLEAR_COUNTER, actor, entry->edx, entry->ebx, actor);
    result =
        port_call(&port, ACTOR_CLEAR_FRAME_COUNTER, actor, vertrix_lift_edx, entry->ebx, actor);
    port_set32(&port, actor, ACTOR_RESOURCE_DATA, vertrix_lift_edx);
    return port_return(&port, result, vertrix_lift_edx);
}

uint32_t vertrix_port_actor_turn(PORT_SIGNATURE)
{
    Port port;
    uint32_t actor = entry->eax;
    uint32_t steps = entry->edx;
    uint32_t whole = 1;
    uint32_t taken;
    uint32_t edx;
    port_open(&port, calls, services, globals, entry);
    taken = port_u32(&port, 0, TURN_STEPS);
    edx = (entry->edx & 0xffff0000u) | port_u16(&port, actor, ACTOR_TURN);
    if ((edx & 0xffff) != 0 && steps != 0)
    {
        for (taken = 0; taken < steps; taken++)
        {
            uint32_t angle =
                (port_u16(&port, actor, ACTOR_ANGLE_WORD) + port_u16(&port, actor, ACTOR_TURN)) &
                0xffff;
            port_set16(&port, actor, ACTOR_ANGLE_WORD, angle);
            edx = actor_angle(&port, actor);
            if ((int32_t)edx >= FULL_TURN)
            {
                port_set16(&port, actor, ACTOR_ANGLE_WORD, angle % FULL_TURN);
                whole = 0;
                edx = actor_angle(&port, actor);
            }
            if ((int32_t)edx < 0)
            {
                edx = ((port_u16(&port, actor, ACTOR_ANGLE_WORD) + FULL_TURN) & 0xffff) % FULL_TURN;
                port_set16(&port, actor, ACTOR_ANGLE_WORD, edx);
                whole = 0;
            }
        }
    }
    port_set32(&port, 0, TURN_WHOLE, whole);
    port_set32(&port, 0, TURN_STEPS, taken);
    return port_return(&port, whole, edx);
}

/* The signed word at actor + offset (the original's `[offset - 2] >> 16`). */
static uint32_t actor_word(Port *port, uint32_t actor, uint32_t offset)
{
    return (uint32_t)((int32_t)port_u32(port, actor, offset - 2) >> 16);
}

uint32_t vertrix_port_actor_text_layout(PORT_SIGNATURE)
{
    /* push ebp, ebx, ecx, edx, esi, then the four results. */
    enum
    {
        BELOW = 0x24
    };
    Port port;
    uint32_t actor = entry->eax;
    uint32_t ebp = entry->esp - 4;
    uint32_t arguments[7];
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_call(&port, TEXT_PREPARE, actor, entry->edx, entry->ebx, entry->ecx);
    arguments[0] = actor_word(&port, actor, TEXT_BOX + 6);
    arguments[1] = port_u32(&port, actor, TEXT_FONT);
    arguments[2] = port_u8(&port, actor, ACTOR_SCALE);
    arguments[3] = ebp - 0x20;
    arguments[4] = ebp - 0x1c;
    arguments[5] = ebp - 0x14;
    arguments[6] = ebp - 0x18;
    port_call_stack(&port, TEXT_LAYOUT,
                    (uint32_t)((int32_t)port_u32(&port, actor, TEXT_ALIGN - 3) >> 24),
                    actor_word(&port, actor, TEXT_BOX), actor_word(&port, actor, TEXT_BOX + 2),
                    actor_word(&port, actor, TEXT_BOX + 4), arguments, 7);
    port_set16(&port, actor, ACTOR_X, port_u32(&port, ebp, -0x14u));
    port_set16(&port, actor, ACTOR_Y, port_u32(&port, ebp, -0x18u));
    port_set32(&port, actor, ACTOR_TEXT_WIDTH, port_u32(&port, ebp, -0x20u));
    port_set32(&port, actor, ACTOR_TEXT_HEIGHT, port_u32(&port, ebp, -0x1cu));
    return port_return(&port, port_u32(&port, ebp, -0x1cu), entry->edx);
}

uint32_t vertrix_port_actor_spot_draw_call(PORT_SIGNATURE)
{
    Port port;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    result = port_call(&port, ACTOR_SPOT_DRAW, entry->eax, entry->edx, entry->ebx, entry->ecx);
    return port_return(&port, result, vertrix_lift_edx);
}

uint32_t vertrix_port_actor_place_saved(PORT_SIGNATURE)
{
    Port port;
    uint32_t actor = entry->eax;
    uint32_t result;
    uint32_t edx;
    port_open(&port, calls, services, globals, entry);
    if (port_u32(&port, 0, SAVED_HIDDEN) != 0)
    {
        port_set16(&port, actor, ACTOR_X, OFF_SCREEN);
        port_set16(&port, actor, ACTOR_Y, OFF_SCREEN);
    }
    else
    {
        port_set16(&port, actor, ACTOR_X, port_u16(&port, 0, SAVED_X));
        port_set16(&port, actor, ACTOR_Y, port_u16(&port, 0, SAVED_Y));
    }
    port_call(&port, ANIMATION_TICK, actor, actor, entry->ebx, entry->ecx);
    edx = vertrix_lift_edx;
    result = port_call(&port, ACTOR_IMAGE_LOOKUP, edx, edx, entry->ebx, entry->ecx);
    return port_return(&port, result, entry->edx);
}

uint32_t vertrix_port_actor_update_hook(PORT_SIGNATURE)
{
    Port port;
    uint32_t actor;
    uint32_t hook;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    result = port_call(&port, ACTOR_UPDATE_BASE, entry->eax, entry->eax, entry->ebx, entry->ecx);
    actor = vertrix_lift_edx;
    hook = port_u32(&port, actor, ACTOR_UPDATE_HOOK);
    if (hook != 0)
    {
        result = port_call(&port, hook, actor, actor, entry->ebx, entry->ecx);
    }
    return port_return(&port, result, entry->edx);
}

uint32_t vertrix_port_timer_running(PORT_SIGNATURE)
{
    Port port;
    uint32_t timer = entry->eax;
    port_open(&port, calls, services, globals, entry);
    return port_return(&port,
                       port_u32(&port, timer, TIMER_ARMED) == 0 ||
                           (int16_t)port_u16(&port, timer, TIMER_COUNT) <=
                               (int16_t)port_u16(&port, timer, TIMER_LIMIT),
                       entry->edx);
}

uint32_t vertrix_port_actor_set_text(PORT_SIGNATURE)
{
    /* push ebp, esi, then 0x14 bytes: the alignment byte and the four results. */
    enum
    {
        BELOW = 0x1c
    };
    Port port;
    uint32_t actor = entry->eax;
    uint32_t ebp = entry->esp - 4;
    uint32_t arguments[7];
    uint32_t edx;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set8(&port, ebp, -8u, entry->ebx);
    port_call(&port, STRING_SET_TEXT, actor + TEXT_FONT, entry->edx, entry->ecx, actor + TEXT_FONT);
    port_set8(&port, actor, TEXT_ALIGN, port_u8(&port, ebp, -8u));
    port_set16(&port, actor, TEXT_BOX + 2, entry->arguments[0]);
    port_set16(&port, actor, TEXT_BOX + 4, entry->arguments[1]);
    port_set16(&port, actor, TEXT_BOX + 6, entry->arguments[2]);
    port_set16(&port, actor, TEXT_BOX, entry->ecx);
    arguments[0] = actor_word(&port, actor, TEXT_BOX + 6);
    arguments[1] = port_u32(&port, actor, TEXT_FONT);
    arguments[2] = port_u8(&port, actor, ACTOR_SCALE);
    arguments[3] = ebp - 0x18;
    arguments[4] = ebp - 0x14;
    arguments[5] = ebp - 0x10;
    arguments[6] = ebp - 0xc;
    port_call_stack(&port, TEXT_LAYOUT,
                    (uint32_t)((int32_t)port_u32(&port, actor, TEXT_ALIGN - 3) >> 24),
                    actor_word(&port, actor, TEXT_BOX), actor_word(&port, actor, TEXT_BOX + 2),
                    actor_word(&port, actor, TEXT_BOX + 4), arguments, 7);
    edx = vertrix_lift_edx;
    port_set16(&port, actor, ACTOR_X, port_u32(&port, ebp, -0x10u));
    port_set16(&port, actor, ACTOR_Y, port_u32(&port, ebp, -0xcu));
    port_set32(&port, actor, ACTOR_TEXT_WIDTH, port_u32(&port, ebp, -0x18u));
    port_set32(&port, actor, ACTOR_TEXT_HEIGHT, port_u32(&port, ebp, -0x14u));
    return port_return(&port, port_u32(&port, ebp, -0x14u), edx);
}

uint32_t vertrix_port_actor_draw_text(PORT_SIGNATURE)
{
    /* push ebp, ebx, ecx, esi, edi, then the text slot. */
    enum
    {
        BELOW = 0x18
    };
    Port port;
    uint32_t actor = entry->eax;
    uint32_t surface = entry->edx;
    uint32_t ebp = entry->esp - 4;
    uint32_t arguments[6];
    uint32_t x;
    uint32_t y;
    uint32_t result;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, -0x14u, actor + TEXT_FONT);
    x = actor_word(&port, actor, ACTOR_X);
    y = actor_word(&port, actor, ACTOR_Y);
    arguments[0] = y;
    arguments[1] = y;
    arguments[2] = port_u32(&port, actor, TEXT_FONT);
    arguments[3] = actor;
    port_call_stack(&port, TEXT_DRAW, surface,
                    (uint32_t)((int32_t)port_u32(&port, actor, TEXT_ALIGN - 3) >> 24), x, x,
                    arguments, 4);
    result = port_call(&port, TIMER_RUNNING, actor, vertrix_lift_edx, x, x);
    if (result != 0)
    {
        return port_return(&port, result, vertrix_lift_edx);
    }
    arguments[0] = actor_word(&port, actor, ACTOR_X);
    arguments[1] = actor_word(&port, actor, ACTOR_Y);
    arguments[2] = arguments[1];
    arguments[3] = port_u32(&port, port_u32(&port, ebp, -0x14u), 0);
    arguments[4] = actor;
    arguments[5] = actor_word(&port, actor, TIMER_WORD);
    result = port_call_stack(&port, TEXT_CURSOR, surface,
                             (uint32_t)((int32_t)port_u32(&port, actor, TEXT_ALIGN - 3) >> 24),
                             (uint32_t)((int32_t)port_u32(&port, actor, TIMER_BYTE - 3) >> 24),
                             arguments[0], arguments, 6);
    return port_return(&port, result, vertrix_lift_edx);
}

uint32_t vertrix_port_actor_paint_call(PORT_SIGNATURE)
{
    Port port;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    result = port_call(&port, PAINT, entry->eax, entry->edx, entry->ebx, entry->ecx);
    return port_return(&port, result, vertrix_lift_edx);
}

uint32_t vertrix_port_actor_paint_target(PORT_SIGNATURE)
{
    Port port;
    uint32_t actor = entry->eax;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    port_set32(&port, 0, PAINT_TARGET, entry->edx);
    result = port_call(&port, PAINT_GATE, actor, port_u32(&port, actor, PAINT_SETTINGS), entry->ebx,
                       actor);
    if (result != 0)
    {
        result = port_call(&port, PAINT_DRAW, actor, vertrix_lift_edx, entry->ebx, actor);
    }
    return port_return(&port, result, vertrix_lift_edx);
}

uint32_t vertrix_port_actor_paint_attached(PORT_SIGNATURE)
{
    Port port;
    uint32_t actor = entry->eax;
    uint32_t attached;
    uint32_t methods;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    result = port_call(&port, PAINT_CALL, actor, entry->edx, actor, entry->edx);
    attached = port_u32(&port, actor, ACTOR_ATTACHED);
    if (attached == 0)
    {
        return port_return(&port, result, 0);
    }
    methods = port_u32(&port, attached, ACTOR_METHODS);
    result = port_call(&port, port_u32(&port, methods, METHOD_DRAW), attached, entry->edx, methods,
                       entry->edx);
    return port_return(&port, result, vertrix_lift_edx);
}

uint32_t vertrix_port_actor_draw_call(PORT_SIGNATURE)
{
    Port port;
    uint32_t methods;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    methods = port_u32(&port, entry->eax, ACTOR_METHODS);
    result = port_call(&port, port_u32(&port, methods, METHOD_DRAW), entry->eax, entry->edx,
                       entry->ebx, methods);
    return port_return(&port, result, vertrix_lift_edx);
}

uint32_t vertrix_port_actor_set_time_scale(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    port_set32(&port, entry->eax, ACTOR_TIME_SCALE, entry->edx * 12);
    return port_return(&port, entry->edx * 12, entry->edx);
}

uint32_t vertrix_port_object_run_active(PORT_SIGNATURE)
{
    Port port;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    if (port_u32(&port, entry->eax, OBJECT_STATE) != 1)
    {
        return port_return(&port, entry->eax, entry->edx);
    }
    result = port_call(&port, OBJECT_ACTIVE_RUN, entry->eax, entry->edx, entry->ebx, entry->ecx);
    return port_return(&port, result, vertrix_lift_edx);
}

uint32_t vertrix_port_actor_wander(PORT_SIGNATURE)
{
    /* push ebp, ebx, ecx, edx, esi, edi, then the old y and the polar results. */
    enum
    {
        BELOW = 0x20
    };
    Port port;
    uint32_t actor = entry->eax;
    uint32_t ebp = entry->esp - 4;
    uint32_t arguments[1];
    uint32_t eax;
    uint32_t edx;
    uint32_t x;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_call(&port, ACTOR_PROGRESS_ADVANCE, actor, entry->edx, entry->ebx, entry->ecx);
    eax = port_call(&port, ACTOR_PROGRESS_DONE, actor, vertrix_lift_edx, entry->ebx, entry->ecx);
    if (eax != 1)
    {
        return port_return(&port, eax, entry->edx);
    }
    eax = port_call(&port, ACTOR_PROGRESS_STEPS, actor, vertrix_lift_edx, entry->ebx, entry->ecx);
    port_call(&port, ACTOR_PROGRESS_CONSUME, actor, eax, entry->ebx, entry->ecx);
    eax = port_call(&port, ACTOR_TURN_STEP, actor, vertrix_lift_edx, entry->ebx, entry->ecx);
    if (eax == 0)
    {
        eax = port_call(&port, RANDOM, RANDOM_GENERATOR, 5, entry->ebx, entry->ecx);
        port_set16(&port, actor, WANDER_SPEED, eax);
        eax = port_call(&port, RANDOM, RANDOM_GENERATOR, 5, entry->ebx, entry->ecx);
        eax = port_call(&port, ACTOR_SET_STEPS, actor, (eax & 0xffff) + 5, entry->ebx, entry->ecx);
    }
    port_set32(&port, ebp, -0x18u, (eax & 0xffff0000u) | port_u16(&port, actor, ACTOR_Y));
    edx = actor_word(&port, actor, WANDER_SPEED);
    x = port_u16(&port, actor, ACTOR_X);
    arguments[0] = ebp - 0x1c;
    eax = port_call_stack(&port, ACTOR_POLAR, actor, edx, edx, ebp - 0x20, arguments, 1);
    edx = ((vertrix_lift_edx & 0xffff0000u) | port_u16(&port, actor, ACTOR_ORIGIN_Y)) +
          port_u32(&port, ebp, -0x1cu);
    port_set16(&port, actor, ACTOR_Y, edx);
    if ((edx & 0xffff) == port_u16(&port, ebp, -0x18u) && x == port_u16(&port, actor, ACTOR_X))
    {
        return port_return(&port, eax, entry->edx);
    }
    eax = port_call(&port, ACTOR_REPLACE, actor, edx, port_u32(&port, ebp, -0x1cu),
                    port_u32(&port, ebp, -0x18u));
    return port_return(&port, eax, entry->edx);
}

uint32_t vertrix_port_star_setup(PORT_SIGNATURE)
{
    Port port;
    uint32_t actor = entry->edx;
    uint32_t value;
    port_open(&port, calls, services, globals, entry);
    port_set16(&port, 0, STAR_WIDTH, port_u16(&port, 0, SCREEN_WIDTH));
    port_set16(&port, 0, STAR_HEIGHT, port_u16(&port, 0, SCREEN_HEIGHT));
    port_set16(&port, 0, STAR_HALF_WIDTH, port_u16(&port, 0, SCREEN_WIDTH) >> 1);
    port_set16(&port, 0, STAR_HALF_HEIGHT, port_u16(&port, 0, SCREEN_HEIGHT) >> 1);
    port_call(&port, ACTOR_ATTACH, actor, STAR_RESOURCE, entry->ebx, actor);
    port_call(&port, ACTOR_ANIMATION, actor, 0xf, entry->ebx, actor);
    port_call(&port, ACTOR_IMAGE_SET, actor, 1, entry->ebx, actor);
    port_call(&port, ACTOR_TIME_SCALE_SET, actor, vertrix_lift_edx, entry->ebx, actor);
    port_set16(&port, actor, ACTOR_X, 0);
    port_set16(&port, actor, ACTOR_Y, 0);
    value = port_call(&port, RANDOM, RANDOM_GENERATOR, port_u16(&port, 0, STAR_WIDTH), entry->ebx,
                      actor);
    port_set16(&port, actor, ACTOR_ORIGIN_X, (value - port_u16(&port, 0, STAR_HALF_WIDTH)) * 0x96);
    value = port_call(&port, RANDOM, RANDOM_GENERATOR, port_u16(&port, 0, STAR_HEIGHT), entry->ebx,
                      actor);
    port_set32(&port, actor, STEP_VALUE, 0xc8);
    port_set16(&port, actor, ACTOR_ORIGIN_Y, (value - port_u16(&port, 0, STAR_HALF_HEIGHT)) * 0x96);
    port_set32(&port, actor, STEP_GOAL, 0);
    value = (port_call(&port, RANDOM, RANDOM_GENERATOR, 3, entry->ebx, actor) & 0xffff) + 1;
    port_set32(&port, actor, PAINT_SETTINGS, 0);
    port_set32(&port, actor, STEP_SPEED, value);
    return port_return(&port, value, vertrix_lift_edx);
}

uint32_t vertrix_port_actor_counter_steps(PORT_SIGNATURE)
{
    Port port;
    uint32_t limit;
    port_open(&port, calls, services, globals, entry);
    limit = port_u32(&port, entry->eax, ACTOR_COUNTER_LIMIT);
    if (limit == 0)
    {
        limit = 1;
    }
    return port_return(&port, port_u32(&port, entry->eax, ACTOR_COUNTER) / limit, entry->edx);
}

uint32_t vertrix_port_title_actor_frame(PORT_SIGNATURE)
{
    Port port;
    uint32_t actor = entry->eax;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    port_call(&port, TITLE_RUN, actor, entry->edx, entry->ebx, actor);
    port_call(&port, ACTOR_COUNTER_ADVANCE, actor, vertrix_lift_edx, entry->ebx, actor);
    result = port_call(&port, ACTOR_COUNTER_DUE, actor, vertrix_lift_edx, entry->ebx, actor);
    if (result != 1)
    {
        return port_return(&port, result, entry->edx);
    }
    port_call(&port, ACTOR_STEPS_CONSUME, actor, vertrix_lift_edx, entry->ebx, actor);
    if (port_u32(&port, actor, OBJECT_STATE) == 0)
    {
        port_call(&port, ACTOR_ATTACH, actor, TITLE_RESOURCE, entry->ebx, actor);
        port_call(&port, ACTOR_IMAGE_SET, actor, vertrix_lift_edx, entry->ebx, actor);
        port_call(&port, ACTOR_REPLACE, actor, vertrix_lift_edx, entry->ebx, actor);
    }
    result = port_call(&port, ACTOR_SET_UPDATE, actor, TITLE_UPDATE, entry->ebx, actor);
    return port_return(&port, result, entry->edx);
}

uint32_t vertrix_port_actor_list_update(PORT_SIGNATURE)
{
    Port port;
    uint32_t list = entry->eax;
    uint32_t count;
    uint32_t number = 0;
    uint32_t offset = 0;
    uint32_t eax;
    port_open(&port, calls, services, globals, entry);
    count = eax = port_u32(&port, list, LIST_COUNT);
    while (number < count && count != 0)
    {
        uint32_t item = port_u32(&port, port_u32(&port, list, LIST_ITEMS), offset);
        uint32_t methods = port_u32(&port, item, ACTOR_METHODS);
        offset += 4;
        eax = port_call(&port, port_u32(&port, methods, METHOD_UPDATE), item, number + 1, methods,
                        offset);
        number = vertrix_lift_edx;
    }
    return port_return(&port, eax, entry->edx);
}

/* 0x4b6170 and 0x4b6120: each actor's table entry `method` with edx the argument. */
static uint32_t list_call_numbered(PORT_SIGNATURE, uint32_t method)
{
    /* push ebp, ebx, ecx, esi, edi, then the list and count slots. */
    enum
    {
        BELOW = 0x1c
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t list = entry->eax;
    uint32_t count;
    uint32_t number = 0;
    uint32_t offset = 0;
    uint32_t eax;
    uint32_t edx = entry->edx;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, -0x14u, list);
    count = eax = port_u32(&port, list, LIST_COUNT);
    port_set32(&port, ebp, -0x18u, count);
    if (count == 0)
    {
        return port_return(&port, eax, edx);
    }
    do
    {
        uint32_t item =
            port_u32(&port, port_u32(&port, port_u32(&port, ebp, -0x14u), LIST_ITEMS), offset);
        uint32_t methods = port_u32(&port, item, ACTOR_METHODS);
        number++;
        eax = port_call(&port, port_u32(&port, methods, method), item, entry->edx, number, offset);
        edx = port_u32(&port, ebp, -0x18u);
        offset += 4;
    } while (number < edx);
    return port_return(&port, eax, edx);
}

uint32_t vertrix_port_actor_list_call14(PORT_SIGNATURE)
{
    return list_call_numbered(calls, services, globals, entry, 0x14);
}

uint32_t vertrix_port_actor_list_call10(PORT_SIGNATURE)
{
    return list_call_numbered(calls, services, globals, entry, 0x10);
}

uint32_t vertrix_port_actor_list_call0c(PORT_SIGNATURE)
{
    /* push ebp, ecx, esi, edi, then the list, the arguments and the count. */
    enum
    {
        BELOW = 0x20
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t list = entry->eax;
    uint32_t count;
    uint32_t number = 0;
    uint32_t offset = 0;
    uint32_t eax;
    uint32_t edx = entry->edx;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, -0x10u, list);
    port_set32(&port, ebp, -0x14u, entry->edx);
    port_set32(&port, ebp, -0x1cu, entry->ebx);
    count = eax = port_u32(&port, list, LIST_COUNT);
    port_set32(&port, ebp, -0x18u, count);
    if (count == 0)
    {
        return port_return(&port, eax, edx);
    }
    do
    {
        uint32_t item =
            port_u32(&port, port_u32(&port, port_u32(&port, ebp, -0x10u), LIST_ITEMS), offset);
        uint32_t methods = port_u32(&port, item, ACTOR_METHODS);
        number++;
        eax = port_call(&port, port_u32(&port, methods, 0xc), item, port_u32(&port, ebp, -0x14u),
                        port_u32(&port, ebp, -0x1cu), offset);
        edx = port_u32(&port, ebp, -0x18u);
        offset += 4;
    } while (number < edx);
    return port_return(&port, eax, edx);
}

uint32_t vertrix_port_actor_array_update(PORT_SIGNATURE)
{
    Port port;
    uint32_t at = entry->eax;
    uint32_t end;
    uint32_t eax = entry->eax;
    port_open(&port, calls, services, globals, entry);
    if (entry->edx == 0)
    {
        return port_return(&port, eax, entry->edx);
    }
    end = entry->eax + entry->edx * 4;
    do
    {
        uint32_t item = port_u32(&port, at, 0);
        if (item != 0)
        {
            uint32_t methods = port_u32(&port, item, ACTOR_METHODS);
            eax = port_call(&port, port_u32(&port, methods, METHOD_UPDATE), item, at, end, methods);
            at = vertrix_lift_edx;
        }
        at += 4;
    } while (at < end);
    return port_return(&port, eax, at);
}

uint32_t vertrix_port_actor_key_pressed(PORT_SIGNATURE)
{
    Port port;
    uint32_t actor = entry->eax;
    uint32_t key;
    port_open(&port, calls, services, globals, entry);
    key = port_u16(&port, actor, ACTOR_KEY);
    if (key == 0 || port_call(&port, INPUT_READY, INPUT, key, 0, actor) != 1)
    {
        return port_return(&port, 0, entry->edx);
    }
    port_call(&port, INPUT_TAKE, INPUT, port_u16(&port, actor, ACTOR_KEY), 1, actor);
    return port_return(&port, 1, entry->edx);
}

uint32_t vertrix_port_actor_approach(PORT_SIGNATURE)
{
    Port port;
    uint32_t actor = entry->eax;
    uint32_t step;
    int32_t from;
    int32_t to;
    int32_t value;
    uint32_t target;
    port_open(&port, calls, services, globals, entry);
    step = entry->edx * actor_word(&port, actor, APPROACH_SPEED);
    from = (int32_t)actor_word(&port, actor, APPROACH_VALUE);
    to = (int32_t)actor_word(&port, actor, APPROACH_TARGET);
    value = from;
    if (from > to)
    {
        value = (int32_t)((uint32_t)from - step);
        if (value < to)
        {
            value = to;
        }
    }
    else if (from < to)
    {
        value = (int32_t)((uint32_t)from + step);
        if (value > to)
        {
            value = to;
        }
    }
    target = port_u16(&port, actor, APPROACH_TARGET);
    port_set16(&port, actor, APPROACH_VALUE, (uint32_t)value);
    return port_return(&port, ((uint32_t)value & 0xffff) != target,
                       ((uint32_t)to & 0xffff0000u) | target);
}

/* The saved pointer position, off screen while it is hidden, in edx and ebx as the original leaves
 * them. */
static void pointer_place(Port *port, uint32_t *edx, uint32_t *ebx)
{
    uint32_t y = port_u32(port, 0, SAVED_HIDDEN) != 0
                     ? OFF_SCREEN
                     : (*edx & 0xffff0000u) | port_u16(port, 0, SAVED_Y);
    *ebx = (uint32_t)(int16_t)y;
    *edx = port_u32(port, 0, SAVED_HIDDEN) != 0 ? OFF_SCREEN
                                                : (uint32_t)(int16_t)port_u16(port, 0, SAVED_X);
}

uint32_t vertrix_port_menu_button_input(PORT_SIGNATURE)
{
    /* push ebp, ebx, ecx, edx, esi, edi, then the click's three results. */
    enum
    {
        BELOW = 0x20
    };
    Port port;
    uint32_t button = entry->eax;
    uint32_t ebp = entry->esp - 4;
    uint32_t arguments[1];
    uint32_t eax;
    uint32_t edx;
    uint32_t ebx;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    if (port_call(&port, INPUT_READY, INPUT, CLICK_KEY, entry->ebx, button) != 1)
    {
        eax = port_call(&port, ACTOR_KEY_PRESSED, button, vertrix_lift_edx, entry->ebx, button);
        if (eax == 0)
        {
            return port_return(&port, eax, entry->edx);
        }
        eax = port_call(&port, ACTOR_SET_NEXT, button, BUTTON_PRESSED, entry->ebx, button);
        port_set32(&port, 0, MENU_CHOSEN, 1);
        return port_return(&port, eax, entry->edx);
    }
    arguments[0] = ebp - 0x18;
    eax =
        port_call_stack(&port, INPUT_CLICK, INPUT, CLICK_KEY, ebp - 0x20, ebp - 0x1c, arguments, 1);
    edx = eax;
    pointer_place(&port, &edx, &ebx);
    eax = port_call(&port, ACTOR_HIT, button, edx, ebx, ebp - 0x1c);
    if ((eax & 0xff) == 0)
    {
        return port_return(&port, eax, entry->edx);
    }
    eax = port_call(&port, ACTOR_SET_UPDATE, button, BUTTON_CLICKED, ebx, ebp - 0x1c);
    return port_return(&port, eax, entry->edx);
}

uint32_t vertrix_port_menu_button_frame(PORT_SIGNATURE)
{
    Port port;
    uint32_t button = entry->eax;
    uint32_t edx;
    uint32_t ebx;
    uint32_t eax;
    port_open(&port, calls, services, globals, entry);
    port_call(&port, ACTOR_COUNTER_ADVANCE, button, entry->edx, entry->ebx, button);
    eax = port_call(&port, ACTOR_COUNTER_DUE, button, vertrix_lift_edx, entry->ebx, button);
    if (eax == 1)
    {
        eax = port_call(&port, ACTOR_STEPS, button, vertrix_lift_edx, entry->ebx, button);
        port_call(&port, ACTOR_STEPS_CONSUME, button, eax, entry->ebx, button);
        port_set16(&port, button, APPROACH_TARGET, 0);
        port_set16(&port, button, APPROACH_SPEED, 5);
        port_call(&port, ACTOR_APPROACH, button, vertrix_lift_edx, entry->ebx, button);
    }
    edx = vertrix_lift_edx;
    pointer_place(&port, &edx, &ebx);
    eax = port_call(&port, ACTOR_HIT, button, edx, ebx, button);
    if ((eax & 0xff) != 0)
    {
        port_set16(&port, button, APPROACH_VALUE, 0x23);
        port_set8(&port, button, BUTTON_SHADE, 0xa);
        port_call(&port, ACTOR_SET_UPDATE, button, BUTTON_LIT, ebx, button);
    }
    else
    {
        port_set8(&port, button, BUTTON_SHADE, 9);
    }
    eax = port_call(&port, BUTTON_INPUT, button, vertrix_lift_edx, ebx, button);
    return port_return(&port, eax, entry->edx);
}

uint32_t vertrix_port_actor_frame_count(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    port_set32(&port, entry->eax, ACTOR_FRAME_INDEX,
               port_u32(&port, entry->eax, ACTOR_FRAME_INDEX) + 1);
    return port_return(&port, entry->eax, entry->edx);
}

uint32_t vertrix_port_actor_frames_done(PORT_SIGNATURE)
{
    Port port;
    uint32_t frames;
    port_open(&port, calls, services, globals, entry);
    frames = port_call(&port, RESOURCE_FRAMES, port_u32(&port, entry->eax, ACTOR_RESOURCE_DATA),
                       entry->eax, entry->ebx, entry->ecx);
    return port_return(&port, frames == port_u32(&port, vertrix_lift_edx, ACTOR_FRAME_INDEX),
                       entry->edx);
}

uint32_t vertrix_port_actor_step_value(PORT_SIGNATURE)
{
    Port port;
    uint32_t actor = entry->eax;
    uint32_t step;
    int32_t value;
    int32_t goal;
    int32_t next;
    port_open(&port, calls, services, globals, entry);
    step = entry->edx * port_u32(&port, actor, STEP_SPEED);
    value = (int32_t)port_u32(&port, actor, STEP_VALUE);
    goal = (int32_t)port_u32(&port, actor, STEP_GOAL);
    next = value;
    if (value > goal)
    {
        next = (int32_t)((uint32_t)value - step);
        if (next < goal)
        {
            next = goal;
        }
    }
    else if (value < goal)
    {
        next = (int32_t)((uint32_t)value + step);
        if (next > goal)
        {
            next = goal;
        }
    }
    goal = (int32_t)port_u32(&port, actor, STEP_GOAL);
    port_set32(&port, actor, STEP_VALUE, (uint32_t)next);
    return port_return(&port, next != goal, (uint32_t)goal);
}

uint32_t vertrix_port_actor_counter_consume(PORT_SIGNATURE)
{
    Port port;
    uint32_t actor = entry->eax;
    uint32_t limit;
    uint32_t taken;
    uint32_t counter;
    port_open(&port, calls, services, globals, entry);
    limit = port_u32(&port, actor, ACTOR_COUNTER_LIMIT);
    if (limit == 0)
    {
        limit = 1;
    }
    taken = port_call(&port, ACTOR_COUNTER_STEPS, actor, actor, entry->ebx, limit) * limit;
    counter = port_u32(&port, actor, ACTOR_COUNTER);
    port_set32(&port, actor, ACTOR_COUNTER, taken < counter ? counter - taken : 0);
    return port_return(&port, taken, entry->edx);
}

uint32_t vertrix_port_wanderer_frame(PORT_SIGNATURE)
{
    Port port;
    uint32_t actor = entry->eax;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    port_call(&port, ACTOR_WANDER, actor, entry->edx, entry->ebx, actor);
    port_call(&port, ACTOR_COUNTER_ADVANCE, actor, vertrix_lift_edx, entry->ebx, actor);
    result = port_call(&port, ACTOR_COUNTER_DUE, actor, vertrix_lift_edx, entry->ebx, actor);
    if (result != 1)
    {
        return port_return(&port, result, entry->edx);
    }
    port_call(&port, ACTOR_COUNTER_RESET, actor, vertrix_lift_edx, entry->ebx, actor);
    port_set32(&port, actor, 0x64, port_u32(&port, actor, 0x68));
    result = port_call(&port, ACTOR_SET_UPDATE, actor, WANDERER_NEXT, entry->ebx, actor);
    return port_return(&port, result, entry->edx);
}

/* A layer list's actors through 0x4b6200, 0x4b6170, 0x4b6120 or 0x4b60c0. */
static uint32_t layer_call(PORT_SIGNATURE, uint32_t list, uint32_t routine)
{
    Port port;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    if (routine == LAYER_UPDATE)
    {
        result = port_call(&port, routine, list, entry->edx, entry->ebx, entry->ecx);
        return port_return(&port, result, vertrix_lift_edx);
    }
    if (routine == LAYER_CALL_0C)
    {
        result = port_call(&port, routine, list, entry->eax, entry->edx, entry->ecx);
        return port_return(&port, result, vertrix_lift_edx);
    }
    result = port_call(&port, routine, list, entry->eax, entry->ebx, entry->ecx);
    return port_return(&port, result, entry->edx);
}

uint32_t vertrix_port_layer_back_update(PORT_SIGNATURE)
{
    return layer_call(calls, services, globals, entry, 0x54671c, LAYER_UPDATE);
}

uint32_t vertrix_port_layer_back_call14(PORT_SIGNATURE)
{
    return layer_call(calls, services, globals, entry, 0x54671c, LAYER_CALL_14);
}

uint32_t vertrix_port_layer_back_call10(PORT_SIGNATURE)
{
    return layer_call(calls, services, globals, entry, 0x54671c, LAYER_CALL_10);
}

uint32_t vertrix_port_layer_back_call0c(PORT_SIGNATURE)
{
    return layer_call(calls, services, globals, entry, 0x54671c, LAYER_CALL_0C);
}

uint32_t vertrix_port_layer_middle_update(PORT_SIGNATURE)
{
    return layer_call(calls, services, globals, entry, 0x546730, LAYER_UPDATE);
}

uint32_t vertrix_port_layer_middle_call14(PORT_SIGNATURE)
{
    return layer_call(calls, services, globals, entry, 0x546730, LAYER_CALL_14);
}

uint32_t vertrix_port_layer_middle_call10(PORT_SIGNATURE)
{
    return layer_call(calls, services, globals, entry, 0x546730, LAYER_CALL_10);
}

uint32_t vertrix_port_layer_middle_call0c(PORT_SIGNATURE)
{
    return layer_call(calls, services, globals, entry, 0x546730, LAYER_CALL_0C);
}

uint32_t vertrix_port_layer_front_update(PORT_SIGNATURE)
{
    return layer_call(calls, services, globals, entry, 0x546744, LAYER_UPDATE);
}

uint32_t vertrix_port_layer_front_call14(PORT_SIGNATURE)
{
    return layer_call(calls, services, globals, entry, 0x546744, LAYER_CALL_14);
}

uint32_t vertrix_port_layer_front_call10(PORT_SIGNATURE)
{
    return layer_call(calls, services, globals, entry, 0x546744, LAYER_CALL_10);
}

uint32_t vertrix_port_layer_front_call0c(PORT_SIGNATURE)
{
    return layer_call(calls, services, globals, entry, 0x546744, LAYER_CALL_0C);
}

uint32_t vertrix_port_actor_keep_place(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    port_set16(&port, entry->eax, 0x4c, port_u16(&port, entry->eax, 0x48));
    port_set16(&port, entry->eax, 0x4e, port_u16(&port, entry->eax, 0x4a));
    return port_return(&port, entry->eax, entry->edx);
}

uint32_t vertrix_port_actor_replace(PORT_SIGNATURE)
{
    Port port;
    uint32_t actor = entry->eax;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    if (port_u16(&port, actor, 0x148) == 0xffff)
    {
        port_set32(&port, actor, 0x120, 1);
        return port_return(&port, actor, entry->edx);
    }
    result = port_call(&port, SLOT_PLACE, actor_word(&port, actor, 0x148), entry->edx, entry->ebx,
                       entry->ecx);
    return port_return(&port, result, vertrix_lift_edx);
}

static const uint32_t cursor_actors_update[4] = {0x54670c, 0x546710, 0x546714, 0x546718};
static const uint32_t cursor_actors_draw[4] = {0x546710, 0x546714, 0x546718, 0x54670c};

uint32_t vertrix_port_cursor_actors_update(PORT_SIGNATURE)
{
    Port port;
    uint32_t result = entry->eax;
    uint32_t index;
    port_open(&port, calls, services, globals, entry);
    for (index = 0; index < 4; index++)
    {
        uint32_t actor = port_u32(&port, 0, cursor_actors_update[index]);
        uint32_t methods = port_u32(&port, actor, ACTOR_METHODS);
        result = port_call(&port, port_u32(&port, methods, METHOD_UPDATE), actor, methods,
                           entry->ebx, entry->ecx);
    }
    return port_return(&port, result, entry->edx);
}

uint32_t vertrix_port_cursor_actors_draw(PORT_SIGNATURE)
{
    Port port;
    uint32_t surface = entry->eax;
    uint32_t result = entry->eax;
    uint32_t index;
    port_open(&port, calls, services, globals, entry);
    for (index = 0; index < 4; index++)
    {
        uint32_t actor = port_u32(&port, 0, cursor_actors_draw[index]);
        uint32_t methods = port_u32(&port, actor, ACTOR_METHODS);
        result = port_call(&port, port_u32(&port, methods, METHOD_DRAW), actor, surface, methods,
                           surface);
    }
    return port_return(&port, result, entry->edx);
}

uint32_t vertrix_port_menu_choice(PORT_SIGNATURE)
{
    Port port;
    uint32_t menu = entry->eax;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    if (port_u32(&port, 0, MENU_CHOSEN) != 1)
    {
        return port_return(&port, menu, entry->edx);
    }
    port_call(&port, MENU_CHOICE_RUN, menu, entry->edx, entry->ebx, menu);
    port_set32(&port, 0, MENU_CHOSEN, 0);
    result = port_call(&port, ACTOR_SET_UPDATE, menu, MENU_NEXT, 0, menu);
    return port_return(&port, result, entry->edx);
}

uint32_t vertrix_port_actor_play_then(PORT_SIGNATURE)
{
    Port port;
    uint32_t actor = entry->eax;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    if (port_call(&port, ANIMATION_PLAY, actor, entry->edx, entry->ebx, actor) == 0)
    {
        port_call(&port, ANIMATION_NEXT, actor, PLAY_BACK_STEP, entry->ebx, actor);
        port_call(&port, ACTOR_SET_UPDATE, actor, vertrix_lift_edx, entry->ebx, actor);
    }
    result = port_call(&port, ACTOR_IMAGE_SET, actor, vertrix_lift_edx, entry->ebx, actor);
    return port_return(&port, result, entry->edx);
}

uint32_t vertrix_port_actor_play_back(PORT_SIGNATURE)
{
    Port port;
    uint32_t actor = entry->eax;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    if (port_call(&port, ANIMATION_BACK, actor, entry->edx, entry->ebx, actor) == 0)
    {
        port_call(&port, ACTOR_ANIMATION, actor, 0, entry->ebx, actor);
        port_call(&port, ACTOR_SET_UPDATE, actor, PLAY_BACK_DONE, entry->ebx, actor);
        port_set8(&port, actor, 0x4e, 0);
    }
    result = port_call(&port, ACTOR_IMAGE_SET, actor, vertrix_lift_edx, entry->ebx, actor);
    return port_return(&port, result, entry->edx);
}

uint32_t vertrix_port_actor_array_draw(PORT_SIGNATURE)
{
    Port port;
    uint32_t at = entry->eax;
    uint32_t end;
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    port_open(&port, calls, services, globals, entry);
    if (entry->edx == 0)
    {
        return port_return(&port, eax, edx);
    }
    end = entry->eax + entry->edx * 4;
    do
    {
        edx = port_u32(&port, at, 0);
        if (edx != 0)
        {
            uint32_t methods = port_u32(&port, edx, ACTOR_METHODS);
            eax = port_call(&port, port_u32(&port, methods, METHOD_DRAW), edx, entry->ebx,
                            entry->ebx, at);
            edx = vertrix_lift_edx;
        }
        at += 4;
    } while (at < end);
    return port_return(&port, eax, edx);
}

uint32_t vertrix_port_actor_update_routine(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    return port_return(&port, port_u32(&port, entry->eax, ACTOR_UPDATE_HOOK), entry->edx);
}

uint32_t vertrix_port_actor_last_frame(PORT_SIGNATURE)
{
    Port port;
    uint32_t frames;
    port_open(&port, calls, services, globals, entry);
    frames = port_call(&port, RESOURCE_FRAMES, port_u32(&port, entry->eax, ACTOR_RESOURCE_DATA),
                       port_u32(&port, entry->eax, ACTOR_FRAME_INDEX) + 1, entry->ebx, entry->ecx);
    return port_return(&port, vertrix_lift_edx == frames, entry->edx);
}

uint32_t vertrix_port_layer_top_update(PORT_SIGNATURE)
{
    return layer_call(calls, services, globals, entry, 0x54676c, LAYER_UPDATE);
}

/* 0x45cf30 and 0x45d160: the frame routine, then when the counter is due `due` and the update. */
static uint32_t frame_then(PORT_SIGNATURE, uint32_t frame, uint32_t due, uint32_t next)
{
    Port port;
    uint32_t actor = entry->eax;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    port_call(&port, frame, actor, entry->edx, entry->ebx, actor);
    port_call(&port, ACTOR_COUNTER_ADVANCE, actor, vertrix_lift_edx, entry->ebx, actor);
    result = port_call(&port, ACTOR_COUNTER_DUE, actor, vertrix_lift_edx, entry->ebx, actor);
    if (result != 1)
    {
        return port_return(&port, result, entry->edx);
    }
    port_call(&port, due, actor, next, entry->ebx, actor);
    result = port_call(&port, ACTOR_SET_UPDATE, actor, vertrix_lift_edx, entry->ebx, actor);
    return port_return(&port, result, entry->edx);
}

uint32_t vertrix_port_title_actor_wait(PORT_SIGNATURE)
{
    return frame_then(calls, services, globals, entry, TITLE_RUN, ACTOR_STEPS_CONSUME,
                      TITLE_WAIT_NEXT);
}

uint32_t vertrix_port_wanderer_wait(PORT_SIGNATURE)
{
    return frame_then(calls, services, globals, entry, ACTOR_WANDER, ACTOR_COUNTER_RESET,
                      WANDERER_NEXT);
}

uint32_t vertrix_port_actor_first_frame(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    return port_return(&port, port_u32(&port, entry->eax, ACTOR_FRAME_INDEX) == 0, entry->edx);
}

uint32_t vertrix_port_actor_set_update(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    port_set32(&port, entry->eax, ACTOR_UPDATE_HOOK, entry->edx);
    return port_return(&port, entry->eax, entry->edx);
}

uint32_t vertrix_port_actor_frame_back(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    port_set32(&port, entry->eax, ACTOR_FRAME_INDEX,
               port_u32(&port, entry->eax, ACTOR_FRAME_INDEX) - 1);
    return port_return(&port, entry->eax, entry->edx);
}

uint32_t vertrix_port_actor_frame_image(PORT_SIGNATURE)
{
    Port port;
    uint32_t actor = entry->eax;
    uint32_t resource;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    resource = port_u32(&port, actor, ACTOR_RESOURCE_DATA);
    if (resource == 0)
    {
        return port_return(&port, actor, entry->edx);
    }
    result = port_call(&port, RESOURCE_LOADED, resource, resource, entry->ebx, actor);
    if (result != 1)
    {
        return port_return(&port, result, entry->edx);
    }
    result = port_call(&port, RESOURCE_FRAME, port_u32(&port, actor, ACTOR_RESOURCE_DATA),
                       port_u32(&port, actor, ACTOR_FRAME_INDEX), entry->ebx, actor);
    port_set32(&port, actor, ACTOR_COUNTER_LIMIT, result);
    return port_return(&port, result, entry->edx);
}
