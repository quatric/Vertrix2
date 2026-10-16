#ifndef PORT_RTLWALKS_H
#define PORT_RTLWALKS_H

#include "port.h"

/* Window walks, AI slot choice, device stream opens and text reads */
uint32_t vertrix_port_rtl_record_field_4cbe80(PORT_SIGNATURE);
uint32_t vertrix_port_ai_find_best_slot_429000(PORT_SIGNATURE);
uint32_t vertrix_port_device_stream_open_47f790(PORT_SIGNATURE);
uint32_t vertrix_port_device_stream_open_47f830(PORT_SIGNATURE);
uint32_t vertrix_port_rtl_read_into_4db8c0(PORT_SIGNATURE);
uint32_t vertrix_port_rtl_window_close_4d21d0(PORT_SIGNATURE);
uint32_t vertrix_port_rtl_window_find_4d1a50(PORT_SIGNATURE);

#endif
