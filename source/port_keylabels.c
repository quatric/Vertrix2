#include "port_keylabels.h"

/* The key actors' number labels. */

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

static uint32_t sign16(uint32_t value)
{
    return (uint32_t)(int32_t)(int16_t)value;
}

/* Original 0x4b5700 (guarded 0x5181d8): the number +0x180 of the actor eax (the edx 0x4ca070
 * leaves) is its label, "%u" (0x4cdfb0), or with +0x184 1 zero padded (0x4ca600 of 0x51109c) to
 * the width +0x188 (0x4ca650 of the "%u" text); a 0 with +0x190 clear is empty (0x4ca370). It is
 * drawn (0x4b65d0 with the style bl, the left cx and the three words of the stack arguments) and
 * the key child +0x18c placed (0x4b54d0) over cx..arg 1 by arg 2..arg 3. eax is the guard's link,
 * edx 0. */
uint32_t vertrix_port_key_actor_label_4b5700(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x34
    };
    Port port;
    uint8_t stack[BELOW + 8 + 4 * 3];
    uint32_t ebp = entry->esp - 4;
    uint32_t guard = 0x5181d8;
    uint32_t actor = entry->eax;
    uint32_t length;
    uint32_t width;
    uint32_t left;
    uint32_t top;
    uint32_t ebx = guard;
    uint32_t ecx = 0x4ec1ec;
    uint32_t edi = 0;
    uint32_t args[3];
    port_open_arguments(&port, stack, calls, services, globals, entry, BELOW, 3);
    port_set8(&port, ebp, -0xcu, entry->ebx);
    port_set16(&port, ebp, -0x10u, entry->ecx);
    guard_record(&port, ebp - 0x30, guard);
    port_call_with(&port, 0x4ca070, ebp - 0x1c, entry->edx, ebx, ecx, actor, edi, ebp);
    port_set32(&port, ebp, -0x24u, 1);
    port_set32(&port, actor, 0x180, vertrix_lift_edx);
    if (port_u32(&port, actor, 0x184) != 1)
    {
        ecx = port_u32(&port, actor, 0x180);
        args[0] = ebp - 0x1c;
        args[1] = 0x51109e;
        args[2] = ecx;
        call_frame(&port, 0x4cdfb0, ebp - 0x1c, vertrix_lift_edx, ebx, ecx, actor, edi, ebp, args,
                   3);
    }
    else
    {
        ebx = 2;
        port_call_with(&port, 0x4ca070, ebp - 0x18, vertrix_lift_edx, ebx, ecx, actor, edi, ebp);
        port_set32(&port, ebp, -0x24u, ebx);
        edi = port_u32(&port, actor, 0x180);
        args[0] = ebp - 0x18;
        args[1] = 0x511098;
        args[2] = edi;
        call_frame(&port, 0x4cdfb0, ebp - 0x18, vertrix_lift_edx, ebx, ecx, actor, edi, ebp, args,
                   3);
        port_call_with(&port, 0x4ca370, ebp - 0x1c, 0x51109b, ebx, ecx, actor, edi, ebp);
        length = port_u32(&port, port_u32(&port, ebp, -0x18u) - 0xc, 4);
        ecx = port_u32(&port, actor, 0x188);
        ebx = length;
        while (ecx > ebx && !port.env.failed)
        {
            edi = 0x51109c;
            ecx--;
            port_call_with(&port, 0x4ca600, ebp - 0x1c, edi, ebx, ecx, actor, edi, ebp);
        }
        port_call_with(&port, 0x4ca650, ebp - 0x1c, ebp - 0x18, ebx, ecx, actor, edi, ebp);
        port_set32(&port, ebp, -0x24u, 1);
        port_call_with(&port, 0x4ca210, ebp - 0x18, 0, ebx, ecx, actor, edi, ebp);
        port_set32(&port, ebp, -0x24u, 1);
    }
    if (port_u32(&port, actor, 0x190) == 0 && port_u32(&port, actor, 0x180) == 0)
    {
        port_call_with(&port, 0x4ca370, ebp - 0x1c, 0x5110a1, ebx, ecx, actor, edi, ebp);
    }
    left = sign16(port_u16(&port, ebp, -0x10u));
    top = sign16(port_u16(&port, ebp, 0xc));
    port_set32(&port, ebp, -0x14u, top);
    args[0] = sign16(port_u16(&port, ebp, 8));
    args[1] = top;
    args[2] = sign16(port_u16(&port, ebp, 0x10));
    call_frame(&port, 0x4b65d0, actor, port_u32(&port, ebp, -0x1cu),
               (uint32_t)(int32_t)(int8_t)port_u8(&port, ebp, -0xcu), left, actor, left, ebp, args,
               3);
    args[0] = (port_u32(&port, ebp, 0x10) - port_u32(&port, ebp, 0xc) + 1) & 0xffff;
    width = (port_u32(&port, ebp, 8) - port_u32(&port, ebp, -0x10u) + 1) & 0xffff;
    call_frame(&port, 0x4b54d0, port_u32(&port, actor, 0x18c), left, top, width, actor, left, ebp,
               args, 1);
    port_set32(&port, ebp, -0x24u, 0);
    port_call_with(&port, 0x4ca210, ebp - 0x1c, 0, top, width, actor, left, ebp);
    port_set32(&port, ebp, -0x24u, 0);
    return port_return(&port, port_u32(&port, ebp, -0x30u), 0);
}

/* Original 0x4b5a60 (guarded 0x518200): after the chain update (0x4ae150) and the key child's
 * method +4 (+0x18c), the number +0x180 becomes the text +0x15c (0x4ca310), "%u" or with +0x184 1
 * zero padded (0x4ca600 of 0x5110b0) to the width +0x188, empty for a 0 with +0x190 clear. A text
 * other than 0x5110b6 (0x4ccfe0) is measured (0x4408e0 with the style +0x160, the box +0x162..
 * +0x168 and the scale +0x44): the place goes to +0xe/+0x16 and the size to +0xf4/+0xf8. eax is
 * the guard's link; edx kept. */
uint32_t vertrix_port_key_actor_relabel_4b5a60(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x44
    };
    Port port;
    uint8_t stack[BELOW + 8];
    uint32_t ebp = entry->esp - 4;
    uint32_t guard = 0x518200;
    uint32_t actor = entry->eax;
    uint32_t child;
    uint32_t methods;
    uint32_t length;
    uint32_t text;
    uint32_t ebx = 0;
    uint32_t ecx = guard;
    uint32_t measured = 0;
    uint32_t args[7];
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    guard_record(&port, ebp - 0x40, guard);
    port_call_with(&port, 0x4ae150, actor, 0x4ec1ec, ebx, ecx, actor, entry->edi, ebp);
    child = port_u32(&port, actor, 0x18c);
    methods = port_u32(&port, child, 0x158);
    port_call_with(&port, port_u32(&port, methods, 4), child, methods, ebx, ecx, actor, entry->edi,
                   ebp);
    port_call_with(&port, 0x4ca070, ebp - 0x2c, vertrix_lift_edx, ebx, ecx, actor, 1, ebp);
    port_set32(&port, ebp, -0x34u, 1);
    if (port_u32(&port, actor, 0x184) != 1)
    {
        args[0] = ebp - 0x2c;
        args[1] = 0x5110b2;
        args[2] = port_u32(&port, actor, 0x180);
        call_frame(&port, 0x4cdfb0, ebp - 0x2c, args[2], ebx, ecx, actor, 1, ebp, args, 3);
    }
    else
    {
        ecx = 2;
        port_call_with(&port, 0x4ca070, ebp - 0x20, vertrix_lift_edx, ebx, ecx, actor, 1, ebp);
        port_set32(&port, ebp, -0x34u, ecx);
        ebx = port_u32(&port, actor, 0x180);
        args[0] = ebp - 0x20;
        args[1] = 0x5110ac;
        args[2] = ebx;
        call_frame(&port, 0x4cdfb0, ebp - 0x20, vertrix_lift_edx, ebx, ecx, actor, 1, ebp, args, 3);
        port_call_with(&port, 0x4ca370, ebp - 0x2c, 0x5110af, ebx, ecx, actor, 1, ebp);
        length = port_u32(&port, port_u32(&port, ebp, -0x20u) - 0xc, 4);
        ecx = port_u32(&port, actor, 0x188);
        ebx = length;
        while (ecx > ebx && !port.env.failed)
        {
            ecx--;
            port_call_with(&port, 0x4ca600, ebp - 0x2c, 0x5110b0, ebx, ecx, actor, 1, ebp);
        }
        port_call_with(&port, 0x4ca650, ebp - 0x2c, ebp - 0x20, ebx, ecx, actor, 1, ebp);
        port_set32(&port, ebp, -0x34u, 1);
        port_call_with(&port, 0x4ca210, ebp - 0x20, 0, ebx, ecx, actor, 1, ebp);
        port_set32(&port, ebp, -0x34u, 1);
    }
    if (port_u32(&port, actor, 0x190) == 0 && port_u32(&port, actor, 0x180) == 0)
    {
        port_call_with(&port, 0x4ca370, ebp - 0x2c, 0x5110b5, ebx, ecx, actor, 1, ebp);
    }
    ecx = actor + 0x15c;
    port_call_with(&port, 0x4ca310, ecx, ebp - 0x2c, ebx, ecx, actor, 1, ebp);
    text = port_u32(&port, ecx, 0);
    if (port_call_with(&port, 0x4ccfe0, text, 0x5110b6, ebx, ecx, actor, 1, ebp) != 0)
    {
        ebx = sign16(port_u16(&port, actor, 0x164));
        ecx = sign16(port_u16(&port, actor, 0x166));
        args[0] = sign16(port_u16(&port, actor, 0x168));
        args[1] = port_u32(&port, actor, 0x15c);
        args[2] = port_u8(&port, actor, 0x44);
        args[3] = ebp - 0x28;
        args[4] = ebp - 0x24;
        args[5] = ebp - 0x1c;
        args[6] = ebp - 0x18;
        call_frame(&port, 0x4408e0, (uint32_t)(int32_t)(int8_t)port_u8(&port, actor, 0x160),
                   sign16(port_u16(&port, actor, 0x162)), ebx, ecx, actor, 1, ebp, args, 7);
        port_set16(&port, actor, 0xe, port_u16(&port, ebp, -0x1cu));
        port_set16(&port, actor, 0x16, port_u16(&port, ebp, -0x18u));
        port_set32(&port, actor, 0xf4, port_u32(&port, ebp, -0x28u));
        port_set32(&port, actor, 0xf8, port_u32(&port, ebp, -0x24u));
        ebx = 0;
        measured = 1;
        port_set32(&port, ebp, -0x34u, 0);
    }
    port_call_with(&port, 0x4ca210, ebp - 0x2c, 0, ebx, ecx, actor, 1, ebp);
    if (measured)
    {
        port_set32(&port, ebp, -0x34u, 0);
    }
    return port_return(&port, port_u32(&port, ebp, -0x40u), entry->edx);
}
