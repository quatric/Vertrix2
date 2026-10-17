#include "port_rtldplayerrors.h"

/* Returns the name of a DirectPlay result code (S_OK, DPNERR_ABORTED, ...) for the error messages.
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

static uint32_t rd32(Regs *r, uint32_t address)
{
    return port_u32(r->port, address, 0);
}

static void wr32(Regs *r, uint32_t address, uint32_t value)
{
    port_set32(r->port, address, 0, value);
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

/* Original 0x480080: Returns the name of a DirectPlay result code (S_OK, DPNERR_ABORTED, ...) for
 * the error messages. Evidence: reads 0x4f1b24. Register-for-register from the listing
 * (0x480080..0x480722); labels are the original addresses. */
static void run(Regs *r)
{
    push_mem(r, r->ecx);
    r->eax = r->edx;
    flags(r, F_SUB, r->edx, 0x80158290u, 32);
    if (cond(r, CC_AE))
    {
        goto at_4802bf;
    }
    flags(r, F_SUB, r->edx, 0x80158120u, 32);
    if (cond(r, CC_AE))
    {
        goto at_480526;
    }
    flags(r, F_SUB, r->edx, 0x80158030u, 32);
    if (cond(r, CC_AE))
    {
        goto at_480642;
    }
    flags(r, F_SUB, r->edx, 0x80004002u, 32);
    if (cond(r, CC_AE))
    {
        goto at_4806c8;
    }
    flags(r, F_SUB, r->edx, 0x15800e, 32);
    if (cond(r, CC_AE))
    {
        goto at_480710;
    }
    if (r->edx != 0)
    {
        goto at_4802fd;
    }
    r->eax = 0x50f0b0;
    r->ecx = pop_mem(r);
    return;
at_4800ce:
    r->eax = 0x50f0b5;
    r->ecx = pop_mem(r);
    return;
at_4800d5:
    r->eax = 0x50f0c4;
    r->ecx = pop_mem(r);
    return;
at_4800dc:
    r->eax = 0x50f0d6;
    r->ecx = pop_mem(r);
    return;
at_4800e3:
    r->eax = 0x50f0ec;
    r->ecx = pop_mem(r);
    return;
at_4800ea:
    r->eax = 0x50f104;
    r->ecx = pop_mem(r);
    return;
at_4800f1:
    r->eax = 0x50f120;
    r->ecx = pop_mem(r);
    return;
at_4800f8:
    r->eax = 0x50f13a;
    r->ecx = pop_mem(r);
    return;
at_4800ff:
    r->eax = 0x50f153;
    r->ecx = pop_mem(r);
    return;
at_480106:
    r->eax = 0x50f169;
    r->ecx = pop_mem(r);
    return;
at_48010d:
    r->eax = 0x50f17d;
    r->ecx = pop_mem(r);
    return;
at_480114:
    r->eax = 0x50f194;
    r->ecx = pop_mem(r);
    return;
at_48011b:
    r->eax = 0x50f1ac;
    r->ecx = pop_mem(r);
    return;
at_480122:
    r->eax = 0x50f1c9;
    r->ecx = pop_mem(r);
    return;
at_480129:
    r->eax = 0x50f1db;
    r->ecx = pop_mem(r);
    return;
at_480130:
    r->eax = 0x50f1f1;
    r->ecx = pop_mem(r);
    return;
at_480137:
    r->eax = 0x50f203;
    r->ecx = pop_mem(r);
    return;
at_48013e:
    r->eax = 0x50f217;
    r->ecx = pop_mem(r);
    return;
at_480145:
    r->eax = 0x50f22b;
    r->ecx = pop_mem(r);
    return;
at_48014c:
    r->eax = 0x50f243;
    r->ecx = pop_mem(r);
    return;
at_480153:
    r->eax = 0x50f25f;
    r->ecx = pop_mem(r);
    return;
at_48015a:
    r->eax = 0x50f278;
    r->ecx = pop_mem(r);
    return;
at_480161:
    r->eax = 0x50f294;
    r->ecx = pop_mem(r);
    return;
at_480168:
    r->eax = 0x50f2a5;
    r->ecx = pop_mem(r);
    return;
at_48016f:
    r->eax = 0x50f2b4;
    r->ecx = pop_mem(r);
    return;
at_480176:
    r->eax = 0x50f2c9;
    r->ecx = pop_mem(r);
    return;
at_48017d:
    r->eax = 0x50f2d8;
    r->ecx = pop_mem(r);
    return;
at_480184:
    r->eax = 0x50f2f6;
    r->ecx = pop_mem(r);
    return;
at_48018b:
    r->eax = 0x50f313;
    r->ecx = pop_mem(r);
    return;
at_480192:
    r->eax = 0x50f32c;
    r->ecx = pop_mem(r);
    return;
at_480199:
    r->eax = 0x50f348;
    r->ecx = pop_mem(r);
    return;
at_4801a0:
    r->eax = 0x50f362;
    r->ecx = pop_mem(r);
    return;
at_4801a7:
    r->eax = 0x50f378;
    r->ecx = pop_mem(r);
    return;
at_4801ae:
    r->eax = 0x50f394;
    r->ecx = pop_mem(r);
    return;
at_4801b5:
    r->eax = 0x50f3ab;
    r->ecx = pop_mem(r);
    return;
at_4801bc:
    r->eax = 0x50f3bf;
    r->ecx = pop_mem(r);
    return;
at_4801c3:
    r->eax = 0x50f3d3;
    r->ecx = pop_mem(r);
    return;
at_4801ca:
    r->eax = 0x50f3e8;
    r->ecx = pop_mem(r);
    return;
at_4801d1:
    r->eax = 0x50f402;
    r->ecx = pop_mem(r);
    return;
at_4801d8:
    r->eax = 0x50f419;
    r->ecx = pop_mem(r);
    return;
at_4801df:
    r->eax = 0x50f431;
    r->ecx = pop_mem(r);
    return;
at_4801e6:
    r->eax = 0x50f446;
    r->ecx = pop_mem(r);
    return;
at_4801ed:
    r->eax = 0x50f45a;
    r->ecx = pop_mem(r);
    return;
at_4801f4:
    r->eax = 0x50f471;
    r->ecx = pop_mem(r);
    return;
at_4801fb:
    r->eax = 0x50f486;
    r->ecx = pop_mem(r);
    return;
at_480202:
    r->eax = 0x50f49c;
    r->ecx = pop_mem(r);
    return;
at_480209:
    r->eax = 0x50f4b3;
    r->ecx = pop_mem(r);
    return;
at_480210:
    r->eax = 0x50f4c8;
    r->ecx = pop_mem(r);
    return;
at_480217:
    r->eax = 0x50f4da;
    r->ecx = pop_mem(r);
    return;
at_48021e:
    r->eax = 0x50f4f0;
    r->ecx = pop_mem(r);
    return;
at_480225:
    r->eax = 0x50f4fe;
    r->ecx = pop_mem(r);
    return;
at_48022c:
    r->eax = 0x50f512;
    r->ecx = pop_mem(r);
    return;
at_480233:
    r->eax = 0x50f526;
    r->ecx = pop_mem(r);
    return;
at_48023a:
    r->eax = 0x50f539;
    r->ecx = pop_mem(r);
    return;
at_480241:
    r->eax = 0x50f558;
    r->ecx = pop_mem(r);
    return;
at_480248:
    r->eax = 0x50f56a;
    r->ecx = pop_mem(r);
    return;
at_48024f:
    r->eax = 0x50f57c;
    r->ecx = pop_mem(r);
    return;
at_480256:
    r->eax = 0x50f58b;
    r->ecx = pop_mem(r);
    return;
at_48025d:
    r->eax = 0x50f59b;
    r->ecx = pop_mem(r);
    return;
at_480264:
    r->eax = 0x50f5b0;
    r->ecx = pop_mem(r);
    return;
at_48026b:
    r->eax = 0x50f5c3;
    r->ecx = pop_mem(r);
    return;
at_480272:
    r->eax = 0x50f5d2;
    r->ecx = pop_mem(r);
    return;
at_480279:
    r->eax = 0x50f5ee;
    r->ecx = pop_mem(r);
    return;
at_480280:
    r->eax = 0x50f600;
    r->ecx = pop_mem(r);
    return;
at_480287:
    r->eax = 0x50f618;
    r->ecx = pop_mem(r);
    return;
at_48028e:
    r->eax = 0x50f632;
    r->ecx = pop_mem(r);
    return;
at_480295:
    r->eax = 0x50f646;
    r->ecx = pop_mem(r);
    return;
at_48029c:
    r->eax = 0x50f659;
    r->ecx = pop_mem(r);
    return;
at_4802a3:
    r->eax = 0x50f66a;
    r->ecx = pop_mem(r);
    return;
at_4802aa:
    r->eax = 0x50f67a;
    r->ecx = pop_mem(r);
    return;
at_4802b1:
    r->eax = 0x50f68f;
    r->ecx = pop_mem(r);
    return;
at_4802b8:
    r->eax = 0x50f6a2;
    r->ecx = pop_mem(r);
    return;
at_4802bf:
    if (cond(r, CC_BE) && !r->port->env.failed)
    {
        goto at_480192;
    }
    flags(r, F_SUB, r->edx, 0x80158470u, 32);
    if (cond(r, CC_AE))
    {
        goto at_480319;
    }
    flags(r, F_SUB, r->edx, 0x80158380u, 32);
    if (cond(r, CC_AE))
    {
        goto at_480441;
    }
    flags(r, F_SUB, r->edx, 0x80158330u, 32);
    if (cond(r, CC_AE))
    {
        goto at_4804c7;
    }
    flags(r, F_SUB, r->edx, 0x80158310u, 32);
    if (cond(r, CC_AE))
    {
        goto at_48050f;
    }
    if (r->edx == 0x80158300u && !r->port->env.failed)
    {
        goto at_480199;
    }
at_4802fd:
    push_mem(r, r->edx);
    push_mem(r, 0x50f6b4);
    push_mem(r, 0x558c90);
    call_mem(r, rd32(r, 0x4f1b24), 3);
    r->eax = 0x558c90;
    r->esp = r->esp + 0xc;
    r->ecx = pop_mem(r);
    return;
at_480319:
    if (cond(r, CC_BE) && !r->port->env.failed)
    {
        goto at_48021e;
    }
    flags(r, F_SUB, r->edx, 0x80158560u, 32);
    if (cond(r, CC_AE))
    {
        goto at_48034d;
    }
    flags(r, F_SUB, r->edx, 0x80158510u, 32);
    if (cond(r, CC_AE))
    {
        goto at_4803e2;
    }
    flags(r, F_SUB, r->edx, 0x80158490u, 32);
    if (cond(r, CC_AE))
    {
        goto at_48042a;
    }
    if (r->edx == 0x80158480u && !r->port->env.failed)
    {
        goto at_480225;
    }
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4802fd;
at_48034d:
    if (cond(r, CC_BE) && !r->port->env.failed)
    {
        goto at_480272;
    }
    flags(r, F_SUB, r->edx, 0x80158610u, 32);
    if (cond(r, CC_AE))
    {
        goto at_480371;
    }
    flags(r, F_SUB, r->edx, 0x80158580u, 32);
    if (cond(r, CC_AE))
    {
        goto at_4803b9;
    }
    if (r->edx == 0x80158570u && !r->port->env.failed)
    {
        goto at_480279;
    }
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4802fd;
at_480371:
    if (cond(r, CC_BE) && !r->port->env.failed)
    {
        goto at_480295;
    }
    flags(r, F_SUB, r->edx, 0x80158630u, 32);
    if (cond(r, CC_AE))
    {
        goto at_480390;
    }
    if (r->edx == 0x80158620u && !r->port->env.failed)
    {
        goto at_48029c;
    }
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4802fd;
at_480390:
    if (cond(r, CC_BE) && !r->port->env.failed)
    {
        goto at_4802a3;
    }
    flags(r, F_SUB, r->edx, 0x80158640u, 32);
    if (cond(r, CC_B) && !r->port->env.failed)
    {
        goto at_4802fd;
    }
    if (cond(r, CC_BE) && !r->port->env.failed)
    {
        goto at_4802aa;
    }
    if (r->edx == 0x80158650u && !r->port->env.failed)
    {
        goto at_4802b8;
    }
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4802fd;
at_4803b9:
    if (cond(r, CC_BE) && !r->port->env.failed)
    {
        goto at_480280;
    }
    flags(r, F_SUB, r->edx, 0x80158590u, 32);
    if (cond(r, CC_B) && !r->port->env.failed)
    {
        goto at_4802fd;
    }
    if (cond(r, CC_BE) && !r->port->env.failed)
    {
        goto at_480287;
    }
    if (r->edx == 0x80158600u && !r->port->env.failed)
    {
        goto at_48028e;
    }
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4802fd;
at_4803e2:
    if (cond(r, CC_BE) && !r->port->env.failed)
    {
        goto at_480241;
    }
    flags(r, F_SUB, r->edx, 0x80158530u, 32);
    if (cond(r, CC_AE))
    {
        goto at_480401;
    }
    if (r->edx == 0x80158520u && !r->port->env.failed)
    {
        goto at_480248;
    }
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4802fd;
at_480401:
    if (cond(r, CC_BE) && !r->port->env.failed)
    {
        goto at_48024f;
    }
    flags(r, F_SUB, r->edx, 0x80158540u, 32);
    if (cond(r, CC_B) && !r->port->env.failed)
    {
        goto at_4802fd;
    }
    if (cond(r, CC_BE) && !r->port->env.failed)
    {
        goto at_480256;
    }
    if (r->edx == 0x80158550u && !r->port->env.failed)
    {
        goto at_48025d;
    }
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4802fd;
at_48042a:
    if (cond(r, CC_BE) && !r->port->env.failed)
    {
        goto at_48022c;
    }
    if (r->edx == 0x80158500u && !r->port->env.failed)
    {
        goto at_48023a;
    }
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4802fd;
at_480441:
    if (cond(r, CC_BE) && !r->port->env.failed)
    {
        goto at_4801d1;
    }
    flags(r, F_SUB, r->edx, 0x80158420u, 32);
    if (cond(r, CC_AE))
    {
        goto at_480468;
    }
    flags(r, F_SUB, r->edx, 0x80158400u, 32);
    if (cond(r, CC_AE))
    {
        goto at_4804b0;
    }
    if (r->edx == 0x80158390u && !r->port->env.failed)
    {
        goto at_4801d8;
    }
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4802fd;
at_480468:
    if (cond(r, CC_BE) && !r->port->env.failed)
    {
        goto at_4801f4;
    }
    flags(r, F_SUB, r->edx, 0x80158440u, 32);
    if (cond(r, CC_AE))
    {
        goto at_480487;
    }
    if (r->edx == 0x80158430u && !r->port->env.failed)
    {
        goto at_480202;
    }
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4802fd;
at_480487:
    if (cond(r, CC_BE) && !r->port->env.failed)
    {
        goto at_480209;
    }
    flags(r, F_SUB, r->edx, 0x80158450u, 32);
    if (cond(r, CC_B) && !r->port->env.failed)
    {
        goto at_4802fd;
    }
    if (cond(r, CC_BE) && !r->port->env.failed)
    {
        goto at_480210;
    }
    if (r->edx == 0x80158460u && !r->port->env.failed)
    {
        goto at_480217;
    }
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4802fd;
at_4804b0:
    if (cond(r, CC_BE) && !r->port->env.failed)
    {
        goto at_4801df;
    }
    if (r->edx == 0x80158410u && !r->port->env.failed)
    {
        goto at_4801ed;
    }
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4802fd;
at_4804c7:
    if (cond(r, CC_BE) && !r->port->env.failed)
    {
        goto at_4801ae;
    }
    flags(r, F_SUB, r->edx, 0x80158350u, 32);
    if (cond(r, CC_AE))
    {
        goto at_4804e6;
    }
    if (r->edx == 0x80158340u && !r->port->env.failed)
    {
        goto at_4801b5;
    }
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4802fd;
at_4804e6:
    if (cond(r, CC_BE) && !r->port->env.failed)
    {
        goto at_4801bc;
    }
    flags(r, F_SUB, r->edx, 0x80158360u, 32);
    if (cond(r, CC_B) && !r->port->env.failed)
    {
        goto at_4802fd;
    }
    if (cond(r, CC_BE) && !r->port->env.failed)
    {
        goto at_4801c3;
    }
    if (r->edx == 0x80158370u && !r->port->env.failed)
    {
        goto at_4801ca;
    }
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4802fd;
at_48050f:
    if (cond(r, CC_BE) && !r->port->env.failed)
    {
        goto at_4801a0;
    }
    if (r->edx == 0x80158320u && !r->port->env.failed)
    {
        goto at_4801a7;
    }
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4802fd;
at_480526:
    if (cond(r, CC_BE) && !r->port->env.failed)
    {
        goto at_48010d;
    }
    flags(r, F_SUB, r->edx, 0x80158200u, 32);
    if (cond(r, CC_AE))
    {
        goto at_48055d;
    }
    flags(r, F_SUB, r->edx, 0x80158160u, 32);
    if (cond(r, CC_AE))
    {
        goto at_4805e3;
    }
    flags(r, F_SUB, r->edx, 0x80158140u, 32);
    if (cond(r, CC_AE))
    {
        goto at_48062b;
    }
    if (r->edx == 0x80158130u && !r->port->env.failed)
    {
        goto at_480114;
    }
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4802fd;
at_48055d:
    if (cond(r, CC_BE) && !r->port->env.failed)
    {
        goto at_48014c;
    }
    flags(r, F_SUB, r->edx, 0x80158240u, 32);
    if (cond(r, CC_AE))
    {
        goto at_480584;
    }
    flags(r, F_SUB, r->edx, 0x80158220u, 32);
    if (cond(r, CC_AE))
    {
        goto at_4805cc;
    }
    if (r->edx == 0x80158210u && !r->port->env.failed)
    {
        goto at_480153;
    }
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4802fd;
at_480584:
    if (cond(r, CC_BE) && !r->port->env.failed)
    {
        goto at_48016f;
    }
    flags(r, F_SUB, r->edx, 0x80158260u, 32);
    if (cond(r, CC_AE))
    {
        goto at_4805a3;
    }
    if (r->edx == 0x80158250u && !r->port->env.failed)
    {
        goto at_480176;
    }
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4802fd;
at_4805a3:
    if (cond(r, CC_BE) && !r->port->env.failed)
    {
        goto at_48017d;
    }
    flags(r, F_SUB, r->edx, 0x80158270u, 32);
    if (cond(r, CC_B) && !r->port->env.failed)
    {
        goto at_4802fd;
    }
    if (cond(r, CC_BE) && !r->port->env.failed)
    {
        goto at_480184;
    }
    if (r->edx == 0x80158280u && !r->port->env.failed)
    {
        goto at_48018b;
    }
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4802fd;
at_4805cc:
    if (cond(r, CC_BE) && !r->port->env.failed)
    {
        goto at_48015a;
    }
    if (r->edx == 0x80158230u && !r->port->env.failed)
    {
        goto at_480161;
    }
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4802fd;
at_4805e3:
    if (cond(r, CC_BE) && !r->port->env.failed)
    {
        goto at_480129;
    }
    flags(r, F_SUB, r->edx, 0x80158175u, 32);
    if (cond(r, CC_AE))
    {
        goto at_480602;
    }
    if (r->edx == 0x80158170u && !r->port->env.failed)
    {
        goto at_480130;
    }
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4802fd;
at_480602:
    if (cond(r, CC_BE) && !r->port->env.failed)
    {
        goto at_480137;
    }
    flags(r, F_SUB, r->edx, 0x80158180u, 32);
    if (cond(r, CC_B) && !r->port->env.failed)
    {
        goto at_4802fd;
    }
    if (cond(r, CC_BE) && !r->port->env.failed)
    {
        goto at_48013e;
    }
    if (r->edx == 0x80158190u && !r->port->env.failed)
    {
        goto at_480145;
    }
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4802fd;
at_48062b:
    if (cond(r, CC_BE) && !r->port->env.failed)
    {
        goto at_48011b;
    }
    if (r->edx == 0x80158150u && !r->port->env.failed)
    {
        goto at_480122;
    }
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4802fd;
at_480642:
    if (cond(r, CC_BE) && !r->port->env.failed)
    {
        goto at_4800ce;
    }
    flags(r, F_SUB, r->edx, 0x80158070u, 32);
    if (cond(r, CC_AE))
    {
        goto at_480669;
    }
    flags(r, F_SUB, r->edx, 0x80158050u, 32);
    if (cond(r, CC_AE))
    {
        goto at_4806b1;
    }
    if (r->edx == 0x80158040u && !r->port->env.failed)
    {
        goto at_4800d5;
    }
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4802fd;
at_480669:
    if (cond(r, CC_BE) && !r->port->env.failed)
    {
        goto at_4800ea;
    }
    flags(r, F_SUB, r->edx, 0x80158090u, 32);
    if (cond(r, CC_AE))
    {
        goto at_480688;
    }
    if (r->edx == 0x80158080u && !r->port->env.failed)
    {
        goto at_4800f1;
    }
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4802fd;
at_480688:
    if (cond(r, CC_BE) && !r->port->env.failed)
    {
        goto at_4800f8;
    }
    flags(r, F_SUB, r->edx, 0x80158100u, 32);
    if (cond(r, CC_B) && !r->port->env.failed)
    {
        goto at_4802fd;
    }
    if (cond(r, CC_BE) && !r->port->env.failed)
    {
        goto at_4800ff;
    }
    if (r->edx == 0x80158110u && !r->port->env.failed)
    {
        goto at_480106;
    }
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4802fd;
at_4806b1:
    if (cond(r, CC_BE) && !r->port->env.failed)
    {
        goto at_4800dc;
    }
    if (r->edx == 0x80158060u && !r->port->env.failed)
    {
        goto at_4800e3;
    }
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4802fd;
at_4806c8:
    if (cond(r, CC_BE) && !r->port->env.failed)
    {
        goto at_480233;
    }
    flags(r, F_SUB, r->edx, 0x80004005u, 32);
    if (cond(r, CC_AE))
    {
        goto at_4806e7;
    }
    if (r->edx == 0x80004003u && !r->port->env.failed)
    {
        goto at_4801fb;
    }
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4802fd;
at_4806e7:
    if (cond(r, CC_BE) && !r->port->env.failed)
    {
        goto at_480168;
    }
    flags(r, F_SUB, r->edx, 0x8007000eu, 32);
    if (cond(r, CC_B) && !r->port->env.failed)
    {
        goto at_4802fd;
    }
    if (cond(r, CC_BE) && !r->port->env.failed)
    {
        goto at_480264;
    }
    if (r->edx == 0x80070057u && !r->port->env.failed)
    {
        goto at_4801e6;
    }
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4802fd;
at_480710:
    if (cond(r, CC_BE) && !r->port->env.failed)
    {
        goto at_48026b;
    }
    if (r->edx == 0x80004001u && !r->port->env.failed)
    {
        goto at_4802b1;
    }
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4802fd;
}

uint32_t vertrix_port_dplay_error_name_480080(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x20
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
