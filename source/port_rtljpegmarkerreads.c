#include "port_rtljpegmarkerreads.h"

/* libjpeg read_markers: reads markers until a start of scan or end of image, handing each one to
 * its reader. */

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

/* An indirect call (an import or a method): every value pushed passed and popped, as stdcall. */
static void call_all(Regs *r, uint32_t target)
{
    call_with_stack(r, target, r->pushed, 0);
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

/* Original 0x4bf940: libjpeg read_markers: reads markers until a start of scan or end of image,
 * handing each one to its reader. Evidence: calls 0x4bf770, 0x4be0b0, 0x4b9200, 0x4b91e0, 0x4bf6a0.
 * Register-for-register from the listing (0x4bf94e..0x4c07c6); labels are the original addresses.
 */
static void run(Regs *r)
{
    wr32(r, r->ebp - 0x18, r->eax);
    if (rd32(r, r->eax + 0x1a0) != 0x0)
    {
        goto at_4bf9ed;
    }
at_4bf95e:
    r->eax = rd32(r, r->ebp - 0x18);
    r->eax = rd32(r, r->eax + 0x1b8);
    if (rd32(r, r->eax + 0xc) != 0x0)
    {
        goto at_4bfa80;
    }
    r->edx = rd32(r, r->ebp - 0x18);
    r->ecx = rd32(r, r->edx + 0x18);
    r->ebx = rd32(r, r->ecx + 0x4);
    r->esi = rd32(r, r->ecx);
    if (r->ebx != 0)
    {
        goto at_4bf992;
    }
    r->eax = r->edx;
    call_all(r, rd32(r, r->ecx + 0xc));
    if (r->eax == 0)
    {
        goto at_4bfa74;
    }
    r->esi = rd32(r, r->ecx);
    r->ebx = rd32(r, r->ecx + 0x4);
at_4bf992:
    r->esi = r->esi + 1;
    r->ebx = r->ebx - 1;
    r->edi = rd8(r, r->esi - 0x1);
    if (r->ebx != 0)
    {
        goto at_4bf9ae;
    }
    r->eax = r->edx;
    call_all(r, rd32(r, r->ecx + 0xc));
    if (r->eax == 0)
    {
        goto at_4bfa74;
    }
    r->esi = rd32(r, r->ecx);
    r->ebx = rd32(r, r->ecx + 0x4);
at_4bf9ae:
    r->eax = 0;
    r->ebx = r->ebx - 1;
    set_low8(&r->eax, rd8(r, r->esi));
    r->esi = r->esi + 1;
    wr32(r, r->ebp - 0x58, r->eax);
    if (r->edi == 0xff)
    {
        goto at_4bfa64;
    }
at_4bf9c3:
    r->eax = rd32(r, r->edx);
    wr32(r, r->eax + 0x14, 0x35);
    r->eax = rd32(r, r->edx);
    wr32(r, r->eax + 0x18, r->edi);
    r->eax = rd32(r, r->edx);
    r->edi = rd32(r, r->ebp - 0x58);
    wr32(r, r->eax + 0x1c, r->edi);
    r->edi = rd32(r, r->edx);
    r->eax = r->edx;
    call_all(r, rd32(r, r->edi));
at_4bf9df:
    r->eax = rd32(r, r->ebp - 0x58);
    wr32(r, r->edx + 0x1a0, r->eax);
    wr32(r, r->ecx, r->esi);
    wr32(r, r->ecx + 0x4, r->ebx);
at_4bf9ed:
    r->eax = rd32(r, r->ebp - 0x18);
    r->eax = rd32(r, r->eax + 0x1a0);
    flags(r, F_SUB, r->eax, 0xd6, 32);
    if (cond(r, CC_AE))
    {
        goto at_4c039b;
    }
    flags(r, F_SUB, r->eax, 0xca, 32);
    if (cond(r, CC_AE))
    {
        goto at_4c0712;
    }
    flags(r, F_SUB, r->eax, 0xc4, 32);
    if (cond(r, CC_AE))
    {
        goto at_4c074b;
    }
    flags(r, F_SUB, r->eax, 0xc1, 32);
    if (cond(r, CC_AE))
    {
        goto at_4c0782;
    }
    flags(r, F_SUB, r->eax, 0x1, 32);
    if (cond(r, CC_AE))
    {
        goto at_4c07b5;
    }
at_4bfa2b:
    r->eax = rd32(r, r->ebp - 0x18);
    r->eax = rd32(r, r->eax);
    r->edx = rd32(r, r->ebp - 0x18);
    wr32(r, r->eax + 0x14, 0x44);
    r->eax = rd32(r, r->ebp - 0x18);
    r->edx = rd32(r, r->edx);
    r->eax = rd32(r, r->eax + 0x1a0);
    wr32(r, r->edx + 0x18, r->eax);
at_4bfa48:
    r->edx = rd32(r, r->ebp - 0x18);
    r->edx = rd32(r, r->edx);
    r->eax = rd32(r, r->ebp - 0x18);
    call_all(r, rd32(r, r->edx));
at_4bfa52:
    r->eax = rd32(r, r->ebp - 0x18);
    wr32(r, r->eax + 0x1a0, 0x0);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4bf95e;
at_4bfa64:
    if (r->eax != 0xd8 && !r->port->env.failed)
    {
        goto at_4bf9c3;
    }
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4bf9df;
at_4bfa74:
    r->eax = 0;
    r->edi = rd32(r, r->ebp - 0x14);
    r->esi = rd32(r, r->ebp - 0x10);
    r->edx = rd32(r, r->ebp - 0xc);
    r->ecx = rd32(r, r->ebp - 0x8);
    r->ebx = rd32(r, r->ebp - 0x4);
    return;
at_4bfa80:
    r->eax = rd32(r, r->ebp - 0x18);
    call_keep(r, 0x4bf770);
    if (r->eax != 0 && !r->port->env.failed)
    {
        goto at_4bf9ed;
    }
    r->edi = rd32(r, r->ebp - 0x14);
    r->esi = rd32(r, r->ebp - 0x10);
    r->edx = rd32(r, r->ebp - 0xc);
    r->ecx = rd32(r, r->ebp - 0x8);
    r->ebx = rd32(r, r->ebp - 0x4);
    return;
at_4bfa9a:
    r->eax = rd32(r, r->ecx);
    wr32(r, r->eax + 0x14, 0x3d);
    r->edx = rd32(r, r->ecx);
    r->eax = r->ecx;
    call_all(r, rd32(r, r->edx));
    goto at_4c03ed;
at_4bfaae:
    r->eax = rd32(r, r->ebp - 0x18);
    r->ebx = 0;
    r->edx = 0;
    call_keep(r, 0x4be0b0);
    if (r->eax != 0 && !r->port->env.failed)
    {
        goto at_4bfa52;
    }
    r->edi = rd32(r, r->ebp - 0x14);
    r->esi = rd32(r, r->ebp - 0x10);
    r->edx = rd32(r, r->ebp - 0xc);
    r->ecx = rd32(r, r->ebp - 0x8);
    r->ebx = rd32(r, r->ebp - 0x4);
    return;
at_4bfac8:
    r->edx = 0x1;
    r->eax = rd32(r, r->ebp - 0x18);
    r->ebx = 0;
    call_keep(r, 0x4be0b0);
    if (r->eax != 0 && !r->port->env.failed)
    {
        goto at_4bfa52;
    }
    r->edi = rd32(r, r->ebp - 0x14);
    r->esi = rd32(r, r->ebp - 0x10);
    r->edx = rd32(r, r->ebp - 0xc);
    r->ecx = rd32(r, r->ebp - 0x8);
    r->ebx = rd32(r, r->ebp - 0x4);
    return;
at_4bfae9:
    r->ebx = 0x1;
    r->eax = rd32(r, r->ebp - 0x18);
    r->edx = r->ebx;
    call_keep(r, 0x4be0b0);
    if (r->eax != 0 && !r->port->env.failed)
    {
        goto at_4bfa52;
    }
    r->edi = rd32(r, r->ebp - 0x14);
    r->esi = rd32(r, r->ebp - 0x10);
    r->edx = rd32(r, r->ebp - 0xc);
    r->ecx = rd32(r, r->ebp - 0x8);
    r->ebx = rd32(r, r->ebp - 0x4);
    return;
at_4bfb0a:
    r->ecx = rd32(r, r->ebp - 0x18);
    r->eax = rd32(r, r->ecx + 0x18);
    wr32(r, r->ebp - 0x1c, r->eax);
    r->ebx = rd32(r, r->eax);
    r->esi = rd32(r, r->eax + 0x4);
    r->eax = rd32(r, r->ecx + 0x1b8);
    if (rd32(r, r->eax + 0x10) == 0x0)
    {
        goto at_4bfc94;
    }
at_4bfb28:
    if (r->esi == 0)
    {
        goto at_4bfca8;
    }
at_4bfb30:
    r->eax = 0;
    set_low8(&r->eax, rd8(r, r->ebx));
    r->esi = r->esi - 1;
    r->eax = r->eax << 0x8;
    r->ebx = r->ebx + 1;
    wr32(r, r->ebp - 0x60, r->eax);
    if (r->esi != 0)
    {
        goto at_4bfb55;
    }
    r->edx = rd32(r, r->ebp - 0x1c);
    r->eax = r->ecx;
    call_all(r, rd32(r, r->edx + 0xc));
    if (r->eax == 0 && !r->port->env.failed)
    {
        goto at_4bfa74;
    }
    r->ebx = rd32(r, r->edx);
    r->esi = rd32(r, r->edx + 0x4);
at_4bfb55:
    r->eax = 0;
    r->edx = rd32(r, r->ebp - 0x60);
    set_low8(&r->eax, rd8(r, r->ebx));
    r->esi = r->esi - 1;
    r->edx = r->edx + r->eax;
    r->ebx = r->ebx + 1;
    wr32(r, r->ebp - 0x60, r->edx);
    if (r->esi != 0)
    {
        goto at_4bfb7c;
    }
    r->edx = rd32(r, r->ebp - 0x1c);
    r->eax = r->ecx;
    call_all(r, rd32(r, r->edx + 0xc));
    if (r->eax == 0 && !r->port->env.failed)
    {
        goto at_4bfa74;
    }
    r->ebx = rd32(r, r->edx);
    r->esi = rd32(r, r->edx + 0x4);
at_4bfb7c:
    r->eax = 0;
    set_low8(&r->eax, rd8(r, r->ebx));
    wr32(r, r->ebp - 0x40, r->eax);
    r->eax = rd32(r, r->ecx);
    wr32(r, r->eax + 0x14, 0x67);
    r->eax = rd32(r, r->ecx);
    r->edx = rd32(r, r->ebp - 0x40);
    wr32(r, r->eax + 0x18, r->edx);
    r->edi = rd32(r, r->ecx);
    r->edx = 0x1;
    r->eax = r->ecx;
    call_all(r, rd32(r, r->edi + 0x4));
    r->eax = rd32(r, r->ebp - 0x40);
    r->esi = r->esi - 1;
    r->eax = r->eax + r->eax;
    r->edi = rd32(r, r->ebp - 0x60);
    r->eax = r->eax + 0x6;
    r->ebx = r->ebx + 1;
    if (r->eax == r->edi)
    {
        goto at_4bfcc2;
    }
at_4bfbb5:
    r->eax = rd32(r, r->ecx);
    wr32(r, r->eax + 0x14, 0xb);
    r->edx = rd32(r, r->ecx);
    r->eax = r->ecx;
    call_all(r, rd32(r, r->edx));
at_4bfbc4:
    r->edi = 0;
    r->eax = rd32(r, r->ebp - 0x40);
    wr32(r, r->ebp - 0x4c, r->edi);
    wr32(r, r->ecx + 0x148, r->eax);
at_4bfbd2:
    r->eax = rd32(r, r->ebp - 0x4c);
    if ((int32_t)r->eax >= (int32_t)rd32(r, r->ebp - 0x40))
    {
        goto at_4bfd04;
    }
    if (r->esi != 0)
    {
        goto at_4bfbf7;
    }
    r->edx = rd32(r, r->ebp - 0x1c);
    r->eax = r->ecx;
    call_all(r, rd32(r, r->edx + 0xc));
    if (r->eax == 0 && !r->port->env.failed)
    {
        goto at_4bfa74;
    }
    r->ebx = rd32(r, r->edx);
    r->esi = rd32(r, r->edx + 0x4);
at_4bfbf7:
    r->eax = 0;
    r->esi = r->esi - 1;
    set_low8(&r->eax, rd8(r, r->ebx));
    r->ebx = r->ebx + 1;
    wr32(r, r->ebp - 0x54, r->eax);
    if (r->esi != 0)
    {
        goto at_4bfc19;
    }
    r->edx = rd32(r, r->ebp - 0x1c);
    r->eax = r->ecx;
    call_all(r, rd32(r, r->edx + 0xc));
    if (r->eax == 0 && !r->port->env.failed)
    {
        goto at_4bfa74;
    }
    r->ebx = rd32(r, r->edx);
    r->esi = rd32(r, r->edx + 0x4);
at_4bfc19:
    r->eax = 0;
    r->esi = r->esi - 1;
    set_low8(&r->eax, rd8(r, r->ebx));
    r->ebx = r->ebx + 1;
    wr32(r, r->ebp - 0x6c, r->eax);
    r->eax = 0;
    r->edx = rd32(r, r->ecx + 0xd8);
at_4bfc2a:
    wr32(r, r->ebp - 0x64, r->eax);
    r->eax = rd32(r, r->ebp - 0x64);
    if ((int32_t)r->eax >= (int32_t)rd32(r, r->ecx + 0x24))
    {
        goto at_4bfce8;
    }
    r->eax = rd32(r, r->ebp - 0x54);
    if (r->eax != rd32(r, r->edx))
    {
        goto at_4bfcdc;
    }
at_4bfc44:
    r->eax = rd32(r, r->ebp - 0x4c);
    wr32(r, r->ecx + r->eax * 4 + 0x14c, r->edx);
    r->eax = rd32(r, r->ebp - 0x6c);
    r->eax = (uint32_t)((int32_t)r->eax >> 0x4);
    r->eax = r->eax & 0xf;
    wr32(r, r->edx + 0x14, r->eax);
    r->eax = rd32(r, r->ebp - 0x6c);
    r->eax = r->eax & 0xf;
    wr32(r, r->edx + 0x18, r->eax);
    r->eax = rd32(r, r->ecx);
    r->edi = rd32(r, r->ebp - 0x54);
    wr32(r, r->eax + 0x18, r->edi);
    r->edi = rd32(r, r->edx + 0x14);
    wr32(r, r->eax + 0x1c, r->edi);
    r->edx = rd32(r, r->edx + 0x18);
    wr32(r, r->eax + 0x20, r->edx);
    r->eax = rd32(r, r->ecx);
    wr32(r, r->eax + 0x14, 0x68);
    r->edi = rd32(r, r->ecx);
    r->edx = 0x1;
    r->eax = r->ecx;
    call_all(r, rd32(r, r->edi + 0x4));
    wr32(r, r->ebp - 0x4c, rd32(r, r->ebp - 0x4c) + 1);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4bfbd2;
at_4bfc94:
    r->eax = rd32(r, r->ecx);
    wr32(r, r->eax + 0x14, 0x3e);
    r->edx = rd32(r, r->ecx);
    r->eax = r->ecx;
    call_all(r, rd32(r, r->edx));
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4bfb28;
at_4bfca8:
    r->edx = rd32(r, r->ebp - 0x1c);
    r->eax = r->ecx;
    call_all(r, rd32(r, r->edx + 0xc));
    if (r->eax == 0 && !r->port->env.failed)
    {
        goto at_4bfa74;
    }
    r->ebx = rd32(r, r->edx);
    r->esi = rd32(r, r->edx + 0x4);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4bfb30;
at_4bfcc2:
    r->eax = rd32(r, r->ebp - 0x40);
    if ((int32_t)r->eax < (int32_t)0x1 && !r->port->env.failed)
    {
        goto at_4bfbb5;
    }
    if ((int32_t)r->eax > (int32_t)0x4 && !r->port->env.failed)
    {
        goto at_4bfbb5;
    }
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4bfbc4;
at_4bfcdc:
    r->eax = rd32(r, r->ebp - 0x64);
    r->eax = r->eax + 1;
    r->edx = r->edx + 0x54;
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4bfc2a;
at_4bfce8:
    r->eax = rd32(r, r->ecx);
    wr32(r, r->eax + 0x14, 0x5);
    r->eax = rd32(r, r->ecx);
    r->edi = rd32(r, r->ebp - 0x54);
    wr32(r, r->eax + 0x18, r->edi);
    r->edi = rd32(r, r->ecx);
    r->eax = r->ecx;
    call_all(r, rd32(r, r->edi));
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4bfc44;
at_4bfd04:
    if (r->esi != 0)
    {
        goto at_4bfd1d;
    }
    r->edx = rd32(r, r->ebp - 0x1c);
    r->eax = r->ecx;
    call_all(r, rd32(r, r->edx + 0xc));
    if (r->eax == 0 && !r->port->env.failed)
    {
        goto at_4bfa74;
    }
    r->ebx = rd32(r, r->edx);
    r->esi = rd32(r, r->edx + 0x4);
at_4bfd1d:
    r->eax = 0;
    r->esi = r->esi - 1;
    set_low8(&r->eax, rd8(r, r->ebx));
    r->ebx = r->ebx + 1;
    wr32(r, r->ecx + 0x190, r->eax);
    if (r->esi != 0)
    {
        goto at_4bfd42;
    }
    r->edx = rd32(r, r->ebp - 0x1c);
    r->eax = r->ecx;
    call_all(r, rd32(r, r->edx + 0xc));
    if (r->eax == 0 && !r->port->env.failed)
    {
        goto at_4bfa74;
    }
    r->ebx = rd32(r, r->edx);
    r->esi = rd32(r, r->edx + 0x4);
at_4bfd42:
    r->eax = 0;
    r->esi = r->esi - 1;
    set_low8(&r->eax, rd8(r, r->ebx));
    r->ebx = r->ebx + 1;
    wr32(r, r->ecx + 0x194, r->eax);
    if (r->esi != 0)
    {
        goto at_4bfd67;
    }
    r->edx = rd32(r, r->ebp - 0x1c);
    r->eax = r->ecx;
    call_all(r, rd32(r, r->edx + 0xc));
    if (r->eax == 0 && !r->port->env.failed)
    {
        goto at_4bfa74;
    }
    r->ebx = rd32(r, r->edx);
    r->esi = rd32(r, r->edx + 0x4);
at_4bfd67:
    r->eax = 0;
    set_low8(&r->eax, rd8(r, r->ebx));
    r->edx = r->eax;
    r->edx = (uint32_t)((int32_t)r->edx >> 0x4);
    r->eax = r->eax & 0xf;
    r->edx = r->edx & 0xf;
    wr32(r, r->ecx + 0x19c, r->eax);
    wr32(r, r->ecx + 0x198, r->edx);
    r->eax = rd32(r, r->ecx);
    r->edx = rd32(r, r->ecx + 0x190);
    wr32(r, r->eax + 0x18, r->edx);
    r->edx = rd32(r, r->ecx + 0x194);
    wr32(r, r->eax + 0x1c, r->edx);
    r->edx = rd32(r, r->ecx + 0x198);
    wr32(r, r->eax + 0x20, r->edx);
    r->edx = rd32(r, r->ecx + 0x19c);
    wr32(r, r->eax + 0x24, r->edx);
    r->eax = rd32(r, r->ecx);
    wr32(r, r->eax + 0x14, 0x69);
    r->edi = rd32(r, r->ecx);
    r->edx = 0x1;
    r->eax = r->ecx;
    call_all(r, rd32(r, r->edi + 0x4));
    r->eax = rd32(r, r->ecx + 0x1b8);
    wr32(r, r->eax + 0x14, 0x0);
    r->edi = rd32(r, r->ecx + 0x90);
    r->ebx = r->ebx + 1;
    r->edi = r->edi + 1;
    r->eax = rd32(r, r->ebp - 0x1c);
    wr32(r, r->ecx + 0x90, r->edi);
    r->esi = r->esi - 1;
    wr32(r, r->eax, r->ebx);
    wr32(r, r->eax + 0x4, r->esi);
    r->eax = rd32(r, r->ebp - 0x18);
    wr32(r, r->eax + 0x1a0, 0x0);
    r->eax = 0x1;
    r->edi = rd32(r, r->ebp - 0x14);
    r->esi = rd32(r, r->ebp - 0x10);
    r->edx = rd32(r, r->ebp - 0xc);
    r->ecx = rd32(r, r->ebp - 0x8);
    r->ebx = rd32(r, r->ebp - 0x4);
    return;
at_4bfdfd:
    r->eax = rd32(r, r->ebp - 0x18);
    r->eax = rd32(r, r->eax);
    r->ecx = rd32(r, r->ebp - 0x18);
    wr32(r, r->eax + 0x14, 0x55);
    r->ecx = rd32(r, r->ecx);
    r->edx = 0x1;
    r->eax = rd32(r, r->ebp - 0x18);
    call_all(r, rd32(r, r->ecx + 0x4));
    r->eax = rd32(r, r->ebp - 0x18);
    wr32(r, r->eax + 0x1a0, 0x0);
    r->eax = 0x2;
    r->edi = rd32(r, r->ebp - 0x14);
    r->esi = rd32(r, r->ebp - 0x10);
    r->edx = rd32(r, r->ebp - 0xc);
    r->ecx = rd32(r, r->ebp - 0x8);
    r->ebx = rd32(r, r->ebp - 0x4);
    return;
at_4bfe35:
    r->ebx = rd32(r, r->ebp - 0x18);
    r->eax = rd32(r, r->ebx + 0x18);
    wr32(r, r->ebp - 0x2c, r->eax);
    r->eax = rd32(r, r->eax);
    wr32(r, r->ebp - 0x24, r->eax);
    r->eax = rd32(r, r->ebp - 0x2c);
    r->eax = rd32(r, r->eax + 0x4);
    wr32(r, r->ebp - 0x28, r->eax);
    if (r->eax == 0)
    {
        goto at_4c005f;
    }
at_4bfe54:
    r->edx = rd32(r, r->ebp - 0x24);
    r->eax = 0;
    set_low8(&r->eax, rd8(r, r->edx));
    r->eax = r->eax << 0x8;
    r->edi = rd32(r, r->ebp - 0x28);
    wr32(r, r->ebp - 0x30, r->eax);
    r->eax = r->edx + 0x1;
    r->edi = r->edi - 1;
    flags(r, F_DEC, r->edi, 0, 32);
    wr32(r, r->ebp - 0x28, r->edi);
    wr32(r, r->ebp - 0x24, r->eax);
    if (cond(r, CC_E))
    {
        goto at_4c007f;
    }
at_4bfe74:
    r->edx = rd32(r, r->ebp - 0x24);
    r->ecx = rd32(r, r->ebp - 0x28);
    r->edi = rd32(r, r->ebp - 0x30);
    r->eax = 0;
    r->ecx = r->ecx - 1;
    set_low8(&r->eax, rd8(r, r->edx));
    r->esi = r->edx + 0x1;
    r->edi = r->edi + r->eax;
    wr32(r, r->ebp - 0x28, r->ecx);
    wr32(r, r->ebp - 0x30, r->edi);
    r->eax = r->edi - 0x2;
    wr32(r, r->ebp - 0x24, r->esi);
    wr32(r, r->ebp - 0x30, r->eax);
at_4bfe96:
    r->edx = rd32(r, r->ebp - 0x30);
    if ((int32_t)r->edx <= (int32_t)0x10)
    {
        goto at_4c0144;
    }
    if (rd32(r, r->ebp - 0x28) != 0x0)
    {
        goto at_4bfec3;
    }
    r->edx = rd32(r, r->ebp - 0x2c);
    r->eax = r->ebx;
    call_all(r, rd32(r, r->edx + 0xc));
    if (r->eax == 0 && !r->port->env.failed)
    {
        goto at_4bfa74;
    }
    r->eax = rd32(r, r->edx);
    wr32(r, r->ebp - 0x24, r->eax);
    r->eax = rd32(r, r->edx + 0x4);
    wr32(r, r->ebp - 0x28, r->eax);
at_4bfec3:
    r->eax = rd32(r, r->ebp - 0x24);
    r->ecx = 0;
    set_low8(&r->ecx, rd8(r, r->eax));
    r->eax = rd32(r, r->ebx);
    wr32(r, r->eax + 0x14, 0x50);
    r->eax = rd32(r, r->ebx);
    r->edi = rd32(r, r->ebp - 0x28);
    r->edx = 0x1;
    wr32(r, r->eax + 0x18, r->ecx);
    r->eax = rd32(r, r->ebp - 0x24);
    r->edi = r->edi - 1;
    r->eax = r->eax + 1;
    r->esi = rd32(r, r->ebx);
    wr32(r, r->ebp - 0x24, r->eax);
    r->eax = r->ebx;
    wr32(r, r->ebp - 0x28, r->edi);
    call_all(r, rd32(r, r->esi + 0x4));
    r->edx = 0x1;
    set_high8(&r->eax, 0);
    r->esi = 0;
    wr8(r, r->ebp - 0x80, ((r->eax >> 8) & 0xff));
at_4bfefe:
    if (rd32(r, r->ebp - 0x28) != 0x0)
    {
        goto at_4bff1f;
    }
    r->edi = rd32(r, r->ebp - 0x2c);
    r->eax = r->ebx;
    call_all(r, rd32(r, r->edi + 0xc));
    if (r->eax == 0 && !r->port->env.failed)
    {
        goto at_4bfa74;
    }
    r->eax = rd32(r, r->edi);
    wr32(r, r->ebp - 0x24, r->eax);
    r->eax = rd32(r, r->edi + 0x4);
    wr32(r, r->ebp - 0x28, r->eax);
at_4bff1f:
    r->eax = rd32(r, r->ebp - 0x24);
    r->edi = rd32(r, r->ebp - 0x28);
    r->edx = r->edx + 1;
    r->edi = r->edi - 1;
    set_low8(&r->eax, rd8(r, r->eax));
    wr32(r, r->ebp - 0x28, r->edi);
    wr8(r, r->edx + r->ebp - 0x81, (r->eax & 0xff));
    r->edi = rd32(r, r->ebp - 0x24);
    r->eax = 0;
    r->edi = r->edi + 1;
    set_low8(&r->eax, rd8(r, r->edx + r->ebp - 0x81));
    wr32(r, r->ebp - 0x24, r->edi);
    r->esi = r->esi + r->eax;
    if ((int32_t)r->edx <= (int32_t)0x10 && !r->port->env.failed)
    {
        goto at_4bfefe;
    }
    wr32(r, r->ebp - 0x30, rd32(r, r->ebp - 0x30) - 0x11);
    r->eax = 0;
    r->edx = rd32(r, r->ebx);
    set_low8(&r->eax, rd8(r, r->ebp - 0x7f));
    wr32(r, r->edx + 0x18, r->eax);
    r->eax = 0;
    set_low8(&r->eax, rd8(r, r->ebp - 0x7e));
    wr32(r, r->edx + 0x1c, r->eax);
    r->eax = 0;
    set_low8(&r->eax, rd8(r, r->ebp - 0x7d));
    wr32(r, r->edx + 0x20, r->eax);
    r->eax = 0;
    set_low8(&r->eax, rd8(r, r->ebp - 0x7c));
    wr32(r, r->edx + 0x24, r->eax);
    r->eax = 0;
    set_low8(&r->eax, rd8(r, r->ebp - 0x7b));
    wr32(r, r->edx + 0x28, r->eax);
    r->eax = 0;
    set_low8(&r->eax, rd8(r, r->ebp - 0x7a));
    wr32(r, r->edx + 0x2c, r->eax);
    r->eax = 0;
    set_low8(&r->eax, rd8(r, r->ebp - 0x79));
    wr32(r, r->edx + 0x30, r->eax);
    r->eax = 0;
    set_low8(&r->eax, rd8(r, r->ebp - 0x78));
    wr32(r, r->edx + 0x34, r->eax);
    r->eax = rd32(r, r->ebx);
    wr32(r, r->eax + 0x14, 0x56);
    r->edi = rd32(r, r->ebx);
    r->edx = 0x2;
    r->eax = r->ebx;
    call_all(r, rd32(r, r->edi + 0x4));
    r->eax = 0;
    r->edx = rd32(r, r->ebx);
    set_low8(&r->eax, rd8(r, r->ebp - 0x77));
    wr32(r, r->edx + 0x18, r->eax);
    r->eax = 0;
    set_low8(&r->eax, rd8(r, r->ebp - 0x76));
    wr32(r, r->edx + 0x1c, r->eax);
    r->eax = 0;
    set_low8(&r->eax, rd8(r, r->ebp - 0x75));
    wr32(r, r->edx + 0x20, r->eax);
    r->eax = 0;
    set_low8(&r->eax, rd8(r, r->ebp - 0x74));
    wr32(r, r->edx + 0x24, r->eax);
    r->eax = 0;
    set_low8(&r->eax, rd8(r, r->ebp - 0x73));
    wr32(r, r->edx + 0x28, r->eax);
    r->eax = 0;
    set_low8(&r->eax, rd8(r, r->ebp - 0x72));
    wr32(r, r->edx + 0x2c, r->eax);
    r->eax = 0;
    set_low8(&r->eax, rd8(r, r->ebp - 0x71));
    wr32(r, r->edx + 0x30, r->eax);
    r->eax = 0;
    set_low8(&r->eax, rd8(r, r->ebp - 0x70));
    wr32(r, r->edx + 0x34, r->eax);
    r->eax = rd32(r, r->ebx);
    wr32(r, r->eax + 0x14, 0x56);
    r->edi = rd32(r, r->ebx);
    r->edx = 0x2;
    r->eax = r->ebx;
    call_all(r, rd32(r, r->edi + 0x4));
    if ((int32_t)r->esi <= (int32_t)0x100)
    {
        goto at_4c009f;
    }
at_4c0008:
    r->eax = rd32(r, r->ebx);
    wr32(r, r->eax + 0x14, 0x8);
    r->edx = rd32(r, r->ebx);
    r->eax = r->ebx;
    call_all(r, rd32(r, r->edx));
at_4c0017:
    r->edi = 0;
at_4c0019:
    if ((int32_t)r->edi >= (int32_t)r->esi)
    {
        goto at_4c00ad;
    }
    if (rd32(r, r->ebp - 0x28) != 0x0)
    {
        goto at_4c0042;
    }
    r->edx = rd32(r, r->ebp - 0x2c);
    r->eax = r->ebx;
    call_all(r, rd32(r, r->edx + 0xc));
    if (r->eax == 0 && !r->port->env.failed)
    {
        goto at_4bfa74;
    }
    r->eax = rd32(r, r->edx);
    wr32(r, r->ebp - 0x24, r->eax);
    r->eax = rd32(r, r->edx + 0x4);
    wr32(r, r->ebp - 0x28, r->eax);
at_4c0042:
    r->eax = rd32(r, r->ebp - 0x24);
    r->edi = r->edi + 1;
    set_low8(&r->eax, rd8(r, r->eax));
    r->edx = rd32(r, r->ebp - 0x24);
    wr8(r, r->edi + r->ebp - 0x181, (r->eax & 0xff));
    r->eax = rd32(r, r->ebp - 0x28);
    r->edx = r->edx + 1;
    r->eax = r->eax - 1;
    wr32(r, r->ebp - 0x24, r->edx);
    wr32(r, r->ebp - 0x28, r->eax);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4c0019;
at_4c005f:
    r->edx = rd32(r, r->ebp - 0x2c);
    r->eax = r->ebx;
    call_all(r, rd32(r, r->edx + 0xc));
    if (r->eax == 0 && !r->port->env.failed)
    {
        goto at_4bfa74;
    }
    r->eax = rd32(r, r->edx);
    wr32(r, r->ebp - 0x24, r->eax);
    r->eax = rd32(r, r->edx + 0x4);
    wr32(r, r->ebp - 0x28, r->eax);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4bfe54;
at_4c007f:
    r->edx = rd32(r, r->ebp - 0x2c);
    r->eax = r->ebx;
    call_all(r, rd32(r, r->edx + 0xc));
    if (r->eax == 0 && !r->port->env.failed)
    {
        goto at_4bfa74;
    }
    r->eax = rd32(r, r->edx);
    wr32(r, r->ebp - 0x24, r->eax);
    r->eax = rd32(r, r->edx + 0x4);
    wr32(r, r->ebp - 0x28, r->eax);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4bfe74;
at_4c009f:
    if ((int32_t)r->esi > (int32_t)rd32(r, r->ebp - 0x30) && !r->port->env.failed)
    {
        goto at_4c0008;
    }
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4c0017;
at_4c00ad:
    wr32(r, r->ebp - 0x30, rd32(r, r->ebp - 0x30) - r->esi);
    if ((uint8_t)((r->ecx & 0xff) & 0x10) == 0)
    {
        goto at_4c0135;
    }
    r->ecx = r->ecx - 0x10;
    r->edx = r->ebx + 0xc4;
    r->eax = r->ecx * 4;
at_4c00c9:
    r->edx = r->edx + r->eax;
    if ((int32_t)r->ecx < 0)
    {
        goto at_4c00d4;
    }
    if ((int32_t)r->ecx < (int32_t)0x4)
    {
        goto at_4c00e8;
    }
at_4c00d4:
    r->eax = rd32(r, r->ebx);
    wr32(r, r->eax + 0x14, 0x1e);
    r->eax = rd32(r, r->ebx);
    wr32(r, r->eax + 0x18, r->ecx);
    r->ecx = rd32(r, r->ebx);
    r->eax = r->ebx;
    call_all(r, rd32(r, r->ecx));
at_4c00e8:
    if (rd32(r, r->edx) != 0x0)
    {
        goto at_4c00f6;
    }
    r->eax = r->ebx;
    call_keep(r, 0x4b9200);
    wr32(r, r->edx, r->eax);
at_4c00f6:
    r->ecx = 0x11;
    r->esi = r->ebp - 0x80;
    r->edi = rd32(r, r->edx);
    push(r, r->edi);
    r->eax = r->ecx;
    r->ecx = r->ecx >> 0x2;
    rep_movs(r, 4);
    set_low8(&r->ecx, (r->eax & 0xff));
    set_low8(&r->ecx, (r->ecx & 0xff) & 0x3);
    rep_movs(r, 1);
    r->edi = pop(r);
    r->ecx = 0x100;
    r->edi = rd32(r, r->edx);
    r->esi = r->ebp - 0x180;
    r->edi = r->edi + 0x11;
    push(r, r->edi);
    r->eax = r->ecx;
    r->ecx = r->ecx >> 0x2;
    rep_movs(r, 4);
    set_low8(&r->ecx, (r->eax & 0xff));
    set_low8(&r->ecx, (r->ecx & 0xff) & 0x3);
    rep_movs(r, 1);
    r->edi = pop(r);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4bfe96;
at_4c0135:
    r->eax = r->ecx * 4;
    r->edx = r->ebx + 0xb4;
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4c00c9;
at_4c0144:
    if (r->edx == 0)
    {
        goto at_4c0157;
    }
    r->eax = rd32(r, r->ebx);
    wr32(r, r->eax + 0x14, 0xb);
    r->edx = rd32(r, r->ebx);
    r->eax = r->ebx;
    call_all(r, rd32(r, r->edx));
at_4c0157:
    r->eax = rd32(r, r->ebp - 0x2c);
    r->edx = rd32(r, r->ebp - 0x24);
    wr32(r, r->eax, r->edx);
    r->edx = rd32(r, r->ebp - 0x2c);
    r->eax = rd32(r, r->ebp - 0x28);
    wr32(r, r->edx + 0x4, r->eax);
    r->eax = rd32(r, r->ebp - 0x18);
    wr32(r, r->eax + 0x1a0, 0x0);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4bf95e;
at_4c017a:
    r->edx = rd32(r, r->ebp - 0x20);
    r->eax = r->ecx;
    call_all(r, rd32(r, r->edx + 0xc));
    if (r->eax == 0 && !r->port->env.failed)
    {
        goto at_4bfa74;
    }
    r->ebx = rd32(r, r->edx);
    r->esi = rd32(r, r->edx + 0x4);
    goto at_4c0525;
at_4c0194:
    r->edx = rd32(r, r->ebp - 0x20);
    r->eax = r->ecx;
    call_all(r, rd32(r, r->edx + 0xc));
    if (r->eax == 0 && !r->port->env.failed)
    {
        goto at_4bfa74;
    }
    r->ebx = rd32(r, r->edx);
    r->esi = rd32(r, r->edx + 0x4);
    goto at_4c0539;
at_4c01ae:
    if (r->esi != 0)
    {
        goto at_4c01ca;
    }
    r->ebx = rd32(r, r->ebp - 0x20);
    r->eax = r->ecx;
    call_all(r, rd32(r, r->ebx + 0xc));
    if (r->eax == 0 && !r->port->env.failed)
    {
        goto at_4bfa74;
    }
    r->esi = rd32(r, r->ebp - 0x20);
    r->ebx = rd32(r, r->ebx);
    r->esi = rd32(r, r->esi + 0x4);
at_4c01ca:
    r->eax = 0;
    r->esi = r->esi - 1;
    set_low8(&r->eax, rd8(r, r->ebx));
    r->ebx = r->ebx + 1;
    wr32(r, r->ebp - 0x48, r->eax);
    goto at_4c064e;
at_4c01d8:
    if (cond(r, CC_E))
    {
        goto at_4c01e9;
    }
    r->eax = rd32(r, r->ecx);
    wr32(r, r->eax + 0x14, 0xb);
    r->edx = rd32(r, r->ecx);
    r->eax = r->ecx;
    call_all(r, rd32(r, r->edx));
at_4c01e9:
    r->eax = rd32(r, r->ebp - 0x20);
    wr32(r, r->eax, r->ebx);
    wr32(r, r->eax + 0x4, r->esi);
    r->eax = rd32(r, r->ebp - 0x18);
    wr32(r, r->eax + 0x1a0, 0x0);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4bf95e;
at_4c0203:
    r->eax = rd32(r, r->ebp - 0x18);
    r->esi = rd32(r, r->eax + 0x18);
    wr32(r, r->ebp - 0x34, r->eax);
    r->ecx = rd32(r, r->esi + 0x4);
    r->ebx = rd32(r, r->esi);
    if (r->ecx == 0)
    {
        goto at_4c02dc;
    }
at_4c0219:
    r->edx = 0;
    r->ecx = r->ecx - 1;
    set_low8(&r->edx, rd8(r, r->ebx));
    r->ebx = r->ebx + 1;
    r->edx = r->edx << 0x8;
    if (r->ecx == 0)
    {
        goto at_4c02f1;
    }
at_4c022a:
    r->eax = 0;
    set_low8(&r->eax, rd8(r, r->ebx));
    r->ecx = r->ecx - 1;
    r->edx = r->edx + r->eax;
    r->ebx = r->ebx + 1;
    if (r->edx == 0x4)
    {
        goto at_4c024d;
    }
    r->eax = rd32(r, r->ebp - 0x34);
    r->eax = rd32(r, r->eax);
    r->edx = rd32(r, r->ebp - 0x34);
    wr32(r, r->eax + 0x14, 0xb);
    r->edx = rd32(r, r->edx);
    r->eax = rd32(r, r->ebp - 0x34);
    call_all(r, rd32(r, r->edx));
at_4c024d:
    if (r->ecx != 0)
    {
        goto at_4c0264;
    }
    r->eax = rd32(r, r->ebp - 0x34);
    call_all(r, rd32(r, r->esi + 0xc));
    if (r->eax == 0 && !r->port->env.failed)
    {
        goto at_4bfa74;
    }
    r->ebx = rd32(r, r->esi);
    r->ecx = rd32(r, r->esi + 0x4);
at_4c0264:
    r->eax = 0;
    set_low8(&r->eax, rd8(r, r->ebx));
    r->ecx = r->ecx - 1;
    r->eax = r->eax << 0x8;
    r->ebx = r->ebx + 1;
    wr32(r, r->ebp - 0x50, r->eax);
    if (r->ecx != 0)
    {
        goto at_4c0287;
    }
    r->eax = rd32(r, r->ebp - 0x34);
    call_all(r, rd32(r, r->esi + 0xc));
    if (r->eax == 0 && !r->port->env.failed)
    {
        goto at_4bfa74;
    }
    r->ebx = rd32(r, r->esi);
    r->ecx = rd32(r, r->esi + 0x4);
at_4c0287:
    r->eax = 0;
    r->edx = rd32(r, r->ebp - 0x50);
    set_low8(&r->eax, rd8(r, r->ebx));
    r->edx = r->edx + r->eax;
    r->eax = rd32(r, r->ebp - 0x34);
    r->eax = rd32(r, r->eax);
    wr32(r, r->eax + 0x14, 0x52);
    r->eax = rd32(r, r->ebp - 0x34);
    r->eax = rd32(r, r->eax);
    r->edi = rd32(r, r->ebp - 0x34);
    wr32(r, r->eax + 0x18, r->edx);
    wr32(r, r->ebp - 0x50, r->edx);
    r->edi = rd32(r, r->edi);
    r->edx = 0x1;
    r->eax = rd32(r, r->ebp - 0x34);
    call_all(r, rd32(r, r->edi + 0x4));
    r->edx = rd32(r, r->ebp - 0x34);
    r->eax = rd32(r, r->ebp - 0x50);
    r->ebx = r->ebx + 1;
    wr32(r, r->edx + 0x114, r->eax);
    r->ecx = r->ecx - 1;
    wr32(r, r->esi, r->ebx);
    wr32(r, r->esi + 0x4, r->ecx);
    r->eax = rd32(r, r->ebp - 0x18);
    wr32(r, r->eax + 0x1a0, 0x0);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4bf95e;
at_4c02dc:
    call_all(r, rd32(r, r->esi + 0xc));
    if (r->eax == 0 && !r->port->env.failed)
    {
        goto at_4bfa74;
    }
    r->ebx = rd32(r, r->esi);
    r->ecx = rd32(r, r->esi + 0x4);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4c0219;
at_4c02f1:
    r->eax = rd32(r, r->ebp - 0x34);
    call_all(r, rd32(r, r->esi + 0xc));
    if (r->eax == 0 && !r->port->env.failed)
    {
        goto at_4bfa74;
    }
    r->ebx = rd32(r, r->esi);
    r->ecx = rd32(r, r->esi + 0x4);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4c022a;
at_4c0309:
    r->eax = rd32(r, r->ebp - 0x18);
    r->edx = rd32(r, r->ebp - 0x18);
    r->eax = rd32(r, r->eax + 0x1a0);
    r->edx = rd32(r, r->edx + 0x1b8);
    r->eax = r->eax << 0x2;
    r->edx = r->edx + r->eax;
    r->eax = rd32(r, r->ebp - 0x18);
    call_all(r, rd32(r, r->edx - 0x360));
    if (r->eax != 0 && !r->port->env.failed)
    {
        goto at_4bfa52;
    }
    r->edi = rd32(r, r->ebp - 0x14);
    r->esi = rd32(r, r->ebp - 0x10);
    r->edx = rd32(r, r->ebp - 0xc);
    r->ecx = rd32(r, r->ebp - 0x8);
    r->ebx = rd32(r, r->ebp - 0x4);
    return;
at_4c033b:
    r->edx = rd32(r, r->ebp - 0x18);
    r->edx = rd32(r, r->edx + 0x1b8);
    r->eax = rd32(r, r->ebp - 0x18);
    call_all(r, rd32(r, r->edx + 0x1c));
    if (r->eax != 0 && !r->port->env.failed)
    {
        goto at_4bfa52;
    }
    r->edi = rd32(r, r->ebp - 0x14);
    r->esi = rd32(r, r->ebp - 0x10);
    r->edx = rd32(r, r->ebp - 0xc);
    r->ecx = rd32(r, r->ebp - 0x8);
    r->ebx = rd32(r, r->ebp - 0x4);
    return;
at_4c035c:
    r->eax = rd32(r, r->ebp - 0x18);
    r->eax = rd32(r, r->eax);
    r->edx = rd32(r, r->ebp - 0x18);
    wr32(r, r->eax + 0x14, 0x5c);
    r->eax = rd32(r, r->ebp - 0x18);
    r->edx = rd32(r, r->edx);
    r->eax = rd32(r, r->eax + 0x1a0);
    r->ecx = rd32(r, r->ebp - 0x18);
    wr32(r, r->edx + 0x18, r->eax);
    r->ecx = rd32(r, r->ecx);
    r->edx = 0x1;
    r->eax = rd32(r, r->ebp - 0x18);
    call_all(r, rd32(r, r->ecx + 0x4));
    r->eax = rd32(r, r->ebp - 0x18);
    wr32(r, r->eax + 0x1a0, 0x0);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4bf95e;
at_4c039b:
    if (cond(r, CC_BE) && !r->port->env.failed)
    {
        goto at_4c035c;
    }
    flags(r, F_SUB, r->eax, 0xe4, 32);
    if (cond(r, CC_AE))
    {
        goto at_4c0489;
    }
    flags(r, F_SUB, r->eax, 0xdc, 32);
    if (cond(r, CC_AE))
    {
        goto at_4c04d2;
    }
    flags(r, F_SUB, r->eax, 0xd9, 32);
    if (cond(r, CC_AE))
    {
        goto at_4c04fe;
    }
    if (r->eax <= 0xd7 && !r->port->env.failed)
    {
        goto at_4c035c;
    }
    r->ecx = rd32(r, r->ebp - 0x18);
    r->eax = rd32(r, r->ecx);
    wr32(r, r->eax + 0x14, 0x66);
    r->ebx = rd32(r, r->ecx);
    r->edx = 0x1;
    r->eax = r->ecx;
    call_all(r, rd32(r, r->ebx + 0x4));
    r->eax = rd32(r, r->ecx + 0x1b8);
    if (rd32(r, r->eax + 0xc) != 0x0 && !r->port->env.failed)
    {
        goto at_4bfa9a;
    }
at_4c03ed:
    r->eax = 0;
at_4c03ef:
    r->edx = r->ecx + r->eax;
    wr8(r, r->edx + 0xe4, 0x0);
    wr8(r, r->edx + 0xf4, 0x1);
    r->eax = r->eax + 1;
    wr8(r, r->edx + 0x104, 0x5);
    if ((int32_t)r->eax < (int32_t)0x10 && !r->port->env.failed)
    {
        goto at_4c03ef;
    }
    wr32(r, r->ecx + 0x114, 0x0);
    wr32(r, r->ecx + 0x28, 0x0);
    wr32(r, r->ecx + 0x12c, 0x0);
    wr32(r, r->ecx + 0x118, 0x0);
    wr8(r, r->ecx + 0x11c, 0x1);
    wr8(r, r->ecx + 0x11d, 0x1);
    wr8(r, r->ecx + 0x11e, 0x0);
    wr16(r, r->ecx + 0x120, 0x1);
    wr16(r, r->ecx + 0x122, 0x1);
    wr32(r, r->ecx + 0x124, 0x0);
    r->eax = rd32(r, r->ecx + 0x1b8);
    wr8(r, r->ecx + 0x128, 0x0);
    wr32(r, r->eax + 0xc, 0x1);
    r->eax = rd32(r, r->ebp - 0x18);
    wr32(r, r->eax + 0x1a0, 0x0);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4bf95e;
at_4c0489:
    if (cond(r, CC_BE) && !r->port->env.failed)
    {
        goto at_4c0309;
    }
    flags(r, F_SUB, r->eax, 0xea, 32);
    if (cond(r, CC_B) && !r->port->env.failed)
    {
        goto at_4c0309;
    }
    if (cond(r, CC_BE) && !r->port->env.failed)
    {
        goto at_4c0309;
    }
    flags(r, F_SUB, r->eax, 0xed, 32);
    if (cond(r, CC_B) && !r->port->env.failed)
    {
        goto at_4c0309;
    }
    if (cond(r, CC_BE) && !r->port->env.failed)
    {
        goto at_4c0309;
    }
    flags(r, F_SUB, r->eax, 0xef, 32);
    if (cond(r, CC_B) && !r->port->env.failed)
    {
        goto at_4c0309;
    }
    if (cond(r, CC_BE) && !r->port->env.failed)
    {
        goto at_4c0309;
    }
    if (r->eax == 0xfe && !r->port->env.failed)
    {
        goto at_4c033b;
    }
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4bfa2b;
at_4c04d2:
    if (cond(r, CC_BE))
    {
        goto at_4c0731;
    }
    if (r->eax >= 0xe1 && !r->port->env.failed)
    {
        goto at_4c0309;
    }
    if (r->eax <= 0xdd && !r->port->env.failed)
    {
        goto at_4c0203;
    }
    if (r->eax == 0xe0 && !r->port->env.failed)
    {
        goto at_4c0309;
    }
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4bfa2b;
at_4c04fe:
    if (cond(r, CC_BE) && !r->port->env.failed)
    {
        goto at_4bfdfd;
    }
    if (r->eax <= 0xda && !r->port->env.failed)
    {
        goto at_4bfb0a;
    }
    r->ecx = rd32(r, r->ebp - 0x18);
    r->eax = rd32(r, r->ecx + 0x18);
    wr32(r, r->ebp - 0x20, r->eax);
    r->esi = rd32(r, r->eax + 0x4);
    r->ebx = rd32(r, r->eax);
    if (r->esi == 0 && !r->port->env.failed)
    {
        goto at_4c017a;
    }
at_4c0525:
    r->eax = 0;
    set_low8(&r->eax, rd8(r, r->ebx));
    r->esi = r->esi - 1;
    r->eax = r->eax << 0x8;
    r->ebx = r->ebx + 1;
    wr32(r, r->ebp - 0x38, r->eax);
    if (r->esi == 0 && !r->port->env.failed)
    {
        goto at_4c0194;
    }
at_4c0539:
    r->eax = 0;
    r->edi = rd32(r, r->ebp - 0x38);
    set_low8(&r->eax, rd8(r, r->ebx));
    r->edi = r->edi + r->eax;
    r->esi = r->esi - 1;
    wr32(r, r->ebp - 0x38, r->edi);
    r->eax = r->edi - 0x2;
    r->ebx = r->ebx + 1;
    wr32(r, r->ebp - 0x38, r->eax);
at_4c054d:
    r->edx = rd32(r, r->ebp - 0x38);
    flags(r, F_LOGIC, r->edx, 0, 32);
    if (cond(r, CC_LE) && !r->port->env.failed)
    {
        goto at_4c01d8;
    }
    if (r->esi != 0)
    {
        goto at_4c0571;
    }
    r->edx = rd32(r, r->ebp - 0x20);
    r->eax = r->ecx;
    call_all(r, rd32(r, r->edx + 0xc));
    if (r->eax == 0 && !r->port->env.failed)
    {
        goto at_4bfa74;
    }
    r->ebx = rd32(r, r->edx);
    r->esi = rd32(r, r->edx + 0x4);
at_4c0571:
    r->eax = 0;
    set_low8(&r->eax, rd8(r, r->ebx));
    wr32(r, r->ebp - 0x3c, r->eax);
    r->eax = (uint32_t)((int32_t)r->eax >> 0x4);
    wr32(r, r->ebp - 0x5c, r->eax);
    wr32(r, r->ebp - 0x3c, rd32(r, r->ebp - 0x3c) & 0xf);
    r->eax = rd32(r, r->ecx);
    wr32(r, r->eax + 0x14, 0x51);
    r->eax = rd32(r, r->ecx);
    r->edx = rd32(r, r->ebp - 0x3c);
    wr32(r, r->eax + 0x18, r->edx);
    r->eax = rd32(r, r->ecx);
    r->edx = rd32(r, r->ebp - 0x5c);
    wr32(r, r->eax + 0x1c, r->edx);
    r->edx = 0x1;
    r->edi = rd32(r, r->ecx);
    r->eax = r->ecx;
    r->esi = r->esi - 1;
    call_all(r, rd32(r, r->edi + 0x4));
    r->edx = rd32(r, r->ebp - 0x3c);
    r->ebx = r->ebx + 1;
    if ((int32_t)r->edx < (int32_t)0x4)
    {
        goto at_4c05c5;
    }
    r->eax = rd32(r, r->ecx);
    wr32(r, r->eax + 0x14, 0x1f);
    r->eax = rd32(r, r->ecx);
    wr32(r, r->eax + 0x18, r->edx);
    r->edx = rd32(r, r->ecx);
    r->eax = r->ecx;
    call_all(r, rd32(r, r->edx));
at_4c05c5:
    r->edx = rd32(r, r->ebp - 0x3c);
    r->edx = r->edx << 0x2;
    r->edx = r->edx + r->ecx;
    if (rd32(r, r->edx + 0xa4) != 0x0)
    {
        goto at_4c05e3;
    }
    r->eax = r->ecx;
    call_keep(r, 0x4b91e0);
    wr32(r, r->edx + 0xa4, r->eax);
at_4c05e3:
    r->eax = rd32(r, r->ebp - 0x3c);
    r->eax = rd32(r, r->ecx + r->eax * 4 + 0xa4);
    r->edx = 0;
    wr32(r, r->ebp - 0x68, r->eax);
at_4c05f2:
    if (rd32(r, r->ebp - 0x5c) == 0x0 && !r->port->env.failed)
    {
        goto at_4c01ae;
    }
    if (r->esi != 0)
    {
        goto at_4c0618;
    }
    r->ebx = rd32(r, r->ebp - 0x20);
    r->eax = r->ecx;
    call_all(r, rd32(r, r->ebx + 0xc));
    if (r->eax == 0 && !r->port->env.failed)
    {
        goto at_4bfa74;
    }
    r->esi = rd32(r, r->ebp - 0x20);
    r->ebx = rd32(r, r->ebx);
    r->esi = rd32(r, r->esi + 0x4);
at_4c0618:
    r->eax = 0;
    set_low8(&r->eax, rd8(r, r->ebx));
    r->esi = r->esi - 1;
    r->eax = r->eax << 0x8;
    r->ebx = r->ebx + 1;
    wr32(r, r->ebp - 0x48, r->eax);
    if (r->esi != 0)
    {
        goto at_4c0640;
    }
    r->ebx = rd32(r, r->ebp - 0x20);
    r->eax = r->ecx;
    call_all(r, rd32(r, r->ebx + 0xc));
    if (r->eax == 0 && !r->port->env.failed)
    {
        goto at_4bfa74;
    }
    r->esi = rd32(r, r->ebp - 0x20);
    r->ebx = rd32(r, r->ebx);
    r->esi = rd32(r, r->esi + 0x4);
at_4c0640:
    r->eax = 0;
    r->edi = rd32(r, r->ebp - 0x48);
    set_low8(&r->eax, rd8(r, r->ebx));
    r->esi = r->esi - 1;
    r->edi = r->edi + r->eax;
    r->ebx = r->ebx + 1;
    wr32(r, r->ebp - 0x48, r->edi);
at_4c064e:
    r->eax = rd32(r, r->edx * 4 + 0x5000d0);
    r->edi = rd32(r, r->ebp - 0x68);
    r->eax = r->eax + r->eax;
    r->eax = r->eax + r->edi;
    r->edi = rd32(r, r->ebp - 0x48);
    r->edx = r->edx + 1;
    wr16(r, r->eax, (r->edi & 0xffff));
    if ((int32_t)r->edx < (int32_t)0x40 && !r->port->env.failed)
    {
        goto at_4c05f2;
    }
    r->eax = rd32(r, r->ecx);
    if ((int32_t)rd32(r, r->eax + 0x68) < (int32_t)0x2)
    {
        goto at_4c06f3;
    }
    r->edi = 0;
    wr32(r, r->ebp - 0x44, r->edi);
at_4c0679:
    r->edx = rd32(r, r->ebp - 0x44);
    r->edi = rd32(r, r->ebp - 0x68);
    r->edx = r->edx + r->edx;
    r->edx = r->edx + r->edi;
    r->edi = 0;
    set_low16(&r->edi, rd16(r, r->edx));
    r->eax = rd32(r, r->ecx);
    wr32(r, r->eax + 0x18, r->edi);
    r->edi = 0;
    set_low16(&r->edi, rd16(r, r->edx + 0x2));
    wr32(r, r->eax + 0x1c, r->edi);
    r->edi = 0;
    set_low16(&r->edi, rd16(r, r->edx + 0x4));
    wr32(r, r->eax + 0x20, r->edi);
    r->edi = 0;
    set_low16(&r->edi, rd16(r, r->edx + 0x6));
    wr32(r, r->eax + 0x24, r->edi);
    r->edi = 0;
    set_low16(&r->edi, rd16(r, r->edx + 0x8));
    wr32(r, r->eax + 0x28, r->edi);
    r->edi = 0;
    set_low16(&r->edi, rd16(r, r->edx + 0xa));
    wr32(r, r->eax + 0x2c, r->edi);
    r->edi = 0;
    set_low16(&r->edi, rd16(r, r->edx + 0xc));
    wr32(r, r->eax + 0x30, r->edi);
    set_low16(&r->edx, rd16(r, r->edx + 0xe));
    r->edx = r->edx & 0xffff;
    wr32(r, r->eax + 0x34, r->edx);
    r->eax = rd32(r, r->ecx);
    wr32(r, r->eax + 0x14, 0x5d);
    r->edi = rd32(r, r->ecx);
    r->edx = 0x2;
    r->eax = r->ecx;
    call_all(r, rd32(r, r->edi + 0x4));
    r->eax = rd32(r, r->ebp - 0x44);
    r->eax = r->eax + 0x8;
    wr32(r, r->ebp - 0x44, r->eax);
    if ((int32_t)r->eax < (int32_t)0x40 && !r->port->env.failed)
    {
        goto at_4c0679;
    }
at_4c06f3:
    r->edi = rd32(r, r->ebp - 0x38);
    r->edi = r->edi - 0x41;
    r->eax = rd32(r, r->ebp - 0x5c);
    wr32(r, r->ebp - 0x38, r->edi);
    if (r->eax == 0 && !r->port->env.failed)
    {
        goto at_4c054d;
    }
    r->edx = r->edi - 0x40;
    wr32(r, r->ebp - 0x38, r->edx);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4c054d;
at_4c0712:
    if (cond(r, CC_BE) && !r->port->env.failed)
    {
        goto at_4bfae9;
    }
    if (r->eax >= 0xd0 && !r->port->env.failed)
    {
        goto at_4c035c;
    }
    if (r->eax >= 0xcd)
    {
        goto at_4c0793;
    }
    if (r->eax <= 0xcb)
    {
        goto at_4c0793;
    }
at_4c0731:
    r->eax = rd32(r, r->ebp - 0x18);
    call_keep(r, 0x4bf6a0);
    if (r->eax != 0 && !r->port->env.failed)
    {
        goto at_4bfa52;
    }
    r->edi = rd32(r, r->ebp - 0x14);
    r->esi = rd32(r, r->ebp - 0x10);
    r->edx = rd32(r, r->ebp - 0xc);
    r->ecx = rd32(r, r->ebp - 0x8);
    r->ebx = rd32(r, r->ebp - 0x4);
    return;
at_4c074b:
    if (cond(r, CC_BE) && !r->port->env.failed)
    {
        goto at_4bfe35;
    }
    flags(r, F_SUB, r->eax, 0xc7, 32);
    if (cond(r, CC_B))
    {
        goto at_4c0793;
    }
    if (cond(r, CC_BE))
    {
        goto at_4c0793;
    }
    if (r->eax <= 0xc8)
    {
        goto at_4c0793;
    }
    r->ebx = 0x1;
    r->eax = rd32(r, r->ebp - 0x18);
    r->edx = 0;
    call_keep(r, 0x4be0b0);
    if (r->eax != 0 && !r->port->env.failed)
    {
        goto at_4bfa52;
    }
    r->edi = rd32(r, r->ebp - 0x14);
    r->esi = rd32(r, r->ebp - 0x10);
    r->edx = rd32(r, r->ebp - 0xc);
    r->ecx = rd32(r, r->ebp - 0x8);
    r->ebx = rd32(r, r->ebp - 0x4);
    return;
at_4c0782:
    if (cond(r, CC_BE) && !r->port->env.failed)
    {
        goto at_4bfaae;
    }
    if (r->eax <= 0xc2 && !r->port->env.failed)
    {
        goto at_4bfac8;
    }
at_4c0793:
    r->eax = rd32(r, r->ebp - 0x18);
    r->eax = rd32(r, r->eax);
    wr32(r, r->eax + 0x14, 0x3c);
    r->eax = rd32(r, r->ebp - 0x18);
    r->edx = rd32(r, r->ebp - 0x18);
    r->eax = rd32(r, r->eax);
    r->edx = rd32(r, r->edx + 0x1a0);
    wr32(r, r->eax + 0x18, r->edx);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4bfa48;
at_4c07b5:
    if (cond(r, CC_BE) && !r->port->env.failed)
    {
        goto at_4c035c;
    }
    if (r->eax == 0xc0 && !r->port->env.failed)
    {
        goto at_4bfaae;
    }
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4bfa2b;
}

uint32_t vertrix_port_jpeg_read_markers_4bf940(PORT_SIGNATURE)
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
    port_set32(&port, r.ebp, -0xcu, entry->edx);
    port_set32(&port, r.ebp, -0x10u, entry->esi);
    port_set32(&port, r.ebp, -0x14u, entry->edi);
    run(&r);
    return port_return(&port, r.eax, r.edx);
}
