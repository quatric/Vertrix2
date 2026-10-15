#include "port_homings.h"

/* The actors' way home. */

static void guard_record(Port *port, uint32_t record, uint32_t guard)
{
    port_set32(port, record, 0, port->env.chain);
    port_set32(port, record, 4, 0x4ec1ec);
    port_set32(port, record, 8, guard);
    port_set32(port, record, 0xc, 0);
}

static uint32_t call_frame(Port *port, uint32_t target, uint32_t eax, uint32_t edx, uint32_t ebx,
                           uint32_t ecx, uint32_t esi, uint32_t edi, uint32_t ebp,
                           const uint32_t *stack, unsigned count)
{
    uint32_t result;
    vertrix_lift_in_esi = esi;
    vertrix_lift_in_edi = edi;
    vertrix_lift_in_ebp = ebp;
    result = lift_call_arguments(&port->env, target, eax, edx, ebx, ecx, stack, count);
    vertrix_lift_in_esi = vertrix_lift_in_edi = vertrix_lift_in_ebp = 0;
    return result;
}

static uint32_t sign16(uint32_t value)
{
    return (uint32_t)(int32_t)(int16_t)value;
}

/* The text `format` of the value at `value` printed (0x4cdfb0) to the temporary at `text`, made
 * by 0x4ca070, and loaded as a script (0x416a80). */
static void homing_print(Port *port, uint32_t text, uint32_t format, uint32_t value, uint32_t edx,
                         uint32_t ebx, uint32_t esi, uint32_t edi, uint32_t ebp)
{
    uint32_t args[3];
    args[0] = text;
    args[1] = format;
    args[2] = port_u32(port, 0, value);
    call_frame(port, 0x4cdfb0, text, edx, ebx, 0, esi, edi, ebp, args, 3);
}

/* Original 0x44bf70: under a guard record (0x51534c) the actor eax, when due (0x4ac500,
 * 0x4ac520), takes its stride (0x4ac540, 0x4ac5b0), bobs to rest (+0x4a 0, +0x4c 5; 0x4adfe0
 * and 0x4ad530 while +0x48 is set), fades (+0x4f 0, +0x50 5; 0x4adfe0 while +0x4e is set;
 * 0x4ad580) and follows its path (0x4b6590 against 0x4b65a0; when apart 0x4adfe0, 0x4b65a0,
 * 0x4ac980 by 5 and 0x4b6540); home (the path ended, 0x4b6560 1, and the fade done) it takes the
 * state 0x44c260, or, as the player 0x4f7bb8's actor with 0x532a84 1 and the import 0x418130
 * 1, loads the script 0x50e1ef of 0x532c20 (0x532a7c 1) or 0x50e206 of 0x532c1c (0x532a80 1),
 * notifies 0x5bb254 (0x48c310 of 0x44c1a0) and takes its state. The guard record's chain. */
uint32_t vertrix_port_actor_homing_44bf70(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x3c
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t actor = entry->eax;
    uint32_t five[1] = {5};
    uint32_t stride;
    uint32_t path;
    uint32_t ebx = 0x51534c;
    uint32_t ecx = actor;
    uint32_t edx;
    uint32_t edi;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, -4u, entry->ebx);
    port_set32(&port, ebp, -8u, entry->ecx);
    port_set32(&port, ebp, -0xcu, entry->edx);
    port_set32(&port, ebp, -0x10u, entry->esi);
    port_set32(&port, ebp, -0x14u, entry->edi);
    guard_record(&port, ebp - 0x38, 0x51534c);
    port_call_with(&port, 0x4ac500, actor, 0x4ec1ec, ebx, actor, 0, entry->edi, ebp);
    if (port_call_with(&port, 0x4ac520, actor, vertrix_lift_edx, ebx, actor, actor, entry->edi,
                       ebp) != 1)
    {
        return port_return(&port, port_u32(&port, ebp, -0x38u), entry->edx);
    }
    port_set32(&port, ebp, -0x1cu, 1);
    stride = port_call_with(&port, 0x4ac540, actor, vertrix_lift_edx, ebx, actor, actor, entry->edi,
                            ebp);
    edi = stride;
    port_call_with(&port, 0x4ac5b0, actor, stride, ebx, actor, actor, edi, ebp);
    port_set16(&port, actor, 0x4a, 0);
    ebx = (ebx & 0xffff0000u) | port_u16(&port, actor, 0x4a);
    port_set16(&port, actor, 0x4c, 5);
    if (port_u16(&port, actor, 0x48) != (ebx & 0xffff))
    {
        port_call_with(&port, 0x4adfe0, actor, vertrix_lift_edx, ebx, actor, actor, edi, ebp);
        port_call_with(&port, 0x4ad530, actor, vertrix_lift_edx, ebx, actor, actor, edi, ebp);
    }
    port_set8(&port, actor, 0x4f, 0);
    port_set16(&port, actor, 0x50, 5);
    if (port_u8(&port, actor, 0x4e) != port_u8(&port, actor, 0x4f))
    {
        port_call_with(&port, 0x4adfe0, actor, vertrix_lift_edx, ebx, actor, actor, edi, ebp);
    }
    port_set32(&port, ebp, -0x18u,
               port_call_with(&port, 0x4ad580, actor, stride, ebx, actor, actor, edi, ebp));
    path = sign16(
        port_call_with(&port, 0x4b6590, actor, vertrix_lift_edx, ebx, actor, actor, edi, ebp));
    path = sign16(port_call_with(&port, 0x4b65a0, actor, path, ebx, actor, actor, edi, ebp));
    if (path != vertrix_lift_edx)
    {
        port_call_with(&port, 0x4adfe0, actor, vertrix_lift_edx, ebx, actor, actor, edi, ebp);
        ebx = sign16(
            port_call_with(&port, 0x4b65a0, actor, vertrix_lift_edx, ebx, actor, actor, edi, ebp));
        ecx = vertrix_lift_edx;
        port_call_with(
            &port, 0x4b6540, actor,
            sign16(call_frame(&port, 0x4ac980, actor, stride, ebx, ecx, actor, edi, ebp, five, 1)),
            ebx, ecx, actor, edi, ebp);
    }
    if (port_call_with(&port, 0x4b6560, actor, vertrix_lift_edx, ebx, ecx, actor, edi, ebp) == 1)
    {
        port_set32(&port, ebp, -0x1cu, 0);
    }
    if (port_u32(&port, ebp, -0x18u) != 0 || port_u32(&port, ebp, -0x1cu) != 0)
    {
        return port_return(&port, port_u32(&port, ebp, -0x38u), entry->edx);
    }
    ecx = 0;
    ebx = port_u32(&port, 0, 0x4f7bb8);
    if (ebx == port_u32(&port, actor, 0x14c))
    {
        edi = port_u32(&port, 0, 0x532a84);
        if (edi == 1 &&
            port_call_with(&port, 0x418130, 0, vertrix_lift_edx, ebx, 0, actor, edi, ebp) == edi)
        {
            edx = port_u32(&port, 0, 0x532a7c);
            if (edx == 1)
            {
                port_call_with(&port, 0x4ca070, ebp - 0x24, edx, ebx, 0, actor, 1, ebp);
                port_set32(&port, ebp, -0x2cu, 1);
                homing_print(&port, ebp - 0x24, 0x50e1ef, 0x532c20, vertrix_lift_edx ^ 1, ebx,
                             actor, 1, ebp);
                ebx = 0;
                port_call_with(&port, 0x416a80, port_u32(&port, ebp, -0x24u), vertrix_lift_edx, ebx,
                               0, actor, 1, ebp);
                port_set32(&port, ebp, -0x2cu, 0);
                port_call_with(&port, 0x4ca210, ebp - 0x24, vertrix_lift_edx, ebx, 0, actor, 1,
                               ebp);
                port_set32(&port, ebp, -0x2cu, 0);
            }
            else if (port_u32(&port, 0, 0x532a80) == 1)
            {
                port_call_with(&port, 0x4ca070, ebp - 0x20, edx, ebx, 0, actor, 1, ebp);
                ebx = 3;
                edi = 0;
                port_set32(&port, ebp, -0x2cu, 3);
                homing_print(&port, ebp - 0x20, 0x50e206, 0x532c1c, vertrix_lift_edx, ebx, actor,
                             edi, ebp);
                port_call_with(&port, 0x416a80, port_u32(&port, ebp, -0x20u), 0, ebx, 0, actor, edi,
                               ebp);
                port_set32(&port, ebp, -0x2cu, 0);
                port_call_with(&port, 0x4ca210, ebp - 0x20, vertrix_lift_edx, ebx, 0, actor, edi,
                               ebp);
                port_set32(&port, ebp, -0x2cu, 0);
            }
            port_call_with(&port, 0x48c310, 0x5bb254, 0x44c1a0, ebx, 0, actor, edi, ebp);
            port_call_with(&port, 0x4ac8f0, actor, vertrix_lift_edx, ebx, 0, actor, edi, ebp);
            return port_return(&port, port_u32(&port, ebp, -0x38u), entry->edx);
        }
    }
    port_call_with(&port, 0x4ac8f0, actor, 0x44c260, ebx, ecx, actor, edi, ebp);
    return port_return(&port, port_u32(&port, ebp, -0x38u), entry->edx);
}
