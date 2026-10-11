#include "port_pixel_format.h"

enum
{
    MASKS = 0x04,
    DOWN = 0x19,
    UP = 0x1d,
    PACKED = 0x21,
    CHANNELS = 4
};

uint32_t vertrix_port_pixel_convert(PORT_SIGNATURE)
{
    Port port;
    uint32_t from = entry->eax;
    uint32_t to = entry->edx;
    uint32_t pixel = entry->ebx;
    uint32_t parts[CHANNELS];
    unsigned i;
    port_open(&port, calls, services, globals, entry);
    for (i = 0; i < CHANNELS; i++)
    {
        uint32_t value = pixel & port_u32(&port, from, MASKS + 4 * i);
        value =
            port_shl(port_shr(value, port_u8(&port, from, DOWN + i)), port_u8(&port, from, UP + i));
        parts[i] =
            port_shl(port_shr(value, port_u8(&port, to, UP + i)), port_u8(&port, to, DOWN + i));
    }
    return port_return(&port, parts[3] | parts[0] | parts[1] | parts[2], to);
}

uint32_t vertrix_port_pixel_repack(PORT_SIGNATURE)
{
    Port port;
    uint32_t from = entry->eax;
    uint32_t to = entry->edx;
    uint32_t pixel = entry->ebx;
    uint32_t down[CHANNELS];
    uint32_t up[CHANNELS];
    uint32_t scaled[CHANNELS];
    uint32_t packed;
    uint32_t red;
    uint32_t green;
    uint32_t blue;
    uint32_t alpha;
    unsigned i;
    port_open(&port, calls, services, globals, entry);
    for (i = 0; i < CHANNELS; i++)
    {
        down[i] = port_u8(&port, from, DOWN + i);
        up[i] = port_u8(&port, from, UP + i);
        scaled[i] =
            port_shl(port_shr(pixel & port_u32(&port, from, MASKS + 4 * i), down[i]), up[i]);
    }
    packed = port_shl(scaled[0], port_u8(&port, to, PACKED)) |
             port_shl(scaled[1], port_u8(&port, to, PACKED + 1)) |
             port_shl(scaled[2], port_u8(&port, to, PACKED + 2));
    red = port_shl(port_shr((packed & 0xff0000) >> 16, up[0]), down[0]);
    green = port_shl(port_shr((packed & 0xffff) >> 8, up[1]), down[1]);
    blue = port_shl(port_shr(packed & 0xff, up[2]), down[2]);
    alpha = port_shl(port_shr(scaled[3], up[3]), down[3]);
    return port_return(&port, alpha | red | green | blue, green);
}
