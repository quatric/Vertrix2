#include "port_rtljpegcolorselects.h"

/* libjpeg two-pass quantizer select_colors: median-cut box splitting over the 32x64x32 histogram,
 * then one colormap entry per box. */

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

/* Original 0x4c90e0: libjpeg two-pass quantizer select_colors: median-cut box splitting over the
 * 32x64x32 histogram, then one colormap entry per box. Evidence: calls 0x4c70f0.
 * Register-for-register from the listing (0x4c90ee..0x4c93b1); labels are the original addresses.
 */
static void run(Regs *r)
{
    r->esi = r->eax;
    r->eax = rd32(r, r->eax + 0x1cc);
    wr32(r, r->ebp - 0x90, r->eax);
    r->eax = rd32(r, r->eax + 0x10);
    r->edi = rd32(r, r->ebp - 0x90);
    wr32(r, r->esi + 0x88, r->eax);
    r->edx = 0x1;
    r->edi = rd32(r, r->edi + 0x14);
    r->ecx = rd32(r, r->esi + 0x4);
    r->ebx = r->edi;
    r->eax = r->esi;
    r->ebx = r->ebx << 0x5;
    call_all(r, rd32(r, r->ecx));
    wr32(r, r->eax, 0x0);
    wr32(r, r->ebp - 0x78, r->esi);
    wr32(r, r->eax + 0x4, 0x1f);
    wr32(r, r->ebp - 0x7c, r->esi);
    wr32(r, r->eax + 0x8, 0x0);
    r->ecx = r->eax;
    wr32(r, r->eax + 0xc, 0x3f);
    wr32(r, r->ebp - 0x94, r->eax);
    wr32(r, r->eax + 0x10, 0x0);
    r->edx = r->eax;
    wr32(r, r->eax + 0x14, 0x1f);
    r->eax = r->esi;
    wr32(r, r->ebp - 0x80, r->edi);
    call_keep(r, 0x4c70f0);
    r->edx = 0x1;
    wr32(r, r->ebp - 0x84, r->ecx);
    wr32(r, r->ebp - 0x64, r->edx);
    if ((int32_t)r->edi > (int32_t)r->edx)
    {
        goto at_4c93c1;
    }
at_4c9178:
    r->eax = rd32(r, r->ebp - 0x64);
    r->edx = 0;
    wr32(r, r->ebp - 0x8c, r->eax);
    wr32(r, r->ebp - 0x68, r->edx);
    if ((int32_t)r->eax <= 0)
    {
        goto at_4c9369;
    }
    r->eax = rd32(r, r->ebp - 0x94);
    wr32(r, r->ebp - 0x60, r->eax);
at_4c9197:
    r->eax = rd32(r, r->ebp - 0x78);
    wr32(r, r->ebp - 0x6c, r->eax);
    r->eax = rd32(r, r->ebp - 0x68);
    wr32(r, r->ebp - 0x70, r->eax);
    r->eax = rd32(r, r->ebp - 0x60);
    r->eax = rd32(r, r->eax + 0x4);
    wr32(r, r->ebp - 0x58, r->eax);
    r->eax = rd32(r, r->ebp - 0x60);
    r->ecx = rd32(r, r->ebp - 0x78);
    r->eax = rd32(r, r->eax + 0x8);
    r->edx = rd32(r, r->ebp - 0x60);
    wr32(r, r->ebp - 0x44, r->eax);
    r->eax = rd32(r, r->ebp - 0x60);
    r->ebx = 0;
    r->esi = 0;
    r->eax = rd32(r, r->eax + 0xc);
    wr32(r, r->ebp - 0x1c, r->ebx);
    wr32(r, r->ebp - 0x54, r->eax);
    r->eax = rd32(r, r->ebp - 0x60);
    wr32(r, r->ebp - 0x18, r->ebx);
    r->ecx = rd32(r, r->ecx + 0x1cc);
    r->eax = rd32(r, r->eax + 0x10);
    r->edx = rd32(r, r->edx);
    wr32(r, r->ebp - 0x34, r->eax);
    r->eax = rd32(r, r->ebp - 0x60);
    wr32(r, r->ebp - 0x4c, r->edx);
    r->ecx = rd32(r, r->ecx + 0x18);
    r->eax = rd32(r, r->eax + 0x14);
    r->edi = rd32(r, r->ebp - 0x58);
    wr32(r, r->ebp - 0x38, r->eax);
    if ((int32_t)r->edx > (int32_t)r->edi)
    {
        goto at_4c92ef;
    }
    r->eax = rd32(r, r->ebp - 0x34);
    r->eax = r->eax + r->eax;
    wr32(r, r->ebp - 0x40, r->eax);
    r->eax = r->edx * 4;
    r->edx = r->edx << 0x3;
    r->eax = r->eax + r->ecx;
    r->edx = r->edx + 0x4;
    wr32(r, r->ebp - 0x50, r->eax);
    wr32(r, r->ebp - 0x48, r->edx);
at_4c9216:
    r->eax = rd32(r, r->ebp - 0x44);
    if ((int32_t)r->eax > (int32_t)rd32(r, r->ebp - 0x54))
    {
        goto at_4c92cb;
    }
    r->eax = rd32(r, r->ebp - 0x48);
    r->edx = rd32(r, r->ebp - 0x50);
    wr32(r, r->ebp - 0x28, r->eax);
    r->eax = rd32(r, r->ebp - 0x44);
    r->edx = rd32(r, r->edx);
    r->eax = r->eax << 0x6;
    r->eax = r->eax + r->edx;
    wr32(r, r->ebp - 0x30, r->eax);
    r->eax = rd32(r, r->ebp - 0x44);
    r->eax = r->eax << 0x2;
    r->eax = r->eax + 0x2;
    wr32(r, r->ebp - 0x2c, r->eax);
    r->eax = rd32(r, r->ebp - 0x54);
    r->eax = r->eax << 0x2;
    wr32(r, r->ebp - 0x3c, r->eax);
    r->ecx = r->eax + 0x2;
    wr32(r, r->ebp - 0x3c, r->ecx);
at_4c9253:
    r->ecx = rd32(r, r->ebp - 0x30);
    r->edi = rd32(r, r->ebp - 0x40);
    r->eax = rd32(r, r->ebp - 0x34);
    r->edx = rd32(r, r->ebp - 0x38);
    r->ecx = r->ecx + r->edi;
    if ((int32_t)r->eax > (int32_t)r->edx)
    {
        goto at_4c92b2;
    }
    r->eax = rd32(r, r->ebp - 0x2c);
    wr32(r, r->ebp - 0x24, r->eax);
    r->eax = rd32(r, r->ebp - 0x38);
    r->edx = rd32(r, r->ebp - 0x34);
    r->eax = r->eax << 0x3;
    r->edx = r->edx << 0x3;
    wr32(r, r->ebp - 0x20, r->eax);
    r->eax = r->eax + 0x4;
    r->edx = r->edx + 0x4;
    wr32(r, r->ebp - 0x20, r->eax);
at_4c9283:
    r->eax = 0;
    set_low16(&r->eax, rd16(r, r->ecx));
    r->ecx = r->ecx + 0x2;
    if (r->eax == 0)
    {
        goto at_4c92a8;
    }
    r->edi = rd32(r, r->ebp - 0x28);
    r->edi = r->edi * r->eax;
    r->esi = r->esi + r->edi;
    r->edi = rd32(r, r->ebp - 0x24);
    r->edi = r->edi * r->eax;
    r->ebx = r->ebx + r->eax;
    r->eax = r->eax * r->edx;
    wr32(r, r->ebp - 0x1c, rd32(r, r->ebp - 0x1c) + r->edi);
    wr32(r, r->ebp - 0x18, rd32(r, r->ebp - 0x18) + r->eax);
at_4c92a8:
    r->edi = rd32(r, r->ebp - 0x20);
    r->edx = r->edx + 0x8;
    if ((int32_t)r->edx <= (int32_t)r->edi && !r->port->env.failed)
    {
        goto at_4c9283;
    }
at_4c92b2:
    r->ecx = rd32(r, r->ebp - 0x30);
    r->edi = rd32(r, r->ebp - 0x2c);
    r->edx = rd32(r, r->ebp - 0x3c);
    r->ecx = r->ecx + 0x40;
    r->edi = r->edi + 0x4;
    wr32(r, r->ebp - 0x30, r->ecx);
    wr32(r, r->ebp - 0x2c, r->edi);
    if ((int32_t)r->edi <= (int32_t)r->edx && !r->port->env.failed)
    {
        goto at_4c9253;
    }
at_4c92cb:
    r->eax = rd32(r, r->ebp - 0x50);
    r->edx = rd32(r, r->ebp - 0x48);
    r->ecx = rd32(r, r->ebp - 0x4c);
    r->edi = rd32(r, r->ebp - 0x58);
    r->eax = r->eax + 0x4;
    r->edx = r->edx + 0x8;
    r->ecx = r->ecx + 1;
    wr32(r, r->ebp - 0x50, r->eax);
    wr32(r, r->ebp - 0x48, r->edx);
    wr32(r, r->ebp - 0x4c, r->ecx);
    if ((int32_t)r->ecx <= (int32_t)r->edi && !r->port->env.failed)
    {
        goto at_4c9216;
    }
at_4c92ef:
    r->ecx = r->ebx;
    r->ecx = (uint32_t)((int32_t)r->ecx >> 0x1);
    r->edx = r->esi + r->ecx;
    r->eax = r->edx;
    r->edx = (uint32_t)((int32_t)r->edx >> 0x1f);
    idiv32(r, r->ebx);
    set_low8(&r->edx, (r->eax & 0xff));
    r->eax = rd32(r, r->ebp - 0x6c);
    r->eax = rd32(r, r->eax + 0x88);
    r->esi = rd32(r, r->ebp - 0x70);
    r->eax = rd32(r, r->eax);
    r->eax = r->eax + r->esi;
    wr8(r, r->eax, (r->edx & 0xff));
    r->edx = rd32(r, r->ebp - 0x1c);
    r->edx = r->edx + r->ecx;
    r->eax = r->edx;
    r->edx = (uint32_t)((int32_t)r->edx >> 0x1f);
    idiv32(r, r->ebx);
    set_low8(&r->edx, (r->eax & 0xff));
    r->eax = rd32(r, r->ebp - 0x6c);
    r->eax = rd32(r, r->eax + 0x88);
    r->eax = rd32(r, r->eax + 0x4);
    r->eax = r->eax + r->esi;
    wr8(r, r->eax, (r->edx & 0xff));
    r->edx = rd32(r, r->ebp - 0x18);
    r->edx = r->edx + r->ecx;
    r->eax = r->edx;
    r->edx = (uint32_t)((int32_t)r->edx >> 0x1f);
    idiv32(r, r->ebx);
    r->edx = rd32(r, r->ebp - 0x6c);
    r->edx = rd32(r, r->edx + 0x88);
    r->edi = rd32(r, r->ebp - 0x8c);
    r->ebx = rd32(r, r->ebp - 0x60);
    r->edx = rd32(r, r->edx + 0x8);
    r->ebx = r->ebx + 0x20;
    r->edx = r->edx + r->esi;
    r->esi = rd32(r, r->ebp - 0x68);
    wr32(r, r->ebp - 0x60, r->ebx);
    r->esi = r->esi + 1;
    wr8(r, r->edx, (r->eax & 0xff));
    wr32(r, r->ebp - 0x68, r->esi);
    if ((int32_t)r->esi < (int32_t)r->edi && !r->port->env.failed)
    {
        goto at_4c9197;
    }
at_4c9369:
    r->edx = rd32(r, r->ebp - 0x78);
    r->eax = rd32(r, r->ebp - 0x8c);
    wr32(r, r->edx + 0x84, r->eax);
    r->eax = rd32(r, r->edx);
    wr32(r, r->eax + 0x14, 0x60);
    r->eax = rd32(r, r->edx);
    r->edx = rd32(r, r->ebp - 0x8c);
    r->ecx = rd32(r, r->ebp - 0x78);
    wr32(r, r->eax + 0x18, r->edx);
    r->ecx = rd32(r, r->ecx);
    r->edx = 0x1;
    r->eax = rd32(r, r->ebp - 0x78);
    call_all(r, rd32(r, r->ecx + 0x4));
    r->eax = rd32(r, r->ebp - 0x90);
    wr32(r, r->eax + 0x1c, 0x1);
    r->edi = rd32(r, r->ebp - 0x14);
    r->esi = rd32(r, r->ebp - 0x10);
    r->edx = rd32(r, r->ebp - 0xc);
    r->ecx = rd32(r, r->ebp - 0x8);
    r->ebx = rd32(r, r->ebp - 0x4);
    return;
at_4c93c1:
    r->eax = 0x2;
    r->ecx = r->ecx + 0x20;
    wr32(r, r->ebp - 0x74, r->eax);
    wr32(r, r->ebp - 0x5c, r->ecx);
at_4c93cf:
    r->eax = rd32(r, r->ebp - 0x74);
    if ((int32_t)r->eax > (int32_t)rd32(r, r->ebp - 0x80))
    {
        goto at_4c94cb;
    }
    r->esi = rd32(r, r->ebp - 0x64);
    r->eax = rd32(r, r->ebp - 0x84);
    r->ecx = 0;
    r->ebx = 0;
    r->edx = 0;
    if ((int32_t)r->esi <= 0)
    {
        goto at_4c9406;
    }
at_4c93ee:
    if ((int32_t)r->ecx >= (int32_t)rd32(r, r->eax + 0x1c))
    {
        goto at_4c93fe;
    }
    if ((int32_t)rd32(r, r->eax + 0x18) <= (int32_t)0x0)
    {
        goto at_4c93fe;
    }
    r->ebx = r->eax;
    r->ecx = rd32(r, r->eax + 0x1c);
at_4c93fe:
    r->edx = r->edx + 1;
    r->eax = r->eax + 0x20;
    if ((int32_t)r->edx < (int32_t)r->esi && !r->port->env.failed)
    {
        goto at_4c93ee;
    }
at_4c9406:
    r->ecx = r->ebx;
    if (r->ecx == 0 && !r->port->env.failed)
    {
        goto at_4c9178;
    }
    r->ebx = rd32(r, r->ebp - 0x5c);
    r->eax = rd32(r, r->ecx + 0x4);
    wr32(r, r->ebx + 0x4, r->eax);
    r->eax = rd32(r, r->ecx + 0xc);
    wr32(r, r->ebx + 0xc, r->eax);
    r->eax = rd32(r, r->ecx + 0x14);
    wr32(r, r->ebx + 0x14, r->eax);
    r->eax = rd32(r, r->ecx);
    wr32(r, r->ebx, r->eax);
    r->eax = rd32(r, r->ecx + 0x8);
    wr32(r, r->ebx + 0x8, r->eax);
    r->eax = rd32(r, r->ecx + 0x10);
    wr32(r, r->ebx + 0x10, r->eax);
    r->esi = rd32(r, r->ecx + 0x4);
    r->eax = rd32(r, r->ecx + 0xc);
    r->edi = rd32(r, r->ecx + 0x8);
    r->edx = rd32(r, r->ecx);
    r->eax = r->eax - r->edi;
    r->esi = r->esi - r->edx;
    r->edx = r->eax * 0xc;
    r->edi = rd32(r, r->ecx + 0x10);
    r->eax = rd32(r, r->ecx + 0x14);
    r->eax = r->eax - r->edi;
    r->esi = r->esi << 0x4;
    r->eax = r->eax << 0x3;
    r->edi = r->edx;
    wr32(r, r->ebp - 0x88, r->eax);
    r->eax = 0x1;
    if ((int32_t)r->esi <= (int32_t)r->edx)
    {
        goto at_4c946a;
    }
    r->edi = r->esi;
    r->eax = 0;
at_4c946a:
    if ((int32_t)r->edi >= (int32_t)rd32(r, r->ebp - 0x88))
    {
        goto at_4c9532;
    }
at_4c9476:
    r->edx = rd32(r, r->ecx + 0x14);
    r->eax = rd32(r, r->ecx + 0x10);
    r->edx = r->edx + r->eax;
    r->eax = r->edx;
    r->edx = (uint32_t)((int32_t)r->edx >> 0x1f);
    r->eax = r->eax - r->edx;
    r->eax = (uint32_t)((int32_t)r->eax >> 0x1);
    wr32(r, r->ecx + 0x14, r->eax);
    r->eax = r->eax + 1;
    wr32(r, r->ebx + 0x10, r->eax);
at_4c948e:
    r->eax = rd32(r, r->ebp - 0x7c);
    r->esi = rd32(r, r->ebp - 0x64);
    r->edx = r->ecx;
    r->edi = rd32(r, r->ebp - 0x80);
    call_keep(r, 0x4c70f0);
    r->eax = rd32(r, r->ebp - 0x7c);
    r->edx = r->ebx;
    r->ecx = rd32(r, r->ebp - 0x74);
    call_keep(r, 0x4c70f0);
    r->esi = r->esi + 1;
    r->ebx = rd32(r, r->ebp - 0x5c);
    r->ecx = r->ecx + 0x2;
    wr32(r, r->ebp - 0x64, r->esi);
    r->ebx = r->ebx + 0x20;
    wr32(r, r->ebp - 0x74, r->ecx);
    wr32(r, r->ebp - 0x5c, r->ebx);
    if ((int32_t)r->esi < (int32_t)r->edi && !r->port->env.failed)
    {
        goto at_4c93cf;
    }
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4c9178;
at_4c94cb:
    r->esi = rd32(r, r->ebp - 0x64);
    r->eax = rd32(r, r->ebp - 0x84);
    r->ecx = 0;
    r->ebx = 0;
    r->edx = 0;
    if ((int32_t)r->esi <= 0 && !r->port->env.failed)
    {
        goto at_4c9406;
    }
at_4c94e2:
    r->edi = rd32(r, r->eax + 0x18);
    if ((int32_t)r->ecx >= (int32_t)r->edi)
    {
        goto at_4c94ed;
    }
    r->ebx = r->eax;
    r->ecx = r->edi;
at_4c94ed:
    r->edx = r->edx + 1;
    r->eax = r->eax + 0x20;
    if ((int32_t)r->edx < (int32_t)r->esi && !r->port->env.failed)
    {
        goto at_4c94e2;
    }
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4c9406;
at_4c9532:
    flags(r, F_SUB, r->eax, 0x1, 32);
    if (cond(r, CC_AE))
    {
        goto at_4c9540;
    }
    if (r->eax == 0)
    {
        goto at_4c94fa;
    }
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4c948e;
at_4c9540:
    if (cond(r, CC_BE))
    {
        goto at_4c9515;
    }
    if (r->eax == 0x2 && !r->port->env.failed)
    {
        goto at_4c9476;
    }
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4c948e;
at_4c94fa:
    r->edx = rd32(r, r->ecx + 0x4);
    r->edi = rd32(r, r->ecx);
    r->edx = r->edx + r->edi;
    r->eax = r->edx;
    r->edx = (uint32_t)((int32_t)r->edx >> 0x1f);
    r->eax = r->eax - r->edx;
    r->eax = (uint32_t)((int32_t)r->eax >> 0x1);
    wr32(r, r->ecx + 0x4, r->eax);
    r->eax = r->eax + 1;
    wr32(r, r->ebx, r->eax);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4c948e;
at_4c9515:
    r->edx = rd32(r, r->ecx + 0xc);
    r->esi = rd32(r, r->ecx + 0x8);
    r->edx = r->edx + r->esi;
    r->eax = r->edx;
    r->edx = (uint32_t)((int32_t)r->edx >> 0x1f);
    r->eax = r->eax - r->edx;
    r->eax = (uint32_t)((int32_t)r->eax >> 0x1);
    wr32(r, r->ecx + 0xc, r->eax);
    r->eax = r->eax + 1;
    wr32(r, r->ebx + 0x8, r->eax);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4c948e;
}

uint32_t vertrix_port_jpeg_quant2_select_colors_4c90e0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x98
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
    port_set32(&port, r.ebp, -0xcu, entry->edx);
    port_set32(&port, r.ebp, -0x10u, entry->esi);
    port_set32(&port, r.ebp, -0x14u, entry->edi);
    run(&r);
    return port_return(&port, r.eax, r.edx);
}
