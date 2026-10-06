#ifndef VERTRIX_RTL_GLUE_H
#define VERTRIX_RTL_GLUE_H
#include <stddef.h>
#include <stdint.h>

#include "block_factory.h"
#include "call_glue.h"

/* Thin wrappers of the Delphi runtime (0x4c9000..0x4df000): per-thread record accessors, flagged
 * dispatchers and string helpers. The routines they call are runtime internals and stay behind the
 * call boundary; records are reached through the factory services. */

/* Original 0x4cbe80: the dword at +4 of the record 0x4ce780 returns. 0x4cba60: the dword at +0xc8
 * of the record 0x4ce220 returns. `target` is the record routine, `offset` the field. */
uint32_t vertrix_rtl_record_field(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  uint32_t target, uint32_t offset, uint32_t eax, uint32_t edx,
                                  uint32_t ebx, uint32_t ecx);

/* Original 0x4dec60: increments the dword at +0x10 of the record 0x4ce780 returns. Returns the
 * record. */
uint32_t vertrix_rtl_record_increment(const VertrixCalls *calls,
                                      const VertrixFactoryServices *services, uint32_t eax,
                                      uint32_t edx, uint32_t ebx, uint32_t ecx);

/* Original 0x4dd170 (ret 4): stores the stack argument at +0x30 of the record 0x4ce740 returns.
 * Returns the record. */
uint32_t vertrix_rtl_record_set_argument(const VertrixCalls *calls,
                                         const VertrixFactoryServices *services, uint32_t eax,
                                         uint32_t edx, uint32_t ebx, uint32_t ecx,
                                         uint32_t argument);

/* Original 0x4d16b0: 0x4cba70 initialises the record; +0x24 becomes 0x519724 and +0x28 one.
 * Returns the record. */
uint32_t vertrix_rtl_record_mark(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                 uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx);

/* Original 0x4cba70: clears a record, its class pointer (+0x24) becoming 0x518d14. */
uint32_t vertrix_rtl_record_clear(const VertrixFactoryServices *services, uint32_t record);

/* Original 0x4c9daf (0x4db719, ebx 0), 0x4c9dd6 (0x4db710, ebx 2) and 0x4c9e00 (0x4db7c8, ebx 1):
 * with the flag byte at 0x5054a1 set the first routine runs, otherwise 0x4c9b6a with ebx the
 * given value. Returns its eax. */
uint32_t vertrix_rtl_flagged_call(const VertrixCalls *calls, uint32_t flag, uint32_t direct,
                                  uint32_t fallback_ebx, uint32_t eax, uint32_t edx, uint32_t ebx,
                                  uint32_t ecx);

/* Original 0x4dd440 (0x4dd3e0) and 0x4ddc40 (0x4ddbe0), ret 4: `first`(1, stack argument), then
 * 0x4ded70. Returns its eax. */
uint32_t vertrix_rtl_pair_call(const VertrixCalls *calls, uint32_t first, uint32_t argument,
                               uint32_t ebx, uint32_t ecx);

/* Original 0x4c98f0: 0x4eb5c0(eax, 0, ebx = edx). 0x4d4990: 0x4d49a0 with ebx the dword edx points
 * at. 0x4cd836: 0x4e0eaf, then 0x4e0ec7(result, edx = eax). Each returns the callee's eax. */
uint32_t vertrix_rtl_zero_call(const VertrixCalls *calls, uint32_t eax, uint32_t edx, uint32_t ecx);
uint32_t vertrix_rtl_deref_call(const VertrixCalls *calls, uint32_t eax, uint32_t edx,
                                uint32_t pointed, uint32_t ecx);
uint32_t vertrix_rtl_chain_call(const VertrixCalls *calls, uint32_t eax, uint32_t edx,
                                uint32_t ebx);

/* Original 0x4c9840: rounds eax up to a multiple of edx (signed). */
int32_t vertrix_round_up(int32_t value, int32_t multiple);

/* Original 0x4ca180: a string variable (eax) whose text, `refcount` references, is a literal when
 * negative: 0x4ca370(eax, 0x5c5c00) then, otherwise 0x4ca110(eax, edx = text - 0xc). Returns eax.
 * 0x4ca1e0: unless the text is shared (refcount > 1) or too small (edx > capacity), nothing;
 * otherwise 0x4ca110(var) and 0x4ca0d0(var, edx); it returns the text header (text - 0xc) when
 * nothing is called. */
uint32_t vertrix_rtl_string_unique(const VertrixCalls *calls, uint32_t variable, uint32_t text,
                                   int32_t refcount, uint32_t ebx, uint32_t ecx);
uint32_t vertrix_rtl_string_reserve(const VertrixCalls *calls, uint32_t variable, uint32_t text,
                                    uint32_t edx, int32_t refcount, uint32_t capacity,
                                    uint32_t ebx);

/* Original 0x4cb460: initialises a stream object (class pointer 0x518cb4 at +0, then +4 = 1,
 * +0x14 = 1 and zeros). Returns the object. */
uint32_t vertrix_rtl_stream_init(const VertrixFactoryServices *services, uint32_t object);

/* Original 0x4cbf10: 0x4cb460, then the derived class pointer 0x518e24, zeros at +0x4c and +0x50
 * and 0x4cbf90(object, object). Returns the object. */
uint32_t vertrix_rtl_stream_init_derived(const VertrixCalls *calls,
                                         const VertrixFactoryServices *services, uint32_t object,
                                         uint32_t ebx, uint32_t ecx);

/* Original 0x4ccb9f: zero for a null pointer, otherwise 0x4cea15(eax, edx = the dword before the
 * block `header`, ebx = edx) and the block address eax - 4. */
uint32_t vertrix_rtl_block_call(const VertrixCalls *calls, uint32_t eax, uint32_t edx,
                                uint32_t header);

/* Original 0x4cd0a4: 0x4df320(eax, edx, ebx, ecx = 0x4cd090) returns a length; the byte at that
 * index of `buffer` (the text eax addresses) becomes zero. Returns the length. */
uint32_t vertrix_rtl_terminate_call(const VertrixCalls *calls, uint32_t eax, uint32_t edx,
                                    uint32_t ebx, char *buffer, size_t size);

/* Original 0x4cd9f0 (local at `local`): 0x4e0f8b, then 0x4cd8b0(eax, edx = &local, ebx = edx).
 * Returns its eax. */
uint32_t vertrix_rtl_local_call(const VertrixCalls *calls, uint32_t local, uint32_t eax,
                                uint32_t edx, uint32_t ebx);

/* Original 0x4cfa10: the address of the runtime's class record 0x4cf9d0. */
uint32_t vertrix_rtl_class_address(void);

/* Original 0x4d67b2: 0x4d67e4 with the low byte of ecx set to 0x9f. Returns its eax. */
uint32_t vertrix_rtl_mode_call(const VertrixCalls *calls, uint32_t eax, uint32_t edx, uint32_t ebx,
                               uint32_t ecx);

/* Original 0x4ce9fd: a variable whose first dword `inner` is non-zero goes through 0x4ce9c0.
 * Returns the variable. */
uint32_t vertrix_rtl_release_inner(const VertrixCalls *calls, uint32_t variable, uint32_t inner,
                                   uint32_t edx, uint32_t ebx);

/* Original 0x4d4060: 0x4ce780 returns a record; 0x4dba20 gets its address + 8 and the original
 * eax. Returns its eax. */
uint32_t vertrix_rtl_record_forward(const VertrixCalls *calls, uint32_t eax, uint32_t edx,
                                    uint32_t ecx);

/* Original 0x4cf8e0 (ret 4): 0x4cf880(1, argument), 0x4ded70 on its result and 0x4cce90 on both.
 * Returns the second result. */
uint32_t vertrix_rtl_triple_call(const VertrixCalls *calls, uint32_t argument, uint32_t ebx,
                                 uint32_t ecx);

/* Original 0x489470 (ebp = frame, length local at frame-0x18): 0x4d79c0(eax, &length, 4, length)
 * and 0x4d79c0(eax, text, length, length) where `length` is the length of the text edx points
 * at. Returns the second eax. */
uint32_t vertrix_rtl_write_text_call(const VertrixCalls *calls, uint32_t frame, uint32_t eax,
                                     uint32_t text, uint32_t length);
/* Originals 0x4ca630 (target 0x4ca5a0) and 0x4cdad0 (target 0x4ca2e0): the low byte of edx is
 * stored in a one-byte local at `local` (the frame's esp), the target gets edx = 1 and ebx = local.
 * The original eax is returned. */
uint32_t vertrix_rtl_byte_local_call(const VertrixCalls *calls, uint32_t target, uint32_t local,
                                     uint32_t eax);

/* Original 0x4d3020: edx zero returns 0; otherwise 0x4d3010(edx, eax) decides: non-zero returns
 * edx, zero returns 0. */
uint32_t vertrix_rtl_swapped_call(const VertrixCalls *calls, uint32_t eax, uint32_t edx,
                                  uint32_t ebx);

/* Original 0x4d8082: three-way compare of two sign-magnitude values; returns 0 when equal,
 * otherwise 1 or 0xffffffff from the sign bit. */
uint32_t vertrix_rtl_sign_compare(uint32_t a, uint32_t b);

/* Originals 0x4d9510, 0x4d9530 and 0x4dde50: 0x4da71b(eax = the frame's one-dword local, edx = the
 * static table). The local holds a constant the original stores first. Returns its eax. */
uint32_t vertrix_rtl_static_init_call(const VertrixCalls *calls, uint32_t local, uint32_t table,
                                      uint32_t ebx, uint32_t ecx);

/* Original 0x4dad2e: 0x4dad38 with ebx = edx. Returns its eax. */
uint32_t vertrix_rtl_ebx_from_edx_call(const VertrixCalls *calls, uint32_t eax, uint32_t edx,
                                       uint32_t ecx);

/* Original 0x4dad19 (entered with edx): 0 for zero, 0xffffffff for a negative value, else 1. */
uint32_t vertrix_rtl_sign_of(uint32_t value);

/* Originals 0x4dabe0 (target 0x4e2434) and 0x4dacf8 (target 0x4dacd0): both stack arguments go in
 * eax and edx, ebx is the address of a local holding the address of the third stack slot. Returns
 * the target's eax. */
uint32_t vertrix_rtl_stack_pair_call(const VertrixCalls *calls, uint32_t target, uint32_t local,
                                     uint32_t first, uint32_t second, uint32_t ecx);

/* Original 0x4db866 (ebp = frame, the eax/edx pair stored at frame-8): the kind is ebx & 0x1f;
 * 0x1040 is or-ed in when it is 8 or edx is non-zero, else 0x1080. Reaches 0x4dad38 (through
 * 0x4dad2e) with the address of the pair in edx and ebx. Returns its eax. */
uint32_t vertrix_rtl_flags_call(const VertrixCalls *calls, uint32_t local, uint32_t edx,
                                uint32_t ebx, uint32_t ecx);

/* Original 0x4db10a: `pair` is the frame's saved edx/eax pair (esp - 8), `scratch` the twelve byte
 * block below it. 0x4e53b4(pair, scratch), 0x4db131(scratch) and 0x4e543c(scratch, pair). Returns
 * the original eax. */
uint32_t vertrix_rtl_scratch_triple_call(const VertrixCalls *calls, uint32_t pair, uint32_t scratch,
                                         uint32_t eax, uint32_t ebx, uint32_t ecx);

/* Original 0x4da66e: 0x4da3ba(0, 0, 0) under an exception frame that is restored afterwards. The
 * original's eax is the restored exception chain, so the native returns 0. */
uint32_t vertrix_rtl_zero_call3(const VertrixCalls *calls, uint32_t ecx);

/* Originals 0x4dd360 and 0x4d9280 (constructors under an exception frame): store the class pointer
 * and the initial fields (0x51b5d4, 0, 0, 0 and 0x517474, 1) at the object. Return the object. */
uint32_t vertrix_rtl_construct_list(uint32_t object, uint8_t *storage);
uint32_t vertrix_rtl_construct_flag(uint32_t object, uint8_t *storage);

/* Original 0x4d82c6: fills the three float helper pointers at 0x503ea0..0x503ea8 from the byte at
 * 0x5054a1 (`fast_flag`) and bit 0 of the byte at 0x508798 (`mode_flags`). */
void vertrix_rtl_select_float_helpers(uint8_t fast_flag, uint8_t mode_flags, uint32_t table[3]);

/* Originals 0x4d8340 (class 0x51a024) and 0x4d8ab0 (class 0x51a1b4): constructors storing the
 * class, five zero dwords and `chunk_size` (edx) at +0x18. Return the object. */
uint32_t vertrix_rtl_construct_chunk_list(uint32_t object, uint8_t *storage, uint32_t class_pointer,
                                          uint32_t chunk_size);

/* Original 0x4ddc60: the dword at +4 is held; when it is non-zero 0x4ddbe0 decides whether 0x4df1c0
 * releases it. The dword is always cleared. Returns the held value. */
uint32_t vertrix_rtl_release_list_head(const VertrixCalls *calls,
                                       const VertrixFactoryServices *services, uint32_t object,
                                       uint32_t edx);

/* Original 0x4cf980: as 0x4ddc60 for the dword at +0x1c (cleared when held, 0x4cf880 decides) and
 * always clears +0x38. Returns the held value. */
uint32_t vertrix_rtl_release_string_member(const VertrixCalls *calls,
                                           const VertrixFactoryServices *services, uint32_t object,
                                           uint32_t edx);

/* Original 0x4dc160 (the table global at 0x5c77e8 passed as `table`): the key is the dword at the
 * object; zero key or table returns 0, otherwise 0x4dbcd0(table, key). Returns its eax. */
uint32_t vertrix_rtl_lookup_call(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                 uint32_t object, uint32_t table, uint32_t ebx, uint32_t ecx);

/* Original 0x4dfa7c: unless flag 8 at +0x1e is set or the byte at +0x16 differs from 0x30, the
 * dword at +4 minus the six dwords from +0x20 is added to the second of them when positive.
 * Returns the object. */
uint32_t vertrix_rtl_distribute_slack(uint32_t object, uint8_t *storage, size_t size);

/* Original 0x4deec0: constructor storing class 0x51bb54, 0, 0x11, three zero dwords and
 * `chunk_size` (edx) at +0x18. Returns the object. */
uint32_t vertrix_rtl_construct_table(uint32_t object, uint8_t *storage, uint32_t chunk_size);

/* Original 0x4d94a0: sets +0xc to 1, calls 0x4db950(+0x94 value, object + 0x14, 0x80) with
 * eax = object + 0x14 and ebx = object, then stores whether its result is non-zero at +0x10.
 * Returns that flag (the original's eax). */
uint32_t vertrix_rtl_probe_call(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                uint32_t object, uint32_t edx, uint32_t ecx);

/* Original 0x4d6775: converts an unsigned 32-bit integer to the double the original returns in
 * edx:eax (high half in the upper dword). */
uint64_t vertrix_rtl_integer_to_double(uint32_t value);

/* Original 0x4d67f0: converts the float bits to an integer, saturating to a right shift of all ones
 * when the biased exponent reaches `limit` (the low byte of ecx). */
uint32_t vertrix_rtl_float_to_integer(uint32_t bits, uint8_t limit);

/* Original 0x4ca3f0 (ret 4; `text` is the stack argument): nothing happens when edx + ecx is zero.
 * Otherwise 0x4ca0d0(variable, edx + ecx), then 0x4eb5e0 twice on the string the variable points at
 * (re-read after each call). Returns the last eax. */
uint32_t vertrix_rtl_string_append_pair(const VertrixCalls *calls,
                                        const VertrixFactoryServices *services, uint32_t variable,
                                        uint32_t edx, uint32_t ebx, uint32_t ecx, uint32_t text);

/* Original 0x4cda90 (the byte at esp is the low byte of edx): the variable takes the pointer the
 * 0x4ca060 result holds; a positive ebx grows it by 0x4ca0d0 and fills it through 0x4eb5c0 with the
 * sign-extended byte. Returns the variable. */
uint32_t vertrix_rtl_string_fill(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                 uint32_t variable, uint32_t edx, uint32_t ebx, uint32_t ecx);

/* Original 0x4ca240 (ret 4; `extra` is the stack argument): with extra + ebx zero the second
 * variable takes the pointer held by the 0x4ca060 result; otherwise 0x4ca0d0 sizes it and 0x4eb5e0
 * copies from the first variable's string + ecx. Returns the last eax. */
uint32_t vertrix_rtl_string_copy_pair(const VertrixCalls *calls,
                                      const VertrixFactoryServices *services, uint32_t first,
                                      uint32_t second, uint32_t ebx, uint32_t ecx, uint32_t extra);

/* Original 0x4ca670: when the string's header (12 bytes before the text) is shared or too small for
 * edx, the text is reallocated through 0x4ca0d0, copied with 0x4eb5e0 and the header's length is
 * rewritten before 0x4ca150 releases the old header. Returns the variable's string pointer. */
uint32_t vertrix_rtl_string_unique_size(const VertrixCalls *calls,
                                        const VertrixFactoryServices *services, uint32_t variable,
                                        uint32_t edx, uint32_t ebx);

/* Original 0x4ca6f0: makes the string unique and large enough (0x4ca670 with edx = ebx = length),
 * stores the length in the header and a terminating zero byte after the text. Returns the string
 * pointer. */
uint32_t vertrix_rtl_string_set_length(const VertrixCalls *calls,
                                       const VertrixFactoryServices *services, uint32_t variable,
                                       uint32_t length);

/* Originals 0x4cf320 (store_size = 0) and 0x4cf3a0 (store_size = 1, size = edx): 0x4cb460
 * initialises the stream, the class becomes 0x519664, 0x4eb5c0 clears the 0x20 bytes at +0x1c and a
 * non-zero size is then stored there. Returns the object. */
uint32_t vertrix_rtl_construct_buffer_stream(const VertrixCalls *calls,
                                             const VertrixFactoryServices *services,
                                             uint32_t object, uint32_t size, int store_size);

/* Original 0x4ca1a0: a string whose header (12 bytes before the text) is shared is copied:
 * 0x4ca110, 0x4ca0d0(variable, length) and 0x4eb5e0 from the old text with length + 1. An unshared
 * string is left alone. Returns the last eax, or the variable when nothing is done. */
uint32_t vertrix_rtl_string_make_unique(const VertrixCalls *calls,
                                        const VertrixFactoryServices *services, uint32_t variable,
                                        uint32_t edx);

/* Original 0x4d3120: walks the chain of dwords at +0x10 from `start`; returns 1 when `target` is
 * met, 0 at the end of the chain. */
uint32_t vertrix_rtl_class_chain_contains(const VertrixFactoryServices *services, uint32_t start,
                                          uint32_t target);

/* Original 0x4d8580: number of 16-bit units before the terminating zero. */
uint32_t vertrix_rtl_wide_length(const uint16_t *text);

/* Original 0x4d4390 (ret 8, arguments `candidate` and `start`): 1 when they are equal, otherwise
 * 0x4d1890 is applied repeatedly (each result is its next eax, edx and stack argument; the first
 * call gets the entry eax and `start`) until it returns 0 (result 0) or `candidate` (result 1). */
uint32_t vertrix_rtl_ancestor_search(const VertrixCalls *calls, uint32_t eax, uint32_t ecx,
                                     uint32_t candidate, uint32_t start);

/* Original 0x4df140 (ebx = `out`, a local at the frame's esp): 0x4df0f0(eax, edx) finds an entry;
 * its dword at +0xc is stored through `out` and 1 returned, or 0 when there is none. */
uint32_t vertrix_rtl_table_lookup_value(const VertrixCalls *calls,
                                        const VertrixFactoryServices *services, uint32_t local,
                                        uint32_t eax, uint32_t edx, uint32_t out);

/* Original 0x4d9930 (ret 8, arguments `first` and `second`): a zero first argument returns 0.
 * Otherwise 0x4d9ae0(first, first, second) and 0x4d9a10(its result). Returns the last eax. */
uint32_t vertrix_rtl_forward_pair(const VertrixCalls *calls, uint32_t edx, uint32_t ebx,
                                  uint32_t ecx, uint32_t first, uint32_t second);

/* Original 0x4ccee0 (its local at `frame_local`, the nested 0x4df140 frame twelve bytes below): an
 * owner whose slot at +0x38 is empty looks its key (+0x1c) up in the member's table (+0x34 + 0x20)
 * through 0x4df0f0. The entry's dword at +0xc is the target: the target's previous owner (+0x24)
 * is unlinked when it points back at it, then owner and target link to each other. Returns the
 * target, 0 for a failed lookup, or the owner when nothing is done. */
uint32_t vertrix_rtl_link_owner(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                uint32_t frame_local, uint32_t owner, uint32_t member);

/* Original 0x4d0b30 (ret 0x10, arguments base, first, second, value): scans 0x20-byte entries from
 * `base` until one with a zero dword at +0x10; an entry matches when its dwords at +0 and +4 equal
 * `first` and `second` and `value` lies in the unsigned range [+8, +0xc]. Returns its address, or
 * 0. `table` holds the bytes at `base`. */
uint32_t vertrix_rtl_range_table_find(const uint8_t *table, size_t size, uint32_t base,
                                      uint32_t first, uint32_t second, uint32_t value);

/* Original 0x4db6d9 (ebp frame saving ebx and ecx): 0x4db507(eax, edx, ebx = eax, ecx = edx), then
 * 0x4db6a4 on its result with the entry ebx and ecx, then 0x4db507 again. Returns the last eax. */
uint32_t vertrix_rtl_bracket_call(const VertrixCalls *calls, uint32_t eax, uint32_t edx,
                                  uint32_t ebx, uint32_t ecx);

/* Original 0x418760: the object 0x4d3e20 returns gets class 0x514284, byte +0xc8 and dword +0xd8
 * cleared. Returns it. */
uint32_t vertrix_rtl_construct_derived_stream(const VertrixCalls *calls,
                                              const VertrixFactoryServices *services, uint32_t eax,
                                              uint32_t edx, uint32_t ebx, uint32_t ecx);

/* Original 0x4decd0 (eax = object, edx = first, ebx = second, ecx): two table constructors
 * (0x4deec0 with 0xa at the object and with 4 at +0x1c), 0x4def50(object + 0x1c, 7), then first,
 * second and ecx are stored at +0x38, +0x3c and +0x40. Returns the object. */
uint32_t vertrix_rtl_construct_event_table(const VertrixCalls *calls,
                                           const VertrixFactoryServices *services, uint32_t object,
                                           uint32_t first, uint32_t second, uint32_t ecx);

/* Original 0x4d8620: 0x4d85f0 returns a slot; when it is non-zero the entry eax is stored there.
 * Returns the slot. */
uint32_t vertrix_rtl_store_in_slot(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services, uint32_t eax,
                                   uint32_t ebx, uint32_t ecx);

/* Originals 0x4cd544 (the first three stack arguments, `local` = the frame's one-dword local that
 * holds the address of the fourth) and 0x4cd520 (which pushes its first two arguments and a zero
 * for it): 0x4cd56c(first, second, third) with ecx = local. Returns its eax. */
uint32_t vertrix_rtl_vararg_call(const VertrixCalls *calls, uint32_t local, uint32_t first,
                                 uint32_t second, uint32_t third);

/* Original 0x4d66cd: the flag byte at the object is tested against `mask` (edx); when clear it is
 * set under the lock at 0x50817e (0x4e14b0 / 0x4e14b7, ebx = the result). Returns 1 when the mask
 * was already set, else 0. */
uint32_t vertrix_rtl_test_and_set(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  uint32_t object, uint32_t mask);

/* Originals 0x4cda12 and 0x4cda10 (the latter first zeroes eax): 0x4e0f8b(eax, edx, ebx, ecx = eax)
 * fills the frame local at `local`, then 0x4cd8b0(eax, local, ebx = `chain`, ecx = eax) with the
 * exception chain head read at entry. Returns its eax. */
uint32_t vertrix_rtl_local_chain_call(const VertrixCalls *calls, uint32_t local, uint32_t eax,
                                      uint32_t edx, uint32_t ebx, uint32_t chain);

/* Original 0x4ca430 (ret 0xc; arguments result, first, second): 0x4ca070(result), then 0x4ca3f0
 * appends the first string (edx = its length, ebx = its text) with the second string's length in
 * ecx and its text as the stack argument. Returns `result`. */
uint32_t vertrix_rtl_string_concat(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services, uint32_t result,
                                   uint32_t first, uint32_t second, uint32_t ebx, uint32_t ecx);

/* Original 0x4db1fd: splits a double (low, high dwords) into a mantissa in [0.5, 1) and the
 * exponent stored through ebx (frexp). A zero high dword gives exponent 0 and the value unchanged.
 * Returns the new value, high dword in the upper half. */
uint64_t vertrix_rtl_split_exponent(uint32_t low, uint32_t high, uint32_t *exponent);

/* Original 0x4d6710: skips white space (the class table at 0x507d58 marks 9 to 13 and 0x20), an
 * optional sign and parses decimal digits with 32-bit wrap-around. */
uint32_t vertrix_rtl_parse_integer(const uint8_t *text);

/* Original 0x4daab0 (eax = destination, edx = source, ebx = limit, ecx = capacity): a zero
 * destination returns 0. Otherwise 0x4e39a0 measures the source up to the smaller of limit and
 * capacity, 0x4e39d0 copies it, 0x4e39f0 returns the end offset and a zero byte is stored there.
 * Returns the offset. */
uint32_t vertrix_rtl_copy_terminated(const VertrixCalls *calls,
                                     const VertrixFactoryServices *services, uint32_t destination,
                                     uint32_t source, uint32_t limit, uint32_t capacity);

/* Original 0x4cdfe0: makes the string unique (0x4ca1a0), then walks it with 0x4e10d0 (white space
 * test) and 0x4e1054 (advance); the start of the final white space run is terminated with a zero
 * byte and the header's length set. Returns the header, or the last eax when nothing is trimmed. */
uint32_t vertrix_rtl_string_trim_end(const VertrixCalls *calls,
                                     const VertrixFactoryServices *services, uint32_t variable,
                                     uint32_t edx, uint32_t ebx);

/* Original 0x4ce030: makes the string unique, skips leading characters 0x4e10d0 accepts, moves the
 * rest down with 0x4e1140 and shortens the header's length. Returns the header. */
uint32_t vertrix_rtl_string_trim_start(const VertrixCalls *calls,
                                       const VertrixFactoryServices *services, uint32_t variable,
                                       uint32_t edx, uint32_t ebx);

/* Original 0x4dee73 (edx passed to 0x4e6220 is the ds selector): 0x4e6220(eax, ds) decides between
 * 0x4eb4d4(edx) and 0x4e6250(eax, edx). Returns the last eax. */
uint32_t vertrix_rtl_segment_dispatch(const VertrixCalls *calls, uint32_t eax, uint32_t edx,
                                      uint32_t data_segment);

/* Original 0x4dae4a: flips the sign bit of a double (low, high) unless it is zero. Returns the
 * value, high dword in the upper half. */
uint64_t vertrix_rtl_negate_double(uint32_t low, uint32_t high);

/* Original 0x4dae62: the same flip only when the sign bit is set. */
uint64_t vertrix_rtl_absolute_double(uint32_t low, uint32_t high);

/* Original 0x4df81c (eax = text at `base`, edx = the format record at `storage`): clears the flag
 * word at +0x1e, then consumes the flag characters '-' (8), '#' (1), '+' (4, clearing 2), ' '
 * (2 unless 4 is set) and '0' (the byte 0x30 at +0x16). Returns the address of the first other
 * character. */
uint32_t vertrix_rtl_parse_format_flags(const uint8_t *text, uint32_t base, uint8_t *storage,
                                        size_t size);

/* Original 0x4cdaf0 (eax = source variable, edx = destination, ebx = start): the start is clamped
 * to [0, length]; 0x4ca070 clears the destination and 0x4ca240 (the copy of the original, run as
 * vertrix_rtl_string_copy_pair) copies from there with ecx = length - start. Returns the
 * destination. */
uint32_t vertrix_rtl_string_tail(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                 uint32_t source, uint32_t destination, uint32_t start,
                                 uint32_t ecx);

/* Original 0x48d3e0: copies the first 0x34 bytes of the record at edx to the record at eax (bytes
 * 0..0xf, dwords 0x10..0x30). Returns the destination handle (eax is not changed by the original).
 */
uint32_t vertrix_record_copy(uint32_t destination, uint8_t *destination_storage,
                             const uint8_t *source_storage);

/* Original 0x4b8fbc (record: data pointer at +0, byte count at +8, flags byte at +0x16): turns the
 * data into running sums in place, 16-bit words (count / 2 of them) when flag 1 is set, else
 * bytes. */
void vertrix_record_prefix_sum(uint32_t count, uint32_t flags, uint8_t *data);

/* Original 0x481480 (a run-length decoder; eax = stream, edx = destination address, ebx = number of
 * input bytes, ecx = expected output size, its byte local at `local`): bytes below 0xc0 are copied
 * once, a byte of 0xc0 or more gives a run length of its value minus 0xc0 for the byte read next
 * (0x48a930 reads one byte through the local). When the output size is not exactly used up
 * 0x4d85c0 and 0x4eb4d4 report the error. The decoded bytes go to `output`. Returns 0 (the
 * original's eax is not defined). */
uint32_t vertrix_rle_decode(const VertrixCalls *calls, uint32_t local, uint32_t stream,
                            uint32_t destination, uint32_t remaining, uint32_t expected,
                            uint8_t *output);

/* Original 0x481580 (the run-length decoder of vertrix_rle_decode with the output count width *
 * height and no error exit): 0x478d10(width, height, 1) returns the bitmap whose first dword is the
 * pixel pointer, to which the run-length decoded bytes are written. Returns the bitmap. */
uint32_t vertrix_rle_decode_bitmap(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services, uint32_t local,
                                   uint32_t stream, uint32_t width, uint32_t height, uint32_t ecx,
                                   uint8_t *output);

/* Originals 0x4896f0, 0x489ba0 and 0x489640 (path splitting wrappers): the zero-terminated text is
 * copied to a global buffer (0x5ba0e0, 0x5baa08, 0x5b9cd0) and 0x4daae8 splits it into further
 * global buffers; 0x4ca370 and 0x4ca600 then assign the pieces to the caller's string variables.
 * Return the last eax. */
uint32_t vertrix_path_split_a(const VertrixCalls *calls, uint32_t variable, const uint8_t *text,
                              uint8_t *destination);
uint32_t vertrix_path_split_b(const VertrixCalls *calls, uint32_t variable, uint32_t edx,
                              const uint8_t *text, uint8_t *destination);
uint32_t vertrix_path_split_c(const VertrixCalls *calls, const uint8_t *text, uint32_t first,
                              uint32_t second, uint32_t third, uint32_t fourth,
                              uint8_t *destination);

/* Original 0x4d2390: with the scope record reached through 0x4ce740 (+4), raise 0x4de900 when the
 * object is the scope's owner (+0x1c); unless 0x4cccc0's flags have 0x40000000 set, re-enter the
 * scope with 0x4cf800's state (+4, +8, +0xc) through 0x4d1ae0; then leave with 0x4cf850. Returns
 * its eax. */
uint32_t vertrix_rtl_scope_refresh(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services, uint32_t object,
                                   uint32_t edx, uint32_t ebx, uint32_t ecx);

/* Original 0x4c98d0 (eax = source, edx = destination, ebx = blocks): copy blocks * 128 bytes. The
 * original copies forward (a Delphi Move without overlap handling); the blocks never overlap.
 * Returns the byte count (the eax it leaves behind). */
uint32_t vertrix_rtl_copy_blocks(uint8_t *destination, const uint8_t *source, uint32_t blocks);

/* Original 0x4db8c0 (eax = object, edx the query argument, ebx and ecx the caller's; `stack` is the
 * token for the entry esp): 0x4db950(edx, buffer, 0x100) fills a 0x100 byte buffer at stack - 0x114
 * and returns its length; when at least three bytes remain 0x4ca370 assigns the buffer to the
 * object, otherwise 0x4ca670 grows a buffer by 0x100 until 0x4db950 leaves three bytes spare and
 * 0x4ca6c0 finishes it. Returns one when the length is positive, otherwise zero. */
uint32_t vertrix_rtl_read_into(const VertrixCalls *calls, uint32_t stack, uint32_t object,
                               uint32_t edx, uint32_t ebx, uint32_t ecx);

/* Original 0x4df914 (edx = text, ebx = width): 0x4e636c(eax, edx, 0x10, ecx) runs first. The
 * zero-terminated text is then moved to the end of its first `width` bytes, '0' fills in front of
 * it and the byte at `width` is set to zero. The text must not be longer than the width. Returns
 * the eax the original leaves behind (-1, or width - 1 - length when that is more negative). */
uint32_t vertrix_rtl_pad_zeros(const VertrixCalls *calls, uint32_t eax, uint32_t edx, uint32_t ecx,
                               uint32_t width, uint8_t *text);

/* Original 0x4df884 (eax = text, edx = its selector, ebx = limit): the length of the
 * zero-terminated text, at most `limit`. */
uint32_t vertrix_rtl_length_limit(const uint8_t *text, uint32_t limit);

/* Original 0x4df8a8 (eax = text, edx = its selector, ebx = limit; `local` is the token for the
 * esp the call receives, entry esp - 16): the bytes the wide characters of the zero-terminated
 * text need, 0x4e62e0(local, character) giving each count (-1 skips the character). `address` is
 * the original's pointer to the text. With a limit other than -1 counting stops once the total
 * exceeds the limit, and the limit is returned when it was exceeded. */
uint32_t vertrix_rtl_wide_byte_count(const VertrixCalls *calls, uint32_t local, uint32_t address,
                                     const uint16_t *text, int32_t limit);

/* Originals 0x4d80a6 (single float addition of eax and edx, as bit patterns) and 0x4d809c (the
 * subtraction, adding edx with its sign flipped): a zero operand returns the other one; otherwise
 * the helper whose address is the dword at 0x503ea0 (`helper`, picked by 0x4d82c6) is jumped to
 * with the registers unchanged. Return its eax. */
uint32_t vertrix_float_add(const VertrixCalls *calls, uint32_t helper, uint32_t eax, uint32_t edx);
uint32_t vertrix_float_subtract(const VertrixCalls *calls, uint32_t helper, uint32_t eax,
                                uint32_t edx);

/* Original 0x4db896 (the double in edx:eax, `bits`; the result is returned in edx:eax): the natural
 * logarithm as fldln2 / fyl2x computes it in extended precision before it is stored as a double.
 * The C library's log agrees to within one unit in the last place (not bit for bit). */
uint64_t vertrix_rtl_natural_log(uint64_t bits);

/* Original 0x4c9b10 (the double in edx:eax, result in edx:eax; `frame` is the token for ebp and
 * `hardware` the byte at 0x5054a1): a negative operand raises 0x4dad2e(0x2043, &local) and the
 * pair it leaves is returned; with the hardware flag set the square root is taken by fsqrt; without
 * it 0x4db10a computes it unless the high word is zero, when the operand is returned as it is.
 * The registers other than eax are the caller's, so edx stays the high word (or &local). */
uint64_t vertrix_rtl_square_root(const VertrixCalls *calls, uint32_t frame, uint32_t hardware,
                                 uint32_t eax, uint32_t edx);

/* Original 0x4ca3a0 (eax = the string variable, edx = the wide text or zero, ebx the caller's):
 * 0x4d8580 measures the text (zero when absent), 0x4ca1e0 resizes the variable to twice that,
 * 0x4ca730 copies the text to the variable's buffer (the dword at +0) and 0x4ca6c0 finishes it
 * with -1. Returns the variable. */
uint32_t vertrix_rtl_wide_assign(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                 uint32_t variable, uint32_t source, uint32_t ebx);

/* Original 0x489d00 (eax and edx point at zero terminated strings): one when they have the same
 * length and every character agrees after 0x4dabb0 (a to z folded to capitals), where a mismatch
 * on the last character still reports equal because the test follows the advance. Both strings
 * must be reachable from the services at their start. Returns zero when they cannot be read. */
int vertrix_rtl_text_equal(const VertrixFactoryServices *services, uint32_t first, uint32_t second,
                           uint32_t *result);

/* Original 0x4db250 (cdecl; the stack arguments are the low and high dwords of two doubles and
 * the pointers for the quotient bits and the result): the remainder of the first by the second
 * by shift and subtract on the mantissas, with the quotient's low bits (negated for differing
 * signs). A divisor whose high dword is zero gives zeros. */
void vertrix_float_remainder(uint32_t low, uint32_t high, uint32_t other_low, uint32_t other_high,
                             uint32_t *quotient, uint32_t *result_low, uint32_t *result_high);

/* Original 0x4d9f06 (a setjmp: eax = buffer): stores ebx, ecx, edx, esi, edi, ebp, the return
 * address (popped from the stack), the stack pointer after that pop, the six segment registers
 * (words) and the exception chain (fs:[0]) at +0x00..+0x2c, and returns zero. The values are the
 * machine's registers at the call, passed in. */
typedef struct VertrixJumpState
{
    uint32_t ebx, ecx, edx, esi, edi, ebp, return_address, esp;
    uint32_t es, ds, cs, fs, gs, ss;
    uint32_t chain;
} VertrixJumpState;

int vertrix_rtl_jump_capture(void *storage, size_t size, const VertrixJumpState *state);

/* Original 0x4c9860 (eax = source pointer array, edx = its first index, ebx = destination pointer
 * array, ecx = its first index; stack: row count (signed, nothing is copied unless positive) and
 * the byte size of a row): copies the rows the source pointers designate over those of the
 * destination, in order. The pointer arrays and rows must be reachable from the services at their
 * start. Returns zero when something cannot be read. */
int vertrix_rtl_copy_rows(const VertrixFactoryServices *services, uint32_t source_array,
                          uint32_t source_index, uint32_t destination_array,
                          uint32_t destination_index, int32_t count, uint32_t size);

#endif
