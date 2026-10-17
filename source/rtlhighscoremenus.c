#include "rtlhighscoremenus.h"

enum
{
    /* The frame below the return slot, and the string local the callees reach by address (at
     * 0x90 below the original's ebp, entry->esp - 4). */
    BELOW = 0xc4,
    TEXT = 0x90,

    SCREEN = 0x558c7c,
    SCREEN_WIDTH = 0x4,
    SCREEN_HEIGHT = 0x8,
    FONT_TITLE = 0x4f9bf5,
    FONT_RETURN = 0x4f9bf9,
    RETURN_X = 0x4f7b92,

    /* The panel: 0x11b by 0xb4, centred across, 0xdc above the bottom. */
    PANEL_WIDTH = 0x11b,
    PANEL_HEIGHT = 0xb4,
    PANEL_BOTTOM = 0xdc,
    ROWS = 5,
    ROW_STEP = 0x19,
    FIRST_ROW_BOTTOM = 0xc1,
    BUTTONS_BOTTOM = 0x42,

    /* The rows: the rank, the name and the score; the name of the new entry is typed in. */
    NAMES = 0x5332a8,
    SCORES = 0x533294,
    ROW_COLOURS = 0x4fd54c,
    RANK_FORMAT = 0x50e4ad,
    TITLE_TEXT = 0x50e4a7,
    RETURN_TEXT = 0x50e4b4,
    ENTRY_LETTERS = 0x50e4b0,
    ENTRY_KEYS = 0x417880,
    ENTRY_KEY_STEP = 0x10,
    ITEM_PAINT = 0x45c8e0,
    ENTRY_PAINT = 0x45cc40,
    ITEM_SPRITE = 0x160,
    SPRITE_COLOUR = 0x4c,
    SPRITE_MODE = 0x52,
    SPRITE_STAGE_A = 0x93,
    SPRITE_STAGE_C = 0x95,
    ROW_MODE = 0xd,

    MENU_ACTOR_BYTES = 0x15c,
    MENU_UPDATE = 0x45c6e0,
    OBJECTS = 0x54671c,
    MENU_CURSOR = 0x532a48,

    STRING_INIT = 0x4ca070,
    LABEL_BOX = 0x460a40,
    TITLE_ITEM = 0x460c50,
    RANK_OF = 0x417840,
    PRINT = 0x4cdfb0,
    TEXT_ITEM = 0x460df0,
    STRING_ASSIGN = 0x4ca310,
    SCORE_TEXT = 0x417790,
    ENTRY_ITEM = 0x4601c0,
    BUTTON_ITEM = 0x460b60,
    GET_MEM = 0x4ca000,
    ACTOR_RESET = 0x4abd70,
    ACTOR_SET_UPDATE = 0x4ac8f0,
    LIST_APPEND = 0x4b5e70,
    STRING_RELEASE = 0x4ca210
};

/* The original keeps its layout in 16-bit locals and hands them over sign-extended. */
static uint32_t word(uint32_t value)
{
    return (uint32_t)(int32_t)(int16_t)value;
}

static uint32_t font(Port *port, uint32_t at)
{
    return (uint32_t)((int32_t)port_u32(port, at, 0) >> 24);
}

/* A row item's sprite: mode 0xd, stages, and the row's colour. */
static void style_item(Port *port, uint32_t item, uint32_t colour)
{
    port_set8(port, port_u32(port, item, ITEM_SPRITE), SPRITE_MODE, ROW_MODE);
    port_set8(port, port_u32(port, item, ITEM_SPRITE), SPRITE_STAGE_C, 0x4);
    port_set8(port, port_u32(port, item, ITEM_SPRITE), SPRITE_STAGE_A, 0x1);
    port_set16(port, port_u32(port, item, ITEM_SPRITE), SPRITE_COLOUR, colour);
}

/* A text item (0x460df0) at x, y in the panel, its text the string local's. */
static uint32_t text_item(Port *port, uint32_t text, uint32_t x, uint32_t y, uint32_t ebx,
                          uint32_t panel_x, uint32_t panel_y, uint32_t alternate)
{
    const uint32_t stack[12] = {port_u32(port, text, 0),
                                0,
                                0xa,
                                0x10,
                                ITEM_PAINT,
                                0,
                                1,
                                PANEL_WIDTH,
                                PANEL_HEIGHT,
                                panel_x,
                                panel_y,
                                alternate};
    return port_call_stack(port, TEXT_ITEM, x, y, ebx, 0x1a, stack, 12);
}

/* Original 0x4651b0 (eax = the row of a new entry, or another value for none): builds the
 * high-score menu. A 0x11b by 0xb4 panel centred across the screen, 0xdc above its bottom, with
 * the title; then five rows 0x19 apart: the rank (formatted from 0x417840), the name (typed in
 * on the new entry's row, with the letter keys 0x417880 + 0x10 * row) and the score
 * (0x417790), each in the row's colour from 0x4fd54c, alternating a flag per row. Then two more
 * boxes, the RETURN button, and the menu actor (updated by 0x45c6e0) appended to the object list,
 * the menu cursor 0x532a48 cleared. Returns the exception chain the caller had and the caller's
 * edx. Callees get the registers the original leaves in them where they read them (the format
 * call ecx, which holds the panel's x on the first row and the row count above 0x1a later). The
 * exception frame at fs:[0] is left out (docs/NATIVE-PORTS.md). */
uint32_t vertrix_port_high_scores_menu_build_4651b0(PORT_SIGNATURE)
{
    Port port;
    uint8_t stack[BELOW + 8];
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    const uint32_t frame = entry->esp - 4;
    port_set32(&port, frame, 0, entry->ebp);
    const uint32_t chain = port.env.chain;
    const uint32_t entry_row = entry->eax;
    const uint32_t text = frame - TEXT;

    port_call(&port, STRING_INIT, text, 0, 0, 0);
    const uint32_t screen = port_u32(&port, SCREEN, 0);
    const uint32_t height = port_u16(&port, screen, SCREEN_HEIGHT);
    const uint32_t x = word((port_u32(&port, screen, SCREEN_WIDTH) - PANEL_WIDTH) >> 1);
    const uint32_t y = word(height - PANEL_BOTTOM);
    const uint32_t buttons_y = height - BUTTONS_BOTTOM;
    uint32_t row_y = height - FIRST_ROW_BOTTOM;

    const uint32_t box[5] = {PANEL_WIDTH, PANEL_HEIGHT, x, y, 1};
    port_call_stack(&port, LABEL_BOX, PANEL_WIDTH, 0x11, x, word(y + 9), box, 5);
    const uint32_t title[11] = {
        y, PANEL_WIDTH, PANEL_HEIGHT, x, y, 0, 1, 1, font(&port, FONT_TITLE), 0x10, 1};
    port_call_stack(&port, TITLE_ITEM, TITLE_TEXT, PANEL_WIDTH, 0x1a, x, title, 11);

    uint32_t colours[ROWS];
    for (unsigned i = 0; i < ROWS; i++)
    {
        colours[i] = port_u32(&port, ROW_COLOURS + i * 4, 0);
    }
    const uint32_t name_x = word(x + 0x25);
    const uint32_t name_width = 0x4c;
    uint32_t alternate = 0;
    uint32_t print_ecx = x;
    for (uint32_t row = 0; row < ROWS && !port.env.failed; row++)
    {
        const uint32_t rank = port_call(&port, RANK_OF, row, 0, 0, 0) & 0xff;
        const uint32_t format[3] = {text, RANK_FORMAT, rank};
        port_call_stack(&port, PRINT, rank, 0, 0, print_ecx, format, 3);
        const uint32_t rank_item = text_item(&port, text, x, word(row_y), 0x26, x, y, alternate);
        style_item(&port, rank_item, colours[row]);

        if (row == entry_row)
        {
            const uint32_t keys = ENTRY_KEYS + row * ENTRY_KEY_STEP;
            const uint32_t entry_stack[15] = {port_u32(&port, NAMES + row * 4, 0),
                                              keys,
                                              0xa,
                                              0x10,
                                              0,
                                              1,
                                              1,
                                              3,
                                              ENTRY_LETTERS,
                                              ENTRY_PAINT,
                                              PANEL_WIDTH,
                                              PANEL_HEIGHT,
                                              x,
                                              y,
                                              alternate};
            const uint32_t name_item = port_call_stack(&port, ENTRY_ITEM, name_x, word(row_y),
                                                       word(name_width), 0x1a, entry_stack, 15);
            style_item(&port, name_item, colours[row]);
        }
        else
        {
            port_call(&port, STRING_ASSIGN, text, NAMES + row * 4, 0, 0);
            const uint32_t name_item =
                text_item(&port, text, name_x, word(row_y), 0x4c, x, y, alternate);
            style_item(&port, name_item, colours[row]);
        }

        port_call(&port, SCORE_TEXT, port_u32(&port, SCORES + row * 4, 0), text, alternate, 0x1a);
        const uint32_t score_item = text_item(&port, text, word(name_x + name_width - 1),
                                              word(row_y), 0xab, x, y, alternate);
        style_item(&port, score_item, colours[row]);
        print_ecx = ((row + 1) << 8) | 0x1a;
        row_y += ROW_STEP;
        alternate = 1 - alternate;
    }

    const uint32_t frame_box[5] = {PANEL_WIDTH, PANEL_HEIGHT, x, y, alternate};
    port_call_stack(&port, LABEL_BOX, 0x4d, 0x11, x, word(buttons_y), frame_box, 5);
    const uint32_t button[12] = {0x1a,
                                 word(x + 0x4e),
                                 word(buttons_y),
                                 PANEL_WIDTH,
                                 PANEL_HEIGHT,
                                 x,
                                 y,
                                 alternate,
                                 font(&port, FONT_RETURN),
                                 0x10,
                                 0,
                                 1};
    port_call_stack(&port, BUTTON_ITEM, RETURN_TEXT, word(port_u32(&port, RETURN_X, 0) >> 16), 1,
                    0x7f, button, 12);
    const uint32_t last_box[5] = {PANEL_WIDTH, PANEL_HEIGHT, x, y, alternate};
    port_call_stack(&port, LABEL_BOX, 0x4d, 0x11, word(x + 0xce), word(buttons_y), last_box, 5);

    uint32_t actor = port_call(&port, GET_MEM, MENU_ACTOR_BYTES, 0, 0, 0);
    if (actor != 0)
    {
        actor = port_call(&port, ACTOR_RESET, actor, 0, 1, 2);
    }
    port_call(&port, ACTOR_SET_UPDATE, actor, MENU_UPDATE, 0, 0);
    port_call(&port, LIST_APPEND, OBJECTS, actor, 0, 0);
    port_set32(&port, MENU_CURSOR, 0, 0);
    port_call(&port, STRING_RELEASE, text, 0, 0, 0);
    return port_return(&port, chain, entry->edx);
}
