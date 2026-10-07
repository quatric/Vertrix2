#ifndef VERTRIX_RENDER_PREPARATION_H
#define VERTRIX_RENDER_PREPARATION_H
#include "render_color.h"
#include "render_color_bank.h"
#include "render_dispatch.h"
#include "render_weights.h"
typedef struct
{
    VertrixRenderColor color;
    const uint8_t *source_weights;
    const uint8_t *destination_weights;
    const uint16_t *source_words;
    const uint16_t *destination_words;
    int16_t map_shift;
    uint8_t cycle_enabled;
    uint8_t cycle;
} VertrixRenderPreparation;
/* Original 0x4ae250: complete decisions. Views borrow weights; fixed color is
 * refreshed only for format mismatch, weights only when flag739 equals1.
 * map_shift is the signed pointer-table shift, NOT a clamped channel row.
 * cycle describes original4754e0 auxiliary binding, not host pointer arithmetic.
 * Initialize output before use; unchanged fields retain prior state.
 * Unsupported bank indices/amounts and missing required inputs preserve output.
 * Pixel kernels must still resolve the selected map/auxiliary views separately. */
int vertrix_render_prepare(VertrixRenderFlagState state, uint8_t cycle,
                           const VertrixRenderWeights *weights, const VertrixRenderColorBank *bank,
                           const uint8_t *hues, size_t hue_count, VertrixRenderPreparation *output);
#endif
