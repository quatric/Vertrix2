#include "port_rtljpegmcudecodes.h"

/* libjpeg decode_mcu for sequential Huffman scans: decodes the DC difference and AC coefficients of
 * each block in the MCU. */

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

/* Original 0x4bc1e0: libjpeg decode_mcu for sequential Huffman scans: decodes the DC difference and
 * AC coefficients of each block in the MCU. Evidence: calls 0x4bc050, 0x4bbf30.
 * Register-for-register from the listing (0x4bc1ea..0x4bc6b5); labels are the original addresses.
 */
static void run(Regs *r)
{
    wr32(r, r->ebp - 0x34, r->eax);
    wr32(r, r->ebp - 0x3c, r->edx);
    r->eax = rd32(r, r->eax + 0x1bc);
    wr32(r, r->ebp - 0x38, r->eax);
    r->eax = rd32(r, r->ebp - 0x34);
    if (rd32(r, r->eax + 0x114) == 0x0)
    {
        goto at_4bc296;
    }
    r->eax = rd32(r, r->ebp - 0x38);
    if (rd32(r, r->eax + 0x24) != 0x0)
    {
        goto at_4bc296;
    }
    r->ebx = r->eax;
    r->edx = r->ebx;
    r->edx = rd32(r, r->edx + 0x10);
    r->eax = rd32(r, r->eax + 0x10);
    r->edx = (uint32_t)((int32_t)r->edx >> 0x1f);
    r->edx = r->edx << 0x3;
    flags(r, F_LOGIC, r->edx, 0, 32);
    r->eax = r->eax - r->edx - carry(r);
    r->eax = (uint32_t)((int32_t)r->eax >> 0x3);
    r->ecx = rd32(r, r->ebp - 0x34);
    r->esi = rd32(r, r->ecx + 0x1b8);
    r->edi = rd32(r, r->esi + 0x18);
    r->edi = r->edi + r->eax;
    r->eax = r->ebx;
    wr32(r, r->esi + 0x18, r->edi);
    wr32(r, r->eax + 0x10, 0x0);
    r->edx = rd32(r, r->ecx + 0x1b8);
    r->eax = r->ecx;
    call_all(r, rd32(r, r->edx + 0x8));
    if (r->eax == 0)
    {
        goto at_4bc526;
    }
    r->esi = rd32(r, r->ecx + 0x148);
    r->edx = 0;
    if ((int32_t)r->esi <= 0)
    {
        goto at_4bc280;
    }
    r->eax = r->ebx;
at_4bc266:
    wr32(r, r->eax + 0x14, 0x0);
    r->edx = r->edx + 1;
    r->edi = rd32(r, r->ecx + 0x148);
    r->eax = r->eax + 0x4;
    if ((int32_t)r->edx < (int32_t)r->edi && !r->port->env.failed)
    {
        goto at_4bc266;
    }
at_4bc280:
    r->eax = rd32(r, r->ecx + 0x114);
    wr32(r, r->ebx + 0x24, r->eax);
    r->eax = rd32(r, r->ecx + 0x1a0);
    if (r->eax != 0)
    {
        goto at_4bc296;
    }
    wr32(r, r->ebx + 0x8, r->eax);
at_4bc296:
    r->eax = rd32(r, r->ebp - 0x38);
    if (rd32(r, r->eax + 0x8) != 0x0)
    {
        goto at_4bc510;
    }
    r->eax = rd32(r, r->ebp - 0x34);
    wr32(r, r->ebp - 0x54, r->eax);
    r->eax = rd32(r, r->eax + 0x18);
    r->eax = rd32(r, r->eax);
    wr32(r, r->ebp - 0x64, r->eax);
    r->eax = rd32(r, r->ebp - 0x34);
    r->edx = rd32(r, r->ebp - 0x38);
    r->eax = rd32(r, r->eax + 0x18);
    r->ebx = rd32(r, r->ebp - 0x38);
    r->edi = r->ebp - 0x50;
    r->eax = rd32(r, r->eax + 0x4);
    r->esi = rd32(r, r->ebp - 0x38);
    wr32(r, r->ebp - 0x60, r->eax);
    r->eax = rd32(r, r->ebp - 0x34);
    r->esi = r->esi + 0x14;
    r->edx = rd32(r, r->edx + 0xc);
    r->ebx = rd32(r, r->ebx + 0x10);
    movs(r, 4);
    movs(r, 4);
    movs(r, 4);
    movs(r, 4);
    r->ecx = 0;
    r->esi = rd32(r, r->eax + 0x164);
    wr32(r, r->ebp - 0x2c, r->ecx);
    if ((int32_t)r->esi <= 0)
    {
        goto at_4bc4e4;
    }
    r->eax = rd32(r, r->ebp - 0x3c);
    wr32(r, r->ebp - 0x30, r->eax);
    r->eax = rd32(r, r->ebp - 0x38);
    wr32(r, r->ebp - 0x28, r->eax);
at_4bc2f8:
    r->eax = rd32(r, r->ebp - 0x30);
    r->esi = rd32(r, r->ebp - 0x28);
    r->edi = rd32(r, r->ebp - 0x28);
    r->eax = rd32(r, r->eax);
    r->esi = rd32(r, r->esi + 0x48);
    r->edi = rd32(r, r->edi + 0x70);
    wr32(r, r->ebp - 0x24, r->eax);
    if ((int32_t)r->ebx < (int32_t)0x8)
    {
        goto at_4bc533;
    }
at_4bc315:
    r->ecx = r->ebx - 0x8;
    r->eax = r->edx;
    r->eax = (uint32_t)((int32_t)r->eax >> (r->ecx & 0xff));
    r->ecx = r->eax;
    r->ecx = r->ecx & 0xff;
    r->eax = r->ecx;
    r->eax = rd32(r, r->esi + r->eax * 4 + 0x90);
    if (r->eax != 0)
    {
        goto at_4bc55a;
    }
    r->eax = 0x9;
at_4bc33a:
    push(r, r->eax);
    r->ecx = r->esi;
    r->eax = r->ebp - 0x64;
    call(r, 0x4bc050, 1);
    wr32(r, r->ebp - 0x14, r->eax);
    if ((int32_t)r->eax < 0)
    {
        goto at_4bc526;
    }
    r->edx = rd32(r, r->ebp - 0x5c);
    r->ebx = rd32(r, r->ebp - 0x58);
at_4bc356:
    r->esi = rd32(r, r->ebp - 0x14);
    if (r->esi == 0)
    {
        goto at_4bc3a8;
    }
    if ((int32_t)r->ebx >= (int32_t)r->esi)
    {
        goto at_4bc379;
    }
    r->eax = r->ebp - 0x64;
    r->ecx = r->esi;
    call_keep(r, 0x4bbf30);
    if (r->eax == 0)
    {
        goto at_4bc526;
    }
    r->edx = rd32(r, r->ebp - 0x5c);
    r->ebx = rd32(r, r->ebp - 0x58);
at_4bc379:
    r->ebx = r->ebx - rd32(r, r->ebp - 0x14);
    r->eax = r->edx;
    set_low8(&r->ecx, (r->ebx & 0xff));
    r->esi = 0x1;
    r->eax = (uint32_t)((int32_t)r->eax >> (r->ecx & 0xff));
    set_low8(&r->ecx, rd8(r, r->ebp - 0x14));
    r->esi = r->esi << (r->ecx & 0xff);
    r->ecx = r->esi - 0x1;
    r->eax = r->eax & r->ecx;
    r->ecx = rd32(r, r->ebp - 0x14);
    r->ecx = r->ecx << 0x2;
    if ((int32_t)r->eax >= (int32_t)rd32(r, r->ecx + 0x4ffcbc))
    {
        goto at_4bc3a5;
    }
    r->eax = r->eax + rd32(r, r->ecx + 0x4ffcfc);
at_4bc3a5:
    wr32(r, r->ebp - 0x14, r->eax);
at_4bc3a8:
    r->ecx = rd32(r, r->ebp - 0x28);
    r->eax = rd32(r, r->ebp - 0x2c);
    r->esi = rd32(r, r->ecx + 0x98);
    r->eax = r->eax << 0x2;
    if (r->esi == 0)
    {
        goto at_4bc3db;
    }
    r->eax = r->eax + rd32(r, r->ebp - 0x34);
    r->eax = rd32(r, r->eax + 0x168);
    r->esi = rd32(r, r->ebp - 0x14);
    r->esi = r->esi + rd32(r, r->ebp + r->eax * 4 - 0x50);
    r->ecx = rd32(r, r->ebp - 0x24);
    wr32(r, r->ebp - 0x14, r->esi);
    wr32(r, r->ebp + r->eax * 4 - 0x50, r->esi);
    r->eax = rd32(r, r->ebp - 0x14);
    wr16(r, r->ecx, (r->eax & 0xffff));
at_4bc3db:
    r->eax = rd32(r, r->ebp - 0x28);
    if (rd32(r, r->eax + 0xc0) == 0x0)
    {
        goto at_4bc5cf;
    }
    r->esi = 0x1;
at_4bc3f0:
    if ((int32_t)r->ebx < (int32_t)0x8)
    {
        goto at_4bc56e;
    }
at_4bc3f9:
    r->ecx = r->ebx - 0x8;
    r->eax = r->edx;
    r->eax = (uint32_t)((int32_t)r->eax >> (r->ecx & 0xff));
    r->ecx = r->eax;
    r->ecx = r->ecx & 0xff;
    r->eax = r->ecx;
    r->eax = rd32(r, r->edi + r->eax * 4 + 0x90);
    if (r->eax == 0)
    {
        goto at_4bc5b6;
    }
    r->ebx = r->ebx - r->eax;
    r->eax = r->ecx;
    set_low8(&r->eax, rd8(r, r->edi + r->eax + 0x490));
    r->eax = r->eax & 0xff;
    wr32(r, r->ebp - 0x14, r->eax);
at_4bc42c:
    r->eax = rd32(r, r->ebp - 0x14);
    r->ecx = rd32(r, r->ebp - 0x14);
    r->eax = (uint32_t)((int32_t)r->eax >> 0x4);
    r->ecx = r->ecx & 0xf;
    flags(r, F_LOGIC, r->ecx, 0, 32);
    wr32(r, r->ebp - 0x14, r->ecx);
    if (cond(r, CC_E))
    {
        goto at_4bc5bf;
    }
    r->esi = r->esi + r->eax;
    if ((int32_t)r->ebx >= (int32_t)r->ecx)
    {
        goto at_4bc45d;
    }
    r->eax = r->ebp - 0x64;
    call_keep(r, 0x4bbf30);
    if (r->eax == 0)
    {
        goto at_4bc526;
    }
    r->edx = rd32(r, r->ebp - 0x5c);
    r->ebx = rd32(r, r->ebp - 0x58);
at_4bc45d:
    r->ebx = r->ebx - rd32(r, r->ebp - 0x14);
    r->eax = r->edx;
    set_low8(&r->ecx, (r->ebx & 0xff));
    r->eax = (uint32_t)((int32_t)r->eax >> (r->ecx & 0xff));
    set_low8(&r->ecx, rd8(r, r->ebp - 0x14));
    wr32(r, r->ebp - 0x40, r->eax);
    r->eax = 0x1;
    r->eax = r->eax << (r->ecx & 0xff);
    r->ecx = r->eax - 0x1;
    r->eax = rd32(r, r->ebp - 0x40);
    r->eax = r->eax & r->ecx;
    wr32(r, r->ebp - 0x18, r->eax);
    r->eax = rd32(r, r->ebp - 0x14);
    r->eax = r->eax << 0x2;
    r->ecx = rd32(r, r->ebp - 0x18);
    if ((int32_t)r->ecx >= (int32_t)rd32(r, r->eax + 0x4ffcbc))
    {
        goto at_4bc495;
    }
    r->ecx = r->ecx + rd32(r, r->eax + 0x4ffcfc);
at_4bc495:
    r->eax = r->ecx;
    wr32(r, r->ebp - 0x14, r->eax);
    r->eax = rd32(r, r->esi * 4 + 0x5000d0);
    r->ecx = rd32(r, r->ebp - 0x24);
    r->eax = r->eax + r->eax;
    r->eax = r->eax + r->ecx;
    r->ecx = rd32(r, r->ebp - 0x14);
    wr16(r, r->eax, (r->ecx & 0xffff));
at_4bc4ae:
    r->esi = r->esi + 1;
    if ((int32_t)r->esi < (int32_t)0x40 && !r->port->env.failed)
    {
        goto at_4bc3f0;
    }
at_4bc4b8:
    r->edi = rd32(r, r->ebp - 0x30);
    r->eax = rd32(r, r->ebp - 0x28);
    r->ecx = rd32(r, r->ebp - 0x2c);
    r->eax = r->eax + 0x4;
    r->ecx = r->ecx + 1;
    wr32(r, r->ebp - 0x28, r->eax);
    wr32(r, r->ebp - 0x2c, r->ecx);
    r->eax = r->ecx;
    r->ecx = rd32(r, r->ebp - 0x34);
    r->edi = r->edi + 0x4;
    r->esi = rd32(r, r->ecx + 0x164);
    wr32(r, r->ebp - 0x30, r->edi);
    if ((int32_t)r->eax < (int32_t)r->esi && !r->port->env.failed)
    {
        goto at_4bc2f8;
    }
at_4bc4e4:
    r->ecx = rd32(r, r->ebp - 0x34);
    r->ecx = rd32(r, r->ecx + 0x18);
    r->eax = rd32(r, r->ebp - 0x64);
    wr32(r, r->ecx, r->eax);
    r->ecx = rd32(r, r->ebp - 0x34);
    r->ecx = rd32(r, r->ecx + 0x18);
    r->eax = rd32(r, r->ebp - 0x60);
    wr32(r, r->ecx + 0x4, r->eax);
    r->eax = rd32(r, r->ebp - 0x38);
    wr32(r, r->eax + 0xc, r->edx);
    r->edi = r->eax;
    wr32(r, r->eax + 0x10, r->ebx);
    r->esi = r->ebp - 0x50;
    r->edi = r->edi + 0x14;
    movs(r, 4);
    movs(r, 4);
    movs(r, 4);
    movs(r, 4);
at_4bc510:
    r->eax = rd32(r, r->ebp - 0x38);
    r->ebx = 0x1;
    wr32(r, r->eax + 0x24, rd32(r, r->eax + 0x24) - r->ebx);
    r->eax = r->ebx;
    r->edi = rd32(r, r->ebp - 0x10);
    r->esi = rd32(r, r->ebp - 0xc);
    r->ecx = rd32(r, r->ebp - 0x8);
    r->ebx = rd32(r, r->ebp - 0x4);
    return;
at_4bc526:
    r->ebx = 0;
    r->eax = r->ebx;
    r->edi = rd32(r, r->ebp - 0x10);
    r->esi = rd32(r, r->ebp - 0xc);
    r->ecx = rd32(r, r->ebp - 0x8);
    r->ebx = rd32(r, r->ebp - 0x4);
    return;
at_4bc533:
    r->eax = r->ebp - 0x64;
    r->ecx = 0;
    call_keep(r, 0x4bbf30);
    if (r->eax == 0 && !r->port->env.failed)
    {
        goto at_4bc526;
    }
    r->ebx = rd32(r, r->ebp - 0x58);
    r->edx = rd32(r, r->ebp - 0x5c);
    if ((int32_t)r->ebx >= (int32_t)0x8 && !r->port->env.failed)
    {
        goto at_4bc315;
    }
    r->eax = 0x1;
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4bc33a;
at_4bc55a:
    r->esi = r->esi + r->ecx;
    r->ebx = r->ebx - r->eax;
    r->eax = 0;
    set_low8(&r->eax, rd8(r, r->esi + 0x490));
    wr32(r, r->ebp - 0x14, r->eax);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4bc356;
at_4bc56e:
    r->eax = r->ebp - 0x64;
    r->ecx = 0;
    call_keep(r, 0x4bbf30);
    if (r->eax == 0 && !r->port->env.failed)
    {
        goto at_4bc526;
    }
    r->ebx = rd32(r, r->ebp - 0x58);
    r->edx = rd32(r, r->ebp - 0x5c);
    if ((int32_t)r->ebx >= (int32_t)0x8 && !r->port->env.failed)
    {
        goto at_4bc3f9;
    }
    wr32(r, r->ebp - 0x20, 0x1);
at_4bc592:
    r->ecx = rd32(r, r->ebp - 0x20);
    push(r, r->ecx);
    r->eax = r->ebp - 0x64;
    r->ecx = r->edi;
    call(r, 0x4bc050, 1);
    wr32(r, r->ebp - 0x14, r->eax);
    if ((int32_t)r->eax < 0 && !r->port->env.failed)
    {
        goto at_4bc526;
    }
    r->edx = rd32(r, r->ebp - 0x5c);
    r->ebx = rd32(r, r->ebp - 0x58);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4bc42c;
at_4bc5b6:
    wr32(r, r->ebp - 0x20, 0x9);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4bc592;
at_4bc5bf:
    if (r->eax != 0xf && !r->port->env.failed)
    {
        goto at_4bc4b8;
    }
    r->esi = r->esi + r->eax;
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4bc4ae;
at_4bc5cf:
    r->esi = 0x1;
at_4bc5d4:
    if ((int32_t)r->ebx < (int32_t)0x8)
    {
        goto at_4bc64b;
    }
at_4bc5d9:
    r->ecx = r->ebx - 0x8;
    r->eax = r->edx;
    r->eax = (uint32_t)((int32_t)r->eax >> (r->ecx & 0xff));
    r->ecx = r->eax;
    r->ecx = r->ecx & 0xff;
    r->eax = r->ecx;
    r->eax = rd32(r, r->edi + r->eax * 4 + 0x90);
    if (r->eax == 0)
    {
        goto at_4bc697;
    }
    r->ebx = r->ebx - r->eax;
    r->eax = r->ecx;
    set_low8(&r->eax, rd8(r, r->edi + r->eax + 0x490));
    r->eax = r->eax & 0xff;
    wr32(r, r->ebp - 0x14, r->eax);
at_4bc60c:
    r->eax = rd32(r, r->ebp - 0x14);
    r->ecx = rd32(r, r->ebp - 0x14);
    r->eax = (uint32_t)((int32_t)r->eax >> 0x4);
    r->ecx = r->ecx & 0xf;
    flags(r, F_LOGIC, r->ecx, 0, 32);
    wr32(r, r->ebp - 0x14, r->ecx);
    if (cond(r, CC_E))
    {
        goto at_4bc6a0;
    }
    r->esi = r->esi + r->eax;
    if ((int32_t)r->ebx >= (int32_t)r->ecx)
    {
        goto at_4bc63d;
    }
    r->eax = r->ebp - 0x64;
    call_keep(r, 0x4bbf30);
    if (r->eax == 0 && !r->port->env.failed)
    {
        goto at_4bc526;
    }
    r->edx = rd32(r, r->ebp - 0x5c);
    r->ebx = rd32(r, r->ebp - 0x58);
at_4bc63d:
    r->ebx = r->ebx - rd32(r, r->ebp - 0x14);
    r->esi = r->esi + 1;
    if ((int32_t)r->esi < (int32_t)0x40 && !r->port->env.failed)
    {
        goto at_4bc5d4;
    }
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4bc4b8;
at_4bc64b:
    r->eax = r->ebp - 0x64;
    r->ecx = 0;
    call_keep(r, 0x4bbf30);
    if (r->eax == 0 && !r->port->env.failed)
    {
        goto at_4bc526;
    }
    r->ebx = rd32(r, r->ebp - 0x58);
    r->edx = rd32(r, r->ebp - 0x5c);
    if ((int32_t)r->ebx >= (int32_t)0x8 && !r->port->env.failed)
    {
        goto at_4bc5d9;
    }
    wr32(r, r->ebp - 0x1c, 0x1);
at_4bc673:
    r->ecx = rd32(r, r->ebp - 0x1c);
    push(r, r->ecx);
    r->eax = r->ebp - 0x64;
    r->ecx = r->edi;
    call(r, 0x4bc050, 1);
    wr32(r, r->ebp - 0x14, r->eax);
    if ((int32_t)r->eax < 0 && !r->port->env.failed)
    {
        goto at_4bc526;
    }
    r->edx = rd32(r, r->ebp - 0x5c);
    r->ebx = rd32(r, r->ebp - 0x58);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4bc60c;
at_4bc697:
    wr32(r, r->ebp - 0x1c, 0x9);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4bc673;
at_4bc6a0:
    if (r->eax != 0xf && !r->port->env.failed)
    {
        goto at_4bc4b8;
    }
    r->esi = r->esi + r->eax;
    r->esi = r->esi + 1;
    if ((int32_t)r->esi < (int32_t)0x40 && !r->port->env.failed)
    {
        goto at_4bc5d4;
    }
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4bc4b8;
}

uint32_t vertrix_port_jpeg_decode_mcu_4bc1e0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x68
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
