#include "wii_texture.h"

#include <string.h>

int vertrix_wii_texture_init(const VertrixImage *image, uint8_t filter, VertrixWiiTexture *output)
{
    if (!output || output->ready || output->pixels.data || output->pixels.allocation ||
        (filter != GX_NEAR && filter != GX_LINEAR))
    {
        return 0;
    }
    VertrixWiiTexture loaded = {0};
    if (!vertrix_texture_rgba8(image, &loaded.pixels))
    {
        return 0;
    }
    DCFlushRange(loaded.pixels.data, (uint32_t)loaded.pixels.size);
    GX_InvalidateTexAll();
    GX_InitTexObj(&loaded.object, loaded.pixels.data, (uint16_t)loaded.pixels.storage_width,
                  (uint16_t)loaded.pixels.storage_height, GX_TF_RGBA8, GX_CLAMP, GX_CLAMP,
                  GX_FALSE);
    GX_InitTexObjFilterMode(&loaded.object, filter, filter);
    loaded.u_limit = (float)loaded.pixels.width / loaded.pixels.storage_width;
    loaded.v_limit = (float)loaded.pixels.height / loaded.pixels.storage_height;
    loaded.ready = 1;
    *output = loaded;
    return 1;
}

int vertrix_wii_texture_bind(VertrixWiiTexture *texture, uint32_t map)
{
    if (!texture || !texture->ready || map > GX_TEXMAP7)
    {
        return 0;
    }
    GX_LoadTexObj(&texture->object, map);
    return 1;
}

void vertrix_wii_texture_free(VertrixWiiTexture *texture)
{
    if (!texture)
    {
        return;
    }
    if (texture->ready)
    {
        GX_DrawDone();
        GX_InvalidateTexAll();
    }
    vertrix_texture_free(&texture->pixels);
    memset(texture, 0, sizeof(*texture));
}
