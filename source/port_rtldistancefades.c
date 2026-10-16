#include "port_rtldistancefades.h"

/* Actors that fade with their distance. */

/* A call that leaves its eax and edx in *eax and *edx; the eax. */
static uint32_t fade_call(Port *port, uint32_t *eax, uint32_t *edx, uint32_t target, uint32_t a,
                          uint32_t d, uint32_t ebx, uint32_t ecx, uint32_t esi, uint32_t edi,
                          uint32_t ebp)
{
    *eax = port_call_with(port, target, a, d, ebx, ecx, esi, edi, ebp);
    *edx = vertrix_lift_edx;
    return *eax;
}

/* Original 0x443550: one step of the actor eax: 0x5448ac 1, 0x4ac500, 0x4ac600; when 0x4ac620
 * gives what it leaves in edx, 0x4ac640 (kept at 0x5448b4) and 0x4ac6b0, then 0x4ad5e0 with it
 * into 0x5448ac, a rising speed (+0x32 negative) flipped for it (+0x30 0 and +0x32 negated, put
 * back after). Moving (0x4ac520 1) by its speed (0x4ac540, 0x4ac5b0, 0x4ad060). Its spot
 * (0x4ad260 into 0x54489c/0x54489e) is +0xe/+0x16; its distance +0x2a (0x5448a4) against +0x64
 * and +0x30 (0x5448a0): within +0x64 the shade +0x44 is 0x10, beyond +0x30 0 and it is handed 0
 * (0x4ac8f0), between 0x10 - (distance - near) * 16 / (far - near) (0x5448a8), 0..0x10; a shade
 * of 0 or 0x5448ac 0 hands it 0. edx kept. */
uint32_t vertrix_port_actor_distance_fade_443550(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x10
    };
    Port port;
    uint32_t ebp = entry->ebp;
    uint32_t actor = entry->eax;
    uint32_t eax;
    uint32_t edx = 1;
    uint32_t ebx = entry->ebx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t near;
    uint32_t far;
    uint32_t shade;
#define CALL(target, a, d) fade_call(&port, &eax, &edx, target, a, d, ebx, actor, esi, edi, ebp)
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, entry->esp, -4u, entry->ebx);
    port_set32(&port, entry->esp, -8u, entry->ecx);
    port_set32(&port, entry->esp, -0xcu, entry->edx);
    port_set32(&port, entry->esp, -0x10u, entry->esi);
    port_set32(&port, 0, 0x5448ac, edx);
    CALL(0x4ac500, actor, edx);
    CALL(0x4ac600, actor, edx);
    CALL(0x4ac620, actor, edx);
    if (eax == edx)
    {
        port_set32(&port, 0, 0x5448b4, CALL(0x4ac640, actor, edx));
        CALL(0x4ac6b0, actor, edx);
        if ((int16_t)port_u16(&port, actor, 0x32) >= 0)
        {
            port_set32(&port, 0, 0x5448ac, CALL(0x4ad5e0, actor, port_u32(&port, 0, 0x5448b4)));
        }
        else
        {
            port_set16(&port, 0, 0x5448b0, port_u16(&port, actor, 0x30));
            port_set16(&port, actor, 0x32, 0u - port_u16(&port, actor, 0x32));
            port_set16(&port, actor, 0x30, 0);
            port_set32(&port, 0, 0x5448ac, CALL(0x4ad5e0, actor, port_u32(&port, 0, 0x5448b4)));
            ebx = 0u - ((ebx & 0xffff0000u) | port_u16(&port, actor, 0x32));
            port_set16(&port, actor, 0x30, port_u16(&port, 0, 0x5448b0));
            port_set16(&port, actor, 0x32, ebx);
        }
    }
    if (CALL(0x4ac520, actor, edx) == 1)
    {
        port_set32(&port, 0, 0x5448b4, CALL(0x4ac540, actor, edx));
        CALL(0x4ac5b0, actor, edx);
        CALL(0x4ad060, actor, port_u32(&port, 0, 0x5448b4));
    }
    ebx = 0x54489e;
    CALL(0x4ad260, actor, 0x54489c);
    port_set16(&port, actor, 0xe, port_u16(&port, 0, 0x54489c));
    port_set16(&port, actor, 0x16, port_u16(&port, 0, 0x54489e));
    eax = (uint32_t)(int32_t)(int16_t)port_u16(&port, actor, 0x2a);
    port_set32(&port, 0, 0x5448a4, eax);
    far = (uint32_t)(int32_t)(int16_t)port_u16(&port, actor, 0x30);
    near = port_u32(&port, actor, 0x64);
    ebx = near;
    port_set32(&port, 0, 0x5448a0, far);
    if (eax <= near)
    {
        port_set8(&port, actor, 0x44, 0x10);
        if (port_u32(&port, 0, 0x5448ac) != 0)
        {
            return port_return(&port, eax, entry->edx);
        }
    }
    else if (eax > far)
    {
        esi = far;
        port_set8(&port, actor, 0x44, 0);
    }
    else
    {
        esi = far - near;
        edx = 0;
        eax = ((eax - near) << 4) / esi;
        edx = 0x10 - eax;
        port_set32(&port, 0, 0x5448a8, edx);
        shade = (int32_t)edx >= 0x10 ? 0x10 : edx;
        port_set8(&port, actor, 0x44, shade);
        eax = port_u8(&port, actor, 0x44);
        if ((int32_t)eax <= 0)
        {
            eax = 0;
        }
        port_set8(&port, actor, 0x44, eax);
        if ((eax & 0xff) != 0 && port_u32(&port, 0, 0x5448ac) != 0)
        {
            return port_return(&port, eax, entry->edx);
        }
    }
    CALL(0x4ac8f0, actor, 0);
#undef CALL
    return port_return(&port, eax, entry->edx);
}
