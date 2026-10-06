#include "handle_registry.h"

uint32_t vertrix_registry_add(uint32_t slots[VERTRIX_REGISTRY_SLOTS], uint32_t value)
{
    uint32_t index = 0;
    while (slots[index] != 0 && slots[index] != value)
    {
        ++index;
        if (index >= VERTRIX_REGISTRY_SLOTS)
        {
            return VERTRIX_REGISTRY_FULL;
        }
    }
    slots[index] = value;
    return 0;
}

uint32_t vertrix_handles_release(uint32_t table[VERTRIX_HANDLE_SLOTS], uint32_t count,
                                 uint32_t handle)
{
    uint32_t index = handle - 1;
    if (index >= count)
    {
        return VERTRIX_HANDLE_BAD;
    }
    table[index] = 0;
    return 0;
}

uint32_t vertrix_handles_init(uint32_t table[VERTRIX_HANDLE_SLOTS], uint32_t *stored,
                              uint32_t count, VertrixHandlesStart start, void *context)
{
    for (int i = 0; i < VERTRIX_HANDLE_SLOTS; ++i)
    {
        table[i] = 0;
    }
    uint32_t result = start(count, context);
    if (result == 0)
    {
        *stored = count;
    }
    return result;
}

uint32_t vertrix_guarded_call(VertrixCallGuard *guard, uint32_t argument, VertrixGuardedCall call,
                              void *context)
{
    if (guard->disabled_id == VERTRIX_GUARD_DISABLED)
    {
        return 0;
    }
    guard->depth += 1;
    if (guard->depth != 1)
    {
        guard->depth -= 1;
        return 0;
    }
    uint32_t result = call(argument, context);
    guard->depth -= 1;
    return result;
}

uint32_t vertrix_close_cell(const uint32_t *cell, VertrixCloseCall close, VertrixRelease release,
                            void *context)
{
    if (cell == 0)
    {
        return 1;
    }
    uint32_t result = close(context);
    uint32_t object = *cell;
    if (object != 0)
    {
        release(object, context);
    }
    return result;
}

uint32_t vertrix_text_for_code(uint32_t code, uint32_t destination,
                               const uint32_t texts[VERTRIX_TEXT_COUNT], VertrixAssignText assign,
                               void *context)
{
    if (destination == 0)
    {
        return VERTRIX_TEXT_INVALID;
    }
    if (code >= VERTRIX_TEXT_COUNT)
    {
        assign(destination, texts[0], context);
        return VERTRIX_TEXT_INVALID;
    }
    assign(destination, texts[code], context);
    return 0;
}

uint32_t vertrix_handles_shutdown(uint32_t table[VERTRIX_HANDLE_SLOTS], uint32_t *count,
                                  VertrixHandlesStop stop, void *context)
{
    for (uint32_t i = 0; i < *count; ++i)
    {
        if (table[i] != 0)
        {
            return VERTRIX_HANDLES_BUSY;
        }
    }
    *count = 0;
    for (int i = 0; i < VERTRIX_HANDLE_SLOTS; ++i)
    {
        table[i] = 0;
    }
    /* The original then stores the count back to itself; stop() may have changed it. */
    return stop(context);
}
