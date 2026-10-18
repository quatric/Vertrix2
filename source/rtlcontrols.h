#ifndef RTLCONTROLS_H
#define RTLCONTROLS_H

#include "port.h"

/* Control message forwarding, form visibility and the handle table */
uint32_t vertrix_port_control_command_4d1710(PORT_SIGNATURE);
uint32_t vertrix_port_form_control_show_4d5390(PORT_SIGNATURE);
uint32_t vertrix_port_handle_table_take_4dbb30(PORT_SIGNATURE);

#endif
