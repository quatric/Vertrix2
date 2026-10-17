#include "port_rtlrecordreleases.h"

/* Releases an exception record and its stream under a guard frame. */

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

static uint32_t rd8(Regs *r, uint32_t address)
{
    return port_u8(r->port, address, 0);
}

static uint32_t rd32(Regs *r, uint32_t address)
{
    return port_u32(r->port, address, 0);
}

static void wr8(Regs *r, uint32_t address, uint32_t value)
{
    port_set8(r->port, address, 0, value);
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

/* Original 0x4e0ec7: Releases an exception record and its stream under a guard frame. Evidence:
 * calls 0x4e37fe, 0x4e36d2, 0x4e36e4, 0x4e0e69, 0x4e6d16; reads 0x507c9c, 0x5c5c54.
 * Register-for-register from the listing (0x4e0ec7..0x4e0fba); labels are the original addresses.
 */
static void run(Regs *r)
{
    push_mem(r, r->esi);
    push_mem(r, r->edi);
    push_mem(r, r->ebp);
    r->esp = r->esp - 0x28;
    r->esi = r->eax;
    r->edi = r->edx;
    r->eax = r->esp + 0x14;
    push_mem(r, r->port->env.chain);
    r->tmp = pop_mem(r);
    wr32(r, r->eax, r->tmp);
    r->port->env.chain = r->eax;
    wr32(r, r->esp + 0x18, 0x4ec1ec);
    wr32(r, r->esp + 0x1c, 0x51bbac);
    wr32(r, r->esp + 0x20, 0x0);
    if (r->esi != 0)
    {
        goto at_4e0f11;
    }
at_4e0f00:
    r->eax = rd32(r, r->esp + 0x14);
    r->port->env.chain = r->eax;
    r->esp = r->esp + 0x28;
    r->ebp = pop_mem(r);
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    return;
at_4e0f11:
    r->eax = rd32(r, r->esi + 0x8);
    call_mem_keep(r, 0x4e37fe, 8);
    r->edx = r->eax;
    r->eax = rd8(r, r->eax);
    if (r->eax != 0)
    {
        goto at_4e0f84;
    }
at_4e0f22:
    r->ebp = rd32(r, r->edx + 0xc);
    if (r->ebp == 0)
    {
        goto at_4e0f76;
    }
    push_mem(r, r->ecx);
    push_mem(r, r->ebx);
    r->ecx = 0x6;
    r->eax = r->esp + 0x8;
    push_mem(r, r->esi);
    r->edx = r->edi;
    r->ebx = 0;
    call_mem(r, 0x4e36d2, 1);
    wr32(r, r->esp + 0x28, 0x1);
    r->eax = r->esi + 0x24;
    r->edx = 0;
    wr8(r, r->esi + 0xc, 0x6);
    call_mem(r, r->ebp, 0);
    wr32(r, r->esp + 0x18, 0x0);
    r->eax = r->esp + 0x8;
    r->edx = 0;
    wr32(r, r->esp + 0x28, 0x0);
    call_mem_keep(r, 0x4e36e4, 8);
    wr32(r, r->esp + 0x28, 0x0);
    r->ebx = pop_mem(r);
    r->ecx = pop_mem(r);
at_4e0f76:
    r->edx = r->esi;
    r->eax = r->edi;
    call_mem_keep(r, 0x4e0e69, 8);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4e0f00;
at_4e0f84:
    if (r->eax == 0x4 && !r->port->env.failed)
    {
        goto at_4e0f22;
    }
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4e0f76;
    r->esp = r->esp - 0x4;
    call_mem(r, rd32(r, 0x507c9c), 0);
    r->eax = r->eax + rd32(r, 0x5c5c54);
    if ((uint8_t)(rd8(r, r->eax + 0x4) & 0x2) != 0)
    {
        goto at_4e0fac;
    }
    r->eax = rd32(r, r->eax);
    if (r->eax == 0)
    {
        goto at_4e0fb0;
    }
    if ((uint8_t)(rd8(r, r->eax + 0x4) & 0x2) == 0)
    {
        goto at_4e0fb0;
    }
at_4e0fac:
    r->esp = r->esp + 0x4;
    return;
at_4e0fb0:
    r->eax = r->esp;
    call_mem_keep(r, 0x4e6d16, 8);
    r->esp = r->esp + 0x4;
    return;
}

uint32_t vertrix_port_rtl_record_release_guarded_4e0ec7(PORT_SIGNATURE)
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
