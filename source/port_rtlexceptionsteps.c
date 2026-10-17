#include "port_rtlexceptionsteps.h"

/* Steps the exception record chain (see exception_chain.c). */

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

/* Original 0x4da6b6: Steps the exception record chain (see exception_chain.c). Evidence: calls
 * 0x4e0f8b, 0x4e0a95, 0x4e0eaf, 0x4e0ec7, 0x4e0b7c, 0x4e0b9e. Register-for-register from the
 * listing (0x4da6b6..0x4da71a); labels are the original addresses. */
static void run(Regs *r)
{
    push_mem(r, r->ebx);
    push_mem(r, r->ecx);
    push_mem(r, r->edx);
    r->esp = r->esp - 0x1c;
    call_mem_keep(r, 0x4e0f8b, 8);
    wr32(r, r->esp + 0x10, r->eax);
    r->eax = r->port->env.chain;
    wr32(r, r->esp + 0x14, r->eax);
    r->ecx = r->eax;
    r->eax = rd32(r, r->eax + 0x8);
    wr32(r, r->esp + 0x18, r->eax);
    r->edx = rd32(r, r->ecx + 0xc);
    r->eax = rd32(r, r->ecx + 0x8);
    call_mem_keep(r, 0x4e0a95, 8);
    r->edx = r->ecx;
    r->ebx = rd32(r, r->eax + 0x4);
    r->eax = r->esp + 0x10;
    r->ebx = r->ebx - 1;
    call_mem_keep(r, 0x4e0eaf, 8);
    r->edx = r->esp + 0x10;
    call_mem_keep(r, 0x4e0ec7, 8);
    r->edx = r->esp + 0x10;
    r->eax = r->esp;
    call_mem_keep(r, 0x4e0b7c, 8);
    r->eax = r->esp;
    call_mem_keep(r, 0x4e0b9e, 8);
    r->eax = rd32(r, r->esp + 0x4);
    wr32(r, r->ecx + 0xc, r->eax);
    r->esp = r->esp + 0x1c;
    r->edx = pop_mem(r);
    r->ecx = pop_mem(r);
    r->ebx = pop_mem(r);
    return;
}

uint32_t vertrix_port_exception_chain_step_4da6b6(PORT_SIGNATURE)
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
