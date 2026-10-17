#ifndef PORT_HANDLEMAPS_H
#define PORT_HANDLEMAPS_H

#include "port.h"

/* Delete the calling thread's MFC handle maps (CHandleMap) of device contexts, GDI objects, menus
 * and windows, when it has them. */
uint32_t vertrix_port_delete_thread_dc_map(PORT_SIGNATURE);
uint32_t vertrix_port_delete_thread_gdi_map(PORT_SIGNATURE);
uint32_t vertrix_port_delete_thread_menu_map(PORT_SIGNATURE);
uint32_t vertrix_port_delete_thread_window_map(PORT_SIGNATURE);

#endif
