#ifndef BOARDS_H
#define BOARDS_H

#include "port.h"

/* Play actor board state and title walker routines. */
uint32_t vertrix_port_state_choice_apply_451e20(PORT_SIGNATURE);
uint32_t vertrix_port_state_choice_take_451f50(PORT_SIGNATURE);
uint32_t vertrix_port_state_match_452160(PORT_SIGNATURE);
uint32_t vertrix_port_state_attack_452440(PORT_SIGNATURE);
uint32_t vertrix_port_state_effect_flags_452960(PORT_SIGNATURE);
uint32_t vertrix_port_state_drain_wait_454a50(PORT_SIGNATURE);
uint32_t vertrix_port_state_drain_wait_454cb0(PORT_SIGNATURE);
uint32_t vertrix_port_state_guard_4553a0(PORT_SIGNATURE);
uint32_t vertrix_port_effect_slide_advance_455f80(PORT_SIGNATURE);
uint32_t vertrix_port_title_walker_enter_457c10(PORT_SIGNATURE);
uint32_t vertrix_port_title_walker_run_457e40(PORT_SIGNATURE);
uint32_t vertrix_port_title_walker_blink_4587a0(PORT_SIGNATURE);

#endif
