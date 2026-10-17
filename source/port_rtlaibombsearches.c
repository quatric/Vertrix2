#include "port_rtlaibombsearches.h"

/* The AI bomb search and blast estimate (see ai_player.c vertrix_ai_bomb_search). */

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

/* The last value pushed taken back. */
static uint32_t pop(Regs *r)
{
    return r->pushed != 0 ? r->stack[--r->pushed] : 0;
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

/* Original 0x427380: The AI bomb search and blast estimate (see ai_player.c
 * vertrix_ai_bomb_search). Evidence: calls 0x4261b0, 0x4344e0, 0x434300. Register-for-register from
 * the listing (0x42738b..0x427848); labels are the original addresses. */
static void run(Regs *r)
{
    wr32(r, r->ebp - 0x3c, r->eax);
    wr32(r, r->ebp - 0x20, r->edx);
    wr32(r, r->ebp - 0x1c, r->ebx);
    wr32(r, r->ebp - 0x18, r->ecx);
    r->ebx = rd32(r, r->ebp + 0x14);
    set_high8(&r->eax, 0);
    r->edx = rd32(r, r->ebp + 0x1c);
    wr8(r, r->ebp - 0x10, ((r->eax >> 8) & 0xff));
    wr8(r, r->ebp - 0xc, ((r->eax >> 8) & 0xff));
    if (r->edx <= 0x1)
    {
        goto at_4275cb;
    }
    if (rd32(r, r->ebp - 0x20) == 0x6)
    {
        goto at_4273c4;
    }
    if (rd32(r, r->ebp - 0x1c) == 0x6)
    {
        goto at_4273c4;
    }
    if (rd32(r, r->ebp - 0x18) != 0x6)
    {
        goto at_4275cb;
    }
at_4273c4:
    r->eax = rd32(r, r->ebp - 0x3c);
    r->ecx = 0x41;
    r->eax = r->eax + 0x184;
    r->edi = r->ebp - 0x94;
    r->esi = r->eax;
    wr32(r, r->ebp - 0x38, r->eax);
    push(r, r->edi);
    r->eax = r->ecx;
    r->ecx = r->ecx >> 0x2;
    rep_movs(r, 4);
    set_low8(&r->ecx, (r->eax & 0xff));
    set_low8(&r->ecx, (r->ecx & 0xff) & 0x3);
    rep_movs(r, 1);
    r->edi = pop(r);
    if (rd32(r, r->ebp + 0x24) != 0x23)
    {
        goto at_4275d6;
    }
    r->ecx = 0x2710;
    r->esi = rd32(r, r->ebp + 0x18);
    r->edx = r->ebp - 0x94;
    r->eax = rd32(r, r->ebp - 0x3c);
    r->edi = 0;
    wr32(r, r->ebp - 0x24, r->ecx);
    push(r, r->esi);
    r->ecx = r->ebx;
    r->ebx = r->ebp - 0x50;
    wr32(r, r->ebp - 0x14, r->edi);
    call(r, 0x4261b0, 1);
    r->eax = rd32(r, r->ebp - 0x38);
    wr32(r, r->ebp - 0x2c, r->edi);
    wr32(r, r->ebp - 0x34, r->eax);
at_427423:
    r->eax = rd32(r, r->ebp - 0x14);
    if ((uint8_t)rd8(r, r->eax + r->ebp - 0x50) == (uint8_t)0x0)
    {
        goto at_427590;
    }
    r->ecx = 0x41;
    r->esi = rd32(r, r->ebp - 0x34);
    r->edi = r->ebp - 0x94;
    r->edx = rd32(r, r->ebp - 0x2c);
    push(r, r->edi);
    r->eax = r->ecx;
    r->ecx = r->ecx >> 0x2;
    rep_movs(r, 4);
    set_low8(&r->ecx, (r->eax & 0xff));
    set_low8(&r->ecx, (r->ecx & 0xff) & 0x3);
    rep_movs(r, 1);
    r->edi = pop(r);
    r->ecx = 0xc;
    r->edx = r->edx + r->ecx;
    set_low8(&r->ebx, rd8(r, r->edx + r->ebp - 0x94));
    r->eax = r->edx;
    if ((uint8_t)((r->ebx & 0xff)) == (uint8_t)0xff)
    {
        goto at_427477;
    }
at_427467:
    r->ecx = r->ecx - 1;
    r->eax = r->eax - 1;
    if ((int32_t)r->ecx < 0)
    {
        goto at_427477;
    }
    if ((uint8_t)rd8(r, r->eax + r->ebp - 0x94) != (uint8_t)0xff && !r->port->env.failed)
    {
        goto at_427467;
    }
at_427477:
    if ((int32_t)r->ecx <= (int32_t)0xffffffffu)
    {
        goto at_427590;
    }
    r->eax = rd32(r, r->ebp - 0x2c);
    r->eax = r->eax + r->ecx;
    set_low8(&r->edx, rd8(r, r->ebp - 0x18));
    wr8(r, r->eax + r->ebp - 0x94, (r->edx & 0xff));
    if ((int32_t)r->ecx <= 0)
    {
        goto at_42749d;
    }
    set_low8(&r->edx, rd8(r, r->ebp - 0x1c));
    wr8(r, r->eax + r->ebp - 0x95, (r->edx & 0xff));
at_42749d:
    if ((int32_t)r->ecx <= (int32_t)0x1)
    {
        goto at_4274b1;
    }
    r->eax = rd32(r, r->ebp - 0x2c);
    r->eax = r->eax + r->ecx;
    set_low8(&r->edx, rd8(r, r->ebp - 0x20));
    wr8(r, r->eax + r->ebp - 0x96, (r->edx & 0xff));
at_4274b1:
    r->ebx = rd32(r, r->ebp + 0x1d);
    r->edx = r->ebp - 0x44;
    r->eax = r->ebp - 0x94;
    r->ebx = (uint32_t)((int32_t)r->ebx >> 0x18);
    call_keep(r, 0x4344e0);
    r->eax = rd32(r, r->ebp - 0x44);
    if ((int32_t)r->eax >= (int32_t)rd32(r, r->ebp - 0x24))
    {
        goto at_4274db;
    }
    wr32(r, r->ebp - 0x24, r->eax);
    set_low8(&r->eax, rd8(r, r->ebp - 0x14));
    wr8(r, r->ebp - 0x10, (r->eax & 0xff));
    set_low8(&r->eax, 0);
    wr8(r, r->ebp - 0xc, (r->eax & 0xff));
at_4274db:
    r->eax = rd32(r, r->ebp - 0x2c);
    r->eax = r->eax + r->ecx;
    set_low8(&r->edx, rd8(r, r->ebp - 0x20));
    wr8(r, r->eax + r->ebp - 0x94, (r->edx & 0xff));
    if ((int32_t)r->ecx <= 0)
    {
        goto at_4274f8;
    }
    set_low8(&r->edx, rd8(r, r->ebp - 0x18));
    wr8(r, r->eax + r->ebp - 0x95, (r->edx & 0xff));
at_4274f8:
    if ((int32_t)r->ecx <= (int32_t)0x1)
    {
        goto at_42750c;
    }
    r->eax = rd32(r, r->ebp - 0x2c);
    r->eax = r->eax + r->ecx;
    set_low8(&r->edx, rd8(r, r->ebp - 0x1c));
    wr8(r, r->eax + r->ebp - 0x96, (r->edx & 0xff));
at_42750c:
    r->ebx = rd32(r, r->ebp + 0x1d);
    r->edx = r->ebp - 0x44;
    r->eax = r->ebp - 0x94;
    r->ebx = (uint32_t)((int32_t)r->ebx >> 0x18);
    r->esi = rd32(r, r->ebp - 0x24);
    call_keep(r, 0x4344e0);
    r->eax = rd32(r, r->ebp - 0x44);
    if ((int32_t)r->eax >= (int32_t)r->esi)
    {
        goto at_427537;
    }
    wr32(r, r->ebp - 0x24, r->eax);
    set_low8(&r->eax, rd8(r, r->ebp - 0x14));
    wr8(r, r->ebp - 0x10, (r->eax & 0xff));
    wr8(r, r->ebp - 0xc, 0x1);
at_427537:
    r->eax = rd32(r, r->ebp - 0x2c);
    r->eax = r->eax + r->ecx;
    set_low8(&r->edx, rd8(r, r->ebp - 0x1c));
    wr8(r, r->eax + r->ebp - 0x94, (r->edx & 0xff));
    if ((int32_t)r->ecx <= 0)
    {
        goto at_427554;
    }
    set_low8(&r->edx, rd8(r, r->ebp - 0x20));
    wr8(r, r->eax + r->ebp - 0x95, (r->edx & 0xff));
at_427554:
    if ((int32_t)r->ecx <= (int32_t)0x1)
    {
        goto at_427566;
    }
    r->ecx = r->ecx + rd32(r, r->ebp - 0x2c);
    set_low8(&r->eax, rd8(r, r->ebp - 0x18));
    wr8(r, r->ecx + r->ebp - 0x96, (r->eax & 0xff));
at_427566:
    r->ebx = rd32(r, r->ebp + 0x1d);
    r->edx = r->ebp - 0x44;
    r->eax = r->ebp - 0x94;
    r->ebx = (uint32_t)((int32_t)r->ebx >> 0x18);
    call_keep(r, 0x4344e0);
    r->eax = rd32(r, r->ebp - 0x44);
    if ((int32_t)r->eax >= (int32_t)rd32(r, r->ebp - 0x24))
    {
        goto at_427590;
    }
    set_low8(&r->edx, 0x2);
    wr32(r, r->ebp - 0x24, r->eax);
    set_low8(&r->eax, rd8(r, r->ebp - 0x14));
    wr8(r, r->ebp - 0xc, (r->edx & 0xff));
    wr8(r, r->ebp - 0x10, (r->eax & 0xff));
at_427590:
    r->ecx = rd32(r, r->ebp - 0x2c);
    r->ebx = rd32(r, r->ebp - 0x14);
    r->ecx = r->ecx + 0xd;
    r->ebx = r->ebx + 1;
    wr32(r, r->ebp - 0x2c, r->ecx);
    wr32(r, r->ebp - 0x14, r->ebx);
    if ((int32_t)r->ebx < (int32_t)0x5 && !r->port->env.failed)
    {
        goto at_427423;
    }
at_4275a9:
    r->eax = 0;
    r->edx = rd32(r, r->ebp + 0xc);
    set_low8(&r->eax, rd8(r, r->ebp - 0x10));
    wr32(r, r->edx, r->eax);
    r->eax = 0;
    r->edx = rd32(r, r->ebp + 0x8);
    set_low8(&r->eax, rd8(r, r->ebp - 0xc));
    wr32(r, r->edx, r->eax);
    r->eax = 0x1;
    r->edi = rd32(r, r->ebp - 0x8);
    r->esi = rd32(r, r->ebp - 0x4);
    return;
at_4275cb:
    r->eax = 0;
    r->edi = rd32(r, r->ebp - 0x8);
    r->esi = rd32(r, r->ebp - 0x4);
    return;
at_4275d6:
    r->edx = 0;
    wr32(r, r->ebp - 0x28, r->edx);
    set_high8(&r->edx, rd8(r, r->ebp + 0x20));
    if ((uint8_t)(((r->edx >> 8) & 0xff)) != (uint8_t)0x2)
    {
        goto at_42780f;
    }
at_4275e7:
    r->eax = 0xc;
    set_high8(&r->ecx, rd8(r, r->ebp - 0x6e));
    r->edx = 0;
    if ((uint8_t)(((r->ecx >> 8) & 0xff)) == (uint8_t)0xff)
    {
        goto at_42760e;
    }
at_4275f6:
    if ((uint8_t)rd8(r, r->eax + r->ebp - 0x7a) != (uint8_t)0x6)
    {
        goto at_427602;
    }
    r->edx = 0x1;
at_427602:
    r->eax = r->eax - 1;
    if ((int32_t)r->eax < 0)
    {
        goto at_42760e;
    }
    if ((uint8_t)rd8(r, r->eax + r->ebp - 0x7a) != (uint8_t)0xff && !r->port->env.failed)
    {
        goto at_4275f6;
    }
at_42760e:
    r->ecx = 0xc;
    r->ecx = r->ecx - r->eax;
    if (r->edx == 0)
    {
        goto at_42781d;
    }
at_42761d:
    r->edx = rd32(r, r->ebp + 0x18);
    r->eax = rd32(r, r->ebp - 0x3c);
    r->ecx = r->ebx;
    push(r, r->edx);
    r->ebx = r->ebp - 0x50;
    r->edx = r->ebp - 0x94;
    call(r, 0x4261b0, 1);
    r->ecx = 0;
    r->eax = rd32(r, r->ebp - 0x3c);
    wr32(r, r->ebp - 0x14, r->ecx);
    r->eax = r->eax + 0x184;
    wr32(r, r->ebp - 0x48, r->ecx);
    wr32(r, r->ebp - 0x30, r->eax);
at_427647:
    r->eax = rd32(r, r->ebp - 0x14);
    if ((uint8_t)rd8(r, r->eax + r->ebp - 0x50) == (uint8_t)0x0)
    {
        goto at_4277f1;
    }
    r->ecx = 0x41;
    r->esi = rd32(r, r->ebp - 0x30);
    r->edi = r->ebp - 0x94;
    r->edx = rd32(r, r->ebp - 0x48);
    push(r, r->edi);
    r->eax = r->ecx;
    r->ecx = r->ecx >> 0x2;
    rep_movs(r, 4);
    set_low8(&r->ecx, (r->eax & 0xff));
    set_low8(&r->ecx, (r->ecx & 0xff) & 0x3);
    rep_movs(r, 1);
    r->edi = pop(r);
    r->esi = 0xc;
    r->edx = r->edx + r->esi;
    set_low8(&r->ebx, rd8(r, r->edx + r->ebp - 0x94));
    r->eax = r->edx;
    if ((uint8_t)((r->ebx & 0xff)) == (uint8_t)0xff)
    {
        goto at_42769b;
    }
at_42768b:
    r->esi = r->esi - 1;
    r->eax = r->eax - 1;
    if ((int32_t)r->esi < 0)
    {
        goto at_42769b;
    }
    if ((uint8_t)rd8(r, r->eax + r->ebp - 0x94) != (uint8_t)0xff && !r->port->env.failed)
    {
        goto at_42768b;
    }
at_42769b:
    if ((int32_t)r->esi <= (int32_t)0xffffffffu)
    {
        goto at_4277f1;
    }
    r->eax = rd32(r, r->ebp - 0x48);
    r->eax = r->eax + r->esi;
    set_low8(&r->edx, rd8(r, r->ebp - 0x18));
    wr8(r, r->eax + r->ebp - 0x94, (r->edx & 0xff));
    if ((int32_t)r->esi <= 0)
    {
        goto at_4276c1;
    }
    set_low8(&r->edx, rd8(r, r->ebp - 0x1c));
    wr8(r, r->eax + r->ebp - 0x95, (r->edx & 0xff));
at_4276c1:
    if ((int32_t)r->esi <= (int32_t)0x1)
    {
        goto at_4276d5;
    }
    r->eax = rd32(r, r->ebp - 0x48);
    r->eax = r->eax + r->esi;
    set_low8(&r->edx, rd8(r, r->ebp - 0x20));
    wr8(r, r->eax + r->ebp - 0x96, (r->edx & 0xff));
at_4276d5:
    r->ecx = rd32(r, r->ebp + 0x1d);
    r->ebx = r->ebp - 0x40;
    r->edx = r->ebp - 0x44;
    r->eax = r->ebp - 0x94;
    r->ecx = (uint32_t)((int32_t)r->ecx >> 0x18);
    r->edi = rd32(r, r->ebp + 0x1c);
    call_keep(r, 0x434300);
    r->eax = rd32(r, r->ebp - 0x40);
    if (r->edi <= 0x2)
    {
        goto at_427701;
    }
    r->eax = rd32(r, r->ebp - 0x44);
    r->edx = rd32(r, r->ebp - 0x40);
    r->eax = r->eax + r->eax;
    r->eax = r->eax + r->edx;
at_427701:
    if ((int32_t)r->eax <= (int32_t)rd32(r, r->ebp - 0x28))
    {
        goto at_427714;
    }
    wr32(r, r->ebp - 0x28, r->eax);
    set_low8(&r->ecx, 0);
    set_low8(&r->eax, rd8(r, r->ebp - 0x14));
    wr8(r, r->ebp - 0xc, (r->ecx & 0xff));
    wr8(r, r->ebp - 0x10, (r->eax & 0xff));
at_427714:
    r->eax = rd32(r, r->ebp - 0x48);
    r->eax = r->eax + r->esi;
    set_low8(&r->edx, rd8(r, r->ebp - 0x20));
    wr8(r, r->eax + r->ebp - 0x94, (r->edx & 0xff));
    if ((int32_t)r->esi <= 0)
    {
        goto at_427731;
    }
    set_low8(&r->edx, rd8(r, r->ebp - 0x18));
    wr8(r, r->eax + r->ebp - 0x95, (r->edx & 0xff));
at_427731:
    if ((int32_t)r->esi <= (int32_t)0x1)
    {
        goto at_427745;
    }
    r->eax = rd32(r, r->ebp - 0x48);
    r->eax = r->eax + r->esi;
    set_low8(&r->edx, rd8(r, r->ebp - 0x1c));
    wr8(r, r->eax + r->ebp - 0x96, (r->edx & 0xff));
at_427745:
    r->ecx = rd32(r, r->ebp + 0x1d);
    r->ebx = r->ebp - 0x40;
    r->edx = r->ebp - 0x44;
    r->eax = r->ebp - 0x94;
    r->ecx = (uint32_t)((int32_t)r->ecx >> 0x18);
    call_keep(r, 0x434300);
    r->ebx = rd32(r, r->ebp + 0x1c);
    r->eax = rd32(r, r->ebp - 0x40);
    if (r->ebx <= 0x2)
    {
        goto at_427771;
    }
    r->eax = rd32(r, r->ebp - 0x44);
    r->edi = rd32(r, r->ebp - 0x40);
    r->eax = r->eax + r->eax;
    r->eax = r->eax + r->edi;
at_427771:
    if ((int32_t)r->eax <= (int32_t)rd32(r, r->ebp - 0x28))
    {
        goto at_427784;
    }
    set_high8(&r->ecx, 0x1);
    wr32(r, r->ebp - 0x28, r->eax);
    set_low8(&r->eax, rd8(r, r->ebp - 0x14));
    wr8(r, r->ebp - 0xc, ((r->ecx >> 8) & 0xff));
    wr8(r, r->ebp - 0x10, (r->eax & 0xff));
at_427784:
    r->eax = rd32(r, r->ebp - 0x48);
    r->eax = r->eax + r->esi;
    set_low8(&r->edx, rd8(r, r->ebp - 0x1c));
    wr8(r, r->eax + r->ebp - 0x94, (r->edx & 0xff));
    if ((int32_t)r->esi <= 0)
    {
        goto at_4277a1;
    }
    set_low8(&r->edx, rd8(r, r->ebp - 0x20));
    wr8(r, r->eax + r->ebp - 0x95, (r->edx & 0xff));
at_4277a1:
    if ((int32_t)r->esi <= (int32_t)0x1)
    {
        goto at_4277b3;
    }
    r->esi = r->esi + rd32(r, r->ebp - 0x48);
    set_low8(&r->eax, rd8(r, r->ebp - 0x18));
    wr8(r, r->esi + r->ebp - 0x96, (r->eax & 0xff));
at_4277b3:
    r->ecx = rd32(r, r->ebp + 0x1d);
    r->ebx = r->ebp - 0x40;
    r->edx = r->ebp - 0x44;
    r->eax = r->ebp - 0x94;
    r->ecx = (uint32_t)((int32_t)r->ecx >> 0x18);
    call_keep(r, 0x434300);
    r->ebx = rd32(r, r->ebp + 0x1c);
    r->eax = rd32(r, r->ebp - 0x40);
    if (r->ebx <= 0x2)
    {
        goto at_4277df;
    }
    r->eax = rd32(r, r->ebp - 0x44);
    r->esi = rd32(r, r->ebp - 0x40);
    r->eax = r->eax + r->eax;
    r->eax = r->eax + r->esi;
at_4277df:
    if ((int32_t)r->eax <= (int32_t)rd32(r, r->ebp - 0x28))
    {
        goto at_4277f1;
    }
    wr32(r, r->ebp - 0x28, r->eax);
    set_low8(&r->eax, rd8(r, r->ebp - 0x14));
    wr8(r, r->ebp - 0x10, (r->eax & 0xff));
    wr8(r, r->ebp - 0xc, 0x2);
at_4277f1:
    r->eax = rd32(r, r->ebp - 0x48);
    r->edx = rd32(r, r->ebp - 0x14);
    r->eax = r->eax + 0xd;
    r->edx = r->edx + 1;
    wr32(r, r->ebp - 0x48, r->eax);
    wr32(r, r->ebp - 0x14, r->edx);
    if ((int32_t)r->edx < (int32_t)0x5 && !r->port->env.failed)
    {
        goto at_427647;
    }
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4275a9;
at_42780f:
    if ((uint8_t)(((r->edx >> 8) & 0xff)) == (uint8_t)0x3 && !r->port->env.failed)
    {
        goto at_4275e7;
    }
    if (r->port->env.failed)
    {
        return;
    }
    goto at_42761d;
at_42781d:
    if ((int32_t)r->eax <= (int32_t)0xffffffffu && !r->port->env.failed)
    {
        goto at_42761d;
    }
    if ((int32_t)r->ecx <= (int32_t)0x8 && !r->port->env.failed)
    {
        goto at_42761d;
    }
    r->eax = rd32(r, r->ebp + 0xc);
    wr32(r, r->eax, 0x2);
    r->eax = rd32(r, r->ebp + 0x8);
    wr32(r, r->eax, r->edx);
    r->eax = 0x1;
    r->edi = rd32(r, r->ebp - 0x8);
    r->esi = rd32(r, r->ebp - 0x4);
    return;
}

uint32_t vertrix_port_ai_bomb_search_427380(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x98
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
    r.ebp = entry->esp - 4;
    port_set32(&port, r.ebp, 0, entry->ebp);
    port_set32(&port, r.ebp, -0x4u, entry->esi);
    port_set32(&port, r.ebp, -0x8u, entry->edi);
    run(&r);
    return port_return(&port, r.eax, r.edx);
}
