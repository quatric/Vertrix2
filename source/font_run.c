#include "font_run.h"
#include "render_geometry.h"

int vertrix_font_run(const VertrixFontBank *bank, const VertrixFontMap *map, const uint8_t *text,
                     size_t storage, uint32_t x, int16_t y, VertrixFontPlacement *placements,
                     size_t capacity, size_t *count, uint32_t *final_x)
{
    if (!bank || !bank->ready || !map || !text || !count || !final_x)
    {
        return 0;
    }
    size_t length = 0, required = 0;
    while (length < storage && text[length])
    {
        if (text[length] != ' ')
        {
            const VertrixImage *image;
            if (!vertrix_font_bank_glyph(bank, map, text[length], &image))
            {
                return 0;
            }
            required += image != NULL;
        }
        length++;
    }
    if (length == storage || required > capacity || (required && !placements))
    {
        return 0;
    }
    size_t written = 0;
    for (size_t i = 0; i < length; i++)
    {
        uint8_t glyph = text[i];
        if (glyph == ' ')
        {
            x += map->space_width + 1;
        }
        else
        {
            int16_t index = map->glyphs[glyph];
            if (index == -1)
            {
                continue;
            }
            placements[written].descriptor = (uint16_t)index;
            placements[written].x = (int16_t)(uint16_t)x;
            placements[written].y = y;
            placements[written].glyph = glyph;
            written++;
            x = (x & UINT32_C(0xffff0000)) |
                (uint16_t)((uint16_t)x + (uint16_t)bank->glyphs[index].width);
            x++;
        }
    }
    *count = written;
    *final_x = x;
    return 1;
}

int vertrix_font_run_scaled(const VertrixFontBank *bank, const VertrixFontMap *map,
                            const uint8_t *text, size_t storage, int16_t x, int16_t y, uint8_t mode,
                            uint8_t screen_override, uint8_t screen_unscaled, uint8_t screen_mode,
                            VertrixFontPlacement *placements, size_t capacity, size_t *count,
                            int16_t *final_x)
{
    uint8_t effective = screen_override ? (screen_unscaled ? 16 : screen_mode) : mode;
    if (!final_x || effective > 16)
    {
        return 0;
    }
    size_t resolved;
    uint32_t unused;
    if (!count || !vertrix_font_run(bank, map, text, storage, (uint32_t)(int32_t)x, y, placements,
                                    capacity, &resolved, &unused))
    {
        return 0;
    }
    size_t written = 0;
    for (size_t i = 0; text[i]; i++)
    {
        uint8_t glyph = text[i];
        VertrixResourceDimensions dimensions;
        if (glyph == ' ')
        {
            dimensions.width = (uint16_t)map->space_width;
            dimensions.height = (uint16_t)map->space_height;
        }
        else
        {
            int16_t index = map->glyphs[glyph];
            if (index == -1)
            {
                continue;
            }
            dimensions.width = (uint16_t)bank->glyphs[index].width;
            dimensions.height = (uint16_t)bank->glyphs[index].height;
            placements[written].x = x;
            written++;
        }
        int32_t width, height;
        vertrix_resource_measure(dimensions.width, dimensions.height, effective, &width, &height);
        x = (int16_t)(uint16_t)((uint16_t)x + (uint32_t)width + 1);
    }
    *count = resolved;
    *final_x = x;
    return 1;
}
