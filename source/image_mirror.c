#include "image.h"

int vertrix_image_mirror_horizontal(VertrixImage *image)
{
    if (!image || !image->rgba || !image->width || !image->height || image->width > 32767 ||
        image->height > 32767 || (uint64_t)image->width * image->height > SIZE_MAX / 4)
    {
        return 0;
    }
    for (uint32_t y = 0; y < image->height; y++)
    {
        unsigned char *row = image->rgba + (size_t)y * image->width * 4;
        for (uint32_t x = 0; x < image->width / 2; x++)
        {
            size_t left = (size_t)x * 4;
            size_t right = (size_t)(image->width - 1 - x) * 4;
            for (size_t channel = 0; channel < 4; channel++)
            {
                unsigned char temporary = row[left + channel];
                row[left + channel] = row[right + channel];
                row[right + channel] = temporary;
            }
        }
    }
    return 1;
}
