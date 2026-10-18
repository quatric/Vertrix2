#include "rtlsurfacefills.h"

/* Pictures filled with one colour. */

/* Original 0x478f50: the picture eax filled with the colour edx: the colour mapped (0x479a40,
 * kept at 0x558a0c), then by the depth +0xc spread over a dword (1: four times, 2: twice, 4:
 * itself, else the last fill 0x558a08); the pixels +0 written a dword at a time, the whole
 * width +4 by height +8 at once, or with a row skip +0x10 row by row with the skip +0x18 (kept at
 * 0x558a04, the rows counted down at 0x558a00). The walk left at 0x5589f8 (dwords), 0x558a08
 * (the fill), 0x5589f4 (the place) and 0x5589fc. eax the pixel count, or 0 by rows; edx's low
 * byte the depth. */
uint32_t vertrix_port_surface_fill_478f50(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x1c
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t picture = entry->eax;
    uint32_t colour = entry->edx;
    uint32_t ecx;
    uint32_t esi;
    uint32_t edi;
    uint32_t place;
    uint32_t eax;
    uint32_t depth;
    uint32_t edx;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -4u, entry->ebx);
    port_set32(&port, ebp, -8u, entry->ecx);
    port_set32(&port, ebp, -0xcu, entry->esi);
    port_set32(&port, ebp, -0x10u, entry->edi);
    ecx = port_u32(&port, 0, 0x5589fc);
    place = port_u32(&port, 0, 0x5589f4);
    esi = port_u32(&port, 0, 0x558a08);
    edi = port_u32(&port, 0, 0x5589f8);
    port_set32(&port, ebp, -0x14u, picture);
    port_set32(&port, ebp, -0x18u, colour);
    port_set32(&port, 0, 0x558a0c,
               port_call_with(&port, 0x479a40, picture, colour, place, ecx, esi, edi, ebp));
    depth = port_u8(&port, picture, 0xc);
    edx = (vertrix_lift_edx & 0xffffff00u) | depth;
    if (depth == 1)
    {
        esi = colour + ((colour << 8) + ((colour << 24) + (colour << 16)));
        ecx = port_u32(&port, 0, 0x5589fc);
    }
    else
    {
        esi = port_u32(&port, 0, 0x558a08);
        ecx = port_u32(&port, 0, 0x5589fc);
        if (depth == 2)
        {
            esi = colour + (colour << 16);
        }
        else if (depth == 4)
        {
            esi = colour;
        }
    }
    if (port_u32(&port, picture, 0x10) == 0)
    {
        eax = port_u32(&port, picture, 4) * port_u32(&port, picture, 8);
        edi = (eax * port_u8(&port, picture, 0xc)) >> 2;
        place = port_u32(&port, picture, 0);
        for (; edi != 0 && !port.env.failed; edi--)
        {
            place += 4;
            port_set32(&port, place, -4u, esi);
        }
    }
    else
    {
        uint32_t rows;
        edi = (port_u32(&port, picture, 4) * port_u8(&port, picture, 0xc)) >> 2;
        port_set32(&port, 0, 0x558a04, port_u32(&port, picture, 0x18));
        place = port_u32(&port, picture, 0);
        rows = port_u32(&port, picture, 8);
        port_set32(&port, 0, 0x558a00, rows);
        eax = rows;
        while (eax != 0 && !port.env.failed)
        {
            for (ecx = edi; ecx != 0 && !port.env.failed; ecx--)
            {
                place += 4;
                port_set32(&port, place, -4u, esi);
            }
            place += port_u32(&port, 0, 0x558a04);
            eax = port_u32(&port, 0, 0x558a00) - 1;
            port_set32(&port, 0, 0x558a00, eax);
        }
    }
    port_set32(&port, 0, 0x5589f8, edi);
    port_set32(&port, 0, 0x558a08, esi);
    port_set32(&port, 0, 0x5589f4, place);
    port_set32(&port, 0, 0x5589fc, ecx);
    return port_return(&port, eax, edx);
}
