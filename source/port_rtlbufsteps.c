#include "port_rtlbufsteps.h"

/* 0x4bd9e0 steps a state machine in the record at [this+0x1a8], with state at +0x44, step counter
 * +0x34 and limit +0x48 (= [this+0x13c]-1, later [this+0x13c]+2). */

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

static uint32_t rd8(Regs *r, uint32_t address)
{
    return port_u8(r->port, address, 0);
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

/* Original 0x4bd9e0: 0x4bd9e0 steps a state machine in the record at [this+0x1a8], with state at
 * +0x44, step counter +0x34 and limit +0x48 (= [this+0x13c]-1, later [this+0x13c]+2). Each step
 * calls the handler [[this+0x1b0]+4] (0x4bda8a, 0x4bdcb2) on the buffer chosen by the toggle flag
 * +0x40 (slot +0x38 or +0x3c), and the [this+0x1ac]+0xc callback (0x4bdc63) gates +0x30 and
 * advances +0x4c. When a pass finishes with +0x4c == 1, the loop at 0x4bdaf1-0x4bdc03 wraps the
 * edge rows of both per-entry buffers into their padding (row -1 gets the last row, the row after
 * the end gets row 0). Then +0x40 is flipped and state 2 is entered. Evidence: no calls.
 * Register-for-register from the listing (0x4bd9e8..0x4bddd4); labels are the original addresses.
 */
static void run(Regs *r)
{
    wr32(r, r->ebp - 0x5c, r->eax);
    wr32(r, r->ebp - 0x68, r->edx);
    wr32(r, r->ebp - 0x64, r->ebx);
    wr32(r, r->ebp - 0x60, r->ecx);
    r->eax = rd32(r, r->eax + 0x1a8);
    r->edx = rd32(r, r->eax + 0x30);
    wr32(r, r->ebp - 0x50, r->eax);
    if (r->edx == 0)
    {
        goto at_4bdc49;
    }
at_4bda08:
    r->eax = rd32(r, r->ebp - 0x50);
    r->eax = rd32(r, r->eax + 0x44);
    flags(r, F_SUB, r->eax, 0x1, 32);
    if (cond(r, CC_AE))
    {
        goto at_4bdda1;
    }
    if (r->eax != 0)
    {
        goto at_4bdc42;
    }
at_4bda1f:
    r->eax = rd32(r, r->ebp - 0x50);
    wr32(r, r->eax + 0x34, 0x0);
    r->eax = rd32(r, r->ebp - 0x5c);
    r->eax = rd32(r, r->eax + 0x13c);
    r->edx = rd32(r, r->ebp - 0x50);
    r->eax = r->eax - 1;
    wr32(r, r->edx + 0x48, r->eax);
    r->eax = rd32(r, r->edx + 0x4c);
    r->edx = rd32(r, r->ebp - 0x5c);
    if (r->eax == rd32(r, r->edx + 0x140))
    {
        goto at_4bdcd7;
    }
at_4bda4b:
    r->eax = rd32(r, r->ebp - 0x50);
    wr32(r, r->eax + 0x44, 0x1);
at_4bda55:
    r->esi = rd32(r, r->ebp - 0x5c);
    r->ecx = rd32(r, r->ebp - 0x60);
    r->ebx = rd32(r, r->ebp - 0x64);
    r->edi = rd32(r, r->ebp - 0x68);
    r->eax = rd32(r, r->ebp - 0x50);
    r->edx = rd32(r, r->ebp - 0x50);
    push(r, r->ecx);
    r->esi = rd32(r, r->esi + 0x1b0);
    r->eax = rd32(r, r->eax + 0x40);
    r->ecx = rd32(r, r->ebp - 0x50);
    push(r, r->ebx);
    r->eax = r->eax << 0x2;
    r->ebx = rd32(r, r->ebp - 0x50);
    push(r, r->edi);
    r->eax = r->eax + r->edx;
    r->ecx = rd32(r, r->ecx + 0x48);
    r->ebx = r->ebx + 0x34;
    r->edx = rd32(r, r->eax + 0x38);
    r->eax = rd32(r, r->ebp - 0x5c);
    call_all(r, rd32(r, r->esi + 0x4));
    r->eax = rd32(r, r->ebp - 0x50);
    r->edx = rd32(r, r->ebp - 0x50);
    r->eax = rd32(r, r->eax + 0x34);
    if (r->eax < rd32(r, r->edx + 0x48))
    {
        goto at_4bdc42;
    }
    r->ebx = rd32(r, r->edx + 0x4c);
    if (r->ebx != 0x1)
    {
        goto at_4bdc09;
    }
    r->edx = rd32(r, r->ebp - 0x5c);
    r->eax = rd32(r, r->ebp - 0x5c);
    r->esi = 0;
    r->edx = rd32(r, r->edx + 0xd8);
    wr32(r, r->ebp - 0x44, r->eax);
    wr32(r, r->ebp - 0x28, r->edx);
    r->eax = rd32(r, r->eax + 0x1a8);
    r->edx = rd32(r, r->ebp - 0x5c);
    wr32(r, r->ebp - 0x48, r->eax);
    r->eax = rd32(r, r->ebp - 0x5c);
    wr32(r, r->ebp - 0x30, r->esi);
    r->edi = rd32(r, r->edx + 0x24);
    r->eax = rd32(r, r->eax + 0x13c);
    if ((int32_t)r->edi <= 0)
    {
        goto at_4bdc09;
    }
    r->edx = r->eax + r->ebx;
    wr32(r, r->ebp - 0x24, r->esi);
    r->eax = r->eax + 0x2;
    wr32(r, r->ebp - 0x54, r->edx);
    wr32(r, r->ebp - 0x58, r->eax);
at_4bdaf1:
    r->edx = rd32(r, r->ebp - 0x28);
    r->eax = rd32(r, r->ebp - 0x28);
    r->edx = rd32(r, r->edx + 0xc);
    r->edx = r->edx * rd32(r, r->eax + 0x24);
    r->ecx = rd32(r, r->ebp - 0x44);
    r->ebx = rd32(r, r->ecx + 0x13c);
    r->eax = r->edx;
    r->edx = (uint32_t)((int32_t)r->edx >> 0x1f);
    idiv32(r, r->ebx);
    wr32(r, r->ebp - 0x20, r->eax);
    r->eax = rd32(r, r->ebp - 0x48);
    r->esi = rd32(r, r->ebp - 0x24);
    r->eax = rd32(r, r->eax + 0x38);
    r->eax = r->eax + r->esi;
    r->esi = rd32(r, r->ebp - 0x48);
    r->edi = rd32(r, r->ebp - 0x24);
    r->edx = rd32(r, r->eax);
    r->esi = rd32(r, r->esi + 0x3c);
    r->eax = 0;
    r->esi = r->esi + r->edi;
    r->ecx = rd32(r, r->ebp - 0x20);
    wr32(r, r->ebp - 0xc, r->eax);
    r->esi = rd32(r, r->esi);
    if ((int32_t)r->ecx <= 0)
    {
        goto at_4bdbe0;
    }
    r->eax = r->ecx;
    r->eax = r->eax * rd32(r, r->ebp - 0x54);
    r->ebx = rd32(r, r->ebp - 0x58);
    r->ecx = rd32(r, r->ebp - 0x20);
    r->ecx = r->ecx * r->ebx;
    r->ecx = r->ecx << 0x2;
    wr32(r, r->ebp - 0x4c, r->eax);
    r->eax = r->esi + r->ecx;
    r->ebx = r->edx + r->ecx;
    r->ecx = rd32(r, r->ebp - 0x20);
    r->ecx = r->ecx << 0x2;
    r->edi = r->ecx;
    wr32(r, r->ebp - 0x6c, r->ecx);
    r->edi = 0u - r->edi;
    wr32(r, r->ebp - 0x6c, r->edi);
    r->ecx = r->edi + r->esi;
    r->edi = rd32(r, r->ebp - 0x4c);
    r->edi = r->edi << 0x2;
    wr32(r, r->ebp - 0x10, r->esi);
    r->esi = r->esi + r->edi;
    wr32(r, r->ebp - 0x18, r->esi);
    r->esi = rd32(r, r->ebp - 0x6c);
    wr32(r, r->ebp - 0x1c, r->edx);
    r->esi = r->esi + r->edx;
    wr32(r, r->ebp - 0x14, r->esi);
    r->edx = r->edx + r->edi;
at_4bdb84:
    r->edi = rd32(r, r->ebp - 0x14);
    r->esi = rd32(r, r->edx);
    wr32(r, r->edi, r->esi);
    r->esi = rd32(r, r->ebp - 0x18);
    r->esi = rd32(r, r->esi);
    wr32(r, r->ecx, r->esi);
    r->esi = rd32(r, r->ebp - 0x1c);
    r->ebx = r->ebx + 0x4;
    r->esi = rd32(r, r->esi);
    r->eax = r->eax + 0x4;
    wr32(r, r->ebx - 0x4, r->esi);
    r->esi = rd32(r, r->ebp - 0x10);
    r->ecx = r->ecx + 0x4;
    r->edx = r->edx + 0x4;
    r->esi = rd32(r, r->esi);
    r->edi = rd32(r, r->ebp - 0x1c);
    wr32(r, r->eax - 0x4, r->esi);
    r->esi = rd32(r, r->ebp - 0x10);
    r->edi = r->edi + 0x4;
    r->esi = r->esi + 0x4;
    wr32(r, r->ebp - 0x1c, r->edi);
    wr32(r, r->ebp - 0x10, r->esi);
    r->esi = rd32(r, r->ebp - 0x18);
    r->edi = rd32(r, r->ebp - 0x14);
    r->esi = r->esi + 0x4;
    r->edi = r->edi + 0x4;
    wr32(r, r->ebp - 0x18, r->esi);
    r->esi = rd32(r, r->ebp - 0xc);
    wr32(r, r->ebp - 0x14, r->edi);
    r->esi = r->esi + 1;
    r->edi = rd32(r, r->ebp - 0x20);
    wr32(r, r->ebp - 0xc, r->esi);
    if ((int32_t)r->esi < (int32_t)r->edi && !r->port->env.failed)
    {
        goto at_4bdb84;
    }
at_4bdbe0:
    r->eax = rd32(r, r->ebp - 0x24);
    r->edx = rd32(r, r->ebp - 0x30);
    r->ecx = rd32(r, r->ebp - 0x28);
    r->eax = r->eax + 0x4;
    r->edx = r->edx + 1;
    wr32(r, r->ebp - 0x24, r->eax);
    wr32(r, r->ebp - 0x30, r->edx);
    r->eax = r->edx;
    r->edx = rd32(r, r->ebp - 0x44);
    r->ecx = r->ecx + 0x54;
    r->ebx = rd32(r, r->edx + 0x24);
    wr32(r, r->ebp - 0x28, r->ecx);
    if ((int32_t)r->eax < (int32_t)r->ebx && !r->port->env.failed)
    {
        goto at_4bdaf1;
    }
at_4bdc09:
    r->eax = rd32(r, r->ebp - 0x50);
    set_low8(&r->edx, rd8(r, r->eax + 0x40));
    wr32(r, r->eax + 0x30, 0x0);
    set_low8(&r->edx, (r->edx & 0xff) ^ 0x1);
    wr8(r, r->eax + 0x40, (r->edx & 0xff));
    r->eax = rd32(r, r->ebp - 0x5c);
    r->eax = rd32(r, r->eax + 0x13c);
    r->edx = rd32(r, r->ebp - 0x50);
    r->eax = r->eax + 1;
    wr32(r, r->edx + 0x34, r->eax);
    r->eax = rd32(r, r->ebp - 0x5c);
    r->eax = rd32(r, r->eax + 0x13c);
    r->eax = r->eax + 0x2;
    wr32(r, r->edx + 0x44, 0x2);
    wr32(r, r->edx + 0x48, r->eax);
at_4bdc42:
    r->edi = rd32(r, r->ebp - 0x8);
    r->esi = rd32(r, r->ebp - 0x4);
    return;
at_4bdc49:
    r->eax = rd32(r, r->eax + 0x40);
    r->ebx = rd32(r, r->ebp - 0x50);
    r->eax = r->eax << 0x2;
    r->ecx = rd32(r, r->ebp - 0x5c);
    r->eax = r->eax + r->ebx;
    r->ecx = rd32(r, r->ecx + 0x1ac);
    r->edx = rd32(r, r->eax + 0x38);
    r->eax = rd32(r, r->ebp - 0x5c);
    call_all(r, rd32(r, r->ecx + 0xc));
    if (r->eax == 0 && !r->port->env.failed)
    {
        goto at_4bdc42;
    }
    r->esi = rd32(r, r->ebx + 0x4c);
    wr32(r, r->ebx + 0x30, 0x1);
    r->esi = r->esi + 1;
    wr32(r, r->ebx + 0x4c, r->esi);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4bda08;
at_4bdc7d:
    r->esi = rd32(r, r->ebp - 0x5c);
    r->edi = rd32(r, r->ebp - 0x60);
    r->eax = rd32(r, r->ebp - 0x64);
    push(r, r->edi);
    r->edx = rd32(r, r->ebp - 0x68);
    r->ebx = rd32(r, r->ebp - 0x50);
    push(r, r->eax);
    r->eax = rd32(r, r->ebp - 0x50);
    r->ecx = rd32(r, r->ebp - 0x50);
    r->ebx = r->ebx + 0x34;
    r->eax = rd32(r, r->eax + 0x40);
    r->edi = rd32(r, r->ebp - 0x50);
    r->eax = r->eax << 0x2;
    r->esi = rd32(r, r->esi + 0x1b0);
    r->eax = r->eax + r->edi;
    r->ecx = rd32(r, r->ecx + 0x48);
    push(r, r->edx);
    r->edx = rd32(r, r->eax + 0x38);
    r->eax = rd32(r, r->ebp - 0x5c);
    call_all(r, rd32(r, r->esi + 0x4));
    r->eax = rd32(r, r->edi + 0x34);
    if (r->eax < rd32(r, r->edi + 0x48) && !r->port->env.failed)
    {
        goto at_4bdc42;
    }
    r->eax = rd32(r, r->ebp - 0x64);
    wr32(r, r->edi + 0x44, 0x0);
    r->ebx = rd32(r, r->ebp - 0x60);
    if (r->ebx <= rd32(r, r->eax) && !r->port->env.failed)
    {
        goto at_4bdc42;
    }
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4bda1f;
at_4bdcd7:
    wr32(r, r->ebp - 0x40, r->edx);
    r->edi = 0;
    r->eax = rd32(r, r->edx + 0x1a8);
    wr32(r, r->ebp - 0x2c, r->edi);
    r->edi = rd32(r, r->edx + 0xd8);
    r->edx = rd32(r, r->edx + 0x24);
    wr32(r, r->ebp - 0x34, r->eax);
    if ((int32_t)r->edx <= 0 && !r->port->env.failed)
    {
        goto at_4bda4b;
    }
    r->eax = 0;
    wr32(r, r->ebp - 0x38, r->eax);
at_4bdcfe:
    r->ecx = rd32(r, r->edi + 0xc);
    r->ecx = r->ecx * rd32(r, r->edi + 0x24);
    r->ebx = rd32(r, r->ebp - 0x40);
    r->esi = rd32(r, r->ebx + 0x13c);
    r->edx = r->ecx;
    r->eax = r->ecx;
    r->edx = (uint32_t)((int32_t)r->edx >> 0x1f);
    idiv32(r, r->esi);
    wr32(r, r->ebp - 0x3c, r->eax);
    r->edx = 0;
    r->eax = rd32(r, r->edi + 0x2c);
    div32(r, r->ecx);
    r->ebx = r->edx;
    if (r->edx != 0)
    {
        goto at_4bdd29;
    }
    r->ebx = r->ecx;
at_4bdd29:
    if (rd32(r, r->ebp - 0x2c) != 0x0)
    {
        goto at_4bdd43;
    }
    r->edx = r->ebx - 0x1;
    r->ecx = rd32(r, r->ebp - 0x3c);
    r->eax = r->edx;
    r->edx = (uint32_t)((int32_t)r->edx >> 0x1f);
    idiv32(r, r->ecx);
    r->edx = rd32(r, r->ebp - 0x34);
    r->eax = r->eax + 1;
    wr32(r, r->edx + 0x48, r->eax);
at_4bdd43:
    r->eax = rd32(r, r->ebp - 0x34);
    r->eax = rd32(r, r->eax + 0x40);
    r->esi = rd32(r, r->ebp - 0x34);
    r->eax = r->eax << 0x2;
    r->eax = r->eax + r->esi;
    r->edx = rd32(r, r->ebp - 0x38);
    r->eax = rd32(r, r->eax + 0x38);
    r->eax = r->eax + r->edx;
    r->ebx = r->ebx << 0x2;
    r->esi = rd32(r, r->eax);
    r->esi = r->esi + r->ebx;
    r->ebx = rd32(r, r->ebp - 0x3c);
    r->edx = 0;
    r->ebx = r->ebx + r->ebx;
    r->eax = r->esi;
    if ((int32_t)r->ebx <= 0)
    {
        goto at_4bdd7b;
    }
at_4bdd6d:
    r->eax = r->eax + 0x4;
    r->ecx = rd32(r, r->esi - 0x4);
    r->edx = r->edx + 1;
    wr32(r, r->eax - 0x4, r->ecx);
    if ((int32_t)r->edx < (int32_t)r->ebx && !r->port->env.failed)
    {
        goto at_4bdd6d;
    }
at_4bdd7b:
    r->ecx = rd32(r, r->ebp - 0x38);
    r->ebx = rd32(r, r->ebp - 0x2c);
    r->edx = rd32(r, r->ebp - 0x40);
    r->edi = r->edi + 0x54;
    r->ecx = r->ecx + 0x4;
    r->ebx = r->ebx + 1;
    r->esi = rd32(r, r->edx + 0x24);
    wr32(r, r->ebp - 0x38, r->ecx);
    wr32(r, r->ebp - 0x2c, r->ebx);
    if ((int32_t)r->ebx >= (int32_t)r->esi && !r->port->env.failed)
    {
        goto at_4bda4b;
    }
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4bdcfe;
at_4bdda1:
    if (cond(r, CC_BE) && !r->port->env.failed)
    {
        goto at_4bda55;
    }
    if (r->eax == 0x2 && !r->port->env.failed)
    {
        goto at_4bdc7d;
    }
    r->edi = rd32(r, r->ebp - 0x8);
    r->esi = rd32(r, r->ebp - 0x4);
    return;
    push(r, r->esi);
    push(r, r->ecx);
    push(r, r->ebx);
    r->esi = rd32(r, r->eax + 0x1b0);
    r->ecx = 0;
    push(r, r->edx);
    r->ebx = 0;
    r->edx = 0;
    call_all(r, rd32(r, r->esi + 0x4));
    r->esi = pop(r);
    return;
}

uint32_t vertrix_port_staged_buffer_step_wrap_pad_4bd9e0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x70
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
    port_set32(&port, r.ebp, -0x4u, entry->esi);
    port_set32(&port, r.ebp, -0x8u, entry->edi);
    run(&r);
    return port_return(&port, r.eax, r.edx);
}
