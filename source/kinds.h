#ifndef KINDS_H
#define KINDS_H
#include "port.h"

/* Clean ports of board kind mark, marked cell clearing, burst, first turn, reaction time, match
 * reward and effect teardown routines (kinds.c). */
uint32_t vertrix_port_board_mark_effect_kinds_435e80(PORT_SIGNATURE);
uint32_t vertrix_port_board_mark_column_tops_435f30(PORT_SIGNATURE);
uint32_t vertrix_port_board_clear_marked_4374e0(PORT_SIGNATURE);
uint32_t vertrix_port_board_burst_first_439080(PORT_SIGNATURE);
uint32_t vertrix_port_player_first_turn_43b1a0(PORT_SIGNATURE);
uint32_t vertrix_port_ai_reaction_time_43b5b0(PORT_SIGNATURE);
uint32_t vertrix_port_player_match_reward_43b9c0(PORT_SIGNATURE);
uint32_t vertrix_port_effect_actor_teardown_43e1a0(PORT_SIGNATURE);
#endif
