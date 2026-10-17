#include "port_rtlstringsuffixes.h"

enum
{
    /* The text ".\" */
    CURRENT_DIRECTORY = 0x5109ce,
    STRING_SET_TEXT = 0x4ca370,
    STRING_APPEND_TEXT = 0x4ca600
};

/* strlen of a C text in the original's address space (repne scasb). */
static uint32_t text_length(Port *port, uint32_t text)
{
    uint32_t length = 0;
    while (port_u8(port, text, length) != 0 && !port->env.failed)
    {
        length++;
    }
    return length;
}

/* Original 0x489760 (eax = address of a string, edx = a directory, ebx = a path inside it): make
 * the path relative: the string becomes ".\" (0x4ca370) followed by the path past as many
 * characters as the directory has (0x4ca600). Returns 1. */
uint32_t vertrix_port_string_take_after_prefix_489760(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    const uint32_t string = entry->eax;
    const uint32_t directory = entry->edx;
    const uint32_t path = entry->ebx;
    const uint32_t skip = text_length(&port, directory);
    port_call(&port, STRING_SET_TEXT, string, CURRENT_DIRECTORY, 0, 0);
    port_call(&port, STRING_APPEND_TEXT, string, path + skip, 0, 0);
    return port_return(&port, 1, 0);
}
