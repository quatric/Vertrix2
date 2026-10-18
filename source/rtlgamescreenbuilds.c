#include "rtlgamescreenbuilds.h"

/* The game screen's actors: the two boards and their previews, the arrows that show each
 * player's next moves, the scoreboards, counters and lights, the two drop queues and each
 * player's end-of-round actors. Called with the screen (eax) and each board's owner (edx, ebx). */

enum
{
    ALLOCATE = 0x4ca000,
    CONSTRUCT_BOARD = 0x43a6f0,
    CONSTRUCT_PREVIEW = 0x429880,
    CONSTRUCT_ARROW = 0x43d3f0,
    CONSTRUCT_ACTOR = 0x4abd70,
    CONSTRUCT_SCORE = 0x4b5580,
    CONSTRUCT_COUNTER = 0x42b150,
    CONSTRUCT_LIGHT = 0x43a160,
    INITIALISE = 0x4adf20,
    BOARD_SIDE = 0x43aab0,
    BOARD_RESET = 0x43bae0,
    BOARD_READY = 0x43ab30,
    PREVIEW_PLAYER = 0x429bf0,
    PREVIEW_READY = 0x42a200,
    PREVIEW_SHOW = 0x429d50,
    SET_TEXT = 0x4b5700,
    ATTACH = 0x4123d0,
    PLACE_CURSOR = 0x4710d0,
    PLACE = 0x471100,
    SET_LAYER = 0x4ac7b0,
    SET_DEPTH = 0x4adfa0,
    SET_UPDATE = 0x4ac8f0,
    SET_ARRIVAL = 0x4ac910,
    SET_HIT_AREA = 0x4ae110,
    SET_SPEED = 0x4ac7d0,
    SET_FRAME = 0x4ac860,
    SET_SPRITES = 0x4ac8d0,
    SET_KIND = 0x4ac710,
    START_ANIMATION = 0x4ac8a0,
    SET_FRAMES = 0x4ac470,
    SET_IMAGE = 0x4ac950,
    SCORE_VALUE = 0x4b58a0,
    COUNTER_SIDE = 0x42b370,
    LIGHT_PLACE = 0x43a310,
    LIGHT_COLOURS = 0x43a4f0,
    LIGHT_SPEED = 0x43a520,
    POINTER_PATH = 0x46e8b0,
    RANDOM = 0x4826c0,
    START_ROUND = 0x4726d0,
    REGISTER = 0x4b5e70,

    ACTORS = 0x54671c,
    RANDOM_STATE = 0x598d30,
    BOARDS = 0x540f88, /* by board number */
    NETWORKED = 0x532a7c,
    HOSTING = 0x532a80,
    ONE_HUMAN = 0x532a74,
    TWO_HUMAN = 0x532a78,
    PLAYER_ONE = 0x532a68,
    PLAYER_TWO = 0x532a6c,
    ONE_SCORE = 0x532aa4,
    TWO_SCORE = 0x532aa8,
    ONE_KEYS = 0x532b6c, /* four words */
    TWO_KEYS = 0x532b74,
    ARROW_RECT = 0x4f8a10,   /* the arrows' width and height */
    SCREEN_OFFSET = 0x533d70 /* x and y words added to the queues' positions */
};

typedef struct
{
    Port *port;
    uint32_t screen;
} Game;

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
    port_call_stack(port, SET_HIT_AREA, actor, x, y, width, &height, 1);
}

/* A text actor's rectangle from the words at x_at and y_at, of the size at size_at. */
static void text_box(Port *port, uint32_t actor, uint32_t edx, uint32_t paint, uint32_t x_at,
                     uint32_t y_at, uint32_t size_at)
{
    const uint32_t x = at(port, x_at), y = at(port, y_at);
    const uint32_t stack[3] = {word(x + at(port, size_at) - 1), word(y),
                               word(y + at(port, size_at + 4) - 1)};
    port_call_stack(port, SET_TEXT, actor, edx, paint, word(x), stack, 3);
}

/* Board `number` (1 or 2) for its player, with the keys it plays with. */
static uint32_t board(Game *g, uint32_t number, uint32_t owner)
{
    Port *port = g->port;
    const uint32_t b = new_actor(port, 0x4ec, CONSTRUCT_BOARD);
    port_set32(port, b, 0, number);
    port_call(port, BOARD_SIDE, b, number - 1, 0, 0);
    initialise(port, b, 0, 0, 0);
    port_call(port, SET_UPDATE, b, 0x450f60, 0, 0);
    port_set32(port, b, 0x488, port_u32(port, number == 1 ? PLAYER_ONE : PLAYER_TWO, 0));
    port_call(port, BOARD_RESET, b, 0, 0, 0);
    port_set32(port, b, 0x470, 3);
    port_set32(port, BOARDS + 4 * port_u32(port, b, 0), 0, b);
    const uint32_t base = number == 1 ? 0xca : 0xce;
    port_set16(port, b, 0x168, base);
    port_set16(port, b, 0x16a, base + 1);
    port_set16(port, b, 0x16c, base - 2);
    port_set16(port, b, 0x16e, base - 1);

    /* Its keys: none for the remote side of a network game, else the player's own, or the
     * computer's when no person plays it. */
    const int remote = port_u32(port, number == 1 ? NETWORKED : HOSTING, 0) == 1;
    uint32_t keys = 0;
    if (!remote)
    {
        if (number == 1)
        {
            keys =
                port_u32(port, HOSTING, 0) == 1 || port_u32(port, ONE_HUMAN, 0) != 0 ? ONE_KEYS : 0;
        }
        else
        {
            keys = port_u32(port, NETWORKED, 0) == 1   ? ONE_KEYS
                   : port_u32(port, TWO_HUMAN, 0) != 0 ? TWO_KEYS
                                                       : 0;
        }
        if (keys == 0)
        {
            port_set32(port, b, 0x454, 1);
        }
    }
    static const uint32_t COMPUTER[2][4] = {{0x6e, 0x6f, 0x6c, 0x6d}, {0xc6, 0xc7, 0xc4, 0xc5}};
    for (unsigned i = 0; i < 4; i++)
    {
        const uint32_t key = remote      ? 0
                             : keys != 0 ? at(port, keys + 2 * i)
                                         : COMPUTER[number - 1][i];
        port_set16(port, b, 0x160 + 2 * i, key);
    }
    port_call(port, BOARD_READY, b, 0, 0, 0);
    port_set32(port, b, 0x174, port_u32(port, number == 1 ? ONE_SCORE : TWO_SCORE, 0));
    port_call(port, REGISTER, ACTORS, b, 0, 0);
    port_set32(port, port_u32(port, b, 0x15c), 0xce4, owner);
    return b;
}

/* Board `number`'s preview of the next pieces, at the rectangle at `rect`. */
static void preview(Game *g, uint32_t number, uint32_t b, uint32_t rect)
{
    Port *port = g->port;
    const uint32_t p = new_actor(port, 0x284, CONSTRUCT_PREVIEW);
    port_set32(port, p, 0, 2 + number);
    port_set32(port, p, 4, number);
    initialise(port, p, word(at(port, rect)), word(at(port, rect + 4)), 0);
    port_set32(port, p, 0x27c, port_u32(port, rect + 8, 0) - port_u32(port, 0x4f9060, 0));
    port_set32(port, p, 0x280, port_u32(port, rect + 0xc, 0) - port_u32(port, 0x4f9064, 0));
    if (number == 2)
    {
        port_set32(port, p, 0x278, 0);
    }
    port_call(port, PREVIEW_PLAYER, p, colour(port, number == 1 ? PLAYER_ONE : PLAYER_TWO), 0, 0);
    port_call(port, PREVIEW_READY, p, 0, 0, 0);
    port_call(port, REGISTER, ACTORS, p, 0, 0);
    port_set32(port, b, 0x3b8, p);
}

typedef struct
{
    uint32_t place; /* x and y words */
    uint32_t kind, side;
    int scored;     /* the text shows the score at 0x532bc0 */
    uint32_t keys;  /* the key names */
    uint32_t group; /* +0x148 */
    uint32_t update, cursor_update;
} Arrows;

static const Arrows ARROWS[4] = {{0x4f8a18, 0xb, 1, 0, 0x4fd608, 2, 0x44fc00, 0x44fc60},
                                 {0x4f8a20, 9, 1, 1, 0x4fd628, 4, 0x44fa70, 0x44fad0},
                                 {0x4f8a30, 0xc, 2, 0, 0x4fd618, 3, 0x44fc00, 0x44fc60},
                                 {0x4f8a28, 0xa, 2, 1, 0x4fd638, 5, 0x44fa70, 0x44fad0}};

/* A column of four arrows (the first clickable, the rest following it) and its cursor. */
static void arrows(Game *g, const Arrows *a)
{
    Port *port = g->port;
    for (uint32_t i = 0; i < 4; i++)
    {
        const uint32_t arrow = new_actor(port, 0x194, CONSTRUCT_ARROW);
        if (i == 0)
        {
            port_set32(port, arrow, 0, a->kind);
            port_set32(port, arrow, 4, a->side);
        }
        else
        {
            port_set32(port, arrow, 4, a->kind);
        }
        initialise(port, arrow, 0, 0, 0);
        port_set32(port, arrow, 0x184, 0);
        port_set32(port, arrow, 0x188, 2);
        text_box(port, arrow, a->scored ? port_u32(port, 0x532bc0, 0) : 0,
                 colour(port, 0x546830 + i), a->place, a->place + 4, ARROW_RECT);
        port_call(port, ATTACH, g->screen, port_u32(port, a->keys + 4 * i, 0), arrow, 0);
        port_set32(port, arrow, 0x124, 1);
        if (i == 0)
        {
            hit_area(port, arrow, word(at(port, a->place)), word(at(port, a->place + 4)),
                     port_u32(port, ARROW_RECT, 0), port_u32(port, ARROW_RECT + 4, 0));
        }
        else
        {
            port_set32(port, arrow, 0x138, 0);
            port_call(port, SET_UPDATE, arrow, a->update, 0, 0);
        }
        port_set16(port, arrow, 0x148, a->group);
        port_call(port, REGISTER, ACTORS, arrow, 0, 0);
    }
    const uint32_t cursor = new_actor(port, 0x15c, CONSTRUCT_ACTOR);
    port_call(port, PLACE_CURSOR, cursor, word(at(port, a->place)), word(at(port, a->place + 4)),
              port_u32(port, 0x4fbf60, 0));
    port_set32(port, cursor, 4, a->kind);
    port_set16(port, cursor, 0x48, 0xff9c);
    port_set8(port, cursor, 0x4e, 0x32);
    port_set8(port, cursor, 0x93, 1);
    port_set8(port, cursor, 0x95, 4);
    port_call(port, SET_LAYER, cursor, 1, 0, 0);
    port_call(port, SET_DEPTH, cursor, 0, 0, 0);
    port_call(port, SET_UPDATE, cursor, a->cursor_update, 0, 0);
    port_call(port, REGISTER, ACTORS, cursor, 0, 0);
}

/* Player `side`'s scoreboard at the rectangle at `rect`. */
static void scoreboard(Game *g, uint32_t side, uint32_t rect)
{
    Port *port = g->port;
    const uint32_t s = new_actor(port, 0x194, CONSTRUCT_SCORE);
    port_set32(port, s, 0, 6 + side);
    port_set32(port, s, 4, side);
    initialise(port, s, 0, 0, 0);
    port_set32(port, s, 0x184, 1);
    port_set32(port, s, 0x188, 8);
    port_set8(port, s, 0x44, 0x10);
    text_box(port, s, 0, colour(port, 0x4f9c0c), rect, rect + 4, rect + 8);
    port_call(port, SET_UPDATE, s, 0x450cd0, 0, 0);
    port_call(port, SET_LAYER, s, 5, 0, 0);
    port_call(port, ATTACH, g->screen, 0x27 + side, s, 0);
    port_set32(port, s, 0x124, 1);
    hit_area(port, s, word(at(port, rect)), word(at(port, rect + 4)), port_u32(port, rect + 8, 0),
             port_u32(port, rect + 0xc, 0));
    port_call(port, SCORE_VALUE, s, port_u32(port, side == 1 ? ONE_SCORE : TWO_SCORE, 0), 0, 0);
    port_call(port, REGISTER, ACTORS, s, 0, 0);
}

static void counter(Game *g, uint32_t side)
{
    Port *port = g->port;
    const uint32_t c = new_actor(port, 0x174, CONSTRUCT_COUNTER);
    port_set32(port, c, 0, 0xc + side);
    port_set32(port, c, 4, side);
    port_call(port, SET_UPDATE, c, 0x44fe80, 0, 0);
    port_call(port, SET_DEPTH, c, 0, 0, 0);
    port_call(port, SET_SPEED, c, 0x1f4, 0, 0);
    port_call(port, SET_FRAME, c, 0x1f4, 0, 0);
    port_call(port, COUNTER_SIDE, c, side - 1, 0, 0);
    port_call(port, REGISTER, ACTORS, c, 0, 0);
}

static uint32_t sbyte(uint32_t value)
{
    return (uint32_t)(int32_t)(int8_t)value;
}

/* Board b's light, in the rectangle at `rect`, starting in the shared colours. */
static void light(Game *g, uint32_t b, uint32_t kind, uint32_t rect, const uint32_t first[3])
{
    Port *port = g->port;
    const uint32_t l = new_actor(port, 0x16c, CONSTRUCT_LIGHT);
    port_set32(port, l, 0, kind);
    initialise(port, l, 0, 0, 0);
    const uint32_t stack[3] = {word(at(port, rect + 0xc)), word(at(port, rect + 0x10)), 0xc};
    port_call_stack(port, LIGHT_PLACE, l, word(at(port, rect)), word(at(port, rect + 4)),
                    word(at(port, rect + 8)), stack, 3);
    for (uint32_t k = 0; k < 3; k++)
    {
        port_call(port, SET_UPDATE, port_u32(port, l, 0x15c + 4 * k), 0x44c3d0, 0x44c3d0, l + 0xc);
    }
    port_call(port, LIGHT_COLOURS, l, sbyte(first[0]), sbyte(first[1]), sbyte(first[2]));
    port_call(port, LIGHT_SPEED, l, 5, 0, 0);
    const uint32_t a = port_call(port, RANDOM, RANDOM_STATE, vertrix_lift_edx, 0, 0);
    const uint32_t c2 = port_call(port, RANDOM, RANDOM_STATE, 5, 0, 0);
    const uint32_t c3 = port_call(port, RANDOM, RANDOM_STATE, 5, 0, 0);
    port_call(port, LIGHT_COLOURS, l, sbyte(a), sbyte(c2), sbyte(c3));
    port_call(port, REGISTER, ACTORS, l, 0, 0);
    port_set32(port, b, 0x3b4, l);
}

/* A row of three lamps down the middle of the rectangle at `rect`. */
static void lamps(Game *g, uint32_t rect, uint32_t handler, uint32_t first_kind)
{
    Port *port = g->port;
    for (uint32_t i = 0; i < 3; i++)
    {
        const uint32_t height = port_u32(port, rect + 0xc, 0);
        const uint32_t x = word(port_u32(port, rect, 0) + (port_u32(port, rect + 8, 0) >> 1));
        const uint32_t y = word(height * i + port_u32(port, rect + 4, 0) + (height >> 1));
        const uint32_t lamp = new_actor(port, 0x15c, CONSTRUCT_ACTOR);
        initialise(port, lamp, x, y, handler);
        port_call(port, SET_ARRIVAL, lamp, 0, 0, 0);
        port_set32(port, lamp, 0, first_kind + i);
        port_call(port, SET_FRAMES, lamp, 1, 0, 0);
        port_call(port, SET_LAYER, lamp, 1, 0, 0);
        port_set8(port, lamp, 0x4e, 0x28);
        port_set8(port, lamp, 0x93, 1);
        port_set8(port, lamp, 0x94, 1);
        port_set8(port, lamp, 0x95, 2);
        port_call(port, REGISTER, ACTORS, lamp, 0, 0);
    }
}

/* Player `side`'s pointer at the rectangle at `rect`, and its path. */
static void pointer(Game *g, uint32_t side, uint32_t rect)
{
    Port *port = g->port;
    const uint32_t p = new_actor(port, 0x15c, CONSTRUCT_ACTOR);
    initialise(port, p, word(at(port, rect)), word(at(port, rect + 4)), 0);
    port_set32(port, p, 0, 0xe + side);
    port_set32(port, p, 4, side);
    port_call(port, SET_LAYER, p, 1, 0, 0);
    port_call(port, SET_UPDATE, p, 0x44c5a0, 0, 0);
    port_call(port, SET_ARRIVAL, p, 0, 0, 0);
    port_set8(port, p, 0x4e, 0);
    port_set8(port, p, 0x93, 1);
    port_set8(port, p, 0x94, 1);
    port_set8(port, p, 0x95, 1);
    port_call(port, SET_SPRITES, p, 0, 0, 0);
    port_call(port, SET_KIND, p, 0, 0, 0);
    port_call(port, SET_IMAGE, p, 0, 0, 0x140);
    port_set32(port, p, 0x58, 0);
    port_call(port, REGISTER, ACTORS, p, 0, 0);
    const uint32_t centre_x = (port_u32(port, rect + 8, 0) >> 1) + port_u32(port, rect, 0);
    const uint32_t centre_y = (port_u32(port, rect + 0xc, 0) >> 1) + port_u32(port, rect + 4, 0);
    const uint32_t which = side - 1;
    port_call_stack(port, POINTER_PATH, 0xe + side, centre_x, centre_y - 1, 0x140, &which, 1);
}

static void badge(Game *g, uint32_t side, uint32_t place)
{
    Port *port = g->port;
    const uint32_t r = new_actor(port, 0x15c, CONSTRUCT_ACTOR);
    initialise(port, r, word(at(port, place)), word(at(port, place + 4)), 0);
    port_set32(port, r, 0, 0x10 + side);
    port_set32(port, r, 4, side);
    port_call(port, SET_LAYER, r, 1, 0, 0);
    port_call(port, SET_UPDATE, r, 0x450d40, 0, 0);
    port_call(port, SET_ARRIVAL, r, 0, 0, 0);
    port_set8(port, r, 0x93, 0);
    port_set8(port, r, 0x94, 1);
    port_set8(port, r, 0x95, 2);
    port_set16(port, r, 0xa8, 0);
    port_set16(port, r, 0xaa, 0);
    port_set16(port, r, 0xac, 0);
    port_set16(port, r, 0xae, 0);
    port_set8(port, r, 0x8e, 3);
    port_call(port, SET_SPRITES, r, 0x5449fc, 0, 0);
    port_call(port, SET_KIND, r, port_u32(port, 0x4fbf80, 0), 0, 0);
    port_call(port, REGISTER, ACTORS, r, 0, 0);
}

static void timer(Game *g, uint32_t side)
{
    Port *port = g->port;
    const uint32_t t = new_actor(port, 0x15c, CONSTRUCT_ACTOR);
    initialise(port, t, 0, 0, 0);
    port_set32(port, t, 0, 0x16 + side);
    port_set32(port, t, 4, side);
    port_call(port, SET_SPEED, t, 0x3e8, 0, 0);
    port_call(port, SET_FRAME, t, 0x96, 0, 0);
    port_set32(port, t, 0x58, 0);
    port_set32(port, t, 0x64, 0xc);
    port_set32(port, t, 0x70, 0xc);
    port_call(port, SET_UPDATE, t, 0x450750, 0, 0);
    port_call(port, SET_ARRIVAL, t, 0, 0, 0);
    port_call(port, REGISTER, ACTORS, t, 0, 0);
}

/* Step `count` of a player's drop queue at the position words at (x_at, y_at): its slot,
 * placed by 0x471100, and the piece in it. */
static void queue_step(Game *g, uint32_t kind, uint32_t x_at, uint32_t y_at, uint32_t number,
                       uint32_t delay, uint32_t count)
{
    Port *port = g->port;
    const uint32_t x = word(at(port, x_at) + at(port, SCREEN_OFFSET));
    const uint32_t y = word(at(port, y_at) + at(port, SCREEN_OFFSET + 4));
    const uint32_t stack[2] = {0xffffffff, g->screen};
    const uint32_t slot =
        port_call_stack(port, PLACE, x, y, port_u32(port, 0x4fbfac, 0), number, stack, 2);
    port_set32(port, slot, 4, kind);
    port_set32(port, slot, 0x124, 0);
    hit_area(port, slot, x, y, port_u32(port, 0x4f8c48, 0), port_u32(port, 0x4f8c4c, 0));
    port_call(port, SET_DEPTH, slot, 0, 0, 0);
    port_set32(port, slot, 0x58, count);
    port_call(port, SET_SPEED, slot, 0xa, 0, 0);
    port_call(port, SET_FRAME, slot, 0x1f4, 0, 0);
    port_call(port, SET_UPDATE, slot, 0x450860, 0, 0);

    const uint32_t piece = new_actor(port, 0x15c, CONSTRUCT_ACTOR);
    initialise(port, piece, x, y, 0);
    port_set32(port, piece, 4, kind);
    port_call(port, SET_SPEED, piece, 0xa, 0, 0);
    port_call(port, SET_FRAME, piece, delay, 0, 0);
    port_call(port, SET_UPDATE, piece, 0x450a10, 0, 0);
    port_call(port, SET_DEPTH, piece, 0, 0, 0);
    port_set32(port, piece, 0x7c, 0);
    port_set8(port, piece, 0x93, 1);
    port_set32(port, piece, 0x58, count);
    port_set8(port, piece, 0x95, 4);
    port_call(port, SET_SPRITES, piece, 0x546618, 0, 0);
    port_call(port, SET_KIND, piece, 0, 0, 0);
    port_call(port, START_ANIMATION, piece, 0, 0, 0);
    port_call(port, REGISTER, ACTORS, piece, 0, 0);
}

/* Player `side`'s end-of-round actors: its marker and its figure. */
static void finish(Game *g, uint32_t side)
{
    Port *port = g->port;
    uint32_t actor = new_actor(port, 0x15c, CONSTRUCT_ACTOR);
    port_set32(port, actor, 4, side);
    initialise(port, actor, 0, 0, 0);
    port_call(port, SET_UPDATE, actor, 0x45aa70, 0, 0);
    port_call(port, REGISTER, ACTORS, actor, 0, 0);

    const uint32_t place = side == 1 ? 0x4f8a58 : 0x4f8a78;
    actor = new_actor(port, 0x15c, CONSTRUCT_ACTOR);
    port_set32(port, actor, 0, 0x12 + side);
    port_set32(port, actor, 4, side);
    initialise(port, actor, word(at(port, place)), word(at(port, place + 4)), 0);
    port_set8(port, actor, 0x8e, 3);
    if (side == 1)
    {
        port_set16(port, actor, 0xa8, at(port, 0x533d68));
        port_set16(port, actor, 0xaa, at(port, 0x4f8a60));
        port_set16(port, actor, 0xae, at(port, 0x4f8a68));
        port_set16(port, actor, 0xac, at(port, 0x4f8a64));
    }
    else
    {
        port_set16(port, actor, 0xa8, at(port, 0x4f8a80));
        port_set16(port, actor, 0xaa, at(port, 0x4f8a84));
        port_set16(port, actor, 0xac, at(port, 0x4f8a88));
        port_set16(port, actor, 0xae, at(port, 0x4f8a8c));
    }
    port_call(port, SET_SPRITES, actor, 0x544a34, 0, 0);
    port_call(port, SET_KIND, actor, port_u32(port, side == 1 ? PLAYER_ONE : PLAYER_TWO, 0), 0, 0);
    port_call(port, START_ANIMATION, actor, 0, 0, 0);
    port_set8(port, actor, 0x4e, 0x64);
    if (side == 2)
    {
        port_set16(port, actor, 0x4a, 0x64);
        port_set16(port, actor, 0x4c, 0x32);
    }
    port_set8(port, actor, 0x93, 1);
    port_set32(port, actor, 0x150, 1);
    port_call(port, SET_LAYER, actor, 0x46, 0, 0);
    port_call(port, SET_UPDATE, actor, 0x45abd0, 0, 0);
    port_set32(port, actor, 0x124, 1);
    if (side == 1)
    {
        hit_area(port, actor, word(at(port, 0x533d6c)), word(at(port, 0x4f8a6c)),
                 port_u32(port, 0x4f8a70, 0), port_u32(port, 0x4f8a74, 0));
    }
    else
    {
        hit_area(port, actor, word(at(port, 0x4f8a90)), word(at(port, 0x4f8a94)),
                 port_u32(port, 0x4f8a98, 0), port_u32(port, 0x4f8a9c, 0));
    }
    port_set32(port, actor, 0x13c, 0);
    port_call(port, REGISTER, ACTORS, actor, 0, 0);
}

uint32_t vertrix_port_game_screen_build_actors_46c9d0(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    Game g = {&port, entry->eax};

    const uint32_t one = board(&g, 1, entry->edx);
    const uint32_t two = board(&g, 2, entry->ebx);
    port_set32(&port, one, 0x3b0, two);
    port_set32(&port, two, 0x3b0, one);
    preview(&g, 1, one, 0x4f8ac0);
    preview(&g, 2, two, 0x4f8ad0);
    for (unsigned i = 0; i < 4; i++)
    {
        arrows(&g, &ARROWS[i]);
    }
    scoreboard(&g, 1, 0x4f8ae0);
    scoreboard(&g, 2, 0x4f8af0);
    counter(&g, 1);
    counter(&g, 2);

    uint32_t shared[3];
    for (unsigned i = 0; i < 3; i++)
    {
        shared[i] = port_call(&port, RANDOM, RANDOM_STATE, 5, 0, 0);
    }
    light(&g, one, 5, 0x4f8b00, shared);
    light(&g, two, 6, 0x4f8b14, shared);
    lamps(&g, 0x4f8b00, 0x457170, 0x64);
    lamps(&g, 0x4f8b14, 0x4572b0, 0x67);
    pointer(&g, 1, 0x4f8980);
    pointer(&g, 2, 0x4f8990);
    const uint32_t mover = new_actor(&port, 0x15c, CONSTRUCT_ACTOR);
    port_call(&port, SET_LAYER, mover, 0xa, 0, 0);
    port_call(&port, SET_UPDATE, mover, 0x450df0, 0, 0);
    port_call(&port, REGISTER, ACTORS, mover, 0, 0);
    badge(&g, 1, 0x4f8a00);
    badge(&g, 2, 0x4f8a08);
    timer(&g, 1);
    timer(&g, 2);

    /* The drop queues: twelve steps each, each a step later. */
    uint32_t delay = 0x1b9;
    for (uint32_t step = 0; step < 12; step++, delay -= 0x28)
    {
        queue_step(&g, 0x17, 0x4f8b88 + 4 * step, 0x4f8bb8 + 4 * step, 0x40 + step, delay,
                   step + 1);
        queue_step(&g, 0x18, 0x4f8be8 + 4 * step, 0x4f8c18 + 4 * step, 0x40 + step, delay,
                   step + 1);
    }
    const uint32_t stack[2] = {0xffffffff, g.screen};
    port_call_stack(&port, PLACE, word(at(&port, 0x4f8c50)), word(at(&port, 0x4f8c54)),
                    port_u32(&port, 0x4fbfa8, 0), 0x4c, stack, 2);
    port_call_stack(&port, PLACE, word(at(&port, 0x4f8c58)), word(at(&port, 0x4f8c5c)),
                    port_u32(&port, 0x4fbfa8, 0), 0x4d, stack, 2);
    finish(&g, 1);
    finish(&g, 2);

    port_call(&port, START_ROUND, 0, 0, 0, 0);
    port_call(&port, PREVIEW_SHOW, port_u32(&port, one, 0x3b8), 0, 0, 0);
    port_call(&port, PREVIEW_SHOW, port_u32(&port, two, 0x3b8), 0, 0, 0);
    return port_return(&port, port.env.chain, vertrix_lift_edx);
}
