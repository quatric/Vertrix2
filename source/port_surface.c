#include "port_surface.h"

enum
{
    SURFACE_PIXELS = 0x00,
    SURFACE_WIDTH = 0x04,
    SURFACE_HEIGHT = 0x08,
    SURFACE_BYTES_PER_PIXEL = 0x0c,
    SURFACE_PITCH = 0x14,
    PIXEL_FROM = 0x558a5c,
    PIXEL_TO = 0x558a60,
    PIXEL_SIZE = 0x558a58,
    READ_ADDRESS = 0x5589f0,
    READ_SIZE = 0x5589ec,
    SURFACE_OFFSET = 0x478eb0,
    SURFACE_COPY_PIXEL = 0x479d70
};

uint32_t vertrix_port_surface_offset(PORT_SIGNATURE)
{
    Port port;
    uint32_t surface = entry->eax;
    uint32_t x = entry->edx;
    uint32_t y = entry->ebx;
    uint32_t row;
    uint32_t pixels;
    uint32_t size;
    port_open(&port, calls, services, globals, entry);
    row = y * port_u32(&port, surface, SURFACE_PITCH);
    pixels = port_u32(&port, surface, SURFACE_PIXELS);
    size = port_u8(&port, surface, SURFACE_BYTES_PER_PIXEL);
    return port_return(&port, size * x + pixels + row, x);
}

uint32_t vertrix_port_surface_copy_pixel(PORT_SIGNATURE)
{
    Port port;
    uint32_t target = entry->eax;
    uint32_t source = entry->edx;
    uint32_t x = entry->ebx;
    uint32_t y = entry->ecx;
    uint32_t from;
    uint32_t to;
    uint32_t size;
    port_open(&port, calls, services, globals, entry);
    if ((int32_t)x < 0 || x >= port_u32(&port, target, SURFACE_WIDTH) || (int32_t)y < 0 ||
        y >= port_u32(&port, target, SURFACE_HEIGHT))
    {
        return port_return(&port, source, source);
    }
    from = port_call(&port, SURFACE_OFFSET, source, x, y, y);
    port_set32(&port, 0, PIXEL_FROM, from);
    to = port_call(&port, SURFACE_OFFSET, target, x, y, y);
    size = port_u8(&port, target, SURFACE_BYTES_PER_PIXEL);
    port_set32(&port, 0, PIXEL_TO, to);
    port_set8(&port, 0, PIXEL_SIZE, size);
    if (size == 4)
    {
        port_set32(&port, to, 0, port_u32(&port, from, 0));
    }
    else if (size == 2)
    {
        port_set16(&port, to, 0, port_u16(&port, from, 0));
    }
    else if (size == 1)
    {
        port_set8(&port, to, 0, port_u8(&port, from, 0));
    }
    return port_return(&port, to, vertrix_lift_edx);
}

uint32_t vertrix_port_neighbour_calls(PORT_SIGNATURE)
{
    static const int32_t STEPS[4][2] = {{0, 1}, {0, -1}, {-1, 1}, {1, -1}};
    Port port;
    uint32_t eax = entry->eax;
    unsigned i;
    port_open(&port, calls, services, globals, entry);
    for (i = 0; i < 4; i++)
    {
        eax = port_call(&port, SURFACE_COPY_PIXEL, entry->eax, entry->edx,
                        entry->ebx + (uint32_t)STEPS[i][0], entry->ecx + (uint32_t)STEPS[i][1]);
    }
    return port_return(&port, eax, vertrix_lift_edx);
}

uint32_t vertrix_port_surface_read(PORT_SIGNATURE)
{
    Port port;
    uint32_t surface = entry->eax;
    uint32_t at;
    uint32_t size;
    uint32_t edx;
    uint32_t pixel = 0;
    port_open(&port, calls, services, globals, entry);
    at = port_call(&port, SURFACE_OFFSET, surface, entry->edx, entry->ebx, surface);
    size = port_u8(&port, surface, SURFACE_BYTES_PER_PIXEL);
    edx = (vertrix_lift_edx & 0xffffff00u) | size;
    port_set32(&port, 0, READ_ADDRESS, at);
    port_set8(&port, 0, READ_SIZE, size);
    if (size == 4)
    {
        pixel = port_u32(&port, at, 0);
    }
    else if (size == 1)
    {
        pixel = port_u8(&port, at, 0);
    }
    else if (size == 2)
    {
        pixel = port_u16(&port, at, 0);
    }
    return port_return(&port, pixel, edx);
}
