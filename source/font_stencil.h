#ifndef VERTRIX_FONT_STENCIL_H
#define VERTRIX_FONT_STENCIL_H
#include <stddef.h>
#include <stdint.h>
/* Original fragment 0x4831b0 pixel transform. Output dimensions are source dimensions
 * plus twice floor(stencil dimensions/2). Buffers must not overlap. */
int vertrix_font_stencil(const uint32_t *source, uint32_t width, uint32_t height,
                         const uint32_t *stencil, uint32_t stencil_width, uint32_t stencil_height,
                         uint32_t solid, uint32_t *output, size_t capacity);
#endif
