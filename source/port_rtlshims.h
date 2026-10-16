#ifndef PORT_RTLSHIMS_H
#define PORT_RTLSHIMS_H

#include "port.h"

/* Runtime library small shims. */
uint32_t vertrix_port_rtl_stream_unbuffer_4e373e(PORT_SIGNATURE);
uint32_t vertrix_port_rtl_overflow_error_4e2389(PORT_SIGNATURE);
uint32_t vertrix_port_rtl_char_fold_4eb250(PORT_SIGNATURE);
uint32_t vertrix_port_rtl_chain_restore_4e6b2c(PORT_SIGNATURE);
uint32_t vertrix_port_rtl_message_hook_484530(PORT_SIGNATURE);
uint32_t vertrix_port_rtl_call_if_set_4e6b50(PORT_SIGNATURE);
uint32_t vertrix_port_rtl_object_flush_4e5bec(PORT_SIGNATURE);
uint32_t vertrix_port_rtl_query_dword_4cf910(PORT_SIGNATURE);

#endif
