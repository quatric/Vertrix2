#include "port_rtljpegcoefrows.h"

/* At 0x4ba470, while the input counters (+0x90/+0x94) are behind the output counters (+0x98/+0x9c),
 * the routine keeps calling the consume-input hook at [[+0x1b4]], and it returns 0 if that hook
 * returns 0. */

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

static uint32_t rd32(Regs *r, uint32_t address)
{
    return port_u32(r->port, address, 0);
}

static void wr32(Regs *r, uint32_t address, uint32_t value)
{
    port_set32(r->port, address, 0, value);
}

static void div32(Regs *r, uint32_t value)
{
    LiftFlags flags;
    memset(&flags, 0, sizeof flags);
    lift_div1(32, value, &r->eax, &r->edx, &flags);
}

/* An indirect call (an import or a method): every value pushed passed and popped, as stdcall. */
static void call_all(Regs *r, uint32_t target)
{
    call_with_stack(r, target, r->pushed, 0);
}

/* Original 0x4ba470: At 0x4ba470, while the input counters (+0x90/+0x94) are behind the output
 * counters (+0x98/+0x9c), the routine keeps calling the consume-input hook at [[+0x1b4]], and it
 * returns 0 if that hook returns 0. It then loops over [+0x24] components (0x54-byte records from
 * [+0xd8], skipping a component when its +0x30 flag is zero). For each one it fetches a row of
 * 0x80-byte coefficient blocks through [[obj+4]+0x20] and passes each block to that component's
 * handler at [[+0x1c0]+idx*4+4]. The last row is handled separately at 0x4ba629. Finally it
 * increments [+0x9c] and returns 3 while that is below [+0x140]. The structure matches libjpeg's
 * decompress_data, but no strings or callers confirm it. Evidence: no calls. Register-for-register
 * from the listing (0x4ba47a..0x4ba653); labels are the original addresses. */
static void run(Regs *r)
{
    wr32(r, r->ebp - 0x20, r->eax);
    r->ecx = r->edx;
    r->ebx = rd32(r, r->eax + 0x1ac);
    r->eax = rd32(r, r->eax + 0x140);
    r->eax = r->eax - 1;
    wr32(r, r->ebp - 0x40, r->eax);
at_4ba48f:
    r->eax = rd32(r, r->ebp - 0x20);
    r->edx = rd32(r, r->ebp - 0x20);
    r->eax = rd32(r, r->eax + 0x90);
    r->esi = rd32(r, r->edx + 0x98);
    if ((int32_t)r->eax < (int32_t)r->esi)
    {
        goto at_4ba611;
    }
    if (r->esi != rd32(r, r->edx + 0x90))
    {
        goto at_4ba4c3;
    }
    r->eax = rd32(r, r->edx + 0x94);
    if (r->eax <= rd32(r, r->edx + 0x9c))
    {
        goto at_4ba611;
    }
at_4ba4c3:
    r->eax = rd32(r, r->ebp - 0x20);
    r->edi = 0;
    r->esi = rd32(r, r->ebp - 0x20);
    wr32(r, r->ebp - 0x34, r->edi);
    r->edx = rd32(r, r->eax + 0x24);
    r->esi = rd32(r, r->esi + 0xd8);
    if ((int32_t)r->edx <= 0)
    {
        goto at_4ba5e9;
    }
    wr32(r, r->ebp - 0x3c, r->ebx);
    wr32(r, r->ebp - 0x38, r->ecx);
at_4ba4e5:
    if (rd32(r, r->esi + 0x30) == 0x0)
    {
        goto at_4ba5bf;
    }
    r->ebx = rd32(r, r->ebp - 0x20);
    r->ecx = rd32(r, r->esi + 0xc);
    r->ebx = rd32(r, r->ebx + 0x9c);
    r->ebx = r->ebx * r->ecx;
    r->edi = rd32(r, r->ebp - 0x20);
    push(r, 0x0);
    r->edx = rd32(r, r->ebp - 0x3c);
    r->edi = rd32(r, r->edi + 0x4);
    r->eax = rd32(r, r->ebp - 0x20);
    r->edx = rd32(r, r->edx + 0x48);
    call_all(r, rd32(r, r->edi + 0x20));
    r->edi = r->eax;
    r->eax = rd32(r, r->ebp - 0x20);
    r->edx = rd32(r, r->ebp - 0x40);
    if (r->edx <= rd32(r, r->eax + 0x9c))
    {
        goto at_4ba629;
    }
    r->eax = rd32(r, r->esi + 0xc);
    wr32(r, r->ebp - 0x30, r->eax);
at_4ba52c:
    r->eax = rd32(r, r->ebp - 0x20);
    r->edx = rd32(r, r->ebp - 0x34);
    r->eax = rd32(r, r->eax + 0x1c0);
    r->eax = rd32(r, r->eax + r->edx * 4 + 0x4);
    wr32(r, r->ebp - 0x24, r->eax);
    r->eax = rd32(r, r->ebp - 0x38);
    r->eax = rd32(r, r->eax);
    wr32(r, r->ebp - 0x1c, r->eax);
    r->eax = 0;
    r->edx = rd32(r, r->ebp - 0x30);
    wr32(r, r->ebp - 0x2c, r->eax);
    if ((int32_t)r->edx <= 0)
    {
        goto at_4ba5bf;
    }
    wr32(r, r->ebp - 0x28, r->edi);
at_4ba556:
    r->edi = rd32(r, r->ebp - 0x28);
    r->ecx = 0;
    r->eax = rd32(r, r->esi + 0x1c);
    wr32(r, r->ebp - 0x14, r->ecx);
    wr32(r, r->ebp - 0x18, r->ecx);
    r->edi = rd32(r, r->edi);
    if (r->eax == 0)
    {
        goto at_4ba59a;
    }
at_4ba56a:
    r->edx = rd32(r, r->ebp - 0x14);
    r->ecx = rd32(r, r->ebp - 0x1c);
    r->eax = rd32(r, r->ebp - 0x20);
    r->ebx = r->edi;
    push(r, r->edx);
    r->edx = r->esi;
    r->edi = r->edi + 0x80;
    call_all(r, rd32(r, r->ebp - 0x24));
    r->ecx = rd32(r, r->ebp - 0x14);
    r->ebx = rd32(r, r->ebp - 0x18);
    r->eax = rd32(r, r->esi + 0x24);
    r->edx = rd32(r, r->esi + 0x1c);
    r->ecx = r->ecx + r->eax;
    r->ebx = r->ebx + 1;
    wr32(r, r->ebp - 0x14, r->ecx);
    wr32(r, r->ebp - 0x18, r->ebx);
    if (r->ebx < r->edx && !r->port->env.failed)
    {
        goto at_4ba56a;
    }
at_4ba59a:
    r->ecx = rd32(r, r->ebp - 0x1c);
    r->ebx = rd32(r, r->ebp - 0x28);
    r->edi = rd32(r, r->esi + 0x24);
    r->edx = rd32(r, r->ebp - 0x30);
    r->edi = r->edi << 0x2;
    r->ebx = r->ebx + 0x4;
    r->ecx = r->ecx + r->edi;
    r->edi = rd32(r, r->ebp - 0x2c);
    wr32(r, r->ebp - 0x28, r->ebx);
    r->edi = r->edi + 1;
    wr32(r, r->ebp - 0x1c, r->ecx);
    wr32(r, r->ebp - 0x2c, r->edi);
    if ((int32_t)r->edi < (int32_t)r->edx && !r->port->env.failed)
    {
        goto at_4ba556;
    }
at_4ba5bf:
    r->ecx = rd32(r, r->ebp - 0x3c);
    r->ebx = rd32(r, r->ebp - 0x38);
    r->edi = rd32(r, r->ebp - 0x34);
    r->edx = rd32(r, r->ebp - 0x20);
    r->esi = r->esi + 0x54;
    r->ecx = r->ecx + 0x4;
    r->ebx = r->ebx + 0x4;
    r->edi = r->edi + 1;
    wr32(r, r->ebp - 0x3c, r->ecx);
    wr32(r, r->ebp - 0x38, r->ebx);
    r->ecx = rd32(r, r->edx + 0x24);
    wr32(r, r->ebp - 0x34, r->edi);
    if ((int32_t)r->edi < (int32_t)r->ecx && !r->port->env.failed)
    {
        goto at_4ba4e5;
    }
at_4ba5e9:
    r->eax = rd32(r, r->ebp - 0x20);
    r->ebx = rd32(r, r->eax + 0x9c);
    r->ebx = r->ebx + 1;
    r->esi = rd32(r, r->eax + 0x140);
    wr32(r, r->eax + 0x9c, r->ebx);
    if (r->ebx >= r->esi)
    {
        goto at_4ba646;
    }
    r->eax = 0x3;
at_4ba608:
    r->edi = rd32(r, r->ebp - 0x10);
    r->esi = rd32(r, r->ebp - 0xc);
    r->ecx = rd32(r, r->ebp - 0x8);
    r->ebx = rd32(r, r->ebp - 0x4);
    return;
at_4ba611:
    r->edx = rd32(r, r->ebp - 0x20);
    r->edx = rd32(r, r->edx + 0x1b4);
    r->eax = rd32(r, r->ebp - 0x20);
    call_all(r, rd32(r, r->edx));
    if (r->eax != 0 && !r->port->env.failed)
    {
        goto at_4ba48f;
    }
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4ba608;
at_4ba629:
    r->eax = rd32(r, r->esi + 0x20);
    r->ecx = rd32(r, r->esi + 0xc);
    r->edx = 0;
    div32(r, r->ecx);
    wr32(r, r->ebp - 0x30, r->edx);
    if (r->edx != 0 && !r->port->env.failed)
    {
        goto at_4ba52c;
    }
    wr32(r, r->ebp - 0x30, r->ecx);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4ba52c;
at_4ba646:
    r->eax = 0x4;
    r->edi = rd32(r, r->ebp - 0x10);
    r->esi = rd32(r, r->ebp - 0xc);
    r->ecx = rd32(r, r->ebp - 0x8);
    r->ebx = rd32(r, r->ebp - 0x4);
    return;
}

uint32_t vertrix_port_jpeg_decompress_coef_rows_4ba470(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x44
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
