#include "font_image.h"
#include "font_outline.h"
#include "font_stencil.h"
#include <stdlib.h>

static uint32_t *image_words(const VertrixImage *image, size_t *count)
{
    if (!image || !image->rgba || !image->width || !image->height ||
        image->width > SIZE_MAX / image->height ||
        (size_t)image->width * image->height > SIZE_MAX / sizeof(uint32_t))
    {
        return NULL;
    }
    *count = (size_t)image->width * image->height;
    uint32_t *words = malloc(*count * sizeof(*words));
    if (!words)
    {
        return NULL;
    }
    for (size_t i = 0; i < *count; i++)
    {
        const unsigned char *p = image->rgba + i * 4;
        words[i] = (uint32_t)p[0] | ((uint32_t)p[1] << 8) | ((uint32_t)p[2] << 16) |
                   ((uint32_t)p[3] << 24);
    }
    return words;
}

static void image_bytes(const uint32_t *words, size_t count, unsigned char *pixels)
{
    for (size_t i = 0; i < count; i++)
    {
        for (unsigned channel = 0; channel < 4; channel++)
        {
            pixels[i * 4 + channel] = (unsigned char)(words[i] >> (channel * 8));
        }
    }
}

int vertrix_font_image_stencil(const VertrixImage *source, const VertrixImage *stencil,
                               uint32_t solid, VertrixImage *output)
{
    if (!source || !stencil || !output || output->rgba || output->width || output->height)
    {
        return 0;
    }
    uint32_t extra_x = (stencil->width >> 1) * 2;
    uint32_t extra_y = (stencil->height >> 1) * 2;
    if (!source->width || !source->height || source->width > UINT32_MAX - extra_x ||
        source->height > UINT32_MAX - extra_y)
    {
        return 0;
    }
    uint32_t width = source->width + extra_x;
    uint32_t height = source->height + extra_y;
    if (width > SIZE_MAX / height || (size_t)width * height > SIZE_MAX / sizeof(uint32_t))
    {
        return 0;
    }
    size_t source_count, stencil_count;
    uint32_t *source_words = image_words(source, &source_count);
    uint32_t *stencil_words = image_words(stencil, &stencil_count);
    size_t count = (size_t)width * height;
    uint32_t *result = malloc(count * sizeof(*result));
    unsigned char *pixels = malloc(count * 4);
    int success = 0;
    if (source_words && stencil_words && result && pixels &&
        vertrix_font_stencil(source_words, source->width, source->height, stencil_words,
                             stencil->width, stencil->height, solid, result, count))
    {
        image_bytes(result, count, pixels);
        output->width = width;
        output->height = height;
        output->rgba = pixels;
        pixels = NULL;
        success = 1;
    }
    free(source_words);
    free(stencil_words);
    free(result);
    free(pixels);
    return success;
}

int vertrix_font_image_outline(VertrixImage *source, uint32_t passes, uint32_t diagonal,
                               VertrixImage *output)
{
    if (!output || output->rgba || output->width || output->height)
    {
        return 0;
    }
    size_t count;
    uint32_t *working = image_words(source, &count);
    if (!working)
    {
        return 0;
    }
    uint32_t *result = malloc(count * sizeof(*result));
    unsigned char *pixels = malloc(count * 4);
    int success = 0;
    if (result && pixels &&
        vertrix_font_outline(working, result, count, source->width, source->height, passes,
                             diagonal))
    {
        image_bytes(result, count, pixels);
        image_bytes(working, count, source->rgba);
        output->width = source->width;
        output->height = source->height;
        output->rgba = pixels;
        pixels = NULL;
        success = 1;
    }
    free(working);
    free(result);
    free(pixels);
    return success;
}
