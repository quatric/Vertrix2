#include "sprite_resources.h"
#include <string.h>

void vertrix_sprite_resources_free(VertrixSpriteResources *resources)
{
    if (!resources)
    {
        return;
    }
    /* view contains borrowed frames, never separately free their pixels. */
    vertrix_ui_artwork_free(&resources->artwork);
    vertrix_sprite_free(&resources->border);
    vertrix_sprite_load_set_free(&resources->sprites);
    memset(resources, 0, sizeof(*resources));
}

int vertrix_sprite_resources_load(VertrixVf *archive, const VertrixSpriteSelection *selection,
                                  const uint32_t masks[3], uint32_t descriptor_format,
                                  VertrixSpriteResources *output)
{
    if (!selection || !output || output->ready || output->sprites.ready || output->view.ready ||
        output->artwork.ready || output->artwork.images[0].rgba || output->artwork.images[1].rgba ||
        output->border.image.rgba || output->map.bindings || output->map.count ||
        (descriptor_format >> 24) != 4)
    {
        return 0;
    }
    for (size_t i = 0; i < VERTRIX_SPRITE_LOAD_COUNT; ++i)
    {
        if (output->sprites.banks[i].frames || output->sprites.banks[i].count)
        {
            return 0;
        }
    }
    VertrixSpriteResources loaded = {0};
    if (!vertrix_sprite_load_set(archive, selection->settings, selection->interface_slot, masks,
                                 selection->first_source, &loaded.sprites))
    {
        return 0;
    }
    const VertrixUiSpriteBank *interface = NULL;
    const VertrixUiSpriteBank *stencils = NULL;
    for (size_t i = 0; i < loaded.sprites.map.count; ++i)
    {
        const VertrixSpriteBankBinding *binding = &loaded.sprites.bindings[i];
        if (binding->resource_token == 0x5449fc)
        {
            interface = binding->sprites;
        }
        if (binding->resource_token == 0x546538)
        {
            stencils = binding->sprites;
        }
    }
    if (!vertrix_ui_artwork_build(interface, stencils, selection->artwork_source,
                                  &loaded.artwork) ||
        !vertrix_ui_artwork_render_view(&loaded.artwork, descriptor_format, &loaded.view) ||
        !vertrix_ui_border_artwork_build(interface, stencils, selection->border_source,
                                         descriptor_format, &loaded.border))
    {
        vertrix_sprite_resources_free(&loaded);
        return 0;
    }
    *output = loaded;
    /* Rebase every borrowed pointer after publishing owned allocations. */
    for (size_t i = 0; i < VERTRIX_SPRITE_LOAD_COUNT; ++i)
    {
        output->sprites.bindings[i].sprites = &output->sprites.banks[i];
        output->bindings[i] = output->sprites.bindings[i];
    }
    output->sprites.map.bindings = output->sprites.bindings;
    for (size_t i = 0; i < 2; ++i)
    {
        output->view.banks[i].frames = &output->view.frames[i];
        output->view.bindings[i].sprites = &output->view.banks[i];
        output->view.resources[i].frames = &output->view.descriptors[i];
        output->bindings[VERTRIX_SPRITE_LOAD_COUNT + i] = output->view.bindings[i];
    }
    output->view.map.bindings = output->view.bindings;
    output->border_bank = (VertrixUiSpriteBank){&output->border, 1};
    output->bindings[VERTRIX_SPRITE_LOAD_COUNT + 2] =
        (VertrixSpriteBankBinding){0x5466a4, &output->border_bank};
    output->map = (VertrixSpriteBankMap){output->bindings, VERTRIX_SPRITE_LOAD_COUNT + 3};
    output->ready = 1;
    return 1;
}
