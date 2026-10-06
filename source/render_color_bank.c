#include "render_color_bank.h"
#include "image.h"

static int order(uint32_t *values, uint32_t count, const uint32_t masks[3])
{
    uint8_t pixels[13 * 4];
    for (uint32_t i = 0; i < count; ++i)
    {
        pixels[i * 4] = (uint8_t)(values[i] >> 16);
        pixels[i * 4 + 1] = (uint8_t)(values[i] >> 8);
        pixels[i * 4 + 2] = (uint8_t)values[i];
        pixels[i * 4 + 3] = (uint8_t)(values[i] >> 24);
    }
    VertrixImage image = {0};
    image.width = count;
    image.height = 1;
    image.rgba = pixels;
    if (!vertrix_image_color_order(&image, masks))
    {
        return 0;
    }
    for (uint32_t i = 0; i < count; ++i)
    {
        values[i] = ((uint32_t)pixels[i * 4] << 16) | ((uint32_t)pixels[i * 4 + 1] << 8) |
                    pixels[i * 4 + 2] | ((uint32_t)pixels[i * 4 + 3] << 24);
    }
    return 1;
}

int vertrix_render_color_bank_build(const uint32_t masks[3], const uint8_t *row, size_t row_size,
                                    VertrixRenderColorBank *output)
{
    if (!masks || !row || row_size < 101 || !output)
    {
        return 0;
    }
    VertrixRenderColorBank bank = {
        {0, 0x646400, 0x326400, 0x6400, 0x32006400, 0x64006400, 0x64003200, 0x64000000, 0x64320000,
         0x64640000, 0x32640000, 0x640000, 0x643200},
        {0},
        {0, 0xff, 0xff00, 0xffff00, 0xff0000, 0xffff, 0xff00ff, 0xffffff, 0xff, 0xbf, 0x7f, 0x3f}};
    if (!order(bank.lookup, 13, masks) || !order(bank.format_colors, 12, masks))
    {
        return 0;
    }
    for (uint32_t i = 0; i < 13; ++i)
    {
        uint32_t value = bank.lookup[i];
        bank.colors[i] = ((uint32_t)row[(value >> 24) & 255u] << 16) |
                         ((uint32_t)row[(value >> 16) & 255u] << 8) | row[(value >> 8) & 255u];
    }
    *output = bank;
    return 1;
}
