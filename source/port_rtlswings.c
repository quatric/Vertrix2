#include "port_rtlswings.h"

/* Actors swinging along their paths. */

/* Original 0x4443d0: the actor eax on its path (0x4ac600): while the path is not over (0x4ac620)
 * its steps go (0x4ac640 into 0x544988, 0x4ac6b0, 0x4ad5e0 into 0x544980; with a negative length
 * +0x30 the step runs with its speed +0x32 reversed and +0x30 cleared, both restored after); its
 * corner (0x4ad260 into 0x544970/0x544972) set at +0xe/+0x16, its travel +0x2a (0x544978) against
 * its length +0x30 (0x544974) fades it in over the first 40 (+0x44, 16 after that until the last
 * stretch, 0x54497c); a finished actor is stopped (0x4ac8f0). edx kept. */
uint32_t vertrix_port_actor_swing_4443d0(PORT_SIGNATURE)
{
    Port port;
    uint32_t actor = entry->eax;
    uint32_t eax;
    uint32_t ebx = entry->ebx;
    uint32_t esi = entry->esi;
    uint32_t travel;
    port_open(&port, calls, services, globals, entry);
#define CALL(target, a, d) port_forward_esi(&port, entry, target, a, d, ebx, actor, esi)
    port_set32(&port, 0, 0x544980, 1);
    CALL(0x4ac600, actor, 1);
    eax = CALL(0x4ac620, actor, vertrix_lift_edx);
    if (eax == vertrix_lift_edx)
    {
        port_set32(&port, 0, 0x544988, CALL(0x4ac640, actor, vertrix_lift_edx));
        CALL(0x4ac6b0, actor, vertrix_lift_edx);
        if ((int32_t)port_u32(&port, actor, 0x30) >= 0)
        {
            port_set32(&port, 0, 0x544980, CALL(0x4ad5e0, actor, port_u32(&port, 0, 0x544988)));
        }
        else
        {
            uint32_t speed;
            port_set16(&port, 0, 0x544984, port_u16(&port, actor, 0x30));
            speed = (vertrix_lift_edx & 0xffff0000u) | port_u16(&port, actor, 0x32);
            port_set16(&port, actor, 0x32, 0u - speed);
            port_set16(&port, actor, 0x30, 0);
            port_set32(&port, 0, 0x544980, CALL(0x4ad5e0, actor, port_u32(&port, 0, 0x544988)));
            ebx = 0u - ((ebx & 0xffff0000u) | port_u16(&port, actor, 0x32));
            port_set16(&port, actor, 0x30, port_u16(&port, 0, 0x544984));
            port_set16(&port, actor, 0x32, ebx);
        }
    }
    ebx = 0x544972;
    CALL(0x4ad260, actor, 0x544970);
    port_set16(&port, actor, 0xe, port_u16(&port, 0, 0x544970));
    port_set16(&port, actor, 0x16, port_u16(&port, 0, 0x544972));
    port_set32(&port, 0, 0x544978, (uint32_t)((int32_t)port_u32(&port, actor, 0x28) >> 16));
    port_set32(&port, 0, 0x544974, (uint32_t)((int32_t)port_u32(&port, actor, 0x2e) >> 16));
    eax = (uint32_t)((int32_t)port_u32(&port, actor, 0x30) >> 16);
    if ((int32_t)eax > 0)
    {
        travel = port_u32(&port, 0, 0x544978);
        ebx = travel;
        if (travel <= 0x28)
        {
            port_set8(&port, actor, 0x44, 0x10);
        }
        else
        {
            esi = port_u32(&port, 0, 0x544974);
            if (travel > esi)
            {
                port_set8(&port, actor, 0x44, 0);
            }
            else
            {
                LiftFlags flags = {0};
                uint32_t edx = 0;
                eax = (travel - 0x28) << 4;
                ebx = esi - 0x28;
                lift_div1(32, ebx, &eax, &edx, &flags);
                edx = 0x10 - eax;
                port_set32(&port, 0, 0x54497c, edx);
                eax = (int32_t)edx >= 0x10 ? 0x10 : edx;
                port_set8(&port, actor, 0x44, eax);
                eax = port_u8(&port, actor, 0x44);
                if ((int32_t)eax <= 0)
                {
                    eax = 0;
                }
                port_set8(&port, actor, 0x44, eax);
            }
        }
    }
    if (port_u32(&port, 0, 0x544980) == 0)
    {
        eax = CALL(0x4ac8f0, actor, 0);
    }
#undef CALL
    return port_return(&port, eax, entry->edx);
}

/* Original 0x44de20: the block actor eax orbiting (+0x95 3, 0x4ac1f0, period 5 by 0x4ac500): when
 * its period is up (0x4ac520) its steps (0x4ac540) are taken (0x4ac5b0), its place (0x4ad060) and
 * its orbit offset (0x4ad1c0 with 0x30 and 5) read; its fade +0x45 is 16 less the period's edx
 * plus the offset (at most 16), its corner +0x10/+0x18 the place less half the extent 0x4b14c0
 * gives; when no step is left (0x4aca60, 0x4acab0, 0x4acc10) it settles (handler 0x44dfb0 and its
 * resting fields); when its move ends (0x4ad6e0) it gets the handler 0x44c860. 0x4ac8a0 always
 * follows. edx kept. */
uint32_t vertrix_port_block_orbit_update_44de20(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x34
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t actor = entry->eax;
    uint32_t eax;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t edi = entry->edi;
    uint32_t edx;
    uint32_t fade;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -4u, entry->ebx);
    port_set32(&port, ebp, -8u, entry->ecx);
    port_set32(&port, ebp, -0xcu, entry->edx);
    port_set32(&port, ebp, -0x10u, entry->esi);
    port_set32(&port, ebp, -0x14u, entry->edi);
#define CALL(target, a, d) port_call_with(&port, target, a, d, ebx, ecx, actor, edi, ebp)
    port_set8(&port, actor, 0x95, 3);
    CALL(0x4ac1f0, actor, entry->edx);
    CALL(0x4ac500, actor, 5);
    port_set32(&port, ebp, -0x2cu, vertrix_lift_edx);
    eax = CALL(0x4ac520, actor, vertrix_lift_edx);
    if (eax == 1)
    {
        uint32_t steps = CALL(0x4ac540, actor, vertrix_lift_edx);
        edi = steps;
        eax = CALL(0x4ac5b0, actor, steps);
        port_set16(&port, ebp, -0x1cu, port_u16(&port, actor, 8));
        port_set16(&port, ebp, -0x18u, port_u16(&port, actor, 0xa));
        ecx = ebp - 0x30;
        CALL(0x4ad060, actor, vertrix_lift_edx);
        ebx = 5;
        {
            uint32_t args[1] = {ebp - 0x28};
            vertrix_lift_in_esi = actor;
            vertrix_lift_in_edi = edi;
            vertrix_lift_in_ebp = ebp;
            lift_call_arguments(&port.env, 0x4ad1c0, actor, 0x30, ebx, ecx, args, 1);
            vertrix_lift_in_esi = vertrix_lift_in_edi = vertrix_lift_in_ebp = 0;
        }
        fade = (0x10 - port_u8(&port, ebp, -0x2cu) + port_u8(&port, ebp, -0x28u)) & 0xff;
        if ((int32_t)fade >= 0x10)
        {
            fade = 0x10;
        }
        ecx = (ecx & 0xffffff00u) | fade;
        port_set32(&port, ebp, -0x24u, 0);
        port_set32(&port, ebp, -0x20u, 0);
        ebx = ebp - 0x20;
        CALL(0x4b14c0, actor, ebp - 0x24);
        edx = port_u32(&port, ebp, -0x30u) +
              (uint32_t)(int32_t)(int16_t)port_u16(&port, ebp, -0x1cu) -
              (port_u32(&port, ebp, -0x24u) >> 1);
        port_set16(&port, ebp, -0x1cu, edx);
        edx = (uint32_t)(int32_t)(int16_t)port_u16(&port, ebp, -0x18u) -
              (port_u32(&port, ebp, -0x20u) >> 1);
        eax = port_u32(&port, ebp, -0x1cu);
        port_set16(&port, ebp, -0x18u, edx);
        port_set16(&port, actor, 0x18, edx);
        port_set16(&port, actor, 0x10, eax);
        port_set8(&port, actor, 0x45, fade);
        ebx = CALL(0x4aca60, actor, steps);
        ecx = CALL(0x4acab0, actor, steps);
        eax = CALL(0x4acc10, actor, steps);
        if (ebx == 0 && ecx == 0 && eax == 0)
        {
            CALL(0x4ac8f0, actor, 0x44dfb0);
            port_set32(&port, actor, 0x64, 0x30);
            port_set32(&port, actor, 0x6c, 5);
            port_set16(&port, actor, 0x18, 0);
            port_set16(&port, actor, 0x12, 6);
            port_set16(&port, actor, 0x1a, 6);
            port_set16(&port, actor, 0x28, 0xf);
            port_set16(&port, actor, 0x4a, 0x64);
            port_set16(&port, actor, 0x4c, 5);
        }
        if (CALL(0x4ad6e0, actor, steps) == 0)
        {
            CALL(0x4ac8f0, actor, 0x44c860);
        }
    }
    eax = CALL(0x4ac8a0, actor, vertrix_lift_edx);
#undef CALL
    return port_return(&port, eax, entry->edx);
}
