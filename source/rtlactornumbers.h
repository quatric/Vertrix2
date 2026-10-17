#ifndef RTLACTORNUMBERS_H
#define RTLACTORNUMBERS_H

#include "port.h"

/* Stores edx as the actor's number at +0x180 and formats it with vertrix_port_rtl_print_4cdfb0
 * (0x4cdfb0), using format 0x5110a8. */
uint32_t vertrix_port_actor_set_number_text_4b58a0(PORT_SIGNATURE);

#endif
