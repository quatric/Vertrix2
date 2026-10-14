#ifndef VERTRIX_PORT_PAUSES_H
#define VERTRIX_PORT_PAUSES_H
#include "port.h"

/* Clean ports of game event wait, pause teardown, level file load, choice grid and piece
 * teardown, block create, piece side test and choice row pick routines (port_pauses.c). */
uint32_t vertrix_port_game_event_wait_424790(PORT_SIGNATURE);
uint32_t vertrix_port_game_event_wait_424890(PORT_SIGNATURE);
uint32_t vertrix_port_game_pause_teardown_4253b0(PORT_SIGNATURE);
uint32_t vertrix_port_level_file_load_429460(PORT_SIGNATURE);
uint32_t vertrix_port_choice_grid_teardown_429910(PORT_SIGNATURE);
uint32_t vertrix_port_piece_actor_destroy_full_42ab10(PORT_SIGNATURE);
uint32_t vertrix_port_piece_pairs_destroy_42b190(PORT_SIGNATURE);
uint32_t vertrix_port_block_create_full_42bbd0(PORT_SIGNATURE);
uint32_t vertrix_port_board_piece_touches_side_42f030(PORT_SIGNATURE);
uint32_t vertrix_port_choice_grid_pick_rows_429ee0(PORT_SIGNATURE);
#endif
