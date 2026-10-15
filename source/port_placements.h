#ifndef PORT_PLACEMENTS_H
#define PORT_PLACEMENTS_H

#include "port.h"

/* Board cell spawn, piece placement, effect maker and marked piece replacement routines. */
uint32_t vertrix_port_board_spawn_cells_429750(PORT_SIGNATURE);
uint32_t vertrix_port_board_place_pieces_42a200(PORT_SIGNATURE);
uint32_t vertrix_port_board_create_overlay_42ff50(PORT_SIGNATURE);
uint32_t vertrix_port_actor_spawn_match_effect_430190(PORT_SIGNATURE);
uint32_t vertrix_port_board_replace_marked_436720(PORT_SIGNATURE);
uint32_t vertrix_port_piece_replace_children_4368e0(PORT_SIGNATURE);
uint32_t vertrix_port_board_mirror_marked_437350(PORT_SIGNATURE);

#endif
