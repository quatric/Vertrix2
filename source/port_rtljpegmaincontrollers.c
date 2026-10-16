#include "port_rtljpegmaincontrollers.h"

/* The routine at 0x4bdde0 matches libjpeg's jinit_d_main_controller. */

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

static void wr16(Regs *r, uint32_t address, uint32_t value)
{
    port_set16(r->port, address, 0, value);
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

/* Original 0x4bdde0: The routine at 0x4bdde0 matches libjpeg's jinit_d_main_controller. It
 * allocates a 0x50-byte main controller through cinfo->mem ([edi]), stores it at cinfo+0x1a8 and
 * sets start_pass to 0x4bd750. A nonzero need_full_buffer argument branches to the error path at
 * 0x4bdfb9. When need_context_rows (+0x1c4 -> +8) is set, it raises error 0x2f if
 * min_DCT_scaled_size (+0x13c) is below 2. It then allocates the funny xbuffer pointer lists
 * (+0x38/+0x3c) for each component in comp_info (+0xd8, stride 0x54, count +0x24). Next, it
 * allocates one sample array per component through mem+8 (alloc_sarray), sized at
 * (min_DCT_scaled_size+2) row groups. Evidence: no calls. Register-for-register from the listing
 * (0x4bddea..0x4be0ab); labels are the original addresses. */
static void run(Regs *r)
{
    r->esi = r->eax;
    r->ecx = r->edx;
    r->edi = rd32(r, r->eax + 0x4);
    r->ebx = 0x50;
    r->edx = 0x1;
    call_all(r, rd32(r, r->edi));
    wr32(r, r->esi + 0x1a8, r->eax);
    wr32(r, r->ebp - 0x38, r->eax);
    wr32(r, r->eax, 0x4bd750);
    if (r->ecx != 0)
    {
        goto at_4bdfb9;
    }
at_4bde14:
    r->eax = rd32(r, r->esi + 0x1c4);
    if (rd32(r, r->eax + 0x8) == 0x0)
    {
        goto at_4bdfcd;
    }
    if ((int32_t)rd32(r, r->esi + 0x13c) >= (int32_t)0x2)
    {
        goto at_4bde3c;
    }
    r->eax = rd32(r, r->esi);
    wr32(r, r->eax + 0x14, 0x2f);
    r->edx = rd32(r, r->esi);
    r->eax = r->esi;
    call_all(r, rd32(r, r->edx));
at_4bde3c:
    r->edx = 0x1;
    r->eax = rd32(r, r->esi + 0x1a8);
    r->edi = rd32(r, r->esi + 0x4);
    r->ebx = rd32(r, r->esi + 0x24);
    wr32(r, r->ebp - 0x2c, r->eax);
    r->eax = rd32(r, r->esi + 0x13c);
    r->ebx = r->ebx << 0x3;
    wr32(r, r->ebp - 0x3c, r->eax);
    r->eax = r->esi;
    call_all(r, rd32(r, r->edi));
    r->edx = rd32(r, r->ebp - 0x2c);
    wr32(r, r->edx + 0x38, r->eax);
    r->eax = rd32(r, r->esi + 0x24);
    r->edx = rd32(r, r->edx + 0x38);
    r->eax = r->eax << 0x2;
    r->edx = r->edx + r->eax;
    r->eax = rd32(r, r->ebp - 0x2c);
    r->ecx = r->esi;
    r->ebx = 0;
    wr32(r, r->eax + 0x3c, r->edx);
    wr32(r, r->ebp - 0x24, r->ebx);
    r->eax = rd32(r, r->esi + 0xd8);
    r->edi = rd32(r, r->esi + 0x24);
    wr32(r, r->ebp - 0x1c, r->eax);
    if ((int32_t)r->edi <= 0)
    {
        goto at_4bdf20;
    }
    r->eax = rd32(r, r->ebp - 0x3c);
    r->eax = r->eax + 0x4;
    wr32(r, r->ebp - 0x18, r->ebx);
    wr32(r, r->ebp - 0x34, r->eax);
at_4bde9e:
    r->edx = rd32(r, r->ebp - 0x1c);
    r->eax = rd32(r, r->ebp - 0x1c);
    r->edx = rd32(r, r->edx + 0xc);
    r->edx = r->edx * rd32(r, r->eax + 0x24);
    r->edi = rd32(r, r->ecx + 0x13c);
    r->eax = r->edx;
    r->edx = (uint32_t)((int32_t)r->edx >> 0x1f);
    idiv32(r, r->edi);
    r->edx = rd32(r, r->ebp - 0x34);
    wr32(r, r->ebp - 0x44, r->eax);
    r->eax = r->eax * r->edx;
    r->edi = rd32(r, r->ecx + 0x4);
    wr32(r, r->ebp - 0x40, r->eax);
    r->ebx = r->eax * 8;
    r->edx = 0x1;
    r->eax = r->ecx;
    call_all(r, rd32(r, r->edi));
    r->edx = rd32(r, r->ebp - 0x44);
    r->edx = r->edx << 0x2;
    r->edx = r->edx + r->eax;
    r->eax = rd32(r, r->ebp - 0x2c);
    r->ebx = rd32(r, r->ebp - 0x18);
    r->eax = rd32(r, r->eax + 0x38);
    r->eax = r->eax + r->ebx;
    wr32(r, r->eax, r->edx);
    r->eax = rd32(r, r->ebp - 0x40);
    r->eax = r->eax << 0x2;
    r->edx = r->edx + r->eax;
    r->eax = rd32(r, r->ebp - 0x2c);
    r->eax = rd32(r, r->eax + 0x3c);
    r->eax = r->eax + r->ebx;
    wr32(r, r->eax, r->edx);
    r->edx = rd32(r, r->ebp - 0x24);
    r->eax = r->ebx + 0x4;
    r->edi = rd32(r, r->ecx + 0x24);
    r->ebx = rd32(r, r->ebp - 0x1c);
    wr32(r, r->ebp - 0x18, r->eax);
    r->edx = r->edx + 1;
    r->ebx = r->ebx + 0x54;
    wr32(r, r->ebp - 0x24, r->edx);
    wr32(r, r->ebp - 0x1c, r->ebx);
    if ((int32_t)r->edx < (int32_t)r->edi && !r->port->env.failed)
    {
        goto at_4bde9e;
    }
at_4bdf20:
    r->eax = rd32(r, r->esi + 0x13c);
    r->eax = r->eax + 0x2;
at_4bdf29:
    wr32(r, r->ebp - 0x30, r->eax);
    r->eax = rd32(r, r->esi + 0xd8);
    r->edx = 0;
    r->ecx = rd32(r, r->esi + 0x24);
    wr32(r, r->ebp - 0x20, r->edx);
    wr32(r, r->ebp - 0x14, r->eax);
    if ((int32_t)r->ecx <= 0)
    {
        goto at_4bdfb0;
    }
    r->eax = rd32(r, r->ebp - 0x38);
    wr32(r, r->ebp - 0x28, r->eax);
at_4bdf47:
    r->edx = rd32(r, r->ebp - 0x14);
    r->eax = rd32(r, r->ebp - 0x14);
    r->edx = rd32(r, r->edx + 0xc);
    r->edx = r->edx * rd32(r, r->eax + 0x24);
    r->edi = rd32(r, r->esi + 0x13c);
    r->eax = r->edx;
    r->edx = (uint32_t)((int32_t)r->edx >> 0x1f);
    idiv32(r, r->edi);
    r->ecx = rd32(r, r->ebp - 0x30);
    r->ecx = r->ecx * r->eax;
    r->edx = rd32(r, r->ebp - 0x14);
    r->eax = rd32(r, r->ebp - 0x14);
    r->edx = rd32(r, r->edx + 0x1c);
    r->ebx = rd32(r, r->eax + 0x24);
    r->ebx = r->ebx * r->edx;
    r->edi = rd32(r, r->esi + 0x4);
    r->eax = r->esi;
    r->edx = 0x1;
    call_all(r, rd32(r, r->edi + 0x8));
    r->edx = rd32(r, r->ebp - 0x28);
    r->edi = r->edx + 0x4;
    wr32(r, r->edx + 0x8, r->eax);
    r->eax = rd32(r, r->ebp - 0x20);
    r->edx = rd32(r, r->ebp - 0x14);
    wr32(r, r->ebp - 0x28, r->edi);
    r->ecx = rd32(r, r->esi + 0x24);
    r->eax = r->eax + 1;
    r->edx = r->edx + 0x54;
    wr32(r, r->ebp - 0x20, r->eax);
    wr32(r, r->ebp - 0x14, r->edx);
    if ((int32_t)r->eax < (int32_t)r->ecx && !r->port->env.failed)
    {
        goto at_4bdf47;
    }
at_4bdfb0:
    r->edi = rd32(r, r->ebp - 0x10);
    r->esi = rd32(r, r->ebp - 0xc);
    r->ecx = rd32(r, r->ebp - 0x8);
    r->ebx = rd32(r, r->ebp - 0x4);
    return;
at_4bdfb9:
    r->eax = rd32(r, r->esi);
    wr32(r, r->eax + 0x14, 0x4);
    r->edx = rd32(r, r->esi);
    r->eax = r->esi;
    call_all(r, rd32(r, r->edx));
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4bde14;
at_4bdfcd:
    r->eax = rd32(r, r->esi + 0x13c);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4bdf29;
    wr8(r, r->eax, rd8(r, r->eax) + (r->eax & 0xff));
    wr8(r, r->eax, rd8(r, r->eax) + (r->eax & 0xff));
    wr8(r, r->eax, rd8(r, r->eax) + (r->eax & 0xff));
    wr8(r, r->eax, rd8(r, r->eax) + (r->eax & 0xff));
    push(r, r->ebx);
    push(r, r->ecx);
    push(r, r->edx);
    r->ecx = r->eax;
    r->eax = rd32(r, r->eax);
    wr32(r, r->eax + 0x14, 0x66);
    r->ebx = rd32(r, r->ecx);
    r->edx = 0x1;
    r->eax = r->ecx;
    call_all(r, rd32(r, r->ebx + 0x4));
    r->eax = rd32(r, r->ecx + 0x1b8);
    if (rd32(r, r->eax + 0xc) != 0x0)
    {
        goto at_4be09c;
    }
at_4be00a:
    r->eax = r->ecx;
    r->edx = r->ecx + 0x10;
at_4be00f:
    r->eax = r->eax + 1;
    wr8(r, r->eax + 0xe3, 0x0);
    wr8(r, r->eax + 0xf3, 0x1);
    wr8(r, r->eax + 0x103, 0x5);
    if (r->eax != r->edx && !r->port->env.failed)
    {
        goto at_4be00f;
    }
    wr32(r, r->ecx + 0x114, 0x0);
    wr32(r, r->ecx + 0x28, 0x0);
    wr32(r, r->ecx + 0x12c, 0x0);
    wr32(r, r->ecx + 0x118, 0x0);
    wr8(r, r->ecx + 0x11c, 0x1);
    wr8(r, r->ecx + 0x11d, 0x1);
    wr8(r, r->ecx + 0x11e, 0x0);
    wr16(r, r->ecx + 0x120, 0x1);
    wr16(r, r->ecx + 0x122, 0x1);
    wr32(r, r->ecx + 0x124, 0x0);
    r->eax = rd32(r, r->ecx + 0x1b8);
    wr8(r, r->ecx + 0x128, 0x0);
    wr32(r, r->eax + 0xc, 0x1);
    r->eax = 0x1;
    r->edx = pop(r);
    r->ecx = pop(r);
    r->ebx = pop(r);
    return;
at_4be09c:
    r->eax = rd32(r, r->ecx);
    wr32(r, r->eax + 0x14, 0x3d);
    r->edx = rd32(r, r->ecx);
    r->eax = r->ecx;
    call_all(r, rd32(r, r->edx));
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4be00a;
}

uint32_t vertrix_port_jpeg_init_main_controller_4bdde0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x48
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
