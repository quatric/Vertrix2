#include "rtlnetworkhandles.h"

/* Closes the network session's event and thread handles. */

enum
{
    /* The handles, in the order they are closed: the one at 0x5bb4a4, the nine from 0x5bb47c,
     * then 0x5bb4a0. */
    FIRST_HANDLE = 0x5bb4a4,
    HANDLES = 0x5bb47c,
    HANDLE_COUNT = 9,
    LAST_HANDLE = 0x5bb4a0,
    CLOSE_HANDLE = 0x4f1b2c
};

static void close_handle(Port *port, uint32_t slot)
{
    const uint32_t handle = port_u32(port, slot, 0);
    if (handle != 0)
    {
        port_call_stack(port, CLOSE_HANDLE, 0, 0, 0, 0, &handle, 1);
        port_set32(port, slot, 0, 0);
    }
}

/* Original 0x48b970: closes each handle that is set and clears it. Returns 1 and the caller's
 * edx. */
uint32_t vertrix_port_network_handles_close_48b970(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    close_handle(&port, FIRST_HANDLE);
    for (uint32_t index = 0; index < HANDLE_COUNT; index++)
    {
        close_handle(&port, HANDLES + index * 4);
    }
    close_handle(&port, LAST_HANDLE);
    return port_return(&port, 1, entry->edx);
}
