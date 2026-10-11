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
    TRAVERSE_LAST = 0x5bbff0
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
