#ifndef VERTRIX_ROTATION_H
#define VERTRIX_ROTATION_H
#include <stdint.h>
typedef struct
{
    uint32_t iterations;
    uint32_t unwrapped;
} VertrixRotationTrace;
/* Original 0x4ad060. Step and angle are signed words, but normalization
 * after a negative wrapped angle uses the original unsigned-word remainder.
 * Inactive calls retain the previous global iteration count. */
int vertrix_rotation_advance(int16_t *angle, int16_t step, uint32_t cycles,
                             VertrixRotationTrace *trace);
#endif
