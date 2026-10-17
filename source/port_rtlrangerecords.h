#ifndef PORT_RTLRANGERECORDS_H
#define PORT_RTLRANGERECORDS_H

#include "port.h"

/* Stores eax and the stack arguments into the record at ebx for the range dispatcher (0x4cb820). */
uint32_t vertrix_port_rtl_range_record_store_4cb5a0(PORT_SIGNATURE);

#endif
