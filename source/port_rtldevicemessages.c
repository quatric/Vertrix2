#include "port_rtldevicemessages.h"

/* A three-argument stdcall callback (ret 0xc): message codes 5..0x16 go through the table at
 * 0x47ea64 to the methods of the device object [0x558ccc] (its vtable at +0x1c8, or 0x47ed10 and
 * 0x47eeb0) with the third argument; other codes return 0. */

typedef struct
{
    Port *port;
    uint32_t eax;
    uint32_t edx;
    uint32_t ebx;
    uint32_t ecx;
    uint32_t esi;
    uint32_t edi;
    uint32_t ebp;
    uint32_t esp;
    uint32_t tmp;
    uint32_t stack[32];
    unsigned pushed;
    uint32_t fa;
    uint32_t fb;
    unsigned fk;
    unsigned fw;
    uint32_t fc;
} Regs;

/* The kinds of the last flag-setting instruction: a subtraction or compare of fa and fb, an
 * addition, a logical result fa (CF and OF clear), and inc / dec of the result fa (CF kept). */
enum
{
    F_SUB,
    F_ADD,
    F_LOGIC,
    F_INC,
    F_DEC
};

/* The conditions of the jumps and sets. */
enum
{
    CC_E,
    CC_NE,
    CC_B,
    CC_AE,
    CC_BE,
    CC_A,
    CC_L,
    CC_GE,
    CC_LE,
    CC_G,
    CC_S,
    CC_NS
};

/* A call of the tracked registers taking the last count values pushed (nearest first) and, unless
 * kept, popping them as the callee's ret does. */
static void call_with_stack(Regs *r, uint32_t target, unsigned count, int keep)
{
    uint32_t args[32] = {0};
    unsigned i;
    if (count > r->pushed)
    {
        count = r->pushed;
    }
    for (i = 0; i < count; i++)
    {
        args[i] = r->stack[r->pushed - 1 - i];
    }
    if (!keep)
    {
        r->pushed -= count;
    }
    vertrix_lift_in_esi = r->esi;
    vertrix_lift_in_edi = r->edi;
    vertrix_lift_in_ebp = r->ebp;
    r->eax =
        lift_call_arguments(&r->port->env, target, r->eax, r->edx, r->ebx, r->ecx, args, count);
    vertrix_lift_in_esi = vertrix_lift_in_edi = vertrix_lift_in_ebp = 0;
    r->edx = vertrix_lift_edx;
}

/* A call that pops nothing (cdecl, or no stack arguments): every value pushed passed and left for
 * the caller's add esp. */
static void call_keep(Regs *r, uint32_t target)
{
    call_with_stack(r, target, r->pushed, 1);
}

static uint32_t rd32(Regs *r, uint32_t address)
{
    return port_u32(r->port, address, 0);
}

/* An indirect call (an import or a method): every value pushed passed and popped, as stdcall. */
static void call_all(Regs *r, uint32_t target)
{
    call_with_stack(r, target, r->pushed, 0);
}

/* Original 0x47eab0: A three-argument stdcall callback (ret 0xc): message codes 5..0x16 go through
 * the table at 0x47ea64 to the methods of the device object [0x558ccc] (its vtable at +0x1c8, or
 * 0x47ed10 and 0x47eeb0) with the third argument; other codes return 0. Evidence: calls 0x47ed10,
 * 0x47eeb0; reads 0x558ccc. Register-for-register from the listing (0x47eab4..0x47eb58); labels are
 * the original addresses. */
static void run(Regs *r)
{
    r->eax = rd32(r, r->ebp + 0x10);
    r->ecx = rd32(r, r->ebp + 0xc);
    r->ecx = r->ecx + 0xfffb;
    if (r->ecx > 0x11)
    {
        goto at_47eacc;
    }
    switch (r->ecx)
    {
        case 0:
            goto at_47eacc;
        case 1:
            goto at_47eacc;
        case 2:
            goto at_47ead3;
        case 3:
            goto at_47eacc;
        case 4:
            goto at_47eaeb;
        case 5:
            goto at_47eacc;
        case 6:
            goto at_47eb2f;
        case 7:
            goto at_47eacc;
        case 8:
            goto at_47eacc;
        case 9:
            goto at_47eacc;
        case 10:
            goto at_47eacc;
        case 11:
            goto at_47eacc;
        case 12:
            goto at_47eb1b;
        case 13:
            goto at_47eacc;
        case 14:
            goto at_47eacc;
        case 15:
            goto at_47eb43;
        case 16:
            goto at_47eacc;
        case 17:
            goto at_47eb03;
        default:
            r->port->env.failed = 1;
            return;
    }
at_47eacc:
    r->eax = 0;
    r->ebx = rd32(r, r->ebp - 0x4);
    return;
at_47ead3:
    r->ecx = rd32(r, 0x558ccc);
    r->ebx = rd32(r, r->ecx + 0x1c8);
    r->edx = r->eax;
    r->eax = r->ecx;
    call_all(r, rd32(r, r->ebx + 0x8));
    r->ebx = rd32(r, r->ebp - 0x4);
    return;
at_47eaeb:
    r->ecx = rd32(r, 0x558ccc);
    r->ebx = rd32(r, r->ecx + 0x1c8);
    r->edx = r->eax;
    r->eax = r->ecx;
    call_all(r, rd32(r, r->ebx + 0xc));
    r->ebx = rd32(r, r->ebp - 0x4);
    return;
at_47eb03:
    r->ecx = rd32(r, 0x558ccc);
    r->ebx = rd32(r, r->ecx + 0x1c8);
    r->edx = r->eax;
    r->eax = r->ecx;
    call_all(r, rd32(r, r->ebx + 0x10));
    r->ebx = rd32(r, r->ebp - 0x4);
    return;
at_47eb1b:
    r->ecx = rd32(r, 0x558ccc);
    r->edx = r->eax;
    r->eax = r->ecx;
    call_keep(r, 0x47ed10);
    r->ebx = rd32(r, r->ebp - 0x4);
    return;
at_47eb2f:
    r->ecx = rd32(r, 0x558ccc);
    r->edx = r->eax;
    r->eax = r->ecx;
    call_keep(r, 0x47eeb0);
    r->ebx = rd32(r, r->ebp - 0x4);
    return;
at_47eb43:
    r->ecx = rd32(r, 0x558ccc);
    r->ebx = rd32(r, r->ecx + 0x1c8);
    r->edx = r->eax;
    r->eax = r->ecx;
    call_all(r, rd32(r, r->ebx + 0x18));
    r->ebx = rd32(r, r->ebp - 0x4);
    return;
}

uint32_t vertrix_port_device_message_dispatch_47eab0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x8
    };
    Port port;
    uint8_t stack[BELOW + 8 + 4 * 3];
    Regs r;
    port_open_arguments(&port, stack, calls, services, globals, entry, BELOW, 3);
    memset(&r, 0, sizeof r);
    r.port = &port;
    r.eax = entry->eax;
    r.edx = entry->edx;
    r.ebx = entry->ebx;
    r.ecx = entry->ecx;
    r.esi = entry->esi;
    r.edi = entry->edi;
    r.ebp = entry->esp - 4;
    port_set32(&port, r.ebp, 0, entry->ebp);
    port_set32(&port, r.ebp, -0x4u, entry->ebx);
    run(&r);
    return port_return(&port, r.eax, r.edx);
}
