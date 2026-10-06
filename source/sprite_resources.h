#ifndef VERTRIX_SPRITE_RESOURCES_H
#define VERTRIX_SPRITE_RESOURCES_H
#include "sprite_load_set.h"
#include "ui_artwork_render.h"
#include "ui_border_artwork.h"

typedef struct
{
    VertrixSpriteLoadSet sprites;
    VertrixUiArtwork artwork;
    VertrixUiArtworkRenderView view;
    VertrixSpriteFrame border;
    VertrixUiSpriteBank border_bank;
    VertrixSpriteBankBinding bindings[VERTRIX_SPRITE_LOAD_COUNT + 3];
    VertrixSpriteBankMap map;
    unsigned ready;
} VertrixSpriteResources;

/* Compose recovered20 direct loads and45e490/45e530-generated images. Selection,
 * masks and descriptor format are explicit. Own pixels after VF closure;
 * publish one23-bank map and the generated animation resources. Zero output,
 * preserve on failure, and keep at a stable address while borrowed. Other
 * original startup builders, actor creation and scene registration are separate. */
int vertrix_sprite_resources_load(VertrixVf *archive, const VertrixSpriteSelection *selection,
                                  const uint32_t masks[3], uint32_t descriptor_format,
                                  VertrixSpriteResources *output);
void vertrix_sprite_resources_free(VertrixSpriteResources *resources);
#endif
