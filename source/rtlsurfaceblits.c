#include "rtlsurfaceblits.h"

/* Copies a rectangle of one surface into another, converting between the pixel sizes (1 byte 3:3:2,
 * 2 bytes 5:6:5 or 5:5:5, 3 bytes, 4 bytes) the two surfaces have. The original keeps its working
 * state (sizes, pitches, row skips, pointers and the pixel count) in globals at 0x558c0c..0x558c48,
 * which the port updates the same way. */

enum
{
    BELOW = 0x18,
    ARGUMENT_SOURCE_X = 4,
    ARGUMENT_SOURCE_Y = 8,
    ARGUMENT_WIDTH = 0xc,
    ARGUMENT_HEIGHT = 0x10,
    ARGUMENTS = 4,

    /* A surface: its pixels, its pitch in pixels, bytes per pixel, the 2-byte format (2 = 5:6:5,
     * 1 = 5:5:5), a lock flag, and when locked the pitch in bytes. */
    SURFACE_PIXELS = 0,
    SURFACE_PITCH = 4,
    SURFACE_BYTES = 0xc,
    SURFACE_FORMAT = 0xd,
    SURFACE_LOCKED = 0x10,
    SURFACE_STRIDE = 0x14,
    FORMAT_565 = 2,
    FORMAT_555 = 1,

    /* The original's working globals: pointers into the target (bytes, dwords, words) and the
     * source, the pixel count left in the row, the target and source pitches and row skips, the
     * copy length of a locked row, the dword count of an aligned row, the four sizes and formats,
     * and the two locked pixel addresses. */
    TARGET_BYTE = 0x558c0c,
    SOURCE_BYTE = 0x558c10,
    TARGET_DWORD = 0x558c14,
    SOURCE_DWORD = 0x558c18,
    TARGET_WORD = 0x558c1c,
    SOURCE_WORD = 0x558c20,
    COUNT = 0x558c24,
    ROW_BYTES = 0x558c28,
    TARGET_SKIP = 0x558c2c,
    SOURCE_SKIP = 0x558c30,
    ALIGNED_COUNT = 0x558c34,
    TARGET_PITCH = 0x558c38,
    SOURCE_PITCH = 0x558c3c,
    TARGET_BYTES = 0x558c40,
    SOURCE_BYTES = 0x558c41,
    TARGET_FORMAT = 0x558c42,
    SOURCE_FORMAT = 0x558c43,
    SOURCE_ADDRESS = 0x558c44,
    TARGET_ADDRESS = 0x558c48,

    PIXEL_ADDRESS = 0x478eb0
};

/* How a pixel goes from the source to the target. */
typedef enum
{
    COPY_32,
    COPY_24_FROM_32,
    TO_565,
    TO_555,
    COPY_16,
    TO_332,
    COPY_8,
    FROM_332,
    FROM_565,
    FROM_555
} Conversion;

typedef struct
{
    Port *port;
    /* The stack slot of the height, which the original counts down in place. */
    uint32_t height_slot;
    uint32_t width;
    uint32_t height;
} Blit;

/* What a walk over the rows leaves: the final pointers, whether any row or pixel was done, and
 * the pointers after the last row's pixels (before its skip). */
typedef struct
{
    uint32_t target;
    uint32_t source;
    uint32_t target_inner;
    uint32_t source_inner;
    int rows;
    int pixels;
} Walk;

static void put(Port *port, uint32_t global, uint32_t value)
{
    port_set32(port, global, 0, value);
}

static void convert(Port *port, Conversion conversion, uint32_t target, uint32_t source)
{
    uint32_t p;
    switch (conversion)
    {
        case COPY_32:
            port_set32(port, target, 0, port_u32(port, source, 0));
            break;
        case COPY_24_FROM_32:
            port_set8(port, target, 0, port_u8(port, source, 0));
            port_set8(port, target, 1, port_u8(port, source, 1));
            port_set8(port, target, 2, port_u8(port, source, 2));
            break;
        case TO_565:
            p = port_u32(port, source, 0);
            port_set16(port, target, 0,
                       (((p & 0xf80000) >> 5) | ((p & 0xfc00) >> 2) | (p & 0xf8)) >> 3);
            break;
        case TO_555:
            p = port_u32(port, source, 0);
            port_set16(port, target, 0,
                       (((p & 0xf80000) >> 6) | ((p & 0xf800) >> 3) | (p & 0xf8)) >> 3);
            break;
        case COPY_16:
            port_set16(port, target, 0, port_u16(port, source, 0));
            break;
        case TO_332:
            p = port_u32(port, source, 0);
            port_set8(port, target, 0,
                      (((p & 0xe00000) >> 10) | ((p & 0xe000) >> 5) | (p & 0xc0)) >> 6);
            break;
        case COPY_8:
            port_set8(port, target, 0, port_u8(port, source, 0));
            break;
        case FROM_332:
            p = port_u8(port, source, 0);
            port_set32(port, target, 0, (((p & 0xe0) << 10) | ((p & 0x1c) << 5) | (p & 3)) << 6);
            break;
        case FROM_565:
            p = port_u16(port, source, 0);
            port_set32(port, target, 0,
                       (((p & 0xf800) << 5) | ((p & 0x7e0) << 2) | (p & 0x1f)) << 3);
            break;
        case FROM_555:
            p = port_u16(port, source, 0);
            port_set32(port, target, 0,
                       (((p & 0x7c00) << 6) | ((p & 0x3e0) << 3) | (p & 0x1f)) << 3);
            break;
    }
}

/* The rows one pixel at a time: each row counts the width down in COUNT, then skips to the next
 * row. The pointers live in the two globals given. */
static Walk walk_rows(const Blit *blit, Conversion conversion, uint32_t target_global,
                      uint32_t source_global, uint32_t target, uint32_t source,
                      uint32_t target_step, uint32_t source_step, uint32_t target_skip,
                      uint32_t source_skip)
{
    Port *port = blit->port;
    Walk walk = {target, source, 0, 0, 0, 0};
    put(port, target_global, target);
    put(port, source_global, source);
    for (uint32_t height = blit->height; height != 0 && !port->env.failed; height--)
    {
        uint32_t count = blit->width;
        if (conversion == COPY_32 && target_step == 4 && source_step == 4 && !port->env.failed &&
            port_move_dwords(port, walk.target, walk.source, count))
        {
            /* the row in place: the same bytes the loop below leaves */
            walk.target += count * 4;
            walk.source += count * 4;
            walk.pixels = 1;
            count = 0;
        }
        for (; count != 0 && !port->env.failed; count--)
        {
            convert(port, conversion, walk.target, walk.source);
            walk.target += target_step;
            walk.source += source_step;
            walk.pixels = 1;
        }
        put(port, COUNT, count);
        walk.target_inner = walk.target;
        walk.source_inner = walk.source;
        walk.target += target_skip;
        walk.source += source_skip;
        put(port, target_global, walk.target);
        put(port, source_global, walk.source);
        port_set32(port, blit->height_slot, 0, height - 1);
        walk.rows = 1;
    }
    return walk;
}

/* The rows of an aligned 1- or 2-byte copy a dword at a time (count dwords a row) through
 * TARGET_DWORD and SOURCE_DWORD, the row starts in the globals given moving on by the pitches. */
static Walk walk_dwords(const Blit *blit, uint32_t target_global, uint32_t source_global,
                        uint32_t target, uint32_t source, uint32_t count, uint32_t target_pitch,
                        uint32_t source_pitch)
{
    Port *port = blit->port;
    Walk walk = {target, source, 0, 0, 0, 0};
    put(port, ALIGNED_COUNT, count);
    for (uint32_t height = blit->height; height != 0 && !port->env.failed; height--)
    {
        uint32_t to = walk.target;
        uint32_t from = walk.source;
        uint32_t left = count;
        if (!port->env.failed && port_move_dwords(port, to, from, left))
        {
            /* the row in place: the same bytes the loop below leaves */
            to += left * 4;
            from += left * 4;
            walk.pixels = 1;
            left = 0;
        }
        for (; left != 0 && !port->env.failed; left--)
        {
            port_set32(port, to, 0, port_u32(port, from, 0));
            to += 4;
            from += 4;
            walk.pixels = 1;
        }
        put(port, TARGET_DWORD, to);
        put(port, SOURCE_DWORD, from);
        put(port, COUNT, left);
        walk.target_inner = to;
        walk.source_inner = from;
        walk.target += target_pitch;
        walk.source += source_pitch;
        put(port, target_global, walk.target);
        put(port, source_global, walk.source);
        port_set32(port, blit->height_slot, 0, height - 1);
        walk.rows = 1;
    }
    return walk;
}

/* Original 0x47dbc3: either surface locked. Both corners come from 0x478eb0 (byte pitches, +0x14)
 * and every pointer global starts at them. Equal sizes copy each row whole; the conversions step a
 * pixel at a time. Returns the edx the original leaves. */
static uint32_t blit_locked(const Blit *blit, uint32_t target_surface, uint32_t source_surface,
                            uint32_t target_x, uint32_t target_y, uint32_t source_x,
                            uint32_t source_y, uint32_t target_bytes, uint32_t source_bytes,
                            uint32_t target_format, uint32_t source_format)
{
    Port *port = blit->port;
    const uint32_t width = blit->width;
    const uint32_t source = port_call(port, PIXEL_ADDRESS, source_surface, source_x, source_y, 0);
    put(port, SOURCE_ADDRESS, source);
    const uint32_t target = port_call(port, PIXEL_ADDRESS, target_surface, target_x, target_y, 0);
    const uint32_t target_stride = port_u32(port, target_surface, SURFACE_STRIDE);
    const uint32_t source_stride = port_u32(port, source_surface, SURFACE_STRIDE);
    const uint32_t row_bytes = target_bytes * width;
    const uint32_t target_skip = target_stride - row_bytes;
    const uint32_t source_skip = source_stride - source_bytes * width;
    put(port, TARGET_SKIP, target_skip);
    put(port, TARGET_ADDRESS, target);
    put(port, TARGET_DWORD, target);
    put(port, TARGET_WORD, target);
    put(port, TARGET_BYTE, target);
    put(port, SOURCE_SKIP, source_skip);
    put(port, SOURCE_DWORD, source);
    put(port, SOURCE_WORD, source);
    put(port, SOURCE_BYTE, source);

    if (target_bytes == source_bytes)
    {
        put(port, ROW_BYTES, row_bytes);
        put(port, TARGET_SKIP, target_stride);
        put(port, SOURCE_SKIP, source_stride);
        uint32_t to = target;
        uint32_t from = source;
        for (uint32_t height = blit->height; height != 0 && !port->env.failed; height--)
        {
            port_copy(port, to, from, row_bytes);
            to += target_stride;
            from += source_stride;
            put(port, TARGET_BYTE, to);
            put(port, SOURCE_BYTE, from);
            port_set32(port, blit->height_slot, 0, height - 1);
        }
        return source;
    }
    if (target_bytes == 3 && source_bytes == 4)
    {
        const Walk walk = walk_rows(blit, COPY_24_FROM_32, TARGET_BYTE, SOURCE_BYTE, target, source,
                                    3, 4, target_skip, source_skip);
        return walk.pixels ? 0 : source;
    }
    if (target_bytes == 2 && source_bytes == 4)
    {
        if (target_format != FORMAT_565 && target_format != FORMAT_555)
        {
            return source;
        }
        const Walk walk =
            walk_rows(blit, target_format == FORMAT_565 ? TO_565 : TO_555, TARGET_WORD,
                      SOURCE_DWORD, target, source, 2, 4, target_skip, source_skip);
        return walk.rows ? source_skip : source;
    }
    if (target_bytes == 1 && source_bytes == 4)
    {
        const Walk walk = walk_rows(blit, TO_332, TARGET_BYTE, SOURCE_DWORD, target, source, 1, 4,
                                    target_skip, source_skip);
        return walk.rows ? source_skip : source;
    }
    if (target_bytes == 4 && source_bytes == 1)
    {
        const Walk walk = walk_rows(blit, FROM_332, TARGET_DWORD, SOURCE_BYTE, target, source, 4, 1,
                                    target_skip, source_skip);
        return walk.rows ? walk.source : source;
    }
    if (target_bytes != 4)
    {
        return source;
    }
    /* The original loads the source size into dh here. */
    const uint32_t edx = (source & 0xffff00ffu) | (source_bytes << 8);
    if (source_bytes != 2 || (source_format != FORMAT_565 && source_format != FORMAT_555))
    {
        return edx;
    }
    if (source_format == FORMAT_565)
    {
        const Walk walk = walk_rows(blit, FROM_565, TARGET_DWORD, SOURCE_WORD, target, source, 4, 2,
                                    target_skip, source_skip);
        return walk.rows ? 0 : edx;
    }
    const Walk walk = walk_rows(blit, FROM_555, TARGET_DWORD, SOURCE_WORD, target, source, 4, 2,
                                target_skip, source_skip);
    return walk.rows ? walk.source : edx;
}

/* Original 0x47ce10 (eax = the target surface, edx = the source surface, ebx and ecx = the target
 * corner; stack: the source corner, the width and the height; ret 0x10). Pitches are in pixels
 * unless a surface is locked (+0x10), which takes 0x47dbc3's byte-pitch paths. Pairs of sizes the
 * original has no path for copy nothing.
 *
 * Kept from the original: the height's stack slot is counted down; whole-surface copies (both
 * pitches equal to the width) are one copy for 4 bytes, and for 2 and 1 bytes when the width is a
 * multiple of 4, other such rows going a dword at a time; and the edx it returns, which callers
 * read, is whatever its path last left there (a pointer, a skip, the height or 0). */
uint32_t vertrix_port_surface_blit_47ce10(PORT_SIGNATURE)
{
    uint8_t stack[BELOW + 8 + 4 * ARGUMENTS];
    Port port;
    port_open_arguments(&port, stack, calls, services, globals, entry, BELOW, ARGUMENTS);
    const uint32_t target_surface = entry->eax;
    const uint32_t source_surface = entry->edx;
    const uint32_t target_x = entry->ebx;
    const uint32_t target_y = entry->ecx;
    const uint32_t source_x = port_u32(&port, entry->esp, ARGUMENT_SOURCE_X);
    const uint32_t source_y = port_u32(&port, entry->esp, ARGUMENT_SOURCE_Y);
    const Blit blit = {&port, entry->esp + ARGUMENT_HEIGHT,
                       port_u32(&port, entry->esp, ARGUMENT_WIDTH),
                       port_u32(&port, entry->esp, ARGUMENT_HEIGHT)};
    const uint32_t width = blit.width;
    const uint32_t height = blit.height;

    const uint32_t target_bytes = port_u8(&port, target_surface, SURFACE_BYTES);
    port_set8(&port, TARGET_BYTES, 0, target_bytes);
    const uint32_t source_bytes = port_u8(&port, source_surface, SURFACE_BYTES);
    port_set8(&port, SOURCE_BYTES, 0, source_bytes);
    const uint32_t target_format = port_u8(&port, target_surface, SURFACE_FORMAT);
    port_set8(&port, TARGET_FORMAT, 0, target_format);
    const uint32_t source_format = port_u8(&port, source_surface, SURFACE_FORMAT);
    port_set8(&port, SOURCE_FORMAT, 0, source_format);
    if (port_u32(&port, target_surface, SURFACE_LOCKED) != 0 ||
        port_u32(&port, source_surface, SURFACE_LOCKED) != 0)
    {
        const uint32_t edx =
            blit_locked(&blit, target_surface, source_surface, target_x, target_y, source_x,
                        source_y, target_bytes, source_bytes, target_format, source_format);
        return port_return(&port, 0, edx);
    }

    const uint32_t target_pixels = port_u32(&port, target_surface, SURFACE_PIXELS);
    const uint32_t source_pixels = port_u32(&port, source_surface, SURFACE_PIXELS);
    const uint32_t target_pitch = port_u32(&port, target_surface, SURFACE_PITCH);
    const uint32_t source_pitch = port_u32(&port, source_surface, SURFACE_PITCH);
    const uint32_t target_cell = target_y * target_pitch + target_x;
    const uint32_t source_cell = source_y * source_pitch + source_x;
    const uint32_t target_skip = target_pitch - width;
    const uint32_t source_skip = source_pitch - width;
    uint32_t edx = source_x;
    int pitches = 1;
    if (target_bytes == 4 && source_bytes == 4)
    {
        const uint32_t target = target_pixels + target_cell * 4;
        const uint32_t source = source_pixels + source_cell * 4;
        put(&port, TARGET_SKIP, target_skip);
        put(&port, SOURCE_SKIP, source_skip);
        edx = source_x << 2;
        if (width == target_pitch && source_pitch == width)
        {
            put(&port, SOURCE_DWORD, source);
            put(&port, TARGET_DWORD, target);
            port_copy(&port, target, source, width * height * 4);
        }
        else
        {
            const Walk walk = walk_rows(&blit, COPY_32, TARGET_DWORD, SOURCE_DWORD, target, source,
                                        4, 4, target_skip * 4, source_skip * 4);
            edx = walk.pixels ? walk.target_inner : edx;
        }
    }
    else if (target_bytes == 3 && source_bytes == 4)
    {
        const uint32_t target = target_pixels + target_cell * 3;
        put(&port, TARGET_SKIP, target_skip * 3);
        put(&port, SOURCE_SKIP, source_skip * 4);
        const Walk walk =
            walk_rows(&blit, COPY_24_FROM_32, TARGET_BYTE, SOURCE_BYTE, target,
                      source_pixels + source_cell * 4, 3, 4, target_skip * 3, source_skip * 4);
        edx = walk.rows ? walk.target : target;
    }
    else if (target_bytes == 2 && source_bytes == 4)
    {
        if (target_format == FORMAT_565 || target_format == FORMAT_555)
        {
            const uint32_t target = target_pixels + target_cell * 2;
            put(&port, TARGET_SKIP, target_skip);
            put(&port, SOURCE_SKIP, source_skip);
            const Walk walk = walk_rows(
                &blit, target_format == FORMAT_565 ? TO_565 : TO_555, TARGET_WORD, SOURCE_DWORD,
                target, source_pixels + source_cell * 4, 2, 4, target_skip * 2, source_skip * 4);
            if (target_format == FORMAT_565)
            {
                edx = walk.rows ? walk.source : target;
            }
            else
            {
                edx = walk.pixels ? walk.target_inner : height;
            }
        }
        else
        {
            pitches = 0;
        }
    }
    else if (target_bytes == 2 && source_bytes == 2)
    {
        const uint32_t target = target_pixels + target_cell * 2;
        const uint32_t source = source_pixels + source_cell * 2;
        put(&port, TARGET_SKIP, target_skip);
        put(&port, SOURCE_SKIP, source_skip);
        put(&port, SOURCE_WORD, source);
        put(&port, TARGET_WORD, target);
        edx = source;
        if ((width & 3) != 0)
        {
            const Walk walk = walk_rows(&blit, COPY_16, TARGET_WORD, SOURCE_WORD, target, source, 2,
                                        2, target_skip * 2, source_skip * 2);
            edx = walk.rows ? walk.target : source;
        }
        else if (target_pitch == width && source_pitch == width)
        {
            port_copy(&port, target, source, width * height * 2);
        }
        else
        {
            const Walk walk = walk_dwords(&blit, TARGET_WORD, SOURCE_WORD, target, source,
                                          width >> 1, target_pitch * 2, source_pitch * 2);
            edx = walk.pixels ? walk.target_inner : source;
        }
    }
    else if (target_bytes == 1 && source_bytes == 4)
    {
        put(&port, TARGET_SKIP, target_skip);
        put(&port, SOURCE_SKIP, source_skip);
        const Walk walk =
            walk_rows(&blit, TO_332, TARGET_BYTE, SOURCE_DWORD, target_pixels + target_cell,
                      source_pixels + source_cell * 4, 1, 4, target_skip, source_skip * 4);
        edx = walk.pixels ? walk.target_inner : height;
    }
    else if (target_bytes == 1 && source_bytes == 1)
    {
        const uint32_t target = target_pixels + target_cell;
        const uint32_t source = source_pixels + source_cell;
        put(&port, TARGET_SKIP, target_skip);
        put(&port, SOURCE_SKIP, source_skip);
        put(&port, SOURCE_BYTE, source);
        put(&port, TARGET_BYTE, target);
        edx = target;
        if ((width & 3) != 0)
        {
            const Walk walk = walk_rows(&blit, COPY_8, TARGET_BYTE, SOURCE_BYTE, target, source, 1,
                                        1, target_skip, source_skip);
            edx = walk.rows ? walk.source : target;
        }
        else if (target_pitch == width && width == source_pitch)
        {
            port_copy(&port, target, source, width * height);
        }
        else
        {
            const Walk walk = walk_dwords(&blit, TARGET_BYTE, SOURCE_BYTE, target, source,
                                          width >> 2, target_pitch, source_pitch);
            edx = walk.pixels ? walk.source_inner : target;
        }
    }
    else if (target_bytes == 4 && source_bytes == 1)
    {
        const uint32_t target = target_pixels + target_cell * 4;
        put(&port, TARGET_SKIP, target_skip);
        put(&port, SOURCE_SKIP, source_skip);
        const Walk walk =
            walk_rows(&blit, FROM_332, TARGET_DWORD, SOURCE_BYTE, target,
                      source_pixels + source_cell, 4, 1, target_skip * 4, source_skip);
        edx = walk.pixels ? walk.target_inner : target;
    }
    else if (target_bytes == 4 && source_bytes == 2 &&
             (source_format == FORMAT_565 || source_format == FORMAT_555))
    {
        put(&port, TARGET_SKIP, target_skip);
        put(&port, SOURCE_SKIP, source_skip);
        const Walk walk =
            walk_rows(&blit, source_format == FORMAT_565 ? FROM_565 : FROM_555, TARGET_DWORD,
                      SOURCE_WORD, target_pixels + target_cell * 4, source_pixels + source_cell * 2,
                      4, 2, target_skip * 4, source_skip * 2);
        if (source_format == FORMAT_565)
        {
            edx = walk.pixels ? 0 : height;
        }
        else
        {
            edx = walk.rows ? walk.target : 0;
        }
    }
    else
    {
        pitches = 0;
    }
    if (pitches)
    {
        put(&port, TARGET_PITCH, target_pitch);
        put(&port, SOURCE_PITCH, source_pitch);
    }
    return port_return(&port, 0, edx);
}
