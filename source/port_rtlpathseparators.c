#include "port_rtlpathseparators.h"

enum
{
    BACKSLASH = '\\'
};

/* Original 0x4885a0 (eax = start of a path, edx = a place in it): the last backslash at or before
 * the place, looking back no further than the start: its address, or the start when there is none
 * (the place itself when it is not past the start). edx is left as it came: callers read it. */
uint32_t vertrix_port_path_last_separator_4885a0(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    const uint32_t start = entry->eax;
    uint32_t at = entry->edx;
    while (at > start && port_u8(&port, at, 0) != BACKSLASH && !port.env.failed)
    {
        at--;
    }
    return port_return(&port, at, entry->edx);
}
