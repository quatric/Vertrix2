#include "render_color.h"

int vertrix_render_color_prepare(uint8_t index, const uint32_t *lookup_colors,
                                 const uint32_t *colors, size_t count, const uint8_t *hues,
                                 size_t hue_count, VertrixRenderColor *output)
{
    if (!lookup_colors || !colors || !hues || !output || index >= count)
    {
        return 0;
    }
    uint32_t color = colors[index];
    uint32_t hue_index =
        ((color & 0xfc0000u) >> 6) | ((color & 0xfc00u) >> 4) | ((color & 0xfcu) >> 2);
    if (hue_index >= hue_count)
    {
        return 0;
    }
    VertrixRenderColor result = {0};
    result.lookup_entry = lookup_colors[index];
    result.color = color;
    result.half_color = (color >> 1) & 0x7f7f7fu;
    result.hue = hues[hue_index];
    for (uint32_t i = 0; i < 3; ++i)
    {
        result.indices[i] = (uint16_t)((result.lookup_entry >> (24 - i * 8)) & 255u);
        result.channels[i] = (uint8_t)(color >> (16 - i * 8));
    }
    *output = result;
    return 1;
}
