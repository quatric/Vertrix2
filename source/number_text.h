#ifndef VERTRIX_NUMBER_TEXT_H
#define VERTRIX_NUMBER_TEXT_H
#include <stddef.h>
#include <stdint.h>
/* Numeric text selection in original 0x4b58a0: mode1 pads to width;
 * all other modes print unsigned decimal. Hidden zero overrides padding.
 * Failure preserves output. Does not bind/render a font resource. */
int vertrix_number_text(uint32_t value, uint32_t mode, uint32_t width, uint32_t show_zero,
                        char *output, size_t capacity);
#endif
