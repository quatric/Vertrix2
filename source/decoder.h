#ifndef DECODER_H
#define DECODER_H
#include "port.h"

/* Clean ports of picture decoder input, setup, restart and upsampling routines (decoder.c). */
uint32_t vertrix_port_decoder_fill_input_4b9c20(PORT_SIGNATURE);
uint32_t vertrix_port_decoder_coefficients_setup_4bb9b0(PORT_SIGNATURE);
uint32_t vertrix_port_decoder_read_restart_4c07d0(PORT_SIGNATURE);
uint32_t vertrix_port_decoder_process_restart_4c26f0(PORT_SIGNATURE);
uint32_t vertrix_port_decoder_upsample_double_4c38b0(PORT_SIGNATURE);
uint32_t vertrix_port_rtl_lookup_or_default_4d24a0(PORT_SIGNATURE);
#endif
