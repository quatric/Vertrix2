#ifndef VERTRIX_SLOT_DEAL_H
#define VERTRIX_SLOT_DEAL_H
#include <stdint.h>

enum
{
    VERTRIX_DEAL_SLOTS = 19,
    VERTRIX_DEAL_POOL = 16,
    VERTRIX_DEAL_PICKS = 4,
    VERTRIX_DEAL_WORDS = 15
};

/* Supplied boundary for the shared draw 0x4826c0: a value below limit (low 16 bits used). */
typedef uint32_t (*VertrixDealDraw)(uint32_t limit, void *context);

/* Original0x415c60: with three distinct reserved slots (dwords 0x4f84e0, 0x4f84cc and 0x4f84b8,
 * all below 19), shuffle the other sixteen slot numbers, drawing sixteen times with limit 16
 * (for each position in turn, swap it with the drawn position) and fill the 15 dwords from
 * 0x53bad8: the first four shuffled numbers, then the three reserved slots (first, second, third
 * as the original's esi, edi and the dword 0x4f84b8), seven zeros and a final zero (all 15 words
 * are written). Returns 0 and changes nothing when the reserved slots are not distinct and below 19
 * (the original then reads uninitialized stack), or when a draw is not below the limit (it then
 * indexes the stack). */
int vertrix_slot_deal(uint32_t first, uint32_t second, uint32_t third, VertrixDealDraw draw,
                      void *context, uint32_t out[VERTRIX_DEAL_WORDS]);
#endif
