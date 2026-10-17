#include "port_rtlflushes.h"

/* Flushes every open stream and returns how many were flushed. */

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

static void set_low8(uint32_t *reg, uint32_t value)
{
    *reg = (*reg & 0xffffff00u) | (value & 0xff);
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

/* Original 0x4e3e00: Flushes every open stream and returns how many were flushed. Evidence: calls
 * 0x4dae70, 0x4e3b60, 0x4e3ce0; reads 0x507ca0, 0x507ca4. Register-for-register from the listing
 * (0x4e3e00..0x4e3f20); labels are the original addresses. */
static void run(Regs *r)
{
    push_mem(r, r->ebx);
    push_mem(r, r->ecx);
    push_mem(r, r->esi);
    push_mem(r, r->edi);
    push_mem(r, r->ebp);
    r->ebx = r->eax;
    r->eax = rd32(r, r->edx + 0x10);
    call_mem(r, rd32(r, 0x507ca0), 5);
    r->eax = rd32(r, r->edx + 0x8);
    r->ecx = rd32(r, r->eax + 0xc);
    if (r->ecx == 0x1)
    {
        goto at_4e3e39;
    }
    if (r->ecx == 0)
    {
        goto at_4e3e32;
    }
    r->eax = rd32(r, r->edx + 0x10);
    call_mem(r, rd32(r, 0x507ca4), 0);
    r->eax = 0xffffffffu;
    goto at_4e3f0e;
at_4e3e32:
    wr32(r, r->eax + 0xc, 0x1);
at_4e3e39:
    if ((uint8_t)(rd8(r, r->edx + 0xc) & 0x2) != 0)
    {
        goto at_4e3e61;
    }
    r->eax = 0x4;
    call_mem_keep(r, 0x4dae70, 8);
    wr8(r, r->edx + 0xc, rd8(r, r->edx + 0xc) | 0x20);
    r->eax = rd32(r, r->edx + 0x10);
    call_mem(r, rd32(r, 0x507ca4), 0);
    r->eax = 0xffffffffu;
    r->ebp = pop_mem(r);
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    r->ecx = pop_mem(r);
    r->ebx = pop_mem(r);
    return;
at_4e3e61:
    r->eax = rd32(r, r->edx + 0x8);
    if (rd32(r, r->eax + 0x8) != 0x0)
    {
        goto at_4e3e71;
    }
    r->eax = r->edx;
    call_mem_keep(r, 0x4e3b60, 8);
at_4e3e71:
    r->ecx = 0x400;
    if (r->ebx != 0xa)
    {
        goto at_4e3ec2;
    }
    set_low8(&r->eax, rd8(r, r->edx + 0xc));
    r->ecx = 0x600;
    if ((uint8_t)((r->eax & 0xff) & 0x40) != 0)
    {
        goto at_4e3ec2;
    }
    wr8(r, r->edx + 0xd, rd8(r, r->edx + 0xd) | 0x10);
    r->eax = rd32(r, r->edx);
    wr8(r, r->eax, 0xd);
    r->ebp = rd32(r, r->edx);
    r->ebp = r->ebp + 1;
    r->eax = rd32(r, r->edx + 0x4);
    wr32(r, r->edx, r->ebp);
    r->eax = r->eax + 1;
    r->esi = rd32(r, r->edx + 0x14);
    wr32(r, r->edx + 0x4, r->eax);
    if (r->eax != r->esi)
    {
        goto at_4e3ec2;
    }
    r->eax = r->edx;
    call_mem_keep(r, 0x4e3ce0, 8);
    if (r->eax == 0)
    {
        goto at_4e3ec2;
    }
    r->eax = rd32(r, r->edx + 0x10);
    call_mem(r, rd32(r, 0x507ca4), 0);
    r->eax = 0xffffffffu;
    r->ebp = pop_mem(r);
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    r->ecx = pop_mem(r);
    r->ebx = pop_mem(r);
    return;
at_4e3ec2:
    wr8(r, r->edx + 0xd, rd8(r, r->edx + 0xd) | 0x10);
    r->eax = rd32(r, r->edx);
    wr8(r, r->eax, (r->ebx & 0xff));
    r->edi = rd32(r, r->edx);
    r->edi = r->edi + 1;
    r->ebp = rd32(r, r->edx + 0x4);
    wr32(r, r->edx, r->edi);
    r->ebp = r->ebp + 1;
    r->eax = rd32(r, r->edx + 0xc);
    wr32(r, r->edx + 0x4, r->ebp);
    if ((r->ecx & r->eax) != 0)
    {
        goto at_4e3ee2;
    }
    if (r->ebp != rd32(r, r->edx + 0x14))
    {
        goto at_4e3f01;
    }
at_4e3ee2:
    r->eax = r->edx;
    call_mem_keep(r, 0x4e3ce0, 8);
    if (r->eax == 0)
    {
        goto at_4e3f01;
    }
    r->eax = rd32(r, r->edx + 0x10);
    call_mem(r, rd32(r, 0x507ca4), 0);
    r->eax = 0xffffffffu;
    r->ebp = pop_mem(r);
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    r->ecx = pop_mem(r);
    r->ebx = pop_mem(r);
    return;
at_4e3f01:
    r->eax = rd32(r, r->edx + 0x10);
    call_mem(r, rd32(r, 0x507ca4), 0);
    r->eax = 0;
    set_low8(&r->eax, (r->ebx & 0xff));
at_4e3f0e:
    r->ebp = pop_mem(r);
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    r->ecx = pop_mem(r);
    r->ebx = pop_mem(r);
    return;
    wr8(r, r->eax, rd8(r, r->eax) + (r->eax & 0xff));
    wr8(r, r->eax, rd8(r, r->eax) + (r->eax & 0xff));
    wr8(r, r->eax, rd8(r, r->eax) + (r->eax & 0xff));
    wr8(r, r->eax, rd8(r, r->eax) + (r->eax & 0xff));
    wr8(r, r->eax, rd8(r, r->eax) + (r->eax & 0xff));
    wr8(r, r->eax, rd8(r, r->eax) + (r->eax & 0xff));
    r->eax = 0xffffffffu;
}

uint32_t vertrix_port_rtl_flush_all_streams_4e3e00(PORT_SIGNATURE)
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
