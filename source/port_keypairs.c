#include "port_keypairs.h"

/* The text actors with key children. */

/* The guard record (0x4ec1ec, `guard`) of a frame routine at `record`. */
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

/* Original 0x4b3a00 (guarded 0x517d30): the text actor eax (0x4b3100) takes the methods 0x517dc4
 * and clears +0x170..+0x178; two 0x160-byte key children (0x4ca000, built by 0x4b5400, the first
 * with edx 2 and the second with ebx 4) go to +0x17c and +0x180, each set up (0x4adf20 with five
 * zero arguments, 0x4b54d0 with one); +0x184..+0x18c are cleared. eax is the actor. */
uint32_t vertrix_port_key_pair_actor_construct_4b3a00(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x3c
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t guard = 0x517d30;
    uint32_t self = entry->eax;
    uint32_t actor;
    uint32_t child;
    uint32_t args[5] = {0, 0, 0, 0, 0};
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    guard_record(&port, ebp - 0x38, guard);
    port_set8(&port, ebp, -0x20u, 0);
    port_set32(&port, ebp, -0x24u, self);
    actor = port_call_with(&port, 0x4b3100, self, 0x4ec1ec, 0, guard, self, 1, ebp);
    port_set32(&port, ebp, -0x2cu, 1);
    port_set32(&port, actor, 0x158, 0x517dc4);
    port_set32(&port, actor, 0x170, 0);
    port_set32(&port, actor, 0x174, 0);
    port_set32(&port, actor, 0x178, 0);
    child = port_call_with(&port, 0x4ca000, 0x160, vertrix_lift_edx, 0, guard, actor, 1, ebp);
    if (child != 0)
    {
        port_set32(&port, ebp, -0x18u, child);
        port_set32(&port, ebp, -0x2cu, 2);
        child = port_call_with(&port, 0x4b5400, child, 2, 0, guard, actor, 1, ebp);
        port_set32(&port, ebp, -0x2cu, 1);
    }
    port_set32(&port, actor, 0x17c, child);
    call_frame(&port, 0x4adf20, child, 0, 0, 0, actor, 1, ebp, args, 5);
    call_frame(&port, 0x4b54d0, port_u32(&port, actor, 0x17c), 0, 0, 0, actor, 1, ebp, args, 1);
    child = port_call_with(&port, 0x4ca000, 0x160, vertrix_lift_edx, 0, 0, actor, 1, ebp);
    if (child != 0)
    {
        port_set32(&port, ebp, -0x18u, child);
        port_set32(&port, ebp, -0x2cu, 4);
        child = port_call_with(&port, 0x4b5400, child, vertrix_lift_edx, 4, 0, actor, 1, ebp);
        port_set32(&port, ebp, -0x2cu, 1);
    }
    port_set32(&port, actor, 0x180, child);
    call_frame(&port, 0x4adf20, child, 0, 0, 0, actor, 1, ebp, args, 5);
    call_frame(&port, 0x4b54d0, port_u32(&port, actor, 0x180), 0, 0, 0, actor, 1, ebp, args, 1);
    port_set32(&port, actor, 0x184, 0);
    port_set32(&port, actor, 0x188, 0);
    port_set32(&port, actor, 0x18c, 0);
    return port_return(&port, actor, entry->edx);
}

/* Original 0x4b42e0 (guarded 0x517e80): the text actor eax (0x4b3100) clears its texts +0x188
 * and +0x18c (0x4ca070, the actor taken back from the second's eax), takes the methods 0x518014,
 * +0x170 -1 and clears +0x174, +0x178 and +0x180; a 0x160-byte key child (0x4ca000, built by
 * 0x4b5400) goes to +0x17c, set up (0x4adf20 with five zero arguments, 0x4b54d0 with one); +0x184
 * is cleared and the texts set to 0x511092 and 0x511093 (0x4ca370). eax is the actor. */
uint32_t vertrix_port_key_text_actor_construct_4b42e0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x38
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t guard = 0x517e80;
    uint32_t self = entry->eax;
    uint32_t actor;
    uint32_t child;
    uint32_t text;
    uint32_t args[5] = {0, 0, 0, 0, 0};
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    guard_record(&port, ebp - 0x34, guard);
    port_set8(&port, ebp, -0x1cu, 0);
    port_set32(&port, ebp, -0x20u, self);
    actor = port_call_with(&port, 0x4b3100, self, 0x4ec1ec, 0, guard, self, 2, ebp);
    port_set32(&port, ebp, -0x28u, 1);
    text = port_call_with(&port, 0x4ca070, actor + 0x188, vertrix_lift_edx, 0, guard, 1, 2, ebp);
    port_set32(&port, ebp, -0x28u, 2);
    text = port_call_with(&port, 0x4ca070, text + 4, vertrix_lift_edx, 0, guard, 1, 2, ebp);
    actor = text - 0x18c;
    port_set32(&port, ebp, -0x28u, 3);
    port_set32(&port, actor, 0x158, 0x518014);
    port_set32(&port, actor, 0x170, 0xffffffffu);
    port_set32(&port, actor, 0x174, 0);
    port_set32(&port, actor, 0x178, 0);
    port_set32(&port, actor, 0x180, 0);
    child = port_call_with(&port, 0x4ca000, 0x160, vertrix_lift_edx, 0, guard, actor, 2, ebp);
    if (child != 0)
    {
        child = port_call_with(&port, 0x4b5400, child, vertrix_lift_edx, 0, guard, actor, 2, ebp);
    }
    port_set32(&port, actor, 0x17c, child);
    call_frame(&port, 0x4adf20, child, 0, 0, 0, actor, 2, ebp, args, 5);
    call_frame(&port, 0x4b54d0, port_u32(&port, actor, 0x17c), 0, 0, 0, actor, 2, ebp, args, 1);
    port_set32(&port, actor, 0x184, 0);
    port_call_with(&port, 0x4ca370, actor + 0x188, 0x511092, 0, 0, actor, 2, ebp);
    port_call_with(&port, 0x4ca370, actor + 0x18c, 0x511093, 0, 0, actor, 2, ebp);
    return port_return(&port, actor, entry->edx);
}
