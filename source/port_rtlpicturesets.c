#include "port_rtlpicturesets.h"

/* The game's pictures loaded. */

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
} Registers;

static void call(Registers *r, uint32_t target)
{
    vertrix_lift_in_esi = r->esi;
    vertrix_lift_in_edi = r->edi;
    vertrix_lift_in_ebp = r->ebp;
    r->eax = lift_call_arguments(&r->port->env, target, r->eax, r->edx, r->ebx, r->ecx, NULL, 0);
    vertrix_lift_in_esi = vertrix_lift_in_edi = vertrix_lift_in_ebp = 0;
    r->edx = vertrix_lift_edx;
}

/* One step of the loading bar (0x418270 with 1). */
static void step(Registers *r)
{
    r->eax = 1;
    call(r, 0x418270);
}

/* The picture named ebx (in the folder 0x4fc188, 0x45f540) loaded into the picture at to
 * (0x4873d0). */
static void load_named(Registers *r, uint32_t to)
{
    r->eax = r->ebp - 0x10c;
    call(r, 0x45f540);
    r->edx = r->ebp - 0x10c;
    r->eax = to;
    call(r, 0x4873d0);
}

/* The picture whose name number is the byte at which (names at 0x533650) loaded into to. */
static void load_picture(Registers *r, uint32_t which, uint32_t to)
{
    r->eax = port_u8(r->port, 0, which) * 4 + 0x533650;
    r->edx = 0x4fc188;
    r->ebx = port_u32(r->port, r->eax, 0);
    load_named(r, to);
}

/* Original 0x45dca0: the game's pictures loaded, a step of the loading bar after each: the
 * pictures named by 0x513c4e, 0x513c4f and 0x53bd09 (the last given its five colour keys from
 * 0x5466c4 and 0x4fbf28..0x4fbf98, 0x487790 and 0x4877d0), 0x513c4d, 0x513c51, 0x513c53 and
 * 0x513c52, 0x513c54..0x513c5d; the tables made (0x45ec00, 0x45e400, 0x45eac0, 0x45e3c0); the
 * pictures named by 0x513c50, 0x513c5e and 0x513c5f; then 0x45e490 and 0x45e530. eax as left,
 * edx kept. */
uint32_t vertrix_port_game_pictures_load_45dca0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x110
    };
    static const uint32_t keys[5][2] = {
        {0x5466c4, 0x4fbf28}, {0x4fbf48, 0x4fbf4c}, {0x4fbf50, 0x4fbf54},
        {0x4fbf94, 0x4fbf98}, {0x4fbf84, 0x4fbf88},
    };
    static const uint32_t middle[][2] = {
        {0x513c54, 0x544c64}, {0x513c55, 0x544d0c}, {0x513c56, 0x544c80}, {0x513c57, 0x544c9c},
        {0x513c58, 0x544cb8}, {0x513c59, 0x544cd4}, {0x513c5a, 0x544cf0}, {0x513c5b, 0x546500},
        {0x513c5c, 0x54651c}, {0x513c5d, 0x546538},
    };
    Port port;
    uint8_t stack[BELOW + 8];
    Registers r;
    unsigned index;
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    r.port = &port;
    r.eax = entry->eax;
    r.edx = entry->edx;
    r.ebx = entry->ebx;
    r.ecx = entry->ecx;
    r.esi = entry->esi;
    r.edi = entry->edi;
    r.ebp = entry->esp - 4;
    port_set32(&port, r.ebp, 0, entry->ebp);
    port_set32(&port, r.ebp, -4u, entry->ebx);
    port_set32(&port, r.ebp, -8u, entry->edx);
    load_picture(&r, 0x513c4e, 0x5449c4);
    step(&r);
    load_picture(&r, 0x513c4f, 0x5449e0);
    step(&r);
    load_picture(&r, 0x53bd09, 0x5449fc);
    for (index = 0; index < 5 && !port.env.failed; index++)
    {
        r.eax = 0x5449fc;
        r.ebx = port_u32(&port, 0, keys[index][0]);
        r.edx = port_u32(&port, 0, keys[index][1]);
        call(&r, 0x487790);
        r.eax = 0x5449fc;
        r.edx = port_u32(&port, 0, keys[index][1]);
        call(&r, 0x4877d0);
    }
    step(&r);
    load_picture(&r, 0x513c4d, 0x544a18);
    step(&r);
    load_picture(&r, 0x513c51, 0x544c10);
    step(&r);
    r.eax = port_u8(&port, 0, 0x513c53) * 4 + 0x533650;
    r.ebx = port_u32(&port, r.eax, 0);
    r.edx = 0x4fc188;
    r.eax = r.ebp - 0x10c;
    call(&r, 0x45f540);
    r.edx = r.ebp - 0x10c;
    r.eax = 0x544c48;
    r.ebx = 0;
    call(&r, 0x4873d0);
    r.ebx = port_u8(&port, 0, 0x513c52) * 4 + 0x533650;
    r.edx = 0x4fc188;
    step(&r);
    r.ebx = port_u32(&port, r.ebx, 0);
    load_named(&r, 0x544c2c);
    step(&r);
    for (index = 0; index < sizeof middle / sizeof middle[0] && !port.env.failed; index++)
    {
        load_picture(&r, middle[index][0], middle[index][1]);
        step(&r);
    }
    call(&r, 0x45ec00);
    r.ebx = 0;
    step(&r);
    call(&r, 0x45e400);
    r.ebx = port_u8(&port, 0, 0x513c50);
    step(&r);
    call(&r, 0x45eac0);
    r.ebx <<= 2;
    step(&r);
    call(&r, 0x45e3c0);
    r.ebx += 0x533650;
    step(&r);
    r.ebx = port_u32(&port, r.ebx, 0);
    r.edx = 0x4fc188;
    load_named(&r, 0x546650);
    step(&r);
    load_picture(&r, 0x513c5e, 0x54666c);
    step(&r);
    load_picture(&r, 0x513c5f, 0x546688);
    step(&r);
    call(&r, 0x45e490);
    call(&r, 0x45e530);
    step(&r);
    return port_return(&port, r.eax, entry->edx);
}
