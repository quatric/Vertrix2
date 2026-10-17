#ifndef PORT_RTLTHREADRECORDS2_H
#define PORT_RTLTHREADRECORDS2_H

#include "port.h"

/* Calls 0x4ddbe0 with eax 0 and raises through 0x4dee00 when it returns nonzero. */
uint32_t vertrix_port_rtl_thread_record_finish_4ddc30(PORT_SIGNATURE);

#endif
