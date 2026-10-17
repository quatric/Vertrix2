#include "port_rtltzrules.h"

/* Parses a time zone change rule: Jn (Julian day), Mm.w.d (month, week, day) or a day number, then
 * the time. */

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

/* Original 0x4e97b4: Parses a time zone change rule: Jn (Julian day), Mm.w.d (month, week, day) or
 * a day number, then the time. Evidence: calls 0x4e9670, 0x4e969c, 0x4e97b4; reads 0x50b0dc,
 * 0x50b0e4, 0x50afb4, 0x50afb0, 0x50afac; writes 0x50b0e0, 0x50b0e4, 0x50afb4, 0x50afb0, 0x50afac.
 * Register-for-register from the listing (0x4e97b4..0x4e9a2e); labels are the original addresses.
 */
static void run(Regs *r)
{
    push_mem(r, r->ebx);
    push_mem(r, r->ecx);
    push_mem(r, r->esi);
    r->esp = r->esp - 0x10;
    r->ebx = r->eax;
    r->ecx = r->edx;
    set_high8(&r->eax, rd8(r, r->eax));
    r->esi = 0xffffffffu;
    if ((uint8_t)(((r->eax >> 8) & 0xff)) != (uint8_t)0x4a)
    {
        goto at_4e97d1;
    }
    r->esi = 0x1;
    r->ebx = r->ebx + r->esi;
at_4e97d1:
    if ((uint8_t)rd8(r, r->ebx) != (uint8_t)0x4d)
    {
        goto at_4e97d9;
    }
    r->ebx = r->ebx + 1;
    r->esi = 0;
at_4e97d9:
    r->edx = r->esp + 0xc;
    r->eax = r->ebx;
    wr32(r, r->ecx + 0x20, r->esi);
    call_mem_keep(r, 0x4e9670, 8);
    r->edx = r->eax;
    r->ebx = r->eax;
    if (r->esi == 0)
    {
        goto at_4e97f8;
    }
    r->eax = rd32(r, r->esp + 0xc);
    wr32(r, r->ecx + 0x1c, r->eax);
    goto at_4e983d;
at_4e97f8:
    r->eax = rd32(r, r->esp + 0xc);
    r->eax = r->eax - 1;
    wr32(r, r->ecx + 0x10, r->eax);
    if ((uint8_t)rd8(r, r->edx) != (uint8_t)0x2e)
    {
        goto at_4e9836;
    }
    r->eax = r->edx + 0x1;
    r->edx = r->esp + 0xc;
    call_mem_keep(r, 0x4e9670, 8);
    r->esi = r->eax;
    r->ebx = r->eax;
    r->eax = rd32(r, r->esp + 0xc);
    wr32(r, r->ecx + 0xc, r->eax);
    if ((uint8_t)rd8(r, r->esi) != (uint8_t)0x2e)
    {
        goto at_4e9836;
    }
    r->edx = r->esp + 0xc;
    r->eax = r->esi + 0x1;
    call_mem_keep(r, 0x4e9670, 8);
    r->ebx = r->eax;
    r->eax = rd32(r, r->esp + 0xc);
    wr32(r, r->ecx + 0x18, r->eax);
at_4e9836:
    wr32(r, r->ecx + 0x1c, 0x0);
at_4e983d:
    r->edx = 0x2;
    r->esi = 0;
    wr32(r, r->esp + 0x8, r->edx);
    wr32(r, r->esp, r->esi);
    wr32(r, r->esp + 0x4, r->esi);
    if ((uint8_t)rd8(r, r->ebx) != (uint8_t)0x2f)
    {
        goto at_4e9886;
    }
    r->edx = r->esp + 0x8;
    r->eax = r->ebx + 0x1;
    call_mem_keep(r, 0x4e9670, 8);
    set_high8(&r->edx, rd8(r, r->eax));
    r->ebx = r->eax;
    if ((uint8_t)(((r->edx >> 8) & 0xff)) != (uint8_t)0x3a)
    {
        goto at_4e9886;
    }
    r->edx = r->esp + 0x4;
    r->eax = r->eax + 1;
    call_mem_keep(r, 0x4e9670, 8);
    set_low8(&r->edx, rd8(r, r->eax));
    r->ebx = r->eax;
    if ((uint8_t)((r->edx & 0xff)) != (uint8_t)0x3a)
    {
        goto at_4e9886;
    }
    r->edx = r->esp;
    r->eax = r->eax + 1;
    call_mem_keep(r, 0x4e9670, 8);
    r->ebx = r->eax;
at_4e9886:
    r->eax = rd32(r, r->esp);
    wr32(r, r->ecx, r->eax);
    r->eax = rd32(r, r->esp + 0x4);
    wr32(r, r->ecx + 0x4, r->eax);
    r->eax = rd32(r, r->esp + 0x8);
    wr32(r, r->ecx + 0x8, r->eax);
    r->eax = r->ebx;
    r->esp = r->esp + 0x10;
    r->esi = pop_mem(r);
    r->ecx = pop_mem(r);
    r->ebx = pop_mem(r);
    return;
    r->ebx = 0x1;
    r->edx = 0x50b051;
    r->eax = rd32(r, 0x50b0dc);
    wr32(r, 0x50b0e0, r->ebx);
    r->eax = r->eax - 0xe10;
    r->ebx = r->esp;
    wr32(r, r->esp, r->eax);
    r->eax = r->ecx;
    call_mem_keep(r, 0x4e969c, 8);
    r->ecx = rd32(r, r->esp);
    r->esi = rd32(r, 0x50b0dc);
    r->edx = r->eax;
    r->esi = r->esi - r->ecx;
    set_low8(&r->ebx, rd8(r, r->eax));
    wr32(r, 0x50b0e4, r->esi);
    if ((uint8_t)((r->ebx & 0xff)) != (uint8_t)0x2c)
    {
        goto at_4e98ef;
    }
    r->edx = 0x50af88;
    r->eax = r->eax + 1;
    call_mem_keep(r, 0x4e97b4, 8);
    r->edx = r->eax;
at_4e98ef:
    set_high8(&r->ebx, rd8(r, r->edx));
    r->esi = rd32(r, 0x50b0e4);
    if ((uint8_t)(((r->ebx >> 8) & 0xff)) != (uint8_t)0x2c)
    {
        goto at_4e9963;
    }
    r->eax = r->edx + 0x1;
    r->edx = 0x50afac;
    call_mem_keep(r, 0x4e97b4, 8);
    r->esi = rd32(r, 0x50b0e4);
    r->ebx = 0xe10;
    r->edx = r->esi;
    r->eax = r->esi;
    r->edx = (uint32_t)((int32_t)r->edx >> 0x1f);
    idiv32(r, r->ebx);
    r->edi = rd32(r, 0x50afb4);
    r->ebx = 0x3c;
    r->edx = r->esi;
    r->edi = r->edi - r->eax;
    r->eax = r->esi;
    r->edx = (uint32_t)((int32_t)r->edx >> 0x1f);
    idiv32(r, r->ebx);
    r->edx = r->eax;
    r->edx = (uint32_t)((int32_t)r->edx >> 0x1f);
    idiv32(r, r->ebx);
    r->ebp = rd32(r, 0x50afb0);
    r->ebp = r->ebp - r->edx;
    r->edx = r->esi;
    r->eax = r->esi;
    r->edx = (uint32_t)((int32_t)r->edx >> 0x1f);
    idiv32(r, r->ebx);
    r->eax = rd32(r, 0x50afac);
    wr32(r, 0x50afb4, r->edi);
    r->eax = r->eax - r->edx;
    wr32(r, 0x50afb0, r->ebp);
    wr32(r, 0x50afac, r->eax);
at_4e9963:
    wr32(r, 0x50b0e4, r->esi);
    r->esp = r->esp + 0x4;
    r->ebp = pop_mem(r);
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    r->edx = pop_mem(r);
    r->ecx = pop_mem(r);
    r->ebx = pop_mem(r);
    return;
    wr8(r, r->eax, rd8(r, r->eax) + (r->eax & 0xff));
    wr8(r, r->eax, rd8(r, r->eax) + (r->eax & 0xff));
    wr8(r, r->eax, rd8(r, r->eax) + (r->eax & 0xff));
    wr8(r, r->eax, rd8(r, r->eax) + (r->eax & 0xff));
    wr8(r, r->eax, rd8(r, r->eax) + (r->eax & 0xff));
    wr8(r, r->eax, rd8(r, r->eax) + (r->eax & 0xff));
    wr8(r, r->ecx + 0x56, rd8(r, r->ecx + 0x56) + (r->edx & 0xff));
    push_mem(r, r->edi);
    push_mem(r, r->ebp);
    r->ebp = 0;
    if (r->eax == 0)
    {
        goto at_4e9a28;
    }
    r->ecx = r->eax + 0xb;
    if (r->ecx < r->eax)
    {
        goto at_4e9a28;
    }
    r->edi = r->ebx;
    set_low8(&r->ecx, (r->ecx & 0xff) & 0xf8);
    r->eax = rd32(r, r->ebx + 0x14);
    if (r->ecx >= 0x10)
    {
        goto at_4e99ab;
    }
    r->ecx = 0x10;
at_4e99ab:
    if (r->ecx > r->eax)
    {
        goto at_4e9a28;
    }
    r->ebx = rd32(r, r->edi + 0x10);
    r->eax = rd32(r, r->edi + 0xc);
    if (r->ecx > r->ebx)
    {
        goto at_4e99c2;
    }
    r->eax = rd32(r, r->edi + 0x28);
    r->ebx = 0;
at_4e99c2:
    r->esi = r->edi + 0x20;
at_4e99c5:
    r->edx = rd32(r, r->eax);
    if (r->ecx <= r->edx)
    {
        goto at_4e99dd;
    }
    if (r->edx <= r->ebx)
    {
        goto at_4e99d1;
    }
    r->ebx = r->edx;
at_4e99d1:
    r->eax = rd32(r, r->eax + 0x8);
    if (r->eax != r->esi && !r->port->env.failed)
    {
        goto at_4e99c5;
    }
    wr32(r, r->edi + 0x14, r->ebx);
    goto at_4e9a28;
at_4e99dd:
    wr32(r, r->edi + 0x10, r->ebx);
    r->ebx = rd32(r, r->edi + 0x18);
    r->ebx = r->ebx + 1;
    r->edx = r->edx - r->ecx;
    wr32(r, r->edi + 0x18, r->ebx);
    if (r->edx < 0x10)
    {
        goto at_4e9a0c;
    }
    r->ebx = r->eax + r->ecx;
    wr32(r, r->edi + 0xc, r->ebx);
    wr32(r, r->ebx, r->edx);
    wr32(r, r->eax, r->ecx);
    r->ecx = rd32(r, r->eax + 0x4);
    wr32(r, r->ebx + 0x4, r->ecx);
    r->edx = rd32(r, r->eax + 0x8);
    wr32(r, r->ebx + 0x8, r->edx);
    wr32(r, r->ecx + 0x8, r->ebx);
    wr32(r, r->edx + 0x4, r->ebx);
    goto at_4e9a1e;
at_4e9a0c:
    wr32(r, r->edi + 0x1c, rd32(r, r->edi + 0x1c) - 1);
    r->edx = rd32(r, r->eax + 0x4);
    wr32(r, r->edi + 0xc, r->edx);
    r->ebx = rd32(r, r->eax + 0x8);
    wr32(r, r->edx + 0x8, r->ebx);
    wr32(r, r->ebx + 0x4, r->edx);
at_4e9a1e:
    set_low8(&r->edx, rd8(r, r->eax));
    set_low8(&r->edx, (r->edx & 0xff) | 0x1);
    r->ebp = r->eax + 0x4;
    wr8(r, r->eax, (r->edx & 0xff));
at_4e9a28:
    r->eax = r->ebp;
    r->ebp = pop_mem(r);
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    r->ecx = pop_mem(r);
    return;
}

uint32_t vertrix_port_rtl_tz_rule_parse_4e97b4(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x30
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
