#ifndef PORT_UPSAMPLES_H
#define PORT_UPSAMPLES_H

#include "port.h"

/* The image decoder's separate upsampling and small pool allocation. */
uint32_t vertrix_port_separate_upsample_4c3610(PORT_SIGNATURE);
uint32_t vertrix_port_pool_allocate_small_4c4d20(PORT_SIGNATURE);

#endif
