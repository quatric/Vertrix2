#include "port_rtlaichainsearches.h"

/* The AI chain search: tries each placement and scores the chains it would set off (see ai_player.c
 * vertrix_ai_chain_search). */

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

static void call(Regs *r, uint32_t target, unsigned count)
{
    call_with_stack(r, target, count, 0);
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

/* Original 0x4269e0: The AI chain search: tries each placement and scores the chains it would set
 * off (see ai_player.c vertrix_ai_chain_search). Evidence: calls 0x4eb5c0, 0x4261b0, 0x432840,
 * 0x4346b0, 0x432980. Register-for-register from the listing (0x4269eb..0x42708c); labels are the
 * original addresses. */
static void run(Regs *r)
{
    wr32(r, r->ebp - 0x38, r->eax);
    wr32(r, r->ebp - 0x28, r->edx);
    wr32(r, r->ebp - 0x2c, r->ebx);
    wr32(r, r->ebp - 0x3c, r->ecx);
    set_high8(&r->eax, 0x1);
    r->ebx = 0x5;
    r->edx = 0;
    wr8(r, r->ebp - 0xc, ((r->eax >> 8) & 0xff));
    wr32(r, r->ebp - 0x10, r->edx);
    r->eax = r->ebp - 0x5c;
    r->edx = 0;
    call_keep(r, 0x4eb5c0);
    r->ebx = 0x5;
    r->eax = r->ebp - 0x4c;
    r->edx = 0;
    call_keep(r, 0x4eb5c0);
    r->ebx = 0x5;
    r->eax = r->ebp - 0x6c;
    r->edx = 0;
    r->ecx = 0x41;
    call_keep(r, 0x4eb5c0);
    r->ebx = 0x5;
    r->eax = r->ebp - 0x64;
    r->edx = 0;
    r->edi = r->ebp - 0xb0;
    call_keep(r, 0x4eb5c0);
    r->eax = rd32(r, r->ebp - 0x38);
    r->edx = rd32(r, r->ebp + 0x18);
    r->eax = r->eax + 0x184;
    r->ebx = r->ebp - 0x54;
    r->esi = r->eax;
    wr32(r, r->ebp - 0x40, r->eax);
    push(r, r->edi);
    r->eax = r->ecx;
    r->ecx = r->ecx >> 0x2;
    rep_movs(r, 4);
    set_low8(&r->ecx, (r->eax & 0xff));
    set_low8(&r->ecx, (r->ecx & 0xff) & 0x3);
    rep_movs(r, 1);
    r->edi = pop(r);
    r->ecx = rd32(r, r->ebp + 0x14);
    push(r, r->edx);
    r->eax = rd32(r, r->ebp - 0x38);
    r->edx = r->ebp - 0xb0;
    call(r, 0x4261b0, 1);
    r->ecx = 0;
    r->eax = rd32(r, r->ebp - 0x40);
    wr32(r, r->ebp - 0x20, r->ecx);
    wr32(r, r->ebp - 0x34, r->eax);
    wr32(r, r->ebp - 0x30, r->eax);
    wr32(r, r->ebp - 0x24, r->ecx);
at_426a8e:
    r->eax = rd32(r, r->ebp - 0x20);
    if ((uint8_t)rd8(r, r->eax + r->ebp - 0x54) != (uint8_t)0x0)
    {
        goto at_426b86;
    }
at_426a9c:
    r->edx = rd32(r, r->ebp - 0x24);
    r->ecx = rd32(r, r->ebp - 0x20);
    r->edx = r->edx + 0xd;
    r->ecx = r->ecx + 1;
    wr32(r, r->ebp - 0x24, r->edx);
    wr32(r, r->ebp - 0x20, r->ecx);
    if ((int32_t)r->ecx < (int32_t)0x5 && !r->port->env.failed)
    {
        goto at_426a8e;
    }
    if ((uint8_t)rd8(r, r->ebp - 0xc) != (uint8_t)0x0)
    {
        goto at_426b71;
    }
    r->ebx = 0xffffffffu;
    r->esi = rd32(r, r->ebp + 0x1c);
    r->edx = r->ebx;
    if (r->esi != 0x4)
    {
        goto at_426af4;
    }
    r->eax = 0;
at_426acc:
    set_low8(&r->ecx, rd8(r, r->eax + r->ebp - 0x64));
    if ((uint8_t)((r->ecx & 0xff)) == 0)
    {
        goto at_426aee;
    }
    r->esi = (r->ecx & 0xff);
    r->ecx = 0;
    set_low8(&r->ecx, rd8(r, r->eax + r->ebp - 0x6c));
    r->ecx = r->ecx + r->esi;
    r->esi = rd8(r, r->eax + r->ebp - 0x5c);
    r->ecx = r->ecx + r->esi;
    if ((int32_t)r->ecx <= (int32_t)r->edx)
    {
        goto at_426aee;
    }
    r->edx = r->ecx;
    r->ebx = r->eax;
at_426aee:
    r->eax = r->eax + 1;
    if ((int32_t)r->eax < (int32_t)0x5 && !r->port->env.failed)
    {
        goto at_426acc;
    }
at_426af4:
    if (r->ebx != 0xffffffffu)
    {
        goto at_426b23;
    }
    if (rd32(r, r->ebp + 0x1c) <= 0x2)
    {
        goto at_426b23;
    }
    r->eax = 0;
at_426b01:
    if ((uint8_t)rd8(r, r->eax + r->ebp - 0x6c) == (uint8_t)0x0)
    {
        goto at_426b1d;
    }
    r->ecx = 0;
    r->esi = rd8(r, r->eax + r->ebp - 0x5c);
    set_low8(&r->ecx, rd8(r, r->eax + r->ebp - 0x6c));
    r->ecx = r->ecx + r->esi;
    if ((int32_t)r->ecx <= (int32_t)r->edx)
    {
        goto at_426b1d;
    }
    r->edx = r->ecx;
    r->ebx = r->eax;
at_426b1d:
    r->eax = r->eax + 1;
    if ((int32_t)r->eax < (int32_t)0x5 && !r->port->env.failed)
    {
        goto at_426b01;
    }
at_426b23:
    if (r->ebx == 0xffffffffu)
    {
        goto at_427053;
    }
at_426b2c:
    r->eax = 0xffffffffu;
    r->ecx = 0x4;
    r->edx = 0;
at_426b38:
    r->ebx = 0;
    set_low8(&r->ebx, rd8(r, r->edx + r->ebp - 0x5c));
    if ((int32_t)r->ebx <= 0)
    {
        goto at_42707c;
    }
    r->eax = r->edx;
at_426b48:
    r->ecx = r->ecx - 1;
    r->edx = r->edx + 1;
    if (r->eax != 0xffffffffu)
    {
        goto at_426b54;
    }
    if ((int32_t)r->edx < (int32_t)0x2 && !r->port->env.failed)
    {
        goto at_426b38;
    }
at_426b54:
    if (r->eax != 0xffffffffu)
    {
        goto at_426b5e;
    }
    r->eax = 0x2;
at_426b5e:
    r->edx = rd32(r, r->ebp + 0xc);
    wr32(r, r->edx, r->eax);
    set_low8(&r->eax, rd8(r, r->eax + r->ebp - 0x4c));
    r->edx = rd32(r, r->ebp + 0x8);
    r->eax = r->eax & 0xff;
    wr32(r, r->edx, r->eax);
at_426b71:
    flags(r, F_SUB, rd8(r, r->ebp - 0xc), 0x0, 8);
    set_low8(&r->eax, cond(r, CC_E));
    r->eax = r->eax & 0xff;
    r->edi = rd32(r, r->ebp - 0x8);
    r->esi = rd32(r, r->ebp - 0x4);
    return;
at_426b86:
    r->ecx = 0x41;
    r->esi = rd32(r, r->ebp - 0x30);
    r->edi = r->ebp - 0xb0;
    r->edx = rd32(r, r->ebp - 0x24);
    push(r, r->edi);
    r->eax = r->ecx;
    r->ecx = r->ecx >> 0x2;
    rep_movs(r, 4);
    set_low8(&r->ecx, (r->eax & 0xff));
    set_low8(&r->ecx, (r->ecx & 0xff) & 0x3);
    rep_movs(r, 1);
    r->edi = pop(r);
    r->esi = 0xc;
    r->edx = r->edx + r->esi;
    wr32(r, r->ebp - 0x18, r->esi);
    set_low8(&r->ebx, rd8(r, r->edx + r->ebp - 0xb0));
    r->eax = r->edx;
    if ((uint8_t)((r->ebx & 0xff)) == (uint8_t)0xff)
    {
        goto at_426bd5;
    }
at_426bbf:
    r->edi = rd32(r, r->ebp - 0x18);
    r->edi = r->edi - 1;
    r->eax = r->eax - 1;
    wr32(r, r->ebp - 0x18, r->edi);
    if ((int32_t)r->edi < 0)
    {
        goto at_426bd5;
    }
    if ((uint8_t)rd8(r, r->eax + r->ebp - 0xb0) != (uint8_t)0xff && !r->port->env.failed)
    {
        goto at_426bbf;
    }
at_426bd5:
    r->ecx = rd32(r, r->ebp - 0x18);
    if ((int32_t)r->ecx <= (int32_t)0xffffffffu && !r->port->env.failed)
    {
        goto at_426a9c;
    }
    r->eax = rd32(r, r->ebp - 0x24);
    r->eax = r->eax + r->ecx;
    set_low8(&r->edx, rd8(r, r->ebp - 0x3c));
    wr8(r, r->eax + r->ebp - 0xb0, (r->edx & 0xff));
    if ((int32_t)r->ecx <= 0)
    {
        goto at_426bfe;
    }
    set_low8(&r->edx, rd8(r, r->ebp - 0x2c));
    wr8(r, r->eax + r->ebp - 0xb1, (r->edx & 0xff));
at_426bfe:
    r->edi = rd32(r, r->ebp - 0x18);
    if ((int32_t)r->edi <= (int32_t)0x1)
    {
        goto at_426c15;
    }
    r->eax = rd32(r, r->ebp - 0x24);
    r->eax = r->eax + r->edi;
    set_low8(&r->edx, rd8(r, r->ebp - 0x28));
    wr8(r, r->eax + r->ebp - 0xb2, (r->edx & 0xff));
at_426c15:
    r->eax = r->ebp - 0x1b4;
    r->ecx = r->ebp - 0x10;
    r->edx = r->ebp - 0x1b4;
    r->ebx = 0;
    call_keep(r, 0x432840);
    set_low8(&r->ebx, rd8(r, r->ebp + 0x10));
    r->eax = r->ebp - 0xb0;
    call_keep(r, 0x4346b0);
    if (r->eax != 0x1)
    {
        goto at_426c6f;
    }
    r->eax = r->ebp - 0x1b4;
    r->ecx = 0;
    r->edx = 0;
at_426c48:
    r->ebx = rd32(r, r->eax);
    r->eax = r->eax + 0x4;
    r->edx = r->edx + 1;
    r->ecx = r->ecx + r->ebx;
    if ((int32_t)r->edx < (int32_t)0x41 && !r->port->env.failed)
    {
        goto at_426c48;
    }
    r->edx = rd32(r, r->ebp - 0x20);
    r->eax = 0;
    set_low8(&r->eax, rd8(r, r->edx + r->ebp - 0x5c));
    if ((int32_t)r->ecx <= (int32_t)r->eax)
    {
        goto at_426c6f;
    }
    wr8(r, r->edx + r->ebp - 0x5c, (r->ecx & 0xff));
    set_low8(&r->ecx, 0);
    wr8(r, r->ebp - 0xc, (r->ecx & 0xff));
    wr8(r, r->edx + r->ebp - 0x4c, (r->ecx & 0xff));
at_426c6f:
    r->eax = rd32(r, r->ebp - 0x24);
    r->esi = rd32(r, r->ebp - 0x18);
    r->eax = r->eax + r->esi;
    set_low8(&r->edx, rd8(r, r->ebp - 0x28));
    wr8(r, r->eax + r->ebp - 0xb0, (r->edx & 0xff));
    if ((int32_t)r->esi <= 0)
    {
        goto at_426c8f;
    }
    set_low8(&r->edx, rd8(r, r->ebp - 0x3c));
    wr8(r, r->eax + r->ebp - 0xb1, (r->edx & 0xff));
at_426c8f:
    if ((int32_t)rd32(r, r->ebp - 0x18) <= (int32_t)0x1)
    {
        goto at_426ca5;
    }
    r->eax = rd32(r, r->ebp - 0x24);
    r->eax = r->eax + rd32(r, r->ebp - 0x18);
    set_low8(&r->edx, rd8(r, r->ebp - 0x2c));
    wr8(r, r->eax + r->ebp - 0xb2, (r->edx & 0xff));
at_426ca5:
    r->eax = r->ebp - 0x1b4;
    r->ecx = r->ebp - 0x10;
    r->edx = r->ebp - 0x1b4;
    r->ebx = 0;
    call_keep(r, 0x432840);
    set_low8(&r->ebx, rd8(r, r->ebp + 0x10));
    r->eax = r->ebp - 0xb0;
    call_keep(r, 0x4346b0);
    if (r->eax != 0x1)
    {
        goto at_426d02;
    }
    r->eax = r->ebp - 0x1b4;
    r->ecx = 0;
    r->edx = 0;
at_426cd8:
    r->ebx = rd32(r, r->eax);
    r->eax = r->eax + 0x4;
    r->edx = r->edx + 1;
    r->ecx = r->ecx + r->ebx;
    if ((int32_t)r->edx < (int32_t)0x41 && !r->port->env.failed)
    {
        goto at_426cd8;
    }
    r->edx = rd32(r, r->ebp - 0x20);
    r->eax = 0;
    set_low8(&r->eax, rd8(r, r->edx + r->ebp - 0x5c));
    if ((int32_t)r->ecx <= (int32_t)r->eax)
    {
        goto at_426d02;
    }
    r->eax = r->edx;
    wr8(r, r->edx + r->ebp - 0x5c, (r->ecx & 0xff));
    wr8(r, r->eax + r->ebp - 0x4c, 0x1);
    set_high8(&r->edx, 0);
    wr8(r, r->ebp - 0xc, ((r->edx >> 8) & 0xff));
at_426d02:
    r->eax = rd32(r, r->ebp - 0x24);
    r->esi = rd32(r, r->ebp - 0x18);
    r->eax = r->eax + r->esi;
    set_low8(&r->edx, rd8(r, r->ebp - 0x2c));
    wr8(r, r->eax + r->ebp - 0xb0, (r->edx & 0xff));
    if ((int32_t)r->esi <= 0)
    {
        goto at_426d22;
    }
    set_low8(&r->edx, rd8(r, r->ebp - 0x28));
    wr8(r, r->eax + r->ebp - 0xb1, (r->edx & 0xff));
at_426d22:
    if ((int32_t)rd32(r, r->ebp - 0x18) <= (int32_t)0x1)
    {
        goto at_426d38;
    }
    r->eax = rd32(r, r->ebp - 0x24);
    r->eax = r->eax + rd32(r, r->ebp - 0x18);
    set_low8(&r->edx, rd8(r, r->ebp - 0x3c));
    wr8(r, r->eax + r->ebp - 0xb2, (r->edx & 0xff));
at_426d38:
    r->eax = r->ebp - 0x1b4;
    r->ecx = r->ebp - 0x10;
    r->edx = r->ebp - 0x1b4;
    r->ebx = 0;
    call_keep(r, 0x432840);
    set_low8(&r->ebx, rd8(r, r->ebp + 0x10));
    r->eax = r->ebp - 0xb0;
    call_keep(r, 0x4346b0);
    if (r->eax != 0x1)
    {
        goto at_426d93;
    }
    r->eax = r->ebp - 0x1b4;
    r->ecx = 0;
    r->edx = 0;
at_426d6b:
    r->ebx = rd32(r, r->eax);
    r->eax = r->eax + 0x4;
    r->edx = r->edx + 1;
    r->ecx = r->ecx + r->ebx;
    if ((int32_t)r->edx < (int32_t)0x41 && !r->port->env.failed)
    {
        goto at_426d6b;
    }
    r->edx = rd32(r, r->ebp - 0x20);
    r->eax = 0;
    set_low8(&r->eax, rd8(r, r->edx + r->ebp - 0x5c));
    if ((int32_t)r->ecx <= (int32_t)r->eax)
    {
        goto at_426d93;
    }
    wr8(r, r->edx + r->ebp - 0x4c, 0x2);
    set_high8(&r->ebx, 0);
    wr8(r, r->edx + r->ebp - 0x5c, (r->ecx & 0xff));
    wr8(r, r->ebp - 0xc, ((r->ebx >> 8) & 0xff));
at_426d93:
    r->edx = rd32(r, r->ebp - 0x20);
    r->eax = 0;
    set_low8(&r->eax, rd8(r, r->edx + r->ebp - 0x5c));
    if ((int32_t)r->eax <= 0 && !r->port->env.failed)
    {
        goto at_426a9c;
    }
    if (rd32(r, r->ebp + 0x1c) <= 0x2 && !r->port->env.failed)
    {
        goto at_426a9c;
    }
    r->ecx = 0x41;
    r->esi = rd32(r, r->ebp - 0x34);
    r->edi = r->ebp - 0xb0;
    push(r, r->edi);
    r->eax = r->ecx;
    r->ecx = r->ecx >> 0x2;
    rep_movs(r, 4);
    set_low8(&r->ecx, (r->eax & 0xff));
    set_low8(&r->ecx, (r->ecx & 0xff) & 0x3);
    rep_movs(r, 1);
    r->edi = pop(r);
    r->eax = rd32(r, r->ebp - 0x24);
    r->edi = rd32(r, r->ebp - 0x18);
    set_low8(&r->ecx, rd8(r, r->edx + r->ebp - 0x4c));
    r->eax = r->eax + r->edi;
    if ((uint8_t)((r->ecx & 0xff)) == 0)
    {
        goto at_426fb5;
    }
    if ((uint8_t)((r->ecx & 0xff)) != (uint8_t)0x1)
    {
        goto at_427001;
    }
    set_low8(&r->edx, rd8(r, r->ebp - 0x28));
    wr8(r, r->eax + r->ebp - 0xb0, (r->edx & 0xff));
    if ((int32_t)r->edi <= 0)
    {
        goto at_426e01;
    }
    set_low8(&r->edx, rd8(r, r->ebp - 0x3c));
    wr8(r, r->eax + r->ebp - 0xb1, (r->edx & 0xff));
at_426e01:
    r->edi = rd32(r, r->ebp - 0x18);
    if ((int32_t)r->edi > (int32_t)0x1)
    {
        goto at_426fed;
    }
at_426e0d:
    r->eax = r->ebp - 0x1b4;
    r->ecx = r->ebp - 0x10;
    r->edx = r->ebp - 0x1b4;
    r->edi = 0x34;
    r->ebx = 0;
    call_keep(r, 0x432840);
    set_low8(&r->ebx, rd8(r, r->ebp + 0x10));
    r->eax = r->ebp - 0xb0;
    r->esi = 0;
    call_keep(r, 0x4346b0);
    wr32(r, r->ebp - 0x1c, r->esi);
at_426e3b:
    r->edx = rd32(r, r->ebp - 0x1c);
    r->ecx = r->edi;
    r->eax = r->esi * 0x34;
at_426e43:
    if (rd32(r, r->eax + r->ebp - 0x1b4) != 0x1)
    {
        goto at_426e55;
    }
    wr8(r, r->edx + r->ebp - 0xb0, 0xff);
at_426e55:
    r->eax = r->eax + 0x4;
    r->edx = r->edx + 1;
    if (r->eax != r->ecx && !r->port->env.failed)
    {
        goto at_426e43;
    }
    r->eax = rd32(r, r->ebp - 0x1c);
    r->edi = r->edi + 0x34;
    r->eax = r->eax + 0xd;
    r->esi = r->esi + 1;
    wr32(r, r->ebp - 0x1c, r->eax);
    if ((int32_t)r->esi < (int32_t)0x5 && !r->port->env.failed)
    {
        goto at_426e3b;
    }
    r->eax = r->ebp - 0xb0;
    r->ecx = r->ebp - 0x10;
    r->edx = r->ebp - 0x1b4;
    call_keep(r, 0x432980);
    r->ebx = 0;
    r->eax = r->ebp - 0x1b4;
    set_low8(&r->ebx, rd8(r, r->ebp + 0x10));
    call_keep(r, 0x432840);
    r->eax = r->ebp - 0xb0;
    call_keep(r, 0x4346b0);
    if (r->eax != 0x1 && !r->port->env.failed)
    {
        goto at_426a9c;
    }
    r->eax = r->ebp - 0x1b4;
    r->ecx = 0;
    r->edx = 0;
at_426eb1:
    r->ebx = rd32(r, r->eax);
    r->eax = r->eax + 0x4;
    r->edx = r->edx + 1;
    r->ecx = r->ecx + r->ebx;
    if ((int32_t)r->edx < (int32_t)0x41 && !r->port->env.failed)
    {
        goto at_426eb1;
    }
    r->eax = rd32(r, r->ebp - 0x20);
    r->esi = rd32(r, r->ebp + 0x1c);
    wr8(r, r->eax + r->ebp - 0x6c, (r->ecx & 0xff));
    if (r->esi != 0x4 && !r->port->env.failed)
    {
        goto at_426a9c;
    }
    r->edi = 0x34;
    r->esi = 0;
    wr32(r, r->ebp - 0x44, r->edi);
    r->edi = 0;
at_426edd:
    r->ecx = rd32(r, r->ebp - 0x44);
    r->edx = r->edi;
    r->eax = r->esi * 0x34;
at_426ee5:
    if (rd32(r, r->eax + r->ebp - 0x1b4) == 0x1)
    {
        goto at_427039;
    }
at_426ef3:
    r->eax = r->eax + 0x4;
    r->edx = r->edx + 1;
    if (r->eax != r->ecx && !r->port->env.failed)
    {
        goto at_426ee5;
    }
    r->eax = rd32(r, r->ebp - 0x44);
    r->edi = r->edi + 0xd;
    r->eax = r->eax + 0x34;
    r->esi = r->esi + 1;
    wr32(r, r->ebp - 0x44, r->eax);
    if ((int32_t)r->esi < (int32_t)0x5 && !r->port->env.failed)
    {
        goto at_426edd;
    }
    r->eax = r->ebp - 0xb0;
    call_keep(r, 0x432980);
    r->eax = r->ebp - 0x1b4;
    call_keep(r, 0x432840);
at_426f23:
    r->ecx = r->ebp - 0x10;
    r->edx = r->ebp - 0x1b4;
    r->ebx = 0;
    r->eax = r->ebp - 0xb0;
    set_low8(&r->ebx, rd8(r, r->ebp + 0x10));
    call_keep(r, 0x4346b0);
    if (r->eax != 0x1 && !r->port->env.failed)
    {
        goto at_426a9c;
    }
    r->edx = r->ebp - 0x1b4;
    r->ecx = 0;
    r->eax = 0;
at_426f4f:
    r->ebx = rd32(r, r->edx);
    r->edx = r->edx + 0x4;
    r->eax = r->eax + 1;
    r->ecx = r->ecx + r->ebx;
    if ((int32_t)r->eax < (int32_t)0x41 && !r->port->env.failed)
    {
        goto at_426f4f;
    }
    r->eax = rd32(r, r->ebp - 0x20);
    r->edi = 0x34;
    r->esi = 0;
    set_high8(&r->ecx, rd8(r, r->eax + r->ebp - 0x64));
    wr32(r, r->ebp - 0x14, r->edi);
    set_high8(&r->ecx, ((r->ecx >> 8) & 0xff) + (r->ecx & 0xff));
    r->edi = 0;
    wr8(r, r->eax + r->ebp - 0x64, ((r->ecx >> 8) & 0xff));
at_426f75:
    r->ecx = rd32(r, r->ebp - 0x14);
    r->edx = r->edi;
    r->eax = r->esi * 0x34;
at_426f7d:
    if (rd32(r, r->eax + r->ebp - 0x1b4) == 0x1)
    {
        goto at_427046;
    }
at_426f8b:
    r->eax = r->eax + 0x4;
    r->edx = r->edx + 1;
    if (r->eax != r->ecx && !r->port->env.failed)
    {
        goto at_426f7d;
    }
    r->eax = rd32(r, r->ebp - 0x14);
    r->edi = r->edi + 0xd;
    r->eax = r->eax + 0x34;
    r->esi = r->esi + 1;
    wr32(r, r->ebp - 0x14, r->eax);
    if ((int32_t)r->esi < (int32_t)0x5 && !r->port->env.failed)
    {
        goto at_426f75;
    }
    r->eax = r->ebp - 0xb0;
    call_keep(r, 0x432980);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_426f23;
at_426fb5:
    set_low8(&r->edx, rd8(r, r->ebp - 0x3c));
    wr8(r, r->eax + r->ebp - 0xb0, (r->edx & 0xff));
    if ((int32_t)r->edi <= 0)
    {
        goto at_426fcd;
    }
    set_low8(&r->edx, rd8(r, r->ebp - 0x2c));
    wr8(r, r->eax + r->ebp - 0xb1, (r->edx & 0xff));
at_426fcd:
    r->ebx = rd32(r, r->ebp - 0x18);
    if ((int32_t)r->ebx <= (int32_t)0x1 && !r->port->env.failed)
    {
        goto at_426e0d;
    }
    r->eax = rd32(r, r->ebp - 0x24);
    r->eax = r->eax + r->ebx;
    set_low8(&r->edx, rd8(r, r->ebp - 0x28));
    wr8(r, r->eax + r->ebp - 0xb2, (r->edx & 0xff));
    if (r->port->env.failed)
    {
        return;
    }
    goto at_426e0d;
at_426fed:
    r->eax = rd32(r, r->ebp - 0x24);
    r->eax = r->eax + r->edi;
    set_low8(&r->edx, rd8(r, r->ebp - 0x2c));
    wr8(r, r->eax + r->ebp - 0xb2, (r->edx & 0xff));
    if (r->port->env.failed)
    {
        return;
    }
    goto at_426e0d;
at_427001:
    set_low8(&r->edx, rd8(r, r->ebp - 0x2c));
    wr8(r, r->eax + r->ebp - 0xb0, (r->edx & 0xff));
    if ((int32_t)r->edi <= 0)
    {
        goto at_427019;
    }
    set_low8(&r->edx, rd8(r, r->ebp - 0x28));
    wr8(r, r->eax + r->ebp - 0xb1, (r->edx & 0xff));
at_427019:
    r->ecx = rd32(r, r->ebp - 0x18);
    if ((int32_t)r->ecx <= (int32_t)0x1 && !r->port->env.failed)
    {
        goto at_426e0d;
    }
    r->eax = rd32(r, r->ebp - 0x24);
    r->eax = r->eax + r->ecx;
    set_low8(&r->edx, rd8(r, r->ebp - 0x3c));
    wr8(r, r->eax + r->ebp - 0xb2, (r->edx & 0xff));
    if (r->port->env.failed)
    {
        return;
    }
    goto at_426e0d;
at_427039:
    wr8(r, r->edx + r->ebp - 0xb0, 0xff);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_426ef3;
at_427046:
    wr8(r, r->edx + r->ebp - 0xb0, 0xff);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_426f8b;
at_427053:
    if (rd32(r, r->ebp + 0x1c) <= 0x1 && !r->port->env.failed)
    {
        goto at_426b2c;
    }
    r->edx = 0x1;
    r->eax = 0;
at_427064:
    set_low8(&r->ebx, rd8(r, r->edx + r->ebp - 0x5c));
    if ((uint8_t)((r->ebx & 0xff)) <= (uint8_t)rd8(r, r->eax + r->ebp - 0x5c))
    {
        goto at_427070;
    }
    r->eax = r->edx;
at_427070:
    r->edx = r->edx + 1;
    if ((int32_t)r->edx >= (int32_t)0x5 && !r->port->env.failed)
    {
        goto at_426b5e;
    }
    if (r->port->env.failed)
    {
        return;
    }
    goto at_427064;
at_42707c:
    r->ebx = 0;
    set_low8(&r->ebx, rd8(r, r->ecx + r->ebp - 0x5c));
    if ((int32_t)r->ebx <= 0 && !r->port->env.failed)
    {
        goto at_426b48;
    }
    r->eax = r->ecx;
    if (r->port->env.failed)
    {
        return;
    }
    goto at_426b48;
}

uint32_t vertrix_port_ai_chain_search_4269e0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x1b8
    };
    Port port;
    uint8_t stack[BELOW + 8 + 4 * 6];
    Regs r;
    port_open_arguments(&port, stack, calls, services, globals, entry, BELOW, 6);
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
