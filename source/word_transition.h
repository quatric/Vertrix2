#ifndef VERTRIX_WORD_TRANSITION_H
#define VERTRIX_WORD_TRANSITION_H
#include <stdint.h>
/* Original variants 0x4aca60, 0x4acab0, 0x4ad530, 0x4ad5e0, 0x4ad630:
 * signed-word transitions at object offsets e/10/12, 16/18/1a, 48/4a/4c,
 * 2a/30/32 and 3a/40/42 (current/target/step), respectively.
 * tools/verify_word_transition.py compares whole object bytes and completion returns.
 * Returns one while moving, zero on arrival, minus one for NULL storage. */
int vertrix_word_transition(int16_t *current, int16_t target, int16_t step, uint32_t cycles);
#endif
