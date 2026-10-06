#ifndef VERTRIX_BIT_READER_H
#define VERTRIX_BIT_READER_H
#include <stdint.h>

typedef struct
{
    uint32_t address; /* 0x51f014: original address of the current byte (an identity token) */
    uint32_t bit;     /* 0x51f018: bit position within it, 0 is the most significant */
} VertrixBitReader;

/* Original0x4046e0: read the next bit, most significant first. current_byte is the byte at the
 * reader's address. The position advances by one bit; when it reaches 8 the address moves on
 * (the carry is the arithmetic shift by 3 of the incremented position, which is then reduced to
 * 0..7). The result is 0 or 1. */
uint32_t vertrix_bit_reader_next(VertrixBitReader *reader, uint8_t current_byte);

/* Original0x404610: read count bits (at most 24 are meaningful) from the three bytes at the
 * reader's address, most significant first. A zero count returns 0 and changes nothing. Shift
 * counts take the low five bits, as the processor does. */
uint32_t vertrix_bit_reader_bits24(VertrixBitReader *reader, uint32_t count,
                                   const uint8_t bytes[3]);

/* Original0x404680: the same over two bytes (at most 16 bits), without the zero-count shortcut:
 * a zero count still advances the address by the carry of the unchanged position. */
uint32_t vertrix_bit_reader_bits16(VertrixBitReader *reader, uint32_t count,
                                   const uint8_t bytes[2]);

enum
{
    VERTRIX_UNREAD_BUFFER_BASE = 0x5c + 0x200,
    VERTRIX_UNREAD_BUFFER_STRIDE = 0x900,
    VERTRIX_UNREAD_FAILED = 0xffffffffu
};

/* Supplied boundary for the runtime copy 0x4eb5e0 (destination, source, byte count). */
typedef void (*VertrixBitCopy)(uint32_t destination, uint32_t source, uint32_t count,
                               void *context);

/* Original0x4060e0: give count bytes back to the stream (state at the dword 0x51f01c). With a
 * negative fill level and a positive count it fails with 0xffffffff. Otherwise the address moves
 * back by count, the last count filled bytes of the stream's current buffer (at stream + 0x25c +
 * buffer_index * 0x900, filled bytes deep) are copied there when count is nonzero, the bit
 * position is cleared and 0 is returned. */
uint32_t vertrix_bit_reader_unread(VertrixBitReader *reader, uint32_t count, uint32_t stream,
                                   int32_t filled, uint32_t buffer_index, VertrixBitCopy copy,
                                   void *context);
#endif
