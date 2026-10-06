#ifndef VERTRIX_AI_PLAYER_H
#define VERTRIX_AI_PLAYER_H
#include "ai_features.h"
#include "game.h"
#include <stdint.h>

/* The computer player's figure search, original 0x4270a0 with its scoring call 0x434ee0 done
 * natively (vertrix_figure_pass): board is the player's 5 columns of 13 cells (0xff empty),
 * a, b and c the colours of the falling piece (the original's ecx, edx and ebx), start the
 * column and row it is in (0..5, 0..12) and level the player's level. Returns 0 for a level of
 * two or less or an invalid start. Otherwise every reachable column that is not full is tried
 * with the three rotations (a, c, b from the bottom up; then b, a, c; then c, b, a) and scored
 * by the figure reward; when any rotation formed a figure, *column is the column of the best
 * score (the first of equals) and *rotation the rotation that scored best there, and 1 is
 * returned; otherwise 0. */
int vertrix_ai_search_native(const uint8_t board[VERTRIX_REACH_COLUMNS * VERTRIX_BOARD_ROWS],
                             uint32_t a, uint32_t b, uint32_t c, uint32_t start, uint32_t row,
                             uint32_t level, uint32_t *column, uint32_t *rotation);

/* The computer player's random draws (original 0x4826c0 on the table at 0x598d48): a value
 * below the divisor. */
typedef uint16_t (*VertrixAiRandom)(void *context, uint16_t divisor);

/* Original 0x426240, the computer player's last resort when no figure can be made. p0, p1 and p2
 * are the original's edx, ebx and ecx (the colours b, c and a), level the player's level and
 * start and row as for the figure search. *previous is the column chosen the last time
 * (object + 0x180). The column is the reachable one whose stack is lowest (ties from the two
 * outer sides inwards, kept or drawn at random), column 2 when none is; the rotation comes from
 * equal colours in the piece, then, from the third level, from the neighbouring columns' cells
 * beside the landing cell, and finally from a draw of three. Returns 0 for an invalid start or
 * row, leaving the outputs unchanged. */
int vertrix_ai_fallback(const uint8_t board[VERTRIX_REACH_COLUMNS * VERTRIX_BOARD_ROWS],
                        uint32_t p0, uint32_t p1, uint32_t p2, uint32_t start, uint32_t row,
                        uint32_t level, uint32_t *previous, VertrixAiRandom random, void *context,
                        uint32_t *column, uint32_t *rotation);

/* Original 0x4269e0, the computer player's chain search: board is the player's 5 columns of 13
 * cells (0xff empty), p0, p1 and p2 the original's edx, ebx and ecx, threshold the run length
 * the line pass needs, start/row/level as for the figure search. Every reachable column that is
 * not full is tried with the piece's three rotations; a rotation that makes runs scores the
 * number of marked cells (kept per column when it beats the earlier one). From level 3 the best
 * rotation is replayed: its runs are removed and the board collapsed to score the follow-up runs
 * (second), and at level 4 the chain is followed to the end (third; the mask is not cleared
 * between those rounds, as in the original). Returns 1 and the chosen column and rotation when
 * any rotation made runs, otherwise 0 with the outputs unchanged (also for an invalid start). */
int vertrix_ai_chain_search(const uint8_t board[VERTRIX_REACH_COLUMNS * VERTRIX_BOARD_ROWS],
                            uint32_t p0, uint32_t p1, uint32_t p2, uint32_t threshold,
                            uint32_t start, uint32_t row, uint32_t level, uint32_t *column,
                            uint32_t *rotation);

/* Original 0x427380, the computer player's bomb search (only for pieces holding a bomb, kind 6,
 * from level 2 on): p0, p1 and p2 as for the other searches, pattern the bomb pattern and mode
 * the original's last argument. With mode 0x23 the placement that puts the fewest cells inside
 * the blast (0x4344e0) wins, the first of equals, and the answer is always 1. Otherwise, for the
 * vertical patterns 2 and 3 a centre column higher than eight cells with no bomb in it is taken
 * at once (column 2, rotation 0); else the placement with the best estimate wins, the first of
 * equals: blasted cells, plus twice the blasted stones from level 3 (0x434300). Returns 0 and
 * leaves the outputs for a level below 2 or without a bomb in the piece. */
int vertrix_ai_bomb_search(const uint8_t board[VERTRIX_REACH_COLUMNS * VERTRIX_BOARD_ROWS],
                           uint32_t p0, uint32_t p1, uint32_t p2, uint32_t start, uint32_t row,
                           uint32_t level, int32_t pattern, uint32_t mode, uint32_t *column,
                           uint32_t *rotation);

/* The computer player's planner, original 0x425f60: the piece's colours c1, c2 and c3 (the
 * original's ebx, ecx and stack argument), its start column and row (0x431b20), the AI level,
 * the player's run threshold (+0x4dc), bomb pattern (+0x4cd) and bomb mode (+0x4c8). The searches
 * run in the original's order until one answers: the bomb search (only with a bomb pattern), the
 * figure search, the chain search and the fallback. *column and *rotation are the target the
 * steering aims for; returns the answer of the search that was used. Read from the executable,
 * not run as a whole in the oracle (each search is). */
typedef struct
{
    uint32_t level;
    uint32_t threshold;
    int32_t pattern;
    uint32_t mode;
} VertrixAiSettings;

int vertrix_ai_plan(const uint8_t board[VERTRIX_REACH_COLUMNS * VERTRIX_BOARD_ROWS], uint32_t c1,
                    uint32_t c2, uint32_t c3, uint32_t start, uint32_t row,
                    const VertrixAiSettings *settings, uint32_t *previous, VertrixAiRandom random,
                    void *context, uint32_t *column, uint32_t *rotation);

/* The keys the computer player presses in one steering tick (original 0x43ae20..0x43b194): left
 * and right move the piece a column, permute rotates it once, drop starts the fast drop. */
typedef struct
{
    uint8_t left;
    uint8_t right;
    uint8_t permute;
    uint8_t drop;
} VertrixAiKeys;

/* One steering tick: current is the piece's column (0x431b20), target and *rotations_left the
 * plan, dropping whether the fast drop is already on (0x431380). Level 4 moves and rotates in the
 * same tick and drops when it started on the target column with no rotation left; level 3 does
 * one thing per tick, moving first; every other level rotates first, then moves, then drops. */
void vertrix_ai_steer(uint32_t level, int32_t current, int32_t target, uint32_t *rotations_left,
                      int dropping, VertrixAiKeys *keys);

#endif
