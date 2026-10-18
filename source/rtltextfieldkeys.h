#ifndef RTLTEXTFIELDKEYS_H
#define RTLTEXTFIELDKEYS_H

#include "port.h"

/* The text fields' key loops (eax = the field): each edits the field with the keys and characters
 * queued at 0x54d640 until the queue is empty or Enter or Escape closes the field. */
uint32_t vertrix_port_text_field_key_handler_444e00(PORT_SIGNATURE);
uint32_t vertrix_port_text_field_key_handler_445350(PORT_SIGNATURE);
uint32_t vertrix_port_text_field_key_input_45c9a0(PORT_SIGNATURE);

#endif
