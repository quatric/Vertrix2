#ifndef PORT_RTLLOCKS_H
#define PORT_RTLLOCKS_H

#include "port.h"

/* Child notifications, window placement, recursive locks and surface locks */
uint32_t vertrix_port_children_release_4b7020(PORT_SIGNATURE);
uint32_t vertrix_port_rtl_window_place_4ccd80(PORT_SIGNATURE);
uint32_t vertrix_port_rtl_lock_slot_enter_4e5728(PORT_SIGNATURE);
uint32_t vertrix_port_rtl_lock_enter_4e57a4(PORT_SIGNATURE);
uint32_t vertrix_port_rtl_lock_enter_4e5710(PORT_SIGNATURE);
uint32_t vertrix_port_rtl_lock_enter_4e576c(PORT_SIGNATURE);
uint32_t vertrix_port_rtl_lock_enter_4e5780(PORT_SIGNATURE);
uint32_t vertrix_port_surface_lock_47fa40(PORT_SIGNATURE);

#endif
