#include "rtlaiboardjudges.h"

enum
{
    /* The frame below the return slot: the boards' copies at ebp-0x94 and ebp-0xd8 (the original
     * frame's floor, BELOW from entry->esp), and the scores 0x4288d0 fills at ebp-0x50. */
    BELOW = 0xdc,
    OWN_CELLS = 0x94,
    RIVAL_CELLS = 0xd8,
    SCORES = 0x50,

    /* The player's rival (+0x3b0), board (+0x15c) and its column, rows and height (+0x178,
     * +0x17c, +0x180). A board's cells (+0x1de, 0x41 bytes). */
    PLAYER_RIVAL = 0x3b0,
    PLAYER_BOARD = 0x15c,
    PLAYER_COLUMN = 0x178,
    PLAYER_ROW = 0x17c,
    PLAYER_HEIGHT = 0x180,
    HEIGHT_MARGIN = 0xc,
    BOARD_CELLS = 0x1de,
    CELL_COUNT = 0x41,

    /* The judge's grades (+0x1c5), ratings (+0x1f4), kind (+0x160) and level (+0x164). */
    JUDGE_GRADES = 0x1c5,
    JUDGE_RATINGS = 0x1f4,
    JUDGE_KIND = 0x160,
    JUDGE_LEVEL = 0x164,

    BOARD_SLOTS = 0x432820,
    COMPARE_BOARDS = 0x428110,
    FEATURES = 0x427c10,
    RATE_MOVES = 0x4288d0
};

/* Original 0x4279b0 (eax = the AI's judge, edx = its player): whether the player should answer
 * now. Both boards' slots are brought up to date (0x432820, the player's and its rival's, +0x3b0),
 * their 0x41 cells copied into the frame and compared (0x428110, the grades at +0x1c5), the
 * features taken (0x427c10: the rival's and the player's column, the heights less 12, the judge's
 * level and grades) and the moves rated (0x4288d0, into the ratings at +0x1f4 and the scores in
 * the frame). 1 when the first score, a signed byte, is over 1, else 0. Called from 0x43ab60 for
 * the bonus effect 0x452e00; the two copies are `f2 a5` / `f2 a4` in the original (a repeated
 * movsd and movsb). */
uint32_t vertrix_port_ai_board_judge_4279b0(PORT_SIGNATURE)
{
    uint8_t stack[BELOW + 8];
    Port port;
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    const uint32_t frame = entry->esp - 4;
    const uint32_t judge = entry->eax;
    const uint32_t player = entry->edx;
    const uint32_t rival = port_u32(&port, player, PLAYER_RIVAL);
    const uint32_t own_board = port_u32(&port, player, PLAYER_BOARD);
    const uint32_t rival_board = port_u32(&port, rival, PLAYER_BOARD);
    const uint32_t grades = judge + JUDGE_GRADES;

    port_call(&port, BOARD_SLOTS, own_board, 0, 0, 0);
    port_call(&port, BOARD_SLOTS, rival_board, 0, 0, 0);
    port_copy(&port, frame - OWN_CELLS, own_board + BOARD_CELLS, CELL_COUNT);
    port_copy(&port, frame - RIVAL_CELLS, rival_board + BOARD_CELLS, CELL_COUNT);
    port_call(&port, COMPARE_BOARDS, judge, frame - OWN_CELLS, frame - RIVAL_CELLS, grades);

    const uint32_t features[5] = {
        port_u32(&port, rival, PLAYER_COLUMN),
        port_u32(&port, player, PLAYER_HEIGHT) - HEIGHT_MARGIN,
        port_u32(&port, rival, PLAYER_HEIGHT) - HEIGHT_MARGIN,
        port_u32(&port, judge, JUDGE_LEVEL),
        grades,
    };
    port_call_stack(&port, FEATURES, judge, port_u32(&port, player, PLAYER_ROW),
                    port_u32(&port, rival, PLAYER_ROW), port_u32(&port, player, PLAYER_COLUMN),
                    features, 5);

    const uint32_t rating[2] = {frame - SCORES, port_u32(&port, judge, JUDGE_KIND)};
    port_call_stack(&port, RATE_MOVES, judge, player, judge + JUDGE_RATINGS, grades, rating, 2);

    const int32_t first = (int8_t)port_u8(&port, frame - SCORES, 0);
    return port_return(&port, first > 1, entry->edx);
}
