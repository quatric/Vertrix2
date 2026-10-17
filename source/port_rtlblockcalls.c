#include "port_rtlblockcalls.h"

/* A runtime block call used by object construction, teardown and the global initialiser: it reaches
 * 0x4ce740, 0x4dc030, the guarded call pair, the handle close and the table register 0x4dde50. */

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

/* Original 0x4ccb9f: A runtime block call used by object construction, teardown and the global
 * initialiser: it reaches 0x4ce740, 0x4dc030, the guarded call pair, the handle close and the table
 * register 0x4dde50. Evidence: calls 0x4cea15, 0x4ce740, 0x4ce220, 0x4d9510, 0x4dc030, 0x4dc400,
 * 0x4dde50; reads 0x4f1ba0, 0x4f1ae0, 0x4f17d8. Register-for-register from the listing
 * (0x4ccb9f..0x4ccc39); labels are the original addresses. */
static void run(Regs *r)
{
    push_mem(r, r->ecx);
    if (r->eax != 0)
    {
        goto at_4ccbaa;
    }
    r->ecx = 0;
    r->eax = r->ecx;
    r->ecx = pop_mem(r);
    return;
at_4ccbaa:
    push_mem(r, r->esi);
    push_mem(r, r->ebx);
    r->ecx = r->eax - 0x4;
    r->esi = rd32(r, r->ecx);
    r->ebx = r->edx;
    r->edx = r->esi;
    call_mem_keep(r, 0x4cea15, 8);
    r->ebx = pop_mem(r);
    r->esi = pop_mem(r);
    r->eax = r->ecx;
    r->ecx = pop_mem(r);
    return;
    push_mem(r, r->ecx);
    push_mem(r, r->esi);
    push_mem(r, r->edi);
    r->edi = r->edx;
    r->esi = r->ebx;
    call_mem_keep(r, 0x4ce740, 8);
    if ((uint8_t)rd8(r, r->eax + 0x14) != (uint8_t)0x0)
    {
        goto at_4ccc03;
    }
    call_mem_keep(r, 0x4ce220, 8);
    r->ebx = r->eax;
    if (rd32(r, r->eax + 0x30) != 0x0)
    {
        goto at_4ccc03;
    }
    call_mem(r, rd32(r, 0x4f1ba0), 0);
    push_mem(r, r->eax);
    push_mem(r, 0x0);
    push_mem(r, 0x4cfe40);
    push_mem(r, 0x5);
    call_mem(r, rd32(r, 0x4f1ae0), 4);
    wr32(r, r->ebx + 0x30, r->eax);
    if (r->eax != 0)
    {
        goto at_4ccc03;
    }
    call_mem_keep(r, 0x4d9510, 8);
at_4ccc03:
    r->edx = 0x4ccc40;
    r->eax = 0x5c5c28;
    call_mem_keep(r, 0x4dc030, 8);
    r->ebx = r->eax;
    r->eax = r->eax + 0x4;
    push_mem(r, r->eax);
    call_mem(r, 0x4dc400, 1);
    push_mem(r, r->edi);
    call_mem(r, rd32(r, 0x4f17d8), 1);
    wr32(r, r->ebx + 0x4, r->eax);
    wr32(r, r->ebx + 0x8, r->esi);
    if (rd32(r, r->ebx + 0x4) != 0x0)
    {
        goto at_4ccc36;
    }
    call_mem_keep(r, 0x4dde50, 8);
at_4ccc36:
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    r->ecx = pop_mem(r);
    return;
}

uint32_t vertrix_port_rtl_block_call_4ccb9f(PORT_SIGNATURE)
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
