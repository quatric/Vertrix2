#ifndef VERTRIX_AI_FEATURES_H
#define VERTRIX_AI_FEATURES_H
#include "choice_grid.h"
#include <stdint.h>
/* Computer-player evaluation helpers over the board bytes (5 columns of 13 cells, 0xff empty) and
 * the choice grid. */
#define VERTRIX_REACH_COLUMNS 5
#define VERTRIX_BOARD_ROWS 13

/* Original0x4261b0: mark which of the five columns a block in a row can reach from a start
 * column. All five outputs start as 1; scanning left from the column before the start and right
 * from the column after it, the first column whose cell in this row is occupied and every column
 * beyond it get 0. Rows of 10 or more never block. start must be 0..5 and row 0..12. Returns
 * zero for other values, leaving the outputs untouched. */
int vertrix_ai_row_reach(const uint8_t cells[VERTRIX_REACH_COLUMNS * VERTRIX_BOARD_ROWS],
                         uint32_t start, uint32_t row, uint8_t reach[VERTRIX_REACH_COLUMNS]);

/* Offsets in the feature byte array filled by 0x427c10. */
enum
{
    VERTRIX_AI_FEATURE_PAIR = 0x01,
    VERTRIX_AI_FEATURE_SHAPE = 0x06,
    VERTRIX_AI_FEATURE_GAP = 0x0b,
    VERTRIX_AI_FEATURE_STEP = 0x0f,
    VERTRIX_AI_FEATURE_REACH = 0x26,
    VERTRIX_AI_FEATURE_SIZE = 0x27
};

/* Original0x427c10: write the five feature bytes at the offsets above, from the register
 * operands (a, b, c) and the stack operands (d, e, f, g) in their original order. Bytes at other
 * offsets are untouched. */
void vertrix_ai_features(uint32_t a, uint32_t b, uint32_t c, uint32_t d, uint32_t e, uint32_t f,
                         uint32_t g, uint8_t out[VERTRIX_AI_FEATURE_SIZE]);

/* Original0x427e10: from the player's mode dword (+0x4c8) and its opponent's, write 4 or 0 into
 * flag bytes 0x13..0x2e of the output (the bytes 0x1c..0x2e come from the opponent). Bytes 0x00 to
 * 0x12 and 0x2f onward are untouched. */
#define VERTRIX_AI_MODE_FLAGS_SIZE 0x2f
void vertrix_ai_mode_flags(uint32_t own_mode, uint32_t opponent_mode,
                           uint8_t flags[VERTRIX_AI_MODE_FLAGS_SIZE]);

/* Original0x428e70: score each of the seven rows of the choice grid into scores[7] (zeroed first)
 * and report whether any enabled cell has a nonzero weight byte. A row with no nonzero value
 * scores 0. Otherwise the score is the largest weight byte among the first nonzero cell and the
 * cells equal to 1 when mode is above 2 or the row is flagged in the table at 0x4fb6c0, else the
 * 8-bit signed average of the weights of the cells equal to 1. */
int vertrix_ai_choice_scores(const VertrixChoiceGrid *grid, uint32_t mode, uint8_t scores[7]);
#endif
