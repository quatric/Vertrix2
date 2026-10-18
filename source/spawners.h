#ifndef SPAWNERS_H
#define SPAWNERS_H
#include "port.h"

/* Clean ports of bob pick, path turn, panel and banner spawn, palette cube, event stack push and
 * scratch pair routines (spawners.c). */
uint32_t vertrix_port_actor_bob_pick_44ad20(PORT_SIGNATURE);
uint32_t vertrix_port_actor_bob_pick_44add0(PORT_SIGNATURE);
uint32_t vertrix_port_actor_path_turn_45d690(PORT_SIGNATURE);
uint32_t vertrix_port_panel_spawn_471020(PORT_SIGNATURE);
uint32_t vertrix_port_banner_actor_spawn_472620(PORT_SIGNATURE);
uint32_t vertrix_port_palette_cube_480ca0(PORT_SIGNATURE);
uint32_t vertrix_port_event_stack_push_482060(PORT_SIGNATURE);
uint32_t vertrix_port_scratch_pair_call_482610(PORT_SIGNATURE);
#endif
