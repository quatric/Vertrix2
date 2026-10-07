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
/* Original variants 0x450130, 0x4501a0, 0x450200, 0x450270, 0x450300: Caller resolves list54671c
 * linked object and supplies its field58. Shared random represents598d30. */
int vertrix_linked_burst_update(VertrixLinkedBurst *burst, int linked_present,
                                uint32_t linked_value, uint32_t elapsed, VertrixRandom *random);
#endif
