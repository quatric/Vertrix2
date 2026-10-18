#include "rtlactorfades.h"

/* Actors that fade while they fly. */

/* A call (with count stack arguments, nearest first) that leaves its eax and edx in *eax and
 * *edx; the eax. */
static uint32_t fade_call(Port *port, uint32_t *eax, uint32_t *edx, uint32_t target, uint32_t a,
                          uint32_t d, uint32_t ebx, uint32_t ecx, uint32_t esi, uint32_t edi,
                          uint32_t ebp, const uint32_t *stack, unsigned count)
{
    *eax = port_call_registers(port, target, a, d, ebx, ecx, esi, edi, ebp, stack, count);
    *edx = vertrix_lift_edx;
    return *eax;
}

/* Original 0x44dfb0: one step of the actor eax flying out: +0x95 3 and +0x94 0, set up with 5
 * (0x4ac1f0, the steps of 0x30), 0x4ac500; not yet moving (0x4ac520 not 1) it is only drawn
 * (0x4ac8a0). Otherwise moved by its speed (0x4ac540, 0x4ac5b0); off its path (0x4ad530 0) with
 * +0x4a 100 its +0x52 becomes 2; its row +0xa stepped (0x4acab0, by +0x16), its spot +8/+0xa
 * kept, 0x4ad060, its centre (0x4ad750) and its step (0x4ad1c0 of +0x64) read; its shade +0x44
 * 0x10 less the count 0x4ac1f0 left in edx plus the step times that count over 0x30, at most
 * 0x10; its size (0x4b14c0) centres it on the spot (+0xe,
 * +0x16) and 0x4ad6e0 run. Ended (0x4acab0 0, or 0x4ad6e0 0) it is handed 0x44c860
 * (0x4ac8f0). Drawn (0x4ac8a0) either way. eax what 0x4ac8a0 gave, edx kept. */
uint32_t vertrix_port_actor_fade_step_44dfb0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x3c
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t actor = entry->eax;
    uint32_t eax;
    uint32_t edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = 0x30;
    uint32_t edi = entry->edi;
    uint32_t arg;
    uint32_t divisor;
    uint32_t shade;
#define CALL(target, a, d)                                                                         \
    fade_call(&port, &eax, &edx, target, a, d, ebx, ecx, actor, edi, ebp, NULL, 0)
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -4u, entry->ebx);
    port_set32(&port, ebp, -8u, entry->ecx);
    port_set32(&port, ebp, -0xcu, entry->edx);
    port_set32(&port, ebp, -0x10u, entry->esi);
    port_set32(&port, ebp, -0x14u, entry->edi);
    port_set8(&port, actor, 0x95, 3);
    port_set8(&port, actor, 0x94, 0);
    CALL(0x4ac1f0, actor, 5);
    port_set32(&port, ebp, -0x24u, edx);
    CALL(0x4ac500, actor, edx);
    port_set32(&port, ebp, -0x20u, ecx);
    if (CALL(0x4ac520, actor, edx) == 1)
    {
        edi = CALL(0x4ac540, actor, edx);
        CALL(0x4ac5b0, actor, edi);
        if (CALL(0x4ad530, actor, edx) == 0 && port_u16(&port, actor, 0x4a) == 0x64)
        {
            port_set8(&port, actor, 0x52, 2);
        }
        port_set16(&port, actor, 0x16, port_u16(&port, actor, 0xa));
        port_set32(&port, ebp, -0x28u, CALL(0x4acab0, actor, edi));
        port_set16(&port, actor, 0xa, port_u16(&port, actor, 0x16));
        port_set16(&port, ebp, -0x18u, port_u16(&port, actor, 8));
        port_set16(&port, ebp, -0x1cu, port_u16(&port, actor, 0xa));
        CALL(0x4ad060, actor, edi);
        ecx = ebp - 0x38;
        CALL(0x4ad750, actor, edi);
        ebx = port_u32(&port, actor, 0x64);
        arg = ebp - 0x34;
        fade_call(&port, &eax, &edx, 0x4ad1c0, actor, ebx, ebx, ecx, actor, edi, ebp, &arg, 1);
        eax = port_u32(&port, ebp, -0x34u) * port_u32(&port, ebp, -0x24u);
        divisor = port_u32(&port, ebp, -0x20u);
        ecx = divisor;
        if (divisor != 0)
        {
            eax /= divisor;
        }
        port_set32(&port, ebp, -0x34u, eax);
        shade = (uint8_t)(0x10 - port_u8(&port, ebp, -0x24u) + port_u8(&port, ebp, -0x34u));
        port_set8(&port, actor, 0x44, shade);
        if (shade >= 0x10)
        {
            shade = 0x10;
        }
        port_set8(&port, actor, 0x44, shade);
        port_set32(&port, ebp, -0x30u, 0);
        port_set32(&port, ebp, -0x2cu, 0);
        ebx = ebp - 0x2c;
        CALL(0x4b14c0, actor, ebp - 0x30);
        port_set16(&port, actor, 0xe,
                   port_u32(&port, ebp, -0x38u) +
                       (uint32_t)(int32_t)(int16_t)port_u16(&port, ebp, -0x18u) -
                       (port_u32(&port, ebp, -0x30u) >> 1));
        port_set16(&port, actor, 0x16,
                   (uint32_t)(int32_t)(int16_t)port_u16(&port, ebp, -0x1cu) -
                       (port_u32(&port, ebp, -0x2cu) >> 1));
        if (CALL(0x4ad6e0, actor, edi) == 0 || port_u32(&port, ebp, -0x28u) == 0)
        {
            CALL(0x4ac8f0, actor, 0x44c860);
        }
    }
    CALL(0x4ac8a0, actor, edx);
#undef CALL
    return port_return(&port, eax, entry->edx);
}
