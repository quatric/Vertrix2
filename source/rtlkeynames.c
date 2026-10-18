#include "rtlkeynames.h"

/* Key names read from the key table. */

/* Original 0x416c10: the name of the key dx (zero-extended) of the key table 0x54d640 put into
 * the string eax (0x476160). eax the string. */
uint32_t vertrix_port_key_name_416c10(PORT_SIGNATURE)
{
    Port port;
    uint32_t text = entry->eax;
    port_open_frame(&port, calls, services, globals, entry, 8);
    port_set32(&port, entry->esp, -4u, entry->ebx);
    port_set32(&port, entry->esp, -8u, entry->ecx);
    port_call_with(&port, 0x476160, 0x54d640, text, entry->edx & 0xffff, text, entry->esi,
                   entry->edi, entry->ebp);
    return port_return(&port, text, vertrix_lift_edx);
}
