#ifndef PORT_RTLSOUNDOUTPUTOPENS_H
#define PORT_RTLSOUNDOUTPUTOPENS_H

#include "port.h"

/* 0x40b110 clears the 0x1c-byte state at 0x52f150 and creates the sound COM object through
 * vertrix_port_com_create (0x40b040), returning 5 on failure. */
uint32_t vertrix_port_sound_output_open_40b110(PORT_SIGNATURE);

#endif
