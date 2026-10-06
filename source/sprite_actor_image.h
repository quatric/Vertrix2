#ifndef VERTRIX_SPRITE_ACTOR_IMAGE_H
#define VERTRIX_SPRITE_ACTOR_IMAGE_H
#include "actor_storage.h"
#include "ui_sprite_bank.h"
/* Original4ac8a0/4877f0 descriptor binding for direct5449fc bank. Bind selected
 * actor frame to its local descriptor ID and borrow configured VF pixels/origins.
 * Invalid resource/frame/storage preserves actor and outputs. Keep bank live.
 * This supplies image data; drawing/effect application remains external. */
int vertrix_sprite_actor_image(void *storage, size_t size, const VertrixUiSpriteBank *bank,
                               const VertrixImage **image, uint32_t *origin_x, uint32_t *origin_y);
/* Same original4ac8a0 direct-bank binding for an explicitly resolved nonzero
 * resource identity. The caller maps the original resource token to its live
 * decoded/configured bank; this function never guesses an asset name. */
int vertrix_sprite_actor_image_resource(void *storage, size_t size, uint32_t resource_token,
                                        const VertrixUiSpriteBank *bank, const VertrixImage **image,
                                        uint32_t *origin_x, uint32_t *origin_y);
#endif
