#include "port_placements.h"

/* The board's cell spawns and placements, the overlay and match effect makers, and the marked
 * pieces' replacements. */

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

static uint32_t sign8(uint32_t value)
{
    return (uint32_t)(int32_t)(int8_t)value;
}

static uint32_t high16(uint32_t value)
{
    return (uint32_t)((int32_t)value >> 16);
}

/* Original 0x429750: the board eax's spawns of its kind +0x15c (none when 0xff): for each of the
 * 28 cells (4 a row, the columns reversed unless +0x160) at the board's place plus the cell size
 * (0x4f9060, 0x4f9064) and spacing (+0x164, +0x168), a cell taken (0x4178d0 not -1) gets an
 * actor (0x15c bytes, 0x4ca000, 0x4abd70; 0x4adf20 with the group 0x544a88) with the board's
 * bytes +0x52, +0x4e, +0x93, +0x94 and +0x95, the owner edx (0x4ac8a0), started (0x4ae140) and
 * told 2 (its method +0). */
uint32_t vertrix_port_board_spawn_cells_429750(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x1c
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t board = entry->eax;
    uint32_t eax = entry->eax;
    uint32_t index;
    uint32_t row;
    uint32_t column;
    uint32_t x;
    uint32_t y;
    uint32_t taken;
    uint32_t actor;
    uint32_t methods;
    uint32_t args[5];
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, -0x18u, entry->edx);
    if (port_u8(&port, board, 0x15c) == 0xff)
    {
        return port_return(&port, eax, entry->edx);
    }
    port_set8(&port, ebp, -0x14u, 0);
    for (;;)
    {
        index = port_u8(&port, ebp, -0x14u);
        if (index >= 0x1c)
        {
            return port_return(&port, eax, index);
        }
        row = index / 4;
        column = index - row * 4;
        if (port_u32(&port, board, 0x160) == 0)
        {
            column = 3 - column;
        }
        x = high16(port_u32(&port, board, 0xc)) +
            column * (port_u32(&port, 0, 0x4f9060) + port_u32(&port, board, 0x164));
        y = high16(port_u32(&port, board, 0x14)) +
            (port_u32(&port, 0, 0x4f9064) + port_u32(&port, board, 0x168)) * row;
        taken = port_call_with(&port, 0x4178d0, port_u8(&port, board, 0x15c), index, y, x, row,
                               board, ebp);
        if (taken == 0xffffffffu)
        {
            eax = taken;
            port_set8(&port, ebp, -0x14u, index + 1);
            continue;
        }
        actor = port_call_with(&port, 0x4ca000, 0x15c, taken, y, x, row, board, ebp);
        if (actor != 0)
        {
            actor = port_call_with(&port, 0x4abd70, actor, vertrix_lift_edx, y, x, row, board, ebp);
        }
        args[0] = 0x544a88;
        args[1] = vertrix_lift_edx;
        args[2] = 0;
        args[3] = 0;
        args[4] = 0;
        call_frame(&port, 0x4adf20, actor, sign16(x), sign16(y), 0, actor, board, ebp, args, 5);
        port_set8(&port, actor, 0x52, port_u8(&port, board, 0x52));
        port_set8(&port, actor, 0x4e, port_u8(&port, board, 0x4e));
        port_set8(&port, actor, 0x93, port_u8(&port, board, 0x93));
        port_set8(&port, actor, 0x94, port_u8(&port, board, 0x94));
        port_set8(&port, actor, 0x95, port_u8(&port, board, 0x95));
        port_call_with(&port, 0x4ac8a0, actor, port_u32(&port, ebp, -0x18u), sign16(y), 0, actor,
                       board, ebp);
        eax = port_call_with(&port, 0x4ae140, actor, vertrix_lift_edx, sign16(y), 0, actor, board,
                             ebp);
        if (actor != 0)
        {
            methods = port_u32(&port, actor, 0x158);
            eax = port_call_with(&port, port_u32(&port, methods, 0), actor, 2, sign16(y), methods,
                                 actor, board, ebp);
        }
        port_set8(&port, ebp, -0x14u, index + 1);
    }
}

/* Original 0x42a200: the board eax's pieces (+0x15c, 4 a row, the columns reversed unless
 * +0x278) placed at the board's place plus the cell size (0x4f9060, 0x4f9064) and spacing
 * (+0x27c, +0x280) (0x4ae110 with the cell size), centred in the cell by their size (0x4b14c0)
 * when known, into +0xe and +0x16. */
uint32_t vertrix_port_board_place_pieces_42a200(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x2c
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t board = entry->eax;
    uint32_t eax = entry->eax & 0xffff00ffu;
    uint32_t index;
    uint32_t row;
    uint32_t column;
    uint32_t across;
    uint32_t piece;
    uint32_t x;
    uint32_t y;
    uint32_t args[1];
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set8(&port, ebp, -0x18u, 0);
    for (;;)
    {
        index = port_u8(&port, ebp, -0x18u);
        if (index >= 0x1c)
        {
            return port_return(&port, eax, entry->edx);
        }
        row = index / 4;
        column = index - row * 4;
        across = port_u32(&port, board, 0x278) == 0 ? 3 - column : column;
        piece = port_u32(&port, board + row * 16 + column * 4, 0x15c);
        if (piece == 0)
        {
            eax = row;
            port_set8(&port, ebp, -0x18u, index + 1);
            continue;
        }
        x = across * (port_u32(&port, 0, 0x4f9060) + port_u32(&port, board, 0x27c)) +
            high16(port_u32(&port, board, 0xc));
        port_set32(&port, ebp, -0x20u, x);
        y = high16(port_u32(&port, board, 0x14)) +
            row * (port_u32(&port, 0, 0x4f9064) + port_u32(&port, board, 0x280));
        port_set32(&port, ebp, -0x1cu, y);
        args[0] = port_u32(&port, 0, 0x4f9064);
        call_frame(&port, 0x4ae110, piece, sign16(x), sign16(y), port_u32(&port, 0, 0x4f9060),
                   piece, board, ebp, args, 1);
        if (port_call_with(&port, 0x4b14c0, piece, ebp - 0x28, ebp - 0x24,
                           port_u32(&port, 0, 0x4f9060), piece, board, ebp) != 0)
        {
            x += (port_u32(&port, 0, 0x4f9060) - port_u32(&port, ebp, -0x28u)) >> 1;
            y += (port_u32(&port, 0, 0x4f9064) - port_u32(&port, ebp, -0x24u)) >> 1;
            port_set32(&port, ebp, -0x20u, x);
            port_set32(&port, ebp, -0x1cu, y);
        }
        port_set16(&port, piece, 0xe, x);
        port_set16(&port, piece, 0x16, y);
        eax = y;
        port_set8(&port, ebp, -0x18u, index + 1);
    }
}

/* The effect actor's start shared by 0x42ff50 and 0x430190: an actor of 0x15c bytes (0x4ca000,
 * 0x4abd70) made at 0 (0x4adf20). */
static uint32_t effect_make(Port *port, const LiftEntry *entry, uint32_t esi, uint32_t edi,
                            uint32_t ebp)
{
    uint32_t actor;
    uint32_t args[5] = {0, 0, 0, 0, 0};
    actor =
        port_call_with(port, 0x4ca000, 0x15c, entry->edx, entry->ebx, entry->ecx, esi, edi, ebp);
    if (actor != 0)
    {
        actor = port_call_with(port, 0x4abd70, actor, vertrix_lift_edx, entry->ebx, entry->ecx, esi,
                               edi, ebp);
    }
    call_frame(port, 0x4adf20, actor, 0, 0, 0, actor, edi, ebp, args, 5);
    return actor;
}

/* The effect's bounds +0xa8 to +0xae (x, x + 0x77, y, y + 0x137), the frame 3 at +0x8e, and
 * 0x4ac710 with 0. */
static void effect_bounds(Port *port, uint32_t actor, uint32_t x, uint32_t y, uint32_t esi,
                          uint32_t edi, uint32_t ebp)
{
    port_set16(port, actor, 0xa8, x);
    port_set16(port, actor, 0xaa, x + 0x77);
    port_set16(port, actor, 0xac, y);
    port_set16(port, actor, 0xae, y + 0x137);
    port_set8(port, actor, 0x8e, 3);
    port_call_with(port, 0x4ac710, actor, 0, 0, 0, esi, edi, ebp);
}

/* Original 0x42ff50: the board eax's overlay: an effect actor with the layer ebx (0x4ac490), the
 * speed of the level 0x532bbc (0x4f7cfc; 0x4ac7b0), the frames 0x544d44 and kind 0x15 (or
 * 0x544d60 and 0x16 when edx) (0x4ac8d0), the board's bounds, at the board's place 0x138 lower,
 * added to the board's list +0xce4 (0x4123d0) and kept at +0xce0. The board. */
uint32_t vertrix_port_board_create_overlay_42ff50(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x2c
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t board = entry->eax;
    uint32_t x;
    uint32_t y;
    uint32_t actor;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    x = high16(port_u32(&port, board, 0xc));
    y = high16(port_u32(&port, board, 0x14));
    port_set32(&port, ebp, -0x10u, board);
    port_set32(&port, ebp, -0x24u, entry->edx);
    port_set32(&port, ebp, -0x1cu, entry->ebx);
    port_set32(&port, ebp, -0x14u, x);
    port_set32(&port, ebp, -0x28u, x + 0x77);
    port_set32(&port, ebp, -0x18u, y);
    port_set32(&port, ebp, -0x20u, y + 0x137);
    actor = effect_make(&port, entry, entry->esi, entry->edi, ebp);
    port_call_with(&port, 0x4ac490, actor, entry->ebx, 0, 0, actor, entry->edi, ebp);
    port_call_with(&port, 0x4ac7b0, actor,
                   port_u32(&port, 0, 0x4f7cfc + port_u32(&port, 0, 0x532bbc) * 4), 0, 0, actor,
                   entry->edi, ebp);
    port_call_with(&port, 0x4ac8d0, actor, entry->edx == 0 ? 0x544d44 : 0x544d60, 0, 0, actor,
                   actor, ebp);
    port_set32(&port, actor, 0, entry->edx == 0 ? 0x15 : 0x16);
    effect_bounds(&port, actor, x, y, actor, actor, ebp);
    port_set16(&port, actor, 0xe, port_u16(&port, board, 0xe));
    port_set16(&port, actor, 0x16, port_u16(&port, board, 0x16) + 0x138);
    port_call_with(&port, 0x4123d0, port_u32(&port, board, 0xce4), 0, actor, 0, actor, actor, ebp);
    port_set32(&port, board, 0xce0, actor);
    return port_return(&port, board, vertrix_lift_edx);
}

/* Original 0x430190: the match effect of the board eax at the cell edx, ebx (24 pixels, 3 to
 * the upper left): an effect actor with the layer 4 (0x4ac470), speed 1 (0x4ac7b0), frames
 * 0x544d28 (0x4ac8d0), the board's bounds, +0x94, +0x95 and +0x93 set, +0x48 30 and +0x4e 90.
 * The actor. */
uint32_t vertrix_port_actor_spawn_match_effect_430190(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x28
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t board = entry->eax;
    uint32_t x;
    uint32_t y;
    uint32_t actor;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    x = high16(port_u32(&port, board, 0xc));
    y = high16(port_u32(&port, board, 0x14));
    port_set32(&port, ebp, -0x14u, entry->edx);
    port_set32(&port, ebp, -0x10u, entry->ebx);
    port_set32(&port, ebp, -0x18u, x);
    port_set32(&port, ebp, -0x24u, x + 0x77);
    port_set32(&port, ebp, -0x20u, y);
    port_set32(&port, ebp, -0x1cu, y + 0x137);
    actor = effect_make(&port, entry, entry->esi, board, ebp);
    port_call_with(&port, 0x4ac470, actor, 4, 0, 0, actor, board, ebp);
    port_call_with(&port, 0x4ac7b0, actor, 1, 0, 0, actor, board, ebp);
    port_call_with(&port, 0x4ac8d0, actor, 0x544d28, 0, 0, actor, board, ebp);
    effect_bounds(&port, actor, x, y, actor, board, ebp);
    port_set8(&port, actor, 0x94, 1);
    port_set8(&port, actor, 0x95, 1);
    port_set16(&port, actor, 0x48, 0x1e);
    port_set8(&port, actor, 0x4e, 0x5a);
    port_set8(&port, actor, 0x93, 1);
    port_set16(&port, actor, 0xe, entry->edx * 0x18 + port_u16(&port, board, 0xe) - 3);
    port_set16(&port, actor, 0x16, entry->ebx * 0x18 + port_u16(&port, board, 0x16) - 3);
    return port_return(&port, actor, vertrix_lift_edx);
}

/* The replacement's finish shared by 0x436720, 0x4368e0 and 0x437350: the new piece takes the
 * old one's layer +0xd0 (0x4ac490) unless `layer_one` (then the old one takes layer 1,
 * 0x4ac470), the speed 5 (0x4ac7b0) and the old one's frame +0xb8 (0x4ac710). */
static void replace_start(Port *port, uint32_t made, uint32_t old, int layer_one, uint32_t ebx,
                          uint32_t ecx, uint32_t esi, uint32_t edi, uint32_t ebp)
{
    if (layer_one)
    {
        port_call_with(port, 0x4ac470, made, 1, ebx, ecx, esi, edi, ebp);
    }
    else
    {
        port_call_with(port, 0x4ac490, made, port_u32(port, old, 0xd0), ebx, ecx, esi, edi, ebp);
    }
    port_call_with(port, 0x4ac7b0, made, 5, ebx, ecx, esi, edi, ebp);
    port_call_with(port, 0x4ac710, made, port_u32(port, old, 0xb8), ebx, ecx, esi, edi, ebp);
}

/* Original 0x436720: the board eax's marked pieces (0x436030, each the first found by 0x4360b0)
 * replaced by new ones of the kind edx (0x430800): the cell marked 2 at +0xb94, the old piece
 * moved to +0x87c fading (0x44d480, speed 5, +0x4e 100, +0x44 16) and ending at 0x44d5f0, the
 * new one in its place with the old one's layer, speed 5 and frame, its state set (0x4ac8f0)
 * and +0x44 cleared. 1, or 0 with none marked. */
uint32_t vertrix_port_board_replace_marked_436720(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x24
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t board = entry->eax;
    uint32_t kind = entry->edx;
    uint32_t count;
    uint32_t done;
    uint32_t row;
    uint32_t column;
    uint32_t slot;
    uint32_t old;
    uint32_t made;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, -0x14u, kind);
    count = port_call_with(&port, 0x436030, board, kind, entry->ebx, entry->ecx, entry->esi,
                           entry->edi, ebp);
    port_set32(&port, ebp, -0x18u, count);
    if (count == 0)
    {
        return port_return(&port, 0, vertrix_lift_edx);
    }
    for (done = 0; done < count;)
    {
        port_call_with(&port, 0x4360b0, board, 0, ebp - 0x20, ebp - 0x1c, board, done, ebp);
        row = port_u32(&port, ebp, -0x20u);
        column = port_u32(&port, ebp, -0x1cu);
        port_set8(&port, board + row * 0xd + column, 0xb94, 2);
        slot = board + row * 0x34 + column * 4;
        old = port_u32(&port, slot, 0x220);
        port_set32(&port, slot, 0x87c, old);
        port_set32(&port, slot, 0x220, 0);
        port_call_with(&port, 0x4ac8f0, old, 0x44d480, ebp - 0x20, old, board, done, ebp);
        port_set8(&port, old, 0x4e, 0x64);
        port_call_with(&port, 0x4ac7b0, old, 5, ebp - 0x20, old, board, done, ebp);
        port_set8(&port, old, 0x44, 0x10);
        made = port_call_with(&port, 0x430800, board, kind, ebp - 0x20, old, board, done, ebp);
        port_set32(&port, slot, 0x220, made);
        replace_start(&port, made, old, 0, made, old, board, done, ebp);
        port_call_with(&port, 0x4ac510, made, vertrix_lift_edx, made, old, board, done, ebp);
        port_call_with(&port, 0x4ac380, made, vertrix_lift_edx, made, old, board, done, ebp);
        ++done;
        port_call_with(&port, 0x4ac510, old, vertrix_lift_edx, made, old, board, done, ebp);
        port_call_with(&port, 0x4ac380, old, 0x44d5f0, made, old, board, done, ebp);
        port_call_with(&port, 0x4ac8f0, made, vertrix_lift_edx, made, count, board, done, ebp);
        port_set8(&port, made, 0x44, 0);
    }
    return port_return(&port, 1, vertrix_lift_edx);
}

/* Original 0x4368e0: the piece eax's three children (+0xa60 +0x15c) replaced by new ones of the
 * kinds edx, ebx and ecx (0x430800): the old child kept at +0x170 fading (0x44f7e0, speed 5,
 * +0x4e 100) and ending at 0x44f880, the new one with layer 1 in its place. */
uint32_t vertrix_port_piece_replace_children_4368e0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x1c
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t piece = entry->eax;
    uint32_t kinds[3];
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t index;
    uint32_t offset;
    uint32_t children;
    uint32_t child;
    uint32_t made;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    kinds[0] = entry->edx;
    kinds[1] = entry->ebx;
    kinds[2] = entry->ecx;
    port_set32(&port, ebp, -0x10u, entry->edx);
    port_set32(&port, ebp, -0x14u, entry->ebx);
    port_set32(&port, ebp, -0x18u, entry->ecx);
    port_set32(&port, ebp, -0xcu, 0);
    for (index = 0; index < 3; ++index)
    {
        offset = port_u32(&port, ebp, -0xcu);
        children = port_u32(&port, piece, 0xa60) + offset;
        child = port_u32(&port, children, 0x15c);
        port_set32(&port, children, 0x170, child);
        edx = offset;
        eax = port_u32(&port, piece, 0xa60) + offset;
        port_set32(&port, eax, 0x15c, 0);
        if (child != 0)
        {
            port_call_with(&port, 0x4ac8f0, child, 0x44f7e0, kinds[index], child, index, piece,
                           ebp);
            port_set8(&port, child, 0x4e, 0x64);
            port_call_with(&port, 0x4ac7b0, child, 5, kinds[index], child, index, piece, ebp);
            made = port_call_with(&port, 0x430800, piece, kinds[index], kinds[index], child, index,
                                  piece, ebp);
            port_set32(&port, port_u32(&port, piece, 0xa60) + port_u32(&port, ebp, -0xcu), 0x15c,
                       made);
            port_call_with(&port, 0x4ac490, made, port_u32(&port, child, 0xd0), made, child, index,
                           piece, ebp);
            port_call_with(&port, 0x4ac470, child, 1, made, child, index, piece, ebp);
            port_call_with(&port, 0x4ac7b0, made, 5, made, child, index, piece, ebp);
            port_call_with(&port, 0x4ac710, made, port_u32(&port, child, 0xb8), made, child, index,
                           piece, ebp);
            port_call_with(&port, 0x4ac510, made, vertrix_lift_edx, made, child, index, piece, ebp);
            port_call_with(&port, 0x4ac380, made, vertrix_lift_edx, made, child, index, piece, ebp);
            port_call_with(&port, 0x4ac510, child, vertrix_lift_edx, made, child, index, piece,
                           ebp);
            port_call_with(&port, 0x4ac380, child, 0x44f880, made, child, index, piece, ebp);
            eax = port_call_with(&port, 0x4ac8f0, made, vertrix_lift_edx, made, child, index, piece,
                                 ebp);
            edx = vertrix_lift_edx;
        }
        port_set32(&port, ebp, -0xcu, offset + 4);
    }
    return port_return(&port, eax, edx);
}

/* Original 0x437350: the board eax's marked pieces (0x436030, the n-th by 0x4360b0) mirrored: the
 * piece fades (0x44d8b0, speed 5, +0x4e 100, +0x93 set) and ends at 0x44da70, a new piece of its
 * kind +0x15c (0x430800) at +0x87c with layer 1, speed 5 and its frame, +0x4e and +0x44 cleared,
 * +0x93 set. 1, or 0 with none marked. */
uint32_t vertrix_port_board_mirror_marked_437350(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x28
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t board = entry->eax;
    uint32_t count;
    uint32_t done;
    uint32_t row;
    uint32_t piece;
    uint32_t made;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    count = port_call_with(&port, 0x436030, board, entry->edx, entry->ebx, entry->ecx, entry->esi,
                           entry->edi, ebp);
    port_set32(&port, ebp, -0x18u, count);
    if (count == 0)
    {
        return port_return(&port, 0, entry->edx);
    }
    for (done = 0; done < count;)
    {
        port_call_with(&port, 0x4360b0, board, done, ebp - 0x24, ebp - 0x20, board, done, ebp);
        row = board + port_u32(&port, ebp, -0x24u) * 0x34;
        piece = port_u32(&port, row + port_u32(&port, ebp, -0x20u) * 4, 0x220);
        port_call_with(&port, 0x4ac8f0, piece, 0x44d8b0, piece, ebp - 0x20, board, done, ebp);
        port_set8(&port, piece, 0x4e, 0x64);
        port_call_with(&port, 0x4ac7b0, piece, 5, piece, ebp - 0x20, board, done, ebp);
        port_set8(&port, piece, 0x93, 1);
        port_set8(&port, piece, 0x4e, 0x64);
        made = port_call_with(&port, 0x430800, board, sign8(port_u8(&port, piece, 0x15c)), piece,
                              ebp - 0x20, board, done, ebp);
        port_set32(&port, ebp, -0x1cu, row);
        port_set32(&port, row + port_u32(&port, ebp, -0x20u) * 4, 0x87c, made);
        replace_start(&port, made, piece, 1, piece, made, board, done, ebp);
        port_set8(&port, made, 0x4e, 0);
        port_set8(&port, made, 0x93, 1);
        port_set8(&port, made, 0x44, 0);
        port_call_with(&port, 0x4ac510, made, vertrix_lift_edx, piece, made, board, done, ebp);
        port_call_with(&port, 0x4ac380, made, vertrix_lift_edx, piece, made, board, done, ebp);
        ++done;
        port_call_with(&port, 0x4ac510, piece, vertrix_lift_edx, piece, made, board, done, ebp);
        port_call_with(&port, 0x4ac380, piece, 0x44da70, piece, made, board, done, ebp);
        port_call_with(&port, 0x4ac8f0, made, vertrix_lift_edx, piece, count, board, done, ebp);
    }
    return port_return(&port, 1, entry->edx);
}
