#include "wii_assets.h"
#include <stdlib.h>
#include <string.h>

void vertrix_wii_block_set_free(VertrixWiiBlockSet *set)
{
    if (!set)
    {
        return;
    }
    for (unsigned color = 0; color < 7; ++color)
    {
        for (unsigned frame = 0; frame < 8; ++frame)
        {
            vertrix_wii_texture_free(&set->frames[color][frame]);
        }
    }
    memset(set, 0, sizeof(*set));
}

int vertrix_wii_block_set_load(VertrixVf *archive, uint32_t character, uint8_t filter,
                               VertrixWiiBlockSet *output)
{
    if (!archive || !output || output->ready || (filter != GX_NEAR && filter != GX_LINEAR))
    {
        return 0;
    }
    for (unsigned color = 0; color < 7; ++color)
    {
        for (unsigned frame = 0; frame < 8; ++frame)
        {
            const VertrixWiiTexture *texture = &output->frames[color][frame];
            if (texture->ready || texture->pixels.data || texture->pixels.allocation)
            {
                return 0;
            }
        }
    }
    VertrixBlockSet decoded = {0};
    const uint32_t masks[3] = {0xff0000, 0xff00, 0xff};
    if (!vertrix_asset_block_set(archive, character, masks, &decoded))
    {
        return 0;
    }
    VertrixWiiBlockSet *loaded = calloc(1, sizeof(*loaded));
    if (!loaded)
    {
        vertrix_block_set_free(&decoded);
        return 0;
    }
    for (unsigned color = 0; color < 7; ++color)
    {
        for (unsigned frame = 0; frame < 8; ++frame)
        {
            if (!vertrix_wii_texture_init(&decoded.frames[color][frame], filter,
                                          &loaded->frames[color][frame]))
            {
                vertrix_wii_block_set_free(loaded);
                free(loaded);
                vertrix_block_set_free(&decoded);
                return 0;
            }
        }
    }
    memcpy(loaded->delays, decoded.delays, sizeof(loaded->delays));
    loaded->ready = 1;
    vertrix_block_set_free(&decoded);
    *output = *loaded;
    free(loaded);
    return 1;
}

int vertrix_wii_sprite_frame_load(VertrixVf *archive, const char *name, uint32_t frame,
                                  uint8_t filter, VertrixWiiSpriteFrame *output)
{
    if (!archive || !name || !output || output->texture.ready || output->texture.pixels.data ||
        output->texture.pixels.allocation || output->frame_count ||
        (filter != GX_NEAR && filter != GX_LINEAR))
    {
        return 0;
    }
    const uint32_t masks[3] = {0xff0000, 0xff00, 0xff};
    VertrixSpriteFrame decoded = {0};
    if (!vertrix_image_sprite_processed(archive, name, frame, masks, &decoded))
    {
        return 0;
    }
    VertrixWiiSpriteFrame loaded = {0};
    if (!vertrix_wii_texture_init(&decoded.image, filter, &loaded.texture))
    {
        vertrix_sprite_free(&decoded);
        return 0;
    }
    loaded.frame_count = decoded.frame_count;
    memcpy(loaded.metadata, decoded.metadata, sizeof(loaded.metadata));
    vertrix_sprite_free(&decoded);
    *output = loaded;
    return 1;
}

void vertrix_wii_sprite_frame_free(VertrixWiiSpriteFrame *frame)
{
    if (!frame)
    {
        return;
    }
    vertrix_wii_texture_free(&frame->texture);
    memset(frame, 0, sizeof(*frame));
}
