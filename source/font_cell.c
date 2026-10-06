#include "font_cell.h"

int vertrix_font_cell(uint32_t sheet_width, uint32_t sheet_height, uint32_t width, uint32_t height,
                      uint32_t index, VertrixFontCell *output)
{
    if (!output || !width || !height || width == UINT32_MAX || height == UINT32_MAX)
    {
        return 0;
    }
    uint32_t columns = sheet_width / (width + 1);
    uint32_t rows = sheet_height / (height + 1);
    if (!columns || !rows || columns > UINT32_MAX / rows || index >= columns * rows)
    {
        return 0;
    }
    VertrixFontCell cell;
    cell.x = 1 + (index % columns) * (width + 1);
    cell.y = 1 + (index / columns) * (height + 1);
    cell.width = width;
    cell.height = height;
    cell.count = columns * rows;
    *output = cell;
    return 1;
}
