#ifndef WINDOWS_H
#define WINDOWS_H
#include "port.h"

/* Clean ports of range table, window teardown, style, close, idle,
 * system command and frame view routines (windows.c). */
uint32_t vertrix_port_decoder_range_table_4c9030(PORT_SIGNATURE);
uint32_t vertrix_port_window_object_teardown_4cb4f0(PORT_SIGNATURE);
uint32_t vertrix_port_window_style_4cccc0(PORT_SIGNATURE);
uint32_t vertrix_port_window_close_4d0410(PORT_SIGNATURE);
uint32_t vertrix_port_frame_view_idle_4d41c0(PORT_SIGNATURE);
uint32_t vertrix_port_window_system_command_4d5010(PORT_SIGNATURE);
uint32_t vertrix_port_frame_view_flag_4d63d0(PORT_SIGNATURE);
#endif
