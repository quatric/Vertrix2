#include "port_rtlglobaleffects.h"

/* Song-wide effects of the mixer. */

/* Original 0x40d880: the speed effect of the note eax: outside a row's first tick (0x531b4c 0) its
 * value +4 from 0x20 up is the tempo (0x531b64, 0x531b44 marked 8), from 1 up the speed
 * (0x531b60), 0 ignored. eax the value when kept, edx kept. */
uint32_t vertrix_port_mixer_speed_effect_40d880(PORT_SIGNATURE)
{
    Port port;
    uint32_t eax = entry->eax;
    uint32_t value;
    port_open_frame(&port, calls, services, globals, entry, 4);
    port_set32(&port, entry->esp, -4u, entry->edx);
    if (port_u32(&port, 0, 0x531b4c) != 0)
    {
        return port_return(&port, eax, entry->edx);
    }
    value = port_u8(&port, eax, 4);
    if (value >= 0x20)
    {
        eax = value;
        port_set32(&port, 0, 0x531b64, eax);
        port_set8(&port, 0, 0x531b44, port_u8(&port, 0, 0x531b44) | 8);
    }
    else if (value >= 1)
    {
        eax = value;
        port_set32(&port, 0, 0x531b60, eax);
    }
    return port_return(&port, eax, entry->edx);
}
