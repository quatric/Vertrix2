#include "rtluiscreenactors.h"

/* The play screen's interface: each piece is placed by 0x471100 at a position from the layout
 * table (an x word and a y word 4 bytes later) with its image and number, for the screen's owner
 * and slot (-1 for none). Then come the two players' 4 x 7 grids, the two panel actors, and the
 * rest of the pieces. */

enum
{
    PLACE = 0x471100,
    GRID_ITEM = 0x4178d0,
    HAS_PANEL = 0x4126f0,
    ALLOCATE = 0x4ca000,
    CONSTRUCT = 0x4b6350,
    INITIALISE = 0x4adf20,
    SET_BOUNDS = 0x4b65d0,
    ATTACH = 0x4123d0,
    REGISTER = 0x4b5e70,

    ACTORS = 0x54671c,
    PLAYER_ONE = 0x532a68,
    PLAYER_TWO = 0x532a6c,
    PLAYER_IMAGES = 0x5345d4,
    PANEL_COLOUR = 0x4f9c0a, /* a byte */
    NO_SLOT = 0xffffffff,

    GRID_COLUMNS = 4,
    GRID_ROWS = 7
};

typedef struct
{
    uint32_t at;    /* the x word; the y word is 4 bytes on */
    uint32_t image; /* where the image is */
    uint32_t number;
} Piece;

/* The pieces placed before the grids. */
static const Piece FIRST[] = {
    {0x4f888c, 0x5466c4, 0x00}, {0x4f8894, 0x4fbf28, 0x01}, {0x4f889c, 0x4fbf2c, 0x02},
    {0x4f88a4, 0x4fbf2c, 0x03}, {0x4f8938, 0x4fbfdc, 0x6a}, {0x4f8948, 0x4fbfdc, 0x6b},
    {0x4f8930, 0x4fbfd8, 0x6c}, {0x4f8940, 0x4fbfd8, 0x6d}, {0x4f88b8, 0x4fbf30, 0x04},
    {0x4f88c8, 0x4fbf38, 0x05}, {0x4f88b0, 0x4fbf34, 0x06}, {0x4f88c0, 0x4fbf3c, 0x07},
    {0x4f88d8, 0x4fbf38, 0x58}, {0x4f88e8, 0x4fbf30, 0x59}, {0x4f88d0, 0x4fbf3c, 0x5a},
    {0x4f88e0, 0x4fbf34, 0x5b}, {0x4f88f8, 0x4fbfd0, 0x62}, {0x4f8928, 0x4fbfd0, 0x63},
    {0x4f88f0, 0x4fbfc8, 0x64}, {0x4f8920, 0x4fbfc8, 0x65}, {0x4f8908, 0x4fbfd4, 0x66},
    {0x4f8918, 0x4fbfd4, 0x67}, {0x4f8900, 0x4fbfcc, 0x68}, {0x4f8910, 0x4fbfcc, 0x69},
    {0x4f8950, 0x4fbf44, 0x08}, {0x4f8958, 0x4fbf44, 0x09}, {0x4f8960, 0x4fbf40, 0x0a},
    {0x4f8968, 0x4fbf40, 0x0b}, {0x4f89b0, 0x4fbf5c, 0x10}, {0x4f89b8, 0x4fbf5c, 0x11},
    {0x4f89c8, 0x4fbf58, 0x12}, {0x4f89d0, 0x4fbf58, 0x13}, {0x4f89e8, 0x4fbf50, 0x14},
    {0x4f89f0, 0x4fbf54, 0x15}, {0x4f89d8, 0x4fbf48, 0x16}, {0x4f89e0, 0x4fbf4c, 0x17},
    {0x4f8a18, 0x4fbf60, 0x18}, {0x4f8a20, 0x4fbf60, 0x19}, {0x4f8a28, 0x4fbf60, 0x1a},
    {0x4f8a30, 0x4fbf60, 0x1b}, {0x4f8aa0, 0x4fbf6c, 0x1c}, {0x4f8aa8, 0x4fbf6c, 0x1d},
    {0x4f8ab0, 0x4fbf70, 0x1e}, {0x4f8ab8, 0x4fbf70, 0x1f}};

/* The pieces after the panel actors, before the numbered rows. */
static const Piece MIDDLE[] = {{0x4f8b58, 0x4fbf84, 0x2e}, {0x4f8b60, 0x4fbf88, 0x2f},
                               {0x4f8b68, 0x4fbf8c, 0x30}, {0x4f8b70, 0x4fbf8c, 0x31},
                               {0x4f8b68, 0x4fbf90, 0x5e}, {0x4f8b70, 0x4fbf90, 0x5f},
                               {0x4f8b78, 0x4fbf94, 0x32}, {0x4f8b80, 0x4fbf98, 0x33},
                               {0x4f8b78, 0x4fbf9c, 0x5c}, {0x4f8b80, 0x4fbf9c, 0x5d}};

/* The last pieces. */
static const Piece LAST[] = {{0x4f8ca0, 0x4fbfbc, 0x56},
                             {0x4f8ca8, 0x4fbfc0, 0x57},
                             {0x4f8cb0, 0x4fbfc4, 0x22},
                             {0x4f8cb8, 0x4fbfc4, 0x23}};

typedef struct
{
    Port *port;
    uint32_t owner;
    uint32_t slot;
    uint32_t placed; /* what the last 0x471100 returned */
} Screen;

/* A word, sign-extended, as the original passes the coordinates. */
static uint32_t word(uint32_t value)
{
    return (uint32_t)(int32_t)(int16_t)value;
}

static uint32_t layout(Screen *s, uint32_t at)
{
    return word(port_u16(s->port, at, 0));
}

static void place(Screen *s, uint32_t x, uint32_t y, uint32_t image, uint32_t number)
{
    const uint32_t stack[2] = {s->slot, s->owner};
    s->placed =
        port_call_stack(s->port, PLACE, x, y, port_u32(s->port, image, 0), number, stack, 2);
}

static void place_at(Screen *s, uint32_t x_at, uint32_t y_at, uint32_t image, uint32_t number)
{
    place(s, layout(s, x_at), layout(s, y_at), image, number);
}

static void place_all(Screen *s, const Piece *pieces, unsigned count)
{
    for (unsigned i = 0; i < count; i++)
    {
        place_at(s, pieces[i].at, pieces[i].at + 4, pieces[i].image, pieces[i].number);
    }
}

/* Whether a grid cell is shown: always with a slot, else when the player's item there is set.
 * `ecx` is what the original leaves in ecx for 0x4178d0. */
static int shown(Screen *s, uint32_t player, uint32_t cell, uint32_t ecx)
{
    if (s->slot != NO_SLOT)
    {
        return 1;
    }
    const uint32_t item =
        port_call(s->port, GRID_ITEM, port_u8(s->port, player, 0), cell & 0xff, 1, ecx);
    return item != NO_SLOT;
}

/* A cell's two pieces (images 0x4fbf64 and 0x4fbf68) for a grid laid out from `origin`: the x
 * and y words, then the column and row steps. */
static void cell(Screen *s, uint32_t origin, uint32_t column, uint32_t row, uint32_t number)
{
    const uint32_t x = word(port_u16(s->port, origin, 0) + column * port_u16(s->port, origin, 8));
    const uint32_t y = word(port_u16(s->port, origin, 4) + row * port_u16(s->port, origin, 0xc));
    place(s, x, y, 0x4fbf64, number);
    place(s, x, y, 0x4fbf68, number + 2);
}

/* A player's panel actor (part 0x20 or 0x21) over the rectangle at `bounds` (x, y, width and
 * height words, 4 apart), when the owner has that part. */
static void panel(Screen *s, uint32_t part, uint32_t player, uint32_t bounds)
{
    Port *port = s->port;
    if (port_call(port, HAS_PANEL, s->owner, part, 0, 0) != 1)
    {
        return;
    }
    uint32_t actor = port_call(port, ALLOCATE, 0x180, 0, 0, 0);
    if (actor != 0)
    {
        actor = port_call(port, CONSTRUCT, actor, 0, 0, 0);
    }
    const uint32_t zeros[5] = {0, 0, 0, 0, 0};
    port_call_stack(port, INITIALISE, actor, 0, 0, 0, zeros, 5);
    const uint32_t x = port_u16(port, bounds, 0);
    const uint32_t y = port_u16(port, bounds, 4);
    const uint32_t rest[3] = {word(x + port_u16(port, bounds, 8) - 1), word(y),
                              word(y + port_u16(port, bounds, 0xc) - 1)};
    const uint32_t image = port_u32(port, PLAYER_IMAGES + 4 * port_u32(port, player, 0), 0);
    const uint32_t colour = (uint32_t)(int32_t)(int8_t)port_u8(port, PANEL_COLOUR, 0);
    port_call_stack(port, SET_BOUNDS, actor, image, colour, word(x), rest, 3);
    port_call(port, ATTACH, s->owner, part, actor, 0);
    port_set8(port, actor, 0x44, 0x10);
    if (s->slot == part)
    {
        port_set8(port, actor, 0x110, 1);
    }
    port_call(port, REGISTER, ACTORS, actor, 0, 0);
}

uint32_t vertrix_port_ui_screen_actors_build_46b810(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    Screen s = {&port, entry->eax, entry->edx, 0};

    place_all(&s, FIRST, sizeof FIRST / sizeof FIRST[0]);

    /* The grids: player one's left to right, player two's right to left. */
    uint32_t ecx = 0x1f;
    uint32_t number = 0;
    for (uint32_t row = 0; row < GRID_ROWS; row++)
    {
        for (uint32_t column = 0; column < GRID_COLUMNS; column++, number++)
        {
            if (shown(&s, PLAYER_ONE, number, ecx))
            {
                cell(&s, 0x4f8ac0, column, row, 0x2a);
                ecx = 0x2c;
            }
            if (shown(&s, PLAYER_TWO, number, ecx))
            {
                cell(&s, 0x4f8ad0, GRID_COLUMNS - 1 - column, row, 0x2b);
            }
            ecx = number + 1;
        }
    }

    panel(&s, 0x20, PLAYER_ONE, 0x4f8cc0);
    panel(&s, 0x21, PLAYER_TWO, 0x4f8cd0);

    place_all(&s, MIDDLE, sizeof MIDDLE / sizeof MIDDLE[0]);
    for (uint32_t i = 0; i < 12; i++)
    {
        place_at(&s, 0x4f8b88 + 4 * i, 0x4f8bb8 + 4 * i, 0x4fbfa4, 0x34 + i);
        place_at(&s, 0x4f8be8 + 4 * i, 0x4f8c18 + 4 * i, 0x4fbfa4, 0x34 + i);
    }
    place_at(&s, 0x4f8b78, 0x4f8b7c, 0x4fbfa0, 0x60);
    place_at(&s, 0x4f8b80, 0x4f8b84, 0x4fbfa0, 0x61);
    for (uint32_t i = 0; i < 2; i++)
    {
        place_at(&s, 0x4f8c60 + 4 * i, 0x4f8c68 + 4 * i, 0x4fbfb0, 0x4e + 2 * i);
        place_at(&s, 0x4f8c70 + 4 * i, 0x4f8c78 + 4 * i, 0x4fbfb4, 0x4f + 2 * i);
    }
    for (uint32_t i = 0; i < 2; i++)
    {
        place_at(&s, 0x4f8c80 + 4 * i, 0x4f8c88 + 4 * i, 0x4fbfb8, 0x52 + 2 * i);
        place_at(&s, 0x4f8c90 + 4 * i, 0x4f8c98 + 4 * i, 0x4fbfb8, 0x53 + 2 * i);
    }
    place_all(&s, LAST, sizeof LAST / sizeof LAST[0]);
    return port_return(&port, s.placed, vertrix_lift_edx);
}
