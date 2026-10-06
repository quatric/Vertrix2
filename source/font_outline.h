#ifndef VERTRIX_FONT_OUTLINE_H
#define VERTRIX_FONT_OUTLINE_H
#include <stddef.h>
#include <stdint.h>
/* Original0x483400 with EBX=1: removes successive alpha edges from source,
 * producing an outline with original RGB and alpha255 at removed pixels.
 * Buffers must be distinct, with width*height words available in each. */
int vertrix_font_outline(uint32_t *source, uint32_t *outline, size_t capacity, uint32_t width,
                         uint32_t height, uint32_t passes, uint32_t diagonal);
#endif
