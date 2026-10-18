#ifndef STREAMS_H
#define STREAMS_H
#include "port.h"

/* Clean ports of runtime start forward, object reset, record setup, space test, stream fill,
 * console read and long double class routines (streams.c). */
uint32_t vertrix_port_crt_start_forward_4e14dc(PORT_SIGNATURE);
uint32_t vertrix_port_crt_object_reset_4e3743(PORT_SIGNATURE);
uint32_t vertrix_port_crt_record_setup_4e38ff(PORT_SIGNATURE);
uint32_t vertrix_port_crt_is_space_4e7140(PORT_SIGNATURE);
uint32_t vertrix_port_crt_stream_fill_4ec578(PORT_SIGNATURE);
uint32_t vertrix_port_crt_console_read_4ecaa0(PORT_SIGNATURE);
uint32_t vertrix_port_crt_long_double_class_4edf7f(PORT_SIGNATURE);
#endif
