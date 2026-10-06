#include "surface.h"
#include "render_dispatch.h"

uint32_t vertrix_surface_offset(uint32_t stride, uint8_t bytes_per_pixel, int32_t x, int32_t y)
{
    return (uint32_t)y * stride + (uint32_t)x * bytes_per_pixel;
}

static int location(const VertrixSurface *surface, uint32_t x, uint32_t y, size_t *offset)
{
    if (!surface || !surface->data || x >= surface->width || y >= surface->height ||
        (surface->bytes_per_pixel != 1 && surface->bytes_per_pixel != 2 &&
         surface->bytes_per_pixel != 4))
    {
        return 0;
    }
    uint64_t row_bytes = (uint64_t)surface->width * surface->bytes_per_pixel;
    uint64_t position = (uint64_t)y * surface->stride + (uint64_t)x * surface->bytes_per_pixel;
    if (row_bytes > surface->stride || position > surface->size ||
        surface->size - (size_t)position < surface->bytes_per_pixel)
    {
        return 0;
    }
    *offset = (size_t)position;
    return 1;
}

int vertrix_surface_read(const VertrixSurface *surface, uint32_t x, uint32_t y, uint32_t *value)
{
    size_t offset;
    if (!value || !location(surface, x, y, &offset))
    {
        return 0;
    }
    uint32_t result = 0;
    for (uint32_t i = 0; i < surface->bytes_per_pixel; ++i)
    {
        result |= (uint32_t)surface->data[offset + i] << (i * 8);
    }
    *value = result;
    return 1;
}

int vertrix_surface_write(VertrixSurface *surface, uint32_t x, uint32_t y, uint32_t value)
{
    size_t offset;
    if (!location(surface, x, y, &offset))
    {
        return 0;
    }
    for (uint32_t i = 0; i < surface->bytes_per_pixel; ++i)
    {
        surface->data[offset + i] = (uint8_t)(value >> (i * 8));
    }
    return 1;
}

static int rectangle32(const VertrixSurface *source, uint32_t source_x, uint32_t source_y,
                       VertrixSurface *target, uint32_t target_x, uint32_t target_y, uint16_t width,
                       uint16_t height, int alpha)
{
    if (!source || !target || source->bytes_per_pixel != 4 || target->bytes_per_pixel != 4)
    {
        return 0;
    }
    if (!width || !height)
    {
        return 1;
    }
    if ((uint64_t)source_x + width > source->width ||
        (uint64_t)source_y + height > source->height ||
        (uint64_t)target_x + width > target->width || (uint64_t)target_y + height > target->height)
    {
        return 0;
    }
    size_t offset;
    if (!location(source, source_x + width - 1, source_y + height - 1, &offset) ||
        !location(target, target_x + width - 1, target_y + height - 1, &offset))
    {
        return 0;
    }
    for (uint32_t row = 0; row < height; ++row)
    {
        for (uint32_t column = 0; column < width; ++column)
        {
            uint32_t pixel = 0;
            vertrix_surface_read(source, source_x + column, source_y + row, &pixel);
            if (alpha)
            {
                uint32_t destination = 0;
                vertrix_surface_read(target, target_x + column, target_y + row, &destination);
                pixel = alpha == 2 ? (pixel >> 24 ? pixel : destination)
                                   : vertrix_surface_alpha_pixel(pixel, destination);
            }
            vertrix_surface_write(target, target_x + column, target_y + row, pixel);
        }
    }
    return 1;
}

uint32_t vertrix_surface_alpha_pixel(uint32_t source, uint32_t destination)
{
    uint32_t alpha = source >> 24;
    if (!alpha)
    {
        return destination;
    }
    if (alpha == 255)
    {
        return source;
    }
    uint32_t result = 0;
    for (uint32_t shift = 0; shift < 24; shift += 8)
    {
        uint32_t channel =
            ((source >> shift) & 255) + ((destination >> shift) & 255) * (255 - alpha) / 255;
        result |= channel << shift;
    }
    return result;
}

int vertrix_surface_copy32(const VertrixSurface *source, uint32_t source_x, uint32_t source_y,
                           VertrixSurface *target, uint32_t target_x, uint32_t target_y,
                           uint16_t width, uint16_t height)
{
    return rectangle32(source, source_x, source_y, target, target_x, target_y, width, height, 0);
}

int vertrix_surface_alpha32(const VertrixSurface *source, uint32_t source_x, uint32_t source_y,
                            VertrixSurface *target, uint32_t target_x, uint32_t target_y,
                            uint16_t width, uint16_t height)
{
    return rectangle32(source, source_x, source_y, target, target_x, target_y, width, height, 1);
}

int vertrix_surface_binary32(const VertrixSurface *source, uint32_t source_x, uint32_t source_y,
                             VertrixSurface *target, uint32_t target_x, uint32_t target_y,
                             uint16_t width, uint16_t height)
{
    return rectangle32(source, source_x, source_y, target, target_x, target_y, width, height, 2);
}

static int sample_row32(const VertrixSurface *source, uint32_t source_x, uint32_t source_y,
                        VertrixSurface *target, uint32_t target_x, uint32_t target_y,
                        const uint8_t *advances, size_t advance_count, uint16_t width, int binary,
                        uint16_t effect)
{
    if (!source || !target || source->bytes_per_pixel != 4 || target->bytes_per_pixel != 4 ||
        !advances || advance_count < width)
    {
        return 0;
    }
    if (!width)
    {
        return 1;
    }
    uint64_t last_x = source_x;
    for (uint32_t i = 0; i + 1 < width; ++i)
    {
        last_x += advances[i];
    }
    size_t offset;
    if (last_x > UINT32_MAX || (uint64_t)target_x + width > target->width ||
        !location(source, (uint32_t)last_x, source_y, &offset) ||
        !location(target, target_x + width - 1, target_y, &offset))
    {
        return 0;
    }
    for (uint32_t i = 0; i < width; ++i)
    {
        uint32_t pixel = 0;
        vertrix_surface_read(source, source_x, source_y, &pixel);
        if (!binary || pixel >> 24)
        {
            if (effect)
            {
                uint32_t destination = 0;
                vertrix_surface_read(target, target_x + i, target_y, &destination);
                if (effect >= 256)
                {
                    vertrix_render_weighted_pixel(pixel, destination, (uint8_t)(effect - 256),
                                                  &pixel);
                }
                else
                {
                    vertrix_render_effect_pixel(pixel, destination, (uint8_t)effect, &pixel);
                }
            }
            vertrix_surface_write(target, target_x + i, target_y, pixel);
        }
        source_x += advances[i];
    }
    return 1;
}

static int sample32(const VertrixSurface *source, uint32_t source_x, uint32_t source_y,
                    VertrixSurface *target, uint32_t target_x, uint32_t target_y,
                    const uint8_t *horizontal, size_t horizontal_count, const uint8_t *vertical,
                    size_t vertical_count, uint16_t width, uint16_t height, int binary,
                    uint16_t effect)
{
    if (!source || !target || source->bytes_per_pixel != 4 || target->bytes_per_pixel != 4 ||
        !horizontal || !vertical || horizontal_count < width || vertical_count < height)
    {
        return 0;
    }
    if (!width || !height)
    {
        return 1;
    }
    uint64_t last_x = source_x;
    uint64_t last_y = source_y;
    for (uint32_t i = 0; i + 1 < width; ++i)
    {
        last_x += horizontal[i];
    }
    for (uint32_t i = 0; i + 1 < height; ++i)
    {
        last_y += vertical[i];
    }
    size_t offset;
    if (last_x > UINT32_MAX || last_y > UINT32_MAX || (uint64_t)target_x + width > target->width ||
        (uint64_t)target_y + height > target->height ||
        !location(source, (uint32_t)last_x, (uint32_t)last_y, &offset) ||
        !location(target, target_x + width - 1, target_y + height - 1, &offset))
    {
        return 0;
    }
    for (uint32_t row = 0; row < height; ++row)
    {
        sample_row32(source, source_x, source_y, target, target_x, target_y + row, horizontal,
                     horizontal_count, width, binary, effect);
        source_y += vertical[row];
    }
    return 1;
}

int vertrix_surface_sample_row32(const VertrixSurface *source, uint32_t source_x, uint32_t source_y,
                                 VertrixSurface *target, uint32_t target_x, uint32_t target_y,
                                 const uint8_t *advances, size_t advance_count, uint16_t width)
{
    return sample_row32(source, source_x, source_y, target, target_x, target_y, advances,
                        advance_count, width, 0, 0);
}
int vertrix_surface_sample32(const VertrixSurface *source, uint32_t source_x, uint32_t source_y,
                             VertrixSurface *target, uint32_t target_x, uint32_t target_y,
                             const uint8_t *horizontal, size_t horizontal_count,
                             const uint8_t *vertical, size_t vertical_count, uint16_t width,
                             uint16_t height)
{
    return sample32(source, source_x, source_y, target, target_x, target_y, horizontal,
                    horizontal_count, vertical, vertical_count, width, height, 0, 0);
}

int vertrix_surface_sample_binary_row32(const VertrixSurface *source, uint32_t source_x,
                                        uint32_t source_y, VertrixSurface *target,
                                        uint32_t target_x, uint32_t target_y,
                                        const uint8_t *advances, size_t advance_count,
                                        uint16_t width)
{
    return sample_row32(source, source_x, source_y, target, target_x, target_y, advances,
                        advance_count, width, 1, 0);
}
int vertrix_surface_sample_binary32(const VertrixSurface *source, uint32_t source_x,
                                    uint32_t source_y, VertrixSurface *target, uint32_t target_x,
                                    uint32_t target_y, const uint8_t *horizontal,
                                    size_t horizontal_count, const uint8_t *vertical,
                                    size_t vertical_count, uint16_t width, uint16_t height)
{
    return sample32(source, source_x, source_y, target, target_x, target_y, horizontal,
                    horizontal_count, vertical, vertical_count, width, height, 1, 0);
}

int vertrix_surface_sample_effect32(const VertrixSurface *source, uint32_t source_x,
                                    uint32_t source_y, VertrixSurface *target, uint32_t target_x,
                                    uint32_t target_y, const uint8_t *horizontal,
                                    size_t horizontal_count, const uint8_t *vertical,
                                    size_t vertical_count, uint16_t width, uint16_t height,
                                    uint8_t effect, int binary)
{
    if (effect != 1 && (effect < 3 || effect > 8))
    {
        return 0;
    }
    return sample32(source, source_x, source_y, target, target_x, target_y, horizontal,
                    horizontal_count, vertical, vertical_count, width, height, binary, effect);
}

int vertrix_surface_sample_weighted32(const VertrixSurface *source, uint32_t source_x,
                                      uint32_t source_y, VertrixSurface *target, uint32_t target_x,
                                      uint32_t target_y, const uint8_t *horizontal,
                                      size_t horizontal_count, const uint8_t *vertical,
                                      size_t vertical_count, uint16_t width, uint16_t height,
                                      uint8_t amount, int binary)
{
    if (amount > 100)
    {
        return 0;
    }
    return sample32(source, source_x, source_y, target, target_x, target_y, horizontal,
                    horizontal_count, vertical, vertical_count, width, height, binary,
                    (uint16_t)(256 + amount));
}
