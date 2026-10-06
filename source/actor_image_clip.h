#ifndef VERTRIX_ACTOR_IMAGE_CLIP_H
#define VERTRIX_ACTOR_IMAGE_CLIP_H
#include "actor_image_bounds.h"
#include "render_geometry.h"
/* Original4b1a99 clipping with actor8e and inclusive boundsA8..AE. Inputs are
 * measured image bounds and target dimensions. Returns1 visible,0 clipped,
 * -1 invalid actor/input; unsuccessful calls preserve output. Source offset is
 * the unscaled traversal offset; scaled drawing must apply scale-table advances
 * separately. This computes clipping and does not draw or apply effects. */
int vertrix_actor_image_clip(const void *storage, size_t size,
                             const VertrixActorImageBounds *bounds, uint16_t target_width,
                             uint16_t target_height, VertrixBoardClip cached_clip,
                             VertrixSpriteClip *output);
/* Convert the visible rectangle's skipped rows/columns to a source-pixel
 * offset using original4ae99f..4aea50. Mode16 retains unscaled clipping;
 * modes1..15 use the original advance tables. Invalid inputs preserve output.
 * The bounds and clip must describe the same resolved image. */
int vertrix_actor_image_clip_offset(const VertrixActorImageBounds *bounds,
                                    const VertrixSpriteClip *clip, uint16_t source_width,
                                    uint8_t scale, uint32_t *output);
#endif
