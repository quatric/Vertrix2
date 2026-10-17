#include "port_rtlancestors.h"

/* Searches a window's owner and parent chain for a matching runtime object. */

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

/* Original 0x4d4390: Searches a window's owner and parent chain for a matching runtime object.
 * Evidence: calls 0x4d1890, 0x4d1900, 0x4cf910, 0x4d4390, 0x4c9ff0, 0x4ca040; reads 0x4f1978,
 * 0x4f1a04, 0x4f1a24, 0x4f1a94, 0x4f1948, 0x4f1a2c, 0x4f19f0, 0x4f1af0. Register-for-register from
 * the listing (0x4d4390..0x4d4628); labels are the original addresses. */
static void run(Regs *r)
{
    push_mem(r, r->ebx);
    r->ebx = rd32(r, r->esp + 0x8);
    r->edx = rd32(r, r->esp + 0xc);
    if (r->ebx != r->edx)
    {
        goto at_4d43a6;
    }
at_4d439d:
    r->eax = 0x1;
    r->ebx = pop_mem(r);
    return;
at_4d43a6:
    push_mem(r, r->edx);
    call_mem(r, 0x4d1890, 1);
    r->edx = r->eax;
    if (r->eax == 0)
    {
        goto at_4d43b8;
    }
    if (r->ebx == r->eax && !r->port->env.failed)
    {
        goto at_4d439d;
    }
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4d43a6;
at_4d43b8:
    r->ebx = pop_mem(r);
    return;
    wr8(r, r->eax, rd8(r, r->eax) + (r->eax & 0xff));
    wr8(r, r->eax, rd8(r, r->eax) + (r->eax & 0xff));
    push_mem(r, r->ebx);
    push_mem(r, r->ecx);
    push_mem(r, r->edx);
    push_mem(r, r->esi);
    push_mem(r, r->edi);
    push_mem(r, r->ebp);
    r->ebp = r->eax;
    wr32(r, r->eax + 0xa0, rd32(r, r->eax + 0xa0) + 1);
    if (rd32(r, r->eax + 0xa0) > 0x1)
    {
        goto at_4d44e5;
    }
    call_mem_keep(r, 0x4d1900, 8);
    push_mem(r, 0x5);
    r->esi = r->eax;
    call_mem(r, rd32(r, 0x4f1978), 1);
    push_mem(r, r->eax);
    r->edi = 0;
    call_mem(r, rd32(r, 0x4f1a04), 1);
    r->ebx = r->eax;
    if (r->eax == 0)
    {
        goto at_4d4444;
    }
at_4d43fb:
    push_mem(r, r->ebx);
    call_mem(r, rd32(r, 0x4f1a24), 1);
    if (r->eax == 0)
    {
        goto at_4d4434;
    }
    push_mem(r, r->ebx);
    call_mem(r, 0x4cf910, 1);
    if (r->eax == 0)
    {
        goto at_4d4434;
    }
    push_mem(r, r->ebx);
    push_mem(r, rd32(r, r->esi + 0x1c));
    call_mem(r, 0x4d4390, 2);
    if (r->eax == 0)
    {
        goto at_4d4434;
    }
    push_mem(r, 0x0);
    push_mem(r, 0x0);
    push_mem(r, 0x36c);
    push_mem(r, r->ebx);
    call_mem(r, rd32(r, 0x4f1a94), 4);
    if (r->eax != 0)
    {
        goto at_4d4434;
    }
    r->edi = r->edi + 1;
at_4d4434:
    push_mem(r, 0x2);
    push_mem(r, r->ebx);
    call_mem(r, rd32(r, 0x4f1a04), 2);
    r->ebx = r->eax;
    if (r->eax != 0 && !r->port->env.failed)
    {
        goto at_4d43fb;
    }
at_4d4444:
    if (r->edi == 0)
    {
        goto at_4d44e5;
    }
    r->eax = r->edi * 4;
    r->eax = r->eax + 0x4;
    call_mem_keep(r, 0x4c9ff0, 8);
    push_mem(r, 0x5);
    wr32(r, r->ebp + 0xa4, r->eax);
    call_mem(r, rd32(r, 0x4f1978), 1);
    push_mem(r, r->eax);
    r->edi = 0;
    call_mem(r, rd32(r, 0x4f1a04), 1);
    r->ebx = r->eax;
    if (r->eax == 0)
    {
        goto at_4d44d8;
    }
at_4d447a:
    push_mem(r, r->ebx);
    call_mem(r, rd32(r, 0x4f1a24), 1);
    if (r->eax == 0)
    {
        goto at_4d44c8;
    }
    push_mem(r, r->ebx);
    call_mem(r, 0x4cf910, 1);
    if (r->eax == 0)
    {
        goto at_4d44c8;
    }
    push_mem(r, r->ebx);
    push_mem(r, rd32(r, r->esi + 0x1c));
    call_mem(r, 0x4d4390, 2);
    if (r->eax == 0)
    {
        goto at_4d44c8;
    }
    push_mem(r, 0x0);
    push_mem(r, 0x0);
    push_mem(r, 0x36c);
    push_mem(r, r->ebx);
    call_mem(r, rd32(r, 0x4f1a94), 4);
    if (r->eax != 0)
    {
        goto at_4d44c8;
    }
    push_mem(r, r->eax);
    push_mem(r, r->ebx);
    r->edi = r->edi + 0x4;
    call_mem(r, rd32(r, 0x4f1948), 2);
    r->eax = rd32(r, r->ebp + 0xa4);
    wr32(r, r->edi + r->eax - 0x4, r->ebx);
at_4d44c8:
    push_mem(r, 0x2);
    push_mem(r, r->ebx);
    call_mem(r, rd32(r, 0x4f1a04), 2);
    r->ebx = r->eax;
    if (r->eax != 0 && !r->port->env.failed)
    {
        goto at_4d447a;
    }
at_4d44d8:
    r->eax = rd32(r, r->ebp + 0xa4);
    wr32(r, r->edi + r->eax, 0x0);
at_4d44e5:
    r->ebp = pop_mem(r);
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    r->edx = pop_mem(r);
    r->ecx = pop_mem(r);
    r->ebx = pop_mem(r);
    return;
    wr8(r, r->eax, rd8(r, r->eax) + (r->eax & 0xff));
    wr8(r, r->eax, rd8(r, r->eax) + (r->eax & 0xff));
    push_mem(r, r->ebx);
    push_mem(r, r->ecx);
    push_mem(r, r->edx);
    push_mem(r, r->esi);
    r->ebx = r->eax;
    if (rd32(r, r->eax + 0xa0) == 0x0)
    {
        goto at_4d455c;
    }
    wr32(r, r->eax + 0xa0, rd32(r, r->eax + 0xa0) - 1);
    if (rd32(r, r->eax + 0xa0) > 0x0)
    {
        goto at_4d455c;
    }
    if (rd32(r, r->eax + 0xa4) == 0x0)
    {
        goto at_4d455c;
    }
    r->esi = 0;
at_4d4519:
    r->edx = rd32(r, r->ebx + 0xa4);
    r->eax = r->edx + r->esi;
    if (rd32(r, r->eax) == 0x0)
    {
        goto at_4d454b;
    }
    push_mem(r, rd32(r, r->eax));
    call_mem(r, rd32(r, 0x4f1a2c), 1);
    if (r->eax == 0)
    {
        goto at_4d4546;
    }
    push_mem(r, 0x1);
    r->eax = rd32(r, r->ebx + 0xa4);
    push_mem(r, rd32(r, r->esi + r->eax));
    call_mem(r, rd32(r, 0x4f1948), 2);
at_4d4546:
    r->esi = r->esi + 0x4;
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4d4519;
at_4d454b:
    r->eax = r->edx;
    call_mem_keep(r, 0x4ca040, 8);
    wr32(r, r->ebx + 0xa4, 0x0);
at_4d455c:
    r->esi = pop_mem(r);
    r->edx = pop_mem(r);
    r->ecx = pop_mem(r);
    r->ebx = pop_mem(r);
    return;
    wr8(r, r->eax, rd8(r, r->eax) + (r->eax & 0xff));
    wr8(r, r->eax, rd8(r, r->eax) + (r->eax & 0xff));
    wr8(r, r->eax, rd8(r, r->eax) + (r->eax & 0xff));
    wr8(r, r->eax, rd8(r, r->eax) + (r->eax & 0xff));
    wr8(r, r->eax, rd8(r, r->eax) + (r->eax & 0xff));
    wr8(r, r->eax, rd8(r, r->eax) + (r->eax & 0xff));
    wr8(r, r->eax, rd8(r, r->eax) + (r->eax & 0xff));
    wr8(r, r->ebx + 0x51, rd8(r, r->ebx + 0x51) + (r->edx & 0xff));
    push_mem(r, r->esi);
    push_mem(r, r->edi);
    push_mem(r, r->ebp);
    r->esp = r->esp - 0x4;
    r->ebp = r->eax;
    wr32(r, r->esp, r->edx);
    push_mem(r, 0x5);
    call_mem(r, rd32(r, 0x4f1978), 4);
    push_mem(r, r->eax);
    call_mem(r, rd32(r, 0x4f1a04), 1);
    r->ebx = r->eax;
    if (r->eax == 0)
    {
        goto at_4d4620;
    }
at_4d4598:
    push_mem(r, r->ebx);
    call_mem(r, 0x4cf910, 1);
    r->esi = r->eax;
    r->edi = r->eax;
    if (r->eax == 0)
    {
        goto at_4d460c;
    }
    if (r->ebx == rd32(r, r->ebp + 0x1c))
    {
        goto at_4d460c;
    }
    push_mem(r, r->ebx);
    push_mem(r, rd32(r, r->ebp + 0x1c));
    call_mem(r, 0x4d4390, 2);
    if (r->eax == 0)
    {
        goto at_4d460c;
    }
    push_mem(r, 0xfffffff0u);
    push_mem(r, r->ebx);
    call_mem(r, rd32(r, 0x4f19f0), 2);
    r->edx = r->eax;
    if (rd32(r, r->esp) != 0x0)
    {
        goto at_4d45ea;
    }
    r->eax = r->eax & 0x18000000;
    if (r->eax != 0x10000000)
    {
        goto at_4d45ea;
    }
    push_mem(r, 0x0);
    push_mem(r, r->ebx);
    call_mem(r, rd32(r, 0x4f1af0), 2);
    wr8(r, r->esi + 0x24, rd8(r, r->esi + 0x24) | 0x2);
    goto at_4d460c;
at_4d45ea:
    if (rd32(r, r->esp) == 0x0)
    {
        goto at_4d460c;
    }
    if ((r->edx & 0x18000000) != 0)
    {
        goto at_4d460c;
    }
    if ((uint8_t)(rd8(r, r->edi + 0x24) & 0x2) == 0)
    {
        goto at_4d460c;
    }
    push_mem(r, 0x4);
    push_mem(r, r->ebx);
    call_mem(r, rd32(r, 0x4f1af0), 2);
    wr8(r, r->edi + 0x24, rd8(r, r->edi + 0x24) & 0xfd);
at_4d460c:
    push_mem(r, 0x2);
    push_mem(r, r->ebx);
    call_mem(r, rd32(r, 0x4f1a04), 2);
    r->ebx = r->eax;
    if (r->eax != 0 && !r->port->env.failed)
    {
        goto at_4d4598;
    }
at_4d4620:
    r->esp = r->esp + 0x4;
    r->ebp = pop_mem(r);
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    r->ecx = pop_mem(r);
    r->ebx = pop_mem(r);
    return;
}

uint32_t vertrix_port_rtl_ancestor_search_4d4390(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0xd0
    };
    Port port;
    uint8_t stack[BELOW + 8 + 4 * 40];
    Regs r;
    port_open_arguments(&port, stack, calls, services, globals, entry, BELOW, 40);
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
