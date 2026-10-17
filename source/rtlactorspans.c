#include "rtlactorspans.h"

/* Sets up the blit globals at 0x5bb7xx for painting an actor onto the target surface: the
 * actor's rectangle, scaled and offset, clipped to the surface (or the actor's own box), and the
 * address of its first pixel. */

enum
{
    /* The actor's fields. */
    ACTOR_X = 0xe,
    ACTOR_Y = 0x16,
    ACTOR_OFFSET_Y = 0x1e,
    ACTOR_SHADE = 0x44,
    ACTOR_TINT_SIZE = 0x48,
    ACTOR_TINT = 0x52,
    ACTOR_FLAGS = 0x80,
    ACTOR_ALPHA = 0x8c,
    ACTOR_CLIP = 0x8e,
    ACTOR_SHADE_MAP = 0x91,
    ACTOR_TINT_MAP = 0x92,
    ACTOR_BLEND = 0x94,
    ACTOR_BOX = 0xa8,
    ACTOR_HIDDEN = 0xb4,
    ACTOR_WIDTH = 0xf4,
    ACTOR_HEIGHT = 0xf8,
    ACTOR_IMAGE = 0x13c,

    /* The surface at 0x5bc010. */
    TARGET = 0x5bc010,
    SURFACE_WIDTH = 0x4,
    SURFACE_HEIGHT = 0x8,
    SURFACE_BYTES = 0xc,
    SURFACE_KIND = 0xd,
    SURFACE_PITCH = 0x14,
    SURFACE_PIXELS = 0x18,

    /* The view at 0x544070. */
    VIEW = 0x544070,
    VIEW_WIDTH = 0x208,
    VIEW_HEIGHT = 0x20c,
    VIEW_LEFT = 0x214,
    VIEW_TOP = 0x216,
    VIEW_DEPTH = 0x226,
    VIEW_SHADE_OFF = 0x220,
    VIEW_SHADE = 0x221,
    VIEW_TINT_OFF = 0x222,
    VIEW_TINT_SIZE = 0x223,
    VIEW_TINT = 0x224,
    VIEW_TINT_MAP = 0x26c,
    VIEW_SHADE_MAP = 0x270,

    /* The blit globals. */
    HIDDEN = 0x5bb734,
    BYTES = 0x5bb732,
    KIND = 0x5bb733,
    START_X = 0x5bb7a4,
    START_Y = 0x5bb7a6,
    MAP_X = 0x5bb740,
    MAP_Y = 0x5bb742,
    MAP_WIDTH = 0x5bb744,
    MAP_HEIGHT = 0x5bb746,
    MAP_CELL = 0x5bb73c,
    LEFT = 0x5bb7a0,
    TOP = 0x5bb7a2,
    OFFSET_Y = 0x5bb7ae,
    WIDTH = 0x5bb7b4,
    HEIGHT = 0x5bb7b6,
    CLIP = 0x5bbffe,
    ZERO = 0x5bb739,
    SKIP = 0x5bb790,
    FOUR = 0x5bb731,
    BLEND = 0x5bc00c,
    ALPHA = 0x5bb73a,
    HUNDRED = 0x5bc00e,
    FLAGS = 0x5bb7b8,
    THIRTEEN = 0x5bb730,
    SHADE = 0x5bb738,
    SCALED = 0x5bb70c,
    TINT = 0x5bc000,
    TINT_SIZE = 0x5bc002,
    TINT_CELL = 0x5bc004,
    SPAN_WIDTH = 0x5bb74c,
    SPAN_HEIGHT = 0x5bb74e,
    CLIP_WIDTH = 0x5bb750,
    CLIP_HEIGHT = 0x5bb752,
    RIGHT = 0x5bb748,
    BOTTOM = 0x5bb74a,
    FIRST_TOP = 0x5bbff4,
    FIRST_LEFT = 0x5bbff2,
    BOX_LEFT = 0x5bbff6,
    BOX_RIGHT = 0x5bbff8,
    BOX_TOP = 0x5bbffa,
    BOX_BOTTOM = 0x5bbffc,
    CLIPPED = 0x5bc014,
    TARGET_WIDTH = 0x5bb798,
    TARGET_STRIDE = 0x5bb7bc,
    TARGET_PITCH = 0x5bb7c4,
    ROW_GAP = 0x5bb794,
    ROW_GAP_BYTES = 0x5bb7c8,
    PIXEL_32 = 0x5bb768,
    PIXEL_32_COPY = 0x5bb770,
    PIXEL_16 = 0x5bb780,
    PIXEL_16_COPY = 0x5bb784,
    PIXEL_8 = 0x5bb778,
    PIXEL_8_COPY = 0x5bb77c,

    /* The scale table: 16 rows of 16 remainders. */
    SCALE_TABLE = 0x5c1b00,

    PIXEL_ADDRESS = 0x478eb0,
    SET_BOX = 0x4ae110
};

static uint32_t g8(Port *port, uint32_t address)
{
    return port_u8(port, address, 0);
}

static uint32_t g16(Port *port, uint32_t address)
{
    return port_u16(port, address, 0);
}

static int32_t s16(Port *port, uint32_t address)
{
    return (int16_t)port_u16(port, address, 0);
}

static uint32_t g32(Port *port, uint32_t address)
{
    return port_u32(port, address, 0);
}

static void set8(Port *port, uint32_t address, uint32_t value)
{
    port_set8(port, address, 0, value);
}

static void set16(Port *port, uint32_t address, uint32_t value)
{
    port_set16(port, address, 0, value);
}

static void set32(Port *port, uint32_t address, uint32_t value)
{
    port_set32(port, address, 0, value);
}

/* 0x4ae110 with the actor's box: x, y, width in registers, height on the stack. */
static void set_box(Port *port, uint32_t actor, uint32_t x, uint32_t y, uint32_t width,
                    uint32_t height)
{
    const uint32_t stack[1] = {height};
    port_call_stack(port, SET_BOX, actor, x, y, width, stack, 1);
}

/* The view's map (0x544070's +0x26c or +0x270): the byte at the map cell 0x5bb73c. */
static uint32_t map_cell(Port *port, uint32_t view, uint32_t field)
{
    return g8(port, g32(port, g32(port, view + field)) + g32(port, MAP_CELL));
}

/* In the view (mode 0): the map size and the rectangle moved by the view's corner and depth. */
static void place_in_view(Port *port)
{
    const uint32_t view = g32(port, VIEW);
    set16(port, MAP_WIDTH, port_u16(port, view, VIEW_WIDTH));
    set16(port, MAP_HEIGHT, port_u16(port, view, VIEW_HEIGHT));
    set16(port, LEFT, g16(port, LEFT) - port_u16(port, view, VIEW_LEFT));
    set16(port, TOP, g16(port, TOP) - port_u16(port, view, VIEW_TOP));
    set16(port, OFFSET_Y, g16(port, OFFSET_Y) + port_u16(port, view, VIEW_DEPTH));
}

/* The map cell under the actor's start: a negative coordinate becomes 0, one past the map's
 * size its size less 1 (a map of size 0 or less keeps the 0). */
static void clamp_map(Port *port)
{
    if (s16(port, MAP_X) < 0)
    {
        set16(port, MAP_X, 0);
    }
    else if (s16(port, MAP_X) >= s16(port, MAP_WIDTH))
    {
        set16(port, MAP_X, g16(port, MAP_WIDTH) - 1);
    }
    if (s16(port, MAP_Y) < 0)
    {
        set16(port, MAP_Y, 0);
    }
    else if (s16(port, MAP_Y) >= s16(port, MAP_HEIGHT))
    {
        set16(port, MAP_Y, g16(port, MAP_HEIGHT) - 1);
    }
    set32(port, MAP_CELL, (uint32_t)(s16(port, MAP_WIDTH) * s16(port, MAP_Y) + s16(port, MAP_X)));
}

/* The shade (0x5bb738): the actor's, or in the view with a shade map the view's shade or its map
 * cell + 1. */
static uint32_t shade_of(Port *port, uint32_t actor, uint32_t mode)
{
    if (mode == 1 || port_u8(port, actor, ACTOR_SHADE_MAP) == 0)
    {
        return port_u8(port, actor, ACTOR_SHADE);
    }
    const uint32_t view = g32(port, VIEW);
    if (port_u8(port, view, VIEW_SHADE_OFF) == 0)
    {
        return port_u8(port, view, VIEW_SHADE);
    }
    return (map_cell(port, view, VIEW_SHADE_MAP) + 1) & 0xff;
}

/* The tint (0x5bc000) and its size (0x5bc002): the actor's, the view's, or from the view's map
 * cell (tint the cell's top five bits, size its low three less 5, times 0x28 or, below 0, 0x14). */
static void tint(Port *port, uint32_t actor, uint32_t mode)
{
    if (mode == 1 || port_u8(port, actor, ACTOR_TINT_MAP) == 0)
    {
        set8(port, TINT, port_u8(port, actor, ACTOR_TINT));
        set16(port, TINT_SIZE, port_u16(port, actor, ACTOR_TINT_SIZE));
        return;
    }
    const uint32_t view = g32(port, VIEW);
    if (port_u8(port, view, VIEW_TINT_OFF) == 0)
    {
        set16(port, TINT_SIZE, (uint32_t)(int8_t)port_u8(port, view, VIEW_TINT_SIZE));
        set8(port, TINT, port_u8(port, view, VIEW_TINT));
        return;
    }
    set8(port, TINT_CELL, map_cell(port, view, VIEW_TINT_MAP));
    const uint32_t cell = g8(port, TINT_CELL);
    set8(port, TINT, cell >> 3);
    const int32_t size = (int8_t)((cell & 7) - 5);
    set16(port, TINT_SIZE, (uint32_t)size);
    set16(port, TINT_SIZE, (uint32_t)(size * (size < 0 ? 0x14 : 0x28)));
}

/* A scaled size: (size >> 4) * shade plus the table's entry for the shade and size & 15. */
static uint32_t scaled(Port *port, uint32_t size, uint32_t shade)
{
    return (size >> 4) * shade + g8(port, SCALE_TABLE + shade * 16 + (size & 0xf));
}

/* The clip box: the target surface's or (clip mode 3) the actor's; other modes keep it. */
static void clip_box(Port *port, uint32_t actor, uint32_t clip)
{
    if (clip == 0 || clip == 1)
    {
        const uint32_t surface = g32(port, TARGET);
        set16(port, BOX_LEFT, 0);
        set16(port, BOX_TOP, 0);
        set16(port, BOX_RIGHT, port_u16(port, surface, SURFACE_WIDTH) - 1);
        set16(port, BOX_BOTTOM, port_u16(port, surface, SURFACE_HEIGHT) - 1);
    }
    else if (clip == 3)
    {
        set16(port, BOX_LEFT, port_u16(port, actor, ACTOR_BOX));
        set16(port, BOX_RIGHT, port_u16(port, actor, ACTOR_BOX + 2));
        set16(port, BOX_TOP, port_u16(port, actor, ACTOR_BOX + 4));
        set16(port, BOX_BOTTOM, port_u16(port, actor, ACTOR_BOX + 6));
    }
}

/* Clips the rectangle to the box, skipping the source rows and columns cut off the top and left
 * (unscaled only); sets 0x5bc014 when it cut anything. */
static void clip_rectangle(Port *port)
{
    const int unscaled = g32(port, SCALED) == 0;
    if (s16(port, TOP) < s16(port, BOX_TOP))
    {
        if (unscaled)
        {
            set32(port, SKIP,
                  g32(port, SKIP) +
                      (uint32_t)(s16(port, BOX_TOP) - s16(port, TOP)) * s16(port, SPAN_WIDTH));
        }
        set16(port, TOP, g16(port, BOX_TOP));
        set8(port, CLIPPED, 1);
    }
    if (s16(port, LEFT) < s16(port, BOX_LEFT))
    {
        if (unscaled)
        {
            set32(port, SKIP, g32(port, SKIP) + (uint32_t)(s16(port, BOX_LEFT) - s16(port, LEFT)));
        }
        set16(port, LEFT, g16(port, BOX_LEFT));
        set8(port, CLIPPED, 1);
    }
    if (s16(port, BOTTOM) > s16(port, BOX_BOTTOM))
    {
        set16(port, BOTTOM, g16(port, BOX_BOTTOM));
        set8(port, CLIPPED, 1);
    }
    if (s16(port, RIGHT) > s16(port, BOX_RIGHT))
    {
        set16(port, RIGHT, g16(port, BOX_RIGHT));
        set8(port, CLIPPED, 1);
    }
}

/* The first pixel's address on the target surface (0x478eb0), kept by its byte depth. */
static void first_pixel(Port *port, uint32_t surface)
{
    const uint32_t bytes = g8(port, BYTES);
    uint32_t slot, copy;
    if (bytes == 4)
    {
        slot = PIXEL_32;
        copy = PIXEL_32_COPY;
    }
    else if (bytes == 2)
    {
        slot = PIXEL_16;
        copy = PIXEL_16_COPY;
    }
    else if (bytes == 1)
    {
        slot = PIXEL_8;
        copy = PIXEL_8_COPY;
    }
    else
    {
        return;
    }
    const uint32_t pixel = port_call(port, PIXEL_ADDRESS, surface, (uint32_t)s16(port, LEFT),
                                     (uint32_t)s16(port, TOP), 0);
    set32(port, slot, pixel);
    set32(port, copy, pixel);
}

/* Original 0x4b17e0 (eax = the actor, edx = the mode: 0 in the view, 1 on screen). Returns 0
 * when the actor is hidden (+0xb4), there is no target surface or it is of kind 3, the rectangle
 * is empty or (clip modes 0, 1, 3) outside the clip box; otherwise sets up the blit and returns
 * 1. An actor without an image (+0x13c) has its box (0x4ae110) set to zero first and to the
 * clipped rectangle at the end. */
static uint32_t paint(Port *port, uint32_t actor, uint32_t mode)
{
    if (port_u32(port, actor, ACTOR_IMAGE) == 0)
    {
        set_box(port, actor, 0, 0, 0, 0);
    }
    const uint32_t hidden = port_u32(port, actor, ACTOR_HIDDEN);
    set32(port, HIDDEN, hidden);
    if (hidden != 0)
    {
        return 0;
    }
    const uint32_t target = g32(port, TARGET);
    if (target == 0)
    {
        return 0;
    }
    set8(port, BYTES, port_u8(port, target, SURFACE_BYTES));
    set8(port, KIND, port_u8(port, target, SURFACE_KIND));
    if (port_u8(port, target, SURFACE_KIND) == 3)
    {
        return 0;
    }

    set16(port, START_X, port_u16(port, actor, ACTOR_X));
    set16(port, MAP_X, port_u16(port, actor, ACTOR_X));
    set16(port, START_Y, port_u16(port, actor, ACTOR_Y));
    set16(port, MAP_Y, port_u16(port, actor, ACTOR_Y));
    set16(port, LEFT, g16(port, START_X));
    set16(port, TOP, g16(port, START_Y));
    set16(port, OFFSET_Y, port_u16(port, actor, ACTOR_OFFSET_Y));
    set16(port, WIDTH, port_u16(port, actor, ACTOR_WIDTH));
    set16(port, HEIGHT, port_u16(port, actor, ACTOR_HEIGHT));
    set8(port, CLIP, port_u8(port, actor, ACTOR_CLIP));
    set8(port, ZERO, 0);
    set32(port, SKIP, 0);
    set8(port, FOUR, 4);
    set8(port, BLEND, port_u8(port, actor, ACTOR_BLEND));
    set8(port, ALPHA, port_u8(port, actor, ACTOR_ALPHA));
    set8(port, HUNDRED, 0x64);
    set8(port, FLAGS, port_u8(port, actor, ACTOR_FLAGS));
    if (mode == 0)
    {
        place_in_view(port);
    }
    set8(port, THIRTEEN, 0xd);
    if (mode == 0)
    {
        clamp_map(port);
    }

    set8(port, SHADE, shade_of(port, actor, mode));
    set32(port, SCALED, g8(port, SHADE) != 0x10);
    tint(port, actor, mode);

    if (g32(port, SCALED) != 0)
    {
        const uint32_t shade = g8(port, SHADE);
        set16(port, SPAN_WIDTH, scaled(port, g16(port, WIDTH), shade));
        set16(port, SPAN_HEIGHT, scaled(port, g16(port, HEIGHT), shade));
    }
    else
    {
        set16(port, SPAN_WIDTH, g16(port, WIDTH));
        set16(port, SPAN_HEIGHT, g16(port, HEIGHT));
    }
    const uint32_t width = g16(port, SPAN_WIDTH);
    const uint32_t height = g16(port, SPAN_HEIGHT);
    if (width == 0 || height == 0)
    {
        return 0;
    }

    const uint32_t top = g16(port, TOP) - g16(port, OFFSET_Y);
    set16(port, CLIP_WIDTH, width);
    set16(port, RIGHT, g16(port, LEFT) + g16(port, SPAN_WIDTH) - 1);
    set16(port, CLIP_HEIGHT, height);
    set16(port, TOP, top);
    set16(port, FIRST_TOP, top);
    set16(port, BOTTOM, top + height - 1);
    set16(port, FIRST_LEFT, g16(port, LEFT));

    const uint32_t clip = g8(port, CLIP);
    if (clip != 2)
    {
        clip_box(port, actor, clip);
        if (s16(port, LEFT) > s16(port, BOX_RIGHT) || s16(port, RIGHT) < s16(port, BOX_LEFT) ||
            s16(port, TOP) > s16(port, BOX_BOTTOM) || s16(port, BOTTOM) < s16(port, BOX_TOP))
        {
            return 0;
        }
    }
    set8(port, CLIPPED, 0);
    if (g8(port, CLIP) != 2)
    {
        clip_rectangle(port);
    }
    if (g8(port, CLIPPED) != 0)
    {
        set16(port, CLIP_WIDTH, g16(port, RIGHT) - g16(port, LEFT) + 1);
        set16(port, CLIP_HEIGHT, g16(port, BOTTOM) - g16(port, TOP) + 1);
        if (g16(port, CLIP_WIDTH) == 0 || g16(port, CLIP_HEIGHT) == 0)
        {
            return 0;
        }
    }

    const uint32_t surface = g32(port, TARGET);
    set16(port, TARGET_WIDTH, port_u16(port, surface, SURFACE_WIDTH));
    set32(port, TARGET_STRIDE, (uint32_t)s16(port, TARGET_WIDTH));
    const uint32_t gap = (uint32_t)(s16(port, TARGET_WIDTH) - s16(port, CLIP_WIDTH));
    set32(port, TARGET_PITCH, port_u32(port, surface, SURFACE_PITCH));
    set32(port, ROW_GAP, gap);
    set32(port, ROW_GAP_BYTES, g8(port, BYTES) * gap + port_u32(port, surface, SURFACE_PIXELS));
    first_pixel(port, surface);

    if (port_u32(port, actor, ACTOR_IMAGE) == 0)
    {
        set_box(port, actor, (uint32_t)s16(port, LEFT), (uint32_t)s16(port, TOP),
                (uint32_t)s16(port, CLIP_WIDTH), (uint32_t)s16(port, CLIP_HEIGHT));
    }
    return 1;
}

uint32_t vertrix_port_actor_paint_span_4b17e0(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    const uint32_t result = paint(&port, entry->eax, entry->edx);
    return port_return(&port, result, 0);
}
