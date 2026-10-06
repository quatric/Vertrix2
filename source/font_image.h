#ifndef VERTRIX_FONT_IMAGE_H
#define VERTRIX_FONT_IMAGE_H
#include "image.h"
/* Owned image adapters for original4831b0 and483400. Output must be empty.
 * Stencil dimensions add twice floor(stencil dimensions/2). Outline removes
 * extracted edges from source, publishing source mutation only on success.
 * Pixel words are translated explicitly, independently of CPU byte order. */
int vertrix_font_image_stencil(const VertrixImage *source, const VertrixImage *stencil,
                               uint32_t solid, VertrixImage *output);
int vertrix_font_image_outline(VertrixImage *source, uint32_t passes, uint32_t diagonal,
                               VertrixImage *output);
#endif
