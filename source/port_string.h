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

#endif
