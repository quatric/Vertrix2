#include "port_rtljpegsofmarkers.h"

/* libjpeg get_sof: reads a start-of-frame marker (precision, image size, components and their
 * sampling factors and quantisation tables). */

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

/* Original 0x4be0b0: libjpeg get_sof: reads a start-of-frame marker (precision, image size,
 * components and their sampling factors and quantisation tables). Evidence: no calls.
 * Register-for-register from the listing (0x4be0b9..0x4be46d); labels are the original addresses.
 */
static void run(Regs *r)
{
    r->ecx = r->eax;
    r->eax = rd32(r, r->eax + 0x18);
    wr32(r, r->ebp - 0x14, r->eax);
    r->esi = rd32(r, r->ebp - 0x14);
    r->eax = rd32(r, r->eax);
    r->esi = rd32(r, r->esi + 0x4);
    wr32(r, r->ecx + 0xdc, r->edx);
    wr32(r, r->ebp - 0x10, r->eax);
    wr32(r, r->ecx + 0xe0, r->ebx);
    if (r->esi == 0)
    {
        goto at_4be350;
    }
at_4be0e0:
    r->eax = rd32(r, r->ebp - 0x10);
    r->ebx = 0;
    set_low8(&r->ebx, rd8(r, r->eax));
    r->edx = r->eax + 0x1;
    r->ebx = r->ebx << 0x8;
    wr32(r, r->ebp - 0x10, r->edx);
    r->esi = r->esi - 1;
    if (r->esi == 0)
    {
        goto at_4be369;
    }
at_4be0f7:
    r->edx = rd32(r, r->ebp - 0x10);
    r->esi = r->esi - 1;
    r->eax = 0;
    r->edi = r->edx + 0x1;
    set_low8(&r->eax, rd8(r, r->edx));
    wr32(r, r->ebp - 0x10, r->edi);
    r->ebx = r->ebx + r->eax;
    if (r->esi == 0)
    {
        goto at_4be382;
    }
at_4be10f:
    r->edx = rd32(r, r->ebp - 0x10);
    r->eax = 0;
    set_low8(&r->eax, rd8(r, r->edx));
    wr32(r, r->ecx + 0xd4, r->eax);
    r->eax = r->edx + 0x1;
    wr32(r, r->ebp - 0x10, r->eax);
    r->esi = r->esi - 1;
    if (r->esi == 0)
    {
        goto at_4be39b;
    }
at_4be129:
    r->edx = rd32(r, r->ebp - 0x10);
    r->eax = 0;
    r->esi = r->esi - 1;
    set_low8(&r->eax, rd8(r, r->edx));
    r->edx = r->edx + 1;
    r->eax = r->eax << 0x8;
    wr32(r, r->ebp - 0x10, r->edx);
    wr32(r, r->ecx + 0x20, r->eax);
    if (r->esi == 0)
    {
        goto at_4be3b4;
    }
at_4be143:
    r->edx = rd32(r, r->ebp - 0x10);
    r->eax = 0;
    r->edi = r->edx + 0x1;
    set_low8(&r->eax, rd8(r, r->edx));
    r->edx = rd32(r, r->ecx + 0x20);
    r->esi = r->esi - 1;
    r->edx = r->edx + r->eax;
    wr32(r, r->ebp - 0x10, r->edi);
    wr32(r, r->ecx + 0x20, r->edx);
    if (r->esi == 0)
    {
        goto at_4be3cd;
    }
at_4be161:
    r->edx = rd32(r, r->ebp - 0x10);
    r->eax = 0;
    set_low8(&r->eax, rd8(r, r->edx));
    r->edi = r->edx + 0x1;
    r->eax = r->eax << 0x8;
    wr32(r, r->ebp - 0x10, r->edi);
    wr32(r, r->ecx + 0x1c, r->eax);
    r->esi = r->esi - 1;
    if (r->esi == 0)
    {
        goto at_4be3ea;
    }
at_4be17b:
    r->edx = rd32(r, r->ebp - 0x10);
    r->esi = r->esi - 1;
    r->eax = 0;
    r->edi = rd32(r, r->ecx + 0x1c);
    set_low8(&r->eax, rd8(r, r->edx));
    r->edx = r->edx + 1;
    r->edi = r->edi + r->eax;
    wr32(r, r->ebp - 0x10, r->edx);
    wr32(r, r->ecx + 0x1c, r->edi);
    if (r->esi != 0)
    {
        goto at_4be1ab;
    }
    r->edx = rd32(r, r->ebp - 0x14);
    r->eax = r->ecx;
    call_all(r, rd32(r, r->edx + 0xc));
    if (r->eax == 0)
    {
        goto at_4be348;
    }
    r->eax = rd32(r, r->edx);
    r->esi = rd32(r, r->edx + 0x4);
    wr32(r, r->ebp - 0x10, r->eax);
at_4be1ab:
    r->edx = rd32(r, r->ebp - 0x10);
    r->eax = 0;
    set_low8(&r->eax, rd8(r, r->edx));
    wr32(r, r->ecx + 0x24, r->eax);
    r->edx = r->edx + 1;
    r->eax = rd32(r, r->ecx);
    wr32(r, r->ebp - 0x10, r->edx);
    r->edx = rd32(r, r->ecx + 0x1a0);
    wr32(r, r->eax + 0x18, r->edx);
    r->edx = rd32(r, r->ecx + 0x1c);
    wr32(r, r->eax + 0x1c, r->edx);
    r->edx = rd32(r, r->ecx + 0x20);
    wr32(r, r->eax + 0x20, r->edx);
    r->edx = rd32(r, r->ecx + 0x24);
    wr32(r, r->eax + 0x24, r->edx);
    r->eax = rd32(r, r->ecx);
    wr32(r, r->eax + 0x14, 0x64);
    r->edi = rd32(r, r->ecx);
    r->edx = 0x1;
    r->eax = r->ecx;
    call_all(r, rd32(r, r->edi + 0x4));
    r->eax = rd32(r, r->ecx + 0x1b8);
    r->esi = r->esi - 1;
    r->edi = rd32(r, r->eax + 0x10);
    r->ebx = r->ebx - 0x8;
    if (r->edi == 0)
    {
        goto at_4be20b;
    }
    r->eax = rd32(r, r->ecx);
    wr32(r, r->eax + 0x14, 0x3a);
    r->edx = rd32(r, r->ecx);
    r->eax = r->ecx;
    call_all(r, rd32(r, r->edx));
at_4be20b:
    if (rd32(r, r->ecx + 0x20) <= 0x0)
    {
        goto at_4be407;
    }
    if (rd32(r, r->ecx + 0x1c) <= 0x0)
    {
        goto at_4be407;
    }
    if ((int32_t)rd32(r, r->ecx + 0x24) <= (int32_t)0x0)
    {
        goto at_4be407;
    }
at_4be229:
    r->edx = rd32(r, r->ecx + 0x24);
    r->eax = r->edx * 4;
    r->eax = r->eax - r->edx;
    if (r->ebx == r->eax)
    {
        goto at_4be248;
    }
    r->eax = rd32(r, r->ecx);
    wr32(r, r->eax + 0x14, 0xb);
    r->edx = rd32(r, r->ecx);
    r->eax = r->ecx;
    call_all(r, rd32(r, r->edx));
at_4be248:
    if (rd32(r, r->ecx + 0xd8) != 0x0)
    {
        goto at_4be277;
    }
    r->edx = rd32(r, r->ecx + 0x24);
    r->ebx = r->edx * 4;
    r->ebx = r->ebx + r->edx;
    r->eax = r->ecx;
    r->ebx = r->ebx << 0x2;
    r->edi = rd32(r, r->ecx + 0x4);
    r->ebx = r->ebx + r->edx;
    r->edx = 0x1;
    r->ebx = r->ebx << 0x2;
    call_all(r, rd32(r, r->edi));
    wr32(r, r->ecx + 0xd8, r->eax);
at_4be277:
    r->ebx = rd32(r, r->ecx + 0xd8);
    r->edx = 0;
    r->edi = rd32(r, r->ecx + 0x24);
    wr32(r, r->ebp - 0x18, r->edx);
    if ((int32_t)r->edi <= 0)
    {
        goto at_4be32b;
    }
at_4be28d:
    r->eax = rd32(r, r->ebp - 0x18);
    wr32(r, r->ebx + 0x4, r->eax);
    if (r->esi == 0)
    {
        goto at_4be41b;
    }
at_4be29b:
    r->edx = rd32(r, r->ebp - 0x10);
    r->eax = 0;
    r->edi = r->edx + 0x1;
    set_low8(&r->eax, rd8(r, r->edx));
    wr32(r, r->ebp - 0x10, r->edi);
    wr32(r, r->ebx, r->eax);
    r->esi = r->esi - 1;
    if (r->esi == 0)
    {
        goto at_4be438;
    }
at_4be2b1:
    r->edx = rd32(r, r->ebp - 0x10);
    r->eax = 0;
    set_low8(&r->eax, rd8(r, r->edx));
    r->esi = r->esi - 1;
    r->edx = r->eax;
    r->eax = r->eax & 0xf;
    r->edx = (uint32_t)((int32_t)r->edx >> 0x4);
    wr32(r, r->ebx + 0xc, r->eax);
    r->eax = rd32(r, r->ebp - 0x10);
    r->edx = r->edx & 0xf;
    r->eax = r->eax + 1;
    wr32(r, r->ebx + 0x8, r->edx);
    wr32(r, r->ebp - 0x10, r->eax);
    if (r->esi == 0)
    {
        goto at_4be455;
    }
at_4be2d9:
    r->edx = rd32(r, r->ebp - 0x10);
    r->eax = 0;
    set_low8(&r->eax, rd8(r, r->edx));
    wr32(r, r->ebx + 0x10, r->eax);
    r->edx = r->edx + 1;
    r->eax = rd32(r, r->ecx);
    wr32(r, r->ebp - 0x10, r->edx);
    r->edx = rd32(r, r->ebx);
    wr32(r, r->eax + 0x18, r->edx);
    r->edx = rd32(r, r->ebx + 0x8);
    wr32(r, r->eax + 0x1c, r->edx);
    r->edx = rd32(r, r->ebx + 0xc);
    wr32(r, r->eax + 0x20, r->edx);
    r->edx = rd32(r, r->ebx + 0x10);
    wr32(r, r->eax + 0x24, r->edx);
    r->eax = rd32(r, r->ecx);
    wr32(r, r->eax + 0x14, 0x65);
    r->edx = 0x1;
    r->edi = rd32(r, r->ecx);
    r->eax = r->ecx;
    r->esi = r->esi - 1;
    call_all(r, rd32(r, r->edi + 0x4));
    r->edi = rd32(r, r->ebp - 0x18);
    r->ebx = r->ebx + 0x54;
    r->edi = r->edi + 1;
    r->edx = rd32(r, r->ecx + 0x24);
    wr32(r, r->ebp - 0x18, r->edi);
    if ((int32_t)r->edi < (int32_t)r->edx && !r->port->env.failed)
    {
        goto at_4be28d;
    }
at_4be32b:
    r->eax = rd32(r, r->ecx + 0x1b8);
    wr32(r, r->eax + 0x10, 0x1);
    r->eax = rd32(r, r->ebp - 0x14);
    r->edx = rd32(r, r->ebp - 0x10);
    wr32(r, r->eax, r->edx);
    wr32(r, r->eax + 0x4, r->esi);
    r->eax = 0x1;
at_4be348:
    r->edi = rd32(r, r->ebp - 0xc);
    r->esi = rd32(r, r->ebp - 0x8);
    r->ecx = rd32(r, r->ebp - 0x4);
    return;
at_4be350:
    r->edx = rd32(r, r->ebp - 0x14);
    r->eax = r->ecx;
    call_all(r, rd32(r, r->edx + 0xc));
    if (r->eax == 0 && !r->port->env.failed)
    {
        goto at_4be348;
    }
    r->eax = rd32(r, r->edx);
    r->esi = rd32(r, r->edx + 0x4);
    wr32(r, r->ebp - 0x10, r->eax);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4be0e0;
at_4be369:
    r->edx = rd32(r, r->ebp - 0x14);
    r->eax = r->ecx;
    call_all(r, rd32(r, r->edx + 0xc));
    if (r->eax == 0 && !r->port->env.failed)
    {
        goto at_4be348;
    }
    r->eax = rd32(r, r->edx);
    r->esi = rd32(r, r->edx + 0x4);
    wr32(r, r->ebp - 0x10, r->eax);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4be0f7;
at_4be382:
    r->edx = rd32(r, r->ebp - 0x14);
    r->eax = r->ecx;
    call_all(r, rd32(r, r->edx + 0xc));
    if (r->eax == 0 && !r->port->env.failed)
    {
        goto at_4be348;
    }
    r->eax = rd32(r, r->edx);
    r->esi = rd32(r, r->edx + 0x4);
    wr32(r, r->ebp - 0x10, r->eax);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4be10f;
at_4be39b:
    r->edx = rd32(r, r->ebp - 0x14);
    r->eax = r->ecx;
    call_all(r, rd32(r, r->edx + 0xc));
    if (r->eax == 0 && !r->port->env.failed)
    {
        goto at_4be348;
    }
    r->eax = rd32(r, r->edx);
    r->esi = rd32(r, r->edx + 0x4);
    wr32(r, r->ebp - 0x10, r->eax);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4be129;
at_4be3b4:
    r->edx = rd32(r, r->ebp - 0x14);
    r->eax = r->ecx;
    call_all(r, rd32(r, r->edx + 0xc));
    if (r->eax == 0 && !r->port->env.failed)
    {
        goto at_4be348;
    }
    r->eax = rd32(r, r->edx);
    r->esi = rd32(r, r->edx + 0x4);
    wr32(r, r->ebp - 0x10, r->eax);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4be143;
at_4be3cd:
    r->edx = rd32(r, r->ebp - 0x14);
    r->eax = r->ecx;
    call_all(r, rd32(r, r->edx + 0xc));
    if (r->eax == 0 && !r->port->env.failed)
    {
        goto at_4be348;
    }
    r->eax = rd32(r, r->edx);
    r->esi = rd32(r, r->edx + 0x4);
    wr32(r, r->ebp - 0x10, r->eax);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4be161;
at_4be3ea:
    r->edx = rd32(r, r->ebp - 0x14);
    r->eax = r->ecx;
    call_all(r, rd32(r, r->edx + 0xc));
    if (r->eax == 0 && !r->port->env.failed)
    {
        goto at_4be348;
    }
    r->eax = rd32(r, r->edx);
    r->esi = rd32(r, r->edx + 0x4);
    wr32(r, r->ebp - 0x10, r->eax);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4be17b;
at_4be407:
    r->eax = rd32(r, r->ecx);
    wr32(r, r->eax + 0x14, 0x20);
    r->edx = rd32(r, r->ecx);
    r->eax = r->ecx;
    call_all(r, rd32(r, r->edx));
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4be229;
at_4be41b:
    r->edx = rd32(r, r->ebp - 0x14);
    r->eax = r->ecx;
    call_all(r, rd32(r, r->edx + 0xc));
    if (r->eax == 0 && !r->port->env.failed)
    {
        goto at_4be348;
    }
    r->eax = rd32(r, r->edx);
    r->esi = rd32(r, r->edx + 0x4);
    wr32(r, r->ebp - 0x10, r->eax);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4be29b;
at_4be438:
    r->edx = rd32(r, r->ebp - 0x14);
    r->eax = r->ecx;
    call_all(r, rd32(r, r->edx + 0xc));
    if (r->eax == 0 && !r->port->env.failed)
    {
        goto at_4be348;
    }
    r->eax = rd32(r, r->edx);
    r->esi = rd32(r, r->edx + 0x4);
    wr32(r, r->ebp - 0x10, r->eax);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4be2b1;
at_4be455:
    r->edx = rd32(r, r->ebp - 0x14);
    r->eax = r->ecx;
    call_all(r, rd32(r, r->edx + 0xc));
    if (r->eax == 0 && !r->port->env.failed)
    {
        goto at_4be348;
    }
    r->eax = rd32(r, r->edx);
    r->esi = rd32(r, r->edx + 0x4);
    wr32(r, r->ebp - 0x10, r->eax);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4be2d9;
}

uint32_t vertrix_port_jpeg_get_sof_4be0b0(PORT_SIGNATURE)
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
    port_set32(&port, r.ebp, -0x4u, entry->ecx);
    port_set32(&port, r.ebp, -0x8u, entry->esi);
    port_set32(&port, r.ebp, -0xcu, entry->edi);
    run(&r);
    return port_return(&port, r.eax, r.edx);
}
