#ifndef MAKERS_H
#define MAKERS_H

#include "port.h"

/* COM setup, object maker and teardown, chain point, mode and decoder start routines. */
uint32_t vertrix_port_sound_device_com_setup_47e890(PORT_SIGNATURE);
uint32_t vertrix_port_object_construct_g_487b00(PORT_SIGNATURE);
uint32_t vertrix_port_actor_chain_point_4ad2c0(PORT_SIGNATURE);
uint32_t vertrix_port_actor_chain_orbit_point_4ad440(PORT_SIGNATURE);
uint32_t vertrix_port_object_construct_labeled_4b2400(PORT_SIGNATURE);
uint32_t vertrix_port_object_set_mode_4b4510(PORT_SIGNATURE);
uint32_t vertrix_port_object_teardown_4b5630(PORT_SIGNATURE);
uint32_t vertrix_port_object_start_5182c4_4b5c60(PORT_SIGNATURE);
uint32_t vertrix_port_decoder_start_4b9220(PORT_SIGNATURE);

#endif
