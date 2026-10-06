#include "image.h"

int vertrix_image_color_key(VertrixImage *image, uint32_t key)
{
    if (!image || !image->rgba || !image->width || !image->height ||
        image->width > SIZE_MAX / image->height ||
        (size_t)image->width * image->height > SIZE_MAX / 4)
    {
        return 0;
    }
    size_t count = (size_t)image->width * image->height;
    for (size_t i = 0; i < count; i++)
    {
        unsigned char *pixel = image->rgba + i * 4;
        uint32_t value = (uint32_t)pixel[0] | ((uint32_t)pixel[1] << 8) |
                         ((uint32_t)pixel[2] << 16) | ((uint32_t)pixel[3] << 24);
        pixel[3] = value == key ? 0 : 255;
    }
    return 1;
}

int vertrix_image_bmp_keyed(VertrixVf *archive, const char *name, VertrixImage *output)
{
    if (!output || output->rgba || output->width || output->height)
    {
        return 0;
    }
    VertrixImage loaded = {0};
    if (!vertrix_image_bmp(archive, name, &loaded))
    {
        return 0;
    }
    const unsigned char *pixel = loaded.rgba;
    uint32_t key = (uint32_t)pixel[0] | ((uint32_t)pixel[1] << 8) | ((uint32_t)pixel[2] << 16) |
                   ((uint32_t)pixel[3] << 24);
    if (!vertrix_image_color_key(&loaded, key))
    {
        vertrix_image_free(&loaded);
        return 0;
    }
    *output = loaded;
    return 1;
}
