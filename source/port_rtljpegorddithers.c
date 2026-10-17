#include "port_rtljpegorddithers.h"

/* libjpeg quantize3_ord_dither: three-component quantisation with the ordered dither matrix. */

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

/* Original 0x4c6640: libjpeg quantize3_ord_dither: three-component quantisation with the ordered
 * dither matrix. Evidence: no calls. Register-for-register from the listing (0x4c6640..0x4c6790);
 * labels are the original addresses. */
static void run(Regs *r)
{
    push_mem(r, r->esi);
    push_mem(r, r->edi);
    push_mem(r, r->ebp);
    r->esp = r->esp - 0x38;
    r->esi = r->edx;
    wr32(r, r->esp + 0x4, r->ecx);
    r->edx = rd32(r, r->eax + 0x1cc);
    wr32(r, r->esp + 0x1c, r->edx);
    r->edx = rd32(r, r->edx + 0x18);
    r->eax = rd32(r, r->eax + 0x70);
    r->ecx = rd32(r, r->edx);
    wr32(r, r->esp + 0x8, r->eax);
    wr32(r, r->esp + 0x24, r->ecx);
    r->ecx = rd32(r, r->edx + 0x4);
    r->edx = rd32(r, r->edx + 0x8);
    wr32(r, r->esp + 0x28, r->ecx);
    wr32(r, r->esp + 0x20, r->edx);
    r->edx = 0;
    r->ecx = rd32(r, r->esp + 0x4);
    wr32(r, r->esp + 0x10, r->edx);
    if ((int32_t)r->ecx <= 0)
    {
        goto at_4c678a;
    }
    wr32(r, r->esp + 0xc, r->ebx);
    wr32(r, r->esp + 0x14, r->esi);
at_4c668e:
    r->eax = rd32(r, r->esp + 0x1c);
    r->eax = rd32(r, r->eax + 0x30);
    wr32(r, r->esp + 0x18, r->eax);
    r->ecx = rd32(r, r->esp + 0x1c);
    r->edx = rd32(r, r->esp + 0x18);
    r->ecx = rd32(r, r->ecx + 0x34);
    r->edx = r->edx << 0x6;
    r->ecx = r->ecx + r->edx;
    wr32(r, r->esp + 0x30, r->ecx);
    r->ecx = rd32(r, r->esp + 0x1c);
    r->ecx = rd32(r, r->ecx + 0x38);
    r->ebx = rd32(r, r->esp + 0xc);
    r->ecx = r->ecx + r->edx;
    r->esi = 0;
    wr32(r, r->esp, r->ecx);
    r->ecx = rd32(r, r->esp + 0x1c);
    r->eax = rd32(r, r->esp + 0x14);
    r->ebx = rd32(r, r->ebx);
    r->ecx = rd32(r, r->ecx + 0x3c);
    r->eax = rd32(r, r->eax);
    r->ecx = r->ecx + r->edx;
    r->edx = rd32(r, r->esp + 0x8);
    wr32(r, r->esp + 0x2c, r->ecx);
    wr32(r, r->esp + 0x34, r->edx);
    if (r->edx == 0)
    {
        goto at_4c674c;
    }
at_4c66e0:
    r->edi = rd32(r, r->esp + 0x30);
    r->edx = 0;
    r->ecx = r->esi * 4;
    set_low8(&r->edx, rd8(r, r->eax));
    r->ebp = rd32(r, r->ecx + r->edi);
    r->edi = rd32(r, r->esp + 0x24);
    r->edx = r->edx + r->ebp;
    r->edx = r->edx + r->edi;
    r->eax = r->eax + 1;
    set_low8(&r->edx, rd8(r, r->edx));
    r->ebp = rd8(r, r->eax);
    r->edi = rd32(r, r->esp);
    r->ebp = r->ebp + rd32(r, r->ecx + r->edi);
    r->edi = rd32(r, r->esp + 0x28);
    r->edi = r->edi + r->ebp;
    r->edx = r->edx & 0xff;
    r->edi = rd8(r, r->edi);
    r->edx = r->edx + r->edi;
    r->edi = rd32(r, r->esp + 0x2c);
    r->ecx = r->ecx + r->edi;
    r->edi = rd8(r, r->eax + 0x1);
    r->ecx = rd32(r, r->ecx);
    r->ebp = rd32(r, r->esp + 0x20);
    r->ecx = r->ecx + r->edi;
    r->eax = r->eax + 1;
    r->ecx = r->ecx + r->ebp;
    r->eax = r->eax + 1;
    set_low8(&r->ecx, rd8(r, r->ecx));
    r->ecx = r->ecx & 0xff;
    r->ebx = r->ebx + 1;
    r->edx = r->edx + r->ecx;
    wr8(r, r->ebx - 0x1, (r->edx & 0xff));
    r->edx = rd32(r, r->esp + 0x34);
    r->esi = r->esi + 1;
    r->edx = r->edx - 1;
    r->esi = r->esi & 0xf;
    wr32(r, r->esp + 0x34, r->edx);
    if (r->edx != 0 && !r->port->env.failed)
    {
        goto at_4c66e0;
    }
at_4c674c:
    r->eax = rd32(r, r->esp + 0x18);
    r->edx = rd32(r, r->esp + 0x1c);
    r->ebx = rd32(r, r->esp + 0xc);
    r->esi = rd32(r, r->esp + 0x14);
    r->edi = rd32(r, r->esp + 0x10);
    r->ebp = rd32(r, r->esp + 0x4);
    r->eax = r->eax + 1;
    r->ebx = r->ebx + 0x4;
    r->esi = r->esi + 0x4;
    r->edi = r->edi + 1;
    r->eax = r->eax & 0xf;
    wr32(r, r->esp + 0xc, r->ebx);
    wr32(r, r->esp + 0x14, r->esi);
    wr32(r, r->esp + 0x10, r->edi);
    wr32(r, r->esp + 0x18, r->eax);
    wr32(r, r->edx + 0x30, r->eax);
    if ((int32_t)r->edi < (int32_t)r->ebp && !r->port->env.failed)
    {
        goto at_4c668e;
    }
at_4c678a:
    r->esp = r->esp + 0x38;
    r->ebp = pop_mem(r);
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    return;
}

uint32_t vertrix_port_jpeg_quantize3_ord_dither_4c6640(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x60
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
