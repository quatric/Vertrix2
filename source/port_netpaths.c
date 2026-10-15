#include "port_netpaths.h"

/* The network path test. */

/* Original 0x488940: 1 when the path eax starts with two backslashes, else 0. edx kept. */
uint32_t vertrix_port_path_is_network_488940(PORT_SIGNATURE)
{
    Port port;
    uint32_t first;
    port_open(&port, calls, services, globals, entry);
    first = port_u8(&port, entry->eax, 0);
    return port_return(&port, first == 0x5c && port_u8(&port, entry->eax, 1) == first, entry->edx);
}
