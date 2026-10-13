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

uint32_t vertrix_port_image_color_order(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x58,
        GUARD_HANDLER = 0x4ec1ec,
        ORDER_GUARD = 0x516c50,
        FORMAT = 0x54, /* below ebp: the pixel format */
        FORMAT_INIT = 0x481b20,
        FORMAT_FROM_MASKS = 0x481bc0,
        FORMAT_RELEASE = 0x481b30,
        FORMAT_COLOR = 0x481e10
    };
    Port port;
    uint8_t stack[BELOW + 8];
    uint32_t ebp = entry->esp - 4;
    uint32_t image = entry->eax;
    uint32_t source = entry->edx;
    uint32_t chain;
    uint32_t count;
    uint32_t pixel;
    uint32_t ebx = 0xff00;
    uint32_t argument = 0xff000000u;
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    chain = port.env.chain;
    port_set32(&port, ebp, -0x14u, image);
    /* The guard record the original links into fs:[0] for the pixel format. */
    port_set32(&port, ebp, -0x28u, chain);
    port_set32(&port, ebp, -0x24u, GUARD_HANDLER);
    port_set32(&port, ebp, -0x20u, ORDER_GUARD);
    port_set32(&port, ebp, -0x1cu, 0);
    port_call(&port, FORMAT_INIT, ebp - FORMAT, GUARD_HANDLER, 0, ORDER_GUARD);
    port_set32(&port, ebp, -0x1cu, 1);
    if (port_call_stack(&port, FORMAT_FROM_MASKS, ebp - FORMAT, 0xff0000, ebx, 0xff, &argument,
                        1) == 0)
    {
        port_call(&port, FORMAT_RELEASE, ebp - FORMAT, 0, ebx, 0xff);
        return port_return(&port, chain, vertrix_lift_edx);
    }
    count = port_u32(&port, image, 4) * port_u32(&port, image, 8);
    if (port_u8(&port, image, 0x27) != 4)
    {
        port_call(&port, FORMAT_RELEASE, ebp - FORMAT, 0, ebx, port_u32(&port, image, 8));
        return port_return(&port, chain, vertrix_lift_edx);
    }
    /* Each 32-bit pixel converted from the source format into the screen's order. */
    pixel = port_u32(&port, image, 0);
    for (; count != 0; count--)
    {
        ebx = port_u32(&port, pixel, 0);
        pixel += 4;
        port_set32(&port, pixel, -4u,
                   port_call(&port, FORMAT_COLOR, ebp - FORMAT, source, ebx, pixel));
    }
    port_set32(&port, ebp, -0x1cu, 0);
    port_call(&port, FORMAT_RELEASE, ebp - FORMAT, 0, ebx, pixel);
    port_set32(&port, ebp, -0x1cu, 0);
    return port_return(&port, chain, vertrix_lift_edx);
}

/* A DirectDraw surface method for 0x485550: eax the surface, edx its table, ebx the display. */
static uint32_t display_method(Port *port, uint32_t surface, uint32_t offset, uint32_t display,
                               uint32_t ecx, uint32_t *arguments, unsigned count)
{
    uint32_t table = port_u32(port, surface, 0);
    arguments[0] = surface;
    return port_call_stack(port, port_u32(port, table, offset), surface, table, display, ecx,
                           arguments, count);
}

uint32_t vertrix_port_display_present(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x28,
        STILL_DRAWING = 0x8876021cu,
        SURFACE_LOST = 0x887601c2u,
        STATUS = 0x5b99c4,
        DESCRIPTION = 0x5b99c8,
        RESTORE = 0x487080,
        BLT = 0x14,
        BLT_FAST = 0x1c,
        GET_BLT_STATUS = 0x34,
        GET_FLIP_STATUS = 0x48,
        LOCK = 0x64,
        IS_LOST = 0x6c,
        UNLOCK = 0x80
    };
    Port port;
    uint8_t stack[BELOW + 8];
    uint32_t ebp = entry->esp - 4;
    uint32_t display = entry->eax;
    uint32_t ecx = entry->ecx;
    uint32_t edx;
    uint32_t result;
    uint32_t front;
    uint32_t back;
    uint32_t rectangle = ebp - 0x24;
    uint32_t arguments[6];
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    do
    {
        arguments[1] = 2;
        result = display_method(&port, port_u32(&port, display, 0x68), GET_FLIP_STATUS, display,
                                ecx, arguments, 2);
    } while (result == STILL_DRAWING);
    /* Lock both surfaces (as a test that neither is lost), restoring a lost one. */
    for (;;)
    {
        arguments[1] = 0;
        arguments[2] = DESCRIPTION;
        arguments[3] = 0x21;
        arguments[4] = 0;
        result =
            display_method(&port, port_u32(&port, display, 0x68), LOCK, display, ecx, arguments, 5);
        port_set32(&port, 0, STATUS, result);
        if (result != SURFACE_LOST)
        {
            break;
        }
        if (display_method(&port, port_u32(&port, display, 0x64), IS_LOST, display, ecx, arguments,
                           1) != 0)
        {
            return port_return(&port, 0, entry->edx);
        }
        edx = vertrix_lift_edx;
        result = port_call(&port, RESTORE, display, edx, display, ecx);
        if (result == 0)
        {
            return port_return(&port, result, entry->edx);
        }
    }
    for (;;)
    {
        arguments[1] = 0;
        arguments[2] = DESCRIPTION;
        arguments[3] = 0x11;
        arguments[4] = 0;
        result =
            display_method(&port, port_u32(&port, display, 0x6c), LOCK, display, ecx, arguments, 5);
        port_set32(&port, 0, STATUS, result);
        if (result != SURFACE_LOST)
        {
            break;
        }
        if (display_method(&port, port_u32(&port, display, 0x6c), IS_LOST, display, ecx, arguments,
                           1) != 0 ||
            port_call(&port, RESTORE, display, vertrix_lift_edx, display, ecx) == 0)
        {
            arguments[1] = 0;
            display_method(&port, port_u32(&port, display, 0x68), UNLOCK, display, ecx, arguments,
                           2);
            return port_return(&port, 0, entry->edx);
        }
    }
    /* The back buffer copied to the front over the whole screen: BltFast, else Blt. */
    port_set32(&port, rectangle, 0, 0);
    port_set32(&port, rectangle, 4, 0);
    port_set32(&port, rectangle, 8, port_u16(&port, display, 0x3e));
    port_set32(&port, rectangle, 0xc, port_u16(&port, display, 0x40));
    back = port_u32(&port, display, 0x6c);
    front = port_u32(&port, display, 0x68);
    ecx = rectangle;
    arguments[1] = 0;
    arguments[2] = 0;
    arguments[3] = back;
    arguments[4] = rectangle;
    arguments[5] = 0x10;
    result = display_method(&port, front, BLT_FAST, display, ecx, arguments, 6);
    port_set32(&port, 0, STATUS, result);
    if (result != 0)
    {
        uint32_t table;
        back = port_u32(&port, display, 0x6c);
        front = port_u32(&port, display, 0x68);
        table = port_u32(&port, front, 0);
        ecx = table;
        arguments[0] = front;
        arguments[1] = rectangle;
        arguments[2] = back;
        arguments[3] = rectangle;
        arguments[4] = 0x1000000;
        arguments[5] = 0;
        port_call_stack(&port, port_u32(&port, table, BLT), front, rectangle, display, ecx,
                        arguments, 6);
    }
    do
    {
        arguments[1] = 2;
        result = display_method(&port, port_u32(&port, display, 0x68), GET_BLT_STATUS, display, ecx,
                                arguments, 2);
    } while (result == STILL_DRAWING);
    arguments[1] = 0;
    display_method(&port, port_u32(&port, display, 0x6c), UNLOCK, display, ecx, arguments, 2);
    arguments[1] = 0;
    display_method(&port, port_u32(&port, display, 0x68), UNLOCK, display, ecx, arguments, 2);
    return port_return(&port, 1, entry->edx);
}

uint32_t vertrix_port_image_new(PORT_SIGNATURE)
{
    enum
    {
        ALLOCATE = 0x4ec160
    };
    Port port;
    uint8_t stack[0x10 + 8 + 4 * 8];
    uint32_t ebp = entry->esp - 4;
    uint32_t width = entry->eax;
    uint32_t height = entry->edx;
    uint32_t image;
    uint32_t pixels;
    port_open_arguments(&port, stack, calls, services, globals, entry, 0x10, 8);
    image = port_call(&port, ALLOCATE, 1, 0x28, entry->ecx, entry->ecx);
    pixels = port_call(&port, ALLOCATE, width * height * port_u8(&port, ebp, 0x24), 1, entry->ecx,
                       image);
    port_set32(&port, image, 0, pixels);
    port_set32(&port, image, 4, width);
    port_set32(&port, image, 8, height);
    port_set32(&port, image, 0x10, entry->ecx);
    port_set32(&port, image, 0xc, entry->ebx);
    port_set32(&port, image, 0x14, port_u32(&port, ebp, 8));
    port_set32(&port, image, 0x18, port_u32(&port, ebp, 0xc));
    port_set32(&port, image, 0x1c, port_u32(&port, ebp, 0x10));
    port_set32(&port, image, 0x20, port_u32(&port, ebp, 0x14));
    port_set8(&port, image, 0x24, port_u8(&port, ebp, 0x18));
    port_set8(&port, image, 0x26, port_u8(&port, ebp, 0x20));
    port_set8(&port, image, 0x25, port_u8(&port, ebp, 0x1c));
    port_set8(&port, image, 0x27, port_u8(&port, ebp, 0x24));
    return port_return(&port, image, vertrix_lift_edx);
}

uint32_t vertrix_port_event_frame_draw_direct(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x34,
        VIEW = 0x2c /* below ebp: a view of the image */
    };
    Port port;
    uint8_t stack[BELOW + 8];
    uint32_t ebp = entry->esp - 4;
    uint32_t image = entry->eax;
    uint32_t view = ebp - VIEW;
    uint32_t width;
    uint32_t height;
    uint32_t depth;
    uint32_t ebx;
    uint32_t arguments[4];
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    width = port_u32(&port, image, 4);
    height = port_u32(&port, image, 8);
    depth = port_u8(&port, image, 0x27);
    port_set32(&port, ebp, -0x10u, entry->ebx);
    port_set32(&port, ebp, -0xcu, entry->ecx);
    port_set32(&port, view, 0, port_u32(&port, image, 0));
    port_set32(&port, view, 4, width);
    port_set32(&port, view, 8, height);
    port_set8(&port, view, 0xc, depth);
    ebx = (entry->ebx & 0xffffff00u) | depth;
    port_call(&port, 0x478cd0, view, (depth << 3) & 0xff, ebx, width);
    port_set32(&port, view, 0x14, width * depth);
    port_call(&port, 0x478da0, view, width * depth, ebx, width);
    /* Blit the view at (ebx, ecx) on entry, whole. */
    arguments[0] = entry->ebx;
    arguments[1] = entry->ecx;
    arguments[2] = width;
    arguments[3] = height;
    return port_return(&port,
                       port_call_stack(&port, 0x47ce10, view, entry->edx, 0, 0, arguments, 4),
                       vertrix_lift_edx);
}

uint32_t vertrix_port_image_new_drawn(PORT_SIGNATURE)
{
    enum
    {
        ALLOCATE = 0x4ec160,
        BELOW = 0x30,
        VIEW = 0x2c /* below ebp */
    };
    Port port;
    uint8_t stack[BELOW + 8 + 4 * 11];
    uint32_t ebp = entry->esp - 4;
    uint32_t width = entry->ecx;
    uint32_t height;
    uint32_t depth;
    uint32_t image;
    uint32_t pixels;
    uint32_t view = ebp - VIEW;
    uint32_t offset;
    uint32_t arguments[4];
    port_open_arguments(&port, stack, calls, services, globals, entry, BELOW, 11);
    port_set32(&port, ebp, -0x10u, entry->edx);
    port_set32(&port, ebp, -0xcu, entry->ebx);
    height = port_u32(&port, ebp, 8);
    depth = port_u8(&port, ebp, 0x30);
    image = port_call(&port, ALLOCATE, 1, 0x28, entry->ebx, width);
    pixels = port_call(&port, ALLOCATE, height * width * depth, 1, depth, width);
    port_set32(&port, image, 0, pixels);
    port_set32(&port, image, 4, width);
    port_set8(&port, image, 0x27, depth);
    for (offset = 8; offset <= 0x20; offset += 4)
    {
        port_set32(&port, image, offset, port_u32(&port, ebp, offset));
    }
    port_set8(&port, image, 0x24, port_u8(&port, ebp, 0x24));
    port_set8(&port, image, 0x26, port_u8(&port, ebp, 0x2c));
    port_set8(&port, image, 0x25, port_u8(&port, ebp, 0x28));
    /* The pixels drawn from the source (eax) through a view of the new image. */
    port_set32(&port, view, 0, pixels);
    port_set32(&port, view, 8, height);
    port_set32(&port, view, 4, width);
    port_set8(&port, view, 0xc, depth);
    port_call(&port, 0x478cd0, view, (depth << 3) & 0xff, depth, width);
    port_set32(&port, view, 0x14, width * depth);
    port_call(&port, 0x478da0, view, height, depth, width);
    arguments[0] = entry->edx;
    arguments[1] = entry->ebx;
    arguments[2] = width;
    arguments[3] = vertrix_lift_edx;
    port_call_stack(&port, 0x47ce10, view, entry->eax, 0, 0, arguments, 4);
    return port_return(&port, image, vertrix_lift_edx);
}

uint32_t vertrix_port_image_read(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0xa0,
        HEADER = 0x98 /* below ebp: 0x80 bytes read from the stream */
    };
    Port port;
    uint8_t stack[BELOW + 8];
    uint32_t ebp = entry->esp - 4;
    uint32_t stream = entry->eax;
    uint32_t position;
    uint32_t surface;
    uint32_t pixels;
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, -0x18u, entry->edx);
    position = port_call(&port, 0x48aad0, stream, entry->edx, entry->ebx, entry->ecx);
    port_call(&port, 0x48a930, stream, ebp - HEADER, 1, 0x80);
    /* The header's last column and row (words at +8 and +0xa): a surface one larger. */
    surface =
        port_call(&port, 0x478d10, (uint32_t)((int32_t)port_u32(&port, ebp, -0x92u) >> 16) + 1,
                  (uint32_t)((int32_t)port_u32(&port, ebp, -0x90u) >> 16) + 1, 1, 0x80);
    pixels = port_u32(&port, surface, 0);
    port_set32(&port, ebp, -0x14u, pixels);
    port_call(&port, 0x48aaf0, stream, position, entry->edx, surface);
    port_call(&port, 0x480d60, pixels, stream, entry->edx, surface);
    return port_return(&port, surface, vertrix_lift_edx);
}

uint32_t vertrix_port_image_read_tga(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x54,
        HEADER = 0x50,
        FIELDS = 0x48,
        FIELD_BYTES = 0x28
    };
    Port port;
    uint8_t stack[BELOW + 8];
    uint32_t ebp = entry->esp - 4;
    uint32_t stream = entry->eax;
    uint32_t image;
    uint32_t size;
    uint32_t depth;
    uint32_t pixels;
    uint32_t offset;
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, -0x20u, stream);
    image = port_call(&port, 0x4ec160, 1, FIELD_BYTES, 1, 0x30);
    port_set32(&port, ebp, -0x1cu, image);
    port_set32(&port, ebp, -0x18u, image);
    port_call(&port, 0x48a930, stream, ebp - HEADER, 1, 0x30);
    /* The image record is the 40 bytes after the header's first 8. */
    for (offset = 0; offset < FIELD_BYTES; offset += 4)
    {
        port_set32(&port, image, offset, port_u32(&port, ebp, offset - FIELDS));
    }
    size = port_u32(&port, image, 4) * port_u32(&port, image, 8);
    depth = port_u8(&port, image, 0x27);
    if (depth == 1)
    {
        /* 8-bit pixels: read raw (header byte 0) or unpacked by 0x481480 (1). */
        uint32_t packing = port_u8(&port, ebp, -HEADER);
        pixels = port_call(&port, 0x4ec160, size, 1, 1, size);
        if (packing == 0)
        {
            port_call(&port, 0x48a930, stream, pixels, 1, size);
        }
        else if (packing == 1)
        {
            port_call(&port, 0x481480, stream, pixels, port_u32(&port, ebp, 4 - HEADER), size);
        }
        port_set32(&port, image, 0, pixels);
    }
    else if (depth == 4)
    {
        uint32_t edx;
        size *= depth;
        pixels = port_call(&port, 0x4ec160, size, 1, 1, size);
        if (port_u8(&port, ebp, -HEADER) == 0)
        {
            port_call(&port, 0x48a930, stream, pixels, 1, size);
        }
        port_set32(&port, image, 0, pixels);
        port_call(&port, 0x483750, image, 0x5b9c60, 1, size);
        edx = vertrix_lift_edx;
        port_call(&port, 0x483ed0, image, edx, 1, size);
    }
    return port_return(&port, image, entry->edx);
}

/* The source record of an image for the blends: pixels, width, height and depth (0x478cd0), its
 * row bytes (+0x10) and its stack position (0x478da0). */
static void frame_source(Port *port, uint32_t ebp, uint32_t image, uint32_t ecx, uint32_t position,
                         uint32_t *ebx)
{
    uint32_t record = ebp - 0x2c;
    uint32_t width = port_u32(port, image, 4);
    uint32_t height = port_u32(port, image, 8);
    uint32_t depth = port_u8(port, image, 0x27);
    port_set32(port, ebp, -0x10u, height);
    port_set32(port, record, 0, port_u32(port, image, 0));
    port_set32(port, record, 8, height);
    port_set32(port, record, 4, width);
    port_set8(port, record, 0xc, depth);
    *ebx = (height & 0xffffff00u) | depth;
    port_call(port, 0x478cd0, record, (depth << 3) & 0xff, *ebx, ecx);
    port_set32(port, record, 0x14, width * depth);
    port_call(port, 0x478da0, record, position, *ebx, ecx);
}

uint32_t vertrix_port_event_frame_draw_blend(PORT_SIGNATURE)
{
    Port port;
    uint8_t stack[0x30 + 8 + 4];
    uint32_t ebp = entry->esp - 4;
    uint32_t ebx;
    uint32_t arguments[5];
    uint32_t eax;
    port_open_arguments(&port, stack, calls, services, globals, entry, 0x30, 1);
    port_set32(&port, ebp, -0xcu, entry->ecx);
    frame_source(&port, ebp, entry->eax, port_u32(&port, entry->eax, 4), port_u32(&port, ebp, 8),
                 &ebx);
    arguments[0] = entry->ebx;
    arguments[1] = port_u32(&port, ebp, -0xcu);
    arguments[2] = port_u32(&port, entry->eax, 4);
    arguments[3] = port_u32(&port, ebp, -0x10u);
    arguments[4] = vertrix_lift_edx;
    eax = port_call_stack(&port, 0x47c930, ebp - 0x2c, entry->edx, 0, 0, arguments, 5);
    return port_return(&port, eax, vertrix_lift_edx);
}

uint32_t vertrix_port_event_frame_draw_scaled(PORT_SIGNATURE)
{
    Port port;
    uint8_t stack[0x30 + 8 + 5 * 4];
    uint32_t ebp = entry->esp - 4;
    uint32_t ebx;
    uint32_t arguments[5];
    uint32_t eax;
    port_open_arguments(&port, stack, calls, services, globals, entry, 0x30, 5);
    port_set32(&port, ebp, -0xcu, entry->ebx);
    frame_source(&port, ebp, entry->eax, entry->ecx, port_u32(&port, ebp, 0x18), &ebx);
    arguments[0] = port_u32(&port, ebp, -0xcu);
    arguments[1] = entry->ecx;
    arguments[2] = port_u32(&port, ebp, 0x10);
    arguments[3] = port_u32(&port, ebp, 0x14);
    arguments[4] = vertrix_lift_edx;
    eax = port_call_stack(&port, 0x47cb40, ebp - 0x2c, entry->edx, port_u32(&port, ebp, 8),
                          port_u32(&port, ebp, 0xc), arguments, 5);
    return port_return(&port, eax, vertrix_lift_edx);
}

uint32_t vertrix_port_image_mirror_rows(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x1c
    };
    Port port;
    uint8_t stack[BELOW + 8];
    uint32_t local = entry->esp - BELOW;
    uint32_t image = entry->eax;
    uint32_t eax = entry->eax;
    uint32_t depth;
    uint32_t rows;
    uint32_t row;
    int32_t width;
    int32_t half;
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    width = (int16_t)port_u16(&port, image, 4);
    half = (width - (width >> 31)) >> 1;
    port_set16(&port, local, 0, (uint32_t)width);
    rows = (entry->edx & 0xffff0000u) | port_u16(&port, image, 8);
    port_set32(&port, local, 4, rows);
    depth = port_u8(&port, image, 0x27);
    if (depth != 1 && depth != 4)
    {
        return port_return(&port, eax, entry->edx);
    }
    /* Each row of 8-bit or 32-bit pixels is mirrored in place, left to right. */
    row = port_u32(&port, image, 0);
    while ((rows & 0xffff) != 0)
    {
        uint32_t index = 0;
        while ((int32_t)(eax = index & 0xffff) < half)
        {
            uint32_t other = (uint32_t)width - 1 - eax;
            if (depth == 1)
            {
                uint32_t left = port_u8(&port, row + eax, 0);
                uint32_t right = port_u8(&port, row, other);
                port_set8(&port, row + eax, 0, right);
                port_set8(&port, row, other, left);
            }
            else
            {
                uint32_t right = port_u32(&port, row, other * 4);
                uint32_t left = port_u32(&port, eax * 4, row);
                port_set32(&port, eax * 4, row, right);
                port_set32(&port, row, other * 4, left);
            }
            index++;
        }
        row += depth == 1 ? (uint32_t)width : (uint32_t)width << 2;
        rows = (rows & 0xffff0000u) | ((rows - 1) & 0xffff);
        port_set32(&port, local, 4, rows);
        if (depth == 1)
        {
            eax = rows;
        }
    }
    return port_return(&port, eax, entry->edx);
}
