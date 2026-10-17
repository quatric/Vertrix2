#include "port_rtltextwraps.h"

/* Wraps text to a width, measuring words with 0x440610 and building the lines as strings. */

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

/* The last value pushed taken back. */
static uint32_t pop(Regs *r)
{
    return r->pushed != 0 ? r->stack[--r->pushed] : 0;
}

/* repne scasb: edi walked to just past the first byte equal to al (or ecx bytes). */
static void repne_scasb(Regs *r)
{
    while (r->ecx != 0 && !r->port->env.failed)
    {
        uint32_t byte = rd8(r, r->edi);
        r->ecx--;
        r->edi++;
        flags(r, F_SUB, r->eax & 0xff, byte, 8);
        if ((r->eax & 0xff) == byte)
        {
            break;
        }
    }
}

/* Original 0x4b25b0: Wraps text to a width, measuring words with 0x440610 and building the lines as
 * strings. Evidence: calls 0x4ca370, 0x4ca280, 0x4ca630, 0x440610, 0x4ca210. Register-for-register
 * from the listing (0x4b25b8..0x4b29c9); labels are the original addresses. */
static void run(Regs *r)
{
    r->esi = rd32(r, r->ebp + 0xc);
    r->edi = rd32(r, r->ebp + 0x10);
    wr32(r, r->ebp - 0x24, r->eax);
    wr32(r, r->ebp - 0x54, r->edx);
    wr8(r, r->ebp - 0xc, (r->ebx & 0xff));
    r->eax = r->ebp - 0x68;
    r->edx = 0x4ec1ec;
    r->ebx = 0x517b68;
    push(r, r->port->env.chain);
    wr32(r, r->eax, pop(r));
    r->port->env.chain = r->eax;
    wr32(r, r->ebp - 0x64, r->edx);
    wr32(r, r->ebp - 0x60, r->ebx);
    r->eax = 0;
    r->ebx = rd32(r, r->ebp - 0x24);
    r->edx = rd32(r, r->ebp - 0x54);
    r->ebx = r->ebx + 0x15c;
    wr32(r, r->ebp - 0x5c, r->eax);
    r->eax = r->ebx;
    call_keep(r, 0x4ca370);
    r->edx = rd32(r, r->ebp - 0x24);
    set_low8(&r->eax, rd8(r, r->ebp - 0xc));
    wr8(r, r->edx + 0x160, (r->eax & 0xff));
    r->eax = r->edx;
    wr16(r, r->edx + 0xe, (r->ecx & 0xffff));
    r->edx = rd32(r, r->ebp + 0x8);
    wr16(r, r->eax + 0x16, (r->edx & 0xffff));
    r->edx = rd32(r, r->ebp - 0x24);
    r->eax = (uint32_t)(int32_t)(int16_t)(r->esi & 0xffff);
    wr32(r, r->edx + 0xf4, r->eax);
    r->eax = (uint32_t)(int32_t)(int16_t)(r->edi & 0xffff);
    wr32(r, r->edx + 0xf8, r->eax);
    r->eax = rd32(r, r->ebp + 0x14);
    wr16(r, r->edx + 0x2f2, (r->eax & 0xffff));
    r->eax = rd32(r, r->ebp + 0x18);
    wr16(r, r->edx + 0x2f4, (r->eax & 0xffff));
    r->eax = r->edx;
    r->edx = rd32(r, r->ebp + 0x1c);
    wr16(r, r->eax + 0x2f6, (r->edx & 0xffff));
    r->edx = rd32(r, r->ebp + 0x20);
    wr16(r, r->eax + 0x2f8, (r->edx & 0xffff));
    r->edx = rd32(r, r->ebp + 0x24);
    wr32(r, r->eax + 0x2fc, r->edx);
    r->edx = rd32(r, r->ebp + 0x28);
    wr32(r, r->eax + 0x300, r->edx);
    r->edx = rd32(r, r->ebp + 0x2c);
    r->edi = rd32(r, r->ebp - 0x54);
    wr32(r, r->eax + 0x304, r->edx);
    r->ecx = r->ecx - r->ecx;
    r->ecx = r->ecx - 1;
    r->eax = 0;
    repne_scasb(r);
    r->ecx = ~r->ecx;
    r->ecx = r->ecx - 1;
    r->edx = 0;
    r->eax = rd32(r, r->ebp - 0x24);
    wr32(r, r->ebp - 0x1c, r->edx);
    wr8(r, r->eax + 0x161, 0x0);
    r->eax = rd32(r, r->ebp + 0x14);
    r->eax = r->eax + rd32(r, r->ebp + 0x18);
    r->esi = r->esi - r->eax;
    wr32(r, r->ebp - 0x14, r->esi);
    wr32(r, r->ebp - 0x4c, 0x1);
    r->esi = 0;
    wr32(r, r->ebp - 0x28, r->ecx);
    wr32(r, r->ebp - 0x18, r->esi);
    if (r->ecx == 0)
    {
        goto at_4b26bf;
    }
    r->edx = rd32(r, r->ebx);
    r->eax = r->edx;
    r->ecx = r->ecx + r->edx;
at_4b26b4:
    set_low8(&r->edx, rd8(r, r->eax));
    if ((uint8_t)((r->edx & 0xff)) == (uint8_t)0x20)
    {
        goto at_4b27ca;
    }
at_4b26bf:
    r->eax = rd32(r, r->ebp - 0x24);
    r->eax = r->eax + 0x15c;
    r->edx = rd32(r, r->ebp - 0x28);
    wr32(r, r->ebp - 0x30, r->eax);
    r->eax = rd32(r, r->ebp - 0x54);
    r->eax = r->eax + r->edx;
    wr32(r, r->ebp - 0x20, r->eax);
at_4b26d5:
    r->eax = rd32(r, r->ebp - 0x1c);
    if (r->eax >= rd32(r, r->ebp - 0x28))
    {
        goto at_4b28f6;
    }
    r->edi = rd32(r, r->ebp - 0x28);
    r->ecx = 0;
    r->esi = r->eax;
    wr16(r, r->ebp - 0x10, (r->ecx & 0xffff));
    if (r->eax >= r->edi)
    {
        goto at_4b276d;
    }
    r->eax = rd32(r, r->ebp - 0x54);
    r->edi = r->esi + r->eax;
    r->eax = rd32(r, r->ebp - 0x20);
    wr32(r, r->ebp - 0x2c, r->eax);
at_4b2700:
    if ((uint8_t)rd8(r, r->edi) == (uint8_t)0x20)
    {
        goto at_4b276d;
    }
    r->edx = 0x511083;
    r->eax = r->ebp - 0x48;
    call_keep(r, 0x4ca280);
    r->eax = 0x1;
    r->edx = 0;
    wr32(r, r->ebp - 0x5c, r->eax);
    r->eax = r->ebp - 0x48;
    set_low8(&r->edx, rd8(r, r->edi));
    call_keep(r, 0x4ca630);
    r->eax = r->ebp - 0x40;
    r->ecx = r->ebp - 0x44;
    push(r, r->eax);
    r->eax = rd32(r, r->ebp - 0x24);
    r->ebx = 0;
    r->edi = r->edi + 1;
    set_low8(&r->ebx, rd8(r, r->eax + 0x44));
    r->eax = rd32(r, r->eax + 0x15d);
    r->edx = rd32(r, r->ebp - 0x48);
    r->eax = (uint32_t)((int32_t)r->eax >> 0x18);
    r->esi = r->esi + 1;
    call(r, 0x440610, 1);
    r->eax = rd32(r, r->ebp - 0x44);
    r->edx = rd32(r, r->ebp - 0x10);
    r->ebx = rd32(r, r->ebp - 0x2c);
    r->edx = r->edx + r->eax;
    r->ecx = 0;
    wr16(r, r->ebp - 0x10, (r->edx & 0xffff));
    r->edx = 0;
    r->eax = r->ebp - 0x48;
    wr32(r, r->ebp - 0x5c, r->edx);
    call_keep(r, 0x4ca210);
    wr32(r, r->ebp - 0x5c, r->ecx);
    if (r->edi < r->ebx && !r->port->env.failed)
    {
        goto at_4b2700;
    }
at_4b276d:
    r->eax = 0;
    r->edx = rd32(r, r->ebp - 0x12);
    set_low16(&r->eax, rd16(r, r->ebp - 0x18));
    r->edx = (uint32_t)((int32_t)r->edx >> 0x10);
    r->edx = r->edx + r->eax;
    r->eax = 0;
    set_low16(&r->eax, rd16(r, r->ebp - 0x14));
    if ((int32_t)r->edx <= (int32_t)r->eax)
    {
        goto at_4b27df;
    }
    r->edx = rd32(r, r->ebp - 0x24);
    r->eax = 0;
    set_low8(&r->eax, rd8(r, r->edx + 0x161));
    r->eax = r->eax + r->eax;
    r->eax = r->eax + r->edx;
    r->edx = rd32(r, r->ebp - 0x1c);
    set_low16(&r->esi, rd16(r, r->eax + 0x162));
    r->edx = r->edx - r->esi;
    wr16(r, r->eax + 0x22a, (r->edx & 0xffff));
    r->eax = rd32(r, r->ebp - 0x24);
    r->ecx = 0x1;
    r->edi = 0;
    set_low8(&r->ebx, rd8(r, r->eax + 0x161));
    wr32(r, r->ebp - 0x18, r->edi);
    set_low8(&r->ebx, (r->ebx & 0xff) + 1);
    wr32(r, r->ebp - 0x4c, r->ecx);
    wr8(r, r->eax + 0x161, (r->ebx & 0xff));
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4b26d5;
at_4b27ca:
    r->edi = rd32(r, r->ebp - 0x1c);
    r->edi = r->edi + 1;
    r->eax = r->eax + 1;
    wr32(r, r->ebp - 0x1c, r->edi);
    if (r->eax < r->ecx && !r->port->env.failed)
    {
        goto at_4b26b4;
    }
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4b26bf;
at_4b27df:
    if (rd32(r, r->ebp - 0x4c) != 0x1)
    {
        goto at_4b2803;
    }
    r->edx = rd32(r, r->ebp - 0x24);
    r->eax = 0;
    set_low8(&r->eax, rd8(r, r->edx + 0x161));
    r->eax = r->eax + r->eax;
    r->ecx = 0;
    r->eax = r->eax + r->edx;
    r->edx = rd32(r, r->ebp - 0x1c);
    wr32(r, r->ebp - 0x4c, r->ecx);
    wr16(r, r->eax + 0x162, (r->edx & 0xffff));
at_4b2803:
    r->eax = rd32(r, r->ebp - 0x10);
    r->ebx = rd32(r, r->ebp - 0x18);
    r->edi = rd32(r, r->ebp - 0x28);
    wr32(r, r->ebp - 0x1c, r->esi);
    r->ecx = 0;
    r->ebx = r->ebx + r->eax;
    wr16(r, r->ebp - 0x10, (r->ecx & 0xffff));
    wr32(r, r->ebp - 0x18, r->ebx);
    if (r->esi >= r->edi)
    {
        goto at_4b2885;
    }
at_4b281e:
    r->eax = rd32(r, r->ebp - 0x30);
    r->eax = rd32(r, r->eax);
    set_low8(&r->eax, rd8(r, r->esi + r->eax));
    if ((uint8_t)((r->eax & 0xff)) != (uint8_t)0x20)
    {
        goto at_4b2885;
    }
    r->edx = 0x511084;
    r->eax = r->ebp - 0x3c;
    r->ebx = 0x3;
    call_keep(r, 0x4ca280);
    r->eax = r->ebp - 0x34;
    wr32(r, r->ebp - 0x5c, r->ebx);
    push(r, r->eax);
    r->eax = rd32(r, r->ebp - 0x24);
    r->ebx = 0;
    r->ecx = r->ebp - 0x38;
    set_low8(&r->ebx, rd8(r, r->eax + 0x44));
    r->eax = rd32(r, r->eax + 0x15d);
    r->edx = rd32(r, r->ebp - 0x3c);
    r->eax = (uint32_t)((int32_t)r->eax >> 0x18);
    r->esi = r->esi + 1;
    call(r, 0x440610, 1);
    r->eax = rd32(r, r->ebp - 0x38);
    r->edx = rd32(r, r->ebp - 0x10);
    r->edi = 0;
    r->edx = r->edx + r->eax;
    r->eax = r->ebp - 0x3c;
    wr16(r, r->ebp - 0x10, (r->edx & 0xffff));
    r->edx = 0;
    wr32(r, r->ebp - 0x5c, r->edi);
    call_keep(r, 0x4ca210);
    r->edx = rd32(r, r->ebp - 0x28);
    wr32(r, r->ebp - 0x5c, r->edi);
    if (r->esi < r->edx && !r->port->env.failed)
    {
        goto at_4b281e;
    }
at_4b2885:
    r->edx = 0;
    r->eax = rd32(r, r->ebp - 0x12);
    set_low16(&r->edx, rd16(r, r->ebp - 0x18));
    r->eax = (uint32_t)((int32_t)r->eax >> 0x10);
    r->edx = r->edx + r->eax;
    r->eax = 0;
    set_low16(&r->eax, rd16(r, r->ebp - 0x14));
    if ((int32_t)r->edx <= (int32_t)r->eax)
    {
        goto at_4b28e3;
    }
    r->edx = rd32(r, r->ebp - 0x24);
    r->eax = 0;
    set_low8(&r->eax, rd8(r, r->edx + 0x161));
    r->eax = r->eax + r->eax;
    r->eax = r->eax + r->edx;
    r->edx = rd32(r, r->ebp - 0x1c);
    set_low16(&r->edx, (r->edx & 0xffff) - rd16(r, r->eax + 0x162));
    r->ebx = 0x1;
    wr16(r, r->eax + 0x22a, (r->edx & 0xffff));
    r->eax = rd32(r, r->ebp - 0x24);
    r->edi = 0;
    wr32(r, r->ebp - 0x4c, r->ebx);
    set_high8(&r->ebx, rd8(r, r->eax + 0x161));
    wr32(r, r->ebp - 0x18, r->edi);
    set_high8(&r->ebx, ((r->ebx >> 8) & 0xff) + 1);
    wr32(r, r->ebp - 0x1c, r->esi);
    wr8(r, r->eax + 0x161, ((r->ebx >> 8) & 0xff));
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4b26d5;
at_4b28e3:
    r->eax = rd32(r, r->ebp - 0x10);
    r->ebx = rd32(r, r->ebp - 0x18);
    r->ebx = r->ebx + r->eax;
    wr32(r, r->ebp - 0x1c, r->esi);
    wr32(r, r->ebp - 0x18, r->ebx);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4b26d5;
at_4b28f6:
    if ((uint16_t)rd16(r, r->ebp - 0x18) != (uint16_t)0x0)
    {
        goto at_4b294e;
    }
at_4b28fd:
    r->esi = 0;
    wr32(r, r->ebp - 0x50, r->esi);
    r->esi = rd32(r, r->ebp - 0x24);
    r->edi = rd32(r, r->ebp - 0x24);
    r->esi = r->esi + 0x15c;
at_4b290e:
    r->edx = rd32(r, r->ebp - 0x24);
    r->eax = 0;
    set_low8(&r->eax, rd8(r, r->edx + 0x161));
    if (r->eax <= rd32(r, r->ebp - 0x50))
    {
        goto at_4b29ba;
    }
    r->eax = 0;
    set_low16(&r->eax, rd16(r, r->edi + 0x22a));
    r->eax = r->eax - 1;
    if ((int32_t)r->eax <= 0)
    {
        goto at_4b297b;
    }
    r->ebx = r->edi;
at_4b2932:
    if ((int32_t)r->eax <= 0)
    {
        goto at_4b2987;
    }
    r->ecx = 0;
    set_low16(&r->ecx, rd16(r, r->ebx + 0x162));
    r->edx = rd32(r, r->esi);
    r->ecx = r->ecx + r->eax;
    set_low8(&r->edx, rd8(r, r->ecx + r->edx));
    if ((uint8_t)((r->edx & 0xff)) != (uint8_t)0x20)
    {
        goto at_4b2987;
    }
    r->eax = r->eax - 1;
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4b2932;
at_4b294e:
    r->edx = rd32(r, r->ebp - 0x24);
    r->eax = 0;
    set_low8(&r->eax, rd8(r, r->edx + 0x161));
    r->eax = r->eax + r->eax;
    r->eax = r->eax + r->edx;
    r->edx = rd32(r, r->ebp - 0x1c);
    set_low16(&r->ebx, rd16(r, r->eax + 0x162));
    r->edx = r->edx - r->ebx;
    wr16(r, r->eax + 0x22a, (r->edx & 0xffff));
    r->eax = rd32(r, r->ebp - 0x24);
    wr8(r, r->eax + 0x161, rd8(r, r->eax + 0x161) + 1);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4b28fd;
at_4b297b:
    r->ecx = rd32(r, r->ebp - 0x50);
    r->ecx = r->ecx + 1;
    r->edi = r->edi + 0x2;
    wr32(r, r->ebp - 0x50, r->ecx);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4b290e;
at_4b2987:
    if ((int32_t)r->eax <= 0)
    {
        goto at_4b29a2;
    }
    r->eax = r->eax + 1;
    wr16(r, r->edi + 0x22a, (r->eax & 0xffff));
    r->ecx = rd32(r, r->ebp - 0x50);
    r->ecx = r->ecx + 1;
    r->edi = r->edi + 0x2;
    wr32(r, r->ebp - 0x50, r->ecx);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4b290e;
at_4b29a2:
    wr16(r, r->edi + 0x22a, 0x0);
    r->ecx = rd32(r, r->ebp - 0x50);
    r->ecx = r->ecx + 1;
    r->edi = r->edi + 0x2;
    wr32(r, r->ebp - 0x50, r->ecx);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4b290e;
at_4b29ba:
    r->eax = rd32(r, r->ebp - 0x68);
    r->port->env.chain = r->eax;
    r->edi = rd32(r, r->ebp - 0x8);
    r->esi = rd32(r, r->ebp - 0x4);
    return;
}

uint32_t vertrix_port_text_wrap_4b25b0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x6c
    };
    Port port;
    uint8_t stack[BELOW + 8 + 4 * 10];
    Regs r;
    port_open_arguments(&port, stack, calls, services, globals, entry, BELOW, 10);
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
