#include "landings.h"

/* The player's piece landing. */

static uint32_t call_frame(Port *port, uint32_t target, uint32_t eax, uint32_t edx, uint32_t ebx,
                           uint32_t ecx, uint32_t esi, uint32_t edi, uint32_t ebp,
                           const uint32_t *stack, unsigned count)
{
    return port_call_registers(port, target, eax, edx, ebx, ecx, esi, edi, ebp, stack, count);
}

/* The sound `cue` (a word of the player) on both sides of the set 0x54d640 (0x4761d0,
 * 0x476280). */
static uint32_t landing_sound(Port *port, uint32_t player, uint32_t cue, uint32_t edi, uint32_t ebp)
{
    const uint32_t zero[1] = {0};
    call_frame(port, 0x4761d0, 0x54d640, port_u16(port, player, cue), 0, 0, player, edi, ebp, zero,
               1);
    return call_frame(port, 0x476280, 0x54d640, port_u16(port, player, cue), 0, 0, player, edi, ebp,
                      zero, 1);
}

/* Original 0x43b260: the landing of the player eax's piece +0x450 while +0x454 is set: with the
 * piece's +0x178 set to 1 it is resolved (0x427850; +0x170 1 when it gives 1, else 0), +0x178
 * cleared, the piece restarted (0x4ac510), the player's delay drawn (0x43b660) and the piece's
 * speed +0x45c (0x4ac7d0); else the piece moves (0x4ac500) and, once it lands (0x4ac520 gives
 * 1), is restarted, the delay drawn and its speed set likewise, then: with +0x170 set it is
 * cleared and, when the piece's kind +0x1d5 is 4 or the first turn (0x43b1a0) answers its edx,
 * the player 1 or 2 (by [eax]) sounds its cue +0x160 or +0x162; without, a board (+0x15c)
 * without its object (0x431480) sounds the cue +0x166. The registers but eax kept. */
uint32_t vertrix_port_player_landing_43b260(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x10
    };
    Port port;
    uint32_t player = entry->eax;
    uint32_t edi = entry->edi;
    uint32_t ebp = entry->ebp;
    uint32_t piece;
    uint32_t value;
    uint32_t result;
    uint32_t side;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, entry->esp, -4u, entry->ebx);
    port_set32(&port, entry->esp, -8u, entry->ecx);
    port_set32(&port, entry->esp, -0xcu, entry->edx);
    port_set32(&port, entry->esp, -0x10u, entry->esi);
    result = port_u32(&port, player, 0x454);
    if (result == 0)
    {
        return port_return(&port, 0, entry->edx);
    }
    piece = port_u32(&port, player, 0x450);
    value = port_u32(&port, piece, 0x178);
    if (value == 1)
    {
        result = port_call_with(&port, 0x427850, piece, player, entry->ebx, entry->ecx, player, edi,
                                ebp);
        port_set32(&port, port_u32(&port, player, 0x450), 0x170, result == 1);
        port_set32(&port, port_u32(&port, player, 0x450), 0x178, 0);
        port_call_with(&port, 0x4ac510, port_u32(&port, player, 0x450), vertrix_lift_edx,
                       entry->ebx, entry->ecx, player, edi, ebp);
        port_call_with(&port, 0x43b660, player, vertrix_lift_edx, entry->ebx, entry->ecx, player,
                       edi, ebp);
        result = port_call_with(&port, 0x4ac7d0, port_u32(&port, player, 0x450),
                                port_u32(&port, player, 0x45c), entry->ebx, entry->ecx, player, edi,
                                ebp);
        return port_return(&port, result, entry->edx);
    }
    port_call_with(&port, 0x4ac500, piece, value, entry->ebx, entry->ecx, player, edi, ebp);
    result = port_call_with(&port, 0x4ac520, port_u32(&port, player, 0x450), vertrix_lift_edx,
                            entry->ebx, entry->ecx, player, edi, ebp);
    if (result != 1)
    {
        return port_return(&port, result, entry->edx);
    }
    port_call_with(&port, 0x4ac510, port_u32(&port, player, 0x450), vertrix_lift_edx, entry->ebx,
                   entry->ecx, player, edi, ebp);
    port_call_with(&port, 0x43b660, player, vertrix_lift_edx, entry->ebx, entry->ecx, player, edi,
                   ebp);
    port_call_with(&port, 0x4ac7d0, port_u32(&port, player, 0x450), port_u32(&port, player, 0x45c),
                   entry->ebx, entry->ecx, player, edi, ebp);
    piece = port_u32(&port, player, 0x450);
    value = port_u32(&port, piece, 0x170);
    if (value != 1)
    {
        result = port_call_with(&port, 0x431480, port_u32(&port, player, 0x15c), value, entry->ebx,
                                entry->ecx, player, edi, ebp);
        if (result != 0)
        {
            return port_return(&port, result, entry->edx);
        }
        return port_return(&port, landing_sound(&port, player, 0x166, edi, ebp), entry->edx);
    }
    port_set32(&port, piece, 0x170, 0);
    piece = port_u32(&port, player, 0x450);
    result = (piece & 0xffffff00u) | port_u8(&port, piece, 0x1d5);
    if ((result & 0xff) != 4)
    {
        result = port_call_with(&port, 0x43b1a0, player, value, entry->ebx, entry->ecx, player, edi,
                                ebp);
        if (result != vertrix_lift_edx)
        {
            return port_return(&port, result, entry->edx);
        }
    }
    side = port_u32(&port, player, 0);
    if (side == 1)
    {
        return port_return(&port, landing_sound(&port, player, 0x160, edi, ebp), entry->edx);
    }
    if (side == 2)
    {
        return port_return(&port, landing_sound(&port, player, 0x162, edi, ebp), entry->edx);
    }
    return port_return(&port, result, entry->edx);
}
