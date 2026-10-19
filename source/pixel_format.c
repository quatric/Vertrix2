#include "pixel_format.h"

enum
{
    MASKS = 0x04,
    DOWN = 0x19,
    UP = 0x1d,
    PACKED = 0x21,
    CHANNELS = 4,
    SURFACE_KIND = 0x0d,
    LAST_KIND = 0x558a50,
    KIND_332 = 0,
    KIND_555 = 1,
    KIND_565 = 2
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

uint32_t vertrix_pixel_repack_on(Port *port, uint32_t from, uint32_t to, uint32_t pixel)
{
    uint32_t down[CHANNELS];
    uint32_t up[CHANNELS];
    uint32_t scaled[CHANNELS];
    uint32_t packed;
    uint32_t red;
    uint32_t green;
    uint32_t blue;
    uint32_t alpha;
    unsigned i;
    for (i = 0; i < CHANNELS; i++)
    {
        down[i] = port_u8(port, from, DOWN + i);
        up[i] = port_u8(port, from, UP + i);
        scaled[i] = port_shl(port_shr(pixel & port_u32(port, from, MASKS + 4 * i), down[i]), up[i]);
    }
    packed = port_shl(scaled[0], port_u8(port, to, PACKED)) |
             port_shl(scaled[1], port_u8(port, to, PACKED + 1)) |
             port_shl(scaled[2], port_u8(port, to, PACKED + 2));
    red = port_shl(port_shr((packed & 0xff0000) >> 16, up[0]), down[0]);
    green = port_shl(port_shr((packed & 0xffff) >> 8, up[1]), down[1]);
    blue = port_shl(port_shr(packed & 0xff, up[2]), down[2]);
    alpha = port_shl(port_shr(scaled[3], up[3]), down[3]);
    vertrix_lift_edx = green;
    return alpha | red | green | blue;
}

uint32_t vertrix_port_pixel_repack(PORT_SIGNATURE)
{
    Port port;
    uint32_t pixel;
    port_open(&port, calls, services, globals, entry);
    pixel = vertrix_pixel_repack_on(&port, entry->eax, entry->edx, entry->ebx);
    return port_return(&port, pixel, vertrix_lift_edx);
}

uint32_t vertrix_port_pixel_pack(PORT_SIGNATURE)
{
    Port port;
    uint32_t colour = entry->edx;
    uint32_t kind;
    port_open(&port, calls, services, globals, entry);
    kind = port_u8(&port, entry->eax, SURFACE_KIND);
    switch (kind)
    {
        case KIND_332:
            colour =
                (((colour & 0xe00000) >> 10) | ((colour & 0xe000) >> 5) | (colour & 0xc0)) >> 6;
            break;
        case KIND_555:
            colour = (((colour & 0xf80000) >> 6) | ((colour & 0xf800) >> 3) | (colour & 0xf8)) >> 3;
            break;
        case KIND_565:
            colour = (((colour & 0xf80000) >> 5) | ((colour & 0xfc00) >> 2) | (colour & 0xf8)) >> 3;
            break;
        default:
            break;
    }
    port_set8(&port, 0, LAST_KIND, kind);
    return port_return(&port, colour, colour);
}

uint32_t vertrix_port_pixel_format_from_masks(PORT_SIGNATURE)
{
    enum
    {
        ARGUMENTS = 1
    };
    static const uint8_t kinds[][3] = {
        {8, 0, 1}, {0xf, 1, 2}, {0x10, 2, 2}, {0x18, 3, 3}, {0x20, 4, 4}};
    uint8_t stack[8 + 4 * ARGUMENTS];
    Port port;
    uint32_t format = entry->eax;
    uint32_t masks[4];
    uint32_t bit;
    uint32_t channel;
    uint32_t sum;
    unsigned i;
    port_open_arguments(&port, stack, calls, services, globals, entry, 0, ARGUMENTS);
    for (channel = 0; channel < 8; channel++)
    {
        port_set8(&port, format, 0x15 + channel, 0);
    }
    port_set32(&port, format, 4, entry->edx);
    port_set32(&port, format, 8, entry->ebx);
    port_set32(&port, format, 0xc, entry->ecx);
    masks[0] = port_u32(&port, format, 4);
    masks[1] = port_u32(&port, format, 8);
    port_set32(&port, format, 0x10, port_u32(&port, entry->esp, 4));
    masks[2] = port_u32(&port, format, 0xc);
    masks[3] = port_u32(&port, format, 0x10);
    /* Per channel: its bit count at +0x15 and the zero bits below its lowest set bit at +0x19. */
    for (bit = 0; bit < 32; bit++)
    {
        for (channel = 0; channel < 4; channel++)
        {
            if ((masks[channel] & 1) != 0)
            {
                port_set8(&port, format, 0x15 + channel,
                          port_u8(&port, format, 0x15 + channel) + 1);
            }
            else if (port_u8(&port, format, 0x15 + channel) == 0)
            {
                port_set8(&port, format, 0x19 + channel,
                          port_u8(&port, format, 0x19 + channel) + 1);
            }
        }
        for (channel = 0; channel < 4; channel++)
        {
            masks[channel] >>= 1;
        }
    }
    port_set8(&port, format, 0x1d, 8 - port_u8(&port, format, 0x15));
    port_set8(&port, format, 0x1e, 8 - port_u8(&port, format, 0x16));
    port_set8(&port, format, 0x21, 0);
    port_set8(&port, format, 0x1f, 8 - port_u8(&port, format, 0x17));
    port_set8(&port, format, 0x22, 0);
    port_set8(&port, format, 0x23, 0);
    port_set8(&port, format, 0x20, 8 - port_u8(&port, format, 0x18));
    port_set8(&port, format, 0x24, 0);
    /* Each of the first three channels moves up 8 for each other one lying below it. */
    for (channel = 0; channel < 3; channel++)
    {
        uint32_t other;
        for (other = 0; other < 3; other++)
        {
            if (other != channel &&
                port_u8(&port, format, 0x19 + channel) > port_u8(&port, format, 0x19 + other))
            {
                port_set8(&port, format, 0x21 + channel,
                          port_u8(&port, format, 0x21 + channel) + 8);
            }
        }
    }
    sum = port_u8(&port, format, 0x15);
    sum = (sum + port_u8(&port, format, 0x16)) & 0xff;
    sum = (sum + port_u8(&port, format, 0x17)) & 0xff;
    sum = (sum + port_u8(&port, format, 0x18)) & 0xff;
    port_set8(&port, format, 0x24, 0x18);
    for (i = 0; i < sizeof kinds / sizeof kinds[0]; i++)
    {
        if (sum == kinds[i][0])
        {
            port_set8(&port, format, 0x14, kinds[i][1]);
            port_set8(&port, format, 0, kinds[i][2]);
            return port_return(&port, 1, port_u8(&port, format, 0x16) << 8 | sum);
        }
    }
    return port_return(&port, 0, port_u8(&port, format, 0x16) << 8 | sum);
}
