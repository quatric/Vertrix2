#include "palette_tables.h"
#include "palette_color.h"
#include "render_palette.h"
#include <stdlib.h>
#include <string.h>

int vertrix_palette_tables_cycle(const VertrixPaletteTables *tables, uint32_t index, uint8_t cycle,
                                 uint32_t constant_tail, uint32_t *output)
{
    if (!tables || !tables->lookup || !tables->hue || !output || index > 255)
    {
        return 0;
    }
    uint32_t offset = index ? index - 1u + cycle : 0;
    *output = !index         ? (cycle == 255 ? constant_tail : 100u)
              : offset < 255 ? tables->auxiliary[offset]
                             : 0;
    return 1;
}

int vertrix_palette_tables_pixel(const VertrixPaletteTables *tables, uint32_t source,
                                 int fixed_channels, const uint16_t channels[3], uint32_t *output)
{
    if (!tables || !tables->lookup || !tables->hue)
    {
        return 0;
    }
    return vertrix_render_palette_pixel_layout(source, tables->lookup, 262144, tables->channels,
                                               sizeof(tables->channels), 101, 201, fixed_channels,
                                               channels, output);
}

void vertrix_palette_tables_free(VertrixPaletteTables *tables)
{
    if (tables)
    {
        free(tables->lookup);
        free(tables->hue);
        memset(tables, 0, sizeof(*tables));
    }
}

int vertrix_palette_tables_build(VertrixPaletteTables *output)
{
    if (!output || output->lookup || output->hue)
    {
        return 0;
    }
    VertrixPaletteTables tables = {0};
    tables.lookup = calloc(262144, sizeof(*tables.lookup));
    tables.hue = calloc(262144, sizeof(*tables.hue));
    if (!tables.lookup || !tables.hue)
    {
        vertrix_palette_tables_free(&tables);
        return 0;
    }
    vertrix_palette_channels(tables.channels, sizeof(tables.channels));
    for (uint32_t i = 0; i < 262144; ++i)
    {
        uint8_t rgb[3] = {(uint8_t)((i >> 12) * 4), (uint8_t)(((i >> 6) & 63) * 4),
                          (uint8_t)((i & 63) * 4)};
        uint16_t hsv[3];
        uint32_t chromatic;
        vertrix_palette_rgb(rgb[0], rgb[1], rgb[2], hsv, &chromatic);
        vertrix_palette_lookup_entry(tables.channels, sizeof(tables.channels), hsv[2], rgb,
                                     &tables.lookup[i]);
        tables.hue[i] = chromatic ? (uint8_t)(hsv[0] * 254u / 359u + 1u) : 0;
    }
    for (uint32_t i = 0; i < 255; ++i)
    {
        uint16_t color[3];
        vertrix_palette_color((uint16_t)(i * 359u / 254u), 100, 100, color);
        uint8_t rgb[3] = {(uint8_t)color[0], (uint8_t)color[1], (uint8_t)color[2]};
        vertrix_palette_lookup_entry(tables.channels, sizeof(tables.channels), 100, rgb,
                                     &tables.auxiliary[i]);
    }
    *output = tables;
    return 1;
}
