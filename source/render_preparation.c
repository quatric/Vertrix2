#include "render_preparation.h"

int vertrix_render_prepare(VertrixRenderFlagState state, uint8_t cycle,
                           const VertrixRenderWeights *weights, const VertrixRenderColorBank *bank,
                           const uint8_t *hues, size_t hue_count, VertrixRenderPreparation *output)
{
    if (!output)
    {
        return 0;
    }
    VertrixRenderPreparation result = *output;
    if (state.format_000 != state.format_730)
    {
        if (!bank || !vertrix_render_color_prepare(state.format_000, bank->lookup, bank->colors, 13,
                                                   hues, hue_count, &result.color))
        {
            return 0;
        }
    }
    if (state.flag_739 == 1)
    {
        if (!vertrix_render_weights_select(weights, state.amount_00e, &result.source_weights,
                                           &result.destination_weights))
        {
            return 0;
        }
        result.source_words = weights->words[state.amount_00e];
        result.destination_words = weights->words[100u - state.amount_00e];
    }
    result.map_shift = (int16_t)(state.word_002 < 32768 ? (int32_t)state.word_002
                                                        : (int32_t)state.word_002 - 65536);
    result.cycle_enabled = state.flag_73a == 1;
    result.cycle = result.cycle_enabled ? cycle : 0;
    *output = result;
    return 1;
}
