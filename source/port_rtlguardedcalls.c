#include "port_rtlguardedcalls.h"

/* 0x489a10 sets up a try frame with vertrix_port_thread_chain_push (0x4d93f0) and
 * lifted_rtl_jump_capture (0x4d9f06), then calls virtual method [vtable+0x38] on the object passed
 * in eax (0x489ad2) and returns its result. */

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

static void wr32(Regs *r, uint32_t address, uint32_t value)
{
    port_set32(r->port, address, 0, value);
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

/* Original 0x489a10: 0x489a10 sets up a try frame with vertrix_port_thread_chain_push (0x4d93f0)
 * and lifted_rtl_jump_capture (0x4d9f06), then calls virtual method [vtable+0x38] on the object
 * passed in eax (0x489ad2) and returns its result. If an exception is caught and its field +8 is
 * nonzero, it builds text with vertrix_port_error_kind_text_488d80 (kind 4), releases that string
 * at once with 0x4ca210 without showing it, and returns 0. The handler then calls
 * lifted_exception_chain_step (0x4da6b6). Its only caller is vertrix_port_resource_load_48a710
 * (0x48a797). Evidence: calls 0x4d93f0, 0x4d9f06, 0x488d80, 0x4ca210, 0x4da6b6, 0x4d9430.
 * Register-for-register from the listing (0x489a1b..0x489b12); labels are the original addresses.
 */
static void run(Regs *r)
{
    r->edx = r->eax;
    r->eax = r->ebp - 0x40;
    r->ecx = 0x4ec1ec;
    r->ebx = 0x517210;
    r->edi = 0x2;
    push(r, r->port->env.chain);
    wr32(r, r->eax, pop(r));
    r->port->env.chain = r->eax;
    r->esi = 0;
    r->eax = r->ebp - 0x2c;
    wr32(r, r->ebp - 0x3c, r->ecx);
    wr32(r, r->ebp - 0x38, r->ebx);
    wr32(r, r->ebp - 0x34, r->esi);
    call(r, 0x4d93f0, 0);
    r->eax = r->ebp - 0x74;
    wr32(r, r->ebp - 0x34, r->edi);
    call(r, 0x4d9f06, 0);
    if (r->eax != 0x1)
    {
        goto at_489ace;
    }
    wr32(r, r->ebp - 0x34, 0x4);
    r->eax = rd32(r, r->ebp - 0x18);
    wr32(r, r->ebp - 0x28, r->eax);
    if (rd32(r, r->eax + 0x8) == 0x0)
    {
        goto at_489a96;
    }
    r->edx = r->eax;
    r->eax = r->ebp - 0x24;
    r->ecx = 0x4;
    call(r, 0x488d80, 0);
    r->eax = r->ebp - 0x24;
    r->edx = 0;
    wr32(r, r->ebp - 0x34, r->ecx);
    call(r, 0x4ca210, 0);
    wr32(r, r->ebp - 0x1c, r->esi);
    wr32(r, r->ebp - 0x34, r->ecx);
at_489a96:
    r->edi = 0x2;
    call(r, 0x4da6b6, 0);
    wr32(r, r->ebp - 0x34, r->edi);
at_489aa3:
    r->eax = 0;
    wr32(r, r->ebp - 0x34, r->eax);
    call(r, 0x4d9430, 0);
    r->edx = 0;
    wr32(r, r->ebp - 0x34, r->edx);
    r->eax = rd32(r, r->ebp - 0x1c);
    wr32(r, r->ebp - 0x20, r->eax);
    r->eax = rd32(r, r->ebp - 0x40);
    r->port->env.chain = r->eax;
    r->eax = rd32(r, r->ebp - 0x20);
    r->edi = rd32(r, r->ebp - 0x14);
    r->esi = rd32(r, r->ebp - 0x10);
    r->edx = rd32(r, r->ebp - 0xc);
    r->ecx = rd32(r, r->ebp - 0x8);
    r->ebx = rd32(r, r->ebp - 0x4);
    return;
at_489ace:
    r->ecx = rd32(r, r->edx);
    r->eax = r->edx;
    call_all(r, rd32(r, r->ecx + 0x38));
    wr32(r, r->ebp - 0x1c, r->eax);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_489aa3;
    push(r, r->ebx);
    push(r, r->ecx);
    push(r, r->edx);
    r->ecx = rd32(r, r->eax);
    r->ebx = 0;
    r->edx = 0;
    call_all(r, rd32(r, r->ecx + 0x30));
    r->eax = 0;
    r->edx = pop(r);
    r->ecx = pop(r);
    r->ebx = pop(r);
    return;
    push(r, r->ebx);
    push(r, r->ecx);
    push(r, r->edx);
    r->ecx = rd32(r, r->eax);
    r->ebx = 0x2;
    r->edx = 0;
    call_all(r, rd32(r, r->ecx + 0x30));
    r->edx = pop(r);
    r->ecx = pop(r);
    r->ebx = pop(r);
    return;
}

uint32_t vertrix_port_guarded_method38_call_489a10(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x78
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
