#ifndef RTLSTRINGSUFFIXES_H
#define RTLSTRINGSUFFIXES_H

#include "port.h"

/* Makes the path at ebx relative to the directory at edx: the string at eax becomes ".\" and the
 * path past the directory's length. Returns 1. */
uint32_t vertrix_port_string_take_after_prefix_489760(PORT_SIGNATURE);

#endif
