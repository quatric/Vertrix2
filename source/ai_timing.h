#ifndef VERTRIX_AI_TIMING_H
#define VERTRIX_AI_TIMING_H
#include "ai_player.h"
#include <stdint.h>

enum
{
    VERTRIX_AI_SKILLS = 19,
    VERTRIX_AI_DIFFICULTIES = 3,
    VERTRIX_AI_STEPS = 10
};

/* Original 0x43b5b0: the computer player's reaction time in milliseconds. The skill (+0x488)
 * picks a column of the tables, the difficulty (0x532bbc) a row; the span is halved, shortened by
 * half * speed / 9 (speed is the player's level, +0x17c), and a draw below the half is added to
 * the base (0x482770). */
uint32_t vertrix_ai_reaction_time(uint32_t skill, uint32_t difficulty, uint32_t speed,
                                  VertrixAiRandom random, void *context);
#endif
