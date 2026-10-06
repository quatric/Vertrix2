#include "ai_timing.h"

/* Original tables: 0x4f8d38 (skill to column), 0x4f8d84 (base) and 0x4f8dac (span), the latter two
 * in rows of 60 dwords per difficulty. */
static const uint8_t SKILL_COLUMN[VERTRIX_AI_SKILLS] = {5, 3, 2, 4, 7, 6, 8, 6, 9, 6,
                                                        8, 4, 2, 8, 5, 4, 8, 8, 7};
static const uint16_t BASE[VERTRIX_AI_DIFFICULTIES][VERTRIX_AI_STEPS] = {
    {0, 476, 440, 404, 368, 332, 296, 260, 224, 188},
    {0, 317, 293, 269, 245, 221, 197, 173, 149, 125},
    {0, 211, 195, 179, 163, 147, 131, 115, 99, 83}};
static const uint16_t SPAN[VERTRIX_AI_DIFFICULTIES][VERTRIX_AI_STEPS] = {
    {0, 476, 440, 404, 368, 332, 296, 260, 224, 188},
    {0, 317, 293, 269, 245, 221, 197, 173, 149, 125},
    {0, 211, 195, 179, 163, 147, 131, 115, 99, 83}};

uint32_t vertrix_ai_reaction_time(uint32_t skill, uint32_t difficulty, uint32_t speed,
                                  VertrixAiRandom random, void *context)
{
    uint32_t column = SKILL_COLUMN[skill];
    uint32_t base = BASE[difficulty][column];
    uint32_t half = SPAN[difficulty][column] >> 1;
    uint32_t low = (base + half - half * speed / 9) & 0xffff;
    if ((half & 0xffff) == 0)
    {
        return low;
    }
    return low + random(context, (uint16_t)half);
}
