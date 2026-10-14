#ifndef VERTRIX_PORT_SPAWNS_H
#define VERTRIX_PORT_SPAWNS_H
#include "port.h"

/* Clean ports of picture actor states, resource row builders, actor spawns, key text reading,
 * object centering and display release (port_spawns.c). */
uint32_t vertrix_port_picture_play_update_45aea0(PORT_SIGNATURE);
uint32_t vertrix_port_actor_glide_update_45af40(PORT_SIGNATURE);
uint32_t vertrix_port_effect_marks_sum_45ba30(PORT_SIGNATURE);
uint32_t vertrix_port_resource_rows_build_45e590(PORT_SIGNATURE);
uint32_t vertrix_port_resource_indexed_finish_45f140(PORT_SIGNATURE);
uint32_t vertrix_port_ui_companion_spawn_471100(PORT_SIGNATURE);
uint32_t vertrix_port_picture_actor_spawn_4723a0(PORT_SIGNATURE);
uint32_t vertrix_port_key_text_read_477610(PORT_SIGNATURE);
uint32_t vertrix_port_object_center_place_477e30(PORT_SIGNATURE);
uint32_t vertrix_port_display_release_pair_47ea20(PORT_SIGNATURE);
#endif
