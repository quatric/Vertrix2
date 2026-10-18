#include "turnsteps.h"

/* The actor turn steps. */

/* Original 0x4ace40: the angle +0x24 of eax turns toward +0x26 by its rate +0x28 times edx (kept
 * in 0x5bb5e4, negated when negative), the shorter way round a 360 turn; a step that would pass
 * the target lands on it, and an angle leaving 0..359 is brought back modulo 360. The angles (the
 * target or the angle raised by 360 for the turn) go to 0x5bb5dc and 0x5bb5e0; eax is 1 while
 * the target is not reached. */
uint32_t vertrix_port_actor_turn_toward_4ace40(PORT_SIGNATURE)
{
    Port port;
    uint32_t actor = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t angle;
    uint32_t target;
    uint32_t step;
    uint32_t value;
    port_open(&port, calls, services, globals, entry);
    angle = (uint32_t)((int32_t)port_u32(&port, actor, 0x22) >> 16);
    target = (uint32_t)((int32_t)port_u32(&port, actor, 0x24) >> 16);
    step = (uint32_t)((int32_t)port_u32(&port, actor, 0x26) >> 16) * edx;
    port_set32(&port, 0, 0x5bb5e4, step);
    if (angle != target && step != 0)
    {
        if ((int32_t)step > 0)
        {
            if ((int32_t)target < (int32_t)angle)
            {
                target += 0x168;
            }
            edx = target - angle;
            if ((int32_t)edx <= (int32_t)step)
            {
                port_set16(&port, actor, 0x24, port_u16(&port, actor, 0x26));
            }
            else
            {
                value = (step & 0xffff0000u) | port_u16(&port, actor, 0x24);
                value += step;
                port_set16(&port, actor, 0x24, value);
                if ((int32_t)port_u32(&port, actor, 0x22) >> 16 >= 0x168)
                {
                    edx = (value & 0xffff) % 0x168;
                    port_set16(&port, actor, 0x24, edx);
                }
            }
        }
        else
        {
            step = 0u - step;
            port_set32(&port, 0, 0x5bb5e4, step);
            if ((int32_t)angle < (int32_t)target)
            {
                angle += 0x168;
            }
            edx = angle - target;
            if ((int32_t)edx <= (int32_t)step)
            {
                port_set16(&port, actor, 0x24, port_u16(&port, actor, 0x26));
            }
            else
            {
                edx = (edx & 0xffff0000u) | port_u16(&port, actor, 0x24);
                edx -= step;
                port_set16(&port, actor, 0x24, edx);
                if ((int32_t)port_u32(&port, actor, 0x22) >> 16 < 0)
                {
                    edx = ((edx + 0x168) & 0xffff) % 0x168;
                    port_set16(&port, actor, 0x24, edx);
                }
            }
        }
    }
    port_set32(&port, 0, 0x5bb5dc, angle);
    port_set32(&port, 0, 0x5bb5e0, target);
    return port_return(&port, port_u16(&port, actor, 0x24) != port_u16(&port, actor, 0x26), edx);
}
