#ifndef VERTRIX_RECORD_SLOTS_H
#define VERTRIX_RECORD_SLOTS_H
#include <stddef.h>
#include <stdint.h>

enum
{
    VERTRIX_RECORD_SIZE = 12,
    VERTRIX_RECORD_CURRENT = 0x5c0
};

/* Original0x412650: copy the 12 byte record `index` (storage + index * 12) to storage + 0x5c0,
 * as three forward dword moves. Returns 0 and changes nothing when the first or last dword of
 * either range lies outside storage. */
int vertrix_record_load_current(uint8_t *storage, size_t size, uint32_t index);

/* Original0x412690: the reverse, storage + 0x5c0 into record `index`. */
int vertrix_record_store_current(uint8_t *storage, size_t size, uint32_t index);

enum
{
    VERTRIX_RECORD_SLOTS = 122,
    VERTRIX_RECORD_COUNT_OFFSET = 0x5b8,
    VERTRIX_RECORD_OWNER_OFFSET = 0x5bc,
    VERTRIX_RECORD_FLAGS_OFFSET = 0x5cc,
    VERTRIX_RECORD_CLASS_OFFSET = 0x7b4,
    VERTRIX_RECORD_CLASS = 0x5132e4,
    VERTRIX_RECORD_STORAGE_SIZE = 0x7b8
};

/* Record layout: signed byte +0, signed byte +1, byte +2, signed word +4, byte +6, signed byte
 * +7, signed byte +8, word +0xa. */
typedef enum
{
    VERTRIX_RECORD_FIELD_0 = 0,
    VERTRIX_RECORD_FIELD_1 = 1,
    VERTRIX_RECORD_FIELD_2 = 2,
    VERTRIX_RECORD_FIELD_4 = 3,
    VERTRIX_RECORD_FIELD_6 = 4,
    VERTRIX_RECORD_FIELD_7 = 5,
    VERTRIX_RECORD_FIELD_8 = 6,
    VERTRIX_RECORD_FIELD_A = 7
} VertrixRecordField;

/* Original0x4120a0: initialize a record table of 122 records plus the current record at +0x5c0
 * (bytes: +0 = 0, +7 = 2, +1 = 1, +6 = 0xd, +2 = 0x32, words +4 and +0xa and byte +8 = 0). The
 * dword at +0x5b8 becomes 1, +0x5bc the owner token, the 122 dwords from +0x5cc become 1 and the
 * dword at +0x7b4 the class token 0x5132e4. Returns 0 and changes nothing when the storage is
 * shorter than 0x7b8 bytes. */
int vertrix_record_table_init(uint8_t *storage, size_t size, uint32_t owner);

/* Original0x4125e0: read one field of record `index` (storage + index * 12). Selector 6 and 7
 * are tried after 5 in the original; unknown selectors give 0. Returns 0 when the bytes lie
 * outside storage (the original reads the dwords at +2, +4 and +5 for fields 4, 7 and 8). */
int vertrix_record_field(const uint8_t *storage, size_t size, uint32_t index, uint32_t field,
                         int32_t *value);

/* Original0x412430 (increase) and 0x412510 (decrease): step one field of record `index`, within
 * limits. Field 0: signed, up only below 1; field 1: signed, up below 10; field 2: unsigned, up
 * below 100; field 4: signed word, up below 200, down above -200; field 6: unsigned, up below
 * 13; field 7: signed, up below 2; field 8: signed, up below 1; field A: unsigned word, up below
 * 254 else wraps to 0, down above 0 else wraps to 254. All fields go down only above zero
 * (fields 4 and A as stated). The field enumerators are those of vertrix_record_field. Returns
 * 0 when the bytes lie outside storage; unknown fields change nothing and return 1. */
int vertrix_record_step(uint8_t *storage, size_t size, uint32_t index, uint32_t field,
                        int increase);
#endif
