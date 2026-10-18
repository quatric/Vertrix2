#ifndef OBJECTS_H
#define OBJECTS_H
#include "port.h"

/* Clean ports of object pair, cursor, release and init helpers (objects.c). */
uint32_t vertrix_port_pair_children_show_4b4150(PORT_SIGNATURE);
uint32_t vertrix_port_pair_children_hide_4b41a0(PORT_SIGNATURE);
uint32_t vertrix_port_object_cursor_clamp_4b4690(PORT_SIGNATURE);
uint32_t vertrix_port_object_release_items_4b6020(PORT_SIGNATURE);
uint32_t vertrix_port_view_frame_state_4b9d70(PORT_SIGNATURE);
uint32_t vertrix_port_object_state_reset_4bd1c0(PORT_SIGNATURE);
uint32_t vertrix_port_object_release_links_4c0990(PORT_SIGNATURE);
uint32_t vertrix_port_rows_double_4c3850(PORT_SIGNATURE);
uint32_t vertrix_port_object_init_4c3fa0(PORT_SIGNATURE);
uint32_t vertrix_port_channels_allocate_4c69c0(PORT_SIGNATURE);
uint32_t vertrix_port_rtl_wide_assign_4ca3a0(PORT_SIGNATURE);
#endif
