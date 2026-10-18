#include "rtlplayscreenactors.h"

/* The play screen's actors. The routine is called with whether the game is networked (eax 1;
 * 0 for a local game, which also starts its music) and the local player (edx: 0 for both, else
 * 1 or 2). The panels' texts are built in a string at ebp - 0x30. */

enum
{
    BELOW = 0x50, /* the locals, down to the exception record at ebp - 0x4c */
    TEXT = 0x30,

    STRING_INIT = 0x4ca070,
    STRING_SET = 0x4ca370,
    STRING_RELEASE = 0x4ca210,
    ALLOCATE = 0x4ca000,
    CONSTRUCT_PANEL = 0x4b6350,
    CONSTRUCT_PLAYER = 0x4abd70,
    INITIALISE = 0x4adf20,
    SET_BOUNDS = 0x4b65d0,
    SET_UPDATE = 0x4ac8f0,
    SET_LAYER = 0x4ac7b0,
    SET_VISIBLE = 0x4ac910,
    SET_HIT_AREA = 0x4ae110,
    SET_TEXT_COLOUR = 0x4b6530,
    SET_SHADOW = 0x4b6540,
    SHADOW_OFF = 0x4b65b0, /* passed the shadow offset, which it leaves for 0x4b6550 */
    SET_SHADOW_Y = 0x4b6550,
    SET_SPRITES = 0x4ac8d0,
    SET_KIND = 0x4ac710,
    START_ANIMATION = 0x4ac8a0,
    SET_FRAME = 0x4ac860,
    SET_SPEED = 0x4ac7d0,
    RANDOM = 0x4826c0,
    NEW_FIELD = 0x470960,
    FIELD_SELECT = 0x4b4510,
    FIELD_LIMIT = 0x4ac4e0,
    NEW_BUTTON = 0x45fc80,
    REGISTER = 0x4b5e70,
    RESET = 0x4b7830,
    START_MUSIC = 0x46a410,

    ACTORS = 0x54671c,
    RANDOM_STATE = 0x598d30,
    PLAYER_ONE = 0x532a68,
    PLAYER_TWO = 0x532a6c,
    TIMED = 0x532a84,        /* 1 for a timed game */
    ONE_HUMAN = 0x532a74,    /* player one is a person */
    TWO_HUMAN = 0x532a78,    /* player two is a person */
    LIVES = 0x4f9c10,        /* how many lives each player has */
    PANEL_COLOUR = 0x54001a, /* bytes */
    LABEL_COLOUR = 0x4f9c03,
    METER_COLOUR = 0x4f9c04,
    TIMER_COLOUR = 0x4f9bfb
};

typedef struct
{
    Port *port;
    uint32_t text;      /* the string's address */
    uint32_t networked; /* eax */
    uint32_t local;     /* edx */
} Screen;

/* A word, sign-extended, as the original passes the coordinates. */
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

/* An actor of `size` bytes, made by `construct` when the allocation succeeds. */
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

/* Bounds from the layout words at x, y, width and height. */
static void bounds(Port *port, uint32_t actor, uint32_t text, uint32_t paint, uint32_t x_at,
                   uint32_t y_at, uint32_t width_at, uint32_t height_at)
{
    const uint32_t x = at(port, x_at);
    const uint32_t y = at(port, y_at);
    const uint32_t stack[3] = {word(x + at(port, width_at) - 1), word(y),
                               word(y + at(port, height_at) - 1)};
    port_call_stack(port, SET_BOUNDS, actor, text, colour(port, paint), word(x), stack, 3);
}

typedef struct
{
    uint32_t text, update, paint;
    uint32_t x_at, width_at;
    uint32_t y_at; /* 0 for the first row */
    uint32_t layer_byte;
} Panel;

/* A player's panel: the name panel `number` (1 or 2) with its text. */
static void panel(Screen *s, const Panel *p, uint32_t number)
{
    Port *port = s->port;
    const uint32_t actor = new_actor(port, 0x180, CONSTRUCT_PANEL);
    initialise(port, actor, 0, 0, 0);
    port_call(port, STRING_SET, s->text, p->text, 0, 0);
    port_call(port, SET_UPDATE, actor, p->update, 0, 0);
    port_set8(port, actor, 0x44, p->layer_byte);
    const uint32_t x = at(port, p->x_at);
    const uint32_t y = p->y_at != 0 ? word(at(port, p->y_at)) : 1;
    const uint32_t stack[3] = {word(x + at(port, p->width_at) - 1), y, y};
    port_call_stack(port, SET_BOUNDS, actor, port_u32(port, s->text, 0), colour(port, p->paint),
                    word(x), stack, 3);
    port_call(port, SET_LAYER, actor, 2, 0, 0);
    port_set8(port, actor, 0x52, 9);
    port_set8(port, actor, 0x4e, 0);
    port_set8(port, actor, 0x93, 1);
    port_set32(port, actor, 4, number);
    port_call(port, SET_VISIBLE, actor, 0, 0, 0);
    port_call(port, REGISTER, ACTORS, actor, 0, 0);
}

/* The panels: a person's (0x4479f0) or the computer's (0x447af0), placed by the game type. */
static void panels(Screen *s)
{
    Port *port = s->port;
    const int timed = port_u32(port, TIMED, 0) == 1;
    const int one = port_u32(port, ONE_HUMAN, 0) == 1;
    const int two = port_u32(port, TWO_HUMAN, 0) == 1;
    Panel first, second;
    if (s->networked == 0)
    {
        first = timed ? (Panel){0x50e53b, 0x447af0, PANEL_COLOUR, 0x533d38, 0x4f8740, 0, 9}
                      : (Panel){one ? 0x50e53c : 0x50e544,
                                0x4479f0,
                                PANEL_COLOUR,
                                0x533d3c,
                                0x4f8754,
                                0x4f8750,
                                9};
    }
    else
    {
        first = timed ? (Panel){0x50e54d, 0x447af0, PANEL_COLOUR, 0x533d38, 0x4f8740, 0x4f8750, 9}
                      : (Panel){one ? 0x50e54e : 0x50e556,
                                0x4479f0,
                                LABEL_COLOUR,
                                0x533d38,
                                0x4f8740,
                                0x4f873c,
                                0x10};
    }
    panel(s, &first, 1);
    if (s->networked == 0)
    {
        second = timed ? (Panel){0x50e55f, 0x447af0, PANEL_COLOUR, 0x4f8744, 0x4f874c, 0, 9}
                       : (Panel){two ? 0x50e560 : 0x50e568,
                                 0x4479f0,
                                 PANEL_COLOUR,
                                 0x4f8758,
                                 0x4f8760,
                                 0x4f875c,
                                 9};
    }
    else
    {
        second = timed ? (Panel){0x50e571, 0x447af0, PANEL_COLOUR, 0x4f8744, 0x4f874c, 0x4f875c, 9}
                       : (Panel){two ? 0x50e572 : 0x50e57a,
                                 0x4479f0,
                                 LABEL_COLOUR,
                                 0x4f8744,
                                 0x4f874c,
                                 0x4f8748,
                                 0x10};
    }
    panel(s, &second, 2);
}

/* A timed game's clock: its label and the field showing the time. */
static void clock(Screen *s)
{
    Port *port = s->port;
    const uint32_t label = new_actor(port, 0x180, CONSTRUCT_PANEL);
    initialise(port, label, 0, 0, 0);
    port_set8(port, label, 0x44, 0x10);
    const uint32_t x = word(at(port, 0x4f8800) + 2);
    const uint32_t stack[3] = {x, word(at(port, 0x4f8804) - 0x18), word(at(port, 0x4f8804) - 5)};
    port_call_stack(port, SET_BOUNDS, label, 0x50e583, colour(port, TIMER_COLOUR), x, stack, 3);
    port_call(port, SET_LAYER, label, 2, 0, 0);
    port_set8(port, label, 0x4e, 0);
    port_call(port, REGISTER, ACTORS, label, 0, 0);

    const uint32_t width =
        port_u32(port, 0x4f8810, 0) + port_u32(port, 0x4f8818, 0) - port_u32(port, 0x4f8800, 0);
    const uint32_t field_stack[4] = {0x10, 0x50e58a, 0x56, colour(port, TIMER_COLOUR)};
    const uint32_t field =
        port_call_stack(port, NEW_FIELD, word(at(port, 0x4f8800)), word(at(port, 0x4f8804) - 0x18),
                        word(width), 0x14, field_stack, 4);
    port_set32(port, field, 0x184, 0x416990);
    port_call(port, SET_UPDATE, field, 0x4451d0, 0, 0);
    port_call(port, FIELD_SELECT, field, 0, 0, 0);
    port_set32(port, field, 0x178, 0x27);
    port_call(port, STRING_SET, field + 0x18c, 0x50e58b, 0, 0);
    port_call(port, FIELD_LIMIT, field, 0x7f, 0, 0);
    port_call(port, REGISTER, ACTORS, field, 0, 0);
}

/* A shaded text at the layout rectangle `rect`; the first one marks itself shown after it is
 * made visible, the second before. */
static void meter(Screen *s, uint32_t rect, uint32_t text, uint32_t speed_at, int first)
{
    Port *port = s->port;
    const uint32_t actor = new_actor(port, 0x180, CONSTRUCT_PANEL);
    initialise(port, actor, 0, 0, 0x44bba0);
    bounds(port, actor, text, LABEL_COLOUR, rect, rect + 4, rect + 8, rect + 0xc);
    port_call(port, SET_LAYER, actor, 2, 0, 0);
    port_set8(port, actor, 0x44, 0);
    port_set8(port, actor, 0x4e, 0x50);
    if (!first)
    {
        port_set8(port, actor, 0x93, 1);
    }
    port_set8(port, actor, 0x94, 0);
    port_set8(port, actor, 0x95, 3);
    port_set32(port, actor, 0x14c, port_u32(port, speed_at, 0));
    if (first)
    {
        port_set16(port, actor, 0x172, 1);
    }
    port_call(port, SET_VISIBLE, actor, 0, 0, 0);
    if (first)
    {
        port_set8(port, actor, 0x93, 1);
    }
    port_call(port, SET_TEXT_COLOUR, actor, colour(port, METER_COLOUR), 0, 0);
    port_call(port, SET_SHADOW, actor, 0xffffffb0, 0, 0);
    port_call(port, SHADOW_OFF, actor, 0xffffffb0, 0, 0);
    port_call(port, SET_SHADOW_Y, actor, vertrix_lift_edx, 0, 0);
    port_set32(port, actor, 0x124, 1);
    const uint32_t hit[1] = {port_u32(port, rect + 0xc, 0) + 8};
    port_call_stack(port, SET_HIT_AREA, actor, word(at(port, rect) - 4),
                    word(at(port, rect + 4) - 4), port_u32(port, rect + 8, 0) + 8, hit, 1);
    port_call(port, REGISTER, ACTORS, actor, 0, 0);
}

/* The round counter. */
static void counter(Screen *s)
{
    Port *port = s->port;
    const uint32_t actor = new_actor(port, 0x180, CONSTRUCT_PANEL);
    initialise(port, actor, 0, 0, 0x45d690);
    bounds(port, actor, 0x50e593, LABEL_COLOUR, 0x533d40, 0x4f87c4, 0x4f87c8, 0x4f87cc);
    port_call(port, SET_LAYER, actor, 3, 0, 0);
    port_set8(port, actor, 0x44, 0x10);
    port_set8(port, actor, 0x4e, 0);
    port_set8(port, actor, 0x93, 1);
    port_set8(port, actor, 0x94, 1);
    port_set8(port, actor, 0x95, 1);
    port_call(port, SET_TEXT_COLOUR, actor, 9, 0, 0);
    port_call(port, SET_SHADOW, actor, 0xffffffb0, 0, 0);
    port_call(port, SHADOW_OFF, actor, 0xffffffb0, 0, 0);
    port_call(port, SET_SHADOW_Y, actor, vertrix_lift_edx, 0, 0);
    port_set32(port, actor, 0x64, 1);
    port_call(port, SET_VISIBLE, actor, 0, 0, 0);
    port_call(port, REGISTER, ACTORS, actor, 0, 0);
}

/* Player `number`'s actor in the layout rectangle `rect`, kind 0x13 or 0x14. */
static void player(Screen *s, uint32_t number, uint32_t rect, uint32_t handler, uint32_t kind_at)
{
    Port *port = s->port;
    const uint32_t actor = new_actor(port, 0x15c, CONSTRUCT_PLAYER);
    const uint32_t cx = port_u32(port, rect, 0) + (port_u32(port, rect + 8, 0) >> 1);
    const uint32_t cy = port_u32(port, rect + 4, 0) + (port_u32(port, rect + 0xc, 0) >> 1);
    initialise(port, actor, word(cx), word(cy), handler);
    port_set32(port, actor, 0, 0x12 + number);
    port_call(port, SET_VISIBLE, actor, 0, 0, 0);
    port_call(port, SET_SPRITES, actor, 0x544a34, 0, 0);
    port_call(port, SET_KIND, actor, port_u32(port, kind_at, 0), 0, 0);
    port_call(port, START_ANIMATION, actor, 1, 0, 0);
    port_call(port, SET_FRAME, actor, vertrix_lift_edx, 0, 0);
    port_set32(port, actor, 0x150, 1);
    port_set16(port, actor, 0xe, number == 1 ? 0xff38 : at(port, 0x5b9c8e) + 0xc7);
    port_set16(port, actor, 0x12, 1);
    port_set16(port, actor, 0x16, cy);
    port_set16(port, actor, 0x10, cx);
    port_set16(port, actor, 0x18, cy);
    port_set16(port, actor, 8, cx);
    port_set16(port, actor, 0xa, cy);
    port_set16(port, actor, 0x1a, 1);
    port_set16(port, actor, 0x24, port_call(port, RANDOM, RANDOM_STATE, 0x168, 0, 0));
    port_set16(port, actor, 0x28, port_call(port, RANDOM, RANDOM_STATE, 2, 0, 0) + 1);
    port_set16(port, actor, 0x30, port_call(port, RANDOM, RANDOM_STATE, 5, 0, 0));

    /* Its playing area; a timed game keeps the clock's 0x18 rows clear at the bottom. */
    const uint32_t x = at(port, rect);
    const uint32_t y = at(port, rect + 4);
    const uint32_t clear = port_u32(port, TIMED, 0) == 1 ? 0x19 : 1;
    port_set16(port, actor, 0xaa, x + at(port, rect + 8) - 1);
    port_set16(port, actor, 0xac, y);
    port_set16(port, actor, 0xa8, x);
    port_set16(port, actor, 0xae, y + at(port, rect + 0xc) - clear);
    port_set8(port, actor, 0x8e, 3);
    port_set32(port, actor, 0x124, 1);
    const uint32_t none[1] = {0};
    port_call_stack(port, SET_HIT_AREA, actor, 0, 0, 0, none, 1);
    port_set32(port, actor, 0x13c, 0);

    /* Who moves it: in a networked game the local player moves fast (5), the other at the
     * network's pace (3, or 4 when both are local); else the computer's pace. */
    if (s->networked != 1)
    {
        port_set32(port, actor, 0x64, 0);
        port_set32(port, actor, 0x70, number);
        port_set32(port, actor, 0x58, port_u32(port, kind_at, 0));
        port_set32(port, actor, 0x68, 0);
        port_call(port, SET_SPEED, actor, 0x1f4, 0, 0);
    }
    else
    {
        if (s->local == number)
        {
            port_call(port, SET_SPEED, actor, 0x64, 0, 0);
            port_set32(port, actor, 0x68, 5);
            port_set32(port, actor, 0x64, 1);
        }
        else
        {
            port_set32(port, actor, 0x64, 2);
            const int both = s->local == 0;
            port_call(port, SET_SPEED, actor, both ? 0x64 : 0x640, 0, 0);
            port_set32(port, actor, 0x68, both ? 4 : 3);
        }
        port_set32(port, actor, 0x70, number);
        port_set32(port, actor, 0x58, port_u32(port, kind_at, 0));
    }
    port_call(port, SET_UPDATE, actor, 0x45af40, 0, 0);
    port_call(port, REGISTER, ACTORS, actor, 0, 0);
}

/* A timed game's lives: a button per life, 0x14 apart down the clock's left edge. */
static void lives(Screen *s)
{
    Port *port = s->port;
    const uint32_t count = port_u32(port, LIVES, 0);
    const uint32_t x = word(at(port, 0x4f8800) - 2);
    const uint32_t width = word(port_u32(port, 0x4f8810, 0) + port_u32(port, 0x4f8818, 0) -
                                port_u32(port, 0x4f8800, 0) + 4);
    uint32_t y = at(port, 0x4f8804) - 2;
    for (uint32_t i = 0; i < count; i++, y += 0x14)
    {
        const uint32_t stack[5] = {0x50e596, 5, 0x10, 2, 0};
        const uint32_t button =
            port_call_stack(port, NEW_BUTTON, x, word(y), width, 0x18, stack, 5);
        port_call(port, SET_UPDATE, button, 0x446500, 0, 0);
        port_set8(port, button, 0x110, 0);
        port_set32(port, button, 0x70, i);
        const uint32_t face = port_u32(port, button, 0x160);
        port_set8(port, face, 0x93, 1);
        port_set8(port, face, 0x95, 5);
        port_set8(port, button, 0x52, 0xd);
        port_set8(port, face, 0x52, 0xd);
        port_call(port, REGISTER, ACTORS, button, 0, 0);
    }
}

uint32_t vertrix_port_play_screen_actors_build_469480(PORT_SIGNATURE)
{
    Port port;
    uint8_t stack[BELOW + 8];
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    const uint32_t frame = entry->esp - 4;
    Screen s = {&port, frame - TEXT, entry->eax, entry->edx};

    port_call(&port, STRING_INIT, s.text, 0, 0, 0);
    port_call(&port, RESET, 0x532c24, 0, 0, 0);
    panels(&s);
    if (port_u32(&port, TIMED, 0) == 1)
    {
        clock(&s);
    }
    meter(&s, 0x4f8794, 0x50e58c, 0x4f7bb8, 1);
    meter(&s, 0x4f87a4, 0x50e590, 0x4f7bbc, 0);
    counter(&s);
    player(&s, 1, 0x4f8774, 0, PLAYER_ONE);
    player(&s, 2, 0x4f8784, 0x448ca0, PLAYER_TWO);
    if (port_u32(&port, TIMED, 0) == 1)
    {
        lives(&s);
    }
    if (s.networked == 0)
    {
        port_call(&port, START_MUSIC, 0, 0, 0, 0);
    }
    port_call(&port, STRING_RELEASE, s.text, 0, 0, 0);
    return port_return(&port, port.env.chain, vertrix_lift_edx);
}
