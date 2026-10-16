#include "port_rtltextfieldkeys3.h"

/* Loops polling keys with 0x476530 on 0x54d640 and edits a text field object, returning when no key
 * or char arrives. */

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

static void wr32(Regs *r, uint32_t address, uint32_t value)
{
    port_set32(r->port, address, 0, value);
}

static void set_low8(uint32_t *reg, uint32_t value)
{
    *reg = (*reg & 0xffffff00u) | (value & 0xff);
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

/* Original 0x45c9a0: Loops polling keys with 0x476530 on 0x54d640 and edits a text field object,
 * returning when no key or char arrives. Key 1 cancels: it calls 0x4b4cd0 and the +0x184 callback
 * with [obj+0x160]+0x15c. Keys 0x1c/0x56 commit: they call 0x4b4cd0 only if the text equals
 * 0x50e22e, store the text into [obj+0x160]+0x15c (string_set_text) and call the callback. Both
 * paths then call object_set_mode 0x4b4510 and channel_volume 0x417260/0x417290 on [0x532d88], and
 * store [0x4f7ba0] into 0x532a4c. Keys 0x5f/0x60/0x5c step the cursor (0x4b4600/10/20) and 0x61
 * resets it (0x4b4630). Key 0xe removes a character (0x4b4950, then 0x4b4600 on success) and 0x65
 * removes the character after the cursor (0x4b4af0). A typed char is checked with
 * object_parent_glyph 0x4b4cb0 (spaces skip the check), then inserted with 0x4b4790 and the cursor
 * advances (0x4b4610). Evidence: calls 0x476530, 0x4ca280, 0x4ccfe0, 0x4b4cd0, 0x4ca370, 0x4b4510,
 * 0x417260, 0x417290, 0x4ca210, 0x4b4600, 0x4b4af0, 0x4b4610, 0x4b4620, 0x4b4630, 0x4b4950,
 * 0x4cda90, 0x4cda10, 0x4b4cb0, 0x4b4790; reads 0x532d88, 0x4f7ba0, 0x532b3c; writes 0x532a4c.
 * Register-for-register from the listing (0x45c9ab..0x45cc2c); labels are the original addresses.
 */
static void run(Regs *r)
{
    r->ecx = r->eax;
    r->eax = r->ebp - 0x38;
    r->edx = 0x4ec1ec;
    r->ebx = 0x515384;
    push(r, r->port->env.chain);
    wr32(r, r->eax, pop(r));
    r->port->env.chain = r->eax;
    r->esi = 0;
    wr32(r, r->ebp - 0x34, r->edx);
    wr32(r, r->ebp - 0x30, r->ebx);
    wr32(r, r->ebp - 0x2c, r->esi);
    r->esi = 0x1;
    r->edi = 0;
at_45c9db:
    r->edx = r->ebp - 0x24;
    r->eax = 0x54d640;
    call(r, 0x476530, 0);
    r->ebx = r->eax;
    if ((uint16_t)((r->eax & 0xffff)) != 0)
    {
        goto at_45ca0b;
    }
    if (r->edi != rd32(r, r->ebp - 0x24))
    {
        goto at_45cba4;
    }
    r->eax = rd32(r, r->ebp - 0x38);
    r->port->env.chain = r->eax;
    r->edi = rd32(r, r->ebp - 0x14);
    r->esi = rd32(r, r->ebp - 0x10);
    r->edx = rd32(r, r->ebp - 0xc);
    r->ecx = rd32(r, r->ebp - 0x8);
    r->ebx = rd32(r, r->ebp - 0x4);
    return;
at_45ca0b:
    r->eax = rd32(r, r->ecx + 0x160);
    r->edx = rd32(r, r->eax + 0x15c);
    r->eax = r->ebp - 0x20;
    call(r, 0x4ca280, 0);
    wr32(r, r->ebp - 0x2c, r->esi);
    if ((uint16_t)((r->ebx & 0xffff)) == (uint16_t)0x1)
    {
        goto at_45cac9;
    }
    if ((uint16_t)((r->ebx & 0xffff)) == (uint16_t)0x1c)
    {
        goto at_45ca3c;
    }
    if ((uint16_t)((r->ebx & 0xffff)) != (uint16_t)0x56)
    {
        goto at_45cb32;
    }
at_45ca3c:
    r->edx = 0x50e22e;
    r->eax = rd32(r, r->ebp - 0x20);
    call(r, 0x4ccfe0, 0);
    if (r->eax != 0)
    {
        goto at_45ca54;
    }
    r->eax = r->ecx;
    call(r, 0x4b4cd0, 0);
at_45ca54:
    r->eax = rd32(r, r->ecx + 0x160);
    r->edx = rd32(r, r->ebp - 0x20);
    r->eax = r->eax + 0x15c;
    call(r, 0x4ca370, 0);
    r->ebx = rd32(r, r->ecx + 0x184);
    r->edx = r->ecx;
    if (r->ebx == 0)
    {
        goto at_45ca85;
    }
    r->eax = rd32(r, r->ecx + 0x160);
    r->eax = rd32(r, r->eax + 0x15c);
    call_all(r, rd32(r, r->edx + 0x184));
at_45ca85:
    r->eax = r->ecx;
    r->edx = 0;
    call(r, 0x4b4510, 0);
    r->eax = rd32(r, 0x532d88);
    call(r, 0x417260, 0);
    r->eax = rd32(r, 0x532d88);
    call(r, 0x417290, 0);
    r->eax = rd32(r, 0x4f7ba0);
    r->edx = 0;
    wr32(r, 0x532a4c, r->eax);
    r->eax = r->ebp - 0x20;
    call(r, 0x4ca210, 0);
    r->eax = rd32(r, r->ebp - 0x38);
    r->port->env.chain = r->eax;
    r->edi = rd32(r, r->ebp - 0x14);
    r->esi = rd32(r, r->ebp - 0x10);
    r->edx = rd32(r, r->ebp - 0xc);
    r->ecx = rd32(r, r->ebp - 0x8);
    r->ebx = rd32(r, r->ebp - 0x4);
    return;
at_45cac9:
    r->eax = r->ecx;
    call(r, 0x4b4cd0, 0);
    r->esi = rd32(r, r->ecx + 0x184);
    r->edx = r->ecx;
    if (r->esi == 0)
    {
        goto at_45caee;
    }
    r->eax = rd32(r, r->ecx + 0x160);
    r->eax = rd32(r, r->eax + 0x15c);
    call_all(r, rd32(r, r->edx + 0x184));
at_45caee:
    r->eax = r->ecx;
    r->edx = 0;
    call(r, 0x4b4510, 0);
    r->eax = rd32(r, 0x532d88);
    call(r, 0x417260, 0);
    r->eax = rd32(r, 0x532d88);
    call(r, 0x417290, 0);
    r->eax = rd32(r, 0x4f7ba0);
    r->edx = 0;
    wr32(r, 0x532a4c, r->eax);
    r->eax = r->ebp - 0x20;
    call(r, 0x4ca210, 0);
    r->eax = rd32(r, r->ebp - 0x38);
    r->port->env.chain = r->eax;
    r->edi = rd32(r, r->ebp - 0x14);
    r->esi = rd32(r, r->ebp - 0x10);
    r->edx = rd32(r, r->ebp - 0xc);
    r->ecx = rd32(r, r->ebp - 0x8);
    r->ebx = rd32(r, r->ebp - 0x4);
    return;
at_45cb32:
    if ((uint16_t)((r->ebx & 0xffff)) != (uint16_t)0x5f)
    {
        goto at_45cb54;
    }
at_45cb38:
    r->eax = r->ecx;
    call(r, 0x4b4600, 0);
at_45cb3f:
    r->eax = r->ebp - 0x20;
    r->edx = r->edi;
    wr32(r, r->ebp - 0x2c, r->edi);
    call(r, 0x4ca210, 0);
    wr32(r, r->ebp - 0x2c, r->edi);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_45c9db;
at_45cb54:
    if ((uint16_t)((r->ebx & 0xffff)) == (uint16_t)0x60)
    {
        goto at_45cb7b;
    }
    if ((uint16_t)((r->ebx & 0xffff)) == (uint16_t)0x5c)
    {
        goto at_45cb84;
    }
    if ((uint16_t)((r->ebx & 0xffff)) == (uint16_t)0x61)
    {
        goto at_45cb8d;
    }
    if ((uint16_t)((r->ebx & 0xffff)) == (uint16_t)0xe)
    {
        goto at_45cb96;
    }
    if ((uint16_t)((r->ebx & 0xffff)) != (uint16_t)0x65 && !r->port->env.failed)
    {
        goto at_45cb3f;
    }
    r->eax = r->ecx;
    call(r, 0x4b4af0, 0);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_45cb3f;
at_45cb7b:
    r->eax = r->ecx;
    call(r, 0x4b4610, 0);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_45cb3f;
at_45cb84:
    r->eax = r->ecx;
    call(r, 0x4b4620, 0);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_45cb3f;
at_45cb8d:
    r->eax = r->ecx;
    call(r, 0x4b4630, 0);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_45cb3f;
at_45cb96:
    r->eax = r->ecx;
    call(r, 0x4b4950, 0);
    if (r->eax != 0x1 && !r->port->env.failed)
    {
        goto at_45cb3f;
    }
    if (r->port->env.failed)
    {
        return;
    }
    goto at_45cb38;
at_45cba4:
    r->edx = rd32(r, r->ecx + 0x160);
    r->eax = r->ebp - 0x1c;
    r->edx = rd32(r, r->edx + 0x15c);
    call(r, 0x4ca280, 0);
    r->edx = 0x3;
    r->ebx = r->esi;
    wr32(r, r->ebp - 0x2c, r->edx);
    r->edx = 0;
    r->eax = r->ebp - 0x18;
    set_low8(&r->edx, rd8(r, r->ebp - 0x24));
    call(r, 0x4cda90, 0);
    r->ebx = 0x4;
    r->eax = rd32(r, 0x532b3c);
    wr32(r, r->ebp - 0x2c, r->ebx);
    r->ebx = r->esi;
    if (r->edi != r->eax)
    {
        goto at_45cbf2;
    }
    if (rd32(r, r->ebp - 0x24) != 0x40)
    {
        goto at_45cbf2;
    }
at_45cbe8:
    call(r, 0x4cda10, 0);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_45c9db;
at_45cbf2:
    if (r->ebx != 0x1)
    {
        goto at_45cc0d;
    }
    if (rd32(r, r->ebp - 0x24) == 0x20)
    {
        goto at_45cc0d;
    }
    r->edx = 0;
    r->eax = r->ecx;
    set_low8(&r->edx, rd8(r, r->ebp - 0x24));
    call(r, 0x4b4cb0, 0);
    if (r->eax == 0 && !r->port->env.failed)
    {
        goto at_45cbe8;
    }
at_45cc0d:
    if (r->ebx != 0x1 && !r->port->env.failed)
    {
        goto at_45cbe8;
    }
    r->edx = rd32(r, r->ebp - 0x18);
    r->eax = r->ecx;
    call(r, 0x4b4790, 0);
    if (r->eax != r->ebx && !r->port->env.failed)
    {
        goto at_45cbe8;
    }
    r->eax = r->ecx;
    call(r, 0x4b4610, 0);
    call(r, 0x4cda10, 0);
    if (r->port->env.failed)
    {
        return;
    }
    goto at_45c9db;
}

uint32_t vertrix_port_text_field_key_input_45c9a0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x3c
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
