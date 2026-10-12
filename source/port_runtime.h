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

/* Original 0x4e1060 (eax = character): isdigit, as 0x4e10d0 with 0x4e70d0 for a lead byte and the
 * digit bit (4) of the type. */
uint32_t vertrix_port_is_digit(PORT_SIGNATURE);

/* Original 0x4e9060 (eax = year): whether it is a leap year. edx is unchanged. */
uint32_t vertrix_port_leap_year(PORT_SIGNATURE);

/* Original 0x4d6710 (eax = text): atoi: spaces skipped (class bit 2 of the table 0x507d58, indexed
 * by the byte plus one), a sign, then the digits (class bit 0x20). edx is unchanged. */
uint32_t vertrix_port_parse_integer(PORT_SIGNATURE);

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

/* Original 0x4b3360: returns at once (eax and edx unchanged). */
uint32_t vertrix_port_nothing(PORT_SIGNATURE);

/* Original 0x4ec160 (eax = count, edx = size): calloc: 0x4e7c90 allocates count * size bytes (ebx
 * the size) and 0x4eb5c0 clears them. Returns the memory (0 when it fails), with the last call's
 * edx. */
uint32_t vertrix_port_clear_allocate(PORT_SIGNATURE);

/* Original 0x478da0 (eax = surface): its padding, the pitch (+0x14) less the width (+4) times the
 * pixel bytes (byte +0xc), stored at +0x18, and whether there is any, stored at +0x10. Returns
 * that; edx is unchanged. */
uint32_t vertrix_port_surface_padding(PORT_SIGNATURE);

/* Original 0x4b76d0 (eax = list, edx = string address): append a copy of the string: 0x4ca000
 * allocates the 4-byte slot (0 when it fails), 0x4ca090 copies the string into it, and 0x4d88a0
 * puts it at the list's end (edx the count, ecx 1). Returns 0. */
uint32_t vertrix_port_list_append_text(PORT_SIGNATURE);

/* Original 0x440ca0 (eax = surface, dl = alignment, bx, cx and the first two stack words = the
 * box, then the text and the actor): lay the text out in the box (0x4408e0, the actor's scale
 * +0x44) and draw it at the place found (0x440a20), under a guard record. Returns the record's
 * previous link; edx from the draw. */
uint32_t vertrix_port_text_draw(PORT_SIGNATURE);

/* Original 0x440a20 (eax = surface, dl = font, bx, cx = place, stack = text and the actor): draw
 * the text a character at a time under a guard record: each glyph (0x43f420) becomes a temporary
 * actor (0x4ca000, 0x4abd70, 0x4adf20) copying the actor's drawing settings, is measured (0x4b14c0)
 * and drawn (its table's +8) and destroyed (its table's first entry); a space only advances by the
 * font's space width (0x541988, 0x20c bytes a font). Returns the record's previous link. */
uint32_t vertrix_port_text_draw_glyphs(PORT_SIGNATURE);

/* Original 0x4dabb0 (eax = character): toupper for 'a' to 'z'. edx is unchanged. */
uint32_t vertrix_port_upper_case(PORT_SIGNATURE);

/* Original 0x48a420 (eax = reader, edx = stream): skip spaces; true when a token follows, false at
 * the end, a line break (skipped) or a '/' comment (skipped, the rest of the line read by
 * 0x48a380). */
uint32_t vertrix_port_stream_token_ahead(PORT_SIGNATURE);

/* Original 0x40ab10: 0x40ab20 with eax 0. */
uint32_t vertrix_port_audio_lock_call(PORT_SIGNATURE);

/* Original 0x40ab20 (eax = argument): when the audio device is open (0x4f6418 not 0xffff) and the
 * lock count (0x4f644c) goes from 0 to 1, call 0x52f020 with the argument. Returns its eax, else 0;
 * edx is unchanged. */
uint32_t vertrix_port_audio_lock(PORT_SIGNATURE);

/* Original 0x4b7600: construct the list (0x4d8650) and set its table to 0x518694. */
uint32_t vertrix_port_list_construct(PORT_SIGNATURE);

/* Original 0x4b79a0 (eax = list, edx = index): delete the item (0x4d88a0, one item, edx the list's
 * items +8). Returns 0. */
uint32_t vertrix_port_list_delete(PORT_SIGNATURE);

/* Original 0x48a380 (edx = stream): skip to the end of the line (0x48a910 ends, 0x48aa80 peeks,
 * 0x48aa90 skips a line break too). Returns the last call's eax and edx. */
uint32_t vertrix_port_stream_skip_line(PORT_SIGNATURE);

/* Original 0x4d8650 (eax = list): construct an empty list (table 0x51a0d4, no items, count or
 * capacity) under a guard record. Returns the list; edx is unchanged. */
uint32_t vertrix_port_list_create(PORT_SIGNATURE);

/* Original 0x48a310 (eax = reader, edx = stream): skip spaces, line breaks and '/' comments (the
 * rest of the line by 0x48a380). Returns the end test's eax, or the peeked pointer with its low
 * byte the next character. */
uint32_t vertrix_port_stream_skip_blank(PORT_SIGNATURE);

/* Original 0x4dac40 (eax = name): getenv: the value after "name=" in the environment 0x5c81d4
 * (strncmp 0x4e4080), else 0. edx is unchanged. */
uint32_t vertrix_port_environment_value(PORT_SIGNATURE);

/* Original 0x4b7830 (eax = list of strings): release each string (0x4ca210 then 0x4ca050) and
 * empty the list (0x4d8770 with no size), under a guard record. Returns the record's previous
 * link; edx is unchanged. */
uint32_t vertrix_port_string_list_clear(PORT_SIGNATURE);

/* Original 0x4b7610 (eax = list of strings, dl = flags): its destructor: with flag 4 it destroys an
 * array of them (0x4ccb9f with the destructor 0x513ea0, then 0x4ca040); otherwise its strings are
 * released (0x4b7830), the base list destroyed (0x4d86d0) and, with flag 2, its memory freed
 * (0x4ca050), under a guard record. Returns the list. */
uint32_t vertrix_port_string_list_destroy(PORT_SIGNATURE);

/* Original 0x4e9194 (eax, edx = two times as struct tm, ebx passed on): whether the first is
 * later: by the year (+0x10) when neither has a day-of-year flag (+0x20), else by their day counts
 * (0x4e909c). */
uint32_t vertrix_port_time_later(PORT_SIGNATURE);

/* Original 0x4e33d0 (eax = result, edx = year, ebx = month, ecx = day, stack = hour, minute,
 * second, dst): mktime (0x4e7850) of a struct tm built in the frame. Stores and returns the
 * result's address. */
uint32_t vertrix_port_time_make(PORT_SIGNATURE);

/* Original 0x4e3420 (eax = result, edx = SYSTEMTIME, ebx = dst): its time as 0x4e33d0 makes it, 0
 * before 1900. Stores and returns the result's address. */
uint32_t vertrix_port_time_from_system(PORT_SIGNATURE);

/* Original 0x4e3470 (eax = result, edx = FILETIME): its local time (FileTimeToLocalFileTime
 * 0x4f1b54, FileTimeToSystemTime 0x4f1b58, then 0x4e3420), the failing call's 0 otherwise. Stores
 * and returns the result's address. */
uint32_t vertrix_port_time_from_file(PORT_SIGNATURE);

/* Original 0x487860 (eax = object): its field +4. edx is unchanged. */
uint32_t vertrix_port_field4(PORT_SIGNATURE);

/* Original 0x475af0 (eax = object): clear its byte +0x5a. Registers are unchanged. */
uint32_t vertrix_port_clear_flag5a(PORT_SIGNATURE);

/* Original 0x41d660: count a tick at 0x5329f8. Registers are unchanged. */
uint32_t vertrix_port_tick_count(PORT_SIGNATURE);

/* Original 0x41aaf0: 0x485550 with eax 0x5b9c50. */
uint32_t vertrix_port_screen_present_call(PORT_SIGNATURE);

/* Original 0x475790 (eax = record, dl, ebx, ecx, stack = its fields): fill an input record: the
 * byte +0, dwords +4, +8, +0xc, and clear the word +0x10 and dword +0x14. Registers are
 * unchanged. */
uint32_t vertrix_port_input_record_set(PORT_SIGNATURE);

/* Original 0x4ca180 (eax = address of a string): copy it (0x4ca110) unless its record is the
 * static one (negative count), when it is set to the empty text 0x5c5c00 (0x4ca370). edx is
 * unchanged. */
uint32_t vertrix_port_string_detach(PORT_SIGNATURE);

/* Original 0x4e39d0 (eax = target, edx = source, ebx passed on): copy the source's length
 * (0x4e39f0) plus one bytes (0x4e7b90). Returns the target. */
uint32_t vertrix_port_text_copy(PORT_SIGNATURE);

/* Original 0x486da0 (eax = surface holder): restore its surface (+0x68, the COM method +0x80 with
 * 0), keeping the result at 0x5b9bc8. Returns whether it succeeded. edx is unchanged. */
uint32_t vertrix_port_surface_restore_68(PORT_SIGNATURE);

/* Original 0x485520: as 0x486da0 with the surface +0x6c and the result at 0x5b99c0. */
uint32_t vertrix_port_surface_restore_6c(PORT_SIGNATURE);

/* Original 0x478cd0 (eax = surface, dl = bits per pixel): its pixel format (+0xd): 0 to 4 for 8,
 * 15, 16, 24 and 32 bits, unchanged otherwise. Registers are unchanged. */
uint32_t vertrix_port_surface_set_format(PORT_SIGNATURE);

/* Original 0x41de80: the pause key (0x3b of input 0x54d640, 0x476480 then taken by 0x4762e0)
 * toggles 0x532a08. Returns the new value, or 0 without the key; edx is unchanged. */
uint32_t vertrix_port_pause_toggle(PORT_SIGNATURE);

/* Original 0x4e39a0 (eax = text, edx = byte limit): how many characters (0x4e6f30 bytes each) fit
 * in the limit before the end (0x4e7b50). edx is the bytes left. */
uint32_t vertrix_port_text_characters(PORT_SIGNATURE);

/* Original 0x4e7b90 (eax = target, edx = source, ebx = size): strncpy that drops a split lead byte
 * (the double-byte table 0x5c8961 when 0x5c8950 is set) and clears the rest (0x4eb5c0). Returns
 * the target. */
uint32_t vertrix_port_text_copy_limit(PORT_SIGNATURE);

/* Original 0x4759e0 (eax = owner): destroy every object in its list (+0x20): each one taken
 * (0x4d8540) is deleted through its table's (+0x18) first entry with 2. Registers but eax are
 * unchanged. */
uint32_t vertrix_port_object_list_destroy(PORT_SIGNATURE);

/* Original 0x4b7d10: the frame time: timeGetTime (0x4f172c) kept at 0x5bd838 and 0x5bd844, the
 * milliseconds since the last call (at most 0xffff) at 0x5bd834. Returns them; registers are
 * unchanged. */
uint32_t vertrix_port_frame_time(PORT_SIGNATURE);

/* Original 0x41d670: the frame rate: once a second (0x5bd838 against 0x5329fc) the frames counted
 * at 0x5329f8 become the rate at 0x532a04 and the count restarts. Returns the time; edx is
 * unchanged. */
uint32_t vertrix_port_frame_rate(PORT_SIGNATURE);

/* Original 0x487020 (eax = screen): flip its surface (+0x64, COM method +0x2c with 0 and 1, the
 * result at 0x5b9c4c); a lost surface (0x887601c2) is restored (+0x6c) and flipped again.
 * Returns the last call's result; edx is unchanged. */
uint32_t vertrix_port_surface_flip(PORT_SIGNATURE);

#endif
