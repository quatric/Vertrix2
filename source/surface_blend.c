#include "surface_blend.h"

enum
{
    PIXEL_BYTES = 4,
    TABLE_STRIDE_SHIFT = 8
};

static int pixel_offset(const VertrixBlendSurface *surface, uint32_t address, size_t *offset)
{
    uint32_t relative = address - surface->address;
    if ((size_t)relative + PIXEL_BYTES > surface->size)
    {
        return 0;
    }
    *offset = relative;
    return 1;
}

static uint32_t load(const uint8_t *data)
{
    return (uint32_t)data[0] | (uint32_t)data[1] << 8 | (uint32_t)data[2] << 16 |
           (uint32_t)data[3] << 24;
}

static void store(uint8_t *data, uint32_t value)
{
    data[0] = (uint8_t)value;
    data[1] = (uint8_t)(value >> 8);
    data[2] = (uint8_t)(value >> 16);
    data[3] = (uint8_t)(value >> 24);
}

int vertrix_surface_blend(VertrixBlendSurface *target, const VertrixBlendSurface *source,
                          uint32_t row, uint32_t column, const uint32_t arguments[5],
                          const uint8_t *tables, VertrixBlendScratch *scratch)
{
    uint32_t source_column = arguments[0];
    uint32_t source_row = arguments[1];
    uint32_t width = arguments[2];
    uint32_t height = arguments[3];
    uint32_t percent = arguments[4];
    uint32_t source_pointer = scratch->source;
    uint32_t destination;
    const uint8_t *first;
    const uint8_t *second;
    scratch->target_depth = target->bytes_per_pixel;
    scratch->source_depth = source->bytes_per_pixel;
    scratch->target_format = target->sub_format;
    scratch->source_format = source->sub_format;
    if (scratch->target_depth != PIXEL_BYTES || scratch->target_depth != scratch->source_depth)
    {
        scratch->source = source_pointer;
        return 1;
    }
    scratch->table_first = VERTRIX_BLEND_TABLES + (percent << TABLE_STRIDE_SHIFT);
    scratch->table_second =
        VERTRIX_BLEND_TABLES + ((VERTRIX_BLEND_PERCENT_MAX - percent) << TABLE_STRIDE_SHIFT);
    first = tables + (percent << TABLE_STRIDE_SHIFT);
    second = tables + ((VERTRIX_BLEND_PERCENT_MAX - percent) << TABLE_STRIDE_SHIFT);
    scratch->target_width = target->width;
    scratch->source_width = source->width;
    scratch->skip_target = target->width - width;
    scratch->skip_source = source->width - width;
    destination = target->address + target->width * row * PIXEL_BYTES + column * PIXEL_BYTES;
    scratch->destination = destination;
    source_pointer =
        source->address + source->width * source_row * PIXEL_BYTES + source_column * PIXEL_BYTES;
    while (height != 0)
    {
        uint32_t count = width;
        scratch->counter = count;
        while (count != 0)
        {
            size_t source_offset;
            size_t target_offset;
            uint32_t from;
            if (!pixel_offset(source, source_pointer, &source_offset) ||
                !pixel_offset(target, scratch->destination, &target_offset))
            {
                scratch->source = source_pointer;
                return 0;
            }
            from = load(source->data + source_offset);
            if ((from >> 24) != 0)
            {
                uint32_t to = load(target->data + target_offset);
                uint32_t red = (uint32_t)first[(from >> 16) & 0xff] + second[(to >> 16) & 0xff];
                uint32_t green = (uint32_t)first[(from >> 8) & 0xff] + second[(to >> 8) & 0xff];
                uint32_t blue = (uint32_t)first[from & 0xff] + second[to & 0xff];
                store(target->data + target_offset, (red << 16 | 0xff000000u) | green << 8 | blue);
            }
            scratch->destination += PIXEL_BYTES;
            source_pointer += PIXEL_BYTES;
            --count;
            scratch->counter = count;
        }
        scratch->destination += scratch->skip_target * PIXEL_BYTES;
        source_pointer += scratch->skip_source * PIXEL_BYTES;
        --height;
    }
    scratch->source = source_pointer;
    return 1;
}
