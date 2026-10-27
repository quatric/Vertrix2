#ifndef VERTRIX_LAUNCHER_GFX_H
#define VERTRIX_LAUNCHER_GFX_H

#include <stdint.h>

/* The launcher draws into a 640x480 canvas of 0xRRGGBB pixels, which is converted to the TV's
 * YUV frame buffer once a frame (gfx_wii.c), or handed to the console shell (consoles/). */
enum
{
    GFX_WIDTH = 640,
    GFX_HEIGHT = 480
};

void gfx_init(void);
/* Show the canvas on the next field. */
void gfx_present(void);
/* Blank the screen (before another program starts). */
void gfx_black(void);
int gfx_widescreen(void);
/* The canvas, 0xAARRGGBB rows of GFX_WIDTH pixels (alpha unused). */
const uint32_t *gfx_canvas(void);
/* Debug builds: the canvas as a PPM file. */
int gfx_save_ppm(const char *path);
/* Keep the canvas as the background, and put it back at the start of each frame. */
void gfx_save_background(void);
void gfx_restore_background(void);

/* argb's alpha (top byte) blends over the canvas; 0xff is opaque. */
void gfx_fill(int x, int y, int w, int h, uint32_t argb);
void gfx_gradient(int x, int y, int w, int h, uint32_t top, uint32_t bottom);
void gfx_round_box(int x, int y, int w, int h, int radius, uint32_t argb);
void gfx_frame(int x, int y, int w, int h, int radius, uint32_t argb);
/* pixels are 0xAARRGGBB, drawn scaled to w x h with bilinear filtering. */
void gfx_image(const uint32_t *pixels, int pw, int ph, int x, int y, int w, int h);

/* Text in the launcher's font (font.h), 16 pixels at scale 1 and 32 at scale 2; bytes are Latin-1.
 * Returns the width drawn. */
int gfx_text(int x, int y, const char *text, int scale, uint32_t argb);
/* The same with a dark shadow below and to the right. */
int gfx_text_shadow(int x, int y, const char *text, int scale, uint32_t argb);
int gfx_text_width(const char *text, int scale);
/* Text cut to max_width with "..." when it does not fit. */
void gfx_text_fit(int x, int y, const char *text, int scale, int max_width, uint32_t argb);

#endif
