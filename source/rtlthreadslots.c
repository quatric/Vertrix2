#include "rtlthreadslots.h"

enum
{
    /* The slot set: its TLS index (-1: one shared record, guarded by the critical section +0x20),
     * the shared record (+4), the records' list (+0x18) and the slots each record holds (+0x10). */
    SET_INDEX = 0,
    SET_SHARED = 4,
    SET_SLOTS = 0x10,
    SET_RECORDS = 0x18,
    SET_SECTION = 0x20,
    SHARED_INDEX = 0xffffffffu,

    /* A record: its class, its slot count and its slots. */
    RECORD_CLASS = 0,
    RECORD_COUNT = 8,
    RECORD_SLOTS = 0xc,
    RECORD_SIZE = 0x10,
    RECORD_CLASS_VALUE = 0x51ac34,
    LMEM_MOVEABLE = 2,

    ENTER_CRITICAL_SECTION = 0x4f1b48,
    LEAVE_CRITICAL_SECTION = 0x4f1c40,
    TLS_GET_VALUE = 0x4f1cdc,
    TLS_SET_VALUE = 0x4f1ce0,
    LOCAL_ALLOC = 0x4f1c4c,
    LOCAL_REALLOC = 0x4f1c58,
    ALLOCATE = 0x4dba80,
    LINK = 0x4dba10,
    OUT_OF_MEMORY = 0x4d9510,
    FILL = 0x4eb5c0
};

static int shared(Port *port, uint32_t set)
{
    return port_u32(port, set, SET_INDEX) == SHARED_INDEX;
}

/* EnterCriticalSection or LeaveCriticalSection on the set's section; returns its eax. */
static uint32_t section(Port *port, uint32_t target, uint32_t set, uint32_t eax, uint32_t edx,
                        uint32_t ebx, uint32_t ecx)
{
    const uint32_t args[1] = {set + SET_SECTION};
    return port_call_stack(port, target, eax, edx, ebx, ecx, args, 1);
}

/* Original 0x4dbd20 (eax = the slot set, edx = the slot, ebx = the value): stores a value in the
 * calling thread's record of the set (TlsGetValue of its index, or its shared record +4 under its
 * critical section when the index is -1). A value of 0 for a slot the record lacks stores nothing.
 * Otherwise a missing record is made (0x4dba80 with 0x10 bytes, class 0x51ac34, no slots) and
 * linked into the set's list (0x4dba10, under the section), and a record too short is grown to the
 * set's slot count (LocalAlloc, or LocalReAlloc moveable; 0x4d9510 when that fails), the new slots
 * cleared (0x4eb5c0) and the record kept (TlsSetValue, or +4). Returns the last eax: the slot, or
 * TlsGetValue's or LeaveCriticalSection's. */
uint32_t vertrix_port_rtl_thread_slot_set_4dbd20(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    const uint32_t set = entry->eax;
    const uint32_t slot = entry->edx;
    const uint32_t value = entry->ebx;
    const uint32_t ecx = entry->ecx;
    uint32_t eax;
    uint32_t record;
    if (shared(&port, set))
    {
        eax = section(&port, ENTER_CRITICAL_SECTION, set, set + SET_SECTION, slot, value, ecx);
        record = port_u32(&port, set, SET_SHARED);
    }
    else
    {
        const uint32_t args[1] = {port_u32(&port, set, SET_INDEX)};
        eax = port_call_stack(&port, TLS_GET_VALUE, set, slot, value, ecx, args, 1);
        record = eax;
    }
    if (record == 0 || (int32_t)slot >= (int32_t)port_u32(&port, record, RECORD_COUNT))
    {
        if (value == 0)
        {
            if (shared(&port, set))
            {
                eax = section(&port, LEAVE_CRITICAL_SECTION, set, set + SET_SECTION,
                              vertrix_lift_edx, value, ecx);
            }
            return port_return(&port, eax, vertrix_lift_edx);
        }
        if (record == 0)
        {
            const uint32_t args[1] = {RECORD_SIZE};
            record = port_call_stack(&port, ALLOCATE, eax, vertrix_lift_edx, value, ecx, args, 1);
            if (record != 0)
            {
                port_set32(&port, record, RECORD_CLASS, RECORD_CLASS_VALUE);
            }
            port_set32(&port, record, RECORD_COUNT, 0);
            port_set32(&port, record, RECORD_SLOTS, 0);
            if (shared(&port, set))
            {
                section(&port, ENTER_CRITICAL_SECTION, set, set + SET_SECTION, vertrix_lift_edx,
                        value, ecx);
            }
            port_call(&port, LINK, set + SET_RECORDS, record, value, ecx);
            if (shared(&port, set))
            {
                section(&port, LEAVE_CRITICAL_SECTION, set, set + SET_SECTION, vertrix_lift_edx,
                        value, ecx);
            }
        }
        const uint32_t bytes = port_u32(&port, set, SET_SLOTS) * 4;
        uint32_t slots;
        if (port_u32(&port, record, RECORD_SLOTS) == 0)
        {
            const uint32_t args[2] = {0, bytes};
            slots =
                port_call_stack(&port, LOCAL_ALLOC, bytes, vertrix_lift_edx, value, ecx, args, 2);
        }
        else
        {
            const uint32_t args[3] = {port_u32(&port, record, RECORD_SLOTS), bytes, LMEM_MOVEABLE};
            slots =
                port_call_stack(&port, LOCAL_REALLOC, bytes, vertrix_lift_edx, value, ecx, args, 3);
        }
        port_set32(&port, record, RECORD_SLOTS, slots);
        if (port_u32(&port, record, RECORD_SLOTS) == 0)
        {
            if (shared(&port, set))
            {
                section(&port, LEAVE_CRITICAL_SECTION, set, set + SET_SECTION, vertrix_lift_edx,
                        value, ecx);
            }
            port_call_with(&port, OUT_OF_MEMORY, 0, vertrix_lift_edx, value, ecx, set, record,
                           value);
        }
        const uint32_t count = port_u32(&port, record, RECORD_COUNT);
        port_call(&port, FILL, port_u32(&port, record, RECORD_SLOTS) + count * 4, 0,
                  (port_u32(&port, set, SET_SLOTS) - count) * 4, ecx);
        port_set32(&port, record, RECORD_COUNT, port_u32(&port, set, SET_SLOTS));
        if (!shared(&port, set))
        {
            const uint32_t args[2] = {port_u32(&port, set, SET_INDEX), record};
            port_call_stack(&port, TLS_SET_VALUE, port_u32(&port, set, SET_SLOTS), vertrix_lift_edx,
                            value, ecx, args, 2);
        }
        else
        {
            port_set32(&port, set, SET_SHARED, record);
        }
    }
    port_set32(&port, port_u32(&port, record, RECORD_SLOTS), slot * 4, value);
    eax = slot;
    if (shared(&port, set))
    {
        eax = section(&port, LEAVE_CRITICAL_SECTION, set, set + SET_SECTION, vertrix_lift_edx,
                      port_u32(&port, record, RECORD_SLOTS), ecx);
    }
    return port_return(&port, eax, vertrix_lift_edx);
}
