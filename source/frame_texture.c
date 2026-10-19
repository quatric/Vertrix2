#include "frame_texture.h"
#include <stdlib.h>
#include <string.h>

static int source_layout(const VertrixSurface *frame, const uint32_t masks[3], unsigned slots[4])
{
    if (!frame || !frame->data || frame->bytes_per_pixel != 4 || !frame->width || !frame->height ||
        frame->width > 1024 || frame->height > 1024 || !masks ||
        (uint64_t)(frame->height - 1) * frame->stride + (uint64_t)frame->width * 4 > frame->size)
    {
        return 0;
    }
    unsigned used = 0;
    for (unsigned channel = 0; channel < 3; ++channel)
    {
        unsigned slot = 0;
        while (slot < 4 && masks[channel] != (UINT32_C(255) << (slot * 8)))
        {
            ++slot;
        }
        if (slot == 4 || (used & (1u << slot)))
        {
            return 0;
        }
        slots[channel] = slot;
        used |= 1u << slot;
    }
    for (unsigned slot = 0; slot < 4; ++slot)
    {
        if (!(used & (1u << slot)))
        {
            slots[3] = slot;
        }
    }
    return 1;
}

int vertrix_frame_texture_validate(const VertrixSurface *frame, const uint32_t masks[3],
                                   const VertrixTexture *texture)
{
    unsigned slots[4];
    if (!source_layout(frame, masks, slots) || !texture || !texture->data || !texture->allocation ||
        ((uintptr_t)texture->data & 31))
    {
        return 0;
    }
    uint32_t width = (frame->width + 3) & ~3u;
    uint32_t height = (frame->height + 3) & ~3u;
    return texture->width == frame->width && texture->height == frame->height &&
           texture->storage_width == width && texture->storage_height == height &&
           texture->size == (size_t)width * height * 4;
}

/* A frame whose sides are multiples of 4 fills every tile: no padding to clear and no bounds to
 * test per pixel. Each 4x4 tile is 32 bytes of alpha-red pairs, then 32 of green-blue pairs. */
static void pack_whole(const VertrixSurface *frame, const unsigned slots[4],
                       VertrixTexture *texture)
{
    const unsigned a = slots[3];
    const unsigned r = slots[0];
    const unsigned g = slots[1];
    const unsigned b = slots[2];
    uint8_t *out = texture->data;
    for (uint32_t y = 0; y < frame->height; y += 4)
    {
        const uint8_t *rows = frame->data + (size_t)y * frame->stride;
        for (uint32_t x = 0; x < frame->width; x += 4)
        {
            for (uint32_t row = 0; row < 4; ++row)
            {
                const uint8_t *pixel = rows + (size_t)row * frame->stride + (size_t)x * 4;
                uint8_t *pair = out + row * 8;
                for (uint32_t column = 0; column < 4; ++column)
                {
                    pair[0] = pixel[a];
                    pair[1] = pixel[r];
                    pair[32] = pixel[g];
                    pair[33] = pixel[b];
                    pixel += 4;
                    pair += 2;
                }
            }
            out += 64;
        }
    }
}

static uint32_t little32(const uint8_t *bytes)
{
    uint32_t word;
    memcpy(&word, bytes, 4);
#if defined(__BYTE_ORDER__) && __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
    word = __builtin_bswap32(word);
#endif
    return word;
}

static void put_big32(uint8_t *bytes, uint32_t word)
{
#if !defined(__BYTE_ORDER__) || __BYTE_ORDER__ != __ORDER_BIG_ENDIAN__
    word = __builtin_bswap32(word);
#endif
    memcpy(bytes, &word, 4);
}

/* pack_whole for the frame's own layout, bytes B, G, R and the unused one (slots 2, 1, 0, 3): a
 * pixel read as a little-endian word is unused << 24 | R << 16 | G << 8 | B, so its alpha-red pair
 * is the high half and its green-blue pair the low half, two pixels to a stored word. */
static void pack_whole_bgrx(const VertrixSurface *frame, VertrixTexture *texture)
{
    uint8_t *out = texture->data;
    for (uint32_t y = 0; y < frame->height; y += 4)
    {
        const uint8_t *rows = frame->data + (size_t)y * frame->stride;
        for (uint32_t x = 0; x < frame->width; x += 4)
        {
            for (uint32_t row = 0; row < 4; ++row)
            {
                const uint8_t *pixel = rows + (size_t)row * frame->stride + (size_t)x * 4;
                const uint32_t p0 = little32(pixel);
                const uint32_t p1 = little32(pixel + 4);
                const uint32_t p2 = little32(pixel + 8);
                const uint32_t p3 = little32(pixel + 12);
                uint8_t *pair = out + row * 8;
                put_big32(pair, (p0 & 0xffff0000u) | (p1 >> 16));
                put_big32(pair + 4, (p2 & 0xffff0000u) | (p3 >> 16));
                put_big32(pair + 32, (p0 << 16) | (p1 & 0xffffu));
                put_big32(pair + 36, (p2 << 16) | (p3 & 0xffffu));
            }
            out += 64;
        }
    }
}

static void pack(const VertrixSurface *frame, const unsigned slots[4], VertrixTexture *texture)
{
    if (frame->width == texture->storage_width && frame->height == texture->storage_height)
    {
        if (slots[0] == 2 && slots[1] == 1 && slots[2] == 0 && slots[3] == 3)
        {
            pack_whole_bgrx(frame, texture);
        }
        else
        {
            pack_whole(frame, slots, texture);
        }
        return;
    }
    memset(texture->data, 0, texture->size);
    size_t tile = 0;
    for (uint32_t y = 0; y < texture->storage_height; y += 4)
    {
        for (uint32_t x = 0; x < texture->storage_width; x += 4)
        {
            for (uint32_t row = 0; row < 4; ++row)
            {
                for (uint32_t column = 0; column < 4; ++column)
                {
                    if (y + row >= frame->height || x + column >= frame->width)
                    {
                        continue;
                    }
                    const uint8_t *pixel =
                        frame->data + (size_t)(y + row) * frame->stride + (size_t)(x + column) * 4;
                    size_t pair = tile + (row * 4 + column) * 2;
                    texture->data[pair] = pixel[slots[3]];
                    texture->data[pair + 1] = pixel[slots[0]];
                    texture->data[pair + 32] = pixel[slots[1]];
                    texture->data[pair + 33] = pixel[slots[2]];
                }
            }
            tile += 64;
        }
    }
}

int vertrix_frame_texture_init(const VertrixSurface *frame, const uint32_t masks[3],
                               VertrixTexture *output)
{
    unsigned slots[4];
    if (!source_layout(frame, masks, slots) || !output || output->data || output->allocation)
    {
        return 0;
    }
    uint32_t width = (frame->width + 3) & ~3u;
    uint32_t height = (frame->height + 3) & ~3u;
    size_t size = (size_t)width * height * 4;
    void *allocation = malloc(size + 31);
    if (!allocation)
    {
        return 0;
    }
    uint8_t *data = (uint8_t *)(((uintptr_t)allocation + 31) & ~(uintptr_t)31);
    VertrixTexture texture = {frame->width, frame->height, width, height, size, data, allocation};
    pack(frame, slots, &texture);
    *output = texture;
    return 1;
}

int vertrix_frame_texture_update(const VertrixSurface *frame, const uint32_t masks[3],
                                 VertrixTexture *texture)
{
    unsigned slots[4];
    if (!vertrix_frame_texture_validate(frame, masks, texture) ||
        !source_layout(frame, masks, slots))
    {
        return 0;
    }
    pack(frame, slots, texture);
    return 1;
}
