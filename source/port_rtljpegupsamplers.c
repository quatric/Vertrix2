#include "port_rtljpegupsamplers.h"

/* 0x4c3be0 allocates a 0xa0-byte upsampler through the memory manager ([[cinfo+4]], pool 1) and
 * stores it at cinfo+0x1c4 with start_pass 0x4c35f0, upsample 0x4c3610 and need_context_rows 0. */

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

/* Original 0x4c3be0: 0x4c3be0 allocates a 0xa0-byte upsampler through the memory manager
 * ([[cinfo+4]], pool 1) and stores it at cinfo+0x1c4 with start_pass 0x4c35f0, upsample 0x4c3610
 * and need_context_rows 0. It raises error 0x19 if CCIR601 sampling (+0x12c) is set. For each
 * component (stride 0x54) it chooses one method: 0x4c3770 (component not needed), 0x4c3760 (full
 * size), 0x4c3850/0x4c3950 (h2v1 plain or fancy), 0x4c38b0/0x4c3a30 (h2v2 plain or fancy; fancy
 * sets need_context_rows), or 0x4c3780 (integral factors stored as bytes at +0x8c/+0x96). Any other
 * ratio raises error 0x26. Every method except full size and no-op also gets a color buffer sized
 * by round_up 0x4c9840 of output_width. This is libjpeg's jinit_upsampler. Evidence: calls
 * 0x4c9840. Register-for-register from the listing (0x4c3beb..0x4c3e3a); labels are the original
 * addresses. */
static void run(Regs *r)
{
    r->esi = r->eax;
    r->ecx = rd32(r, r->eax + 0x4);
    r->ebx = 0xa0;
    r->edx = 0x1;
    call_all(r, rd32(r, r->ecx));
    wr32(r, r->esi + 0x1c4, r->eax);
    wr32(r, r->eax, 0x4c35f0);
    wr32(r, r->eax + 0x4, 0x4c3610);
    wr32(r, r->eax + 0x8, 0x0);
    r->edx = rd32(r, r->esi + 0x12c);
    wr32(r, r->ebp - 0x34, r->eax);
    if (r->edx != 0)
    {
        goto at_4c3d07;
    }
at_4c3c27:
    if (rd32(r, r->esi + 0x4c) == 0x0)
    {
        goto at_4c3d1b;
    }
    if ((int32_t)rd32(r, r->esi + 0x13c) <= (int32_t)0x1)
    {
        goto at_4c3d1b;
    }
    r->eax = 0x1;
at_4c3c43:
    wr32(r, r->ebp - 0x2c, r->eax);
    r->eax = rd32(r, r->esi + 0xd8);
    r->edi = 0;
    wr32(r, r->ebp - 0x1c, r->eax);
    r->eax = rd32(r, r->esi + 0x24);
    wr32(r, r->ebp - 0x28, r->edi);
    if ((int32_t)r->eax <= 0)
    {
        goto at_4c3cfd;
    }
    r->eax = rd32(r, r->ebp - 0x34);
    wr32(r, r->ebp - 0x24, r->eax);
    wr32(r, r->ebp - 0x18, r->eax);
at_4c3c68:
    r->edx = rd32(r, r->ebp - 0x1c);
    r->eax = rd32(r, r->ebp - 0x1c);
    r->edx = rd32(r, r->edx + 0x8);
    r->edx = r->edx * rd32(r, r->eax + 0x24);
    r->ebx = rd32(r, r->esi + 0x13c);
    r->eax = r->edx;
    r->edx = (uint32_t)((int32_t)r->edx >> 0x1f);
    idiv32(r, r->ebx);
    r->edx = rd32(r, r->ebp - 0x1c);
    wr32(r, r->ebp - 0x20, r->eax);
    r->eax = rd32(r, r->ebp - 0x1c);
    r->edx = rd32(r, r->edx + 0xc);
    r->edi = rd32(r, r->eax + 0x24);
    r->edx = r->edx * r->edi;
    r->eax = r->edx;
    r->edx = (uint32_t)((int32_t)r->edx >> 0x1f);
    idiv32(r, r->ebx);
    r->edi = r->eax;
    r->eax = rd32(r, r->ebp - 0x18);
    r->ecx = rd32(r, r->esi + 0x134);
    r->ebx = rd32(r, r->esi + 0x138);
    wr32(r, r->eax + 0x64, r->edi);
    wr32(r, r->ebp - 0x30, 0x1);
    r->eax = rd32(r, r->ebp - 0x1c);
    if (rd32(r, r->eax + 0x30) == 0x0)
    {
        goto at_4c3d22;
    }
    if (r->ecx != rd32(r, r->ebp - 0x20))
    {
        goto at_4c3d2e;
    }
    if (r->edi != r->ebx)
    {
        goto at_4c3d2e;
    }
    r->eax = rd32(r, r->ebp - 0x18);
    wr32(r, r->eax + 0x34, 0x4c3760);
at_4c3cd2:
    r->edx = rd32(r, r->ebp - 0x24);
    r->ecx = rd32(r, r->ebp - 0x18);
    r->ebx = rd32(r, r->ebp - 0x28);
    r->edi = rd32(r, r->ebp - 0x1c);
    r->edx = r->edx + 1;
    r->ecx = r->ecx + 0x4;
    r->ebx = r->ebx + 1;
    r->edi = r->edi + 0x54;
    wr32(r, r->ebp - 0x24, r->edx);
    wr32(r, r->ebp - 0x18, r->ecx);
    wr32(r, r->ebp - 0x28, r->ebx);
    r->edx = rd32(r, r->esi + 0x24);
    wr32(r, r->ebp - 0x1c, r->edi);
    if ((int32_t)r->ebx < (int32_t)r->edx && !r->port->env.failed)
    {
        goto at_4c3c68;
    }
at_4c3cfd:
    r->edi = rd32(r, r->ebp - 0x14);
    r->esi = rd32(r, r->ebp - 0x10);
    r->edx = rd32(r, r->ebp - 0xc);
    r->ecx = rd32(r, r->ebp - 0x8);
    r->ebx = rd32(r, r->ebp - 0x4);
    return;
at_4c3d07:
    r->eax = rd32(r, r->esi);
    wr32(r, r->eax + 0x14, 0x19);
    r->edx = rd32(r, r->esi);
    r->eax = r->esi;
    call_all(r, rd32(r, r->edx));
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4c3c27;
at_4c3d1b:
    r->eax = 0;
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4c3c43;
at_4c3d22:
    r->eax = rd32(r, r->ebp - 0x18);
    wr32(r, r->eax + 0x34, 0x4c3770);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4c3cd2;
at_4c3d2e:
    r->eax = rd32(r, r->ebp - 0x20);
    r->eax = r->eax + r->eax;
    if (r->eax != r->ecx)
    {
        goto at_4c3d98;
    }
    if (r->edi != r->ebx)
    {
        goto at_4c3d98;
    }
    if (rd32(r, r->ebp - 0x2c) == 0x0)
    {
        goto at_4c3d8c;
    }
    r->eax = rd32(r, r->ebp - 0x1c);
    if (rd32(r, r->eax + 0x28) <= 0x2)
    {
        goto at_4c3d8c;
    }
    r->eax = rd32(r, r->ebp - 0x18);
    wr32(r, r->eax + 0x34, 0x4c3950);
at_4c3d54:
    if (rd32(r, r->ebp - 0x30) == 0x0 && !r->port->env.failed)
    {
        goto at_4c3cd2;
    }
    r->edi = rd32(r, r->esi + 0x4);
    r->edx = rd32(r, r->esi + 0x134);
    r->eax = rd32(r, r->esi + 0x70);
    r->ecx = rd32(r, r->esi + 0x138);
    call(r, 0x4c9840, 0);
    r->edx = 0x1;
    r->ebx = r->eax;
    r->eax = r->esi;
    call_all(r, rd32(r, r->edi + 0x8));
    r->edx = rd32(r, r->ebp - 0x18);
    wr32(r, r->edx + 0xc, r->eax);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4c3cd2;
at_4c3d8c:
    r->eax = rd32(r, r->ebp - 0x18);
    wr32(r, r->eax + 0x34, 0x4c3850);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4c3d54;
at_4c3d98:
    r->eax = rd32(r, r->ebp - 0x20);
    r->eax = r->eax + r->eax;
    if (r->eax != r->ecx)
    {
        goto at_4c3ddc;
    }
    r->eax = r->edi + r->edi;
    if (r->eax != r->ebx)
    {
        goto at_4c3ddc;
    }
    if (rd32(r, r->ebp - 0x2c) == 0x0)
    {
        goto at_4c3dcd;
    }
    r->eax = rd32(r, r->ebp - 0x1c);
    if (rd32(r, r->eax + 0x28) <= 0x2)
    {
        goto at_4c3dcd;
    }
    r->eax = rd32(r, r->ebp - 0x18);
    wr32(r, r->eax + 0x34, 0x4c3a30);
    r->eax = rd32(r, r->ebp - 0x34);
    wr32(r, r->eax + 0x8, 0x1);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4c3d54;
at_4c3dcd:
    r->eax = rd32(r, r->ebp - 0x18);
    wr32(r, r->eax + 0x34, 0x4c38b0);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4c3d54;
at_4c3ddc:
    r->edx = r->ecx;
    r->eax = r->ecx;
    r->edx = (uint32_t)((int32_t)r->edx >> 0x1f);
    idiv32(r, rd32(r, r->ebp - 0x20));
    if (r->edx != 0)
    {
        goto at_4c3e2b;
    }
    r->edx = r->ebx;
    r->eax = r->ebx;
    r->edx = (uint32_t)((int32_t)r->edx >> 0x1f);
    idiv32(r, r->edi);
    if (r->edx != 0)
    {
        goto at_4c3e2b;
    }
    r->edx = r->ecx;
    r->eax = rd32(r, r->ebp - 0x18);
    r->edx = (uint32_t)((int32_t)r->edx >> 0x1f);
    wr32(r, r->eax + 0x34, 0x4c3780);
    r->eax = r->ecx;
    idiv32(r, rd32(r, r->ebp - 0x20));
    r->edx = rd32(r, r->ebp - 0x24);
    wr8(r, r->edx + 0x8c, (r->eax & 0xff));
    r->edx = r->ebx;
    r->eax = r->ebx;
    r->edx = (uint32_t)((int32_t)r->edx >> 0x1f);
    idiv32(r, r->edi);
    r->edx = rd32(r, r->ebp - 0x24);
    wr8(r, r->edx + 0x96, (r->eax & 0xff));
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4c3d54;
at_4c3e2b:
    r->eax = rd32(r, r->esi);
    wr32(r, r->eax + 0x14, 0x26);
    r->edx = rd32(r, r->esi);
    r->eax = r->esi;
    call_all(r, rd32(r, r->edx));
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4c3d54;
}

uint32_t vertrix_port_jpeg_init_upsampler_4c3be0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x38
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
