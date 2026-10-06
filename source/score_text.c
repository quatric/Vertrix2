#include "score_text.h"

int vertrix_score_text(uint32_t value, char *output, size_t capacity)
{
    if (!output || capacity < VERTRIX_SCORE_TEXT_SIZE)
    {
        return 0;
    }
    if (value > VERTRIX_SCORE_TEXT_MAX)
    {
        value = VERTRIX_SCORE_TEXT_MAX;
    }
    for (size_t index = VERTRIX_SCORE_TEXT_SIZE - 1; index-- > 0;)
    {
        output[index] = (char)('0' + value % 10);
        value /= 10;
    }
    output[VERTRIX_SCORE_TEXT_SIZE - 1] = '\0';
    return 1;
}
