#ifndef VERTRIX_RENDER_COLOR_H
#define VERTRIX_RENDER_COLOR_H
#include <stddef.h>
#include <stdint.h>
typedef struct
{
    uint32_t lookup_entry;
    uint32_t color;
    uint32_t half_color;
    uint16_t indices[3];
    uint8_t channels[3];
    uint8_t hue;
} VertrixRenderColor;
/* Original4ae2ff..4ae3b3: palette banks54b808/54b83c and hue table54b804.
 * Explicit counts bound original format-byte indexing; invalid inputs preserve
 * output. The caller decides whether format mismatch requires this preparation. */
int vertrix_render_color_prepare(uint8_t index, const uint32_t *lookup_colors,
                                 const uint32_t *colors, size_t count, const uint8_t *hues,
                                 size_t hue_count, VertrixRenderColor *output);
#endif
