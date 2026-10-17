#include "port_rtlactorspans.h"

/* Paints an actor onto its target surface, unless it has no image (+0x13c) or the target is 8-bit,
 * using the blit globals at 0x5bb7xx. */

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

/* Original 0x4b17e0: Paints an actor onto its target surface, unless it has no image (+0x13c) or
 * the target is 8-bit, using the blit globals at 0x5bb7xx. Evidence: calls 0x478eb0, 0x4ae110;
 * reads 0x5bc010, 0x5bb7a4, 0x5bb7a6, 0x544070, 0x5bb7a0, 0x5bb7a2, 0x5bb7ae, 0x5bb73e, 0x5bb740,
 * 0x5bb744, 0x5bb742, 0x5bb746, 0x5bb738, 0x5bb70c, 0x5bb7b4, 0x5bb7b6 and more; writes 0x5bb734,
 * 0x5bb732, 0x5bb733, 0x5bb7a4, 0x5bb740, 0x5bb7a6, 0x5bb742, 0x5bb7a0, 0x5bb7a2, 0x5bb7ae,
 * 0x5bb7b4, 0x5bb7b6, 0x5bbffe, 0x5bb739, 0x5bb790, 0x5bb731 and more. Register-for-register from
 * the listing (0x4b17e0..0x4b1f8e); labels are the original addresses. */
static void run(Regs *r)
{
    push_mem(r, r->ebx);
    push_mem(r, r->ecx);
    push_mem(r, r->esi);
    push_mem(r, r->edi);
    r->esi = r->eax;
    r->edi = r->edx;
    r->edx = rd32(r, r->eax + 0x13c);
    if (r->edx == 0)
    {
        goto at_4b1d35;
    }
at_4b17f6:
    r->eax = rd32(r, r->esi + 0xb4);
    wr32(r, 0x5bb734, r->eax);
    if (r->eax != 0)
    {
        goto at_4b1d44;
    }
    r->ebx = rd32(r, 0x5bc010);
    if (r->ebx == 0)
    {
        goto at_4b1d30;
    }
    set_low8(&r->edx, rd8(r, r->ebx + 0xc));
    set_low8(&r->eax, rd8(r, r->ebx + 0xd));
    wr8(r, 0x5bb732, (r->edx & 0xff));
    wr8(r, 0x5bb733, (r->eax & 0xff));
    if ((uint8_t)((r->eax & 0xff)) == (uint8_t)0x3)
    {
        goto at_4b1d44;
    }
    set_low16(&r->eax, rd16(r, r->esi + 0xe));
    wr16(r, 0x5bb7a4, (r->eax & 0xffff));
    wr16(r, 0x5bb740, (r->eax & 0xffff));
    set_low16(&r->eax, rd16(r, r->esi + 0x16));
    wr16(r, 0x5bb7a6, (r->eax & 0xffff));
    wr16(r, 0x5bb742, (r->eax & 0xffff));
    set_low16(&r->eax, rd16(r, 0x5bb7a4));
    wr16(r, 0x5bb7a0, (r->eax & 0xffff));
    set_low16(&r->eax, rd16(r, 0x5bb7a6));
    wr16(r, 0x5bb7a2, (r->eax & 0xffff));
    set_low16(&r->eax, rd16(r, r->esi + 0x1e));
    wr16(r, 0x5bb7ae, (r->eax & 0xffff));
    set_low16(&r->eax, rd16(r, r->esi + 0xf4));
    wr16(r, 0x5bb7b4, (r->eax & 0xffff));
    set_low16(&r->eax, rd16(r, r->esi + 0xf8));
    set_low8(&r->ebx, 0x4);
    wr16(r, 0x5bb7b6, (r->eax & 0xffff));
    set_low8(&r->eax, rd8(r, r->esi + 0x8e));
    set_low8(&r->edx, 0);
    wr8(r, 0x5bbffe, (r->eax & 0xff));
    r->eax = 0;
    wr8(r, 0x5bb739, (r->edx & 0xff));
    wr32(r, 0x5bb790, r->eax);
    set_low8(&r->eax, rd8(r, r->esi + 0x94));
    wr8(r, 0x5bb731, (r->ebx & 0xff));
    wr8(r, 0x5bc00c, (r->eax & 0xff));
    set_low8(&r->eax, rd8(r, r->esi + 0x8c));
    set_high8(&r->edx, 0x64);
    wr8(r, 0x5bb73a, (r->eax & 0xff));
    set_low8(&r->eax, rd8(r, r->esi + 0x80));
    wr8(r, 0x5bc00e, ((r->edx >> 8) & 0xff));
    wr8(r, 0x5bb7b8, (r->eax & 0xff));
    if (r->edi != 0)
    {
        goto at_4b1941;
    }
    r->eax = rd32(r, 0x544070);
    set_low16(&r->edx, rd16(r, r->eax + 0x208));
    wr16(r, 0x5bb744, (r->edx & 0xffff));
    set_low16(&r->edx, rd16(r, r->eax + 0x20c));
    set_low16(&r->ebx, rd16(r, 0x5bb7a0));
    wr16(r, 0x5bb746, (r->edx & 0xffff));
    set_low16(&r->edx, rd16(r, r->eax + 0x214));
    set_low16(&r->ecx, rd16(r, 0x5bb7a2));
    r->ebx = r->ebx - r->edx;
    set_low16(&r->edx, rd16(r, r->eax + 0x216));
    set_low16(&r->eax, rd16(r, r->eax + 0x226));
    r->ecx = r->ecx - r->edx;
    set_low16(&r->edx, rd16(r, 0x5bb7ae));
    wr16(r, 0x5bb7a0, (r->ebx & 0xffff));
    r->edx = r->edx + r->eax;
    wr16(r, 0x5bb7a2, (r->ecx & 0xffff));
    wr16(r, 0x5bb7ae, (r->edx & 0xffff));
at_4b1941:
    wr8(r, 0x5bb730, 0xd);
    if (r->edi != 0)
    {
        goto at_4b19ca;
    }
    r->eax = rd32(r, 0x5bb73e);
    r->eax = (uint32_t)((int32_t)r->eax >> 0x10);
    if ((int32_t)r->eax < 0)
    {
        goto at_4b1d4b;
    }
    set_low16(&r->eax, rd16(r, 0x5bb740));
    set_low16(&r->ebx, rd16(r, 0x5bb744));
    if ((int16_t)((r->eax & 0xffff)) < (int16_t)((r->ebx & 0xffff)))
    {
        goto at_4b197b;
    }
    r->eax = r->ebx;
    r->eax = r->eax - 1;
    wr16(r, 0x5bb740, (r->eax & 0xffff));
at_4b197b:
    r->eax = rd32(r, 0x5bb740);
    r->eax = (uint32_t)((int32_t)r->eax >> 0x10);
    if ((int32_t)r->eax < 0)
    {
        goto at_4b1d59;
    }
    set_low16(&r->eax, rd16(r, 0x5bb742));
    set_low16(&r->edx, rd16(r, 0x5bb746));
    if ((int16_t)((r->eax & 0xffff)) < (int16_t)((r->edx & 0xffff)))
    {
        goto at_4b19a6;
    }
    r->eax = r->edx;
    r->eax = r->eax - 1;
    wr16(r, 0x5bb742, (r->eax & 0xffff));
at_4b19a6:
    r->edx = rd32(r, 0x5bb742);
    r->eax = rd32(r, 0x5bb740);
    r->edx = (uint32_t)((int32_t)r->edx >> 0x10);
    r->eax = (uint32_t)((int32_t)r->eax >> 0x10);
    r->edx = r->edx * r->eax;
    r->eax = rd32(r, 0x5bb73e);
    r->eax = (uint32_t)((int32_t)r->eax >> 0x10);
    r->edx = r->edx + r->eax;
    wr32(r, 0x5bb73c, r->edx);
at_4b19ca:
    if (r->edi != 0x1)
    {
        goto at_4b1d67;
    }
at_4b19d3:
    set_low8(&r->eax, rd8(r, r->esi + 0x44));
at_4b19d6:
    wr8(r, 0x5bb738, (r->eax & 0xff));
    flags(r, F_SUB, rd8(r, 0x5bb738), 0x10, 8);
    set_low8(&r->eax, cond(r, CC_NE));
    r->eax = r->eax & 0xff;
    wr32(r, 0x5bb70c, r->eax);
    if (r->edi != 0x1)
    {
        goto at_4b1da6;
    }
at_4b19f8:
    set_low8(&r->eax, rd8(r, r->esi + 0x52));
    wr8(r, 0x5bc000, (r->eax & 0xff));
    set_low16(&r->eax, rd16(r, r->esi + 0x48));
at_4b1a04:
    wr16(r, 0x5bc002, (r->eax & 0xffff));
at_4b1a0a:
    if (rd32(r, 0x5bb70c) != 0x0)
    {
        goto at_4b1e31;
    }
    set_low16(&r->eax, rd16(r, 0x5bb7b4));
    wr16(r, 0x5bb74c, (r->eax & 0xffff));
    set_low16(&r->eax, rd16(r, 0x5bb7b6));
    wr16(r, 0x5bb74e, (r->eax & 0xffff));
at_4b1a2f:
    set_low16(&r->eax, rd16(r, 0x5bb74c));
    if ((uint16_t)((r->eax & 0xffff)) == 0)
    {
        goto at_4b1d44;
    }
    set_low16(&r->edx, rd16(r, 0x5bb74e));
    if ((uint16_t)((r->edx & 0xffff)) == 0)
    {
        goto at_4b1d44;
    }
    set_low16(&r->ebx, rd16(r, 0x5bb7a2));
    wr16(r, 0x5bb750, (r->eax & 0xffff));
    set_low16(&r->eax, rd16(r, 0x5bb7ae));
    set_low16(&r->ecx, rd16(r, 0x5bb74c));
    r->ebx = r->ebx - r->eax;
    set_low16(&r->eax, rd16(r, 0x5bb7a0));
    r->eax = r->eax + r->ecx;
    r->eax = r->eax - 1;
    wr16(r, 0x5bb748, (r->eax & 0xffff));
    r->eax = r->ebx;
    wr16(r, 0x5bb752, (r->edx & 0xffff));
    r->eax = r->eax + r->edx;
    wr16(r, 0x5bb7a2, (r->ebx & 0xffff));
    r->eax = r->eax - 1;
    wr16(r, 0x5bbff4, (r->ebx & 0xffff));
    wr16(r, 0x5bb74a, (r->eax & 0xffff));
    set_low16(&r->eax, rd16(r, 0x5bb7a0));
    set_low8(&r->ebx, rd8(r, 0x5bbffe));
    wr16(r, 0x5bbff2, (r->eax & 0xffff));
    if ((uint8_t)((r->ebx & 0xff)) == (uint8_t)0x2)
    {
        goto at_4b1b35;
    }
    if ((uint8_t)((r->ebx & 0xff)) != (uint8_t)0x1)
    {
        goto at_4b1eb5;
    }
    r->ebx = 0;
    r->eax = rd32(r, 0x5bc010);
    wr16(r, 0x5bbff6, (r->ebx & 0xffff));
    wr16(r, 0x5bbffa, (r->ebx & 0xffff));
    set_low16(&r->edx, rd16(r, r->eax + 0x4));
    set_low16(&r->eax, rd16(r, r->eax + 0x8));
    r->edx = r->edx - 1;
    r->eax = r->eax - 1;
    wr16(r, 0x5bbff8, (r->edx & 0xffff));
at_4b1ae3:
    wr16(r, 0x5bbffc, (r->eax & 0xffff));
at_4b1ae9:
    set_low16(&r->eax, rd16(r, 0x5bb7a0));
    if ((int16_t)((r->eax & 0xffff)) > (int16_t)rd16(r, 0x5bbff8))
    {
        goto at_4b1d44;
    }
    set_low16(&r->eax, rd16(r, 0x5bb748));
    if ((int16_t)((r->eax & 0xffff)) < (int16_t)rd16(r, 0x5bbff6))
    {
        goto at_4b1d44;
    }
    set_low16(&r->eax, rd16(r, 0x5bb7a2));
    if ((int16_t)((r->eax & 0xffff)) > (int16_t)rd16(r, 0x5bbffc))
    {
        goto at_4b1d44;
    }
    set_low16(&r->eax, rd16(r, 0x5bb74a));
    if ((int16_t)((r->eax & 0xffff)) < (int16_t)rd16(r, 0x5bbffa))
    {
        goto at_4b1d44;
    }
at_4b1b35:
    set_low8(&r->eax, 0);
    wr8(r, 0x5bc014, (r->eax & 0xff));
    if ((uint8_t)rd8(r, 0x5bbffe) == (uint8_t)0x2)
    {
        goto at_4b1f27;
    }
    set_low16(&r->eax, rd16(r, 0x5bb7a2));
    if ((int16_t)((r->eax & 0xffff)) >= (int16_t)rd16(r, 0x5bbffa))
    {
        goto at_4b1b9b;
    }
    if (rd32(r, 0x5bb70c) != 0x0)
    {
        goto at_4b1b87;
    }
    r->eax = rd32(r, 0x5bbff8);
    r->edx = rd32(r, 0x5bb7a0);
    r->eax = (uint32_t)((int32_t)r->eax >> 0x10);
    r->edx = (uint32_t)((int32_t)r->edx >> 0x10);
    r->eax = r->eax - r->edx;
    r->edx = r->eax;
    r->eax = rd32(r, 0x5bb74a);
    r->eax = (uint32_t)((int32_t)r->eax >> 0x10);
    r->eax = r->eax * r->edx;
    wr32(r, 0x5bb790, rd32(r, 0x5bb790) + r->eax);
at_4b1b87:
    set_low16(&r->eax, rd16(r, 0x5bbffa));
    set_low8(&r->edx, 0x1);
    wr16(r, 0x5bb7a2, (r->eax & 0xffff));
    wr8(r, 0x5bc014, (r->edx & 0xff));
at_4b1b9b:
    set_low16(&r->eax, rd16(r, 0x5bb7a0));
    if ((int16_t)((r->eax & 0xffff)) >= (int16_t)rd16(r, 0x5bbff6))
    {
        goto at_4b1be8;
    }
    if (rd32(r, 0x5bb70c) != 0x0)
    {
        goto at_4b1bd4;
    }
    r->edx = rd32(r, 0x5bbff4);
    r->eax = rd32(r, 0x5bb79e);
    r->edx = (uint32_t)((int32_t)r->edx >> 0x10);
    r->eax = (uint32_t)((int32_t)r->eax >> 0x10);
    r->ebx = rd32(r, 0x5bb790);
    r->edx = r->edx - r->eax;
    r->ebx = r->ebx + r->edx;
    wr32(r, 0x5bb790, r->ebx);
at_4b1bd4:
    set_low16(&r->eax, rd16(r, 0x5bbff6));
    set_high8(&r->edx, 0x1);
    wr16(r, 0x5bb7a0, (r->eax & 0xffff));
    wr8(r, 0x5bc014, ((r->edx >> 8) & 0xff));
at_4b1be8:
    set_low16(&r->eax, rd16(r, 0x5bb74a));
    set_low16(&r->ebx, rd16(r, 0x5bbffc));
    if ((int16_t)((r->eax & 0xffff)) <= (int16_t)((r->ebx & 0xffff)))
    {
        goto at_4b1c08;
    }
    wr16(r, 0x5bb74a, (r->ebx & 0xffff));
    wr8(r, 0x5bc014, 0x1);
at_4b1c08:
    set_low16(&r->eax, rd16(r, 0x5bb748));
    set_low16(&r->ecx, rd16(r, 0x5bbff8));
    if ((int16_t)((r->eax & 0xffff)) <= (int16_t)((r->ecx & 0xffff)))
    {
        goto at_4b1f27;
    }
    wr16(r, 0x5bb748, (r->ecx & 0xffff));
    wr8(r, 0x5bc014, 0x1);
at_4b1c2c:
    set_low16(&r->eax, rd16(r, 0x5bb748));
    set_low16(&r->eax, (r->eax & 0xffff) - rd16(r, 0x5bb7a0));
    r->eax = r->eax + 1;
    set_low16(&r->edx, rd16(r, 0x5bb7a2));
    wr16(r, 0x5bb750, (r->eax & 0xffff));
    set_low16(&r->eax, rd16(r, 0x5bb74a));
    r->eax = r->eax - r->edx;
    r->eax = r->eax + 1;
    set_low16(&r->ebx, rd16(r, 0x5bb750));
    wr16(r, 0x5bb752, (r->eax & 0xffff));
    if ((uint16_t)((r->ebx & 0xffff)) == 0)
    {
        goto at_4b1d44;
    }
    if ((uint16_t)((r->eax & 0xffff)) == 0)
    {
        goto at_4b1d44;
    }
at_4b1c6f:
    r->eax = rd32(r, 0x5bc010);
    set_low16(&r->edx, rd16(r, r->eax + 0x4));
    wr16(r, 0x5bb798, (r->edx & 0xffff));
    r->edx = rd32(r, 0x5bb796);
    r->edx = (uint32_t)((int32_t)r->edx >> 0x10);
    r->ecx = rd32(r, 0x5bb796);
    wr32(r, 0x5bb7bc, r->edx);
    r->edx = rd32(r, 0x5bb74e);
    r->ecx = (uint32_t)((int32_t)r->ecx >> 0x10);
    r->edx = (uint32_t)((int32_t)r->edx >> 0x10);
    r->ecx = r->ecx - r->edx;
    r->edx = rd32(r, r->eax + 0x14);
    wr32(r, 0x5bb7c4, r->edx);
    r->edx = 0;
    set_low8(&r->edx, rd8(r, 0x5bb732));
    r->edx = r->edx * r->ecx;
    wr32(r, 0x5bb794, r->ecx);
    r->ecx = rd32(r, r->eax + 0x18);
    r->edx = r->edx + r->ecx;
    set_high8(&r->ecx, rd8(r, 0x5bb732));
    wr32(r, 0x5bb7c8, r->edx);
    if ((uint8_t)(((r->ecx >> 8) & 0xff)) != (uint8_t)0x4)
    {
        goto at_4b1f39;
    }
    r->ebx = rd32(r, 0x5bb7a0);
    r->edx = rd32(r, 0x5bb79e);
    r->ebx = (uint32_t)((int32_t)r->ebx >> 0x10);
    r->edx = (uint32_t)((int32_t)r->edx >> 0x10);
    call_mem_keep(r, 0x478eb0, 8);
    wr32(r, 0x5bb768, r->eax);
    wr32(r, 0x5bb770, r->eax);
at_4b1cf7:
    if (rd32(r, r->esi + 0x13c) != 0x0)
    {
        goto at_4b1d2b;
    }
    r->eax = rd32(r, 0x5bb750);
    r->ecx = rd32(r, 0x5bb74e);
    r->ebx = rd32(r, 0x5bb7a0);
    r->edx = rd32(r, 0x5bb79e);
    r->eax = (uint32_t)((int32_t)r->eax >> 0x10);
    r->ecx = (uint32_t)((int32_t)r->ecx >> 0x10);
    r->ebx = (uint32_t)((int32_t)r->ebx >> 0x10);
    push_mem(r, r->eax);
    r->edx = (uint32_t)((int32_t)r->edx >> 0x10);
    r->eax = r->esi;
    call_mem(r, 0x4ae110, 1);
at_4b1d2b:
    r->eax = 0x1;
at_4b1d30:
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    r->ecx = pop_mem(r);
    r->ebx = pop_mem(r);
    return;
at_4b1d35:
    push_mem(r, r->edx);
    r->ecx = 0;
    r->ebx = 0;
    call_mem(r, 0x4ae110, 1);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4b17f6;
at_4b1d44:
    r->eax = 0;
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    r->ecx = pop_mem(r);
    r->ebx = pop_mem(r);
    return;
at_4b1d4b:
    r->ecx = 0;
    wr16(r, 0x5bb740, (r->ecx & 0xffff));
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4b197b;
at_4b1d59:
    r->ebx = 0;
    wr16(r, 0x5bb742, (r->ebx & 0xffff));
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4b19a6;
at_4b1d67:
    if ((uint8_t)rd8(r, r->esi + 0x91) == (uint8_t)0x0 && !r->port->env.failed)
    {
        goto at_4b19d3;
    }
    r->eax = rd32(r, 0x544070);
    if ((uint8_t)rd8(r, r->eax + 0x220) != (uint8_t)0x0)
    {
        goto at_4b1d8d;
    }
    set_low8(&r->eax, rd8(r, r->eax + 0x221));
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4b19d6;
at_4b1d8d:
    r->eax = rd32(r, r->eax + 0x270);
    r->edx = rd32(r, 0x5bb73c);
    r->eax = rd32(r, r->eax);
    r->eax = r->eax + r->edx;
    set_low8(&r->eax, rd8(r, r->eax));
    set_low8(&r->eax, (r->eax & 0xff) + 1);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4b19d6;
at_4b1da6:
    if ((uint8_t)rd8(r, r->esi + 0x92) == (uint8_t)0x0 && !r->port->env.failed)
    {
        goto at_4b19f8;
    }
    r->eax = rd32(r, 0x544070);
    if ((uint8_t)rd8(r, r->eax + 0x222) != (uint8_t)0x0)
    {
        goto at_4b1de0;
    }
    set_low16(&r->edx, (uint32_t)(int32_t)(int8_t)rd8(r, r->eax + 0x223));
    set_low8(&r->eax, rd8(r, r->eax + 0x224));
    wr16(r, 0x5bc002, (r->edx & 0xffff));
    wr8(r, 0x5bc000, (r->eax & 0xff));
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4b1a0a;
at_4b1de0:
    r->eax = rd32(r, r->eax + 0x26c);
    r->ecx = rd32(r, 0x5bb73c);
    r->eax = rd32(r, r->eax);
    r->eax = r->eax + r->ecx;
    set_low8(&r->eax, rd8(r, r->eax));
    wr8(r, 0x5bc004, (r->eax & 0xff));
    r->eax = 0;
    set_low8(&r->eax, rd8(r, 0x5bc004));
    r->eax = (uint32_t)((int32_t)r->eax >> 0x3);
    wr8(r, 0x5bc000, (r->eax & 0xff));
    set_low8(&r->eax, rd8(r, 0x5bc004));
    set_low8(&r->eax, (r->eax & 0xff) & 0x7);
    set_low8(&r->eax, (r->eax & 0xff) - 0x5);
    set_low16(&r->edx, (uint32_t)(int32_t)(int8_t)(r->eax & 0xff));
    r->eax = (uint32_t)(int32_t)(int8_t)(r->eax & 0xff);
    wr16(r, 0x5bc002, (r->edx & 0xffff));
    if ((int32_t)r->eax < 0)
    {
        goto at_4b1e29;
    }
    r->eax = r->edx * 0x28;
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4b1a04;
at_4b1e29:
    r->eax = r->edx * 0x14;
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4b1a04;
at_4b1e31:
    r->eax = 0;
    set_low16(&r->eax, rd16(r, 0x5bb7b4));
    r->edx = r->eax;
    r->eax = 0;
    r->edx = (uint32_t)((int32_t)r->edx >> 0x4);
    set_low8(&r->eax, rd8(r, 0x5bb738));
    r->edx = r->edx * r->eax;
    set_low16(&r->ebx, rd16(r, 0x5bb7b4));
    set_high8(&r->ebx, 0);
    r->ecx = 0;
    set_low8(&r->ebx, (r->ebx & 0xff) & 0xf);
    wr16(r, 0x5bb74c, (r->edx & 0xffff));
    r->edx = r->eax;
    set_low16(&r->ecx, (r->ebx & 0xffff));
    r->edx = r->edx << 0x4;
    set_low8(&r->ebx, rd8(r, r->ecx + r->edx + 0x5c1b00));
    wr16(r, 0x5bb74c, rd16(r, 0x5bb74c) + (r->ebx & 0xffff));
    r->ecx = 0;
    set_low16(&r->ecx, rd16(r, 0x5bb7b6));
    r->ecx = (uint32_t)((int32_t)r->ecx >> 0x4);
    r->eax = r->eax * r->ecx;
    wr16(r, 0x5bb74e, (r->eax & 0xffff));
    set_low16(&r->eax, rd16(r, 0x5bb7b6));
    set_high8(&r->eax, 0);
    set_low8(&r->eax, (r->eax & 0xff) & 0xf);
    r->eax = r->eax & 0xffff;
    set_low8(&r->eax, rd8(r, r->edx + r->eax + 0x5c1b00));
    set_low16(&r->edi, rd16(r, 0x5bb74e));
    set_high8(&r->eax, 0);
    r->edi = r->edi + r->eax;
    wr16(r, 0x5bb74e, (r->edi & 0xffff));
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4b1a2f;
at_4b1eb5:
    if ((uint8_t)((r->ebx & 0xff)) != 0)
    {
        goto at_4b1eeb;
    }
    r->eax = 0;
    wr16(r, 0x5bbff6, (r->eax & 0xffff));
    r->eax = rd32(r, 0x5bc010);
    set_low16(&r->edx, rd16(r, r->eax + 0x4));
    r->edx = r->edx - 1;
    set_low16(&r->eax, rd16(r, r->eax + 0x8));
    wr16(r, 0x5bbff8, (r->edx & 0xffff));
    r->eax = r->eax - 1;
    r->edx = 0;
    wr16(r, 0x5bbffc, (r->eax & 0xffff));
    wr16(r, 0x5bbffa, (r->edx & 0xffff));
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4b1ae9;
at_4b1eeb:
    if ((uint8_t)((r->ebx & 0xff)) != (uint8_t)0x3 && !r->port->env.failed)
    {
        goto at_4b1ae9;
    }
    set_low16(&r->eax, rd16(r, r->esi + 0xa8));
    wr16(r, 0x5bbff6, (r->eax & 0xffff));
    set_low16(&r->eax, rd16(r, r->esi + 0xaa));
    wr16(r, 0x5bbff8, (r->eax & 0xffff));
    set_low16(&r->eax, rd16(r, r->esi + 0xac));
    wr16(r, 0x5bbffa, (r->eax & 0xffff));
    set_low16(&r->eax, rd16(r, r->esi + 0xae));
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4b1ae3;
at_4b1f27:
    if ((uint8_t)rd8(r, 0x5bc014) != (uint8_t)0x0 && !r->port->env.failed)
    {
        goto at_4b1c2c;
    }
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4b1c6f;
at_4b1f39:
    if ((uint8_t)(((r->ecx >> 8) & 0xff)) == (uint8_t)0x2)
    {
        goto at_4b1f6d;
    }
    if ((uint8_t)(((r->ecx >> 8) & 0xff)) != (uint8_t)0x1 && !r->port->env.failed)
    {
        goto at_4b1cf7;
    }
    r->ebx = rd32(r, 0x5bb7a0);
    r->edx = rd32(r, 0x5bb79e);
    r->ebx = (uint32_t)((int32_t)r->ebx >> 0x10);
    r->edx = (uint32_t)((int32_t)r->edx >> 0x10);
    call_mem_keep(r, 0x478eb0, 8);
    wr32(r, 0x5bb778, r->eax);
    wr32(r, 0x5bb77c, r->eax);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4b1cf7;
at_4b1f6d:
    r->ebx = rd32(r, 0x5bb7a0);
    r->edx = rd32(r, 0x5bb79e);
    r->ebx = (uint32_t)((int32_t)r->ebx >> 0x10);
    r->edx = (uint32_t)((int32_t)r->edx >> 0x10);
    call_mem_keep(r, 0x478eb0, 8);
    wr32(r, 0x5bb780, r->eax);
    wr32(r, 0x5bb784, r->eax);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4b1cf7;
}

uint32_t vertrix_port_actor_paint_span_4b17e0(PORT_SIGNATURE)
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
