#ifndef PORT_SCREENS_H
#define PORT_SCREENS_H

#include "port.h"

/* Sound buffer, channel volume, table check, notice and menu screen state routines. */
uint32_t vertrix_port_sound_buffer_make_40bba0(PORT_SIGNATURE);
uint32_t vertrix_port_sound_channel_volume_40c020(PORT_SIGNATURE);
uint32_t vertrix_port_table_all_filled_415c30(PORT_SIGNATURE);
uint32_t vertrix_port_notice_call_full_416010(PORT_SIGNATURE);
uint32_t vertrix_port_screen_state_41f210(PORT_SIGNATURE);
uint32_t vertrix_port_screen_state_41f350(PORT_SIGNATURE);
uint32_t vertrix_port_screen_state_41f800(PORT_SIGNATURE);
uint32_t vertrix_port_screen_state_41fb40(PORT_SIGNATURE);

#endif
