#include "port_previews.h"

/* The player panel's three previews and its bar. */

static uint32_t call_frame(Port *port, uint32_t target, uint32_t eax, uint32_t edx, uint32_t ebx,
                           uint32_t ecx, uint32_t esi, uint32_t edi, uint32_t ebp,
                           const uint32_t *stack, unsigned count)
{
    uint32_t result;
    vertrix_lift_in_esi = esi;
    vertrix_lift_in_edi = edi;
    vertrix_lift_in_ebp = ebp;
    result = lift_call_arguments(&port->env, target, eax, edx, ebx, ecx, stack, count);
    vertrix_lift_in_esi = vertrix_lift_in_edi = vertrix_lift_in_ebp = 0;
    return result;
}

static uint32_t sign16(uint32_t value)
{
    return (uint32_t)(int32_t)(int16_t)value;
}

/* Original 0x42b370: under a guard record (0x5147cc) the panel eax's three previews, at the
 * places 0x4f8b40 and 0x4f8b4c (with dl set, else 0x4f8b28 and 0x4f8b34): each a piece (0x15c
 * bytes, 0x4ca000, 0x4abd70) at +0x15c made (0x4adf20 with 0x5449fc and the frame 0x4fbf74 plus
 * its number), at speed 1 (0x4ac7b0), shown, unmoving, owned by [eax], numbered +0x58, stopped
 * (0x4ac8f0, 0x4adfa0), +0x7c cleared and given the state 0x44ff90 (0x4ac8a0, 0x4ac8f0); and a
 * frame (0x5466a4) at +0x168 likewise, behind (+0x4e 0x32, +0x95 4), with the state 0x450130.
 * The guard record's chain. */
uint32_t vertrix_port_ui_player_previews_construct_42b370(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x3c
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t panel = entry->eax;
    uint32_t flag = entry->edx & 0xff;
    uint32_t place;
    uint32_t index;
    uint32_t x;
    uint32_t y;
    uint32_t ebx = 0;
    uint32_t ecx = 0x5147cc;
    uint32_t piece;
    uint32_t args[5];
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, -0x1cu, panel);
    port_set8(&port, ebp, -0x14u, flag);
    port_set32(&port, ebp, -0x38u, port.env.chain);
    port_set32(&port, ebp, -0x34u, 0x4ec1ec);
    port_set32(&port, ebp, -0x30u, 0x5147cc);
    port_set32(&port, ebp, -0x2cu, 0);
    for (index = 0; index < 3; ++index)
    {
        place = panel + index * 4;
        x = port_u32(&port, 0, (flag != 0 ? 0x4f8b40 : 0x4f8b28) + index * 4);
        y = port_u32(&port, 0, (flag != 0 ? 0x4f8b4c : 0x4f8b34) + index * 4);
        port_set32(&port, ebp, -0x24u, x);
        port_set32(&port, ebp, -0x18u, y);
        piece = port_call_with(&port, 0x4ca000, 0x15c, x, ebx, ecx, place, index, ebp);
        if (piece != 0)
        {
            port_set32(&port, ebp, -0x20u, piece);
            port_set32(&port, ebp, -0x2cu, 1);
            ecx = 0;
            piece = port_call_with(&port, 0x4abd70, piece, 1, ebx, 0, place, index, ebp);
            port_set32(&port, ebp, -0x2cu, 0);
        }
        ebx = sign16(y);
        port_set32(&port, place, 0x15c, piece);
        args[0] = 0x5449fc;
        args[1] = port_u32(&port, 0, 0x4fbf74) + index;
        args[2] = 0;
        args[3] = 0;
        args[4] = 0;
        ecx = 0;
        call_frame(&port, 0x4adf20, piece, sign16(x), ebx, 0, place, index, ebp, args, 5);
        piece = port_u32(&port, place, 0x15c);
        port_call_with(&port, 0x4ac7b0, piece, 1, ebx, 0, place, index, ebp);
        piece = port_u32(&port, place, 0x15c);
        port_set8(&port, piece, 0x4e, 0);
        port_set8(&port, port_u32(&port, place, 0x15c), 0x93, 1);
        port_set16(&port, port_u32(&port, place, 0x15c), 0x48, 0);
        port_set32(&port, port_u32(&port, place, 0x15c), 4, port_u32(&port, panel, 0));
        port_call_with(&port, 0x4ac8f0, port_u32(&port, place, 0x15c), 0, ebx, 0, place, index,
                       ebp);
        port_set32(&port, port_u32(&port, place, 0x15c), 0x58, index + 1);
        port_call_with(&port, 0x4adfa0, port_u32(&port, place, 0x15c), 0, ebx, 0, place, index,
                       ebp);
        port_set32(&port, port_u32(&port, place, 0x15c), 0x7c, 0);
        port_call_with(&port, 0x4ac8a0, port_u32(&port, place, 0x15c), 0x44ff90, ebx, 0, place,
                       index, ebp);
        port_call_with(&port, 0x4ac8f0, port_u32(&port, place, 0x15c), vertrix_lift_edx, ebx, 0,
                       place, index, ebp);
        piece = port_call_with(&port, 0x4ca000, 0x15c, vertrix_lift_edx, ebx, 0, place, index, ebp);
        if (piece != 0)
        {
            port_set32(&port, ebp, -0x20u, piece);
            port_set32(&port, ebp, -0x2cu, 3);
            piece = port_call_with(&port, 0x4abd70, piece, 0, 3, 0, place, index, ebp);
            port_set32(&port, ebp, -0x2cu, vertrix_lift_edx);
        }
        ebx = sign16(y);
        port_set32(&port, place, 0x168, piece);
        args[0] = 0x5466a4;
        args[1] = 0;
        call_frame(&port, 0x4adf20, piece, sign16(x), ebx, 0, place, index, ebp, args, 5);
        piece = port_u32(&port, place, 0x168);
        port_call_with(&port, 0x4ac7b0, piece, 1, ebx, 0, place, index, ebp);
        port_set8(&port, port_u32(&port, place, 0x168), 0x4e, 0x32);
        port_set8(&port, port_u32(&port, place, 0x168), 0x93, 1);
        port_set8(&port, port_u32(&port, place, 0x168), 0x95, 4);
        port_set16(&port, port_u32(&port, place, 0x168), 0x48, 0);
        port_set32(&port, port_u32(&port, place, 0x168), 4, port_u32(&port, panel, 0));
        piece = port_u32(&port, place, 0x168);
        port_call_with(&port, 0x4adfa0, piece, 0, ebx, 0, place + 4, index, ebp);
        port_call_with(&port, 0x4ac8f0, port_u32(&port, place, 0x168), 0, ebx, 0, place + 4,
                       index + 1, ebp);
        port_call_with(&port, 0x4ac8a0, port_u32(&port, place, 0x168), 0x450130, ebx, 0, place + 4,
                       index + 1, ebp);
        port_call_with(&port, 0x4ac8f0, port_u32(&port, place, 0x168), vertrix_lift_edx, ebx, 0,
                       place + 4, index + 1, ebp);
        port_set32(&port, ebp, -0x2cu, 0);
    }
    return port_return(&port, port_u32(&port, ebp, -0x38u), vertrix_lift_edx);
}

/* Original 0x42b6b0: the panel's bar eax for the side dl and the player ebx: made (0x4adf20 with
 * five zeros), placed at 0x4f89b0, 0x4f89b4 for side 0 (its box to 0x4f89c0 and 0x4f89c4 wide,
 * its origin 0x4f9098 and 0x4f909c in), or 0x4f89b8, 0x4f89bc for the other side; its step
 * (0x4ac490, twice the level 0x532bbc's speed 0x4f7d50 of the player), speed (0x4ac7d0), +0x1a
 * (0x4f7dc8) and size 0x12c (0x4ac860) set, +0x8e 3, its box at +0xa8, the state 0x450710 or
 * 0x450730 (0x4ac8f0), shown (0x42b920 with 1) and +0x170 cleared. */
uint32_t vertrix_port_ui_player_bar_construct_42b6b0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x20
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t bar = entry->eax;
    uint32_t side = entry->edx & 0xff;
    uint32_t edi = entry->ebx * 4;
    uint32_t zeros[5] = {0, 0, 0, 0, 0};
    uint32_t left;
    uint32_t right;
    uint32_t top;
    uint32_t bottom;
    uint32_t ebx;
    uint32_t level;
    uint32_t eax;
    uint32_t ecx;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set8(&port, bar, 0x16c, side);
    call_frame(&port, 0x4adf20, bar, 0, 0, 0, bar, edi, ebp, zeros, 5);
    if (side == 0)
    {
        left = port_u32(&port, 0, 0x4f89b0);
        top = port_u32(&port, 0, 0x4f89b4);
        ebx = 0;
        port_set32(&port, ebp, -0x1cu, left);
    }
    else
    {
        left = port_u32(&port, 0, 0x4f89b8);
        top = port_u32(&port, 0, 0x4f89bc);
        ebx = top;
    }
    ecx = side == 0 ? top : left;
    right = left + port_u32(&port, 0, 0x4f89c0) - 1;
    bottom = port_u32(&port, 0, 0x4f89c4) + top - 1;
    port_set32(&port, ebp, -0x18u, right);
    port_set32(&port, ebp, -0x14u, bottom);
    if (side == 0)
    {
        port_set16(&port, bar, 0xe, right - port_u16(&port, 0, 0x4f9098));
    }
    else
    {
        port_set32(&port, ebp, -0x10u, port_u32(&port, 0, 0x532bbc));
        port_set16(&port, bar, 0xe, left);
    }
    port_set16(&port, bar, 0x16, top - port_u16(&port, 0, 0x4f909c));
    level = port_u32(&port, 0, 0x532bbc);
    port_call_with(&port, 0x4ac490, bar, port_u32(&port, 0, edi + level * 40 + 0x4f7d50) * 2, ebx,
                   ecx, bar, edi, ebp);
    level = port_u32(&port, 0, 0x532bbc);
    if (side != 0)
    {
        port_set32(&port, ebp, -0x10u, level);
    }
    port_call_with(&port, 0x4ac7d0, bar, port_u32(&port, 0, edi + level * 40 + 0x4f7d50), ebx, ecx,
                   bar, edi, ebp);
    level = port_u32(&port, 0, 0x532bbc);
    if (side == 0)
    {
        ebx = level;
    }
    else
    {
        port_set32(&port, ebp, -0x10u, level);
    }
    port_set16(&port, bar, 0x1a, port_u16(&port, 0, edi + level * 40 + 0x4f7dc8));
    port_call_with(&port, 0x4ac860, bar, 0x12c, ebx, ecx, bar, edi, ebp);
    port_set8(&port, bar, 0x8e, 3);
    port_set16(&port, bar, 0xa8, side == 0 ? port_u32(&port, ebp, -0x1cu) : left);
    port_set16(&port, bar, 0xaa, right);
    port_set16(&port, bar, 0xae, bottom);
    port_set16(&port, bar, 0xac, top);
    port_call_with(&port, 0x4ac8f0, bar, side == 0 ? 0x450710 : 0x450730, ebx, ecx, bar, edi, ebp);
    eax = port_call_with(&port, 0x42b920, bar, 1, ebx, ecx, bar, edi, ebp);
    port_set32(&port, bar, 0x170, 0);
    return port_return(&port, eax, vertrix_lift_edx);
}
