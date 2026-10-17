#include "rtlrecordreleases.h"

/* Releases an exception record and its stream under a guard frame. */

enum
{
    /* The frame below the return slot; the guard record the helpers fill sits 0x34 below it. */
    BELOW = 0x50,
    GUARD = 0x34,

    RECORD_INFO = 0x8,
    RECORD_STATE = 0xc,
    RECORD_STREAM = 0x24,
    INFO_HANDLER = 0xc,
    /* The info kinds whose handler runs, and the state the record takes while it runs. */
    KIND_PLAIN = 0,
    KIND_STREAM = 4,
    RUNNING = 6,

    INFO_LOOKUP = 0x4e37fe,
    GUARD_ENTER = 0x4e36d2,
    GUARD_LEAVE = 0x4e36e4,
    RECORD_FREE = 0x4e0e69
};

/* Original 0x4e0ec7 (eax = a record, edx = its owner): nothing for a null record. Otherwise looks
 * up the record's info (0x4e37fe with +8); for info kinds 0 and 4 with a handler at info +0xc,
 * enters a guard (0x4e36d2: the guard, the owner, ebx 0, ecx 6 and the record on the stack), marks
 * the record running (+0xc = 6), calls the handler with the record's +0x24 (the record, the owner
 * and the handler in esi, edi and ebp, as the original leaves them) and leaves the guard
 * (0x4e36e4). Then frees the record (0x4e0e69 with the owner and the record). No caller reads a
 * result. The exception frame at fs:[0] and its state words are left out (docs/NATIVE-PORTS.md). */
uint32_t vertrix_port_rtl_record_release_guarded_4e0ec7(PORT_SIGNATURE)
{
    Port port;
    uint8_t stack[BELOW + 8];
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    const uint32_t record = entry->eax;
    const uint32_t owner = entry->edx;
    if (record == 0)
    {
        return port_return(&port, 0, 0);
    }
    const uint32_t info =
        port_call(&port, INFO_LOOKUP, port_u32(&port, record, RECORD_INFO), 0, 0, 0);
    const uint32_t kind = port_u8(&port, info, 0);
    if (kind == KIND_PLAIN || kind == KIND_STREAM)
    {
        const uint32_t handler = port_u32(&port, info, INFO_HANDLER);
        if (handler != 0)
        {
            const uint32_t guard = entry->esp - GUARD;
            port_call_stack(&port, GUARD_ENTER, guard, owner, 0, RUNNING, &record, 1);
            port_set8(&port, record, RECORD_STATE, RUNNING);
            port_call_with(&port, handler, record + RECORD_STREAM, 0, 0, RUNNING, record, owner,
                           handler);
            port_call(&port, GUARD_LEAVE, guard, 0, 0, 0);
        }
    }
    port_call(&port, RECORD_FREE, owner, record, 0, 0);
    return port_return(&port, 0, 0);
}
