#include "port_rtljpegscansetups.h"

/* libjpeg per_scan_setup: computes the MCU layout of the current scan for one component or for up
 * to four interleaved components. */

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

static void div32(Regs *r, uint32_t value)
{
    LiftFlags flags;
    memset(&flags, 0, sizeof flags);
    lift_div1(32, value, &r->eax, &r->edx, &flags);
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

/* Original 0x4bcbc0: libjpeg per_scan_setup: computes the MCU layout of the current scan for one
 * component or for up to four interleaved components. Evidence: calls 0x4c9820.
 * Register-for-register from the listing (0x4bcbcb..0x4bce80); labels are the original addresses.
 */
static void run(Regs *r)
{
    wr32(r, r->ebp - 0x28, r->eax);
    r->edx = rd32(r, r->eax + 0x148);
    r->ecx = r->eax;
    if (r->edx == 0x1)
    {
        goto at_4bcce5;
    }
    if ((int32_t)r->edx <= 0)
    {
        goto at_4bcbe8;
    }
    if ((int32_t)r->edx <= (int32_t)0x4)
    {
        goto at_4bcc0b;
    }
at_4bcbe8:
    r->eax = rd32(r, r->ecx);
    wr32(r, r->eax + 0x14, 0x1a);
    r->eax = rd32(r, r->ecx);
    r->edx = rd32(r, r->ecx + 0x148);
    wr32(r, r->eax + 0x18, r->edx);
    r->eax = rd32(r, r->ecx);
    wr32(r, r->eax + 0x1c, 0x4);
    r->edx = rd32(r, r->ecx);
    r->eax = r->ecx;
    call_all(r, rd32(r, r->edx));
at_4bcc0b:
    r->edx = rd32(r, r->ecx + 0x134);
    r->eax = rd32(r, r->ecx + 0x1c);
    r->edx = r->edx << 0x3;
    call_keep(r, 0x4c9820);
    r->edx = rd32(r, r->ecx + 0x138);
    wr32(r, r->ecx + 0x15c, r->eax);
    r->edx = r->edx << 0x3;
    r->eax = rd32(r, r->ecx + 0x20);
    call_keep(r, 0x4c9820);
    wr32(r, r->ecx + 0x164, 0x0);
    r->esi = 0;
    r->edi = rd32(r, r->ecx + 0x148);
    wr32(r, r->ecx + 0x160, r->eax);
    if ((int32_t)r->edi <= 0)
    {
        goto at_4bcd4a;
    }
    r->edi = r->ecx;
at_4bcc55:
    r->ebx = rd32(r, r->edi + 0x14c);
    r->eax = rd32(r, r->ebx + 0x8);
    wr32(r, r->ebx + 0x34, r->eax);
    r->eax = rd32(r, r->ebx + 0xc);
    wr32(r, r->ebx + 0x38, r->eax);
    r->eax = rd32(r, r->ebx + 0x34);
    r->edx = rd32(r, r->ebx + 0x38);
    r->eax = r->eax * r->edx;
    wr32(r, r->ebx + 0x3c, r->eax);
    r->edx = rd32(r, r->ebx + 0x24);
    r->eax = rd32(r, r->ebx + 0x34);
    r->eax = r->eax * r->edx;
    wr32(r, r->ebx + 0x40, r->eax);
    r->edx = 0;
    r->eax = rd32(r, r->ebx + 0x1c);
    div32(r, rd32(r, r->ebx + 0x34));
    r->eax = r->edx;
    if (r->edx != 0)
    {
        goto at_4bcc90;
    }
    r->eax = rd32(r, r->ebx + 0x34);
at_4bcc90:
    wr32(r, r->ebx + 0x44, r->eax);
    r->edx = 0;
    r->eax = rd32(r, r->ebx + 0x20);
    div32(r, rd32(r, r->ebx + 0x38));
    r->eax = r->edx;
    if (r->edx != 0)
    {
        goto at_4bcca4;
    }
    r->eax = rd32(r, r->ebx + 0x38);
at_4bcca4:
    wr32(r, r->ebx + 0x48, r->eax);
    r->edx = rd32(r, r->ebx + 0x3c);
    r->eax = rd32(r, r->ecx + 0x164);
    r->eax = r->eax + r->edx;
    if ((int32_t)r->eax > (int32_t)0xa)
    {
        goto at_4bcdea;
    }
at_4bccbb:
    r->eax = r->edx;
    r->edx = r->edx - 1;
    if ((int32_t)r->eax <= 0)
    {
        goto at_4bcdd3;
    }
    r->eax = rd32(r, r->ecx + 0x164);
    r->ebx = r->eax * 4;
    r->eax = r->eax + 1;
    wr32(r, r->ecx + 0x164, r->eax);
    r->eax = r->ecx + r->ebx;
    wr32(r, r->eax + 0x168, r->esi);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4bccbb;
at_4bcce5:
    r->ebx = rd32(r, r->eax + 0x14c);
    r->edx = r->ecx;
    r->eax = rd32(r, r->ebx + 0x1c);
    wr32(r, r->edx + 0x15c, r->eax);
    r->eax = rd32(r, r->ebx + 0x20);
    wr32(r, r->edx + 0x160, r->eax);
    r->eax = rd32(r, r->ebx + 0x24);
    r->esi = rd32(r, r->ebx + 0xc);
    wr32(r, r->ebx + 0x40, r->eax);
    r->edx = 0;
    r->eax = rd32(r, r->ebx + 0x20);
    div32(r, r->esi);
    wr32(r, r->ebx + 0x34, 0x1);
    wr32(r, r->ebx + 0x38, 0x1);
    wr32(r, r->ebx + 0x3c, 0x1);
    wr32(r, r->ebx + 0x44, 0x1);
    r->eax = r->edx;
    if (r->edx != 0)
    {
        goto at_4bcd33;
    }
    r->eax = r->esi;
at_4bcd33:
    wr32(r, r->ebx + 0x48, r->eax);
    wr32(r, r->ecx + 0x164, 0x1);
    wr32(r, r->ecx + 0x168, 0x0);
at_4bcd4a:
    r->eax = rd32(r, r->ebp - 0x28);
    r->ecx = 0;
    wr32(r, r->ebp - 0x18, r->eax);
    r->ebx = rd32(r, r->eax + 0x148);
    wr32(r, r->ebp - 0x24, r->ecx);
    if ((int32_t)r->ebx <= 0)
    {
        goto at_4bcd96;
    }
    wr32(r, r->ebp - 0x20, r->eax);
at_4bcd62:
    r->eax = rd32(r, r->ebp - 0x20);
    r->eax = rd32(r, r->eax + 0x14c);
    r->ebx = rd32(r, r->eax + 0x4c);
    wr32(r, r->ebp - 0x1c, r->eax);
    if (r->ebx == 0)
    {
        goto at_4bcdfe;
    }
at_4bcd79:
    r->esi = rd32(r, r->ebp - 0x20);
    r->edi = rd32(r, r->ebp - 0x24);
    r->edx = rd32(r, r->ebp - 0x18);
    r->esi = r->esi + 0x4;
    r->edi = r->edi + 1;
    r->ecx = rd32(r, r->edx + 0x148);
    wr32(r, r->ebp - 0x20, r->esi);
    wr32(r, r->ebp - 0x24, r->edi);
    if ((int32_t)r->edi < (int32_t)r->ecx && !r->port->env.failed)
    {
        goto at_4bcd62;
    }
at_4bcd96:
    r->edx = rd32(r, r->ebp - 0x28);
    r->edx = rd32(r, r->edx + 0x1bc);
    r->eax = rd32(r, r->ebp - 0x28);
    call_all(r, rd32(r, r->edx));
    r->edx = rd32(r, r->ebp - 0x28);
    r->edx = rd32(r, r->edx + 0x1ac);
    r->eax = rd32(r, r->ebp - 0x28);
    call_all(r, rd32(r, r->edx));
    r->eax = rd32(r, r->ebp - 0x28);
    r->edx = rd32(r, r->ebp - 0x28);
    r->eax = rd32(r, r->eax + 0x1ac);
    r->edx = rd32(r, r->edx + 0x1b4);
    r->eax = rd32(r, r->eax + 0x4);
    wr32(r, r->edx, r->eax);
    r->edi = rd32(r, r->ebp - 0x14);
    r->esi = rd32(r, r->ebp - 0x10);
    r->edx = rd32(r, r->ebp - 0xc);
    r->ecx = rd32(r, r->ebp - 0x8);
    r->ebx = rd32(r, r->ebp - 0x4);
    return;
at_4bcdd3:
    r->esi = r->esi + 1;
    r->eax = rd32(r, r->ecx + 0x148);
    r->edi = r->edi + 0x4;
    if ((int32_t)r->esi >= (int32_t)r->eax && !r->port->env.failed)
    {
        goto at_4bcd4a;
    }
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4bcc55;
at_4bcdea:
    r->eax = rd32(r, r->ecx);
    wr32(r, r->eax + 0x14, 0xd);
    r->ebx = rd32(r, r->ecx);
    r->eax = r->ecx;
    call_all(r, rd32(r, r->ebx));
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4bccbb;
at_4bcdfe:
    r->ecx = rd32(r, r->eax + 0x10);
    if ((int32_t)r->ecx < 0)
    {
        goto at_4bce0a;
    }
    if ((int32_t)r->ecx < (int32_t)0x4)
    {
        goto at_4bce6b;
    }
at_4bce0a:
    r->eax = rd32(r, r->ebp - 0x18);
    r->eax = rd32(r, r->eax);
    wr32(r, r->eax + 0x14, 0x34);
    r->eax = rd32(r, r->ebp - 0x18);
    r->eax = rd32(r, r->eax);
    r->edx = rd32(r, r->ebp - 0x18);
    wr32(r, r->eax + 0x18, r->ecx);
    r->edx = rd32(r, r->edx);
    r->eax = rd32(r, r->ebp - 0x18);
    call_all(r, rd32(r, r->edx));
at_4bce28:
    r->esi = rd32(r, r->ebp - 0x18);
    r->ebx = 0x84;
    r->esi = rd32(r, r->esi + 0x4);
    r->edx = 0x1;
    r->eax = rd32(r, r->ebp - 0x18);
    call_all(r, rd32(r, r->esi));
    r->esi = rd32(r, r->ebp - 0x18);
    r->edi = r->eax;
    r->esi = rd32(r, r->esi + r->ecx * 4 + 0xa4);
    r->ecx = 0x84;
    r->edx = r->eax;
    push(r, r->edi);
    r->eax = r->ecx;
    r->ecx = r->ecx >> 0x2;
    rep_movs(r, 4);
    set_low8(&r->ecx, (r->eax & 0xff));
    set_low8(&r->ecx, (r->ecx & 0xff) & 0x3);
    rep_movs(r, 1);
    r->edi = pop(r);
    r->eax = rd32(r, r->ebp - 0x1c);
    wr32(r, r->eax + 0x4c, r->edx);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4bcd79;
at_4bce6b:
    r->esi = rd32(r, r->ebp - 0x18);
    r->eax = r->ecx * 4;
    r->eax = r->eax + r->esi;
    if (rd32(r, r->eax + 0xa4) == 0x0 && !r->port->env.failed)
    {
        goto at_4bce0a;
    }
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4bce28;
}

uint32_t vertrix_port_jpeg_per_scan_setup_4bcbc0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x2c
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
