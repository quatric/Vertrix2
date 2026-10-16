#ifndef PORT_RTLHOOKS_H
#define PORT_RTLHOOKS_H

#include "port.h"

/* Message hooks, decimal text to packed numbers and surface blits */
uint32_t vertrix_port_rtl_message_hook_4cfc90(PORT_SIGNATURE);
uint32_t vertrix_port_rtl_decimal_pack_4ee370(PORT_SIGNATURE);
uint32_t vertrix_port_surface_blit_47fa90(PORT_SIGNATURE);

#endif
