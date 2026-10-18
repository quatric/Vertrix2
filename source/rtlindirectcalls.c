#include "rtlindirectcalls.h"

/* Original 0x484520 (eax = an object): calls the routine its first dword holds, with every
 * register as given (a call through a procedure variable compares all four), and returns its eax.
 * No caller reads edx. */
uint32_t vertrix_port_indirect_call_484520(PORT_SIGNATURE)
{
    Port port;
    port_open_frame(&port, calls, services, globals, entry, 0);
    const uint32_t result = port_call(&port, port_u32(&port, entry->eax, 0), entry->eax, entry->edx,
                                      entry->ebx, entry->ecx);
    return port_return(&port, result, 0);
}
