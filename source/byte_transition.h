#ifndef VERTRIX_BYTE_TRANSITION_H
#define VERTRIX_BYTE_TRANSITION_H
#include <stdint.h>
/* Original variants 0x4acc10, 0x4ad580: mode and amount transitions: unsigned-byte endpoints,
 * signed-word step and wrapped 32-bit intermediates. Returns one while moving,
 * zero on arrival, minus one for NULL storage. */
int vertrix_byte_transition(uint8_t *current, uint8_t target, int16_t step, uint32_t cycles);
#endif
