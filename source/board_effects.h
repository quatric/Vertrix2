#ifndef VERTRIX_BOARD_EFFECTS_H
#define VERTRIX_BOARD_EFFECTS_H
#include "object_list.h"
#include "timer.h"

typedef struct
{
    uint32_t parameter;
    uint32_t state;
    uint32_t flash;
    uint32_t primary_counter;
    VertrixTimer blink;
    uint16_t effect;
} VertrixBoardEffect;

typedef struct
{
    VertrixBoardEffect *first;
    VertrixBoardEffect *second;
    uint32_t first_handle;
    uint32_t second_handle;
    uint32_t first_parameter;
    uint32_t second_parameter;
} VertrixBoardEffects;
/* Original board prefix 0x42fb60..0x42fbba: two optional effect objects,
 * parameter/state transitions, blink timers and virtual updates in order.
 * The visitor can alter the second parameter before its branch is reached.
 * A present object requires its live nonzero handle. No allocation. */
int vertrix_board_effects_tick(VertrixBoardEffects *effects, uint32_t elapsed,
                               VertrixObjectVisit visit, void *context);
#endif
