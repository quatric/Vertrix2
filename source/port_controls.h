#ifndef PORT_CONTROLS_H
#define PORT_CONTROLS_H

#include "port.h"

/* Image record start, decoder input step, control helper and list removal routines. */
uint32_t vertrix_port_image_record_start_4b74c0(PORT_SIGNATURE);
uint32_t vertrix_port_decoder_input_step_4b95e0(PORT_SIGNATURE);
uint32_t vertrix_port_control_outer_owner_4d1930(PORT_SIGNATURE);
uint32_t vertrix_port_return_constant_ffff_4d25e0(PORT_SIGNATURE);
uint32_t vertrix_port_object_status_active_4d2d70(PORT_SIGNATURE);
uint32_t vertrix_port_rtl_record_forward_4d4060(PORT_SIGNATURE);
uint32_t vertrix_port_control_command_note_4d5660(PORT_SIGNATURE);
uint32_t vertrix_port_control_send_note_4d57a0(PORT_SIGNATURE);
uint32_t vertrix_port_list_remove_range_4d8950(PORT_SIGNATURE);

#endif
