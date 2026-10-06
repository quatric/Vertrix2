#ifndef VERTRIX_WORD_TRANSITION_H
#define VERTRIX_WORD_TRANSITION_H
#include <stdint.h>
/* Original 0x4aca60, 0x4acab0 and 0x4ad530 share this signed-word arithmetic.
 * Returns one while moving, zero on arrival, minus one for NULL storage. */
int vertrix_word_transition(int16_t *current, int16_t target, int16_t step, uint32_t cycles);
#endif
