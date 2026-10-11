#ifndef VERTRIX_PORT_PIXEL_FORMAT_H
#define VERTRIX_PORT_PIXEL_FORMAT_H
#include "port.h"

/* Clean ports of the pixel format conversions (port.h). A format record has the channel masks of
 * red, green, blue and alpha at +0x04, +0x08, +0x0c and +0x10, the bytes +0x19..+0x1c the right
 * shifts that bring each masked channel down to its low bits, the bytes +0x1d..+0x20 the left
 * shifts that scale it to eight bits, and the bytes +0x21..+0x23 the positions of red, green and
 * blue in a packed 24-bit colour. Shift counts are taken modulo 32 as on x86. */

/* Original 0x481d90 (eax = source format, edx = target format, ebx = pixel): each channel is
 * masked and shifted down and left by the source's shifts, then right by the target's left shift
 * and left by its right shift. Returns the target pixel; edx is unchanged. */
uint32_t vertrix_port_pixel_convert(PORT_SIGNATURE);

/* Original 0x481e10 (eax = source format, edx = target format, ebx = pixel): the source's
 * channels scaled to eight bits are packed at the target's positions (+0x21..+0x23), and the
 * packed red, green and blue bytes (bits 16..23, 8..15 and 0..7) are converted back with the
 * source format's own shifts; alpha is taken back directly. Returns the result, with edx the
 * green part. */
uint32_t vertrix_port_pixel_repack(PORT_SIGNATURE);

/* Original 0x479a40 (eax = surface, edx = colour 0xRRGGBB): the colour in the surface's pixel
 * format, by its kind byte +0x0d: 0 is 3-3-2, 1 is 5-5-5, 2 is 5-6-5 and any other keeps the
 * colour. The kind is kept at 0x558a50. Returns the pixel in eax and edx. */
uint32_t vertrix_port_pixel_pack(PORT_SIGNATURE);

#endif
