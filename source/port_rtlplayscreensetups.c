#include "port_rtlplayscreensetups.h"

/* Sets up the play screen without heads: loads the background (.\IMAGE\BACKGROUND\), starts the
 * music, resets the keys and timers, fades in and builds the play screen actors. */

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

/* Original 0x41e780: Sets up the play screen without heads: loads the background
 * (.\IMAGE\BACKGROUND\), starts the music, resets the keys and timers, fades in and builds the play
 * screen actors. Evidence: calls 0x4ca090, 0x45f540, 0x45f590, 0x41a960, 0x4191b0, 0x45f770,
 * 0x472d00, 0x476090, 0x4760f0, 0x476590, 0x4765b0, 0x476140, 0x4b7cd0, 0x477d70, 0x46a9c0,
 * 0x471a70, 0x4719f0, 0x4719e0, 0x47a040, 0x469480, 0x41aa20, 0x41ab00, 0x41aaa0, 0x418840 and 2
 * more; reads 0x532a84, 0x532a70, 0x513c1a, 0x532a90, 0x532a7c, 0x4f8520, 0x532b40, 0x544070,
 * 0x4f880c, 0x4f8800, 0x4f8808, 0x4f8804, 0x4f881c, 0x4f8818, 0x4f8814, 0x4f8810 and more; writes
 * 0x532a54. Register-for-register from the listing (0x41e78e..0x41eaaa); labels are the original
 * addresses. */
static void run(Regs *r)
{
    r->esi = r->eax;
    r->eax = r->ebp - 0x34;
    r->edx = 0x4ec1ec;
    r->ecx = 0x5140d0;
    push(r, r->port->env.chain);
    wr32(r, r->eax, pop(r));
    r->port->env.chain = r->eax;
    r->ebx = 0;
    r->edi = rd32(r, 0x532a84);
    wr32(r, r->ebp - 0x30, r->edx);
    wr32(r, r->ebp - 0x2c, r->ecx);
    wr32(r, r->ebp - 0x28, r->ebx);
    if (r->edi == 0x1)
    {
        goto at_41ea34;
    }
at_41e7c6:
    r->edx = rd32(r, 0x532a70);
    r->edx = r->edx << 0x2;
    r->eax = r->ebp - 0x20;
    r->edx = r->edx + 0x5332c0;
    call_keep(r, 0x4ca090);
    r->edx = 0x1;
    r->ebx = rd32(r, r->ebp - 0x20);
    r->eax = r->ebp - 0x138;
    wr32(r, r->ebp - 0x28, r->edx);
    r->edx = 0x4fc290;
    call_keep(r, 0x45f540);
    r->eax = r->ebp - 0x138;
    call_keep(r, 0x45f590);
    if (r->eax != 0)
    {
        goto at_41e82a;
    }
    r->ebx = 0;
    set_low8(&r->ebx, rd8(r, 0x513c1a));
    r->ebx = r->ebx << 0x2;
    r->ebx = r->ebx + 0x5334a0;
    r->edx = 0x4fc398;
    r->eax = r->ebp - 0x138;
    r->ebx = rd32(r, r->ebx);
    call_keep(r, 0x45f540);
at_41e82a:
    r->edx = r->ebp - 0x138;
    r->eax = r->esi;
    call_keep(r, 0x41a960);
    r->ecx = rd32(r, 0x532a90);
    if (r->ecx != 0x1)
    {
        goto at_41ea46;
    }
    r->edi = r->ecx;
at_41e848:
    r->eax = rd32(r, 0x532a84);
    if (r->eax != 0x1)
    {
        goto at_41eaa0;
    }
    if (r->eax != rd32(r, 0x532a7c))
    {
        goto at_41ea78;
    }
    if (r->edi != r->eax)
    {
        goto at_41ea65;
    }
at_41e86a:
    r->eax = rd32(r, 0x4f8520);
at_41e86f:
    wr32(r, r->ebp - 0x18, r->eax);
at_41e872:
    r->ebx = 0x1;
    r->edx = rd32(r, r->ebp - 0x18);
    r->eax = r->esi;
    call_keep(r, 0x4191b0);
    call_keep(r, 0x45f770);
    r->ebx = rd32(r, 0x532b40);
    if (r->ebx != 0x1)
    {
        goto at_41e898;
    }
    r->eax = r->ebx;
    call_keep(r, 0x472d00);
at_41e898:
    r->eax = 0x54d640;
    call_keep(r, 0x476090);
    r->eax = 0x54d640;
    call_keep(r, 0x4760f0);
    r->eax = 0x54d640;
    call_keep(r, 0x476590);
    r->eax = 0x54d640;
    r->edx = 0x1;
    call_keep(r, 0x4765b0);
    r->eax = 0x54d640;
    call_keep(r, 0x476140);
    r->edx = 0x3b;
    r->eax = 0x54d640;
    call_keep(r, 0x476140);
    r->edx = 0x3c;
    r->eax = 0x54d640;
    call_keep(r, 0x476140);
    r->edx = 0x3d;
    r->eax = 0x54d640;
    call_keep(r, 0x476140);
    call_keep(r, 0x4b7cd0);
    r->eax = 0x5588f8;
    call_keep(r, 0x477d70);
    r->edx = r->edi;
    r->eax = 0x1;
    call_keep(r, 0x46a9c0);
    call_keep(r, 0x471a70);
    r->eax = rd32(r, 0x544070);
    r->eax = rd32(r, r->eax + 0x268);
    call_keep(r, 0x4719f0);
    call_keep(r, 0x4719e0);
    push(r, 0x50);
    r->eax = rd32(r, 0x4f880c);
    push(r, r->eax);
    r->eax = rd32(r, 0x4f8800);
    r->ecx = rd32(r, 0x4f8808);
    wr32(r, r->ebp - 0x1c, r->eax);
    r->eax = rd32(r, 0x544070);
    r->ebx = rd32(r, 0x4f8804);
    r->edx = rd32(r, r->ebp - 0x1c);
    r->eax = rd32(r, r->eax + 0x268);
    call(r, 0x47a040, 2);
    push(r, 0x50);
    r->edx = rd32(r, 0x4f881c);
    r->ecx = rd32(r, 0x4f8818);
    r->eax = rd32(r, 0x4f8814);
    push(r, r->edx);
    wr32(r, r->ebp - 0x1c, r->eax);
    r->eax = rd32(r, 0x544070);
    r->ebx = rd32(r, r->ebp - 0x1c);
    r->edx = rd32(r, 0x4f8810);
    r->eax = rd32(r, r->eax + 0x268);
    call(r, 0x47a040, 2);
    push(r, 0x50);
    r->ecx = rd32(r, 0x4f8864);
    r->eax = rd32(r, 0x4f885c);
    r->edx = rd32(r, 0x4f8858);
    push(r, r->ecx);
    wr32(r, r->ebp - 0x1c, r->eax);
    r->eax = rd32(r, 0x544070);
    r->ebx = rd32(r, r->ebp - 0x1c);
    r->ecx = rd32(r, 0x4f8860);
    r->eax = rd32(r, r->eax + 0x268);
    call(r, 0x47a040, 2);
    r->eax = 0x1;
    r->edx = r->edi;
    call_keep(r, 0x469480);
    r->eax = rd32(r, 0x532a98);
    wr32(r, 0x532a54, r->eax);
    r->eax = r->esi;
    call_keep(r, 0x41aa20);
    call_keep(r, 0x471a70);
    r->eax = r->esi;
    call_keep(r, 0x41ab00);
    r->eax = r->esi;
    r->edx = 0x422c50;
    call_keep(r, 0x41aaa0);
    r->eax = r->esi;
    wr8(r, r->esi + 0xc8, 0x4);
    call_keep(r, 0x418840);
    r->edx = 0x41eab0;
    r->eax = r->esi;
    r->ebx = 0;
    call_keep(r, 0x418820);
    r->eax = r->ebp - 0x20;
    r->edx = 0;
    wr32(r, r->ebp - 0x28, r->ebx);
    call_keep(r, 0x4ca210);
    r->eax = rd32(r, r->ebp - 0x34);
    wr32(r, r->ebp - 0x28, r->ebx);
    r->port->env.chain = r->eax;
    r->edi = rd32(r, r->ebp - 0x14);
    r->esi = rd32(r, r->ebp - 0x10);
    r->edx = rd32(r, r->ebp - 0xc);
    r->ecx = rd32(r, r->ebp - 0x8);
    r->ebx = rd32(r, r->ebp - 0x4);
    return;
at_41ea34:
    r->eax = rd32(r, 0x5bb490);
    push(r, r->eax);
    call_all(r, rd32(r, 0x4f1c7c));
    if (r->port->env.failed)
    {
        return;
    }
    goto at_41e7c6;
at_41ea46:
    if (rd32(r, 0x532a94) != 0x1)
    {
        goto at_41ea59;
    }
    r->edi = 0x2;
    if (r->port->env.failed)
    {
        return;
    }
    goto at_41e848;
at_41ea59:
    r->eax = rd32(r, 0x4f851c);
    r->edi = 0;
    if (r->port->env.failed)
    {
        return;
    }
    goto at_41e86f;
at_41ea65:
    if (r->edi != 0x2 && !r->port->env.failed)
    {
        goto at_41e872;
    }
    r->eax = rd32(r, 0x4f8524);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_41e86f;
at_41ea78:
    if (r->eax != rd32(r, 0x532a80) && !r->port->env.failed)
    {
        goto at_41e872;
    }
    if (r->edi != r->eax)
    {
        goto at_41ea92;
    }
    r->eax = rd32(r, 0x4f8524);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_41e86f;
at_41ea92:
    if (r->edi != 0x2 && !r->port->env.failed)
    {
        goto at_41e872;
    }
    if (r->port->env.failed)
    {
        return;
    }
    goto at_41e86a;
at_41eaa0:
    if (r->edi != 0x1 && !r->port->env.failed)
    {
        goto at_41ea92;
    }
    r->eax = rd32(r, 0x4f8524);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_41e86f;
}

uint32_t vertrix_port_play_screen_setup_41e780(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x13c
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
