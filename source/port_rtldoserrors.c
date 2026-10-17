#include "port_rtldoserrors.h"

/* Maps a Windows error code (the stack argument) to the C runtime errno value. */

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

/* Original 0x4d9ae0: Maps a Windows error code (the stack argument) to the C runtime errno value.
 * Evidence: no calls. Register-for-register from the listing (0x4d9ae0..0x4d9f05); labels are the
 * original addresses. */
static void run(Regs *r)
{
    r->edx = rd32(r, r->esp + 0x4);
    r->eax = r->edx;
    flags(r, F_SUB, r->edx, 0x41, 32);
    if (cond(r, CC_B))
    {
        goto at_4d9d50;
    }
    if (cond(r, CC_BE))
    {
        goto at_4d9b48;
    }
    flags(r, F_SUB, r->edx, 0x7d, 32);
    if (cond(r, CC_B))
    {
        goto at_4d9c6a;
    }
    if (cond(r, CC_BE))
    {
        goto at_4d9b40;
    }
    flags(r, F_SUB, r->edx, 0xb7, 32);
    if (cond(r, CC_B))
    {
        goto at_4d9bd4;
    }
    if (cond(r, CC_BE))
    {
        goto at_4d9b48;
    }
    flags(r, F_SUB, r->edx, 0x10b, 32);
    if (cond(r, CC_B))
    {
        goto at_4d9ba0;
    }
    if (cond(r, CC_BE))
    {
        goto at_4d9b40;
    }
    flags(r, F_SUB, r->edx, 0x3e4, 32);
    if (cond(r, CC_B))
    {
        goto at_4d9b90;
    }
    if (cond(r, CC_BE))
    {
        goto at_4d9b60;
    }
    if (r->edx <= 0x3e5)
    {
        goto at_4d9b60;
    }
    if (r->edx == 0x3e7)
    {
        goto at_4d9b48;
    }
    goto at_4d9b88;
at_4d9b38:
    r->eax = 0x2;
    return;
at_4d9b40:
    r->eax = 0x3;
    return;
at_4d9b48:
    r->eax = 0x5;
    return;
at_4d9b50:
    r->eax = 0x6;
    return;
at_4d9b58:
    r->eax = 0x7;
    return;
at_4d9b60:
    r->eax = 0xa;
    return;
at_4d9b68:
    r->eax = 0xb;
    return;
at_4d9b70:
    r->eax = 0xc;
    return;
at_4d9b78:
    r->eax = 0xe;
    return;
at_4d9b80:
    r->eax = 0x8;
    return;
at_4d9b88:
    r->eax = 0x1;
    return;
at_4d9b90:
    if (r->edx == 0x3e3 && !r->port->env.failed)
    {
        goto at_4d9b60;
    }
    r->eax = 0x1;
    return;
at_4d9ba0:
    flags(r, F_SUB, r->edx, 0xc1, 32);
    if (cond(r, CC_B))
    {
        goto at_4d9bc4;
    }
    if (cond(r, CC_BE) && !r->port->env.failed)
    {
        goto at_4d9b50;
    }
    flags(r, F_SUB, r->edx, 0xce, 32);
    if (cond(r, CC_B) && !r->port->env.failed)
    {
        goto at_4d9b88;
    }
    if (cond(r, CC_BE) && !r->port->env.failed)
    {
        goto at_4d9b40;
    }
    if (r->edx == 0xd0 && !r->port->env.failed)
    {
        goto at_4d9b40;
    }
    r->eax = 0x1;
    return;
at_4d9bc4:
    if (r->edx == 0xbf && !r->port->env.failed)
    {
        goto at_4d9b50;
    }
    r->eax = 0x1;
    return;
at_4d9bd4:
    flags(r, F_SUB, r->edx, 0x9a, 32);
    if (cond(r, CC_B))
    {
        goto at_4d9c22;
    }
    if (cond(r, CC_BE) && !r->port->env.failed)
    {
        goto at_4d9b40;
    }
    flags(r, F_SUB, r->edx, 0xa7, 32);
    if (cond(r, CC_B))
    {
        goto at_4d9c0e;
    }
    if (cond(r, CC_BE) && !r->port->env.failed)
    {
        goto at_4d9b70;
    }
    flags(r, F_SUB, r->edx, 0xaa, 32);
    if (cond(r, CC_B) && !r->port->env.failed)
    {
        goto at_4d9b88;
    }
    if (cond(r, CC_BE) && !r->port->env.failed)
    {
        goto at_4d9b48;
    }
    if (r->edx == 0xb6 && !r->port->env.failed)
    {
        goto at_4d9b50;
    }
    r->eax = 0x1;
    return;
at_4d9c0e:
    if (r->edx == 0xa1 && !r->port->env.failed)
    {
        goto at_4d9b40;
    }
    r->eax = 0x1;
    return;
at_4d9c22:
    flags(r, F_SUB, r->edx, 0x84, 32);
    if (cond(r, CC_B))
    {
        goto at_4d9c56;
    }
    if (cond(r, CC_BE))
    {
        goto at_4d9e6a;
    }
    flags(r, F_SUB, r->edx, 0x90, 32);
    if (cond(r, CC_B) && !r->port->env.failed)
    {
        goto at_4d9b88;
    }
    if (cond(r, CC_BE) && !r->port->env.failed)
    {
        goto at_4d9b40;
    }
    if (r->edx == 0x91 && !r->port->env.failed)
    {
        goto at_4d9b58;
    }
    r->eax = 0x1;
    return;
at_4d9c56:
    if (r->edx == 0x83)
    {
        goto at_4d9e6a;
    }
    r->eax = 0x1;
    return;
at_4d9c6a:
    flags(r, F_SUB, r->edx, 0x58, 32);
    if (cond(r, CC_B))
    {
        goto at_4d9ce0;
    }
    if (cond(r, CC_BE) && !r->port->env.failed)
    {
        goto at_4d9b60;
    }
    flags(r, F_SUB, r->edx, 0x71, 32);
    if (cond(r, CC_B))
    {
        goto at_4d9cad;
    }
    if (cond(r, CC_BE))
    {
        goto at_4d9ee7;
    }
    flags(r, F_SUB, r->edx, 0x75, 32);
    if (cond(r, CC_B))
    {
        goto at_4d9c9c;
    }
    if (cond(r, CC_BE) && !r->port->env.failed)
    {
        goto at_4d9b60;
    }
    if (r->edx < 0x7b && !r->port->env.failed)
    {
        goto at_4d9b88;
    }
    r->eax = 0x3;
    return;
at_4d9c9c:
    if (r->edx == 0x72 && !r->port->env.failed)
    {
        goto at_4d9b50;
    }
    r->eax = 0x1;
    return;
at_4d9cad:
    flags(r, F_SUB, r->edx, 0x6c, 32);
    if (cond(r, CC_B))
    {
        goto at_4d9ccf;
    }
    if (cond(r, CC_BE) && !r->port->env.failed)
    {
        goto at_4d9b70;
    }
    flags(r, F_SUB, r->edx, 0x6f, 32);
    if (cond(r, CC_B) && !r->port->env.failed)
    {
        goto at_4d9b88;
    }
    if (cond(r, CC_BE) && !r->port->env.failed)
    {
        goto at_4d9b40;
    }
at_4d9cc7:
    r->eax = 0xd;
    return;
at_4d9ccf:
    if (r->edx == 0x6b && !r->port->env.failed)
    {
        goto at_4d9b38;
    }
    r->eax = 0x1;
    return;
at_4d9ce0:
    flags(r, F_SUB, r->edx, 0x47, 32);
    if (cond(r, CC_B))
    {
        goto at_4d9d27;
    }
    if (cond(r, CC_BE) && !r->port->env.failed)
    {
        goto at_4d9b48;
    }
    flags(r, F_SUB, r->edx, 0x52, 32);
    if (cond(r, CC_B))
    {
        goto at_4d9d16;
    }
    if (cond(r, CC_BE) && !r->port->env.failed)
    {
        goto at_4d9b48;
    }
    flags(r, F_SUB, r->edx, 0x55, 32);
    if (cond(r, CC_B) && !r->port->env.failed)
    {
        goto at_4d9b88;
    }
    if (cond(r, CC_BE) && !r->port->env.failed)
    {
        goto at_4d9b40;
    }
    if (r->edx == 0x56 && !r->port->env.failed)
    {
        goto at_4d9b48;
    }
    r->eax = 0x1;
    return;
at_4d9d16:
    if (r->edx == 0x50 && !r->port->env.failed)
    {
        goto at_4d9b48;
    }
    r->eax = 0x1;
    return;
at_4d9d27:
    flags(r, F_SUB, r->edx, 0x43, 32);
    if (cond(r, CC_B) && !r->port->env.failed)
    {
        goto at_4d9b50;
    }
    if (cond(r, CC_BE) && !r->port->env.failed)
    {
        goto at_4d9b40;
    }
    if (r->edx <= 0x44)
    {
        goto at_4d9ee7;
    }
    if (r->edx == 0x46 && !r->port->env.failed)
    {
        goto at_4d9b40;
    }
    r->eax = 0x1;
    return;
at_4d9d50:
    flags(r, F_SUB, r->edx, 0x1a, 32);
    if (cond(r, CC_B))
    {
        goto at_4d9e42;
    }
    if (cond(r, CC_BE) && !r->port->env.failed)
    {
        goto at_4d9b50;
    }
    flags(r, F_SUB, r->edx, 0x34, 32);
    if (cond(r, CC_B))
    {
        goto at_4d9dcd;
    }
    if (cond(r, CC_BE) && !r->port->env.failed)
    {
        goto at_4d9b40;
    }
    flags(r, F_SUB, r->edx, 0x3a, 32);
    if (cond(r, CC_B))
    {
        goto at_4d9da4;
    }
    if (cond(r, CC_BE) && !r->port->env.failed)
    {
        goto at_4d9b48;
    }
    flags(r, F_SUB, r->edx, 0x3c, 32);
    if (cond(r, CC_B) && !r->port->env.failed)
    {
        goto at_4d9b60;
    }
    if (cond(r, CC_BE) && !r->port->env.failed)
    {
        goto at_4d9b50;
    }
    flags(r, F_SUB, r->edx, 0x3e, 32);
    if (cond(r, CC_B) && !r->port->env.failed)
    {
        goto at_4d9b88;
    }
    if (cond(r, CC_BE) && !r->port->env.failed)
    {
        goto at_4d9b80;
    }
    if (r->edx == 0x40 && !r->port->env.failed)
    {
        goto at_4d9b48;
    }
    r->eax = 0x1;
    return;
at_4d9da4:
    flags(r, F_SUB, r->edx, 0x36, 32);
    if (cond(r, CC_B) && !r->port->env.failed)
    {
        goto at_4d9b40;
    }
    if (cond(r, CC_BE) && !r->port->env.failed)
    {
        goto at_4d9b48;
    }
    if (r->edx <= 0x37 && !r->port->env.failed)
    {
        goto at_4d9b40;
    }
    if (r->edx == 0x39 && !r->port->env.failed)
    {
        goto at_4d9b60;
    }
    r->eax = 0x1;
    return;
at_4d9dcd:
    flags(r, F_SUB, r->edx, 0x21, 32);
    if (cond(r, CC_B))
    {
        goto at_4d9e14;
    }
    if (cond(r, CC_BE) && !r->port->env.failed)
    {
        goto at_4d9b70;
    }
    flags(r, F_SUB, r->edx, 0x24, 32);
    if (cond(r, CC_B))
    {
        goto at_4d9e03;
    }
    if (cond(r, CC_BE))
    {
        goto at_4d9ee7;
    }
    flags(r, F_SUB, r->edx, 0x26, 32);
    if (cond(r, CC_B) && !r->port->env.failed)
    {
        goto at_4d9b88;
    }
    if (cond(r, CC_BE) && !r->port->env.failed)
    {
        goto at_4d9b78;
    }
    if (r->edx == 0x27 && !r->port->env.failed)
    {
        goto at_4d9cc7;
    }
    r->eax = 0x1;
    return;
at_4d9e03:
    if (r->edx == 0x22 && !r->port->env.failed)
    {
        goto at_4d9b40;
    }
    r->eax = 0x1;
    return;
at_4d9e14:
    flags(r, F_SUB, r->edx, 0x1d, 32);
    if (cond(r, CC_B))
    {
        goto at_4d9e35;
    }
    if (cond(r, CC_BE) && !r->port->env.failed)
    {
        goto at_4d9b48;
    }
    if (r->edx <= 0x1e)
    {
        goto at_4d9e6a;
    }
    if (r->edx == 0x20 && !r->port->env.failed)
    {
        goto at_4d9b68;
    }
    r->eax = 0x1;
    return;
at_4d9e35:
    if (r->edx == 0x1b)
    {
        goto at_4d9e6a;
    }
    r->eax = 0x1;
    return;
at_4d9e42:
    flags(r, F_SUB, r->edx, 0x10, 32);
    if (cond(r, CC_B))
    {
        goto at_4d9e92;
    }
    if (cond(r, CC_BE) && !r->port->env.failed)
    {
        goto at_4d9b58;
    }
    flags(r, F_SUB, r->edx, 0x15, 32);
    if (cond(r, CC_B))
    {
        goto at_4d9e72;
    }
    if (cond(r, CC_BE) && !r->port->env.failed)
    {
        goto at_4d9b60;
    }
    flags(r, F_SUB, r->edx, 0x17, 32);
    if (cond(r, CC_B) && !r->port->env.failed)
    {
        goto at_4d9b60;
    }
    if (cond(r, CC_BE) && !r->port->env.failed)
    {
        goto at_4d9b60;
    }
at_4d9e6a:
    r->eax = 0x9;
    return;
at_4d9e72:
    flags(r, F_SUB, r->edx, 0x12, 32);
    if (cond(r, CC_B) && !r->port->env.failed)
    {
        goto at_4d9b40;
    }
    if (cond(r, CC_BE) && !r->port->env.failed)
    {
        goto at_4d9b38;
    }
    if (r->edx <= 0x13 && !r->port->env.failed)
    {
        goto at_4d9b48;
    }
    r->eax = 0xa;
    return;
at_4d9e92:
    flags(r, F_SUB, r->edx, 0x5, 32);
    if (cond(r, CC_B))
    {
        goto at_4d9ed3;
    }
    if (cond(r, CC_BE) && !r->port->env.failed)
    {
        goto at_4d9b48;
    }
    flags(r, F_SUB, r->edx, 0xb, 32);
    if (cond(r, CC_B))
    {
        goto at_4d9ec2;
    }
    if (cond(r, CC_BE) && !r->port->env.failed)
    {
        goto at_4d9b50;
    }
    if (r->edx <= 0xc && !r->port->env.failed)
    {
        goto at_4d9b48;
    }
    if (r->edx == 0xf && !r->port->env.failed)
    {
        goto at_4d9b40;
    }
    r->eax = 0x1;
    return;
at_4d9ec2:
    if (r->edx == 0x6 && !r->port->env.failed)
    {
        goto at_4d9b38;
    }
    r->eax = 0x1;
    return;
at_4d9ed3:
    flags(r, F_SUB, r->edx, 0x2, 32);
    if (cond(r, CC_B))
    {
        goto at_4d9eef;
    }
    if (cond(r, CC_BE) && !r->port->env.failed)
    {
        goto at_4d9b38;
    }
    if (r->edx <= 0x3 && !r->port->env.failed)
    {
        goto at_4d9b40;
    }
at_4d9ee7:
    r->eax = 0x4;
    return;
at_4d9eef:
    if (r->edx != 0 && !r->port->env.failed)
    {
        goto at_4d9b88;
    }
    return;
    wr8(r, r->eax, rd8(r, r->eax) + (r->eax & 0xff));
    wr8(r, r->eax, rd8(r, r->eax) + (r->eax & 0xff));
    wr8(r, r->eax, rd8(r, r->eax) + (r->eax & 0xff));
    r->eax = 0x5051a8;
    return;
}

uint32_t vertrix_port_rtl_dos_error_to_errno_4d9ae0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x10
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
