#ifndef PORT_RTLGUARDS_H
#define PORT_RTLGUARDS_H

#include "port.h"

/* Guarded buffer advances, item broadcasts, window message routes and object teardown */
uint32_t vertrix_port_reader_advance_4b50d0(PORT_SIGNATURE);
uint32_t vertrix_port_items_broadcast_both_42b290(PORT_SIGNATURE);
uint32_t vertrix_port_rtl_command_finish_4cff20(PORT_SIGNATURE);
uint32_t vertrix_port_rtl_handle_destroy_4dd4a0(PORT_SIGNATURE);
uint32_t vertrix_port_table_items_set_429a10(PORT_SIGNATURE);
uint32_t vertrix_port_table_items_apply_429af0(PORT_SIGNATURE);

#endif
