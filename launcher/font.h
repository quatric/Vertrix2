#ifndef VERTRIX_LAUNCHER_FONT_H
#define VERTRIX_LAUNCHER_FONT_H

#include <stdint.h>

/* One glyph: its coverage bitmap (width x height bytes at pixels + offset), drawn at (x, y) from
 * the line's top left, and the advance to the next one. */
typedef struct
{
    uint8_t code;
    uint8_t width;
    uint8_t height;
    int8_t x;
    int8_t y;
    uint8_t advance;
    uint32_t offset;
} FontGlyph;

typedef struct
{
    int line;
    int baseline;
    const FontGlyph *glyphs; /* ordered by code */
    int count;
    const uint8_t *pixels;
} FontSet;

/* Sizes for text scales 1 and 2 (tools/make_font.py). */
extern const FontSet font_sets[2];

#endif
