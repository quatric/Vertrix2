#include "rtlflyins.h"

/* Actors flying in to rest. */

/* Original 0x4594a0: the actor eax, when due (0x4ac500, 0x4ac520 1), steps with its stride
 * (0x4ac540, 0x4ac5b0): from its place +8/+0xa held at +0xe/+0x16 it tries both ways (0x4aca60,
 * 0x4acab0), is put back (0x4ad530) and measured (0x4b14c0) to centre +0xe/+0x16 on its place.
 * Blocked across it stops (0x4ac8f0 with 0); free both ways it slows: +0x12 down by 2 to at least
 * 1, +0x1a 4, +0x70 halved to at least 1, +0x48 0x50, +0x4a 0, its depth +0x18 0x1c7 less +0x70,
 * +0x4c 5, 0x4acc10 with 2 and the step 0x4593b0 (0x4ac8f0). edx kept. */
uint32_t vertrix_port_actor_fly_in_4594a0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x20
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t actor = entry->eax;
    uint32_t eax;
    uint32_t ebx = entry->ebx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t stride;
    uint32_t speed;
    uint32_t half;
#define CALL(target, a, d) port_call_with(&port, target, a, d, ebx, actor, esi, edi, ebp)
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -4u, entry->ebx);
    port_set32(&port, ebp, -8u, entry->ecx);
    port_set32(&port, ebp, -0xcu, entry->edx);
    port_set32(&port, ebp, -0x10u, entry->esi);
    port_set32(&port, ebp, -0x14u, entry->edi);
    CALL(0x4ac500, actor, entry->edx);
    eax = CALL(0x4ac520, actor, vertrix_lift_edx);
    if (eax != 1)
    {
        return port_return(&port, eax, entry->edx);
    }
    stride = CALL(0x4ac540, actor, vertrix_lift_edx);
    ebx = stride;
    CALL(0x4ac5b0, actor, vertrix_lift_edx);
    port_set16(&port, actor, 0xe, port_u16(&port, actor, 8));
    port_set16(&port, actor, 0x16, port_u16(&port, actor, 0xa));
    esi = CALL(0x4aca60, actor, stride);
    edi = CALL(0x4acab0, actor, stride);
    port_set16(&port, actor, 8, port_u16(&port, actor, 0xe));
    port_set16(&port, actor, 0xa, port_u16(&port, actor, 0x16));
    ebx = ebp - 0x18;
    CALL(0x4ad530, actor, stride);
    port_set32(&port, ebp, -0x1cu, 0);
    port_set32(&port, ebp, -0x18u, 0);
    CALL(0x4b14c0, actor, ebp - 0x1c);
    port_set16(&port, actor, 0xe,
               (uint32_t)((int32_t)port_u32(&port, actor, 6) >> 16) -
                   (port_u32(&port, ebp, -0x1cu) >> 1));
    eax =
        (uint32_t)((int32_t)port_u32(&port, actor, 8) >> 16) - (port_u32(&port, ebp, -0x18u) >> 1);
    port_set16(&port, actor, 0x16, eax);
    if (esi == 0)
    {
        eax = CALL(0x4ac8f0, actor, 0);
        return port_return(&port, eax, entry->edx);
    }
    if (edi != 0)
    {
        return port_return(&port, eax, entry->edx);
    }
    port_set16(&port, actor, 0x12, port_u16(&port, actor, 0x12) - 2);
    speed = (uint32_t)((int32_t)port_u32(&port, actor, 0x10) >> 16);
    if ((int32_t)speed < 1)
    {
        speed = 1;
    }
    port_set16(&port, actor, 0x12, speed);
    half = (uint32_t)((int32_t)port_u32(&port, actor, 0x70) / 2);
    port_set16(&port, actor, 0x1a, 4);
    port_set32(&port, actor, 0x70, half);
    if ((int32_t)half < 1)
    {
        half = 1;
    }
    port_set16(&port, actor, 0x48, 0x50);
    port_set32(&port, actor, 0x70, half);
    port_set16(&port, actor, 0x4a, 0);
    port_set16(&port, actor, 0x18, 0x1c7 - port_u16(&port, actor, 0x70));
    port_set16(&port, actor, 0x4c, 5);
    CALL(0x4acc10, actor, 2);
    eax = CALL(0x4ac8f0, actor, 0x4593b0);
#undef CALL
    return port_return(&port, eax, entry->edx);
}
