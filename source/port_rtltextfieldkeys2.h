#ifndef PORT_RTLTEXTFIELDKEYS2_H
#define PORT_RTLTEXTFIELDKEYS2_H

#include "port.h"

/* 0x445350 polls the key queue at 0x54d640 in a loop through 0x476530, which returns a key code or
 * a character. */
uint32_t vertrix_port_text_field_key_handler_445350(PORT_SIGNATURE);

#endif
