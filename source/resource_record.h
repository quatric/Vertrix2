#ifndef VERTRIX_RESOURCE_RECORD_H
#define VERTRIX_RESOURCE_RECORD_H
#include "actor_gate.h"
#include "actor_storage.h"
#include "board_cells.h"
/* A resource record: a name string at +0x00, a path string at +0x104 (260 bytes each), flag
 * bytes at +0x220..+0x224 and five resource handles at +0x268..+0x278. */
#define VERTRIX_RECORD_SIZE 0x27c
#define VERTRIX_RECORD_STRING_SIZE 0x104
#define VERTRIX_WIDTH_TABLE_SIZE 256

/* Original0x441530: copy both NUL-terminated strings into the record (the original copies
 * without a bound; strings that do not fit in 260 bytes return zero without changes), clear the
 * dwords +0x208, +0x20c and the five handles, and store the five flag bytes. */
int vertrix_record_init(void *record, size_t size, const char *name, const char *path,
                        uint8_t flag_220, uint8_t flag_221, uint8_t flag_222, uint8_t flag_223,
                        uint8_t flag_224);

/* Supplied boundary for the original handle release 0x478d80. */
typedef void (*VertrixRecordRelease)(uint32_t handle, void *context);

/* Original0x441a80: release the handles at +0x268, +0x274 and +0x278 when set, the one at +0x270
 * when byte +0x220 is 1 and it is set, and the one at +0x26c when byte +0x222 is 1 and it is
 * set, in that order; then clear all five. Returns zero for short storage. */
int vertrix_record_release(void *record, size_t size, VertrixRecordRelease release, void *context);

/* Supplied boundary for the original draw call 0x47ce10 (eax, edx, ecx, ebx and four stack
 * arguments). */
typedef void (*VertrixRecordDraw)(uint32_t first, uint32_t second, uint32_t ecx, uint32_t ebx,
                                  const uint32_t stack[4], void *context);

/* Original0x441b30: when the handles at +0x274 and +0x278 are both set, call the draw routine
 * with them, zero registers and the stack arguments 0, 0, dword +0x4 and dword +0x8 of the first
 * object. Returns zero for an unresolvable object. */
int vertrix_record_draw(const void *record, size_t size, VertrixObjectStorage resolve,
                        VertrixRecordDraw draw, void *context);

/* Original0x442b00: the width of a string using the glyph width table at 0x544790: spaces add 4,
 * other characters add their table width minus one, and a nonzero total gains one. Only the low
 * 16 bits of the original result are defined (the upper bits mix a caller register). */
uint16_t vertrix_text_width(const uint8_t *text, const uint8_t widths[VERTRIX_WIDTH_TABLE_SIZE]);

/* Supplied boundary for the original virtual method at [object + 0x27c],
 * invoked with the object and flag 2. */
typedef uint32_t (*VertrixRecordMethod)(uint32_t object, uint32_t flag, void *context);

/* Original fragment 0x41a9e0: release the record, then re-read the global cell: when it
 * is still nonzero, run the virtual method it names (the dword at the
 * method-table address in +0x27c, invoked with the object and flag 2) and
 * clear the cell after the callback returns (including any callback write),
 * returning the method's value. When release clears the global cell, this API
 * returns zero instead of preserving the original release-register return;
 * the void release boundary cannot represent that return. Short storage rejects
 * before release; late lookup failure retains completed release effects and returns zero. */
int vertrix_record_release_global(uint32_t *global, void *record, size_t record_size,
                                  VertrixRecordRelease release, void *context,
                                  VertrixRecordMethod method, void *method_context,
                                  VertrixMemoryRead read, void *read_context);
#endif
