#include "port_rtljpegmergedupsamples.h"

/* libjpeg h2v2_merged_upsample: upsamples and colour-converts two output rows from one chroma row.
 */

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

/* Original 0x4c2000: libjpeg h2v2_merged_upsample: upsamples and colour-converts two output rows
 * from one chroma row. Evidence: no calls. Register-for-register from the listing
 * (0x4c2000..0x4c227f); labels are the original addresses. */
static void run(Regs *r)
{
    push_mem(r, r->esi);
    push_mem(r, r->edi);
    push_mem(r, r->ebp);
    r->esp = r->esp - 0x38;
    wr32(r, r->esp + 0xc, r->eax);
    r->esi = r->ebx;
    r->eax = r->edx;
    r->ebx = r->ecx;
    r->ecx = rd32(r, r->esp + 0xc);
    r->ecx = rd32(r, r->ecx + 0x1c4);
    r->edi = rd32(r, r->ecx + 0x10);
    wr32(r, r->esp + 0x18, r->edi);
    r->edi = rd32(r, r->ecx + 0x14);
    wr32(r, r->esp + 0x1c, r->edi);
    r->edi = rd32(r, r->ecx + 0x18);
    r->ecx = rd32(r, r->ecx + 0x1c);
    wr32(r, r->esp + 0x10, r->edi);
    wr32(r, r->esp + 0x14, r->ecx);
    r->edi = r->esi * 8;
    r->ecx = rd32(r, r->eax);
    r->ecx = r->ecx + r->edi;
    r->edi = rd32(r, r->ecx);
    r->ecx = rd32(r, r->ecx + 0x4);
    wr32(r, r->esp + 0x30, r->ecx);
    r->ecx = rd32(r, r->eax + 0x4);
    r->eax = rd32(r, r->eax + 0x8);
    r->edx = rd32(r, r->esp + 0xc);
    r->eax = rd32(r, r->eax + r->esi * 4);
    r->ecx = rd32(r, r->ecx + r->esi * 4);
    wr32(r, r->esp + 0x24, r->eax);
    r->eax = rd32(r, r->esp + 0xc);
    r->edx = rd32(r, r->edx + 0x144);
    wr32(r, r->esp + 0x20, r->ecx);
    r->eax = rd32(r, r->eax + 0x70);
    r->esi = rd32(r, r->ebx);
    r->eax = r->eax >> 0x1;
    r->ecx = rd32(r, r->ebx + 0x4);
    wr32(r, r->esp + 0x28, r->eax);
    if (r->eax == 0)
    {
        goto at_4c21d0;
    }
at_4c2082:
    r->ebx = rd32(r, r->esp + 0x20);
    r->eax = 0;
    set_low8(&r->eax, rd8(r, r->ebx));
    wr32(r, r->esp + 0x8, r->eax);
    r->eax = rd32(r, r->esp + 0x24);
    set_low8(&r->eax, rd8(r, r->eax));
    r->ebp = r->ebx + 0x1;
    r->ebx = rd32(r, r->esp + 0x24);
    r->eax = r->eax & 0xff;
    r->ebx = r->ebx + 1;
    r->eax = r->eax << 0x2;
    wr32(r, r->esp + 0x24, r->ebx);
    r->ebx = rd32(r, r->esp + 0x18);
    r->ebx = rd32(r, r->ebx + r->eax);
    wr32(r, r->esp + 0x20, r->ebp);
    wr32(r, r->esp, r->ebx);
    r->ebx = rd32(r, r->esp + 0x8);
    r->ebp = rd32(r, r->esp + 0x14);
    r->ebx = r->ebx << 0x2;
    r->ebp = r->ebp + r->ebx;
    wr32(r, r->esp + 0x34, r->ebp);
    r->ebp = rd32(r, r->esp + 0x10);
    r->ebp = r->ebp + r->eax;
    r->eax = rd32(r, r->esp + 0x34);
    r->eax = rd32(r, r->eax);
    wr32(r, r->esp + 0x34, r->eax);
    r->eax = rd32(r, r->ebp);
    r->ebp = rd32(r, r->esp + 0x34);
    r->ebp = r->ebp + r->eax;
    r->eax = r->ebp;
    r->eax = (uint32_t)((int32_t)r->eax >> 0x10);
    wr32(r, r->esp + 0x4, r->eax);
    r->ebx = r->ebx + rd32(r, r->esp + 0x1c);
    r->eax = rd32(r, r->ebx);
    wr32(r, r->esp + 0x2c, r->eax);
    r->eax = 0;
    r->ebp = rd32(r, r->esp);
    set_low8(&r->eax, rd8(r, r->edi));
    r->ebp = r->ebp + r->eax;
    set_low8(&r->ebx, rd8(r, r->edx + r->ebp));
    r->ebp = rd32(r, r->esp + 0x4);
    r->ebp = r->ebp + r->eax;
    wr8(r, r->esi, (r->ebx & 0xff));
    set_low8(&r->ebx, rd8(r, r->edx + r->ebp));
    wr8(r, r->esi + 0x1, (r->ebx & 0xff));
    r->eax = r->eax + rd32(r, r->esp + 0x2c);
    set_low8(&r->eax, rd8(r, r->edx + r->eax));
    wr8(r, r->esi + 0x2, (r->eax & 0xff));
    r->eax = 0;
    r->ebp = rd32(r, r->esp);
    set_low8(&r->eax, rd8(r, r->edi + 0x1));
    r->ebp = r->ebp + r->eax;
    r->ebp = r->ebp + r->edx;
    set_low8(&r->ebx, rd8(r, r->ebp));
    r->ebp = rd32(r, r->esp + 0x4);
    r->ebp = r->ebp + r->eax;
    r->ebp = r->ebp + r->edx;
    wr8(r, r->esi + 0x3, (r->ebx & 0xff));
    set_low8(&r->ebx, rd8(r, r->ebp));
    r->eax = r->eax + rd32(r, r->esp + 0x2c);
    wr8(r, r->esi + 0x4, (r->ebx & 0xff));
    set_low8(&r->eax, rd8(r, r->edx + r->eax));
    r->ebx = rd32(r, r->esp + 0x30);
    wr8(r, r->esi + 0x5, (r->eax & 0xff));
    r->eax = 0;
    r->ebp = rd32(r, r->esp);
    set_low8(&r->eax, rd8(r, r->ebx));
    r->ebp = r->ebp + r->eax;
    r->ebx = r->ebx + 1;
    r->ebp = r->ebp + r->edx;
    wr32(r, r->esp + 0x30, r->ebx);
    set_low8(&r->ebx, rd8(r, r->ebp));
    r->ebp = rd32(r, r->esp + 0x4);
    r->ebp = r->ebp + r->eax;
    wr8(r, r->ecx, (r->ebx & 0xff));
    set_low8(&r->ebx, rd8(r, r->edx + r->ebp));
    r->eax = r->eax + rd32(r, r->esp + 0x2c);
    wr8(r, r->ecx + 0x1, (r->ebx & 0xff));
    set_low8(&r->eax, rd8(r, r->edx + r->eax));
    r->ebx = rd32(r, r->esp + 0x30);
    wr8(r, r->ecx + 0x2, (r->eax & 0xff));
    r->eax = 0;
    r->ebp = rd32(r, r->esp);
    set_low8(&r->eax, rd8(r, r->ebx));
    r->ebp = r->ebp + r->eax;
    r->ebx = r->ebx + 1;
    r->ebp = r->ebp + r->edx;
    wr32(r, r->esp + 0x30, r->ebx);
    set_low8(&r->ebx, rd8(r, r->ebp));
    r->ebp = rd32(r, r->esp + 0x4);
    r->ebp = r->ebp + r->eax;
    r->ebp = r->ebp + r->edx;
    wr8(r, r->ecx + 0x3, (r->ebx & 0xff));
    r->edi = r->edi + 1;
    set_low8(&r->ebx, rd8(r, r->ebp));
    r->ebp = rd32(r, r->esp + 0x2c);
    r->esi = r->esi + 0x3;
    r->eax = r->eax + r->ebp;
    wr8(r, r->ecx + 0x4, (r->ebx & 0xff));
    r->ecx = r->ecx + 0x3;
    set_low8(&r->eax, rd8(r, r->edx + r->eax));
    r->edi = r->edi + 1;
    wr8(r, r->ecx + 0x2, (r->eax & 0xff));
    r->eax = rd32(r, r->esp + 0x28);
    r->esi = r->esi + 0x3;
    r->eax = r->eax - 1;
    r->ecx = r->ecx + 0x3;
    wr32(r, r->esp + 0x28, r->eax);
    if (r->eax != 0 && !r->port->env.failed)
    {
        goto at_4c2082;
    }
at_4c21d0:
    r->eax = rd32(r, r->esp + 0xc);
    if ((uint8_t)(rd8(r, r->eax + 0x70) & 0x1) != 0)
    {
        goto at_4c21e1;
    }
    r->esp = r->esp + 0x38;
    r->ebp = pop_mem(r);
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    return;
at_4c21e1:
    r->ebx = rd32(r, r->esp + 0x20);
    r->eax = 0;
    set_low8(&r->eax, rd8(r, r->ebx));
    r->ebx = rd32(r, r->esp + 0x24);
    wr32(r, r->esp + 0x8, r->eax);
    r->eax = 0;
    set_low8(&r->eax, rd8(r, r->ebx));
    r->ebx = rd32(r, r->esp + 0x18);
    r->eax = r->eax << 0x2;
    r->ebx = rd32(r, r->ebx + r->eax);
    wr32(r, r->esp, r->ebx);
    r->ebx = rd32(r, r->esp + 0x8);
    r->ebp = rd32(r, r->esp + 0x14);
    r->ebx = r->ebx << 0x2;
    r->ebp = r->ebp + r->ebx;
    wr32(r, r->esp + 0x34, r->ebp);
    r->ebp = rd32(r, r->esp + 0x10);
    r->ebp = r->ebp + r->eax;
    r->eax = rd32(r, r->esp + 0x34);
    r->eax = rd32(r, r->eax);
    r->eax = r->eax + rd32(r, r->ebp);
    r->eax = (uint32_t)((int32_t)r->eax >> 0x10);
    wr32(r, r->esp + 0x4, r->eax);
    r->eax = 0;
    r->ebp = rd32(r, r->esp + 0x1c);
    set_low8(&r->eax, rd8(r, r->edi));
    r->edi = rd32(r, r->esp);
    r->ebx = r->ebx + r->ebp;
    r->edi = r->edi + r->eax;
    r->ebp = rd32(r, r->ebx);
    set_low8(&r->ebx, rd8(r, r->edx + r->edi));
    r->edi = rd32(r, r->esp + 0x4);
    r->edi = r->edi + r->eax;
    wr8(r, r->esi, (r->ebx & 0xff));
    set_low8(&r->ebx, rd8(r, r->edx + r->edi));
    r->eax = r->eax + r->ebp;
    wr8(r, r->esi + 0x1, (r->ebx & 0xff));
    set_low8(&r->eax, rd8(r, r->edx + r->eax));
    r->ebx = rd32(r, r->esp + 0x30);
    wr8(r, r->esi + 0x2, (r->eax & 0xff));
    r->eax = 0;
    set_low8(&r->eax, rd8(r, r->ebx));
    r->ebx = rd32(r, r->esp);
    r->ebx = r->ebx + r->eax;
    set_low8(&r->ebx, rd8(r, r->edx + r->ebx));
    wr8(r, r->ecx, (r->ebx & 0xff));
    r->ebx = rd32(r, r->esp + 0x4);
    r->ebx = r->ebx + r->eax;
    set_low8(&r->ebx, rd8(r, r->edx + r->ebx));
    r->eax = r->eax + r->ebp;
    wr8(r, r->ecx + 0x1, (r->ebx & 0xff));
    set_low8(&r->eax, rd8(r, r->edx + r->eax));
    wr8(r, r->ecx + 0x2, (r->eax & 0xff));
    r->esp = r->esp + 0x38;
    r->ebp = pop_mem(r);
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    return;
}

uint32_t vertrix_port_jpeg_h2v2_merged_upsample_4c2000(PORT_SIGNATURE)
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
