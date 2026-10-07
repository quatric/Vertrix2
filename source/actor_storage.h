#ifndef VERTRIX_ACTOR_STORAGE_H
#define VERTRIX_ACTOR_STORAGE_H
#include <stddef.h>
#include <stdint.h>

#define VERTRIX_ACTOR_BASE_SIZE 0x15c
/* Original 0x4abd70. Write only constructor-defined fields into existing storage.
 * Byte order remains explicitly little endian on all platforms. Original class,
 * resource and handler addresses are identity tokens; never native pointers.
 * Derived actor storage may exceed base size. Short/null storage is preserved. */
int vertrix_actor_storage_construct(void *storage, size_t size);
/* Field widths1/2/4. Invalid bounds/width preserve storage or output. */
int vertrix_actor_storage_read(const void *storage, size_t size, size_t offset, unsigned width,
                               uint32_t *value);
int vertrix_actor_storage_write(void *storage, size_t size, size_t offset, unsigned width,
                                uint32_t value);
#endif
