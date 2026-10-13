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
    SURFACE_COPY_PIXEL = 0x479d70,
    PIXEL_PACK = 0x479a40,
    FILL_SIZE = 0x558b70,
    FILL_START = 0x558b80,
    FILL_SKIP = 0x558b68,
    FILL_WORD_AT = 0x558b78,
    FILL_DWORD_AT = 0x558b7c,
    FILL_BYTE_AT = 0x558b74,
    FILL_LEFT = 0x558b64
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

uint32_t vertrix_port_surface_fill(PORT_SIGNATURE)
{
    Port port;
    uint32_t surface = entry->eax;
    uint32_t width = entry->ecx;
    uint32_t rows = entry->arguments[0];
    uint32_t colour = entry->arguments[1];
    uint32_t pixel;
    uint32_t start;
    uint32_t size;
    uint32_t at;
    uint32_t left;
    uint32_t eax;
    uint32_t edx;
    port_open(&port, calls, services, globals, entry);
    /* The byte cursor and the count left (esi and edi of the original), written back at the end. */
    left = port_u32(&port, 0, FILL_LEFT);
    at = port_u32(&port, 0, FILL_BYTE_AT);
    port_set8(&port, 0, FILL_SIZE, port_u8(&port, surface, SURFACE_BYTES_PER_PIXEL));
    pixel = port_call(&port, PIXEL_PACK, surface, colour, entry->ebx, colour);
    start = port_call(&port, SURFACE_OFFSET, surface, entry->edx, entry->ebx, pixel);
    edx = vertrix_lift_edx;
    port_set32(&port, 0, FILL_START, start);
    size = port_u8(&port, 0, FILL_SIZE);
    edx = (edx & 0xffffff00u) | size;
    eax = start;
    if (size == 1)
    {
        at = start;
        edx = width;
        eax = port_u32(&port, surface, SURFACE_PITCH) - width;
        port_set32(&port, 0, FILL_SKIP, eax);
        left = port_u32(&port, 0, FILL_LEFT);
        for (; rows != 0; rows--)
        {
            for (left = width; left != 0; left--)
            {
                at++;
                port_set8(&port, at, -1u, pixel);
            }
            at += port_u32(&port, 0, FILL_SKIP);
            eax = rows - 1;
        }
    }
    else
    {
        at = port_u32(&port, 0, FILL_BYTE_AT);
        left = port_u32(&port, 0, FILL_LEFT);
        if (size == 2 || size == 4)
        {
            uint32_t cursor = size == 2 ? FILL_WORD_AT : FILL_DWORD_AT;
            port_set32(&port, 0, cursor, start);
            edx = width * size;
            eax = port_u32(&port, surface, SURFACE_PITCH) - edx;
            port_set32(&port, 0, FILL_SKIP, eax);
            if (size == 4)
            {
                edx = rows;
            }
            for (; rows != 0; rows--)
            {
                for (left = width; left != 0; left--)
                {
                    uint32_t next = port_u32(&port, 0, cursor) + size;
                    lift_store(&port.env, next, -size, size, pixel);
                    port_set32(&port, 0, cursor, next);
                }
                edx = port_u32(&port, 0, FILL_SKIP);
                port_set32(&port, 0, cursor, port_u32(&port, 0, cursor) + edx);
                eax = rows - 1;
            }
        }
    }
    port_set32(&port, 0, FILL_BYTE_AT, at);
    port_set32(&port, 0, FILL_LEFT, left);
    return port_return(&port, eax, edx);
}

uint32_t vertrix_port_draw_outline(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x64,
        ARGUMENTS = 7,
        GUARD_HANDLER = 0x4ec1ec,
        OUTLINE_GUARD = 0x51684c,
        FORMAT = 0x60, /* below ebp: the pixel format */
        CLIPPED = 0x558b82,
        FORMAT_INIT = 0x481b20,
        FORMAT_FROM_MASKS = 0x481bc0,
        FORMAT_RELEASE = 0x481b30,
        FORMAT_COLOR = 0x481e10,
        DRAW_LINE = 0x47c3b0
    };
    Port port;
    uint8_t stack[BELOW + 8 + 4 * ARGUMENTS];
    uint32_t ebp = entry->esp - 4;
    uint32_t surface = entry->eax;
    uint32_t left = entry->ebx;
    uint32_t top = entry->ecx;
    uint32_t right;
    uint32_t bottom;
    uint32_t clip_left;
    uint32_t clip_top;
    uint32_t clip_right;
    uint32_t clip_bottom;
    uint32_t color;
    uint32_t chain;
    uint32_t x;
    uint32_t y;
    uint32_t ebx;
    uint32_t ecx;
    uint32_t edx;
    uint32_t pair[2];
    port_open_arguments(&port, stack, calls, services, globals, entry, BELOW, ARGUMENTS);
    right = port_u32(&port, ebp, 8);
    bottom = port_u32(&port, ebp, 0xc);
    clip_left = port_u32(&port, ebp, 0x10);
    clip_top = port_u32(&port, ebp, 0x14);
    clip_right = port_u32(&port, ebp, 0x18);
    clip_bottom = port_u32(&port, ebp, 0x1c);
    color = port_u32(&port, ebp, 0x20);
    chain = port.env.chain;
    /* The guard record the original links into fs:[0] for the pixel format. */
    port_set32(&port, ebp, -0x34u, chain);
    port_set32(&port, ebp, -0x30u, GUARD_HANDLER);
    port_set32(&port, ebp, -0x2cu, OUTLINE_GUARD);
    port_set32(&port, ebp, -0x28u, 0);
    edx = clip_left;
    if (color == 0xff000000u || (int32_t)left > (int32_t)clip_right ||
        (int32_t)clip_left > (int32_t)right || (int32_t)top > (int32_t)clip_bottom ||
        (int32_t)clip_top > (int32_t)bottom)
    {
        return port_return(&port, chain, edx);
    }
    y = (int32_t)top < (int32_t)clip_top ? clip_top : top;
    x = (int32_t)left < (int32_t)clip_left ? clip_left : left;
    edx = clip_bottom;
    if ((int32_t)bottom > (int32_t)clip_bottom)
    {
        port_set32(&port, ebp, 0xc, clip_bottom);
    }
    if ((int32_t)clip_right < (int32_t)right)
    {
        port_set32(&port, ebp, 8, clip_right);
    }
    /* The clipped size, as two words at 0x558b84. */
    port_set16(&port, 0, CLIPPED + 2, port_u32(&port, ebp, 8) - x + 1);
    port_set16(&port, 0, CLIPPED + 4, port_u32(&port, ebp, 0xc) - y + 1);
    if ((int32_t)port_u32(&port, 0, CLIPPED) >> 16 <= 0 ||
        (int32_t)port_u32(&port, 0, CLIPPED + 2) >> 16 <= 0)
    {
        return port_return(&port, chain, edx);
    }
    ebx = 0xff00;
    ecx = 0xff;
    port_call(&port, FORMAT_INIT, ebp - FORMAT, 0xff0000, ebx, ecx);
    edx = vertrix_lift_edx;
    port_set32(&port, ebp, -0x28u, 1);
    pair[0] = 0xff000000u;
    if (port_call_stack(&port, FORMAT_FROM_MASKS, ebp - FORMAT, edx, ebx, ecx, pair, 1) == 0)
    {
        port_call(&port, FORMAT_RELEASE, ebp - FORMAT, 0, ebx, ecx);
        return port_return(&port, chain, vertrix_lift_edx);
    }
    ebx = color;
    color = port_call(&port, FORMAT_COLOR, ebp - FORMAT, entry->edx, ebx, ecx);
    port_set32(&port, ebp, 0x20, color);
    /* The edges left whole by the clip: top, bottom, left and right. */
    if (y == top)
    {
        pair[0] = 1;
        pair[1] = color;
        ebx = top;
        ecx = (uint32_t)((int32_t)port_u32(&port, 0, CLIPPED) >> 16);
        port_call_stack(&port, DRAW_LINE, surface, x, ebx, ecx, pair, 2);
    }
    if (port_u32(&port, ebp, 0xc) == bottom)
    {
        pair[0] = 1;
        pair[1] = color;
        ecx = (uint32_t)((int32_t)port_u32(&port, 0, CLIPPED) >> 16);
        ebx = port_u32(&port, ebp, 0xc);
        port_call_stack(&port, DRAW_LINE, surface, x, ebx, ecx, pair, 2);
    }
    if (x == left)
    {
        pair[0] = (uint32_t)((int32_t)port_u32(&port, 0, CLIPPED + 2) >> 16);
        pair[1] = color;
        ecx = 1;
        ebx = y;
        port_call_stack(&port, DRAW_LINE, surface, x, ebx, ecx, pair, 2);
    }
    if (port_u32(&port, ebp, 8) == right)
    {
        pair[0] = (uint32_t)((int32_t)port_u32(&port, 0, CLIPPED + 2) >> 16);
        pair[1] = color;
        ecx = 1;
        ebx = y;
        port_call_stack(&port, DRAW_LINE, surface, port_u32(&port, ebp, 8), ebx, ecx, pair, 2);
    }
    port_set32(&port, ebp, -0x28u, 0);
    port_call(&port, FORMAT_RELEASE, ebp - FORMAT, 0, ebx, ecx);
    port_set32(&port, ebp, -0x28u, 0);
    return port_return(&port, chain, vertrix_lift_edx);
}
