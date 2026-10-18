#include "rtlexceptioncatches.h"

enum
{
    /* The record (eax): its current and end pointers. The handler found: 0 when it catches by
     * type, then its type record, whose first byte is the kind. */
    RECORD_CURRENT = 4,
    RECORD_END = 8,
    HANDLER_KIND = 0,
    HANDLER_TYPE = 4,
    KIND_LAST = 0xf,

    HANDLER_FIND = 0x4e0bed,
    BAD_KIND = 0x4e0bf8
};

/* Original 0x4cd7dc (eax = a record): the record's handler (0x4e0bed), returned. A handler that
 * catches by type, on a record whose current and end pointers differ, has its type's kind checked:
 * kinds 1, 5 and 14, and those above 16, are reported by 0x4e0bf8 (eax the kind - 1, its upper
 * bits the type pointer's when above 16; ebx the record's current pointer; ecx the handler). The
 * caller's edx is kept. */
uint32_t vertrix_port_rtl_exception_catch_4cd7dc(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    const uint32_t record = entry->eax;
    const uint32_t handler = port_call(&port, HANDLER_FIND, record, record, entry->ebx, entry->ecx);
    if (handler == 0 || port_u32(&port, handler, HANDLER_KIND) != 0)
    {
        return port_return(&port, handler, entry->edx);
    }
    const uint32_t current = port_u32(&port, record, RECORD_CURRENT);
    if (current == port_u32(&port, record, RECORD_END))
    {
        return port_return(&port, handler, entry->edx);
    }
    const uint32_t type = port_u32(&port, handler, HANDLER_TYPE);
    const uint32_t kind = (port_u8(&port, type, 0) - 1) & 0xff;
    if (kind > KIND_LAST)
    {
        port_call(&port, BAD_KIND, (type & 0xffffff00u) | kind, record, current, handler);
    }
    else if (kind == 0 || kind == 4 || kind == 13)
    {
        port_call(&port, BAD_KIND, kind, record, current, handler);
    }
    return port_return(&port, handler, entry->edx);
}
