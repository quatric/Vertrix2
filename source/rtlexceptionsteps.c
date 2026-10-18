#include "rtlexceptionsteps.h"

/* A rethrow: a new exception object (0x4e0f8b), raised again from the innermost frame at fs:[0]
 * with the state its catch block was at, through the runtime's raise steps on a record in the
 * frame. The frame's state is then the one the raise left. */

enum
{
    /* The locals from esp up: the raise record (its +4 the new state) and at +0x10 the exception,
     * the frame and the frame's handler table. */
    BELOW = 0x28,
    RAISE = 0,
    RAISE_STATE = 4,
    THROWN = 0x10,
    THROWN_FRAME = 0x14,
    THROWN_TABLE = 0x18,

    FRAME_TABLE = 8,
    FRAME_STATE = 0xc,
    ENTRY_COUNT = 4,

    NEW_EXCEPTION = 0x4e0f8b,
    FIND_ENTRY = 0x4e0a95,
    PREPARE = 0x4e0eaf,
    PREPARE_RECORD = 0x4e0ec7,
    RAISE_FROM = 0x4e0b7c,
    RAISE_END = 0x4e0b9e
};

/* Original 0x4da6b6. Returns the new state in eax (callers never read edx). */
uint32_t vertrix_port_exception_chain_step_4da6b6(PORT_SIGNATURE)
{
    Port port;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    const uint32_t locals = entry->esp - BELOW;
    const uint32_t thrown = locals + THROWN;
    port_set32(&port, thrown, 0,
               port_call(&port, NEW_EXCEPTION, entry->eax, entry->edx, entry->ebx, entry->ecx));
    const uint32_t frame = port.env.chain;
    port_set32(&port, locals, THROWN_FRAME, frame);
    port_set32(&port, locals, THROWN_TABLE, port_u32(&port, frame, FRAME_TABLE));
    const uint32_t found = port_call(&port, FIND_ENTRY, port_u32(&port, frame, FRAME_TABLE),
                                     port_u32(&port, frame, FRAME_STATE), entry->ebx, frame);
    const uint32_t count = port_u32(&port, found, ENTRY_COUNT) - 1;
    const uint32_t prepared = port_call(&port, PREPARE, thrown, frame, count, frame);
    port_call(&port, PREPARE_RECORD, prepared, thrown, count, frame);
    port_call(&port, RAISE_FROM, locals + RAISE, thrown, count, frame);
    port_call(&port, RAISE_END, locals + RAISE, thrown, count, frame);
    const uint32_t state = port_u32(&port, locals, RAISE_STATE);
    port_set32(&port, frame, FRAME_STATE, state);
    return port_return(&port, state, entry->edx);
}
