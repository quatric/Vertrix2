#include "ui_display_layout.h"

static int16_t position_word(uint16_t value)
{
    return (int16_t)(value < 32768 ? (int32_t)value : (int32_t)value - 65536);
}

int vertrix_ui_display_position(size_t pair, unsigned side, int16_t offset_x, int16_t offset_y,
                                int16_t *x, int16_t *y)
{
    static const uint16_t relative_x[2] = {156, 472};
    static const uint16_t relative_y[12] = {269, 284, 299, 314, 329, 344,
                                            359, 374, 389, 404, 419, 434};
    if (pair >= 12 || side >= 2 || !x || !y || x == y)
    {
        return 0;
    }
    *x = position_word((uint16_t)((uint16_t)offset_x + relative_x[side]));
    *y = position_word((uint16_t)((uint16_t)offset_y + relative_y[pair]));
    return 1;
}
