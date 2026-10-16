#ifndef PORT_RTLWAITS_H
#define PORT_RTLWAITS_H

#include "port.h"

/* Frame waits, cursor capture, menu and dropped-file walks, float truncation, fault flags and the
 * mixer volume */
uint32_t vertrix_port_frame_wait_40aed0(PORT_SIGNATURE);
uint32_t vertrix_port_cursor_capture_477c30(PORT_SIGNATURE);
uint32_t vertrix_port_rtl_flags_call_4db866(PORT_SIGNATURE);
uint32_t vertrix_port_rtl_float_trunc_4ee025(PORT_SIGNATURE);
uint32_t vertrix_port_menu_find_4d06d0(PORT_SIGNATURE);
uint32_t vertrix_port_files_dropped_4d50d0(PORT_SIGNATURE);
uint32_t vertrix_port_mixer_set_volume_40d490(PORT_SIGNATURE);

#endif
