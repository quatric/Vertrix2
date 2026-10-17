#include "port_rtldisplayreadies.h"

enum
{
    DISPLAY_SURFACE = 0,
    DISPLAY_DEVICE = 0x10
};

/* Original 0x47f410 (eax = display): 1 when both its first field and its field +0x10 are set, else
 * 0 (the shared `xor eax, eax; ret` at 0x47ed00). edx is the caller's: its callers read it on. */
uint32_t vertrix_port_display_ready_47f410(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    const uint32_t display = entry->eax;
    const uint32_t ready = port_u32(&port, display, DISPLAY_SURFACE) != 0 &&
                           port_u32(&port, display, DISPLAY_DEVICE) != 0;
    return port_return(&port, ready, entry->edx);
}
