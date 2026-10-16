#ifndef PORT_RTLBLOCKIMAGELOADS_H
#define PORT_RTLBLOCKIMAGELOADS_H

#include "port.h"

/* Routine 0x41df30 switches on the per-index mode word dword [0x4f8554 + idx*4]. */
uint32_t vertrix_port_block_images_load_for_mode_41df30(PORT_SIGNATURE);

#endif
