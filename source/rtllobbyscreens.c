#include "rtllobbyscreens.h"

/* The lobby: a 0x275 x 0x198 panel. The routine is called with the lobby's mode (eax): 0 for a
 * local game, which has the game's settings, the five players' table and the add-player
 * buttons; 1 to host and 2 to join a network game, which have only the message lines. */

enum
{
    BELOW = 0x1d0, /* the locals, down to the exception record at ebp - 0x1cc */
    /* The settings' value names, in the frame, by the value table each names. */
    TEXT_C88 = 0x194,
    TEXT_C44 = 0x1a8,
    TEXT_C50 = 0x1a4,
    TEXT_C78 = 0x1a0,
    TEXT_C80 = 0x19c,
    TEXT_C90 = 0x198,
    NAME_TEXT = 0x150,

    PANEL_WIDTH = 0x275,
    PANEL_HEIGHT = 0x198,
    PANEL_X = 8,
    ROW_HEIGHT = 0x18,
    LIST_LINES = 4,
    PLAYER_ROWS = 5,
    COLUMNS = 7,

    TITLE_COLOUR = 0x4f9bf8, /* bytes */
    LABEL_COLOUR = 0x4f9bf9,
    CELL_COLOUR = 0x4f9bfb,
    ITEM_COLOUR = 0x4f9bfd,
    LINE_COLOUR = 0x4f9bfe,
    BUTTON_COLOUR = 0x4f9bfa,
    FONT = 0x532a98,      /* a word */
    NAME_FONT = 0x4f7b78, /* a word */

    STRING_INIT = 0x4ca070,
    STRING_SET = 0x4ca370,
    STRING_RELEASE = 0x4ca210,
    VALUE_NAME = 0x415ed0,
    RESET = 0x4b7830,
    CLEAR_PLAYERS = 0x4b7020,
    RESET_NETWORK = 0x47f070,
    LABEL_BOX = 0x460a40,
    LABEL_BOX_LINE = 0x460ad0,
    ITEM_LABEL = 0x460c50,
    ITEM_FIELD = 0x460b60,
    ITEM_NUMBER = 0x4601c0,
    ITEM_CHOICE = 0x460fa0,
    ITEM_BUTTON = 0x460df0,
    ITEM_SCROLL = 0x461090,
    SET_CLICK = 0x4ac930,
    SET_BORDER = 0x4ac4e0,
    SET_FILL = 0x4ac4f0,
    ALLOCATE = 0x4ca000,
    CONSTRUCT = 0x4abd70,
    SET_UPDATE = 0x4ac8f0,
    REGISTER = 0x4b5e70,
    THROW = 0x4cda10,

    PLAYER_LIST = 0x532c04,
    FIRST_SHOWN = 0x532bfc, /* the table's first player */
    LEVEL = 0x532bf8,
    MENU_ACTOR = 0x532a48,
    ACTORS = 0x54671c,
    MENU_UPDATE = 0x45c6e0
};

typedef struct
{
    Port *port;
    uint32_t frame;
    uint32_t y; /* the panel's top */
} Lobby;

static uint32_t colour(Port *port, uint32_t at)
{
    return (uint32_t)(int32_t)(int8_t)port_u8(port, at, 0);
}

static uint32_t font(Port *port, uint32_t at)
{
    return (uint32_t)(int32_t)(int16_t)port_u16(port, at, 0);
}

static uint32_t text_at(Lobby *l, uint32_t slot)
{
    return port_u32(l->port, l->frame - slot, 0);
}

/* A call whose stack holds `before`, the panel (width, height, x, y) and `after`. */
static uint32_t on_panel(Lobby *l, uint32_t routine, uint32_t eax, uint32_t edx, uint32_t ebx,
                         uint32_t ecx, const uint32_t *before, unsigned nbefore,
                         const uint32_t *after, unsigned nafter)
{
    uint32_t stack[24];
    unsigned n = 0;
    for (unsigned i = 0; i < nbefore; i++)
    {
        stack[n++] = before[i];
    }
    stack[n++] = PANEL_WIDTH;
    stack[n++] = PANEL_HEIGHT;
    stack[n++] = PANEL_X;
    stack[n++] = l->y;
    for (unsigned i = 0; i < nafter; i++)
    {
        stack[n++] = after[i];
    }
    return port_call_stack(l->port, routine, eax, edx, ebx, ecx, stack, n);
}

/* A box or line (0x460a40, 0x460ad0) of `width` x `height` at (x, y). */
static uint32_t box(Lobby *l, uint32_t routine, uint32_t width, uint32_t height, uint32_t x,
                    uint32_t y, uint32_t last)
{
    return on_panel(l, routine, width, height, x, y, NULL, 0, &last, 1);
}

/* A text in a `width` x `height` box at (x, y). */
static uint32_t label(Lobby *l, uint32_t text, uint32_t width, uint32_t height, uint32_t x,
                      uint32_t y, uint32_t style, uint32_t heading, uint32_t shown, uint32_t paint,
                      uint32_t last)
{
    const uint32_t after[6] = {style, heading, shown, colour(l->port, paint), 0x10, last};
    return on_panel(l, ITEM_LABEL, text, width, height, x, &y, 1, after, 6);
}

/* A setting's heading and its field: a number (0x4601c0) whose value is at `value`. */
static uint32_t number(Lobby *l, uint32_t x, uint32_t y, uint32_t width, uint32_t value,
                       uint32_t getter, uint32_t kind, uint32_t limit, uint32_t text,
                       uint32_t handler)
{
    const uint32_t before[10] = {
        value, getter, colour(l->port, ITEM_COLOUR), 0x10, kind, kind == 2 ? 0 : 1, 0, limit,
        text,  handler};
    const uint32_t last = 0;
    return on_panel(l, ITEM_NUMBER, x, y, width, ROW_HEIGHT, before, 10, &last, 1);
}

static void heading(Lobby *l, uint32_t text, uint32_t x, uint32_t y, uint32_t width, uint32_t style,
                    uint32_t right, uint32_t paint)
{
    box(l, LABEL_BOX_LINE, width, ROW_HEIGHT, x, y, 0);
    label(l, text, width, ROW_HEIGHT, x, y, style, right, 0, paint, 0);
}

/* The game's settings: two rows of a heading and a number field each side. */
static void settings(Lobby *l)
{
    Port *port = l->port;
    const uint32_t first = l->y + 0x1b;
    const uint32_t second = l->y + 0x32;
    heading(l, 0x50e42c, PANEL_X, first, 0xa9, 7, 0, LABEL_COLOUR);
    number(l, 0xb0, first, 0xd0, port_u32(port, 0x532bec, 0), 0x415fc0, 2, 0xe, 0x50e438, 0x444c80);
    heading(l, 0x50e43f, 0x17f, first, 0x55, 0, 1, LABEL_COLOUR);
    const uint32_t first_name = port_u32(port, 0x532c90 + 4 * port_u32(port, 0x4f8160, 0), 0);
    const uint32_t named =
        number(l, 0x1d3, first, 0x91, first_name, 0, 0, 0x14, 0x50e444, 0x448140);
    port_set8(port, named, 0x52, 0);
    heading(l, 0x50e445, PANEL_X, second, 0xa9, 7, 0, LABEL_COLOUR);
    const uint32_t wide = number(l, 0xb0, second, 0x124, port_u32(port, 0x532bf0, 0), 0x415fd0, 2,
                                 0x14, 0x50e451, 0x444c80);
    port_set32(port, wide, 0, 0x1f4);
    heading(l, 0x50e452, 0x1d3, second, 0x40, 0, 1, LABEL_COLOUR);
    const uint32_t narrow = number(l, 0x212, second, 0x52, port_u32(port, 0x532bf4, 0), 0x415fe0, 2,
                                   5, 0x50e457, 0x444c80);
    port_set32(port, narrow, 0, 0x1f5);
}

/* The message lines, a box of four from `top`. */
static void messages(Lobby *l, uint32_t top)
{
    Port *port = l->port;
    const uint32_t frame_box = box(l, LABEL_BOX_LINE, 0x25c, 0x60, PANEL_X, top, 1);
    port_call(port, SET_BORDER, frame_box, 0x7f7f7f, 0, 0);
    port_call(port, SET_FILL, frame_box, 0xffffff, 0, 0);
    for (uint32_t i = 0; i < LIST_LINES; i++)
    {
        const uint32_t before[3] = {ROW_HEIGHT, PANEL_X, top + ROW_HEIGHT * i};
        const uint32_t after[5] = {1, colour(port, LINE_COLOUR), 0x10, 5, 0};
        const uint32_t line =
            on_panel(l, ITEM_FIELD, 0x50e458, font(port, FONT), 0, 0x25c, before, 3, after, 5);
        port_call(port, SET_CLICK, line, 0x446440, 0, 0);
        port_set8(port, line, 0x110, 0);
        port_set8(port, line, 0x52, 0xd);
        port_set32(port, line, 0x70, i);
        port_set8(port, port_u32(port, line, 0x160), 0x52, 0xd);
    }
}

typedef struct
{
    uint32_t x, width;
    uint32_t heading;
    uint32_t getter, slot; /* the player's value, into this frame string */
    uint32_t click;
} Column;

/* The players' table's columns: each heading, and the value each row shows. */
static const Column COLUMN[COLUMNS] = {{8, 0xc8, 0x50e459, 0x4b73a0, 0x1b8, 0x445f00},
                                       {0xcf, 0x50, 0x50e466, 0x4b7300, 0x124, 0x445fc0},
                                       {0x11e, 0x3c, 0x50e46c, 0x4b7080, 0x120, 0x446080},
                                       {0x159, 0x3c, 0x50e471, 0x4b7120, 0x1b4, 0x446140},
                                       {0x194, 0x50, 0x50e476, 0x4b71c0, 0x11c, 0x446200},
                                       {0x1e3, 0x50, 0x50e47c, 0x4b7260, 0x1b0, 0x4462c0},
                                       {0x232, 0x32, 0x50e482, 0x4b7420, 0x118, 0x446380}};

/* The new player's row: a name field, a choice per middle column and a last field. */
typedef struct
{
    uint32_t slot;  /* the shown value's name */
    uint32_t value; /* where the value is */
    uint32_t count, wraps, kind;
    uint32_t namer;
} Choice;

static const Choice CHOICE[5] = {{TEXT_C88, 0x532c88, 2, 1, 3, 0x415f90},
                                 {TEXT_C44, 0x532c44, 3, 0, 2, 0x415f10},
                                 {TEXT_C50, 0x532c50, 0xa, 0, 2, 0x415f30},
                                 {TEXT_C78, 0x532c78, 2, 1, 3, 0x415f50},
                                 {TEXT_C80, 0x532c80, 2, 1, 3, 0x415f70}};

static void players(Lobby *l)
{
    Port *port = l->port;
    const uint32_t headings = l->y + 0xac;
    for (unsigned c = 0; c < COLUMNS; c++)
    {
        heading(l, COLUMN[c].heading, COLUMN[c].x, headings, COLUMN[c].width, 8, c != 0,
                CELL_COLOUR);
    }

    const uint32_t entry = l->y + 0xc3;
    number(l, 8, entry, 0xc8, port_u32(port, 0x532be8, 0), 0x415fb0, 2, 0xd, 0x50e485, 0x444c80);
    for (unsigned c = 0; c < 5; c++)
    {
        const Choice *ch = &CHOICE[c];
        const uint32_t before[12] = {text_at(l, ch->slot),
                                     ch->value,
                                     ch->count,
                                     ch->wraps,
                                     ch->kind,
                                     ch->namer,
                                     0,
                                     0x447f40,
                                     colour(port, ITEM_COLOUR),
                                     0x10,
                                     0,
                                     1};
        const uint32_t last = 0;
        on_panel(l, ITEM_CHOICE, COLUMN[c + 1].x, entry, COLUMN[c + 1].width, ROW_HEIGHT, before,
                 12, &last, 1);
    }
    const uint32_t last_before[3] = {ROW_HEIGHT, COLUMN[6].x, entry};
    const uint32_t last_after[5] = {0, colour(port, ITEM_COLOUR), 0x10, 0, 1};
    const uint32_t last_field = on_panel(l, ITEM_FIELD, 0x50e48a, font(port, FONT), 0,
                                         COLUMN[6].width, last_before, 3, last_after, 5);
    port_call(port, SET_CLICK, last_field, 0, 0, 0);

    /* The table, with its scroll bar. */
    const uint32_t top = l->y + 0xda;
    box(l, LABEL_BOX_LINE, 0x25c, 0x78, PANEL_X, top, 0);
    const uint32_t bar = box(l, LABEL_BOX_LINE, 0x16, 0x78, 0x264, top, 0);
    port_call(port, SET_FILL, bar, 0xff000000, 0, 0);
    const uint32_t scroll[11] = {0,    0, 0, 0,       2, 0x418100, colour(port, BUTTON_COLOUR),
                                 0x10, 0, 1, 0x448180};
    const uint32_t last = 0;
    on_panel(l, ITEM_SCROLL, 0x264, top, 0x16, 0x78, scroll, 11, &last, 1);
    for (uint32_t row = 0; row < PLAYER_ROWS; row++)
    {
        const uint32_t y = top + ROW_HEIGHT * row;
        const uint32_t line = box(l, LABEL_BOX_LINE, 0x25c, ROW_HEIGHT, PANEL_X, y, 0);
        port_set8(port, line, 0x110, 0);
        port_call(port, SET_CLICK, line, 0x4465a0, 0, 0);
        port_set32(port, line, 0x70, row);
        port_call(port, SET_FILL, line, 0xff000000, 0, 0);
        for (unsigned c = 0; c < COLUMNS; c++)
        {
            const Column *col = &COLUMN[c];
            const uint32_t player = port_u32(port, FIRST_SHOWN, 0) + row;
            const uint32_t value =
                port_call(port, col->getter, PLAYER_LIST, l->frame - col->slot, player, 0);
            const uint32_t before[3] = {ROW_HEIGHT, col->x, y};
            const uint32_t after_name[5] = {0, colour(port, CELL_COLOUR), 0x10, 2, 0};
            const uint32_t after_value[5] = {0, colour(port, CELL_COLOUR), 0x10, 0, 1};
            const uint32_t cell =
                on_panel(l, ITEM_FIELD, port_u32(port, value, 0), font(port, FONT), 0, col->width,
                         before, 3, c == 0 ? after_name : after_value, 5);
            port_call(port, STRING_RELEASE, l->frame - col->slot, 0, 0, 0);
            port_call(port, SET_CLICK, cell, col->click, 0, 0);
            port_set8(port, cell, 0x110, 0);
            port_set8(port, cell, 0x52, 0xd);
            port_set32(port, cell, 0x70, row);
        }
    }
}

/* The three buttons along the bottom and the name field, each after a marker box. */
static void buttons(Lobby *l)
{
    Port *port = l->port;
    const uint32_t y = l->y + 0x153;
    static const uint32_t TEXT[3] = {0x50e48c, 0x50e494, 0x50e499};
    static const uint32_t STATE[3] = {0x4163b0, 0x416900, 0x416140};
    static const uint32_t CLICK[3] = {0x445a00, 0x445b90, 0x445770};
    uint32_t x = PANEL_X;
    for (unsigned i = 0; i < 4; i++, x += 0x8e)
    {
        box(l, LABEL_BOX, 0x24, 0x11, x, y, 1);
        if (i < 3)
        {
            const uint32_t before[7] = {
                TEXT[i], STATE[i], colour(port, ITEM_COLOUR), 0x10, CLICK[i], 0, 1};
            const uint32_t last = 1;
            const uint32_t button =
                on_panel(l, ITEM_BUTTON, x + 0x25, y, 0x68, 0x16, before, 7, &last, 1);
            if (i == 1)
            {
                port_set8(port, button, 0x52, 0);
            }
        }
        else
        {
            const uint32_t name = l->frame - NAME_TEXT;
            port_call(port, STRING_INIT, name, 0x50e4a0, 0, 0);
            port_call(port, STRING_SET, name, vertrix_lift_edx, 0, 0);
            const uint32_t before[3] = {0x16, x + 0x25, y};
            const uint32_t after[5] = {1, colour(port, ITEM_COLOUR), 0x10, 0, 1};
            on_panel(l, ITEM_FIELD, port_u32(port, name, 0), font(port, NAME_FONT), 1, 0x68, before,
                     3, after, 5);
            port_call(port, STRING_RELEASE, name, 0, 0, 6);
        }
    }
    box(l, LABEL_BOX, 0x24, 0x11, x, y, 1);
}

uint32_t vertrix_port_lobby_launch_screen_4633b0(PORT_SIGNATURE)
{
    Port port;
    uint8_t stack[BELOW + 8];
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    const uint32_t mode = entry->eax;
    Lobby l = {&port, entry->esp - 4, mode == 1 ? 0xd2 : 0x5a};

    port_set32(&port, 0x532c38, 0, 0xffffffff);
    if (mode == 1)
    {
        port_set32(&port, LEVEL, 0, port_u32(&port, 0x4f8164, 0));
    }
    else
    {
        port_set32(&port, LEVEL, 0, port_u32(&port, 0x4f8160, 0));
        port_set32(&port, 0x532c38, 0, port_u32(&port, LEVEL, 0));
    }
    port_set32(&port, FIRST_SHOWN, 0, 0);
    port_set32(&port, 0x532c18, 0, 0);
    port_set32(&port, 0x532c40, 0, 0);
    port_set32(&port, 0x532c00, 0, 0xffffffff);
    port_call(&port, RESET, 0x532c24, 0, 0, 0);
    port_call(&port, CLEAR_PLAYERS, PLAYER_LIST, 0, 0, 0);
    port_call(&port, RESET_NETWORK, 0x5bb254, 0, 0, 0);

    /* The settings' value names. */
    static const uint32_t TEXTS[6] = {TEXT_C44, TEXT_C50, TEXT_C78, TEXT_C80, TEXT_C90, TEXT_C88};
    for (unsigned i = 0; i < 6; i++)
    {
        port_call(&port, STRING_INIT, l.frame - TEXTS[i], 0, 0, 0);
    }
    static const struct
    {
        uint32_t slot, value, table, names, count;
    } NAMES[6] = {
        {TEXT_C80, 0x532be0, 0x532c80, 0x4f8120, 2},   {TEXT_C78, 0x532bdc, 0x532c78, 0x4f8118, 2},
        {TEXT_C50, 0x532bd8, 0x532c50, 0x4f80f0, 0xa}, {TEXT_C44, 0x532bd4, 0x532c44, 0x4f80e4, 3},
        {TEXT_C90, LEVEL, 0x532c90, 0x4f8170, 2},      {TEXT_C88, 0x532be4, 0x532c88, 0x4f8168, 2}};
    for (unsigned i = 0; i < 6; i++)
    {
        const uint32_t name = port_call(&port, VALUE_NAME, port_u32(&port, NAMES[i].value, 0),
                                        NAMES[i].table, NAMES[i].names, NAMES[i].count);
        port_call(&port, STRING_SET, l.frame - NAMES[i].slot, name, 0, 0);
    }

    /* The title. */
    box(&l, LABEL_BOX, 0x25c, 0x11, PANEL_X, l.y + 9, 1);
    const uint32_t title = label(&l, mode == 1 ? 0x50e417 : 0x50e424, 0x25c, 0x1a, PANEL_X, l.y, 0,
                                 1, 1, TITLE_COLOUR, 1);
    if (mode == 1)
    {
        port_call(&port, SET_CLICK, title, 0x448010, 0, 0);
    }

    if (mode == 0)
    {
        settings(&l);
        messages(&l, l.y + 0x4b);
        players(&l);
        buttons(&l);
    }
    else
    {
        messages(&l, l.y + 0x1b);
    }

    /* The menu's actor. */
    uint32_t actor = port_call(&port, ALLOCATE, 0x15c, 0, 0, 0);
    if (actor != 0)
    {
        actor = port_call(&port, CONSTRUCT, actor, 6, 0, 0);
    }
    port_call(&port, SET_UPDATE, actor, MENU_UPDATE, 0, 0);
    port_call(&port, REGISTER, ACTORS, actor, 0, 0);
    port_set32(&port, MENU_ACTOR, 0, 0);
    port_call(&port, THROW, 0, vertrix_lift_edx, 0, 0);
    return port_return(&port, port.env.chain, entry->edx);
}
