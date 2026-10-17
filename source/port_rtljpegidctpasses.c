#include "port_rtljpegidctpasses.h"

/* libjpeg start_pass for the inverse DCT: picks each component's IDCT by its scaled size (1x1, 2x2,
 * 4x4, or 8x8 by the DCT method) and copies its quantisation table into the multiplier table. */

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

static uint32_t rd16(Regs *r, uint32_t address)
{
    return port_u16(r->port, address, 0);
}

static uint32_t rd32(Regs *r, uint32_t address)
{
    return port_u32(r->port, address, 0);
}

static void wr32(Regs *r, uint32_t address, uint32_t value)
{
    port_set32(r->port, address, 0, value);
}

static void set_low16(uint32_t *reg, uint32_t value)
{
    *reg = (*reg & 0xffff0000u) | (value & 0xffff);
}

/* An indirect call (an import or a method): every value pushed passed and popped, as stdcall. */
static void call_all(Regs *r, uint32_t target)
{
    call_with_stack(r, target, r->pushed, 0);
}

/* Original 0x4bb870: libjpeg start_pass for the inverse DCT: picks each component's IDCT by its
 * scaled size (1x1, 2x2, 4x4, or 8x8 by the DCT method) and copies its quantisation table into the
 * multiplier table. Evidence: no calls. Register-for-register from the listing
 * (0x4bb87b..0x4bb99c); labels are the original addresses. */
static void run(Regs *r)
{
    r->esi = r->eax;
    r->edx = 0;
    r->eax = rd32(r, r->eax + 0x1c0);
    wr32(r, r->ebp - 0x18, r->edx);
    wr32(r, r->ebp - 0x1c, r->edx);
    wr32(r, r->ebp - 0x24, r->edx);
    r->edx = rd32(r, r->esi + 0x24);
    r->edi = rd32(r, r->esi + 0xd8);
    if ((int32_t)r->edx <= 0)
    {
        goto at_4bb8f4;
    }
    wr32(r, r->ebp - 0x20, r->eax);
at_4bb89e:
    r->eax = rd32(r, r->edi + 0x24);
    r->eax = r->eax - 1;
    if (r->eax > 0x7)
    {
        goto at_4bb939;
    }
    switch (r->eax)
    {
        case 0:
            goto at_4bb8b2;
        case 1:
            goto at_4bb8fe;
        case 2:
            goto at_4bb939;
        case 3:
            goto at_4bb90d;
        case 4:
            goto at_4bb939;
        case 5:
            goto at_4bb939;
        case 6:
            goto at_4bb939;
        case 7:
            goto at_4bb921;
        default:
            r->port->env.failed = 1;
            return;
    }
at_4bb8b2:
    r->eax = 0x4c4cc0;
at_4bb8b7:
    r->edx = 0;
    wr32(r, r->ebp - 0x1c, r->eax);
    wr32(r, r->ebp - 0x18, r->edx);
at_4bb8bf:
    r->edx = rd32(r, r->ebp - 0x20);
    r->eax = rd32(r, r->ebp - 0x1c);
    wr32(r, r->edx + 0x4, r->eax);
    if (rd32(r, r->edi + 0x30) == 0x0)
    {
        goto at_4bb8da;
    }
    r->ebx = rd32(r, r->ebp - 0x18);
    if (r->ebx != rd32(r, r->edx + 0x2c))
    {
        goto at_4bb955;
    }
at_4bb8da:
    r->ecx = rd32(r, r->ebp - 0x20);
    r->ebx = rd32(r, r->ebp - 0x24);
    r->edi = r->edi + 0x54;
    r->edx = rd32(r, r->esi + 0x24);
    r->ecx = r->ecx + 0x4;
    r->ebx = r->ebx + 1;
    wr32(r, r->ebp - 0x20, r->ecx);
    wr32(r, r->ebp - 0x24, r->ebx);
    if ((int32_t)r->ebx < (int32_t)r->edx && !r->port->env.failed)
    {
        goto at_4bb89e;
    }
at_4bb8f4:
    r->edi = rd32(r, r->ebp - 0x14);
    r->esi = rd32(r, r->ebp - 0x10);
    r->edx = rd32(r, r->ebp - 0xc);
    r->ecx = rd32(r, r->ebp - 0x8);
    r->ebx = rd32(r, r->ebp - 0x4);
    return;
at_4bb8fe:
    r->ecx = 0x4c4b00;
    r->ebx = 0;
    wr32(r, r->ebp - 0x1c, r->ecx);
    wr32(r, r->ebp - 0x18, r->ebx);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4bb8bf;
at_4bb90d:
    r->eax = 0x4c4730;
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4bb8b7;
at_4bb914:
    r->ecx = 0x4c4000;
    wr32(r, r->ebp - 0x18, r->eax);
    wr32(r, r->ebp - 0x1c, r->ecx);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4bb8bf;
at_4bb921:
    r->eax = rd32(r, r->esi + 0x48);
    if (r->eax == 0 && !r->port->env.failed)
    {
        goto at_4bb914;
    }
    r->eax = rd32(r, r->esi);
    wr32(r, r->eax + 0x14, 0x30);
    r->edx = rd32(r, r->esi);
    r->eax = r->esi;
    call_all(r, rd32(r, r->edx));
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4bb8bf;
at_4bb939:
    r->eax = rd32(r, r->esi);
    wr32(r, r->eax + 0x14, 0x7);
    r->eax = rd32(r, r->esi);
    r->edx = rd32(r, r->edi + 0x24);
    wr32(r, r->eax + 0x18, r->edx);
    r->edx = rd32(r, r->esi);
    r->eax = r->esi;
    call_all(r, rd32(r, r->edx));
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4bb8bf;
at_4bb955:
    r->ebx = rd32(r, r->edi + 0x4c);
    if (r->ebx == 0 && !r->port->env.failed)
    {
        goto at_4bb8da;
    }
    r->eax = rd32(r, r->ebp - 0x18);
    wr32(r, r->edx + 0x2c, r->eax);
    if (r->eax != 0)
    {
        goto at_4bb98d;
    }
    r->eax = r->ebx;
    r->edx = rd32(r, r->edi + 0x50);
    r->ebx = r->ebx + 0x80;
at_4bb975:
    r->ecx = 0;
    r->edx = r->edx + 0x4;
    set_low16(&r->ecx, rd16(r, r->eax));
    r->eax = r->eax + 0x2;
    wr32(r, r->edx - 0x4, r->ecx);
    if (r->eax == r->ebx && !r->port->env.failed)
    {
        goto at_4bb8da;
    }
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4bb975;
at_4bb98d:
    r->eax = rd32(r, r->esi);
    wr32(r, r->eax + 0x14, 0x30);
    r->edx = rd32(r, r->esi);
    r->eax = r->esi;
    call_all(r, rd32(r, r->edx));
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4bb8da;
}

uint32_t vertrix_port_jpeg_idct_start_pass_4bb870(PORT_SIGNATURE)
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
    port_set32(&port, r.ebp, -0x4u, entry->ebx);
    port_set32(&port, r.ebp, -0x8u, entry->ecx);
    port_set32(&port, r.ebp, -0xcu, entry->edx);
    port_set32(&port, r.ebp, -0x10u, entry->esi);
    port_set32(&port, r.ebp, -0x14u, entry->edi);
    run(&r);
    return port_return(&port, r.eax, r.edx);
}
