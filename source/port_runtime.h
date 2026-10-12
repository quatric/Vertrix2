#ifndef VERTRIX_PORT_RUNTIME_H
#define VERTRIX_PORT_RUNTIME_H
#include "port.h"

/* Clean ports of small runtime routines (port.h). */

/* Original 0x4d85f0: the thread's data block (the routine at [0x507c9c]) plus 0x0c, the random
 * seed's address. Returns it, with edx the call's. */
uint32_t vertrix_port_random_seed_address(PORT_SIGNATURE);

/* Original 0x4d85fc: rand(). The seed at 0x4d85f0's address becomes seed * 0x41c64e6d + 0x3039;
 * returns bits 16 to 30 of it (0 when there is no address). edx is unchanged. */
uint32_t vertrix_port_random(PORT_SIGNATURE);

/* Original 0x4e5838: the running thread's data, keeping the last error (the imports
 * GetLastError [0x4f1bbc] and SetLastError [0x4f1cb0] around it). TlsGetValue ([0x4f1cdc], the
 * index [0x507c98]) gives it; when that is 0, 0x4e8400 makes it (eax and ebx 0), and when its byte
 * +0x53 is set, 0x4e843c (eax and ebx the data) gives it instead. edx is unchanged. */
uint32_t vertrix_port_thread_data(PORT_SIGNATURE);

/* Original 0x4e10d0 (eax = character): isspace. With the double-byte code page 0x3a4 and a lead
 * byte in ah, 0x4e7140 answers. Otherwise 0x4e7120 writes the character's bytes to a local,
 * 0x4e6f30 (dl 0) gives their length and the byte after them is cleared (with the low byte of its
 * edx), and GetStringTypeA ([0x4f1bec], CT_CTYPE1) types them: the space bit (8) of the first's
 * type, 0 when the call fails. edx is its saved copy, which long bytes overrun. */
uint32_t vertrix_port_is_space(PORT_SIGNATURE);

/* Original 0x4849e0 (eax, edx = 16.16 fixed-point values): their product, the signed 64-bit
 * product's middle 32 bits; edx is its high dword. */
uint32_t vertrix_port_fixed_multiply(PORT_SIGNATURE);

/* Original 0x4b79c0 (eax = list, edx = index): the list's item at the index (the items at +4,
 * their count at +8), 0 past the end (unsigned). edx is unchanged. */
uint32_t vertrix_port_list_item(PORT_SIGNATURE);

/* Original 0x440990 (eax, edx = addresses of the x and y words, ebx, ecx = the text's width and
 * height, stack = left, right, top, bottom words): where to put text centred in the box. Each
 * word starts 0; when the box is wider (taller) than one pixel the offset is half the room left
 * (the width counted one wider), rounded towards zero, and a negative one ends it there (eax that
 * offset, edx its sign). Otherwise the box's left and top are added. Returns the top. */
uint32_t vertrix_port_text_layout(PORT_SIGNATURE);

/* Original 0x4b7a80 (eax = list, edx = index): the dword at +8 of the list's item (0x4b79c0), 0
 * when there is none. edx is the call's. */
uint32_t vertrix_port_list_item_field(PORT_SIGNATURE);

/* Original 0x48a2f0: 0x4b7a80 with the same registers. */
uint32_t vertrix_port_list_item_field_call(PORT_SIGNATURE);

/* Original 0x4b5eb0 (eax = list, edx = key): the first item whose first dword is the key, or 0.
 * edx is left as the last item read (the key when the list is empty). */
uint32_t vertrix_port_list_find(PORT_SIGNATURE);

/* Original 0x48a2e0: the dword at eax + 8. edx is unchanged. */
uint32_t vertrix_port_field8(PORT_SIGNATURE);

#endif
