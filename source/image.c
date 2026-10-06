#include "image.h"

#include <stdlib.h>
#include <string.h>

static uint32_t image_word(const unsigned char *bytes)
{
    return (uint32_t)bytes[0] | (uint32_t)bytes[1] << 8 | (uint32_t)bytes[2] << 16 |
           (uint32_t)bytes[3] << 24;
}

static uint16_t image_halfword(const unsigned char *bytes)
{
    return (uint16_t)((uint16_t)bytes[0] | (uint16_t)bytes[1] << 8);
}

void vertrix_image_free(VertrixImage *image)
{
    if (image)
    {
        free(image->rgba);
        image->rgba = NULL;
        image->width = 0;
        image->height = 0;
    }
}

int vertrix_image_bmp(VertrixVf *archive, const char *name, VertrixImage *image)
{
    uint32_t index, size;
    unsigned char header[54];
    if (!image || image->rgba || !vertrix_vf_find(archive, name, &index) ||
        !vertrix_vf_size(archive, index, &size) || size < sizeof(header) ||
        !vertrix_vf_read(archive, index, 0, header, sizeof(header)) || header[0] != 'B' ||
        header[1] != 'M' || image_word(header + 14) != 40 || image_halfword(header + 26) != 1 ||
        image_halfword(header + 28) != 24 || image_word(header + 30) != 0)
    {
        return 0;
    }
    uint32_t offset = image_word(header + 10);
    uint32_t width = image_word(header + 18);
    uint32_t height_bits = image_word(header + 22);
    int top_down = height_bits >= 0x80000000u;
    uint32_t height = top_down ? 0u - height_bits : height_bits;
    uint64_t stride = ((uint64_t)width * 3 + 3) & ~UINT64_C(3);
    uint64_t pixels = (uint64_t)width * height;
    if (!width || width >= 0x80000000u || !height || height >= 0x80000000u ||
        offset < sizeof(header) || (uint64_t)offset + stride * height > size ||
        pixels > SIZE_MAX / 4)
    {
        return 0;
    }
    unsigned char *rgba = malloc((size_t)pixels * 4);
    unsigned char *row = malloc((size_t)stride);
    if (!rgba || !row)
    {
        free(rgba);
        free(row);
        return 0;
    }
    for (uint32_t y = 0; y < height; y++)
    {
        uint32_t row_offset = (uint32_t)((uint64_t)offset + stride * y);
        if (!vertrix_vf_read(archive, index, row_offset, row, (size_t)stride))
        {
            free(row);
            free(rgba);
            return 0;
        }
        uint32_t output_y = top_down ? y : height - 1 - y;
        unsigned char *output = rgba + (size_t)output_y * width * 4;
        for (uint32_t x = 0; x < width; x++)
        {
            output[(size_t)x * 4] = row[(size_t)x * 3 + 2];
            output[(size_t)x * 4 + 1] = row[(size_t)x * 3 + 1];
            output[(size_t)x * 4 + 2] = row[(size_t)x * 3];
            output[(size_t)x * 4 + 3] = 255;
        }
    }
    free(row);
    image->width = width;
    image->height = height;
    image->rgba = rgba;
    return 1;
}

typedef struct
{
    VertrixVf *archive;
    uint32_t index;
    uint32_t position;
    uint32_t end;
    size_t used;
    size_t count;
    unsigned char buffer[4096];
} PcxReader;

static int pcx_byte(PcxReader *reader, unsigned char *byte)
{
    if (reader->used == reader->count)
    {
        if (reader->position >= reader->end)
        {
            return 0;
        }
        reader->count = reader->end - reader->position;
        if (reader->count > sizeof(reader->buffer))
        {
            reader->count = sizeof(reader->buffer);
        }
        if (!vertrix_vf_read(reader->archive, reader->index, reader->position, reader->buffer,
                             reader->count))
        {
            return 0;
        }
        reader->position += (uint32_t)reader->count;
        reader->used = 0;
    }
    *byte = reader->buffer[reader->used++];
    return 1;
}

void vertrix_pcx_free(VertrixPcx *image)
{
    if (image)
    {
        free(image->indices);
        memset(image, 0, sizeof(*image));
    }
}

int vertrix_image_pcx(VertrixVf *archive, const char *name, VertrixPcx *image)
{
    uint32_t index, size;
    unsigned char header[128];
    unsigned char palette[769];
    if (!image || image->indices || !vertrix_vf_find(archive, name, &index) ||
        !vertrix_vf_size(archive, index, &size) || size < sizeof(header) + sizeof(palette) ||
        !vertrix_vf_read(archive, index, 0, header, sizeof(header)) || header[0] != 10 ||
        header[1] != 5 || header[2] != 1 || header[3] != 8 || header[65] != 1)
    {
        return 0;
    }
    uint32_t left = image_halfword(header + 4);
    uint32_t top = image_halfword(header + 6);
    uint32_t right = image_halfword(header + 8);
    uint32_t bottom = image_halfword(header + 10);
    uint32_t stride = image_halfword(header + 66);
    if (right < left || bottom < top)
    {
        return 0;
    }
    uint32_t width = right - left + 1;
    uint32_t height = bottom - top + 1;
    uint32_t palette_offset = size - sizeof(palette);
    uint64_t pixels = (uint64_t)width * height;
    if (stride < width || pixels > SIZE_MAX ||
        (uint64_t)stride * height > (uint64_t)(palette_offset - sizeof(header)) * 63 ||
        !vertrix_vf_read(archive, index, palette_offset, palette, sizeof(palette)) ||
        palette[0] != 12)
    {
        return 0;
    }
    unsigned char *indices = malloc((size_t)pixels);
    if (!indices)
    {
        return 0;
    }
    PcxReader reader = {0};
    reader.archive = archive;
    reader.index = index;
    reader.position = sizeof(header);
    reader.end = palette_offset;
    unsigned repeat = 0;
    unsigned char value = 0;
    for (uint32_t y = 0; y < height; y++)
    {
        for (uint32_t x = 0; x < stride; x++)
        {
            if (!repeat)
            {
                if (!pcx_byte(&reader, &value))
                {
                    goto failure;
                }
                repeat = 1;
                if ((value & 0xc0) == 0xc0)
                {
                    repeat = value & 0x3f;
                    if (!repeat || !pcx_byte(&reader, &value))
                    {
                        goto failure;
                    }
                }
            }
            if (x < width)
            {
                indices[(size_t)y * width + x] = value;
            }
            repeat--;
        }
    }
    if (repeat)
    {
        goto failure;
    }
    image->width = width;
    image->height = height;
    image->indices = indices;
    memcpy(image->palette, palette + 1, sizeof(image->palette));
    return 1;

failure:
    free(indices);
    return 0;
}

void vertrix_sprite_free(VertrixSpriteFrame *frame)
{
    if (frame)
    {
        vertrix_image_free(&frame->image);
        memset(frame, 0, sizeof(*frame));
    }
}

int vertrix_image_sprite(VertrixVf *archive, const char *name, uint32_t frame,
                         VertrixSpriteFrame *output)
{
    uint32_t index, size;
    unsigned char count_bytes[2];
    if (!output || output->image.rgba || !vertrix_vf_find(archive, name, &index) ||
        !vertrix_vf_size(archive, index, &size) || size < 2 ||
        !vertrix_vf_read(archive, index, 0, count_bytes, 2))
    {
        return 0;
    }
    uint32_t count = image_halfword(count_bytes);
    if (frame >= count || count > (size - 2) / 48)
    {
        return 0;
    }
    uint64_t cursor = 2;
    uint32_t selected_offset = 0;
    uint32_t width = 0, height = 0;
    uint32_t metadata[10];
    for (uint32_t i = 0; i < count; i++)
    {
        unsigned char header[48];
        if (cursor + sizeof(header) > size ||
            !vertrix_vf_read(archive, index, (uint32_t)cursor, header, sizeof(header)) ||
            header[0] != 0 || header[47] != 4)
        {
            return 0;
        }
        uint32_t frame_width = image_word(header + 12);
        uint32_t frame_height = image_word(header + 16);
        uint64_t pixels = (uint64_t)frame_width * frame_height;
        cursor += sizeof(header);
        if (!frame_width || !frame_height || pixels > (size - cursor) / 4 || pixels > SIZE_MAX / 4)
        {
            return 0;
        }
        if (i == frame)
        {
            selected_offset = (uint32_t)cursor;
            width = frame_width;
            height = frame_height;
            for (unsigned word = 0; word < 10; word++)
            {
                metadata[word] = image_word(header + 8 + word * 4);
            }
        }
        cursor += pixels * 4;
    }
    if (cursor != size)
    {
        return 0;
    }
    size_t bytes = (size_t)width * height * 4;
    unsigned char *rgba = malloc(bytes);
    if (!rgba)
    {
        return 0;
    }
    if (!vertrix_vf_read(archive, index, selected_offset, rgba, bytes))
    {
        free(rgba);
        return 0;
    }
    for (size_t pixel = 0; pixel < bytes; pixel += 4)
    {
        unsigned char blue = rgba[pixel];
        rgba[pixel] = rgba[pixel + 2];
        rgba[pixel + 2] = blue;
    }
    output->image.width = width;
    output->image.height = height;
    output->image.rgba = rgba;
    output->frame_count = count;
    memcpy(output->metadata, metadata, sizeof(metadata));
    return 1;
}

int vertrix_image_block_frame(const VertrixImage *sheet, uint32_t color, uint32_t frame,
                              VertrixImage *output)
{
    if (!sheet || !sheet->rgba || !output || output->rgba || output->width || output->height ||
        color >= 7 || frame >= 8 || sheet->width < 192 || sheet->height < 168 ||
        (uint64_t)sheet->width * sheet->height > SIZE_MAX / 4)
    {
        return 0;
    }
    uint32_t color_row = color == 5 ? 0 : color == 6 ? 6 : color + 1;
    unsigned char *pixels = malloc(24 * 24 * 4);
    if (!pixels)
    {
        return 0;
    }
    for (uint32_t row = 0; row < 24; ++row)
    {
        size_t source = ((size_t)(color_row * 24 + row) * sheet->width + frame * 24) * 4;
        memcpy(pixels + row * 24 * 4, sheet->rgba + source, 24 * 4);
    }
    output->width = 24;
    output->height = 24;
    output->rgba = pixels;
    return 1;
}

int vertrix_image_mask(VertrixImage *image, const VertrixPcx *mask)
{
    if (!image || !mask || !image->rgba || !mask->indices || !image->width || !image->height ||
        image->width != mask->width || image->height != mask->height ||
        (uint64_t)image->width * image->height > SIZE_MAX / 4)
    {
        return 0;
    }
    size_t count = (size_t)image->width * image->height;
    for (size_t index = 0; index < count; ++index)
    {
        image->rgba[index * 4 + 3] = mask->indices[index] ? 255 : 0;
    }
    return 1;
}

int vertrix_image_mask_graded(VertrixImage *image, const VertrixPcx *mask, int32_t offset)
{
    if (!image || !mask || !image->rgba || !mask->indices || !image->width || !image->height ||
        image->width != mask->width || image->height != mask->height ||
        (uint64_t)image->width * image->height > SIZE_MAX / 4)
    {
        return 0;
    }
    size_t count = (size_t)image->width * image->height;
    for (size_t index = 0; index < count; ++index)
    {
        uint32_t alpha = mask->indices[index];
        if (alpha)
        {
            alpha = (alpha + (uint32_t)offset) & 65535;
            if (alpha >= 255)
            {
                alpha = 255;
            }
        }
        unsigned char *pixel = image->rgba + index * 4;
        for (unsigned channel = 0; channel < 3; ++channel)
        {
            pixel[channel] = (unsigned char)((uint32_t)pixel[channel] * alpha / 255);
        }
        pixel[3] = (unsigned char)alpha;
    }
    return 1;
}

int vertrix_image_bmp_masked(VertrixVf *archive, const char *artwork, const char *mask,
                             VertrixImage *output)
{
    VertrixImage decoded = {0};
    VertrixPcx decoded_mask = {0};
    if (!output || output->rgba || output->width || output->height ||
        !vertrix_image_bmp(archive, artwork, &decoded))
    {
        return 0;
    }
    int success = vertrix_image_pcx(archive, mask, &decoded_mask) &&
                  vertrix_image_mask(&decoded, &decoded_mask);
    vertrix_pcx_free(&decoded_mask);
    if (!success)
    {
        vertrix_image_free(&decoded);
        return 0;
    }
    *output = decoded;
    return 1;
}

int vertrix_image_sprite_processed(VertrixVf *archive, const char *name, uint32_t frame,
                                   const uint32_t masks[3], VertrixSpriteFrame *output)
{
    VertrixSpriteFrame decoded = {0};
    if (!output || output->image.rgba || output->image.width || output->image.height ||
        !vertrix_image_sprite(archive, name, frame, &decoded))
    {
        return 0;
    }
    if (!vertrix_image_binary_alpha(&decoded.image) ||
        !vertrix_image_color_order(&decoded.image, masks))
    {
        vertrix_sprite_free(&decoded);
        return 0;
    }
    *output = decoded;
    return 1;
}

int vertrix_image_color_order(VertrixImage *image, const uint32_t masks[3])
{
    unsigned shifts[3];
    unsigned slots[3];
    if (!image || !image->rgba || !image->width || !image->height || !masks ||
        (uint64_t)image->width * image->height > SIZE_MAX / 4)
    {
        return 0;
    }
    for (unsigned channel = 0; channel < 3; ++channel)
    {
        uint32_t mask = masks[channel];
        if (!mask)
        {
            return 0;
        }
        shifts[channel] = 0;
        while (!(mask & 1))
        {
            ++shifts[channel];
            mask >>= 1;
        }
    }
    for (unsigned channel = 0; channel < 3; ++channel)
    {
        unsigned rank = 0;
        for (unsigned other = 0; other < 3; ++other)
        {
            if (channel != other && shifts[channel] == shifts[other])
            {
                return 0;
            }
            rank += shifts[channel] > shifts[other];
        }
        slots[channel] = 2 - rank;
    }
    size_t count = (size_t)image->width * image->height;
    for (size_t index = 0; index < count; ++index)
    {
        unsigned char *pixel = image->rgba + index * 4;
        unsigned char rgb[3] = {pixel[0], pixel[1], pixel[2]};
        for (unsigned channel = 0; channel < 3; ++channel)
        {
            pixel[slots[channel]] = rgb[channel];
        }
    }
    return 1;
}

int vertrix_image_binary_alpha(VertrixImage *image)
{
    if (!image || !image->rgba || !image->width || !image->height)
    {
        return 0;
    }
    uint64_t pixels = (uint64_t)image->width * image->height;
    if (pixels > SIZE_MAX / 4)
    {
        return 0;
    }
    for (size_t pixel = 0; pixel < (size_t)pixels; pixel++)
    {
        unsigned char *alpha = &image->rgba[pixel * 4 + 3];
        *alpha = *alpha ? 0 : 255;
    }
    return 1;
}
