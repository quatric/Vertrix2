#include "port_rtljpegquantizers.h"

/* At 0x4c6c80, libjpeg's jinit_1pass_quantizer: it allocates a 0x58-byte quantizer object through
 * the memory manager, stores it at cinfo+0x1cc and sets its methods to 0x4c6a20, 0x4c6a80 and
 * 0x4c6c70. */

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

/* idiv and div of edx:eax as the original's (a zero divisor or an overflowing quotient leaves
 * both registers). */
static void idiv32(Regs *r, uint32_t value)
{
    LiftFlags flags;
    memset(&flags, 0, sizeof flags);
    lift_idiv1(32, value, &r->eax, &r->edx, &flags);
}

/* An indirect call (an import or a method): every value pushed passed and popped, as stdcall. */
static void call_all(Regs *r, uint32_t target)
{
    call_with_stack(r, target, r->pushed, 0);
}

/* Original 0x4c6c80: At 0x4c6c80, libjpeg's jinit_1pass_quantizer: it allocates a 0x58-byte
 * quantizer object through the memory manager, stores it at cinfo+0x1cc and sets its methods to
 * 0x4c6a20, 0x4c6a80 and 0x4c6c70. It raises errors when out_color_components (+0x78) exceeds 4 or
 * desired colours (+0x60) exceeds 256, then picks per-component colour counts (error 0x38 below 2,
 * trace 0x5e for 3 components) and allocates the colormap via mem+8. It builds the colour index
 * through 0x4c6020 and, when dither mode (+0x2c) is 2 (Floyd-Steinberg), allocates the error
 * workspace through 0x4c69c0. Evidence: calls 0x4c6020, 0x4c69c0. Register-for-register from the
 * listing (0x4c6c8b..0x4c6fe6); labels are the original addresses. */
static void run(Regs *r)
{
    wr32(r, r->ebp - 0x5c, r->eax);
    r->ecx = rd32(r, r->eax + 0x4);
    r->ebx = 0x58;
    r->edx = 0x1;
    call_all(r, rd32(r, r->ecx));
    r->edx = rd32(r, r->ebp - 0x5c);
    wr32(r, r->edx + 0x1cc, r->eax);
    wr32(r, r->eax, 0x4c6a20);
    wr32(r, r->eax + 0x8, 0x4c6a80);
    wr32(r, r->eax + 0xc, 0x4c6c70);
    wr32(r, r->eax + 0x44, 0x0);
    wr32(r, r->eax + 0x34, 0x0);
    if ((int32_t)rd32(r, r->edx + 0x78) > (int32_t)0x4)
    {
        goto at_4c6f49;
    }
at_4c6cd2:
    r->eax = rd32(r, r->ebp - 0x5c);
    if ((int32_t)rd32(r, r->eax + 0x60) > (int32_t)0x100)
    {
        goto at_4c6f70;
    }
at_4c6ce2:
    r->eax = rd32(r, r->ebp - 0x5c);
    wr32(r, r->ebp - 0x58, r->eax);
    r->eax = rd32(r, r->eax + 0x1cc);
    r->edx = rd32(r, r->ebp - 0x5c);
    wr32(r, r->ebp - 0x64, r->eax);
    r->eax = r->eax + 0x20;
    r->ebx = 0x1;
    wr32(r, r->ebp - 0x4c, r->eax);
    r->eax = rd32(r, r->edx + 0x78);
    wr32(r, r->ebp - 0x48, r->edx);
    wr32(r, r->ebp - 0x34, r->eax);
    r->ecx = r->ebx;
    r->edi = rd32(r, r->ebp - 0x34);
    r->eax = rd32(r, r->edx + 0x60);
    r->esi = rd32(r, r->ebp - 0x34);
    wr32(r, r->ebp - 0x44, r->eax);
at_4c6d16:
    r->ebx = r->ebx + 1;
    r->eax = r->ecx;
    r->edx = r->ebx;
    if ((int32_t)r->ecx >= (int32_t)r->esi)
    {
        goto at_4c6d27;
    }
at_4c6d1f:
    r->edx = r->edx * r->ebx;
    r->eax = r->eax + 1;
    if ((int32_t)r->eax < (int32_t)r->edi && !r->port->env.failed)
    {
        goto at_4c6d1f;
    }
at_4c6d27:
    if ((int32_t)r->edx <= (int32_t)rd32(r, r->ebp - 0x44) && !r->port->env.failed)
    {
        goto at_4c6d16;
    }
    r->ebx = r->ebx - 1;
    if ((int32_t)r->ebx >= (int32_t)0x2)
    {
        goto at_4c6d50;
    }
    r->eax = rd32(r, r->ebp - 0x48);
    r->eax = rd32(r, r->eax);
    wr32(r, r->eax + 0x14, 0x38);
    r->eax = rd32(r, r->ebp - 0x48);
    r->eax = rd32(r, r->eax);
    wr32(r, r->eax + 0x18, r->edx);
    r->edx = rd32(r, r->ebp - 0x48);
    r->edx = rd32(r, r->edx);
    r->eax = rd32(r, r->ebp - 0x48);
    call_all(r, rd32(r, r->edx));
at_4c6d50:
    r->ecx = 0x1;
    r->edx = rd32(r, r->ebp - 0x34);
    r->eax = 0;
    if ((int32_t)r->edx <= 0)
    {
        goto at_4c6d80;
    }
    r->edx = rd32(r, r->ebp - 0x4c);
    r->esi = rd32(r, r->ebp - 0x34);
at_4c6d64:
    r->ecx = r->ecx * r->ebx;
    r->edx = r->edx + 0x4;
    r->eax = r->eax + 1;
    wr32(r, r->edx - 0x4, r->ebx);
    if ((int32_t)r->eax < (int32_t)r->esi && !r->port->env.failed)
    {
        goto at_4c6d64;
    }
at_4c6d80:
    r->eax = rd32(r, r->ebp - 0x34);
    r->edi = 0;
    r->esi = 0;
    wr32(r, r->ebp - 0x3c, r->edi);
    if ((int32_t)r->eax <= 0)
    {
        goto at_4c6dc6;
    }
    r->ebx = 0;
at_4c6d90:
    r->eax = rd32(r, r->ebp - 0x48);
    if (rd32(r, r->eax + 0x2c) != 0x2)
    {
        goto at_4c6fb8;
    }
    r->eax = rd32(r, r->ebx + 0x4fffc0);
at_4c6da3:
    r->edi = rd32(r, r->ebp - 0x4c);
    r->eax = r->eax << 0x2;
    r->edx = r->ecx;
    r->edi = r->edi + r->eax;
    r->edx = (uint32_t)((int32_t)r->edx >> 0x1f);
    r->eax = r->ecx;
    idiv32(r, rd32(r, r->edi));
    r->edx = rd32(r, r->edi);
    r->edx = r->edx + 1;
    r->eax = r->eax * r->edx;
    wr32(r, r->ebp - 0x30, r->edx);
    if ((int32_t)r->eax <= (int32_t)rd32(r, r->ebp - 0x44))
    {
        goto at_4c6f94;
    }
at_4c6dc6:
    if (rd32(r, r->ebp - 0x3c) != 0x0 && !r->port->env.failed)
    {
        goto at_4c6d80;
    }
    r->eax = rd32(r, r->ebp - 0x58);
    r->esi = rd32(r, r->eax + 0x78);
    wr32(r, r->ebp - 0x20, r->ecx);
    if (r->esi != 0x3)
    {
        goto at_4c6fbf;
    }
    r->eax = rd32(r, r->eax);
    r->edx = rd32(r, r->ebp - 0x64);
    wr32(r, r->eax + 0x18, r->ecx);
    r->edx = rd32(r, r->edx + 0x20);
    wr32(r, r->eax + 0x1c, r->edx);
    r->edx = rd32(r, r->ebp - 0x64);
    r->edx = rd32(r, r->edx + 0x24);
    wr32(r, r->eax + 0x20, r->edx);
    r->edx = rd32(r, r->ebp - 0x64);
    r->edx = rd32(r, r->edx + 0x28);
    wr32(r, r->eax + 0x24, r->edx);
    r->eax = rd32(r, r->ebp - 0x58);
    r->eax = rd32(r, r->eax);
    r->ecx = rd32(r, r->ebp - 0x58);
    wr32(r, r->eax + 0x14, 0x5e);
at_4c6e0d:
    r->ecx = rd32(r, r->ecx);
    r->edx = 0x1;
    r->eax = rd32(r, r->ebp - 0x58);
    call_all(r, rd32(r, r->ecx + 0x4));
    r->esi = rd32(r, r->ebp - 0x58);
    r->ecx = rd32(r, r->ebp - 0x58);
    r->ebx = rd32(r, r->ebp - 0x20);
    r->edx = 0x1;
    r->esi = rd32(r, r->esi + 0x4);
    r->eax = rd32(r, r->ebp - 0x58);
    r->ecx = rd32(r, r->ecx + 0x78);
    call_all(r, rd32(r, r->esi + 0x8));
    wr32(r, r->ebp - 0x60, r->eax);
    r->eax = rd32(r, r->ebp - 0x20);
    wr32(r, r->ebp - 0x24, r->eax);
    r->eax = rd32(r, r->ebp - 0x58);
    r->edi = 0;
    r->edx = rd32(r, r->eax + 0x78);
    wr32(r, r->ebp - 0x50, r->edi);
    if ((int32_t)r->edx <= 0)
    {
        goto at_4c6f1b;
    }
    r->eax = rd32(r, r->ebp - 0x64);
    wr32(r, r->ebp - 0x54, r->eax);
at_4c6e56:
    r->eax = rd32(r, r->ebp - 0x54);
    r->eax = rd32(r, r->eax + 0x20);
    wr32(r, r->ebp - 0x38, r->eax);
    r->eax = rd32(r, r->ebp - 0x24);
    r->edx = r->eax;
    r->ecx = rd32(r, r->ebp - 0x38);
    r->edx = (uint32_t)((int32_t)r->edx >> 0x1f);
    idiv32(r, r->ecx);
    r->edi = rd32(r, r->ebp - 0x50);
    r->ebx = 0;
    r->edi = r->edi << 0x2;
    wr32(r, r->ebp - 0x28, r->ebx);
    r->esi = r->eax;
    if ((int32_t)r->ecx <= 0)
    {
        goto at_4c6efa;
    }
    r->edi = r->edi + rd32(r, r->ebp - 0x60);
    r->eax = r->ecx - 0x1;
    r->edx = r->eax;
    r->edx = (uint32_t)((int32_t)r->edx >> 0x1f);
    wr32(r, r->ebp - 0x40, r->eax);
    r->eax = r->eax - r->edx;
    r->eax = (uint32_t)((int32_t)r->eax >> 0x1);
    wr32(r, r->ebp - 0x2c, r->eax);
at_4c6e96:
    r->eax = rd32(r, r->ebp - 0x2c);
    r->edx = r->eax;
    r->ecx = rd32(r, r->ebp - 0x40);
    r->edx = (uint32_t)((int32_t)r->edx >> 0x1f);
    idiv32(r, r->ecx);
    wr32(r, r->ebp - 0x18, r->eax);
    r->eax = rd32(r, r->ebp - 0x28);
    r->eax = r->eax * r->esi;
    r->ebx = rd32(r, r->ebp - 0x20);
    wr32(r, r->ebp - 0x1c, r->eax);
    if ((int32_t)r->eax >= (int32_t)r->ebx)
    {
        goto at_4c6ee0;
    }
    set_low8(&r->ebx, rd8(r, r->ebp - 0x18));
at_4c6eb9:
    r->edx = 0;
    if ((int32_t)r->esi <= 0)
    {
        goto at_4c6ece;
    }
    r->eax = rd32(r, r->ebp - 0x1c);
at_4c6ec2:
    r->eax = r->eax + 1;
    r->ecx = rd32(r, r->edi);
    r->edx = r->edx + 1;
    wr8(r, r->ecx + r->eax - 0x1, (r->ebx & 0xff));
    if ((int32_t)r->edx < (int32_t)r->esi && !r->port->env.failed)
    {
        goto at_4c6ec2;
    }
at_4c6ece:
    r->eax = rd32(r, r->ebp - 0x24);
    r->edx = rd32(r, r->ebp - 0x1c);
    r->edx = r->edx + r->eax;
    r->ecx = rd32(r, r->ebp - 0x20);
    wr32(r, r->ebp - 0x1c, r->edx);
    if ((int32_t)r->edx < (int32_t)r->ecx && !r->port->env.failed)
    {
        goto at_4c6eb9;
    }
at_4c6ee0:
    r->edx = rd32(r, r->ebp - 0x2c);
    r->ecx = rd32(r, r->ebp - 0x28);
    r->ebx = rd32(r, r->ebp - 0x38);
    r->edx = r->edx + 0xff;
    r->ecx = r->ecx + 1;
    wr32(r, r->ebp - 0x2c, r->edx);
    wr32(r, r->ebp - 0x28, r->ecx);
    if ((int32_t)r->ecx < (int32_t)r->ebx && !r->port->env.failed)
    {
        goto at_4c6e96;
    }
at_4c6efa:
    r->ecx = rd32(r, r->ebp - 0x54);
    r->ebx = rd32(r, r->ebp - 0x50);
    r->edx = rd32(r, r->ebp - 0x58);
    wr32(r, r->ebp - 0x24, r->esi);
    r->ecx = r->ecx + 0x4;
    r->ebx = r->ebx + 1;
    r->esi = rd32(r, r->edx + 0x78);
    wr32(r, r->ebp - 0x54, r->ecx);
    wr32(r, r->ebp - 0x50, r->ebx);
    if ((int32_t)r->ebx < (int32_t)r->esi && !r->port->env.failed)
    {
        goto at_4c6e56;
    }
at_4c6f1b:
    r->edx = rd32(r, r->ebp - 0x64);
    r->eax = rd32(r, r->ebp - 0x60);
    wr32(r, r->edx + 0x10, r->eax);
    r->eax = rd32(r, r->ebp - 0x20);
    wr32(r, r->edx + 0x14, r->eax);
    r->eax = rd32(r, r->ebp - 0x5c);
    call(r, 0x4c6020, 0);
    r->eax = rd32(r, r->ebp - 0x5c);
    if (rd32(r, r->eax + 0x58) == 0x2)
    {
        goto at_4c6fd8;
    }
    r->edi = rd32(r, r->ebp - 0x14);
    r->esi = rd32(r, r->ebp - 0x10);
    r->edx = rd32(r, r->ebp - 0xc);
    r->ecx = rd32(r, r->ebp - 0x8);
    r->ebx = rd32(r, r->ebp - 0x4);
    return;
at_4c6f49:
    r->eax = rd32(r, r->ebp - 0x5c);
    r->eax = rd32(r, r->eax);
    wr32(r, r->eax + 0x14, 0x37);
    r->eax = rd32(r, r->ebp - 0x5c);
    r->eax = rd32(r, r->eax);
    r->edx = rd32(r, r->ebp - 0x5c);
    wr32(r, r->eax + 0x18, 0x4);
    r->edx = rd32(r, r->edx);
    r->eax = rd32(r, r->ebp - 0x5c);
    call_all(r, rd32(r, r->edx));
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4c6cd2;
at_4c6f70:
    r->eax = rd32(r, r->eax);
    wr32(r, r->eax + 0x14, 0x39);
    r->eax = rd32(r, r->ebp - 0x5c);
    r->eax = rd32(r, r->eax);
    r->edx = rd32(r, r->ebp - 0x5c);
    wr32(r, r->eax + 0x18, 0x100);
    r->edx = rd32(r, r->edx);
    r->eax = rd32(r, r->ebp - 0x5c);
    call_all(r, rd32(r, r->edx));
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4c6ce2;
at_4c6f94:
    r->edx = 0x1;
    r->ecx = r->eax;
    r->ebx = r->ebx + 0x4;
    r->eax = rd32(r, r->ebp - 0x30);
    r->esi = r->esi + r->edx;
    wr32(r, r->edi, r->eax);
    r->edi = rd32(r, r->ebp - 0x34);
    wr32(r, r->ebp - 0x3c, r->edx);
    if ((int32_t)r->esi < (int32_t)r->edi && !r->port->env.failed)
    {
        goto at_4c6d90;
    }
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4c6dc6;
at_4c6fb8:
    r->eax = r->esi;
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4c6da3;
at_4c6fbf:
    r->eax = rd32(r, r->eax);
    wr32(r, r->eax + 0x14, 0x5f);
    r->eax = rd32(r, r->ebp - 0x58);
    r->eax = rd32(r, r->eax);
    wr32(r, r->eax + 0x18, r->ecx);
    r->ecx = rd32(r, r->ebp - 0x58);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4c6e0d;
at_4c6fd8:
    call(r, 0x4c69c0, 0);
    r->edi = rd32(r, r->ebp - 0x14);
    r->esi = rd32(r, r->ebp - 0x10);
    r->edx = rd32(r, r->ebp - 0xc);
    r->ecx = rd32(r, r->ebp - 0x8);
    r->ebx = rd32(r, r->ebp - 0x4);
    return;
}

uint32_t vertrix_port_jpeg_one_pass_quantizer_init_4c6c80(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x68
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
