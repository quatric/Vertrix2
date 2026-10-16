#include "port_rtlheadsanims.h"

/* For the set index in eax, 0x41e310 reads the count at 0x53969c and returns early if it is 1 or
 * less. */

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

/* Original 0x41e310: For the set index in eax, 0x41e310 reads the count at 0x53969c and returns
 * early if it is 1 or less. Otherwise it allocates count-1 bank slots (0x45ea60). For each head
 * entry that does not match the string at 0x50dd31, it joins the names from the tables at 0x534f5c
 * and 0x53612c with '.\IMAGE\HEADS\' (0x4fc9c8) and opens the pair with 0x423dc0. It stores the
 * result through table_fill_indexed_b (0x45e9e0) and frees it with 0x478d80. It then joins each of
 * the 0x534f10[idx] entries from 0x534920 with '.\ANIM\' (0x4fd100), reads that file with
 * settings_file_read (0x48a050) and allocates a bank table (0x45e950). It parses an integer pair
 * from each list slot and stores it with grid_cell_call (0x45e990). The callers are
 * scores_screen_setup_41acc0, world_screen_setup_421be0, 0x41b310 and 0x41cc30. Evidence: calls
 * 0x489f90, 0x45ea60, 0x4ccfe0, 0x45f540, 0x423dc0, 0x45e9e0, 0x478d80, 0x48a050, 0x48a2e0,
 * 0x45e950, 0x48a300, 0x4d6710, 0x4ca210, 0x45e990, 0x489fa0, 0x48a2d0. Register-for-register from
 * the listing (0x41e31e..0x41e5d7); labels are the original addresses. */
static void run(Regs *r)
{
    wr32(r, r->ebp - 0x1c, r->eax);
    r->eax = r->ebp - 0x58;
    r->edx = 0x4ec1ec;
    r->ecx = 0x5140a0;
    r->esi = 0x1;
    push(r, r->port->env.chain);
    wr32(r, r->eax, pop(r));
    r->port->env.chain = r->eax;
    r->ebx = 0;
    r->eax = r->ebp - 0x70;
    wr32(r, r->ebp - 0x50, r->ecx);
    r->ecx = rd32(r, r->ebp - 0x1c);
    wr32(r, r->ebp - 0x54, r->edx);
    r->ecx = r->ecx << 0x2;
    wr32(r, r->ebp - 0x4c, r->ebx);
    call(r, 0x489f90, 0);
    r->edi = rd32(r, r->ecx + 0x53969c);
    wr32(r, r->ebp - 0x4c, r->esi);
    if (r->edi <= r->esi)
    {
        goto at_41e571;
    }
    r->eax = r->edi;
    r->eax = r->eax - r->esi;
    wr32(r, r->ebp - 0x34, r->eax);
    r->edx = r->eax;
    r->eax = rd32(r, r->ebp - 0x1c);
    call(r, 0x45ea60, 0);
    r->eax = rd32(r, r->ebp - 0x34);
    r->edi = 0;
    if (r->eax == 0)
    {
        goto at_41e462;
    }
    r->eax = rd32(r, r->ebp - 0x1c);
    r->eax = r->eax << 0x4;
    r->edx = r->eax;
    r->eax = r->eax << 0x4;
    r->eax = r->eax - r->edx;
    wr32(r, r->ebp - 0x24, r->eax);
    r->eax = 0x534f5c;
    r->eax = r->eax + rd32(r, r->ebp - 0x24);
    r->eax = r->eax + 0x4;
    wr32(r, r->ebp - 0x3c, r->ecx);
    wr32(r, r->ebp - 0x2c, r->eax);
at_41e3ab:
    r->eax = r->edi * 4;
    wr32(r, r->ebp - 0x30, r->eax);
    r->ecx = r->eax + 0x4;
    r->eax = rd32(r, r->ebp - 0x2c);
    r->edx = 0x50dd31;
    r->eax = rd32(r, r->eax);
    call(r, 0x4ccfe0, 0);
    if (r->eax == 0)
    {
        goto at_41e44d;
    }
    r->eax = 0x534f5c;
    r->eax = r->eax + rd32(r, r->ebp - 0x24);
    r->edx = 0x4fc9c8;
    r->ebx = rd32(r, r->ecx + r->eax);
    r->eax = r->ebp - 0x174;
    r->esi = rd32(r, r->ebp - 0x24);
    call(r, 0x45f540, 0);
    r->eax = 0x53612c;
    r->eax = r->eax + r->esi;
    r->edx = 0x4fc9c8;
    r->ebx = rd32(r, r->ecx + r->eax);
    r->eax = r->ebp - 0x278;
    call(r, 0x45f540, 0);
    r->ebx = rd32(r, r->ebp - 0x3c);
    r->edx = r->ebp - 0x278;
    r->eax = r->ebp - 0x174;
    r->ebx = rd32(r, r->ebx + 0x5347f0);
    call(r, 0x423dc0, 0);
    r->esi = r->eax;
    if (r->eax == 0)
    {
        goto at_41e44d;
    }
    r->eax = rd32(r, r->ebp - 0x24);
    r->eax = r->eax + rd32(r, r->ebp - 0x30);
    r->ebx = r->esi;
    r->ecx = rd32(r, r->eax + 0x5384d0);
    r->edx = r->edi;
    push(r, r->ecx);
    r->ecx = rd32(r, r->eax + 0x537300);
    r->eax = rd32(r, r->ebp - 0x1c);
    call(r, 0x45e9e0, 0);
    r->eax = r->esi;
    call(r, 0x478d80, 0);
at_41e44d:
    r->edx = rd32(r, r->ebp - 0x2c);
    r->ecx = rd32(r, r->ebp - 0x34);
    r->edx = r->edx + 0x4;
    r->edi = r->edi + 1;
    wr32(r, r->ebp - 0x2c, r->edx);
    if (r->edi < r->ecx && !r->port->env.failed)
    {
        goto at_41e3ab;
    }
at_41e462:
    r->ebx = 0;
    wr32(r, r->ebp - 0x18, r->ebx);
    r->ebx = rd32(r, r->ebp - 0x1c);
    r->ebx = r->ebx << 0x2;
    r->eax = rd32(r, r->ebx + 0x534f10);
    wr32(r, r->ebp - 0x38, r->eax);
    if (r->eax == 0)
    {
        goto at_41e5b1;
    }
    r->eax = rd32(r, r->ebp - 0x1c);
    r->eax = r->eax << 0x2;
    r->edx = r->eax;
    r->eax = r->eax << 0x3;
    r->eax = r->eax - r->edx;
    r->edx = 0x544d7c;
    r->ebx = r->ebx + 0x534920;
    r->edx = r->edx + r->eax;
    wr32(r, r->ebp - 0x28, r->ebx);
    wr32(r, r->ebp - 0x20, r->edx);
at_41e49e:
    r->ebx = rd32(r, r->ebp - 0x28);
    r->edx = 0x4fd100;
    r->eax = r->ebp - 0x174;
    r->ebx = rd32(r, r->ebx);
    call(r, 0x45f540, 0);
    r->edx = r->ebp - 0x174;
    r->eax = r->ebp - 0x70;
    call(r, 0x48a050, 0);
    r->eax = r->ebp - 0x70;
    r->edx = rd32(r, r->ebp - 0x18);
    call(r, 0x48a2e0, 0);
    r->ebx = r->eax;
    r->eax = rd32(r, r->ebp - 0x1c);
    r->esi = 0;
    call(r, 0x45e950, 0);
at_41e4d8:
    r->eax = r->ebp - 0x70;
    call(r, 0x48a2e0, 0);
    if (r->esi >= r->eax)
    {
        goto at_41e58e;
    }
    r->edx = r->ebp - 0x44;
    r->eax = r->ebp - 0x70;
    r->ebx = r->esi;
    r->ecx = 0;
    call(r, 0x48a300, 0);
    wr32(r, r->ebp - 0x4c, 0x2);
    r->ebx = 0x1;
    r->eax = rd32(r, r->eax);
    r->edx = 0;
    call(r, 0x4d6710, 0);
    r->ecx = r->ebx;
    r->edi = r->eax;
    r->eax = r->ebp - 0x44;
    wr32(r, r->ebp - 0x4c, r->ebx);
    call(r, 0x4ca210, 0);
    r->edx = r->ebp - 0x40;
    r->eax = r->ebp - 0x70;
    wr32(r, r->ebp - 0x4c, r->ebx);
    r->ebx = r->esi;
    call(r, 0x48a300, 0);
    wr32(r, r->ebp - 0x4c, 0x4);
    r->eax = rd32(r, r->eax);
    r->ebx = 0x1;
    call(r, 0x4d6710, 0);
    r->edx = 0;
    r->ecx = r->eax;
    r->eax = r->ebp - 0x40;
    wr32(r, r->ebp - 0x4c, r->ebx);
    call(r, 0x4ca210, 0);
    r->edx = rd32(r, r->ebp - 0x18);
    push(r, r->ecx);
    r->eax = rd32(r, r->ebp - 0x1c);
    wr32(r, r->ebp - 0x4c, r->ebx);
    push(r, r->edi);
    r->ecx = rd32(r, r->ebp - 0x20);
    r->ebx = r->esi;
    call(r, 0x45e990, 0);
    r->edx = 0x1;
    wr32(r, r->ebp - 0x4c, r->edx);
    r->esi = r->esi + r->edx;
    if (r->port->env.failed)
    {
        return;
    }
    goto at_41e4d8;
at_41e571:
    r->eax = r->ebp - 0x70;
    r->edx = 0;
    call(r, 0x489fa0, 0);
    r->eax = rd32(r, r->ebp - 0x58);
    r->port->env.chain = r->eax;
    r->edi = rd32(r, r->ebp - 0x14);
    r->esi = rd32(r, r->ebp - 0x10);
    r->edx = rd32(r, r->ebp - 0xc);
    r->ecx = rd32(r, r->ebp - 0x8);
    r->ebx = rd32(r, r->ebp - 0x4);
    return;
at_41e58e:
    r->eax = r->ebp - 0x70;
    r->ebx = rd32(r, r->ebp - 0x28);
    r->esi = rd32(r, r->ebp - 0x18);
    r->edi = rd32(r, r->ebp - 0x38);
    call(r, 0x48a2d0, 0);
    r->ebx = r->ebx + 0x4c;
    r->esi = r->esi + 1;
    wr32(r, r->ebp - 0x28, r->ebx);
    wr32(r, r->ebp - 0x18, r->esi);
    if (r->esi < r->edi && !r->port->env.failed)
    {
        goto at_41e49e;
    }
at_41e5b1:
    r->eax = 0;
    r->edx = 0;
    wr32(r, r->ebp - 0x4c, r->eax);
    r->eax = r->ebp - 0x70;
    call(r, 0x489fa0, 0);
    r->edx = 0;
    wr32(r, r->ebp - 0x4c, r->edx);
    r->eax = rd32(r, r->ebp - 0x58);
    r->port->env.chain = r->eax;
    r->edi = rd32(r, r->ebp - 0x14);
    r->esi = rd32(r, r->ebp - 0x10);
    r->edx = rd32(r, r->ebp - 0xc);
    r->ecx = rd32(r, r->ebp - 0x8);
    r->ebx = rd32(r, r->ebp - 0x4);
    return;
}

uint32_t vertrix_port_heads_anims_load_41e310(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x27c
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
