#include "native_dispatch.h"
#include "game_frame.h"
#include "title_frame.h"

uint32_t vertrix_native_title_frame(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services,
                                    const VertrixGlobals *globals, const LiftEntry *entry)
{
    (void)services;
    return vertrix_title_frame(calls, globals, entry->eax);
}

uint32_t vertrix_native_game_frame(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, const LiftEntry *entry)
{
    (void)services;
    return vertrix_game_frame(calls, globals, entry->eax);
}
