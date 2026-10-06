#include "slot_deal.h"

enum
{
    WORD_FIRST_RESERVED = 4,
    WORD_SECOND_RESERVED = 5,
    WORD_THIRD_RESERVED = 6,
    WORD_ZERO_FIRST = 7,
    WORD_ZERO_LAST = 13,
    WORD_FINAL_ZERO = 14,
    DRAW_MASK = 0xffff
};

static int reserved_valid(uint32_t first, uint32_t second, uint32_t third)
{
    return first < VERTRIX_DEAL_SLOTS && second < VERTRIX_DEAL_SLOTS &&
           third < VERTRIX_DEAL_SLOTS && first != second && first != third && second != third;
}

int vertrix_slot_deal(uint32_t first, uint32_t second, uint32_t third, VertrixDealDraw draw,
                      void *context, uint32_t out[VERTRIX_DEAL_WORDS])
{
    uint32_t pool[VERTRIX_DEAL_POOL];
    uint32_t count = 0;
    if (!reserved_valid(first, second, third))
    {
        return 0;
    }
    for (uint32_t slot = 0; slot < VERTRIX_DEAL_SLOTS; ++slot)
    {
        if (slot != first && slot != second && slot != third)
        {
            pool[count] = slot;
            count += 1;
        }
    }
    for (uint32_t i = 0; i < VERTRIX_DEAL_POOL; ++i)
    {
        uint32_t j = draw(VERTRIX_DEAL_POOL, context) & DRAW_MASK;
        if (j >= VERTRIX_DEAL_POOL)
        {
            return 0;
        }
        uint32_t held = pool[j];
        pool[j] = pool[i];
        pool[i] = held;
    }
    for (uint32_t i = 0; i < VERTRIX_DEAL_PICKS; ++i)
    {
        out[i] = pool[i];
    }
    out[WORD_FIRST_RESERVED] = first;
    out[WORD_SECOND_RESERVED] = second;
    out[WORD_THIRD_RESERVED] = third;
    for (uint32_t i = WORD_ZERO_FIRST; i <= WORD_ZERO_LAST; ++i)
    {
        out[i] = 0;
    }
    out[WORD_FINAL_ZERO] = 0;
    return 1;
}
