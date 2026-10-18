#include "rtlbitmaps.h"

/* Bitmap files and filled rectangles. */

/* Original 0x473cf0: a 24-bit uncompressed bitmap read from the stream eax (opened by 0x48a8a0):
 * its 14-byte file header and 44-byte info header (0x48a930, at the start 0x48aad0 gives); any
 * other kind gives 0. A width by |height| picture of four bytes a pixel is made (0x478d10 with 4),
 * the pixel rows read from the data offset (0x48aaf0) three bytes a pixel with a 0 fourth, each
 * row's padding to four bytes skipped (0x48aa90), and the picture finished (0x479b50). eax the
 * picture. */
uint32_t vertrix_port_bitmap_load_473cf0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x7c
    };
    Port port;
    uint8_t stack[BELOW + 8];
    uint32_t ebp = entry->esp - 4;
    uint32_t stream = entry->eax;
    uint32_t esi;
    uint32_t eax;
    uint32_t edx;
    uint32_t ebx;
    uint32_t ecx;
    uint32_t height;
    uint32_t pad;
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -4u, entry->ebx);
    port_set32(&port, ebp, -8u, entry->ecx);
    port_set32(&port, ebp, -0xcu, entry->edx);
    port_set32(&port, ebp, -0x10u, entry->esi);
    port_set32(&port, ebp, -0x14u, entry->edi);
#define CALL(target, a, d) port_call_with(&port, target, a, d, ebx, ecx, esi, stream, ebp)
    ebx = entry->ebx;
    ecx = entry->ecx;
    esi = entry->esi;
    CALL(0x48a8a0, stream, entry->edx);
    ecx = 0xe;
    ebx = 1;
    esi = CALL(0x48aad0, stream, ebp - 0x4c);
    CALL(0x48a930, stream, ebp - 0x4c);
    port_set32(&port, ebp, -0x30u, port_u32(&port, ebp, -0x42u) + esi);
    ecx = 0x2c;
    ebx = 1;
    CALL(0x48a930, stream, ebp - 0x78);
    if (port_u32(&port, ebp, -0x78u) != 0x28 || port_u16(&port, ebp, -0x6cu) != 1 ||
        port_u16(&port, ebp, -0x6au) != 0x18 || port_u32(&port, ebp, -0x68u) != 0)
    {
        return port_return(&port, 0, entry->edx);
    }
    ecx = 0;
    port_set32(&port, ebp, -0x28u, port_u32(&port, ebp, -0x74u));
    height = port_u32(&port, ebp, -0x70u);
    if ((int32_t)height < 0)
    {
        height = 0u - height;
    }
    port_set32(&port, ebp, -0x38u, height);
    ebx = 4;
    eax = CALL(0x478d10, port_u32(&port, ebp, -0x28u), height);
    port_set32(&port, ebp, -0x3cu, eax);
    esi = port_u32(&port, eax, 0);
    pad = 4 - ((port_u32(&port, ebp, -0x28u) * 3) & 3);
    if (pad == 4)
    {
        pad = ecx;
    }
    port_set32(&port, ebp, -0x2cu, pad);
    port_set8(&port, ebp, -0x20u, pad);
    port_set32(&port, ebp, -0x34u, 0);
    ecx = height;
    CALL(0x48aaf0, stream, port_u32(&port, ebp, -0x30u));
    edx = vertrix_lift_edx;
    if (height != 0)
    {
        do
        {
            ecx = 0;
            ebx = port_u32(&port, ebp, -0x28u);
            port_set32(&port, ebp, -0x2cu, 0);
            if (ebx != 0)
            {
                do
                {
                    ecx = 1;
                    ebx = 1;
                    CALL(0x48a930, stream, ebp - 0x1c);
                    CALL(0x48a930, stream, ebp - 0x24);
                    esi++;
                    CALL(0x48a930, stream, ebp - 0x18);
                    port_set8(&port, esi, -1u, port_u8(&port, ebp, -0x1cu));
                    esi++;
                    port_set8(&port, esi, -1u, port_u8(&port, ebp, -0x24u));
                    esi++;
                    port_set8(&port, esi, -1u, port_u8(&port, ebp, -0x18u));
                    port_set8(&port, esi, 0, 0);
                    esi++;
                    port_set32(&port, ebp, -0x2cu, port_u32(&port, ebp, -0x2cu) + 1);
                } while (port_u32(&port, ebp, -0x2cu) < port_u32(&port, ebp, -0x28u) &&
                         !port.env.failed);
            }
            ebx = port_u32(&port, ebp, -0x34u);
            CALL(0x48aa90, stream, port_u8(&port, ebp, -0x20u));
            ebx++;
            edx = port_u32(&port, ebp, -0x38u);
            port_set32(&port, ebp, -0x34u, ebx);
        } while (ebx < edx && !port.env.failed);
    }
    CALL(0x479b50, port_u32(&port, ebp, -0x3cu), edx);
#undef CALL
    return port_return(&port, port_u32(&port, ebp, -0x3cu), entry->edx);
}

/* Original 0x47c3b0 (two stack arguments, popped: the row count, counted down in place, and the
 * colour): an ecx-wide rectangle of the surface eax from its point edx filled with the colour
 * mapped by 0x479a40, from the address 0x478eb0 gives (kept at 0x558b80): by bytes, words (the
 * walk at 0x558b78) or dwords (0x558b7c) by the depth +0xc (kept at 0x558b70), the row skip at
 * 0x558b68; the walk left at 0x558b74/0x558b64. */
uint32_t vertrix_port_surface_fill_rect_47c3b0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x18
    };
    Port port;
    uint8_t stack[BELOW + 8 + 2 * 4];
    uint32_t ebp = entry->esp - 4;
    uint32_t surface = entry->eax;
    uint32_t width = entry->ecx;
    uint32_t esi;
    uint32_t edi;
    uint32_t eax;
    uint32_t edx;
    uint32_t colour;
    uint32_t depth;
    uint32_t rows;
    port_open_arguments(&port, stack, calls, services, globals, entry, BELOW, 2);
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -4u, entry->esi);
    port_set32(&port, ebp, -8u, entry->edi);
    esi = port_u32(&port, 0, 0x558b64);
    edi = port_u32(&port, 0, 0x558b74);
    port_set32(&port, ebp, -0x10u, surface);
    port_set32(&port, ebp, -0x14u, entry->edx);
    port_set32(&port, ebp, -0xcu, width);
    colour = port_u32(&port, entry->esp, 8);
    port_set8(&port, 0, 0x558b70, port_u8(&port, surface, 0xc));
    colour = port_call_with(&port, 0x479a40, surface, colour, entry->ebx, colour, esi, edi, ebp);
    eax = port_call_with(&port, 0x478eb0, surface, port_u32(&port, ebp, -0x14u), entry->ebx, colour,
                         esi, edi, ebp);
    depth = port_u8(&port, 0, 0x558b70);
    edx = (vertrix_lift_edx & 0xffffff00u) | depth;
    port_set32(&port, 0, 0x558b80, eax);
    rows = port_u32(&port, entry->esp, 4);
    if (depth == 1)
    {
        edi = eax;
        edx = width;
        eax = port_u32(&port, surface, 0x14) - width;
        esi = port_u32(&port, 0, 0x558b64);
        port_set32(&port, 0, 0x558b68, eax);
        if (rows != 0)
        {
            do
            {
                for (esi = width; esi != 0 && !port.env.failed; esi--)
                {
                    edi++;
                    port_set8(&port, edi, -1u, colour);
                }
                edi += port_u32(&port, 0, 0x558b68);
                eax = port_u32(&port, entry->esp, 4) - 1;
                port_set32(&port, entry->esp, 4, eax);
            } while (eax != 0 && !port.env.failed);
        }
    }
    else
    {
        edi = port_u32(&port, 0, 0x558b74);
        esi = port_u32(&port, 0, 0x558b64);
        if (depth == 2)
        {
            port_set32(&port, 0, 0x558b78, eax);
            edx = width * 2;
            eax = port_u32(&port, surface, 0x14) - edx;
            port_set32(&port, 0, 0x558b68, eax);
            if (rows != 0)
            {
                do
                {
                    for (esi = width; esi != 0 && !port.env.failed; esi--)
                    {
                        eax = port_u32(&port, 0, 0x558b78) + 2;
                        port_set16(&port, eax, -2u, colour);
                        port_set32(&port, 0, 0x558b78, eax);
                    }
                    edx = port_u32(&port, 0, 0x558b68);
                    port_set32(&port, 0, 0x558b78, port_u32(&port, 0, 0x558b78) + edx);
                    eax = port_u32(&port, entry->esp, 4) - 1;
                    port_set32(&port, entry->esp, 4, eax);
                } while (eax != 0 && !port.env.failed);
            }
        }
        else if (depth == 4)
        {
            port_set32(&port, 0, 0x558b7c, eax);
            eax = port_u32(&port, surface, 0x14) - (width << 2);
            edx = rows;
            port_set32(&port, 0, 0x558b68, eax);
            if (rows != 0)
            {
                do
                {
                    for (esi = width; esi != 0 && !port.env.failed; esi--)
                    {
                        eax = port_u32(&port, 0, 0x558b7c) + 4;
                        port_set32(&port, eax, -4u, colour);
                        port_set32(&port, 0, 0x558b7c, eax);
                    }
                    edx = port_u32(&port, 0, 0x558b68);
                    port_set32(&port, 0, 0x558b7c, port_u32(&port, 0, 0x558b7c) + edx);
                    eax = port_u32(&port, entry->esp, 4) - 1;
                    port_set32(&port, entry->esp, 4, eax);
                } while (eax != 0 && !port.env.failed);
            }
        }
    }
    port_set32(&port, 0, 0x558b74, edi);
    port_set32(&port, 0, 0x558b64, esi);
    return port_return(&port, eax, edx);
}
