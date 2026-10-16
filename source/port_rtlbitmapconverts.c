#include "port_rtlbitmapconverts.h"

/* Bitmap files read into a pixel format. */

/* A call (with count stack arguments, nearest first) that leaves its eax and edx in *eax and
 * *edx; the eax. */
static uint32_t convert_call(Port *port, uint32_t *eax, uint32_t *edx, uint32_t target, uint32_t a,
                             uint32_t d, uint32_t ebx, uint32_t ecx, uint32_t esi, uint32_t edi,
                             uint32_t ebp, const uint32_t *stack, unsigned count)
{
    vertrix_lift_in_esi = esi;
    vertrix_lift_in_edi = edi;
    vertrix_lift_in_ebp = ebp;
    *eax = lift_call_arguments(&port->env, target, a, d, ebx, ecx, stack, count);
    vertrix_lift_in_esi = vertrix_lift_in_edi = vertrix_lift_in_ebp = 0;
    *edx = vertrix_lift_edx;
    return *eax;
}

/* Original 0x4741a0 (guarded 0x5163e8): a 24-bit uncompressed bitmap read from the stream eax
 * into the pixel format edx (its depth +0, its kind +0x14): an RGB 8:8:8 source format made at
 * ebp-0xa8 (0x481b20, 0x481bc0 with the masks 0xff0000, 0xff00, 0xff and 0xff000000; failing it
 * gives 0). The file header (14 bytes, at the start 0x48aad0 gives) and info header (44) read
 * (0x48a930); any other kind gives 0. A width by |height| picture of the depth made (0x478d10),
 * its +0xd the kind; from the data offset (0x48aaf0) each pixel's three bytes read, made a colour
 * and converted (0x481d90) and written as 1, 2, 3 (high byte first) or 4 bytes by the depth,
 * each row's padding to four skipped (0x48aa90); the picture finished (0x479b50). The source
 * format freed (0x481b30). eax the picture or 0. */
uint32_t vertrix_port_bitmap_load_convert_4741a0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0xd8
    };
    Port port;
    uint8_t stack[BELOW + 8];
    uint32_t ebp = entry->esp - 4;
    uint32_t record = ebp - 0x7c;
    uint32_t source = ebp - 0xa8;
    uint32_t stream = entry->eax;
    uint32_t format = entry->edx;
    uint32_t eax;
    uint32_t edx = 0x4ec1ec;
    uint32_t ebx = 0;
    uint32_t ecx = 0x5163e8;
    uint32_t esi = 1;
    uint32_t mask = 0xff000000u;
    uint32_t width;
    uint32_t height;
    uint32_t pad;
    uint32_t picture;
    uint32_t depth;
#define CALL(target, a, d)                                                                         \
    convert_call(&port, &eax, &edx, target, a, d, ebx, ecx, esi, stream, ebp, NULL, 0)
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -4u, entry->ebx);
    port_set32(&port, ebp, -8u, entry->ecx);
    port_set32(&port, ebp, -0xcu, entry->esi);
    port_set32(&port, ebp, -0x10u, entry->edi);
    port_set32(&port, ebp, -0x28u, format);
    port_set32(&port, record, 0, port.env.chain);
    port.env.chain = record;
    port_set32(&port, ebp, -0x78u, edx);
    port_set32(&port, ebp, -0x74u, ecx);
    port_set32(&port, ebp, -0x70u, ebx);
    CALL(0x481b20, source, edx);
    ecx = 0xff;
    ebx = 0xff00;
    port_set32(&port, ebp, -0x70u, esi);
    if (convert_call(&port, &eax, &edx, 0x481bc0, source, 0xff0000, ebx, ecx, esi, stream, ebp,
                     &mask, 1) == 0)
    {
        goto fail;
    }
    ecx = 0xe;
    ebx = 1;
    port_set8(&port, ebp, -0x14u, port_u8(&port, format, 0));
    esi = CALL(0x48aad0, stream, ebp - 0x68);
    CALL(0x48a930, stream, edx);
    port_set32(&port, ebp, -0x30u, port_u32(&port, ebp, -0x5eu) + esi);
    ecx = 0x2c;
    ebx = 1;
    CALL(0x48a930, stream, ebp - 0xd4);
    if (port_u32(&port, ebp, -0xd4u) != 0x28 || port_u16(&port, ebp, -0xc8u) != 1 ||
        port_u16(&port, ebp, -0xc6u) != 0x18 || port_u32(&port, ebp, -0xc4u) != 0)
    {
        goto fail;
    }
    width = port_u32(&port, ebp, -0xd0u);
    port_set32(&port, ebp, -0x2cu, width);
    height = port_u32(&port, ebp, -0xccu);
    if ((int32_t)height < 0)
    {
        height = 0u - height;
    }
    port_set32(&port, ebp, -0x58u, height);
    ebx = port_u8(&port, ebp, -0x14u);
    picture = CALL(0x478d10, width, height);
    port_set32(&port, ebp, -0x34u, picture);
    port_set8(&port, picture, 0xd, port_u8(&port, format, 0x14));
    port_set32(&port, ebp, -0x38u, picture);
    esi = port_u32(&port, picture, 0);
    port_set32(&port, ebp, -0x4cu, esi);
    port_set32(&port, ebp, -0x54u, esi);
    port_set32(&port, ebp, -0x50u, esi);
    pad = 4 - ((width * 3) & 3);
    port_set32(&port, ebp, -0x48u, pad);
    if (pad == 4)
    {
        ebx = 0;
        pad = 0;
        port_set32(&port, ebp, -0x48u, 0);
    }
    port_set8(&port, ebp, -0x24u, pad);
    port_set32(&port, ebp, -0x3cu, 0);
    CALL(0x48aaf0, stream, port_u32(&port, ebp, -0x30u));
    if (height != 0)
    {
        do
        {
            port_set32(&port, ebp, -0x40u, ebp - 0x43);
            port_set32(&port, ebp, -0x48u, 0);
            if (port_u32(&port, ebp, -0x2cu) != 0)
            {
                do
                {
                    ecx = 1;
                    ebx = 1;
                    CALL(0x48a930, stream, ebp - 0x18);
                    CALL(0x48a930, stream, ebp - 0x1c);
                    CALL(0x48a930, stream, ebp - 0x20);
                    port_set8(&port, ebp, -0x44u, port_u8(&port, ebp, -0x18u));
                    port_set8(&port, ebp, -0x43u, port_u8(&port, ebp, -0x1cu));
                    port_set8(&port, ebp, -0x41u, 0);
                    port_set8(&port, ebp, -0x42u, port_u8(&port, ebp, -0x20u));
                    ebx = port_u32(&port, ebp, -0x44u);
                    CALL(0x481d90, source, port_u32(&port, ebp, -0x28u));
                    depth = port_u8(&port, ebp, -0x14u);
                    edx = (edx & 0xffffff00u) | depth;
                    port_set32(&port, ebp, -0x44u, eax);
                    if (depth == 1)
                    {
                        edx = port_u32(&port, ebp, -0x4cu);
                        ecx = edx + 1;
                        port_set8(&port, edx, 0, eax);
                        port_set32(&port, ebp, -0x4cu, ecx);
                    }
                    else if (depth == 2)
                    {
                        edx = port_u32(&port, ebp, -0x54u) + 2;
                        port_set16(&port, edx, -2u, eax);
                        port_set32(&port, ebp, -0x54u, edx);
                    }
                    else if (depth == 3)
                    {
                        port_set8(&port, esi, 0, (eax & 0xff0000) >> 16);
                        eax = port_u16(&port, ebp, -0x44u) >> 8;
                        port_set8(&port, esi, 1, eax);
                        eax = (eax & 0xffffff00u) | port_u8(&port, ebp, -0x44u);
                        port_set8(&port, esi, 2, eax);
                        esi += 3;
                    }
                    else if (depth == 4)
                    {
                        edx = port_u32(&port, ebp, -0x50u);
                        port_set32(&port, edx, 0, eax);
                        eax = edx + 4;
                        port_set32(&port, ebp, -0x50u, eax);
                    }
                    ecx = port_u32(&port, ebp, -0x48u) + 1;
                    ebx = port_u32(&port, ebp, -0x2cu);
                    port_set32(&port, ebp, -0x48u, ecx);
                } while (ecx < ebx && !port.env.failed);
            }
            ecx = port_u32(&port, ebp, -0x3cu) + 1;
            ebx = port_u32(&port, ebp, -0x58u);
            CALL(0x48aa90, stream, port_u8(&port, ebp, -0x24u));
            port_set32(&port, ebp, -0x3cu, ecx);
        } while (ecx < ebx && !port.env.failed);
    }
    ebx = port_u32(&port, ebp, -0x38u);
    CALL(0x479b50, port_u32(&port, ebp, -0x34u), edx);
    esi = 0;
    port_set32(&port, ebp, -0x70u, 0);
    CALL(0x481b30, source, 0);
    port_set32(&port, ebp, -0x70u, 0);
    port.env.chain = port_u32(&port, record, 0);
    return port_return(&port, ebx, edx);
fail:
    CALL(0x481b30, source, 0);
#undef CALL
    port.env.chain = port_u32(&port, record, 0);
    return port_return(&port, 0, edx);
}
