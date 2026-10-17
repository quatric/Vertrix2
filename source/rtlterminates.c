#include "rtlterminates.h"

enum
{
    FORMAT_OUTPUT = 0x4df320,
    /* Appends a character at the buffer's pointer. */
    PUT_CHARACTER = 0x4cd090
};

/* Original 0x4cd0a4 (eax = the buffer, edx = the format, ebx = the address of the va_list):
 * vsprintf. The printf core (0x4df320) writes through 0x4cd090; the text is terminated after the
 * count it returns, which is the result. */
uint32_t vertrix_port_rtl_vsprintf_4cd0a4(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    const uint32_t buffer = entry->eax;
    const uint32_t length =
        port_call(&port, FORMAT_OUTPUT, buffer, entry->edx, entry->ebx, PUT_CHARACTER);
    port_set8(&port, buffer, length, 0);
    return port_return(&port, length, 0);
}
