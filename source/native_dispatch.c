#include "native_dispatch.h"
#include "game_frame.h"
#include "native_ports.h"
#include "s3m_pattern.h"
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

uint32_t vertrix_native_s3m_pattern(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services,
                                    const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint32_t result = 0;
    if (!vertrix_s3m_pattern(calls, services, globals, entry->eax, entry->edx, entry->ebx,
                             entry->ecx, entry->arguments[0], &result))
    {
        /* Memory the host cannot reach (the original would fault): answer the routine's own
         * allocation failure so the loader at 0x410ca3 releases the module and stops. */
        return 8;
    }
    return result;
}

uint32_t vertrix_native_kind_snapshot(const VertrixCalls *calls,
                                      const VertrixFactoryServices *services,
                                      const VertrixGlobals *globals, const LiftEntry *entry)
{
    VertrixNativeMemory memory = {calls, services, globals, 1};
    return vertrix_port_kind_snapshot(&memory, entry->eax, entry->edx, entry->ebx);
}

uint32_t vertrix_native_bit_read(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                 const VertrixGlobals *globals, const LiftEntry *entry)
{
    VertrixNativeMemory memory = {calls, services, globals, 1};
    (void)entry;
    return vertrix_port_bit_read(&memory);
}

uint32_t vertrix_native_line_pass(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  const VertrixGlobals *globals, const LiftEntry *entry)
{
    VertrixNativeMemory memory = {calls, services, globals, 1};
    return vertrix_port_line_pass(&memory, entry->eax, entry->edx, entry->ebx, entry->ecx);
}
