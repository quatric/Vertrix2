#include "font_map.h"

int vertrix_font_map_construct(VertrixFontMap *map)
{
    if (!map)
    {
        return 0;
    }
    map->space_width = 0;
    map->space_height = 0;
    for (unsigned i = 0; i < 255; i++)
    {
        map->glyphs[i] = -1;
    }
    return 1;
}

int vertrix_font_maps_initialize(VertrixFontMap *maps, size_t count, uint32_t width6,
                                 uint32_t height6, uint32_t width9, uint32_t height9)
{
    static const int16_t specs[19][5] = {
        {35, 30, 48, 74, 0},     {35, 30, 12, 38, 0},     {35, 30, 12, 74, 0},
        {35, 30, 48, 74, 0},     {28, 30, 12, 84, 0},     {13, 12, 106, 132, 94},
        {14, 16, 152, 142, -1},  {0, 0, 178, 204, 214},   {0, 0, -1, -1, -1},
        {0, 0, -1, -1, -1},      {18, 14, 242, 268, 230}, {13, 12, 290, 316, 278},
        {18, 14, 338, 364, 326}, {13, 12, 386, 412, 374}, {18, 14, 434, 460, 422},
        {13, 12, 482, 508, 470}, {28, 30, 12, 518, 0},    {28, 30, 12, 528, 0},
        {28, 30, 12, 538, 0}};
    static const uint8_t punctuation[] = "'.&!?,/;:<>@";
    if (!maps || count < 19)
    {
        return 0;
    }
    for (size_t font = 0; font < 19; font++)
    {
        maps[font].space_width = (uint32_t)specs[font][0];
        maps[font].space_height = (uint32_t)specs[font][1];
        if (font >= 7 && font <= 9)
        {
            maps[font].space_width = ((font == 7 ? width6 : width9) & ~UINT32_C(1)) + 35;
            maps[font].space_height = ((font == 7 ? height6 : height9) & ~UINT32_C(1)) + 30;
        }
        if (specs[font][2] >= 0)
        {
            for (unsigned i = 0; i < 26; i++)
            {
                maps[font].glyphs['A' + i] = specs[font][2] + i;
            }
        }
        if (specs[font][3] >= 0)
        {
            for (unsigned i = 0; i < 10; i++)
            {
                maps[font].glyphs['0' + i] = specs[font][3] + i;
            }
        }
        if (specs[font][4] >= 0)
        {
            for (unsigned i = 0; i < 12; i++)
            {
                maps[font].glyphs[punctuation[i]] = specs[font][4] + i;
            }
        }
    }
    maps[8].glyphs['G'] = 226;
    maps[8].glyphs['O'] = 227;
    maps[9].glyphs['V'] = 228;
    maps[9].glyphs['S'] = 229;
    return 1;
}

int vertrix_font_glyph(const VertrixFontMap *map, uint8_t glyph, const uint32_t *resources,
                       size_t resource_count, int16_t *selected_index, uint32_t *resource)
{
    if (!map || !selected_index || !resource)
    {
        return 0;
    }
    int16_t index = map->glyphs[glyph];
    if (index != -1 && (index < 0 || !resources || (size_t)index >= resource_count))
    {
        return 0;
    }
    *selected_index = index;
    *resource = index == -1 ? 0 : resources[index];
    return 1;
}
