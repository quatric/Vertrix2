#include "port_rtljpegacrefines.h"

/* libjpeg decode_mcu_AC_refine: one progressive AC refinement pass over an MCU, including restart
 * handling and the end-of-band run. */

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

/* Original 0x4c2d60: libjpeg decode_mcu_AC_refine: one progressive AC refinement pass over an MCU,
 * including restart handling and the end-of-band run. Evidence: calls 0x4c26f0, 0x4bbf30, 0x4bc050.
 * Register-for-register from the listing (0x4c2d6d..0x4c3194); labels are the original addresses.
 */
static void run(Regs *r)
{
    wr32(r, r->ebp - 0x38, r->eax);
    r->eax = rd32(r, r->eax + 0x1bc);
    wr32(r, r->ebp - 0x50, r->eax);
    r->eax = rd32(r, r->ebp - 0x38);
    r->ecx = rd32(r, r->ebp - 0x38);
    r->eax = rd32(r, r->eax + 0x194);
    set_low8(&r->ecx, rd8(r, r->ecx + 0x19c));
    wr32(r, r->ebp - 0x48, r->eax);
    r->eax = 0x1;
    r->eax = r->eax << (r->ecx & 0xff);
    r->ecx = rd32(r, r->ebp - 0x38);
    wr32(r, r->ebp - 0x1c, r->eax);
    r->eax = 0xffffffffu;
    set_low8(&r->ecx, rd8(r, r->ecx + 0x19c));
    r->eax = r->eax << (r->ecx & 0xff);
    wr32(r, r->ebp - 0x24, r->eax);
    r->eax = rd32(r, r->ebp - 0x38);
    if (rd32(r, r->eax + 0x114) == 0x0)
    {
        goto at_4c2dd0;
    }
    r->eax = rd32(r, r->ebp - 0x50);
    if (rd32(r, r->eax + 0x28) != 0x0)
    {
        goto at_4c2dd0;
    }
    r->eax = rd32(r, r->ebp - 0x38);
    call_keep(r, 0x4c26f0);
    if (r->eax == 0)
    {
        goto at_4c2d33;
    }
at_4c2dd0:
    r->eax = rd32(r, r->ebp - 0x50);
    r->esi = rd32(r, r->eax + 0x8);
    if (r->esi != 0)
    {
        goto at_4c3176;
    }
    r->eax = rd32(r, r->ebp - 0x38);
    wr32(r, r->ebp - 0x5c, r->eax);
    r->eax = rd32(r, r->eax + 0x18);
    r->eax = rd32(r, r->eax);
    wr32(r, r->ebp - 0x6c, r->eax);
    r->eax = rd32(r, r->ebp - 0x38);
    r->eax = rd32(r, r->eax + 0x18);
    r->eax = rd32(r, r->eax + 0x4);
    wr32(r, r->ebp - 0x68, r->eax);
    r->eax = rd32(r, r->ebp - 0x50);
    r->eax = rd32(r, r->eax + 0x14);
    wr32(r, r->ebp - 0x54, r->eax);
    r->eax = rd32(r, r->edx);
    wr32(r, r->ebp - 0x20, r->eax);
    r->eax = rd32(r, r->ebp - 0x50);
    r->edi = rd32(r, r->ebp - 0x50);
    r->ebx = rd32(r, r->ebp - 0x50);
    r->eax = rd32(r, r->eax + 0x3c);
    wr32(r, r->ebp - 0x30, r->esi);
    wr32(r, r->ebp - 0x40, r->eax);
    r->eax = rd32(r, r->ebp - 0x38);
    r->edi = rd32(r, r->edi + 0xc);
    r->ebx = rd32(r, r->ebx + 0x10);
    r->eax = rd32(r, r->eax + 0x190);
    r->edx = rd32(r, r->ebp - 0x54);
    wr32(r, r->ebp - 0x18, r->eax);
    if (r->edx != 0)
    {
        goto at_4c3096;
    }
    r->eax = rd32(r, r->ebp - 0x48);
    r->eax = r->eax << 0x2;
    wr32(r, r->ebp - 0x3c, r->esi);
    wr32(r, r->ebp - 0x4c, r->eax);
at_4c2e41:
    r->eax = rd32(r, r->ebp - 0x18);
    if ((int32_t)r->eax > (int32_t)rd32(r, r->ebp - 0x48))
    {
        goto at_4c3096;
    }
    if ((int32_t)r->ebx >= (int32_t)0x8)
    {
        goto at_4c2ff4;
    }
    r->eax = r->ebp - 0x6c;
    r->edx = r->edi;
    r->ecx = 0;
    call_keep(r, 0x4bbf30);
    if (r->eax != 0)
    {
        goto at_4c2e93;
    }
at_4c2e66:
    r->eax = rd32(r, r->ebp - 0x30);
    r->ebx = rd32(r, r->ebp - 0x20);
    r->edx = 0;
    r->eax = r->eax << 0x2;
at_4c2e71:
    if ((int32_t)r->eax <= 0)
    {
        goto at_4c318a;
    }
    r->ecx = rd32(r, r->eax + r->ebp - 0x170);
    r->edi = rd32(r, r->ebp - 0x30);
    r->ecx = r->ecx + r->ecx;
    r->edi = r->edi - 1;
    r->ecx = r->ecx + r->ebx;
    r->eax = r->eax - 0x4;
    wr32(r, r->ebp - 0x30, r->edi);
    wr16(r, r->ecx, (r->edx & 0xffff));
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4c2e71;
at_4c2e93:
    r->ebx = rd32(r, r->ebp - 0x60);
    r->edi = rd32(r, r->ebp - 0x64);
    if ((int32_t)r->ebx >= (int32_t)0x8)
    {
        goto at_4c2ff4;
    }
    r->eax = 0x1;
at_4c2ea7:
    r->ecx = rd32(r, r->ebp - 0x40);
    push(r, r->eax);
    r->edx = r->edi;
    r->eax = r->ebp - 0x6c;
    call(r, 0x4bc050, 1);
    wr32(r, r->ebp - 0x2c, r->eax);
    if ((int32_t)r->eax < 0 && !r->port->env.failed)
    {
        goto at_4c2e66;
    }
    r->edi = rd32(r, r->ebp - 0x64);
    r->ebx = rd32(r, r->ebp - 0x60);
at_4c2ec2:
    r->eax = rd32(r, r->ebp - 0x2c);
    r->eax = (uint32_t)((int32_t)r->eax >> 0x4);
    r->esi = rd32(r, r->ebp - 0x2c);
    wr32(r, r->ebp - 0x58, r->eax);
    r->esi = r->esi & 0xf;
    flags(r, F_LOGIC, r->esi, 0, 32);
    wr32(r, r->ebp - 0x2c, r->esi);
    if (cond(r, CC_E))
    {
        goto at_4c303f;
    }
    if (r->esi == 0x1)
    {
        goto at_4c2efb;
    }
    r->eax = rd32(r, r->ebp - 0x38);
    r->eax = rd32(r, r->eax);
    r->ecx = rd32(r, r->ebp - 0x38);
    wr32(r, r->eax + 0x14, 0x76);
    r->ecx = rd32(r, r->ecx);
    r->edx = 0xffffffffu;
    r->eax = rd32(r, r->ebp - 0x38);
    call_all(r, rd32(r, r->ecx + 0x4));
at_4c2efb:
    if ((int32_t)r->ebx >= (int32_t)0x1)
    {
        goto at_4c2f1d;
    }
    r->ecx = 0x1;
    r->eax = r->ebp - 0x6c;
    r->edx = r->edi;
    call_keep(r, 0x4bbf30);
    if (r->eax == 0 && !r->port->env.failed)
    {
        goto at_4c2e66;
    }
    r->edi = rd32(r, r->ebp - 0x64);
    r->ebx = rd32(r, r->ebp - 0x60);
at_4c2f1d:
    r->ebx = r->ebx - 1;
    r->eax = r->edi;
    set_low8(&r->ecx, (r->ebx & 0xff));
    r->eax = (uint32_t)((int32_t)r->eax >> (r->ecx & 0xff));
    if ((uint8_t)((r->eax & 0xff) & 0x1) == 0)
    {
        goto at_4c3037;
    }
    r->eax = rd32(r, r->ebp - 0x1c);
at_4c2f2f:
    wr32(r, r->ebp - 0x2c, r->eax);
at_4c2f32:
    r->eax = rd32(r, r->ebp - 0x18);
    r->eax = r->eax << 0x2;
    wr32(r, r->ebp - 0x14, r->eax);
    r->eax = rd32(r, r->ebp - 0x4c);
    wr32(r, r->ebp - 0x28, r->eax);
at_4c2f41:
    r->esi = rd32(r, r->ebp - 0x14);
    r->esi = rd32(r, r->esi + 0x5000d0);
    r->eax = rd32(r, r->ebp - 0x20);
    r->esi = r->esi + r->esi;
    r->esi = r->esi + r->eax;
    if ((uint16_t)rd16(r, r->esi) == (uint16_t)0x0)
    {
        goto at_4c30eb;
    }
    if ((int32_t)r->ebx >= (int32_t)0x1)
    {
        goto at_4c2f7d;
    }
    r->ecx = 0x1;
    r->eax = r->ebp - 0x6c;
    r->edx = r->edi;
    call_keep(r, 0x4bbf30);
    if (r->eax == 0 && !r->port->env.failed)
    {
        goto at_4c2e66;
    }
    r->edi = rd32(r, r->ebp - 0x64);
    r->ebx = rd32(r, r->ebp - 0x60);
at_4c2f7d:
    r->ebx = r->ebx - 1;
    r->eax = r->edi;
    set_low8(&r->ecx, (r->ebx & 0xff));
    r->eax = (uint32_t)((int32_t)r->eax >> (r->ecx & 0xff));
    if ((uint8_t)((r->eax & 0xff) & 0x1) == 0)
    {
        goto at_4c2fa0;
    }
    r->edx = rd32(r, r->ebp - 0x1c);
    r->eax = (uint32_t)(int32_t)(int16_t)rd16(r, r->esi);
    if ((r->eax & r->edx) != 0)
    {
        goto at_4c2fa0;
    }
    if ((int32_t)r->eax < 0)
    {
        goto at_4c30e3;
    }
    r->eax = rd32(r, r->ebp - 0x1c);
at_4c2f9d:
    wr16(r, r->esi, rd16(r, r->esi) + (r->eax & 0xffff));
at_4c2fa0:
    r->ecx = rd32(r, r->ebp - 0x14);
    r->esi = rd32(r, r->ebp - 0x18);
    r->edx = rd32(r, r->ebp - 0x28);
    r->ecx = r->ecx + 0x4;
    r->esi = r->esi + 1;
    wr32(r, r->ebp - 0x14, r->ecx);
    wr32(r, r->ebp - 0x18, r->esi);
    if ((int32_t)r->ecx <= (int32_t)r->edx && !r->port->env.failed)
    {
        goto at_4c2f41;
    }
at_4c2fb7:
    if (rd32(r, r->ebp - 0x2c) == 0x0)
    {
        goto at_4c2fec;
    }
    r->eax = rd32(r, r->ebp - 0x18);
    r->eax = rd32(r, r->eax * 4 + 0x5000d0);
    r->esi = rd32(r, r->ebp - 0x20);
    r->ecx = r->eax + r->eax;
    r->ecx = r->ecx + r->esi;
    r->edx = rd32(r, r->ebp - 0x2c);
    wr16(r, r->ecx, (r->edx & 0xffff));
    r->edx = rd32(r, r->ebp - 0x3c);
    wr32(r, r->edx + r->ebp - 0x16c, r->eax);
    r->eax = r->edx + 0x4;
    r->edx = rd32(r, r->ebp - 0x30);
    r->edx = r->edx + 1;
    wr32(r, r->ebp - 0x3c, r->eax);
    wr32(r, r->ebp - 0x30, r->edx);
at_4c2fec:
    wr32(r, r->ebp - 0x18, rd32(r, r->ebp - 0x18) + 1);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4c2e41;
at_4c2ff4:
    r->ecx = r->ebx - 0x8;
    r->eax = r->edi;
    r->eax = (uint32_t)((int32_t)r->eax >> (r->ecx & 0xff));
    r->eax = r->eax & 0xff;
    r->edx = rd32(r, r->ebp - 0x40);
    r->esi = r->eax * 4;
    r->esi = r->esi + r->edx;
    r->esi = rd32(r, r->esi + 0x90);
    if (r->esi == 0)
    {
        goto at_4c302d;
    }
    r->eax = r->eax + r->edx;
    r->ebx = r->ebx - r->esi;
    set_low8(&r->eax, rd8(r, r->eax + 0x490));
    r->eax = r->eax & 0xff;
    wr32(r, r->ebp - 0x2c, r->eax);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4c2ec2;
at_4c302d:
    r->eax = 0x9;
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4c2ea7;
at_4c3037:
    r->eax = rd32(r, r->ebp - 0x24);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4c2f2f;
at_4c303f:
    if (r->eax == 0xf && !r->port->env.failed)
    {
        goto at_4c2f32;
    }
    set_low8(&r->ecx, rd8(r, r->ebp - 0x58));
    r->eax = 0x1;
    r->eax = r->eax << (r->ecx & 0xff);
    r->ecx = rd32(r, r->ebp - 0x58);
    wr32(r, r->ebp - 0x54, r->eax);
    if (r->ecx == 0)
    {
        goto at_4c3096;
    }
    if ((int32_t)r->ebx >= (int32_t)r->ecx)
    {
        goto at_4c3078;
    }
    r->eax = r->ebp - 0x6c;
    r->edx = r->edi;
    call_keep(r, 0x4bbf30);
    if (r->eax == 0 && !r->port->env.failed)
    {
        goto at_4c2e66;
    }
    r->edi = rd32(r, r->ebp - 0x64);
    r->ebx = rd32(r, r->ebp - 0x60);
at_4c3078:
    r->ebx = r->ebx - rd32(r, r->ebp - 0x58);
    r->edx = r->edi;
    set_low8(&r->ecx, (r->ebx & 0xff));
    r->eax = 0x1;
    r->edx = (uint32_t)((int32_t)r->edx >> (r->ecx & 0xff));
    set_low8(&r->ecx, rd8(r, r->ebp - 0x58));
    r->eax = r->eax << (r->ecx & 0xff);
    r->eax = r->eax - 1;
    r->edx = r->edx & r->eax;
    wr32(r, r->ebp - 0x58, r->edx);
    r->eax = r->edx;
    wr32(r, r->ebp - 0x54, rd32(r, r->ebp - 0x54) + r->eax);
at_4c3096:
    if (rd32(r, r->ebp - 0x54) <= 0x0)
    {
        goto at_4c314d;
    }
    r->eax = rd32(r, r->ebp - 0x18);
    r->eax = r->eax << 0x2;
    wr32(r, r->ebp - 0x34, r->eax);
    r->eax = rd32(r, r->ebp - 0x48);
    r->eax = r->eax << 0x2;
    wr32(r, r->ebp - 0x44, r->eax);
at_4c30b2:
    r->eax = rd32(r, r->ebp - 0x34);
    if ((int32_t)r->eax > (int32_t)rd32(r, r->ebp - 0x44))
    {
        goto at_4c314a;
    }
    r->esi = rd32(r, r->eax + 0x5000d0);
    r->eax = rd32(r, r->ebp - 0x20);
    r->esi = r->esi + r->esi;
    r->esi = r->esi + r->eax;
    if ((uint16_t)rd16(r, r->esi) != (uint16_t)0x0)
    {
        goto at_4c30ff;
    }
at_4c30d1:
    r->ecx = rd32(r, r->ebp - 0x34);
    r->esi = rd32(r, r->ebp - 0x18);
    r->ecx = r->ecx + 0x4;
    r->esi = r->esi + 1;
    wr32(r, r->ebp - 0x34, r->ecx);
    wr32(r, r->ebp - 0x18, r->esi);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4c30b2;
at_4c30e3:
    r->eax = rd32(r, r->ebp - 0x24);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4c2f9d;
at_4c30eb:
    r->edx = rd32(r, r->ebp - 0x58);
    r->edx = r->edx - 1;
    wr32(r, r->ebp - 0x58, r->edx);
    if ((int32_t)r->edx < 0 && !r->port->env.failed)
    {
        goto at_4c2fb7;
    }
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4c2fa0;
at_4c30ff:
    if ((int32_t)r->ebx >= (int32_t)0x1)
    {
        goto at_4c3121;
    }
    r->ecx = 0x1;
    r->eax = r->ebp - 0x6c;
    r->edx = r->edi;
    call_keep(r, 0x4bbf30);
    if (r->eax == 0 && !r->port->env.failed)
    {
        goto at_4c2e66;
    }
    r->edi = rd32(r, r->ebp - 0x64);
    r->ebx = rd32(r, r->ebp - 0x60);
at_4c3121:
    r->ebx = r->ebx - 1;
    r->eax = r->edi;
    set_low8(&r->ecx, (r->ebx & 0xff));
    r->eax = (uint32_t)((int32_t)r->eax >> (r->ecx & 0xff));
    if ((uint8_t)((r->eax & 0xff) & 0x1) == 0 && !r->port->env.failed)
    {
        goto at_4c30d1;
    }
    r->edx = rd32(r, r->ebp - 0x1c);
    r->eax = (uint32_t)(int32_t)(int16_t)rd16(r, r->esi);
    if ((r->eax & r->edx) != 0 && !r->port->env.failed)
    {
        goto at_4c30d1;
    }
    if ((int32_t)r->eax < 0)
    {
        goto at_4c3142;
    }
    r->eax = rd32(r, r->ebp - 0x1c);
    wr16(r, r->esi, rd16(r, r->esi) + (r->eax & 0xffff));
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4c30d1;
at_4c3142:
    r->eax = rd32(r, r->ebp - 0x24);
    wr16(r, r->esi, rd16(r, r->esi) + (r->eax & 0xffff));
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4c30d1;
at_4c314a:
    wr32(r, r->ebp - 0x54, rd32(r, r->ebp - 0x54) - 1);
at_4c314d:
    r->edx = rd32(r, r->ebp - 0x38);
    r->edx = rd32(r, r->edx + 0x18);
    r->eax = rd32(r, r->ebp - 0x6c);
    wr32(r, r->edx, r->eax);
    r->edx = rd32(r, r->ebp - 0x38);
    r->edx = rd32(r, r->edx + 0x18);
    r->eax = rd32(r, r->ebp - 0x68);
    wr32(r, r->edx + 0x4, r->eax);
    r->eax = rd32(r, r->ebp - 0x50);
    wr32(r, r->eax + 0xc, r->edi);
    r->edx = rd32(r, r->ebp - 0x50);
    wr32(r, r->eax + 0x10, r->ebx);
    r->eax = rd32(r, r->ebp - 0x54);
    wr32(r, r->edx + 0x14, r->eax);
at_4c3176:
    r->edx = rd32(r, r->ebp - 0x50);
    r->eax = 0x1;
    wr32(r, r->edx + 0x28, rd32(r, r->edx + 0x28) - r->eax);
    r->edi = rd32(r, r->ebp - 0x10);
    r->esi = rd32(r, r->ebp - 0xc);
    r->ecx = rd32(r, r->ebp - 0x8);
    r->ebx = rd32(r, r->ebp - 0x4);
    return;
at_4c318a:
    r->eax = 0;
    r->edi = rd32(r, r->ebp - 0x10);
    r->esi = rd32(r, r->ebp - 0xc);
    r->ecx = rd32(r, r->ebp - 0x8);
    r->ebx = rd32(r, r->ebp - 0x4);
    return;
at_4c2d33:
    r->edi = rd32(r, r->ebp - 0x10);
    r->esi = rd32(r, r->ebp - 0xc);
    r->ecx = rd32(r, r->ebp - 0x8);
    r->ebx = rd32(r, r->ebp - 0x4);
    return;
}

uint32_t vertrix_port_jpeg_decode_ac_refine_4c2d60(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x170
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
