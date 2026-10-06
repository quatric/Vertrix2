#include "font_stencil.h"
#include <string.h>

int vertrix_font_stencil(const uint32_t *source, uint32_t width, uint32_t height,
                         const uint32_t *stencil, uint32_t stencil_width, uint32_t stencil_height,
                         uint32_t solid, uint32_t *output, size_t capacity)
{
    uint32_t extra_x = (stencil_width >> 1) * 2;
    uint32_t extra_y = (stencil_height >> 1) * 2;
    if (!source || !stencil || !output || source == output || stencil == output || !width ||
        !height || !stencil_width || !stencil_height || width > UINT32_MAX - extra_x ||
        height > UINT32_MAX - extra_y)
    {
        return 0;
    }
    uint32_t output_width = width + extra_x;
    uint32_t output_height = height + extra_y;
    if (output_width > SIZE_MAX / output_height ||
        (size_t)output_width * output_height > SIZE_MAX / sizeof(uint32_t) ||
        (size_t)output_width * output_height > capacity)
    {
        return 0;
    }
    size_t count = (size_t)output_width * output_height;
    memset(output, 0, count * sizeof(*output));
    for (uint32_t y = 0; y < height; y++)
    {
        for (uint32_t x = 0; x < width; x++)
        {
            if (!(source[(size_t)y * width + x] >> 24))
            {
                continue;
            }
            for (uint32_t sy = 0; sy < stencil_height; sy++)
            {
                for (uint32_t sx = 0; sx < stencil_width; sx++)
                {
                    if (stencil[(size_t)sy * stencil_width + sx] >> 24)
                    {
                        output[(size_t)(y + sy) * output_width + x + sx]++;
                    }
                }
            }
        }
    }
    for (size_t i = 0; i < count; i++)
    {
        if (output[i])
        {
            uint32_t value = output[i] > 255 ? 255 : output[i];
            output[i] = UINT32_C(0xff000000) | value | (value << 8) | (value << 16);
        }
    }
    if (!solid)
    {
        for (uint32_t y = 0; y < height; y++)
        {
            for (uint32_t x = 0; x < width; x++)
            {
                if (source[(size_t)y * width + x] >> 24)
                {
                    output[(size_t)(y + (stencil_height >> 1)) * output_width + x +
                           (stencil_width >> 1)] &= UINT32_C(0x00ffffff);
                }
            }
        }
    }
    return 1;
}
