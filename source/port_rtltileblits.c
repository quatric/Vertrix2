#include "port_rtltileblits.h"

/* The ten-row tile blitter. */

static uint32_t low(uint32_t value)
{
    return value & 0xff;
}

static uint32_t high(uint32_t value)
{
    return (value >> 8) & 0xff;
}

static void set_low(uint32_t *reg, uint32_t value)
{
    *reg = (*reg & 0xffffff00u) | (value & 0xff);
}

static void set_high(uint32_t *reg, uint32_t value)
{
    *reg = (*reg & 0xffff00ffu) | ((value & 0xff) << 8);
}

static uint32_t g8(Port *port, uint32_t address)
{
    return port_u8(port, 0, address);
}

static uint32_t g32(Port *port, uint32_t address)
{
    return port_u32(port, 0, address);
}

/* Original 0x442140 (one stack argument, popped: handed to 0x478eb0 in ebx): the tile dl (its
 * width 0x544790, its ten rows of indices at 0x54438c) drawn in the palette bl (12 bytes a palette
 * from 0x5440f8, its fourth byte set for transparent index 0) on the surface eax at the point ecx
 * (0x478eb0), by the surface's depth +0xc and format +0xd: 8-bit (3-3-2 colours; walk
 * 0x544080..0x544098), 32-bit (0x54409c..0x5440b4), 16-bit 5-6-5 (format 2; 0x5440b8..0x5440d0) or
 * 5-5-5 (format 1; 0x5440d4..0x5440ec); without transparency the 8- and 16-bit 5-5-5 forms take
 * each pixel's three channels from three indices. The source walk kept at 0x544088 / 0x5440dc. */
uint32_t vertrix_port_tile_blit_442140(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x1c
    };
    Port port;
    uint8_t stack[BELOW + 8 + 4];
    uint32_t ebp = entry->esp - 4;
    uint32_t surface = entry->eax;
    uint32_t eax = entry->eax;
    uint32_t edx;
    uint32_t ebx;
    uint32_t ecx;
    uint32_t esi;
    uint32_t edi;
    uint32_t value;
    port_open_arguments(&port, stack, calls, services, globals, entry, BELOW, 1);
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -4u, entry->esi);
    port_set32(&port, ebp, -8u, entry->edi);
    esi = g32(&port, 0x5440dc);
    edi = g32(&port, 0x544088);
    port_set32(&port, ebp, -0x14u, surface);
    port_set8(&port, ebp, -0xcu, entry->edx);
    port_set8(&port, ebp, -0x10u, entry->ebx);
    ebx = port_u32(&port, ebp, 8);
    edx = entry->ecx;
    ecx = surface;
    set_low(&eax, port_u8(&port, surface, 0xd));
    set_high(&eax, port_u8(&port, ecx, 0xc));
    if (high(eax) == 1)
    {
        /* 0x44219d: 8-bit. */
        ecx = port_u8(&port, ebp, -0x10u);
        ecx = 0x5440f8 + ecx * 12;
        eax = port_u8(&port, ebp, -0xcu);
        port_set32(&port, 0, 0x54408c, ecx);
        set_high(&ecx, 0);
        set_low(&ecx, g8(&port, eax + 0x544790));
        edi = g32(&port, eax * 4 + 0x54438c);
        set_low(&eax, 0xa);
        port_set16(&port, 0, 0x544094, ecx);
        port_set32(&port, 0, 0x544088, edi);
        port_set8(&port, 0, 0x544081, eax);
        eax = port_u32(&port, ebp, -0x14u);
        ecx = 0;
        eax = port_call_with(&port, 0x478eb0, eax, edx, ebx, ecx, esi, edi, ebp);
        edx = eax;
        port_set32(&port, 0, 0x544098, eax);
        ecx = (ecx & 0xffff0000u) | port_u16(&port, 0, 0x544094);
        eax = port_u32(&port, port_u32(&port, ebp, -0x14u), 0x14) - ecx;
        port_set32(&port, 0, 0x544090, eax);
        eax = g32(&port, 0x54408c);
        port_set32(&port, 0, 0x544084, edx);
        set_low(&edx, port_u8(&port, eax, 3));
        edi = g32(&port, 0x544088);
        if (low(edx) != 0)
        {
            set_high(&ebx, 0xff);
            esi = g32(&port, 0x5440dc);
            set_low(&ebx, 0);
            for (;;)
            {
                set_low(&eax, g8(&port, 0x544081));
                port_set32(&port, 0, 0x544088, edi);
                if (low(eax) == 0 || port.env.failed)
                {
                    break;
                }
                set_low(&eax, g8(&port, 0x544094));
                port_set8(&port, 0, 0x544080, eax);
                if (low(eax) != 0)
                {
                    do
                    {
                        set_high(&ecx, port_u8(&port, edi, 0));
                        eax = edi;
                        if (high(ecx) != 0)
                        {
                            set_low(&eax, high(ecx));
                            eax &= 0xff;
                            edx = g32(&port, 0x54408c);
                            eax = eax * 4 + edx;
                            value = port_u32(&port, eax, 0);
                            ecx = (value & 0xe00000) >> 10;
                            edx = (value & 0xe000) >> 5;
                            eax = value & 0xc0;
                            edx |= ecx;
                            eax = (eax | edx) >> 6;
                            set_low(&edx, eax);
                            eax = g32(&port, 0x544084);
                            port_set8(&port, eax, 0, edx);
                        }
                        ecx = g32(&port, 0x544084);
                        set_low(&edx, g8(&port, 0x544080));
                        edi++;
                        ecx++;
                        set_low(&edx, low(edx) + high(ebx));
                        port_set32(&port, 0, 0x544084, ecx);
                        port_set8(&port, 0, 0x544080, edx);
                    } while (low(edx) != 0 && !port.env.failed);
                }
                eax = g32(&port, 0x544090);
                edx = g32(&port, 0x544084);
                set_low(&ecx, g8(&port, 0x544081));
                edx += eax;
                set_low(&ecx, low(ecx) + high(ebx));
                port_set32(&port, 0, 0x544084, edx);
                port_set8(&port, 0, 0x544081, ecx);
            }
        }
        else
        {
            esi = g32(&port, 0x5440dc);
            for (;;)
            {
                set_high(&edx, g8(&port, 0x544081));
                port_set32(&port, 0, 0x544088, edi);
                if (high(edx) == 0 || port.env.failed)
                {
                    break;
                }
                set_low(&eax, g8(&port, 0x544094));
                port_set8(&port, 0, 0x544080, eax);
                if (low(eax) != 0)
                {
                    do
                    {
                        eax = g32(&port, 0x54408c);
                        ecx = port_u32(&port, eax, port_u8(&port, edi, 0) * 4) & 0xe00000;
                        edx = port_u32(&port, eax, port_u8(&port, edi, 1) * 4) & 0xe000;
                        ecx = (ecx >> 10) | (edx >> 5);
                        edx = port_u8(&port, edi, 2);
                        eax = port_u32(&port, eax, edx * 4) & 0xc0;
                        eax = (eax | ecx) >> 6;
                        set_low(&edx, eax);
                        eax = g32(&port, 0x544084) + 1;
                        edi += 3;
                        set_high(&ebx, g8(&port, 0x544080));
                        port_set8(&port, eax, -1u, edx);
                        port_set32(&port, 0, 0x544084, eax);
                        set_high(&ebx, high(ebx) - 1);
                        port_set8(&port, 0, 0x544080, high(ebx));
                    } while (high(ebx) != 0 && !port.env.failed);
                }
                eax = g32(&port, 0x544090);
                edx = g32(&port, 0x544084);
                set_high(&ecx, g8(&port, 0x544081));
                edx += eax;
                set_high(&ecx, high(ecx) - 1);
                port_set32(&port, 0, 0x544084, edx);
                port_set8(&port, 0, 0x544081, high(ecx));
            }
        }
    }
    else if (high(eax) == 4)
    {
        /* 0x44238f: 32-bit. */
        eax = port_u8(&port, ebp, -0x10u);
        port_set32(&port, ebp, -0x18u, eax);
        ecx = 0x5440f8 + eax * 12;
        eax = port_u8(&port, ebp, -0xcu);
        port_set32(&port, 0, 0x5440a8, ecx);
        set_high(&ecx, 0);
        set_low(&ecx, g8(&port, eax + 0x544790));
        port_set16(&port, 0, 0x5440b0, ecx);
        eax = g32(&port, eax * 4 + 0x54438c);
        set_low(&ecx, 0xa);
        port_set32(&port, 0, 0x5440a4, eax);
        eax = port_u32(&port, ebp, -0x14u);
        port_set8(&port, 0, 0x54409d, ecx);
        eax = port_call_with(&port, 0x478eb0, eax, edx, ebx, ecx, esi, edi, ebp);
        edx = port_u16(&port, 0, 0x5440b0);
        ecx = edx * 4;
        port_set32(&port, 0, 0x5440b4, eax);
        port_set32(&port, 0, 0x5440a0, eax);
        edx = port_u32(&port, port_u32(&port, ebp, -0x14u), 0x14);
        eax = g32(&port, 0x5440a8);
        edx -= ecx;
        set_high(&ecx, port_u8(&port, eax, 3));
        port_set32(&port, 0, 0x5440ac, edx);
        if (high(ecx) != 0)
        {
            set_high(&ebx, 0xff);
            ecx = 4;
            edi = g32(&port, 0x544088);
            esi = g32(&port, 0x5440dc);
            set_low(&ebx, 0);
            for (;;)
            {
                set_low(&eax, g8(&port, 0x54409d));
                port_set32(&port, 0, 0x544088, edi);
                if (low(eax) == 0 || port.env.failed)
                {
                    break;
                }
                set_low(&eax, g8(&port, 0x5440b0));
                port_set8(&port, 0, 0x54409c, eax);
                if (low(eax) != 0)
                {
                    do
                    {
                        eax = g32(&port, 0x5440a4);
                        set_low(&edx, port_u8(&port, eax, 0));
                        if (low(edx) != 0)
                        {
                            set_low(&eax, edx);
                            eax &= 0xff;
                            edx = g32(&port, 0x5440a8);
                            eax = eax * 4 + edx;
                            edx = g32(&port, 0x5440a0);
                            eax = port_u32(&port, eax, 0);
                            port_set32(&port, edx, 0, eax);
                        }
                        edx = g32(&port, 0x5440a4) + 1;
                        eax = g32(&port, 0x5440a0);
                        port_set32(&port, 0, 0x5440a4, edx);
                        set_low(&edx, g8(&port, 0x54409c));
                        eax += ecx;
                        set_low(&edx, low(edx) + high(ebx));
                        port_set32(&port, 0, 0x5440a0, eax);
                        port_set8(&port, 0, 0x54409c, edx);
                    } while (low(edx) != 0 && !port.env.failed);
                }
                edx = g32(&port, 0x5440a0);
                eax = g32(&port, 0x5440ac);
                edx += eax;
                set_low(&eax, g8(&port, 0x54409d));
                set_low(&eax, low(eax) + high(ebx));
                port_set32(&port, 0, 0x5440a0, edx);
                port_set8(&port, 0, 0x54409d, eax);
            }
        }
        else
        {
            set_high(&ebx, 0xff);
            edi = g32(&port, 0x544088);
            esi = g32(&port, 0x5440dc);
            set_low(&ebx, 0);
            for (;;)
            {
                set_high(&ecx, g8(&port, 0x54409d));
                port_set32(&port, 0, 0x544088, edi);
                if (high(ecx) == 0 || port.env.failed)
                {
                    break;
                }
                set_low(&eax, g8(&port, 0x5440b0));
                port_set8(&port, 0, 0x54409c, eax);
                if (low(eax) != 0)
                {
                    do
                    {
                        eax = g32(&port, 0x5440a4) + 1;
                        edx = port_u8(&port, eax, -1u);
                        port_set32(&port, 0, 0x5440a4, eax);
                        eax = g32(&port, 0x5440a0);
                        ecx = g32(&port, 0x5440a8);
                        eax += 4;
                        edx = port_u32(&port, ecx, edx * 4);
                        port_set32(&port, eax, -4u, edx);
                        port_set32(&port, 0, 0x5440a0, eax);
                        set_high(&eax, g8(&port, 0x54409c));
                        set_high(&eax, high(eax) + high(ebx));
                        port_set8(&port, 0, 0x54409c, high(eax));
                    } while (high(eax) != 0 && !port.env.failed);
                }
                eax = g32(&port, 0x5440a0);
                edx = g32(&port, 0x5440ac);
                eax += edx;
                set_high(&edx, g8(&port, 0x54409d));
                set_high(&edx, high(edx) + high(ebx));
                port_set32(&port, 0, 0x5440a0, eax);
                port_set8(&port, 0, 0x54409d, high(edx));
            }
        }
    }
    else if (high(eax) == 2 && low(eax) == high(eax))
    {
        /* 0x442553: 16-bit 5-6-5. */
        eax = port_u8(&port, ebp, -0x10u);
        port_set32(&port, ebp, -0x18u, eax);
        ecx = 0x5440f8 + eax * 12;
        eax = port_u8(&port, ebp, -0xcu);
        port_set32(&port, 0, 0x5440c4, ecx);
        set_high(&ecx, 0);
        set_low(&ecx, g8(&port, eax + 0x544790));
        eax = g32(&port, eax * 4 + 0x54438c);
        port_set32(&port, 0, 0x5440c0, eax);
        port_set8(&port, 0, 0x5440b9, 0xa);
        eax = port_u32(&port, ebp, -0x14u);
        port_set16(&port, 0, 0x5440cc, ecx);
        eax = port_call_with(&port, 0x478eb0, eax, edx, ebx, ecx, esi, edi, ebp);
        edx = eax;
        port_set32(&port, 0, 0x5440d0, eax);
        eax = port_u16(&port, 0, 0x5440cc);
        ecx = eax + eax;
        eax = port_u32(&port, port_u32(&port, ebp, -0x14u), 0x14) - ecx;
        port_set32(&port, 0, 0x5440c8, eax);
        eax = g32(&port, 0x5440c4);
        port_set32(&port, 0, 0x5440bc, edx);
        if (port_u8(&port, eax, 3) != 0)
        {
            set_high(&ebx, 0xff);
            edi = g32(&port, 0x544088);
            esi = g32(&port, 0x5440dc);
            set_low(&ebx, 0);
            for (;;)
            {
                set_high(&ecx, g8(&port, 0x5440b9));
                port_set32(&port, 0, 0x544088, edi);
                if (high(ecx) == 0 || port.env.failed)
                {
                    break;
                }
                set_low(&eax, g8(&port, 0x5440cc));
                port_set8(&port, 0, 0x5440b8, eax);
                if (low(eax) != 0)
                {
                    do
                    {
                        eax = g32(&port, 0x5440c0);
                        set_low(&ecx, port_u8(&port, eax, 0));
                        if (low(ecx) != 0)
                        {
                            edx = low(ecx) * 4;
                            eax = g32(&port, 0x5440c4) + edx;
                            value = port_u32(&port, eax, 0);
                            ecx = (value & 0xf80000) >> 5;
                            edx = (value & 0xfc00) >> 2;
                            eax = value & 0xf8;
                            edx |= ecx;
                            eax = (eax | edx) >> 3;
                            edx = eax;
                            eax = g32(&port, 0x5440bc);
                            port_set16(&port, eax, 0, edx);
                        }
                        eax = g32(&port, 0x5440bc) + 2;
                        ecx = g32(&port, 0x5440c0);
                        port_set32(&port, 0, 0x5440bc, eax);
                        set_high(&eax, g8(&port, 0x5440b8));
                        ecx++;
                        set_high(&eax, high(eax) + high(ebx));
                        port_set32(&port, 0, 0x5440c0, ecx);
                        port_set8(&port, 0, 0x5440b8, high(eax));
                    } while (high(eax) != 0 && !port.env.failed);
                }
                edx = g32(&port, 0x5440bc);
                eax = g32(&port, 0x5440c8);
                edx += eax;
                port_set32(&port, 0, 0x5440bc, edx);
                port_set8(&port, 0, 0x5440b9, g8(&port, 0x5440b9) + high(ebx));
            }
        }
        else
        {
            set_high(&ebx, 0xff);
            edi = g32(&port, 0x544088);
            esi = g32(&port, 0x5440dc);
            set_low(&ebx, 0);
            for (;;)
            {
                set_low(&eax, g8(&port, 0x5440b9));
                port_set32(&port, 0, 0x544088, edi);
                if (low(eax) == 0 || port.env.failed)
                {
                    break;
                }
                set_low(&eax, g8(&port, 0x5440cc));
                port_set8(&port, 0, 0x5440b8, eax);
                if (low(eax) != 0)
                {
                    do
                    {
                        edx = g32(&port, 0x5440c0);
                        eax = port_u8(&port, edx, 0);
                        ecx = eax * 4;
                        edx++;
                        eax = g32(&port, 0x5440c4);
                        port_set32(&port, 0, 0x5440c0, edx);
                        edx = (port_u32(&port, eax + ecx, 0) & 0xf80000) >> 5;
                        port_set32(&port, ebp, -0x18u, edx);
                        edx = g32(&port, 0x5440c0);
                        ecx = port_u8(&port, edx, 0) * 4;
                        edx++;
                        port_set32(&port, 0, 0x5440c0, edx);
                        edx = port_u32(&port, eax + ecx, 0) & 0xfc00;
                        ecx = port_u32(&port, ebp, -0x18u);
                        edx >>= 2;
                        ecx |= edx;
                        edx = g32(&port, 0x5440c0) + 1;
                        port_set32(&port, ebp, -0x18u, ecx);
                        ecx = port_u8(&port, edx, -1u);
                        port_set32(&port, 0, 0x5440c0, edx);
                        eax = port_u32(&port, eax, ecx * 4);
                        edx = port_u32(&port, ebp, -0x18u);
                        eax = ((eax & 0xf8) | edx) >> 3;
                        edx = eax;
                        eax = g32(&port, 0x5440bc);
                        port_set16(&port, eax, 0, edx);
                        set_low(&edx, g8(&port, 0x5440b8));
                        eax += 2;
                        set_low(&edx, low(edx) + high(ebx));
                        port_set32(&port, 0, 0x5440bc, eax);
                        port_set8(&port, 0, 0x5440b8, edx);
                    } while (low(edx) != 0 && !port.env.failed);
                }
                edx = g32(&port, 0x5440bc);
                eax = g32(&port, 0x5440c8);
                set_low(&ecx, g8(&port, 0x5440b9));
                edx += eax;
                set_low(&ecx, low(ecx) + high(ebx));
                port_set32(&port, 0, 0x5440bc, edx);
                port_set8(&port, 0, 0x5440b9, ecx);
            }
        }
    }
    else if (high(eax) == 2 && low(eax) == 1)
    {
        /* 0x442796: 16-bit 5-5-5. */
        ecx = port_u8(&port, ebp, -0x10u);
        ecx = 0x5440f8 + ecx * 12;
        eax = port_u8(&port, ebp, -0xcu);
        port_set32(&port, 0, 0x5440e0, ecx);
        set_high(&ecx, 0);
        set_low(&ecx, g8(&port, eax + 0x544790));
        esi = g32(&port, eax * 4 + 0x54438c);
        eax = port_u32(&port, ebp, -0x14u);
        port_set16(&port, 0, 0x5440e8, ecx);
        set_low(&ecx, 0xa);
        port_set32(&port, 0, 0x5440dc, esi);
        port_set8(&port, 0, 0x5440d5, ecx);
        eax = port_call_with(&port, 0x478eb0, eax, edx, ebx, ecx, esi, edi, ebp);
        edx = eax;
        port_set32(&port, 0, 0x5440ec, eax);
        ecx = port_u16(&port, 0, 0x5440e8);
        eax = port_u32(&port, port_u32(&port, ebp, -0x14u), 0x14);
        ecx += ecx;
        eax -= ecx;
        port_set32(&port, 0, 0x5440e4, eax);
        eax = g32(&port, 0x5440e0);
        esi = g32(&port, 0x5440dc);
        set_high(&ecx, port_u8(&port, eax, 3));
        port_set32(&port, 0, 0x5440d8, edx);
        if (high(ecx) != 0)
        {
            set_high(&ebx, 0xff);
            edi = g32(&port, 0x544088);
            set_low(&ebx, 0);
            for (;;)
            {
                set_low(&eax, g8(&port, 0x5440d5));
                port_set32(&port, 0, 0x544088, edi);
                if (low(eax) == 0 || port.env.failed)
                {
                    break;
                }
                set_low(&eax, g8(&port, 0x5440e8));
                port_set8(&port, 0, 0x5440d4, eax);
                if (low(eax) != 0)
                {
                    do
                    {
                        set_high(&ecx, port_u8(&port, esi, 0));
                        eax = esi;
                        if (high(ecx) != 0)
                        {
                            eax = high(ecx) * 4 + g32(&port, 0x5440e0);
                            value = port_u32(&port, eax, 0);
                            ecx = (value & 0xf80000) >> 6;
                            edx = (value & 0xf800) >> 3;
                            eax = value & 0xf8;
                            edx |= ecx;
                            eax = (eax | edx) >> 3;
                            edx = eax;
                            eax = g32(&port, 0x5440d8);
                            port_set16(&port, eax, 0, edx);
                        }
                        eax = g32(&port, 0x5440d8);
                        set_low(&edx, g8(&port, 0x5440d4));
                        esi++;
                        eax += 2;
                        set_low(&edx, low(edx) + high(ebx));
                        port_set32(&port, 0, 0x5440d8, eax);
                        port_set8(&port, 0, 0x5440d4, edx);
                    } while (low(edx) != 0 && !port.env.failed);
                }
                edx = g32(&port, 0x5440d8);
                eax = g32(&port, 0x5440e4);
                set_low(&ecx, g8(&port, 0x5440d5));
                edx += eax;
                set_low(&ecx, low(ecx) + high(ebx));
                port_set32(&port, 0, 0x5440d8, edx);
                port_set8(&port, 0, 0x5440d5, ecx);
            }
        }
        else
        {
            edi = g32(&port, 0x544088);
            for (;;)
            {
                set_high(&edx, g8(&port, 0x5440d5));
                port_set32(&port, 0, 0x544088, edi);
                if (high(edx) == 0 || port.env.failed)
                {
                    break;
                }
                set_low(&eax, g8(&port, 0x5440e8));
                port_set8(&port, 0, 0x5440d4, eax);
                if (low(eax) != 0)
                {
                    do
                    {
                        eax = g32(&port, 0x5440e0);
                        ecx = port_u32(&port, eax, port_u8(&port, esi, 0) * 4) & 0xf80000;
                        edx = port_u32(&port, eax, port_u8(&port, esi, 1) * 4) & 0xf800;
                        ecx = (ecx >> 6) | (edx >> 3);
                        edx = port_u8(&port, esi, 2);
                        eax = port_u32(&port, eax, edx * 4) & 0xf8;
                        eax = (eax | ecx) >> 3;
                        esi += 3;
                        edx = eax;
                        eax = g32(&port, 0x5440d8) + 2;
                        set_high(&ebx, g8(&port, 0x5440d4));
                        port_set16(&port, eax, -2u, edx);
                        port_set32(&port, 0, 0x5440d8, eax);
                        set_high(&ebx, high(ebx) - 1);
                        port_set8(&port, 0, 0x5440d4, high(ebx));
                    } while (high(ebx) != 0 && !port.env.failed);
                }
                edx = g32(&port, 0x5440d8);
                eax = g32(&port, 0x5440e4);
                set_high(&ecx, g8(&port, 0x5440d5));
                edx += eax;
                set_high(&ecx, high(ecx) - 1);
                port_set32(&port, 0, 0x5440d8, edx);
                port_set8(&port, 0, 0x5440d5, high(ecx));
            }
        }
    }
    port_set32(&port, 0, 0x5440dc, esi);
    return port_return(&port, eax, edx);
}
