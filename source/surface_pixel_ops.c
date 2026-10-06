#include "surface_pixel_ops.h"
#include <string.h>

static int in_range(size_t size, uint64_t offset, uint64_t length)
{
    return offset <= size && length <= size - offset;
}

int vertrix_surface_or_rectangle(VertrixSurface *surface, uint32_t x, uint32_t y, uint32_t width,
                                 uint32_t rows, uint8_t value)
{
    if (!surface || !surface->data)
    {
        return 0;
    }
    uint32_t start = surface->width * y + x;
    uint32_t advance = surface->width - width;
    uint32_t offset = start;
    for (uint32_t row = 0; row < rows; ++row)
    {
        if (width != 0 && !in_range(surface->size, offset, width))
        {
            return 0;
        }
        offset += width;
        offset += advance;
    }
    offset = start;
    for (uint32_t row = 0; row < rows; ++row)
    {
        for (uint32_t column = 0; column < width; ++column)
        {
            surface->data[offset + column] |= value;
        }
        offset += width;
        offset += advance;
    }
    return 1;
}

int vertrix_surface_copy_pixel(const VertrixSurface *source, VertrixSurface *target, int32_t x,
                               int32_t y)
{
    if (!source || !target || !source->data || !target->data)
    {
        return 0;
    }
    if (x < 0 || (uint32_t)x >= target->width || y < 0 || (uint32_t)y >= target->height)
    {
        return 1;
    }
    uint32_t size = target->bytes_per_pixel;
    if (size != 1 && size != 2 && size != 4)
    {
        return 1;
    }
    uint32_t from = vertrix_surface_offset(source->stride, source->bytes_per_pixel, x, y);
    uint32_t to = vertrix_surface_offset(target->stride, target->bytes_per_pixel, x, y);
    if (!in_range(source->size, from, size) || !in_range(target->size, to, size))
    {
        return 0;
    }
    memmove(target->data + to, source->data + from, size);
    return 1;
}

static int16_t low_word(uint32_t value)
{
    return (int16_t)(uint16_t)value;
}

int vertrix_surface_flip_vertical(VertrixSurface *surface)
{
    if (!surface || !surface->data)
    {
        return 0;
    }
    int32_t unit = surface->bytes_per_pixel;
    if (unit < 1 || unit > 4)
    {
        return 1;
    }
    int32_t width = low_word(surface->width);
    int32_t height = low_word(surface->height);
    if (height < 0)
    {
        return 0;
    }
    int32_t row_bytes = unit == 3 ? low_word((uint32_t)(width * 3)) : width * unit;
    uint32_t pairs = (uint32_t)height / 2;
    if (pairs == 0 || row_bytes <= 0)
    {
        return 1;
    }
    uint64_t span = (uint64_t)(height - 1) * (uint64_t)row_bytes;
    if (!in_range(surface->size, 0, span + (uint64_t)row_bytes))
    {
        return 0;
    }
    uint8_t *top = surface->data;
    uint8_t *bottom = surface->data + span;
    for (uint32_t row = 0; row < pairs; ++row)
    {
        for (int32_t i = 0; i < row_bytes; ++i)
        {
            uint8_t saved = top[i];
            top[i] = bottom[i];
            bottom[i] = saved;
        }
        top += row_bytes;
        bottom -= row_bytes;
    }
    return 1;
}

int vertrix_surface_blit_keyed(VertrixSurface *target, uint32_t target_x, uint32_t target_y,
                               const VertrixSurface *source, uint32_t source_x, uint32_t source_y,
                               uint32_t width, uint32_t rows, uint32_t target_flag,
                               uint32_t source_flag)
{
    if (!target || !source || !target->data || !source->data)
    {
        return 0;
    }
    if (target_flag != 0 || source_flag != 0 || target->bytes_per_pixel != 4 ||
        source->bytes_per_pixel != 4)
    {
        return 1;
    }
    uint32_t to = (target->width * target_y + target_x) * 4;
    uint32_t from = (source->width * source_y + source_x) * 4;
    uint32_t target_advance = (target->width - width) * 4;
    uint32_t source_advance = (source->width - width) * 4;
    for (int pass = 0; pass < 2; ++pass)
    {
        uint32_t t = to;
        uint32_t s = from;
        for (uint32_t row = 0; row < rows; ++row)
        {
            if (width != 0 && (!in_range(target->size, t, 4ull * width) ||
                               !in_range(source->size, s, 4ull * width)))
            {
                return 0;
            }
            for (uint32_t column = 0; pass == 1 && column < width; ++column)
            {
                if (source->data[s + 4 * column + 3] != 0)
                {
                    memmove(target->data + t + 4 * column, source->data + s + 4 * column, 4);
                }
            }
            t += 4 * width + target_advance;
            s += 4 * width + source_advance;
        }
    }
    return 1;
}

int vertrix_surface_decimate(const VertrixSurface *source, uint32_t divisor, uint32_t *output,
                             size_t output_count)
{
    if (!source || !source->data || divisor == 0 || (!output && output_count))
    {
        return 0;
    }
    if (source->bytes_per_pixel != 4)
    {
        return 1;
    }
    uint32_t columns = source->width / divisor;
    uint32_t rows = source->height / divisor;
    if ((uint64_t)columns * rows > output_count)
    {
        return 0;
    }
    uint32_t row_jump = (divisor - 1) * source->width * 4;
    uint32_t offset = 0;
    size_t written = 0;
    for (uint32_t row = 0; row < rows; ++row)
    {
        for (uint32_t column = 0; column < columns; ++column)
        {
            if (!in_range(source->size, offset, 4))
            {
                return 0;
            }
            output[written++] = (uint32_t)source->data[offset] |
                                ((uint32_t)source->data[offset + 1] << 8) |
                                ((uint32_t)source->data[offset + 2] << 16) |
                                ((uint32_t)source->data[offset + 3] << 24);
            offset += divisor * 4;
        }
        offset += row_jump;
    }
    return 1;
}
