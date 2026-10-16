#include "port_rtlyccrgbtables.h"

/* The routine at 0x4bb170 makes four memory-manager calls through [[eax+4]], each asking for 0x400
 * bytes from pool 1. */

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

static uint32_t rd32(Regs *r, uint32_t address)
{
    return port_u32(r->port, address, 0);
}

static void wr32(Regs *r, uint32_t address, uint32_t value)
{
    port_set32(r->port, address, 0, value);
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

/* Original 0x4bb170: The routine at 0x4bb170 makes four memory-manager calls through [[eax+4]],
 * each asking for 0x400 bytes from pool 1. It stores the four table pointers at +8, +0xc, +0x10 and
 * +0x14 of the deconverter object at [eax+0x1c8]. A 256-entry loop then fills them with libjpeg's
 * YCbCr-to-RGB lookups: Cr_r (1.402, 0x166e9) and Cb_b (1.772, 0x1c5a2) shifted right by 16, and
 * Cr_g (-0.71414, 0xb6d2) and Cb_g (-0.34414, 0x581a), with 0x8000 rounding added to Cb_g. Its only
 * caller is vertrix_port_color_deconverter_init_4bb6c0, at 0x4bb7d9 and 0x4bb810. Evidence: no
 * calls. Register-for-register from the listing (0x4bb17b..0x4bb258); labels are the original
 * addresses. */
static void run(Regs *r)
{
    r->esi = r->eax;
    r->ebx = 0x400;
    r->edi = rd32(r, r->eax + 0x4);
    r->edx = 0x1;
    r->ecx = rd32(r, r->eax + 0x1c8);
    call_all(r, rd32(r, r->edi));
    wr32(r, r->ecx + 0x8, r->eax);
    r->ebx = 0x400;
    r->edi = rd32(r, r->esi + 0x4);
    r->edx = 0x1;
    r->eax = r->esi;
    call_all(r, rd32(r, r->edi));
    wr32(r, r->ecx + 0xc, r->eax);
    r->ebx = 0x400;
    r->edi = rd32(r, r->esi + 0x4);
    r->edx = 0x1;
    r->eax = r->esi;
    call_all(r, rd32(r, r->edi));
    wr32(r, r->ecx + 0x10, r->eax);
    r->ebx = 0x400;
    r->edi = rd32(r, r->esi + 0x4);
    r->edx = 0x1;
    r->eax = r->esi;
    call_all(r, rd32(r, r->edi));
    wr32(r, r->ecx + 0x14, r->eax);
    r->eax = 0xffd3f300u;
    r->eax = 0u - r->eax;
    wr32(r, r->ebp - 0x18, r->eax);
    r->eax = 0xffa49700u;
    r->edx = 0xff1daf00u;
    r->eax = 0u - r->eax;
    r->ebx = 0xff4d0b80u;
    wr32(r, r->ebp - 0x1c, r->eax);
    r->eax = 0;
at_4bb1f1:
    r->edi = rd32(r, r->ecx + 0x8);
    r->esi = r->ebx;
    r->edi = r->edi + r->eax;
    r->esi = (uint32_t)((int32_t)r->esi >> 0x10);
    wr32(r, r->edi, r->esi);
    r->edi = r->edx;
    r->esi = rd32(r, r->ecx + 0xc);
    r->edi = (uint32_t)((int32_t)r->edi >> 0x10);
    wr32(r, r->esi + r->eax, r->edi);
    r->eax = r->eax + 0x4;
    r->esi = rd32(r, r->ecx + 0x10);
    r->edi = rd32(r, r->ebp - 0x1c);
    r->ebx = r->ebx + 0x166e9;
    wr32(r, r->esi + r->eax - 0x4, r->edi);
    r->edi = rd32(r, r->ebp - 0x18);
    r->esi = rd32(r, r->ecx + 0x14);
    r->edi = r->edi + 0x8000;
    r->edx = r->edx + 0x1c5a2;
    wr32(r, r->esi + r->eax - 0x4, r->edi);
    r->esi = rd32(r, r->ebp - 0x18);
    r->edi = rd32(r, r->ebp - 0x1c);
    r->esi = r->esi - 0x581a;
    r->edi = r->edi - 0xb6d2;
    wr32(r, r->ebp - 0x18, r->esi);
    wr32(r, r->ebp - 0x1c, r->edi);
    if (r->eax != 0x400 && !r->port->env.failed)
    {
        goto at_4bb1f1;
    }
    r->edi = pop(r);
    r->esi = pop(r);
    r->edx = pop(r);
    r->ecx = pop(r);
    r->ebx = pop(r);
    r->ebp = pop(r);
}

uint32_t vertrix_port_jpeg_build_ycc_rgb_table_4bb170(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x20
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
