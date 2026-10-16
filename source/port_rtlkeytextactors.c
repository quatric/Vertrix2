#include "port_rtlkeytextactors.h"

/* Constructor at 0x4b4cf0. */

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

static void set_high8(uint32_t *reg, uint32_t value)
{
    *reg = (*reg & 0xffff00ffu) | ((value & 0xff) << 8);
}

/* The last value pushed taken back. */
static uint32_t pop(Regs *r)
{
    return r->pushed != 0 ? r->stack[--r->pushed] : 0;
}

/* Original 0x4b4cf0: Constructor at 0x4b4cf0. It calls vertrix_port_text_actor_construct
 * (0x4b3100), stores the pointer 0x5180f4 at +0x158 and zeroes +0x170 to +0x178. It then allocates
 * three 0x160-byte children with get_memory, builds each with vertrix_port_key_actor_construct
 * (0x4b5400) using kinds 2, 4 and 6 (the 4 is loaded into ebx), and stores them at +0x17c, +0x184
 * and +0x180. Each child is passed through actor_initialize (0x4adf20) and actor_place_size
 * (0x4b54d0). It zeroes +0x188 to +0x194 and returns the object; the reported only caller is
 * menu_item_construct (0x460a26). Evidence: calls 0x4b3100, 0x4ca000, 0x4adf20, 0x4b54d0, 0x4b5400.
 * Register-for-register from the listing (0x4b4cfb..0x4b4e9a); labels are the original addresses.
 */
static void run(Regs *r)
{
    r->esi = r->eax;
    r->eax = r->ebp - 0x38;
    r->edx = 0x4ec1ec;
    r->ecx = 0x518050;
    r->edi = 0x1;
    push(r, r->port->env.chain);
    wr32(r, r->eax, pop(r));
    r->port->env.chain = r->eax;
    r->ebx = 0;
    wr32(r, r->ebp - 0x34, r->edx);
    wr32(r, r->ebp - 0x30, r->ecx);
    set_high8(&r->eax, 0);
    wr32(r, r->ebp - 0x2c, r->ebx);
    wr8(r, r->ebp - 0x20, ((r->eax >> 8) & 0xff));
    r->eax = r->esi;
    wr32(r, r->ebp - 0x24, r->esi);
    call(r, 0x4b3100, 0);
    wr32(r, r->ebp - 0x2c, r->edi);
    wr32(r, r->eax + 0x158, 0x5180f4);
    wr32(r, r->eax + 0x170, r->ebx);
    wr32(r, r->eax + 0x174, r->ebx);
    r->esi = r->eax;
    wr32(r, r->eax + 0x178, r->ebx);
    r->eax = 0x160;
    call(r, 0x4ca000, 0);
    if (r->eax != 0)
    {
        goto at_4b4e6a;
    }
at_4b4d6b:
    push(r, 0x0);
    push(r, 0x0);
    push(r, 0x0);
    push(r, 0x0);
    r->ecx = 0;
    r->ebx = 0;
    push(r, 0x0);
    r->edx = 0;
    wr32(r, r->esi + 0x17c, r->eax);
    call(r, 0x4adf20, 5);
    push(r, 0x0);
    r->eax = rd32(r, r->esi + 0x17c);
    r->ecx = 0;
    r->ebx = 0;
    r->edx = 0;
    call(r, 0x4b54d0, 1);
    r->eax = 0x160;
    call(r, 0x4ca000, 0);
    if (r->eax == 0)
    {
        goto at_4b4dbf;
    }
    r->ebx = 0x4;
    r->edi = 0x1;
    wr32(r, r->ebp - 0x18, r->eax);
    wr32(r, r->ebp - 0x2c, r->ebx);
    call(r, 0x4b5400, 0);
    wr32(r, r->ebp - 0x2c, r->edi);
at_4b4dbf:
    push(r, 0x0);
    push(r, 0x0);
    push(r, 0x0);
    push(r, 0x0);
    r->ecx = 0;
    r->ebx = 0;
    push(r, 0x0);
    r->edx = 0;
    wr32(r, r->esi + 0x184, r->eax);
    call(r, 0x4adf20, 5);
    push(r, 0x0);
    r->eax = rd32(r, r->esi + 0x184);
    r->ecx = 0;
    r->ebx = 0;
    r->edx = 0;
    call(r, 0x4b54d0, 1);
    r->eax = 0x160;
    call(r, 0x4ca000, 0);
    if (r->eax != 0)
    {
        goto at_4b4e82;
    }
at_4b4dff:
    push(r, 0x0);
    push(r, 0x0);
    push(r, 0x0);
    push(r, 0x0);
    r->ecx = 0;
    r->ebx = 0;
    push(r, 0x0);
    r->edx = 0;
    wr32(r, r->esi + 0x180, r->eax);
    call(r, 0x4adf20, 5);
    push(r, 0x0);
    r->eax = rd32(r, r->esi + 0x180);
    r->ecx = 0;
    r->ebx = 0;
    r->edx = 0;
    call(r, 0x4b54d0, 1);
    wr32(r, r->esi + 0x188, 0x0);
    wr32(r, r->esi + 0x18c, 0x0);
    wr32(r, r->esi + 0x190, 0x0);
    wr32(r, r->esi + 0x194, 0x0);
    r->eax = rd32(r, r->ebp - 0x38);
    r->port->env.chain = r->eax;
    r->eax = r->esi;
    r->edi = rd32(r, r->ebp - 0x14);
    r->esi = rd32(r, r->ebp - 0x10);
    r->edx = rd32(r, r->ebp - 0xc);
    r->ecx = rd32(r, r->ebp - 0x8);
    r->ebx = rd32(r, r->ebp - 0x4);
    return;
at_4b4e6a:
    r->edx = 0x2;
    wr32(r, r->ebp - 0x18, r->eax);
    wr32(r, r->ebp - 0x2c, r->edx);
    call(r, 0x4b5400, 0);
    wr32(r, r->ebp - 0x2c, r->edi);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4b4d6b;
at_4b4e82:
    r->edx = 0x6;
    r->ecx = 0x1;
    wr32(r, r->ebp - 0x18, r->eax);
    wr32(r, r->ebp - 0x2c, r->edx);
    call(r, 0x4b5400, 0);
    wr32(r, r->ebp - 0x2c, r->ecx);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4b4dff;
}

uint32_t vertrix_port_key_text_actor_construct_4b4cf0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x3c
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
