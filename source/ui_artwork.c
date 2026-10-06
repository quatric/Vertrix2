#include "ui_artwork.h"
#include "font_image.h"
#include "font_stencils.h"
#include <string.h>

void vertrix_ui_artwork_free(VertrixUiArtwork *artwork)
{
    if (!artwork)
    {
        return;
    }
    for (size_t i = 0; i < 2; i++)
    {
        vertrix_image_free(&artwork->images[i]);
    }
    memset(artwork, 0, sizeof(*artwork));
}

int vertrix_ui_artwork_build(const VertrixUiSpriteBank *bank, const VertrixUiSpriteBank *stencils,
                             uint32_t source_index, VertrixUiArtwork *output)
{
    if (!bank || !bank->frames || source_index >= bank->count || !stencils || !stencils->frames ||
        stencils->count <= 9 || !output || output->ready || output->images[0].rgba ||
        output->images[1].rgba || output->images[0].width || output->images[0].height ||
        output->images[1].width || output->images[1].height)
    {
        return 0;
    }
    const VertrixSpriteFrame *source = &bank->frames[source_index];
    const VertrixImage *stencil = &stencils->frames[9].image;
    VertrixUiArtwork loaded = {0};
    for (size_t i = 0; i < 2; ++i)
    {
        if (!vertrix_font_image_stencil(&source->image, stencil, i == 0, &loaded.images[i]))
        {
            vertrix_ui_artwork_free(&loaded);
            return 0;
        }
        loaded.origin_x[i] = source->metadata[3] + (stencil->width >> 1);
        loaded.origin_y[i] = source->metadata[4] + (stencil->height >> 1);
    }
    loaded.ready = 1;
    *output = loaded;
    return 1;
}

int vertrix_ui_artwork_load(VertrixVf *archive, const char *name, const uint32_t masks[3],
                            size_t first_source, uint32_t source_index, VertrixUiArtwork *output)
{
    if (!output || output->ready || output->images[0].rgba || output->images[1].rgba ||
        output->images[0].width || output->images[0].height || output->images[1].width ||
        output->images[1].height)
    {
        return 0;
    }
    VertrixUiSpriteBank bank = {0};
    VertrixFontStencils stencils = {0};
    VertrixUiArtwork loaded = {0};
    int success = 0;
    if (!vertrix_ui_sprite_bank_load(archive, name, masks, first_source, &bank) ||
        !vertrix_font_stencils_load(archive, masks, &stencils))
    {
        goto done;
    }
    if (source_index >= bank.count)
    {
        goto done;
    }
    for (size_t i = 0; i < 2; i++)
    {
        const VertrixSpriteFrame *source = &bank.frames[source_index];
        if (!vertrix_font_image_stencil(&source->image, &stencils.frame9.image, i == 0,
                                        &loaded.images[i]))
        {
            goto done;
        }
        loaded.origin_x[i] = source->metadata[3] + (stencils.frame9.image.width >> 1);
        loaded.origin_y[i] = source->metadata[4] + (stencils.frame9.image.height >> 1);
    }
    loaded.ready = 1;
    *output = loaded;
    memset(&loaded, 0, sizeof(loaded));
    success = 1;
done:
    vertrix_ui_artwork_free(&loaded);
    vertrix_font_stencils_free(&stencils);
    vertrix_ui_sprite_bank_free(&bank);
    return success;
}
