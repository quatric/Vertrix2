#ifndef VERTRIX_MODULE_LOAD_H
#define VERTRIX_MODULE_LOAD_H
#include <stdint.h>

#include "block_factory.h"
#include "call_glue.h"

/* The scratch the loader reads the file into (0x531b8c: the title, 31 sample headers of 30 bytes
 * from 0x531ba0, the song length and restart bytes at 0x531f42, the 0x80 byte pattern table at
 * 0x531f44, the signature at 0x531fc4 and a sample header copy at 0x531fc8) and the table of the
 * 20 module signatures with their channel counts (0x4f7594, 8 bytes each): the services resolve
 * both handles to their storage. */
enum
{
    VERTRIX_MODULE_SCRATCH = 0x531b8c,
    VERTRIX_MODULE_SCRATCH_SIZE = 0x460,
    VERTRIX_MODULE_SIGNATURES = 0x4f7594,
    VERTRIX_MODULE_SIGNATURES_SIZE = 0xa0
};

/* Original 0x40f360 (ebx = stream, edx = pointer for the result; eax and ecx are the caller's
 * registers): loads a tracker module. 0x40c1c0 opens the file (a non-zero answer returns 0xa),
 * 0x40c1f0 selects the stream, 0x4ec160 makes the 0x158 byte module object (8 when it fails; every
 * failure runs 0x40c1e0, and 0x40ef90 on the object first once it exists). 0x40c220, 0x40c360
 * and 0x40c320 read the title (0x14 bytes), the 31 sample headers (name 0x16, big endian length
 * in words, finetune, volume, repeat start and length), the song length, the restart byte, the
 * pattern table and the signature into the scratch. The signature is looked up in the table
 * (0x4ec180 compares its four bytes; the channel count becomes the word at +0x26; none leaves it,
 * and zero releases and answers 0xb). The title is copied into the object by 0x4eb860 (0x14 bytes),
 * +0x20 is 0x8000, +0x22 and +0x24 take the song length and restart bytes, +0x2a is 0x1f, +0x2c 6
 * and +0x2e 0x7d, the pattern table is copied to +0x30 (the highest entry plus one is the word at
 * +0x28) and the bytes from +0x130 mark the channels (zero for the first and last of each four,
 * else 0xff). 0x4ec160 makes the pattern array (+0x150, 12 bytes a pattern) and the sample array
 * (+0x154, 0xfc bytes a sample) and 0x40f1a0 (vertrix_event_pack) reads each pattern (a non-zero
 * answer releases and is returned). Each sample header is copied (0x4eb5e0, 30 bytes) to 0x531fc8,
 * its name copied (0x4eb860, 0x16 bytes) into the sample entry; a sample with a length makes the
 * 0x3c byte sound object (+0x80 flag one and +0xf8 link in the entry; +0x2c the length in bytes,
 * +0x38 0x20ab, loop bytes +0x30 and +0x34 and flag +0x3a bit 4 when the repeat length exceeds one
 * and the repeat start is inside the sample, volume +0x20 (at most 0x40), finetune +0x23, +0x21
 * 0x80); 0x40ac50 makes its buffer (+0x24, failure returned after the release), 0x40c220 reads the
 * samples and 0x40acd0 registers them. Finally 0x40c1e0 runs, the object is stored through the
 * result pointer and zero is returned. *result is the original's eax. Returns zero when memory
 * cannot be accessed. */
int vertrix_module_load(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        uint32_t eax, uint32_t stream, uint32_t result_pointer, uint32_t ecx,
                        uint32_t *result);

#endif
