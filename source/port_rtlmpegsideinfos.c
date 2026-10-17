#include "port_rtlmpegsideinfos.h"

/* Reads MPEG-1 layer III side information: main_data_begin (9 bits), the private bits (5 for mono),
 * each channel's 4 scfsi bits, then each granule's fields; other layouts take the branch at
 * 0x4071f8. */

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

/* A call that pops nothing (cdecl, or no stack arguments): every value pushed passed and left for
 * the caller's add esp. */
static void call_keep(Regs *r, uint32_t target)
{
    call_with_stack(r, target, r->pushed, 1);
}

static uint32_t rd32(Regs *r, uint32_t address)
{
    return port_u32(r->port, address, 0);
}

static void wr32(Regs *r, uint32_t address, uint32_t value)
{
    port_set32(r->port, address, 0, value);
}

/* Original 0x407020: Reads MPEG-1 layer III side information: main_data_begin (9 bits), the private
 * bits (5 for mono), each channel's 4 scfsi bits, then each granule's fields; other layouts take
 * the branch at 0x4071f8. Evidence: calls 0x404610, 0x404680, 0x4046e0, 0x4eb4d4.
 * Register-for-register from the listing (0x407028..0x40726f); labels are the original addresses.
 */
static void run(Regs *r)
{
    r->esi = r->eax;
    wr32(r, r->ebp - 0x14, r->edx);
    wr32(r, r->ebp - 0x1c, r->ebx);
    r->ebx = r->ecx;
    if (rd32(r, r->ebp + 0x8) != 0x3)
    {
        goto at_4071f8;
    }
    r->eax = 0x4;
at_407041:
    r->edi = r->eax;
    r->eax = 0x9;
    call_keep(r, 0x404610);
    wr32(r, r->esi, r->eax);
    if (rd32(r, r->ebp - 0x14) != 0x1)
    {
        goto at_4071ff;
    }
    r->eax = 0x5;
at_40705e:
    call_keep(r, 0x404680);
    wr32(r, r->esi + 0x4, r->eax);
    r->ecx = 0;
    if ((int32_t)rd32(r, r->ebp - 0x14) <= (int32_t)0x0)
    {
        goto at_407090;
    }
    r->edx = r->esi;
at_407070:
    wr32(r, r->edx + 0x8, 0xffffffffu);
    r->eax = 0x4;
    call_keep(r, 0x404680);
    wr32(r, r->edx + 0x70, r->eax);
    r->edx = r->edx + 0xd0;
    r->ecx = r->ecx + 1;
    if ((int32_t)r->ecx < (int32_t)rd32(r, r->ebp - 0x14) && !r->port->env.failed)
    {
        goto at_407070;
    }
at_407090:
    r->edx = r->ebx;
    r->eax = r->ebx * 8;
    r->eax = r->eax + r->ebx;
    r->eax = r->eax << 0x4;
    wr32(r, r->ebp - 0x10, r->eax);
    r->edi = r->edi << 0x2;
    wr32(r, r->ebp - 0x18, r->edi);
    r->esi = r->esi + 0x8;
    wr32(r, r->ebp - 0x24, r->esi);
    r->edx = r->edx ^ r->ebx;
    wr32(r, r->ebp - 0x20, r->edx);
at_4070b2:
    r->ecx = 0;
    wr32(r, r->ebp - 0xc, r->ecx);
    if ((int32_t)rd32(r, r->ebp - 0x14) <= (int32_t)0x0)
    {
        goto at_4071da;
    }
    r->edi = rd32(r, r->ebp - 0x20);
    r->edi = r->edi + rd32(r, r->ebp - 0x24);
at_4070c7:
    r->ecx = r->edi;
    r->eax = 0xc;
    call_keep(r, 0x404610);
    wr32(r, r->edi + 0x4, r->eax);
    r->eax = 0x9;
    call_keep(r, 0x404680);
    wr32(r, r->edi + 0x8, r->eax);
    if (r->eax <= 0x120)
    {
        goto at_4070f1;
    }
    wr32(r, r->edi + 0x8, 0x120);
at_4070f1:
    r->eax = 0x8;
    call_keep(r, 0x404680);
    r->eax = r->eax << 0x2;
    r->edx = 0x523698;
    r->edx = r->edx - r->eax;
    r->eax = r->edx;
    r->edx = rd32(r, r->ebp - 0x18);
    r->edx = r->edx + r->eax;
    wr32(r, r->ecx + 0x64, r->edx);
    if (rd32(r, r->ebp - 0x1c) == 0x0)
    {
        goto at_40711b;
    }
    r->esi = r->edx + 0x8;
    wr32(r, r->ecx + 0x64, r->esi);
at_40711b:
    r->eax = 0x4;
    call_keep(r, 0x404680);
    wr32(r, r->ecx + 0xc, r->eax);
    call_keep(r, 0x4046e0);
    r->ebx = r->ecx + 0xc;
    if (r->eax == 0)
    {
        goto at_407209;
    }
    r->eax = 0x2;
    call_keep(r, 0x404680);
    wr32(r, r->ecx + 0x10, r->eax);
    call_keep(r, 0x4046e0);
    wr32(r, r->ecx + 0x14, r->eax);
    r->eax = 0x5;
    call_keep(r, 0x404680);
    wr32(r, r->ecx + 0x18, r->eax);
    r->eax = 0x5;
    call_keep(r, 0x404680);
    wr32(r, r->ecx + 0x1c, r->eax);
    wr32(r, r->ecx + 0x20, 0x0);
    r->edx = r->ecx;
    r->esi = r->ebx;
at_407172:
    r->eax = 0x3;
    call_keep(r, 0x404680);
    r->eax = r->eax << 0x5;
    r->ebx = rd32(r, r->ecx + 0x64);
    r->eax = r->eax + r->ebx;
    wr32(r, r->edx + 0x58, r->eax);
    r->edx = r->edx + 0x4;
    if (r->edx != r->esi && !r->port->env.failed)
    {
        goto at_407172;
    }
    if (rd32(r, r->ecx + 0x10) != 0x0)
    {
        goto at_40719e;
    }
    r->eax = 0x1;
    call_keep(r, 0x4eb4d4);
at_40719e:
    wr32(r, r->ecx + 0x44, 0x12);
    wr32(r, r->ecx + 0x48, 0x120);
at_4071ac:
    call_keep(r, 0x4046e0);
    wr32(r, r->ecx + 0x4c, r->eax);
    call_keep(r, 0x4046e0);
    wr32(r, r->ecx + 0x50, r->eax);
    call_keep(r, 0x4046e0);
    wr32(r, r->ecx + 0x54, r->eax);
    r->edi = r->edi + 0xd0;
    r->esi = rd32(r, r->ebp - 0xc);
    r->esi = r->esi + 1;
    wr32(r, r->ebp - 0xc, r->esi);
    if ((int32_t)r->esi < (int32_t)rd32(r, r->ebp - 0x14) && !r->port->env.failed)
    {
        goto at_4070c7;
    }
at_4071da:
    r->ecx = rd32(r, r->ebp - 0x20);
    r->ecx = r->ecx + 0x68;
    wr32(r, r->ebp - 0x20, r->ecx);
    if (r->ecx != 0xd0 && !r->port->env.failed)
    {
        goto at_4070b2;
    }
    r->edi = rd32(r, r->ebp - 0x8);
    r->esi = rd32(r, r->ebp - 0x4);
    return;
at_4071f8:
    r->eax = 0;
    if (r->port->env.failed)
    {
        return;
    }
    goto at_407041;
at_4071ff:
    r->eax = 0x3;
    if (r->port->env.failed)
    {
        return;
    }
    goto at_40705e;
at_407209:
    r->edx = r->ecx;
    r->esi = 0x5;
at_407210:
    r->eax = r->esi;
    call_keep(r, 0x404680);
    wr32(r, r->edx + 0x18, r->eax);
    r->edx = r->edx + 0x4;
    if (r->edx != r->ebx && !r->port->env.failed)
    {
        goto at_407210;
    }
    r->eax = 0x4;
    call_keep(r, 0x404680);
    r->edx = r->eax;
    r->eax = 0x3;
    call_keep(r, 0x404680);
    r->ebx = r->edx + r->edx;
    r->esi = rd32(r, r->ebp - 0x10);
    r->ebx = r->ebx + r->esi;
    r->ebx = rd32(r, r->ebx + 0x4f5918);
    r->ebx = (uint32_t)((int32_t)r->ebx >> 0x10);
    r->ebx = (uint32_t)((int32_t)r->ebx >> 0x1);
    wr32(r, r->ecx + 0x44, r->ebx);
    r->eax = r->eax + r->edx;
    r->eax = r->eax + r->eax;
    r->eax = r->eax + r->esi;
    r->eax = rd32(r, r->eax + 0x4f591a);
    r->eax = (uint32_t)((int32_t)r->eax >> 0x10);
    r->eax = (uint32_t)((int32_t)r->eax >> 0x1);
    wr32(r, r->ecx + 0x48, r->eax);
    wr32(r, r->ecx + 0x10, 0x0);
    wr32(r, r->ecx + 0x14, 0x0);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4071ac;
}

uint32_t vertrix_port_mpeg1_side_info_407020(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x28
    };
    Port port;
    uint8_t stack[BELOW + 8 + 4 * 1];
    Regs r;
    port_open_arguments(&port, stack, calls, services, globals, entry, BELOW, 1);
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
    port_set32(&port, r.ebp, -0x4u, entry->esi);
    port_set32(&port, r.ebp, -0x8u, entry->edi);
    run(&r);
    return port_return(&port, r.eax, r.edx);
}
