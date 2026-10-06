#ifndef VERTRIX_FRAME_TEXTURE_H
#define VERTRIX_FRAME_TEXTURE_H
#include "surface.h"
#include "texture.h"
/* Pack a bounded four-byte CPU frame into Wii4x4 AR/GB tiles. RGB masks must
 * each select a distinct complete byte of the little-endian pixel; the remaining
 * byte is alpha. Masks are explicit so recovered destination ordering is not
 * guessed. Source and texture backing must be independent. Dimensions1..1024.
 * Init owns aligned storage; update reuses it. Invalid input preserves output.
 * Validation performs no writes and is available before GPU synchronization. */
int vertrix_frame_texture_validate(const VertrixSurface *frame, const uint32_t masks[3],
                                   const VertrixTexture *texture);
int vertrix_frame_texture_init(const VertrixSurface *frame, const uint32_t masks[3],
                               VertrixTexture *output);
int vertrix_frame_texture_update(const VertrixSurface *frame, const uint32_t masks[3],
                                 VertrixTexture *texture);
#endif
