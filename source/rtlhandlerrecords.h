#ifndef RTLHANDLERRECORDS_H
#define RTLHANDLERRECORDS_H

#include "port.h"

/* Runtime initialisation: sets 0x5c7564 and 0x5c7568 to 0x80000000, clears 0x5c756c and 0x5c7570,
 * and builds records with the handlers 0x4d6490, 0x4d64a0 and 0x4d64b0 (calls application_link). */
uint32_t vertrix_port_rtl_handler_records_init_4d3140(PORT_SIGNATURE);

#endif
