#ifndef VERTRIX_PALETTE_COLOR_H
#define VERTRIX_PALETTE_COLOR_H
#include <stddef.h>
#include <stdint.h>
/* Original474910 HSV conversion. Hue0..360, saturation/value0..100.
 * Output channels round half upward after original single-precision stages.
 * Invalid inputs preserve output. */
int vertrix_palette_color(uint16_t hue, uint16_t saturation, uint16_t value, uint16_t output[3]);
/* Original474cd0 channel table5468b0:201 rows of101 bytes. */
int vertrix_palette_channels(uint8_t *output, size_t size);
/* Original475183..47525c: select first nearest entry from101 channel values
 * independently for RGB. Row is the original HSV value/map selector0..200.
 * Pack selected RGB indices in bytes3/2/1 and row in byte0. */
int vertrix_palette_lookup_entry(const uint8_t *maps, size_t size, uint16_t row,
                                 const uint8_t channels[3], uint32_t *output);
/* Original474560 RGB-to-HSV. RGB channels0..255; output hue is truncated,
 * saturation/value round half upward. chromatic distinguishes grayscale. */
int vertrix_palette_rgb(uint16_t red, uint16_t green, uint16_t blue, uint16_t output[3],
                        uint32_t *chromatic);
#endif
