#include "port_rtlsessionstarts.h"

/* At 0x48cc30, the routine returns 0 when [edi+0x1bc] is null. */

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

/* A value pushed for the next call. */
static void push(Regs *r, uint32_t value)
{
    if (r->pushed < 32)
    {
        r->stack[r->pushed++] = value;
    }
}

/* The last count values pushed dropped (the caller's add esp). */
static void drop(Regs *r, unsigned count)
{
    r->pushed = count < r->pushed ? r->pushed - count : 0;
}

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

/* A cdecl call: every value pushed passed, left for the caller to drop. */
static void call_cdecl(Regs *r, uint32_t target)
{
    call_with_stack(r, target, r->pushed, 1);
}

static uint32_t rd8(Regs *r, uint32_t address)
{
    return port_u8(r->port, address, 0);
}

static uint32_t rd32(Regs *r, uint32_t address)
{
    return port_u32(r->port, address, 0);
}

static void wr32(Regs *r, uint32_t address, uint32_t value)
{
    port_set32(r->port, address, 0, value);
}

static void set_high8(uint32_t *reg, uint32_t value)
{
    *reg = (*reg & 0xffff00ffu) | ((value & 0xff) << 8);
}

/* The last value pushed taken back. */
static uint32_t pop(Regs *r)
{
    return r->pushed != 0 ? r->stack[--r->pushed] : 0;
}

/* An indirect call (an import or a method): every value pushed passed and popped, as stdcall. */
static void call_all(Regs *r, uint32_t target)
{
    call_with_stack(r, target, r->pushed, 0);
}

/* Original 0x48cc30: At 0x48cc30, the routine returns 0 when [edi+0x1bc] is null. Otherwise it gets
 * a connection buffer through vtable +0x28, retrying with a vertrix_port_get_memory (0x4c9ff0)
 * buffer when the result is 0x80158100. Bit 0 of buffer+4 chooses the path. The host path logs
 * 'HOST MANAGEMENT...' and creates the session and player. The client path logs 'CLIENT
 * MANAGEMENT...' and 'HOST ADDRESS :' (via 0x48ca20), enumerates sessions through [edi] vtable
 * +0x64, and joins through +0x18. Both paths call events_setup (0x48b7e0) and options_unpack
 * (0x48c610), and compare versions ('VERSIONS ERROR : SERVER (%s) CLIENT (%s)'). They return 1 on
 * success, and on failure they log one of the CAN'T CREATE/JOIN SESSION, PLAYER, GAME EVENTS, or
 * ENUM SESSIONS messages, or 'ERROR OF SESSION INFOS !...'. Evidence: calls 0x4ca040, 0x4c9ff0,
 * 0x4ca280, 0x4b76d0, 0x4ca210, 0x48c390, 0x48ca20, 0x47f190, 0x48b7e0, 0x48c610, 0x418150,
 * 0x4ca070, 0x418170, 0x4cdfb0, 0x4ca090, 0x48b970, 0x4cda10, 0x47f3d0, 0x48c3b0, 0x47f0f0; reads
 * 0x4f1b30, 0x4f172c, 0x4f1b48, 0x4f1c40, 0x4f1b2c, 0x4f7b40, 0x4f1cfc. Register-for-register from
 * the listing (0x48cc3b..0x48d31f); labels are the original addresses. */
static void run(Regs *r)
{
    r->edi = r->eax;
    r->eax = r->ebp - 0x88;
    r->edx = 0x4ec1ec;
    r->ecx = 0x517808;
    push(r, r->port->env.chain);
    wr32(r, r->eax, pop(r));
    r->port->env.chain = r->eax;
    r->ebx = 0;
    wr32(r, r->ebp - 0x84, r->edx);
    wr32(r, r->ebp - 0x80, r->ecx);
    wr32(r, r->ebp - 0x7c, r->ebx);
    if (rd32(r, r->edi + 0x1bc) != 0x0)
    {
        goto at_48cc8d;
    }
at_48cc73:
    r->edx = 0;
at_48cc75:
    r->eax = rd32(r, r->ebp - 0x88);
    r->port->env.chain = r->eax;
    r->eax = r->edx;
    r->edi = rd32(r, r->ebp - 0x14);
    r->esi = rd32(r, r->ebp - 0x10);
    r->edx = rd32(r, r->ebp - 0xc);
    r->ecx = rd32(r, r->ebp - 0x8);
    r->ebx = rd32(r, r->ebp - 0x4);
    return;
at_48cc8d:
    push(r, r->ebx);
    r->edx = r->ebp - 0x74;
    push(r, r->edx);
    wr32(r, r->ebp - 0x74, r->ebx);
    push(r, r->ebx);
    r->edx = rd32(r, r->edi + 0x1c0);
    r->eax = rd32(r, r->edi + 0x1bc);
    push(r, r->edx);
    r->ecx = rd32(r, r->eax);
    push(r, r->eax);
    r->esi = 0;
    call_all(r, rd32(r, r->ecx + 0x28));
    wr32(r, r->ebp - 0x28, r->eax);
    if (r->eax == 0x80158100u)
    {
        goto at_48cd32;
    }
at_48ccb9:
    if (r->esi == 0)
    {
        goto at_48cd0b;
    }
    r->ebx = rd32(r, r->esi + 0x50);
    if (r->ebx == 0)
    {
        goto at_48ccd1;
    }
    push(r, r->ebx);
    r->edx = rd32(r, r->ebx);
    call_all(r, rd32(r, r->edx + 0x8));
    wr32(r, r->esi + 0x50, 0x0);
at_48ccd1:
    r->eax = 0;
    r->edx = rd32(r, r->esi + 0x58);
    wr32(r, r->ebp - 0x18, r->eax);
    if (r->edx == 0)
    {
        goto at_48cd0b;
    }
    r->ebx = 0;
at_48ccdf:
    r->eax = rd32(r, r->esi + 0x54);
    r->eax = r->eax + r->ebx;
    r->ecx = rd32(r, r->eax);
    if (r->ecx == 0)
    {
        goto at_48ccfa;
    }
    push(r, r->ecx);
    r->edx = rd32(r, r->ecx);
    call_all(r, rd32(r, r->edx + 0x8));
    r->eax = rd32(r, r->esi + 0x54);
    wr32(r, r->ebx + r->eax, 0x0);
at_48ccfa:
    r->ecx = rd32(r, r->ebp - 0x18);
    r->ebx = r->ebx + 0x4;
    r->ecx = r->ecx + 1;
    r->edx = rd32(r, r->esi + 0x58);
    wr32(r, r->ebp - 0x18, r->ecx);
    if (r->ecx < r->edx && !r->port->env.failed)
    {
        goto at_48ccdf;
    }
at_48cd0b:
    if (r->esi == 0)
    {
        goto at_48cd16;
    }
    r->eax = r->esi;
    call(r, 0x4ca040, 0);
at_48cd16:
    r->ebx = rd32(r, r->ebp - 0x28);
    wr32(r, r->edi + 0x14, 0x0);
    if ((int32_t)r->ebx < 0 && !r->port->env.failed)
    {
        goto at_48cc73;
    }
    r->edx = 0x1;
    if (r->port->env.failed)
    {
        return;
    }
    goto at_48cc75;
at_48cd32:
    r->eax = rd32(r, r->ebp - 0x74);
    call(r, 0x4c9ff0, 0);
    r->ebx = r->eax;
    r->esi = r->eax;
    if (r->eax != 0)
    {
        goto at_48cd4e;
    }
    wr32(r, r->ebp - 0x28, 0x80004005u);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_48ccb9;
at_48cd4e:
    push(r, 0x0);
    r->edx = r->ebp - 0x74;
    push(r, r->edx);
    push(r, r->ebx);
    r->edx = rd32(r, r->edi + 0x1c0);
    r->eax = rd32(r, r->edi + 0x1bc);
    push(r, r->edx);
    r->ecx = rd32(r, r->eax);
    push(r, r->eax);
    call_all(r, rd32(r, r->ecx + 0x28));
    wr32(r, r->ebp - 0x28, r->eax);
    if ((int32_t)r->eax < 0 && !r->port->env.failed)
    {
        goto at_48ccb9;
    }
    r->ecx = 0x80004005u;
    set_high8(&r->eax, rd8(r, r->ebx + 0x4));
    wr32(r, r->ebp - 0x28, r->ecx);
    if ((uint8_t)(((r->eax >> 8) & 0xff) & 0x1) != 0)
    {
        goto at_48d054;
    }
    r->edx = 0x510f85;
    r->eax = r->ebp - 0x5c;
    call(r, 0x4ca280, 0);
    wr32(r, r->ebp - 0x7c, 0xb);
    r->edx = r->eax;
    r->eax = 0x532c24;
    r->ecx = 0;
    call(r, 0x4b76d0, 0);
    r->eax = r->ebp - 0x5c;
    r->edx = 0;
    wr32(r, r->ebp - 0x7c, r->ecx);
    call(r, 0x4ca210, 0);
    r->eax = 0x5bb254;
    wr32(r, r->ebp - 0x7c, r->ecx);
    call(r, 0x48c390, 0);
    if (r->eax != 0x1)
    {
        goto at_48d2ea;
    }
    r->edx = 0x510faf;
    wr32(r, r->ebp - 0x2c, r->eax);
    r->eax = r->ebp - 0x58;
    call(r, 0x4ca280, 0);
    wr32(r, r->ebp - 0x7c, 0xd);
    r->edx = r->eax;
    r->eax = 0x532c24;
    call(r, 0x4b76d0, 0);
    r->eax = r->ebp - 0x58;
    r->edx = 0;
    wr32(r, r->ebp - 0x7c, r->ecx);
    call(r, 0x4ca210, 0);
    wr32(r, r->ebp - 0x7c, r->ecx);
    r->eax = r->edi;
    r->edx = rd32(r, r->ebx + 0x50);
    call(r, 0x48ca20, 0);
    push(r, 0x0);
    r->edx = r->edi + 0x10;
    push(r, r->edx);
    push(r, 0x0);
    push(r, 0xffffffffu);
    push(r, 0x0);
    push(r, 0x4);
    push(r, 0x0);
    r->edx = rd32(r, r->ebx + 0x54);
    push(r, 0x0);
    push(r, rd32(r, r->edx));
    r->edx = rd32(r, r->ebx + 0x50);
    push(r, r->edx);
    r->ebx = r->ebx + 0x8;
    r->eax = rd32(r, r->edi);
    push(r, r->ebx);
    r->ecx = rd32(r, r->eax);
    push(r, r->eax);
    call_all(r, rd32(r, r->ecx + 0x64));
    if (r->eax != 0x15800e)
    {
        goto at_48d1d8;
    }
at_48ce3b:
    push(r, 0x0);
    push(r, 0x0);
    push(r, 0x1);
    push(r, 0x0);
    call_all(r, rd32(r, 0x4f1b30));
    wr32(r, r->ebp - 0x1c, r->eax);
    call_all(r, rd32(r, 0x4f172c));
    wr32(r, r->ebp - 0x24, r->eax);
at_48ce57:
    push(r, 0x558c9c);
    call_all(r, rd32(r, 0x4f1b48));
    r->eax = r->edi;
    r->edx = 0;
    call(r, 0x47f190, 0);
    push(r, 0x558c9c);
    r->ebx = r->eax;
    wr32(r, r->ebp - 0x20, r->eax);
    call_all(r, rd32(r, 0x4f1c40));
    if (r->ebx == 0)
    {
        goto at_48d1e5;
    }
at_48ce85:
    r->ebx = rd32(r, r->ebp - 0x1c);
    push(r, r->ebx);
    call_all(r, rd32(r, 0x4f1b2c));
    if (rd32(r, r->ebp - 0x20) == 0x0)
    {
        goto at_48cff9;
    }
    push(r, 0x558c9c);
    call_all(r, rd32(r, 0x4f1b48));
    r->eax = r->edi;
    r->edx = 0;
    call(r, 0x47f190, 0);
    if (r->eax == 0)
    {
        goto at_48cfed;
    }
    r->edx = 0;
    wr32(r, r->ebp - 0x54, r->edx);
    r->edx = r->ebp - 0x54;
    r->eax = rd32(r, r->eax + 0x48);
    push(r, r->edx);
    r->ecx = rd32(r, r->eax);
    push(r, r->eax);
    call_all(r, rd32(r, r->ecx + 0x14));
    if ((int32_t)r->eax < 0)
    {
        goto at_48cfed;
    }
    push(r, 0x80000000u);
    push(r, 0x0);
    push(r, 0x0);
    push(r, 0x0);
    push(r, 0x0);
    push(r, 0x0);
    push(r, 0x0);
    r->edx = rd32(r, r->esi + 0x54);
    push(r, 0x0);
    r->ebx = rd32(r, r->edx);
    push(r, r->ebx);
    r->edx = rd32(r, r->ebp - 0x54);
    r->eax = rd32(r, r->edi);
    push(r, r->edx);
    r->edx = r->esi + 0x8;
    r->ecx = 0;
    push(r, r->edx);
    wr32(r, r->ebp - 0x2c, r->ecx);
    r->ecx = rd32(r, r->eax);
    push(r, r->eax);
    call_all(r, rd32(r, r->ecx + 0x18));
    if ((int32_t)r->eax < 0)
    {
        goto at_48d295;
    }
    r->eax = 0x5bb254;
    wr32(r, r->edi + 0x30, 0x0);
    call(r, 0x48b7e0, 0);
    if (r->eax != 0x1)
    {
        goto at_48d25e;
    }
    r->eax = 0x5bb254;
    call(r, 0x48c610, 0);
    if (r->eax != 0x1)
    {
        goto at_48d21a;
    }
    r->ecx = rd32(r, 0x4f7b40);
    r->ebx = rd32(r, r->edi + 0x24);
    r->edx = r->ecx;
    r->eax = r->ebx;
    call(r, 0x418150, 0);
    if (r->eax == 0)
    {
        goto at_48d20c;
    }
    r->eax = r->ebp - 0x50;
    call(r, 0x4ca070, 0);
    r->eax = 0xf;
    r->edx = r->ebx;
    wr32(r, r->ebp - 0x7c, r->eax);
    r->eax = r->ebp - 0x4c;
    call(r, 0x418170, 0);
    r->edx = 0x10;
    r->eax = r->ebp - 0x48;
    wr32(r, r->ebp - 0x7c, r->edx);
    r->edx = r->ecx;
    call(r, 0x418170, 0);
    r->ebx = rd32(r, r->ebp - 0x48);
    push(r, r->ebx);
    r->eax = rd32(r, r->ebp - 0x4c);
    push(r, r->eax);
    push(r, 0x510fcd);
    r->eax = r->ebp - 0x50;
    r->ecx = 0x11;
    push(r, r->eax);
    wr32(r, r->ebp - 0x7c, r->ecx);
    call_cdecl(r, 0x4cdfb0);
    drop(r, 4);
    r->edx = r->ebp - 0x50;
    r->eax = r->ebp - 0x44;
    call(r, 0x4ca090, 0);
    wr32(r, r->ebp - 0x7c, 0x12);
    r->edx = r->eax;
    r->eax = 0x532c24;
    call(r, 0x4b76d0, 0);
    r->eax = r->ebp - 0x44;
    r->edx = 0;
    wr32(r, r->ebp - 0x7c, r->ecx);
    call(r, 0x4ca210, 0);
    r->eax = 0x5bb254;
    wr32(r, r->ebp - 0x7c, r->ecx);
    call(r, 0x48b970, 0);
    call(r, 0x4cda10, 0);
at_48cfd8:
    r->eax = rd32(r, r->ebp - 0x54);
    if (r->eax == 0)
    {
        goto at_48cfed;
    }
    r->edx = rd32(r, r->ebp - 0x54);
    r->eax = rd32(r, r->eax);
    push(r, r->edx);
    call_all(r, rd32(r, r->eax + 0x8));
    r->ecx = 0;
    wr32(r, r->ebp - 0x54, r->ecx);
at_48cfed:
    push(r, 0x558c9c);
    call_all(r, rd32(r, 0x4f1c40));
at_48cff9:
    if (rd32(r, r->ebp - 0x2c) != 0x1)
    {
        goto at_48d031;
    }
    r->edx = 0x51104c;
    r->eax = r->ebp - 0x34;
    call(r, 0x4ca280, 0);
    wr32(r, r->ebp - 0x7c, 0x1a);
    r->edx = r->eax;
    r->eax = 0x532c24;
    r->ecx = 0;
    call(r, 0x4b76d0, 0);
    r->eax = r->ebp - 0x34;
    r->edx = 0;
    wr32(r, r->ebp - 0x7c, r->ecx);
    call(r, 0x4ca210, 0);
    wr32(r, r->ebp - 0x7c, r->ecx);
at_48d031:
    if (rd32(r, r->ebp - 0x28) == 0x0)
    {
        goto at_48d2d4;
    }
    r->eax = 0x5bb254;
    call(r, 0x47f3d0, 0);
    r->edx = 0;
    wr32(r, r->ebp - 0x7c, r->edx);
    r->ecx = 0;
    wr32(r, r->ebp - 0x7c, r->ecx);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_48ccb9;
at_48d054:
    r->edx = 0x510eea;
    r->eax = r->ebp - 0x70;
    r->ecx = 0x1;
    call(r, 0x4ca280, 0);
    r->edx = r->eax;
    r->eax = 0x532c24;
    wr32(r, r->ebp - 0x7c, r->ecx);
    call(r, 0x4b76d0, 0);
    r->eax = 0;
    r->edx = 0;
    wr32(r, r->ebp - 0x7c, r->eax);
    r->eax = r->ebp - 0x70;
    call(r, 0x4ca210, 0);
    r->edx = 0;
    r->eax = 0x5bb254;
    wr32(r, r->ebp - 0x7c, r->edx);
    call(r, 0x48c3b0, 0);
    if (r->eax != r->ecx)
    {
        goto at_48d19b;
    }
    r->edx = rd32(r, r->edi + 0x1c8);
    r->eax = r->edi;
    wr32(r, r->edi + 0x14, r->ebx);
    call_all(r, rd32(r, r->edx + 0x44));
    if (r->eax != r->ecx)
    {
        goto at_48d15f;
    }
    r->eax = 0x5bb254;
    call(r, 0x48b7e0, 0);
    if (r->eax != r->ecx)
    {
        goto at_48d123;
    }
    r->eax = 0x5bb254;
    call(r, 0x48c610, 0);
    if (r->eax != r->ecx)
    {
        goto at_48d0e2;
    }
    r->edx = 0;
    wr32(r, r->edi + 0xb4, r->ecx);
    wr32(r, r->ebp - 0x28, r->edx);
at_48d0d8:
    r->ecx = 0;
    wr32(r, r->ebp - 0x7c, r->ecx);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_48ccb9;
at_48d0e2:
    r->edx = 0x510f10;
    r->eax = r->ebp - 0x6c;
    call(r, 0x4ca280, 0);
    wr32(r, r->ebp - 0x7c, 0x3);
    r->edx = r->eax;
    r->eax = 0x532c24;
    r->ecx = 0;
    call(r, 0x4b76d0, 0);
    r->eax = r->ebp - 0x6c;
    r->edx = 0;
    wr32(r, r->ebp - 0x7c, r->ecx);
    call(r, 0x4ca210, 0);
    r->eax = 0x5bb254;
    wr32(r, r->ebp - 0x7c, r->ecx);
    call(r, 0x48b970, 0);
    wr32(r, r->ebp - 0x7c, r->ecx);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_48d0d8;
at_48d123:
    r->edx = 0x510f2c;
    r->eax = r->ebp - 0x68;
    call(r, 0x4ca280, 0);
    wr32(r, r->ebp - 0x7c, 0x5);
    r->edx = r->eax;
    r->eax = 0x532c24;
    r->ecx = 0;
    call(r, 0x4b76d0, 0);
    r->eax = r->ebp - 0x68;
    r->edx = 0;
    wr32(r, r->ebp - 0x7c, r->ecx);
    call(r, 0x4ca210, 0);
    wr32(r, r->ebp - 0x7c, r->ecx);
    r->ecx = 0;
    wr32(r, r->ebp - 0x7c, r->ecx);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_48ccb9;
at_48d15f:
    r->edx = 0x510f4a;
    r->eax = r->ebp - 0x64;
    call(r, 0x4ca280, 0);
    wr32(r, r->ebp - 0x7c, 0x7);
    r->edx = r->eax;
    r->eax = 0x532c24;
    r->ecx = 0;
    call(r, 0x4b76d0, 0);
    r->eax = r->ebp - 0x64;
    r->edx = 0;
    wr32(r, r->ebp - 0x7c, r->ecx);
    call(r, 0x4ca210, 0);
    wr32(r, r->ebp - 0x7c, r->ecx);
    r->ecx = 0;
    wr32(r, r->ebp - 0x7c, r->ecx);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_48ccb9;
at_48d19b:
    r->edx = 0x510f68;
    r->eax = r->ebp - 0x60;
    r->ecx = 0x9;
    call(r, 0x4ca280, 0);
    r->ebx = 0;
    r->edx = r->eax;
    r->eax = 0x532c24;
    wr32(r, r->ebp - 0x7c, r->ecx);
    call(r, 0x4b76d0, 0);
    r->eax = r->ebp - 0x60;
    r->edx = 0;
    wr32(r, r->ebp - 0x7c, r->ebx);
    call(r, 0x4ca210, 0);
    wr32(r, r->ebp - 0x7c, r->ebx);
    r->ecx = 0;
    wr32(r, r->ebp - 0x7c, r->ecx);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_48ccb9;
at_48d1d8:
    if ((int32_t)r->eax >= 0 && !r->port->env.failed)
    {
        goto at_48ce3b;
    }
    if (r->port->env.failed)
    {
        return;
    }
    goto at_48cff9;
at_48d1e5:
    call_all(r, rd32(r, 0x4f172c));
    r->eax = r->eax - rd32(r, r->ebp - 0x24);
    if (r->eax >= 0x2710 && !r->port->env.failed)
    {
        goto at_48ce85;
    }
    push(r, 0x64);
    r->ecx = rd32(r, r->ebp - 0x1c);
    push(r, r->ecx);
    call_all(r, rd32(r, 0x4f1cfc));
    if (r->port->env.failed)
    {
        return;
    }
    goto at_48ce57;
at_48d20c:
    wr32(r, r->ebp - 0x28, r->eax);
    wr32(r, r->edi + 0xb4, r->eax);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_48cfd8;
at_48d21a:
    r->edx = 0x510ff6;
    r->eax = r->ebp - 0x40;
    call(r, 0x4ca280, 0);
    wr32(r, r->ebp - 0x7c, 0x14);
    r->edx = r->eax;
    r->eax = 0x532c24;
    r->ecx = 0;
    call(r, 0x4b76d0, 0);
    r->eax = r->ebp - 0x40;
    r->edx = 0;
    wr32(r, r->ebp - 0x7c, r->ecx);
    call(r, 0x4ca210, 0);
    r->eax = 0x5bb254;
    wr32(r, r->ebp - 0x7c, r->ecx);
    call(r, 0x48b970, 0);
    wr32(r, r->ebp - 0x7c, r->ecx);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_48cfd8;
at_48d25e:
    r->edx = 0x511012;
    r->eax = r->ebp - 0x3c;
    call(r, 0x4ca280, 0);
    wr32(r, r->ebp - 0x7c, 0x16);
    r->edx = r->eax;
    r->eax = 0x532c24;
    r->ecx = 0;
    call(r, 0x4b76d0, 0);
    r->eax = r->ebp - 0x3c;
    r->edx = 0;
    wr32(r, r->ebp - 0x7c, r->ecx);
    call(r, 0x4ca210, 0);
    wr32(r, r->ebp - 0x7c, r->ecx);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_48cfd8;
at_48d295:
    r->edx = 0x511030;
    r->eax = r->ebp - 0x38;
    r->ecx = 0x18;
    wr32(r, r->edi + 0x30, 0x1);
    call(r, 0x4ca280, 0);
    r->ebx = 0;
    r->edx = r->eax;
    r->eax = 0x532c24;
    wr32(r, r->ebp - 0x7c, r->ecx);
    call(r, 0x4b76d0, 0);
    r->eax = r->ebp - 0x38;
    r->edx = 0;
    wr32(r, r->ebp - 0x7c, r->ebx);
    call(r, 0x4ca210, 0);
    wr32(r, r->ebp - 0x7c, r->ebx);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_48cfd8;
at_48d2d4:
    r->eax = r->edi;
    call(r, 0x47f0f0, 0);
    r->edx = 0;
    wr32(r, r->ebp - 0x7c, r->edx);
    r->ecx = 0;
    wr32(r, r->ebp - 0x7c, r->ecx);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_48ccb9;
at_48d2ea:
    r->edx = 0x511065;
    r->eax = r->ebp - 0x30;
    call(r, 0x4ca280, 0);
    wr32(r, r->ebp - 0x7c, 0x1c);
    r->edx = r->eax;
    r->eax = 0x532c24;
    call(r, 0x4b76d0, 0);
    r->eax = r->ebp - 0x30;
    r->edx = 0;
    wr32(r, r->ebp - 0x7c, r->ecx);
    call(r, 0x4ca210, 0);
    wr32(r, r->ebp - 0x7c, r->ecx);
    r->ecx = 0;
    wr32(r, r->ebp - 0x7c, r->ecx);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_48ccb9;
}

uint32_t vertrix_port_network_session_start_48cc30(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x8c
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
