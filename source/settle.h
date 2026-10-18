#ifndef SETTLE_H
#define SETTLE_H
#include "port.h"

/* Clean ports of piece child, board shift, piece fit, stone placement and extra start routines
 * (settle.c). */
uint32_t vertrix_port_piece_children_place_42a800(PORT_SIGNATURE);
uint32_t vertrix_port_piece_actor_update_42ac40(PORT_SIGNATURE);
uint32_t vertrix_port_board_columns_push_42f310(PORT_SIGNATURE);
uint32_t vertrix_port_board_rows_push_42f620(PORT_SIGNATURE);
uint32_t vertrix_port_board_piece_left_free_4311c0(PORT_SIGNATURE);
uint32_t vertrix_port_board_piece_right_free_431280(PORT_SIGNATURE);
uint32_t vertrix_port_board_place_stones_4316c0(PORT_SIGNATURE);
uint32_t vertrix_port_board_extras_start_4323d0(PORT_SIGNATURE);
uint32_t vertrix_port_board_piece_hits_grid_4330d0(PORT_SIGNATURE);
#endif
