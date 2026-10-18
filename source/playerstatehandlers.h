#ifndef PLAYERSTATEHANDLERS_H
#define PLAYERSTATEHANDLERS_H
#include "port.h"

/* Clean ports of border, finish effect, countdown, linked actor and player start, step and effect
 * handler states (playerstatehandlers.c). */
uint32_t vertrix_port_ui_border_storage_update_450270(PORT_SIGNATURE);
uint32_t vertrix_port_block_finish_effect_update_4503b0(PORT_SIGNATURE);
uint32_t vertrix_port_block_finish_effect_update_450450(PORT_SIGNATURE);
uint32_t vertrix_port_player_countdown_update_450750(PORT_SIGNATURE);
uint32_t vertrix_port_linked_alternating_update_450a10(PORT_SIGNATURE);
uint32_t vertrix_port_linked_alternating_update_450aa0(PORT_SIGNATURE);
uint32_t vertrix_port_state_start_4513f0(PORT_SIGNATURE);
uint32_t vertrix_port_state_start_451690(PORT_SIGNATURE);
uint32_t vertrix_port_state_steps_451490(PORT_SIGNATURE);
uint32_t vertrix_port_state_steps_451730(PORT_SIGNATURE);
uint32_t vertrix_port_player_opponent_settle_4526e0(PORT_SIGNATURE);
uint32_t vertrix_port_effect_armed_handler_452b20(PORT_SIGNATURE);
uint32_t vertrix_port_effect_armed_handler_452bd0(PORT_SIGNATURE);
uint32_t vertrix_port_effect_armed_handler_452c80(PORT_SIGNATURE);
uint32_t vertrix_port_effect_progress_compare_452d70(PORT_SIGNATURE);
#endif
