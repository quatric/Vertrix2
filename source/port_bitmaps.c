#include "port_bitmaps.h"

/* The surface saved as a bitmap file. */

/* One byte `value` into the buffer at ebp-0xd0 at the count ebp-0x30, which steps; then the
 * buffer's turn (0x474540 with the stream `stream`). Returns that call's eax. */
static uint32_t bitmap_put(Port *port, uint32_t stream, uint32_t value, uint32_t ecx, uint32_t esi,
                           uint32_t ebp)
{
    uint32_t count = port_u32(port, ebp, -0x30u);
    port_set8(port, count, ebp - 0xd0, value);
    port_set32(port, ebp, -0x30u, count + 1);
    return port_call_with(port, 0x474540, stream, ebp - 0xd0, ebp - 0x30, ecx, esi, stream, ebp);
}

/* Original 0x473fc0: the surface edx written to the stream eax as a 24 bit bitmap: the file
 * header (0xe bytes at ebp-0x40, 'BM', the size the rows' 3 bytes a pixel times the height, the
 * offset 0x3a) and the information (0x2c bytes at ebp-0x6c: 0x28, the width +4, the height +8, 1
 * plane, 0x18 bits), both cleared first (0x4eb5c0) and written (0x489170); then the rows bottom
 * up (0x479b30), each pixel's three bytes in the order of the bytes of 0x4fd6d4 and each row's
 * pad to 4 taken past its end, through the buffer (bitmap_put), whose rest is written last. eax
 * is the last buffer turn's (0 for a row without pad, the height less 1 for none) or the last
 * write's, edx the rest's count or that write's; ebx, ecx, esi and edi kept. */
uint32_t vertrix_port_surface_save_bitmap_473fc0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0xd4
    };
    Port port;
    uint8_t stack[BELOW + 8];
    uint32_t ebp = entry->esp - 4;
    uint32_t stream = entry->eax;
    uint32_t surface = entry->edx;
    uint32_t width;
    uint32_t height;
    uint32_t stride;
    uint32_t pad;
    uint32_t row;
    uint32_t pixel;
    uint32_t cell;
    uint32_t count;
    uint32_t eax;
    uint32_t esi = entry->esi;
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -4u, entry->ebx);
    port_set32(&port, ebp, -8u, entry->ecx);
    port_set32(&port, ebp, -0xcu, entry->esi);
    port_set32(&port, ebp, -0x10u, entry->edi);
    port_set32(&port, ebp, -0x1cu, surface);
    port_set32(&port, ebp, -0x24u, port_u32(&port, 0, 0x4fd6d4));
    port_set32(&port, ebp, -0x30u, 0);
    port_call_with(&port, 0x4eb5c0, ebp - 0x6c, 0, 0x2c, entry->ecx, esi, stream, ebp);
    port_call_with(&port, 0x4eb5c0, ebp - 0x40, 0, 0xe, 0x3a, esi, stream, ebp);
    port_set32(&port, ebp, -0x36u, 0x3a);
    port_set16(&port, ebp, -0x40u, 0x4d42);
    width = port_u32(&port, surface, 4);
    port_set32(&port, ebp, -0x18u, width);
    height = port_u32(&port, surface, 8);
    port_set32(&port, ebp, -0x20u, height);
    port_set16(&port, ebp, -0x5eu, 0x18);
    port_set32(&port, ebp, -0x54u, 0);
    port_set32(&port, ebp, -0x50u, 0);
    port_set32(&port, ebp, -0x5cu, 0);
    port_set32(&port, ebp, -0x68u, width);
    port_set32(&port, ebp, -0x64u, height);
    port_set32(&port, ebp, -0x6cu, 0x28);
    stride = width * 3;
    port_set32(&port, ebp, -0x3eu, height * stride);
    port_set16(&port, ebp, -0x60u, 1);
    pad = 4 - (stride & 3);
    if (pad == 4)
    {
        pad = 0;
    }
    port_set32(&port, ebp, -0x28u, pad);
    port_set8(&port, ebp, -0x14u, pad);
    port_call_with(&port, 0x489170, stream, ebp - 0x40, 1, 0xe, esi, stream, ebp);
    port_call_with(&port, 0x489170, stream, ebp - 0x6c, 1, 0x2c, esi, stream, ebp);
    row = height - 1;
    port_set32(&port, ebp, -0x30u, 0);
    port_set32(&port, ebp, -0x2cu, row);
    eax = row;
    cell = 0x2c;
    while ((int32_t)row >= 0)
    {
        cell = port_call_with(&port, 0x479b30, surface, 0, row, cell, esi, stream, ebp);
        port_set32(&port, ebp, -0x28u, 0);
        width = port_u32(&port, ebp, -0x18u);
        for (pixel = 0; pixel < width;)
        {
            for (esi = 0; esi < 3;)
            {
                uint32_t value = port_u8(&port, cell, port_u8(&port, esi, ebp - 0x24));
                esi++;
                bitmap_put(&port, stream, value, cell, esi, ebp);
            }
            pixel = port_u32(&port, ebp, -0x28u) + 1;
            cell += 4;
            port_set32(&port, ebp, -0x28u, pixel);
            width = port_u32(&port, ebp, -0x18u);
        }
        eax = 0;
        port_set32(&port, ebp, -0x28u, 0);
        while ((int32_t)port_u8(&port, ebp, -0x14u) > (int32_t)port_u32(&port, ebp, -0x28u))
        {
            eax = bitmap_put(&port, stream, port_u8(&port, cell, port_u8(&port, esi, ebp - 0x24)),
                             cell, esi, ebp);
            port_set32(&port, ebp, -0x28u, port_u32(&port, ebp, -0x28u) + 1);
        }
        row = port_u32(&port, ebp, -0x2cu) - 1;
        port_set32(&port, ebp, -0x2cu, row);
    }
    count = port_u32(&port, ebp, -0x30u);
    if (count != 0)
    {
        eax = port_call_with(&port, 0x489170, stream, ebp - 0xd0, 1, count, esi, stream, ebp);
        return port_return(&port, eax, vertrix_lift_edx);
    }
    return port_return(&port, eax, count);
}
