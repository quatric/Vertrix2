#include "port_imagebounds.h"

/* The actor image bounds. */

/* `cdq; idiv divisor`: the quotient and remainder, both unchanged when it would fault. */
static void divide(uint32_t dividend, uint32_t divisor, uint32_t *eax, uint32_t *edx)
{
    LiftFlags flags = {0, 0, 0, 0, 0, 0};
    *eax = dividend;
    *edx = (uint32_t)((int32_t)dividend >> 31);
    lift_idiv1(32, divisor, eax, edx, &flags);
}

static uint32_t sign16(uint32_t value)
{
    return (uint32_t)(int32_t)(int16_t)value;
}

/* Original 0x4b15e0: the image of the actor eax (its frame +0xb4, kept in 0x5bb734, gives the
 * flag +0x27 to 0x5bb731, the size +4/+8 and the offset +0xc/+0x10; without one the size is
 * +0xf4/+0xf8 and the offset 0) is scaled by 0x5bb738: 0x10, or with +0x91 set the byte +0x221
 * of 0x544070 unless its +0x220 is set, otherwise the actor's +0x44. A scale other than 0x10
 * takes the size from the table 0x5c1b00 (16 bytes a scale) and the offset in proportion. The
 * width and height go to [ecx] and the stack argument (and 0x5bb74c, 0x5bb74e; the height
 * before scaling to 0x5bb7b6), the place +0xe/+0x16 less the offset to [edx] and [ebx]; eax 1. */
uint32_t vertrix_port_actor_image_bounds_4b15e0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0
    };
    Port port;
    uint8_t stack[BELOW + 8 + 4];
    uint32_t actor = entry->eax;
    uint32_t frame;
    uint32_t edi = entry->edi;
    uint32_t ebx = entry->ebx;
    uint32_t ecx;
    uint32_t eax;
    uint32_t edx;
    uint32_t width;
    uint32_t height;
    uint32_t scale;
    uint32_t board;
    port_open_arguments(&port, stack, calls, services, globals, entry, BELOW, 1);
    frame = port_u32(&port, actor, 0xb4);
    port_set32(&port, 0, 0x5bb734, frame);
    if (frame != 0)
    {
        port_set8(&port, 0, 0x5bb731, port_u8(&port, frame, 0x27));
        edi = (edi & 0xffff0000u) | port_u16(&port, frame, 8);
        port_set16(&port, 0, 0x5bb7b4, port_u16(&port, frame, 4));
        port_set16(&port, 0, 0x5bb7b0, port_u16(&port, frame, 0xc));
        port_set16(&port, 0, 0x5bb7b2, port_u16(&port, frame, 0x10));
    }
    else
    {
        edi = (edi & 0xffff0000u) | port_u16(&port, actor, 0xf8);
        port_set16(&port, 0, 0x5bb7b4, port_u16(&port, actor, 0xf4));
        port_set16(&port, 0, 0x5bb7b0, 0);
        port_set16(&port, 0, 0x5bb7b2, 0);
    }
    port_set8(&port, 0, 0x5bb738, 0x10);
    if (port_u8(&port, actor, 0x91) != 0)
    {
        board = port_u32(&port, 0, 0x544070);
        if (port_u8(&port, board, 0x220) == 0)
        {
            port_set8(&port, 0, 0x5bb738, port_u8(&port, board, 0x221));
        }
    }
    else
    {
        port_set8(&port, 0, 0x5bb738, port_u8(&port, actor, 0x44));
    }
    scale = port_u8(&port, 0, 0x5bb738);
    if (scale == 0x10)
    {
        ecx = (entry->ecx & 0xffff0000u) | port_u16(&port, 0, 0x5bb7b4);
        ebx = edi;
    }
    else
    {
        width = port_u16(&port, 0, 0x5bb7b4);
        height = edi & 0xffff;
        ecx = (width >> 4) * scale +
              ((ebx & 0xffff0000u) | port_u8(&port, 0, 0x5c1b00 + scale * 0x10 + (width & 0xf)));
        ebx = scale * (height >> 4) + port_u8(&port, 0, 0x5c1b00 + scale * 0x10 + (height & 0xf));
        divide(sign16(ecx) * sign16(port_u16(&port, 0, 0x5bb7b0)), width, &eax, &edx);
        port_set16(&port, 0, 0x5bb7b0, eax);
        divide(sign16(ebx) * sign16(port_u16(&port, 0, 0x5bb7b2)), height, &eax, &edx);
        port_set16(&port, 0, 0x5bb7b2, eax);
    }
    port_set32(&port, entry->ecx, 0, sign16(ecx));
    port_set32(&port, port_u32(&port, entry->esp, 4), 0, sign16(ebx));
    port_set32(&port, entry->edx, 0,
               sign16(port_u16(&port, actor, 0xe)) - sign16(port_u16(&port, 0, 0x5bb7b0)));
    edx = sign16(port_u16(&port, actor, 0x16)) - sign16(port_u16(&port, 0, 0x5bb7b2));
    port_set32(&port, entry->ebx, 0, edx);
    port_set16(&port, 0, 0x5bb7b6, edi);
    port_set16(&port, 0, 0x5bb74c, ecx);
    port_set16(&port, 0, 0x5bb74e, ebx);
    return port_return(&port, 1, edx);
}
