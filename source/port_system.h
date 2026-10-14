#ifndef VERTRIX_PORT_SYSTEM_H
#define VERTRIX_PORT_SYSTEM_H
#include "port.h"

/* Clean ports of runtime release, focus, event table, handle, stream buffer, text and extended
 * float routines (port_system.c). */
uint32_t vertrix_port_rtl_release_counted_4d9350(PORT_SIGNATURE);
uint32_t vertrix_port_rtl_focus_notify_4dc420(PORT_SIGNATURE);
uint32_t vertrix_port_rtl_construct_event_table_4decd0(PORT_SIGNATURE);
uint32_t vertrix_port_crt_handle_slot_add_4e02a4(PORT_SIGNATURE);
uint32_t vertrix_port_crt_handle_close_4e0fc0(PORT_SIGNATURE);
uint32_t vertrix_port_crt_stream_buffer_4e3b60(PORT_SIGNATURE);
uint32_t vertrix_port_crt_text_compare_4e4080(PORT_SIGNATURE);
uint32_t vertrix_port_crt_text_to_wide_4e6510(PORT_SIGNATURE);
uint32_t vertrix_port_rtl_extended_op_4edd24(PORT_SIGNATURE);
uint32_t vertrix_port_rtl_extended_op_4ee0dc(PORT_SIGNATURE);
#endif
