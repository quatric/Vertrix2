#ifndef VERTRIX_ACTOR_RENDER_GEOMETRY_H
#define VERTRIX_ACTOR_RENDER_GEOMETRY_H
#include "actor_image_clip.h"
typedef struct
{
    VertrixActorImageBounds bounds;
    VertrixSpriteClip clip;
    uint32_t source_offset;
    uint8_t scale;
} VertrixActorRenderGeometry;
/* Direct-coordinate preparation corresponding to 0x4ae3e0 with EDX1.
 * Descriptor anchors and actor1e vertical displacement retain word wrapping.
 * Actor91 screen override is ignored in this direct mode. Returns1 visible,
 * 0 empty/clipped, -1 invalid input, preserving output on unsuccessful calls. */
int vertrix_actor_render_geometry(const void *storage, size_t size, const VertrixSpriteFrame *frame,
                                  uint16_t target_width, uint16_t target_height,
                                  VertrixBoardClip cached_clip, VertrixActorRenderGeometry *output);
#endif
