#ifndef VERTRIX_ACTOR_IMAGE_BOUNDS_H
#define VERTRIX_ACTOR_IMAGE_BOUNDS_H
#include "actor_storage.h"
#include "image.h"
typedef struct
{
    int32_t x, y, width, height;
} VertrixActorImageBounds;
/* Original4b15e0 descriptor geometry. Pixels/origins come from the resolved
 * VF image; mode44/override91 and positionE/16 come from actor storage.
 * Screen override inputs correspond to screen220/221. Invalid inputs preserve
 * output. Effect application, clipping and rasterization remain separate. */
int vertrix_actor_image_bounds(const void *storage, size_t size, const VertrixImage *image,
                               uint32_t origin_x, uint32_t origin_y, uint8_t screen_unscaled,
                               uint8_t screen_mode, VertrixActorImageBounds *output);
#endif
