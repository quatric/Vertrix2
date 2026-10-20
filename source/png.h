#ifndef VERTRIX_PNG_H
#define VERTRIX_PNG_H

#include <stddef.h>
#include <stdint.h>

#include "image.h"

/* Vertrix 3 texture artwork (.\TEXTURE\*.png): 8-bit truecolor (type 2) or truecolor with
 * alpha (type 6), not interlaced, as every PNG of the original vertrix3.vf is. Pixel rows are
 * top-down RGBA; alpha is 255 for truecolor. Ancillary chunks (gAMA, pHYs, tIME, tEXt) are
 * skipped and no gamma is applied. Output must be initialized to zero and empty; returns 0
 * without changing it on unsupported, corrupt or truncated input. */
int vertrix_png_decode(const unsigned char *data, size_t size, VertrixImage *image);
int vertrix_image_png(VertrixVf *archive, const char *name, VertrixImage *image);

/* zlib stream (RFC 1950/1951) into exactly output_size bytes; returns the bytes produced, or 0
 * on a corrupt stream, a bad Adler-32 or one that does not fill the output. */
size_t vertrix_inflate(const unsigned char *input, size_t input_size, unsigned char *output,
                       size_t output_size);

#endif
