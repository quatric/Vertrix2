#include "port_rtlplayerkeys.h"

/* The player's keys read each frame. */

/* A call (with count stack arguments, nearest first) that leaves its eax and edx in *eax and
 * *edx; the eax. */
static uint32_t keys_call(Port *port, uint32_t *eax, uint32_t *edx, uint32_t target, uint32_t a,
                          uint32_t d, uint32_t ebx, uint32_t ecx, uint32_t esi, uint32_t edi,
                          uint32_t ebp, const uint32_t *stack, unsigned count)
{
    vertrix_lift_in_esi = esi;
    vertrix_lift_in_edi = edi;
    vertrix_lift_in_ebp = ebp;
    *eax = lift_call_arguments(&port->env, target, a, d, ebx, ecx, stack, count);
    vertrix_lift_in_esi = vertrix_lift_in_edi = vertrix_lift_in_ebp = 0;
    *edx = vertrix_lift_edx;
    return *eax;
}

/* Original 0x450ff0: the player eax's turn (its board +0x15c, the other player +0x3b0, its
 * pointer +0x3b4). Not playing (+0x4c5 0) it is handed 0x4513d0 (0x4ac8f0). With no piece
 * falling (board +0xa60 0) the drop key +0x16e is let go (0x476480, 0x476320), the pointer's
 * place read (0x43a5b0) and the next piece put there (0x431d90 with +0x17c); in mode +0x4c8 0x31
 * 0x43b7c0, in 0x2c the board's 0x431fb0; +0x170 0 and 0x43ad50. Unless the board is over
 * (+0xbd8): 0x43ad70, and each key pressed (0x476480) and let go (0x476320): left +0x168 and
 * right +0x16a move (0x431100, 0x431140; refused 0x43ad50; in mode 0x2b the other player's keys
 * +0x160/+0x162 cleared by 0x4761d0 and 0x476280), turn +0x16c (0x431180, and when 0x432000
 * gives 1 0x4311a0 and 0x43ad50), drop +0x16e (0x431390). The board's method +4 run. A piece
 * falling: once (+0x170 0) when 0x431d60 gives 1 the pointer 0x43a520, 0x43d260, +0x170 1. The
 * board over: 0x43bb00 with 0, handed 0x4513d0, the other player not playing sets 0x532a3c 1,
 * else 0x43acd0, 0x43c0e0 with 0x4f81c8 and 0x4713d0 of its first field. Otherwise (+0x170 0
 * first 0x43a520, 0x43d260, +0x170 1): +0x184 and +0x188 0, +0x44c whether 0x43d3b0 gives 1,
 * handed 0x4513f0 in mode 0x23 else 0x451690 (0x4ac8f0), and 0x43bae0 with 1. edx kept. */
uint32_t vertrix_port_player_keys_450ff0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x2c
    };
    static const uint32_t moves[2][3] = {{0x168, 0x431100, 0x160}, {0x16a, 0x431140, 0x162}};
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t player = entry->eax;
    uint32_t board;
    uint32_t eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = player;
    uint32_t key;
    uint32_t arg;
    unsigned index;
#define CALL(target, a, d)                                                                         \
    keys_call(&port, &eax, &edx, target, a, d, ebx, ecx, player, board, ebp, NULL, 0)
#define CALL1(target, a, d, value)                                                                 \
    (arg = (value),                                                                                \
     keys_call(&port, &eax, &edx, target, a, d, ebx, ecx, player, board, ebp, &arg, 1))
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -4u, entry->ebx);
    port_set32(&port, ebp, -8u, entry->ecx);
    port_set32(&port, ebp, -0xcu, entry->edx);
    port_set32(&port, ebp, -0x10u, entry->esi);
    port_set32(&port, ebp, -0x14u, entry->edi);
    board = port_u32(&port, player, 0x15c);
    port_set32(&port, ebp, -0x28u, port_u32(&port, player, 0x3b0));
    eax = port_u32(&port, player, 0x3b4);
    port_set32(&port, ebp, -0x24u, eax);
    eax = (eax & 0xffffff00u) | port_u8(&port, player, 0x4c5);
    if ((eax & 0xff) == 0)
    {
        CALL(0x4ac8f0, player, 0x4513d0);
        return port_return(&port, eax, entry->edx);
    }
    edx = port_u32(&port, board, 0xa60);
    if (edx == 0)
    {
        edx = port_u16(&port, player, 0x16e);
        if (CALL(0x476480, 0x54d640, edx) != 0)
        {
            CALL(0x476320, 0x54d640, port_u16(&port, player, 0x16e));
        }
        ecx = ebp - 0x1c;
        ebx = ebp - 0x18;
        CALL(0x43a5b0, port_u32(&port, ebp, -0x24u), ebp - 0x20);
        ebx = (uint32_t)(int32_t)(int8_t)port_u8(&port, ebp, -0x18u);
        ecx = (uint32_t)(int32_t)(int8_t)port_u8(&port, ebp, -0x1cu);
        CALL1(0x431d90, board, (uint32_t)(int32_t)(int8_t)port_u8(&port, ebp, -0x20u),
              port_u32(&port, player, 0x17c));
        if (port_u32(&port, player, 0x4c8) == 0x31)
        {
            CALL(0x43b7c0, player, edx);
        }
        if (port_u32(&port, player, 0x4c8) == 0x2c)
        {
            CALL(0x431fb0, board, edx);
        }
        port_set32(&port, player, 0x170, 0);
        CALL(0x43ad50, player, edx);
    }
    ebx = port_u32(&port, board, 0xbd8);
    if (ebx == 0)
    {
        CALL(0x43ad70, player, edx);
        for (index = 0; index < 2 && !port.env.failed; index++)
        {
            key = moves[index][0];
            if (CALL(0x476480, 0x54d640, port_u16(&port, player, key)) == 0)
            {
                continue;
            }
            if (CALL(moves[index][1], board, edx) != 1)
            {
                CALL(0x43ad50, player, edx);
            }
            else if (port_u32(&port, player, 0x4c8) == 0x2b)
            {
                uint32_t other = port_u32(&port, ebp, -0x28u);
                ecx = 0;
                CALL1(0x4761d0, 0x54d640, port_u16(&port, other, moves[index][2]), ebx);
                ebx = 0;
                CALL1(0x476280, 0x54d640, port_u16(&port, other, moves[index][2]), 0);
            }
            CALL(0x476320, 0x54d640, port_u16(&port, player, key));
        }
        if (CALL(0x476480, 0x54d640, port_u16(&port, player, 0x16c)) != 0)
        {
            CALL(0x431180, board, edx);
            if (CALL(0x432000, board, edx) == 1)
            {
                CALL(0x4311a0, board, edx);
                CALL(0x43ad50, player, edx);
            }
            CALL(0x476320, 0x54d640, port_u16(&port, player, 0x16c));
        }
        if (CALL(0x476480, 0x54d640, port_u16(&port, player, 0x16e)) != 0)
        {
            CALL(0x431390, board, edx);
            CALL(0x476320, 0x54d640, port_u16(&port, player, 0x16e));
        }
    }
    edx = port_u32(&port, board, 0x158);
    CALL(port_u32(&port, edx, 4), board, edx);
    if (port_u32(&port, board, 0xa60) != 0)
    {
        if (port_u32(&port, player, 0x170) == 0 && CALL(0x431d60, board, edx) == 1)
        {
            CALL(0x43a520, port_u32(&port, ebp, -0x24u), edx);
            CALL(0x43d260, player, edx);
            port_set32(&port, player, 0x170, 1);
        }
        return port_return(&port, eax, entry->edx);
    }
    if (port_u32(&port, board, 0xbd8) != 0)
    {
        CALL(0x43bb00, player, 0);
        CALL(0x4ac8f0, player, 0x4513d0);
        eax = port_u32(&port, ebp, -0x28u);
        eax = (eax & 0xffffff00u) | port_u8(&port, eax, 0x4c5);
        if ((eax & 0xff) == 0)
        {
            port_set32(&port, 0, 0x532a3c, 1);
            return port_return(&port, eax, entry->edx);
        }
        CALL(0x43acd0, player, edx);
        CALL(0x43c0e0, player, port_u32(&port, 0, 0x4f81c8));
        CALL(0x4713d0, port_u32(&port, player, 0), edx);
        return port_return(&port, eax, entry->edx);
    }
    if (port_u32(&port, player, 0x170) == 0)
    {
        CALL(0x43a520, port_u32(&port, ebp, -0x24u), edx);
        CALL(0x43d260, player, edx);
        port_set32(&port, player, 0x170, 1);
    }
    port_set32(&port, player, 0x184, 0);
    port_set32(&port, player, 0x188, 0);
    port_set32(&port, player, 0x44c, CALL(0x43d3b0, player, edx) == 1);
    CALL(0x4ac8f0, player, port_u32(&port, player, 0x4c8) == 0x23 ? 0x4513f0 : 0x451690);
    CALL(0x43bae0, player, 1);
#undef CALL
#undef CALL1
    return port_return(&port, eax, entry->edx);
}
