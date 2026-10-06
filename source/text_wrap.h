#ifndef VERTRIX_TEXT_WRAP_H
#define VERTRIX_TEXT_WRAP_H
#include <stdint.h>

#include "block_factory.h"
#include "call_glue.h"

/* The arguments of 0x4b25b0: registers eax (the text object), edx (the text pointer), ebx (the low
 * byte is the font byte stored at +0x160) and ecx (the low word is stored at +0xe), and ten stack
 * dwords nearest esp first, stored as the original does at +0x16 (word), +0xf4 and +0xf8 (the low
 * words sign extended), +0x2f2, +0x2f4, +0x2f6 and +0x2f8 (words), +0x2fc, +0x300 and +0x304. */
typedef struct VertrixTextWrap
{
    uint32_t object;
    uint32_t text;
    uint32_t font;
    uint32_t ecx;
    uint32_t left;
    uint32_t right;
    uint32_t bottom;
    uint32_t margin_left;
    uint32_t margin_right;
    uint32_t spacing_a;
    uint32_t spacing_b;
    uint32_t flag_a;
    uint32_t flag_b;
    uint32_t flag_c;
} VertrixTextWrap;

/* The two bytes the original leaves in the frame word above its width local (frame - 0xe) are
 * added into its running line width: the services resolve frame - VERTRIX_TEXT_WRAP_FRAME to
 * their storage (4 bytes). */
enum
{
    VERTRIX_TEXT_WRAP_FRAME = 0x10,
    VERTRIX_TEXT_WRAP_FRAME_SIZE = 4
};

/* Original 0x4b25b0 (`frame` is the token for ebp; ret 0x28): breaks a text into lines. 0x4ca370
 * assigns the text to the string at +0x15c (the new pointer comes back in out_value) and the
 * arguments are stored in the object. The available width is the right argument (the dword at
 * +0xf4 source) minus the two margins. The line count (byte at +0x161) and, for each line, its
 * start (words from +0x162) and length (words from +0x22a) are built by measuring words one
 * character at a time (0x4ca280 makes a one character string, 0x4ca630 appends the character,
 * 0x440610 measures it with the font byte, +0x44 and the signed byte at +0x160, width through ecx;
 * 0x4ca210 releases the string): a word that does not fit the line ends it, and the spaces after a
 * word (measured the same way from the literal 0x511084) are added to the line unless they overflow
 * it. Leading spaces are skipped; at the end the last line is closed when it has width, and the
 * trailing spaces of each line are trimmed from its length. Returns zero when memory cannot be
 * accessed.
 */
int vertrix_text_wrap(const VertrixCalls *calls, const VertrixFactoryServices *services,
                      uint32_t frame, const VertrixTextWrap *wrap);

#endif
