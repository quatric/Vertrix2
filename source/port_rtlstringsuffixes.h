#ifndef PORT_RTLSTRINGSUFFIXES_H
#define PORT_RTLSTRINGSUFFIXES_H

#include "port.h"

/* Sets the string at eax to the text at ebx past strlen(edx) characters (after clearing it with
 * 0x5109ce) and returns 1. */
uint32_t vertrix_port_string_take_after_prefix_489760(PORT_SIGNATURE);

#endif
