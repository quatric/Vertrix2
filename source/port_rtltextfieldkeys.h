#ifndef PORT_RTLTEXTFIELDKEYS_H
#define PORT_RTLTEXTFIELDKEYS_H

#include "port.h"

/* Loops reading keys from the key set at 0x54d640 (call 0x476530) and dispatches on the scan code.
 */
uint32_t vertrix_port_text_field_key_handler_444e00(PORT_SIGNATURE);

#endif
