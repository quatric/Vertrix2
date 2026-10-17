#include "port_rtljpegmergedchecks.h"

/* libjpeg use_merged_upsample: whether the merged upsampling and colour conversion path can be used
 * (no fancy upsampling, YCbCr to 3-component RGB, 2x1 or 2x2 luma sampling and matching scaled
 * sizes). */

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

static uint32_t rd32(Regs *r, uint32_t address)
{
    return port_u32(r->port, address, 0);
}

static void wr32(Regs *r, uint32_t address, uint32_t value)
{
    port_set32(r->port, address, 0, value);
}

/* Original 0x4c0b51: libjpeg use_merged_upsample: whether the merged upsampling and colour
 * conversion path can be used (no fancy upsampling, YCbCr to 3-component RGB, 2x1 or 2x2 luma
 * sampling and matching scaled sizes). Evidence: no calls. Register-for-register from the listing
 * (0x4c0b5f..0x4c0c8e); labels are the original addresses. */
static void run(Regs *r)
{
    wr32(r, r->ebp - 0x1c, r->eax);
    r->eax = rd32(r, r->ebp - 0x1c);
    if (rd32(r, r->eax + 0x4c) != 0x0)
    {
        goto at_4c0b77;
    }
    r->eax = rd32(r, r->ebp - 0x1c);
    if (rd32(r, r->eax + 0x12c) == 0x0)
    {
        goto at_4c0b83;
    }
at_4c0b77:
    wr32(r, r->ebp - 0x18, 0x0);
    goto at_4c0c82;
at_4c0b83:
    r->eax = rd32(r, r->ebp - 0x1c);
    if (rd32(r, r->eax + 0x28) != 0x3)
    {
        goto at_4c0b95;
    }
    r->eax = rd32(r, r->ebp - 0x1c);
    if (rd32(r, r->eax + 0x24) == 0x3)
    {
        goto at_4c0b97;
    }
at_4c0b95:
    goto at_4c0ba0;
at_4c0b97:
    r->eax = rd32(r, r->ebp - 0x1c);
    if (rd32(r, r->eax + 0x2c) == 0x2)
    {
        goto at_4c0ba2;
    }
at_4c0ba0:
    goto at_4c0bab;
at_4c0ba2:
    r->eax = rd32(r, r->ebp - 0x1c);
    if (rd32(r, r->eax + 0x78) == 0x3)
    {
        goto at_4c0bb7;
    }
at_4c0bab:
    wr32(r, r->ebp - 0x18, 0x0);
    goto at_4c0c82;
at_4c0bb7:
    r->eax = rd32(r, r->ebp - 0x1c);
    r->eax = rd32(r, r->eax + 0xd8);
    if (rd32(r, r->eax + 0x8) != 0x2)
    {
        goto at_4c0bd5;
    }
    r->eax = rd32(r, r->ebp - 0x1c);
    r->eax = rd32(r, r->eax + 0xd8);
    if (rd32(r, r->eax + 0x5c) == 0x1)
    {
        goto at_4c0bd7;
    }
at_4c0bd5:
    goto at_4c0be9;
at_4c0bd7:
    r->eax = rd32(r, r->ebp - 0x1c);
    r->eax = rd32(r, r->eax + 0xd8);
    if (rd32(r, r->eax + 0xb0) == 0x1)
    {
        goto at_4c0beb;
    }
at_4c0be9:
    goto at_4c0bfa;
at_4c0beb:
    r->eax = rd32(r, r->ebp - 0x1c);
    r->eax = rd32(r, r->eax + 0xd8);
    if ((int32_t)rd32(r, r->eax + 0xc) <= (int32_t)0x2)
    {
        goto at_4c0bfc;
    }
at_4c0bfa:
    goto at_4c0c0b;
at_4c0bfc:
    r->eax = rd32(r, r->ebp - 0x1c);
    r->eax = rd32(r, r->eax + 0xd8);
    if (rd32(r, r->eax + 0x60) == 0x1)
    {
        goto at_4c0c0d;
    }
at_4c0c0b:
    goto at_4c0c1f;
at_4c0c0d:
    r->eax = rd32(r, r->ebp - 0x1c);
    r->eax = rd32(r, r->eax + 0xd8);
    if (rd32(r, r->eax + 0xb4) == 0x1)
    {
        goto at_4c0c28;
    }
at_4c0c1f:
    wr32(r, r->ebp - 0x18, 0x0);
    goto at_4c0c82;
at_4c0c28:
    r->eax = rd32(r, r->ebp - 0x1c);
    r->eax = rd32(r, r->eax + 0xd8);
    r->edx = rd32(r, r->eax + 0x24);
    r->eax = rd32(r, r->ebp - 0x1c);
    if (r->edx != rd32(r, r->eax + 0x13c))
    {
        goto at_4c0c56;
    }
    r->eax = rd32(r, r->ebp - 0x1c);
    r->eax = rd32(r, r->eax + 0xd8);
    r->edx = rd32(r, r->eax + 0x78);
    r->eax = rd32(r, r->ebp - 0x1c);
    if (r->edx == rd32(r, r->eax + 0x13c))
    {
        goto at_4c0c58;
    }
at_4c0c56:
    goto at_4c0c72;
at_4c0c58:
    r->eax = rd32(r, r->ebp - 0x1c);
    r->eax = rd32(r, r->eax + 0xd8);
    r->edx = rd32(r, r->eax + 0xcc);
    r->eax = rd32(r, r->ebp - 0x1c);
    if (r->edx == rd32(r, r->eax + 0x13c))
    {
        goto at_4c0c7b;
    }
at_4c0c72:
    wr32(r, r->ebp - 0x18, 0x0);
    goto at_4c0c82;
at_4c0c7b:
    wr32(r, r->ebp - 0x18, 0x1);
at_4c0c82:
    r->eax = rd32(r, r->ebp - 0x18);
    r->edi = rd32(r, r->ebp - 0x14);
    r->esi = rd32(r, r->ebp - 0x10);
    r->edx = rd32(r, r->ebp - 0xc);
    r->ecx = rd32(r, r->ebp - 0x8);
    r->ebx = rd32(r, r->ebp - 0x4);
    return;
}

uint32_t vertrix_port_jpeg_use_merged_upsample_4c0b51(PORT_SIGNATURE)
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
