#include "ai_piece_choice.h"
#include "actor_storage.h"
#include "object_scalars.h"

enum
{
    PLAYER_ROTATION_COUNT = 0x16c,
    PLAYER_SCORES_OFFSET = 0x210,
    MAX_CANDIDATES = 7
};

/* Original static priority table at 0x4f9318 (first 64 bytes). */
static const uint8_t DEFAULT_PIECE_PRIORITIES[64] = {
    1,  4,  4,  4,  2,  2,  3,  0,  1,  2,  3,  0,  6,  7, 0, 0, 14, 14, 15, 0, 17, 19,
    20, 0,  24, 24, 25, 0,  30, 31, 0,  0,  34, 50, 37, 0, 4, 3, 0,  0,  6,  7, 7,  0,
    14, 14, 15, 13, 19, 19, 21, 20, 24, 25, 0,  0,  30, 0, 0, 0, 38, 41, 47, 0};

uint32_t vertrix_ai_find_best_slot(const uint32_t table[7], const uint8_t *scores,
                                   const uint8_t *priorities, VertrixAiRandom random, void *context)
{
    if (!priorities)
    {
        priorities = DEFAULT_PIECE_PRIORITIES;
    }

    uint32_t count = vertrix_table_used_count(table);
    if (count == 1)
    {
        return 0;
    }
    if (count == 0)
    {
        return 1;
    }

    uint8_t val1[MAX_CANDIDATES];
    uint8_t val2[MAX_CANDIDATES];

    for (uint32_t i = 0; i < count; ++i)
    {
        uint32_t idx = table[i];
        val1[i] = scores ? scores[idx] : 0;
        val2[i] = priorities[idx];
    }

    uint32_t best = 0;
    int8_t best_score = (int8_t)val1[0];
    for (uint32_t candidate = 1; candidate < count; ++candidate)
    {
        int8_t cand_score = (int8_t)val1[candidate];

        if (cand_score > best_score)
        {
            best = candidate;
            best_score = cand_score;
        }
        else if (cand_score == best_score)
        {
            int8_t cand_prio = (int8_t)val2[candidate];
            int8_t best_prio = (int8_t)val2[best];

            if (cand_prio > best_prio)
            {
                best = candidate;
            }
            else if (cand_prio == best_prio)
            {
                uint16_t draw = random ? random(context, 2) : 0;
                if ((draw & 0xffff) == 1)
                {
                    best = candidate;
                }
            }
        }
    }

    uint32_t result = best + 1;
    if (result == count)
    {
        result ^= count;
    }
    return result;
}

int vertrix_ai_choose_piece_rotation(void *player, size_t size, const uint32_t table[7],
                                     const uint8_t *priorities, VertrixAiRandom random,
                                     void *context, uint32_t *chosen)
{
    if (!player || size < PLAYER_SCORES_OFFSET)
    {
        return 0;
    }

    const uint8_t *scores = (const uint8_t *)player + PLAYER_SCORES_OFFSET;
    uint32_t result = vertrix_ai_find_best_slot(table, scores, priorities, random, context);

    if (!vertrix_actor_storage_write(player, size, PLAYER_ROTATION_COUNT, 4, result))
    {
        return 0;
    }

    if (chosen)
    {
        *chosen = result;
    }
    return 1;
}
