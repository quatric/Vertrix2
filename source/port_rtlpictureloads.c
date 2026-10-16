#include "port_rtlpictureloads.h"

/* The game's pictures loaded. */

/* A call that leaves its eax and edx in *eax and *edx; the eax. */
static uint32_t load_call(Port *port, uint32_t *eax, uint32_t *edx, uint32_t target, uint32_t a,
                          uint32_t d, uint32_t ebx, uint32_t ecx, uint32_t esi, uint32_t edi,
                          uint32_t ebp)
{
    *eax = port_call_with(port, target, a, d, ebx, ecx, esi, edi, ebp);
    *edx = vertrix_lift_edx;
    return *eax;
}

/* Original 0x418d50 (guarded 0x513f84): the game eax's pictures loaded, a
 * progress step (0x418270 with 1) after each: 0x43eab0 first. For each of the
 * 20 tiles the name 0x533450 (not 0x50d7c7, made with 0x4fc8c0 by 0x45f540 and
 * found by 0x45f590) is loaded (0x423d70) for 0x45ed10, else the name 0x5332c0
 * (not 0x50d7c8, with 0x4fc290) for 0x45ecd0; each freed (0x478d80). The pairs
 * of pictures 0x5334a0 and 0x533578 (with 0x4fc5a8, loaded by 0x423ea0) of the
 * players 0x513c1f (0x45ec50), 0x513c20 (0x45f1f0), 0x513c23 (0x45ed60, then
 * with the pair of 0x513c3a 0x45ef40) and 0x513c22 (0x45ee30). 0x414a90,
 * 0x414b10, 0x45e690; the 19 level backgrounds (0x534f5c and 0x53612c with
 * 0x4fc9c8, 0xf0 apart, the first moved on from the edx each step leaves,
 * loaded by 0x423dc0 with 0x5347f0) handed with 0x5372fc
 * and 0x5384cc to 0x45e7b0; 0x45e6b0, 0x41e5e0 (a step of 5), 0x45ed40, and the
 * game started (0x41d640). eax 1, edx kept. */
uint32_t vertrix_port_pictures_load_418d50(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x24c
    };
    Port port;
    uint8_t stack[BELOW + 8];
    uint32_t ebp = entry->esp - 4;
    uint32_t record = ebp - 0x40;
    uint32_t name = ebp - 0x144;
    uint32_t other = ebp - 0x248;
    uint32_t eax;
    uint32_t edx = 0x4ec1ec;
    uint32_t ebx = 0;
    uint32_t ecx = 0x513f84;
    uint32_t esi = 0x533450;
    uint32_t edi = 0x5332c0;
    uint32_t picture;
#define CALL(target, a, d) load_call(&port, &eax, &edx, target, a, d, ebx, ecx, esi, edi, ebp)
#define STEP() CALL(0x418270, 1, edx)
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -4u, entry->ebx);
    port_set32(&port, ebp, -8u, entry->ecx);
    port_set32(&port, ebp, -0xcu, entry->edx);
    port_set32(&port, ebp, -0x10u, entry->esi);
    port_set32(&port, ebp, -0x14u, entry->edi);
    port_set32(&port, ebp, -0x2cu, entry->eax);
    port_set32(&port, record, 0, port.env.chain);
    port.env.chain = record;
    port_set32(&port, ebp, -0x3cu, edx);
    port_set32(&port, ebp, -0x38u, ecx);
    port_set32(&port, ebp, -0x34u, ebx);
    CALL(0x43eab0, record, edx);
    port_set32(&port, ebp, -0x18u, esi);
    STEP();
    for (ecx = 0; ecx < 0x14 && !port.env.failed; ecx++)
    {
        int loaded = 0;
        esi = 0;
        if (CALL(0x4ccfe0, port_u32(&port, port_u32(&port, ebp, -0x18u), 0), 0x50d7c7) != 0)
        {
            ebx = port_u32(&port, port_u32(&port, ebp, -0x18u), 0);
            CALL(0x45f540, name, 0x4fc8c0);
            if (CALL(0x45f590, name, edx) == 1)
            {
                esi = CALL(0x423d70, name, edx);
                CALL(0x45ed10, ecx, esi);
                CALL(0x478d80, esi, edx);
                loaded = 1;
            }
        }
        if (!loaded && esi == 0 && CALL(0x4ccfe0, port_u32(&port, edi, 0), 0x50d7c8) != 0)
        {
            ebx = port_u32(&port, edi, 0);
            CALL(0x45f540, name, 0x4fc290);
            if (CALL(0x45f590, name, edx) == 1)
            {
                esi = CALL(0x423d70, name, edx);
                CALL(0x45ecd0, ecx, esi);
                CALL(0x478d80, esi, edx);
            }
        }
        STEP();
        edi += 4;
        port_set32(&port, ebp, -0x18u, port_u32(&port, ebp, -0x18u) + 4);
    }
    ecx = port_u8(&port, 0, 0x513c1f) << 2;
    ebx = port_u32(&port, ecx, 0x5334a0);
    CALL(0x45f540, name, 0x4fc5a8);
    ecx += 0x533578;
    ebx = port_u32(&port, ecx, 0);
    CALL(0x45f540, other, 0x4fc5a8);
    picture = CALL(0x423ea0, name, other);
    edx = picture;
    if (picture != 0)
    {
        CALL(0x45ec50, picture, picture);
        CALL(0x478d80, edx, edx);
    }
    ebx = 0x5334a0;
    ecx = port_u8(&port, 0, 0x513c20);
    CALL(0x418270, 1, 0x4fc5a8);
    ecx <<= 2;
    ebx = port_u32(&port, ecx, 0x5334a0);
    CALL(0x45f540, name, edx);
    ecx += 0x533578;
    ebx = port_u32(&port, ecx, 0);
    CALL(0x45f540, other, 0x4fc5a8);
    picture = CALL(0x423ea0, name, other);
    edx = picture;
    if (picture != 0)
    {
        CALL(0x45f1f0, picture, picture);
        CALL(0x478d80, edx, edx);
    }
    ebx = 0x5334a0;
    ecx = port_u8(&port, 0, 0x513c23);
    CALL(0x418270, 1, 0x4fc5a8);
    ecx <<= 2;
    ebx = port_u32(&port, ecx, 0x5334a0);
    CALL(0x45f540, name, edx);
    ecx += 0x533578;
    ebx = port_u32(&port, ecx, 0);
    CALL(0x45f540, other, 0x4fc5a8);
    picture = CALL(0x423ea0, name, other);
    ecx = picture;
    edi = picture;
    if (picture != 0)
    {
        uint32_t second;
        CALL(0x45ed60, picture, edx);
        esi = port_u8(&port, 0, 0x513c3a);
        ebx = port_u32(&port, esi * 4, 0x5334a0);
        CALL(0x45f540, name, 0x4fc5a8);
        ebx = port_u32(&port, esi * 4, 0x533578);
        CALL(0x45f540, other, 0x4fc5a8);
        second = CALL(0x423ea0, name, other);
        ebx = second;
        if (second != 0)
        {
            CALL(0x45ef40, ecx, second);
            CALL(0x478d80, ebx, edx);
        }
        CALL(0x478d80, edi, edx);
    }
    ebx = 0x5334a0;
    ecx = port_u8(&port, 0, 0x513c22);
    CALL(0x418270, 1, 0x4fc5a8);
    ecx <<= 2;
    ebx = port_u32(&port, ecx, 0x5334a0);
    CALL(0x45f540, name, edx);
    ecx += 0x533578;
    ebx = port_u32(&port, ecx, 0);
    CALL(0x45f540, other, 0x4fc5a8);
    picture = CALL(0x423ea0, name, other);
    edx = picture;
    if (picture != 0)
    {
        CALL(0x45ee30, picture, picture);
        CALL(0x478d80, edx, edx);
    }
    ecx = 0x53612c;
    ebx = 0x534f5c;
    STEP();
    CALL(0x414a90, eax, edx);
    CALL(0x414b10, eax, edx);
    CALL(0x45e690, eax, edx);
    edi = 0;
    STEP();
    port_set32(&port, ebp, -0x20u, edi);
    port_set32(&port, ebp, -0x1cu, ecx);
    port_set32(&port, ebp, -0x24u, ebx);
    do
    {
        port_set32(&port, ebp, -0x28u, edi * 0xf0);
        ebx = port_u32(&port, port_u32(&port, ebp, -0x24u), 0);
        CALL(0x45f540, name, 0x4fc9c8);
        ebx = port_u32(&port, port_u32(&port, ebp, -0x1cu), 0);
        CALL(0x45f540, other, 0x4fc9c8);
        ebx = port_u32(&port, port_u32(&port, ebp, -0x20u), 0x5347f0);
        esi = CALL(0x423dc0, name, other);
        if (esi != 0)
        {
            ecx = port_u32(&port, port_u32(&port, ebp, -0x28u), 0x5384cc);
            ebx = port_u32(&port, port_u32(&port, ebp, -0x28u), 0x5372fc);
            CALL(0x45e7b0, edi, esi);
            CALL(0x478d80, esi, edx);
        }
        esi = port_u32(&port, ebp, -0x20u);
        CALL(0x418270, 1, port_u32(&port, ebp, -0x24u));
        edi++;
        eax = port_u32(&port, ebp, -0x1cu) + 0xf0;
        esi += 4;
        edx += 0xf0;
        port_set32(&port, ebp, -0x20u, esi);
        port_set32(&port, ebp, -0x24u, edx);
        port_set32(&port, ebp, -0x1cu, eax);
    } while (edi < 0x13 && !port.env.failed);
    CALL(0x45e6b0, eax, edx);
    STEP();
    CALL(0x41e5e0, eax, edx);
    CALL(0x418270, 5, edx);
    CALL(0x45ed40, eax, edx);
    STEP();
    CALL(0x41d640, port_u32(&port, ebp, -0x2cu), edx);
#undef CALL
#undef STEP
    port.env.chain = port_u32(&port, record, 0);
    return port_return(&port, 1, entry->edx);
}
