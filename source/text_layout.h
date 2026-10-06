#ifndef VERTRIX_TEXT_LAYOUT_H
#define VERTRIX_TEXT_LAYOUT_H
#include <stdint.h>
/* Original 0x440990: signed-word dimensions and bounds. Oversized text
 * can return before either origin is added. Does not measure a font. */
int vertrix_text_layout(int16_t width, int16_t height, int16_t left, int16_t right, int16_t top,
                        int16_t bottom, int16_t *x, int16_t *y);
#endif
