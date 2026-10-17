#include "port_rtlheapfrees.h"

/* Frees a heap block, merging it with a free neighbour and trimming the heap. */

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

static void set_high8(uint32_t *reg, uint32_t value)
{
    *reg = (*reg & 0xffff00ffu) | ((value & 0xff) << 8);
}

static void div32(Regs *r, uint32_t value)
{
    LiftFlags flags;
    memset(&flags, 0, sizeof flags);
    lift_div1(32, value, &r->eax, &r->edx, &flags);
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

static uint32_t overflow(const Regs *r)
{
    uint32_t top = 1u << (r->fw - 1);
    uint32_t value = result(r);
    if (r->fk == F_SUB)
    {
        return (((r->fa ^ r->fb) & (r->fa ^ value)) & top) != 0;
    }
    if (r->fk == F_ADD)
    {
        return ((~(r->fa ^ r->fb) & (r->fa ^ value)) & top) != 0;
    }
    if (r->fk == F_INC)
    {
        return value == top;
    }
    if (r->fk == F_DEC)
    {
        return value == top - 1;
    }
    return 0;
}

/* A condition of the recorded flags. */
static uint32_t cond(const Regs *r, unsigned code)
{
    uint32_t zero = result(r) == 0;
    uint32_t sign = (result(r) >> (r->fw - 1)) & 1;
    uint32_t less = sign != overflow(r);
    switch (code)
    {
        case CC_E:
            return zero;
        case CC_NE:
            return !zero;
        case CC_B:
            return carry(r);
        case CC_AE:
            return !carry(r);
        case CC_BE:
            return carry(r) || zero;
        case CC_A:
            return !carry(r) && !zero;
        case CC_L:
            return less;
        case CC_GE:
            return !less;
        case CC_LE:
            return less || zero;
        case CC_G:
            return !less && !zero;
        case CC_S:
            return sign;
        default:
            return !sign;
    }
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

static void call_mem(Regs *r, uint32_t target, unsigned count)
{
    call_mem_with(r, target, count, 0);
}

static void call_mem_keep(Regs *r, uint32_t target, unsigned count)
{
    call_mem_with(r, target, count, 1);
}

/* Original 0x4e9a30: Frees a heap block, merging it with a free neighbour and trimming the heap.
 * Evidence: calls 0x4e9ca8, 0x4e9b60, 0x4ea190, 0x4e8660, 0x4e9bd8; reads 0x50aefc, 0x50b214,
 * 0x5096e8, 0x4f1cec, 0x50b218; writes 0x50aefc. Register-for-register from the listing
 * (0x4e9a30..0x4e9cf6); labels are the original addresses. */
static void run(Regs *r)
{
    push_mem(r, r->ecx);
    push_mem(r, r->esi);
    push_mem(r, r->edi);
    push_mem(r, r->ebp);
    r->ecx = r->ebx;
    if (r->eax == 0)
    {
        goto at_4e9b5b;
    }
    r->ebx = r->eax - 0x4;
    if ((uint8_t)(rd8(r, r->ebx) & 0x1) == 0)
    {
        goto at_4e9b5b;
    }
    r->edx = rd32(r, r->ebx);
    set_low8(&r->edx, (r->edx & 0xff) & 0xfe);
    r->eax = r->ebx + r->edx;
    r->esi = r->ecx;
    if ((uint8_t)(rd8(r, r->eax) & 0x1) != 0)
    {
        goto at_4e9a7b;
    }
    r->edi = rd32(r, r->eax);
    r->edx = r->edx + r->edi;
    wr32(r, r->ebx, r->edx);
    if (r->eax != rd32(r, r->ecx + 0xc))
    {
        goto at_4e9a67;
    }
    wr32(r, r->ecx + 0xc, r->ebx);
at_4e9a67:
    r->edx = rd32(r, r->eax + 0x4);
    r->eax = rd32(r, r->eax + 0x8);
    wr32(r, r->edx + 0x8, r->eax);
    wr32(r, r->eax + 0x4, r->edx);
    wr32(r, r->esi + 0x1c, rd32(r, r->esi + 0x1c) - 1);
    goto at_4e9b0f;
at_4e9a7b:
    wr32(r, r->ebx, r->edx);
    r->eax = rd32(r, r->ecx + 0xc);
    if (r->ebx >= r->eax)
    {
        goto at_4e9a9a;
    }
    if (r->ebx > rd32(r, r->eax + 0x4))
    {
        goto at_4e9b0f;
    }
    r->eax = rd32(r, r->ecx + 0x28);
    if (r->ebx < r->eax)
    {
        goto at_4e9b0f;
    }
    goto at_4e9ab3;
at_4e9a9a:
    r->eax = rd32(r, r->eax + 0x8);
    if (r->ebx < r->eax)
    {
        goto at_4e9b0f;
    }
    r->eax = r->ecx + 0x20;
    r->edx = rd32(r, r->eax + 0x4);
    if (r->ebx > r->edx)
    {
        goto at_4e9b0f;
    }
at_4e9ab3:
    r->edi = rd32(r, r->esi + 0x1c);
    r->eax = rd32(r, r->esi + 0x18);
    r->edx = 0;
    r->ecx = r->edi + 0x1;
    div32(r, r->ecx);
    r->ecx = r->eax;
    if (r->eax >= r->edi)
    {
        goto at_4e9aee;
    }
    r->eax = rd32(r, r->esi + 0x18);
    r->eax = r->eax - r->edi;
    r->ecx = r->ecx + r->ecx;
    if (r->eax > r->edi)
    {
        goto at_4e9ad6;
    }
    r->ecx = 0xffffffffu;
at_4e9ad6:
    r->eax = rd32(r, r->ebx);
    r->eax = r->eax + r->ebx;
at_4e9ada:
    r->edx = rd32(r, r->eax);
    if ((uint8_t)((r->edx & 0xff) & 0x1) == 0)
    {
        goto at_4e9b0f;
    }
    if (r->edx == 0xffffffffu)
    {
        goto at_4e9aee;
    }
    set_low8(&r->edx, (r->edx & 0xff) & 0xfe);
    r->eax = r->eax + r->edx;
    r->ecx = r->ecx - 1;
    if (r->ecx != 0 && !r->port->env.failed)
    {
        goto at_4e9ada;
    }
at_4e9aee:
    r->eax = rd32(r, r->esi + 0xc);
    if (r->ebx >= r->eax)
    {
        goto at_4e9af8;
    }
    r->eax = rd32(r, r->esi + 0x28);
at_4e9af8:
    if (r->ebx < r->eax)
    {
        goto at_4e9b0f;
    }
    r->eax = rd32(r, r->eax + 0x8);
    if (r->ebx < r->eax)
    {
        goto at_4e9b0f;
    }
    r->eax = rd32(r, r->eax + 0x8);
    if (r->ebx < r->eax)
    {
        goto at_4e9b0f;
    }
    r->eax = rd32(r, r->eax + 0x8);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4e9af8;
at_4e9b0f:
    r->edx = rd32(r, r->eax + 0x4);
    r->edi = rd32(r, r->edx);
    r->edi = r->edi + r->edx;
    r->ecx = rd32(r, r->ebx);
    if (r->edi != r->ebx)
    {
        goto at_4e9b2e;
    }
    r->ebp = rd32(r, r->edx);
    r->ecx = r->ecx + r->ebp;
    wr32(r, r->edx, r->ecx);
    if (r->ebx != rd32(r, r->esi + 0xc))
    {
        goto at_4e9b2a;
    }
    wr32(r, r->esi + 0xc, r->edx);
at_4e9b2a:
    r->ebx = r->edx;
    goto at_4e9b3d;
at_4e9b2e:
    wr32(r, r->esi + 0x1c, rd32(r, r->esi + 0x1c) + 1);
    wr32(r, r->ebx + 0x8, r->eax);
    wr32(r, r->ebx + 0x4, r->edx);
    wr32(r, r->edx + 0x8, r->ebx);
    wr32(r, r->eax + 0x4, r->ebx);
at_4e9b3d:
    r->edx = rd32(r, r->esi + 0x18);
    r->edx = r->edx - 1;
    r->edi = rd32(r, r->esi + 0xc);
    wr32(r, r->esi + 0x18, r->edx);
    if (r->ebx >= r->edi)
    {
        goto at_4e9b53;
    }
    if (r->ecx <= rd32(r, r->esi + 0x10))
    {
        goto at_4e9b53;
    }
    wr32(r, r->esi + 0x10, r->ecx);
at_4e9b53:
    if (r->ecx <= rd32(r, r->esi + 0x14))
    {
        goto at_4e9b5b;
    }
    wr32(r, r->esi + 0x14, r->ecx);
at_4e9b5b:
    r->ebp = pop_mem(r);
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    r->ecx = pop_mem(r);
    return;
    push_mem(r, r->ebx);
    push_mem(r, r->edx);
    r->edx = r->eax;
    r->eax = rd32(r, 0x50aefc);
    r->ebx = 0;
    if (r->eax == 0)
    {
        goto at_4e9b7c;
    }
at_4e9b6f:
    if (r->edx < r->eax)
    {
        goto at_4e9b7c;
    }
    r->ebx = r->eax;
    r->eax = rd32(r, r->eax + 0x8);
    if (r->eax != 0 && !r->port->env.failed)
    {
        goto at_4e9b6f;
    }
at_4e9b7c:
    wr32(r, r->edx + 0x4, r->ebx);
    wr32(r, r->edx + 0x8, r->eax);
    if (r->ebx == 0)
    {
        goto at_4e9b8b;
    }
    wr32(r, r->ebx + 0x8, r->edx);
    goto at_4e9b91;
at_4e9b8b:
    wr32(r, 0x50aefc, r->edx);
at_4e9b91:
    if (r->eax == 0)
    {
        goto at_4e9b98;
    }
    wr32(r, r->eax + 0x4, r->edx);
at_4e9b98:
    r->ebx = r->edx + 0x20;
    r->edx = r->edx + 0x2c;
    wr32(r, r->edx - 0xc, 0x0);
    wr32(r, r->edx - 0x1c, 0x0);
    wr32(r, r->edx - 0x14, 0x0);
    wr32(r, r->edx - 0x10, 0x0);
    wr32(r, r->edx - 0x8, r->ebx);
    r->eax = rd32(r, r->edx - 0x2c);
    wr32(r, r->edx - 0x4, r->ebx);
    r->eax = r->eax - 0x2c;
    wr32(r, r->edx - 0x20, r->ebx);
    wr32(r, r->edx, r->eax);
    wr32(r, r->edx + r->eax, 0xffffffffu);
    r->eax = r->edx;
    r->edx = pop_mem(r);
    r->ebx = pop_mem(r);
    return;
    push_mem(r, r->ebx);
    push_mem(r, r->ecx);
    push_mem(r, r->edx);
    push_mem(r, r->esi);
    push_mem(r, r->edi);
    r->esp = r->esp - 0x4;
    wr32(r, r->esp, r->eax);
    if (rd32(r, 0x50b214) != 0x0)
    {
        goto at_4e9bf3;
    }
    r->eax = 0;
    goto at_4e9c8b;
at_4e9bf3:
    if (rd32(r, 0x5096e8) != 0xfffffffeu)
    {
        goto at_4e9c07;
    }
    r->eax = 0;
    r->esp = r->esp + 0x4;
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    r->edx = pop_mem(r);
    r->ecx = pop_mem(r);
    r->ebx = pop_mem(r);
    return;
at_4e9c07:
    r->eax = r->esp;
    call_mem_keep(r, 0x4e9ca8, 8);
    if (r->eax == 0)
    {
        goto at_4e9c8b;
    }
    push_mem(r, 0x40);
    push_mem(r, 0x1000);
    r->ecx = rd32(r, r->esp + 0x8);
    push_mem(r, r->ecx);
    push_mem(r, 0x0);
    call_mem(r, rd32(r, 0x4f1cec), 4);
    r->edx = r->eax;
    if (r->eax == 0)
    {
        goto at_4e9c8b;
    }
    r->eax = rd32(r, r->esp);
    r->esi = rd32(r, r->esp);
    r->eax = r->eax - 0x4;
    if (r->eax <= r->esi)
    {
        goto at_4e9c49;
    }
    r->eax = 0;
    r->esp = r->esp + 0x4;
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    r->edx = pop_mem(r);
    r->ecx = pop_mem(r);
    r->ebx = pop_mem(r);
    return;
at_4e9c49:
    wr32(r, r->esp, r->eax);
    if (r->eax >= 0x38)
    {
        goto at_4e9c5c;
    }
    r->eax = 0;
    r->esp = r->esp + 0x4;
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    r->edx = pop_mem(r);
    r->ecx = pop_mem(r);
    r->ebx = pop_mem(r);
    return;
at_4e9c5c:
    wr32(r, r->edx, r->eax);
    r->eax = r->edx;
    call_mem_keep(r, 0x4e9b60, 8);
    r->ebx = r->eax;
    r->eax = rd32(r, r->eax);
    wr32(r, r->esp, r->eax);
    set_low8(&r->eax, (r->eax & 0xff) | 0x1);
    wr32(r, r->ebx, r->eax);
    r->edi = rd32(r, r->edx + 0x18);
    wr32(r, r->edx + 0x14, 0x0);
    r->edi = r->edi + 1;
    r->eax = r->ebx + 0x4;
    wr32(r, r->edx + 0x18, r->edi);
    call_mem_keep(r, 0x4ea190, 8);
    r->eax = 0x1;
at_4e9c8b:
    r->esp = r->esp + 0x4;
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    r->edx = pop_mem(r);
    r->ecx = pop_mem(r);
    r->ebx = pop_mem(r);
    return;
    push_mem(r, r->edx);
    r->edx = r->eax;
    call_mem_keep(r, 0x4e8660, 8);
    r->eax = r->edx;
    call_mem_keep(r, 0x4e9bd8, 8);
    r->edx = pop_mem(r);
    return;
    push_mem(r, r->ecx);
    push_mem(r, r->edx);
    r->edx = r->eax;
    r->eax = rd32(r, r->eax);
    r->eax = r->eax + 0x7;
    set_low8(&r->eax, (r->eax & 0xff) & 0xf8);
    if (r->eax == 0)
    {
        goto at_4e9cf4;
    }
    wr32(r, r->edx, r->eax);
    r->eax = r->eax + 0x3c;
    if (r->eax >= rd32(r, r->edx))
    {
        goto at_4e9cc5;
    }
    r->eax = 0;
    r->edx = pop_mem(r);
    r->ecx = pop_mem(r);
    return;
at_4e9cc5:
    r->ecx = rd32(r, 0x50b218);
    if (r->eax >= r->ecx)
    {
        goto at_4e9cd3;
    }
    r->eax = r->ecx;
    set_low8(&r->eax, (r->eax & 0xff) & 0xfe);
at_4e9cd3:
    wr32(r, r->edx, r->eax);
    r->eax = r->eax + 0xfff;
    if (r->eax >= rd32(r, r->edx))
    {
        goto at_4e9ce3;
    }
    r->eax = 0;
    r->edx = pop_mem(r);
    r->ecx = pop_mem(r);
    return;
at_4e9ce3:
    set_low8(&r->eax, 0);
    set_high8(&r->eax, ((r->eax >> 8) & 0xff) & 0xf0);
    wr32(r, r->edx, r->eax);
    flags(r, F_LOGIC, r->eax, 0, 32);
    set_low8(&r->eax, cond(r, CC_NE));
    r->eax = r->eax & 0xff;
at_4e9cf4:
    r->edx = pop_mem(r);
    r->ecx = pop_mem(r);
    return;
}

uint32_t vertrix_port_rtl_heap_free_block_4e9a30(PORT_SIGNATURE)
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
