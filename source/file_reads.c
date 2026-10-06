#include "file_reads.h"

enum
{
    ITEM_SIZE = 1,
    WORD_BYTES = 2,
    DWORD_BYTES = 4
};

uint32_t vertrix_file_read_exact(uint32_t file, uint8_t *buffer, uint32_t count,
                                 VertrixFileRead read, void *context)
{
    if (read(file, buffer, ITEM_SIZE, count, context) == count)
    {
        return 0;
    }
    for (uint32_t i = 0; i < count; ++i)
    {
        buffer[i] = 0;
    }
    return 0;
}

uint32_t vertrix_file_read_byte(uint32_t file, uint8_t *buffer, VertrixFileRead read, void *context)
{
    return vertrix_file_read_exact(file, buffer, ITEM_SIZE, read, context);
}

uint32_t vertrix_file_read_word(uint32_t file, uint8_t *buffer, VertrixFileRead read, void *context)
{
    return vertrix_file_read_exact(file, buffer, WORD_BYTES, read, context);
}

uint32_t vertrix_file_read_dword(uint32_t file, uint8_t *buffer, VertrixFileRead read,
                                 void *context)
{
    return vertrix_file_read_exact(file, buffer, DWORD_BYTES, read, context);
}

uint32_t vertrix_file_read_word_swapped(uint32_t file, uint8_t *buffer, VertrixFileRead read,
                                        void *context)
{
    vertrix_file_read_exact(file, buffer, WORD_BYTES, read, context);
    uint8_t low = buffer[0];
    buffer[0] = buffer[1];
    buffer[1] = low;
    return 0;
}

int vertrix_flip_high_bits(uint8_t *buffer, size_t size, uint32_t count)
{
    if (!buffer || count > size)
    {
        return 0;
    }
    for (uint32_t i = 0; i < count; ++i)
    {
        buffer[i] ^= 0x80;
    }
    return 1;
}
