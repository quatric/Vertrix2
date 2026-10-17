#include "port_rtljpegidct4s.h"

/* libjpeg jpeg_idct_4x4: the reduced-size inverse DCT giving a 4x4 block. */

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

/* Original 0x4c4730: libjpeg jpeg_idct_4x4: the reduced-size inverse DCT giving a 4x4 block.
 * Evidence: no calls. Register-for-register from the listing (0x4c4730..0x4c4af3); labels are the
 * original addresses. */
static void run(Regs *r)
{
    push_mem(r, r->esi);
    push_mem(r, r->edi);
    push_mem(r, r->ebp);
    r->esp = r->esp - 0xa8;
    r->esi = r->eax;
    wr32(r, r->esp + 0x9c, r->ecx);
    r->eax = r->edx;
    r->edx = r->ebx;
    r->ecx = rd32(r, r->esi + 0x144);
    r->ecx = r->ecx + 0x80;
    r->ebx = r->esp;
    wr32(r, r->esp + 0xa4, r->ecx);
    r->ecx = rd32(r, r->eax + 0x50);
    r->eax = 0x8;
at_4c4763:
    if ((uint16_t)rd16(r, r->edx + 0x10) != (uint16_t)0x0)
    {
        goto at_4c47ba;
    }
    if ((uint16_t)rd16(r, r->edx + 0x20) != (uint16_t)0x0)
    {
        goto at_4c47ba;
    }
    if ((uint16_t)rd16(r, r->edx + 0x30) != (uint16_t)0x0)
    {
        goto at_4c47ba;
    }
    if ((uint16_t)rd16(r, r->edx + 0x50) != (uint16_t)0x0)
    {
        goto at_4c47ba;
    }
    if ((uint16_t)rd16(r, r->edx + 0x60) != (uint16_t)0x0)
    {
        goto at_4c47ba;
    }
    if ((uint16_t)rd16(r, r->edx + 0x70) != (uint16_t)0x0)
    {
        goto at_4c47ba;
    }
    r->esi = (uint32_t)(int32_t)(int16_t)rd16(r, r->edx);
    r->esi = r->esi * rd32(r, r->ecx);
    r->esi = r->esi << 0x2;
    wr32(r, r->ebx, r->esi);
    wr32(r, r->ebx + 0x20, r->esi);
    wr32(r, r->ebx + 0x40, r->esi);
    wr32(r, r->ebx + 0x60, r->esi);
at_4c47a1:
    r->edx = r->edx + 0x2;
    r->ecx = r->ecx + 0x4;
    r->eax = r->eax - 1;
    r->ebx = r->ebx + 0x4;
    if ((int32_t)r->eax <= 0)
    {
        goto at_4c493c;
    }
    if (r->eax == 0x4 && !r->port->env.failed)
    {
        goto at_4c47a1;
    }
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4c4763;
at_4c47ba:
    r->esi = (uint32_t)(int32_t)(int16_t)rd16(r, r->edx);
    r->esi = r->esi * rd32(r, r->ecx);
    r->edi = rd32(r, r->edx + 0x1e);
    r->ebp = rd32(r, r->ecx + 0x40);
    r->edi = (uint32_t)((int32_t)r->edi >> 0x10);
    r->ebp = r->ebp * r->edi;
    r->edi = rd32(r, r->edx + 0x5e);
    wr32(r, r->esp + 0x8c, r->ebp);
    r->edi = (uint32_t)((int32_t)r->edi >> 0x10);
    r->edi = r->edi * rd32(r, r->ecx + 0xc0);
    r->ebp = rd32(r, r->esp + 0x8c) * 0x3b21;
    r->edi = r->edi * 0xffffe782u;
    r->esi = r->esi << 0xe;
    r->edi = r->edi + r->ebp;
    r->ebp = r->esi + r->edi;
    r->esi = r->esi - r->edi;
    wr32(r, r->esp + 0x84, r->esi);
    r->esi = rd32(r, r->edx + 0x6e);
    r->edi = rd32(r, r->ecx + 0xe0);
    r->esi = (uint32_t)((int32_t)r->esi >> 0x10);
    r->edi = r->edi * r->esi;
    r->esi = rd32(r, r->edx + 0x4e);
    wr32(r, r->esp + 0x88, r->edi);
    r->esi = (uint32_t)((int32_t)r->esi >> 0x10);
    r->edi = rd32(r, r->ecx + 0xa0);
    r->edi = r->edi * r->esi;
    wr32(r, r->esp + 0x8c, r->edi);
    r->edi = rd32(r, r->edx + 0x2e);
    r->esi = rd32(r, r->ecx + 0x60);
    r->edi = (uint32_t)((int32_t)r->edi >> 0x10);
    r->edi = r->edi * r->esi;
    wr32(r, r->esp + 0x80, r->ebp);
    r->esi = rd32(r, r->edx + 0xe);
    r->ebp = rd32(r, r->ecx + 0x20);
    r->esi = (uint32_t)((int32_t)r->esi >> 0x10);
    r->ebp = r->ebp * r->esi;
    wr32(r, r->esp + 0x90, r->ebp);
    r->esi = rd32(r, r->esp + 0x88) * 0xfffff93eu;
    r->ebp = rd32(r, r->esp + 0x8c);
    wr32(r, r->esp + 0x94, r->esi);
    r->esi = r->ebp * 0x2e75;
    r->ebp = rd32(r, r->esp + 0x94);
    r->ebp = r->ebp + r->esi;
    r->esi = r->edi * 0xffffba79u;
    r->edi = r->edi * 0x1ccd;
    r->ebp = r->ebp + r->esi;
    wr32(r, r->esp + 0x94, r->ebp);
    r->esi = rd32(r, r->esp + 0x90) * 0x21f9;
    r->esi = r->esi + rd32(r, r->esp + 0x94);
    r->ebp = rd32(r, r->esp + 0x88) * 0xffffefb0u;
    wr32(r, r->esp + 0x94, r->ebp);
    r->ebp = rd32(r, r->esp + 0x8c) * 0xffffecc2u;
    wr32(r, r->esp + 0x98, r->ebp);
    r->ebp = rd32(r, r->esp + 0x94);
    r->ebp = r->ebp + rd32(r, r->esp + 0x98);
    r->edi = r->edi + r->ebp;
    r->ebp = rd32(r, r->esp + 0x90) * 0x5203;
    r->edi = r->edi + r->ebp;
    r->ebp = rd32(r, r->esp + 0x80);
    r->ebp = r->ebp + r->edi;
    r->ebp = r->ebp + 0x800;
    r->ebp = (uint32_t)((int32_t)r->ebp >> 0xc);
    wr32(r, r->ebx, r->ebp);
    r->ebp = rd32(r, r->esp + 0x80);
    r->ebp = r->ebp - r->edi;
    r->edi = r->ebp + 0x800;
    r->edi = (uint32_t)((int32_t)r->edi >> 0xc);
    wr32(r, r->ebx + 0x60, r->edi);
    r->edi = rd32(r, r->esp + 0x84);
    r->edi = r->edi + r->esi;
    r->edi = r->edi + 0x800;
    r->edi = (uint32_t)((int32_t)r->edi >> 0xc);
    wr32(r, r->ebx + 0x20, r->edi);
    r->edi = rd32(r, r->esp + 0x84);
    r->edi = r->edi - r->esi;
    r->esi = r->edi + 0x800;
    r->esi = (uint32_t)((int32_t)r->esi >> 0xc);
    wr32(r, r->ebx + 0x40, r->esi);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4c47a1;
at_4c493c:
    r->edi = rd32(r, r->esp + 0x9c);
    r->edx = r->edi + 0x10;
    r->eax = r->esp;
    wr32(r, r->esp + 0xa0, r->edx);
at_4c494f:
    r->ebp = rd32(r, r->esp + 0xb8);
    r->edx = rd32(r, r->edi);
    r->ecx = rd32(r, r->eax + 0x4);
    r->edx = r->edx + r->ebp;
    if (r->ecx != 0)
    {
        goto at_4c49bf;
    }
    if (rd32(r, r->eax + 0x8) != 0x0)
    {
        goto at_4c49bf;
    }
    if (rd32(r, r->eax + 0xc) != 0x0)
    {
        goto at_4c49bf;
    }
    if (rd32(r, r->eax + 0x14) != 0x0)
    {
        goto at_4c49bf;
    }
    if (rd32(r, r->eax + 0x18) != 0x0)
    {
        goto at_4c49bf;
    }
    if (rd32(r, r->eax + 0x1c) != 0x0)
    {
        goto at_4c49bf;
    }
    r->ecx = rd32(r, r->eax);
    r->ecx = r->ecx + 0x10;
    r->ecx = (uint32_t)((int32_t)r->ecx >> 0x5);
    r->ebx = rd32(r, r->esp + 0xa4);
    r->ecx = r->ecx & 0x3ff;
    set_low8(&r->ebx, rd8(r, r->ecx + r->ebx));
    wr8(r, r->edx, (r->ebx & 0xff));
    wr8(r, r->edx + 0x1, (r->ebx & 0xff));
    wr8(r, r->edx + 0x2, (r->ebx & 0xff));
    r->eax = r->eax + 0x20;
    wr8(r, r->edx + 0x3, (r->ebx & 0xff));
at_4c49a5:
    r->esi = rd32(r, r->esp + 0xa0);
    r->edi = r->edi + 0x4;
    if (r->edi != r->esi && !r->port->env.failed)
    {
        goto at_4c494f;
    }
    r->esp = r->esp + 0xa8;
    r->ebp = pop_mem(r);
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    return;
at_4c49bf:
    r->esi = rd32(r, r->eax + 0x8) * 0x3b21;
    r->ebx = rd32(r, r->eax + 0x18) * 0xffffe782u;
    r->ecx = rd32(r, r->eax);
    r->ecx = r->ecx << 0xe;
    r->esi = r->esi + r->ebx;
    r->ebx = r->ecx + r->esi;
    r->ecx = r->ecx - r->esi;
    wr32(r, r->esp + 0x84, r->ecx);
    r->ecx = rd32(r, r->eax + 0x1c);
    wr32(r, r->esp + 0x88, r->ecx);
    r->ecx = rd32(r, r->eax + 0x14);
    wr32(r, r->esp + 0x8c, r->ecx);
    r->ecx = rd32(r, r->eax + 0x4);
    wr32(r, r->esp + 0x90, r->ecx);
    r->esi = rd32(r, r->esp + 0x88) * 0xfffff93eu;
    r->ecx = rd32(r, r->esp + 0x8c) * 0x2e75;
    wr32(r, r->esp + 0x80, r->ebx);
    r->ebx = rd32(r, r->eax + 0xc);
    r->esi = r->esi + r->ecx;
    r->ecx = r->ebx * 0xffffba79u;
    r->ebx = r->ebx * 0x1ccd;
    r->ebp = rd32(r, r->esp + 0x90);
    r->ecx = r->ecx + r->esi;
    r->esi = r->ebp * 0x21f9;
    r->ebp = rd32(r, r->esp + 0x88);
    r->ecx = r->ecx + r->esi;
    r->esi = r->ebp * 0xffffefb0u;
    r->ebp = rd32(r, r->esp + 0x8c) * 0xffffecc2u;
    r->esi = r->esi + r->ebp;
    r->ebp = rd32(r, r->esp + 0x90);
    r->ebx = r->ebx + r->esi;
    r->esi = r->ebp * 0x5203;
    r->esi = r->esi + r->ebx;
    r->ebx = rd32(r, r->esp + 0x80);
    r->ebx = r->ebx + r->esi;
    r->ebx = r->ebx + 0x40000;
    r->ebx = (uint32_t)((int32_t)r->ebx >> 0x13);
    r->ebp = rd32(r, r->esp + 0xa4);
    r->ebx = r->ebx & 0x3ff;
    r->ebp = r->ebp + r->ebx;
    set_low8(&r->ebx, rd8(r, r->ebp));
    wr8(r, r->edx, (r->ebx & 0xff));
    r->ebx = rd32(r, r->esp + 0x80);
    r->ebx = r->ebx - r->esi;
    r->ebx = r->ebx + 0x40000;
    r->ebx = (uint32_t)((int32_t)r->ebx >> 0x13);
    r->esi = rd32(r, r->esp + 0xa4);
    r->ebx = r->ebx & 0x3ff;
    set_low8(&r->ebx, rd8(r, r->esi + r->ebx));
    wr8(r, r->edx + 0x3, (r->ebx & 0xff));
    r->ebx = rd32(r, r->esp + 0x84);
    r->ebx = r->ebx + r->ecx;
    r->ebx = r->ebx + 0x40000;
    r->ebx = (uint32_t)((int32_t)r->ebx >> 0x13);
    r->ebx = r->ebx & 0x3ff;
    set_low8(&r->ebx, rd8(r, r->esi + r->ebx));
    wr8(r, r->edx + 0x1, (r->ebx & 0xff));
    r->ebx = rd32(r, r->esp + 0x84);
    r->ebx = r->ebx - r->ecx;
    r->ecx = r->ebx + 0x40000;
    r->ecx = (uint32_t)((int32_t)r->ecx >> 0x13);
    r->ecx = r->ecx & 0x3ff;
    r->ecx = r->ecx + r->esi;
    set_low8(&r->ebx, rd8(r, r->ecx));
    r->eax = r->eax + 0x20;
    wr8(r, r->edx + 0x2, (r->ebx & 0xff));
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4c49a5;
}

uint32_t vertrix_port_jpeg_idct_4x4_4c4730(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0xd0
    };
    Port port;
    uint8_t stack[BELOW + 8 + 4 * 511];
    Regs r;
    port_open_arguments(&port, stack, calls, services, globals, entry, BELOW, 511);
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
