#ifndef PORT_RTLPATTERNS_H
#define PORT_RTLPATTERNS_H

#include "port.h"

/* Music pattern packing, board blast counts, game loading and backdrop views. */
uint32_t vertrix_port_event_pack_40f1a0(PORT_SIGNATURE);
uint32_t vertrix_port_board_blast_count_4344e0(PORT_SIGNATURE);
uint32_t vertrix_port_board_blast_tally_434300(PORT_SIGNATURE);
uint32_t vertrix_port_game_load_418af0(PORT_SIGNATURE);
uint32_t vertrix_port_backdrop_view_set_441b70(PORT_SIGNATURE);

#endif
