#ifndef VERTRIX_WII_TEXTURE_H
#define VERTRIX_WII_TEXTURE_H

#include "texture.h"
#include <gccore.h>

typedef struct
{
    VertrixTexture pixels;
    GXTexObj object;
    float u_limit;
    float v_limit;
    unsigned ready;
} VertrixWiiTexture;

/* Requires an initialized GX context. Initialize output to zero.
 * filter is GX_NEAR or GX_LINEAR, explicitly selected by the renderer.
 * Output remains unchanged on failure. Pixel storage is owned by output. */
int vertrix_wii_texture_init(const VertrixImage *image, uint8_t filter, VertrixWiiTexture *output);
int vertrix_wii_texture_bind(VertrixWiiTexture *texture, uint32_t map);
/* Waits for pending GX draws before freeing a ready texture's pixel storage. */
void vertrix_wii_texture_free(VertrixWiiTexture *texture);

#endif
