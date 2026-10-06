#ifndef VERTRIX_COLOR_CONVERSION_H
#define VERTRIX_COLOR_CONVERSION_H
#include <stdint.h>

#define VERTRIX_PALETTE_SIZE 256

/* Channel layout of a packed pixel format: for each of four channels (original slots 0..3
 * at +4, +8, +0xc and +0x10) the mask, the right shift that isolates it and the shift that
 * scales it to eight bits. */
typedef struct
{
    uint32_t mask[4];
    uint8_t shift[4];
    uint8_t scale[4];
} VertrixPixelFormat;

/* Original0x480890: expand 256 packed 6-bit RGB triples into four-byte palette entries
 * (each component << 2 truncated to a byte, fourth byte 2). */
void vertrix_palette_expand_vga(const uint8_t rgb[3 * VERTRIX_PALETTE_SIZE],
                                uint8_t entries[4 * VERTRIX_PALETTE_SIZE]);

/* Original0x480ca0: fill 256 RGB triples with the 8x8x4 colour cube; entry
 * (a * 32 + b * 4 + c) is (a * 8, b * 8, c * 16). */
void vertrix_palette_cube(uint8_t rgb[3 * VERTRIX_PALETTE_SIZE]);

/* Original0x481d90: convert a pixel between two channel layouts. Per channel the pixel is
 * masked, shifted right, scaled with the source's left shift, scaled back with the
 * destination's right shift and placed with its shift; x86 shift counts use five bits. */
uint32_t vertrix_pixel_convert(const VertrixPixelFormat *source,
                               const VertrixPixelFormat *destination, uint32_t pixel);
#endif
