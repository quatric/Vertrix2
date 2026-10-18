#include "rtlboardselectscreens.h"

/* The board select screen: each player's board area with its cursor, player, frame and corner
 * marker, the keys each player picks with, the shared board, the screen's labels and switches,
 * and in a timed game the two panels and the start button. */

enum
{
    ALLOCATE = 0x4ca000,
    CONSTRUCT_ACTOR = 0x4abd70,
    CONSTRUCT_PANEL = 0x4b6350,
    CONSTRUCT_SWITCH = 0x429670,
    CONSTRUCT_TOGGLE = 0x4b5400,
    INITIALISE = 0x4adf20,
    SET_BOUNDS = 0x4b65d0,
    SET_CLIP = 0x4b6690,
    SET_LAYER = 0x4ac7b0,
    SET_ARRIVAL = 0x4ac910,
    SET_HIT_AREA = 0x4ae110,
    SET_SPEED = 0x4ac7d0,
    SET_SPRITES = 0x4ac8d0,
    SET_KIND = 0x4ac710,
    START_ANIMATION = 0x4ac8a0,
    SET_FRAMES = 0x4ac470,
    SET_FRAME = 0x4ac860,
    SET_TEXT_COLOUR = 0x4b6530,
    SET_SHADOW = 0x4b6540,
    SHADOW_OFF = 0x4b65b0,
    SET_SHADOW_Y = 0x4b6550,
    TOGGLE_PLACE = 0x4b54d0,
    SET_BORDER = 0x4ac4e0,
    SET_UPDATE = 0x4ac8f0,
    NEW_BUTTON = 0x4602a0,
    REGISTER = 0x4b5e70,
    IS_PAD_KEY = 0x476650,

    ACTORS = 0x54671c,
    NETWORKED = 0x532a7c,
    HOSTING = 0x532a80,
    TIMED = 0x532a84,
    SHARED = 0x532a8c,
    BIG_KEYS = 0x532b40,
    PLAYER_ONE = 0x532a68,
    PLAYER_TWO = 0x532a6c,
    ONE_READY = 0x5344a4, /* by player */
    TWO_READY = 0x5344f0,
    ONE_KEYS = 0x532b6c, /* four words */
    TWO_KEYS = 0x532b74,
    BACK_IMAGE = 0x558c7c,
    SHEET = 0x544a18,

    ONE_AREA = 0x4f85e8, /* x and y; both areas' width and height are at 0x4f85f8 */
    TWO_AREA = 0x4f85f0,
    AREA_SIZE = 0x4f85f8,
    BOARD = 0x4f8608, /* x, y, width and height */
    PANEL_HEIGHT = 0x4f86a4,
    SCREEN_WIDTH = 0x280
};

typedef struct
{
    Port *port;
    uint32_t first_keys[3], second_keys[3]; /* the key words each side's key actors hold */
    uint32_t first_flag, second_flag;       /* whether that side has no pad keys */
} Select;

static uint32_t word(uint32_t value)
{
    return (uint32_t)(int32_t)(int16_t)value;
}

static uint32_t at(Port *port, uint32_t address)
{
    return port_u16(port, address, 0);
}

static uint32_t colour(Port *port, uint32_t address)
{
    return (uint32_t)(int32_t)(int8_t)port_u8(port, address, 0);
}

static uint32_t new_actor(Port *port, uint32_t size, uint32_t construct)
{
    const uint32_t actor = port_call(port, ALLOCATE, size, 0, 0, 0);
    return actor != 0 ? port_call(port, construct, actor, 0, 0, 0) : 0;
}

static void initialise(Port *port, uint32_t actor, uint32_t x, uint32_t y, uint32_t handler)
{
    const uint32_t stack[5] = {0, 0, 0, handler, 0};
    port_call_stack(port, INITIALISE, actor, x, y, 0, stack, 5);
}

static void hit_area(Port *port, uint32_t actor, uint32_t x, uint32_t y, uint32_t width,
                     uint32_t height)
{
    const uint32_t stack[1] = {height};
    port_call_stack(port, SET_HIT_AREA, actor, x, y, width, stack, 1);
}

/* The bounds words of the rectangle at (x_at, y_at) of the size at size_at. */
static void bounds(Port *port, uint32_t actor, uint32_t x_at, uint32_t y_at, uint32_t size_at)
{
    const uint32_t x = at(port, x_at), y = at(port, y_at);
    port_set16(port, actor, 0xa8, x);
    port_set16(port, actor, 0xaa, x + at(port, size_at) - 1);
    port_set16(port, actor, 0xac, y);
    port_set16(port, actor, 0xae, y + at(port, size_at + 4) - 1);
}

/* Whether none of `count` keys is a pad key (0x476650), stopping at the first that is. The
 * last key is read from what the calls leave in edx, which starts as `edx`. */
static int no_pad_keys(Port *port, const uint32_t *keys, unsigned count, uint32_t edx,
                       int last_from_edx)
{
    for (unsigned i = 0; i < count; i++)
    {
        const uint32_t key = (i == count - 1 && last_from_edx) ? edx & 0xffff : keys[i];
        const int pad = port_call(port, IS_PAD_KEY, key, edx, 0, 0) == 1;
        edx = vertrix_lift_edx;
        if (pad)
        {
            return 0;
        }
    }
    return 1;
}

/* A timed game's panel `number`: the left (1) or right (2) half of the top. */
static void panel(Port *port, uint32_t number)
{
    const uint32_t actor = new_actor(port, 0x180, CONSTRUCT_PANEL);
    initialise(port, actor, 0, 0, 0x447af0);
    const uint32_t width = port_u32(port, port_u32(port, BACK_IMAGE, 0), 4);
    const uint32_t bottom = word(at(port, PANEL_HEIGHT) - 1);
    const uint32_t left = number == 1 ? 0 : word(width >> 1);
    const uint32_t right = number == 1 ? word((width >> 1) - 1) : word(width - 1);
    const uint32_t stack[3] = {right, 0, bottom};
    port_call_stack(port, SET_BOUNDS, actor, number == 1 ? 0x50e528 : 0x50e529,
                    colour(port, 0x54001a), left, stack, 3);
    port_call(port, SET_LAYER, actor, 2, 0, 0);
    port_set8(port, actor, 0x52, 9);
    port_set8(port, actor, 0x44, 9);
    port_set8(port, actor, 0x4e, 0);
    port_set8(port, actor, 0x93, 1);
    port_set32(port, actor, 4, number);
    port_call(port, SET_ARRIVAL, actor, 0, 0, 0);
    port_call(port, REGISTER, ACTORS, actor, 0, 0);
}

/* A player's board area at `area` (side 0 or 1): its cursor, player (kind 0x13 + side), frame
 * and corner marker. */
static void area(Port *port, uint32_t side, uint32_t area_at, const uint32_t handlers[3])
{
    const uint32_t x_at = area_at, y_at = area_at + 4;
    const uint32_t cx = word(port_u32(port, x_at, 0) + (port_u32(port, AREA_SIZE, 0) >> 1));
    const uint32_t cy = word(port_u32(port, y_at, 0) + (port_u32(port, AREA_SIZE + 4, 0) >> 1));

    uint32_t actor = new_actor(port, 0x15c, CONSTRUCT_ACTOR);
    initialise(port, actor, cx, cy, handlers[0]);
    port_call(port, SET_LAYER, actor, 8, 0, 0);
    port_set8(port, actor, 0x44, 0x10);
    port_set8(port, actor, 0x95, 4);
    port_set8(port, actor, 0x93, 1);
    port_set16(port, actor, 0x48, 0xff9c);
    port_call(port, SET_ARRIVAL, actor, 0, 0, 0);
    port_set8(port, actor, 0x8e, 3);
    bounds(port, actor, x_at, y_at, AREA_SIZE);
    if (side == 0)
    {
        port_set32(port, actor, 0x124, 1);
    }
    hit_area(port, actor, word(at(port, x_at)), word(at(port, y_at)), port_u32(port, AREA_SIZE, 0),
             port_u32(port, AREA_SIZE + 4, 0));
    if (side == 1)
    {
        port_set32(port, actor, 0x124, 1);
    }
    port_set16(port, actor, 0x148, side);
    port_call(port, REGISTER, ACTORS, actor, 0, 0);

    actor = new_actor(port, 0x15c, CONSTRUCT_ACTOR);
    initialise(port, actor, cx, cy, handlers[1]);
    port_set32(port, actor, 0, 0x13 + side);
    port_call(port, SET_LAYER, actor, 2, 0, 0);
    port_set8(port, actor, 0x44, 0x10);
    port_call(port, SET_ARRIVAL, actor, 0, 0, 0);
    port_set8(port, actor, 0x8e, 3);
    port_set32(port, actor, 0x150, 1);
    port_set32(port, actor, 0x138, 0);
    port_set32(port, actor, 0x124, 1);
    port_set16(port, actor, 0x148, side);
    bounds(port, actor, x_at, y_at, AREA_SIZE);
    port_call(port, REGISTER, ACTORS, actor, 0, 0);

    actor = new_actor(port, 0x15c, CONSTRUCT_ACTOR);
    initialise(port, actor, cx, cy, handlers[2]);
    port_call(port, SET_LAYER, actor, 2, 0, 0);
    port_call(port, SET_ARRIVAL, actor, 0, 0, 0);
    port_set8(port, actor, 0x8e, 3);
    port_set8(port, actor, 0x93, 1);
    port_set8(port, actor, 0x95, 0);
    port_set8(port, actor, 0x4e, 0x46);
    port_set32(port, actor, 0x138, 0);
    port_set32(port, actor, 0x124, 1);
    port_set16(port, actor, 0x148, side);
    bounds(port, actor, x_at, y_at, AREA_SIZE);
    port_call(port, REGISTER, ACTORS, actor, 0, 0);

    actor = new_actor(port, 0x15c, CONSTRUCT_ACTOR);
    initialise(port, actor, word(at(port, x_at)), word(at(port, y_at)), 0x44a610);
    port_call(port, SET_SPEED, actor, 0x64, 0, 0);
    port_call(port, SET_ARRIVAL, actor, 0, 0, 0);
    port_set8(port, actor, 0x93, 1);
    port_set8(port, actor, 0x95, 5);
    port_set8(port, actor, 0x4e, 0x32);
    port_call(port, SET_SPRITES, actor, SHEET, 0, 0);
    port_call(port, SET_KIND, actor, port_u32(port, 0x4fbf24, 0), 0, 0);
    port_call(port, START_ANIMATION, actor, 0, 0, 0);
    port_set32(port, actor, 0x138, 0);
    port_set32(port, actor, 0x124, 0);
    port_set32(port, actor, 0x58, port_u32(port, x_at, 0));
    port_set32(port, actor, 0x64, port_u32(port, y_at, 0));
    port_set16(port, actor, 0x148, side);
    port_call(port, REGISTER, ACTORS, actor, 0, 0);
}

/* A key picture at the position at `place`, showing `sprite`; the third of a set animates. */
static void key_picture(Port *port, uint32_t place, uint32_t sprite, int third)
{
    const uint32_t actor = new_actor(port, 0x15c, CONSTRUCT_ACTOR);
    initialise(port, actor, word(port_u32(port, place, 0)), word(port_u32(port, place + 4, 0)), 0);
    port_call(port, SET_LAYER, actor, 2, 0, 0);
    if (third)
    {
        port_call(port, SET_FRAMES, actor, 0xa, 0, 0);
    }
    port_call(port, SET_ARRIVAL, actor, 0, 0, 0);
    port_call(port, SET_SPRITES, actor, SHEET, 0, 0);
    port_call(port, SET_KIND, actor, port_u32(port, sprite, 0), 0, 0);
    port_call(port, START_ANIMATION, actor, 0, 0, 0);
    port_set8(port, actor, 0x52, 0);
    port_set8(port, actor, 0x94, 0);
    port_set32(port, actor, 0x124, 1);
    hit_area(port, actor, 0, 0, 0, 0);
    port_set32(port, actor, 0x13c, 0);
    port_call(port, REGISTER, ACTORS, actor, 0, 0);
}

/* A key button at `place` run by `handler`; with `key` set it holds that key and `flag`. */
static void key_button(Port *port, uint32_t place, uint32_t handler, int third, int holds,
                       uint32_t key, uint32_t flag)
{
    const uint32_t actor = new_actor(port, 0x15c, CONSTRUCT_ACTOR);
    initialise(port, actor, word(port_u32(port, place, 0)), word(port_u32(port, place + 4, 0)),
               handler);
    port_call(port, SET_LAYER, actor, 2, 0, 0);
    if (third)
    {
        port_call(port, SET_FRAMES, actor, 0xa, 0, 0);
    }
    port_call(port, SET_ARRIVAL, actor, 0, 0, 0);
    port_set32(port, actor, 0x124, 1);
    if (holds)
    {
        port_set32(port, actor, 0x64, key);
        port_set32(port, actor, 0x70, flag);
    }
    hit_area(port, actor, 0, 0, 0, 0);
    port_set32(port, actor, 0x13c, 0);
    port_call(port, REGISTER, ACTORS, actor, 0, 0);
}

typedef struct
{
    uint32_t place[3];   /* positions, in the order made */
    uint32_t sprite[3];  /* the pictures' sprites */
    uint32_t handler[2]; /* the first two buttons' handlers */
    uint32_t third[2];   /* the third's, with and without big keys */
} KeySet;

static const KeySet KEY_SETS[3] = {{{0x4f8618, 0x4f8628, 0x4f8620},
                                    {0x4fbed0, 0x4fbee0, 0x4fbed8},
                                    {0x449500, 0x449660},
                                    {0x449870, 0x4497c0}},
                                   {{0x4f8630, 0x4f8640, 0x4f8638},
                                    {0x4fbee8, 0x4fbef8, 0x4fbef0},
                                    {0x449aa0, 0x449c00},
                                    {0x449e10, 0x449d60}},
                                   {{0x4f8648, 0x4f8658, 0x4f8650},
                                    {0x4fbf00, 0x4fbf10, 0x4fbf08},
                                    {0x44a040, 0x44a170},
                                    {0x44a340, 0x44a2a0}}};

/* Key set `which`: pictures, or buttons (holding `keys` and `flag` when given). */
static void keys(Port *port, unsigned which, int pictures, const uint32_t *held, uint32_t flag)
{
    const KeySet *set = &KEY_SETS[which];
    for (unsigned i = 0; i < 3; i++)
    {
        if (pictures)
        {
            key_picture(port, set->place[i], set->sprite[i], i == 2);
        }
        else
        {
            const uint32_t handler =
                i < 2 ? set->handler[i] : set->third[port_u32(port, BIG_KEYS, 0) == 1 ? 0 : 1];
            key_button(port, set->place[i], handler, i == 2, held != NULL,
                       held != NULL ? held[i] : 0, flag);
        }
    }
}

/* The shared board and its title. */
static void board(Port *port)
{
    uint32_t actor = new_actor(port, 0x15c, CONSTRUCT_ACTOR);
    initialise(port, actor, word(port_u32(port, BOARD, 0)), word(port_u32(port, BOARD + 4, 0)),
               0x4492f0);
    port_call(port, SET_LAYER, actor, 2, 0, 0);
    port_call(port, SET_ARRIVAL, actor, 0, 0, 0);
    port_set8(port, actor, 0x8e, 3);
    port_set16(port, actor, 0x48, 0);
    port_set16(port, actor, 0x4a, 0);
    port_set16(port, actor, 0x4c, 1);
    bounds(port, actor, BOARD, BOARD + 4, BOARD + 8);
    port_set32(port, actor, 0x124, 1);
    hit_area(port, actor, 0, 0, 0, 0);
    port_set32(port, actor, 0x13c, 0);
    port_set32(port, actor, 0x7c, 0xffffffff);
    port_call(port, REGISTER, ACTORS, actor, 0, 0);
}

static void board_title(Port *port)
{
    const uint32_t actor = new_actor(port, 0x180, CONSTRUCT_PANEL);
    initialise(port, actor, 0, 0, 0x44a6d0);
    const uint32_t x = at(port, BOARD), y = at(port, BOARD + 4);
    const uint32_t right = word(x + at(port, BOARD + 8) - 1);
    const uint32_t bottom = word(y + at(port, BOARD + 0xc) - 1);
    const uint32_t stack[3] = {right, word(y), bottom};
    port_call_stack(port, SET_BOUNDS, actor, 0x50e52a, colour(port, 0x540018), word(x), stack, 3);
    port_call_stack(port, SET_CLIP, actor, word(x), right, word(y), &bottom, 1);
    port_call(port, SET_TEXT_COLOUR, actor, 8, 0, 0);
    port_call(port, SET_SHADOW, actor, 0xffffffb0, 0, 0);
    port_call(port, SHADOW_OFF, actor, 0xffffffb0, 0, 0);
    port_call(port, SET_SHADOW_Y, actor, vertrix_lift_edx, 0, 0);
    port_call(port, SET_LAYER, actor, 2, 0, 0);
    port_set8(port, actor, 0x44, 0);
    port_set8(port, actor, 0x93, 1);
    port_set8(port, actor, 0x4e, 0x32);
    port_set32(port, actor, 0x14c, port_u32(port, 0x4f7bb0, 0));
    port_set16(port, actor, 0x172, 1);

    /* Lit when hosting, or when the players are ready. */
    int lit = port_u32(port, HOSTING, 0) == 1;
    if (!lit)
    {
        const int two_ready = port_u32(port, TWO_READY + 4 * port_u32(port, PLAYER_TWO, 0), 0) == 1;
        if (port_u32(port, NETWORKED, 0) == 1)
        {
            lit = two_ready;
        }
        else
        {
            const int one_ready =
                port_u32(port, ONE_READY + 4 * port_u32(port, PLAYER_ONE, 0), 0) == 1;
            lit = two_ready || one_ready;
        }
    }
    port_set8(port, actor, 0x52, lit ? 1 : 0xd);
    port_set8(port, actor, 0x94, 0);
    port_set8(port, actor, 0x95, lit ? 0 : 1);
    port_call(port, SET_ARRIVAL, actor, 0, 0, 0);
    port_call(port, REGISTER, ACTORS, actor, 0, 0);
}

/* The two switches. */
static void switches(Port *port)
{
    for (unsigned i = 0; i < 2; i++)
    {
        const uint32_t place = i == 0 ? 0x4f8660 : 0x4f8670;
        const uint32_t actor = new_actor(port, 0x16c, CONSTRUCT_SWITCH);
        const uint32_t x = word(at(port, place)), y = word(at(port, place + 4));
        initialise(port, actor, x, y, i == 0 ? 0x44a570 : 0x44a5c0);
        if (i == 1)
        {
            port_set32(port, actor, 0x160, 0);
        }
        port_set32(port, actor, 0x164, port_u32(port, 0x4f8668, 0));
        port_set32(port, actor, 0x168, port_u32(port, 0x4f866c, 0));
        port_set32(port, actor, 0x124, 1);
        hit_area(port, actor, x, y, port_u32(port, 0x4f8678, 0), port_u32(port, 0x4f867c, 0));
        port_call(port, REGISTER, ACTORS, actor, 0, 0);
    }
}

/* A text in the label column at the row word at `row`, clickable over the top or bottom half of
 * the area at `hit`; `frame` is its first frame (0 for none). */
static void label(Port *port, uint32_t text, uint32_t handler, uint32_t row, uint32_t hit,
                  int bottom_half, uint32_t frame)
{
    const uint32_t actor = new_actor(port, 0x180, CONSTRUCT_PANEL);
    initialise(port, actor, 0, 0, handler);
    const uint32_t y = word(at(port, row));
    const uint32_t stack[3] = {word(at(port, 0x4f869c)), y, y};
    port_call_stack(port, SET_BOUNDS, actor, text, colour(port, 0x4f9c00), word(at(port, 0x4f8698)),
                    stack, 3);
    port_call(port, SET_LAYER, actor, 2, 0, 0);
    if (frame != 0)
    {
        port_call(port, SET_FRAME, actor, frame, 0, 0);
    }
    port_set8(port, actor, 0x44, 8);
    port_set8(port, actor, 0x4e, 0x32);
    if (frame != 0)
    {
        port_set32(port, actor, 0x7c, 0);
    }
    const uint32_t half = port_u32(port, hit + 0xc, 0) >> 1;
    const uint32_t top =
        bottom_half ? word(half + port_u32(port, hit + 4, 0)) : word(at(port, hit + 4));
    port_set32(port, actor, 0x124, 1);
    hit_area(port, actor, word(at(port, hit)), top, port_u32(port, hit + 8, 0), half);
    port_set8(port, actor, 0x93, 1);
    port_set8(port, actor, 0x4e, 0x5a);
    port_set8(port, actor, 0x95, 1);
    port_call(port, REGISTER, ACTORS, actor, 0, 0);
}

/* A heading over an area or the board. */
static void heading(Port *port, uint32_t text, uint32_t handler, uint32_t x_at, uint32_t width_at)
{
    const uint32_t actor = new_actor(port, 0x180, CONSTRUCT_PANEL);
    initialise(port, actor, 0, 0, handler);
    const uint32_t x = at(port, x_at), y = at(port, 0x4f85a4);
    const uint32_t stack[3] = {word(x + at(port, width_at) - 1), word(y),
                               word(y + at(port, 0x4f85a8) - 1)};
    port_call_stack(port, SET_BOUNDS, actor, text, colour(port, 0x540019), word(x), stack, 3);
    port_call(port, SET_LAYER, actor, 2, 0, 0);
    port_set8(port, actor, 0x44, 8);
    port_set32(port, actor, 0x124, 1);
    hit_area(port, actor, word(x), word(y), port_u32(port, width_at, 0),
             port_u32(port, 0x4f85a8, 0));
    port_set8(port, actor, 0x93, 1);
    port_set8(port, actor, 0x4e, 0x5a);
    port_set8(port, actor, 0x95, 1);
    port_call(port, REGISTER, ACTORS, actor, 0, 0);
}

/* A toggle at the rectangle at `rect`. */
static void toggle(Port *port, uint32_t rect, uint32_t update)
{
    const uint32_t actor = new_actor(port, 0x160, CONSTRUCT_TOGGLE);
    initialise(port, actor, 0, 0, 0);
    const uint32_t none[1] = {0};
    port_call_stack(port, TOGGLE_PLACE, actor, word(at(port, rect)), word(at(port, rect + 4)), 0,
                    none, 1);
    port_set16(port, actor, 0x48, 0xf);
    port_call(port, SET_LAYER, actor, 2, 0, 0);
    port_set8(port, actor, 0x94, 0);
    port_set8(port, actor, 0x95, 1);
    port_set8(port, actor, 0x110, 1);
    port_call(port, SET_BORDER, actor, 0xff000000, 0, 0);
    port_call(port, SET_UPDATE, actor, update, 0, 0);
    port_set32(port, actor, 0x124, 1);
    hit_area(port, actor, word(at(port, rect) - 2), word(at(port, rect + 4) - 2),
             port_u32(port, rect + 8, 0) + 4, port_u32(port, rect + 0xc, 0) + 4);
    port_set32(port, actor, 0x7c, 0xffffffff);
    port_call(port, REGISTER, ACTORS, actor, 0, 0);
}

static void start_button(Port *port)
{
    const uint32_t width = port_u32(port, 0x4f8734, 0) + 4;
    const uint32_t stack[6] = {0x50e536, 0x416970, colour(port, 0x540018), 8, 0, 1};
    const uint32_t button = port_call_stack(
        port, NEW_BUTTON, word((SCREEN_WIDTH - width) >> 1), word(at(port, 0x4f8730) - 6),
        word(at(port, 0x4f8734) + 4), word(at(port, 0x4f8738) + 0xc), stack, 6);
    port_set8(port, port_u32(port, button, 0x160), 0x52, 0);
    port_call(port, SET_ARRIVAL, button, 0, 0, 0);
    port_call(port, SET_UPDATE, button, 0x445d80, 0, 0);
    port_call(port, REGISTER, ACTORS, button, 0, 0);
}

uint32_t vertrix_port_board_select_screen_build_466d60(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    Select s = {&port, {0}, {0}, 0, 0};

    port_set32(&port, 0x532a9c, 0, 0);
    const uint32_t networked = port_u32(&port, NETWORKED, 0);
    const uint32_t hosting = port_u32(&port, HOSTING, 0);
    uint32_t one[4], two[4];
    for (unsigned i = 0; i < 4; i++)
    {
        one[i] = at(&port, ONE_KEYS + 2 * i);
        two[i] = at(&port, TWO_KEYS + 2 * i);
    }
    /* Which side's keys come first, and whether each side has only keyboard keys. */
    const int second_first = networked == 1 && hosting == 0;
    for (unsigned i = 0; i < 3; i++)
    {
        s.first_keys[i] = second_first ? two[i] : one[i];
        s.second_keys[i] = second_first ? one[i] : two[i];
    }
    if (networked == 0 && hosting == 1)
    {
        s.first_flag = no_pad_keys(&port, one, 4, vertrix_lift_edx, 0);
    }
    else if (second_first)
    {
        s.second_flag = no_pad_keys(&port, one, 4, one[3], 1);
    }
    else
    {
        s.first_flag = no_pad_keys(&port, one, 4, two[3], 0);
        s.second_flag = no_pad_keys(&port, two, 4, vertrix_lift_edx, 1);
    }

    if (port_u32(&port, TIMED, 0) == 1)
    {
        panel(&port, 1);
        panel(&port, 2);
    }
    static const uint32_t ONE_HANDLERS[3] = {0x448d30, 0x448c20, 0x449090};
    static const uint32_t TWO_HANDLERS[3] = {0x448ed0, 0x448ca0, 0x449180};
    area(&port, 0, ONE_AREA, ONE_HANDLERS);
    keys(&port, 0, port_u32(&port, NETWORKED, 0) == 1, s.first_keys, s.first_flag);
    area(&port, 1, TWO_AREA, TWO_HANDLERS);
    keys(&port, 1, port_u32(&port, SHARED, 0) == 0 || port_u32(&port, HOSTING, 0) == 1,
         s.second_keys, s.second_flag);
    board(&port);
    keys(&port, 2, port_u32(&port, SHARED, 0) == 0 || port_u32(&port, NETWORKED, 0) == 1, NULL, 0);
    board_title(&port);
    switches(&port);
    label(&port, 0x50e52d, 0x44aec0, 0x4f8680, 0x4f86d8, 0, 0x64);
    label(&port, 0x50e52e, 0x44b050, 0x4f8684, 0x4f86d8, 1, 0);
    label(&port, 0x50e52f, 0x44b170, 0x4f8690, 0x4f86e8, 0, 0x44c);
    label(&port, 0x50e530, 0x44b340, 0x4f8694, 0x4f86e8, 1, 0);
    label(&port, 0x50e531, 0x44b4a0, 0x4f8688, 0x4f86f8, 0, 0);
    label(&port, 0x50e532, 0x44b5d0, 0x4f868c, 0x4f86f8, 1, 0);
    heading(&port, 0x50e533, 0x44b6f0, ONE_AREA, AREA_SIZE);
    heading(&port, 0x50e534, 0x44b810, TWO_AREA, AREA_SIZE);
    heading(&port, 0x50e535, 0x44b980, BOARD, BOARD + 8);
    const uint32_t shared = port_u32(&port, SHARED, 0);
    if (shared == 0 || shared == 1)
    {
        toggle(&port, 0x4f86c4, 0x44bac0);
        toggle(&port, 0x4f86b4, 0x44bb30);
    }
    if (port_u32(&port, TIMED, 0) == 1)
    {
        start_button(&port);
    }
    return port_return(&port, port.env.chain, entry->edx);
}
