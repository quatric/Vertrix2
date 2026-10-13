#include "port_render_rule.h"

enum
{
    FORMAT_ENTRIES = 0x54b808,
    FORMAT_COLOURS = 0x54b83c,
    FORMAT_SELECTS = 0x54b804,
    FORMAT_ENTRY = 0x54d5d4,
    FORMAT_TINT_RED = 0x54d5dc,
    FORMAT_TINT_GREEN = 0x54d5de,
    FORMAT_TINT_BLUE = 0x54d5e0,
    FORMAT_COLOUR = 0x5bc008,
    FORMAT_COLOUR_RED = 0x54d5e8,
    FORMAT_COLOUR_GREEN = 0x54d5e9,
    FORMAT_COLOUR_BLUE = 0x54d5ea,
    FORMAT_COLOUR_HALF = 0x54d5ec,
    FORMAT_SELECT = 0x54d5f0,
    LEVEL_ROWS = 0x558cf0,
    SHADE_ROWS = 0x55f1f8,
    LEVEL_PERCENT = 100,
    SOURCE_LEVELS = 0x55f1f0,
    TARGET_LEVELS = 0x55f1f4,
    SOURCE_SHADES = 0x5785f8,
    TARGET_SHADES = 0x5785fc,
    CHANNEL_MAP_ROWS = 0x54bb90,
    CHANNEL_MAPS = 0x54cdc8,
    CHANNEL_MAP_MIRROR = 0x54cdcc,
    CHANNEL_MAP_PLAIN = 0x54d1d0,
    MIRROR_MAP_INDEX = 0x5bb7b8,
    MIRROR_MAP = 0x4754e0,
    ACTOR_IMAGE = 0xb4,
    ACTOR_WIDTH = 0xf4,
    ACTOR_HEIGHT = 0xf8,
    ACTOR_SCALE = 0x44,
    ACTOR_SCREEN_SCALE = 0x91,
    IMAGE_WIDTH = 4,
    IMAGE_HEIGHT = 8,
    IMAGE_KIND = 0x27,
    SCREEN = 0x544070,
    SCREEN_SCALE_OFF = 0x220,
    SCREEN_SCALE = 0x221,
    SCALE_FULL = 0x10,
    SCALE_REMAINDERS = 0x5c1b00,
    DRAW_IMAGE = 0x5bb734,
    DRAW_IMAGE_KIND = 0x5bb731,
    DRAW_SOURCE_WIDTH = 0x5bb7b4,
    DRAW_SOURCE_HEIGHT = 0x5bb7b6,
    DRAW_WIDTH = 0x5bb74c,
    DRAW_HEIGHT = 0x5bb74e,
    DRAW_SCALE = 0x5bb738,
    BLEND_KIND = 0x5bc00d,
    OPACITY = 0x5bc00e,
    BLEND_ON = 0x5bb739,
    MIRRORED = 0x5bb73a,
    OUTLINE = 0x5bc00c,
    CLIP = 0x5bc002,
    IMAGE_FORMAT = 0x5bc000,
    TARGET_FORMAT = 0x5bb730,
    HALF_OPACITY = 0x32,
    RULES = 0x4fed44,
    RULE_COUNT = 0x5c,
    TRAVERSE_FIRST = 0x5bbfff,
    TRAVERSE_DEPTH = 0x5bb738,
    TRAVERSE_LAST = 0x5bbff0,
    PALETTE_SOURCE = 0x5bb764,
    BLEND_SOURCE_WEIGHTS = 0x55f1f0,
    MIX_SOURCE_TABLE = 0x5785f8,
    PALETTE_SELECTORS = 0x54b804,
    PALETTE_ENTRY_TABLES = 0x54cdcc,
    PALETTE_INDEX = 0x54d5e4,
    SATURATE_COLOUR = 0x5bc018,
    SATURATE_SUM = 0x54d624,
    MIX_TARGET_TABLE = 0x5785fc,
    BLEND_TARGET_WEIGHTS = 0x55f1f4,
    PALETTE_TARGET = 0x5bb768,
    PALETTE_INDEXES = 0x54b800,
    PALETTE_ENTRIES = 0x54cdc8,
    PALETTE_ENTRY = 0x54d5d0,
    ROWS = 0x5bb752,
    ROW_WIDTH = 0x5bb750,
    ROW_WIDTH_COPY = 0x5bc016,
    ROW_SOURCE_SKIP = 0x5bb79c,
    ROW_TARGET_SKIP = 0x5bb7c8,
    TARGET_ENTRY = 0x54d5d8,
};

uint32_t vertrix_port_render_flags(PORT_SIGNATURE)
{
    Port port;
    uint32_t kind;
    uint32_t opacity;
    uint32_t flags = 0;
    uint32_t plain = 0;
    port_open(&port, calls, services, globals, entry);
    kind = port_u8(&port, 0, BLEND_KIND);
    opacity = port_u8(&port, 0, OPACITY);
    if (port_u8(&port, 0, MIRRORED) == 1)
    {
        flags = 0x80000;
    }
    if (entry->edx == 1)
    {
        plain = 1;
        flags += 0x100000;
    }
    else if (port_u8(&port, 0, BLEND_ON) == 0)
    {
        plain = 1;
        flags += 1;
    }
    else
    {
        flags += opacity == HALF_OPACITY ? 8 : 0x10;
        if (kind == 0)
        {
            flags += 0x100;
        }
        else if (kind <= 3)
        {
            flags += 0x200u << (kind - 1);
        }
        else if (kind <= 10)
        {
            flags += 0x1000u << (kind - 4);
            if (opacity != HALF_OPACITY)
            {
                flags -= 8;
            }
            plain = 1;
        }
    }
    if (port_u8(&port, 0, IMAGE_FORMAT) != port_u8(&port, 0, TARGET_FORMAT))
    {
        flags += 4;
        if (plain == 1)
        {
            plain = port_u8(&port, 0, OUTLINE);
            flags += plain == 0 ? 0x20 : plain == 1 ? 0x40 : plain == 2 ? 0x80 : 0;
        }
    }
    if (port_u16(&port, 0, CLIP) != 0)
    {
        flags += 2;
    }
    port_set8(&port, 0, OPACITY, opacity);
    port_set8(&port, 0, BLEND_KIND, kind);
    return port_return(&port, flags, plain);
}

uint32_t vertrix_port_render_rule(PORT_SIGNATURE)
{
    Port port;
    uint32_t flags = entry->edx;
    uint32_t required = 0;
    uint32_t rule;
    port_open(&port, calls, services, globals, entry);
    for (rule = 0; rule < RULE_COUNT; rule++)
    {
        uint32_t allowed;
        required = port_u32(&port, 0, RULES + 8 * rule);
        allowed = port_u32(&port, 0, RULES + 8 * rule + 4);
        if ((flags & required) == required && (flags & ~(allowed | required)) == 0)
        {
            break;
        }
    }
    return port_return(&port, rule, required);
}

uint32_t vertrix_port_render_traversal_flags(PORT_SIGNATURE)
{
    Port port;
    uint32_t flags;
    port_open(&port, calls, services, globals, entry);
    flags = (port_u8(&port, 0, TRAVERSE_FIRST) != 1) + 1;
    if (port_u8(&port, 0, TRAVERSE_DEPTH) != 0x10)
    {
        flags += 4;
    }
    if (port_u8(&port, 0, TRAVERSE_LAST) == 1)
    {
        flags += 8;
    }
    return port_return(&port, flags, entry->edx);
}

/* The index of `value` in `keys`, or the key count. */
static uint32_t key_index(uint32_t value, const uint32_t *keys, uint32_t count)
{
    uint32_t i;
    for (i = 0; i < count && keys[i] != value; i++)
    {
    }
    return i;
}

uint32_t vertrix_port_render_mirror_index(PORT_SIGNATURE)
{
    static const uint32_t KEYS[] = {0, 8, 4, 0xc};
    Port port;
    port_open(&port, calls, services, globals, entry);
    return port_return(&port, key_index(entry->edx, KEYS, 4), entry->edx);
}

uint32_t vertrix_port_render_direction_index(PORT_SIGNATURE)
{
    static const uint32_t KEYS[] = {2, 1, 6, 5, 0xa, 9, 0xe, 0xd};
    Port port;
    port_open(&port, calls, services, globals, entry);
    return port_return(&port, key_index(entry->edx, KEYS, 8), entry->edx);
}

/* A 16-bit size scaled by sixteenths: whole sixteenths times the scale, plus the rounded share of
 * the remainder from the table at 0x5c1b00 (16 bytes per scale). */
static uint32_t scale_size(Port *port, uint32_t size, uint32_t scale)
{
    return (size >> 4) * scale + port_u8(port, SCALE_REMAINDERS, scale * 16 + (size & 0xf));
}

uint32_t vertrix_port_render_source_size(PORT_SIGNATURE)
{
    Port port;
    uint32_t actor = entry->eax;
    uint32_t image;
    uint32_t width;
    uint32_t height;
    uint32_t high;
    uint32_t scale;
    uint32_t scaled_width;
    uint32_t scaled_height;
    port_open(&port, calls, services, globals, entry);
    image = port_u32(&port, actor, ACTOR_IMAGE);
    port_set32(&port, 0, DRAW_IMAGE, image);
    if (image != 0)
    {
        port_set8(&port, 0, DRAW_IMAGE_KIND, port_u8(&port, image, IMAGE_KIND));
        width = port_u16(&port, image, IMAGE_WIDTH);
        height = port_u16(&port, image, IMAGE_HEIGHT);
    }
    else
    {
        width = port_u16(&port, actor, ACTOR_WIDTH);
        height = port_u16(&port, actor, ACTOR_HEIGHT);
    }
    /* edx keeps the high half of the image pointer over the height. */
    high = image & 0xffff0000u;
    if (port_u8(&port, actor, ACTOR_SCREEN_SCALE) == 0)
    {
        scale = port_u8(&port, actor, ACTOR_SCALE);
    }
    else
    {
        uint32_t screen = port_u32(&port, 0, SCREEN);
        scale = port_u8(&port, screen, SCREEN_SCALE_OFF) != 0
                    ? SCALE_FULL
                    : port_u8(&port, screen, SCREEN_SCALE);
    }
    scaled_width = width;
    scaled_height = height;
    if (scale != SCALE_FULL)
    {
        scaled_width = scale_size(&port, width, scale);
        scaled_height = scale_size(&port, height, scale);
    }
    port_set32(&port, entry->edx, 0, (uint32_t)(int32_t)(int16_t)scaled_width);
    port_set32(&port, entry->ebx, 0, (uint32_t)(int32_t)(int16_t)scaled_height);
    port_set16(&port, 0, DRAW_SOURCE_WIDTH, width);
    port_set16(&port, 0, DRAW_HEIGHT, scaled_height);
    port_set16(&port, 0, DRAW_WIDTH, scaled_width);
    port_set8(&port, 0, DRAW_SCALE, scale);
    port_set16(&port, 0, DRAW_SOURCE_HEIGHT, height);
    return port_return(&port, 1, high | height);
}

uint32_t vertrix_port_render_prepare(PORT_SIGNATURE)
{
    Port port;
    /* eax and edx as the original leaves them on each path (eax is its result; edx, ebx and ecx are
     * what 0x4754e0 receives). */
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t format;
    port_open(&port, calls, services, globals, entry);
    format = port_u8(&port, 0, IMAGE_FORMAT);
    eax = (eax & 0xffffff00u) | format;
    if (format != port_u8(&port, 0, TARGET_FORMAT))
    {
        /* The format's colour entry, split into the tint words, and its colour, split into bytes,
         * halved, and its select byte. */
        uint32_t colour = port_u32(&port, FORMAT_COLOURS, format * 4);
        uint32_t index;
        port_set32(&port, 0, FORMAT_ENTRY, port_u32(&port, FORMAT_ENTRIES, format * 4));
        port_set16(&port, 0, FORMAT_TINT_RED, port_u32(&port, 0, FORMAT_ENTRY) >> 24);
        port_set16(&port, 0, FORMAT_TINT_GREEN, (port_u32(&port, 0, FORMAT_ENTRY) >> 16) & 0xff);
        port_set16(&port, 0, FORMAT_TINT_BLUE, port_u16(&port, 0, FORMAT_ENTRY) >> 8);
        port_set32(&port, 0, FORMAT_COLOUR, colour);
        port_set8(&port, 0, FORMAT_COLOUR_RED, colour >> 16);
        port_set8(&port, 0, FORMAT_COLOUR_GREEN, port_u16(&port, 0, FORMAT_COLOUR) >> 8);
        port_set8(&port, 0, FORMAT_COLOUR_BLUE, port_u8(&port, 0, FORMAT_COLOUR));
        port_set32(&port, 0, FORMAT_COLOUR_HALF, (colour >> 1) & 0x7f7f7f);
        index = (((colour & 0xfc0000) >> 4) | ((port_u32(&port, 0, FORMAT_COLOUR) & 0xfc00) >> 2) |
                 (port_u32(&port, 0, FORMAT_COLOUR) & 0xfc)) >>
                2;
        edx = port_u32(&port, 0, FORMAT_SELECTS);
        eax = (index & 0xffffff00u) | port_u8(&port, edx, index);
        port_set8(&port, 0, FORMAT_SELECT, eax);
    }
    if (port_u8(&port, 0, BLEND_ON) == 1)
    {
        /* The level and shade rows of the opacity (in percent) and of its complement. */
        uint32_t opacity = port_u8(&port, 0, OPACITY);
        edx = LEVEL_PERCENT - opacity;
        port_set32(&port, 0, SOURCE_LEVELS, LEVEL_ROWS + (opacity << 8));
        ebx = LEVEL_ROWS + (edx << 8);
        ecx = SHADE_ROWS + (opacity << 10);
        edx <<= 10;
        eax = SHADE_ROWS + edx;
        port_set32(&port, 0, TARGET_LEVELS, ebx);
        port_set32(&port, 0, SOURCE_SHADES, ecx);
        port_set32(&port, 0, TARGET_SHADES, eax);
    }
    if (port_u16(&port, 0, CLIP) != 0)
    {
        eax = (uint32_t)((int32_t)port_u32(&port, 0, IMAGE_FORMAT) >> 16) << 2;
        edx = CHANNEL_MAP_ROWS + eax;
        port_set32(&port, 0, CHANNEL_MAPS, edx);
    }
    else
    {
        port_set32(&port, 0, CHANNEL_MAPS, CHANNEL_MAP_ROWS);
    }
    if (port_u8(&port, 0, MIRRORED) == 1)
    {
        eax = port_call(&port, MIRROR_MAP, port_u8(&port, 0, MIRROR_MAP_INDEX), edx, ebx, ecx);
        return port_return(&port, eax, entry->edx);
    }
    port_set32(&port, 0, CHANNEL_MAP_MIRROR, CHANNEL_MAP_PLAIN);
    return port_return(&port, eax, entry->edx);
}

uint32_t vertrix_port_render_palette_pixel(PORT_SIGNATURE)
{
    Port port;
    uint32_t pixel;
    uint32_t index;
    uint32_t palette;
    uint32_t colour;
    port_open(&port, calls, services, globals, entry);
    pixel = port_u32(&port, port_u32(&port, 0, PALETTE_SOURCE), 0);
    index = (((pixel & 0xfc0000) >> 4) | ((pixel & 0xfc00) >> 2) | (pixel & 0xfc)) >> 2;
    index = port_u8(&port, port_u32(&port, 0, PALETTE_INDEXES), index * 4);
    palette = port_u32(&port, port_u32(&port, 0, PALETTE_ENTRIES), index * 4);
    port_set32(&port, 0, PALETTE_ENTRY, palette);
    colour = port_u8(&port, port_u16(&port, 0, FORMAT_TINT_RED), palette) << 16;
    colour |= port_u8(&port, port_u16(&port, 0, FORMAT_TINT_GREEN), palette) << 8;
    colour |= port_u8(&port, port_u16(&port, 0, FORMAT_TINT_BLUE), palette);
    port_set32(&port, port_u32(&port, 0, PALETTE_TARGET), 0, colour);
    return port_return(&port, colour, entry->edx);
}

/* 0x492880's rows with the target pixel at `target`. */
static uint32_t render_rows_at(PORT_SIGNATURE, uint32_t target)
{
    Port port;
    uint32_t routine = entry->eax;
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t rows;
    port_open(&port, calls, services, globals, entry);
    rows = port_u16(&port, 0, ROWS);
    while (rows != 0)
    {
        eax = (eax & 0xffff0000u) | port_u16(&port, 0, ROW_WIDTH);
        port_set16(&port, 0, ROWS, rows);
        port_set16(&port, 0, ROW_WIDTH_COPY, eax);
        port_call(&port, routine, eax, edx, (entry->ebx & 0xffff0000u) | rows, routine);
        port_set32(&port, 0, PALETTE_SOURCE,
                   port_u32(&port, 0, PALETTE_SOURCE) + (port_u32(&port, 0, ROW_SOURCE_SKIP) << 2));
        eax = port_u32(&port, 0, ROW_TARGET_SKIP);
        edx = port_u32(&port, 0, target) + eax;
        port_set32(&port, 0, target, edx);
        rows = (port_u16(&port, 0, ROWS) - 1) & 0xffff;
    }
    port_set16(&port, 0, ROWS, 0);
    return port_return(&port, eax, entry->edx);
}

uint32_t vertrix_port_render_rows(PORT_SIGNATURE)
{
    return render_rows_at(calls, services, globals, entry, PALETTE_TARGET);
}

uint32_t vertrix_port_render_rows_49a590(PORT_SIGNATURE)
{
    return render_rows_at(calls, services, globals, entry, 0x5bb780);
}

uint32_t vertrix_port_render_rows_4a2650(PORT_SIGNATURE)
{
    return render_rows_at(calls, services, globals, entry, 0x5bb780);
}

uint32_t vertrix_port_render_rows_4aa350(PORT_SIGNATURE)
{
    return render_rows_at(calls, services, globals, entry, 0x5bb778);
}

/* One channel of 0x490c60's blend: the two weights and the colour, halved. */
static uint32_t blend_channel(Port *port, uint32_t source, uint32_t target, uint32_t colour)
{
    uint32_t sum = port_u8(port, port_u32(port, 0, BLEND_SOURCE_WEIGHTS), source) +
                   port_u8(port, port_u32(port, 0, BLEND_TARGET_WEIGHTS), target) +
                   port_u8(port, 0, colour);
    return sum >> 1;
}

uint32_t vertrix_port_render_palette_blend(PORT_SIGNATURE)
{
    Port port;
    uint32_t source;
    uint32_t target;
    uint32_t pixel;
    uint32_t index;
    uint32_t entry_bits;
    uint32_t palette;
    uint32_t colour;
    port_open(&port, calls, services, globals, entry);
    source = port_u32(&port, port_u32(&port, 0, PALETTE_SOURCE), 0);
    target = port_u32(&port, 0, PALETTE_TARGET);
    pixel = port_u32(&port, target, 0);
    colour = blend_channel(&port, (source >> 16) & 0xff, (pixel >> 16) & 0xff, FORMAT_COLOUR_RED)
             << 16;
    colour |= blend_channel(&port, (source >> 8) & 0xff, (pixel >> 8) & 0xff, FORMAT_COLOUR_RED + 1)
              << 8;
    colour |= blend_channel(&port, source & 0xff, pixel & 0xff, FORMAT_COLOUR_RED + 2);
    port_set32(&port, target, 0, colour);
    pixel = port_u32(&port, target, 0);
    index = (((pixel & 0xfc0000) >> 4) | ((pixel & 0xfc00) >> 2) | (pixel & 0xfc)) >> 2;
    entry_bits = port_u32(&port, port_u32(&port, 0, PALETTE_INDEXES), index * 4);
    port_set32(&port, 0, FORMAT_ENTRY, entry_bits);
    palette = port_u32(&port, port_u32(&port, 0, PALETTE_ENTRIES), (entry_bits & 0xff) * 4);
    colour = port_u8(&port, entry_bits >> 24, palette) << 16;
    colour |= port_u8(&port, (entry_bits >> 16) & 0xff, palette) << 8;
    colour |= port_u8(&port, (entry_bits >> 8) & 0xff, palette);
    port_set32(&port, target, 0, colour);
    port_set32(&port, 0, PALETTE_ENTRY, palette);
    return port_return(&port, target, entry->edx);
}

/* A pixel's palette index: 6 bits a channel looked up in [0x54b800] (every fourth byte). */
static uint32_t palette_index(Port *port, uint32_t pixel)
{
    uint32_t index = (((pixel & 0xfc0000) >> 4) | ((pixel & 0xfc00) >> 2) | (pixel & 0xfc)) >> 2;
    return port_u8(port, port_u32(port, 0, PALETTE_INDEXES), index * 4);
}

uint32_t vertrix_port_render_palette_mix(PORT_SIGNATURE)
{
    Port port;
    uint32_t target;
    uint32_t source_word;
    uint32_t target_word;
    uint32_t palette;
    uint32_t colour;
    port_open(&port, calls, services, globals, entry);
    source_word =
        port_u16(&port, port_u32(&port, 0, MIX_SOURCE_TABLE),
                 palette_index(&port, port_u32(&port, port_u32(&port, 0, PALETTE_SOURCE), 0)) * 2);
    target = port_u32(&port, 0, PALETTE_TARGET);
    target_word = port_u16(&port, port_u32(&port, 0, MIX_TARGET_TABLE),
                           palette_index(&port, port_u32(&port, target, 0)) * 2);
    palette = port_u32(&port, port_u32(&port, 0, PALETTE_ENTRIES),
                       (uint32_t)(int16_t)(source_word + target_word) * 4);
    port_set32(&port, 0, PALETTE_ENTRY, palette);
    colour = port_u8(&port, port_u16(&port, 0, FORMAT_TINT_RED), palette) << 16;
    colour |= port_u8(&port, port_u16(&port, 0, FORMAT_TINT_GREEN), palette) << 8;
    colour |= port_u8(&port, port_u16(&port, 0, FORMAT_TINT_BLUE), palette);
    port_set32(&port, target, 0, colour);
    return port_return(&port, target, entry->edx);
}

/* The source pixel's index into the palette tables (6 bits a channel). */
static uint32_t source_index(Port *port)
{
    uint32_t pixel = port_u32(port, port_u32(port, 0, PALETTE_SOURCE), 0);
    return (((pixel & 0xfc0000) >> 4) | ((pixel & 0xfc00) >> 2) | (pixel & 0xfc)) >> 2;
}

/* The colour the entry's channel offsets (its top three bytes) pick from the palette, each offset
 * halfway to the tint's when `tinted`. */
static uint32_t entry_colour(Port *port, uint32_t entry_bits, uint32_t palette, int tinted)
{
    uint32_t red = entry_bits >> 24;
    uint32_t green = (entry_bits >> 16) & 0xff;
    uint32_t blue = (entry_bits >> 8) & 0xff;
    if (tinted)
    {
        red = (red + port_u16(port, 0, FORMAT_TINT_RED)) >> 1;
        green = (green + port_u16(port, 0, FORMAT_TINT_GREEN)) >> 1;
        blue = (blue + port_u16(port, 0, FORMAT_TINT_BLUE)) >> 1;
    }
    return (port_u8(port, red, palette) << 16) | (port_u8(port, green, palette) << 8) |
           port_u8(port, blue, palette);
}

/* The tinted colour of the source pixel's palette entry (0x48ea30 and 0x48ec70). */
static uint32_t tinted_colour(Port *port)
{
    uint32_t entry_bits =
        port_u32(port, port_u32(port, 0, PALETTE_INDEXES), source_index(port) * 4);
    uint32_t palette;
    port_set32(port, 0, FORMAT_ENTRY, entry_bits);
    palette = port_u32(port, port_u32(port, 0, PALETTE_ENTRIES), (entry_bits & 0xff) * 4);
    port_set32(port, 0, PALETTE_ENTRY, palette);
    return entry_colour(port, entry_bits, palette, 1);
}

/* Add `colour` to the target pixel, each channel saturating at 0xff (the low bit of each channel
 * is dropped first so the carries land in bits 8, 16 and 24). */
static uint32_t saturate_add(Port *port, uint32_t colour)
{
    uint32_t target = port_u32(port, 0, PALETTE_TARGET);
    uint32_t sum = (port_u32(port, target, 0) & 0xfefeff) + (colour & 0xfefeff);
    uint32_t mask = 0x1010100 - ((sum & 0x1010100) >> 7);
    port_set32(port, 0, SATURATE_SUM, sum);
    port_set32(port, target, 0, (mask | sum) & 0xffffff);
    return target;
}

uint32_t vertrix_port_render_palette_add_tinted(PORT_SIGNATURE)
{
    Port port;
    uint32_t colour;
    port_open(&port, calls, services, globals, entry);
    colour = tinted_colour(&port);
    port_set32(&port, 0, SATURATE_COLOUR, colour);
    return port_return(&port, saturate_add(&port, colour), entry->edx);
}

uint32_t vertrix_port_render_palette_subtract_tinted(PORT_SIGNATURE)
{
    Port port;
    uint32_t colour;
    uint32_t target;
    uint32_t difference;
    uint32_t mask;
    port_open(&port, calls, services, globals, entry);
    colour = tinted_colour(&port);
    target = port_u32(&port, 0, PALETTE_TARGET);
    difference = (port_u32(&port, target, 0) & 0xfefeff) - (colour & 0xfefeff);
    mask = ((difference & 0x1010100) >> 7) - 0x1010101;
    port_set32(&port, 0, SATURATE_COLOUR, colour);
    port_set32(&port, 0, SATURATE_SUM, difference);
    port_set32(&port, target, 0, mask & difference & 0xffffff);
    return port_return(&port, target, entry->edx);
}

uint32_t vertrix_port_render_palette_add(PORT_SIGNATURE)
{
    Port port;
    uint32_t index;
    uint32_t palette;
    uint32_t entry_bits;
    uint32_t selector;
    port_open(&port, calls, services, globals, entry);
    index = source_index(&port);
    port_set32(&port, 0, PALETTE_INDEX, index);
    palette = port_u32(&port, port_u32(&port, 0, PALETTE_ENTRIES),
                       port_u8(&port, port_u32(&port, 0, PALETTE_INDEXES), index * 4) * 4);
    port_set32(&port, 0, PALETTE_ENTRY, palette);
    selector = port_u8(&port, index, port_u32(&port, 0, PALETTE_SELECTORS));
    entry_bits =
        port_u32(&port, port_u32(&port, port_u32(&port, 0, PALETTE_ENTRY_TABLES), selector * 4), 0);
    port_set32(&port, 0, FORMAT_ENTRY, entry_bits);
    port_set32(&port, 0, SATURATE_COLOUR, entry_colour(&port, entry_bits, palette, 0));
    return port_return(&port, saturate_add(&port, port_u32(&port, 0, SATURATE_COLOUR)), entry->edx);
}

/* The source or target pixel's entry from the index table, as a whole word. */
static uint32_t pixel_entry(Port *port, uint32_t pointer)
{
    uint32_t pixel = port_u32(port, port_u32(port, 0, pointer), 0);
    uint32_t index = (((pixel & 0xfc0000) >> 4) | ((pixel & 0xfc00) >> 2) | (pixel & 0xfc)) >> 2;
    return port_u32(port, port_u32(port, 0, PALETTE_INDEXES), index * 4);
}

/* The three channel bytes of an entry (bits 24, 16 and 8) mapped through a palette. */
static uint32_t mapped_colour(Port *port, uint32_t palette, uint32_t entry)
{
    return (port_u8(port, palette, entry >> 24) << 16) |
           (port_u8(port, palette, (entry >> 16) & 0xff) << 8) |
           port_u8(port, palette, (entry >> 8) & 0xff);
}

uint32_t vertrix_port_render_palette_average(PORT_SIGNATURE)
{
    Port port;
    uint32_t source;
    uint32_t target;
    uint32_t palette;
    port_open(&port, calls, services, globals, entry);
    source = pixel_entry(&port, PALETTE_SOURCE);
    port_set32(&port, 0, FORMAT_ENTRY, source);
    target = pixel_entry(&port, PALETTE_TARGET) & 0xff;
    palette = port_u32(&port, port_u32(&port, 0, PALETTE_ENTRIES),
                       (uint32_t)(int16_t)(((source & 0xff) + target) >> 1) * 4);
    port_set32(&port, 0, PALETTE_ENTRY, palette);
    target = port_u32(&port, 0, PALETTE_TARGET);
    port_set32(&port, target, 0, mapped_colour(&port, palette, source));
    return port_return(&port, target, entry->edx);
}

uint32_t vertrix_port_render_palette_halve(PORT_SIGNATURE)
{
    Port port;
    uint32_t source;
    uint32_t other;
    uint32_t palette;
    uint32_t target;
    uint32_t colour = 0;
    uint32_t shift;
    port_open(&port, calls, services, globals, entry);
    source = pixel_entry(&port, PALETTE_SOURCE);
    port_set32(&port, 0, FORMAT_ENTRY, source);
    palette = port_u32(&port, port_u32(&port, 0, PALETTE_ENTRIES), (source & 0xff) * 4);
    port_set32(&port, 0, PALETTE_ENTRY, palette);
    other = pixel_entry(&port, PALETTE_TARGET);
    port_set32(&port, 0, TARGET_ENTRY, other);
    for (shift = 24; shift >= 8; shift -= 8)
    {
        colour =
            (colour << 8) |
            port_u8(&port, palette, (((source >> shift) & 0xff) + ((other >> shift) & 0xff)) >> 1);
    }
    target = port_u32(&port, 0, PALETTE_TARGET);
    port_set32(&port, target, 0, colour);
    return port_return(&port, target, entry->edx);
}

uint32_t vertrix_port_render_palette_map(PORT_SIGNATURE)
{
    Port port;
    uint32_t palette;
    uint32_t other;
    uint32_t target;
    port_open(&port, calls, services, globals, entry);
    palette = port_u32(&port, port_u32(&port, 0, PALETTE_ENTRIES),
                       (pixel_entry(&port, PALETTE_SOURCE) & 0xff) * 4);
    port_set32(&port, 0, PALETTE_ENTRY, palette);
    other = pixel_entry(&port, PALETTE_TARGET);
    port_set32(&port, 0, FORMAT_ENTRY, other);
    target = port_u32(&port, 0, PALETTE_TARGET);
    port_set32(&port, target, 0, mapped_colour(&port, palette, other));
    return port_return(&port, target, entry->edx);
}
