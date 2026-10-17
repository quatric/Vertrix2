#include "port_rtlboardmatches.h"

/* Resolves matches after a piece locks: takes a kind snapshot, runs the line pass (0x4346b0) and
 * the figure pass (0x434ee0), clears the matched cells and spawns the match effects and bursts. */

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

static void set_low16(uint32_t *reg, uint32_t value)
{
    *reg = (*reg & 0xffff0000u) | (value & 0xffff);
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

/* Original 0x432480: Resolves matches after a piece locks: takes a kind snapshot, runs the line
 * pass (0x4346b0) and the figure pass (0x434ee0), clears the matched cells and spawns the match
 * effects and bursts. Evidence: calls 0x4327e0, 0x432840, 0x434ee0, 0x4346b0, 0x4ac7b0, 0x4ac8f0,
 * 0x430190, 0x4302a0; reads 0x532a70. Register-for-register from the listing (0x432488..0x4327d4);
 * labels are the original addresses. */
static void run(Regs *r)
{
    wr32(r, r->ebp - 0x24, r->eax);
    wr32(r, r->ebp - 0x2c, r->edx);
    wr32(r, r->ebp - 0x5c, r->ebx);
    wr8(r, r->ebp - 0xc, (r->ecx & 0xff));
    r->eax = rd32(r, r->ebp - 0x2c);
    r->edi = 0x5407b8;
    r->edx = 0;
    wr8(r, r->ebp - 0x10, (r->ecx & 0xff));
    wr32(r, r->ebp - 0x14, r->edx);
    r->edx = 0;
    r->ecx = 0x41;
    wr32(r, r->ebp - 0x58, r->edx);
    wr32(r, r->eax, r->edx);
    r->eax = rd32(r, r->ebp - 0x24);
    wr32(r, r->ebx, r->edx);
    r->eax = r->eax + 0x1de;
    r->ebx = 0x41;
    wr32(r, r->ebp - 0x60, r->eax);
    r->eax = rd32(r, r->ebp - 0x24);
    r->edx = rd32(r, r->ebp - 0x60);
    r->eax = r->eax + 0x220;
    r->esi = rd32(r, r->ebp - 0x60);
    call_keep(r, 0x4327e0);
    push(r, r->edi);
    r->eax = r->ecx;
    r->ecx = r->ecx >> 0x2;
    rep_movs(r, 4);
    set_low8(&r->ecx, (r->eax & 0xff));
    set_low8(&r->ecx, (r->ecx & 0xff) & 0x3);
    rep_movs(r, 1);
    r->edi = pop(r);
    r->eax = 0x5406b0;
    call_keep(r, 0x432840);
    r->eax = rd32(r, r->ebp + 0x8);
    wr32(r, r->eax, 0x0);
    r->eax = rd32(r, r->ebp + 0xc);
    r->ecx = 0x1;
    r->edx = 0x5406b0;
    wr32(r, r->eax, 0x0);
    r->eax = r->ebp - 0x14;
    r->ebx = 0;
    push(r, r->eax);
    set_low8(&r->ebx, rd8(r, r->ebp - 0xc));
    r->eax = rd32(r, r->ebp - 0x60);
    call(r, 0x434ee0, 1);
    if (r->eax != 0x1)
    {
        goto at_43253b;
    }
    r->eax = rd32(r, r->ebp + 0x8);
    r->ecx = 0x1;
    wr32(r, r->eax, 0x1);
    r->eax = rd32(r, r->ebp + 0xc);
    wr32(r, r->ebp - 0x58, r->ecx);
    wr32(r, r->eax, 0x1);
at_43253b:
    r->ecx = r->ebp - 0x14;
    r->edx = 0x5406b0;
    r->ebx = 0;
    r->eax = 0x5407b8;
    set_low8(&r->ebx, rd8(r, r->ebp - 0x10));
    call_keep(r, 0x4346b0);
    if (r->eax == 0x1)
    {
        goto at_43277c;
    }
at_43255b:
    r->esi = 0;
    r->eax = rd32(r, r->ebp - 0x24);
    wr32(r, r->ebp - 0x40, r->esi);
    wr32(r, r->ebp - 0x48, r->esi);
    wr32(r, r->ebp - 0x50, r->eax);
    wr32(r, r->ebp - 0x44, r->eax);
at_43256c:
    r->eax = rd32(r, r->ebp - 0x44);
    r->edx = rd32(r, r->ebp - 0x48);
    wr32(r, r->ebp - 0x3c, r->eax);
    r->eax = r->edx * 0x34;
    wr32(r, r->ebp - 0x30, r->eax);
    r->eax = rd32(r, r->ebp - 0x44);
    wr32(r, r->ebp - 0x64, r->eax);
    r->eax = r->eax + 0x10;
    r->edi = 0;
    wr32(r, r->ebp - 0x20, r->eax);
    r->eax = rd32(r, r->ebp - 0x50);
    r->esi = 0;
    wr32(r, r->ebp - 0x34, r->eax);
at_432591:
    r->eax = rd32(r, r->ebp - 0x64);
    if (rd32(r, r->eax + 0x324) == 0x0)
    {
        goto at_4325f7;
    }
    r->eax = rd32(r, r->ebp - 0x34);
    if (rd32(r, r->esi + r->eax + 0x220) != 0x0)
    {
        goto at_432792;
    }
at_4325ae:
    r->ecx = 0x1;
    r->eax = r->edi;
    wr32(r, r->ebp - 0x40, r->ecx);
    r->eax = r->eax << 0x4;
    r->ecx = rd32(r, r->ebp - 0x3c);
    r->ebx = rd32(r, r->ebp - 0x20);
    r->ecx = r->ecx + r->eax;
at_4325c3:
    r->edx = 0x1;
    r->eax = rd32(r, r->ecx + 0x324);
    call_keep(r, 0x4ac7b0);
    r->eax = rd32(r, r->ecx + 0x324);
    wr8(r, r->eax + 0x15d, 0x1);
    r->edx = 0x4504e0;
    r->eax = rd32(r, r->ecx + 0x324);
    r->ecx = r->ecx + 0x4;
    call_keep(r, 0x4ac8f0);
    if (r->ecx != r->ebx && !r->port->env.failed)
    {
        goto at_4325c3;
    }
at_4325f7:
    r->ebx = rd32(r, r->ebp - 0x64);
    r->eax = rd32(r, r->ebp - 0x20);
    r->esi = r->esi + 0x4;
    r->edi = r->edi + 1;
    r->ebx = r->ebx + 0x10;
    r->eax = r->eax + 0x10;
    wr32(r, r->ebp - 0x64, r->ebx);
    wr32(r, r->ebp - 0x20, r->eax);
    if (r->edi < 0xd && !r->port->env.failed)
    {
        goto at_432591;
    }
    r->edx = rd32(r, r->ebp - 0x50);
    r->ecx = rd32(r, r->ebp - 0x44);
    r->ebx = rd32(r, r->ebp - 0x48);
    r->edx = r->edx + 0x34;
    r->ecx = r->ecx + 0xd0;
    r->ebx = r->ebx + 1;
    wr32(r, r->ebp - 0x50, r->edx);
    wr32(r, r->ebp - 0x44, r->ecx);
    wr32(r, r->ebp - 0x48, r->ebx);
    if (r->ebx < 0x5 && !r->port->env.failed)
    {
        goto at_43256c;
    }
    r->edi = rd32(r, r->ebp - 0x40);
    if (r->edi != 0x1)
    {
        goto at_4327a5;
    }
    wr32(r, r->ebp - 0x58, r->edi);
at_43264a:
    r->eax = 0;
    r->edx = rd32(r, r->ebp - 0x5c);
    set_low16(&r->eax, rd16(r, r->ebp - 0x14));
    r->ecx = 0;
    wr32(r, r->edx, r->eax);
    r->eax = rd32(r, r->ebp - 0x24);
    wr32(r, r->ebp - 0x28, r->ecx);
    wr32(r, r->ebp - 0x54, r->eax);
    wr32(r, r->ebp - 0x4c, r->eax);
at_432663:
    r->ebx = rd32(r, r->ebp - 0x28);
    r->eax = r->ebx * 0x34;
    wr32(r, r->ebp - 0x68, r->eax);
    r->eax = rd32(r, r->ebp - 0x54);
    wr32(r, r->ebp - 0x18, r->eax);
    r->eax = rd32(r, r->ebp - 0x4c);
    r->ecx = 0;
    wr32(r, r->ebp - 0x1c, r->eax);
    wr32(r, r->ebp - 0x38, r->eax);
at_43267d:
    r->esi = rd32(r, r->ebp - 0x38);
    r->eax = r->ecx * 4;
    r->esi = r->esi + r->eax;
    if (rd32(r, r->esi + 0x220) == 0x0)
    {
        goto at_432734;
    }
    r->eax = r->eax + rd32(r, r->ebp - 0x68);
    r->ebx = rd32(r, r->eax + 0x5406b0);
    if (r->ebx != 0x1)
    {
        goto at_432734;
    }
    r->eax = rd32(r, r->ebp - 0x2c);
    wr32(r, r->eax, rd32(r, r->eax) + r->ebx);
    r->edx = r->ebx;
    r->eax = rd32(r, r->esi + 0x220);
    call_keep(r, 0x4ac7b0);
    r->eax = rd32(r, r->esi + 0x220);
    wr8(r, r->eax + 0x15d, 0x1);
    r->eax = rd32(r, r->ebp - 0x18);
    r->edx = rd32(r, r->esi + 0x220);
    set_low8(&r->eax, rd8(r, r->eax + 0x1de));
    wr8(r, r->edx + 0x15c, (r->eax & 0xff));
    r->eax = rd32(r, r->ebp - 0x18);
    if ((uint8_t)rd8(r, r->eax + 0x1de) != (uint8_t)0x7)
    {
        goto at_4327bb;
    }
    r->eax = rd32(r, r->ebp - 0x2a);
    r->edi = (uint32_t)(int32_t)(int16_t)(r->ecx & 0xffff);
    r->eax = (uint32_t)((int32_t)r->eax >> 0x10);
    r->ebx = r->edi;
    wr32(r, r->ebp - 0x60, r->eax);
    r->edx = r->eax;
    r->eax = rd32(r, r->ebp - 0x24);
    call_keep(r, 0x430190);
    r->edx = 0x450450;
    wr32(r, r->esi + 0xbdc, r->eax);
    call_keep(r, 0x4ac8f0);
    r->ebx = r->edi;
    r->edx = rd32(r, r->ebp - 0x60);
    r->eax = rd32(r, r->ebp - 0x24);
    call_keep(r, 0x4302a0);
at_432721:
    r->eax = rd32(r, r->ebp - 0x1c);
    r->edx = 0x450330;
    r->eax = rd32(r, r->eax + 0x220);
    call_keep(r, 0x4ac8f0);
at_432734:
    r->eax = rd32(r, r->ebp - 0x18);
    r->edx = rd32(r, r->ebp - 0x1c);
    r->ecx = r->ecx + 1;
    r->eax = r->eax + 1;
    r->edx = r->edx + 0x4;
    wr32(r, r->ebp - 0x18, r->eax);
    wr32(r, r->ebp - 0x1c, r->edx);
    if (r->ecx < 0xd && !r->port->env.failed)
    {
        goto at_43267d;
    }
    r->ecx = rd32(r, r->ebp - 0x54);
    r->ebx = rd32(r, r->ebp - 0x4c);
    r->esi = rd32(r, r->ebp - 0x28);
    r->ecx = r->ecx + 0xd;
    r->ebx = r->ebx + 0x34;
    r->esi = r->esi + 1;
    wr32(r, r->ebp - 0x54, r->ecx);
    wr32(r, r->ebp - 0x4c, r->ebx);
    wr32(r, r->ebp - 0x28, r->esi);
    if (r->esi < 0x5 && !r->port->env.failed)
    {
        goto at_432663;
    }
    r->eax = rd32(r, r->ebp - 0x58);
    r->edi = rd32(r, r->ebp - 0x8);
    r->esi = rd32(r, r->ebp - 0x4);
    return;
at_43277c:
    r->ebx = 0x1;
    r->eax = rd32(r, r->ebp + 0x8);
    wr32(r, r->ebp - 0x58, r->ebx);
    wr32(r, r->eax, 0x1);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_43255b;
at_432792:
    r->eax = rd32(r, r->ebp - 0x30);
    wr32(r, r->esi + r->eax + 0x5406b0, 0x1);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4325ae;
at_4327a5:
    if (rd32(r, r->ebp - 0x58) == 0x1 && !r->port->env.failed)
    {
        goto at_43264a;
    }
    r->eax = rd32(r, r->ebp - 0x58);
    r->edi = rd32(r, r->ebp - 0x8);
    r->esi = rd32(r, r->ebp - 0x4);
    return;
at_4327bb:
    r->edx = rd32(r, r->ebp - 0x2a);
    r->eax = rd32(r, r->ebp - 0x24);
    r->esi = rd32(r, 0x532a70);
    r->ebx = (uint32_t)(int32_t)(int16_t)(r->ecx & 0xffff);
    r->edx = (uint32_t)((int32_t)r->edx >> 0x10);
    call_all(r, rd32(r, r->esi * 4 + 0x4fb7b0));
    if (r->port->env.failed)
    {
        return;
    }
    goto at_432721;
}

uint32_t vertrix_port_board_match_resolve_432480(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x6c
    };
    Port port;
    uint8_t stack[BELOW + 8 + 4 * 2];
    Regs r;
    port_open_arguments(&port, stack, calls, services, globals, entry, BELOW, 2);
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
