#include "port_turns.h"

/* The computer player's tick, the players' key steps, the board shifts, a drop's landing
 * and the pointer and slot picks. */

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

/* The key notes 0x4761d0 and 0x476280 on 0x54d640 for the key `key`, each with a zero argument. */
static uint32_t key_notes(Port *port, uint32_t key, uint32_t esi, uint32_t edi, uint32_t ebp)
{
    uint32_t args[1] = {0};
    call_frame(port, 0x4761d0, 0x54d640, key, 0, 0, esi, edi, ebp, args, 1);
    return call_frame(port, 0x476280, 0x54d640, key, 0, 0, esi, edi, ebp, args, 1);
}

/* Original 0x43b430: the player eax's computer tick, when it has one (+0x454): with the thinker
 * +0x450 ready (+0x178 1) it thinks (0x427850), places on the board +0x15c's piece +0xb78 the
 * choice +0x46c (0x42b090, 0x4290a0), is cleared, steps (0x4ac510, 0x43b680) and waits +0x460
 * (0x4ac7d0); otherwise when due (0x4ac500, 0x4ac520) it steps and waits likewise and presses a
 * key: the key +0x164 while the thinker's moves +0x16c last (counting down), else the key +0x166
 * once the board is idle (0x431490 of 0). */
uint32_t vertrix_port_player_ai_tick_43b430(PORT_SIGNATURE)
{
    Port port;
    uint32_t player = entry->eax;
    uint32_t thinker;
    uint32_t moves;
    uint32_t eax;
    port_open(&port, calls, services, globals, entry);
    eax = port_u32(&port, player, 0x454);
    if (eax == 0)
    {
        return port_return(&port, eax, entry->edx);
    }
    thinker = port_u32(&port, player, 0x450);
    if (port_u32(&port, thinker, 0x178) == 1)
    {
        port_call_with(&port, 0x427850, thinker, player, entry->ebx, entry->ecx, player, entry->edi,
                       entry->ebp);
        port_call_with(&port, 0x42b090, port_u32(&port, port_u32(&port, player, 0x15c), 0xb78),
                       port_u32(&port, player, 0x46c), entry->ebx, entry->ecx, player, entry->edi,
                       entry->ebp);
        port_call_with(&port, 0x4290a0, port_u32(&port, player, 0x450),
                       port_u32(&port, player, 0x46c), entry->ebx, entry->ecx, player, entry->edi,
                       entry->ebp);
        port_set32(&port, port_u32(&port, player, 0x450), 0x178, 0);
        port_call_with(&port, 0x4ac510, port_u32(&port, player, 0x450), vertrix_lift_edx,
                       entry->ebx, entry->ecx, player, entry->edi, entry->ebp);
        port_call_with(&port, 0x43b680, player, vertrix_lift_edx, entry->ebx, entry->ecx, player,
                       entry->edi, entry->ebp);
        eax = port_call_with(&port, 0x4ac7d0, port_u32(&port, player, 0x450),
                             port_u32(&port, player, 0x460), entry->ebx, entry->ecx, player,
                             entry->edi, entry->ebp);
        return port_return(&port, eax, entry->edx);
    }
    port_call_with(&port, 0x4ac500, thinker, port_u32(&port, thinker, 0x178), entry->ebx,
                   entry->ecx, player, entry->edi, entry->ebp);
    eax = port_call_with(&port, 0x4ac520, port_u32(&port, player, 0x450), vertrix_lift_edx,
                         entry->ebx, entry->ecx, player, entry->edi, entry->ebp);
    if (eax != 1)
    {
        return port_return(&port, eax, entry->edx);
    }
    port_call_with(&port, 0x4ac510, port_u32(&port, player, 0x450), vertrix_lift_edx, entry->ebx,
                   entry->ecx, player, entry->edi, entry->ebp);
    port_call_with(&port, 0x43b680, player, vertrix_lift_edx, entry->ebx, entry->ecx, player,
                   entry->edi, entry->ebp);
    port_call_with(&port, 0x4ac7d0, port_u32(&port, player, 0x450), port_u32(&port, player, 0x460),
                   entry->ebx, entry->ecx, player, entry->edi, entry->ebp);
    thinker = port_u32(&port, player, 0x450);
    moves = port_u32(&port, thinker, 0x16c);
    if ((int32_t)moves > 0)
    {
        port_set32(&port, thinker, 0x16c, moves - 1);
        eax = key_notes(&port, port_u16(&port, player, 0x164), player, entry->edi, entry->ebp);
        return port_return(&port, eax, entry->edx);
    }
    eax = port_call_with(&port, 0x431490, port_u32(&port, player, 0x15c), moves, entry->ebx,
                         entry->ecx, player, entry->edi, entry->ebp);
    if (eax != 0)
    {
        return port_return(&port, eax, entry->edx);
    }
    eax = key_notes(&port, port_u16(&port, player, 0x166), player, entry->edi, entry->ebp);
    return port_return(&port, eax, entry->edx);
}

/* The key `key` of the player (0x476480 on 0x54d640) calls `action` on the piece and is taken
 * (0x476320). */
static void key_action(Port *port, uint32_t player, uint32_t key, uint32_t piece, uint32_t action,
                       uint32_t ebx, uint32_t ecx, uint32_t esi, uint32_t edi, uint32_t ebp)
{
    if (port_call_with(port, 0x476480, 0x54d640, port_u16(port, player, key), ebx, ecx, esi, edi,
                       ebp) == 0)
    {
        return;
    }
    port_call_with(port, action, piece, vertrix_lift_edx, ebx, ecx, esi, edi, ebp);
    port_call_with(port, 0x476320, 0x54d640, port_u16(port, player, key), ebx, ecx, esi, edi, ebp);
}

/* Original 0x451aa0: the player eax's key step (0x43b260): the keys +0x168, +0x16a and +0x16e move
 * the board +0x15c's piece +0xb70 (0x42b950, 0x42b990, 0x42b9f0); the board runs (method +4 of
 * +0x158); when the piece has landed (0x42ba40) the board settles (0x432110) and the player takes
 * the state 0x450ff0 with 0 (0x43bae0) when it is over (0x43d3b0) or the board's +0xb74 is 1
 * (after 0x43b9c0), or 0x451c00 with 3 when +0xb74 is 0. */
uint32_t vertrix_port_player_key_step_451aa0(PORT_SIGNATURE)
{
    Port port;
    uint32_t player = entry->eax;
    uint32_t board;
    uint32_t methods;
    uint32_t kind;
    uint32_t eax;
    port_open(&port, calls, services, globals, entry);
    board = port_u32(&port, player, 0x15c);
    port_call_with(&port, 0x43b260, player, entry->edx, board, player, player, entry->edi,
                   entry->ebp);
    key_action(&port, player, 0x168, port_u32(&port, board, 0xb70), 0x42b950, board, player, player,
               entry->edi, entry->ebp);
    key_action(&port, player, 0x16a, port_u32(&port, board, 0xb70), 0x42b990, board, player, player,
               entry->edi, entry->ebp);
    key_action(&port, player, 0x16e, port_u32(&port, board, 0xb70), 0x42b9f0, board, player, player,
               entry->edi, entry->ebp);
    methods = port_u32(&port, board, 0x158);
    port_call_with(&port, port_u32(&port, methods, 4), board, methods, board, player, player,
                   entry->edi, entry->ebp);
    eax = port_call_with(&port, 0x42ba40, port_u32(&port, board, 0xb70), vertrix_lift_edx, board,
                         player, player, entry->edi, entry->ebp);
    if (eax != 1)
    {
        return port_return(&port, eax, entry->edx);
    }
    port_call_with(&port, 0x432110, board, vertrix_lift_edx, board, player, player, entry->edi,
                   entry->ebp);
    eax = port_call_with(&port, 0x43d3b0, player, vertrix_lift_edx, board, player, player,
                         entry->edi, entry->ebp);
    if (eax != 1)
    {
        kind = port_u32(&port, board, 0xb74);
        if (kind == 0)
        {
            port_call_with(&port, 0x4ac8f0, player, 0x451c00, board, player, player, entry->edi,
                           entry->ebp);
            eax = port_call_with(&port, 0x43bae0, player, 3, board, player, player, entry->edi,
                                 entry->ebp);
            return port_return(&port, eax, entry->edx);
        }
        if (kind != 1)
        {
            return port_return(&port, eax, entry->edx);
        }
        port_call_with(&port, 0x43b9c0, player, kind, board, player, player, entry->edi,
                       entry->ebp);
    }
    port_call_with(&port, 0x4ac8f0, player, 0x450ff0, board, player, player, entry->edi,
                   entry->ebp);
    eax = port_call_with(&port, 0x43bae0, player, 0, board, player, player, entry->edi, entry->ebp);
    return port_return(&port, eax, entry->edx);
}

/* Original 0x451c80: the player eax's computer key step (0x43b430): the keys +0x16e and +0x16c
 * move the board +0x15c's piece +0xb78 (0x42b000, 0x42af80); the board runs (method +4 of
 * +0x158); when the piece has landed (0x42b050) the board settles (0x4321b0); unless the player
 * is over (0x43d3b0), a find of the board's +0xb7c by the thinker +0x3b8 (0x42a080) keeps it at
 * +0x194 with the found byte at +0x198 and gives the states 0x450ff0 with 0 (0x43bae0) and then
 * that of 0x43bb60 with 0x451f10; otherwise the state 0x450ff0 with 0. */
uint32_t vertrix_port_player_ai_key_step_451c80(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x1c
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t player = entry->eax;
    uint32_t board;
    uint32_t thinker;
    uint32_t methods;
    uint32_t ebx = player;
    uint32_t eax;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    board = port_u32(&port, player, 0x15c);
    thinker = port_u32(&port, player, 0x3b8);
    port_call_with(&port, 0x43b430, player, entry->edx, player, player, board, thinker, ebp);
    key_action(&port, player, 0x16e, port_u32(&port, board, 0xb78), 0x42b000, player, player, board,
               thinker, ebp);
    key_action(&port, player, 0x16c, port_u32(&port, board, 0xb78), 0x42af80, player, player, board,
               thinker, ebp);
    methods = port_u32(&port, board, 0x158);
    port_call_with(&port, port_u32(&port, methods, 4), board, methods, player, player, board,
                   thinker, ebp);
    eax = port_call_with(&port, 0x42b050, port_u32(&port, board, 0xb78), vertrix_lift_edx, player,
                         player, board, thinker, ebp);
    if (eax != 1)
    {
        return port_return(&port, eax, entry->edx);
    }
    port_call_with(&port, 0x4321b0, board, vertrix_lift_edx, player, player, board, thinker, ebp);
    eax = port_call_with(&port, 0x43d3b0, player, vertrix_lift_edx, player, player, board, thinker,
                         ebp);
    if (eax != 1)
    {
        ebx = ebp - 0x18;
        eax = port_call_with(&port, 0x42a080, thinker, port_u8(&port, board, 0xb7c), ebx, player,
                             board, thinker, ebp);
        if (eax == 1)
        {
            port_set32(&port, player, 0x194, port_u32(&port, board, 0xb7c));
            port_set32(&port, player, 0x198, port_u8(&port, ebp, -0x18u));
            port_call_with(&port, 0x4ac8f0, player, 0x450ff0, ebx, player, board, thinker, ebp);
            port_call_with(&port, 0x43bae0, player, 0, ebx, player, board, thinker, ebp);
            port_call_with(&port, 0x43bb60, player, 0x451f10, ebx, player, board, thinker, ebp);
            eax = port_call_with(&port, 0x4ac8f0, player, vertrix_lift_edx, ebx, player, board,
                                 thinker, ebp);
            return port_return(&port, eax, entry->edx);
        }
    }
    port_call_with(&port, 0x4ac8f0, player, 0x450ff0, ebx, player, board, thinker, ebp);
    eax = port_call_with(&port, 0x43bae0, player, 0, ebx, player, board, thinker, ebp);
    return port_return(&port, eax, entry->edx);
}

static uint32_t sign8(uint32_t value)
{
    return (uint32_t)(int32_t)(int8_t)value;
}

typedef struct
{
    int32_t way;
    uint32_t edge;
    uint32_t start;
    uint32_t settle;
    uint32_t settled;
    uint32_t filled;
    uint32_t fits;
    uint32_t next;
    uint32_t end;
} Shift;

static int shift_short(const Shift *shift, uint32_t offset)
{
    return shift->way > 0 ? (int32_t)offset < 0x18 : (int32_t)offset > -0x18;
}

/* The board shift shared by 0x454090 and 0x4543a0: the player eax's board +0x15c moves when due
 * (0x4ac500, 0x4ac520, 0x4ac540, 0x4ac5b0), its offset +0x58 going `way` by the step times its
 * speed +0x10 >> 16. Short of a column (24) it eases (`edge`, `end` with the player's +0x42c and
 * +0x430); otherwise the column shifts (`start`, `settle`), and once settled and full (`settled`,
 * `filled`) the pending pick +0x170 is played (0x43a560 with the player's +0x3b4 and the signed
 * kinds of the board +0xa60's three pieces) and cleared and the board is rebuilt (0x42eb60);
 * +0x430 counts on, the offset sheds whole columns, and when the column no longer fits (`fits`)
 * the player scores 0x4f8188 (0x43c0e0), else takes the state `next`. The board then runs (method
 * +4 of +0x158). */
static uint32_t board_shift(PORT_SIGNATURE, const Shift *shift)
{
    enum
    {
        BELOW = 0x1c
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t player = entry->eax;
    uint32_t board;
    uint32_t edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t eax;
    uint32_t offset;
    uint32_t pieces;
    uint32_t methods;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    board = port_u32(&port, player, 0x15c);
    port_set32(&port, ebp, -0x18u, port_u32(&port, player, 0x3b4));
    port_call_with(&port, 0x4ac500, board, entry->edx, ebx, ecx, board, player, ebp);
    eax = port_call_with(&port, 0x4ac520, board, vertrix_lift_edx, ebx, ecx, board, player, ebp);
    edx = vertrix_lift_edx;
    if (eax == 1)
    {
        eax = port_call_with(&port, 0x4ac540, board, edx, ebx, ecx, board, player, ebp);
        port_call_with(&port, 0x4ac5b0, board, eax, ebx, ecx, board, player, ebp);
        edx = vertrix_lift_edx * (uint32_t)((int32_t)port_u32(&port, board, 0x10) >> 16);
        port_set32(&port, board, 0x58,
                   shift->way > 0 ? port_u32(&port, board, 0x58) + edx
                                  : port_u32(&port, board, 0x58) - edx);
    }
    if (shift_short(shift, port_u32(&port, board, 0x58)))
    {
        port_call_with(&port, shift->edge, board, edx, ebx, ecx, board, player, ebp);
        ebx = port_u32(&port, player, 0x430);
        port_call_with(&port, shift->end, board, port_u32(&port, player, 0x42c), ebx, ecx, board,
                       player, ebp);
    }
    else
    {
        ebx = port_u32(&port, player, 0x430);
        port_call_with(&port, shift->start, board, port_u32(&port, player, 0x42c), ebx, ecx, board,
                       player, ebp);
        port_call_with(&port, shift->settle, board, vertrix_lift_edx, ebx, ecx, board, player, ebp);
        if (port_call_with(&port, shift->settled, board, vertrix_lift_edx, ebx, ecx, board, player,
                           ebp) == 1 &&
            port_call_with(&port, shift->filled, board, vertrix_lift_edx, ebx, ecx, board, player,
                           ebp) == 1)
        {
            if (port_u32(&port, player, 0x170) == 1)
            {
                pieces = port_u32(&port, board, 0xa60);
                ecx = sign8(port_u8(&port, port_u32(&port, pieces, 0x164), 0x15c));
                ebx = sign8(port_u8(&port, port_u32(&port, pieces, 0x160), 0x15c));
                edx = sign8(port_u8(&port, port_u32(&port, pieces, 0x15c), 0x15c));
                port_call_with(&port, 0x43a560, port_u32(&port, ebp, -0x18u), edx, ebx, ecx, board,
                               player, ebp);
                port_set32(&port, player, 0x170, 0);
            }
            port_call_with(&port, 0x42eb60, board, vertrix_lift_edx, ebx, ecx, board, player, ebp);
        }
        port_set32(&port, player, 0x430, port_u32(&port, player, 0x430) + 1);
        offset = port_u32(&port, board, 0x58);
        while (!shift_short(shift, offset))
        {
            offset = shift->way > 0 ? offset - 0x18 : offset + 0x18;
            port_set32(&port, board, 0x58, offset);
            ebx = offset;
        }
        ebx = port_u32(&port, player, 0x430);
        eax = port_call_with(&port, shift->fits, board, port_u32(&port, player, 0x42c), ebx, ecx,
                             board, player, ebp);
        if (eax != 0)
        {
            port_call_with(&port, 0x43c0e0, player, port_u32(&port, 0, 0x4f8188), ebx, ecx, board,
                           player, ebp);
        }
        else
        {
            port_call_with(&port, 0x4ac8f0, player, shift->next, ebx, ecx, board, player, ebp);
        }
    }
    methods = port_u32(&port, board, 0x158);
    eax = port_call_with(&port, port_u32(&port, methods, 4), board, methods, ebx, ecx, board,
                         player, ebp);
    return port_return(&port, eax, entry->edx);
}

/* Original 0x454090: the board shift forwards (0x42f440, 0x42f6e0, 0x42f580, 0x4320c0, 0x432040,
 * 0x431780, the state 0x454200, 0x42f520). */
uint32_t vertrix_port_board_shift_454090(PORT_SIGNATURE)
{
    static const Shift shift = {1,        0x42f440, 0x42f6e0, 0x42f580, 0x4320c0,
                                0x432040, 0x431780, 0x454200, 0x42f520};
    return board_shift(calls, services, globals, entry, &shift);
}

/* Original 0x4543a0: the board shift backwards (0x42f4b0, 0x42f720, 0x42f620, 0x4320c0,
 * 0x432080, 0x431930, the state 0x454510, 0x42f550). */
uint32_t vertrix_port_board_shift_4543a0(PORT_SIGNATURE)
{
    static const Shift shift = {-1,       0x42f4b0, 0x42f720, 0x42f620, 0x4320c0,
                                0x432080, 0x431930, 0x454510, 0x42f550};
    return board_shift(calls, services, globals, entry, &shift);
}

static uint32_t sign16(uint32_t value)
{
    return (uint32_t)(int32_t)(int16_t)value;
}

/* Original 0x458880: the actor eax's drop when due (0x4ac500, 0x4ac520): it moves the step
 * (0x4ac540, 0x4ac5b0, 0x4ad060), keeps its place (0x4ad260) centred by its size (0x4b14c0) and
 * shrinks +0x32 by the step to no less than 15; unless it is still going (0x4ad790) or turning
 * (0x4ad5e0 with 1, after +0x70 is cleared), it lands at +0x10, +0x18, centred, waits 20
 * (0x4ac7d0) and takes the state 0x458260 with +0x93 0, +0x48 0, +0x4a 100 and +0x4c 5. */
uint32_t vertrix_port_actor_drop_land_458880(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x2c
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t actor = entry->eax;
    uint32_t step;
    uint32_t value;
    uint32_t eax;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_call_with(&port, 0x4ac500, actor, entry->edx, entry->ebx, actor, entry->esi, entry->edi,
                   ebp);
    eax = port_call_with(&port, 0x4ac520, actor, vertrix_lift_edx, entry->ebx, actor, entry->esi,
                         entry->edi, ebp);
    if (eax != 1)
    {
        return port_return(&port, eax, entry->edx);
    }
    step = port_call_with(&port, 0x4ac540, actor, vertrix_lift_edx, entry->ebx, actor, entry->esi,
                          entry->edi, ebp);
    port_call_with(&port, 0x4ac5b0, actor, step, entry->ebx, actor, step, entry->edi, ebp);
    port_call_with(&port, 0x4ad060, actor, vertrix_lift_edx, ebp - 0x14, actor, step, entry->edi,
                   ebp);
    port_call_with(&port, 0x4ad260, actor, ebp - 0x18, ebp - 0x14, actor, step, entry->edi, ebp);
    port_set32(&port, ebp, -0x28u, 0);
    port_set32(&port, ebp, -0x24u, 0);
    port_call_with(&port, 0x4b14c0, actor, ebp - 0x28, ebp - 0x24, actor, step, entry->edi, ebp);
    port_set16(&port, actor, 8, port_u32(&port, ebp, -0x18u));
    port_set16(&port, actor, 0xa, port_u32(&port, ebp, -0x14u));
    port_set16(&port, actor, 0xe,
               sign16(port_u16(&port, ebp, -0x18u)) - (port_u32(&port, ebp, -0x28u) >> 1));
    port_set16(&port, actor, 0x16,
               sign16(port_u16(&port, ebp, -0x14u)) - (port_u32(&port, ebp, -0x24u) >> 1));
    port_set16(&port, actor, 0x32, port_u16(&port, actor, 0x32) - step);
    value = sign16(port_u16(&port, actor, 0x32));
    if ((int32_t)value < 0xf)
    {
        value = 0xf;
    }
    port_set16(&port, actor, 0x32, value);
    eax = port_call_with(&port, 0x4ad790, actor, step, ebp - 0x24, actor, step, entry->edi, ebp);
    if (eax != 0)
    {
        return port_return(&port, eax, entry->edx);
    }
    port_set32(&port, actor, 0x70, 0);
    eax = port_call_with(&port, 0x4ad5e0, actor, 1, ebp - 0x24, actor, step, entry->edi, ebp);
    if (eax != 0)
    {
        return port_return(&port, eax, entry->edx);
    }
    port_call_with(&port, 0x4ad260, actor, ebp - 0x18, ebp - 0x14, actor, step, entry->edi, ebp);
    port_set16(&port, actor, 8, port_u16(&port, actor, 0x10));
    port_set16(&port, actor, 0xa, port_u16(&port, actor, 0x18));
    port_set32(&port, ebp, -0x20u, 0);
    port_set32(&port, ebp, -0x1cu, 0);
    port_call_with(&port, 0x4b14c0, actor, ebp - 0x20, ebp - 0x1c, actor, 0, entry->edi, ebp);
    port_set16(&port, actor, 0xe,
               sign16(port_u16(&port, actor, 8)) - (port_u32(&port, ebp, -0x20u) >> 1));
    port_set16(&port, actor, 0x16,
               sign16(port_u16(&port, actor, 0xa)) - (port_u32(&port, ebp, -0x1cu) >> 1));
    port_call_with(&port, 0x4ac7d0, actor, 0x14, ebp - 0x1c, actor, 0, entry->edi, ebp);
    eax = port_call_with(&port, 0x4ac8f0, actor, 0x458260, ebp - 0x1c, actor, 0, entry->edi, ebp);
    port_set8(&port, actor, 0x93, 0);
    port_set16(&port, actor, 0x48, 0);
    port_set16(&port, actor, 0x4a, 0x64);
    port_set16(&port, actor, 0x4c, 5);
    return port_return(&port, eax, entry->edx);
}

/* Original 0x448260: the actor eax's pointer pick: when due it moves and bobs (0x4ac500, 0x4ac520,
 * 0x4ac540, 0x4ac5b0; +0x4a 0, +0x4c 5; 0x4ad530); the pointer 0x558944 and 0x558946 (0x7d00 each
 * while 0x558958) over it (0x4b0b70) gives +0x48 35 and +0x52 10, else +0x52 9; the pointer on its
 * pick area (0x4b4270) gives the state 0x4483d0, and a click of 0x74 (0x476480 on 0x54d640) there
 * (0x4764a0, 0x4b4270) the state 0x448610. */
uint32_t vertrix_port_actor_pointer_pick_448260(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x24
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t actor = entry->eax;
    uint32_t pressed;
    uint32_t held;
    uint32_t eax;
    uint32_t x;
    uint32_t y;
    uint32_t args[1];
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_call_with(&port, 0x4ac500, actor, entry->edx, entry->ebx, actor, actor, entry->edi, ebp);
    if (port_call_with(&port, 0x4ac520, actor, vertrix_lift_edx, entry->ebx, actor, actor,
                       entry->edi, ebp) == 1)
    {
        eax = port_call_with(&port, 0x4ac540, actor, vertrix_lift_edx, entry->ebx, actor, actor,
                             entry->edi, ebp);
        port_call_with(&port, 0x4ac5b0, actor, eax, entry->ebx, actor, actor, entry->edi, ebp);
        port_set16(&port, actor, 0x4a, 0);
        port_set16(&port, actor, 0x4c, 5);
        port_call_with(&port, 0x4ad530, actor, vertrix_lift_edx, entry->ebx, actor, actor,
                       entry->edi, ebp);
    }
    pressed = port_u32(&port, 0, 0x558958);
    y = sign16(pressed != 0 ? 0x7d00 : port_u16(&port, 0, 0x558946));
    x = sign16(pressed != 0 ? 0x7d00 : port_u16(&port, 0, 0x558944));
    eax = port_call_with(&port, 0x4b0b70, actor, x, y, pressed, actor, entry->edi, ebp);
    if ((eax & 0xff) != 0)
    {
        port_set16(&port, actor, 0x48, 0x23);
        port_set8(&port, actor, 0x52, 0xa);
    }
    else
    {
        port_set8(&port, actor, 0x52, 9);
    }
    held = port_u32(&port, 0, 0x558958);
    y = held != 0 ? 0x7d00 : port_u16(&port, 0, 0x558946);
    x = held != 0 ? 0x7d00 : port_u16(&port, 0, 0x558944);
    if (port_call_with(&port, 0x4b4270, actor, x, y, pressed, actor, held, ebp) == 1)
    {
        port_call_with(&port, 0x4ac8f0, actor, 0x4483d0, y, pressed, actor, held, ebp);
    }
    eax = port_call_with(&port, 0x476480, 0x54d640, 0x74, y, pressed, actor, held, ebp);
    if (eax != 1)
    {
        return port_return(&port, eax, entry->edx);
    }
    args[0] = ebp - 0x18;
    call_frame(&port, 0x4764a0, 0x54d640, 0x74, ebp - 0x20, ebp - 0x1c, actor, held, ebp, args, 1);
    eax = port_call_with(&port, 0x4b4270, actor, port_u32(&port, ebp, -0x20u),
                         port_u32(&port, ebp, -0x1cu), ebp - 0x1c, actor, held, ebp);
    if (eax != 1)
    {
        return port_return(&port, eax, entry->edx);
    }
    eax = port_call_with(&port, 0x4ac8f0, actor, 0x448610, port_u32(&port, ebp, -0x1cu), ebp - 0x1c,
                         actor, held, ebp);
    return port_return(&port, eax, entry->edx);
}

/* Original 0x4465a0: the slot actor eax for the number 0x532bfc plus its step +0x70 (0x4ac510):
 * at or past 0x532c18 it is dimmed (+0x110 0, +0x48 0, +0x52 13, +0x94 1, 0x4ac4f0 with 0x7f);
 * otherwise the pointer 0x558944 and 0x558946 (0x7d00 each while 0x558958) over it (0x4b0b70)
 * lights it (+0x110 0, +0x48 35, +0x52 9, 0xff000000) or dims it (+0x48 0, +0x52 13, 0x7f) with
 * +0x94 1 (0x4ac4f0); a click of 0x74 (0x476480 on 0x54d640) on it (0x4764a0, 0x4b0b70) is taken
 * (0x476320) and picks the number into 0x532c00 (0x47f2f0 on 0x5bb254); when 0x532c00 is the
 * number the actor takes the state 0x446730 lit (0x4ac4f0 with 0xff000000). */
uint32_t vertrix_port_slot_pick_4465a0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x24
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t actor = entry->eax;
    uint32_t number;
    uint32_t pressed;
    uint32_t light;
    uint32_t ebx;
    uint32_t ecx = actor;
    uint32_t eax;
    uint32_t x;
    uint32_t y;
    uint32_t args[1];
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    number = port_u32(&port, 0, 0x532bfc);
    port_call_with(&port, 0x4ac510, actor, port_u32(&port, actor, 0x70), entry->ebx, actor, actor,
                   number, ebp);
    ebx = port_u32(&port, 0, 0x532c18);
    number += vertrix_lift_edx;
    if (number >= ebx)
    {
        port_set8(&port, actor, 0x110, 0);
        port_set16(&port, actor, 0x48, 0);
        port_set8(&port, actor, 0x52, 0xd);
        port_set8(&port, actor, 0x94, 1);
        eax = port_call_with(&port, 0x4ac4f0, actor, 0x7f, ebx, actor, actor, number, ebp);
        return port_return(&port, eax, entry->edx);
    }
    pressed = port_u32(&port, 0, 0x558958);
    y = sign16(pressed != 0 ? 0x7d00 : port_u16(&port, 0, 0x558946));
    x = sign16(pressed != 0 ? 0x7d00 : port_u16(&port, 0, 0x558944));
    ebx = y;
    eax = port_call_with(&port, 0x4b0b70, actor, x, y, actor, actor, number, ebp);
    if ((eax & 0xff) != 0)
    {
        port_set8(&port, actor, 0x110, 0);
        port_set16(&port, actor, 0x48, 0x23);
        port_set8(&port, actor, 0x52, 9);
        light = 0xff000000u;
    }
    else
    {
        port_set16(&port, actor, 0x48, 0);
        port_set8(&port, actor, 0x52, 0xd);
        port_set8(&port, actor, 0x110, eax);
        light = 0x7f;
    }
    port_set8(&port, actor, 0x94, 1);
    port_call_with(&port, 0x4ac4f0, actor, light, ebx, ecx, actor, number, ebp);
    eax = port_call_with(&port, 0x476480, 0x54d640, 0x74, ebx, ecx, actor, number, ebp);
    if (eax == 1)
    {
        args[0] = ebp - 0x18;
        call_frame(&port, 0x4764a0, 0x54d640, 0x74, ebp - 0x20, ebp - 0x1c, actor, number, ebp,
                   args, 1);
        ebx = sign16(port_u16(&port, ebp, -0x1cu));
        ecx = ebp - 0x1c;
        x = sign16(port_u16(&port, ebp, -0x20u));
        eax = port_call_with(&port, 0x4b0b70, actor, x, ebx, ecx, actor, number, ebp);
        if ((eax & 0xff) != 0)
        {
            port_call_with(&port, 0x476320, 0x54d640, 0x74, ebx, ecx, actor, number, ebp);
            port_set32(&port, 0, 0x532c00, number);
            eax = port_call_with(&port, 0x47f2f0, 0x5bb254, number, ebx, ecx, actor, number, ebp);
        }
    }
    if (number != port_u32(&port, 0, 0x532c00))
    {
        return port_return(&port, eax, entry->edx);
    }
    port_call_with(&port, 0x4ac8f0, actor, 0x446730, ebx, ecx, actor, number, ebp);
    eax = port_call_with(&port, 0x4ac4f0, actor, 0xff000000u, ebx, ecx, actor, number, ebp);
    return port_return(&port, eax, entry->edx);
}
