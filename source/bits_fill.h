#ifndef VERTRIX_BITS_FILL_H
#define VERTRIX_BITS_FILL_H
#include <stdint.h>

#include "block_factory.h"
#include "call_glue.h"

/* The two width tables the fill reads (0x4f5e78 and 0x4f5e88, sixteen bytes each): the services
 * resolve VERTRIX_BITS_TABLES to the storage of both. */
enum
{
    VERTRIX_BITS_TABLES = 0x4f5e78,
    VERTRIX_BITS_TABLE_SIZE = 0x20
};

/* Original 0x4074a0 (eax = output array, edx = object): reads bit fields with 0x404680 (eax = the
 * width) into the dword array at `out` and returns the total number of bits. The widths are D and
 * B, the bytes of the tables at the object's index (+0xc). With the mode at +0x10 equal to two
 * there are 18 (17 when the flag at +0x14 is set, which also takes D off the total) reads of D
 * then 18 of B; otherwise the flags dword at +0 selects: negative gives 11 reads of D and ten of
 * B, else bits 3, 2, 1 and 0 each skip (zero fill) or read 6 D, 5 D, 5 B and 5 B. The array ends
 * with a zero dword (three in the first case). Returns zero when a table, the object or the array
 * cannot be accessed. */
int vertrix_bits_fill(const VertrixCalls *calls, const VertrixFactoryServices *services,
                      uint32_t out, uint32_t object, uint32_t *total);

/* The word table the header reads (0x4f5918, 144 bytes for each selector): the services resolve
 * VERTRIX_BITS_WORDS to its storage. */
enum
{
    VERTRIX_BITS_WORDS = 0x4f5918,
    VERTRIX_BITS_WORDS_SIZE = 0x500
};

/* Original 0x407280 (eax = record, edx = count, ebx = flag, ecx = selector; stack: mode, ret 4):
 * reads the header of a coded frame into the record with 0x404610, 0x404680 and 0x4046e0. The first
 * two dwords come from 0x404610(8) and either 0x4046e0 (count one) or 0x404680(2); then for each of
 * `count` entries of 0xd0 bytes from record + 8, fields are read and derived (the flag adds eight
 * to the pointer at +0x64, a mode of zero calls 0x4eb4d4, an entry without the extension bit
 * takes its sizes from the word table by selector). Mode three (the argument) makes the call
 * register ecx four, else zero. Returns zero when the record or a table cannot be accessed. */
int vertrix_bits_header(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        uint32_t record, int32_t count, uint32_t flag, uint32_t selector,
                        uint32_t mode);

#endif
