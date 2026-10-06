#include "wii_frame_texture.h"

int vertrix_wii_frame_texture_init(const VertrixSurface *frame, const uint32_t masks[3],
                                   uint8_t filter, VertrixWiiTexture *output)
{
    if (!output || output->ready || output->pixels.data || output->pixels.allocation ||
        (filter != GX_NEAR && filter != GX_LINEAR))
    {
        return 0;
    }
    VertrixWiiTexture texture = {0};
    if (!vertrix_frame_texture_init(frame, masks, &texture.pixels))
    {
        return 0;
    }
    DCFlushRange(texture.pixels.data, (uint32_t)texture.pixels.size);
    GX_InvalidateTexAll();
    GX_InitTexObj(&texture.object, texture.pixels.data, (uint16_t)texture.pixels.storage_width,
                  (uint16_t)texture.pixels.storage_height, GX_TF_RGBA8, GX_CLAMP, GX_CLAMP,
                  GX_FALSE);
    GX_InitTexObjFilterMode(&texture.object, filter, filter);
    texture.u_limit = (float)texture.pixels.width / texture.pixels.storage_width;
    texture.v_limit = (float)texture.pixels.height / texture.pixels.storage_height;
    texture.ready = 1;
    *output = texture;
    return 1;
}

int vertrix_wii_frame_texture_update(const VertrixSurface *frame, const uint32_t masks[3],
                                     VertrixWiiTexture *texture)
{
    if (!texture || !texture->ready ||
        !vertrix_frame_texture_validate(frame, masks, &texture->pixels))
    {
        return 0;
    }
    GX_DrawDone();
    if (!vertrix_frame_texture_update(frame, masks, &texture->pixels))
    {
        return 0;
    }
    DCFlushRange(texture->pixels.data, (uint32_t)texture->pixels.size);
    GX_InvalidateTexAll();
    return 1;
}
