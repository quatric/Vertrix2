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

#endif
