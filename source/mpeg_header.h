#ifndef VERTRIX_MPEG_HEADER_H
#define VERTRIX_MPEG_HEADER_H
#include <stdint.h>

/* Decoded fields of an MPEG audio frame header (offsets of the original structure in comments). */
typedef struct
{
    uint32_t channels;       /* +0x00: 1 for mono (mode 3), else 2 */
    uint32_t lsf;            /* +0x0c: 1 for the MPEG-1 family, per header bits 19-20 */
    uint32_t extension;      /* +0x10: 1 when the header has the MPEG-2.5 extension bit clear */
    uint32_t layer;          /* +0x18: 4 - layer bits */
    uint32_t protection;     /* +0x1c: inverted bit 16 */
    uint32_t bitrate;        /* +0x20: bits 12-15 */
    uint32_t sample_rate;    /* +0x24: bits 10-11 plus the table offset */
    uint32_t padding;        /* +0x28: bit 9 */
    uint32_t private_bit;    /* +0x2c: bit 8 */
    uint32_t mode;           /* +0x30: bits 6-7 */
    uint32_t mode_extension; /* +0x34: bits 4-5 */
    uint32_t copyright;      /* +0x38: bit 3 */
    uint32_t original;       /* +0x3c: bit 2 */
    uint32_t emphasis;       /* +0x40: bits 0-1 */
    int32_t frame_size;      /* +0x44: layer 3 frame size, only set for layer 3 */
} VertrixMpegHeader;

enum
{
    VERTRIX_MPEG_EXTENSION_BIT = 0x100000,
    VERTRIX_MPEG_VERSION_BIT = 0x80000,
    VERTRIX_MPEG_BITRATES = 48,
    VERTRIX_MPEG_FRAME_FACTOR = 0x23280
};

/* Supplied boundary for 0x4eb4d4 (argument 1), called when the sample rate bits are 3; the
 * original continues if it returns. */
typedef void (*VertrixMpegInvalid)(uint32_t code, void *context);

/* Original0x404480: decode the header word. bitrates is the dword table at 0x4f40ac (two rows of 48
 * dwords, selected by the lsf field) and sample_rates the table at 0x4f41ac. Returns 0 for a zero
 * bitrate field or an invalid layer (4) and 1 otherwise; only layer 3 computes the
 * frame size. All fields except the frame size are stored before the result is decided. A zero
 * sample rate divisor faults in the original and returns 0 here without storing the size. */
uint32_t vertrix_mpeg_header_decode(VertrixMpegHeader *header, uint32_t word,
                                    const uint32_t *bitrates, const uint32_t *sample_rates,
                                    VertrixMpegInvalid invalid, void *context);
#endif
