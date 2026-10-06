#ifndef VERTRIX_AI_SCORING_H
#define VERTRIX_AI_SCORING_H
#include <stdint.h>
/* Computer-player scoring over two boards of 5 columns of 13 cells (0xff empty, 5 stone, 6 bomb)
 * and over a record list. */
#define VERTRIX_SCORE_COLUMNS 5
#define VERTRIX_SCORE_ROWS 13
#define VERTRIX_SCORE_CELLS 65
#define VERTRIX_COMPARE_SIZE 0x13

/* Original0x428110: compare the pressure of board a (the player's) and board b. Writes the
 * level of a, the level of b and their positive difference at out[0] / out[5] / out[0xa] (filled
 * cells), out[2] / out[7] / out[0xc] (column heights, or 4 when a top-row path is open), out[3] /
 * out[8] / out[0xd] (stones) and out[4] / out[9] / out[0xe] (bombs of a against the stone level of
 * b); out[0x10] and out[0x11] become 4 when column 2 of a or b is occupied in its top row and
 * out[0x12] depends on the player's level byte (+0x17c). Other bytes are untouched. */
void vertrix_ai_compare_boards(const uint8_t a[VERTRIX_SCORE_CELLS],
                               const uint8_t b[VERTRIX_SCORE_CELLS], uint8_t player_level,
                               uint8_t out[VERTRIX_COMPARE_SIZE]);

#define VERTRIX_RECORD_SCORE_SLOTS 6

/* Original0x428610: score a record list. data[0] is the mode, data[1] the record count and the
 * records of five bytes start at data[5]: slot, table index, kind, rank and limit. Records whose
 * limit exceeds max_limit are skipped. Kinds 2..5 accumulate (add, subtract, 4 minus, minus 4) the
 * looked up byte into per-slot sums, kinds 0 and 1 track the smallest rank whose looked up byte
 * is 4 (kind 0) or 0 (kind 1). When such a rank exists the score is twice the smallest. Otherwise
 * the slot sums are averaged and combined per mode (0: largest, 1: smallest, 2: mean, times 2
 * for 0 and 1) and other modes score 0. Returns zero (leaving the score untouched) when a slot
 * of a kind 2..5 record is not below 6, which overruns the original's stack. */
int vertrix_ai_record_score(const uint8_t *data, const uint8_t table[256], uint32_t max_limit,
                            int32_t *score);
#endif
