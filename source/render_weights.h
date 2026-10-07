#ifndef VERTRIX_RENDER_WEIGHTS_H
#define VERTRIX_RENDER_WEIGHTS_H
#include <stdint.h>
typedef struct
{
    uint8_t bytes[101][256];
    uint16_t words[101][512];
    uint8_t alpha[256][256];
    uint8_t inverse_alpha[256][256];
} VertrixRenderWeights;
/* Original 0x480730: complete routine: percentage and alpha tables. Native words are numerical
 * values, not serialized x86 memory. NULL output is rejected. */
int vertrix_render_weights_build(VertrixRenderWeights *output);
/* Original4ae26d..4ae2b9 selects amount and100-amount rows. Amount0..100;
 * invalid input preserves both outputs. Views borrow table storage. */
int vertrix_render_weights_select(const VertrixRenderWeights *tables, uint8_t amount,
                                  const uint8_t **source, const uint8_t **destination);
#endif
