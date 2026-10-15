#ifndef PORT_REPLACEMENTS_H
#define PORT_REPLACEMENTS_H

#include "port.h"

/* Marked cell replacement, scatter and flying copy routines. */
uint32_t vertrix_port_board_replace_cell_4365c0(PORT_SIGNATURE);
uint32_t vertrix_port_board_replace_random_cell_436440(PORT_SIGNATURE);
uint32_t vertrix_port_board_replace_marked_scaled_437060(PORT_SIGNATURE);
uint32_t vertrix_port_board_scatter_marked_437be0(PORT_SIGNATURE);
uint32_t vertrix_port_board_flying_copy_438ef0(PORT_SIGNATURE);
uint32_t vertrix_port_board_flying_copy_439510(PORT_SIGNATURE);

#endif
