#include "color_conversion.h"

enum
{
    CUBE_RED_STEP = 8,
    CUBE_GREEN_STEP = 8,
    CUBE_BLUE_STEP = 16,
    CUBE_RED_STRIDE = 32,
    CUBE_GREEN_STRIDE = 4,
    CUBE_LEVELS_RED = 8,
    CUBE_LEVELS_GREEN = 8,
    CUBE_LEVELS_BLUE = 4,
    ENTRY_FLAGS = 2,
    SHIFT_MASK = 31
};

void vertrix_palette_expand_vga(const uint8_t rgb[3 * VERTRIX_PALETTE_SIZE],
                                uint8_t entries[4 * VERTRIX_PALETTE_SIZE])
{
    for (int i = 0; i < VERTRIX_PALETTE_SIZE; i++)
    {
        entries[4 * i] = (uint8_t)(rgb[3 * i] << 2);
        entries[4 * i + 1] = (uint8_t)(rgb[3 * i + 1] << 2);
        entries[4 * i + 2] = (uint8_t)(rgb[3 * i + 2] << 2);
        entries[4 * i + 3] = ENTRY_FLAGS;
    }
}

void vertrix_palette_cube(uint8_t rgb[3 * VERTRIX_PALETTE_SIZE])
{
    for (int a = 0; a < CUBE_LEVELS_RED; a++)
    {
        for (int b = 0; b < CUBE_LEVELS_GREEN; b++)
        {
            for (int c = 0; c < CUBE_LEVELS_BLUE; c++)
            {
                int index = a * CUBE_RED_STRIDE + b * CUBE_GREEN_STRIDE + c;
                rgb[3 * index] = (uint8_t)(a * CUBE_RED_STEP);
                rgb[3 * index + 1] = (uint8_t)(b * CUBE_GREEN_STEP);
                rgb[3 * index + 2] = (uint8_t)(c * CUBE_BLUE_STEP);
            }
        }
    }
}

static uint32_t convert_channel(const VertrixPixelFormat *source,
                                const VertrixPixelFormat *destination, int channel, uint32_t pixel)
{
    uint32_t value = (pixel & source->mask[channel]) >> (source->shift[channel] & SHIFT_MASK);
    value <<= source->scale[channel] & SHIFT_MASK;
    value >>= destination->scale[channel] & SHIFT_MASK;
    return value << (destination->shift[channel] & SHIFT_MASK);
}

uint32_t vertrix_pixel_convert(const VertrixPixelFormat *source,
                               const VertrixPixelFormat *destination, uint32_t pixel)
{
    uint32_t result = 0;
    for (int channel = 0; channel < 4; channel++)
    {
        result |= convert_channel(source, destination, channel, pixel);
    }
    return result;
}
