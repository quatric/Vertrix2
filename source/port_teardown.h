#ifndef VERTRIX_PORT_TEARDOWN_H
#define VERTRIX_PORT_TEARDOWN_H
#include "port.h"

/* Clean ports of object teardown and construction, script loading, the options scene exit and
 * the choice grid column pick (port_teardown.c). */
uint32_t vertrix_port_object_teardown_412130(PORT_SIGNATURE);
uint32_t vertrix_port_object_read_412240(PORT_SIGNATURE);
uint32_t vertrix_port_object_load_script_416a80(PORT_SIGNATURE);
uint32_t vertrix_port_scene_leave_options_41fc70(PORT_SIGNATURE);
uint32_t vertrix_port_choice_grid_pick_column_42a080(PORT_SIGNATURE);
uint32_t vertrix_port_choice_grid_construct_42a310(PORT_SIGNATURE);
uint32_t vertrix_port_choice_grid_teardown_42a3c0(PORT_SIGNATURE);
#endif
