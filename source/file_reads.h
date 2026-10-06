#ifndef VERTRIX_FILE_READS_H
#define VERTRIX_FILE_READS_H
#include <stddef.h>
#include <stdint.h>

/* Supplied boundary for the runtime read 0x4ebec0 (buffer, item size, item count, file): fills
 * the buffer with the data read and returns the number of items read. */
typedef uint32_t (*VertrixFileRead)(uint32_t file, uint8_t *buffer, uint32_t size, uint32_t count,
                                    void *context);

/* Original0x40c220: read count single bytes from the file (the global handle 0x52f90c in the
 * original). When fewer than count bytes arrive, zero all count bytes of the buffer. Always
 * returns 0. */
uint32_t vertrix_file_read_exact(uint32_t file, uint8_t *buffer, uint32_t count,
                                 VertrixFileRead read, void *context);

/* Original0x40c260 and 0x40c320 (identical): read one byte. */
uint32_t vertrix_file_read_byte(uint32_t file, uint8_t *buffer, VertrixFileRead read,
                                void *context);
/* Original0x40c2a0: read two bytes. */
uint32_t vertrix_file_read_word(uint32_t file, uint8_t *buffer, VertrixFileRead read,
                                void *context);
/* Original0x40c2e0: read four bytes. */
uint32_t vertrix_file_read_dword(uint32_t file, uint8_t *buffer, VertrixFileRead read,
                                 void *context);

/* Original0x40c360: read two bytes as 0x40c2a0 does (zero on a short read), then swap them.
 * Returns 0. */
uint32_t vertrix_file_read_word_swapped(uint32_t file, uint8_t *buffer, VertrixFileRead read,
                                        void *context);

/* Original0x410890: flip the high bit of count bytes in place (post-read
 * transform used at 0x410ee3). Counts down through zero, so a zero count
 * changes nothing. Returns zero and preserves the buffer when count exceeds
 * size; the original trusts its caller. */
int vertrix_flip_high_bits(uint8_t *buffer, size_t size, uint32_t count);
#endif
