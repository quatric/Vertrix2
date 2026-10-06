#include "value_flash.h"

#include "word_transition.h"

enum
{
    PERIOD = 12,
    STEP = 2,
    PEAK = 50,
    REST = -100
};

/* One pass of 0x44fcf0 / 0x44fd60: the timer adds the elapsed time (0x4ac500), acts when a period
 * is full (0x4ac520) and keeps its remainder only as 0x4ac5b0 does. Returns one on arrival. */
static int run(VertrixValueFlash *flash, int16_t target, uint32_t elapsed)
{
    flash->counter += elapsed;
    if (flash->counter < PERIOD)
    {
        return 0;
    }
    uint32_t cycles = flash->counter / PERIOD;
    if (cycles * PERIOD >= flash->counter)
    {
        flash->counter = 0;
    }
    return vertrix_word_transition(&flash->offset, target, STEP, cycles) == 0;
}

void vertrix_value_flash_update(VertrixValueFlash *flash, uint32_t value, uint32_t elapsed)
{
    if (flash->phase == VERTRIX_FLASH_IDLE)
    {
        if (flash->shown != value)
        {
            flash->offset = REST;
            flash->counter = 0;
            flash->phase = VERTRIX_FLASH_RISE;
        }
    }
    else if (flash->phase == VERTRIX_FLASH_RISE)
    {
        if (run(flash, PEAK, elapsed))
        {
            flash->shown = value;
            flash->phase = VERTRIX_FLASH_FALL;
        }
    }
    else if (run(flash, REST, elapsed))
    {
        flash->phase = VERTRIX_FLASH_IDLE;
    }
}
