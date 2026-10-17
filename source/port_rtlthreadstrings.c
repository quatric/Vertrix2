#include "port_rtlthreadstrings.h"

/* Calls 0x4cf880 with eax 0 and raises through 0x4dee00 when it returns nonzero. */

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

static void call_mem_keep(Regs *r, uint32_t target, unsigned count)
{
    call_mem_with(r, target, count, 1);
}

/* Original 0x4cf8d0: Calls 0x4cf880 with eax 0 and raises through 0x4dee00 when it returns nonzero.
 * Evidence: calls 0x4cf880. Register-for-register from the listing (0x4cf8d0..0x4cf8df); labels are
 * the original addresses. */
static void run(Regs *r)
{
    r->eax = 0;
    call_mem_keep(r, 0x4cf880, 8);
    if (r->eax != 0)
    {
        goto at_4dee00;
    }
    return;
at_4dee00:
    push_mem(r, r->ebx);
    push_mem(r, r->ecx);
    push_mem(r, r->edx);
    push_mem(r, r->esi);
    push_mem(r, r->edi);
    r->esp = r->esp - 0xc;
    r->esi = r->eax;
    r->edi = r->eax + 0x1c;
    flags(r, F_SUB, rd32(r, r->edi + 0xc), 0x0, 32);
    set_low8(&r->eax, cond(r, CC_E));
    r->eax = (r->eax & 0xff);
    r->eax = r->eax - 1;
    flags(r, F_DEC, r->eax, 0, 32);
    wr32(r, r->esp, r->eax);
    if (cond(r, CC_E))
    {
        goto at_4dee63;
    }
at_4dee1d:
    r->ecx = r->esp + 0x8;
    r->ebx = r->esp + 0x4;
    r->edx = r->esp;
    r->eax = r->edi;
    call_mem_keep(r, 0x4df220, 8);
    r->eax = rd32(r, r->esp + 0x8);
    r->eax = r->eax + rd32(r, r->esi + 0x3c);
    wr32(r, r->eax, 0x0);
    if (rd32(r, r->esi + 0x40) != 0x2)
    {
        goto at_4dee48;
    }
    wr32(r, r->eax + 0x4, 0x0);
at_4dee48:
    if (rd32(r, r->esp + 0x8) == 0x0)
    {
        goto at_4dee5d;
    }
    r->eax = rd32(r, r->esp + 0x8);
    r->ebx = rd32(r, r->eax);
    r->edx = 0x2;
    call_mem(r, rd32(r, r->ebx + 0x4), 0);
at_4dee5d:
    if (rd32(r, r->esp) != 0x0 && !r->port->env.failed)
    {
        goto at_4dee1d;
    }
at_4dee63:
    r->eax = r->edi;
    call_mem_keep(r, 0x4def90, 8);
    r->esp = r->esp + 0xc;
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    r->edx = pop_mem(r);
    r->ecx = pop_mem(r);
    r->ebx = pop_mem(r);
    return;
}

uint32_t vertrix_port_rtl_thread_string_finish_4cf8d0(PORT_SIGNATURE)
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
