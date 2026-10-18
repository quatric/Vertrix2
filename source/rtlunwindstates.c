#include "rtlunwindstates.h"

enum
{
    /* The walker: its context (+0: the frame record +4 and the state table +8), the current state,
     * the target state and flags (+0xc, +0xd bit 0: run the cleanups). */
    WALKER_CONTEXT = 0,
    WALKER_STATE = 4,
    WALKER_TARGET = 8,
    WALKER_KIND = 0xc,
    WALKER_FLAGS = 0xd,
    CONTEXT_FRAME = 4,
    CONTEXT_TABLE = 8,
    CONTEXT_FIRST = 0xc,
    FLAG_CLEANUP = 1,
    FRAME_OBJECTS = 0x10,

    /* An entry: 0 when the state has no action, else its action (+4): a kind byte, then the next
     * state or the test and its two next states. */
    KINDS = 0xe,
    KIND_JUMP = 1,
    KIND_TEST = 5,
    KIND_OBJECT = 0xe,
    ACTION_ARGUMENT = 4,
    ACTION_TRUE = 8,
    ACTION_FALSE = 0xc,

    STATE_ENTRY = 0x4e0a95,
    BAD_KIND = 0x4e0bf8,
    OBJECT_LIVE = 0x4e6bff,
    OBJECT_CLEANUP = 0x4e6c1d
};

/* The walk 0x4e0ae5 does from the walker in eax and the state in edx, with the caller's ebx and ecx
 * handed to the first entry lookup. */
static uint32_t walk(Port *port, uint32_t walker, uint32_t state, uint32_t ecx)
{
    uint32_t entry_address;
    uint32_t edx;
    for (;;)
    {
        const uint32_t context = port_u32(port, walker, WALKER_CONTEXT);
        uint32_t objects = port_u32(port, context, CONTEXT_FRAME);
        entry_address =
            port_call(port, STATE_ENTRY, port_u32(port, context, CONTEXT_TABLE), state, state, ecx);
        edx = vertrix_lift_edx;
        if (state == port_u32(port, walker, WALKER_TARGET) ||
            port_u32(port, entry_address, 0) != 0 || port->env.failed)
        {
            break;
        }
        ecx = port_u32(port, entry_address, ACTION_ARGUMENT);
        const uint32_t kind = (port_u8(port, ecx, 0) - 1) & 0xff;
        if (kind >= KINDS)
        {
            port_call(port, BAD_KIND, (entry_address & 0xffffff00u) | kind, edx, state, ecx);
            edx = vertrix_lift_edx;
            break;
        }
        if (kind == KIND_JUMP - 1)
        {
            state = port_u32(port, ecx, ACTION_ARGUMENT);
            continue;
        }
        if (kind == KIND_TEST - 1)
        {
            const uint32_t live = port_call(port, OBJECT_LIVE, objects + FRAME_OBJECTS,
                                            port_u32(port, ecx, ACTION_ARGUMENT), state, ecx);
            state = port_u32(port, ecx, (live & 0xff) != 0 ? ACTION_TRUE : ACTION_FALSE);
            continue;
        }
        if (kind != KIND_OBJECT - 1)
        {
            break;
        }
        objects += FRAME_OBJECTS;
        const uint32_t live =
            port_call(port, OBJECT_LIVE, objects, port_u32(port, ecx, ACTION_ARGUMENT), state, ecx);
        edx = vertrix_lift_edx;
        if ((live & 0xff) == 0)
        {
            state--;
            if (state == port_u32(port, walker, WALKER_TARGET))
            {
                break;
            }
            state--;
            continue;
        }
        if ((port_u8(port, walker, WALKER_FLAGS) & FLAG_CLEANUP) != 0)
        {
            port_call(port, OBJECT_CLEANUP, objects, port_u32(port, ecx, ACTION_ARGUMENT), state,
                      ecx);
            edx = vertrix_lift_edx;
        }
        state--;
        break;
    }
    port_set32(port, walker, WALKER_STATE, state);
    return port_return(port, entry_address, edx);
}

/* Original 0x4e0ae5 (eax = the walker, edx = the state): walks the C++ unwind states of a frame
 * from the state given towards the target (+8), stopping at a state with no action or the target.
 * Kind 1 jumps to its next state, kind 5 to one of two by whether the object of its test is live
 * (0x4e6bff), kind 14 checks its object (0x4e6bff on the frame record's objects +0x10, stepping on)
 * and runs its cleanup (0x4e6c1d) when the walker's flag asks, else steps back two states; other
 * kinds stop, those past 14 through 0x4e0bf8. Stores the state reached (+4) and returns the last
 * entry looked up (0x4e0a95); edx (callers read it) is the last callee's. */
uint32_t vertrix_port_rtl_unwind_walk_4e0ae5(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    return walk(&port, entry->eax, entry->edx, entry->ecx);
}

/* Original 0x4e0b7c (eax = the walker, edx = its context): starts a walk: the context stored, the
 * state from the context's first entry (+4, its +0xc), the target and kind cleared, the cleanup
 * flag cleared, then the walk 0x4e0ae5 the original jumps to. */
uint32_t vertrix_port_rtl_unwind_begin_4e0b7c(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    const uint32_t walker = entry->eax;
    port_set32(&port, walker, WALKER_CONTEXT, entry->edx);
    const uint32_t first =
        port_u32(&port, port_u32(&port, entry->edx, CONTEXT_FRAME), CONTEXT_FIRST);
    port_set32(&port, walker, WALKER_TARGET, 0);
    port_set8(&port, walker, WALKER_KIND, 0);
    port_set32(&port, walker, WALKER_STATE, first);
    port_set8(&port, walker, WALKER_FLAGS, port_u8(&port, walker, WALKER_FLAGS) & ~FLAG_CLEANUP);
    return walk(&port, walker, port_u32(&port, walker, WALKER_STATE), entry->ecx);
}
