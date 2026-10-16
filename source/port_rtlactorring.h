#ifndef PORT_RTLACTORRING_H
#define PORT_RTLACTORRING_H

#include "port.h"

/* 0x42bca0 picks one random start angle with random_below(0x168), then builds 8 actors in a single
 * loop (0x42bce1-0x42be32, ebx < 8). */
uint32_t vertrix_port_board_cell_spawn_actor_ring_42bca0(PORT_SIGNATURE);

#endif
