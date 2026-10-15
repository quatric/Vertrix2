#include "port_drifts.h"

/* The blocks' drift, fall and spin steps. */

static uint32_t sign16(uint32_t value)
{
    return (uint32_t)(int32_t)(int16_t)value;
}

static uint32_t high16(uint32_t value)
{
    return (uint32_t)((int32_t)value >> 16);
}

/* Original 0x44dcf0: the block eax's drift step (+0x95 3; 0x4ac1f0): when due (0x4ac500,
 * 0x4ac520) the time 0x4ac540 adds to +0x58 (0x4ac5b0); past +0x64 it restarts, +0x1a goes up,
 * the bob +0x4a -200, +0x4c 30 (0x4ad530), +0x45 0, +0x46 1, the drift (0x4acc10; 0x44c860 when
 * done) moves +0xe and +0x16 by +0x12 and +0x1a times the time, and leaving the bounds +0xa8 to
 * +0xae gives the state 0x44c860. Then 0x4ac8a0. */
uint32_t vertrix_port_block_drift_step_44dcf0(PORT_SIGNATURE)
{
    Port port;
    uint32_t actor = entry->eax;
    uint32_t time;
    uint32_t sum;
    uint32_t limit;
    uint32_t eax;
    uint32_t x;
    uint32_t y;
    uint32_t ebx;
    uint32_t esi;
    uint32_t edi;
    uint32_t edx;
    port_open(&port, calls, services, globals, entry);
    port_set8(&port, actor, 0x95, 3);
    port_call_with(&port, 0x4ac1f0, actor, entry->edx, entry->ebx, actor, entry->esi, entry->edi,
                   entry->ebp);
    port_call_with(&port, 0x4ac500, actor, vertrix_lift_edx, entry->ebx, actor, entry->esi,
                   entry->edi, entry->ebp);
    if (port_call_with(&port, 0x4ac520, actor, vertrix_lift_edx, entry->ebx, actor, entry->esi,
                       entry->edi, entry->ebp) != 1)
    {
        eax = port_call_with(&port, 0x4ac8a0, actor, vertrix_lift_edx, entry->ebx, actor,
                             entry->esi, entry->edi, entry->ebp);
        return port_return(&port, eax, entry->edx);
    }
    time = port_call_with(&port, 0x4ac540, actor, vertrix_lift_edx, entry->ebx, actor, entry->esi,
                          entry->edi, entry->ebp);
    port_call_with(&port, 0x4ac5b0, actor, vertrix_lift_edx, time, actor, time, entry->edi,
                   entry->ebp);
    sum = port_u32(&port, actor, 0x58) + time;
    limit = port_u32(&port, actor, 0x64);
    port_set32(&port, actor, 0x58, sum);
    if ((int32_t)sum <= (int32_t)limit)
    {
        eax = port_call_with(&port, 0x4ac8a0, actor, sum, time, actor, time, limit, entry->ebp);
        return port_return(&port, eax, entry->edx);
    }
    port_set32(&port, actor, 0x58, 0);
    port_set16(&port, actor, 0x4a, 0xff38);
    port_set16(&port, actor, 0x1a, port_u16(&port, actor, 0x1a) + 1);
    port_set16(&port, actor, 0x4c, 0x1e);
    port_call_with(&port, 0x4ad530, actor, time, time, actor, time, limit, entry->ebp);
    port_set8(&port, actor, 0x45, 0);
    port_set16(&port, actor, 0x46, 1);
    eax = port_call_with(&port, 0x4acc10, actor, time, time, actor, time, limit, entry->ebp);
    if (eax == 0)
    {
        eax =
            port_call_with(&port, 0x4ac8f0, actor, 0x44c860, time, actor, time, limit, entry->ebp);
    }
    eax = ((eax & 0xffff0000u) | port_u16(&port, actor, 0x12)) * time;
    port_set16(&port, actor, 0xe, port_u16(&port, actor, 0xe) + eax);
    port_set16(&port, actor, 0x16,
               port_u16(&port, actor, 0x16) + time * port_u16(&port, actor, 0x1a));
    edx = high16(port_u32(&port, actor, 0xa8));
    x = high16(port_u32(&port, actor, 0xc));
    y = high16(port_u32(&port, actor, 0x14));
    edi = x + 0x17;
    esi = y + 0x17;
    ebx = x;
    if ((int32_t)x <= (int32_t)edx)
    {
        ebx = high16(port_u32(&port, actor, 0xa6));
        if ((int32_t)edi >= (int32_t)ebx)
        {
            ebx = high16(port_u32(&port, actor, 0xac));
            if ((int32_t)y <= (int32_t)ebx &&
                (int32_t)esi >= (int32_t)high16(port_u32(&port, actor, 0xaa)))
            {
                eax = port_call_with(&port, 0x4ac8a0, actor, edx, ebx, actor, esi, edi, entry->ebp);
                return port_return(&port, eax, entry->edx);
            }
        }
    }
    port_call_with(&port, 0x4ac8f0, actor, 0x44c860, ebx, actor, esi, edi, entry->ebp);
    eax =
        port_call_with(&port, 0x4ac8a0, actor, vertrix_lift_edx, ebx, actor, esi, edi, entry->ebp);
    return port_return(&port, eax, entry->edx);
}

/* Original 0x44e120: the block eax's fall step (0x4ac1f0): when due (0x4ac500, 0x4ac520) it
 * moves by the time 0x4ac540 (0x4ac5b0, 0x4ad060) to its place (0x4ad260); its fade +0x44 is
 * height * 16 / 78 up to 16 (16 above 78, with +0x48 cleared); it is centred by its size
 * (0x4b14c0) into +0xe and +0x16; when the fall ends (0x4ad750 of 0) +0x64 is cleared and +0x2a
 * slowed by the time (0 when the height is negative); a landing (0x4ad6e0 of 0) or a stop gives
 * the state 0x44c860. Then 0x4ac8a0. */
uint32_t vertrix_port_block_fall_step_44e120(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x24
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t actor = entry->eax;
    uint32_t time;
    uint32_t height;
    uint32_t fade;
    uint32_t eax;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_call_with(&port, 0x4ac1f0, actor, entry->edx, entry->ebx, actor, entry->esi, entry->edi,
                   ebp);
    port_call_with(&port, 0x4ac500, actor, vertrix_lift_edx, entry->ebx, actor, entry->esi,
                   entry->edi, ebp);
    if (port_call_with(&port, 0x4ac520, actor, vertrix_lift_edx, entry->ebx, actor, entry->esi,
                       entry->edi, ebp) != 1)
    {
        eax = port_call_with(&port, 0x4ac8a0, actor, vertrix_lift_edx, entry->ebx, actor,
                             entry->esi, entry->edi, ebp);
        return port_return(&port, eax, entry->edx);
    }
    time = port_call_with(&port, 0x4ac540, actor, vertrix_lift_edx, entry->ebx, actor, entry->esi,
                          entry->edi, ebp);
    port_call_with(&port, 0x4ac5b0, actor, time, entry->ebx, actor, time, entry->edi, ebp);
    port_call_with(&port, 0x4ad060, actor, vertrix_lift_edx, ebp - 0x18, actor, time, entry->edi,
                   ebp);
    port_call_with(&port, 0x4ad260, actor, ebp - 0x14, ebp - 0x18, actor, time, entry->edi, ebp);
    height = high16(port_u32(&port, actor, 0x28));
    if (height <= 0x4e)
    {
        fade = height * 16 / 0x4e;
        if ((int32_t)fade >= 0x10)
        {
            fade = 0x10;
        }
        port_set8(&port, actor, 0x44, fade);
    }
    else
    {
        port_set8(&port, actor, 0x44, 0x10);
        port_set16(&port, actor, 0x48, 0);
    }
    port_set32(&port, ebp, -0x20u, 0);
    port_set32(&port, ebp, -0x1cu, 0);
    port_call_with(&port, 0x4b14c0, actor, ebp - 0x20, ebp - 0x1c, actor, time, entry->edi, ebp);
    port_set16(&port, actor, 0xe,
               sign16(port_u32(&port, ebp, -0x14u)) - (port_u32(&port, ebp, -0x20u) >> 1));
    port_set16(&port, actor, 0x16,
               sign16(port_u32(&port, ebp, -0x18u)) - (port_u32(&port, ebp, -0x1cu) >> 1));
    if (port_call_with(&port, 0x4ad750, actor, time, ebp - 0x1c, actor, time, entry->edi, ebp) == 0)
    {
        port_set32(&port, actor, 0x64, 0);
        port_set16(&port, actor, 0x2a, port_u16(&port, actor, 0x2a) - time);
        if ((int32_t)port_u32(&port, actor, 0x28) < 0)
        {
            port_set16(&port, actor, 0x2a, 0);
        }
    }
    if (port_call_with(&port, 0x4ad6e0, actor, time, ebp - 0x1c, actor, time, entry->edi, ebp) ==
            0 ||
        port_u16(&port, actor, 0x2a) == 0)
    {
        port_call_with(&port, 0x4ac8f0, actor, 0x44c860, ebp - 0x1c, actor, time, entry->edi, ebp);
    }
    eax = port_call_with(&port, 0x4ac8a0, actor, vertrix_lift_edx, ebp - 0x1c, actor, time,
                         entry->edi, ebp);
    return port_return(&port, eax, entry->edx);
}

/* Original 0x44ece0: the block eax's spin step (+0x93 set; 0x4ac1f0): it slides when due
 * (0x4ac600, 0x4ac620, 0x4ac640, 0x4ac6b0) and moves when due (0x4ac500, 0x4ac520, 0x4ac540,
 * 0x4ac5b0); the slide (0x4ad5e0) and move (0x4ad060) are applied, the spin (+0x4f 0, +0x50 8;
 * 0x4ad580) run, and with all three done it takes the state 0x44c860; its fade +0x44 is
 * 16 - height * 16 / 100 up to 16; it is centred by its size (0x4b14c0) at its place (0x4ad260)
 * into +0xe and +0x16. Then 0x4ac8a0. */
uint32_t vertrix_port_block_spin_update_44ece0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x28
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t actor = entry->eax;
    uint32_t slide = 0;
    uint32_t time = 0;
    uint32_t slid;
    uint32_t spun;
    uint32_t fade;
    uint32_t y;
    uint32_t eax;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set8(&port, actor, 0x93, 1);
    port_call_with(&port, 0x4ac1f0, actor, entry->edx, entry->ebx, actor, entry->esi, entry->edi,
                   ebp);
    port_call_with(&port, 0x4ac600, actor, vertrix_lift_edx, 0, actor, entry->esi, entry->edi, ebp);
    if (port_call_with(&port, 0x4ac620, actor, vertrix_lift_edx, 0, actor, 0, entry->edi, ebp) == 1)
    {
        slide =
            port_call_with(&port, 0x4ac640, actor, vertrix_lift_edx, 0, actor, 0, entry->edi, ebp);
        port_call_with(&port, 0x4ac6b0, actor, vertrix_lift_edx, slide, actor, 0, entry->edi, ebp);
    }
    port_call_with(&port, 0x4ac500, actor, vertrix_lift_edx, slide, actor, 0, entry->edi, ebp);
    if (port_call_with(&port, 0x4ac520, actor, vertrix_lift_edx, slide, actor, 0, entry->edi,
                       ebp) == 1)
    {
        time = port_call_with(&port, 0x4ac540, actor, vertrix_lift_edx, slide, actor, 0, entry->edi,
                              ebp);
        port_call_with(&port, 0x4ac5b0, actor, vertrix_lift_edx, slide, actor, time, entry->edi,
                       ebp);
    }
    slid = port_call_with(&port, 0x4ad5e0, actor, slide, slide, actor, time, entry->edi, ebp);
    port_call_with(&port, 0x4ad060, actor, slide, slide, actor, time, slid, ebp);
    port_set8(&port, actor, 0x4f, 0);
    port_set16(&port, actor, 0x50, 8);
    spun = port_call_with(&port, 0x4ad580, actor, time, slide, actor, time, slid, ebp);
    if (slid == 0 && spun == 0)
    {
        port_call_with(&port, 0x4ac8f0, actor, 0x44c860, slide, actor, time, slid, ebp);
    }
    fade = 0x10 - high16(port_u32(&port, actor, 0x28)) * 16 / 0x64;
    if ((int32_t)fade >= 0x10)
    {
        fade = 0x10;
    }
    port_set8(&port, actor, 0x44, fade);
    port_set32(&port, ebp, -0x24u, 0);
    port_set32(&port, ebp, -0x20u, 0);
    port_call_with(&port, 0x4b14c0, actor, ebp - 0x24, ebp - 0x20, actor, time, slid, ebp);
    port_call_with(&port, 0x4ad260, actor, ebp - 0x18, ebp - 0x1c, actor, time, slid, ebp);
    port_set16(&port, actor, 0xe,
               sign16(port_u32(&port, ebp, -0x18u)) - (port_u32(&port, ebp, -0x24u) >> 1));
    y = sign16(port_u32(&port, ebp, -0x1cu)) - (port_u32(&port, ebp, -0x20u) >> 1);
    port_set16(&port, actor, 0x16, y);
    eax = port_call_with(&port, 0x4ac8a0, actor, y, ebp - 0x1c, actor, time, slid, ebp);
    return port_return(&port, eax, entry->edx);
}
