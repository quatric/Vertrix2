#ifndef VERTRIX_OBJECT_VALUE_HELPERS_H
#define VERTRIX_OBJECT_VALUE_HELPERS_H
#include <stddef.h>
#include <stdint.h>

/* Small value routines of the original UI/surface objects. Storage is a flat little-endian copy
 * of the object; storage too small for the touched fields is preserved and 0 is returned. */

/* Original 0x4776a0: decimal text of value. At most width digits are produced, lowest digits
 * first, so a longer number loses its highest digits; zero gives one digit. A negative value uses
 * one position of the width and adds a minus sign in front. Writes a terminating zero; dest needs
 * 13 bytes. Returns the text length. */
size_t vertrix_format_decimal(int32_t value, uint8_t width, char *dest);

/* Original 0x478b70: write a ramp of n = word +0x26 bytes at +0x130: step 0x100 / (n - 1)
 * (n = 1 writes 0x80), starting at zero and saturating at 0xff. */
#define VERTRIX_RAMP_COUNT 0x26
#define VERTRIX_RAMP_FIRST 0x130
int vertrix_object_fill_ramp(uint8_t *object, size_t size);

/* Original 0x478da0: remaining = +0x14 - +4 * byte(+0xc) stored at +0x18; +0x10 = remaining != 0.
 * Returns +0x10. Needs 0x1c bytes. */
int vertrix_object_remaining(uint8_t *object, size_t size);

/* Original 0x478480: clamp the signed position x, y into the rectangle of words +0x3c/+0x3e
 * (minimum x/y) and +0x40/+0x42 (maximum x/y), storing the low words at +0x48/+0x4a. A value
 * below the minimum wins over the maximum, and the maximum is applied first for x. Needs 0x4c
 * bytes. */
int vertrix_object_clamp_position(uint8_t *object, size_t size, int32_t x, int32_t y);

/* Original 0x479a40: pack an 0x00rrggbb colour for a pixel format byte (+0xd of the surface):
 * 0 = 3-3-2, 1 = 5-5-5, 2 = 5-6-5, anything else leaves the colour unchanged. The original also
 * stores the format byte in the global 0x558a50, reported in stored_format. */
uint32_t vertrix_pixel_pack(uint8_t format, uint32_t rgb, uint8_t *stored_format);
#endif
