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

/* Original 0x48abf0 (eax = table, dl = index, bx = value): store the word at +8 + index * 2. edx
 * is the index. */
uint32_t vertrix_port_word_table_set(PORT_SIGNATURE);

/* Original 0x475810: the field +4. edx is unchanged. */
uint32_t vertrix_port_field_04(PORT_SIGNATURE);

/* Original 0x475820: the field +8. edx is unchanged. */
uint32_t vertrix_port_field_08(PORT_SIGNATURE);

/* Original 0x475830: the field +0xc. edx is unchanged. */
uint32_t vertrix_port_field_0c(PORT_SIGNATURE);

/* Original 0x4757b0: clear the first byte. */
uint32_t vertrix_port_clear_first_byte(PORT_SIGNATURE);

/* Original 0x478d80 (eax = holder): free its buffer (+0, 0x4ea190), then itself. edx is
 * unchanged. */
uint32_t vertrix_port_holder_free(PORT_SIGNATURE);

/* Original 0x476120 (eax = records, dx = index): clear the record of 0x60 bytes (0x4757b0). */
uint32_t vertrix_port_record_clear(PORT_SIGNATURE);

/* Original 0x4ca710 (eax = address of a string): make it its own (0x4ca1a0) and upper-case it
 * (CharUpperA 0x4f1904). edx is unchanged. */
uint32_t vertrix_port_string_upper(PORT_SIGNATURE);

/* Original 0x4b7d70: the milliseconds since the last frame time (timeGetTime 0x4f172c kept at
 * 0x5bd838, against 0x5bd844), 0 when not later. edx is unchanged. */
uint32_t vertrix_port_time_since_frame(PORT_SIGNATURE);

/* Original 0x41a520 (eax = state): after two seconds since the last frame (0x4b7d70) run 0x418830.
 * edx is unchanged. */
uint32_t vertrix_port_idle_check(PORT_SIGNATURE);

/* Original 0x4194b0: unless paused (0x532b40) or the pointer is hidden (0x558958), 0x45fab0 with
 * 0x558c7c. */
uint32_t vertrix_port_cursor_update(PORT_SIGNATURE);

/* Original 0x419490: as 0x4194b0 with 0x45fa70. */
uint32_t vertrix_port_cursor_draw(PORT_SIGNATURE);

/* Original 0x41dec0: inside the input lock (0x5328c0) keep the mouse place (0x478460 of
 * 0x5588f8) and age the keys (0x476400 of 0x54d640 with the frame time 0x5bd834). edx is
 * unchanged. */
uint32_t vertrix_port_input_frame(PORT_SIGNATURE);

/* Original 0x4d93f0 (eax = record): push a record on this thread's chain (its block from 0x4dbf80
 * of 0x5c5c60 for GetCurrentThreadId 0x4f1bbc, SetLastError 0x4f1cb0 restoring the error; the
 * chain at +0x10), clearing its +4. Returns the record; edx is unchanged. */
uint32_t vertrix_port_thread_chain_push(PORT_SIGNATURE);

/* Original 0x4d9430: pop this thread's chain record, running its cleanup (+4, 0x4d9350) first.
 * Returns the next record; edx is the popped one. */
uint32_t vertrix_port_thread_chain_pop(PORT_SIGNATURE);

/* Original 0x4d66cd (eax = flags byte, edx = bit): test and set the bit under the lock 0x50817e
 * (0x4e14b0, 0x4e14b7). Returns 1 when it was already set, else 0. */
uint32_t vertrix_port_flag_test_set(PORT_SIGNATURE);

/* Original 0x48a8a0 (eax = stream): rewind it: its position (+4) to its buffer's start and its end
 * (+8) past the buffer's size. Registers are unchanged. */
uint32_t vertrix_port_stream_rewind(PORT_SIGNATURE);

/* Original 0x48aad0 (eax = stream): its position from the start, kept at 0x5bb250. edx is
 * unchanged. */
uint32_t vertrix_port_stream_tell(PORT_SIGNATURE);

/* Original 0x48aaf0 (eax = stream, edx = offset): seek to the offset from the start. Registers are
 * unchanged. */
uint32_t vertrix_port_stream_seek(PORT_SIGNATURE);

/* Original 0x4d9280 (eax = object): construct a counted object (table 0x517474, count 1) under a
 * guard record. Returns it; edx is unchanged. */
uint32_t vertrix_port_counted_create(PORT_SIGNATURE);

/* Original 0x4182c0: the timer count 0x540044 read inside its lock (0x540020). edx is
 * unchanged. */
uint32_t vertrix_port_timer_count(PORT_SIGNATURE);

/* Original 0x418270 (eax = ticks): add them to the timer count inside its lock, then refresh the
 * screen (0x41a040) of the application's main window (0x4ce740). edx is unchanged. */
uint32_t vertrix_port_timer_advance(PORT_SIGNATURE);

/* Original 0x41a040 (eax = window, edx = force): when the timer count (0x4182c0) changed since
 * 0x54004c or forced, repaint (0x41a2b0 with 0x540048). */
uint32_t vertrix_port_screen_refresh(PORT_SIGNATURE);

/* Original 0x41a2f0 (eax = window, edx = surface, ebx, ecx = scale): blit the screen buffer (+0xd0)
 * scaled by ebx over ecx (0x47ce10, mode 0x1cd). */
uint32_t vertrix_port_screen_blit(PORT_SIGNATURE);

/* Original 0x487750 (eax = table, edx = index, ebx, ecx, stack = values): store the entry's three
 * values in the arrays +0xc, +0x10 and +8. Returns the last slot; edx is the last value. */
uint32_t vertrix_port_triple_set(PORT_SIGNATURE);

/* Original 0x4872f0 (eax = list): initialise it empty with the table 0x516d94. */
uint32_t vertrix_port_list_init_516d94(PORT_SIGNATURE);

/* Original 0x4756d0 (eax = state): initialise an input state with the table 0x5165c4. */
uint32_t vertrix_port_input_state_init(PORT_SIGNATURE);

/* Original 0x4759d0: set the first byte to 1. */
uint32_t vertrix_port_set_first_byte(PORT_SIGNATURE);

/* Original 0x476140 (eax = records, dx = index): set the record's first byte (0x4759d0). */
uint32_t vertrix_port_record_mark(PORT_SIGNATURE);

/* Original 0x475a80 (eax = key record): clear its flag (0x475af0), state (0x475790) and events
 * (0x4759e0). Registers but eax are unchanged. */
uint32_t vertrix_port_key_record_clear(PORT_SIGNATURE);

/* Original 0x48aa70 (eax = holder): its object's (+0) field +4. edx is unchanged. */
uint32_t vertrix_port_object_field4(PORT_SIGNATURE);

/* Original 0x48a2d0: calls 0x4b7b00 with the same registers. */
uint32_t vertrix_port_call_4b7b00(PORT_SIGNATURE);

/* Original 0x487770 (eax = resource, edx = frame): the frame's image (+8 array) when loaded
 * (0x4877e0), else 0. */
uint32_t vertrix_port_resource_frame(PORT_SIGNATURE);

/* Original 0x482bb0 (eax, edx): 0x48a930 with ebx 1 and ecx 2. */
uint32_t vertrix_port_call_48a930(PORT_SIGNATURE);

/* Original 0x4849f0 (eax = dividend, edx = divisor): 16.16 fixed-point division: the dividend
 * shifted up 16 over the divisor. edx is the remainder. */
uint32_t vertrix_port_fixed_divide(PORT_SIGNATURE);

/* Original 0x487850 (eax = holder, edx = index, ebx = value): store the value in its array (+0).
 * Registers are unchanged. */
uint32_t vertrix_port_array_set(PORT_SIGNATURE);

/* Original 0x4b5e70: as 0x4b79a0 (delete an item). */
uint32_t vertrix_port_list_delete_4b5e70(PORT_SIGNATURE);

/* Original 0x4b7cd0: restart the frame time: timeGetTime (0x4f172c) into 0x5bd838 and 0x5bd844.
 * edx is unchanged. */
uint32_t vertrix_port_frame_time_reset(PORT_SIGNATURE);

/* Original 0x45ed10 (eax = name, edx = surface): load the image (0x4877f0 of 0x544a6c), draw it
 * (0x482e10) and release it (0x483ed0 with 0x5b9c60). */
uint32_t vertrix_port_image_show(PORT_SIGNATURE);

/* Original 0x48abe0 (eax = pair, edx, ebx): store edx and ebx. */
uint32_t vertrix_port_pair_set(PORT_SIGNATURE);

/* Original 0x48ab10 (eax = table): initialise a word table: its type 0x5176b4, two cleared fields
 * and 0xff words of -1 from +8. Returns it; edx is unchanged. */
uint32_t vertrix_port_word_table_init(PORT_SIGNATURE);

/* Original 0x4d8620 (eax = size): allocate a block (0x4d85f0) and store the size in its first
 * dword. edx is unchanged. */
uint32_t vertrix_port_block_allocate(PORT_SIGNATURE);

/* Original 0x4b5db0: construct a list (0x4d8650) with the table 0x518344. */
uint32_t vertrix_port_list_construct_518344(PORT_SIGNATURE);

/* Original 0x487640 (eax = array, edx = count): allocate its count of dwords (0x4ec160) and keep
 * the count at +4. */
uint32_t vertrix_port_dword_array_allocate(PORT_SIGNATURE);

/* Original 0x4e5810 (eax = lock): release one level of a counted lock (+0xc); at the last its
 * owner (+8) is cleared and its section (+0) left (LeaveCriticalSection 0x4f1c40). Registers but
 * eax are unchanged. */
uint32_t vertrix_port_counted_unlock(PORT_SIGNATURE);

/* Original 0x4ec1f7 (a jump to 0x4df2e1; eax = node): push the node on the free list 0x50818e
 * under the lock 0x50817e. edx is unchanged. */
uint32_t vertrix_port_free_list_push(PORT_SIGNATURE);

/* Original 0x4ce9fd (eax = object): 0x4ce9c0 when its first field is set. Returns the object. */
uint32_t vertrix_port_object_release_if(PORT_SIGNATURE);

/* Original 0x4eb860 (eax = target, edx = source, ebx = size): strncpy. Returns the target; edx is
 * 0. */
uint32_t vertrix_port_text_copy_padded(PORT_SIGNATURE);

/* Original 0x4dba10 (eax = list, edx = node): push the node, linking it by the list's offset (+4).
 * Registers are unchanged. */
uint32_t vertrix_port_link_push(PORT_SIGNATURE);

/* Original 0x4dea40 (stack = lock number): leave the lock's section (0x18 bytes each from
 * 0x5c79d8) unless locking is off (0x5c79d4). */
uint32_t vertrix_port_lock_leave(PORT_SIGNATURE);

/* Original 0x4d30f0 (eax = value, edx = node): link the node into the application's (0x4ce740)
 * list +0x1c inside lock 0 (0x4de9c0, 0x4dea40). Returns the value. */
uint32_t vertrix_port_application_link(PORT_SIGNATURE);

/* Original 0x4e14b0: the lock routine at 0x509748. */
uint32_t vertrix_port_lock_enter_call(PORT_SIGNATURE);

/* Original 0x4e14b7: the unlock routine at 0x50974c. */
uint32_t vertrix_port_lock_leave_call(PORT_SIGNATURE);

/* Original 0x4ec1a0 (eax = result or 0): time(): the local time (0x4ec850, rounded up from 500
 * milliseconds) as mktime (0x4e7850) gives it, stored at the result when given. edx is unchanged.
 */
uint32_t vertrix_port_time_now(PORT_SIGNATURE);

/* Original 0x4877d0: load (0x4877f0) and, when found, prepare (0x483ce0). */
uint32_t vertrix_port_load_prepare(PORT_SIGNATURE);

/* Original 0x487710 (eax = table, edx = count): allocate its three dword arrays (+8, +0xc, +0x10,
 * 0x4ec160), keep the count (+4) and mark it ready (+0x14). */
uint32_t vertrix_port_triple_allocate(PORT_SIGNATURE);

/* Original 0x4830f0 (eax = holder or 0): free its buffer and itself (0x4ea190). edx is
 * unchanged. */
uint32_t vertrix_port_holder_free_if(PORT_SIGNATURE);

/* Original 0x482750 (eax = generator, edx = low, ebx = high): a random word from low to high
 * (0x4826c0). edx is the low word. */
uint32_t vertrix_port_random_range(PORT_SIGNATURE);

/* Original 0x45e950 (eax = bank, edx = slot, ebx = count): allocate the table of slot +0x1c bytes
 * each in bank +0x118 bytes each from 0x544f90 (0x487710). */
uint32_t vertrix_port_bank_table_allocate(PORT_SIGNATURE);

/* Original 0x4b78d0: construct a list (0x4d8650) with the table 0x518704. */
uint32_t vertrix_port_list_construct_518704(PORT_SIGNATURE);

/* Original 0x489f90: a list from 0x4b78d0 with the field +0x14 set to 0x517644. */
uint32_t vertrix_port_list_construct_517644(PORT_SIGNATURE);

/* Original 0x4dba80 (stack = size): LocalAlloc (0x4f1c4c) of zeroed memory, 0x4d9510 when it
 * fails. */
uint32_t vertrix_port_local_allocate(PORT_SIGNATURE);

/* Original 0x418820 (eax = state, edx): set +0xc0. */
uint32_t vertrix_port_state_set_c0(PORT_SIGNATURE);

/* Original 0x418830 (eax = state): copy +0xc0 to +0xbc. Registers are unchanged. */
uint32_t vertrix_port_state_copy_c0(PORT_SIGNATURE);

/* Original 0x418840 (eax = state, edx): set +0xbc. */
uint32_t vertrix_port_state_set_bc(PORT_SIGNATURE);

/* Original 0x4dc400(stack = handle pointer): close the handle it holds (0x4f17e0) and clear it. */
uint32_t vertrix_port_handle_close_clear(PORT_SIGNATURE);

/* Original 0x4e04f4: does nothing. */
uint32_t vertrix_port_nothing_4e04f4(PORT_SIGNATURE);

/* Original 0x477e10(eax = box, dx, bx, cx, stack): set the words +0x3c, +0x3e, +0x40 and +0x42. edx
 * is the stack word. */
uint32_t vertrix_port_box_set(PORT_SIGNATURE);

/* Original 0x45e8d0(eax = bank, edx = count): allocate the dword list of bank +0x1c bytes each from
 * 0x546458 (0x487640) when count is nonzero. */
uint32_t vertrix_port_bank_list_allocate(PORT_SIGNATURE);

/* Original 0x41d640: take the frame time (0x4b7cd0) as the clock start (0x5329fc), clearing
 * 0x5329f8 and 0x532a04. */
uint32_t vertrix_port_clock_reset(PORT_SIGNATURE);

/* Original 0x4ac950(eax = actor, edx): set +0xb4. */
uint32_t vertrix_port_actor_set_b4(PORT_SIGNATURE);

/* Original 0x4ac940(eax = actor): make +0xf0 its update (+0x154). Registers are unchanged. */
uint32_t vertrix_port_actor_take_f0(PORT_SIGNATURE);

/* Original 0x48d330(eax = set): give it the table 0x517a44 at +0x34 and construct its list
 * (0x48d480). */
uint32_t vertrix_port_rule_set_construct(PORT_SIGNATURE);

/* Original 0x482540(eax = reader): restart at its start (+8 from +0) with +0xc cleared. */
uint32_t vertrix_port_reader_restart(PORT_SIGNATURE);

/* Original 0x40a890(eax = hook): add it to the eight hook slots at 0x52f090. Returns 8 when they
 * are full. */
uint32_t vertrix_port_audio_hook_add(PORT_SIGNATURE);

/* Original 0x48d520: construct a list (0x4d8650) with the table 0x517a94. */
uint32_t vertrix_port_list_construct_517a94(PORT_SIGNATURE);

/* Original 0x476090(eax = records): reset all 256 key records of 0x60 bytes each (0x475a20). */
uint32_t vertrix_port_key_records_reset(PORT_SIGNATURE);

/* Original 0x472330: draw the top layer list 0x54676c (0x4b5fc0). */
uint32_t vertrix_port_layer_top_draw(PORT_SIGNATURE);

/* Original 0x45e530: allocate bank 0x5466a4 (0x487640), load 0x546538 and 0x5449fc (0x4877f0),
 * combine them (0x4831b0) and store it in the bank (0x487850). */
uint32_t vertrix_port_bank_setup_5466a4(PORT_SIGNATURE);

/* Original 0x45e400: create the 160x120 surface 0x544a6c (0x4875a0). */
uint32_t vertrix_port_surface_create_544a6c(PORT_SIGNATURE);

/* Original 0x45e3c0: create the 30x30 surface 0x544d28 (0x4875a0). */
uint32_t vertrix_port_surface_create_544d28(PORT_SIGNATURE);

/* Original 0x4486f0(eax = actor): size it 8x8 from +0x14 and +0x1c, then set its mode (0x4ac7b0),
 * update 0x448790 (0x4ac510) and show it (0x4ac8f0). */
uint32_t vertrix_port_actor_square_setup(PORT_SIGNATURE);

/* Original 0x41ac80(eax = scene): leave it (0x41aa20, 0x41aaa0), read the frame time (0x4b7cd0) and
 * reset 0x5588f8 (0x477d70). */
uint32_t vertrix_port_scene_leave(PORT_SIGNATURE);

/* Original 0x41ab90: hand the rectangle words +0x214..+0x21a and +0x268 of 0x544070 to 0x558c80
 * (0x47ce10). */
uint32_t vertrix_port_view_rect_set(PORT_SIGNATURE);

/* Original 0x41a9e0: close 0x544070 (0x441a80), destroy it through its table (+0x27c) and clear it.
 */
uint32_t vertrix_port_scene_release(PORT_SIGNATURE);

/* Original 0x41a940: set 0x540040 and call 0x41a040. */
uint32_t vertrix_port_scene_flag_enter(PORT_SIGNATURE);

/* Original 0x41a930: clear 0x54004c. */
uint32_t vertrix_port_scene_flag_clear(PORT_SIGNATURE);

/* Original 0x4e2400(eax = block): free the chain of blocks linked through +0 (0x4ca040). */
uint32_t vertrix_port_block_chain_free(PORT_SIGNATURE);

/* Original 0x4d8540(eax = queue): unlink its first node, release it (0x4d84f0) and return the node
 * +8. */
uint32_t vertrix_port_queue_pop(PORT_SIGNATURE);

/* Original 0x4d8510(eax = queue, edx = value): append a node (0x4d8490) holding the value at +8. */
uint32_t vertrix_port_queue_push(PORT_SIGNATURE);

/* Original 0x4d83c0(eax = pool): clear its counters and lists and free its blocks +0x14 (0x4e2400).
 */
uint32_t vertrix_port_pool_reset(PORT_SIGNATURE);

/* Original 0x4872c0(eax = record): look up the cell of +0x3e, +0x40 and +0x10 (0x478d10) and give
 * it the colour byte +0x24. */
uint32_t vertrix_port_cell_colour_set(PORT_SIGNATURE);

/* Original 0x482a60(al = sound): play it (0x482a40) when 0x4829c0 reports it ready. */
uint32_t vertrix_port_sound_play_if_ready(PORT_SIGNATURE);

/* Original 0x482a40(al = sound): play the sample of slot 0x598d88 (0x40adc0). */
uint32_t vertrix_port_sound_play(PORT_SIGNATURE);

/* Original 0x482720(eax = holder): allocate 0x1001 bytes (0x4ec160) into +0 and set the owned flag
 * +4. */
uint32_t vertrix_port_buffer_4k_allocate(PORT_SIGNATURE);

/* Original 0x482480(eax = reader): clear it and give it the table 0x516c24. */
uint32_t vertrix_port_reader_construct(PORT_SIGNATURE);

/* Original 0x476d20(eax = key): clear the 32 slots +0x24 and the dwords +0xa4..+0xb0. Returns key +
 * 0x80. */
uint32_t vertrix_port_key_slots_clear(PORT_SIGNATURE);

/* Original 0x4768e0(eax = key): clear it and give it the table 0x5166d4. */
uint32_t vertrix_port_key_construct(PORT_SIGNATURE);

/* Original 0x476590(eax = keys): reset keys 0x7a and 0x7b (0x476140). */
uint32_t vertrix_port_key_pair_reset(PORT_SIGNATURE);

/* Original 0x4760c0(eax = keys): release all 256 keys (0x476120). */
uint32_t vertrix_port_key_all_release(PORT_SIGNATURE);

/* Original 0x475b00(eax = record): 1 when byte +0x5a is clear. */
uint32_t vertrix_port_record_free_test(PORT_SIGNATURE);

/* Original 0x4757e0(eax = target, edx = source): copy the byte +0 and dwords +4..+0xc. Returns
 * dword +0xc in edx. */
uint32_t vertrix_port_entry_copy(PORT_SIGNATURE);

/* Original 0x473cd0(eax = name): open it in mode 4 with 0x513e60 (0x4cea15). */
uint32_t vertrix_port_stream_open_513e60(PORT_SIGNATURE);

/* Original 0x45ea60(eax = slot, edx = count): allocate bank 0x544d7c + slot * 0x1c (0x487640) when
 * count is nonzero. */
uint32_t vertrix_port_bank_slot_allocate(PORT_SIGNATURE);

/* Original 0x45d140(eax = actor): reset it (0x45cff0), update 0x45d160 (0x4ac510) and show it
 * (0x4ac8f0). */
uint32_t vertrix_port_actor_restart_45d160(PORT_SIGNATURE);

/* Original 0x45d0c0(eax = actor): reset it (0x45cff0), wait 2000 + random(10000) (0x4826c0,
 * 0x4ac7d0), update 0x45d100 (0x4ac510) and show it (0x4ac8f0). */
uint32_t vertrix_port_actor_restart_45d100(PORT_SIGNATURE);

/* Original 0x4ee820: initialise the lock 0x5c8b04 with 0x50c428 (0x4d30f0). */
uint32_t vertrix_port_lock_init_5c8b04(PORT_SIGNATURE);

/* Original 0x4e7520: initialise the lock 0x5c8a84 with 0x50ae38 (0x4d30f0). */
uint32_t vertrix_port_lock_init_5c8a84(PORT_SIGNATURE);

/* Original 0x4ecb98: mark the current handle record (0x507c9c + 0x5c5c54) as text (flag 2 at +4).
 */
uint32_t vertrix_port_handle_mark_text(PORT_SIGNATURE);

/* Original 0x4ecb50(eax = code): map the code (-3 to -1, 0 to -3, 0x3a4 to -4) and set it
 * (0x4e6f60). Returns -1 on failure, 0 on success. */
uint32_t vertrix_port_error_set_code(PORT_SIGNATURE);

/* Original 0x4ec940(eax = stream): reset its state to text mode (0x4ec910 with 0, 0x410). Returns
 * the stream. */
uint32_t vertrix_port_stream_reset_text(PORT_SIGNATURE);

/* Original 0x4ec2b0: set the hook pair 0x509794 to 0x4ec970 and 0x4eca85. */
uint32_t vertrix_port_hooks_set_509794(PORT_SIGNATURE);

/* Original 0x4e8db0: set the hook pair 0x507cdc to 0x4e8d38 and 0x4e8d80. */
uint32_t vertrix_port_hooks_set_507cdc(PORT_SIGNATURE);

/* Original 0x4ea130: returns 0. */
uint32_t vertrix_port_zero_4ea130(PORT_SIGNATURE);

/* Original 0x4ea144: call the hook 0x50b20c. */
uint32_t vertrix_port_hook_call_50b20c(PORT_SIGNATURE);

/* Original 0x4e8620(eax = record): mark it started (+0xc), set it up (0x4e6630) and store the
 * thread id (+0xda). */
uint32_t vertrix_port_thread_record_start(PORT_SIGNATURE);

/* Original 0x4e85c0: under the lock hooks 0x507cc8 and 0x507ccc set byte +0x53 of every record in
 * the list 0x5c8aa0. */
uint32_t vertrix_port_threads_mark_all(PORT_SIGNATURE);

/* Original 0x425f40: does nothing. */
uint32_t vertrix_port_nothing_425f40(PORT_SIGNATURE);

/* Original 0x4e08b0: does nothing. */
uint32_t vertrix_port_nothing_4e08b0(PORT_SIGNATURE);

/* Original 0x40ac00: call the hook 0x52f024. */
uint32_t vertrix_port_hook_call_52f024(PORT_SIGNATURE);

/* Original 0x40ac10: call the hook 0x52f044. */
uint32_t vertrix_port_hook_call_52f044(PORT_SIGNATURE);

/* Original 0x40ac20: call the hook 0x52f048. */
uint32_t vertrix_port_hook_call_52f048(PORT_SIGNATURE);

/* Original 0x40ac30: call the hook 0x52f04c. */
uint32_t vertrix_port_hook_call_52f04c(PORT_SIGNATURE);

/* Original 0x429660(eax): returns eax + 4. */
uint32_t vertrix_port_pointer_add_4(PORT_SIGNATURE);

/* Original 0x477870(eax = object): give it the table 0x5167a4 at +0xc. */
uint32_t vertrix_port_table_set_5167a4(PORT_SIGNATURE);

/* Original 0x484410(eax = object): give it the table 0x516c84 at +4. */
uint32_t vertrix_port_table_set_516c84(PORT_SIGNATURE);

/* Original 0x4ac4f0(eax = actor, edx): set +0x11c. */
uint32_t vertrix_port_actor_set_11c(PORT_SIGNATURE);

/* Original 0x4b7da0: returns 0x5bd83c. */
uint32_t vertrix_port_frame_count_get(PORT_SIGNATURE);

/* Original 0x40cd30(eax): store it in 0x52fc30. Returns 0. */
uint32_t vertrix_port_global_set_52fc30(PORT_SIGNATURE);

/* Original 0x411270(eax): store it in 0x532574. Returns 0. */
uint32_t vertrix_port_global_set_532574(PORT_SIGNATURE);

/* Original 0x4719e0: draw the layer list 0x54671c (0x4b5fc0). */
uint32_t vertrix_port_layer_draw_54671c(PORT_SIGNATURE);

/* Original 0x471a60: clear the layer list 0x54671c (0x4b61c0). */
uint32_t vertrix_port_layer_clear_54671c(PORT_SIGNATURE);

/* Original 0x471af0: clear the layer list 0x546744 (0x4b61c0). */
uint32_t vertrix_port_layer_clear_546744(PORT_SIGNATURE);

/* Original 0x471b70: clear the layer list 0x546730 (0x4b61c0). */
uint32_t vertrix_port_layer_clear_546730(PORT_SIGNATURE);

/* Original 0x4b6ea0: construct a list (0x4d8650) with the table 0x518574. */
uint32_t vertrix_port_list_construct_518574(PORT_SIGNATURE);

/* Original 0x4e04ec: returns 0x5c7b9c. */
uint32_t vertrix_port_global_get_5c7b9c(PORT_SIGNATURE);

/* Original 0x477240(eax = reader): clear +0 and +4 and give it the table 0x516744 at +0x14. */
uint32_t vertrix_port_reader_construct_516744(PORT_SIGNATURE);

/* Original 0x4df307: allocate 0x24 bytes (0x4e62b0) as the handle table 0x5c5c54. */
uint32_t vertrix_port_handle_table_allocate(PORT_SIGNATURE);

/* Original 0x417f40: clear 0x540014. */
uint32_t vertrix_port_global_clear_540014(PORT_SIGNATURE);

/* Original 0x484a60(eax = object): construct its part at +0x10 (0x481b20) and give that the table
 * 0x516d34 at +0x60. */
uint32_t vertrix_port_sound_object_construct(PORT_SIGNATURE);

/* Original 0x4b7b60: construct 0x5bd82c (0x484410) and register its exit routine 0x4ff89b
 * (0x4ec1f7). */
uint32_t vertrix_port_frame_counter_init(PORT_SIGNATURE);

/* Original 0x45e690: allocate bank 0x544a34 with 0x13 entries (0x487640). */
uint32_t vertrix_port_bank_allocate_544a34(PORT_SIGNATURE);

/* Original 0x45ed40: load bank 0x544a88 with 0x50 (0x4876c0). */
uint32_t vertrix_port_bank_load_544a88(PORT_SIGNATURE);

/* Original 0x4719f0(eax = item): add it to the layer list 0x54671c (0x4b6070). */
uint32_t vertrix_port_layer_add_54671c(PORT_SIGNATURE);

/* Original 0x471aa0(eax = item): add it to the layer list 0x546744 (0x4b6070). */
uint32_t vertrix_port_layer_add_546744(PORT_SIGNATURE);

/* Original 0x471b20(eax = item): add it to the layer list 0x546730 (0x4b6070). */
uint32_t vertrix_port_layer_add_546730(PORT_SIGNATURE);

/* Original 0x477910(eax = scale): clear +0 and +4 and set +8 to 0x1800000. */
uint32_t vertrix_port_scale_reset(PORT_SIGNATURE);

/* Original 0x4884f0: initialise the lock 0x5bb228 with 0x4fec10 (0x4d30f0). */
uint32_t vertrix_port_lock_init_5bb228(PORT_SIGNATURE);

/* Original 0x4cbe60: initialise the lock 0x5c5c50 with 0x501368 (0x4d30f0). */
uint32_t vertrix_port_lock_init_5c5c50(PORT_SIGNATURE);

/* Original 0x4d2fe0: initialise the lock 0x5c7560 with 0x502e48 (0x4d30f0). */
uint32_t vertrix_port_lock_init_5c7560(PORT_SIGNATURE);

/* Original 0x4d74f0: initialise the lock 0x5c7600 with 0x503e68 (0x4d30f0). */
uint32_t vertrix_port_lock_init_5c7600(PORT_SIGNATURE);

/* Original 0x4d8320: initialise the lock 0x5c7604 with 0x5041a8 (0x4d30f0). */
uint32_t vertrix_port_lock_init_5c7604(PORT_SIGNATURE);

/* Original 0x4d8630: initialise the lock 0x5c7610 with 0x5044b8 (0x4d30f0). */
uint32_t vertrix_port_lock_init_5c7610(PORT_SIGNATURE);

/* Original 0x4d8a90: initialise the lock 0x5c7614 with 0x5047d8 (0x4d30f0). */
uint32_t vertrix_port_lock_init_5c7614(PORT_SIGNATURE);

/* Original 0x4d9910: initialise the lock 0x5c7750 with 0x5051a8 (0x4d30f0). */
uint32_t vertrix_port_lock_init_5c7750(PORT_SIGNATURE);

/* Original 0x4deea0: initialise the lock 0x5c7b88 with 0x507c08 (0x4d30f0). */
uint32_t vertrix_port_lock_init_5c7b88(PORT_SIGNATURE);

/* Original 0x4e1190: initialise the lock 0x5c81c0 with 0x508158 (0x4d30f0). */
uint32_t vertrix_port_lock_init_5c81c0(PORT_SIGNATURE);

/* Original 0x4e7290: initialise the lock 0x5c8a80 with 0x50ab28 (0x4d30f0). */
uint32_t vertrix_port_lock_init_5c8a80(PORT_SIGNATURE);

/* Original 0x4189f0: clear 0x532a38, then call 0x415580 and 0x413bd0. */
uint32_t vertrix_port_level_restart(PORT_SIGNATURE);

/* Original 0x4ce810: allocate 0x103c bytes (0x4dba80), construct them (0x4ce230 with 1) and give
 * them the table 0x519374. */
uint32_t vertrix_port_file_object_new(PORT_SIGNATURE);

/* Original 0x4ce7c0: allocate 0x114 bytes (0x4dba80) and give them the table 0x519334 with +0xd8
 * and +0x104 at -1. */
uint32_t vertrix_port_stream_object_new(PORT_SIGNATURE);

/* Original 0x41ab00: under the lock 0x5b9c50 (0x4854a0, 0x485520) add 0x558c84 to the layer list
 * 0x54671c (0x4719f0). */
uint32_t vertrix_port_hud_layer_add_54671c(PORT_SIGNATURE);

/* Original 0x41ab30: under the lock 0x5b9c50 (0x4854a0, 0x485520) add 0x558c84 to the layer list
 * 0x546730 (0x471b20). */
uint32_t vertrix_port_hud_layer_add_546730(PORT_SIGNATURE);

/* Original 0x41ab60: under the lock 0x5b9c50 (0x4854a0, 0x485520) add 0x558c84 to the layer list
 * 0x546744 (0x471aa0). */
uint32_t vertrix_port_hud_layer_add_546744(PORT_SIGNATURE);

/* Original 0x475ad0(eax = record, edx, ebx, ecx): mark it busy (+0x5a), restart it from +0x3c and
 * store the three arguments at +0x4c..+0x54. */
uint32_t vertrix_port_record_start(PORT_SIGNATURE);

/* Original 0x4c9daf: free through 0x4db719 when 0x5054a1 is set, otherwise through 0x4c9b6a with
 * ebx 0. */
uint32_t vertrix_port_memory_free_dispatch(PORT_SIGNATURE);

/* Original 0x4c9e00: free through 0x4db7c8 when 0x5054a1 is set, otherwise through 0x4c9b6a with
 * ebx 1. */
uint32_t vertrix_port_memory_free_dispatch_4db7c8(PORT_SIGNATURE);

/* Original 0x43e9e0: initialise 0x541988 with 0x13 and 0x514fb0 (0x4ccf3b) and register its exit
 * routine 0x4fb9ae (0x4ec1f7). */
uint32_t vertrix_port_table_init_541988(PORT_SIGNATURE);

/* Original 0x45c8b0(eax = player): when its target +0x14c is valid (0x471c40), make it the current
 * target 0x532a4c. */
uint32_t vertrix_port_player_target_take(PORT_SIGNATURE);

/* Original 0x48c9f0: under the lock 0x5bb254 (0x47e7d0, 0x47e9b0) run 0x48c970 and 0x48c860 on it.
 */
uint32_t vertrix_port_rules_refresh(PORT_SIGNATURE);

/* Original 0x410f80: 0 when the import 0x4f1740 succeeds, otherwise 5. */
uint32_t vertrix_port_import_check_4f1740(PORT_SIGNATURE);

/* Original 0x478b40: when 0x5589d4 is 1 call 0x40ee60, with eax 0 unless 0x5589dc is also 1. */
uint32_t vertrix_port_input_mode_apply(PORT_SIGNATURE);

/* Original 0x4e62b0(eax = size): under the lock hooks 0x507cc8 and 0x507ccc advance the heap top
 * 0x509768 by size and mark the threads (0x4e85c0). Returns the old top. */
uint32_t vertrix_port_heap_reserve(PORT_SIGNATURE);

/* Original 0x40ae80: when 0x4f6418 is 0xffff add the four audio hooks (0x40a890) and start them
 * (0x40a800); otherwise returns 3. */
uint32_t vertrix_port_audio_hooks_install(PORT_SIGNATURE);

/* Original 0x477af0(eax = holder, bl = flag): store the flag at +8 and +0 = 0, or the result of
 * 0x477b10 when the flag is clear. */
uint32_t vertrix_port_handle_flag_set(PORT_SIGNATURE);

/* Original 0x4856a0(eax = record): look up its cell twice (0x4872c0) into 0x558c80 and 0x558c88,
 * clearing each (0x478f50). Returns 1. */
uint32_t vertrix_port_view_cells_setup(PORT_SIGNATURE);

/* Original 0x4ce0e0: register the exit routines 0x501fc0 and 0x501fd0 (0x4ec1f7). */
uint32_t vertrix_port_exit_register_501fc0(PORT_SIGNATURE);

/* Original 0x4dea80: register the exit routines 0x507250 and 0x507260 (0x4ec1f7). */
uint32_t vertrix_port_exit_register_507250(PORT_SIGNATURE);

/* Original 0x4de5a0: read the metrics into 0x5c7944 (0x4de630) and register the exit routine
 * 0x506c30 (0x4ec1f7). */
uint32_t vertrix_port_metrics_init(PORT_SIGNATURE);

/* Original 0x4760f0(eax = keys): reset all 256 keys (0x476140). */
uint32_t vertrix_port_key_all_reset(PORT_SIGNATURE);

/* Original 0x484b30: 1 when the library 0x50fc31 loads (import 0x4f1c44), releasing it again
 * (import 0x4f1b78); otherwise 0. */
uint32_t vertrix_port_library_probe(PORT_SIGNATURE);

/* Original 0x4772f0(eax = holder, bl = flag): open it (0x477390) unless the flag is set, then mark
 * it open (+0 = 1) with the flag at +4. Returns 1. */
uint32_t vertrix_port_handle_open_flag(PORT_SIGNATURE);

/* Original 0x4cb3d0: clear the stream counters 0x500fbc.. and 0x500ff0.. and initialise the lock
 * 0x5c5c4c with 0x501038 (0x4d30f0). */
uint32_t vertrix_port_stream_tables_reset(PORT_SIGNATURE);

/* Original 0x4cbf90(eax = stream): clear its counters and initialise its critical section +0x54
 * (import 0x4f1970), then set +0x24. */
uint32_t vertrix_port_stream_section_init(PORT_SIGNATURE);

/* Original 0x41a6c0(eax = scene): read the frame time (0x4b7cd0), clear 0x54004c (0x41a930), call
 * 0x418af0, enter with 0x41a700 (0x41a940), set +0xc0 (0x418820) and the update 0x41a520
 * (0x418840). */
uint32_t vertrix_port_scene_enter(PORT_SIGNATURE);

/* Original 0x472ad0(edx = text): allocate a 0x96c byte item (0x4ca000, 0x43e100), fill it
 * (0x43e4d0), give it the width 400 and add it to the layer list 0x546744 (0x4b5e70). */
uint32_t vertrix_port_text_item_add(PORT_SIGNATURE);

/* Original 0x4766b0(eax = records, edx = set): when the set differs from 0x553648 select it, reload
 * 0x55364c (0x4759e0) and refresh all 256 key records (0x475a80). */
uint32_t vertrix_port_key_set_select(PORT_SIGNATURE);

/* Original 0x4ce230(eax = object, dl = mode): clear it, give it the table 0x519344, the sizes 0x14
 * and 0x1c and the mode +0x14. Returns object + 0x1c in edx. */
uint32_t vertrix_port_file_object_construct(PORT_SIGNATURE);

/* Original 0x45c7e0(eax = actor): size it 8x8 from +0x14 and +0x1c, then set its mode (0x4ac7b0),
 * update 0x45c830 (0x4ac510) and show it (0x4ac8f0). */
uint32_t vertrix_port_actor_square_setup_45c830(PORT_SIGNATURE);

/* Original 0x4e587c(eax = record): allocate one (0x4ec160) when it is null, marking it (+0x52) with
 * the heap top +0xf0, then start it (0x4e8620). Returns the record. */
uint32_t vertrix_port_thread_record_ensure(PORT_SIGNATURE);

/* Original 0x405f30(eax = reader): read four bytes (0x405ee0) as a big-endian dword into +0x3664.
 */
uint32_t vertrix_port_reader_dword_be(PORT_SIGNATURE);

/* Original 0x45c760(eax = actor): play sounds 0 and 4 (0x482a60) with the level entry of 0x533164
 * and 0x532b9c, then show the actor (0x4ac8f0). */
uint32_t vertrix_port_actor_sounds_show(PORT_SIGNATURE);

/* Original 0x41a680(eax = scene): reload it (0x41a4e0), apply the setting 0x513c1c (0x41a320,
 * 0x41a440) around 0x41aa20 and set +0xc0 to 0x41a6c0 (0x418820). */
uint32_t vertrix_port_scene_reload(PORT_SIGNATURE);

/* Original 0x471bb0: advance every actor of the list 0x546720 (count 0x546724) to its next update
 * (0x4ac920). */
uint32_t vertrix_port_actors_take_next(PORT_SIGNATURE);

/* Original 0x4828f0(eax = volume): when sound is on (0x598d60) set all eight samples 0x598d88 to
 * the volume (0x40ae00), or to 0 when 0x598da8 is clear. */
uint32_t vertrix_port_sounds_volume_set(PORT_SIGNATURE);

/* Original 0x40a800(eax): clear 0x52f130, mark 0x4f6418 free, clear the 0x80 bytes 0x52f0b0
 * (0x4eb5c0) and copy the tables 0x4f7658 and 0x4f7670 into 0x52f010 and 0x52f028 (0x4eb5e0).
 * Returns eax. */
uint32_t vertrix_port_audio_reset(PORT_SIGNATURE);

/* Original 0x40ab60(eax = device): clear the 0x80 bytes 0x52f0b0 (0x4eb5c0) and open the device
 * through the hook 0x52f03c, storing it in 0x52f130 when that returns 0. */
uint32_t vertrix_port_audio_open(PORT_SIGNATURE);

/* Original 0x4779c0(eax = box): clear it, set +0x44 to 200 and give it the table 0x516804 at +0x74.
 */
uint32_t vertrix_port_box_construct(PORT_SIGNATURE);

/* Original 0x4e579c: leave the lock 0x5c8920: drop its count +0xc and, at zero, clear the owner +8
 * and release its semaphore +0 (import 0x4f1c40). */
uint32_t vertrix_port_lock_leave_5c8920(PORT_SIGNATURE);

/* Original 0x4784d0(eax = box, dx = key): press the key in 0x54d640 (0x4761d0) at the box position
 * +0x48, +0x4a, or at 0x7d00 when +0x60 is set. */
uint32_t vertrix_port_box_key_press(PORT_SIGNATURE);

/* Original 0x478520(eax = box, dx = key): release the key in 0x54d640 (0x476280) at the box
 * position +0x48, +0x4a, or at 0x7d00 when +0x60 is set. */
uint32_t vertrix_port_box_key_release(PORT_SIGNATURE);

/* Original 0x40ee60(eax = channels): when the device flags 0x531b44 have 0x80 store up to 64
 * channels in 0x531b68 and flag 0x10 unless 0x20 is set. Returns 0, 2 for too many or 3 without a
 * device. */
uint32_t vertrix_port_audio_channels_set(PORT_SIGNATURE);

/* Original 0x40c8d0(eax = count): for 1 to 32 store it in 0x52fc18 and set the enable byte of that
 * many 0x18 byte voices at 0x52f92e. Returns 0, or 2 for a bad count. */
uint32_t vertrix_port_voices_enable(PORT_SIGNATURE);

/* Original 0x459760(eax = actor): step it (0x4ac500); when its frame is due (0x4ac520) advance it
 * (0x4ac540, 0x4ac5b0) and show it (0x4ac8f0) unless it ended (0x4ad6e0). */
uint32_t vertrix_port_actor_animate(PORT_SIGNATURE);

/* Original 0x48d480(eax = rule): clear its 16 bytes and the dwords +0x10..+0x30. */
uint32_t vertrix_port_rule_clear(PORT_SIGNATURE);

/* Original 0x40af30: install the audio hooks (0x40ae80), clear 0x52f148 and 0x52f14c and start the
 * audio thread 0x40aed0 (import 0x4f1b38) into 0x52f140, raising its priority (imports 0x4f1cb4 and
 * 0x4f1cbc). */
uint32_t vertrix_port_audio_thread_start(PORT_SIGNATURE);

/* Original 0x45ec00: create the screen-sized surface 0x544bf4 from 0x4f90b0, 0x4f90b8 and 0x4f90bc
 * (0x4875a0). */
uint32_t vertrix_port_surface_create_544bf4(PORT_SIGNATURE);

/* Original 0x48a620(eax = record): clear it, give it the table 0x517684 at +0x110 and copy the
 * default name 0x510a5a to +0xc. */
uint32_t vertrix_port_name_record_construct(PORT_SIGNATURE);

/* Original 0x4cb460(eax = stream): give it the table 0x518cb4 with +4 and +0x14 set and the rest
 * clear. */
uint32_t vertrix_port_stream_base_construct(PORT_SIGNATURE);

/* Original 0x4deec0(eax = object, edx = code): give it the table 0x51bb54, the kind 0x11 at +8 and
 * the code at +0x18. */
uint32_t vertrix_port_error_object_construct(PORT_SIGNATURE);

/* Original 0x41aaa0: under the lock 0x5b9c50 (0x4854a0, 0x485520) hand the size +4, +8 of 0x558c84
 * to 0x558c88 (0x47ce10). */
uint32_t vertrix_port_view_size_set(PORT_SIGNATURE);

/* Original 0x45f590(eax = name): 1 when the archive 0x5466c8 holds it (0x487fd0) or, without an
 * archive, when the file exists (0x4895e0). */
uint32_t vertrix_port_file_exists(PORT_SIGNATURE);

/* Original 0x472360: 1 when no actor of the list 0x546770 (count 0x546774) is busy (0x4ac900),
 * otherwise 0. */
uint32_t vertrix_port_actors_all_idle(PORT_SIGNATURE);

/* Original 0x4771e0: construct 0x55608c (0x477240) and register its exit routine 0x4fea9d
 * (0x4ec1f7). Returns the handler chain. */
uint32_t vertrix_port_static_init_55608c(PORT_SIGNATURE);

/* Original 0x477810: construct 0x5560bc (0x477870) and register its exit routine 0x4feac9
 * (0x4ec1f7). Returns the handler chain. */
uint32_t vertrix_port_static_init_5560bc(PORT_SIGNATURE);

/* Original 0x477960: construct 0x5588f8 (0x4779c0) and register its exit routine 0x4feae4
 * (0x4ec1f7). Returns the handler chain. */
uint32_t vertrix_port_static_init_5588f8(PORT_SIGNATURE);

/* Original 0x484a00: construct 0x5b9c50 (0x484a60) and register its exit routine 0x4feb7c
 * (0x4ec1f7). Returns the handler chain. */
uint32_t vertrix_port_static_init_5b9c50(PORT_SIGNATURE);

/* Original 0x4799f0(eax = image, edx = key colour): make the key colour transparent and every other
 * pixel opaque, counting them into 0x558a4c and leaving the end in 0x558a44. */
uint32_t vertrix_port_image_alpha_key(PORT_SIGNATURE);

/* Original 0x482b40(al = sound): when sound is on (0x598d60) and the sound is playing (0x598d68)
 * stop its sample (0x40add0) if 0x4828a0 allows it, then clear its playing flag. */
uint32_t vertrix_port_sound_stop(PORT_SIGNATURE);

/* Original 0x492710: run the row hook 0x5bb72c for every row counted down in 0x5bc016, stepping the
 * row pointer 0x5bb7dc and the offsets 0x5bb764 and 0x5bb768. */
uint32_t vertrix_port_music_rows_play(PORT_SIGNATURE);

/* Original 0x4b61c0(eax = list): call method +0x18 of the table +0x158 of every item. */
uint32_t vertrix_port_layer_list_clear(PORT_SIGNATURE);

/* Original 0x4d8340(eax = pool, edx = size): give it the table 0x51a024 and the block size +0x18,
 * clearing the rest. */
uint32_t vertrix_port_pool_construct(PORT_SIGNATURE);

/* Original 0x40cd40(eax = tempo): for 32 to 255 set the samples per tick 0x52fc24 from the rate
 * 0x52fc20 (doubled when 0x52fc1d bit 0 is set) as rate * 5 / (tempo * 2). Returns 0, or 2 for a
 * bad tempo. */
uint32_t vertrix_port_audio_tempo_set(PORT_SIGNATURE);

/* Original 0x417fc0(eax = level, edx = value): count the 0x4c byte entries of the level (count
 * 0x534f10) whose dword at 0x534c18 equals the value. Returns the end offset in edx. */
uint32_t vertrix_port_level_count_matches(PORT_SIGNATURE);

/* Original 0x4e58b8: when 0x507c98 is unset read the mode (import 0x4f1cd4), rereading it while
 * 0x509731 and 0x50972f allow and it stays 0 to 2. Stores it in 0x507c98 and returns 1 unless it is
 * -1. */
uint32_t vertrix_port_console_mode_probe(PORT_SIGNATURE);

/* Original 0x4d7510(eax = object): construct its lock +0xc (0x4ca070), give it the table 0x519f14
 * with no handle (+4 = -1) and set the lock up (0x4ca180). */
uint32_t vertrix_port_event_object_construct(PORT_SIGNATURE);

/* Original 0x40ac50(eax = sample): allocate its data (0x4e7c90, size +8 + 4) into +0 and load it
 * through the hook 0x52f054, freeing it (0x4ea190) when that fails. Returns 0, 2 for no sample, 8
 * for no memory or the hook error. */
uint32_t vertrix_port_sample_load(PORT_SIGNATURE);

/* Original 0x411bf0: construct 0x5327f0 (0x411c70), register its exit routine 0x4f7700 (0x4ec1f7)
 * and clear 0x53291c..0x532924. Returns the handler chain. */
uint32_t vertrix_port_static_init_5327f0(PORT_SIGNATURE);

/* Original 0x423d70(eax = name): load it as a 0x50de07 object (0x473f10) or a 0x50de0c object
 * (0x48ac50) by its extension (0x489b40). Returns the object or 0. */
uint32_t vertrix_port_script_object_load(PORT_SIGNATURE);

/* Original 0x478ae0: when audio is open (0x5589d4) stop and release the eight sounds when sound is
 * on (0x482b40, 0x40ad50), then close the device (0x40ed70, 0x40aba0, 0x40ef90 with 0x5589d8). */
uint32_t vertrix_port_audio_shutdown(PORT_SIGNATURE);

/* Original 0x482930: when sound is on (0x598d60) give the eight samples 0x598d88 their default pans
 * (0x40ae10). */
uint32_t vertrix_port_sounds_pan_default(PORT_SIGNATURE);

/* Original 0x4d7bb0(eax = stream): seek to the end through method +0x30 to read the length, then
 * back to where it was. */
uint32_t vertrix_port_stream_length(PORT_SIGNATURE);

/* Original 0x457550(eax = actor): step it (0x4ac500); when its frame is due (0x4ac520) advance it
 * (0x4ac540, 0x4ac5b0) and, at the end (0x4acc10), drop it at speed (-150, 10) with the update
 * 0x4575b0 (0x4ac8f0). Then move it (0x4ac8a0). */
uint32_t vertrix_port_actor_animate_drop(PORT_SIGNATURE);

/* Original 0x45e6b0: allocate bank 0x544a50 with 19 entries (0x487640) and fill each with entry i
 * of 0x544a34 combined with 0x546538 (0x4877f0, 0x4831b0, 0x487850), reporting progress (0x418270).
 */
uint32_t vertrix_port_bank_build_544a50(PORT_SIGNATURE);

/* Original 0x475660: construct 0x54d640 (0x475ec0) and 0x55364c (0x475840), registering their exit
 * routines 0x4fd6e0 and 0x4fd6f0 (0x4ec1f7). Returns the handler chain. */
uint32_t vertrix_port_static_init_54d640(PORT_SIGNATURE);

/* Original 0x476870: construct the keys 0x5536c8 and 0x553798 (0x4768e0), registering their exit
 * routines 0x4fea6d and 0x4fea7d (0x4ec1f7). Returns the handler chain. */
uint32_t vertrix_port_static_init_5536c8(PORT_SIGNATURE);

/* Original 0x482410: construct the readers 0x598d30 and 0x598d48 (0x482480), registering their exit
 * routines 0x4feb43 and 0x4feb53 (0x4ec1f7). Returns the handler chain. */
uint32_t vertrix_port_static_init_598d30(PORT_SIGNATURE);

/* Original 0x476a00(eax = key, bl = flag, ecx = layout): store the layout at +0xb4, the flag at +8
 * and +0 (0 or 0x476aa0 when the flag is clear), and set the five key codes +0xb8..+0xc8 for layout
 * 0 or 1. Returns the layout in edx. */
uint32_t vertrix_port_key_layout_set(PORT_SIGNATURE);

/* Original 0x483750(eax = image): for a 4 byte per pixel image (+0x27) make transparent pixels
 * opaque and the rest transparent. Returns the end of the pixels. */
uint32_t vertrix_port_image_alpha_invert(PORT_SIGNATURE);

/* Original 0x4845d0(eax = value): look the value up in the table 0x59993c, mirrored to 180 - entry
 * for negative values. Out of range gives 0 or 180. */
uint32_t vertrix_port_angle_lookup(PORT_SIGNATURE);

/* Original 0x45f620: construct the six layer lists 0x54671c..0x546780 (0x4b5db0), registering their
 * exit routines 0x4fd430..0x4fd480 (0x4ec1f7), and copy the four bytes 0x4f9c06 to 0x546830. */
uint32_t vertrix_port_layer_lists_init(PORT_SIGNATURE);

/* Original 0x48a8c0(eax = record): release its object +0 (0x478d80), clear it and copy the default
 * name 0x510ac1 to +0xc. */
uint32_t vertrix_port_name_record_reset(PORT_SIGNATURE);

/* Original 0x4cf3a0(eax = stream, edx = owner): construct the base (0x4cb460), give it the table
 * 0x519664, clear the 0x20 bytes +0x1c (0x4eb5c0) and store the owner at +0x1c. */
uint32_t vertrix_port_memory_stream_construct(PORT_SIGNATURE);

/* Original 0x40cb10(eax = voice, edx = rate): for a voice below 0x52fc18 and a rate of 0x200 to
 * 0x80000 store the step (rate << 12) / 0x52fc20, rounded, in the voice +0x52f920. Returns 0, 1 for
 * a bad voice or 2 for a bad rate. */
uint32_t vertrix_port_voice_rate_set(PORT_SIGNATURE);

/* Original 0x4b6070(eax = list, edx = argument): call method +8 of the table +0x158 of every item
 * with the argument. Returns the count in edx. */
uint32_t vertrix_port_layer_list_call(PORT_SIGNATURE);

/* Original 0x40acf0(eax = slot pointer): take the first free one of the 0x52f130 sample slots
 * 0x52f0b0, storing its number (from 1). Returns 0, 2 for no pointer or 8 when all are taken. */
uint32_t vertrix_port_sample_slot_take(PORT_SIGNATURE);

/* Original 0x45cdd0(eax = actor): reset it (0x45cdc0) and wait a random time (0x4826c0 on 0x598d30,
 * 0x4ac7d0): 3000 + random(5000) with a random 50 + random(50) +0xd0 (0x4ac490) when +0x58 is 1,
 * otherwise 1000 + random(5000). Then update 0x45ce50 (0x4ac8f0). */
uint32_t vertrix_port_actor_respawn_wait(PORT_SIGNATURE);

/* Original 0x4aca60(eax = actor, edx = steps): move the x word +0xe towards +0x10 by steps * speed
 * +0x12, not past it. 1 while it has not arrived; the target word in dx. */
uint32_t vertrix_port_actor_approach_x(PORT_SIGNATURE);

/* Original 0x4acab0(eax = actor, edx = steps): move the y word +0x16 towards +0x18 by steps * speed
 * +0x1a, not past it. 1 while it has not arrived; the target word in dx. */
uint32_t vertrix_port_actor_approach_y(PORT_SIGNATURE);

/* Original 0x4acb00(eax = actor, edx = steps): move the word +0x1e towards +0x20 by steps * speed
 * +0x22, not past it. 1 while it has not arrived; the target word in dx. */
uint32_t vertrix_port_actor_approach_z(PORT_SIGNATURE);

/* Original 0x41b680(eax = scene): construct it (0x41b310), set +0xc8, the update 0x4237d0
 * (0x418840) and +0xc0 = 0x41b820 (0x418820). Returns the handler chain. */
uint32_t vertrix_port_scene_title_construct(PORT_SIGNATURE);

/* Original 0x475c30(eax = key): clear its entry +4 (0x475790), then take the next queued entry from
 * +0x20 (0x4d8540), copy it in (0x4757e0) and release it through its table +0x18. */
uint32_t vertrix_port_key_queue_next(PORT_SIGNATURE);

/* Original 0x4e8510(eax = thread, edx = record): under the lock hooks 0x507cc8 and 0x507ccc link a
 * 0x10 byte node (0x4ec160) for them into 0x5c8aa0, unless 0x4ea144 refuses (then free it,
 * 0x4ea190). Returns 1 when linked. */
uint32_t vertrix_port_thread_list_add(PORT_SIGNATURE);

/* Original 0x4de900(eax = metrics): read the screen size (import 0x4f19e4) into +8 and +0xc, the
 * extra metrics (0x4de5c0 or 0x4de600 by +0x88) and the pixels per inch (imports 0x4f1974,
 * 0x4f1808, 0x4f1a78) into +0x18 and +0x1c. */
uint32_t vertrix_port_screen_metrics_read(PORT_SIGNATURE);

/* Original 0x484550: load the tables 0x50fc16, 0x50fc1e and 0x50fc26 into 0x598dfc, 0x59939c and
 * 0x59993c (0x4848f0). Returns the handler chain. */
uint32_t vertrix_port_tables_load(PORT_SIGNATURE);

/* Original 0x4e39f0(eax = text, edx = count): the width of the first count characters, stopping at
 * the end (0x4e7b50); a lead byte of a double byte character (0x5c8961 with 0x5c8950 set) adds
 * 0x4e6f30, others 1. Steps with 0x4e3a90. */
uint32_t vertrix_port_text_width_chars(PORT_SIGNATURE);

/* Original 0x4154b0: once (0x532b40) take the player key 0x532b90 from 0x54d640 when it is down
 * (0x476480, 0x4762e0), play its sound (0x482a60) and mark it taken (0x532b40, 0x532b48, clearing
 * 0x532b44). */
uint32_t vertrix_port_player_key_pickup(PORT_SIGNATURE);

/* Original 0x418050(eax = level): count the 0x4c byte entries of the level (count 0x534f10) whose
 * dword at 0x534c18 is 0, 3, 4 or 5. */
uint32_t vertrix_port_level_count_free(PORT_SIGNATURE);

/* Original 0x45f1f0(eax = target): draw the eight digit images of 0x544d28 (0x4877f0, 0x482e10)
 * into 0x5b9c60 at 31 pixel steps (0x483ed0). */
uint32_t vertrix_port_digits_draw(PORT_SIGNATURE);

/* Original 0x471c40(eax = target): 0 when an actor of the list 0x546720 (count 0x546724) with
 * another target +0x14c is busy (0x4ac900), otherwise 1. */
uint32_t vertrix_port_actors_target_idle(PORT_SIGNATURE);

/* Original 0x43f190(eax = first, edx = source, ebx = count, ecx): prepare count images of 0x5410f8
 * from the source index (0x483400) into the slots from first + 1, reporting progress (0x418270).
 * Returns the count in edx. */
uint32_t vertrix_port_images_prepare(PORT_SIGNATURE);

/* Original 0x489b40(eax = path, edx = extension): split a copy of the path at 0x5ba5f8 (0x4daae8)
 * and compare its extension 0x5ba908 (0x489d00). */
uint32_t vertrix_port_file_extension_is(PORT_SIGNATURE);

/* Original 0x41aa20: when 0x558c84 and 0x544070 are set, under the lock 0x5b9c50 (0x4854a0,
 * 0x485520) hand the rectangle words +0x214..+0x21a and +0x268 of 0x544070 to 0x558c84 (0x47ce10).
 */
uint32_t vertrix_port_view_rect_set_locked(PORT_SIGNATURE);

/* Original 0x472100: allocate a 0x15c byte actor (0x4ca000, 0x4abd70), place it (0x4adf20), set its
 * kind 7 and mode 1 (0x4ac7b0), the update 0x456ea0 (0x4ac8f0), clear 0x4ac910 and add it to the
 * layer list 0x54676c (0x4b5e70). */
uint32_t vertrix_port_marker_actor_add(PORT_SIGNATURE);

/* Original 0x478b70(eax = fade): fill its +0x26 ramp bytes +0x130 from 0 to 255 in 256 / (count -
 * 1) steps, or all 0x80 for one. */
uint32_t vertrix_port_fade_ramp_build(PORT_SIGNATURE);

/* Original 0x4b5fc0(eax = list): destroy every item through method +0 of its table +0x158 (with 2),
 * then free the list (0x4d8770). */
uint32_t vertrix_port_layer_list_destroy(PORT_SIGNATURE);

/* Original 0x4b7b00(eax = list): destroy every item through method +4 of its table (with 2), then
 * free the list (0x4d8770). */
uint32_t vertrix_port_object_list_free(PORT_SIGNATURE);

/* Original 0x4d8490(eax = pool, edx = value, ebx = next): take a node from the free list +0x10,
 * growing it by a block of +0x18 nodes of 12 bytes (0x4e23e0) when empty, and fill it with next,
 * value and 0. */
uint32_t vertrix_port_pool_node_take(PORT_SIGNATURE);

/* Original 0x45ceb0(eax = actor): reset it (0x45cdc0, keeping +0xb8); while it is busy (0x4ac250)
 * stop and move it (0x4adfe0, 0x4ac8a0) once +0xb8 changed, otherwise stop it, move it by 1000 and
 * wait 100 + random(edx) (0x4826c0, 0x4ac7d0) with the update 0x45cf30 (0x4ac8f0). */
uint32_t vertrix_port_actor_wander_45cf30(PORT_SIGNATURE);

/* Original 0x45f540(eax = target, edx = first, ebx = second): copy the first string to the target
 * and append the second. */
uint32_t vertrix_port_path_join(PORT_SIGNATURE);

/* Original 0x45e490: allocate banks 0x546618 and 0x546634 (0x487640), each holding 0x5449fc entry
 * 0x4fbfac combined with 0x546538 entry 9 (0x4877f0, 0x4831b0, 0x487850). */
uint32_t vertrix_port_banks_setup_546618(PORT_SIGNATURE);

/* Original 0x4765b0(eax = keys): release keys 0x74, 0x75 and 0xbe..0xc3 (0x476120) and reset keys
 * 0x70..0x73 (0x476140). */
uint32_t vertrix_port_keys_release_group(PORT_SIGNATURE);

/* Original 0x4876c0(eax = bank, edx = argument): call 0x483790 on every image of the bank with the
 * argument. Returns the count, with the last image or 0x483790 edx in edx. */
uint32_t vertrix_port_bank_images_apply(PORT_SIGNATURE);

/* Original 0x41a700(eax = scene): reload it (0x41a4e0), apply the setting 0x513c1d (0x41a320,
 * 0x41a440) around 0x41aa20 and set +0xc0 to 0x41a780 (0x418820). Returns the handler chain. */
uint32_t vertrix_port_scene_reload_513c1d(PORT_SIGNATURE);

/* Original 0x456ea0(eax = actor): step it (0x4ac500); when its frame is due (0x4ac520) advance it
 * (0x4ac540, 0x4ac5b0), set the speed +0x5c to two thirds of 0x5b9c8e and +0x60 to 4, and show it
 * (0x4ac8f0) unless it ended (0x4ad6e0). */
uint32_t vertrix_port_actor_animate_slide(PORT_SIGNATURE);

/* Original 0x4724f0: allocate a 0x15c byte actor (0x4ca000, 0x4abd70), place it (0x4adf20), set its
 * kind 8, wait 10 (0x4ac7d0), speed 100 at +0x5c with +0x60 = 1, the update 0x459760 (0x4ac8f0),
 * clear 0x4ac910 and add it to the layer list 0x54676c (0x4b5e70). */
uint32_t vertrix_port_sparkle_actor_add(PORT_SIGNATURE);

/* Original 0x478d10(eax = width, edx = height, bl = bytes per pixel): allocate a 0x1c byte image
 * (0x4ec160) with its pixels, set its depth (0x478cd0) and pitch +0x14 and clear it (0x478da0). */
uint32_t vertrix_port_image_create(PORT_SIGNATURE);

/* Original 0x40ce20(eax = value): for a positive value the period: 0x4f6584[value % 768] >> (value
 * / 768) in linear mode (0x531b46 bit 0), otherwise 0xda7790 / value. 0 for the rest. */
uint32_t vertrix_port_audio_period_from(PORT_SIGNATURE);

/* Original 0x4acc10(eax = actor, edx = steps): move the byte +0x44 towards +0x45 by steps times the
 * speed +0x46, not past it. 1 while it has not arrived. */
uint32_t vertrix_port_actor_fade_approach(PORT_SIGNATURE);

/* Original 0x48b4a0: construct 0x5bb254 (0x48b550) and the rule sets 0x5bb4ec..0x5bb594 (0x48d330),
 * registering their exit routines 0x4feca0..0x4fece0 (0x4ec1f7). Returns the handler chain. */
uint32_t vertrix_port_static_init_5bb254(PORT_SIGNATURE);

/* Original 0x4ce7a0: allocate 0x84 bytes (0x4dba80) and construct the buffered file in them: two
 * error objects (0x4deec0), a pool of 10 (0x4d8340) and the table 0x519364. */
uint32_t vertrix_port_file_buffer_new(PORT_SIGNATURE);

/* Original 0x4180a0(eax = level, edx = n): the index of the n-th entry of the level (count
 * 0x534f10) whose dword at 0x534c18 is 0, 3, 4 or 5, or 0. Returns the index reached in edx. */
uint32_t vertrix_port_level_free_index(PORT_SIGNATURE);

/* Original 0x418a10(eax = game): load the game in steps reported to 0x418270, running 0x475090,
 * 0x417c80, 0x425f40, 0x4b9050, 0x484550, 0x480730 and 0x478860 only while +0xd8 is clear, then
 * read the frame time (0x4b7cd0, 0x4b7c00). */
uint32_t vertrix_port_game_load_all(PORT_SIGNATURE);

/* Original 0x40a8f0(eax = driver, edx = info): clear the 0x24 byte info (0x4eb5c0) and fill it
 * through the first or second routine of driver slot 0x52f090. Returns 2 without info, 4 without a
 * driver. */
uint32_t vertrix_port_audio_driver_info(PORT_SIGNATURE);

/* Original 0x45cf70(eax = actor): reset it (0x45cdc0, keeping +0xb8) and stop it (0x4adfe0); while
 * it is busy (0x4ac2b0) stop and move it (0x4adfe0, 0x4ac8a0) once +0xb8 changed, otherwise clear
 * 0x4ac710, move it by +0x58 (0x4ac8a0) or reset 0x4ac950 and 0x4ac8d0 without, and restart with
 * 0x45cdd0 (0x4adfe0, 0x4ac8f0). */
uint32_t vertrix_port_actor_wander_45cdd0(PORT_SIGNATURE);

/* Original 0x4b7710(eax = list, edx = string, ebx = index): set the string to 0x5110ca (0x4ca280),
 * then to entry index of the list when it has one (0x4ca310). Returns the string. */
uint32_t vertrix_port_string_list_get(PORT_SIGNATURE);

/* Original 0x414a90: for each of the 19 levels store the offsets of its 0x53969c entries from the
 * origin 0x534888, 0x5348d4 into 0x5372fc and 0x5384cc when both are not negative. */
uint32_t vertrix_port_level_offsets_534888(PORT_SIGNATURE);

/* Original 0x414b10: for each of the 5 groups store the offsets of its 0x54021c entries from the
 * origin 0x540064, 0x540078 into 0x540154 and 0x5401b8 when both are not negative. */
uint32_t vertrix_port_level_offsets_540064(PORT_SIGNATURE);

/* Original 0x41a800(eax = scene): reload it (0x41a4e0), release its images +0xcc and +0xd0
 * (0x478d80), leave the critical section 0x540020 (import 0x4f1b3c), clear +0xd4, refresh the view
 * (0x4b7cd0, 0x41aa20, 0x41aaa0), refresh the rules with 0x41b680 (0x48c9f0) and update it
 * (0x418840). Returns the handler chain. */
uint32_t vertrix_port_scene_leave_game(PORT_SIGNATURE);

/* Original 0x417c80: expand the 0x34 group sizes 0x4f90c0 into the level numbers 0x53bb18 (8 per
 * group) and sum the 7 section counts 0x4f90f8 of those sizes into 0x53bcc0. */
uint32_t vertrix_port_level_tables_build(PORT_SIGNATURE);

/* Original 0x4413b0(eax = hud): construct its three layer lists +0x22c, +0x240 and +0x254
 * (0x4b5db0) and give it the table 0x5150f4 at +0x27c. Returns the hud. */
uint32_t vertrix_port_hud_construct(PORT_SIGNATURE);

/* Original 0x441a80(eax = hud): release its images +0x268, +0x274, +0x278, +0x270 (when +0x220 is
 * 1) and +0x26c (when +0x222 is 1) through 0x478d80 and clear them. */
uint32_t vertrix_port_hud_images_release(PORT_SIGNATURE);

/* Original 0x4ac250(eax = actor): 0 when one of its remaining frames (0x4ac390, 0x4ac3b0, 0x4ac420)
 * is busy (0x4ac780), stepping with 0x4ac740; otherwise 1. */
uint32_t vertrix_port_actor_frames_busy(PORT_SIGNATURE);

/* Original 0x4ac2b0(eax = actor): 0 when one of its remaining frames (0x4ac390, 0x4ac3b0, 0x4ac420)
 * is busy (0x4ac7a0), stepping with 0x4ac750; otherwise 1. */
uint32_t vertrix_port_actor_frames_busy_4ac7a0(PORT_SIGNATURE);

/* Original 0x41dd60(eax = scene): when the player key 0x532b94 of 0x54d640 is down (0x476480) take
 * it (0x4762e0) and act on it (0x4192a0). Returns the handler chain. */
uint32_t vertrix_port_player_key_use(PORT_SIGNATURE);

/* Original 0x41ddf0(eax = scene): when the player key 0x532b94 of 0x54d640 is down (0x476480) take
 * it (0x4762e0) and act on it (0x4193b0). Returns the handler chain. */
uint32_t vertrix_port_player_key_use_4193b0(PORT_SIGNATURE);

/* Original 0x45ec50(eax = target): draw the 0x4f90b0 tiles of 0x544bf4 (0x4877f0, 0x482e10) into
 * 0x5b9c60 (0x483ed0) on a grid 0x4f90b4 wide with cells of 0x4f90b8 by 0x4f90bc plus one. */
uint32_t vertrix_port_tiles_draw(PORT_SIGNATURE);

/* Original 0x4ca7b0: set up the stream type tables 0x500b80, 0x500ba0 and 0x500bc0 with their
 * copies at 0x5c5c0c and 0x5c5c18, initialise the lock 0x5c5c24 with 0x500bec (0x4d30f0) and
 * register the exit routine 0x500820 (0x4ec1f7). */
uint32_t vertrix_port_stream_types_init(PORT_SIGNATURE);

/* Original 0x4e55d4: take the next of the 64 lock records 0x5c8310, or allocate one (0x4ec160) and
 * add it to the list 0x5c8948 (0x4ec0e0, failing through 0x4e628c), then initialise its critical
 * section (import 0x4f1c30). */
uint32_t vertrix_port_lock_record_new(PORT_SIGNATURE);

/* Original 0x43e100(eax = hud): construct the actor base (0x4abd70), give it the table 0x514e94 and
 * clear its 0x1c2 item slots +0x15c, 3 dwords +0x864 and 1 at +0x870 (0x4b2290), then set +0x968.
 * Returns the hud. */
uint32_t vertrix_port_hud_object_construct(PORT_SIGNATURE);

/* Original 0x4574a0(eax = actor): clear +0x4e and step it (0x4ac500); when its frame is due
 * (0x4ac520) advance it (0x4ac540, 0x4ac5b0) and, at the end (0x4ad6e0), start the drop: +0x58 = 0,
 * +0x5c = +0x64 + random(+0x70) (0x4826c0), 0x43e920, the fade bytes and words, +0x4e = 50 and the
 * update 0x457550 (0x4ac8f0). Then move it (0x4ac8a0). */
uint32_t vertrix_port_actor_drop_start(PORT_SIGNATURE);

/* Original 0x4e3f70: set the mode bits of 0x505275 and link a 0x1d byte buffer (0x4e7c90, failing
 * through 0x4e628c) for each 0x1a byte stream record from 0x505234 into the list 0x5c7760, then
 * clear 0x5c7764. */
uint32_t vertrix_port_file_streams_init(PORT_SIGNATURE);

/* Original 0x411c70(eax = game): construct the base (0x4ca970), give it the table 0x5131c4, start
 * the audio thread (0x40af30), reset the scale 0x5560bc (0x477910), call 0x45f3f0 and initialise
 * the critical sections 0x5328c0, 0x5328d8 and 0x5328f0 (import 0x4f1c30). Returns the game. */
uint32_t vertrix_port_game_object_construct(PORT_SIGNATURE);

/* Original 0x40c9d0(eax = voice, edx = sample): for a voice below 0x52fc18 and a sample with data
 * +4 set the voice +0x52f918 to play it: start 0, loop or length from the sample flags +0x16,
 * halved for 16 bit, all in 20.12 fixed point. Returns 0, or 1 when refused. */
uint32_t vertrix_port_voice_sample_set(PORT_SIGNATURE);

/* Original 0x448790(eax = actor): set mode 1 (0x4ac7b0) and step it (0x4ac500); when its frame is
 * due (0x4ac520) advance it (0x4ac540, 0x4ac5b0) and move it on all three axes (0x4aca60, 0x4acab0,
 * 0x4acb00), showing it (0x4ac8f0) once it arrived. */
uint32_t vertrix_port_actor_glide(PORT_SIGNATURE);

/* Original 0x45c830(eax = actor): set mode 1 (0x4ac7b0) and step it (0x4ac500); when its frame is
 * due (0x4ac520) advance it (0x4ac540, 0x4ac5b0) and move it on all three axes (0x4aca60, 0x4acab0,
 * 0x4acb00), updating 0x45c8b0 (0x4ac8f0) once it arrived. */
uint32_t vertrix_port_actor_glide_45c8b0(PORT_SIGNATURE);

/* Original 0x40e8a0(eax = voice, edx = command): apply the flags of byte +1: sample +0x38
 * (0x40adb0) with offset +0x74 (0x40ade0), stop (0x40add0), period +0x2c (0x40ce20, 0x40adf0),
 * volume +0x18 scaled by 0x531b68 (0x40ae00), pan +0x20 (0x40ae10) and start (0x40adc0), then clear
 * the flags. */
uint32_t vertrix_port_voice_command_apply(PORT_SIGNATURE);

/* Original 0x43e840(edx = actor): store the screen size 0x5b9c8e in 0x54101c, set the actor up
 * (0x4ac8d0 with 0x544c64, 0x4ac710, 0x4ac8a0 by 5, 0x4ac7b0) at a random place on it (0x4826c0)
 * with the update 0x4574a0 (0x4ac8f0) and a random wait of 100 + random(200) into +0x5c. Returns
 * the random part in edx. */
uint32_t vertrix_port_drop_actor_start(PORT_SIGNATURE);

/* Original 0x443460(eax = actor): set mode 1 (0x4ac7b0) and step it (0x4ac500); when its frame is
 * due (0x4ac520) advance it (0x4ac540, 0x4ac5b0) and move it on all three axes (0x4aca60, 0x4acab0,
 * 0x4acb00); once it arrived take its next update (0x4ac940 with 2) and reset its mode (0x4ac7b0).
 */
uint32_t vertrix_port_actor_glide_take(PORT_SIGNATURE);

/* Original 0x4854a0(eax = display): lock its surface +0x6c (method +0x64 with 0x5b9944), restoring
 * it (method +0x6c, 0x487080) and retrying while it is lost; on success store the pitch 0x5b9954
 * and pixels 0x5b9968 in 0x558c84 (0x478da0). Returns 1, or 0 when it stays lost. */
uint32_t vertrix_port_surface_lock(PORT_SIGNATURE);

/* Original 0x489d00(eax = first, edx = second): 1 when the strings have the same length and match
 * ignoring case (0x4dabb0), otherwise 0. Returns where the second stopped in edx. */
uint32_t vertrix_port_name_equals(PORT_SIGNATURE);

/* Original 0x4d9150: initialise the locks 0x5c7618 and 0x5c7619 (0x4d30f0), construct the exception
 * records 0x5c761c and 0x5c76b8 (0x4d92f0, tables 0x51a524 and 0x51a544, codes 0xf023 and 0xf021)
 * with the lock 0x5c76b4 between, registering 0x504af0 and 0x504b00 (0x4ec1f7). Returns the handler
 * chain. */
uint32_t vertrix_port_static_init_5c7618(PORT_SIGNATURE);

/* Original 0x477d70(eax = box): make it cover the screen 0x5b9c8e by 0x5b9c90 (0x477e10), put it in
 * the middle (0x478480) and clear +0x64..+0x70. */
uint32_t vertrix_port_box_fit_screen(PORT_SIGNATURE);

/* Original 0x40a950(eax = result): find the highest of the audio drivers 7..1 (0x52f090) whose
 * first or second routine table (+4 of each) opens, storing its number. Returns 0, 2 without a
 * result, 3 when audio is busy (0x4f6418) or 5 when none opens. */
uint32_t vertrix_port_audio_driver_find(PORT_SIGNATURE);

/* Original 0x43f480(eax = font): map the twelve punctuation characters ' . & ! ? , / ; : < > @ to
 * glyphs 0..11 (0x48abf0). The setups after it map them from the glyph in their name on. */
uint32_t vertrix_port_font_glyphs_map(PORT_SIGNATURE);

/* Original 0x4e53b4(eax = double, edx = target): convert the double to the 80 bit extended format
 * at the target, normalising denormals and quieting NaNs (0x4e2371). Returns the mantissa in eax
 * and edx. */
uint32_t vertrix_port_double_to_extended(PORT_SIGNATURE);

/* Original 0x43f550(eax = font): the punctuation from glyph 0xd6 on. */
uint32_t vertrix_port_font_glyphs_map_d6(PORT_SIGNATURE);

/* Original 0x43f630(eax = font): the punctuation from glyph 0x5e on. */
uint32_t vertrix_port_font_glyphs_map_5e(PORT_SIGNATURE);

/* Original 0x43f710(eax = font): the punctuation from glyph 0xe6 on. */
uint32_t vertrix_port_font_glyphs_map_e6(PORT_SIGNATURE);

/* Original 0x43f7f0(eax = font): the punctuation from glyph 0x116 on. */
uint32_t vertrix_port_font_glyphs_map_116(PORT_SIGNATURE);

/* Original 0x43f8d0(eax = font): the punctuation from glyph 0x146 on. */
uint32_t vertrix_port_font_glyphs_map_146(PORT_SIGNATURE);

/* Original 0x43f9b0(eax = font): the punctuation from glyph 0x176 on. */
uint32_t vertrix_port_font_glyphs_map_176(PORT_SIGNATURE);

/* Original 0x43fa90(eax = font): the punctuation from glyph 0x1a6 on. */
uint32_t vertrix_port_font_glyphs_map_1a6(PORT_SIGNATURE);

/* Original 0x43fb70(eax = font): the punctuation from glyph 0x1d6 on. */
uint32_t vertrix_port_font_glyphs_map_1d6(PORT_SIGNATURE);

/* Original 0x441530(eax = entry, edx = name, ebx, ecx, stack: three flags and a second name): copy
 * the names to +0 and +0x104, store bl, cl and the flags at +0x220..+0x224 and clear the counters.
 */
uint32_t vertrix_port_player_entry_init(PORT_SIGNATURE);

/* Original 0x4ee420(static initialiser): set the three handler records at 0x50c08c, 0x50c0ac and
 * 0x50c0cc to 0x4ee7f0, 0x4ee800 and 0x4ee810, clear 0x50c0ec..0x50c0f4 and register the table
 * (0x4d30f0). */
uint32_t vertrix_port_static_init_50c08c(PORT_SIGNATURE);

/* Original 0x4797f0(eax = image, edx = mask name): load the mask (0x4816f0) and set the alpha byte
 * of each of the width +4 by height +8 pixels at +0 to 0xff where the mask byte is set, otherwise
 * 0, through the cursors at 0x558a20..0x558a2c; then free the mask (0x478d80). */
uint32_t vertrix_port_image_alpha_from_mask(PORT_SIGNATURE);

/* Original 0x40c5c0(eax = samples, edx = count): hand the samples to each of the 0x52fc18 mixer
 * channels at 0x52f918 (0x40c460), in pieces that fit the ring at 0x52fc24 and 0x52fc28 when the
 * ring callback 0x52fc30 is set, calling it each time the ring wraps. */
uint32_t vertrix_port_mix_buffer_feed(PORT_SIGNATURE);

/* Original 0x40df20(eax = voice): reset the voice for a new note from its instrument +0x34: clear
 * the volume and pitch envelopes the instrument uses, take its pan +0x86 and set up the vibrato
 * step from depth +0x84 over speed +0x83. */
uint32_t vertrix_port_voice_note_reset(PORT_SIGNATURE);

/* Original 0x486d00(eax = display): flip the back buffer +0x68 (method 0x64) until it succeeds,
 * restoring lost surfaces (+0x64 method 0x6c, then 0x487080) and waiting out busy ones (method
 * 0x48); then reattach the view (0x478da0). Returns 1, or 0 when a surface cannot be restored. */
uint32_t vertrix_port_display_restore(PORT_SIGNATURE);

/* Original 0x4575b0(eax = actor): on a new frame (0x4ac520) start the hop animation, nudge +0xe and
 * +0x16 by 2 less a random 0..4 (0x4826c0 on 0x598d30) and, when it ends (0x4ad530), settle
 * (0x4ac740, 0x4ac700) and go back to state 0x4574a0; then step (0x4ac8a0). */
uint32_t vertrix_port_actor_hop_step(PORT_SIGNATURE);

/* Original 0x45c480(eax = actor): the bobbing state at height 0x32, going to 0x45c540
 * (actor_bob_step). */
uint32_t vertrix_port_actor_bob_high(PORT_SIGNATURE);

/* Original 0x45c540(eax = actor): the bobbing state at height 0, going to 0x45c480
 * (actor_bob_step). */
uint32_t vertrix_port_actor_bob_low(PORT_SIGNATURE);

/* Original 0x405e00(eax = list, ebx = size): allocate a 0x14 byte chunk record (0x4e7c90) with a
 * cleared buffer of the size (0x4eb5e0) and append it to the list, adding the size to +8. Returns
 * the record, or 0 when either allocation fails. */
uint32_t vertrix_port_chunk_list_add(PORT_SIGNATURE);

/* Original 0x45d420(eax = actor): update the climb (0x45cff0, 0x4ac370); on a new frame (0x4ac390)
 * take its step count (0x4ac3b0, 0x4ac420) and walk it (0x4ac780, 0x4ac740), ending (0x4ac4a0,
 * 0x4adfe0); when a step is blocked, fall back to the idle state 0x45d0c0 with animation 0x544a34.
 */
uint32_t vertrix_port_actor_climb_step(PORT_SIGNATURE);

/* Original 0x40c6b0(eax = format): clear the mixer channels at 0x52f918, store the rate and flags
 * from +4 and +6, pick the mixing routines for 16 bit (0x8000) and stereo (0x100) output, allocate
 * the 1K aligned mix buffers (0x4e7c90) and start the mixer timer (0x40ac30, 0x40ac00). Returns 0,
 * or 8 without memory. */
uint32_t vertrix_port_mixer_open(PORT_SIGNATURE);

/* Original 0x483110(eax = image): copy the image record (0x4ec160) and its pixels (0x4ec160).
 * Returns the copy, or 0 without an image. */
uint32_t vertrix_port_image_clone(PORT_SIGNATURE);

/* Original 0x457330(eax = actor): on a new frame (0x4ac520) and once the animation ends (0x4ad6e0)
 * pick a random heading (0x482750) and pause (0x4826c0, 0x4ac470), jump to a random spot of the
 * area table 0x546744 (0x4b5eb0) and go to state 0x457420; then step (0x4ac8a0). */
uint32_t vertrix_port_actor_wander_start(PORT_SIGNATURE);

/* Original 0x40e580(eax = voice): mark the voice on +0 when its note +7 is 1..0x60 and pick the
 * sample +6 for the note from the instrument +0x34 keyboard map, taking its record +0x38 (of the
 * +0xf8 records of 0x3c bytes), fine tune +0xc and relative note +8; then, unless the effect +3 is
 * 3 or 5 or a fine tune +2 is given, set the period +0x24 and +0x28 (0x40ce80). */
uint32_t vertrix_port_voice_sample_select(PORT_SIGNATURE);

/* Original 0x45ed60(eax = sheet): cut the 0x5d glyphs of font 0x544a88 (0x4877f0) out of the sheet
 * (0x482e10) at their cells in the grid 0x4f9054..0x4f9064, numbered by 0x4f92a0, paste each into
 * the next grid cell (0x482e80) and add it to 0x5b9c60 (0x483ed0). */
uint32_t vertrix_port_font_sheet_cut(PORT_SIGNATURE);

/* Original 0x45ef40(eax = target, edx = sheet): cut the 0x13 glyphs of font 0x544aa4 (0x4877f0) out
 * of the sheet (0x482e10) along the strip 0x4f9068..0x4f9070, numbered by 0x4f9300, and paste each
 * doubled (0x482f00) into the grid 0x4f9054..0x4f9064 from cell 0x53bc20 on, adding it to 0x5b9c60
 * (0x483ed0). */
uint32_t vertrix_port_font_sheet_cut_wide(PORT_SIGNATURE);

/* Original 0x40e690(eax = cell): read the next packed cell of the pattern stream 0x530440 into the
 * five bytes note, instrument, volume, effect and parameter: a byte with bit 7 set says which
 * follow, otherwise all five do; a missing stream gives an empty cell. */
uint32_t vertrix_port_pattern_cell_read(PORT_SIGNATURE);

/* Original 0x45ee30(eax = sheet): cut the glyph strips of the fonts 0x544ba0 (12, along 0x4f9090),
 * 0x544bbc (12, along 0x4f9080) and 0x544bd8 (7, along 0x4f90a0) out of the sheet (0x4877f0,
 * 0x482e10) and add each to 0x5b9c60 (0x483ed0). */
uint32_t vertrix_port_font_strips_cut(PORT_SIGNATURE);

/* Original 0x40eb10(): advance the module player a tick unless it is stopped (0x531b44 bit 0x20):
 * past the speed 0x531b60 read the next row (0x40e940), run the effects of each of the 0x531b48
 * channels at 0x530444 (0x40dc80, 0x40dc50, 0x40e030), count down the pattern delay 0x531b78, apply
 * a pending volume change to all channels (bit 0x10) and tempo (bit 8, 0x40ac20), then mix each
 * channel into its voice 0x531ac4 (0x40e8a0). */
uint32_t vertrix_port_module_tick(PORT_SIGNATURE);

/* Original 0x4e8098(): once (0x5c81d4), copy the double null terminated environment block 0x509729
 * into a new buffer 0x5c8a90 (0x4e7c90) and build the null ended table of its strings 0x5c81d4,
 * whose end is 0x5c81d0, clearing the per string flags after it (0x4eb5c0); then finish (0x4e9f10).
 */
uint32_t vertrix_port_environment_table_build(PORT_SIGNATURE);

/* Original 0x40e770(eax = channel): read the channel's next pattern cell into 0x531b80
 * (0x40e690), keep the vibrato period unless the new effect continues it, take the effect,
 * parameter and volume, switch to the cell's instrument of the module 0x53043c, and start the
 * note (0x40e580, 0x40df20) or key it off (0x40e640), resetting the volume and panning from the
 * sample. */
uint32_t vertrix_port_channel_row_read(PORT_SIGNATURE);

/* Original 0x40a9d0(eax = settings): open the audio driver named by +0 (or, when that is the busy
 * marker, the best one found by 0x40a950): copy its routine tables to 0x52f010 and 0x52f028
 * (0x4eb5e0, defaults 0x4f7658 and 0x4f651c), probe (0x52f018) and open it (0x52f030), then clear
 * the voice table 0x52f0b0 (0x4eb5c0) and mark it busy in 0x4f6418. Errors go through 0x40a800; 3
 * when audio is already open. */
uint32_t vertrix_port_audio_driver_open(PORT_SIGNATURE);

/* Original 0x40c7d0(eax = 1, edx = volume up to 0x100): fill the 16 bit volume table 0x52f910 (65
 * levels of 128 positive and 128 negative samples, halving the volume for 8 bit output) and the 8
 * bit table 0x52f914 (32 levels). Returns 0, 3 without mix buffers or 2 for a bad request. */
uint32_t vertrix_port_mixer_volume_tables(PORT_SIGNATURE);

/* Original 0x40ec40(eax = module): start playing the module unless one is playing (0x531b44 bit
 * 0x80): clear the player state 0x53043c (0x4eb5c0), take the channel count, flags, speed and
 * tempo, allocate a voice for each channel (0x40acf0) with its default panning (0x40ae10), set the
 * tempo (0x40ac20) and install the tick 0x40eb10 (0x40ac10). Returns 0, 2 without a module, 3 when
 * busy or 8 when voices run out (0x40ed70). */
uint32_t vertrix_port_module_start(PORT_SIGNATURE);

/* Original 0x4d6830(static initialiser): set the eight handler records 0x503a1c..0x503afc (every
 * 0x20 bytes) to 0x4d7430..0x4d74a0, clear 0x503b1c..0x503b24 and register the table (0x4d30f0). */
uint32_t vertrix_port_static_init_503a1c(PORT_SIGNATURE);

/* Original 0x4b9050(): expand the 16 dither patterns 0x4ff8ac into 64 rows of 16 flag bytes each at
 * 0x5bdb00, count the set flags before each position of the first row of each into 0x5c1b00, and
 * for patterns 1..15 record the gaps between set flags at 0x5c1c00 (cleared first, 0x4eb5c0). */
uint32_t vertrix_port_dither_tables_build(PORT_SIGNATURE);

/* Original 0x45eac0(): create the six fonts 0x544a88, 0x544aa4, 0x544b84, 0x544ba0, 0x544bbc and
 * 0x544bd8 with their glyph counts and cell sizes from 0x4f9060..0x4f90ac (0x4875a0); the last one
 * without the flag the others pass. */
uint32_t vertrix_port_fonts_create(PORT_SIGNATURE);

/* Original 0x40e940(): move the module player to the next row: unless it is stopped (0x531b44 bit
 * 4), past the pattern length 0x531b54 advance the order position 0x531b5c (or jump to 0x531b70 or
 * break to 0x531b74), wrapping to the restart order +0x24 or stopping at the song length +0x22 (bit
 * 0x20); load the pattern of the order (+0x150 records of 12 bytes, 0x40 empty rows when missing)
 * into 0x530440 and skip to the break row (0x40e690), then read the cell of each channel
 * (0x40e770). */
uint32_t vertrix_port_module_next_row(PORT_SIGNATURE);

/* Original 0x404480(eax = frame, edx = header): decode an MPEG audio frame header into the frame
 * record: version +0xc and +0x10, layer +0x18, rate index +0x24, protection +0x1c, bit rate +0x20,
 * padding +0x28, private +0x2c, mode +0x30, extension +0x34, copyright +0x38, original +0x3c,
 * emphasis +0x40 and channels +0; for layer III the frame size +0x44 from the tables 0x4f40ac and
 * 0x4f41ac. A reserved rate stops (0x4eb4d4). Returns 1 for a usable header. */
uint32_t vertrix_port_mpeg_header_decode(PORT_SIGNATURE);

/* Original 0x472db0(): spawn the two title screen actors (0x4ca000, 0x4abd70 when it fails): random
 * heading and speed (0x4826c0), an animation from 0x546834 (0x4ac950 or 0x4ac8d0 with 0x4fd648,
 * 0x4ac710, 0x4ac8a0), position from 0x4fd650 and 0x4fd658, state 0x4fd660, the first one marked
 * leading, and add each to the area list 0x546744 (0x4b5e70). */
uint32_t vertrix_port_title_actors_spawn(PORT_SIGNATURE);

/* Original 0x45d4d0(eax = actor): on a new frame (0x4ac520, 0x4adfe0, 0x4ac510) measure the
 * distance (0x484680) and angle (0x484700) from (0x1aa, 0x28) to the target 0x558944, 0x558946
 * (0x7d00 while 0x558958 is set); near it stop (0x4ac8d0, 0x4ac950), otherwise turn the facing
 * +0xb8 one of eight steps towards the angle (0x4ac710, 0x4ac8a0), or face it at once with
 * animation 0x54666c when not turning (+0xb0). */
uint32_t vertrix_port_actor_face_target(PORT_SIGNATURE);

/* Original 0x45d880(static initialiser): construct the animation and image objects
 * 0x5449c4..0x5466a4 (0x4872f0, or 0x4ccf3b for the arrays) and register the destructor records
 * 0x4fbc30..0x4fbec0 (0x4ec1f7). */
uint32_t vertrix_port_static_init_animations(PORT_SIGNATURE);

/* Original 0x4b1fa0(eax = actor): draw the actor: a sprite with a colour key (+0x11c not
 * 0xff000000) through 0x47c710, otherwise through its draw routine 0x4ff024 for the colour depth
 * 0x5bb733 and the frame (0x4af370, 0x4af2a0, 0x4ae250); then, when selected (+0x110), its outline
 * in colour +0x118 and +0x114 (0x47c520, plain in mode 2 of 0x5bbffe) and, unless +0x13c, its hit
 * box (0x4ae110). */
uint32_t vertrix_port_actor_draw_frame(PORT_SIGNATURE);

/* Original 0x4e7850(eax = tm): mktime: normalise the month into the year, count the days since 1900
 * with the leap year (0x4e9060) month table 0x51c06c or 0x51c086, add the seconds of the day, set
 * the time zone (0x4e7a00, 0x4e960c), apply daylight saving (0x4e91e0, 0x50b0e4) and the zone
 * 0x50b0dc, and return seconds since 1970, or -1 out of range. */
uint32_t vertrix_port_time_from_tm(PORT_SIGNATURE);

/* Original 0x4408e0(al = font, edx = x, bx = y, ecx = width; stack: the alignment word, the text,
 * the flags byte and pointers for the line start, the line count, the left and the top; ret
 * 0x1c): measure the text (0x440610, the line start and count into the frame at ebp - 0x20 and
 * ebp - 0x1c) and lay it out (0x440990 with x, y, width and the alignment sign-extended), then
 * store the left and top words and the start and count dwords through the pointers. Returns the
 * saved exception chain in eax and the count pointer in edx. */
uint32_t vertrix_port_text_measure_layout(PORT_SIGNATURE);

/* Original 0x440610(al = font, edx = text, bl = style, ecx = width pointer; stack: the height
 * pointer; ret 4): measure a text. Width and height start at 0. Empty text (0x4ccfe0 against
 * 0x50e12c) sizes one blank glyph: the width becomes 0 and the height its height. Otherwise each
 * character makes a glyph actor (0x4ca000, 0x4abd70, placed by 0x4adf20): a space with the font's
 * size from 0x541988, any other with its image from 0x43f420 (skipped when there is none). Each
 * measured glyph (0x4b14c0) adds its width plus 1 and raises the height to its own; the glyph is
 * then destroyed through its table (+0x158, with 2). Returns the saved exception chain. */
uint32_t vertrix_port_text_measure(PORT_SIGNATURE);

/* Original 0x4b3390(eax = actor): refresh its label actor (+0x160). The actor's style +0x44 is set
 * to 0x10 and 0x4b5560 runs; with a label, its text (+0x15c) is copied into a frame string and the
 * label placed (0x4b65d0, font byte +0x160) at the actor's position plus the label offset
 * (+0x164, +0x166) or, when +0x168 or +0x16c is set, plus its size (+0xf4, +0xf8) less one,
 * then updated through its table slot 1 and the string released (0x4ca210). Returns the saved
 * exception chain; edx is unchanged. */
uint32_t vertrix_port_actor_label_refresh(PORT_SIGNATURE);

/* Original 0x4826c0(eax = table, dx = limit): the next word of the random table (+8) modulo the
 * limit. The draw count +0xc goes up and the pointer by 2; at 0x1001 draws the table is refilled
 * (0x482550 when +4 is 1, else 0x482540), whose edx is then the result. Returns the result in eax
 * and edx. */
uint32_t vertrix_port_random_below(PORT_SIGNATURE);

/* Original 0x4ac1f0(eax = animation): advance it (0x4ac370) and, when 0x4ac390 reports 1, run the
 * frame steps 0x4ac3b0 counts: 0x4ac420 once, then per step 0x4ac740 and, when 0x4ac760 reports
 * 1, 0x4ac700. Returns the last call's eax; edx is unchanged. */
uint32_t vertrix_port_animation_tick(PORT_SIGNATURE);

/* Original 0x4d86d0(eax = exception object, dl = flags): its destructor. With flag 4 the object
 * is finalized (0x4ccb9f with 0x51a0f0) and freed (0x4ca040). Otherwise, under a guard record,
 * its message (+4) is freed, its class pointer set back to 0x517454, and with flag 2 the object
 * freed (0x4ca050). Returns the object. */
uint32_t vertrix_port_exception_destroy(PORT_SIGNATURE);

/* Original 0x4d7a10(eax = file, edx = distance, ebx = method): move the file's pointer through
 * the SetFilePointer import (slot 0x4f1ca8, handle +4); on failure the error (slot 0x4f1bbc) is
 * recorded by 0x4d9930. Returns the new position or -1. */
uint32_t vertrix_port_file_seek(PORT_SIGNATURE);

/* Original 0x478480(eax = object, edx = x, ebx = y): clamp the position into the object's
 * bounds (the words +0x3c to +0x42: left, top, right, bottom) and store it at +0x48 and +0x4a.
 * Returns the object and, in edx, the clamped x. */
uint32_t vertrix_port_object_clamp_position(PORT_SIGNATURE);

/* Original 0x4d7630(eax = file stream, edx = mode): the file stream's destructor. Mode 4
 * destroys an array (0x4ccb9f with the element destructor 0x519f70, freed by 0x4ca040).
 * Otherwise, under a guard record, an open file with a buffer is flushed (0x4d7aa0), the buffer
 * member (+0xc) destroyed by 0x4ca210, the base class's table restored and, with mode 2, the
 * object freed (0x4ca050). Returns the object. */
uint32_t vertrix_port_file_stream_destroy(PORT_SIGNATURE);

/* Original 0x4dbf80(eax = slot key, edx = constructor): the calling thread's value for a slot,
 * made by the constructor and stored (0x4dbd20) when it has none. The key is allocated on first
 * use (0x4dbb30, the slot table at 0x5c77a8 made by 0x4dbac0); the value is looked up in the
 * thread's array from TlsGetValue (slot 0x4f1cdc). */
uint32_t vertrix_port_thread_slot(PORT_SIGNATURE);

/* Original 0x4e7a00(eax = days since 1900, edx = seconds, ebx = bias in seconds, ecx = struct
 * tm): fill in the seconds, minutes, hours, day of the month, month, year since 1900, weekday
 * and day of the year. Leap years come from 0x4e9060, month starts from the tables 0x51c06c and
 * 0x51c086 (leap). Returns the struct and, in edx, the weekday. */
uint32_t vertrix_port_days_to_tm(PORT_SIGNATURE);

/* Original 0x4e960c: the C runtime's tzset. With TZ set (getenv 0x4dac40) its standard and
 * daylight names and offsets are parsed (0x4e969c) into 0x50afd0, 0x50b0dc, 0x50b051 and the
 * daylight bias 0x50b0e4, and the daylight rules (0x4e97b4, 0x50af88 and 0x50afac, the end moved
 * back by the bias). Otherwise, once (0x50b0e8 bit 1), GetTimeZoneInformation gives the bias,
 * the daylight flag 0x50b0e0 and the names (0x4ea350). Keeps edx. */
uint32_t vertrix_port_tzset(PORT_SIGNATURE);

/* Original 0x4e91e0(eax = struct tm): the C runtime's daylight saving test, stored at +0x20 and
 * returned. Without a daylight zone name ([0x50b0d8]) it is 0. The time must be past the start
 * rule's day and before the end rule's (0x50af88 and 0x50afac, swapped for a southern zone that
 * 0x4e9194 reports, whose answer is reversed); rules give the nth weekday of a month or a day of
 * the year, and on the rule's day 0x4e949c compares the time of day. */
uint32_t vertrix_port_is_dst(PORT_SIGNATURE);

/* Original 0x4895e0(eax = path): whether a file is found (0x4d9060 with a local find record
 * returns 1). */
uint32_t vertrix_port_find_succeeded(PORT_SIGNATURE);

/* Original 0x41a2b0(eax = scene, ebx = argument): refresh a scene: 0x41aaf0, the screen
 * (0x5b9c50) opened by 0x486d00, the scene drawn by 0x41a2f0 with 0x558c7c, the screen closed and
 * presented (0x486da0, 0x487020). */
uint32_t vertrix_port_scene_refresh(PORT_SIGNATURE);

/* Original 0x4db10a(edx:eax = a double): run the value through a 12-byte temporary: 0x4e53b4
 * converts it, 0x4db131 works on it and 0x4e543c (the temporary also as its stack arguments)
 * converts it back into the pushed pair, which is returned. */
uint32_t vertrix_port_scratch_triple(PORT_SIGNATURE);

/* Original 0x4d7aa0(eax = file): close the file's handle (+4, CloseHandle) and its buffer
 * (+0xc, 0x4ca180); a failure is recorded by 0x4d9930. Keeps edx. */
uint32_t vertrix_port_file_close(PORT_SIGNATURE);

/* Original 0x4d7980(eax = file, edx = buffer, ebx = count): read or write through slot 0x4f1c78
 * on the handle (+4); a failure is recorded by 0x4d9930. Returns the count done, 0 for none
 * asked. */
uint32_t vertrix_port_file_transfer(PORT_SIGNATURE);

/* Original 0x4dbcd0(eax = slot table, edx = index): the calling thread's value at the index:
 * from TlsGetValue's array, or without a TLS index (-1) the shared array at +4 under the critical
 * section at +0x20. 0 past the array's count (+8, values at +0xc). */
uint32_t vertrix_port_thread_value(PORT_SIGNATURE);

/* Original 0x488b10(eax = object): construct an object of the class with table 0x5174b4 on the
 * base 0x4d7510, under a guard record; a temporary base object is made and destroyed. Keeps
 * edx. */
uint32_t vertrix_port_object_construct_e(PORT_SIGNATURE);

/* Original 0x45e990(eax = row, edx = column, ebx, ecx; stack: two dwords; ret 8): call 0x487750
 * on the grid cell (0x544f90, rows of 0x118 bytes, cells of 0x1c) with edx = ebx, ebx = ecx,
 * ecx = the first stack dword and the second passed on. */
uint32_t vertrix_port_grid_cell_call(PORT_SIGNATURE);

/* Original 0x484680(ax, dx = one point, bx, cx = the other): the integer distance between the
 * points, by Newton's method from 1 (state in 0x598dc0 to 0x598dd4). edx is the sign of the last
 * change. */
uint32_t vertrix_port_point_distance(PORT_SIGNATURE);

/* Original 0x4ec850(eax = struct tm): the local time (GetLocalTime) as a struct tm, isdst -1.
 * Returns the milliseconds; keeps edx. */
uint32_t vertrix_port_local_time(PORT_SIGNATURE);

/* Original 0x4de9c0(stack: lock number; ret 0): the C runtime's _lock: enter the numbered
 * critical section (0x5c79d8, 0x18 bytes each), made on first use under the guard lock 0x5c7b28;
 * nothing for a single-threaded runtime (0x5c79d4). The locks are made by 0x4de970 first. */
uint32_t vertrix_port_runtime_lock(PORT_SIGNATURE);

/* Original 0x4ccf3b(eax = array, edx = count, ebx = type): construct each element of an array
 * with the type's constructor (+4) and size (+0x10), under a guard record that 0x4ce9fd closes.
 * Returns the array. */
uint32_t vertrix_port_construct_array(PORT_SIGNATURE);

/* Original 0x487790(eax = object, edx, ebx = keys): look both keys up (0x4877f0); with the
 * second's entry found, 0x4830f0 runs on it; the first's (0x483110) is then stored under the
 * second key by 0x487850. Returns 0 when the first is missing. */
uint32_t vertrix_port_object_pair_update(PORT_SIGNATURE);

/* Original 0x48a670(eax = object, edx = mode): a destructor: mode 4 destroys an array (element
 * destructor 0x513310, freed by 0x4ca040); otherwise the table at +0x110 is reset, the base
 * destructor 0x48a8c0 runs under a guard record and, when its edx has bit 1, 0x4ca050 frees the
 * object. Returns the object. */
uint32_t vertrix_port_object_destroy_h(PORT_SIGNATURE);

/* Original 0x475840(eax = owner): construct an effect object (0x4756d0, then 0x4d8340 with 10
 * for its base at +0x20) under a guard record, with its tables 0x5165f4 and 0x5165d4, fields
 * cleared and +0x3c, +0x40 from 0x553644. Returns the effect; keeps edx. */
uint32_t vertrix_port_effect_construct(PORT_SIGNATURE);

/* Original 0x43f110(eax = index, edx = first, ebx = count, ecx = file; one stack argument): open
 * the bank (0x4877f0 on 0x546538) and, when it opens, load `count` sprites by the names at
 * 0x5410f8 (0x4831b0) into 0x5410f8 from the index, calling 0x418270 with 2 after each. */
uint32_t vertrix_port_sprite_bank_load(PORT_SIGNATURE);

/* Original 0x4d92f0(eax = object, edx = code): construct an error object (tables 0x517454, then
 * 0x517474) holding the code at +4, under a guard record. */
uint32_t vertrix_port_error_construct(PORT_SIGNATURE);

/* Original 0x4b2290(eax = start, edx = count): clear `count` dwords; returns the end in eax and
 * edx (eax and 0 for none). */
uint32_t vertrix_port_zero_dwords(PORT_SIGNATURE);

/* Original 0x4ca600(eax = string, edx = text): 0x4ca5a0 with the text's length (0 for none) and
 * ebx = text. Returns the string. */
uint32_t vertrix_port_string_assign_text(PORT_SIGNATURE);

/* Original 0x41a4e0(eax = player): 0x4182c0, then 0x41a2f0 (with +0x268 of 0x544070's object),
 * 0x41ab90 and 0x41a9e0 with its result in ebx and 0x540048 in ecx. Keeps edx. */
uint32_t vertrix_port_player_refresh(PORT_SIGNATURE);

/* Original 0x4e23e0(chain, count, size; cdecl): allocate count * size bytes after a link
 * (0x4c9ff0) and push it onto the chain. Returns the block. */
uint32_t vertrix_port_block_chain_new(PORT_SIGNATURE);

/* Original 0x4dbac0(eax = lock, edx = name): clear a lock's fields, open its named event (import
 * 0x4f1cd4, failing to 0x4d9510) or mark it -1, and initialise its section at +0x20 (import
 * 0x4f1c30). Returns the lock. */
uint32_t vertrix_port_lock_construct(PORT_SIGNATURE);

/* Original 0x4d84f0(eax = pool, edx = item): push the item on the pool's free list (+0x10) and,
 * when no item is left in use (+0xc), release the pool (0x4d83c0). */
uint32_t vertrix_port_pool_release(PORT_SIGNATURE);

/* Original 0x4cea15(eax = object, edx, ebx): under a guard record, call 0x4ce9c0 and 0x4ce9fd on
 * a record of 1, edx, ebx and the object. Returns the object. */
uint32_t vertrix_port_guarded_call_pair(PORT_SIGNATURE);

/* Original 0x4ce9c0(eax = array record): destroy its elements (count +4, type +8 with the size at
 * +0x10 and the destructor at +0xc, data +0xc) last first, then clear +0. Returns the data. */
uint32_t vertrix_port_array_destroy_elements(PORT_SIGNATURE);

/* Original 0x487280(eax, edx, ebx): a new 0x1c-byte record (0x4ec160) of the three with the byte
 * at 0x5b9ca6. */
uint32_t vertrix_port_object_record_new(PORT_SIGNATURE);

#endif
