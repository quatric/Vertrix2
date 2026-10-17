#include "port_rtljpegbitbuffers.h"

/* libjpeg jpeg_fill_bit_buffer: loads bytes into the Huffman bit buffer, refilling the source and
 * stopping at a marker; past a marker it pads with zeros and warns once. */

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

/* An indirect call (an import or a method): every value pushed passed and popped, as stdcall. */
static void call_all(Regs *r, uint32_t target)
{
    call_with_stack(r, target, r->pushed, 0);
}

/* Original 0x4bbf30: libjpeg jpeg_fill_bit_buffer: loads bytes into the Huffman bit buffer,
 * refilling the source and stopping at a marker; past a marker it pads with zeros and warns once.
 * Evidence: no calls. Register-for-register from the listing (0x4bbf38..0x4bc049); labels are the
 * original addresses. */
static void run(Regs *r)
{
    wr32(r, r->ebp - 0x14, r->eax);
    wr32(r, r->ebp - 0x10, r->edx);
    wr32(r, r->ebp - 0xc, r->ebx);
    wr32(r, r->ebp - 0x18, r->ecx);
    r->ecx = rd32(r, r->eax + 0x10);
    r->esi = rd32(r, r->eax);
    r->edx = rd32(r, r->ecx + 0x1a0);
    r->ebx = rd32(r, r->eax + 0x4);
    if (r->edx != 0)
    {
        goto at_4bbfd6;
    }
    r->edi = 0xff;
at_4bbf5f:
    if ((int32_t)rd32(r, r->ebp - 0xc) >= (int32_t)0x19)
    {
        goto at_4bc004;
    }
    if (r->ebx == 0)
    {
        goto at_4bbfb6;
    }
at_4bbf6d:
    r->eax = 0;
    r->ebx = r->ebx - 1;
    set_low8(&r->eax, rd8(r, r->esi));
    r->esi = r->esi + 1;
    if (r->eax != 0xff)
    {
        goto at_4bbfa5;
    }
at_4bbf7a:
    if (r->ebx != 0)
    {
        goto at_4bbf92;
    }
    r->ebx = rd32(r, r->ecx + 0x18);
    r->eax = r->ecx;
    call_all(r, rd32(r, r->ebx + 0xc));
    if (r->eax == 0)
    {
        goto at_4bbf24;
    }
    r->ebx = rd32(r, r->ecx + 0x18);
    r->esi = rd32(r, r->ebx);
    r->ebx = rd32(r, r->ebx + 0x4);
at_4bbf92:
    r->eax = 0;
    r->ebx = r->ebx - 1;
    set_low8(&r->eax, rd8(r, r->esi));
    r->esi = r->esi + 1;
    if (r->eax == 0xff && !r->port->env.failed)
    {
        goto at_4bbf7a;
    }
    if (r->eax != 0)
    {
        goto at_4bbfd0;
    }
    r->eax = r->edi;
at_4bbfa5:
    r->edx = rd32(r, r->ebp - 0x10);
    r->edx = r->edx << 0x8;
    r->edx = r->edx | r->eax;
    wr32(r, r->ebp - 0x10, r->edx);
    wr32(r, r->ebp - 0xc, rd32(r, r->ebp - 0xc) + 0x8);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4bbf5f;
at_4bbfb6:
    r->ebx = rd32(r, r->ecx + 0x18);
    r->eax = r->ecx;
    call_all(r, rd32(r, r->ebx + 0xc));
    if (r->eax == 0)
    {
        goto at_4bbf24;
    }
    r->ebx = rd32(r, r->ecx + 0x18);
    r->esi = rd32(r, r->ebx);
    r->ebx = rd32(r, r->ebx + 0x4);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4bbf6d;
at_4bbfd0:
    wr32(r, r->ecx + 0x1a0, r->eax);
at_4bbfd6:
    r->eax = rd32(r, r->ebp - 0x18);
    if ((int32_t)r->eax <= (int32_t)rd32(r, r->ebp - 0xc))
    {
        goto at_4bc004;
    }
    r->eax = rd32(r, r->ecx + 0x1bc);
    if (rd32(r, r->eax + 0x8) == 0x0)
    {
        goto at_4bc027;
    }
at_4bbfea:
    r->ecx = 0x19;
    r->edi = rd32(r, r->ebp - 0xc);
    r->eax = rd32(r, r->ebp - 0x10);
    r->ecx = r->ecx - r->edi;
    r->edx = 0x19;
    r->eax = r->eax << (r->ecx & 0xff);
    wr32(r, r->ebp - 0xc, r->edx);
    wr32(r, r->ebp - 0x10, r->eax);
at_4bc004:
    r->eax = rd32(r, r->ebp - 0x14);
    wr32(r, r->eax, r->esi);
    r->edx = rd32(r, r->ebp - 0x14);
    wr32(r, r->eax + 0x4, r->ebx);
    r->eax = rd32(r, r->ebp - 0x10);
    wr32(r, r->edx + 0x8, r->eax);
    r->eax = rd32(r, r->ebp - 0xc);
    wr32(r, r->edx + 0xc, r->eax);
    r->eax = 0x1;
    r->edi = rd32(r, r->ebp - 0x8);
    r->esi = rd32(r, r->ebp - 0x4);
    return;
at_4bc027:
    r->eax = rd32(r, r->ecx);
    wr32(r, r->eax + 0x14, 0x75);
    r->edi = rd32(r, r->ecx);
    r->edx = 0xffffffffu;
    r->eax = r->ecx;
    call_all(r, rd32(r, r->edi + 0x4));
    r->eax = rd32(r, r->ecx + 0x1bc);
    wr32(r, r->eax + 0x8, 0x1);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4bbfea;
at_4bbf24:
    r->edi = rd32(r, r->ebp - 0x8);
    r->esi = rd32(r, r->ebp - 0x4);
    return;
}

uint32_t vertrix_port_jpeg_fill_bit_buffer_4bbf30(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x1c
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
    port_set32(&port, r.ebp, -0x4u, entry->esi);
    port_set32(&port, r.ebp, -0x8u, entry->edi);
    run(&r);
    return port_return(&port, r.eax, r.edx);
}
