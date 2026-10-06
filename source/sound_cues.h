#ifndef VERTRIX_SOUND_CUES_H
#define VERTRIX_SOUND_CUES_H
#include <stddef.h>
#include <stdint.h>

/* Sound cue wrappers. The original sound table sits at 0x54d640 (entries of 0x60 bytes) and is
 * driven by two large routines that are supplied as a callback: 0x4761d0 (start) and 0x476280
 * (stop). Both take the table, an entry index, two values (original ebx and ecx) and a stack
 * word that every wrapper passes as zero. */
#define VERTRIX_SOUND_TABLE 0x54d640

typedef enum
{
    VERTRIX_CUE_START = 0x4761d0,
    VERTRIX_CUE_STOP = 0x476280
} VertrixCueOperation;

typedef struct
{
    uint32_t table;
    uint32_t index;
    uint32_t first;
    uint32_t second;
} VertrixCueRequest;

typedef void (*VertrixCueCall)(void *context, VertrixCueOperation operation,
                               const VertrixCueRequest *request);

/* Original 0x477010/0x477040 (word +0xb8), 0x477070/0x4770a0 (+0xbc), 0x4770d0/0x477100 (+0xc0)
 * and 0x477130/0x477160 (+0xc4): operate on the entry named by that key word, with the
 * object's dwords +0x14 and +0x18 as the two values. Needs 0xcc bytes. */
typedef enum
{
    VERTRIX_CUE_KEY_FIRST = 0xb8,
    VERTRIX_CUE_KEY_SECOND = 0xbc,
    VERTRIX_CUE_KEY_THIRD = 0xc0,
    VERTRIX_CUE_KEY_FOURTH = 0xc4
} VertrixCueKey;
int vertrix_sound_cue_key(const uint8_t *object, size_t size, VertrixCueKey key,
                          VertrixCueOperation operation, VertrixCueCall call, void *context);

/* Original 0x476fb0 (start) and 0x476fe0 (stop): entry (delta + word +0xc8) & 0xffff. */
int vertrix_sound_cue_offset(const uint8_t *object, size_t size, uint32_t delta,
                             VertrixCueOperation operation, VertrixCueCall call, void *context);

/* Original 0x4784d0 (start) and 0x478520 (stop), entry (index & 0xffff): the two values are the
 * words +0x48 and +0x4a, or 0x7d00 twice when the dword +0x60 is nonzero. The fixed-entry
 * wrappers use the entries 0x72 (0x478570 start, 0x4785c0 stop), 0x73 (0x478610, 0x478660),
 * 0x70 (0x4786b0, 0x478700) and 0x71 (0x478750, 0x4787a0) with the same rule; pass the entry in
 * index. Needs 0x64 bytes. */
int vertrix_sound_cue_position(const uint8_t *object, size_t size, uint32_t index,
                               VertrixCueOperation operation, VertrixCueCall call, void *context);

/* Original 0x476720: start then stop entry (index & 0xffff) with both values zero. */
void vertrix_sound_cue_both(uint32_t table, uint32_t index, VertrixCueCall call, void *context);
#endif
