#ifndef VERTRIX_GUEST_BYTES_H
#define VERTRIX_GUEST_BYTES_H
#include <stddef.h>
#include <stdint.h>

/* Little-endian field access into a flat copy of original object storage. Callers check that
 * the storage is large enough for every offset they touch before using these helpers. */
static inline uint8_t vertrix_guest_get8(const uint8_t *base, size_t offset)
{
    return base[offset];
}

static inline uint16_t vertrix_guest_get16(const uint8_t *base, size_t offset)
{
    return (uint16_t)(base[offset] | (base[offset + 1] << 8));
}

static inline uint32_t vertrix_guest_get32(const uint8_t *base, size_t offset)
{
    return (uint32_t)base[offset] | ((uint32_t)base[offset + 1] << 8) |
           ((uint32_t)base[offset + 2] << 16) | ((uint32_t)base[offset + 3] << 24);
}

static inline void vertrix_guest_set8(uint8_t *base, size_t offset, uint8_t value)
{
    base[offset] = value;
}

static inline void vertrix_guest_set16(uint8_t *base, size_t offset, uint16_t value)
{
    base[offset] = (uint8_t)value;
    base[offset + 1] = (uint8_t)(value >> 8);
}

static inline void vertrix_guest_set32(uint8_t *base, size_t offset, uint32_t value)
{
    vertrix_guest_set16(base, offset, (uint16_t)value);
    vertrix_guest_set16(base, offset + 2, (uint16_t)(value >> 16));
}
#endif
