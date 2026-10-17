#ifndef PORT_RTLDDRAWERRORS_H
#define PORT_RTLDDRAWERRORS_H

#include "port.h"

/* Copies a message prefix to 0x5b9a48 and appends the name of a DirectDraw result code (0x8876xxxx
 * and the generic COM codes). */
uint32_t vertrix_port_ddraw_error_text_485700(PORT_SIGNATURE);

#endif
