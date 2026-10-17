#include "port_rtlhandlerthunks.h"

/* The exception handler address the guarded routines store in their frames: a jump to 0x4e6e19. */

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

/* Original 0x4ec1ec: The exception handler address the guarded routines store in their frames: a
 * jump to 0x4e6e19. Evidence: no calls. Register-for-register from the listing
 * (0x4ec1ec..0x4ec1f6); labels are the original addresses. */
static void run(Regs *r)
{
    goto at_4e6e19;
    push_mem(r, r->edi);
    r->ecx = r->ecx + 1;
    push_mem(r, r->esp);
    r->ebx = r->ebx + 1;
    r->edi = r->edi - 1;
    r->ebp = r->ebp - 1;
at_4e6e19:
    push_mem(r, r->ebx);
    r->edx = rd32(r, r->esp + 0x8);
    r->ebx = rd32(r, r->esp + 0xc);
    if (r->ebx == 0)
    {
        goto at_4e6e4a;
    }
    if ((uint8_t)(rd8(r, r->edx + 0x4) & 0x2) != 0)
    {
        goto at_4e6e3a;
    }
    if ((uint8_t)(rd8(r, r->edx + 0x4) & 0x4) == 0)
    {
        goto at_4e6e64;
    }
    r->eax = rd32(r, r->ebx + 0x8);
    if (rd32(r, r->eax) != 0x4)
    {
        goto at_4e6e43;
    }
at_4e6e3a:
    r->edx = r->ebx;
    r->eax = 0;
    call_mem_keep(r, 0x4cd9f0, 8);
at_4e6e43:
    r->eax = 0x1;
    r->ebx = pop_mem(r);
    return;
at_4e6e4a:
    call_mem(r, rd32(r, 0x507c9c), 0);
    r->ecx = rd32(r, 0x5c5c54);
    r->ecx = r->ecx + r->eax;
    r->eax = rd32(r, r->edx + 0x18);
    r->eax = rd32(r, r->eax + 0x8);
    wr32(r, r->eax, r->ecx);
    r->eax = 0;
    r->ebx = pop_mem(r);
    return;
at_4e6e64:
    r->eax = rd32(r, r->edx);
    r->eax = r->eax & 0x3fffffff;
    if (r->eax != 0x25671234 && !r->port->env.failed)
    {
        goto at_4e6e43;
    }
    r->ecx = rd32(r, r->edx + 0x18);
    if (r->ebx == rd32(r, r->ecx + 0x2c))
    {
        goto at_4e6e90;
    }
at_4e6e7a:
    r->eax = rd32(r, r->ecx + 0x34);
at_4e6e7d:
    if (r->eax == 0)
    {
        goto at_4e6ea9;
    }
    if (r->ebx != rd32(r, r->eax))
    {
        goto at_4e6ea9;
    }
    if (rd32(r, r->ecx + 0x2c) == 0x0)
    {
        goto at_4e6ea1;
    }
at_4e6e8b:
    r->eax = rd32(r, r->eax + 0x8);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4e6e7d;
at_4e6e90:
    wr32(r, r->ecx + 0x2c, 0x0);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4e6e7a;
at_4e6ea9:
    if (r->eax == 0)
    {
        goto at_4e6ec3;
    }
    if (r->ebx != rd32(r, r->eax))
    {
        goto at_4e6ec3;
    }
    set_high8(&r->eax, 0x4);
at_4e6eb3:
    wr8(r, r->ecx + 0x24, ((r->eax >> 8) & 0xff));
    r->eax = 0;
    r->ebx = pop_mem(r);
    return;
at_4e6ea1:
    set_low8(&r->edx, rd8(r, r->eax + 0xc));
    flags(r, F_SUB, (r->edx & 0xff), 0x2, 8);
    if (cond(r, CC_AE))
    {
        goto at_4e6eba;
    }
at_4e6ec3:
    if (rd32(r, r->ecx + 0x2c) == 0x0)
    {
        goto at_4e6eda;
    }
at_4e6ec9:
    if (r->ebx != rd32(r, r->ecx + 0x30) && !r->port->env.failed)
    {
        goto at_4e6e43;
    }
    wr8(r, r->ecx + 0x24, 0x3);
    r->eax = 0;
    r->ebx = pop_mem(r);
    return;
at_4e6eba:
    if (cond(r, CC_BE))
    {
        goto at_4e6e99;
    }
    if ((uint8_t)((r->edx & 0xff)) == (uint8_t)0x7)
    {
        goto at_4e6e99;
    }
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4e6ea9;
at_4e6eda:
    r->edx = r->ebx;
    r->eax = r->ecx;
    call_mem_keep(r, 0x4e8fa7, 8);
    set_high8(&r->eax, (r->eax & 0xff));
    if ((uint8_t)((r->eax & 0xff)) == 0 && !r->port->env.failed)
    {
        goto at_4e6ec9;
    }
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4e6eb3;
at_4e6e99:
    r->edx = rd32(r, r->eax + 0x14);
    wr32(r, r->ecx + 0x2c, r->edx);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4e6e8b;
}

uint32_t vertrix_port_rtl_exception_handler_thunk_4ec1ec(PORT_SIGNATURE)
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
