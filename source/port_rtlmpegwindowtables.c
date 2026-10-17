#include "port_rtlmpegwindowtables.h"

/* Builds the MP3 IMDCT window tables from sines when the reader is reset. */

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

/* Original 0x40a590: Builds the MP3 IMDCT window tables from sines when the reader is reset.
 * Evidence: calls 0x4d6768, 0x4db507, 0x4db350, 0x4eb652, 0x4c9dd6, 0x4eb606. Register-for-register
 * from the listing (0x40a590..0x40a7fa); labels are the original addresses. */
static void run(Regs *r)
{
    push_mem(r, r->ebx);
    push_mem(r, r->ecx);
    push_mem(r, r->edx);
    push_mem(r, r->esi);
    push_mem(r, r->edi);
    push_mem(r, r->ebp);
    r->esp = r->esp - 0x28;
    wr32(r, r->esp + 0x18, r->eax);
    r->edx = 0;
    wr32(r, r->esp + 0x14, r->edx);
    wr32(r, r->esp + 0xc, r->edx);
at_40a5a7:
    set_low8(&r->ecx, rd8(r, r->esp + 0x14));
    r->eax = 0x10;
    r->eax = (uint32_t)((int32_t)r->eax >> (r->ecx & 0xff));
    wr32(r, r->esp + 0x20, r->eax);
    r->eax = 0x40;
    r->eax = (uint32_t)((int32_t)r->eax >> (r->ecx & 0xff));
    wr32(r, r->esp + 0x1c, r->eax);
    r->eax = rd32(r, r->esp + 0xc);
    r->eax = rd32(r, r->eax + 0x4f5f90);
    r->esi = 0;
    if ((int32_t)rd32(r, r->esp + 0x20) <= (int32_t)0x0)
    {
        goto at_40a666;
    }
    wr32(r, r->esp + 0x24, r->eax);
at_40a5dc:
    r->eax = r->esi;
    call_mem_keep(r, 0x4d6768, 8);
    r->ebx = 0;
    r->ecx = 0x40000000;
    call_mem_keep(r, 0x4db507, 8);
    r->ebx = 0;
    r->ecx = 0x3ff00000;
    call_mem_keep(r, 0x4db350, 8);
    r->ebx = 0x54442d18;
    r->ecx = 0x400921fb;
    call_mem_keep(r, 0x4db507, 8);
    r->ecx = r->eax;
    r->ebx = r->edx;
    r->eax = rd32(r, r->esp + 0x1c);
    call_mem_keep(r, 0x4d6768, 8);
    r->edi = r->eax;
    r->ebp = r->edx;
    r->eax = r->ecx;
    r->edx = r->ebx;
    r->ebx = r->edi;
    r->ecx = r->ebp;
    call_mem_keep(r, 0x4eb652, 8);
    call_mem_keep(r, 0x4c9dd6, 8);
    r->ebx = 0;
    r->ecx = 0x40000000;
    call_mem_keep(r, 0x4db507, 8);
    r->ebx = r->eax;
    r->ecx = r->edx;
    r->eax = 0;
    r->edx = 0x3ff00000;
    call_mem_keep(r, 0x4eb652, 8);
    call_mem_keep(r, 0x4eb606, 8);
    r->edx = rd32(r, r->esp + 0x24);
    wr32(r, r->edx, r->eax);
    r->edi = r->edx + 0x4;
    wr32(r, r->esp + 0x24, r->edi);
    r->esi = r->esi + 1;
    if ((int32_t)r->esi < (int32_t)rd32(r, r->esp + 0x20) && !r->port->env.failed)
    {
        goto at_40a5dc;
    }
at_40a666:
    wr32(r, r->esp + 0xc, rd32(r, r->esp + 0xc) + 0x4);
    r->edx = rd32(r, r->esp + 0x14);
    r->edx = r->edx + 1;
    wr32(r, r->esp + 0x14, r->edx);
    if ((int32_t)r->edx < (int32_t)0x5 && !r->port->env.failed)
    {
        goto at_40a5a7;
    }
    r->edi = 0x52e784;
    wr32(r, r->esp + 0x18, 0u - rd32(r, r->esp + 0x18));
    r->esi = 0;
    r->ebp = 0;
    wr32(r, r->esp + 0x10, r->esi);
at_40a68e:
    if (r->edi < 0x52efc4)
    {
        goto at_40a741;
    }
at_40a69a:
    r->eax = r->esi;
    r->edx = r->esi;
    r->edx = (uint32_t)((int32_t)r->edx >> 0x1f);
    r->ecx = 0x20;
    idiv32(r, r->ecx);
    if (r->edx != 0x1f)
    {
        goto at_40a6b3;
    }
    r->edi = r->edi - 0xffc;
at_40a6b3:
    r->eax = r->esi;
    r->edx = r->esi;
    r->edx = (uint32_t)((int32_t)r->edx >> 0x1f);
    r->ecx = 0x40;
    idiv32(r, r->ecx);
    if (r->edx != 0x3f)
    {
        goto at_40a6ca;
    }
    wr32(r, r->esp + 0x18, 0u - rd32(r, r->esp + 0x18));
at_40a6ca:
    r->esi = r->esi + 1;
    wr32(r, r->esp + 0x10, rd32(r, r->esp + 0x10) + 0x4);
    r->ebp = r->ebp + 1;
    r->edi = r->edi + 0x80;
    if ((int32_t)r->esi < (int32_t)0x100 && !r->port->env.failed)
    {
        goto at_40a68e;
    }
    r->eax = r->ebp * 4;
    wr32(r, r->esp + 0x8, r->eax);
at_40a6ea:
    if ((int32_t)r->esi >= (int32_t)0x200)
    {
        goto at_40a7f1;
    }
    if (r->edi < 0x52efc4)
    {
        goto at_40a78d;
    }
at_40a702:
    r->eax = r->esi;
    r->edx = r->esi;
    r->edx = (uint32_t)((int32_t)r->edx >> 0x1f);
    r->ecx = 0x20;
    idiv32(r, r->ecx);
    if (r->edx != 0x1f)
    {
        goto at_40a71b;
    }
    r->edi = r->edi - 0xffc;
at_40a71b:
    r->eax = r->esi;
    r->edx = r->esi;
    r->edx = (uint32_t)((int32_t)r->edx >> 0x1f);
    r->ecx = 0x40;
    idiv32(r, r->ecx);
    if (r->edx == 0x3f)
    {
        goto at_40a7db;
    }
    r->esi = r->esi + 1;
    wr32(r, r->esp + 0x8, rd32(r, r->esp + 0x8) - 0x4);
    r->ebp = r->ebp - 1;
    r->edi = r->edi + 0x80;
    if (r->port->env.failed)
    {
        return;
    }
    goto at_40a6ea;
at_40a741:
    r->eax = rd32(r, r->esp + 0x10);
    r->eax = rd32(r, r->eax + 0x4f5fa4);
    call_mem_keep(r, 0x4d6768, 8);
    r->ebx = 0;
    r->ecx = 0x3ef00000;
    call_mem_keep(r, 0x4db507, 8);
    wr32(r, r->esp + 0x4, r->eax);
    r->ecx = r->edx;
    r->eax = rd32(r, r->esp + 0x18);
    call_mem_keep(r, 0x4d6768, 8);
    r->ebx = r->eax;
    wr32(r, r->esp, r->edx);
    r->eax = rd32(r, r->esp + 0x4);
    r->edx = r->ecx;
    r->ecx = rd32(r, r->esp);
    call_mem_keep(r, 0x4db507, 8);
    call_mem_keep(r, 0x4eb606, 8);
    wr32(r, r->edi, r->eax);
    wr32(r, r->edi + 0x40, r->eax);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_40a69a;
at_40a78d:
    r->eax = rd32(r, r->esp + 0x8);
    r->eax = rd32(r, r->eax + 0x4f5fa4);
    call_mem_keep(r, 0x4d6768, 8);
    r->ebx = 0;
    r->ecx = 0x3ef00000;
    call_mem_keep(r, 0x4db507, 8);
    r->ecx = r->eax;
    r->ebx = r->edx;
    r->eax = rd32(r, r->esp + 0x18);
    call_mem_keep(r, 0x4d6768, 8);
    wr32(r, r->esp, r->eax);
    wr32(r, r->esp + 0x4, r->edx);
    r->eax = r->ecx;
    r->edx = r->ebx;
    r->ebx = rd32(r, r->esp);
    r->ecx = rd32(r, r->esp + 0x4);
    call_mem_keep(r, 0x4db507, 8);
    call_mem_keep(r, 0x4eb606, 8);
    wr32(r, r->edi, r->eax);
    wr32(r, r->edi + 0x40, r->eax);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_40a702;
at_40a7db:
    wr32(r, r->esp + 0x18, 0u - rd32(r, r->esp + 0x18));
    r->esi = r->esi + 1;
    wr32(r, r->esp + 0x8, rd32(r, r->esp + 0x8) - 0x4);
    r->ebp = r->ebp - 1;
    r->edi = r->edi + 0x80;
    if (r->port->env.failed)
    {
        return;
    }
    goto at_40a6ea;
at_40a7f1:
    r->esp = r->esp + 0x28;
    r->ebp = pop_mem(r);
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    r->edx = pop_mem(r);
    r->ecx = pop_mem(r);
    r->ebx = pop_mem(r);
    return;
}

uint32_t vertrix_port_window_tables_40a590(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x50
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
