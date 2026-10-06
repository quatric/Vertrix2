#include "surface_blit.h"
#include <string.h>

enum
{
    FORMAT_RGB555 = 1,
    FORMAT_RGB565 = 2,
    BYTES_8 = 1,
    BYTES_16 = 2,
    BYTES_24 = 3,
    BYTES_32 = 4,
    RGB24_BYTES = 3
};

/* Pixel packing and unpacking between 0x00RRGGBB and the narrow formats. */
static uint32_t pack_565(uint32_t pixel)
{
    return (((pixel & 0xf80000) >> 5) | ((pixel & 0xfc00) >> 2) | (pixel & 0xf8)) >> 3;
}

static uint32_t pack_555(uint32_t pixel)
{
    return (((pixel & 0xf80000) >> 6) | ((pixel & 0xf800) >> 3) | (pixel & 0xf8)) >> 3;
}

static uint32_t pack_332(uint32_t pixel)
{
    return (((pixel & 0xe00000) >> 10) | ((pixel & 0xe000) >> 5) | (pixel & 0xc0)) >> 6;
}

static uint32_t unpack_565(uint32_t word)
{
    return (((word & 0xf800) << 5) | ((word & 0x7e0) << 2) | (word & 0x1f)) << 3;
}

static uint32_t unpack_555(uint32_t word)
{
    return (((word & 0x7c00) << 6) | ((word & 0x3e0) << 3) | (word & 0x1f)) << 3;
}

static uint32_t unpack_332(uint32_t byte)
{
    return (((byte & 0xe0) << 10) | ((byte & 0x1c) << 5) | (byte & 3)) << 6;
}

static uint32_t load32(const uint8_t *bytes)
{
    return (uint32_t)bytes[0] | (uint32_t)bytes[1] << 8 | (uint32_t)bytes[2] << 16 |
           (uint32_t)bytes[3] << 24;
}

static void store32(uint8_t *bytes, uint32_t value)
{
    for (int i = 0; i < 4; ++i)
    {
        bytes[i] = (uint8_t)(value >> (8 * i));
    }
}

static uint32_t load16(const uint8_t *bytes)
{
    return (uint32_t)bytes[0] | (uint32_t)bytes[1] << 8;
}

static void store16(uint8_t *bytes, uint32_t value)
{
    bytes[0] = (uint8_t)value;
    bytes[1] = (uint8_t)(value >> 8);
}

typedef enum
{
    ROW_NONE,
    ROW_COPY,
    ROW_32_TO_24,
    ROW_32_TO_565,
    ROW_32_TO_555,
    ROW_32_TO_332,
    ROW_332_TO_32,
    ROW_565_TO_32,
    ROW_555_TO_32
} RowKind;

static RowKind row_kind(const VertrixBlitSurface *target, const VertrixBlitSurface *source,
                        int pitched)
{
    uint8_t to = target->surface.bytes_per_pixel;
    uint8_t from = source->surface.bytes_per_pixel;
    if (to == from)
    {
        return (pitched || to == BYTES_32 || to == BYTES_16 || to == BYTES_8) ? ROW_COPY : ROW_NONE;
    }
    if (to == BYTES_24 && from == BYTES_32)
    {
        return ROW_32_TO_24;
    }
    if (to == BYTES_16 && from == BYTES_32)
    {
        return target->sub_format == FORMAT_RGB565   ? ROW_32_TO_565
               : target->sub_format == FORMAT_RGB555 ? ROW_32_TO_555
                                                     : ROW_NONE;
    }
    if (to == BYTES_8 && from == BYTES_32)
    {
        return ROW_32_TO_332;
    }
    if (to == BYTES_32 && from == BYTES_8)
    {
        return ROW_332_TO_32;
    }
    if (to == BYTES_32 && from == BYTES_16)
    {
        return source->sub_format == FORMAT_RGB565   ? ROW_565_TO_32
               : source->sub_format == FORMAT_RGB555 ? ROW_555_TO_32
                                                     : ROW_NONE;
    }
    return ROW_NONE;
}

static void convert_row(RowKind kind, uint8_t *to, const uint8_t *from, uint32_t width,
                        uint32_t to_bytes)
{
    for (uint32_t i = 0; i < width; ++i)
    {
        switch (kind)
        {
            case ROW_COPY:
                memmove(to + (size_t)i * to_bytes, from + (size_t)i * to_bytes, to_bytes);
                break;
            case ROW_32_TO_24:
                memcpy(to + (size_t)i * RGB24_BYTES, from + (size_t)i * BYTES_32, RGB24_BYTES);
                break;
            case ROW_32_TO_565:
                store16(to + (size_t)i * BYTES_16, pack_565(load32(from + (size_t)i * BYTES_32)));
                break;
            case ROW_32_TO_555:
                store16(to + (size_t)i * BYTES_16, pack_555(load32(from + (size_t)i * BYTES_32)));
                break;
            case ROW_32_TO_332:
                to[i] = (uint8_t)pack_332(load32(from + (size_t)i * BYTES_32));
                break;
            case ROW_332_TO_32:
                store32(to + (size_t)i * BYTES_32, unpack_332(from[i]));
                break;
            case ROW_565_TO_32:
                store32(to + (size_t)i * BYTES_32, unpack_565(load16(from + (size_t)i * BYTES_16)));
                break;
            case ROW_555_TO_32:
                store32(to + (size_t)i * BYTES_32, unpack_555(load16(from + (size_t)i * BYTES_16)));
                break;
            case ROW_NONE:
                break;
        }
    }
}

/* Whether a rectangle of rows lies inside the storage; offsets are computed in 64 bits. */
static int rectangle_fits(const VertrixSurface *surface, uint64_t stride, uint32_t x, uint32_t y,
                          uint32_t width, uint32_t height, uint32_t bytes)
{
    if (!surface->data || width == 0 || height == 0)
    {
        return 1;
    }
    uint64_t first = (uint64_t)y * stride + (uint64_t)x * surface->bytes_per_pixel;
    uint64_t last = first + (uint64_t)(height - 1) * stride + (uint64_t)width * bytes;
    return last <= surface->size;
}

int vertrix_surface_blit(VertrixBlitSurface *target, const VertrixBlitSurface *source,
                         uint32_t target_x, uint32_t target_y, uint32_t source_x, uint32_t source_y,
                         uint32_t width, uint32_t height)
{
    int pitched = target->pitched != 0 || source->pitched != 0;
    RowKind kind = row_kind(target, source, pitched);
    uint64_t target_stride =
        pitched ? target->surface.stride
                : (uint64_t)target->surface.width * target->surface.bytes_per_pixel;
    uint64_t source_stride =
        pitched ? source->surface.stride
                : (uint64_t)source->surface.width * source->surface.bytes_per_pixel;
    if (kind == ROW_NONE || width == 0 || height == 0)
    {
        return 1;
    }
    if (!target->surface.data || !source->surface.data ||
        !rectangle_fits(&target->surface, target_stride, target_x, target_y, width, height,
                        target->surface.bytes_per_pixel) ||
        !rectangle_fits(&source->surface, source_stride, source_x, source_y, width, height,
                        source->surface.bytes_per_pixel))
    {
        return 0;
    }
    for (uint32_t row = 0; row < height; ++row)
    {
        uint8_t *to = target->surface.data + (uint64_t)(target_y + row) * target_stride +
                      (uint64_t)target_x * target->surface.bytes_per_pixel;
        const uint8_t *from = source->surface.data + (uint64_t)(source_y + row) * source_stride +
                              (uint64_t)source_x * source->surface.bytes_per_pixel;
        convert_row(kind, to, from, width, target->surface.bytes_per_pixel);
    }
    return 1;
}

int vertrix_surface_blit_progress(VertrixBlitSurface *target, const VertrixBlitSurface *source,
                                  uint32_t numerator, uint32_t denominator)
{
    if (denominator == 0)
    {
        return 0;
    }
    uint32_t width = (uint32_t)((uint32_t)(source->surface.width * numerator) / denominator);
    return vertrix_surface_blit(target, source, 0, VERTRIX_PROGRESS_ROW, 0, 0, width,
                                source->surface.height);
}

int vertrix_surface_blit_region(VertrixBlitSurface *target, const VertrixBlitSurface *source,
                                const uint16_t region[4])
{
    return vertrix_surface_blit(target, source, 0, 0, region[0], region[1], region[2], region[3]);
}

int vertrix_surface_blit_whole(VertrixBlitSurface *target, const VertrixBlitSurface *source)
{
    if (!target || !source)
    {
        return 1;
    }
    return vertrix_surface_blit(target, source, 0, 0, 0, 0, target->surface.width,
                                target->surface.height);
}

/* Colour of the pixel at index of a packed row buffer, as 0x00RRGGBB. */
static uint32_t fade_load(const uint8_t *pixels, uint32_t index, uint8_t bytes, uint8_t sub_format)
{
    if (bytes == BYTES_32)
    {
        return load32(pixels + (size_t)index * BYTES_32);
    }
    uint32_t word = load16(pixels + (size_t)index * BYTES_16);
    return sub_format == FORMAT_RGB565 ? unpack_565(word) : unpack_555(word);
}

static uint32_t fade_channel(const uint8_t *tables, uint32_t percent, uint32_t own,
                             uint32_t average, unsigned shift)
{
    uint32_t keep = tables[percent * VERTRIX_FADE_TABLE_SIZE + ((own >> shift) & 0xff)];
    uint32_t blend = tables[(VERTRIX_FADE_PERCENT_MAX - percent) * VERTRIX_FADE_TABLE_SIZE +
                            ((average >> shift) & 0xff)];
    return (keep + blend) << shift;
}

int vertrix_surface_fade(VertrixBlitSurface *surface, uint32_t x, uint32_t y, uint32_t width,
                         uint32_t height, uint32_t percent, const uint8_t *tables, uint8_t *scratch)
{
    uint8_t bytes = surface->surface.bytes_per_pixel;
    if (bytes == BYTES_8)
    {
        return 1;
    }
    VertrixBlitSurface copy = {
        {scratch, (size_t)width * height * bytes, width, height, width * bytes, bytes},
        surface->sub_format,
        0};
    int result = vertrix_surface_blit(&copy, surface, 0, 0, x, y, width, height);
    if ((bytes != BYTES_32 && bytes != BYTES_16) || width == 0 || height == 0)
    {
        return result;
    }
    for (uint32_t row = 0; row < height; ++row)
    {
        uint8_t *destination =
            surface->surface.data + ((uint64_t)(y + row) * surface->surface.width + x) * bytes;
        for (uint32_t column = 0; column < width; ++column)
        {
            uint32_t sums[VERTRIX_FADE_CHANNELS] = {0, 0, 0};
            uint32_t count = 0;
            uint32_t neighbours[4];
            int present[4] = {row > 0, row + 1 < height, column > 0, column + 1 < width};
            uint32_t at[4] = {(row - 1) * width + column, (row + 1) * width + column,
                              row * width + column - 1, row * width + column + 1};
            for (int n = 0; n < 4; ++n)
            {
                if (present[n])
                {
                    neighbours[n] = fade_load(scratch, at[n], bytes, copy.sub_format);
                    sums[0] += (neighbours[n] >> 16) & 0xff;
                    sums[1] += (neighbours[n] >> 8) & 0xff;
                    sums[2] += neighbours[n] & 0xff;
                    ++count;
                }
            }
            if (count == 0)
            {
                continue;
            }
            uint32_t average = (sums[0] / count) << 16 | (sums[1] / count) << 8 | sums[2] / count;
            uint32_t own = fade_load(scratch, row * width + column, bytes, copy.sub_format);
            uint32_t mixed = fade_channel(tables, percent, own, average, 16) |
                             fade_channel(tables, percent, own, average, 8) |
                             fade_channel(tables, percent, own, average, 0);
            if (bytes == BYTES_32)
            {
                store32(destination + (size_t)column * BYTES_32, mixed);
            }
            else
            {
                store16(destination + (size_t)column * BYTES_16,
                        copy.sub_format == FORMAT_RGB565 ? pack_565(mixed) : pack_555(mixed));
            }
        }
    }
    return result;
}
