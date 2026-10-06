#ifndef VERTRIX_LIST_TEXT_H
#define VERTRIX_LIST_TEXT_H
#include "block_factory.h"
#include "call_glue.h"
#include <stdint.h>

/* The list readers of 0x4b7080..0x4b7420: a checked read through 0x4b6fa0 followed by the text
 * routines of the runtime (0x4ca280 clear, 0x415ed0 format, 0x4ca370 and 0x4ca310 assign). The
 * exception frame around them leaves no state and is not reproduced. */

typedef struct VertrixListTextSpec
{
    uint32_t name;
    uint32_t field;
    uint32_t format_ebx;
    uint32_t format_edx;
    uint32_t format_ecx;
} VertrixListTextSpec;

enum
{
    VERTRIX_LIST_TEXT_FRAME = 0x4ec1ec
};

/* Original 0x4b7080 (name 0x5110bc, field 0), 0x4b7120 (0x5110bd, 4), 0x4b71c0 (0x5110be, 8),
 * 0x4b7260 (0x5110bf, 0xc) and 0x4b7300 (0x5110c0, 0x10): 0x4b6fa0 on the list reader, 0x4ca280
 * on the slot with the name, and when an item was read the dword at its field through 0x415ed0 with
 * the spec's format registers, assigned to the slot through 0x4ca370. Returns the slot. */
uint32_t vertrix_list_text_dword(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                 const VertrixListTextSpec *spec, uint32_t reader, uint32_t slot,
                                 uint32_t ebx);

/* Original 0x4b73a0: the same read, the item address + 0x14 assigned to the slot through 0x4ca310.
 * Returns the slot. */
uint32_t vertrix_list_text_name(const VertrixCalls *calls, uint32_t reader, uint32_t slot,
                                uint32_t ebx);

/* Original 0x4b7420: the same read, the dword at +0x18 formatted into the slot through the cdecl
 * 0x4cdfb0 with 0x5110c3. Returns the slot. */
uint32_t vertrix_list_text_format(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  uint32_t reader, uint32_t slot, uint32_t ebx);

enum
{
    VERTRIX_CYCLE_PREVIOUS = 0,
    VERTRIX_CYCLE_NEXT = 1,
    VERTRIX_CYCLE_PREVIOUS_WRAP = 2,
    VERTRIX_CYCLE_NEXT_WRAP = 3
};

/* Original 0x4b3740 (VERTRIX_CYCLE_PREVIOUS), 0x4b37e0 (NEXT), 0x4b3880 (PREVIOUS_WRAP) and
 * 0x4b3940 (NEXT_WRAP): step the choice text of a list box. The text at +0x15c of the object that
 * +0x160 names is compared (through 0x4ccfe0, zero when equal) with each of the +0x174 strings of
 * the array at +0x170; the last match selects the neighbour, which is assigned to that text
 * through 0x4ca370. Returns one after an assignment, zero when the text is not listed or has no
 * neighbour (and the wrapping variants have none only when it is not listed). */
uint32_t vertrix_list_cycle(const VertrixCalls *calls, const VertrixFactoryServices *services,
                            uint32_t object, const void *storage, size_t size, unsigned mode);

/* Original 0x4b4fb0 (ebp = frame, text local at frame-0x14): stores edx at +0x190 of the object,
 * formats it into the local through the cdecl 0x4cdfb0 with 0x511094 and assigns the text to the
 * field at +0x15c of the object at +0x160 through 0x4ca370; then releases the local with 0x4ca210.
 * The text pointer 0x4cdfb0 leaves in the local comes back through its out value. The original's
 * eax is the exception chain it restores, which is not ported; returns zero. */
uint32_t vertrix_object_label_format(const VertrixCalls *calls,
                                     const VertrixFactoryServices *services, uint32_t frame,
                                     uint32_t object, uint32_t value, void *storage, size_t size);
/* Original 0x4b3c40: the same formatter as 0x4b4fb0 with the value at +0x18c and the format string
 * at 0x51108e. Returns 0. */
uint32_t vertrix_object_label_format_alternate(const VertrixCalls *calls,
                                               const VertrixFactoryServices *services,
                                               uint32_t frame, uint32_t object, uint32_t value,
                                               void *storage, size_t size);

/* Original 0x4b7710 (eax = object, edx = slot, ebx = index): 0x4ca280 sets the slot to the literal
 * 0x5110ca; an index below the count at +8 then appends the entry of the dword array at +4 through
 * 0x4ca310. Returns the slot. */
uint32_t vertrix_list_text_indexed(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services, uint32_t object,
                                   uint32_t slot, uint32_t index);

/* Original 0x4b76d0: 0x4ca000(4); a non-zero block goes through 0x4ca090; then 0x4d88a0(object,
 * count at +8, block, 1). Returns 0. */
uint32_t vertrix_list_resize_call(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  uint32_t object, uint32_t edx, uint32_t ebx, uint32_t ecx);

/* Original 0x4b7830: every non-zero dword of the array at +4 (count at +8) goes through 0x4ca210
 * and 0x4ca050, then 0x4d8770(object, 0, -1) with ecx = 4 * count (0x51864c for an
 * empty array). Returns 0 (the original's eax is
 * the restored exception chain). */
uint32_t vertrix_list_release_entries(const VertrixCalls *calls,
                                      const VertrixFactoryServices *services, uint32_t object);

/* Original 0x4b79e0 (eax = reader, edx = slot, ebx = key, ecx = index; its local string at
 * `local`): 0x4ca280 sets the slot to the literal 0x5110cb; the item 0x4b79c0 finds for the key
 * supplies its indexed text (vertrix_list_text_indexed into the local), which 0x4ca310 appends to
 * the slot before 0x4ca210 releases the local. Returns the slot. */
uint32_t vertrix_list_text_lookup(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  uint32_t local, uint32_t reader, uint32_t slot, uint32_t ebx,
                                  uint32_t index);

/* Original 0x48a300: vertrix_list_text_lookup with its local at the frame of this wrapper
 * (0x18 below `stack_base`); returns the slot (edx). */
uint32_t vertrix_list_text_lookup_slot(const VertrixCalls *calls,
                                       const VertrixFactoryServices *services, uint32_t stack_base,
                                       uint32_t reader, uint32_t slot, uint32_t ebx,
                                       uint32_t index);

/* Original 0x478dd0 (eax = object; frame is the token for ebp, the exception frame being ignored;
 * the original's eax is the restored exception chain and is not compared). A local string at
 * frame - 0x14 is initialised by 0x4ca070 and assigned the text 0x50ea1e by 0x4ca370; the byte at
 * +0xd (0..4) appends its kind text, 0x4ca370 assigns 0x50ea3c, 0x4ca600 appends the text for the
 * dword at +0x10 (0x50ea48 when one, otherwise 0x50ea4c) and 0x4ca210 releases the local. Returns
 * the eax of the release. */
uint32_t vertrix_object_describe(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                 uint32_t frame, uint32_t object);

/* Original 0x416a80 (eax = object; frame is the token for ebp, the exception frame being ignored;
 * the original's eax is the restored exception chain and is not compared): when 0x4ccfe0 accepts
 * the key 0x50d652 on the object, a local string at frame - 0x18 is initialised (0x4ca070) and
 * formatted by the cdecl call 0x4cdfb0(local, 0x50d653, object), which stores the text pointer
 * through its first argument; 0x47faf0 takes that text for the object 0x5bb254 and 0x4ca210
 * releases the local. Returns zero when the check failed, otherwise the release's eax. */
uint32_t vertrix_object_load_script(const VertrixCalls *calls, uint32_t frame, uint32_t object);

/* Original 0x418170 (eax = the result string variable, edx = value; frame is the token for ebp,
 * the exception frame being ignored): three locals are initialised (0x4ca070); the value divided
 * by ten and its remainder are formatted by the cdecl 0x4cdfb0 into the tens (frame - 0x20) and
 * ones (frame - 0x1c) locals with the formats 0x50d7bd and 0x50d7c1; 0x4ca4a0 joins them with
 * 0x50d7c5, 0x4ca430 turns the joined text into the result local (frame - 0x14), 0x4ca310 assigns
 * it to the variable and 0x4cda12 and 0x4cda10 leave. Returns the variable. */
uint32_t vertrix_clock_text(const VertrixCalls *calls, uint32_t frame, uint32_t variable,
                            uint32_t value);

/* Original 0x48a560 (eax = reader, edx = destination, ebx = count, ecx = fallback, one stack
 * argument `threshold`, ret 4; the exception frame is ignored and the original's eax is the
 * restored exception chain). `destination_token` is the original pointer (logged by the calls)
 * and `destination` the host array. For each of the low word of `count` entries: 0x48a2e0 gives
 * the reader's count; an index beyond it, or an item (0x48a2f0) not above the threshold, stores the
 * fallback; otherwise 0x48a300(reader, local, index, threshold) gives a slot whose text pointer
 * 0x4d6710 parses (ebx 0) into the entry before 0x4ca210 releases the local at frame - 0x18. The
 * register arguments follow the original's loop state. */
void vertrix_list_parse_values(const VertrixCalls *calls, const VertrixFactoryServices *services,
                               uint32_t frame, uint32_t reader, uint32_t destination_token,
                               uint32_t count, uint32_t fallback, uint32_t threshold,
                               uint32_t *destination);

/* Original 0x48a4a0 (eax = reader, edx = destination, ebx = count, ecx = fallback, one stack
 * argument `threshold`): the loop of vertrix_list_parse_values with text slots; an entry of the
 * reader above the threshold is assigned with 0x4ca310 from the 0x48a300 slot (the local at frame -
 * 0x18 released with 0x4ca210), any other with the fallback through 0x4ca370. The destination
 * advances four bytes an entry. */
void vertrix_list_parse_texts(const VertrixCalls *calls, uint32_t frame, uint32_t reader,
                              uint32_t destination, uint32_t count, uint32_t fallback,
                              uint32_t threshold);

/* Original 0x487fd0 (eax = list, edx = text): the index of the first non-null name in the array at
 * +0x20 (+0x14 entries) that vertrix_rtl_text_equal (0x489d00) accepts against the text, or
 * 0xffffffff. Returns zero when the list cannot be read. */
int vertrix_list_find_name(const VertrixFactoryServices *services, uint32_t list, uint32_t text,
                           uint32_t *index);

/* Original 0x4b4af0 (eax = object; frame is the token for ebp, the exception frame being ignored):
 * the text the object's parent (+0x160) holds at +0x15c is copied into three locals (frame - 0x2c,
 * 0x28 and 0x24); unless the cursor (+0x170) is on its last character, the text up to and
 * including the cursor (0x4cdb70) and the text from two characters past it (0x4cdaf0) are
 * joined (0x4ca430) into the first local and stored back through 0x4ca370. Returns zero when the
 * object cannot be read; *result is the original's eax (zero when the cursor is last, else one). */
int vertrix_object_text_rebuild(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                uint32_t frame, uint32_t object, uint32_t *result);

/* Original 0x4b4790 (eax = object, edx = value; frame is the token for ebp): like
 * vertrix_object_text_rebuild but the join (0x4ca4a0: local, text up to the cursor, value, text
 * from one character past it) is stored through 0x4ca430, 0x4ca310 and 0x4ca370; it stops with
 * zero when the text is as long as the limit at +0x178. */
int vertrix_object_text_insert(const VertrixCalls *calls, const VertrixFactoryServices *services,
                               uint32_t frame, uint32_t object, uint32_t value, uint32_t *result);

/* Original 0x4b4950: vertrix_object_text_rebuild with the guard on a cursor of 0xffffffff
 * (zero returned), the head copied to the cursor and the tail from one character past it. */
int vertrix_object_text_remove(const VertrixCalls *calls, const VertrixFactoryServices *services,
                               uint32_t frame, uint32_t object, uint32_t *result);

/* Original 0x4b6930 (eax = object, edx = value; frame is the token for ebp): 0x4cdb70 copies the
 * text at +0x15c into a local (frame - 0x1c; the pointer it stores comes back as the text), whose
 * header length four bytes into the 0xc bytes before the text decides: an empty text releases the
 * local and returns zero, otherwise 0x440610(signed byte at +0x160, text, byte at +0x44, a value
 * local at frame - 0x18, stack frame - 0x14) stores the result, which is returned after the local
 * is released. */
int vertrix_object_text_value(const VertrixCalls *calls, const VertrixFactoryServices *services,
                              uint32_t frame, uint32_t object, uint32_t edx, uint32_t *result);

/* Original 0x4b46e0 (eax = object, edx = index; `entry` is the esp at entry): zero unless index + 1
 * is positive, otherwise vertrix_object_text_value of the object's parent (+0x160) for index + 1.
 * Returns zero when a field cannot be read. */
int vertrix_object_text_row(const VertrixCalls *calls, const VertrixFactoryServices *services,
                            uint32_t entry, uint32_t object, uint32_t index, uint32_t *result);
/* Original 0x4b4700 (eax = object, edx = target; frame is the token for ebp): the index from -1
 * to the parent's text length that makes the row value (0x4b46e0) minus the target plus the high
 * word of the parent's dword at +0xc nearest zero, starting from a best distance of 0x4e20
 * (strictly closer wins); 0xffffffff when none. */
int vertrix_object_text_nearest(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                uint32_t frame, uint32_t object, uint32_t target, uint32_t *result);
/* Original 0x4b4780 (`entry` is the esp at entry): stores the nearest index (0x4b4700) in the
 * dword at +0x170. */
int vertrix_object_text_seek(const VertrixCalls *calls, const VertrixFactoryServices *services,
                             uint32_t entry, uint32_t object, uint32_t target);

/* Originals 0x4b45f0 (`entry` is the esp at entry): vertrix_object_text_row at the cursor (+0x170).
 */
int vertrix_object_cursor_row(const VertrixCalls *calls, const VertrixFactoryServices *services,
                              uint32_t entry, uint32_t object, uint32_t *result);
/* Original 0x4b4690: the cursor below -1 becomes -1 and one at or past the parent's text length
 * becomes length - 1. 0x4b4600 (delta -1) and 0x4b4610 (delta +1) move it first;
 * vertrix_object_cursor_home is 0x4b4620 (-1) and vertrix_object_cursor_end 0x4b4630 (length - 1),
 * both then clamped. */
int vertrix_object_cursor_clamp(const VertrixFactoryServices *services, uint32_t object);
int vertrix_object_cursor_step(const VertrixFactoryServices *services, uint32_t object,
                               int32_t delta);
int vertrix_object_cursor_home(const VertrixFactoryServices *services, uint32_t object);
int vertrix_object_cursor_end(const VertrixFactoryServices *services, uint32_t object);
/* Original 0x4b4660: whether the cursor is on the last character (length - 1). */
int vertrix_object_cursor_at_end(const VertrixFactoryServices *services, uint32_t object,
                                 uint32_t *result);

/* Original 0x488d80 (eax = the string variable, edx = object; the exception frame is ignored):
 * 0x4ca280 initialises the variable with 0x510737, then the dword at +8 (0 to 14) picks one of
 * fifteen texts that 0x4ca370 stores into it. Returns the variable (zero when the object cannot be
 * read). */
uint32_t vertrix_object_kind_text(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  uint32_t variable, uint32_t object);

#endif
