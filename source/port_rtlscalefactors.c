#include "port_rtlscalefactors.h"

/* MPEG audio layer 3 scale factors read. */

/* count fields of eax bits each read (0x404680) into the dwords at *place; edx follows what each
 * call leaves. */
static void read_fields(Port *port, uint32_t *place, uint32_t *edx, uint32_t bits_from_edx,
                        uint32_t ebx, uint32_t count, uint32_t edi, uint32_t ebp)
{
    uint32_t value;
    for (; count != 0 && !port->env.failed; count--)
    {
        value = port_call_with(port, 0x404680, bits_from_edx ? *edx : ebx, *edx, ebx, *place, count,
                               edi, ebp);
        *edx = vertrix_lift_edx;
        port_set32(port, *place, 0, value);
        *place += 4;
    }
}

/* count fields of ebx bits read with edx the count left (each call's edx less one). */
static void read_counted(Port *port, uint32_t *place, uint32_t *edx, uint32_t ebx, uint32_t esi,
                         uint32_t edi, uint32_t ebp)
{
    uint32_t value;
    do
    {
        value = port_call_with(port, 0x404680, ebx, *edx, ebx, *place, esi, edi, ebp);
        port_set32(port, *place, 0, value);
        *place += 4;
        *edx = vertrix_lift_edx - 1;
    } while (*edx != 0 && !port->env.failed);
}

/* count zero fields at *place. */
static void zero_fields(Port *port, uint32_t *place, unsigned count)
{
    for (; count != 0; count--)
    {
        port_set32(port, *place, 0, 0);
        *place += 4;
    }
}

/* Original 0x4074a0: the scale factors of the granule edx read into the dwords at eax, the bit
 * lengths from its +0xc by the tables 0x4f5e78 (first) and 0x4f5e88 (second). Short blocks (+0x10
 * 2): mixed (+0x14) 8 then 9, else 18, of the first, 18 of the second, three zeros; eax 18 times
 * the two (mixed less the first). Long blocks by the reuse bits +0 (from bit 8 down, each group
 * reused written as zeros and not counted): 6 and 5 of the first, 5 and 5 of the second; with +0
 * negative 11 of the first and 10 of the second; then a zero. eax the bits read. */
uint32_t vertrix_port_scale_factors_4074a0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x1c
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t place = entry->eax;
    uint32_t granule = entry->edx;
    uint32_t edx;
    uint32_t ebx;
    uint32_t esi = entry->esi;
    uint32_t edi;
    uint32_t reuse;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -4u, entry->ebx);
    port_set32(&port, ebp, -8u, entry->ecx);
    port_set32(&port, ebp, -0xcu, entry->esi);
    port_set32(&port, ebp, -0x10u, entry->edi);
    port_set32(&port, ebp, -0x18u, granule);
    ebx = port_u32(&port, granule, 0xc);
    edx = port_u8(&port, ebx, 0x4f5e78);
    ebx = port_u8(&port, ebx, 0x4f5e88);
    edi = entry->edi;
    if (port_u32(&port, granule, 0x10) == 2)
    {
        esi = 0x12;
        edi = (edx + ebx) * 18;
        if (port_u32(&port, granule, 0x14) != 0)
        {
            read_fields(&port, &place, &edx, 1, ebx, 8, edi, ebp);
            esi = 9;
            edi -= edx;
        }
        read_fields(&port, &place, &edx, 1, ebx, esi, edi, ebp);
        esi = 0;
        edx = 0x12;
        read_counted(&port, &place, &edx, ebx, esi, edi, ebp);
        port_set32(&port, place, 0, edx);
        port_set32(&port, place, 4, edx);
        port_set32(&port, place, 8, edx);
        return port_return(&port, edi, edx);
    }
    reuse = port_u32(&port, granule, 0);
    port_set32(&port, ebp, -0x14u, reuse);
    if ((int32_t)reuse < 0)
    {
        read_fields(&port, &place, &edx, 1, ebx, 0xb, entry->edi, ebp);
        read_fields(&port, &place, &edx, 0, ebx, 0xa, entry->edi, ebp);
        ebx += edx;
        edi = ebx * 10 + edx;
        port_set32(&port, place, 0, 0);
        return port_return(&port, edi, edx);
    }
    edi = 0;
    if (reuse & 8)
    {
        zero_fields(&port, &place, 6);
    }
    else
    {
        read_fields(&port, &place, &edx, 1, ebx, 6, edi, ebp);
        esi = 0;
        edi += edx * 6;
    }
    if (reuse & 4)
    {
        zero_fields(&port, &place, 5);
    }
    else
    {
        read_fields(&port, &place, &edx, 1, ebx, 5, edi, ebp);
        esi = 0;
        edi += edx * 5;
    }
    if (reuse & 2)
    {
        zero_fields(&port, &place, 5);
    }
    else
    {
        edx = 5;
        read_counted(&port, &place, &edx, ebx, esi, edi, ebp);
        edi += ebx * 5;
    }
    if (reuse & 1)
    {
        zero_fields(&port, &place, 5);
    }
    else
    {
        edx = 5;
        read_counted(&port, &place, &edx, ebx, esi, edi, ebp);
        edi += ebx * 5;
    }
    port_set32(&port, place, 0, 0);
    return port_return(&port, edi, edx);
}
