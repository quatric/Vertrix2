#include "port_rtlrangerecords.h"

/* Stores eax and the stack arguments into the record at ebx for the range dispatcher (0x4cb820). */

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

static void set_low8(uint32_t *reg, uint32_t value)
{
    *reg = (*reg & 0xffffff00u) | (value & 0xff);
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

/* Original 0x4cb5a0: Stores eax and the stack arguments into the record at ebx for the range
 * dispatcher (0x4cb820). Evidence: no calls. Register-for-register from the listing
 * (0x4cb5a0..0x4cb819); labels are the original addresses. */
static void run(Regs *r)
{
    push_mem(r, r->ecx);
    push_mem(r, r->esi);
    push_mem(r, r->edi);
    push_mem(r, r->ebp);
    r->esp = r->esp - 0x14;
    r->ecx = rd32(r, r->esp + 0x34);
    r->ebx = rd32(r, r->esp + 0x3c);
    wr32(r, r->esp + 0x10, r->eax);
    r->edi = r->edx;
    r->edx = rd32(r, r->esp + 0x38);
    r->eax = rd32(r, r->esp + 0x28);
    wr32(r, r->esp, r->eax);
    r->eax = rd32(r, r->esp + 0x2c);
    wr32(r, r->esp + 0x4, r->eax);
    r->eax = rd32(r, r->esp + 0x30);
    r->ebp = 0x1;
    wr32(r, r->esp + 0x8, r->eax);
    if (r->ebx == 0)
    {
        goto at_4cb78d;
    }
    r->eax = rd32(r, r->esp + 0x10);
    wr32(r, r->ebx, r->eax);
    r->edx = r->ebx + 0x4;
    r->eax = rd32(r, r->esp);
    wr32(r, r->edx, r->eax);
    r->eax = rd32(r, r->esp + 0x4);
    wr32(r, r->edx + 0x4, r->eax);
    r->eax = rd32(r, r->esp + 0x8);
    wr32(r, r->edx + 0x8, r->eax);
    r->eax = r->ebp;
    r->esp = r->esp + 0x14;
    r->ebp = pop_mem(r);
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    r->ecx = pop_mem(r);
    return;
at_4cb605:
    r->edx = rd32(r, r->esp + 0x10);
    r->edx = r->edx + rd32(r, r->esp + 0x4);
    r->ecx = r->esp;
    r->eax = r->edx;
    call_mem(r, rd32(r, r->ecx), 0);
    r->ecx = r->eax;
    r->eax = r->edx;
    call_mem(r, r->ecx, 0);
    r->eax = r->ebp;
    r->esp = r->esp + 0x14;
    r->ebp = pop_mem(r);
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    r->ecx = pop_mem(r);
    return;
at_4cb625:
    r->edx = r->esp;
    r->eax = r->esi;
    call_mem(r, rd32(r, r->edx), 0);
    r->edx = r->eax;
    r->eax = r->esi;
    call_mem(r, r->edx, 0);
    r->ebp = r->eax;
    r->eax = r->ebp;
    r->esp = r->esp + 0x14;
    r->ebp = pop_mem(r);
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    r->ecx = pop_mem(r);
    return;
at_4cb63f:
    r->edx = r->esp;
    r->eax = r->esi;
    call_mem(r, rd32(r, r->edx), 0);
    r->ecx = r->eax;
    r->edx = r->edi;
    r->eax = r->esi;
    call_mem(r, r->ecx, 0);
    r->eax = r->ebp;
    r->esp = r->esp + 0x14;
    r->ebp = pop_mem(r);
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    r->ecx = pop_mem(r);
    return;
at_4cb659:
    r->ecx = rd32(r, r->esp + 0x10);
    r->ecx = r->ecx + rd32(r, r->esp + 0x4);
    r->edx = r->esp;
    r->eax = r->ecx;
    call_mem(r, rd32(r, r->edx), 0);
    r->esi = r->eax;
    r->edx = r->edi;
    r->eax = r->ecx;
    call_mem(r, r->esi, 0);
    r->ebp = r->eax;
    r->eax = r->ebp;
    r->esp = r->esp + 0x14;
    r->ebp = pop_mem(r);
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    r->ecx = pop_mem(r);
    return;
at_4cb67d:
    r->edx = r->esp;
    r->eax = r->esi;
    call_mem(r, rd32(r, r->edx), 0);
    r->edi = r->eax;
    r->ebx = rd32(r, r->ecx);
    r->edx = rd32(r, r->ecx + 0x4);
    r->eax = r->esi;
    call_mem(r, r->edi, 0);
    r->eax = r->ebp;
    r->esp = r->esp + 0x14;
    r->ebp = pop_mem(r);
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    r->ecx = pop_mem(r);
    return;
at_4cb69a:
    r->edx = r->esp;
    r->eax = r->esi;
    call_mem(r, rd32(r, r->edx), 0);
    r->edi = r->eax;
    r->ebx = rd32(r, r->ecx);
    r->edx = rd32(r, r->ecx + 0x4);
    r->eax = r->esi;
    call_mem(r, r->edi, 0);
    r->ebp = r->eax;
    r->eax = r->ebp;
    r->esp = r->esp + 0x14;
    r->ebp = pop_mem(r);
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    r->ecx = pop_mem(r);
    return;
at_4cb6b9:
    r->edx = r->esp;
    r->eax = r->esi;
    call_mem(r, rd32(r, r->edx), 0);
    wr32(r, r->esp + 0xc, r->eax);
    r->edx = r->edi;
    r->eax = rd32(r, r->ecx);
    r->ebx = rd32(r, r->ecx + 0x4);
    r->ecx = r->eax;
    r->eax = r->esi;
    call_mem(r, rd32(r, r->esp + 0xc), 0);
    r->eax = r->ebp;
    r->esp = r->esp + 0x14;
    r->ebp = pop_mem(r);
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    r->ecx = pop_mem(r);
    return;
at_4cb6de:
    r->edx = r->esp;
    r->eax = r->esi;
    call_mem(r, rd32(r, r->edx), 0);
    r->ebp = r->eax;
    r->edx = r->edi;
    r->eax = rd32(r, r->ecx);
    r->ebx = rd32(r, r->ecx + 0x4);
    r->ecx = r->eax;
    r->eax = r->esi;
    call_mem(r, r->ebp, 0);
    r->ebp = r->eax;
    r->eax = r->ebp;
    r->esp = r->esp + 0x14;
    r->ebp = pop_mem(r);
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    r->ecx = pop_mem(r);
    return;
at_4cb701:
    r->edx = r->esp;
    r->eax = r->esi;
    call_mem(r, rd32(r, r->edx), 0);
    r->edi = r->eax;
    r->edx = r->ecx;
    r->eax = r->esi;
    call_mem(r, r->edi, 0);
    flags(r, F_SUB, rd32(r, r->ecx + 0x18), 0x0, 32);
    set_low8(&r->eax, cond(r, CC_E));
    r->eax = (r->eax & 0xff);
    wr32(r, r->ecx + 0x18, r->ebx);
    r->ebp = r->eax;
    r->eax = r->ebp;
    r->esp = r->esp + 0x14;
    r->ebp = pop_mem(r);
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    r->ecx = pop_mem(r);
    return;
at_4cb72a:
    r->edx = r->esp;
    r->eax = r->esi;
    r->ebx = r->edi;
    call_mem(r, rd32(r, r->edx), 0);
    r->ebp = r->eax;
    r->edx = r->ecx;
    r->eax = r->esi;
    call_mem(r, r->ebp, 0);
    flags(r, F_SUB, rd32(r, r->ecx + 0x18), 0x0, 32);
    set_low8(&r->eax, cond(r, CC_E));
    r->ebp = (r->eax & 0xff);
    wr32(r, r->ecx + 0x18, 0x0);
    r->eax = r->ebp;
    r->esp = r->esp + 0x14;
    r->ebp = pop_mem(r);
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    r->ecx = pop_mem(r);
    return;
at_4cb757:
    r->edx = r->esp;
    r->eax = r->esi;
    call_mem(r, rd32(r, r->edx), 0);
    r->ebx = r->eax;
    r->edx = r->ecx;
    r->eax = r->esi;
    call_mem(r, r->ebx, 0);
    r->eax = r->ebp;
    r->esp = r->esp + 0x14;
    r->ebp = pop_mem(r);
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    r->ecx = pop_mem(r);
    return;
at_4cb771:
    r->edx = r->esp;
    r->eax = r->esi;
    call_mem(r, rd32(r, r->edx), 0);
    r->ebx = r->eax;
    r->edx = r->ecx;
    r->eax = r->esi;
    call_mem(r, r->ebx, 0);
    r->ebp = r->eax;
    r->eax = r->ebp;
    r->esp = r->esp + 0x14;
    r->ebp = pop_mem(r);
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    r->ecx = pop_mem(r);
    return;
at_4cb78d:
    r->esi = rd32(r, r->esp + 0x10);
    r->esi = r->esi + rd32(r, r->esp + 0x4);
    flags(r, F_SUB, r->edx, 0x27, 32);
    if (cond(r, CC_B))
    {
        goto at_4cb7d1;
    }
    if (cond(r, CC_BE) && !r->port->env.failed)
    {
        goto at_4cb69a;
    }
    flags(r, F_SUB, r->edx, 0x2c, 32);
    if (cond(r, CC_B))
    {
        goto at_4cb7bd;
    }
    if (cond(r, CC_BE) && !r->port->env.failed)
    {
        goto at_4cb701;
    }
    flags(r, F_SUB, r->edx, 0x2e, 32);
    if (cond(r, CC_B) && !r->port->env.failed)
    {
        goto at_4cb72a;
    }
    if (cond(r, CC_BE) && !r->port->env.failed)
    {
        goto at_4cb757;
    }
    if (r->edx == 0x2f && !r->port->env.failed)
    {
        goto at_4cb771;
    }
    goto at_4cb810;
at_4cb7bd:
    if (r->edx <= 0x28 && !r->port->env.failed)
    {
        goto at_4cb6b9;
    }
    if (r->edx == 0x29 && !r->port->env.failed)
    {
        goto at_4cb6de;
    }
    goto at_4cb810;
at_4cb7d1:
    flags(r, F_SUB, r->edx, 0xd, 32);
    if (cond(r, CC_B))
    {
        goto at_4cb7fc;
    }
    if (cond(r, CC_BE) && !r->port->env.failed)
    {
        goto at_4cb63f;
    }
    flags(r, F_SUB, r->edx, 0x23, 32);
    if (cond(r, CC_B))
    {
        goto at_4cb810;
    }
    if (cond(r, CC_BE) && !r->port->env.failed)
    {
        goto at_4cb625;
    }
    if (r->edx == 0x26 && !r->port->env.failed)
    {
        goto at_4cb67d;
    }
    r->eax = 0;
    r->esp = r->esp + 0x14;
    r->ebp = pop_mem(r);
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    r->ecx = pop_mem(r);
    return;
at_4cb7fc:
    flags(r, F_SUB, r->edx, 0x2, 32);
    if (cond(r, CC_B))
    {
        goto at_4cb810;
    }
    if (cond(r, CC_BE) && !r->port->env.failed)
    {
        goto at_4cb659;
    }
    if (r->edx == 0xc && !r->port->env.failed)
    {
        goto at_4cb605;
    }
at_4cb810:
    r->eax = 0;
    r->esp = r->esp + 0x14;
    r->ebp = pop_mem(r);
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    r->ecx = pop_mem(r);
    return;
}

uint32_t vertrix_port_rtl_range_record_store_4cb5a0(PORT_SIGNATURE)
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
