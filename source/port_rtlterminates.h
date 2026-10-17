#ifndef PORT_RTLTERMINATES_H
#define PORT_RTLTERMINATES_H

#include "port.h"

/* A runtime file and handle routine (the lifter named it rtl_terminate_call): it calls 0x4cd0c0,
 * 0x4cd184, 0x4e08e0, the stream seek 0x4e0150 and the handle table setter 0x4e0228, and reads
 * GetLastError through 0x4e0884. */
uint32_t vertrix_port_rtl_terminate_call_4cd0a4(PORT_SIGNATURE);

#endif
