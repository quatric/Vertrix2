#ifndef GAMEHELPERS_H
#define GAMEHELPERS_H
#include "port.h"

/* Clean ports of device mode, timer, file, button, table and scene helpers (gamehelpers.c). */
uint32_t vertrix_port_mode_switch_call_40afc0(PORT_SIGNATURE);
uint32_t vertrix_port_timer_tick_40b980(PORT_SIGNATURE);
uint32_t vertrix_port_value_over_32_40bac0(PORT_SIGNATURE);
uint32_t vertrix_port_file_read_exact_40c220(PORT_SIGNATURE);
uint32_t vertrix_port_file_read_word_40c2a0(PORT_SIGNATURE);
uint32_t vertrix_port_channel_mark_40caa0(PORT_SIGNATURE);
uint32_t vertrix_port_flagged_table_call_40ed70(PORT_SIGNATURE);
uint32_t vertrix_port_record_field_4125e0(PORT_SIGNATURE);
uint32_t vertrix_port_locked_call_416900(PORT_SIGNATURE);
uint32_t vertrix_port_player_keys_check_417350(PORT_SIGNATURE);
uint32_t vertrix_port_button_pick_4175b0(PORT_SIGNATURE);
uint32_t vertrix_port_button_pick_417620(PORT_SIGNATURE);
uint32_t vertrix_port_matcher_feed_417f50(PORT_SIGNATURE);
uint32_t vertrix_port_scene_open_418970(PORT_SIGNATURE);
uint32_t vertrix_port_game_teardown_419ef0(PORT_SIGNATURE);
uint32_t vertrix_port_language_apply_41a240(PORT_SIGNATURE);
uint32_t vertrix_port_scene_enter_41c390(PORT_SIGNATURE);
uint32_t vertrix_port_scene_restart_41cbb0(PORT_SIGNATURE);
#endif
