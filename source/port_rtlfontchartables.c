#include "port_rtlfontchartables.h"

/* 0x43fc50 builds about twenty character-to-glyph word tables (0x541988 through 0x543e60). */

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

static void set_low8(uint32_t *reg, uint32_t value)
{
    *reg = (*reg & 0xffffff00u) | (value & 0xff);
}

/* Original 0x43fc50: 0x43fc50 builds about twenty character-to-glyph word tables (0x541988 through
 * 0x543e60). For each table it calls vertrix_port_pair_set (0x48abe0) with values that vary by
 * table (0x23/0x1e at first, then 0x1c, 0xd, 0xe or 0x12). It then fills 'A'..'Z' and '0'..'9' with
 * vertrix_port_word_table_set (0x48abf0), using offsets such as char-0x11, char-0x35, char+0x1a and
 * char-0xa. Some tables (0x5429e8, 0x542bf4) set only 'G'/'O' or 'V'/'S' after
 * vertrix_port_frame_resource_get (0x4877f0) on 0x546538. Between tables it calls the
 * font_glyphs_map family (0x43f480, 0x43f550, 0x43f630, 0x43f710 to 0x43fb70) with the previous
 * table. Evidence: calls 0x48abe0, 0x48abf0, 0x43f480, 0x43f630, 0x4877f0, 0x43f550, 0x43f710,
 * 0x43f7f0, 0x43f8d0, 0x43f9b0, 0x43fa90, 0x43fb70. Register-for-register from the listing
 * (0x43fc5c..0x440482); labels are the original addresses. */
static void run(Regs *r)
{
    r->ecx = 0x541988;
    r->ebx = 0x1e;
    r->edx = 0x23;
    r->eax = r->ecx;
    call(r, 0x48abe0, 0);
    wr8(r, r->ebp - 0x8c, 0x41);
at_43fc79:
    r->edx = 0;
    set_low8(&r->edx, rd8(r, r->ebp - 0x8c));
    if ((int32_t)r->edx <= (int32_t)0x5a)
    {
        goto at_43fcac;
    }
    wr8(r, r->ebp - 0x28, 0x30);
at_43fc8a:
    r->eax = 0;
    set_low8(&r->eax, rd8(r, r->ebp - 0x28));
    if ((int32_t)r->eax > (int32_t)0x39)
    {
        goto at_43fcc8;
    }
    r->edx = 0;
    set_low8(&r->edx, (r->eax & 0xff));
    r->edx = r->edx + 0x1a;
    r->ebx = (uint32_t)(int32_t)(int16_t)(r->edx & 0xffff);
    r->edx = r->eax;
    r->eax = r->ecx;
    call(r, 0x48abf0, 0);
    wr8(r, r->ebp - 0x28, rd8(r, r->ebp - 0x28) + 1);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_43fc8a;
at_43fcac:
    r->eax = 0;
    set_low8(&r->eax, (r->edx & 0xff));
    r->eax = r->eax - 0x11;
    r->ebx = (uint32_t)(int32_t)(int16_t)(r->eax & 0xffff);
    r->eax = 0x541988;
    call(r, 0x48abf0, 0);
    wr8(r, r->ebp - 0x8c, rd8(r, r->ebp - 0x8c) + 1);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_43fc79;
at_43fcc8:
    r->ebx = 0x1e;
    r->edx = 0x23;
    r->eax = r->ecx;
    r->ecx = 0x541b94;
    call(r, 0x43f480, 0);
    r->eax = r->ecx;
    call(r, 0x48abe0, 0);
    wr8(r, r->ebp - 0x2c, 0x41);
at_43fce9:
    r->edx = 0;
    set_low8(&r->edx, rd8(r, r->ebp - 0x2c));
    if ((int32_t)r->edx > (int32_t)0x5a)
    {
        goto at_43fd0c;
    }
    r->eax = 0;
    set_low8(&r->eax, (r->edx & 0xff));
    r->eax = r->eax - 0x35;
    r->ebx = (uint32_t)(int32_t)(int16_t)(r->eax & 0xffff);
    r->eax = 0x541b94;
    call(r, 0x48abf0, 0);
    wr8(r, r->ebp - 0x2c, rd8(r, r->ebp - 0x2c) + 1);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_43fce9;
at_43fd0c:
    wr8(r, r->ebp - 0x30, 0x30);
at_43fd10:
    r->eax = 0;
    set_low8(&r->eax, rd8(r, r->ebp - 0x30));
    if ((int32_t)r->eax > (int32_t)0x39)
    {
        goto at_43fd32;
    }
    r->edx = 0;
    set_low8(&r->edx, (r->eax & 0xff));
    r->edx = r->edx - 0xa;
    r->ebx = (uint32_t)(int32_t)(int16_t)(r->edx & 0xffff);
    r->edx = r->eax;
    r->eax = r->ecx;
    call(r, 0x48abf0, 0);
    wr8(r, r->ebp - 0x30, rd8(r, r->ebp - 0x30) + 1);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_43fd10;
at_43fd32:
    r->ebx = 0x1e;
    r->edx = 0x23;
    r->eax = r->ecx;
    r->ecx = 0x541da0;
    call(r, 0x43f480, 0);
    r->eax = r->ecx;
    call(r, 0x48abe0, 0);
    wr8(r, r->ebp - 0x34, 0x41);
at_43fd53:
    r->edx = 0;
    set_low8(&r->edx, rd8(r, r->ebp - 0x34));
    if ((int32_t)r->edx > (int32_t)0x5a)
    {
        goto at_43fd76;
    }
    r->eax = 0;
    set_low8(&r->eax, (r->edx & 0xff));
    r->eax = r->eax - 0x35;
    r->ebx = (uint32_t)(int32_t)(int16_t)(r->eax & 0xffff);
    r->eax = 0x541da0;
    call(r, 0x48abf0, 0);
    wr8(r, r->ebp - 0x34, rd8(r, r->ebp - 0x34) + 1);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_43fd53;
at_43fd76:
    wr8(r, r->ebp - 0x38, 0x30);
at_43fd7a:
    r->eax = 0;
    set_low8(&r->eax, rd8(r, r->ebp - 0x38));
    if ((int32_t)r->eax > (int32_t)0x39)
    {
        goto at_43fd9c;
    }
    r->edx = 0;
    set_low8(&r->edx, (r->eax & 0xff));
    r->edx = r->edx + 0x1a;
    r->ebx = (uint32_t)(int32_t)(int16_t)(r->edx & 0xffff);
    r->edx = r->eax;
    r->eax = r->ecx;
    call(r, 0x48abf0, 0);
    wr8(r, r->ebp - 0x38, rd8(r, r->ebp - 0x38) + 1);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_43fd7a;
at_43fd9c:
    r->ebx = 0x1e;
    r->edx = 0x23;
    r->eax = r->ecx;
    r->ecx = 0x541fac;
    call(r, 0x43f480, 0);
    r->eax = r->ecx;
    call(r, 0x48abe0, 0);
    wr8(r, r->ebp - 0x3c, 0x41);
at_43fdbd:
    r->edx = 0;
    set_low8(&r->edx, rd8(r, r->ebp - 0x3c));
    if ((int32_t)r->edx > (int32_t)0x5a)
    {
        goto at_43fde0;
    }
    r->eax = 0;
    set_low8(&r->eax, (r->edx & 0xff));
    r->eax = r->eax - 0x11;
    r->ebx = (uint32_t)(int32_t)(int16_t)(r->eax & 0xffff);
    r->eax = 0x541fac;
    call(r, 0x48abf0, 0);
    wr8(r, r->ebp - 0x3c, rd8(r, r->ebp - 0x3c) + 1);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_43fdbd;
at_43fde0:
    wr8(r, r->ebp - 0x40, 0x30);
at_43fde4:
    r->eax = 0;
    set_low8(&r->eax, rd8(r, r->ebp - 0x40));
    if ((int32_t)r->eax > (int32_t)0x39)
    {
        goto at_43fe06;
    }
    r->edx = 0;
    set_low8(&r->edx, (r->eax & 0xff));
    r->edx = r->edx + 0x1a;
    r->ebx = (uint32_t)(int32_t)(int16_t)(r->edx & 0xffff);
    r->edx = r->eax;
    r->eax = r->ecx;
    call(r, 0x48abf0, 0);
    wr8(r, r->ebp - 0x40, rd8(r, r->ebp - 0x40) + 1);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_43fde4;
at_43fe06:
    r->ebx = 0x1e;
    r->edx = 0x1c;
    r->eax = r->ecx;
    r->ecx = 0x5421b8;
    call(r, 0x43f480, 0);
    r->eax = r->ecx;
    call(r, 0x48abe0, 0);
    wr8(r, r->ebp - 0x44, 0x41);
at_43fe27:
    r->edx = 0;
    set_low8(&r->edx, rd8(r, r->ebp - 0x44));
    if ((int32_t)r->edx > (int32_t)0x5a)
    {
        goto at_43fe4a;
    }
    r->eax = 0;
    set_low8(&r->eax, (r->edx & 0xff));
    r->eax = r->eax - 0x35;
    r->ebx = (uint32_t)(int32_t)(int16_t)(r->eax & 0xffff);
    r->eax = 0x5421b8;
    call(r, 0x48abf0, 0);
    wr8(r, r->ebp - 0x44, rd8(r, r->ebp - 0x44) + 1);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_43fe27;
at_43fe4a:
    wr8(r, r->ebp - 0x48, 0x30);
at_43fe4e:
    r->eax = 0;
    set_low8(&r->eax, rd8(r, r->ebp - 0x48));
    if ((int32_t)r->eax > (int32_t)0x39)
    {
        goto at_43fe70;
    }
    r->edx = 0;
    set_low8(&r->edx, (r->eax & 0xff));
    r->edx = r->edx + 0x24;
    r->ebx = (uint32_t)(int32_t)(int16_t)(r->edx & 0xffff);
    r->edx = r->eax;
    r->eax = r->ecx;
    call(r, 0x48abf0, 0);
    wr8(r, r->ebp - 0x48, rd8(r, r->ebp - 0x48) + 1);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_43fe4e;
at_43fe70:
    r->ebx = 0x1e;
    r->edx = 0x1c;
    r->eax = r->ecx;
    r->ecx = 0x543a48;
    call(r, 0x43f480, 0);
    r->eax = r->ecx;
    call(r, 0x48abe0, 0);
    wr8(r, r->ebp - 0x4c, 0x41);
at_43fe91:
    r->edx = 0;
    set_low8(&r->edx, rd8(r, r->ebp - 0x4c));
    if ((int32_t)r->edx > (int32_t)0x5a)
    {
        goto at_43feb4;
    }
    r->eax = 0;
    set_low8(&r->eax, (r->edx & 0xff));
    r->eax = r->eax - 0x35;
    r->ebx = (uint32_t)(int32_t)(int16_t)(r->eax & 0xffff);
    r->eax = 0x543a48;
    call(r, 0x48abf0, 0);
    wr8(r, r->ebp - 0x4c, rd8(r, r->ebp - 0x4c) + 1);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_43fe91;
at_43feb4:
    wr8(r, r->ebp - 0x50, 0x30);
at_43feb8:
    r->eax = 0;
    set_low8(&r->eax, rd8(r, r->ebp - 0x50));
    if ((int32_t)r->eax > (int32_t)0x39)
    {
        goto at_43fedd;
    }
    r->edx = 0;
    set_low8(&r->edx, (r->eax & 0xff));
    r->edx = r->edx + 0x1d6;
    r->ebx = (uint32_t)(int32_t)(int16_t)(r->edx & 0xffff);
    r->edx = r->eax;
    r->eax = r->ecx;
    call(r, 0x48abf0, 0);
    wr8(r, r->ebp - 0x50, rd8(r, r->ebp - 0x50) + 1);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_43feb8;
at_43fedd:
    r->ebx = 0x1e;
    r->edx = 0x1c;
    r->eax = r->ecx;
    r->ecx = 0x543c54;
    call(r, 0x43f480, 0);
    r->eax = r->ecx;
    call(r, 0x48abe0, 0);
    wr8(r, r->ebp - 0x54, 0x41);
at_43fefe:
    r->edx = 0;
    set_low8(&r->edx, rd8(r, r->ebp - 0x54));
    if ((int32_t)r->edx > (int32_t)0x5a)
    {
        goto at_43ff21;
    }
    r->eax = 0;
    set_low8(&r->eax, (r->edx & 0xff));
    r->eax = r->eax - 0x35;
    r->ebx = (uint32_t)(int32_t)(int16_t)(r->eax & 0xffff);
    r->eax = 0x543c54;
    call(r, 0x48abf0, 0);
    wr8(r, r->ebp - 0x54, rd8(r, r->ebp - 0x54) + 1);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_43fefe;
at_43ff21:
    wr8(r, r->ebp - 0x58, 0x30);
at_43ff25:
    r->eax = 0;
    set_low8(&r->eax, rd8(r, r->ebp - 0x58));
    if ((int32_t)r->eax > (int32_t)0x39)
    {
        goto at_43ff4a;
    }
    r->edx = 0;
    set_low8(&r->edx, (r->eax & 0xff));
    r->edx = r->edx + 0x1e0;
    r->ebx = (uint32_t)(int32_t)(int16_t)(r->edx & 0xffff);
    r->edx = r->eax;
    r->eax = r->ecx;
    call(r, 0x48abf0, 0);
    wr8(r, r->ebp - 0x58, rd8(r, r->ebp - 0x58) + 1);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_43ff25;
at_43ff4a:
    r->ebx = 0x1e;
    r->edx = 0x1c;
    r->eax = r->ecx;
    r->ecx = 0x543e60;
    call(r, 0x43f480, 0);
    r->eax = r->ecx;
    call(r, 0x48abe0, 0);
    wr8(r, r->ebp - 0x5c, 0x41);
at_43ff6b:
    r->edx = 0;
    set_low8(&r->edx, rd8(r, r->ebp - 0x5c));
    if ((int32_t)r->edx > (int32_t)0x5a)
    {
        goto at_43ff8e;
    }
    r->eax = 0;
    set_low8(&r->eax, (r->edx & 0xff));
    r->eax = r->eax - 0x35;
    r->ebx = (uint32_t)(int32_t)(int16_t)(r->eax & 0xffff);
    r->eax = 0x543e60;
    call(r, 0x48abf0, 0);
    wr8(r, r->ebp - 0x5c, rd8(r, r->ebp - 0x5c) + 1);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_43ff6b;
at_43ff8e:
    wr8(r, r->ebp - 0x60, 0x30);
at_43ff92:
    r->eax = 0;
    set_low8(&r->eax, rd8(r, r->ebp - 0x60));
    if ((int32_t)r->eax > (int32_t)0x39)
    {
        goto at_43ffb7;
    }
    r->edx = 0;
    set_low8(&r->edx, (r->eax & 0xff));
    r->edx = r->edx + 0x1ea;
    r->ebx = (uint32_t)(int32_t)(int16_t)(r->edx & 0xffff);
    r->edx = r->eax;
    r->eax = r->ecx;
    call(r, 0x48abf0, 0);
    wr8(r, r->ebp - 0x60, rd8(r, r->ebp - 0x60) + 1);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_43ff92;
at_43ffb7:
    r->ebx = 0xc;
    r->edx = 0xd;
    r->eax = r->ecx;
    r->ecx = 0x5423c4;
    call(r, 0x43f480, 0);
    r->eax = r->ecx;
    call(r, 0x48abe0, 0);
    wr8(r, r->ebp - 0x64, 0x41);
at_43ffd8:
    r->edx = 0;
    set_low8(&r->edx, rd8(r, r->ebp - 0x64));
    if ((int32_t)r->edx > (int32_t)0x5a)
    {
        goto at_43fffd;
    }
    r->eax = 0;
    set_low8(&r->eax, (r->edx & 0xff));
    r->eax = r->eax + 0x29;
    r->ebx = (uint32_t)(int32_t)(int16_t)(r->eax & 0xffff);
    r->eax = 0x5423c4;
    call(r, 0x48abf0, 0);
    wr8(r, r->ebp - 0x64, rd8(r, r->ebp - 0x64) + 1);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_43ffd8;
at_43fffd:
    wr8(r, r->ebp - 0x1c, 0x30);
at_440001:
    r->eax = 0;
    set_low8(&r->eax, rd8(r, r->ebp - 0x1c));
    if ((int32_t)r->eax > (int32_t)0x39)
    {
        goto at_440023;
    }
    r->edx = 0;
    set_low8(&r->edx, (r->eax & 0xff));
    r->edx = r->edx + 0x54;
    r->ebx = (uint32_t)(int32_t)(int16_t)(r->edx & 0xffff);
    r->edx = r->eax;
    r->eax = r->ecx;
    call(r, 0x48abf0, 0);
    wr8(r, r->ebp - 0x1c, rd8(r, r->ebp - 0x1c) + 1);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_440001;
at_440023:
    r->ebx = 0x10;
    r->edx = 0xe;
    r->eax = r->ecx;
    r->ecx = 0x5425d0;
    call(r, 0x43f630, 0);
    r->eax = r->ecx;
    call(r, 0x48abe0, 0);
    wr8(r, r->ebp - 0x20, 0x30);
at_440044:
    r->edx = 0;
    set_low8(&r->edx, rd8(r, r->ebp - 0x20));
    if ((int32_t)r->edx > (int32_t)0x39)
    {
        goto at_440069;
    }
    r->eax = 0;
    set_low8(&r->eax, (r->edx & 0xff));
    r->eax = r->eax + 0x5e;
    r->ebx = (uint32_t)(int32_t)(int16_t)(r->eax & 0xffff);
    r->eax = 0x5425d0;
    call(r, 0x48abf0, 0);
    wr8(r, r->ebp - 0x20, rd8(r, r->ebp - 0x20) + 1);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_440044;
at_440069:
    wr8(r, r->ebp - 0x24, 0x41);
at_44006d:
    r->eax = 0;
    set_low8(&r->eax, rd8(r, r->ebp - 0x24));
    if ((int32_t)r->eax > (int32_t)0x5a)
    {
        goto at_44008f;
    }
    r->edx = 0;
    set_low8(&r->edx, (r->eax & 0xff));
    r->edx = r->edx + 0x57;
    r->ebx = (uint32_t)(int32_t)(int16_t)(r->edx & 0xffff);
    r->edx = r->eax;
    r->eax = r->ecx;
    call(r, 0x48abf0, 0);
    wr8(r, r->ebp - 0x24, rd8(r, r->ebp - 0x24) + 1);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_44006d;
at_44008f:
    r->edx = 0x6;
    r->eax = 0x546538;
    call(r, 0x4877f0, 0);
    r->edx = rd32(r, r->eax + 0x8);
    r->edx = r->edx >> 0x1;
    r->edx = r->edx + r->edx;
    r->ebx = r->edx + 0x1e;
    r->edx = rd32(r, r->eax + 0x4);
    r->edx = r->edx >> 0x1;
    r->ecx = 0x5427dc;
    r->edx = r->edx + r->edx;
    r->eax = r->ecx;
    r->edx = r->edx + 0x23;
    call(r, 0x48abe0, 0);
    wr8(r, r->ebp - 0x74, 0x41);
at_4400c2:
    r->edx = 0;
    set_low8(&r->edx, rd8(r, r->ebp - 0x74));
    if ((int32_t)r->edx > (int32_t)0x5a)
    {
        goto at_4400e7;
    }
    r->eax = 0;
    set_low8(&r->eax, (r->edx & 0xff));
    r->eax = r->eax + 0x71;
    r->ebx = (uint32_t)(int32_t)(int16_t)(r->eax & 0xffff);
    r->eax = 0x5427dc;
    call(r, 0x48abf0, 0);
    wr8(r, r->ebp - 0x74, rd8(r, r->ebp - 0x74) + 1);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4400c2;
at_4400e7:
    wr8(r, r->ebp - 0x78, 0x30);
at_4400eb:
    r->eax = 0;
    set_low8(&r->eax, rd8(r, r->ebp - 0x78));
    if ((int32_t)r->eax > (int32_t)0x39)
    {
        goto at_440110;
    }
    r->edx = 0;
    set_low8(&r->edx, (r->eax & 0xff));
    r->edx = r->edx + 0x9c;
    r->ebx = (uint32_t)(int32_t)(int16_t)(r->edx & 0xffff);
    r->edx = r->eax;
    r->eax = r->ecx;
    call(r, 0x48abf0, 0);
    wr8(r, r->ebp - 0x78, rd8(r, r->ebp - 0x78) + 1);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4400eb;
at_440110:
    r->eax = r->ecx;
    r->edx = 0x9;
    call(r, 0x43f550, 0);
    r->eax = 0x546538;
    call(r, 0x4877f0, 0);
    r->ebx = rd32(r, r->eax + 0x8);
    r->eax = rd32(r, r->eax + 0x4);
    r->eax = r->eax >> 0x1;
    r->ebx = r->ebx >> 0x1;
    r->eax = r->eax + r->eax;
    r->ebx = r->ebx + r->ebx;
    r->edx = r->eax + 0x23;
    r->ebx = r->ebx + 0x1e;
    r->eax = 0x5429e8;
    call(r, 0x48abe0, 0);
    r->ebx = 0xe2;
    r->edx = 0x47;
    r->eax = 0x5429e8;
    call(r, 0x48abf0, 0);
    r->ebx = 0xe3;
    r->edx = 0x4f;
    r->eax = 0x5429e8;
    call(r, 0x48abf0, 0);
    r->edx = 0x9;
    r->eax = 0x546538;
    call(r, 0x4877f0, 0);
    r->ebx = rd32(r, r->eax + 0x8);
    r->eax = rd32(r, r->eax + 0x4);
    r->eax = r->eax >> 0x1;
    r->ebx = r->ebx >> 0x1;
    r->eax = r->eax + r->eax;
    r->ebx = r->ebx + r->ebx;
    r->edx = r->eax + 0x23;
    r->ebx = r->ebx + 0x1e;
    r->eax = 0x542bf4;
    call(r, 0x48abe0, 0);
    r->ebx = 0xe4;
    r->edx = 0x56;
    r->eax = 0x542bf4;
    call(r, 0x48abf0, 0);
    r->ebx = 0xe5;
    r->edx = 0x53;
    r->eax = 0x542bf4;
    r->ecx = 0x542e00;
    call(r, 0x48abf0, 0);
    r->ebx = 0xe;
    r->edx = 0x12;
    r->eax = r->ecx;
    call(r, 0x48abe0, 0);
    wr8(r, r->ebp - 0x7c, 0x41);
at_4401db:
    r->edx = 0;
    set_low8(&r->edx, rd8(r, r->ebp - 0x7c));
    if ((int32_t)r->edx > (int32_t)0x5a)
    {
        goto at_440200;
    }
    r->eax = 0;
    set_low8(&r->eax, (r->edx & 0xff));
    r->eax = r->eax + 0xb1;
    r->ebx = (uint32_t)(int32_t)(int16_t)(r->eax & 0xffff);
    r->eax = 0x542e00;
    call(r, 0x48abf0, 0);
    wr8(r, r->ebp - 0x7c, rd8(r, r->ebp - 0x7c) + 1);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4401db;
at_440200:
    wr8(r, r->ebp - 0x80, 0x30);
at_440204:
    r->eax = 0;
    set_low8(&r->eax, rd8(r, r->ebp - 0x80));
    if ((int32_t)r->eax > (int32_t)0x39)
    {
        goto at_440229;
    }
    r->edx = 0;
    set_low8(&r->edx, (r->eax & 0xff));
    r->edx = r->edx + 0xdc;
    r->ebx = (uint32_t)(int32_t)(int16_t)(r->edx & 0xffff);
    r->edx = r->eax;
    r->eax = r->ecx;
    call(r, 0x48abf0, 0);
    wr8(r, r->ebp - 0x80, rd8(r, r->ebp - 0x80) + 1);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_440204;
at_440229:
    r->ebx = 0xc;
    r->edx = 0xd;
    r->eax = r->ecx;
    r->ecx = 0x54300c;
    call(r, 0x43f710, 0);
    r->eax = r->ecx;
    call(r, 0x48abe0, 0);
    wr8(r, r->ebp - 0x84, 0x41);
at_44024d:
    r->edx = 0;
    set_low8(&r->edx, rd8(r, r->ebp - 0x84));
    if ((int32_t)r->edx > (int32_t)0x5a)
    {
        goto at_440278;
    }
    r->eax = 0;
    set_low8(&r->eax, (r->edx & 0xff));
    r->eax = r->eax + 0xe1;
    r->ebx = (uint32_t)(int32_t)(int16_t)(r->eax & 0xffff);
    r->eax = 0x54300c;
    call(r, 0x48abf0, 0);
    wr8(r, r->ebp - 0x84, rd8(r, r->ebp - 0x84) + 1);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_44024d;
at_440278:
    wr8(r, r->ebp - 0x88, 0x30);
at_44027f:
    r->eax = 0;
    set_low8(&r->eax, rd8(r, r->ebp - 0x88));
    if ((int32_t)r->eax > (int32_t)0x39)
    {
        goto at_4402aa;
    }
    r->edx = 0;
    set_low8(&r->edx, (r->eax & 0xff));
    r->edx = r->edx + 0x10c;
    r->ebx = (uint32_t)(int32_t)(int16_t)(r->edx & 0xffff);
    r->edx = r->eax;
    r->eax = r->ecx;
    call(r, 0x48abf0, 0);
    wr8(r, r->ebp - 0x88, rd8(r, r->ebp - 0x88) + 1);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_44027f;
at_4402aa:
    r->ebx = 0xe;
    r->edx = 0x12;
    r->eax = r->ecx;
    r->ecx = 0x543218;
    call(r, 0x43f7f0, 0);
    r->eax = r->ecx;
    call(r, 0x48abe0, 0);
    wr8(r, r->ebp - 0x68, 0x41);
at_4402cb:
    r->edx = 0;
    set_low8(&r->edx, rd8(r, r->ebp - 0x68));
    if ((int32_t)r->edx > (int32_t)0x5a)
    {
        goto at_4402f0;
    }
    r->eax = 0;
    set_low8(&r->eax, (r->edx & 0xff));
    r->eax = r->eax + 0x111;
    r->ebx = (uint32_t)(int32_t)(int16_t)(r->eax & 0xffff);
    r->eax = 0x543218;
    call(r, 0x48abf0, 0);
    wr8(r, r->ebp - 0x68, rd8(r, r->ebp - 0x68) + 1);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4402cb;
at_4402f0:
    wr8(r, r->ebp - 0x6c, 0x30);
at_4402f4:
    r->eax = 0;
    set_low8(&r->eax, rd8(r, r->ebp - 0x6c));
    if ((int32_t)r->eax > (int32_t)0x39)
    {
        goto at_440319;
    }
    r->edx = 0;
    set_low8(&r->edx, (r->eax & 0xff));
    r->edx = r->edx + 0x13c;
    r->ebx = (uint32_t)(int32_t)(int16_t)(r->edx & 0xffff);
    r->edx = r->eax;
    r->eax = r->ecx;
    call(r, 0x48abf0, 0);
    wr8(r, r->ebp - 0x6c, rd8(r, r->ebp - 0x6c) + 1);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4402f4;
at_440319:
    r->ebx = 0xc;
    r->edx = 0xd;
    r->eax = r->ecx;
    r->ecx = 0x543424;
    call(r, 0x43f8d0, 0);
    r->eax = r->ecx;
    call(r, 0x48abe0, 0);
    wr8(r, r->ebp - 0x70, 0x41);
at_44033a:
    r->edx = 0;
    set_low8(&r->edx, rd8(r, r->ebp - 0x70));
    if ((int32_t)r->edx > (int32_t)0x5a)
    {
        goto at_44035f;
    }
    r->eax = 0;
    set_low8(&r->eax, (r->edx & 0xff));
    r->eax = r->eax + 0x141;
    r->ebx = (uint32_t)(int32_t)(int16_t)(r->eax & 0xffff);
    r->eax = 0x543424;
    call(r, 0x48abf0, 0);
    wr8(r, r->ebp - 0x70, rd8(r, r->ebp - 0x70) + 1);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_44033a;
at_44035f:
    wr8(r, r->ebp - 0x90, 0x30);
at_440366:
    r->eax = 0;
    set_low8(&r->eax, rd8(r, r->ebp - 0x90));
    if ((int32_t)r->eax > (int32_t)0x39)
    {
        goto at_440391;
    }
    r->edx = 0;
    set_low8(&r->edx, (r->eax & 0xff));
    r->edx = r->edx + 0x16c;
    r->ebx = (uint32_t)(int32_t)(int16_t)(r->edx & 0xffff);
    r->edx = r->eax;
    r->eax = r->ecx;
    call(r, 0x48abf0, 0);
    wr8(r, r->ebp - 0x90, rd8(r, r->ebp - 0x90) + 1);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_440366;
at_440391:
    r->ebx = 0xe;
    r->edx = 0x12;
    r->eax = r->ecx;
    r->ecx = 0x543630;
    call(r, 0x43f9b0, 0);
    r->eax = r->ecx;
    call(r, 0x48abe0, 0);
    wr8(r, r->ebp - 0x94, 0x41);
at_4403b5:
    r->edx = 0;
    set_low8(&r->edx, rd8(r, r->ebp - 0x94));
    if ((int32_t)r->edx > (int32_t)0x5a)
    {
        goto at_4403e0;
    }
    r->eax = 0;
    set_low8(&r->eax, (r->edx & 0xff));
    r->eax = r->eax + 0x171;
    r->ebx = (uint32_t)(int32_t)(int16_t)(r->eax & 0xffff);
    r->eax = 0x543630;
    call(r, 0x48abf0, 0);
    wr8(r, r->ebp - 0x94, rd8(r, r->ebp - 0x94) + 1);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4403b5;
at_4403e0:
    wr8(r, r->ebp - 0x10, 0x30);
at_4403e4:
    r->eax = 0;
    set_low8(&r->eax, rd8(r, r->ebp - 0x10));
    if ((int32_t)r->eax > (int32_t)0x39)
    {
        goto at_440409;
    }
    r->edx = 0;
    set_low8(&r->edx, (r->eax & 0xff));
    r->edx = r->edx + 0x19c;
    r->ebx = (uint32_t)(int32_t)(int16_t)(r->edx & 0xffff);
    r->edx = r->eax;
    r->eax = r->ecx;
    call(r, 0x48abf0, 0);
    wr8(r, r->ebp - 0x10, rd8(r, r->ebp - 0x10) + 1);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_4403e4;
at_440409:
    r->ebx = 0xc;
    r->edx = 0xd;
    r->eax = r->ecx;
    r->ecx = 0x54383c;
    call(r, 0x43fa90, 0);
    r->eax = r->ecx;
    call(r, 0x48abe0, 0);
    wr8(r, r->ebp - 0x14, 0x41);
at_44042a:
    r->edx = 0;
    set_low8(&r->edx, rd8(r, r->ebp - 0x14));
    if ((int32_t)r->edx > (int32_t)0x5a)
    {
        goto at_44044f;
    }
    r->eax = 0;
    set_low8(&r->eax, (r->edx & 0xff));
    r->eax = r->eax + 0x1a1;
    r->ebx = (uint32_t)(int32_t)(int16_t)(r->eax & 0xffff);
    r->eax = 0x54383c;
    call(r, 0x48abf0, 0);
    wr8(r, r->ebp - 0x14, rd8(r, r->ebp - 0x14) + 1);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_44042a;
at_44044f:
    wr8(r, r->ebp - 0x18, 0x30);
at_440453:
    r->edx = 0;
    set_low8(&r->edx, rd8(r, r->ebp - 0x18));
    if ((int32_t)r->edx <= (int32_t)0x39)
    {
        goto at_44046c;
    }
    r->eax = r->ecx;
    call(r, 0x43fb70, 0);
    r->edx = rd32(r, r->ebp - 0xc);
    r->ecx = rd32(r, r->ebp - 0x8);
    r->ebx = rd32(r, r->ebp - 0x4);
    return;
at_44046c:
    r->eax = 0;
    set_low8(&r->eax, (r->edx & 0xff));
    r->eax = r->eax + 0x1cc;
    r->ebx = (uint32_t)(int32_t)(int16_t)(r->eax & 0xffff);
    r->eax = r->ecx;
    call(r, 0x48abf0, 0);
    wr8(r, r->ebp - 0x18, rd8(r, r->ebp - 0x18) + 1);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_440453;
}

uint32_t vertrix_port_font_char_tables_build_43fc50(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x98
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
    run(&r);
    return port_return(&port, r.eax, r.edx);
}
