#include "rtlpatterntables.h"

/* Cuts the pattern sheet into patterns: six bands of ten rows, in which a run of columns with any
 * pixel set is one pattern, ended by a column that is empty in all ten rows. */

enum
{
    SURFACE_WIDTH = 4,
    BANDS = 6,
    BAND_ROWS = 10,
    /* Band n covers rows 1 + 11n to 10 + 11n. */
    BAND_STRIDE = 0xb,

    WIDEST = 0x5440f6,
    NARROWEST = 0x5440f7,
    NARROWEST_START = 4,
    PATTERN_WIDTHS = 0x544318,
    PATTERN_PIXELS = 0x54414c,
    PATTERN_COUNT = 0x73,
    /* Per character: the pattern from the character table 0x4fba48, or pattern 0x53. */
    CHARACTERS = 0x4fba48,
    CHARACTER_COUNT = 0x100,
    MISSING_PATTERN = 0x53,
    CHARACTER_PIXELS = 0x54438c,
    CHARACTER_WIDTHS = 0x544790,

    PIXEL = 0x478f10,
    CALLOC = 0x4ec160
};

static uint32_t pixel(Port *port, uint32_t surface, uint32_t x, uint32_t y)
{
    return port_call(port, PIXEL, surface, x, y, 0);
}

/* Copies a pattern's pixels, row by row across the band, into a new block; records its width. */
static void store_pattern(Port *port, uint32_t surface, uint32_t pattern, uint32_t start,
                          uint32_t width, uint32_t top, uint32_t bottom)
{
    if (width > port_u8(port, WIDEST, 0))
    {
        port_set8(port, WIDEST, 0, width);
    }
    if (width < port_u8(port, NARROWEST, 0))
    {
        port_set8(port, NARROWEST, 0, width);
    }
    port_set8(port, PATTERN_WIDTHS, pattern, width);
    uint32_t to = port_call(port, CALLOC, width * BAND_ROWS, 1, 0, 0);
    port_set32(port, PATTERN_PIXELS, pattern * 4, to);
    for (uint32_t y = top; y != bottom && !port->env.failed; y++)
    {
        for (uint32_t column = 0; column < width && !port->env.failed; column++)
        {
            port_set8(port, to, 0, pixel(port, surface, start + column, y));
            to++;
        }
    }
}

/* Original 0x441f20 (eax = the pattern sheet): fills the pattern tables (width bounds at
 * 0x5440f6 and 0x5440f7), then the per-character tables. Keeps the caller's edx. */
uint32_t vertrix_port_pattern_tables_441f20(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    const uint32_t surface = entry->eax;
    const uint32_t width = port_u32(&port, surface, SURFACE_WIDTH);
    port_set8(&port, WIDEST, 0, 0);
    port_set8(&port, NARROWEST, 0, NARROWEST_START);

    uint32_t pattern = 0;
    for (uint32_t band = 0; band < BANDS && !port.env.failed; band++)
    {
        const uint32_t top = 1 + band * BAND_STRIDE;
        const uint32_t bottom = top + BAND_ROWS;
        int inside = 0;
        uint32_t start = 0;
        for (uint32_t x = 0; x < width && !port.env.failed; x++)
        {
            uint32_t empty_rows = 0;
            for (uint32_t y = top; y < bottom && !port.env.failed; y++, empty_rows++)
            {
                if (pixel(&port, surface, x, y) != 0)
                {
                    break;
                }
            }
            if (empty_rows != BAND_ROWS)
            {
                if (!inside)
                {
                    inside = 1;
                    start = x & 0xffff;
                }
            }
            else if (inside)
            {
                store_pattern(&port, surface, pattern, start, (x - start) & 0xff, top, bottom);
                pattern = (pattern + 1) & 0xffff;
                inside = 0;
            }
        }
    }

    for (uint32_t character = 0; character < CHARACTER_COUNT && !port.env.failed; character++)
    {
        uint32_t index = 0;
        while (index < PATTERN_COUNT && port_u8(&port, CHARACTERS, index) != character)
        {
            index++;
        }
        if (index == PATTERN_COUNT)
        {
            index = MISSING_PATTERN;
        }
        port_set32(&port, CHARACTER_PIXELS, character * 4,
                   port_u32(&port, PATTERN_PIXELS, index * 4));
        port_set8(&port, CHARACTER_WIDTHS, character, port_u8(&port, PATTERN_WIDTHS, index));
    }
    return port_return(&port, 0, entry->edx);
}
