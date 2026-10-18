#include "swoops.h"

/* The title letters' rise, return, fall and land steps. */

static uint32_t high16(uint32_t value)
{
    return (uint32_t)((int32_t)value >> 16);
}

/* Original 0x457d10: the letter eax's rise: when due (0x4ac500, 0x4ac520) it moves by the time
 * 0x4ac540 (0x4ac5b0) from its place +8, +0xa (kept at +0x2c, +0x2e; 0x4ad060, 0x4ad260); its
 * fade +0x44 is 16 - height * 16 / 160 (0 above 160, with +0x48 cleared); it is drawn there
 * (0x457890) and put back, +0x2a turned by +0x32 times the time and bobbed (0x4ad530); faded
 * out it stops (0x4ac8f0 with 0). */
uint32_t vertrix_port_letter_rise_457d10(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x24
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t actor = entry->eax;
    uint32_t time;
    uint32_t eax;
    uint32_t edi;
    uint32_t ebx = ebp - 0x18;
    uint32_t edx;
    uint32_t height;
    uint32_t fade;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_call_with(&port, 0x4ac500, actor, entry->edx, entry->ebx, actor, entry->esi, entry->edi,
                   ebp);
    eax = port_call_with(&port, 0x4ac520, actor, vertrix_lift_edx, entry->ebx, actor, entry->esi,
                         entry->edi, ebp);
    if (eax != 1)
    {
        return port_return(&port, eax, entry->edx);
    }
    time = port_call_with(&port, 0x4ac540, actor, vertrix_lift_edx, entry->ebx, actor, entry->esi,
                          entry->edi, ebp);
    eax = port_call_with(&port, 0x4ac5b0, actor, time, entry->ebx, actor, time, entry->edi, ebp);
    port_set16(&port, actor, 0xe, port_u16(&port, actor, 8));
    port_set16(&port, actor, 0x16, port_u16(&port, actor, 0xa));
    port_set16(&port, actor, 8, port_u16(&port, actor, 0xe));
    eax = (eax & 0xffff0000u) | port_u16(&port, actor, 0x16);
    edi = (entry->edi & 0xffff0000u) | port_u16(&port, actor, 8);
    port_set16(&port, actor, 0xa, eax);
    port_set32(&port, ebp, -0x20u, eax);
    port_set16(&port, actor, 0x2e, eax);
    port_set16(&port, actor, 0x2c, edi);
    port_call_with(&port, 0x4ad060, actor, vertrix_lift_edx, ebx, actor, time, edi, ebp);
    port_call_with(&port, 0x4ad260, actor, ebp - 0x1c, ebx, actor, time, edi, ebp);
    edx = vertrix_lift_edx;
    height = high16(port_u32(&port, actor, 0x28));
    if (height <= 0xa0)
    {
        ebx = 0xa0;
        edx = 0x10 - height * 16 / 0xa0;
        fade = (int32_t)edx >= 0x10 ? 0x10 : edx;
        port_set8(&port, actor, 0x44, fade);
    }
    else
    {
        port_set8(&port, actor, 0x44, 0);
        port_set16(&port, actor, 0x48, 0);
    }
    port_set16(&port, actor, 8, port_u32(&port, ebp, -0x1cu));
    port_set16(&port, actor, 0xa, port_u32(&port, ebp, -0x18u));
    eax = port_call_with(&port, 0x457890, actor, edx, ebx, actor, time, edi, ebp);
    port_set16(&port, actor, 0xa, port_u32(&port, ebp, -0x20u));
    eax = ((eax & 0xffff0000u) | port_u16(&port, actor, 0x32)) * time;
    port_set16(&port, actor, 0x2a, port_u16(&port, actor, 0x2a) + eax);
    port_set16(&port, actor, 8, edi);
    eax = port_call_with(&port, 0x4ad530, actor, time, ebx, actor, time, edi, ebp);
    if (port_u8(&port, actor, 0x44) != 0)
    {
        return port_return(&port, eax, entry->edx);
    }
    eax = port_call_with(&port, 0x4ac8f0, actor, 0, ebx, actor, time, edi, ebp);
    return port_return(&port, eax, entry->edx);
}

/* Original 0x458150: the letter eax's return home (0x457810, +0xc cleared): when due it moves by
 * the time (0x4ac540, 0x4ac5b0; 0x4aca60, 0x4acab0 from +8, +0xa) and, both arrived, slows
 * (0x4ac7d0 with 20) into the state 0x458260 (+0x93 and +0x48 cleared, +0x4a 100, +0x4c 5); its
 * fade +0x44 is 16 - distance squared from home (+0x10 - +8, +0x18 - +0xa) * 16 / 320000, 0
 * beyond. Then 0x457890. */
uint32_t vertrix_port_letter_return_458150(PORT_SIGNATURE)
{
    Port port;
    uint32_t actor = entry->eax;
    uint32_t ebx = entry->ebx;
    uint32_t esi = entry->esi;
    uint32_t time;
    uint32_t across;
    uint32_t down;
    int32_t across_raw;
    int32_t down_raw;
    uint32_t distance;
    uint32_t edx;
    uint32_t eax;
    port_open(&port, calls, services, globals, entry);
    port_call_with(&port, 0x457810, actor, entry->edx, ebx, actor, esi, entry->edi, entry->ebp);
    port_set16(&port, actor, 0xc, 0);
    port_call_with(&port, 0x4ac500, actor, vertrix_lift_edx, ebx, actor, esi, entry->edi,
                   entry->ebp);
    if (port_call_with(&port, 0x4ac520, actor, vertrix_lift_edx, ebx, actor, esi, entry->edi,
                       entry->ebp) == 1)
    {
        uint32_t moved;
        time = port_call_with(&port, 0x4ac540, actor, vertrix_lift_edx, ebx, actor, esi, entry->edi,
                              entry->ebp);
        port_call_with(&port, 0x4ac5b0, actor, vertrix_lift_edx, time, actor, esi, entry->edi,
                       entry->ebp);
        port_set16(&port, actor, 0xe, port_u16(&port, actor, 8));
        port_set16(&port, actor, 0x16, port_u16(&port, actor, 0xa));
        esi =
            port_call_with(&port, 0x4aca60, actor, time, time, actor, esi, entry->edi, entry->ebp);
        moved =
            port_call_with(&port, 0x4acab0, actor, time, time, actor, esi, entry->edi, entry->ebp);
        port_set16(&port, actor, 8, port_u16(&port, actor, 0xe));
        ebx = (time & 0xffff0000u) | port_u16(&port, actor, 0x16);
        port_set16(&port, actor, 0xa, ebx);
        if (esi == 0 && moved == 0)
        {
            port_call_with(&port, 0x4ac7d0, actor, 0x14, ebx, actor, esi, entry->edi, entry->ebp);
            port_call_with(&port, 0x4ac8f0, actor, 0x458260, ebx, actor, esi, entry->edi,
                           entry->ebp);
            port_set8(&port, actor, 0x93, 0);
            port_set16(&port, actor, 0x48, 0);
            port_set16(&port, actor, 0x4a, 0x64);
            port_set16(&port, actor, 0x4c, 5);
        }
    }
    across_raw = (int32_t)(high16(port_u32(&port, actor, 0xe)) - high16(port_u32(&port, actor, 6)));
    across = across_raw < 0 ? 0u - (uint32_t)across_raw : (uint32_t)across_raw;
    esi = high16(port_u32(&port, actor, 8));
    down_raw = (int32_t)(high16(port_u32(&port, actor, 0x16)) - esi);
    down = down_raw < 0 ? 0u - (uint32_t)down_raw : (uint32_t)down_raw;
    ebx = across * across;
    distance = down * down + ebx;
    if (distance > 0x4e200)
    {
        port_set8(&port, actor, 0x44, 0);
        edx = down_raw < 0 ? 0xffffffffu : 0;
    }
    else
    {
        edx = distance * 16 % 0x4e200;
        ebx = 0x10 - distance * 16 / 0x4e200;
        port_set8(&port, actor, 0x44, ebx);
    }
    eax = port_call_with(&port, 0x457890, actor, edx, ebx, actor, esi, entry->edi, entry->ebp);
    return port_return(&port, eax, entry->edx);
}

/* Original 0x458c20: the letter eax's fall: when due it moves by the time (0x4ac540, 0x4ac5b0,
 * 0x4ad060) to its place (0x4ad260); its fade +0x44 is +0x45 less +0x45 * height / 160 (0 above
 * 160, with +0x48 cleared); centred by its size (0x4b14c0) into +0xe and +0x16; a finished fall
 * (0x4ad750 of 0) clears +0x64 and turns +0x2a by the time; it bobs (0x4ad530) and, faded out,
 * stops (0x4ac8f0 with 0). */
uint32_t vertrix_port_letter_fall_458c20(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x28
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t actor = entry->eax;
    uint32_t edi = entry->edi;
    uint32_t time;
    uint32_t height;
    uint32_t base;
    uint32_t fade;
    uint32_t eax;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_call_with(&port, 0x4ac500, actor, entry->edx, entry->ebx, actor, entry->esi, edi, ebp);
    eax = port_call_with(&port, 0x4ac520, actor, vertrix_lift_edx, entry->ebx, actor, entry->esi,
                         edi, ebp);
    if (eax != 1)
    {
        return port_return(&port, eax, entry->edx);
    }
    time = port_call_with(&port, 0x4ac540, actor, vertrix_lift_edx, entry->ebx, actor, entry->esi,
                          edi, ebp);
    port_call_with(&port, 0x4ac5b0, actor, time, entry->ebx, actor, time, edi, ebp);
    port_call_with(&port, 0x4ad060, actor, vertrix_lift_edx, ebp - 0x1c, actor, time, edi, ebp);
    port_call_with(&port, 0x4ad260, actor, ebp - 0x18, ebp - 0x1c, actor, time, edi, ebp);
    height = high16(port_u32(&port, actor, 0x28));
    if (height <= 0xa0)
    {
        base = port_u8(&port, actor, 0x45);
        fade = base - base * height / 0xa0;
        if ((int32_t)fade >= (int32_t)base)
        {
            fade = base;
        }
        port_set8(&port, actor, 0x44, fade);
        edi = 0xa0;
    }
    else
    {
        port_set8(&port, actor, 0x44, 0);
        port_set16(&port, actor, 0x48, 0);
    }
    port_set32(&port, ebp, -0x24u, 0);
    port_set32(&port, ebp, -0x20u, 0);
    port_call_with(&port, 0x4b14c0, actor, ebp - 0x24, ebp - 0x20, actor, time, edi, ebp);
    port_set16(&port, actor, 0xe,
               high16(port_u32(&port, ebp, -0x1au)) - (port_u32(&port, ebp, -0x24u) >> 1));
    port_set16(&port, actor, 0x16,
               high16(port_u32(&port, ebp, -0x1eu)) - (port_u32(&port, ebp, -0x20u) >> 1));
    if (port_call_with(&port, 0x4ad750, actor, time, ebp - 0x20, actor, time, edi, ebp) == 0)
    {
        port_set32(&port, actor, 0x64, 0);
        port_set16(&port, actor, 0x2a, port_u16(&port, actor, 0x2a) + time);
    }
    eax = port_call_with(&port, 0x4ad530, actor, time, ebp - 0x20, actor, time, edi, ebp);
    if (port_u8(&port, actor, 0x44) != 0)
    {
        return port_return(&port, eax, entry->edx);
    }
    eax = port_call_with(&port, 0x4ac8f0, actor, 0, ebp - 0x20, actor, time, edi, ebp);
    return port_return(&port, eax, entry->edx);
}

/* Original 0x459290: the letter eax's landing: when due it moves by the time (0x4ac540,
 * 0x4ac5b0; 0x4acab0 from +8, +0xa) and is centred by its size (0x4b14c0) on that place; a
 * finished drop (0x4ad750 of 0) clears +0x64 and restarts it (0x4acc10 with 1); a finished turn
 * (0x4ad790 of 0) clears +0x70 and steps +0x1a; once landed (0x4acab0 of 0) it takes the state
 * 0x4593b0 with +0x1a 4, +0x70 80, +0x48 80, +0x4a 0, +0x4c 5 and +0x18 375. */
uint32_t vertrix_port_letter_land_459290(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x24
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t actor = entry->eax;
    uint32_t time;
    uint32_t eax;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_call_with(&port, 0x4ac500, actor, entry->edx, entry->ebx, actor, entry->esi, entry->edi,
                   ebp);
    eax = port_call_with(&port, 0x4ac520, actor, vertrix_lift_edx, entry->ebx, actor, entry->esi,
                         entry->edi, ebp);
    if (eax != 1)
    {
        return port_return(&port, eax, entry->edx);
    }
    time = port_call_with(&port, 0x4ac540, actor, vertrix_lift_edx, entry->ebx, actor, entry->esi,
                          entry->edi, ebp);
    port_call_with(&port, 0x4ac5b0, actor, vertrix_lift_edx, entry->ebx, actor, time, time, ebp);
    port_set16(&port, actor, 0xe, port_u16(&port, actor, 8));
    port_set16(&port, actor, 0x16, port_u16(&port, actor, 0xa));
    port_set32(&port, ebp, -0x18u,
               port_call_with(&port, 0x4acab0, actor, time, entry->ebx, actor, time, time, ebp));
    port_set16(&port, actor, 8, port_u16(&port, actor, 0xe));
    port_set16(&port, actor, 0xa, port_u16(&port, actor, 0x16));
    port_set32(&port, ebp, -0x20u, 0);
    port_set32(&port, ebp, -0x1cu, 0);
    port_call_with(&port, 0x4b14c0, actor, ebp - 0x20, ebp - 0x1c, actor, time, time, ebp);
    port_set16(&port, actor, 0xe,
               high16(port_u32(&port, actor, 6)) - (port_u32(&port, ebp, -0x20u) >> 1));
    port_set16(&port, actor, 0x16,
               high16(port_u32(&port, actor, 8)) - (port_u32(&port, ebp, -0x1cu) >> 1));
    if (port_call_with(&port, 0x4ad750, actor, time, ebp - 0x1c, actor, time, time, ebp) == 0)
    {
        port_set32(&port, actor, 0x64, 0);
        port_call_with(&port, 0x4acc10, actor, 1, ebp - 0x1c, actor, time, time, ebp);
    }
    eax = port_call_with(&port, 0x4ad790, actor, time, ebp - 0x1c, actor, time, time, ebp);
    if (eax == 0)
    {
        port_set32(&port, actor, 0x70, 0);
        port_set16(&port, actor, 0x1a, port_u16(&port, actor, 0x1a) + 1);
    }
    if (port_u32(&port, ebp, -0x18u) != 0)
    {
        return port_return(&port, eax, entry->edx);
    }
    eax = port_call_with(&port, 0x4ac8f0, actor, 0x4593b0, ebp - 0x1c, actor, time, time, ebp);
    port_set16(&port, actor, 0x1a, 4);
    port_set32(&port, actor, 0x70, 0x50);
    port_set16(&port, actor, 0x48, 0x50);
    port_set16(&port, actor, 0x4a, 0);
    eax = (eax & 0xffff0000u) | port_u16(&port, actor, 0x70);
    port_set16(&port, actor, 0x4c, 5);
    port_set16(&port, actor, 0x18, 0x1c7 - eax);
    return port_return(&port, eax, entry->edx);
}
