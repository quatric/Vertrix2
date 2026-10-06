#include "text_layout.h"

static int16_t layout_word(int32_t value)
{
    uint32_t word = (uint16_t)value;
    return (int16_t)(word < 32768 ? (int32_t)word : (int32_t)word - 65536);
}

int vertrix_text_layout(int16_t width, int16_t height, int16_t left, int16_t right, int16_t top,
                        int16_t bottom, int16_t *x, int16_t *y)
{
    if (!x || !y)
    {
        return 0;
    }
    int16_t result_x = 0, result_y = 0;
    if (right > left)
    {
        result_x = layout_word(((int32_t)right - left + 2 - width) / 2);
        if (result_x < 0)
        {
            *x = result_x;
            *y = result_y;
            return 1;
        }
    }
    if (top < bottom)
    {
        result_y = layout_word(((int32_t)bottom - top + 1 - height) / 2);
        if (result_y < 0)
        {
            *x = result_x;
            *y = result_y;
            return 1;
        }
    }
    *x = layout_word((int32_t)result_x + left);
    *y = layout_word((int32_t)result_y + top);
    return 1;
}
