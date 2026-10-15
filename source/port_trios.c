#include "port_trios.h"

/* The three shuffled actors. */

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

/* Original 0x472f80: the five frame kinds of 0x4fd668 (at ebp-0x60) are shuffled, each swapped
 * with a random one of the five (0x4826c0 of 5) unless it draws itself; then three 0x15c byte
 * actors (0x4ca000, 0x4abd70), placed (0x4adf20), without a hover (0x4ac910 with 0), turned by a
 * random 0x168 (+0x24) and spun by a random 2 plus 1 (+0x28), of the kinds +0 0x4fd694 and the
 * frames 0x546458 + 0x1c times the shuffled kind (0x4ac8d0, 0x4ac710 with 0), turned (0x4ac8a0
 * with 0x64), owned (0x4ac490), timed at 0xc8 and 0xa (0x4ac7d0, 0x4ac860), stand at the words
 * 0x4fd67c and 0x4fd688 (+8, +0xe, +0x10 and +0xa, +0x16, +0x18) with +0x12, +0x1a 0xa, +0x30 5,
 * +0x4e, +0x4f 0x64, +0x93, +0x8f, +0x58, +0x50 1; they rise from their fall (0x4ad1c0 into
 * ebp-0x1c and ebp-0x18, added to +0x16), 0x4ae110 with 0, +0x124 1, +0x13c 0, +0x140 and
 * +0x150 1, take the states 0x4fd6a0 (0x4ac8f0) and are listed (0x546730, 0x4b5e70). Returns the
 * last listing's eax and the pushed edx; the registers kept. */
uint32_t vertrix_port_actor_trio_spawn_472f80(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x64
    };
    Port port;
    uint8_t stack[BELOW + 8];
    uint32_t ebp = entry->esp - 4;
    uint32_t zeros[5] = {0, 0, 0, 0, 0};
    uint32_t pushed[1];
    uint32_t edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi;
    uint32_t edi;
    uint32_t pick;
    uint32_t actor;
    uint32_t eax = 0;
    uint32_t i;
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -4u, entry->ebx);
    port_set32(&port, ebp, -8u, entry->ecx);
    port_set32(&port, ebp, -0xcu, entry->edx);
    port_set32(&port, ebp, -0x10u, entry->esi);
    port_set32(&port, ebp, -0x14u, entry->edi);
    for (i = 0; i < 5; i++)
    {
        port_set32(&port, ebp, -0x60u + i * 4, port_u32(&port, 0, 0x4fd668 + i * 4));
    }
    for (i = 0; i < 3; i++)
    {
        port_set32(&port, ebp, -0x34u + i * 4, port_u32(&port, 0, 0x4fd67c + i * 4));
        port_set32(&port, ebp, -0x28u + i * 4, port_u32(&port, 0, 0x4fd688 + i * 4));
        port_set32(&port, ebp, -0x4cu + i * 4, port_u32(&port, 0, 0x4fd694 + i * 4));
        port_set32(&port, ebp, -0x40u + i * 4, port_u32(&port, 0, 0x4fd6a0 + i * 4));
    }
    esi = 0;
    for (edi = 0; edi < 5; edi++)
    {
        pick = port_call_with(&port, 0x4826c0, 0x598d30, 5, ebx, ecx, esi, edi, ebp) & 0xffff;
        edx = vertrix_lift_edx;
        if (pick != edi)
        {
            edx = port_u32(&port, ebp, pick * 4 - 0x60);
            ecx = port_u32(&port, esi, ebp - 0x60);
            port_set32(&port, esi, ebp - 0x60, edx);
            port_set32(&port, ebp, pick * 4 - 0x60, ecx);
        }
        esi += 4;
    }
    for (edi = 0; edi != 0xc;)
    {
        actor = port_call_with(&port, 0x4ca000, 0x15c, edx, ebx, ecx, esi, edi, ebp);
        if (actor != 0)
        {
            actor =
                port_call_with(&port, 0x4abd70, actor, vertrix_lift_edx, ebx, ecx, esi, edi, ebp);
        }
        esi = actor;
        call_frame(&port, 0x4adf20, actor, 0, 0, 0, esi, edi, ebp, zeros, 5);
        port_call_with(&port, 0x4ac910, actor, 0, 0, 0, esi, edi, ebp);
        port_set16(&port, actor, 0x24,
                   port_call_with(&port, 0x4826c0, 0x598d30, 0x168, 0, 0, esi, edi, ebp));
        port_set16(&port, actor, 0x28,
                   port_call_with(&port, 0x4826c0, 0x598d30, 2, 0, 0, esi, edi, ebp) + 1);
        port_set8(&port, actor, 0x8f, 1);
        port_set32(&port, actor, 0x58, 1);
        port_set32(&port, actor, 0, port_u32(&port, edi, ebp - 0x4c));
        port_call_with(&port, 0x4ac8d0, actor, port_u32(&port, edi, ebp - 0x60) * 0x1c + 0x546458,
                       0, 0, esi, edi, ebp);
        port_call_with(&port, 0x4ac710, actor, 0, 0, 0, esi, edi, ebp);
        port_call_with(&port, 0x4ac8a0, actor, 0x64, 0, 0, esi, edi, ebp);
        port_call_with(&port, 0x4ac490, actor, vertrix_lift_edx, 0, 0, esi, edi, ebp);
        port_call_with(&port, 0x4ac7d0, actor, 0xc8, 0, 0, esi, edi, ebp);
        port_call_with(&port, 0x4ac860, actor, 0xa, 0, 0, esi, edi, ebp);
        port_set16(&port, actor, 8, port_u16(&port, edi, ebp - 0x34));
        port_set16(&port, actor, 0xa, port_u16(&port, edi, ebp - 0x28));
        port_set16(&port, actor, 0xe, port_u16(&port, edi, ebp - 0x34));
        port_set16(&port, actor, 0x12, 0xa);
        port_set16(&port, actor, 0x1a, 0xa);
        port_set16(&port, actor, 0x30, 5);
        port_set8(&port, actor, 0x4e, 0x64);
        port_set8(&port, actor, 0x93, 1);
        port_set8(&port, actor, 0x4f, 0x64);
        port_set16(&port, actor, 0x16, port_u16(&port, edi, ebp - 0x28));
        port_set16(&port, actor, 0x10, port_u16(&port, actor, 8));
        edx = (uint32_t)((int32_t)port_u32(&port, actor, 0x2e) >> 16);
        port_set16(&port, actor, 0x18, port_u16(&port, actor, 0xa));
        port_set16(&port, actor, 0x50, 1);
        pushed[0] = ebp - 0x18;
        call_frame(&port, 0x4ad1c0, actor, edx, edx, ebp - 0x1c, esi, edi, ebp, pushed, 1);
        port_set16(&port, actor, 0x16, port_u16(&port, actor, 0xa) + port_u32(&port, ebp, -0x18u));
        port_set32(&port, actor, 0x124, 1);
        pushed[0] = 0;
        call_frame(&port, 0x4ae110, actor, 0, 0, 0, esi, edi, ebp, pushed, 1);
        port_set32(&port, actor, 0x13c, 0);
        port_set32(&port, actor, 0x140, 1);
        port_set32(&port, actor, 0x150, 1);
        port_call_with(&port, 0x4ac8f0, actor, port_u32(&port, edi, ebp - 0x40), 0, 0, esi, edi,
                       ebp);
        edi += 4;
        eax = port_call_with(&port, 0x4b5e70, 0x546730, actor, 0, 0, esi, edi, ebp);
        edx = vertrix_lift_edx;
        ebx = 0;
        ecx = 0;
    }
    /* An index past the list swaps into the pushed registers: edx is the one the caller sees. */
    return port_return(&port, eax, port_u32(&port, ebp, -0xcu));
}
