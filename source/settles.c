#include "settles.h"

/* The match's settling of a player's falling column. */

/* The method +4 of the object's methods +0x158. */
static uint32_t settle_method(Port *port, uint32_t object, uint32_t ebx, uint32_t ecx, uint32_t esi,
                              uint32_t edi, uint32_t ebp)
{
    uint32_t methods = port_u32(port, object, 0x158);
    return port_call_with(port, port_u32(port, methods, 4), object, methods, ebx, ecx, esi, edi,
                          ebp);
}

/* Original 0x453d50: the player eax's own falling column (+0x15c) when due (0x4ac500, 0x4ac520)
 * falls by its stride (0x4ac540, 0x4ac5b0) times its speed +0x18 into +0x58; short of a cell
 * (0x18) it moves (0x42f210, 0x42f280 of the player's +0x424 and +0x428); else it lands
 * (0x42f3d0, 0x42f310) and, when it fills (0x4320c0 gives 1), with +0x170 1 and a board not lost
 * (0x431d60) its three kinds go to +0x3b4 (0x43a560) and +0x170 is cleared, and a board still
 * open (0x432010 gives 0) takes its next column (0x431340, 0x431d80, 0x42eb60); +0x428 counts
 * it, the fall is kept below a cell and, unless the board is done (0x4314a0; else 0x43c0e0 of
 * 0x4f8188) the player takes the state 0x453ef0. The column is drawn (its methods +0x158, the
 * second). The registers but eax kept. */
uint32_t vertrix_port_player_own_column_settle_453d50(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x20
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t player = entry->eax;
    uint32_t column;
    uint32_t edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t fall;
    uint32_t stride;
    uint32_t kinds;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, -4u, entry->ebx);
    port_set32(&port, ebp, -8u, entry->ecx);
    port_set32(&port, ebp, -0xcu, entry->edx);
    port_set32(&port, ebp, -0x10u, entry->esi);
    port_set32(&port, ebp, -0x14u, entry->edi);
    column = port_u32(&port, player, 0x15c);
    port_set32(&port, ebp, -0x1cu, port_u32(&port, player, 0x3b4));
    port_call_with(&port, 0x4ac500, column, entry->edx, ebx, ecx, column, player, ebp);
    if (port_call_with(&port, 0x4ac520, column, vertrix_lift_edx, ebx, ecx, column, player, ebp) ==
        1)
    {
        stride = port_call_with(&port, 0x4ac540, column, vertrix_lift_edx, ebx, ecx, column, player,
                                ebp);
        port_call_with(&port, 0x4ac5b0, column, stride, ebx, ecx, column, player, ebp);
        edx = vertrix_lift_edx * (uint32_t)((int32_t)port_u32(&port, column, 0x18) >> 16);
        port_set32(&port, column, 0x58, port_u32(&port, column, 0x58) + edx);
    }
    else
    {
        edx = vertrix_lift_edx;
    }
    if ((int32_t)port_u32(&port, column, 0x58) < 0x18)
    {
        port_call_with(&port, 0x42f210, column, edx, ebx, ecx, column, player, ebp);
        ebx = port_u32(&port, player, 0x428);
        port_call_with(&port, 0x42f280, column, port_u32(&port, player, 0x424), ebx, ecx, column,
                       player, ebp);
    }
    else
    {
        ebx = port_u32(&port, player, 0x428);
        port_call_with(&port, 0x42f3d0, column, port_u32(&port, player, 0x424), ebx, ecx, column,
                       player, ebp);
        port_call_with(&port, 0x42f310, column, vertrix_lift_edx, ebx, ecx, column, player, ebp);
        if (port_call_with(&port, 0x4320c0, column, vertrix_lift_edx, ebx, ecx, column, player,
                           ebp) == 1)
        {
            if (port_u32(&port, player, 0x170) == 1 &&
                port_call_with(&port, 0x431d60, column, vertrix_lift_edx, ebx, ecx, column, player,
                               ebp) == 0)
            {
                kinds = port_u32(&port, column, 0xa60);
                port_set8(&port, ebp, -0x18u, port_u8(&port, port_u32(&port, kinds, 0x15c), 0x15c));
                ebx =
                    (uint32_t)(int32_t)(int8_t)port_u8(&port, port_u32(&port, kinds, 0x160), 0x15c);
                ecx =
                    (uint32_t)(int32_t)(int8_t)port_u8(&port, port_u32(&port, kinds, 0x164), 0x15c);
                port_call_with(&port, 0x43a560, port_u32(&port, ebp, -0x1cu),
                               (uint32_t)(int32_t)(int8_t)port_u8(&port, ebp, -0x18u), ebx, ecx,
                               column, player, ebp);
                port_set32(&port, player, 0x170, 0);
            }
            if (port_call_with(&port, 0x432010, column, vertrix_lift_edx, ebx, ecx, column, player,
                               ebp) == 0)
            {
                port_call_with(&port, 0x431d80, column,
                               port_call_with(&port, 0x431340, column, vertrix_lift_edx, ebx, ecx,
                                              column, player, ebp),
                               ebx, ecx, column, player, ebp);
                port_call_with(&port, 0x42eb60, column, vertrix_lift_edx, ebx, ecx, column, player,
                               ebp);
            }
        }
        port_set32(&port, player, 0x428, port_u32(&port, player, 0x428) + 1);
        fall = port_u32(&port, column, 0x58);
        if ((int32_t)fall >= 0x18)
        {
            port_set32(&port, column, 0x58, fall % 0x18);
        }
        ebx = port_u32(&port, player, 0x428);
        if (port_call_with(&port, 0x4314a0, column, port_u32(&port, player, 0x424), ebx, ecx,
                           column, player, ebp) != 0)
        {
            port_call_with(&port, 0x43c0e0, player, port_u32(&port, 0, 0x4f8188), ebx, ecx, column,
                           player, ebp);
        }
        else
        {
            port_call_with(&port, 0x4ac8f0, player, 0x453ef0, ebx, ecx, column, player, ebp);
        }
    }
    return port_return(&port, settle_method(&port, column, ebx, ecx, column, player, ebp),
                       entry->edx);
}
