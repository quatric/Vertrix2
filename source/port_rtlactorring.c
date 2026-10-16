#include "port_rtlactorring.h"

/* 0x42bca0 picks one random start angle with random_below(0x168), then builds 8 actors in a single
 * loop (0x42bce1-0x42be32, ebx < 8). */

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

static void set_low16(uint32_t *reg, uint32_t value)
{
    *reg = (*reg & 0xffff0000u) | (value & 0xffff);
}

/* idiv and div of edx:eax as the original's (a zero divisor or an overflowing quotient leaves
 * both registers). */
static void idiv32(Regs *r, uint32_t value)
{
    LiftFlags flags;
    memset(&flags, 0, sizeof flags);
    lift_idiv1(32, value, &r->eax, &r->edx, &flags);
}

/* Original 0x42bca0: 0x42bca0 picks one random start angle with random_below(0x168), then builds 8
 * actors in a single loop (0x42bce1-0x42be32, ebx < 8). Each actor is a 0x15c-byte
 * vertrix_port_get_memory block passed through vertrix_port_actor_initialize and placed at owner
 * word 0xe + column*0x18+0xc and owner word 0x16 + row*0x18+0xc, where column and row are the
 * edx/ebx arguments. Each actor gets angle start+45*i in field 0x24, image 0x546500 (frame 0) when
 * random_below(0x21) returns 0 and otherwise image 0x54651c with frame result-1, speed
 * random_below(0x14)+0x50 in field 0x30, and update handler 0x443550. Each actor is then passed
 * with owner+0xcec to vertrix_port_list_delete_4b5e70. Evidence: calls 0x4826c0, 0x4ca000,
 * 0x4adf20, 0x4ac470, 0x4ac7b0, 0x4ac840, 0x4ac8d0, 0x4ac710, 0x4ac8a0, 0x4ad510, 0x4ac8f0,
 * 0x4b5e70, 0x4abd70. Register-for-register from the listing (0x42bca9..0x42be5b); labels are the
 * original addresses. */
static void run(Regs *r)
{
    wr32(r, r->ebp - 0x20, r->eax);
    r->ecx = r->edx;
    r->edx = 0x168;
    r->eax = 0x598d30;
    call(r, 0x4826c0, 0);
    r->ecx = r->ecx * 0x18;
    r->ebx = r->ebx * 0x18;
    r->eax = r->eax & 0xffff;
    wr32(r, r->ebp - 0x18, r->eax);
    r->eax = rd32(r, r->ebp - 0x20);
    r->edx = 0;
    r->eax = r->eax + 0xcec;
    wr32(r, r->ebp - 0x1c, r->edx);
    wr32(r, r->ebp - 0x24, r->eax);
    wr32(r, r->ebp - 0x10, r->ecx);
    wr32(r, r->ebp - 0x14, r->ebx);
at_42bce1:
    r->eax = 0x15c;
    call(r, 0x4ca000, 0);
    if (r->eax != 0)
    {
        goto at_42be40;
    }
at_42bcf3:
    r->esi = r->eax;
    push(r, 0x0);
    push(r, 0x0);
    push(r, 0x0);
    push(r, 0x0);
    r->eax = r->esi;
    r->ecx = 0;
    push(r, 0x0);
    r->ebx = 0;
    r->edx = 0;
    call(r, 0x4adf20, 5);
    r->eax = rd32(r, r->ebp - 0x20);
    r->edx = rd32(r, r->ebp - 0x10);
    set_low16(&r->eax, rd16(r, r->eax + 0xe));
    r->eax = r->eax + r->edx;
    r->eax = r->eax + 0xc;
    wr16(r, r->esi + 0xe, (r->eax & 0xffff));
    r->eax = rd32(r, r->ebp - 0x20);
    r->ebx = rd32(r, r->ebp - 0x14);
    set_low16(&r->eax, rd16(r, r->eax + 0x16));
    r->eax = r->eax + r->ebx;
    r->eax = r->eax + 0xc;
    r->edx = 0x4;
    wr16(r, r->esi + 0x16, (r->eax & 0xffff));
    r->eax = r->esi;
    call(r, 0x4ac470, 0);
    r->edx = 0x1;
    r->eax = r->esi;
    call(r, 0x4ac7b0, 0);
    r->edx = 0x1;
    r->eax = r->esi;
    call(r, 0x4ac840, 0);
    r->edx = 0x21;
    r->eax = 0x598d30;
    r->ecx = 0;
    call(r, 0x4826c0, 0);
    set_low16(&r->ecx, (r->eax & 0xffff));
    r->edi = r->esi;
    if (r->ecx != 0)
    {
        goto at_42be4a;
    }
    r->edx = 0x546500;
    r->eax = r->esi;
    call(r, 0x4ac8d0, 0);
    r->eax = r->esi;
    r->edx = 0;
at_42bd88:
    call(r, 0x4ac710, 0);
    r->ecx = 0x168;
    r->eax = r->edi;
    r->edx = 0;
    wr8(r, r->edi + 0x94, 0x1);
    set_low16(&r->edx, rd16(r, r->ebp - 0x18));
    call(r, 0x4ac8a0, 0);
    r->eax = r->edx;
    r->edx = (uint32_t)((int32_t)r->edx >> 0x1f);
    idiv32(r, r->ecx);
    wr8(r, r->edi + 0x95, 0x4);
    wr16(r, r->edi + 0x48, 0x0);
    wr8(r, r->edi + 0x4e, 0x32);
    r->ebx = rd32(r, r->edi + 0xc);
    wr8(r, r->edi + 0x93, 0x1);
    r->ebx = (uint32_t)((int32_t)r->ebx >> 0x10);
    r->eax = r->edi;
    r->ecx = rd32(r, r->edi + 0x14);
    wr16(r, r->edi + 0x24, (r->edx & 0xffff));
    r->ecx = (uint32_t)((int32_t)r->ecx >> 0x10);
    r->edx = 0;
    wr16(r, r->edi + 0x28, 0x0);
    call(r, 0x4ad510, 0);
    r->edx = 0x14;
    r->eax = 0x598d30;
    r->ecx = rd32(r, r->ebp - 0x18);
    r->ebx = rd32(r, r->ebp - 0x1c);
    call(r, 0x4826c0, 0);
    r->edx = 0x443550;
    r->eax = r->eax + 0x50;
    wr16(r, r->edi + 0x32, 0x2);
    r->ecx = r->ecx + 0x2d;
    wr32(r, r->edi + 0x64, 0x28);
    r->ebx = r->ebx + 1;
    wr16(r, r->edi + 0x30, (r->eax & 0xffff));
    r->eax = r->edi;
    wr32(r, r->ebp - 0x18, r->ecx);
    call(r, 0x4ac8f0, 0);
    r->eax = rd32(r, r->ebp - 0x24);
    r->edx = r->edi;
    wr32(r, r->ebp - 0x1c, r->ebx);
    call(r, 0x4b5e70, 0);
    if (r->ebx < 0x8 && !r->port->env.failed)
    {
        goto at_42bce1;
    }
    r->edi = rd32(r, r->ebp - 0xc);
    r->esi = rd32(r, r->ebp - 0x8);
    r->ecx = rd32(r, r->ebp - 0x4);
    return;
at_42be40:
    call(r, 0x4abd70, 0);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_42bcf3;
at_42be4a:
    r->edx = 0x54651c;
    r->eax = r->esi;
    call(r, 0x4ac8d0, 0);
    r->edx = r->ecx - 0x1;
    r->eax = r->esi;
    if (r->port->env.failed)
    {
        return;
    }
    goto at_42bd88;
}

uint32_t vertrix_port_board_cell_spawn_actor_ring_42bca0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x28
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
    port_set32(&port, r.ebp, -0x4u, entry->ecx);
    port_set32(&port, r.ebp, -0x8u, entry->esi);
    port_set32(&port, r.ebp, -0xcu, entry->edi);
    run(&r);
    return port_return(&port, r.eax, r.edx);
}
