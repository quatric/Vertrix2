#ifndef VERTRIX_SCORE_H
#define VERTRIX_SCORE_H

#include <stdint.h>

/* Difficulty is the original global index 0..2. */
uint32_t vertrix_score_add(uint32_t score, uint32_t reward, uint32_t difficulty);

#endif
