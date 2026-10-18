#ifndef RTLPOOLS_H
#define RTLPOOLS_H

#include "port.h"

/* JPEG row expansion and sample arrays, form refreshes and stream records */
uint32_t vertrix_port_actor_shade_rise_444a80(PORT_SIGNATURE);
uint32_t vertrix_port_jpeg_expand_rows_4c3780(PORT_SIGNATURE);
uint32_t vertrix_port_jpeg_alloc_sarray_4c4f60(PORT_SIGNATURE);
uint32_t vertrix_port_jpeg_sarray_io_4c5400(PORT_SIGNATURE);
uint32_t vertrix_port_form_controls_refresh_4d5930(PORT_SIGNATURE);
uint32_t vertrix_port_rtl_stream_record_take_4e7d80(PORT_SIGNATURE);

#endif
