#ifndef PORT_RTLTEXTFIELDKEYS3_H
#define PORT_RTLTEXTFIELDKEYS3_H

#include "port.h"

/* Loops polling keys with 0x476530 on 0x54d640 and edits a text field object, returning when no key
 * or char arrives. */
uint32_t vertrix_port_text_field_key_input_45c9a0(PORT_SIGNATURE);

#endif
