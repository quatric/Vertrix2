#ifndef VERTRIX_RENDER_PIXEL_H
#define VERTRIX_RENDER_PIXEL_H
#include "palette_tables.h"
#include "render_preparation.h"
/* Original flag/rule selection plus recovered32-bit pixel kernels. Returns1
 * applied,0 unsupported kernel or invalid required backing; failure preserves
 * output. Prepared views borrow their table lifetimes. This does not traverse
 * pixels, apply source-alpha skipping, or perform full actor preparation. */
int vertrix_render_pixel32(uint32_t flags, uint32_t source, uint32_t destination,
                           const VertrixRenderPreparation *prepared,
                           const VertrixPaletteTables *tables, uint32_t *output);
#endif
