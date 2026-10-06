#include "palette_map.h"

int vertrix_palette_map(const VertrixPaletteTables *tables, int16_t shift, int16_t index,
                        VertrixPaletteMap *output)
{
    if (!tables || !tables->lookup || !tables->hue || !output)
    {
        return 0;
    }
    int32_t row = (int32_t)shift + index;
    if (row < -200 || row > 400)
    {
        return 0;
    }
    VertrixPaletteMap result;
    size_t offset = (size_t)(row < 0 ? 0 : row > 200 ? 200 : row) * 101u;
    result.data = tables->channels + offset;
    result.size = sizeof(tables->channels) - offset;
    *output = result;
    return 1;
}

int vertrix_palette_map_pixel(const VertrixPaletteTables *tables, int16_t shift, uint32_t source,
                              int fixed, const uint16_t channels[3], uint32_t *output)
{
    if (!tables || !tables->lookup || !output || (fixed && !channels))
    {
        return 0;
    }
    uint32_t index =
        ((source & 0xfc0000u) >> 6) | ((source & 0xfc00u) >> 4) | ((source & 0xfcu) >> 2);
    uint32_t entry = tables->lookup[index];
    VertrixPaletteMap map;
    if (!vertrix_palette_map(tables, shift, (uint8_t)entry, &map))
    {
        return 0;
    }
    uint32_t result = 0;
    for (uint32_t i = 0; i < 3; ++i)
    {
        uint32_t channel = fixed ? channels[i] : ((entry >> (24 - i * 8)) & 255u);
        if (channel >= map.size)
        {
            return 0;
        }
        result |= (uint32_t)map.data[channel] << (16 - i * 8);
    }
    *output = result;
    return 1;
}
