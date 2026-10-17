#include "port_rtlgameloops.h"

/* Runs the game screen loop: frame timing, the game keys, pause, the options panel and the per-slot
 * input and menu handling until the screen ends. */

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

static void set_high8(uint32_t *reg, uint32_t value)
{
    *reg = (*reg & 0xffff00ffu) | ((value & 0xff) << 8);
}

static void set_low16(uint32_t *reg, uint32_t value)
{
    *reg = (*reg & 0xffff0000u) | (value & 0xffff);
}

static void div32(Regs *r, uint32_t value)
{
    LiftFlags flags;
    memset(&flags, 0, sizeof flags);
    lift_div1(32, value, &r->eax, &r->edx, &flags);
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

static void call_mem(Regs *r, uint32_t target, unsigned count)
{
    call_mem_with(r, target, count, 0);
}

static void call_mem_keep(Regs *r, uint32_t target, unsigned count)
{
    call_mem_with(r, target, count, 1);
}

/* Original 0x424990: Runs the game screen loop: frame timing, the game keys, pause, the options
 * panel and the per-slot input and menu handling until the screen ends. Evidence: calls 0x41d640,
 * 0x4b7cd0, 0x425ae0, 0x4b7d10, 0x41d670, 0x41df00, 0x4ac1c0, 0x471a70, 0x471b80, 0x472d90,
 * 0x471a60, 0x4854a0, 0x471a20, 0x471a40, 0x485520, 0x41aaf0, 0x486d00, 0x471a50, 0x471ba0,
 * 0x41d6d0, 0x41dd60, 0x486da0, 0x487020, 0x41d660 and 35 more; reads 0x532a84, 0x54061c, 0x532a44,
 * 0x532b40, 0x532b44, 0x540620, 0x558c88, 0x558c84, 0x558c7c, 0x532a38, 0x532a40, 0x54062c,
 * 0x4f88ac, 0x532a98, 0x4f8188, 0x532b9c and more; writes 0x540620, 0x532bd0, 0x54062c, 0x54061c,
 * 0x532a44, 0x532a24, 0x532a60, 0x532a3c, 0x5bb534, 0x5bb548, 0x5bb710, 0x5bb54c, 0x540624,
 * 0x5bb508, 0x540628, 0x5bb550 and more. Register-for-register from the listing
 * (0x424990..0x425252); labels are the original addresses. */
static void run(Regs *r)
{
    push_mem(r, r->ebx);
    push_mem(r, r->ecx);
    push_mem(r, r->edx);
    push_mem(r, r->esi);
    push_mem(r, r->edi);
    r->esi = r->eax;
    r->edx = rd32(r, 0x532a84);
    if (r->edx != 0)
    {
        goto at_424d9d;
    }
    if ((uint8_t)rd8(r, 0x54061c) != (uint8_t)0x0)
    {
        goto at_4249d6;
    }
    call_mem_keep(r, 0x41d640, 8);
    wr32(r, 0x540620, r->edx);
    wr32(r, 0x532bd0, r->edx);
    call_mem_keep(r, 0x4b7cd0, 8);
    r->eax = r->esi;
    r->ecx = 0x1;
    call_mem_keep(r, 0x425ae0, 8);
    wr32(r, 0x54062c, r->ecx);
at_4249d6:
    call_mem_keep(r, 0x4b7d10, 8);
    r->eax = r->esi;
    call_mem_keep(r, 0x41d670, 8);
    r->eax = r->esi;
    set_low8(&r->ecx, 0x1);
    call_mem_keep(r, 0x41df00, 8);
    wr8(r, 0x54061c, (r->ecx & 0xff));
    call_mem_keep(r, 0x4ac1c0, 8);
    call_mem_keep(r, 0x471a70, 8);
    if (rd32(r, 0x532a44) != 0x1)
    {
        goto at_424a09;
    }
    call_mem_keep(r, 0x471b80, 8);
at_424a09:
    if (rd32(r, 0x532b40) != 0x1)
    {
        goto at_424a17;
    }
    call_mem_keep(r, 0x472d90, 8);
at_424a17:
    r->eax = rd32(r, 0x532b40);
    if (r->eax != 0x1)
    {
        goto at_424a2d;
    }
    if (r->eax == rd32(r, 0x532b44))
    {
        goto at_424d6a;
    }
at_424a2d:
    if (rd32(r, 0x540620) != 0x0)
    {
        goto at_424a46;
    }
    r->ebx = 0x1;
    call_mem_keep(r, 0x471a60, 8);
    wr32(r, 0x540620, r->ebx);
at_424a46:
    r->eax = 0x5b9c50;
    call_mem_keep(r, 0x4854a0, 8);
    if (r->eax != 0x1)
    {
        goto at_424a79;
    }
    r->edx = rd32(r, 0x558c88);
    r->eax = rd32(r, 0x558c84);
    call_mem_keep(r, 0x471a20, 8);
    r->eax = rd32(r, 0x558c84);
    call_mem_keep(r, 0x471a40, 8);
    r->eax = 0x5b9c50;
    call_mem_keep(r, 0x485520, 8);
at_424a79:
    r->eax = r->esi;
    call_mem_keep(r, 0x41aaf0, 8);
    r->eax = 0x5b9c50;
    call_mem_keep(r, 0x486d00, 8);
    r->eax = rd32(r, 0x558c7c);
    call_mem_keep(r, 0x471a50, 8);
    if (rd32(r, 0x532a44) != 0x1)
    {
        goto at_424aa7;
    }
    r->eax = rd32(r, 0x558c7c);
    call_mem_keep(r, 0x471ba0, 8);
at_424aa7:
    r->eax = r->esi;
    call_mem_keep(r, 0x41d6d0, 8);
    r->eax = r->esi;
    call_mem_keep(r, 0x41dd60, 8);
    r->eax = 0x5b9c50;
    call_mem_keep(r, 0x486da0, 8);
    r->eax = 0x5b9c50;
    call_mem_keep(r, 0x487020, 8);
    r->eax = r->esi;
    call_mem_keep(r, 0x41d660, 8);
    r->eax = r->esi;
    call_mem_keep(r, 0x41de80, 8);
at_424ad7:
    if (rd32(r, 0x532a38) != 0x1)
    {
        goto at_424aef;
    }
    r->eax = r->esi;
    r->edx = 0;
    call_mem_keep(r, 0x41aca0, 8);
    wr32(r, 0x540620, r->edx);
at_424aef:
    r->ecx = rd32(r, 0x532a44);
    if (r->ecx != 0x1)
    {
        goto at_4251f7;
    }
    if (r->ecx != rd32(r, 0x532a40))
    {
        goto at_4251f7;
    }
    call_mem_keep(r, 0x471b90, 8);
    r->eax = 0;
    wr32(r, 0x532a44, r->eax);
at_424b16:
    r->edx = rd32(r, 0x54062c);
    if (r->edx != 0x1)
    {
        goto at_424d57;
    }
    r->eax = 0x54d640;
    call_mem_keep(r, 0x476480, 8);
    if (r->eax == 0)
    {
        goto at_424bd8;
    }
    r->edx = 0x1;
    r->eax = 0x54d640;
    r->ecx = 0x1;
    call_mem_keep(r, 0x4762e0, 8);
    wr32(r, 0x532a24, r->ecx);
    set_high8(&r->ecx, 0);
    wr8(r, 0x54061c, ((r->ecx >> 8) & 0xff));
    call_mem_keep(r, 0x4657f0, 8);
    r->eax = 0x5588f8;
    call_mem_keep(r, 0x477ed0, 8);
    r->eax = 0x5588f8;
    r->edx = 0x7f;
    call_mem_keep(r, 0x477d70, 8);
    r->ebx = rd32(r, 0x4f88ac);
    r->eax = 0x5588f8;
    r->ebx = r->ebx + 0xb;
    call_mem_keep(r, 0x478480, 8);
    r->edx = 0x74;
    r->eax = 0x54d640;
    call_mem_keep(r, 0x476120, 8);
    r->edx = 0x75;
    r->eax = 0x54d640;
    call_mem_keep(r, 0x476120, 8);
    r->eax = rd32(r, 0x532a98);
    r->edx = rd32(r, 0x4f8188);
    r->ebx = rd32(r, 0x532b9c);
    wr32(r, 0x532a60, r->eax);
    r->edx = rd32(r, r->edx * 4 + 0x533164);
    r->eax = 0;
    call_mem_keep(r, 0x482a60, 8);
    r->edx = 0x4254a0;
    r->eax = r->esi;
    call_mem_keep(r, 0x418840, 8);
at_424bd8:
    r->edx = 0;
    r->eax = 0x54d640;
    set_low16(&r->edx, rd16(r, 0x532b7c));
    call_mem_keep(r, 0x476480, 8);
    if (r->eax == 0)
    {
        goto at_424c36;
    }
    r->edx = 0;
    r->eax = 0x54d640;
    set_low16(&r->edx, rd16(r, 0x532b7c));
    call_mem_keep(r, 0x4762e0, 8);
    if (rd32(r, 0x532a7c) != 0x0)
    {
        goto at_424c36;
    }
    if (rd32(r, 0x532a80) != 0x0)
    {
        goto at_424c36;
    }
    wr32(r, 0x532bd0, 0x1);
    set_low8(&r->eax, 0);
    r->edx = 0x425260;
    wr8(r, 0x54061c, (r->eax & 0xff));
    call_mem_keep(r, 0x46f220, 8);
    r->eax = r->esi;
    call_mem_keep(r, 0x418840, 8);
at_424c36:
    if (rd32(r, 0x532b3c) != 0x1)
    {
        goto at_425213;
    }
at_424c43:
    r->edx = 0x3e;
    r->eax = 0x54d640;
    call_mem_keep(r, 0x476480, 8);
    if (r->eax == 0)
    {
        goto at_424c6a;
    }
    r->edx = 0x3e;
    r->eax = 0x54d640;
    call_mem_keep(r, 0x4762e0, 8);
    call_mem_keep(r, 0x471e60, 8);
at_424c6a:
    r->edx = 0x42;
    r->eax = 0x54d640;
    call_mem_keep(r, 0x476480, 8);
    if (r->eax == 0)
    {
        goto at_424c91;
    }
    r->edx = 0x42;
    r->eax = 0x54d640;
    call_mem_keep(r, 0x4762e0, 8);
    call_mem_keep(r, 0x471e80, 8);
at_424c91:
    r->edx = 0x3f;
    r->eax = 0x54d640;
    call_mem_keep(r, 0x476480, 8);
    if (r->eax == 0)
    {
        goto at_424cd3;
    }
    r->edx = 0x3f;
    r->eax = 0x54d640;
    r->ebx = 0x1;
    call_mem_keep(r, 0x4762e0, 8);
    r->edx = r->ebx;
    r->eax = r->ebx;
    wr32(r, 0x532a3c, r->ebx);
    call_mem_keep(r, 0x471ea0, 8);
    r->eax = 0x2;
    r->edx = 0;
    call_mem_keep(r, 0x471ea0, 8);
at_424cd3:
    r->edx = 0x40;
    r->eax = 0x54d640;
    call_mem_keep(r, 0x476480, 8);
    if (r->eax == 0)
    {
        goto at_424d15;
    }
    r->edx = 0x40;
    r->eax = 0x54d640;
    r->edi = 0x1;
    call_mem_keep(r, 0x4762e0, 8);
    r->eax = r->edi;
    r->edx = 0;
    wr32(r, 0x532a3c, r->edi);
    call_mem_keep(r, 0x471ea0, 8);
    r->eax = 0x2;
    r->edx = 0;
    call_mem_keep(r, 0x471ea0, 8);
at_424d15:
    r->edx = 0x41;
    r->eax = 0x54d640;
    call_mem_keep(r, 0x476480, 8);
    if (r->eax == 0)
    {
        goto at_424d57;
    }
    r->edx = 0x41;
    r->eax = 0x54d640;
    call_mem_keep(r, 0x4762e0, 8);
    r->eax = 0x1;
    r->edx = 0;
    wr32(r, 0x532a3c, r->eax);
    call_mem_keep(r, 0x471ea0, 8);
    r->edx = 0x1;
    r->eax = 0x2;
    call_mem_keep(r, 0x471ea0, 8);
at_424d57:
    if (rd32(r, 0x532a3c) == 0x1)
    {
        goto at_42522f;
    }
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    r->edx = pop_mem(r);
    r->ecx = pop_mem(r);
    r->ebx = pop_mem(r);
    return;
at_424d6a:
    call_mem_keep(r, 0x415530, 8);
    call_mem_keep(r, 0x415550, 8);
    call_mem_keep(r, 0x472d50, 8);
    r->eax = 0x5588f8;
    r->edx = 0x4259d0;
    call_mem_keep(r, 0x477ed0, 8);
    r->eax = r->esi;
    call_mem_keep(r, 0x418840, 8);
    set_low8(&r->edx, 0);
    wr8(r, 0x54061c, (r->edx & 0xff));
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    r->edx = pop_mem(r);
    r->ecx = pop_mem(r);
    r->ebx = pop_mem(r);
    return;
at_424d9d:
    if ((uint8_t)rd8(r, 0x54061c) != (uint8_t)0x0)
    {
        goto at_424df3;
    }
    r->eax = r->esi;
    r->ecx = 0;
    call_mem_keep(r, 0x41d640, 8);
    wr32(r, 0x540620, r->ecx);
    wr32(r, 0x532bd0, r->ecx);
    call_mem_keep(r, 0x4b7cd0, 8);
    r->eax = r->esi;
    call_mem_keep(r, 0x425ae0, 8);
    if (rd32(r, 0x532a24) != 0x0)
    {
        goto at_424de4;
    }
    r->eax = 0x5bb4ec;
    call_mem_keep(r, 0x48d500, 8);
    r->eax = 0x5bb524;
    call_mem_keep(r, 0x48d500, 8);
at_424de4:
    r->eax = 0;
    set_low8(&r->edx, 0x1);
    wr32(r, 0x532a24, r->eax);
    wr8(r, 0x54061c, (r->edx & 0xff));
at_424df3:
    call_mem_keep(r, 0x4b7d10, 8);
    r->eax = r->esi;
    call_mem_keep(r, 0x41d670, 8);
    r->eax = r->esi;
    call_mem_keep(r, 0x41df00, 8);
    if (rd32(r, 0x5bb508) != 0x0)
    {
        goto at_424fd1;
    }
    r->edx = 0x5bb524;
    r->eax = 0x5bb594;
    call_mem_keep(r, 0x48d3e0, 8);
    call_mem_keep(r, 0x473af0, 8);
    r->eax = 0x5bb524;
    r->ebx = 0;
    call_mem_keep(r, 0x48d480, 8);
    call_mem(r, rd32(r, 0x4f172c), 0);
    r->edx = 0x5bb594;
    wr32(r, 0x5bb534, r->eax);
    wr32(r, 0x5bb548, r->eax);
    call_mem_keep(r, 0x4737d0, 8);
    r->eax = 0x5bb254;
    call_mem_keep(r, 0x48c0f0, 8);
at_424e58:
    r->eax = rd32(r, 0x5bb50c);
    r->ecx = rd32(r, 0x5bb508);
    r->eax = r->eax >> 0x1;
    if (r->eax != r->ecx)
    {
        goto at_424e6e;
    }
    call_mem_keep(r, 0x473960, 8);
at_424e6e:
    r->eax = 0x5bb254;
    r->ebx = 0x1;
    call_mem_keep(r, 0x48c370, 8);
    call_mem_keep(r, 0x4ac1c0, 8);
    wr32(r, 0x5bb710, r->ebx);
    call_mem_keep(r, 0x471a70, 8);
    if (r->ebx != rd32(r, 0x532a44))
    {
        goto at_424e9a;
    }
    call_mem_keep(r, 0x471b80, 8);
at_424e9a:
    if (rd32(r, 0x540620) != 0x0)
    {
        goto at_424eb3;
    }
    r->edx = 0x1;
    call_mem_keep(r, 0x471a60, 8);
    wr32(r, 0x540620, r->edx);
at_424eb3:
    r->eax = 0x5b9c50;
    call_mem_keep(r, 0x4854a0, 8);
    if (r->eax != 0x1)
    {
        goto at_424ee6;
    }
    r->edx = rd32(r, 0x558c88);
    r->eax = rd32(r, 0x558c84);
    call_mem_keep(r, 0x471a20, 8);
    r->eax = rd32(r, 0x558c84);
    call_mem_keep(r, 0x471a40, 8);
    r->eax = 0x5b9c50;
    call_mem_keep(r, 0x485520, 8);
at_424ee6:
    r->eax = r->esi;
    call_mem_keep(r, 0x41aaf0, 8);
    r->eax = 0x5b9c50;
    call_mem_keep(r, 0x486d00, 8);
    r->eax = rd32(r, 0x558c7c);
    call_mem_keep(r, 0x471a50, 8);
    if (rd32(r, 0x532a44) != 0x1)
    {
        goto at_424f14;
    }
    r->eax = rd32(r, 0x558c7c);
    call_mem_keep(r, 0x471ba0, 8);
at_424f14:
    r->eax = r->esi;
    call_mem_keep(r, 0x41d6d0, 8);
    r->eax = r->esi;
    call_mem_keep(r, 0x41dd60, 8);
    r->eax = 0x5b9c50;
    call_mem_keep(r, 0x486da0, 8);
    r->eax = 0x5b9c50;
    call_mem_keep(r, 0x487020, 8);
    r->eax = 0x5b9c50;
    call_mem_keep(r, 0x487060, 8);
    r->eax = r->esi;
    call_mem_keep(r, 0x41d660, 8);
    r->eax = r->esi;
    call_mem_keep(r, 0x41de80, 8);
    call_mem(r, rd32(r, 0x4f172c), 0);
    r->edi = rd32(r, 0x5bb548);
    r->edx = r->eax;
    r->ecx = rd32(r, 0x5bb550);
    r->edx = r->edx - r->edi;
    r->ebx = rd32(r, 0x5bb508);
    r->ecx = r->ecx + r->edx;
    r->edx = rd32(r, 0x5bb534);
    wr32(r, 0x5bb54c, r->eax);
    r->eax = r->eax - r->edx;
    r->ebx = r->ebx + 1;
    wr32(r, 0x540624, r->eax);
    r->eax = rd32(r, 0x5bb518);
    r->eax = r->eax * r->ebx;
    wr32(r, 0x5bb508, r->ebx);
    wr32(r, 0x540628, r->eax);
    r->eax = rd32(r, 0x540624);
    r->edi = rd32(r, 0x540628);
    wr32(r, 0x5bb550, r->ecx);
    if (r->eax >= r->edi)
    {
        goto at_424fb7;
    }
    r->edx = rd32(r, 0x540624);
    r->eax = r->edi;
    r->eax = r->eax - r->edx;
    call_mem_keep(r, 0x4b7db0, 8);
at_424fb7:
    r->eax = rd32(r, 0x5bb508);
    if (r->eax == rd32(r, 0x5bb50c))
    {
        goto at_424fe2;
    }
    r->ebx = 0;
    wr32(r, 0x54062c, r->ebx);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_424ad7;
at_424fd1:
    call_mem(r, rd32(r, 0x4f172c), 0);
    wr32(r, 0x5bb548, r->eax);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_424e58;
at_424fe2:
    r->eax = r->esi;
    call_mem_keep(r, 0x424790, 8);
    if (r->eax != 0)
    {
        goto at_424ffb;
    }
    set_low8(&r->ebx, 0);
    wr8(r, 0x54061c, (r->ebx & 0xff));
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    r->edx = pop_mem(r);
    r->ecx = pop_mem(r);
    r->ebx = pop_mem(r);
    return;
at_424ffb:
    r->eax = r->esi;
    call_mem_keep(r, 0x424890, 8);
    if (r->eax == 0)
    {
        goto at_4251d8;
    }
    r->edx = 0x5bb55c;
    r->eax = 0x5bb254;
    call_mem_keep(r, 0x48bca0, 8);
    r->edx = 0x5bb594;
    r->eax = 0x5bb254;
    call_mem_keep(r, 0x48be70, 8);
    r->eax = rd32(r, 0x5bb570);
    wr32(r, 0x5bb538, r->eax);
    call_mem(r, rd32(r, 0x4f172c), 0);
    r->edx = rd32(r, 0x5bb534);
    r->eax = r->eax - r->edx;
    r->ebx = rd32(r, 0x5bb50c);
    wr32(r, 0x540624, r->eax);
    r->edx = 0;
    r->eax = rd32(r, 0x5bb550);
    div32(r, r->ebx);
    wr32(r, 0x5bb550, r->eax);
    r->eax = 0x5bb254;
    call_mem_keep(r, 0x480030, 8);
    r->eax = 0x5bb254;
    r->edx = 0;
    call_mem_keep(r, 0x480070, 8);
    r->edi = rd32(r, 0x5bb550);
    wr32(r, 0x5bb53c, r->eax);
    div32(r, r->edi);
    r->eax = r->eax + 1;
    wr32(r, 0x5bb544, r->eax);
    if (r->eax >= 0xff)
    {
        goto at_4251e6;
    }
at_42508e:
    wr32(r, 0x5bb544, r->eax);
    r->eax = 0x5bb4ec;
    call_mem_keep(r, 0x48d480, 8);
    set_low8(&r->eax, rd8(r, 0x5bb594));
    wr8(r, 0x5bb4ec, (r->eax & 0xff));
    set_low8(&r->eax, rd8(r, 0x5bb595));
    wr8(r, 0x5bb4ed, (r->eax & 0xff));
    set_low8(&r->eax, rd8(r, 0x5bb596));
    wr8(r, 0x5bb4ee, (r->eax & 0xff));
    set_low8(&r->eax, rd8(r, 0x5bb597));
    wr8(r, 0x5bb4ef, (r->eax & 0xff));
    set_low8(&r->eax, rd8(r, 0x5bb598));
    wr8(r, 0x5bb4f0, (r->eax & 0xff));
    set_low8(&r->eax, rd8(r, 0x5bb599));
    wr8(r, 0x5bb4f1, (r->eax & 0xff));
    set_low8(&r->eax, rd8(r, 0x5bb59a));
    wr8(r, 0x5bb4f2, (r->eax & 0xff));
    set_low8(&r->eax, rd8(r, 0x5bb59b));
    wr8(r, 0x5bb4f3, (r->eax & 0xff));
    set_low8(&r->eax, rd8(r, 0x5bb564));
    wr8(r, 0x5bb4f4, (r->eax & 0xff));
    set_low8(&r->eax, rd8(r, 0x5bb565));
    wr8(r, 0x5bb4f5, (r->eax & 0xff));
    set_low8(&r->eax, rd8(r, 0x5bb566));
    wr8(r, 0x5bb4f6, (r->eax & 0xff));
    set_low8(&r->eax, rd8(r, 0x5bb567));
    wr8(r, 0x5bb4f7, (r->eax & 0xff));
    set_low8(&r->eax, rd8(r, 0x5bb568));
    wr8(r, 0x5bb4f8, (r->eax & 0xff));
    set_low8(&r->eax, rd8(r, 0x5bb569));
    wr8(r, 0x5bb4f9, (r->eax & 0xff));
    set_low8(&r->eax, rd8(r, 0x5bb56a));
    wr8(r, 0x5bb4fa, (r->eax & 0xff));
    set_low8(&r->eax, rd8(r, 0x5bb56b));
    r->edx = rd32(r, 0x5bb588);
    wr8(r, 0x5bb4fb, (r->eax & 0xff));
    r->eax = rd32(r, 0x5bb5c0);
    if (r->eax <= r->edx)
    {
        goto at_4251f0;
    }
at_425150:
    r->edx = rd32(r, 0x5bb5c0);
    r->edx = r->edx * rd32(r, 0x5bb5b4);
    r->ebx = rd32(r, 0x5bb57c);
    wr32(r, 0x5bb518, r->eax);
    r->eax = rd32(r, 0x5bb588);
    r->eax = r->eax * r->ebx;
    if (r->edx <= r->eax)
    {
        goto at_425176;
    }
    r->eax = r->edx;
at_425176:
    r->ebx = rd32(r, 0x5bb518);
    r->edx = 0;
    wr32(r, 0x5bb50c, r->eax);
    div32(r, r->ebx);
    wr32(r, 0x5bb50c, r->eax);
    r->eax = r->eax * r->ebx;
    if (r->eax <= 0x3e8)
    {
        goto at_4251a3;
    }
    r->eax = 0x1;
    wr32(r, 0x5bb518, r->eax);
    wr32(r, 0x5bb50c, r->eax);
at_4251a3:
    if (rd32(r, 0x532a08) != 0x1)
    {
        goto at_4251c9;
    }
    r->eax = rd32(r, 0x5bb53c);
    r->ebx = rd32(r, 0x5bb518);
    wr32(r, 0x532a10, r->eax);
    r->eax = rd32(r, 0x5bb50c);
    r->eax = r->eax * r->ebx;
    wr32(r, 0x532a14, r->eax);
at_4251c9:
    wr32(r, 0x54062c, 0x1);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_424ad7;
at_4251d8:
    set_high8(&r->edx, 0);
    wr8(r, 0x54061c, ((r->edx >> 8) & 0xff));
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    r->edx = pop_mem(r);
    r->ecx = pop_mem(r);
    r->ebx = pop_mem(r);
    return;
at_4251e6:
    r->eax = 0xff;
    if (r->port->env.failed)
    {
        return;
    }
    goto at_42508e;
at_4251f0:
    r->eax = r->edx;
    if (r->port->env.failed)
    {
        return;
    }
    goto at_425150;
at_4251f7:
    if (rd32(r, 0x532a44) == 0x0 && !r->port->env.failed)
    {
        goto at_424b16;
    }
    if (rd32(r, 0x532a3c) == 0x1)
    {
        goto at_42522f;
    }
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    r->edx = pop_mem(r);
    r->ecx = pop_mem(r);
    r->ebx = pop_mem(r);
    return;
at_425213:
    if (rd32(r, 0x532b38) == 0x1 && !r->port->env.failed)
    {
        goto at_424c43;
    }
    if (rd32(r, 0x532a3c) == 0x1)
    {
        goto at_42522f;
    }
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    r->edx = pop_mem(r);
    r->ecx = pop_mem(r);
    r->ebx = pop_mem(r);
    return;
at_42522f:
    set_high8(&r->eax, 0);
    wr8(r, 0x54061c, ((r->eax >> 8) & 0xff));
    r->eax = 0x5588f8;
    r->edx = 0x425810;
    call_mem_keep(r, 0x477ed0, 8);
    r->eax = r->esi;
    call_mem_keep(r, 0x418840, 8);
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    r->edx = pop_mem(r);
    r->ecx = pop_mem(r);
    r->ebx = pop_mem(r);
    return;
}

uint32_t vertrix_port_game_loop_run_424990(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x30
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
