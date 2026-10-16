#include "port_rtlgamestarts.h"

/* The game started. */

/* A call that leaves its eax and edx in *eax and *edx; the eax. */
static uint32_t start_call(Port *port, uint32_t *eax, uint32_t *edx, uint32_t target, uint32_t a,
                           uint32_t d, uint32_t ebx, uint32_t ecx, uint32_t esi, uint32_t edi,
                           uint32_t ebp)
{
    *eax = port_call_with(port, target, a, d, ebx, ecx, esi, edi, ebp);
    *edx = vertrix_lift_edx;
    return *eax;
}

/* Original 0x41b310 (guarded 0x514000): the game eax started: a pending network game (0x532a84 1)
 * clears 0x532a7c/0x532a80/0x532a84 and closes the link 0x5bb254 (0x48b770); the three player
 * names picked by 0x53bd08, 0x513c18 and 0x513c19 from 0x5334a0 made with 0x4fc398 (0x45f540);
 * 0x532bb0 0; the players set up (0x41a9a0) and the level 0x533ccc started (0x4191b0 with 1);
 * the overlays made (0x45f770); the music chosen: the game's +0xd8 (0x461930), else unless
 * already chosen 0x532a34 2 and the link asked (0x47e890, 0x47e9a0: both 1 keep it at 1, else
 * the link closed), then 1 plays 0x4633b0 and any other 0x461360; +0xd8 0; both boards 0x4f84b8
 * and 0x4f84cc refreshed (0x41e310), the screen redone (0x472db0, 0x472ad0 with the third name,
 * 0x472f80, 0x4731a0 of the boards, and 0x472d00 with 0x532b40 1); the keys 0x54d640 reset
 * (0x476090, 0x4760c0, 0x476590, 0x4765b0 with 1, 0x476140 and 0x476140 with 0x3b..0x3e,
 * 0x476120 with 0x5f and 0x60); 0x4b7cd0, 0x477d70 of 0x5588f8, 0x417f40; 0x532a4c from
 * 0x532a98; and the game's parts started (0x41aa20, 0x471a80, 0x471b00, 0x471a70, 0x41ab60,
 * 0x41ab30, 0x41ab00, 0x41aaa0). eax the restored chain, edx kept. */
uint32_t vertrix_port_game_start_41b310(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x338
    };
    static const uint32_t names[3][2] = {{0x53bd08, 0x334}, {0x513c18, 0x230}, {0x513c19, 0x12c}};
    static const uint32_t marks[] = {0x3b, 0x3c, 0x3d, 0x3e};
    Port port;
    uint8_t stack[BELOW + 8];
    uint32_t ebp = entry->esp - 4;
    uint32_t record = ebp - 0x28;
    uint32_t game = entry->eax;
    uint32_t eax = entry->eax;
    uint32_t edx = 0x4ec1ec;
    uint32_t ebx = 0x514000;
    uint32_t esi = 0;
    uint32_t edi;
    unsigned index;
#define CALL(target, a, d) start_call(&port, &eax, &edx, target, a, d, ebx, game, esi, edi, ebp)
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -4u, entry->ebx);
    port_set32(&port, ebp, -8u, entry->ecx);
    port_set32(&port, ebp, -0xcu, entry->edx);
    port_set32(&port, ebp, -0x10u, entry->esi);
    port_set32(&port, ebp, -0x14u, entry->edi);
    port_set32(&port, record, 0, port.env.chain);
    port.env.chain = record;
    edi = port_u32(&port, 0, 0x532a84);
    port_set32(&port, ebp, -0x24u, 0x4ec1ec);
    port_set32(&port, ebp, -0x20u, 0x514000);
    port_set32(&port, ebp, -0x1cu, 0);
    if (edi == 1)
    {
        port_set32(&port, 0, 0x532a7c, 0);
        port_set32(&port, 0, 0x532a80, 0);
        port_set32(&port, 0, 0x532a84, 0);
        CALL(0x48b770, 0x5bb254, edx);
    }
    for (index = 0; index < 3; index++)
    {
        ebx = port_u32(&port, port_u8(&port, 0, names[index][0]) * 4, 0x5334a0);
        CALL(0x45f540, ebp - names[index][1], 0x4fc398);
    }
    ebx = ebp - 0x230;
    port_set32(&port, 0, 0x532bb0, 0);
    CALL(0x41a9a0, game, ebp - 0x334);
    ebx = 1;
    CALL(0x4191b0, game, port_u32(&port, 0, 0x533ccc));
    CALL(0x45f770, eax, edx);
    if (port_u32(&port, game, 0xd8) != 0)
    {
        CALL(0x461930, eax, edx);
    }
    else
    {
        if (port_u8(&port, 0, 0x532a34) == 0)
        {
            edx = (edx & 0xffffff00u) | 2;
            port_set8(&port, 0, 0x532a34, 2);
            if (CALL(0x47e890, 0x5bb254, edx) == 1)
            {
                if (CALL(0x47e9a0, 0x5bb254, edx) == 1)
                {
                    port_set8(&port, 0, 0x532a34, 1);
                }
                else
                {
                    CALL(0x48b770, 0x5bb254, edx);
                }
            }
        }
        if (port_u8(&port, 0, 0x532a34) == 1)
        {
            CALL(0x4633b0, 1, edx);
        }
        else
        {
            CALL(0x461360, eax, edx);
        }
    }
    eax = port_u32(&port, 0, 0x4f84b8);
    port_set32(&port, game, 0xd8, 0);
    CALL(0x41e310, eax, edx);
    CALL(0x41e310, port_u32(&port, 0, 0x4f84cc), edx);
    CALL(0x472db0, eax, edx);
    CALL(0x472ad0, ebp - 0x12c, edx);
    CALL(0x472f80, eax, edx);
    CALL(0x4731a0, port_u32(&port, 0, 0x4f84b8), port_u32(&port, 0, 0x4f84cc));
    if (port_u32(&port, 0, 0x532b40) == 1)
    {
        CALL(0x472d00, 1, edx);
    }
    CALL(0x476090, 0x54d640, edx);
    CALL(0x4760c0, 0x54d640, edx);
    CALL(0x476590, 0x54d640, edx);
    CALL(0x4765b0, 0x54d640, 1);
    CALL(0x476140, 0x54d640, edx);
    for (index = 0; index < 4; index++)
    {
        CALL(0x476140, 0x54d640, marks[index]);
    }
    CALL(0x476120, 0x54d640, 0x5f);
    CALL(0x476120, 0x54d640, 0x60);
    CALL(0x4b7cd0, eax, edx);
    CALL(0x477d70, 0x5588f8, edx);
    CALL(0x417f40, eax, edx);
    port_set32(&port, 0, 0x532a4c, port_u32(&port, 0, 0x532a98));
    CALL(0x41aa20, game, edx);
    CALL(0x471a80, eax, edx);
    CALL(0x471b00, eax, edx);
    CALL(0x471a70, eax, edx);
    CALL(0x41ab60, game, edx);
    CALL(0x41ab30, game, edx);
    CALL(0x41ab00, game, edx);
    CALL(0x41aaa0, game, edx);
#undef CALL
    port.env.chain = port_u32(&port, record, 0);
    return port_return(&port, port_u32(&port, record, 0), entry->edx);
}
