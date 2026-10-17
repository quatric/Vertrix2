#include "port_rtlextendedeffects.h"

/* Applies a module row's extended (Exx) effect: the high nibble of the effect byte at +4 picks the
 * case through the table at 0x40d500, for example a fine volume or period slide that is skipped
 * while [0x531b4c] is set. */

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

static void set_high8(uint32_t *reg, uint32_t value)
{
    *reg = (*reg & 0xffff00ffu) | ((value & 0xff) << 8);
}

/* idiv and div of edx:eax as the original's (a zero divisor or an overflowing quotient leaves
 * both registers). */
static void idiv32(Regs *r, uint32_t value)
{
    LiftFlags flags;
    memset(&flags, 0, sizeof flags);
    lift_idiv1(32, value, &r->eax, &r->edx, &flags);
}

/* The emulated stack of a routine without a frame pointer: pushes and pops move esp. */
static void push_mem(Regs *r, uint32_t value)
{
    r->esp -= 4;
    wr32(r, r->esp, value);
}

static uint32_t pop_mem(Regs *r)
{
    uint32_t value = rd32(r, r->esp);
    r->esp += 4;
    return value;
}

/* A call taking count stack arguments from esp up; the callee pops them unless kept (cdecl). */
static void call_mem_with(Regs *r, uint32_t target, unsigned count, int keep)
{
    uint32_t args[32] = {0};
    unsigned i;
    for (i = 0; i < count && i < 32; i++)
    {
        args[i] = rd32(r, r->esp + 4 * i);
    }
    vertrix_lift_in_esi = r->esi;
    vertrix_lift_in_edi = r->edi;
    vertrix_lift_in_ebp = r->ebp;
    r->eax =
        lift_call_arguments(&r->port->env, target, r->eax, r->edx, r->ebx, r->ecx, args, count);
    vertrix_lift_in_esi = vertrix_lift_in_edi = vertrix_lift_in_ebp = 0;
    r->edx = vertrix_lift_edx;
    if (!keep)
    {
        r->esp += 4 * count;
    }
}

static void call_mem_keep(Regs *r, uint32_t target, unsigned count)
{
    call_mem_with(r, target, count, 1);
}

/* Original 0x40d540: Applies a module row's extended (Exx) effect: the high nibble of the effect
 * byte at +4 picks the case through the table at 0x40d500, for example a fine volume or period
 * slide that is skipped while [0x531b4c] is set. Evidence: calls 0x40ce80, 0x40e670; reads
 * 0x531b4c, 0x531b5c, 0x531b50, 0x531b44; writes 0x531b74, 0x531b70, 0x531b44, 0x531b78.
 * Register-for-register from the listing (0x40d540..0x40d877); labels are the original addresses.
 */
static void run(Regs *r)
{
    push_mem(r, r->ebx);
    push_mem(r, r->ecx);
    push_mem(r, r->edx);
    push_mem(r, r->edi);
    r->ecx = r->eax;
    r->eax = 0;
    set_low8(&r->eax, rd8(r, r->ecx + 0x4));
    r->eax = (uint32_t)((int32_t)r->eax >> 0x4);
    if (r->eax > 0xf)
    {
        goto at_40d55a;
    }
    switch (r->eax)
    {
        case 0:
            goto at_40d55a;
        case 1:
            goto at_40d55f;
        case 2:
            goto at_40d5a4;
        case 3:
            goto at_40d5ec;
        case 4:
            goto at_40d606;
        case 5:
            goto at_40d62d;
        case 6:
            goto at_40d66a;
        case 7:
            goto at_40d6e0;
        case 8:
            goto at_40d70a;
        case 9:
            goto at_40d730;
        case 10:
            goto at_40d76d;
        case 11:
            goto at_40d7a7;
        case 12:
            goto at_40d7ec;
        case 13:
            goto at_40d818;
        case 14:
            goto at_40d842;
        case 15:
            goto at_40d55a;
        default:
            r->port->env.failed = 1;
            return;
    }
at_40d55a:
    r->edi = pop_mem(r);
    r->edx = pop_mem(r);
    r->ecx = pop_mem(r);
    r->ebx = pop_mem(r);
    return;
at_40d55f:
    if (rd32(r, 0x531b4c) != 0x0 && !r->port->env.failed)
    {
        goto at_40d55a;
    }
    set_high8(&r->eax, rd8(r, r->ecx + 0x4));
    if ((uint8_t)(((r->eax >> 8) & 0xff) & 0xf) != 0)
    {
        goto at_40d598;
    }
at_40d570:
    r->eax = 0;
    set_low8(&r->eax, rd8(r, r->ecx + 0x6a));
    r->edx = rd32(r, r->ecx + 0x24);
    r->edx = r->edx - r->eax;
    wr32(r, r->ecx + 0x24, r->edx);
    if ((int32_t)r->edx >= (int32_t)0x1)
    {
        goto at_40d589;
    }
    wr32(r, r->ecx + 0x24, 0x1);
at_40d589:
    r->eax = rd32(r, r->ecx + 0x24);
    wr32(r, r->ecx + 0x28, r->eax);
    wr8(r, r->ecx + 0x1, rd8(r, r->ecx + 0x1) | 0x1);
    r->edi = pop_mem(r);
    r->edx = pop_mem(r);
    r->ecx = pop_mem(r);
    r->ebx = pop_mem(r);
    return;
at_40d598:
    set_low8(&r->eax, ((r->eax >> 8) & 0xff));
    set_low8(&r->eax, (r->eax & 0xff) & 0xf);
    set_low8(&r->eax, (r->eax & 0xff) << 0x2);
    wr8(r, r->ecx + 0x6a, (r->eax & 0xff));
    if (r->port->env.failed)
    {
        return;
    }
    goto at_40d570;
at_40d5a4:
    if (rd32(r, 0x531b4c) != 0x0 && !r->port->env.failed)
    {
        goto at_40d55a;
    }
    set_high8(&r->ebx, rd8(r, r->ecx + 0x4));
    if ((uint8_t)(((r->ebx >> 8) & 0xff) & 0xf) != 0)
    {
        goto at_40d5e0;
    }
at_40d5b5:
    r->eax = 0;
    set_low8(&r->eax, rd8(r, r->ecx + 0x6b));
    r->ebx = rd32(r, r->ecx + 0x24);
    r->ebx = r->ebx + r->eax;
    wr32(r, r->ecx + 0x24, r->ebx);
    if ((int32_t)r->ebx <= (int32_t)0x7cff)
    {
        goto at_40d5d1;
    }
    wr32(r, r->ecx + 0x24, 0x7cff);
at_40d5d1:
    r->eax = rd32(r, r->ecx + 0x24);
    wr32(r, r->ecx + 0x28, r->eax);
    wr8(r, r->ecx + 0x1, rd8(r, r->ecx + 0x1) | 0x1);
    r->edi = pop_mem(r);
    r->edx = pop_mem(r);
    r->ecx = pop_mem(r);
    r->ebx = pop_mem(r);
    return;
at_40d5e0:
    set_low8(&r->eax, ((r->ebx >> 8) & 0xff));
    set_low8(&r->eax, (r->eax & 0xff) & 0xf);
    set_low8(&r->eax, (r->eax & 0xff) << 0x2);
    wr8(r, r->ecx + 0x6b, (r->eax & 0xff));
    if (r->port->env.failed)
    {
        return;
    }
    goto at_40d5b5;
at_40d5ec:
    if (rd32(r, 0x531b4c) != 0x0 && !r->port->env.failed)
    {
        goto at_40d55a;
    }
    set_low8(&r->eax, rd8(r, r->ecx + 0x4));
    set_low8(&r->eax, (r->eax & 0xff) & 0xf);
    wr8(r, r->ecx + 0x3d, (r->eax & 0xff));
    r->edi = pop_mem(r);
    r->edx = pop_mem(r);
    r->ecx = pop_mem(r);
    r->ebx = pop_mem(r);
    return;
at_40d606:
    if (rd32(r, 0x531b4c) != 0x0 && !r->port->env.failed)
    {
        goto at_40d55a;
    }
    set_high8(&r->edx, rd8(r, r->ecx + 0x3c));
    set_high8(&r->edx, ((r->edx >> 8) & 0xff) & 0xf0);
    wr8(r, r->ecx + 0x3c, ((r->edx >> 8) & 0xff));
    set_low8(&r->eax, rd8(r, r->ecx + 0x4));
    set_low8(&r->eax, (r->eax & 0xff) & 0xf);
    set_low8(&r->ebx, ((r->edx >> 8) & 0xff));
    set_low8(&r->ebx, (r->ebx & 0xff) | (r->eax & 0xff));
    wr8(r, r->ecx + 0x3c, (r->ebx & 0xff));
    r->edi = pop_mem(r);
    r->edx = pop_mem(r);
    r->ecx = pop_mem(r);
    r->ebx = pop_mem(r);
    return;
at_40d62d:
    if (rd32(r, 0x531b4c) != 0x0 && !r->port->env.failed)
    {
        goto at_40d55a;
    }
    set_low8(&r->eax, rd8(r, r->ecx + 0x4));
    set_low8(&r->eax, (r->eax & 0xff) & 0xf);
    r->eax = r->eax & 0xff;
    r->eax = r->eax << 0x4;
    r->eax = r->eax - 0x80;
    wr32(r, r->ecx + 0x8, r->eax);
    r->ebx = r->eax;
    r->edx = rd32(r, r->ecx + 0xc);
    r->eax = 0;
    set_low8(&r->eax, rd8(r, r->ecx + 0x7));
    call_mem_keep(r, 0x40ce80, 8);
    wr32(r, r->ecx + 0x28, r->eax);
    wr8(r, r->ecx + 0x1, rd8(r, r->ecx + 0x1) | 0x1);
    r->edi = pop_mem(r);
    r->edx = pop_mem(r);
    r->ecx = pop_mem(r);
    r->ebx = pop_mem(r);
    return;
at_40d66a:
    if (rd32(r, 0x531b4c) != 0x0 && !r->port->env.failed)
    {
        goto at_40d55a;
    }
    if ((uint8_t)(rd8(r, r->ecx + 0x4) & 0xf) == 0)
    {
        goto at_40d6d0;
    }
    r->eax = rd32(r, r->ecx + 0xb0);
    if (r->eax != 0)
    {
        goto at_40d6c5;
    }
    set_low8(&r->eax, rd8(r, r->ecx + 0x4));
    set_low8(&r->eax, (r->eax & 0xff) & 0xf);
    r->eax = r->eax & 0xff;
    wr32(r, r->ecx + 0xb0, r->eax);
at_40d697:
    if (rd32(r, r->ecx + 0xb0) == 0x0 && !r->port->env.failed)
    {
        goto at_40d55a;
    }
    r->eax = rd32(r, r->ecx + 0xac);
    wr32(r, 0x531b74, r->eax);
    r->eax = rd32(r, 0x531b5c);
    wr32(r, 0x531b70, r->eax);
    wr8(r, 0x531b44, rd8(r, 0x531b44) | 0x1);
    r->edi = pop_mem(r);
    r->edx = pop_mem(r);
    r->ecx = pop_mem(r);
    r->ebx = pop_mem(r);
    return;
at_40d6c5:
    r->edx = r->eax - 0x1;
    wr32(r, r->ecx + 0xb0, r->edx);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_40d697;
at_40d6d0:
    r->eax = rd32(r, 0x531b50);
    wr32(r, r->ecx + 0xac, r->eax);
    r->edi = pop_mem(r);
    r->edx = pop_mem(r);
    r->ecx = pop_mem(r);
    r->ebx = pop_mem(r);
    return;
at_40d6e0:
    if (rd32(r, 0x531b4c) != 0x0 && !r->port->env.failed)
    {
        goto at_40d55a;
    }
    set_low8(&r->ebx, rd8(r, r->ecx + 0x3c));
    set_low8(&r->ebx, (r->ebx & 0xff) & 0xf);
    wr8(r, r->ecx + 0x3c, (r->ebx & 0xff));
    set_low8(&r->eax, rd8(r, r->ecx + 0x4));
    set_low8(&r->eax, (r->eax & 0xff) & 0xf);
    set_low8(&r->eax, (r->eax & 0xff) << 0x4);
    set_high8(&r->ebx, (r->ebx & 0xff));
    set_high8(&r->ebx, ((r->ebx >> 8) & 0xff) | (r->eax & 0xff));
    wr8(r, r->ecx + 0x3c, ((r->ebx >> 8) & 0xff));
    r->edi = pop_mem(r);
    r->edx = pop_mem(r);
    r->ecx = pop_mem(r);
    r->ebx = pop_mem(r);
    return;
at_40d70a:
    if (rd32(r, 0x531b4c) != 0x0 && !r->port->env.failed)
    {
        goto at_40d55a;
    }
    set_low8(&r->eax, rd8(r, r->ecx + 0x4));
    set_low8(&r->eax, (r->eax & 0xff) & 0xf);
    r->eax = r->eax & 0xff;
    r->eax = r->eax << 0x4;
    wr32(r, r->ecx + 0x1c, r->eax);
    wr8(r, r->ecx + 0x1, rd8(r, r->ecx + 0x1) | 0x4);
    r->edi = pop_mem(r);
    r->edx = pop_mem(r);
    r->ecx = pop_mem(r);
    r->ebx = pop_mem(r);
    return;
at_40d730:
    if (rd32(r, 0x531b4c) == 0x0)
    {
        goto at_40d761;
    }
    set_low8(&r->edx, rd8(r, r->ecx + 0x4));
    if ((uint8_t)((r->edx & 0xff) & 0xf) == 0 && !r->port->env.failed)
    {
        goto at_40d55a;
    }
    set_low8(&r->eax, (r->edx & 0xff));
    set_low8(&r->eax, (r->eax & 0xff) & 0xf);
    r->ebx = 0;
    set_low8(&r->ebx, (r->eax & 0xff));
    r->eax = rd32(r, 0x531b4c);
    r->edx = r->eax;
    r->edx = (uint32_t)((int32_t)r->edx >> 0x1f);
    idiv32(r, r->ebx);
    if (r->edx != 0 && !r->port->env.failed)
    {
        goto at_40d55a;
    }
at_40d761:
    r->eax = r->ecx;
    call_mem_keep(r, 0x40e670, 8);
    r->edi = pop_mem(r);
    r->edx = pop_mem(r);
    r->ecx = pop_mem(r);
    r->ebx = pop_mem(r);
    return;
at_40d76d:
    if (rd32(r, 0x531b4c) != 0x0 && !r->port->env.failed)
    {
        goto at_40d55a;
    }
    set_low8(&r->eax, rd8(r, r->ecx + 0x4));
    set_low8(&r->eax, (r->eax & 0xff) & 0xf);
    r->eax = r->eax & 0xff;
    r->edi = rd32(r, r->ecx + 0x10);
    r->edi = r->edi + r->eax;
    wr32(r, r->ecx + 0x10, r->edi);
    if ((int32_t)r->edi <= (int32_t)0x40)
    {
        goto at_40d798;
    }
    wr32(r, r->ecx + 0x10, 0x40);
at_40d798:
    r->eax = rd32(r, r->ecx + 0x10);
    wr32(r, r->ecx + 0x14, r->eax);
    wr8(r, r->ecx + 0x1, rd8(r, r->ecx + 0x1) | 0x2);
    r->edi = pop_mem(r);
    r->edx = pop_mem(r);
    r->ecx = pop_mem(r);
    r->ebx = pop_mem(r);
    return;
at_40d7a7:
    r->edi = rd32(r, 0x531b4c);
    if (r->edi != 0 && !r->port->env.failed)
    {
        goto at_40d55a;
    }
    set_low8(&r->eax, rd8(r, r->ecx + 0x4));
    set_low8(&r->eax, (r->eax & 0xff) & 0xf);
    r->eax = r->eax & 0xff;
    r->edx = rd32(r, r->ecx + 0x10);
    r->edx = r->edx - r->eax;
    wr32(r, r->ecx + 0x10, r->edx);
    if ((int32_t)r->edx < 0)
    {
        goto at_40d7da;
    }
    r->eax = rd32(r, r->ecx + 0x10);
    wr32(r, r->ecx + 0x14, r->eax);
    wr8(r, r->ecx + 0x1, rd8(r, r->ecx + 0x1) | 0x2);
    r->edi = pop_mem(r);
    r->edx = pop_mem(r);
    r->ecx = pop_mem(r);
    r->ebx = pop_mem(r);
    return;
at_40d7da:
    wr32(r, r->ecx + 0x10, r->edi);
    r->eax = rd32(r, r->ecx + 0x10);
    wr32(r, r->ecx + 0x14, r->eax);
    wr8(r, r->ecx + 0x1, rd8(r, r->ecx + 0x1) | 0x2);
    r->edi = pop_mem(r);
    r->edx = pop_mem(r);
    r->ecx = pop_mem(r);
    r->ebx = pop_mem(r);
    return;
at_40d7ec:
    set_low8(&r->eax, rd8(r, r->ecx + 0x4));
    set_low8(&r->eax, (r->eax & 0xff) & 0xf);
    r->eax = r->eax & 0xff;
    if (r->eax != rd32(r, 0x531b4c) && !r->port->env.failed)
    {
        goto at_40d55a;
    }
    wr32(r, r->ecx + 0x14, 0x0);
    r->eax = rd32(r, r->ecx + 0x14);
    wr32(r, r->ecx + 0x10, r->eax);
    wr8(r, r->ecx + 0x1, rd8(r, r->ecx + 0x1) | 0x2);
    r->edi = pop_mem(r);
    r->edx = pop_mem(r);
    r->ecx = pop_mem(r);
    r->ebx = pop_mem(r);
    return;
at_40d818:
    wr8(r, r->ecx + 0x1, rd8(r, r->ecx + 0x1) & 0x10);
    set_low8(&r->eax, rd8(r, r->ecx + 0x4));
    set_low8(&r->eax, (r->eax & 0xff) & 0xf);
    r->eax = r->eax & 0xff;
    if (r->eax != rd32(r, 0x531b4c) && !r->port->env.failed)
    {
        goto at_40d55a;
    }
    r->eax = r->ecx;
    call_mem_keep(r, 0x40e670, 8);
    wr8(r, r->ecx + 0x1, rd8(r, r->ecx + 0x1) | 0x6);
    r->edi = pop_mem(r);
    r->edx = pop_mem(r);
    r->ecx = pop_mem(r);
    r->ebx = pop_mem(r);
    return;
at_40d842:
    if (rd32(r, 0x531b4c) != 0x0 && !r->port->env.failed)
    {
        goto at_40d55a;
    }
    if ((uint8_t)(rd8(r, 0x531b44) & 0x4) != 0 && !r->port->env.failed)
    {
        goto at_40d55a;
    }
    set_low8(&r->eax, rd8(r, r->ecx + 0x4));
    set_low8(&r->eax, (r->eax & 0xff) & 0xf);
    r->eax = r->eax & 0xff;
    r->eax = r->eax + 1;
    wr32(r, 0x531b78, r->eax);
    wr8(r, 0x531b44, rd8(r, 0x531b44) | 0x4);
    r->edi = pop_mem(r);
    r->edx = pop_mem(r);
    r->ecx = pop_mem(r);
    r->ebx = pop_mem(r);
    return;
}

uint32_t vertrix_port_sequence_extended_effect_40d540(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x20
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
    r.ebp = entry->ebp;
    r.esp = entry->esp;
    run(&r);
    return port_return(&port, r.eax, r.edx);
}
