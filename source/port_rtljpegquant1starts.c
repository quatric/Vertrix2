#include "port_rtljpegquant1starts.h"

/* libjpeg one-pass quantizer start_pass: picks the colour quantize routine by dither mode (none,
 * ordered or Floyd-Steinberg) and component count; an unknown mode is error 0x30. */

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

static uint32_t rd32(Regs *r, uint32_t address)
{
    return port_u32(r->port, address, 0);
}

static void wr32(Regs *r, uint32_t address, uint32_t value)
{
    port_set32(r->port, address, 0, value);
}

static void set_low8(uint32_t *reg, uint32_t value)
{
    *reg = (*reg & 0xffffff00u) | (value & 0xff);
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

/* Original 0x4c6a20: libjpeg one-pass quantizer start_pass: picks the colour quantize routine by
 * dither mode (none, ordered or Floyd-Steinberg) and component count; an unknown mode is error
 * 0x30. Evidence: no calls. Register-for-register from the listing (0x4c6a2a..0x4c6a77); labels are
 * the original addresses. */
static void run(Regs *r)
{
    r->edi = r->eax;
    r->ebx = rd32(r, r->eax + 0x1cc);
    r->eax = rd32(r, r->ebx + 0x10);
    wr32(r, r->edi + 0x88, r->eax);
    r->eax = rd32(r, r->ebx + 0x14);
    wr32(r, r->edi + 0x84, r->eax);
    r->eax = rd32(r, r->edi + 0x58);
    flags(r, F_SUB, r->eax, 0x1, 32);
    if (cond(r, CC_AE))
    {
        goto at_4c6c3e;
    }
    if (r->eax != 0)
    {
        goto at_4c6c49;
    }
    if (rd32(r, r->edi + 0x78) != 0x3)
    {
        goto at_4c6a81;
    }
    wr32(r, r->ebx + 0x4, 0x4c6460);
at_4c6a70:
    r->edi = rd32(r, r->ebp - 0x10);
    r->esi = rd32(r, r->ebp - 0xc);
    r->ecx = rd32(r, r->ebp - 0x8);
    r->ebx = rd32(r, r->ebp - 0x4);
    return;
at_4c6c3e:
    if (cond(r, CC_BE))
    {
        goto at_4c6a91;
    }
    if (r->eax == 0x2)
    {
        goto at_4c6bed;
    }
at_4c6c49:
    r->eax = rd32(r, r->edi);
    wr32(r, r->eax + 0x14, 0x30);
    r->edx = rd32(r, r->edi);
    r->eax = r->edi;
    call_all(r, rd32(r, r->edx));
    r->edi = rd32(r, r->ebp - 0x10);
    r->esi = rd32(r, r->ebp - 0xc);
    r->ecx = rd32(r, r->ebp - 0x8);
    r->ebx = rd32(r, r->ebp - 0x4);
    return;
at_4c6a81:
    wr32(r, r->ebx + 0x4, 0x4c63a0);
    r->edi = rd32(r, r->ebp - 0x10);
    r->esi = rd32(r, r->ebp - 0xc);
    r->ecx = rd32(r, r->ebp - 0x8);
    r->ebx = rd32(r, r->ebp - 0x4);
    return;
at_4c6a91:
    if (rd32(r, r->edi + 0x78) == 0x3)
    {
        goto at_4c6bb4;
    }
    wr32(r, r->ebx + 0x4, 0x4c6510);
at_4c6aa2:
    r->ecx = rd32(r, r->ebx + 0x1c);
    wr32(r, r->ebx + 0x30, 0x0);
    if (r->ecx == 0)
    {
        goto at_4c6bc0;
    }
at_4c6ab4:
    r->esi = rd32(r, r->ebx + 0x34);
    if (r->esi != 0 && !r->port->env.failed)
    {
        goto at_4c6a70;
    }
    wr32(r, r->ebp - 0x2c, r->edi);
    wr32(r, r->ebp - 0x20, r->esi);
    r->eax = rd32(r, r->edi + 0x1cc);
    r->edx = rd32(r, r->edi + 0x78);
    wr32(r, r->ebp - 0x30, r->eax);
    if ((int32_t)r->edx <= 0 && !r->port->env.failed)
    {
        goto at_4c6a70;
    }
    wr32(r, r->ebp - 0x28, r->eax);
at_4c6ad4:
    r->ecx = rd32(r, r->ebp - 0x28);
    r->esi = rd32(r, r->ebp - 0x20);
    r->ebx = 0;
    r->edx = 0;
    r->ecx = rd32(r, r->ecx + 0x20);
    if ((int32_t)r->esi <= 0)
    {
        goto at_4c6af7;
    }
    r->eax = rd32(r, r->ebp - 0x30);
    r->edi = rd32(r, r->ebp - 0x20);
at_4c6aeb:
    if (r->ecx != rd32(r, r->eax + 0x20))
    {
        goto at_4c6bcc;
    }
    r->ebx = rd32(r, r->eax + 0x34);
at_4c6af7:
    if (r->ebx != 0)
    {
        goto at_4c6b8e;
    }
    r->esi = rd32(r, r->ebp - 0x2c);
    r->ebx = 0x400;
    r->edx = 0x1;
    r->eax = rd32(r, r->ebp - 0x2c);
    r->edi = 0;
    r->esi = rd32(r, r->esi + 0x4);
    wr32(r, r->ebp - 0x14, r->edi);
    wr32(r, r->ebp - 0x18, r->edi);
    call_all(r, rd32(r, r->esi));
    wr32(r, r->ebp - 0x24, r->eax);
    r->esi = r->ecx - 0x1;
    r->eax = r->eax + 0x40;
    r->esi = r->esi << 0x9;
    wr32(r, r->ebp - 0x1c, r->eax);
at_4c6b2b:
    r->eax = rd32(r, r->ebp - 0x14);
    r->ecx = rd32(r, r->ebp - 0x24);
    r->ebx = rd32(r, r->ebp - 0x18);
    r->eax = r->eax << 0x6;
    r->edi = rd32(r, r->ebp - 0x1c);
    r->ecx = r->ecx + r->eax;
at_4c6b3c:
    r->eax = 0;
    set_low8(&r->eax, rd8(r, r->ebx + 0x4fffd0));
    r->edx = 0xff;
    r->eax = r->eax + r->eax;
    r->edx = r->edx - r->eax;
    r->edx = r->edx * 0xff;
    if ((int32_t)r->edx < 0)
    {
        goto at_4c6bdd;
    }
    r->eax = r->edx;
    r->edx = (uint32_t)((int32_t)r->edx >> 0x1f);
    idiv32(r, r->esi);
at_4c6b62:
    r->ecx = r->ecx + 0x4;
    r->ebx = r->ebx + 1;
    wr32(r, r->ecx - 0x4, r->eax);
    if (r->ecx != r->edi && !r->port->env.failed)
    {
        goto at_4c6b3c;
    }
    r->edx = rd32(r, r->ebp - 0x1c);
    r->ecx = rd32(r, r->ebp - 0x18);
    r->ebx = rd32(r, r->ebp - 0x14);
    r->edx = r->edx + 0x40;
    r->ecx = r->ecx + 0x10;
    r->ebx = r->ebx + 1;
    wr32(r, r->ebp - 0x1c, r->edx);
    wr32(r, r->ebp - 0x18, r->ecx);
    wr32(r, r->ebp - 0x14, r->ebx);
    if ((int32_t)r->ebx < (int32_t)0x10 && !r->port->env.failed)
    {
        goto at_4c6b2b;
    }
    r->ebx = rd32(r, r->ebp - 0x24);
at_4c6b8e:
    r->eax = rd32(r, r->ebp - 0x28);
    r->edx = r->eax + 0x4;
    r->ecx = rd32(r, r->ebp - 0x20);
    wr32(r, r->ebp - 0x28, r->edx);
    r->edx = rd32(r, r->ebp - 0x2c);
    wr32(r, r->eax + 0x34, r->ebx);
    r->ecx = r->ecx + 1;
    r->ebx = rd32(r, r->edx + 0x78);
    wr32(r, r->ebp - 0x20, r->ecx);
    if ((int32_t)r->ecx >= (int32_t)r->ebx && !r->port->env.failed)
    {
        goto at_4c6a70;
    }
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4c6ad4;
at_4c6bed:
    wr32(r, r->ebx + 0x4, 0x4c67a0);
    r->edx = rd32(r, r->ebx + 0x44);
    wr32(r, r->ebx + 0x54, 0x0);
    if (r->edx == 0)
    {
        goto at_4c6c35;
    }
at_4c6c02:
    r->esi = rd32(r, r->edi + 0x70);
    r->eax = rd32(r, r->edi + 0x78);
    r->esi = r->esi + 0x2;
    r->ecx = 0;
    r->esi = r->esi + r->esi;
    if ((int32_t)r->eax <= 0 && !r->port->env.failed)
    {
        goto at_4c6a70;
    }
at_4c6c17:
    r->edx = r->esi;
    r->eax = rd32(r, r->ebx + 0x44);
    call_keep(r, 0x4c98f0);
    r->ecx = r->ecx + 1;
    r->eax = rd32(r, r->edi + 0x78);
    r->ebx = r->ebx + 0x4;
    if ((int32_t)r->ecx < (int32_t)r->eax && !r->port->env.failed)
    {
        goto at_4c6c17;
    }
    r->edi = rd32(r, r->ebp - 0x10);
    r->esi = rd32(r, r->ebp - 0xc);
    r->ecx = rd32(r, r->ebp - 0x8);
    r->ebx = rd32(r, r->ebp - 0x4);
    return;
at_4c6bb4:
    wr32(r, r->ebx + 0x4, 0x4c6640);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4c6aa2;
at_4c6bc0:
    r->eax = r->edi;
    call_keep(r, 0x4c6020);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4c6ab4;
at_4c6bcc:
    r->edx = r->edx + 1;
    r->eax = r->eax + 0x4;
    if ((int32_t)r->edx < (int32_t)r->edi && !r->port->env.failed)
    {
        goto at_4c6aeb;
    }
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4c6af7;
at_4c6bdd:
    r->edx = 0u - r->edx;
    r->eax = r->edx;
    r->edx = (uint32_t)((int32_t)r->edx >> 0x1f);
    idiv32(r, r->esi);
    r->eax = 0u - r->eax;
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4c6b62;
at_4c6c35:
    r->eax = r->edi;
    call_keep(r, 0x4c69c0);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4c6c02;
}

uint32_t vertrix_port_jpeg_quant1_start_pass_4c6a20(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x34
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
