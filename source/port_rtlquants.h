#ifndef PORT_RTLQUANTS_H
#define PORT_RTLQUANTS_H

#include "port.h"

/* JPEG upsampling, block arrays and colour lookup, paired timers, date rules, float faults and the
 * settings reload */
uint32_t vertrix_port_jpeg_h2v1_fancy_4c3950(PORT_SIGNATURE);
uint32_t vertrix_port_players_timed_450e70(PORT_SIGNATURE);
uint32_t vertrix_port_jpeg_alloc_barray_4c5030(PORT_SIGNATURE);
uint32_t vertrix_port_jpeg_quantize_rows_4c8be0(PORT_SIGNATURE);
uint32_t vertrix_port_rtl_rule_day_4e909c(PORT_SIGNATURE);
uint32_t vertrix_port_rtl_float_fault_4dad38(PORT_SIGNATURE);
uint32_t vertrix_port_settings_screen_reload_420e10(PORT_SIGNATURE);

#endif
