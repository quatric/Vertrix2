#include "port_rtlcurvetables.h"

/* Builds a curve table from logarithms when the sound device opens. */

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

static void call_mem_keep(Regs *r, uint32_t target, unsigned count)
{
    call_mem_with(r, target, count, 1);
}

/* Original 0x40ba00: Builds a curve table from logarithms when the sound device opens. Evidence:
 * calls 0x4c9e2f, 0x4eb892, 0x4d6768, 0x4db507, 0x4eb652; writes 0x52f1fc. Register-for-register
 * from the listing (0x40ba00..0x40baba); labels are the original addresses. */
static void run(Regs *r)
{
    push_mem(r, r->ebx);
    push_mem(r, r->ecx);
    push_mem(r, r->esi);
    push_mem(r, r->edi);
    push_mem(r, r->ebp);
    r->esp = r->esp - 0x8;
    r->edi = r->edx;
    if (r->eax == 0x1)
    {
        goto at_40ba23;
    }
    if (r->eax == 0x2)
    {
        goto at_40ba23;
    }
    if (r->eax == 0x3)
    {
        goto at_40ba23;
    }
    if (r->eax == 0x4)
    {
        goto at_40ba23;
    }
    if (r->eax != 0x5)
    {
        goto at_40ba87;
    }
at_40ba23:
    if (r->eax != 0x1)
    {
        goto at_40ba7c;
    }
    if (r->edi > 0x100)
    {
        goto at_40ba7c;
    }
    wr32(r, 0x52f1fc, 0xffffd8f0u);
    r->eax = 0;
    r->edx = 0x3f700000;
    call_mem_keep(r, 0x4c9e2f, 8);
    r->ebp = r->eax;
    wr32(r, r->esp, r->edx);
    wr32(r, r->esp + 0x4, r->edi);
    r->esi = 0x4;
at_40ba54:
    r->eax = r->edi;
    r->eax = r->eax >> 0x6;
    if (r->eax != 0)
    {
        goto at_40ba8e;
    }
    r->edx = 0xc0c38800u;
at_40ba62:
    call_mem_keep(r, 0x4eb892, 8);
    wr32(r, r->esi + 0x52f1fc, r->eax);
    r->edi = r->edi + rd32(r, r->esp + 0x4);
    r->esi = r->esi + 0x4;
    if (r->esi != 0x104 && !r->port->env.failed)
    {
        goto at_40ba54;
    }
at_40ba7c:
    r->eax = 0;
at_40ba7e:
    r->esp = r->esp + 0x8;
    r->ebp = pop_mem(r);
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    r->ecx = pop_mem(r);
    r->ebx = pop_mem(r);
    return;
at_40ba87:
    r->eax = 0x2;
    if (r->port->env.failed)
    {
        return;
    }
    goto at_40ba7e;
at_40ba8e:
    call_mem_keep(r, 0x4d6768, 8);
    r->ebx = 0;
    r->ecx = 0x3f700000;
    call_mem_keep(r, 0x4db507, 8);
    call_mem_keep(r, 0x4c9e2f, 8);
    r->ebx = 0;
    r->ecx = 0xc09f4000u;
    call_mem_keep(r, 0x4db507, 8);
    r->ebx = r->ebp;
    r->ecx = rd32(r, r->esp);
    call_mem_keep(r, 0x4eb652, 8);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_40ba62;
}

uint32_t vertrix_port_curve_table_build_40ba00(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x30
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
