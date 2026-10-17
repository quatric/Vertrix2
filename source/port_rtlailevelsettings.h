#ifndef PORT_RTLAILEVELSETTINGS_H
#define PORT_RTLAILEVELSETTINGS_H

#include "port.h"

/* Sets a computer player's values from its level byte (dl): +0x15c from table 0x4f8cec, +0x160 from
 * that value's range (2 above 3, other values for 7 and 12), +0x164 from table 0x4f8d38, and +0x180
 * to -1. */
uint32_t vertrix_port_ai_level_settings_init_425ef0(PORT_SIGNATURE);

#endif
