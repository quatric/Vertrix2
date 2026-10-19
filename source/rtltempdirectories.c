#include "rtltempdirectories.h"

enum
{
    /* The directory, kept once found, and the variables that may name it ("TMP", "TEMP", ...,
     * ending with an empty name). */
    DIRECTORY = 0x50b100,
    LONGEST = 0x103,
    NAMES = 0x50b0ec,

    GETENV = 0x4dac40,
    STRNCPY = 0x4ea470,
    GETCWD = 0x4e3ac0
};

static uint32_t text_length(Port *port, uint32_t text)
{
    uint32_t length = 0;
    while (port_u8(port, text, length) != 0 && !port->env.failed)
    {
        length++;
    }
    return length;
}

/* Original 0x4e9e30: the temporary directory (0x50b100), found the first time: the first of the
 * variables named at 0x50b0ec that is set (getenv, 0x4dac40) and no longer than 0x103 characters
 * (strncpy, 0x4ea470), else the current directory (getcwd(0, 0), 0x4e3ac0, copied); then a
 * backslash when it does not end with one or a slash. Returns the directory. */
uint32_t vertrix_port_rtl_temp_directory_4e9e30(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    if (port_u8(&port, DIRECTORY, 0) != 0)
    {
        return port_return(&port, DIRECTORY, entry->edx);
    }
    uint32_t edx = entry->edx;
    uint32_t ecx = entry->ecx;
    for (uint32_t slot = NAMES; !port.env.failed; slot += 4)
    {
        const uint32_t name = port_u32(&port, slot, 0);
        if (port_u8(&port, name, 0) == 0)
        {
            break;
        }
        const uint32_t value = port_call(&port, GETENV, name, edx, slot, ecx);
        edx = value;
        if (value == 0)
        {
            continue;
        }
        ecx = text_length(&port, value);
        if (ecx <= LONGEST)
        {
            port_call_with(&port, STRNCPY, DIRECTORY, value, LONGEST, ecx, entry->esi,
                           value + ecx + 1, entry->ebp);
            break;
        }
    }
    if (port_u8(&port, DIRECTORY, 0) == 0)
    {
        const uint32_t current = port_call(&port, GETCWD, 0, 0, 0, ecx);
        for (uint32_t i = 0;; i++)
        {
            const uint32_t byte = port_u8(&port, current, i);
            port_set8(&port, DIRECTORY, i, byte);
            if (byte == 0 || port.env.failed)
            {
                break;
            }
        }
    }
    const uint32_t last = DIRECTORY + text_length(&port, DIRECTORY) - 1;
    const uint32_t byte = port_u8(&port, last, 0);
    if (byte != '\\' && byte != '/')
    {
        port_set8(&port, last, 1, '\\');
        port_set8(&port, last, 2, 0);
    }
    return port_return(&port, DIRECTORY, entry->edx);
}
