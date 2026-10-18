#ifndef FONT_H
#define FONT_H
#include "port.h"

/* Clean ports of the font glyph lookups (port.h). A font record keeps a 16-bit glyph index for
 * each character code at +0x08; the fonts are 0x20c-byte records from 0x541988, and the glyph
 * images the dwords from 0x5410f8. */

/* Original 0x48ac00 (eax = font, dl = character): the font's 16-bit glyph index for the character
 * in ax (eax's upper half unchanged). edx is the character. */
uint32_t vertrix_port_font_glyph_index(PORT_SIGNATURE);

/* Original 0x43f420 (al = font number, signed; dl = character): the glyph index from 0x48ac00 (ecx
 * the character), stored at the word 0x5410f4; 0xffff gives 0, otherwise the glyph image at that
 * (signed) index. Returns it, with edx the lookup's. */
uint32_t vertrix_port_font_glyph(PORT_SIGNATURE);

#endif
