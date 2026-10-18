#ifndef DRAINS_H
#define DRAINS_H
#include "port.h"

/* Clean ports of board advance, armed effect, board pair, forced choice, slide start, cycle,
 * kind sweep and drain routines (drains.c). */
uint32_t vertrix_port_state_advance_452770(PORT_SIGNATURE);
uint32_t vertrix_port_effect_armed_handler_452a50(PORT_SIGNATURE);
uint32_t vertrix_port_state_pair_4533b0(PORT_SIGNATURE);
uint32_t vertrix_port_effect_forced_choice_453ad0(PORT_SIGNATURE);
uint32_t vertrix_port_effect_slide_start_453c90(PORT_SIGNATURE);
uint32_t vertrix_port_effect_slide_start_453fd0(PORT_SIGNATURE);
uint32_t vertrix_port_effect_slide_start_4542e0(PORT_SIGNATURE);
uint32_t vertrix_port_state_cycle_4546a0(PORT_SIGNATURE);
uint32_t vertrix_port_effect_kind_sweep_454830(PORT_SIGNATURE);
uint32_t vertrix_port_state_drain_454b20(PORT_SIGNATURE);
uint32_t vertrix_port_state_drain_454d80(PORT_SIGNATURE);
uint32_t vertrix_port_effect_kind_take_454f00(PORT_SIGNATURE);
#endif
