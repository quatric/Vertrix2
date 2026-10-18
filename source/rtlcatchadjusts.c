#include "rtlcatchadjusts.h"

enum
{
    /* The descriptor (eax): the offset of the record, the offset added to the found address, and
     * the routine called with it. */
    DESCRIPTOR_OFFSET = 4,
    DESCRIPTOR_ADJUST = 8,
    DESCRIPTOR_ROUTINE = 0xc,
    RECORD_FLAGS = 4
};

/* Original 0x4cd819 (eax = a descriptor, ebx = an object, ecx = a flag mask): the record at the
 * object's +4 plus the descriptor's +4. When its flag byte (+4) shares a bit with the mask, returns
 * the record; otherwise calls the descriptor's routine (+0xc) on the record's first dword plus the
 * descriptor's +8, with the flag byte in ebx, and returns what it returns. edx is kept. */
uint32_t vertrix_port_catch_adjust_4cd819(PORT_SIGNATURE)
{
    Port port;
    port_open_frame(&port, calls, services, globals, entry, 0);
    const uint32_t descriptor = entry->eax;
    const uint32_t record =
        port_u32(&port, entry->ebx, 4) + port_u32(&port, descriptor, DESCRIPTOR_OFFSET);
    const uint32_t flags = port_u8(&port, record, RECORD_FLAGS);
    if ((flags & entry->ecx) != 0)
    {
        return port_return(&port, record, entry->edx);
    }
    const uint32_t address =
        port_u32(&port, record, 0) + port_u32(&port, descriptor, DESCRIPTOR_ADJUST);
    const uint32_t result = port_call(&port, port_u32(&port, descriptor, DESCRIPTOR_ROUTINE),
                                      address, entry->edx, flags, entry->ecx);
    return port_return(&port, result, vertrix_lift_edx);
}
