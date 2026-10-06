#ifndef VERTRIX_AI_SEARCH_H
#define VERTRIX_AI_SEARCH_H
#include <stdint.h>

#include "block_factory.h"
#include "call_glue.h"

/* The stack locals the search works in (the 0x190 bytes below the frame): the services resolve
 * frame - VERTRIX_AI_SEARCH_FRAME_SIZE to their storage. */
enum
{
    VERTRIX_AI_SEARCH_FRAME_SIZE = 0x190
};

/* The arguments of 0x4270a0: registers eax (the AI object), edx, ebx and ecx (the three block
 * colours' bytes b, c and a, in that order) and six stack dwords (nearest esp first). */
typedef struct VertrixAiSearch
{
    uint32_t object;
    uint32_t b;
    uint32_t c;
    uint32_t a;
    uint32_t kind_out;
    uint32_t column_out;
    uint32_t pressure;
    uint32_t start;
    uint32_t row;
    uint32_t level;
} VertrixAiSearch;

/* Original 0x4270a0 (`frame` is the token for ebp; ret 0x18): returns zero at once for a level of
 * two or less. Otherwise the board bytes at object + 0x184 (5 columns of 13) are copied to the
 * frame; 0x4261b0 (vertrix_ai_row_reach, start and row) marks the reachable columns (+0x38).
 * For each reachable column the board is copied afresh, the last empty (0xff) cell of the column
 * is found and the three rotations of the block (a, c, b at the cell and the two above it; then
 * b, a, c; then c, b, a) are each scored by 0x434ee0 (eax the copy, edx frame - 0x190, ebx the
 * pressure byte, ecx 0, a stack pointer to the word the score comes back in); a score above the
 * column's best (+0x40) replaces it with the rotation number (+0x48) and clears the failure flag.
 * When some call answered 1 the column of the highest best score (the first of equals) is stored
 * through column_out and its rotation through kind_out, and 1 is returned; otherwise 0. The
 * score word is the call's out_value. *result is the original's eax. Returns zero when memory
 * cannot be accessed. */
int vertrix_ai_search(const VertrixCalls *calls, const VertrixFactoryServices *services,
                      uint32_t frame, const VertrixAiSearch *search, uint32_t *result);

#endif
