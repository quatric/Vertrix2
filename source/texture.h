#ifndef VERTRIX_TEXTURE_H
#define VERTRIX_TEXTURE_H

#include "image.h"
#include <stddef.h>

typedef struct
{
    uint32_t width;
    uint32_t height;
    uint32_t storage_width;
    uint32_t storage_height;
    size_t size;
    unsigned char *data;
    void *allocation;
} VertrixTexture;

/* Wii GX_TF_RGBA8: 4x4 tiles, AR plane followed by GB plane, 32-byte aligned.
 * Copies every source channel unchanged; padded edge pixels are transparent.
 * Initialize output to zero. Cache flush and GX object setup are separate. */
int vertrix_texture_rgba8(const VertrixImage *image, VertrixTexture *output);
void vertrix_texture_free(VertrixTexture *texture);

#endif
