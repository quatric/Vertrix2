#include "rtlrangefinds.h"

enum
{
    ARGUMENT_TABLE = 4,
    ARGUMENT_FIRST = 8,
    ARGUMENT_SECOND = 0xc,
    ARGUMENT_VALUE = 0x10,
    ARGUMENTS = 4,

    /* An entry: two keys, the low and high bounds of a range, and a nonzero tag; a zero tag ends
     * the table. */
    ENTRY_FIRST = 0,
    ENTRY_SECOND = 4,
    ENTRY_LOW = 8,
    ENTRY_HIGH = 0xc,
    ENTRY_TAG = 0x10,
    ENTRY_SIZE = 0x20
};

/* Original 0x4d0b30 (stdcall: the table, two keys, a value; ret 0x10): the first entry whose keys
 * match and whose range holds the value (unsigned, both ends included), or 0. No caller reads
 * edx. */
uint32_t vertrix_port_rtl_range_table_find_4d0b30(PORT_SIGNATURE)
{
    Port port;
    uint8_t stack[8 + 4 * ARGUMENTS];
    port_open_arguments(&port, stack, calls, services, globals, entry, 0, ARGUMENTS);
    const uint32_t first = port_u32(&port, entry->esp, ARGUMENT_FIRST);
    const uint32_t second = port_u32(&port, entry->esp, ARGUMENT_SECOND);
    const uint32_t value = port_u32(&port, entry->esp, ARGUMENT_VALUE);
    for (uint32_t item = port_u32(&port, entry->esp, ARGUMENT_TABLE);
         port_u32(&port, item, ENTRY_TAG) != 0 && !port.env.failed; item += ENTRY_SIZE)
    {
        if (first == port_u32(&port, item, ENTRY_FIRST) &&
            second == port_u32(&port, item, ENTRY_SECOND) &&
            value >= port_u32(&port, item, ENTRY_LOW) && value <= port_u32(&port, item, ENTRY_HIGH))
        {
            return port_return(&port, item, 0);
        }
    }
    return port_return(&port, 0, 0);
}
