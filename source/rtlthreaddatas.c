#include "rtlthreaddatas.h"
#include "rtlthreadslotgets.h"

enum
{
    /* The runtime's thread data: its slot (0x5c5c60, made by 0x4ce7c0) holds a record whose +4 is
     * the data, else the data comes from the slot 0x5c5c64 (made by 0x4ce810). The data's +0x1034
     * slot index makes its own value with 0x4ce7e0. */
    DATA_SLOT = 0x5c5c60,
    DATA_MAKER = 0x4ce7c0,
    FALLBACK_SLOT = 0x5c5c64,
    FALLBACK_MAKER = 0x4ce810,
    RECORD_DATA = 4,
    FIRST_SLOT = 0x1034,
    FIRST_MAKER = 0x4ce7e0,

    THREAD_SLOT = 0x4dbf80,
    THREAD_DATA = 0x4ce740
};

/* The original jumps to a routine with eax and edx set: its rewrite runs here on the same stack,
 * as the original's own code. */
static uint32_t jump(uint32_t (*target)(PORT_SIGNATURE), const VertrixCalls *calls,
                     const VertrixFactoryServices *services, const VertrixGlobals *globals,
                     const LiftEntry *entry, uint32_t eax, uint32_t edx)
{
    LiftEntry jumped = *entry;
    jumped.eax = eax;
    jumped.edx = edx;
    return target(calls, services, globals, &jumped);
}

/* Original 0x4ce740: the calling thread's runtime data: the +4 of its record in the slot 0x5c5c60
 * (0x4dbf80 with the maker 0x4ce7c0), or, when that is 0, the value of the slot 0x5c5c64 (the
 * original jumps to 0x4dc030 with the maker 0x4ce810). edx is the last callee's. */
uint32_t vertrix_port_rtl_thread_data_4ce740(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    const uint32_t record =
        port_forward(&port, entry, THREAD_SLOT, DATA_SLOT, DATA_MAKER, entry->ebx, entry->ecx);
    const uint32_t edx = vertrix_lift_edx;
    if (port.env.failed)
    {
        return port_return(&port, 0, edx);
    }
    if (port_u32(&port, record, RECORD_DATA) == 0)
    {
        return jump(vertrix_port_rtl_thread_slot_get_4dc030, calls, services, globals, entry,
                    FALLBACK_SLOT, FALLBACK_MAKER);
    }
    return port_return(&port, port_u32(&port, record, RECORD_DATA), edx);
}

/* Original 0x4ce760: the value of the thread data's slot +0x1034 (0x4ce740, then the original
 * jumps to 0x4dc030 with the maker 0x4ce7e0). */
uint32_t vertrix_port_rtl_thread_data_first_4ce760(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    const uint32_t data =
        port_forward(&port, entry, THREAD_DATA, entry->eax, entry->edx, entry->ebx, entry->ecx);
    if (port.env.failed)
    {
        return port_return(&port, 0, vertrix_lift_edx);
    }
    return jump(vertrix_port_rtl_thread_slot_get_4dc030, calls, services, globals, entry,
                data + FIRST_SLOT, FIRST_MAKER);
}
