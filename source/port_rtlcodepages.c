#include "port_rtlcodepages.h"

/* Selects the multibyte code page: -1 for GetACP, -2 for GetOEMCP, -3 for the default, otherwise
 * the number given, and fills the ctype table. */

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

static void set_high8(uint32_t *reg, uint32_t value)
{
    *reg = (*reg & 0xffff00ffu) | ((value & 0xff) << 8);
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

/* Original 0x4e6f60: Selects the multibyte code page: -1 for GetACP, -2 for GetOEMCP, -3 for the
 * default, otherwise the number given, and fills the ctype table. Evidence: calls 0x4eb5c0; reads
 * 0x4f1b7c, 0x4f1bd0, 0x4f1b80; writes 0x5c8950, 0x50a820. Register-for-register from the listing
 * (0x4e6f60..0x4e70c2); labels are the original addresses. */
static void run(Regs *r)
{
    push_mem(r, r->ebx);
    push_mem(r, r->ecx);
    push_mem(r, r->edx);
    push_mem(r, r->esi);
    push_mem(r, r->ebp);
    r->esp = r->esp - 0x14;
    r->esi = r->eax;
    if (r->eax != 0xffffffffu)
    {
        goto at_4e6f7d;
    }
    call_mem(r, rd32(r, 0x4f1b7c), 5);
    r->esi = r->eax;
    goto at_4e7015;
at_4e6f7d:
    if (r->eax != 0xfffffffeu)
    {
        goto at_4e6f90;
    }
    call_mem(r, rd32(r, 0x4f1bd0), 0);
    r->esi = r->eax;
    goto at_4e7015;
at_4e6f90:
    if (r->eax != 0xfffffffdu)
    {
        goto at_4e6fbb;
    }
    r->ebx = 0x101;
    r->eax = 0x5c8960;
    r->edx = 0;
    call_mem_keep(r, 0x4eb5c0, 8);
    r->edx = 0;
    r->eax = 0;
    wr32(r, 0x5c8950, r->edx);
    wr32(r, 0x50a820, r->edx);
    goto at_4e70ba;
at_4e6fbb:
    if (r->eax != 0xfffffffcu)
    {
        goto at_4e7015;
    }
    r->ebx = 0x101;
    r->eax = 0x5c8960;
    r->edx = 0;
    call_mem_keep(r, 0x4eb5c0, 8);
    r->eax = 0x81;
    set_low8(&r->edx, 0x1);
at_4e6fd8:
    r->eax = r->eax + 1;
    wr8(r, r->eax + 0x5c8960, (r->edx & 0xff));
    if ((int32_t)r->eax <= (int32_t)0x9f && !r->port->env.failed)
    {
        goto at_4e6fd8;
    }
    r->eax = 0xe0;
    set_high8(&r->edx, 0x1);
at_4e6fed:
    r->eax = r->eax + 1;
    wr8(r, r->eax + 0x5c8960, ((r->edx >> 8) & 0xff));
    if ((int32_t)r->eax <= (int32_t)0xfc && !r->port->env.failed)
    {
        goto at_4e6fed;
    }
    r->ebp = 0x1;
    r->eax = 0x3a4;
    wr32(r, 0x5c8950, r->ebp);
    wr32(r, 0x50a820, r->eax);
    goto at_4e70b8;
at_4e7015:
    if (r->esi != 0)
    {
        goto at_4e701e;
    }
    r->esi = 0x1;
at_4e701e:
    r->eax = r->esp;
    push_mem(r, r->eax);
    push_mem(r, r->esi);
    call_mem(r, rd32(r, 0x4f1b80), 2);
    if (r->eax != 0)
    {
        goto at_4e703b;
    }
    r->eax = 0x1;
    r->esp = r->esp + 0x14;
    r->ebp = pop_mem(r);
    r->esi = pop_mem(r);
    r->edx = pop_mem(r);
    r->ecx = pop_mem(r);
    r->ebx = pop_mem(r);
    return;
at_4e703b:
    r->ebx = 0x101;
    r->eax = 0x5c8960;
    r->edx = 0;
    call_mem_keep(r, 0x4eb5c0, 8);
    r->ecx = 0;
    set_high8(&r->eax, rd8(r, r->esp + 0x6));
    wr32(r, 0x5c8950, r->ecx);
    if ((uint8_t)(((r->eax >> 8) & 0xff)) == 0)
    {
        goto at_4e7066;
    }
    wr32(r, 0x5c8950, 0x1);
at_4e7066:
    r->ebx = 0;
    set_low8(&r->ecx, 0x1);
    goto at_4e7088;
at_4e706c:
    r->eax = 0;
    set_low8(&r->eax, rd8(r, r->esp + r->ebx + 0x6));
    goto at_4e707b;
at_4e7074:
    r->eax = r->eax + 1;
    wr8(r, r->eax + 0x5c8960, (r->ecx & 0xff));
at_4e707b:
    r->edx = 0;
    set_low8(&r->edx, rd8(r, r->esp + r->ebx + 0x7));
    if ((int32_t)r->eax <= (int32_t)r->edx && !r->port->env.failed)
    {
        goto at_4e7074;
    }
    r->ebx = r->ebx + 0x2;
at_4e7088:
    if ((uint8_t)rd8(r, r->esp + r->ebx + 0x6) != (uint8_t)0x0 && !r->port->env.failed)
    {
        goto at_4e706c;
    }
    if ((uint8_t)rd8(r, r->esp + r->ebx + 0x7) != (uint8_t)0x0 && !r->port->env.failed)
    {
        goto at_4e706c;
    }
    if (r->esi != 0x1)
    {
        goto at_4e70b2;
    }
    call_mem(r, rd32(r, 0x4f1bd0), 0);
    wr32(r, 0x50a820, r->eax);
    r->eax = 0;
    r->esp = r->esp + 0x14;
    r->ebp = pop_mem(r);
    r->esi = pop_mem(r);
    r->edx = pop_mem(r);
    r->ecx = pop_mem(r);
    r->ebx = pop_mem(r);
    return;
at_4e70b2:
    wr32(r, 0x50a820, r->esi);
at_4e70b8:
    r->eax = 0;
at_4e70ba:
    r->esp = r->esp + 0x14;
    r->ebp = pop_mem(r);
    r->esi = pop_mem(r);
    r->edx = pop_mem(r);
    r->ecx = pop_mem(r);
    r->ebx = pop_mem(r);
    return;
}

uint32_t vertrix_port_rtl_set_code_page_4e6f60(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x40
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
