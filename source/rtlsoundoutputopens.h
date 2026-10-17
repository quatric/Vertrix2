#ifndef RTLSOUNDOUTPUTOPENS_H
#define RTLSOUNDOUTPUTOPENS_H

#include "port.h"

/* 0x40b110 opens the DirectSound output: the device, its primary buffer in the config's format
 * and a looping streaming buffer of 20 to 100 ms of sound, in the 0x1c-byte state at 0x52f150.
 * Returns 5 on failure. */
uint32_t vertrix_port_sound_output_open_40b110(PORT_SIGNATURE);

#endif
