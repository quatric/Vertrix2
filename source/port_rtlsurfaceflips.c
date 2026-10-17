#include "port_rtlsurfaceflips.h"

/* Flips a loaded bitmap upside down in place, swapping its rows pairwise from the outside in. */

enum
{
    BITMAP_DATA = 0,
    BITMAP_WIDTH = 4,
    BITMAP_HEIGHT = 8,
    BITMAP_PIXEL_BYTES = 0xc
};

/* Swap `count` units of `unit` bytes (1, 2 or 4) between two rows. The column counter is a word
 * compared with the signed count, as in the original. */
static void swap_rows(Port *port, uint32_t top, uint32_t bottom, int32_t count, unsigned unit)
{
    for (uint16_t col = 0; (int32_t)col < count && !port->env.failed; col++)
    {
        const uint32_t at = col * unit;
        if (unit == 1)
        {
            const uint32_t upper = port_u8(port, top, at);
            port_set8(port, top, at, port_u8(port, bottom, at));
            port_set8(port, bottom, at, upper);
        }
        else if (unit == 2)
        {
            const uint32_t upper = port_u16(port, top, at);
            port_set16(port, top, at, port_u16(port, bottom, at));
            port_set16(port, bottom, at, upper);
        }
        else
        {
            const uint32_t upper = port_u32(port, top, at);
            port_set32(port, top, at, port_u32(port, bottom, at));
            port_set32(port, bottom, at, upper);
        }
    }
}

/* Original 0x479b50 (eax = bitmap): by its pixel size (+0xc, 1 to 4 bytes) swaps rows 0 and
 * height - 1, 1 and height - 2, and so on, for height / 2 pairs; other sizes are left alone. A
 * 24-bit row is width * 3 bytes cut to a signed word. */
uint32_t vertrix_port_surface_flip_vertical_479b50(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    const uint32_t bitmap = entry->eax;
    const int32_t width = (int16_t)port_u16(&port, bitmap, BITMAP_WIDTH);
    const int32_t height = (int16_t)port_u16(&port, bitmap, BITMAP_HEIGHT);
    const uint32_t pixel_bytes = port_u8(&port, bitmap, BITMAP_PIXEL_BYTES);

    int32_t count;
    unsigned unit;
    switch (pixel_bytes)
    {
        case 1:
            count = width;
            unit = 1;
            break;
        case 2:
            count = width;
            unit = 2;
            break;
        case 3:
            count = (int16_t)(width * 3);
            unit = 1;
            break;
        case 4:
            count = width;
            unit = 4;
            break;
        default:
            return port_return(&port, 0, 0);
    }
    const uint32_t row_bytes = (uint32_t)count * unit;
    uint32_t top = port_u32(&port, bitmap, BITMAP_DATA);
    uint32_t bottom = top + (uint32_t)(height - 1) * row_bytes;
    for (uint16_t pairs = (uint16_t)(height / 2); pairs != 0 && !port.env.failed; pairs--)
    {
        swap_rows(&port, top, bottom, count, unit);
        top += row_bytes;
        bottom -= row_bytes;
    }
    return port_return(&port, 0, 0);
}
