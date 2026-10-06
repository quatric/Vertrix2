#ifndef VERTRIX_STREAM_READ_H
#define VERTRIX_STREAM_READ_H
#include <stddef.h>
#include <stdint.h>

/* A memory stream object holds the original addresses of the read position (+4) and the end
 * (+8). They are identity tokens: bytes are fetched through a supplied reader, never by native
 * pointer arithmetic. */
typedef void (*VertrixStreamFetch)(void *context, uint32_t address, uint8_t *destination,
                                   uint32_t count);

/* Original0x48a930: read size * count bytes (32-bit product) into destination. When fewer
 * remain, read what remains. Returns 1 in *complete when the whole request was available. The
 * position advances by the bytes read. Returns 0 for short storage. */
int vertrix_stream_read_exact(void *stream, size_t size, uint32_t item_size, uint32_t count,
                              uint8_t *destination, VertrixStreamFetch fetch, void *context,
                              uint32_t *complete);

/* Original0x48a9d0: as above but returns the number of bytes read in *bytes_read. */
int vertrix_stream_read(void *stream, size_t size, uint32_t item_size, uint32_t count,
                        uint8_t *destination, VertrixStreamFetch fetch, void *context,
                        uint32_t *bytes_read);

/* Original0x48aa90: advance the position. A non-negative delta is limited to the remaining
 * bytes; a negative delta advances by its magnitude without a limit. *applied (the original
 * global 0x5bb24c) receives the amount added. Returns 0 for short storage. */
int vertrix_stream_skip(void *stream, size_t size, int32_t delta, uint32_t *applied);
#endif
