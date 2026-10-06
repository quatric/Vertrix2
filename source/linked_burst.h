#ifndef VERTRIX_LINKED_BURST_H
#define VERTRIX_LINKED_BURST_H
#include "random.h"
#include "timer.h"
typedef struct
{
    uint32_t repetitions, source, handler;
    int16_t effect, target, step;
    int32_t delay, delay_target, delay_step;
    VertrixTimer timer;
} VertrixLinkedBurst;
/* Original450130/4501a0/450200/450270/450300. Caller resolves list54671c
 * linked object and supplies its field58. Shared random represents598d30. */
int vertrix_linked_burst_update(VertrixLinkedBurst *burst, int linked_present,
                                uint32_t linked_value, uint32_t elapsed, VertrixRandom *random);
#endif
