#include "port_rtlaikeys.h"

/* The computer player's keys. */

/* A call (with count stack arguments, nearest first) that leaves its eax and edx in *eax and
 * *edx; the eax. */
static uint32_t ai_call(Port *port, uint32_t *eax, uint32_t *edx, uint32_t target, uint32_t a,
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

/* The player's key at +key pressed on the key table 0x54d640 (0x4761d0 and 0x476280, each with
 * 0); ebx and ecx left 0. */
static void press(Port *port, uint32_t *eax, uint32_t *edx, uint32_t *ebx, uint32_t *ecx,
                  uint32_t player, uint32_t edi, uint32_t ebp, uint32_t key)
{
    uint32_t zero = 0;
    *ebx = 0;
    *ecx = 0;
    ai_call(port, eax, edx, 0x4761d0, 0x54d640, port_u16(port, player, key), 0, 0, player, edi, ebp,
            &zero, 1);
    ai_call(port, eax, edx, 0x476280, 0x54d640, port_u16(port, player, key), 0, 0, player, edi, ebp,
            &zero, 1);
}

/* Original 0x43ad70: the computer player eax's move (its brain +0x450, on with +0x454). A brain
 * set to think (+0x178 1) reads the falling piece (0x431fa0 of the board +0x15c), picks a place
 * (0x425f60), +0x178 0, 0x4ac510, 0x43b5b0 and 0x4ac7d0 with +0x458. Otherwise 0x4ac500, and on
 * its tick (0x4ac520 1) 0x4ac510, 0x43b5b0, 0x4ac7d0, and with the piece's place (0x431b20) it
 * presses the player's keys toward the brain's column +0x168 and turns +0x16c (each counted
 * down): left +0x160 or right +0x162, turn +0x164, drop +0x166 when in place and 0x431380
 * allows. Mode 4 (+0x160) moves and may then turn or drop; mode 3 moves, else turns, else drops;
 * others turn first. edx kept. */
uint32_t vertrix_port_ai_keys_43ad70(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x30
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t player = entry->eax;
    uint32_t eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t edi = entry->edi;
    uint32_t brain;
    uint32_t column;
    uint32_t mode;
#define CALL(target, a, d)                                                                         \
    ai_call(&port, &eax, &edx, target, a, d, ebx, ecx, player, edi, ebp, NULL, 0)
#define PRESS(key) press(&port, &eax, &edx, &ebx, &ecx, player, edi, ebp, key)
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -4u, entry->ebx);
    port_set32(&port, ebp, -8u, entry->ecx);
    port_set32(&port, ebp, -0xcu, entry->edx);
    port_set32(&port, ebp, -0x10u, entry->esi);
    port_set32(&port, ebp, -0x14u, entry->edi);
    eax = port_u32(&port, player, 0x454);
    if (eax == 0)
    {
        return port_return(&port, eax, entry->edx);
    }
    brain = port_u32(&port, player, 0x450);
    edx = port_u32(&port, brain, 0x178);
    if (edx == 1)
    {
        uint32_t arg;
        ecx = ebp - 0x20;
        ebx = ebp - 0x18;
        CALL(0x431fa0, port_u32(&port, player, 0x15c), ebp - 0x1c);
        arg = (uint32_t)(int32_t)(int8_t)port_u8(&port, ebp, -0x20u);
        ecx = (uint32_t)(int32_t)(int8_t)port_u8(&port, ebp, -0x18u);
        ebx = (uint32_t)(int32_t)(int8_t)port_u8(&port, ebp, -0x1cu);
        ai_call(&port, &eax, &edx, 0x425f60, port_u32(&port, player, 0x450), player, ebx, ecx,
                player, edi, ebp, &arg, 1);
        port_set32(&port, port_u32(&port, player, 0x450), 0x178, 0);
        CALL(0x4ac510, port_u32(&port, player, 0x450), edx);
        CALL(0x43b5b0, player, edx);
        CALL(0x4ac7d0, port_u32(&port, player, 0x450), port_u32(&port, player, 0x458));
        return port_return(&port, eax, entry->edx);
    }
    CALL(0x4ac500, brain, edx);
    if (CALL(0x4ac520, port_u32(&port, player, 0x450), edx) != 1)
    {
        return port_return(&port, eax, entry->edx);
    }
    CALL(0x4ac510, port_u32(&port, player, 0x450), edx);
    CALL(0x43b5b0, player, edx);
    ecx = ebp - 0x24;
    CALL(0x4ac7d0, port_u32(&port, player, 0x450), port_u32(&port, player, 0x458));
    ebx = ebp - 0x28;
    port_set32(&port, ebp, -0x2cu, 0);
    port_set32(&port, ebp, -0x28u, 0);
    port_set32(&port, ebp, -0x24u, 0);
    if (CALL(0x431b20, port_u32(&port, player, 0x15c), ebp - 0x2c) == 0)
    {
        return port_return(&port, eax, entry->edx);
    }
    edx = port_u32(&port, player, 0x450);
    mode = port_u32(&port, edx, 0x160);
    edi = mode;
    column = port_u32(&port, ebp, -0x2cu);
    if (mode == 4)
    {
        ecx = port_u32(&port, edx, 0x168);
        if ((int32_t)column > (int32_t)ecx)
        {
            PRESS(0x160);
        }
        else if ((int32_t)column < (int32_t)ecx)
        {
            PRESS(0x162);
        }
        edx = port_u32(&port, player, 0x450);
        edi = port_u32(&port, edx, 0x16c);
        if ((int32_t)edi > 0)
        {
            port_set32(&port, edx, 0x16c, edi - 1);
            PRESS(0x164);
            return port_return(&port, eax, entry->edx);
        }
        eax = port_u32(&port, ebp, -0x2cu);
        if (eax != port_u32(&port, edx, 0x168))
        {
            return port_return(&port, eax, entry->edx);
        }
    }
    else if (mode == 3)
    {
        ecx = port_u32(&port, edx, 0x168);
        if ((int32_t)column > (int32_t)ecx)
        {
            PRESS(0x160);
            return port_return(&port, eax, entry->edx);
        }
        if ((int32_t)column < (int32_t)ecx)
        {
            PRESS(0x162);
            return port_return(&port, eax, entry->edx);
        }
        edi = port_u32(&port, edx, 0x16c);
        if ((int32_t)edi > 0)
        {
            port_set32(&port, edx, 0x16c, edi - 1);
            PRESS(0x164);
            return port_return(&port, eax, entry->edx);
        }
    }
    else
    {
        ecx = port_u32(&port, edx, 0x16c);
        if ((int32_t)ecx > 0)
        {
            port_set32(&port, edx, 0x16c, ecx - 1);
            PRESS(0x164);
            return port_return(&port, eax, entry->edx);
        }
        ebx = port_u32(&port, edx, 0x168);
        if ((int32_t)column > (int32_t)ebx)
        {
            PRESS(0x160);
            return port_return(&port, eax, entry->edx);
        }
        if ((int32_t)column < (int32_t)ebx)
        {
            PRESS(0x162);
            return port_return(&port, eax, entry->edx);
        }
    }
    if (CALL(0x431380, port_u32(&port, player, 0x15c), edx) != 0)
    {
        return port_return(&port, eax, entry->edx);
    }
    PRESS(0x166);
#undef CALL
#undef PRESS
    return port_return(&port, eax, entry->edx);
}
