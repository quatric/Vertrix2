#include "rtlcursors.h"

/* The menu cursor steered by the mouse and keys. */

/* A call (with count stack arguments, nearest first) that leaves its eax and edx in *eax and
 * *edx; the eax. */
static uint32_t cursor_call(Port *port, uint32_t *eax, uint32_t *edx, uint32_t target, uint32_t a,
                            uint32_t d, uint32_t ebx, uint32_t ecx, uint32_t esi, uint32_t edi,
                            uint32_t ebp, const uint32_t *stack, unsigned count)
{
    *eax = port_call_registers(port, target, a, d, ebx, ecx, esi, edi, ebp, stack, count);
    *edx = vertrix_lift_edx;
    return *eax;
}

/* Original 0x44a720: one step of the menu cursor eax with the speed edx. It may pick when the
 * player 0x532a68's 0x5344a4 is not 1 (a network game 0x532a80 1 also asks 0x418110; otherwise
 * the joined 0x532a7c or not, the other player 0x532a6c's 0x5344f0 decides): able, +0x52 0xd,
 * +0x94 0, +0x95 1, else +0x52 1 and both 0. Over a choice (0x4b6700): picking, +0x93 1, +0x4e
 * 100, +0x94 0, +0x95 3, +0x44 0x10, handed 0x44abe0 and the timers 0x4f819c run (0x417260,
 * 0x417290), 0x532a9c 1; otherwise the timers 0x4f818c run by the two players' entries (the
 * network game without 0x418110 both). Not over one: with a speed the cursor moves toward the
 * mouse 0x558944/0x558946 (0x7d00 both while 0x558958): reached (0x4b66c0 1) and able by 10,
 * else by 2 with 0x4b6590's turn (0x4b65a0, then 0x4ac980 with the step, 0x4b6540). The key 0x74
 * (0x476480, 0x4764a0) on a choice (0x4b66c0) picks it: able, +0x44 0x10, handed 0x44ab50, 0x532a9c
 * 1; otherwise the timers as before and handed 0x44ab00. edx what the last call left. */
uint32_t vertrix_port_menu_cursor_step_44a720(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x24
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t cursor = entry->eax;
    uint32_t eax;
    uint32_t edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = cursor;
    uint32_t edi = 1;
    uint32_t arg;
    int able;
#define CALL(target, a, d)                                                                         \
    cursor_call(&port, &eax, &edx, target, a, d, ebx, ecx, cursor, edi, ebp, NULL, 0)
#define TIMER(target) CALL(target, port_u32(&port, 0, 0x4f818c), edx)
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -4u, entry->ebx);
    port_set32(&port, ebp, -8u, entry->ecx);
    port_set32(&port, ebp, -0xcu, entry->esi);
    port_set32(&port, ebp, -0x10u, entry->edi);
    port_set32(&port, ebp, -0x14u, entry->edx);
    eax = port_u32(&port, 0, 0x532a68) << 2;
    edx = port_u32(&port, 0, 0x532a80);
    if (edx == 1)
    {
        if (port_u32(&port, eax, 0x5344a4) == 1)
        {
            edi = 0;
        }
        able = CALL(0x418110, eax, edx) != 0;
    }
    else
    {
        if (port_u32(&port, 0, 0x532a7c) != 1 && port_u32(&port, eax, 0x5344a4) == 1)
        {
            edi = 0;
        }
        eax = port_u32(&port, 0, 0x532a6c);
        able = port_u32(&port, eax * 4, 0x5344f0) != 1;
    }
    if (able && edi != 0)
    {
        port_set8(&port, cursor, 0x52, 0xd);
        port_set8(&port, cursor, 0x94, 0);
        port_set8(&port, cursor, 0x95, 1);
    }
    else
    {
        edi = 0;
        port_set8(&port, cursor, 0x52, 1);
        port_set8(&port, cursor, 0x94, 0);
        port_set8(&port, cursor, 0x95, 0);
    }
    if (CALL(0x4b6700, cursor, edx) != 0)
    {
        if (edi == 1)
        {
            port_set8(&port, cursor, 0x93, 1);
            port_set8(&port, cursor, 0x4e, 0x64);
            port_set8(&port, cursor, 0x94, 0);
            port_set8(&port, cursor, 0x95, 3);
            port_set8(&port, cursor, 0x44, 0x10);
            CALL(0x4ac8f0, cursor, 0x44abe0);
            CALL(0x417260, port_u32(&port, 0, 0x4f819c), edx);
            CALL(0x417290, port_u32(&port, 0, 0x4f819c), edx);
            port_set32(&port, 0, 0x532a9c, edi);
            return port_return(&port, eax, edx);
        }
        if (port_u32(&port, 0, 0x532a80) == 1 && CALL(0x418110, eax, edx) == 0)
        {
            TIMER(0x417260);
            TIMER(0x417290);
            return port_return(&port, eax, edx);
        }
        eax = port_u32(&port, 0, 0x532a68);
        if (port_u32(&port, eax * 4, 0x5344a4) == 1)
        {
            TIMER(0x417260);
        }
        eax = port_u32(&port, 0, 0x532a6c);
        if (port_u32(&port, eax * 4, 0x5344f0) == 1)
        {
            TIMER(0x417290);
        }
        return port_return(&port, eax, edx);
    }
    if (port_u32(&port, ebp, -0x14u) != 0)
    {
        uint32_t step;
        ecx = port_u32(&port, 0, 0x558958);
        if (ecx != 0)
        {
            ebx = 0x7d00;
            edx = 0x7d00;
        }
        else
        {
            ebx = (uint32_t)(int32_t)(int16_t)port_u16(&port, 0, 0x558946);
            edx = (uint32_t)(int32_t)(int16_t)port_u16(&port, 0, 0x558944);
        }
        if (CALL(0x4b66c0, cursor, edx) == 1 && edi == 1)
        {
            step = 0xa;
            ecx = 0;
        }
        else
        {
            ecx = (uint32_t)(int32_t)(int16_t)CALL(0x4b6590, cursor, edx);
            step = 2;
        }
        arg = step;
        CALL(0x4b65a0, cursor, port_u32(&port, ebp, -0x14u));
        ebx = (uint32_t)(int32_t)(int16_t)eax;
        edx = (uint32_t)(int32_t)(int16_t)cursor_call(&port, &eax, &edx, 0x4ac980, cursor, edx, ebx,
                                                      ecx, cursor, edi, ebp, &arg, 1);
        CALL(0x4b6540, cursor, edx);
    }
    if (CALL(0x476480, 0x54d640, 0x74) != 1)
    {
        return port_return(&port, eax, edx);
    }
    ecx = ebp - 0x1c;
    ebx = ebp - 0x20;
    arg = ebp - 0x18;
    cursor_call(&port, &eax, &edx, 0x4764a0, 0x54d640, 0x74, ebx, ecx, cursor, edi, ebp, &arg, 1);
    ebx = (uint32_t)(int32_t)(int16_t)port_u16(&port, ebp, -0x1cu);
    if (CALL(0x4b66c0, cursor, (uint32_t)(int32_t)(int16_t)port_u16(&port, ebp, -0x20u)) != 1)
    {
        return port_return(&port, eax, edx);
    }
    if (edi == 1)
    {
        ecx = edi;
        port_set8(&port, cursor, 0x44, 0x10);
        CALL(0x4ac8f0, cursor, 0x44ab50);
        port_set32(&port, 0, 0x532a9c, ecx);
        return port_return(&port, eax, edx);
    }
    if (eax == port_u32(&port, 0, 0x532a80) && CALL(0x418110, eax, edx) == 0)
    {
        TIMER(0x417260);
        TIMER(0x417290);
    }
    else
    {
        eax = port_u32(&port, 0, 0x532a68);
        if (port_u32(&port, eax * 4, 0x5344a4) == 1)
        {
            TIMER(0x417260);
        }
        eax = port_u32(&port, 0, 0x532a6c);
        if (port_u32(&port, eax * 4, 0x5344f0) == 1)
        {
            TIMER(0x417290);
        }
    }
    CALL(0x4ac8f0, cursor, 0x44ab00);
#undef CALL
#undef TIMER
    return port_return(&port, eax, edx);
}
