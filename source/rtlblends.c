#include "rtlblends.h"

/* Palette-weighted pixel blends. */

/* Original 0x490340: the pixels at 0x5bb764 and 0x5bb768 blended into the second: each colour
 * (six bits a channel) looked up in the palette 0x54b800 (kept at 0x54d5d4 and 0x54d5d8), the
 * first one's index byte picking the weight row 0x54cdc8 (kept at 0x54d5d0); each channel the row's
 * entry at the sum of the two weight tables 0x55f1f0 and 0x55f1f4 for the channel bytes. eax the
 * second pixel's address. */
uint32_t vertrix_port_render_palette_weighted_pixel_490340(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x1c
    };
    Port port;
    uint32_t first;
    uint32_t second;
    uint32_t pixel;
    uint32_t palette;
    uint32_t one;
    uint32_t two;
    uint32_t row;
    uint32_t left;
    uint32_t right;
    uint32_t red;
    uint32_t green;
    uint32_t blue;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, entry->esp, -0xcu, entry->edi);
    port_set32(&port, entry->esp, -0x10u, entry->esi);
    port_set32(&port, entry->esp, -0x14u, entry->edx);
    port_set32(&port, entry->esp, -0x18u, entry->ecx);
    port_set32(&port, entry->esp, -0x1cu, entry->ebx);
    first = port_u32(&port, 0, 0x5bb764);
    pixel = port_u32(&port, first, 0);
    palette = port_u32(&port, 0, 0x54b800);
    one = port_u32(
        &port,
        palette +
            ((((pixel & 0xfc0000u) >> 4) | ((pixel & 0xfc00u) >> 2) | (pixel & 0xfc)) >> 2) * 4,
        0);
    port_set32(&port, 0, 0x54d5d4, one);
    row = port_u32(&port, (port_u8(&port, 0, 0x54d5d4)) * 4 + port_u32(&port, 0, 0x54cdc8), 0);
    port_set32(&port, 0, 0x54d5d0, row);
    second = port_u32(&port, 0, 0x5bb768);
    pixel = port_u32(&port, second, 0);
    two = port_u32(
        &port,
        palette +
            ((((pixel & 0xfc0000u) >> 4) | ((pixel & 0xfc00u) >> 2) | (pixel & 0xfc)) >> 2) * 4,
        0);
    port_set32(&port, 0, 0x54d5d8, two);
    one = port_u32(&port, 0, 0x54d5d4);
    left = port_u32(&port, 0, 0x55f1f0);
    right = port_u32(&port, 0, 0x55f1f4);
    row = port_u32(&port, 0, 0x54d5d0);
    red = port_u8(&port,
                  row + port_u8(&port, left + (one >> 24), 0) +
                      port_u8(&port, right + (port_u32(&port, 0, 0x54d5d8) >> 24), 0),
                  0)
          << 16;
    port_set32(&port, entry->esp, -4u, red);
    port_set32(&port, entry->esp, -8u, port_u32(&port, 0, 0x54d5d4) >> 16);
    green = port_u8(&port, left + port_u8(&port, entry->esp, -8u), 0);
    port_set32(&port, entry->esp, -8u, port_u32(&port, 0, 0x54d5d8) >> 16);
    green += port_u8(&port, right + port_u8(&port, entry->esp, -8u), 0);
    green = port_u8(&port, green + row, 0) << 8;
    port_set32(&port, entry->esp, -8u, port_u16(&port, 0, 0x54d5d4) >> 8);
    blue = port_u8(&port, left + port_u8(&port, entry->esp, -8u), 0);
    blue += port_u8(&port, right + ((port_u16(&port, 0, 0x54d5d8) >> 8) & 0xff), 0);
    blue = port_u8(&port, row + blue, 0);
    port_set32(&port, second, 0, red | green | blue);
    return port_return(&port, second, entry->edx);
}
