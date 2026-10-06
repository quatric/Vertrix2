#ifndef VERTRIX_RENDER_COLOR_BANK_H
#define VERTRIX_RENDER_COLOR_BANK_H
#include <stddef.h>
#include <stdint.h>
typedef struct
{
    uint32_t lookup[13];
    uint32_t colors[13];
    uint32_t format_colors[12];
} VertrixRenderColorBank;
/* Original474e00: destination RGB mask ordering and selected map row100.
 * The row is explicit because original54cdc8 can select other map tables.
 * Invalid masks/row preserve output. */
int vertrix_render_color_bank_build(const uint32_t masks[3], const uint8_t *row, size_t row_size,
                                    VertrixRenderColorBank *output);
#endif
