#include "port_rtlpendingerrors.h"

/* Checks the runtime's pending error state (0x50ba74, 0x5c8af4, 0x5c8af8) for the error reporter.
 */

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

static uint32_t rd16(Regs *r, uint32_t address)
{
    return port_u16(r->port, address, 0);
}

static uint32_t rd32(Regs *r, uint32_t address)
{
    return port_u32(r->port, address, 0);
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

static void set_low16(uint32_t *reg, uint32_t value)
{
    *reg = (*reg & 0xffff0000u) | (value & 0xffff);
}

static uint32_t flag_mask(const Regs *r)
{
    return r->fw == 8 ? 0xffu : r->fw == 16 ? 0xffffu : 0xffffffffu;
}

static uint32_t result(const Regs *r)
{
    uint32_t mask = flag_mask(r);
    if (r->fk == F_SUB)
    {
        return (r->fa - r->fb) & mask;
    }
    if (r->fk == F_ADD)
    {
        return (r->fa + r->fb) & mask;
    }
    return r->fa & mask;
}

static uint32_t carry(const Regs *r)
{
    uint32_t mask = flag_mask(r);
    if (r->fk == F_SUB)
    {
        return (r->fa & mask) < (r->fb & mask);
    }
    if (r->fk == F_ADD)
    {
        return result(r) < (r->fa & mask);
    }
    if (r->fk == F_INC || r->fk == F_DEC)
    {
        return r->fc;
    }
    return 0;
}

/* The flags of an instruction recorded (width 8, 16 or 32). */
static void flags(Regs *r, unsigned kind, uint32_t a, uint32_t b, unsigned width)
{
    if (kind == F_INC || kind == F_DEC)
    {
        r->fc = carry(r);
    }
    r->fk = kind;
    r->fa = a;
    r->fb = b;
    r->fw = width;
}

static uint32_t overflow(const Regs *r)
{
    uint32_t top = 1u << (r->fw - 1);
    uint32_t value = result(r);
    if (r->fk == F_SUB)
    {
        return (((r->fa ^ r->fb) & (r->fa ^ value)) & top) != 0;
    }
    if (r->fk == F_ADD)
    {
        return ((~(r->fa ^ r->fb) & (r->fa ^ value)) & top) != 0;
    }
    if (r->fk == F_INC)
    {
        return value == top;
    }
    if (r->fk == F_DEC)
    {
        return value == top - 1;
    }
    return 0;
}

/* A condition of the recorded flags. */
static uint32_t cond(const Regs *r, unsigned code)
{
    uint32_t zero = result(r) == 0;
    uint32_t sign = (result(r) >> (r->fw - 1)) & 1;
    uint32_t less = sign != overflow(r);
    switch (code)
    {
        case CC_E:
            return zero;
        case CC_NE:
            return !zero;
        case CC_B:
            return carry(r);
        case CC_AE:
            return !carry(r);
        case CC_BE:
            return carry(r) || zero;
        case CC_A:
            return !carry(r) && !zero;
        case CC_L:
            return less;
        case CC_GE:
            return !less;
        case CC_LE:
            return less || zero;
        case CC_G:
            return !less && !zero;
        case CC_S:
            return sign;
        default:
            return !sign;
    }
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

/* Original 0x4ed880: Checks the runtime's pending error state (0x50ba74, 0x5c8af4, 0x5c8af8) for
 * the error reporter. Evidence: calls 0x4e8950; reads 0x5c8af8, 0x5c8af4, 0x50ba74, 0x5c8af0,
 * 0x4f1c74; writes 0x50ba74, 0x5c8af8, 0x5c8af4, 0x5c8af0. Register-for-register from the listing
 * (0x4ed880..0x4ed983); labels are the original addresses. */
static void run(Regs *r)
{
    push_mem(r, r->ebx);
    push_mem(r, r->ecx);
    push_mem(r, r->edx);
    push_mem(r, r->esi);
    push_mem(r, r->edi);
    push_mem(r, r->ebp);
    r->esp = r->esp - 0x18;
    r->esi = rd32(r, 0x5c8af8);
    r->edi = rd32(r, 0x5c8af4);
    r->ebx = r->eax;
    r->eax = rd32(r, 0x50ba74);
    flags(r, F_SUB, r->eax, 0x1, 32);
    if (cond(r, CC_B))
    {
        goto at_4ed8e5;
    }
    if (cond(r, CC_BE))
    {
        goto at_4ed8aa;
    }
    if (r->eax == 0x2)
    {
        goto at_4ed8cc;
    }
    goto at_4ed8e5;
at_4ed8aa:
    r->esi = r->esi - 1;
    if (r->edi == 0)
    {
        goto at_4ed8bb;
    }
    if (r->esi != 0)
    {
        goto at_4ed8c5;
    }
    wr32(r, 0x50ba74, r->esi);
    goto at_4ed8c5;
at_4ed8bb:
    wr32(r, 0x50ba74, 0x2);
at_4ed8c5:
    r->eax = r->edi;
    goto at_4ed96e;
at_4ed8cc:
    flags(r, F_LOGIC, r->esi, 0, 32);
    set_low8(&r->eax, cond(r, CC_NE));
    r->eax = r->eax & 0xff;
    wr32(r, 0x50ba74, r->eax);
    r->eax = rd32(r, 0x5c8af0);
    goto at_4ed96e;
at_4ed8e5:
    wr32(r, 0x5c8af8, r->esi);
    wr32(r, 0x5c8af4, r->edi);
at_4ed8f1:
    r->eax = r->esp + 0x14;
    push_mem(r, r->eax);
    push_mem(r, 0x1);
    r->eax = r->esp + 0x8;
    push_mem(r, r->eax);
    push_mem(r, r->ebx);
    call_mem(r, rd32(r, 0x4f1c74), 4);
    if (r->eax == 0)
    {
        goto at_4ed95d;
    }
    r->eax = r->esp;
    call_mem_keep(r, 0x4e8950, 8);
    if (r->eax == 0 && !r->port->env.failed)
    {
        goto at_4ed8f1;
    }
    r->eax = 0;
    set_low16(&r->eax, rd16(r, r->esp + 0x8));
    r->esi = r->eax - 0x1;
    set_high8(&r->eax, rd8(r, r->esp + 0x11));
    r->edi = rd8(r, r->esp + 0xe);
    if ((uint8_t)(((r->eax >> 8) & 0xff) & 0x1) != 0)
    {
        goto at_4ed930;
    }
    if (r->edi != 0)
    {
        goto at_4ed94b;
    }
at_4ed930:
    r->ebp = 0x2;
    r->eax = 0;
    r->edi = 0;
    set_low16(&r->eax, rd16(r, r->esp + 0xc));
    wr32(r, 0x50ba74, r->ebp);
    wr32(r, 0x5c8af0, r->eax);
    goto at_4ed959;
at_4ed94b:
    if (r->esi == 0)
    {
        goto at_4ed959;
    }
    wr32(r, 0x50ba74, 0x1);
at_4ed959:
    r->eax = r->edi;
    goto at_4ed96e;
at_4ed95d:
    r->eax = 0xffffffffu;
    r->edi = rd32(r, 0x5c8af4);
    r->esi = rd32(r, 0x5c8af8);
at_4ed96e:
    wr32(r, 0x5c8af4, r->edi);
    wr32(r, 0x5c8af8, r->esi);
    r->esp = r->esp + 0x18;
    r->ebp = pop_mem(r);
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    r->edx = pop_mem(r);
    r->ecx = pop_mem(r);
    r->ebx = pop_mem(r);
    return;
}

uint32_t vertrix_port_rtl_pending_error_check_4ed880(PORT_SIGNATURE)
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
