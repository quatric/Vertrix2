#ifndef VERTRIX_OBJECT_LABEL_H
#define VERTRIX_OBJECT_LABEL_H
#include <stdint.h>

#include "block_factory.h"
#include "call_glue.h"

/* Original 0x4b3210 (eax = object, edx = parent handle, bx = x offset, cx = y offset, stack
 * arguments flag_x_arg and flag_y_arg, both stdcall): store the parent at +0x160, the offsets at
 * +0x164 and +0x166 and the two flags at +0x168 and +0x16c. 0x4ca070 initialises a string temporary
 * (temp, the address of the caller's local, is passed through) and a non-zero parent sends it
 * through 0x4ca370 with the parent's dword +0x15c. The label is then placed by 0x4b65d0 on the
 * parent with the temporary, the sign-extended glyph byte +0x160 of the parent and the corner
 * words: the left is object word +0xe plus the x offset, or +0xe alone when +0x168 is set, the
 * right is the left again, or +0xe plus word +0xf4 minus one when +0x168 is set; the top is
 * word +0x16 plus the y offset, or +0x16 alone when +0x16c is set, the bottom is the top, or
 * +0x16 plus word +0xf8 minus one when +0x16c is set. 0x4ca210 releases the temporary.
 * The original returns the saved exception chain head, which no caller uses; returns one, or
 * zero when a storage is short or does not resolve. */
int vertrix_object_place_label(const VertrixCalls *calls, const VertrixFactoryServices *services,
                               uint32_t object, uint32_t parent, uint32_t ebx, uint32_t ecx,
                               uint32_t flag_x_arg, uint32_t flag_y_arg, uint32_t temp);

/* Original 0x4b65d0 (eax = object, edx = text, ecx = x1, bl = glyph byte, stack arguments x2, y1
 * and y2 at ebp + 8..0x10, ret 0xc; frame is the token for ebp). 0x4ca370 assigns the text to
 * object + 0x15c; the glyph byte is stored at +0x160 and the words x1, x2, y1 and y2 at +0x162,
 * +0x164, +0x166 and +0x168. 0x4408e0 then measures with the sign extended glyph, x1, y1 and x2
 * as registers and y2, the dword +0x15c, the byte +0x44 and four pointers to the locals
 * frame - 0x18, - 0x14, - 0x10 and - 0xc as stack arguments: its dwords at -0x18 and -0x14
 * become +0xf4 and +0xf8, the low words at -0x10 and -0xc become +0xe and +0x16. The call site
 * returns the four dwords in out_value, stack_rest[4], out_ebx and out_ecx. *result is the
 * original's eax, the dword at -0x14. Returns zero when a storage does not resolve. */
int vertrix_object_label_text(const VertrixCalls *calls, const VertrixFactoryServices *services,
                              uint32_t frame, uint32_t object, uint32_t text, uint32_t x1,
                              uint32_t glyph, const uint32_t arguments[3], uint32_t *result);
#endif
