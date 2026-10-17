#ifndef RTLXMMODULELOADS_H
#define RTLXMMODULELOADS_H

#include "port.h"

/* Loads an XM module from a stream into a new module record (eax = the stream, edx = where the
 * record goes); returns 0, 8 without memory or 0xb for a file it does not take. */
uint32_t vertrix_port_xm_module_load_4b826f(PORT_SIGNATURE);

#endif
