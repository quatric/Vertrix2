#include "port_rtljpegidct8s.h"

/* libjpeg 8x8 inverse DCT with dequantisation, a shortcut for columns whose AC terms are zero, and
 * range limiting. */

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

static uint32_t rd8(Regs *r, uint32_t address)
{
    return port_u8(r->port, address, 0);
}

static uint32_t rd16(Regs *r, uint32_t address)
{
    return port_u16(r->port, address, 0);
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

static void set_low8(uint32_t *reg, uint32_t value)
{
    *reg = (*reg & 0xffffff00u) | (value & 0xff);
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

/* Original 0x4c4000: libjpeg 8x8 inverse DCT with dequantisation, a shortcut for columns whose AC
 * terms are zero, and range limiting. Evidence: no calls. Register-for-register from the listing
 * (0x4c4000..0x4c4729); labels are the original addresses. */
static void run(Regs *r)
{
    push_mem(r, r->esi);
    push_mem(r, r->edi);
    push_mem(r, r->ebp);
    r->esp = r->esp - 0x14c;
    wr32(r, r->esp + 0x120, r->ecx);
    r->eax = rd32(r, r->eax + 0x144);
    r->ecx = 0x8;
    r->eax = r->eax + 0x80;
    wr32(r, r->esp + 0x100, r->ecx);
    wr32(r, r->esp + 0x13c, r->eax);
    r->eax = r->ebx;
    r->ebx = rd32(r, r->edx + 0x50);
    r->edx = r->esp;
at_4c4035:
    if ((uint16_t)rd16(r, r->eax + 0x10) != (uint16_t)0x0)
    {
        goto at_4c419e;
    }
    if ((uint16_t)rd16(r, r->eax + 0x20) != (uint16_t)0x0)
    {
        goto at_4c419e;
    }
    if ((uint16_t)rd16(r, r->eax + 0x30) != (uint16_t)0x0)
    {
        goto at_4c419e;
    }
    if ((uint16_t)rd16(r, r->eax + 0x40) != (uint16_t)0x0)
    {
        goto at_4c419e;
    }
    if ((uint16_t)rd16(r, r->eax + 0x50) != (uint16_t)0x0)
    {
        goto at_4c419e;
    }
    if ((uint16_t)rd16(r, r->eax + 0x60) != (uint16_t)0x0)
    {
        goto at_4c419e;
    }
    if ((uint16_t)rd16(r, r->eax + 0x70) != (uint16_t)0x0)
    {
        goto at_4c419e;
    }
    r->ecx = (uint32_t)(int32_t)(int16_t)rd16(r, r->eax);
    r->ecx = r->ecx * rd32(r, r->ebx);
    r->edx = r->edx + 0x4;
    r->ecx = r->ecx << 0x2;
    wr32(r, r->edx - 0x4, r->ecx);
    wr32(r, r->edx + 0x1c, r->ecx);
    wr32(r, r->edx + 0x3c, r->ecx);
    wr32(r, r->edx + 0x5c, r->ecx);
    wr32(r, r->edx + 0x7c, r->ecx);
    wr32(r, r->edx + 0x9c, r->ecx);
    r->eax = r->eax + 0x2;
    wr32(r, r->edx + 0xbc, r->ecx);
    r->ebx = r->ebx + 0x4;
    wr32(r, r->edx + 0xdc, r->ecx);
at_4c40b5:
    r->ebp = rd32(r, r->esp + 0x100);
    r->ebp = r->ebp - 1;
    wr32(r, r->esp + 0x100, r->ebp);
    if ((int32_t)r->ebp > 0 && !r->port->env.failed)
    {
        goto at_4c4035;
    }
    r->edx = rd32(r, r->esp + 0x120);
    wr32(r, r->esp + 0x138, r->edx);
    r->edx = r->edx + 0x20;
    r->eax = r->esp;
    wr32(r, r->esp + 0x124, r->edx);
at_4c40e6:
    r->edx = rd32(r, r->esp + 0x138);
    r->ebx = rd32(r, r->esp + 0x15c);
    r->edx = rd32(r, r->edx);
    r->esi = rd32(r, r->eax + 0x4);
    r->edx = r->edx + r->ebx;
    if (r->esi != 0)
    {
        goto at_4c448c;
    }
    if (rd32(r, r->eax + 0x8) != 0x0)
    {
        goto at_4c448c;
    }
    if (rd32(r, r->eax + 0xc) != 0x0)
    {
        goto at_4c448c;
    }
    if (rd32(r, r->eax + 0x10) != 0x0)
    {
        goto at_4c448c;
    }
    if (rd32(r, r->eax + 0x14) != 0x0)
    {
        goto at_4c448c;
    }
    if (rd32(r, r->eax + 0x18) != 0x0)
    {
        goto at_4c448c;
    }
    if (rd32(r, r->eax + 0x1c) != 0x0)
    {
        goto at_4c448c;
    }
    r->ecx = rd32(r, r->eax);
    r->ecx = r->ecx + 0x10;
    r->ecx = (uint32_t)((int32_t)r->ecx >> 0x5);
    r->ebx = rd32(r, r->esp + 0x13c);
    r->ecx = r->ecx & 0x3ff;
    r->ecx = r->ecx + r->ebx;
    set_low8(&r->ebx, rd8(r, r->ecx));
    wr8(r, r->edx, (r->ebx & 0xff));
    wr8(r, r->edx + 0x1, (r->ebx & 0xff));
    wr8(r, r->edx + 0x2, (r->ebx & 0xff));
    wr8(r, r->edx + 0x3, (r->ebx & 0xff));
    wr8(r, r->edx + 0x4, (r->ebx & 0xff));
    wr8(r, r->edx + 0x5, (r->ebx & 0xff));
    wr8(r, r->edx + 0x6, (r->ebx & 0xff));
    r->eax = r->eax + 0x20;
    wr8(r, r->edx + 0x7, (r->ebx & 0xff));
at_4c4172:
    r->esi = rd32(r, r->esp + 0x138);
    r->esi = r->esi + 0x4;
    r->edi = rd32(r, r->esp + 0x124);
    wr32(r, r->esp + 0x138, r->esi);
    if (r->esi != r->edi && !r->port->env.failed)
    {
        goto at_4c40e6;
    }
    r->esp = r->esp + 0x14c;
    r->ebp = pop_mem(r);
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    return;
at_4c419e:
    r->ecx = rd32(r, r->eax + 0x1e);
    r->esi = rd32(r, r->ebx + 0x40);
    r->ecx = (uint32_t)((int32_t)r->ecx >> 0x10);
    r->esi = r->esi * r->ecx;
    r->ecx = rd32(r, r->eax + 0x5e);
    wr32(r, r->esp + 0x110, r->esi);
    r->ecx = (uint32_t)((int32_t)r->ecx >> 0x10);
    r->ecx = r->ecx * rd32(r, r->ebx + 0xc0);
    r->esi = rd32(r, r->esp + 0x110);
    r->esi = r->esi + r->ecx;
    r->esi = r->esi * 0x1151;
    r->ecx = r->ecx * 0xffffc4dfu;
    r->ebp = rd32(r, r->esp + 0x110);
    wr32(r, r->esp + 0x10c, r->esi);
    r->edi = r->esi + r->ecx;
    r->esi = r->ebp * 0x187e;
    r->ecx = rd32(r, r->esp + 0x10c);
    r->ebp = rd32(r, r->ebx);
    r->esi = r->esi + r->ecx;
    r->ecx = (uint32_t)(int32_t)(int16_t)rd16(r, r->eax);
    r->ebp = r->ebp * r->ecx;
    r->ecx = rd32(r, r->eax + 0x3e);
    wr32(r, r->esp + 0x110, r->ebp);
    r->ecx = (uint32_t)((int32_t)r->ecx >> 0x10);
    r->ecx = r->ecx * rd32(r, r->ebx + 0x80);
    r->ebp = rd32(r, r->esp + 0x110);
    r->ebp = r->ebp + r->ecx;
    r->ebp = r->ebp << 0xd;
    wr32(r, r->esp + 0x148, r->ebp);
    r->ebp = rd32(r, r->esp + 0x110);
    r->ebp = r->ebp - r->ecx;
    r->ecx = r->ebp;
    r->ecx = r->ecx << 0xd;
    wr32(r, r->esp + 0x140, r->ecx);
    r->ecx = rd32(r, r->esp + 0x148);
    r->ecx = r->ecx + r->esi;
    wr32(r, r->esp + 0x104, r->ecx);
    r->ecx = rd32(r, r->esp + 0x148);
    r->ecx = r->ecx - r->esi;
    wr32(r, r->esp + 0x130, r->ecx);
    r->ecx = rd32(r, r->esp + 0x140);
    r->ecx = r->ecx + r->edi;
    wr32(r, r->esp + 0x108, r->ecx);
    r->ecx = rd32(r, r->esp + 0x140);
    r->ecx = r->ecx - r->edi;
    wr32(r, r->esp + 0x128, r->ecx);
    r->ecx = rd32(r, r->eax + 0x6e);
    r->esi = rd32(r, r->ebx + 0xe0);
    r->ecx = (uint32_t)((int32_t)r->ecx >> 0x10);
    r->esi = r->esi * r->ecx;
    r->ecx = rd32(r, r->eax + 0x4e);
    wr32(r, r->esp + 0x148, r->esi);
    r->ecx = (uint32_t)((int32_t)r->ecx >> 0x10);
    r->esi = rd32(r, r->ebx + 0xa0);
    r->esi = r->esi * r->ecx;
    r->edi = rd32(r, r->eax + 0x2e);
    r->edi = (uint32_t)((int32_t)r->edi >> 0x10);
    r->edi = r->edi * rd32(r, r->ebx + 0x60);
    wr32(r, r->esp + 0x140, r->esi);
    r->esi = rd32(r, r->eax + 0xe);
    r->ebp = rd32(r, r->ebx + 0x20);
    r->esi = (uint32_t)((int32_t)r->esi >> 0x10);
    r->esi = r->esi * r->ebp;
    r->ecx = rd32(r, r->esp + 0x148);
    r->ebp = rd32(r, r->esp + 0x140);
    r->ecx = r->ecx + r->esi;
    r->ebp = r->ebp + r->esi;
    r->esi = r->esi * 0x300b;
    wr32(r, r->esp + 0x10c, r->ecx);
    r->ecx = rd32(r, r->esp + 0x140);
    r->ecx = r->ecx + r->edi;
    wr32(r, r->esp + 0x110, r->ecx);
    r->ecx = rd32(r, r->esp + 0x148);
    r->ecx = r->ecx + r->edi;
    r->edi = r->edi * 0x6254;
    wr32(r, r->esp + 0x118, r->ebp);
    r->ebp = r->ebp + r->ecx;
    r->ecx = r->ecx * 0xffffc13bu;
    r->ebp = r->ebp * 0x25a1;
    wr32(r, r->esp + 0x11c, r->ebp);
    r->ebp = rd32(r, r->esp + 0x148) * 0x98e;
    wr32(r, r->esp + 0x148, r->ebp);
    r->ebp = rd32(r, r->esp + 0x140) * 0x41b3;
    wr32(r, r->esp + 0x140, r->ebp);
    r->ebp = rd32(r, r->esp + 0x10c) * 0xffffe333u;
    wr32(r, r->esp + 0x10c, r->ebp);
    r->ebp = rd32(r, r->esp + 0x110) * 0xffffadfdu;
    wr32(r, r->esp + 0x110, r->ebp);
    r->ebp = rd32(r, r->esp + 0x118) * 0xfffff384u;
    wr32(r, r->esp + 0x118, r->ebp);
    r->ebp = rd32(r, r->esp + 0x11c);
    wr32(r, r->esp + 0x118, rd32(r, r->esp + 0x118) + r->ebp);
    r->ecx = r->ecx + r->ebp;
    r->ebp = rd32(r, r->esp + 0x10c);
    r->ebp = r->ebp + r->ecx;
    wr32(r, r->esp + 0x148, rd32(r, r->esp + 0x148) + r->ebp);
    r->ebp = rd32(r, r->esp + 0x110);
    r->ebp = r->ebp + rd32(r, r->esp + 0x118);
    wr32(r, r->esp + 0x140, rd32(r, r->esp + 0x140) + r->ebp);
    r->ecx = r->ecx + rd32(r, r->esp + 0x110);
    r->ebp = rd32(r, r->esp + 0x118);
    r->edi = r->edi + r->ecx;
    r->ecx = rd32(r, r->esp + 0x10c);
    r->ecx = r->ecx + r->ebp;
    r->esi = r->esi + r->ecx;
    r->ecx = rd32(r, r->esp + 0x104);
    r->ecx = r->ecx + r->esi;
    r->ecx = r->ecx + 0x400;
    r->ecx = (uint32_t)((int32_t)r->ecx >> 0xb);
    wr32(r, r->edx, r->ecx);
    r->ecx = rd32(r, r->esp + 0x104);
    r->ecx = r->ecx - r->esi;
    r->ecx = r->ecx + 0x400;
    r->ecx = (uint32_t)((int32_t)r->ecx >> 0xb);
    wr32(r, r->edx + 0xe0, r->ecx);
    r->ecx = rd32(r, r->esp + 0x108);
    r->ecx = r->ecx + r->edi;
    r->ecx = r->ecx + 0x400;
    r->ecx = (uint32_t)((int32_t)r->ecx >> 0xb);
    wr32(r, r->edx + 0x20, r->ecx);
    r->ecx = rd32(r, r->esp + 0x108);
    r->ecx = r->ecx - r->edi;
    r->ecx = r->ecx + 0x400;
    r->ecx = (uint32_t)((int32_t)r->ecx >> 0xb);
    r->esi = rd32(r, r->esp + 0x140);
    wr32(r, r->edx + 0xc0, r->ecx);
    r->ecx = rd32(r, r->esp + 0x128);
    r->ecx = r->ecx + r->esi;
    r->ecx = r->ecx + 0x400;
    r->ecx = (uint32_t)((int32_t)r->ecx >> 0xb);
    wr32(r, r->edx + 0x40, r->ecx);
    r->ecx = rd32(r, r->esp + 0x128);
    r->ecx = r->ecx - r->esi;
    r->ecx = r->ecx + 0x400;
    r->ecx = (uint32_t)((int32_t)r->ecx >> 0xb);
    r->ebp = rd32(r, r->esp + 0x148);
    wr32(r, r->edx + 0xa0, r->ecx);
    r->ecx = rd32(r, r->esp + 0x130);
    r->ecx = r->ecx + r->ebp;
    r->ecx = r->ecx + 0x400;
    r->ecx = (uint32_t)((int32_t)r->ecx >> 0xb);
    wr32(r, r->edx + 0x60, r->ecx);
    r->ecx = rd32(r, r->esp + 0x130);
    r->ecx = r->ecx - r->ebp;
    r->ecx = r->ecx + 0x400;
    r->ecx = (uint32_t)((int32_t)r->ecx >> 0xb);
    wr32(r, r->edx + 0x80, r->ecx);
    r->eax = r->eax + 0x2;
    r->ebx = r->ebx + 0x4;
    r->edx = r->edx + 0x4;
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4c40b5;
at_4c448c:
    r->ecx = rd32(r, r->eax + 0x8);
    wr32(r, r->esp + 0x110, r->ecx);
    r->edi = rd32(r, r->esp + 0x110) * 0x187e;
    r->ebx = rd32(r, r->esp + 0x110);
    r->ecx = rd32(r, r->eax + 0x18);
    r->ebx = r->ebx + r->ecx;
    r->ebx = r->ebx * 0x1151;
    wr32(r, r->esp + 0x114, r->ecx);
    r->ecx = r->ecx * 0xffffc4dfu;
    r->esi = rd32(r, r->eax + 0x10);
    r->ecx = r->ecx + r->ebx;
    r->edi = r->edi + r->ebx;
    r->ebx = rd32(r, r->eax);
    r->ebx = r->ebx + r->esi;
    r->ebx = r->ebx << 0xd;
    r->ebp = rd32(r, r->eax + 0x10);
    wr32(r, r->esp + 0x144, r->ebx);
    r->ebx = r->ebx + r->edi;
    r->esi = rd32(r, r->eax);
    wr32(r, r->esp + 0x104, r->ebx);
    r->ebx = rd32(r, r->esp + 0x144);
    r->esi = r->esi - r->ebp;
    r->ebx = r->ebx - r->edi;
    r->esi = r->esi << 0xd;
    wr32(r, r->esp + 0x12c, r->ebx);
    r->ebx = r->esi + r->ecx;
    r->esi = r->esi - r->ecx;
    r->ecx = rd32(r, r->eax + 0x1c);
    r->edi = rd32(r, r->eax + 0x4);
    wr32(r, r->esp + 0x144, r->ecx);
    wr32(r, r->esp + 0x108, r->ebx);
    r->ebx = rd32(r, r->esp + 0x144);
    r->ebx = r->ebx + r->edi;
    r->ebx = r->ebx * 0xffffe333u;
    wr32(r, r->esp + 0x134, r->esi);
    r->esi = rd32(r, r->eax + 0x14);
    r->ecx = rd32(r, r->eax + 0xc);
    r->ebp = r->esi + r->ecx;
    wr32(r, r->esp + 0x110, r->ebp);
    r->ebp = rd32(r, r->esp + 0x144);
    r->ebp = r->ebp + r->ecx;
    r->ecx = r->ecx * 0x6254;
    wr32(r, r->esp + 0x114, r->ebp);
    r->ebp = r->esi + r->edi;
    r->esi = r->esi * 0x41b3;
    r->edi = r->edi * 0x300b;
    wr32(r, r->esp + 0x118, r->ebp);
    r->ebp = rd32(r, r->esp + 0x114);
    r->ebp = r->ebp + rd32(r, r->esp + 0x118);
    r->ebp = r->ebp * 0x25a1;
    wr32(r, r->esp + 0x11c, r->ebp);
    r->ebp = rd32(r, r->esp + 0x144) * 0x98e;
    wr32(r, r->esp + 0x144, r->ebp);
    r->ebp = rd32(r, r->esp + 0x110) * 0xffffadfdu;
    wr32(r, r->esp + 0x110, r->ebp);
    r->ebp = rd32(r, r->esp + 0x114) * 0xffffc13bu;
    wr32(r, r->esp + 0x114, r->ebp);
    r->ebp = rd32(r, r->esp + 0x118) * 0xfffff384u;
    wr32(r, r->esp + 0x118, r->ebp);
    r->ebp = rd32(r, r->esp + 0x11c);
    wr32(r, r->esp + 0x114, rd32(r, r->esp + 0x114) + r->ebp);
    wr32(r, r->esp + 0x118, rd32(r, r->esp + 0x118) + r->ebp);
    r->ebp = rd32(r, r->esp + 0x114);
    r->ebp = r->ebp + r->ebx;
    wr32(r, r->esp + 0x144, rd32(r, r->esp + 0x144) + r->ebp);
    r->ebp = rd32(r, r->esp + 0x110);
    r->ebp = r->ebp + rd32(r, r->esp + 0x118);
    r->esi = r->esi + r->ebp;
    r->ebp = rd32(r, r->esp + 0x110);
    r->ebp = r->ebp + rd32(r, r->esp + 0x114);
    r->ecx = r->ecx + r->ebp;
    r->ebx = r->ebx + rd32(r, r->esp + 0x118);
    r->edi = r->edi + r->ebx;
    r->ebx = rd32(r, r->esp + 0x104);
    r->ebx = r->ebx + r->edi;
    r->ebx = r->ebx + 0x20000;
    r->ebx = (uint32_t)((int32_t)r->ebx >> 0x12);
    r->ebp = rd32(r, r->esp + 0x13c);
    r->ebx = r->ebx & 0x3ff;
    r->ebp = r->ebp + r->ebx;
    set_low8(&r->ebx, rd8(r, r->ebp));
    wr8(r, r->edx, (r->ebx & 0xff));
    r->ebx = rd32(r, r->esp + 0x104);
    r->ebx = r->ebx - r->edi;
    r->ebx = r->ebx + 0x20000;
    r->ebx = (uint32_t)((int32_t)r->ebx >> 0x12);
    r->edi = rd32(r, r->esp + 0x13c);
    r->ebx = r->ebx & 0x3ff;
    set_low8(&r->ebx, rd8(r, r->edi + r->ebx));
    wr8(r, r->edx + 0x7, (r->ebx & 0xff));
    r->ebx = rd32(r, r->esp + 0x108);
    r->ebx = r->ebx + r->ecx;
    r->ebx = r->ebx + 0x20000;
    r->ebx = (uint32_t)((int32_t)r->ebx >> 0x12);
    r->ebx = r->ebx & 0x3ff;
    set_low8(&r->ebx, rd8(r, r->edi + r->ebx));
    wr8(r, r->edx + 0x1, (r->ebx & 0xff));
    r->ebx = rd32(r, r->esp + 0x108);
    r->ebx = r->ebx - r->ecx;
    r->ecx = r->ebx + 0x20000;
    r->ecx = (uint32_t)((int32_t)r->ecx >> 0x12);
    r->ecx = r->ecx & 0x3ff;
    r->ecx = r->ecx + r->edi;
    set_low8(&r->ebx, rd8(r, r->ecx));
    r->ecx = rd32(r, r->esp + 0x134);
    r->ecx = r->ecx + r->esi;
    r->ecx = r->ecx + 0x20000;
    r->ecx = (uint32_t)((int32_t)r->ecx >> 0x12);
    r->ecx = r->ecx & 0x3ff;
    r->ecx = r->ecx + r->edi;
    wr8(r, r->edx + 0x6, (r->ebx & 0xff));
    set_low8(&r->ebx, rd8(r, r->ecx));
    wr8(r, r->edx + 0x2, (r->ebx & 0xff));
    r->ecx = rd32(r, r->esp + 0x134);
    r->ecx = r->ecx - r->esi;
    r->ecx = r->ecx + 0x20000;
    r->ecx = (uint32_t)((int32_t)r->ecx >> 0x12);
    r->ecx = r->ecx & 0x3ff;
    r->ecx = r->ecx + r->edi;
    set_low8(&r->ebx, rd8(r, r->ecx));
    r->ecx = rd32(r, r->esp + 0x12c);
    wr8(r, r->edx + 0x5, (r->ebx & 0xff));
    r->ecx = r->ecx + rd32(r, r->esp + 0x144);
    r->ecx = r->ecx + 0x20000;
    r->ecx = (uint32_t)((int32_t)r->ecx >> 0x12);
    r->ecx = r->ecx & 0x3ff;
    r->ecx = r->ecx + r->edi;
    r->ebp = r->edi;
    r->edi = rd32(r, r->esp + 0x144);
    set_low8(&r->ebx, rd8(r, r->ecx));
    r->ecx = rd32(r, r->esp + 0x12c);
    r->ecx = r->ecx - r->edi;
    r->ecx = r->ecx + 0x20000;
    r->ecx = (uint32_t)((int32_t)r->ecx >> 0x12);
    r->ecx = r->ecx & 0x3ff;
    r->ecx = r->ecx + r->ebp;
    wr8(r, r->edx + 0x3, (r->ebx & 0xff));
    set_low8(&r->ebx, rd8(r, r->ecx));
    r->eax = r->eax + 0x20;
    wr8(r, r->edx + 0x4, (r->ebx & 0xff));
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4c4172;
}

uint32_t vertrix_port_jpeg_idct_8x8_4c4000(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x170
    };
    Port port;
    uint8_t stack[BELOW + 8 + 4 * 8];
    Regs r;
    port_open_arguments(&port, stack, calls, services, globals, entry, BELOW, 8);
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
