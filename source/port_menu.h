#ifndef VERTRIX_PORT_MENU_H
#define VERTRIX_PORT_MENU_H
#include "port.h"

/* Clean ports of menu key, sound tick, score table, scene change and mixer helpers (port_menu.c).
 */
uint32_t vertrix_port_mixer_portamento_40cff0(PORT_SIGNATURE);
uint32_t vertrix_port_record_table_init_4120a0(PORT_SIGNATURE);
uint32_t vertrix_port_table_pair_select_415350(PORT_SIGNATURE);
uint32_t vertrix_port_table_pair_select_4153e0(PORT_SIGNATURE);
uint32_t vertrix_port_sound_volume_tick_417060(PORT_SIGNATURE);
uint32_t vertrix_port_sound_tick_417150(PORT_SIGNATURE);
uint32_t vertrix_port_player_key_pair_4172c0(PORT_SIGNATURE);
uint32_t vertrix_port_player_key_pair_4173d0(PORT_SIGNATURE);
uint32_t vertrix_port_player_keys_check_417460(PORT_SIGNATURE);
uint32_t vertrix_port_high_score_insert_4177b0(PORT_SIGNATURE);
uint32_t vertrix_port_window_activate_419f80(PORT_SIGNATURE);
uint32_t vertrix_port_scene_enter_41b5e0(PORT_SIGNATURE);
uint32_t vertrix_port_scene_leave_41d470(PORT_SIGNATURE);
uint32_t vertrix_port_scene_leave_41d510(PORT_SIGNATURE);
uint32_t vertrix_port_object_load_4122f0(PORT_SIGNATURE);
#endif
