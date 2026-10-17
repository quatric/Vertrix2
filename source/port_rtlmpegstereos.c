#include "port_rtlmpegstereos.h"

/* Applies layer III stereo processing for a granule: intensity stereo ratios from the tables at
 * 0x522f98 and 0x523098 (picked by the mode extension), with the scale factor band table at
 * 0x4f5918. */

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

static uint32_t rd16(Regs *r, uint32_t address)
{
    return port_u16(r->port, address, 0);
}

static uint32_t rd32(Regs *r, uint32_t address)
{
    return port_u32(r->port, address, 0);
}

static void wr32(Regs *r, uint32_t address, uint32_t value)
{
    port_set32(r->port, address, 0, value);
}

/* The emulated stack of a routine without a frame pointer: pushes and pops move esp. */
static void push_mem(Regs *r, uint32_t value)
{
    r->esp -= 4;
    wr32(r, r->esp, value);
}

static uint32_t pop_mem(Regs *r)
{
    uint32_t value = rd32(r, r->esp);
    r->esp += 4;
    return value;
}

/* A call taking count stack arguments from esp up; the callee pops them unless kept (cdecl). */
static void call_mem_with(Regs *r, uint32_t target, unsigned count, int keep)
{
    uint32_t args[32] = {0};
    unsigned i;
    for (i = 0; i < count && i < 32; i++)
    {
        args[i] = rd32(r, r->esp + 4 * i);
    }
    vertrix_lift_in_esi = r->esi;
    vertrix_lift_in_edi = r->edi;
    vertrix_lift_in_ebp = r->ebp;
    r->eax =
        lift_call_arguments(&r->port->env, target, r->eax, r->edx, r->ebx, r->ecx, args, count);
    vertrix_lift_in_esi = vertrix_lift_in_edi = vertrix_lift_in_ebp = 0;
    r->edx = vertrix_lift_edx;
    if (!keep)
    {
        r->esp += 4 * count;
    }
}

static void call_mem_keep(Regs *r, uint32_t target, unsigned count)
{
    call_mem_with(r, target, count, 1);
}

/* Original 0x4083a0: Applies layer III stereo processing for a granule: intensity stereo ratios
 * from the tables at 0x522f98 and 0x523098 (picked by the mode extension), with the scale factor
 * band table at 0x4f5918. Evidence: calls 0x4d8177. Register-for-register from the listing
 * (0x4083a0..0x4087f4); labels are the original addresses. */
static void run(Regs *r)
{
    push_mem(r, r->esi);
    push_mem(r, r->edi);
    push_mem(r, r->ebp);
    r->esp = r->esp - 0x60;
    wr32(r, r->esp + 0x38, r->edx);
    wr32(r, r->esp + 0x3c, r->ebx);
    r->ebx = rd32(r, r->esp + 0x70);
    wr32(r, r->esp + 0x40, r->eax);
    r->eax = r->ecx * 8;
    r->eax = r->eax + r->ecx;
    r->eax = r->eax << 0x4;
    r->ecx = 0x4f5918;
    r->ecx = r->ecx + r->eax;
    wr32(r, r->esp + 0x24, r->ecx);
    if (rd32(r, r->esp + 0x74) == 0x0)
    {
        goto at_4084b9;
    }
    r->eax = rd32(r, r->esp + 0x3c);
    r->eax = rd32(r, r->eax + 0xc);
    r->eax = r->eax & 0x1;
    r->eax = r->eax << 0x6;
    if (r->ebx == 0)
    {
        goto at_4084a4;
    }
    r->ecx = 0x523098;
    r->ecx = r->ecx + r->eax;
    wr32(r, r->esp + 0x44, r->ecx);
    r->ecx = 0x522f98;
at_4083fd:
    r->ecx = r->ecx + r->eax;
    wr32(r, r->esp + 0x48, r->ecx);
at_408403:
    r->eax = rd32(r, r->esp + 0x3c);
    if (rd32(r, r->eax + 0x10) != 0x2)
    {
        goto at_4086d8;
    }
    r->ecx = 0;
    wr32(r, r->esp + 0x4, r->ecx);
    if (rd32(r, r->eax + 0x14) != 0x0)
    {
        goto at_4084e7;
    }
at_408421:
    r->edi = 0;
    wr32(r, r->esp + 0x4c, r->edi);
    r->eax = rd32(r, r->esp + 0x3c);
    wr32(r, r->esp + 0x8, r->eax);
    wr32(r, r->esp + 0xc, 0x21);
at_408437:
    r->eax = rd32(r, r->esp + 0x8);
    r->eax = rd32(r, r->eax + 0x30);
    wr32(r, r->esp + 0x54, r->eax);
    if ((int32_t)r->eax > (int32_t)0x3)
    {
        goto at_40857d;
    }
at_40844b:
    r->eax = rd32(r, r->esp + 0x54);
    r->eax = r->eax + r->eax * 2;
    r->ebx = rd32(r, r->esp + 0x4c);
    r->eax = r->eax + r->ebx;
    wr32(r, r->esp + 0x50, r->eax);
    r->eax = rd32(r, r->esp + 0x54);
    r->eax = r->eax + r->eax;
    r->esi = rd32(r, r->esp + 0x24);
    r->eax = r->eax + r->esi;
    wr32(r, r->esp + 0x58, r->eax);
at_40846c:
    if ((int32_t)rd32(r, r->esp + 0x54) >= (int32_t)0xc)
    {
        goto at_4085f6;
    }
    r->eax = rd32(r, r->esp + 0x50);
    r->ecx = rd32(r, r->esp + 0x3c);
    r->eax = r->eax - rd32(r, r->ecx + 0x14);
    r->eax = r->eax << 0x2;
    r->eax = r->eax + rd32(r, r->esp + 0x38);
    r->eax = rd32(r, r->eax);
    if (r->eax != 0x7)
    {
        goto at_408588;
    }
at_408494:
    wr32(r, r->esp + 0x50, rd32(r, r->esp + 0x50) + 0x3);
    wr32(r, r->esp + 0x58, rd32(r, r->esp + 0x58) + 0x2);
    wr32(r, r->esp + 0x54, rd32(r, r->esp + 0x54) + 1);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_40846c;
at_4084a4:
    r->ecx = 0x523118;
    r->ecx = r->ecx + r->eax;
    wr32(r, r->esp + 0x44, r->ecx);
    r->ecx = 0x523018;
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4083fd;
at_4084b9:
    if (r->ebx == 0)
    {
        goto at_4084d2;
    }
    wr32(r, r->esp + 0x44, 0x523258);
    wr32(r, r->esp + 0x48, 0x5231d8);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_408403;
at_4084d2:
    wr32(r, r->esp + 0x44, 0x523218);
    wr32(r, r->esp + 0x48, 0x523198);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_408403;
at_4084e7:
    wr32(r, r->esp + 0x4, 0x1);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_408421;
at_4084f4:
    wr32(r, r->esp + 0x8, rd32(r, r->esp + 0x8) + 0x4);
    wr32(r, r->esp + 0xc, rd32(r, r->esp + 0xc) + 1);
    r->ebp = rd32(r, r->esp + 0x4c);
    r->ebp = r->ebp + 1;
    wr32(r, r->esp + 0x4c, r->ebp);
    if ((int32_t)r->ebp < (int32_t)0x3 && !r->port->env.failed)
    {
        goto at_408437;
    }
    if (rd32(r, r->esp + 0x4) == 0x0)
    {
        goto at_408574;
    }
    r->eax = rd32(r, r->esp + 0x3c);
    r->eax = rd32(r, r->eax + 0x3c);
    wr32(r, r->esp + 0x28, r->eax);
    r->ecx = r->eax + r->eax;
    r->ecx = r->ecx + rd32(r, r->esp + 0x24);
    r->edi = (uint32_t)(int32_t)(int16_t)rd16(r, r->ecx);
    if ((int32_t)r->eax >= (int32_t)0x8)
    {
        goto at_408574;
    }
    r->eax = r->eax << 0x2;
    r->ebx = rd32(r, r->esp + 0x38);
    r->eax = r->eax + r->ebx;
    wr32(r, r->esp + 0x10, r->eax);
    wr32(r, r->esp + 0x18, r->ecx);
at_408541:
    r->esi = rd32(r, r->esp + 0x18);
    r->esi = rd32(r, r->esi + 0x2c);
    r->esi = (uint32_t)((int32_t)r->esi >> 0x10);
    r->eax = rd32(r, r->esp + 0x10);
    r->eax = rd32(r, r->eax);
    if (r->eax != 0x7)
    {
        goto at_408684;
    }
    r->edi = r->edi + r->esi;
at_40855c:
    wr32(r, r->esp + 0x10, rd32(r, r->esp + 0x10) + 0x4);
    wr32(r, r->esp + 0x18, rd32(r, r->esp + 0x18) + 0x2);
    r->eax = rd32(r, r->esp + 0x28);
    r->eax = r->eax + 1;
    wr32(r, r->esp + 0x28, r->eax);
    if ((int32_t)r->eax < (int32_t)0x8 && !r->port->env.failed)
    {
        goto at_408541;
    }
at_408574:
    r->esp = r->esp + 0x60;
    r->ebp = pop_mem(r);
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    return;
at_40857d:
    r->ecx = 0;
    wr32(r, r->esp + 0x4, r->ecx);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_40844b;
at_408588:
    r->esi = rd32(r, r->esp + 0x58);
    r->esi = rd32(r, r->esi + 0x74);
    r->esi = (uint32_t)((int32_t)r->esi >> 0x10);
    r->edi = rd32(r, r->esp + 0x58);
    r->edi = rd32(r, r->edi + 0x58);
    r->edi = (uint32_t)((int32_t)r->edi >> 0x10);
    r->edi = r->edi + rd32(r, r->esp + 0x4c);
    r->eax = r->eax << 0x2;
    r->ebp = rd32(r, r->esp + 0x44);
    r->ebp = rd32(r, r->eax + r->ebp);
    r->eax = r->eax + rd32(r, r->esp + 0x48);
    r->eax = rd32(r, r->eax);
    wr32(r, r->esp + 0x5c, r->eax);
    if ((int32_t)r->esi <= 0 && !r->port->env.failed)
    {
        goto at_408494;
    }
    r->ecx = r->edi * 4;
    r->ecx = r->ecx + rd32(r, r->esp + 0x40);
at_4085c7:
    r->ebx = rd32(r, r->ecx);
    r->eax = r->ebx;
    r->edx = r->ebp;
    call_mem_keep(r, 0x4d8177, 8);
    wr32(r, r->ecx, r->eax);
    r->eax = r->ebx;
    r->edx = rd32(r, r->esp + 0x5c);
    call_mem_keep(r, 0x4d8177, 8);
    wr32(r, r->ecx + 0x900, r->eax);
    r->esi = r->esi - 1;
    r->ecx = r->ecx + 0xc;
    r->edi = r->edi + 0x3;
    if ((int32_t)r->esi <= 0 && !r->port->env.failed)
    {
        goto at_408494;
    }
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4085c7;
at_4085f6:
    r->eax = rd32(r, r->esp + 0xc);
    r->ecx = rd32(r, r->esp + 0x3c);
    r->eax = r->eax - rd32(r, r->ecx + 0x14);
    r->eax = r->eax << 0x2;
    r->eax = r->eax + rd32(r, r->esp + 0x38);
    r->eax = rd32(r, r->eax);
    r->esi = rd32(r, r->esp + 0x24);
    r->esi = rd32(r, r->esi + 0x8c);
    r->esi = (uint32_t)((int32_t)r->esi >> 0x10);
    r->ebp = rd32(r, r->esp + 0x24);
    r->ebp = rd32(r, r->ebp + 0x70);
    r->ebp = (uint32_t)((int32_t)r->ebp >> 0x10);
    r->ebp = r->ebp + rd32(r, r->esp + 0x4c);
    if (r->eax == 0x7 && !r->port->env.failed)
    {
        goto at_4084f4;
    }
    r->eax = r->eax << 0x2;
    r->edi = rd32(r, r->esp + 0x44);
    r->edi = rd32(r, r->edi + r->eax);
    r->eax = r->eax + rd32(r, r->esp + 0x48);
    r->eax = rd32(r, r->eax);
    wr32(r, r->esp + 0x30, r->eax);
    if ((int32_t)r->esi <= 0 && !r->port->env.failed)
    {
        goto at_4084f4;
    }
    r->ecx = r->ebp * 4;
    r->ecx = r->ecx + rd32(r, r->esp + 0x40);
at_408655:
    r->ebx = rd32(r, r->ecx);
    r->eax = r->ebx;
    r->edx = r->edi;
    call_mem_keep(r, 0x4d8177, 8);
    wr32(r, r->ecx, r->eax);
    r->eax = r->ebx;
    r->edx = rd32(r, r->esp + 0x30);
    call_mem_keep(r, 0x4d8177, 8);
    wr32(r, r->ecx + 0x900, r->eax);
    r->esi = r->esi - 1;
    r->ecx = r->ecx + 0xc;
    r->ebp = r->ebp + 0x3;
    if ((int32_t)r->esi <= 0 && !r->port->env.failed)
    {
        goto at_4084f4;
    }
    if (r->port->env.failed)
    {
        return;
    }
    goto at_408655;
at_408684:
    r->eax = r->eax << 0x2;
    r->ebp = rd32(r, r->esp + 0x44);
    r->ebp = rd32(r, r->eax + r->ebp);
    r->eax = r->eax + rd32(r, r->esp + 0x48);
    r->eax = rd32(r, r->eax);
    wr32(r, r->esp + 0x2c, r->eax);
    if ((int32_t)r->esi <= 0 && !r->port->env.failed)
    {
        goto at_40855c;
    }
    r->ecx = r->edi * 4;
    r->ecx = r->ecx + rd32(r, r->esp + 0x40);
at_4086ab:
    r->ebx = rd32(r, r->ecx);
    r->eax = r->ebx;
    r->edx = r->ebp;
    call_mem_keep(r, 0x4d8177, 8);
    wr32(r, r->ecx, r->eax);
    r->eax = r->ebx;
    r->edx = rd32(r, r->esp + 0x2c);
    call_mem_keep(r, 0x4d8177, 8);
    wr32(r, r->ecx + 0x900, r->eax);
    r->esi = r->esi - 1;
    r->ecx = r->ecx + 0x4;
    r->edi = r->edi + 1;
    if ((int32_t)r->esi <= 0 && !r->port->env.failed)
    {
        goto at_40855c;
    }
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4086ab;
at_4086d8:
    r->eax = rd32(r, r->eax + 0x3c);
    wr32(r, r->esp + 0x20, r->eax);
    r->esi = r->eax + r->eax;
    r->esi = r->esi + rd32(r, r->esp + 0x24);
    r->edi = (uint32_t)(int32_t)(int16_t)rd16(r, r->esi);
    r->edx = rd32(r, r->esp + 0x20);
    if ((int32_t)r->edx >= (int32_t)0x15)
    {
        goto at_408786;
    }
    r->eax = r->edx * 4;
    r->ebp = rd32(r, r->esp + 0x38);
    r->eax = r->eax + r->ebp;
    wr32(r, r->esp + 0x14, r->eax);
    wr32(r, r->esp + 0x1c, r->esi);
at_40870b:
    r->esi = rd32(r, r->esp + 0x1c);
    r->esi = rd32(r, r->esi + 0x2c);
    r->esi = (uint32_t)((int32_t)r->esi >> 0x10);
    r->eax = rd32(r, r->esp + 0x14);
    r->eax = rd32(r, r->eax);
    if (r->eax == 0x7)
    {
        goto at_4087f2;
    }
    r->eax = r->eax << 0x2;
    r->ebp = rd32(r, r->esp + 0x44);
    r->ebp = rd32(r, r->eax + r->ebp);
    r->eax = r->eax + rd32(r, r->esp + 0x48);
    r->eax = rd32(r, r->eax);
    wr32(r, r->esp + 0x34, r->eax);
    if ((int32_t)r->esi <= 0)
    {
        goto at_40876e;
    }
    r->ecx = r->edi * 4;
    r->ecx = r->ecx + rd32(r, r->esp + 0x40);
at_408747:
    r->ebx = rd32(r, r->ecx);
    r->eax = r->ebx;
    r->edx = r->ebp;
    call_mem_keep(r, 0x4d8177, 8);
    wr32(r, r->ecx, r->eax);
    r->eax = r->ebx;
    r->edx = rd32(r, r->esp + 0x34);
    call_mem_keep(r, 0x4d8177, 8);
    wr32(r, r->ecx + 0x900, r->eax);
    r->esi = r->esi - 1;
    r->ecx = r->ecx + 0x4;
    r->edi = r->edi + 1;
    if ((int32_t)r->esi > 0 && !r->port->env.failed)
    {
        goto at_408747;
    }
at_40876e:
    wr32(r, r->esp + 0x14, rd32(r, r->esp + 0x14) + 0x4);
    wr32(r, r->esp + 0x1c, rd32(r, r->esp + 0x1c) + 0x2);
    r->ecx = rd32(r, r->esp + 0x20);
    r->ecx = r->ecx + 1;
    wr32(r, r->esp + 0x20, r->ecx);
    if ((int32_t)r->ecx < (int32_t)0x15 && !r->port->env.failed)
    {
        goto at_40870b;
    }
at_408786:
    r->eax = rd32(r, r->esp + 0x38);
    r->eax = rd32(r, r->eax + 0x50);
    if (r->eax == 0x7 && !r->port->env.failed)
    {
        goto at_408574;
    }
    r->eax = r->eax << 0x2;
    r->ebp = rd32(r, r->esp + 0x44);
    r->ebp = rd32(r, r->eax + r->ebp);
    r->eax = r->eax + rd32(r, r->esp + 0x48);
    r->eax = rd32(r, r->eax);
    wr32(r, r->esp, r->eax);
    r->esi = rd32(r, r->esp + 0x24);
    r->esi = rd32(r, r->esi + 0x56);
    r->esi = (uint32_t)((int32_t)r->esi >> 0x10);
    if ((int32_t)r->esi <= 0 && !r->port->env.failed)
    {
        goto at_408574;
    }
    r->ecx = r->edi * 4;
    r->ecx = r->ecx + rd32(r, r->esp + 0x40);
at_4087c6:
    r->ebx = rd32(r, r->ecx);
    r->eax = r->ebx;
    r->edx = r->ebp;
    call_mem_keep(r, 0x4d8177, 8);
    wr32(r, r->ecx, r->eax);
    r->eax = r->ebx;
    r->edx = rd32(r, r->esp);
    call_mem_keep(r, 0x4d8177, 8);
    wr32(r, r->ecx + 0x900, r->eax);
    r->esi = r->esi - 1;
    r->ecx = r->ecx + 0x4;
    r->edi = r->edi + 1;
    if ((int32_t)r->esi <= 0 && !r->port->env.failed)
    {
        goto at_408574;
    }
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4087c6;
at_4087f2:
    r->edi = r->edi + r->esi;
    if (r->port->env.failed)
    {
        return;
    }
    goto at_40876e;
}

uint32_t vertrix_port_mpeg_intensity_stereo_4083a0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x80
    };
    Port port;
    uint8_t stack[BELOW + 8 + 4 * 27];
    Regs r;
    port_open_arguments(&port, stack, calls, services, globals, entry, BELOW, 27);
    memset(&r, 0, sizeof r);
    r.port = &port;
    r.eax = entry->eax;
    r.edx = entry->edx;
    r.ebx = entry->ebx;
    r.ecx = entry->ecx;
    r.esi = entry->esi;
    r.edi = entry->edi;
    r.ebp = entry->ebp;
    r.esp = entry->esp;
    run(&r);
    return port_return(&port, r.eax, r.edx);
}
