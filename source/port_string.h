#ifndef VERTRIX_PORT_STRING_H
#define VERTRIX_PORT_STRING_H
#include "port.h"

/* Clean ports of the runtime's string and character routines (port.h). A string's text is preceded
 * by its record: the reference count at -0x0c, the length at -0x08 and the capacity at -0x04. The
 * empty string is the shared record whose text is at [0x500818]. Multi-byte text is on when the
 * global 0x5c8950 is set; the lead bytes are those with bit 0 set in the table at 0x5c8961. */

/* Original 0x4e3a90 (eax = text): the address of the next character: two bytes on for a lead byte
 * followed by a non-zero byte in multi-byte text, one otherwise. edx is unchanged. */
uint32_t vertrix_port_char_next(PORT_SIGNATURE);

/* Original 0x4e6f30 (eax = text): the length of its first character, 2 for a lead byte in
 * multi-byte text and 1 otherwise. edx is unchanged. */
uint32_t vertrix_port_char_length(PORT_SIGNATURE);

/* Original 0x4e7120 (eax = character code, edx = destination): store the character, high byte
 * first for a two-byte code. Returns the destination, with edx the code's high byte for a two-byte
 * code and unchanged otherwise. */
uint32_t vertrix_port_char_put(PORT_SIGNATURE);

/* Original 0x4ca0d0 (eax = address of a string, edx = length): a new string of that length, from
 * 0x4c9ff0 (length + 13 bytes): count 1, length and capacity the length (from the edx the
 * allocation leaves), a zero after the text. A zero length stores the empty string from 0x4ca060.
 * The text's address is stored at eax's address. Returns the record (or the empty string's text),
 * with edx the call's. */
uint32_t vertrix_port_string_new(PORT_SIGNATURE);

/* Original 0x4ca150 (one stack argument: a string record): unless it is the empty string, the
 * import at [0x4f1c34] (InterlockedDecrement) on it and, when that leaves zero or less, 0x4ca040
 * (FreeMem) on it. Returns the last call's eax and edx (the record and edx unchanged for the empty
 * string). */
uint32_t vertrix_port_string_release(PORT_SIGNATURE);

/* Original 0x4ca060: the empty string's text, 0x50081c. edx is unchanged. */
uint32_t vertrix_port_string_empty(PORT_SIGNATURE);

/* Original 0x4ca630 (eax = address of a string, dl = character): append the character through
 * 0x4ca5a0 (edx 1, ebx the address of a one-byte local holding it, ecx the string's address).
 * Returns the string's address, with edx the call's. */
uint32_t vertrix_port_string_append_char(PORT_SIGNATURE);

/* Original 0x4ca5a0 (eax = address of a string, edx = count, ebx = source): append `count` bytes.
 * Nothing for a count of 0 (returns the address, edx the source). A record held once with room
 * for them (reference count and new length compared signed) takes them in place: 0x4eb5e0 copies
 * them to the end (ebx and ecx the count), the length grows and the text is terminated; returns
 * the new length, edx the text. Otherwise 0x4ca3f0 (edx the old length, ebx the text, ecx the
 * count, one stack argument: the source) builds the longer string and 0x4ca150 releases the old
 * record; returns the release's eax and edx. */
uint32_t vertrix_port_string_append(PORT_SIGNATURE);

/* Original 0x4ca210 (eax = address of a string): release its record as 0x4ca150 does (the
 * decrement and free are called with ebx the address). Returns the address, with edx the last
 * call's (unchanged for the empty string). */
uint32_t vertrix_port_string_release_variable(PORT_SIGNATURE);

/* Original 0x4ca110 (eax = address of a string): release it as 0x4ca210 does and make it the
 * empty string (the text [0x50081c] through 0x4ca060). Returns that text (the record for a string
 * already empty); edx is unchanged. */
uint32_t vertrix_port_string_clear(PORT_SIGNATURE);

/* Original 0x4e7b50 (eax = text): 1 when the text ends at its first byte, 2 when the first byte
 * is a lead byte (the multi-byte tables of 0x4e3a90) followed by the end, otherwise 0. edx is
 * unchanged. */
uint32_t vertrix_port_char_end(PORT_SIGNATURE);

/* Original 0x4ca3f0 (eax = address of a string, edx and ebx = count and bytes of the first part,
 * ecx = count of the second, one stack argument: its bytes, popped by the routine): the string
 * becomes a new one (0x4ca0d0, edx the total) holding both parts, each copied by 0x4eb5e0 (ebx the
 * count, ecx the second count). Returns the last copy's eax and edx; with no bytes at all, the
 * address and 0. */
uint32_t vertrix_port_string_concat(PORT_SIGNATURE);

/* Original 0x4ca310 (eax = the string variable, edx = the source variable): assignment. Nothing
 * happens when they already share their text. A source whose count is negative (locked), or a
 * locked target that is not the empty string, is copied by 0x4ca2e0 (ebx the text, edx its
 * length); otherwise 0x4ca110 clears the target and it shares the source's record, whose count
 * InterlockedIncrement ([0x4f1c38]) raises. Returns the variable. */
uint32_t vertrix_port_string_assign(PORT_SIGNATURE);

/* Original 0x4ccfe0 (eax and edx = the texts): strcmp, a dword at a time in blocks of 16 bytes.
 * Returns 0 when they match to their ends, otherwise -1 or 1 as the first differing byte of eax's
 * is below or above edx's (unsigned), with the flags of `sub eax, eax` or `or al, 1`. edx is left
 * advanced past the whole blocks that matched (the last block's when its last dword ends it). */
uint32_t vertrix_port_string_compare(PORT_SIGNATURE);

/* Original 0x4ca070 (eax = address of a string): make it the empty string (0x4ca060, ebx the
 * address). Returns the address; edx is unchanged. */
uint32_t vertrix_port_string_init(PORT_SIGNATURE);

/* Original 0x4ca1e0 (eax = address of a string, edx = length): make sure the string is its own
 * and holds the length: when it is shared (count over 1) or too small (signed), 0x4ca110 clears it
 * and 0x4ca0d0 makes a new one (ecx the address both times). Returns the new record, or the old
 * one when it is kept. */
uint32_t vertrix_port_string_reserve(PORT_SIGNATURE);

/* Original 0x4ca2e0 (eax = address of a string, edx = length, ebx = text): set the string to the
 * text: 0x4ca1e0 reserves it, 0x4eb5e0 copies the bytes, then the length and a terminating zero
 * are stored (ecx the address throughout). Returns the text. */
uint32_t vertrix_port_string_set(PORT_SIGNATURE);

/* Original 0x4ca370 (eax = address of a string, edx = C text or 0): set the string to the text,
 * its length from lstrlenA ([0x4f1d24]), through 0x4ca2e0 (ebx the text). Returns the address. */
uint32_t vertrix_port_string_set_text(PORT_SIGNATURE);

/* Original 0x4ca1a0 (eax = address of a string): when it is shared, give it its own copy: 0x4ca110
 * releases it, 0x4ca0d0 makes a record of the same length and 0x4eb5e0 copies the text with its
 * zero (ebx the old record, ecx the address, until the copy). Returns the copy's result, or the
 * address when the string is its own; edx is unchanged. */
uint32_t vertrix_port_string_make_unique(PORT_SIGNATURE);

/* Original 0x4ca280 (eax = address of a string, edx = text or resource number): start it empty
 * (0x4ca060), then set it to the resource string numbered edx when edx is under 0x10000
 * (0x4db8c0), or else to the C text (lstrlenA [0x4f1d24], 0x4ca0d0, 0x4eb5e0, ebx the length).
 * Returns the address. */
uint32_t vertrix_port_string_from(PORT_SIGNATURE);

/* Original 0x4e3a50 (eax = text): the character there: a lead byte and the next as one code
 * (lead byte high), otherwise the byte. edx is unchanged. */
uint32_t vertrix_port_char_code(PORT_SIGNATURE);

/* Original 0x4ca090 (eax = address of a new string, edx = address of the source): copy-construct.
 * An unlocked source's record is shared (its count raised by InterlockedIncrement [0x4f1c38]);
 * a locked one's text is copied into an empty string (0x4ca060, then 0x4ca370). Returns the
 * address, with the last call's edx. */
uint32_t vertrix_port_string_copy(PORT_SIGNATURE);

/* Original 0x4ca6c0 (eax = address of a string, edx = length or -1): after the text was written in
 * place, make the string its own (0x4ca1a0) and set its length (lstrlenA [0x4f1d24] for -1) with
 * the zero after it. Returns the text, edx the length. */
uint32_t vertrix_port_string_set_length(PORT_SIGNATURE);

/* Original 0x4ca670 (eax = address of a string, edx = size): make it its own and at least that
 * big: when shared or too small, 0x4ca0d0 makes a record of the size (at least the length), the
 * text is copied (0x4eb5e0) with its length, and 0x4ca150 releases the old record. Returns the
 * text. */
uint32_t vertrix_port_string_reserve_unique(PORT_SIGNATURE);

/* Original 0x4cdfe0 (eax = address of a string): cut the spaces off its end (isspace 0x4e10d0, the
 * next character 0x4e1054) after making it its own (0x4ca1a0). edx is unchanged. */
uint32_t vertrix_port_string_trim_end(PORT_SIGNATURE);

/* Original 0x4ce030 (eax = address of a string): cut the spaces off its start, moving the rest
 * down (0x4e1140). edx is unchanged. */
uint32_t vertrix_port_string_trim_start(PORT_SIGNATURE);

/* Original 0x4df884 (eax = text, ebx = limit): its length, at most the limit; edx is left one past
 * the last byte read. */
uint32_t vertrix_port_text_length_limit(PORT_SIGNATURE);

/* Original 0x4df81c (eax = format text, edx = specification): read printf's flags: '-' sets bit 8
 * of the flags (the byte +0x1e, cleared first), '#' bit 1, '+' bit 4 (clearing bit 2), ' ' bit 2
 * unless '+' was seen, and '0' sets the pad character (+0x16). Returns the first other character's
 * address; edx is unchanged. */
uint32_t vertrix_port_format_flags(PORT_SIGNATURE);

/* Original 0x4dfa7c (eax = specification): for '0' padding without '-', grow the zero count
 * (+0x24) by whatever the width (+4) has left after the six parts (+0x20 to +0x34). Registers are
 * unchanged. */
uint32_t vertrix_port_format_zero_pad(PORT_SIGNATURE);

/* Original 0x4df6c8 (eax = format text after '%', edx = address of the argument pointer, ebx =
 * specification): read printf's flags (0x4df81c, the pad set to ' '), the width (+4, '*' taking an
 * argument, negative meaning '-'), the precision (+8, -1 when none, '0' padding dropped when given)
 * and the size: 'l' or 'w' (bit 0x20 of +0x1e), 'h' (0x10), 'N' (0x40), 'F' (0x80), 'L' or "I64"
 * (bit 1 of +0x1f). Returns the conversion character's address; edx's low byte is the last byte
 * read. */
uint32_t vertrix_port_format_spec(PORT_SIGNATURE);

/* Original 0x4daab0(eax = destination, edx = source, ebx = length, ecx = limit): copy a string
 * of at most the smaller of the two lengths (0x4e39a0 measures it, 0x4e39d0 copies) and
 * terminate it where 0x4e39f0 says. Nothing for a null destination. */
uint32_t vertrix_port_copy_terminated(PORT_SIGNATURE);

/* Original 0x4d7d70(stack: a path name, the string for the root; ret 0): the root of the path's
 * full name (GetFullPathNameA, slot 0x4f1d20, into the string's buffer from 0x4ca670): for a
 * UNC name up to the separator after the share, else up to the first separator, which is kept;
 * the name is cut after it and the string's length fixed by 0x4ca6c0. Characters advance through
 * 0x4e1054. */
uint32_t vertrix_port_path_root(PORT_SIGNATURE);

/* Original 0x4d7c40(stack: a file name, a MAX_PATH buffer; ret 0): the name's full path into the
 * buffer (GetFullPathNameA, else the name copied and 0 returned). The root's volume information
 * then decides the case: upper case on a volume that does not preserve it, and the file part as
 * FindFirstFileA spells it without Unicode names on disk. Returns 1, or 0 when the volume cannot
 * be read. */
uint32_t vertrix_port_full_path(PORT_SIGNATURE);

#endif
