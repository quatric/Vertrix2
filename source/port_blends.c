#include "port_blends.h"

/* The surfaces' alpha blends through the percentage tables. */

/* The blended pixel: each channel the source's through the table `ours` plus the target's
 * through `theirs`, added and or-ed together as the original does, opaque. */
static uint32_t blend_pixel(Port *port, uint32_t source, uint32_t target, uint32_t ours,
                            uint32_t theirs)
{
    uint32_t red = port_u8(port, (port_u32(port, source, 0) >> 16) & 0xff, ours);
    uint32_t value = port_u8(port, theirs, (port_u32(port, target, 0) >> 16) & 0xff);
    uint32_t green;
    uint32_t blue;
    value = ((value + red) << 16) | 0xff000000u;
    green = port_u8(port, port_u16(port, source, 0) >> 8, ours);
    green += port_u8(port, theirs, port_u16(port, target, 0) >> 8);
    value |= green << 8;
    blue = port_u8(port, ours + port_u8(port, source, 0), 0);
    blue += port_u8(port, theirs, port_u8(port, target, 0));
    return blue | value;
}

/* Original 0x47c930: the source surface edx's rectangle at the first and second stack words, the
 * third wide and the fourth high, blended at the fifth (a percentage) onto the target surface eax
 * at bx, cx, both of format 4 (+0xc; the formats and the +0xd bytes go to 0x558bbc..0x558bbf).
 * The tables 0x558cf0 + 0x100 times the percentage (0x55f1f0) and times 100 less it (0x55f1f4)
 * blend each source pixel with alpha (its top byte) into the target (blend_pixel); the target
 * runs through 0x558b9c, the count of a row through 0x558ba4, the rows' rests through 0x558ba8
 * and 0x558bac, and the source's end goes to 0x558ba0. eax and edx are the last row step's (the
 * surfaces for other formats). ret 0x14. */
uint32_t vertrix_port_surface_blend_47c930(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x14
    };
    Port port;
    uint8_t stack[BELOW + 8 + 0x14];
    uint32_t esp = entry->esp - BELOW;
    uint32_t target = entry->eax;
    uint32_t source = entry->edx;
    uint32_t percent;
    uint32_t ours;
    uint32_t theirs;
    uint32_t from;
    uint32_t rows;
    uint32_t count;
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    port_open_arguments(&port, stack, calls, services, globals, entry, BELOW, 5);
    from = port_u32(&port, 0, 0x558ba0);
    port_set8(&port, 0, 0x558bbc, port_u8(&port, target, 0xc));
    port_set8(&port, 0, 0x558bbd, port_u8(&port, source, 0xc));
    port_set8(&port, 0, 0x558bbe, port_u8(&port, target, 0xd));
    port_set8(&port, 0, 0x558bbf, port_u8(&port, source, 0xd));
    if (port_u8(&port, 0, 0x558bbc) == 4 && port_u8(&port, 0, 0x558bbd) == 4)
    {
        percent = port_u32(&port, esp, 0x28);
        ours = 0x558cf0 + (percent << 8);
        port_set32(&port, 0, 0x55f1f0, ours);
        theirs = 0x558cf0 + ((0x64 - percent) << 8);
        port_set32(&port, 0, 0x558bb4, port_u32(&port, target, 4));
        port_set32(&port, 0, 0x558bb8, port_u32(&port, source, 4));
        port_set32(&port, 0, 0x558ba8, port_u32(&port, 0, 0x558bb4) - port_u32(&port, esp, 0x20));
        port_set32(&port, 0, 0x558bac, port_u32(&port, 0, 0x558bb8) - port_u32(&port, esp, 0x20));
        port_set32(&port, 0, 0x558b9c,
                   port_u32(&port, target, 0) + (port_u32(&port, 0, 0x558bb4) * entry->ecx << 2) +
                       (entry->ebx << 2));
        port_set32(&port, 0, 0x55f1f4, theirs);
        eax = port_u32(&port, source, 0) +
              port_u32(&port, 0, 0x558bb8) * port_u32(&port, esp, 0x1c) * 4;
        from = (port_u32(&port, esp, 0x18) << 2) + eax;
        rows = port_u32(&port, esp, 0x24);
        while (rows != 0 && !port.env.failed)
        {
            count = port_u32(&port, esp, 0x20);
            port_set32(&port, 0, 0x558ba4, count);
            while (count != 0 && !port.env.failed)
            {
                if ((port_u32(&port, from, 0) >> 24) != 0)
                {
                    uint32_t at = port_u32(&port, 0, 0x558b9c);
                    port_set32(&port, at, 0,
                               blend_pixel(&port, from, at, port_u32(&port, 0, 0x55f1f0),
                                           port_u32(&port, 0, 0x55f1f4)));
                }
                from += 4;
                port_set32(&port, 0, 0x558b9c, port_u32(&port, 0, 0x558b9c) + 4);
                count = port_u32(&port, 0, 0x558ba4) - 1;
                port_set32(&port, 0, 0x558ba4, count);
            }
            edx = port_u32(&port, 0, 0x558b9c) + (port_u32(&port, 0, 0x558ba8) << 2);
            eax = port_u32(&port, 0, 0x558bac) << 2;
            port_set32(&port, 0, 0x558b9c, edx);
            from += eax;
            rows = port_u32(&port, esp, 0x24) - 1;
            port_set32(&port, esp, 0x24, rows);
        }
    }
    port_set32(&port, 0, 0x558ba0, from);
    return port_return(&port, eax, edx);
}

/* blend_pixel with the loads addressed as 0x47cb40 addresses them. */
static uint32_t blend_pixel_masked(Port *port, uint32_t source, uint32_t target, uint32_t ours,
                                   uint32_t theirs)
{
    uint32_t red = port_u8(port, ours, (port_u32(port, source, 0) >> 16) & 0xff);
    uint32_t value = port_u8(port, (port_u32(port, target, 0) >> 16) & 0xff, theirs);
    uint32_t green;
    uint32_t blue;
    value = ((value + red) << 16) | 0xff000000u;
    green = port_u8(port, ours, port_u16(port, source, 0) >> 8);
    green += port_u8(port, port_u16(port, target, 0) >> 8, theirs);
    value |= green << 8;
    blue = port_u8(port, ours, port_u8(port, source, 0));
    blue += port_u8(port, port_u8(port, target, 0), theirs);
    return blue | value;
}

/* Original 0x47cb40: 0x47c930 for target pixels with alpha too (a target pixel whose top byte is
 * 0 is kept), with its own globals (0x558bf0..0x558bf3, the widths 0x558be8 and 0x558bec, the
 * rests 0x558bdc and 0x558be0, the target 0x558bc8, the count 0x558bd8 and the source's end
 * 0x558bcc). eax and edx are the last row step's (the surfaces for other formats). ret 0x14. */
uint32_t vertrix_port_surface_blend_masked_47cb40(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x18
    };
    Port port;
    uint8_t stack[BELOW + 8 + 0x14];
    uint32_t esp = entry->esp - BELOW;
    uint32_t target = entry->eax;
    uint32_t source = entry->edx;
    uint32_t percent;
    uint32_t from;
    uint32_t rows;
    uint32_t count;
    uint32_t at;
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    port_open_arguments(&port, stack, calls, services, globals, entry, BELOW, 5);
    from = port_u32(&port, 0, 0x558bcc);
    port_set8(&port, 0, 0x558bf0, port_u8(&port, target, 0xc));
    port_set8(&port, 0, 0x558bf1, port_u8(&port, source, 0xc));
    port_set8(&port, 0, 0x558bf2, port_u8(&port, target, 0xd));
    port_set8(&port, 0, 0x558bf3, port_u8(&port, source, 0xd));
    if (port_u8(&port, 0, 0x558bf0) == 4 && port_u8(&port, 0, 0x558bf1) == 4)
    {
        percent = port_u32(&port, esp, 0x2c);
        port_set32(&port, 0, 0x55f1f0, 0x558cf0 + (percent << 8));
        port_set32(&port, 0, 0x558be8, port_u32(&port, target, 4));
        port_set32(&port, 0, 0x558bec, port_u32(&port, source, 4));
        port_set32(&port, 0, 0x558bdc, port_u32(&port, 0, 0x558be8) - port_u32(&port, esp, 0x24));
        port_set32(&port, 0, 0x55f1f4, 0x558cf0 + ((0x64 - percent) << 8));
        port_set32(&port, 0, 0x558bc8,
                   port_u32(&port, target, 0) + (entry->ecx * port_u32(&port, 0, 0x558be8) << 2) +
                       (entry->ebx << 2));
        from = (port_u32(&port, 0, 0x558bec) * port_u32(&port, esp, 0x20) << 2) +
               port_u32(&port, source, 0);
        port_set32(&port, 0, 0x558be0, port_u32(&port, 0, 0x558bec) - port_u32(&port, esp, 0x24));
        eax = port_u32(&port, esp, 0x1c) << 2;
        from += eax;
        edx = port_u32(&port, esp, 0x28);
        rows = edx;
        while (rows != 0 && !port.env.failed)
        {
            count = port_u32(&port, esp, 0x24);
            port_set32(&port, 0, 0x558bd8, count);
            while (count != 0 && !port.env.failed)
            {
                at = port_u32(&port, 0, 0x558bc8);
                if ((port_u32(&port, from, 0) >> 24) != 0 && (port_u32(&port, at, 0) >> 24) != 0)
                {
                    port_set32(&port, at, 0,
                               blend_pixel_masked(&port, from, at, port_u32(&port, 0, 0x55f1f0),
                                                  port_u32(&port, 0, 0x55f1f4)));
                }
                port_set32(&port, 0, 0x558bc8, port_u32(&port, 0, 0x558bc8) + 4);
                from += 4;
                count = port_u32(&port, 0, 0x558bd8) - 1;
                port_set32(&port, 0, 0x558bd8, count);
                edx = count;
            }
            port_set32(&port, 0, 0x558bc8,
                       port_u32(&port, 0, 0x558bc8) + (port_u32(&port, 0, 0x558bdc) << 2));
            eax = port_u32(&port, 0, 0x558be0) << 2;
            from += eax;
            rows = port_u32(&port, esp, 0x28) - 1;
            port_set32(&port, esp, 0x28, rows);
        }
    }
    port_set32(&port, 0, 0x558bcc, from);
    return port_return(&port, eax, edx);
}
