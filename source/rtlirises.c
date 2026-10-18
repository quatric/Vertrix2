#include "rtlirises.h"

/* The screen's iris step between levels. */

/* A call (with count stack arguments, nearest first) that leaves its eax and
 * edx in *eax and *edx; the eax. */
static uint32_t iris_call(Port *port, uint32_t *eax, uint32_t *edx, uint32_t target, uint32_t a,
                          uint32_t d, uint32_t ebx, uint32_t ecx, uint32_t esi, uint32_t edi,
                          uint32_t ebp, const uint32_t *stack, unsigned count)
{
    *eax = port_call_registers(port, target, a, d, ebx, ecx, esi, edi, ebp, stack, count);
    *edx = vertrix_lift_edx;
    return *eax;
}

/* A blit (0x47ce10) of the back buffer 0x558c88 onto the screen 0x558c7c with
 * ebx and ecx and the four stack arguments a0..a3 (nearest first). */
static void blit(Port *port, uint32_t *eax, uint32_t *edx, uint32_t ebx, uint32_t ecx, uint32_t esi,
                 uint32_t edi, uint32_t ebp, uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3)
{
    uint32_t args[4];
    args[0] = a0;
    args[1] = a1;
    args[2] = a2;
    args[3] = a3;
    iris_call(port, eax, edx, 0x47ce10, port_u32(port, 0, 0x558c7c), port_u32(port, 0, 0x558c88),
              ebx, ecx, esi, edi, ebp, args, 4);
}

/* The flags, guard and frame slot that tell the two irises apart. */
typedef struct IrisKind
{
    uint32_t guard;   /* the guard record's handler data */
    uint32_t started; /* the byte set while the iris runs */
    uint32_t size;    /* the size last drawn */
    uint32_t game;    /* the frame slot of the game */
} IrisKind;

/* The start of an iris step: the guard record set; the first step (started 0)
 * clears the size, marks it and starts the game (0x4b7cd0, 0x472250, 0x41d640);
 * 0x4b7d10, 0x41d670 with 4, 0x472350; the new size (the +0x58 of the first of
 * 0x54676c by 0x4b5eb0, at ebp-0x4c), 0x486d00 of 0x5b9c50; at size 0 the whole
 * screen cleared (0x47ce10 of 0x558c80's width and height). */
static void iris_begin(Port *port, uint32_t *eax, uint32_t *edx, uint32_t *ebx, uint32_t *ecx,
                       uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t game,
                       const IrisKind *kind)
{
    uint32_t record = ebp - 0x70;
#define CALL(target, a, d)                                                                         \
    iris_call(port, eax, edx, target, a, d, *ebx, *ecx, esi, edi, ebp, NULL, 0)
    port_set32(port, ebp, kind->game, game);
    port_set32(port, record, 0, port->env.chain);
    port->env.chain = record;
    *edx = 0x4ec1ec;
    *ecx = kind->guard;
    *ebx = 0;
    *eax = (record & 0xffff00ffu) | ((uint32_t)port_u8(port, 0, kind->started) << 8);
    port_set32(port, ebp, -0x6cu, *edx);
    port_set32(port, ebp, -0x68u, *ecx);
    port_set32(port, ebp, -0x64u, *ebx);
    if (port_u8(port, 0, kind->started) == 0)
    {
        *edx = (*edx & 0xffffff00u) | 1;
        port_set32(port, 0, kind->size, *ebx);
        port_set8(port, 0, kind->started, 1);
        CALL(0x4b7cd0, *eax, *edx);
        CALL(0x472250, *eax, *edx);
        CALL(0x41d640, game, *edx);
    }
    CALL(0x4b7d10, *eax, *edx);
    CALL(0x41d670, game, 4);
    CALL(0x472350, *eax, *edx);
    if (CALL(0x4b5eb0, 0x54676c, *edx) != 0)
    {
        *eax = port_u32(port, *eax, 0x58);
    }
    port_set32(port, ebp, -0x4cu, *eax);
    CALL(0x486d00, 0x5b9c50, *edx);
    if (port_u32(port, 0, kind->size) == 0)
    {
        uint32_t surface = port_u32(port, 0, 0x558c80);
        uint32_t args[4];
        *ecx = 0;
        *ebx = 0;
        args[0] = 0;
        args[1] = 0;
        args[2] = port_u32(port, surface, 4);
        args[3] = port_u32(port, surface, 8);
        iris_call(port, eax, edx, 0x47ce10, port_u32(port, 0, 0x558c7c), surface, *ebx, *ecx, esi,
                  edi, ebp, args, 4);
    }
}

/* The end of an iris step: the game's 0x41d6d0, 0x486da0, 0x487020, 0x486ed0 of
 * 0x5b9c50, the size kept, 0x41d660, 0x41de80, 0x41ddf0; when 0x472360 says the
 * iris is done 0x472330, 0x41ac80, 0x418830 and the mark cleared; the guard
 * record dropped. The restored chain. */
static uint32_t iris_end(Port *port, uint32_t *eax, uint32_t *edx, uint32_t *ebx, uint32_t *ecx,
                         uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t game,
                         const IrisKind *kind)
{
    CALL(0x41d6d0, game, *edx);
    CALL(0x486da0, 0x5b9c50, *edx);
    CALL(0x487020, 0x5b9c50, *edx);
    CALL(0x486ed0, 0x5b9c50, *edx);
    port_set32(port, 0, kind->size, port_u32(port, ebp, -0x4cu));
    CALL(0x41d660, game, *edx);
    CALL(0x41de80, game, *edx);
    CALL(0x41ddf0, game, *edx);
    if (CALL(0x472360, *eax, *edx) == 1)
    {
        CALL(0x472330, *eax, *edx);
        CALL(0x41ac80, game, *edx);
        *ecx &= 0xffff00ffu;
        CALL(0x418830, game, *edx);
        port_set8(port, 0, kind->started, 0);
    }
#undef CALL
    *eax = port_u32(port, ebp - 0x70, 0);
    port->env.chain = *eax;
    return *eax;
}

/* Original 0x4223d0 (guarded 0x5141f4): one step of the closing iris of the
 * game eax (iris_begin, with the mark 0x5405bc and the size 0x5405c0). A new
 * size m against the old n copies the back buffer 0x558c88 onto the screen
 * 0x558c7c (0x47ce10) in the four bands between them: left, right, top and
 * bottom; with the game's +0xc8 1 each band's edge also gets strips of 3 and 1
 * pixel every 4. Then iris_end. eax the restored chain, edx kept. */
uint32_t vertrix_port_screen_iris_4223d0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x74
    };
    Port port;
    uint8_t stack[BELOW + 8];
    static const IrisKind kind = {0x5141f4, 0x5405bc, 0x5405c0, -0x40u};
    uint32_t ebp = entry->esp - 4;
    uint32_t game = entry->eax;
    uint32_t eax;
    uint32_t edx;
    uint32_t ebx;
    uint32_t ecx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t count;
#define CALL(target, a, d)                                                                         \
    iris_call(&port, &eax, &edx, target, a, d, ebx, ecx, esi, edi, ebp, NULL, 0)
#define BLIT(b, c, a0, a1, a2, a3) blit(&port, &eax, &edx, b, c, esi, edi, ebp, a0, a1, a2, a3)
#define EDGES() (port_u8(&port, game, 0xc8) == 1)
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -4u, entry->ebx);
    port_set32(&port, ebp, -8u, entry->ecx);
    port_set32(&port, ebp, -0xcu, entry->edx);
    port_set32(&port, ebp, -0x10u, entry->esi);
    port_set32(&port, ebp, -0x14u, entry->edi);
    iris_begin(&port, &eax, &edx, &ebx, &ecx, esi, edi, ebp, game, &kind);
    esi = port_u32(&port, ebp, -0x4cu);
    if (esi != port_u32(&port, 0, 0x5405c0))
    {
        uint32_t surface = port_u32(&port, 0, 0x558c80);
        uint32_t n = port_u32(&port, 0, 0x5405c0);
        uint32_t width = port_u32(&port, surface, 4);
        uint32_t height = port_u32(&port, surface, 8);
        uint32_t m = esi;
        port_set32(&port, ebp, -0x48u, height - 2 * n);
        port_set32(&port, ebp, -0x28u, n);
        port_set32(&port, ebp, -0x50u, width - 2 * n);
        port_set32(&port, ebp, -0x58u, height - n);
        port_set32(&port, ebp, -0x5cu, width - n);
        port_set32(&port, ebp, -0x44u, m - n);
        port_set32(&port, ebp, -0x54u, m - n);
        edi = n;
        ebx = n;
        ecx = n;
        BLIT(ebx, ecx, n, n, m - n, height - 2 * n);
        edx = (edx & 0xffff00ffu) | ((uint32_t)port_u8(&port, game, 0xc8) << 8);
        port_set32(&port, ebp, -0x2cu, edi);
        count = port_u32(&port, ebp, -0x48u) >> 2;
        if (EDGES() && count != 0)
        {
            port_set32(&port, ebp, -0x1cu, 0);
            port_set32(&port, ebp, -0x3cu, count << 2);
            edi += port_u32(&port, ebp, -0x44u);
            do
            {
                esi = port_u32(&port, ebp, -0x2cu) + port_u32(&port, ebp, -0x1cu);
                ebx = edi;
                ecx = esi;
                BLIT(ebx, ecx, edi, esi, 1, 3);
                esi++;
                ebx = edi + 1;
                ecx = esi;
                BLIT(ebx, ecx, edi + 1, esi, 1, 1);
                ecx = port_u32(&port, ebp, -0x1cu) + 4;
                ebx = port_u32(&port, ebp, -0x3cu);
                port_set32(&port, ebp, -0x1cu, ecx);
            } while (ecx < ebx && !port.env.failed);
        }
        esi = port_u32(&port, ebp, -0x5cu) - port_u32(&port, ebp, -0x44u);
        ecx = port_u32(&port, ebp, -0x2cu);
        ebx = esi;
        BLIT(ebx, ecx, esi, ecx, port_u32(&port, ebp, -0x44u), port_u32(&port, ebp, -0x48u));
        count = port_u32(&port, ebp, -0x48u) >> 2;
        if (EDGES() && count != 0)
        {
            uint32_t right = esi - 1;
            port_set32(&port, ebp, -0x24u, right);
            port_set32(&port, ebp, -0x38u, count << 2);
            edi = 0;
            do
            {
                esi = port_u32(&port, ebp, -0x2cu) + edi;
                ebx = right;
                ecx = esi;
                BLIT(ebx, ecx, right, esi, 1, 3);
                esi++;
                ebx = right - 1;
                ecx = esi;
                edi += 4;
                BLIT(ebx, ecx, ebx, esi, 1, 1);
            } while (edi < port_u32(&port, ebp, -0x38u) && !port.env.failed);
        }
        esi = port_u32(&port, ebp, -0x2cu);
        edi = port_u32(&port, ebp, -0x28u);
        ecx = esi;
        ebx = edi;
        BLIT(ebx, ecx, edi, esi, port_u32(&port, ebp, -0x50u), port_u32(&port, ebp, -0x54u));
        count = port_u32(&port, ebp, -0x50u) >> 2;
        if (EDGES() && count != 0)
        {
            uint32_t top = esi + port_u32(&port, ebp, -0x54u);
            edi = 0;
            port_set32(&port, ebp, -0x34u, count << 2);
            port_set32(&port, ebp, -0x20u, top);
            do
            {
                esi = port_u32(&port, ebp, -0x28u) + edi;
                ecx = top;
                ebx = esi;
                BLIT(ebx, ecx, esi, top, 3, 1);
                ecx = top + 1;
                esi++;
                ebx = esi;
                edi += 4;
                BLIT(ebx, ecx, esi, ecx, 1, 1);
            } while (edi < port_u32(&port, ebp, -0x34u) && !port.env.failed);
        }
        esi = port_u32(&port, ebp, -0x58u) - port_u32(&port, ebp, -0x54u);
        ebx = port_u32(&port, ebp, -0x28u);
        ecx = esi;
        BLIT(ebx, ecx, ebx, esi, port_u32(&port, ebp, -0x50u), port_u32(&port, ebp, -0x54u));
        count = port_u32(&port, ebp, -0x50u) >> 2;
        if (EDGES() && count != 0)
        {
            edi = esi - 1;
            esi = 0;
            port_set32(&port, ebp, -0x30u, count << 2);
            port_set32(&port, ebp, -0x18u, esi);
            do
            {
                esi = port_u32(&port, ebp, -0x28u) + port_u32(&port, ebp, -0x18u);
                ecx = edi;
                ebx = esi;
                BLIT(ebx, ecx, esi, edi, 3, 1);
                ecx = edi - 1;
                esi++;
                ebx = esi;
                BLIT(ebx, ecx, esi, ecx, 1, 1);
                ecx = port_u32(&port, ebp, -0x18u) + 4;
                ebx = port_u32(&port, ebp, -0x30u);
                port_set32(&port, ebp, -0x18u, ecx);
            } while (ecx < ebx && !port.env.failed);
        }
    }
#undef CALL
#undef BLIT
#undef EDGES
    iris_end(&port, &eax, &edx, &ebx, &ecx, esi, edi, ebp, game, &kind);
    return port_return(&port, eax, entry->edx);
}

/* Original 0x422800 (guarded 0x5141f8): one step of the opening iris of the
 * game eax (iris_begin, with the mark 0x5405c4 and the size 0x5405c8). A new
 * size m against the old n copies the back buffer 0x558c88 onto the screen
 * 0x558c7c (0x47ce10) in the four bands between them, centred on half the
 * height (s = height / 2 - m): left, right, top and bottom; with the game's
 * +0xc8 1 each band's edge also gets strips of 3 and 1 pixel every 4 (the left
 * and top when s is at least 2, the right and bottom while inside the screen).
 * Then iris_end. eax the restored chain, edx kept. */
uint32_t vertrix_port_screen_iris_open_422800(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x74
    };
    static const IrisKind kind = {0x5141f8, 0x5405c4, 0x5405c8, -0x48u};
    Port port;
    uint8_t stack[BELOW + 8];
    uint32_t ebp = entry->esp - 4;
    uint32_t game = entry->eax;
    uint32_t eax;
    uint32_t edx;
    uint32_t ebx;
    uint32_t ecx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t count;
#define BLIT(b, c, a0, a1, a2, a3) blit(&port, &eax, &edx, b, c, esi, edi, ebp, a0, a1, a2, a3)
#define EDGES() (port_u8(&port, game, 0xc8) == 1)
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -4u, entry->ebx);
    port_set32(&port, ebp, -8u, entry->ecx);
    port_set32(&port, ebp, -0xcu, entry->edx);
    port_set32(&port, ebp, -0x10u, entry->esi);
    port_set32(&port, ebp, -0x14u, entry->edi);
    iris_begin(&port, &eax, &edx, &ebx, &ecx, esi, edi, ebp, game, &kind);
    esi = port_u32(&port, ebp, -0x4cu);
    if (esi != port_u32(&port, 0, 0x5405c8))
    {
        uint32_t surface = port_u32(&port, 0, 0x558c80);
        uint32_t height = port_u32(&port, surface, 8);
        uint32_t width = port_u32(&port, surface, 4);
        uint32_t n = port_u32(&port, 0, 0x5405c8);
        uint32_t m = esi;
        uint32_t s = (height >> 1) - m;
        uint32_t band = ((height >> 1) - n) - s;
        edi = n;
        port_set32(&port, ebp, -0x54u, height - 2 * s);
        port_set32(&port, ebp, -0x58u, band);
        port_set32(&port, ebp, -0x5cu, band);
        port_set32(&port, ebp, -0x50u, width - 2 * s);
        port_set32(&port, ebp, -0x2cu, width - s);
        port_set32(&port, ebp, -0x28u, height - s);
        esi = s;
        ecx = s;
        ebx = s;
        BLIT(ebx, ecx, s, s, band, height - 2 * s);
        port_set32(&port, ebp, -0x24u, esi);
        edx = (edx & 0xffff00ffu) | ((uint32_t)port_u8(&port, game, 0xc8) << 8);
        port_set32(&port, ebp, -0x20u, esi);
        count = port_u32(&port, ebp, -0x54u) >> 2;
        if (EDGES() && esi >= 2 && count != 0)
        {
            edi = esi - 1;
            ebx = 0;
            port_set32(&port, ebp, -0x18u, ebx);
            port_set32(&port, ebp, -0x38u, count << 2);
            do
            {
                esi = port_u32(&port, ebp, -0x20u) + port_u32(&port, ebp, -0x18u);
                ebx = edi;
                ecx = esi;
                BLIT(ebx, ecx, edi, esi, 1, 3);
                esi++;
                ebx = edi - 1;
                ecx = esi;
                BLIT(ebx, ecx, ebx, esi, 1, 1);
                edx = port_u32(&port, ebp, -0x18u) + 4;
                ecx = port_u32(&port, ebp, -0x38u);
                port_set32(&port, ebp, -0x18u, edx);
            } while (edx < ecx && !port.env.failed);
        }
        esi = port_u32(&port, ebp, -0x54u);
        edi = port_u32(&port, ebp, -0x58u);
        ebx = port_u32(&port, ebp, -0x2cu) - edi;
        ecx = port_u32(&port, ebp, -0x20u);
        BLIT(ebx, ecx, ebx, ecx, edi, esi);
        if (EDGES())
        {
            eax = port_u32(&port, ebp, -0x2cu) + 1;
            edx = esi >> 2;
            if (eax < port_u32(&port, port_u32(&port, 0, 0x558c80), 4) && edx != 0)
            {
                port_set32(&port, ebp, -0x30u, eax);
                port_set32(&port, ebp, -0x40u, edx << 2);
                edi = 0;
                do
                {
                    esi = port_u32(&port, ebp, -0x20u) + edi;
                    ebx = port_u32(&port, ebp, -0x2cu);
                    ecx = esi;
                    BLIT(ebx, ecx, ebx, esi, 1, 3);
                    esi++;
                    ebx = port_u32(&port, ebp, -0x30u);
                    ecx = esi;
                    edi += 4;
                    BLIT(ebx, ecx, ebx, esi, 1, 1);
                } while (edi < port_u32(&port, ebp, -0x40u) && !port.env.failed);
            }
        }
        esi = port_u32(&port, ebp, -0x20u);
        edi = port_u32(&port, ebp, -0x24u);
        ecx = esi;
        ebx = edi;
        BLIT(ebx, ecx, edi, esi, port_u32(&port, ebp, -0x50u), port_u32(&port, ebp, -0x5cu));
        count = port_u32(&port, ebp, -0x50u) >> 2;
        if (EDGES() && esi >= 2 && count != 0)
        {
            port_set32(&port, ebp, -0x1cu, esi - 1);
            port_set32(&port, ebp, -0x44u, count << 2);
            edi = 0;
            do
            {
                uint32_t top = port_u32(&port, ebp, -0x1cu);
                esi = port_u32(&port, ebp, -0x24u) + edi;
                ecx = top;
                ebx = esi;
                BLIT(ebx, ecx, esi, top, 3, 1);
                ecx = top - 1;
                esi++;
                ebx = esi;
                edi += 4;
                BLIT(ebx, ecx, esi, ecx, 1, 1);
            } while (edi < port_u32(&port, ebp, -0x44u) && !port.env.failed);
        }
        esi = port_u32(&port, ebp, -0x50u);
        ecx = port_u32(&port, ebp, -0x28u) - port_u32(&port, ebp, -0x5cu);
        ebx = port_u32(&port, ebp, -0x24u);
        BLIT(ebx, ecx, ebx, ecx, esi, port_u32(&port, ebp, -0x5cu));
        if (EDGES())
        {
            eax = port_u32(&port, ebp, -0x28u) + 1;
            edx = esi >> 2;
            if (eax < port_u32(&port, port_u32(&port, 0, 0x558c80), 8) && edx != 0)
            {
                port_set32(&port, ebp, -0x34u, eax);
                port_set32(&port, ebp, -0x3cu, edx << 2);
                edi = 0;
                do
                {
                    esi = port_u32(&port, ebp, -0x24u) + edi;
                    ecx = port_u32(&port, ebp, -0x28u);
                    ebx = esi;
                    BLIT(ebx, ecx, esi, ecx, 3, 1);
                    ecx = port_u32(&port, ebp, -0x34u);
                    esi++;
                    ebx = esi;
                    edi += 4;
                    BLIT(ebx, ecx, esi, ecx, 1, 1);
                } while (edi < port_u32(&port, ebp, -0x3cu) && !port.env.failed);
            }
        }
    }
#undef BLIT
#undef EDGES
    iris_end(&port, &eax, &edx, &ebx, &ecx, esi, edi, ebp, game, &kind);
    return port_return(&port, eax, entry->edx);
}
