#include "port_rtlfontsetmembers.h"

/* This is a flag-dispatched helper whose only caller is vertrix_port_font_set_construct (0x48b711).
 */

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

/* Original 0x47e680: This is a flag-dispatched helper whose only caller is
 * vertrix_port_font_set_construct (0x48b711). With flag bit 4 clear, it sets +0x1c8 to 0x516a54 and
 * calls import [0x4f1b3c] on globals 0x558cb4 and 0x558c9c. It then calls [0x4f1768], clears three
 * string fields starting at +0x40 with vertrix_port_string_release_variable (0x4ca210), and calls
 * 0x4ca050 if flag bit 2 is set. With bit 4 set, it instead calls lifted_rtl_block_call (0x4ccb9f)
 * with 0x516aa0, then 0x4ca040. Evidence: calls 0x4ca210, 0x4ca050, 0x4ccb9f, 0x4ca040; reads
 * 0x4f1b3c, 0x4f1768. Register-for-register from the listing (0x47e68a..0x47e77a); labels are the
 * original addresses. */
static void run(Regs *r)
{
    r->ebx = r->eax;
    wr32(r, r->ebp - 0x14, r->edx);
    set_high8(&r->eax, rd8(r, r->ebp - 0x14));
    if ((uint8_t)(((r->eax >> 8) & 0xff) & 0x4) != 0)
    {
        goto at_47e74f;
    }
    r->edx = 0x4ec1ec;
    r->ecx = 0x51689c;
    wr32(r, r->ebx + 0x1c8, 0x516a54);
    r->esi = 0x5;
    wr8(r, r->ebp - 0x1c, ((r->eax >> 8) & 0xff));
    r->eax = r->ebp - 0x34;
    wr32(r, r->ebp - 0x20, r->ebx);
    push(r, r->port->env.chain);
    wr32(r, r->eax, pop(r));
    r->port->env.chain = r->eax;
    push(r, 0x558cb4);
    wr32(r, r->ebp - 0x30, r->edx);
    wr32(r, r->ebp - 0x2c, r->ecx);
    wr32(r, r->ebp - 0x28, r->esi);
    call_all(r, rd32(r, 0x4f1b3c));
    push(r, 0x558c9c);
    r->edi = 0x4;
    call_all(r, rd32(r, 0x4f1b3c));
    call_all(r, rd32(r, 0x4f1768));
    r->eax = r->ebx + 0x40;
    r->edx = 0;
    wr32(r, r->ebp - 0x28, r->edi);
    call(r, 0x4ca210, 0);
    r->edx = 0x3;
    r->eax = r->eax - r->edi;
    wr32(r, r->ebp - 0x28, r->edx);
    r->edx = 0;
    r->ecx = 0;
    call(r, 0x4ca210, 0);
    r->eax = r->eax - 0x20;
    r->edx = 0;
    wr32(r, r->ebp - 0x28, r->ecx);
    call(r, 0x4ca210, 0);
    set_low8(&r->edx, rd8(r, r->ebp - 0x14));
    r->ebx = r->eax - 0x1c;
    wr32(r, r->ebp - 0x28, r->ecx);
    if ((uint8_t)((r->edx & 0xff) & 0x2) == 0)
    {
        goto at_47e73b;
    }
    r->eax = r->ebx;
    call(r, 0x4ca050, 0);
at_47e73b:
    r->eax = rd32(r, r->ebp - 0x34);
    r->port->env.chain = r->eax;
    r->eax = r->ebx;
    r->edi = rd32(r, r->ebp - 0x10);
    r->esi = rd32(r, r->ebp - 0xc);
    r->ecx = rd32(r, r->ebp - 0x8);
    r->ebx = rd32(r, r->ebp - 0x4);
    return;
at_47e74f:
    r->edi = 0x1;
    r->edx = 0x516aa0;
    wr32(r, r->ebp - 0x48, r->ebx);
    r->eax = r->ebx;
    wr32(r, r->ebp - 0x28, r->edi);
    call(r, 0x4ccb9f, 0);
    r->edx = 0;
    wr32(r, r->ebp - 0x28, r->edx);
    call(r, 0x4ca040, 0);
    r->eax = r->ebx;
    r->edi = rd32(r, r->ebp - 0x10);
    r->esi = rd32(r, r->ebp - 0xc);
    r->ecx = rd32(r, r->ebp - 0x8);
    r->ebx = rd32(r, r->ebp - 0x4);
    return;
}

uint32_t vertrix_port_font_set_member_construct_47e680(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x4c
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
