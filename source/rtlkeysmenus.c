#include "rtlkeysmenus.h"

/* The key-configuration menu: a 0x1f9 x 0xe5 panel centred on the back buffer with the two
 * players' four movement keys and their drop key, the control and speed choices and the name
 * field, then the menu's actor. */

enum
{
    BELOW = 0x19c,
    /* Strings and tables in the frame, below the saved ebp. */
    CONTROL_TEXT = 0x10c, /* then the two speed texts, 4 apart */
    LABELS = 0x174,       /* nine label strings */
    KEY_TEXTS = 0x198,    /* each key's text, nine */
    KEY_CODES = 0x150,    /* where each key's code is, nine */
    KEY_NAME = 0xfc,      /* a key's name, for each key drawn (0xfc, 0xf8, 0x100) */
    KEY_COUNT = 9,

    PANEL_WIDTH = 0x1f9,
    PANEL_HEIGHT = 0xe5,
    BACK_IMAGE = 0x558c7c,
    IMAGE_WIDTH = 4,
    IMAGE_HEIGHT = 8,
    TEXT_COLOUR = 0x4f9bf8, /* bytes */
    ITEM_COLOUR = 0x4f9bfd,
    FIELD_COLOUR = 0x4f9bfc,
    FIELD_WIDTH = 0x4f7b9c, /* a word */

    STRING_INIT = 0x4ca070,
    STRING_ASSIGN = 0x4ca280,
    STRING_SET = 0x4ca370,
    STRING_RELEASE = 0x4ca210,
    TABLE_VALUE = 0x415ed0,
    KEY_NAME_OF = 0x416c10,
    LABEL_BOX = 0x460a40,
    LABEL_BOX_LINE = 0x460ad0,
    ITEM_LABEL = 0x460c50,
    ITEM_KEY = 0x460df0,
    ITEM_CHOICE = 0x460fa0,
    ITEM_FIELD = 0x460b60,
    ALLOCATE = 0x4ca000,
    CONSTRUCT = 0x4abd70,
    SET_UPDATE = 0x4ac8f0,
    REGISTER = 0x4b5e70,
    THROW = 0x4cda10,

    CONTROL_VALUE = 0x532b64,
    CONTROL_SHOWN = 0x532b68,
    CONTROL_TABLE = 0x532b20,
    SPEED_ONE = 0x532b80,
    SPEED_TWO = 0x532b84,
    SPEED_TABLE = 0x532b08,
    MENU_ACTOR = 0x532a48,
    ACTORS = 0x54671c,
    MENU_UPDATE = 0x45c6e0
};

/* The rows' labels. */
static const uint32_t LABEL_TEXTS[KEY_COUNT] = {0x50e3cb, 0x50e3d0, 0x50e3d6, 0x50e3de, 0x50e3e3,
                                                0x50e3e8, 0x50e3ee, 0x50e3f6, 0x50e3fb};

typedef struct
{
    Port *port;
    uint32_t frame;
    uint32_t x, y; /* the panel's corner, as signed words */
} Menu;

/* A word, sign-extended, as the original passes the coordinates. */
static uint32_t word(uint32_t value)
{
    return (uint32_t)(int32_t)(int16_t)value;
}

static uint32_t colour(Port *port, uint32_t at)
{
    return (uint32_t)(int32_t)(int8_t)port_u8(port, at, 0);
}

/* A call whose stack holds `before`, the panel (width, height, x, y) and `after`. */
static uint32_t on_panel(Menu *m, uint32_t routine, uint32_t eax, uint32_t edx, uint32_t ebx,
                         uint32_t ecx, const uint32_t *before, unsigned nbefore,
                         const uint32_t *after, unsigned nafter)
{
    uint32_t stack[20];
    unsigned n = 0;
    for (unsigned i = 0; i < nbefore; i++)
    {
        stack[n++] = before[i];
    }
    stack[n++] = PANEL_WIDTH;
    stack[n++] = PANEL_HEIGHT;
    stack[n++] = m->x;
    stack[n++] = m->y;
    for (unsigned i = 0; i < nafter; i++)
    {
        stack[n++] = after[i];
    }
    return port_call_stack(m->port, routine, eax, edx, ebx, ecx, stack, n);
}

/* A box or line of the panel (0x460a40, 0x460ad0) at (x, y). */
static void box(Menu *m, uint32_t routine, uint32_t eax, uint32_t edx, uint32_t x, uint32_t y,
                uint32_t last)
{
    on_panel(m, routine, eax, edx, x, y, NULL, 0, &last, 1);
}

/* A text at (x, row): its string, the column style and whether it is a heading. */
static void label(Menu *m, uint32_t text, uint32_t x, uint32_t row, uint32_t style,
                  uint32_t heading)
{
    const uint32_t after[6] = {style, heading, 1, colour(m->port, TEXT_COLOUR), 0x10, 1};
    on_panel(m, ITEM_LABEL, text, 0xa9, 0x1a, x, &row, 1, after, 6);
}

/* Key `index`'s button at (x, row), width `width`: its name from 0x416c10 in the frame slot
 * `slot`, released after. */
static void key(Menu *m, uint32_t index, uint32_t x, uint32_t row, uint32_t width, uint32_t slot)
{
    Port *port = m->port;
    const uint32_t code = port_u32(port, m->frame - KEY_CODES + 4 * index, 0);
    const uint32_t name =
        port_call(port, KEY_NAME_OF, m->frame - slot, port_u16(port, code, 0), 0, 0);
    const uint32_t before[7] = {port_u32(port, name, 0),
                                port_u32(port, m->frame - KEY_TEXTS + 4 * index, 0),
                                colour(port, ITEM_COLOUR),
                                0x10,
                                0x448810,
                                0,
                                1};
    const uint32_t last = 0;
    on_panel(m, ITEM_KEY, x, row, width, 0x1a, before, 7, &last, 1);
    port_call(port, STRING_RELEASE, m->frame - slot, 0, 0, 0);
}

/* A choice at (x, row) showing `text` from `table` (`count` values), with its handlers. */
static void choice(Menu *m, uint32_t x, uint32_t row, uint32_t text, uint32_t table, uint32_t count,
                   uint32_t handler, uint32_t left, uint32_t right)
{
    const uint32_t before[12] = {
        text, table, count, 0, 2, handler, left, right, colour(m->port, ITEM_COLOUR), 0x10, 0, 1};
    const uint32_t last = 0;
    on_panel(m, ITEM_CHOICE, x, row, 0xa9, 0x1a, before, 12, &last, 1);
}

/* The text of `value` in `table` (0x415ed0), into the frame string at `slot`. */
static void set_value_text(Port *port, uint32_t frame, uint32_t slot, uint32_t value,
                           uint32_t table, uint32_t format, uint32_t count)
{
    const uint32_t text = port_call(port, TABLE_VALUE, value, table, format, count);
    port_call(port, STRING_SET, frame - slot, text, 0, 0);
}

/* Original 0x4627a0. Its exception frame is left out (docs/NATIVE-PORTS.md); it ends with the
 * runtime's throw (0x4cda10), which the lifted runtime returns from. Returns the caller's exception
 * chain. */
uint32_t vertrix_port_keys_menu_screen_4627a0(PORT_SIGNATURE)
{
    uint8_t stack[BELOW + 8];
    Port port;
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    const uint32_t frame = entry->esp - 4;
    port_set32(&port, frame, 0, entry->ebp);
    for (uint32_t k = 0; k < 3; k++)
    {
        port_call(&port, STRING_INIT, frame - CONTROL_TEXT + 4 * k, 0, 0, 0);
    }
    const uint32_t control = port_u32(&port, CONTROL_VALUE, 0);
    port_set32(&port, CONTROL_SHOWN, 0, control);
    set_value_text(&port, frame, CONTROL_TEXT, control, CONTROL_TABLE, 0x4f8134, 5);
    set_value_text(&port, frame, CONTROL_TEXT - 4, port_u32(&port, SPEED_ONE, 0), SPEED_TABLE,
                   0x4f8148, 6);
    set_value_text(&port, frame, CONTROL_TEXT - 8, port_u32(&port, SPEED_TWO, 0), SPEED_TABLE,
                   0x4f8148, 6);

    const uint32_t image = port_u32(&port, BACK_IMAGE, 0);
    const uint32_t x0 = (port_u32(&port, image, IMAGE_WIDTH) - PANEL_WIDTH) >> 1;
    const uint32_t y0 = port_u16(&port, image, IMAGE_HEIGHT) - 0x10d;
    Menu m = {&port, frame, word(x0), word(y0)};
    const uint32_t x_left = word(x0 + 0xa8);
    const uint32_t x_right = word(x0 + 0x150);
    const uint32_t title = word(y0 + 1);
    const uint32_t keys_top = word(y0 + 0x1a);
    const uint32_t speed_row = word(y0 + 0x97);
    const uint32_t control_row = word(y0 + 0xb0);
    const uint32_t name_row = word(y0 + 0xcb);

    /* The headings: the panel's title and the two players' columns. */
    box(&m, LABEL_BOX, 0xa9, 0x1a, m.x, title, 1);
    label(&m, 0x50e3b6, m.x, title, 0, 1);
    box(&m, LABEL_BOX_LINE, 0xa9, 0x1a, x_left, title, 1);
    box(&m, LABEL_BOX_LINE, 0xa9, 0x1a, x_right, title, 1);
    label(&m, 0x50e3bb, x_left, title, 0xa, 1);
    label(&m, 0x50e3c3, x_right, title, 0xa, 1);
    box(&m, LABEL_BOX_LINE, 0xa9, 0x7e, m.x, keys_top, 1);

    /* The key rows: up, down, left and right for both players, then the drop key. */
    port_copy(&port, frame - LABELS, 0x54680c, 4 * KEY_COUNT);
    for (uint32_t k = 0; k < KEY_COUNT; k++)
    {
        port_call(&port, STRING_ASSIGN, frame - LABELS + 4 * k, LABEL_TEXTS[k], 0, 0);
    }
    port_copy(&port, frame - KEY_TEXTS, 0x4fd504, 4 * KEY_COUNT);
    port_copy(&port, frame - KEY_CODES, 0x4fd528, 4 * KEY_COUNT);
    uint32_t row = keys_top;
    for (uint32_t i = 0; i < 4 && !port.env.failed; i++)
    {
        label(&m, port_u32(&port, frame - LABELS + 4 * i, 0), m.x, row, 0xa, 0);
        key(&m, i, x_left, row, 0xa9, KEY_NAME);
        key(&m, 4 + i, x_right, row, 0xa9, KEY_NAME - 4);
        row = word(row + 0x19);
    }
    label(&m, port_u32(&port, frame - LABELS + 4 * 8, 0), m.x, row, 0xa, 0);
    key(&m, 8, x_left, row, 0x151, KEY_NAME + 4);

    /* The speeds, the control and the name. */
    box(&m, LABEL_BOX_LINE, 0xa9, 0x1a, m.x, speed_row, 1);
    label(&m, 0x50e401, m.x, speed_row, 0xa, 0);
    choice(&m, x_left, speed_row, port_u32(&port, frame - CONTROL_TEXT + 4, 0), SPEED_TABLE, 6,
           0x416bd0, 0, 0x447f40);
    choice(&m, x_right, speed_row, port_u32(&port, frame - CONTROL_TEXT + 8, 0), SPEED_TABLE, 6,
           0x416bf0, 0, 0x447f40);
    box(&m, LABEL_BOX_LINE, 0xa9, 0x1a, m.x, control_row, 1);
    label(&m, 0x50e407, m.x, control_row, 0xa, 0);
    choice(&m, x_left, control_row, port_u32(&port, frame - CONTROL_TEXT, 0), CONTROL_TABLE, 5,
           0x416bb0, 0x448680, 0x448260);
    box(&m, LABEL_BOX_LINE, 0xa9, 0x1a, x_right, control_row, 0);
    box(&m, LABEL_BOX, 0xbc, 0x11, m.x, name_row, 0);
    const uint32_t before[3] = {0x1a, word(x0 + 0xbd), name_row};
    const uint32_t after[5] = {0, colour(&port, FIELD_COLOUR), 0x10, 0, 1};
    on_panel(&m, ITEM_FIELD, 0x50e410, word(port_u16(&port, FIELD_WIDTH, 0)), 1, 0x7f, before, 3,
             after, 5);
    box(&m, LABEL_BOX, 0xbc, 0x11, word(x0 + 0x13d), name_row, 0);

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
