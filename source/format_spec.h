#ifndef VERTRIX_FORMAT_SPEC_H
#define VERTRIX_FORMAT_SPEC_H
#include <stdint.h>

#include "block_factory.h"

/* Original 0x4df6c8 (eax = the format text after the percent sign, edx = pointer to the argument
 * pointer, ebx = the specification record) with its callee 0x4df81c: reads one print format
 * specification into the record. Flags (0x4df81c; record word +0x1e cleared first): '-' sets +0x1e
 * bit 3, '#' bit 0, '+' sets bit 2 and clears bit 1, ' ' sets bit 1 unless bit 2 is set, '0'
 * stores the pad character '0' at +0x16 (which is otherwise a space). The width at +4 is '*' (the
 * next argument dword; a negative one is negated and sets +0x1e bit 3) or decimal digits; the
 * precision at +8 is -1, or '.' followed by '*' (the next argument, -1 when negative) or digits (a
 * precision other than -1 resets the pad character to a space). A size letter then sets a flag
 * and moves on: 'F' +0x1e bit 7, 'N' bit 6, 'h' bit 4, 'l' and 'w' bit 5, 'L' and "I64" +0x1f bit
 * 0 (the letter moves one, "I64" three), anything else stays. Arguments are read at the argument
 * pointer, which moves on four bytes each time. *result is the original's eax, the text after
 * the specification. Returns zero when memory cannot be accessed. */
int vertrix_format_spec(const VertrixFactoryServices *services, uint32_t text,
                        uint32_t argument_cell, uint32_t spec, uint32_t *result);

#endif
