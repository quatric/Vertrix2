#include "port_rtlcrossfades.h"

/* Two surfaces crossfaded into a third. */

enum
{
    DEPTH = 0x558ac4,
    FORMAT = 0x558ac5,
    FIRST = 0x55f1f0,
    SECOND = 0x55f1f4,
    FIRST_PIXEL = 0x558ab8,
    SECOND_PIXEL = 0x558abc,
    COLUMNS = 0x558ac0,
    ROWS = 0x558aa4,
    TARGET_SKIP = 0x558aa8,
    FIRST_SKIP = 0x558aac,
    SECOND_SKIP = 0x558ab0,
    TARGET32 = 0x558a88,
    FIRST32 = 0x558a8c,
    SECOND32 = 0x558a90,
    TARGET16 = 0x558a94,
    SECOND16 = 0x558a9c,
    TARGET8 = 0x558a7c,
    FIRST8 = 0x558a80,
    SECOND8 = 0x558a84
};

static uint32_t g32(Port *port, uint32_t address)
{
    return port_u32(port, 0, address);
}

static void s32(Port *port, uint32_t address, uint32_t value)
{
    port_set32(port, 0, address, value);
}

/* The two pixels (0xRRGGBB) blended a channel at a time through the level's tables: the first's
 * entry plus the second's, OR-ed together. */
static uint32_t blend(Port *port, uint32_t first, uint32_t second)
{
    uint32_t a = g32(port, FIRST);
    uint32_t b = g32(port, SECOND);
    uint32_t red = port_u8(port, a, (first >> 16) & 0xff) + port_u8(port, b, (second >> 16) & 0xff);
    uint32_t green =
        port_u8(port, a, (first & 0xffff) >> 8) + port_u8(port, b, (second & 0xffff) >> 8);
    uint32_t blue = port_u8(port, a, first & 0xff) + port_u8(port, b, second & 0xff);
    return (red << 16) | (green << 8) | blue;
}

static uint32_t widen565(uint32_t word)
{
    return (((word & 0xf800) << 5) | ((word & 0x7e0) << 2) | (word & 0x1f)) << 3;
}

static uint32_t widen555(uint32_t word)
{
    return (((word & 0x7c00) << 6) | ((word & 0x3e0) << 3) | (word & 0x1f)) << 3;
}

static uint32_t widen332(uint32_t byte)
{
    return (((byte & 0xe0) << 10) | ((byte & 0x1c) << 5) | (byte & 3)) << 6;
}

static uint32_t pack565(uint32_t value)
{
    return (((value & 0xf80000) >> 5) | ((value & 0xfc00) >> 2) | (value & 0xf8)) >> 3;
}

static uint32_t pack555(uint32_t value)
{
    return (((value & 0xf80000) >> 6) | ((value & 0xf800) >> 3) | (value & 0xf8)) >> 3;
}

static uint32_t pack332(uint32_t value)
{
    return (((value & 0xe00000) >> 10) | ((value & 0xe000) >> 5) | (value & 0xc0)) >> 6;
}

/* One 32-bit pixel of the walks 0x558a88.. blended. */
static void pixel32(Port *port)
{
    uint32_t first = g32(port, FIRST32);
    uint32_t second = g32(port, SECOND32);
    uint32_t target = g32(port, TARGET32);
    uint32_t value = blend(port, port_u32(port, first, 0), port_u32(port, second, 0));
    s32(port, FIRST32, first + 4);
    s32(port, SECOND32, second + 4);
    port_set32(port, target, 0, value);
    s32(port, TARGET32, target + 4);
}

/* One 16-bit pixel (the first at *first, the walks 0x558a94/0x558a9c) blended; edi the blend. */
static void pixel16(Port *port, uint32_t *first, int five_six_five, uint32_t *edi)
{
    uint32_t second = g32(port, SECOND16);
    uint32_t target;
    uint32_t a = port_u16(port, *first, 0);
    uint32_t b;
    s32(port, FIRST_PIXEL, five_six_five ? widen565(a) : widen555(a));
    b = port_u16(port, second, 0);
    s32(port, SECOND_PIXEL, five_six_five ? widen565(b) : widen555(b));
    *edi = blend(port, g32(port, FIRST_PIXEL), g32(port, SECOND_PIXEL));
    *first += 2;
    target = g32(port, TARGET16) + 2;
    s32(port, SECOND16, second + 2);
    port_set16(port, target, -2u, five_six_five ? pack565(*edi) : pack555(*edi));
    s32(port, TARGET16, target);
}

/* One 8-bit (3-3-2) pixel of the walks 0x558a7c.. blended; edi the blend. */
static void pixel8(Port *port, uint32_t *edi)
{
    uint32_t first = g32(port, FIRST8);
    uint32_t second;
    uint32_t target;
    s32(port, FIRST_PIXEL, widen332(port_u8(port, first, 0)));
    second = g32(port, SECOND8);
    s32(port, SECOND_PIXEL, widen332(port_u8(port, second, 0)));
    *edi = blend(port, g32(port, FIRST_PIXEL), g32(port, SECOND_PIXEL));
    target = g32(port, TARGET8) + 1;
    s32(port, FIRST8, first + 1);
    s32(port, SECOND8, second + 1);
    port_set8(port, target, -1u, pack332(*edi));
    s32(port, TARGET8, target);
}

/* The level ecx's tables: 0x558cf0 + level * 256 for the first, + (100 - level) * 256 for the
 * second. */
static void set_tables(Port *port, uint32_t level)
{
    s32(port, FIRST, 0x558cf0 + (level << 8));
    s32(port, SECOND, 0x558cf0 + ((0x64 - level) << 8));
}

/* Original 0x47ab70: the surfaces edx and ebx crossfaded into the surface eax at the level ecx
 * (0..100, the tables 0x55f1f0/0x55f1f4), a channel at a time, by the target's depth 0x558ac4 and
 * format 0x558ac5: 32-bit, 16-bit 5-6-5 (format 2) or 5-5-5 (1), or 8-bit 3-3-2; as one run of
 * width * height pixels when none of the three has a row skip +0x10, else row by row with the skips
 * +0x18 (0x558aa8..0x558ab0, the rows 0x558aa4, the columns 0x558ac0). The walks are kept at
 * 0x558a7c..0x558a9c, the widened pixels at 0x558ab8/0x558abc, and the original's esi, edi and ebp
 * at 0x558aa0, 0x558ab4 and 0x558a98. eax and edx as the original leaves them. */
uint32_t vertrix_port_surface_crossfade_47ab70(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x24
    };
    Port port;
    uint32_t target = entry->eax;
    uint32_t first = entry->edx;
    uint32_t second = entry->ebx;
    uint32_t esi;
    uint32_t edi;
    uint32_t ebp;
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t depth;
    uint32_t format;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, entry->esp, -4u, entry->esi);
    port_set32(&port, entry->esp, -8u, entry->edi);
    port_set32(&port, entry->esp, -0xcu, entry->ebp);
    esi = g32(&port, 0x558aa0);
    edi = g32(&port, 0x558ab4);
    ebp = g32(&port, 0x558a98);
    port_set8(&port, 0, DEPTH, port_u8(&port, target, 0xc));
    port_set8(&port, 0, FORMAT, port_u8(&port, target, 0xd));
    if (port_u32(&port, target, 0x10) == 0 && port_u32(&port, first, 0x10) == 0 &&
        port_u32(&port, second, 0x10) == 0)
    {
        esi = port_u32(&port, target, 4) * port_u32(&port, target, 8);
        set_tables(&port, entry->ecx);
        depth = port_u8(&port, 0, DEPTH);
        if (depth == 4)
        {
            s32(&port, TARGET32, port_u32(&port, target, 0));
            s32(&port, FIRST32, port_u32(&port, first, 0));
            eax = port_u32(&port, second, 0);
            s32(&port, SECOND32, eax);
            for (; esi != 0 && !port.env.failed; esi--)
            {
                pixel32(&port);
                eax = g32(&port, SECOND32);
                edx = g32(&port, FIRST32);
            }
        }
        else if (depth == 2)
        {
            s32(&port, TARGET16, port_u32(&port, target, 0));
            format = port_u8(&port, 0, FORMAT);
            eax = port_u32(&port, second, 0);
            ebp = port_u32(&port, first, 0);
            s32(&port, SECOND16, eax);
            if (format == 2 || format == 1)
            {
                for (; esi != 0 && !port.env.failed; esi--)
                {
                    pixel16(&port, &ebp, format == 2, &edi);
                    eax = g32(&port, SECOND16);
                    edx = g32(&port, TARGET16);
                }
            }
        }
        else if (depth == 1)
        {
            s32(&port, TARGET8, port_u32(&port, target, 0));
            s32(&port, FIRST8, port_u32(&port, first, 0));
            eax = port_u32(&port, second, 0);
            s32(&port, SECOND8, eax);
            for (; esi != 0 && !port.env.failed; esi--)
            {
                pixel8(&port, &edi);
                eax = g32(&port, FIRST8);
                edx = g32(&port, SECOND8);
            }
        }
    }
    else
    {
        s32(&port, COLUMNS, port_u32(&port, target, 4));
        s32(&port, TARGET_SKIP, port_u32(&port, target, 0x18));
        s32(&port, FIRST_SKIP, port_u32(&port, first, 0x18));
        s32(&port, SECOND_SKIP, port_u32(&port, second, 0x18));
        s32(&port, ROWS, port_u32(&port, target, 8));
        set_tables(&port, entry->ecx);
        depth = port_u8(&port, 0, DEPTH);
        if (depth == 4)
        {
            s32(&port, TARGET32, port_u32(&port, target, 0));
            s32(&port, FIRST32, port_u32(&port, first, 0));
            eax = port_u32(&port, second, 0);
            s32(&port, SECOND32, eax);
            while (g32(&port, ROWS) != 0 && !port.env.failed)
            {
                for (esi = g32(&port, COLUMNS); esi != 0 && !port.env.failed; esi--)
                {
                    pixel32(&port);
                }
                s32(&port, TARGET32, g32(&port, TARGET32) + g32(&port, TARGET_SKIP));
                s32(&port, FIRST32, g32(&port, FIRST32) + g32(&port, FIRST_SKIP));
                s32(&port, SECOND32, g32(&port, SECOND32) + g32(&port, SECOND_SKIP));
                eax = g32(&port, SECOND_SKIP);
                edx = g32(&port, ROWS) - 1;
                s32(&port, ROWS, edx);
            }
        }
        else if (depth == 2)
        {
            s32(&port, TARGET16, port_u32(&port, target, 0));
            format = port_u8(&port, 0, FORMAT);
            eax = port_u32(&port, second, 0);
            ebp = port_u32(&port, first, 0);
            s32(&port, SECOND16, eax);
            if (format == 2 || format == 1)
            {
                while (g32(&port, ROWS) != 0 && !port.env.failed)
                {
                    for (esi = g32(&port, COLUMNS); esi != 0 && !port.env.failed; esi--)
                    {
                        pixel16(&port, &ebp, format == 2, &edi);
                    }
                    s32(&port, TARGET16, g32(&port, TARGET16) + g32(&port, TARGET_SKIP));
                    ebp += g32(&port, FIRST_SKIP);
                    edx = g32(&port, SECOND16) + g32(&port, SECOND_SKIP);
                    eax = g32(&port, ROWS) - 1;
                    s32(&port, SECOND16, edx);
                    s32(&port, ROWS, eax);
                }
            }
        }
        else if (depth == 1)
        {
            s32(&port, TARGET8, port_u32(&port, target, 0));
            s32(&port, FIRST8, port_u32(&port, first, 0));
            eax = port_u32(&port, second, 0);
            s32(&port, SECOND8, eax);
            while (g32(&port, ROWS) != 0 && !port.env.failed)
            {
                for (esi = g32(&port, COLUMNS); esi != 0 && !port.env.failed; esi--)
                {
                    pixel8(&port, &edi);
                }
                eax = g32(&port, TARGET_SKIP);
                s32(&port, TARGET8, g32(&port, TARGET8) + eax);
                edx = g32(&port, FIRST8) + g32(&port, FIRST_SKIP);
                eax = g32(&port, SECOND_SKIP);
                s32(&port, FIRST8, edx);
                s32(&port, SECOND8, g32(&port, SECOND8) + eax);
                s32(&port, ROWS, g32(&port, ROWS) - 1);
            }
        }
    }
    s32(&port, 0x558a98, ebp);
    s32(&port, 0x558ab4, edi);
    s32(&port, 0x558aa0, esi);
    return port_return(&port, eax, edx);
}
