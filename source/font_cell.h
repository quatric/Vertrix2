#ifndef VERTRIX_FONT_CELL_H
#define VERTRIX_FONT_CELL_H
#include <stdint.h>
typedef struct
{
    uint32_t x, y, width, height, count;
} VertrixFontCell;
/* Original0x43f200 row-major slicing. Sheet dimensions, rather than the
 * caller's progress count, determine how many bordered cells are produced. */
int vertrix_font_cell(uint32_t sheet_width, uint32_t sheet_height, uint32_t width, uint32_t height,
                      uint32_t index, VertrixFontCell *output);
#endif
