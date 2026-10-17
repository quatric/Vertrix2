#include "port_rtlpathseparators.h"

/* Finds the last path separator in a name. */

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

/* Original 0x4885a0: Finds the last path separator in a name. Evidence: reads 0x4f1c3c.
 * Register-for-register from the listing (0x4885a0..0x488618); labels are the original addresses.
 */
static void run(Regs *r)
{
    push_mem(r, r->ecx);
    r->ecx = r->eax;
    r->eax = r->edx;
    if (r->edx <= r->ecx)
    {
        goto at_4885b3;
    }
at_4885a9:
    if ((uint8_t)rd8(r, r->eax) == (uint8_t)0x5c)
    {
        goto at_4885b3;
    }
    r->eax = r->eax - 1;
    if (r->eax > r->ecx && !r->port->env.failed)
    {
        goto at_4885a9;
    }
at_4885b3:
    r->ecx = pop_mem(r);
    return;
    push_mem(r, r->ebx);
    push_mem(r, r->ecx);
    push_mem(r, r->esi);
    r->ebx = r->eax;
    r->esi = r->edx;
    set_high8(&r->eax, rd8(r, r->eax));
    if ((uint8_t)(((r->eax >> 8) & 0xff)) != 0)
    {
        goto at_4885d3;
    }
    wr8(r, r->ebx, 0x5c);
    wr8(r, r->ebx + 0x1, ((r->eax >> 8) & 0xff));
at_4885d3:
    r->eax = 0;
    set_low8(&r->eax, rd8(r, r->ebx));
    push_mem(r, r->eax);
    call_mem(r, rd32(r, 0x4f1c3c), 1);
    if (r->eax == 0)
    {
        goto at_4885f9;
    }
at_4885e3:
    if (r->esi == 0)
    {
        goto at_4885f5;
    }
    set_low8(&r->ecx, rd8(r, r->ebx));
    if ((uint8_t)((r->ecx & 0xff)) != (uint8_t)0x5c)
    {
        goto at_4885f5;
    }
    set_high8(&r->ecx, rd8(r, r->ebx + 0x1));
    if ((uint8_t)(((r->ecx >> 8) & 0xff)) == 0)
    {
        goto at_48860f;
    }
at_4885f5:
    r->esi = pop_mem(r);
    r->ecx = pop_mem(r);
    r->ebx = pop_mem(r);
    return;
at_4885f9:
    if ((uint8_t)rd8(r, r->ebx + 0x1) != (uint8_t)0x3a && !r->port->env.failed)
    {
        goto at_4885e3;
    }
    set_high8(&r->edx, rd8(r, r->ebx + 0x2));
    if ((uint8_t)(((r->edx >> 8) & 0xff)) != 0 && !r->port->env.failed)
    {
        goto at_4885e3;
    }
    wr8(r, r->ebx + 0x2, 0x5c);
    wr8(r, r->ebx + 0x3, ((r->edx >> 8) & 0xff));
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4885e3;
at_48860f:
    wr8(r, r->ebx + 0x1, (r->ecx & 0xff));
    wr8(r, r->ebx + 0x2, ((r->ecx >> 8) & 0xff));
    r->esi = pop_mem(r);
    r->ecx = pop_mem(r);
    r->ebx = pop_mem(r);
    return;
}

uint32_t vertrix_port_path_last_separator_4885a0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x20
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
