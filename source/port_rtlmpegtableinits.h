#ifndef PORT_RTLMPEGTABLEINITS_H
#define PORT_RTLMPEGTABLEINITS_H

#include "port.h"

/* Builds the MP3 decoder's floating-point tables when the reader is reset (powers through 0x4c9921
 * and conversions between integer, double and single). */
uint32_t vertrix_port_mpeg_tables_init_406170(PORT_SIGNATURE);

#endif
