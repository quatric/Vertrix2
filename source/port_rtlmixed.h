#ifndef PORT_RTLMIXED_H
#define PORT_RTLMIXED_H

#include "port.h"

/* Mixed small routines: text drawing steps, counters, lock set-up and guarded calls. */
uint32_t vertrix_port_text_draw_4429a0(PORT_SIGNATURE);
uint32_t vertrix_port_counter_steps_4acd30(PORT_SIGNATURE);
uint32_t vertrix_port_rtl_locks_init_4e5b0c(PORT_SIGNATURE);
uint32_t vertrix_port_rtl_name_lookup_4ebb34(PORT_SIGNATURE);
uint32_t vertrix_port_delta_decode_411280(PORT_SIGNATURE);
uint32_t vertrix_port_rtl_guarded_routine_4d3040(PORT_SIGNATURE);

#endif
