#ifndef VERTRIX_AI_PIECE_CHOICE_H
#define VERTRIX_AI_PIECE_CHOICE_H

#include "ai_player.h"
#include <stddef.h>
#include <stdint.h>

/* Original 0x429000: finds the best piece slot / rotation candidate from an active
 * table of up to seven indices (counted by 0x425e00). Scores are read from scores[table[i]],
 * tie-breaking uses priority table at 0x4f9318 (or supplied priorities), and further ties
 * are broken by random draw 0x4826c0 with divisor 2.
 * Returns best + 1, wrapping to 0 if best + 1 == count. Returns 0 if count == 1. */
uint32_t vertrix_ai_find_best_slot(const uint32_t table[7], const uint8_t *scores,
                                   const uint8_t *priorities, VertrixAiRandom random,
                                   void *context);

/* Original 0x4290a0: reads scores from player object (+0x210), calls 0x429000 with table[7],
 * writes the chosen rotation count into player +0x16c (dword), and returns the chosen count.
 * Safe against undersized storage. */
int vertrix_ai_choose_piece_rotation(void *player, size_t size, const uint32_t table[7],
                                     const uint8_t *priorities, VertrixAiRandom random,
                                     void *context, uint32_t *chosen);

#endif
