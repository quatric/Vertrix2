#include "port_rtlaisearches.h"

/* The AI figure search over the board copy (see ai_player.c vertrix_ai_search_native). */

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

/* Original 0x4270a0: The AI figure search over the board copy (see ai_player.c
 * vertrix_ai_search_native). Evidence: calls 0x4eb5c0, 0x4261b0, 0x434ee0. Register-for-register
 * from the listing (0x4270ab..0x427372); labels are the original addresses. */
static void run(Regs *r)
{
    wr32(r, r->ebp - 0x30, r->eax);
    wr32(r, r->ebp - 0x2c, r->edx);
    wr32(r, r->ebp - 0x20, r->ebx);
    wr32(r, r->ebp - 0x18, r->ecx);
    set_high8(&r->eax, 0x1);
    r->edx = rd32(r, r->ebp + 0x1c);
    wr8(r, r->ebp - 0xc, ((r->eax >> 8) & 0xff));
    if (r->edx > 0x2)
    {
        goto at_4270cf;
    }
at_4270c4:
    r->eax = 0;
    r->edi = rd32(r, r->ebp - 0x8);
    r->esi = rd32(r, r->ebp - 0x4);
    return;
at_4270cf:
    r->ebx = 0x5;
    r->eax = r->ebp - 0x40;
    r->edx = 0;
    call_keep(r, 0x4eb5c0);
    r->ebx = 0x5;
    r->eax = r->ebp - 0x48;
    r->edx = 0;
    r->ecx = 0x41;
    call_keep(r, 0x4eb5c0);
    r->eax = rd32(r, r->ebp - 0x30);
    r->edi = r->ebp - 0x8c;
    r->eax = r->eax + 0x184;
    r->ebx = r->ebp - 0x38;
    r->esi = r->eax;
    wr32(r, r->ebp - 0x28, r->eax);
    push(r, r->edi);
    r->eax = r->ecx;
    r->ecx = r->ecx >> 0x2;
    rep_movs(r, 4);
    set_low8(&r->ecx, (r->eax & 0xff));
    set_low8(&r->ecx, (r->ecx & 0xff) & 0x3);
    rep_movs(r, 1);
    r->edi = pop(r);
    r->ecx = rd32(r, r->ebp + 0x18);
    r->edx = r->ebp - 0x8c;
    push(r, r->ecx);
    r->eax = rd32(r, r->ebp - 0x30);
    r->ecx = rd32(r, r->ebp + 0x14);
    call(r, 0x4261b0, 1);
    r->ebx = 0;
    r->eax = rd32(r, r->ebp - 0x28);
    wr32(r, r->ebp - 0x1c, r->ebx);
    wr32(r, r->ebp - 0x24, r->eax);
    wr32(r, r->ebp - 0x14, r->ebx);
at_42713b:
    r->eax = rd32(r, r->ebp - 0x1c);
    if ((uint8_t)rd8(r, r->eax + r->ebp - 0x38) == (uint8_t)0x0)
    {
        goto at_427315;
    }
    r->ecx = 0x41;
    r->esi = rd32(r, r->ebp - 0x24);
    r->edi = r->ebp - 0x8c;
    r->edx = rd32(r, r->ebp - 0x14);
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
    set_low8(&r->ebx, rd8(r, r->edx + r->ebp - 0x8c));
    r->eax = r->edx;
    if ((uint8_t)((r->ebx & 0xff)) == (uint8_t)0xff)
    {
        goto at_42718f;
    }
at_42717f:
    r->esi = r->esi - 1;
    r->eax = r->eax - 1;
    if ((int32_t)r->esi < 0)
    {
        goto at_42718f;
    }
    if ((uint8_t)rd8(r, r->eax + r->ebp - 0x8c) != (uint8_t)0xff && !r->port->env.failed)
    {
        goto at_42717f;
    }
at_42718f:
    if ((int32_t)r->esi <= (int32_t)0xffffffffu)
    {
        goto at_427315;
    }
    r->eax = rd32(r, r->ebp - 0x14);
    r->eax = r->eax + r->esi;
    set_low8(&r->edx, rd8(r, r->ebp - 0x18));
    wr8(r, r->eax + r->ebp - 0x8c, (r->edx & 0xff));
    if ((int32_t)r->esi <= 0)
    {
        goto at_4271b5;
    }
    set_low8(&r->edx, rd8(r, r->ebp - 0x20));
    wr8(r, r->eax + r->ebp - 0x8d, (r->edx & 0xff));
at_4271b5:
    if ((int32_t)r->esi <= (int32_t)0x1)
    {
        goto at_4271c9;
    }
    r->eax = rd32(r, r->ebp - 0x14);
    r->eax = r->eax + r->esi;
    set_low8(&r->edx, rd8(r, r->ebp - 0x2c));
    wr8(r, r->eax + r->ebp - 0x8e, (r->edx & 0xff));
at_4271c9:
    r->eax = r->ebp - 0x10;
    r->edx = 0;
    r->ebx = 0;
    r->ecx = 0;
    set_low8(&r->ebx, rd8(r, r->ebp + 0x10));
    wr16(r, r->ebp - 0x10, (r->edx & 0xffff));
    push(r, r->eax);
    r->edx = r->ebp - 0x190;
    r->eax = r->ebp - 0x8c;
    call(r, 0x434ee0, 1);
    if (r->eax != 0x1)
    {
        goto at_427216;
    }
    r->edx = rd32(r, r->ebp - 0x1c);
    r->eax = 0;
    set_low8(&r->eax, rd8(r, r->edx + r->ebp - 0x40));
    r->edx = 0;
    set_low8(&r->ecx, 0);
    set_low16(&r->edx, rd16(r, r->ebp - 0x10));
    wr8(r, r->ebp - 0xc, (r->ecx & 0xff));
    if ((int32_t)r->edx <= (int32_t)r->eax)
    {
        goto at_427216;
    }
    r->edx = rd32(r, r->ebp - 0x1c);
    set_low8(&r->eax, rd8(r, r->ebp - 0x10));
    wr8(r, r->edx + r->ebp - 0x40, (r->eax & 0xff));
    wr8(r, r->edx + r->ebp - 0x48, (r->ecx & 0xff));
at_427216:
    r->eax = rd32(r, r->ebp - 0x14);
    r->eax = r->eax + r->esi;
    set_low8(&r->edx, rd8(r, r->ebp - 0x2c));
    wr8(r, r->eax + r->ebp - 0x8c, (r->edx & 0xff));
    if ((int32_t)r->esi <= 0)
    {
        goto at_427233;
    }
    set_low8(&r->edx, rd8(r, r->ebp - 0x18));
    wr8(r, r->eax + r->ebp - 0x8d, (r->edx & 0xff));
at_427233:
    if ((int32_t)r->esi <= (int32_t)0x1)
    {
        goto at_427247;
    }
    r->eax = rd32(r, r->ebp - 0x14);
    r->eax = r->eax + r->esi;
    set_low8(&r->edx, rd8(r, r->ebp - 0x20));
    wr8(r, r->eax + r->ebp - 0x8e, (r->edx & 0xff));
at_427247:
    r->eax = r->ebp - 0x10;
    r->edx = r->ebp - 0x190;
    r->ebx = 0;
    r->ecx = 0;
    wr16(r, r->ebp - 0x10, (r->ebx & 0xffff));
    push(r, r->eax);
    r->ebx = 0;
    r->eax = r->ebp - 0x8c;
    set_low8(&r->ebx, rd8(r, r->ebp + 0x10));
    call(r, 0x434ee0, 1);
    if (r->eax != 0x1)
    {
        goto at_427297;
    }
    set_low8(&r->eax, 0);
    wr8(r, r->ebp - 0xc, (r->eax & 0xff));
    r->eax = rd32(r, r->ebp - 0x1c);
    r->edx = 0;
    set_low8(&r->edx, rd8(r, r->eax + r->ebp - 0x40));
    r->eax = 0;
    set_low16(&r->eax, rd16(r, r->ebp - 0x10));
    if ((int32_t)r->eax <= (int32_t)r->edx)
    {
        goto at_427297;
    }
    r->edx = rd32(r, r->ebp - 0x1c);
    set_low8(&r->eax, rd8(r, r->ebp - 0x10));
    wr8(r, r->edx + r->ebp - 0x40, (r->eax & 0xff));
    r->eax = r->edx;
    wr8(r, r->eax + r->ebp - 0x48, 0x1);
at_427297:
    r->eax = rd32(r, r->ebp - 0x14);
    r->eax = r->eax + r->esi;
    set_low8(&r->edx, rd8(r, r->ebp - 0x20));
    wr8(r, r->eax + r->ebp - 0x8c, (r->edx & 0xff));
    if ((int32_t)r->esi <= 0)
    {
        goto at_4272b4;
    }
    set_low8(&r->edx, rd8(r, r->ebp - 0x2c));
    wr8(r, r->eax + r->ebp - 0x8d, (r->edx & 0xff));
at_4272b4:
    if ((int32_t)r->esi <= (int32_t)0x1)
    {
        goto at_4272c6;
    }
    r->esi = r->esi + rd32(r, r->ebp - 0x14);
    set_low8(&r->eax, rd8(r, r->ebp - 0x18));
    wr8(r, r->esi + r->ebp - 0x8e, (r->eax & 0xff));
at_4272c6:
    r->eax = r->ebp - 0x10;
    r->edx = r->ebp - 0x190;
    r->ebx = 0;
    r->ecx = 0;
    set_low8(&r->ebx, rd8(r, r->ebp + 0x10));
    wr16(r, r->ebp - 0x10, (r->ecx & 0xffff));
    push(r, r->eax);
    r->eax = r->ebp - 0x8c;
    r->ecx = 0;
    call(r, 0x434ee0, 1);
    if (r->eax != 0x1)
    {
        goto at_427315;
    }
    set_high8(&r->edx, 0);
    wr8(r, r->ebp - 0xc, ((r->edx >> 8) & 0xff));
    r->edx = rd32(r, r->ebp - 0x1c);
    r->eax = 0;
    set_low8(&r->eax, rd8(r, r->edx + r->ebp - 0x40));
    r->edx = 0;
    set_low16(&r->edx, rd16(r, r->ebp - 0x10));
    if ((int32_t)r->edx <= (int32_t)r->eax)
    {
        goto at_427315;
    }
    r->edx = rd32(r, r->ebp - 0x1c);
    set_low8(&r->eax, rd8(r, r->ebp - 0x10));
    set_low8(&r->ebx, 0x2);
    wr8(r, r->edx + r->ebp - 0x40, (r->eax & 0xff));
    wr8(r, r->edx + r->ebp - 0x48, (r->ebx & 0xff));
at_427315:
    r->eax = rd32(r, r->ebp - 0x14);
    r->edx = rd32(r, r->ebp - 0x1c);
    r->eax = r->eax + 0xd;
    r->edx = r->edx + 1;
    wr32(r, r->ebp - 0x14, r->eax);
    wr32(r, r->ebp - 0x1c, r->edx);
    if ((int32_t)r->edx < (int32_t)0x5 && !r->port->env.failed)
    {
        goto at_42713b;
    }
    if ((uint8_t)rd8(r, r->ebp - 0xc) != (uint8_t)0x0)
    {
        goto at_42735d;
    }
    r->eax = 0x1;
    r->edx = 0;
at_42733b:
    set_low8(&r->ebx, rd8(r, r->eax + r->ebp - 0x40));
    if ((uint8_t)((r->ebx & 0xff)) <= (uint8_t)rd8(r, r->edx + r->ebp - 0x40))
    {
        goto at_427347;
    }
    r->edx = r->eax;
at_427347:
    r->eax = r->eax + 1;
    if ((int32_t)r->eax < (int32_t)0x5 && !r->port->env.failed)
    {
        goto at_42733b;
    }
    r->eax = rd32(r, r->ebp + 0xc);
    wr32(r, r->eax, r->edx);
    r->eax = 0;
    set_low8(&r->eax, rd8(r, r->edx + r->ebp - 0x48));
    r->edx = rd32(r, r->ebp + 0x8);
    wr32(r, r->edx, r->eax);
at_42735d:
    if ((uint8_t)rd8(r, r->ebp - 0xc) != (uint8_t)0x0 && !r->port->env.failed)
    {
        goto at_4270c4;
    }
    r->eax = 0x1;
    r->edi = rd32(r, r->ebp - 0x8);
    r->esi = rd32(r, r->ebp - 0x4);
    return;
}

uint32_t vertrix_port_ai_search_4270a0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x194
    };
    Port port;
    uint8_t stack[BELOW + 8 + 4 * 6];
    Regs r;
    port_open_arguments(&port, stack, calls, services, globals, entry, BELOW, 6);
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
