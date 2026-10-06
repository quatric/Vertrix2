#include "ui_artwork_render.h"
#include "ui_actor_storage.h"
#include <string.h>

int vertrix_ui_artwork_actor_construct(void *storage, size_t size, size_t pair, unsigned side,
                                       int16_t offset_x, int16_t offset_y,
                                       const VertrixUiArtworkRenderView *view)
{
    if (!view || !view->ready)
    {
        return 0;
    }
    return vertrix_ui_actor_storage_construct(storage, size, pair, side, offset_x, offset_y,
                                              view->descriptors[0]);
}

int vertrix_ui_artwork_render_view(const VertrixUiArtwork *artwork, uint32_t descriptor_format,
                                   VertrixUiArtworkRenderView *output)
{
    if (!artwork || !artwork->ready || !output || output->ready || output->map.bindings ||
        output->frames[0].image.rgba || output->frames[1].image.rgba ||
        (descriptor_format >> 24) != 4)
    {
        return 0;
    }
    for (size_t i = 0; i < 2; ++i)
    {
        if (!artwork->images[i].rgba || !artwork->images[i].width || !artwork->images[i].height ||
            artwork->images[i].width > 65535 || artwork->images[i].height > 65535)
        {
            return 0;
        }
    }
    memset(output, 0, sizeof(*output));
    for (size_t i = 0; i < 2; ++i)
    {
        output->frames[i].image = artwork->images[i];
        output->frames[i].frame_count = 1;
        output->frames[i].metadata[1] = artwork->images[i].width;
        output->frames[i].metadata[2] = artwork->images[i].height;
        output->frames[i].metadata[3] = artwork->origin_x[i];
        output->frames[i].metadata[4] = artwork->origin_y[i];
        output->frames[i].metadata[9] = descriptor_format;
        output->banks[i] = (VertrixUiSpriteBank){&output->frames[i], 1};
        output->bindings[i] =
            (VertrixSpriteBankBinding){i == 0 ? 0x546618 : 0x546634, &output->banks[i]};
        output->resources[i] = (VertrixFrameResource){0, 1, &output->descriptors[i], NULL, NULL};
    }
    output->map = (VertrixSpriteBankMap){output->bindings, 2};
    output->ready = 1;
    return 1;
}
