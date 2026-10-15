#include "port_bounces.h"

/* The bouncing pieces. */

/* The piece's way word at `way` and its speed word after it, moved by `step` with the stride
 * at 0x5448ec: a negative way is set aside (at 0x5448e8) with the speed turned in `scratch`
 * while it moves, then restored with the speed turned back in `turned`, as the original turns
 * them in its registers. */
static void bounce_axis(Port *port, uint32_t piece, uint32_t way, uint32_t step, uint32_t *scratch,
                        uint32_t *turned, uint32_t ebx, const uint32_t *esi, uint32_t edi,
                        uint32_t ebp)
{
    if ((int32_t)port_u32(port, piece, way) >> 16 >= 0)
    {
        port_call_with(port, step, piece, port_u32(port, 0, 0x5448ec), ebx, piece, *esi, edi, ebp);
        return;
    }
    port_set16(port, 0, 0x5448e8, port_u16(port, piece, way));
    *scratch = 0u - ((*scratch & 0xffff0000u) | port_u16(port, piece, way + 2));
    port_set16(port, piece, way + 2, *scratch);
    port_set16(port, piece, way, 0);
    port_call_with(port, step, piece, port_u32(port, 0, 0x5448ec), ebx, piece, *esi, edi, ebp);
    *turned = 0u - ((*turned & 0xffff0000u) | port_u16(port, piece, way + 2));
    port_set16(port, piece, way, port_u16(port, 0, 0x5448e8));
    port_set16(port, piece, way + 2, *turned);
}

/* Original 0x443890: a bouncing piece eax's frame: 0x5448e4 set; moved (0x4ac500, 0x4ac600)
 * and, when 0x4ac620 answers its edx, its stride (0x4ac640, kept at 0x5448ec) taken across
 * (0x4ac6b0) and down (0x4ad5e0 of +0x30, 0x4ad630 of +0x40, a negative way set aside while its
 * speed is turned); when it lands (0x4ac520 gives 1) its stride (0x4ac540, 0x4ac5b0) bounces it
 * (0x4ace40 into 0x5448e4, 0x4ad110); placed (0x4ad2c0 into 0x5448d4 and 0x5448d6, copied to
 * +0xe and +0x16), its height +0x28 (0x5448dc) against its reach +0x2e plus +0x3e (0x5448d8)
 * gives +0x44: 0x10 up to 0x28, 8 at the reach, between them 0x10 less 8 parts of the way
 * (0x5448e0) held from 8 to 0x10; with 0x5448e4 clear, +0x45 0, +0x46 1 and the state 0x443ab0
 * (0x4ac8f0). The registers but eax kept. */
uint32_t vertrix_port_piece_bounce_443890(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x14
    };
    Port port;
    uint32_t piece = entry->eax;
    uint32_t ebp = entry->ebp;
    uint32_t ebx = entry->ebx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t stride;
    uint32_t edx;
    uint32_t height;
    uint32_t reach;
    uint32_t level;
    uint32_t eax;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, entry->esp, -4u, entry->ebx);
    port_set32(&port, entry->esp, -8u, entry->ecx);
    port_set32(&port, entry->esp, -0xcu, entry->edx);
    port_set32(&port, entry->esp, -0x10u, entry->esi);
    port_set32(&port, entry->esp, -0x14u, entry->edi);
    port_set32(&port, 0, 0x5448e4, 1);
    port_call_with(&port, 0x4ac500, piece, 1, ebx, piece, esi, edi, ebp);
    port_call_with(&port, 0x4ac600, piece, vertrix_lift_edx, ebx, piece, esi, edi, ebp);
    eax = port_call_with(&port, 0x4ac620, piece, vertrix_lift_edx, ebx, piece, esi, edi, ebp);
    if (eax == vertrix_lift_edx)
    {
        stride =
            port_call_with(&port, 0x4ac640, piece, vertrix_lift_edx, ebx, piece, esi, edi, ebp);
        port_set32(&port, 0, 0x5448ec, stride);
        port_call_with(&port, 0x4ac6b0, piece, vertrix_lift_edx, ebx, piece, esi, edi, ebp);
        edx = vertrix_lift_edx;
        bounce_axis(&port, piece, 0x30, 0x4ad5e0, &edx, &ebx, ebx, &esi, edi, ebp);
        bounce_axis(&port, piece, 0x40, 0x4ad630, &esi, &edi, ebx, &esi, edi, ebp);
    }
    if (port_call_with(&port, 0x4ac520, piece, vertrix_lift_edx, ebx, piece, esi, edi, ebp) == 1)
    {
        stride =
            port_call_with(&port, 0x4ac540, piece, vertrix_lift_edx, ebx, piece, esi, edi, ebp);
        port_set32(&port, 0, 0x5448ec, stride);
        port_call_with(&port, 0x4ac5b0, piece, vertrix_lift_edx, ebx, piece, esi, edi, ebp);
        port_set32(&port, 0, 0x5448e4,
                   port_call_with(&port, 0x4ace40, piece, port_u32(&port, 0, 0x5448ec), ebx, piece,
                                  esi, edi, ebp));
        port_call_with(&port, 0x4ad110, piece, port_u32(&port, 0, 0x5448ec), ebx, piece, esi, edi,
                       ebp);
    }
    port_call_with(&port, 0x4ad2c0, piece, 0x5448d4, 0x5448d6, piece, esi, edi, ebp);
    port_set16(&port, piece, 0xe, port_u16(&port, 0, 0x5448d4));
    port_set16(&port, piece, 0x16, port_u16(&port, 0, 0x5448d6));
    height = (uint32_t)((int32_t)port_u32(&port, piece, 0x28) >> 16);
    port_set32(&port, 0, 0x5448dc, height);
    eax = (uint32_t)((int32_t)port_u32(&port, piece, 0x3e) >> 16);
    reach = (uint32_t)((int32_t)port_u32(&port, piece, 0x2e) >> 16) + eax;
    port_set32(&port, 0, 0x5448d8, reach);
    ebx = height;
    if (height <= 0x28)
    {
        port_set8(&port, piece, 0x44, 0x10);
    }
    else if (height >= reach)
    {
        port_set8(&port, piece, 0x44, 8);
    }
    else
    {
        level = 0x10 - ((height - 0x28) * 8) / (reach - 0x28);
        port_set32(&port, 0, 0x5448e0, level);
        eax = (int32_t)level >= 0x10 ? 0x10 : level;
        port_set8(&port, piece, 0x44, (int32_t)(eax & 0xff) <= 8 ? 8 : eax & 0xff);
    }
    if (port_u32(&port, 0, 0x5448e4) == 0)
    {
        port_set8(&port, piece, 0x45, 0);
        port_set16(&port, piece, 0x46, 1);
        eax = port_call_with(&port, 0x4ac8f0, piece, 0x443ab0, ebx, piece, esi, edi, ebp);
    }
    return port_return(&port, eax, entry->edx);
}

/* Original 0x444550: a falling piece eax's frame: 0x54499c set; moved (0x4ac500, 0x4ac600)
 * and, when 0x4ac620 answers its edx, its stride (0x4ac640, kept at 0x5449a4) taken across
 * (0x4ac6b0) and down (0x4ad5e0 of +0x30 into 0x54499c, a negative way set aside at 0x5449a0
 * while its speed is turned); when it lands (0x4ac520 gives 1) its stride (0x4ac540, 0x4ac5b0)
 * bounces it (0x4ace40, 0x54499c cleared when it does not); placed (0x4ad260 into 0x54498c and
 * 0x54498e, copied to +0xe and +0x16), its height +0x28 (0x544994) against its reach +0x2e
 * (0x544990) gives +0x44: 0x10 up to 0x28, 0 past the reach, between them 0x10 less 16 parts of
 * the way (0x544998) at most 0x10; with it 0 or 0x54499c clear, the state 0 (0x4ac8f0). The
 * registers but eax kept. */
uint32_t vertrix_port_piece_fall_444550(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x10
    };
    Port port;
    uint32_t piece = entry->eax;
    uint32_t ebp = entry->ebp;
    uint32_t ebx = entry->ebx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t edx;
    uint32_t stride;
    uint32_t height;
    uint32_t reach;
    uint32_t level;
    uint32_t eax;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, entry->esp, -4u, entry->ebx);
    port_set32(&port, entry->esp, -8u, entry->ecx);
    port_set32(&port, entry->esp, -0xcu, entry->edx);
    port_set32(&port, entry->esp, -0x10u, entry->esi);
    port_set32(&port, 0, 0x54499c, 1);
    port_call_with(&port, 0x4ac500, piece, 1, ebx, piece, esi, edi, ebp);
    port_call_with(&port, 0x4ac600, piece, vertrix_lift_edx, ebx, piece, esi, edi, ebp);
    eax = port_call_with(&port, 0x4ac620, piece, vertrix_lift_edx, ebx, piece, esi, edi, ebp);
    if (eax == vertrix_lift_edx)
    {
        stride =
            port_call_with(&port, 0x4ac640, piece, vertrix_lift_edx, ebx, piece, esi, edi, ebp);
        port_set32(&port, 0, 0x5449a4, stride);
        port_call_with(&port, 0x4ac6b0, piece, vertrix_lift_edx, ebx, piece, esi, edi, ebp);
        if ((int32_t)port_u32(&port, piece, 0x30) >> 16 >= 0)
        {
            port_set32(&port, 0, 0x54499c,
                       port_call_with(&port, 0x4ad5e0, piece, port_u32(&port, 0, 0x5449a4), ebx,
                                      piece, esi, edi, ebp));
        }
        else
        {
            port_set16(&port, 0, 0x5449a0, port_u16(&port, piece, 0x30));
            edx = 0u - ((vertrix_lift_edx & 0xffff0000u) | port_u16(&port, piece, 0x32));
            port_set16(&port, piece, 0x32, edx);
            port_set16(&port, piece, 0x30, 0);
            port_set32(&port, 0, 0x54499c,
                       port_call_with(&port, 0x4ad5e0, piece, port_u32(&port, 0, 0x5449a4), ebx,
                                      piece, esi, edi, ebp));
            ebx = 0u - ((ebx & 0xffff0000u) | port_u16(&port, piece, 0x32));
            port_set16(&port, piece, 0x30, port_u16(&port, 0, 0x5449a0));
            port_set16(&port, piece, 0x32, ebx);
        }
    }
    if (port_call_with(&port, 0x4ac520, piece, vertrix_lift_edx, ebx, piece, esi, edi, ebp) == 1)
    {
        stride =
            port_call_with(&port, 0x4ac540, piece, vertrix_lift_edx, ebx, piece, esi, edi, ebp);
        port_set32(&port, 0, 0x5449a4, stride);
        port_call_with(&port, 0x4ac5b0, piece, vertrix_lift_edx, ebx, piece, esi, edi, ebp);
        if (port_call_with(&port, 0x4ace40, piece, port_u32(&port, 0, 0x5449a4), ebx, piece, esi,
                           edi, ebp) == 0)
        {
            port_set32(&port, 0, 0x54499c, 0);
        }
    }
    port_call_with(&port, 0x4ad260, piece, 0x54498c, 0x54498e, piece, esi, edi, ebp);
    ebx = 0x54498e;
    port_set16(&port, piece, 0xe, port_u16(&port, 0, 0x54498c));
    port_set16(&port, piece, 0x16, port_u16(&port, 0, 0x54498e));
    height = (uint32_t)((int32_t)port_u32(&port, piece, 0x28) >> 16);
    port_set32(&port, 0, 0x544994, height);
    reach = (uint32_t)((int32_t)port_u32(&port, piece, 0x2e) >> 16);
    port_set32(&port, 0, 0x544990, reach);
    esi = height;
    eax = reach;
    if (height <= 0x28)
    {
        port_set8(&port, piece, 0x44, 0x10);
        if (port_u32(&port, 0, 0x54499c) != 0)
        {
            return port_return(&port, eax, entry->edx);
        }
    }
    else if (height > reach)
    {
        port_set8(&port, piece, 0x44, 0);
    }
    else
    {
        ebx = reach - 0x28;
        level = 0x10 - ((height - 0x28) << 4) / ebx;
        port_set32(&port, 0, 0x544998, level);
        port_set8(&port, piece, 0x44, (int32_t)level >= 0x10 ? 0x10 : level);
        eax = port_u8(&port, piece, 0x44);
        port_set8(&port, piece, 0x44, eax);
        if (eax != 0 && port_u32(&port, 0, 0x54499c) != 0)
        {
            return port_return(&port, eax, entry->edx);
        }
    }
    eax = port_call_with(&port, 0x4ac8f0, piece, 0, ebx, piece, esi, edi, ebp);
    return port_return(&port, eax, entry->edx);
}
