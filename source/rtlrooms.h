#ifndef RTLROOMS_H
#define RTLROOMS_H

#include "port.h"

/* Screen room refreshes, text panels and glyph rows, pointer steering, title screen setups and
 * picture tables. */
uint32_t vertrix_port_screen_room_refresh_4237d0(PORT_SIGNATURE);
uint32_t vertrix_port_text_panel_make_45fc80(PORT_SIGNATURE);
uint32_t vertrix_port_text_glyph_row_440490(PORT_SIGNATURE);
uint32_t vertrix_port_actor_pointer_steer_445b90(PORT_SIGNATURE);
uint32_t vertrix_port_screen_title_music_41f080(PORT_SIGNATURE);
uint32_t vertrix_port_screen_title_room_41f500(PORT_SIGNATURE);
uint32_t vertrix_port_picture_tables_load_41e5e0(PORT_SIGNATURE);

#endif
