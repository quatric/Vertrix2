#ifndef LETTERS_H
#define LETTERS_H
#include "port.h"

/* Clean ports of board settle end, slide begin, move end, kind light, fade volume, title letter
 * restart, place pick and child bob routines (letters.c). */
uint32_t vertrix_port_board_settle_end_455830(PORT_SIGNATURE);
uint32_t vertrix_port_effect_slide_begin_455e50(PORT_SIGNATURE);
uint32_t vertrix_port_actor_move_end_4560c0(PORT_SIGNATURE);
uint32_t vertrix_port_actor_kind_light_456bf0(PORT_SIGNATURE);
uint32_t vertrix_port_actor_fade_volume_456cd0(PORT_SIGNATURE);
uint32_t vertrix_port_title_letter_restart_459e00(PORT_SIGNATURE);
uint32_t vertrix_port_title_letter_fight_restart_45a440(PORT_SIGNATURE);
uint32_t vertrix_port_player_place_pick_45bad0(PORT_SIGNATURE);
uint32_t vertrix_port_actor_child_bob_45cc40(PORT_SIGNATURE);
uint32_t vertrix_port_actor_child_bob_45cd00(PORT_SIGNATURE);
#endif
