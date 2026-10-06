#include "render_palette.h"

int vertrix_render_palette_weighted_pixel(uint32_t source, uint32_t destination,
                                          const uint32_t *lookup, size_t lookup_count,
                                          const uint8_t *maps, size_t maps_size, size_t map_stride,
                                          size_t map_count, const uint8_t source_weight[256],
                                          const uint8_t destination_weight[256], uint32_t *output)
{
    uint32_t index =
        ((source & 0xfc0000u) >> 6) | ((source & 0xfc00u) >> 4) | ((source & 0xfcu) >> 2);
    uint32_t other_index = ((destination & 0xfc0000u) >> 6) | ((destination & 0xfc00u) >> 4) |
                           ((destination & 0xfcu) >> 2);
    if (!lookup || !maps || !output || !source_weight || !destination_weight ||
        index >= lookup_count || other_index >= lookup_count)
    {
        return 0;
    }
    uint32_t entry = lookup[index], other = lookup[other_index];
    size_t row = entry & 255u;
    if (!map_stride || row >= map_count || row > SIZE_MAX / map_stride)
    {
        return 0;
    }
    size_t base = row * map_stride;
    uint32_t result = 0;
    for (uint32_t i = 0; i < 3; ++i)
    {
        uint32_t shift = 24 - i * 8;
        uint32_t channel = (uint32_t)source_weight[(entry >> shift) & 255u] +
                           destination_weight[(other >> shift) & 255u];
        if (base >= maps_size || channel >= maps_size - base)
        {
            return 0;
        }
        result |= (uint32_t)maps[base + channel] << (16 - i * 8);
    }
    *output = result;
    return 1;
}

int vertrix_render_palette_half_pixel(uint32_t source, uint32_t destination, const uint32_t *lookup,
                                      size_t lookup_count, const uint8_t *maps, size_t maps_size,
                                      size_t map_stride, size_t map_count, uint32_t *output)
{
    uint32_t index =
        ((source & 0xfc0000u) >> 6) | ((source & 0xfc00u) >> 4) | ((source & 0xfcu) >> 2);
    uint32_t other_index = ((destination & 0xfc0000u) >> 6) | ((destination & 0xfc00u) >> 4) |
                           ((destination & 0xfcu) >> 2);
    if (!lookup || !maps || !output || index >= lookup_count || other_index >= lookup_count)
    {
        return 0;
    }
    uint32_t entry = lookup[index], other = lookup[other_index];
    size_t row = entry & 255u;
    if (!map_stride || row >= map_count || row > SIZE_MAX / map_stride)
    {
        return 0;
    }
    size_t base = row * map_stride;
    uint32_t result = 0;
    for (uint32_t i = 0; i < 3; ++i)
    {
        uint32_t shift = 24 - i * 8;
        uint32_t channel = (((entry >> shift) & 255u) + ((other >> shift) & 255u)) / 2;
        if (base >= maps_size || channel >= maps_size - base)
        {
            return 0;
        }
        result |= (uint32_t)maps[base + channel] << (16 - i * 8);
    }
    *output = result;
    return 1;
}

int vertrix_render_palette_pixel(uint32_t source, const uint32_t *lookup, size_t lookup_count,
                                 const uint8_t *maps, size_t maps_size, int fixed_channels,
                                 const uint16_t channels[3], uint32_t *output)
{
    return vertrix_render_palette_pixel_layout(source, lookup, lookup_count, maps, maps_size, 256,
                                               256, fixed_channels, channels, output);
}

int vertrix_render_palette_pixel_layout(uint32_t source, const uint32_t *lookup,
                                        size_t lookup_count, const uint8_t *maps, size_t maps_size,
                                        size_t map_stride, size_t map_count, int fixed_channels,
                                        const uint16_t channels[3], uint32_t *output)
{
    uint32_t index =
        ((source & 0xfc0000u) >> 6) | ((source & 0xfc00u) >> 4) | ((source & 0xfcu) >> 2);
    if (!lookup || !maps || !output || index >= lookup_count || (fixed_channels && !channels))
    {
        return 0;
    }
    uint32_t entry = lookup[index];
    size_t row = entry & 255u;
    if (!map_stride || row >= map_count || row > SIZE_MAX / map_stride)
    {
        return 0;
    }
    size_t base = row * map_stride;
    uint32_t result = 0;
    for (uint32_t i = 0; i < 3; ++i)
    {
        uint32_t channel = fixed_channels ? channels[i] : ((entry >> (24 - i * 8)) & 255u);
        if (base >= maps_size || channel >= maps_size - base)
        {
            return 0;
        }
        result |= (uint32_t)maps[base + channel] << (16 - i * 8);
    }
    *output = result;
    return 1;
}
