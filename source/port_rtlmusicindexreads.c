#include "port_rtlmusicindexreads.h"

/* Called from vertrix_port_music_load_45f3f0 (0x45f482). */

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

static void wr32(Regs *r, uint32_t address, uint32_t value)
{
    port_set32(r->port, address, 0, value);
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

/* repne scasb: edi walked to just past the first byte equal to al (or ecx bytes). */
static void repne_scasb(Regs *r)
{
    while (r->ecx != 0 && !r->port->env.failed)
    {
        uint32_t byte = rd8(r, r->edi);
        r->ecx--;
        r->edi++;
        flags(r, F_SUB, r->eax & 0xff, byte, 8);
        if ((r->eax & 0xff) == byte)
        {
            break;
        }
    }
}

/* Original 0x487be0: Called from vertrix_port_music_load_45f3f0 (0x45f482). If lifted_f488c50
 * returns 1, it reads an 8-byte header with stream_read_exact (0x489230) and requires the first
 * dword to be 10. It stores that value at +0x10 and the entry count at +0x14. When the count is
 * nonzero, it clear-allocates three 4-byte arrays at +0x20/+0x1c/+0x18 through 0x4ec160 and fills
 * each entry from 8 bytes plus a text string (file_text_read 0x4893c0): the string goes in +0x20,
 * the second dword in +0x1c and the first in +0x18. It then returns 1. A header mismatch calls the
 * virtual error method [vmt+0x54]. If lifted_f488c50 does not return 1, the routine returns 0.
 * Evidence: calls 0x4ca070, 0x488c50, 0x489230, 0x4ec160, 0x4893c0, 0x4ca210, 0x4ea190.
 * Register-for-register from the listing (0x487bea..0x487dde); labels are the original addresses.
 */
static void run(Regs *r)
{
    r->esi = r->eax;
    r->eax = r->ebp - 0x3c;
    r->ecx = 0x4ec1ec;
    r->ebx = 0x516e8c;
    push(r, r->port->env.chain);
    wr32(r, r->eax, pop(r));
    r->port->env.chain = r->eax;
    r->edi = 0;
    r->eax = r->ebp - 0x18;
    wr32(r, r->ebp - 0x38, r->ecx);
    wr32(r, r->ebp - 0x34, r->ebx);
    wr32(r, r->ebp - 0x30, r->edi);
    call(r, 0x4ca070, 0);
    wr32(r, r->ebp - 0x30, 0x1);
    r->eax = r->esi;
    call(r, 0x488c50, 0);
    if (r->eax != 0x1)
    {
        goto at_487ce5;
    }
    r->ecx = 0x8;
    r->edx = r->ebp - 0x28;
    r->ebx = r->eax;
    r->eax = r->esi;
    call(r, 0x489230, 0);
    r->edx = rd32(r, r->ebp - 0x28);
    if (r->edx != 0xa)
    {
        goto at_487d0b;
    }
    wr32(r, r->esi + 0x10, r->edx);
    r->eax = rd32(r, r->ebp - 0x24);
    wr32(r, r->esi + 0x14, r->eax);
    if (r->eax == 0)
    {
        goto at_487ce0;
    }
    r->edx = 0x4;
    call(r, 0x4ec160, 0);
    wr32(r, r->esi + 0x20, r->eax);
    r->edx = 0x4;
    r->eax = rd32(r, r->esi + 0x14);
    call(r, 0x4ec160, 0);
    wr32(r, r->esi + 0x1c, r->eax);
    r->edx = 0x4;
    r->eax = rd32(r, r->esi + 0x14);
    wr32(r, r->ebp - 0x14, r->edi);
    call(r, 0x4ec160, 0);
    r->edi = rd32(r, r->esi + 0x14);
    wr32(r, r->esi + 0x18, r->eax);
    if (r->edi == 0)
    {
        goto at_487ce0;
    }
    r->edi = 0;
at_487c99:
    r->ecx = 0x8;
    r->ebx = 0x1;
    r->edx = r->ebp - 0x20;
    r->eax = r->esi;
    call(r, 0x489230, 0);
    r->eax = r->esi;
    call(r, 0x4893c0, 0);
    r->edx = rd32(r, r->esi + 0x20);
    wr32(r, r->edx + r->edi, r->eax);
    r->eax = rd32(r, r->esi + 0x1c);
    r->edx = r->eax + r->edi;
    r->eax = rd32(r, r->ebp - 0x1c);
    wr32(r, r->edx, r->eax);
    r->edx = rd32(r, r->esi + 0x18);
    r->eax = rd32(r, r->ebp - 0x20);
    wr32(r, r->edx + r->edi, r->eax);
    r->eax = rd32(r, r->ebp - 0x14);
    r->edi = r->edi + 0x4;
    r->eax = r->eax + 1;
    r->edx = rd32(r, r->esi + 0x14);
    wr32(r, r->ebp - 0x14, r->eax);
    if (r->eax < r->edx && !r->port->env.failed)
    {
        goto at_487c99;
    }
at_487ce0:
    r->edi = 0x1;
at_487ce5:
    r->eax = r->ebp - 0x18;
    r->ecx = 0;
    r->edx = 0;
    wr32(r, r->ebp - 0x30, r->ecx);
    call(r, 0x4ca210, 0);
    wr32(r, r->ebp - 0x30, r->ecx);
    r->eax = rd32(r, r->ebp - 0x3c);
    r->port->env.chain = r->eax;
    r->eax = r->edi;
    r->edi = rd32(r, r->ebp - 0x10);
    r->esi = rd32(r, r->ebp - 0xc);
    r->ecx = rd32(r, r->ebp - 0x8);
    r->ebx = rd32(r, r->ebp - 0x4);
    return;
at_487d0b:
    r->edx = rd32(r, r->esi);
    r->eax = r->esi;
    call_all(r, rd32(r, r->edx + 0x54));
    r->eax = r->ebp - 0x18;
    r->edx = 0;
    call(r, 0x4ca210, 0);
    r->eax = rd32(r, r->ebp - 0x3c);
    r->port->env.chain = r->eax;
    r->eax = r->edi;
    r->edi = rd32(r, r->ebp - 0x10);
    r->esi = rd32(r, r->ebp - 0xc);
    r->ecx = rd32(r, r->ebp - 0x8);
    r->ebx = rd32(r, r->ebp - 0x4);
    return;
    push(r, r->ebx);
    push(r, r->ecx);
    push(r, r->edx);
    push(r, r->esi);
    push(r, r->edi);
    r->ebx = r->eax;
    if (rd32(r, r->eax + 0x4) != 0xffffffffu)
    {
        goto at_487dcd;
    }
at_487d41:
    if (rd32(r, r->ebx + 0x10) == 0x0)
    {
        goto at_487da4;
    }
    r->esi = rd32(r, r->ebx + 0x1c);
    if (r->esi != 0)
    {
        goto at_487dd7;
    }
at_487d52:
    r->edi = rd32(r, r->ebx + 0x18);
    if (r->edi == 0)
    {
        goto at_487d60;
    }
    r->eax = r->edi;
    call(r, 0x4ea190, 0);
at_487d60:
    if (rd32(r, r->ebx + 0x20) == 0x0)
    {
        goto at_487da4;
    }
    r->edx = rd32(r, r->ebx + 0x14);
    r->esi = 0;
    if (r->edx == 0)
    {
        goto at_487d9c;
    }
    r->edx = 0;
at_487d71:
    r->eax = rd32(r, r->ebx + 0x20);
    r->eax = r->eax + r->edx;
    r->edi = rd32(r, r->eax);
    if (r->edi == 0)
    {
        goto at_487d91;
    }
    r->ecx = r->ecx - r->ecx;
    r->ecx = r->ecx - 1;
    r->eax = 0;
    repne_scasb(r);
    r->ecx = ~r->ecx;
    r->ecx = r->ecx - 1;
    r->eax = rd32(r, r->ebx + 0x20);
    r->eax = rd32(r, r->edx + r->eax);
    call(r, 0x4ea190, 0);
at_487d91:
    r->esi = r->esi + 1;
    r->ecx = rd32(r, r->ebx + 0x14);
    r->edx = r->edx + 0x4;
    if (r->esi < r->ecx && !r->port->env.failed)
    {
        goto at_487d71;
    }
at_487d9c:
    r->eax = rd32(r, r->ebx + 0x20);
    call(r, 0x4ea190, 0);
at_487da4:
    wr32(r, r->ebx + 0x10, 0x0);
    wr32(r, r->ebx + 0x14, 0x0);
    wr32(r, r->ebx + 0x18, 0x0);
    wr32(r, r->ebx + 0x1c, 0x0);
    wr32(r, r->ebx + 0x20, 0x0);
    r->edi = pop(r);
    r->esi = pop(r);
    r->edx = pop(r);
    r->ecx = pop(r);
    r->ebx = pop(r);
    return;
at_487dcd:
    r->edx = rd32(r, r->eax);
    call_all(r, rd32(r, r->edx + 0x54));
    if (r->port->env.failed)
    {
        return;
    }
    goto at_487d41;
at_487dd7:
    r->eax = r->esi;
    call(r, 0x4ea190, 0);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_487d52;
}

uint32_t vertrix_port_music_index_table_read_487be0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x40
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
