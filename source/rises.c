#include "rises.h"

/* The rising pieces. */

/* Original 0x458a70: the rising piece eax when due (0x4ac500, 0x4ac520) takes its stride
 * (0x4ac540, 0x4ac5b0), moves (0x4ad060) and is placed (0x4ad260 into ebp-0x18 and ebp-0x14);
 * its depth +0x44 is 0x10 less 16 parts of 0xa0 of its height +0x28 (0 to 0x10), or 0 with
 * +0x48 0 past 0xa0; it is centred on its place by its size (0x4b14c0), its turn steps by the
 * stride (+0x2a, +0x64 0) unless 0x4ad750 holds it, it bobs (0x4ad530) and, with no depth left,
 * takes the state 0 (0x4ac8f0). The registers but eax kept. */
uint32_t vertrix_port_piece_rise_458a70(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x24
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t piece = entry->eax;
    uint32_t edi = entry->edi;
    uint32_t stride;
    uint32_t height;
    uint32_t depth;
    uint32_t edx;
    uint32_t eax;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, -4u, entry->ebx);
    port_set32(&port, ebp, -8u, entry->ecx);
    port_set32(&port, ebp, -0xcu, entry->edx);
    port_set32(&port, ebp, -0x10u, entry->esi);
    port_call_with(&port, 0x4ac500, piece, entry->edx, entry->ebx, piece, entry->esi, edi, ebp);
    eax = port_call_with(&port, 0x4ac520, piece, vertrix_lift_edx, entry->ebx, piece, entry->esi,
                         edi, ebp);
    if (eax != 1)
    {
        return port_return(&port, eax, entry->edx);
    }
    stride = port_call_with(&port, 0x4ac540, piece, vertrix_lift_edx, entry->ebx, piece, entry->esi,
                            edi, ebp);
    port_call_with(&port, 0x4ac5b0, piece, stride, entry->ebx, piece, stride, edi, ebp);
    port_call_with(&port, 0x4ad060, piece, vertrix_lift_edx, ebp - 0x14, piece, stride, edi, ebp);
    port_call_with(&port, 0x4ad260, piece, ebp - 0x18, ebp - 0x14, piece, stride, edi, ebp);
    height = (uint32_t)((int32_t)port_u32(&port, piece, 0x28) >> 16);
    if (height <= 0xa0)
    {
        depth = 0x10 - (height << 4) / 0xa0;
        port_set8(&port, piece, 0x44, (int32_t)depth >= 0x10 ? 0x10 : depth);
        depth = port_u8(&port, piece, 0x44);
        port_set8(&port, piece, 0x44, depth);
    }
    else
    {
        port_set8(&port, piece, 0x44, 0);
        port_set16(&port, piece, 0x48, 0);
    }
    port_set32(&port, ebp, -0x20u, 0);
    port_set32(&port, ebp, -0x1cu, 0);
    port_call_with(&port, 0x4b14c0, piece, ebp - 0x20, ebp - 0x1c, piece, stride, edi, ebp);
    port_set16(&port, piece, 0xe,
               (uint32_t)(int32_t)(int16_t)port_u16(&port, ebp, -0x18u) -
                   (port_u32(&port, ebp, -0x20u) >> 1));
    edx = (uint32_t)(int32_t)(int16_t)port_u16(&port, ebp, -0x14u) -
          (port_u32(&port, ebp, -0x1cu) >> 1);
    port_set16(&port, piece, 0x16, edx);
    if (port_call_with(&port, 0x4ad750, piece, stride, ebp - 0x1c, piece, stride, edi, ebp) == 0)
    {
        port_set32(&port, piece, 0x64, 0);
        port_set16(&port, piece, 0x2a, port_u16(&port, piece, 0x2a) + stride);
    }
    eax = port_call_with(&port, 0x4ad530, piece, stride, ebp - 0x1c, piece, stride, edi, ebp);
    if (port_u8(&port, piece, 0x44) == 0)
    {
        eax = port_call_with(&port, 0x4ac8f0, piece, 0, ebp - 0x1c, piece, stride, edi, ebp);
    }
    return port_return(&port, eax, entry->edx);
}
