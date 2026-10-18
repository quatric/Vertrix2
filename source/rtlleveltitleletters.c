#include "rtlleveltitleletters.h"

/* The level title: each line of the level's title is centred on the 640 x 480 screen, 0x32
 * apart, and each letter is an actor 0x23 apart that arrives in the level's style (0 to 12).
 * Then 80 sparkles, and on levels 7 and 8 two more actors. */

enum
{
    BELOW = 0x8c, /* the locals, down to the exception record at ebp - 0x88 */
    TEXT = 0x60,  /* the line's string */
    WIDTH = 0x5c, /* its size, from 0x440610 */
    HEIGHT = 0x58,
    TARGET_X = 0x18, /* from 0x4ad260 */
    TARGET_Y = 0x1c,

    STRING_INIT = 0x4ca070,
    STRING_COPY = 0x4ca310,
    STRING_UPPER = 0x4ca710,
    STRING_RELEASE = 0x4ca210,
    MEASURE = 0x440610,
    ALLOCATE = 0x4ca000,
    CONSTRUCT = 0x4abd70,
    INITIALISE = 0x4adf20,
    RANDOM = 0x4826c0,
    GLYPH = 0x43f420,
    SET_IMAGE = 0x4ac950,
    START = 0x4ac810,
    SET_SPEED = 0x4ac7d0,
    SET_ARRIVAL = 0x4ac910,
    SET_UPDATE = 0x4ac8f0,
    SET_SPRITES = 0x4ac8d0,
    SET_KIND = 0x4ac710,
    START_ANIMATION = 0x4ac8a0,
    SET_LAYER = 0x4ac7b0,
    SET_FRAMES = 0x4ac470,
    START_FADE = 0x4ac7e0,
    START_PATH = 0x4ac510,
    SET_ORBIT = 0x4ad510,
    ORBIT_ANGLE = 0x484680,
    ORBIT_START = 0x484700,
    ORBIT_POINT = 0x4ad260,
    REGISTER = 0x4b5e70,

    TITLE_ACTORS = 0x546744,
    RANDOM_STATE = 0x598d30,
    LEVEL = 0x532a64,
    STYLES = 0x4f9b50,   /* each level's letter style */
    ARRIVALS = 0x4f9ba0, /* each level's arrival (0 to 6) */
    LINE_COUNTS = 0x53bd0c,
    LINES = 0x53bdfc,      /* nine line strings a level */
    TITLE_FONT = 0x54001e, /* a byte */

    SCREEN_WIDTH = 0x280,
    SCREEN_HEIGHT = 0x1e0,
    LEFT = 0xffce, /* -0x32, off the left edge */
    RIGHT = 0x2b2,
    BOTTOM = 0x212,
    LETTER_STEP = 0x23,
    LINE_STEP = 0x32
};

/* The routines an arriving letter runs, for arrivals 1 to 6 (0 is 0x4589e0, others none). */
static const uint32_t ARRIVAL_HANDLERS[7] = {0x4589e0, 0x458410, 0x458d40, 0x458f00,
                                             0x4590a0, 0x459200, 0x458490};

typedef struct
{
    Port *port;
    uint32_t frame;
    uint32_t x, y;   /* where the letter ends up */
    uint32_t index;  /* in the line */
    uint32_t half;   /* the line's length / 2 */
    uint32_t parity; /* the line's number & 1 */
    uint32_t count;  /* letters so far, for styles 4 and 7 */
    uint32_t offset; /* index - half */
} Title;

static uint32_t random_below(Port *port, uint32_t range)
{
    return port_call(port, RANDOM, RANDOM_STATE, range, 0, 0) & 0xffff;
}

static uint32_t sword(Port *port, uint32_t actor, uint32_t offset)
{
    return (uint32_t)(int32_t)(int16_t)port_u16(port, actor, offset);
}

static uint32_t text(Title *t)
{
    return port_u32(t->port, t->frame - TEXT, 0);
}

static void initialise(Port *port, uint32_t actor, uint32_t handler)
{
    const uint32_t stack[5] = {0, 0, 0, handler, 0};
    port_call_stack(port, INITIALISE, actor, 0, 0, 0, stack, 5);
}

/* The letter's image: character `shown` in a random one of two looks. */
static void glyph(Port *port, uint32_t actor, uint32_t shown)
{
    port_set32(port, actor, 0x58, shown);
    port_set32(port, actor, 0x64, random_below(port, 2));
    const uint32_t look = (uint32_t)(int32_t)(int8_t)port_u8(port, actor, 0x64);
    const uint32_t image = port_call(port, GLYPH, look, port_u8(port, actor, 0x58), 0, 0);
    port_call(port, SET_IMAGE, actor, image, 0, 0);
}

/* A letter actor at its place, started with `edx` (what 0x4ac810 leaves for the next call). */
static void letter(Title *t, uint32_t actor, uint32_t handler, uint32_t edx)
{
    Port *port = t->port;
    initialise(port, actor, handler);
    glyph(port, actor, port_u8(port, text(t), t->index));
    port_set32(port, actor, 0xd4, 0x64);
    port_set16(port, actor, 8, t->x);
    port_set16(port, actor, 0xa, t->y);
    port_set32(port, actor, 0xd8, 0x64);
    port_call(port, START, actor, edx, 0, 0);
    port_set16(port, actor, 0xc, 0);
}

/* A flight from (+0xe, +0x16) to the letter's place in `steps` steps a way. */
static void fly(Title *t, uint32_t actor, uint32_t steps_x, uint32_t steps_y)
{
    Port *port = t->port;
    port_set16(port, actor, 0x10, t->x);
    port_set16(port, actor, 0x18, t->y);
    port_set16(port, actor, 8, port_u16(port, actor, 0xe));
    port_set16(port, actor, 0xa, port_u16(port, actor, 0x16));
    port_set16(port, actor, 0x12, steps_x);
    port_set16(port, actor, 0x1a, steps_y);
    port_call(port, SET_SPEED, actor, 0xa, 0, 0);
}

/* fly() with as many steps as the distance needs, `scale` per screen. */
static void fly_by_distance(Title *t, uint32_t actor, int32_t scale)
{
    Port *port = t->port;
    port_set16(port, actor, 0x10, t->x);
    port_set16(port, actor, 0x18, t->y);
    port_set16(port, actor, 8, port_u16(port, actor, 0xe));
    port_set16(port, actor, 0xa, port_u16(port, actor, 0x16));
    int32_t dx = (int32_t)sword(port, actor, 0x10) - (int32_t)sword(port, actor, 8);
    int32_t dy = (int32_t)sword(port, actor, 0x18) - (int32_t)sword(port, actor, 0xa);
    dx = dx < 0 ? -dx : dx;
    dy = dy < 0 ? -dy : dy;
    if (dx > SCREEN_WIDTH)
    {
        dx = SCREEN_WIDTH;
    }
    if (dy > SCREEN_HEIGHT)
    {
        dy = SCREEN_HEIGHT;
    }
    fly(t, actor, (uint32_t)(dx * scale / SCREEN_WIDTH + 1),
        (uint32_t)(dy * scale / SCREEN_HEIGHT + 1));
}

/* The end of a flight: shown, with a random wobble. */
static void landed(Port *port, uint32_t actor)
{
    port_set8(port, actor, 0x95, 4);
    port_set8(port, actor, 0x93, 1);
    port_set8(port, actor, 0x44, 0);
    port_set32(port, actor, 0x80, 0);
    const uint32_t wobble = random_below(port, 5);
    port_set8(port, actor, 0x8c, 0);
    port_set32(port, actor, 0x88, wobble + 1);
}

/* Styles 5, 6 and 10: circling in from the letter's place. */
static void orbit(Title *t, uint32_t actor, uint32_t radius)
{
    Port *port = t->port;
    letter(t, actor, 0x4585c0, radius);
    port_set16(port, actor, 0xe, t->x);
    port_set16(port, actor, 0x16, t->y);
    port_set16(port, actor, 0xc, 0);
    port_call(port, SET_ORBIT, actor, vertrix_lift_edx, sword(port, actor, 8),
              sword(port, actor, 0xa));
    port_set16(port, actor, 0x30, radius);
}

static void orbit_end(Port *port, uint32_t actor, uint32_t turns)
{
    port_set32(port, actor, 0x70, 0);
    port_set32(port, actor, 0x74, 1);
    port_set32(port, actor, 0x78, 1);
    port_set16(port, actor, 0x32, turns);
    port_call(port, SET_SPEED, actor, 0xa, 0, 0);
    port_call(port, START_PATH, actor, 0, 0, 0);
    port_set16(port, actor, 0x48, 0x96);
    port_set16(port, actor, 0x4a, 0);
    port_set16(port, actor, 0x4c, 1);
}

/* Styles 7 and 9: growing in place after `delay`. */
static void grow(Title *t, uint32_t actor, uint32_t delay)
{
    Port *port = t->port;
    port_call(port, SET_SPEED, actor, vertrix_lift_edx, 0, 0);
    port_call(port, SET_SPEED, actor, delay, 0, 0);
    port_set8(port, actor, 0x44, 0);
    port_set8(port, actor, 0x45, 0x10);
    port_set16(port, actor, 0x46, 1);
}

static void style(Title *t, uint32_t actor, uint32_t kind)
{
    Port *port = t->port;
    switch (kind)
    {
        case 0: /* from a random edge */
        {
            letter(t, actor, 0x458150, 4);
            const uint32_t edge = random_below(port, vertrix_lift_edx);
            if (edge == 0)
            {
                const uint32_t x = random_below(port, SCREEN_WIDTH);
                port_set16(port, actor, 0x16, LEFT);
                port_set16(port, actor, 0xe, x);
            }
            else if (edge == 1)
            {
                port_set16(port, actor, 0xe, LEFT);
                port_set16(port, actor, 0x16, random_below(port, SCREEN_HEIGHT));
            }
            else if (edge == 2)
            {
                const uint32_t x = random_below(port, SCREEN_WIDTH);
                port_set16(port, actor, 0x16, BOTTOM);
                port_set16(port, actor, 0xe, x);
            }
            else if (edge == 3)
            {
                port_set16(port, actor, 0xe, RIGHT);
                port_set16(port, actor, 0x16, random_below(port, SCREEN_HEIGHT));
            }
            fly_by_distance(t, actor, 5);
            landed(port, actor);
            break;
        }
        case 1: /* from the left or right, level with its place */
        {
            letter(t, actor, 0x458150, 2);
            const uint32_t side = random_below(port, vertrix_lift_edx);
            if (side < 2)
            {
                port_set16(port, actor, 0xe, side == 0 ? LEFT : RIGHT);
                port_set16(port, actor, 0x16, t->y);
            }
            fly_by_distance(t, actor, 10);
            landed(port, actor);
            break;
        }
        case 2: /* up from the bottom */
            letter(t, actor, 0x458150, 0);
            port_set16(port, actor, 0x16, BOTTOM);
            port_set16(port, actor, 0xe, t->x);
            fly(t, actor, 8, 8);
            landed(port, actor);
            break;
        case 3: /* even lines from the left, odd from the right */
            letter(t, actor, 0x458150, 0);
            port_set16(port, actor, 0xe, t->parity == 0 ? LEFT : RIGHT);
            port_set16(port, actor, 0x16, t->y);
            fly(t, actor, 6, 6);
            landed(port, actor);
            break;
        case 4: /* from below, the left, above and the right in turn */
        {
            letter(t, actor, 0x458150, 0);
            port_set16(port, actor, 0xe, t->x);
            port_set16(port, actor, 0x16, t->y);
            switch (t->count & 3)
            {
                case 0:
                    port_set16(port, actor, 0x16, t->y - BOTTOM);
                    break;
                case 1:
                    port_set16(port, actor, 0xe, t->x - RIGHT);
                    break;
                case 2:
                    port_set16(port, actor, 0x16, t->y + BOTTOM);
                    break;
                default:
                    port_set16(port, actor, 0xe, t->x + RIGHT);
                    break;
            }
            fly(t, actor, 8, 8);
            landed(port, actor);
            t->count++;
            break;
        }
        case 5: /* circling in */
            orbit(t, actor, 0xa0);
            port_set16(port, actor, 0x24, 0);
            port_set16(port, actor, 0x28, random_below(port, 8) + 3);
            orbit_end(port, actor, 1);
            port_call(port, SET_SPEED, actor, 0xa, 0, 0);
            port_set8(port, actor, 0x44, 0);
            break;
        case 6: /* circling in either way */
            orbit(t, actor, 0xa0);
            port_set16(port, actor, 0x24, 0);
            port_set16(port, actor, 0x28, random_below(port, 8) + 3);
            if (random_below(port, 2) == 0)
            {
                port_set16(port, actor, 0x24, 0xb4);
                port_set16(port, actor, 0x28, 0 - port_u16(port, actor, 0x28));
            }
            orbit_end(port, actor, 1);
            port_call(port, SET_SPEED, actor, 0xa, 0, 0);
            port_set8(port, actor, 0x44, 0);
            break;
        case 7: /* growing one after another */
            letter(t, actor, 0x458710, 0x28);
            grow(t, actor, 2 * t->count + 0xa);
            t->count++;
            break;
        case 8: /* the first half from the left, the rest from the right */
            letter(t, actor, 0x458150, 0);
            port_set16(port, actor, 0xe, t->index <= t->half ? t->x - 0x172 : t->x + 0x172);
            port_set16(port, actor, 0x16, t->y);
            fly(t, actor, 8, 8);
            landed(port, actor);
            break;
        case 9: /* growing out from the middle */
        {
            letter(t, actor, 0x458710, 0);
            const int32_t offset = (int32_t)t->offset;
            const uint32_t distance = (uint32_t)(offset < 0 ? -offset : offset);
            port_call(port, SET_SPEED, actor, 0x28, 0, 0);
            port_call(port, SET_SPEED, actor, distance * 8 + 0xa, 0, 0);
            port_set8(port, actor, 0x44, 0);
            port_set8(port, actor, 0x45, 0x10);
            port_set16(port, actor, 0x46, 1);
            break;
        }
        case 10: /* circling in from a random angle */
            orbit(t, actor, 0x140);
            port_set16(port, actor, 0x24, random_below(port, 0x168));
            port_set16(port, actor, 0x28, 4);
            orbit_end(port, actor, 3);
            port_set8(port, actor, 0x44, 0);
            break;
        case 11: /* a space that becomes the letter */
        {
            Port *p = port;
            initialise(p, actor, 0x4587a0);
            port_set32(p, actor, 0x5c, port_u8(p, text(t), t->index));
            glyph(p, actor, 0x20);
            port_set32(p, actor, 0xd4, 0x64);
            port_set16(p, actor, 8, t->x);
            port_set16(p, actor, 0xa, t->y);
            port_set32(p, actor, 0xd8, 0x64);
            port_call(p, START, actor, 0, 0, 0);
            port_set16(p, actor, 0xc, 0);
            port_set32(p, actor, 0x70, 0);
            port_set16(p, actor, 0xe, t->x);
            port_set32(p, actor, 0x74, 0x32);
            port_set16(p, actor, 0x16, t->y);
            port_set32(p, actor, 0x78, 1);
            port_call(p, SET_SPEED, actor, random_below(p, 0x14) + 0xa, 0, 0);
            port_call(p, START_PATH, actor, 0, 0, 0);
            break;
        }
        case 12: /* spiralling in from the screen's centre */
        {
            initialise(port, actor, 0x458880);
            glyph(port, actor, port_u8(port, text(t), t->index));
            port_set8(port, actor, 0x52, random_below(port, 0xd));
            port_set16(port, actor, 8, t->x);
            port_set16(port, actor, 0xa, t->y);
            port_set16(port, actor, 0x10, t->x);
            port_set16(port, actor, 0x18, t->y);
            const uint32_t cx = SCREEN_WIDTH / 2, cy = SCREEN_HEIGHT / 2;
            const uint32_t radius = port_call(port, ORBIT_ANGLE, cx, cy, sword(port, actor, 8),
                                              sword(port, actor, 0xa));
            port_call(port, SET_ORBIT, actor, (uint32_t)(int32_t)(int16_t)radius, cx, cy);
            const uint32_t angle = port_call(port, ORBIT_START, cx, cy, sword(port, actor, 8),
                                             sword(port, actor, 0xa));
            port_set16(port, actor, 0x24, (int32_t)(angle & 0xffff) % 0x168);
            port_set16(port, actor, 0x28, 0);
            port_set16(port, actor, 0x2a, 0x240);
            port_set16(port, actor, 0x30, radius);
            port_set16(port, actor, 0x32, 0x50);
            port_call(port, ORBIT_POINT, actor, t->frame - TARGET_X, t->frame - TARGET_Y, 0x168);
            port_set32(port, actor, 0x70, 0);
            port_set32(port, actor, 0x74, 6);
            port_set32(port, actor, 0x78, 1);
            port_call(port, SET_SPEED, actor, 0xa, 0, 0);
            port_set32(port, actor, 0xd4, 0x64);
            port_set32(port, actor, 0xd8, 0x64);
            port_call(port, START, actor, 0, 0, 0);
            port_set16(port, actor, 0xc, 0);
            const uint32_t x = port_u32(port, t->frame - TARGET_X, 0);
            const uint32_t y = port_u32(port, t->frame - TARGET_Y, 0);
            port_set16(port, actor, 0xe, x);
            port_set16(port, actor, 0x16, y);
            port_set16(port, actor, 8, x);
            port_set16(port, actor, 0xa, y);
            port_call(port, START_PATH, actor, 0, 0, 0);
            break;
        }
        default: /* nothing but the arrival */
            break;
    }
}

static void sparkle(Port *port)
{
    uint32_t actor = port_call(port, ALLOCATE, 0x15c, 0, 0, 0);
    if (actor != 0)
    {
        actor = port_call(port, CONSTRUCT, actor, 0, 0, 0);
    }
    initialise(port, actor, 0);
    port_set16(port, actor, 0xe, random_below(port, SCREEN_WIDTH));
    port_set16(port, actor, 0x16, random_below(port, SCREEN_HEIGHT));
    port_call(port, SET_SPRITES, actor, 0x544c48, 0, 0);
    port_call(port, SET_KIND, actor, 0, 0, 0);
    port_call(port, START_ANIMATION, actor, 3, 0, 0);
    port_call(port, SET_LAYER, actor, random_below(port, vertrix_lift_edx) + 1, 0, 0);
    port_call(port, SET_FRAMES, actor, random_below(port, 0xa) + 2, 0, 0);
    port_set32(port, actor, 0xc4, 0x3e8);
    port_set32(port, actor, 0xc8, 0x3e8);
    port_call(port, START_FADE, actor, 0, 0, 0);
    port_set8(port, actor, 0x93, 1);
    port_set8(port, actor, 0x4e, 0);
    port_set32(port, actor, 0x58, 0);
    port_set32(port, actor, 0x5c, 1);
    port_call(port, SET_UPDATE, actor, 0x4597e0, 0, 0);
    port_set8(port, actor, 0x95, 4);
    port_call(port, REGISTER, TITLE_ACTORS, actor, 0, 0);
}

/* Levels 7 and 8's extra actor `which` (0 or 1). */
static void extra(Port *port, uint32_t level, uint32_t which)
{
    uint32_t actor = port_call(port, ALLOCATE, 0x15c, 0, 0, 0);
    if (actor != 0)
    {
        actor = port_call(port, CONSTRUCT, actor, 0, 0, 0);
    }
    initialise(port, actor, 0);
    port_set16(port, actor, 0xe, 0x14);
    port_set16(port, actor, 0x16, 0x14);
    port_call(port, SET_SPRITES, actor, 0x5464e4, 0, 0);
    port_set32(port, actor, 0x64, (level == 7 ? 0 : 4) + which);
    port_set32(port, actor, 0x68, level == 7 ? 4 : 8);
    port_call(port, SET_KIND, actor, port_u32(port, actor, 0x64), 0, 0);
    port_call(port, START_ANIMATION, actor, 1, 0, 0);
    port_call(port, SET_LAYER, actor, vertrix_lift_edx, 0, 0);
    port_call(port, SET_FRAMES, actor, 1 + which, 0, 0);
    port_set8(port, actor, 0x93, which);
    port_set8(port, actor, 0x4e, which == 0 ? 0x64 : 0);
    port_set16(port, actor, 0x50, 1);
    port_set32(port, actor, 0x60, 1);
    port_call(port, SET_UPDATE, actor, which == 0 ? 0x459a30 : 0x459b00, 0, 0);
    port_set8(port, actor, 0x95, 1);
    port_call(port, SET_ARRIVAL, actor, 0x4599e0, 0, 0);
    if (which == 1)
    {
        port_set32(port, actor, 0x58, 0);
    }
    port_call(port, REGISTER, TITLE_ACTORS, actor, 0, 0);
}

uint32_t vertrix_port_level_title_letter_actors_46f440(PORT_SIGNATURE)
{
    Port port;
    uint8_t stack[BELOW + 8];
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    Title t = {&port, entry->esp - 4, 0, 0, 0, 0, 0, 0, 0};
    const uint32_t frame = t.frame;

    const uint32_t level = port_u32(&port, LEVEL, 0);
    port_call(&port, STRING_INIT, frame - TEXT, 0, 0, 0);
    const uint32_t kind = port_u32(&port, STYLES + 4 * level, 0);
    const uint32_t arrival = port_u32(&port, ARRIVALS + 4 * level, 0);
    const uint32_t first_count = port_u32(&port, LINE_COUNTS + 4 * level, 0);
    t.y = ((SCREEN_HEIGHT - (first_count * 50 - 0x14)) >> 1) + 0xf;
    uint32_t line = LINES + 36 * level;
    for (uint32_t number = 0; number < port_u32(&port, LINE_COUNTS + 4 * level, 0);
         number++, line += 4, t.y += LINE_STEP)
    {
        port_call(&port, STRING_COPY, frame - TEXT, line, 0, 0);
        port_call(&port, STRING_UPPER, frame - TEXT, 0, 0, 0);
        const uint32_t length = port_u32(&port, text(&t), (uint32_t)-8);
        const uint32_t font = (uint32_t)(int32_t)(int8_t)port_u8(&port, TITLE_FONT, 0);
        const uint32_t size[1] = {frame - HEIGHT};
        port_call_stack(&port, MEASURE, font, text(&t), 0x10, frame - WIDTH, size, 1);
        t.x = ((SCREEN_WIDTH - port_u32(&port, frame - WIDTH, 0) + 1) >> 1) + 0x11;
        t.parity = number & 1;
        t.half = length >> 1;
        t.offset = 0 - t.half;
        for (t.index = 0; t.index < length; t.index++, t.x += LETTER_STEP, t.offset++)
        {
            uint32_t actor = port_call(&port, ALLOCATE, 0x15c, 0, 0, 0);
            if (actor != 0)
            {
                actor = port_call(&port, CONSTRUCT, actor, 0, 0, 0);
            }
            style(&t, actor, kind);
            port_call(&port, SET_ARRIVAL, actor, arrival <= 6 ? ARRIVAL_HANDLERS[arrival] : 0, 0,
                      0);
            port_call(&port, REGISTER, TITLE_ACTORS, actor, 0, 0);
        }
    }

    for (unsigned i = 0; i < 0x50; i++)
    {
        sparkle(&port);
    }
    if (level == 7 || level == 8)
    {
        extra(&port, level, 0);
        extra(&port, level, 1);
    }
    port_call(&port, STRING_RELEASE, frame - TEXT, 0, 0, 0);
    return port_return(&port, port.env.chain, vertrix_lift_edx);
}
