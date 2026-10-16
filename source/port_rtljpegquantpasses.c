#include "port_rtljpegquantpasses.h"

/* 0x4c9550 has the structure of libjpeg's jquant2 start_pass_2_quant and is reached through a
 * method pointer. */

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

static void wr32(Regs *r, uint32_t address, uint32_t value)
{
    port_set32(r->port, address, 0, value);
}

/* An indirect call (an import or a method): every value pushed passed and popped, as stdcall. */
static void call_all(Regs *r, uint32_t target)
{
    call_with_stack(r, target, r->pushed, 0);
}

/* Original 0x4c9550: 0x4c9550 has the structure of libjpeg's jquant2 start_pass_2_quant and is
 * reached through a method pointer. It forces any nonzero dither mode (+0x58) to 2. On a prescan
 * pass it installs 0x4c6ff0 and 0x4c90e0, then zeroes 32 histogram rows of 0x1000 bytes each
 * through 0x4c98f0. Otherwise it installs 0x4c8cd0 (or 0x4c8be0 when the dither mode is not 2) plus
 * 0x4c93c0, and raises errors 0x38 or 0x39 when the colour count at +0x84 is below 1 or above 256.
 * In dither mode 2 it allocates (if needed) and zeroes an error buffer of (width+2)*3*2 bytes at
 * +0x20, calls 0x4c9030 when the table at +0x28 is unset, and clears +0x24. Finally it zeroes the
 * histogram when the needs-zeroed flag at +0x1c is set. Evidence: calls 0x4c98f0, 0x4c9030.
 * Register-for-register from the listing (0x4c955a..0x4c9687); labels are the original addresses.
 */
static void run(Regs *r)
{
    r->ecx = r->eax;
    r->esi = rd32(r, r->eax + 0x1cc);
    r->eax = rd32(r, r->esi + 0x18);
    r->ebx = rd32(r, r->ecx + 0x58);
    wr32(r, r->ebp - 0x14, r->eax);
    if (r->ebx != 0)
    {
        goto at_4c95b6;
    }
at_4c956f:
    if (r->edx == 0)
    {
        goto at_4c95bf;
    }
    wr32(r, r->esi + 0x4, 0x4c6ff0);
    wr32(r, r->esi + 0x8, 0x4c90e0);
    wr32(r, r->esi + 0x1c, 0x1);
at_4c9588:
    r->ecx = rd32(r, r->ebp - 0x14);
    r->ebx = r->ecx + 0x80;
    r->edi = 0x1000;
at_4c9596:
    r->edx = r->edi;
    r->eax = rd32(r, r->ecx);
    r->ecx = r->ecx + 0x4;
    call(r, 0x4c98f0, 0);
    if (r->ecx != r->ebx && !r->port->env.failed)
    {
        goto at_4c9596;
    }
    wr32(r, r->esi + 0x1c, 0x0);
    r->edi = rd32(r, r->ebp - 0x10);
    r->esi = rd32(r, r->ebp - 0xc);
    r->ecx = rd32(r, r->ebp - 0x8);
    r->ebx = rd32(r, r->ebp - 0x4);
    return;
at_4c95b6:
    wr32(r, r->ecx + 0x58, 0x2);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4c956f;
at_4c95bf:
    if (rd32(r, r->ecx + 0x58) != 0x2)
    {
        goto at_4c9680;
    }
    wr32(r, r->esi + 0x4, 0x4c8cd0);
at_4c95d0:
    wr32(r, r->esi + 0x8, 0x4c93c0);
    r->ebx = rd32(r, r->ecx + 0x84);
    if ((int32_t)r->ebx >= (int32_t)0x1)
    {
        goto at_4c95fa;
    }
    r->eax = rd32(r, r->ecx);
    wr32(r, r->eax + 0x14, 0x38);
    r->eax = rd32(r, r->ecx);
    wr32(r, r->eax + 0x18, 0x1);
    r->edx = rd32(r, r->ecx);
    r->eax = r->ecx;
    call_all(r, rd32(r, r->edx));
at_4c95fa:
    if ((int32_t)r->ebx <= (int32_t)0x100)
    {
        goto at_4c961a;
    }
    r->eax = rd32(r, r->ecx);
    wr32(r, r->eax + 0x14, 0x39);
    r->eax = rd32(r, r->ecx);
    wr32(r, r->eax + 0x18, 0x100);
    r->edx = rd32(r, r->ecx);
    r->eax = r->ecx;
    call_all(r, rd32(r, r->edx));
at_4c961a:
    r->eax = rd32(r, r->ecx + 0x58);
    if (r->eax != 0x2)
    {
        goto at_4c966d;
    }
    r->edx = rd32(r, r->ecx + 0x70);
    r->edx = r->edx + r->eax;
    r->eax = r->edx * 4;
    r->eax = r->eax - r->edx;
    r->eax = r->eax + r->eax;
    r->edx = rd32(r, r->esi + 0x20);
    wr32(r, r->ebp - 0x18, r->eax);
    if (r->edx != 0)
    {
        goto at_4c964e;
    }
    r->edx = 0x1;
    r->edi = rd32(r, r->ecx + 0x4);
    r->ebx = r->eax;
    r->eax = r->ecx;
    call_all(r, rd32(r, r->edi + 0x4));
    wr32(r, r->esi + 0x20, r->eax);
at_4c964e:
    r->edx = rd32(r, r->ebp - 0x18);
    r->eax = rd32(r, r->esi + 0x20);
    call(r, 0x4c98f0, 0);
    if (rd32(r, r->esi + 0x28) != 0x0)
    {
        goto at_4c9666;
    }
    r->eax = r->ecx;
    call(r, 0x4c9030, 0);
at_4c9666:
    wr32(r, r->esi + 0x24, 0x0);
at_4c966d:
    if (rd32(r, r->esi + 0x1c) != 0x0 && !r->port->env.failed)
    {
        goto at_4c9588;
    }
    r->edi = rd32(r, r->ebp - 0x10);
    r->esi = rd32(r, r->ebp - 0xc);
    r->ecx = rd32(r, r->ebp - 0x8);
    r->ebx = rd32(r, r->ebp - 0x4);
    return;
at_4c9680:
    wr32(r, r->esi + 0x4, 0x4c8be0);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4c95d0;
}

uint32_t vertrix_port_jpeg_quant2_start_pass_4c9550(PORT_SIGNATURE)
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
    port_set32(&port, r.ebp, -0x4u, entry->ebx);
    port_set32(&port, r.ebp, -0x8u, entry->ecx);
    port_set32(&port, r.ebp, -0xcu, entry->esi);
    port_set32(&port, r.ebp, -0x10u, entry->edi);
    run(&r);
    return port_return(&port, r.eax, r.edx);
}
