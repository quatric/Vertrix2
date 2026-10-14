#ifndef VERTRIX_PORT_SCENES_H
#define VERTRIX_PORT_SCENES_H
#include "port.h"

/* Clean ports of scene change, choice grid, piece slot and computer player row helpers
 * (port_scenes.c). */
uint32_t vertrix_port_scene_leave_41efe0(PORT_SIGNATURE);
uint32_t vertrix_port_scene_leave_41f460(PORT_SIGNATURE);
uint32_t vertrix_port_scene_leave_41f910(PORT_SIGNATURE);
uint32_t vertrix_port_scene_leave_421e80(PORT_SIGNATURE);
uint32_t vertrix_port_scene_leave_picture_425a50(PORT_SIGNATURE);
uint32_t vertrix_port_gate_dispatch_call_full_41d5b0(PORT_SIGNATURE);
uint32_t vertrix_port_scene_title_end_421de0(PORT_SIGNATURE);
uint32_t vertrix_port_scene_load_named_41e280(PORT_SIGNATURE);
uint32_t vertrix_port_ai_row_reach_4261b0(PORT_SIGNATURE);
uint32_t vertrix_port_piece_actor_construct_slots_429880(PORT_SIGNATURE);
uint32_t vertrix_port_choice_grid_apply_429d50(PORT_SIGNATURE);
uint32_t vertrix_port_choice_grid_load_values_429df0(PORT_SIGNATURE);
uint32_t vertrix_port_blocks_set_state_42aa20(PORT_SIGNATURE);
#endif
