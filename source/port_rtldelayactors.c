#include "port_rtldelayactors.h"

/* Creates a 0x15c-byte timing actor: update 0x457770, time scale 0x1388 + 180 * table
 * 0x53bdac[[0x532a64]], first field 0xc8, then links it through 0x4b5e70 on list 0x54671c. */

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

/* Original 0x471340: Creates a 0x15c-byte timing actor: update 0x457770, time scale 0x1388 + 180 *
 * table 0x53bdac[[0x532a64]], first field 0xc8, then links it through 0x4b5e70 on list 0x54671c.
 * Evidence: calls 0x4ca000, 0x4adf20, 0x4ac8f0, 0x4ac7d0, 0x4b5e70; reads 0x532a64.
 * Register-for-register from the listing (0x471340..0x4713bc); labels are the original addresses.
 */
static void run(Regs *r)
{
    push_mem(r, r->ebx);
    push_mem(r, r->ecx);
    push_mem(r, r->edx);
    push_mem(r, r->esi);
    push_mem(r, r->edi);
    r->eax = rd32(r, 0x532a64);
    r->esi = rd32(r, r->eax * 4 + 0x53bdac);
    r->eax = r->esi * 4;
    r->eax = r->eax - r->esi;
    r->eax = r->eax << 0x2;
    r->esi = r->eax;
    r->eax = r->eax << 0x4;
    r->eax = r->eax - r->esi;
    r->edi = r->eax + 0x1388;
    r->eax = 0x15c;
    call_mem_keep(r, 0x4ca000, 8);
    if (r->eax != 0)
    {
        goto at_4713c1;
    }
at_471378:
    r->esi = r->eax;
    push_mem(r, 0x0);
    push_mem(r, 0x0);
    push_mem(r, 0x0);
    push_mem(r, 0x0);
    r->eax = r->esi;
    r->ecx = 0;
    push_mem(r, 0x0);
    r->ebx = 0;
    r->edx = 0;
    call_mem(r, 0x4adf20, 5);
    r->edx = 0x457770;
    r->eax = r->esi;
    call_mem_keep(r, 0x4ac8f0, 8);
    r->edx = r->edi;
    r->eax = r->esi;
    call_mem_keep(r, 0x4ac7d0, 8);
    r->eax = 0x54671c;
    r->edx = r->esi;
    wr32(r, r->esi, 0xc8);
    call_mem_keep(r, 0x4b5e70, 8);
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    r->edx = pop_mem(r);
    r->ecx = pop_mem(r);
    r->ebx = pop_mem(r);
    return;
at_4713c1:
    call_mem_keep(r, 0x4abd70, 8);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_471378;
}

uint32_t vertrix_port_delay_actor_spawn_471340(PORT_SIGNATURE)
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
