#include "port_rtlaiboardcompares.h"

/* Prepares the AI board comparison for a player: copies the 0x41-byte boards (+0x1de) of the player
 * and its opponent into the frame, stores the choice grid values (0x429e80), sets the mode flags
 * (0x427e10), compares the two boards (0x428110) and passes the players' speeds and positions on.
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

/* The last value pushed taken back. */
static uint32_t pop(Regs *r)
{
    return r->pushed != 0 ? r->stack[--r->pushed] : 0;
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

/* Original 0x427850: Prepares the AI board comparison for a player: copies the 0x41-byte boards
 * (+0x1de) of the player and its opponent into the frame, stores the choice grid values (0x429e80),
 * sets the mode flags (0x427e10), compares the two boards (0x428110) and passes the players' speeds
 * and positions on. Evidence: calls 0x432820, 0x429e80, 0x427e10, 0x428110, 0x427c10, 0x4288d0,
 * 0x428e70. Register-for-register from the listing (0x42785d..0x4279a5); labels are the original
 * addresses. */
static void run(Regs *r)
{
    wr32(r, r->ebp - 0x14, r->eax);
    wr32(r, r->ebp - 0x18, r->edx);
    r->esi = rd32(r, r->ebp - 0x18);
    r->eax = rd32(r, r->edx + 0x3b0);
    r->ecx = 0x41;
    wr32(r, r->ebp - 0x1c, r->eax);
    r->esi = rd32(r, r->esi + 0x15c);
    r->edx = rd32(r, r->eax + 0x15c);
    r->eax = r->esi;
    r->edi = r->ebp - 0x94;
    call_keep(r, 0x432820);
    r->eax = r->edx;
    r->esi = r->esi + 0x1de;
    call_keep(r, 0x432820);
    push(r, r->edi);
    r->eax = r->ecx;
    r->ecx = r->ecx >> 0x2;
    rep_movs(r, 4);
    set_low8(&r->ecx, (r->eax & 0xff));
    set_low8(&r->ecx, (r->ecx & 0xff) & 0x3);
    rep_movs(r, 1);
    r->edi = pop(r);
    r->ecx = 0x41;
    r->edi = r->ebp - 0xd8;
    r->esi = r->edx + 0x1de;
    push(r, r->edi);
    r->eax = r->ecx;
    r->ecx = r->ecx >> 0x2;
    rep_movs(r, 4);
    set_low8(&r->ecx, (r->eax & 0xff));
    set_low8(&r->ecx, (r->ecx & 0xff) & 0x3);
    rep_movs(r, 1);
    r->edi = pop(r);
    r->eax = rd32(r, r->ebp - 0x18);
    r->edx = r->ebp - 0x148;
    r->eax = rd32(r, r->eax + 0x3b8);
    r->esi = rd32(r, r->ebp - 0x14);
    call_keep(r, 0x429e80);
    r->esi = r->esi + 0x1c5;
    r->edx = rd32(r, r->ebp - 0x18);
    r->eax = rd32(r, r->ebp - 0x14);
    r->ebx = r->esi;
    call_keep(r, 0x427e10);
    r->ecx = r->esi;
    r->ebx = r->ebp - 0xd8;
    r->edx = r->ebp - 0x94;
    r->eax = rd32(r, r->ebp - 0x14);
    call_keep(r, 0x428110);
    r->eax = rd32(r, r->ebp - 0x14);
    r->edx = rd32(r, r->eax + 0x164);
    r->eax = rd32(r, r->ebp - 0x1c);
    push(r, r->esi);
    r->eax = rd32(r, r->eax + 0x180);
    push(r, r->edx);
    r->eax = r->eax - 0xc;
    push(r, r->eax);
    r->eax = rd32(r, r->ebp - 0x18);
    r->eax = rd32(r, r->eax + 0x180);
    r->eax = r->eax - 0xc;
    push(r, r->eax);
    r->eax = rd32(r, r->ebp - 0x1c);
    r->edx = rd32(r, r->ebp - 0x18);
    r->ecx = rd32(r, r->eax + 0x178);
    r->edx = rd32(r, r->edx + 0x17c);
    push(r, r->ecx);
    r->ecx = rd32(r, r->ebp - 0x18);
    r->ebx = rd32(r, r->eax + 0x17c);
    r->eax = rd32(r, r->ebp - 0x14);
    r->ecx = rd32(r, r->ecx + 0x178);
    r->edi = rd32(r, r->ebp - 0x14);
    call(r, 0x427c10, 5);
    r->eax = rd32(r, r->ebp - 0x14);
    r->edi = r->edi + 0x1f4;
    r->ebx = rd32(r, r->eax + 0x160);
    r->edx = rd32(r, r->ebp - 0x18);
    push(r, r->ebx);
    r->eax = r->ebp - 0x50;
    r->ecx = r->esi;
    push(r, r->eax);
    r->ebx = r->edi;
    r->eax = rd32(r, r->ebp - 0x14);
    call(r, 0x4288d0, 2);
    r->eax = rd32(r, r->ebp - 0x14);
    r->esi = rd32(r, r->eax + 0x160);
    r->ecx = r->ebp - 0x148;
    push(r, r->esi);
    r->edx = r->edi;
    r->ebx = r->eax + 0x210;
    call(r, 0x428e70, 1);
    r->edi = rd32(r, r->ebp - 0x10);
    r->esi = rd32(r, r->ebp - 0xc);
    r->ecx = rd32(r, r->ebp - 0x8);
    r->ebx = rd32(r, r->ebp - 0x4);
    return;
}

uint32_t vertrix_port_ai_compare_player_boards_427850(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x14c
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
