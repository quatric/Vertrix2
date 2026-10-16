#ifndef PORT_RTLPANELS_H
#define PORT_RTLPANELS_H

#include "port.h"

/* Decoder passes, colour map fills, panel set-up, window moves and surface lists */
uint32_t vertrix_port_jpeg_main_pass_4bd950(PORT_SIGNATURE);
uint32_t vertrix_port_palette_map_fill_48c970(PORT_SIGNATURE);
uint32_t vertrix_port_panel_construct_4b6a30(PORT_SIGNATURE);
uint32_t vertrix_port_rtl_window_reposition_4cf4d0(PORT_SIGNATURE);
uint32_t vertrix_port_surface_list_clear_47f0f0(PORT_SIGNATURE);

#endif
