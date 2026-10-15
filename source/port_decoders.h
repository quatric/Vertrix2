#ifndef PORT_DECODERS_H
#define PORT_DECODERS_H

#include "port.h"

/* Image decoder input, marker, pass, upsampler row and buffered row controller routines. */
uint32_t vertrix_port_decoder_consume_input_4b97c0(PORT_SIGNATURE);
uint32_t vertrix_port_decoder_output_start_4b98b0(PORT_SIGNATURE);
uint32_t vertrix_port_decoder_adobe_marker_4bf190(PORT_SIGNATURE);
uint32_t vertrix_port_decoder_pass_finish_4c16dc(PORT_SIGNATURE);
uint32_t vertrix_port_decoder_merged_rows_4c1d40(PORT_SIGNATURE);
uint32_t vertrix_port_decoder_buffer_pass_start_4c3220(PORT_SIGNATURE);
uint32_t vertrix_port_decoder_buffer_write_4c33a0(PORT_SIGNATURE);
uint32_t vertrix_port_decoder_buffer_read_4c3470(PORT_SIGNATURE);

#endif
