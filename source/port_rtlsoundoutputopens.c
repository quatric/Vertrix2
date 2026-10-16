#include "port_rtlsoundoutputopens.h"

/* 0x40b110 clears the 0x1c-byte state at 0x52f150 and creates the sound COM object through
 * vertrix_port_com_create (0x40b040), returning 5 on failure. */

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

static void set_low16(uint32_t *reg, uint32_t value)
{
    *reg = (*reg & 0xffff0000u) | (value & 0xffff);
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

/* Original 0x40b110: 0x40b110 clears the 0x1c-byte state at 0x52f150 and creates the sound COM
 * object through vertrix_port_com_create (0x40b040), returning 5 on failure. It calls vtable +0x18
 * (cooperative level 2, with the result of the import at 0x4f1994) and +0x10 (GetCaps), which
 * clears the option bits at [esi+5] and [esi+4] when the hardware lacks them. It creates the
 * primary buffer at 0x52f154 (flags 1) and sets a format built from those bits and the rate in
 * [esi+6] through +0x38, halving the rate while it is above 11025. It then sizes and creates a
 * secondary buffer at 0x52f158 (flags 0x14000) and starts both buffers looping with +0x30. It
 * records the size and settings at 0x52f160-0x52f16a and returns 0, or releases everything through
 * 0x40b080 and returns 5 on any error. Evidence: calls 0x4eb5c0, 0x40b040, 0x40b080; reads
 * 0x52f150, 0x4f1994, 0x52f154, 0x52f158; writes 0x52f160, 0x52f164, 0x52f168, 0x52f16a.
 * Register-for-register from the listing (0x40b11e..0x40b482); labels are the original addresses.
 */
static void run(Regs *r)
{
    r->esi = r->eax;
    r->ebx = 0x1c;
    r->edx = 0;
    r->eax = 0x52f150;
    call(r, 0x4eb5c0, 0);
    r->ebx = 0;
    r->edx = 0x52f150;
    r->eax = 0;
    call(r, 0x40b040, 0);
    if (r->eax == 0)
    {
        goto at_40b152;
    }
    r->eax = 0x5;
    r->edi = rd32(r, r->ebp - 0x14);
    r->esi = rd32(r, r->ebp - 0x10);
    r->edx = rd32(r, r->ebp - 0xc);
    r->ecx = rd32(r, r->ebp - 0x8);
    r->ebx = rd32(r, r->ebp - 0x4);
    return;
at_40b152:
    r->eax = rd32(r, 0x52f150);
    r->ebx = rd32(r, r->eax);
    push(r, 0x2);
    call_all(r, rd32(r, 0x4f1994));
    push(r, r->eax);
    r->edx = rd32(r, 0x52f150);
    push(r, r->edx);
    call_all(r, rd32(r, r->ebx + 0x18));
    if (r->eax != 0)
    {
        goto at_40b28f;
    }
    wr32(r, r->ebp - 0xb0, 0x60);
    r->eax = rd32(r, 0x52f150);
    r->ecx = rd32(r, r->eax);
    r->edx = r->ebp - 0xb0;
    push(r, r->edx);
    push(r, r->eax);
    call_all(r, rd32(r, r->ecx + 0x10));
    if (r->eax != 0)
    {
        goto at_40b28f;
    }
    if ((uint8_t)(rd8(r, r->ebp - 0xac) & 0x2) != 0)
    {
        goto at_40b1a6;
    }
    wr8(r, r->esi + 0x5, rd8(r, r->esi + 0x5) & 0xfe);
at_40b1a6:
    if ((uint8_t)(rd8(r, r->ebp - 0xab) & 0x8) != 0)
    {
        goto at_40b1b3;
    }
    wr8(r, r->esi + 0x4, rd8(r, r->esi + 0x4) & 0xfe);
at_40b1b3:
    wr16(r, r->ebp - 0x28, 0x1);
    flags(r, F_LOGIC, rd8(r, r->esi + 0x5) & 0x1, 0, 8);
    set_low8(&r->eax, cond(r, CC_NE));
    r->eax = r->eax & 0xff;
    r->eax = r->eax + 1;
    wr16(r, r->ebp - 0x26, (r->eax & 0xffff));
    if ((uint8_t)(rd8(r, r->esi + 0x4) & 0x1) == 0)
    {
        goto at_40b2a8;
    }
    r->eax = 0x10;
at_40b1d9:
    wr16(r, r->ebp - 0x1a, (r->eax & 0xffff));
    r->eax = 0;
    set_low16(&r->eax, rd16(r, r->esi + 0x6));
    wr32(r, r->ebp - 0x24, r->eax);
    r->eax = 0;
    set_low16(&r->eax, rd16(r, r->esi + 0x6));
    wr32(r, r->ebp - 0x20, r->eax);
    wr16(r, r->ebp - 0x1c, 0x1);
    r->ecx = 0;
    wr16(r, r->ebp - 0x18, (r->ecx & 0xffff));
    if ((uint8_t)(rd8(r, r->esi + 0x5) & 0x1) == 0)
    {
        goto at_40b20d;
    }
    r->ebx = r->eax + r->eax;
    wr32(r, r->ebp - 0x20, r->ebx);
    wr16(r, r->ebp - 0x1c, 0x2);
at_40b20d:
    if ((uint8_t)(rd8(r, r->esi + 0x4) & 0x1) == 0)
    {
        goto at_40b224;
    }
    r->edi = rd32(r, r->ebp - 0x20);
    r->edi = r->edi + r->edi;
    wr32(r, r->ebp - 0x20, r->edi);
    r->eax = rd32(r, r->ebp - 0x1c);
    r->eax = r->eax + r->eax;
    wr16(r, r->ebp - 0x1c, (r->eax & 0xffff));
at_40b224:
    r->ebx = 0x14;
    r->edx = 0;
    r->eax = r->ebp - 0x50;
    call(r, 0x4eb5c0, 0);
    wr32(r, r->ebp - 0x50, 0x14);
    wr32(r, r->ebp - 0x4c, 0x1);
    r->ecx = 0;
    wr32(r, r->ebp - 0x48, r->ecx);
    r->ebx = 0;
    wr32(r, r->ebp - 0x40, r->ecx);
    r->eax = rd32(r, 0x52f150);
    r->ecx = rd32(r, r->eax);
    push(r, r->ebx);
    push(r, 0x52f154);
    r->edx = r->ebp - 0x50;
    push(r, r->edx);
    push(r, r->eax);
    call_all(r, rd32(r, r->ecx + 0xc));
    if (r->eax != 0)
    {
        goto at_40b28f;
    }
at_40b264:
    r->eax = rd32(r, 0x52f154);
    r->ecx = rd32(r, r->eax);
    r->edx = r->ebp - 0x28;
    push(r, r->edx);
    push(r, r->eax);
    call_all(r, rd32(r, r->ecx + 0x38));
    if (r->eax == 0)
    {
        goto at_40b2d6;
    }
    if ((uint16_t)rd16(r, r->esi + 0x6) <= (uint16_t)0x2b11)
    {
        goto at_40b2b2;
    }
    wr32(r, r->ebp - 0x24, rd32(r, r->ebp - 0x24) >> 0x1);
    wr32(r, r->ebp - 0x20, rd32(r, r->ebp - 0x20) >> 0x1);
    wr16(r, r->ebp - 0x1c, rd16(r, r->ebp - 0x1c) >> 0x1);
    wr16(r, r->esi + 0x6, rd16(r, r->esi + 0x6) >> 0x1);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_40b264;
at_40b28f:
    r->eax = rd32(r, 0x52f150);
    call(r, 0x40b080, 0);
    r->eax = 0x5;
    r->edi = rd32(r, r->ebp - 0x14);
    r->esi = rd32(r, r->ebp - 0x10);
    r->edx = rd32(r, r->ebp - 0xc);
    r->ecx = rd32(r, r->ebp - 0x8);
    r->ebx = rd32(r, r->ebp - 0x4);
    return;
at_40b2a8:
    r->eax = 0x8;
    if (r->port->env.failed)
    {
        return;
    }
    goto at_40b1d9;
at_40b2b2:
    r->eax = rd32(r, 0x52f154);
    r->edx = rd32(r, r->eax);
    push(r, r->eax);
    call_all(r, rd32(r, r->edx + 0x8));
    r->eax = rd32(r, 0x52f150);
    call(r, 0x40b080, 0);
    r->eax = 0x5;
    r->edi = rd32(r, r->ebp - 0x14);
    r->esi = rd32(r, r->ebp - 0x10);
    r->edx = rd32(r, r->ebp - 0xc);
    r->ecx = rd32(r, r->ebp - 0x8);
    r->ebx = rd32(r, r->ebp - 0x4);
    return;
at_40b2d6:
    wr32(r, r->ebp - 0x3c, 0x14);
    r->eax = rd32(r, 0x52f154);
    r->edx = rd32(r, r->eax);
    r->ecx = r->ebp - 0x3c;
    push(r, r->ecx);
    push(r, r->eax);
    call_all(r, rd32(r, r->edx + 0xc));
    if (r->eax != 0 && !r->port->env.failed)
    {
        goto at_40b2b2;
    }
    r->edx = rd32(r, r->ebp - 0x20);
    r->eax = r->edx * 4;
    r->eax = r->eax - r->edx;
    r->eax = r->eax << 0x3;
    r->eax = r->eax + r->edx;
    r->eax = r->eax << 0x2;
    r->ecx = 0x3e8;
    r->edx = 0;
    div32(r, r->ecx);
    if (r->eax >= rd32(r, r->ebp - 0x34))
    {
        goto at_40b315;
    }
    wr32(r, r->ebp - 0x34, r->eax);
at_40b315:
    r->edx = rd32(r, r->ebp - 0x20);
    r->eax = r->edx * 4;
    r->eax = r->eax + r->edx;
    r->eax = r->eax << 0x2;
    r->ecx = 0x3e8;
    r->edx = 0;
    div32(r, r->ecx);
    if (r->eax <= rd32(r, r->ebp - 0x34))
    {
        goto at_40b335;
    }
    wr32(r, r->ebp - 0x34, r->eax);
at_40b335:
    if ((uint8_t)(rd8(r, r->ebp - 0xac) & 0x20) == 0)
    {
        goto at_40b364;
    }
    r->edx = rd32(r, r->ebp - 0x20);
    r->eax = r->edx * 4;
    r->eax = r->eax + r->edx;
    r->eax = r->eax + r->eax;
    r->edx = r->eax;
    r->eax = r->eax << 0x4;
    r->eax = r->eax - r->edx;
    r->ecx = 0x3e8;
    r->edx = 0;
    div32(r, r->ecx);
    if (r->eax <= rd32(r, r->ebp - 0x34))
    {
        goto at_40b364;
    }
    wr32(r, r->ebp - 0x34, r->eax);
at_40b364:
    r->edi = rd32(r, r->ebp - 0x34);
    r->edi = r->edi >> 0x2;
    wr32(r, r->ebp - 0x34, r->edi);
    r->eax = r->edi * 4;
    wr32(r, r->ebp - 0x34, r->eax);
    r->ebx = 0x14;
    r->edx = 0;
    r->eax = r->ebp - 0x50;
    call(r, 0x4eb5c0, 0);
    wr32(r, r->ebp - 0x50, 0x14);
    wr32(r, r->ebp - 0x4c, 0x14000);
    r->eax = rd32(r, r->ebp - 0x34);
    wr32(r, r->ebp - 0x48, r->eax);
    r->eax = r->ebp - 0x28;
    wr32(r, r->ebp - 0x40, r->eax);
    r->eax = rd32(r, 0x52f150);
    r->ecx = rd32(r, r->eax);
    push(r, 0x0);
    push(r, 0x52f158);
    r->edx = r->ebp - 0x50;
    push(r, r->edx);
    push(r, r->eax);
    call_all(r, rd32(r, r->ecx + 0xc));
    if (r->eax == 0)
    {
        goto at_40b3d3;
    }
    r->eax = rd32(r, 0x52f150);
    call(r, 0x40b080, 0);
    r->eax = 0x5;
    r->edi = rd32(r, r->ebp - 0x14);
    r->esi = rd32(r, r->ebp - 0x10);
    r->edx = rd32(r, r->ebp - 0xc);
    r->ecx = rd32(r, r->ebp - 0x8);
    r->ebx = rd32(r, r->ebp - 0x4);
    return;
at_40b3d3:
    r->ebx = 0;
    wr32(r, 0x52f160, r->eax);
    r->eax = rd32(r, r->ebp - 0x48);
    wr32(r, 0x52f164, r->eax);
    r->eax = rd32(r, 0x52f154);
    r->edx = rd32(r, r->eax);
    push(r, 0x1);
    push(r, r->ebx);
    push(r, r->ebx);
    push(r, r->eax);
    call_all(r, rd32(r, r->edx + 0x30));
    r->eax = rd32(r, 0x52f158);
    r->edx = rd32(r, r->eax);
    push(r, 0x1);
    push(r, r->ebx);
    push(r, r->ebx);
    push(r, r->eax);
    call_all(r, rd32(r, r->edx + 0x30));
    set_low16(&r->eax, rd16(r, r->esi + 0x6));
    wr16(r, 0x52f168, (r->eax & 0xffff));
    set_low16(&r->eax, rd16(r, r->esi + 0x4));
    wr16(r, 0x52f16a, (r->eax & 0xffff));
    r->eax = 0;
    r->edi = rd32(r, r->ebp - 0x14);
    r->esi = rd32(r, r->ebp - 0x10);
    r->edx = rd32(r, r->ebp - 0xc);
    r->ecx = rd32(r, r->ebp - 0x8);
    r->ebx = rd32(r, r->ebp - 0x4);
    return;
    push(r, r->ebx);
    push(r, r->ecx);
    push(r, r->edx);
    if (rd32(r, 0x52f150) == 0x0)
    {
        goto at_40b46c;
    }
    r->ecx = rd32(r, 0x52f158);
    if (r->ecx == 0)
    {
        goto at_40b447;
    }
    r->edx = rd32(r, r->ecx);
    push(r, r->ecx);
    call_all(r, rd32(r, r->edx + 0x48));
    r->eax = rd32(r, 0x52f158);
    r->edx = rd32(r, r->eax);
    push(r, r->eax);
    call_all(r, rd32(r, r->edx + 0x8));
at_40b447:
    r->ebx = rd32(r, 0x52f154);
    if (r->ebx == 0)
    {
        goto at_40b462;
    }
    r->edx = rd32(r, r->ebx);
    push(r, r->ebx);
    call_all(r, rd32(r, r->edx + 0x48));
    r->eax = rd32(r, 0x52f154);
    r->edx = rd32(r, r->eax);
    push(r, r->eax);
    call_all(r, rd32(r, r->edx + 0x8));
at_40b462:
    r->eax = rd32(r, 0x52f150);
    call(r, 0x40b080, 0);
at_40b46c:
    r->ebx = 0x1c;
    r->edx = 0;
    r->eax = 0x52f150;
    call(r, 0x4eb5c0, 0);
    r->eax = 0;
    r->edx = pop(r);
    r->ecx = pop(r);
    r->ebx = pop(r);
    return;
}

uint32_t vertrix_port_sound_output_open_40b110(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0xb4
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
