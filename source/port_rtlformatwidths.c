#include "port_rtlformatwidths.h"

/* Reads a format's width or precision, including the * form. */

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

/* Original 0x4e43c4: Reads a format's width or precision, including the * form. Evidence: no calls.
 * Register-for-register from the listing (0x4e43c4..0x4e44c7); labels are the original addresses.
 */
static void run(Regs *r)
{
    push_mem(r, r->ebx);
    push_mem(r, r->ecx);
    push_mem(r, r->esi);
    push_mem(r, r->edi);
    r->edi = r->edx;
    set_low8(&r->edx, rd8(r, r->edx + 0x10));
    set_low8(&r->edx, (r->edx & 0xff) | 0x1);
    wr8(r, r->edi + 0x10, (r->edx & 0xff));
    set_high8(&r->edx, (r->edx & 0xff));
    wr32(r, r->edi + 0xc, 0xffffffffu);
    set_high8(&r->edx, ((r->edx >> 8) & 0xff) & 0x3);
    wr8(r, r->edi + 0x10, ((r->edx >> 8) & 0xff));
    if ((uint8_t)rd8(r, r->eax) != (uint8_t)0x2a)
    {
        goto at_4e43f1;
    }
    set_high8(&r->ebx, rd8(r, r->edi + 0x10));
    set_high8(&r->ebx, ((r->ebx >> 8) & 0xff) & 0xfe);
    r->eax = r->eax + 1;
    wr8(r, r->edi + 0x10, ((r->ebx >> 8) & 0xff));
at_4e43f1:
    r->ebx = 0;
    set_low8(&r->ebx, rd8(r, r->eax));
    set_low8(&r->edx, (r->ebx & 0xff));
    set_low8(&r->edx, (r->edx & 0xff) + 1);
    r->edx = r->edx & 0xff;
    if ((uint8_t)(rd8(r, r->edx + 0x507d58) & 0x20) == 0)
    {
        goto at_4e442d;
    }
    r->edx = 0;
at_4e440a:
    r->edx = r->edx * 0xa;
    r->ebx = r->ebx - 0x30;
    r->edx = r->edx + r->ebx;
    r->ebx = 0;
    set_low8(&r->ebx, rd8(r, r->eax + 0x1));
    set_low8(&r->ecx, (r->ebx & 0xff));
    set_low8(&r->ecx, (r->ecx & 0xff) + 1);
    r->esi = (r->ecx & 0xff);
    set_high8(&r->ecx, rd8(r, r->esi + 0x507d58));
    r->eax = r->eax + 1;
    if ((uint8_t)(((r->ecx >> 8) & 0xff) & 0x20) != 0 && !r->port->env.failed)
    {
        goto at_4e440a;
    }
    wr32(r, r->edi + 0xc, r->edx);
at_4e442d:
    set_low8(&r->ebx, rd8(r, r->eax));
    r->edx = r->eax + 0x1;
    if ((uint8_t)((r->ebx & 0xff)) != (uint8_t)0x4e)
    {
        goto at_4e4444;
    }
    set_high8(&r->ecx, rd8(r, r->edi + 0x10));
    set_high8(&r->ecx, ((r->ecx >> 8) & 0xff) | 0x8);
    r->eax = r->edx;
    wr8(r, r->edi + 0x10, ((r->ecx >> 8) & 0xff));
    goto at_4e4454;
at_4e4444:
    if ((uint8_t)((r->ebx & 0xff)) != (uint8_t)0x46)
    {
        goto at_4e4454;
    }
    set_low8(&r->ecx, rd8(r, r->edi + 0x10));
    set_low8(&r->ecx, (r->ecx & 0xff) | 0x4);
    r->eax = r->edx;
    wr8(r, r->edi + 0x10, (r->ecx & 0xff));
at_4e4454:
    set_low8(&r->edx, rd8(r, r->eax));
    r->ebx = r->eax + 0x1;
    flags(r, F_SUB, (r->edx & 0xff), 0x68, 8);
    if (cond(r, CC_B))
    {
        goto at_4e4471;
    }
    if (cond(r, CC_BE))
    {
        goto at_4e4482;
    }
    flags(r, F_SUB, (r->edx & 0xff), 0x6c, 8);
    if (cond(r, CC_B))
    {
        goto at_4e44c3;
    }
    if (cond(r, CC_BE))
    {
        goto at_4e448c;
    }
    if ((uint8_t)((r->edx & 0xff)) == (uint8_t)0x77)
    {
        goto at_4e448c;
    }
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    r->ecx = pop_mem(r);
    r->ebx = pop_mem(r);
    return;
at_4e4471:
    flags(r, F_SUB, (r->edx & 0xff), 0x49, 8);
    if (cond(r, CC_B))
    {
        goto at_4e44c3;
    }
    if (cond(r, CC_BE))
    {
        goto at_4e44ab;
    }
    if ((uint8_t)((r->edx & 0xff)) == (uint8_t)0x4c)
    {
        goto at_4e449b;
    }
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    r->ecx = pop_mem(r);
    r->ebx = pop_mem(r);
    return;
at_4e4482:
    set_high8(&r->edx, rd8(r, r->edi + 0x10));
    set_high8(&r->edx, ((r->edx >> 8) & 0xff) | 0x10);
    r->eax = r->ebx;
    goto at_4e44c0;
at_4e448c:
    set_low8(&r->edx, rd8(r, r->edi + 0x10));
    set_low8(&r->edx, (r->edx & 0xff) | 0x20);
    r->eax = r->eax + 1;
    wr8(r, r->edi + 0x10, (r->edx & 0xff));
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    r->ecx = pop_mem(r);
    r->ebx = pop_mem(r);
    return;
at_4e449b:
    set_low8(&r->ecx, rd8(r, r->edi + 0x10));
    set_low8(&r->ecx, (r->ecx & 0xff) | 0x40);
    r->eax = r->ebx;
    wr8(r, r->edi + 0x10, (r->ecx & 0xff));
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    r->ecx = pop_mem(r);
    r->ebx = pop_mem(r);
    return;
at_4e44ab:
    if ((uint8_t)rd8(r, r->eax + 0x1) != (uint8_t)0x36)
    {
        goto at_4e44c3;
    }
    if ((uint8_t)rd8(r, r->eax + 0x2) != (uint8_t)0x34)
    {
        goto at_4e44c3;
    }
    set_high8(&r->edx, rd8(r, r->edi + 0x10));
    set_high8(&r->edx, ((r->edx >> 8) & 0xff) | 0x40);
    r->eax = r->eax + 0x3;
at_4e44c0:
    wr8(r, r->edi + 0x10, ((r->edx >> 8) & 0xff));
at_4e44c3:
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    r->ecx = pop_mem(r);
    r->ebx = pop_mem(r);
    return;
}

uint32_t vertrix_port_rtl_format_width_4e43c4(PORT_SIGNATURE)
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
