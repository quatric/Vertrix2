#ifndef VERTRIX_AI_CONTROLLER_H
#define VERTRIX_AI_CONTROLLER_H
#include "ai_player.h"
#include "ai_timing.h"
#include "game_session.h"

/* The computer player of one board: the planner object at player +0x450 (0x425e20) and the driver
 * 0x43ad70 / 0x43ae20 that plans once per piece, waits the reaction time (0x43b5b0) and steers one
 * key tick at a time. skill is the player's +0x488, the character index the select screen leaves
 * in 0x532a6c. */
typedef struct
{
    uint32_t skill;
    uint32_t level;     /* object +0x160, from the skill by 0x425ef0 */
    uint32_t previous;  /* object +0x180, the column chosen last */
    uint32_t column;    /* object +0x168 */
    uint32_t rotations; /* object +0x16c */
    uint32_t spawned;   /* the session's piece count at the last plan */
    uint32_t counter;   /* timer +0xbc */
    uint32_t period;    /* timer +0xc0 */
    int planned;        /* object +0x178 == 0 */
    int dropping;
} VertrixAiController;

void vertrix_ai_controller_init(VertrixAiController *ai, uint32_t skill);

/* Advance by elapsed milliseconds and press the keys of the computer player on the session. */
void vertrix_ai_controller_update(VertrixAiController *ai, VertrixSession *session,
                                  uint32_t elapsed);

#endif
