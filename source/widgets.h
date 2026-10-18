#ifndef WIDGETS_H
#define WIDGETS_H
#include "port.h"

/* Clean ports of interface object scroll, layout, hit test and release helpers (widgets.c). */
uint32_t vertrix_port_options_unpack_48c610(PORT_SIGNATURE);
uint32_t vertrix_port_step_toward_4ac980(PORT_SIGNATURE);
uint32_t vertrix_port_actor_counter_advance_4accc0(PORT_SIGNATURE);
uint32_t vertrix_port_object_scroll_up_4b3ce0(PORT_SIGNATURE);
uint32_t vertrix_port_object_scroll_down_4b3d60(PORT_SIGNATURE);
uint32_t vertrix_port_object_scroll_up_4b5050(PORT_SIGNATURE);
uint32_t vertrix_port_object_layout_4b3f30(PORT_SIGNATURE);
uint32_t vertrix_port_object_layout_4b41f0(PORT_SIGNATURE);
uint32_t vertrix_port_object_contains_point_4b4270(PORT_SIGNATURE);
uint32_t vertrix_port_object_slot_present_unowned_4b5d40(PORT_SIGNATURE);
uint32_t vertrix_port_object_list_release_4b5ee0(PORT_SIGNATURE);
uint32_t vertrix_port_object_release_parts_48b770(PORT_SIGNATURE);
#endif
