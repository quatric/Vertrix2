#include "port_rtlsplitbars.h"

/* Lays out and draws a two-part bar: the first child actor (+0x17c) gets width (value - min) *
 * width / (max - min) from +0x18c, +0x184, +0x188 and +0xf4, the second (+0x180) the rest, and both
 * are drawn through their vtables. */

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

static uint32_t rd16(Regs *r, uint32_t address)
{
    return port_u16(r->port, address, 0);
}

static uint32_t rd32(Regs *r, uint32_t address)
{
    return port_u32(r->port, address, 0);
}

static void wr16(Regs *r, uint32_t address, uint32_t value)
{
    port_set16(r->port, address, 0, value);
}

static void wr32(Regs *r, uint32_t address, uint32_t value)
{
    port_set32(r->port, address, 0, value);
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

/* An indirect call (an import or a method): every value pushed passed and popped, as stdcall. */
static void call_all(Regs *r, uint32_t target)
{
    call_with_stack(r, target, r->pushed, 0);
}

/* Original 0x4b3de0: Lays out and draws a two-part bar: the first child actor (+0x17c) gets width
 * (value - min) * width / (max - min) from +0x18c, +0x184, +0x188 and +0xf4, the second (+0x180)
 * the rest, and both are drawn through their vtables. Evidence: calls 0x4b54d0.
 * Register-for-register from the listing (0x4b3dea..0x4b3f00); labels are the original addresses.
 */
static void run(Regs *r)
{
    r->esi = r->eax;
    r->edi = r->edx;
    r->eax = rd32(r, r->eax + 0x17c);
    set_low16(&r->edx, rd16(r, r->esi + 0x48));
    wr16(r, r->eax + 0x48, (r->edx & 0xffff));
    r->edx = rd32(r, r->esi + 0x180);
    set_low16(&r->eax, rd16(r, r->esi + 0x48));
    wr16(r, r->edx + 0x48, (r->eax & 0xffff));
    r->eax = rd32(r, r->esi + 0x18c);
    r->edx = rd32(r, r->esi + 0x184);
    r->ecx = rd32(r, r->esi + 0xf4);
    r->eax = r->eax - r->edx;
    r->eax = r->eax * r->ecx;
    r->ebx = rd32(r, r->esi + 0x188);
    r->ebx = r->ebx - r->edx;
    r->edx = 0;
    div32(r, r->ebx);
    wr32(r, r->ebp - 0x14, r->eax);
    r->ecx = rd32(r, r->ebp - 0x14);
    set_low16(&r->edx, rd16(r, r->esi + 0xe));
    wr32(r, r->ebp - 0x1c, r->ecx);
    r->ecx = rd32(r, r->esi + 0xf8);
    r->edx = (uint32_t)(int32_t)(int16_t)(r->edx & 0xffff);
    wr32(r, r->ebp - 0x18, r->ecx);
    r->ecx = 0;
    set_low16(&r->eax, rd16(r, r->esi + 0x16));
    set_low16(&r->ecx, rd16(r, r->ebp - 0x18));
    r->ebx = (uint32_t)(int32_t)(int16_t)(r->eax & 0xffff);
    push(r, r->ecx);
    r->ecx = 0;
    r->eax = rd32(r, r->esi + 0x17c);
    set_low16(&r->ecx, rd16(r, r->ebp - 0x1c));
    call(r, 0x4b54d0, 1);
    r->ebx = rd32(r, r->ebp - 0x14);
    set_low16(&r->edx, rd16(r, r->esi + 0xe));
    r->ecx = rd32(r, r->esi + 0xf4);
    r->edx = r->edx + r->ebx;
    r->ebx = rd32(r, r->ebp - 0x14);
    set_low16(&r->eax, rd16(r, r->esi + 0x16));
    r->ecx = r->ecx - r->ebx;
    r->eax = (uint32_t)(int32_t)(int16_t)r->eax;
    wr32(r, r->ebp - 0x1c, r->ecx);
    r->ecx = rd32(r, r->esi + 0xf8);
    wr32(r, r->ebp - 0x20, r->eax);
    wr32(r, r->ebp - 0x18, r->ecx);
    r->ecx = 0;
    r->edx = (uint32_t)(int32_t)(int16_t)(r->edx & 0xffff);
    set_low16(&r->ecx, rd16(r, r->ebp - 0x18));
    r->eax = rd32(r, r->esi + 0x180);
    push(r, r->ecx);
    r->ecx = 0;
    r->ebx = rd32(r, r->ebp - 0x20);
    set_low16(&r->ecx, rd16(r, r->ebp - 0x1c));
    call(r, 0x4b54d0, 1);
    r->eax = rd32(r, r->esi + 0x17c);
    r->ecx = rd32(r, r->eax + 0x158);
    r->edx = r->edi;
    call_all(r, rd32(r, r->ecx + 0x8));
    r->eax = rd32(r, r->esi + 0x180);
    r->ecx = rd32(r, r->eax + 0x158);
    r->edx = r->edi;
    call_all(r, rd32(r, r->ecx + 0x8));
    r->eax = rd32(r, r->esi + 0x160);
    if (r->eax != 0)
    {
        goto at_4b3f11;
    }
at_4b3ed7:
    r->eax = rd32(r, r->esi + 0x170);
    r->ecx = rd32(r, r->eax + 0x158);
    r->edx = r->edi;
    call_all(r, rd32(r, r->ecx + 0x8));
    r->eax = rd32(r, r->esi + 0x174);
    r->ecx = rd32(r, r->eax + 0x158);
    r->edx = r->edi;
    call_all(r, rd32(r, r->ecx + 0x8));
    r->edi = rd32(r, r->ebp - 0x10);
    r->esi = rd32(r, r->ebp - 0xc);
    r->ecx = rd32(r, r->ebp - 0x8);
    r->ebx = rd32(r, r->ebp - 0x4);
    return;
at_4b3f11:
    r->ecx = rd32(r, r->eax + 0x158);
    r->edx = r->edi;
    call_all(r, rd32(r, r->ecx + 0x8));
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4b3ed7;
}

uint32_t vertrix_port_split_bar_draw_4b3de0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x24
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
