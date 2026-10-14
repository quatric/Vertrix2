#include "port_spawn.h"

/* Actor spawning, resource table loading and panel release helpers. */

/* A call handing the callee esi, edi and ebp as given and `count` stack dwords. */
static uint32_t call_stack(Port *port, uint32_t target, uint32_t eax, uint32_t edx, uint32_t ebx,
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

/* A new actor: 0x4ca000 allocates 0x15c bytes and 0x4abd70 builds them when it gave any (the
 * actor, else 0). */
static uint32_t actor_new(Port *port, const LiftEntry *entry, uint32_t ecx, uint32_t edi)
{
    uint32_t actor = call_stack(port, 0x4ca000, 0x15c, entry->edx, entry->ebx, ecx, entry->esi, edi,
                                entry->ebp, NULL, 0);
    if (actor != 0)
    {
        actor = call_stack(port, 0x4abd70, actor, vertrix_lift_edx, entry->ebx, ecx, entry->esi,
                           edi, entry->ebp, NULL, 0);
    }
    return actor;
}

/* Original 0x465a70: a new actor (0x4adf20 at the signed words eax and the edx left), the
 * animation set 0x544a18 at the frame ebx, 0x4ac8a0, bytes +0x93 1, +0x95 1 and +0x4e 0, word
 * +0x48 -40, and listed by 0x4b5e70 on 0x54671c. */
uint32_t vertrix_port_marker_spawn_465a70(PORT_SIGNATURE)
{
    Port port;
    uint32_t zeros[5] = {0};
    uint32_t frame = entry->ebx;
    uint32_t actor;
    uint32_t ebx;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    actor = actor_new(&port, entry, entry->eax, frame);
    ebx = (uint32_t)(int32_t)(int16_t)vertrix_lift_edx;
    call_stack(&port, 0x4adf20, actor, (uint32_t)(int32_t)(int16_t)entry->eax, ebx, 0, actor, frame,
               entry->ebp, zeros, 5);
    call_stack(&port, 0x4ac8d0, actor, 0x544a18, ebx, 0, actor, frame, entry->ebp, NULL, 0);
    call_stack(&port, 0x4ac710, actor, frame, ebx, 0, actor, frame, entry->ebp, NULL, 0);
    call_stack(&port, 0x4ac8a0, actor, vertrix_lift_edx, ebx, 0, actor, frame, entry->ebp, NULL, 0);
    port_set8(&port, actor, 0x93, 1);
    port_set8(&port, actor, 0x95, 1);
    port_set8(&port, actor, 0x4e, 0);
    port_set16(&port, actor, 0x48, 0xffd8);
    result =
        call_stack(&port, 0x4b5e70, 0x54671c, actor, ebx, 0, actor, frame, entry->ebp, NULL, 0);
    return port_return(&port, result, vertrix_lift_edx);
}

/* A new actor at 0, 0 (0x4adf20) with 0x4ac7b0 1, `then` stored and the next handler `next`, and
 * 0x4ac910 0. */
static uint32_t actor_spawn(Port *port, const LiftEntry *entry, uint32_t next, int land)
{
    uint32_t zeros[5] = {0};
    uint32_t actor = actor_new(port, entry, entry->ecx, entry->edi);
    call_stack(port, 0x4adf20, actor, 0, 0, 0, actor, entry->edi, entry->ebp, zeros, 5);
    call_stack(port, 0x4ac7b0, actor, 1, 0, 0, actor, entry->edi, entry->ebp, NULL, 0);
    if (land)
    {
        port_set8(port, actor, 0x94, 1);
        port_set8(port, actor, 0x95, 0);
    }
    call_stack(port, 0x4ac8f0, actor, next, 0, 0, actor, entry->edi, entry->ebp, NULL, 0);
    call_stack(port, 0x4ac910, actor, 0, 0, 0, actor, entry->edi, entry->ebp, NULL, 0);
    return actor;
}

/* Original 0x4718a0: bytes +0x94 1 and +0x95 0, next 0x446850, then 0x4ac710 0; the actor. */
uint32_t vertrix_port_actor_spawn_4718a0(PORT_SIGNATURE)
{
    Port port;
    uint32_t actor;
    port_open(&port, calls, services, globals, entry);
    actor = actor_spawn(&port, entry, 0x446850, 1);
    call_stack(&port, 0x4ac710, actor, 0, 0, 0, actor, entry->edi, entry->ebp, NULL, 0);
    return port_return(&port, actor, entry->edx);
}

/* Original 0x472170: next 0x456f10, then listed by 0x4b5e70 on 0x54676c. */
uint32_t vertrix_port_actor_spawn_472170(PORT_SIGNATURE)
{
    Port port;
    uint32_t actor;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    actor = actor_spawn(&port, entry, 0x456f10, 0);
    result =
        call_stack(&port, 0x4b5e70, 0x54676c, actor, 0, 0, actor, entry->edi, entry->ebp, NULL, 0);
    return port_return(&port, result, entry->edx);
}

/* Original 0x45f020: for the 13 entries: 0x4877f0 on 0x544b84 with the index (and its offset),
 * 0x482e10 with eax and the two tables' dwords (0x4fbfe0 and 0x4fc014, copied to the frame), and
 * 0x483ed0 with 0x5b9c60. */
uint32_t vertrix_port_resource_paired_finish_45f020(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x88
    };
    Port port;
    uint8_t stack[BELOW + 8];
    uint32_t ebp = entry->esp - 4;
    uint32_t esi = 0x4fc048;
    uint32_t index = 0;
    uint32_t k;
    uint32_t result = 0;
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, -0x1cu, entry->eax);
    for (k = 0; k < 0xd; k++)
    {
        port_set32(&port, ebp, -0x84u + k * 4, port_u32(&port, 0, 0x4fbfe0 + k * 4));
    }
    for (k = 0; k < 0xd; k++)
    {
        port_set32(&port, ebp, -0x50u + k * 4, port_u32(&port, 0, 0x4fc014 + k * 4));
    }
    port_set32(&port, ebp, -0x18u, 0);
    do
    {
        uint32_t offset = port_u32(&port, ebp, -0x18u);
        uint32_t ebx;
        uint32_t ecx;
        esi =
            call_stack(&port, 0x4877f0, 0x544b84, index, offset, offset, esi, index, ebp, NULL, 0);
        ecx = port_u32(&port, ebp + offset, -0x50u);
        ebx = port_u32(&port, ebp + offset, -0x84u);
        call_stack(&port, 0x482e10, esi, port_u32(&port, ebp, -0x1cu), ebx, ecx, esi, index, ebp,
                   NULL, 0);
        index++;
        ecx = port_u32(&port, ebp, -0x18u) + 4;
        result = call_stack(&port, 0x483ed0, esi, 0x5b9c60, ebx, ecx, esi, index, ebp, NULL, 0);
        port_set32(&port, ebp, -0x18u, ecx);
    } while (index < 0xd);
    return port_return(&port, result, entry->edx);
}

/* Original 0x45f0c0: for the 8 entries of the kind edx (its byte of the 7 at 0x4fc048, copied to
 * the frame): 0x4877f0 on its 28-byte set at 0x544ac0 with the index, 0x482e10 with eax, and
 * 0x483ed0 with 0x5b9c60; ecx the kind's 24-byte row, ebx the entry's. */
uint32_t vertrix_port_resource_kind_finish_45f0c0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x2c
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t esi = 0x4fc04f;
    uint32_t index = 0;
    uint32_t k;
    uint32_t result = 0;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, -0x20u, entry->eax);
    for (k = 0; k < 7; k++)
    {
        port_set8(&port, ebp, -0x28u + k, port_u8(&port, 0, 0x4fc048 + k));
    }
    port_set8(&port, ebp, -0x14u, port_u8(&port, ebp + entry->edx, -0x28u));
    port_set32(&port, ebp, -0x1cu, 0);
    port_set32(&port, ebp, -0x18u, entry->edx * 0x18);
    do
    {
        uint32_t set = port_u8(&port, ebp, -0x14u) * 0x1c + 0x544ac0;
        uint32_t ecx = port_u32(&port, ebp, -0x18u);
        uint32_t ebx = port_u32(&port, ebp, -0x1cu);
        uint32_t at = index;
        index++;
        esi = call_stack(&port, 0x4877f0, set, at, ebx, ecx, esi, index, ebp, NULL, 0);
        call_stack(&port, 0x482e10, esi, port_u32(&port, ebp, -0x20u), ebx, ecx, esi, index, ebp,
                   NULL, 0);
        ecx = port_u32(&port, ebp, -0x1cu) + 0x18;
        result = call_stack(&port, 0x483ed0, esi, 0x5b9c60, ebx, ecx, esi, index, ebp, NULL, 0);
        port_set32(&port, ebp, -0x1cu, ecx);
    } while (index < 8);
    return port_return(&port, result, vertrix_lift_edx);
}

/* Original 0x45f9f0: the panels 0x54670c, 0x546710, 0x546714 and 0x546718 (those set) destroyed by
 * their method +0 (table +0x158) with 2. */
uint32_t vertrix_port_ui_panels_destroy_full_45f9f0(PORT_SIGNATURE)
{
    Port port;
    uint32_t result = entry->eax;
    uint32_t panel;
    uint32_t methods;
    uint32_t ebx = entry->ebx;
    port_open(&port, calls, services, globals, entry);
    panel = port_u32(&port, 0, 0x54670c);
    if (panel != 0)
    {
        methods = port_u32(&port, panel, 0x158);
        result = call_stack(&port, port_u32(&port, methods, 0), panel, 2, ebx, methods, entry->esi,
                            entry->edi, entry->ebp, NULL, 0);
    }
    panel = port_u32(&port, 0, 0x546710);
    if (panel != 0)
    {
        methods = port_u32(&port, panel, 0x158);
        result = call_stack(&port, port_u32(&port, methods, 0), panel, 2, ebx, methods, entry->esi,
                            entry->edi, entry->ebp, NULL, 0);
    }
    panel = port_u32(&port, 0, 0x546714);
    ebx = panel;
    if (panel != 0)
    {
        methods = port_u32(&port, panel, 0x158);
        result = call_stack(&port, port_u32(&port, methods, 0), panel, 2, ebx, methods, entry->esi,
                            entry->edi, entry->ebp, NULL, 0);
    }
    panel = port_u32(&port, 0, 0x546718);
    if (panel != 0)
    {
        methods = port_u32(&port, panel, 0x158);
        result = call_stack(&port, port_u32(&port, methods, 0), panel, 2, ebx, methods, panel,
                            entry->edi, entry->ebp, NULL, 0);
    }
    return port_return(&port, result, entry->edx);
}
