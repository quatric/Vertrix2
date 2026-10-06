#ifndef VERTRIX_HANDLE_REGISTRY_H
#define VERTRIX_HANDLE_REGISTRY_H
#include <stdint.h>
/* Small registries and guarded calls of the runtime support layer (0x40a860..0x40aca0). Calls
 * through the library function pointers at 0x52f020, 0x52f03c and 0x52f058, the string
 * assignment 0x4eb860 and the release 0x4ea190 are supplied callbacks. */

enum
{
    VERTRIX_REGISTRY_SLOTS = 8,
    VERTRIX_REGISTRY_FULL = 8,
    VERTRIX_HANDLE_SLOTS = 32,
    VERTRIX_HANDLE_BAD = 1,
    VERTRIX_HANDLES_BUSY = 3,
    VERTRIX_GUARD_DISABLED = 0xffff,
    VERTRIX_TEXT_COUNT = 12,
    VERTRIX_TEXT_INVALID = 2
};

/* Original0x40a890: store value in the first empty slot of the eight (0x52f090) unless it is
 * already present before the first empty slot. Returns 0, or 8 when the slots are full. */
uint32_t vertrix_registry_add(uint32_t slots[VERTRIX_REGISTRY_SLOTS], uint32_t value);

/* Original0x40ad50: handle numbers start at 1. Clears the entry (table 0x52f0b0) for handles up
 * to count (dword 0x52f130, at most 32) and returns 0, else returns 1 untouched. */
uint32_t vertrix_handles_release(uint32_t table[VERTRIX_HANDLE_SLOTS], uint32_t count,
                                 uint32_t handle);

/* Supplied boundary for the library entry 0x52f03c taking the requested count. */
typedef uint32_t (*VertrixHandlesStart)(uint32_t count, void *context);

/* Original0x40ab60: zero the 32 entries, call start(count) and, when it returns zero, store the
 * count in *stored (dword 0x52f130). Returns the callback result. */
uint32_t vertrix_handles_init(uint32_t table[VERTRIX_HANDLE_SLOTS], uint32_t *stored,
                              uint32_t count, VertrixHandlesStart start, void *context);

typedef struct
{
    uint32_t disabled_id; /* 0x4f6418, 0xffff disables the guarded call */
    uint32_t depth;       /* 0x4f644c */
} VertrixCallGuard;

/* Supplied boundary for the library entry 0x52f020 taking one argument. */
typedef uint32_t (*VertrixGuardedCall)(uint32_t argument, void *context);

/* Original0x40ab20: unless disabled, run the call only when no other guarded call is active
 * (depth 1 after incrementing). Returns the call's result, else 0. */
uint32_t vertrix_guarded_call(VertrixCallGuard *guard, uint32_t argument, VertrixGuardedCall call,
                              void *context);

/* Supplied boundaries: library entry 0x52f058 (no arguments) and release 0x4ea190. */
typedef uint32_t (*VertrixCloseCall)(void *context);
typedef void (*VertrixRelease)(uint32_t object, void *context);

/* Original0x40aca0: a null cell returns 1. Otherwise close() runs first, then the object held
 * in the cell is released when nonzero (the cell is left unchanged). Returns the close result. */
uint32_t vertrix_close_cell(const uint32_t *cell, VertrixCloseCall close, VertrixRelease release,
                            void *context);

/* Supplied boundary for the string assignment 0x4eb860 (destination, source). */
typedef void (*VertrixAssignText)(uint32_t destination, uint32_t source, void *context);

/* Original0x40a860: assign the text for a code from the twelve at 0x4f641c to the destination.
 * A null destination returns 2 without assigning; a code above 11 assigns text 0 and returns 2;
 * otherwise returns 0. */
uint32_t vertrix_text_for_code(uint32_t code, uint32_t destination,
                               const uint32_t texts[VERTRIX_TEXT_COUNT], VertrixAssignText assign,
                               void *context);

/* Supplied boundary for the library entry 0x52f040 (no arguments). */
typedef uint32_t (*VertrixHandlesStop)(void *context);

/* Original0x40aba0: when any of the first *count entries is nonzero returns 3 and changes
 * nothing. Otherwise clears the count and the 32 entries, calls stop() and returns its result;
 * the count (which stop may have changed) is then stored back unchanged. */
uint32_t vertrix_handles_shutdown(uint32_t table[VERTRIX_HANDLE_SLOTS], uint32_t *count,
                                  VertrixHandlesStop stop, void *context);
#endif
