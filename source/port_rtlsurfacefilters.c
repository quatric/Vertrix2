#include "port_rtlsurfacefilters.h"

/* Loops over the rows of an object (count at +0x24, descriptor at +0xd8), clipped by
 * +0x90/+0x98/+0x9c/+0x140. */

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

/* idiv and div of edx:eax as the original's (a zero divisor or an overflowing quotient leaves
 * both registers). */
static void idiv32(Regs *r, uint32_t value)
{
    LiftFlags flags;
    memset(&flags, 0, sizeof flags);
    lift_idiv1(32, value, &r->eax, &r->edx, &flags);
}

static void div32(Regs *r, uint32_t value)
{
    LiftFlags flags;
    memset(&flags, 0, sizeof flags);
    lift_div1(32, value, &r->eax, &r->edx, &flags);
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

/* An indirect call (an import or a method): every value pushed passed and popped, as stdcall. */
static void call_all(Regs *r, uint32_t target)
{
    call_with_stack(r, target, r->pushed, 0);
}

/* Original 0x4ba7b0: Loops over the rows of an object (count at +0x24, descriptor at +0xd8),
 * clipped by +0x90/+0x98/+0x9c/+0x140. It fetches each scanline through the virtual method at
 * vtable+0x20 (0x4ba8d9, 0x4baf2d) and calls vertrix_port_rtl_copy_blocks_4c98d0 at 0x4baaed. It
 * takes 16-bit coefficients from the table at [[obj+0xd8]+0x4c], scales them, and applies them in
 * fixed-point multiply-accumulate steps (imul, then sar 0x10). It then calls a per-row handler from
 * the table at obj+0x1c0 (call [ebp-0xbc] at 0x4bad2d). This reads as a weighted per-row filter or
 * resample pass. No strings or callers are listed. Evidence: calls 0x4c98d0. Register-for-register
 * from the listing (0x4ba7bd..0x4bb03c); labels are the original addresses. */
static void run(Regs *r)
{
    wr32(r, r->ebp - 0xa4, r->eax);
    r->ecx = r->edx;
    r->eax = rd32(r, r->eax + 0x1ac);
    wr32(r, r->ebp - 0xf8, r->eax);
    r->eax = rd32(r, r->ebp - 0xa4);
    r->eax = rd32(r, r->eax + 0x140);
    r->eax = r->eax - 1;
    r->edx = rd32(r, r->ebp - 0xa4);
    wr32(r, r->ebp - 0xfc, r->eax);
    r->eax = rd32(r, r->ebp - 0xa4);
    r->ebx = rd32(r, r->edx + 0x98);
    if ((int32_t)r->ebx < (int32_t)rd32(r, r->eax + 0x90))
    {
        goto at_4ba814;
    }
at_4ba7fe:
    r->eax = rd32(r, r->ebp - 0xa4);
    r->eax = rd32(r, r->eax + 0x1b4);
    if (rd32(r, r->eax + 0x14) == 0x0)
    {
        goto at_4bae60;
    }
at_4ba814:
    r->eax = rd32(r, r->ebp - 0xa4);
    r->eax = rd32(r, r->eax + 0xd8);
    wr32(r, r->ebp - 0x68, r->eax);
    r->eax = rd32(r, r->ebp - 0xa4);
    r->esi = 0;
    r->edi = rd32(r, r->eax + 0x24);
    wr32(r, r->ebp - 0xd8, r->esi);
    if ((int32_t)r->edi <= 0)
    {
        goto at_4bae29;
    }
    r->eax = rd32(r, r->ebp - 0xf8);
    wr32(r, r->ebp - 0xe0, r->ecx);
    wr32(r, r->ebp - 0xe4, r->esi);
    wr32(r, r->ebp - 0xdc, r->eax);
at_4ba854:
    r->eax = rd32(r, r->ebp - 0x68);
    if (rd32(r, r->eax + 0x30) == 0x0)
    {
        goto at_4badd5;
    }
    r->eax = rd32(r, r->ebp - 0xa4);
    r->edi = rd32(r, r->ebp - 0xfc);
    if (r->edi <= rd32(r, r->eax + 0x9c))
    {
        goto at_4baee7;
    }
    r->eax = rd32(r, r->ebp - 0x68);
    r->eax = rd32(r, r->eax + 0xc);
    wr32(r, r->ebp - 0xc8, r->eax);
    r->ecx = r->eax + r->eax;
    r->eax = 0;
    wr32(r, r->ebp - 0xcc, r->eax);
at_4ba890:
    r->eax = rd32(r, r->ebp - 0xa4);
    if (rd32(r, r->eax + 0x9c) <= 0x0)
    {
        goto at_4baf1d;
    }
    r->eax = rd32(r, r->ebp - 0x68);
    r->esi = rd32(r, r->eax + 0xc);
    r->eax = rd32(r, r->ebp - 0xa4);
    r->ebx = rd32(r, r->eax + 0x9c);
    r->eax = rd32(r, r->ebp - 0x68);
    r->ebx = r->ebx - 1;
    r->ebx = r->ebx * rd32(r, r->eax + 0xc);
    r->ecx = r->ecx + r->esi;
    r->esi = rd32(r, r->ebp - 0xa4);
    r->edx = rd32(r, r->ebp - 0xdc);
    push(r, 0x0);
    r->esi = rd32(r, r->esi + 0x4);
    r->edx = rd32(r, r->edx + 0x48);
    r->eax = rd32(r, r->ebp - 0xa4);
    call_all(r, rd32(r, r->esi + 0x20));
    r->ecx = rd32(r, r->ebp - 0x68);
    r->ecx = rd32(r, r->ecx + 0xc);
    r->ecx = r->ecx << 0x2;
    r->ecx = r->ecx + r->eax;
    r->eax = 0;
    wr32(r, r->ebp - 0xd0, r->eax);
at_4ba8ef:
    r->edi = rd32(r, r->ebp - 0xf8);
    r->edx = rd32(r, r->ebp - 0xe4);
    r->edi = rd32(r, r->edi + 0x70);
    r->edi = r->edi + r->edx;
    r->edx = rd32(r, r->ebp - 0x68);
    r->edx = rd32(r, r->edx + 0x4c);
    r->ebx = 0;
    set_low16(&r->ebx, rd16(r, r->edx + 0x2));
    wr32(r, r->ebp - 0xf0, r->ebx);
    r->ebx = 0;
    set_low16(&r->ebx, rd16(r, r->edx + 0x10));
    wr32(r, r->ebp - 0xec, r->ebx);
    r->ebx = 0;
    set_low16(&r->ebx, rd16(r, r->edx + 0x20));
    wr32(r, r->ebp - 0xe8, r->ebx);
    r->ebx = 0;
    r->eax = 0;
    set_low16(&r->ebx, rd16(r, r->edx + 0x12));
    set_low16(&r->eax, rd16(r, r->edx));
    wr32(r, r->ebp - 0xf4, r->ebx);
    set_low16(&r->edx, rd16(r, r->edx + 0x4));
    r->ebx = rd32(r, r->ebp - 0xa4);
    r->ebx = rd32(r, r->ebx + 0x1c0);
    wr32(r, r->ebp - 0x100, r->ebx);
    r->ebx = rd32(r, r->ebp - 0xd8);
    r->esi = rd32(r, r->ebp - 0x100);
    r->ebx = r->ebx << 0x2;
    r->ebx = r->ebx + r->esi;
    r->ebx = rd32(r, r->ebx + 0x4);
    wr32(r, r->ebp - 0xbc, r->ebx);
    r->ebx = rd32(r, r->ebp - 0xe0);
    r->ebx = rd32(r, r->ebx);
    r->edx = r->edx & 0xffff;
    wr32(r, r->ebp - 0xa0, r->ebx);
    r->ebx = 0;
    r->esi = rd32(r, r->ebp - 0xc8);
    wr32(r, r->ebp - 0xc4, r->ebx);
    if ((int32_t)r->esi <= 0)
    {
        goto at_4badd5;
    }
    r->ebx = r->eax + r->eax * 8;
    wr32(r, r->ebp - 0xa8, r->ebx);
    r->ebx = r->edx;
    r->edx = r->edx << 0x7;
    wr32(r, r->ebp - 0x80, r->edx);
    r->edx = r->eax + r->eax * 4;
    r->eax = r->eax * 0x24;
    wr32(r, r->ebp - 0xc0, r->ecx);
    wr32(r, r->ebp - 0xb8, r->edx);
    r->edx = rd32(r, r->ebp - 0xf4);
    r->ebx = r->ebx << 0x8;
    r->edx = r->edx << 0x8;
    wr32(r, r->ebp - 0x98, r->ebx);
    wr32(r, r->ebp - 0x94, r->edx);
    r->edx = rd32(r, r->ebp - 0xf4);
    wr32(r, r->ebp - 0xac, r->eax);
    r->eax = rd32(r, r->ebp - 0xec);
    r->edx = r->edx << 0x7;
    r->eax = r->eax << 0x8;
    wr32(r, r->ebp - 0x88, r->edx);
    wr32(r, r->ebp - 0x9c, r->eax);
    r->eax = rd32(r, r->ebp - 0xec);
    r->edx = rd32(r, r->ebp - 0xa8);
    r->eax = r->eax << 0x7;
    wr32(r, r->ebp - 0xb4, r->edx);
    wr32(r, r->ebp - 0x84, r->eax);
    r->eax = rd32(r, r->ebp - 0xac);
    r->edx = rd32(r, r->ebp - 0xe8);
    wr32(r, r->ebp - 0xb0, r->eax);
    r->eax = rd32(r, r->ebp - 0xf0);
    r->edx = r->edx << 0x8;
    r->eax = r->eax << 0x8;
    wr32(r, r->ebp - 0x7c, r->edx);
    wr32(r, r->ebp - 0x78, r->eax);
    r->eax = rd32(r, r->ebp - 0xf0);
    r->edx = rd32(r, r->ebp - 0xe8);
    r->eax = r->eax << 0x7;
    r->edx = r->edx << 0x7;
    wr32(r, r->ebp - 0x90, r->eax);
    r->eax = r->esi - 0x1;
    wr32(r, r->ebp - 0x8c, r->edx);
    wr32(r, r->ebp - 0xd4, r->eax);
at_4baa5a:
    r->esi = rd32(r, r->ebp - 0xc0);
    r->eax = rd32(r, r->ebp - 0xd0);
    r->esi = rd32(r, r->esi);
    if (r->eax == 0)
    {
        goto at_4baf42;
    }
    if (rd32(r, r->ebp - 0xc4) != 0x0)
    {
        goto at_4baf42;
    }
    wr32(r, r->ebp - 0x3c, r->esi);
at_4baa80:
    if (rd32(r, r->ebp - 0xcc) == 0x0)
    {
        goto at_4baf53;
    }
    r->eax = rd32(r, r->ebp - 0xc4);
    if (r->eax != rd32(r, r->ebp - 0xd4))
    {
        goto at_4baf53;
    }
    wr32(r, r->ebp - 0x48, r->esi);
at_4baaa2:
    r->eax = rd32(r, r->ebp - 0x3c);
    r->eax = (uint32_t)(int32_t)(int16_t)rd16(r, r->eax);
    wr32(r, r->ebp - 0x40, r->eax);
    wr32(r, r->ebp - 0x24, r->eax);
    wr32(r, r->ebp - 0x74, r->eax);
    r->eax = (uint32_t)(int32_t)(int16_t)rd16(r, r->esi);
    wr32(r, r->ebp - 0x14, r->eax);
    wr32(r, r->ebp - 0x1c, r->eax);
    wr32(r, r->ebp - 0x50, r->eax);
    r->eax = rd32(r, r->ebp - 0x48);
    r->eax = (uint32_t)(int32_t)(int16_t)rd16(r, r->eax);
    wr32(r, r->ebp - 0x44, r->eax);
    wr32(r, r->ebp - 0x18, r->eax);
    wr32(r, r->ebp - 0x70, r->eax);
    r->eax = 0;
    wr32(r, r->ebp - 0x4c, r->eax);
    r->eax = rd32(r, r->ebp - 0x68);
    r->eax = rd32(r, r->eax + 0x1c);
    r->eax = r->eax - 1;
    r->edx = 0;
    wr32(r, r->ebp - 0x6c, r->eax);
    wr32(r, r->ebp - 0x20, r->edx);
at_4baae0:
    r->ebx = 0x1;
    r->edx = r->ebp - 0x180;
    r->eax = r->esi;
    call(r, 0x4c98d0, 0);
    r->eax = rd32(r, r->ebp - 0x20);
    if (r->eax >= rd32(r, r->ebp - 0x6c))
    {
        goto at_4bab1b;
    }
    r->eax = rd32(r, r->ebp - 0x3c);
    r->eax = rd32(r, r->eax + 0x7e);
    r->eax = (uint32_t)((int32_t)r->eax >> 0x10);
    wr32(r, r->ebp - 0x40, r->eax);
    r->eax = rd32(r, r->esi + 0x7e);
    r->eax = (uint32_t)((int32_t)r->eax >> 0x10);
    wr32(r, r->ebp - 0x14, r->eax);
    r->eax = rd32(r, r->ebp - 0x48);
    r->eax = rd32(r, r->eax + 0x7e);
    r->eax = (uint32_t)((int32_t)r->eax >> 0x10);
    wr32(r, r->ebp - 0x44, r->eax);
at_4bab1b:
    r->ebx = rd32(r, r->edi + 0x4);
    if (r->ebx == 0)
    {
        goto at_4bab7a;
    }
    if ((uint16_t)rd16(r, r->ebp - 0x17e) != (uint16_t)0x0)
    {
        goto at_4bab7a;
    }
    r->edx = rd32(r, r->ebp - 0x50);
    r->ecx = rd32(r, r->ebp - 0x14);
    r->eax = rd32(r, r->ebp - 0xb0);
    r->edx = r->edx - r->ecx;
    r->edx = r->edx * r->eax;
    set_low8(&r->ecx, (r->ebx & 0xff));
    r->eax = 0x1;
    r->eax = r->eax << (r->ecx & 0xff);
    wr32(r, r->ebp - 0x34, r->eax);
    r->eax = r->eax - 1;
    wr32(r, r->ebp - 0x64, r->eax);
    if ((int32_t)r->edx < 0)
    {
        goto at_4baf64;
    }
    r->edx = r->edx + rd32(r, r->ebp - 0x90);
    r->ecx = rd32(r, r->ebp - 0x78);
    r->eax = r->edx;
    r->edx = (uint32_t)((int32_t)r->edx >> 0x1f);
    idiv32(r, r->ecx);
    r->ecx = r->eax;
    if ((int32_t)r->ebx <= 0)
    {
        goto at_4bab73;
    }
    if ((int32_t)r->eax < (int32_t)rd32(r, r->ebp - 0x34))
    {
        goto at_4bab73;
    }
    r->ecx = rd32(r, r->ebp - 0x64);
at_4bab73:
    wr16(r, r->ebp - 0x17e, (r->ecx & 0xffff));
at_4bab7a:
    r->ebx = rd32(r, r->edi + 0x8);
    if (r->ebx == 0)
    {
        goto at_4babdc;
    }
    if ((uint16_t)rd16(r, r->ebp - 0x170) != (uint16_t)0x0)
    {
        goto at_4babdc;
    }
    r->edx = rd32(r, r->ebp - 0x24);
    r->eax = rd32(r, r->ebp - 0x18);
    r->ecx = rd32(r, r->ebp - 0xac);
    r->edx = r->edx - r->eax;
    r->edx = r->edx * r->ecx;
    r->eax = 0x1;
    set_low8(&r->ecx, (r->ebx & 0xff));
    r->eax = r->eax << (r->ecx & 0xff);
    wr32(r, r->ebp - 0x38, r->eax);
    r->eax = r->eax - 1;
    wr32(r, r->ebp - 0x60, r->eax);
    if ((int32_t)r->edx < 0)
    {
        goto at_4baf8b;
    }
    r->edx = r->edx + rd32(r, r->ebp - 0x84);
    r->ecx = rd32(r, r->ebp - 0x9c);
    r->eax = r->edx;
    r->edx = (uint32_t)((int32_t)r->edx >> 0x1f);
    idiv32(r, r->ecx);
    r->ecx = r->eax;
    if ((int32_t)r->ebx <= 0)
    {
        goto at_4babd5;
    }
    if ((int32_t)r->eax < (int32_t)rd32(r, r->ebp - 0x38))
    {
        goto at_4babd5;
    }
    r->ecx = rd32(r, r->ebp - 0x60);
at_4babd5:
    wr16(r, r->ebp - 0x170, (r->ecx & 0xffff));
at_4babdc:
    r->ebx = rd32(r, r->edi + 0xc);
    if (r->ebx == 0)
    {
        goto at_4bac42;
    }
    if ((uint16_t)rd16(r, r->ebp - 0x160) != (uint16_t)0x0)
    {
        goto at_4bac42;
    }
    r->ecx = rd32(r, r->ebp - 0x24);
    r->eax = rd32(r, r->ebp - 0x18);
    r->edx = rd32(r, r->ebp - 0x1c);
    r->ecx = r->ecx + r->eax;
    r->edx = r->edx + r->edx;
    r->ecx = r->ecx - r->edx;
    r->edx = r->ecx;
    r->edx = r->edx * rd32(r, r->ebp - 0xb4);
    r->eax = 0x1;
    set_low8(&r->ecx, (r->ebx & 0xff));
    r->eax = r->eax << (r->ecx & 0xff);
    wr32(r, r->ebp - 0x28, r->eax);
    r->eax = r->eax - 1;
    wr32(r, r->ebp - 0x58, r->eax);
    if ((int32_t)r->edx < 0)
    {
        goto at_4bafb5;
    }
    r->edx = r->edx + rd32(r, r->ebp - 0x8c);
    r->ecx = rd32(r, r->ebp - 0x7c);
    r->eax = r->edx;
    r->edx = (uint32_t)((int32_t)r->edx >> 0x1f);
    idiv32(r, r->ecx);
    r->ecx = r->eax;
    if ((int32_t)r->ebx <= 0)
    {
        goto at_4bac3b;
    }
    if ((int32_t)r->eax < (int32_t)rd32(r, r->ebp - 0x28))
    {
        goto at_4bac3b;
    }
    r->ecx = rd32(r, r->ebp - 0x58);
at_4bac3b:
    wr16(r, r->ebp - 0x160, (r->ecx & 0xffff));
at_4bac42:
    r->ebx = rd32(r, r->edi + 0x10);
    if (r->ebx == 0)
    {
        goto at_4bacae;
    }
    if ((uint16_t)rd16(r, r->ebp - 0x16e) != (uint16_t)0x0)
    {
        goto at_4bacae;
    }
    r->edx = rd32(r, r->ebp - 0x74);
    r->eax = rd32(r, r->ebp - 0x40);
    r->ecx = rd32(r, r->ebp - 0x70);
    r->edx = r->edx - r->eax;
    r->eax = rd32(r, r->ebp - 0x44);
    r->edx = r->edx - r->ecx;
    r->ecx = rd32(r, r->ebp - 0xb8);
    r->edx = r->edx + r->eax;
    r->edx = r->edx * r->ecx;
    r->eax = 0x1;
    set_low8(&r->ecx, (r->ebx & 0xff));
    r->eax = r->eax << (r->ecx & 0xff);
    wr32(r, r->ebp - 0x30, r->eax);
    r->eax = r->eax - 1;
    wr32(r, r->ebp - 0x5c, r->eax);
    if ((int32_t)r->edx < 0)
    {
        goto at_4bafdc;
    }
    r->edx = r->edx + rd32(r, r->ebp - 0x88);
    r->ecx = rd32(r, r->ebp - 0x94);
    r->eax = r->edx;
    r->edx = (uint32_t)((int32_t)r->edx >> 0x1f);
    idiv32(r, r->ecx);
    r->ecx = r->eax;
    if ((int32_t)r->ebx <= 0)
    {
        goto at_4baca7;
    }
    if ((int32_t)r->eax < (int32_t)rd32(r, r->ebp - 0x30))
    {
        goto at_4baca7;
    }
    r->ecx = rd32(r, r->ebp - 0x5c);
at_4baca7:
    wr16(r, r->ebp - 0x16e, (r->ecx & 0xffff));
at_4bacae:
    r->ebx = rd32(r, r->edi + 0x14);
    if (r->ebx == 0)
    {
        goto at_4bad14;
    }
    if ((uint16_t)rd16(r, r->ebp - 0x17c) != (uint16_t)0x0)
    {
        goto at_4bad14;
    }
    r->ecx = rd32(r, r->ebp - 0x50);
    r->eax = rd32(r, r->ebp - 0x14);
    r->edx = rd32(r, r->ebp - 0x1c);
    r->ecx = r->ecx + r->eax;
    r->edx = r->edx + r->edx;
    r->ecx = r->ecx - r->edx;
    r->edx = r->ecx;
    r->edx = r->edx * rd32(r, r->ebp - 0xa8);
    r->eax = 0x1;
    set_low8(&r->ecx, (r->ebx & 0xff));
    r->eax = r->eax << (r->ecx & 0xff);
    wr32(r, r->ebp - 0x2c, r->eax);
    r->eax = r->eax - 1;
    wr32(r, r->ebp - 0x54, r->eax);
    if ((int32_t)r->edx < 0)
    {
        goto at_4bb006;
    }
    r->edx = r->edx + rd32(r, r->ebp - 0x80);
    r->ecx = rd32(r, r->ebp - 0x98);
    r->eax = r->edx;
    r->edx = (uint32_t)((int32_t)r->edx >> 0x1f);
    idiv32(r, r->ecx);
    r->ecx = r->eax;
    if ((int32_t)r->ebx <= 0)
    {
        goto at_4bad0d;
    }
    if ((int32_t)r->eax < (int32_t)rd32(r, r->ebp - 0x2c))
    {
        goto at_4bad0d;
    }
    r->ecx = rd32(r, r->ebp - 0x54);
at_4bad0d:
    wr16(r, r->ebp - 0x17c, (r->ecx & 0xffff));
at_4bad14:
    r->ecx = rd32(r, r->ebp - 0x4c);
    r->ebx = r->ebp - 0x180;
    r->edx = rd32(r, r->ebp - 0x68);
    push(r, r->ecx);
    r->eax = rd32(r, r->ebp - 0xa4);
    r->ecx = rd32(r, r->ebp - 0xa0);
    call_all(r, rd32(r, r->ebp - 0xbc));
    r->eax = rd32(r, r->ebp - 0x24);
    wr32(r, r->ebp - 0x74, r->eax);
    r->eax = rd32(r, r->ebp - 0x40);
    wr32(r, r->ebp - 0x24, r->eax);
    r->eax = rd32(r, r->ebp - 0x1c);
    wr32(r, r->ebp - 0x50, r->eax);
    r->eax = rd32(r, r->ebp - 0x14);
    r->esi = r->esi + 0x80;
    wr32(r, r->ebp - 0x1c, r->eax);
    r->eax = rd32(r, r->ebp - 0x18);
    r->ebx = rd32(r, r->ebp - 0x3c);
    wr32(r, r->ebp - 0x70, r->eax);
    r->eax = rd32(r, r->ebp - 0x44);
    r->edx = rd32(r, r->ebp - 0x4c);
    wr32(r, r->ebp - 0x18, r->eax);
    r->eax = rd32(r, r->ebp - 0x48);
    r->ecx = rd32(r, r->ebp - 0x20);
    r->eax = r->eax + 0x80;
    r->ebx = r->ebx + 0x80;
    wr32(r, r->ebp - 0x48, r->eax);
    r->eax = rd32(r, r->ebp - 0x68);
    r->ecx = r->ecx + 1;
    wr32(r, r->ebp - 0x3c, r->ebx);
    r->eax = rd32(r, r->eax + 0x24);
    wr32(r, r->ebp - 0x20, r->ecx);
    r->edx = r->edx + r->eax;
    r->ebx = rd32(r, r->ebp - 0x6c);
    wr32(r, r->ebp - 0x4c, r->edx);
    if (r->ecx <= r->ebx && !r->port->env.failed)
    {
        goto at_4baae0;
    }
    r->edx = rd32(r, r->ebp - 0x68);
    r->eax = rd32(r, r->ebp - 0xa0);
    r->ecx = rd32(r, r->ebp - 0xc4);
    r->edx = rd32(r, r->edx + 0x24);
    r->ebx = rd32(r, r->ebp - 0xc8);
    r->edx = r->edx << 0x2;
    r->ecx = r->ecx + 1;
    r->eax = r->eax + r->edx;
    r->edx = rd32(r, r->ebp - 0xc0);
    wr32(r, r->ebp - 0xc4, r->ecx);
    r->edx = r->edx + 0x4;
    wr32(r, r->ebp - 0xa0, r->eax);
    wr32(r, r->ebp - 0xc0, r->edx);
    if ((int32_t)r->ecx < (int32_t)r->ebx && !r->port->env.failed)
    {
        goto at_4baa5a;
    }
at_4badd5:
    r->eax = rd32(r, r->ebp - 0xdc);
    r->edx = rd32(r, r->ebp - 0xe0);
    r->ecx = rd32(r, r->ebp - 0xe4);
    r->ebx = rd32(r, r->ebp - 0xd8);
    r->esi = rd32(r, r->ebp - 0x68);
    r->eax = r->eax + 0x4;
    r->edx = r->edx + 0x4;
    r->ecx = r->ecx + 0x18;
    r->ebx = r->ebx + 1;
    r->esi = r->esi + 0x54;
    wr32(r, r->ebp - 0xdc, r->eax);
    wr32(r, r->ebp - 0xe0, r->edx);
    r->edx = rd32(r, r->ebp - 0xa4);
    wr32(r, r->ebp - 0xe4, r->ecx);
    wr32(r, r->ebp - 0xd8, r->ebx);
    r->edi = rd32(r, r->edx + 0x24);
    wr32(r, r->ebp - 0x68, r->esi);
    if ((int32_t)r->ebx < (int32_t)r->edi && !r->port->env.failed)
    {
        goto at_4ba854;
    }
at_4bae29:
    r->eax = rd32(r, r->ebp - 0xa4);
    r->edx = rd32(r, r->eax + 0x9c);
    r->edx = r->edx + 1;
    wr32(r, r->eax + 0x9c, r->edx);
    r->eax = r->edx;
    r->edx = rd32(r, r->ebp - 0xa4);
    if (r->eax >= rd32(r, r->edx + 0x140))
    {
        goto at_4bb02d;
    }
    r->edx = 0x3;
    r->eax = r->edx;
    r->edi = rd32(r, r->ebp - 0x10);
    r->esi = rd32(r, r->ebp - 0xc);
    r->ecx = rd32(r, r->ebp - 0x8);
    r->ebx = rd32(r, r->ebp - 0x4);
    return;
at_4bae60:
    r->eax = rd32(r, r->ebp - 0xa4);
    r->edx = rd32(r, r->ebp - 0xa4);
    r->eax = rd32(r, r->eax + 0x90);
    if (r->eax != rd32(r, r->edx + 0x98))
    {
        goto at_4bae9f;
    }
    flags(r, F_SUB, rd32(r, r->edx + 0x190), 0x0, 32);
    set_low8(&r->eax, cond(r, CC_E));
    r->eax = r->eax & 0xff;
    r->edi = rd32(r, r->edx + 0x9c);
    r->ebx = rd32(r, r->edx + 0x94);
    r->eax = r->eax + r->edi;
    if (r->eax < r->ebx && !r->port->env.failed)
    {
        goto at_4ba814;
    }
at_4bae9f:
    r->edx = rd32(r, r->ebp - 0xa4);
    r->edx = rd32(r, r->edx + 0x1b4);
    r->eax = rd32(r, r->ebp - 0xa4);
    call_all(r, rd32(r, r->edx));
    if (r->eax == 0)
    {
        goto at_4baeda;
    }
    r->eax = rd32(r, r->ebp - 0xa4);
    r->edx = rd32(r, r->ebp - 0xa4);
    r->eax = rd32(r, r->eax + 0x90);
    if ((int32_t)r->eax <= (int32_t)rd32(r, r->edx + 0x98) && !r->port->env.failed)
    {
        goto at_4ba7fe;
    }
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4ba814;
at_4baeda:
    r->edx = 0;
    r->eax = r->edx;
    r->edi = rd32(r, r->ebp - 0x10);
    r->esi = rd32(r, r->ebp - 0xc);
    r->ecx = rd32(r, r->ebp - 0x8);
    r->ebx = rd32(r, r->ebp - 0x4);
    return;
at_4baee7:
    r->eax = rd32(r, r->ebp - 0x68);
    r->ecx = rd32(r, r->ebp - 0x68);
    r->edx = 0;
    r->eax = rd32(r, r->eax + 0x20);
    r->ebx = rd32(r, r->ecx + 0xc);
    div32(r, r->ebx);
    wr32(r, r->ebp - 0xc8, r->edx);
    if (r->edx != 0)
    {
        goto at_4baf07;
    }
    wr32(r, r->ebp - 0xc8, r->ebx);
at_4baf07:
    r->edi = 0x1;
    r->ecx = rd32(r, r->ebp - 0xc8);
    wr32(r, r->ebp - 0xcc, r->edi);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4ba890;
at_4baf1d:
    push(r, 0x0);
    r->edx = rd32(r, r->ebp - 0xdc);
    r->esi = rd32(r, r->eax + 0x4);
    r->ebx = 0;
    r->edx = rd32(r, r->edx + 0x48);
    call_all(r, rd32(r, r->esi + 0x20));
    r->ebx = 0x1;
    r->ecx = r->eax;
    wr32(r, r->ebp - 0xd0, r->ebx);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4ba8ef;
at_4baf42:
    r->eax = rd32(r, r->ebp - 0xc0);
    r->eax = rd32(r, r->eax - 0x4);
    wr32(r, r->ebp - 0x3c, r->eax);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4baa80;
at_4baf53:
    r->eax = rd32(r, r->ebp - 0xc0);
    r->eax = rd32(r, r->eax + 0x4);
    wr32(r, r->ebp - 0x48, r->eax);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4baaa2;
at_4baf64:
    r->eax = rd32(r, r->ebp - 0x90);
    r->eax = r->eax - r->edx;
    r->edx = r->eax;
    r->ecx = rd32(r, r->ebp - 0x78);
    r->edx = (uint32_t)((int32_t)r->edx >> 0x1f);
    idiv32(r, r->ecx);
    r->ecx = r->eax;
    if ((int32_t)r->ebx <= 0)
    {
        goto at_4baf84;
    }
    if ((int32_t)r->eax < (int32_t)rd32(r, r->ebp - 0x34))
    {
        goto at_4baf84;
    }
    r->ecx = rd32(r, r->ebp - 0x64);
at_4baf84:
    r->ecx = 0u - r->ecx;
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4bab73;
at_4baf8b:
    r->eax = rd32(r, r->ebp - 0x84);
    r->eax = r->eax - r->edx;
    r->edx = r->eax;
    r->ecx = rd32(r, r->ebp - 0x9c);
    r->edx = (uint32_t)((int32_t)r->edx >> 0x1f);
    idiv32(r, r->ecx);
    r->ecx = r->eax;
    if ((int32_t)r->ebx <= 0)
    {
        goto at_4bafae;
    }
    if ((int32_t)r->eax < (int32_t)rd32(r, r->ebp - 0x38))
    {
        goto at_4bafae;
    }
    r->ecx = rd32(r, r->ebp - 0x60);
at_4bafae:
    r->ecx = 0u - r->ecx;
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4babd5;
at_4bafb5:
    r->eax = rd32(r, r->ebp - 0x8c);
    r->eax = r->eax - r->edx;
    r->edx = r->eax;
    r->ecx = rd32(r, r->ebp - 0x7c);
    r->edx = (uint32_t)((int32_t)r->edx >> 0x1f);
    idiv32(r, r->ecx);
    r->ecx = r->eax;
    if ((int32_t)r->ebx <= 0)
    {
        goto at_4bafd5;
    }
    if ((int32_t)r->eax < (int32_t)rd32(r, r->ebp - 0x28))
    {
        goto at_4bafd5;
    }
    r->ecx = rd32(r, r->ebp - 0x58);
at_4bafd5:
    r->ecx = 0u - r->ecx;
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4bac3b;
at_4bafdc:
    r->eax = rd32(r, r->ebp - 0x88);
    r->eax = r->eax - r->edx;
    r->edx = r->eax;
    r->ecx = rd32(r, r->ebp - 0x94);
    r->edx = (uint32_t)((int32_t)r->edx >> 0x1f);
    idiv32(r, r->ecx);
    r->ecx = r->eax;
    if ((int32_t)r->ebx <= 0)
    {
        goto at_4bafff;
    }
    if ((int32_t)r->eax < (int32_t)rd32(r, r->ebp - 0x30))
    {
        goto at_4bafff;
    }
    r->ecx = rd32(r, r->ebp - 0x5c);
at_4bafff:
    r->ecx = 0u - r->ecx;
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4baca7;
at_4bb006:
    r->eax = rd32(r, r->ebp - 0x80);
    r->eax = r->eax - r->edx;
    r->edx = r->eax;
    r->ecx = rd32(r, r->ebp - 0x98);
    r->edx = (uint32_t)((int32_t)r->edx >> 0x1f);
    idiv32(r, r->ecx);
    r->ecx = r->eax;
    if ((int32_t)r->ebx <= 0)
    {
        goto at_4bb026;
    }
    if ((int32_t)r->eax < (int32_t)rd32(r, r->ebp - 0x2c))
    {
        goto at_4bb026;
    }
    r->ecx = rd32(r, r->ebp - 0x54);
at_4bb026:
    r->ecx = 0u - r->ecx;
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4bad0d;
at_4bb02d:
    r->edx = 0x4;
    r->eax = r->edx;
    r->edi = rd32(r, r->ebp - 0x10);
    r->esi = rd32(r, r->ebp - 0xc);
    r->ecx = rd32(r, r->ebp - 0x8);
    r->ebx = rd32(r, r->ebp - 0x4);
    return;
}

uint32_t vertrix_port_surface_filter_rows_4ba7b0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x184
    };
    Port port;
    uint8_t stack[BELOW + 8];
    Regs r;
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
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
    port_set32(&port, r.ebp, -0x4u, entry->ebx);
    port_set32(&port, r.ebp, -0x8u, entry->ecx);
    port_set32(&port, r.ebp, -0xcu, entry->esi);
    port_set32(&port, r.ebp, -0x10u, entry->edi);
    run(&r);
    return port_return(&port, r.eax, r.edx);
}
