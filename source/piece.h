#ifndef VERTRIX_PIECE_H
#define VERTRIX_PIECE_H

#include "random.h"

/* mode is the original player field +0x4c8, not a translated bonus ID. */
void vertrix_piece(VertrixRandom *random, uint32_t mode, uint8_t blocks[3]);
void vertrix_piece_cycle(uint8_t blocks[3]);
void vertrix_piece_bottom_color(VertrixRandom *random, uint8_t blocks[3]);

#endif
