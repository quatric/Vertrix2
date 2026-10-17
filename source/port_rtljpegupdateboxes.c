#include "port_rtljpegupdateboxes.h"

/* libjpeg update_box: shrinks a median-cut box to the histogram cells in use and computes its
 * volume and population. */

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

/* Original 0x4c70f0: libjpeg update_box: shrinks a median-cut box to the histogram cells in use and
 * computes its volume and population. Evidence: no calls. Register-for-register from the listing
 * (0x4c70f0..0x4c77db); labels are the original addresses. */
static void run(Regs *r)
{
    push_mem(r, r->ebx);
    push_mem(r, r->ecx);
    push_mem(r, r->esi);
    push_mem(r, r->edi);
    push_mem(r, r->ebp);
    r->esp = r->esp - 0xb8;
    wr32(r, r->esp + 0x10, r->edx);
    r->eax = rd32(r, r->eax + 0x1cc);
    r->eax = rd32(r, r->eax + 0x18);
    wr32(r, r->esp + 0x5c, r->eax);
    r->eax = rd32(r, r->edx);
    r->ebx = rd32(r, r->edx + 0xc);
    wr32(r, r->esp + 0x60, r->eax);
    r->eax = rd32(r, r->edx + 0x4);
    r->ebp = rd32(r, r->edx + 0x10);
    wr32(r, r->esp + 0xb0, r->eax);
    r->eax = rd32(r, r->edx + 0x8);
    r->ecx = rd32(r, r->esp + 0x60);
    wr32(r, r->esp + 0xb4, r->eax);
    r->eax = rd32(r, r->edx + 0x14);
    r->edx = rd32(r, r->esp + 0xb0);
    if ((int32_t)r->edx > (int32_t)r->ecx)
    {
        goto at_4c7518;
    }
at_4c7142:
    r->edx = rd32(r, r->esp + 0xb0);
    r->ecx = rd32(r, r->esp + 0x60);
    flags(r, F_SUB, r->edx, r->ecx, 32);
    if (cond(r, CC_LE))
    {
        goto at_4c71dd;
    }
    wr32(r, r->esp + 0x44, r->edx);
    if (cond(r, CC_L))
    {
        goto at_4c71dd;
    }
    r->edx = r->ebp + r->ebp;
    wr32(r, r->esp + 0x7c, r->edx);
    r->edx = rd32(r, r->esp + 0xb0);
    r->esi = rd32(r, r->esp + 0x5c);
    r->edx = r->edx << 0x2;
    r->edx = r->edx + r->esi;
    wr32(r, r->esp + 0x34, r->edx);
at_4c717b:
    r->edx = rd32(r, r->esp + 0xb4);
    wr32(r, r->esp + 0x9c, r->edx);
    if ((int32_t)r->ebx < (int32_t)r->edx)
    {
        goto at_4c7616;
    }
    r->ecx = rd32(r, r->esp + 0x34);
    r->edx = r->edx << 0x6;
    r->ecx = rd32(r, r->ecx);
    r->edx = r->edx + r->ecx;
    wr32(r, r->esp + 0x90, r->edx);
at_4c71a3:
    r->edx = rd32(r, r->esp + 0x90);
    r->edi = rd32(r, r->esp + 0x7c);
    r->ecx = r->ebp;
    r->edx = r->edx + r->edi;
    if ((int32_t)r->ebp > (int32_t)r->eax)
    {
        goto at_4c75ee;
    }
at_4c71ba:
    r->esi = r->edx;
    set_low16(&r->edi, rd16(r, r->esi));
    r->edx = r->edx + 0x2;
    if ((uint16_t)((r->edi & 0xffff)) == 0)
    {
        goto at_4c75e5;
    }
    r->edx = rd32(r, r->esp + 0x44);
    r->ecx = rd32(r, r->esp + 0x10);
    wr32(r, r->esp + 0xb0, r->edx);
    wr32(r, r->ecx + 0x4, r->edx);
at_4c71dd:
    r->edx = rd32(r, r->esp + 0xb4);
    flags(r, F_SUB, r->ebx, r->edx, 32);
    if (cond(r, CC_LE))
    {
        goto at_4c7290;
    }
    wr32(r, r->esp + 0x30, r->edx);
    if (cond(r, CC_L))
    {
        goto at_4c7290;
    }
    r->edx = r->ebp + r->ebp;
    wr32(r, r->esp + 0x70, r->edx);
    r->edx = rd32(r, r->esp + 0xb4);
    r->edx = r->edx << 0x6;
    wr32(r, r->esp + 0x58, r->edx);
    r->edx = r->ebx;
    r->edx = r->edx << 0x6;
    wr32(r, r->esp + 0x20, r->edx);
at_4c7215:
    r->edx = rd32(r, r->esp + 0x60);
    r->esi = rd32(r, r->esp + 0xb0);
    wr32(r, r->esp + 0x8, r->edx);
    if ((int32_t)r->edx > (int32_t)r->esi)
    {
        goto at_4c766d;
    }
    r->edx = rd32(r, r->esp + 0x58);
    wr32(r, r->esp + 0x84, r->edx);
    r->edx = rd32(r, r->esp + 0x60);
    r->esi = rd32(r, r->esp + 0x5c);
    r->edx = r->edx << 0x2;
    r->edx = r->edx + r->esi;
    wr32(r, r->esp + 0x94, r->edx);
at_4c724b:
    r->edx = rd32(r, r->esp + 0x94);
    r->edi = rd32(r, r->esp + 0x84);
    r->edx = rd32(r, r->edx);
    r->ecx = rd32(r, r->esp + 0x70);
    r->edx = r->edx + r->edi;
    r->edx = r->edx + r->ecx;
    r->ecx = r->ebp;
    if ((int32_t)r->ebp > (int32_t)r->eax)
    {
        goto at_4c7644;
    }
at_4c726d:
    r->esi = r->edx;
    set_low16(&r->edi, rd16(r, r->esi));
    r->edx = r->edx + 0x2;
    if ((uint16_t)((r->edi & 0xffff)) == 0)
    {
        goto at_4c763b;
    }
    r->edx = rd32(r, r->esp + 0x30);
    r->ecx = rd32(r, r->esp + 0x10);
    wr32(r, r->esp + 0xb4, r->edx);
    wr32(r, r->ecx + 0x8, r->edx);
at_4c7290:
    r->esi = rd32(r, r->esp + 0xb4);
    flags(r, F_SUB, r->ebx, r->esi, 32);
    if (cond(r, CC_LE))
    {
        goto at_4c732f;
    }
    wr32(r, r->esp + 0x2c, r->ebx);
    if (cond(r, CC_L))
    {
        goto at_4c732f;
    }
    r->edx = r->ebp + r->ebp;
    wr32(r, r->esp + 0x68, r->edx);
    r->edx = r->ebx;
    r->edx = r->edx << 0x6;
    wr32(r, r->esp + 0x54, r->edx);
    r->edx = r->esi;
    r->edx = r->edx << 0x6;
    wr32(r, r->esp + 0x14, r->edx);
at_4c72c3:
    r->edx = rd32(r, r->esp + 0x60);
    r->edi = rd32(r, r->esp + 0xb0);
    wr32(r, r->esp + 0xc, r->edx);
    if ((int32_t)r->edx > (int32_t)r->edi)
    {
        goto at_4c76c4;
    }
    r->edx = rd32(r, r->esp + 0x54);
    wr32(r, r->esp, r->edx);
    r->edx = rd32(r, r->esp + 0x60);
    r->edi = rd32(r, r->esp + 0x5c);
    r->edx = r->edx << 0x2;
    r->edx = r->edx + r->edi;
    wr32(r, r->esp + 0xa8, r->edx);
at_4c72f5:
    r->edx = rd32(r, r->esp + 0xa8);
    r->ecx = rd32(r, r->esp);
    r->edx = rd32(r, r->edx);
    r->edx = r->edx + r->ecx;
    r->ecx = rd32(r, r->esp + 0x68);
    r->ecx = r->ecx + r->edx;
    r->edx = r->ebp;
    if ((int32_t)r->ebp > (int32_t)r->eax)
    {
        goto at_4c769b;
    }
at_4c7313:
    r->esi = r->ecx;
    set_low16(&r->edi, rd16(r, r->esi));
    r->ecx = r->ecx + 0x2;
    if ((uint16_t)((r->edi & 0xffff)) == 0)
    {
        goto at_4c7692;
    }
    r->ecx = rd32(r, r->esp + 0x10);
    r->ebx = rd32(r, r->esp + 0x2c);
    wr32(r, r->ecx + 0xc, r->ebx);
at_4c732f:
    if ((int32_t)r->eax <= (int32_t)r->ebp)
    {
        goto at_4c73c7;
    }
    wr32(r, r->esp + 0x28, r->ebp);
    if ((int32_t)r->ebp > (int32_t)r->eax)
    {
        goto at_4c73c7;
    }
    r->edx = rd32(r, r->esp + 0xb4);
    r->edx = r->edx << 0x6;
    wr32(r, r->esp + 0x74, r->edx);
    r->edx = r->ebp + r->ebp;
    wr32(r, r->esp + 0x50, r->edx);
    r->edx = r->eax + r->eax;
    wr32(r, r->esp + 0x1c, r->edx);
at_4c7360:
    r->edx = rd32(r, r->esp + 0x60);
    r->esi = rd32(r, r->esp + 0xb0);
    wr32(r, r->esp + 0xa0, r->edx);
    if ((int32_t)r->edx > (int32_t)r->esi)
    {
        goto at_4c7716;
    }
    r->edx = rd32(r, r->esp + 0x50);
    r->esi = rd32(r, r->esp + 0x60);
    r->edi = rd32(r, r->esp + 0x5c);
    r->esi = r->esi << 0x2;
    wr32(r, r->esp + 0x88, r->edx);
    r->esi = r->esi + r->edi;
at_4c7392:
    r->ecx = rd32(r, r->esp + 0x74);
    r->edx = rd32(r, r->esi);
    r->edx = r->edx + r->ecx;
    r->ecx = rd32(r, r->esp + 0x88);
    r->ecx = r->ecx + r->edx;
    r->edx = rd32(r, r->esp + 0xb4);
    if ((int32_t)r->ebx < (int32_t)r->edx)
    {
        goto at_4c76f5;
    }
at_4c73b2:
    if ((uint16_t)rd16(r, r->ecx) == (uint16_t)0x0)
    {
        goto at_4c76e9;
    }
    r->ecx = rd32(r, r->esp + 0x10);
    r->ebp = rd32(r, r->esp + 0x28);
    wr32(r, r->ecx + 0x10, r->ebp);
at_4c73c7:
    flags(r, F_SUB, r->eax, r->ebp, 32);
    if (cond(r, CC_LE))
    {
        goto at_4c7462;
    }
    wr32(r, r->esp + 0x24, r->eax);
    if (cond(r, CC_L))
    {
        goto at_4c7462;
    }
    r->edx = rd32(r, r->esp + 0xb4);
    r->edx = r->edx << 0x6;
    wr32(r, r->esp + 0x64, r->edx);
    r->edx = r->eax + r->eax;
    wr32(r, r->esp + 0x4c, r->edx);
    r->edx = r->ebp + r->ebp;
    wr32(r, r->esp + 0x18, r->edx);
at_4c73f6:
    r->esi = rd32(r, r->esp + 0x60);
    if ((int32_t)r->esi > (int32_t)rd32(r, r->esp + 0xb0))
    {
        goto at_4c7768;
    }
    r->edx = rd32(r, r->esp + 0x4c);
    r->edi = rd32(r, r->esp + 0x5c);
    wr32(r, r->esp + 0x80, r->edx);
    r->edx = r->esi * 4;
    r->edx = r->edx + r->edi;
    wr32(r, r->esp + 0x98, r->edx);
at_4c7426:
    r->edx = rd32(r, r->esp + 0x98);
    r->ecx = rd32(r, r->esp + 0x64);
    r->edx = rd32(r, r->edx);
    r->edi = rd32(r, r->esp + 0x80);
    r->edx = r->edx + r->ecx;
    r->ecx = rd32(r, r->esp + 0xb4);
    r->edx = r->edx + r->edi;
    if ((int32_t)r->ebx < (int32_t)r->ecx)
    {
        goto at_4c7747;
    }
at_4c744d:
    if ((uint16_t)rd16(r, r->edx) == (uint16_t)0x0)
    {
        goto at_4c773b;
    }
    r->ecx = rd32(r, r->esp + 0x10);
    r->eax = rd32(r, r->esp + 0x24);
    wr32(r, r->ecx + 0x14, r->eax);
at_4c7462:
    r->esi = rd32(r, r->esp + 0xb0);
    r->esi = r->esi - rd32(r, r->esp + 0x60);
    r->esi = r->esi << 0x4;
    r->esi = r->esi * r->esi;
    r->edi = rd32(r, r->esp + 0xb4);
    r->ecx = r->ebx;
    r->ecx = r->ecx - r->edi;
    r->edx = r->ecx * 4;
    r->edx = r->edx - r->ecx;
    r->edx = r->edx << 0x2;
    r->edx = r->edx * r->edx;
    r->ecx = r->eax;
    r->ecx = r->ecx - r->ebp;
    r->ecx = r->ecx << 0x3;
    r->ecx = r->ecx * r->ecx;
    r->edx = r->edx + r->esi;
    r->edx = r->edx + r->ecx;
    r->ecx = rd32(r, r->esp + 0x10);
    r->esi = 0;
    wr32(r, r->ecx + 0x18, r->edx);
    r->edx = rd32(r, r->esp + 0x60);
    r->ecx = rd32(r, r->esp + 0xb0);
    wr32(r, r->esp + 0x38, r->edx);
    if ((int32_t)r->edx > (int32_t)r->ecx)
    {
        goto at_4c7505;
    }
    r->edx = r->ebp + r->ebp;
    wr32(r, r->esp + 0x6c, r->edx);
    r->edx = rd32(r, r->esp + 0x60);
    r->edi = rd32(r, r->esp + 0x5c);
    r->edx = r->edx << 0x2;
    r->edx = r->edx + r->edi;
    wr32(r, r->esp + 0x3c, r->edx);
at_4c74d0:
    r->edx = rd32(r, r->esp + 0xb4);
    wr32(r, r->esp + 0x8c, r->edx);
    if ((int32_t)r->ebx >= (int32_t)r->edx)
    {
        goto at_4c77cc;
    }
at_4c74e6:
    r->edi = rd32(r, r->esp + 0x3c);
    r->edx = rd32(r, r->esp + 0x38);
    r->ecx = rd32(r, r->esp + 0xb0);
    r->edi = r->edi + 0x4;
    r->edx = r->edx + 1;
    wr32(r, r->esp + 0x3c, r->edi);
    wr32(r, r->esp + 0x38, r->edx);
    if ((int32_t)r->edx <= (int32_t)r->ecx && !r->port->env.failed)
    {
        goto at_4c74d0;
    }
at_4c7505:
    r->eax = rd32(r, r->esp + 0x10);
    wr32(r, r->eax + 0x1c, r->esi);
    r->esp = r->esp + 0xb8;
    r->ebp = pop_mem(r);
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    r->ecx = pop_mem(r);
    r->ebx = pop_mem(r);
    return;
at_4c7518:
    wr32(r, r->esp + 0x48, r->ecx);
    if ((int32_t)r->ecx > (int32_t)r->edx && !r->port->env.failed)
    {
        goto at_4c7142;
    }
    r->edx = r->ebp + r->ebp;
    r->esi = rd32(r, r->esp + 0x5c);
    wr32(r, r->esp + 0x78, r->edx);
    r->edx = r->ecx * 4;
    r->edx = r->edx + r->esi;
    wr32(r, r->esp + 0x40, r->edx);
at_4c753d:
    r->edx = rd32(r, r->esp + 0xb4);
    wr32(r, r->esp + 0xac, r->edx);
    if ((int32_t)r->ebx < (int32_t)r->edx)
    {
        goto at_4c7594;
    }
    r->ecx = rd32(r, r->esp + 0x40);
    r->edx = r->edx << 0x6;
    r->ecx = rd32(r, r->ecx);
    r->edx = r->edx + r->ecx;
    wr32(r, r->esp + 0xa4, r->edx);
at_4c7561:
    r->edx = rd32(r, r->esp + 0xa4);
    r->edi = rd32(r, r->esp + 0x78);
    r->ecx = r->ebp;
    r->edx = r->edx + r->edi;
    if ((int32_t)r->ebp > (int32_t)r->eax)
    {
        goto at_4c75b8;
    }
at_4c7574:
    r->esi = r->edx;
    set_low16(&r->edi, rd16(r, r->esi));
    r->edx = r->edx + 0x2;
    if ((uint16_t)((r->edi & 0xffff)) == 0)
    {
        goto at_4c75de;
    }
    r->edx = rd32(r, r->esp + 0x48);
    r->ecx = rd32(r, r->esp + 0x10);
    wr32(r, r->esp + 0x60, r->edx);
    wr32(r, r->ecx, r->edx);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4c7142;
at_4c7594:
    r->edi = rd32(r, r->esp + 0x40);
    r->edx = rd32(r, r->esp + 0x48);
    r->ecx = rd32(r, r->esp + 0xb0);
    r->edi = r->edi + 0x4;
    r->edx = r->edx + 1;
    wr32(r, r->esp + 0x40, r->edi);
    wr32(r, r->esp + 0x48, r->edx);
    if ((int32_t)r->edx <= (int32_t)r->ecx && !r->port->env.failed)
    {
        goto at_4c753d;
    }
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4c7142;
at_4c75b8:
    r->edx = rd32(r, r->esp + 0xa4);
    r->ecx = rd32(r, r->esp + 0xac);
    r->edx = r->edx + 0x40;
    r->ecx = r->ecx + 1;
    wr32(r, r->esp + 0xa4, r->edx);
    wr32(r, r->esp + 0xac, r->ecx);
    if ((int32_t)r->ebx >= (int32_t)r->ecx && !r->port->env.failed)
    {
        goto at_4c7561;
    }
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4c7594;
at_4c75de:
    r->ecx = r->ecx + 1;
    if ((int32_t)r->ecx <= (int32_t)r->eax && !r->port->env.failed)
    {
        goto at_4c7574;
    }
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4c75b8;
at_4c75e5:
    r->ecx = r->ecx + 1;
    if ((int32_t)r->ecx <= (int32_t)r->eax && !r->port->env.failed)
    {
        goto at_4c71ba;
    }
at_4c75ee:
    r->edx = rd32(r, r->esp + 0x90);
    r->ecx = rd32(r, r->esp + 0x9c);
    r->edx = r->edx + 0x40;
    r->ecx = r->ecx + 1;
    wr32(r, r->esp + 0x90, r->edx);
    wr32(r, r->esp + 0x9c, r->ecx);
    if ((int32_t)r->ebx >= (int32_t)r->ecx && !r->port->env.failed)
    {
        goto at_4c71a3;
    }
at_4c7616:
    r->edi = rd32(r, r->esp + 0x34);
    r->edx = rd32(r, r->esp + 0x44);
    r->ecx = rd32(r, r->esp + 0x60);
    r->edi = r->edi - 0x4;
    r->edx = r->edx - 1;
    wr32(r, r->esp + 0x34, r->edi);
    wr32(r, r->esp + 0x44, r->edx);
    if ((int32_t)r->edx >= (int32_t)r->ecx && !r->port->env.failed)
    {
        goto at_4c717b;
    }
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4c71dd;
at_4c763b:
    r->ecx = r->ecx + 1;
    if ((int32_t)r->ecx <= (int32_t)r->eax && !r->port->env.failed)
    {
        goto at_4c726d;
    }
at_4c7644:
    r->edi = rd32(r, r->esp + 0x94);
    r->edx = rd32(r, r->esp + 0x8);
    r->ecx = rd32(r, r->esp + 0xb0);
    r->edi = r->edi + 0x4;
    r->edx = r->edx + 1;
    wr32(r, r->esp + 0x94, r->edi);
    wr32(r, r->esp + 0x8, r->edx);
    if ((int32_t)r->edx <= (int32_t)r->ecx && !r->port->env.failed)
    {
        goto at_4c724b;
    }
at_4c766d:
    r->esi = rd32(r, r->esp + 0x58);
    r->edi = rd32(r, r->esp + 0x30);
    r->ecx = rd32(r, r->esp + 0x20);
    r->esi = r->esi + 0x40;
    r->edi = r->edi + 1;
    wr32(r, r->esp + 0x58, r->esi);
    wr32(r, r->esp + 0x30, r->edi);
    if ((int32_t)r->esi <= (int32_t)r->ecx && !r->port->env.failed)
    {
        goto at_4c7215;
    }
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4c7290;
at_4c7692:
    r->edx = r->edx + 1;
    if ((int32_t)r->edx <= (int32_t)r->eax && !r->port->env.failed)
    {
        goto at_4c7313;
    }
at_4c769b:
    r->edx = rd32(r, r->esp + 0xa8);
    r->ecx = rd32(r, r->esp + 0xc);
    r->esi = rd32(r, r->esp + 0xb0);
    r->edx = r->edx + 0x4;
    r->ecx = r->ecx + 1;
    wr32(r, r->esp + 0xa8, r->edx);
    wr32(r, r->esp + 0xc, r->ecx);
    if ((int32_t)r->ecx <= (int32_t)r->esi && !r->port->env.failed)
    {
        goto at_4c72f5;
    }
at_4c76c4:
    r->edx = rd32(r, r->esp + 0x54);
    r->ecx = rd32(r, r->esp + 0x2c);
    r->esi = rd32(r, r->esp + 0x14);
    r->edx = r->edx - 0x40;
    r->ecx = r->ecx - 1;
    wr32(r, r->esp + 0x54, r->edx);
    wr32(r, r->esp + 0x2c, r->ecx);
    if ((int32_t)r->edx >= (int32_t)r->esi && !r->port->env.failed)
    {
        goto at_4c72c3;
    }
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4c732f;
at_4c76e9:
    r->edx = r->edx + 1;
    r->ecx = r->ecx + 0x40;
    if ((int32_t)r->edx <= (int32_t)r->ebx && !r->port->env.failed)
    {
        goto at_4c73b2;
    }
at_4c76f5:
    r->edi = rd32(r, r->esp + 0xa0);
    r->ecx = rd32(r, r->esp + 0xb0);
    r->edi = r->edi + 1;
    r->esi = r->esi + 0x4;
    wr32(r, r->esp + 0xa0, r->edi);
    if ((int32_t)r->edi <= (int32_t)r->ecx && !r->port->env.failed)
    {
        goto at_4c7392;
    }
at_4c7716:
    r->esi = rd32(r, r->esp + 0x50);
    r->edi = rd32(r, r->esp + 0x28);
    r->ecx = rd32(r, r->esp + 0x1c);
    r->esi = r->esi + 0x2;
    r->edi = r->edi + 1;
    wr32(r, r->esp + 0x50, r->esi);
    wr32(r, r->esp + 0x28, r->edi);
    if ((int32_t)r->esi <= (int32_t)r->ecx && !r->port->env.failed)
    {
        goto at_4c7360;
    }
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4c73c7;
at_4c773b:
    r->ecx = r->ecx + 1;
    r->edx = r->edx + 0x40;
    if ((int32_t)r->ecx <= (int32_t)r->ebx && !r->port->env.failed)
    {
        goto at_4c744d;
    }
at_4c7747:
    r->edx = rd32(r, r->esp + 0x98);
    r->ecx = rd32(r, r->esp + 0xb0);
    r->edx = r->edx + 0x4;
    r->esi = r->esi + 1;
    wr32(r, r->esp + 0x98, r->edx);
    if ((int32_t)r->esi <= (int32_t)r->ecx && !r->port->env.failed)
    {
        goto at_4c7426;
    }
at_4c7768:
    r->edx = rd32(r, r->esp + 0x4c);
    r->ecx = rd32(r, r->esp + 0x24);
    r->esi = rd32(r, r->esp + 0x18);
    r->edx = r->edx - 0x2;
    r->ecx = r->ecx - 1;
    wr32(r, r->esp + 0x4c, r->edx);
    wr32(r, r->esp + 0x24, r->ecx);
    if ((int32_t)r->edx >= (int32_t)r->esi && !r->port->env.failed)
    {
        goto at_4c73f6;
    }
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4c7462;
at_4c778d:
    r->ecx = rd32(r, r->esp + 0x4);
    r->edi = rd32(r, r->esp + 0x8c);
    r->ecx = r->ecx + 0x40;
    r->edi = r->edi + 1;
    wr32(r, r->esp + 0x4, r->ecx);
    wr32(r, r->esp + 0x8c, r->edi);
    if ((int32_t)r->ebx < (int32_t)r->edi && !r->port->env.failed)
    {
        goto at_4c74e6;
    }
at_4c77af:
    r->edx = rd32(r, r->esp + 0x4);
    r->edx = r->edx + rd32(r, r->esp + 0x6c);
    r->ecx = r->ebp;
    flags(r, F_SUB, r->ebp, r->eax, 32);
at_4c77bb:
    if (cond(r, CC_G) && !r->port->env.failed)
    {
        goto at_4c778d;
    }
    if ((uint16_t)rd16(r, r->edx) == (uint16_t)0x0)
    {
        goto at_4c77c4;
    }
    r->esi = r->esi + 1;
at_4c77c4:
    r->ecx = r->ecx + 1;
    r->edx = r->edx + 0x2;
    flags(r, F_SUB, r->ecx, r->eax, 32);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4c77bb;
at_4c77cc:
    r->ecx = rd32(r, r->esp + 0x3c);
    r->edx = r->edx << 0x6;
    r->ecx = rd32(r, r->ecx);
    r->edx = r->edx + r->ecx;
    wr32(r, r->esp + 0x4, r->edx);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4c77af;
}

uint32_t vertrix_port_jpeg_update_box_4c70f0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0xe0
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
