#ifndef PORT_RTLTHREADRECORDS_H
#define PORT_RTLTHREADRECORDS_H

#include "port.h"

/* Calls 0x4dd3e0 with eax 0 and raises through 0x4dee00 when it returns nonzero. */
uint32_t vertrix_port_rtl_thread_record_finish_4dd430(PORT_SIGNATURE);

#endif
