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
#endif
