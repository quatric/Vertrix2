#include "font_outline.h"

int vertrix_font_outline(uint32_t *source, uint32_t *outline, size_t capacity, uint32_t width,
                         uint32_t height, uint32_t passes, uint32_t diagonal)
{
    if (!source || !outline || source == outline || !width || !height ||
        width > SIZE_MAX / height || (size_t)width * height > capacity)
    {
        return 0;
    }
    size_t count = (size_t)width * height;
    for (size_t i = 0; i < count; i++)
    {
        outline[i] = source[i] & UINT32_C(0x00ffffff);
    }
    for (uint32_t pass = 0; pass < passes; pass++)
    {
        for (uint32_t y = 0; y < height; y++)
        {
            for (uint32_t x = 0; x < width; x++)
            {
                size_t i = (size_t)y * width + x;
                if (!(source[i] >> 24))
                {
                    continue;
                }
                int edge = !x || !y || x == width - 1 || y == height - 1;
                if (!edge)
                {
                    edge = !(source[i - width] >> 24) || !(source[i + width] >> 24) ||
                           !(source[i - 1] >> 24) || !(source[i + 1] >> 24);
                    if (!edge && diagonal == 1)
                    {
                        edge = !(source[i - width - 1] >> 24) || !(source[i - width + 1] >> 24) ||
                               !(source[i + width - 1] >> 24) || !(source[i + width + 1] >> 24);
                    }
                }
                if (edge)
                {
                    outline[i] |= UINT32_C(0xff000000);
                }
            }
        }
        for (size_t i = 0; i < count; i++)
        {
            if (outline[i] >> 24)
            {
                source[i] &= UINT32_C(0x00ffffff);
            }
        }
    }
    return 1;
}
