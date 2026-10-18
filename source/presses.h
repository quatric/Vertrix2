#ifndef PRESSES_H
#define PRESSES_H

#include "port.h"

/* Button hover and arrival state and dial turn routines. */
uint32_t vertrix_port_button_hover_446c10(PORT_SIGNATURE);
uint32_t vertrix_port_button_hover_446fe0(PORT_SIGNATURE);
uint32_t vertrix_port_button_arrive_446d70(PORT_SIGNATURE);
uint32_t vertrix_port_button_arrive_447140(PORT_SIGNATURE);
uint32_t vertrix_port_dial_turn_4498e0(PORT_SIGNATURE);
uint32_t vertrix_port_dial_turn_449e80(PORT_SIGNATURE);
uint32_t vertrix_port_dial_turn_44a3a0(PORT_SIGNATURE);

#endif
