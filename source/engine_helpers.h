#ifndef VERTRIX_ENGINE_HELPERS_H
#define VERTRIX_ENGINE_HELPERS_H
#include "random.h"
#include <stddef.h>
#include <stdint.h>

/* Original0x482480: construct a random-sample object: sample table token +0 = 0, mode byte +4
 * = 1, cursor +8 = 0, position word +0xc = 0, seed +0x10 = 0 and class token +0x14 =
 * 0x516c24 (an original address, never a native pointer). Short storage is preserved. */
int vertrix_random_object_construct(void *storage, size_t size);

/* Original0x487870: construct a table object: +0 = 0, +8 = 0, +0xc = class token 0x516dc4
 * and +4 = the value of the original global 0x4f81cc, supplied by the caller. */
int vertrix_table_object_construct(void *storage, size_t size, uint32_t default_value);

/* Original0x482750: minimum + draw(maximum - minimum + 1) with 16-bit operands. The original
 * faults when the width wraps to zero; that reports 0 and leaves *value untouched. */
int vertrix_random_inclusive(VertrixRandom *random, uint16_t minimum, uint16_t maximum,
                             uint32_t *value);

/* Original0x481420: size of the run-length encoding of the first count bytes (PCX style:
 * runs of up to 63 equal bytes take two bytes, a single byte below 0xc0 takes one and
 * otherwise two). */
uint32_t vertrix_rle_encoded_length(const uint8_t *data, uint32_t count);

/* Original0x4ae170: a cell cursor (original globals 0x5bb73c and 0x5bb740..0x5bb746). */
typedef struct
{
    int32_t index;
    int16_t x;
    int16_t y;
    int16_t width;
    int16_t height;
} VertrixCursor;

/* Clamp x to 0..width-1 and y to 0..height-1 (negative to zero, otherwise at most the limit
 * minus one, with 16-bit wrap) and recompute index = y * width + x. Always returns 1. */
int vertrix_cursor_clamp(VertrixCursor *cursor);
#endif
