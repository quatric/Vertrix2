#include "port_rtlmpeghuffmans.h"

/* Decodes a granule's Huffman-coded spectral values (big values through the table pairs, then the
 * count1 quadruples), reading bits through 0x404610 and 0x4046e0. */

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

/* Original 0x407830: Decodes a granule's Huffman-coded spectral values (big values through the
 * table pairs, then the count1 quadruples), reading bits through 0x404610 and 0x4046e0. Evidence:
 * calls 0x404610, 0x4046e0, 0x4eb5b4, 0x4d8177. Register-for-register from the listing
 * (0x40783b..0x40838f); labels are the original addresses. */
static void run(Regs *r)
{
    wr32(r, r->ebp - 0x90, r->eax);
    wr32(r, r->ebp - 0x8c, r->edx);
    wr32(r, r->ebp - 0x88, r->ebx);
    wr32(r, r->ebp - 0x84, r->ecx);
    r->eax = rd32(r, r->ebx + 0x50);
    r->eax = r->eax + 1;
    wr32(r, r->ebp - 0x80, r->eax);
    r->ebx = rd32(r, r->ebp - 0x90);
    r->esi = rd32(r, r->ebp - 0x88);
    r->esi = rd32(r, r->esi + 0x4);
    r->esi = r->esi - rd32(r, r->ebp + 0x8);
    r->eax = rd32(r, r->ebp - 0x88);
    r->eax = rd32(r, r->eax + 0x8);
    r->edx = rd32(r, r->ebp - 0x88);
    r->edx = rd32(r, r->edx + 0x44);
    r->ecx = rd32(r, r->ebp - 0x88);
    r->ecx = rd32(r, r->ecx + 0x48);
    r->edi = 0x120;
    r->edi = r->edi - r->eax;
    r->edi = (uint32_t)((int32_t)r->edi >> 0x1);
    wr32(r, r->ebp - 0x7c, r->edi);
    if ((int32_t)r->eax <= (int32_t)r->edx)
    {
        goto at_407ab2;
    }
    wr32(r, r->ebp - 0x9c, r->edx);
    if ((int32_t)r->eax > (int32_t)r->ecx)
    {
        goto at_407acb;
    }
    r->eax = r->eax - r->edx;
    wr32(r, r->ebp - 0x98, r->eax);
    r->ecx = 0;
    wr32(r, r->ebp - 0x94, r->ecx);
at_4078b9:
    r->eax = rd32(r, r->ebp - 0x88);
    if (rd32(r, r->eax + 0x10) != 0x2)
    {
        goto at_407f2e;
    }
    r->edi = 0;
    wr32(r, r->ebp - 0x70, r->edi);
    wr32(r, r->ebp - 0x6c, r->edi);
    wr32(r, r->ebp - 0x68, r->edi);
    wr32(r, r->ebp - 0x64, r->edi);
    r->edx = rd32(r, r->ebp - 0x84);
    r->eax = r->edx * 4;
    r->eax = r->eax - r->edx;
    r->eax = r->eax << 0x2;
    r->edx = rd32(r, r->ebp - 0x88);
    if (rd32(r, r->edx + 0x14) == 0x0)
    {
        goto at_407ae2;
    }
    wr32(r, r->ebp - 0xa0, 0xffffffffu);
    r->edi = 0x2;
    wr32(r, r->ebp - 0xa4, r->edi);
    wr32(r, r->ebp - 0xa8, r->edi);
    wr32(r, r->ebp - 0xac, r->edi);
    r->edx = rd32(r, r->eax + 0x524208);
    wr32(r, r->ebp - 0x60, r->edx);
    r->eax = rd32(r, r->eax + 0x523e60);
at_407929:
    wr32(r, r->ebp - 0x78, r->eax);
    r->edi = 0;
    wr32(r, r->ebp - 0x5c, r->edi);
    wr32(r, r->ebp - 0x74, r->edi);
    r->eax = rd32(r, r->ebp - 0x88);
    wr32(r, r->ebp - 0x20, r->eax);
at_40793d:
    r->eax = rd32(r, r->ebp - 0x74);
    r->eax = rd32(r, r->ebp + r->eax * 4 - 0x9c);
    wr32(r, r->ebp - 0x58, r->eax);
    r->eax = rd32(r, r->ebp - 0x20);
    r->eax = rd32(r, r->eax + 0x18);
    r->eax = r->eax << 0x3;
    r->edx = 0x4f5808;
    r->edx = r->edx + r->eax;
    wr32(r, r->ebp - 0x54, r->edx);
    if (rd32(r, r->ebp - 0x58) == 0x0)
    {
        goto at_407a59;
    }
at_407967:
    if (rd32(r, r->ebp - 0x5c) == 0x0)
    {
        goto at_407b13;
    }
at_407971:
    r->edx = rd32(r, r->ebp - 0x54);
    r->edx = rd32(r, r->edx + 0x4);
at_407977:
    r->ecx = (uint32_t)(int32_t)(int16_t)rd16(r, r->edx);
    r->edx = r->edx + 0x2;
    if ((int32_t)r->ecx < 0)
    {
        goto at_407bcc;
    }
    r->edx = r->ecx;
    r->edx = (uint32_t)((int32_t)r->edx >> 0x4);
    r->ecx = r->ecx & 0xf;
    r->eax = rd32(r, r->ebp - 0x6c);
    r->eax = r->eax << 0x2;
    if (r->edx != 0xf)
    {
        goto at_407bf0;
    }
    r->edi = rd32(r, r->ebp - 0x68);
    wr32(r, r->eax + r->ebp - 0xac, r->edi);
    r->eax = rd32(r, r->ebp - 0x54);
    r->eax = rd32(r, r->eax);
    r->eax = r->eax + 1;
    r->esi = r->esi - r->eax;
    r->eax = rd32(r, r->ebp - 0x54);
    r->eax = rd32(r, r->eax);
    call_keep(r, 0x404610);
    r->edx = r->edx + r->eax;
    call_keep(r, 0x4046e0);
    r->edx = r->edx << 0x2;
    if (r->eax == 0)
    {
        goto at_407be5;
    }
    r->eax = rd32(r, r->edx + 0x524288);
    call_keep(r, 0x4eb5b4);
at_4079d5:
    r->edx = rd32(r, r->ebp - 0x64);
    call_keep(r, 0x4d8177);
    wr32(r, r->ebx, r->eax);
at_4079df:
    r->eax = rd32(r, r->ebp - 0x70);
    r->eax = r->eax << 0x2;
    r->ebx = r->ebx + r->eax;
    r->eax = rd32(r, r->ebp - 0x6c);
    r->eax = r->eax << 0x2;
    if (r->ecx != 0xf)
    {
        goto at_407c3f;
    }
    r->edx = rd32(r, r->ebp - 0x68);
    wr32(r, r->eax + r->ebp - 0xac, r->edx);
    r->eax = rd32(r, r->ebp - 0x54);
    r->eax = rd32(r, r->eax);
    r->eax = r->eax + 1;
    r->esi = r->esi - r->eax;
    r->eax = rd32(r, r->ebp - 0x54);
    r->eax = rd32(r, r->eax);
    call_keep(r, 0x404610);
    r->ecx = r->ecx + r->eax;
    call_keep(r, 0x4046e0);
    r->edx = r->eax;
    r->eax = r->ecx * 4;
    if (r->edx == 0)
    {
        goto at_407c34;
    }
    r->eax = rd32(r, r->eax + 0x524288);
    call_keep(r, 0x4eb5b4);
at_407a35:
    r->edx = rd32(r, r->ebp - 0x64);
    call_keep(r, 0x4d8177);
    wr32(r, r->ebx, r->eax);
at_407a3f:
    r->eax = rd32(r, r->ebp - 0x70);
    r->eax = r->eax << 0x2;
    r->ebx = r->ebx + r->eax;
    r->edi = rd32(r, r->ebp - 0x58);
    r->edi = r->edi - 1;
    wr32(r, r->ebp - 0x58, r->edi);
    wr32(r, r->ebp - 0x5c, rd32(r, r->ebp - 0x5c) - 1);
    if (r->edi != 0 && !r->port->env.failed)
    {
        goto at_407967;
    }
at_407a59:
    wr32(r, r->ebp - 0x20, rd32(r, r->ebp - 0x20) + 0x4);
    r->edi = rd32(r, r->ebp - 0x74);
    r->edi = r->edi + 1;
    wr32(r, r->ebp - 0x74, r->edi);
    if ((int32_t)r->edi < (int32_t)0x2 && !r->port->env.failed)
    {
        goto at_40793d;
    }
at_407a6d:
    if (rd32(r, r->ebp - 0x7c) != 0x0)
    {
        goto at_407c87;
    }
at_407a77:
    r->ecx = 0x3;
    r->edx = 0x4;
at_407a81:
    r->eax = rd32(r, r->ebp - 0x60);
    if (r->eax >= rd32(r, r->ebp - 0x78))
    {
        goto at_407e77;
    }
    if (rd32(r, r->ebp - 0x5c) == 0x0)
    {
        goto at_407e34;
    }
at_407a97:
    wr32(r, r->ebx, 0x0);
    r->eax = rd32(r, r->ebp - 0x70);
    r->eax = r->eax << 0x2;
    wr32(r, r->ebp - 0x5c, rd32(r, r->ebp - 0x5c) - 1);
    r->ebx = r->ebx + r->eax;
    wr32(r, r->ebx, 0x0);
    r->ebx = r->ebx + r->eax;
    if (r->port->env.failed)
    {
        return;
    }
    goto at_407a81;
at_407ab2:
    wr32(r, r->ebp - 0x9c, r->eax);
    r->edi = 0;
    wr32(r, r->ebp - 0x98, r->edi);
    wr32(r, r->ebp - 0x94, r->edi);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4078b9;
at_407acb:
    r->edi = r->ecx;
    r->edi = r->edi - r->edx;
    wr32(r, r->ebp - 0x98, r->edi);
    r->eax = r->eax - r->ecx;
    wr32(r, r->ebp - 0x94, r->eax);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4078b9;
at_407ae2:
    r->edx = 0xffffffffu;
    wr32(r, r->ebp - 0xa0, r->edx);
    wr32(r, r->ebp - 0xa4, r->edx);
    wr32(r, r->ebp - 0xa8, r->edx);
    wr32(r, r->ebp - 0xac, r->edx);
    r->edx = rd32(r, r->eax + 0x52420c);
    wr32(r, r->ebp - 0x60, r->edx);
    r->eax = rd32(r, r->eax + 0x523e64);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_407929;
at_407b13:
    r->eax = rd32(r, r->ebp - 0x60);
    r->eax = rd32(r, r->eax);
    wr32(r, r->ebp - 0x5c, r->eax);
    r->ecx = rd32(r, r->ebp - 0x60);
    r->ecx = r->ecx + 0x4;
    wr32(r, r->ebp - 0x60, r->ecx);
    r->ebx = rd32(r, r->ecx);
    r->ebx = r->ebx << 0x2;
    r->edi = r->ecx + 0x4;
    wr32(r, r->ebp - 0x60, r->edi);
    r->ebx = r->ebx + rd32(r, r->ebp - 0x90);
    r->eax = rd32(r, r->edi);
    wr32(r, r->ebp - 0x6c, r->eax);
    r->edx = r->edi + 0x4;
    wr32(r, r->ebp - 0x60, r->edx);
    r->eax = rd32(r, r->edx);
    wr32(r, r->ebp - 0x68, r->eax);
    r->ecx = r->edx + 0x4;
    wr32(r, r->ebp - 0x60, r->ecx);
    r->eax = rd32(r, r->ebp - 0x8c);
    r->eax = r->eax + 0x4;
    r->edi = rd32(r, r->ebp - 0x6c);
    if (r->edi != 0x3)
    {
        goto at_407b93;
    }
    set_low8(&r->ecx, rd8(r, r->ebp - 0x80));
    r->edx = rd32(r, r->ebp - 0x8c);
    r->edx = rd32(r, r->edx);
    r->edx = r->edx << (r->ecx & 0xff);
    r->ecx = r->edx * 4;
    r->edx = rd32(r, r->ebp - 0x88);
    r->edx = rd32(r, r->edx + 0x64);
    wr32(r, r->ebp - 0x8c, r->eax);
    r->eax = r->edx + r->ecx;
    r->eax = rd32(r, r->eax);
    wr32(r, r->ebp - 0x64, r->eax);
    wr32(r, r->ebp - 0x70, 0x1);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_407971;
at_407b93:
    r->edx = r->edi * 4;
    r->edi = rd32(r, r->ebp - 0x88);
    r->edi = r->edi + r->edx;
    set_low8(&r->ecx, rd8(r, r->ebp - 0x80));
    r->edx = rd32(r, r->ebp - 0x8c);
    r->edx = rd32(r, r->edx);
    r->edx = r->edx << (r->ecx & 0xff);
    r->ecx = r->edx;
    r->edx = rd32(r, r->edi + 0x58);
    wr32(r, r->ebp - 0x8c, r->eax);
    r->eax = rd32(r, r->edx + r->ecx * 4);
    wr32(r, r->ebp - 0x64, r->eax);
    wr32(r, r->ebp - 0x70, 0x3);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_407971;
at_407bcc:
    call_keep(r, 0x4046e0);
    if (r->eax != 0)
    {
        goto at_407bdb;
    }
    r->esi = r->esi - 1;
    if (r->port->env.failed)
    {
        return;
    }
    goto at_407977;
at_407bdb:
    r->ecx = r->ecx + r->ecx;
    r->edx = r->edx - r->ecx;
    r->esi = r->esi - 1;
    if (r->port->env.failed)
    {
        return;
    }
    goto at_407977;
at_407be5:
    r->eax = rd32(r, r->edx + 0x524288);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4079d5;
at_407bf0:
    if (r->edx == 0)
    {
        goto at_407c2d;
    }
    r->edi = rd32(r, r->ebp - 0x68);
    wr32(r, r->eax + r->ebp - 0xac, r->edi);
    call_keep(r, 0x4046e0);
    r->edx = r->edx << 0x2;
    if (r->eax == 0)
    {
        goto at_407c25;
    }
    r->eax = rd32(r, r->edx + 0x524288);
    call_keep(r, 0x4eb5b4);
at_407c15:
    r->edx = rd32(r, r->ebp - 0x64);
    call_keep(r, 0x4d8177);
    wr32(r, r->ebx, r->eax);
    r->esi = r->esi - 1;
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4079df;
at_407c25:
    r->eax = rd32(r, r->edx + 0x524288);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_407c15;
at_407c2d:
    wr32(r, r->ebx, r->edx);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4079df;
at_407c34:
    r->eax = rd32(r, r->eax + 0x524288);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_407a35;
at_407c3f:
    if (r->ecx == 0)
    {
        goto at_407c80;
    }
    r->edx = rd32(r, r->ebp - 0x68);
    wr32(r, r->eax + r->ebp - 0xac, r->edx);
    call_keep(r, 0x4046e0);
    r->edx = r->ecx * 4;
    if (r->eax == 0)
    {
        goto at_407c78;
    }
    r->eax = rd32(r, r->edx + 0x524288);
    call_keep(r, 0x4eb5b4);
at_407c68:
    r->edx = rd32(r, r->ebp - 0x64);
    call_keep(r, 0x4d8177);
    wr32(r, r->ebx, r->eax);
    r->esi = r->esi - 1;
    if (r->port->env.failed)
    {
        return;
    }
    goto at_407a3f;
at_407c78:
    r->eax = rd32(r, r->edx + 0x524288);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_407c68;
at_407c80:
    wr32(r, r->ebx, r->ecx);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_407a3f;
at_407c87:
    if ((int32_t)r->esi <= 0 && !r->port->env.failed)
    {
        goto at_407a77;
    }
    r->edx = rd32(r, r->ebp - 0x88);
    r->edx = rd32(r, r->edx + 0x54);
    r->edx = r->edx << 0x3;
    r->edx = r->edx + 0x4f5908;
    r->edx = rd32(r, r->edx + 0x4);
    r->ecx = 0;
at_407ca6:
    set_low16(&r->eax, rd16(r, r->edx));
    wr16(r, r->ebp - 0x10, (r->eax & 0xffff));
    r->edx = r->edx + 0x2;
    if ((int16_t)((r->ecx & 0xffff)) > (int16_t)((r->eax & 0xffff)))
    {
        goto at_407d25;
    }
at_407cb5:
    r->edx = 0;
at_407cb7:
    if (rd32(r, r->ebp - 0x5c) == 0x0)
    {
        goto at_407d60;
    }
at_407cc1:
    wr32(r, r->ebp - 0x5c, rd32(r, r->ebp - 0x5c) - 1);
    r->eax = rd32(r, r->ebp - 0x70);
    r->eax = r->eax << 0x2;
    wr32(r, r->ebp - 0x50, r->eax);
    r->edi = rd32(r, r->ebp - 0x6c);
    r->edi = r->edi << 0x2;
at_407cd3:
    set_low8(&r->ecx, (r->edx & 0xff));
    r->eax = 0x8;
    r->eax = (uint32_t)((int32_t)r->eax >> (r->ecx & 0xff));
    r->ecx = rd32(r, r->ebp - 0x12);
    r->ecx = (uint32_t)((int32_t)r->ecx >> 0x10);
    if ((r->ecx & r->eax) == 0)
    {
        goto at_407e29;
    }
    r->eax = rd32(r, r->ebp - 0x68);
    wr32(r, r->edi + r->ebp - 0xac, r->eax);
    r->esi = r->esi - 1;
    if ((int32_t)r->esi < 0)
    {
        goto at_407e18;
    }
    call_keep(r, 0x4046e0);
    if (r->eax == 0)
    {
        goto at_407e21;
    }
    r->eax = rd32(r, r->ebp - 0x64);
    call_keep(r, 0x4eb5b4);
at_407d12:
    wr32(r, r->ebx, r->eax);
at_407d14:
    r->ebx = r->ebx + rd32(r, r->ebp - 0x50);
    r->edx = r->edx + 1;
    if ((int32_t)r->edx < (int32_t)0x4)
    {
        goto at_407d52;
    }
    wr32(r, r->ebp - 0x7c, rd32(r, r->ebp - 0x7c) - 1);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_407a6d;
at_407d25:
    r->esi = r->esi - 1;
    if ((int32_t)r->esi < 0)
    {
        goto at_407d46;
    }
    call_keep(r, 0x4046e0);
    if (r->eax == 0 && !r->port->env.failed)
    {
        goto at_407ca6;
    }
    r->eax = rd32(r, r->ebp - 0x12);
    r->eax = (uint32_t)((int32_t)r->eax >> 0x10);
    r->eax = r->eax + r->eax;
    r->edx = r->edx - r->eax;
    if (r->port->env.failed)
    {
        return;
    }
    goto at_407ca6;
at_407d46:
    r->eax = 0;
    wr16(r, r->ebp - 0x10, (r->eax & 0xffff));
    r->esi = r->esi + 1;
    if (r->port->env.failed)
    {
        return;
    }
    goto at_407cb5;
at_407d52:
    if ((uint8_t)((r->edx & 0xff) & 0x1) == 0 && !r->port->env.failed)
    {
        goto at_407cb7;
    }
    if (r->port->env.failed)
    {
        return;
    }
    goto at_407cd3;
at_407d60:
    r->eax = rd32(r, r->ebp - 0x60);
    r->eax = rd32(r, r->eax);
    wr32(r, r->ebp - 0x5c, r->eax);
    r->ecx = rd32(r, r->ebp - 0x60);
    r->ecx = r->ecx + 0x4;
    wr32(r, r->ebp - 0x60, r->ecx);
    r->ebx = rd32(r, r->ecx);
    r->ebx = r->ebx << 0x2;
    r->edi = r->ecx + 0x4;
    wr32(r, r->ebp - 0x60, r->edi);
    r->ebx = r->ebx + rd32(r, r->ebp - 0x90);
    r->eax = rd32(r, r->edi);
    wr32(r, r->ebp - 0x6c, r->eax);
    r->ecx = r->edi + 0x4;
    wr32(r, r->ebp - 0x60, r->ecx);
    r->eax = rd32(r, r->ecx);
    wr32(r, r->ebp - 0x68, r->eax);
    r->edi = r->ecx + 0x4;
    wr32(r, r->ebp - 0x60, r->edi);
    r->eax = rd32(r, r->ebp - 0x8c);
    r->eax = r->eax + 0x4;
    wr32(r, r->ebp - 0x14, r->eax);
    r->eax = rd32(r, r->ebp - 0x6c);
    if (r->eax != 0x3)
    {
        goto at_407ddf;
    }
    set_low8(&r->ecx, rd8(r, r->ebp - 0x80));
    r->eax = rd32(r, r->ebp - 0x8c);
    r->eax = rd32(r, r->eax);
    r->eax = r->eax << (r->ecx & 0xff);
    r->ecx = r->eax;
    r->eax = rd32(r, r->ebp - 0x88);
    r->eax = rd32(r, r->eax + 0x64);
    r->edi = rd32(r, r->ebp - 0x14);
    wr32(r, r->ebp - 0x8c, r->edi);
    r->eax = rd32(r, r->eax + r->ecx * 4);
    wr32(r, r->ebp - 0x64, r->eax);
    wr32(r, r->ebp - 0x70, 0x1);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_407cc1;
at_407ddf:
    r->eax = r->eax << 0x2;
    r->edi = rd32(r, r->ebp - 0x88);
    r->edi = r->edi + r->eax;
    set_low8(&r->ecx, rd8(r, r->ebp - 0x80));
    r->eax = rd32(r, r->ebp - 0x8c);
    r->eax = rd32(r, r->eax);
    r->eax = r->eax << (r->ecx & 0xff);
    r->eax = r->eax << 0x2;
    r->ecx = rd32(r, r->edi + 0x58);
    r->edi = rd32(r, r->ebp - 0x14);
    wr32(r, r->ebp - 0x8c, r->edi);
    r->eax = rd32(r, r->ecx + r->eax);
    wr32(r, r->ebp - 0x64, r->eax);
    wr32(r, r->ebp - 0x70, 0x3);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_407cc1;
at_407e18:
    r->esi = r->esi + 1;
    wr32(r, r->ebp - 0x7c, rd32(r, r->ebp - 0x7c) - 1);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_407a6d;
at_407e21:
    r->eax = rd32(r, r->ebp - 0x64);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_407d12;
at_407e29:
    wr32(r, r->ebx, 0x0);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_407d14;
at_407e34:
    r->eax = rd32(r, r->eax);
    wr32(r, r->ebp - 0x5c, r->eax);
    r->eax = rd32(r, r->ebp - 0x60);
    r->eax = r->eax + r->edx;
    wr32(r, r->ebp - 0x60, r->eax);
    r->ebx = rd32(r, r->eax);
    r->ebx = r->ebx << 0x2;
    r->edi = r->eax + r->edx;
    wr32(r, r->ebp - 0x60, r->edi);
    r->ebx = r->ebx + rd32(r, r->ebp - 0x90);
    r->eax = r->edi;
    r->edi = r->edi + r->edx;
    wr32(r, r->ebp - 0x60, r->edi);
    if (r->ecx != rd32(r, r->eax))
    {
        goto at_407e6c;
    }
    wr32(r, r->ebp - 0x70, 0x1);
    wr32(r, r->ebp - 0x60, rd32(r, r->ebp - 0x60) + r->edx);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_407a97;
at_407e6c:
    wr32(r, r->ebp - 0x70, r->ecx);
    wr32(r, r->ebp - 0x60, rd32(r, r->ebp - 0x60) + r->edx);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_407a97;
at_407e77:
    r->eax = rd32(r, r->ebp - 0xac);
    r->eax = r->eax + 1;
    r->edx = rd32(r, r->ebp - 0x88);
    wr32(r, r->edx + 0x30, r->eax);
    r->eax = rd32(r, r->ebp - 0xa8);
    r->eax = r->eax + 1;
    wr32(r, r->edx + 0x34, r->eax);
    r->eax = rd32(r, r->ebp - 0xa4);
    r->eax = r->eax + 1;
    wr32(r, r->edx + 0x38, r->eax);
    r->eax = rd32(r, r->ebp - 0xa0);
    r->eax = r->eax + 1;
    wr32(r, r->edx + 0x3c, r->eax);
    r->eax = rd32(r, r->ebp - 0xac);
    r->edx = rd32(r, r->ebp - 0xa8);
    if ((int32_t)r->eax <= (int32_t)r->edx)
    {
        goto at_407f00;
    }
at_407eb5:
    r->ecx = rd32(r, r->ebp - 0xa4);
    if ((int32_t)r->eax <= (int32_t)r->ecx)
    {
        goto at_407f04;
    }
at_407ebf:
    r->ecx = r->eax + 0x1;
    if (r->ecx == 0)
    {
        goto at_407f08;
    }
    r->eax = rd32(r, r->ebp - 0x84);
    r->eax = r->eax << 0x3;
    r->edx = r->eax;
    r->eax = r->eax << 0x3;
    r->eax = r->eax - r->edx;
    r->eax = rd32(r, r->eax + r->ecx * 4 + 0x522da0);
at_407edd:
    r->edx = rd32(r, r->ebp - 0x88);
    wr32(r, r->edx + 0x40, r->eax);
    r->edx = 0x10;
at_407eeb:
    if ((int32_t)r->esi <= (int32_t)0x10)
    {
        goto at_40836c;
    }
    r->eax = r->edx;
    call_keep(r, 0x404610);
    r->esi = r->esi - 0x10;
    if (r->port->env.failed)
    {
        return;
    }
    goto at_407eeb;
at_407f00:
    r->eax = r->edx;
    if (r->port->env.failed)
    {
        return;
    }
    goto at_407eb5;
at_407f04:
    r->eax = r->ecx;
    if (r->port->env.failed)
    {
        return;
    }
    goto at_407ebf;
at_407f08:
    r->ecx = rd32(r, r->ebp - 0xa0);
    r->edx = rd32(r, r->ebp - 0x84);
    r->eax = r->edx * 4;
    r->eax = r->eax - r->edx;
    r->eax = r->eax << 0x3;
    r->eax = r->eax - r->edx;
    r->eax = r->eax << 0x2;
    r->eax = rd32(r, r->eax + r->ecx * 4 + 0x523ed0);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_407edd;
at_407f2e:
    if (rd32(r, r->eax + 0x4c) == 0x0)
    {
        goto at_408141;
    }
    r->eax = 0x4f5ee0;
at_407f3d:
    wr32(r, r->ebp - 0x4c, r->eax);
    wr32(r, r->ebp - 0x44, 0xffffffffu);
    r->eax = 0;
    wr32(r, r->ebp - 0x40, r->eax);
    r->edx = rd32(r, r->ebp - 0x84);
    r->eax = r->edx * 4;
    r->eax = r->eax - r->edx;
    r->eax = rd32(r, r->eax * 4 + 0x524210);
    wr32(r, r->ebp - 0x3c, r->eax);
    r->edi = 0;
    wr32(r, r->ebp - 0x38, r->edi);
    wr32(r, r->ebp - 0x48, r->edi);
    r->eax = rd32(r, r->ebp - 0x88);
    wr32(r, r->ebp - 0x24, r->eax);
at_407f76:
    r->eax = rd32(r, r->ebp - 0x48);
    r->eax = rd32(r, r->ebp + r->eax * 4 - 0x9c);
    wr32(r, r->ebp - 0x34, r->eax);
    r->eax = rd32(r, r->ebp - 0x24);
    r->eax = rd32(r, r->eax + 0x18);
    r->eax = r->eax << 0x3;
    r->edx = 0x4f5808;
    r->edx = r->edx + r->eax;
    wr32(r, r->ebp - 0x30, r->edx);
    if (rd32(r, r->ebp - 0x34) == 0x0)
    {
        goto at_40808c;
    }
at_407fa0:
    if (rd32(r, r->ebp - 0x38) == 0x0)
    {
        goto at_40814b;
    }
at_407faa:
    r->edx = rd32(r, r->ebp - 0x30);
    r->edx = rd32(r, r->edx + 0x4);
at_407fb0:
    r->ecx = (uint32_t)(int32_t)(int16_t)rd16(r, r->edx);
    r->edx = r->edx + 0x2;
    if ((int32_t)r->ecx < 0)
    {
        goto at_408195;
    }
    r->eax = r->ecx;
    r->eax = (uint32_t)((int32_t)r->eax >> 0x4);
    wr32(r, r->ebp - 0x2c, r->eax);
    r->ecx = r->ecx & 0xf;
    r->eax = r->ebx + 0x4;
    wr32(r, r->ebp - 0x1c, r->eax);
    r->edx = rd32(r, r->ebp - 0x2c);
    if (r->edx != 0xf)
    {
        goto at_4081b9;
    }
    r->eax = rd32(r, r->ebp - 0x40);
    wr32(r, r->ebp - 0x44, r->eax);
    r->eax = rd32(r, r->ebp - 0x30);
    r->eax = rd32(r, r->eax);
    r->eax = r->eax + 1;
    r->esi = r->esi - r->eax;
    r->eax = rd32(r, r->ebp - 0x30);
    r->eax = rd32(r, r->eax);
    call_keep(r, 0x404610);
    r->edx = r->edx + r->eax;
    wr32(r, r->ebp - 0x2c, r->edx);
    call_keep(r, 0x4046e0);
    r->edx = r->eax;
    r->eax = rd32(r, r->ebp - 0x2c);
    r->eax = r->eax << 0x2;
    if (r->edx == 0)
    {
        goto at_4081ae;
    }
    r->eax = rd32(r, r->eax + 0x524288);
    call_keep(r, 0x4eb5b4);
at_408018:
    r->edx = r->edi;
    call_keep(r, 0x4d8177);
    wr32(r, r->ebx, r->eax);
    r->ebx = rd32(r, r->ebp - 0x1c);
at_408024:
    r->eax = r->ebx + 0x4;
    wr32(r, r->ebp - 0x18, r->eax);
    if (r->ecx != 0xf)
    {
        goto at_40820d;
    }
    r->eax = rd32(r, r->ebp - 0x40);
    wr32(r, r->ebp - 0x44, r->eax);
    r->eax = rd32(r, r->ebp - 0x30);
    r->eax = rd32(r, r->eax);
    r->eax = r->eax + 1;
    r->esi = r->esi - r->eax;
    r->eax = rd32(r, r->ebp - 0x30);
    r->eax = rd32(r, r->eax);
    call_keep(r, 0x404610);
    r->ecx = r->ecx + r->eax;
    call_keep(r, 0x4046e0);
    r->edx = r->eax;
    r->eax = r->ecx * 4;
    if (r->edx == 0)
    {
        goto at_408202;
    }
    r->eax = rd32(r, r->eax + 0x524288);
    call_keep(r, 0x4eb5b4);
at_40806e:
    r->edx = r->edi;
    call_keep(r, 0x4d8177);
    wr32(r, r->ebx, r->eax);
    r->ebx = rd32(r, r->ebp - 0x18);
at_40807a:
    r->ecx = rd32(r, r->ebp - 0x34);
    r->ecx = r->ecx - 1;
    wr32(r, r->ebp - 0x34, r->ecx);
    wr32(r, r->ebp - 0x38, rd32(r, r->ebp - 0x38) - 1);
    if (r->ecx != 0 && !r->port->env.failed)
    {
        goto at_407fa0;
    }
at_40808c:
    wr32(r, r->ebp - 0x24, rd32(r, r->ebp - 0x24) + 0x4);
    r->eax = rd32(r, r->ebp - 0x48);
    r->eax = r->eax + 1;
    wr32(r, r->ebp - 0x48, r->eax);
    if ((int32_t)r->eax < (int32_t)0x3 && !r->port->env.failed)
    {
        goto at_407f76;
    }
at_4080a0:
    if (rd32(r, r->ebp - 0x7c) == 0x0)
    {
        goto at_408316;
    }
    if ((int32_t)r->esi <= 0)
    {
        goto at_408316;
    }
    r->eax = rd32(r, r->ebp - 0x88);
    r->eax = rd32(r, r->eax + 0x54);
    r->eax = r->eax << 0x3;
    r->eax = r->eax + 0x4f5908;
    r->edx = rd32(r, r->eax + 0x4);
    r->ecx = 0;
at_4080c8:
    set_low16(&r->eax, rd16(r, r->edx));
    wr16(r, r->ebp - 0xc, (r->eax & 0xffff));
    r->edx = r->edx + 0x2;
    if ((int16_t)((r->ecx & 0xffff)) > (int16_t)((r->eax & 0xffff)))
    {
        goto at_408251;
    }
at_4080db:
    r->edx = 0;
at_4080dd:
    if (rd32(r, r->ebp - 0x38) == 0x0)
    {
        goto at_40828c;
    }
at_4080e7:
    wr32(r, r->ebp - 0x38, rd32(r, r->ebp - 0x38) - 1);
at_4080ea:
    set_low8(&r->ecx, (r->edx & 0xff));
    r->eax = 0x8;
    r->eax = (uint32_t)((int32_t)r->eax >> (r->ecx & 0xff));
    wr32(r, r->ebp - 0x28, r->eax);
    r->eax = rd32(r, r->ebp - 0xe);
    r->eax = (uint32_t)((int32_t)r->eax >> 0x10);
    r->ecx = r->ebx + 0x4;
    if ((rd32(r, r->ebp - 0x28) & r->eax) == 0)
    {
        goto at_4082fc;
    }
    r->eax = rd32(r, r->ebp - 0x40);
    wr32(r, r->ebp - 0x44, r->eax);
    r->esi = r->esi - 1;
    if ((int32_t)r->esi < 0)
    {
        goto at_4082e1;
    }
    call_keep(r, 0x4046e0);
    if (r->eax == 0)
    {
        goto at_4082ea;
    }
    r->eax = r->edi;
    call_keep(r, 0x4eb5b4);
    wr32(r, r->ebx, r->eax);
    r->ebx = r->ecx;
    r->edx = r->edx + 1;
    if ((int32_t)r->edx < (int32_t)0x4)
    {
        goto at_40827e;
    }
    wr32(r, r->ebp - 0x7c, rd32(r, r->ebp - 0x7c) - 1);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4080a0;
at_408141:
    r->eax = 0x4f5f38;
    if (r->port->env.failed)
    {
        return;
    }
    goto at_407f3d;
at_40814b:
    r->eax = rd32(r, r->ebp - 0x3c);
    r->eax = rd32(r, r->eax);
    wr32(r, r->ebp - 0x38, r->eax);
    r->eax = rd32(r, r->ebp - 0x8c);
    r->edx = rd32(r, r->ebp - 0x4c);
    wr32(r, r->ebp - 0x3c, rd32(r, r->ebp - 0x3c) + 0x4);
    r->ecx = r->eax + 0x4;
    wr32(r, r->ebp - 0x8c, r->ecx);
    r->edi = r->edx + 0x4;
    wr32(r, r->ebp - 0x4c, r->edi);
    r->eax = rd32(r, r->eax);
    r->eax = r->eax + rd32(r, r->edx);
    set_low8(&r->ecx, rd8(r, r->ebp - 0x80));
    r->eax = r->eax << (r->ecx & 0xff);
    r->edx = rd32(r, r->ebp - 0x88);
    r->edx = rd32(r, r->edx + 0x64);
    r->edi = rd32(r, r->edx + r->eax * 4);
    r->eax = rd32(r, r->ebp - 0x3c);
    r->eax = rd32(r, r->eax);
    wr32(r, r->ebp - 0x40, r->eax);
    wr32(r, r->ebp - 0x3c, rd32(r, r->ebp - 0x3c) + 0x4);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_407faa;
at_408195:
    call_keep(r, 0x4046e0);
    if (r->eax != 0)
    {
        goto at_4081a4;
    }
    r->esi = r->esi - 1;
    if (r->port->env.failed)
    {
        return;
    }
    goto at_407fb0;
at_4081a4:
    r->ecx = r->ecx + r->ecx;
    r->edx = r->edx - r->ecx;
    r->esi = r->esi - 1;
    if (r->port->env.failed)
    {
        return;
    }
    goto at_407fb0;
at_4081ae:
    r->eax = rd32(r, r->eax + 0x524288);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_408018;
at_4081b9:
    if (r->edx == 0)
    {
        goto at_4081f9;
    }
    r->eax = rd32(r, r->ebp - 0x40);
    wr32(r, r->ebp - 0x44, r->eax);
    call_keep(r, 0x4046e0);
    r->edx = r->eax;
    r->eax = rd32(r, r->ebp - 0x2c);
    r->eax = r->eax << 0x2;
    if (r->edx == 0)
    {
        goto at_4081f1;
    }
    r->eax = rd32(r, r->eax + 0x524288);
    call_keep(r, 0x4eb5b4);
at_4081df:
    r->edx = r->edi;
    call_keep(r, 0x4d8177);
    wr32(r, r->ebx, r->eax);
    r->ebx = rd32(r, r->ebp - 0x1c);
    r->esi = r->esi - 1;
    if (r->port->env.failed)
    {
        return;
    }
    goto at_408024;
at_4081f1:
    r->eax = rd32(r, r->eax + 0x524288);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4081df;
at_4081f9:
    wr32(r, r->ebx, r->edx);
    r->ebx = r->eax;
    if (r->port->env.failed)
    {
        return;
    }
    goto at_408024;
at_408202:
    r->eax = rd32(r, r->eax + 0x524288);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_40806e;
at_40820d:
    if (r->ecx == 0)
    {
        goto at_408248;
    }
    r->eax = rd32(r, r->ebp - 0x40);
    wr32(r, r->ebp - 0x44, r->eax);
    call_keep(r, 0x4046e0);
    r->ecx = r->ecx << 0x2;
    if (r->eax == 0)
    {
        goto at_408240;
    }
    r->eax = rd32(r, r->ecx + 0x524288);
    call_keep(r, 0x4eb5b4);
at_40822e:
    r->edx = r->edi;
    call_keep(r, 0x4d8177);
    wr32(r, r->ebx, r->eax);
    r->ebx = rd32(r, r->ebp - 0x18);
    r->esi = r->esi - 1;
    if (r->port->env.failed)
    {
        return;
    }
    goto at_40807a;
at_408240:
    r->eax = rd32(r, r->ecx + 0x524288);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_40822e;
at_408248:
    wr32(r, r->ebx, r->ecx);
    r->ebx = r->eax;
    if (r->port->env.failed)
    {
        return;
    }
    goto at_40807a;
at_408251:
    r->esi = r->esi - 1;
    if ((int32_t)r->esi < 0)
    {
        goto at_408272;
    }
    call_keep(r, 0x4046e0);
    if (r->eax == 0 && !r->port->env.failed)
    {
        goto at_4080c8;
    }
    r->eax = rd32(r, r->ebp - 0xe);
    r->eax = (uint32_t)((int32_t)r->eax >> 0x10);
    r->eax = r->eax + r->eax;
    r->edx = r->edx - r->eax;
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4080c8;
at_408272:
    r->edx = 0;
    wr16(r, r->ebp - 0xc, (r->edx & 0xffff));
    r->esi = r->esi + 1;
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4080db;
at_40827e:
    if ((uint8_t)((r->edx & 0xff) & 0x1) == 0 && !r->port->env.failed)
    {
        goto at_4080dd;
    }
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4080ea;
at_40828c:
    r->eax = rd32(r, r->ebp - 0x3c);
    r->eax = rd32(r, r->eax);
    wr32(r, r->ebp - 0x38, r->eax);
    r->edi = rd32(r, r->ebp - 0x3c);
    r->edi = r->edi + 0x4;
    wr32(r, r->ebp - 0x3c, r->edi);
    r->eax = rd32(r, r->edi);
    wr32(r, r->ebp - 0x40, r->eax);
    r->eax = rd32(r, r->ebp - 0x8c);
    r->ecx = rd32(r, r->ebp - 0x4c);
    r->edi = r->edi + 0x4;
    wr32(r, r->ebp - 0x3c, r->edi);
    r->edi = r->eax + 0x4;
    wr32(r, r->ebp - 0x8c, r->edi);
    r->edi = r->ecx + 0x4;
    wr32(r, r->ebp - 0x4c, r->edi);
    r->eax = rd32(r, r->eax);
    r->eax = r->eax + rd32(r, r->ecx);
    set_low8(&r->ecx, rd8(r, r->ebp - 0x80));
    r->eax = r->eax << (r->ecx & 0xff);
    r->ecx = r->eax * 4;
    r->eax = rd32(r, r->ebp - 0x88);
    r->eax = rd32(r, r->eax + 0x64);
    r->edi = rd32(r, r->ecx + r->eax);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4080e7;
at_4082e1:
    r->esi = r->esi + 1;
    wr32(r, r->ebp - 0x7c, rd32(r, r->ebp - 0x7c) - 1);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4080a0;
at_4082ea:
    wr32(r, r->ebx, r->edi);
    r->ebx = r->ecx;
    r->edx = r->edx + 1;
    if ((int32_t)r->edx < (int32_t)0x4 && !r->port->env.failed)
    {
        goto at_40827e;
    }
    wr32(r, r->ebp - 0x7c, rd32(r, r->ebp - 0x7c) - 1);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4080a0;
at_4082fc:
    wr32(r, r->ebx, 0x0);
    r->ebx = r->ecx;
    r->edx = r->edx + 1;
    if ((int32_t)r->edx < (int32_t)0x4 && !r->port->env.failed)
    {
        goto at_40827e;
    }
    wr32(r, r->ebp - 0x7c, rd32(r, r->ebp - 0x7c) - 1);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4080a0;
at_408316:
    r->edx = rd32(r, r->ebp - 0x90);
    r->edx = r->edx + 0x900;
    r->edx = r->edx - r->ebx;
    r->edx = (uint32_t)((int32_t)r->edx >> 0x3);
    if (r->edx == 0)
    {
        goto at_40833a;
    }
    r->eax = 0;
at_40832d:
    wr32(r, r->ebx, r->eax);
    r->ebx = r->ebx + 0x4;
    wr32(r, r->ebx, r->eax);
    r->ebx = r->ebx + 0x4;
    r->edx = r->edx - 1;
    if (r->edx != 0 && !r->port->env.failed)
    {
        goto at_40832d;
    }
at_40833a:
    r->eax = rd32(r, r->ebp - 0x44);
    r->eax = r->eax + 1;
    r->edx = rd32(r, r->ebp - 0x88);
    wr32(r, r->edx + 0x3c, r->eax);
    r->ecx = r->eax;
    r->edx = rd32(r, r->ebp - 0x84);
    r->eax = r->edx * 4;
    r->eax = r->eax - r->edx;
    r->eax = r->eax << 0x3;
    r->eax = r->eax - r->edx;
    r->eax = r->eax << 0x2;
    r->eax = rd32(r, r->eax + r->ecx * 4 + 0x523ecc);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_407edd;
at_40836c:
    flags(r, F_LOGIC, r->esi, 0, 32);
    if (cond(r, CC_LE))
    {
        goto at_408382;
    }
    r->eax = r->esi;
    call_keep(r, 0x404610);
at_408377:
    r->eax = 0;
    r->edi = rd32(r, r->ebp - 0x8);
    r->esi = rd32(r, r->ebp - 0x4);
    return;
at_408382:
    if (cond(r, CC_GE) && !r->port->env.failed)
    {
        goto at_408377;
    }
    r->eax = 0x1;
    r->edi = rd32(r, r->ebp - 0x8);
    r->esi = rd32(r, r->ebp - 0x4);
    return;
}

uint32_t vertrix_port_mpeg_huffman_decode_407830(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0xb0
    };
    Port port;
    uint8_t stack[BELOW + 8 + 4 * 1];
    Regs r;
    port_open_arguments(&port, stack, calls, services, globals, entry, BELOW, 1);
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
