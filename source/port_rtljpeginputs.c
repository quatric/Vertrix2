#include "port_rtljpeginputs.h"

/* This routine matches libjpeg's jdinput consume_markers with initial_setup inlined (0x4bcea0). */

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

static uint32_t flag_mask(const Regs *r)
{
    return r->fw == 8 ? 0xffu : r->fw == 16 ? 0xffffu : 0xffffffffu;
}

static uint32_t result(const Regs *r)
{
    uint32_t mask = flag_mask(r);
    if (r->fk == F_SUB)
    {
        return (r->fa - r->fb) & mask;
    }
    if (r->fk == F_ADD)
    {
        return (r->fa + r->fb) & mask;
    }
    return r->fa & mask;
}

static uint32_t carry(const Regs *r)
{
    uint32_t mask = flag_mask(r);
    if (r->fk == F_SUB)
    {
        return (r->fa & mask) < (r->fb & mask);
    }
    if (r->fk == F_ADD)
    {
        return result(r) < (r->fa & mask);
    }
    if (r->fk == F_INC || r->fk == F_DEC)
    {
        return r->fc;
    }
    return 0;
}

/* The flags of an instruction recorded (width 8, 16 or 32). */
static void flags(Regs *r, unsigned kind, uint32_t a, uint32_t b, unsigned width)
{
    if (kind == F_INC || kind == F_DEC)
    {
        r->fc = carry(r);
    }
    r->fk = kind;
    r->fa = a;
    r->fb = b;
    r->fw = width;
}

static uint32_t overflow(const Regs *r)
{
    uint32_t top = 1u << (r->fw - 1);
    uint32_t value = result(r);
    if (r->fk == F_SUB)
    {
        return (((r->fa ^ r->fb) & (r->fa ^ value)) & top) != 0;
    }
    if (r->fk == F_ADD)
    {
        return ((~(r->fa ^ r->fb) & (r->fa ^ value)) & top) != 0;
    }
    if (r->fk == F_INC)
    {
        return value == top;
    }
    if (r->fk == F_DEC)
    {
        return value == top - 1;
    }
    return 0;
}

/* A condition of the recorded flags. */
static uint32_t cond(const Regs *r, unsigned code)
{
    uint32_t zero = result(r) == 0;
    uint32_t sign = (result(r) >> (r->fw - 1)) & 1;
    uint32_t less = sign != overflow(r);
    switch (code)
    {
        case CC_E:
            return zero;
        case CC_NE:
            return !zero;
        case CC_B:
            return carry(r);
        case CC_AE:
            return !carry(r);
        case CC_BE:
            return carry(r) || zero;
        case CC_A:
            return !carry(r) && !zero;
        case CC_L:
            return less;
        case CC_GE:
            return !less;
        case CC_LE:
            return less || zero;
        case CC_G:
            return !less && !zero;
        case CC_S:
            return sign;
        default:
            return !sign;
    }
}

/* An indirect call (an import or a method): every value pushed passed and popped, as stdcall. */
static void call_all(Regs *r, uint32_t target)
{
    call_with_stack(r, target, r->pushed, 0);
}

/* Original 0x4bcea0: This routine matches libjpeg's jdinput consume_markers with initial_setup
 * inlined (0x4bcea0). It reads the input controller at [cinfo+0x1b4] and returns 2
 * (JPEG_REACHED_EOI) once eof_reached ([+0x14]) is set. While inheaders ([+0x18]) is set, it checks
 * the image height and width ([+0x20], [+0x1c]) against 0xffdc (65500), data_precision ([+0xd4])
 * against 8 and num_components ([+0x24]) against 10. It raises errors 0x29, 0xf and 0x1a through
 * the error manager, and 0x12 when a sampling factor is outside 1..4. It then sets
 * max_h/v_samp_factor (0x134/0x138) and DCT size 8 (0x13c), fills each 0x54-byte component's sizes
 * through jdiv_round_up (0x4c9820), sets total_iMCU_rows (0x140), sets has_multiple_scans when
 * num_components exceeds comps_in_scan ([+0x148]), and clears inheaders. Evidence: calls 0x4c9820,
 * 0x4bcbc0. Register-for-register from the listing (0x4bceab..0x4bd1bd); labels are the original
 * addresses. */
static void run(Regs *r)
{
    r->edx = r->eax;
    r->edi = rd32(r, r->eax + 0x1b4);
    if (rd32(r, r->edi + 0x14) == 0x0)
    {
        goto at_4bd18d;
    }
    r->eax = 0x2;
    r->edi = rd32(r, r->ebp - 0x14);
    r->esi = rd32(r, r->ebp - 0x10);
    r->edx = rd32(r, r->ebp - 0xc);
    r->ecx = rd32(r, r->ebp - 0x8);
    r->ebx = rd32(r, r->ebp - 0x4);
    return;
at_4bcecc:
    if (rd32(r, r->edi + 0x18) == 0x0)
    {
        goto at_4bd103;
    }
    r->ebx = rd32(r, r->edx + 0x20);
    r->ecx = r->edx;
    if ((int32_t)r->ebx <= (int32_t)0xffdc)
    {
        goto at_4bd0a3;
    }
at_4bcee7:
    r->eax = rd32(r, r->ecx);
    wr32(r, r->eax + 0x14, 0x29);
    r->eax = rd32(r, r->ecx);
    wr32(r, r->eax + 0x18, 0xffdc);
    r->edx = rd32(r, r->ecx);
    r->eax = r->ecx;
    call_all(r, rd32(r, r->edx));
at_4bceff:
    if (rd32(r, r->ecx + 0xd4) == 0x8)
    {
        goto at_4bcf22;
    }
    r->eax = rd32(r, r->ecx);
    wr32(r, r->eax + 0x14, 0xf);
    r->eax = rd32(r, r->ecx);
    r->edx = rd32(r, r->ecx + 0xd4);
    wr32(r, r->eax + 0x18, r->edx);
    r->edx = rd32(r, r->ecx);
    r->eax = r->ecx;
    call_all(r, rd32(r, r->edx));
at_4bcf22:
    if ((int32_t)rd32(r, r->ecx + 0x24) <= (int32_t)0xa)
    {
        goto at_4bcf48;
    }
    r->eax = rd32(r, r->ecx);
    wr32(r, r->eax + 0x14, 0x1a);
    r->edx = rd32(r, r->ecx);
    r->eax = rd32(r, r->ecx + 0x24);
    wr32(r, r->edx + 0x18, r->eax);
    r->eax = rd32(r, r->ecx);
    wr32(r, r->eax + 0x1c, 0xa);
    r->edx = rd32(r, r->ecx);
    r->eax = r->ecx;
    call_all(r, rd32(r, r->edx));
at_4bcf48:
    wr32(r, r->ecx + 0x134, 0x1);
    wr32(r, r->ecx + 0x138, 0x1);
    r->ebx = rd32(r, r->ecx + 0xd8);
    r->esi = rd32(r, r->ecx + 0x24);
    r->edx = 0;
    if ((int32_t)r->esi <= 0)
    {
        goto at_4bcfc3;
    }
at_4bcf6b:
    r->esi = rd32(r, r->ebx + 0x8);
    if ((int32_t)r->esi <= 0)
    {
        goto at_4bcf7b;
    }
    if ((int32_t)r->esi <= (int32_t)0x4)
    {
        goto at_4bd0b5;
    }
at_4bcf7b:
    r->eax = rd32(r, r->ecx);
    wr32(r, r->eax + 0x14, 0x12);
    r->esi = rd32(r, r->ecx);
    r->eax = r->ecx;
    call_all(r, rd32(r, r->esi));
at_4bcf8a:
    r->eax = rd32(r, r->ecx + 0x134);
    r->esi = rd32(r, r->ebx + 0x8);
    if ((int32_t)r->eax <= (int32_t)r->esi)
    {
        goto at_4bd0ce;
    }
at_4bcf9b:
    wr32(r, r->ecx + 0x134, r->eax);
    r->eax = rd32(r, r->ecx + 0x138);
    r->esi = rd32(r, r->ebx + 0xc);
    if ((int32_t)r->eax <= (int32_t)r->esi)
    {
        goto at_4bd0d5;
    }
at_4bcfb2:
    wr32(r, r->ecx + 0x138, r->eax);
    r->edx = r->edx + 1;
    r->eax = rd32(r, r->ecx + 0x24);
    r->ebx = r->ebx + 0x54;
    if ((int32_t)r->edx < (int32_t)r->eax && !r->port->env.failed)
    {
        goto at_4bcf6b;
    }
at_4bcfc3:
    wr32(r, r->ecx + 0x13c, 0x8);
    r->ebx = rd32(r, r->ecx + 0xd8);
    r->edx = rd32(r, r->ecx + 0x24);
    r->esi = 0;
    if ((int32_t)r->edx <= 0)
    {
        goto at_4bd060;
    }
at_4bcfe0:
    wr32(r, r->ebx + 0x24, 0x8);
    r->eax = rd32(r, r->ecx + 0x1c);
    r->eax = r->eax * rd32(r, r->ebx + 0x8);
    r->edx = rd32(r, r->ecx + 0x134);
    r->edx = r->edx << 0x3;
    call(r, 0x4c9820, 0);
    wr32(r, r->ebx + 0x1c, r->eax);
    r->eax = rd32(r, r->ecx + 0x20);
    r->eax = r->eax * rd32(r, r->ebx + 0xc);
    r->edx = rd32(r, r->ecx + 0x138);
    r->edx = r->edx << 0x3;
    call(r, 0x4c9820, 0);
    wr32(r, r->ebx + 0x20, r->eax);
    r->eax = rd32(r, r->ecx + 0x1c);
    r->eax = r->eax * rd32(r, r->ebx + 0x8);
    r->edx = rd32(r, r->ecx + 0x134);
    call(r, 0x4c9820, 0);
    wr32(r, r->ebx + 0x28, r->eax);
    r->eax = rd32(r, r->ecx + 0x20);
    r->eax = r->eax * rd32(r, r->ebx + 0xc);
    r->edx = rd32(r, r->ecx + 0x138);
    call(r, 0x4c9820, 0);
    wr32(r, r->ebx + 0x30, 0x1);
    wr32(r, r->ebx + 0x4c, 0x0);
    wr32(r, r->ebx + 0x2c, r->eax);
    r->esi = r->esi + 1;
    r->eax = rd32(r, r->ecx + 0x24);
    r->ebx = r->ebx + 0x54;
    if ((int32_t)r->esi < (int32_t)r->eax && !r->port->env.failed)
    {
        goto at_4bcfe0;
    }
at_4bd060:
    r->edx = rd32(r, r->ecx + 0x138);
    r->eax = rd32(r, r->ecx + 0x20);
    r->edx = r->edx << 0x3;
    call(r, 0x4c9820, 0);
    wr32(r, r->ecx + 0x140, r->eax);
    r->edx = rd32(r, r->ecx + 0x24);
    if ((int32_t)r->edx <= (int32_t)rd32(r, r->ecx + 0x148))
    {
        goto at_4bd0dc;
    }
at_4bd082:
    r->eax = rd32(r, r->ecx + 0x1b4);
    wr32(r, r->eax + 0x10, 0x1);
    wr32(r, r->edi + 0x18, 0x0);
at_4bd096:
    r->eax = rd32(r, r->ebp - 0x18);
    r->edi = rd32(r, r->ebp - 0x14);
    r->esi = rd32(r, r->ebp - 0x10);
    r->edx = rd32(r, r->ebp - 0xc);
    r->ecx = rd32(r, r->ebp - 0x8);
    r->ebx = rd32(r, r->ebp - 0x4);
    return;
at_4bd0a3:
    if ((int32_t)rd32(r, r->edx + 0x1c) > (int32_t)0xffdc && !r->port->env.failed)
    {
        goto at_4bcee7;
    }
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4bceff;
at_4bd0b5:
    r->esi = rd32(r, r->ebx + 0xc);
    if ((int32_t)r->esi <= 0 && !r->port->env.failed)
    {
        goto at_4bcf7b;
    }
    if ((int32_t)r->esi > (int32_t)0x4 && !r->port->env.failed)
    {
        goto at_4bcf7b;
    }
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4bcf8a;
at_4bd0ce:
    r->eax = r->esi;
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4bcf9b;
at_4bd0d5:
    r->eax = r->esi;
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4bcfb2;
at_4bd0dc:
    r->ebx = rd32(r, r->ecx + 0xdc);
    if (r->ebx != 0 && !r->port->env.failed)
    {
        goto at_4bd082;
    }
    r->eax = rd32(r, r->ecx + 0x1b4);
    wr32(r, r->eax + 0x10, r->ebx);
    wr32(r, r->edi + 0x18, 0x0);
    r->eax = rd32(r, r->ebp - 0x18);
    r->edi = rd32(r, r->ebp - 0x14);
    r->esi = rd32(r, r->ebp - 0x10);
    r->edx = rd32(r, r->ebp - 0xc);
    r->ecx = rd32(r, r->ebp - 0x8);
    r->ebx = rd32(r, r->ebp - 0x4);
    return;
at_4bd103:
    if (rd32(r, r->edi + 0x10) != 0x0)
    {
        goto at_4bd118;
    }
    r->eax = rd32(r, r->edx);
    wr32(r, r->eax + 0x14, 0x23);
    r->ecx = rd32(r, r->edx);
    r->eax = r->edx;
    call_all(r, rd32(r, r->ecx));
at_4bd118:
    r->eax = r->edx;
    call(r, 0x4bcbc0, 0);
    r->eax = rd32(r, r->ebp - 0x18);
    r->edi = rd32(r, r->ebp - 0x14);
    r->esi = rd32(r, r->ebp - 0x10);
    r->edx = rd32(r, r->ebp - 0xc);
    r->ecx = rd32(r, r->ebp - 0x8);
    r->ebx = rd32(r, r->ebp - 0x4);
    return;
at_4bd12c:
    r->ebx = rd32(r, r->edi + 0x18);
    wr32(r, r->edi + 0x14, 0x1);
    if (r->ebx == 0)
    {
        goto at_4bd166;
    }
    r->eax = rd32(r, r->edx + 0x1b8);
    if (rd32(r, r->eax + 0x10) == 0x0 && !r->port->env.failed)
    {
        goto at_4bd096;
    }
    r->eax = rd32(r, r->edx);
    wr32(r, r->eax + 0x14, 0x3b);
    r->ecx = rd32(r, r->edx);
    r->eax = r->edx;
    call_all(r, rd32(r, r->ecx));
    r->eax = rd32(r, r->ebp - 0x18);
    r->edi = rd32(r, r->ebp - 0x14);
    r->esi = rd32(r, r->ebp - 0x10);
    r->edx = rd32(r, r->ebp - 0xc);
    r->ecx = rd32(r, r->ebp - 0x8);
    r->ebx = rd32(r, r->ebp - 0x4);
    return;
at_4bd166:
    r->eax = rd32(r, r->edx + 0x98);
    r->esi = rd32(r, r->edx + 0x90);
    if ((int32_t)r->eax <= (int32_t)r->esi && !r->port->env.failed)
    {
        goto at_4bd096;
    }
    wr32(r, r->edx + 0x98, r->esi);
    r->eax = rd32(r, r->ebp - 0x18);
    r->edi = rd32(r, r->ebp - 0x14);
    r->esi = rd32(r, r->ebp - 0x10);
    r->edx = rd32(r, r->ebp - 0xc);
    r->ecx = rd32(r, r->ebp - 0x8);
    r->ebx = rd32(r, r->ebp - 0x4);
    return;
at_4bd18d:
    r->ecx = rd32(r, r->eax + 0x1b8);
    call_all(r, rd32(r, r->ecx + 0x4));
    wr32(r, r->ebp - 0x18, r->eax);
    flags(r, F_SUB, r->eax, 0x1, 32);
    if (cond(r, CC_B) && !r->port->env.failed)
    {
        goto at_4bd096;
    }
    if (cond(r, CC_BE) && !r->port->env.failed)
    {
        goto at_4bcecc;
    }
    if (r->eax == 0x2 && !r->port->env.failed)
    {
        goto at_4bd12c;
    }
    r->eax = rd32(r, r->ebp - 0x18);
    r->edi = rd32(r, r->ebp - 0x14);
    r->esi = rd32(r, r->ebp - 0x10);
    r->edx = rd32(r, r->ebp - 0xc);
    r->ecx = rd32(r, r->ebp - 0x8);
    r->ebx = rd32(r, r->ebp - 0x4);
    return;
}

uint32_t vertrix_port_jpeg_input_consume_markers_4bcea0(PORT_SIGNATURE)
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
    port_set32(&port, r.ebp, -0xcu, entry->edx);
    port_set32(&port, r.ebp, -0x10u, entry->esi);
    port_set32(&port, r.ebp, -0x14u, entry->edi);
    run(&r);
    return port_return(&port, r.eax, r.edx);
}
