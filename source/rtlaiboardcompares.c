#include "rtlaiboardcompares.h"

/* The computer player's look at both boards before it picks a move. */

enum
{
    /* The routine's frame under its return slot: its callees fill and read these locals by
     * address. */
    BELOW = 0x14c,
    CHOICES = 0x148,
    OPPONENT_CELLS = 0xd8,
    PLAYER_CELLS = 0x94,
    RESULT = 0x50,

    BOARD_CELLS = 0x1de,
    BOARD_CELL_BYTES = 0x41,

    PLAYER_BOARD = 0x15c,
    PLAYER_SPEED_X = 0x178,
    PLAYER_SPEED_Y = 0x17c,
    PLAYER_POSITION = 0x180,
    PLAYER_OPPONENT = 0x3b0,
    PLAYER_CHOICE_GRID = 0x3b8,
    /* The position is kept 12 ahead of the one passed on. */
    POSITION_BIAS = 0xc,

    AI_DEPTH = 0x160,
    AI_LEVEL = 0x164,
    AI_MODE = 0x1c5,
    AI_SEARCH = 0x1f4,
    AI_BEST = 0x210,

    BOARD_SETTLE = 0x432820,
    CHOICE_GRID_READ = 0x429e80,
    MODE_SET = 0x427e10,
    BOARDS_COMPARE = 0x428110,
    MOTION_SET = 0x427c10,
    SEARCH = 0x4288d0,
    CHOOSE = 0x428e70
};

/* Original 0x427850 (eax = the computer player's state, edx = its player): brings both boards up
 * to date (0x432820), copies their cells into the frame, reads the choice grid (0x429e80), sets
 * the mode (0x427e10), compares the boards (0x428110), passes on both players' speeds and
 * positions (0x427c10), searches (0x4288d0) and chooses (0x428e70), returning what the choice
 * returns. */
uint32_t vertrix_port_ai_compare_player_boards_427850(PORT_SIGNATURE)
{
    uint8_t stack[BELOW + 8];
    Port port;
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    const uint32_t frame = entry->esp - 4;
    const uint32_t choices = frame - CHOICES;
    const uint32_t opponent_cells = frame - OPPONENT_CELLS;
    const uint32_t player_cells = frame - PLAYER_CELLS;
    const uint32_t ai = entry->eax;
    const uint32_t player = entry->edx;
    const uint32_t mode = ai + AI_MODE;
    const uint32_t search = ai + AI_SEARCH;

    const uint32_t opponent = port_u32(&port, player, PLAYER_OPPONENT);
    const uint32_t player_board = port_u32(&port, player, PLAYER_BOARD);
    const uint32_t opponent_board = port_u32(&port, opponent, PLAYER_BOARD);
    port_call(&port, BOARD_SETTLE, player_board, 0, 0, 0);
    port_call(&port, BOARD_SETTLE, opponent_board, 0, 0, 0);
    port_copy(&port, player_cells, player_board + BOARD_CELLS, BOARD_CELL_BYTES);
    port_copy(&port, opponent_cells, opponent_board + BOARD_CELLS, BOARD_CELL_BYTES);

    port_call(&port, CHOICE_GRID_READ, port_u32(&port, player, PLAYER_CHOICE_GRID), choices, 0, 0);
    port_call(&port, MODE_SET, ai, player, mode, 0);
    port_call(&port, BOARDS_COMPARE, ai, player_cells, opponent_cells, mode);

    const uint32_t motion[5] = {
        port_u32(&port, opponent, PLAYER_SPEED_X),
        port_u32(&port, player, PLAYER_POSITION) - POSITION_BIAS,
        port_u32(&port, opponent, PLAYER_POSITION) - POSITION_BIAS,
        port_u32(&port, ai, AI_LEVEL),
        mode,
    };
    port_call_stack(&port, MOTION_SET, ai, port_u32(&port, player, PLAYER_SPEED_Y),
                    port_u32(&port, opponent, PLAYER_SPEED_Y),
                    port_u32(&port, player, PLAYER_SPEED_X), motion, 5);

    const uint32_t search_arguments[2] = {frame - RESULT, port_u32(&port, ai, AI_DEPTH)};
    port_call_stack(&port, SEARCH, ai, player, search, mode, search_arguments, 2);

    const uint32_t depth = port_u32(&port, ai, AI_DEPTH);
    const uint32_t result =
        port_call_stack(&port, CHOOSE, ai, search, ai + AI_BEST, choices, &depth, 1);
    return port_return(&port, result, 0);
}
