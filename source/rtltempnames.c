#include "rtltempnames.h"

enum
{
    PROCESS_ID = 0x4e9d10, /* GetCurrentProcessId through its import */
    TEMP_DIRECTORY = 0x4e9e30
};

/* 0x4e7f0c's digit: 0-9, then a-f. */
static uint32_t hex_digit(uint32_t value)
{
    value += '0';
    return value > '9' ? value + 0x27 : value;
}

/* Original 0x4e7f18 (eax = the name, edx = the number): a temporary file's name, the temporary
 * directory (0x4e9e30) then "t", the process id's halves or'ed as four hex digits, "_", the
 * number's low byte as two hex digits and ".tmp". Returns edx at the "t" (eax the last digit). */
uint32_t vertrix_port_rtl_temp_name_4e7f18(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    const uint32_t name = entry->eax;
    const uint32_t number = entry->edx;
    const uint32_t id = port_call(&port, PROCESS_ID, name, number, 0, 0);
    uint32_t mixed = id | id >> 16;
    const uint32_t directory = port_call(&port, TEMP_DIRECTORY, name, number, mixed, 0);
    uint32_t length = 0;
    for (;; length++)
    {
        const uint32_t byte = port_u8(&port, directory, length);
        port_set8(&port, name, length, byte);
        if (byte == 0 || port.env.failed)
        {
            break;
        }
    }
    const uint32_t at = name + length;
    port_set8(&port, at, 0, 't');
    for (uint32_t i = 4; i >= 1; i--)
    {
        port_set8(&port, at, i, hex_digit(mixed & 0xf));
        mixed >>= 4;
    }
    port_set8(&port, at, 5, '_');
    port_set8(&port, at, 6, hex_digit((uint32_t)((int32_t)number >> 4) & 0xf));
    const uint32_t last = hex_digit(number & 0xf);
    port_set8(&port, at, 8, '.');
    port_set8(&port, at, 9, 't');
    port_set8(&port, at, 10, 'm');
    port_set8(&port, at, 11, 'p');
    port_set8(&port, at, 12, 0);
    port_set8(&port, at, 7, last);
    return port_return(&port, last, at);
}
