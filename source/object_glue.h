#ifndef VERTRIX_OBJECT_GLUE_H
#define VERTRIX_OBJECT_GLUE_H
#include "actor_gate.h"
#include "block_factory.h"
#include "call_glue.h"
#include <stddef.h>
#include <stdint.h>

enum
{
    VERTRIX_OBJECT_PARENT = 0x160,
    VERTRIX_OBJECT_PARENT_LIST = 0x15c,
    VERTRIX_OBJECT_TABLE_FIELD = 0x158,
    VERTRIX_OBJECT_TABLE_5182C4 = 0x5182c4,
    VERTRIX_OBJECT_WORD_15C = 0x15c,
    VERTRIX_OBJECT_MODE = 0x174,
    VERTRIX_OBJECT_HEAD = 0x188,
    VERTRIX_OBJECT_TAIL = 0x18c,
    VERTRIX_OBJECT_BOX_LEFT = 0x16a,
    VERTRIX_OBJECT_BOX_RIGHT = 0x16c,
    VERTRIX_OBJECT_BOX_TOP = 0x16e,
    VERTRIX_OBJECT_BOX_BOTTOM = 0x170,
    VERTRIX_OBJECT_GLYPH_BYTE = 0x160,
    VERTRIX_OBJECT_STYLE_BYTE = 0x44
};

/* Original 0x4b4510: store value at +0x174; when it is one, 0x4ca370 on object + 0x188 with the
 * dword at +0x15c of the object that +0x160 names. Returns its eax, or the object otherwise;
 * zero when a storage is short. */
uint32_t vertrix_object_set_mode(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                 uint32_t object, void *storage, size_t size, uint32_t value);

/* Original variants 0x4b4c90, 0x4b4cd0: fields 0x188 and 0x18c, respectively.
 * 0x4ca370 on the parent list at +0x15c of the object +0x160 names, with the
 * dword of the field. Returns its eax. */
uint32_t vertrix_object_parent_append(const VertrixCalls *calls, uint32_t object,
                                      const void *storage, size_t size, size_t field);

/* Original 0x4b5c60: build through 0x4abd70 (eax and edx handed through), then store 0x5182c4 at
 * +0x158 and clear the word at +0x15c and the dword at +0x160 of the object it returned. Returns
 * that object. */
uint32_t vertrix_object_start_5182c4(const VertrixCalls *calls,
                                     const VertrixFactoryServices *services, uint32_t eax,
                                     uint32_t edx);

/* Original 0x4b66c0: one when (x, y) lies inside the signed 16-bit box at +0x16a..+0x170, stored
 * through *hit (the global 0x5bd828) as well. Returns the result; zero for short storage. */
uint32_t vertrix_object_contains(const void *storage, size_t size, int16_t x, int16_t y,
                                 uint32_t *hit);

/* Original 0x4b69f0: 0x440610 on the signed glyph byte at +0x160, 0x5110b8 and the style byte at
 * +0x44, with edx as ecx and the caller's ebx as its stack argument. Returns its eax. */
uint32_t vertrix_object_glyph_layout(const VertrixCalls *calls, const void *storage, size_t size,
                                     uint32_t edx, uint32_t caller_ebx);

/* Original 0x4b6a10: 0x43f460 on the signed glyph byte at +0x160 and the low byte of edx. */
uint32_t vertrix_object_glyph_present(const VertrixCalls *calls, const void *storage, size_t size,
                                      uint32_t edx);

/* Original variants 0x4b6f70, 0x4879f0, 0x48d600, 0x4b79a0: 0x4d88a0 on the
 * object, its dword at +8, edx and one. Returns zero. */
uint32_t vertrix_object_release_call(const VertrixCalls *calls, uint32_t object,
                                     const void *storage, size_t size, uint32_t edx);

/* Original 0x43d330: allocate a 0x10-byte object (the raw 0x4ca000 operator
 * new; no constructor runs, so the object carries no class token), store
 * edx/ebx/ecx at +0/+4/+8 and then release-call the object named by the
 * holder's +0x468 with the new handle. Zero from the allocator fails (the
 * Delphi owner raises instead of returning nil). Returns the release result
 * (always zero), zero when storage is short or an object does not resolve. */
uint32_t vertrix_object_table_store(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services, const void *storage,
                                    size_t size, uint32_t edx, uint32_t ebx, uint32_t ecx);

/* Original 0x43ac00 (eax = object): store one at +0x474, then run the holder's
 * virtual slot 6. state is the value the slot left at +0x474: one takes the
 * first path (chain length one, +0x474 cleared to zero, fallback
 * state_defaults[column] of the original table 0x532ca4); anything else takes
 * the second path (chain length five, +0x474 kept at one, fallback the
 * original global 0x4f81cc). The chain is looked up in the grid (0x534c18) by
 * column +0x488 through the counts at 0x534f10, and the first matching row is
 * taken; an empty result stores the zero address for chain one and returns
 * without storing for chain five. The selected row addresses the cell array at
 * 0x544f90 (0x118 bytes per column, 0x1c per row), which is stored as the
 * table value. ebx/ecx are the caller's registers, forwarded to the slot
 * method. Returns zero. */
uint32_t vertrix_object_chain_select(const VertrixCalls *calls,
                                     const VertrixFactoryServices *services, VertrixMemoryRead read,
                                     void *read_context, void *storage, size_t size,
                                     uint32_t global_default, const uint32_t *state_defaults,
                                     const uint32_t *grid, const uint32_t *counts, uint32_t column,
                                     uint32_t state, uint32_t ebx, uint32_t ecx);

/* Original 0x43acd0 (eax = object): run the holder's virtual slot 6 (its
 * result and the state at +0x474 are ignored), then the chain of length two
 * in the grid (0x534c18) by column +0x488 through the counts at 0x534f10;
 * the first matching row addresses the cell array at 0x544f90 and an empty
 * result stores the zero address. The fallback is pair_defaults[column] of
 * the original table 0x532cf0. Returns zero. */
uint32_t vertrix_object_chain_select_pair(const VertrixCalls *calls,
                                          const VertrixFactoryServices *services,
                                          VertrixMemoryRead read, void *read_context, void *storage,
                                          size_t size, const uint32_t *pair_defaults,
                                          const uint32_t *grid, const uint32_t *counts,
                                          uint32_t column, uint32_t ebx, uint32_t ecx);

enum
{
    VERTRIX_OBJECT_COMPARE_FIELD = 0x38,
    VERTRIX_OBJECT_COMPARE_LIST = 0x40,
    VERTRIX_OBJECT_COMPARE_VALUE = 0x4,
    VERTRIX_OBJECT_COMPARE_TABLE = 0x50ee0b,
    VERTRIX_OBJECT_CHAIN_HEAD = 0xc,
    VERTRIX_OBJECT_CHAIN_NEXT = 0x60
};

/* Original 0x47ecd0: when the dword at +4 of other equals the dword at +0x38 of the object,
 * 0x4ca370 on object + 0x40 with 0x50ee0b. Always returns zero. */
uint32_t vertrix_object_match_append(const VertrixCalls *calls, uint32_t object,
                                     const void *storage, size_t size, const void *other,
                                     size_t other_size);

/* Original 0x47f190: the index-th handle along the chain that starts at +0xc and continues at
 * +0x60 of each object, or zero when the chain ends first or a handle does not resolve. */
uint32_t vertrix_object_chain_at(const VertrixFactoryServices *services, const void *storage,
                                 size_t size, uint32_t index);

/* Original 0x482720: 0x4ec160 on 0x1001 with 2, then store the result at +0 and one at +4 of the
 * object. Returns the result, zero for short storage. */
uint32_t vertrix_object_alloc_pair(const VertrixCalls *calls, uint32_t object, void *storage,
                                   size_t size);

/* Original 0x487280: 0x4ec160 on 1 with 0x1c, then store eax, edx and ebx at +0, +4 and +8 of the
 * result and the byte at 0x5b9ca6 at +0xc. Returns the result, zero when it does not resolve. */
uint32_t vertrix_object_record_new(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services, uint32_t eax,
                                   uint32_t edx, uint32_t ebx, uint8_t global_byte);

/* Original 0x487710: store count at +4 and three 0x4ec160 results (size count, element 4) at +8,
 * +0xc and +0x10, with one at +0x14. Returns the last result, zero for short storage. */
uint32_t vertrix_object_alloc_arrays(const VertrixCalls *calls, void *storage, size_t size,
                                     uint32_t object, uint32_t count);

/* Original 0x4872c0: 0x478d10 with the word at +0x3e, the word at +0x40 and the byte at +0x10 of
 * the object, then the byte at +0x24 stored at +0xd of the surface it returns. */
uint32_t vertrix_object_surface_format(const VertrixCalls *calls,
                                       const VertrixFactoryServices *services, uint32_t object,
                                       const void *storage, size_t size);

/* Original 0x48c9b0: zero when the dword at +0x38 is zero, otherwise 0x47fa40 on the object with
 * that dword as ebx and the caller's ebx as ecx. Returns its eax. */
uint32_t vertrix_object_delegate(const VertrixCalls *calls, uint32_t object, uint32_t edx,
                                 uint32_t ebx, const void *storage, size_t size);

enum
{
    VERTRIX_OBJECT_ENABLED = 0x44,
    VERTRIX_OBJECT_TEXT_LENGTH = 0x170,
    VERTRIX_OBJECT_TABLE_4B78D0 = 0x518704,
    VERTRIX_OBJECT_TABLE_48D520 = 0x517a94,
    VERTRIX_OBJECT_BLOCK_COPY = 0xa4
};

/* Original variants 0x48c260, 0x48c310, 0x48c330: offsets 0x1cc, 0x1e4 and
 * 0x1e5, respectively. vertrix_object_delegate (0x48c9b0) on the object with
 * the address of the field at offset and a size of one. Returns its eax. */
uint32_t vertrix_object_notify_field(const VertrixCalls *calls, uint32_t object,
                                     const void *storage, size_t size, uint32_t offset);

/* Original 0x48c280: zero unless the dword at +0x44 is one; otherwise store the global 0x598d40 at
 * +0x1d4 and call 0x48c9b0 on the object, +0x1d0 and a size of eight. */
uint32_t vertrix_object_notify_global(const VertrixCalls *calls, uint32_t object, void *storage,
                                      size_t size, uint32_t global);

/* Original 0x48c2b0: store the first byte (0x532a68) at +0x1e1 when the dword at +0x44 is one,
 * the second (0x532a6c) otherwise, then 0x48c9b0 on the object, +0x1e0 and two. */
uint32_t vertrix_object_notify_choice(const VertrixCalls *calls, uint32_t object, void *storage,
                                      size_t size, uint8_t enabled_value, uint8_t disabled_value);

/* Original 0x48c2e0: store the byte (0x532a70) at +0x1e3, then when the dword at +0x44 is one
 * 0x48c9b0 on the object, +0x1e2 and two; zero otherwise. */
uint32_t vertrix_object_notify_byte(const VertrixCalls *calls, uint32_t object, void *storage,
                                    size_t size, uint8_t value);

/* Original 0x4b4cb0: vertrix_object_glyph_present (0x4b6a10) on the object that +0x160 names. */
uint32_t vertrix_object_parent_glyph(const VertrixCalls *calls,
                                     const VertrixFactoryServices *services, const void *storage,
                                     size_t size, uint32_t edx);

/* Original variants 0x4b78d0, 0x48d520: tables 0x518704 and 0x517a94,
 * respectively. 0x4d8650, then the table stored at +0 of the object it
 * returns, which is returned. */
uint32_t vertrix_object_table_new(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  uint32_t eax, uint32_t edx, uint32_t table);

/* Original 0x4b7a80: the dword at +8 of the object 0x4b79c0 returns, zero when there is none. */
uint32_t vertrix_object_first_field8(const VertrixCalls *calls,
                                     const VertrixFactoryServices *services, uint32_t eax,
                                     uint32_t edx);

/* Original 0x4b4660: one when the length of the string at the pointer in the object named by
 * +0x160 (at its +0x15c), minus one, equals the dword at +0x170. */
uint32_t vertrix_object_text_length_matches(const VertrixFactoryServices *services,
                                            const void *storage, size_t size);

/* Original 0x4b4690: clamp the dword at +0x170: below minus one it becomes minus one, and when the
 * text length is not above it, length minus one. Always returns zero. */
uint32_t vertrix_object_clamp_text_length(const VertrixFactoryServices *services, void *storage,
                                          size_t size);

/* Original 0x4c3fa0: store the five method addresses 0x4c3e40, 0x4c3ea0, 0x4c3e60, 0x4c3ed0 and
 * 0x4c3f80 at +0 to +0x10 and the fixed words of the record. Returns zero for short storage. */
int vertrix_object_init_4c3fa0(void *storage, size_t size);

/* Original 0x47f070: clear the dword at +0xc and copy the 16 bytes at 0x558ce0 to +0xa4. */
int vertrix_object_reset_block(void *storage, size_t size, const uint8_t *source);

/* Original 0x47f260: the address of the +0x50 member of the chain entry 0x47f190 returns for edx,
 * zero when there is none. */
uint32_t vertrix_object_chain_member(const VertrixCalls *calls, uint32_t eax, uint32_t edx);

/* Original 0x475a20: 0x475af0 on the object, clear the dwords at +0x3c to +0x54 (the seven the
 * original zeroes: 0x44, 0x40, 0x3c, 0x48, 0x4c, 0x50, 0x54), then 0x475790 on object + 4 with a
 * zero stack argument and 0x4759e0 on the object. Returns the last eax. */
uint32_t vertrix_object_list_init(const VertrixCalls *calls, uint32_t object, void *storage,
                                  size_t size, uint32_t edx, uint32_t ebx, uint32_t ecx);

/* Original 0x4762e0: select the 96-byte slot of the 16-bit index inside the table at eax, store
 * its address in *selected (global 0x54d630) and, when its first byte is one, 0x475790 on slot + 4
 * with a zero stack argument; otherwise return the slot address. */
uint32_t vertrix_slot_select(const VertrixCalls *calls, uint32_t table, const void *storage,
                             size_t size, uint32_t index, uint32_t *selected);

/* Original 0x478c90: copy the text to the buffer (the global 0x558970), then 0x40a860 on eax, the
 * buffer address and 0x64 with ecx = eax. Returns its eax, zero for a missing terminator. */
uint32_t vertrix_literal_copy_call(const VertrixCalls *calls, uint32_t eax, uint8_t *buffer,
                                   size_t buffer_size, const uint8_t *text, size_t text_size);

/* The length of the text that +0x160 and then +0x15c of the object lead to (the scan of 0x4b4660,
 * 0x4b4690 and 0x4b4630). Returns zero when it does not resolve or has no terminator. */
int vertrix_object_text_length(const VertrixFactoryServices *services, const void *storage,
                               size_t size, uint32_t *length);

/* Original 0x45d820: with a non-zero count, 0x4b65a0(object, ecx = step, stack 1) and 0x4ac980
 * give two words that 0x4b6540 consumes; when the second equals the step (zero for a state of 1,
 * -10 otherwise) the state at +0x64 is flipped. Returns eax; `ebx` and `edx` are the caller's. */
uint32_t vertrix_object_step_toggle(const VertrixCalls *calls, uint32_t object, void *storage,
                                    size_t size, uint32_t edx, uint32_t ebx);

/* Original 0x4b5420, a Delphi destructor wrapper: unless bit 2 of the flags is set, the class
 * pointer at +0x158 becomes 0x518174, 0x4ac130(object, 1) runs and 0x4ca050 follows when bit 1
 * is set; with bit 2 set only 0x4ccb9f(object, 0x518190) and 0x4ca040 run. The exception frame
 * leaves no state. Returns the object or the result of 0x4ac130. */
uint32_t vertrix_object_destroy_call(const VertrixCalls *calls, uint32_t object, void *storage,
                                     size_t size, uint32_t flags);

/* Original 0x48a620: the class pointer at +0x110 becomes 0x517684, +0, +4 and +8 are cleared and
 * the text "UNKNOWN" is stored at +0xc. Returns the object. */
uint32_t vertrix_object_unknown_init(void *storage, size_t size, uint32_t object);

/* Original 0x48a8c0: a non-null owner (the dword at +0) first goes through 0x478d80; then +0, +4
 * and +8 are cleared and "UNKNOWN" stored at +0xc. `ebx` is the caller's register. Returns eax,
 * the callee's result or the object with its low byte cleared. */
uint32_t vertrix_object_unknown_reset(const VertrixCalls *calls, void *storage, size_t size,
                                      uint32_t object, uint32_t ebx);

/* Original 0x48a380 (the stream is edx): with 0x48a910 saying the stream is not at its end, reads
 * one byte (through the handle 0x48aa80 returns), advances with 0x48aa90 and repeats until a line
 * feed or carriage return. `ebx` is the caller's register; its low byte follows the bytes read.
 * Returns eax. */
uint32_t vertrix_stream_skip_line(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  uint32_t stream, uint32_t ebx);

/* Original 0x4ad720: moves the value at +0x58 towards the one at +0x5c by the amount of 0x4aca00
 * (stack argument: the dword at +0x60; edx is the caller's) and stores it back. Returns whether the
 * result differs from the target. */
uint32_t vertrix_object_step_field(const VertrixCalls *calls, void *storage, size_t size,
                                   uint32_t edx);

/* Original 0x481f30: 0x4ccf3b(eax, 0xa, 0x516ba0) creates an object whose +0x20c becomes
 * 0x516b84; 0x482050 initialises it. Returns the object. */
uint32_t vertrix_object_create_with_class(const VertrixCalls *calls,
                                          const VertrixFactoryServices *services, uint32_t eax);
/* Original 0x48a310 (eax = object kept in ebx, edx = stream): skips blanks (space, line feed,
 * carriage return) and, for '/', the rest of the line (0x48a380, vertrix_stream_skip_line), one
 * 0x48aa90 advance each, until 0x48a910 reports the end (returned) or another character is next
 * (returned in the low byte of the peeked handle). */
uint32_t vertrix_stream_skip_blank(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services, uint32_t stream,
                                   uint32_t object, uint32_t edx);

/* Original 0x477d70 (eax = object; width and height are the words at 0x5b9c8e and 0x5b9c90):
 * 0x477e10(object, 0, 0, width - 1, stack: height - 1) and 0x478480(object, width / 2, height / 2),
 * then the four dwords from +0x64 are cleared. Returns the eax of 0x478480. */
uint32_t vertrix_object_center_setup(const VertrixCalls *calls, void *storage, size_t size,
                                     uint32_t object, uint32_t width, uint32_t height);

/* Original 0x4b2400: 0x4abd70 and 0x4ca070 (at +0x15c) build the object, 0x4ca370 assigns the
 * literal 0x511082 to its name, then the class pointer and the fields at +0x160, +0x2f2..+0x2f8,
 * +0x94, +0x95 (3) and +0x2fc..+0x304 are initialised. Returns the object (the original's eax). */
uint32_t vertrix_object_construct_labeled(const VertrixCalls *calls,
                                          const VertrixFactoryServices *services, uint32_t eax);

/* Original 0x4b6350: the constructor of vertrix_object_construct_labeled for class 0x518404, name
 * literal 0x5110b7 and the field set +0x160..+0x17c (0xff9c at +0x17a and +0x17c). */
uint32_t vertrix_object_construct_labeled_box(const VertrixCalls *calls,
                                              const VertrixFactoryServices *services, uint32_t eax);

/* Originals 0x4b5dc0, 0x481fb0 and 0x429350: destructors taking the Delphi flags in edx (4: only
 * the 0x4ccb9f / 0x4ca040 pair, 2: free the instance through 0x4ca050). They store the class
 * pointer (0x518344 at +0, 0x516b84 at +0x20c and 0x514554 at +0x228) and the first two call
 * 0x4d86d0(object, 1) and 0x4823b0(object, 0). Each returns the original's eax. */
uint32_t vertrix_object_destroy_a(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  uint32_t object, uint32_t flags);
/* Original0x481fb0: Destructor described above, with class 0x516b84 at +0x20c. */
uint32_t vertrix_object_destroy_b(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  uint32_t object, uint32_t flags);
/* Original0x429350: Destructor described above, with class 0x514554 at +0x228. */
uint32_t vertrix_object_destroy_c(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  uint32_t object, uint32_t flags, uint32_t ebx);

/* Originals 0x4b6460 (class 0x518404 at +0x158; 0x4ca210 on +0x15c, 0x4ac130(base, 1)) and 0x488b90
 * (class 0x5174b4 at +0; 0x4d7630(object, 0) and (object, 1)): destructors in the style of
 * vertrix_object_destroy_a. Each returns the original's eax. */
uint32_t vertrix_object_destroy_d(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  uint32_t object, uint32_t flags);
/* Original0x488b90: Destructor described above, with class 0x5174b4 at +0. */
uint32_t vertrix_object_destroy_e(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  uint32_t object, uint32_t flags);

/* Original 0x477e30 (eax = object, edx = ecx, ebx): while the dword at +0x60 is zero, copy the
 * words +0x48/+0x4a to +0x50/+0x52, store half the screen size at +0x5c/+0x5e, set +0x60 to 1 and
 * keep ebx and ecx at +0x54/+0x58, run vertrix_center_setup, then 0x477e10 with the box of half
 * size ecx around the centre. Returns its eax, or the object when the state was already set. */
uint32_t vertrix_object_center_place(const VertrixCalls *calls, void *storage, size_t size,
                                     uint32_t object, uint32_t ebx, uint32_t ecx, uint32_t width,
                                     uint32_t height);

/* Original 0x424760 (eax = object): vertrix_object_center_place on the global object 0x5588f8 with
 * ebx 0x3c and ecx 0xc8, then 0x418840(object, 0x424990) with the ebx the placement left behind.
 * Returns the eax of 0x418840. */
uint32_t vertrix_object_center_titled(const VertrixCalls *calls,
                                      const VertrixFactoryServices *services, uint32_t object,
                                      uint32_t width, uint32_t height);

/* Original 0x488b10 (eax = object; frame is the token for ebp, the exception frame being ignored):
 * 0x4d7510 creates the object, whose class is set to 0x5174b4; the local at frame - 0x30 is then
 * initialised by 0x4d7510 and released by 0x4d7630. Returns the created object. */
uint32_t vertrix_object_construct_e(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services, uint32_t frame,
                                    uint32_t object);

/* Original 0x475ec0 (eax = object): 0x4ccf3b creates the table object (0x100 rows of 0x60 bytes),
 * whose class at +0x6000 is set to 0x5165e4 and whose row words at +0x58 are numbered 0..0xff;
 * 0x476090, 0x4760f0 and 0x4766b0 follow, with the global 0x553648 (*flag) set to one before the
 * last. Returns the created object. */
uint32_t vertrix_object_construct_f(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services, uint32_t object,
                                    uint32_t *flag);

/* Original 0x487b00 (eax = object; frame as for vertrix_object_construct_e, one return address
 * above its ebp): vertrix_object_construct_e, then the class 0x516f04 and the dwords +0x10..+0x20
 * cleared. Returns the created object. */
uint32_t vertrix_object_construct_g(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services, uint32_t frame,
                                    uint32_t object);

/* Original 0x47faf0 (eax = object, edx = the zero-terminated text): an empty text returns zero;
 * otherwise at most 0x100 bytes of it are copied to +0xb9 and terminated, and 0x47fa40(object,
 * object + 0xb8, the dword at +0x38, 0x102) runs. Returns its eax. */
uint32_t vertrix_object_set_text(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                 uint32_t object, const uint8_t *text);

/* Original 0x4d8b80 (eax = object, edx = flags, ebx the caller's): bit 4 skips the destruction
 * (0x4ccb9f, 0x4ca040 on the literal 0x516f80); otherwise the class 0x51a1b4 is stored, 0x4d8b30
 * runs, the class becomes 0x517454 and bit 2 frees the object through 0x4ca050. Returns the
 * object. */
uint32_t vertrix_object_destroy_g(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  uint32_t object, uint32_t flags, uint32_t ebx);

/* Original 0x48a670 (eax = object, edx = flags, ebx the caller's; the exception frame is
 * ignored): bit 4 skips the destruction (0x4ccb9f on the literal 0x513310, then 0x4ca040 with edx
 * zero); otherwise the class 0x517684 is stored at +0x110, vertrix_object_unknown_reset runs with
 * ebx 0x4ec1ec and bit 2 frees the object through 0x4ca050. Returns the object. */
uint32_t vertrix_object_destroy_h(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  uint32_t object, uint32_t flags, uint32_t ebx);

/* Original 0x47f280 (eax = object, edx = index, ecx the caller's): 0x47fbb0(object, the list head
 * at +0xc, index, ecx) fills a 16 byte local (`scratch`, written through esi), which is copied to
 * +0xa4. Then the list is walked `index` links (+0x60); when it ends first zero is returned,
 * otherwise the 16 bytes at node + 8 are copied to +0xa4 and one is returned. */
uint32_t vertrix_object_pick_entry(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services, uint32_t object,
                                   uint32_t index, uint32_t ecx, const uint8_t scratch[16]);

/* Original 0x4c0b51 (eax = object): one when the object has +0x4c and +0x12c clear, +0x28 and +0x24
 * three, +0x2c two and +0x78 three, and the object B at +0xd8 has +8 two, +0x5c, +0xb0, +0x60 and
 * +0xb4 one, +0xc at most two (signed) and +0x24, +0x78 and +0xcc all equal to the +0x13c of the
 * object;
 * otherwise zero (also when a field does not resolve). */
uint32_t vertrix_object_is_idle(const VertrixFactoryServices *services, uint32_t object);

/* Original 0x427ae0 (eax = object, edx = second, ebx the caller's; `frame` is the token for ebp,
 * the frame holds two 0x41 byte copies of the areas at +0x1de of the text records, returned in
 * first_copy (frame - 0xa4, from the second object's record) and second_copy (frame - 0x60, from
 * the link's record) for the callees to read). The text
 * records at +0x15c of the second object and of its link (+0x3b0) go through 0x432820 twice,
 * 0x428110 takes the two local copies and the object's scratch area (+0x1c5), 0x427c10 measures
 * with the regions of the second object and its link, and 0x428610's byte classifies the result:
 * below three one, up to five zero, above five -1. */
uint32_t vertrix_object_compare_regions(const VertrixCalls *calls,
                                        const VertrixFactoryServices *services, uint32_t frame,
                                        uint32_t object, uint32_t second, uint32_t ebx,
                                        uint8_t first_copy[0x41], uint8_t second_copy[0x41]);

/* Original 0x40ef90 (eax = object, edx, ebx and ecx the caller's): zero object returns two.
 * Otherwise the records array at +0x150 (0xc bytes each, word count at +0x28) has the pointers at
 * +8 released through 0x4ea190, then the array itself; the blocks array at +0x154 (0xfc bytes
 * each, word count at +0x2a) has the items of every block (pointer at +0xf8, word count at +0x80,
 * 0x3c bytes each from +0x24) released through 0x40aca0, then the items array, and finally the
 * blocks array and the object are released. The register arguments of those calls are the loop
 * state of the original. Returns zero. */
uint32_t vertrix_object_free_tree(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  uint32_t object, uint32_t edx, uint32_t ebx, uint32_t ecx);

/* Original 0x40f910 (eax = object, edx = source): 0x4eb860 runs first; a source whose size (+0x18)
 * is zero returns zero. Otherwise 0x4ec160 allocates an item (zero returns 8): the object's word
 * +0x80 becomes one and its slot +0xf8 the item; the item takes the size, the bytes at source
 * +0x25/+0x24 (to +0x20/+0x23) and the mark 0x80 at +0x21, and when low + 2 < high <= size
 * (source +0x1c, +0x20) the range with the flag 0x10. 0x40ac50 attaches the buffer pointer (stored
 * at item +0x24, a non-zero result is returned), 0x40c220 fills it, every byte is flipped with
 * 0x80 and 0x40acd0 finishes. Returns zero. */
uint32_t vertrix_object_attach_item(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services, uint32_t object,
                                    uint32_t source);

/* Original 0x43ab80 (eax = object, ebx the caller's; `frame` is the token for the entry esp minus
 * 4 as for the other wrappers): three when the byte at +0x4c5 is zero, five when that of its link
 * (+0x3b0) is zero; otherwise vertrix_object_compare_regions(the object at +0x450, object) decides:
 * -1 gives three, zero four and anything else five. The copies are those of the comparison. */
uint32_t vertrix_object_region_verdict(const VertrixCalls *calls,
                                       const VertrixFactoryServices *services, uint32_t frame,
                                       uint32_t object, uint32_t ebx, uint8_t first_copy[0x41],
                                       uint8_t second_copy[0x41]);

/* Original 0x440ca0 (eax = object, dx, bx and cx the caller's words, ret 0x10 with the arguments
 * arg1..arg4 at ebp + 8..0x14; frame is the token for ebp, the exception frame being ignored; the
 * original's eax is the restored exception chain). 0x4408e0 takes the sign extended low bytes and
 * words as registers (dl, bx, cx, arg1), arg2's low word, arg3, the byte at +0x44 of arg4 and four
 * pointers to locals (frame - 0x1c, -0x18, -0xc, -0x10) of which it stores the dwords at -0xc
 * and -0x10 (the callee's results `out_ecx` and `out_ebx` of the site) for 0x440a20(object, dl,
 * word(-0xc), word(-0x10), arg3, arg4). Returns that call's eax. */
uint32_t vertrix_object_corner_call(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services, uint32_t frame,
                                    uint32_t object, uint32_t edx, uint32_t ebx, uint32_t ecx,
                                    const uint32_t arguments[4]);

/* Original 0x43dff0 (eax = object, edx, ebx and ecx the caller's registers, which the first
 * allocation sees): the dword at +0x94c is set to one; then 500 items (0x4ca000(0x15c), a non-zero
 * result going through 0x4abd70; 0x4adf20 with five zero stack arguments; 0x43dea0(object, item);
 * the item's delay at +0x58 is a 0x4826c0(0x598d30, 0xc8) draw masked to 16 bits) are stored at
 * +0x15c + 4 * i, and 8 more (flag byte +0x94 set, 0x43dc80 instead of 0x43dea0) at +0x92c + 4 *
 * i. The register arguments of each call are the loop state of the original. Returns the
 * object + 0x1c the original leaves in eax. */
uint32_t vertrix_object_populate(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                 uint32_t object, uint32_t edx, uint32_t ebx, uint32_t ecx);

/* Original 0x477ed0: unless the dword at +0x60 is 1 nothing happens and the object is returned.
 * Otherwise it is cleared, vertrix_object_center_setup runs, 0x478480(object, word +0x50,
 * word +0x52) and 0x478460(object) follow. Returns the eax of 0x478460. */
uint32_t vertrix_object_reset_center(const VertrixCalls *calls, void *storage, size_t size,
                                     uint32_t object, uint32_t width, uint32_t height);

/* Original 0x4d3f70 (eax = object, edx = flags): the destructor of the object holding a name at
 * +0xac. Bit 4 skips the destruction (0x4ccb9f, 0x4ca040 on the literal 0x5199f0); otherwise the
 * class 0x5198f4 is stored and 0x4d4060, 0x4ca210 (name), 0x4d83f0 and 0x4d01a0 walk the bases
 * (-0x40, -0x6c); bit 2 frees the result through 0x4ca050. Returns the final eax. */
uint32_t vertrix_object_destroy_f(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  uint32_t object, uint32_t flags);

/* Original 0x48a3c0 (ebx = object, edx = stream): assigns 0x510a59 to the object (0x4ca370), then
 * until 0x48a910 reports the end appends each byte read through 0x48aa80 (0x48aa90 advances one)
 * with 0x4ca630, stopping after a backslash, line feed or carriage return, which is not appended.
 * 0x4ce030 and 0x4cdfe0 finish the object; the latter's eax is returned. */
uint32_t vertrix_stream_read_token(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services, uint32_t stream,
                                   uint32_t object);
/* Original 0x48a420 (eax = object, edx = stream): skips spaces; a '/' is followed by the rest of
 * the line (0x48a380), a line break by one advance, both returning zero; another character
 * returns one without being consumed; the end of the stream returns zero. */
uint32_t vertrix_stream_next_directive(const VertrixCalls *calls,
                                       const VertrixFactoryServices *services, uint32_t object,
                                       uint32_t stream);

/* Original0x43d320: call virtual slot 6 (offset 0x18) of the object whose
 * handle is the dword at holder +0x468, with that object in eax, its class
 * token in edx and the caller's ebx/ecx. Original addresses resolve through
 * read; the method runs through the calls boundary. Returns the method's
 * eax, or zero when storage is short or an address is unreadable. */
uint32_t vertrix_object_virtual_slot6(const VertrixCalls *calls, VertrixMemoryRead read,
                                      void *read_context, const void *storage, size_t size,
                                      uint32_t ebx, uint32_t ecx);

/* Original0x418850: when the dword at +0xbc is nonzero, call it with the
 * object in eax and edx (plus the caller's ebx/ecx); otherwise return the
 * object unchanged. A second routine clears the slot. Returns zero when
 * storage is short. */
uint32_t vertrix_object_invoke_callback(const VertrixCalls *calls, uint32_t object,
                                        const void *storage, size_t size, uint32_t ebx,
                                        uint32_t ecx);

#endif
