#ifndef VERTRIX_EVENT_STACK_H
#define VERTRIX_EVENT_STACK_H
#include <stddef.h>
#include <stdint.h>

/* Fixed stack of nine 0x34-byte event records embedded in an engine object. Record zero is
 * the unused bottom; the byte at +0x208 counts the pushed records and addresses the top. */
#define VERTRIX_EVENT_STACK_CAPACITY 9

/* One stack record, fields named by their original offsets. */
typedef struct
{
    uint8_t b00;
    uint8_t b01;
    uint32_t d04;
    uint8_t b08;
    uint32_t d0c;
    uint32_t d10;
    uint8_t b14;
    uint32_t d18;
    uint32_t d1c;
    uint16_t w20;
    uint16_t w22;
    uint32_t d24;
    uint32_t d28;
    uint32_t d2c;
} VertrixEventRecord;

/* Optional destinations for a pop; a null member is skipped like the original null pointer. */
typedef struct
{
    uint8_t *b00;
    uint8_t *b01;
    uint32_t *d04;
    uint8_t *b08;
    uint32_t *d0c;
    uint32_t *d10;
    uint8_t *b14;
    uint32_t *d2c;
    uint32_t *d18;
    uint32_t *d1c;
    uint16_t *w20;
    uint16_t *w22;
    uint32_t *d24;
    uint32_t *d28;
} VertrixEventPopRefs;

/* Optional sources for a top replacement; a null member leaves that field unchanged. */
typedef struct
{
    const uint8_t *b00;
    const uint8_t *b01;
    const uint32_t *d04;
    const uint8_t *b08;
    const uint32_t *d0c;
    const uint32_t *d10;
    const uint8_t *b14;
    const uint32_t *d2c;
    const uint32_t *d18;
    const uint32_t *d1c;
    const uint16_t *w20;
    const uint16_t *w22;
    const uint32_t *d24;
    const uint32_t *d28;
} VertrixEventTopRefs;

/* Original0x482060: push a record unless nine are stacked. Returns 1 when stored, 0 when the
 * stack is full or the storage is too short (storage preserved). */
int vertrix_event_stack_push(void *storage, size_t size, const VertrixEventRecord *record);

/* Original0x482110: copy the top record to the supplied destinations and drop it. A stack
 * with no records stays unchanged and returns 0. */
int vertrix_event_stack_pop(void *storage, size_t size, const VertrixEventPopRefs *refs);

/* Original0x482210: overwrite fields of the record at the current top without changing the
 * count. Returns 1 when applied, 0 for short storage. */
int vertrix_event_stack_replace_top(void *storage, size_t size, const VertrixEventTopRefs *refs);

/* Original0x482300: 1 in *empty when no records are stacked. Returns 0 for short storage. */
int vertrix_event_stack_empty(const void *storage, size_t size, uint32_t *empty);

/* Original0x478cd0: map a key byte to a slot index 0..4 (keys 8, 0xf, 0x10,
 * 0x18, 0x20), stored at +0xd; other keys leave storage untouched. Only the
 * low byte matters, as in the original. Returns zero when a required write
 * fails or the event is null. */
int vertrix_event_key_index(void *event, size_t size, uint32_t key);

/* Original0x478da0: scale the dword at +0x4 by the byte at +0xc, subtract
 * from the dword at +0x14 into +0x18, and set +0x10 to whether the result is
 * nonzero (also returned). Callers sanitize edx, so only the stored byte
 * participates; the native likewise reads just the byte. Returns zero for
 * short storage. */
int vertrix_event_scale_fields(void *event, size_t size);
#endif
