#ifndef PORT_RTLGUARDEDCALLS_H
#define PORT_RTLGUARDEDCALLS_H

#include "port.h"

/* 0x489a10 sets up a try frame with vertrix_port_thread_chain_push (0x4d93f0) and
 * lifted_rtl_jump_capture (0x4d9f06), then calls virtual method [vtable+0x38] on the object passed
 * in eax (0x489ad2) and returns its result. */
uint32_t vertrix_port_guarded_method38_call_489a10(PORT_SIGNATURE);

#endif
