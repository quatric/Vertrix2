#include "texture.h"

#include <stdlib.h>
#include <string.h>

int vertrix_texture_rgba8(const VertrixImage *image, VertrixTexture *output)
{
    if (!image || !image->rgba || !output || output->data || output->allocation || !image->width ||
        !image->height || image->width > 1024 || image->height > 1024)
    {
        return 0;
    }
    uint32_t width = (image->width + 3) & ~3u;
    uint32_t height = (image->height + 3) & ~3u;
    size_t size = (size_t)width * height * 4;
    void *allocation = malloc(size + 31);
    if (!allocation)
    {
        return 0;
    }
    unsigned char *data = (unsigned char *)(((uintptr_t)allocation + 31) & ~(uintptr_t)31);
    memset(data, 0, size);
    size_t tile = 0;
    for (uint32_t y = 0; y < height; y += 4)
    {
        for (uint32_t x = 0; x < width; x += 4)
        {
            for (uint32_t row = 0; row < 4; ++row)
            {
                for (uint32_t column = 0; column < 4; ++column)
                {
                    if (x + column >= image->width || y + row >= image->height)
                    {
                        continue;
                    }
                    const unsigned char *pixel =
                        image->rgba + ((size_t)(y + row) * image->width + x + column) * 4;
                    size_t pair = tile + (row * 4 + column) * 2;
                    data[pair] = pixel[3];
                    data[pair + 1] = pixel[0];
                    data[pair + 32] = pixel[1];
                    data[pair + 33] = pixel[2];
                }
            }
            tile += 64;
        }
    }
    *output = (VertrixTexture){image->width, image->height, width, height, size, data, allocation};
    return 1;
}

void vertrix_texture_free(VertrixTexture *texture)
{
    if (texture)
    {
        free(texture->allocation);
        memset(texture, 0, sizeof(*texture));
    }
}
