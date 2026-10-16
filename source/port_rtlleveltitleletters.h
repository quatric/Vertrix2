#ifndef PORT_RTLLEVELTITLELETTERS_H
#define PORT_RTLLEVELTITLELETTERS_H

#include "port.h"

/* For the level index at [0x532a64], it reads the line count from 0x53bd0c and walks 36-byte
 * strings from 0x53bdfc. */
uint32_t vertrix_port_level_title_letter_actors_46f440(PORT_SIGNATURE);

#endif
