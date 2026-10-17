#include "port_rtlactorclips.h"

/* Draws an actor's image clipped to the view: loads its surface (+0xb4) and position (+0xe, +0x16)
 * into the blit globals at 0x5bb7xx and copies the visible part. */

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

/* Original 0x4b0b70: Draws an actor's image clipped to the view: loads its surface (+0xb4) and
 * position (+0xe, +0x16) into the blit globals at 0x5bb7xx and copies the visible part. Evidence:
 * reads 0x5bb700, 0x5bb764, 0x5bb7d4, 0x5bb7d8, 0x5bb7a4, 0x5bb734, 0x5bb7a6, 0x5bb738, 0x5bb7b4,
 * 0x5bb7b6, 0x5bb7b0, 0x5bb7a0, 0x5bb7b2, 0x5bb7ae, 0x5bb6e4, 0x5bb6e6 and more; writes 0x5bb734,
 * 0x5bb7a4, 0x5bb740, 0x5bb7a6, 0x5bb742, 0x5bb7a0, 0x5bbffe, 0x5bb7ae, 0x5bb738, 0x5bb7b0,
 * 0x5bb7b2, 0x5bb731, 0x5bb7b4, 0x5bb6e6, 0x5bb6e4, 0x5bb7b6 and more. Register-for-register from
 * the listing (0x4b0b70..0x4b14ad); labels are the original addresses. */
static void run(Regs *r)
{
    push_mem(r, r->ecx);
    push_mem(r, r->esi);
    push_mem(r, r->edi);
    push_mem(r, r->ebp);
    r->esp = r->esp - 0x38;
    set_low16(&r->ecx, rd16(r, 0x5bb700));
    r->esi = rd32(r, 0x5bb764);
    r->edi = rd32(r, 0x5bb7d4);
    r->ebp = rd32(r, 0x5bb7d8);
    wr32(r, r->esp + 0x4, r->eax);
    wr16(r, r->esp + 0x2c, (r->edx & 0xffff));
    wr16(r, r->esp + 0x30, (r->ebx & 0xffff));
    r->eax = rd32(r, r->eax + 0xb4);
    wr32(r, 0x5bb734, r->eax);
    r->eax = rd32(r, r->esp + 0x4);
    set_low16(&r->eax, rd16(r, r->eax + 0xe));
    wr16(r, 0x5bb7a4, (r->eax & 0xffff));
    wr16(r, 0x5bb740, (r->eax & 0xffff));
    r->eax = rd32(r, r->esp + 0x4);
    set_low16(&r->eax, rd16(r, r->eax + 0x16));
    wr16(r, 0x5bb7a6, (r->eax & 0xffff));
    wr16(r, 0x5bb742, (r->eax & 0xffff));
    set_low16(&r->eax, rd16(r, 0x5bb7a4));
    wr16(r, 0x5bb7a0, (r->eax & 0xffff));
    r->eax = rd32(r, r->esp + 0x4);
    set_low8(&r->eax, rd8(r, r->eax + 0x8e));
    wr8(r, 0x5bbffe, (r->eax & 0xff));
    r->eax = rd32(r, r->esp + 0x4);
    set_low16(&r->eax, rd16(r, r->eax + 0x1e));
    wr16(r, 0x5bb7ae, (r->eax & 0xffff));
    r->eax = rd32(r, r->esp + 0x4);
    r->edx = rd32(r, 0x5bb734);
    set_low8(&r->eax, rd8(r, r->eax + 0x44));
    set_low16(&r->ebx, rd16(r, 0x5bb7a6));
    wr8(r, 0x5bb738, (r->eax & 0xff));
    if (r->edx == 0)
    {
        goto at_4b0ef2;
    }
    r->eax = r->edx;
    set_low16(&r->edx, rd16(r, r->edx + 0xc));
    wr16(r, 0x5bb7b0, (r->edx & 0xffff));
    set_low16(&r->edx, rd16(r, r->eax + 0x10));
    set_low8(&r->eax, rd8(r, r->eax + 0x27));
    wr16(r, 0x5bb7b2, (r->edx & 0xffff));
    wr8(r, 0x5bb731, (r->eax & 0xff));
at_4b0c3b:
    if ((uint8_t)rd8(r, 0x5bb738) != (uint8_t)0x10)
    {
        goto at_4b0fc5;
    }
    r->edx = rd32(r, 0x5bb734);
    if (r->edx != 0)
    {
        goto at_4b0f07;
    }
    r->eax = rd32(r, r->esp + 0x4);
    set_low16(&r->eax, rd16(r, r->eax + 0xf4));
    r->edx = 0;
    wr16(r, 0x5bb7b4, (r->eax & 0xffff));
    r->eax = rd32(r, r->esp + 0x4);
    wr16(r, 0x5bb6e6, (r->edx & 0xffff));
    set_low16(&r->eax, rd16(r, r->eax + 0xf8));
    wr16(r, 0x5bb6e4, (r->edx & 0xffff));
    wr16(r, 0x5bb7b6, (r->eax & 0xffff));
    set_low16(&r->eax, rd16(r, 0x5bb7b4));
    set_high8(&r->edx, 0);
    wr16(r, 0x5bb6e0, (r->eax & 0xffff));
    set_low16(&r->eax, rd16(r, 0x5bb7b6));
    wr8(r, 0x5bbfff, ((r->edx >> 8) & 0xff));
    wr16(r, 0x5bb6e2, (r->eax & 0xffff));
at_4b0ca8:
    set_low16(&r->eax, rd16(r, 0x5bb7b0));
    set_low16(&r->edx, rd16(r, 0x5bb7a0));
    r->edx = r->edx - r->eax;
    set_low16(&r->eax, rd16(r, 0x5bb7b2));
    wr16(r, 0x5bb7a0, (r->edx & 0xffff));
    r->ebx = r->ebx - r->eax;
    set_low16(&r->eax, rd16(r, 0x5bb7ae));
    wr16(r, 0x5bb6ec, (r->edx & 0xffff));
    r->ebx = r->ebx - r->eax;
    set_low16(&r->eax, rd16(r, 0x5bb6e4));
    wr16(r, 0x5bb6ee, (r->ebx & 0xffff));
    r->edx = r->edx + r->eax;
    set_low16(&r->eax, rd16(r, 0x5bb6e6));
    wr16(r, 0x5bb7a0, (r->edx & 0xffff));
    r->ebx = r->ebx + r->eax;
    r->eax = r->edx;
    set_low16(&r->eax, (r->eax & 0xffff) + rd16(r, 0x5bb6e0));
    r->eax = r->eax - 1;
    set_low16(&r->edx, rd16(r, 0x5bb6e2));
    wr16(r, 0x5bb748, (r->eax & 0xffff));
    r->eax = r->ebx;
    r->eax = r->eax + r->edx;
    r->eax = r->eax - 1;
    wr16(r, 0x5bb74a, (r->eax & 0xffff));
    if ((uint8_t)rd8(r, 0x5bbffe) == (uint8_t)0x2)
    {
        goto at_4b0e07;
    }
    set_low16(&r->eax, rd16(r, 0x5b9c90));
    r->eax = r->eax - 1;
    wr32(r, r->esp + 0x24, r->eax);
    set_low16(&r->eax, rd16(r, 0x5b9c8e));
    r->eax = r->eax - 1;
    wr32(r, r->esp + 0x1c, r->eax);
    set_high8(&r->eax, rd8(r, 0x5bbffe));
    if ((uint8_t)(((r->eax >> 8) & 0xff)) != (uint8_t)0x1)
    {
        goto at_4b0f58;
    }
    r->eax = 0;
at_4b0d49:
    wr16(r, 0x5bbff6, (r->eax & 0xffff));
    r->eax = rd32(r, r->esp + 0x1c);
    r->edx = 0;
    wr16(r, 0x5bbff8, (r->eax & 0xffff));
    r->eax = rd32(r, r->esp + 0x24);
    wr16(r, 0x5bbffa, (r->edx & 0xffff));
at_4b0d66:
    wr16(r, 0x5bbffc, (r->eax & 0xffff));
at_4b0d6c:
    set_low16(&r->eax, rd16(r, 0x5bb7a0));
    if ((int16_t)((r->eax & 0xffff)) > (int16_t)rd16(r, 0x5bbff8))
    {
        goto at_4b0faf;
    }
    set_low16(&r->eax, rd16(r, 0x5bb748));
    if ((int16_t)((r->eax & 0xffff)) < (int16_t)rd16(r, 0x5bbff6))
    {
        goto at_4b0faf;
    }
    if ((int16_t)((r->ebx & 0xffff)) > (int16_t)rd16(r, 0x5bbffc))
    {
        goto at_4b0faf;
    }
    set_low16(&r->eax, rd16(r, 0x5bb74a));
    set_low16(&r->edx, rd16(r, 0x5bbffa));
    if ((int16_t)((r->eax & 0xffff)) < (int16_t)((r->edx & 0xffff)))
    {
        goto at_4b0faf;
    }
    if ((int16_t)((r->ebx & 0xffff)) >= (int16_t)((r->edx & 0xffff)))
    {
        goto at_4b0dbc;
    }
    r->ebx = r->edx;
at_4b0dbc:
    set_low16(&r->eax, rd16(r, 0x5bb7a0));
    set_low16(&r->edx, rd16(r, 0x5bbff6));
    if ((int16_t)((r->eax & 0xffff)) >= (int16_t)((r->edx & 0xffff)))
    {
        goto at_4b0dd5;
    }
    wr16(r, 0x5bb7a0, (r->edx & 0xffff));
at_4b0dd5:
    set_low16(&r->eax, rd16(r, 0x5bb74a));
    set_low16(&r->edx, rd16(r, 0x5bbffc));
    if ((int16_t)((r->eax & 0xffff)) <= (int16_t)((r->edx & 0xffff)))
    {
        goto at_4b0dee;
    }
    wr16(r, 0x5bb74a, (r->edx & 0xffff));
at_4b0dee:
    set_low16(&r->eax, rd16(r, 0x5bb748));
    set_low16(&r->edx, rd16(r, 0x5bbff8));
    if ((int16_t)((r->eax & 0xffff)) <= (int16_t)((r->edx & 0xffff)))
    {
        goto at_4b0e07;
    }
    wr16(r, 0x5bb748, (r->edx & 0xffff));
at_4b0e07:
    r->eax = rd32(r, r->esp + 0x2c);
    wr16(r, 0x5bb6e8, (r->eax & 0xffff));
    r->eax = rd32(r, r->esp + 0x30);
    set_low16(&r->edx, rd16(r, 0x5bb7a0));
    wr16(r, 0x5bb6ea, (r->eax & 0xffff));
    if ((int16_t)((r->edx & 0xffff)) > (int16_t)rd16(r, r->esp + 0x2c))
    {
        goto at_4b0fba;
    }
    if ((int16_t)((r->ebx & 0xffff)) > (int16_t)rd16(r, r->esp + 0x30))
    {
        goto at_4b0fba;
    }
    r->eax = rd32(r, r->esp + 0x2c);
    if ((int16_t)((r->eax & 0xffff)) > (int16_t)rd16(r, 0x5bb748))
    {
        goto at_4b0fba;
    }
    r->eax = rd32(r, r->esp + 0x30);
    if ((int16_t)((r->eax & 0xffff)) > (int16_t)rd16(r, 0x5bb74a))
    {
        goto at_4b0fba;
    }
    if ((uint8_t)rd8(r, 0x5bbfff) != (uint8_t)0x1)
    {
        goto at_4b14a8;
    }
    r->edx = rd32(r, r->esp + 0x2e);
    r->eax = rd32(r, 0x5bb6ec);
    r->edx = (uint32_t)((int32_t)r->edx >> 0x10);
    r->eax = (uint32_t)((int32_t)r->eax >> 0x10);
    r->edx = r->edx - r->eax;
    r->eax = 0;
    set_low16(&r->eax, rd16(r, 0x5bb7b4));
    r->edx = r->edx * r->eax;
    r->eax = rd32(r, 0x5bb734);
    r->edx = r->edx << 0x2;
    r->eax = rd32(r, r->eax);
    r->edx = r->edx + r->eax;
    r->eax = rd32(r, r->esp + 0x2a);
    r->eax = (uint32_t)((int32_t)r->eax >> 0x10);
    wr32(r, r->esp + 0x8, r->eax);
    r->eax = rd32(r, 0x5bb6ea);
    r->esi = rd32(r, r->esp + 0x8);
    r->eax = (uint32_t)((int32_t)r->eax >> 0x10);
    r->esi = r->esi - r->eax;
    r->esi = r->esi << 0x2;
    r->esi = r->esi + r->edx;
    r->eax = rd32(r, r->esi);
    r->eax = r->eax >> 0x18;
    wr32(r, r->esp + 0x8, r->eax);
    set_low8(&r->eax, rd8(r, r->esp + 0x8));
at_4b0eba:
    if ((uint8_t)((r->eax & 0xff)) != 0)
    {
        goto at_4b14a8;
    }
at_4b0ec2:
    wr8(r, r->esp + 0x34, (r->eax & 0xff));
at_4b0ec6:
    set_low8(&r->eax, rd8(r, r->esp + 0x34));
    wr16(r, 0x5bb7a2, (r->ebx & 0xffff));
    wr32(r, 0x5bb7d8, r->ebp);
    wr32(r, 0x5bb7d4, r->edi);
    wr32(r, 0x5bb764, r->esi);
    wr16(r, 0x5bb700, (r->ecx & 0xffff));
    r->esp = r->esp + 0x38;
    r->ebp = pop_mem(r);
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    r->ecx = pop_mem(r);
    return;
at_4b0ef2:
    r->edx = 0;
    wr16(r, 0x5bb7b2, (r->edx & 0xffff));
    wr16(r, 0x5bb7b0, (r->edx & 0xffff));
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4b0c3b;
at_4b0f07:
    r->eax = r->edx;
    set_low16(&r->edx, rd16(r, r->edx + 0x4));
    wr16(r, 0x5bb7b4, (r->edx & 0xffff));
    set_low16(&r->edx, rd16(r, r->eax + 0x8));
    wr16(r, 0x5bb7b6, (r->edx & 0xffff));
    set_low16(&r->edx, rd16(r, r->eax + 0x1c));
    wr16(r, 0x5bb6e0, (r->edx & 0xffff));
    set_low16(&r->edx, rd16(r, r->eax + 0x20));
    wr16(r, 0x5bb6e2, (r->edx & 0xffff));
    set_low16(&r->edx, rd16(r, r->eax + 0x14));
    wr16(r, 0x5bb6e4, (r->edx & 0xffff));
    set_low16(&r->edx, rd16(r, r->eax + 0x18));
    set_low8(&r->eax, rd8(r, r->eax + 0x25));
    wr16(r, 0x5bb6e6, (r->edx & 0xffff));
    wr8(r, 0x5bbfff, (r->eax & 0xff));
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4b0ca8;
at_4b0f58:
    if ((uint8_t)(((r->eax >> 8) & 0xff)) != 0)
    {
        goto at_4b0f63;
    }
    set_low8(&r->eax, 0);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4b0d49;
at_4b0f63:
    if ((uint8_t)(((r->eax >> 8) & 0xff)) != (uint8_t)0x3 && !r->port->env.failed)
    {
        goto at_4b0d6c;
    }
    r->eax = rd32(r, r->esp + 0x4);
    set_low16(&r->eax, rd16(r, r->eax + 0xa8));
    wr16(r, 0x5bbff6, (r->eax & 0xffff));
    r->eax = rd32(r, r->esp + 0x4);
    set_low16(&r->eax, rd16(r, r->eax + 0xaa));
    wr16(r, 0x5bbff8, (r->eax & 0xffff));
    r->eax = rd32(r, r->esp + 0x4);
    set_low16(&r->eax, rd16(r, r->eax + 0xac));
    wr16(r, 0x5bbffa, (r->eax & 0xffff));
    r->eax = rd32(r, r->esp + 0x4);
    set_low16(&r->eax, rd16(r, r->eax + 0xae));
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4b0d66;
at_4b0faf:
    set_high8(&r->edx, 0);
    wr8(r, r->esp + 0x34, ((r->edx >> 8) & 0xff));
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4b0ec6;
at_4b0fba:
    set_low8(&r->edx, 0);
    wr8(r, r->esp + 0x34, (r->edx & 0xff));
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4b0ec6;
at_4b0fc5:
    r->eax = rd32(r, 0x5bb734);
    if (r->eax == 0 && !r->port->env.failed)
    {
        goto at_4b0fba;
    }
    set_low16(&r->edx, rd16(r, r->eax + 0x4));
    wr16(r, 0x5bb7b4, (r->edx & 0xffff));
    set_low16(&r->edx, rd16(r, r->eax + 0x8));
    wr16(r, 0x5bb7b6, (r->edx & 0xffff));
    set_low16(&r->edx, rd16(r, r->eax + 0x1c));
    wr16(r, 0x5bb6e0, (r->edx & 0xffff));
    set_low16(&r->edx, rd16(r, r->eax + 0x20));
    wr16(r, 0x5bb6e2, (r->edx & 0xffff));
    set_low16(&r->edx, rd16(r, r->eax + 0x14));
    wr16(r, 0x5bb6e4, (r->edx & 0xffff));
    set_low16(&r->edx, rd16(r, r->eax + 0x18));
    wr16(r, 0x5bb6e6, (r->edx & 0xffff));
    set_low8(&r->edx, rd8(r, r->eax + 0x25));
    wr8(r, 0x5bbfff, (r->edx & 0xff));
    set_low8(&r->eax, rd8(r, r->eax + 0x27));
    set_low16(&r->edx, rd16(r, 0x5bb7b0));
    wr8(r, 0x5bb731, (r->eax & 0xff));
    set_low16(&r->eax, rd16(r, 0x5bb7a0));
    r->eax = r->eax - r->edx;
    set_low16(&r->edx, rd16(r, 0x5bb6e4));
    r->edx = r->edx + r->eax;
    set_low16(&r->eax, rd16(r, 0x5bb7b2));
    wr16(r, 0x5bb7a0, (r->edx & 0xffff));
    set_low16(&r->edx, rd16(r, 0x5bb7ae));
    r->ebx = r->ebx - r->eax;
    set_low16(&r->eax, rd16(r, 0x5bb6e6));
    r->ebx = r->ebx - r->edx;
    set_low16(&r->edx, rd16(r, 0x5bb6e0));
    r->ebx = r->ebx + r->eax;
    set_low16(&r->eax, rd16(r, 0x5bb7a0));
    r->eax = r->eax + r->edx;
    r->eax = r->eax - 1;
    set_low16(&r->edx, rd16(r, 0x5bb6e2));
    wr16(r, 0x5bb748, (r->eax & 0xffff));
    r->eax = r->ebx;
    r->eax = r->eax + r->edx;
    r->eax = r->eax - 1;
    wr16(r, 0x5bb74a, (r->eax & 0xffff));
    r->eax = 0;
    r->edx = 0;
    set_low16(&r->eax, rd16(r, 0x5bb7b4));
    set_low8(&r->edx, rd8(r, 0x5bb738));
    wr32(r, r->esp + 0x18, r->eax);
    r->eax = (uint32_t)((int32_t)r->eax >> 0x4);
    r->eax = r->eax * r->edx;
    wr16(r, 0x5bb6f8, (r->eax & 0xffff));
    r->eax = r->edx;
    r->eax = r->eax << 0x4;
    wr32(r, r->esp + 0x8, r->eax);
    set_low16(&r->eax, rd16(r, 0x5bb7b4));
    set_high8(&r->eax, 0);
    wr32(r, r->esp + 0xc, r->edx);
    set_low8(&r->eax, (r->eax & 0xff) & 0xf);
    r->edx = rd32(r, r->esp + 0x8);
    r->eax = r->eax & 0xffff;
    r->eax = r->eax + r->edx;
    set_low8(&r->eax, rd8(r, r->eax + 0x5c1b00));
    set_low16(&r->edx, rd16(r, 0x5bb6f8));
    set_high8(&r->eax, 0);
    r->edx = r->edx + r->eax;
    r->eax = 0;
    wr16(r, 0x5bb6f8, (r->edx & 0xffff));
    set_low16(&r->eax, rd16(r, 0x5bb7b6));
    r->edx = rd32(r, r->esp + 0xc);
    wr32(r, r->esp, r->eax);
    r->eax = (uint32_t)((int32_t)r->eax >> 0x4);
    r->eax = r->eax * r->edx;
    wr16(r, 0x5bb6fa, (r->eax & 0xffff));
    set_low16(&r->eax, rd16(r, 0x5bb7b6));
    set_high8(&r->eax, 0);
    set_low8(&r->eax, (r->eax & 0xff) & 0xf);
    r->edx = rd32(r, r->esp + 0x8);
    r->eax = r->eax & 0xffff;
    r->eax = r->eax + r->edx;
    set_low8(&r->eax, rd8(r, r->eax + 0x5c1b00));
    set_low16(&r->edx, rd16(r, 0x5bb6fa));
    set_high8(&r->eax, 0);
    r->edx = r->edx + r->eax;
    set_low16(&r->eax, rd16(r, 0x5bb6f8));
    wr16(r, 0x5bb6fa, (r->edx & 0xffff));
    if ((uint16_t)((r->eax & 0xffff)) == 0)
    {
        goto at_4b13fa;
    }
    if ((uint16_t)((r->edx & 0xffff)) == 0)
    {
        goto at_4b13fa;
    }
    r->eax = rd32(r, 0x5bb7a2);
    r->eax = (uint32_t)((int32_t)r->eax >> 0x10);
    wr32(r, r->esp + 0x10, r->eax);
    r->eax = rd32(r, 0x5bb79e);
    r->edx = rd32(r, r->esp + 0x10);
    r->eax = (uint32_t)((int32_t)r->eax >> 0x10);
    r->edx = r->edx - r->eax;
    r->eax = r->edx;
    r->edx = rd32(r, 0x5bb6f6);
    r->edx = (uint32_t)((int32_t)r->edx >> 0x10);
    wr32(r, r->esp + 0xc, r->edx);
    r->edx = r->edx * r->eax;
    r->eax = r->edx;
    r->edx = (uint32_t)((int32_t)r->edx >> 0x1f);
    idiv32(r, rd32(r, r->esp + 0x18));
    r->edx = rd32(r, r->esp + 0x10);
    r->edx = r->edx - r->eax;
    r->eax = rd32(r, 0x5bb7a4);
    r->eax = (uint32_t)((int32_t)r->eax >> 0x10);
    wr32(r, r->esp + 0x8, r->eax);
    wr16(r, 0x5bb6f0, (r->edx & 0xffff));
    r->edx = rd32(r, r->esp + 0x8);
    r->eax = (uint32_t)(int32_t)(int16_t)(r->ebx & 0xffff);
    r->edx = r->edx - r->eax;
    r->eax = r->edx;
    r->edx = rd32(r, 0x5bb7ac);
    r->edx = (uint32_t)((int32_t)r->edx >> 0x10);
    wr32(r, r->esp + 0x10, r->edx);
    r->eax = r->eax - r->edx;
    r->edx = rd32(r, 0x5bb6f8);
    r->edx = (uint32_t)((int32_t)r->edx >> 0x10);
    wr32(r, r->esp + 0x14, r->edx);
    r->edx = r->edx * r->eax;
    r->eax = r->edx;
    r->edx = (uint32_t)((int32_t)r->edx >> 0x1f);
    idiv32(r, rd32(r, r->esp));
    r->edx = rd32(r, r->esp + 0x8);
    r->edx = r->edx - r->eax;
    r->eax = r->edx;
    r->eax = r->eax - rd32(r, r->esp + 0x10);
    r->edx = rd32(r, 0x5bb6de);
    wr16(r, 0x5bb6f2, (r->eax & 0xffff));
    r->eax = rd32(r, r->esp + 0xc);
    r->edx = (uint32_t)((int32_t)r->edx >> 0x10);
    r->edx = r->edx * r->eax;
    r->eax = r->edx;
    r->edx = (uint32_t)((int32_t)r->edx >> 0x1f);
    idiv32(r, rd32(r, r->esp + 0x18));
    r->edx = rd32(r, 0x5bb6e0);
    wr16(r, 0x5bb6fc, (r->eax & 0xffff));
    r->eax = rd32(r, r->esp + 0x14);
    r->edx = (uint32_t)((int32_t)r->edx >> 0x10);
    r->edx = r->edx * r->eax;
    r->eax = r->edx;
    r->edx = (uint32_t)((int32_t)r->edx >> 0x1f);
    idiv32(r, rd32(r, r->esp));
    set_low16(&r->edx, rd16(r, 0x5bb6fc));
    wr16(r, 0x5bb6fe, (r->eax & 0xffff));
    set_low16(&r->eax, rd16(r, 0x5bb6f0));
    r->eax = r->eax + r->edx;
    r->eax = r->eax - 1;
    set_low16(&r->edx, rd16(r, 0x5bb6fe));
    wr16(r, 0x5bb6f4, (r->eax & 0xffff));
    set_low16(&r->eax, rd16(r, 0x5bb6f2));
    r->eax = r->eax + r->edx;
    r->eax = r->eax - 1;
    set_low8(&r->edx, rd8(r, 0x5bbffe));
    wr16(r, 0x5bb6f6, (r->eax & 0xffff));
    if ((uint8_t)((r->edx & 0xff)) == (uint8_t)0x2)
    {
        goto at_4b1333;
    }
    set_low16(&r->eax, rd16(r, 0x5b9c90));
    r->eax = r->eax - 1;
    wr32(r, r->esp + 0x20, r->eax);
    set_low16(&r->eax, rd16(r, 0x5b9c8e));
    r->eax = r->eax - 1;
    wr32(r, r->esp + 0x28, r->eax);
    if ((uint8_t)((r->edx & 0xff)) != (uint8_t)0x1)
    {
        goto at_4b1405;
    }
    r->eax = 0;
    wr16(r, 0x5bbff6, (r->eax & 0xffff));
    r->eax = rd32(r, r->esp + 0x28);
    r->edx = 0;
at_4b1272:
    wr16(r, 0x5bbff8, (r->eax & 0xffff));
    r->eax = rd32(r, r->esp + 0x20);
    wr16(r, 0x5bbffa, (r->edx & 0xffff));
at_4b1283:
    wr16(r, 0x5bbffc, (r->eax & 0xffff));
at_4b1289:
    set_low16(&r->eax, rd16(r, 0x5bb6f0));
    if ((int16_t)((r->eax & 0xffff)) > (int16_t)rd16(r, 0x5bbff8))
    {
        goto at_4b1468;
    }
    set_low16(&r->eax, rd16(r, 0x5bb6f4));
    if ((int16_t)((r->eax & 0xffff)) < (int16_t)rd16(r, 0x5bbff6))
    {
        goto at_4b1468;
    }
    set_low16(&r->eax, rd16(r, 0x5bb6f2));
    if ((int16_t)((r->eax & 0xffff)) > (int16_t)rd16(r, 0x5bbffc))
    {
        goto at_4b1468;
    }
    set_low16(&r->eax, rd16(r, 0x5bb6f6));
    set_low16(&r->edx, rd16(r, 0x5bbffa));
    if ((int16_t)((r->eax & 0xffff)) < (int16_t)((r->edx & 0xffff)))
    {
        goto at_4b1468;
    }
    if ((int16_t)((r->edx & 0xffff)) <= (int16_t)rd16(r, 0x5bb6f2))
    {
        goto at_4b12e8;
    }
    wr16(r, 0x5bb6f2, (r->edx & 0xffff));
at_4b12e8:
    set_low16(&r->eax, rd16(r, 0x5bb6f0));
    set_low16(&r->edx, rd16(r, 0x5bbff6));
    if ((int16_t)((r->eax & 0xffff)) >= (int16_t)((r->edx & 0xffff)))
    {
        goto at_4b1301;
    }
    wr16(r, 0x5bb6f0, (r->edx & 0xffff));
at_4b1301:
    set_low16(&r->eax, rd16(r, 0x5bb6f6));
    set_low16(&r->edx, rd16(r, 0x5bbffc));
    if ((int16_t)((r->eax & 0xffff)) <= (int16_t)((r->edx & 0xffff)))
    {
        goto at_4b131a;
    }
    wr16(r, 0x5bb6f6, (r->edx & 0xffff));
at_4b131a:
    set_low16(&r->eax, rd16(r, 0x5bb6f4));
    set_low16(&r->edx, rd16(r, 0x5bbff8));
    if ((int16_t)((r->eax & 0xffff)) <= (int16_t)((r->edx & 0xffff)))
    {
        goto at_4b1333;
    }
    wr16(r, 0x5bb6f4, (r->edx & 0xffff));
at_4b1333:
    r->eax = rd32(r, r->esp + 0x2c);
    wr16(r, 0x5bb6e8, (r->eax & 0xffff));
    r->eax = rd32(r, r->esp + 0x30);
    set_low16(&r->edx, rd16(r, 0x5bb6f0));
    wr16(r, 0x5bb6ea, (r->eax & 0xffff));
    if ((int16_t)((r->edx & 0xffff)) > (int16_t)rd16(r, r->esp + 0x2c) && !r->port->env.failed)
    {
        goto at_4b0faf;
    }
    r->eax = rd32(r, r->esp + 0x30);
    if ((int16_t)((r->eax & 0xffff)) < (int16_t)rd16(r, 0x5bb6f2) && !r->port->env.failed)
    {
        goto at_4b0faf;
    }
    r->eax = rd32(r, r->esp + 0x2c);
    if ((int16_t)((r->eax & 0xffff)) > (int16_t)rd16(r, 0x5bb6f4) && !r->port->env.failed)
    {
        goto at_4b0faf;
    }
    r->eax = rd32(r, r->esp + 0x30);
    if ((int16_t)((r->eax & 0xffff)) > (int16_t)rd16(r, 0x5bb6f6) && !r->port->env.failed)
    {
        goto at_4b0faf;
    }
    if ((uint8_t)rd8(r, 0x5bbfff) != (uint8_t)0x1)
    {
        goto at_4b14a8;
    }
    r->edi = rd8(r, 0x5bb738);
    r->esi = rd32(r, 0x5bb734);
    r->edi = r->edi << 0xa;
    set_low16(&r->ecx, rd16(r, 0x5bb6f2));
    r->edi = r->edi + 0x5c1c00;
    r->esi = rd32(r, r->esi);
    r->ebp = r->edi;
    set_low16(&r->eax, (r->eax & 0xffff) - (r->ecx & 0xffff));
    flags(r, F_SUB, (r->eax & 0xffff) + (r->ecx & 0xffff), (r->ecx & 0xffff), 16);
    r->ecx = r->eax;
    if (cond(r, CC_NE))
    {
        goto at_4b146f;
    }
at_4b13c5:
    set_low16(&r->ecx, rd16(r, 0x5bb6e8));
    set_low16(&r->ecx, (r->ecx & 0xffff) - rd16(r, 0x5bb6f0));
    if ((uint16_t)((r->ecx & 0xffff)) == 0)
    {
        goto at_4b13f0;
    }
at_4b13d5:
    r->edx = 0;
    set_low8(&r->edx, rd8(r, r->ebp));
    r->edx = r->edx << 0x2;
    r->ebp = r->ebp + 1;
    r->esi = r->esi + r->edx;
    set_low16(&r->ecx, (r->ecx & 0xffff) - 1);
    if ((uint16_t)((r->ecx & 0xffff)) != 0 && !r->port->env.failed)
    {
        goto at_4b13d5;
    }
at_4b13f0:
    r->eax = rd32(r, r->esi);
    r->eax = r->eax >> 0x18;
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4b0eba;
at_4b13fa:
    set_high8(&r->eax, 0);
    wr8(r, r->esp + 0x34, ((r->eax >> 8) & 0xff));
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4b0ec6;
at_4b1405:
    if ((uint8_t)((r->edx & 0xff)) != 0)
    {
        goto at_4b141c;
    }
    r->eax = 0;
    wr16(r, 0x5bbff6, (r->eax & 0xffff));
    r->eax = rd32(r, r->esp + 0x28);
    set_high8(&r->edx, 0);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4b1272;
at_4b141c:
    if ((uint8_t)((r->edx & 0xff)) != (uint8_t)0x3 && !r->port->env.failed)
    {
        goto at_4b1289;
    }
    r->eax = rd32(r, r->esp + 0x4);
    set_low16(&r->eax, rd16(r, r->eax + 0xa8));
    wr16(r, 0x5bbff6, (r->eax & 0xffff));
    r->eax = rd32(r, r->esp + 0x4);
    set_low16(&r->eax, rd16(r, r->eax + 0xaa));
    wr16(r, 0x5bbff8, (r->eax & 0xffff));
    r->eax = rd32(r, r->esp + 0x4);
    set_low16(&r->eax, rd16(r, r->eax + 0xac));
    wr16(r, 0x5bbffa, (r->eax & 0xffff));
    r->eax = rd32(r, r->esp + 0x4);
    set_low16(&r->eax, rd16(r, r->eax + 0xae));
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4b1283;
at_4b1468:
    set_low8(&r->eax, 0);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4b0ec2;
at_4b146f:
    r->eax = 0;
    wr16(r, 0x5bb702, (r->eax & 0xffff));
at_4b1477:
    set_high8(&r->edx, 0);
    set_low16(&r->eax, rd16(r, 0x5bb702));
    set_low8(&r->edx, rd8(r, r->edi));
    r->eax = r->eax + r->edx;
    r->edi = r->edi + 1;
    wr16(r, 0x5bb702, (r->eax & 0xffff));
    set_low16(&r->ecx, (r->ecx & 0xffff) - 1);
    if ((uint16_t)((r->ecx & 0xffff)) != 0 && !r->port->env.failed)
    {
        goto at_4b1477;
    }
    r->edx = 0;
    set_low16(&r->edx, (r->eax & 0xffff));
    r->eax = 0;
    set_low16(&r->eax, rd16(r, 0x5bb7b4));
    r->eax = r->eax * r->edx;
    r->eax = r->eax << 0x2;
    r->esi = r->esi + r->eax;
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4b13c5;
at_4b14a8:
    wr8(r, r->esp + 0x34, 0x1);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4b0ec6;
}

uint32_t vertrix_port_actor_draw_clipped_4b0b70(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x60
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
