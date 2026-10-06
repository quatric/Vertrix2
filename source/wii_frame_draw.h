#ifndef VERTRIX_WII_FRAME_DRAW_H
#define VERTRIX_WII_FRAME_DRAW_H
#include "wii_frame_texture.h"
/* Draw the already composited CPU frame as an opaque textured quad. Caller
 * initializes GX, viewport and an orthographic projection in destination pixel
 * coordinates. This configures texture/vertex/TEV/depth/blend/alpha/cull state.
 * Source alpha never removes final-frame RGB. Texture padding is excluded by
 * its limits. Invalid inputs issue no GX commands. Does not copy/swap video
 * buffers or wait for vertical sync; those belong to the application loop. */
int vertrix_wii_frame_draw(VertrixWiiTexture *texture, int16_t x, int16_t y, uint16_t width,
                           uint16_t height);
#endif
