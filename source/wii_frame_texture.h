#ifndef VERTRIX_WII_FRAME_TEXTURE_H
#define VERTRIX_WII_FRAME_TEXTURE_H
#include "frame_texture.h"
#include "wii_texture.h"
/* Initialized GX required. Upload recovered CPU frames with explicit channel
 * masks. Initialize zero output; update retains the object/allocation and waits
 * for prior GPU draws before overwriting pixels, then flushes/invalidate caches.
 * Bind/free through the existing Wii texture API. Invalid input changes nothing.
 * Caller supplies final geometry/projection and video presentation. */
int vertrix_wii_frame_texture_init(const VertrixSurface *frame, const uint32_t masks[3],
                                   uint8_t filter, VertrixWiiTexture *output);
int vertrix_wii_frame_texture_update(const VertrixSurface *frame, const uint32_t masks[3],
                                     VertrixWiiTexture *texture);
#endif
