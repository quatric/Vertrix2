#ifndef PORT_ITEMS_H
#define PORT_ITEMS_H

#include "port.h"

/* Menu item maker, overlay spawn, input acknowledge and sound cue routines. */
uint32_t vertrix_port_menu_item_make_4601c0(PORT_SIGNATURE);
uint32_t vertrix_port_menu_item_make_460b60(PORT_SIGNATURE);
uint32_t vertrix_port_menu_item_make_460df0(PORT_SIGNATURE);
uint32_t vertrix_port_menu_item_make_460ed0(PORT_SIGNATURE);
uint32_t vertrix_port_menu_item_make_460fa0(PORT_SIGNATURE);
uint32_t vertrix_port_menu_item_make_461090(PORT_SIGNATURE);
uint32_t vertrix_port_overlay_spawn_472c10(PORT_SIGNATURE);
uint32_t vertrix_port_input_queue_acknowledge_full_476320(PORT_SIGNATURE);
uint32_t vertrix_port_sound_cue_both_476720(PORT_SIGNATURE);

#endif
