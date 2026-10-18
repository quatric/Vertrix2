#include "memory_fill.h"

enum
{
    FILL_PATTERN = 0x4ec2d0,
    FILL_DWORDS = 0x4ec307
};

uint32_t vertrix_port_fill_bytes(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    port_call(&port, FILL_PATTERN, entry->eax, (entry->edx & 0xff) * 0x01010101u, entry->ebx,
              entry->ebx);
    return port_return(&port, entry->eax, vertrix_lift_edx);
}

uint32_t vertrix_port_fill_pattern(PORT_SIGNATURE)
{
    Port port;
    uint32_t at = entry->eax;
    uint32_t pattern = entry->edx;
    uint32_t count = entry->ecx;
    uint32_t left;
    port_open(&port, calls, services, globals, entry);
    if (count == 0)
    {
        return port_return(&port, at, pattern);
    }
    while ((at & 3) != 0)
    {
        port_set8(&port, at, 0, pattern);
        at++;
        pattern = (pattern >> 8) | (pattern << 24);
        if (--count == 0)
        {
            break;
        }
    }
    at = port_call(&port, FILL_DWORDS, at, pattern, entry->ebx, count >> 2);
    pattern = vertrix_lift_edx;
    left = count & 3;
    if (left > 0)
    {
        port_set8(&port, at, 0, pattern);
    }
    if (left > 1)
    {
        port_set8(&port, at, 1, pattern >> 8);
    }
    if (left > 2)
    {
        port_set8(&port, at, 2, pattern);
    }
    return port_return(&port, at, pattern);
}

uint32_t vertrix_port_fill_dwords(PORT_SIGNATURE)
{
    Port port;
    uint32_t at = entry->eax;
    uint32_t value = entry->edx;
    uint32_t count = entry->ecx;
    uint32_t groups;
    uint32_t i;
    port_open(&port, calls, services, globals, entry);
    if (count == 0)
    {
        return port_return(&port, at, value);
    }
    while ((at & 0x1f) != 0)
    {
        port_set32(&port, at, 0, value);
        at += 4;
        if (--count == 0)
        {
            return port_return(&port, at, value);
        }
    }
    for (groups = count >> 2; groups > 0; groups--, at += 16)
    {
        for (i = 0; i < 4; i++)
        {
            port_set32(&port, at, 4 * i, value);
        }
    }
    for (i = 0; i < (count & 3); i++, at += 4)
    {
        port_set32(&port, at, 0, value);
    }
    return port_return(&port, at, value);
}
