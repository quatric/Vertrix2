#ifndef VERTRIX_ACTOR_BUILD_H
#define VERTRIX_ACTOR_BUILD_H
#include <stddef.h>
#include <stdint.h>

#include "actor_storage.h"
#include "block_factory.h"
#include "call_glue.h"

/* Helpers shared by the recovered screen builders: reads of the original's static data, sign
 * extension and the byte and word stores into actor storage. */

/* Supplied read of the dword at an original address, which need not be aligned. */
typedef uint32_t (*VertrixGlobalRead)(uint32_t address, void *context);

typedef struct VertrixGlobals
{
    VertrixGlobalRead read;
    void *context;
} VertrixGlobals;

enum
{
    VERTRIX_BUILD_INIT = 0x4adf20,
    VERTRIX_BUILD_INIT_ARGUMENTS = 5
};

static inline uint32_t vertrix_build_sign16(uint32_t value)
{
    return (uint32_t)(int32_t)(int16_t)(uint16_t)value;
}

static inline uint32_t vertrix_build_sign8(uint32_t value)
{
    return (uint32_t)(int32_t)(int8_t)(uint8_t)value;
}

static inline uint32_t vertrix_build_word(uint32_t value)
{
    return value & 0xffff;
}

/* The word at an address of the original's static data. */
static inline uint32_t vertrix_build_global_word(const VertrixGlobals *globals, uint32_t address)
{
    return globals->read(address, globals->context) & 0xffff;
}

/* The dword at an address shifted right arithmetically by 0x10 (`mov r, [address]; sar r, 0x10`):
 * the sign extended word at address + 2. */
static inline uint32_t vertrix_build_global_high16(const VertrixGlobals *globals, uint32_t address)
{
    return (uint32_t)((int32_t)globals->read(address, globals->context) >> 0x10);
}

/* The dword at an address shifted right arithmetically by 0x18: the sign extended byte at
 * address + 3. */
static inline uint32_t vertrix_build_global_high8(const VertrixGlobals *globals, uint32_t address)
{
    return (uint32_t)((int32_t)globals->read(address, globals->context) >> 0x18);
}

/* 0x4adf20 with its five zero stack arguments. */
static inline void vertrix_build_init(const VertrixCalls *calls, uint32_t actor)
{
    static const uint32_t zeros[VERTRIX_BUILD_INIT_ARGUMENTS] = {0, 0, 0, 0, 0};
    vertrix_calln(calls, VERTRIX_BUILD_INIT, actor, 0, 0, 0, zeros, VERTRIX_BUILD_INIT_ARGUMENTS,
                  NULL);
}

static inline int vertrix_build_store(const VertrixFactoryServices *services, uint32_t handle,
                                      uint32_t offset, unsigned width, uint32_t value)
{
    void *storage;
    size_t size;
    return services->resolve(handle, &storage, &size, services->context) &&
           vertrix_actor_storage_write(storage, size, offset, width, value);
}
#endif
