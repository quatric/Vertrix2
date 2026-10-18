#include "rtlboardmatches.h"

/* Resolves the matches on a player's board after a piece locks: snapshots the cell kinds, runs the
 * figure pass (0x434ee0) and the line pass (0x4346b0) into the match mask, marks the cells whose
 * extra actors are out, then clears every matched cell and starts its effect. */

enum
{
    /* The routine's frame under its return slot; only the figure count is reached by address. */
    BELOW = 0x6c,
    FIGURE_COUNT = 0x14,

    ARGUMENT_MATCHED = 4,
    ARGUMENT_FIGURE = 8,
    ARGUMENTS = 2,

    COLUMNS = 5,
    ROWS_PER_COLUMN = 13,
    BOARD_CELLS = COLUMNS * ROWS_PER_COLUMN,
    /* The player's cell kinds (a byte each), cell actors (a dword each) and the four extra actors
     * of each cell (0x10 bytes a cell), all column by column. */
    PLAYER_KINDS = 0x1de,
    PLAYER_CELLS = 0x220,
    PLAYER_EXTRAS = 0x324,
    EXTRAS_PER_CELL = 4,
    PLAYER_BURSTS = 0xbdc,
    BOMB_KIND = 7,

    ACTOR_KIND = 0x15c,
    ACTOR_CLEARED = 0x15d,

    /* The kind snapshot the line pass reads and the match mask (5 columns of 13 dwords). */
    KINDS_COPY = 0x5407b8,
    MATCH_MASK = 0x5406b0,
    MATCH_STYLE = 0x532a70,
    MATCH_HANDLERS = 0x4fb7b0,

    TAKE_KINDS = 0x4327e0,
    CLEAR_MASK = 0x432840,
    FIGURE_PASS = 0x434ee0,
    LINE_PASS = 0x4346b0,
    ACTOR_SHOW = 0x4ac7b0,
    ACTOR_ANIMATE = 0x4ac8f0,
    BOMB_BURST = 0x430190,
    BOMB_BLAST = 0x4302a0,
    EXTRA_FADE = 0x4504e0,
    BURST_ANIMATION = 0x450450,
    CELL_FADE = 0x450330
};

/* An actor shown (0x4ac7b0 with 1), marked cleared and set to animate with the routine given. */
static void clear_actor(Port *port, uint32_t slot, uint32_t animation)
{
    port_call(port, ACTOR_SHOW, port_u32(port, slot, 0), 1, 0, 0);
    port_set8(port, port_u32(port, slot, 0), ACTOR_CLEARED, 1);
    port_call(port, ACTOR_ANIMATE, port_u32(port, slot, 0), animation, 0, 0);
}

/* Original 0x432480 (eax = the player, edx = where the count of cleared cells goes, ebx = where
 * the figure count goes, cl = the level both passes get; stack: where the matched flag and the
 * figure flag go; ret 8). Returns 1 when anything was matched, else 0.
 *
 * Both flags are 1 when the figure pass matches, the matched flag alone when the line pass does.
 * A cell with extra actors out (+0x324) is marked in the mask when it holds an actor, and its four
 * extras are cleared and faded (0x4504e0) without a check for empty slots after the first. Then,
 * when anything was matched or an extra was out, the figure count is stored and each marked cell
 * with an actor is cleared: a bomb (kind 7) gets a burst (0x430190, kept at +0xbdc) and its blast
 * (0x4302a0); any other kind goes to the handler of the current match style (0x532a70, table
 * 0x4fb7b0), which gets the column in edx and the row in ebx and ecx. The original reloads each
 * actor from its slot after every call, as the port does. */
uint32_t vertrix_port_board_match_resolve_432480(PORT_SIGNATURE)
{
    uint8_t stack[BELOW + 8 + 4 * ARGUMENTS];
    Port port;
    port_open_arguments(&port, stack, calls, services, globals, entry, BELOW, ARGUMENTS);
    const uint32_t figure_count = entry->esp - 4 - FIGURE_COUNT;
    const uint32_t player = entry->eax;
    const uint32_t cleared = entry->edx;
    const uint32_t figures = entry->ebx;
    const uint32_t level = entry->ecx & 0xff;
    const uint32_t matched_flag = port_u32(&port, entry->esp, ARGUMENT_MATCHED);
    const uint32_t figure_flag = port_u32(&port, entry->esp, ARGUMENT_FIGURE);
    uint32_t result = 0;

    port_set32(&port, figure_count, 0, 0);
    port_set32(&port, cleared, 0, 0);
    port_set32(&port, figures, 0, 0);
    port_call(&port, TAKE_KINDS, player + PLAYER_CELLS, player + PLAYER_KINDS, BOARD_CELLS, 0);
    port_copy(&port, KINDS_COPY, player + PLAYER_KINDS, BOARD_CELLS);
    port_call(&port, CLEAR_MASK, MATCH_MASK, 0, 0, 0);
    port_set32(&port, matched_flag, 0, 0);
    port_set32(&port, figure_flag, 0, 0);
    if (port_call_stack(&port, FIGURE_PASS, player + PLAYER_KINDS, MATCH_MASK, 0, 1, &figure_count,
                        1) == 1)
    {
        port_set32(&port, matched_flag, 0, 1);
        result = 1;
        port_set32(&port, figure_flag, 0, 1);
    }
    if (port_call(&port, LINE_PASS, KINDS_COPY, MATCH_MASK, level, figure_count) == 1)
    {
        result = 1;
        port_set32(&port, matched_flag, 0, 1);
    }

    int extras_out = 0;
    for (uint32_t x = 0; x < COLUMNS && !port.env.failed; x++)
    {
        for (uint32_t y = 0; y < ROWS_PER_COLUMN && !port.env.failed; y++)
        {
            const uint32_t extras = player + x * ROWS_PER_COLUMN * 0x10 + y * 0x10 + PLAYER_EXTRAS;
            const uint32_t cell = x * ROWS_PER_COLUMN * 4 + y * 4;
            if (port_u32(&port, extras, 0) == 0)
            {
                continue;
            }
            if (port_u32(&port, player + cell, PLAYER_CELLS) != 0)
            {
                port_set32(&port, MATCH_MASK + cell, 0, 1);
            }
            extras_out = 1;
            for (uint32_t k = 0; k < EXTRAS_PER_CELL && !port.env.failed; k++)
            {
                clear_actor(&port, extras + k * 4, EXTRA_FADE);
            }
        }
    }
    if (extras_out)
    {
        result = 1;
    }
    else if (result != 1)
    {
        return port_return(&port, result, 0);
    }

    port_set32(&port, figures, 0, port_u16(&port, figure_count, 0));
    for (uint32_t x = 0; x < COLUMNS && !port.env.failed; x++)
    {
        for (uint32_t y = 0; y < ROWS_PER_COLUMN && !port.env.failed; y++)
        {
            const uint32_t cell = x * ROWS_PER_COLUMN * 4 + y * 4;
            const uint32_t slot = player + cell + PLAYER_CELLS;
            const uint32_t kind = player + x * ROWS_PER_COLUMN + y + PLAYER_KINDS;
            if (port_u32(&port, slot, 0) == 0 || port_u32(&port, MATCH_MASK + cell, 0) != 1)
            {
                continue;
            }
            port_set32(&port, cleared, 0, port_u32(&port, cleared, 0) + 1);
            port_call(&port, ACTOR_SHOW, port_u32(&port, slot, 0), 1, 0, 0);
            port_set8(&port, port_u32(&port, slot, 0), ACTOR_CLEARED, 1);
            port_set8(&port, port_u32(&port, slot, 0), ACTOR_KIND, port_u8(&port, kind, 0));
            if (port_u8(&port, kind, 0) == BOMB_KIND)
            {
                const uint32_t burst = port_call(&port, BOMB_BURST, player, x, y, 0);
                port_set32(&port, player + cell, PLAYER_BURSTS, burst);
                port_call(&port, ACTOR_ANIMATE, burst, BURST_ANIMATION, 0, 0);
                port_call(&port, BOMB_BLAST, player, x, y, 0);
            }
            else
            {
                const uint32_t style = port_u32(&port, MATCH_STYLE, 0);
                port_call(&port, port_u32(&port, MATCH_HANDLERS + style * 4, 0), player, x, y, y);
            }
            port_call(&port, ACTOR_ANIMATE, port_u32(&port, slot, 0), CELL_FADE, 0, 0);
        }
    }
    return port_return(&port, result, 0);
}
