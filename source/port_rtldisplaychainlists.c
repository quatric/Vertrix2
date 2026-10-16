#include "port_rtldisplaychainlists.h"

/* Clears the global list at 0x532c04 (vertrix_port_children_release_4b7020), then takes a lock on
 * 0x558c9c (import 0x4f1b48). */

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

/* Original 0x48c4a0: Clears the global list at 0x532c04 (vertrix_port_children_release_4b7020),
 * then takes a lock on 0x558c9c (import 0x4f1b48). For each member of the object's display chain
 * (vertrix_port_display_chain_count_47f160 / vertrix_port_object_chain_member_47f260) it allocates
 * a 0x28-byte record (vertrix_port_image_record_start_4b74c0), unpacks the member's flag bits
 * (masks 0x180, 0x78, 4, 2, 1) into the record, stores the object's surface name for that index
 * (vertrix_port_surface_name_47f1b0) at +0x14 and three member dwords, and passes the record to
 * 0x4b6f70 with the list. Finally it stores the chain index (0x47f370) in 0x532c00 and the member
 * count in 0x532c18, then releases the lock (import 0x4f1c40). Evidence: calls 0x4b7020, 0x47f160,
 * 0x47f260, 0x4ca000, 0x4b74c0, 0x47f1b0, 0x4ca310, 0x4ca210, 0x4b6f70, 0x47f370; reads 0x4f1b48,
 * 0x4f1c40; writes 0x532c00, 0x532c18. Register-for-register from the listing (0x48c4ab..0x48c603);
 * labels are the original addresses. */
static void run(Regs *r)
{
    wr32(r, r->ebp - 0x18, r->eax);
    r->eax = r->ebp - 0x38;
    r->edx = 0x4ec1ec;
    r->ecx = 0x5177ac;
    push(r, r->port->env.chain);
    wr32(r, r->eax, pop(r));
    r->port->env.chain = r->eax;
    r->ebx = 0;
    r->eax = 0x532c04;
    wr32(r, r->ebp - 0x34, r->edx);
    wr32(r, r->ebp - 0x30, r->ecx);
    wr32(r, r->ebp - 0x2c, r->ebx);
    call(r, 0x4b7020, 0);
    push(r, 0x558c9c);
    call_all(r, rd32(r, 0x4f1b48));
    r->eax = rd32(r, r->ebp - 0x18);
    r->edi = 0;
    call(r, 0x47f160, 0);
    wr32(r, r->ebp - 0x24, r->eax);
    if (r->eax == 0)
    {
        goto at_48c5d0;
    }
at_48c500:
    r->eax = rd32(r, r->ebp - 0x18);
    r->edx = r->edi;
    call(r, 0x47f260, 0);
    r->esi = r->eax;
    if (r->eax == 0)
    {
        goto at_48c5c4;
    }
    r->eax = 0x28;
    call(r, 0x4ca000, 0);
    if (r->eax == 0)
    {
        goto at_48c537;
    }
    r->edx = 0x1;
    wr32(r, r->ebp - 0x1c, r->eax);
    r->ecx = 0;
    wr32(r, r->ebp - 0x2c, r->edx);
    call(r, 0x4b74c0, 0);
    wr32(r, r->ebp - 0x2c, r->ecx);
at_48c537:
    r->ecx = r->eax;
    r->eax = rd32(r, r->esi);
    r->eax = r->eax & 0x180;
    r->eax = r->eax >> 0x7;
    wr32(r, r->ecx, r->eax);
    r->eax = rd32(r, r->esi);
    r->eax = r->eax & 0x78;
    r->eax = r->eax >> 0x3;
    wr32(r, r->ecx + 0x4, r->eax);
    r->eax = rd32(r, r->esi);
    r->eax = r->eax & 0x4;
    r->eax = r->eax >> 0x2;
    wr32(r, r->ecx + 0x8, r->eax);
    r->eax = rd32(r, r->esi);
    r->eax = r->eax & 0x2;
    r->eax = r->eax >> 0x1;
    wr32(r, r->ecx + 0xc, r->eax);
    r->eax = rd32(r, r->esi);
    r->edx = r->ebp - 0x20;
    r->eax = r->eax & 0x1;
    r->ebx = r->edi;
    wr32(r, r->ecx + 0x10, r->eax);
    r->eax = rd32(r, r->ebp - 0x18);
    call(r, 0x47f1b0, 0);
    wr32(r, r->ebp - 0x2c, 0x3);
    r->ebx = r->ecx + 0x14;
    r->edx = r->eax;
    r->eax = r->ebx;
    call(r, 0x4ca310, 0);
    r->eax = 0;
    r->edx = 0;
    wr32(r, r->ebp - 0x2c, r->eax);
    r->eax = r->ebp - 0x20;
    call(r, 0x4ca210, 0);
    r->edx = 0;
    wr32(r, r->ebp - 0x2c, r->edx);
    r->eax = rd32(r, r->esi + 0x4);
    wr32(r, r->ecx + 0x1c, r->eax);
    r->eax = rd32(r, r->esi + 0x8);
    wr32(r, r->ecx + 0x20, r->eax);
    r->eax = rd32(r, r->esi + 0xc);
    r->edx = r->ecx;
    wr32(r, r->ecx + 0x18, r->eax);
    r->eax = 0x532c04;
    r->ecx = 0;
    call(r, 0x4b6f70, 0);
    wr32(r, r->ebp - 0x2c, r->ecx);
at_48c5c4:
    r->esi = rd32(r, r->ebp - 0x24);
    r->edi = r->edi + 1;
    if (r->edi < r->esi && !r->port->env.failed)
    {
        goto at_48c500;
    }
at_48c5d0:
    r->eax = rd32(r, r->ebp - 0x18);
    call(r, 0x47f370, 0);
    wr32(r, 0x532c00, r->eax);
    r->eax = rd32(r, r->ebp - 0x24);
    push(r, 0x558c9c);
    wr32(r, 0x532c18, r->eax);
    call_all(r, rd32(r, 0x4f1c40));
    r->eax = rd32(r, r->ebp - 0x38);
    r->port->env.chain = r->eax;
    r->edi = rd32(r, r->ebp - 0x14);
    r->esi = rd32(r, r->ebp - 0x10);
    r->edx = rd32(r, r->ebp - 0xc);
    r->ecx = rd32(r, r->ebp - 0x8);
    r->ebx = rd32(r, r->ebp - 0x4);
    return;
}

uint32_t vertrix_port_display_chain_list_rebuild_48c4a0(PORT_SIGNATURE)
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
