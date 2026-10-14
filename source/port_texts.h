#ifndef VERTRIX_PORT_TEXTS_H
#define VERTRIX_PORT_TEXTS_H
#include "port.h"

/* Clean ports of text conversion, object teardown, device query, stream read, display setting,
 * record copy, list cycle and label format routines (port_texts.c). */
uint32_t vertrix_port_text_from_wide_47fc50(PORT_SIGNATURE);
uint32_t vertrix_port_object_destroy_b_481fb0(PORT_SIGNATURE);
uint32_t vertrix_port_device_query_487130(PORT_SIGNATURE);
uint32_t vertrix_port_stream_read_48a9d0(PORT_SIGNATURE);
uint32_t vertrix_port_display_settings_apply_48c3d0(PORT_SIGNATURE);
uint32_t vertrix_port_record_copy_48d3e0(PORT_SIGNATURE);
uint32_t vertrix_port_list_cycle_4b3740(PORT_SIGNATURE);
uint32_t vertrix_port_list_cycle_4b37e0(PORT_SIGNATURE);
uint32_t vertrix_port_object_label_format_alternate_4b3c40(PORT_SIGNATURE);
uint32_t vertrix_port_object_label_format_4b4fb0(PORT_SIGNATURE);
uint32_t vertrix_port_list_text_format_4b7420(PORT_SIGNATURE);
uint32_t vertrix_port_decoder_header_check_4b9540(PORT_SIGNATURE);
#endif
