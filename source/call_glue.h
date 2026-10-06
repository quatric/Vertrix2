#ifndef VERTRIX_CALL_GLUE_H
#define VERTRIX_CALL_GLUE_H
#include <stddef.h>
#include <stdint.h>

/* One call out of a recovered wrapper, in the original Delphi register convention: the callee
 * address identifies the unrecovered routine and the registers are its inputs. */
typedef struct VertrixCallSite
{
    uint32_t target;
    uint32_t eax;
    uint32_t edx;
    uint32_t ebx;
    uint32_t ecx;
    uint32_t stack;
    uint32_t stack_next;
    uint32_t stack_third;
    uint32_t out_ebx;
    uint32_t out_ecx;
    uint32_t stack_rest[8];
    uint32_t out_value;
} VertrixCallSite;

/* Performs the call and returns the callee's eax. */
/* The callee may store a dword through the ebx and ecx pointers it was given (the locals of the
 * caller); the dwords are returned in out_ebx and out_ecx. */
typedef uint32_t (*VertrixCallFn)(VertrixCallSite *site, void *context);

typedef struct VertrixCalls
{
    VertrixCallFn call;
    void *context;
} VertrixCalls;

/* Perform one call through the boundary; one stack argument at most. Returns the callee's eax. */
uint32_t vertrix_call(const VertrixCalls *calls, uint32_t target, uint32_t eax, uint32_t edx,
                      uint32_t ebx, uint32_t ecx, uint32_t stack);

/* The same for a callee that stores through ebx and ecx; the stored dwords come back in *out_ebx
 * and *out_ecx. */
uint32_t vertrix_call_out(const VertrixCalls *calls, uint32_t target, uint32_t eax, uint32_t edx,
                          uint32_t ebx, uint32_t ecx, uint32_t *out_ebx, uint32_t *out_ecx);

/* The same for a callee that stores a byte or dword through each of the pointers in edx, ebx and
 * ecx (the caller's locals); the stored values come back in *out_edx, *out_ebx and *out_ecx. */
uint32_t vertrix_call_out3(const VertrixCalls *calls, uint32_t target, uint32_t eax, uint32_t edx,
                           uint32_t ebx, uint32_t ecx, uint32_t *out_edx, uint32_t *out_ebx,
                           uint32_t *out_ecx);

/* The same for a callee with one stack argument that also stores through the ebx and ecx pointers;
 * the stored dwords come back in *out_ebx and *out_ecx and the dword it stores through the pointer
 * in the stack argument in *out_value. */
uint32_t vertrix_call_out_stack(const VertrixCalls *calls, uint32_t target, uint32_t eax,
                                uint32_t edx, uint32_t ebx, uint32_t ecx, uint32_t stack,
                                uint32_t *out_ebx, uint32_t *out_ecx, uint32_t *out_value);

/* The same with up to eleven stack arguments (the first three in stack, stack_next and
 * stack_third, the rest in stack_rest), the nearest to the stack pointer first. The callee may
 * store one dword through a pointer it was given in the arguments; it returns in *out_value. */
uint32_t vertrix_calln(const VertrixCalls *calls, uint32_t target, uint32_t eax, uint32_t edx,
                       uint32_t ebx, uint32_t ecx, const uint32_t *stack, unsigned count,
                       uint32_t *out_value);

/* The same with three stack arguments (a cdecl callee such as 0x4cdfb0), first being the one
 * nearest the stack pointer. */
uint32_t vertrix_call3(const VertrixCalls *calls, uint32_t target, uint32_t eax, uint32_t edx,
                       uint32_t ebx, uint32_t ecx, const uint32_t stack[3]);

enum
{
    VERTRIX_CALL_RESOURCE_TABLE = 0x513e60,
    VERTRIX_CALL_POINT_LIST = 0x54d640,
    VERTRIX_CALL_GRID_BASE = 0x544f90,
    VERTRIX_CALL_VTABLE_FIELD = 0x1c,
    VERTRIX_CALL_VTABLE_VALUE = 0x514464
};

/* Original 0x4182f0 (index 7), 0x418550 (index 5) and 0x418570 (index 6): hand eax, the resource
 * table 0x513e60 and the index to 0x4cea15. Returns its eax. */
uint32_t vertrix_resource_entry_call(const VertrixCalls *calls, uint32_t eax, uint32_t index);

/* Original 0x416c10: 0x476160 on the point list 0x54d640 with the object and the 16-bit value.
 * Returns the object. */
uint32_t vertrix_point_list_add(const VertrixCalls *calls, uint32_t object, uint16_t value);

/* Original 0x4735e0: 0x476480 on the point list; when it returns one, 0x476720 with the second
 * value. Returns the eax of the last call. */
uint32_t vertrix_point_list_conditional(const VertrixCalls *calls, uint16_t first, uint32_t second);

/* Original 0x473610: 0x476720 on the point list with the 16-bit value when flag is one, otherwise
 * returns eax unchanged. */
uint32_t vertrix_point_list_when_one(const VertrixCalls *calls, uint32_t eax, uint32_t flag);

/* Original 0x45e690 (0x544a34, 0x13) and 0x45e720 (0x5464e4, 0x8): 0x487640 on a fixed resource
 * with a fixed count. Returns its eax. */
uint32_t vertrix_resource_one_frame(const VertrixCalls *calls, uint32_t resource, uint32_t count);

/* Original 0x45e990: 0x487750 on the grid cell 0x544f90 + 280 * row + 28 * column with the
 * arguments passed through; first and second are its two stack arguments. Returns its eax. */
uint32_t vertrix_grid_cell_call(const VertrixCalls *calls, uint32_t row, uint32_t column,
                                uint32_t third, uint32_t fourth, uint32_t first, uint32_t second);

/* Original 0x45f0a0: 0x45f0c0 for each index 0 to 6 (ebx keeps eax), then 0x45f1e0. Returns the eax
 * of the last call. */
uint32_t vertrix_seven_steps(const VertrixCalls *calls, uint32_t eax);

/* Original 0x425d30: store 0x514464 at object + 0x1c and call 0x425de0 on the object. Returns
 * the object, or zero when the storage is too short. */
uint32_t vertrix_object_set_table(const VertrixCalls *calls, void *storage, size_t size,
                                  uint32_t object);

/* Original 0x43f460: nonzero when 0x43f420 accepts the sign-extended low byte of eax and the low
 * byte of edx. */
uint32_t vertrix_glyph_present(const VertrixCalls *calls, uint32_t eax, uint32_t edx);

/* Original 0x441120: tail call to 0x4ea190. Returns its eax. */
uint32_t vertrix_forward_4ea190(const VertrixCalls *calls);

enum
{
    VERTRIX_CALL_LIST_CLEAR = 0x4b6200,
    VERTRIX_CALL_SLOT_STRIDE_SHIFT = 5
};

/* Original 0x471a70 (list 0x54671c), 0x471a80 (0x546744), 0x471b00 (0x546730), 0x471b80
 * (0x546758) and 0x472350 (0x54676c): 0x4b6200 on a fixed list. Returns its eax. */
uint32_t vertrix_list_clear_call(const VertrixCalls *calls, uint32_t list);

/* Original 0x475d90 (offset 4 to 0x475800), 0x47ed50 (offset 0x1c) and 0x47f8d0 (offset 0x3c), both
 * to 0x4ca370: call target on eax + offset. Returns its eax. */
uint32_t vertrix_offset_call(const VertrixCalls *calls, uint32_t target, uint32_t eax,
                             uint32_t offset);

/* Original 0x476010: 0x4759e0 on the 96-byte slot of the 16-bit index inside the table at eax.
 * Returns its eax. */
uint32_t vertrix_slot_call(const VertrixCalls *calls, uint32_t table, uint32_t index);

/* Original 0x476260: 0x475b80 on 0x55364c with the stack arguments zero (the second is the caller's
 * ebx; it pops both). Returns its eax. */
uint32_t vertrix_list_find_call(const VertrixCalls *calls, uint32_t edx);

/* Original 0x478bd0: 0x40eea0 on zero when the flag at 0x5589d4 is one. Returns its eax, or the
 * incoming eax otherwise. */
uint32_t vertrix_when_flag_call(const VertrixCalls *calls, uint32_t flag, uint32_t eax);

/* Original 0x482740: 0x4ea190 on the first dword of the object. Returns its eax, or zero for
 * storage shorter than a dword. */
uint32_t vertrix_forward_first_dword(const VertrixCalls *calls, const void *storage, size_t size);

/* Original 0x482a40: 0x40adc0 on the entry of the 256-entry table at 0x598d88 selected by the low
 * byte of eax. */
uint32_t vertrix_table_entry_call(const VertrixCalls *calls, const uint32_t *table, uint32_t eax);

/* Original 0x48c370: copy the dword at 0x5bb518 to 0x5bd834. */
void vertrix_copy_dword(uint32_t *destination, const uint32_t *source);

/* Original 0x475a80: 0x475af0 on eax, 0x475790 on eax + 4 with a zero stack argument, then
 * 0x4759e0 on eax; the first call receives edx, ebx and ecx unchanged. Returns the eax of the last
 * call. */
uint32_t vertrix_list_reset_calls(const VertrixCalls *calls, uint32_t eax, uint32_t edx,
                                  uint32_t ebx, uint32_t ecx);

/* Original 0x475ab0: 0x475790 on eax + 4 with the sign-extended low byte of edx and one stack
 * argument. Returns its eax. */
uint32_t vertrix_list_push_call(const VertrixCalls *calls, uint32_t eax, uint32_t edx,
                                uint32_t stack);

/* Original 0x4764a0: 0x475da0 on the 96-byte slot of the 16-bit index inside the table at eax,
 * with the remaining registers shifted down and the stack argument as ecx. Returns its eax. */
uint32_t vertrix_slot_store_call(const VertrixCalls *calls, uint32_t table, uint32_t index,
                                 uint32_t second, uint32_t third, uint32_t stack);

/* Original 0x476590: 0x476140 on eax with 0x7a, then with 0x7b. Returns the last eax. */
uint32_t vertrix_two_codes_call(const VertrixCalls *calls, uint32_t eax);

/* Original 0x478b40: with the flags at 0x5589d4 and 0x5589dc, 0x40ee60 on eax when both are one,
 * on zero when only the first is, and nothing otherwise (returning eax). */
uint32_t vertrix_flagged_call(const VertrixCalls *calls, uint32_t first_flag, uint32_t second_flag,
                              uint32_t eax);

/* Original 0x47f9b0: one when 0x47e7d0 returns one on eax and then 0x47fd70 on eax and 0x51698c
 * returns one, zero otherwise. */
uint32_t vertrix_checked_calls(const VertrixCalls *calls, uint32_t eax);

/* Original 0x482bb0: 0x48a930 on eax with ebx = 1 and ecx = 2. Returns its eax. */
uint32_t vertrix_flag_pair_call(const VertrixCalls *calls, uint32_t eax);

/* Original 0x489760: 0x4ca370 on eax with 0x5109ce and the length of the string, then 0x4ca600 on
 * eax with ebx plus that length. Returns one. */
uint32_t vertrix_string_append_calls(const VertrixCalls *calls, uint32_t eax, const char *string,
                                     uint32_t ebx);

/* Original 0x47fbb0: copy the 16 bytes at 0x558ce0 to the destination. */
void vertrix_copy_global16(uint8_t *destination, const uint8_t *source);

/* Original 0x40c1e0, 0x40c1f0 and 0x40c210: the global at 0x52f90c handed to 0x4e7eb0 (result
 * discarded, returns zero), to 0x4ebce8 with eax and edx (returns zero) and to 0x4ebe60 (returns
 * its eax). */
uint32_t vertrix_global_discard_call(const VertrixCalls *calls, uint32_t global);
uint32_t vertrix_global_pair_call(const VertrixCalls *calls, uint32_t global, uint32_t eax,
                                  uint32_t edx);
uint32_t vertrix_global_call(const VertrixCalls *calls, uint32_t global);

/* Original 0x40ae80: 0x40a890 on four fixed blocks and then 0x40a800 on zero when the dword at
 * 0x4f6418 is 0xffff; returns three otherwise. */
uint32_t vertrix_module_reset_calls(const VertrixCalls *calls, uint32_t marker);

/* Original 0x4c5bc0 (target 0x4ea190), 0x4c5bd0 (0x4e7c90) and 0x4c5be0 (0x4ea190): the target on
 * edx. Returns its eax. */
uint32_t vertrix_edx_to_eax_call(const VertrixCalls *calls, uint32_t target, uint32_t edx,
                                 uint32_t ebx, uint32_t ecx);

/* Original 0x4c5bf0 returns ebx; 0x4c5c10 returns zero. */
uint32_t vertrix_return_ebx(uint32_t ebx);
uint32_t vertrix_return_zero(void);

/* Original 0x45e8d0 (base 0x546458) and 0x45ea60 (base 0x544d7c): when edx is not zero,
 * 0x487640 on base + 28 * eax with ecx = 4 * eax; eax is returned unchanged for zero. */
uint32_t vertrix_indexed_resource_call(const VertrixCalls *calls, uint32_t base, uint32_t eax,
                                       uint32_t edx, uint32_t ebx);

/* Original 0x45e950: 0x487710 on the grid cell 0x544f90 + 280 * row + 28 * column with ebx as
 * edx and ebx and the column as ecx. Returns its eax. */
uint32_t vertrix_grid_array_call(const VertrixCalls *calls, uint32_t row, uint32_t column,
                                 uint32_t ebx);

/* Original 0x4766f0: the 0x475a80 body (vertrix_list_reset_calls) on each of the 256 96-byte slots
 * of the table at eax, with edx counting from one and ecx the table. Returns 256. */
uint32_t vertrix_slot_table_reset(const VertrixCalls *calls, uint32_t table);

/* Original 0x4b8170: 0x40aca0 on eax, then 0x4ea190 on eax. Returns the first result. */
uint32_t vertrix_two_step_call(const VertrixCalls *calls, uint32_t eax);

/* Original 0x4b7da0: the dword at 0x5bd83c. */
uint32_t vertrix_read_global(const uint32_t *global);

/* Original 0x4760f0 (target 0x476140) and 0x4760c0 (0x476120): the target on the object for each
 * index 0 to 255 (edx and ebx the index, ecx the object). Returns the last eax. */
uint32_t vertrix_index_sweep_call(const VertrixCalls *calls, uint32_t target, uint32_t object);

/* Original 0x4765b0: 0x476120 on the object with 0x74, 0x75 and 0xbe to 0xc3, then 0x476140 with
 * 0x70 to 0x73. Returns the last eax. */
uint32_t vertrix_fixed_codes_call(const VertrixCalls *calls, uint32_t object);

/* Original 0x4766b0: nothing when mode equals *current (the global 0x553648, returning the table);
 * otherwise store it, 0x4759e0 on 0x55364c and the 256 slot resets of vertrix_slot_table_reset.
 * Returns 256 after a change. */
uint32_t vertrix_slot_table_switch(const VertrixCalls *calls, uint32_t table, uint32_t mode,
                                   uint32_t *current);

/* Original 0x479df0: 0x479d70 four times on eax and edx with (ebx, ecx + 1), (ebx, ecx - 1),
 * (ebx - 1, ecx + 1) and (ebx + 1, ecx - 1). Returns the last eax. */
uint32_t vertrix_neighbour_calls(const VertrixCalls *calls, uint32_t eax, uint32_t edx,
                                 uint32_t ebx, uint32_t ecx);

/* Original 0x415e10: for each of the 76 dwords of the array at 0x533164 (a guest address passed
 * for the call), 0x482b30 on it with edx the byte offset of the next one and ecx zero, then the
 * dword cleared. ebx is the caller's. Returns the last eax. */
uint32_t vertrix_clear_each_call(const VertrixCalls *calls, uint32_t items[76], uint32_t ebx);

/* Original 0x4b6890 (to 0x4ae010): tail call that hands every register through unchanged. */
uint32_t vertrix_forward_registers(const VertrixCalls *calls, uint32_t target, uint32_t eax,
                                   uint32_t edx, uint32_t ebx, uint32_t ecx);

/* Original 0x48d6b0: tail call to 0x4d8950 (and 0x4872b0 to 0x4ea190). Returns its eax. */
uint32_t vertrix_forward_call(const VertrixCalls *calls, uint32_t target);

/* Original 0x419490 (target 0x45fa70, eax = 0, the guard) and 0x4194b0 (target 0x45fab0, eax = the
 * dword at 0x558c7c): run only while the flag at 0x532b40 is clear and the dword at 0x558958 is
 * zero. Returns the callee's eax; a set flag returns the incoming eax, a set guard the guard. */
uint32_t vertrix_guarded_call(const VertrixCalls *calls, uint32_t flag, uint32_t guard,
                              uint32_t target, uint32_t eax, uint32_t edx, uint32_t ebx,
                              uint32_t ecx);

/* Original 0x45ecd0: 0x4877f0(0x544a6c, edx = eax, ebx = 4, ecx unchanged), 0x47cd60(esi = edx
 * argument, edx = first dword of the result), then 0x483ed0(result, edx = 0x5b9c60). The result of
 * the first call is read through `first_dword`. Returns the eax of the last call. */
uint32_t vertrix_resource_pair_call(const VertrixCalls *calls, uint32_t eax, uint32_t edx,
                                    uint32_t ecx, uint32_t first_dword);

/* Original 0x40afc0 (ebp = frame, local at frame-8): when mode differs from *current, stores it,
 * calls 0x40ef40 with the local's address (it stores a dword through eax) and then 0x40ede0 for
 * mode 1 with a zero local, or 0x40ee30 for another mode with a local of 1. Returns eax. */
uint32_t vertrix_mode_switch_call(const VertrixCalls *calls, uint32_t frame, uint32_t *current,
                                  uint32_t mode, uint32_t ebx, uint32_t ecx);

/* Original 0x4895b0, 0x4895e0, 0x489610: 0x4d9060(path, &find_data) with the find data in a local
 * at frame-0x120 (0x4895b0, 0x4895e0) or frame-0x124 (0x489610). 0x4895b0 returns bit 0 of the
 * dword at +0x10 (the file attributes), 0x4895e0 whether the call returned 1, and 0x489610 the
 * dword at +0xc when the call returned non-zero, else 0. `stored` is the dword the callee stored
 * at the relevant offset. */
uint32_t vertrix_find_attribute_flag(const VertrixCalls *calls, uint32_t frame, uint32_t path);
uint32_t vertrix_find_succeeded(const VertrixCalls *calls, uint32_t frame, uint32_t path);
uint32_t vertrix_find_size_field(const VertrixCalls *calls, uint32_t frame, uint32_t path);

/* Original 0x482610 (ebp = frame): 0x4ec1a0 with a local at frame-0xc, then 0x482640(eax, edx =
 * that result). The registers other than eax are the caller's. Returns eax. */
uint32_t vertrix_scratch_pair_call(const VertrixCalls *calls, uint32_t frame, uint32_t eax,
                                   uint32_t edx, uint32_t ebx);

/* Original 0x478bf0 (locals at frame-0x10 and frame-0xc): when the flag at 0x5589d4 is one,
 * 0x40ef00 stores a pair of dwords through eax and edx (returned in out_ebx and out_ecx of the
 * site) and, when it returns zero, 0x40eea0 is called on the pair offset by the caller's eax and
 * edx. Returns eax. */
uint32_t vertrix_offset_pair_call(const VertrixCalls *calls, uint32_t frame, uint32_t flag,
                                  uint32_t eax, uint32_t edx);

/* Original 0x478c40: like vertrix_offset_pair_call (0x478bf0) but the stored pair is reduced by the
 * caller's eax and edx (ebx and ecx swapped) instead of increased: when the second difference is
 * negative it is clamped to zero and the first loses one, and a negative first is clamped to zero
 * before 0x40eea0. Returns its eax. */
uint32_t vertrix_offset_pair_clamp_call(const VertrixCalls *calls, uint32_t frame, uint32_t flag,
                                        uint32_t eax, uint32_t edx);

/* Original 0x41d5b0 (eax = object; the exception frame is ignored and the original's eax, the
 * restored exception chain, is not comparable): 0x418820 runs on the object; when the global
 * 0x532a8c (gate) is zero, 0x4177b0 on the global 0x532aa4 (value) gives a signed byte, 0xff
 * meaning none, which is stored (sign extended) to the global 0x532ab4 (*stored) before
 * 0x418820 runs again with the second handler. Returns the last call's eax, or zero. */
uint32_t vertrix_gate_dispatch_call(const VertrixCalls *calls, uint32_t object, uint32_t gate,
                                    uint32_t value, uint32_t *stored);

/* Original 0x416010 (frame is the token for ebp, the exception frame being ignored; the original's
 * eax is the restored exception chain and is not comparable): the global 0x532c40 (*flag) is set
 * to one; when the global 0x532bf8 (current) equals the dword at 0x4f8160 (expected), 0x47f9b0
 * probes the table 0x5bb254. A result of one assigns the text 0x50d3c9 (0x4ca280) to a local,
 * hands it to 0x4b76d0 on the list 0x532c24, releases it (0x4ca210) and sets the flag again;
 * otherwise the texts 0x50d3f4 and 0x50d40d go the same way. Returns zero. */
uint32_t vertrix_notice_call(const VertrixCalls *calls, uint32_t frame, uint32_t current,
                             uint32_t expected, uint32_t *flag);

/* Original 0x472d00: 0x472d50, then 0x4ca000(0x15c); a non-zero result goes through 0x4abd70 and is
 * stored in *slot (the global 0x546794), which then has its handler set by 0x4ac8f0 (0x45c250 for
 * mode 1, otherwise 0x45c2b0) and, for mode 1, its delay set to 0x1f40 by 0x4ac7d0. Returns eax. */
uint32_t vertrix_slot_create_call(const VertrixCalls *calls, uint32_t mode, uint32_t ebx,
                                  uint32_t ecx, uint32_t *slot);

/* Original 0x476530: clears the dword at `cleared` (edx, when not null; `edx` is its address), then
 * returns 0x475c80(0x55364c) when the flag at 0x553648 is one, otherwise the first index 0..255 for
 * which 0x476480(object, index) returns one, or zero. */
uint32_t vertrix_slot_search_call(const VertrixCalls *calls, uint32_t flag, uint32_t object,
                                  uint32_t edx, uint32_t ebx, uint32_t *cleared);

/* Original 0x4777c0: 0x4776a0(edx, 0x5560b0, 0xc) fills the text at 0x5560b0, which is appended
 * to the NUL terminated text in `destination`. Returns eax with its low byte cleared. */
uint32_t vertrix_text_append_call(const VertrixCalls *calls, uint32_t edx, uint32_t ecx,
                                  char *destination, const char *appended);

/* Original 0x40ed70: when bit 7 of the flags at 0x531b44 is set, 0x40add0 and 0x40ad50 run on each
 * of the `count` handles of the table at 0x531ac4 (edx = index, ebx = 4 * index), then 0x4eb5c0
 * (0x53043c, 0, 0x1744), 0x40ac10(0) and 0x40ac20(0x7d). Returns zero, or three without the flag.
 */
uint32_t vertrix_flagged_table_call(const VertrixCalls *calls, uint32_t flags, int32_t count,
                                    const uint32_t *handles, uint32_t ecx);

/* The matcher state of 0x417f50: the pattern at 0x540010 (its length is the dword 8 bytes before
 * it) and the match position at 0x540014. */
typedef struct VertrixMatcher
{
    const uint8_t *pattern;
    uint32_t length;
    uint32_t index;
} VertrixMatcher;

/* Original 0x417f40: restart the match. */
void vertrix_matcher_reset(VertrixMatcher *matcher);

/* Original 0x417f50: 0x4ca710 on the text handle, then the first byte of the text is matched
 * against the pattern (on a mismatch the match restarts, and the byte is tried once more at the
 * start). Returns one and restarts when the whole pattern matched, otherwise zero. */
uint32_t vertrix_matcher_feed(const VertrixCalls *calls, VertrixMatcher *matcher, uint32_t handle,
                              uint8_t first, uint32_t ebx, uint32_t ecx);

typedef struct VertrixTransformOut
{
    uint32_t first_word;
    uint32_t second_word;
    uint32_t first_dword;
    uint32_t second_dword;
} VertrixTransformOut;

/* Original 0x4408e0 (ret 0x1c, ebp = frame; locals: al at frame-0xc, bx at frame-0x10, results at
 * frame-0x20, -0x1c, -0x18 and -0x14): 0x440610(sign extended al, edx = stack argument 2, ebx =
 * byte of argument 3, ecx = &local, stack = &local) stores two dwords; 0x440990 then maps the four
 * sign extended words (edi, bx, esi and the low word of argument 1) with them, storing two more.
 * The first_/second_dword results are the two dwords of 0x440610, the words the low 16 bits of
 * those of 0x440990 (the original stores them through the caller's pointers). `arguments` are the
 * stack dwords from [ebp+8] up to the byte argument. */
void vertrix_corner_transform_call(const VertrixCalls *calls, uint32_t frame, uint32_t al,
                                   uint32_t edi, uint32_t bx, uint32_t esi,
                                   const uint32_t arguments[3], VertrixTransformOut *out);

/* The routines below keep a value in the x87 stack between runtime calls. The recovery models each
 * call by its register arguments, and (as the oracle's stubs do) assumes the callees leave edx, ebx
 * and ecx unchanged. */

/* Original 0x4ac560: 0x4d74a6 on the float at +0xc0 of the object, again on the one at +0xbc
 * (edx = the first result, or 0x3f800000 when it is zero), then 0x4d81fe. Returns its eax. */
uint32_t vertrix_object_scale_call(const VertrixCalls *calls, uint32_t object, uint32_t scale_c0,
                                   uint32_t scale_bc, uint32_t edx, uint32_t ebx);

/* Original 0x4aca00 (ret 4): moves `ebx` towards `ecx` by the amount 0x4d67a8 derives from the
 * stack argument, clamping at `ecx`. Returns the new ebx. */
uint32_t vertrix_step_toward_call(const VertrixCalls *calls, uint32_t ebx, uint32_t ecx,
                                  uint32_t edx, uint32_t argument);

enum
{
    VERTRIX_CURVE_ENTRIES = 65
};

/* Original 0x40ba00: for mode 1 and a step edx of at most 0x100, fills the curve table at 0x52f1fc
 * (65 dwords, the first 0xffffd8f0) from the runtime's float routines. Modes 2 to 5 do nothing;
 * others return 2. Returns zero. */
uint32_t vertrix_curve_table_build(const VertrixCalls *calls, uint32_t mode, uint32_t step,
                                   uint32_t ebx, uint32_t ecx,
                                   uint32_t table[VERTRIX_CURVE_ENTRIES]);
#endif
