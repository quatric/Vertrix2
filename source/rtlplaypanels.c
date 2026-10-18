#include "rtlplaypanels.h"

enum
{
    /* Actor sizes and constructors: a sprite (0x160, 0x4b5400), a text (0x180, 0x4b6350) and an
     * indicator (0x15c, 0x4abd70). */
    SPRITE_SIZE = 0x160,
    TEXT_SIZE = 0x180,
    INDICATOR_SIZE = 0x15c,
    SPRITE_CONSTRUCT = 0x4b5400,
    TEXT_CONSTRUCT = 0x4b6350,
    INDICATOR_CONSTRUCT = 0x4abd70,

    /* Actor fields: level (+0x44), depth (+0x48, 16 bits), angle (+0x4e), frame (+0x52), shown
     * (+0x93), drawn (+0x94), layer (+0x95) and tinted (+0x110). */
    ACTOR_LEVEL = 0x44,
    ACTOR_DEPTH = 0x48,
    ACTOR_ANGLE = 0x4e,
    ACTOR_FRAME = 0x52,
    ACTOR_SHOWN = 0x93,
    ACTOR_DRAWN = 0x94,
    ACTOR_LAYER = 0x95,
    ACTOR_TINTED = 0x110,

    ACTORS = 0x54671c,
    BAR_WIDTH = 0x280,
    FRAME_BAR = 8,
    MODE_DEFAULT = 2,
    TINT_DARK = 0xff000000u,
    TINT_CELL = 0x7f,
    BAR_START = 0xffffffe2u,
    BAR_STEP = 6,
    SECOND_BAR_STEP = 7,
    ROWS = 7,
    COLUMNS = 4,
    CELL_INSET = 4,
    CELL_MARGIN = 2,
    INDICATOR_OFFSET = 5,
    TEXT_FONT = 0x4479f0,
    INDICATOR_IMAGE = 0x544a18,

    /* The bars' counts and rows, the title's and texts' strings and the modes. */
    BAR_COUNT = 0x4f86d4,
    BAR_ROW = 0x533d30,
    SECOND_BAR_COUNT = 0x4f870c,
    SECOND_BAR_ROW = 0x4f8708,
    TITLE_MODE = 0x532a84,
    PANEL_MODE = 0x532a8c,
    TITLE_STRING = 0x50e506,
    SURFACE = 0x558c7c,

    ALLOCATE = 0x4ca000,
    ACTOR_INIT = 0x4adf20,
    ACTOR_PLACE = 0x4b54d0,
    ACTOR_MODE = 0x4ac7b0,
    ACTOR_TINT = 0x4ac4e0,
    ACTOR_ADD = 0x4b5e70,
    TEXT_SET = 0x4b65d0,
    ACTOR_FLIP = 0x4ac910,
    ACTOR_IMAGE = 0x4ac8d0,
    ACTOR_SET_LEVEL = 0x4ac710,
    ACTOR_REFRESH = 0x4ac8a0,
    MARKER_MAKE = 0x465a70
};

/* A panel: its place (x and y as the high words of two dwords, width and height words), depth,
 * frame (0 for none), drawn and tinted flags. */
typedef struct
{
    uint32_t x;
    uint32_t y;
    uint32_t width;
    uint32_t height;
    uint32_t depth;
    uint32_t frame;
    uint32_t drawn;
    uint32_t tinted;
} Panel;

/* A text: its string, place (x as a dword's high word, left and width words to add, height as a
 * dword's high word). */
typedef struct
{
    uint32_t string;
    uint32_t x;
    uint32_t left;
    uint32_t width;
    uint32_t height;
} Text;

/* An indicator: its place (half of a size dword plus an origin dword, each axis), the offset added
 * to both, its level's global and its depth (0 for none), layer and angle. */
typedef struct
{
    uint32_t width;
    uint32_t x;
    uint32_t height;
    uint32_t y;
    uint32_t offset;
    uint32_t level;
    uint32_t depth;
    uint32_t layer;
    uint32_t angle;
} Indicator;

static uint32_t u32(Port *port, uint32_t address)
{
    return port_u32(port, address, 0);
}

static uint32_t high_word(Port *port, uint32_t address)
{
    return (uint32_t)((int32_t)port_u32(port, address, 0) >> 16);
}

/* Allocates an actor and constructs it, or 0 when the allocation fails. */
static uint32_t make(Port *port, uint32_t size, uint32_t constructor)
{
    const uint32_t memory = port_call(port, ALLOCATE, size, 0, 0, 0);
    return memory != 0 ? port_call(port, constructor, memory, 0, 0, 0) : 0;
}

/* 0x4adf20 (ecx = 0; stdcall: five arguments, the fourth `fourth`). */
static void init(Port *port, uint32_t actor, uint32_t x, uint32_t y, uint32_t fourth)
{
    const uint32_t args[5] = {0, 0, 0, fourth, 0};
    port_call_stack(port, ACTOR_INIT, actor, x, y, 0, args, 5);
}

static void place(Port *port, uint32_t actor, uint32_t x, uint32_t y, uint32_t width,
                  uint32_t height)
{
    const uint32_t args[1] = {height};
    port_call_stack(port, ACTOR_PLACE, actor, x, y, width, args, 1);
}

static void add(Port *port, uint32_t actor)
{
    port_call(port, ACTOR_ADD, ACTORS, actor, 0, 0);
}

/* A bar piece (0x465b49): row `row`, depth `depth`, frame 8, drawn on layer 1 untinted. */
static void bar(Port *port, uint32_t row, uint32_t depth)
{
    const uint32_t actor = make(port, SPRITE_SIZE, SPRITE_CONSTRUCT);
    init(port, actor, 0, 0, 0);
    place(port, actor, 0, (uint32_t)(int32_t)(int16_t)row, BAR_WIDTH, 1);
    port_set8(port, actor, ACTOR_FRAME, FRAME_BAR);
    port_set16(port, actor, ACTOR_DEPTH, depth);
    port_call(port, ACTOR_MODE, actor, MODE_DEFAULT, 0, 0);
    port_set8(port, actor, ACTOR_DRAWN, 1);
    port_set8(port, actor, ACTOR_LAYER, 1);
    port_set8(port, actor, ACTOR_TINTED, 0);
    add(port, actor);
}

/* The bar pieces of a count (`count` global) on rows from `row`: the first half with depths from
 * -30 rising by `step`, the rest falling again. */
static void bars(Port *port, uint32_t count_global, uint32_t row_global, uint32_t step)
{
    const uint32_t count = u32(port, count_global);
    const uint32_t half = count >> 1;
    uint32_t depth = BAR_START;
    for (uint32_t i = 0; i < half && !port->env.failed; i++)
    {
        bar(port, port_u16(port, row_global, 0) + i, depth);
        depth += step;
    }
    const uint32_t rest = u32(port, count_global) - half;
    for (uint32_t i = 0; i < rest && !port->env.failed; i++)
    {
        bar(port, port_u16(port, row_global, 0) + half + i, depth);
        depth -= step;
    }
}

/* A panel (0x465d34): placed, its depth set, mode 2, then its frame when it has one, drawn,
 * layer 1, tinted as given and darkened (0x4ac4e0). */
static void panel(Port *port, uint32_t actor, const Panel *p)
{
    init(port, actor, 0, 0, 0);
    place(port, actor, high_word(port, p->x), high_word(port, p->y), port_u16(port, p->width, 0),
          port_u16(port, p->height, 0));
    port_set16(port, actor, ACTOR_DEPTH, p->depth);
    port_call(port, ACTOR_MODE, actor, MODE_DEFAULT, 0, 0);
    if (p->frame != 0)
    {
        port_set8(port, actor, ACTOR_FRAME, p->frame);
    }
    port_set8(port, actor, ACTOR_DRAWN, p->drawn);
    port_set8(port, actor, ACTOR_LAYER, 1);
    port_set8(port, actor, ACTOR_TINTED, p->tinted);
    port_call(port, ACTOR_TINT, actor, TINT_DARK, 0, 0);
    add(port, actor);
}

/* A grid cell (0x4660d0): at (x, y), the cell's size less 4, depth 0, frame 8, drawn, layer 1,
 * tinted 0x7f. */
static void cell(Port *port, uint32_t x, uint32_t y)
{
    const uint32_t actor = make(port, SPRITE_SIZE, SPRITE_CONSTRUCT);
    init(port, actor, 0, 0, 0);
    place(port, actor, (uint32_t)(int32_t)(int16_t)x, (uint32_t)(int32_t)(int16_t)y,
          (port_u16(port, 0x4f9060, 0) - CELL_INSET) & 0xffff,
          (port_u16(port, 0x4f9064, 0) - CELL_INSET) & 0xffff);
    port_set16(port, actor, ACTOR_DEPTH, 0);
    port_set8(port, actor, ACTOR_FRAME, FRAME_BAR);
    port_call(port, ACTOR_MODE, actor, MODE_DEFAULT, 0, 0);
    port_set8(port, actor, ACTOR_DRAWN, 1);
    port_set8(port, actor, ACTOR_LAYER, 1);
    port_set8(port, actor, ACTOR_TINTED, 1);
    port_call(port, ACTOR_TINT, actor, TINT_CELL, 0, 0);
    add(port, actor);
}

/* A text (0x466748): the font's fourth init argument, the string at (x, y) with the height twice
 * and the width (left + width - 1) on the stack, mode 2, level 8, shown, layer 4. */
static void text(Port *port, const Text *t)
{
    const uint32_t actor = make(port, TEXT_SIZE, TEXT_CONSTRUCT);
    init(port, actor, 0, 0, TEXT_FONT);
    const uint32_t height = high_word(port, t->height);
    const uint32_t width =
        (uint32_t)(int32_t)(int16_t)(port_u16(port, t->left, 0) + port_u16(port, t->width, 0) - 1);
    const uint32_t args[3] = {width, height, height};
    port_call_stack(port, TEXT_SET, actor, t->string,
                    (uint32_t)((int32_t)u32(port, 0x540018) >> 24), high_word(port, t->x), args, 3);
    port_call(port, ACTOR_MODE, actor, MODE_DEFAULT, 0, 0);
    port_set8(port, actor, ACTOR_LEVEL, 8);
    port_set8(port, actor, ACTOR_SHOWN, 1);
    port_set8(port, actor, ACTOR_LAYER, 4);
    add(port, actor);
}

/* An indicator (0x466936): placed at half its size plus its origin (and the offset), its image
 * and level set and refreshed, shown, its layer, angle and depth. */
static void indicator(Port *port, const Indicator *n)
{
    const uint32_t actor = make(port, INDICATOR_SIZE, INDICATOR_CONSTRUCT);
    const uint32_t x = n->offset + (u32(port, n->width) >> 1) + u32(port, n->x);
    const uint32_t y = (u32(port, n->height) >> 1) + u32(port, n->y) + n->offset;
    const uint32_t args[5] = {0, 0, 0, 0, 0};
    port_call_stack(port, ACTOR_INIT, actor, (uint32_t)(int32_t)(int16_t)x,
                    (uint32_t)(int32_t)(int16_t)y, 0, args, 5);
    port_call(port, ACTOR_IMAGE, actor, INDICATOR_IMAGE, 0, 0);
    port_call(port, ACTOR_SET_LEVEL, actor, u32(port, n->level), 0, 0);
    port_call(port, ACTOR_REFRESH, actor, 0, 0, 0);
    port_set8(port, actor, ACTOR_SHOWN, 1);
    port_set8(port, actor, ACTOR_LAYER, n->layer);
    port_set8(port, actor, ACTOR_ANGLE, n->angle);
    if (n->depth != 0)
    {
        port_set16(port, actor, ACTOR_DEPTH, n->depth);
    }
    add(port, actor);
}

static const Panel PANELS_ONE[5] = {
    {0x4f85e6, 0x4f85ea, 0x4f85f8, 0x4f85fc, 0xf, 8, 1, 1},
    {0x4f85ee, 0x4f85f2, 0x4f85f8, 0x4f85fc, 0xf, 0xb, 1, 1},
    {0x4f86d6, 0x4f86da, 0x4f86e0, 0x4f86e4, 0xfff6, 9, 1, 1},
    {0x4f86f6, 0x4f86fa, 0x4f8700, 0x4f8704, 0xfff6, 9, 1, 1},
    {0x4f86e6, 0x4f86ea, 0x4f86f0, 0x4f86f4, 0xfff6, 9, 1, 1},
};

static const Panel PANELS_TWO[3] = {
    {0x4f85e6, 0x4f85a2, 0x4f85f8, 0x4f85a8, 0xfff6, 0, 1, 0},
    {0x4f85ee, 0x4f85a2, 0x4f85f8, 0x4f85a8, 0xfff6, 0, 1, 0},
    {0x4f8606, 0x4f85a2, 0x4f8610, 0x4f85a8, 0xfff6, 0, 1, 0},
};

static const Panel PANELS_THREE[2] = {
    {0x4f86c2, 0x4f86c6, 0x4f86cc, 0x4f86d0, 0xffdd, 0, 0, 1},
    {0x4f86b2, 0x4f86b6, 0x4f86bc, 0x4f86c0, 0xffdd, 0, 1, 1},
};

static const Text TEXTS[3] = {
    {0x50e518, 0x4f870e, 0x4f8710, 0x4f8718, 0x4f8712},
    {0x50e51c, 0x533d32, 0x533d34, 0x4f8724, 0x4f871e},
    {0x50e522, 0x4f872a, 0x4f872c, 0x4f8734, 0x4f872e},
};

static const Indicator INDICATORS[4] = {
    {0x4f85b0, 0x533d20, 0x4f85b4, 0x4f85ac, INDICATOR_OFFSET, 0x4fbf1c, 0xffd8, 1, 0},
    {0x4f85c0, 0x4f85b8, 0x4f85c4, 0x4f85bc, INDICATOR_OFFSET, 0x4fbf20, 0xffd8, 1, 0},
    {0x4f85b0, 0x533d20, 0x4f85b4, 0x4f85ac, 0, 0x4fbf1c, 0, 0, 0x5a},
    {0x4f85c0, 0x4f85b8, 0x4f85c4, 0x4f85bc, 0, 0x4fbf20, 0, 0, 0x5a},
};

/* The markers (0x465a70: x, y and colour globals; x and y moved by 5). */
static const uint32_t MARKERS[9][3] = {
    {0x4f8618, 0x4f861c, 0x4fbed0}, {0x4f8620, 0x4f8624, 0x4fbed8}, {0x4f8628, 0x4f862c, 0x4fbee0},
    {0x4f8648, 0x4f864c, 0x4fbf00}, {0x4f8650, 0x4f8654, 0x4fbf08}, {0x4f8658, 0x4f865c, 0x4fbf10},
    {0x4f8630, 0x4f8634, 0x4fbed0}, {0x4f8638, 0x4f863c, 0x4fbed8}, {0x4f8640, 0x4f8644, 0x4fbee0},
};

/* Original 0x465af0: builds the play screen's actors, each added to the actor list 0x54671c. The
 * bar pieces, the title text when no title mode is set (0x532a84), five panels, a 7 x 4 grid of
 * paired cells (at the grid's two origins, stepping by the cell size and gap), three more panels,
 * the second bar, then (panel mode 0x532a8c 0 or 1) two panels and three texts, the four
 * indicators and the nine markers. The exception frame at fs:[0] and its state word are left out
 * (docs/NATIVE-PORTS.md); no caller reads eax or edx. */
uint32_t vertrix_port_rtl_play_panels_465af0(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    bars(&port, BAR_COUNT, BAR_ROW, BAR_STEP);
    if (u32(&port, TITLE_MODE) == 0)
    {
        const uint32_t actor = make(&port, TEXT_SIZE, TEXT_CONSTRUCT);
        init(&port, actor, 0, 0, 0);
        const uint32_t height = high_word(&port, 0x4f869e);
        const uint32_t width =
            (uint32_t)(int32_t)(int16_t)(port_u16(&port, u32(&port, SURFACE), 4) - 1);
        const uint32_t args[3] = {width, height, height};
        port_call_stack(&port, TEXT_SET, actor, TITLE_STRING,
                        (uint32_t)((int32_t)u32(&port, 0x4f9bfd) >> 24), 0, args, 3);
        port_call(&port, ACTOR_MODE, actor, MODE_DEFAULT, 0, 0);
        port_set8(&port, actor, ACTOR_LEVEL, 0x10);
        port_set8(&port, actor, ACTOR_ANGLE, 0x32);
        port_set8(&port, actor, ACTOR_DRAWN, 1);
        port_set8(&port, actor, ACTOR_LAYER, 4);
        port_set8(&port, actor, ACTOR_SHOWN, 1);
        port_set16(&port, actor, ACTOR_DEPTH, BAR_START);
        port_call(&port, ACTOR_FLIP, actor, 0, 0, 0);
        add(&port, actor);
    }
    for (unsigned i = 0; i < 5; i++)
    {
        panel(&port, make(&port, SPRITE_SIZE, SPRITE_CONSTRUCT), &PANELS_ONE[i]);
    }
    for (uint32_t row = 0; row < ROWS && !port.env.failed; row++)
    {
        for (uint32_t column = 0; column < COLUMNS && !port.env.failed; column++)
        {
            const uint32_t across = (u32(&port, 0x4f9060) + u32(&port, 0x4f8668)) * column;
            const uint32_t down = (u32(&port, 0x4f9064) + u32(&port, 0x4f866c)) * row;
            cell(&port, across + u32(&port, 0x4f8660) + CELL_MARGIN,
                 down + u32(&port, 0x4f8664) + CELL_MARGIN);
            const uint32_t across_two = (u32(&port, 0x4f9060) + u32(&port, 0x4f8668)) * column;
            const uint32_t down_two = (u32(&port, 0x4f9064) + u32(&port, 0x4f866c)) * row;
            cell(&port, across_two + u32(&port, 0x4f8670) + CELL_MARGIN,
                 down_two + u32(&port, 0x4f8674) + CELL_MARGIN);
        }
    }
    for (unsigned i = 0; i < 3; i++)
    {
        panel(&port, make(&port, SPRITE_SIZE, SPRITE_CONSTRUCT), &PANELS_TWO[i]);
    }
    bars(&port, SECOND_BAR_COUNT, SECOND_BAR_ROW, SECOND_BAR_STEP);
    const uint32_t mode = u32(&port, PANEL_MODE);
    if (mode == 0 || mode == 1)
    {
        for (unsigned i = 0; i < 2; i++)
        {
            panel(&port, make(&port, SPRITE_SIZE, SPRITE_CONSTRUCT), &PANELS_THREE[i]);
        }
        for (unsigned i = 0; i < 3; i++)
        {
            text(&port, &TEXTS[i]);
        }
    }
    for (unsigned i = 0; i < 4; i++)
    {
        indicator(&port, &INDICATORS[i]);
    }
    for (unsigned i = 0; i < 9; i++)
    {
        port_call(&port, MARKER_MAKE, u32(&port, MARKERS[i][0]) + INDICATOR_OFFSET,
                  u32(&port, MARKERS[i][1]) + INDICATOR_OFFSET, u32(&port, MARKERS[i][2]), 0);
    }
    return port_return(&port, 0, 0);
}
