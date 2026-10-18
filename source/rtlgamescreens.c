#include "rtlgamescreens.h"

/* The game screen entered. */

/* A call that leaves its eax and edx in *eax and *edx; the eax. */
static uint32_t screen_call(Port *port, uint32_t *eax, uint32_t *edx, uint32_t target, uint32_t a,
                            uint32_t d, uint32_t ebx, uint32_t ecx, uint32_t esi, uint32_t edi,
                            uint32_t ebp)
{
    *eax = port_call_with(port, target, a, d, ebx, ecx, esi, edi, ebp);
    *edx = vertrix_lift_edx;
    return *eax;
}

/* Original 0x420f10 (guarded 0x514184): the game eax put on its screen: the text 0x5332c0 of the
 * language 0x532a70 made (0x4ca090) into the picture name with 0x4fc290 (0x45f540); missing
 * (0x45f590 0) it is the player 0x513c1a's 0x5334a0 with 0x4fc398; the game shown it (0x41a960).
 * The two boards (0x7b8 bytes, 0x4ca000, made by 0x4120a0 with 0x7a and 2, then with 1 and 4)
 * each kept at 0x532928 with the names 0x533310 and 0x534750 (0x4ca310, 0x45f540 with 0x4fcff8)
 * loaded (0x4122f0); between them the first set up (0x46b800, 0x471a70, 0x4719f0 of 0x544070's
 * +0x268, 0x4719e0) and its method +0x7b4 called with 2. The overlays made (0x45f770); the keys
 * 0x54d640 reset (0x476090, 0x4760c0, 0x476590, 0x4765b0 with 1, 0x476140 with the last edx, 0x3d
 * and 2..9); 0x4b7cd0; 0x4871d0 of 0x5b9c50 with 0; 0x45e630 with 8 for both players; the pair of
 * pictures 0x534620 and 0x534670 (with 0x4fc7b8) loaded (0x423ea0): one given is spread to both
 * players (0x45f250 with 8) and freed (0x478d80). The music 0x5347a0 (0x4711a0), the level
 * 0x533cd0 started (0x4191b0 with 1), and the game's parts (0x41aa20, 0x41aaa0 with 0x4212a0,
 * 0x418840); the text freed (0x4ca210). eax the restored chain, edx kept. */
uint32_t vertrix_port_game_screen_420f10(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x23c
    };
    Port port;
    uint8_t stack[BELOW + 8];
    uint32_t ebp = entry->esp - 4;
    uint32_t record = ebp - 0x30;
    uint32_t game = entry->eax;
    uint32_t name = ebp - 0x134;
    uint32_t eax;
    uint32_t edx;
    uint32_t ebx = 0x514184;
    uint32_t ecx;
    uint32_t esi = 0;
    uint32_t edi = 1;
    uint32_t board;
    uint32_t mark;
#define CALL(target, a, d) screen_call(&port, &eax, &edx, target, a, d, ebx, ecx, esi, edi, ebp)
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -4u, entry->ebx);
    port_set32(&port, ebp, -8u, entry->ecx);
    port_set32(&port, ebp, -0xcu, entry->edx);
    port_set32(&port, ebp, -0x10u, entry->esi);
    port_set32(&port, ebp, -0x14u, entry->edi);
    ecx = game;
    port_set32(&port, record, 0, port.env.chain);
    port.env.chain = record;
    port_set32(&port, ebp, -0x2cu, 0x4ec1ec);
    port_set32(&port, ebp, -0x28u, 0x514184);
    port_set32(&port, ebp, -0x24u, 0);
    CALL(0x4ca090, ebp - 0x1c, port_u32(&port, 0, 0x532a70) * 4 + 0x5332c0);
    ebx = port_u32(&port, ebp, -0x1cu);
    port_set32(&port, ebp, -0x24u, 1);
    CALL(0x45f540, name, 0x4fc290);
    if (CALL(0x45f590, name, edx) == 0)
    {
        ebx = port_u32(&port, port_u8(&port, 0, 0x513c1a) * 4, 0x5334a0);
        CALL(0x45f540, name, 0x4fc398);
    }
    CALL(0x41a960, game, name);
    CALL(0x4ca310, ebp - 0x1c, port_u32(&port, 0, 0x532a70) * 4 + 0x533310);
    ebx = port_u32(&port, ebp, -0x1cu);
    CALL(0x45f540, name, 0x4fcff8);
    board = CALL(0x4ca000, 0x7b8, edx);
    if (board != 0)
    {
        ebx = 1;
        port_set32(&port, ebp, -0x24u, 2);
        port_set32(&port, ebp, -0x18u, board);
        board = CALL(0x4120a0, board, 0x7a);
        port_set32(&port, ebp, -0x24u, ebx);
    }
    port_set32(&port, 0, 0x532928, board);
    CALL(0x4122f0, board, name);
    CALL(0x46b800, port_u32(&port, 0, 0x532928), edx);
    CALL(0x471a70, eax, edx);
    CALL(0x4719f0, port_u32(&port, port_u32(&port, 0, 0x544070), 0x268), edx);
    CALL(0x4719e0, eax, edx);
    esi = port_u32(&port, 0, 0x532928);
    if (esi != 0)
    {
        ebx = port_u32(&port, esi, 0x7b4);
        CALL(port_u32(&port, ebx, 0), esi, 2);
    }
    CALL(0x4ca310, ebp - 0x1c, port_u32(&port, 0, 0x532a70) * 4 + 0x534750);
    ebx = port_u32(&port, ebp, -0x1cu);
    CALL(0x45f540, name, 0x4fcff8);
    board = CALL(0x4ca000, 0x7b8, edx);
    if (board != 0)
    {
        edi = 4;
        port_set32(&port, ebp, -0x18u, board);
        port_set32(&port, ebp, -0x24u, edi);
        board = CALL(0x4120a0, board, 1);
        port_set32(&port, ebp, -0x24u, 1);
    }
    port_set32(&port, 0, 0x532928, board);
    CALL(0x4122f0, board, name);
    CALL(0x45f770, eax, edx);
    CALL(0x476090, 0x54d640, edx);
    CALL(0x4760c0, 0x54d640, edx);
    CALL(0x476590, 0x54d640, edx);
    CALL(0x4765b0, 0x54d640, 1);
    CALL(0x476140, 0x54d640, edx);
    CALL(0x476140, 0x54d640, 0x3d);
    for (mark = 2; mark <= 9 && !port.env.failed; mark++)
    {
        CALL(0x476140, 0x54d640, mark);
    }
    CALL(0x4b7cd0, eax, edx);
    CALL(0x4871d0, 0x5b9c50, 0);
    CALL(0x45e630, 0, 8);
    CALL(0x45e630, 1, 8);
    ebx = port_u32(&port, port_u32(&port, 0, 0x532a70) * 4, 0x534620);
    CALL(0x45f540, name, 0x4fc7b8);
    ebx = port_u32(&port, port_u32(&port, 0, 0x532a70) * 4, 0x534670);
    CALL(0x45f540, ebp - 0x238, 0x4fc7b8);
    esi = CALL(0x423ea0, name, ebp - 0x238);
    if (esi != 0)
    {
        ebx = 8;
        CALL(0x45f250, esi, 0);
        ebx = 8;
        CALL(0x45f250, esi, 1);
        CALL(0x478d80, esi, edx);
    }
    CALL(0x4711a0, port_u32(&port, port_u32(&port, 0, 0x532a70) * 4, 0x5347a0), edx);
    ebx = 1;
    CALL(0x4191b0, game, port_u32(&port, port_u32(&port, 0, 0x532a70) * 4, 0x533cd0));
    CALL(0x41aa20, game, edx);
    CALL(0x41aaa0, game, 0x4212a0);
    CALL(0x418840, game, edx);
    ecx = 0;
    port_set32(&port, ebp, -0x24u, 0);
    CALL(0x4ca210, ebp - 0x1c, 0);
#undef CALL
    eax = port_u32(&port, record, 0);
    port_set32(&port, ebp, -0x24u, 0);
    port.env.chain = eax;
    return port_return(&port, eax, entry->edx);
}
