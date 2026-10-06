#ifndef VERTRIX_LETTER_ROW_H
#define VERTRIX_LETTER_ROW_H
#include <stdint.h>

#include "block_factory.h"
#include "call_glue.h"

/* Original 0x46f000 (no arguments; `frame` is the token for ebp, the exception frame being
 * ignored): builds one actor for each character of the text 0x50e61f. 0x4ca070 initialises a local
 * string (frame - 0x2c) that 0x4ca370 assigns the text (the new string's pointer comes back in the
 * call's out_value), whose width 0x440610 measures (stored through its ecx
 * pointer, frame - 0x28; its stack pointer is frame - 0x24). The first actor sits at x = ((0x280 -
 * width + 1) >> 1) + 0x11, y = 0xf0, and each next one 0x23 further with the alternation
 * flag flipped. For each character: 0x4ca000 and (when it answers) 0x4abd70 make the actor,
 * 0x4adf20 initialises it (five zero stack arguments), 0x43f420 maps the character (with the signed
 * byte at 0x4f9c0d) and 0x4ac950 and 0x4ac8a0 take the result; the words and bytes at +0xc, +0x52,
 * +0x94, +0x95, +0x93, +8, +0xa, +0xe, +0x16, +0x10, +0x18, +0x4e and +0x30 are set, 0x4ac8f0 sets
 * the handler 0x45a290, 0x4ad510 the bounds, 0x4826c0 draws +0x24 (modulus 0x168) and +0x28
 * (modulus 3, plus 4, negated when the flag is clear) while +0x32 becomes 3, 0x4ac7d0, 0x4ac510 and
 * 0x4b5e70 (with the list 0x546758) finish it. 0x4ca210 releases the local. The services resolve
 * the string's header (the string address - 0xc: the length at +4, the characters from +0xc) and
 * the dword at 0x4f9c0a. Returns zero when memory cannot be accessed. */
enum
{
    VERTRIX_LETTER_TEXT = 0x50e61f,
    VERTRIX_LETTER_SECOND_TEXT = 0x50e626,
    VERTRIX_LETTER_GLOBAL = 0x4f9c0a
};

int vertrix_letter_row(const VertrixCalls *calls, const VertrixFactoryServices *services,
                       uint32_t frame);

/* Original 0x46f220: the same row for the text 0x50e626 with the handler 0x45a620, the local
 * string at frame - 0x34, the initialisation register 0x5161e0, the byte at +0x94 one and without
 * the stores to +0x52 and +0x95. */
int vertrix_letter_row_second(const VertrixCalls *calls, const VertrixFactoryServices *services,
                              uint32_t frame);

/* Original 0x46eda0 (eax = index; `frame` is the token for ebp): for each of the dword count at
 * 0x540000 + 4 * index rows, 0x4ca310 copies the string at 0x53fe20 + 4 * index + 0xc * row into a
 * local (frame - 0x38; the pointer comes back in out_value) and 0x440610 measures it (width through
 * ecx, frame - 0x34; a second value through its stack pointer, frame - 0x30, in out_value). One
 * actor per character is made as in vertrix_letter_row, laid out from the centred x, the row y
 * 0x1a4 + 0x32 * row and 0x23 apart, with the last three rows given the handler 0x457e40 and the
 * vertical placement from the second measure. 0x4ca210 releases the local. */
int vertrix_letter_grid(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        uint32_t frame, uint32_t index);

/* Original 0x46ea30 (eax = index; `frame` is the token for ebp): like vertrix_letter_grid for a
 * menu of strings kept in a local array of 0x30 strings (frame - 0x128, made by 0x4ccf3b). 0x4826c0
 * draws a choice of three; the row count is the dword at 0x53fd38 + 12 * index + 4 * choice plus 8.
 * Every element is assigned the text 0x50e60d by 0x4ca370, the first count - 8 elements are copied
 * (0x4ca310, then trimmed by 0x4ca710) from the string variables at 0x53d998 + 4 * index + 0x4c *
 * choice, 0xe4 apart, and the last three are assigned 0x50e60e, 0x50e616 and 0x50e619. Each row is
 * then built as in the grid (text local frame - 0x3c, width frame - 0x38, second measure frame -
 * 0x34), with the register values the original leaves for 0x4ca000, 0x4ac910 and 0x4ac7d0, and
 * 0x4cda10 finishes the locals. */
int vertrix_letter_menu(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        uint32_t frame, uint32_t index);

#endif
