#include "rtltextloads.h"

/* The game's texts loaded from the language file: the file object at ebp - 0x84, each key built
 * at ebp - 0x188 (0x45f540), counted (0x48a050) and its entries read (0x48a4a0, 0x48a560), the
 * sections opened by 0x48a2d0. */

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
} Texts;

/* A call (with count stack arguments, nearest first) of the tracked registers. */
static void call(Texts *r, uint32_t target, const uint32_t *stack, unsigned count)
{
    r->eax = port_call_registers(r->port, target, r->eax, r->edx, r->ebx, r->ecx, r->esi, r->edi,
                                 r->ebp, stack, count);
    r->edx = vertrix_lift_edx;
}

static uint32_t local(Texts *r, uint32_t offset)
{
    return port_u32(r->port, r->ebp, offset);
}

static void set_local(Texts *r, uint32_t offset, uint32_t value)
{
    port_set32(r->port, r->ebp, offset, value);
}

static uint32_t g32(Texts *r, uint32_t address)
{
    return port_u32(r->port, 0, address);
}

/* Sections read into 0x532d8c, 0x532ebc, 0x5330a8, 0x532fec, 0x53305c, 0x5332c0, 0x533450,
 * 0x533310, 0x533d7c, 0x533dcc, 0x533360, 0x5333b0, 0x533400, 0x53ba88 and 0x533e1c
 * (0x413c15..0x413fd4). */
static void read_s1a(Texts *r)
{
    r->ebx = 0x50cbfd;
    r->edx = 0x4fcde8;
    r->eax = r->ebp - 0x188;
    r->ecx = 0x50cc09;
    set_local(r, -0x60u, r->esi);
    call(r, 0x45f540, NULL, 0);
    r->edx = r->ebp - 0x188;
    r->eax = r->ebp - 0x84;
    r->ebx = 0x4c;
    call(r, 0x48a050, NULL, 0);
    r->edx = 0x532d8c;
    r->eax = r->ebp - 0x84;
    {
        uint32_t args[1] = {0x0};
        call(r, 0x48a4a0, args, 1);
    }
    r->eax = r->ebp - 0x84;
    r->ebx = 0x50cc0a;
    r->edx = 0x4fcde8;
    call(r, 0x48a2d0, NULL, 0);
    r->eax = r->ebp - 0x188;
    r->ecx = 0x50cc1a;
    call(r, 0x45f540, NULL, 0);
    r->edx = r->ebp - 0x188;
    r->eax = r->ebp - 0x84;
    r->ebx = 0x4c;
    call(r, 0x48a050, NULL, 0);
    r->edx = 0x532ebc;
    r->eax = r->ebp - 0x84;
    {
        uint32_t args[1] = {0x0};
        call(r, 0x48a4a0, args, 1);
    }
    r->eax = r->ebp - 0x84;
    r->ebx = 0x50cc1b;
    r->edx = 0x4fcde8;
    call(r, 0x48a2d0, NULL, 0);
    r->eax = r->ebp - 0x188;
    r->ecx = 0x50cc2d;
    call(r, 0x45f540, NULL, 0);
    r->edx = r->ebp - 0x188;
    r->eax = r->ebp - 0x84;
    r->ebx = 0x2f;
    call(r, 0x48a050, NULL, 0);
    r->edx = 0x5330a8;
    r->eax = r->ebp - 0x84;
    {
        uint32_t args[1] = {0x0};
        call(r, 0x48a4a0, args, 1);
    }
    r->eax = r->ebp - 0x84;
    r->ebx = 0x50cc2e;
    r->edx = 0x4fcde8;
    call(r, 0x48a2d0, NULL, 0);
    r->eax = r->ebp - 0x188;
    r->ecx = 0x50cc44;
    call(r, 0x45f540, NULL, 0);
    r->edx = r->ebp - 0x188;
    r->eax = r->ebp - 0x84;
    r->ebx = 0x1c;
    call(r, 0x48a050, NULL, 0);
    r->edx = 0x532fec;
    r->eax = r->ebp - 0x84;
    {
        uint32_t args[1] = {0x0};
        call(r, 0x48a4a0, args, 1);
    }
    r->eax = r->ebp - 0x84;
    r->ebx = 0x50cc45;
    r->edx = 0x4fcde8;
    call(r, 0x48a2d0, NULL, 0);
    r->eax = r->ebp - 0x188;
    call(r, 0x45f540, NULL, 0);
    r->edx = r->ebp - 0x188;
    r->eax = r->ebp - 0x84;
    r->ecx = 0x50cc5a;
    r->ebx = 0x13;
    call(r, 0x48a050, NULL, 0);
    r->edx = 0x53305c;
    r->eax = r->ebp - 0x84;
    {
        uint32_t args[1] = {0x0};
        call(r, 0x48a4a0, args, 1);
    }
    r->eax = r->ebp - 0x84;
    r->ebx = 0x50cc5b;
    r->edx = 0x4fcde8;
    call(r, 0x48a2d0, NULL, 0);
    r->eax = r->ebp - 0x188;
    r->ecx = 0x50cc72;
    call(r, 0x45f540, NULL, 0);
    r->edx = r->ebp - 0x188;
    r->eax = r->ebp - 0x84;
    r->ebx = 0x14;
    call(r, 0x48a050, NULL, 0);
    r->edx = 0x5332c0;
    r->eax = r->ebp - 0x84;
    {
        uint32_t args[1] = {0x0};
        call(r, 0x48a4a0, args, 1);
    }
    r->ecx = 0x50cc73;
    r->ebx = 0x14;
    r->edx = 0x533450;
    r->eax = r->ebp - 0x84;
    {
        uint32_t args[1] = {r->esi};
        call(r, 0x48a4a0, args, 1);
    }
    r->eax = r->ebp - 0x84;
    r->ebx = 0x50cc74;
    r->edx = 0x4fcde8;
    call(r, 0x48a2d0, NULL, 0);
    r->eax = r->ebp - 0x188;
    r->ecx = 0x50cc87;
    call(r, 0x45f540, NULL, 0);
    r->edx = r->ebp - 0x188;
    r->eax = r->ebp - 0x84;
    r->ebx = 0x14;
    call(r, 0x48a050, NULL, 0);
    r->edx = 0x533310;
    r->eax = r->ebp - 0x84;
    {
        uint32_t args[1] = {0x0};
        call(r, 0x48a4a0, args, 1);
    }
    r->eax = r->ebp - 0x84;
    r->ebx = 0x50cc88;
    r->edx = 0x4fcde8;
    call(r, 0x48a2d0, NULL, 0);
    r->eax = r->ebp - 0x188;
    r->ecx = 0x50cc9b;
    call(r, 0x45f540, NULL, 0);
    r->edx = r->ebp - 0x188;
    r->eax = r->ebp - 0x84;
    r->ebx = 0x14;
    call(r, 0x48a050, NULL, 0);
    r->edx = 0x533d7c;
    r->eax = r->ebp - 0x84;
    {
        uint32_t args[1] = {0x0};
        call(r, 0x48a4a0, args, 1);
    }
    r->ecx = 0x50cc9c;
    r->ebx = 0x14;
    r->edx = 0x533dcc;
    r->eax = r->ebp - 0x84;
    {
        uint32_t args[1] = {r->esi};
        call(r, 0x48a4a0, args, 1);
    }
    r->eax = r->ebp - 0x84;
    r->ebx = 0x50cc9d;
    r->edx = 0x4fcde8;
    call(r, 0x48a2d0, NULL, 0);
    r->eax = r->ebp - 0x188;
    call(r, 0x45f540, NULL, 0);
    r->edx = r->ebp - 0x188;
    r->eax = r->ebp - 0x84;
    r->ecx = 0x50ccaf;
    r->ebx = 0x14;
    call(r, 0x48a050, NULL, 0);
    r->edx = 0x533360;
    r->eax = r->ebp - 0x84;
    {
        uint32_t args[1] = {0x0};
        call(r, 0x48a4a0, args, 1);
    }
    r->ecx = 0x50ccb0;
    r->ebx = 0x14;
    r->edx = 0x5333b0;
    r->eax = r->ebp - 0x84;
    {
        uint32_t args[1] = {r->esi};
        call(r, 0x48a4a0, args, 1);
    }
    r->ecx = 0x50ccb1;
    r->ebx = 0x14;
    r->edx = 0x533400;
    r->eax = r->ebp - 0x84;
    {
        uint32_t args[1] = {0x2};
        call(r, 0x48a4a0, args, 1);
    }
    r->eax = r->ebp - 0x84;
    r->ebx = 0x50ccb2;
    r->edx = 0x4fcde8;
    call(r, 0x48a2d0, NULL, 0);
    r->eax = r->ebp - 0x188;
    r->ecx = 0x50ccc5;
    call(r, 0x45f540, NULL, 0);
    r->edx = r->ebp - 0x188;
    r->eax = r->ebp - 0x84;
    r->ebx = 0x14;
    call(r, 0x48a050, NULL, 0);
    r->edx = 0x53ba88;
    r->eax = r->ebp - 0x84;
    {
        uint32_t args[1] = {0x0};
        call(r, 0x48a4a0, args, 1);
    }
    r->eax = r->ebp - 0x84;
    r->ebx = 0x50ccc6;
    r->edx = 0x4fcde8;
    call(r, 0x48a2d0, NULL, 0);
    r->eax = r->ebp - 0x188;
    r->ecx = 0x50ccd6;
    call(r, 0x45f540, NULL, 0);
    r->edx = r->ebp - 0x188;
    r->eax = r->ebp - 0x84;
    r->ebx = 0x1a2;
    call(r, 0x48a050, NULL, 0);
    r->edx = 0x533e1c;
    r->eax = r->ebp - 0x84;
    {
        uint32_t args[1] = {0x0};
        call(r, 0x48a4a0, args, 1);
    }
    r->eax = r->ebp - 0x84;
    r->ecx = 0x533e1c;
    call(r, 0x48a2d0, NULL, 0);
}

/* Sections read into 0x53453c, 0x534588, 0x5345d4, 0x5334a0, 0x533578, 0x533650, 0x534620,
 * 0x534670, 0x5346c0, 0x534750 and 0x5347a0, and the key of the fourteen entries at 0x5336ac
 * counted (0x413fed..0x41426f). */
static void read_s1b(Texts *r)
{
    r->ebx = 0x50ccd7;
    r->edx = 0x4fcde8;
    r->eax = r->ebp - 0x188;
    r->ecx = 0x50cce5;
    call(r, 0x45f540, NULL, 0);
    r->edx = r->ebp - 0x188;
    r->eax = r->ebp - 0x84;
    r->ebx = 0x13;
    call(r, 0x48a050, NULL, 0);
    r->edx = 0x53453c;
    r->eax = r->ebp - 0x84;
    {
        uint32_t args[1] = {0x0};
        call(r, 0x48a4a0, args, 1);
    }
    r->ecx = 0x50cce6;
    r->ebx = 0x13;
    r->edx = 0x534588;
    r->eax = r->ebp - 0x84;
    {
        uint32_t args[1] = {0x1};
        call(r, 0x48a4a0, args, 1);
    }
    r->ecx = 0x50cce7;
    r->ebx = 0x13;
    r->edx = 0x5345d4;
    r->eax = r->ebp - 0x84;
    {
        uint32_t args[1] = {0x2};
        call(r, 0x48a4a0, args, 1);
    }
    r->eax = r->ebp - 0x84;
    r->ebx = 0x50cce8;
    r->edx = 0x4fcde8;
    call(r, 0x48a2d0, NULL, 0);
    r->eax = r->ebp - 0x188;
    r->ecx = 0x50ccfc;
    call(r, 0x45f540, NULL, 0);
    r->edx = r->ebp - 0x188;
    r->eax = r->ebp - 0x84;
    r->ebx = 0x36;
    call(r, 0x48a050, NULL, 0);
    r->edx = 0x5334a0;
    r->eax = r->ebp - 0x84;
    {
        uint32_t args[1] = {0x0};
        call(r, 0x48a4a0, args, 1);
    }
    r->ecx = 0x50ccfd;
    r->ebx = 0x36;
    r->edx = 0x533578;
    r->eax = r->ebp - 0x84;
    {
        uint32_t args[1] = {0x1};
        call(r, 0x48a4a0, args, 1);
    }
    r->eax = r->ebp - 0x84;
    r->ebx = 0x50ccfe;
    r->edx = 0x4fcde8;
    call(r, 0x48a2d0, NULL, 0);
    r->eax = r->ebp - 0x188;
    r->ecx = 0x50cd11;
    call(r, 0x45f540, NULL, 0);
    r->edx = r->ebp - 0x188;
    r->eax = r->ebp - 0x84;
    r->ebx = 0x17;
    call(r, 0x48a050, NULL, 0);
    r->edx = 0x533650;
    r->eax = r->ebp - 0x84;
    {
        uint32_t args[1] = {0x0};
        call(r, 0x48a4a0, args, 1);
    }
    r->eax = r->ebp - 0x84;
    r->ebx = 0x50cd12;
    r->edx = 0x4fcde8;
    call(r, 0x48a2d0, NULL, 0);
    r->eax = r->ebp - 0x188;
    call(r, 0x45f540, NULL, 0);
    r->edx = r->ebp - 0x188;
    r->eax = r->ebp - 0x84;
    call(r, 0x48a050, NULL, 0);
    r->ecx = 0x50cd29;
    r->ebx = 0x14;
    r->edx = 0x534620;
    r->eax = r->ebp - 0x84;
    {
        uint32_t args[1] = {0x0};
        call(r, 0x48a4a0, args, 1);
    }
    r->ecx = 0x50cd2a;
    r->ebx = 0x14;
    r->edx = 0x534670;
    r->eax = r->ebp - 0x84;
    {
        uint32_t args[1] = {0x1};
        call(r, 0x48a4a0, args, 1);
    }
    r->ecx = 0x50cd2b;
    r->ebx = 0x14;
    r->edx = 0x5346c0;
    r->eax = r->ebp - 0x84;
    {
        uint32_t args[1] = {0x2};
        call(r, 0x48a4a0, args, 1);
    }
    r->eax = r->ebp - 0x84;
    r->ebx = 0x50cd2c;
    r->edx = 0x4fcde8;
    call(r, 0x48a2d0, NULL, 0);
    r->eax = r->ebp - 0x188;
    r->ecx = 0x50cd49;
    call(r, 0x45f540, NULL, 0);
    r->edx = r->ebp - 0x188;
    r->eax = r->ebp - 0x84;
    r->ebx = 0x14;
    call(r, 0x48a050, NULL, 0);
    r->edx = 0x534750;
    r->eax = r->ebp - 0x84;
    {
        uint32_t args[1] = {0x0};
        call(r, 0x48a4a0, args, 1);
    }
    r->eax = r->ebp - 0x84;
    r->ebx = 0x50cd4a;
    r->edx = 0x4fcde8;
    call(r, 0x48a2d0, NULL, 0);
    r->eax = r->ebp - 0x188;
    r->ecx = 0x32;
    call(r, 0x45f540, NULL, 0);
    r->edx = r->ebp - 0x188;
    r->eax = r->ebp - 0x84;
    r->ebx = 0x14;
    call(r, 0x48a050, NULL, 0);
    r->edx = 0x5347a0;
    r->eax = r->ebp - 0x84;
    {
        uint32_t args[1] = {0x0};
        call(r, 0x48a560, args, 1);
    }
    r->eax = r->ebp - 0x84;
    r->ebx = 0x50cd5e;
    r->edx = 0x4fcde8;
    call(r, 0x48a2d0, NULL, 0);
    r->eax = r->ebp - 0x188;
    r->edi = 0x5336ac;
    call(r, 0x45f540, NULL, 0);
    r->edx = r->ebp - 0x188;
    r->eax = r->ebp - 0x84;
    r->esi = 0;
    call(r, 0x48a050, NULL, 0);
}

/* Sections read into 0x53483c, 0x534888 and 0x5348d4 and the section 0x5396e8 opened
 * (0x414295..0x414333). */
static void read_s2(Texts *r)
{
    r->eax = r->ebp - 0x84;
    r->ebx = 0x50cd6d;
    r->edx = 0x4fcde8;
    r->ecx = 0x50cd7e;
    call(r, 0x48a2d0, NULL, 0);
    r->eax = r->ebp - 0x188;
    r->esi = 0x53483c;
    call(r, 0x45f540, NULL, 0);
    r->edx = r->ebp - 0x188;
    r->eax = r->ebp - 0x84;
    r->ebx = 0x13;
    call(r, 0x48a050, NULL, 0);
    r->edx = 0x53483c;
    r->eax = r->ebp - 0x84;
    r->edi = 0;
    {
        uint32_t args[1] = {0x0};
        call(r, 0x48a4a0, args, 1);
    }
    r->ebx = 0x13;
    r->edx = 0x534888;
    r->eax = r->ebp - 0x84;
    r->ecx = 0;
    set_local(r, -0x58u, r->edi);
    {
        uint32_t args[1] = {0x1};
        call(r, 0x48a560, args, 1);
    }
    r->ebx = 0x13;
    r->edx = 0x5348d4;
    r->eax = r->ebp - 0x84;
    r->ecx = 0;
    r->edi = 0x534f5c;
    {
        uint32_t args[1] = {0x2};
        call(r, 0x48a560, args, 1);
    }
    r->eax = r->ebp - 0x84;
    r->edx = 0x5396e8;
    r->ecx = 0x53612c;
    call(r, 0x48a2d0, NULL, 0);
}

/* The key of the ten pairs at 0x534920 and 0x534c18 counted (0x4143a3..0x4143d0). */
static void read_s3(Texts *r)
{
    r->ebx = 0x50cd82;
    r->edx = 0x4fcde8;
    r->eax = r->ebp - 0x188;
    r->ecx = 0x1;
    r->edi = 0x534920;
    call(r, 0x45f540, NULL, 0);
    r->edx = r->ebp - 0x188;
    r->eax = r->ebp - 0x84;
    r->esi = 0;
    call(r, 0x48a050, NULL, 0);
}

/* Sections read into 0x540050, 0x540064 and 0x540078 and the section 0x5400f0 opened
 * (0x414495..0x414523). */
static void read_s5(Texts *r)
{
    r->ebx = 0x50cd99;
    r->edx = 0x4fcde8;
    r->eax = r->ebp - 0x188;
    r->ecx = 0x50cdab;
    call(r, 0x45f540, NULL, 0);
    r->edx = r->ebp - 0x188;
    r->eax = r->ebp - 0x84;
    r->ebx = 0x5;
    call(r, 0x48a050, NULL, 0);
    r->edx = 0x540050;
    r->eax = r->ebp - 0x84;
    {
        uint32_t args[1] = {0x0};
        call(r, 0x48a4a0, args, 1);
    }
    r->ebx = 0x5;
    r->edx = 0x540064;
    r->eax = r->ebp - 0x84;
    r->ecx = 0;
    r->esi = 0x540050;
    {
        uint32_t args[1] = {0x1};
        call(r, 0x48a560, args, 1);
    }
    r->ebx = 0x5;
    r->edx = 0x540078;
    r->eax = r->ebp - 0x84;
    r->ecx = 0;
    r->edi = 0x540294;
    {
        uint32_t args[1] = {0x2};
        call(r, 0x48a560, args, 1);
    }
    r->eax = r->ebp - 0x84;
    r->edx = 0x5400f0;
    r->ecx = 0x54008c;
    call(r, 0x48a2d0, NULL, 0);
}

/* The key of the nine entries at 0x53c0cc counted (0x414648..0x414670). */
static void read_s6(Texts *r)
{
    r->ebx = 0x50cdaf;
    r->edx = 0x4fcde8;
    r->eax = r->ebp - 0x188;
    r->esi = 0x53c0cc;
    call(r, 0x45f540, NULL, 0);
    r->edx = r->ebp - 0x188;
    r->eax = r->ebp - 0x84;
    r->edi = 0;
    call(r, 0x48a050, NULL, 0);
}

/* The key of the nine entries at 0x53c93c counted (0x414699..0x4146cc). */
static void read_s7(Texts *r)
{
    r->eax = r->ebp - 0x84;
    r->ebx = 0x50cdc5;
    r->edx = 0x4fcde8;
    call(r, 0x48a2d0, NULL, 0);
    r->eax = r->ebp - 0x188;
    r->edi = 0x53c93c;
    call(r, 0x45f540, NULL, 0);
    r->edx = r->ebp - 0x188;
    r->eax = r->ebp - 0x84;
    r->esi = 0;
    call(r, 0x48a050, NULL, 0);
}

/* The key of the forty entries at 0x53d998 counted (0x4146f5..0x414728). */
static void read_s8(Texts *r)
{
    r->eax = r->ebp - 0x84;
    r->ebx = 0x50cdd6;
    r->edx = 0x4fcde8;
    call(r, 0x48a2d0, NULL, 0);
    r->eax = r->ebp - 0x188;
    r->edi = 0x53d998;
    call(r, 0x45f540, NULL, 0);
    r->edx = r->ebp - 0x188;
    r->eax = r->ebp - 0x84;
    r->esi = 0;
    call(r, 0x48a050, NULL, 0);
}

/* The key of the forty entries at 0x53fe20 counted (0x4147d6..0x4147fe). */
static void read_s10(Texts *r)
{
    r->ebx = 0x50cde7;
    r->edx = 0x4fcde8;
    r->eax = r->ebp - 0x188;
    r->edi = 0x53fe20;
    call(r, 0x45f540, NULL, 0);
    r->edx = r->ebp - 0x188;
    r->eax = r->ebp - 0x84;
    r->esi = 0;
    call(r, 0x48a050, NULL, 0);
}

/* Sections read into 0x532d3c, 0x532ca4, 0x532cf0 and 0x5347f0 and the file closed
 * (0x41486e..0x4149b4). */
static void read_s12(Texts *r)
{
    r->ebx = 0x50cdf5;
    r->edx = 0x4fcde8;
    r->eax = r->ebp - 0x188;
    call(r, 0x45f540, NULL, 0);
    r->edx = r->ebp - 0x188;
    r->eax = r->ebp - 0x84;
    r->ebx = 0x13;
    call(r, 0x48a050, NULL, 0);
    r->edx = 0x532d3c;
    r->eax = r->ebp - 0x84;
    r->ecx = g32(r, 0x532d88);
    {
        uint32_t args[1] = {0x0};
        call(r, 0x48a560, args, 1);
    }
    r->eax = r->ebp - 0x84;
    r->ebx = 0x50ce03;
    r->edx = 0x4fcde8;
    call(r, 0x48a2d0, NULL, 0);
    r->eax = r->ebp - 0x188;
    call(r, 0x45f540, NULL, 0);
    r->edx = r->ebp - 0x188;
    r->eax = r->ebp - 0x84;
    r->ebx = 0x13;
    call(r, 0x48a050, NULL, 0);
    r->edx = 0x532ca4;
    r->eax = r->ebp - 0x84;
    r->ecx = g32(r, 0x532d88);
    {
        uint32_t args[1] = {0x0};
        call(r, 0x48a560, args, 1);
    }
    r->eax = r->ebp - 0x84;
    r->ebx = 0x50ce13;
    r->edx = 0x4fcde8;
    call(r, 0x48a2d0, NULL, 0);
    r->eax = r->ebp - 0x188;
    call(r, 0x45f540, NULL, 0);
    r->edx = r->ebp - 0x188;
    r->eax = r->ebp - 0x84;
    r->ebx = 0x13;
    call(r, 0x48a050, NULL, 0);
    r->edx = 0x532cf0;
    r->eax = r->ebp - 0x84;
    r->ecx = g32(r, 0x532d88);
    {
        uint32_t args[1] = {0x0};
        call(r, 0x48a560, args, 1);
    }
    r->eax = r->ebp - 0x84;
    r->ebx = 0x50ce20;
    r->edx = 0x4fcde8;
    call(r, 0x48a2d0, NULL, 0);
    r->eax = r->ebp - 0x188;
    r->ecx = 0;
    call(r, 0x45f540, NULL, 0);
    r->edx = r->ebp - 0x188;
    r->eax = r->ebp - 0x84;
    r->ebx = 0x13;
    call(r, 0x48a050, NULL, 0);
    r->edx = 0x5347f0;
    r->eax = r->ebp - 0x84;
    {
        uint32_t args[1] = {0x0};
        call(r, 0x48a560, args, 1);
    }
    r->eax = r->ebp - 0x84;
    r->edi = 0;
    call(r, 0x48a2d0, NULL, 0);
    r->edx = 0;
    r->eax = r->ebp - 0x84;
    set_local(r, -0x60u, r->edi);
    call(r, 0x489fa0, NULL, 0);
    r->eax = local(r, -0x6cu);
}

/* An entry of a four-part table read when its name (at esi) is not 0x50cd7f / 0x50cdac and its key
 * exists (0x45f540, 0x45f590): its count read (0x48a050 with ebx count and ecx first), parts 0 and
 * 1 (0x48a4a0 with second) and 2 and 3 (0x48a560) into the four destinations, its number (0x48a2e0
 * of the slot) stored at table + slot and the section closed (0x48a2d0). */
static void read_entry(Texts *r, uint32_t count, uint32_t first, uint32_t second,
                       const uint32_t *destinations, uint32_t slot, uint32_t table)
{
    uint32_t args[1];
    r->edx = 0x4fcde8;
    r->eax = r->ebp - 0x188;
    r->ebx = port_u32(r->port, r->esi, 0);
    call(r, 0x45f540, NULL, 0);
    r->eax = r->ebp - 0x188;
    call(r, 0x45f590, NULL, 0);
    if (r->eax != 1)
    {
        return;
    }
    r->edx = r->ebp - 0x188;
    r->eax = r->ebp - 0x84;
    r->ecx = first;
    r->ebx = count;
    call(r, 0x48a050, NULL, 0);
    args[0] = 0;
    r->eax = r->ebp - 0x84;
    r->edx = destinations[0];
    call(r, 0x48a4a0, args, 1);
    args[0] = 1;
    r->ecx = second;
    r->ebx = count;
    r->edx = destinations[1];
    r->eax = r->ebp - 0x84;
    call(r, 0x48a4a0, args, 1);
    args[0] = 2;
    r->ebx = count;
    r->edx = destinations[2];
    r->eax = r->ebp - 0x84;
    r->ecx = 0;
    call(r, 0x48a560, args, 1);
    args[0] = 3;
    r->ebx = count;
    r->eax = r->ebp - 0x84;
    r->edx = destinations[3];
    r->ecx = 0;
    call(r, 0x48a560, args, 1);
    r->eax = r->ebp - 0x84;
    r->edx = slot;
    call(r, 0x48a2e0, NULL, 0);
    port_set32(r->port, r->edx, table, r->eax);
    r->eax = r->ebp - 0x84;
    call(r, 0x48a2d0, NULL, 0);
}

/* A list of entries (0x48a4a0, ecx mark, ebx size) read count times into destination on, step
 * apart, its index (esi or edi as kept) pushed. */
static void read_list(Texts *r, uint32_t *index, uint32_t *destination, uint32_t count,
                      uint32_t mark, uint32_t size, uint32_t step)
{
    do
    {
        uint32_t args[1];
        r->ecx = mark;
        r->ebx = size;
        args[0] = *index;
        r->eax = r->ebp - 0x84;
        r->edx = *destination;
        call(r, 0x48a4a0, args, 1);
        (*index)++;
        *destination += step;
    } while (*index < count && !r->port->env.failed);
}

/* A column searched back from its entry 39 (at start, step apart) while 0x4ccfe0 gives 0 against
 * mark: esi left the count of entries up to the last that does not. */
static uint32_t last_named(Texts *r, uint32_t start, uint32_t mark, uint32_t step)
{
    r->esi = 0x28;
    r->ebx = start;
    r->ecx = 0x27;
    do
    {
        r->edx = mark;
        r->eax = port_u32(r->port, r->ebx, 0);
        call(r, 0x4ccfe0, NULL, 0);
        if (r->eax != 0)
        {
            break;
        }
        r->ebx -= step;
        r->ecx--;
        r->esi--;
    } while ((int32_t)r->ecx >= 0 && !r->port->env.failed);
    return r->esi;
}

/* Original 0x413bd0 (guarded 0x5139a4): the game's texts read from the language file (0x489f90 to
 * 0x489fa0) section by section into their tables: plain lists, the nineteen level entries (from
 * 0x53483c, four parts into 0x534f5c.., 0x53a8b8.. and the two from 0x5396e8/0x53612c, their
 * numbers at 0x53969c), the ten level title pairs and their counts at 0x534f10, the five tune
 * entries (from 0x540050, their numbers at 0x54021c), the help, story, hint and tip pages and the
 * counts of their named lines (0x53fd38, 0x540000). eax the restored chain, edx kept. */
uint32_t vertrix_port_texts_load_413bd0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x18c
    };
    Port port;
    uint8_t stack[BELOW + 8];
    Texts r;
    uint32_t record;
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    r.port = &port;
    r.ebp = entry->esp - 4;
    record = r.ebp - 0x6c;
    port_set32(&port, r.ebp, 0, entry->ebp);
    port_set32(&port, r.ebp, -4u, entry->ebx);
    port_set32(&port, r.ebp, -8u, entry->ecx);
    port_set32(&port, r.ebp, -0xcu, entry->edx);
    port_set32(&port, r.ebp, -0x10u, entry->esi);
    port_set32(&port, r.ebp, -0x14u, entry->edi);
    port_set32(&port, record, 0, port.env.chain);
    port.env.chain = record;
    r.edx = 0x4ec1ec;
    r.ecx = 0x5139a4;
    r.esi = 1;
    r.ebx = 0;
    r.edi = entry->edi;
    set_local(&r, -0x68u, r.edx);
    set_local(&r, -0x64u, r.ecx);
    set_local(&r, -0x60u, r.ebx);
    r.eax = r.ebp - 0x84;
    call(&r, 0x489f90, NULL, 0);
    read_s1a(&r);
    r.edx = r.ecx + 0x688;
    do
    {
        r.eax = r.ecx;
        r.ecx += 4;
        call(&r, 0x4ca710, NULL, 0);
    } while (r.ecx != r.edx && !port.env.failed);
    read_s1b(&r);
    do
    {
        uint32_t args[1];
        r.ecx = 0x32;
        r.ebx = 0x14;
        args[0] = r.esi;
        r.eax = r.ebp - 0x84;
        r.edx = r.edi;
        call(&r, 0x48a560, args, 1);
        r.esi++;
        r.edi += 0x50;
    } while (r.esi < 0xe && !port.env.failed);
    read_s2(&r);
    r.eax = 0x53a8b8;
    set_local(&r, -0x44u, r.edx);
    set_local(&r, -0x40u, r.ecx);
    set_local(&r, -0x48u, r.eax);
    do
    {
        r.eax = local(&r, -0x58u) << 2;
        r.ebx = 0;
        r.edx = 0x50cd7f;
        port_set32(&port, r.eax, 0x53969c, 0);
        set_local(&r, -0x54u, r.eax);
        r.eax = port_u32(&port, r.esi, 0);
        call(&r, 0x4ccfe0, NULL, 0);
        if (r.eax != 0)
        {
            uint32_t destinations[4] = {r.edi, local(&r, -0x40u), local(&r, -0x44u),
                                        local(&r, -0x48u)};
            read_entry(&r, 0x3c, 0x50cd80, 0x50cd81, destinations, local(&r, -0x54u), 0x53969c);
        }
        r.eax = local(&r, -0x48u) + 0xf0;
        r.edx = local(&r, -0x44u) + 0xf0;
        r.ecx = local(&r, -0x40u) + 0xf0;
        r.ebx = local(&r, -0x58u) + 1;
        r.esi += 4;
        r.edi += 0xf0;
        set_local(&r, -0x48u, r.eax);
        set_local(&r, -0x44u, r.edx);
        set_local(&r, -0x40u, r.ecx);
        set_local(&r, -0x58u, r.ebx);
    } while (r.ebx < 0x13 && !port.env.failed);
    read_s3(&r);
    r.edx = 0x534c18;
    set_local(&r, -0x38u, r.ecx);
    set_local(&r, -0x3cu, r.edx);
    do
    {
        uint32_t args[1];
        r.ecx = 0x50cd97;
        r.ebx = 0x13;
        args[0] = r.esi + r.esi;
        r.edx = r.edi;
        r.eax = r.ebp - 0x84;
        r.edi += 0x4c;
        call(&r, 0x48a4a0, args, 1);
        r.ebx = local(&r, -0x38u);
        r.edx = local(&r, -0x3cu);
        r.eax = r.ebp - 0x84;
        r.ecx = 0;
        args[0] = r.ebx;
        r.ebx = 0x13;
        r.esi++;
        call(&r, 0x48a560, args, 1);
        r.eax = local(&r, -0x3cu) + 0x4c;
        r.edx = local(&r, -0x38u) + 2;
        set_local(&r, -0x3cu, r.eax);
        set_local(&r, -0x38u, r.edx);
    } while (r.esi < 0xa && !port.env.failed);
    r.eax = r.ebp - 0x84;
    r.ecx = 0x2f8;
    call(&r, 0x48a2d0, NULL, 0);
    r.edi = 0;
    set_local(&r, -0x34u, r.ecx);
    do
    {
        r.esi = 0x534920 + local(&r, -0x34u);
        r.ecx = r.edi + 0x534920;
        port_set32(&port, r.edi, 0x534f10, 0);
        r.ebx = r.edi;
        do
        {
            r.edx = 0x50cd98;
            r.eax = port_u32(&port, r.ecx, 0);
            call(&r, 0x4ccfe0, NULL, 0);
            if (r.eax == 0)
            {
                break;
            }
            r.edx = port_u32(&port, r.ebx, 0x534f10) + 1;
            r.ecx += 0x4c;
            port_set32(&port, r.ebx, 0x534f10, r.edx);
        } while (r.ecx < r.esi && !port.env.failed);
        r.ecx = local(&r, -0x34u) + 4;
        r.edi += 4;
        set_local(&r, -0x34u, r.ecx);
    } while (r.edi != 0x4c && !port.env.failed);
    read_s5(&r);
    r.ebx = 0;
    r.eax = 0x540230;
    set_local(&r, -0x18u, r.ebx);
    set_local(&r, -0x2cu, r.edx);
    set_local(&r, -0x28u, r.ecx);
    set_local(&r, -0x30u, r.eax);
    do
    {
        r.eax = local(&r, -0x18u) << 2;
        r.ebx = 0;
        r.edx = 0x50cdac;
        port_set32(&port, r.eax, 0x54021c, 0);
        set_local(&r, -0x50u, r.eax);
        r.eax = port_u32(&port, r.esi, 0);
        call(&r, 0x4ccfe0, NULL, 0);
        if (r.eax != 0)
        {
            uint32_t destinations[4] = {local(&r, -0x28u), local(&r, -0x2cu), local(&r, -0x30u),
                                        r.edi};
            read_entry(&r, 5, 0x50cdad, 0x50cdae, destinations, local(&r, -0x50u), 0x54021c);
        }
        r.eax = local(&r, -0x30u) + 0x14;
        r.edx = local(&r, -0x2cu) + 0x14;
        r.ecx = local(&r, -0x28u) + 0x14;
        r.ebx = local(&r, -0x18u) + 1;
        r.esi += 4;
        r.edi += 0x14;
        set_local(&r, -0x30u, r.eax);
        set_local(&r, -0x2cu, r.edx);
        set_local(&r, -0x28u, r.ecx);
        set_local(&r, -0x18u, r.ebx);
    } while (r.ebx < 5 && !port.env.failed);
    read_s6(&r);
    read_list(&r, &r.edi, &r.esi, 9, 0x50cdc4, 0x3c, 0xf0);
    read_s7(&r);
    read_list(&r, &r.esi, &r.edi, 9, 0x50cdd5, 0x72, 0x1c8);
    read_s8(&r);
    read_list(&r, &r.esi, &r.edi, 0x28, 0x50cde5, 0x39, 0xe4);
    r.eax = r.ebp - 0x84;
    r.edx = 0;
    call(&r, 0x48a2d0, NULL, 0);
    set_local(&r, -0x20u, r.edx);
    set_local(&r, -0x1cu, r.edx);
    do
    {
        set_local(&r, -0x4cu, local(&r, -0x20u));
        r.edi = 0;
        set_local(&r, -0x24u, local(&r, -0x1cu));
        do
        {
            r.eax = local(&r, -0x24u);
            last_named(&r, r.edi + 0x22bc + local(&r, -0x4cu) + 0x53d998, 0x50cde6, 0xe4);
            r.eax = local(&r, -0x24u);
            r.edi += 4;
            r.edx = r.eax + 0xc;
            port_set32(&port, r.eax, 0x53fd38, r.esi);
            set_local(&r, -0x24u, r.edx);
        } while (r.edi != 0x4c && !port.env.failed);
        r.ecx = local(&r, -0x20u) + r.edi;
        r.ebx = local(&r, -0x1cu) + 4;
        set_local(&r, -0x20u, r.ecx);
        set_local(&r, -0x1cu, r.ebx);
    } while (r.ebx != 0xc && !port.env.failed);
    read_s10(&r);
    read_list(&r, &r.esi, &r.edi, 0x28, 0x50cdf3, 3, 0xc);
    r.eax = r.ebp - 0x84;
    call(&r, 0x48a2d0, NULL, 0);
    r.edi = 0;
    do
    {
        last_named(&r, r.edi + 0x1d4 + 0x53fe20, 0x50cdf4, 0xc);
        r.edi += 4;
        port_set32(&port, r.edi, 0x53fffc, r.esi);
    } while (r.edi != 0xc && !port.env.failed);
    read_s12(&r);
    port.env.chain = port_u32(&port, record, 0);
    return port_return(&port, port.env.chain, entry->edx);
}
