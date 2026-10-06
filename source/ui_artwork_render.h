#ifndef VERTRIX_UI_ARTWORK_RENDER_H
#define VERTRIX_UI_ARTWORK_RENDER_H
#include "frame_resource.h"
#include "sprite_actor_draw.h"
#include "ui_artwork.h"
typedef struct
{
    VertrixSpriteFrame frames[2];
    VertrixUiSpriteBank banks[2];
    VertrixSpriteBankBinding bindings[2];
    VertrixSpriteBankMap map;
    uint32_t descriptors[2];
    VertrixFrameResource resources[2];
    unsigned ready;
} VertrixUiArtworkRenderView;
/* Borrow the actual45e490-generated solid/hollow pixels for mapped rendering.
 * Metadata word9 comes from the caller's recovered image descriptor format.
 * Geometry retains original wrapping origins. Each one-frame resource uses
 * bank-local descriptor0, matching renderer binding. Keep artwork and this
 * view at stable addresses while actors/frame options borrow them. Zero-init
 * output; invalid/occupied output stays unchanged. No allocation or ownership
 * transfer; do not pass borrowed frames to sprite/bank free functions. */
int vertrix_ui_artwork_render_view(const VertrixUiArtwork *artwork, uint32_t descriptor_format,
                                   VertrixUiArtworkRenderView *output);
/* Original24 interface actor placements/setup, bound to the render view's
 * solid resource descriptor. Actor allocation and scene registration remain
 * caller-owned. Invalid view or actor parameters preserve storage. */
int vertrix_ui_artwork_actor_construct(void *storage, size_t size, size_t pair, unsigned side,
                                       int16_t offset_x, int16_t offset_y,
                                       const VertrixUiArtworkRenderView *view);
#endif
