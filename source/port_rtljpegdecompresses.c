#include "port_rtljpegdecompresses.h"

/* 0x4b9f70 has the shape of libjpeg's jdcoefct decompress_onepass, which the Delphi JPEG unit links
 * in. */

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

/* An indirect call (an import or a method): every value pushed passed and popped, as stdcall. */
static void call_all(Regs *r, uint32_t target)
{
    call_with_stack(r, target, r->pushed, 0);
}

/* Original 0x4b9f70: 0x4b9f70 has the shape of libjpeg's jdcoefct decompress_onepass, which the
 * Delphi JPEG unit links in. It walks the MCU rows and columns held by the coefficient controller
 * at [cinfo+0x1ac]. For each MCU it zeroes the block buffer with 0x4c98f0 and decodes it through
 * [[cinfo+0x1bc]+4]. It then calls the per-component inverse DCT at [[cinfo+0x1c0]+4+ci*4] for each
 * needed component in [cinfo+0x14c]. If the input is suspended it saves the MCU counters at +0x18
 * and +0x14 and returns 0. Otherwise it increments the iMCU row counters at +0x9c and +0x94. While
 * rows remain it calls the start-row routine 0x4b9d70 and returns 3. After the last row it calls
 * [[cinfo+0x1b4]+0xc] (finish_input_pass) and returns 4. Evidence: calls 0x4c98f0, 0x4b9d70.
 * Register-for-register from the listing (0x4b9f7a..0x4ba20a); labels are the original addresses.
 */
static void run(Regs *r)
{
    wr32(r, r->ebp - 0x20, r->eax);
    wr32(r, r->ebp - 0x58, r->edx);
    r->eax = rd32(r, r->eax + 0x1ac);
    wr32(r, r->ebp - 0x3c, r->eax);
    r->eax = rd32(r, r->ebp - 0x20);
    r->eax = rd32(r, r->eax + 0x15c);
    r->eax = r->eax - 1;
    wr32(r, r->ebp - 0x54, r->eax);
    r->eax = rd32(r, r->ebp - 0x20);
    r->eax = rd32(r, r->eax + 0x140);
    r->eax = r->eax - 1;
    wr32(r, r->ebp - 0x40, r->eax);
    r->eax = rd32(r, r->ebp - 0x3c);
    r->edx = rd32(r, r->ebp - 0x3c);
    r->eax = rd32(r, r->eax + 0x18);
    r->ecx = rd32(r, r->edx + 0x1c);
    wr32(r, r->ebp - 0x50, r->eax);
    if ((int32_t)r->eax >= (int32_t)r->ecx)
    {
        goto at_4ba176;
    }
    r->eax = r->edx + 0x20;
    wr32(r, r->ebp - 0x5c, r->eax);
at_4b9fc0:
    r->eax = rd32(r, r->ebp - 0x3c);
    r->eax = rd32(r, r->eax + 0x14);
    r->ebx = rd32(r, r->ebp - 0x54);
    wr32(r, r->ebp - 0x4c, r->eax);
    if (r->eax > r->ebx)
    {
        goto at_4ba15a;
    }
at_4b9fd4:
    r->edx = rd32(r, r->ebp - 0x20);
    r->eax = rd32(r, r->ebp - 0x3c);
    r->edx = rd32(r, r->edx + 0x164);
    r->eax = rd32(r, r->eax + 0x20);
    r->edx = r->edx << 0x7;
    r->ebx = rd32(r, r->ebp - 0x20);
    call(r, 0x4c98f0, 0);
    r->ebx = rd32(r, r->ebx + 0x1bc);
    r->edx = rd32(r, r->ebp - 0x5c);
    r->eax = rd32(r, r->ebp - 0x20);
    call_all(r, rd32(r, r->ebx + 0x4));
    if (r->eax == 0)
    {
        goto at_4ba1b5;
    }
    r->eax = 0;
    wr32(r, r->ebp - 0x2c, r->eax);
    wr32(r, r->ebp - 0x48, r->eax);
    r->eax = rd32(r, r->ebp - 0x20);
    if ((int32_t)rd32(r, r->eax + 0x148) <= (int32_t)0x0)
    {
        goto at_4ba148;
    }
    wr32(r, r->ebp - 0x44, r->eax);
at_4ba020:
    r->esi = rd32(r, r->ebp - 0x44);
    r->esi = rd32(r, r->esi + 0x14c);
    if (rd32(r, r->esi + 0x30) == 0x0)
    {
        goto at_4ba1c8;
    }
    r->edi = rd32(r, r->ebp - 0x20);
    r->ebx = rd32(r, r->esi + 0x4);
    r->edi = rd32(r, r->edi + 0x1c0);
    r->eax = rd32(r, r->edi + r->ebx * 4 + 0x4);
    r->ecx = rd32(r, r->ebp - 0x54);
    wr32(r, r->ebp - 0x28, r->eax);
    if (r->ecx <= rd32(r, r->ebp - 0x4c))
    {
        goto at_4ba1d8;
    }
    r->ebx = rd32(r, r->esi + 0x34);
at_4ba055:
    wr32(r, r->ebp - 0x24, r->ebx);
    r->ebx = rd32(r, r->esi + 0x4);
    r->edi = rd32(r, r->ebp - 0x58);
    r->ebx = r->ebx << 0x2;
    r->eax = rd32(r, r->esi + 0x24);
    r->edi = r->edi + r->ebx;
    r->ebx = rd32(r, r->ebp - 0x50);
    r->ebx = r->ebx * r->eax;
    r->edx = rd32(r, r->esi + 0x40);
    r->eax = rd32(r, r->ebp - 0x4c);
    r->eax = r->eax * r->edx;
    r->edi = rd32(r, r->edi);
    r->ebx = r->ebx << 0x2;
    r->ecx = 0;
    r->edi = r->edi + r->ebx;
    wr32(r, r->ebp - 0x30, r->ecx);
    wr32(r, r->ebp - 0x1c, r->edi);
    r->ebx = rd32(r, r->esi + 0x38);
    wr32(r, r->ebp - 0x38, r->eax);
    if ((int32_t)r->ebx <= 0)
    {
        goto at_4ba127;
    }
    r->eax = rd32(r, r->ebp - 0x50);
    wr32(r, r->ebp - 0x34, r->eax);
at_4ba098:
    r->eax = rd32(r, r->ebp - 0x20);
    r->edi = rd32(r, r->ebp - 0x40);
    if (r->edi <= rd32(r, r->eax + 0x94))
    {
        goto at_4ba1e0;
    }
at_4ba0aa:
    r->eax = rd32(r, r->ebp - 0x38);
    r->ebx = rd32(r, r->ebp - 0x24);
    r->ecx = 0;
    wr32(r, r->ebp - 0x14, r->eax);
    wr32(r, r->ebp - 0x18, r->ecx);
    if ((int32_t)r->ebx <= 0)
    {
        goto at_4ba0f5;
    }
    r->ebx = rd32(r, r->ebp - 0x2c);
    r->edi = rd32(r, r->ebp - 0x3c);
    r->ebx = r->ebx << 0x2;
    r->edi = r->edi + r->ebx;
at_4ba0c7:
    r->eax = rd32(r, r->ebp - 0x14);
    r->ecx = rd32(r, r->ebp - 0x1c);
    r->edx = r->esi;
    r->ebx = rd32(r, r->edi + 0x20);
    push(r, r->eax);
    r->eax = rd32(r, r->ebp - 0x20);
    r->edi = r->edi + 0x4;
    call_all(r, rd32(r, r->ebp - 0x28));
    r->edx = rd32(r, r->ebp - 0x14);
    r->ecx = rd32(r, r->ebp - 0x18);
    r->eax = rd32(r, r->esi + 0x24);
    r->ebx = rd32(r, r->ebp - 0x24);
    r->edx = r->edx + r->eax;
    r->ecx = r->ecx + 1;
    wr32(r, r->ebp - 0x14, r->edx);
    wr32(r, r->ebp - 0x18, r->ecx);
    if ((int32_t)r->ecx < (int32_t)r->ebx && !r->port->env.failed)
    {
        goto at_4ba0c7;
    }
at_4ba0f5:
    r->edi = rd32(r, r->ebp - 0x2c);
    r->edx = rd32(r, r->ebp - 0x34);
    r->ecx = rd32(r, r->ebp - 0x30);
    r->ebx = rd32(r, r->esi + 0x24);
    r->eax = rd32(r, r->esi + 0x34);
    r->ebx = r->ebx << 0x2;
    r->edx = r->edx + 1;
    r->ecx = r->ecx + 1;
    r->edi = r->edi + r->eax;
    r->eax = rd32(r, r->ebp - 0x1c);
    wr32(r, r->ebp - 0x2c, r->edi);
    wr32(r, r->ebp - 0x34, r->edx);
    wr32(r, r->ebp - 0x30, r->ecx);
    r->eax = r->eax + r->ebx;
    r->ebx = rd32(r, r->esi + 0x38);
    wr32(r, r->ebp - 0x1c, r->eax);
    if ((int32_t)r->ecx < (int32_t)r->ebx && !r->port->env.failed)
    {
        goto at_4ba098;
    }
at_4ba127:
    r->ebx = rd32(r, r->ebp - 0x44);
    r->esi = rd32(r, r->ebp - 0x48);
    r->edx = rd32(r, r->ebp - 0x20);
    r->ebx = r->ebx + 0x4;
    r->esi = r->esi + 1;
    r->edi = rd32(r, r->edx + 0x148);
    wr32(r, r->ebp - 0x44, r->ebx);
    wr32(r, r->ebp - 0x48, r->esi);
    if ((int32_t)r->esi < (int32_t)r->edi && !r->port->env.failed)
    {
        goto at_4ba020;
    }
at_4ba148:
    r->esi = rd32(r, r->ebp - 0x4c);
    r->esi = r->esi + 1;
    r->edi = rd32(r, r->ebp - 0x54);
    wr32(r, r->ebp - 0x4c, r->esi);
    if (r->esi <= r->edi && !r->port->env.failed)
    {
        goto at_4b9fd4;
    }
at_4ba15a:
    r->eax = rd32(r, r->ebp - 0x3c);
    r->ebx = rd32(r, r->ebp - 0x50);
    wr32(r, r->eax + 0x14, 0x0);
    r->ebx = r->ebx + 1;
    r->esi = rd32(r, r->eax + 0x1c);
    wr32(r, r->ebp - 0x50, r->ebx);
    if ((int32_t)r->ebx < (int32_t)r->esi && !r->port->env.failed)
    {
        goto at_4b9fc0;
    }
at_4ba176:
    r->eax = rd32(r, r->ebp - 0x20);
    r->edi = rd32(r, r->eax + 0x9c);
    r->edx = rd32(r, r->eax + 0x94);
    r->edi = r->edi + 1;
    r->edx = r->edx + 1;
    wr32(r, r->eax + 0x9c, r->edi);
    wr32(r, r->eax + 0x94, r->edx);
    r->eax = r->edx;
    r->edx = rd32(r, r->ebp - 0x20);
    if (r->eax >= rd32(r, r->edx + 0x140))
    {
        goto at_4ba1f1;
    }
    r->eax = r->edx;
    call(r, 0x4b9d70, 0);
    r->eax = 0x3;
at_4ba1ac:
    r->edi = rd32(r, r->ebp - 0x10);
    r->esi = rd32(r, r->ebp - 0xc);
    r->ecx = rd32(r, r->ebp - 0x8);
    r->ebx = rd32(r, r->ebp - 0x4);
    return;
at_4ba1b5:
    r->edx = rd32(r, r->ebp - 0x3c);
    r->eax = rd32(r, r->ebp - 0x50);
    wr32(r, r->edx + 0x18, r->eax);
    r->eax = rd32(r, r->ebp - 0x4c);
    wr32(r, r->edx + 0x14, r->eax);
    r->eax = 0;
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4ba1ac;
at_4ba1c8:
    r->edx = rd32(r, r->ebp - 0x2c);
    r->eax = rd32(r, r->esi + 0x3c);
    r->edx = r->edx + r->eax;
    wr32(r, r->ebp - 0x2c, r->edx);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4ba127;
at_4ba1d8:
    r->ebx = rd32(r, r->esi + 0x44);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4ba055;
at_4ba1e0:
    r->eax = rd32(r, r->ebp - 0x34);
    if ((int32_t)r->eax < (int32_t)rd32(r, r->esi + 0x48) && !r->port->env.failed)
    {
        goto at_4ba0aa;
    }
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4ba0f5;
at_4ba1f1:
    r->edx = rd32(r, r->edx + 0x1b4);
    r->eax = rd32(r, r->ebp - 0x20);
    call_all(r, rd32(r, r->edx + 0xc));
    r->eax = 0x4;
    r->edi = rd32(r, r->ebp - 0x10);
    r->esi = rd32(r, r->ebp - 0xc);
    r->ecx = rd32(r, r->ebp - 0x8);
    r->ebx = rd32(r, r->ebp - 0x4);
    return;
}

uint32_t vertrix_port_jpeg_decompress_onepass_4b9f70(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x60
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
