#include "port_rtlhuffderivedtables.h"

/* This is most likely the libjpeg 6b Huffman decoder setup jpeg_make_d_derived_tbl, built into
 * Vertrix2.exe for JPEG loading. */

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

static void set_high8(uint32_t *reg, uint32_t value)
{
    *reg = (*reg & 0xffff00ffu) | ((value & 0xff) << 8);
}

/* An indirect call (an import or a method): every value pushed passed and popped, as stdcall. */
static void call_all(Regs *r, uint32_t target)
{
    call_with_stack(r, target, r->pushed, 0);
}

/* Original 0x4bbc00: This is most likely the libjpeg 6b Huffman decoder setup
 * jpeg_make_d_derived_tbl, built into Vertrix2.exe for JPEG loading. At 0x4bbc00 it checks the
 * table number in ebx (0-3). It picks the table from cinfo+0xb4 or cinfo+0xc4 depending on edx, and
 * raises error 0x32 if the number is out of range or the table is missing. It allocates the
 * 0x590-byte derived table through cinfo->mem if *ecx is empty and stores the source table at
 * +0x8c. It then builds the code sizes and canonical codes from the 16 bit-length counts, raising
 * error 8 when the table is invalid (0x4bbd42, 0x4bbd6b). Evidence: calls 0x4eb5c0.
 * Register-for-register from the listing (0x4bbc0b..0x4bbf2a); labels are the original addresses.
 */
static void run(Regs *r)
{
    wr32(r, r->ebp - 0x30, r->eax);
    wr32(r, r->ebp - 0x44, r->edx);
    if ((int32_t)r->ebx < 0)
    {
        goto at_4bbc1a;
    }
    if ((int32_t)r->ebx < (int32_t)0x4)
    {
        goto at_4bbc38;
    }
at_4bbc1a:
    r->eax = rd32(r, r->ebp - 0x30);
    r->eax = rd32(r, r->eax);
    wr32(r, r->eax + 0x14, 0x32);
    r->eax = rd32(r, r->ebp - 0x30);
    r->eax = rd32(r, r->eax);
    r->edx = rd32(r, r->ebp - 0x30);
    wr32(r, r->eax + 0x18, r->ebx);
    r->edx = rd32(r, r->edx);
    r->eax = rd32(r, r->ebp - 0x30);
    call_all(r, rd32(r, r->edx));
at_4bbc38:
    r->edx = rd32(r, r->ebp - 0x30);
    r->eax = r->ebx * 4;
    r->esi = rd32(r, r->ebp - 0x44);
    r->eax = r->eax + r->edx;
    if (r->esi == 0)
    {
        goto at_4bbccc;
    }
    r->eax = rd32(r, r->eax + 0xb4);
at_4bbc55:
    wr32(r, r->ebp - 0x3c, r->eax);
    if (r->eax != 0)
    {
        goto at_4bbc7a;
    }
    r->eax = rd32(r, r->ebp - 0x30);
    r->eax = rd32(r, r->eax);
    wr32(r, r->eax + 0x14, 0x32);
    r->eax = rd32(r, r->ebp - 0x30);
    r->eax = rd32(r, r->eax);
    r->edx = rd32(r, r->ebp - 0x30);
    wr32(r, r->eax + 0x18, r->ebx);
    r->edx = rd32(r, r->edx);
    r->eax = rd32(r, r->ebp - 0x30);
    call_all(r, rd32(r, r->edx));
at_4bbc7a:
    if (rd32(r, r->ecx) == 0x0)
    {
        goto at_4bbcd4;
    }
at_4bbc7f:
    r->eax = rd32(r, r->ecx);
    wr32(r, r->ebp - 0x24, r->eax);
    r->edx = rd32(r, r->ebp - 0x24);
    r->eax = rd32(r, r->ebp - 0x3c);
    r->ebx = 0;
    wr32(r, r->edx + 0x8c, r->eax);
    r->eax = 0x1;
    r->ecx = rd32(r, r->ebp - 0x3c);
    wr32(r, r->ebp - 0xc, r->eax);
    r->ecx = r->ecx + r->eax;
at_4bbc9f:
    r->edx = 0;
    set_low8(&r->edx, rd8(r, r->ecx));
    if ((int32_t)r->edx < 0)
    {
        goto at_4bbd42;
    }
    r->eax = r->ebx + r->edx;
    if ((int32_t)r->eax > (int32_t)0x100)
    {
        goto at_4bbd42;
    }
at_4bbcb9:
    set_low8(&r->eax, rd8(r, r->ebp - 0xc));
at_4bbcbc:
    r->edx = r->edx - 1;
    if (r->edx == 0xffffffffu)
    {
        goto at_4bbced;
    }
    r->ebx = r->ebx + 1;
    wr8(r, r->ebx + r->ebp - 0x14d, (r->eax & 0xff));
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4bbcbc;
at_4bbccc:
    r->eax = rd32(r, r->eax + 0xc4);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4bbc55;
at_4bbcd4:
    r->esi = rd32(r, r->ebp - 0x30);
    r->ebx = 0x590;
    r->esi = rd32(r, r->esi + 0x4);
    r->edx = 0x1;
    r->eax = rd32(r, r->ebp - 0x30);
    call_all(r, rd32(r, r->esi));
    wr32(r, r->ecx, r->eax);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4bbc7f;
at_4bbced:
    r->edx = rd32(r, r->ebp - 0xc);
    r->edx = r->edx + 1;
    r->ecx = r->ecx + 1;
    wr32(r, r->ebp - 0xc, r->edx);
    if ((int32_t)r->edx <= (int32_t)0x10 && !r->port->env.failed)
    {
        goto at_4bbc9f;
    }
    set_high8(&r->eax, 0);
    wr32(r, r->ebp - 0x40, r->ebx);
    wr8(r, r->ebx + r->ebp - 0x14c, ((r->eax >> 8) & 0xff));
    r->eax = 0;
    r->edx = 0;
    set_low8(&r->eax, rd8(r, r->ebp - 0x14c));
    r->ebx = 0;
    wr32(r, r->ebp - 0x48, r->eax);
    if ((uint8_t)((r->eax & 0xff)) == 0)
    {
        goto at_4bbd95;
    }
at_4bbd1d:
    r->esi = rd32(r, r->ebp - 0x48);
    r->eax = r->ebx * 4;
at_4bbd27:
    r->ecx = 0;
    set_low8(&r->ecx, rd8(r, r->ebx + r->ebp - 0x14c));
    if (r->ecx != r->esi)
    {
        goto at_4bbd5d;
    }
    r->ebx = r->ebx + 1;
    wr32(r, r->eax + r->ebp - 0x550, r->edx);
    r->eax = r->eax + 0x4;
    r->edx = r->edx + 1;
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4bbd27;
at_4bbd42:
    r->eax = rd32(r, r->ebp - 0x30);
    r->eax = rd32(r, r->eax);
    r->esi = rd32(r, r->ebp - 0x30);
    wr32(r, r->eax + 0x14, 0x8);
    r->esi = rd32(r, r->esi);
    r->eax = rd32(r, r->ebp - 0x30);
    call_all(r, rd32(r, r->esi));
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4bbcb9;
at_4bbd5d:
    set_low8(&r->ecx, rd8(r, r->ebp - 0x48));
    r->eax = 0x1;
    r->eax = r->eax << (r->ecx & 0xff);
    if ((int32_t)r->edx < (int32_t)r->eax)
    {
        goto at_4bbd81;
    }
    r->eax = rd32(r, r->ebp - 0x30);
    r->eax = rd32(r, r->eax);
    r->ecx = rd32(r, r->ebp - 0x30);
    wr32(r, r->eax + 0x14, 0x8);
    r->ecx = rd32(r, r->ecx);
    r->eax = rd32(r, r->ebp - 0x30);
    call_all(r, rd32(r, r->ecx));
at_4bbd81:
    r->edi = rd32(r, r->ebp - 0x48);
    set_high8(&r->ecx, rd8(r, r->ebx + r->ebp - 0x14c));
    r->edi = r->edi + 1;
    r->edx = r->edx + r->edx;
    wr32(r, r->ebp - 0x48, r->edi);
    if ((uint8_t)(((r->ecx >> 8) & 0xff)) != 0 && !r->port->env.failed)
    {
        goto at_4bbd1d;
    }
at_4bbd95:
    r->eax = rd32(r, r->ebp - 0x24);
    r->ecx = rd32(r, r->ebp - 0x3c);
    r->esi = rd32(r, r->ebp - 0x24);
    r->edx = 0;
    r->eax = r->eax + 0x4;
    r->ecx = r->ecx + 1;
    r->esi = r->esi + 0x44;
at_4bbda7:
    if ((uint8_t)rd8(r, r->ecx) == (uint8_t)0x0)
    {
        goto at_4bbebc;
    }
    r->edi = r->edx;
    r->ebx = rd32(r, r->ebp + r->edx * 4 - 0x550);
    r->edi = r->edi - r->ebx;
    r->ebx = r->edi;
    wr32(r, r->eax + 0x48, r->edi);
    r->ebx = r->ebx ^ r->edi;
    set_low8(&r->ebx, rd8(r, r->ecx));
    r->edx = r->edx + r->ebx;
    r->ebx = rd32(r, r->ebp + r->edx * 4 - 0x554);
    wr32(r, r->eax, r->ebx);
at_4bbdcf:
    r->eax = r->eax + 0x4;
    r->ecx = r->ecx + 1;
    if (r->eax != r->esi && !r->port->env.failed)
    {
        goto at_4bbda7;
    }
    r->esi = 0x11;
    r->eax = rd32(r, r->ebp - 0x24);
    r->ebx = 0x400;
    r->edx = 0;
    r->eax = r->eax + 0x90;
    r->edi = 0;
    wr32(r, r->ebp - 0xc, r->esi);
    wr32(r, r->eax - 0x4c, 0xfffff);
    call(r, 0x4eb5c0, 0);
    r->eax = 0x1;
    wr32(r, r->ebp - 0x1c, r->edi);
    wr32(r, r->ebp - 0xc, r->eax);
    r->eax = rd32(r, r->ebp - 0x3c);
    r->edx = 0x7;
    r->eax = r->eax + 1;
    wr32(r, r->ebp - 0x34, r->edx);
    wr32(r, r->ebp - 0x38, r->eax);
at_4bbe16:
    r->edi = 0x1;
    r->eax = rd32(r, r->ebp - 0x34);
    set_low8(&r->ecx, rd8(r, r->ebp - 0x34));
    wr32(r, r->ebp - 0x2c, r->eax);
    r->eax = r->edi;
    r->eax = r->eax << (r->ecx & 0xff);
    wr32(r, r->ebp - 0x20, r->eax);
    r->eax = rd32(r, r->ebp - 0x38);
    wr32(r, r->ebp - 0x28, r->eax);
    r->eax = rd32(r, r->ebp - 0x1c);
    r->eax = r->eax << 0x2;
    r->edx = rd32(r, r->ebp - 0x3c);
    wr32(r, r->ebp - 0x14, r->eax);
    r->eax = rd32(r, r->ebp - 0x1c);
    r->eax = r->eax + r->edx;
    wr32(r, r->ebp - 0x18, r->edi);
    wr32(r, r->ebp - 0x10, r->eax);
at_4bbe48:
    r->edx = rd32(r, r->ebp - 0x28);
    r->eax = 0;
    r->ecx = rd32(r, r->ebp - 0x18);
    set_low8(&r->eax, rd8(r, r->edx));
    if ((int32_t)r->eax < (int32_t)r->ecx)
    {
        goto at_4bbec7;
    }
    r->esi = rd32(r, r->ebp - 0x14);
    set_low8(&r->ecx, rd8(r, r->ebp - 0x2c));
    r->esi = rd32(r, r->esi + r->ebp - 0x550);
    r->edx = rd32(r, r->ebp - 0x20);
    r->esi = r->esi << (r->ecx & 0xff);
    if ((int32_t)r->edx <= 0)
    {
        goto at_4bbe9c;
    }
    r->eax = rd32(r, r->ebp - 0x24);
    r->ebx = rd32(r, r->ebp - 0x24);
    r->eax = r->eax + r->esi;
    r->ecx = r->esi * 4;
    r->edi = rd32(r, r->ebp - 0x10);
    r->ecx = r->ecx + r->ebx;
at_4bbe80:
    r->ecx = r->ecx + 0x4;
    r->ebx = rd32(r, r->ebp - 0xc);
    r->eax = r->eax + 1;
    wr32(r, r->ecx + 0x8c, r->ebx);
    r->esi = r->esi + 1;
    set_low8(&r->ebx, rd8(r, r->edi + 0x11));
    r->edx = r->edx - 1;
    wr8(r, r->eax + 0x48f, (r->ebx & 0xff));
    if ((int32_t)r->edx > 0 && !r->port->env.failed)
    {
        goto at_4bbe80;
    }
at_4bbe9c:
    r->edi = rd32(r, r->ebp - 0x18);
    r->eax = rd32(r, r->ebp - 0x14);
    r->edx = rd32(r, r->ebp - 0x10);
    r->ecx = rd32(r, r->ebp - 0x1c);
    r->edi = r->edi + 1;
    r->eax = r->eax + 0x4;
    r->edx = r->edx + 1;
    r->ecx = r->ecx + 1;
    wr32(r, r->ebp - 0x18, r->edi);
    wr32(r, r->ebp - 0x14, r->eax);
    wr32(r, r->ebp - 0x10, r->edx);
    wr32(r, r->ebp - 0x1c, r->ecx);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4bbe48;
at_4bbebc:
    wr32(r, r->eax, 0xffffffffu);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4bbdcf;
at_4bbec7:
    r->ebx = rd32(r, r->ebp - 0x38);
    r->esi = rd32(r, r->ebp - 0x34);
    r->edi = rd32(r, r->ebp - 0xc);
    r->ebx = r->ebx + 1;
    r->esi = r->esi - 1;
    r->edi = r->edi + 1;
    wr32(r, r->ebp - 0x38, r->ebx);
    wr32(r, r->ebp - 0x34, r->esi);
    wr32(r, r->ebp - 0xc, r->edi);
    if ((int32_t)r->edi <= (int32_t)0x8 && !r->port->env.failed)
    {
        goto at_4bbe16;
    }
    if (rd32(r, r->ebp - 0x44) == 0x0)
    {
        goto at_4bbf24;
    }
    r->ecx = rd32(r, r->ebp - 0x40);
    r->edx = 0;
    if ((int32_t)r->ecx <= 0)
    {
        goto at_4bbf24;
    }
    r->ecx = rd32(r, r->ebp - 0x3c);
    r->esi = rd32(r, r->ebp - 0x40);
at_4bbefa:
    r->eax = 0;
    set_low8(&r->eax, rd8(r, r->ecx + 0x11));
    if ((int32_t)r->eax < 0)
    {
        goto at_4bbf08;
    }
    if ((int32_t)r->eax <= (int32_t)0xf)
    {
        goto at_4bbf1e;
    }
at_4bbf08:
    r->eax = rd32(r, r->ebp - 0x30);
    r->eax = rd32(r, r->eax);
    r->ebx = rd32(r, r->ebp - 0x30);
    wr32(r, r->eax + 0x14, 0x8);
    r->ebx = rd32(r, r->ebx);
    r->eax = rd32(r, r->ebp - 0x30);
    call_all(r, rd32(r, r->ebx));
at_4bbf1e:
    r->edx = r->edx + 1;
    r->ecx = r->ecx + 1;
    if ((int32_t)r->edx < (int32_t)r->esi && !r->port->env.failed)
    {
        goto at_4bbefa;
    }
at_4bbf24:
    r->edi = rd32(r, r->ebp - 0x8);
    r->esi = rd32(r, r->ebp - 0x4);
    return;
}

uint32_t vertrix_port_jpeg_make_huff_derived_table_4bbc00(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x554
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
    port_set32(&port, r.ebp, -0x4u, entry->esi);
    port_set32(&port, r.ebp, -0x8u, entry->edi);
    run(&r);
    return port_return(&port, r.eax, r.edx);
}
