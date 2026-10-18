#include "rtlblits.h"

/* Keyed surface blits and render tables. */

/* Original 0x47e200 (four stack arguments, popped: the source x and y, the width and height): the
 * source surface edx's pixels with a non-zero top byte copied onto the surface eax at ebx, ecx,
 * when both are plain 32-bit surfaces (+0x10 0, depth +0xc 4); the depths and formats kept at
 * 0x558c70..0x558c73, the pitches at 0x558c68/0x558c6c, the row skips at 0x558c5c/0x558c60 and the
 * walk left at 0x558c4c/0x558c50/0x558c54. */
uint32_t vertrix_port_surface_blit_keyed_47e200(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x1c
    };
    Port port;
    uint8_t stack[BELOW + 8 + 4 * 4];
    uint32_t target = entry->eax;
    uint32_t source = entry->edx;
    uint32_t esi;
    uint32_t edi;
    uint32_t ebp;
    uint32_t eax;
    uint32_t edx = entry->edx;
    uint32_t width;
    uint32_t height;
    port_open_arguments(&port, stack, calls, services, globals, entry, BELOW, 4);
    port_set32(&port, entry->esp, -4u, entry->esi);
    port_set32(&port, entry->esp, -8u, entry->edi);
    port_set32(&port, entry->esp, -0xcu, entry->ebp);
    port_set32(&port, entry->esp, -0x10u, target);
    port_set32(&port, entry->esp, -0x14u, source);
    port_set32(&port, entry->esp, -0x1cu, entry->ebx);
    port_set32(&port, entry->esp, -0x18u, entry->ecx);
    esi = port_u32(&port, 0, 0x558c50);
    edi = port_u32(&port, 0, 0x558c4c);
    ebp = port_u32(&port, 0, 0x558c54);
    width = port_u32(&port, entry->esp, 0xc);
    height = port_u32(&port, entry->esp, 0x10);
    port_set8(&port, 0, 0x558c70, port_u8(&port, target, 0xc));
    port_set8(&port, 0, 0x558c71, port_u8(&port, source, 0xc));
    port_set8(&port, 0, 0x558c72, port_u8(&port, target, 0xd));
    port_set8(&port, 0, 0x558c73, port_u8(&port, source, 0xd));
    eax = target;
    if (port_u32(&port, target, 0x10) == 0)
    {
        eax = source;
        if (port_u32(&port, source, 0x10) == 0)
        {
            uint32_t depth = port_u8(&port, 0, 0x558c70);
            eax = (source & 0xffff00ffu) | (depth << 8);
            if (depth == 4 && depth == port_u8(&port, 0, 0x558c71))
            {
                uint32_t skip;
                port_set32(&port, 0, 0x558c68, port_u32(&port, target, 4));
                port_set32(&port, 0, 0x558c6c, port_u32(&port, source, 4));
                port_set32(&port, 0, 0x558c5c, port_u32(&port, 0, 0x558c68) - width);
                port_set32(&port, 0, 0x558c60, port_u32(&port, 0, 0x558c6c) - width);
                edi = (entry->ebx << 2) + ((port_u32(&port, 0, 0x558c68) * entry->ecx) << 2) +
                      port_u32(&port, target, 0);
                edx = (port_u32(&port, 0, 0x558c6c) * port_u32(&port, entry->esp, 8)) * 4;
                eax = port_u32(&port, source, 0) + edx;
                esi = (port_u32(&port, entry->esp, 4) << 2) + eax;
                while (height != 0 && !port.env.failed)
                {
                    ebp = width;
                    while (ebp != 0 && !port.env.failed)
                    {
                        edx = port_u32(&port, esi, 0) >> 24;
                        eax = esi;
                        if ((edx & 0xff) != 0)
                        {
                            eax = port_u32(&port, esi, 0);
                            port_set32(&port, edi, 0, eax);
                        }
                        edi += 4;
                        esi += 4;
                        ebp--;
                    }
                    skip = port_u32(&port, 0, 0x558c5c);
                    edi += skip << 2;
                    eax = port_u32(&port, 0, 0x558c60) << 2;
                    esi += eax;
                    height--;
                }
            }
        }
    }
    port_set32(&port, 0, 0x558c54, ebp);
    port_set32(&port, 0, 0x558c4c, edi);
    port_set32(&port, 0, 0x558c50, esi);
    return port_return(&port, eax, edx);
}

/* Original 0x480d60: a run-length coded picture read from the stream edx into the pixels eax: the
 * 128-byte header (0x48a930) after the start (0x48aad0), the palette's place (the end less 768,
 * 0x48aa70), the width and height +1 from the header's +8/+10, the line padding from +0x42; each
 * row's bytes decoded (from 0xc0 up a repeat count for the next byte), the padding skipped
 * (0x48aa90) after a full row. With palette room ebx its 768 bytes are read (0x48aaf0) and kept
 * divided by 4. */
uint32_t vertrix_port_picture_decode_rle_480d60(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0xb0
    };
    Port port;
    uint8_t stack[BELOW + 8];
    uint32_t ebp = entry->esp - 4;
    uint32_t stream = entry->edx;
    uint32_t edi = entry->eax;
    uint32_t eax;
    uint32_t edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi;
#define READ(target, a, d) port_call_with(&port, target, a, d, ebx, ecx, esi, edi, ebp)
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -4u, entry->ecx);
    port_set32(&port, ebp, -8u, entry->esi);
    port_set32(&port, ebp, -0xcu, entry->edi);
    port_set32(&port, ebp, -0x18u, stream);
    port_set32(&port, ebp, -0x24u, entry->ebx);
    esi = entry->esi;
    eax = READ(0x48aad0, stream, stream);
    esi = eax + 0x80;
    eax = READ(0x48aad0, vertrix_lift_edx, vertrix_lift_edx);
    edx = eax;
    ecx = 0x80;
    eax = READ(0x48aa70, port_u32(&port, ebp, -0x18u), edx);
    eax += vertrix_lift_edx;
    ebx = 1;
    port_set32(&port, ebp, -0x20u, eax - 0x300);
    READ(0x48a930, port_u32(&port, ebp, -0x18u), ebp - 0xac);
    port_set32(&port, ebp, -0x1cu, (uint32_t)(int32_t)(int16_t)port_u16(&port, ebp, -0xa4u) + 1);
    port_set32(&port, ebp, -0x2cu, (uint32_t)(int32_t)(int16_t)port_u16(&port, ebp, -0xa2u) + 1);
    port_set32(&port, ebp, -0x14u, port_u32(&port, ebp, -0x6au) - port_u32(&port, ebp, -0x1cu));
    eax = READ(0x48aaf0, port_u32(&port, ebp, -0x18u), esi);
    edx = vertrix_lift_edx;
    while (port_u32(&port, ebp, -0x2cu) != 0 && !port.env.failed)
    {
        esi = port_u32(&port, ebp, -0x1cu);
        while ((int32_t)esi > 0 && !port.env.failed)
        {
            ecx = 1;
            ebx = 1;
            READ(0x48a930, port_u32(&port, ebp, -0x18u), ebp - 0x10);
            edx = vertrix_lift_edx;
            eax = port_u8(&port, ebp, -0x10u);
            if ((int32_t)eax > 0xbf)
            {
                ecx = 1;
                port_set32(&port, ebp, -0x28u, eax - 0xc0);
                ebx = 1;
                eax = READ(0x48a930, port_u32(&port, ebp, -0x18u), ebp - 0x10);
                edx = vertrix_lift_edx;
                while (port_u32(&port, ebp, -0x28u) != 0 && !port.env.failed)
                {
                    esi--;
                    if ((int32_t)esi >= 0)
                    {
                        edi++;
                        eax = (eax & 0xffffff00u) | port_u8(&port, ebp, -0x10u);
                        port_set8(&port, edi, -1u, eax);
                    }
                    ebx = port_u32(&port, ebp, -0x28u) - 1;
                    port_set32(&port, ebp, -0x28u, ebx);
                }
            }
            else
            {
                edi++;
                esi--;
                port_set8(&port, edi, -1u, eax);
            }
        }
        if (esi == 0)
        {
            edx = port_u16(&port, ebp, -0x14u);
            eax = READ(0x48aa90, port_u32(&port, ebp, -0x18u), edx);
            edx = vertrix_lift_edx;
        }
        ecx = port_u32(&port, ebp, -0x2cu) - 1;
        port_set32(&port, ebp, -0x2cu, ecx);
    }
    if (port_u32(&port, ebp, -0x24u) == 0)
    {
        return port_return(&port, eax, edx);
    }
    READ(0x48aaf0, port_u32(&port, ebp, -0x18u), port_u32(&port, ebp, -0x20u));
    esi = 0;
    edi = 1;
    while ((esi & 0xffff) < 0x300 && !port.env.failed)
    {
        ecx = edi;
        ebx = edi;
        READ(0x48a930, port_u32(&port, ebp, -0x18u), ebp - 0x10);
        esi++;
        edx = port_u32(&port, ebp, -0x24u) + 1;
        port_set32(&port, ebp, -0x24u, edx);
        port_set8(&port, edx, -1u, port_u8(&port, ebp, -0x10u) >> 2);
    }
#undef READ
    return port_return(&port, esi & 0xffff, edx);
}

/* Original 0x4bb270 (one stack argument, the row count, counted down in place and popped): the
 * JPEG YCbCr rows of the decoder eax (the planes edx from row ebx) converted to RGB into the rows
 * ecx through the colour tables of +0x1c8 (+8 Cr to red, +0xc Cb to blue, +0x10/+0x14 the green
 * parts) and the range limit +0x144, +0x70 pixels a row. */
uint32_t vertrix_port_jpeg_ycc_rgb_convert_4bb270(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x44
    };
    Port port;
    uint8_t stack[BELOW + 8 + 4];
    uint32_t esp = entry->esp - BELOW;
    uint32_t decoder = entry->eax;
    uint32_t tables;
    uint32_t eax;
    uint32_t edx;
    port_open_arguments(&port, stack, calls, services, globals, entry, BELOW, 1);
    port_set32(&port, entry->esp, -4u, entry->esi);
    port_set32(&port, entry->esp, -8u, entry->edi);
    port_set32(&port, entry->esp, -0xcu, entry->ebp);
    port_set32(&port, esp, 0x18, entry->edx);
    port_set32(&port, esp, 0x10, entry->ebx);
    port_set32(&port, esp, 0x14, entry->ecx);
    edx = port_u32(&port, decoder, 0x70);
    port_set32(&port, esp, 0xc, edx);
    edx = port_u32(&port, decoder, 0x144);
    tables = port_u32(&port, decoder, 0x1c8);
    port_set32(&port, esp, 0x34, edx);
    port_set32(&port, esp, 0x2c, port_u32(&port, tables, 8));
    port_set32(&port, esp, 0x20, port_u32(&port, tables, 0xc));
    edx = port_u32(&port, tables, 0x10);
    eax = port_u32(&port, tables, 0x14);
    port_set32(&port, esp, 0x24, eax);
    eax = entry->ebx << 2;
    port_set32(&port, esp, 0x28, edx);
    port_set32(&port, esp, 0x1c, eax);
    while (!port.env.failed)
    {
        uint32_t row;
        uint32_t luma;
        uint32_t blue;
        uint32_t red;
        uint32_t end;
        uint32_t planes = port_u32(&port, esp, 0x18);
        edx = port_u32(&port, entry->esp, 4) - 1;
        port_set32(&port, entry->esp, 4, edx);
        if ((int32_t)edx < 0)
        {
            break;
        }
        row = port_u32(&port, esp, 0x1c);
        luma = port_u32(&port, port_u32(&port, planes, 0) + row, 0);
        blue = port_u32(&port, port_u32(&port, planes, 4) + row, 0);
        red = port_u32(&port, port_u32(&port, planes, 8) + row, 0);
        port_set32(&port, esp, 0x1c, row + 4);
        port_set32(&port, esp, 0x10, port_u32(&port, esp, 0x10) + 1);
        eax = port_u32(&port, port_u32(&port, esp, 0x14), 0);
        port_set32(&port, esp, 0x14, port_u32(&port, esp, 0x14) + 4);
        if (port_u32(&port, esp, 0xc) == 0)
        {
            continue;
        }
        end = port_u32(&port, esp, 0xc) + luma;
        port_set32(&port, esp, 0x30, end);
        do
        {
            uint32_t range = port_u32(&port, esp, 0x34);
            uint32_t y = port_u8(&port, luma, 0);
            uint32_t value;
            port_set32(&port, esp, 0, port_u8(&port, blue, 0));
            port_set32(&port, esp, 4, port_u8(&port, red, 0) << 2);
            value = port_u32(&port, port_u32(&port, esp, 0x2c) + port_u32(&port, esp, 4), 0) + y;
            port_set32(&port, esp, 8, value);
            port_set8(&port, eax, 0, port_u8(&port, range + value, 0));
            port_set32(&port, esp, 8, port_u32(&port, esp, 0) << 2);
            value = port_u32(&port, port_u32(&port, esp, 0x24) + port_u32(&port, esp, 8), 0) +
                    port_u32(&port, port_u32(&port, esp, 0x28) + port_u32(&port, esp, 4), 0);
            value = (uint32_t)((int32_t)value >> 16) + y + range;
            port_set8(&port, eax, 1, port_u8(&port, value, 0));
            value = port_u32(&port, port_u32(&port, esp, 0x20) + port_u32(&port, esp, 8), 0);
            port_set8(&port, eax, 2, port_u8(&port, y + value + range, 0));
            eax += 3;
            red++;
            luma++;
            blue++;
        } while (luma < port_u32(&port, esp, 0x30) && !port.env.failed);
    }
    return port_return(&port, eax, edx);
}
