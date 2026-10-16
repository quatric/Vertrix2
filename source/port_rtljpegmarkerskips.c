#include "port_rtljpegmarkerskips.h"

/* At 0x4bf6a0, reads a 2-byte big-endian marker length from the source manager at [cinfo+0x18]. */

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

/* Original 0x4bf6a0: At 0x4bf6a0, reads a 2-byte big-endian marker length from the source manager
 * at [cinfo+0x18]. It calls fill_input_buffer (+0xc) whenever the buffer is empty and returns 0 if
 * that call fails. It sets err->msg_code to 0x5b with msg_parm = (unread_marker [cinfo+0x1a0],
 * length-2) and emits a level-1 trace through err+4. It then stores back next_input_byte and
 * bytes_in_buffer, calls skip_input_data (+0x10) for length-2 bytes when that is positive, and
 * returns 1. This is libjpeg's skip_variable. Evidence: no calls. Register-for-register from the
 * listing (0x4bf6ab..0x4bf760); labels are the original addresses. */
static void run(Regs *r)
{
    r->ecx = r->eax;
    r->ebx = rd32(r, r->eax + 0x18);
    r->eax = rd32(r, r->ebx + 0x4);
    r->esi = rd32(r, r->ebx);
    wr32(r, r->ebp - 0x18, r->eax);
    if (r->eax == 0)
    {
        goto at_4bf74f;
    }
at_4bf6c0:
    r->esi = r->esi + 1;
    r->eax = 0;
    r->edi = rd32(r, r->ebp - 0x18);
    set_low8(&r->eax, rd8(r, r->esi - 0x1));
    r->edi = r->edi - 1;
    r->eax = r->eax << 0x8;
    wr32(r, r->ebp - 0x18, r->edi);
    wr32(r, r->ebp - 0x1c, r->eax);
    if (r->edi != 0)
    {
        goto at_4bf6e8;
    }
    r->eax = r->ecx;
    call_all(r, rd32(r, r->ebx + 0xc));
    if (r->eax == 0)
    {
        goto at_4bf745;
    }
    r->eax = rd32(r, r->ebx + 0x4);
    r->esi = rd32(r, r->ebx);
    wr32(r, r->ebp - 0x18, r->eax);
at_4bf6e8:
    r->eax = 0;
    r->edi = rd32(r, r->ebp - 0x1c);
    set_low8(&r->eax, rd8(r, r->esi));
    r->edx = rd32(r, r->ebp - 0x18);
    r->edi = r->edi + r->eax;
    r->eax = rd32(r, r->ecx);
    r->edx = r->edx - 1;
    wr32(r, r->eax + 0x14, 0x5b);
    wr32(r, r->ebp - 0x18, r->edx);
    r->edx = rd32(r, r->ecx);
    r->eax = rd32(r, r->ecx + 0x1a0);
    wr32(r, r->ebp - 0x1c, r->edi);
    wr32(r, r->edx + 0x18, r->eax);
    r->edx = r->edi - 0x2;
    r->eax = rd32(r, r->ecx);
    wr32(r, r->ebp - 0x1c, r->edx);
    wr32(r, r->eax + 0x1c, r->edx);
    r->edx = 0x1;
    r->edi = rd32(r, r->ecx);
    r->eax = r->ecx;
    r->esi = r->esi + 1;
    call_all(r, rd32(r, r->edi + 0x4));
    r->eax = rd32(r, r->ebp - 0x18);
    wr32(r, r->ebx, r->esi);
    wr32(r, r->ebx + 0x4, r->eax);
    if ((int32_t)rd32(r, r->ebp - 0x1c) <= (int32_t)0x0)
    {
        goto at_4bf740;
    }
    r->ebx = rd32(r, r->ecx + 0x18);
    r->edx = rd32(r, r->ebp - 0x1c);
    r->eax = r->ecx;
    call_all(r, rd32(r, r->ebx + 0x10));
at_4bf740:
    r->eax = 0x1;
at_4bf745:
    r->edi = rd32(r, r->ebp - 0x14);
    r->esi = rd32(r, r->ebp - 0x10);
    r->edx = rd32(r, r->ebp - 0xc);
    r->ecx = rd32(r, r->ebp - 0x8);
    r->ebx = rd32(r, r->ebp - 0x4);
    return;
at_4bf74f:
    r->eax = r->ecx;
    call_all(r, rd32(r, r->ebx + 0xc));
    if (r->eax == 0 && !r->port->env.failed)
    {
        goto at_4bf745;
    }
    r->eax = rd32(r, r->ebx + 0x4);
    r->esi = rd32(r, r->ebx);
    wr32(r, r->ebp - 0x18, r->eax);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4bf6c0;
}

uint32_t vertrix_port_jpeg_skip_variable_marker_4bf6a0(PORT_SIGNATURE)
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
