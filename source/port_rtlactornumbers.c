#include "port_rtlactornumbers.h"

/* Stores edx as the actor's number at +0x180 and formats it with vertrix_port_rtl_print_4cdfb0
 * (0x4cdfb0), using format 0x5110a8. */

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

/* The last count values pushed dropped (the caller's add esp). */
static void drop(Regs *r, unsigned count)
{
    r->pushed = count < r->pushed ? r->pushed - count : 0;
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

/* A cdecl call: every value pushed passed, left for the caller to drop. */
static void call_cdecl(Regs *r, uint32_t target)
{
    call_with_stack(r, target, r->pushed, 1);
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

/* Original 0x4b58a0: Stores edx as the actor's number at +0x180 and formats it with
 * vertrix_port_rtl_print_4cdfb0 (0x4cdfb0), using format 0x5110a8. If flag +0x184 is 1, it uses
 * format 0x5110a2 and builds the text by repeating constant 0x5110a6 until it reaches width +0x188,
 * then appending the formatted number (0x4b59d4-0x4b59f6). If +0x190 and the value are both 0, it
 * replaces the text with constant 0x5110ab. It passes the result to vertrix_port_actor_set_text
 * (0x4b65d0) with the actor's +0x15d and +0x160..+0x166 fields. Its callers are
 * number_player_update/field, number_owner_grow, board_clear_marked_extra and game_screen.
 * Evidence: calls 0x4ca070, 0x4cdfb0, 0x4ca370, 0x4b65d0, 0x4ca210, 0x4ca600, 0x4ca650.
 * Register-for-register from the listing (0x4b58aa..0x4b5a14); labels are the original addresses.
 */
static void run(Regs *r)
{
    r->esi = r->eax;
    r->eax = r->ebp - 0x2c;
    r->ecx = 0x4ec1ec;
    r->ebx = 0x5181ec;
    push(r, r->port->env.chain);
    wr32(r, r->eax, pop(r));
    r->port->env.chain = r->eax;
    r->edi = 0;
    r->eax = r->ebp - 0x18;
    wr32(r, r->ebp - 0x28, r->ecx);
    wr32(r, r->ebp - 0x24, r->ebx);
    wr32(r, r->ebp - 0x20, r->edi);
    call(r, 0x4ca070, 0);
    r->eax = 0x1;
    wr32(r, r->ebp - 0x20, r->eax);
    wr32(r, r->esi + 0x180, r->edx);
    if (r->eax == rd32(r, r->esi + 0x184))
    {
        goto at_4b598a;
    }
    r->ecx = rd32(r, r->esi + 0x180);
    push(r, r->ecx);
    push(r, 0x5110a8);
    r->eax = r->ebp - 0x18;
    push(r, r->eax);
    call_cdecl(r, 0x4cdfb0);
    drop(r, 3);
at_4b590d:
    if (rd32(r, r->esi + 0x190) != 0x0)
    {
        goto at_4b592c;
    }
    if (rd32(r, r->esi + 0x180) != 0x0)
    {
        goto at_4b592c;
    }
    r->edx = 0x5110ab;
    r->eax = r->ebp - 0x18;
    call(r, 0x4ca370, 0);
at_4b592c:
    r->eax = rd32(r, r->esi + 0x166);
    r->eax = (uint32_t)((int32_t)r->eax >> 0x10);
    push(r, r->eax);
    r->eax = rd32(r, r->esi + 0x164);
    r->edx = rd32(r, r->ebp - 0x18);
    r->eax = (uint32_t)((int32_t)r->eax >> 0x10);
    r->ecx = rd32(r, r->esi + 0x160);
    push(r, r->eax);
    r->eax = rd32(r, r->esi + 0x162);
    r->ebx = rd32(r, r->esi + 0x15d);
    r->eax = (uint32_t)((int32_t)r->eax >> 0x10);
    r->ecx = (uint32_t)((int32_t)r->ecx >> 0x10);
    push(r, r->eax);
    r->ebx = (uint32_t)((int32_t)r->ebx >> 0x18);
    r->eax = r->esi;
    call(r, 0x4b65d0, 3);
    r->eax = r->ebp - 0x18;
    r->esi = 0;
    r->edx = 0;
    wr32(r, r->ebp - 0x20, r->esi);
    call(r, 0x4ca210, 0);
    r->eax = rd32(r, r->ebp - 0x2c);
    wr32(r, r->ebp - 0x20, r->esi);
    r->port->env.chain = r->eax;
    r->edi = rd32(r, r->ebp - 0x10);
    r->esi = rd32(r, r->ebp - 0xc);
    r->ecx = rd32(r, r->ebp - 0x8);
    r->ebx = rd32(r, r->ebp - 0x4);
    return;
at_4b598a:
    r->eax = r->ebp - 0x14;
    r->ebx = 0x2;
    call(r, 0x4ca070, 0);
    wr32(r, r->ebp - 0x20, r->ebx);
    r->edi = rd32(r, r->esi + 0x180);
    push(r, r->edi);
    push(r, 0x5110a2);
    r->eax = r->ebp - 0x14;
    push(r, r->eax);
    call_cdecl(r, 0x4cdfb0);
    drop(r, 3);
    r->edx = 0x5110a5;
    r->eax = r->ebp - 0x18;
    call(r, 0x4ca370, 0);
    r->eax = rd32(r, r->ebp - 0x14);
    r->eax = r->eax - 0xc;
    r->eax = rd32(r, r->eax + 0x4);
    r->ecx = rd32(r, r->esi + 0x188);
    r->ebx = r->eax;
    if (r->ecx <= r->eax)
    {
        goto at_4b59f0;
    }
at_4b59d4:
    r->edx = 0x5110a6;
    r->eax = r->ebp - 0x18;
    r->ecx = r->ecx - 1;
    call(r, 0x4ca600, 0);
    if (r->ecx > r->ebx && !r->port->env.failed)
    {
        goto at_4b59d4;
    }
at_4b59f0:
    r->edx = r->ebp - 0x14;
    r->eax = r->ebp - 0x18;
    call(r, 0x4ca650, 0);
    r->eax = 0x1;
    r->edx = 0;
    wr32(r, r->ebp - 0x20, r->eax);
    r->eax = r->ebp - 0x14;
    call(r, 0x4ca210, 0);
    wr32(r, r->ebp - 0x20, 0x1);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4b590d;
}

uint32_t vertrix_port_actor_set_number_text_4b58a0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x30
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
