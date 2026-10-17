#include "port_rtlnetworkhandles.h"

/* Unless [0x5bb4a4] is set, closes the network handles kept at 0x5bb47c. */

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

static uint32_t rd32(Regs *r, uint32_t address)
{
    return port_u32(r->port, address, 0);
}

static void wr32(Regs *r, uint32_t address, uint32_t value)
{
    port_set32(r->port, address, 0, value);
}

/* The emulated stack of a routine without a frame pointer: pushes and pops move esp. */
static void push_mem(Regs *r, uint32_t value)
{
    r->esp -= 4;
    wr32(r, r->esp, value);
}

static uint32_t pop_mem(Regs *r)
{
    uint32_t value = rd32(r, r->esp);
    r->esp += 4;
    return value;
}

/* A call taking count stack arguments from esp up; the callee pops them unless kept (cdecl). */
static void call_mem_with(Regs *r, uint32_t target, unsigned count, int keep)
{
    uint32_t args[32] = {0};
    unsigned i;
    for (i = 0; i < count && i < 32; i++)
    {
        args[i] = rd32(r, r->esp + 4 * i);
    }
    vertrix_lift_in_esi = r->esi;
    vertrix_lift_in_edi = r->edi;
    vertrix_lift_in_ebp = r->ebp;
    r->eax =
        lift_call_arguments(&r->port->env, target, r->eax, r->edx, r->ebx, r->ecx, args, count);
    vertrix_lift_in_esi = vertrix_lift_in_edi = vertrix_lift_in_ebp = 0;
    r->edx = vertrix_lift_edx;
    if (!keep)
    {
        r->esp += 4 * count;
    }
}

static void call_mem(Regs *r, uint32_t target, unsigned count)
{
    call_mem_with(r, target, count, 0);
}

static void call_mem_keep(Regs *r, uint32_t target, unsigned count)
{
    call_mem_with(r, target, count, 1);
}

/* Original 0x48b970: Unless [0x5bb4a4] is set, closes the network handles kept at 0x5bb47c..
 * (CloseHandle) and clears them. Evidence: calls 0x47eba0, 0x415b10, 0x48c2e0, 0x48c2b0, 0x47ecd0;
 * reads 0x5bb4a4, 0x5bb47c, 0x4f1b2c, 0x5bb480, 0x5bb484, 0x5bb488, 0x5bb48c, 0x5bb490, 0x5bb494,
 * 0x5bb498, 0x5bb49c, 0x5bb4a0, 0x4f1ca0, 0x4f1c7c; writes 0x5bb47c, 0x5bb480, 0x5bb484, 0x5bb488,
 * 0x5bb48c, 0x5bb490, 0x5bb494, 0x5bb498, 0x5bb49c, 0x5bb4a4, 0x5bb4a0. Register-for-register from
 * the listing (0x48b970..0x48bb7e); labels are the original addresses. */
static void run(Regs *r)
{
    push_mem(r, r->ebx);
    push_mem(r, r->ecx);
    push_mem(r, r->edx);
    push_mem(r, r->esi);
    r->edx = rd32(r, 0x5bb4a4);
    if (r->edx != 0)
    {
        goto at_48ba7b;
    }
at_48b982:
    r->esi = rd32(r, 0x5bb47c);
    if (r->esi == 0)
    {
        goto at_48b99b;
    }
    push_mem(r, r->esi);
    call_mem(r, rd32(r, 0x4f1b2c), 1);
    r->eax = 0;
    wr32(r, 0x5bb47c, r->eax);
at_48b99b:
    r->edx = rd32(r, 0x5bb480);
    if (r->edx == 0)
    {
        goto at_48b9b5;
    }
    push_mem(r, r->edx);
    r->ebx = 0;
    call_mem(r, rd32(r, 0x4f1b2c), 1);
    wr32(r, 0x5bb480, r->ebx);
at_48b9b5:
    r->esi = rd32(r, 0x5bb484);
    if (r->esi == 0)
    {
        goto at_48b9ce;
    }
    push_mem(r, r->esi);
    call_mem(r, rd32(r, 0x4f1b2c), 1);
    r->eax = 0;
    wr32(r, 0x5bb484, r->eax);
at_48b9ce:
    r->edx = rd32(r, 0x5bb488);
    if (r->edx == 0)
    {
        goto at_48b9e8;
    }
    push_mem(r, r->edx);
    r->ebx = 0;
    call_mem(r, rd32(r, 0x4f1b2c), 1);
    wr32(r, 0x5bb488, r->ebx);
at_48b9e8:
    r->esi = rd32(r, 0x5bb48c);
    if (r->esi == 0)
    {
        goto at_48ba01;
    }
    push_mem(r, r->esi);
    call_mem(r, rd32(r, 0x4f1b2c), 1);
    r->eax = 0;
    wr32(r, 0x5bb48c, r->eax);
at_48ba01:
    r->edx = rd32(r, 0x5bb490);
    if (r->edx == 0)
    {
        goto at_48ba1b;
    }
    push_mem(r, r->edx);
    r->ebx = 0;
    call_mem(r, rd32(r, 0x4f1b2c), 1);
    wr32(r, 0x5bb490, r->ebx);
at_48ba1b:
    r->esi = rd32(r, 0x5bb494);
    if (r->esi == 0)
    {
        goto at_48ba34;
    }
    push_mem(r, r->esi);
    call_mem(r, rd32(r, 0x4f1b2c), 1);
    r->eax = 0;
    wr32(r, 0x5bb494, r->eax);
at_48ba34:
    r->edx = rd32(r, 0x5bb498);
    if (r->edx == 0)
    {
        goto at_48ba4e;
    }
    push_mem(r, r->edx);
    r->ebx = 0;
    call_mem(r, rd32(r, 0x4f1b2c), 1);
    wr32(r, 0x5bb498, r->ebx);
at_48ba4e:
    r->esi = rd32(r, 0x5bb49c);
    if (r->esi == 0)
    {
        goto at_48ba67;
    }
    push_mem(r, r->esi);
    call_mem(r, rd32(r, 0x4f1b2c), 1);
    r->eax = 0;
    wr32(r, 0x5bb49c, r->eax);
at_48ba67:
    r->edx = rd32(r, 0x5bb4a0);
    if (r->edx != 0)
    {
        goto at_48ba90;
    }
    r->eax = 0x1;
    r->esi = pop_mem(r);
    r->edx = pop_mem(r);
    r->ecx = pop_mem(r);
    r->ebx = pop_mem(r);
    return;
at_48ba7b:
    push_mem(r, r->edx);
    r->ebx = 0;
    call_mem(r, rd32(r, 0x4f1b2c), 1);
    wr32(r, 0x5bb4a4, r->ebx);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_48b982;
at_48ba90:
    push_mem(r, r->edx);
    r->ebx = 0;
    call_mem(r, rd32(r, 0x4f1b2c), 1);
    wr32(r, 0x5bb4a0, r->ebx);
    r->eax = 0x1;
    r->esi = pop_mem(r);
    r->edx = pop_mem(r);
    r->ecx = pop_mem(r);
    r->ebx = pop_mem(r);
    return;
    push_mem(r, r->ebx);
    push_mem(r, r->ecx);
    push_mem(r, r->esi);
    push_mem(r, r->edi);
    r->ecx = r->eax;
    r->ebx = r->edx;
    call_mem_keep(r, 0x47eba0, 8);
    r->esi = r->eax;
    if ((int32_t)r->eax < 0)
    {
        goto at_48bad1;
    }
    r->eax = rd32(r, r->ebx + 0x4);
    if (r->eax == rd32(r, r->ecx + 0x34))
    {
        goto at_48bad1;
    }
    if (rd32(r, r->ecx + 0x44) != 0x0)
    {
        goto at_48bad8;
    }
at_48bad1:
    r->eax = r->esi;
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    r->ecx = pop_mem(r);
    r->ebx = pop_mem(r);
    return;
at_48bad8:
    call_mem_keep(r, 0x415b10, 8);
    r->ebx = rd32(r, r->ecx + 0x1c8);
    r->eax = r->ecx;
    call_mem(r, rd32(r, r->ebx + 0x2c), 0);
    r->eax = r->ecx;
    call_mem_keep(r, 0x48c2e0, 8);
    r->eax = r->ecx;
    call_mem_keep(r, 0x48c2b0, 8);
    r->edi = rd32(r, 0x5bb480);
    push_mem(r, r->edi);
    call_mem(r, rd32(r, 0x4f1ca0), 1);
    r->eax = rd32(r, 0x5bb488);
    push_mem(r, r->eax);
    call_mem(r, rd32(r, 0x4f1c7c), 1);
    r->edx = rd32(r, 0x5bb494);
    push_mem(r, r->edx);
    call_mem(r, rd32(r, 0x4f1c7c), 1);
    r->eax = r->esi;
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    r->ecx = pop_mem(r);
    r->ebx = pop_mem(r);
    return;
    push_mem(r, r->ebx);
    push_mem(r, r->ecx);
    push_mem(r, r->esi);
    r->ebx = r->eax;
    r->ecx = r->edx;
    call_mem_keep(r, 0x47ecd0, 8);
    r->ecx = rd32(r, r->ecx + 0x4);
    r->edx = rd32(r, r->ebx + 0x38);
    r->esi = r->eax;
    if (r->ecx == r->edx)
    {
        goto at_48bb59;
    }
    r->ecx = rd32(r, r->ebx + 0x1c8);
    r->eax = r->ebx;
    call_mem(r, rd32(r, r->ecx + 0x2c), 0);
    r->eax = r->esi;
    r->esi = pop_mem(r);
    r->ecx = pop_mem(r);
    r->ebx = pop_mem(r);
    return;
at_48bb59:
    r->ecx = rd32(r, 0x5bb488);
    push_mem(r, r->ecx);
    call_mem(r, rd32(r, 0x4f1ca0), 1);
    wr32(r, r->ebx + 0x38, 0x0);
    r->ecx = rd32(r, r->ebx + 0x1c8);
    r->eax = r->ebx;
    call_mem(r, rd32(r, r->ecx + 0x2c), 0);
    r->eax = r->esi;
    r->esi = pop_mem(r);
    r->ecx = pop_mem(r);
    r->ebx = pop_mem(r);
    return;
}

uint32_t vertrix_port_network_handles_close_48b970(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x50
    };
    Port port;
    uint8_t stack[BELOW + 8 + 4 * 8];
    Regs r;
    port_open_arguments(&port, stack, calls, services, globals, entry, BELOW, 8);
    memset(&r, 0, sizeof r);
    r.port = &port;
    r.eax = entry->eax;
    r.edx = entry->edx;
    r.ebx = entry->ebx;
    r.ecx = entry->ecx;
    r.esi = entry->esi;
    r.edi = entry->edi;
    r.ebp = entry->ebp;
    r.esp = entry->esp;
    run(&r);
    return port_return(&port, r.eax, r.edx);
}
