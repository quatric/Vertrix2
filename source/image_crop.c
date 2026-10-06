#include "image.h"
#include <stdlib.h>
#include <string.h>

int vertrix_image_font_crop(const VertrixImage *sheet, uint32_t x, uint32_t y, uint32_t width,
                            uint32_t height, VertrixImage *output)
{
    if (!sheet || !sheet->rgba || !output || output->rgba || output->width || output->height ||
        !width || !height || width >= sheet->width || x > sheet->width - width ||
        height > sheet->height || y > sheet->height - height ||
        sheet->width > SIZE_MAX / sheet->height ||
        (size_t)sheet->width * sheet->height > SIZE_MAX / 4)
    {
        return 0;
    }
    size_t row_bytes = (size_t)width * 4;
    unsigned char *pixels = malloc(row_bytes * height);
    if (!pixels)
    {
        return 0;
    }
    for (uint32_t row = 0; row < height; row++)
    {
        memcpy(pixels + (size_t)row * row_bytes,
               sheet->rgba + ((size_t)(y + row) * sheet->width + x) * 4, row_bytes);
    }
    output->rgba = pixels;
    output->width = width;
    output->height = height;
    return 1;
}
