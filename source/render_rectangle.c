#include "render_rectangle.h"
#include "palette_map.h"
#include "render_dispatch.h"
#include <stdlib.h>
#include <string.h>

static int rectangle32(VertrixSurface *target, uint32_t x, uint32_t y, uint16_t width,
                       uint16_t height, uint32_t half_color, const VertrixPaletteTables *tables,
                       int16_t map_shift, int palette, const uint16_t channels[3])
{
    if (!target || target->bytes_per_pixel != 4 || x > target->width || y > target->height ||
        width > target->width - x || height > target->height - y)
    {
        return 0;
    }
    if (!width || !height)
    {
        return 1;
    }
    uint64_t end = (uint64_t)(y + height - 1) * target->stride + (uint64_t)(x + width) * 4;
    if (!target->data || end > target->size)
    {
        return 0;
    }
    uint8_t *pixels = target->data;
    if (palette)
    {
        pixels = malloc(target->size);
        if (!pixels)
        {
            return 0;
        }
        memcpy(pixels, target->data, target->size);
    }
    for (uint32_t row = 0; row < height; ++row)
    {
        size_t offset = (size_t)((uint64_t)(y + row) * target->stride + (uint64_t)x * 4);
        for (uint32_t column = 0; column < width; ++column)
        {
            uint8_t *pixel = pixels + offset + column * 4;
            uint32_t value = (uint32_t)pixel[0] | (uint32_t)pixel[1] << 8 |
                             (uint32_t)pixel[2] << 16 | (uint32_t)pixel[3] << 24;
            if (palette)
            {
                uint16_t averaged[3];
                const uint16_t *selected = channels;
                if (palette == 4)
                {
                    value = ((value >> 1) & 0x7f7f7fu) + half_color;
                }
                if (palette == 3)
                {
                    if (!tables || !tables->lookup || !channels)
                    {
                        free(pixels);
                        return 0;
                    }
                    uint32_t index = ((value & 0xfc0000u) >> 6) | ((value & 0xfc00u) >> 4) |
                                     ((value & 0xfcu) >> 2);
                    uint32_t entry = tables->lookup[index];
                    for (uint32_t i = 0; i < 3; ++i)
                    {
                        averaged[i] =
                            (uint16_t)((channels[i] + ((entry >> (24 - i * 8)) & 255u)) / 2u);
                    }
                    selected = averaged;
                }
                if (!vertrix_palette_map_pixel(tables, map_shift, value,
                                               palette == 2 || palette == 3, selected, &value))
                {
                    free(pixels);
                    return 0;
                }
            }
            else
            {
                value = ((value >> 1) & 0x7f7f7fu) + half_color;
            }
            for (uint32_t byte = 0; byte < 4; ++byte)
            {
                pixel[byte] = (uint8_t)(value >> (byte * 8));
            }
        }
    }
    if (palette)
    {
        memcpy(target->data, pixels, target->size);
        free(pixels);
    }
    return 1;
}

int vertrix_render_rectangle_half32(VertrixSurface *target, uint32_t x, uint32_t y, uint16_t width,
                                    uint16_t height, uint32_t half_color)
{
    return rectangle32(target, x, y, width, height, half_color, NULL, 0, 0, NULL);
}

int vertrix_render_rectangle_palette32(VertrixSurface *target, uint32_t x, uint32_t y,
                                       uint16_t width, uint16_t height,
                                       const VertrixPaletteTables *tables, int16_t map_shift)
{
    return rectangle32(target, x, y, width, height, 0, tables, map_shift, 1, NULL);
}

int vertrix_render_rectangle_fixed_palette32(VertrixSurface *target, uint32_t x, uint32_t y,
                                             uint16_t width, uint16_t height,
                                             const VertrixPaletteTables *tables, int16_t map_shift,
                                             const uint16_t channels[3])
{
    return rectangle32(target, x, y, width, height, 0, tables, map_shift, 2, channels);
}

int vertrix_render_rectangle_index_half32(VertrixSurface *target, uint32_t x, uint32_t y,
                                          uint16_t width, uint16_t height,
                                          const VertrixPaletteTables *tables, int16_t map_shift,
                                          const uint16_t channels[3])
{
    return rectangle32(target, x, y, width, height, 0, tables, map_shift, 3, channels);
}

int vertrix_render_rectangle_half_palette32(VertrixSurface *target, uint32_t x, uint32_t y,
                                            uint16_t width, uint16_t height,
                                            const VertrixPaletteTables *tables, int16_t map_shift,
                                            uint32_t half_color)
{
    return rectangle32(target, x, y, width, height, half_color, tables, map_shift, 4, NULL);
}

int vertrix_render_rectangle32(uint32_t flags, VertrixSurface *target, uint32_t x, uint32_t y,
                               uint16_t width, uint16_t height,
                               const VertrixRenderPreparation *prepared,
                               const VertrixPaletteTables *tables)
{
    if (!prepared)
    {
        return 0;
    }
    switch (vertrix_render_kernel_address(flags, 4))
    {
        case 0x492b90:
            return vertrix_render_rectangle_palette32(target, x, y, width, height, tables,
                                                      prepared->map_shift);
        case 0x492cc0:
            return vertrix_render_rectangle_fixed_palette32(
                target, x, y, width, height, tables, prepared->map_shift, prepared->color.indices);
        case 0x492dc0:
            return vertrix_render_rectangle_half32(target, x, y, width, height,
                                                   prepared->color.half_color);
        case 0x492e40:
            return vertrix_render_rectangle_index_half32(
                target, x, y, width, height, tables, prepared->map_shift, prepared->color.indices);
        case 0x492f90:
            return vertrix_render_rectangle_half_palette32(target, x, y, width, height, tables,
                                                           prepared->map_shift,
                                                           prepared->color.half_color);
        default:
            return 0;
    }
}
