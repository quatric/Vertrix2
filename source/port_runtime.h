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

/* Original 0x48a300: 0x4b79e0 with the same registers; returns the edx it was given, with the
 * call's edx. */
uint32_t vertrix_port_list_text_slot(PORT_SIGNATURE);

/* Original 0x481b20: store 0x516b14 at eax + 0x28. Returns eax; edx is unchanged. */
uint32_t vertrix_port_object_set_table(PORT_SIGNATURE);

/* Original 0x4cd090 (eax = output buffer, dl = byte): append the byte at the buffer's pointer
 * (+0) and count it (+0x10). Returns the buffer, edx the byte's address. */
uint32_t vertrix_port_buffer_put(PORT_SIGNATURE);

/* Original 0x4c9dd6: sin: the coprocessor's (0x4db710) when 0x5054a1 is set, else 0x4c9b6a with
 * ebx 2. Returns its eax and edx. */
uint32_t vertrix_port_sine(PORT_SIGNATURE);

/* Original 0x481b30 (eax = object, dl = mode): its destructor, as 0x4ac130 is the actor's: with
 * mode bit 4, 0x4ccb9f finalizes the record (type 0x515130) and 0x4ca040 frees it; otherwise the
 * object gets its base table (0x516b14) under a guard record (0x516af0) and, with mode bit 2,
 * 0x4ca050 frees it. Returns the object. */
uint32_t vertrix_port_object_destroy(PORT_SIGNATURE);

/* Original 0x4b79e0 (eax = list, edx = address of a string, ebx = index, ecx = argument): set the
 * string to the list item's text: it starts as 0x5110cb (0x4ca280); for an item (0x4b79c0),
 * 0x4b7710 makes the text into a local string, 0x4ca310 assigns it and 0x4ca210 releases the
 * local, under a guard record (0x5186cc). Returns the string's address. */
uint32_t vertrix_port_list_text(PORT_SIGNATURE);

/* Original 0x4d8770 (eax = pointer array, edx = new size, ebx = grow step or -1): resize it (data
 * +4, size +8, capacity +0xc, grow step +0x10). Size 0 frees the data (0x4ca040); with no data it
 * is allocated (0x4c9ff0) and cleared (0x4eb5c0); within the capacity the new slots are cleared;
 * beyond it the capacity grows by the step (the old size / 8 within 4 and 0x400 when 0), or to the
 * size, and the slots are copied (0x4eb5e0) into the new data, the rest cleared and the old freed.
 * Returns the last call's eax and edx (the array and size when none is made). */
uint32_t vertrix_port_pointer_array_resize(PORT_SIGNATURE);

#endif
