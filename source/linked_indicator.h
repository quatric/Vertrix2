#ifndef VERTRIX_LINKED_INDICATOR_H
#define VERTRIX_LINKED_INDICATOR_H
#include "timer.h"
typedef struct
{
    uint32_t threshold, source, handler;
    VertrixTimer timer;
    uint8_t amount, target, stage;
    int16_t step;
} VertrixLinkedIndicator;
/* Original44ff90/44fff0/450040/4500b0/450100. Caller resolves first matching
 * list54671c object. linked_present0 represents a missing object; its value58
 * and state64 are otherwise supplied. Comparisons of state/threshold are signed. */
int vertrix_linked_indicator_update(VertrixLinkedIndicator *indicator, int linked_present,
                                    uint32_t linked_value, uint32_t linked_state, uint32_t elapsed);
#endif
