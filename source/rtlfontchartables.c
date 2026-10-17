#include "rtlfontchartables.h"

/* Builds the character-to-glyph tables of the game's fonts: each table gets its glyph size, then
 * the letters A to Z and the digits 0 to 9 as runs of glyph numbers, then the font's punctuation.
 * Three tables take their size from an image of the font set at 0x546538. */

enum
{
    TABLE_INIT = 0x48abe0,
    TABLE_SET = 0x48abf0,
    FONT_IMAGES = 0x546538,
    FONT_IMAGE = 0x4877f0,
    IMAGE_WIDTH = 4,
    IMAGE_HEIGHT = 8,

    /* The size of an image-sized table: the image's, rounded down to even, plus a margin. */
    IMAGE_MARGIN_WIDTH = 0x23,
    IMAGE_MARGIN_HEIGHT = 0x1e
};

/* A table with its glyph width and height (0: the image's), the glyph numbers of A and 0 relative
 * to the characters, whether the digits come first, and the routine that adds its punctuation
 * (0: none). */
typedef struct
{
    uint32_t table;
    uint32_t width;
    uint32_t height;
    int32_t letters;
    int32_t digits;
    int digits_first;
    uint32_t punctuation;
} FontTable;

static const FontTable TABLES[] = {
    {0x541988, 0x23, 0x1e, -0x11, 0x1a, 0, 0x43f480},
    {0x541b94, 0x23, 0x1e, -0x35, -0xa, 0, 0x43f480},
    {0x541da0, 0x23, 0x1e, -0x35, 0x1a, 0, 0x43f480},
    {0x541fac, 0x23, 0x1e, -0x11, 0x1a, 0, 0x43f480},
    {0x5421b8, 0x1c, 0x1e, -0x35, 0x24, 0, 0x43f480},
    {0x543a48, 0x1c, 0x1e, -0x35, 0x1d6, 0, 0x43f480},
    {0x543c54, 0x1c, 0x1e, -0x35, 0x1e0, 0, 0x43f480},
    {0x543e60, 0x1c, 0x1e, -0x35, 0x1ea, 0, 0x43f480},
    {0x5423c4, 0xd, 0xc, 0x29, 0x54, 0, 0x43f630},
    {0x5425d0, 0xe, 0x10, 0x57, 0x5e, 1, 0},
};

static const FontTable SMALL_TABLES[] = {
    {0x542e00, 0x12, 0xe, 0xb1, 0xdc, 0, 0x43f710},
    {0x54300c, 0xd, 0xc, 0xe1, 0x10c, 0, 0x43f7f0},
    {0x543218, 0x12, 0xe, 0x111, 0x13c, 0, 0x43f8d0},
    {0x543424, 0xd, 0xc, 0x141, 0x16c, 0, 0x43f9b0},
    {0x543630, 0x12, 0xe, 0x171, 0x19c, 0, 0x43fa90},
    {0x54383c, 0xd, 0xc, 0x1a1, 0x1cc, 0, 0x43fb70},
};

static void set(Port *port, uint32_t table, uint32_t character, int32_t glyph)
{
    port_call(port, TABLE_SET, table, character, (uint32_t)(int32_t)(int16_t)glyph, 0);
}

static void run(Port *port, uint32_t table, uint32_t first, uint32_t last, int32_t offset)
{
    for (uint32_t c = first; c <= last && !port->env.failed; c++)
    {
        set(port, table, c, (int32_t)c + offset);
    }
}

/* A table sized by the font image `image`: the image's width and height, each rounded down to
 * even, plus the margins. */
static void init_from_image(Port *port, uint32_t table, uint32_t image)
{
    const uint32_t picture = port_call(port, FONT_IMAGE, FONT_IMAGES, image, 0, 0);
    const uint32_t height = (port_u32(port, picture, IMAGE_HEIGHT) >> 1) * 2 + IMAGE_MARGIN_HEIGHT;
    const uint32_t width = (port_u32(port, picture, IMAGE_WIDTH) >> 1) * 2 + IMAGE_MARGIN_WIDTH;
    port_call(port, TABLE_INIT, table, width, height, 0);
}

static void fill(Port *port, const FontTable *font)
{
    if (font->width != 0)
    {
        port_call(port, TABLE_INIT, font->table, font->width, font->height, 0);
    }
    if (font->digits_first)
    {
        run(port, font->table, '0', '9', font->digits);
        run(port, font->table, 'A', 'Z', font->letters);
    }
    else
    {
        run(port, font->table, 'A', 'Z', font->letters);
        run(port, font->table, '0', '9', font->digits);
    }
    if (font->punctuation != 0)
    {
        port_call(port, font->punctuation, font->table, 0, 0, 0);
    }
}

/* Original 0x43fc50. Each punctuation routine runs after its table's letters and digits; the
 * image-sized tables use the font images 6 and 9 (twice). */
uint32_t vertrix_port_font_char_tables_build_43fc50(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    for (size_t i = 0; i < sizeof TABLES / sizeof TABLES[0] && !port.env.failed; i++)
    {
        fill(&port, &TABLES[i]);
    }

    /* The image-sized tables: one full font, and two of two letters each. */
    const FontTable sized = {0x5427dc, 0, 0, 0x71, 0x9c, 0, 0x43f550};
    init_from_image(&port, sized.table, 6);
    fill(&port, &sized);
    init_from_image(&port, 0x5429e8, 9);
    set(&port, 0x5429e8, 'G', 0xe2);
    set(&port, 0x5429e8, 'O', 0xe3);
    init_from_image(&port, 0x542bf4, 9);
    set(&port, 0x542bf4, 'V', 0xe4);
    set(&port, 0x542bf4, 'S', 0xe5);

    for (size_t i = 0; i < sizeof SMALL_TABLES / sizeof SMALL_TABLES[0] && !port.env.failed; i++)
    {
        fill(&port, &SMALL_TABLES[i]);
    }
    return port_return(&port, 0, 0);
}
