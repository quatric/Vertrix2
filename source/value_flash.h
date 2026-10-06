#ifndef VERTRIX_VALUE_FLASH_H
#define VERTRIX_VALUE_FLASH_H
#include <stdint.h>

enum
{
    VERTRIX_FLASH_IDLE = 0,
    VERTRIX_FLASH_RISE = 1,
    VERTRIX_FLASH_FALL = 2
};

/* The dim overlay over a HUD number and the number's delayed value. Handlers 0x44fc60 (level,
 * compares the shown value +0x180 with the player's +0x178), 0x44fad0 (speed, +0x17c), the rise
 * 0x44fcf0 and the fall 0x44fd60: when the value changes the overlay's effect offset (+0x48) runs
 * from -100 to 50 and back in steps of 2 per 12 ms cycle (0x4ac7b0 period 1 * 12), and the number
 * takes the new value at the peak (0x44fc30). */
typedef struct
{
    uint32_t phase;
    uint32_t counter; /* timer +0xbc */
    int16_t offset;   /* actor +0x48 */
    uint32_t shown;   /* the number's displayed value */
} VertrixValueFlash;

void vertrix_value_flash_update(VertrixValueFlash *flash, uint32_t value, uint32_t elapsed);

#endif
