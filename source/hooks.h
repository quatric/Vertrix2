#ifndef HOOKS_H
#define HOOKS_H

#include "port.h"

/* Runtime window teardown, activation, focus, hook, error raise and string assignment routines. */
uint32_t vertrix_port_handle_object_teardown_4cbfe0(PORT_SIGNATURE);
uint32_t vertrix_port_object_destroy_f_4d3f70(PORT_SIGNATURE);
uint32_t vertrix_port_window_activate_4d4630(PORT_SIGNATURE);
uint32_t vertrix_port_window_focus_step_4d4d10(PORT_SIGNATURE);
uint32_t vertrix_port_application_idle_step_4d04f0(PORT_SIGNATURE);
uint32_t vertrix_port_window_procedure_hook_4cfe40(PORT_SIGNATURE);
uint32_t vertrix_port_rtl_forward_pair_4d9930(PORT_SIGNATURE);
uint32_t vertrix_port_rtl_error_raise_4d9a10(PORT_SIGNATURE);
uint32_t vertrix_port_string_assign_text_4ca4a0(PORT_SIGNATURE);
uint32_t vertrix_port_window_enable_state_4d4ee0(PORT_SIGNATURE);

#endif
