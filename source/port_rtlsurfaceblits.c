#include "port_rtlsurfaceblits.h"

/* Copies a rectangle from one surface to another, choosing the path from both surfaces' pixel sizes
 * (+0xc, +0xd) and locks (+0x10) and caching the sizes and pitches in 0x558c2c..0x558c43. */

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

/* A value pushed for the next call. */
static void push(Regs *r, uint32_t value)
{
    if (r->pushed < 32)
    {
        r->stack[r->pushed++] = value;
    }
}

/* A call of the tracked registers taking the last count values pushed (nearest first) and, unless
 * kept, popping them as the callee's ret does. */
static void call_with_stack(Regs *r, uint32_t target, unsigned count, int keep)
{
    uint32_t args[32] = {0};
    unsigned i;
    if (count > r->pushed)
    {
        count = r->pushed;
    }
    for (i = 0; i < count; i++)
    {
        args[i] = r->stack[r->pushed - 1 - i];
    }
    if (!keep)
    {
        r->pushed -= count;
    }
    vertrix_lift_in_esi = r->esi;
    vertrix_lift_in_edi = r->edi;
    vertrix_lift_in_ebp = r->ebp;
    r->eax =
        lift_call_arguments(&r->port->env, target, r->eax, r->edx, r->ebx, r->ecx, args, count);
    vertrix_lift_in_esi = vertrix_lift_in_edi = vertrix_lift_in_ebp = 0;
    r->edx = vertrix_lift_edx;
}

/* A call that pops nothing (cdecl, or no stack arguments): every value pushed passed and left for
 * the caller's add esp. */
static void call_keep(Regs *r, uint32_t target)
{
    call_with_stack(r, target, r->pushed, 1);
}

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

static void wr8(Regs *r, uint32_t address, uint32_t value)
{
    port_set8(r->port, address, 0, value);
}

static void wr16(Regs *r, uint32_t address, uint32_t value)
{
    port_set16(r->port, address, 0, value);
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

/* The last value pushed taken back. */
static uint32_t pop(Regs *r)
{
    return r->pushed != 0 ? r->stack[--r->pushed] : 0;
}

/* movs and rep movs of size bytes from esi to edi, forwards. */
static void movs(Regs *r, unsigned size)
{
    if (size == 1)
    {
        wr8(r, r->edi, rd8(r, r->esi));
    }
    else if (size == 2)
    {
        wr16(r, r->edi, rd16(r, r->esi));
    }
    else
    {
        wr32(r, r->edi, rd32(r, r->esi));
    }
    r->esi += size;
    r->edi += size;
}

static void rep_movs(Regs *r, unsigned size)
{
    for (; r->ecx != 0 && !r->port->env.failed; r->ecx--)
    {
        movs(r, size);
    }
}

/* Original 0x47ce10: Copies a rectangle from one surface to another, choosing the path from both
 * surfaces' pixel sizes (+0xc, +0xd) and locks (+0x10) and caching the sizes and pitches in
 * 0x558c2c..0x558c43. Evidence: calls 0x478eb0; reads 0x558c40, 0x558c41, 0x558c38, 0x558c3c,
 * 0x558c18, 0x558c14, 0x558c24, 0x558c2c, 0x558c30, 0x558c10, 0x558c0c, 0x558c42, 0x558c1c,
 * 0x558c20, 0x558c34, 0x558c43 and more; writes 0x558c40, 0x558c41, 0x558c42, 0x558c43, 0x558c38,
 * 0x558c3c, 0x558c2c, 0x558c30, 0x558c18, 0x558c14, 0x558c24, 0x558c10, 0x558c0c, 0x558c1c,
 * 0x558c20, 0x558c34 and more. Register-for-register from the listing (0x47ce18..0x47e1ec); labels
 * are the original addresses. */
static void run(Regs *r)
{
    r->esi = r->eax;
    r->edi = r->edx;
    wr32(r, r->ebp - 0x10, r->ebx);
    r->edx = rd32(r, r->ebp + 0x8);
    r->eax = rd32(r, r->ebp + 0xc);
    set_low8(&r->ebx, rd8(r, r->esi + 0xc));
    wr8(r, 0x558c40, (r->ebx & 0xff));
    set_low8(&r->ebx, rd8(r, r->edi + 0xc));
    wr8(r, 0x558c41, (r->ebx & 0xff));
    set_low8(&r->ebx, rd8(r, r->esi + 0xd));
    wr8(r, 0x558c42, (r->ebx & 0xff));
    set_low8(&r->ebx, rd8(r, r->edi + 0xd));
    wr8(r, 0x558c43, (r->ebx & 0xff));
    if (rd32(r, r->esi + 0x10) != 0x0)
    {
        goto at_47dbc3;
    }
    if (rd32(r, r->edi + 0x10) != 0x0)
    {
        goto at_47dbc3;
    }
    set_low8(&r->ebx, rd8(r, 0x558c40));
    if ((uint8_t)((r->ebx & 0xff)) != (uint8_t)0x4)
    {
        goto at_47cfb9;
    }
    if ((uint8_t)((r->ebx & 0xff)) != (uint8_t)rd8(r, 0x558c41))
    {
        goto at_47cfb9;
    }
    r->ebx = rd32(r, r->esi + 0x4);
    wr32(r, 0x558c38, r->ebx);
    r->ebx = rd32(r, r->edi + 0x4);
    wr32(r, 0x558c3c, r->ebx);
    r->ebx = rd32(r, 0x558c38);
    wr32(r, r->ebp - 0x14, r->ebx);
    r->ebx = rd32(r, r->ebp + 0x10);
    wr32(r, r->ebp - 0x14, rd32(r, r->ebp - 0x14) - r->ebx);
    r->ebx = rd32(r, r->ebp - 0x14);
    wr32(r, 0x558c2c, r->ebx);
    r->ebx = rd32(r, 0x558c3c);
    wr32(r, r->ebp - 0xc, r->ebx);
    r->ebx = rd32(r, r->ebp + 0x10);
    wr32(r, r->ebp - 0xc, rd32(r, r->ebp - 0xc) - r->ebx);
    r->ebx = rd32(r, r->ebp - 0xc);
    wr32(r, 0x558c30, r->ebx);
    r->ecx = r->ecx * rd32(r, 0x558c38);
    r->ebx = rd32(r, r->esi);
    r->esi = rd32(r, 0x558c3c);
    r->eax = r->eax * r->esi;
    r->ecx = r->ecx << 0x2;
    r->ebx = r->ebx + r->ecx;
    r->ecx = rd32(r, r->ebp - 0x10);
    r->ecx = r->ecx << 0x2;
    r->ebx = r->ebx + r->ecx;
    r->ecx = rd32(r, r->edi);
    r->eax = r->eax << 0x2;
    r->edx = r->edx << 0x2;
    r->eax = r->eax + r->ecx;
    r->eax = r->eax + r->edx;
    r->edi = rd32(r, 0x558c38);
    wr32(r, 0x558c18, r->eax);
    r->eax = rd32(r, r->ebp + 0x10);
    wr32(r, 0x558c14, r->ebx);
    if (r->eax == r->edi)
    {
        goto at_47cf81;
    }
at_47cf01:
    r->edi = 0x4;
    r->esi = 0;
at_47cf08:
    if (r->esi == rd32(r, r->ebp + 0x14))
    {
        goto at_47cfb0;
    }
    r->eax = rd32(r, r->ebp + 0x10);
    wr32(r, 0x558c24, r->eax);
    if (r->esi == r->eax)
    {
        goto at_47cf4c;
    }
    r->ebx = r->edi;
at_47cf1f:
    r->eax = rd32(r, 0x558c18);
    r->edx = rd32(r, 0x558c14);
    r->ecx = rd32(r, r->eax);
    r->eax = r->eax + r->ebx;
    wr32(r, r->edx, r->ecx);
    wr32(r, 0x558c18, r->eax);
    r->eax = rd32(r, 0x558c24);
    r->edx = r->edx + r->ebx;
    r->eax = r->eax - 1;
    wr32(r, 0x558c14, r->edx);
    wr32(r, 0x558c24, r->eax);
    if (r->esi != r->eax && !r->port->env.failed)
    {
        goto at_47cf1f;
    }
at_47cf4c:
    r->eax = rd32(r, 0x558c2c);
    r->ecx = rd32(r, 0x558c14);
    r->eax = r->eax << 0x2;
    r->ecx = r->ecx + r->eax;
    r->eax = rd32(r, 0x558c30);
    r->ebx = rd32(r, 0x558c18);
    r->eax = r->eax << 0x2;
    r->ebx = r->ebx + r->eax;
    r->eax = rd32(r, r->ebp + 0x14);
    wr32(r, 0x558c14, r->ecx);
    r->eax = r->eax - 1;
    wr32(r, 0x558c18, r->ebx);
    wr32(r, r->ebp + 0x14, r->eax);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_47cf08;
at_47cf81:
    if (r->esi != rd32(r, r->ebp + 0x10) && !r->port->env.failed)
    {
        goto at_47cf01;
    }
    r->ecx = rd32(r, r->ebp + 0x10);
    r->ecx = r->ecx * rd32(r, r->ebp + 0x14);
    r->esi = rd32(r, 0x558c18);
    r->edi = rd32(r, 0x558c14);
    r->ecx = r->ecx << 0x2;
at_47cfa0:
    push(r, r->edi);
    r->eax = r->ecx;
    r->ecx = r->ecx >> 0x2;
    rep_movs(r, 4);
    set_low8(&r->ecx, (r->eax & 0xff));
    set_low8(&r->ecx, (r->ecx & 0xff) & 0x3);
    rep_movs(r, 1);
    r->edi = pop(r);
at_47cfb0:
    r->edi = rd32(r, r->ebp - 0x8);
    r->esi = rd32(r, r->ebp - 0x4);
    return;
at_47cfb9:
    if ((uint8_t)rd8(r, 0x558c40) != (uint8_t)0x3)
    {
        goto at_47d0ec;
    }
    if ((uint8_t)rd8(r, 0x558c41) != (uint8_t)0x4)
    {
        goto at_47d0ec;
    }
    r->ebx = rd32(r, r->esi + 0x4);
    wr32(r, 0x558c38, r->ebx);
    r->ebx = rd32(r, r->edi + 0x4);
    wr32(r, 0x558c3c, r->ebx);
    r->ebx = rd32(r, 0x558c38);
    r->ebx = r->ebx - rd32(r, r->ebp + 0x10);
    wr32(r, r->ebp - 0xc, r->ebx);
    wr32(r, r->ebp - 0x14, r->ebx);
    r->ebx = r->ebx << 0x2;
    wr32(r, r->ebp - 0x14, r->ebx);
    r->ebx = rd32(r, r->ebp - 0xc);
    wr32(r, r->ebp - 0x14, rd32(r, r->ebp - 0x14) - r->ebx);
    r->ebx = rd32(r, r->ebp - 0x14);
    wr32(r, 0x558c2c, r->ebx);
    r->ebx = rd32(r, 0x558c3c);
    r->ebx = r->ebx - rd32(r, r->ebp + 0x10);
    r->ebx = r->ebx << 0x2;
    wr32(r, 0x558c30, r->ebx);
    r->eax = r->eax * rd32(r, 0x558c3c);
    r->eax = r->eax + r->edx;
    r->edx = rd32(r, r->edi);
    r->ecx = r->ecx * rd32(r, 0x558c38);
    r->eax = r->eax << 0x2;
    r->edx = r->edx + r->eax;
    wr32(r, 0x558c10, r->edx);
    r->edx = rd32(r, r->ebp - 0x10);
    r->edx = r->edx + r->ecx;
    r->eax = r->edx * 4;
    r->eax = r->eax - r->edx;
    r->edx = rd32(r, r->esi);
    r->edx = r->edx + r->eax;
    r->eax = rd32(r, r->ebp + 0x14);
    wr32(r, 0x558c0c, r->edx);
    flags(r, F_LOGIC, r->eax, 0, 32);
at_47d055:
    if (cond(r, CC_E) && !r->port->env.failed)
    {
        goto at_47cfb0;
    }
    r->eax = rd32(r, r->ebp + 0x10);
    wr32(r, 0x558c24, r->eax);
    if (r->eax == 0)
    {
        goto at_47d0ba;
    }
at_47d067:
    r->eax = rd32(r, 0x558c10);
    r->edx = rd32(r, 0x558c0c);
    r->eax = r->eax + 1;
    r->edx = r->edx + 1;
    set_low8(&r->ecx, rd8(r, r->eax - 0x1));
    wr32(r, 0x558c10, r->eax);
    wr32(r, 0x558c0c, r->edx);
    r->eax = r->eax + 1;
    wr8(r, r->edx - 0x1, (r->ecx & 0xff));
    r->edx = r->edx + 1;
    set_low8(&r->ecx, rd8(r, r->eax - 0x1));
    wr32(r, 0x558c10, r->eax);
    wr32(r, 0x558c0c, r->edx);
    r->eax = r->eax + 0x2;
    wr8(r, r->edx - 0x1, (r->ecx & 0xff));
    r->edx = r->edx + 1;
    set_low8(&r->ecx, rd8(r, r->eax - 0x2));
    wr32(r, 0x558c10, r->eax);
    wr32(r, 0x558c0c, r->edx);
    r->eax = rd32(r, 0x558c24);
    wr8(r, r->edx - 0x1, (r->ecx & 0xff));
    r->eax = r->eax - 1;
    flags(r, F_DEC, r->eax, 0, 32);
    wr32(r, 0x558c24, r->eax);
    if (cond(r, CC_NE) && !r->port->env.failed)
    {
        goto at_47d067;
    }
at_47d0ba:
    r->eax = rd32(r, 0x558c2c);
    r->edx = rd32(r, 0x558c0c);
    r->ecx = rd32(r, 0x558c10);
    r->edx = r->edx + r->eax;
    r->eax = rd32(r, 0x558c30);
    r->ebx = rd32(r, r->ebp + 0x14);
    r->ecx = r->ecx + r->eax;
    wr32(r, 0x558c0c, r->edx);
    wr32(r, 0x558c10, r->ecx);
    r->ebx = r->ebx - 1;
    flags(r, F_DEC, r->ebx, 0, 32);
    wr32(r, r->ebp + 0x14, r->ebx);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_47d055;
at_47d0ec:
    if ((uint8_t)rd8(r, 0x558c40) != (uint8_t)0x2)
    {
        goto at_47d343;
    }
    if ((uint8_t)rd8(r, 0x558c41) != (uint8_t)0x4)
    {
        goto at_47d343;
    }
    set_low8(&r->ebx, rd8(r, 0x558c42));
    if ((uint8_t)((r->ebx & 0xff)) != (uint8_t)0x2)
    {
        goto at_47d22a;
    }
    r->ebx = rd32(r, r->esi + 0x4);
    wr32(r, 0x558c38, r->ebx);
    r->ebx = rd32(r, r->edi + 0x4);
    wr32(r, 0x558c3c, r->ebx);
    r->ebx = rd32(r, 0x558c38);
    wr32(r, r->ebp - 0x14, r->ebx);
    r->ebx = rd32(r, r->ebp + 0x10);
    wr32(r, r->ebp - 0x14, rd32(r, r->ebp - 0x14) - r->ebx);
    r->ebx = rd32(r, r->ebp - 0x14);
    wr32(r, 0x558c2c, r->ebx);
    r->ebx = rd32(r, 0x558c3c);
    wr32(r, r->ebp - 0xc, r->ebx);
    r->ebx = rd32(r, r->ebp + 0x10);
    wr32(r, r->ebp - 0xc, rd32(r, r->ebp - 0xc) - r->ebx);
    r->ebx = rd32(r, r->ebp - 0xc);
    wr32(r, 0x558c30, r->ebx);
    r->eax = r->eax * rd32(r, 0x558c3c);
    r->eax = r->eax + r->edx;
    r->eax = r->eax << 0x2;
    r->edx = rd32(r, r->edi);
    r->edx = r->edx + r->eax;
    r->eax = rd32(r, 0x558c38);
    r->eax = r->eax * r->ecx;
    r->edi = rd32(r, r->ebp - 0x10);
    wr32(r, 0x558c18, r->edx);
    r->eax = r->eax + r->edi;
    r->edx = rd32(r, r->esi);
    r->eax = r->eax + r->eax;
    r->edx = r->edx + r->eax;
    r->eax = rd32(r, r->ebp + 0x14);
    wr32(r, 0x558c1c, r->edx);
    flags(r, F_LOGIC, r->eax, 0, 32);
at_47d18b:
    if (cond(r, CC_E) && !r->port->env.failed)
    {
        goto at_47cfb0;
    }
    r->eax = rd32(r, r->ebp + 0x10);
    wr32(r, 0x558c24, r->eax);
    if (r->eax == 0)
    {
        goto at_47d1f3;
    }
at_47d19d:
    r->eax = rd32(r, 0x558c18);
    r->edx = rd32(r, r->eax);
    r->ecx = rd32(r, r->eax);
    r->edx = r->edx & 0xf80000;
    r->ecx = r->ecx & 0xfc00;
    r->edx = r->edx >> 0x5;
    r->ecx = r->ecx >> 0x2;
    r->ecx = r->ecx | r->edx;
    r->edx = rd32(r, r->eax);
    r->edx = r->edx & 0xf8;
    r->edx = r->edx | r->ecx;
    r->edx = r->edx >> 0x3;
    r->ecx = r->edx;
    r->edx = rd32(r, 0x558c1c);
    r->eax = r->eax + 0x4;
    r->edx = r->edx + 0x2;
    r->edi = rd32(r, 0x558c24);
    wr32(r, 0x558c18, r->eax);
    wr16(r, r->edx - 0x2, (r->ecx & 0xffff));
    wr32(r, 0x558c1c, r->edx);
    r->edi = r->edi - 1;
    flags(r, F_DEC, r->edi, 0, 32);
    wr32(r, 0x558c24, r->edi);
    if (cond(r, CC_NE) && !r->port->env.failed)
    {
        goto at_47d19d;
    }
at_47d1f3:
    r->eax = rd32(r, 0x558c2c);
    r->edi = rd32(r, 0x558c1c);
    r->eax = r->eax + r->eax;
    r->edi = r->edi + r->eax;
    r->eax = rd32(r, 0x558c30);
    r->edx = rd32(r, 0x558c18);
    r->eax = r->eax << 0x2;
    r->ecx = rd32(r, r->ebp + 0x14);
    r->edx = r->edx + r->eax;
    wr32(r, 0x558c1c, r->edi);
    wr32(r, 0x558c18, r->edx);
    r->ecx = r->ecx - 1;
    flags(r, F_DEC, r->ecx, 0, 32);
    wr32(r, r->ebp + 0x14, r->ecx);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_47d18b;
at_47d22a:
    if ((uint8_t)((r->ebx & 0xff)) != (uint8_t)0x1 && !r->port->env.failed)
    {
        goto at_47cfb0;
    }
    r->ebx = rd32(r, r->esi + 0x4);
    wr32(r, 0x558c38, r->ebx);
    r->ebx = rd32(r, r->edi + 0x4);
    wr32(r, 0x558c3c, r->ebx);
    r->ebx = rd32(r, 0x558c38);
    wr32(r, r->ebp - 0xc, r->ebx);
    r->ebx = rd32(r, r->ebp + 0x10);
    wr32(r, r->ebp - 0xc, rd32(r, r->ebp - 0xc) - r->ebx);
    r->ebx = rd32(r, r->ebp - 0xc);
    wr32(r, 0x558c2c, r->ebx);
    r->ebx = rd32(r, 0x558c3c);
    wr32(r, r->ebp - 0x14, r->ebx);
    r->ebx = rd32(r, r->ebp + 0x10);
    wr32(r, r->ebp - 0x14, rd32(r, r->ebp - 0x14) - r->ebx);
    r->ebx = rd32(r, r->ebp - 0x14);
    wr32(r, 0x558c30, r->ebx);
    r->eax = r->eax * rd32(r, 0x558c3c);
    r->edx = r->edx + r->eax;
    r->eax = rd32(r, r->edi);
    r->ecx = r->ecx * rd32(r, 0x558c38);
    r->edx = r->edx << 0x2;
    r->eax = r->eax + r->edx;
    wr32(r, 0x558c18, r->eax);
    r->ecx = r->ecx + rd32(r, r->ebp - 0x10);
    r->eax = rd32(r, r->esi);
    r->ecx = r->ecx + r->ecx;
    r->eax = r->eax + r->ecx;
    r->edx = rd32(r, r->ebp + 0x14);
    wr32(r, 0x558c1c, r->eax);
    flags(r, F_LOGIC, r->edx, 0, 32);
at_47d2a4:
    if (cond(r, CC_E) && !r->port->env.failed)
    {
        goto at_47cfb0;
    }
    r->eax = rd32(r, r->ebp + 0x10);
    wr32(r, 0x558c24, r->eax);
    if (r->eax == 0)
    {
        goto at_47d30c;
    }
at_47d2b6:
    r->eax = rd32(r, 0x558c18);
    r->ecx = rd32(r, r->eax);
    r->edx = rd32(r, r->eax);
    r->ecx = r->ecx & 0xf80000;
    r->edx = r->edx & 0xf800;
    r->ecx = r->ecx >> 0x6;
    r->edx = r->edx >> 0x3;
    r->ecx = r->ecx | r->edx;
    r->edx = rd32(r, r->eax);
    r->edx = r->edx & 0xf8;
    r->edx = r->edx | r->ecx;
    r->edx = r->edx >> 0x3;
    r->ecx = r->edx;
    r->edx = rd32(r, 0x558c1c);
    r->eax = r->eax + 0x4;
    r->edx = r->edx + 0x2;
    r->ebx = rd32(r, 0x558c24);
    wr32(r, 0x558c18, r->eax);
    wr16(r, r->edx - 0x2, (r->ecx & 0xffff));
    wr32(r, 0x558c1c, r->edx);
    r->ebx = r->ebx - 1;
    flags(r, F_DEC, r->ebx, 0, 32);
    wr32(r, 0x558c24, r->ebx);
    if (cond(r, CC_NE) && !r->port->env.failed)
    {
        goto at_47d2b6;
    }
at_47d30c:
    r->eax = rd32(r, 0x558c2c);
    r->esi = rd32(r, 0x558c1c);
    r->eax = r->eax + r->eax;
    r->esi = r->esi + r->eax;
    r->eax = rd32(r, 0x558c30);
    r->edi = rd32(r, 0x558c18);
    r->eax = r->eax << 0x2;
    wr32(r, 0x558c1c, r->esi);
    r->edi = r->edi + r->eax;
    r->eax = rd32(r, r->ebp + 0x14);
    wr32(r, 0x558c18, r->edi);
    r->eax = r->eax - 1;
    flags(r, F_DEC, r->eax, 0, 32);
    wr32(r, r->ebp + 0x14, r->eax);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_47d2a4;
at_47d343:
    set_low8(&r->ebx, rd8(r, 0x558c40));
    if ((uint8_t)((r->ebx & 0xff)) != (uint8_t)0x2)
    {
        goto at_47d525;
    }
    if ((uint8_t)((r->ebx & 0xff)) != (uint8_t)rd8(r, 0x558c41))
    {
        goto at_47d525;
    }
    r->ebx = rd32(r, r->esi + 0x4);
    wr32(r, 0x558c38, r->ebx);
    r->ebx = rd32(r, r->edi + 0x4);
    wr32(r, 0x558c3c, r->ebx);
    r->ebx = rd32(r, 0x558c38);
    wr32(r, r->ebp - 0x14, r->ebx);
    r->ebx = rd32(r, r->ebp + 0x10);
    wr32(r, r->ebp - 0x14, rd32(r, r->ebp - 0x14) - r->ebx);
    r->ebx = rd32(r, r->ebp - 0x14);
    wr32(r, 0x558c2c, r->ebx);
    r->ebx = rd32(r, 0x558c3c);
    wr32(r, r->ebp - 0xc, r->ebx);
    r->ebx = rd32(r, r->ebp + 0x10);
    wr32(r, r->ebp - 0xc, rd32(r, r->ebp - 0xc) - r->ebx);
    r->ebx = rd32(r, r->ebp - 0xc);
    wr32(r, 0x558c30, r->ebx);
    r->ebx = rd32(r, 0x558c3c);
    r->eax = r->eax * r->ebx;
    r->eax = r->eax + r->edx;
    r->edx = rd32(r, r->edi);
    r->edi = rd32(r, 0x558c38);
    r->ecx = r->ecx * r->edi;
    r->eax = r->eax + r->eax;
    r->edx = r->edx + r->eax;
    r->ecx = r->ecx + rd32(r, r->ebp - 0x10);
    r->eax = rd32(r, r->esi);
    r->ecx = r->ecx + r->ecx;
    wr32(r, 0x558c20, r->edx);
    r->eax = r->eax + r->ecx;
    set_high8(&r->ecx, rd8(r, r->ebp + 0x10));
    wr32(r, 0x558c1c, r->eax);
    if ((uint8_t)(((r->ecx >> 8) & 0xff) & 0x3) == 0)
    {
        goto at_47d45c;
    }
    r->edi = 0x2;
    r->esi = 0;
at_47d3e1:
    if (r->esi == rd32(r, r->ebp + 0x14) && !r->port->env.failed)
    {
        goto at_47cfb0;
    }
    r->eax = rd32(r, r->ebp + 0x10);
    wr32(r, 0x558c24, r->eax);
    if (r->esi == r->eax)
    {
        goto at_47d429;
    }
    r->ebx = r->edi;
at_47d3f8:
    r->eax = rd32(r, 0x558c20);
    r->edx = rd32(r, 0x558c1c);
    set_low16(&r->ecx, rd16(r, r->eax));
    r->eax = r->eax + r->ebx;
    wr16(r, r->edx, (r->ecx & 0xffff));
    r->ecx = rd32(r, 0x558c24);
    wr32(r, 0x558c20, r->eax);
    r->edx = r->edx + r->ebx;
    r->ecx = r->ecx - 1;
    wr32(r, 0x558c1c, r->edx);
    wr32(r, 0x558c24, r->ecx);
    if (r->esi != r->ecx && !r->port->env.failed)
    {
        goto at_47d3f8;
    }
at_47d429:
    r->ebx = rd32(r, r->ebp + 0x14);
    r->eax = rd32(r, 0x558c2c);
    r->edx = rd32(r, 0x558c1c);
    r->eax = r->eax + r->eax;
    r->ecx = rd32(r, 0x558c20);
    r->edx = r->edx + r->eax;
    r->eax = rd32(r, 0x558c30);
    r->ebx = r->ebx - 1;
    r->eax = r->eax + r->eax;
    wr32(r, r->ebp + 0x14, r->ebx);
    r->ecx = r->ecx + r->eax;
    wr32(r, 0x558c1c, r->edx);
    wr32(r, 0x558c20, r->ecx);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_47d3e1;
at_47d45c:
    if (r->edi != rd32(r, r->ebp + 0x10))
    {
        goto at_47d46a;
    }
    if (r->ebx == rd32(r, r->ebp + 0x10))
    {
        goto at_47d50f;
    }
at_47d46a:
    r->eax = rd32(r, r->ebp + 0x10);
    r->eax = r->eax >> 0x1;
    r->ebx = rd32(r, r->ebp + 0x14);
    wr32(r, 0x558c34, r->eax);
    if (r->ebx == 0 && !r->port->env.failed)
    {
        goto at_47cfb0;
    }
    r->ebx = 0x4;
at_47d484:
    r->eax = rd32(r, 0x558c1c);
    wr32(r, 0x558c14, r->eax);
    r->eax = rd32(r, 0x558c20);
    wr32(r, 0x558c18, r->eax);
    r->eax = rd32(r, 0x558c34);
    wr32(r, 0x558c24, r->eax);
    if (r->eax == 0)
    {
        goto at_47d4d3;
    }
at_47d4a6:
    r->eax = rd32(r, 0x558c18);
    r->edx = rd32(r, 0x558c14);
    r->esi = rd32(r, 0x558c24);
    r->ecx = rd32(r, r->eax);
    r->eax = r->eax + r->ebx;
    wr32(r, r->edx, r->ecx);
    r->edx = r->edx + r->ebx;
    wr32(r, 0x558c18, r->eax);
    wr32(r, 0x558c14, r->edx);
    r->esi = r->esi - 1;
    flags(r, F_DEC, r->esi, 0, 32);
    wr32(r, 0x558c24, r->esi);
    if (cond(r, CC_NE) && !r->port->env.failed)
    {
        goto at_47d4a6;
    }
at_47d4d3:
    r->eax = rd32(r, 0x558c38);
    r->esi = rd32(r, 0x558c1c);
    r->eax = r->eax + r->eax;
    r->esi = r->esi + r->eax;
    r->eax = rd32(r, 0x558c3c);
    r->edi = rd32(r, 0x558c20);
    r->eax = r->eax + r->eax;
    wr32(r, 0x558c1c, r->esi);
    r->edi = r->edi + r->eax;
    r->eax = rd32(r, r->ebp + 0x14);
    wr32(r, 0x558c20, r->edi);
    r->eax = r->eax - 1;
    flags(r, F_DEC, r->eax, 0, 32);
    wr32(r, r->ebp + 0x14, r->eax);
    if (cond(r, CC_E) && !r->port->env.failed)
    {
        goto at_47cfb0;
    }
    if (r->port->env.failed)
    {
        return;
    }
    goto at_47d484;
at_47d50f:
    r->ecx = rd32(r, r->ebp + 0x10);
    r->ecx = r->ecx * rd32(r, r->ebp + 0x14);
    r->edi = rd32(r, 0x558c1c);
    r->esi = r->edx;
    r->ecx = r->ecx + r->ecx;
    if (r->port->env.failed)
    {
        return;
    }
    goto at_47cfa0;
at_47d525:
    if ((uint8_t)rd8(r, 0x558c40) != (uint8_t)0x1)
    {
        goto at_47d648;
    }
    if ((uint8_t)rd8(r, 0x558c41) != (uint8_t)0x4)
    {
        goto at_47d648;
    }
    r->ebx = rd32(r, r->esi + 0x4);
    wr32(r, 0x558c38, r->ebx);
    r->ebx = rd32(r, r->edi + 0x4);
    wr32(r, 0x558c3c, r->ebx);
    r->ebx = rd32(r, 0x558c38);
    wr32(r, r->ebp - 0xc, r->ebx);
    r->ebx = rd32(r, r->ebp + 0x10);
    wr32(r, r->ebp - 0xc, rd32(r, r->ebp - 0xc) - r->ebx);
    r->ebx = rd32(r, r->ebp - 0xc);
    wr32(r, 0x558c2c, r->ebx);
    r->ebx = rd32(r, 0x558c3c);
    wr32(r, r->ebp - 0xc, r->ebx);
    r->ebx = rd32(r, r->ebp + 0x10);
    wr32(r, r->ebp - 0xc, rd32(r, r->ebp - 0xc) - r->ebx);
    r->ebx = rd32(r, r->ebp - 0xc);
    wr32(r, 0x558c30, r->ebx);
    r->eax = r->eax * rd32(r, 0x558c3c);
    r->eax = r->eax + r->edx;
    r->edx = rd32(r, r->edi);
    r->ecx = r->ecx * rd32(r, 0x558c38);
    r->eax = r->eax << 0x2;
    r->edx = r->edx + r->eax;
    r->ecx = r->ecx + rd32(r, r->ebp - 0x10);
    r->eax = rd32(r, r->esi);
    wr32(r, 0x558c18, r->edx);
    r->eax = r->eax + r->ecx;
    r->edx = rd32(r, r->ebp + 0x14);
    wr32(r, 0x558c0c, r->eax);
    flags(r, F_LOGIC, r->edx, 0, 32);
at_47d5af:
    if (cond(r, CC_E) && !r->port->env.failed)
    {
        goto at_47cfb0;
    }
    r->eax = rd32(r, r->ebp + 0x10);
    wr32(r, 0x558c24, r->eax);
    if (r->eax == 0)
    {
        goto at_47d613;
    }
at_47d5c1:
    r->eax = rd32(r, 0x558c18);
    r->ecx = rd32(r, r->eax);
    r->edx = rd32(r, r->eax);
    r->ecx = r->ecx & 0xe00000;
    r->edx = r->edx & 0xe000;
    r->ecx = r->ecx >> 0xa;
    r->edx = r->edx >> 0x5;
    r->edx = r->edx | r->ecx;
    r->ecx = rd32(r, r->eax);
    r->ecx = r->ecx & 0xc0;
    r->edx = r->edx | r->ecx;
    r->edx = r->edx >> 0x6;
    r->eax = r->eax + 0x4;
    set_low8(&r->ecx, (r->edx & 0xff));
    r->edx = rd32(r, 0x558c0c);
    wr32(r, 0x558c18, r->eax);
    wr8(r, r->edx, (r->ecx & 0xff));
    r->edx = r->edx + 1;
    r->ecx = rd32(r, 0x558c24);
    wr32(r, 0x558c0c, r->edx);
    r->ecx = r->ecx - 1;
    flags(r, F_DEC, r->ecx, 0, 32);
    wr32(r, 0x558c24, r->ecx);
    if (cond(r, CC_NE) && !r->port->env.failed)
    {
        goto at_47d5c1;
    }
at_47d613:
    r->eax = rd32(r, 0x558c2c);
    r->ebx = rd32(r, 0x558c0c);
    r->ebx = r->ebx + r->eax;
    r->eax = rd32(r, 0x558c30);
    r->esi = rd32(r, 0x558c18);
    r->eax = r->eax << 0x2;
    r->edi = rd32(r, r->ebp + 0x14);
    r->esi = r->esi + r->eax;
    wr32(r, 0x558c0c, r->ebx);
    wr32(r, 0x558c18, r->esi);
    r->edi = r->edi - 1;
    flags(r, F_DEC, r->edi, 0, 32);
    wr32(r, r->ebp + 0x14, r->edi);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_47d5af;
at_47d648:
    set_low8(&r->ebx, rd8(r, 0x558c40));
    if ((uint8_t)((r->ebx & 0xff)) != (uint8_t)0x1)
    {
        goto at_47d819;
    }
    if ((uint8_t)((r->ebx & 0xff)) != (uint8_t)rd8(r, 0x558c41))
    {
        goto at_47d819;
    }
    r->ebx = rd32(r, r->esi + 0x4);
    wr32(r, 0x558c38, r->ebx);
    r->ebx = rd32(r, r->edi + 0x4);
    wr32(r, 0x558c3c, r->ebx);
    r->ebx = rd32(r, 0x558c38);
    wr32(r, r->ebp - 0xc, r->ebx);
    r->ebx = rd32(r, r->ebp + 0x10);
    wr32(r, r->ebp - 0xc, rd32(r, r->ebp - 0xc) - r->ebx);
    r->ebx = rd32(r, r->ebp - 0xc);
    wr32(r, 0x558c2c, r->ebx);
    r->ebx = rd32(r, 0x558c3c);
    wr32(r, r->ebp - 0xc, r->ebx);
    r->ebx = rd32(r, r->ebp + 0x10);
    wr32(r, r->ebp - 0xc, rd32(r, r->ebp - 0xc) - r->ebx);
    r->ebx = rd32(r, r->ebp - 0xc);
    wr32(r, 0x558c30, r->ebx);
    r->eax = r->eax * rd32(r, 0x558c3c);
    r->ebx = rd32(r, r->edi);
    r->edi = rd32(r, 0x558c38);
    r->ecx = r->ecx * r->edi;
    r->eax = r->eax + r->ebx;
    r->eax = r->eax + r->edx;
    wr32(r, 0x558c10, r->eax);
    r->eax = rd32(r, r->esi);
    r->edx = rd32(r, r->ebp - 0x10);
    r->eax = r->eax + r->ecx;
    r->edx = r->edx + r->eax;
    set_low8(&r->ecx, rd8(r, r->ebp + 0x10));
    wr32(r, 0x558c0c, r->edx);
    if ((uint8_t)((r->ecx & 0xff) & 0x3) == 0)
    {
        goto at_47d74f;
    }
    r->ebx = 0;
at_47d6dd:
    if (r->ebx == rd32(r, r->ebp + 0x14) && !r->port->env.failed)
    {
        goto at_47cfb0;
    }
    r->eax = rd32(r, r->ebp + 0x10);
    wr32(r, 0x558c24, r->eax);
    if (r->ebx == r->eax)
    {
        goto at_47d720;
    }
at_47d6f2:
    r->edx = rd32(r, 0x558c0c);
    r->eax = rd32(r, 0x558c10);
    r->edx = r->edx + 1;
    set_low8(&r->ecx, rd8(r, r->eax));
    r->eax = r->eax + 1;
    wr8(r, r->edx - 0x1, (r->ecx & 0xff));
    r->ecx = rd32(r, 0x558c24);
    wr32(r, 0x558c10, r->eax);
    r->ecx = r->ecx - 1;
    wr32(r, 0x558c0c, r->edx);
    wr32(r, 0x558c24, r->ecx);
    if (r->ebx != r->ecx && !r->port->env.failed)
    {
        goto at_47d6f2;
    }
at_47d720:
    r->ecx = rd32(r, r->ebp + 0x14);
    r->eax = rd32(r, 0x558c2c);
    r->edi = rd32(r, 0x558c0c);
    r->edx = rd32(r, 0x558c10);
    r->ecx = r->ecx - 1;
    r->edi = r->edi + r->eax;
    r->eax = rd32(r, 0x558c30);
    wr32(r, 0x558c0c, r->edi);
    r->edx = r->edx + r->eax;
    wr32(r, r->ebp + 0x14, r->ecx);
    wr32(r, 0x558c10, r->edx);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_47d6dd;
at_47d74f:
    if (r->edi != rd32(r, r->ebp + 0x10))
    {
        goto at_47d763;
    }
    r->eax = rd32(r, r->ebp + 0x10);
    if (r->eax == rd32(r, 0x558c3c))
    {
        goto at_47d805;
    }
at_47d763:
    r->eax = rd32(r, r->ebp + 0x10);
    r->eax = r->eax >> 0x2;
    r->ebx = rd32(r, r->ebp + 0x14);
    wr32(r, 0x558c34, r->eax);
    if (r->ebx == 0 && !r->port->env.failed)
    {
        goto at_47cfb0;
    }
    r->ebx = 0x4;
at_47d77e:
    r->eax = rd32(r, 0x558c0c);
    wr32(r, 0x558c14, r->eax);
    r->eax = rd32(r, 0x558c10);
    wr32(r, 0x558c18, r->eax);
    r->eax = rd32(r, 0x558c34);
    wr32(r, 0x558c24, r->eax);
    if (r->eax == 0)
    {
        goto at_47d7cd;
    }
at_47d7a0:
    r->edx = rd32(r, 0x558c18);
    r->eax = rd32(r, 0x558c14);
    r->esi = rd32(r, 0x558c24);
    r->ecx = rd32(r, r->edx);
    r->edx = r->edx + r->ebx;
    wr32(r, r->eax, r->ecx);
    r->eax = r->eax + r->ebx;
    wr32(r, 0x558c18, r->edx);
    wr32(r, 0x558c14, r->eax);
    r->esi = r->esi - 1;
    flags(r, F_DEC, r->esi, 0, 32);
    wr32(r, 0x558c24, r->esi);
    if (cond(r, CC_NE) && !r->port->env.failed)
    {
        goto at_47d7a0;
    }
at_47d7cd:
    r->eax = rd32(r, 0x558c38);
    r->esi = rd32(r, 0x558c0c);
    r->edi = rd32(r, 0x558c10);
    r->esi = r->esi + r->eax;
    r->eax = rd32(r, 0x558c3c);
    wr32(r, 0x558c0c, r->esi);
    r->edi = r->edi + r->eax;
    r->eax = rd32(r, r->ebp + 0x14);
    wr32(r, 0x558c10, r->edi);
    r->eax = r->eax - 1;
    flags(r, F_DEC, r->eax, 0, 32);
    wr32(r, r->ebp + 0x14, r->eax);
    if (cond(r, CC_E) && !r->port->env.failed)
    {
        goto at_47cfb0;
    }
    if (r->port->env.failed)
    {
        return;
    }
    goto at_47d77e;
at_47d805:
    r->ecx = rd32(r, r->ebp + 0x10);
    r->ecx = r->ecx * rd32(r, r->ebp + 0x14);
    r->edi = r->edx;
    r->esi = rd32(r, 0x558c10);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_47cfa0;
at_47d819:
    if ((uint8_t)rd8(r, 0x558c40) != (uint8_t)0x4)
    {
        goto at_47d948;
    }
    if ((uint8_t)rd8(r, 0x558c41) != (uint8_t)0x1)
    {
        goto at_47d948;
    }
    r->ebx = rd32(r, r->esi + 0x4);
    wr32(r, 0x558c38, r->ebx);
    r->ebx = rd32(r, r->edi + 0x4);
    wr32(r, 0x558c3c, r->ebx);
    r->ebx = rd32(r, 0x558c38);
    wr32(r, r->ebp - 0xc, r->ebx);
    r->ebx = rd32(r, r->ebp + 0x10);
    wr32(r, r->ebp - 0xc, rd32(r, r->ebp - 0xc) - r->ebx);
    r->ebx = rd32(r, r->ebp - 0xc);
    wr32(r, 0x558c2c, r->ebx);
    r->ebx = rd32(r, 0x558c3c);
    wr32(r, r->ebp - 0xc, r->ebx);
    r->ebx = rd32(r, r->ebp + 0x10);
    wr32(r, r->ebp - 0xc, rd32(r, r->ebp - 0xc) - r->ebx);
    r->ebx = rd32(r, r->ebp - 0xc);
    wr32(r, 0x558c30, r->ebx);
    r->eax = r->eax * rd32(r, 0x558c3c);
    r->eax = r->eax + r->edx;
    r->edx = rd32(r, r->edi);
    r->ecx = r->ecx * rd32(r, 0x558c38);
    r->edx = r->edx + r->eax;
    r->eax = rd32(r, r->ebp - 0x10);
    wr32(r, 0x558c10, r->edx);
    r->eax = r->eax + r->ecx;
    r->edx = rd32(r, r->esi);
    r->eax = r->eax << 0x2;
    r->edx = r->edx + r->eax;
    r->eax = rd32(r, r->ebp + 0x14);
    wr32(r, 0x558c14, r->edx);
    flags(r, F_LOGIC, r->eax, 0, 32);
at_47d8a6:
    if (cond(r, CC_E) && !r->port->env.failed)
    {
        goto at_47cfb0;
    }
    r->eax = rd32(r, r->ebp + 0x10);
    wr32(r, 0x558c24, r->eax);
    if (r->eax == 0)
    {
        goto at_47d913;
    }
at_47d8b8:
    r->eax = rd32(r, 0x558c10);
    set_low8(&r->edx, rd8(r, r->eax));
    set_low8(&r->edx, (r->edx & 0xff) & 0xe0);
    r->ecx = r->edx;
    r->ecx = r->ecx & 0xff;
    set_low8(&r->edx, rd8(r, r->eax));
    r->ecx = r->ecx << 0xa;
    set_low8(&r->edx, (r->edx & 0xff) & 0x1c);
    r->edx = r->edx & 0xff;
    r->edx = r->edx << 0x5;
    r->ecx = r->ecx | r->edx;
    set_low8(&r->edx, rd8(r, r->eax));
    set_low8(&r->edx, (r->edx & 0xff) & 0x3);
    r->edx = r->edx & 0xff;
    r->eax = r->eax + 1;
    r->ecx = r->ecx | r->edx;
    r->edx = rd32(r, 0x558c14);
    r->ecx = r->ecx << 0x6;
    wr32(r, 0x558c10, r->eax);
    wr32(r, r->edx, r->ecx);
    r->edx = r->edx + 0x4;
    r->ecx = rd32(r, 0x558c24);
    wr32(r, 0x558c14, r->edx);
    r->ecx = r->ecx - 1;
    flags(r, F_DEC, r->ecx, 0, 32);
    wr32(r, 0x558c24, r->ecx);
    if (cond(r, CC_NE) && !r->port->env.failed)
    {
        goto at_47d8b8;
    }
at_47d913:
    r->eax = rd32(r, 0x558c2c);
    r->ebx = rd32(r, 0x558c14);
    r->eax = r->eax << 0x2;
    r->esi = rd32(r, 0x558c10);
    r->ebx = r->ebx + r->eax;
    r->eax = rd32(r, 0x558c30);
    r->edi = rd32(r, r->ebp + 0x14);
    r->esi = r->esi + r->eax;
    wr32(r, 0x558c14, r->ebx);
    wr32(r, 0x558c10, r->esi);
    r->edi = r->edi - 1;
    flags(r, F_DEC, r->edi, 0, 32);
    wr32(r, r->ebp + 0x14, r->edi);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_47d8a6;
at_47d948:
    if ((uint8_t)rd8(r, 0x558c40) != (uint8_t)0x4 && !r->port->env.failed)
    {
        goto at_47cfb0;
    }
    set_high8(&r->ebx, rd8(r, 0x558c41));
    if ((uint8_t)(((r->ebx >> 8) & 0xff)) != (uint8_t)0x2 && !r->port->env.failed)
    {
        goto at_47cfb0;
    }
    set_low8(&r->ebx, rd8(r, 0x558c43));
    if ((uint8_t)((r->ebx & 0xff)) == (uint8_t)(((r->ebx >> 8) & 0xff)))
    {
        goto at_47daa0;
    }
    if ((uint8_t)((r->ebx & 0xff)) != (uint8_t)0x1 && !r->port->env.failed)
    {
        goto at_47cfb0;
    }
    r->ebx = rd32(r, r->esi + 0x4);
    wr32(r, 0x558c38, r->ebx);
    r->ebx = rd32(r, r->edi + 0x4);
    wr32(r, 0x558c3c, r->ebx);
    r->ebx = rd32(r, 0x558c38);
    wr32(r, r->ebp - 0xc, r->ebx);
    r->ebx = rd32(r, r->ebp + 0x10);
    wr32(r, r->ebp - 0xc, rd32(r, r->ebp - 0xc) - r->ebx);
    r->ebx = rd32(r, r->ebp - 0xc);
    wr32(r, 0x558c2c, r->ebx);
    r->ebx = rd32(r, 0x558c3c);
    wr32(r, r->ebp - 0xc, r->ebx);
    r->ebx = rd32(r, r->ebp + 0x10);
    wr32(r, r->ebp - 0xc, rd32(r, r->ebp - 0xc) - r->ebx);
    r->ebx = rd32(r, r->ebp - 0xc);
    wr32(r, 0x558c30, r->ebx);
    r->eax = r->eax * rd32(r, 0x558c3c);
    r->eax = r->eax + r->edx;
    r->edx = rd32(r, r->edi);
    r->ecx = r->ecx * rd32(r, 0x558c38);
    r->eax = r->eax + r->eax;
    r->edx = r->edx + r->eax;
    r->ecx = r->ecx + rd32(r, r->ebp - 0x10);
    r->ecx = r->ecx << 0x2;
    r->eax = rd32(r, r->esi);
    wr32(r, 0x558c20, r->edx);
    r->eax = r->eax + r->ecx;
    r->edx = rd32(r, r->ebp + 0x14);
    wr32(r, 0x558c14, r->eax);
    flags(r, F_LOGIC, r->edx, 0, 32);
at_47d9ed:
    if (cond(r, CC_E) && !r->port->env.failed)
    {
        goto at_47cfb0;
    }
    r->eax = rd32(r, r->ebp + 0x10);
    wr32(r, 0x558c24, r->eax);
    if (r->eax == 0)
    {
        goto at_47da69;
    }
at_47d9ff:
    r->eax = rd32(r, 0x558c20);
    set_low16(&r->edx, rd16(r, r->eax));
    set_low8(&r->edx, 0);
    set_high8(&r->edx, ((r->edx >> 8) & 0xff) & 0x7c);
    r->ecx = r->edx;
    r->ecx = r->ecx & 0xffff;
    set_low16(&r->edx, rd16(r, r->eax));
    r->ecx = r->ecx << 0x6;
    r->edx = r->edx & 0x3e0;
    r->edx = r->edx & 0xffff;
    r->edx = r->edx << 0x3;
    r->edx = r->edx | r->ecx;
    set_low16(&r->ecx, rd16(r, r->eax));
    set_high8(&r->ecx, 0);
    set_low8(&r->ecx, (r->ecx & 0xff) & 0x1f);
    r->ecx = r->ecx & 0xffff;
    r->edx = r->edx | r->ecx;
    r->ecx = r->edx * 8;
    r->edx = rd32(r, 0x558c14);
    r->eax = r->eax + 0x2;
    r->edx = r->edx + 0x4;
    wr32(r, 0x558c20, r->eax);
    r->eax = rd32(r, 0x558c24);
    wr32(r, r->edx - 0x4, r->ecx);
    wr32(r, 0x558c14, r->edx);
    r->eax = r->eax - 1;
    flags(r, F_DEC, r->eax, 0, 32);
    wr32(r, 0x558c24, r->eax);
    if (cond(r, CC_NE) && !r->port->env.failed)
    {
        goto at_47d9ff;
    }
at_47da69:
    r->eax = rd32(r, 0x558c2c);
    r->edx = rd32(r, 0x558c14);
    r->eax = r->eax << 0x2;
    r->edx = r->edx + r->eax;
    r->eax = rd32(r, 0x558c30);
    r->ecx = rd32(r, 0x558c20);
    r->eax = r->eax + r->eax;
    r->ebx = rd32(r, r->ebp + 0x14);
    r->ecx = r->ecx + r->eax;
    wr32(r, 0x558c14, r->edx);
    wr32(r, 0x558c20, r->ecx);
    r->ebx = r->ebx - 1;
    flags(r, F_DEC, r->ebx, 0, 32);
    wr32(r, r->ebp + 0x14, r->ebx);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_47d9ed;
at_47daa0:
    r->ebx = rd32(r, r->esi + 0x4);
    wr32(r, 0x558c38, r->ebx);
    r->ebx = rd32(r, r->edi + 0x4);
    wr32(r, 0x558c3c, r->ebx);
    r->ebx = rd32(r, 0x558c38);
    wr32(r, r->ebp - 0xc, r->ebx);
    r->ebx = rd32(r, r->ebp + 0x10);
    wr32(r, r->ebp - 0xc, rd32(r, r->ebp - 0xc) - r->ebx);
    r->ebx = rd32(r, r->ebp - 0xc);
    wr32(r, 0x558c2c, r->ebx);
    r->ebx = rd32(r, 0x558c3c);
    wr32(r, r->ebp - 0xc, r->ebx);
    r->ebx = rd32(r, r->ebp + 0x10);
    wr32(r, r->ebp - 0xc, rd32(r, r->ebp - 0xc) - r->ebx);
    r->ebx = rd32(r, r->ebp - 0xc);
    wr32(r, 0x558c30, r->ebx);
    r->eax = r->eax * rd32(r, 0x558c3c);
    r->eax = r->eax + r->edx;
    r->edx = rd32(r, r->edi);
    r->ecx = r->ecx * rd32(r, 0x558c38);
    r->eax = r->eax + r->eax;
    r->edx = r->edx + r->eax;
    r->ecx = r->ecx + rd32(r, r->ebp - 0x10);
    r->ecx = r->ecx << 0x2;
    r->eax = rd32(r, r->esi);
    wr32(r, 0x558c20, r->edx);
    r->eax = r->eax + r->ecx;
    r->edx = rd32(r, r->ebp + 0x14);
    wr32(r, 0x558c14, r->eax);
    flags(r, F_LOGIC, r->edx, 0, 32);
at_47db12:
    if (cond(r, CC_E) && !r->port->env.failed)
    {
        goto at_47cfb0;
    }
    r->eax = rd32(r, r->ebp + 0x10);
    wr32(r, 0x558c24, r->eax);
    if (r->eax == 0)
    {
        goto at_47db8c;
    }
at_47db24:
    r->eax = rd32(r, 0x558c20);
    set_low16(&r->edx, rd16(r, r->eax));
    set_low8(&r->edx, 0);
    set_high8(&r->edx, ((r->edx >> 8) & 0xff) & 0xf8);
    r->ecx = r->edx;
    r->ecx = r->ecx & 0xffff;
    set_low16(&r->edx, rd16(r, r->eax));
    r->ecx = r->ecx << 0x5;
    r->edx = r->edx & 0x7e0;
    r->edx = r->edx & 0xffff;
    r->edx = r->edx << 0x2;
    r->ecx = r->ecx | r->edx;
    set_low16(&r->edx, rd16(r, r->eax));
    set_high8(&r->edx, 0);
    set_low8(&r->edx, (r->edx & 0xff) & 0x1f);
    r->edx = r->edx & 0xffff;
    r->ecx = r->ecx | r->edx;
    r->edx = rd32(r, 0x558c14);
    r->edx = r->edx + 0x4;
    r->ecx = r->ecx << 0x3;
    r->eax = r->eax + 0x2;
    wr32(r, r->edx - 0x4, r->ecx);
    wr32(r, 0x558c14, r->edx);
    r->edx = rd32(r, 0x558c24);
    wr32(r, 0x558c20, r->eax);
    r->edx = r->edx - 1;
    flags(r, F_DEC, r->edx, 0, 32);
    wr32(r, 0x558c24, r->edx);
    if (cond(r, CC_NE) && !r->port->env.failed)
    {
        goto at_47db24;
    }
at_47db8c:
    r->eax = rd32(r, 0x558c2c);
    r->ecx = rd32(r, 0x558c14);
    r->eax = r->eax << 0x2;
    r->ecx = r->ecx + r->eax;
    r->eax = rd32(r, 0x558c30);
    r->ebx = rd32(r, 0x558c20);
    r->eax = r->eax + r->eax;
    r->esi = rd32(r, r->ebp + 0x14);
    r->ebx = r->ebx + r->eax;
    wr32(r, 0x558c14, r->ecx);
    wr32(r, 0x558c20, r->ebx);
    r->esi = r->esi - 1;
    flags(r, F_DEC, r->esi, 0, 32);
    wr32(r, r->ebp + 0x14, r->esi);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_47db12;
at_47dbc3:
    r->ebx = r->eax;
    r->eax = r->edi;
    call_keep(r, 0x478eb0);
    r->edx = rd32(r, r->ebp - 0x10);
    wr32(r, 0x558c44, r->eax);
    r->ebx = r->ecx;
    r->eax = r->esi;
    call_keep(r, 0x478eb0);
    r->ecx = 0;
    r->edx = rd32(r, r->ebp + 0x10);
    set_low8(&r->ecx, rd8(r, 0x558c40));
    r->ecx = r->ecx * r->edx;
    r->edx = rd32(r, r->esi + 0x14);
    r->edx = r->edx - r->ecx;
    wr32(r, 0x558c2c, r->edx);
    r->edx = 0;
    r->ebx = rd32(r, r->ebp + 0x10);
    set_low8(&r->edx, rd8(r, 0x558c41));
    r->ebx = r->ebx * r->edx;
    wr32(r, 0x558c48, r->eax);
    wr32(r, 0x558c14, r->eax);
    wr32(r, 0x558c1c, r->eax);
    wr32(r, 0x558c0c, r->eax);
    r->edx = rd32(r, r->edi + 0x14);
    set_low8(&r->eax, rd8(r, 0x558c40));
    r->edx = r->edx - r->ebx;
    set_high8(&r->eax, rd8(r, 0x558c41));
    wr32(r, 0x558c30, r->edx);
    r->edx = rd32(r, 0x558c44);
    wr32(r, 0x558c18, r->edx);
    wr32(r, 0x558c20, r->edx);
    wr32(r, 0x558c10, r->edx);
    if ((uint8_t)((r->eax & 0xff)) != (uint8_t)(((r->eax >> 8) & 0xff)))
    {
        goto at_47dcc9;
    }
    r->eax = rd32(r, r->esi + 0x14);
    wr32(r, 0x558c28, r->ecx);
    wr32(r, 0x558c2c, r->eax);
    r->eax = rd32(r, r->edi + 0x14);
    r->esi = rd32(r, r->ebp + 0x14);
    wr32(r, 0x558c30, r->eax);
    if (r->esi == 0 && !r->port->env.failed)
    {
        goto at_47cfb0;
    }
at_47dc6f:
    r->ecx = rd32(r, 0x558c28);
    r->esi = rd32(r, 0x558c10);
    r->edi = rd32(r, 0x558c0c);
    push(r, r->edi);
    r->eax = r->ecx;
    r->ecx = r->ecx >> 0x2;
    rep_movs(r, 4);
    set_low8(&r->ecx, (r->eax & 0xff));
    set_low8(&r->ecx, (r->ecx & 0xff) & 0x3);
    rep_movs(r, 1);
    r->edi = pop(r);
    r->eax = rd32(r, 0x558c2c);
    r->esi = rd32(r, 0x558c0c);
    r->edi = rd32(r, 0x558c10);
    r->esi = r->esi + r->eax;
    r->eax = rd32(r, 0x558c30);
    wr32(r, 0x558c0c, r->esi);
    r->edi = r->edi + r->eax;
    r->eax = rd32(r, r->ebp + 0x14);
    wr32(r, 0x558c10, r->edi);
    r->eax = r->eax - 1;
    flags(r, F_DEC, r->eax, 0, 32);
    wr32(r, r->ebp + 0x14, r->eax);
    if (cond(r, CC_NE) && !r->port->env.failed)
    {
        goto at_47dc6f;
    }
    r->edi = rd32(r, r->ebp - 0x8);
    r->esi = rd32(r, r->ebp - 0x4);
    return;
at_47dcc9:
    if ((uint8_t)((r->eax & 0xff)) != (uint8_t)0x3)
    {
        goto at_47dd78;
    }
    if ((uint8_t)(((r->eax >> 8) & 0xff)) != (uint8_t)0x4)
    {
        goto at_47dd78;
    }
    r->ebx = 0;
at_47dcdc:
    if (r->ebx == rd32(r, r->ebp + 0x14) && !r->port->env.failed)
    {
        goto at_47cfb0;
    }
    r->eax = rd32(r, r->ebp + 0x10);
    wr32(r, 0x558c24, r->eax);
    if (r->ebx == r->eax)
    {
        goto at_47dd47;
    }
at_47dcf1:
    r->eax = rd32(r, 0x558c10);
    r->edx = rd32(r, 0x558c0c);
    r->eax = r->eax + 1;
    r->edx = r->edx + 1;
    set_low8(&r->ecx, rd8(r, r->eax - 0x1));
    wr32(r, 0x558c10, r->eax);
    wr32(r, 0x558c0c, r->edx);
    r->eax = r->eax + 1;
    wr8(r, r->edx - 0x1, (r->ecx & 0xff));
    r->edx = r->edx + 1;
    set_low8(&r->ecx, rd8(r, r->eax - 0x1));
    wr32(r, 0x558c10, r->eax);
    wr32(r, 0x558c0c, r->edx);
    wr8(r, r->edx - 0x1, (r->ecx & 0xff));
    r->edx = r->edx + 1;
    set_low8(&r->ecx, rd8(r, r->eax));
    wr32(r, 0x558c0c, r->edx);
    wr8(r, r->edx - 0x1, (r->ecx & 0xff));
    r->edx = rd32(r, 0x558c24);
    r->eax = r->eax + 0x2;
    r->edx = r->edx - 1;
    wr32(r, 0x558c10, r->eax);
    wr32(r, 0x558c24, r->edx);
    if (r->ebx != r->edx && !r->port->env.failed)
    {
        goto at_47dcf1;
    }
at_47dd47:
    r->eax = rd32(r, 0x558c2c);
    r->esi = rd32(r, 0x558c0c);
    r->edi = rd32(r, 0x558c10);
    r->esi = r->esi + r->eax;
    r->edi = r->edi + rd32(r, 0x558c30);
    r->eax = rd32(r, r->ebp + 0x14);
    wr32(r, 0x558c0c, r->esi);
    r->eax = r->eax - 1;
    wr32(r, 0x558c10, r->edi);
    wr32(r, r->ebp + 0x14, r->eax);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_47dcdc;
at_47dd78:
    set_low8(&r->ebx, rd8(r, 0x558c40));
    if ((uint8_t)((r->ebx & 0xff)) != (uint8_t)0x2)
    {
        goto at_47dee8;
    }
    if ((uint8_t)rd8(r, 0x558c41) != (uint8_t)0x4)
    {
        goto at_47dee8;
    }
    set_low8(&r->ecx, rd8(r, 0x558c42));
    if ((uint8_t)((r->ecx & 0xff)) != (uint8_t)((r->ebx & 0xff)))
    {
        goto at_47de3f;
    }
    r->ebx = 0;
at_47dda4:
    if (r->ebx == rd32(r, r->ebp + 0x14) && !r->port->env.failed)
    {
        goto at_47cfb0;
    }
    r->eax = rd32(r, r->ebp + 0x10);
    wr32(r, 0x558c24, r->eax);
    if (r->ebx == r->eax)
    {
        goto at_47de0f;
    }
at_47ddb9:
    r->eax = rd32(r, 0x558c18);
    r->ecx = rd32(r, r->eax);
    r->edx = rd32(r, r->eax);
    r->ecx = r->ecx & 0xf80000;
    r->edx = r->edx & 0xfc00;
    r->ecx = r->ecx >> 0x5;
    r->edx = r->edx >> 0x2;
    r->edx = r->edx | r->ecx;
    r->ecx = rd32(r, r->eax);
    r->ecx = r->ecx & 0xf8;
    r->ecx = r->ecx | r->edx;
    r->edx = rd32(r, 0x558c1c);
    r->edx = r->edx + 0x2;
    r->ecx = r->ecx >> 0x3;
    wr16(r, r->edx - 0x2, (r->ecx & 0xffff));
    wr32(r, 0x558c1c, r->edx);
    r->edx = rd32(r, 0x558c24);
    r->eax = r->eax + 0x4;
    r->edx = r->edx - 1;
    wr32(r, 0x558c18, r->eax);
    wr32(r, 0x558c24, r->edx);
    if (r->ebx != r->edx && !r->port->env.failed)
    {
        goto at_47ddb9;
    }
at_47de0f:
    r->eax = rd32(r, 0x558c1c);
    r->edx = rd32(r, 0x558c2c);
    r->esi = rd32(r, r->ebp + 0x14);
    r->eax = r->eax + r->edx;
    r->edx = rd32(r, 0x558c30);
    wr32(r, 0x558c1c, r->eax);
    r->eax = rd32(r, 0x558c18);
    r->esi = r->esi - 1;
    r->eax = r->eax + r->edx;
    wr32(r, r->ebp + 0x14, r->esi);
    wr32(r, 0x558c18, r->eax);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_47dda4;
at_47de3f:
    if ((uint8_t)((r->ecx & 0xff)) != (uint8_t)0x1 && !r->port->env.failed)
    {
        goto at_47cfb0;
    }
    r->ebx = 0;
at_47de4a:
    if (r->ebx == rd32(r, r->ebp + 0x14) && !r->port->env.failed)
    {
        goto at_47cfb0;
    }
    r->eax = rd32(r, r->ebp + 0x10);
    wr32(r, 0x558c24, r->eax);
    if (r->ebx == r->eax)
    {
        goto at_47deb7;
    }
at_47de5f:
    r->eax = rd32(r, 0x558c18);
    r->ecx = rd32(r, r->eax);
    r->edx = rd32(r, r->eax);
    r->ecx = r->ecx & 0xf80000;
    r->edx = r->edx & 0xf800;
    r->ecx = r->ecx >> 0x6;
    r->edx = r->edx >> 0x3;
    r->edx = r->edx | r->ecx;
    r->ecx = rd32(r, r->eax);
    r->ecx = r->ecx & 0xf8;
    r->edx = r->edx | r->ecx;
    r->edx = r->edx >> 0x3;
    r->ecx = r->edx;
    r->edx = rd32(r, 0x558c1c);
    r->edx = r->edx + 0x2;
    wr16(r, r->edx - 0x2, (r->ecx & 0xffff));
    wr32(r, 0x558c1c, r->edx);
    r->edx = rd32(r, 0x558c24);
    r->eax = r->eax + 0x4;
    r->edx = r->edx - 1;
    wr32(r, 0x558c18, r->eax);
    wr32(r, 0x558c24, r->edx);
    if (r->ebx != r->edx && !r->port->env.failed)
    {
        goto at_47de5f;
    }
at_47deb7:
    r->edx = rd32(r, 0x558c1c);
    r->eax = rd32(r, 0x558c2c);
    r->esi = rd32(r, r->ebp + 0x14);
    r->edx = r->edx + r->eax;
    r->eax = rd32(r, 0x558c18);
    wr32(r, 0x558c1c, r->edx);
    r->edx = rd32(r, 0x558c30);
    r->esi = r->esi - 1;
    r->eax = r->eax + r->edx;
    wr32(r, r->ebp + 0x14, r->esi);
    wr32(r, 0x558c18, r->eax);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_47de4a;
at_47dee8:
    if ((uint8_t)rd8(r, 0x558c40) != (uint8_t)0x1)
    {
        goto at_47df9d;
    }
    if ((uint8_t)rd8(r, 0x558c41) != (uint8_t)0x4)
    {
        goto at_47df9d;
    }
    r->ebx = 0;
at_47df04:
    if (r->ebx == rd32(r, r->ebp + 0x14) && !r->port->env.failed)
    {
        goto at_47cfb0;
    }
    r->eax = rd32(r, r->ebp + 0x10);
    wr32(r, 0x558c24, r->eax);
    if (r->ebx == r->eax)
    {
        goto at_47df6c;
    }
at_47df19:
    r->eax = rd32(r, 0x558c18);
    r->ecx = rd32(r, r->eax);
    r->edx = rd32(r, r->eax);
    r->ecx = r->ecx & 0xe00000;
    r->edx = r->edx & 0xe000;
    r->ecx = r->ecx >> 0xa;
    r->edx = r->edx >> 0x5;
    r->ecx = r->ecx | r->edx;
    r->edx = rd32(r, r->eax);
    r->edx = r->edx & 0xc0;
    r->eax = r->eax + 0x4;
    r->edx = r->edx | r->ecx;
    wr32(r, 0x558c18, r->eax);
    r->edx = r->edx >> 0x6;
    r->eax = rd32(r, 0x558c24);
    set_low8(&r->ecx, (r->edx & 0xff));
    r->edx = rd32(r, 0x558c0c);
    r->eax = r->eax - 1;
    r->edx = r->edx + 1;
    wr32(r, 0x558c24, r->eax);
    wr8(r, r->edx - 0x1, (r->ecx & 0xff));
    wr32(r, 0x558c0c, r->edx);
    if (r->ebx != r->eax && !r->port->env.failed)
    {
        goto at_47df19;
    }
at_47df6c:
    r->esi = rd32(r, r->ebp + 0x14);
    r->eax = rd32(r, 0x558c2c);
    r->ecx = rd32(r, 0x558c0c);
    r->edx = rd32(r, 0x558c30);
    r->esi = r->esi - 1;
    r->ecx = r->ecx + r->eax;
    r->eax = rd32(r, 0x558c18);
    wr32(r, 0x558c0c, r->ecx);
    r->eax = r->eax + r->edx;
    wr32(r, r->ebp + 0x14, r->esi);
    wr32(r, 0x558c18, r->eax);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_47df04;
at_47df9d:
    if ((uint8_t)rd8(r, 0x558c40) != (uint8_t)0x4)
    {
        goto at_47e05d;
    }
    if ((uint8_t)rd8(r, 0x558c41) != (uint8_t)0x1)
    {
        goto at_47e05d;
    }
    r->ebx = 0;
at_47dfb9:
    if (r->ebx == rd32(r, r->ebp + 0x14) && !r->port->env.failed)
    {
        goto at_47cfb0;
    }
    r->eax = rd32(r, r->ebp + 0x10);
    wr32(r, 0x558c24, r->eax);
    if (r->ebx == r->eax)
    {
        goto at_47e02c;
    }
at_47dfce:
    r->eax = rd32(r, 0x558c10);
    set_low8(&r->edx, rd8(r, r->eax));
    set_low8(&r->edx, (r->edx & 0xff) & 0xe0);
    r->ecx = r->edx;
    r->ecx = r->ecx & 0xff;
    set_low8(&r->edx, rd8(r, r->eax));
    r->ecx = r->ecx << 0xa;
    set_low8(&r->edx, (r->edx & 0xff) & 0x1c);
    r->edx = r->edx & 0xff;
    r->edx = r->edx << 0x5;
    r->ecx = r->ecx | r->edx;
    set_low8(&r->edx, rd8(r, r->eax));
    set_low8(&r->edx, (r->edx & 0xff) & 0x3);
    r->edi = rd32(r, 0x558c24);
    r->eax = r->eax + 1;
    r->edx = r->edx & 0xff;
    wr32(r, 0x558c10, r->eax);
    r->ecx = r->ecx | r->edx;
    r->edx = rd32(r, 0x558c14);
    r->edi = r->edi - 1;
    r->edx = r->edx + 0x4;
    r->ecx = r->ecx << 0x6;
    wr32(r, 0x558c24, r->edi);
    wr32(r, r->edx - 0x4, r->ecx);
    wr32(r, 0x558c14, r->edx);
    if (r->ebx != r->edi && !r->port->env.failed)
    {
        goto at_47dfce;
    }
at_47e02c:
    r->eax = rd32(r, 0x558c14);
    r->edx = rd32(r, 0x558c2c);
    r->ecx = rd32(r, r->ebp + 0x14);
    r->eax = r->eax + r->edx;
    r->edx = rd32(r, 0x558c10);
    wr32(r, 0x558c14, r->eax);
    r->eax = rd32(r, 0x558c30);
    r->ecx = r->ecx - 1;
    r->edx = r->edx + r->eax;
    wr32(r, r->ebp + 0x14, r->ecx);
    wr32(r, 0x558c10, r->edx);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_47dfb9;
at_47e05d:
    if ((uint8_t)rd8(r, 0x558c40) != (uint8_t)0x4 && !r->port->env.failed)
    {
        goto at_47cfb0;
    }
    set_high8(&r->edx, rd8(r, 0x558c41));
    if ((uint8_t)(((r->edx >> 8) & 0xff)) != (uint8_t)0x2 && !r->port->env.failed)
    {
        goto at_47cfb0;
    }
    set_low8(&r->ebx, rd8(r, 0x558c43));
    if ((uint8_t)((r->ebx & 0xff)) != (uint8_t)(((r->edx >> 8) & 0xff)))
    {
        goto at_47e137;
    }
    r->esi = 0;
at_47e089:
    if (r->esi == rd32(r, r->ebp + 0x14) && !r->port->env.failed)
    {
        goto at_47cfb0;
    }
    r->eax = rd32(r, r->ebp + 0x10);
    wr32(r, 0x558c24, r->eax);
    if (r->esi == r->eax)
    {
        goto at_47e107;
    }
at_47e09e:
    r->eax = rd32(r, 0x558c20);
    set_low16(&r->edx, rd16(r, r->eax));
    set_low8(&r->edx, 0);
    set_high8(&r->edx, ((r->edx >> 8) & 0xff) & 0xf8);
    r->ebx = r->edx;
    r->ecx = 0;
    set_low16(&r->edx, rd16(r, r->eax));
    r->ebx = r->ebx & 0xffff;
    r->edx = r->edx & 0x7e0;
    r->ebx = r->ebx << 0x5;
    set_low16(&r->ecx, (r->edx & 0xffff));
    set_low16(&r->edx, rd16(r, r->eax));
    r->ecx = r->ecx << 0x2;
    set_high8(&r->edx, 0);
    r->ecx = r->ecx | r->ebx;
    set_low8(&r->edx, (r->edx & 0xff) & 0x1f);
    r->edi = rd32(r, 0x558c24);
    r->eax = r->eax + 0x2;
    r->edx = r->edx & 0xffff;
    wr32(r, 0x558c20, r->eax);
    r->ecx = r->ecx | r->edx;
    r->edx = rd32(r, 0x558c14);
    r->edi = r->edi - 1;
    r->edx = r->edx + 0x4;
    r->ecx = r->ecx << 0x3;
    wr32(r, 0x558c24, r->edi);
    wr32(r, r->edx - 0x4, r->ecx);
    wr32(r, 0x558c14, r->edx);
    if (r->esi != r->edi && !r->port->env.failed)
    {
        goto at_47e09e;
    }
at_47e107:
    r->eax = rd32(r, 0x558c14);
    r->edx = rd32(r, 0x558c2c);
    r->eax = r->eax + r->edx;
    r->edx = rd32(r, 0x558c30);
    wr32(r, 0x558c14, r->eax);
    r->eax = rd32(r, 0x558c20);
    r->eax = r->eax + r->edx;
    r->edx = rd32(r, r->ebp + 0x14);
    r->edx = r->edx - 1;
    wr32(r, 0x558c20, r->eax);
    wr32(r, r->ebp + 0x14, r->edx);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_47e089;
at_47e137:
    if ((uint8_t)((r->ebx & 0xff)) != (uint8_t)0x1 && !r->port->env.failed)
    {
        goto at_47cfb0;
    }
    r->ebx = 0;
at_47e142:
    if (r->ebx == rd32(r, r->ebp + 0x14) && !r->port->env.failed)
    {
        goto at_47cfb0;
    }
    r->eax = rd32(r, r->ebp + 0x10);
    wr32(r, 0x558c24, r->eax);
    if (r->ebx == r->eax)
    {
        goto at_47e1c3;
    }
at_47e157:
    r->eax = rd32(r, 0x558c20);
    set_low16(&r->edx, rd16(r, r->eax));
    set_low8(&r->edx, 0);
    set_high8(&r->edx, ((r->edx >> 8) & 0xff) & 0x7c);
    r->edx = r->edx & 0xffff;
    set_low16(&r->ecx, rd16(r, r->eax));
    r->edx = r->edx << 0x6;
    r->ecx = r->ecx & 0x3e0;
    r->ecx = r->ecx & 0xffff;
    r->ecx = r->ecx << 0x3;
    r->ecx = r->ecx | r->edx;
    set_low16(&r->edx, rd16(r, r->eax));
    set_high8(&r->edx, 0);
    set_low8(&r->edx, (r->edx & 0xff) & 0x1f);
    r->edx = r->edx & 0xffff;
    r->edx = r->edx | r->ecx;
    r->edi = rd32(r, 0x558c24);
    r->ecx = r->edx * 8;
    r->eax = r->eax + 0x2;
    r->edx = rd32(r, 0x558c14);
    r->edi = r->edi - 1;
    r->edx = r->edx + 0x4;
    wr32(r, 0x558c20, r->eax);
    wr32(r, 0x558c24, r->edi);
    wr32(r, r->edx - 0x4, r->ecx);
    wr32(r, 0x558c14, r->edx);
    if (r->ebx != r->edi && !r->port->env.failed)
    {
        goto at_47e157;
    }
at_47e1c3:
    r->edx = rd32(r, 0x558c14);
    r->eax = rd32(r, 0x558c2c);
    r->edx = r->edx + r->eax;
    r->eax = rd32(r, 0x558c30);
    wr32(r, 0x558c14, r->edx);
    r->edx = rd32(r, 0x558c20);
    r->edx = r->edx + r->eax;
    wr32(r, 0x558c20, r->edx);
    wr32(r, r->ebp + 0x14, rd32(r, r->ebp + 0x14) - 1);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_47e142;
}

uint32_t vertrix_port_surface_blit_47ce10(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x18
    };
    Port port;
    uint8_t stack[BELOW + 8 + 4 * 4];
    Regs r;
    port_open_arguments(&port, stack, calls, services, globals, entry, BELOW, 4);
    memset(&r, 0, sizeof r);
    r.port = &port;
    r.eax = entry->eax;
    r.edx = entry->edx;
    r.ebx = entry->ebx;
    r.ecx = entry->ecx;
    r.esi = entry->esi;
    r.edi = entry->edi;
    r.ebp = entry->esp - 4;
    port_set32(&port, r.ebp, 0, entry->ebp);
    port_set32(&port, r.ebp, -0x4u, entry->esi);
    port_set32(&port, r.ebp, -0x8u, entry->edi);
    run(&r);
    return port_return(&port, r.eax, r.edx);
}
