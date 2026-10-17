#include "port_rtlformatoutputs.h"

/* The runtime printf core: walks the format, converts each argument and writes the text through the
 * stream. */

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

static void wr16(Regs *r, uint32_t address, uint32_t value)
{
    port_set16(r->port, address, 0, value);
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

/* Original 0x4e2434: The runtime printf core: walks the format, converts each argument and writes
 * the text through the stream. Evidence: calls 0x4e3b60, 0x4df320, 0x4e3ce0, 0x4e2ad0, 0x4e2a30,
 * 0x4e2b60, 0x4e2610, 0x4ca6f0, 0x4e28e0, 0x4e7370, 0x4ca060, 0x4ca3a0, 0x4ca040, 0x4ce740,
 * 0x4de9c0, 0x4dea40, 0x4eb5e0, 0x4e1140, 0x4e2f10, 0x4df160, 0x4e3060, 0x4e2d40, 0x4e3160,
 * 0x4d3010 and 13 more; reads 0x507ca0, 0x507ca4, 0x4f1d14, 0x4f1d24. Register-for-register from
 * the listing (0x4e2434..0x4e33cf); labels are the original addresses. */
static void run(Regs *r)
{
    push_mem(r, r->ecx);
    push_mem(r, r->esi);
    push_mem(r, r->edi);
    push_mem(r, r->ebp);
    r->esi = r->eax;
    r->eax = rd32(r, r->eax + 0x10);
    call_mem(r, rd32(r, 0x507ca0), 4);
    r->eax = rd32(r, r->esi + 0x8);
    r->ecx = rd32(r, r->eax + 0xc);
    if (r->ecx == 0x1)
    {
        goto at_4e2469;
    }
    if (r->ecx == 0)
    {
        goto at_4e2462;
    }
    r->eax = rd32(r, r->esi + 0x10);
    call_mem(r, rd32(r, 0x507ca4), 0);
    r->eax = 0;
    r->ebp = pop_mem(r);
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    r->ecx = pop_mem(r);
    return;
at_4e2462:
    wr32(r, r->eax + 0xc, 0x1);
at_4e2469:
    set_high8(&r->eax, rd8(r, r->esi + 0xc));
    set_high8(&r->eax, ((r->eax >> 8) & 0xff) & 0xcf);
    r->ebp = rd32(r, r->esi + 0xc);
    wr8(r, r->esi + 0xc, ((r->eax >> 8) & 0xff));
    r->eax = rd32(r, r->esi + 0x8);
    r->ecx = rd32(r, r->eax + 0x8);
    r->ebp = r->ebp & 0x30;
    if (r->ecx != 0)
    {
        goto at_4e2489;
    }
    r->eax = r->esi;
    call_mem_keep(r, 0x4e3b60, 8);
at_4e2489:
    set_low8(&r->ecx, rd8(r, r->esi + 0xd));
    r->edi = 0;
    if ((uint8_t)((r->ecx & 0xff) & 0x4) == 0)
    {
        goto at_4e24a7;
    }
    set_high8(&r->ecx, (r->ecx & 0xff));
    set_high8(&r->ecx, ((r->ecx >> 8) & 0xff) & 0xfa);
    set_low8(&r->eax, ((r->ecx >> 8) & 0xff));
    wr8(r, r->esi + 0xd, ((r->ecx >> 8) & 0xff));
    set_low8(&r->eax, (r->eax & 0xff) | 0x1);
    r->edi = 0x1;
    wr8(r, r->esi + 0xd, (r->eax & 0xff));
at_4e24a7:
    r->ecx = 0x4e2420;
    r->eax = r->esi;
    call_mem_keep(r, 0x4df320, 8);
    r->edx = r->eax;
    if (r->edi == 0)
    {
        goto at_4e24d1;
    }
    set_high8(&r->eax, rd8(r, r->esi + 0xd));
    set_high8(&r->eax, ((r->eax >> 8) & 0xff) & 0xfa);
    set_low8(&r->ebx, ((r->eax >> 8) & 0xff));
    wr8(r, r->esi + 0xd, ((r->eax >> 8) & 0xff));
    set_low8(&r->ebx, (r->ebx & 0xff) | 0x4);
    r->eax = r->esi;
    wr8(r, r->esi + 0xd, (r->ebx & 0xff));
    call_mem_keep(r, 0x4e3ce0, 8);
at_4e24d1:
    if ((uint8_t)(rd8(r, r->esi + 0xc) & 0x20) == 0)
    {
        goto at_4e24dc;
    }
    r->edx = 0xffffffffu;
at_4e24dc:
    r->edi = rd32(r, r->esi + 0xc);
    r->edi = r->edi | r->ebp;
    r->eax = rd32(r, r->esi + 0x10);
    wr32(r, r->esi + 0xc, r->edi);
    call_mem(r, rd32(r, 0x507ca4), 0);
    r->eax = r->edx;
    r->ebp = pop_mem(r);
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    r->ecx = pop_mem(r);
    return;
    wr8(r, r->eax, rd8(r, r->eax) + (r->eax & 0xff));
    wr8(r, r->eax, rd8(r, r->eax) + (r->eax & 0xff));
    wr8(r, r->eax, rd8(r, r->eax) + (r->eax & 0xff));
    wr8(r, r->eax, rd8(r, r->eax) + (r->eax & 0xff));
    wr8(r, r->eax, rd8(r, r->eax) + (r->eax & 0xff));
    wr8(r, r->eax, rd8(r, r->eax) + (r->eax & 0xff));
    push_mem(r, r->ebx);
    push_mem(r, r->esi);
    r->esp = r->esp - 0x4;
    r->ecx = rd32(r, r->esp + 0x10);
    r->esi = rd32(r, r->esp + 0x14);
    r->eax = rd32(r, r->esi);
    r->eax = r->eax - 0xc;
    if ((int32_t)rd32(r, r->eax + 0x4) >= (int32_t)0xff)
    {
        goto at_4e253d;
    }
    set_low8(&r->ebx, rd8(r, r->eax + 0x4));
    r->eax = rd32(r, r->ecx + 0x24);
    r->eax = r->eax + 1;
    r->edx = r->ecx;
    if (r->eax <= rd32(r, r->ecx + 0x28))
    {
        goto at_4e2530;
    }
    r->eax = r->ecx;
    call_mem_keep(r, 0x4e2ad0, 8);
at_4e2530:
    r->eax = rd32(r, r->edx + 0x24);
    wr8(r, r->eax, (r->ebx & 0xff));
    wr32(r, r->edx + 0x24, rd32(r, r->edx + 0x24) + 1);
    goto at_4e25f4;
at_4e253d:
    if ((int32_t)rd32(r, r->eax + 0x4) >= (int32_t)0xfffe)
    {
        goto at_4e258b;
    }
    r->eax = rd32(r, r->ecx + 0x24);
    set_low8(&r->ebx, 0xff);
    r->eax = r->eax + 1;
    r->edx = r->ecx;
    if (r->eax <= rd32(r, r->ecx + 0x28))
    {
        goto at_4e255a;
    }
    r->eax = r->ecx;
    call_mem_keep(r, 0x4e2ad0, 8);
at_4e255a:
    r->eax = rd32(r, r->edx + 0x24);
    wr8(r, r->eax, (r->ebx & 0xff));
    wr32(r, r->edx + 0x24, rd32(r, r->edx + 0x24) + 1);
    r->eax = rd32(r, r->esi);
    r->eax = r->eax - 0xc;
    set_low16(&r->ebx, rd16(r, r->eax + 0x4));
    r->eax = rd32(r, r->ecx + 0x24);
    r->eax = r->eax + 0x2;
    r->edx = r->ecx;
    if (r->eax <= rd32(r, r->ecx + 0x28))
    {
        goto at_4e257f;
    }
    r->eax = r->ecx;
    call_mem_keep(r, 0x4e2ad0, 8);
at_4e257f:
    r->eax = rd32(r, r->edx + 0x24);
    wr16(r, r->eax, (r->ebx & 0xffff));
    wr32(r, r->edx + 0x24, rd32(r, r->edx + 0x24) + 0x2);
    goto at_4e25f4;
at_4e258b:
    r->eax = rd32(r, r->ecx + 0x24);
    set_low8(&r->ebx, 0xff);
    r->eax = r->eax + 1;
    r->edx = r->ecx;
    if (r->eax <= rd32(r, r->ecx + 0x28))
    {
        goto at_4e259f;
    }
    r->eax = r->ecx;
    call_mem_keep(r, 0x4e2ad0, 8);
at_4e259f:
    r->eax = rd32(r, r->edx + 0x24);
    wr8(r, r->eax, (r->ebx & 0xff));
    wr32(r, r->edx + 0x24, rd32(r, r->edx + 0x24) + 1);
    r->eax = rd32(r, r->ecx + 0x24);
    wr32(r, r->esp, 0xffff);
    r->eax = r->eax + 0x2;
    r->ebx = r->ecx;
    if (r->eax <= rd32(r, r->ecx + 0x28))
    {
        goto at_4e25c2;
    }
    r->eax = r->ecx;
    call_mem_keep(r, 0x4e2ad0, 8);
at_4e25c2:
    r->eax = rd32(r, r->ebx + 0x24);
    r->edx = rd32(r, r->esp);
    wr16(r, r->eax, (r->edx & 0xffff));
    wr32(r, r->ebx + 0x24, rd32(r, r->ebx + 0x24) + 0x2);
    r->eax = rd32(r, r->esi);
    r->eax = r->eax - 0xc;
    r->ebx = rd32(r, r->eax + 0x4);
    r->eax = rd32(r, r->ecx + 0x24);
    r->eax = r->eax + 0x4;
    r->edx = r->ecx;
    if (r->eax <= rd32(r, r->ecx + 0x28))
    {
        goto at_4e25eb;
    }
    r->eax = r->ecx;
    call_mem_keep(r, 0x4e2ad0, 8);
at_4e25eb:
    r->eax = rd32(r, r->edx + 0x24);
    wr32(r, r->eax, r->ebx);
    wr32(r, r->edx + 0x24, rd32(r, r->edx + 0x24) + 0x4);
at_4e25f4:
    r->edx = rd32(r, r->esi);
    r->ebx = r->edx - 0xc;
    r->eax = r->ecx;
    r->ebx = rd32(r, r->ebx + 0x4);
    call_mem_keep(r, 0x4e2a30, 8);
    r->eax = r->ecx;
    r->esp = r->esp + 0x4;
    r->esi = pop_mem(r);
    r->ebx = pop_mem(r);
    return;
    wr8(r, r->eax, rd8(r, r->eax) + (r->eax & 0xff));
    wr8(r, r->ebx - 0x75, rd8(r, r->ebx - 0x75) + (r->edx & 0xff));
    r->esp = r->esp - 1;
    set_low8(&r->eax, (r->eax & 0xff) & 0x8);
    r->eax = rd32(r, r->ecx + 0x24);
    r->edx = r->eax + 0x1;
    r->ebx = r->ecx;
    if (r->edx <= rd32(r, r->ecx + 0x28))
    {
        goto at_4e2637;
    }
    r->edx = rd32(r, r->ecx + 0x28);
    r->edx = r->edx - r->eax;
    r->eax = 0x1;
    r->eax = r->eax - r->edx;
    r->edx = r->eax;
    r->eax = r->ecx;
    call_mem_keep(r, 0x4e2b60, 8);
at_4e2637:
    r->eax = rd32(r, r->ebx + 0x24);
    r->eax = r->eax + 1;
    set_low8(&r->edx, rd8(r, r->eax - 0x1));
    wr32(r, r->ebx + 0x24, r->eax);
    r->eax = (r->edx & 0xff);
    if ((int32_t)r->eax >= (int32_t)0xff)
    {
        goto at_4e2652;
    }
    r->eax = (r->edx & 0xff);
    r->ebx = pop_mem(r);
    return;
at_4e2652:
    r->eax = rd32(r, r->ecx + 0x24);
    r->edx = r->eax + 0x2;
    r->ebx = r->ecx;
    if (r->edx <= rd32(r, r->ecx + 0x28))
    {
        goto at_4e2674;
    }
    r->edx = rd32(r, r->ecx + 0x28);
    r->edx = r->edx - r->eax;
    r->eax = 0x2;
    r->eax = r->eax - r->edx;
    r->edx = r->eax;
    r->eax = r->ecx;
    call_mem_keep(r, 0x4e2b60, 8);
at_4e2674:
    r->eax = rd32(r, r->ebx + 0x24);
    r->eax = r->eax + 0x2;
    set_low16(&r->edx, rd16(r, r->eax - 0x2));
    wr32(r, r->ebx + 0x24, r->eax);
    r->eax = (r->edx & 0xffff);
    if (r->eax != 0xfffe)
    {
        goto at_4e2694;
    }
    r->eax = 0xffffffffu;
    r->ebx = pop_mem(r);
    return;
at_4e2694:
    if (r->eax != 0xffff)
    {
        goto at_4e26cf;
    }
    r->eax = rd32(r, r->ecx + 0x24);
    r->edx = r->eax + 0x4;
    r->ebx = r->ecx;
    if (r->edx <= rd32(r, r->ecx + 0x28))
    {
        goto at_4e26bd;
    }
    r->edx = rd32(r, r->ecx + 0x28);
    r->edx = r->edx - r->eax;
    r->eax = 0x4;
    r->eax = r->eax - r->edx;
    r->edx = r->eax;
    r->eax = r->ecx;
    call_mem_keep(r, 0x4e2b60, 8);
at_4e26bd:
    r->eax = rd32(r, r->ebx + 0x24);
    r->eax = r->eax + 0x4;
    r->edx = rd32(r, r->eax - 0x4);
    wr32(r, r->ebx + 0x24, r->eax);
    r->eax = r->edx;
    r->ebx = pop_mem(r);
    return;
at_4e26cf:
    r->eax = (r->edx & 0xffff);
    r->ebx = pop_mem(r);
    return;
    wr8(r, r->eax, rd8(r, r->eax) + (r->eax & 0xff));
    wr8(r, r->eax, rd8(r, r->eax) + (r->eax & 0xff));
    wr8(r, r->eax, rd8(r, r->eax) + (r->eax & 0xff));
    wr8(r, r->eax, rd8(r, r->eax) + (r->eax & 0xff));
    wr8(r, r->eax, rd8(r, r->eax) + (r->eax & 0xff));
    push_mem(r, r->ebx);
    push_mem(r, r->esi);
    push_mem(r, r->edi);
    push_mem(r, r->ebp);
    r->esi = rd32(r, r->esp + 0x18);
    push_mem(r, rd32(r, r->esp + 0x14));
    call_mem(r, 0x4e2610, 1);
    r->ebp = 0;
    r->edi = r->eax;
    if (r->eax != 0xffffffffu)
    {
        goto at_4e270a;
    }
    push_mem(r, rd32(r, r->esp + 0x14));
    r->ebp = 0x1;
    call_mem(r, 0x4e2610, 1);
    r->edi = r->eax;
at_4e270a:
    r->ecx = r->edi;
    r->ecx = r->ecx * r->ebp;
    r->ecx = r->ecx + r->edi;
    if (r->edi != 0)
    {
        goto at_4e271b;
    }
    r->eax = r->esi;
    r->edx = 0;
    goto at_4e2720;
at_4e271b:
    r->eax = r->esi;
    r->edx = r->ecx + r->ebp;
at_4e2720:
    call_mem_keep(r, 0x4ca6f0, 8);
    if (r->edi == 0)
    {
        goto at_4e276c;
    }
    r->eax = rd32(r, r->esp + 0x14);
    r->ebx = r->ecx;
    r->edx = rd32(r, r->esi);
    call_mem_keep(r, 0x4e28e0, 8);
    if (r->eax == r->ecx)
    {
        goto at_4e2743;
    }
    push_mem(r, 0x0);
    push_mem(r, 0x3);
    call_mem(r, 0x4e7370, 2);
at_4e2743:
    if (r->ebp == 0)
    {
        goto at_4e276c;
    }
    r->ebp = rd32(r, r->esi);
    r->ebx = r->ebp - 0xc;
    wr16(r, r->ebp + r->edi * 2, 0x0);
    call_mem_keep(r, 0x4ca060, 8);
    r->eax = rd32(r, r->eax);
    r->edx = r->ebp;
    wr32(r, r->esi, r->eax);
    r->eax = r->esi;
    call_mem_keep(r, 0x4ca3a0, 8);
    r->eax = r->ebx;
    call_mem_keep(r, 0x4ca040, 8);
at_4e276c:
    r->eax = rd32(r, r->esp + 0x14);
    r->ebp = pop_mem(r);
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    r->ebx = pop_mem(r);
    return;
    wr8(r, r->eax, rd8(r, r->eax) + (r->eax & 0xff));
    wr8(r, r->eax, rd8(r, r->eax) + (r->eax & 0xff));
    wr8(r, r->eax, rd8(r, r->eax) + (r->eax & 0xff));
    wr8(r, r->eax, rd8(r, r->eax) + (r->eax & 0xff));
    wr8(r, r->ebx + 0x56, rd8(r, r->ebx + 0x56) + (r->edx & 0xff));
    r->esp = r->esp - 0x44;
    r->ecx = rd32(r, r->esp + 0x50);
    r->eax = rd32(r, r->ecx + 0x24);
    r->edx = r->eax + 0x2;
    r->ebx = r->ecx;
    if (r->edx <= rd32(r, r->ecx + 0x28))
    {
        goto at_4e27ab;
    }
    r->edx = rd32(r, r->ecx + 0x28);
    r->edx = r->edx - r->eax;
    r->eax = 0x2;
    r->eax = r->eax - r->edx;
    r->edx = r->eax;
    r->eax = r->ecx;
    call_mem_keep(r, 0x4e2b60, 8);
at_4e27ab:
    r->eax = rd32(r, r->ebx + 0x24);
    set_low16(&r->edx, rd16(r, r->eax));
    r->eax = r->eax + 0x2;
    wr32(r, r->ebx + 0x24, r->eax);
    r->eax = (r->edx & 0xffff);
    r->edx = rd32(r, r->esp + 0x54);
    wr32(r, r->edx, r->eax);
    r->eax = rd32(r, r->ecx + 0x24);
    r->edx = r->eax + 0x2;
    r->ebx = r->ecx;
    if (r->edx <= rd32(r, r->ecx + 0x28))
    {
        goto at_4e27e2;
    }
    r->edx = rd32(r, r->ecx + 0x28);
    r->edx = r->edx - r->eax;
    r->eax = 0x2;
    r->eax = r->eax - r->edx;
    r->edx = r->eax;
    r->eax = r->ecx;
    call_mem_keep(r, 0x4e2b60, 8);
at_4e27e2:
    r->eax = rd32(r, r->ebx + 0x24);
    set_low16(&r->edx, rd16(r, r->eax));
    r->eax = r->eax + 0x2;
    wr16(r, r->esp + 0x40, (r->edx & 0xffff));
    r->esi = (r->edx & 0xffff);
    wr32(r, r->ebx + 0x24, r->eax);
    if (r->esi >= 0x40)
    {
        goto at_4e2856;
    }
    r->edx = r->esp;
    r->ebx = r->esi;
    r->eax = r->ecx;
    call_mem_keep(r, 0x4e28e0, 8);
    if (r->eax != r->esi)
    {
        goto at_4e2856;
    }
    r->eax = rd16(r, r->esp + 0x40);
    wr8(r, r->esp + r->eax, 0x0);
    call_mem_keep(r, 0x4ce740, 8);
    push_mem(r, 0x0);
    r->ebx = r->eax;
    call_mem(r, 0x4de9c0, 1);
    r->eax = rd32(r, r->ebx + 0x1c);
    r->ebx = r->eax;
    if (r->eax != 0)
    {
        goto at_4e2833;
    }
    goto at_4e284f;
at_4e282c:
    r->ebx = rd32(r, r->ebx + 0x14);
    if (r->ebx == 0)
    {
        goto at_4e284f;
    }
at_4e2833:
    push_mem(r, rd32(r, r->ebx));
    r->eax = r->esp + 0x4;
    push_mem(r, r->eax);
    call_mem(r, rd32(r, 0x4f1d14), 2);
    if (r->eax != 0 && !r->port->env.failed)
    {
        goto at_4e282c;
    }
    push_mem(r, r->eax);
    call_mem(r, 0x4dea40, 1);
    r->eax = r->ebx;
    goto at_4e2858;
at_4e284f:
    push_mem(r, 0x0);
    call_mem(r, 0x4dea40, 1);
at_4e2856:
    r->eax = 0;
at_4e2858:
    r->esp = r->esp + 0x44;
    r->esi = pop_mem(r);
    r->ebx = pop_mem(r);
    return;
    push_mem(r, r->ebx);
    push_mem(r, r->ecx);
    push_mem(r, r->esi);
    push_mem(r, r->edi);
    r->esp = r->esp - 0x8;
    r->ebx = r->eax;
    r->esi = r->edx;
    push_mem(r, rd32(r, r->eax));
    call_mem(r, rd32(r, 0x4f1d24), 5);
    r->edi = r->eax;
    set_low16(&r->eax, rd16(r, r->ebx + 0x8));
    wr32(r, r->esp + 0x4, r->eax);
    r->eax = rd32(r, r->esi + 0x24);
    r->eax = r->eax + 0x2;
    r->edx = r->esi;
    if (r->eax <= rd32(r, r->esi + 0x28))
    {
        goto at_4e2892;
    }
    r->eax = r->esi;
    call_mem_keep(r, 0x4e2ad0, 8);
at_4e2892:
    r->ecx = rd32(r, r->edx + 0x24);
    r->eax = rd32(r, r->esp + 0x4);
    wr16(r, r->ecx, (r->eax & 0xffff));
    wr32(r, r->edx + 0x24, rd32(r, r->edx + 0x24) + 0x2);
    r->eax = rd32(r, r->edx + 0x24);
    wr32(r, r->esp, r->edi);
    r->eax = r->eax + 0x2;
    r->ecx = r->edx;
    if (r->eax <= rd32(r, r->edx + 0x28))
    {
        goto at_4e28b7;
    }
    r->eax = r->edx;
    call_mem_keep(r, 0x4e2ad0, 8);
at_4e28b7:
    r->edx = rd32(r, r->ecx + 0x24);
    r->eax = rd32(r, r->esp);
    wr16(r, r->edx, (r->eax & 0xffff));
    r->edx = (r->edi & 0xffff);
    wr32(r, r->ecx + 0x24, rd32(r, r->ecx + 0x24) + 0x2);
    r->eax = r->esi;
    r->ecx = rd32(r, r->ebx);
    r->ebx = r->edx;
    r->edx = r->ecx;
    call_mem_keep(r, 0x4e2a30, 8);
    r->esp = r->esp + 0x8;
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    r->ecx = pop_mem(r);
    r->ebx = pop_mem(r);
    return;
    wr8(r, r->eax, rd8(r, r->eax) + (r->eax & 0xff));
    wr8(r, r->eax, rd8(r, r->eax) + (r->eax & 0xff));
    push_mem(r, r->ecx);
    push_mem(r, r->esi);
    push_mem(r, r->edi);
    push_mem(r, r->ebp);
    r->esp = r->esp - 0x18;
    r->esi = r->eax;
    r->edi = r->edx;
    wr32(r, r->esp + 0x4, r->ebx);
    if (r->ebx != 0)
    {
        goto at_4e28fa;
    }
    r->eax = 0;
    goto at_4e2a1b;
at_4e28fa:
    r->eax = rd32(r, r->eax + 0x28);
    r->eax = r->eax - rd32(r, r->esi + 0x24);
    wr32(r, r->esp + 0x8, r->ebx);
    if (r->eax <= r->ebx)
    {
        goto at_4e290c;
    }
    r->ecx = r->ebx;
    goto at_4e290e;
at_4e290c:
    r->ecx = r->eax;
at_4e290e:
    r->ebx = r->ecx;
    r->eax = r->edi;
    r->edx = rd32(r, r->esi + 0x24);
    call_mem_keep(r, 0x4eb5e0, 8);
    r->edi = r->edi + r->ecx;
    wr32(r, r->esi + 0x24, rd32(r, r->esi + 0x24) + r->ecx);
    wr32(r, r->esp + 0x8, rd32(r, r->esp + 0x8) - r->ecx);
    if (rd32(r, r->esp + 0x8) == 0)
    {
        goto at_4e2a13;
    }
    r->eax = rd32(r, r->esp + 0x8);
    r->edx = 0;
    div32(r, rd32(r, r->esi + 0x1c));
    r->eax = rd32(r, r->esp + 0x8);
    r->eax = r->eax - r->edx;
    wr32(r, r->esp + 0xc, 0x0);
    wr32(r, r->esp, r->eax);
    r->ecx = r->eax;
at_4e2945:
    r->eax = rd32(r, r->esi + 0x20);
    r->ebp = rd32(r, r->eax);
    r->ebx = r->ecx;
    r->edx = r->edi;
    call_mem(r, rd32(r, r->ebp + 0x3c), 0);
    wr32(r, r->esp + 0xc, rd32(r, r->esp + 0xc) + r->eax);
    r->edi = r->edi + r->eax;
    r->ecx = r->ecx - r->eax;
    if (r->eax == 0)
    {
        goto at_4e2961;
    }
    if (r->ecx != 0 && !r->port->env.failed)
    {
        goto at_4e2945;
    }
at_4e2961:
    r->eax = rd32(r, r->esp + 0xc);
    wr32(r, r->esp + 0x8, rd32(r, r->esp + 0x8) - r->eax);
    if (r->eax != rd32(r, r->esp))
    {
        goto at_4e2a13;
    }
    if (rd32(r, r->esi + 0x8) != 0x0)
    {
        goto at_4e29d2;
    }
    r->eax = rd32(r, r->esp + 0x8);
    if (r->eax <= rd32(r, r->esi + 0x1c))
    {
        goto at_4e2985;
    }
    r->ecx = r->eax;
    goto at_4e2988;
at_4e2985:
    r->ecx = rd32(r, r->esi + 0x1c);
at_4e2988:
    r->eax = rd32(r, r->esi + 0x2c);
    wr32(r, r->esp + 0x14, 0x0);
    wr32(r, r->esp + 0x10, r->eax);
at_4e2997:
    r->eax = rd32(r, r->esi + 0x20);
    r->ebp = rd32(r, r->eax);
    r->edx = rd32(r, r->esp + 0x10);
    r->ebx = r->ecx;
    call_mem(r, rd32(r, r->ebp + 0x3c), 0);
    wr32(r, r->esp + 0x10, rd32(r, r->esp + 0x10) + r->eax);
    wr32(r, r->esp + 0x14, rd32(r, r->esp + 0x14) + r->eax);
    r->ecx = r->ecx - r->eax;
    if (r->eax == 0)
    {
        goto at_4e29c1;
    }
    if (r->ecx == 0)
    {
        goto at_4e29c1;
    }
    r->eax = rd32(r, r->esp + 0x14);
    if (r->eax < rd32(r, r->esp + 0x8) && !r->port->env.failed)
    {
        goto at_4e2997;
    }
at_4e29c1:
    r->edx = rd32(r, r->esp + 0x14);
    r->eax = rd32(r, r->esi + 0x2c);
    r->edx = r->edx + r->eax;
    wr32(r, r->esi + 0x24, r->eax);
    wr32(r, r->esi + 0x28, r->edx);
    goto at_4e29ec;
at_4e29d2:
    r->edx = r->esi + 0x28;
    r->eax = rd32(r, r->esi + 0x20);
    r->ebx = rd32(r, r->esi + 0x1c);
    push_mem(r, r->edx);
    r->ebp = rd32(r, r->eax);
    r->ecx = r->esi + 0x2c;
    r->edx = 0;
    call_mem(r, rd32(r, r->ebp + 0x58), 1);
    r->eax = rd32(r, r->esi + 0x2c);
    wr32(r, r->esi + 0x24, r->eax);
at_4e29ec:
    r->eax = rd32(r, r->esi + 0x28);
    r->eax = r->eax - rd32(r, r->esi + 0x24);
    if (r->eax <= rd32(r, r->esp + 0x8))
    {
        goto at_4e29fe;
    }
    r->ecx = rd32(r, r->esp + 0x8);
    goto at_4e2a00;
at_4e29fe:
    r->ecx = r->eax;
at_4e2a00:
    r->ebx = r->ecx;
    r->eax = r->edi;
    r->edx = rd32(r, r->esi + 0x24);
    call_mem_keep(r, 0x4eb5e0, 8);
    wr32(r, r->esp + 0x8, rd32(r, r->esp + 0x8) - r->ecx);
    wr32(r, r->esi + 0x24, rd32(r, r->esi + 0x24) + r->ecx);
at_4e2a13:
    r->eax = rd32(r, r->esp + 0x4);
    r->eax = r->eax - rd32(r, r->esp + 0x8);
at_4e2a1b:
    r->esp = r->esp + 0x18;
    r->ebp = pop_mem(r);
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    r->ecx = pop_mem(r);
    return;
    wr8(r, r->eax, rd8(r, r->eax) + (r->eax & 0xff));
    wr8(r, r->eax, rd8(r, r->eax) + (r->eax & 0xff));
    wr8(r, r->eax, rd8(r, r->eax) + (r->eax & 0xff));
    wr8(r, r->eax, rd8(r, r->eax) + (r->eax & 0xff));
    wr8(r, r->eax, rd8(r, r->eax) + (r->eax & 0xff));
    wr8(r, r->eax, rd8(r, r->eax) + (r->eax & 0xff));
    wr8(r, r->ecx + 0x56, rd8(r, r->ecx + 0x56) + (r->edx & 0xff));
    push_mem(r, r->edi);
    push_mem(r, r->ebp);
    r->esp = r->esp - 0x4;
    r->esi = r->eax;
    wr32(r, r->esp, r->edx);
    r->edi = r->ebx;
    if (r->ebx == 0)
    {
        goto at_4e2ac6;
    }
    r->eax = rd32(r, r->eax + 0x28);
    r->eax = r->eax - rd32(r, r->esi + 0x24);
    if (r->ebx >= r->eax)
    {
        goto at_4e2a54;
    }
    r->ecx = r->ebx;
    goto at_4e2a56;
at_4e2a54:
    r->ecx = r->eax;
at_4e2a56:
    r->edx = rd32(r, r->esp);
    r->ebx = r->ecx;
    r->eax = rd32(r, r->esi + 0x24);
    call_mem_keep(r, 0x4eb5e0, 8);
    r->edi = r->edi - r->ecx;
    wr32(r, r->esp, rd32(r, r->esp) + r->ecx);
    wr32(r, r->esi + 0x24, rd32(r, r->esi + 0x24) + r->ecx);
    if (r->edi == 0)
    {
        goto at_4e2ac6;
    }
    r->eax = r->esi;
    call_mem_keep(r, 0x4e2ad0, 8);
    r->edx = 0;
    r->eax = r->edi;
    div32(r, rd32(r, r->esi + 0x1c));
    r->ecx = r->edi;
    r->eax = rd32(r, r->esi + 0x20);
    r->ecx = r->ecx - r->edx;
    r->edx = rd32(r, r->esp);
    r->ebp = rd32(r, r->eax);
    r->ebx = r->ecx;
    r->edi = r->edi - r->ecx;
    call_mem(r, rd32(r, r->ebp + 0x40), 0);
    wr32(r, r->esp, rd32(r, r->esp) + r->ecx);
    if (rd32(r, r->esi + 0x8) == 0x0)
    {
        goto at_4e2ab6;
    }
    r->edx = r->esi + 0x28;
    r->eax = rd32(r, r->esi + 0x20);
    r->ebx = rd32(r, r->esi + 0x1c);
    push_mem(r, r->edx);
    r->ebp = rd32(r, r->eax);
    r->ecx = r->esi + 0x2c;
    r->edx = 0x1;
    call_mem(r, rd32(r, r->ebp + 0x58), 1);
    r->eax = rd32(r, r->esi + 0x2c);
    wr32(r, r->esi + 0x24, r->eax);
at_4e2ab6:
    r->edx = rd32(r, r->esp);
    r->ebx = r->edi;
    r->eax = rd32(r, r->esi + 0x24);
    call_mem_keep(r, 0x4eb5e0, 8);
    wr32(r, r->esi + 0x24, rd32(r, r->esi + 0x24) + r->edi);
at_4e2ac6:
    r->esp = r->esp + 0x4;
    r->ebp = pop_mem(r);
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    r->ecx = pop_mem(r);
    return;
    wr8(r, r->eax, rd8(r, r->eax) + (r->eax & 0xff));
    push_mem(r, r->ebx);
    push_mem(r, r->ecx);
    push_mem(r, r->edx);
    push_mem(r, r->esi);
    push_mem(r, r->edi);
    r->esi = r->eax;
    if ((uint8_t)(rd8(r, r->eax + 0x14) & 0x1) == 0)
    {
        goto at_4e2af9;
    }
    r->edx = rd32(r, r->eax + 0x28);
    r->edx = r->edx - rd32(r, r->eax + 0x24);
    if ((r->edx + rd32(r, r->eax + 0x24)) == rd32(r, r->eax + 0x24))
    {
        goto at_4e2af4;
    }
    r->eax = rd32(r, r->eax + 0x20);
    r->ecx = rd32(r, r->eax);
    r->ebx = 0x1;
    r->edx = 0u - r->edx;
    call_mem(r, rd32(r, r->ecx + 0x30), 5);
at_4e2af4:
    r->eax = rd32(r, r->esi + 0x28);
    goto at_4e2b51;
at_4e2af9:
    if (rd32(r, r->eax + 0x2c) == 0x0)
    {
        goto at_4e2b07;
    }
    r->eax = rd32(r, r->eax + 0x24);
    if (r->eax == rd32(r, r->esi + 0x2c))
    {
        goto at_4e2b54;
    }
at_4e2b07:
    if (rd32(r, r->esi + 0x8) != 0x0)
    {
        goto at_4e2b20;
    }
    r->eax = rd32(r, r->esi + 0x20);
    r->ebx = rd32(r, r->esi + 0x24);
    r->ecx = rd32(r, r->eax);
    r->edx = rd32(r, r->esi + 0x2c);
    r->ebx = r->ebx - rd32(r, r->esi + 0x2c);
    call_mem(r, rd32(r, r->ecx + 0x40), 0);
    goto at_4e2b4e;
at_4e2b20:
    push_mem(r, 0x0);
    r->eax = rd32(r, r->esi + 0x20);
    r->edx = 0x2;
    r->ebx = rd32(r, r->esi + 0x24);
    r->edi = rd32(r, r->eax);
    r->ecx = 0;
    r->ebx = r->ebx - rd32(r, r->esi + 0x2c);
    call_mem(r, rd32(r, r->edi + 0x58), 1);
    r->edx = r->esi + 0x28;
    r->eax = rd32(r, r->esi + 0x20);
    r->ebx = rd32(r, r->esi + 0x1c);
    push_mem(r, r->edx);
    r->edi = rd32(r, r->eax);
    r->ecx = r->esi + 0x2c;
    r->edx = 0x1;
    call_mem(r, rd32(r, r->edi + 0x58), 1);
at_4e2b4e:
    r->eax = rd32(r, r->esi + 0x2c);
at_4e2b51:
    wr32(r, r->esi + 0x24, r->eax);
at_4e2b54:
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    r->edx = pop_mem(r);
    r->ecx = pop_mem(r);
    r->ebx = pop_mem(r);
    return;
    wr8(r, r->eax, rd8(r, r->eax) + (r->eax & 0xff));
    wr8(r, r->eax, rd8(r, r->eax) + (r->eax & 0xff));
    wr8(r, r->eax, rd8(r, r->eax) + (r->eax & 0xff));
    push_mem(r, r->ebx);
    push_mem(r, r->ecx);
    push_mem(r, r->esi);
    push_mem(r, r->edi);
    push_mem(r, r->ebp);
    r->esp = r->esp - 0x8;
    r->esi = r->eax;
    wr32(r, r->esp, r->edx);
    if (rd32(r, r->eax + 0x8) != 0x0)
    {
        goto at_4e2be7;
    }
    r->eax = rd32(r, r->eax + 0x24);
    if (r->eax <= rd32(r, r->esi + 0x2c))
    {
        goto at_4e2c1a;
    }
    r->edi = rd32(r, r->esi + 0x28);
    r->edi = r->edi - rd32(r, r->esi + 0x24);
    if ((int32_t)r->edi <= 0)
    {
        goto at_4e2ba3;
    }
    r->ebx = r->edi;
    r->edx = rd32(r, r->esi + 0x24);
    r->eax = rd32(r, r->esi + 0x2c);
    call_mem_keep(r, 0x4e1140, 8);
    r->eax = rd32(r, r->esi + 0x2c);
    wr32(r, r->esi + 0x28, rd32(r, r->esi + 0x28) - r->edi);
    wr32(r, r->esi + 0x24, r->eax);
at_4e2ba3:
    wr32(r, r->esp + 0x4, r->edi);
    r->ecx = rd32(r, r->esi + 0x1c);
    r->eax = rd32(r, r->esi + 0x2c);
    r->ecx = r->ecx - r->edi;
    r->edi = r->edi + r->eax;
at_4e2bb1:
    r->eax = rd32(r, r->esi + 0x20);
    r->ebp = rd32(r, r->eax);
    r->ebx = r->ecx;
    r->edx = r->edi;
    call_mem(r, rd32(r, r->ebp + 0x3c), 0);
    wr32(r, r->esp + 0x4, rd32(r, r->esp + 0x4) + r->eax);
    r->edi = r->edi + r->eax;
    r->ecx = r->ecx - r->eax;
    if (r->eax == 0)
    {
        goto at_4e2bd6;
    }
    if (r->ecx == 0)
    {
        goto at_4e2bd6;
    }
    r->eax = rd32(r, r->esp + 0x4);
    if (r->eax < rd32(r, r->esp) && !r->port->env.failed)
    {
        goto at_4e2bb1;
    }
at_4e2bd6:
    r->edx = rd32(r, r->esp + 0x4);
    r->eax = rd32(r, r->esi + 0x2c);
    r->edx = r->edx + r->eax;
    wr32(r, r->esi + 0x24, r->eax);
    wr32(r, r->esi + 0x28, r->edx);
    goto at_4e2c1a;
at_4e2be7:
    r->ecx = rd32(r, r->eax + 0x28);
    r->ecx = r->ecx - rd32(r, r->eax + 0x24);
    if ((r->ecx + rd32(r, r->eax + 0x24)) == rd32(r, r->eax + 0x24))
    {
        goto at_4e2c00;
    }
    r->eax = rd32(r, r->eax + 0x20);
    r->edx = r->ecx;
    r->edi = rd32(r, r->eax);
    r->ebx = 0x1;
    r->edx = 0u - r->edx;
    call_mem(r, rd32(r, r->edi + 0x30), 0);
at_4e2c00:
    r->edx = r->esi + 0x28;
    r->eax = rd32(r, r->esi + 0x20);
    r->ebx = rd32(r, r->esi + 0x1c);
    push_mem(r, r->edx);
    r->edi = rd32(r, r->eax);
    r->ecx = r->esi + 0x2c;
    r->edx = 0;
    call_mem(r, rd32(r, r->edi + 0x58), 1);
    r->eax = rd32(r, r->esi + 0x2c);
    wr32(r, r->esi + 0x24, r->eax);
at_4e2c1a:
    r->eax = rd32(r, r->esi + 0x28);
    r->eax = r->eax - rd32(r, r->esi + 0x24);
    if (r->eax >= rd32(r, r->esp))
    {
        goto at_4e2c2e;
    }
    push_mem(r, 0x0);
    push_mem(r, 0x3);
    call_mem(r, 0x4e7370, 2);
at_4e2c2e:
    r->esp = r->esp + 0x8;
    r->ebp = pop_mem(r);
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    r->ecx = pop_mem(r);
    r->ebx = pop_mem(r);
    return;
    wr8(r, r->eax, rd8(r, r->eax) + (r->eax & 0xff));
    wr8(r, r->eax, rd8(r, r->eax) + (r->eax & 0xff));
    wr8(r, r->eax, rd8(r, r->eax) + (r->eax & 0xff));
    wr8(r, r->eax, rd8(r, r->eax) + (r->eax & 0xff));
    wr8(r, r->ebx + 0x51, rd8(r, r->ebx + 0x51) + (r->edx & 0xff));
    push_mem(r, r->esi);
    r->esp = r->esp - 0x4;
    r->ecx = r->eax;
    r->esi = r->edx;
    if (r->edx >= 0xffff)
    {
        goto at_4e2c70;
    }
    r->ebx = rd32(r, r->eax + 0x24);
    r->ebx = r->ebx + 0x2;
    r->edx = r->eax;
    if (r->ebx <= rd32(r, r->eax + 0x28))
    {
        goto at_4e2c64;
    }
    call_mem_keep(r, 0x4e2ad0, 8);
at_4e2c64:
    r->ecx = rd32(r, r->edx + 0x24);
    wr16(r, r->ecx, (r->esi & 0xffff));
    wr32(r, r->edx + 0x24, rd32(r, r->edx + 0x24) + 0x2);
    goto at_4e2cb3;
at_4e2c70:
    r->edx = rd32(r, r->eax + 0x24);
    wr32(r, r->esp, 0xffff);
    r->edx = r->edx + 0x2;
    r->ebx = r->eax;
    if (r->edx <= rd32(r, r->eax + 0x28))
    {
        goto at_4e2c89;
    }
    call_mem_keep(r, 0x4e2ad0, 8);
at_4e2c89:
    r->edx = rd32(r, r->ebx + 0x24);
    r->eax = rd32(r, r->esp);
    wr16(r, r->edx, (r->eax & 0xffff));
    wr32(r, r->ebx + 0x24, rd32(r, r->ebx + 0x24) + 0x2);
    r->ebx = rd32(r, r->ecx + 0x24);
    r->ebx = r->ebx + 0x4;
    r->edx = r->ecx;
    if (r->ebx <= rd32(r, r->ecx + 0x28))
    {
        goto at_4e2caa;
    }
    r->eax = r->ecx;
    call_mem_keep(r, 0x4e2ad0, 8);
at_4e2caa:
    r->ecx = rd32(r, r->edx + 0x24);
    wr32(r, r->ecx, r->esi);
    wr32(r, r->edx + 0x24, rd32(r, r->edx + 0x24) + 0x4);
at_4e2cb3:
    r->esp = r->esp + 0x4;
    r->esi = pop_mem(r);
    r->ecx = pop_mem(r);
    r->ebx = pop_mem(r);
    return;
    wr8(r, r->eax, rd8(r, r->eax) + (r->eax & 0xff));
    wr8(r, r->eax, rd8(r, r->eax) + (r->eax & 0xff));
    wr8(r, r->eax, rd8(r, r->eax) + (r->eax & 0xff));
    push_mem(r, r->ebx);
    push_mem(r, r->ecx);
    push_mem(r, r->edx);
    r->ecx = r->eax;
    r->ebx = r->eax;
    r->eax = rd32(r, r->eax + 0x24);
    r->edx = r->eax + 0x2;
    if (r->edx <= rd32(r, r->ecx + 0x28))
    {
        goto at_4e2ce7;
    }
    r->edx = rd32(r, r->ecx + 0x28);
    r->edx = r->edx - r->eax;
    r->eax = 0x2;
    r->eax = r->eax - r->edx;
    r->edx = r->eax;
    r->eax = r->ecx;
    call_mem_keep(r, 0x4e2b60, 8);
at_4e2ce7:
    r->eax = rd32(r, r->ebx + 0x24);
    r->eax = r->eax + 0x2;
    set_low16(&r->edx, rd16(r, r->eax - 0x2));
    wr32(r, r->ebx + 0x24, r->eax);
    r->eax = (r->edx & 0xffff);
    if (r->eax == 0xffff)
    {
        goto at_4e2d05;
    }
    r->eax = (r->edx & 0xffff);
    r->edx = pop_mem(r);
    r->ecx = pop_mem(r);
    r->ebx = pop_mem(r);
    return;
at_4e2d05:
    r->eax = rd32(r, r->ecx + 0x24);
    r->edx = r->eax + 0x4;
    r->ebx = r->ecx;
    if (r->edx <= rd32(r, r->ecx + 0x28))
    {
        goto at_4e2d27;
    }
    r->edx = rd32(r, r->ecx + 0x28);
    r->edx = r->edx - r->eax;
    r->eax = 0x4;
    r->eax = r->eax - r->edx;
    r->edx = r->eax;
    r->eax = r->ecx;
    call_mem_keep(r, 0x4e2b60, 8);
at_4e2d27:
    r->eax = rd32(r, r->ebx + 0x24);
    r->eax = r->eax + 0x4;
    r->edx = rd32(r, r->eax - 0x4);
    wr32(r, r->ebx + 0x24, r->eax);
    r->eax = r->edx;
    r->edx = pop_mem(r);
    r->ecx = pop_mem(r);
    r->ebx = pop_mem(r);
    return;
    wr8(r, r->eax, rd8(r, r->eax) + (r->eax & 0xff));
    wr8(r, r->eax, rd8(r, r->eax) + (r->eax & 0xff));
    wr8(r, r->eax, rd8(r, r->eax) + (r->eax & 0xff));
    wr8(r, r->ecx + 0x52, rd8(r, r->ecx + 0x52) + (r->edx & 0xff));
    if (rd32(r, r->eax + 0x30) < 0x3ffffffe)
    {
        goto at_4e2d56;
    }
    r->eax = rd32(r, r->eax + 0x10);
    push_mem(r, r->eax);
    push_mem(r, 0x5);
    call_mem(r, 0x4e7370, 2);
at_4e2d56:
    r->edx = pop_mem(r);
    r->ecx = pop_mem(r);
    return;
    wr8(r, r->eax, rd8(r, r->eax) + (r->eax & 0xff));
    wr8(r, r->eax, rd8(r, r->eax) + (r->eax & 0xff));
    wr8(r, r->eax, rd8(r, r->eax) + (r->eax & 0xff));
    wr8(r, r->ebx + 0x51, rd8(r, r->ebx + 0x51) + (r->edx & 0xff));
    push_mem(r, r->esi);
    r->ecx = r->eax;
    r->ebx = r->edx;
    r->edx = 0;
    call_mem_keep(r, 0x4e2f10, 8);
    if (r->ebx != 0)
    {
        goto at_4e2d96;
    }
    r->eax = rd32(r, r->ecx + 0x24);
    r->edx = r->ecx;
    r->eax = r->eax + 0x2;
    r->ebx = 0;
    if (r->eax <= rd32(r, r->ecx + 0x28))
    {
        goto at_4e2d88;
    }
    r->eax = r->ecx;
    call_mem_keep(r, 0x4e2ad0, 8);
at_4e2d88:
    r->eax = rd32(r, r->edx + 0x24);
    wr16(r, r->eax, (r->ebx & 0xffff));
    wr32(r, r->edx + 0x24, rd32(r, r->edx + 0x24) + 0x2);
    r->esi = pop_mem(r);
    r->ecx = pop_mem(r);
    r->ebx = pop_mem(r);
    return;
at_4e2d96:
    r->edx = r->ebx;
    r->eax = rd32(r, r->ecx + 0x34);
    call_mem_keep(r, 0x4df160, 8);
    r->esi = rd32(r, r->eax);
    if (r->esi == 0)
    {
        goto at_4e2e18;
    }
    if (r->esi >= 0x7fff)
    {
        goto at_4e2dd4;
    }
    r->eax = rd32(r, r->ecx + 0x24);
    r->eax = r->eax + 0x2;
    r->ebx = r->ecx;
    if (r->eax <= rd32(r, r->ecx + 0x28))
    {
        goto at_4e2dc6;
    }
    r->eax = r->ecx;
    call_mem_keep(r, 0x4e2ad0, 8);
at_4e2dc6:
    r->eax = rd32(r, r->ebx + 0x24);
    wr16(r, r->eax, (r->esi & 0xffff));
    wr32(r, r->ebx + 0x24, rd32(r, r->ebx + 0x24) + 0x2);
    r->esi = pop_mem(r);
    r->ecx = pop_mem(r);
    r->ebx = pop_mem(r);
    return;
at_4e2dd4:
    r->eax = rd32(r, r->ecx + 0x24);
    r->ebx = 0x7fff;
    r->eax = r->eax + 0x2;
    r->edx = r->ecx;
    if (r->eax <= rd32(r, r->ecx + 0x28))
    {
        goto at_4e2ded;
    }
    r->eax = r->ecx;
    call_mem_keep(r, 0x4e2ad0, 8);
at_4e2ded:
    r->eax = rd32(r, r->edx + 0x24);
    wr16(r, r->eax, (r->ebx & 0xffff));
    wr32(r, r->edx + 0x24, rd32(r, r->edx + 0x24) + 0x2);
    r->eax = rd32(r, r->ecx + 0x24);
    r->eax = r->eax + 0x4;
    r->ebx = r->ecx;
    if (r->eax <= rd32(r, r->ecx + 0x28))
    {
        goto at_4e2e0b;
    }
    r->eax = r->ecx;
    call_mem_keep(r, 0x4e2ad0, 8);
at_4e2e0b:
    r->eax = rd32(r, r->ebx + 0x24);
    wr32(r, r->eax, r->esi);
    wr32(r, r->ebx + 0x24, rd32(r, r->ebx + 0x24) + 0x4);
    r->esi = pop_mem(r);
    r->ecx = pop_mem(r);
    r->ebx = pop_mem(r);
    return;
at_4e2e18:
    r->edx = rd32(r, r->ebx);
    r->eax = r->ebx;
    call_mem(r, rd32(r, r->edx), 0);
    r->edx = r->eax;
    r->eax = r->ecx;
    call_mem_keep(r, 0x4e3060, 8);
    r->eax = r->ecx;
    call_mem_keep(r, 0x4e2d40, 8);
    r->esi = rd32(r, r->ecx + 0x30);
    r->eax = r->esi + 0x1;
    wr32(r, r->ecx + 0x30, r->eax);
    r->edx = r->ebx;
    r->eax = rd32(r, r->ecx + 0x34);
    call_mem_keep(r, 0x4df160, 8);
    wr32(r, r->eax, r->esi);
    r->esi = rd32(r, r->ebx);
    r->edx = r->ecx;
    r->eax = r->ebx;
    call_mem(r, rd32(r, r->esi + 0x8), 0);
    r->esi = pop_mem(r);
    r->ecx = pop_mem(r);
    r->ebx = pop_mem(r);
    return;
    push_mem(r, r->ebx);
    push_mem(r, r->ecx);
    push_mem(r, r->esi);
    push_mem(r, r->edi);
    push_mem(r, r->ebp);
    r->esp = r->esp - 0x8;
    r->esi = r->eax;
    r->ebp = r->edx;
    r->ecx = r->esp + 0x4;
    r->ebx = r->esp;
    call_mem_keep(r, 0x4e3160, 8);
    if (r->eax != 0)
    {
        goto at_4e2eb4;
    }
    r->eax = rd32(r, r->esi + 0x34);
    r->eax = rd32(r, r->eax + 0x8);
    r->eax = r->eax - 1;
    if (r->eax >= rd32(r, r->esp + 0x4))
    {
        goto at_4e2e85;
    }
    r->eax = r->esi + 0x10;
    r->eax = rd32(r, r->eax);
    push_mem(r, r->eax);
    push_mem(r, 0x5);
    call_mem(r, 0x4e7370, 2);
at_4e2e85:
    r->eax = rd32(r, r->esi + 0x34);
    r->edx = rd32(r, r->esp + 0x4);
    r->eax = rd32(r, r->eax + 0x4);
    r->eax = rd32(r, r->eax + r->edx * 4);
    r->edi = r->eax;
    if (r->eax == 0)
    {
        goto at_4e2ef8;
    }
    if (r->ebp == 0)
    {
        goto at_4e2ef8;
    }
    r->edx = r->ebp;
    call_mem_keep(r, 0x4d3010, 8);
    if (r->eax != 0)
    {
        goto at_4e2ef8;
    }
    r->eax = rd32(r, r->esi + 0x10);
    push_mem(r, r->eax);
    push_mem(r, 0x6);
    call_mem(r, 0x4e7370, 2);
    goto at_4e2ef8;
at_4e2eb4:
    call_mem_keep(r, 0x4d3040, 8);
    r->edi = r->eax;
    if (r->eax != 0)
    {
        goto at_4e2ec4;
    }
    call_mem_keep(r, 0x4d9510, 8);
at_4e2ec4:
    r->eax = r->esi;
    call_mem_keep(r, 0x4e2d40, 8);
    r->edx = rd32(r, r->esi + 0x30);
    r->eax = r->edx + 0x1;
    r->ecx = 0x1;
    wr32(r, r->esi + 0x30, r->eax);
    r->ebx = r->edi;
    r->eax = rd32(r, r->esi + 0x34);
    call_mem_keep(r, 0x4e7790, 8);
    r->eax = rd32(r, r->esp);
    r->ebx = rd32(r, r->esi + 0xc);
    wr32(r, r->esi + 0xc, r->eax);
    r->ecx = rd32(r, r->edi);
    r->edx = r->esi;
    r->eax = r->edi;
    call_mem(r, rd32(r, r->ecx + 0x8), 0);
    wr32(r, r->esi + 0xc, r->ebx);
at_4e2ef8:
    r->eax = r->edi;
    r->esp = r->esp + 0x8;
    r->ebp = pop_mem(r);
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    r->ecx = pop_mem(r);
    r->ebx = pop_mem(r);
    return;
    wr8(r, r->eax, rd8(r, r->eax) + (r->eax & 0xff));
    wr8(r, r->eax, rd8(r, r->eax) + (r->eax & 0xff));
    wr8(r, r->eax, rd8(r, r->eax) + (r->eax & 0xff));
    wr8(r, r->eax, rd8(r, r->eax) + (r->eax & 0xff));
    wr8(r, r->eax, rd8(r, r->eax) + (r->eax & 0xff));
    wr8(r, r->eax, rd8(r, r->eax) + (r->eax & 0xff));
    wr8(r, r->ebx + 0x51, rd8(r, r->ebx + 0x51) + (r->edx & 0xff));
    push_mem(r, r->esi);
    r->esp = r->esp - 0x18;
    r->ecx = r->eax;
    r->esi = r->edx;
    r->eax = r->esp;
    push_mem(r, r->port->env.chain);
    r->tmp = pop_mem(r);
    wr32(r, r->eax, r->tmp);
    r->port->env.chain = r->eax;
    wr32(r, r->esp + 0x4, 0x4ec1ec);
    wr32(r, r->esp + 0x8, 0x51bd40);
    wr32(r, r->esp + 0xc, 0x0);
    if ((uint8_t)(rd8(r, r->ecx + 0x14) & 0x1) != 0)
    {
        goto at_4e2fd8;
    }
    if (rd32(r, r->ecx + 0x34) != 0x0)
    {
        goto at_4e2fa4;
    }
    r->eax = 0x1c;
    call_mem_keep(r, 0x4ca000, 8);
    if (r->eax == 0)
    {
        goto at_4e2f7d;
    }
    wr32(r, r->esp + 0xc, 0x1);
    r->edx = rd32(r, r->ecx + 0x3c);
    wr32(r, r->esp + 0x14, r->eax);
    call_mem_keep(r, 0x4deec0, 8);
    wr32(r, r->esp + 0xc, 0x0);
at_4e2f7d:
    r->ebx = 0x1;
    r->edx = rd32(r, r->ecx + 0x40);
    wr32(r, r->ecx + 0x34, r->eax);
    call_mem_keep(r, 0x4def50, 8);
    r->eax = rd32(r, r->ecx + 0x34);
    r->edx = 0;
    call_mem_keep(r, 0x4df160, 8);
    wr32(r, r->eax, 0x0);
    wr32(r, r->ecx + 0x30, 0x1);
at_4e2fa4:
    if (r->esi == 0)
    {
        goto at_4e304b;
    }
    r->eax = r->ecx;
    call_mem_keep(r, 0x4e2d40, 8);
    r->ebx = rd32(r, r->ecx + 0x30);
    r->eax = r->ebx + 0x1;
    wr32(r, r->ecx + 0x30, r->eax);
    r->edx = r->esi;
    r->eax = rd32(r, r->ecx + 0x34);
    call_mem_keep(r, 0x4df160, 8);
    wr32(r, r->eax, r->ebx);
    r->eax = rd32(r, r->esp);
    r->port->env.chain = r->eax;
    r->esp = r->esp + 0x18;
    r->esi = pop_mem(r);
    r->ecx = pop_mem(r);
    r->ebx = pop_mem(r);
    return;
at_4e2fd8:
    if (rd32(r, r->ecx + 0x34) != 0x0)
    {
        goto at_4e3028;
    }
    r->eax = 0x14;
    call_mem_keep(r, 0x4ca000, 8);
    if (r->eax == 0)
    {
        goto at_4e3005;
    }
    wr32(r, r->esp + 0xc, 0x3);
    wr32(r, r->esp + 0x14, r->eax);
    call_mem_keep(r, 0x4e7540, 8);
    wr32(r, r->esp + 0xc, 0x0);
at_4e3005:
    r->edx = 0x1;
    r->ebx = rd32(r, r->ecx + 0x3c);
    wr32(r, r->ecx + 0x34, r->eax);
    call_mem_keep(r, 0x4e7660, 8);
    r->eax = rd32(r, r->ecx + 0x34);
    r->eax = rd32(r, r->eax + 0x4);
    wr32(r, r->eax, 0x0);
    wr32(r, r->ecx + 0x30, 0x1);
at_4e3028:
    if (r->esi == 0)
    {
        goto at_4e304b;
    }
    r->eax = r->ecx;
    call_mem_keep(r, 0x4e2d40, 8);
    r->edx = rd32(r, r->ecx + 0x30);
    r->eax = r->edx + 0x1;
    wr32(r, r->ecx + 0x30, r->eax);
    r->ebx = r->esi;
    r->eax = rd32(r, r->ecx + 0x34);
    r->ecx = 0x1;
    call_mem_keep(r, 0x4e7790, 8);
at_4e304b:
    r->eax = rd32(r, r->esp);
    r->port->env.chain = r->eax;
    r->esp = r->esp + 0x18;
    r->esi = pop_mem(r);
    r->ecx = pop_mem(r);
    r->ebx = pop_mem(r);
    return;
    wr8(r, r->eax, rd8(r, r->eax) + (r->eax & 0xff));
    wr8(r, r->eax, rd8(r, r->eax) + (r->eax & 0xff));
    wr8(r, r->ebx + 0x51, rd8(r, r->ebx + 0x51) + (r->edx & 0xff));
    push_mem(r, r->esi);
    r->ebx = r->eax;
    r->esi = r->edx;
    if (rd32(r, r->edx + 0x8) != 0xffff)
    {
        goto at_4e3075;
    }
    call_mem_keep(r, 0x4d9530, 8);
at_4e3075:
    r->eax = r->ebx;
    r->edx = 0;
    call_mem_keep(r, 0x4e2f10, 8);
    r->edx = r->esi;
    r->eax = rd32(r, r->ebx + 0x34);
    call_mem_keep(r, 0x4df160, 8);
    r->edx = rd32(r, r->eax);
    if (r->edx == 0)
    {
        goto at_4e310d;
    }
    if (r->edx >= 0x7fff)
    {
        goto at_4e30c1;
    }
    set_high8(&r->edx, ((r->edx >> 8) & 0xff) | 0x80);
    r->eax = rd32(r, r->ebx + 0x24);
    r->ecx = r->edx;
    r->eax = r->eax + 0x2;
    r->edx = r->ebx;
    if (r->eax <= rd32(r, r->ebx + 0x28))
    {
        goto at_4e30b3;
    }
    r->eax = r->ebx;
    call_mem_keep(r, 0x4e2ad0, 8);
at_4e30b3:
    r->eax = rd32(r, r->edx + 0x24);
    wr16(r, r->eax, (r->ecx & 0xffff));
    wr32(r, r->edx + 0x24, rd32(r, r->edx + 0x24) + 0x2);
    r->esi = pop_mem(r);
    r->ecx = pop_mem(r);
    r->ebx = pop_mem(r);
    return;
at_4e30c1:
    r->eax = rd32(r, r->ebx + 0x24);
    r->ecx = 0x7fff;
    r->eax = r->eax + 0x2;
    r->esi = r->ebx;
    if (r->eax <= rd32(r, r->ebx + 0x28))
    {
        goto at_4e30da;
    }
    r->eax = r->ebx;
    call_mem_keep(r, 0x4e2ad0, 8);
at_4e30da:
    r->eax = rd32(r, r->esi + 0x24);
    wr16(r, r->eax, (r->ecx & 0xffff));
    wr32(r, r->esi + 0x24, rd32(r, r->esi + 0x24) + 0x2);
    r->ecx = r->edx;
    r->eax = rd32(r, r->ebx + 0x24);
    r->ecx = r->ecx | 0x80000000u;
    r->eax = r->eax + 0x4;
    r->edx = r->ebx;
    if (r->eax <= rd32(r, r->ebx + 0x28))
    {
        goto at_4e3100;
    }
    r->eax = r->ebx;
    call_mem_keep(r, 0x4e2ad0, 8);
at_4e3100:
    r->eax = rd32(r, r->edx + 0x24);
    wr32(r, r->eax, r->ecx);
    wr32(r, r->edx + 0x24, rd32(r, r->edx + 0x24) + 0x4);
    r->esi = pop_mem(r);
    r->ecx = pop_mem(r);
    r->ebx = pop_mem(r);
    return;
at_4e310d:
    r->eax = rd32(r, r->ebx + 0x24);
    r->ecx = 0xffff;
    r->eax = r->eax + 0x2;
    r->edx = r->ebx;
    if (r->eax <= rd32(r, r->ebx + 0x28))
    {
        goto at_4e3126;
    }
    r->eax = r->ebx;
    call_mem_keep(r, 0x4e2ad0, 8);
at_4e3126:
    r->eax = rd32(r, r->edx + 0x24);
    wr16(r, r->eax, (r->ecx & 0xffff));
    r->eax = r->esi;
    wr32(r, r->edx + 0x24, rd32(r, r->edx + 0x24) + 0x2);
    r->edx = r->ebx;
    call_mem_keep(r, 0x4e2860, 8);
    r->eax = r->ebx;
    call_mem_keep(r, 0x4e2d40, 8);
    r->ecx = rd32(r, r->ebx + 0x30);
    r->eax = r->ecx + 0x1;
    wr32(r, r->ebx + 0x30, r->eax);
    r->edx = r->esi;
    r->eax = rd32(r, r->ebx + 0x34);
    call_mem_keep(r, 0x4df160, 8);
    wr32(r, r->eax, r->ecx);
    r->esi = pop_mem(r);
    r->ecx = pop_mem(r);
    r->ebx = pop_mem(r);
    return;
    wr8(r, r->eax, rd8(r, r->eax) + (r->eax & 0xff));
    wr8(r, r->eax, rd8(r, r->eax) + (r->eax & 0xff));
    wr8(r, r->eax, rd8(r, r->eax) + (r->eax & 0xff));
    wr8(r, r->esi + 0x57, rd8(r, r->esi + 0x57) + (r->edx & 0xff));
    push_mem(r, r->ebp);
    r->esp = r->esp - 0x30;
    r->esi = r->eax;
    r->ebp = r->edx;
    wr32(r, r->esp + 0x20, r->ebx);
    wr32(r, r->esp + 0x24, r->ecx);
    r->eax = r->esp;
    push_mem(r, r->port->env.chain);
    r->tmp = pop_mem(r);
    wr32(r, r->eax, r->tmp);
    r->port->env.chain = r->eax;
    wr32(r, r->esp + 0x4, 0x4ec1ec);
    wr32(r, r->esp + 0x8, 0x51bd5c);
    wr32(r, r->esp + 0xc, 0x0);
    if (r->edx == 0)
    {
        goto at_4e31ad;
    }
    if (rd32(r, r->edx + 0x8) != 0xffff)
    {
        goto at_4e31ad;
    }
    call_mem_keep(r, 0x4d9530, 8);
at_4e31ad:
    r->eax = r->esi;
    r->edx = 0;
    call_mem_keep(r, 0x4e2f10, 8);
    r->eax = rd32(r, r->esi + 0x24);
    r->edx = r->eax + 0x2;
    r->edi = r->esi;
    if (r->edx <= rd32(r, r->esi + 0x28))
    {
        goto at_4e31d8;
    }
    r->edx = rd32(r, r->esi + 0x28);
    r->edx = r->edx - r->eax;
    r->eax = 0x2;
    r->eax = r->eax - r->edx;
    r->edx = r->eax;
    r->eax = r->esi;
    call_mem_keep(r, 0x4e2b60, 8);
at_4e31d8:
    r->eax = rd32(r, r->edi + 0x24);
    set_low16(&r->edx, rd16(r, r->eax));
    r->eax = r->eax + 0x2;
    wr16(r, r->esp + 0x2c, (r->edx & 0xffff));
    wr32(r, r->edi + 0x24, r->eax);
    if ((uint16_t)((r->edx & 0xffff)) != (uint16_t)0x7fff)
    {
        goto at_4e3223;
    }
    r->eax = rd32(r, r->esi + 0x24);
    r->edx = r->eax + 0x4;
    r->edi = r->esi;
    if (r->edx <= rd32(r, r->esi + 0x28))
    {
        goto at_4e3212;
    }
    r->edx = rd32(r, r->esi + 0x28);
    r->edx = r->edx - r->eax;
    r->eax = 0x4;
    r->eax = r->eax - r->edx;
    r->edx = r->eax;
    r->eax = r->esi;
    call_mem_keep(r, 0x4e2b60, 8);
at_4e3212:
    r->eax = rd32(r, r->edi + 0x24);
    r->edx = rd32(r, r->eax);
    r->eax = r->eax + 0x4;
    wr32(r, r->esp + 0x28, r->edx);
    wr32(r, r->edi + 0x24, r->eax);
    goto at_4e3240;
at_4e3223:
    r->eax = r->edx;
    set_low8(&r->eax, (r->eax & 0xff) ^ (r->edx & 0xff));
    set_high8(&r->eax, ((r->eax >> 8) & 0xff) & 0x80);
    r->eax = (r->eax & 0xffff);
    r->edx = r->eax;
    r->eax = rd16(r, r->esp + 0x2c);
    r->edx = r->edx << 0x10;
    set_high8(&r->eax, ((r->eax >> 8) & 0xff) & 0x7f);
    r->edx = r->edx | r->eax;
    wr32(r, r->esp + 0x28, r->edx);
at_4e3240:
    r->ebx = r->esi + 0x10;
    if ((uint8_t)(rd8(r, r->esp + 0x2b) & 0x80) != 0)
    {
        goto at_4e326c;
    }
    if (rd32(r, r->esp + 0x24) != 0x0)
    {
        goto at_4e325b;
    }
    r->eax = rd32(r, r->ebx);
    push_mem(r, r->eax);
    push_mem(r, 0x5);
    call_mem(r, 0x4e7370, 2);
at_4e325b:
    r->edx = rd32(r, r->esp + 0x24);
    r->eax = rd32(r, r->esp + 0x28);
    wr32(r, r->edx, r->eax);
    r->edx = 0;
    goto at_4e33be;
at_4e326c:
    if ((uint16_t)rd16(r, r->esp + 0x2c) != (uint16_t)0xffffffffu)
    {
        goto at_4e331c;
    }
    r->eax = r->esp + 0x14;
    push_mem(r, r->eax);
    push_mem(r, r->esi);
    call_mem(r, 0x4e2780, 2);
    r->edi = r->eax;
    if (r->eax != 0)
    {
        goto at_4e3293;
    }
    r->eax = rd32(r, r->ebx);
    push_mem(r, r->eax);
    push_mem(r, 0x6);
    call_mem(r, 0x4e7370, 2);
at_4e3293:
    r->eax = rd32(r, r->edi + 0x8);
    r->eax = r->eax & 0x7fffffff;
    if (r->eax == rd32(r, r->esp + 0x14))
    {
        goto at_4e32fb;
    }
    if ((uint8_t)(rd8(r, r->edi + 0xb) & 0x80) != 0)
    {
        goto at_4e32b6;
    }
    r->eax = r->esi + 0x10;
    r->eax = rd32(r, r->eax);
    push_mem(r, r->eax);
    push_mem(r, 0x7);
    call_mem(r, 0x4e7370, 2);
    goto at_4e32fb;
at_4e32b6:
    if (rd32(r, r->esi + 0x38) != 0x0)
    {
        goto at_4e32eb;
    }
    r->eax = 0x1c;
    call_mem_keep(r, 0x4ca000, 8);
    if (r->eax == 0)
    {
        goto at_4e32e8;
    }
    wr32(r, r->esp + 0xc, 0x1);
    r->edx = 0xa;
    wr32(r, r->esp + 0x18, r->eax);
    call_mem_keep(r, 0x4deec0, 8);
    wr32(r, r->esp + 0xc, 0x0);
at_4e32e8:
    wr32(r, r->esi + 0x38, r->eax);
at_4e32eb:
    r->edx = r->edi;
    r->eax = rd32(r, r->esi + 0x38);
    r->ebx = rd32(r, r->esp + 0x14);
    call_mem_keep(r, 0x4df160, 8);
    wr32(r, r->eax, r->ebx);
at_4e32fb:
    r->eax = r->esi;
    call_mem_keep(r, 0x4e2d40, 8);
    r->edx = rd32(r, r->esi + 0x30);
    r->eax = r->edx + 0x1;
    r->ecx = 0x1;
    wr32(r, r->esi + 0x30, r->eax);
    r->ebx = r->edi;
    r->eax = rd32(r, r->esi + 0x34);
    call_mem_keep(r, 0x4e7790, 8);
    goto at_4e3373;
at_4e331c:
    r->ebx = rd32(r, r->esp + 0x28);
    r->ebx = r->ebx & 0x7fffffff;
    if (r->ebx == 0)
    {
        goto at_4e3333;
    }
    r->eax = rd32(r, r->esi + 0x34);
    r->eax = rd32(r, r->eax + 0x8);
    r->eax = r->eax - 1;
    if (r->ebx <= r->eax)
    {
        goto at_4e3340;
    }
at_4e3333:
    r->eax = r->esi + 0x10;
    r->eax = rd32(r, r->eax);
    push_mem(r, r->eax);
    push_mem(r, 0x5);
    call_mem(r, 0x4e7370, 2);
at_4e3340:
    r->eax = rd32(r, r->esi + 0x34);
    r->eax = rd32(r, r->eax + 0x4);
    r->edx = rd32(r, r->eax + r->ebx * 4);
    r->edi = r->edx;
    if (rd32(r, r->esi + 0x38) == 0x0)
    {
        goto at_4e3367;
    }
    r->ebx = r->esp + 0x1c;
    r->eax = rd32(r, r->esi + 0x38);
    call_mem_keep(r, 0x4df140, 8);
    if (r->eax == 0)
    {
        goto at_4e3367;
    }
    r->eax = rd32(r, r->esp + 0x1c);
    goto at_4e336f;
at_4e3367:
    r->eax = rd32(r, r->edi + 0x8);
    r->eax = r->eax & 0x7fffffff;
at_4e336f:
    wr32(r, r->esp + 0x14, r->eax);
at_4e3373:
    if (r->ebp == 0)
    {
        goto at_4e3391;
    }
    r->edx = r->ebp;
    r->eax = r->edi;
    call_mem_keep(r, 0x4d3120, 8);
    if (r->eax != 0)
    {
        goto at_4e3391;
    }
    r->eax = r->esi + 0x10;
    r->eax = rd32(r, r->eax);
    push_mem(r, r->eax);
    push_mem(r, 0x6);
    call_mem(r, 0x4e7370, 2);
at_4e3391:
    if (rd32(r, r->esp + 0x20) == 0x0)
    {
        goto at_4e33a4;
    }
    r->edx = rd32(r, r->esp + 0x20);
    r->eax = rd32(r, r->esp + 0x14);
    wr32(r, r->edx, r->eax);
    goto at_4e33ab;
at_4e33a4:
    r->eax = rd32(r, r->esp + 0x14);
    wr32(r, r->esi + 0xc, r->eax);
at_4e33ab:
    if (rd32(r, r->esp + 0x24) == 0x0)
    {
        goto at_4e33bc;
    }
    r->edx = rd32(r, r->esp + 0x24);
    r->eax = rd32(r, r->esp + 0x28);
    wr32(r, r->edx, r->eax);
at_4e33bc:
    r->edx = r->edi;
at_4e33be:
    r->eax = rd32(r, r->esp);
    r->port->env.chain = r->eax;
    r->eax = r->edx;
    r->esp = r->esp + 0x30;
    r->ebp = pop_mem(r);
    r->edi = pop_mem(r);
    r->esi = pop_mem(r);
    return;
}

uint32_t vertrix_port_rtl_format_output_4e2434(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x60
    };
    Port port;
    uint8_t stack[BELOW + 8 + 4 * 21];
    Regs r;
    port_open_arguments(&port, stack, calls, services, globals, entry, BELOW, 21);
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
