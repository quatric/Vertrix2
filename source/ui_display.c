#include "ui_display.h"
#include <string.h>

int vertrix_ui_display_assets_load(VertrixVf *archive, const char *name, const uint32_t masks[3],
                                   size_t first_source, uint32_t source_index,
                                   VertrixUiDisplayAssets *assets)
{
    if (!assets || !vertrix_ui_artwork_load(archive, name, masks, first_source, source_index,
                                            &assets->artwork))
    {
        return 0;
    }
    for (size_t i = 0; i < 2; i++)
    {
        assets->descriptors[i] = (uint32_t)i;
        assets->resources[i] = (VertrixFrameResource){0, 1, &assets->descriptors[i], NULL, NULL};
    }
    return 1;
}

void vertrix_ui_display_assets_free(VertrixUiDisplayAssets *assets)
{
    if (!assets)
    {
        return;
    }
    vertrix_ui_artwork_free(&assets->artwork);
    memset(assets, 0, sizeof(*assets));
}

int vertrix_ui_display_initialize_animation(VertrixLinkedAlternating *display, size_t pair,
                                            const VertrixUiDisplayAssets *assets)
{
    if (!display || !assets || !assets->artwork.ready || pair >= 12)
    {
        return 0;
    }
    VertrixLinkedAlternating next = *display;
    if (!vertrix_block_resource_attach(&next.animation, &next.resource, &assets->resources[0]) ||
        !vertrix_block_resource_bind(&next.animation, next.resource, 1, &next.descriptor))
    {
        return 0;
    }
    next.primary.period = 10;
    next.secondary.period = 441 - (uint32_t)pair * 40;
    next.threshold = (uint32_t)pair + 1;
    next.handler = 0x450a10;
    next.phase = 0;
    next.source = 0;
    *display = next;
    return 1;
}

int vertrix_ui_display_update(VertrixLinkedAlternating *display, int linked_present,
                              uint32_t linked_value, uint32_t linked_state, int16_t start_y,
                              uint32_t elapsed, const VertrixUiDisplayAssets *assets)
{
    if (!assets || !assets->artwork.ready)
    {
        return 0;
    }
    return vertrix_linked_alternating_update(display, linked_present, linked_value, linked_state,
                                             start_y, elapsed, &assets->resources[0],
                                             &assets->resources[1], 1);
}

int vertrix_ui_display_image(const VertrixLinkedAlternating *display,
                             const VertrixUiDisplayAssets *assets, const VertrixImage **image,
                             uint32_t *origin_x, uint32_t *origin_y)
{
    if (!display || !assets || !assets->artwork.ready || !image || !origin_x || !origin_y)
    {
        return 0;
    }
    for (size_t i = 0; i < 2; i++)
    {
        if (display->resource == &assets->resources[i] &&
            display->descriptor == assets->descriptors[i])
        {
            *image = &assets->artwork.images[i];
            *origin_x = assets->artwork.origin_x[i];
            *origin_y = assets->artwork.origin_y[i];
            return 1;
        }
    }
    return 0;
}
