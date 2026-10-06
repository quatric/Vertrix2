#include "bit_reader.h"

enum
{
    SHIFT_COUNT_MASK = 31,
    BYTE_BITS_SHIFT = 3,
    BIT_MASK = 7,
    TOP_BIT_SHIFT = 7
};

uint32_t vertrix_bit_reader_next(VertrixBitReader *reader, uint8_t current_byte)
{
    uint8_t shifted = (uint8_t)((uint32_t)current_byte << (reader->bit & SHIFT_COUNT_MASK));
    uint32_t next = reader->bit + 1;
    reader->address += (uint32_t)((int32_t)next >> BYTE_BITS_SHIFT);
    reader->bit = next & BIT_MASK;
    return (uint32_t)(shifted >> TOP_BIT_SHIFT);
}

static uint32_t read_bits(VertrixBitReader *reader, uint32_t count, uint32_t window, uint32_t width)
{
    uint32_t mask = (1u << width) - 1;
    window = (window << (reader->bit & SHIFT_COUNT_MASK)) & mask;
    reader->bit += count;
    uint32_t value = window >> ((width - count) & SHIFT_COUNT_MASK);
    reader->address += (uint32_t)((int32_t)reader->bit >> BYTE_BITS_SHIFT);
    reader->bit &= BIT_MASK;
    return value;
}

uint32_t vertrix_bit_reader_bits24(VertrixBitReader *reader, uint32_t count, const uint8_t bytes[3])
{
    if (count == 0)
    {
        return 0;
    }
    uint32_t window = ((uint32_t)bytes[0] << 16) | ((uint32_t)bytes[1] << 8) | bytes[2];
    return read_bits(reader, count, window, 24);
}

uint32_t vertrix_bit_reader_bits16(VertrixBitReader *reader, uint32_t count, const uint8_t bytes[2])
{
    uint32_t window = ((uint32_t)bytes[0] << 8) | bytes[1];
    return read_bits(reader, count, window, 16);
}

uint32_t vertrix_bit_reader_unread(VertrixBitReader *reader, uint32_t count, uint32_t stream,
                                   int32_t filled, uint32_t buffer_index, VertrixBitCopy copy,
                                   void *context)
{
    if (filled < 0 && (int32_t)count > 0)
    {
        return VERTRIX_UNREAD_FAILED;
    }
    uint32_t buffer =
        stream + VERTRIX_UNREAD_BUFFER_BASE + buffer_index * VERTRIX_UNREAD_BUFFER_STRIDE;
    reader->address -= count;
    if (count != 0)
    {
        copy(reader->address, buffer + (uint32_t)filled - count, count, context);
    }
    reader->bit = 0;
    return 0;
}
