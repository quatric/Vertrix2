#include "render_weights.h"

int vertrix_render_weights_build(VertrixRenderWeights *output)
{
    if (!output)
    {
        return 0;
    }
    for (uint32_t amount = 0; amount <= 100; ++amount)
    {
        for (uint32_t value = 0; value < 256; ++value)
        {
            output->bytes[amount][value] = (uint8_t)(value * amount / 100u);
        }
        for (uint32_t value = 0; value < 512; ++value)
        {
            output->words[amount][value] = (uint16_t)(value * amount / 100u);
        }
    }
    for (uint32_t alpha = 0; alpha < 256; ++alpha)
    {
        for (uint32_t value = 0; value < 256; ++value)
        {
            uint8_t weighted = (uint8_t)(value * alpha / 255u);
            output->alpha[alpha][value] = weighted;
            output->inverse_alpha[255u - alpha][value] = weighted;
        }
    }
    return 1;
}

int vertrix_render_weights_select(const VertrixRenderWeights *tables, uint8_t amount,
                                  const uint8_t **source, const uint8_t **destination)
{
    if (!tables || !source || !destination || source == destination || amount > 100)
    {
        return 0;
    }
    *source = tables->bytes[amount];
    *destination = tables->bytes[100u - amount];
    return 1;
}
